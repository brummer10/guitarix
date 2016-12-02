import os
from analog import *

schema = "newtilt1.sch"
path = "/home/steve/Source/guitarix-git/trunktools/ampsim/DK"
module_id = "tiltdrive"
mod = os.path.join(path, module_id+".so")


# create plugin
c1 = Circuit()
c1.plugindef = dk_simulator.PluginDef(module_id)
c1.plugindef.lv2_plugin_type = "SimulatorPlugin"
c1.plugindef.name = "Tilt Drive"
c1.plugindef.id = "tiltdrive"
c1.set_module_id(module_id)
c1.read_gschem(schema)
c1.create_faust_module()
