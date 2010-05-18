namespace echo {
// generated from file '../src/faust/echo.dsp'

FAUSTFLOAT 	fslider0;
double 	fConst0;
FAUSTFLOAT 	fslider1;
int 	IOTA;
double 	fRec0[262144];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (0.001 * fSamplingFreq);
	IOTA = 0;
	for (int i=0; i<262144; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	int 	iSlow0 = int((1 + int((int((int((fConst0 * fslider0)) - 1)) & 131071))));
	double 	fSlow1 = (0.01 * fslider1);
	for (int i=0; i<count; i++) {
		fRec0[IOTA&262143] = ((double)input0[i] + (fSlow1 * fRec0[(IOTA-iSlow0)&262143]));
		output0[i] = (FAUSTFLOAT)fRec0[(IOTA-0)&262143];
		// post processing
		IOTA = IOTA+1;
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("echo.percent","","S","",&fslider1, 0.0, 0.0, 1e+02, 0.1);
	registerVar("echo.time","","S","",&fslider0, 1.0, 1.0, 2e+03, 1.0);
	registerInit(init);
}

} // end namespace echo
