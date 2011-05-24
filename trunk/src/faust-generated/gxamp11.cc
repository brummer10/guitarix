namespace gxamp11 {
// generated from file '../src/faust/gxamp11.dsp'

FAUSTFLOAT&	fslider0 = get_alias("amp2.stage2.gain1");
double 	fRec0[2];
double 	fConst0;
double 	fConst1;
double 	fConst2;
double 	fConst3;
double 	fConst4;
double 	fConst5;
double 	fVec0[2];
double 	fConst6;
double 	fRec3[2];
double 	fConst7;
double 	fConst8;
double 	fConst9;
FAUSTFLOAT&	fslider1 = get_alias("amp2.stage1.Pregain");
double 	fRec8[2];
FAUSTFLOAT&	fslider2 = get_alias("gxdistortion.drive");
double 	fConst10;
double 	fConst11;
double 	fConst12;
double 	fVec1[2];
double 	fConst13;
double 	fRec11[2];
double 	fRec10[2];
double 	fConst14;
double 	fConst15;
double 	fRec9[2];
double 	fVec2[2];
double 	fConst16;
double 	fRec7[2];
double 	fConst17;
double 	fConst18;
double 	fConst19;
double 	fVec3[2];
double 	fConst20;
double 	fRec12[2];
double 	fRec6[2];
double 	fRec5[2];
double 	fVec4[2];
double 	fRec4[2];
double 	fRec2[2];
double 	fRec1[2];
double 	fVec5[2];
double 	fRec15[2];
double 	fRec14[2];
double 	fRec13[2];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	fConst0 = (1.0 / tan((97.38937226128358 / fSamplingFreq)));
	fConst1 = (1 + fConst0);
	fConst2 = (0 - ((1 - fConst0) / fConst1));
	fConst3 = (1.0 / tan((609.4689747964198 / fSamplingFreq)));
	fConst4 = (1 + fConst3);
	fConst5 = (0 - ((1 - fConst3) / fConst4));
	for (int i=0; i<2; i++) fVec0[i] = 0;
	fConst6 = (0.0082 / fConst4);
	for (int i=0; i<2; i++) fRec3[i] = 0;
	fConst7 = (1.0 / tan((20517.741620594938 / fSamplingFreq)));
	fConst8 = (1 + fConst7);
	fConst9 = (0 - ((1 - fConst7) / fConst8));
	for (int i=0; i<2; i++) fRec8[i] = 0;
	fConst10 = (1.0 / tan((270.1769682087222 / fSamplingFreq)));
	fConst11 = (1 + fConst10);
	fConst12 = (0 - ((1 - fConst10) / fConst11));
	for (int i=0; i<2; i++) fVec1[i] = 0;
	fConst13 = (0.027 / fConst11);
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	fConst14 = (0 - fConst0);
	fConst15 = (0.05 / fConst1);
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	fConst16 = (1.0 / fConst8);
	for (int i=0; i<2; i++) fRec7[i] = 0;
	fConst17 = (1.0 / tan((414.6902302738527 / fSamplingFreq)));
	fConst18 = (1 + fConst17);
	fConst19 = (0 - ((1 - fConst17) / fConst18));
	for (int i=0; i<2; i++) fVec3[i] = 0;
	fConst20 = (0.015 / fConst18);
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.06 * fslider0)));
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.06 * fslider1)));
	double 	fSlow2 = (1.25 * fslider2);
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		double fTemp0 = (fRec2[1] - 1.3e+02);
		fVec0[0] = fTemp0;
		fRec3[0] = ((fConst6 * (fVec0[0] + fVec0[1])) + (fConst5 * fRec3[1]));
		fRec8[0] = (fSlow1 + (0.999 * fRec8[1]));
		double fTemp1 = (double)input0[i];
		double fTemp2 = (fRec10[1] - 1.3e+02);
		fVec1[0] = fTemp2;
		fRec11[0] = ((fConst13 * (fVec1[0] + fVec1[1])) + (fConst12 * fRec11[1]));
		fRec10[0] = Ftube4(0, (fRec11[0] + (fTemp1 * (1 + (fSlow2 * ((4 - (4 * fabs(fTemp1))) - 1))))));
		fRec9[0] = ((fConst15 * ((fConst14 * fRec10[1]) + (fConst0 * fRec10[0]))) + (fConst2 * fRec9[1]));
		double fTemp3 = (fRec9[0] * fRec8[0]);
		fVec2[0] = fTemp3;
		fRec7[0] = ((fConst16 * (fVec2[0] + fVec2[1])) + (fConst9 * fRec7[1]));
		double fTemp4 = (fRec6[1] - 1.3e+02);
		fVec3[0] = fTemp4;
		fRec12[0] = ((fConst20 * (fVec3[0] + fVec3[1])) + (fConst19 * fRec12[1]));
		fRec6[0] = Ftube4(1, (fRec12[0] + fRec7[0]));
		fRec5[0] = ((fConst15 * ((fConst14 * fRec6[1]) + (fConst0 * fRec6[0]))) + (fConst2 * fRec5[1]));
		double fTemp5 = (fRec8[0] * fRec5[0]);
		fVec4[0] = fTemp5;
		fRec4[0] = ((fConst16 * (fVec4[0] + fVec4[1])) + (fConst9 * fRec4[1]));
		fRec2[0] = Ftube4(1, (fRec4[0] + fRec3[0]));
		fRec1[0] = ((fConst15 * ((fConst14 * fRec2[1]) + (fConst0 * fRec2[0]))) + (fConst2 * fRec1[1]));
		double fTemp6 = (fRec14[1] - 1.3e+02);
		fVec5[0] = fTemp6;
		fRec15[0] = ((fConst6 * (fVec5[0] + fVec5[1])) + (fConst5 * fRec15[1]));
		fRec14[0] = Ftube4(0, (fRec15[0] + fRec4[0]));
		fRec13[0] = ((fConst15 * ((fConst14 * fRec14[1]) + (fConst0 * fRec14[0]))) + (fConst2 * fRec13[1]));
		output0[i] = (FAUSTFLOAT)((fRec13[0] + fRec1[0]) * fRec0[0]);
		// post processing
		fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec5[1] = fVec5[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fVec4[1] = fVec4[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec12[1] = fRec12[0];
		fVec3[1] = fVec3[0];
		fRec7[1] = fRec7[0];
		fVec2[1] = fVec2[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec1[1] = fVec1[0];
		fRec8[1] = fRec8[0];
		fRec3[1] = fRec3[0];
		fVec0[1] = fVec0[0];
		fRec0[1] = fRec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerInit("amp", init);
}

} // end namespace gxamp11
