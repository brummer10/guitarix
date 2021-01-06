import os
import argparse,sys

parser = argparse.ArgumentParser(description='Build script for lv2 plugins.')
parser.add_argument('-i','--input', help='Input file name [REQUIRED]',required=True)
parser.add_argument('-n','--name',help='Name for plugin [OPTIONAL]', required=False)
parser.add_argument('-s','--shortname',help='Shortname for plugin [OPTIONAL]', required=False)
parser.add_argument('-d','--description',help='Description for plugin [OPTIONAL]', required=False)
parser.add_argument('-c','--category',help='Category for plugin [OPTIONAL]', required=False)
parser.add_argument('-m','--module_id',help='Module ID for plugin [OPTIONAL]', required=False)
parser.add_argument('-p','--prefilter',help='prefilter for plugin [OPTIONAL]', required=False)
args = parser.parse_args()
 
## show values ##
schema = args.input
workfile="./gschem-schematics/"+schema
name = args.name
shortname = args.shortname
description = args.description
category = args.category
module_id = args.module_id
prefilter = args.prefilter
print ("Input file: %s" % args.input )
del sys.argv[1:]

# set path 
scriptPath = os.path.realpath(os.path.dirname(sys.argv[0]))
os.chdir(scriptPath)
sys.path.append("../")

from analog import *

# set working directory
os.chdir(scriptPath+"/../")

# set path to build the dsp file to 
path = "tmp"

if not module_id:
	module_id = schema.split('.')[0].lower()
print ("module_id: %s" % module_id )
mod = os.path.join(path, module_id+".so")


def calc_highpass_f0(c1, c2):
    from scipy.optimize import curve_fit
    sig = Signal()
    s = c1.make_signal_vector(sig(0.01*sig.impulse(), timespan=1))
    f0 = numpy.zeros(11)
    fl = numpy.logspace(numpy.log10(s.start_freq), numpy.log10(s.stop_freq), 200)
    w = 2 * numpy.pi * fl / s.fs
    for i, Level in enumerate(numpy.linspace(0, 1, 11)):
        c1.set_pot_variable('Level', Level)
        c1.stream(s)
        h1 = s.get_spectrum(c1.last_output[:,0], w)

        c2.set_pot_variable('Level', Level)
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

#set_log_level(DEBUG)
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
#c1.linearize("T1", "T2", keep_dc=False)

#c0 = Circuit(c1)
#f0 = calc_highpass_f0(c0, c1)
#print ("calc_highpass: %s" % f0 )
print ("build plugin from: %s" % args.input)
if not prefilter:
    #c1.create_faust_module()
    dspfile = module_id+".dsp"
    dspfilepath = "./buildlv2/"
    dspfp = dspfilepath+dspfile
    c1.save_faust_code(filename=str(dspfp))
else:
    c1.create_faust_module(pre_filter=prefilter)

# finally build the lv2 bundle
import subprocess
os.chdir(scriptPath)
subprocess.check_call(['./make_lv2_bundle.sh -p ./ %s' % dspfile], shell=True)
