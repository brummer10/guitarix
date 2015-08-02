#General imports
import subprocess, pylab, os, tempfile, shutil
import numpy as np
import scipy.signal
import matplotlib.pylab as plt
import itertools
from itertools import count

#Filters design imports
from scipy import signal
import math, numpy
from matplotlib import pyplot

#Curve fitting
from scipy.optimize import curve_fit

#Filters wrappers
from scipy import signal
import matplotlib.pyplot as plt

#Text parsers
import re
from parse import *

"""
	OC-2 Octaver precomputation script.

	The next basic steps have place:
	- Convert .sch files to netlists.
	- Run ngspice and extract required data from here.
	- Parse data.
	- Extract required data from ngspice.
	- Write it to file, which will be included to faust .dsp script 
	
	Partially crafted from Guitarix/trunk/tools/ampsim/DK/spice.py
	May be will be merged with ampsim in future.
"""

# Spice get characteristics
def _add_ac_cmd(cmd, output, step, fmin, fmax, prefix = "ngspice"):
    l = list(cmd)
    l.append(".ac dec %g %g %g" % (step, fmin, fmax))
    l.append(".control")
    l += ["run",
          "wrdata %s %s" % (prefix, ",".join(["db(v(%s))" % output])),
          ".endc",
          ".end",
          ]
    return "\n".join(l)

def _add_dc_cmd(cmd, output, source, step, fmin, fmax, prefix = "ngspice"):
    l = list(cmd)
    l.append(".dc %s %g %g %g" % (source, fmin, fmax, step))
    l.append(".control")
    l += ["run",
          "wrdata %s %s" % (prefix, ",".join(["v(%s)" % output])),
          ".endc",
          ".end",
          ]
    return "\n".join(l)

# Read netlist from gschem .sch file
def _mk_spice_netlist(fname):
    try:
        p = subprocess.Popen(
            ("gnetlist","-g","spice-sdb","-o","/dev/fd/1","-q",fname),
            stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    except OSError as e:
        raise RuntimeError(
            "can't start gnetlist -- please check gnetlist installation [%s]" % e)
    out, err = p.communicate()
    if p.returncode:
        raise ValueError("error calling gnetlist: %s" % err)
    if err:
        print err
    l = []
    for line in out.split("\n"):
        line = line.rstrip()
        if line == ".end":
            break
        l.append(line)
        
    return l

def _write_input_file(iname, lines):
    with open(iname, "w") as f:
        for i in lines:
            f.write(i)
        f.write("\n")
    return len(lines)

def _stream(script, out_file, prefix = "ngspice"):
    try:
        p = subprocess.Popen(
            ("ngspice","-n","-b","/dev/fd/0"), cwd=out_file, stdin=subprocess.PIPE, 
            stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    except OSError as e:
        raise RuntimeError(
            "can't start ngspice -- please check ngspice installation [%s]" % e)
    out, err = p.communicate(script)
    # bug in ngspice: returncode always 1
    def checkerr(buf):
        #Find "error" key word in output stream
        print buf
        if "Error" in buf:
            l = [line for line in buf.split("\n") if line.startswith("Error")]
            raise RuntimeError("error in ngspice call:\n%s" % "\n".join(l))
    #checkerr(out)
    #checkerr(err)
    return
    
def _read_result(rname):
    with open(rname) as f:
        lines = f.readlines()
        result = None
        for i, line in enumerate(lines):
            parts = [float(part) for part in line.split()]
            if result is None:
                result = np.zeros((len(lines), len(parts)))
            result[i] = parts
    return result

# Returns array with frequency and magnitude in db
def get_ac(sch_fname, out_name, step, fmin, fmax):
    outdir = tempfile.mkdtemp()
    _stream(_add_ac_cmd(_mk_spice_netlist(sch_fname), out_name, step, fmin, fmax), outdir)
    return _read_result(outdir+"/ngspice.data")

# Returns array with output DC values
def get_dc(sch_fname, out_name, source, step, vmin, vmax):
    outdir = tempfile.mkdtemp()
    _stream(_add_dc_cmd(_mk_spice_netlist(sch_fname), out_name, source, step, vmin, vmax), outdir)
    return _read_result(outdir+"/ngspice.data")


# Results processing
def normalize(arr):
	#Extract magnituce
	mag = []
	for i, val in enumerate(arr):
		mag.append(arr[i][1])
	#Normalize it
	mag=mag - max(mag)
	#Apply normalized
	for i, val in enumerate(arr):
		arr[i][1] = mag[i]

	return arr

def _find_first_more(arr, value):
	for i, val in enumerate(arr):
		if value < arr[i]:
			return i

def _find_first_less(arr, value):
	for i, val in enumerate(arr):
		if value > arr[i]:
			return i
	
def hp_freq(arr, val_db):
	mag = []
	for i, val in enumerate(arr):
		mag.append(arr[i][1])
	return arr[_find_first_more(mag, val_db)][0]

def lp_freq(arr, val_db):
	mag = []
	for i, val in enumerate(arr):
		mag.append(arr[i][1])
	return arr[_find_first_less(mag, val_db)][0]

# Custom plot functions
def parse_data(data):
	x = []
	y = []
	for i, val in enumerate(data):
		x.append(data[i][0])
		y.append(data[i][1])

	return (x, y)

def plot_ac_to_compare(filter_data_from_spice, coef_b, coef_a, FS, visualise=False):
	if visualise:
		#get and plot data from spice	
		w1, h1 = parse_data(filter_data_from_spice)
		#get and plot data from coesfs
		w, h = signal.freqz(coef_b, coef_a)
		plt.figure()
		plt.plot(w1, h1)
		plt.semilogx(w/max(w)*FS/2, 20 * np.log10(abs(h)))
		plt.xlabel('Frequency [ Hz ]')
		plt.ylabel('Amplitude [dB]')
		plt.margins(0, 0.1)
		plt.grid(which='both', axis='both')
		plt.show()
	

def plot_dc_to_compare(data_to_fit, polyfunc, visualise=False):
	if visualise:
		vin, vout = parse_data(data_to_fit)
		x_new = np.linspace(vin[0], vin[-1], 50)
		y_new = polyfunc(x_new)
		plt.figure()
		plt.plot(vin,vout,'o', x_new, y_new)
		plt.show()
		
# Functions, which are needed for data exporting
def save_filter_to_file(fileName, b, a, prefixStr, description=""):
	try:
		with open(fileName, "a+") as f:
			l = list("\n")
			l.append("//Description: %s" % (description))
			i = 0
			for b_val, a_val in itertools.izip_longest(b, a, fillvalue=0):
				l.append("b%g_%s = %s; a%g_%s = %s;" % (i, prefixStr, b_val, i, prefixStr, a_val))
				i += 1
			f.write("\n".join(l))
			f.close()
	except IOError as e:
		print "I/O error({0}): {1}".format(e.errno, e.strerror)

def save_dc_curve_to_file(fileName, poly, prefixStr, description=""):
	coefs = poly.c
	num_of_coefs = len(coefs)
	try:
		with open(fileName, "a+") as f:
			l = list("\n")
			l.append("//Description: %s" % (description))
			l.append("%s = " % (prefixStr))
			for i, coef in enumerate(coefs):
				l.append("%g * pow(x, %d) + " % (coef, num_of_coefs -1 - i))
				if i == num_of_coefs - 2:
					break
			
			l.append("%g;" % (coefs[num_of_coefs -1]))
			f.write("\n".join(l))
			f.close()
	except IOError as e:
		print "I/O error({0}): {1}".format(e.errno, e.strerror)

# Read components values from netlist
def _getValByRefDes(lines, refDes):
	#Use reversed() to read main schematic from 
	#.end and avoid included models
	for line in reversed(lines): 
		if line == "*==============  Begin SPICE netlist of main design ============":
			break

		split = parse("%s {} {} {}" % (refDes), line)
		if split != None:
			return split[2]

def _metricConvert(val):
	num = re.findall(r'\d+', val)
	num = float(''.join(map(str,num)))
	letter = re.findall("[a-zA-Z]+", val)
	return {
        'M': num*1e6,
		'k': num*1e3,
        'm': num*1e-3,
		'u': num*1e-6,
		'n': num*1e-9,
		'p': num*1e-12,
    }[letter[0]]

def getValByRefDes(lines, refDes):
	#Find value, parse and apply metric conversion	
	return _metricConvert(_getValByRefDes(lines, refDes))

# Some info
descriptionHeader = """
//BOSS OC-2 partial emulation header file.
//Generated automatically using oc_2.py script.
//So, do not modify it.
//Also, see description in the .odg file
"""

# Set to True, if you want to learn figures with plots
showPlots = True

# Predefinitions
FS=48000.0
filtersOrder = 3
polyOrder = 12

# Filters emulation
f1_mag = get_ac("oc_2_partial_emulation_0.sch", "out_f1", 20, 20, FS/2)
f2_mag = get_ac("oc_2_partial_emulation_0.sch", "out_f2", 20, 20, FS/2)
f3_mag = get_ac("oc_2_partial_emulation_0.sch", "out_f3", 20, 20, FS/2)

# Emulate cached filters using butterworth function,
# *_cutoff values picked up visually from plots
f1_cutoff = lp_freq(f1_mag, -3)
b1, a1 = signal.butter(filtersOrder, 2*f1_cutoff/FS, 'lowpass')
plot_ac_to_compare(f1_mag, b1, a1, FS, showPlots)

f2_cutoff = lp_freq(f2_mag, -3)
b2, a2 = signal.butter(filtersOrder, 2*f2_cutoff/FS, 'lowpass')
plot_ac_to_compare(f2_mag, b2, a2, FS, showPlots)

f3_cutoff = lp_freq(f3_mag, -3)
b3, a3 = signal.butter(filtersOrder, 2*f3_cutoff/FS, 'lowpass')
plot_ac_to_compare(f3_mag, b3, a3, FS, showPlots)

# Emulate trigger filters using bilinear transform
#The values are cached from gschem file "oc_2_partial_emulation_1.sch"
netlist = _mk_spice_netlist("oc_2_partial_emulation_1.sch")

R1=getValByRefDes(netlist, "R1")
C1=getValByRefDes(netlist, "C1")
R2=getValByRefDes(netlist, "R2")
C2=getValByRefDes(netlist, "C2")
R9=getValByRefDes(netlist, "R9")

# Some bilinear transform usage: see oc_2.dsp and *_1.sch to understand, what is going on.
b41_1, a41_1 = scipy.signal.bilinear ([1.0], [R1*C1, 1.0], FS)
b41_2, a41_2 = scipy.signal.bilinear ([C2*R9,1.0], [C2*(R2+R9),1.0], FS)
b42, a42 = scipy.signal.bilinear ([C2*(R2+R9), 1.0], [C1*C2*(R2+R9)*R1, C2*(R2+R9)+R1*(C1+C2), 1.0], FS)

R6=getValByRefDes(netlist, "R6")
C4=getValByRefDes(netlist, "C4")
b_int, a_int = scipy.signal.bilinear ([1.0], [R6*C4, 1.0], FS)

# Switches emulation
opened_state = get_dc("oc_2_partial_emulation_0.sch", "sw_out_opened", "V3", 0.1, -5, 5)
vin1, vout1 = parse_data(opened_state)
f_opened = np.poly1d(np.polyfit(vin1, vout1, polyOrder))
plot_dc_to_compare(opened_state, f_opened, showPlots)

closed_state = get_dc("oc_2_partial_emulation_0.sch", "sw_out_closed", "V4", 0.1, -5, 5)
vin2, vout2 = parse_data(closed_state)
f_closed = np.poly1d(np.polyfit(vin2, vout2, polyOrder))
plot_dc_to_compare(closed_state, f_closed, showPlots)

# All data ready, start file exporting
outputFilePath = os.path.dirname(os.path.realpath(__file__))
outputFilePath += "/oc_2.lib"

f = open(outputFilePath, "w")
f.write(descriptionHeader)
f.close()

# Save filters
save_filter_to_file(outputFilePath, b1, a1, "f1", "Filter 1")
save_filter_to_file(outputFilePath, b2, a2, "f2", "Filter 2")
save_filter_to_file(outputFilePath, b3, a3, "f3", "Filter 3")

save_filter_to_file(outputFilePath, b41_1, a41_1, "f41_1", "Filter 4")
save_filter_to_file(outputFilePath, b41_2, a41_2, "f41_2", "Filter 4")
save_filter_to_file(outputFilePath, b42,   a42,   "f42",   "Filter 4")
save_filter_to_file(outputFilePath, b_int, a_int, "fint",  "Integration filter")

# Save switches curves
save_dc_curve_to_file(outputFilePath, f_opened, 
	"sw_opened(x)", "Switch opened state curve")

save_dc_curve_to_file(outputFilePath, f_closed, 
	"sw_closed(x)", "Switch closed state curve")


