## makefile for guitarix by @brummer

        ## set the install Path for guitarix
	PREFIX = /usr
	LADSPAPATH = $(PREFIX)/lib/ladspa
 	CXXFLAGS = -O3  -march=native -Wall 
 	CXXLADSPAFLAGS = -fPIC -shared $(CXXFLAGS)
 	INSTALL = install -p
        CXX          = g++


targets-ladspa = gcrybaby.so gdistortion.so gecho.so gfreeverb.so gIR.so gmonoamp.so gmonocompressor.so guitarix.so


all    :
	$(CXX) $(CXXLADSPAFLAGS) -Dmydsp=guitarix ./ladspa/guitarix-ladspa.cpp -o guitarix.so

	$(CXX) $(CXXLADSPAFLAGS) -Dcrydsp=guitarix_crybaby ./ladspa/crybaby.cpp -o gcrybaby.so
	$(CXX) $(CXXLADSPAFLAGS) -Ddistdsp=guitarix_distortion ./ladspa/distortion.cpp -o gdistortion.so
	$(CXX) $(CXXLADSPAFLAGS) -Dechodsp=guitarix_echo ./ladspa/echo.cpp -o gecho.so
	$(CXX) $(CXXLADSPAFLAGS) -Dfrdsp=guitarix_freeverb ./ladspa/freeverb.cpp -o gfreeverb.so
	$(CXX) $(CXXLADSPAFLAGS) -Dirdsp=guitarix_IR ./ladspa/impulseresponse.cpp -o gIR.so
	$(CXX) $(CXXLADSPAFLAGS) -Dampdsp=guitarix_amp ./ladspa/monoamp.cpp -o gmonoamp.so
	$(CXX) $(CXXLADSPAFLAGS) -Dcomprdsp=guitarix_compressor ./ladspa/monocompressor.cpp -o gmonocompressor.so


	$(CXX) $(CXXFLAGS) `pkg-config --cflags --libs jack gtk+-2.0 sndfile` ./src/main.cpp -o guitarix


install:
	$(INSTALL) -d $(DESTDIR)$(LADSPAPATH)
	$(INSTALL) -m755 $(targets-ladspa) $(DESTDIR)$(LADSPAPATH)
	$(INSTALL) -d $(DESTDIR)$(PREFIX)/bin
	$(INSTALL) -m755 guitarix $(DESTDIR)$(PREFIX)/bin
	$(INSTALL) -d $(DESTDIR)$(PREFIX)/share/applications
	$(INSTALL) -m644 guitarix.desktop $(DESTDIR)$(PREFIX)/share/applications
	$(INSTALL) -d $(DESTDIR)$(PREFIX)/share/guitarix
	$(INSTALL) -d $(DESTDIR)$(PREFIX)/share/pixmaps
	$(INSTALL) -m644 ./guitarix.png $(DESTDIR)$(PREFIX)/share/pixmaps
	$(INSTALL) -m644 ./guitarix-midi.png $(DESTDIR)$(PREFIX)/share/pixmaps
	$(INSTALL) -m644 ./guitarix-warn.png $(DESTDIR)$(PREFIX)/share/pixmaps
	$(INSTALL) -m644 ./rcstyles/controls.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	$(INSTALL) -m644 ./rcstyles/controls1.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	$(INSTALL) -m644 ./rcstyles/controls2.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	$(INSTALL) -m644 ./rcstyles/controls3.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	$(INSTALL) -m644 ./rcstyles/controls4.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	$(INSTALL) -m644 ./rcstyles/controlsbl.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	$(INSTALL) -m644 ./rcstyles/controlsbl1.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	$(INSTALL) -m644 ./rcstyles/controlsbl2.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	$(INSTALL) -m644 ./rcstyles/controlsbl3.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	$(INSTALL) -m644 ./rcstyles/controlsbl4.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	$(INSTALL) -m644 ./rcstyles/guitarix-darkblack-relief.jpg $(DESTDIR)$(PREFIX)/share/guitarix
	$(INSTALL) -m644 ./rcstyles/guitarix.rc $(DESTDIR)$(PREFIX)/share/guitarix
	$(INSTALL) -m644 ./rcstyles/guitarix_pix.rc $(DESTDIR)$(PREFIX)/share/guitarix
	$(INSTALL) -m644 ./rcstyles/guitarix_black.rc $(DESTDIR)$(PREFIX)/share/guitarix
	$(INSTALL) -d $(DESTDIR)$(PREFIX)/share/ladspa/rdf
	$(INSTALL) -m644 ./ladspa/guitarix.rdf $(DESTDIR)$(PREFIX)/share/ladspa/rdf

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
	rm -rf $(PREFIX)/bin/guitarix $(LADSPAPATH)/guitarix.so $(LADSPAPATH)/gcrybaby.so $(LADSPAPATH)/gdistortion.so $(LADSPAPATH)/gfreeverb.so  $(LADSPAPATH)/gmonoamp.so $(LADSPAPATH)/monocompressor.so $(PREFIX)/share/applications/guitarix.desktop $(PREFIX)/share/pixmaps/guitarix.png $(PREFIX)/share/guitarix/guitarix.rc  $(PREFIX)/share/guitarix/controls.jpg  $(PREFIX)/share/guitarix/controls1.jpg $(PREFIX)/share/guitarix/controls2.jpg  $(PREFIX)/share/guitarix/controlsbl.jpg  $(PREFIX)/share/guitarix/controlsbl1.jpg $(PREFIX)/share/guitarix/controlsbl2.jpg $(PREFIX)/share/guitarix/controls3.jpg $(PREFIX)/share/guitarix/guitarix_pix.rc $(PREFIX)/share/pixmaps/guitarix-midi.png $(PREFIX)/share/pixmaps/guitarix-warn.png $(PREFIX)/share/guitarix/controlsbl3.jpg $(PREFIX)/share/guitarix/controlsbl4.jpg $(PREFIX)/share/guitarix/controlsbl3.jpg $(PREFIX)/share/guitarix/controlsbl4.jpg $(PREFIX)/share/guitarix/guitarix-darkblack-relief.jpg $(PREFIX)/share/ladspa/rdf/guitarix.rdf

