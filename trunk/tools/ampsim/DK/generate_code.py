from __future__ import division
import math, sys
from collections import OrderedDict
import sympy as sp
import numpy as np
import numpy.matlib as ml
import numpy.linalg as la
import dk_templates
from codelib import *
import dk_simulator

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
        s = dict((m.name, i) for i, m in enumerate(v for v in self.members if v.pointer))
        n = len(s)
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
        if not l:
            return ""
        return "("+", ".join(l)+")"

    def generate_lines(self):
        arglist = [m.generate("_") for m in self.members if m.pointer]
        initlist = []
        for m in self.members:
            if m.pointer:
                initlist.append("%s(%s_)" % (m.name, m.name))
            else:
                initlist.append("%s()" % m.name)
        l = []
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
        if initlist:
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

    def __init__(self, global_ns, neq, on):
        self.global_ns = global_ns
        self.neq = neq
        self.have_constant_matrices = (neq.eq.np == 0)
        self.locals = Namespace()
        self.input_slice = on.input_slice
        self.output_slice = on.output_slice

    def expr_list(self, v):
        par_v = make_symbol_vector('(*par.v)', self.neq.nn)
        l = []
        f = self.neq.eq.f
        off = 0
        if self.neq.v_slice:
            off = self.neq.v_slice.start
            f = f[self.neq.v_slice]
        for expr, vl, base in f:
            for var, idx in zip(vl, base):
                if idx >= off:
                    vv = v[idx-off]
                else:
                    vv = par_v[idx]
                expr = expr.subs(var, vv)
            l.append(expr)
        return l

    def generate(self, template):
        if self.neq.v_slice:
            iblockV = self.input_slice
            oblockV = self.output_slice
            blockM = (self.neq.v_slice, self.neq.v_slice)
            start = self.output_slice.start
        else:
            iblockV = oblockV = None
            blockM = None
            start = 0
        v = make_symbol_vector('v', self.neq.nn)
        i = VectorAccess('i', param=True)
        l = []
        l += expr_list_to_ccode(str(i), self.expr_list(v), '(%d)', start)
        mv = MatrixDefinition('mv', rows=self.neq.nn, cols=1)
        Mfvec = MatrixDefinition('Mfvec', value='fvec', rows=self.neq.nn, cols=1)
        self.locals.add(mv)
        self.locals.add(Mfvec)
        l += self.locals.generate_lines()
        CZ = self.neq.eq.CZ[self.neq.v_slice]
        K = self.neq.eq.K
        if self.have_constant_matrices:
            K = K[blockM]
        l.append("mv << %s;\n" % ", ".join(
            ['v[%d]' % i if z else '0' for i, z in enumerate(CZ)]))
        if not matrix_is_identity(K):
            if self.have_constant_matrices:
                self.global_ns.add(MatrixDefinition('K', K))
                K = MatrixAccess('K')
            else:
                K = MatrixAccess('K', param=True, block=blockM, pointer=False)
            l.append("Mfvec = %(p)s + %(K)s * %(i)s - %(mv)s;\n" % dict(
                p = VectorAccess('p', param=True, block=iblockV),
                K = K,
                i = VectorAccess('i', param=True, block=oblockV),
                mv = VectorAccess('mv'),
                ))
        else:
            l.append("Mfvec = %(p)s + %(i)s - %(mv)s;" % dict(
                p = VectorAccess('p', param=True, block=iblockV),
                i = VectorAccess('i', param=True, block=oblockV),
                mv = VectorAccess('mv'),
                ))
        return template.render(dict(expression=join_with_indent(l)))


class NonlinFunctionCC(object):

    def __init__(self, global_ns, neq, extra_sources):
        self.global_ns = global_ns
        self.neq = neq
        self.extra_sources = extra_sources

    def generate(self, template):
        neq = self.neq
        have_constant_matrices = (neq.eq.np == 0)
        end = neq.cc_slice.start
        cc = neq.cc_slice.stop - neq.cc_slice.start
        p0_slice = slice(neq.p_slice.start, neq.p_slice.stop-cc)
        p1_slice = slice(neq.p_slice.stop-cc, neq.p_slice.stop)
        i0_slice = slice(neq.i_slice.start, neq.i_slice.stop-cc)
        i1_slice = slice(neq.i_slice.stop-cc, neq.i_slice.stop)
        M0 = (slice(0, end), slice(end, neq.nn))
        M1 = (slice(end, neq.nn), slice(0, neq.nn))
        loc = Namespace()
        l = []
        loc.add(MatrixDefinition('Mv', value='v', rows=neq.nn-end, cols=1, aligned=False, const=True))
        if self.extra_sources:
            loc.add(MatrixDefinition('pt', rows=p0_slice.stop-p0_slice.start, cols=1, array=True))
            pt = VectorAccess('pt')
        else:
            loc.add(MatrixDefinition('pt', rows=neq.nn, cols=1))
            pt = VectorAccess('pt', block=p0_slice)
        l += loc.generate_lines()
        if have_constant_matrices:
            #self.global_ns.add(MatrixDefinition('Ku', neq.eq.K[M0]))
            self.global_ns.add(MatrixDefinition('Ku', neq.Ku))
            Ku = MatrixAccess('Ku')
        else:
            Ku = MatrixAccess('K', param=True, block=M0, pointer=False)
        l.append("%s = %s + %s * %s;\n" % (
            pt,
            VectorAccess('p', param=True, block=p0_slice),
            Ku,
            VectorAccess('Mv')))
        if self.extra_sources:
            shape_transform = self.extra_sources.get("shape_transform", ())
            for mat in shape_transform:
                self.global_ns.add(mat)
            if shape_transform:
                def nth(j):
                    idx = []
                    for bl in neq.subblocks:
                        ln = bl.v_slice.stop - bl.v_slice.start
                        idx.append(j)
                        j += ln
                    return idx
                def spliced(n):
                    for a in range(n):
                        yield a
                        yield a+n
                nn2 = end//2
                loc.add(MatrixDeclaration('PP1', rows=nn2, cols=1, array=True))
                l += loc.generate_lines()
                l.append("PP1 << %s;\n" % ", ".join(["pt(%d)" % i for i in nth(1)]))
                loc.add(MatrixDeclaration('PP0', rows=nn2, cols=1, array=True))
                l += loc.generate_lines()
                l.append("PP0 << %s;\n" % ", ".join(["pt(%d)" % i for i in nth(0)]))
                l += loc.generate_lines()
                l.append("pt.head<%d>() = (Spm1 * PP1 + Ssm1) * PP1 + Sam1 + ((Spm2 * PP1 + Ssm2) * PP1 + Sam2) * PP0;\n" % nn2)
                loc.add(MatrixDeclaration('res', rows=end, cols=1, array=True))
                l += loc.generate_lines()
                inp = ["&pt(%d)" % (i//2) for i in range(end)]
                outp = ["&res(%d)" % i for i in spliced(nn2)]
            else:
                inp = []
                outp = []
                for bl in neq.subblocks:
                    o = VectorAccess('i', param=True)
                    for j in range(bl.i_slice.start, bl.i_slice.stop):
                        inp.append("&pt(%d)" % bl.p_slice.start)
                        outp.append("&%s(%d)" % (o, j))
            jj = 0
            tables = self.extra_sources["tables"]
            for bl in neq.subblocks:
                for j, kn in enumerate(tables[bl.namespace].knot_data):
                    reorder = False
                    unused = False
                    ll = []
                    for i, v in enumerate(kn):
                        if not v.used():
                            unused = True
                        else:
                            ll.append(i)
                            if unused:
                                reorder = True
                    if reorder:
                        l.append("{ Array<creal, %d, 1> pt2; pt2 << %s;\n" % (len(ll), ", ".join(["pt(%d)" % (bl.p_slice.start+i) for i in ll])))
                        inpt = "&pt2(0)"
                    else:
                        inpt = inp[jj]
                    fu = "splev"
                    if kn[0].tp == 'pp':
                        fu = "splev_pp"
                    l.append("splinedata<AmpData::%s::maptype>::%s<%s>(&AmpData::%s::sd.sc[%d], %s, %s);\n"
                             % (bl.namespace, fu, ",".join([str(v.get_order()) for v in kn if v.used()]), bl.namespace, j, inpt, outp[jj]))
                    if reorder:
                        l.append("}\n")
                    jj += 1
            if shape_transform:
                l.append("pt.head<%d>() = ((Spm0 * PP1 + Ssm0) * PP1 + Sam0) * res.head<%d>();\n" % (nn2,nn2))
                l.append("pt.tail<%d>() = ((Spm0 * PP1 + Ssm0) * PP1 + Sam0) * res.tail<%d>();\n" % (nn2,nn2))
                l.append("%s << %s;\n" % (VectorAccess('i', param=True, block=i0_slice),
                                          ", ".join(["pt(%d)" % v for v in spliced(nn2)])))
        else:
            loc.add(MatrixDefinition('pp', rows=neq.nn, cols=1, pointer=True))
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
            for bl in neq.subblocks:
                l.append("ret = %s::nonlin_solve(par);\n" % bl.namespace)
                l.append("if (ret != 0) {\n")
                l.append("    "+restore)
                l.append("    return 1;\n")
                l.append("};\n")
            l.append(restore)
        l.append("%s = %s;\n" % (VectorAccess('i', param=True, block=i1_slice), VectorAccess('Mv')))
        if have_constant_matrices:
            if M1:
                self.global_ns.add(MatrixDefinition('Kl', neq.Kl))
                Kl = MatrixAccess('Kl')
            else:
                Kl = MatrixAccess('K', block=M1)
        else:
            Kl = MatrixAccess('K', param=True, block=M1, pointer=False)
        Mfvec = MatrixDefinition('Mfvec', value='fvec', rows=neq.nn-end, cols=1)
        loc.add(Mfvec)
        l += loc.generate_lines()
        l.append("Mfvec = %(p)s + %(K)s * %(i)s;\n" % dict(
            p = VectorAccess('p', param=True, block=p1_slice),
            K = Kl,
            i = VectorAccess('i', param=True, block=neq.i_slice),
            ))
        return template.render(dict(expression=join_with_indent(l)))


class NonlinSolver(object):

    def __init__(self, base, glob, neq, solver_dict):
        self.base = base
        self.neq = neq
        self.solver_dict = solver_dict
        self.have_constant_matrices = (neq.eq.np == 0)
        self.global_ns = glob
        self.local_ns = Namespace()
        self.mp_is_ident = matrix_is_identity(self.neq.U)
        self.mpc_is_zero = matrix_is_zero(self.neq.Hc)
        if self.mp_is_ident and self.mpc_is_zero:
            self.input_slice = self.neq.p_slice
        else:
            self.input_slice = slice(0, self.neq.nn)
        self.mi_is_ident = matrix_is_identity(self.neq.Mi)
        if self.mi_is_ident:
            self.output_slice = self.neq.i_slice
        else:
            self.output_slice = slice(0, self.neq.nn)
        self.base["nn"] = self.neq.nn
        self.base["nni"] = self.neq.nni
        self.base["nno"] = self.neq.nno

    def p_transform(self):
        l = []
        if self.mp_is_ident and self.mpc_is_zero:
            return l
        par = not self.have_constant_matrices
        par_p = VectorAccess('p', param=True, block=self.neq.p_slice)
        if not self.mp_is_ident:
            if not par:
                self.global_ns.add(MatrixDefinition('Mp', value=self.neq.U))
            s = "%s * %s" % (MatrixAccess('Mp', param=par), par_p)
        else:
            s = "%s" % par_p
        if not self.mpc_is_zero:
            if not par:
                self.global_ns.add(MatrixDefinition('Mpc', value=self.neq.Hc))
            s += " + %s" % VectorAccess('Mpc', param=par, pointer=False)
        g_nn = self.neq.eq.nonlin.nn
        p_old_def = MatrixDefinition("p_old", rows=g_nn, cols=1, pointer=True)
        self.local_ns.add(p_old_def)
        p_old = VectorAccess(p_old_def)
        p2_def = MatrixDefinition("p2", rows=g_nn, cols=1)
        self.local_ns.add(p2_def)
        p2 = VectorAccess(p2_def, block=self.input_slice)
        l += self.local_ns.generate_lines()
        l.append("%s = %s;\n" % (p2, s))
        l.append("p_old = %s;\n" % par_p.address_of())
        l.append("%s = &p2;\n" % par_p.address_of())
        self.cleanup.append("%s = p_old;\n" % par_p.address_of())
        return l

    def i_transform(self):
        l = []
        if self.mi_is_ident or self.neq.nno == 0:
            return l
        g_nn = self.neq.eq.nonlin.nn
        mi_def = MatrixDefinition("mi", rows=g_nn, cols=1)
        mi = VectorAccess(mi_def, block=self.output_slice)
        i_old_def = MatrixDefinition("i_old", rows=g_nn, cols=1, pointer=True)
        i_old = VectorAccess(i_old_def)
        par_i = VectorAccess('i', param=True, block=self.neq.i_slice)
        self.global_ns.add(MatrixDefinition("Mi", self.neq.Mi))
        self.local_ns.add(mi_def)
        self.local_ns.add(i_old_def)
        self.setup += self.local_ns.generate_lines()
        self.setup.append("i_old = %s;\n" % VectorAccess('i', param=True).address_of())
        self.setup.append("%s = &mi;\n" % VectorAccess('i', param=True).address_of())
        l.append("%s = i_old;\n" % VectorAccess('i', param=True).address_of())
        par = not self.have_constant_matrices
        l.append("%(io)s = %(Mi)s * %(ii)s;" % dict(
                io = par_i,
                Mi = MatrixAccess('Mi', param=par, pointer=False),
                ii = mi,
                ))
        return l

    def make_var_v_ref(self):
        start = 0
        if self.neq.v_slice:
            start = self.neq.v_slice.start
        return "&%s(%s)" % (VectorAccess("v", param=True), start)

    def generate(self, template):
        d = self.base.copy()
        self.setup = []
        self.cleanup = []
        d["i_transform"] = join_with_indent(self.i_transform())
        d["p_transform"] = join_with_indent(self.p_transform())
        d["setup"] = join_with_indent(self.setup)
        d["cleanup"] = join_with_indent(self.cleanup)
        d["var_v_ref"] = self.make_var_v_ref()
        d["store_p"] = "%s = %s;\n" % (
            VectorAccess('p_val', param=True, block=self.neq.p_slice),
            VectorAccess('p', param=True, block=self.neq.p_slice),
            )
        return template.render(d)

class NonlinSolverCC(NonlinSolver):

    def __init__(self, base, glob, neq, solver_dict):
        NonlinSolver.__init__(self, base, glob, neq, solver_dict)
        self.input_slice = self.neq.p_slice
        self.mp_is_ident = True
        self.mi_is_ident = True

    def make_var_v_ref(self):
        return "&%s(%s)" % (VectorAccess("v", param=True), self.neq.cc_slice.start)

    def generate(self, template):
        self.base = self.base.copy()
        self.base["nn"] = self.base["nni"] = self.base["nno"] = self.neq.cc_slice.stop - self.neq.cc_slice.start
        return NonlinSolver.generate(self, template)


class NonlinCode(object):

    method_templates = {
        'hybr':   (dk_templates.c_template_nonlin_func_hybrCC,
                   dk_templates.c_template_nonlin_solver_hybrCC),
        'lm':     (dk_templates.c_template_nonlin_func_lm,
                   dk_templates.c_template_nonlin_solver_lm),
        'hybrCC': (dk_templates.c_template_nonlin_func_hybrCC,
                   dk_templates.c_template_nonlin_solver_hybrCC),
        }

    def __init__(self, struct, neq, solver_dict, extra_sources):
        self.struct = struct
        self.neq = neq
        self.solver_dict = solver_dict
        self.extra_sources = extra_sources

    def setup(self, d):
        neq = self.neq
        base = {}
        base["dev_interface"] = d["dev_interface"]
        g_nonlin = neq.eq.nonlin
        base["extern_nonlin"] = not neq.subblocks or neq is g_nonlin
        base["g_nn"] = g_nonlin.nn
        base["g_nni"] = g_nonlin.nni
        base["g_nno"] = g_nonlin.nno
        base["npl"] = neq.eq.get_npl()
        if neq.nn != g_nonlin.nn:
            nn = base["nn"] = neq.nn
            nni = base["nni"] = neq.nni
            nno = base["nno"] = neq.nno
            self.blockV = neq.v_slice
            self.pblockV = neq.p_slice
            base["pblockV"] = VectorAccess.block_expr(neq.p_slice)
            base["iblockV"] = VectorAccess.block_expr(neq.i_slice)
        else:
            base["nn"] = nn = neq.nn
            base["nni"] = nni = neq.nni
            base["nno"] = nno = neq.nno
            self.blockV = None
            if nn != nni:
                self.pblockV = slice(0, nni)
                base["pblockV"] = VectorAccess.block_expr([0, nni])
            else:
                self.pblockV = None
                base["pblockV"] = ""
            if nn != nno:
                base["iblockV"] = VectorAccess.block_expr([0, nno])
            else:
                base["iblockV"] = ""
        if self.solver_dict:
            for k, v in self.solver_dict.items():
                base["solver_"+k] = v
        ini = dict(
            p = MatrixAccess('mp'),
            i = MatrixAccess('mi'),
            v = MatrixAccess('Mv'),
            info = 'info',
            fnorm = 'fnorm',
            nfev = 'nfev',
            p_val = MatrixAccess('p_val'),
            )
        base["nonlin_mat_list"] = self.struct.get_initializer(ini)
        self.glob = Namespace()
        base["namespace"] = neq.namespace
        base["global_data_def"] = self.glob
        return base

    def generate(self, d):
        base = self.setup(d)
        d = base.copy()
        neq = self.neq
        func_t, solv_t = self.method_templates[self.solver_dict["method"]]
        if isinstance(neq, dk_simulator.PartitionedNonlinEquations):
            of = NonlinFunctionCC(self.glob, neq, self.extra_sources)
            on = NonlinSolverCC(base, self.glob, neq, self.solver_dict)
        else:
            on = NonlinSolver(base, self.glob, neq, self.solver_dict)
            of = NonlinFunction(self.glob, neq, on)
        if func_t is not None:
            d["fcn_def"] = of.generate(func_t)
        d["nonlin_def"] = on.generate(solv_t)
        d["par_p"] = VectorAccess("p", param=True, block=self.pblockV)
        d["par_v"] = VectorAccess("v", param=True, block=self.blockV)
        return dk_templates.c_template_nonlin_solver.render(d)


class NonlinChained(NonlinCode):

    def __init__(self, s, neq):
        NonlinCode.__init__(self, s, neq, None, None)

    def generate(self, d):
        d = self.setup(d)
        self.glob.add(MatrixDefinition('K', self.neq.eq.K))
        template = dk_templates.c_template_nonlin_chained
        l = []
        l.append("%s = %s;\n" % (
            VectorAccess('p_val', param=True, block=self.neq.p_slice),
            VectorAccess('p', param=True, block=self.neq.p_slice),
            ))
        g_nn = self.neq.eq.nonlin.nn
        p_old_def = MatrixDefinition("p_old", rows=g_nn, cols=1, pointer=True)
        local_ns = Namespace()
        local_ns.add(p_old_def)
        p_old = VectorAccess(p_old_def)
        p2_def = MatrixDefinition("p2", rows=g_nn, cols=1)
        local_ns.add(p2_def)
        p2 = VectorAccess(p2_def, block=self.neq.p_slice)
        l += local_ns.generate_lines()
        l.append("int ret = 0;\n")
        l.append("p2 = *par.p;\n")
        l.append("p_old = par.p;\n")
        l.append("par.p = &p2;\n")
        for nlin in self.neq.subblocks:
            st = nlin.p_slice.start
            if st:
                l.append("p2.segment<%(ln)d>(%(st)d) += K.block<%(ln)d,%(st)d>(%(st)d,0) * (*par.v).head<%(st)d>();\n"
                         % dict(ln=nlin.p_slice.stop-st, st=st))
            l.append("ret = %s::nonlin_solve(par);\n" % nlin.namespace)
            l.append("if (ret != 0) {\n")
            l.append("    par.p = p_old;\n")
            l.append("    return ret;\n")
            l.append("}\n")
        l.append("par.p = p_old;\n")
        l.append("return 0;\n")
        d["chained_code"] = join_with_indent(l)
        return template.render(d)


class TableCode(object):

    def __init__(self, struct, neq):
        self.struct = struct
        self.neq = neq

    def generate(self, d):
        neq = self.neq
        base = {}
        base["dev_interface"] = d["dev_interface"]
        g_nonlin = neq.eq.nonlin
        base["g_nn"] = g_nonlin.nn
        base["g_nni"] = g_nonlin.nni
        base["g_nno"] = g_nonlin.nno
        base["npl"] = neq.eq.get_npl()
        if neq.v_slice:
            nn = base["nn"] = neq.nn
            nni = base["nni"] = neq.nni
            nno = base["nno"] = neq.nno
            self.blockV = neq.v_slice
            self.pblockV = neq.p_slice
            self.iblockV = neq.i_slice
            base["blockV"] = VectorAccess.block_expr(neq.v_slice)
            base["pblockV"] = VectorAccess.block_expr(neq.p_slice)
            base["iblockV"] = VectorAccess.block_expr(neq.i_slice)
        else:
            base["nn"] = nn = neq.nn
            base["nni"] = nni = neq.nni
            base["nno"] = nno = neq.nno
            self.blockV = None
            base["blockV"] = ""
            if nn != nni:
                self.pblockV = slice(0, nni)
                base["pblockV"] = VectorAccess.block_expr([0, nni])
            else:
                self.pblockV = None
                base["pblockV"] = ""
            if nn != nno:
                base["iblockV"] = VectorAccess.block_expr([0, nno])
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
        base["nonlin_mat_list"] = self.struct.get_initializer(ini)
        self.glob = Namespace()
        d = base.copy()
        d["namespace"] = neq.namespace
        d["global_data_def"] = self.glob
        d["par_p"] = VectorAccess("p", param=True, block=self.pblockV)
        d["par_v"] = VectorAccess("v", param=True, block=self.iblockV)
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
        if not isinstance(res, VariableAccess):
            res = MatrixAccess(res)
        if not isinstance(var, VariableAccess):
            var = MatrixAccess(var)
        self.glob.add(MatrixDefinition(var, var_data))
        self.glob.add(MatrixDefinition(res, rows=var_data.shape[0], cols=var_data.shape[1]))
        s = "%s = %s" % (res, var)
        if t is None:
            return s + ";\n"
        if u_data is not None:
            self.glob.add(MatrixDefinition(u, u_data))
        return s + " - %s * %s;\n" % (t, u)

    def generate(self, struct):
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
            Mx_mat = eq.get_Mx()
            m = MatrixDeclaration('Mx', rows=Mx_mat.shape[0], cols=Mx_mat.shape[1])
            struct.add(m)
            Mx = MatrixAccess(m, param=True)
            lines.append(self.trans_line(Mx, 'Mx', Mx_mat, t, 'UR', eq.get_UR()))
            m = MatrixDeclaration('Mxc', rows=eq.Bc.shape[0], cols=1)
            struct.add(m)
            Mxc = VectorAccess(m, param=True)
            lines.append(self.trans_line(Mxc, 'Mxc', eq.Bc, t, 'Ucv', eq.Ucv.T))
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
        Mo_mat = eq.get_Mo()
        m = MatrixDeclaration('Mo', rows=Mo_mat.shape[0], cols=Mo_mat.shape[1])
        struct.add(m)
        Mo = MatrixAccess(m, param=True)
        lines.append(self.trans_line(Mo, 'Mo', Mo_mat, t, 'UR', eq.get_UR()))
        m = MatrixDeclaration('Moc', rows=eq.Ec.shape[0], cols=1)
        struct.add(m)
        Moc = VectorAccess(m, param=True)
        lines.append(self.trans_line(Moc, 'Moc', eq.Ec, t, 'Ucv', eq.Ucv.T))
        if eq.nonlin and eq.nonlin.nni:
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
            Mp_mat = eq.get_Mp()
            struct.add(MatrixDeclaration('Mp', rows=Mp_mat.shape[0], cols=Mp_mat.shape[1]))
            lines.append(self.trans_line(MatrixAccess('Mp', param=True, pointer=False), 'Mp', Mp_mat, t, 'UR.block<%d, %d>(0, 0)' % (eq.np, eq.mp_cols), None))
            struct.add(MatrixDeclaration('Mpc', rows=eq.nonlin.Hc.shape[0], cols=1))
            lines.append(self.trans_line(VectorAccess('Mpc', param=True, pointer=False), 'Mpc', eq.nonlin.Hc, t, 'Ucv', eq.Ucv.T))
            struct.add(MatrixDeclaration('K', rows=eq.K.shape[0], cols=eq.K.shape[1]))
            mp_cols = eq.get_mp_cols()
            lines.append(self.trans_line(MatrixAccess('K', param=True, pointer=False), 'K', eq.K, t, 'UR.block<%d, %d>(0, %d)' % (eq.np, eq.get_mx_cols()-mp_cols, mp_cols), None))
        d["update_pot"] = join_with_indent(lines)
        return d


class LinearCode(object):

    def __init__(self, glob, eq):
        self.glob = glob
        self.eq = eq

    def generate(self):
        eq = self.eq
        param = bool(eq.np)
        Mp = MatrixAccess('Mp', param=param, pointer=False)
        Mo = MatrixAccess('Mo', param=param, pointer=False)
        Moc = VectorAccess('Moc', param=param, pointer=False)
        Mx = MatrixAccess('Mx', param=param, pointer=False)
        Mxc = VectorAccess('Mxc', param=param, pointer=False)
        d = {}
        if eq.nonlin and eq.nn != eq.nonlin.nni:
            pblock = slice(0, eq.nonlin.nni)
        else:
            pblock = None
        d["m_cols"] = eq.get_mx_cols()
        d["gen_mp"] = gen_linear_combination(
            self.glob, VectorAccess('mp',block=pblock), 'dp', Mp, eq.get_Mp())
        d["gen_xn"] = gen_linear_combination(
            self.glob, 'xn', 'd', Mx, eq.get_Mx(), Mxc, eq.Bc)
        d["gen_xo"] = gen_linear_combination(
            self.glob, 'xo', 'd', Mo, eq.get_Mo(), Moc, eq.Ec)
        d["gen_xo_float"] = gen_linear_combination(
            self.glob, 'xo', 'd', Mo, eq.get_Mo(), cast="float")
        return d


class NonlinEq(object):

    def __init__(self, nn, nni, nno, np, npl, K, CZ, f, U, Hc, Mi, Kn):
        self.nn = nn
        self.nni = nni
        self.nno = nno
        self.np =  np
        self.npl =  npl
        self.K = K
        self.CZ = CZ
        self.f = f
        self.U = U
        self.Hc = Hc
        self.Mi = Mi
        self.Kn = Kn


class LV2_Port_List(object):

    def __init__(self, pot_attr, pot, eq):
        self.pot_attr = pot_attr
        self.pot = pot
        self.ni = eq.ni
        self.no = eq.no

    def port_count(self):
        return self.ni + self.no + len(self.pot_attr)

    def __len__(self):
        return self.ni + self.no + len(self.pot_attr)

    def __iter__(self):
        idx = 0
        max_idx = len(self) - 1
        for i in range(self.ni):
            yield dict(
                type_list="lv2:AudioPort , lv2:InputPort",
                index = idx,
                symbol = "in%d" % i,
                name = "In%d" % i,
                control_index = -1,
                separator = "," if idx == max_idx else "",
                )
            idx += 1
        for i in range(self.no):
            yield dict(
                type_list="lv2:AudioPort , lv2:OutputPort",
                index = idx,
                symbol = "out%d" % i,
                name = "Out%d" % i,
                control_index = -1,
                separator = "," if idx == max_idx else "",
                )
            idx += 1
        for i, row in enumerate(self.pot_attr):
            var = row[0]
            name = row[1]
            yield dict(
                type_list="lv2:InputPort , lv2:ControlPort",
                index = idx,
                symbol = var,
                name = name,
                default = self.pot.get(var, 0.5),
                minimum = 0.0,
                maximum = 1.0,
                control_index = i,
                separator = "," if idx == max_idx else "",
                )
            idx += 1


class CodeGenerator(object):

    def __init__(self, eq, solver_dict, solver_params, pot, pot_list, pot_func, pot_attr, Pv, extra_sources):
        self.eq = eq
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

    @staticmethod
    def walk_eqs(nlin):
        yield nlin
        if nlin.__class__ is dk_simulator.NonlinEquations:
            return
        for bl in nlin.subblocks:
            for neq in CodeGenerator.walk_eqs(bl):
                yield neq

    def gen_nonlin(self, nonlin, s, d, complist, code):
        eq = self.eq
        if isinstance(nonlin, dk_simulator.PartitionedNonlinEquations):
            for i, nlin in enumerate(nonlin.subblocks):
                #spar = solver_set_defaults({} if self.solver_params is None else self.solver_params[i])
                self.gen_nonlin(nlin, s, d, complist, code)
            if self.solver_dict["method"] == "table":
                solver = self.solver_dict.copy()
                solver["method"] = "hybrCC"
            else:
                solver = self.solver_dict
            code.append(NonlinCode(s, nonlin, solver, self.extra_sources).generate(d))
        elif isinstance(nonlin, dk_simulator.ChainedNonlinEquations):
            for i, nlin in enumerate(nonlin.subblocks):
                #spar = solver_set_defaults({} if self.solver_params is None else self.solver_params[i])
                self.gen_nonlin(nlin, s, d, complist, code)
            solver = self.solver_dict
            code.append(NonlinChained(s, nonlin).generate(d))
        else:
            complist.append(dict(
                name = nonlin.name,
                namespace = nonlin.namespace,
                pins = ",".join(dk_simulator.Parser.format_element(v) for v in nonlin.pins),
                v_slice = nonlin.v_slice,
                p_slice = nonlin.p_slice,
                i_slice = nonlin.i_slice,
                ))
            if self.solver_dict["method"] == "table":
                code.append(TableCode(s, nonlin).generate(d))
            else:
                code.append(NonlinCode(s, nonlin, self.solver_dict, None).generate(d))

    def add_dict(self, d):
        eq = self.eq
        s = Structure("nonlin_param")
        par_ini = {}
        glob = Namespace()
        if self.have_constant_matrices:
            d["update_pot"] = ""
        else:
            d.update(UpdateMatrix(glob, eq, self.pot, self.pot_list, self.pot_func, self.Pv).generate(s))
        if eq.nonlin and eq.nonlin.nno:
            for k, v in self.solver_dict.items():
                d["solver_"+k] = v
            s.add(MatrixDeclaration('p', rows=eq.nn, cols=1, pointer=True))
            s.add(MatrixDeclaration('i', rows=eq.nn, cols=1, pointer=True))
            s.add(MatrixDeclaration('v', rows=eq.nn, cols=1, mapping=True, pointer=True, aligned=False))
            s.add_nonlin_info()
            s.add_minmax_info(eq.nonlin.nni)
            par_ini.update(dict(
                v = '&g_v',
                info = '&g_info',
                fnorm = '0',
                nfev = '&g_nfev',
                p = '0',
                i = '0',
                p_val = '0',
                ))
            ini = dict(
                p = MatrixAccess('mp'),
                i = MatrixAccess('mi'),
                v = '&g_v',
                info = '&g_info',
                fnorm = '&fnorm',
                nfev = '&g_nfev',
                p_val = MatrixAccess('p_val'),
                )
            d["nonlin_mat_list_calc"] = s.get_initializer(ini)
            for i, neq in enumerate(self.walk_eqs(eq.nonlin)):
                if i == 0:
                    neq.namespace = "nonlin"
                else:
                    neq.namespace = "nonlin_%d" % (i-1)
            complist = []
            code = []
            self.gen_nonlin(eq.nonlin, s, d, complist, code)
            d["nc"] = len(complist)
            d["components"] = complist
            d["nonlin_code"] = "".join(code)
            if eq.nn != eq.nonlin.nno:
                d["iblock"] = VectorAccess.block_expr([0, eq.nonlin.nno])
            else:
                d["iblock"] = ""
        else:
            d["nonlin_code"] = ""
            d["nc"] = 0
            d["iblock"] = ""
        d["nonlin_mat_list"] = s.get_initializer(par_ini)
        d.update(self.pot_code())
        d["struct_def"] = s
        d.update(LinearCode(glob, eq).generate())
        d["global_matrices"] = glob
        d["add_npl"] = 0
        d["DKPlugin_fields"] = ""
        d["DKPlugin_init"] = ""
        d["process_add"] = ""
        return d

    def generate(self, d):
        d = self.add_dict(d)
        d["lv2_ports"] = LV2_Port_List(self.pot_attr, self.pot, self.eq)
        out = dict(c_source = dk_templates.c_template_top.render(d))
        plugindef = d["plugindef"]
        if plugindef.lv2_plugin_type:
            out["manifest.ttl"] = dk_templates.lv2_manifest.render(d)
            out["%s.ttl" % plugindef.lv2_versioned_id] = dk_templates.lv2_ttl.render(d)
        return out
