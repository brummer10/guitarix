namespace bassbooster {
// generated from file '../src/faust/bassbooster.dsp'

double 	fConst0;
double 	fConst1;
double 	fConst2;
double 	fConst3;
double 	fConst4;
double 	fRec0[3];
double 	fConst5;
double 	fConst6;
double 	fConst7;
double 	fConst8;
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
	fConst5 = (3.1622776601683795 * fConst0);
	fConst6 = (1 + (fConst0 * (fConst5 - 2.514866859365871)));
	fConst7 = (2 * ((3.1622776601683795 * fConst1) - 1));
	fConst8 = (1 + (fConst0 * (fConst5 + 2.514866859365871)));
}

void compute(int count, float *input0, float *output0)
{
	for (int i=0; i<count; i++) {
		fRec0[0] = ((double)input0[i] - (fConst4 * ((fConst3 * fRec0[2]) + (fConst2 * fRec0[1]))));
		output0[i] = (FAUSTFLOAT)(fConst4 * (((fConst8 * fRec0[0]) + (fConst7 * fRec0[1])) + (fConst6 * fRec0[2])));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerInit("bassbooster", init);
}

} // end namespace bassbooster
