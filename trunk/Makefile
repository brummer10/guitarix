## makefile for guitarix by @brummer

        ## set the install Path for guitarix
	PREFIX = /usr
	LADSPAPATH = $(PREFIX)/lib/ladspa

targets-ladspa = gcrybaby.so gdistortion.so gecho.so gfreeverb.so gIR.so gmonoamp.so gmonocompressor.so guitarix.so


all    :
	$(CXX) -fPIC -shared -O3 -march=native -Dmydsp=guitarix ./ladspa/guitarix-ladspa.cpp -o guitarix.so

	$(CXX) -fPIC -shared -O3 -march=native -Dcrydsp=guitarix_crybaby ./ladspa/crybaby.cpp -o gcrybaby.so
	$(CXX) -fPIC -shared -O3 -march=native -Ddistdsp=guitarix_distortion ./ladspa/distortion.cpp -o gdistortion.so
	$(CXX) -fPIC -shared -O3 -march=native -Dechodsp=guitarix_echo ./ladspa/echo.cpp -o gecho.so
	$(CXX) -fPIC -shared -O3 -march=native -Dfrdsp=guitarix_freeverb ./ladspa/freeverb.cpp -o gfreeverb.so
	$(CXX) -fPIC -shared -O3 -march=native -Dirdsp=guitarix_IR ./ladspa/impulseresponse.cpp -o gIR.so
	$(CXX) -fPIC -shared -O3 -march=native -Dampdsp=guitarix_amp ./ladspa/monoamp.cpp -o gmonoamp.so
	$(CXX) -fPIC -shared -O3 -march=native -Dcomprdsp=guitarix_compressor ./ladspa/monocompressor.cpp -o gmonocompressor.so


	$(CXX) -O3  -march=native -Werror `pkg-config --cflags --libs jack gtk+-2.0 sndfile` ./src/main.cpp -o guitarix


install:
	mkdir -p $(DESTDIR)$(LADSPAPATH)
	install $(targets-ladspa) $(DESTDIR)$(LADSPAPATH)
	install -m755 guitarix $(DESTDIR)$(PREFIX)/bin
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
	install ./rcstyles/controls4.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	install ./rcstyles/controlsbl.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	install ./rcstyles/controlsbl1.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	install ./rcstyles/controlsbl2.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	install ./rcstyles/controlsbl3.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	install ./rcstyles/controlsbl4.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	install ./rcstyles/guitarix-darkblack-relief.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	install ./rcstyles/guitarix.rc $(DESTDIR)$(PREFIX)/share/guitarix
	install ./rcstyles/guitarix_pix.rc $(DESTDIR)$(PREFIX)/share/guitarix
	install ./rcstyles/guitarix_black.rc $(DESTDIR)$(PREFIX)/share/guitarix
	mkdir -p $(DESTDIR)$(PREFIX)/share/ladspa/rdf
	install ./ladspa/guitarix.rdf $(DESTDIR)$(PREFIX)/share/ladspa/rdf

clean  :
	rm -rf guitarix
	rm -rf *.so
	rm -rf *-stamp
	rm -rf *~
	rm -rf ./src/*~
	rm -rf ./ladspa/*~
	rm -rf ./src/guitarix/*~
	rm -rf ./debian/guitarix
	rm -rf ./debian/*.log
	rm -rf ./debian/*.substvars
uninstall :
	rm -rf $(PREFIX)/bin/guitarix $(LADSPAPATH)/guitarix.so $(LADSPAPATH)/gcrybaby.so $(LADSPAPATH)/gdistortion.so $(LADSPAPATH)/gfreeverb.so  $(LADSPAPATH)/gmonoamp.so $(LADSPAPATH)/monocompressor.so $(PREFIX)/share/applications/guitarix.desktop $(PREFIX)/share/pixmaps/guitarix.png $(PREFIX)/share/guitarix/guitarix.rc  $(PREFIX)/share/guitarix/controls.jpg  $(PREFIX)/share/guitarix/controls1.jpg $(PREFIX)/share/guitarix/controls2.jpg  $(PREFIX)/share/guitarix/controlsbl.jpg  $(PREFIX)/share/guitarix/controlsbl1.jpg $(PREFIX)/share/guitarix/controlsbl2.jpg $(PREFIX)/share/guitarix/controls3.jpg $(PREFIX)/share/guitarix/guitarix_pix.rc $(PREFIX)/share/pixmaps/guitarix-midi.png $(PREFIX)/share/pixmaps/guitarix-warn.png $(PREFIX)/share/guitarix/controlsbl3.jpg $(PREFIX)/share/guitarix/controlsbl4.jpg $(PREFIX)/share/guitarix/controlsbl3.jpg $(PREFIX)/share/guitarix/controlsbl4.jpg $(PREFIX)/share/guitarix/guitarix-darkblack-relief.jpg

