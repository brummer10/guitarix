FILES=b1ink.f b2ink.f b2val.f b3ink.f b3val.f b4ink.f b4val.f
DEPFILES=btpcf.f bintk.f bknot.f bnslv.f xerrwv.f xerprt.f i1mach.f \
        xersav.f j4save.f fdump.f xgetua.f bvalu.f xerctl.f \
        xerror.f bspvn.f intrv.f bnfac.f xerabt.f
ONLY=b1ink b2ink b2val b3ink b3val b4ink b4val
OPTS=-DF2PY_REPORT_ON_ARRAY_COPY=1 --f77flags="-Wno-unused-parameter"

.PHONY: all clean

all: tensbs.so

clean:
	rm -f tensbs.so splinetable.pyc

tensbs.so: $(FILES) $(DEPFILES) tensbs.pyf
	f2py --quiet -c $(OPTS) -m tensbs only: $(ONLY) : tensbs.pyf $(FILES) $(DEPFILES)
