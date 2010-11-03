namespace phaser {
// generated from file '../src/faust/phaser.dsp'

FAUSTFLOAT 	fslider0;
FAUSTFLOAT 	fcheckbox0;
int 	iVec0[2];
FAUSTFLOAT 	fslider1;
FAUSTFLOAT 	fcheckbox1;
FAUSTFLOAT 	fslider2;
double 	fConst0;
double 	fRec1[2];
double 	fRec2[2];
FAUSTFLOAT 	fslider3;
FAUSTFLOAT 	fslider4;
FAUSTFLOAT 	fslider5;
double 	fConst1;
FAUSTFLOAT 	fslider6;
FAUSTFLOAT 	fslider7;
double 	fRec6[3];
double 	fRec5[3];
double 	fRec4[3];
double 	fRec3[3];
double 	fRec0[2];
double 	fRec11[3];
double 	fRec10[3];
double 	fRec9[3];
double 	fRec8[3];
double 	fRec7[2];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) iVec0[i] = 0;
	fConst0 = (6.283185307179586 / fSamplingFreq);
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	fConst1 = (1.0 / fSamplingFreq);
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
}

void compute(int count, float *input0, float *input1, float *output0, float *output1)
{
	double 	fSlow0 = (0.5 * ((int(fcheckbox0))?2:fslider0));
	double 	fSlow1 = (1 - fSlow0);
	double 	fSlow2 = pow(10,(0.05 * fslider1));
	double 	fSlow3 = ((int(fcheckbox1))?(0 - fSlow0):fSlow0);
	double 	fSlow4 = (fConst0 * fslider2);
	double 	fSlow5 = sin(fSlow4);
	double 	fSlow6 = cos(fSlow4);
	double 	fSlow7 = (0 - fSlow5);
	double 	fSlow8 = fslider3;
	double 	fSlow9 = (6.283185307179586 * fSlow8);
	double 	fSlow10 = (0.5 * ((6.283185307179586 * max(fSlow8, fslider4)) - fSlow9));
	double 	fSlow11 = fslider5;
	double 	fSlow12 = (fConst1 * faustpower<4>(fSlow11));
	double 	fSlow13 = fslider6;
	double 	fSlow14 = (fConst1 * fSlow11);
	double 	fSlow15 = exp((fConst1 * (0 - (3.141592653589793 * fslider7))));
	double 	fSlow16 = (0 - (2 * fSlow15));
	double 	fSlow17 = faustpower<2>(fSlow15);
	double 	fSlow18 = (fConst1 * faustpower<2>(fSlow11));
	double 	fSlow19 = (fConst1 * faustpower<3>(fSlow11));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		double fTemp0 = (double)input0[i];
		fRec1[0] = ((fSlow6 * fRec1[1]) + (fSlow5 * fRec2[1]));
		fRec2[0] = ((1 + ((fSlow7 * fRec1[1]) + (fSlow6 * fRec2[1]))) - iVec0[1]);
		double fTemp1 = (fSlow9 + (fSlow10 * (1 - fRec1[0])));
		double fTemp2 = (fRec6[1] * cos((fSlow14 * fTemp1)));
		fRec6[0] = (0 - (((fSlow17 * fRec6[2]) + (fSlow16 * fTemp2)) - ((fSlow2 * fTemp0) + (fSlow13 * fRec0[1]))));
		double fTemp3 = (fRec5[1] * cos((fSlow18 * fTemp1)));
		fRec5[0] = ((fSlow16 * (fTemp2 - fTemp3)) + (fRec6[2] + (fSlow17 * (fRec6[0] - fRec5[2]))));
		double fTemp4 = (fRec4[1] * cos((fSlow19 * fTemp1)));
		fRec4[0] = ((fSlow16 * (fTemp3 - fTemp4)) + (fRec5[2] + (fSlow17 * (fRec5[0] - fRec4[2]))));
		double fTemp5 = (fRec3[1] * cos((fSlow12 * fTemp1)));
		fRec3[0] = ((fSlow16 * (fTemp4 - fTemp5)) + (fRec4[2] + (fSlow17 * (fRec4[0] - fRec3[2]))));
		fRec0[0] = ((fSlow17 * fRec3[0]) + (fRec3[2] + (fSlow16 * fTemp5)));
		output0[i] = (FAUSTFLOAT)((fRec0[0] * fSlow3) + (fSlow2 * (fTemp0 * fSlow1)));
		double fTemp6 = (double)input1[i];
		double fTemp7 = (fSlow9 + (fSlow10 * (1 - fRec2[0])));
		double fTemp8 = (fRec11[1] * cos((fSlow14 * fTemp7)));
		fRec11[0] = (0 - (((fSlow17 * fRec11[2]) + (fSlow16 * fTemp8)) - ((fSlow2 * fTemp6) + (fSlow13 * fRec7[1]))));
		double fTemp9 = (fRec10[1] * cos((fSlow18 * fTemp7)));
		fRec10[0] = ((fSlow16 * (fTemp8 - fTemp9)) + (fRec11[2] + (fSlow17 * (fRec11[0] - fRec10[2]))));
		double fTemp10 = (fRec9[1] * cos((fSlow19 * fTemp7)));
		fRec9[0] = ((fSlow16 * (fTemp9 - fTemp10)) + (fRec10[2] + (fSlow17 * (fRec10[0] - fRec9[2]))));
		double fTemp11 = (fRec8[1] * cos((fSlow12 * fTemp7)));
		fRec8[0] = ((fSlow16 * (fTemp10 - fTemp11)) + (fRec9[2] + (fSlow17 * (fRec9[0] - fRec8[2]))));
		fRec7[0] = ((fSlow17 * fRec8[0]) + (fRec8[2] + (fSlow16 * fTemp11)));
		output1[i] = (FAUSTFLOAT)((fRec7[0] * fSlow3) + (fSlow2 * (fTemp6 * fSlow1)));
		// post processing
		fRec7[1] = fRec7[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
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
	static const char *fcheckbox1_values[] = {"invert","linear",0};
	registerEnumVar("phaser.invert","","B","",fcheckbox1_values,&fcheckbox1, 0.0, 0.0, 1.0, 1.0);
	static const char *fcheckbox0_values[] = {"direct "," vibrato",0};
	registerEnumVar("phaser.VibratoMode","","B","",fcheckbox0_values,&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	registerVar("phaser.Notch width","","S","",&fslider7, 1e+03, 1e+01, 5e+03, 1.0);
	registerVar("phaser.feedback gain","","S","",&fslider6, 0.0, 0.0, 1.0, 0.01);
	registerVar("phaser.NotchFreq","","S","",&fslider5, 1.5, 1.1, 4.0, 0.01);
	registerVar("phaser.MaxNotch1Freq","","S","",&fslider4, 8e+02, 2e+01, 1e+04, 1.0);
	registerVar("phaser.MinNotch1Freq","","S","",&fslider3, 1e+02, 2e+01, 5e+03, 1.0);
	registerVar("phaser.Speed","","S","",&fslider2, 0.5, 0.0, 1e+01, 0.01);
	registerVar("phaser.level","","S","",&fslider1, 0.0, -6e+01, 1e+01, 0.1);
	registerVar("phaser.depth","","S","",&fslider0, 1.0, 0.0, 1.0, 0.01);
	registerInit("phaser", init);
}

} // end namespace phaser
