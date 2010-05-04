namespace moog {
// generated from file '../src/faust/moog.dsp'

FAUSTFLOAT 	fslider0;
float 	fRec1[2];
float 	fConst0;
FAUSTFLOAT 	fslider1;
float 	fRec5[2];
float 	fRec4[2];
float 	fRec3[2];
float 	fRec2[2];
float 	fRec0[2];
float 	fRec10[2];
float 	fRec9[2];
float 	fRec8[2];
float 	fRec7[2];
float 	fRec6[2];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	fConst0 = (6.283185307179586f / fSamplingFreq);
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
}

void compute(int count, float *input0, float *input1, float *output0, float *output1)
{
	float 	fSlow0 = (0.0010000000000000009f * fslider0);
	float 	fSlow1 = (0 - fslider1);
	for (int i=0; i<count; i++) {
		fRec1[0] = (fSlow0 + (0.999f * fRec1[1]));
		float fTemp0 = (fConst0 * fRec1[0]);
		float fTemp1 = faustpower<4>(fTemp0);
		float fTemp2 = (1.0f - fTemp0);
		fRec5[0] = (((float)input0[i] + (fSlow1 * fRec0[1])) + (fTemp2 * fRec5[1]));
		fRec4[0] = (fRec5[0] + (fTemp2 * fRec4[1]));
		fRec3[0] = (fRec4[0] + (fTemp2 * fRec3[1]));
		fRec2[0] = (fRec3[0] + (fTemp2 * fRec2[1]));
		fRec0[0] = (fRec2[0] * fTemp1);
		output0[i] = (FAUSTFLOAT)fRec0[0];
		fRec10[0] = (((float)input1[i] + (fSlow1 * fRec6[1])) + (fTemp2 * fRec10[1]));
		fRec9[0] = (fRec10[0] + (fTemp2 * fRec9[1]));
		fRec8[0] = (fRec9[0] + (fTemp2 * fRec8[1]));
		fRec7[0] = (fRec8[0] + (fTemp2 * fRec7[1]));
		fRec6[0] = (fRec7[0] * fTemp1);
		output1[i] = (FAUSTFLOAT)fRec6[0];
		// post processing
		fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec1[1] = fRec1[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("moog.Q","","S","",&fslider1, 1.0f, 0.0f, 4.0f, 0.1f);
	registerVar("moog.fr","","S","",&fslider0, 3e+03f, 4.4e+02f, 6e+03f, 1e+01f);
	registerInit(init);
}

} // end namespace moog
