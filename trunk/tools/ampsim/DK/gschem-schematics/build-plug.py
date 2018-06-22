import os
import argparse,sys
sys.path.append(".")

parser = argparse.ArgumentParser(description='Build script for guitarix plugins.')
parser.add_argument('-i','--input', help='Input file name [REQUIRED]',required=True)
parser.add_argument('-n','--name',help='Name for plugin [OPTIONAL]', required=False)
parser.add_argument('-s','--shortname',help='Shortname for plugin [OPTIONAL]', required=False)
parser.add_argument('-d','--description',help='Description for plugin [OPTIONAL]', required=False)
parser.add_argument('-c','--category',help='Category for plugin [OPTIONAL]', required=False)
parser.add_argument('-m','--module_id',help='Module ID for plugin [OPTIONAL]', required=False)
parser.add_argument('-p','--prefilter',help='prefilter for plugin [OPTIONAL]', required=False)
parser.add_argument('--plot',help='frequency plot from the circuit [OPTIONAL]',action="store_true", required=False)
parser.add_argument('--build',help='build guitarix plugin from the circuit [OPTIONAL]',action="store_true", required=False)
args = parser.parse_args()
 
## show values ##
schema = args.input

os.chdir("../")
workfile="gschem-schematics/"+schema
name = args.name
shortname = args.shortname
description = args.description
category = args.category
module_id = args.module_id
prefilter = args.prefilter
do_plot = args.plot
gx_build = args.build
print ("Input file: %s" % args.input )
del sys.argv[1:]

from analog import *

path = "tmp"

if not module_id:
	module_id = schema.split('.')[0].lower()
print ("module_id: %s" % module_id )
mod = os.path.join(path, module_id+".so")


def calc_highpass_f0(c1, c2, pot):
    from scipy.optimize import curve_fit
    sig = Signal()
    s = c1.make_signal_vector(sig(0.01*sig.impulse(), timespan=1))
    f0 = numpy.zeros(11)
    fl = numpy.logspace(numpy.log10(s.start_freq), numpy.log10(s.stop_freq), 200)
    w = 2 * numpy.pi * fl / s.fs
    for i, Level in enumerate(numpy.linspace(0, 1, 11)):
        c1.set_pot_variable(pot, Level)
        c1.stream(s)
        h1 = s.get_spectrum(c1.last_output[:,0], w)

        c2.set_pot_variable(pot, Level)
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

def freqplot(c1,name):
    sig = Signal()
    s = c1.make_signal_vector(sig(sig.impulse(), timespan=1))
    c1.stream(s)
    s.plot_spectrum(c1.last_output)
    ax = pylab.axes()
    ax.grid()
    ax.yaxis.set_major_formatter(pylab.FormatStrFormatter('%d dB'))
    ax.xaxis.set_major_formatter(pylab.FormatStrFormatter('%d Hz'))
    pylab.title(name)
    pylab.xlabel('Frequency')
    pylab.ylabel('Magnitude')
    pylab.show()


set_log_level(INFO)
# create plugin
c1 = Circuit()
c1.plugindef = dk_simulator.PluginDef(module_id)
if not name:
	name = module_id
c1.plugindef.name = name
if not shortname:
	shortname = name
c1.plugindef.shortname = shortname
if not description:
	description = name
c1.plugindef.description = description
if not category:
	category = "Extern"
c1.plugindef.category = category
c1.plugindef.id = module_id
c1.set_module_id(module_id)
c1.read_gschem(workfile)
c1.show_status()

# use to calculate dc blocker
#c1.linearize("Triode1", "Pentode3", keep_dc=False)
#c1.linearize("Triode2", "Pentode4", keep_dc=False)
#c1.print_filter_coeffs()
#c0 = Circuit(c1)
#c1.remove_element("C1")
#c1.join_net("V2", "V1")
#f0 = calc_highpass_f0(c0, c1, "Volume_a")
#print ("calc_highpass: %s" % f0 )
#prefilter = "fi.dcblockerat(%s)" % f0

c1.print_netlist()

if do_plot:
    freqplot(c1,name)

if gx_build or not do_plot:
    print ("build plugin from: %s" % args.input)
    if not prefilter:
        c1.create_faust_module()
    else:
        print prefilter
        c1.create_faust_module(pre_filter=prefilter)

#c1.deploy(".")
