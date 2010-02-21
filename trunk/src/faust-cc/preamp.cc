namespace preamp {
// generated from file '../src/faust/preamp.dsp'

float 	fVec0[3];
FAUSTFLOAT 	fslider0;
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<3; i++) fVec0[i] = 0;
	fslider0 = 1.0f;
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = fslider0;
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		fVec0[0] = fTemp0;
		float fTemp1 = (fVec0[2] + (fVec0[0] + fVec0[1]));
		float fTemp2 = (fTemp1 * fTemp1);
		float fTemp3 = ((3.333333e-04f - (1.666667e-08f * fTemp1)) - (5.555556e-12f * fTemp2));
		float fTemp4 = ((fTemp1 * fTemp3) * (1.5f - (0.5f * (fTemp2 * (fTemp3 * fTemp3)))));
		output0[i] = (FAUSTFLOAT)(750 * (atanf((fSlow0 * fTemp4)) / atanf(fTemp4)));
		// post processing
		fVec0[2] = fVec0[1]; fVec0[1] = fVec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("preamp.atan","drive","S","Input level for pre-amp (higher level gives more distortion)",&fslider0, 1.0f, 1.0f, 10.0f, 1.0f);
}

} // end namespace preamp
