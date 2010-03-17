namespace inputgain {
// generated from file '../src/faust/inputgain.dsp'

FAUSTFLOAT 	fslider0;
float 	fRec0[2];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = (1.000000e-03f * powf(10,(5.000000e-02f * fslider0)));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
		output0[i] = (FAUSTFLOAT)((float)input0[i] * fRec0[0]);
		// post processing
		fRec0[1] = fRec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("amp.in_level","in / level","S","",&fslider0, 0.0f, -40.0f, 40.0f, 0.1f);
	registerInit(init);
}

} // end namespace inputgain
