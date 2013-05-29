#! /bin/bash
cd `dirname $0`
counter=deploy/lastN
bootplate/tools/deploy.sh
cp bootplate/assets/favicon.ico deploy/webui/assets
REV=$(git rev-parse HEAD 2>/dev/null)
N=1
[ -e $counter ] && let N=$(< $counter)+1
sed "s/%N%/$N $REV/" source/manifest.appcache >deploy/webui/manifest.appcache
echo $N > $counter
