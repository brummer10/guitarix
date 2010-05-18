namespace biquad {
// generated from file '../src/faust/biquad.dsp'

FAUSTFLOAT 	fslider0;
double 	fConst0;
double 	fRec0[3];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (6.283185307179586 / fSamplingFreq);
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = log((fConst0 * fslider0));
	double 	fSlow1 = (0 - (1.8442 * cos(exp((0.07238887 + (fSlow0 * (1.31282248 + (fSlow0 * (0.43359433 + (fSlow0 * (0.27547621 + (fSlow0 * (0.06446806 + (0.00506158 * fSlow0))))))))))))));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((double)input0[i] - ((0.8502684100000001 * fRec0[2]) + (fSlow1 * fRec0[1])));
		output0[i] = (FAUSTFLOAT)(0.31622776601683794 * (fRec0[0] - (1.059 * fRec0[1])));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("biquad.Freq","","S","",&fslider0, 1.2e+03, 3e+02, 3e+03, 5.0);
	registerInit(init);
}

} // end namespace biquad
