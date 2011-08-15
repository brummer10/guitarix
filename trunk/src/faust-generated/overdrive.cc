namespace overdrive {
// generated from file '../src/faust/overdrive.dsp'

FAUSTFLOAT 	fslider0;
FAUSTFLOAT 	fslider1;
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
	double 	fSlow1 = (0.0001 * faustpower<2>(fSlow0));
	double 	fSlow2 = (0.01 * fSlow0);
	double 	fSlow3 = fslider1;
	double 	fSlow4 = (fSlow3 - 1);
	double 	fSlow5 = (0.0010000000000000009 * pow(10,(0.05 * (0 - (0.5 * fSlow3)))));
	double 	fSlow6 = (1 - fSlow2);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		double fTemp1 = fabs((fSlow2 * fTemp0));
		fRec0[0] = (fSlow5 + (0.999 * fRec0[1]));
		output0[i] = (FAUSTFLOAT)(fTemp0 * (fSlow6 + (fSlow2 * ((fRec0[0] * (fSlow3 + fTemp1)) / (1 + ((fSlow4 * fTemp1) + (fSlow1 * faustpower<2>(fTemp0))))))));
		// post processing
		fRec0[1] = fRec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("overdrive.drive","","S","",&fslider1, 1.0, 1.0, 2e+01, 0.1);
	registerVar("overdrive.wet_dry","wet/dry","S","percentage of processed signal in output signal",&fslider0, 1e+02, 0.0, 1e+02, 1.0);
	registerInit("overdrive", init);
}

} // end namespace overdrive
