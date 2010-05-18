namespace delay {
// generated from file '../src/faust/delay.dsp'

int 	IOTA;
double 	fVec0[2097152];
FAUSTFLOAT 	fslider0;
double 	fConst0;
FAUSTFLOAT 	fslider1;
double 	fRec0[2];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	for (int i=0; i<2097152; i++) fVec0[i] = 0;
	fConst0 = (0.001 * fSamplingFreq);
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (fConst0 * fslider0);
	int 	iSlow1 = int(fSlow0);
	int 	iSlow2 = int((iSlow1 & 2097151));
	int 	iSlow3 = (1 + iSlow1);
	double 	fSlow4 = (iSlow3 - fSlow0);
	int 	iSlow5 = int((int(iSlow3) & 2097151));
	double 	fSlow6 = (fSlow0 - iSlow1);
	double 	fSlow7 = (0.0010000000000000009 * pow(10,(0.05 * fslider1)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[IOTA&2097151] = fTemp0;
		fRec0[0] = (fSlow7 + (0.999 * fRec0[1]));
		output0[i] = (FAUSTFLOAT)(fVec0[IOTA&2097151] + (fRec0[0] * ((fSlow6 * fVec0[(IOTA-iSlow5)&2097151]) + (fSlow4 * fVec0[(IOTA-iSlow2)&2097151]))));
		// post processing
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("delay.gain","","S","",&fslider1, 0.0, -2e+01, 2e+01, 0.1);
	registerVar("delay.delay","","S","",&fslider0, 0.0, 0.0, 5e+03, 1e+01);
	registerInit(init);
}

} // end namespace delay
