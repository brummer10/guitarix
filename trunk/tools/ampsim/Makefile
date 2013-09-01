CXXFLAGS=-O2
#CXXFLAGS=-g
INTPP_OPT=-msse2 -mfpmath=sse -ffast-math -funsafe-math-optimizations

.PHONY: clean all profopt tensbs

#all: tensbs # test client pyamp.so
all: data.cc

clean:
	rm -f client.o client intpp.o intpp.gcda amp.o test.o test data.cc pyamp.so pyamp.cpp
	rm -rf build

pyamp.so: pyamp.pyx intpp.o amp.o data.o
	@rm -f pyamp.so
	python setup.py build_ext --inplace

RESAMP_D = ~/guitarix/trunk/src/zita-resampler
RESAMP = $(RESAMP_D)/zita-resampler
client: client.o intpp.o amp.o data.o $(RESAMP).o
	$(LINK.cc) $^ -ljack -o $@

client.o: client.cc
	$(COMPILE.cc) $(CXXFLAGS) -I $(RESAMP_D) $< -o $@

test: test.o intpp.o amp.o data.o
	$(LINK.cc) $^ -lrt -o $@

intpp.o: intpp.cc intpp.h Makefile intpp.gcda
	$(COMPILE.cc) $(CXXFLAGS) $(INTPP_OPT) -fprofile-use $< -o $@

intpp.gcda: test_
	./test_
	@mv intpp_.gcda intpp.gcda

test_: test.o intpp_.o amp.o data.o
	$(LINK.cc) -fprofile-arcs $^ -lrt -o $@

intpp_.o: intpp.cc intpp.h Makefile
	$(COMPILE.cc) $(CXXFLAGS) $(INTPP_OPT) -fprofile-arcs $< -o $@

amp.o: amp.h

data.cc: gentables.py data.h circuit/pycircuit.so tensbs/tensbs.so
	python $< >$@

circuit/pycircuit.so: circuit/circuit.cc circuit/circuit.hpp circuit/pycircuit.pyx circuit/setup.py
	cd circuit && rm -f pycircuit.so && python setup.py build_ext --inplace && rm pycircuit.cpp

tensbs/tensbs.so:
	cd tensbs && make
