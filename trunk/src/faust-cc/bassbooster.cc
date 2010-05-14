namespace bassbooster {
// generated from file '../src/faust/bassbooster.dsp'

float 	fConst0;
float 	fConst1;
float 	fConst2;
float 	fConst3;
float 	fConst4;
float 	fRec0[3];
float 	fConst5;
float 	fConst6;
float 	fConst7;
float 	fConst8;
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = tanf((376.99111843077515f / fSamplingFreq));
	fConst1 = faustpower<2>(fConst0);
	fConst2 = (2 * (fConst1 - 1));
	fConst3 = (1 + (fConst0 * (fConst0 - 1.4142135623730951f)));
	fConst4 = (1.0f / (1 + (fConst0 * (1.4142135623730951f + fConst0))));
	for (int i=0; i<3; i++) fRec0[i] = 0;
	fConst5 = (3.1622776601683795f * fConst0);
	fConst6 = (1 + (fConst0 * (fConst5 - 2.514866859365871f)));
	fConst7 = (2 * ((3.1622776601683795f * fConst1) - 1));
	fConst8 = (1 + (fConst0 * (fConst5 + 2.514866859365871f)));
}

void compute(int count, float *input0, float *output0)
{
	for (int i=0; i<count; i++) {
		fRec0[0] = ((float)input0[i] - (fConst4 * ((fConst3 * fRec0[2]) + (fConst2 * fRec0[1]))));
		output0[i] = (FAUSTFLOAT)(fConst4 * (((fConst8 * fRec0[0]) + (fConst7 * fRec0[1])) + (fConst6 * fRec0[2])));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerInit(init);
}

} // end namespace bassbooster
