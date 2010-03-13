namespace osc_tube {
// generated from file '../src/faust/osc_tube.dsp'

int 	iVec0[2];
float 	fConst0;
float 	fConst1;
float 	fConst2;
float 	fConst3;
float 	fConst4;
float 	fConst5;
float 	fConst6;
float 	fConst7;
float 	fConst8;
float 	fConst9;
float 	fRec4[2];
FAUSTFLOAT&	fslider0=*(float*)&GxEngine::instance()->fresotube1;
int 	IOTA;
float 	fVec1[4096];
FAUSTFLOAT&	fslider1=*(float*)&GxEngine::instance()->fresotube2;
float 	fRec5[2];
float 	fVec2[2];
float 	fConst10;
float 	fRec3[2];
float 	fRec2[2];
float 	fRec1[3];
float 	fRec0[3];
FAUSTFLOAT&	fslider2=*(float*)&GxEngine::instance()->fresotube3;
float 	fConst11;
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) iVec0[i] = 0;
	fConst0 = tanf((15707.963268f / fSamplingFreq));
	fConst1 = (2 * (1 - (1.0f / (fConst0 * fConst0))));
	fConst2 = (1.0f / fConst0);
	fConst3 = (1 + ((fConst2 - 0.765367f) / fConst0));
	fConst4 = (1 + ((0.765367f + fConst2) / fConst0));
	fConst5 = (1.0f / fConst4);
	fConst6 = (1 + ((fConst2 - 1.847759f) / fConst0));
	fConst7 = (1.0f / (1 + ((1.847759f + fConst2) / fConst0)));
	fConst8 = (408.407045f / fSamplingFreq);
	fConst9 = (1 - fConst8);
	for (int i=0; i<2; i++) fRec4[i] = 0;
	IOTA = 0;
	for (int i=0; i<4096; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	fConst10 = (1.0f / (1 + fConst8));
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
	fConst11 = (0.5f / fConst4);
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = (fslider0 + 1.000000e-01f);
	float 	fSlow1 = fslider1;
	int 	iSlow2 = int((int((0 - fSlow1)) & 4095));
	int 	iSlow3 = int((int((1 - fSlow1)) & 4095));
	float 	fSlow4 = (fConst11 * fslider2);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec4[0] = ((1.000000e-20f * (1 - iVec0[1])) - fRec4[1]);
		float fTemp0 = (float)input0[i];
		float fTemp1 = ((0.5f * (fTemp0 * ((2 - fabsf(fTemp0)) - 1))) + (fSlow0 * fRec5[1]));
		fVec1[IOTA&4095] = fTemp1;
		fRec5[0] = (0.5f * (fVec1[(IOTA-iSlow3)&4095] + fVec1[(IOTA-iSlow2)&4095]));
		float fTemp2 = (fRec5[0] + fRec4[0]);
		fVec2[0] = fTemp2;
		fRec3[0] = (fConst10 * ((fVec2[0] - fVec2[1]) + (fConst9 * fRec3[1])));
		fRec2[0] = (fConst10 * ((fRec3[0] - fRec3[1]) + (fConst9 * fRec2[1])));
		fRec1[0] = (fRec2[0] - (fConst7 * ((fConst6 * fRec1[2]) + (fConst1 * fRec1[1]))));
		fRec0[0] = ((fConst7 * (fRec1[2] + (fRec1[0] + (2 * fRec1[1])))) - (fConst5 * ((fConst3 * fRec0[2]) + (fConst1 * fRec0[1]))));
		output0[i] = (FAUSTFLOAT)max(-0.7f, min(0.7f, (fTemp0 + (fSlow4 * (fRec0[2] + (fRec0[0] + (2 * fRec0[1])))))));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fVec2[1] = fVec2[0];
		fRec5[1] = fRec5[0];
		IOTA = IOTA+1;
		fRec4[1] = fRec4[0];
		iVec0[1] = iVec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("tube2.fuzzy","count","S","",&fslider2, 1.0f, -3.0f, 10.0f, 1.0f);
	registerVar("tube2.vibrato","","S","",&fslider1, 1.0f, 0.0f, 1.0f, 1.000000e-02f);
	registerVar("tube2.resonanz","","S","",&fslider0, 0.5f, 0.0f, 0.9f, 1.000000e-02f);
	registerInit(init);
}

} // end namespace osc_tube
