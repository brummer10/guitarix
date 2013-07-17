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
