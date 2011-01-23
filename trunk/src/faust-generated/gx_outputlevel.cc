namespace gx_outputlevel {
// generated from file '../src/faust/gx_outputlevel.dsp'

FAUSTFLOAT 	fslider0;
double 	fRec0[2];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *input1, float *output0, float *output1)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		output0[i] = (FAUSTFLOAT)((double)input0[i] * fRec0[0]);
		output1[i] = (FAUSTFLOAT)((double)input1[i] * fRec0[0]);
		// post processing
		fRec0[1] = fRec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("amp.out_master","Level","S","",&fslider0, 0.0, -5e+01, 4.0, 0.1);
	registerInit("amp", init);
}

} // end namespace gx_outputlevel
