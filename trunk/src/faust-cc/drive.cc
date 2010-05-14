namespace drive {
// generated from file '../src/faust/drive.dsp'

FAUSTFLOAT 	fslider0;
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.0625 * fslider0);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		output0[i] = (FAUSTFLOAT)max(-0.7, min(0.7, (fTemp0 * (1 + (fSlow0 * ((4 - (4 * fabs(fTemp0))) - 1))))));
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("drive.value","drive","S","",&fslider0, 1.0, 1.0, 1e+01, 1.0);
	registerInit(init);
}

} // end namespace drive
