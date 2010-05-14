namespace overdrive {
// generated from file '../src/faust/overdrive.dsp'

FAUSTFLOAT 	fslider0;
float 	fRec0[2];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = fslider0;
	float 	fSlow1 = (fSlow0 - 1);
	float 	fSlow2 = (0.0010000000000000009f * powf(10,(0.05f * (0 - (0.5f * fSlow0)))));
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		float fTemp1 = fabsf(fTemp0);
		fRec0[0] = (fSlow2 + (0.999f * fRec0[1]));
		output0[i] = (FAUSTFLOAT)(((fTemp0 * fRec0[0]) * (fSlow0 + fTemp1)) / (1 + ((fSlow1 * fTemp1) + faustpower<2>(fTemp0))));
		// post processing
		fRec0[1] = fRec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("overdrive.drive","","S","",&fslider0, 1.0f, 1.0f, 2e+01f, 0.1f);
	registerInit(init);
}

} // end namespace overdrive
