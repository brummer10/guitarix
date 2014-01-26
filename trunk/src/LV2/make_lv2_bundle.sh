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
faustdir=./faust
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
  $prec "${faustopt[@]}" -o gx_${bname}.lv2/"$bname.cc" ${faustdir}/"$1"

cp -r gx_sceleton.lv2/* gx_${bname}.lv2/ 
cd ./gx_${bname}.lv2 && rename 's/sceleton/'${bname}'/g' * && sed -i 's/sceleton/'${bname}'/g' *

cat "$bname.cc" | sed -n '/enum/,/PortIndex/p' |  sed '/enum/d;/PortIndex/d;/{/d;/}/d'>ports
sed -i -e '/EFFECTS_INPUT/r ports' "gx_$bname.h"

cat "$bname.cc" | sed -n '/data;/{p;g;1!p;};h' | sed 's/ , /\n/;s/.*\n//;s/case//g;s/,/ ;/g;s/://g;s/	 //g;s/$/;/' | sed '$!N;s/\n/ /'>ports
cat "$bname.cc" | sed -n '/value_pair/{p;n;1!p;};h' | sed 's/{/\n/;s/.*\n//;s/ , /\n/;s/.*\n//;s/case//g;s/}//g;s/{//g;s/;//g;s/,/ ;/g;s/://g;s/	 //g;s/;0//g;s/$/;/' > enums

enum_var=$(echo '        lv2:portProperty lv2:integer;
        lv2:portProperty lv2:enumeration ; ')
j=2;
d=0
match=0

while IFS=$';' read -r -a myArray
do
  while IFS=$';' read -r -a myEnum
  do
    if [ -z "${myEnum[0]}" ]; then
      match=0
      echo "VAR is unset or set to the empty string"
    else
      a=${#myEnum[@]} 
      if (($a==1))
      then
        if [ ${myArray[4]} == ${myEnum[0]} ]
        then
          match=1
          break
        fi
      else
        match=0
        FLOAT=${myArray[1]}
        i=${FLOAT/\.*}
        for (( c=0; c<a; c++ ))
        do 
          enum_var1+="        lv2:scalePoint [rdfs:label "${myEnum[d]}"; rdf:value "${i}"];\n"
          i=$[i+1]
          d=$[d+1]
        done
        d=0
      fi
    fi
  sed -i -e "1d" enums
  done < enums
  echo '      , [
        a lv2:InputPort ,
            lv2:ControlPort ;
        lv2:index' $j' ;
        lv2:symbol "'${myArray[4]}'" ;
        lv2:name "'${myArray[4]}'" ;'
  echo '        lv2:default '${myArray[0]}' ;
        lv2:minimum '${myArray[1]}' ;
        lv2:maximum '${myArray[2]}' ;'
  if (($match==1))
  then
    echo '        lv2:portProperty lv2:integer;
        lv2:portProperty lv2:enumeration ; '
    echo -e "$enum_var1"
    enum_var1=""
    match=0
  fi
  echo -n '    ]'
  j=$[j+1]
done < ports >> gx_$bname.ttl
echo "." >> gx_$bname.ttl
rm -rf ports
rm -rf enums


echo "Okay, gx_${bname}.lv2 is done" 
