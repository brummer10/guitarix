namespace gx_feedback {
// generated from file '../src/faust/gx_feedback.dsp'

FAUSTFLOAT 	fslider0;
FAUSTFLOAT 	fslider1;
double 	fRec0[6];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<6; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.01 * fslider0);
	double 	fSlow1 = (1 - fSlow0);
	double 	fSlow2 = fslider1;
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec0[0] = ((fSlow0 * fTemp0) - (fSlow2 * fRec0[5]));
		output0[i] = (FAUSTFLOAT)(fRec0[0] + (fSlow1 * fTemp0));
		// post processing
		for (int i=5; i>0; i--) fRec0[i] = fRec0[i-1];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("feedback.feedback","","S","",&fslider1, 0.0, -1.0, 1.0, 0.01);
	registerVar("feedback.wet_dry","","S","",&fslider0, 1e+02, 0.0, 1e+02, 1.0);
	registerInit("feedback", init);
}

} // end namespace gx_feedback
