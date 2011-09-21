// generated from file '../src/faust/crybaby.dsp' by dsp2cc:
namespace crybaby {
static FAUSTFLOAT 	fslider0;
static double 	fConst0;
static double 	fConst1;
static double 	fRec1[2];
static double 	fRec2[2];
static double 	fRec3[2];
static FAUSTFLOAT 	fslider1;
static FAUSTFLOAT 	fslider2;
static double 	fRec0[3];
static int	fSamplingFreq;

static void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (1413.7166941154069 / fSamplingFreq);
	fConst1 = (2827.4333882308138 / fSamplingFreq);
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = pow(2.0,(2.3 * fSlow0));
	double 	fSlow2 = (1 - (fConst0 * (fSlow1 / pow(2.0,(1.0 + (2.0 * (1.0 - fSlow0)))))));
	double 	fSlow3 = (0.0010000000000000009 * (0 - (2.0 * (cos((fConst1 * fSlow1)) * fSlow2))));
	double 	fSlow4 = (0.0010000000000000009 * faustpower<2>(fSlow2));
	double 	fSlow5 = (0.0001000000000000001 * pow(4.0,fSlow0));
	double 	fSlow6 = fslider2;
	double 	fSlow7 = (0.01 * (fSlow6 * fslider1));
	double 	fSlow8 = (1 - (0.01 * fSlow6));
	for (int i=0; i<count; i++) {
		fRec1[0] = (fSlow3 + (0.999 * fRec1[1]));
		fRec2[0] = (fSlow4 + (0.999 * fRec2[1]));
		fRec3[0] = (fSlow5 + (0.999 * fRec3[1]));
		double fTemp0 = (double)input0[i];
		fRec0[0] = ((fSlow7 * (fTemp0 * fRec3[0])) - (0.996 * ((fRec2[0] * fRec0[2]) + (fRec1[0] * fRec0[1]))));
		output0[i] = (FAUSTFLOAT)((fRec0[0] + (fSlow8 * fTemp0)) - (0.996 * fRec0[1]));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("crybaby.wet_dry","wet/dry","S","",&fslider2, 1e+02, 0.0, 1e+02, 1.0);
	registerVar("crybaby.level","","S","",&fslider1, 0.1, 0.0, 1.0, 0.01);
	registerVar("crybaby.wah","","S","",&fslider0, 0.0, 0.0, 1.0, 0.01);
	registerInit("crybaby", init);
}

} // end namespace crybaby
