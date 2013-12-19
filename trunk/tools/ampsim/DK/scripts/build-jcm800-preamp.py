import sys; sys.path.append(".")
from models import *
from analog import *
from codelib import MatrixDefinition
from scipy.optimize import minimize

def calc_shape_transform(fnum, resnum, minmax, c):
    p0 = np.zeros(c.sim_py.eq.nni)
    end = c.sim_py.eq.blocklist[-1].stop
    Kn = np.concatenate(c.sim_py.eq.Kn, axis=0)
    p0[:end] = ((c.sim_py.p0 + c.sim_py.eq.Hc0)[:6] + Kn * np.matrix(c.sim_py.v00[6:]).T).A1
    p0[end:] = c.sim_py.p0[6:].A1
    argstart = fnum*2
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
    ro = numpy.zeros((3,3))
    for i, v in enumerate(r.T):
        ro[i] = numpy.polyfit(ap2,v,2)
    return ro

def shape_transform_matrices(c):
    o = numpy.zeros((6, 3, 3))
    o[0] = calc_shape_transform(0, 0, c.minmax, c)
    o[1] = o[0]
    o[2] = calc_shape_transform(1, 0, c.minmax, c)
    o[3] = o[2]
    o[4] = calc_shape_transform(2, 0, c.minmax, c)
    o[5] = o[4]
    l = []
    for i in range(o.shape[1]):
        for j in range(3):
            sn = "S%sm%d" % (['p','s','a'][j], i)
            l.append(MatrixDefinition(sn, array=True, value=o[:,i,j]))
    return l

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
c.set_module_id("JCM800Pre")
c.set_netlist(circ.Preamp_test.S, circ.Preamp_test.V)
#c.add_element(R('cc1'), (6, GND), 1e12)
#c.add_element(R('cc2'), (13, GND), 1e12)
c.remove_element("Cm1")
#c.remove_element("Cm2")
#c.remove_element("Cm3")
c.backward_euler = True
c.partition = True
c._ensure_eq()
if 1:
    c1 = Circuit(copy_from=c)
    c1.linearize()
    c1._ensure_eq()
    T, Ti, hsv = dk_simulator.get_state_transform(c1.eq.A0, c1.eq.B0, c1.eq.D0, tol=1e-9)
    c.eq.make_eq(c.parser, True, T, Ti)
c.build_verbose = True
c.set_tempdir("gencode")
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
    c.E = np.array([1e0, 1e0, 1e-4, 1e-3, 1e0, 2e-1])
    c.max_homotopy_iter = 10
    #c.table_datatype = "float"
    c.set_use(SIM_TABLE)
    c._ensure_table_source()
    x0 = np.array([
        1.21066261e+02,   2.83936328e+00,  -5.32394069e+02,  -1.57911412e+02,
        -2.07897605e+03,  -9.75459737e-01,  1.04929150e+01,   4.71551189e+00])
    c.sim_py.x0 = x0
    c.table_source["shape_transform"] = shape_transform_matrices(c)
    c.set_solver(dict(factor=1e5, xtol=1e-1, maxfev=12))
    c.post_filter = highpass_as_postfilter(20, c.FS)
#c.stream(s)
#abl=2
#pylab.plot(c.last_signal.timeline[100+abl:], np.diff(c.last_output, abl, axis=0)[100:])
#pylab.show()
c.deploy()
