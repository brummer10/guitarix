namespace osc_tube {
// generated from file '../src/faust/osc_tube.dsp'

int 	iVec0[2];
double 	fConst0;
double 	fConst1;
double 	fConst2;
double 	fConst3;
double 	fConst4;
double 	fConst5;
double 	fConst6;
double 	fConst7;
double 	fConst8;
double 	fConst9;
double 	fRec4[2];
FAUSTFLOAT 	fslider0;
double 	fConst10;
double 	fConst11;
double 	fConst12;
double 	fConst13;
double 	fConst14;
double 	fConst15;
double 	fConst16;
double 	fVec1[3];
double 	fConst17;
double 	fConst18;
double 	fConst19;
double 	fConst20;
double 	fConst21;
double 	fRec6[3];
int 	IOTA;
double 	fVec2[4096];
FAUSTFLOAT 	fslider1;
double 	fRec5[2];
double 	fVec3[2];
double 	fConst22;
double 	fRec3[2];
double 	fRec2[2];
double 	fRec1[3];
double 	fRec0[3];
FAUSTFLOAT 	fslider2;
double 	fConst23;
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) iVec0[i] = 0;
	fConst0 = tan((15707.963267948966 / fSamplingFreq));
	fConst1 = (2 * (1 - (1.0 / faustpower<2>(fConst0))));
	fConst2 = (1.0 / fConst0);
	fConst3 = (1 + ((fConst2 - 0.76536686473018) / fConst0));
	fConst4 = (1 + ((0.76536686473018 + fConst2) / fConst0));
	fConst5 = (1.0 / fConst4);
	fConst6 = (1 + ((fConst2 - 1.847759065022573) / fConst0));
	fConst7 = (1.0 / (1 + ((1.847759065022573 + fConst2) / fConst0)));
	fConst8 = (408.4070449666731 / fSamplingFreq);
	fConst9 = (1 - fConst8);
	for (int i=0; i<2; i++) fRec4[i] = 0;
	fConst10 = (6.283185307179586 * (max(0, ((0.5 * fSamplingFreq) - 1e+02)) / fSamplingFreq));
	fConst11 = cos(fConst10);
	fConst12 = (1.316227766016838 * fConst11);
	fConst13 = (0 - (2 * (0 - (0.683772233983162 + fConst12))));
	fConst14 = (0.683772233983162 * fConst11);
	fConst15 = (0.5623413251903491 * sin(fConst10));
	fConst16 = (fConst15 - (fConst14 + 1.316227766016838));
	for (int i=0; i<3; i++) fVec1[i] = 0;
	fConst17 = (fConst15 + fConst14);
	fConst18 = (0.31622776601683794 * (1.316227766016838 - fConst17));
	fConst19 = (0.31622776601683794 * ((fConst15 + 1.316227766016838) - fConst14));
	fConst20 = (0 - (0.6324555320336759 * (fConst12 - 0.683772233983162)));
	fConst21 = (1.0 / (1.316227766016838 + fConst17));
	for (int i=0; i<3; i++) fRec6[i] = 0;
	IOTA = 0;
	for (int i=0; i<4096; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	fConst22 = (1.0 / (1 + fConst8));
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
	fConst23 = (0.5 / fConst4);
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (fslider0 + 0.09999999999999998);
	double 	fSlow1 = fslider1;
	int 	iSlow2 = int((int((0 - fSlow1)) & 4095));
	int 	iSlow3 = int((int((1 - fSlow1)) & 4095));
	double 	fSlow4 = (fConst23 * fslider2);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec4[0] = ((1e-20 * (1 - iVec0[1])) - fRec4[1]);
		double fTemp0 = (double)input0[i];
		fVec1[0] = fTemp0;
		fRec6[0] = (fConst21 * ((((fConst20 * fVec1[1]) + (fConst19 * fVec1[0])) + (fConst18 * fVec1[2])) + ((fConst16 * fRec6[2]) + (fConst13 * fRec6[1]))));
		double fTemp1 = ((0.5 * (fRec6[0] * ((2 - fabs(fRec6[0])) - 1))) + (fSlow0 * fRec5[1]));
		fVec2[IOTA&4095] = fTemp1;
		fRec5[0] = (0.5 * (fVec2[(IOTA-iSlow3)&4095] + fVec2[(IOTA-iSlow2)&4095]));
		double fTemp2 = (fRec5[0] + fRec4[0]);
		fVec3[0] = fTemp2;
		fRec3[0] = (fConst22 * ((fVec3[0] - fVec3[1]) + (fConst9 * fRec3[1])));
		fRec2[0] = (fConst22 * ((fRec3[0] - fRec3[1]) + (fConst9 * fRec2[1])));
		fRec1[0] = (fRec2[0] - (fConst7 * ((fConst6 * fRec1[2]) + (fConst1 * fRec1[1]))));
		fRec0[0] = ((fConst7 * (fRec1[2] + (fRec1[0] + (2 * fRec1[1])))) - (fConst5 * ((fConst3 * fRec0[2]) + (fConst1 * fRec0[1]))));
		output0[i] = (FAUSTFLOAT)max(-0.7, min(0.7, (fVec1[0] + (fSlow4 * (fRec0[2] + (fRec0[0] + (2 * fRec0[1])))))));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fVec3[1] = fVec3[0];
		fRec5[1] = fRec5[0];
		IOTA = IOTA+1;
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fVec1[2] = fVec1[1]; fVec1[1] = fVec1[0];
		fRec4[1] = fRec4[0];
		iVec0[1] = iVec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("tube2.fuzzy","tube","S","",&fslider2, 1.0, -3.0, 1e+01, 1.0);
	registerVar("tube2.vibrato","","S","",&fslider1, 1.0, 0.0, 0.99, 0.01);
	registerVar("tube2.resonanz","","S","",&fslider0, 0.5, 0.0, 0.9, 0.01);
	registerInit(init);
}

} // end namespace osc_tube
