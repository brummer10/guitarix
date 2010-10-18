namespace phaser {
// generated from file '../src/faust/phaser.dsp'

FAUSTFLOAT 	fslider0;
double 	fVec0[6];
int 	iVec1[2];
FAUSTFLOAT 	fslider1;
int 	IOTA;
double 	fVec2[2048];
FAUSTFLOAT 	fslider2;
double 	fConst0;
double 	fRec1[2];
double 	fRec2[2];
FAUSTFLOAT 	fslider3;
FAUSTFLOAT 	fslider4;
double 	fRec0[2];
FAUSTFLOAT 	fslider5;
FAUSTFLOAT 	fcheckbox0;
double 	fVec3[6];
double 	fVec4[2048];
double 	fRec3[2];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<6; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) iVec1[i] = 0;
	IOTA = 0;
	for (int i=0; i<2048; i++) fVec2[i] = 0;
	fConst0 = (6.283185307179586 / fSamplingFreq);
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<6; i++) fVec3[i] = 0;
	for (int i=0; i<2048; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
}

void compute(int count, float *input0, float *input1, float *output0, float *output1)
{
	double 	fSlow0 = pow(10,(0.05 * fslider0));
	double 	fSlow1 = fslider1;
	double 	fSlow2 = (fConst0 * fslider2);
	double 	fSlow3 = sin(fSlow2);
	double 	fSlow4 = cos(fSlow2);
	double 	fSlow5 = (0 - fSlow3);
	double 	fSlow6 = (0.0005 * fslider3);
	double 	fSlow7 = (0.001 * fslider4);
	double 	fSlow8 = fslider5;
	double 	fSlow9 = ((int(fcheckbox0))?(0 - fSlow8):fSlow8);
	for (int i=0; i<count; i++) {
		double fTemp0 = (fSlow0 * (double)input0[i]);
		fVec0[0] = fTemp0;
		iVec1[0] = 1;
		double fTemp1 = ((fSlow1 * fRec0[1]) - fVec0[5]);
		fVec2[IOTA&2047] = fTemp1;
		fRec1[0] = ((fSlow4 * fRec1[1]) + (fSlow3 * fRec2[1]));
		fRec2[0] = ((1 + ((fSlow5 * fRec1[1]) + (fSlow4 * fRec2[1]))) - iVec1[1]);
		double fTemp2 = (fSamplingFreq * (fSlow7 + (fSlow6 * (1 + fRec1[0]))));
		int iTemp3 = int(fTemp2);
		int iTemp4 = (1 + iTemp3);
		fRec0[0] = (((fTemp2 - iTemp3) * fVec2[(IOTA-int((int(iTemp4) & 2047)))&2047]) + ((iTemp4 - fTemp2) * fVec2[(IOTA-int((iTemp3 & 2047)))&2047]));
		output0[i] = (FAUSTFLOAT)(0.5 * (fVec0[0] + (fSlow9 * fRec0[0])));
		double fTemp5 = (fSlow0 * (double)input1[i]);
		fVec3[0] = fTemp5;
		double fTemp6 = ((fSlow1 * fRec3[1]) - fVec3[5]);
		fVec4[IOTA&2047] = fTemp6;
		double fTemp7 = (fSamplingFreq * (fSlow7 + (fSlow6 * (1 + fRec2[0]))));
		int iTemp8 = int(fTemp7);
		int iTemp9 = (1 + iTemp8);
		fRec3[0] = (((fTemp7 - iTemp8) * fVec4[(IOTA-int((int(iTemp9) & 2047)))&2047]) + ((iTemp9 - fTemp7) * fVec4[(IOTA-int((iTemp8 & 2047)))&2047]));
		output1[i] = (FAUSTFLOAT)(0.5 * (fVec3[0] + (fSlow9 * fRec3[0])));
		// post processing
		fRec3[1] = fRec3[0];
		for (int i=5; i>0; i--) fVec3[i] = fVec3[i-1];
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		IOTA = IOTA+1;
		iVec1[1] = iVec1[0];
		for (int i=5; i>0; i--) fVec0[i] = fVec0[i-1];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	static const char *fcheckbox0_values[] = {"linear","invert",0};
	registerEnumVar("phaser.invert","","B","",fcheckbox0_values,&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	registerVar("phaser.depth","","S","",&fslider5, 1.0, 0.0, 1.0, 0.01);
	registerVar("phaser.delay offset","","S","",&fslider4, 1.0, 0.0, 2e+01, 0.01);
	registerVar("phaser.delay","","S","",&fslider3, 1e+01, 0.0, 2e+01, 0.01);
	registerVar("phaser.LFO freq","","S","",&fslider2, 0.2, 0.0, 5.0, 0.01);
	registerVar("phaser.feedback gain","","S","",&fslider1, 0.0, 0.0, 1.0, 0.01);
	registerVar("phaser.level","","S","",&fslider0, 0.0, -6e+01, 1e+01, 0.1);
	registerInit("phaser", init);
}

} // end namespace phaser
