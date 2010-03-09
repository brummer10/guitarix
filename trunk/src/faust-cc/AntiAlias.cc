namespace AntiAlias {
// generated from file '../src/faust/AntiAlias.dsp'

FAUSTFLOAT&	fslider0=*(float*)&GxEngine::instance()->faas1;
float 	fRec0[4];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<4; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = fslider0;
	for (int i=0; i<count; i++) {
		fRec0[0] = ((float)input0[i] + (fSlow0 * fRec0[3]));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		for (int i=3; i>0; i--) fRec0[i] = fRec0[i-1];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("anti_aliase.feedback","Feedback","S","",&fslider0, 0.3f, 0.3f, 0.9f, 1.000000e-02f);
	registerInit(init);
}

} // end namespace AntiAlias
