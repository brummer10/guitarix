import os
import argparse,sys

parser = argparse.ArgumentParser(description='Build script for guitarix plugins.')
parser.add_argument('-i','--input', help='Input file name [REQUIRED]',required=True)
parser.add_argument('-n','--name',help='Name for plugin [OPTIONAL]', required=False)
parser.add_argument('-s','--shortname',help='Shortname for plugin [OPTIONAL]', required=False)
parser.add_argument('-d','--description',help='Description for plugin [OPTIONAL]', required=False)
parser.add_argument('-c','--category',help='Category for plugin [OPTIONAL]', required=False)
parser.add_argument('-m','--module_id',help='Module ID for plugin [OPTIONAL]', required=False)
parser.add_argument('-p','--prefilter',help='prefilter for plugin [OPTIONAL]', required=False)
args = parser.parse_args()
 
## show values ##
schema = args.input
workfile="gschem-schematics/"+schema
name = args.name
shortname = args.shortname
description = args.description
category = args.category
module_id = args.module_id
prefilter = args.prefilter
print ("Input file: %s" % args.input )
del sys.argv[1:]

from analog import *

path = "tmp"

if not module_id:
	module_id = schema.split('.')[0].lower()
print ("module_id: %s" % module_id )
mod = os.path.join(path, module_id+".so")

#set_log_level(DEBUG)
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
print ("build plugin from: %s" % args.input)
if not prefilter:
    c1.create_faust_module()
else:
    c1.create_faust_module(pre_filter=prefilter)

#c1.deploy(".")
