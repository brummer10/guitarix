import sys; sys.path.append(".")
import os ; os.chdir("../")
from models import *
from analog import *
from scipy.optimize import curve_fit

def calc_highpass_f0(c1, c2):
    sig = Signal()
    s = c1.make_signal_vector(sig(0.01*sig.impulse(), timespan=1))
    f0 = numpy.zeros(11)
    fl = numpy.logspace(numpy.log10(s.start_freq), numpy.log10(s.stop_freq), 200)
    w = 2 * numpy.pi * fl / s.fs
    for i, hotpotz in enumerate(numpy.linspace(0, 1, 11)):
        c1.set_pot_variable('hotpotz', hotpotz)
        c1.stream(s)
        h1 = s.get_spectrum(c1.last_output[:,0], w)

        c2.set_pot_variable('hotpotz', hotpotz)
        c2.stream(s)
        h2 = s.get_spectrum(c2.last_output[:,0], w)

        ydata = numpy.log(abs(h1/h2))
        e = numpy.exp(-1j*w)
        a1 = -1
        def f(e, a1):
            return numpy.log(abs((1-a1)/2 * (1 - e) / (1 + a1 * e)))
        res = curve_fit(f, e, ydata, a1)

        a1 = res[0][0]
        f0[i] = s.fs*(1 + a1)/(numpy.pi*(1 - a1))
    return numpy.mean(f0)

def highpass_as_prefilter(f0, FS):
    w0 = numpy.pi * f0 / FS
    b0 = 1 / (1 + w0)
    a1 = (1 - w0) * b0
    return (
        "static DTP_U y; {\n"
        "            static double xm1;\n"
        "            y = %s * (GET_U[0] - xm1) + %s * y;\n"
        "            xm1 = GET_U[0];\n"
        "        }\n"
        "#undef GET_U\n"
        "#define GET_U (&y)\n"
        % (b0, a1))

def build_module(FS, postfix, linear=False):
    c1 = Circuit(FS=FS)
    c1.build_script = sys.argv[0]
    c1.set_tempdir("gencode")
    c1.keep_tempdir()
    mod_id = "GCB_95%s" % postfix
    c1.set_module_id(mod_id)
    c1.plugindef = dk_simulator.PluginDef(mod_id)
    c1.plugindef.name = "GCB 95"
    c1.plugindef.description = "Linear filter simulating the GCB 95 crybaby circuit"
    c1.plugindef.category = "Guitar Effects"
    c1.set_netlist(circ.WahWah_test.S, circ.WahWah_test.V)
    c1.linearize(T(1), T(2), keep_dc=False)
    c1.remove_element("C2")
    c1.remove_element("R8")
    c1.join_net("V6", GND)
    c0 = Circuit(c1)
    c1.remove_element("C1")
    c1.join_net("V3", "V2")
    f0 = calc_highpass_f0(c0, c1)
    if linear:
        c1.create_faust_module(pre_filter="dcblockerat(%s)" % f0)
    else:
        c1.sig.timespan = 0.2
        #c1.grid_error_limit = 1e-1
        c1.input_amplitude = 3
        c1.pre_filter = highpass_as_prefilter(f0, c1.FS)
        c1.set_use(SIM_TABLE)
        c1.sim_c.set_variable("hotpotz", 1) # gives largest values for range calculation
        c1.deploy(".")

if __name__ == "__main__":
    set_log_level(INFO)
    build_module(44100, "", linear=True)
    build_module(44100, "_44")
    build_module(48000, "_48")
