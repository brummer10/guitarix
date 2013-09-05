from libc.string cimport const_char, const_uchar
import numpy as np
cimport numpy as np
from libc.string cimport strcmp

cdef extern from "circuit.hpp":
    ctypedef struct N_Vector:
        pass
    N_Vector N_VNew_Serial(long int vec_length)
    void N_VDestroy_Serial(N_Vector v)
    double *NV_DATA_S(N_Vector v)
    int NV_LENGTH_S(N_Vector v)

    int FS "fs"

    cppclass UserData:
        pass

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
        int func(N_Vector x, N_Vector u, UserData *user_data)
        void update(N_Vector y, N_Vector x, N_Vector state)
        int findzero(N_Vector x, N_Vector u)
        int set_range(int i, double lower, double upper, int size)
        void init(N_Vector u0)
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


cdef find_idx(const_char *k, const_char **p, int n):
    cdef int i
    for i in range(n):
        if p[i] == k:
            return i
    return -1

cdef to_list(const_char **p, int n):
    cdef int i
    cdef list l = []
    for i in range(n):
        l.append(p[i])
    return l

cdef class CalcBase:
    cdef ComponentBase *pbase
    cdef int capture
    cdef list idx
    cdef np.ndarray capt

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
    def __cinit__(self):
        self.capture = 0
        self.idx = []

    def __dealloc__(self):
        del self.pbase

    property capt_flag:
        def __get__(self):
            return self.capture
        def __set__(self, v):
            self.capture = v

    property captured:
        def __get__(self):
            return self.capt

    cdef set_var(self, char *k, double v):
        for i in range(self.pbase.n_params):
            if strcmp(k, self.pbase.param_names[i]) == 0:
                self.pbase.params[i] = v
                return 1
        return 0           

    cdef store(self, N_Vector u):
        cdef int i
        for i in range(self.pbase.NEQ):
            self.capt[i] = NV_DATA_S(u)[i]

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
        cdef N_Vector U0 = N_VNew_Serial(self.pbase.NEQ)
        for i, v in enumerate(self.u0):
            NV_DATA_S(U0)[i] = v
        self.pbase.init(U0)
        N_VDestroy_Serial(U0)

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
        if self.capture:
            self.store(u)
        self.pbase.update(u, x, s)
        for i in range(self.pbase.NDIM-self.pbase.N_IN):
            state[i] = NV_DATA_S(s)[i]
        ret = [NV_DATA_S(u)[self.idx[i]] for i in range(self.pbase.N_OUT)]
        N_VDestroy_Serial(x)
        N_VDestroy_Serial(s)
        N_VDestroy_Serial(u)
        return ret

    def __init__(self):
        cdef int i
        cdef int j
        for i in range(self.pbase.N_OUT):
            j = find_idx(self.pbase.out_names[i], self.pbase.var_names, self.pbase.NEQ)
            if j < 0:
                raise ValueError("not found: %s", self.pbase.out_names[i])
            self.idx.append(j)
        self.capt = np.zeros(self.pbase.NEQ, dtype=np.float32)


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
        NV_DATA_S(x)[1] -= NV_DATA_S(x)[0] #added
        i = self.pbase.calc(x, s, u)
        if i:
            raise ConvergenceError(i, a, state)
        if self.capture:
            self.store(u)
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
