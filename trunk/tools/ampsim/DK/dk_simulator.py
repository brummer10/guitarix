from __future__ import division
import numpy as np
import numpy.matlib as ml
import numpy.linalg as la
import scipy.optimize as opt
import scipy.signal as sig
import sympy as sp
import ctypes as ct
import collections, warnings, tempfile, os, operator, sys, shutil, time, commands, subprocess, math, re

import dk_templates, generate_code
from models import GND, Out, Node
from dk_lib import printoptions

try:
    opt.root
except AttributeError:
    class RootResult(object):
        def __init__(self, x, infodict, ier, mesg):
            self.x = x
            self.success = (ier == 1)
            self.status = ier
            self.message = mesg
    def opt_root(fun, x0, args=(), method='hybr', jac=None, tol=None, callback=None, options=None):
        factor = 100
        if options:
            factor = options.get("factor", 100)
        return RootResult(*opt.fsolve(fun, x0, args, jac, full_output=True))
    opt.root = opt_root

################################################################
# bugfixes
#
from sympy.printing.ccode import CCodePrinter

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
#
# end bugfixes
################################################################

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


class CodeWrapError(Exception): pass

class CodeWrapper(object):

    _filename = "dk_code"
    _module_basename = "dk_sim"
    _module_counter = 0

    def __init__(self, d, code, tempdir=None, verbose=False, flags=[]):
        self.d = d
        self.code = code
        if tempdir is not None:
            tempdir = os.path.abspath(tempdir)
        self.filepath = tempdir
        self.flags = flags
        self.quiet = not verbose
        dct = pkgconfig('cminpack','eigen3')
        dct["include_dirs"].append(os.path.abspath(".."))
        dct["include_dirs"].append(os.path.abspath("../../../src/headers"))
        l = ["%s=%s" % v for v in dct.items()]
        #l.append("extra_compile_args=['-mavx','-g0','-O2','-ffast-math','-UNDEBUG']")
        #
        # ffast-math seems to trigger a compiler error on gcc 4.7.3
        # according to documentation it expands into list of settings, including
        # funsafe-math-optimizations, which seems to be responsible for the bug.
        # But funsafe-math-optimizations in turn just expands into another list of
        # settings. When using the expanded list of settings the bug is gone (?!).
        #
        # maybe -mavx is the culprit??
        fast_math_expand=(
            #" '-funsafe-math-optimizations',"
            " '-fno-math-errno',"
            " '-ffinite-math-only', '-fno-rounding-math',"
            " '-fno-signaling-nans', '-fcx-limited-range',"
            " '-fno-signed-zeros', '-fno-trapping-math',"
            " '-fassociative-math', '-freciprocal-math'"
            )
        l.append("extra_compile_args=['-g0','-O2',%s,'-UNDEBUG','-Dcreal=%s','-fvisibility=hidden']" % (fast_math_expand, d["c_real"]))
        l.append("extra_link_args=['-fPIC','-Wl,--strip-all','-UNDEBUG','-Dcreal=%s']" % d["c_real"])
        l.append("language='c++'")
        d["flags"] = ",\n".join(["    " + v for v in l])
        d["mcount"] = CodeWrapper._module_counter

    @property
    def module_name(self):
        return "%s_%s" % (self._module_basename, CodeWrapper._module_counter)

    def _process_files(self, routine):
        command = self.command
        command.extend(self.flags)
        null = open(os.devnull, 'w')
        try:
            if self.quiet:
                retcode = subprocess.call(command, stdout=null, stderr=subprocess.STDOUT)
            else:
                retcode = subprocess.call(command)
        except OSError:
            retcode = 1
        if retcode:
            raise CodeWrapError(
                    "Error while executing command: %s" % " ".join(command))

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
            soname = os.path.join(workdir, self.module_name+".so")
            return soname, SimulateC(soname)
        finally:
            CodeWrapper._module_counter +=1
            os.chdir(oldwork)
            if not self.filepath:
                shutil.rmtree(workdir)


class LinearFilter(object):

    def __init__(self, p, jacobi):
        self.in_mat = p.N["I"]
        self.out_mat = p.N["O"]
        if self.in_mat.shape[0] != 1 or self.out_mat.shape[0] != 1:
            raise ValueError("linear filter generation only implemented for circuits with one input and one output channel")
        pot_func = p.get_pot_funcs()
        Rv = sp.diag(*[1/(f * v) for (a, f), v in zip(pot_func, p.Pv)])
        Nv = p.N["P"]
        S = p.S + Nv.T * Rv * Nv
        if jacobi is not None:
            S -= p.N["Nr"].T * jacobi * p.N["Nl"]
        self.S = S
        ss = set()
        self.syms = []
        for a, f in pot_func:
            if a not in ss:
                self.syms.append(a)
                ss.add(a)
        self.subst_var_default = p.get_variable_defaults()

    def get_s_coeffs(self):
        s = sp.symbols("s")
        expr = self.solve(self.S, self.in_mat, self.out_mat)
        r = [sp.poly(e, s) for e in sp.fraction(expr)]
        tc = r[1].TC()
        b_coeffs, b_terms = self.collect_s_coeffs(sp.poly(r[0], s), 'b', tc)
        a_coeffs, a_terms = self.collect_s_coeffs(sp.poly(r[1], s), 'a', tc)
        if a_coeffs[0] == -1:
            a_coeffs *= -1
            b_coeffs *= -1
        return b_coeffs, a_coeffs, b_terms / a_terms

    def collect_s_coeffs(self, expr, prefix, tc):
        s = sp.symbols("s")
        monoms = expr.monoms()
        max_degree = monoms[0][0]
        filter_coeffs = np.zeros(max_degree+1, dtype=object)
        ll = 0
        for e, i in zip(expr.coeffs(), monoms):
            i = i[0]
            if self.syms:
                # factorize according to variable symbols
                x = sp.poly(e, self.syms)
                ss = 0
                for co, o in zip(x.coeffs(), x.monoms()):
                    ss += reduce(operator.mul, [pow(y, p) for y, p in zip(self.syms, o)], 1) * (co/tc).simplify()
            else:
                ss = e/tc
            filter_coeffs[i] = ss
            sym = "%s%d" % (prefix, i)
            ll += sp.symbols(sym) * pow(s, i)
        return filter_coeffs, ll

    def transform_bilinear(self, expr):
        s = sp.symbols("s")
        fs = sp.symbols("fs")
        c = sp.symbols("c")
        z = sp.symbols("z")
        b = c*(z-1)/(z+1)
        r = [sp.poly(e, z) for e in sp.fraction(expr.subs(s, b).ratsimp())]
        return self.collect_z_symbolic(r[0]), self.collect_z_symbolic(r[1]), 2 * fs

    def collect_z_symbolic(self, expr):
        c = sp.symbols("c")
        monoms = expr.monoms()
        max_degree = monoms[0][0]
        filter_coeffs = np.zeros(max_degree+1, dtype=object)
        for e, i in zip(expr.coeffs(), monoms):
            idx = max_degree - i[0]
            filter_coeffs[idx] = e
        return filter_coeffs

    def convert_variable_dict(self, subst_var):
        d = self.subst_var_default.copy()
        df = set(subst_var.keys()) - set([str(v) for v in d.keys()])
        if df:
            raise ValueError("unknown variable(s): %s" % ", ".join(df))
        d.update(dict([(sp.symbols(k), v) for k, v in subst_var.items()]))
        return d

    def get_z_coeffs(self, samplerate=None, subst_var=None):
        if samplerate is None:
            c = 2 * sp.symbols("fs")
        else:
            c = 2 * samplerate
        z = sp.symbols("z")
        b = c*(z-1)/(z+1)
        expr = self.S.subs(sp.symbols("s"), b)
        expr = self.solve(expr, self.in_mat, self.out_mat)
        if subst_var is not None:
            expr = expr.subs(subst_var)
            syms = None
        else:
            syms = self.syms
        # divide coeffs by magnitude of trailing denominator coefficient == a1 coefficient of filter
        lc = sp.poly(sp.fraction(expr)[1], z).LC()
        lc = lc.subs(self.subst_var_default)
        if samplerate is None:
            lc = lc.subs(sp.symbols("fs"), 48000.)
        r = [sp.poly((e/lc).expand(), z) for e in sp.fraction(expr)]
        return (self.collect_z_coeffs(r[0], 'b', syms),
                self.collect_z_coeffs(r[1], 'a', syms))

    def collect_z_coeffs(self, expr, prefix, syms):
        monoms = expr.monoms()
        max_degree = monoms[0][0]
        filter_coeffs = np.zeros(max_degree+1, dtype=object)
        for e, i in zip(expr.coeffs(), monoms):
            i = i[0]
            if syms:
                # factorize according to variable symbols
                x = sp.poly(e.expand(), syms)
                ss = 0
                for co, o in zip(x.coeffs(), x.monoms()):
                    ss += reduce(operator.mul, [pow(y, p) for y, p in zip(syms, o)], 1) * co.evalf()
            else:
                ss = e.evalf()
            idx = max_degree-i
            filter_coeffs[idx] = sp.horner(ss, wrt=(syms or [])+[sp.symbols("fs")])
        return filter_coeffs

    def coeffs_as_faust_code(self, prefix, coeffs):
        l = []
        for i, c in enumerate(coeffs):
            c = re.sub(r'([a-zA-Z0-9]+)\*\*(\d+)', r'pow(\1,\2)', str(c))
            l.append('%s%d = %s;' % (prefix, i, c))
        return l

    def print_coeffs(self, prefix, coeffs, f=sys.stdout):
        print >>f, "\n\n".join(self.coeffs_as_faust_code(prefix, coeffs))

    def spectrum(self, b, a, start_freq=20, stop_freq=10000, fs=48000, nbins=8*1024):
        b = [float(x) for x in b]
        a = [float(x) for x in a]
        w, h = sig.freqz(b, a, nbins)
        cut = slice(int(round(2 * nbins * start_freq / fs)), int(round(2 * nbins * stop_freq / fs)) + 1)
        w = (w[cut] * (fs/(2*np.pi)))
        h = 20*np.log10(abs(h[cut]))
        return w, h

    def solve(self, S, in_mat, out_mat):
        v = sp.Matrix(sp.symbols("v:%d" % self.S.shape[0]))
        p = subprocess.Popen("maxima -b /dev/fd/0 --very-quiet 2>&1 >/dev/null", shell=True,
                             stdin=subprocess.PIPE, stdout=subprocess.PIPE)
        p.stdin.write("stringout(\"/dev/fd/2\",facsum(linsolve([%s], [%s])[%d], s));\n" % (
            ", ".join(["%s = %s" % e for e in zip(S * v, in_mat)]),
            ", ".join([str(sym) for sym in v]),
            np.array(out_mat).nonzero()[1]+1,
            ))
        p.stdin.close()
        expr = p.stdout.read()
        p.wait()
        syms = set()
        for i in S:
            syms |= i.atoms(sp.Symbol)
        return eval(expr.split("=",1)[1].rstrip(";\n").replace("^","**"), dict([(str(sym),sym) for sym in syms]))


class EquationSystem(object):

    def __init__(self, parser, jacobi_par=None, svd_prec=None):
        self.parser = parser
        if svd_prec is None:
            svd_prec = math.sqrt(sys.float_info.epsilon)
        self.jacobi_par = jacobi_par
        self.svd_prec = svd_prec
        self.make_eq(parser)

    def get_parser(self):
        return self.parser

    @staticmethod
    def get_unique_rows(a):
        """returns unique rows of a 2-dim array
        """
        order = np.lexsort(a.T)
        a = a[order]
        diff = np.diff(a, axis=0)
        ui = np.ones(len(a), dtype=bool)
        ui[1:] = (diff != 0).any(axis=1) 
        return a[ui]

    @staticmethod
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

    def print_S(self, p):
        S = p.S
        with printoptions(linewidth=200):
            nn = np.get_printoptions()["precision"]+8
            print "    "+" ".join(["%-*.*s" % (nn, nn, d) for d in p.node_names()])
            for ss, nn in zip(str(S).split('\n'), p.node_names()):
                print ss[:-1], "i@%s" % nn
            print
            for i, e in enumerate(p.node_names()):
                l = [p.format_element(v,"X.") for j, v in enumerate(p.element_name['X']) if p.N['Xl'][j, i] != 0]
                if l:
                    print "%s <-" % e, ", ".join(l)
            for i, e in enumerate(p.element_name['X']):
                l = [v for j, v in enumerate(p.node_names()) if p.N['Xr'][i, j] != 0]
                if l:
                    print "d%s/dt <-" % p.format_element(e,"X."), ", ".join(l)
            print
            for i, e in enumerate(p.node_names()):
                l = [p.format_element(v) for j, v in enumerate(p.element_name['N']) if p.N['Nl'][j, i] != 0]
                if l:
                    print "%s <-" % e, ", ".join(l)
            for i, e in enumerate(p.element_name['N']):
                l = ["f(%s)" % v for j, v in enumerate(p.node_names()) if p.N['Nr'][i, j] != 0]
                if l:
                    print "%s =" % p.format_element(e), ", ".join(l)
            print p.N["Nl"]
            print p.N["Nr"]

    def get_status(self):
        return "nx=%d, nni=%d, nn=%d, nno=%d, ni=%d, no=%d, np=%d" % (self.nx, self.nni, self.nn, self.nno, self.ni, self.no, self.np)

    def make_eq(self, p):
        self.nx, self.nn, self.ni, self.no, self.np = [len(p.element_name[j]) for j in 'X', 'N', 'I', 'O', 'P']
        self.mp_cols = self.nx + self.ni
        Nxl, Nxr, Nnl, Nnr, No, Nv, I = [p.N[j] for j in "Xl", "Xr", "Nl", "Nr", "O", "P", "I"]
        CV = p.ConstVoltages
        m = p.mm
        self.f = p.get_nonlin_funcs()
        self.CZ = p.CZ
        if self.jacobi_par is not None:
            J, Jc, select, unselect = self.jacobi_par
            Si = (p.S - Nnr[unselect].T * J[unselect][:,unselect] * Nnl[unselect]).I
            CV = CV + (Nnr[unselect].T * Jc[unselect]).T
            Nnr = Nnr[select]
            Nnl = Nnl[select]
            self.nn = len(select)
            self.CZ = self.CZ[select][:,select]
            # rebase base index
            f = np.zeros(len(self.f), dtype=object)
            for j, (expr, vl, base) in enumerate(self.f):
                f[j] = (expr, vl, base-j)
            f = f[select]
            self.f = np.zeros(len(f), dtype=object)
            for j, (expr, vl, base) in enumerate(f):
                self.f[j] = (expr, vl, base+j)
            p.f = self.f
            p.element_name["N"] = np.array(p.element_name["N"])[select]
        else:
            Si = p.S.I

        Z = ml.diag(p.Z)

        T = m * Z * Nxl * Si
        self.A0 = T * Nxr.T - (Z if p.TR else ml.diag((p.Z - 1) / 2.0))
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

        self.make_nonlin_input_trans()
        #self.nni = self.nn
        #self.U0 = ml.matrix(np.identity(self.nn))
        self.make_nonlin_output_trans()
        #self.nno = self.nn
        #self.Mi = ml.matrix(np.identity(self.nn))
        #self.Co = self.C0
        #self.Fo = self.F0

        if self.np:
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

    def make_nonlin_input_trans(self):
        # find number of linear independent inputs to the nonlinear function
        if self.G0.shape[0] > 0 and self.G0.shape[1] > 0 and self.np == 0:
            U0, SV0, V0 = la.svd(np.append(self.G0, self.H0, axis=1), full_matrices=False)
            SV0 = np.where(SV0 / SV0[0] > self.svd_prec, SV0, 0)
            self.nni = np.count_nonzero(SV0)
        else:
            self.nni = self.nn
        if self.nni < self.nn:
            U0 = U0[:,:self.nni]
            U0H = U0.H
            self.G0 = U0H * self.G0
            self.H0 = U0H * self.H0
            self.U0 = U0
        else:
            self.U0 = ml.matrix(np.identity(self.nn))

    def make_nonlin_output_trans(self):
        # find number of linear independent outputs of the nonlinear function
        if self.nn == 0 or self.np != 0:
            self.nno = self.nn
            self.Mi = ml.matrix(np.identity(self.nn))
            self.Fo = self.F0
            self.Co = self.C0
            return
        Uo, SVo, Vo = la.svd(np.append(self.F0, self.C0, axis=0), full_matrices=False)
        SVo = np.where(SVo / SVo[0] > self.svd_prec, SVo, 0)
        n = np.count_nonzero(SVo)
        if n < self.nn and n < self.nx + self.no:
            self.nno = n
            self.Mi = (np.diag(SVo) * Vo)[:n]
            self.Fo = Uo[:self.F0.shape[0],:n]
            self.Co = Uo[self.F0.shape[0]:,:n]
        elif self.nx + self.no < self.nn:
            self.nno = self.nx + self.no
            self.Mi = np.append(self.F0, self.C0, axis=0)
            self.Fo = np.eye(self.no, self.nno)
            self.Co = np.eye(self.nx, self.nno, self.nn)
        else:
            self.nno = n
            self.Mi = ml.matrix(np.identity(n))
            self.Fo = self.F0
            self.Co = self.C0


class Simulate(object):

    def __init__(self, eq, solver):
        self.eq = eq
        self.parser = eq.get_parser()
        if solver is None:
            self.solver_dict = dict(method = 'hybr')
        else:
            self.solver_dict = dict(solver)
        self.solver_method = self.solver_dict["method"]
        del self.solver_dict["method"]
        if self.solver_method in ('hybr', 'lm'):
            self.solver_dict.setdefault("factor", 1.e2)
            self.solver_dict.setdefault("xtol", math.sqrt(sys.float_info.epsilon))

    def get_solver(self):
        d = self.solver_dict.copy()
        d["method"] = self.solver_method
        return d

    def get_eq(self):
        return self.eq

    def get_parser(self):
        return self.parser


class SimulatePy(Simulate):

    def __init__(self, eq, solver=None):
        Simulate.__init__(self, eq, solver)
        parser = eq.get_parser()
        self.pot_func = parser.get_pot_funcs()
        self.Pv = parser.Pv
        self.pot = parser.pot
        self.out_labels = parser.out_labels()
        self.v0 = parser.V.get("v0", np.zeros(eq.nn))
        self.x = np.zeros(eq.nx)
        self.o0 = np.zeros(eq.no)
        self.op = parser.op
        self.compile_py_func()
        self.calc_dc(parser.op)
        #FIXME:
        self.pot_list = []
        for a, f in self.pot_func:
            s = str(a)
            if s not in self.pot_list:
                self.pot_list.append(s)

    def set_variable(self, var, val):
        self.pot[var] = val

    def calc_Rv(self):
        n = self.eq.np
        Rv = ml.matrix(np.zeros((n, n)))
        for i, ((a, f), p) in enumerate(zip(self.pot_func, self.Pv)):
            k = str(a)
            try:
                v = self.pot[k]
            except KeyError:
                v = self.pot[k] = 0.5
            Rv[i, i] = float(f.n(subs={a: v})) * p
        return Rv

    def calc_matrixes(self):
        eq = self.eq
        if eq.np:
            Qi = (eq.Q + self.calc_Rv()).I
            Tx = eq.Uxl * Qi
            To = eq.Uo * Qi
            Tn = eq.Unl * Qi
            return (eq.A0 - Tx * eq.Uxr.T,
                    eq.B0 - Tx * eq.Uu.T,
                    eq.Bc0 - Tx * eq.Ucv.T,
                    eq.C0 - Tx * eq.Unr.T,
                    eq.D0 - To * eq.Uxr.T,
                    eq.E0 - To * eq.Uu.T,
                    eq.Ec0 - To * eq.Ucv.T,
                    eq.F0 - To * eq.Unr.T,
                    eq.G0 - Tn * eq.Uxr.T,
                    eq.H0 - Tn * eq.Uu.T,
                    eq.Hc0 - Tn * eq.Ucv.T,
                    eq.K0 - Tn * eq.Unr.T,
                    )
        else:
            return (eq.A0, eq.B0, eq.Bc0, eq.C0,
                    eq.D0, eq.E0, eq.Ec0, eq.F0,
                    eq.G0, eq.H0, eq.Hc0, eq.K0,
                    )

    def solve(self, func, v0):
        # use homotopy
        points = [0, 1]
        max_iter = 1000
        for tries in range(max_iter):
            try:
                with warnings.catch_warnings():
                    warnings.filterwarnings(action="error")
                    res = opt.root(func, v0, args=(points[1],), method='hybr')
            except RuntimeWarning as e:
                success = False
                msg = e
            else:
                success = res.success
                msg = res.message
            if not success:
                points.insert(1, (points[0]+points[1])/2)
                continue
            if len(points) == 2:
                return res
            v0 = res.x
            points = points[1:]
        raise ValueError("calc_dc: more than %d iterations (list msg: %s)" % (max_iter, msg))

    def calc_dc(self, u):
        u = ml.matrix(u, dtype=np.float64).T
        A, B, Bc, C, D, E, Ec, F, G, H, Hc, K = self.calc_matrixes()
        if A.size == 0:
            if len(self.eq.f):
                p = self.eq.U0 * H * u
                def func(v, fact):
                    v = ml.matrix(v).T
                    r = p + Hc * fact + K * self.calc_i(v) - self.eq.CZ * v
                    return r.A1
                self.v0 = self.solve(func, self.v0).x
        else:
            I = ml.eye(len(A))
            try:
                Ai = (I - A).I
            except la.LinAlgError:
                G1 = ml.append(self.eq.U0 * G, A, axis=0)
                H1 = ml.append(self.eq.U0 * H, B, axis=0)
                Hc1 = ml.append(Hc, Bc, axis=0)
                K1 = ml.append(K, C, axis=0)
                CZ1 = ml.matrix(np.diag(np.append(np.diagonal(self.eq.CZ), np.ones(C.shape[0]))))
                n = len(self.v0)
                def func(v, fact):
                    v = ml.matrix(v).T
                    return (G1 * v[n:] + H1 * u + Hc1*fact + K1 * self.calc_i(v) - CZ1 * v).A1
                res = self.solve(func, np.append(self.v0, self.x))
                self.v0 = res.x[:n]
                self.x = res.x[n:]
            else:
                self.x = matrix_add(Ai * B * u, Ai * Bc)
                if K.size != 0:
                    T = self.eq.U0 * G * Ai
                    p = matrix_add(T * B * u, self.eq.U0 * H * u)
                    Hc1 = matrix_add(T * Bc, Hc)
                    KK = T * C + K
                    def func(v, fact):
                        v = ml.matrix(v).T
                        r = p + Hc1 * fact + KK * self.calc_i(v) - self.eq.CZ * v
                        return r.A1
                    self.v0 = self.solve(func, self.v0).x
                    self.x += Ai * C * self.calc_i(self.v0)
                self.x = self.x.A1
        self.v00 = self.v0
        self.x0 = self.x
        self.p0 = matrix_add(G * np.matrix(self.x0).T, H * np.matrix(self.op).T)
        self.o0 = matrix_add(D * np.matrix(self.x0).T, E * np.matrix(self.op).T, Ec, F * self.calc_i(self.v0)).A1

    def calc_i(self, v):
        i = ml.zeros(len(self.ff)).T
        for n, (f, start, end) in enumerate(self.ff):
            i[n] = f(*[float(t) for t in v[start:end]])
        return i

    def nonlin_py(self, p, K, Hc):
        def func(v):
            v = ml.matrix(v).T
            r = p + K * self.calc_i(v) - self.eq.CZ * v
            return r.A1
        p = self.eq.U0 * p + Hc
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
        return self.eq.Mi * self.calc_i(v)

    def compile_py_func(self):
        self.ff = []
        if not self.eq.nn:
            # model is linearized
            return
        for j, (expr, vl, base) in enumerate(self.eq.f):
            self.ff.append((sp.lambdify(vl, expr), base, base+len(vl)))

    def calc_di(self, v, j):
        i = np.zeros(len(self.eq.f))
        for n, (f, vl, base) in enumerate(self.eq.f):
            idx = j - base
            if idx < 0 or idx >= len(vl):
                i[n] = 0.
            else:
                s = dict([(sym,val) for sym, val in zip(vl, v[base:])])
                i[n] = f.diff(vl[idx]).subs(s)
        return i

    def jacobi_numeric(self):
        J = np.zeros((len(self.eq.f), len(self.v00)))
        i0 = self.calc_i(self.v00).A1
        eps = 1e-4
        for j in range(len(self.v00)):
            v = self.v00.copy()
            v[j] += eps
            J[:, j] = (self.calc_i(v).A1 - i0) / eps
        return ml.matrix(J)

    def jacobi_symbolic(self):
        J = np.zeros((len(self.eq.f), len(self.v00)))
        for j in range(len(self.v00)):
            J[:, j] = self.calc_di(self.v00, j)
        return ml.matrix(J)

    jacobi = jacobi_symbolic

    def eval_py(self, v_in):
        self.x = ml.matrix(self.x).T ##FIXME
        v_in = ml.matrix(v_in)
        assert v_in.shape[1] == self.eq.ni
        y = np.empty((v_in.shape[0], self.eq.no))
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
            y[n,:] = matrix_add(D * self.x, E * u, Ec, F * i).A1
            self.x = matrix_add(A * self.x, B * u, Bc, C * i)
        self.time_per_sample = (time.time() - t1)/(n+1)
        self.x = self.x.A1 ##FIXME
        return y

    def __call__(self, v_in):
        return self.eval_py(v_in)


class CheckedDict(dict):
    def __setitem__(self, n, v):
        assert n not in self
        return dict.__setitem__(self, n, v)


class BuildCModule(Simulate):

    def __init__(self, name, sim, solver=None, c_tempdir=None, c_verbose=False,
                 c_real="double", extra_sources=None, linearize=False, pre_filter=None):
        if solver is None:
            solver = sim.get_solver()
        Simulate.__init__(self, sim.get_eq(), solver)
        self.name = name
        self.c_tempdir = c_tempdir
        self.c_verbose = c_verbose
        self.c_real = c_real
        self.extra_sources = extra_sources
        self.pre_filter = pre_filter
        self.eq = sim.get_eq()
        parser = sim.get_parser()
        if linearize:
            l = [i for i, e in enumerate(parser.element_name["N"]) if "linearize" not in parser.V[e[0]]]
            li = [i for i, e in enumerate(parser.element_name["N"]) if "linearize" in parser.V[e[0]]]
            J = sim.jacobi()
            Jc = sim.calc_i(sim.v00)
            par = J, Jc, l, li
            self.eq = EquationSystem(parser, par)
            sim = SimulatePy(self.eq, solver)
        self.v0, self.x0, self.p0, self.o0 = sim.v0, sim.x, sim.p0, sim.o0
        self.op = parser.op
        self.pot_func = parser.get_pot_funcs()
        self.pot = parser.pot
        self.Pv = parser.Pv
        self.pot_attr = parser.get_pot_attr()
        self.out_labels = parser.out_labels()
        #FIXME:
        self.pot_list = []
        for a, f in self.pot_func:
            s = str(a)
            if s not in self.pot_list:
                self.pot_list.append(s)

    def get_executor(self):
        return self.compile_c_func().wrap_code()

    def prepare(self):
        eq = self.eq
        d = CheckedDict(name=self.name, comment=time.ctime())
        d["c_real"] = self.c_real
        for j in "nx", "nn", "ni", "no", "np", "nni", "nno", "mp_cols":
            d[j] = getattr(eq, j)
        d["npl"] = len(self.pot_list)
        d["v0_data"] = ",".join([str(j) for j in self.v0])
        d["x0_data"] = ",".join([str(j) for j in self.x0])
        d["p0_data"] = ",".join([str(j) for j in self.p0.A1])
        d["o0_data"] = ",".join([str(j) for j in self.o0])
        d["op_data"] = ",".join([str(j) for j in self.op])
        d["out_labels"] = ",".join(['"%s"' % j for j in self.out_labels])
        d["method"] = method = "linear" if eq.nn == 0 else self.solver_method
        t = "solver_%s_" % self.solver_method
        d.update(dict([(t+k, v) for k, v in self.solver_dict.items()]))
        if method == "table":
            d["extra_sources"] = self.extra_sources[0]
            d["extra_code"] = self.extra_sources[1:]
        else:
            d["extra_sources"] = ""
        d["namespace"] = "nonlin"
        templ_main, templ_nonlin = dk_templates.get_templates(method)
        if eq.nn > 0:
            dd = d.copy()
            d["nonlin_code"] = templ_nonlin % generate_code.NonlinSolverCodeGen(
                dd, self.eq.f, eq.K0, eq.U0, eq.Hc0, np.diagonal(self.eq.CZ), eq.Mi, len(self.pot_func) == 0).generate()
        else:
            d["nonlin_code"] = ""
        d["pre_filter"] = self.pre_filter or ""
        return templ_main, d

    def make_code(self, templ_main, d):
        eq = self.eq
        if not hasattr(eq,"Q"):
            Q = Uxl = Uo = Unl = Ucv = UR = None
        else:
            Q = eq.Q
            Uxl = eq.Uxl
            Uo = eq.Uo
            Unl = eq.Unl
            UR = np.concatenate((eq.Uxr.T, eq.Uu.T, eq.Unr.T), axis=1)
            Ucv = eq.Ucv.T
        code = templ_main % generate_code.SimulationCodeGen(
            d,
            self.pot_attr,
            np.concatenate((eq.G0, eq.H0), axis=1),
            np.concatenate((eq.A0, eq.B0, eq.Co), axis=1),
            eq.Bc0,
            np.concatenate((eq.D0, eq.E0, eq.Fo), axis=1),
            eq.Ec0,
            self.pot_func,
            self.Pv,
            self.pot_list,
            self.pot,
            Q,
            Uxl,
            Uo,
            Unl,
            UR,
            Ucv,
            eq.Hc0,
            eq.K0
            ).generate()
        return code

    def compile_c_func(self):
        templ_main, d = self.prepare()
        code = self.make_code(templ_main, d)
        return CodeWrapper(d, code, self.c_tempdir, self.c_verbose)


class SimulateC(object):

    def __init__(self, soname):
        self.soname = soname
        self.load_from_shared_lib()
        self.v0, self.x, self.p0, self.o0, self.op = self.c_get_dc()
        self.v00 = self.v0
        self.x0 = self.x
        self.c_set_state(self.v0, self.x)
        self.c_calc_pot_update(np.array([self.pot[v] for v in self.pot_list], dtype=self.dtp))
        self.eval = self.eval_c
        self.nonlin = self.nonlin_c

    def set_variable(self, var, val):
        assert var in self.pot
        self.pot[var] = val
        self.c_calc_pot_update(np.array([self.pot[v] for v in self.pot_list], dtype=self.dtp))

    def nonlin_c(self, p):#, K, Hc): ##FIXME
        return self.c_calc_nonlin(p, self.v0) ##FIXME

    def eval_c(self, v_in):
        v_in = np.array(v_in)
        if v_in.ndim == 1:
            v_in = v_in.reshape((len(v_in),1))
        assert v_in.shape[1] == self.ni
        y = np.empty((v_in.shape[0], self.no))
        x = self.x
        v = self.v0
        t1 = time.time()
        for n, u in enumerate(v_in):
            y[n,:], x, v = self.c_calc(u, x, v)
        self.time_per_sample = (time.time() - t1)/n
        self.x = x
        self.v0 = v
        return y

    def reset(self):
        self.c_set_state(self.v00, self.x0)

    def eval_c(self, v_in):
        self.c_set_state(self.v0, self.x)
        y = np.empty((v_in.shape[0], self.no))
        t1 = time.time()
        y = self.c_calc_stream(v_in)
        self.time_per_sample = (time.time() - t1)/v_in.shape[0]
        self.v0, self.x, self.minmax, info, nfev, fnorm = self.c_get_info()
        return y

    def load_from_shared_lib(self):
        INTERFACE_VERSION = 1
        try:
            lib = ct.cdll.LoadLibrary(self.soname)
        except OSError as e:
            raise SystemExit(e)
        try:
            version = lib.get_interface_version()
        except AttributeError:
            raise SystemExit("%s: bad shared lib, missing get_interface_version" % self.soname)
        if version != INTERFACE_VERSION:
            raise SystemExit("interface version %d expected (found: %d)" % (version, INTERFACE_VERSION))
        c_char_pp = ct.POINTER(ct.c_char_p)
        c_get_structure = lib.get_structure
        c_get_structure.restype = None
        c_get_structure.argtypes = [c_char_pp, ct.POINTER(ct.c_int), ct.POINTER(ct.POINTER(ct.c_int)),
                                    c_char_pp, ct.POINTER(c_char_pp), ct.POINTER(ct.POINTER(ct.c_double)),
                                    ct.POINTER(c_char_pp), c_char_pp]
        nm = ct.c_char_p()
        sz = ct.c_int()
        t = ct.POINTER(ct.c_int)()
        p = ct.c_char_p()
        plist = c_char_pp()
        pvals = ct.POINTER(ct.c_double)()
        ol = c_char_pp()
        cmt = ct.c_char_p()
        c_get_structure(ct.byref(nm), ct.byref(sz), ct.byref(t), ct.byref(p),
                        ct.byref(plist), ct.byref(pvals), ct.byref(ol), ct.byref(cmt))
        nx, ni, nn, no, npl, nni, nno, end = [t[i] for i in range(8)]
        if end != -1:
            raise SystemExit("%s: bad sequence length in get_structure")
        self.nx, self.ni, self.nn, self.no, self.npl, self.nni, self.nno = nx, ni, nn, no, npl, nni, nno
        self.name = nm.value
        self.data_size = sz.value
        self.method = p.value
        self.pot_list = [plist[i] for i in range(npl)]
        self.pot = dict([(plist[i], pvals[i]) for i in range(npl)])
        self.out_labels = [ol[i] for i in range(no)]
        self.comment = cmt.value
        if self.data_size == 8:
            c_real = ct.c_double
            self.dtp = np.float64
        elif self.data_size == 4:
            c_real = ct.c_float
            self.dtp = np.float32
        else:
            raise ValueError("unknown data size: %d" % self.data_size)
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
        c_get_dc = lib.get_dc
        c_get_dc.restype = None
        c_get_dc.argtypes = [c_arr(nn, True), c_arr(nx, True), c_arr(nni, True), c_arr(no, True), c_arr(ni, True)]
        info = ct.c_int()
        nfev = ct.c_int()
        fnorm = c_real()
        def calc(u, x, v):
            u = np.array(u, dtype=self.dtp)
            x = np.array(x, dtype=self.dtp)
            v = np.array(v, dtype=self.dtp)
            x_new = np.zeros(shapes[nx], dtype=self.dtp)
            o = np.zeros(shapes[no], dtype=self.dtp)
            if c_calc(u, x, v, x_new, o, ct.byref(info), ct.byref(nfev), ct.byref(fnorm)) < 0:
                if fnorm.value > 1e-7:
                    raise RuntimeError("convergence: method=%s, info=%d, nfev=%d, fnorm=%g"
                                       % (method, info.value, nfev.value, fnorm.value))
            return o, x_new, v
        def calc_stream(u):
            assert u.shape[1] == ni
            u = np.array(u, dtype=self.dtp)
            o = np.zeros((u.shape[0], no), dtype=self.dtp)
            if c_calc_stream(u, o, u.shape[0]) != 0:
                v, x, minmax, g_info, g_nfev, g_fnorm = get_info()
                raise ValueError("convergence error: info=%d, nfev=%d, fnorm=%g" % (g_info, g_nfev, g_fnorm))
            return o
        def get_info():
            v = np.zeros(nn, dtype=self.dtp, order='C')
            x = np.zeros(nx, dtype=self.dtp, order='C')
            minv = np.zeros(nni, dtype=self.dtp, order='C')
            maxv = np.zeros(nni, dtype=self.dtp, order='C')
            c_get_info(v, x, minv, maxv, ct.byref(info), ct.byref(nfev), ct.byref(fnorm))
            return v, x, np.vstack((minv, maxv)).T, info.value, nfev.value, fnorm.value
        def set_state(v, x):
            v = np.array(v, dtype=self.dtp)
            x = np.array(x, dtype=self.dtp)
            c_set_state(v, x)
        def calc_nonlin(p, v):
            assert p.shape[1] == nni+npl, (p.shape[1], nni+npl)
            p = np.array(p, dtype=self.dtp, order='C', copy=False)
            i = np.zeros((p.shape[0], nno), dtype=self.dtp, order='C')
            r = c_calc_nonlin(len(p), p, i, v, ct.byref(info), ct.byref(nfev), ct.byref(fnorm))
            if r != 0:
                raise ValueError("convergence error: info=%d, nfev=%d, fnorm=%g" % (info.value, nfev.value, fnorm.value))
            return i
        def get_dc():
            v0 = np.zeros(nn, dtype=self.dtp, order='C')
            x0 = np.zeros(nx, dtype=self.dtp, order='C')
            p0 = np.zeros(nni, dtype=self.dtp, order='C')
            o0 = np.zeros(no, dtype=self.dtp, order='C')
            op = np.zeros(ni, dtype=self.dtp, order='C')
            c_get_dc(v0, x0, p0, o0, op)
            return v0, x0, ml.matrix(p0).T, o0, op
        self.c_calc = calc
        self.c_set_state = set_state
        self.c_get_info = get_info
        self.c_calc_stream = calc_stream
        self.c_calc_nonlin = calc_nonlin
        self.c_calc_pot_update = c_calc_pot_update
        self.c_get_dc = get_dc

    def __call__(self, v_in):
        return self.eval_c(v_in)


class Parser(object):
    # Nl = incidence matrix denoting the nodes which potentials are controlling the currents
    # Nr = incidence matrix denoting the nodes where the current flows in (> 0) or out (< 0)
    #
    def __init__(self, S, V, fs, TR=True, create_filter=False, symbolic=False):
        self.fs = fs
        self.TR = TR   # True: TR (trapezoidal) integration, False: BE backward euler
        self.create_filter = create_filter
        self.symbolic = symbolic
        self.mm = 2.0 if TR else 1.0
        self.update(S, V)

    def update(self, S, V):
        self.V = V
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
        if self.create_filter or self.symbolic:
            alpha = sp.symbols("s")
            self.S = sp.Matrix(self.S)
            for k in self.N.keys():
                self.N[k] = sp.Matrix(self.N[k])
            if self.symbolic:
                self.Pv = sp.Matrix(self.Pv)
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
        else:
            alpha = self.mm * self.fs
        for row in S:
            row[0].process(self, [c if isinstance(c, Out) else self.nodes.get(c, -1) for c in row[1:]], V.get(row[0]), alpha)
        self.pot = V.get("POT", {})
        self.op = V.get("OP",[0.]*tc["I"])

    def get_status(self):
        return ""
        
    def matches(self, create_filter, symbolic):
        return self.create_filter == create_filter and self.symbolic == symbolic

    def get_nonlin_funcs(self):
        return self.f

    def get_pot_funcs(self):
        return self.pot_func

    def get_pot_attr(self):
        attrlist = []
        for e in set([e[0] for e in self.element_name["P"]]):
            t = self.V[e]
            if not isinstance(t, dict):
                t = dict(value=t)
            var = t.get('var')
            if var is None:
                var = str(e)+"v"
            name = t.get('name', var)
            loga = t.get('a', 0)
            inv = t.get('inv', 0)
            if loga:
                expr = lambda a: (math.exp(loga * a) - 1) / (math.exp(loga) - 1)
            else:
                expr = lambda a: a
            attrlist.append((var, name, loga, inv, expr))
        return attrlist

    def get_variable_defaults(self):
        return dict([(a, self.pot.get(str(a), 0.5)) for a, f in self.pot_func])

    def extra_variable_index(self, idx):
        return len(self.nodes) + idx

    def extra_variable_by_name(self, tpl):
        try:
            return len(self.nodes) + self.element_name["V"].index(tpl)
        except ValueError:
            print "%s not in %s" % (tpl, self.element_name["V"])
            raise

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

    def show_symbolic(self, symbolic, jacobi=None):
        if symbolic:
            c = sp.symbols("c")
        else:
            #c = 2 * 48000
            c = 2 * sp.symbols("fs")
        s = sp.symbols("s")
        v = sp.Matrix(sp.symbols("v:%d" % self.S.shape[0]))
        z = sp.symbols("z")
        b = c*(z-1)/(z+1)
        Rv = sp.diag(*[1/(f * p) for (a, f), p in zip(self.pot_func, self.Pv)])
        Nv = self.N["P"]
        SS = self.S + Nv.T * Rv * Nv
        if jacobi is not None:
            SS -= self.N["Nr"].T * jacobi * self.N["Nl"]
        SS = SS.subs(s, b)
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
        ss = set()
        syms = []
        for a, f in self.pot_func:
            if a not in ss:
                syms.append(a)
                ss.add(a)
        if symbolic:
            r = [sp.poly(e, s) for e in sp.fraction(expr)]
            c = r[1].TC()
            r[0] = sp.poly(r[0]/c, s)
            r[1] = sp.poly(r[1]/c, s)
            def print_c(e, c):
                ll = 0
                for e1, i in zip(e.coeffs(), e.monoms()):
                    i = i[0]
                    if syms:
                        x = sp.poly(e1, syms)
                        ss = 0
                        for co, o in zip(x.coeffs(), x.monoms()):
                            if symbolic:
                                co = co.simplify()
                            else:
                                co = co.evalf()
                            ss += reduce(operator.mul, [pow(y, p) for y, p in zip(syms, o)], 1) * co
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
            print_C(r[0], 'B')
            print_C(r[1], 'A')
        else:
            #expr = expr.subs(dict([(a, self.pot.get(str(a), 0.5)) for a, f in self.pot_func]))
            r = [sp.poly(e, z) for e in sp.fraction(expr)]
            tc = r[1].LC()
            #r[0] = sp.poly(r[0]/tc, z)
            #r[1] = sp.poly(r[1]/tc, z)
            ss = set()
            syms = []
            for a, f in self.pot_func:
                if a not in ss:
                    syms.append(a)
                    ss.add(a)
            def print_c(e, cc):
                ll = []
                l = e.monoms()[0]
                for e1, i in zip(e.coeffs(), e.monoms()):
                    i = i[0]
                    if syms:
                        x = sp.poly(e1.expand(), syms)
                        ss = 0
                        for co, o in zip(x.coeffs(), x.monoms()):
                            #co = (co / tc).ratsimp()
                            if symbolic:
                                co = co.expand().simplify()
                            else:
                                co = co.evalf()
                            ss += reduce(operator.mul, [pow(y, p) for y, p in zip(syms, o)], 1) * co
                    else:
                        ss = (e1 / tc).evalf()
                    sym = "%s%d" % (cc, l[0]-i)
                    print '\n%s = %s' % (sym, ss)
                    ll.append(ss)
                return ll
            e1 = print_c(r[0], 'b')
            e2 = print_c(r[1], 'a')
            return e1, e2
            #expr = expr.subs(s, b)
            #print sp.poly(expr.ratsimp(), c)
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

    def node_names(self):
        return [self.format_element(v) for v in self.element_name["S"]+self.element_name["V"]]

    def out_labels(self):
        return self.element_name["O"][0][0].conn

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
        for n, (expr, vl, base) in enumerate(self.eq.f):
            for j, e in enumerate(vl):
                expr = expr.subs(e, v[base+j])
            l.append(expr)
        ccode(d, 'fvec', sp.Matrix(p) + sp.Matrix(self.K) * sp.Matrix(l) - sp.Matrix(self.eq.CZ) * sp.Matrix(v))
        # "currents"
        ccode(d, 'i', l)
        # p value
        ccodesum(d, 'p', [sp.Matrix(self.G) * x, sp.Matrix(self.H) * u, sp.Matrix(self.Hc)])
        # x update
        ccodesum(d, 'x_new', [sp.Matrix(self.A) * x, sp.Matrix(self.B) * u, sp.Matrix(self.Bc), sp.Matrix(self.C) * i])
        # output
        ccodesum(d, 'o', [sp.Matrix(self.D) * x, sp.Matrix(self.E) * u, sp.Matrix(self.Ec), sp.Matrix(self.F) * i])


def get_py_executor(parser, solver=None, linearize=False):
    sim = SimulatePy(EquationSystem(parser), solver)
    if linearize:
        J = sim.jacobi()
        sim = SimulatePy(EquationSystem(parser, J), solver)
    return sim

def get_executor(name, parser, solver=None, pure_python=True, c_tempdir=None, c_verbose=False,
                 c_debug_load="", c_real="double", extra_sources=None, linearize=False):
    if pure_python:
        return get_py_executor(parser, solver, linearize)
    elif c_debug_load:
        sim = SimulateC(c_debug_load)
        print "%s/%s: %s[%d], %s, %s" % (sim.name, sim.comment, sim.method, sim.data_size, sim.out_labels, sim.pot_list)
        return sim
    else:
        sim = SimulatePy(EquationSystem(parser), solver)
        return BuildCModule(name, sim, solver, c_tempdir, c_verbose, c_real, extra_sources, linearize).get_executor()[1]
