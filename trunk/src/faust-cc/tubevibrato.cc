namespace tubevibrato {
// generated from file '../src/faust/tubevibrato.dsp'

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
	float 	fSlow0 = (0.5f * fslider0);
	for (int i=0; i<count; i++) {
		fRec0[0] = ((float)input0[i] + (fSlow0 * fRec0[1]));
		output0[i] = (FAUSTFLOAT)max(-0.7f, min(0.7f, fRec0[0]));
		// post processing
		fRec0[1] = fRec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("tube.vibrato","","S","",&fslider0, 0.0f, 0.0f, 2.0f, 0.02f);
	registerInit(init);
}

} // end namespace tubevibrato
