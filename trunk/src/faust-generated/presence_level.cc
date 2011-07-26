namespace presence_level {
// generated from file '../src/faust/presence_level.dsp'

FAUSTFLOAT&	fslider0 = get_alias("con.Level");
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fslider0;
	for (int i=0; i<count; i++) {
		output0[i] = (FAUSTFLOAT)(fSlow0 * (double)input0[i]);
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerInit("con", init);
}

} // end namespace presence_level
