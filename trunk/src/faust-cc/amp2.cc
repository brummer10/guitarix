namespace amp2 {
// generated from file '../src/faust/amp2.dsp'

FAUSTFLOAT 	fslider0;
double 	fRec0[2];
FAUSTFLOAT 	fcheckbox0;
FAUSTFLOAT 	fslider1;
double 	fRec1[2];
double 	fConst0;
double 	fConst1;
double 	fConst2;
double 	fVec0[2];
double 	fConst3;
double 	fConst4;
double 	fConst5;
double 	fRec4[2];
double 	fRec3[2];
double 	fConst6;
double 	fRec2[2];
FAUSTFLOAT 	fcheckbox1;
double 	fVec1[2];
FAUSTFLOAT 	fslider2;
double 	fRec5[2];
double 	fConst7;
double 	fConst8;
double 	fConst9;
double 	fRec8[2];
double 	fVec2[2];
double 	fConst10;
double 	fConst11;
double 	fConst12;
double 	fRec9[2];
double 	fRec7[2];
double 	fRec6[2];
FAUSTFLOAT 	fcheckbox2;
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	fConst0 = (1.0 / tan((0.5 * (((3.141592653589793 * fSamplingFreq) - 194.77874452256717) / fSamplingFreq))));
	fConst1 = (1 + fConst0);
	fConst2 = (0 - ((fConst0 - 1) / fConst1));
	for (int i=0; i<2; i++) fVec0[i] = 0;
	fConst3 = (1.0 / tan((270.1769682087222 / fSamplingFreq)));
	fConst4 = (fConst3 - 1);
	fConst5 = (1.0 / (1 + fConst3));
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	fConst6 = (1.0 / fConst1);
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	fConst7 = (1.0 / tan((20517.741620594938 / fSamplingFreq)));
	fConst8 = (fConst7 - 1);
	fConst9 = (1.0 / (1 + fConst7));
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	fConst10 = (1.0 / tan((414.6902302738527 / fSamplingFreq)));
	fConst11 = (fConst10 - 1);
	fConst12 = (1.0 / (1 + fConst10));
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	int 	iSlow1 = int(fcheckbox0);
	double 	fSlow2 = (0.0010000000000000009 * pow(10,(0.05 * fslider1)));
	int 	iSlow3 = int(fcheckbox1);
	double 	fSlow4 = (0.0010000000000000009 * pow(10,(0.05 * fslider2)));
	int 	iSlow5 = int(fcheckbox2);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		double fTemp1 = ((iSlow1)?(fTemp0 * fRec0[0]):fTemp0);
		fRec1[0] = (fSlow2 + (0.999 * fRec1[1]));
		double fTemp2 = (fRec3[1] - 2.5e+02);
		fVec0[0] = fTemp2;
		fRec4[0] = (fConst5 * ((fConst4 * fRec4[1]) + (0.027 * (fVec0[0] + fVec0[1]))));
		fRec3[0] = Ftube(0, (fTemp1 + fRec4[0]));
		fRec2[0] = ((fConst6 * ((0.025 * fRec3[0]) - (0.025 * fRec3[1]))) + (fConst2 * fRec2[1]));
		double fTemp3 = ((iSlow3)?(fRec2[0] * fRec1[0]):fTemp1);
		fVec1[0] = fTemp3;
		fRec5[0] = (fSlow4 + (0.999 * fRec5[1]));
		fRec8[0] = (fConst9 * ((fVec1[0] + fVec1[1]) + (fConst8 * fRec8[1])));
		double fTemp4 = (fRec7[1] - 2.5e+02);
		fVec2[0] = fTemp4;
		fRec9[0] = (fConst12 * ((fConst11 * fRec9[1]) + (0.015 * (fVec2[0] + fVec2[1]))));
		fRec7[0] = Ftube(1, (fRec9[0] + fRec8[0]));
		fRec6[0] = ((fConst6 * ((0.025 * fRec7[0]) - (0.025 * fRec7[1]))) + (fConst2 * fRec6[1]));
		output0[i] = (FAUSTFLOAT)((iSlow5)?(fRec6[0] * fRec5[0]):fVec1[0]);
		// post processing
		fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec9[1] = fRec9[0];
		fVec2[1] = fVec2[0];
		fRec8[1] = fRec8[0];
		fRec5[1] = fRec5[0];
		fVec1[1] = fVec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fVec0[1] = fVec0[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("amp2.stage1.ON","","B","",&fcheckbox1, 0.0, 0.0, 1.0, 1.0);
	registerVar("amp2.preamp.ON","","B","",&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	registerVar("amp2.stage2.ON","","B","",&fcheckbox2, 0.0, 0.0, 1.0, 1.0);
	registerVar("amp2.stage2.gain2","","S","",&fslider2, 6.0, -1e+01, 2e+01, 0.1);
	registerVar("amp2.stage1.gain1","","S","",&fslider1, 6.0, -1e+01, 2e+01, 0.1);
	registerVar("amp2.preamp.Pregain","","S","",&fslider0, 3e+01, -1e+01, 8e+01, 0.1);
	registerInit("amp2", init);
}

} // end namespace amp2
