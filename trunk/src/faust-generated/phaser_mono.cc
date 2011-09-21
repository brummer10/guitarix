// generated from file '../src/faust/phaser_mono.dsp' by dsp2cc:
namespace phaser_mono {
static FAUSTFLOAT 	fslider0;
static int 	iVec0[2];
static int 	iConst0;
static FAUSTFLOAT 	fslider1;
static double 	fConst1;
static double 	fRec1[2];
static double 	fRec2[2];
static double 	fConst2;
static FAUSTFLOAT 	fslider2;
static double 	fConst3;
static double 	fConst4;
static double 	fConst5;
static double 	fConst6;
static double 	fRec6[3];
static double 	fConst7;
static double 	fRec5[3];
static double 	fConst8;
static double 	fRec4[3];
static double 	fRec3[3];
static double 	fRec0[2];
static int	fSamplingFreq;

static void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) iVec0[i] = 0;
	iConst0 = ((1)?-1:1);
	fConst1 = (6.283185307179586 / fSamplingFreq);
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	fConst2 = (16.0 / fSamplingFreq);
	fConst3 = (2.0 / fSamplingFreq);
	fConst4 = exp((0 - (3141.592653589793 / fSamplingFreq)));
	fConst5 = (0 - (2 * fConst4));
	fConst6 = faustpower<2>(fConst4);
	for (int i=0; i<3; i++) fRec6[i] = 0;
	fConst7 = (4.0 / fSamplingFreq);
	for (int i=0; i<3; i++) fRec5[i] = 0;
	fConst8 = (8.0 / fSamplingFreq);
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (1 - (0.01 * fSlow0));
	double 	fSlow2 = (fConst1 * fslider1);
	double 	fSlow3 = sin(fSlow2);
	double 	fSlow4 = cos(fSlow2);
	double 	fSlow5 = (0 - fSlow3);
	double 	fSlow6 = (0.01 * (fSlow0 * pow(10,(0.05 * fslider2))));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		iVec0[0] = 1;
		fRec1[0] = ((fSlow4 * fRec1[1]) + (fSlow3 * fRec2[1]));
		fRec2[0] = ((1 + ((fSlow5 * fRec1[1]) + (fSlow4 * fRec2[1]))) - iVec0[1]);
		double fTemp1 = (628.3185307179587 + (2199.1148575128555 * (1 - fRec1[0])));
		double fTemp2 = (fRec6[1] * cos((fConst3 * fTemp1)));
		fRec6[0] = (0 - (((fConst6 * fRec6[2]) + (fConst5 * fTemp2)) - ((fSlow6 * fTemp0) + (0.5 * fRec0[1]))));
		double fTemp3 = (fRec5[1] * cos((fConst7 * fTemp1)));
		fRec5[0] = ((fConst5 * (fTemp2 - fTemp3)) + (fRec6[2] + (fConst6 * (fRec6[0] - fRec5[2]))));
		double fTemp4 = (fRec4[1] * cos((fConst8 * fTemp1)));
		fRec4[0] = ((fConst5 * (fTemp3 - fTemp4)) + (fRec5[2] + (fConst6 * (fRec5[0] - fRec4[2]))));
		double fTemp5 = (fRec3[1] * cos((fConst2 * fTemp1)));
		fRec3[0] = ((fConst5 * (fTemp4 - fTemp5)) + (fRec4[2] + (fConst6 * (fRec4[0] - fRec3[2]))));
		fRec0[0] = ((fConst6 * fRec3[0]) + (fRec3[2] + (fConst5 * fTemp5)));
		output0[i] = (FAUSTFLOAT)((fRec0[0] * iConst0) + (fSlow1 * fTemp0));
		// post processing
		fRec0[1] = fRec0[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		iVec0[1] = iVec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("phaser_mono.level","","S","",&fslider2, 0.0, -6e+01, 1e+01, 0.1);
	registerVar("phaser_mono.Speed","","S","",&fslider1, 0.5, 0.0, 1e+01, 0.01);
	registerVar("phaser_mono.wet_dry","wet/dry","S","percentage of processed signal in output signal",&fslider0, 1e+02, 0.0, 1e+02, 1.0);
	registerInit("phaser_mono", init);
}

} // end namespace phaser_mono
