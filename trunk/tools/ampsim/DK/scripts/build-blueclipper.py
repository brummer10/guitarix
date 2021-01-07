import sys; sys.path.append(".")
import os ; os.chdir("../")
from analog import *
import diode_table_gen as di
import re

schema = "gschem-schematics/BlueClipper.sch"
path = "dkbuild/blueclipper"
module_id = "blueclipper"
mod = os.path.join(path, module_id+".so")
dspfile = "dkbuild/blueclipper/blueclipper"
dspfile_in = "dkbuild/blueclipper/blueclipper_in"
dspfile_out = "dkbuild/blueclipper/blueclipper_out"
category = "Extern"

# if not exist, create build dir
if not os.path.exists("dkbuild/blueclipper/"):
    os.makedirs("dkbuild/blueclipper/")

# generate diode clipping table for 1N4148 diodes
t = "Diode_clipper"
v = di.Diode_clipper("1N4148")
parser = dk_simulator.Parser(v.S, v.V, v.FS)
p = dk_simulator.get_executor(
    t, parser, v.solver, '-p', c_tempdir='/tmp', c_verbose='--c-verbose',
    c_debug_load='', linearize='', c_real=("double"))
v.generate_table(p,"dkbuild/blueclipper/1N4148_table.h")

# create plugin
c1 = Circuit()
c1.plugindef = dk_simulator.PluginDef(module_id)

if not category:
	category = "Extern"
c1.plugindef.category = category
c1.plugindef.name = "Blue Clipper"
c1.plugindef.id = "blueclipper"
c1.set_module_id(module_id)
c1.set_tempdir("dkbuild/blueclipper")
c1.keep_tempdir()
c1.read_gschem(schema)

# print netlist to get the element names
#c1.print_netlist()

# create input circuit, therefore remove the output circuit
c0 = Circuit(c1)
c0.plugindef = dk_simulator.PluginDef(module_id)
c0.plugindef.category = category
c0.plugindef.name = "Blue Clipper In"
c0.plugindef.id = "blueclipper_in"
c0.remove_element("C3")
c0.remove_element("R8")
c0.remove_element("D1")
c0.remove_element("D2")
c0.remove_element("R5")
c0.remove_element("C5")
c0.remove_element("P2")
c0.join_net("V4", "V3")
c0.save_faust_code(filename=str(dspfile_in))

# create output circuit, therefore remove the input circuit
c1.remove_element("C1")
c1.remove_element("R1")
c1.remove_element("R2")
c1.remove_element("Vcc")
c1.remove_element("OPA_L1")
c1.remove_element("R4")
c1.remove_element("R3")
c1.remove_element("C2")
#c1.remove_element("GND") # not needed
c1.join_net("V3", "V1")
c1.save_faust_code(filename=str(dspfile_out))


dspname_out = "{0}.dsp".format(dspfile_out)
uiname_out = "{0}_ui.cc".format(dspfile_out)
dspname_in = "{0}.dsp".format(dspfile_in)
uiname_in = "{0}_ui.cc".format(dspfile_in)
dspname = "{0}.dsp".format(dspfile)
uiname = "{0}_ui.cc".format(dspfile)

# contacate the ui files, here we only need the uiname_out file as no input control is given.
with open(uiname_out, 'r') as f :
  fdata = f.read()

with open(uiname, 'w') as f:
  f.write(fdata)
  

# now contacate the generated dsp files into one file
f = open(dspname_out, "a")
f.write('\n    clip = ffunction(float diodeclip(float), "1N4148_table.h", "");\n')


v = 0
pattern = re.compile("process")
with open(dspname_in, "r") as fi:
    for line in fi:
        if pattern.search(line) != None:
            v = 1
            line = line.replace("process", "p1")
            f.write("\n")
        if v:
            f.write(line)
f.close()

with open(dspname_out, 'r') as f :
  fdata = f.read()

fdata = fdata.replace('process', 'p2')
fdata +=  "\nprocess = p1 : clip : p2;"

with open(dspname, 'w') as f:
  f.write(fdata)

# now create the guitarix module
datatype="double"
pgm = os.path.abspath("../../build-faust")
opts = " " if datatype == "float" else ""
os.system("%s %s -c -k %s" % (pgm, opts, dspname))

