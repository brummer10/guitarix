namespace flanger_mono {
// generated from file '../src/faust/flanger_mono.dsp'

FAUSTFLOAT 	fslider0;
int 	iVec0[2];
int 	IOTA;
double 	fVec1[2048];
FAUSTFLOAT 	fslider1;
double 	fConst0;
double 	fRec1[2];
double 	fRec2[2];
double 	fRec0[2];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) iVec0[i] = 0;
	IOTA = 0;
	for (int i=0; i<2048; i++) fVec1[i] = 0;
	fConst0 = (6.283185307179586 / fSamplingFreq);
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = pow(10,(0.05 * fslider0));
	double 	fSlow1 = (fConst0 * fslider1);
	double 	fSlow2 = sin(fSlow1);
	double 	fSlow3 = cos(fSlow1);
	double 	fSlow4 = (0 - fSlow2);
	for (int i=0; i<count; i++) {
		double fTemp0 = (fSlow0 * (double)input0[i]);
		iVec0[0] = 1;
		double fTemp1 = ((0.5 * fRec0[1]) - fTemp0);
		fVec1[IOTA&2047] = fTemp1;
		fRec1[0] = ((fSlow3 * fRec1[1]) + (fSlow2 * fRec2[1]));
		fRec2[0] = ((1 + ((fSlow4 * fRec1[1]) + (fSlow3 * fRec2[1]))) - iVec0[1]);
		double fTemp2 = (fSamplingFreq * (0.001 + (0.005 * (1 + fRec1[0]))));
		int iTemp3 = int(fTemp2);
		int iTemp4 = (1 + iTemp3);
		fRec0[0] = (((fTemp2 - iTemp3) * fVec1[(IOTA-int((int(iTemp4) & 2047)))&2047]) + ((iTemp4 - fTemp2) * fVec1[(IOTA-int((iTemp3 & 2047)))&2047]));
		output0[i] = (FAUSTFLOAT)(0.5 * (fTemp0 - fRec0[0]));
		// post processing
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		IOTA = IOTA+1;
		iVec0[1] = iVec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("flanger_mono.freq","","S","",&fslider1, 0.2, 0.0, 5.0, 0.01);
	registerVar("flanger_mono.level","","S","",&fslider0, 0.0, -6e+01, 1e+01, 0.1);
	registerInit("flanger_mono", init);
}

} // end namespace flanger_mono
