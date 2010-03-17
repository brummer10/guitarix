namespace drive {
// generated from file '../src/faust/drive.dsp'

FAUSTFLOAT 	fslider0;
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = (6.250000e-02f * fslider0);
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		output0[i] = (FAUSTFLOAT)max(-0.7f, min(0.7f, (fTemp0 * (1 + (fSlow0 * ((4 - (4 * fabsf(fTemp0))) - 1))))));
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("drive.value","drive","S","",&fslider0, 1.0f, 1.0f, 10.0f, 1.0f);
	registerInit(init);
}

} // end namespace drive
