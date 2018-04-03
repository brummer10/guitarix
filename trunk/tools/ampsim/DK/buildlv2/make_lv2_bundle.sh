#! /bin/bash

# use to copy the LV2 bundle gx_sceleton.lv2 to gx_${name}.lv2
# generate a C++ file from the faust.dsp source (by dsp2cc)
# generate a acording name.ttl file
# were ${name} is the first arg on comandline, usualy the dsp file.
# the dsp file needs to be stored in the faust folder.

########################## functions ###################################

function usage() {
  echo "usage: make_lv2_bundle {options} <cc|cpp|dsp-file> [<plugin class>] "
  echo "options:"
  echo "    -h:   show this help"
  echo "    -s:   faust use single precision"
  echo "    -d:   faust use double precision (default)"
  echo "    -V:   faust use vectorize"
  echo "    -S x: faust use vector size x"
  echo "    -p:   path/to/source/sourcefile "
  echo "    -n    effect name "
  exit 1
}

function get_basename_ext() {
case "$extension" in
  dsp)
    if [ "$2" = "" ]; then
      bname="$(basename "$1" .dsp)"
    else
      bname="$(basename "$1" .dsp)"
      effect_category="$2"
    fi;;
  cc)
    if [ "$2" = "" ]; then
      bname="$(basename "$1" .cc)"
    else
      bname="$(basename "$1" .cc)"
      effect_category="$2"
    fi;;
  cpp)
    if [ "$2" = "" ]; then
      bname="$(basename "$1" .cpp)"
    else
      bname="$(basename "$1" .cpp)"
      effect_category="$2"
    fi;;
  *)
   echo -e $RED"file extension not supported"$NONE ; usage;;
esac
}

function select_plugin_type() {
  echo -e $RED'Please select a Plugin type from the list'$NONE
  select type in "${Plugin_types[@]}" ; do 
    if [[ $type == "quit" ]]; then
      break
    fi
    effect_category="$type"
    if [ ! -z "$type" ]; then
      break;
    else
      echo -e $RED"Select a number from the list!"$NONE
    fi
  done
}

function check_plugin_type() { 
  for I in "${Plugin_types[@]}"; do
    [[ $I == $effect_category ]] && return 0
  done
  select_plugin_type
  return 0
}

function check_dir() {
  if [ ! -d gx_${bname}.lv2 ]; then
    mkdir -p gx_${bname}.lv2
  else
    echo -e $RED"Directory gx_${bname}.lv2 allready exist, should we remove it? Yes/No"$NONE
    select yn in "Yes" "No"; do
      case $yn in
        Yes ) rm -rf gx_${bname}.lv2; mkdir -p gx_${bname}.lv2; break;;
        No ) echo  -e $RED"exit"$NONE; exit;;
      esac
    done
  fi
}

function dsptocc() {
  if [ -f ${faustdir}/"$bname.$extension" ] ; then
    if [ $extension == "dsp" ] ; then
      echo -e $BLUE"generate $bname.cc and copy to gx_$bname.lv2"$NONE
      set -e
      "$tooldir"/dsp2cc  --init-type=plugin-lv2  \
        $prec "${faustopt[@]}" -o gx_${bname}.lv2/"$bname.cc" ${faustdir}/"$bname.dsp"
    else
      echo -e $BLUE"copy $bname.$extension to gx_$bname.lv2/$bname.cc"$NONE
      cp -r ${faustdir}/"$bname.$extension" gx_${bname}.lv2/"$bname.cc"
    fi
  else
    echo  -e $RED"error: "${faustdir}/"$bname.$extension not found"$NONE; exit;
  fi
}


function copy_sceleton() {
  grep 'stereo_audio' gx_${bname}.lv2/$bname.cc >/dev/null && stereo="true"  || stereo="false"
  if [ "$stereo" == "true" ] ; then
    grep 'stereo_audio = 0;' gx_${bname}.lv2/$bname.cc >/dev/null && stereo="false"  || stereo="true"
  fi

  if [ "$stereo" == "false" ] ; then
    echo -e "copy gx_sceleton.lv2 to "$BLUE"gx_$bname.lv2"$NONE" and rename/replace strings to "$BLUE"$bname"$NONE
    cp -r gx_sceleton.lv2/* gx_${bname}.lv2/ 
    j=3
  else
    echo -e "copy gx_sceleton_stereo.lv2 to "$BLUE"gx_$bname.lv2"$NONE" and rename/replace strings to "$BLUE"$bname"$NONE
    cp -r gx_sceleton_stereo.lv2/* gx_${bname}.lv2/ 
    j=4
  fi
  cd ./gx_${bname}.lv2 && find . -depth -exec rename 's/sceleton/'${bname}'/g' {} + && find . -depth -type f -exec  sed -i 's/sceleton/'${bname}'/g' {} +
}

function grep_ports_enums() {
  echo -e "grep ports and copy them to  "$BLUE"gx_$bname.h"$NONE
  cat "$bname.cc" | sed -n '/enum/,/PortIndex/p' |  sed '/enum/d;/PortIndex/d;/{/d;/}/d'>ports

  if [ "$stereo" == "false" ] ; then
    sed -i -e '/BYPASS/r ports' "plugin/gx_$bname.h"
  else
    sed -i -e '/EFFECTS_INPUT1/r ports' "plugin/gx_$bname.h"
  fi
  echo -e "grep ports values and enums and copy them to "$BLUE"gx_$bname.ttl"$NONE
  cat "$bname.cc" | sed -n '/data;/{p;g;1!p;};h' | sed 's/ , /\n/;s/.*\n//;s/case//g;s/,/ ;/g;s/://g;s/	 //g;s/  //g;s/ //g;s/$/;/' | sed '$!N;s/\n//'>ports
  cat "$bname.cc" | sed -n '/value_pair/{p;n;1!p;};h' | sed 's/{/\n/;s/.*\n//;s/ , /\n/;s/.*\n//;s/case//g;s/}//g;s/{//g;s/;//g;s/,/ ;/g;s/://g;s/	 //g;s/;0//g;s/  //g;s/ //g;s/$/;/' > enums
}

function make_ui() {
  echo "generate GUI"
  COUNTER=0
  PCOUNTER=0
  ECOUNTER=0
  match=0
  enum_var1=""
  enum_var=""
  cat enums >enums1
  while IFS=$';' read -r -a line; do
    while IFS=$';' read -r -a myEnum; do
      if [ -z "${myEnum[0]}" ]; then
        match=0
      else
        a=${#myEnum[@]} 
        if (($a==1)); then
          if [ ${line[4]} == ${myEnum[0]} ]; then
            match=1
            sed -i -e "1,2d" enums1
            break
          fi
        else
          match=0
          FLOAT=${myPorts[1]}
          i=${FLOAT/\.*}
          i=${i/e/}
          enum_var1+="Glib::ustring enum"${line[4]}"[] = {"
          for (( c=0; c<a; c++ )); do 
            enum_var1+="${myEnum[c]},"
            i=$[i+1]
          done
          enum_var2="${enum_var1::-1}" 
          enum_var2+="};\n"
        fi
      fi
    done < enums1
    if (($match==1)); then
      conts+='    ui->adj['${COUNTER}'] = gtk_adjustment_new( '${line[0]}', '${line[1]}', '${line[2]}', '${line[3]}', '${line[3]}'*10.0, 0);\n'
      conts+='    ui->knob['${COUNTER}'] = gtk_switch_new_with_adjustment(GTK_ADJUSTMENT(ui->adj['${COUNTER}']));\n'
      conts+='    ui->label['${COUNTER}'] = gtk_label_new(\"'${line[4]}'\");\n'
      conts+='    ui->vkbox['${COUNTER}'] = gtk_vbox_new(FALSE, 0);\n\n'
      conts+='    gtk_widget_modify_fg (ui->label['${COUNTER}'], GTK_STATE_NORMAL, \&color);\n'
      conts+='    style = gtk_widget_get_style(ui->label['${COUNTER}']);\n'
      conts+='    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);\n'
      conts+='    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);\n'
      conts+='    gtk_widget_modify_font(ui->label['${COUNTER}'], style->font_desc);\n\n'

      conts+='    gtk_box_pack_start(GTK_BOX(ui->hbox), ui->vkbox['${COUNTER}'], TRUE, TRUE, 0);\n'
      conts+='    gtk_box_pack_start(GTK_BOX(ui->vkbox['${COUNTER}']), ui->knob['${COUNTER}'], TRUE, TRUE, 0);\n'
      conts+='    gtk_box_pack_start(GTK_BOX(ui->vkbox['${COUNTER}']), ui->label['${COUNTER}'], FALSE, FALSE, 0);\n'
      conts+='    ui->args['${COUNTER}'] = (struct gx_args*) malloc(sizeof(struct gx_args));\n'
      conts+='    ui->args['${COUNTER}']->ui = ui;\n'
      conts+='    ui->args['${COUNTER}']->port_index = (int)'${line[4]}';\n'
      conts+='    g_signal_connect(G_OBJECT(ui->adj['${COUNTER}']), "value-changed",\n'
      conts+='          G_CALLBACK(ref_value_changed),(gpointer*)ui->args['${COUNTER}']);\n\n'
      let COUNTER=COUNTER+1 

      enum_var+='  '$enum_var2
      enum_var+="  static const size_t enum"${line[4]}"_size = sizeof(enum"${line[4]}") / sizeof(enum"${line[4]}"[0]);\n"
      enum_var+="  make_selector_box(\&m_vboxs["${ECOUNTER}"],\""${line[4]}"\", enum"${line[4]}", enum"${line[4]}"_size, 0,1.0, "${line[4]}");\n"
      ports+='    case '${line[4]}':\n      return \&m_selector['${ECOUNTER}'];\n'
      let ECOUNTER=ECOUNTER+1 
      enum_var1=""
      match=0
    else
      enum_var1=""
      conts+='    ui->adj['${COUNTER}'] = gtk_adjustment_new( '${line[0]}', '${line[1]}', '${line[2]}', '${line[3]}', '${line[3]}'*10.0, 0);\n'
      conts+='    ui->knob['${COUNTER}'] = gtk_knob_new_with_adjustment(GTK_ADJUSTMENT(ui->adj['${COUNTER}']));\n'
      conts+='    ui->label['${COUNTER}'] = gtk_label_new(\"'${line[4]}'\");\n'
      conts+='    ui->vkbox['${COUNTER}'] = gtk_vbox_new(FALSE, 0);\n\n'
      conts+='    gtk_widget_modify_fg (ui->label['${COUNTER}'], GTK_STATE_NORMAL, \&color);\n'
      conts+='    style = gtk_widget_get_style(ui->label['${COUNTER}']);\n'
      conts+='    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);\n'
      conts+='    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);\n'
      conts+='    gtk_widget_modify_font(ui->label['${COUNTER}'], style->font_desc);\n\n'

      conts+='    gtk_box_pack_start(GTK_BOX(ui->hbox), ui->vkbox['${COUNTER}'], TRUE, TRUE, 0);\n'
      conts+='    gtk_box_pack_start(GTK_BOX(ui->vkbox['${COUNTER}']), ui->knob['${COUNTER}'], TRUE, TRUE, 0);\n'
      conts+='    gtk_box_pack_start(GTK_BOX(ui->vkbox['${COUNTER}']), ui->label['${COUNTER}'], FALSE, FALSE, 0);\n'
      conts+='    ui->args['${COUNTER}'] = (struct gx_args*) malloc(sizeof(struct gx_args));\n'
      conts+='    ui->args['${COUNTER}']->ui = ui;\n'
      conts+='    ui->args['${COUNTER}']->port_index = (int)'${line[4]}';\n'
      conts+='    g_signal_connect(G_OBJECT(ui->adj['${COUNTER}']), "value-changed",\n'
      conts+='          G_CALLBACK(ref_value_changed),(gpointer*)ui->args['${COUNTER}']);\n\n'

    #  conts+='    make_controller_box(ui->vkbox['${COUNTER}'], ui->knob['${COUNTER}'], ui->adj['${COUNTER}'], ui->label['${COUNTER}'], (const char*)\"'${line[4]}'\", ui, ui->args['${COUNTER}'], '${line[4]}');\n'
      ports+='    case '${line[4]}':\n      return \&m_bigknob['${COUNTER}'];\n'
      let COUNTER=COUNTER+1 
    fi
  done < ports
  #let PCOUNTER=COUNTER-1
  sed -i "s/PORTS/${ports}/g;s/CONTS/${conts}/g;s/VARI/${COUNTER}/g;s#ENUMS#${enum_var}#g;s/VAI/${ECOUNTER}/g;" gui/gx_${bname}_ui.c  
 #  sed -i "s/VAR/${PCOUNTER}/g;s/VAI/${ECOUNTER}/g;" gx_${bname}_ui.c
  rm -rf enums1
  if [ ! -z "$effect_name" ]; then
    EFNAME=${effect_name^^}
    efname=${effect_name}
    sed -i 's/EffectNAME/'"${effect_name}"'/g'  gui/gx_${bname}_ui.c
    sed -i 's/EFNAME/'"${EFNAME}"'/g'  gui/gx_${bname}_ui.c
    sed -i 's/EFNAME/'"${EFNAME}"'/g'  gui/gtkknob.cc
    sed -i 's/efname/'"${efname}"'/g'  gui/gtkknob.cc
    sed -i 's/EFNAME/'"${EFNAME}"'/g'  gui/gtkknob.h
    sed -i 's/efname/'"${efname}"'/g'  gui/gtkknob.h
    sed -i 's/EFNAME/'"${EFNAME}"'/g'  gui/paintbox.cpp
    sed -i 's/efname/'"${efname}"'/g'  gui/paintbox.cpp
    sed -i 's/EFNAME/'"${EFNAME}"'/g'  gui/paintbox.h
    sed -i 's/efname/'"${efname}"'/g'  gui/paintbox.h
    echo -e "set plugin name to "$BLUE"Gx$effect_name"$NONE
  else
    EFNAME=${bname^^}
    efname=${bname}
    sed -i 's/EffectNAME/'${bname}'/g'  gui/gx_${bname}_ui.c
    sed -i 's/EFNAME/'"${EFNAME}"'/g'  gui/gx_${bname}_ui.c
    sed -i 's/EFNAME/'"${EFNAME}"'/g'  gui/gtkknob.cc
    sed -i 's/efname/'"${efname}"'/g'  gui/gtkknob.cc
    sed -i 's/EFNAME/'"${EFNAME}"'/g'  gui/gtkknob.h
    sed -i 's/efname/'"${efname}"'/g'  gui/gtkknob.h
    sed -i 's/EFNAME/'"${EFNAME}"'/g'  gui/paintbox.cpp
    sed -i 's/efname/'"${efname}"'/g'  gui/paintbox.cpp
    sed -i 's/EFNAME/'"${EFNAME}"'/g'  gui/paintbox.h
    sed -i 's/efname/'"${efname}"'/g'  gui/paintbox.h
    echo -e "set plugin name to "$BLUE"Gx$bname"$NONE
  fi
}

function make_ttl() {
  match=0

  while IFS=$';' read -r -a myPorts; do
    while IFS=$';' read -r -a myEnum; do
      if [ -z "${myEnum[0]}" ]; then
        match=0
      else
        a=${#myEnum[@]} 
        if (($a==1)); then
          if [ ${myPorts[4]} == ${myEnum[0]} ]; then
            match=1
            sed -i -e "1,2d" enums
            break
          fi
        else
          match=0
          FLOAT=${myPorts[1]}
          i=${FLOAT/\.*}
          i=${i/e/}
          for (( c=0; c<a; c++ )); do 
            enum_var1+="        lv2:scalePoint [rdfs:label "${myEnum[c]}"; rdf:value "${i}"];\n"
            i=$[i+1]
          done
        fi
      fi
    done < enums
    echo '      , [
        a lv2:InputPort ,
            lv2:ControlPort ;
        lv2:index' $j' ;
        lv2:symbol "'${myPorts[4]}'" ;
        lv2:name "'${myPorts[4]}'" ;'
    echo '        lv2:default '${myPorts[0]}' ;
        lv2:minimum '${myPorts[1]}' ;
        lv2:maximum '${myPorts[2]}' ;'
    if (($match==1)); then
      echo '        lv2:portProperty lv2:integer;
        lv2:portProperty lv2:enumeration ; '
      echo -e "$enum_var1"
      enum_var1=""
      match=0
    fi
    echo -n '    ]'
    j=$[j+1]
    enum_var1=""
  done < ports >> plugin/gx_$bname.ttl
  echo " .

<http://guitarix.sourceforge.net/plugins/gx_${bname}_gui#_${bname}_>
  a guiext:GtkUI;
  guiext:binary <gx_${bname}_ui.so>;
  guiext:requiredFeature guiext:makeResident;
  ." >> plugin/gx_$bname.ttl

  if [ ! -z "$effect_category" ]; then
    sed -i 's/EffectPlugin/'${effect_category}'/g'  plugin/gx_${bname}.ttl
    echo -e "set plugin class to "$BLUE"$effect_category"$NONE
  fi
  if [ ! -z "$effect_name" ]; then
    sed -i 's/EffectNAME/'"${effect_name}"'/g'  plugin/gx_${bname}.ttl
  else
    sed -i 's/EffectNAME/'${bname}'/g'  plugin/gx_${bname}.ttl
  fi
 
  rm -rf ports
  rm -rf enums
}

function byby() {
  mv -f "$bname.cc" "dsp/$bname.cc"
  echo -e $BLUE"Okay, gx_${bname}.lv2 is done"$NONE
  echo  -e $BLUE"Now you can enter ./gx_${bname}.lv2 
  and run make && make install"$NONE
}

########################## supported plugin types ######################

Plugin_types=(
        'DelayPlugin'
            'ReverbPlugin'
        'DistortionPlugin'
            'WaveshaperPlugin'
        'DynamicsPlugin'
            'AmplifierPlugin'
            'CompressorPlugin'
            'EnvelopePlugin'
            'ExpanderPlugin'
            'GatePlugin'
            'LimiterPlugin'
        'FilterPlugin'
            'AllpassPlugin'
            'BandpassPlugin'
            'CombPlugin'
            'EQPlugin'
               'MultiEQPlugin'
                'ParaEQPlugin'
            'HighpassPlugin'
            'LowpassPlugin'
        'GeneratorPlugin'
            'ConstantPlugin'
            'InstrumentPlugin'
            'OscillatorPlugin'
        'ModulatorPlugin'
            'ChorusPlugin'
            'FlangerPlugin'
            'PhaserPlugin'
        'ReverbPlugin'
        'SimulatorPlugin'
            'ReverbPlugin'
        'SpatialPlugin'
        'SpectralPlugin'
            'PitchPlugin'
        'UtilityPlugin'
            'AnalyserPlugin'
            'ConverterPlugin'
            'FunctionPlugin'
            'MixerPlugin' )



###################### global variables ################################

BLUE="\033[1;34m"
RED="\033[1;31m"
NONE="\033[0m"

tooldir=../../../
faustdir=./tmp
instdir="$tooldir"/.."$(dirname "$0")"
prec="--double"
faustopt=()
copy=0
bname=""
effect_category=""
effect_name=""

############################# main #####################################

while getopts hn:sdVSp:c OPT; do
  sc=0
  case "$OPT" in
  h) usage;;
  n) effect_name=$OPTARG;;
  s) prec="--float";;
  d) prec="--double";;
  V) faustopt+=(--vectorize);;
  S) faustopt+=(--add="-vs $OPTARG");;
  p) faustdir="$(dirname "$2")/"
     file="$(basename "$2")"
     sc=1;;
  c) copy=1;;
  \?) usage;;
  esac
  if [ $OPTIND != 1 ] # This test fails only if multiple options are stacked
                        # after a single -.
  then    shift $((OPTIND - 1 + sc))
     OPTIND=1
  fi
done

#shift $(expr $OPTIND - 1)
#[ "$1" = "" ] && usage
extension="${file##*.}"

######################## function calls ################################

get_basename_ext "$file" "$2"
check_plugin_type && echo -e "Plugin type "$BLUE"$effect_category"$NONE
check_dir
dsptocc
copy_sceleton
grep_ports_enums
make_ui
make_ttl
byby

############################ EOF #######################################

exit
