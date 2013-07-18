#! /bin/bash
set -e
cd `dirname $0`
ddir=deploy/webui
bootplate/tools/deploy.sh
cp -L --remove-destination assets/* $ddir/assets
FILES=$((cd $ddir && find * -type f ! -name LICENSE\*.txt) | sort)
pcl() { md5sum source/manifest.appcache && cd $ddir && md5sum -b $FILES; }
CSUM=$(pcl | md5sum | cut -d' ' -f1)
eval "echo \"$(cat source/manifest.appcache)\"" >$ddir/manifest.appcache
