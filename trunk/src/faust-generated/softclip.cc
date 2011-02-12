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
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (1 - fSlow0);
	double 	fSlow2 = (fSlow0 - 1);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		output0[i] = (FAUSTFLOAT)(0.5 * (fabs((fTemp0 + fSlow2)) - fabs((fTemp0 + fSlow1))));
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("amp.fuzz","","S","",&fslider0, 0.01, 0.01, 0.99, 0.01);
	registerInit("amp", init);
}

} // end namespace softclip
