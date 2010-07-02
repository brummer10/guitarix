namespace stage3 {
// generated from file '../src/faust/stage3.dsp'

double 	fVec0[2];
FAUSTFLOAT 	fslider0;
double 	fRec0[2];
double 	fConst0;
double 	fConst1;
double 	fConst2;
double 	fConst3;
double 	fConst4;
double 	fConst5;
double 	fRec3[2];
double 	fVec1[2];
double 	fConst6;
double 	fConst7;
double 	fConst8;
double 	fRec4[2];
double 	fRec2[2];
double 	fConst9;
double 	fRec1[2];
FAUSTFLOAT 	fcheckbox0;
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	fConst0 = (1.0 / tan((0.5 * (((3.141592653589793 * fSamplingFreq) - 194.77874452256717) / fSamplingFreq))));
	fConst1 = (1 + fConst0);
	fConst2 = (0 - ((fConst0 - 1) / fConst1));
	fConst3 = (1.0 / tan((20517.741620594938 / fSamplingFreq)));
	fConst4 = (fConst3 - 1);
	fConst5 = (1.0 / (1 + fConst3));
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	fConst6 = (1.0 / tan((609.4689747964198 / fSamplingFreq)));
	fConst7 = (fConst6 - 1);
	fConst8 = (1.0 / (1 + fConst6));
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	fConst9 = (1.0 / fConst1);
	for (int i=0; i<2; i++) fRec1[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	int 	iSlow1 = int(fcheckbox0);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec3[0] = (fConst5 * ((fVec0[0] + fVec0[1]) + (fConst4 * fRec3[1])));
		double fTemp1 = (fRec2[1] - 2.5e+02);
		fVec1[0] = fTemp1;
		fRec4[0] = (fConst8 * ((fConst7 * fRec4[1]) + (0.0082 * (fVec1[0] + fVec1[1]))));
		fRec2[0] = Ftube(1, (fRec4[0] + fRec3[0]));
		fRec1[0] = ((fConst9 * ((0.025 * fRec2[0]) - (0.025 * fRec2[1]))) + (fConst2 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)((iSlow1)?(fRec1[0] * fRec0[0]):fVec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fVec1[1] = fVec1[0];
		fRec3[1] = fRec3[0];
		fRec0[1] = fRec0[0];
		fVec0[1] = fVec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("stage3.ON","","B","",&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	registerVar("stage3.gain3","","S","",&fslider0, 6.0, -1e+01, 2e+01, 0.1);
	registerInit(init);
}

} // end namespace stage3
