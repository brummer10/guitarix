import sys; sys.path.append(".")
import os ; os.chdir("../")
from models import *
from analog import *
from codelib import MatrixDefinition
import generate_code, re
from scipy.optimize import minimize, curve_fit
from scipy.signal import freqz

class Filter(object):

    def __init__(self, fs):
        self.fs = fs
        self.calc_coeffs()

    def freqz(self, R1, R5, C4, C5, P6v, w):
        args = (R1, R5, C4, C5, P6v)
        return freqz([v(*args) for v in self.b], [v(*args) for v in self.a], w)[1]

    def calc_coeffs(self):
        self.c = Circuit()
        S = ((R(5), 7, 8),
             (C(4), 7, 88),
             (R(1), 88, 9),
             (C(5), 8, 9),
             (P(6), GND, 8, 9),
             (IN, 7),
             (OUT, 9),
             )
        R1, R5, C4, C5, P6v = sp.symbols("R1,R5,C4,C5,P6v")
        V = {R(1): R1 * (1-P6v),
             R(5): R5 * (1-P6v),
             C(4): C4 * (1-P6v),
             C(5): C5 * (1-P6v),
             P(6): 1e6,
            }
        self.c.set_netlist(S, V)
        self.c._ensure_filter(symbolic=False)
        self.c.sim_filter.subst_var_default = dict(R1=1e4,R5=470e3,C4=470e-12,C5=1e-9,P6v=0.5)
        b, a = self.c.sim_filter.get_z_coeffs(samplerate=self.fs)
        args = (R1, R5, C4, C5, P6v)
        self.b = [sp.lambdify(args, v) for v in b]
        self.a = [sp.lambdify(args, v) for v in a]

    def get_coeffs(self, R1, R5, C4, C5):
        b, a = self.c.sim_filter.get_z_coeffs(as_expr=False)
        l = []
        for i, v in enumerate(b[0]+a[0]):
            s = set()
            for j, p in v:
                p = p.subs(dict(R1=R1,R5=R5,C4=C4,C5=C5))
                p = re.sub(r'([a-zA-Z0-9]+)\*\*(\d+)', r'pow(\1,\2)', str(p))
                j = j[0]
                l.append('    self.K%d(%d) = %s;' % (j, i, p))
                s.add(j)
            for j in sorted(set(range(max(s)+1))-s):
                l.append('    self.K%d(%d) = 0.0;' % (j, i))
        return l


class CompareFilter(object):

    def __init__(self):
        self.sig = Signal()
        self.c = Circuit()
        self.c.set_netlist(circ.Preamp_test.S, circ.Preamp_test.V)
        self.c.linearize()
        self.sr = self.sig(self.sig.sweep(), timespan=1)
        self.fr = (50,20000)
        self.f = numpy.logspace(numpy.log10(self.fr[0]), numpy.log10(self.fr[1]), 200)
        self.flt = Filter(self.c.FS)
        self.rg = np.logspace(0, -3, 6)
        self.c.set_pot_variable('P6v', 1.0)
        self.c.stream(self.sr)
        self.base = self.c.last_signal.get_spectrum(
            self.c.last_output, 2 * numpy.pi * self.f / self.c.FS)
        self.base = 20 * numpy.log10(abs(self.base))

    def get_coeffs(self, R1, R5, C4, C5):
        return self.flt.get_coeffs(R1, R5, C4, C5)

    def calc_highpass_f0(self, P6v, xdata, ydata):
        omega = numpy.pi * xdata / 96000
        p = [ 100e3, 470.e3,  470.e-12,  1.e-9]
        def f(w, R1, R5, C4, C5):
            return 20*numpy.log10(abs(self.flt.freqz(R1, R5, C4, C5, P6v, w)))
        p, cov = curve_fit(f, omega, ydata, p)
        return p

    def calc_param(self, rg):
        params = []
        for i, p in enumerate(rg):
            self.c.set_pot_variable('P6v', p)
            self.c.sim_c(numpy.zeros((self.c.FS,1)))
            self.c.stream(self.sr)
            h = self.c.last_signal.get_spectrum(
                self.c.last_output, 2 * numpy.pi * self.f / self.c.FS)
            h = 20 * numpy.log10(abs(h)) - self.base
            params.append(self.calc_highpass_f0(p, self.f, h))
        return params

    def plotcurves(self, param):
        for i, p in enumerate(self.rg):
            self.c.set_pot_variable('P6v', p)
            self.c.sim_c(numpy.zeros((self.c.FS,1)))
            lb = "%.1g" % p
            self.c.stream(self.sr)
            h = self.c.last_signal.get_spectrum(
                self.c.last_output, 2 * numpy.pi * self.f / self.c.FS)
            pylab.semilogx(self.f, 20*numpy.log10(abs(h))-self.base, label="c:"+lb)
            h = self.flt.freqz(*param, P6v=p, w=numpy.pi*self.f/self.c.FS)
            pylab.semilogx(self.f, 20*numpy.log10(abs(h)), label="f:"+lb)
        pylab.xlim(*self.fr)
        pylab.ylim(-60, 0)
        pylab.grid(which="both")
        pylab.legend(loc='lower right', ncol=2)
        pylab.show()


def calc_shape_transform(fnum, resnum, minmax, c):
    p0 = c.sim_py.p0.A1
    argstart = fnum*2
    if minmax[argstart+1,0] == minmax[argstart+1,1]:
        return numpy.array([[0.,0.,0.],[0.,0.,0.],[1.,0.,1.]])
    x = numpy.linspace(minmax[argstart,0], minmax[argstart,1], 200)
    p1 = float(p0[argstart+1])
    ap2 = numpy.linspace(minmax[argstart+1,0], minmax[argstart+1,1], 5)
    m0 = [1,0,1]
    r = numpy.zeros((len(ap2), 3))
    a = numpy.zeros((len(x),2))
    def f(x, p):
        a[:,0] = x
        a[:,1] = p
        return c.sim_c.c_calc_comp[fnum](a)
    for i, p2 in enumerate(ap2):
        def func(m):
            return numpy.sum(((m[0]*f(m[1]+m[2]*x,p1)) - f(x, p2)) ** 2)
        meth = "Powell"
        res = minimize(func, m0, method=meth)
        r[i] = res.x
        m0 = res.x
    return numpy.polyfit(ap2, r, 2)

def shape_transform_matrices(c):
    o = numpy.zeros((3, 3, 3))
    o[0] = calc_shape_transform(0, 0, c.minmax, c)
    o[1] = calc_shape_transform(1, 0, c.minmax, c)
    o[2] = calc_shape_transform(2, 0, c.minmax, c)
    l = []
    for i in range(o.shape[2]):
        for j in range(3):
            sn = "S%sm%d" % (['p','s','a'][j], i)
            l.append(MatrixDefinition(sn, array=True, value=o[:,j,i]))
    return l

class CodeGenerator(generate_code.CodeGenerator):
    def add_dict(self, d):
        self.pot_attr = self.pot_attr + [("P6v", "Volume", 5, False, None)]
        d = generate_code.CodeGenerator.add_dict(self, d)
        fl = CompareFilter()
        params = fl.calc_param(fl.rg[2:3])
        l = ["self.X.setZero();",
             "self.Y.setZero();",
             "unsigned int fs = samplingFreq;"]
        l.extend(fl.get_coeffs(*params[0]))
        d.overwrite("filter_init", "\n   ".join(l))
        fields = ["Array<double, %d, 1> %s;" % r for r in
                  ((6,"K0"),(6,"K1"),(6,"K2"),(6,"K3"),(6,"K4"),(6,"K5"),(6,"Y"),(6,"X"))]
        d.overwrite("DKPlugin_fields", "\n    ".join(fields))
        d.overwrite("add_npl", 1)
        d.overwrite("DKPlugin_init", ", K0(), K1(), K2(), K3(), K4(), K5(), Y(), X()")
        d.overwrite("process_add", """\
    for (int j = 0; j < n; j++) {
        self.pots_last[0] = 0.01 * t[0] + (1-0.01) * self.pots_last[0];
        double P6v = self.pots_last[0];
        Array<double, 6, 1> AB;
        AB = (((((self.K5 * P6v + self.K4) * P6v + self.K3) * P6v + self.K2) * P6v + self.K1) * P6v + self.K0);
        double out;
        out = ((u[j] * AB(0) + self.X(0) * AB(1) + self.X(1) * AB(2)) - (self.Y(0) * AB(4) + self.Y(1) * AB(5))) / AB(3);
        self.Y(1) = self.Y(0);
        self.Y(0) = out;
        self.X(1) = self.X(0);
        self.X(0) = u[j];
        o[j] = out;
    }
    u = o;
""")
        return d

# hand-optimized, unused, maybe out of date:
cc_func_code = """
    Array<creal, 2, 1> PP1;
    PP1 << pt(1), pt(5);
    Array<creal, 2, 1> PP0;
    PP0 << pt(0), pt(4);
    pt.head<2>() = (Spm1 * PP1 + Ssm1) * PP1 + Sam1 + ((Spm2 * PP1 + Ssm2) * PP1 + Sam2) * PP0;
    Array<creal, 6, 1> res;
    splinedata<unsigned short>::splev_pp<4>(&AmpData::nonlin_1::sd.sc[0], &pt(2), &res(2));
    splinedata<unsigned short>::splev_pp<4>(&AmpData::nonlin_1::sd.sc[1], &pt(2), &res(3));

    splinedata<unsigned short>::splev_pp<4>(&AmpData::nonlin_0::sd.sc[0], &pt(0), &res(0));
    splinedata<unsigned short>::splev_pp<4>(&AmpData::nonlin_0::sd.sc[1], &pt(0), &res(4));

    splinedata<unsigned short>::splev_pp<4>(&AmpData::nonlin_2::sd.sc[0], &pt(1), &res(1));
    splinedata<unsigned short>::splev_pp<4>(&AmpData::nonlin_2::sd.sc[1], &pt(1), &res(5));

    pt.head<2>() = ((Spm0 * PP1 + Ssm0) * PP1 + Sam0) * res.head<2>();
    pt.tail<2>() = ((Spm0 * PP1 + Ssm0) * PP1 + Sam0) * res.tail<2>();

    (*par.i).head<6>() << pt(0), pt(4), res(2), res(3), pt(1), pt(5), v[0], v[1];
"""

def highpass_as_postfilter(f0, FS):
    w0 = numpy.pi * f0 / FS
    b0 = 1 / (1 + w0)
    a1 = (1 - w0) * b0
    return (
        "{\n"
        "            static double y;\n"
        "            static double xm1;\n"
        "            y = %s * (buf[j] - xm1) + %s * y;\n"
        "            xm1 = buf[j];\n"
        "            buf[j] = y;\n"
        "        }\n"
        % (b0, a1))

numpy.set_printoptions(linewidth=2000)
sig = Signal()
sr = sig(20*sig.sine(freq=150), timespan=1)
s = sig(0.15*sig.sine(freq=150), timespan=0.2)
c = Circuit(FS=96000)
mod_id = "JCM800Pre_DK"
c.set_module_id(mod_id)
c.plugindef = dk_simulator.PluginDef(mod_id)
c.plugindef.name = "JCM 800 Preamp DK"
c.plugindef.shortname = "JCM800Pre_DK"
c.plugindef.description = "DK Simulation of JCM 800 preamp circuit"
c.plugindef.category = "Distortion"
c.plugindef.namespace = "JCM800Pre_DK"
c.plugindef.lv2_plugin_type = "DKSimulatorPlugin"
c.build_script = sys.argv[0]
c.set_netlist(circ.Preamp_test.S, circ.Preamp_test.V)
c.backward_euler = True
c.transform_opts.partition = True
c.transform_opts.decompose = True
c.sys_reduce_tol = 1e-5
#c.add_element(R('cc1'), (6, GND), 1e12)
#c.add_element(R('cc2'), (13, GND), 1e12)
c.add_element(R(61), (8, 9), 0.2e6),
c.add_element(R(62), (9, GND), 0.8e6),
c.remove_element("P6")
c.remove_element("Cm1")
#c.remove_element("Cm2")
#c.remove_element("Cm3")
c.build_verbose = True
c.set_tempdir("dkbuild/jcm800")
c.keep_tempdir()
c.set_solver(dict(method='hybr', factor=1e5))
if 1:
    c.max_homotopy_iter = 10
    c.solver_params = [
        dict(method="hybr", factor=1e-1, max_homotopy_iter=10),
        dict(method="hybr", factor=1e-2, max_homotopy_iter=10),
        dict(method="hybr", factor=1e-1, max_homotopy_iter=10),
        ]
    c.basegrid = 6 * [ [[None, ('pp',4)], [None, None]], ]  # with shape transform
    c.stream(sig(0.0, samples=500))
    c.calc_range(sr)
    class CE(object):
        def __init__(self, atol, rtol):
            self.atol = atol
            self.rtol = rtol
        def __call__(self, f_intp, f_calc, f0):
            return abs(f_intp - f_calc) > self.atol + self.rtol * abs(f_calc - f0)
    c.E = [CE(2e-2, 5e-5), CE(1e-1, 5e-5), CE(1e-3, 5e-5),
           CE(1e-2, 5e-5), CE(1e-1, 5e-5), CE(1e-3, 5e-5)]
    c.max_homotopy_iter = 10
    c.set_use(SIM_TABLE)
    c._ensure_table_source()
    x0 = np.array([ -101.11169547,    -4.28127308,  -514.34759921,  -230.31382521,
                    -1133.65846006,    -4.20085902,   -20.3466745 ])
    c.sim_py.x0 = x0
    c.table_source["shape_transform"] = shape_transform_matrices(c)
    c.set_solver(dict(factor=1e5, xtol=1e-1, maxfev=12))
    c.post_filter = highpass_as_postfilter(20, c.FS)

c.code_generator = CodeGenerator
#c.build_guitarix_module(include_paths=["../../../src/headers"])
c.deploy()
