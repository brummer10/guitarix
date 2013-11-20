from __future__ import division
from collections import OrderedDict
import sympy as sp
import numpy as np
import numpy.matlib as ml
import dk_templates

class CodeGenerator(object):

    def __init__(self, d):
        self.d = d
        self.const_data_matrices = {}
        self.global_matrices = {}
        self.local_matrix_declaration = OrderedDict();

    @staticmethod
    def matrix_is_zero(m):
        return np.allclose(m, np.zeros_like(m))

    @staticmethod
    def matrix_is_identity(m):
        if m.shape[0] != m.shape[1]:
            return False
        return np.allclose(m, np.identity(m.shape[0]))

    @staticmethod
    def make_symbol_vector(s, n, idx="[%d]"):
        return sp.symbols(['%s%s' % (s, idx % i) for i in range(n)])

    @staticmethod
    def generate_matrix_declaration(name, rows, cols, prefix="", Map=None, const=False, datatype="creal"):
        if const:
            s = "const "
        else:
            s = ""
        if Map:
            return "%sMap<%sMatrix<%s, %d, %d> >%s(%s);" % (prefix, s, datatype, rows, cols, name, Map)
        else:
            return "%s%sMatrix<%s, %d, %d> %s;" % (prefix, s, datatype, rows, cols, name)

    def declare_local(self, name, rows, cols, Map=None, const=False, datatype="creal"):
        self.local_matrix_declaration[name] = (rows, cols, Map, const, datatype)

    def generate_local_declarations(self):
        l = []
        for name, (rows, cols, Map, const, datatype) in self.local_matrix_declaration.items():
            l.append(self.generate_matrix_declaration(name, rows, cols, Map=Map, const=const, datatype=datatype))
        self.local_matrix_declaration.clear()
        return "\n    ".join(l);

    def generate_global_matrices(self):
        l = []
        for name, shape in self.global_matrices.items():
            l.append(self.generate_matrix_declaration(name, shape[0], shape[1], "static "))
        self.d["global_matrices"] = "\n".join(l)

    def generate_const_data(self):
        templ = (
            "static const creal __attribute__((aligned(16))) %(data_name)s[%(rows)d*%(cols)d] = { %(data)s };\n"
            "static const Map<const Matrix<creal, %(rows)d, %(cols)d>, Aligned> %(matrix_name)s(%(data_name)s);\n\n"
            )
        l = []
        for name, mat in self.const_data_matrices.items():
            l.append(templ % dict(
                matrix_name = name,
                data_name = name.lower()+"_data",
                rows = mat.shape[0],
                cols = mat.shape[1],
                data = ",".join([sp.ccode(v) for v in mat.T]), # col-major order is eigen3 default
                ))
        self.d["const_matrices"] = "".join(l)

    def ccode(self, ret, ex, idx='[%d]'):
        """
        d: dictionary
        ret: name of variable
        ex: vector expression (iterable)
        idx: syntax for index access
        """
        ret += idx
        return "\n".join([sp.ccode(ee, ret % i) for i, ee in enumerate(ex)]).replace("\n","\n    ")


class NonlinSolverCodeGen(CodeGenerator):

    def __init__(self, d, func, K, Mp, Mpc, CZ, Mi, have_constant_matrices):
        CodeGenerator.__init__(self, d)
        assert isinstance(K, ml.matrix) and K.shape[0] == K.shape[1] and K.shape[0] > 0
        assert isinstance(Mp, ml.matrix) and Mp.shape[0] == K.shape[0]
        assert isinstance(Mpc, ml.matrix) and Mpc.shape[0] == Mp.shape[0] and Mpc.shape[1] == 1
        assert isinstance(func, np.ndarray) and func.ndim == 1 and func.shape[0] == K.shape[0]
        assert isinstance(Mi, ml.matrix) and Mi.shape[1] == K.shape[0]
        assert isinstance(CZ, np.ndarray) and CZ.ndim == 1 and CZ.shape[0] == K.shape[0]
        self.d = d
        self.func = func
        self.K = K
        self.Mp = Mp
        self.Mpc = Mpc
        self.CZ = CZ
        self.Mi = Mi
        self.have_constant_matrices = have_constant_matrices
        self.d["use_blocks"] = False
        self.d["block_off"] = 0
        self.g_nn = self.d["nn"]

    def access_matrix(self, name, value=None, const=None, block=""):
        if name in self.local_matrix_declaration:
            return "%s%s" % (name, block)
        if const is None:
            if value is None:
                const = False
            else:
                const = self.have_constant_matrices
        if const:
            if value is not None and name not in self.const_data_matrices:
                self.const_data_matrices[name] = sp.Matrix(value)
            return "%s%s" % (name, block)
        else:
            return "(*par.%s)%s" % (name, block)

    def blockV(self):
        return ""

    def blockM(self):
        return ""

    def blockE(self):
        return ""

    def blockR(self):
        return ""

    def expr_list(self, v):
        l = []
        for n, (expr, vl, base) in enumerate(self.func):
            for j, e in enumerate(vl):
                expr = expr.subs(e, v[base+j])
            l.append(expr)
        return l

    def get_v_list(self, v):
        return ['v[%d]' % i if self.CZ[i] else '0' for i in range(len(self.CZ))]

    def p_transform(self, fcn_p_list):
        par_p = self.access_matrix('p')
        need_p_var = False
        if not self.matrix_is_identity(self.Mp):
            s = "%s * %s" % (self.access_matrix('Mp', self.Mp, True), par_p)
            need_p_var = True
        else:
            s = self.access_matrix('p')
        if not self.matrix_is_zero(self.Mpc):
            s += " + %s" % self.access_matrix('Mpc', self.Mpc)
            need_p_var = True
        if need_p_var:
            self.declare_local("p2", self.g_nn, 1)
            fcn_p_list.append("p2")
            s = "p2 = %s;" % s
        else:
            fcn_p_list.append(s)
            s = ""
        return s

    def generate(self):
        nn = self.d["nn"]   # = self.K.shape[0]
        nni = self.d["nni"] # = self.Mp.shape[1]
        nno = self.d["nno"] # = self.Mi.shape[0]
        self.d["have_constant_matrices"] = self.have_constant_matrices

        # code for the nonlinear function to be solved:
        v = self.make_symbol_vector('v', self.g_nn)
        self.d['i'] = self.ccode(self.access_matrix('i', block=self.blockV()), self.expr_list(v), '(%d)')
        self.d['v_list'] = ", ".join(self.get_v_list(v))
        self.declare_local("mv", nn, 1)
        if not self.matrix_is_identity(self.K):
            self.d["equation"] = "Mfvec = %(p)s + %(K)s * %(i)s - %(mv)s;" % dict(
                p = self.access_matrix('p', block=self.blockV()),
                K = self.access_matrix('K', self.K, block=self.blockM()),
                i = self.access_matrix('i', block=self.blockV()),
                mv = self.access_matrix('mv'),
                )
        else:
            self.d["equation"] = "Mfvec = %(p)s + %(i)s - %(mv)s;" % dict(
                p = self.access_matrix('p', block=self.blockV()),
                i = self.access_matrix('i', block=self.blockV()),
                mv = self.access_matrix('mv'),
                )
        self.d["fcn_local_matrix_declaration"] = self.generate_local_declarations()

        self.d["v_block"] = self.blockV()

        # transformation of p
        fcn_p_list = []
        self.d['par_p'] = self.access_matrix('p', block=self.blockV())
        self.d["p_transform"] = self.p_transform(fcn_p_list)

        # transformation of i
        if not self.matrix_is_identity(self.Mi):
            self.declare_local("i2", self.Mi.shape[1], 1)
            self.d['i_transform'] = "%(i)s = %(Mi)s * %(i2)s;" % dict(
                i = self.access_matrix('i', block=self.blockV()),
                Mi = self.access_matrix('Mi', self.Mi, True),
                i2 = 'i2')
            fcn_p_list.append('i2')
        else:
            fcn_p_list.append(self.access_matrix('i'))
            self.d['i_transform'] = ""

        self.d["local_matrix_declaration"] = self.generate_local_declarations()

        if self.d["use_blocks"]:
            fcn_p_list.append(self.access_matrix('v'))
        if not self.have_constant_matrices:
            fcn_p_list.append(self.access_matrix('K', self.K))
        self.d["fcn_p_list"] = ",".join(["&%s" % v for v in fcn_p_list])

        self.generate_const_data()

        return self.d


class NonlinSolverCodeGenSF(NonlinSolverCodeGen):

    def __init__(self, d, func, K, Mp, Mpc, CZ, Mi, have_constant_matrices, kslice, kcc):
        NonlinSolverCodeGen.__init__(self, d, func, K, Mp, Mpc, CZ, Mi, have_constant_matrices)
        self.kslice = kslice
        self.kcc = kcc
        self.d["use_blocks"] = True
        self.d["block_off"] = self.kslice.start

    def blockV(self):
        return ".block<%d,%d>(%d,%d)" % (self.kslice.stop - self.kslice.start, 1, self.kslice.start, 0)

    def blockM(self):
        n = self.kslice.stop - self.kslice.start
        return ".block<%d,%d>(%d,%d)" % (n, n, self.kslice.start, self.kslice.start)

    def blockE(self):
        n = self.kslice.stop - self.kslice.start
        return ".block<%d,%d>(%d,%d)" % (n, self.kcc, self.kslice.start, self.g_nn - self.kcc)

    def blockR(self):
        return ".block<%d,%d>(%d,%d)" % (self.kcc, self.g_nn, self.g_nn - self.kcc, 0)

    def expr_list(self, v):
        l = []
        for n, (expr, vl, base) in enumerate(self.func[self.kslice]):
            for j, e in enumerate(vl):
                expr = expr.subs(e, v[base+j-self.kslice.start])
            l.append(expr)
        return l

    def get_v_list(self, v):
        return ['v[%d]' % i if self.CZ[i] else '0' for i in range(self.kslice.stop - self.kslice.start)]

    def p_transform(self, fcn_p_list):
        fcn_p_list.append(self.access_matrix('p'))
        return ""

    def generate(self):
        n = self.kslice.stop - self.kslice.start
        self.d["nn"] = n
        self.d["nni"] = n
        self.d["nno"] = n
        NonlinSolverCodeGen.generate(self)
        return self.d


class NonlinSolverCodeGenCC(NonlinSolverCodeGen):

    def __init__(self, d, func, K, Mp, Mpc, CZ, Mi, have_constant_matrices, blocklist):
        NonlinSolverCodeGen.__init__(self, d, func, K, Mp, Mpc, CZ, Mi, have_constant_matrices)
        self.blocklist = blocklist
        self.col = self.blocklist[-1].stop
        self.d["use_blocks"] = True
        self.d["block_off"] = self.col

    def blockV(self):
        return ".block<%d,1>(%d,0)" % (self.g_nn - self.col, self.col)

    def generate(self):
        n = self.g_nn - self.col
        self.d["nn"] = n
        self.d["nni"] = n
        self.d["nno"] = n
        NonlinSolverCodeGen.generate(self)
        self.d["nonlin_mat_list"] = self.d["fcn_p_list"] + ", par.Mp, par.Mpc"
        for d, sl in zip(self.d["blocklist"], self.blocklist):
            n = sl.stop - sl.start
            bv = ".block<%s,1>(%s,0)" % (n, sl.start)
            bm = ".block<%s,%s>(%s,%s)" % (n, n, sl.start, self.col)
            d["block"] = "%(p)s = (*pp)%(ppb)s + %(K)s * Mv;" % dict(
                p = self.access_matrix('p', block=bv),
                ppb = bv,
                K = self.access_matrix('K', block=bm),
                )
        bv = ".block<%s,1>(%s,0)" % (n, self.col)
        bm = ".block<%s,%s>(%s,%s)" % (n, self.g_nn, self.col, 0)
        self.d["equation"] = "Mfvec = (*pp)%(ppb)s + %(K)s * %(i)s;" % dict(
            ppb = bv,
            K = self.access_matrix('K', block=bm),
            i = self.access_matrix('i'))
        return self.d


class SimulationCodeGen(CodeGenerator):

    def __init__(self, d, pot_attr, Mp, Mx, Mxc, Mo, Moc, pot_func, Pv, pot_list, pot, Q, Uxl, Uo, Unl, UR, Ucv, Mpc, K):
        CodeGenerator.__init__(self, d)
        self.pot_attr = pot_attr
        self.Mp = Mp
        self.Mx = Mx
        self.Mxc = Mxc
        self.Mo = Mo
        self.Moc = Moc
        self.pot_func = pot_func
        self.Pv = Pv
        self.pot_list = pot_list
        self.pot = pot
        self.Q = Q
        self.Uxl = Uxl
        self.Uo = Uo
        self.Unl = Unl
        self.UR = UR
        self.Ucv = Ucv
        self.Mpc = Mpc
        self.K = K
        self.have_constant_matrices = len(pot_func) == 0

    def access_matrix(self, name, value=None, const=None):
        if const is None:
            if value is None:
                const = False
            else:
                const = self.have_constant_matrices
        if const:
            if name not in self.const_data_matrices:
                self.const_data_matrices[name] = sp.Matrix(value)
            return name
        else:
            self.global_matrices[name] = value.shape
            return name

    def gen_linear_combination(self, resname, varname, mult, mult_data, add=None, add_data=None, cast=None):
        if mult_data.shape[0] == 0:
            if add is None or add_data.shape[0] == 0:
                return ""
            else:
                e = "%s" % self.access_matrix(add, add_data)
        else:
            if not self.matrix_is_identity(mult_data):
                e = "%s * %s" % (self.access_matrix(mult, mult_data), varname)
            else:
                e = "%s" % varname
            if add is not None and not self.matrix_is_zero(add_data):
                e += " + %s" % self.access_matrix(add, add_data)
        if cast is not None:
            e = "(%s).cast<%s>()" % (e, cast)
        return "%s = %s;" % (resname, e)

    def trans_line(self, res, var, var_data, t, u, u_data):
        s = "%s = %s" % (
            self.access_matrix(res, var_data, False),
            self.access_matrix(var, var_data, True),
            )
        if t is None:
            return s + ";"
        return s + " - %s * %s;" % (
            t,
            self.access_matrix(u, u_data, True) if u_data is not None else u,
            )

    def generate(self):
        if self.pot_attr:
            self.d['have_master_slider'] = True
            self.d['master_slider_id'] = self.pot_attr[0][0]
        else:
            self.d['have_master_slider'] = False
        self.d['knob_ids'] = [t[0] for t in self.pot_attr]
        self.d['id'] = self.d["name"]
        self.d['timecst'] = 0.01
        self.d['regs'] = [dict(id=vv[0],name=vv[1],desc="",varidx=i) for i, vv in enumerate(self.pot_attr)]
        ll = []
        for i, (var, name, loga, inv, expr) in enumerate(self.pot_attr):
            if loga and inv:
                ss = "t[%d] = (exp(%s * (1-self.pots[%d])) - 1) / (exp(%s) - 1);" % (i, loga, i, loga)
            elif loga:
                ss = "t[%d] = (exp(%s * self.pots[%d]) - 1) / (exp(%s) - 1);" % (i, loga, i, loga)
            else:
                ss = "t[%d] = self.pots[%d];" % (i, i)
            ll.append(ss)
        s = 0.993;
        self.d['calc_pots'] = "\n    ".join(ll)
        self.d["gen_mp"] = self.gen_linear_combination('mp', 'dp', 'Mp', self.Mp)
        #mp_cols = self.d["mp_cols"] # = self.Mp.shape[1]
        self.d["gen_xn"] = self.gen_linear_combination('xn', 'd', 'Mx', self.Mx, 'Mxc', self.Mxc)
        self.d["m_cols"] = m_cols = self.Mx.shape[1]
        self.d["gen_xo"] = self.gen_linear_combination('xo', 'd', 'Mo', self.Mo, 'Moc', self.Moc)
        self.d["gen_xo_float"] = self.gen_linear_combination('xo', 'd', 'Mo', self.Mo, 'Moc', self.Moc, cast="float")

        #self.d["np"] = np = len(self.pot_func)
        nonlin_mat_list = ""
        if "solver" in self.d and "blocklist" in self.d["solver"]:
            nonlin_mat_list += ", &Mv"
        if self.have_constant_matrices:
            self.d["update_pot"] = ""
            #self.d["npl"] = 0
            self.d["pot_vars"] = ""
            self.d["pot"] = ""
        else:
            nonlin_mat_list += ", &K, &Mp, &Mpc"
            pot = self.make_symbol_vector('pot', self.d['np'])
            l = []
            for (a, f), p in zip(self.pot_func, self.Pv):
                s = str(a)
                try:
                    i = self.pot_list.index(s)
                except ValueError:
                    self.pot_list.append(s)
                    i = len(self.pot_list)-1
                expr = f.subs(a, pot[i]) * p
                l.append(expr)
            self.d["pot_vars"] = ",".join(['"%s"' % v for v in self.pot_list])
            self.d["pot"] = ",".join([str(self.pot.get(v,0.5)) for v in self.pot_list])
            #self.d["npl"] = npl = len(self.pot_list)
            nx = self.d["nx"]
            no = self.d["no"]
            np = self.d["np"]
            nn = self.d["nn"]
            self.declare_local("Rv", np, 1)
            lines = []
            lines.append(self.ccode('Rv', l, '(%d)'))
            self.declare_local("Qi", np, np)
            lines.append("Qi = (%s + Matrix<creal, %d, %d>(Rv.asDiagonal())).inverse();" % (self.access_matrix('Q',self.Q, True), np, np))
            if self.matrix_is_identity(self.Uxl):
                t = "Qi"
            elif self.matrix_is_zero(self.Uxl):
                t = None
            else:
                self.declare_local("Tx", nx, np)
                lines.append("Tx = %s * Qi;" % self.access_matrix('Uxl', self.Uxl, True))
                t = "Tx"
            lines.append(self.trans_line('Mx', 'Mx0', self.Mx, t, 'UR', self.UR))
            lines.append(self.trans_line('Mxc', 'Mxc0', self.Mxc, t, 'Ucv', self.Ucv))
            if self.matrix_is_identity(self.Uo):
                t  = "Qi"
            elif self.matrix_is_zero(self.Uo):
                t = None
            else:
                self.declare_local("To", no, np)
                lines.append("To = %s * Qi;" % self.access_matrix('Uo', self.Uo, True))
                t = "To"
            lines.append(self.trans_line('Mo', 'Mo0', self.Mo, t, 'UR', self.UR))
            lines.append(self.trans_line('Moc', 'Moc0', self.Moc, t, 'Ucv', self.Ucv))
            if self.matrix_is_identity(self.Unl):
                t = "Qi"
            elif  self.matrix_is_zero(self.Unl):
                t = None
            else:
                self.declare_local("Tp", nn, np)
                lines.append("Tp = %s * Qi;" % self.access_matrix('Unl', self.Unl, True))
                t = "Tp"
            lines.append(self.trans_line('Mp', 'Mp0', self.Mp, t, 'UR.block<%(np)d, %(mp_cols)d>(0, 0)' % self.d, None))
            lines.append(self.trans_line('Mpc', 'Mpc0', self.Mpc, t, 'Ucv', self.Ucv))
            lines.append(self.trans_line('K', 'K0', self.K, t, 'UR.block<%(np)d, %(m_cols)d-%(mp_cols)d>(0, %(mp_cols)d)' % self.d, None))
            self.d["update_pot"] = self.generate_local_declarations()+"\n"+"\n    ".join(lines)
        self.d["nonlin_mat_list"] = nonlin_mat_list
        self.generate_global_matrices()
        self.generate_const_data()
        return self.d
