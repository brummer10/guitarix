namespace gxamp6 {
// generated from file '../src/faust/gxamp6.dsp'

FAUSTFLOAT&	fslider0 = get_alias("amp2.stage2.gain1");
double 	fRec0[2];
double 	fConst0;
double 	fConst1;
double 	fConst2;
double 	fConst3;
double 	fConst4;
double 	fConst5;
FAUSTFLOAT&	fslider1 = get_alias("amp2.stage1.Pregain");
double 	fRec7[2];
FAUSTFLOAT&	fslider2 = get_alias("gxdistortion.drive");
double 	fConst6;
double 	fConst7;
double 	fConst8;
double 	fVec0[2];
double 	fConst9;
double 	fRec10[2];
double 	fRec9[2];
double 	fConst10;
double 	fConst11;
double 	fRec8[2];
double 	fVec1[2];
double 	fConst12;
double 	fRec6[2];
double 	fConst13;
double 	fConst14;
double 	fConst15;
double 	fVec2[2];
double 	fConst16;
double 	fRec11[2];
double 	fRec5[2];
double 	fRec4[2];
double 	fVec3[2];
double 	fRec3[2];
double 	fConst17;
double 	fConst18;
double 	fConst19;
double 	fVec4[2];
double 	fConst20;
double 	fRec12[2];
double 	fRec2[2];
double 	fRec1[2];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	fConst0 = (1.0 / tan((97.38937226128358 / fSamplingFreq)));
	fConst1 = (1 + fConst0);
	fConst2 = (0 - ((1 - fConst0) / fConst1));
	fConst3 = (1.0 / tan((20517.741620594938 / fSamplingFreq)));
	fConst4 = (1 + fConst3);
	fConst5 = (0 - ((1 - fConst3) / fConst4));
	for (int i=0; i<2; i++) fRec7[i] = 0;
	fConst6 = (1.0 / tan((270.1769682087222 / fSamplingFreq)));
	fConst7 = (1 + fConst6);
	fConst8 = (0 - ((1 - fConst6) / fConst7));
	for (int i=0; i<2; i++) fVec0[i] = 0;
	fConst9 = (0.027 / fConst7);
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	fConst10 = (0 - fConst0);
	fConst11 = (0.025 / fConst1);
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	fConst12 = (1.0 / fConst4);
	for (int i=0; i<2; i++) fRec6[i] = 0;
	fConst13 = (1.0 / tan((414.6902302738527 / fSamplingFreq)));
	fConst14 = (1 + fConst13);
	fConst15 = (0 - ((1 - fConst13) / fConst14));
	for (int i=0; i<2; i++) fVec2[i] = 0;
	fConst16 = (0.015 / fConst14);
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	fConst17 = (1.0 / tan((609.4689747964198 / fSamplingFreq)));
	fConst18 = (1 + fConst17);
	fConst19 = (0 - ((1 - fConst17) / fConst18));
	for (int i=0; i<2; i++) fVec4[i] = 0;
	fConst20 = (0.0082 / fConst18);
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * fslider1)));
	double 	fSlow2 = (1.25 * fslider2);
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec7[0] = (fSlow1 + (0.999 * fRec7[1]));
		double fTemp0 = (double)input0[i];
		double fTemp1 = (fRec9[1] - 2.5e+02);
		fVec0[0] = fTemp1;
		fRec10[0] = ((fConst9 * (fVec0[0] + fVec0[1])) + (fConst8 * fRec10[1]));
		fRec9[0] = Ftube(0, (fRec10[0] + (fTemp0 * (1 + (fSlow2 * ((4 - (4 * fabs(fTemp0))) - 1))))));
		fRec8[0] = ((fConst11 * ((fConst10 * fRec9[1]) + (fConst0 * fRec9[0]))) + (fConst2 * fRec8[1]));
		double fTemp2 = (fRec8[0] * fRec7[0]);
		fVec1[0] = fTemp2;
		fRec6[0] = ((fConst12 * (fVec1[0] + fVec1[1])) + (fConst5 * fRec6[1]));
		double fTemp3 = (fRec5[1] - 2.5e+02);
		fVec2[0] = fTemp3;
		fRec11[0] = ((fConst16 * (fVec2[0] + fVec2[1])) + (fConst15 * fRec11[1]));
		fRec5[0] = Ftube(1, (fRec11[0] + fRec6[0]));
		fRec4[0] = ((fConst11 * ((fConst10 * fRec5[1]) + (fConst0 * fRec5[0]))) + (fConst2 * fRec4[1]));
		double fTemp4 = (fRec7[0] * fRec4[0]);
		fVec3[0] = fTemp4;
		fRec3[0] = ((fConst12 * (fVec3[0] + fVec3[1])) + (fConst5 * fRec3[1]));
		double fTemp5 = (fRec2[1] - 2.5e+02);
		fVec4[0] = fTemp5;
		fRec12[0] = ((fConst20 * (fVec4[0] + fVec4[1])) + (fConst19 * fRec12[1]));
		fRec2[0] = Ftube(1, (fRec12[0] + fRec3[0]));
		fRec1[0] = ((fConst11 * ((fConst10 * fRec2[1]) + (fConst0 * fRec2[0]))) + (fConst2 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec12[1] = fRec12[0];
		fVec4[1] = fVec4[0];
		fRec3[1] = fRec3[0];
		fVec3[1] = fVec3[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec11[1] = fRec11[0];
		fVec2[1] = fVec2[0];
		fRec6[1] = fRec6[0];
		fVec1[1] = fVec1[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fVec0[1] = fVec0[0];
		fRec7[1] = fRec7[0];
		fRec0[1] = fRec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerInit("amp", init);
}

} // end namespace gxamp6
