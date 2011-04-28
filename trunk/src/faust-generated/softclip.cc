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
	double 	fSlow1 = (fSlow0 - 2);
	double 	fSlow2 = (2 - fSlow0);
	for (int i=0; i<count; i++) {
		output0[i] = (FAUSTFLOAT)max(fSlow1, min(fSlow2, (double)input0[i]));
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("amp.fuzz","","S","",&fslider0, 0.0, 0.0, 1.99, 0.01);
	registerInit("amp", init);
}

} // end namespace softclip
