#!/bin/bash

#### export a guitarix preset-bank including settings for LADSPA plugins
#### as preset-bank-name.tar.bz2. use  -e preset-bankname
#### import guitarix preset-bank from the preset-bank-name.tar.bz2 
#### use -i preset-bankname. 
#### the script must run from the same directory
#### where the preset-bank-name.tar.bz2 is located

conf="none";
file="no";
while getopts eie:h o
do case "$o" in
    e)  conf="export";;
    i)  conf="import";;
    h)  echo "Usage: $0 [-e|-i] <guitarix-preset-bank-name> " ;
        echo "      -e = export guitarix-preset-bank " ;
        echo "      -i = import guitarix-preset-bank " && exit 1;;
    *)  echo "Usage: $0 [-e|-i] <guitarix-preset-bank-name> " ;
        echo "      -e = export guitarix-preset-bank " ;
        echo "      -i = import guitarix-preset-bank " && exit 1;;
esac
done

# Reset $@
shift `echo $OPTIND-1 | bc`;
file=$1;
DIR=$( cd "$( dirname "$0" )" && pwd );

if [ -n "$file" ];then
if grep -q export <<<$conf;then
cd $HOME/.config/guitarix;
tar -cf $DIR/$file.tar.bz2 --bzip2 banks/$file.gx plugins/*.js ladspa_defs.js;
echo "create $DIR/$file.tar.bz2";
echo "done";
exit 0;
elif grep -q import <<<$conf;then
tar -xjkf $file.tar.bz2 -C $HOME/.config/guitarix/ --exclude ladspa_defs.js;
echo "extract $file.tar.bz2 to $HOME/.config/guitarix/";
tar -xf $file.tar.bz2 ladspa_defs.js;
cat  $HOME/.config/guitarix/ladspa_defs.js >> ladspa_defs.js;
sort -u ladspa_defs.js | sed -e 's/^]//' -e '/^$/d' > ladspa_opt.js ;
echo "]" >> ladspa_opt.js ;
cat ladspa_opt.js > $HOME/.config/guitarix/ladspa_defs.js;
rm "ladspa_opt.js";
rm "ladspa_defs.js";
echo "done";
exit 0;
fi
fi
echo "Error: please use with [-e |-i] <guitarix-preset-bank-name>";
exit 0;
