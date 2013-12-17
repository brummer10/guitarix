from __future__ import division
import math, sys
from collections import OrderedDict
import sympy as sp
import numpy as np
import numpy.matlib as ml
import numpy.linalg as la
import dk_templates
from codelib import *

def solver_set_defaults(solver_dict=None):
    if solver_dict is None:
        solver_dict = {}
    else:
        solver_dict = solver_dict.copy()
    solver_dict.setdefault("method", "hybr")
    solver_dict.setdefault("factor", 1.e2)
    solver_dict.setdefault("xtol", math.sqrt(sys.float_info.epsilon))
    solver_dict.setdefault("maxfev", 2000)
    solver_dict.setdefault("max_homotopy_iter", 100)
    return solver_dict


class EquationMatrices(object):

    def __init__(self, eq, npl):
        self.__dict__.update(eq.__dict__)
        self.npl = npl
        self.Mp = np.concatenate((eq.G0, eq.H0), axis=1)
        if len(eq.blocklist) > 1:
            C = eq.Cd
            F = eq.Fd
        else:
            C = eq.Co
            F = eq.Fo
        self.Mx = np.concatenate((eq.A0, eq.B0, C), axis=1)
        self.Mo = np.concatenate((eq.D0, eq.E0, F), axis=1)
        self.m_cols = self.Mx.shape[1]
        if hasattr(eq,"Q"):
            self.UR = np.concatenate((eq.Uxr.T, eq.Uu.T, eq.Unr.T), axis=1)


class Structure(object):

    def __init__(self, name):
        self.name = name
        self.members = []
        self.nonlin_info = False
        self.minmax_info = None

    def add(self, m):
        self.members.append(m)

    def add_nonlin_info(self):
        self.nonlin_info = True;

    def add_minmax_info(self, rows):
        self.minmax_info = rows

    def get_initializer(self, kw):
        s = dict((m.name, i) for i, m in enumerate(self.members))
        n = len(self.members)
        if self.nonlin_info:
            s['info'] = n
            s['nfev'] = n+1
            s['fnorm'] = n+2
            n += 3
        if self.minmax_info:
            s['p_val'] = n
            n += 1
        l = [None]*n
        s2 = set()
        for k, v in kw.items():
            try:
                i = s[k]
            except KeyError:
                raise ValueError("unknown struct member: %s" % k)
            if isinstance(v, VariableAccess):
                l[i] = str(v.address_of())
            else:
                l[i] = v
            s2.add(k)
        missing = set(s) - s2
        if missing:
            raise ValueError("no structure initialization for: %s" % ", ".join(missing))
        return ", ".join(l)

    def generate_lines(self):
        l = []
        arglist = [m.generate("_") for m in self.members]
        initlist = ["%s(%s_)" % (r.name, r.name) for r in self.members]
        l.append("struct %s {\n" % self.name)
        l += ["    %s;\n" % m for m in self.members]
        if self.nonlin_info:
            l.append("    int *info;\n")
            l.append("    int *nfev;\n")
            l.append("    creal *fnorm;\n")
            initlist += ["info(info_)", "nfev(nfev_)", "fnorm(fnorm_)"]
            arglist += ["int *info_", "int *nfev_", "creal *fnorm_"]
        if self.minmax_info:
            p_val = MatrixDeclaration('p_val', rows=self.minmax_info, cols=1, pointer=True, array=True)
            l.append("    %s;\n" % p_val)
            initlist.append("p_val(p_val_)")
            arglist.append(p_val.generate("_"))
        l.append("    inline %(name)s(%(args)s): %(init)s {}\n" % dict(
                name = self.name,
                args = ", ".join(arglist),
                init = ", ".join(initlist),
                ))
        l.append("};")
        return l

    def __str__(self):
        return "".join(self.generate_lines())


class NonlinFunction(object):

    def __init__(self, global_ns, K, CZ, func, nn, slicing, have_constant_matrices):
        self.global_ns = global_ns
        self.K = K
        self.CZ = CZ
        self.func = func
        self.nn = nn
        self.slicing = slicing
        self.have_constant_matrices = have_constant_matrices
        self.locals = Namespace()

    def expr_list(self, v):
        l = []
        f = self.func
        off = 0
        if self.slicing:
            f = f[self.slicing]
            off = self.slicing.start
        for expr, vl, base in f:
            for j, e in enumerate(vl):
                expr = expr.subs(e, v[base-off+j])
            l.append(expr)
        return l

    def generate(self, template):
        if self.slicing:
            blockV = self.slicing
            blockM = (self.slicing, self.slicing)
            start = self.slicing.start
        else:
            blockV = None
            blockM = None
            start = 0
        v = make_symbol_vector('v', self.nn)
        i = VectorAccess('i', param=True)
        l = []
        l += expr_list_to_ccode(str(i), self.expr_list(v), '(%d)', start)
        mv = MatrixDefinition('mv', rows=self.nn, cols=1)
        Mfvec = MatrixDefinition('Mfvec', value='fvec', rows=self.nn, cols=1)
        self.locals.add(mv)
        self.locals.add(Mfvec)
        l += self.locals.generate_lines()
        if self.slicing:
            l.append("mv << %s;\n" % ", ".join(['v[%d]' % i for i in range(self.nn)]))
        else:
            l.append("mv << %s;\n" % ", ".join(['v[%d]' % i if self.CZ[i] else '0' for i in range(len(self.CZ))]))
        if not matrix_is_identity(self.K):
            if self.have_constant_matrices:
                if blockM:
                    self.global_ns.add(MatrixDefinition('Ks', self.K[blockM]))
                    K = MatrixAccess('Ks')
                else:
                    self.global_ns.add(MatrixDefinition('K', self.K))
                    K = MatrixAccess('K')
            else:
                K = MatrixAccess('K', param=True, block=blockM)
            l.append("Mfvec = %(p)s + %(K)s * %(i)s - %(mv)s;\n" % dict(
                p = VectorAccess('p', param=True, block=blockV),
                K = K,
                i = VectorAccess('i', param=True, block=blockV),
                mv = VectorAccess('mv'),
                ))
        else:
            l.append("Mfvec = %(p)s + %(i)s - %(mv)s;" % dict(
                p = VectorAccess('p', param=True, block=blockV),
                i = VectorAccess('i', param=True, block=blockV),
                mv = VectorAccess('mv'),
                ))
        return template.render(dict(expression=join_with_indent(l)))


class NonlinFunctionCC(object):

    def __init__(self, global_ns, K, Kl, CZ, func, nn, blocklist, have_constant_matrices, extra_sources):
        self.global_ns = global_ns
        self.K = K
        self.Kl = Kl
        self.CZ = CZ
        self.func = func
        self.nn = nn
        self.blocklist = blocklist
        self.extra_sources = extra_sources
        self.have_constant_matrices = have_constant_matrices

    def generate(self, template):
        end = self.blocklist[-1].stop
        V0 = slice(0, end)
        V1 = slice(end, self.nn)
        M0 = (slice(0, end), slice(end, self.nn))
        M1 = (slice(end, self.nn), slice(0, self.nn))
        loc = Namespace()
        l = []
        loc.add(MatrixDefinition('Mv', value='v', rows=self.nn-end, cols=1, aligned=False, const=True))
        if self.extra_sources:
            loc.add(MatrixDefinition('pt', rows=end, cols=1, array=True))
            pt = VectorAccess('pt')
        else:
            loc.add(MatrixDefinition('pt', rows=self.nn, cols=1))
            pt = VectorAccess('pt', block=V0)
        l += loc.generate_lines()
        if self.have_constant_matrices:
            self.global_ns.add(MatrixDefinition('Ku', self.K[M0]))
            Ku = MatrixAccess('Ku')
        else:
            Ku = MatrixAccess('K', param=True, block=M0)
        l.append("%s = %s + %s * %s;\n" % (
            pt,
            VectorAccess('p', param=True, block=V0),
            Ku,
            VectorAccess('Mv')))
        if self.extra_sources:
            shape_transform = self.extra_sources["shape_transform"]
            for mat in shape_transform:
                self.global_ns.add(mat)
            if shape_transform:
                def nth(j):
                    idx = []
                    for sl in self.blocklist:
                        ln = sl.stop - sl.start
                        for i in range(ln):
                            idx.append(j)
                        j += ln
                    return idx
                loc.add(MatrixDeclaration('PP1', rows=end, cols=1, array=True))
                l += loc.generate_lines()
                l.append("PP1 << %s;\n" % ", ".join(["pt(%d)" % i for i in nth(1)]))
                loc.add(MatrixDeclaration('PP0', rows=end, cols=1, array=True))
                l += loc.generate_lines()
                l.append("PP0 << %s;\n" % ", ".join(["pt(%d)" % i for i in nth(0)]))
                l += loc.generate_lines()
                l.append("pt = (Spm1 * PP1 + Ssm1) * PP1 + Sam1 + ((Spm2 * PP1 + Ssm2) * PP1 + Sam2) * PP0;\n")
                loc.add(MatrixDeclaration('res', rows=end, cols=1, array=True))
                l += loc.generate_lines()
                inp = ["&pt(%d)" % i for i in range(end)]
                outp = ["&res(%d)" % i for i in range(end)]
            else:
                jj = 0
                inp = []
                outp = []
                for i, sl in enumerate(self.blocklist):
                    o = VectorAccess('i', param=True)
                    for j in range(sl.stop - sl.start):
                        inp.append("&pt(%d)" % i)
                        inp.append("&%s(%d)" % (o, jj))
                        jj += 1
            jj = 0
            tables = self.extra_sources["tables"]
            for i, sl in enumerate(self.blocklist):
                for j, kn in enumerate(tables[i].knot_data):
                    fu = "splev"
                    if kn[0].tp == 'pp':
                        fu = "splev_pp"
                    l.append("splinedata<unsigned short>::%s<%s>(&AmpData::nonlin_%d::sd.sc[%d], %s, %s);\n"
                             % (fu, ",".join([str(v.get_order()) for v in kn if v.used()]), i, j, inp[jj], outp[jj]))
                    jj += 1
            if shape_transform:
                l.append("%s = ((Spm0 * PP1 + Ssm0) * PP1 + Sam0) * res;\n" % VectorAccess('i', param=True, block=V0))
        else:
            loc.add(MatrixDefinition('pp', rows=self.nn, cols=1, pointer=True))
            l += loc.generate_lines()
            l.append("%s = %s;\n" % (
                MatrixAccess('pp', pointer=True).address_of(),
                MatrixAccess('p', param=True).address_of()))
            restore = "%s = %s;\n" % (
                MatrixAccess('p', param=True).address_of(),
                MatrixAccess('pp', pointer=True).address_of())
            l.append("%s = %s;\n" % (
                MatrixAccess('p', param=True).address_of(),
                MatrixAccess('pt').address_of()))
            l.append("int ret;\n")
            for i, sl in enumerate(self.blocklist):
                l.append("ret = nonlin_%d::nonlin_solve(par);\n" % i)
                l.append("if (ret != 0) {\n")
                l.append("    "+restore)
                l.append("    return 1;\n")
                l.append("};\n")
            l.append(restore)
        l.append("%s = %s;\n" % (VectorAccess('i', param=True, block=V1), VectorAccess('Mv')))
        if self.have_constant_matrices:
            if M1:
                self.global_ns.add(MatrixDefinition('Kl', self.Kl))
                Kl = MatrixAccess('Kl')
            else:
                Kl = MatrixAccess('K', block=M1)
        else:
            Kl = MatrixAccess('K', param=True, block=M1)
        Mfvec = MatrixDefinition('Mfvec', value='fvec', rows=self.nn-end, cols=1)
        loc.add(Mfvec)
        l += loc.generate_lines()
        l.append("Mfvec = %(p)s + %(K)s * %(i)s;\n" % dict(
            p = VectorAccess('p', param=True, block=V1),
            K = Kl,
            i = VectorAccess('i', param=True),
            ))
        return template.render(dict(expression=join_with_indent(l)))


class NonlinSolver(object):

    def __init__(self, base, glob, Mp, Mpc, Mi, solver_dict, slicing, have_constant_matrices):
        self.base = base
        self.Mp = Mp
        self.Mpc = Mpc
        self.Mi = Mi
        self.solver_dict = solver_dict
        self.slicing = slicing
        self.have_constant_matrices = have_constant_matrices
        self.global_ns = glob
        self.local_ns = Namespace()

    def p_transform(self, pblock):
        l = []
        mp_is_ident = matrix_is_identity(self.Mp)
        mpc_is_zero = matrix_is_zero(self.Mpc)
        if mp_is_ident and mpc_is_zero:
            return l
        par = not self.have_constant_matrices
        par_p = VectorAccess('p', param=True, block=pblock)
        if not mp_is_ident:
            if not par:
                self.global_ns.add(MatrixDefinition('Mp', value=self.Mp))
            s = "%s * %s" % (MatrixAccess('Mp', param=par), par_p)
        else:
            s = "%s" % par_p
        if not mpc_is_zero:
            if not par:
                self.global_ns.add(MatrixDefinition('Mpc', value=self.Mpc))
            s += " + %s" % VectorAccess('Mpc', param=par)
        p_old_def = MatrixDefinition("p_old", rows=self.Mpc.shape[0], cols=1, pointer=True)
        self.local_ns.add(p_old_def)
        p_old = VectorAccess(p_old_def)
        p2_def = MatrixDefinition("p2", rows=self.Mpc.shape[0], cols=1)
        self.local_ns.add(p2_def)
        p2 = VectorAccess(p2_def)
        l += self.local_ns.generate_lines()
        l.append("p2 = %s;\n" % s)
        l.append("p_old = %s;\n" % par_p.address_of())
        l.append("%s = &p2;\n" % par_p.address_of())
        self.cleanup.append("%s = p_old;\n" % par_p.address_of())
        return l

    def i_transform(self, iblock):
        l = []
        mi_is_ident = matrix_is_identity(self.Mi)
        if mi_is_ident:
            return l
        par = not self.have_constant_matrices
        self.global_ns.add(MatrixDefinition("Mi", self.Mi))
        l.append("%(io)s = %(Mi)s * %(ii)s;" % dict(
                io = VectorAccess('i', param=True, block=iblock),
                Mi = MatrixAccess('Mi'),
                ii = VectorAccess('i', param=True, block=self.slicing),
                ))
        return l

    def make_var_v_ref(self):
        return "&%s(%s)" % (VectorAccess("v", param=True), self.slicing.start if self.slicing else 0)

    def generate(self, template):
        d = self.base.copy()
        if self.slicing:
            d["nn"] = d["nni"] = d["nno"] = self.slicing.stop - self.slicing.start
            pblock = iblock = self.slicing
        else:
            if d["nn"] != d["nni"]:
                pblock = slice(0, d["nni"])
            else:
                pblock = None
            if d["nn"] != d["nno"]:
                iblock = slice(0, d["nno"])
            else:
                iblock = None
        self.cleanup = []
        d["i_transform"] = join_with_indent(self.i_transform(iblock))
        d["p_transform"] = join_with_indent(self.p_transform(pblock))
        d["cleanup"] = join_with_indent(self.cleanup)
        d["var_v_ref"] = self.make_var_v_ref()
        d["store_p"] = "%s = %s;\n" % (
            VectorAccess('p_val', param=True, block=self.slicing),
            VectorAccess('p', param=True, block=pblock),
            )
        return template.render(d)


class NonlinSolverCC(NonlinSolver):

    def __init__(self, base, glob, Mp, Mpc, Mi, solver_dict, slicing_cc, have_constant_matrices):
        NonlinSolver.__init__(self, base, glob, Mp, Mpc, Mi, solver_dict, None, have_constant_matrices)
        self.slicing_cc = slicing_cc

    def make_var_v_ref(self):
        return "&%s(%s)" % (VectorAccess("v", param=True), self.slicing_cc.start)

    def generate(self, template):
        self.base = self.base.copy()
        self.base["nn"] = self.base["nni"] = self.base["nno"] = self.slicing_cc.stop - self.slicing_cc.start
        return NonlinSolver.generate(self, template)


class NonlinCode(object):

    method_templates = {
        'hybr':   (dk_templates.c_template_nonlin_func_hybr,
                   dk_templates.c_template_nonlin_solver_hybr),
        'lm':     (dk_templates.c_template_nonlin_func_lm,
                   dk_templates.c_template_nonlin_solver_lm),
        'hybrCC': (dk_templates.c_template_nonlin_func_hybrCC,
                   dk_templates.c_template_nonlin_solver_hybrCC),
        }

    def __init__(self, struct, eq, solver_dict, slicing, slicing_cc, namespace, extra_sources):
        self.struct = struct
        self.eq = eq
        self.solver_dict = solver_dict
        self.slicing = slicing
        self.slicing_cc = slicing_cc
        self.namespace = namespace
        self.extra_sources = extra_sources

    def generate(self):
        eq = self.eq
        base = {}
        base["g_nn"] = eq.nn
        base["g_nni"] = eq.nni
        base["g_nno"] = eq.nno
        base["npl"] = eq.npl
        if self.slicing:
            nn = base["nn"] = nni = base["nni"] = nno = base["nno"] = self.slicing.stop - self.slicing.start
            pblockV = blockV = self.slicing
            base["pblockV"] = VectorAccess.block_expr(self.slicing.start, self.slicing.stop - self.slicing.start)
            base["iblockV"] = VectorAccess.block_expr(self.slicing.start, self.slicing.stop - self.slicing.start)
        else:
            base["nn"] = nn = eq.nn
            base["nni"] = nni = eq.nni
            base["nno"] = nno = eq.nno
            blockV = None
            if nn != nni:
                pblockV = slice(0, nni)
                base["pblockV"] = VectorAccess.block_expr(0, nni)
            else:
                pblockV = None
                base["pblockV"] = ""
            if nn != nno:
                base["iblockV"] = VectorAccess.block_expr(0, nno)
            else:
                base["iblockV"] = ""
        for k, v in self.solver_dict.items():
            base["solver_"+k] = v
        ini = dict(
            p = MatrixAccess('mp'),
            i = MatrixAccess('mi'),
            v = MatrixAccess('Mv'),
            info = '&g_info',
            fnorm = 'fnorm',
            nfev = '&g_nfev',
            p_val = MatrixAccess('p_val'),
            )
        if eq.np:
            ini["K"] = MatrixAccess('K')
            ini["Mpc"] = MatrixAccess('Mpc')
        base["nonlin_mat_list"] = self.struct.get_initializer(ini)
        glob = Namespace()
        d = base.copy()
        if self.slicing_cc:
            if self.slicing:
                of = NonlinFunction(glob, eq.K0, eq.CZ, eq.f, nn, self.slicing, eq.np==0)
                on = NonlinSolver(base, glob, eq.U0, eq.Hc0, eq.Kn, self.solver_dict, self.slicing, eq.np==0)
                func_t, solv_t = self.method_templates[self.solver_dict["method"]]
            else:
                of = NonlinFunctionCC(glob, eq.K0, eq.Kl, eq.CZ, eq.f, nn, eq.blocklist, eq.np==0, self.extra_sources)
                on = NonlinSolverCC(base, glob, eq.U0, eq.Hc0, np.identity(len(eq.Mi)), self.solver_dict, self.slicing_cc, eq.np==0)
                func_t, solv_t = self.method_templates[self.solver_dict["method"]]
        else:
            of = NonlinFunction(glob, eq.K0, eq.CZ, eq.f, nn, self.slicing, eq.np==0)
            on = NonlinSolver(base, glob, eq.U0, eq.Hc0, eq.Mi, self.solver_dict, self.slicing, eq.np==0)
            func_t, solv_t = self.method_templates[self.solver_dict["method"]]
        if func_t is not None:
            d["fcn_def"] = of.generate(func_t)
        d["nonlin_def"] = on.generate(solv_t)
        d["namespace"] = self.namespace
        d["global_data_def"] = glob
        d["par_p"] = VectorAccess("p", param=True, block=pblockV)
        d["par_v"] = VectorAccess("v", param=True, block=blockV)
        return dk_templates.c_template_nonlin_solver.render(d)


class TableCode(object):

    def __init__(self, struct, eq, slicing, slicing_cc, namespace):
        self.struct = struct
        self.eq = eq
        self.slicing = slicing
        self.slicing_cc = slicing_cc
        self.namespace = namespace

    def generate(self):
        eq = self.eq
        base = {}
        base["g_nn"] = eq.nn
        base["g_nni"] = eq.nni
        base["g_nno"] = eq.nno
        base["npl"] = eq.npl
        if self.slicing:
            nn = base["nn"] = nni = base["nni"] = nno = base["nno"] = self.slicing.stop - self.slicing.start
            blockV = self.slicing
            base["blockV"] = base["pblockV"] = base["iblockV"] = VectorAccess.block_expr(
                self.slicing.start, self.slicing.stop - self.slicing.start)
        else:
            base["nn"] = nn = eq.nn
            base["nni"] = nni = eq.nni
            base["nno"] = nno = eq.nno
            blockV = None
            base["blockV"] = ""
            if nn != nni:
                pblockV = slice(0, nni)
                base["pblockV"] = VectorAccess.block_expr(0, nni)
            else:
                pblockV = None
                base["pblockV"] = ""
            if nn != nno:
                base["iblockV"] = VectorAccess.block_expr(0, nno)
            else:
                base["iblockV"] = ""
        ini = dict(
            p = MatrixAccess('mp'),
            i = MatrixAccess('mi'),
            v = MatrixAccess('Mv'),
            info = '&g_info',
            fnorm = 'fnorm',
            nfev = '&g_nfev',
            p_val = MatrixAccess('p_val'),
            )
        if eq.np:
            ini["K"] = MatrixAccess('K')
            ini["Mpc"] = MatrixAccess('Mpc')
        base["nonlin_mat_list"] = self.struct.get_initializer(ini)
        glob = Namespace()
        d = base.copy()
        d["namespace"] = self.namespace
        d["global_data_def"] = glob
        d["par_p"] = VectorAccess("p", param=True, block=blockV)
        d["par_v"] = VectorAccess("v", param=True, block=blockV)
        return dk_templates.c_template_table.render(d)


class UpdateMatrix(object):

    def __init__(self, glob, eq, pot, pot_list, pot_func, Pv):
        self.glob = glob
        self.eq = eq
        self.pot = pot
        self.pot_func = pot_func
        self.pot_list = pot_list
        self.Pv = Pv

    def trans_line(self, res, var, var_data, t, u, u_data):
        self.glob.add(MatrixDefinition(var, var_data))
        self.glob.add(MatrixDefinition(res, rows=var_data.shape[0], cols=var_data.shape[1]))
        s = "%s = %s" % (MatrixAccess(res), MatrixAccess(var))
        if t is None:
            return s + ";\n"
        if u_data is not None:
            self.glob.add(MatrixDefinition(u, u_data))
        return s + " - %s * %s;\n" % (t, u)

    def generate(self):
        eq = self.eq
        d = {}
        pot = make_symbol_vector('pot', eq.np)
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
        d["pot_vars"] = ",".join(['"%s"' % v for v in self.pot_list])
        d["pot"] = ",".join([str(self.pot.get(v,0.5)) for v in self.pot_list])
        nx = eq.nx
        no = eq.no
        np = eq.np
        nn = eq.nn
        loc = Namespace()
        loc.add(MatrixDeclaration("Rv", rows=np, cols=1))
        lines = []
        lines += loc.generate_lines()
        lines += expr_list_to_ccode('Rv', l, '(%d)')
        self.glob.add(MatrixDefinition("Q", eq.Q))
        loc.add(MatrixDeclaration("Qi", rows=np, cols=np))
        lines += loc.generate_lines()
        lines.append("Qi = (%s + Matrix<creal, %d, %d>(Rv.asDiagonal())).inverse();\n" % (MatrixAccess('Q'), np, np))
        if eq.nx:
            if matrix_is_identity(eq.Uxl):
                t = "Qi"
            elif matrix_is_zero(eq.Uxl):
                t = None
            else:
                loc.add(MatrixDeclaration("Tx", rows=nx, cols=np))
                lines += loc.generate_lines()
                self.glob.add(MatrixDefinition("Uxl", eq.Uxl))
                lines.append("Tx = %s * Qi;\n" % MatrixAccess('Uxl'))
                t = "Tx"
            lines.append(self.trans_line('Mx', 'Mx0', eq.Mx, t, 'UR', eq.UR))
            lines.append(self.trans_line('Mxc', 'Mxc0', eq.Bc0, t, 'Ucv', eq.Ucv.T))
        if matrix_is_identity(eq.Uo):
            t  = "Qi"
        elif matrix_is_zero(eq.Uo):
            t = None
        else:
            loc.add(MatrixDeclaration("To", rows=no, cols=np))
            lines += loc.generate_lines()
            self.glob.add(MatrixDefinition('Uo', eq.Uo))
            lines.append("To = %s * Qi;\n" % MatrixAccess('Uo'))
            t = "To"
        lines.append(self.trans_line('Mo', 'Mo0', eq.Mo, t, 'UR', eq.UR))
        lines.append(self.trans_line('Moc', 'Moc0', eq.Ec0, t, 'Ucv', eq.Ucv.T))
        if eq.nni:
            if matrix_is_identity(eq.Unl):
                t = "Qi"
            elif  matrix_is_zero(eq.Unl):
                t = None
            else:
                loc.add(MatrixDeclaration("Tp", rows=nn, cols=np))
                lines += loc.generate_lines()
                self.glob.add(MatrixDefinition("Unl", eq.Unl))
                lines.append("Tp = %s * Qi;\n" % MatrixAccess('Unl'))
                t = "Tp"
            lines.append(self.trans_line('Mp', 'Mp0', eq.Mp, t, 'UR.block<%d, %d>(0, 0)' % (eq.np, eq.mp_cols), None))
            lines.append(self.trans_line('Mpc', 'Mpc0', eq.Hc0, t, 'Ucv', eq.Ucv.T))
            lines.append(self.trans_line('K', 'K0', eq.K0, t, 'UR.block<%d, %d>(0, %d)' % (eq.np, eq.m_cols-eq.mp_cols, eq.mp_cols), None))
        d["update_pot"] = join_with_indent(lines)
        return d


class LinearCode(object):

    def __init__(self, glob, eq):
        self.glob = glob
        self.eq = eq

    def generate(self):
        eq = self.eq
        d = {}
        if eq.nn != eq.nni:
            pblock = slice(0, eq.nni)
        else:
            pblock = None
        d["m_cols"] = eq.m_cols
        d["gen_mp"] = gen_linear_combination(
            self.glob, VectorAccess('mp',block=pblock), 'dp', 'Mp', eq.Mp)
        d["gen_xn"] = gen_linear_combination(
            self.glob, 'xn', 'd', 'Mx', eq.Mx, 'Mxc', eq.Bc0)
        d["gen_xo"] = gen_linear_combination(
            self.glob, 'xo', 'd', 'Mo', eq.Mo, 'Moc', eq.Ec0)
        d["gen_xo_float"] = gen_linear_combination(
            self.glob, 'xo', 'd', 'Mo', eq.Mo, cast="float")
        return d


class NonlinEq(object):

    def __init__(self, nn, nni, nno, np, npl, K0, CZ, f, U0, Hc0, Mi, Kn):
        self.nn = nn
        self.nni = nni
        self.nno = nno
        self.np =  np
        self.npl =  npl
        self.K0 = K0
        self.CZ = CZ
        self.f = f
        self.U0 = U0
        self.Hc0 = Hc0
        self.Mi = Mi
        self.Kn = Kn


class CodeGenerator(object):

    def __init__(self, eq, solver_dict, solver_params, pot, pot_list, pot_func, pot_attr, Pv, extra_sources):
        self.eq = EquationMatrices(eq, len(pot_list))
        self.solver_dict = solver_set_defaults(solver_dict)
        self.solver_params = solver_params
        self.pot = pot
        self.pot_list = pot_list
        self.pot_func = pot_func
        self.pot_attr = pot_attr
        self.Pv = Pv
        self.extra_sources = extra_sources
        self.have_constant_matrices = (len(pot_func) == 0)

    def pot_code(self):
        d = {}
        if self.pot_attr:
            d['have_master_slider'] = True
            d['master_slider_id'] = self.pot_attr[0][0]
        else:
            d['have_master_slider'] = False
        d['knob_ids'] = [t[0] for t in self.pot_attr]
        d['timecst'] = 0.01
        d['regs'] = [dict(id=vv[0],name=vv[1],desc="",varidx=i) for i, vv in enumerate(self.pot_attr)]
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
        d['calc_pots'] = "\n    ".join(ll)
        return d

    def generate(self, d):
        eq = self.eq
        if eq.nni:
            for k, v in self.solver_dict.items():
                d["solver_"+k] = v
            s = Structure("nonlin_param")
            s.add(MatrixDeclaration('p', rows=eq.nn, cols=1, pointer=True))
            s.add(MatrixDeclaration('i', rows=eq.nn, cols=1, pointer=True))
            s.add(MatrixDeclaration('v', rows=eq.nn, cols=1, mapping=True, pointer=True, aligned=False))
            if not self.have_constant_matrices:
                s.add(MatrixDeclaration('K', rows=eq.nn, cols=eq.nn, pointer=True))
                s.add(MatrixDeclaration('Mpc', rows=eq.nn, cols=1, pointer=True))
            s.add_nonlin_info()
            s.add_minmax_info(eq.nni)
            ini = dict(
                p = MatrixAccess('mp'),
                i = MatrixAccess('mi'),
                v = '&g_v',
                info = '&g_info',
                fnorm = '&fnorm',
                nfev = '&g_nfev',
                p_val = MatrixAccess('p_val'),
                )
            if not self.have_constant_matrices:
                ini["K"] = MatrixAccess('K')
                ini["Mpc"] = MatrixAccess('Mpc')
            d["nonlin_mat_list"] = s.get_initializer(ini)
            ini = dict(
                p = MatrixAccess('mp'),
                i = MatrixAccess('mi'),
                v = '&Mv',
                info = 'info',
                fnorm = 'fnorm',
                nfev = 'nfev',
                p_val = MatrixAccess('p_val'),
                )
            if not self.have_constant_matrices:
                ini["K"] = MatrixAccess('K')
                ini["Mpc"] = MatrixAccess('Mpc')
            d["nonlin_mat_list_calc"] = s.get_initializer(ini)
            if len(eq.blocklist) > 1:
                d["nc"] = len(eq.blocklist)
                l = []
                sl_cc = slice(eq.blocklist[-1].stop, eq.nn)
                complist = []
                for i, sl in enumerate(eq.blocklist):
                    complist.append(dict(
                        nn = sl.stop-sl.start,
                        nni = sl.stop-sl.start,
                        nno = sl.stop-sl.start,
                        ))
                    neq = NonlinEq(eq.nn, eq.nni, eq.nno, eq.np, eq.npl, eq.K0, eq.CZ, eq.f, ml.identity(eq.U0.shape[0]), ml.zeros_like(eq.Hc0), eq.Mi, eq.Kn[i])
                    if self.solver_dict["method"] == "table":
                        l.append(TableCode(s, neq, sl, sl_cc, "nonlin_%d" % i).generate())
                    else:
                        if self.solver_params is None:
                            spar = {}
                        else:
                            spar = self.solver_params[i]
                        spar = solver_set_defaults(spar)
                        l.append(NonlinCode(s, neq, spar, sl, sl_cc, "nonlin_%d" % i, None).generate())
                if self.solver_dict["method"] == "table":
                    solver = self.solver_dict.copy()
                    solver["method"] = "hybrCC"
                else:
                    solver = self.solver_dict
                l.append(NonlinCode(s, eq, solver, None, sl_cc, "nonlin", self.extra_sources).generate())
                d["components"] = complist
                d["nonlin_code"] = "".join(l)
            else:
                d["components"] = ()
                d["nc"] = 0
                if self.solver_dict["method"] == "table":
                    d["nonlin_code"] = TableCode(s, eq, None, None, "nonlin").generate()
                else:
                    d["nonlin_code"] = NonlinCode(s, eq, self.solver_dict, None, None, "nonlin", None).generate()
            d["struct_def"] = s
            if eq.nn != eq.nni:
                d["iblock"] = VectorAccess.block_expr(0, eq.nno)
            else:
                d["iblock"] = ""
        else:
            d["nonlin_code"] = ""
            d["struct_def"] = ""
            d["nc"] = 0
            d["iblock"] = ""
        glob = Namespace()
        if self.have_constant_matrices:
            d["update_pot"] = ""
        else:
            d.update(UpdateMatrix(glob, eq, self.pot, self.pot_list, self.pot_func, self.Pv).generate())
            d.update(self.pot_code())
        d.update(LinearCode(glob, eq).generate())
        d["global_matrices"] = glob
        return dk_templates.c_template_top.render(d)
