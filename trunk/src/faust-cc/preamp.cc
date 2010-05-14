namespace preamp {
// generated from file '../src/faust/preamp.dsp'

float 	fVec0[3];
int 	iVec1[2];
float 	fRec0[2];
FAUSTFLOAT 	fslider0;
float 	fVec2[3];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<3; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) iVec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<3; i++) fVec2[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = fslider0;
	float 	fSlow1 = (0.75f / atanf(fSlow0));
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		fVec0[0] = fTemp0;
		iVec1[0] = 1;
		float fTemp1 = (fVec0[2] + (fVec0[0] + fVec0[1]));
		fRec0[0] = ((1e-20f * (1 - iVec1[1])) - fRec0[1]);
		float fTemp2 = (fTemp1 * ((0.3333333333333333f - (0.016666666666666663f * fTemp1)) - (0.016666666666666663f * (fTemp1 * (fRec0[0] + (0.3333333333333333f * fTemp1))))));
		float fTemp3 = (fSlow1 * atanf((fSlow0 * (fTemp2 * (1.5f - (0.5f * (fTemp2 * (fRec0[0] + fTemp2))))))));
		fVec2[0] = fTemp3;
		output0[i] = (FAUSTFLOAT)(0.3333333333333333f * (fVec2[2] + (fVec2[0] + fVec2[1])));
		// post processing
		fVec2[2] = fVec2[1]; fVec2[1] = fVec2[0];
		fRec0[1] = fRec0[0];
		iVec1[1] = iVec1[0];
		fVec0[2] = fVec0[1]; fVec0[1] = fVec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("preamp.atan","drive","S","Input level for pre-amp (higher level gives more distortion)",&fslider0, 1.0f, 1.0f, 1e+01f, 1.0f);
	registerInit(init);
}

} // end namespace preamp
