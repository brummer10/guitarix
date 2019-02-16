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
parser.add_argument('-p','--prefilter',help='prefilter for plugin [OPTIONAL]', required=False)
parser.add_argument('--plot',help='frequency plot from the circuit [OPTIONAL]',action="store_true", required=False)
parser.add_argument('--build',help='build guitarix plugin from the circuit [OPTIONAL]',action="store_true", required=False)
parser.add_argument('--buildlv2',help='build lv2 plugin from the circuit [OPTIONAL]',action="store_true", required=False)
parser.add_argument('--table', metavar='N', type=int,help='build nonlinear response table from the N\'t circuit [OPTIONAL]', required=False)
parser.add_argument('--sig_max', metavar='N', type=float, nargs='+', help='max signal send to build the nonlinear response table from the circuit [OPTIONAL]', required=False)
parser.add_argument('--table_div', metavar='N', type=int, nargs='+', help='divider for nonlinear response table from the circuit [OPTIONAL]', required=False)

args = parser.parse_args()
 
## show values ##
a = 0
b = 0
nonlintable = ""
nonlinfile = ""
nonlinuifile = ""
nonlinname = ""
dspfile = ""
dspfileui = ""
dspname = ""
fdata = ""
fuidata = ""
os.chdir("../")


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

def nonlin_table(c1):
    v = ci.Circ_table(name, c1.S,c1.V, sig_max, table_div)
    parser = dk_simulator.Parser(v.S, v.V, v.FS)
    p = dk_simulator.get_executor(
    name, parser, v.solver, '-p', c_tempdir='/tmp', c_verbose='--c-verbose',
    c_debug_load='', linearize='', c_real=("double"))
    y = p(v.signal())
    v.generate_table(p, y,"")
    v.plot(p,y)
    

for sch in args.input:
    a +=1
    print ("%s %s" %(a, sch))
    schema = args.input[a-1]

    workfile="gschem-schematics/"+schema
    name = args.name
    shortname = args.shortname
    description = args.description
    category = args.category
    module_id = args.module_id
    prefilter = args.prefilter
    do_plot = args.plot
    gx_build = args.build
    lv2_build = args.buildlv2
    build_table = args.table

    if (args.table_div) :
        table_div = args.table_div
    else :
        table_div = None
    if (args.sig_max) :
        sig_max = args.sig_max
    else :
        sig_max = None

    print ("Input file: %s" % args.input )
    del sys.argv[1:]

    from analog import *
    import circ_table_gen as ci

    path = "tmp"

    modulename = schema.split('.')[0].lower()
    if not module_id:
        module_id = modulename
    print ("module_id: %s" % module_id )
    mod = os.path.join(path, module_id+".so")

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

    #print("V %s" % format(c1.V))
    #print("S %s" % format(c1.S))

    if do_plot:
        freqplot(c1,name)

    if build_table == a:
        nonlin_table(c1)
        # generate faust source in build dir
        if gx_build or lv2_build :
            src = 'dkbuild/%s_table.h' %  modulename
            dst = 'dkbuild/%s/' % modulename
            nonlintable = modulename
            # copy table to build dir
            if not os.path.exists(dst):
                os.makedirs(dst)
            copy2(src, dst)
            dspname = dst+modulename
            dspfile = dspname+".dsp"
            dspfileui = dspname+"_ui.cc"
            nonlinfile = dspfile
            nonlinuifile = dspfileui
            nonlinname = modulename
            c1.save_faust_code(filename=str(dspname))
            # add table to faust source
            with open(dspfile, 'r') as f :
               fdata = f.read()
            fdata = fdata.replace('process', "p%s" % a)
            fdata = fdata.replace('with', ": clip with" )
            fdata +=  '\n    clip = ffunction(float circclip(float), "%s_table.h", "");\n' % modulename
            f.close()

            with open(dspfile, 'w') as f:
                f.write(fdata)
            f.close()
            with open(dspfileui, 'r') as f:
                fuidata = f.read()
            f.close()
    else :
        dst = 'dkbuild/%s/' % modulename
        if not os.path.exists(dst):
            os.makedirs(dst)
        dspname = dst+modulename
        dspfile = dspname+".dsp"
        dspfileui = dspname+"_ui.cc"
        c1.save_faust_code(filename=str(dspname))
        with open(dspfileui, 'r') as f:
            fuidata = f.read()
        f.close()
       
for sch in args.input:
    b +=1
    #print ("%s %s" %(a, sch))
    schema = args.input[b-1]
    modulename = schema.split('.')[0].lower()
    dst = 'dkbuild/%s/' % modulename
    dspname = dst+modulename
    dspfile = dspname+".dsp"
    dspfiletmp = dspname+".dsp~"
    if build_table != b :
        v = 0
        f = open(dspfiletmp, "a")
        if (build_table or b>1) :
            pattern = re.compile("process")
            with open(dspfile, "r") as fi:
                for line in fi:
                    if pattern.search(line) != None:
                        v = 1
                        line = line.replace("process", "p%s" % b)
                        f.write("\n")
                    if v:
                        f.write(line)
        else :
            pattern = re.compile("process")
            with open(dspfile, "r") as fi:
                for line in fi:
                    if pattern.search(line) != None:
                        line = line.replace("process", "p%s" % b)
                    f.write(line)
        f.close()
        fi.close()
        with open(dspfiletmp, 'r') as f :
            fdata += f.read()
        f.close()
        os.remove(dspfiletmp)

        if (b != a) :
            dspfileui = dspname+"_ui.cc"
            dspfiletmpui = dspname+"_ui.cc~"
            v = 0
            f = open(dspfiletmpui, "a")
            pattern = re.compile("openHorizontalBox")
            with open(dspfileui, "r") as fi:
                for line in fi:
                    if pattern.search(line) != None:
                        v = 1
                    if v:
                        f.write(line)
            f.close()
            fi.close()
            with open(dspfiletmpui, 'r') as f :
                fuidata += f.read()
            f.close()
            os.remove(dspfiletmpui)

if a == 1 :
    fdata +=  "\nprocess = p1 ;"
elif a == 2 :
    fdata +=  "\nprocess = p1 : p2;"
elif a == 3 :
    fdata +=  "\nprocess = p1 : p2 : p3;"
elif a == 4 :
    fdata +=  "\nprocess = p1 : p2 : p3 : p4;"

if build_table :
    with open(nonlinfile, 'w') as f:
      f.write(fdata)
    f.close()

    with open(nonlinuifile, 'w') as f:
      f.write(fuidata)
    f.close()
else :
    with open(dspfile, 'w') as f:
      f.write(fdata)
    f.close()

    with open(dspfileui, 'w') as f:
      f.write(fuidata)
    f.close()


# create a guitarix module
if gx_build and build_table :
    print ("build nonlin gx_plugin from: %s" % args.input)
    datatype="double"
    pgm = os.path.abspath("../../build-faust")
    opts = " " if datatype == "float" else ""
    os.system("%s %s -c -k %s" % (pgm, opts, nonlinfile))

# create a LV2 module
if lv2_build and build_table :
    print ("build nonlin lv2_plugin from: %s" % args.input)
    p = os.getcwd()
    os.chdir("buildlv2/")
    pgm = os.path.abspath("./make_lv2_X11bundle.sh")
    os.system("%s -p ../%s -n  %s" % (pgm, nonlinfile, name ))
    # copy table to bundle
    src1 = '../dkbuild/%s_table.h' %  nonlintable
    dst1 = 'gx_%s.lv2/dsp/' % nonlintable
    copy2(src1, dst1)
    os.chdir('gx_%s.lv2' % nonlinname)
    os.system('make && make install')
    os.chdir(p)


# default build guitarix module
if gx_build and not build_table or (not do_plot and not build_table and not lv2_build) :
    print ("build gx_plugin from: %s" % args.input[a-1])
    datatype="double"
    pgm = os.path.abspath("../../build-faust")
    opts = " " if datatype == "float" else ""
    os.system("%s %s -c -k %s" % (pgm, opts, dspfile))
   # if not prefilter:
   #     c1.create_faust_module()
   # else:
   #     print prefilter
   #     c1.create_faust_module(pre_filter=prefilter)

# build linear lv2 plugin
if lv2_build and not build_table :
    print ("build lv2_plugin from: %s" % args.input)
    p = os.getcwd()
    os.chdir("buildlv2/")
    pgm = os.path.abspath("./make_lv2_X11bundle.sh")
    os.system("%s -p ../%s -n  %s" % (pgm, dspfile, name ))
    os.chdir('gx_%s.lv2' % modulename)
    os.system('make && make install')
    os.chdir(p)
