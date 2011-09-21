// generated from file '../src/faust/balance1.dsp' by dsp2cc:
namespace balance1 {
static FAUSTFLOAT&	fslider0 = get_alias("amp.balance");
static int	fSamplingFreq;

static void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
}

void compute(int count, float *input0, float *output0, float *output1)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (1 - max(0, fSlow0));
	double 	fSlow2 = (1 - max(0, (0 - fSlow0)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		output0[i] = (FAUSTFLOAT)(fSlow1 * fTemp0);
		output1[i] = (FAUSTFLOAT)(fSlow2 * fTemp0);
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerInit("balance1", init);
}

} // end namespace balance1
