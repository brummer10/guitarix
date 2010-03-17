namespace echo {
// generated from file '../src/faust/echo.dsp'

FAUSTFLOAT 	fslider0;
float 	fConst0;
FAUSTFLOAT 	fslider1;
int 	IOTA;
float 	fRec0[262144];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (1.000000e-03f * fSamplingFreq);
	IOTA = 0;
	for (int i=0; i<262144; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	int 	iSlow0 = int((1 + int((int((int((fConst0 * fslider0)) - 1)) & 131071))));
	float 	fSlow1 = (1.000000e-02f * fslider1);
	for (int i=0; i<count; i++) {
		fRec0[IOTA&262143] = ((float)input0[i] + (fSlow1 * fRec0[(IOTA-iSlow0)&262143]));
		output0[i] = (FAUSTFLOAT)fRec0[(IOTA-0)&262143];
		// post processing
		IOTA = IOTA+1;
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("echo.percent","","S","",&fslider1, 0.0f, 0.0f, 100.0f, 0.1f);
	registerVar("echo.time","","S","",&fslider0, 1.0f, 1.0f, 2000.0f, 1.0f);
	registerInit(init);
}

} // end namespace echo
