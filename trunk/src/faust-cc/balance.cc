namespace balance {
// generated from file '../src/faust/balance.dsp'

FAUSTFLOAT 	fslider0;
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
}

void compute(int count, float *input0, float *input1, float *output0, float *output1)
{
	float 	fSlow0 = fslider0;
	float 	fSlow1 = (1 - max(0, fSlow0));
	float 	fSlow2 = (1 - max(0, (0 - fSlow0)));
	for (int i=0; i<count; i++) {
		output0[i] = (FAUSTFLOAT)(fSlow1 * (float)input0[i]);
		output1[i] = (FAUSTFLOAT)(fSlow2 * (float)input1[i]);
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("amp.balance","Balance","S","",&fslider0, 0.0f, -1.0f, 1.0f, 0.1f);
	registerInit(init);
}

} // end namespace balance
