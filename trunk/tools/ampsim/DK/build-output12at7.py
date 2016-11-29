import os
from analog import *

schema = "output12at7.sch"
path = "tmp"
module_id = "output12at7"
mod = os.path.join(path, module_id+".so")


# create plugin
c1 = Circuit()
c1.plugindef = dk_simulator.PluginDef(module_id)
c1.plugindef.lv2_plugin_type = "AmplifierPlugin"
c1.plugindef.lv2_versioned_id="output12at7"
c1.plugindef.name = "12at7 Tube output Stage"
c1.plugindef.id = "output12at7"
c1.set_module_id(module_id)
c1.read_gschem(schema)
c1.create_faust_module()
print vars(c1)
#c1.deploy()