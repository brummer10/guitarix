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
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (1 - max(0, fSlow0));
	double 	fSlow2 = (1 - max(0, (0 - fSlow0)));
	for (int i=0; i<count; i++) {
		output0[i] = (FAUSTFLOAT)(fSlow1 * (double)input0[i]);
		output1[i] = (FAUSTFLOAT)(fSlow2 * (double)input1[i]);
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("amp.balance","Balance","S","",&fslider0, 0.0, -1.0, 1.0, 0.1);
	registerInit("balance", init);
}

} // end namespace balance
