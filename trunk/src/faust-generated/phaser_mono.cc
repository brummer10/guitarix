namespace phaser_mono {
// generated from file '../src/faust/phaser_mono.dsp'

int 	iVec0[2];
int 	iConst0;
FAUSTFLOAT 	fslider0;
double 	fConst1;
double 	fRec1[2];
double 	fRec2[2];
double 	fConst2;
FAUSTFLOAT 	fslider1;
double 	fConst3;
double 	fConst4;
double 	fConst5;
double 	fConst6;
double 	fRec6[3];
double 	fConst7;
double 	fRec5[3];
double 	fConst8;
double 	fRec4[3];
double 	fRec3[3];
double 	fRec0[2];
int	fSamplingFreq;

void init(int samplingFreq)
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
	double 	fSlow0 = (fConst1 * fslider0);
	double 	fSlow1 = sin(fSlow0);
	double 	fSlow2 = cos(fSlow0);
	double 	fSlow3 = (0 - fSlow1);
	double 	fSlow4 = pow(10,(0.05 * fslider1));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec1[0] = ((fSlow2 * fRec1[1]) + (fSlow1 * fRec2[1]));
		fRec2[0] = ((1 + ((fSlow3 * fRec1[1]) + (fSlow2 * fRec2[1]))) - iVec0[1]);
		double fTemp0 = (628.3185307179587 + (2199.1148575128555 * (1 - fRec1[0])));
		double fTemp1 = (fRec6[1] * cos((fConst3 * fTemp0)));
		fRec6[0] = (0 - (((fConst6 * fRec6[2]) + (fConst5 * fTemp1)) - ((fSlow4 * (double)input0[i]) + (0.5 * fRec0[1]))));
		double fTemp2 = (fRec5[1] * cos((fConst7 * fTemp0)));
		fRec5[0] = ((fConst5 * (fTemp1 - fTemp2)) + (fRec6[2] + (fConst6 * (fRec6[0] - fRec5[2]))));
		double fTemp3 = (fRec4[1] * cos((fConst8 * fTemp0)));
		fRec4[0] = ((fConst5 * (fTemp2 - fTemp3)) + (fRec5[2] + (fConst6 * (fRec5[0] - fRec4[2]))));
		double fTemp4 = (fRec3[1] * cos((fConst2 * fTemp0)));
		fRec3[0] = ((fConst5 * (fTemp3 - fTemp4)) + (fRec4[2] + (fConst6 * (fRec4[0] - fRec3[2]))));
		fRec0[0] = ((fConst6 * fRec3[0]) + (fRec3[2] + (fConst5 * fTemp4)));
		output0[i] = (FAUSTFLOAT)(fRec0[0] * iConst0);
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
	registerVar("phaser_mono.level","","S","",&fslider1, 0.0, -6e+01, 1e+01, 0.1);
	registerVar("phaser_mono.Speed","","S","",&fslider0, 0.5, 0.0, 1e+01, 0.01);
	registerInit("phaser_mono", init);
}

} // end namespace phaser_mono
