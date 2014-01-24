#! /bin/bash

# use to copy the LV2 bundle gx_sceleton.lv2 to gx_${name}.lv2
# were ${name} is the first arg on comandline, usualy the dsp file name.
# the dsp file needs to be stored in the faust folder.

name=$*
mkdir -p gx_${name}.lv2
cp -r gx_sceleton.lv2/* gx_${name}.lv2/ 
cd ./gx_${name}.lv2 && rename 's/sceleton/'${name}'/g' * && sed -i 's/sceleton/'${name}'/g' *

 # TO DO
 # add ${name}.dsp to wscript in /faust directory
 # add used ports from generated ${name}.cc file to ${name}.h struct PortIndex
 # and to gx_${name}.ttl
