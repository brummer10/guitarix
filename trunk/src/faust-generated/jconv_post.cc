// generated from file '../src/faust/jconv_post.dsp' by dsp2cc:
namespace jconv_post {
static FAUSTFLOAT 	fslider0;
static int 	IOTA;
static double 	fVec0[65536];
static FAUSTFLOAT 	fslider1;
static double 	fConst0;
static double 	fRec0[2];
static FAUSTFLOAT 	fslider2;
static double 	fRec1[2];
static FAUSTFLOAT 	fslider3;
static double 	fRec2[2];
static FAUSTFLOAT&	fslider4 = get_alias("amp.balance");
static double 	fRec3[2];
static double 	fVec1[65536];
static int	fSamplingFreq;

static void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	for (int i=0; i<65536; i++) fVec0[i] = 0;
	fConst0 = (1.000000000000001e-06 * fSamplingFreq);
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<65536; i++) fVec1[i] = 0;
}

void compute(int count, float *input0, float *input1, float *input2, float *input3, float *output0, float *output1)
{
	double 	fSlow0 = (0.01 * fslider0);
	double 	fSlow1 = (1 - fSlow0);
	double 	fSlow2 = (fConst0 * fslider1);
	double 	fSlow3 = (0.0010000000000000009 * fslider2);
	double 	fSlow4 = (0.0010000000000000009 * pow(10,(0.05 * fslider3)));
	double 	fSlow5 = (0.0010000000000000009 * fslider4);
	for (int i=0; i<count; i++) {
		double fTemp0 = (fSlow0 * (double)input2[i]);
		fVec0[IOTA&65535] = fTemp0;
		fRec0[0] = (fSlow2 + (0.999 * fRec0[1]));
		double fTemp1 = ((int((fRec0[0] < 0)))?0:fRec0[0]);
		int iTemp2 = int(fTemp1);
		int iTemp3 = (1 + iTemp2);
		fRec1[0] = (fSlow3 + (0.999 * fRec1[1]));
		fRec2[0] = (fSlow4 + (0.999 * fRec2[1]));
		fRec3[0] = (fSlow5 + (0.999 * fRec3[1]));
		output0[i] = (FAUSTFLOAT)((1 - max(0, fRec3[0])) * (((fRec2[0] * (1 - max(0, fRec1[0]))) * (((fTemp1 - iTemp2) * fVec0[(IOTA-int((int(iTemp3) & 65535)))&65535]) + ((iTemp3 - fTemp1) * fVec0[(IOTA-int((iTemp2 & 65535)))&65535]))) + (fSlow1 * (double)input0[i])));
		double fTemp4 = (fSlow0 * (double)input3[i]);
		fVec1[IOTA&65535] = fTemp4;
		double fTemp5 = ((int((fRec0[0] > 0)))?0:(0 - fRec0[0]));
		int iTemp6 = int(fTemp5);
		int iTemp7 = (1 + iTemp6);
		output1[i] = (FAUSTFLOAT)((1 - max(0, (0 - fRec3[0]))) * (((fRec2[0] * (1 - max(0, (0 - fRec1[0])))) * (((fTemp5 - iTemp6) * fVec1[(IOTA-int((int(iTemp7) & 65535)))&65535]) + ((iTemp7 - fTemp5) * fVec1[(IOTA-int((iTemp6 & 65535)))&65535]))) + (fSlow1 * (double)input1[i])));
		// post processing
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("jconv.gain","Gain","S","gain trim for processed signal (unit: dB)",&fslider3, 0.0, -2e+01, 2e+01, 0.1);
	registerVar("jconv.balance","Balance","S","left/right trim for processed signal",&fslider2, 0.0, -1.0, 1.0, 0.1);
	registerVar("jconv.diff_delay","Delta Delay","S","delay left or right channel by the specified amount (unit: ms)",&fslider1, 0.0, -1e+02, 1e+02, 0.01);
	registerVar("jconv.wet_dry","wet/dry","S","percentage of processed signal in output signal",&fslider0, 1e+02, 0.0, 1e+02, 1.0);
	registerInit("jconv", init);
}

} // end namespace jconv_post
