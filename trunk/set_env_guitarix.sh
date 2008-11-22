# !bin/sh
# this is the environmet setup script for guitarix. feel free to use it. you can also simply start guitarix, if you feel allright with the default settings. If you move the script out of the buildtree you must comment the following lines out.

p="`echo $0 | sed 's?\(.*\)/set_env_guitarix.sh?\1?g'`"
cd $p

# autoconnect guitarix in and outputs, here you can set autoconecction ports to use for in and output. leave it blank to disable autoconnect

export GUITARIX2JACK_INPUTS=system:capture_3
export GUITARIX2JACK_OUTPUTS1=system:playback_1
export GUITARIX2JACK_OUTPUTS2=system:playback_2

# here you can set the path and the gtk.rc file to use a diferent skin, as default guitarix will look in /usr/share/guitarix


 GUITARIX_RC_PATH=./rcstyles/guitarix_pix.rc

# start guitarix with the above environmet settings. If you store guitarix and guitarix.sh in diferent floders, you must set the path to guitarix here.

./guitarix -r $GUITARIX_RC_PATH &

# sleep and exit
sleep 5
exit 

