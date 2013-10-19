import numpy as np
import numpy.matlib as ml
import numpy.linalg as la
import scipy.optimize as opt
import sympy as sp
import sympy.utilities.autowrap as spauto
import sympy.utilities.codegen as spcode
import ctypes as ct
from sympy.printing.ccode import CCodePrinter
import collections, warnings, tempfile, os, operator, sys, shutil, time, commands

import dk_templates
from models import GND, Out

def _print_Piecewise(self, expr):
    # This method is called only for inline if constructs
    # Top level piecewise is handled in doprint()
    ecpairs = ["(%s) ? (%s) : " % (self._print(c), self._print(e)) \
                   for e, c in expr.args[:-1]]
    last_line = ""
    if expr.args[-1].cond == True:
        last_line = "(%s)" % self._print(expr.args[-1].expr)
    else:
        ecpairs.append("(%s) ? (%s)" % \
                       (self._print(expr.args[-1].cond),
                        self._print(expr.args[-1].expr)))
    return "(" + "".join(ecpairs) + last_line + ")"

CCodePrinter._print_Piecewise = _print_Piecewise

def pkgconfig(*packages, **kw):
    flag_map = {'-I': 'include_dirs', '-L': 'library_dirs', '-l': 'libraries'}
    for token in commands.getoutput("pkg-config --libs --cflags %s" % ' '.join(packages)).split():
        kw.setdefault(flag_map.get(token[:2]), []).append(token[2:])
    return kw

def matrix_add(*args):
    l = [m for m in args if m.size]
    if l:
        return reduce(ml.add, l)
    else:
        return ml.zeros(0).T

def load_from_shared_lib(fname, shapes):
    if 1:
        c_real = ct.c_double
        dtp = np.float64
    else:
        c_real = ct.c_float
        dtp = np.float32
    def c_arr(s, w=False):
        flags = ['C']
        if w:
            flags.append('W')
        return np.ctypeslib.ndpointer(dtype=c_real, ndim=1, shape=(shapes[s],), flags=flags)
    def c_mat(w=False):
        flags = ['C']
        if w:
            flags.append('W')
        return np.ctypeslib.ndpointer(dtype=c_real, ndim=2, flags=flags)
    c_int_p = ct.POINTER(ct.c_int)
    c_real_p = ct.POINTER(c_real)
    lib = ct.cdll.LoadLibrary(fname)
    c_calc = lib.calc
    c_calc.restype = ct.c_int
    c_calc.argtypes = [c_arr("ni"), c_arr("nx"), c_arr("nn",True), c_arr("nx",True), c_arr("no",True), c_int_p, c_int_p, c_real_p]
    c_set_state = lib.set_state
    c_set_state.restype = None
    c_set_state.argtypes = [c_arr("nn"), c_arr("nx")]
    c_get_info = lib.get_info
    c_get_info.restype = None
    c_get_info.argtypes = [c_arr("nn",True), c_arr("nx", True), c_int_p, c_int_p, c_real_p]
    c_calc_stream = lib.calc_stream
    c_calc_stream.restype = ct.c_int
    c_calc_stream.argtypes = [c_mat(), c_mat(True), ct.c_int]
    info = ct.c_int()
    nfev = ct.c_int()
    fnorm = c_real()
    def calc(u, x, v):
        u = np.array(u, dtype=dtp)
        x = np.array(x, dtype=dtp)
        v = np.array(v, dtype=dtp)
        x_new = np.zeros(shapes["nx"], dtype=dtp)
        o = np.zeros(shapes["no"], dtype=dtp)
        if c_calc(u, x, v, x_new, o, ct.byref(info), ct.byref(nfev), ct.byref(fnorm)) < 0:
            if fnorm.value > 1e-7:
                raise RuntimeError("convergence: method=%s, info=%d, nfev=%d, fnorm=%g"
                                   % (shapes["method"], info.value, nfev.value, fnorm.value))
        return o, x_new, v
    def calc_stream(u):
        assert u.shape[1] == shapes["ni"]
        u = np.array(u, dtype=dtp)
        o = np.zeros((u.shape[0], shapes["no"]), dtype=dtp)
        c_calc_stream(u, o, u.shape[0])
        return o
    def get_info():
        v = np.zeros(shapes["nn"], dtype=dtp, order='C')
        x = np.zeros(shapes["nx"], dtype=dtp, order='C')
        c_get_info(v, x, ct.byref(info), ct.byref(nfev), ct.byref(fnorm))
        return v, x, info.value, nfev.value, fnorm.value
    def set_state(v, x):
        v = np.array(v, dtype=dtp)
        x = np.array(x, dtype=dtp)
        c_set_state(v, x)
    return calc, set_state, get_info, calc_stream

class CythonCodeWrapper(spauto.CodeWrapper):

    _filename = "dk_code"
    _module_basename = "dk_sim"

    def __init__(self, d, tempdir=None, verbose=False):
        self.d = d
        if tempdir is not None:
            tempdir = os.path.abspath(tempdir)
        spauto.CodeWrapper.__init__(self, None, filepath=tempdir, verbose=verbose)
        l = ["%s=%s" % v for v in pkgconfig('cminpack','eigen3').items()]
        l.append("extra_compile_args=['-mavx','-g0','-O2','-ffast-math','-UNDEBUG']")
        l.append("extra_link_args=['-fPIC','-Wl,--strip-all','-UNDEBUG']")
        l.append("language='c++'")
        d["flags"] = ",\n".join(["    " + v for v in l])
        d["mcount"] = spauto.CodeWrapper._module_counter

    @property
    def command(self):
        command = [sys.executable, "setup.py", "build_ext", "--inplace"]
        return command

    def _prepare_files(self):
        pyxfilename = 'dk_sim.pyx'
        codefilename = "%s.c" % self.filename

        # pyx
        if 0:
            with open(pyxfilename, 'w') as f:
                f.write(pyx_template % self.d)

        # setup.py
        with open('setup.py', 'w') as f:
            print >> f, dk_templates.get_setup_template() % self.d

    def _generate_code(self):
        with open('dk_code.cpp', 'w') as f:
            f.write(dk_templates.get_cpp_template(self.d["method"]) % self.d)
        if 0:
            with open('dk_code.h', 'w') as f:
                f.write(h_template % self.d)

    def wrap_code(self):
        workdir = self.filepath or tempfile.mkdtemp("_sympy_compile")
        if not os.access(workdir, os.F_OK):
            os.mkdir(workdir)
        oldwork = os.getcwd()
        os.chdir(workdir)
        try:
            self._generate_code()
            self._prepare_files()
            self._process_files(None)
            return load_from_shared_lib(os.path.join(workdir, self.module_name+".so"), self.d)
        finally:
            spauto.CodeWrapper._module_counter +=1
            os.chdir(oldwork)
            if not self.filepath:
                shutil.rmtree(workdir)

    @classmethod
    def _get_wrapped_function(cls, mod):
        return mod.calc_c


class Parser(object):
    """
    Xr: for all nodes n in Xr: n = f(X)
    Xl: for all nodes n in Xl: dX/dt = f(n)
    """
    def __init__(self, S, V, fs, method=None, TR=True, pure_python=False):
        self.V = V
        self.fs = fs
        if method is None:
            method = 'hybr'
        self.solver_method = method
        self.TR = TR   # True: TR (trapezoidal) integration, False: BE backward euler
        self.mm = 2.0 if TR else 1.0
        self.nodes = {}
        self.element_name = collections.defaultdict(list)
        tc = self.collect(S)
        n = len(self.nodes) + tc["V"]
        self.S = ml.zeros((n,n))
        self.N = dict([(t, ml.zeros((tc[t[0]], n)))
                       for t in "R","Xl","Xr","Nl","Nr","I","O"])
        self.Gx = np.zeros(tc["X"])
        self.Gr = np.zeros(tc["R"])
        self.Z = np.zeros(tc["X"])
        self.f = np.array((None,)*tc["N"])
        for row in S:
            row[0].process(self, [c if isinstance(c, Out) else self.nodes.get(c, -1) for c in row[1:]], V.get(row[0]), fs, self.mm)
        self.v0 = np.zeros(tc["N"])
        self.x = np.zeros(tc["X"])
        self.make_S()
        self.compile_py_func()
        self.op = V.get("OP",[0.]*tc["I"])
        self.calc_dc(self.op)
        if not pure_python:
            self.c_calc, self.c_set_state, self.c_get_info, self.c_calc_stream = self.compile_c_func()
            self.__class__.__call__ = self.eval_c ##FIXME better use subclassing
        else:
            self.__class__.__call__ = self.eval_py

    def extra_variable_index(self, idx):
        return len(self.nodes) + idx

    def extra_variable_by_name(self, tpl):
        return len(self.nodes) + self.element_name["V"].index(tpl)

    def collect(self, S):
        tc = collections.Counter()
        l = self.element_name["S"]
        for row in S:
            conn = row[1:]
            row[0].add_count(tc, conn)
            for s in conn:
                if s not in self.nodes:
                    if s != GND and not isinstance(s, Out):
                        self.nodes[s] = len(self.nodes)
                        l.append((s,None))
        return tc

    def new_row(self, N, sym, f=None):
        l = self.element_name[N]
        n = len(l)
        if N == "V":
            n += len(self.nodes)
        l.append((sym,f))
        return n

    def current_row(self, N):
        n = len(self.element_name[N]) - 1
        if N == "V":
            n += len(self.nodes)
        return n

    def add_S_currents(self, conn, value):
        if conn[0] != -1:
            self.S[conn[0], conn[0]] += value
            if conn[1] != -1:
                self.S[conn[0], conn[1]] += -value
        if conn[1] != -1:
            self.S[conn[1], conn[1]] += value
            if conn[0] != -1:
                self.S[conn[1], conn[0]] += -value

    def add_S(self, idx, conn, value):
        for i in conn[0], conn[1]:
            if i != -1:
                self.S[idx,i] += value
            value = -value
        for i in conn[0], conn[1]:
            value = -value
            if i != -1:
                self.S[i,idx] += value

    def add_conn(self, N, node, conn, val):
        if conn != -1:
            self.N[N][node, conn] += val

    def add_2conn(self, N, node, conn, value=1):
        if len(conn) != 2:
            raise ValueError("2 connections expected")
        for i, v in zip(conn, (value, -value)):
            self.add_conn(N, node, i, v)

    def format_element(self, el, pref=""):
        n, d = el
        return "%s%s%s" % (pref, n, d and ("[%s]" % d) or "")

    def make_S(self):
        Gr = ml.diag(self.Gr)
        Nr = self.N["R"]
        Nxl = self.N["Xl"]
        Nxr = self.N["Xr"]
        Nnl = self.N["Nl"]
        Nnr = self.N["Nr"]
        I = self.N["I"]
        S = self.S + Nr.T * Gr * Nr
        m = self.mm
        if 0:
            np.set_printoptions(linewidth=200)
            nn = np.get_printoptions()["precision"]+8
            print "    "+" ".join(["%-*.*s" % (nn, nn, d) for d in self.node_names()])
            for ss, nn in zip(str(S).split('\n'), self.node_names()):
                print ss[:-1], "i@%s" % nn
            print
            for i, e in enumerate(self.node_names()):
                l = [self.format_element(v,"X.") for j, v in enumerate(self.element_name['X']) if self.N['Xl'][j, i] != 0]
                if l:
                    print "%s <-" % e, ", ".join(l)
            for i, e in enumerate(self.element_name['X']):
                l = [v for j, v in enumerate(self.node_names()) if self.N['Xr'][i, j] != 0]
                if l:
                    print "d%s/dt <-" % self.format_element(e,"X."), ", ".join(l)
            print
            for i, e in enumerate(self.node_names()):
                l = [self.format_element(v) for j, v in enumerate(self.element_name['N']) if self.N['Nl'][j, i] != 0]
                if l:
                    print "%s <-" % e, ", ".join(l)
            for i, e in enumerate(self.element_name['N']):
                l = ["f(%s)" % v for j, v in enumerate(self.node_names()) if self.N['Nr'][i, j] != 0]
                if l:
                    print "%s =" % self.format_element(e), ", ".join(l)
            print self.N["Nl"]
            print self.N["Nr"]
            #raise SystemExit
        Si = S.I

        conc = lambda *a: ml.concatenate(a, axis=1)
        Z = ml.diag(self.Z)

        T = m * Z * Nxl * Si
        self.A = T * Nxr.T - (Z if self.TR else ml.diag((self.Z - 1) / 2.0))
        self.B = T * I.T
        self.C = T * Nnr.T

        ##self.N["O"] = ml.eye(len(Si))
        T = self.N["O"] * Si
        self.D = T * Nxr.T
        self.E = T * I.T
        self.F = T * Nnr.T

        T = Nnl * Si
        self.G = T * Nxr.T
        self.H = T * I.T
        self.K = T * Nnr.T

    def node_names(self):
        return [self.format_element(v) for v in self.element_name["S"]+self.element_name["V"]]

    def out_labels(self):
        return self.element_name["O"][0][0].conn

    def calc_dc(self, u):
        u = ml.matrix(u, dtype=np.float64).T
        if self.A.size == 0:
            if not len(self.f):
                return
            p = self.H * u
            def func(v):
                v = ml.matrix(v).T
                r = p + self.K * self.calc_i(v) - v
                return r.A[:,0]
            with warnings.catch_warnings():
                warnings.filterwarnings(action="error")
                res = opt.root(func, self.v0, method='lm')
            if not res.success:
                raise ValueError(res.message)
            self.v0 = res.x
        else:
            I = ml.eye(len(self.A))
            try:
                Ai = (I - self.A).I
            except la.LinAlgError:
                n = len(self.v0)
                G = ml.append(self.G, self.A, axis=0)
                H = ml.append(self.H, self.B, axis=0)
                K = ml.append(self.K, self.C, axis=0)
                def func(v):
                    v = ml.matrix(v).T
                    return (G * v[n:] + H * u + K * self.calc_i(v) - v).A[:,0]
                with warnings.catch_warnings():
                    warnings.filterwarnings(action="error")
                    res = opt.root(func, np.append(self.v0, self.x), method='lm')
                if not res.success:
                    raise ValueError(res.message)
                self.v0 = res.x[:n]
                self.x = res.x[n:]
            else:
                self.x = Ai * self.B * u
                if self.K.size != 0:
                    T = self.G * Ai
                    p = (T * self.B + self.H) * u
                    KK = T * self.C + self.K
                    def func(v):
                        v = ml.matrix(v).T
                        r = p + KK * self.calc_i(v) - v
                        return r.A[:,0]
                    with warnings.catch_warnings():
                        warnings.filterwarnings(action="error")
                        res = opt.root(func, self.v0, method='lm')
                    if not res.success:
                        raise ValueError(res.message)
                    self.v0 = res.x
                    self.x += Ai * self.C * self.calc_i(self.v0)
                self.x = self.x.A[:,0]

    def print_matrix(self, A):
        xv = ([v[1] for v in sorted([(i, n) for n, i in self.nodes.items()])]+
              ["Iin%d" % (v+1) for v in range(len(self.element_name["U"]))])
        yv = reduce(list.__add__, [self.element_name[v] for v in "R","X","N","U"])
        print "<TABLE>"
        print "<TR><TH></TH>"
        print "".join(["<TH>%s</TH>" % t for t in xv])
        print "</TR>"
        for i in range(A.shape[0]):
            print "<TR><TH>%s</TH>" % yv[i]
            for j in range(A.shape[1]):
                print "<TD>%s</TD>" % str(A[i,j]).replace(".",",")
            print "</TR>"
        print "</TABLE>"
        raise SystemExit

    def calc_i(self, v):
        i = ml.zeros(len(self.f)).T
        #for n, (f, j) in enumerate(self.f):
        #    i[n] = f(v[j:])
        for n, (f, start, end) in enumerate(self.ff):
            i[n] = f(*[float(t) for t in v[start:end]])
        return i

    def eval_py(self, v_in):
        self.x = ml.matrix(self.x).T ##FIXME
        v_in = ml.matrix(v_in)
        assert v_in.shape[1] == len(self.N["I"])
        y = np.empty((v_in.shape[0], self.N["O"].shape[0]))
        def func(v):
            v = ml.matrix(v).T
            r = p + self.K * self.calc_i(v) - v
            return r.A[:,0]
        t1 = time.time()
        for n, u in enumerate(v_in):
            u = ml.matrix(u).T
            if len(self.v0) == 0:
                i = ml.matrix(()).T
            else:
                p = self.G * self.x + self.H * u
                try:
                    with warnings.catch_warnings():
                        warnings.filterwarnings(action="error")
                        res = opt.root(func, self.v0, method=self.solver_method)
                except RuntimeWarning:
                    print "##", n
                    raise
                if not res.success:
                    print "##", n
                    raise ValueError(res.message)
                v = res.x
                self.v0 = v
                i = self.calc_i(v)
            y[n,:] = matrix_add(self.D * self.x, self.E * u, self.F * i).A[:,0]
            self.x = matrix_add(self.A * self.x, self.B * u, self.C * i)
            ##print y[n,:], self.x
        self.time_per_sample = (time.time() - t1)/(n+1)
        return y

    def eval_c(self, v_in):
        v_in = np.array(v_in)
        if v_in.ndim == 1:
            v_in = v_in.reshape((len(v_in),1))
        assert v_in.shape[1] == len(self.N["I"])
        y = np.empty((v_in.shape[0], self.N["O"].shape[0]))
        x = self.x
        v = self.v0
        t1 = time.time()
        for n, u in enumerate(v_in):
            y[n,:], x, v = self.c_calc(u, x, v)
        self.time_per_sample = (time.time() - t1)/n
        self.x = x
        self.v0 = v
        return y

    def eval_c(self, v_in):
        self.c_set_state(self.v0, self.x)
        y = np.empty((v_in.shape[0], self.N["O"].shape[0]))
        t1 = time.time()
        y = self.c_calc_stream(v_in)
        self.time_per_sample = (time.time() - t1)/v_in.shape[0]
        self.v0, self.x, info, nfev, fnorm = self.c_get_info()
        return y

    def compile_py_func(self):
        self.ff = []
        for j, (expr, vl, base) in enumerate(self.f):
            self.ff.append((sp.lambdify(vl, expr), base, base+len(vl)))

    def generate_c_code(self, d):
        def mk_sym(s, n):
            return sp.symbols(['%s[%d]' % (s, i) for i in range(len(self.element_name[n]))])
        def ccode(d, ret, ex):
            r = ret + '[%d]'
            d[ret] = "\n".join([sp.ccode(ee, r % i) for i, ee in enumerate(ex)]).replace("\n","\n    ")
        def ccodesum(d, ret, l):
            l2 = [m for m in l if m]
            if l2:
                ccode(d, ret, reduce(operator.add, l2))
            else:
                d[ret] = '/* no %s */' % ret
        x = sp.Matrix(mk_sym('x', 'X'))
        u = sp.Matrix(mk_sym('u', 'I'))
        i = sp.Matrix(mk_sym('i', 'N'))
        v = mk_sym('v', 'N')
        p = mk_sym('p', 'N')
        # nonlinear function for root-finding
        l = []
        for n, (expr, vl, base) in enumerate(self.f):
            for j, e in enumerate(vl):
                expr = expr.subs(e, v[base+j])
            l.append(expr)
        ccode(d, 'fvec', sp.Matrix(p) + sp.Matrix(self.K) * sp.Matrix(l) - sp.Matrix(v))
        # "currents"
        ccode(d, 'i', l)
        # p value
        ccodesum(d, 'p', [sp.Matrix(self.G) * x, sp.Matrix(self.H) * u])
        # x update
        ccodesum(d, 'x_new', [sp.Matrix(self.A) * x, sp.Matrix(self.B) * u, sp.Matrix(self.C) * i])
        # output
        ccodesum(d, 'o', [sp.Matrix(self.D) * x, sp.Matrix(self.E) * u, sp.Matrix(self.F) * i])

    def generate_matrix_code(self, d):
        def mk_sym(s, n):
            return sp.symbols(['%s[%d]' % (s, i) for i in range(len(self.element_name[n]))])
        def ccode(d, ret, ex):
            r = ret + '[%d]'
            d[ret] = "\n".join([sp.ccode(ee, r % i) for i, ee in enumerate(ex)]).replace("\n","\n    ")
        def ccodesum(d, ret, l):
            l2 = [m for m in l if m]
            if l2:
                d[ret] = ",".join([sp.ccode(v) for v in reduce(sp.Matrix.row_join, l2).T])
            else:
                d[ret] = '/* no %s */' % ret
        v = mk_sym('v', 'N')
        p = mk_sym('p', 'N')
        # nonlinear function for root-finding
        l = []
        for n, (expr, vl, base) in enumerate(self.f):
            for j, e in enumerate(vl):
                expr = expr.subs(e, v[base+j])
            l.append(expr)
        ccode(d, 'fvec', sp.Matrix(p) + sp.Matrix(self.K) * sp.Matrix(l) - sp.Matrix(v))
        # "currents"
        ccode(d, 'i', l)
        # p value
        ccodesum(d, 'mp_data', [sp.Matrix(self.G), sp.Matrix(self.H)])
        d["mp_cols"] =  d["nx"] + d["ni"]
        d["m_cols"] = d["mp_cols"] + d["nn"]
        # x update
        ccodesum(d, 'mx_data', [sp.Matrix(self.A), sp.Matrix(self.B), sp.Matrix(self.C)])
        # output
        ccodesum(d, 'mo_data', [sp.Matrix(self.D), sp.Matrix(self.E), sp.Matrix(self.F)])

    def compile_c_func(self):
        d = dict([("n%s" % j.lower(), len(self.element_name[j])) for j in 'X', 'N', 'I','O'])
        d["method"] = "linear" if d["nn"] == 0 else self.solver_method
        #self.generate_c_code(d)
        self.generate_matrix_code(d)
        return CythonCodeWrapper(d).wrap_code()
        #return load_from_shared_lib("gencode/dk_sim_0.so", d)

