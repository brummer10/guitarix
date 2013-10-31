CXXFLAGS=-O2 -fPIC -fvisibility=hidden
#CXXFLAGS=-g
INTPP_OPT=-msse2 -mfpmath=sse -ffast-math
LDFLAGS=-fPIC

DSP2CC = ../dsp2cc
GXHEAD = ../../src/headers

.PHONY: clean all

all: pyamp.so gxplugins.so

clean:
	rm -f gxplugins.so gxplugins_.so data.o intpp.o intpp_.o intpp.gcda intpp_.gcda
	rm -f gx_poweramp.o gxpoweramp.cc gxpreamp.cc data.cc intpp_inst.cc data.h
	rm -f pyamp.so pyamp.cpp
	rm -f circuit/components.pyc circuit/__init__.pyc circuit/pycircuit.so
	rm -rf circuit/build
	make -C tensbs clean

install: gxplugins.so
	cp gxplugins.so $(HOME)/.config/guitarix/plugins

gxplugins.so: gx_poweramp.o intpp.o data.o
	$(LINK.cc) -shared -Wl,-soname,gxplugins.so -o gxplugins.so $^ -lzita-resampler

gx_poweramp.o: gx_poweramp.cpp gxpoweramp.cc gxpreamp.cc data.cc intpp.h
	$(COMPILE.cc) $(CXXFLAGS) `pkg-config --cflags glibmm-2.4` -I$(GXHEAD) $< -o $@

gxpoweramp.cc: gxpoweramp.dsp gxpreamp.dsp $(DSP2CC)
	$(DSP2CC) -i plugin gxpoweramp.dsp > $@

gxpreamp.cc: gxpreamp.dsp $(DSP2CC)
	$(DSP2CC) -i plugin gxpreamp.dsp > $@

intpp.o: intpp.cc data.cc intpp.h Makefile intpp.gcda
	$(COMPILE.cc) $(CXXFLAGS) $(INTPP_OPT) -fprofile-use $< -o $@
#	$(COMPILE.cc) $(CXXFLAGS) $(INTPP_OPT) $< -o $@

intpp.gcda: gxplugins_.so exercise.py
	python exercise.py
	@mv intpp_.gcda intpp.gcda

intpp_.o: intpp.cc intpp.h intpp_inst.cc Makefile
	$(COMPILE.cc) $(CXXFLAGS) $(INTPP_OPT) -fprofile-arcs $< -o $@

gxplugins_.so: gx_poweramp.o intpp_.o data.o
	$(LINK.cc) -fprofile-arcs -shared -Wl,-soname,gxplugins_.so -o gxplugins_.so $^ -lzita-resampler

data.cc: gentables.py circuit/components.py circuit/pycircuit.so # tensbs/tensbs.so tensbs/splinetable.py
	python $< data.cc intpp_inst.cc data.h

circuit/pycircuit.so: circuit/circuit.cc circuit/circuit.hpp circuit/pycircuit.pyx circuit/setup.py
	cd circuit && rm -f pycircuit.so && python setup.py build_ext --inplace && rm pycircuit.cpp

tensbs/tensbs.so:
	cd tensbs && make

pyamp.so: pyamp.pyx intpp.o data.o
	@rm -f pyamp.so
	python setup.py build_ext --inplace
