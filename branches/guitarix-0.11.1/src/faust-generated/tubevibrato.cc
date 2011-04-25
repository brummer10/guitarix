namespace tubevibrato {
// generated from file '../src/faust/tubevibrato.dsp'

FAUSTFLOAT 	fslider0;
double 	fRec0[2];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.5 * fslider0);
	for (int i=0; i<count; i++) {
		fRec0[0] = ((double)input0[i] + (fSlow0 * fRec0[1]));
		output0[i] = (FAUSTFLOAT)max(-0.7, min(0.7, fRec0[0]));
		// post processing
		fRec0[1] = fRec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("tube.vibrato","","S","",&fslider0, 0.0, 0.0, 2.0, 0.02);
	registerInit("tube", init);
}

} // end namespace tubevibrato
