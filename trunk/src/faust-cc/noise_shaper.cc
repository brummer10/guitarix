namespace noise_shaper {
// generated from file '../src/faust/noise_shaper.dsp'

float 	fConst0;
float 	fConst1;
float 	fRec0[2];
FAUSTFLOAT 	fslider0;
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = expf((0 - (2e+02f / fSamplingFreq)));
	fConst1 = expf((0 - (0.1f / fSamplingFreq)));
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = fslider0;
	float 	fSlow1 = (5 * fSlow0);
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		float fTemp1 = max(1, fabsf(fTemp0));
		float fTemp2 = ((fConst1 * (fRec0[1] >= fTemp1)) + (fConst0 * (fRec0[1] < fTemp1)));
		fRec0[0] = ((fTemp1 * (0 - (fTemp2 - 1))) + (fRec0[1] * fTemp2));
		float fTemp3 = max(0, (fSlow1 + (20 * log10f(fRec0[0]))));
		float fTemp4 = (0.5f * min(1, max(0, (0.09522902580706599f * fTemp3))));
		output0[i] = (FAUSTFLOAT)(fTemp0 * powf(10,(0.05f * (fSlow0 + ((fTemp3 * (0 - fTemp4)) / (1 + fTemp4))))));
		// post processing
		fRec0[1] = fRec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("shaper.sharper","sharper","S","",&fslider0, 1.0f, 1.0f, 1e+01f, 1.0f);
	registerInit(init);
}

} // end namespace noise_shaper
