namespace impulseresponse {
// generated from file '../src/faust/impulseresponse.dsp'

FAUSTFLOAT 	fslider0;
float 	fConst0;
FAUSTFLOAT 	fslider1;
float 	fConst1;
float 	fVec0[3];
FAUSTFLOAT 	fcheckbox0;
FAUSTFLOAT 	fslider2;
float 	fRec0[3];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (3.141592653589793f / fSamplingFreq);
	fConst1 = (6.283185307179586f / fSamplingFreq);
	for (int i=0; i<3; i++) fVec0[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = expf((0 - (fConst0 * fslider0)));
	float 	fSlow1 = (2 * cosf((fConst1 * fslider1)));
	int 	iSlow2 = int(max(0, min(1, fcheckbox0)));
	float 	fSlow3 = (0.5f * (fslider2 * (1 - faustpower<2>(fSlow0))));
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		fVec0[0] = fTemp0;
		fRec0[0] = ((fSlow3 * (fVec0[0] - fVec0[2])) + (fSlow0 * ((fRec0[1] * ((iSlow2)?max(-0.6f, min(0.6f, fVec0[0])):fSlow1)) - (fSlow0 * fRec0[2]))));
		output0[i] = (FAUSTFLOAT)(fVec0[0] + fRec0[0]);
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fVec0[2] = fVec0[1]; fVec0[1] = fVec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("IR.peak","","S","peak gain",&fslider2, 1.0f, 0.0f, 1e+01f, 0.2f);
	registerVar("IR.auto_freq","auto freq","B","",&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	registerVar("IR.freq","","S","frequency (Hz)",&fslider1, 4.4e+02f, 2e+01f, 1.2e+04f, 1e+01f);
	registerVar("IR.bandwidth","","S","bandwidth (Hz)",&fslider0, 1e+02f, 2e+01f, 2e+04f, 1e+01f);
	registerInit(init);
}

} // end namespace impulseresponse
