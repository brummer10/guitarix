namespace softclip {
// generated from file '../src/faust/softclip.dsp'

FAUSTFLOAT 	fslider0;
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.88 * (2 - fslider0));
	double 	fSlow1 = (0 - fSlow0);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		double fTemp1 = max(fSlow1, min(fSlow0, fTemp0));
		output0[i] = (FAUSTFLOAT)(fTemp1 + (0.33 * (fTemp0 - max(fSlow1, min(fSlow0, fTemp1)))));
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("amp.fuzz","","S","",&fslider0, 0.0, 0.0, 1.99, 0.01);
	registerInit("amp", init);
}

} // end namespace softclip
