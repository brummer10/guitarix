#!/usr/bin/env python

import os
from shutil import copy2
import argparse,sys
import re
sys.path.append(".")

class ArgParser(argparse.ArgumentParser):
    def error(self, message):
        sys.stderr.write('error: %s\n' % message)
        self.print_help()
        sys.exit(0)

parser = ArgParser(description='Build script to generate guitarix or LV2 plugins from schematic files.', usage='')
#parser = argparse.ArgumentParser(description='Build script for guitarix plugins.')
parser.add_argument('-i','--input', metavar='*.sch', nargs='+', help='Input schematic file(s) name(s) [ONE REQUIRED]',required=True)
parser.add_argument('-n','--name',help='Name for plugin [OPTIONAL]', required=False)
parser.add_argument('-s','--shortname',help='Shortname for plugin [OPTIONAL]', required=False)
parser.add_argument('-d','--description',help='Description for plugin [OPTIONAL]', required=False)
parser.add_argument('-c','--category',help='Category for plugin [OPTIONAL]', required=False)
parser.add_argument('-m','--module_id',help='Module ID for plugin [OPTIONAL]', required=False)
parser.add_argument('-p','--plot', type=str, nargs='?', const='freq', help='frequency response (freq), sinewave (sine) or harmonics (harm) plot from the circuit [OPTIONAL]', required=False)
parser.add_argument('-b','--build',help='build guitarix plugin from the circuit [OPTIONAL]',action="store_true", required=False)
parser.add_argument('-l','--buildlv2',help='build lv2 plugin from the circuit [OPTIONAL]',action="store_true", required=False)
parser.add_argument('-F','--buildfaust',help='build faust code only from the circuit [OPTIONAL]',action="store_true", required=False)
parser.add_argument('--deploy',help='build C++ code only from the circuit [OPTIONAL]',action="store_true", required=False)
parser.add_argument('-2','--stereo',help='build stereo plugin from the circuit [OPTIONAL]',action="store_true", required=False)
parser.add_argument('--switch', metavar='N=Name', nargs='+', help='add on/off switch with "Name" for the N\'t circuit [OPTIONAL]', required=False)
parser.add_argument('-T','--faust_table', help='build faust, instead C based nonlinear response tables [OPTIONAL]',action="store_true", required=False)
parser.add_argument('-t','--table', metavar='N', type=int, nargs='+', help='build nonlinear response table from the N\'t circuit [OPTIONAL]', required=False)
parser.add_argument('-g','--table_neg', metavar='N', type=int, nargs='+', help='build negative nonlinear response table from the N\'t circuit (imply --table)[OPTIONAL]', required=False)
parser.add_argument('-x','--sig_max', metavar='N', type=float, nargs='+', help='max signal send to build the nonlinear response table from the circuit [OPTIONAL]', required=False)
parser.add_argument('-/','--table_div', metavar='N', type=float, nargs='+', help='divider for nonlinear response table from the circuit [OPTIONAL]', required=False)
parser.add_argument('-S','--scip_div',help='skip the divider for the negative nonlinear response table[OPTIONAL]',action="store_true", required=False)
parser.add_argument('-o','--table_op', metavar='N', type=float, nargs='+', help='step operator multiplier for nonlinear response table from the circuit [OPTIONAL]', required=False)
parser.add_argument('--oversample', metavar='N', type=int, help='set oversample rate [OPTIONAL]', required=False)
parser.add_argument('--fixedrate', metavar='N', type=int, help='set fixed samplerate [OPTIONAL]', required=False)
parser.add_argument('--samplerate', metavar='N', type=int, help='set samplerate to be used in sim (default 96000) [OPTIONAL]', required=False)
parser.add_argument('--bypass',  help='add bypass switch  [OPTIONAL]',action="store_true", required=False)
parser.add_argument('-f','--freqsplit', help='use frequency splitter for all filters [OPTIONAL]',action="store_true", required=False)
parser.add_argument('-N','--nonlinsplit', help='use frequency splitter only for nonlinear response [OPTIONAL]',action="store_true", required=False)
parser.add_argument('-v','--vectorize', help='generate vectorized loop [OPTIONAL]',action="store_true", required=False)
parser.add_argument('-V','--vector_size', metavar='N', type=int, help='use vector size N [OPTIONAL]', required=False)
parser.add_argument('-r','--reduce_gain', metavar='N=value', nargs='+', help='reduce gain output from the circuit N by value [OPTIONAL]', required=False)


args = parser.parse_args()

def parse_var(s):
    items = s.split('=')
    key = items[0].strip() # we remove blanks around keys, as is logical
    if len(items) > 1:
        # rejoin the rest:
        value = '='.join(items[1:])
    return (key, value)


def parse_vars(items):
    """
    Parse a series of key-value pairs and return a dictionary
    """
    d = {}

    if items:
        for item in items:
            key, value = parse_var(item)
            d[key] = value
    return d

os.chdir("../")

comandline = "\n\n/*******************************************************************************\n"
comandline += "**************************** File generated by *********************************\n"
comandline += "********************************************************************************\n"
for arg in sys.argv:
    comandline += " %s" % arg
comandline += "\n*******************************************************************************/\n\n"

del sys.argv[1:]
from analog import *
import circ_table_gen as ci

faust_table_template = """
/*******************************************************************************
  * 1-dimensional function table for linear interpolation
*******************************************************************************/
rd = library("reducemaps.lib");

//-- Rdtable from waveform
rtable(table, r) = (table, int(r)):rdtable;

//-- Copy the sign of x to f
ccopysign(f, x) = ma.fabs(f) * sign(x);

//-- Get sign of value x
sign(x) = x<0, 1, -1 : select2;

//-- Check if value x is negative
fsignbit(x) = x<0;

//-- Get fractal part of value n
fractal(n) = n - int(n);

//-- Interpolate value between i and i+1 in table with fractal coefficient f.
interpolation(table, size, f, i) = select2(i<0,select2(i>size-2,
    rtable(table, i)*(1-f) + rtable(table,i+1)*f, rtable(table, size-1)),
    rtable(table, 0)) : table_gate(table);

//-- reduce dc-offset (noise) from table response for very low values
table_gate(table,x) = select2(ma.fabs(x):rd.maxn(4096)<ma.fabs(rtable(table, 1))*(0.12), x, x*x*x);

//-- Linear interpolation for value x in rdtable
circuit_response(table, low, high, step, size, x) =
    interpolation(table, size, fractal(linindex(step, x)),
    int(linindex(step, x))), x : ccopysign;

//-- Calculate linear table index for value x
linindex(step, x) = ma.fabs(x) * step;

//-- predefined filterbank 
freq_split = fi.filterbank(3, (86.0,210.0,1200.0,6531.0));
"""

class Filter(object):

    def calc_highpass_f0(self,c1, c2, pot):
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

class FrequencyPlot(object):

    def freq_plot(self, c1,name):
        sig = Signal()
        s = c1.make_signal_vector(sig(sig.impulse(), timespan=1))
        c1.stream(s)
        s.plot_spectrum(c1.last_output)
        ax = pylab.gca()
        ax.grid()
        ax.yaxis.set_major_formatter(pylab.FormatStrFormatter('%d dB'))
        ax.xaxis.set_major_formatter(pylab.FormatStrFormatter('%d Hz'))
        pylab.title(name)
        pylab.xlabel('Frequency')
        pylab.ylabel('Magnitude')
        pylab.show()

    def sine_plot(self, c1,name):
        sig = Signal()
        s = c1.make_signal_vector(sig(sig.sine(), timespan=0.00907))
        c1.stream(s)
        s.plot(c1.last_output)
        ax = pylab.gca()
        ax.grid()
        ax.yaxis.set_major_formatter(pylab.FormatStrFormatter('%d dB'))
        pylab.title(name)
        pylab.ylabel('Magnitude')
        pylab.show()

    def harmonic_plot(self, c1,name):
        sig = Signal()
        s = c1.make_signal_vector(sig(sig.sweep()))
        c1.stream(s)
        s.plot(c1.last_output,"Harmonic")
        ax = pylab.gca()
        ax.grid()
        ax.yaxis.set_major_formatter(pylab.FormatStrFormatter('%d dB'))
        ax.xaxis.set_major_formatter(pylab.FormatStrFormatter('%d Hz'))
        ax.legend()
        pylab.title(name)
        pylab.xlabel('Frequency')
        pylab.ylabel('Magnitude')
        pylab.show()

class Generators(object):

    def generate_nonlin_table(self, c1, modulename, sig_max, table_op, scip_div, table_neg, table_div=None, faust_table=None):
        v = ci.Circ_table(modulename, c1.S,c1.V, sig_max, table_op, table_div)
        parser = dk_simulator.Parser(v.S, v.V, v.FS)
        p = dk_simulator.get_executor(
        modulename, parser, v.solver, '-p', c_tempdir='/tmp', c_verbose='--c-verbose',
        c_debug_load='', linearize='', c_real=("double"))
        y = p(v.signal())
        if (faust_table) :
            td = v.generate_faust_table(p, y,"")
        else :
            td = v.generate_table(p, y,"")
        v.plot(p,y)
        if (table_neg):
            if (scip_div) :
                td = None
            v = ci.Circ_table(modulename+"_neg", c1.S,c1.V, -1.0*sig_max, table_op, td)
            parser = dk_simulator.Parser(v.S, v.V, v.FS)
            p = dk_simulator.get_executor(
            modulename, parser, v.solver, '-p', c_tempdir='/tmp', c_verbose='--c-verbose',
            c_debug_load='', linearize='', c_real=("double"))
            y = p(v.signal())
            if (faust_table) :
                v.generate_faust_table(p, y,"")
            else :
                td = v.generate_table(p, y,"")
            v.plot(p,y)

    def write_final_file(self, a, dspfile,fdata,dspfileui,fuidata,freqs,gain_stages,switch=None,stereo=None,faust_table=None,bypass=None):
        button = ''
        if not stereo:
            if not freqs:
                if (bypass):
                    process_line = '\n\nbypass = checkbox("Enable[name:Enable");\n'
                    process_line += "\nproc = "
                else:
                    process_line = "\nprocess = "
                for x in xrange(1,a+1,1):
                    if str(x) in switch:
                        process_line += 'ba.bypass_fade(ma.SR/10, 1 - b%s, p%s) ' % (x,x)
                        button += '\nb%s = checkbox("%s[name:%s");' % (x,switch[str(x)],switch[str(x)])
                    else:
                        process_line += ' p%s ' % x
                    if str(x) in gain_stages:
                        stage = 'p%s' % x
                        gain_stage = ' : *(%s)' % gain_stages[str(x)]
                        process_line = process_line.replace(stage,stage+gain_stage)
                    if a>x :
                        process_line += ':'
                    else :
                        process_line += ';\n'
                fdata += button
                if (bypass):
                    process_line += '\nprocess = ba.bypass_fade(ma.SR/10, 1- bypass, proc);\n'
                fdata += process_line
            else:
                process_line = "\namp = "
                for x in xrange(1,a+1,1):
                    if str(x) in switch:
                        process_line += 'ba.bypass_fade(ma.SR/10, 1 - b%s, p%s) ' % (x,x)
                        button += '\nb%s = checkbox("%s[name:%s");\n' % (x,switch[str(x)],switch[str(x)])
                    else:
                        process_line += ' p%s ' % x
                    if str(x) in gain_stages:
                        stage = 'p%s' % x
                        gain_stage = ' : *(%s)' % gain_stages[str(x)]
                        process_line = process_line.replace(stage,stage+gain_stage)
                    if a>x :
                        process_line += ':'
                    else :
                        process_line += ';\n'
                if not (faust_table):
                    process_line += '\nfreq_split = fi.filterbank(3, (86.0,210.0,1200.0,6531.0));\n'
                if (bypass):
                    process_line += '\nbypass = checkbox("Enable[name:Enable");\n'
                    process_line += "\nproc = freq_split: ( amp , amp , amp, amp, amp) :>_;\n"
                else:
                    process_line += '\n\nprocess    = freq_split: ( amp , amp , amp, amp, amp) :>_;\n'
                fdata += button
                if (bypass):
                    process_line += '\nprocess = ba.bypass_fade(ma.SR/10, 1- bypass, proc);\n'
                fdata += process_line
        else:
            if not freqs:
                process_line = "\nchanel = "
                for x in xrange(1,a+1,1):
                    if str(x) in switch:
                        process_line += 'ba.bypass_fade(ma.SR/10, 1 - b%s, p%s) ' % (x,x)
                        button += '\nb%s = checkbox("%s[name:%s");' % (x,switch[str(x)],switch[str(x)])
                    else:
                        process_line += ' p%s ' % x
                    if str(x) in gain_stages:
                        stage = 'p%s' % x
                        gain_stage = ' : *(%s)' % gain_stages[str(x)]
                        process_line = process_line.replace(stage,stage+gain_stage)
                    if a>x :
                        process_line += ':'
                    else :
                        process_line += ';\n'
                if (bypass):
                    process_line += '\n\nbypass = checkbox("Enable[name:Enable");\n'
                    process_line += "\nproc = chanel , chanel ;\n"
                else:
                    process_line += '\nprocess = chanel , chanel ;\n'
                fdata += button
                if (bypass):
                    process_line += '\nprocess = ba.bypass_fade(ma.SR/10, 1- bypass, proc);\n'
                fdata += process_line
            else:
                process_line = "\namp = "
                for x in xrange(1,a+1,1):
                    if str(x) in switch:
                        process_line += 'ba.bypass_fade(ma.SR/10, 1 - b%s, p%s) ' % (x,x)
                        button += '\nb%s = checkbox("%s[name:%s");' % (x,switch[str(x)],switch[str(x)])
                    else:
                        process_line += ' p%s ' % x
                    if str(x) in gain_stages:
                        stage = 'p%s' % x
                        gain_stage = ' : *(%s)' % gain_stages[str(x)]
                        process_line = process_line.replace(stage,stage+gain_stage)
                    if a>x :
                        process_line += ':'
                    else :
                        process_line += ';\n'
                if not (faust_table):
                    process_line += '\nfreq_split = fi.filterbank(3, (86.0,210.0,1200.0,6531.0));\n'
                process_line += "\nchanel = freq_split: ( amp , amp , amp, amp, amp) :>_;\n"
                if (bypass):
                    process_line += '\n\nbypass = checkbox("Enable[name:Enable");\n'
                    process_line += "\nproc = chanel , chanel ;\n"
                else:
                    process_line += '\n\nprocess    = chanel , chanel ;\n'
                fdata += button
                if (bypass):
                    process_line += '\nprocess = ba.bypass_fade(ma.SR/10, 1- bypass, proc);\n'
                fdata += process_line
        if(faust_table):
            fdata = fdata.replace('import("stdfaust.lib");', 'import("stdfaust.lib");\n%s') % faust_table_template
        fdata = comandline + fdata
        with open(dspfile, 'w') as f:
            f.write(fdata)
        f.close()
        x = 1
        for line in button.split('\n'):
            if not len(line.strip()) == 0 :
                fuidata = fuidata.replace('b.openHorizontalBox("");','b.openHorizontalBox("");\n\n    b.create_switch("minitoggle",PARAM("%s"), "%s");') % (switch[str(x)],switch[str(x)])
                x = x+1
        if (bypass):
            fuidata = fuidata.replace('b.openHorizontalBox("");','b.openHorizontalBox("");\n\n    b.create_switch("switch",PARAM("Enable"), "Enable");')

        with open(dspfileui, 'w') as f:
            f.write(fuidata)
        f.close()

    def generate_gx_plugin(self, arg, dspfile, rs, vec, vs, nonlin=None):
        if nonlin :
            print ("build nonlin gx_plugin from: %s" % arg)
        else :
            print ("build gx_plugin from: %s" % arg)
        datatype="double"
        pgm = os.path.abspath("../../build-faust")
        opts = " " if datatype == "float" else ""
        if (vec):
            opts += " -V "
        if (vs):
            opts += " -S %s " % vs
        if (rs):
            opts += " -r "
        os.system("%s %s -c -k %s" % (pgm, opts, dspfile))

    def generate_lv2_plugin(self, arg, dspfile, tablename, modulename, name, rs, vec, vs, nonlin=None, nonlin_neg=None, faust_table=None):
        if nonlin :
            print ("build nonlin lv2_plugin from: %s" % arg)
        else :
            print ("build lv2_plugin from: %s" % arg)
        p = os.getcwd()
        os.chdir("buildlv2/")
        pgm = os.path.abspath("./make_lv2_X11bundle.sh")
        if (vec):
            opts = " -V "
        else:
            opt = ""
        if (vs):
            opts += " -S %s " % vs
        if not rs :
            result = os.system("%s -p ../%s %s -n  %s" % (pgm, dspfile, opt, name ))
        else :
            result = os.system("%s -p ../%s %s -r -n  %s" % (pgm, dspfile, opt, name ))
        if (result):
            print ('\033[91m'+"Error, see message above"+'\033[0m')
            exit (1)
        # copy table to bundle
        if not faust_table :
            if nonlin :
                for a in nonlin:
                    src1 = '../dkbuild/%s_table.h' %  tablename[a-1]
                    dst1 = 'gx_%s.lv2/dsp/' % modulename
                    copy2(src1, dst1)
            if nonlin_neg :
                for a in nonlin_neg:
                    src1 = '../dkbuild/%s_neg_table.h' %  tablename[a-1]
                    dst1 = 'gx_%s.lv2/dsp/' % modulename
                    copy2(src1, dst1)
        os.chdir('gx_%s.lv2' % modulename)
        os.system('make uninstall && make && make install')
        os.chdir(p)

    def deploy_c(self, c1):
        c1.build_script = sys.argv[0]
        c1.backward_euler = True
        c1.transform_opts.partition = True
        c1.transform_opts.decompose = True
        c1.sys_reduce_tol = 1e-5
        c1.set_tempdir("gencode")
        c1.keep_tempdir()
        c1.set_solver(dict(method='hybr', factor=1e5))
        c1.deploy()


class DKbuilder(object):

    name = args.name
    shortname = args.shortname
    description = args.description
    category = args.category
    oversample = args.oversample
    fixedrate = args.fixedrate
    samplerate = args.samplerate
    faust_table = args.faust_table
    rs = False
    freqsplit = args.freqsplit
    frs = False
    tablename = {}
    gain_stages = {}
    switch = {}

    if (args.table_neg):
        if (not args.table):
            args.table = args.table_neg
        else:
            args.table += args.table_neg

    if name:
        modulename = name.lower()
    else:
        schema = args.input[0]
        modulename = schema.split('.')[0].lower()

    if (args.vectorize):
        vec = True
    else:
        vec = False

    if (args.vector_size):
        vs = args.vector_size
        vec = True
    else:
        vs = 0

    if (args.reduce_gain):
        gain_stages = parse_vars(args.reduce_gain)

    if (args.switch):
        switch = parse_vars(args.switch)

    def index_exists(self,ls, i):
        return (0 <= i < len(ls)) or (-len(ls) <= i < 0)

    def build(self):

        fdata = ""
        fuidata = ""
        table_counter = 0
        dsp_counter = 0
        ui_counter = 0
        in_files = len(args.input)

        if not (self.samplerate):
            self.samplerate = 96000

        g = Generators()
        c1 = Circuit(FS=self.samplerate)

        # generate faust code and nonlin table
        for sch in args.input:
            dsp_counter +=1
            print ("\nInput file %s: %s" % (dsp_counter, args.input[dsp_counter-1]))
           # fileName, fileExtension = os.path.splitext(args.input[dsp_counter-1])
           # if fileExtension == ".dsp":
           #     read_dsp_file(args.input[dsp_counter-1])
           #     continue

            schema = args.input[dsp_counter-1]
            workfile="gschem-schematics/"+schema
            path = "tmp"

            module_id = args.module_id
            if not module_id:
                module_id = self.modulename
            print ("module_id: %s" % module_id )

            dst = 'dkbuild/%s/' % self.modulename
            dspname = dst+self.modulename
            dspfile = dspname+".dsp"
            dspfileui = dspname+"_ui.cc"

            # set_log_level(INFO)
            c1.plugindef = dk_simulator.PluginDef(module_id)
            if not self.name:
                self.name = module_id
            c1.plugindef.name = self.name
            if not self.shortname:
                self.shortname = self.name
            c1.plugindef.shortname = self.shortname
            if not self.description:
                self.description = self.name
            c1.plugindef.description = self.description
            if not self.category:
                self.category = "Extern"
            c1.plugindef.category = self.category
            if self.oversample:
                c1.plugindef.oversample = self.oversample
                self.rs = True
            if self.fixedrate:
                c1.plugindef.fixedrate = self.fixedrate
                self.rs = True
            if self.freqsplit:
                self.frs = True
                
            c1.plugindef.id = module_id
            c1.set_module_id(module_id)
            c1.read_gschem(workfile)
            #c1.show_status()
            #c1.print_netlist()

            if args.plot:
                f = FrequencyPlot()
                if args.plot == "harm":
                    f.harmonic_plot(c1,self.name)
                elif args.plot == "sine":
                    f.sine_plot(c1,self.name)
                else:
                    f.freq_plot(c1,self.name)
                # generate faust source and build dir
            if args.deploy:
                g.deploy_c(c1)
            elif args.build or args.buildlv2 or not args.plot:
                dlimer = """/*******************************************************************************
  * %s generated by dkbuiler from %s
*******************************************************************************/
""" % (schema.split('.')[0].lower(), schema)
                if not os.path.exists(dst):
                    os.makedirs(dst)
                if dsp_counter == 1 :
                    faustdsp, faustui = c1.get_faust_code(filename=str(dspname))
                else :
                    faustdsp, faustui = c1.get_simple_faust_code(filename=str(dspname))
                if args.table and dsp_counter in args.table:
                    s = False
                    tn = False
                    self.tablename[dsp_counter-1] = schema.split('.')[0].lower()
                    table_counter += 1
                    if args.sig_max and self.index_exists(args.sig_max,table_counter-1) :
                        m = args.sig_max[table_counter-1]
                    else :
                        m = 1.4
                    if args.table_op and self.index_exists(args.table_op,table_counter-1):
                        o = args.table_op[table_counter-1]
                    else:
                        o = 1.0
                    if args.table_div and self.index_exists(args.table_div,table_counter-1):
                        d = args.table_div[table_counter-1]
                    else:
                        d = None
                    if args.table_neg and dsp_counter in args.table_neg:
                        tn = True
                        if (args.scip_div):
                            s = True
                    g.generate_nonlin_table(c1, self.tablename[dsp_counter-1], m, o, s, tn, d,args.faust_table)
                    if (args.faust_table) :
                        tsrc = 'dkbuild/%s_table.lib' %  self.tablename[dsp_counter-1]
                        with open(tsrc, 'r') as f:
                            mytable = f.read()
                        f.close()
                    else:
                        src = 'dkbuild/%s_table.h' %  self.tablename[dsp_counter-1]
                        # copy table to build dir
                        copy2(src, dst)
                    if (tn) :
                        if (args.faust_table) :
                            tsrc = 'dkbuild/%s_neg_table.lib' %  self.tablename[dsp_counter-1]
                            with open(tsrc, 'r') as f:
                                myneg_table = f.read()
                            f.close()
                        else :
                            src = 'dkbuild/%s_neg_table.h' %  self.tablename[dsp_counter-1]
                            # copy table to build dir
                            copy2(src, dst)
                    # include table use in faust code
                    if (tn):
                        faustdsp = faustdsp.replace('with', ': %sclip with' ) % self.tablename[dsp_counter-1]
                        if (args.faust_table) :
                            faustdsp = faustdsp.replace('//TABLE', '%s\n%s') % (mytable,myneg_table)
                            faustdsp = faustdsp.replace('process', '%s\nprocess') % dlimer
                            if (args.nonlinsplit):
                                faustdsp +=  '\n{st}p = _<: ba.if(fsignbit(_), {st}_neg_clip, {st}_clip) :>_ ;\n'.format(st=self.tablename[dsp_counter-1])
                                faustdsp += '\n{st}clip = freq_split: ( {st}p , {st}p , {st}p, {st}p, {st}p) :>_;\n'.format(st=self.tablename[dsp_counter-1])
                            else:
                                faustdsp +=  '\n{st}clip = _<: ba.if(fsignbit(_), {st}_neg_clip, {st}_clip) :>_ ;\n'.format(st=self.tablename[dsp_counter-1])
                        else:
                            faustdsp = faustdsp.replace('//TABLE', '\n\n%s') % dlimer
                            if (args.nonlinsplit):
                                faustdsp +=  '\n{st}p = _<: ba.if(signbit(_), {st}_neg_clip, {st}_clip) :>_  with  '.format(st=self.tablename[dsp_counter-1])
                                faustdsp +=  '{\n'
                                faustdsp +=  '\n    signbit = ffunction(int signbit(float), "math.h", "");\n'
                                faustdsp +=  '\n    {st}_clip = ffunction(float {st}clip(float), "{st}_table.h", "");\n'.format(st=self.tablename[dsp_counter-1])
                                faustdsp +=  '\n    {st}_neg_clip = ffunction(float {st}_negclip(float), "{st}_neg_table.h", "");\n'.format(st=self.tablename[dsp_counter-1])
                                faustdsp +=  '\n};\n'
                                faustdsp += '\n{st}clip = freq_split: ( {st}p , {st}p , {st}p, {st}p, {st}p) :>_;\n'.format(st=self.tablename[dsp_counter-1])                                
                            else:
                                faustdsp +=  '\n{st}clip = _<: ba.if(signbit(_), {st}_neg_clip, {st}_clip) :>_  with  '.format(st=self.tablename[dsp_counter-1])
                                faustdsp +=  '{\n'
                                faustdsp +=  '\n    signbit = ffunction(int signbit(float), "math.h", "");\n'
                                faustdsp +=  '\n    {st}_clip = ffunction(float {st}clip(float), "{st}_table.h", "");\n'.format(st=self.tablename[dsp_counter-1])
                                faustdsp +=  '\n    {st}_neg_clip = ffunction(float {st}_negclip(float), "{st}_neg_table.h", "");\n'.format(st=self.tablename[dsp_counter-1])
                                faustdsp +=  '\n};\n'
                    else :
                        if not (args.nonlinsplit):
                            faustdsp = faustdsp.replace('with', ': %s_clip with' ) % self.tablename[dsp_counter-1]
                        else:
                            faustdsp = faustdsp.replace('with', ': %sp with' ) % self.tablename[dsp_counter-1]
                        if (args.faust_table) :
                            faustdsp = faustdsp.replace('//TABLE', '\n%s') % mytable
                            if (args.nonlinsplit):
                                faustdsp += '\n    {st}p = freq_split: ( {st}_clip , {st}_clip , {st}_clip, {st}_clip, {st}_clip) :>_;\n'.format(st=self.tablename[dsp_counter-1])
                        else :
                            faustdsp = faustdsp.replace('//TABLE', '')
                            if (args.nonlinsplit):
                                faustdsp = faustdsp.replace('with', ': %s_clip with' ) % self.tablename[dsp_counter-1]
                                faustdsp += '\n    freq_split = fi.filterbank(3, (86.0,210.0,1200.0,6531.0));\n'
                                faustdsp +=  '\n    {st}p = ffunction(float {st}clip(float), "{st}_table.h", "");\n'.format(st=self.tablename[dsp_counter-1])
                                faustdsp += '\n    {st}_clip = freq_split: ( {st}p , {st}p , {st}p, {st}p, {st}p) :>_;\n'.format(st=self.tablename[dsp_counter-1])
                            else:
                                faustdsp +=  '\n    {st}_clip = ffunction(float {st}clip(float), "{st}_table.h", "");\n'.format(st=self.tablename[dsp_counter-1])
                else:
                    faustdsp = faustdsp.replace('//TABLE', '\n\n%s') % dlimer
                faustdsp = faustdsp.replace('process', "p%s" % dsp_counter)
                fdata += faustdsp
                if faustui:
                    ui_counter +=1
                    if (ui_counter ==2) and ( dsp_counter != in_files):
                        fuidata = fuidata.rsplit("\n", 2)[0]
                        faustui = faustui.replace('b.openHorizontalBox("");\n', '')
                        faustui = faustui.replace('b.closeBox();\n', '')
                    elif (ui_counter ==2) and ( dsp_counter == in_files):
                        fuidata = fuidata.rsplit("\n", 2)[0]
                        faustui = faustui.replace('b.openHorizontalBox("");\n', '')
                    elif (ui_counter >2) and ( dsp_counter != in_files):
                        fuidata = fuidata.rsplit("\n", 1)[0]
                        faustui = faustui.replace('b.openHorizontalBox("");\n', '')
                        faustui = faustui.replace('b.closeBox();\n', '')
                    elif (ui_counter >2) and ( dsp_counter == in_files):
                        fuidata = fuidata.rsplit("\n", 1)[0]
                        faustui = faustui.replace('b.openHorizontalBox("");\n', '')
                elif (ui_counter >1) and ( dsp_counter == in_files):
                    faustui += 'b.closeBox();\n'
                fuidata += faustui

        if any ([args.build, args.buildlv2, args.buildfaust]):
            g.write_final_file(dsp_counter,dspfile,fdata,dspfileui,fuidata,self.frs,self.gain_stages,self.switch,args.stereo,args.faust_table,args.bypass)
        # create a guitarix module
        if args.build or (not args.table and not args.plot and not args.buildlv2 and not args.buildfaust and not args.deploy) :
            g.generate_gx_plugin(args.input, dspfile, self.rs, self.vec, self.vs, args.table)
        # create a LV2 module
        elif args.buildlv2 :
            g.generate_lv2_plugin(args.input, dspfile, self.tablename, self.modulename, self.name, self.rs, self.vec, self.vs, args.table, args.table_neg, args.faust_table)

def main(argv):
    dk = DKbuilder()
    dk.build()

if __name__ == "__main__":
    main(sys.argv[1:])
