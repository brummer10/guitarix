namespace flanger_mono {
// generated from file '../src/faust/flanger_mono.dsp'

FAUSTFLOAT 	fslider0;
int 	iVec0[2];
FAUSTFLOAT 	fslider1;
int 	IOTA;
double 	fVec1[2048];
FAUSTFLOAT 	fslider2;
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
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (1 - (0.01 * fSlow0));
	double 	fSlow2 = (0.01 * (fSlow0 * pow(10,(0.05 * fslider1))));
	double 	fSlow3 = (fConst0 * fslider2);
	double 	fSlow4 = sin(fSlow3);
	double 	fSlow5 = cos(fSlow3);
	double 	fSlow6 = (0 - fSlow4);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		iVec0[0] = 1;
		double fTemp1 = (fSlow2 * fTemp0);
		double fTemp2 = ((0.5 * fRec0[1]) - fTemp1);
		fVec1[IOTA&2047] = fTemp2;
		fRec1[0] = ((fSlow5 * fRec1[1]) + (fSlow4 * fRec2[1]));
		fRec2[0] = ((1 + ((fSlow6 * fRec1[1]) + (fSlow5 * fRec2[1]))) - iVec0[1]);
		double fTemp3 = (fSamplingFreq * (0.001 + (0.005 * (1 + fRec1[0]))));
		int iTemp4 = int(fTemp3);
		int iTemp5 = (1 + iTemp4);
		fRec0[0] = (((fTemp3 - iTemp4) * fVec1[(IOTA-int((int(iTemp5) & 2047)))&2047]) + ((iTemp5 - fTemp3) * fVec1[(IOTA-int((iTemp4 & 2047)))&2047]));
		output0[i] = (FAUSTFLOAT)((0.5 * (fTemp1 - fRec0[0])) + (fSlow1 * fTemp0));
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
	registerVar("flanger_mono.freq","","S","",&fslider2, 0.2, 0.0, 5.0, 0.01);
	registerVar("flanger_mono.level","","S","",&fslider1, 0.0, -6e+01, 1e+01, 0.1);
	registerVar("flanger_mono.wet_dry","wet/dry","S","percentage of processed signal in output signal",&fslider0, 1e+02, 0.0, 1e+02, 1.0);
	registerInit("flanger_mono", init);
}

} // end namespace flanger_mono
