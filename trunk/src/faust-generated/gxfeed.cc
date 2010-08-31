namespace gxfeed {
// generated from file '../src/faust/gxfeed.dsp'

int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
}

void compute(int count, float *input0, float *output0, float *output1)
{
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		output0[i] = (FAUSTFLOAT)fTemp0;
		output1[i] = (FAUSTFLOAT)fTemp0;
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerInit("amp", init);
}

} // end namespace gxfeed
