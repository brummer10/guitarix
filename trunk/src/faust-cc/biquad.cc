namespace biquad {
// generated from file '../src/faust/biquad.dsp'

FAUSTFLOAT 	fslider0;
float 	fConst0;
float 	fRec0[3];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (6.283185307179586f / fSamplingFreq);
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = logf((fConst0 * fslider0));
	float 	fSlow1 = (0 - (1.8442f * cosf(expf((0.07238887f + (fSlow0 * (1.31282248f + (fSlow0 * (0.43359433f + (fSlow0 * (0.27547621f + (fSlow0 * (0.06446806f + (0.00506158f * fSlow0))))))))))))));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((float)input0[i] - ((0.8502684100000001f * fRec0[2]) + (fSlow1 * fRec0[1])));
		output0[i] = (FAUSTFLOAT)(0.31622776601683794f * (fRec0[0] - (1.059f * fRec0[1])));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("biquad.Freq","","S","",&fslider0, 1.2e+03f, 3e+02f, 3e+03f, 5.0f);
	registerInit(init);
}

} // end namespace biquad
