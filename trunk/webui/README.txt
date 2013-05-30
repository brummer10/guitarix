This directory contains the user interface for controlling a headless
(embedded) guitarix with a browser on a smartphone or tablet (just
some basic functionality at the moment).


--------------- downloading the Enyo framework ------------

The web based frontend uses enyo (http://enyojs.com, distributed under
Apache License, Version 2.0) as JavaScript framework. It's included as
a git submodule and in turn contains further submodules. It's meant to
be readonly (but you can change the commit id's to use for the
submodules). If you really need to change anything permanently it's
better to discuss that with the enyo project, or at least you need to
fork the git archive on github (then you can publish changes made to
enyo in that git archive and reference it as submodule in Guitarix).

To download the submodules you have to chdir to the Guitarix toplevel
working directory and then:

$ git submodule update --init
$ cd trunk/webui/bootplate/
$ git submodule update --init


--------------- Test it on a Desktop PC ---------------

1. start guitarix:

.../guitarix -N

2. start the websockify program from the current directory (webui):

python -m websockify.websocketproxy --web=. '*':8000 localhost:7000

3. open the URL http://localhost:8000 in the desktop browser

You should be redirected to debug.html. index.html expects preprocessed
files which can be generated with the deploy script:

./deploy.sh

This script creates the build/ directory which is used in index.html.

deploy.sh needs the node program from node.js. For Debian/Ubuntu:

# apt-get install nodejs-legacy

(The program in the nodejs package is named "nodejs". The package
nodejs-legacy depends on nodejs and installs a symbolic link for the
name "node".)

--------------- Deployable version ---------------

The script ./deploy.sh also creates the deploy/webui/ directory tree
with a deployable version. You can move it anywhere to make it
accessable by a web server (it should only use relative paths, you can
rename its top level directory "webui" to something else).

The deployable version can also be loaded in the configuration
described above with 

http://localhost:8000/deploy/webui/

The deployable version uses a manifest.appcache document to tell a
HTML5 browser which documents to cache for offline usage (then only
the websocket connection to Guitarix is needed).


--------------- Use it on Android devices ---------------

For using it with an Android device install the firefox browser (the
standard Android browser doesn't support websockets as of Android
version 4). It's also recommended to install the Firefox add-on "Full
Screen" (use the added menu button to switch the display to fullscreen).


--------------- Other notes ---------------

The included websockify program (https://github.com/kanaka/websockify.git)
is modified to allow a websocket connection with utf8 text frames and to
recognize line separators as message delimiters in the JSON-RPC stream
from guitarix.
