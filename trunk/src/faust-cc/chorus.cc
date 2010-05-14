namespace chorus {
// generated from file '../src/faust/chorus.dsp'

class SIG0 {
  private:
	int 	fSamplingFreq;
	int 	iRec1[2];
  public:
	int getNumInputs() 	{ return 0; }
	int getNumOutputs() 	{ return 1; }
	void init(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		for (int i=0; i<2; i++) iRec1[i] = 0;
	}
	void fill (int count, double output[]) {
		for (int i=0; i<count; i++) {
			iRec1[0] = (1 + iRec1[1]);
			output[i] = sin((9.587379924285257e-05 * (iRec1[0] - 1)));
			// post processing
			iRec1[1] = iRec1[0];
		}
	}
};
int 	IOTA;
double 	fVec0[65536];
FAUSTFLOAT 	fslider0;
double 	fConst0;
double 	fRec0[2];
static double 	ftbl0[65536];
FAUSTFLOAT 	fslider1;
FAUSTFLOAT 	fslider2;
double 	fConst1;
FAUSTFLOAT 	fslider3;
double 	fVec1[65536];
int	fSamplingFreq;

void init(int samplingFreq)
{
	SIG0 sig0;
	sig0.init(samplingFreq);
	sig0.fill(65536,ftbl0);
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	for (int i=0; i<65536; i++) fVec0[i] = 0;
	fConst0 = (1.0 / fSamplingFreq);
	for (int i=0; i<2; i++) fRec0[i] = 0;
	fConst1 = (0.5 * fSamplingFreq);
	for (int i=0; i<65536; i++) fVec1[i] = 0;
}

void compute(int count, float *input0, float *input1, float *output0, float *output1)
{
	double 	fSlow0 = (fConst0 * fslider0);
	double 	fSlow1 = fslider1;
	double 	fSlow2 = (fConst1 * fslider2);
	double 	fSlow3 = fslider3;
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[IOTA&65535] = fTemp0;
		double fTemp1 = (fSlow0 + fRec0[1]);
		fRec0[0] = (fTemp1 - floor(fTemp1));
		double fTemp2 = (65536 * (fRec0[0] - floor(fRec0[0])));
		double fTemp3 = floor(fTemp2);
		int iTemp4 = int(fTemp3);
		double fTemp5 = (fSlow2 * (1 + (fSlow1 * ((ftbl0[((1 + iTemp4) & 65535)] * (fTemp2 - fTemp3)) + (ftbl0[(iTemp4 & 65535)] * ((1 + fTemp3) - fTemp2))))));
		int iTemp6 = int(fTemp5);
		int iTemp7 = (1 + iTemp6);
		output0[i] = (FAUSTFLOAT)(fVec0[IOTA&65535] + (fSlow3 * (((fTemp5 - iTemp6) * fVec0[(IOTA-int((int(iTemp7) & 65535)))&65535]) + ((iTemp7 - fTemp5) * fVec0[(IOTA-int((iTemp6 & 65535)))&65535]))));
		double fTemp8 = (double)input1[i];
		fVec1[IOTA&65535] = fTemp8;
		double fTemp9 = (0.25 + fRec0[0]);
		double fTemp10 = (65536 * (fTemp9 - floor(fTemp9)));
		double fTemp11 = floor(fTemp10);
		int iTemp12 = int(fTemp11);
		double fTemp13 = (fSlow2 * (1 + (fSlow1 * ((ftbl0[((1 + iTemp12) & 65535)] * (fTemp10 - fTemp11)) + (ftbl0[(iTemp12 & 65535)] * ((1 + fTemp11) - fTemp10))))));
		int iTemp14 = int(fTemp13);
		int iTemp15 = (1 + iTemp14);
		output1[i] = (FAUSTFLOAT)(fVec1[IOTA&65535] + (fSlow3 * (((fTemp13 - iTemp14) * fVec1[(IOTA-int((int(iTemp15) & 65535)))&65535]) + ((iTemp15 - fTemp13) * fVec1[(IOTA-int((iTemp14 & 65535)))&65535]))));
		// post processing
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("chorus.level","","S","",&fslider3, 0.5, 0.0, 1.0, 0.01);
	registerVar("chorus.delay","","S","",&fslider2, 0.025, 0.0, 0.2, 0.001);
	registerVar("chorus.depth","","S","",&fslider1, 0.02, 0.0, 1.0, 0.001);
	registerVar("chorus.freq","","S","",&fslider0, 3.0, 0.0, 1e+01, 0.01);
	registerInit(init);
}

} // end namespace chorus
