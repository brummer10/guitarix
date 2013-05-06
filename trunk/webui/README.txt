This directory contains the user interface for controlling a headless
(embedded) guitarix with a browser on a smartphone or tablet (just
some basic functionality at the moment).

To test it on a Desktop PC:

1. start guitarix:

.../guitarix -N

2. start the websockify program from the current directory:

python -m websockify.websocketproxy --web=. '*':8000 localhost:7000

3. open the URL http://localhost:8000 in the desktop browser

For using it with an Android device install the firefox browser (the
standard Android browser doesn't support websockets as of Android
version 4). It's also recommended to install the Firefox add-on "Full
Screen" (use the added menu button to switch the display to fullscreen).

The included websockify program (https://github.com/kanaka/websockify.git)
is modified to allow a websocket connection with utf8 text frames and to
recognize line separators as message delimiters in the JSON-RPC stream
from guitarix.
