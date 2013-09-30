import os
from libc.string cimport const_char, const_uchar, strcmp
from libc.stdlib cimport malloc, free
import numpy as np
cimport numpy as np
np.import_array()
cdef extern from "time.h":
    cdef struct timespec:
        int tv_sec
        int tv_nsec
    ctypedef int clockid_t
    int CLOCK_MONOTONIC
    int clock_gettime(clockid_t clk_id, timespec *tp)

cdef extern from "circuit.hpp":
    ctypedef struct N_Vector:
        pass
    N_Vector N_VNew_Serial(long int vec_length)
    void N_VDestroy_Serial(N_Vector v)
    double *NV_DATA_S(N_Vector v)
    int NV_LENGTH_S(N_Vector v)

    int FS "fs"

    cppclass UserData "ComponentBase::UserData":
        double *inval
        double *state

    cppclass ComponentBase:
        int NEQ
        int NDIM
        int NVALS
        int N_IN
        int N_OUT
        int n_params
        double *params
        char **param_names
        char **in_names
        char **out_names
        char **state_names
        char **var_names
        int *ix
        int verbose
        int func(N_Vector x, N_Vector u, UserData *user_data)
        void update(N_Vector y, N_Vector x, N_Vector state)
        int startvalue(N_Vector x, N_Vector s, N_Vector u)
        int findzero(double *x, double *s, N_Vector u) 
        int set_range(int i, double lower, double upper, int size)
        void init(N_Vector u0, char* fname)
        int calc(N_Vector x, N_Vector s, N_Vector u)

    cppclass TriodeCircuit(ComponentBase):
        pass

    cppclass CoupledTriodeCircuit(ComponentBase):
        pass

    cppclass PowerAmpGate(ComponentBase):
        pass

    cppclass PowerAmpPlate(ComponentBase):
        pass

    cppclass PhaseSplitter(ComponentBase):
        void feedback_coeff(double *b0, double *b1, double *a1, double pres)

    cdef cppclass CSpline "Spline":
        CSpline(double *, int, double, double)
        double eval(double)

fs = FS


class ConvergenceError(ValueError):

    def __init__(self, err, x, s, tag=None):
        self.error = err
        self.x = x
        self.s = s
        self.tag = tag
        t = "%s: " % tag if tag else ""
        v1 = ", ".join((str(v) for v in x))
        v2 = ", ".join((str(v) for v in s))
        ValueError.__init__(
            self, "%sKINSol error %d at [%s]/[%s]" % (t, err, v1, v2))

    def __reduce__(self):
        return (ConvergenceError, (self.error, self.x, self.s, self.tag))


cdef int find_idx(const_char *k, const_char **p, int n):
    cdef int i
    for i in range(n):
        if strcmp(p[i], k) == 0:
            return i
    return -1

cdef to_list(const_char **p, int n):
    cdef int i
    cdef list l = []
    for i in range(n):
        l.append(p[i])
    return l

cdef inline double ts_diff(timespec ts1, timespec ts2):
    cdef double df = ts1.tv_sec - ts2.tv_sec
    return df * 1e9 + (ts1.tv_nsec - ts2.tv_nsec)

cdef class CalcBase:
    cdef ComponentBase *pbase
    cdef int *idx
    cdef int *capt_idx
    cdef int capt_len
    cdef list capt_vars
    cdef np.ndarray _captured
    cdef N_Vector _state
    cdef np.ndarray state_min
    cdef np.ndarray state_max
    cdef N_Vector inp
    cdef N_Vector outp
    cdef double time_per_sample

    property NDIM:
        def __get__(self):
            return self.pbase.NDIM
    property NEQ:
        def __get__(self):
            return self.pbase.NEQ
    property NVALS:
        def __get__(self):
            return self.pbase.NVALS
    property N_IN:
        def __get__(self):
            return self.pbase.N_IN
    property N_OUT:
        def __get__(self):
            return self.pbase.N_OUT
    property param_names:
        def __get__(self):
            return to_list(self.pbase.param_names, self.pbase.n_params)
    property in_names:
        def __get__(self):
            return to_list(self.pbase.in_names, self.pbase.N_IN)
    property out_names:
        def __get__(self):
            return to_list(self.pbase.out_names, self.pbase.N_OUT)
    property state_names:
        def __get__(self):
            return to_list(self.pbase.state_names, self.pbase.NDIM-self.pbase.N_IN)
    property var_names:
        def __get__(self):
            return to_list(self.pbase.var_names, self.pbase.NEQ)
    property state:
        def __get__(self):
            cdef int i
            return np.array([NV_DATA_S(self._state)[i] for i in range(self.pbase.NDIM-self.pbase.N_IN)])
        def __set__(self, v):
            for i in range(self.pbase.NDIM-self.pbase.N_IN):
                NV_DATA_S(self._state)[i] = v[i]
    property min_state:
        def __get__(self):
            return self.state_min
    property max_state:
        def __get__(self):
            return self.state_max
    property nanosec_per_sample:
        "time in nanoseconds measured for last compute call"
        def __get__(self):
            return self.time_per_sample

            
    def __dealloc__(self):
        free(self.idx)
        free(self.capt_idx)
        N_VDestroy_Serial(self.inp)
        N_VDestroy_Serial(self._state)
        N_VDestroy_Serial(self.outp)
        del self.pbase

    property capture_signals:
        def __get__(self):
            return self.capt_vars
        def __set__(self, v):
            cdef int i, j
            if isinstance(v, basestring):
                v = [v]
            l = []
            for n in v:
                j = find_idx(n, self.pbase.var_names, self.pbase.NEQ)
                if j < 0:
                    raise ValueError("not found: %s", n)
                l.append(j)
            i = len(l)
            if i != self.capt_len:
                free(self.capt_idx)
                self.capt_idx = <int*>malloc(i * sizeof(int))
                self.capt_len = i
            for j in range(i):
                self.capt_idx[j] = l[j]
            self.capt_vars = v

    property captured:
        def __get__(self):
            return self._captured

    cdef int set_var(self, char *k, double v):
        for i in range(self.pbase.n_params):
            if strcmp(k, self.pbase.param_names[i]) == 0:
                self.pbase.params[i] = v
                return 1
        return 0           

    def init(self):
        cdef int i
        for k, v in self.circuit.items():
            if not self.set_var(k, v):
                raise KeyError("unknown: %s" % k)
        for i, l in enumerate(self.start_grid):
            if not self.pbase.set_range(i, l[0], l[1], l[2]):
                raise ValueError("can't set range nr %d" % i)
        if len(self.u0) != self.pbase.NEQ:
            raise ValueError("lenght %d expected for u0" % self.pbase.NEQ)
        for i, v in enumerate(self.u0):
            NV_DATA_S(self.outp)[i] = v
        if "AMPSIM_CACHE" in os.environ:
            fname = "%s.cache" % self.comp_id
        else:
            fname = None
        if fname and os.path.exists(fname) and os.stat(fname).st_mtime < os.stat("circuit/components.py").st_mtime:
            print "remove", fname
            os.remove(fname)
        cdef const_char *_fname = NULL
        if fname:
            _fname = fname
        self.pbase.init(self.outp, _fname)

    def pre_call(self, A, with_state):
        return A

    def post_call(self, O, with_state):
        return O

    cdef np.ndarray prepare_input(self, object a, int with_state, int& n_in, int& n_out, int& ndim):
        cdef np.ndarray A = np.PyArray_FROMANY(a, np.NPY_DOUBLE, 0, 2, np.NPY_ALIGNED)
        ndim = np.PyArray_NDIM(A)
        n_in = self.pbase.NDIM if with_state else self.pbase.N_IN
        n_out = self.pbase.N_OUT
        if with_state:
            n_out += self.pbase.NDIM-self.pbase.N_IN
        if ndim == 0:
            if n_in > 1:
                raise ValueError("input array: bad shape")
            A = np.PyArray_Reshape(A, (1, 1))
            if n_out > 1:
                ndim = 1
        elif ndim == 1:
            if n_in == 1:
                A = np.PyArray_Reshape(A, ((np.PyArray_DIM(A, 0), 1)))
                if n_out > 1:
                    ndim = 2
            elif np.PyArray_DIM(A, 0) == n_in:
                A = np.PyArray_Reshape(A, (1, n_in))
                if n_out == 1:
                    ndim = 0
            else:
                raise ValueError("input array: bad shape")
        elif np.PyArray_NDIM(A) == 2:
            if np.PyArray_DIM(A, 1) != n_in:
                raise ValueError("input array: bad shape %d/%d" % (np.PyArray_DIM(A, 1), n_in))
            if n_out == 1:
                ndim = 1
        return A

    def __call__(self, a, int with_state=False):
        cdef int ndim = 0
        cdef int n_in = 0
        cdef int n_out = 0
        cdef np.ndarray A = self.prepare_input(a, with_state, n_in, n_out, ndim)
        cdef int dim[2]
        dim[0] = np.PyArray_DIM(A, 0)
        dim[1] = n_out
        cdef np.ndarray O = np.PyArray_SimpleNew(2, dim, np.NPY_DOUBLE)
        cdef np.flatiter itc
        if self.capt_len:
            dim[0] = np.PyArray_DIM(A, 0)
            dim[1] = self.capt_len
            self._captured = np.PyArray_SimpleNew(2, dim, np.NPY_DOUBLE)
            itc = np.PyArray_IterNew(self._captured)
        A = self.pre_call(A, with_state)
        cdef int i, j, n
        cdef np.flatiter it = np.PyArray_IterNew(A)
        cdef np.flatiter ito = np.PyArray_IterNew(O)
        cdef np.npy_intp ix[2]
        cdef timespec t0, t1
        cdef double v
        clock_gettime(CLOCK_MONOTONIC, &t0)
        for i in range(np.PyArray_DIM(A, 0)):
            ix[0] = i
            for j in range(self.pbase.N_IN):
                ix[1] = j
                np.PyArray_ITER_GOTO(it, ix)
                NV_DATA_S(self.inp)[j] = (<double*>np.PyArray_ITER_DATA(it))[0]
            if with_state:
                for j in range(n_in - self.pbase.N_IN):
                    ix[1] = self.pbase.N_IN + j
                    np.PyArray_ITER_GOTO(it, ix)
                    NV_DATA_S(self._state)[j] = (<double*>np.PyArray_ITER_DATA(it))[0]
            n = self.pbase.calc(self.inp, self._state, self.outp)
            if n:
                raise ConvergenceError(n, A[i], self.state, getattr(self,"comp_id",None))
            if self.capt_len:
                for j in range(self.capt_len):
                    (<double*>np.PyArray_ITER_DATA(itc))[j] = NV_DATA_S(self.outp)[self.capt_idx[j]]
                    np.PyArray_ITER_NEXT(itc)
            self.pbase.update(self.outp, self.inp, self._state)
            for j in range(self.pbase.N_OUT):
                (<double*>np.PyArray_ITER_DATA(ito))[0] = NV_DATA_S(self.outp)[self.idx[j]]
                np.PyArray_ITER_NEXT(ito)
            if with_state:
                for j in range(n_out-self.pbase.N_OUT):
                    (<double*>np.PyArray_ITER_DATA(ito))[0] = NV_DATA_S(self._state)[j]
                    np.PyArray_ITER_NEXT(ito)
            else:
                for j in range(self.pbase.NDIM - self.pbase.N_IN):
                    v = NV_DATA_S(self._state)[j]
                    if v > (<double*>np.PyArray_DATA(self.state_max))[j]:
                        (<double*>np.PyArray_DATA(self.state_max))[j] = v
                    if v < (<double*>np.PyArray_DATA(self.state_min))[j]:
                        (<double*>np.PyArray_DATA(self.state_min))[j] = v
        clock_gettime(CLOCK_MONOTONIC, &t1)
        self.time_per_sample = ts_diff(t1,t0)/np.PyArray_DIM(A, 0)
        O = self.post_call(O, with_state)
        cdef np.PyArray_Dims dm
        if ndim != np.PyArray_NDIM(O):
            if ndim == 1:
                if np.PyArray_NDIM(O) == 0:
                    dim[0] = 1
                else:
                    dim[0] = np.PyArray_DIM(O, 0) * np.PyArray_DIM(O, 1)
            else:
                if np.PyArray_NDIM(O) == 0:
                    dim[0] = 1
                    dim[1] = 1
                else:
                    dim[0] = np.PyArray_DIM(O, 0)
                    dim[1] = 1
            dm.ptr = dim
            dm.len = ndim
            O = np.PyArray_Newshape(O, &dm, np.NPY_ANYORDER)
        return O

    def func(self, a, state):
        cdef int i
        cdef N_Vector x = N_VNew_Serial(self.pbase.N_IN)
        cdef N_Vector s = N_VNew_Serial(self.pbase.NDIM-self.pbase.N_IN)
        cdef N_Vector u = N_VNew_Serial(self.pbase.NEQ)
        for i in range(self.pbase.N_IN):
            NV_DATA_S(x)[i] = a[i]
        for i in range(self.pbase.NDIM-self.pbase.N_IN):
            NV_DATA_S(s)[i] = state[i]
        i = self.pbase.calc(x, s, u)
        if i:
            raise ConvergenceError(i, a, state, getattr(self,"comp_id",None))
        self.pbase.update(u, x, s)
        for i in range(self.pbase.NDIM-self.pbase.N_IN):
            state[i] = NV_DATA_S(s)[i]
        ret = [NV_DATA_S(u)[self.idx[i]] for i in range(self.pbase.N_OUT)]
        N_VDestroy_Serial(x)
        N_VDestroy_Serial(s)
        N_VDestroy_Serial(u)
        return ret

    def startvalue(self, x, s):
        cdef int i
        cdef N_Vector X = N_VNew_Serial(self.pbase.N_IN)
        cdef N_Vector S = N_VNew_Serial(self.pbase.NDIM-self.pbase.N_IN)
        cdef N_Vector U = N_VNew_Serial(self.pbase.NEQ)
        for i in range(self.pbase.N_IN):
            NV_DATA_S(X)[i] = x[i]
        for i in range(self.pbase.NDIM-self.pbase.N_IN):
            NV_DATA_S(S)[i] = s[i]
        self.pbase.startvalue(X, S, U)
        ret = [NV_DATA_S(U)[i] for i in range(self.pbase.NEQ)]
        N_VDestroy_Serial(X)
        N_VDestroy_Serial(S)
        N_VDestroy_Serial(U)
        return ret

    def findzero(self, x, s, u, verbose=False):
        cdef int i
        cdef N_Vector X = N_VNew_Serial(self.pbase.N_IN)
        cdef N_Vector S = N_VNew_Serial(self.pbase.NDIM-self.pbase.N_IN)
        cdef N_Vector U = N_VNew_Serial(self.pbase.NEQ)
        for i in range(self.pbase.N_IN):
            NV_DATA_S(X)[i] = x[i]
        for i in range(self.pbase.NDIM-self.pbase.N_IN):
            NV_DATA_S(S)[i] = s[i]
        for i in range(self.pbase.NEQ):
            NV_DATA_S(U)[i] = u[i]
        self.pbase.verbose = verbose
        i = self.pbase.findzero(NV_DATA_S(X), NV_DATA_S(S), U)
        self.pbase.verbose = False
        if i != 0:
            raise ValueError
        ret = [NV_DATA_S(U)[i] for i in range(self.pbase.NEQ)]
        N_VDestroy_Serial(X)
        N_VDestroy_Serial(S)
        N_VDestroy_Serial(U)
        return ret

    def equations(self, x, s, u):
        cdef UserData D
        cdef N_Vector X = N_VNew_Serial(self.pbase.N_IN)
        cdef N_Vector S = N_VNew_Serial(self.pbase.NDIM-self.pbase.N_IN)
        cdef N_Vector U = N_VNew_Serial(self.pbase.NEQ)
        cdef N_Vector F = N_VNew_Serial(self.pbase.NEQ)
        for i in range(self.pbase.N_IN):
            NV_DATA_S(X)[i] = x[i]
        for i in range(self.pbase.NDIM-self.pbase.N_IN):
            NV_DATA_S(S)[i] = s[i]
        for i in range(self.pbase.NEQ):
            NV_DATA_S(U)[i] = u[i]
        D.inval = NV_DATA_S(X)
        D.state = NV_DATA_S(S)
        self.pbase.func(U, F, &D)
        ret = [NV_DATA_S(F)[i] for i in range(self.pbase.NEQ)]
        N_VDestroy_Serial(X)
        N_VDestroy_Serial(S)
        N_VDestroy_Serial(U)
        N_VDestroy_Serial(F)
        return ret

    def __init__(self):
        cdef int i
        cdef int j
        self.inp = N_VNew_Serial(self.pbase.N_IN)
        self._state = N_VNew_Serial(self.pbase.NDIM-self.pbase.N_IN)
        i = self.pbase.NDIM-self.pbase.N_IN
        self.state_min = np.PyArray_SimpleNew(1, &i, np.NPY_DOUBLE)
        self.state_min[:] = 1e99
        self.state_max = np.PyArray_SimpleNew(1, &i, np.NPY_DOUBLE)
        self.state_max[:] = -1e99
        self.outp = N_VNew_Serial(self.pbase.NEQ)
        self.idx = <int*>malloc(2*sizeof(int))
        for i in range(self.pbase.N_OUT):
            j = find_idx(self.pbase.out_names[i], self.pbase.var_names, self.pbase.NEQ)
            if j < 0:
                raise ValueError("not found: %s", self.pbase.out_names[i])
            self.idx[i] = j
        self.state = self.operating_point


cdef class tcParams(CalcBase):
    def __cinit__(self):
        self.pbase = new TriodeCircuit()


cdef class ctcParams(CalcBase):
    def __cinit__(self):
        self.pbase = new CoupledTriodeCircuit()


cdef class pagParams(CalcBase):
    def __cinit__(self):
        self.pbase = new PowerAmpGate()

cdef class papParams(CalcBase):
    def __cinit__(self):
        self.pbase = new PowerAmpPlate()

    def Xpre_call(self, A, with_state):
        return np.append(A[:,0], A[:,1] + A[:,0], axis=1)

    def post_call(self, O, with_state):
        if with_state:
            return np.append(O[:,:1] - O[:,1:2], O[:,2:], axis=1)
        else:
            return O[:,0] - O[:,1]

    def func(self, a, state):
        # expects [Ug1, Ug1+Ug2]
        # returns Ua1 - Ua2
        cdef int i
        cdef N_Vector x = N_VNew_Serial(self.pbase.N_IN)
        cdef N_Vector s = N_VNew_Serial(self.pbase.NDIM-self.pbase.N_IN)
        cdef N_Vector u = N_VNew_Serial(self.pbase.NEQ)
        for i in range(self.pbase.N_IN):
            NV_DATA_S(x)[i] = a[i]
        for i in range(self.pbase.NDIM-self.pbase.N_IN):
            NV_DATA_S(s)[i] = state[i]
        #NV_DATA_S(x)[1] -= NV_DATA_S(x)[0] #added
        i = self.pbase.calc(x, s, u)
        if i:
            raise ConvergenceError(i, a, state)
        self.pbase.update(u, x, s)
        for i in range(self.pbase.NDIM-self.pbase.N_IN):
            state[i] = NV_DATA_S(s)[i]
        ret = [NV_DATA_S(u)[3] - NV_DATA_S(u)[4]] #changed
        N_VDestroy_Serial(x)
        N_VDestroy_Serial(s)
        N_VDestroy_Serial(u)
        return ret


cdef class psParams(CalcBase):
    def __cinit__(self):
        self.pbase = new PhaseSplitter()

    def feedback_coeff(self, double pres):
        cdef double b0, b1, a1
        (<PhaseSplitter*>self.pbase).feedback_coeff(&b0, &b1, &a1, pres)
        return b0, b1, a1


cdef class Spline:
    cdef CSpline *spl
    cdef np.ndarray y

    def __cinit__(self, np.ndarray[np.float_t,ndim=1] y, double xstart, double h):
        self.y = y
        self.spl = new CSpline(<double*>np.PyArray_DATA(y), len(y), xstart, h)

    def __dealloc__(self):
        del self.spl

    def __call__(self, np.ndarray[np.float_t,ndim=1] x):
        cdef int i
        cdef double v
        out = np.empty_like(x)
        for i in range(len(x)):
            out[i] = self.spl.eval(x[i])
        return out
    
# Local Variables:
# compile-command: "rm -f pycircuit.so; python setup.py build_ext --inplace"
# End:
