namespace gxamp4 {
// generated from file '../src/faust/gxamp4.dsp'

double 	fConst0;
double 	fConst1;
double 	fConst2;
double 	fConst3;
double 	fConst4;
FAUSTFLOAT&	fslider0 = get_alias("amp2.stage2.gain1");
double 	fRec3[2];
double 	fConst5;
double 	fConst6;
double 	fConst7;
FAUSTFLOAT&	fslider1 = get_alias("amp2.stage1.Pregain");
double 	fRec10[2];
double 	fConst8;
double 	fConst9;
double 	fConst10;
double 	fVec0[2];
double 	fConst11;
double 	fRec11[2];
double 	fRec9[2];
double 	fConst12;
double 	fConst13;
double 	fRec8[2];
double 	fConst14;
double 	fRec7[2];
double 	fConst15;
double 	fConst16;
double 	fConst17;
double 	fVec1[2];
double 	fConst18;
double 	fRec12[2];
double 	fRec6[2];
double 	fRec5[2];
double 	fRec4[2];
double 	fRec2[3];
double 	fConst19;
double 	fConst20;
double 	fConst21;
double 	fVec2[2];
double 	fConst22;
double 	fRec13[2];
double 	fRec1[2];
double 	fRec0[2];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (1.0 / tan((97.38937226128358 / fSamplingFreq)));
	fConst1 = (1 + fConst0);
	fConst2 = (0 - ((1 - fConst0) / fConst1));
	fConst3 = log((7539.822368615503 / fSamplingFreq));
	fConst4 = (0 - (1.8442 * cos(exp((0.07238887 + (fConst3 * (1.31282248 + (fConst3 * (0.43359433 + (fConst3 * (0.27547621 + (fConst3 * (0.06446806 + (0.00506158 * fConst3))))))))))))));
	for (int i=0; i<2; i++) fRec3[i] = 0;
	fConst5 = (1.0 / tan((20517.741620594938 / fSamplingFreq)));
	fConst6 = (1 + fConst5);
	fConst7 = (0 - ((1 - fConst5) / fConst6));
	for (int i=0; i<2; i++) fRec10[i] = 0;
	fConst8 = (1.0 / tan((270.1769682087222 / fSamplingFreq)));
	fConst9 = (1 + fConst8);
	fConst10 = (0 - ((1 - fConst8) / fConst9));
	for (int i=0; i<2; i++) fVec0[i] = 0;
	fConst11 = (0.027 / fConst9);
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	fConst12 = (0 - fConst0);
	fConst13 = (0.025 / fConst1);
	for (int i=0; i<2; i++) fRec8[i] = 0;
	fConst14 = (2.0 / fConst6);
	for (int i=0; i<2; i++) fRec7[i] = 0;
	fConst15 = (1.0 / tan((414.6902302738527 / fSamplingFreq)));
	fConst16 = (1 + fConst15);
	fConst17 = (0 - ((1 - fConst15) / fConst16));
	for (int i=0; i<2; i++) fVec1[i] = 0;
	fConst18 = (0.015 / fConst16);
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	fConst19 = (1.0 / tan((609.4689747964198 / fSamplingFreq)));
	fConst20 = (1 + fConst19);
	fConst21 = (0 - ((1 - fConst19) / fConst20));
	for (int i=0; i<2; i++) fVec2[i] = 0;
	fConst22 = (0.0082 / fConst20);
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * fslider1)));
	for (int i=0; i<count; i++) {
		fRec3[0] = (fSlow0 + (0.999 * fRec3[1]));
		fRec10[0] = (fSlow1 + (0.999 * fRec10[1]));
		double fTemp0 = (fRec9[1] - 2.5e+02);
		fVec0[0] = fTemp0;
		fRec11[0] = ((fConst11 * (fVec0[0] + fVec0[1])) + (fConst10 * fRec11[1]));
		fRec9[0] = Ftube3(0, (fRec11[0] + ((double)input0[i] * fRec10[0])));
		fRec8[0] = ((fConst13 * ((fConst12 * fRec9[1]) + (fConst0 * fRec9[0]))) + (fConst2 * fRec8[1]));
		fRec7[0] = ((fConst14 * (fRec8[0] + fRec8[1])) + (fConst7 * fRec7[1]));
		double fTemp1 = (fRec6[1] - 2.5e+02);
		fVec1[0] = fTemp1;
		fRec12[0] = ((fConst18 * (fVec1[0] + fVec1[1])) + (fConst17 * fRec12[1]));
		fRec6[0] = Ftube3(1, (fRec12[0] + (fRec10[0] * fRec7[0])));
		fRec5[0] = ((fConst13 * ((fConst12 * fRec6[1]) + (fConst0 * fRec6[0]))) + (fConst2 * fRec5[1]));
		fRec4[0] = ((fConst14 * (fRec5[0] + fRec5[1])) + (fConst7 * fRec4[1]));
		fRec2[0] = ((fRec4[0] * fRec3[0]) - ((0.8502684100000001 * fRec2[2]) + (fConst4 * fRec2[1])));
		double fTemp2 = (fRec1[1] - 2.5e+02);
		fVec2[0] = fTemp2;
		fRec13[0] = ((fConst22 * (fVec2[0] + fVec2[1])) + (fConst21 * fRec13[1]));
		fRec1[0] = Ftube2(1, ((fRec13[0] + fRec2[0]) - (1.059 * fRec2[1])));
		fRec0[0] = ((fConst13 * ((fConst12 * fRec1[1]) + (fConst0 * fRec1[0]))) + (fConst2 * fRec0[1]));
		output0[i] = (FAUSTFLOAT)(0.77 * fRec0[0]);
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec13[1] = fRec13[0];
		fVec2[1] = fVec2[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec12[1] = fRec12[0];
		fVec1[1] = fVec1[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec11[1] = fRec11[0];
		fVec0[1] = fVec0[0];
		fRec10[1] = fRec10[0];
		fRec3[1] = fRec3[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerInit("amp2", init);
}

} // end namespace gxamp4
