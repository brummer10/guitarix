#!/usr/bin/env python

import os
from shutil import copy2
import argparse,sys
import re
sys.path.append(".")

parser = argparse.ArgumentParser(description='Build script for guitarix plugins.')
parser.add_argument('-i','--input', metavar='N', nargs='+', help='Input file(s) name [ONE REQUIRED]',required=True)
parser.add_argument('-n','--name',help='Name for plugin [OPTIONAL]', required=False)
parser.add_argument('-s','--shortname',help='Shortname for plugin [OPTIONAL]', required=False)
parser.add_argument('-d','--description',help='Description for plugin [OPTIONAL]', required=False)
parser.add_argument('-c','--category',help='Category for plugin [OPTIONAL]', required=False)
parser.add_argument('-m','--module_id',help='Module ID for plugin [OPTIONAL]', required=False)
parser.add_argument('-f','--prefilter',help='prefilter for plugin [OPTIONAL]', required=False)
parser.add_argument('-p','--plot',help='frequency plot from the circuit [OPTIONAL]',action="store_true", required=False)
parser.add_argument('-b','--build',help='build guitarix plugin from the circuit [OPTIONAL]',action="store_true", required=False)
parser.add_argument('-l','--buildlv2',help='build lv2 plugin from the circuit [OPTIONAL]',action="store_true", required=False)
parser.add_argument('-t','--table', metavar='N', type=int,help='build nonlinear response table from the N\'t circuit [OPTIONAL]', required=False)
parser.add_argument('-x','--sig_max', metavar='N', type=float, nargs='+', help='max signal send to build the nonlinear response table from the circuit [OPTIONAL]', required=False)
parser.add_argument('-/','--table_div', metavar='N', type=float, nargs='+', help='divider for nonlinear response table from the circuit [OPTIONAL]', required=False)

args = parser.parse_args()

os.chdir("../")
del sys.argv[1:]

from analog import *
import circ_table_gen as ci


a = 0
b = 0

dspfile = ""
dspfileui = ""
dspname = ""
fdata = ""
fuidata = ""

name = args.name
shortname = args.shortname
description = args.description
category = args.category
prefilter = args.prefilter
do_plot = args.plot
gx_build = args.build
lv2_build = args.buildlv2
build_table = args.table
table_div = args.table_div
sig_max = args.sig_max

if name:
    modulename = name.lower()
else:
    schema = args.input[a]
    modulename = schema.split('.')[0].lower()

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

def generate_nonlin_table(c1):
    v = ci.Circ_table(modulename, c1.S,c1.V, sig_max, table_div)
    parser = dk_simulator.Parser(v.S, v.V, v.FS)
    p = dk_simulator.get_executor(
    modulename, parser, v.solver, '-p', c_tempdir='/tmp', c_verbose='--c-verbose',
    c_debug_load='', linearize='', c_real=("double"))
    y = p(v.signal())
    v.generate_table(p, y,"")
    v.plot(p,y)

def write_final_file(dspfile,fdata,dspfileui,fuidata):
    process_line = "\nprocess = "
    for x in xrange(1,a+1,1):
        process_line += ' p%s ' % x
        if a>x :
            process_line += ':'
        else :
            process_line += ';'
    fdata += process_line

    with open(dspfile, 'w') as f:
      f.write(fdata)
    f.close()

    with open(dspfileui, 'w') as f:
      f.write(fuidata)
    f.close()

def generate_gx_plugin(arg, dspfile, nonlin=None):
    if nonlin :
        print ("build nonlin gx_plugin from: %s" % arg)
    else :
        print ("build gx_plugin from: %s" % arg)
    datatype="double"
    pgm = os.path.abspath("../../build-faust")
    opts = " " if datatype == "float" else ""
    os.system("%s %s -c -k %s" % (pgm, opts, dspfile))

def generate_lv2_plugin(arg, dspfile, modulename, nonlin=None):
    if nonlin :
        print ("build nonlin lv2_plugin from: %s" % arg)
    else :
        print ("build lv2_plugin from: %s" % arg)
    p = os.getcwd()
    os.chdir("buildlv2/")
    pgm = os.path.abspath("./make_lv2_X11bundle.sh")
    os.system("%s -p ../%s -n  %s" % (pgm, dspfile, name ))
    # copy table to bundle
    if nonlin :
        src1 = '../dkbuild/%s_table.h' %  modulename
        dst1 = 'gx_%s.lv2/dsp/' % modulename
        copy2(src1, dst1)
    os.chdir('gx_%s.lv2' % modulename)
    os.system('make uninstall && make && make install')
    os.chdir(p)


# generate faust code and nonlin table
for sch in args.input:
    a +=1
    schema = args.input[a-1]
    print ("\nInput file %s: %s" % (a, args.input[a-1]))

    workfile="gschem-schematics/"+schema
    path = "tmp"

    module_id = args.module_id
    if not module_id:
        module_id = modulename
    print ("module_id: %s" % module_id )

    dst = 'dkbuild/%s/' % modulename
    dspname = dst+modulename
    dspfile = dspname+".dsp"
    dspfileui = dspname+"_ui.cc"

    mod = os.path.join(path, module_id+".so")

    # set_log_level(INFO)
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
    #c1.show_status()
    #c1.print_netlist()

    if do_plot:
        freqplot(c1,name)
        # generate faust source and build dir
    if gx_build or lv2_build or not do_plot:
        if not os.path.exists(dst):
            os.makedirs(dst)
        if a == 1 :
            faustdsp, faustui = c1.get_faust_code(filename=str(dspname))
        else :
            faustdsp, faustui = c1.get_simple_faust_code(filename=str(dspname))
        if build_table == a:
            generate_nonlin_table(c1)
            src = 'dkbuild/%s_table.h' %  modulename
            # copy table to build dir
            copy2(src, dst)
            # include table use in faust code
            faustdsp = faustdsp.replace('with', ': clip with' )
            faustdsp +=  '\n    clip = ffunction(float circclip(float), "%s_table.h", "");\n' % modulename

        faustdsp = faustdsp.replace('process', "p%s" % a)
        fdata += faustdsp
        fuidata += faustui

# create a guitarix module
if gx_build or (not do_plot and not lv2_build) :
    write_final_file(dspfile,fdata,dspfileui,fuidata)
    generate_gx_plugin(args.input, dspfile, build_table)

# create a LV2 module
elif lv2_build :
    write_final_file(dspfile,fdata,dspfileui,fuidata)
    generate_lv2_plugin(args.input, dspfile, modulename, build_table)

