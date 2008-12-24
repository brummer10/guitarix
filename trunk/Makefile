## makefile for guitarix by @brummer

        ## set the install Path for guitarix
	PREFIX = /usr
	LADSPAPATH = $(LADSPA_PATH)

all    :
	$(CXX) -fPIC -shared -O3 -march=native  -mfpmath=sse -ffast-math -Dmydsp=guitarix guitarix-ladspa.cpp -o guitarix.so
	$(CXX) -O3  -march=native -mfpmath=sse -ffast-math `pkg-config --cflags --libs jack gtk+-2.0 sndfile` main.cpp -o guitarix

nosse   :

	$(CXX) -fPIC -shared -O3 -Dmydsp=guitarix guitarix-ladspa.cpp -o guitarix.so
	$(CXX) -O3  `pkg-config --cflags --libs jack gtk+-2.0` guitarix.cpp -o guitarix

install:
	mkdir -p $(DESTDIR)$(LADSPAPATH)
	install guitarix.so $(DESTDIR)$(LADSPAPATH)
	install guitarix $(DESTDIR)$(PREFIX)/bin
	mkdir -p $(DESTDIR)$(PREFIX)/share/applications
	install guitarix.desktop $(DESTDIR)$(PREFIX)/share/applications
	mkdir -p $(DESTDIR)$(PREFIX)/share/guitarix
	mkdir -p $(DESTDIR)$(PREFIX)/share/pixmaps
	install ./guitarix.png $(DESTDIR)$(PREFIX)/share/pixmaps
	install ./guitarix-midi.png $(DESTDIR)$(PREFIX)/share/pixmaps
	install ./guitarix-warn.png $(DESTDIR)$(PREFIX)/share/pixmaps
	install ./rcstyles/controls.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	install ./rcstyles/controls1.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	install ./rcstyles/controls2.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	install ./rcstyles/controls3.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	install ./rcstyles/guitarix.rc $(DESTDIR)$(PREFIX)/share/guitarix
	install ./rcstyles/guitarix_pix.rc $(DESTDIR)$(PREFIX)/share/guitarix
clean  :
	rm -rf guitarix
	rm -rf *.so
	rm -rf *-stamp
	rm -rf *~
uninstall :
	rm -rf $(PREFIX)/bin/guitarix $(LADSPAPATH)/guitarix.so $(PREFIX)/share/applications/guitarix.desktop $(PREFIX)/share/pixmaps/guitarix.png $(PREFIX)/share/guitarix/guitarix.rc  $(PREFIX)/share/guitarix/controls.jpg  $(PREFIX)/share/guitarix/controls1.jpg$ (PREFIX)/share/guitarix/controls2.jpg (PREFIX)/share/guitarix/controls3.jpg $(PREFIX)/share/guitarix/guitarix_pix.rc $(PREFIX)/share/pixmaps/guitarix-midi.png $(PREFIX)/share/pixmaps/guitarix-warn.png

