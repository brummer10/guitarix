// generated from file '../src/faust/inputgain.dsp' by dsp2cc:
namespace inputgain {
static FAUSTFLOAT 	fslider0;
static double 	fRec0[2];
static int	fSamplingFreq;

static void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		output0[i] = (FAUSTFLOAT)((double)input0[i] * fRec0[0]);
		// post processing
		fRec0[1] = fRec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("amp.in_level","in / level","S","",&fslider0, 0.0, -4e+01, 4e+01, 0.1);
	registerInit("amp", init);
}

} // end namespace inputgain
