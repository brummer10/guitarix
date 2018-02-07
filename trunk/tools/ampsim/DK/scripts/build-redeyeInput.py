import sys; sys.path.append(".")
import os ; os.chdir("../")
from analog import *

schema = "gschem-schematics/redeyeChump.sch"
path = "tmp"
module_id = "redeyeChump"
mod = os.path.join(path, module_id+".so")


# create plugin
c1 = Circuit()
c1.plugindef = dk_simulator.PluginDef(module_id)
c1.plugindef.lv2_plugin_type = "AmplifierPlugin"
c1.plugindef.lv2_versioned_id="redeyeChump"
c1.plugindef.name = "Redeye Tube Input Stage"
c1.plugindef.id = "redeyeChump"
c1.set_module_id(module_id)
c1.read_gschem(schema)
c1.create_faust_module()
print vars(c1)
#c1.deploy()
