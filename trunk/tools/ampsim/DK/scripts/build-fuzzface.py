import sys; sys.path.append(".")
import os ; os.chdir("../")
from analog import *

schema = "gschem-schematics/FuzzfaceRogerMayer.sch"
path = "tmp"
module_id = "fuzzfaceRM"
mod = os.path.join(path, module_id+".so")


# create plugin
c1 = Circuit()
c1.plugindef = dk_simulator.PluginDef(module_id)
c1.plugindef.name = "Fuzz Face"
c1.plugindef.description = "J Hendrix Fuzz Face simulation"
c1.plugindef.category = "Distortion"
c1.plugindef.id = "fuzzface"
c1.set_module_id(module_id)
c1.read_gschem(schema)
c1.create_faust_module()
