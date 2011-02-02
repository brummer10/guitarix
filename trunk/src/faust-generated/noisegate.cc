namespace noisegate {
// generated from file '../src/faust/noisegate.dsp'

int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = ngate;
	for (int i=0; i<count; i++) {
		output0[i] = (FAUSTFLOAT)(fSlow0 * (double)input0[i]);
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerInit("amp", init);
}

} // end namespace noisegate
