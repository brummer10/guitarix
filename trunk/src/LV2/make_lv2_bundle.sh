#! /bin/bash

# use to copy the LV2 bundle gx_sceleton.lv2 to gx_${name}.lv2
# were ${name} is the first arg on comandline, usualy the dsp file.
# the dsp file needs to be stored in the faust folder.

function usage() {
  echo "usage: make_lv2_bundle {options} <dsp-file> [<module-name>]"
  echo "options:"
  echo "    -s:   faust use single precision"
  echo "    -d:   faust use double precision (default)"
  echo "    -V:   faust use vectorize"
  echo "    -S x: faust use vector size x"
  exit 1
}
tooldir=../../tools
instdir="$tooldir"/.."$(dirname "$0")"
prec="--double"
faustopt=()
copy=0
while getopts sdVS:c OPT; do
  case "$OPT" in
  h) usage;;
  s) prec="--float";;
  d) prec="--double";;
  V) faustopt+=(--vectorize);;
  S) faustopt+=(--add="-vs $OPTARG");;
  c) copy=1;;
  \?) usage;;
  esac
done
shift $(expr $OPTIND - 1)
[ "$1" = "" ] && usage
if [ "$2" = "" ]; then
  bname="$(basename "$1" .dsp)"
else
  bname="$2"
fi

if [ ! -d gx_${bname}.lv2 ]; then
mkdir -p gx_${bname}.lv2
else
echo "Directory gx_${bname}.lv2 allready exist, should we remove it? Yes/No"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) rm -rf gx_${bname}.lv2; mkdir -p gx_${bname}.lv2; break;;
        No ) echo "exit"; exit;;
    esac
done
fi

set -e
"$tooldir"/dsp2cc  --init-type=plugin-lv2  \
  $prec "${faustopt[@]}" -o gx_${bname}.lv2/"$bname.cc" ./faust/"$1"

cp -r gx_sceleton.lv2/* gx_${bname}.lv2/ 
cd ./gx_${bname}.lv2 && rename 's/sceleton/'${bname}'/g' * && sed -i 's/sceleton/'${bname}'/g' *

cat "$bname.cc" | sed -n '/enum/,/PortIndex/p' |  sed '/enum/d;/PortIndex/d;/{/d;/}/d'>ports
sed -i -e '/EFFECTS_INPUT/r ports' "gx_$bname.h"
rm -rf ports

echo "Okay, done, you need to add the used ports to gx_$bname.ttl" 
 # TO DO
 # add ports to bname.ttl 
