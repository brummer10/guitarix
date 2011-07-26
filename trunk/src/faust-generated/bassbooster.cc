namespace bassbooster {
// generated from file '../src/faust/bassbooster.dsp'

double 	fConst0;
double 	fConst1;
double 	fConst2;
double 	fConst3;
double 	fConst4;
double 	fRec0[3];
FAUSTFLOAT 	fslider0;
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = tan((376.99111843077515 / fSamplingFreq));
	fConst1 = faustpower<2>(fConst0);
	fConst2 = (2 * (fConst1 - 1));
	fConst3 = (1 + (fConst0 * (fConst0 - 1.4142135623730951)));
	fConst4 = (1.0 / (1 + (fConst0 * (1.4142135623730951 + fConst0))));
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = pow(10,(0.05 * fslider0));
	double 	fSlow1 = sqrt((2 * fSlow0));
	double 	fSlow2 = (fConst0 * fSlow0);
	double 	fSlow3 = (1 + (fConst0 * (fSlow2 - fSlow1)));
	double 	fSlow4 = (2 * ((fConst1 * fSlow0) - 1));
	double 	fSlow5 = (1 + (fConst0 * (fSlow2 + fSlow1)));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((double)input0[i] - (fConst4 * ((fConst3 * fRec0[2]) + (fConst2 * fRec0[1]))));
		output0[i] = (FAUSTFLOAT)(fConst4 * (((fSlow5 * fRec0[0]) + (fSlow4 * fRec0[1])) + (fSlow3 * fRec0[2])));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("bassbooster.Level","","S","",&fslider0, 1e+01, 0.5, 2e+01, 0.5);
	registerInit("bassbooster", init);
}

} // end namespace bassbooster
