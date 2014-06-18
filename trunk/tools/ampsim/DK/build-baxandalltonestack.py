import os
from analog import *

schema = "baxandalltonestack.sch"
path = "tmp"
module_id = "baxandall"
mod = os.path.join(path, module_id+".so")


# create plugin
c1 = Circuit()
c1.plugindef = dk_simulator.PluginDef(module_id)
c1.plugindef.name = "Baxandall"
c1.plugindef.id = "baxandall"
c1.set_module_id(module_id)
c1.read_gschem(schema)
c1.create_faust_module()
