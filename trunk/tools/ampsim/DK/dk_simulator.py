import numpy as np
import numpy.matlib as ml
import numpy.linalg as la
import scipy.optimize as opt
import sympy as sp
import sympy.utilities.autowrap as spauto
import sympy.utilities.codegen as spcode
import ctypes as ct
from sympy.printing.ccode import CCodePrinter
import collections, warnings, tempfile, os, operator, sys, shutil, time, commands, subprocess, math

import dk_templates
from models import GND, Out, Node
from dk_lib import printoptions
import generate_code

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
        return args[0]

def load_from_shared_lib(fname):
    if 1:
        c_real = ct.c_double
        dtp = np.float64
    else:
        c_real = ct.c_float
        dtp = np.float32
    def c_arr(n, w=False):
        flags = ['C']
        if w:
            flags.append('W')
        return np.ctypeslib.ndpointer(dtype=c_real, ndim=1, shape=(n,), flags=flags)
    def c_mat(w=False):
        flags = ['C']
        if w:
            flags.append('W')
        return np.ctypeslib.ndpointer(dtype=c_real, ndim=2, flags=flags)
    c_int_p = ct.POINTER(ct.c_int)
    c_real_p = ct.POINTER(c_real)
    lib = ct.cdll.LoadLibrary(fname)
    c_get_structure = lib.get_structure
    c_get_structure.restype = None
    c_get_structure.argtypes = [ct.POINTER(ct.POINTER(ct.c_int)), ct.POINTER(ct.c_char_p)]
    t = ct.POINTER(ct.c_int)()
    p = ct.c_char_p();
    c_get_structure(ct.byref(t), ct.byref(p))
    nx, ni, nn, no, npl, nni, nno, end = [t[i] for i in range(8)]
    assert end == -1
    method = p.value
    c_calc = lib.calc
    c_calc.restype = ct.c_int
    c_calc.argtypes = [c_arr(ni), c_arr(nx), c_arr(nn,True), c_arr(nx,True), c_arr(no,True), c_int_p, c_int_p, c_real_p]
    c_set_state = lib.set_state
    c_set_state.restype = None
    c_set_state.argtypes = [c_arr(nn), c_arr(nx)]
    c_get_info = lib.get_info
    c_get_info.restype = None
    c_get_info.argtypes = [c_arr(nn,True), c_arr(nx, True), c_arr(nni,True), c_arr(nni,True), c_int_p, c_int_p, c_real_p]
    c_calc_stream = lib.calc_stream
    c_calc_stream.restype = ct.c_int
    c_calc_stream.argtypes = [c_mat(), c_mat(True), ct.c_int]
    c_calc_nonlin = lib.calc_nonlin
    c_calc_nonlin.restype = ct.c_int
    c_calc_nonlin.argtypes = [ct.c_int, c_mat(), c_mat(True), c_arr(nn, True), c_int_p, c_int_p, c_real_p]
    c_calc_pot_update = lib.calc_inv_update
    c_calc_pot_update.restype = None
    c_calc_pot_update.argtypes = [c_arr(npl)]
    info = ct.c_int()
    nfev = ct.c_int()
    fnorm = c_real()
    def calc(u, x, v):
        u = np.array(u, dtype=dtp)
        x = np.array(x, dtype=dtp)
        v = np.array(v, dtype=dtp)
        x_new = np.zeros(shapes[nx], dtype=dtp)
        o = np.zeros(shapes[no], dtype=dtp)
        if c_calc(u, x, v, x_new, o, ct.byref(info), ct.byref(nfev), ct.byref(fnorm)) < 0:
            if fnorm.value > 1e-7:
                raise RuntimeError("convergence: method=%s, info=%d, nfev=%d, fnorm=%g"
                                   % (method, info.value, nfev.value, fnorm.value))
        return o, x_new, v
    def calc_stream(u):
        assert u.shape[1] == ni
        u = np.array(u, dtype=dtp)
        o = np.zeros((u.shape[0], no), dtype=dtp)
        if c_calc_stream(u, o, u.shape[0]) != 0:
            v, x, minmax, g_info, g_nfev, g_fnorm = get_info()
            raise ValueError("convergence error: info=%d, nfev=%d, fnorm=%g" % (g_info, g_nfev, g_fnorm))
        return o
    def get_info():
        v = np.zeros(nn, dtype=dtp, order='C')
        x = np.zeros(nx, dtype=dtp, order='C')
        minv = np.zeros(nni, dtype=dtp, order='C')
        maxv = np.zeros(nni, dtype=dtp, order='C')
        c_get_info(v, x, minv, maxv, ct.byref(info), ct.byref(nfev), ct.byref(fnorm))
        return v, x, np.vstack((minv, maxv)).T, info.value, nfev.value, fnorm.value
    def set_state(v, x):
        v = np.array(v, dtype=dtp)
        x = np.array(x, dtype=dtp)
        c_set_state(v, x)
    def calc_nonlin(p, v):
        assert p.shape[1] == nni
        p = np.array(p, dtype=dtp, order='C', copy=False)
        i = np.zeros((p.shape[0], nno), dtype=dtp, order='C')
        r = c_calc_nonlin(len(p), p, i, v, ct.byref(info), ct.byref(nfev), ct.byref(fnorm))
        if r != 0:
            raise ValueError("convergence error: info=%d, nfev=%d, fnorm=%g" % (info.value, nfev.value, fnorm.value))
        return i
    return calc, set_state, get_info, calc_stream, calc_nonlin, c_calc_pot_update

class CythonCodeWrapper(spauto.CodeWrapper):

    _filename = "dk_code"
    _module_basename = "dk_sim"

    def __init__(self, d, code, tempdir=None, verbose=False):
        self.d = d
        self.code = code
        if tempdir is not None:
            tempdir = os.path.abspath(tempdir)
        spauto.CodeWrapper.__init__(self, None, filepath=tempdir, verbose=verbose)
        dct = pkgconfig('cminpack','eigen3')
        dct["include_dirs"].append(os.path.abspath(".."))
        l = ["%s=%s" % v for v in dct.items()]
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
        # setup.py
        with open('setup.py', 'w') as f:
            print >> f, dk_templates.get_setup_template() % self.d

    def _generate_code(self):
        with open('dk_code.cpp', 'w') as f:
            f.write(self.code)
        if "extra_code" in self.d:
            for fname, code in self.d["extra_code"]:
                with open(fname, 'w') as f:
                    f.write(code)
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
            return load_from_shared_lib(os.path.join(workdir, self.module_name+".so"))
        finally:
            spauto.CodeWrapper._module_counter +=1
            os.chdir(oldwork)
            if not self.filepath:
                shutil.rmtree(workdir)


def get_unique_rows(a):
    """returns unique rows of a 2-dim array
    """
    order = np.lexsort(a.T)
    a = a[order]
    diff = np.diff(a, axis=0)
    ui = np.ones(len(a), dtype=bool)
    ui[1:] = (diff != 0).any(axis=1) 
    return a[ui]

def get_blockdiag_permutation(B):
    """returns the permuted index list to transform B to block diagonal form

    B: quadratic (sparse) matrix
    returns: index permutation (p), block indexlist (bl)

    To get the block diagonal matrix A:
    A = B[p][:,p]

    Permutation matrix:
    Q = matrix(eye(len(p)))[p]
    A = Q * B * Q.T

    To permute a list of row or column labels with the matrix:
    labels_for_A = [labels_for_B[i] for i in p]

    To get the ith block matrix:
    r = slice(bl[i], bl[i+1])
    A[r,r]
    """
    B = ml.matrix(B, bool)
    G = B.T * B
    while True:
        G1 = G * G
        if (G1 == G).all():
            break
    n = B.shape[0]
    p = []
    bl = [0]
    for row in get_unique_rows(G.A):
        i = np.nonzero(row)[0]
        p.extend(i)
        bl.append(len(p))
    return p, bl


class Nonlin(object):

    def __init__(self):
        pass


class Parser(object):
    def __init__(self, S, V, fs, solver=None, TR=True, pure_python=False, c_tempdir=None, c_verbose=False,
                 c_debug_load=None, extra_sources=None, symbolic=False):
        self.V = V
        self.fs = fs
        if solver is None:
            solver = dict(method = 'hybr')
        else:
            solver = dict(solver)
        self.solver_method = solver["method"]
        del solver["method"]
        if self.solver_method in ('hybr', 'lm'):
            solver.setdefault("factor", 1.e2)
        self.solver_dict = solver
        self.TR = TR   # True: TR (trapezoidal) integration, False: BE backward euler
        self.mm = 2.0 if TR else 1.0
        self.c_tempdir = c_tempdir
        self.c_verbose = c_verbose
        self.c_debug_load = c_debug_load
        self.extra_sources = extra_sources
        self.symbolic = symbolic
        self.nodes = {}
        self.element_name = collections.defaultdict(list)
        tc = self.collect(S)
        n = len(self.nodes) + tc["V"]
        self.S = ml.zeros((n,n))
        self.N = dict([(t, ml.zeros((tc[t[0]], n)))
                       for t in "R","Xl","Xr","Nl","Nr","I","O","P"])
        self.Pv = np.zeros(tc["P"])
        self.pot_func = np.array((None,)*tc["P"])
        self.ConstVoltages = ml.zeros(n)
        self.Z = np.zeros(tc["X"])
        self.CZ = ml.matrix(np.diag(np.ones(tc["N"], dtype=int)))
        self.f = np.array((None,)*tc["N"])
        alpha = self.mm * fs
        if symbolic:
            self.S = sp.Matrix(self.S)
            for k in self.N.keys():
                self.N[k] = sp.Matrix(self.N[k])
            self.Pv = sp.Matrix(self.Pv)
            alpha = sp.symbols("s")
            d = {}
            for k, v in V.items():
                if isinstance(k, Node):
                    sym = sp.Symbol(str(k))
                    if isinstance(v, dict):
                        v = v.copy()
                        v["value"] = sym
                    else:
                        v = sym
                    d[k] = v
            V = d
        for row in S:
            row[0].process(self, [c if isinstance(c, Out) else self.nodes.get(c, -1) for c in row[1:]], V.get(row[0]), alpha)
        self.v0 = np.zeros(tc["N"])
        self.x = np.zeros(tc["X"])
        self.pot = V.get("POT", {})
        self.make_S()
        self.compile_py_func()
        self.pp = ml.eye(tc["N"])
        #self.pp = self.K.I
        #self.pp = ml.matrix(((1,-0.55,0.9,-0.9),(0,1,0,0),(0,0,1,0),(0,0,0,1)))
        self.op = V.get("OP",[0.]*tc["I"])
        self.calc_dc(self.op)
        if not pure_python:
            self.pot_list = []
            self.c_calc, self.c_set_state, self.c_get_info, self.c_calc_stream, self.c_calc_nonlin, self.c_calc_pot_update = self.compile_c_func()
            self.c_calc_pot_update(np.array([self.pot[v] for v in self.pot_list]))
            self.eval = self.eval_c
            self.nonlin = self.nonlin_c
        else:
            self.eval = self.eval_py
            self.nonlin = self.nonlin_py

    def __call__(self, v_in):
        return self.eval(v_in)

    def calc_Rv(self):
        n = len(self.Pv)
        Rv = ml.matrix(np.zeros((n, n)))
        for i, ((a, f), p) in enumerate(zip(self.pot_func, self.Pv)):
            k = str(a)
            try:
                v = self.pot[k]
            except KeyError:
                v = self.pot[k] = 0.5
            Rv[i, i] = float(f.n(subs={a: v})) * p
        return Rv

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

    def add_currents(self, m, conn, value):
        if conn[0] != -1:
            m[conn[0], conn[0]] += value
            if conn[1] != -1:
                m[conn[0], conn[1]] += -value
        if conn[1] != -1:
            m[conn[1], conn[1]] += value
            if conn[0] != -1:
                m[conn[1], conn[0]] += -value

    def add_S_currents(self, conn, value):
        self.add_currents(self.S, conn, value)

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

    def show_symbolic(self):
        c = sp.symbols("c")
        s = sp.symbols("s")
        v = sp.Matrix(sp.symbols("v:%d" % self.S.shape[0]))
        z = sp.symbols("z")
        b = c*(z-1)/(z+1)
        Rv = sp.diag(*[1/(f * p) for (a, f), p in zip(self.pot_func, self.Pv)])
        Nv = self.N["P"]
        SS = self.S + Nv.T * Rv * Nv
        p = subprocess.Popen("maxima -b /dev/fd/0 --very-quiet 2>&1 >/dev/null", shell=True,
                             stdin=subprocess.PIPE, stdout=subprocess.PIPE)
        p.stdin.write("stringout(\"/dev/fd/2\",facsum(linsolve([%s], [%s])[%d], s));\n" % (
            ", ".join(["%s = %s" % ss for ss in zip(SS * v, self.N["I"])]),
            ", ".join([str(ss) for ss in v]),
            np.array(self.N["O"]).nonzero()[1]+1,
            ))
        p.stdin.close()
        expr = p.stdout.read()
        #print expr
        p.wait()
        syms = set()
        for i in SS:
            syms |= i.atoms(sp.Symbol)
        expr = eval(expr.split("=",1)[1].rstrip(";\n").replace("^","**"), dict([(str(sym),sym) for sym in syms]))
        r = [sp.poly(e, s) for e in sp.fraction(expr)]
        c = r[1].TC()
        r[0] = sp.poly(r[0]/c, s)
        r[1] = sp.poly(r[1]/c, s)
        ss = set()
        syms = []
        for a, f in self.pot_func:
            if a not in ss:
                syms.append(a)
                ss.add(a)
        def print_c(e, c):
            ll = 0
            for e1, i in zip(e.coeffs(), e.monoms()):
                i = i[0]
                if syms:
                    x = sp.poly(e1, syms)
                    ss = 0
                    for co, o in zip(x.coeffs(), x.monoms()):
                        ss += reduce(operator.mul, [pow(y, p) for y, p in zip(syms, o)], 1) * co.simplify()
                else:
                    ss = e1
                sym = "%s%d" % (c, i)
                print '\n%s = %s' % (sym, ss)
                ll += sp.symbols(sym) * pow(s, i)
            return ll
        e1 = print_c(r[0], 'b')
        e2 = print_c(r[1], 'a')
        def print_C(e, cc):
            c = sp.symbols("c")
            l = e.monoms()[0]
            for e1, i in zip(e.coeffs(), e.monoms()):
                i = l[0]-i[0]
                sym = "%s%d" % (cc, i)
                print '\n%s = %s' % (sym, e1)
        r = [sp.poly(e, z) for e in sp.fraction((e1 / e2).subs(s, b).ratsimp())]
        e1 = print_C(r[0], 'B')
        e2 = print_C(r[1], 'A')
        raise SystemExit
        # with printoptions(precision=0):
        #     print
        #     l = np.random.permutation(range(self.K.shape[0]))
        #     K = self.K[l][:,l]
        #     Z = np.diagonal(self.CZ)[l]
        #     p1 = range(len(Z))
        #     n = np.count_nonzero(Z)
        #     k = n
        #     for i in range(n):
        #         if not Z[i]:
        #             while not Z[k]:
        #                 k += 1
        #             t = p1[i]
        #             p1[i] = p1[k]
        #             p1[k] = t
        #             k += 1
        #     ll = np.array(['A','B','C','D','E','F','G','H'])
        #     ll = ll[p1]
        #     Z = Z[p1]
        #     K = K[p1][:,p1]
        #     B = K[:n,:n]
        #     #print Z
        #     #print ll
        #     #print B
        #     p, bl = get_blockdiag_permutation(B)
        #     ll = [ll[i] for i in p]
        #     A = B[p][:,p]
        #     Kn = np.zeros_like(K)
        #     nn = K.shape[0]-n
        #     Kn[:n,:n] = A
        #     Kn[:,n:] = K[:,n:]
        #     Kn[n:,:] = K[n:,:]
        #     for i, j in zip(bl[:-1], bl[1:]):
        #         print Kn[range(i,j)][:,range(i,j)+range(n,Kn.shape[0])]
        #         print
        #     print Kn[n:,:]
        #     #Q = ml.matrix(np.eye(len(p)))[p]
        #     #print Q * B * Q.T
        #     #print p
        #     #print [ll[i] for i in p]
        # raise SystemExit

    def make_S(self):
        Nxl = self.N["Xl"]
        Nxr = self.N["Xr"]
        Nnl = self.N["Nl"]
        Nnr = self.N["Nr"]
        No = self.N["O"]
        Nv = self.N["P"]
        I = self.N["I"]
        CV = self.ConstVoltages
        S = self.S
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
        if self.symbolic:
            self.show_symbolic()
        Si = S.I

        conc = lambda *a: ml.concatenate(a, axis=1)
        Z = ml.diag(self.Z)

        T = m * Z * Nxl * Si
        self.A0 = T * Nxr.T - (Z if self.TR else ml.diag((self.Z - 1) / 2.0))
        self.B0 = T * I.T
        self.Bc0 = T * CV.T
        self.C0 = T * Nnr.T

        T = No * Si
        self.D0 = T * Nxr.T
        self.E0 = T * I.T
        self.Ec0 = T * CV.T
        self.F0 = T * Nnr.T

        T = Nnl * Si
        self.G0 = T * Nxr.T
        self.H0 = T * I.T
        self.Hc0 = T * CV.T
        self.K0 = T * Nnr.T

        # find number of linear independent outputs of the nonlinear function
        if self.F0.shape[1] > 0 and len(self.pot_func) == 0:
            M = np.append(self.F0, self.C0, axis=0)
            Uo, SVo, Vo = la.svd(M, full_matrices=False)
            prec = math.sqrt(sys.float_info.epsilon) ##FIXME
            SVo = np.where(SVo / SVo[0] > prec, SVo, 0)
            n = np.count_nonzero(SVo)
            if n < self.K0.shape[0] and n < self.F0.shape[0] + self.C0.shape[0]:
                self.Mi = (np.diag(SVo) * Vo)[:n]
                self.Fo = Uo[:self.F0.shape[0],:n]
                self.Co = Uo[self.F0.shape[0]:,:n]
            elif self.F0.shape[0] + self.C0.shape[0] < self.K0.shape[0]:
                self.Mi = np.append(self.F0, self.C0, axis=0)
                self.Fo = np.eye(self.F0.shape[0],self.Mi.shape[0])
                self.Co = np.eye(self.C0.shape[0],self.Mi.shape[0],self.F0.shape[1])
            else:
                self.Mi = ml.matrix(np.identity(n))
                self.Fo = self.F0
                self.Co = self.C0
        else:
            self.Mi = ml.matrix(np.identity(self.F0.shape[1]))
            self.Fo = self.F0
            self.Co = self.C0

        # find number of linear independent inputs to the nonlinear function
        if self.G0.shape[0] > 0 and len(self.pot_func) == 0:
            U0, SV0, V0 = la.svd(np.append(self.G0, self.H0, axis=1), full_matrices=False)
            prec = math.sqrt(sys.float_info.epsilon) ##FIXME
            SV0 = np.where(SV0 / SV0[0] > prec, SV0, 0)
            self.svnz = np.count_nonzero(SV0)
        else:
            self.svnz = self.G0.shape[0]
        if self.svnz < self.G0.shape[0]:
            U0 = U0[:,:self.svnz]
            U0H = U0.H
            self.G0 = U0H * self.G0
            self.H0 = U0H * self.H0
            self.U0 = U0
            self.U0H = U0H
        else:
            self.U0 = ml.matrix(np.identity(self.G0.shape[0]))

        if len(self.pot_func):
            # Woodbury Identity: \left(A+UCV \right)^{-1} = A^{-1} - A^{-1}U \left(C^{-1}+VA^{-1}U \right)^{-1} VA^{-1}, 
            T = Si * Nv.T
            self.Q = Nv * T
            self.Uxl = m * Z * Nxl * T
            self.Uo = No * T
            self.Unl = Nnl * T
            T = Si.T * Nv.T
            self.Uxr = Nxr * T
            self.Unr = Nnr * T
            self.Uu = I * T
            self.Ucv = CV * T

    def node_names(self):
        return [self.format_element(v) for v in self.element_name["S"]+self.element_name["V"]]

    def out_labels(self):
        return self.element_name["O"][0][0].conn

    def calc_dc(self, u):
        u = ml.matrix(u, dtype=np.float64).T
        A, B, Bc, C, D, E, Ec, F, G, H, Hc, K = self.calc_matrixes()
        if A.size == 0:
            if not len(self.f):
                return
            p = H * u + Hc
            def func(v):
                v = ml.matrix(v).T
                r = p + K * self.calc_i(v) - self.CZ * v
                return r.A[:,0]
            with warnings.catch_warnings():
                warnings.filterwarnings(action="error")
                res = opt.root(func, self.v0, method='lm') ##FIXME
            if not res.success:
                raise ValueError(res.message)
            self.v0 = res.x
        else:
            I = ml.eye(len(A))
            try:
                Ai = (I - A).I
            except la.LinAlgError:
                n = len(self.v0)
                if self.U0 is not None:
                    G1 = ml.append(self.U0 * G, A, axis=0)
                    H1 = ml.append(self.U0 * H, B, axis=0)
                else:
                    G1 = ml.append(G, A, axis=0)
                    H1 = ml.append(H, B, axis=0)
                Hc1 = ml.append(Hc, Bc, axis=0)
                K1 = ml.append(K, C, axis=0)
                CZ1 = ml.matrix(np.diag(np.append(np.diagonal(self.CZ), np.zeros(C.shape[0]))))
                def func(v):
                    v = ml.matrix(v).T
                    return (G1 * v[n:] + H1 * u + Hc1 + K1 * self.calc_i(v) - CZ1 * v).A[:,0]
                with warnings.catch_warnings():
                    warnings.filterwarnings(action="error")
                    res = opt.root(func, np.append(self.v0, self.x), method='lm') ##FIXME
                if not res.success:
                    raise ValueError(res.message)
                self.v0 = res.x[:n]
                self.x = res.x[n:]
            else:
                self.x = matrix_add(Ai * B * u, Ai * Bc)
                if K.size != 0:
                    if self.U0 is not None:
                        T = self.U0 * G * Ai
                        p = matrix_add(T * B * u, T * Bc, self.U0 * H * u, Hc)
                    else:
                        T = G * Ai
                        p = matrix_add(T * B * u, T * Bc, H * u, Hc)
                    KK = T * C + K
                    def func(v):
                        v = ml.matrix(v).T
                        r = p + KK * self.calc_i(v) - self.CZ * v
                        return r.A[:,0]
                    with warnings.catch_warnings():
                        warnings.filterwarnings(action="error")
                        res = opt.root(func, self.v0, method='lm') ##FIXME
                    if not res.success:
                        raise ValueError(res.message)
                    self.v0 = res.x
                    self.x += Ai * C * self.calc_i(self.v0)
                self.x = self.x.A[:,0]
        self.v00 = self.v0
        self.x0 = self.x
        #self.p0 = matrix_add(self.pp * G * np.matrix(self.x0).T, self.pp * H * np.matrix(self.op).T)
        self.p0 = matrix_add(G * np.matrix(self.x0).T, H * np.matrix(self.op).T)

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

    def nonlin_py(self, p, K, Hc):
        def func(v):
            v = ml.matrix(v).T
            r = p + K * self.calc_i(v) - self.CZ * v
            return r.A[:,0]
        p = self.U0 * p + Hc
        try:
            with warnings.catch_warnings():
                warnings.filterwarnings(action="error")
                res = opt.root(func, self.v0, method=self.solver_method, options=self.solver_dict)
        except RuntimeWarning as e:
            raise ValueError(e)
        if not res.success:
            raise ValueError(res.message)
        v = res.x
        self.v0 = v
        return self.Mi * self.calc_i(v)

    def nonlin_c(self, p):#, K, Hc): ##FIXME
        return self.c_calc_nonlin(p, self.v0) ##FIXME

    def calc_matrixes(self):
        if len(self.pot_func):
            Qi = (self.Q + self.calc_Rv()).I
            Tx = self.Uxl * Qi
            To = self.Uo * Qi
            Tn = self.Unl * Qi
            #print np.concatenate((self.A0, self.B0, self.C0), axis=1)
            return (self.A0 - Tx * self.Uxr.T,
                    self.B0 - Tx * self.Uu.T,
                    self.Bc0 - Tx * self.Ucv.T,
                    self.C0 - Tx * self.Unr.T,
                    self.D0 - To * self.Uxr.T,
                    self.E0 - To * self.Uu.T,
                    self.Ec0 - To * self.Ucv.T,
                    self.F0 - To * self.Unr.T,
                    self.G0 - Tn * self.Uxr.T,
                    self.H0 - Tn * self.Uu.T,
                    self.Hc0 - Tn * self.Ucv.T,
                    self.K0 - Tn * self.Unr.T,
                    )
        else:
            return (self.A0, self.B0, self.Bc0, self.C0,
                    self.D0, self.E0, self.Ec0, self.F0,
                    self.G0, self.H0, self.Hc0, self.K0,
                    )
        
    def eval_py(self, v_in):
        self.x = ml.matrix(self.x).T ##FIXME
        v_in = ml.matrix(v_in)
        assert v_in.shape[1] == len(self.N["I"])
        y = np.empty((v_in.shape[0], self.N["O"].shape[0]))
        t1 = time.time()
        A, B, Bc, C, D, E, Ec, F, G, H, Hc, K = self.calc_matrixes()
        self.minmax = np.array(((float("inf"), float("-inf")),) * G.shape[0])
        for n, u in enumerate(v_in):
            u = ml.matrix(u).T
            if len(self.v0) == 0:
                i = ml.matrix(()).T
            else:
                try:
                    p = G * self.x + H * u
                    self.minmax[:,0] = np.min((self.minmax[:,0], p), axis=0)
                    self.minmax[:,1] = np.max((self.minmax[:,1], p), axis=0)
                    i = self.nonlin_py(p, K, Hc)
                except ValueError as e:
                    print "##", n
                    raise
            y[n,:] = matrix_add(D * self.x, E * u, Ec, F * i).A[:,0]
            self.x = matrix_add(A * self.x, B * u, Bc, C * i)
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
        self.v0, self.x, self.minmax, info, nfev, fnorm = self.c_get_info()
        return y

    def compile_py_func(self):
        self.ff = []
        for j, (expr, vl, base) in enumerate(self.f):
            self.ff.append((sp.lambdify(vl, expr), base, base+len(vl)))

    def generate_c_code(self, d):
        # UNUSED
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
        ccode(d, 'fvec', sp.Matrix(p) + sp.Matrix(self.K) * sp.Matrix(l) - sp.Matrix(self.CZ) * sp.Matrix(v))
        # "currents"
        ccode(d, 'i', l)
        # p value
        ccodesum(d, 'p', [sp.Matrix(self.G) * x, sp.Matrix(self.H) * u, sp.Matrix(self.Hc)])
        # x update
        ccodesum(d, 'x_new', [sp.Matrix(self.A) * x, sp.Matrix(self.B) * u, sp.Matrix(self.Bc), sp.Matrix(self.C) * i])
        # output
        ccodesum(d, 'o', [sp.Matrix(self.D) * x, sp.Matrix(self.E) * u, sp.Matrix(self.Ec), sp.Matrix(self.F) * i])

    def compile_c_func(self):
        d = dict([("n%s" % j.lower(), len(self.element_name[j])) for j in 'X', 'N', 'I','O'])
        d["nni"] = self.svnz
        d["nno"] = self.Mi.shape[0]
        d["method"] = "linear" if d["nn"] == 0 else self.solver_method
        t = "solver_%s_" % self.solver_method
        d.update(dict([(t+k, v) for k, v in self.solver_dict.items()]))
        if d["method"] == "table":
            d["extra_sources"] = self.extra_sources[0]
            d["extra_code"] = self.extra_sources[1:]
        else:
            d["extra_sources"] = ""
        #self.generate_c_code(d)
        d["mp_cols"] = d["nx"] + d["ni"]
        d["namespace"] = "nonlin"
        templ_main, templ_nonlin = dk_templates.get_templates(d["method"])
        if d["nn"] > 0:
            d["nonlin_code"] = templ_nonlin % generate_code.NonlinSolverCodeGen(
                d, self.f, self.K0, self.U0, self.Hc0, np.diagonal(self.CZ), self.Mi, len(self.pot_func) == 0).generate()
        else:
            d["nonlin_code"] = ""
        if not hasattr(self,"Q"):
            self.Q=self.Uxl=self.Uo=self.Unl=self.Uxr=Ucv=UR=None
        else:
            UR = np.concatenate((self.Uxr.T, self.Uu.T, self.Unr.T), axis=1)
            Ucv = self.Ucv.T
        code = templ_main % generate_code.SimulationCodeGen(
            d,
            np.concatenate((self.G0, self.H0), axis=1),
            np.concatenate((self.A0, self.B0, self.Co), axis=1),
            self.Bc0,
            np.concatenate((self.D0, self.E0, self.Fo), axis=1),
            self.Ec0,
            self.pot_func,
            self.Pv,
            self.pot_list,
            self.Q,
            self.Uxl,
            self.Uo,
            self.Unl,
            UR,
            Ucv,
            self.Hc0,
            self.K0
            ).generate()
        if self.c_debug_load:
            return load_from_shared_lib(self.c_debug_load)
        else:
            return CythonCodeWrapper(d, code, self.c_tempdir, self.c_verbose).wrap_code()
