namespace overdrive {
// generated from file '../src/faust/overdrive.dsp'

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
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (fSlow0 - 1);
	double 	fSlow2 = (0.0010000000000000009 * pow(10,(0.05 * (0 - (0.5 * fSlow0)))));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		double fTemp1 = fabs(fTemp0);
		fRec0[0] = (fSlow2 + (0.999 * fRec0[1]));
		output0[i] = (FAUSTFLOAT)(((fTemp0 * fRec0[0]) * (fSlow0 + fTemp1)) / (1 + ((fSlow1 * fTemp1) + faustpower<2>(fTemp0))));
		// post processing
		fRec0[1] = fRec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("overdrive.drive","","S","",&fslider0, 1.0, 1.0, 2e+01, 0.1);
	registerInit(init);
}

} // end namespace overdrive
