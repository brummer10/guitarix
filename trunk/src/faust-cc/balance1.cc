namespace balance1 {
// generated from file '../src/faust/balance1.dsp'

FAUSTFLOAT&	fslider0 = get_alias("amp.balance");
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
}

void compute(int count, float *input0, float *output0, float *output1)
{
	float 	fSlow0 = fslider0;
	float 	fSlow1 = (1 - max(0, fSlow0));
	float 	fSlow2 = (1 - max(0, (0 - fSlow0)));
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		output0[i] = (FAUSTFLOAT)(fSlow1 * fTemp0);
		output1[i] = (FAUSTFLOAT)(fSlow2 * fTemp0);
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerInit(init);
}

} // end namespace balance1
