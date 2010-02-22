namespace reso_tube {
// generated from file '../src/faust/reso_tube.dsp'

FAUSTFLOAT 	fslider0;
int 	IOTA;
float 	fVec0[4096];
FAUSTFLOAT 	fslider1;
float 	fRec0[2];
FAUSTFLOAT 	fslider2;
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	for (int i=0; i<4096; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = (1.0f - fslider0);
	float 	fSlow1 = fslider1;
	int 	iSlow2 = int((int((fSlow1 - 1)) & 4095));
	int 	iSlow3 = int((int(fSlow1) & 4095));
	float 	fSlow4 = (0.5f * fslider2);
	for (int i=0; i<count; i++) {
		float fTemp0 = ((float)input0[i] + 1.000000e-20f);
		float fTemp1 = ((0.5f * ((fTemp0 * (2 - fabsf(fTemp0))) - fTemp0)) + (fSlow0 * fRec0[1]));
		fVec0[IOTA&4095] = fTemp1;
		fRec0[0] = (0.5f * (fVec0[(IOTA-iSlow3)&4095] + fVec0[(IOTA-iSlow2)&4095]));
		output0[i] = (FAUSTFLOAT)max(-0.7f, min(0.7f, (fTemp0 - max(-0.7f, min(0.7f, (fSlow4 * fRec0[0]))))));
		// post processing
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("reso_tube.fuzzy","","S","",&fslider2, 0.5f, 0.0f, 1.0f, 1.000000e-02f);
	registerVar("reso_tube.vibrato","","S","",&fslider1, 0.5f, 0.0f, 1.0f, 1.000000e-02f);
	registerVar("reso_tube.trigger","","S","",&fslider0, 0.12f, 0.0f, 1.0f, 1.000000e-02f);
	registerInit(init);
}

} // end namespace reso_tube
