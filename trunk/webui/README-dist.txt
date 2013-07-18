This is the web frontend for Guitarix.

Getting started:

- after unpacking the webui tarfile, cd into the websockify directory
  and start websockify:

  python websocketproxy.py --web=../webui '*':8000 localhost:7000

  (you can use the -D options to start the program in the background).

- start guitarix with --rpcport=7000

- open "http://localhost:8000/" in your browser

The included server is not audited for security; don't use it in an
untrusted environment.

The javascript and CSS files are generated from the code in the
guitarix git archive:

git clone git://git.code.sf.net/p/guitarix/git guitarix-git

commit-id: %C%

This files in this archive are distributed under the terms of the GNU
General Public License as published by the Free Software Foundation;
either version 2 of the License, or (at your option) any later
version.
