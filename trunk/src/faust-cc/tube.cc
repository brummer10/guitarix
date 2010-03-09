namespace tube {
// generated from file '../src/faust/tube.dsp'

FAUSTFLOAT&	fslider0=*(float*)&GxEngine::instance()->ffuzzytube;
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = (0.25f * fslider0);
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		output0[i] = (FAUSTFLOAT)max(-0.7f, min(0.7f, (fTemp0 * (1 + (fSlow0 * ((2 - fabsf(fTemp0)) - 1))))));
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("tube.fuzzy","count","S","",&fslider0, 1.0f, -3.0f, 10.0f, 1.0f);
	registerInit(init);
}

} // end namespace tube
