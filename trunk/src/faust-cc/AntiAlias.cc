namespace AntiAlias {
// generated from file '../src/faust/AntiAlias.dsp'

FAUSTFLOAT 	fslider0;
double 	fRec0[4];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<4; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fslider0;
	for (int i=0; i<count; i++) {
		fRec0[0] = (1e-20 + ((double)input0[i] + (fSlow0 * fRec0[3])));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		for (int i=3; i>0; i--) fRec0[i] = fRec0[i-1];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("anti_aliase.feedback","Feedback","S","",&fslider0, 0.3, 0.3, 0.9, 0.01);
	registerInit(init);
}

} // end namespace AntiAlias
