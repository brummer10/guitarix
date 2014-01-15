from __future__ import division
import numpy as np
import numpy.matlib as ml
import numpy.linalg as la
import scipy.linalg as sla
import scipy.optimize as opt
import scipy.signal as sig
import sympy as sp
import ctypes as ct
import slicot
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
            factor = options.get("factor", factor)
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

class ConvergenceError(Exception): pass

class CodeWrapError(Exception): pass

class CodeWrapper(object):

    _module_counter = 0

    def __init__(self, d, code, tempdir=None, verbose=False, flags=[]):
        self.code = code
        if tempdir is not None:
            tempdir = os.path.abspath(tempdir)
        self.filepath = tempdir
        self.flags = flags
        self.quiet = not verbose
        packages = ["eigen3"]
        if d["method"] in ("hybr", "lm"):
            packages.append('cminpack')
        dct = pkgconfig(*packages)
        libs = dct.get("libraries",[])
        libs.append("m")
        if d["resample"]:
            libs.append("zita-resampler")
        self.script_dict = dict(
            includes = " ".join("-I%s" % v for v in dct.get("include_dirs",[])),
            libraries = " ".join("-l%s" % v for v in set(libs)),
            #defines = "-DCHECK_BOUNDS",
            defines = "",
            debug = False,
            sourcename = "%s_%d.cpp" % (d["id"], CodeWrapper._module_counter),
            soname = "%s_%d.so" % (d["id"], CodeWrapper._module_counter),
            soname_ = "%s_%d_.so" % (d["id"], CodeWrapper._module_counter),
            optimize = False,#(d["method"] == "table"),
            )
        self.build_script = "./build_script_%d" % CodeWrapper._module_counter

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
        command = [self.build_script]
        return command

    def _prepare_files(self):
        with open(self.build_script, 'w') as f:
            print >> f, dk_templates.build_script_template.render(self.script_dict)
            os.fchmod(f.fileno(), 0o777)
        

    def _generate_code(self):
        with open(self.script_dict['sourcename'], 'w') as f:
            f.write(self.code)

    def wrap_code(self, load_module=True):
        workdir = self.filepath or tempfile.mkdtemp("_dk_compile")
        if not os.access(workdir, os.F_OK):
            os.mkdir(workdir)
        oldwork = os.getcwd()
        os.chdir(workdir)
        try:
            self._generate_code()
            self._prepare_files()
            self._process_files(None)
            path = os.path.join(workdir, self.script_dict["soname"])
            if load_module:
                return path, SimulateC(path)
            else:
                return path
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
        for v in tc.atoms(sp.Symbol):
            tc = tc.subs(v, 1)
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

    def get_z_coeffs(self, samplerate=None, subst_var=None, as_expr=True):
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
        return (self.collect_z_coeffs(r[0], 'b', syms, as_expr),
                self.collect_z_coeffs(r[1], 'a', syms, as_expr))

    def collect_z_coeffs(self, expr, prefix, syms, as_expr=True):
        monoms = expr.monoms()
        if as_expr:
            max_degree = monoms[0][0]
            filter_coeffs = np.zeros(max_degree+1, dtype=object)
        else:
            l = []
        for e, i in zip(expr.coeffs(), monoms):
            i = i[0]
            if syms:
                # factorize according to variable symbols
                x = sp.poly(e.expand(), syms)
                if not as_expr:
                    l.append(zip(x.monoms(), x.coeffs()))
                else:
                    ss = 0
                    for co, o in zip(x.coeffs(), x.monoms()):
                        ss += reduce(operator.mul, [pow(y, p) for y, p in zip(syms, o)], 1) * co.evalf()
            else:
                if not as_expr:
                    l.append(((0,), ss))
                else:
                    ss = e.evalf()
            if as_expr:
                idx = max_degree-i
                filter_coeffs[idx] = sp.horner(ss, wrt=(syms or [])+[sp.symbols("fs")])
        if as_expr:
            return filter_coeffs
        else:
            return l, syms

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


def get_state_transform_trace(A, B, C):
    "return the trace of the gram matrices (sensitivity measure)"
    Wc = ml.matrix(sla.solve_discrete_lyapunov(A.A, (B*B.T).A))
    Wo = ml.matrix(sla.solve_discrete_lyapunov(A.T.A, (C.T*C).A))
    #R = ml.matrix(sla.cholesky(Wo, lower=False))
    #X = R * Wc * R.T
    #U, s, V = sla.svd(X)
    #U = ml.matrix(U)
    #V = ml.matrix(V)
    #lli = np.sqrt(np.sqrt(s))
    #U = R.I * V.T * ml.diag(lli)
    #Ui = ml.diag(1/lli) * V * R
    #return U, Ui
    return np.trace(Wc), np.trace(Wo)

def get_state_transform(A, B, C, tol=0):
    "calculate balanced reduced state space model realization"
    # balance matrices
    A, B, C, maxred, scale = slicot.tb01id('A', A, B, C)
    # transform to schur form
    A, B, C, U, WR, WI = slicot.tb01wd(A, B, C)
    # reduce and balance
    T, Ti, A, B, C, hsv = slicot.ab09ax('D', 'B', A, B, C, tol=tol)
    # return transformation matrix (+ inverse) and hankel singular values
    return (np.matrix(np.diag(scale).dot(U).dot(T)),
            np.matrix(Ti.dot(U.T).dot(np.diag(1/scale))),
            hsv)


class NonlinEquations(object):

    def __init__(self, eq, v_slice):
        self.eq = eq
        self.v_slice = v_slice
        self.p_slice = v_slice
        self.i_slice = v_slice
        self.nn = self.v_slice.stop - self.v_slice.start
        self.nni = self.nn
        self.nno = self.nn
        self.U = self.Mi = ml.matrix(np.identity(self.nn))
        self.Hc = ml.zeros((self.nn, 1))

    @staticmethod
    def create(eq, K, CZ, v_slice, partition):
        "return a Permution and an instance of NonlinEquations or derived"
        Pn = np.arange(len(CZ))
        if eq.np:
            return Pn, NonlinEquations(eq, v_slice)
        # permute nonlinear part to make left upper submatrix of K blockdiagonal
        p, blocklist = NonlinEquations.get_block_indices(K[v_slice][:,v_slice], CZ[v_slice])
        if len(blocklist) > 1:
            Pn[v_slice] = p
            K = K[Pn][:,Pn]
            CZ = CZ[Pn]
        if partition and len(blocklist) > 1:
            nlin = PartitionedNonlinEquations(eq, v_slice)
            Pn = Pn[nlin.create(eq, K, CZ, blocklist)]
            return Pn, nlin
        # permute the system if there is more than one strongly connected component
        p, blocklist = NonlinEquations.find_scc(K[v_slice][:,v_slice], eq.get_parser())
        if len(blocklist) > 1:
            Pn[v_slice] = p
            K = K[Pn][:,Pn]
            CZ = CZ[Pn]
            nlin = ChainedNonlinEquations(eq, v_slice)
            Pn = Pn[nlin.create(eq, K, CZ, blocklist)]
            return Pn, nlin
        return np.arange(len(CZ)), NonlinEquations(eq, v_slice)

    @staticmethod
    def rebase_nonlinear_functions(f, Pn):
        Pni = np.argsort(Pn) # inverse permutation
        a = np.zeros(len(f), dtype=object)
        for j, (expr, vl, base) in enumerate(f[Pn]):
            a[j] = (expr, vl, Pni[base])
        return a

    @staticmethod
    def get_unique_rows(a):
        """returns unique rows of a 2-dim array
        """
        if not a.size:
            return a
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
            G = G1
        n = B.shape[0]
        p = []
        bl = [0]
        for row in NonlinEquations.get_unique_rows(G.A):
            i = np.nonzero(row)[0]
            if len(i):
                p.extend(i)
                bl.append(len(p))
        if len(p) != B.shape[0]:
            p.extend(set(range(B.shape[0])) - set(p))
        return p, bl

    @staticmethod
    def get_block_indices(K, CZ):
        "returns a permutation and a list of component slices"
        nz = len(CZ)
        n = np.count_nonzero(CZ)
        if n != nz:
            pc = np.argsort(CZ == 0)
            K = K[pc][:,pc][:n,:n]
        p, bl = NonlinEquations.get_blockdiag_permutation(K)
        if n != nz:
            p = np.array(pc)[p+range(n, nz)]
        return p, [slice(i,j) for i, j in zip(bl[:-1], bl[1:])]

    @staticmethod
    def decompose(a):
        U, s, V = la.svd(a, full_matrices=False)
        o = np.sqrt(np.sum(s*s) / np.count_nonzero(s))
        sr = np.where(s, s, o)
        V1 = ml.diag(sr) * V
        V1i = (ml.diag(1/sr) * V).T
        U1 = U * np.diag(np.where(s, 1, 0))
        if (U1 <= 0).all():
            U1 = -U1
            V1 = -V1
            V1i = -V1i
        return U1, V1, V1i

    @staticmethod
    def find_scc(K, parser):
        from pygraph.classes.digraph import digraph
        from pygraph.algorithms.accessibility import mutual_accessibility
        from pygraph.algorithms.sorting import topological_sorting
        g = digraph()
        for i in range(len(K)):
            attrs = [("label","%s/%d" % (Parser.format_element(parser.element_name["N"][i]),i))]
            g.add_node(i, attrs=attrs)
        for i, j in zip(*K.A.nonzero()):
            g.add_edge((j, i))
        #from pygraph.readwrite.dot import write
        #print >>sys.stderr, write(g)
        d = {}
        gc = digraph()
        ma = mutual_accessibility(g)
        for a, b in g.edges():
            a = ma[a]
            b = ma[b]
            if not gc.has_node(id(a)):
                gc.add_node(id(a))
                d[id(a)] = a
            if not gc.has_node(id(b)):
                gc.add_node(id(b))
                d[id(b)] = b
            e = (id(a), id(b))
            if not gc.has_edge(e):
                gc.add_edge(e)
        p = []
        l = []
        for k in topological_sorting(gc):
            j = len(p)
            p.extend(d[k])
            l.append(slice(j, len(p)))
        return p, l

    @staticmethod
    def get_svd_prec(svd_prec):
        if svd_prec is None:
            return math.sqrt(sys.float_info.epsilon)
        return svd_prec

    def make_input_trans(self, matrix_list, svd_prec):
        if self.eq.np:
            return matrix_list
        # find number of linear independent inputs to the nonlinear function
        M = np.concatenate(matrix_list, axis=1)
        if not M.size:
            return matrix_list
        U, SV, V = la.svd(M, full_matrices=False)
        if SV[0] != 0:
            if svd_prec is None:
                svd_prec = self.get_svd_prec(svd_prec)
            SV = np.where(SV / SV[0] > svd_prec, SV, 0)
        nni = np.count_nonzero(SV)
        if nni == self.nn:
            return matrix_list
        U = U[:,:nni]
        UH = U.H
        self.U = U
        self.nni = nni
        self.p_slice = slice(self.p_slice.start, self.p_slice.start+nni)
        return [UH * m for m in matrix_list]

    def make_output_trans(self, matrix_list, svd_prec):
        if self.nn == 0 or self.eq.np != 0:
            return matrix_list
        # find number of linear independent outputs of the nonlinear function
        M = np.concatenate(matrix_list, axis=0)
        U, SV, V = la.svd(M, full_matrices=False)
        if SV[0] != 0:
            if svd_prec is None:
                svd_prec = self.get_svd_prec(svd_prec)
            SV = np.where(SV / SV[0] > svd_prec, SV, 0)
        n = np.count_nonzero(SV)
        if n < self.nn and n < self.eq.nx + self.eq.no:
            self.nno = n
            self.Mi = (np.diag(SV) * V)[:n]
            s = np.cumsum([0]+[m.shape[0] for m in matrix_list])
            matrix_list = [U[slice(*sl),:n] for sl in zip(s[:-1],s[1:])]
        elif self.eq.nx + self.eq.no < self.nn:
            self.nno = self.eq.nx + self.eq.no
            self.Mi = M
            M = np.eye(self.nno, self.nno)
            s = np.cumsum([0]+[m.shape[0] for m in matrix_list])
            matrix_list = [M[slice(*sl)] for sl in zip(s[:-1],s[1:])]
        self.i_slice = slice(self.i_slice.start, self.i_slice.start+self.nno)
        return matrix_list


class ChainedNonlinEquations(NonlinEquations):

    def create(self, eq, K, CZ, blocklist):
        self.subblocks = []
        Pn = np.arange(len(K))
        for sl in blocklist:
            p, nlin = NonlinEquations.create(eq, K, CZ, sl, False)
            self.subblocks.append(nlin)
            Pn = Pn[p]
        return Pn

    def make_input_trans(self, matrix_list, svd_prec):
        return matrix_list
        i = self.subblocks[0].p_slice.start
        j = self.subblocks[-1].p_slice.stop
        ll = [[] for m in matrix_list]
        if i:
            for l, m in zip(ll, matrix_list):
                l.append(m[0:i])
        for bl in self.subblocks:
            r = bl.make_input_trans([m[bl.p_slice] for m in matrix_list], svd_prec)
            for l, m in zip(ll, r):
                l.append(m)
        for l, m in zip(ll, matrix_list):
            if j < m.shape[0]:
                l.append(m[j:])
        return [np.concatenate(l, axis=0) for l in ll]

    def make_output_trans(self, matrix_list, svd_prec):
        return matrix_list
        F, C = matrix_list ##FIXME
        i = self.subblocks[0].i_slice.start
        j = self.subblocks[-1].i_slice.stop
        l_F = []
        l_C = []
        if i:
            l_F.append(F[:,0:i])
            l_C.append(C[:,0:i])
        for bl in self.subblocks:
            Fs, Cs = bl.make_output_trans((F[:,bl.i_slice], C[:,bl.i_slice]), svd_prec)
            l_F.append(Fs)
            l_C.append(Cs)
        if j < F.shape[0]:
            l_F.append(F[:,j:])
            l_C.append(C[:,j:])
        return np.concatenate(l_F, axis=1), np.concatenate(l_C, axis=1)


class PartitionedNonlinEquations(NonlinEquations):

    def create(self, eq, K, CZ, blocklist):
        self.cc_slice = slice(blocklist[-1].stop, self.v_slice.stop)
        self.subblocks = []
        Pn = np.arange(len(K))
        for sl in blocklist:
            p, nlin = NonlinEquations.create(eq, K, CZ, sl, False)
            self.subblocks.append(nlin)
            Pn = Pn[p]
        return Pn

    def make_input_trans(self, matrix_list, svd_prec):
        return matrix_list

    def make_output_trans(self, matrix_list, svd_prec):
        return matrix_list

    def decompose_blocks(self, F, C):
        if False: ##FIXME make configurable
            return matrix_list
        Kni = ml.identity(self.nn)
        end = self.subblocks[-1].v_slice.stop
        self.Kl = self.eq.K[end:, :].copy()
        for bl in self.subblocks:
            sl = bl.v_slice
            U, V, Vi = self.decompose(self.eq.K[end:, sl])
            self.Kl[:,sl] = U
            #self.Mi[sl,sl] = V
            bl.Mi = V
            Kni[sl,sl] = Vi
        return F * Kni, C * Kni


class EquationSystem(object):

    def __init__(self, parser, jacobi_par=None, partition=False, svd_prec=None):
        self.parser = parser
        self.jacobi_par = jacobi_par
        self.svd_prec = svd_prec

        self.nx, self.nn, self.ni, self.no, self.np = [len(parser.element_name[j]) for j in 'X', 'N', 'I', 'O', 'P']
        self.nlin_elements = np.array(parser.element_name["N"])
        self.Nxl, self.Nxr, self.Nnl, self.Nnr, self.No, self.Nv, self.I = [
            parser.N[j] for j in "Xl", "Xr", "Nl", "Nr", "O", "P", "I"]
        self.CV = parser.ConstVoltages
        m = parser.mm
        self.f = parser.get_nonlin_funcs()
        self.CZ = parser.CZ
        if self.jacobi_par is not None:
            J, Jc, select, unselect = self.jacobi_par
            self.S = parser.S - self.Nnr[unselect].T * J[unselect][:,unselect] * self.Nnl[unselect]
            self.CV = self.CV + (Nnr[unselect].T * Jc[unselect]).T
            self.Nnr = self.Nnr[select]
            self.Nnl = self.Nnl[select]
            self.nn = len(select)
            self.CZ = self.CZ[select]
            self.f = NonlinEquations.rebase_nonlinear_functions(self.f, select)
            parser.f = self.f
            parser.element_name["N"] = np.array(parser.element_name["N"])[select]
        else:
            self.S = parser.S
        self.Si = self.S.I

        if self.nn:
            K = (self.Nnl * self.Si * self.Nnr.T != 0)
            for j, (expr, vl, base) in enumerate(self.f):
                for i in base:
                    K[j, i] = True
            v_slice = slice(0, len(K))
            Pn, self.nonlin = NonlinEquations.create(self, K, self.CZ, v_slice, partition)
            self.apply_permutation(Pn)
        else:
            self.nonlin = None

        Z = ml.diag(parser.Z)
        self.Tx = m * Z * self.Nxl * self.Si
        self.A = self.Tx * self.Nxr.T - (Z if parser.TR else ml.diag((parser.Z - 1) / 2.0))
        self.B = self.Tx * self.I.T
        self.Bc = self.Tx * self.CV.T
        self.C = self.Tx * self.Nnr.T

        self.To = self.No * self.Si
        self.D = self.To * self.Nxr.T
        self.E = self.To * self.I.T
        self.Ec = self.To * self.CV.T
        self.F = self.To * self.Nnr.T

        self.Tn = self.Nnl * self.Si
        self.G = self.Tn * self.Nxr.T
        self.H = self.Tn * self.I.T
        self.Hc = self.Tn * self.CV.T
        self.K = self.Tn * self.Nnr.T

        if self.nn:
            self.nonlin.Hc = self.Hc
            self.G, self.H = self.nonlin.make_input_trans((self.G, self.H), svd_prec)
            self.F, self.C = self.nonlin.make_output_trans((self.F, self.C), svd_prec)

        if self.np:
            # Woodbury Identity: \left(A+UCV \right)^{-1} = A^{-1} - A^{-1}U \left(C^{-1}+VA^{-1}U \right)^{-1} VA^{-1}, 
            self.Twl = self.Si * self.Nv.T
            self.Q = self.Nv * self.Twl
            self.Uxl = m * Z * self.Nxl * self.Twl
            self.Uo = self.No * self.Twl
            self.Unl = self.Nnl * self.Twl
            self.Twr = self.Si.T * self.Nv.T
            self.Uxr = self.Nxr * self.Twr
            self.Uu = self.I * self.Twr
            self.Ucv = self.CV * self.Twr
            self.Unr = self.Nnr * self.Twr

        self.mp_cols = self.nx + self.ni

    def apply_permutation(self, Pn):
        self.nlin_elements = self.nlin_elements[Pn]
        self.CZ = self.CZ[Pn]
        self.f = NonlinEquations.rebase_nonlinear_functions(self.f, Pn)
        self.Nnl = self.Nnl[Pn]
        self.Nnr = self.Nnr[Pn]

    def transform_state(self, Ts, Tsi):
        self.A = Tsi * self.A * Ts
        self.B = Tsi * self.B
        self.Bc = Tsi * self.Bc
        self.C = Tsi * self.C
        self.D = self.D * Ts
        self.G = self.G * Ts
        self.nx = self.A.shape[0]
        self.mp_cols = self.nx + self.ni
        if self.np:
            self.Uxl = Tsi * self.Uxl
            self.Uxr = Ts.T * self.Uxr

    def get_parser(self):
        return self.parser

    def get_Mo(self):
        return np.concatenate((self.D, self.E, self.F), axis=1)

    def get_Mx(self):
        return np.concatenate((self.A, self.B, self.C), axis=1)

    def get_Mp(self):
        return np.concatenate((self.G, self.H), axis=1)

    def get_UR(self):
        assert hasattr(self, "Q")
        return np.concatenate((self.Uxr.T, self.Uu.T, self.Unr.T), axis=1)

    def get_mx_cols(self):
        return self.A.shape[1] + self.B.shape[1] + self.C.shape[1]

    def get_mp_cols(self):
        return self.G.shape[1] + self.H.shape[1]

    def get_npl(self):
        return len(self.parser.pot_list)

    def get_status(self):
        return "nx=%d, nni=%d, nn=%d, nno=%d, ni=%d, no=%d, np=%d" % (self.nx, self.nni, self.nn, self.nno, self.ni, self.no, self.np)


class Simulate(object):

    def __init__(self, eq, solver):
        self.eq = eq
        self.parser = eq.get_parser()
        if solver is None:
            self.solver_dict = dict()
        elif isinstance(solver, basestring):
            self.solver_dict = dict(method = solver)
        else:
            self.solver_dict = dict(solver)
        self.solver_method = self.solver_dict.get("method", 'hybr')
        self.max_homotopy_iter = self.solver_dict.get("max_homotopy_iter", 1000)
        try:
            del self.solver_dict["max_homotopy_iter"]
        except KeyError:
            pass
        try:
            del self.solver_dict["method"]
        except KeyError:
            pass

    def get_solver(self):
        d = self.solver_dict.copy()
        d["method"] = self.solver_method
        d["max_homotopy_iter"] = self.max_homotopy_iter
        return d

    def get_eq(self):
        return self.eq

    def get_parser(self):
        return self.parser


class SimulatePy(Simulate):

    def __init__(self, eq, solver=None, dc_method="A"):
        Simulate.__init__(self, eq, solver)
        self.dc_method = dc_method
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
        self.calc_dc(parser.op, method=dc_method)

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
            return (eq.A - Tx * eq.Uxr.T,
                    eq.B - Tx * eq.Uu.T,
                    eq.Bc - Tx * eq.Ucv.T,
                    eq.C - Tx * eq.Unr.T,
                    eq.D - To * eq.Uxr.T,
                    eq.E - To * eq.Uu.T,
                    eq.Ec - To * eq.Ucv.T,
                    eq.F - To * eq.Unr.T,
                    eq.G - Tn * eq.Uxr.T,
                    eq.H - Tn * eq.Uu.T,
                    eq.Hc - Tn * eq.Ucv.T,
                    eq.K - Tn * eq.Unr.T,
                    )
        else:
            return (eq.A, eq.B, eq.Bc, eq.C,
                    eq.D, eq.E, eq.Ec, eq.F,
                    eq.G, eq.H, eq.Hc, eq.K,
                    )

    def calc_linear_sys_matrices(self, v0=None):
        eq = self.eq
        if eq.nn:
            nonlin = eq.nonlin
            J = self.jacobi(v0)
            X = nonlin.Mi * (np.diag(eq.CZ) - J * eq.K).I * J * nonlin.U
            # equivalent formula for X:
            # X = nonlin.Mi * J * (np.diag(eq.CZ) - eq.K * J).I * nonlin.U
            A = eq.A + eq.C * X * eq.G
            B = eq.B + eq.C * X * eq.H
            D = eq.D + eq.F * X * eq.G
            return A, B, D
        else:
            return eq.A, eq.B, eq.D

    def balance_realization(self, tol=None):
        if self.eq.np:
            return
        A, B, D = self.calc_linear_sys_matrices()
        T, Ti, hsv = get_state_transform(A, B, D, tol=tol)
        #print tol, T.shape, hsv
        self.eq.transform_state(T, Ti)
        self.calc_dc(self.eq.parser.op, method=self.dc_method)

    def solve(self, func, v0, args=(), method='hybr', options=None):
        try:
            with warnings.catch_warnings():
                warnings.filterwarnings(action="error")
                res = opt.root(func, v0, args=args, method=method, options=options)
        except RuntimeWarning as e:
            raise ConvergenceError(e)
        else:
            if not res.success:
                raise ConvergenceError(res.message)
        return res

    def solve_using_homotopy(self, func, v0, method='hybr', options=None):
        # use homotopy
        points = [0, 1]
        max_iter = 1000
        for tries in range(max_iter):
            try:
                res = self.solve(func, v0, args=(points[1],), method=method, options=options)
            except ConvergenceError as e:
                msg = e
                points.insert(1, (points[0]+points[1])/2)
                continue
            if len(points) == 2:
                return res
            v0 = res.x
            points = points[1:]
        raise ConvergenceError("more than %d iterations (list msg: %s)" % (max_iter, msg))

    def calc_dc(self, u, method="A"):
        u = ml.matrix(u, dtype=np.float64).T
        A, B, Bc, C, D, E, Ec, F, G, H, Hc, K = self.calc_matrixes()
        if A.size == 0:
            if len(self.eq.f):
                p = self.eq.nonlin.U * H * u
                def func(v, fact):
                    return (p + Hc * fact + K * self.calc_i(v) - ml.matrix(self.eq.CZ * v).T).A1
                self.v0 = self.solve_using_homotopy(func, self.v0).x
        else:
            I = ml.eye(len(A))
            if method == "A":
                try:
                    Ai = (I - A).I
                except la.LinAlgError:
                    method = "N"
            if method == "N":
                G1 = ml.append(self.eq.nonlin.U * G, A, axis=0)
                H1 = ml.append(self.eq.nonlin.U * H, B, axis=0)
                Hc1 = ml.append(Hc, Bc, axis=0)
                K1 = ml.append(K, C * self.eq.nonlin.Mi, axis=0)
                CZ1 = np.append(self.eq.CZ, np.ones(len(self.x)))
                n = len(self.v0)
                def func(v, fact):
                    return (G1 * ml.matrix(v[n:]).T + H1 * u + Hc1*fact + K1 * self.calc_i(v) - ml.matrix(CZ1 * v).T).A1
                res = self.solve_using_homotopy(func, np.append(self.v0, self.x))
                self.v0 = res.x[:n]
                self.x = res.x[n:]
            else:
                self.x = matrix_add(Ai * B * u, Ai * Bc)
                if K.size != 0:
                    T = self.eq.nonlin.U * G * Ai
                    p = matrix_add(T * B * u, self.eq.nonlin.U * H * u)
                    Hc1 = matrix_add(T * Bc, Hc)
                    KK = T * C * self.eq.nonlin.Mi + K
                    def func(v, fact):
                        return (p + Hc1 * fact + KK * self.calc_i(v) - ml.matrix(self.eq.CZ * v).T).A1
                    self.v0 = self.solve_using_homotopy(func, self.v0).x
                    self.x += Ai * C * self.eq.nonlin.Mi * self.calc_i(self.v0)
                self.x = self.x.A1
        self.v00 = self.v0.copy()
        self.x0 = self.x.copy()
        self.p0 = matrix_add(G * np.matrix(self.x0).T, H * np.matrix(self.op).T)
        if self.eq.nonlin:
            self.o0 = matrix_add(D * np.matrix(self.x0).T, E * np.matrix(self.op).T, Ec, F * self.eq.nonlin.Mi * self.calc_i(self.v0)).A1
            self.last_p = self.eq.nonlin.U * self.p0 + Hc
        else:
            self.o0 = matrix_add(D * np.matrix(self.x0).T, E * np.matrix(self.op).T, Ec).A1

    def calc_i(self, v):
        i = ml.zeros(len(self.ff)).T
        for n, (f, base) in enumerate(self.ff):
            i[n] = f(*v[base])
        return i

    def solve_one(self, p, K, s, sm=None, sd=None):
        if sm is None:
            sm = self.solver_method
        if sd is None:
            sd = self.solver_dict
        i = ml.zeros((p.shape[0],1))
        vv = self.v0.copy()
        def func(v):
            for n, (f, base) in enumerate(self.ff[s]):
                ##FIXME
                vv[s] = v
                i[n] = f(*vv[base])
            return (p + K * i - ml.matrix(v).T).A1
        self.v0[s] = self.solve(func, self.v0[s], method=sm, options=sd).x
        return i

    def nonlin_py(self, p, K, Hc):
        p = self.eq.nonlin.U * p + Hc
        i = ml.zeros((self.eq.nn, 1))
        if isinstance(self.eq.nonlin, PartitionedNonlinEquations):
            rc = slice(self.eq.blocklist[-1].stop, None)
            #sm = ["hybr", "lm", "hybr"]
            #sd = [dict(), dict(diag=(1e3,1),factor=1e-1), dict()]
            #sm = ["lm", "lm", "lm"]
            #sd = [dict(diag=(1e3,1),factor=1e-1), dict(diag=(1e3,1),factor=1e-1), dict(diag=(1e3,1),factor=1e-1)]
            sm = [None,None,None]
            sd = [None,None,None]
            def func(icc, fact):
                #print "*", fact, icc
                p1 = self.last_p + (p - self.last_p) * fact
                for j, s in enumerate(self.eq.blocklist):
                    k = K[s]
                    try:
                        i[s] = self.eq.Kn[j] * self.solve_one(p1[s]+k[:,rc].dot(icc).T, k[:,s], s, sm[j], sd[j])
                    except ConvergenceError as e:
                        print "conv error in %d: %s" % (j, e)
                        raise
                        #raise SystemExit
                i[rc] = icc.reshape(len(icc), 1)
                return (p1[rc] + self.eq.Kl * i).A1
            self.v0[rc] = self.solve_using_homotopy(func, self.v0[rc], method=self.solver_method, options=self.solver_dict).x
        elif isinstance(self.eq.nonlin, ChainedNonlinEquations):
            for j, s in enumerate(self.eq.nonlin.blocklist):
                pp = p[s]
                if s.start:
                    pp += K[s][:,:s.start] * i[:s.start]
                i[s] = self.solve_one(pp, K[s][:,s], s)
            i = self.eq.nonlin.Mi * i
        else:
            def func(v, fact):
                i[:] = self.calc_i(v)
                p1 = self.last_p + (p - self.last_p) * fact
                return (p1 + K * i - ml.matrix(self.eq.CZ * v).T).A1
            self.v0 = self.solve_using_homotopy(func, self.v0, method=self.solver_method, options=self.solver_dict).x
            i = self.eq.nonlin.Mi * i
        self.last_p = p
        return i

    def compile_py_func(self):
        self.ff = np.zeros(len(self.eq.f), dtype=object)
        if not self.eq.nn:
            # model is linearized
            return
        for j, (expr, vl, base) in enumerate(self.eq.f):
            self.ff[j] = (sp.lambdify(vl, expr), base)

    def calc_di(self, v, j):
        i = np.zeros(len(self.eq.f))
        for n, (f, vl, base) in enumerate(self.eq.f):
            for k, var in zip(base, vl):
                if k == j:
                    s = dict([(sym,val) for sym, val in zip(vl, v[base])])
                    i[n] = f.diff(var).subs(s)
                    break
            else:
                i[n] = 0.
        return i

    def jacobi_numeric(self, v0=None):
        if v0 is None:
            v0 = self.v00
        J = np.zeros((len(self.eq.f), len(v0)))
        i0 = self.calc_i(v0).A1
        eps = 1e-4
        for j in range(len(v0)):
            v = v0.copy()
            v[j] += eps
            J[:, j] = (self.calc_i(v).A1 - i0) / eps
        return ml.matrix(J)

    def jacobi_symbolic(self, v0=None):
        if v0 is None:
            v0 = self.v00
        J = np.zeros((len(self.eq.f), len(v0)))
        for j in range(len(v0)):
            J[:, j] = self.calc_di(v0, j)
        return ml.matrix(J)

    jacobi = jacobi_symbolic
    #jacobi = jacobi_numeric

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
                except ConvergenceError as e:
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
    def overwrite(self, n, v):
        return dict.__setitem__(self, n, v)


class PluginDef(object):

    def __init__(self, id):
        self._id = id
        self._name = id
        self._description = None
        self._category = "External"
        self._shortname = None
        self._namespace = id

    @staticmethod
    def _lfmt(s):
        if s is None:
            return 0
        if not s:
            return '""'
        return 'N_("%s")' % s

    @property
    def id(self):
        return self._id
    @id.setter
    def id(self, v):
        self._id = v

    @property
    def namespace(self):
        return self._namespace
    @namespace.setter
    def namespace(self, v):
        self._namespace = v

    @property
    def name(self):
        return self._name
    @name.setter
    def name(self, v):
        self._name = v

    @property
    def description(self):
        return self._description or ""
    @description.setter
    def description(self, v):
        self._description = v

    @property
    def category(self):
        return self._category
    @category.setter
    def category(self, v):
        self._category = v

    @property
    def shortname(self):
        return self._shortname or ""
    @shortname.setter
    def shortname(self, v):
        self._shortname = v

    @property
    def s_id(self):
        return '"%s"' % self._id

    @property
    def l_name(self):
        return self._lfmt(self._name)

    @property
    def l_description(self):
        return self._lfmt(self._description)

    @property
    def l_category(self):
        return self._lfmt(self._category)

    @property
    def l_shortname(self):
        return self._lfmt(self._shortname)


class BuildCModule(Simulate):

    def __init__(self, name, sim, solver=None, c_tempdir=None, c_verbose=False,
                 c_real="double", extra_sources=None, linearize=False, pre_filter=None,
                 post_filter=None, generator=None):
        if solver is None:
            solver = sim.get_solver()
        Simulate.__init__(self, sim.get_eq(), solver)
        self.name = name
        self.c_tempdir = c_tempdir
        self.c_verbose = c_verbose
        self.c_real = c_real
        self.extra_sources = extra_sources
        self.pre_filter = pre_filter
        self.post_filter = post_filter
        if generator is None:
            generator = generate_code.CodeGenerator
        self.generator = generator
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
        self.v0, self.x0, self.p0, self.o0 = sim.v0, sim.x0, sim.p0, sim.o0
        self.op = parser.op
        self.pot_func = parser.get_pot_funcs()
        self.pot = parser.pot
        self.Pv = parser.Pv
        self.pot_attr = parser.get_pot_attr()
        self.out_labels = parser.out_labels()
        self.fs = parser.fs
        self.max_homotopy_iter = 64000
        self.resample = False
        self.solver_params = None
        self.dev_interface = True
        self.build_script = None
        self.plugindef = PluginDef(name)

    def get_executor(self):
        return self.compile_c_func().wrap_code()

    def compile_c_func(self):
        eq = self.eq
        d = CheckedDict(name=self.name, comment=time.ctime())
        d["solver_maptype"] = "unsigned short" ##FIXME
        d["max_homotopy_iter"] = self.max_homotopy_iter
        d["fs"] = self.fs
        d["resample"] = self.resample
        d["c_real"] = self.c_real
        for j in "nx", "nn", "ni", "no", "np", "mp_cols":
            d[j] = getattr(eq, j)
        for j in "nni", "nno":
            d[j] = getattr(eq.nonlin, j, 0)
        d["npl"] = self.eq.get_npl()
        d["v0_data"] = ",".join([str(j) for j in self.v0])
        d["x0_data"] = ",".join([str(j) for j in self.x0])
        d["p0_data"] = ",".join([str(j) for j in self.p0.A1])
        d["o0_data"] = ",".join([str(j) for j in self.o0])
        d["op_data"] = ",".join([str(j) for j in self.op])
        d["out_labels"] = ",".join(['"%s"' % j for j in self.out_labels])
        d["method"] = method = "linear" if eq.nn == 0 else self.solver_method
        pot_list = self.eq.get_parser().pot_list
        d["pot_vars"] = ",".join(['"%s"' % v for v in pot_list])
        d["pot"] = ",".join([str(self.pot.get(v,0.5)) for v in pot_list])
        d["pre_filter"] = self.pre_filter or ""
        d["post_filter"] = self.post_filter or ""
        d['id'] = d["name"]
        d['plugindef'] = self.plugindef
        d['build_script'] = self.build_script
        d["dev_interface"] = self.dev_interface
        solver = self.solver_dict.copy()
        solver["method"] = method
        if method == "table":
            d["extra_sources"] = self.extra_sources
        else:
            d["extra_sources"] = ""
        cg = self.generator(
            self.eq, solver, self.solver_params, self.pot, pot_list,
            self.pot_func, self.pot_attr, self.Pv, self.extra_sources
            ).generate(d)
        return CodeWrapper(d, cg, self.c_tempdir, self.c_verbose)


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
        t1 = time.time()
        try:
            return self.c_calc_stream(v_in)
        finally:
            self.time_per_sample = (time.time() - t1)/v_in.shape[0]
            self.v0, self.x, self.minmax, info, nfev, fnorm = self.c_get_info()

    def load_from_shared_lib(self):
        INTERFACE_VERSION = 3
        try:
            lib = ct.cdll.LoadLibrary(self.soname)
        except OSError as e:
            raise SystemExit(e)
        try:
            version = lib.get_interface_version()
        except AttributeError:
            raise SystemExit("%s: bad shared lib, missing get_interface_version" % self.soname)
        if version != INTERFACE_VERSION:
            raise SystemExit("interface version %d expected (found: %d)" % (INTERFACE_VERSION, version))
        c_char_pp = ct.POINTER(ct.c_char_p)
        c_get_structure = lib.get_structure
        c_get_structure.restype = None
        c_get_structure.argtypes = [c_char_pp, ct.POINTER(ct.c_int), ct.POINTER(ct.c_int), ct.POINTER(ct.POINTER(ct.c_int)),
                                    ct.POINTER(ct.POINTER(ct.c_int)), c_char_pp, ct.POINTER(c_char_pp),
                                    ct.POINTER(ct.POINTER(ct.c_double)), ct.POINTER(c_char_pp), c_char_pp]
        nm = ct.c_char_p()
        sz = ct.c_int()
        fs = ct.c_int()
        t = ct.POINTER(ct.c_int)()
        tc = ct.POINTER(ct.c_int)()
        p = ct.c_char_p()
        plist = c_char_pp()
        pvals = ct.POINTER(ct.c_double)()
        ol = c_char_pp()
        cmt = ct.c_char_p()
        c_get_structure(ct.byref(nm), ct.byref(sz), ct.byref(fs), ct.byref(t), ct.byref(tc), ct.byref(p),
                        ct.byref(plist), ct.byref(pvals), ct.byref(ol), ct.byref(cmt))
        nx, ni, no, npl, nn, nni, nno, nc, end = [t[i] for i in range(9)]
        if end != -1:
            raise SystemExit("%s: bad sequence length in get_structure")
        self.nx, self.ni, self.no, self.npl, self.nn, self.nni, self.nno = nx, ni, no, npl, nn, nni, nno
        self.comp_sz = comp_sz = np.array([[tc[3*i+j] for j in range(3)] for i in range(nc)])
        self.name = nm.value
        self.data_size = sz.value
        self.fs = fs.value
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
        info = ct.c_int()
        nfev = ct.c_int()
        fnorm = c_real()
        if nn:
            c_calc_nonlin = lib.calc_nonlin
            c_calc_nonlin.restype = ct.c_int
            c_calc_nonlin.argtypes = [ct.c_int, c_mat(), c_mat(True), c_arr(nn, True), c_int_p, c_int_p, c_real_p]
            def calc_nonlin(p, v):
                assert p.shape[1] == nni+npl, (p.shape[1], nni+npl)
                p = np.array(p, dtype=self.dtp, order='C', copy=False)
                i = np.zeros((p.shape[0], nno), dtype=self.dtp, order='C')
                r = c_calc_nonlin(len(p), p, i, v, ct.byref(info), ct.byref(nfev), ct.byref(fnorm))
                if r != 0:
                    raise ValueError("convergence error: info=%d, nfev=%d, fnorm=%g" % (info.value, nfev.value, fnorm.value))
                return i
            self.c_calc_nonlin = calc_nonlin
            def define_func(f, nni, npl, nno):
                dtp = self.dtp
                def func(p, v=None):
                    assert p.shape[1] == nni+npl, (p.shape[1], nni+npl)
                    if v is None:
                        v = self.v0
                    p = np.array(p, dtype=dtp, order='C', copy=False)
                    i = np.zeros((p.shape[0], nno), dtype=dtp, order='C')
                    r = f(len(p), p, i, v, ct.byref(info), ct.byref(nfev), ct.byref(fnorm))
                    if r != 0:
                        raise ValueError("convergence error: info=%d, nfev=%d, fnorm=%g" % (info.value, nfev.value, fnorm.value))
                    return i
                return func
            self.c_calc_comp = []
            for i in range(nc):
                t = getattr(lib, "calc_nonlin_%d" % i)
                t.restype = ct.c_int
                t.argtypes = [ct.c_int, c_mat(), c_mat(True), c_arr(nn, True), c_int_p, c_int_p, c_real_p]
                self.c_calc_comp.append(define_func(t, comp_sz[i][1], npl, comp_sz[i][2]))
        c_calc_pot_update = lib.calc_inv_update
        c_calc_pot_update.restype = None
        c_calc_pot_update.argtypes = [c_arr(npl)]
        c_get_dc = lib.get_dc
        c_get_dc.restype = None
        c_get_dc.argtypes = [c_arr(nn, True), c_arr(nx, True), c_arr(nni, True), c_arr(no, True), c_arr(ni, True)]
        def calc(u, x, v):
            u = np.array(u, dtype=self.dtp)
            x = np.array(x, dtype=self.dtp)
            v = np.array(v, dtype=self.dtp)
            x_new = np.zeros(nx, dtype=self.dtp)
            o = np.zeros(no, dtype=self.dtp)
            if c_calc(u, x, v, x_new, o, ct.byref(info), ct.byref(nfev), ct.byref(fnorm)) < 0:
                if fnorm.value > 1e-7:
                    raise RuntimeError("convergence: method=%s, info=%d, nfev=%d, fnorm=%g"
                                       % (self.method, info.value, nfev.value, fnorm.value))
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
        self.CZ = np.ones(tc["N"], dtype=int)
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
        self.pot_list = []
        for a, f in self.pot_func:
            s = str(a)
            if s not in self.pot_list:
                self.pot_list.append(s)

    def get_status(self):
        return ""
        
    def matches(self, create_filter, symbolic):
        return self.create_filter == create_filter and self.symbolic == symbolic

    def get_nonlin_funcs(self):
        return self.f

    def set_function(self, idx, expr, vl, base):
        assert self.f[idx] is None
        self.f[idx] = (expr, vl, range(base, base+len(vl)))

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

    @staticmethod
    def format_element(el, pref=""):
        n, d = el
        return "%s%s%s" % (pref, n, d and ("[%s]" % d) or "")

    def node_names(self):
        return [self.format_element(v) for v in self.element_name["S"]+self.element_name["V"]]

    def out_labels(self):
        return [str(v) for v in self.element_name["O"][0][0].conn]

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
        ccode(d, 'fvec', sp.Matrix(p) + sp.Matrix(self.K) * sp.Matrix(l) - sp.Matrix(np.diag(self.eq.CZ)) * sp.Matrix(v))
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
