import os
from analog import *

schema = "lineoutlevel.sch"
path = "tmp"
module_id = "lineoutlevel"
mod = os.path.join(path, module_id+".so")


# create plugin
c1 = Circuit()
c1.plugindef = dk_simulator.PluginDef(module_id)
c1.plugindef.lv2_plugin_type = "SimulatorPlugin"
c1.plugindef.lv2_versioned_id="lineoutlevel"
c1.plugindef.name = "Line Out"
c1.plugindef.id = "lineoutlevel"
c1.set_module_id(module_id)
c1.read_gschem(schema)
c1.create_faust_module()
print vars(c1)
#c1.deploy()
