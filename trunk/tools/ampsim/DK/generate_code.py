from __future__ import division
import sympy as sp
import numpy as np
import numpy.matlib as ml
from dk_templates import c_template_struct_const, c_template_struct

class CodeGenerator(object):

    def __init__(self, d):
        self.d = d
        self.const_data_matrices = {}
        self.global_matrices = {}

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
    def generate_matrix_declaration(name, rows, cols):
        return "Matrix<creal, %d, %d> %s;" % (rows, cols, name)

    def generate_global_matrices(self):
        templ = "static Matrix<creal, %(rows)d, %(cols)d> %(matrix_name)s;"
        l = []
        for name, shape in self.global_matrices.items():
            l.append("static " + self.generate_matrix_declaration(name, shape[0], shape[1]))
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
            return "par.%s" % name

    def generate(self):
        self.d["nn"] = nn = self.K.shape[0]
        self.d["nni"] = nni = self.Mp.shape[1]
        self.d["nno"] = nno = self.Mi.shape[0]
        self.d["have_constant_matrices"] = int(self.have_constant_matrices)
        self.d["struct_decl"] = (c_template_struct_const if self.have_constant_matrices else c_template_struct) % self.d

        # code for the nonlinear function to be solved:
        v = self.make_symbol_vector('v', nn)
        l = []
        for n, (expr, vl, base) in enumerate(self.func):
            for j, e in enumerate(vl):
                expr = expr.subs(e, v[base+j])
            l.append(expr)
        self.d['i'] = self.ccode(self.access_matrix('i'), l, '(%d)')
        self.d['v_list'] = ", ".join(['v[%d]' % i if self.CZ[i] else '0' for i in range(len(self.CZ))])
        if not self.matrix_is_identity(self.K):
            self.d["equation"] = "Mfvec = %(p)s + %(K)s * %(i)s - Mv;" % dict(
                p = self.access_matrix('p'),
                K = self.access_matrix('K', self.K),
                i = self.access_matrix('i'),
                )
        else:
            self.d["equation"] = "Mfvec = %(p)s + %(i)s - Mv;" % dict(
                p = self.access_matrix('p'),
                i = self.access_matrix('i'),
                )

        local_matrix_declaration = [];

        # transformation of p
        need_p_var = False
        if not self.matrix_is_identity(self.Mp):
            s = "%s * %s" % (self.access_matrix('Mp', self.Mp, True), self.access_matrix('p'))
            need_p_var = True
        else:
            s = self.access_matrix('p')
        if not self.matrix_is_zero(self.Mpc):
            s += " + %s" % self.access_matrix('Mpc', self.Mpc)
            need_p_var = True
        if need_p_var:
            fcn_p_list = ["p2"]
            local_matrix_declaration.append(self.generate_matrix_declaration("p2", self.Mp.shape[0], 1))
            s = "p2 = " + s + ";"
        else:
            fcn_p_list = [s]
            s = ""
        self.d["p_transform"] = s

        # transformation of i
        if not self.matrix_is_identity(self.Mi):
            local_matrix_declaration.append(self.generate_matrix_declaration("i2", self.Mi.shape[1], 1))
            self.d['i_transform'] = "%(i)s = %(Mi)s * %(i2)s;" % dict(
                i = self.access_matrix('i'),
                Mi = self.access_matrix('Mi', self.Mi, True),
                i2 = 'i2')
            fcn_p_list.append('i2')
        else:
            fcn_p_list.append(self.access_matrix('i'))
            self.d['i_transform'] = ""

        if not self.have_constant_matrices:
            fcn_p_list.append(self.access_matrix('K'))
        self.d["fcn_p_list"] = ",".join(fcn_p_list)

        self.d["local_matrix_declaration"] = "\n    ".join(local_matrix_declaration)
        self.generate_const_data()
        return self.d

class SimulationCodeGen(CodeGenerator):

    def __init__(self, d, Mp, Mx, Mxc, Mo, Moc, pot_func, Pv, pot_list, pot, Q, Uxl, Uo, Unl, UR, Ucv, Mpc, K):
        CodeGenerator.__init__(self, d)
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

    def gen_linear_combination(self, resname, varname, mult, mult_data, add=None, add_data=None):
        if mult_data.shape[0] == 0:
            if add is None or add_data.shape[0] == 0:
                return ""
            else:
                return "%s = %s;" % (resname, self.access_matrix(add, add_data))
        if not self.matrix_is_identity(mult_data):
            s = "%s = %s * %s" % (resname, self.access_matrix(mult, mult_data), varname)
        else:
            s = "%s = %s" % (resname, varname)
        if add is not None and not self.matrix_is_zero(add_data):
            s += " + %s;" % self.access_matrix(add, add_data)
        else:
            s += ";"
        return s

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
        self.d["gen_mp"] = self.gen_linear_combination('mp', 'dp', 'Mp', self.Mp)
        self.d["mp_cols"] = mp_cols = self.Mp.shape[1]
        self.d["gen_xn"] = self.gen_linear_combination('xn', 'd', 'Mx', self.Mx, 'Mxc', self.Mxc)
        self.d["m_cols"] = m_cols = self.Mx.shape[1]
        self.d["gen_xo"] = self.gen_linear_combination('xo', 'd', 'Mo', self.Mo, 'Moc', self.Moc)

        self.d["np"] = np = len(self.pot_func)
        if self.have_constant_matrices:
            self.d["update_pot"] = ""
            self.d["npl"] = 0
            self.d["nonlin_mat_list"] = ""
            self.d["pot_vars"] = ""
            self.d["pot"] = ""
        else:
            self.d["nonlin_mat_list"] = ",K,Mp,Mpc"
            local_matrix_declaration = []
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
            self.d["npl"] = npl = len(self.pot_list)
            nx = self.d["nx"]
            no = self.d["no"]
            np = self.d["np"]
            nn = self.d["nn"]
            local_matrix_declaration.append(self.generate_matrix_declaration("Rv", np, 1))
            lines = []
            lines.append(self.ccode('Rv', l, '(%d)'))
            local_matrix_declaration.append(self.generate_matrix_declaration("Qi", np, np))
            lines.append("Qi = (%s + Matrix<creal, %d, %d>(Rv.asDiagonal())).inverse();" % (self.access_matrix('Q',self.Q, True), np, np))
            if self.matrix_is_identity(self.Uxl):
                t = "Qi"
            elif self.matrix_is_zero(self.Uxl):
                t = None
            else:
                local_matrix_declaration.append(self.generate_matrix_declaration("Tx", nx, np))
                lines.append("Tx = %s * Qi;" % self.access_matrix('Uxl', self.Uxl, True))
                t = "Tx"
            lines.append(self.trans_line('Mx', 'Mx0', self.Mx, t, 'UR', self.UR))
            lines.append(self.trans_line('Mxc', 'Mxc0', self.Mxc, t, 'Ucv', self.Ucv))
            if self.matrix_is_identity(self.Uo):
                t  = "Qi"
            elif self.matrix_is_zero(self.Uo):
                t = None
            else:
                local_matrix_declaration.append(self.generate_matrix_declaration("To", no, np))
                lines.append("To = %s * Qi;" % self.access_matrix('Uo', self.Uo, True))
                t = "To"
            lines.append(self.trans_line('Mo', 'Mo0', self.Mo, t, 'UR', self.UR))
            lines.append(self.trans_line('Moc', 'Moc0', self.Moc, t, 'Ucv', self.Ucv))
            if self.matrix_is_identity(self.Unl):
                t = "Qi"
            elif  self.matrix_is_zero(self.Unl):
                t = None
            else:
                local_matrix_declaration.append(self.generate_matrix_declaration("Tp", nn, np))
                lines.append("Tp = %s * Qi;" % self.access_matrix('Unl', self.Unl, True))
                t = "Tp"
            lines.append(self.trans_line('Mp', 'Mp0', self.Mp, t, 'UR.block(0, 0, %(np)d, %(mp_cols)d)' % self.d, None))
            lines.append(self.trans_line('Mpc', 'Mpc0', self.Mpc, t, 'Ucv', self.Ucv))
            lines.append(self.trans_line('K', 'K0', self.K, t, 'UR.block(0, %(mp_cols)d, %(np)d, %(m_cols)d-%(mp_cols)d)' % self.d, None))
            self.d["update_pot"] = "\n    ".join(local_matrix_declaration+lines)
        self.generate_global_matrices()
        self.generate_const_data()
        return self.d
