namespace delay {
// generated from file '../src/faust/delay.dsp'

int 	IOTA;
float 	fVec0[8192];
FAUSTFLOAT&	fslider0=*(float*)&GxEngine::instance()->fsliderdel2;
FAUSTFLOAT&	fslider1=*(float*)&GxEngine::instance()->fdel_gain1;
float 	fRec0[2];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	for (int i=0; i<8192; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = fslider0;
	int 	iSlow1 = int(fSlow0);
	int 	iSlow2 = int((iSlow1 & 262143));
	int 	iSlow3 = (1 + iSlow1);
	float 	fSlow4 = (iSlow3 - fSlow0);
	int 	iSlow5 = int((int(iSlow3) & 262143));
	float 	fSlow6 = (fSlow0 - iSlow1);
	float 	fSlow7 = (1.000000e-03f * powf(10,(5.000000e-02f * fslider1)));
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		fVec0[IOTA&8191] = fTemp0;
		fRec0[0] = (fSlow7 + (0.999f * fRec0[1]));
		output0[i] = (FAUSTFLOAT)(fVec0[IOTA&8191] + (fRec0[0] * ((fSlow6 * fVec0[(IOTA-iSlow5)&8191]) + (fSlow4 * fVec0[(IOTA-iSlow2)&8191]))));
		// post processing
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("delay.gain","","S","",&fslider1, 0.0f, -20.0f, 20.0f, 0.1f);
	registerVar("delay.delay","","S","",&fslider0, 0.0f, 0.0f, 5000.0f, 10.0f);
	registerInit(init);
}

} // end namespace delay
