namespace freeverb {
// generated from file '../src/faust/freeverb.dsp'

FAUSTFLOAT&	fslider0=*(float*)&GxEngine::instance()->fslider15;
float 	fRec9[2];
FAUSTFLOAT&	fslider1=*(float*)&GxEngine::instance()->fslider16;
int 	IOTA;
float 	fVec0[2048];
float 	fRec8[2];
float 	fRec11[2];
float 	fVec1[2048];
float 	fRec10[2];
float 	fRec13[2];
float 	fVec2[2048];
float 	fRec12[2];
float 	fRec15[2];
float 	fVec3[2048];
float 	fRec14[2];
float 	fRec17[2];
float 	fVec4[2048];
float 	fRec16[2];
float 	fRec19[2];
float 	fVec5[2048];
float 	fRec18[2];
float 	fRec21[2];
float 	fVec6[2048];
float 	fRec20[2];
float 	fRec23[2];
float 	fVec7[2048];
float 	fRec22[2];
float 	fVec8[1024];
float 	fRec6[2];
float 	fVec9[512];
float 	fRec4[2];
float 	fVec10[512];
float 	fRec2[2];
float 	fVec11[256];
float 	fRec0[2];
FAUSTFLOAT&	fslider2=*(float*)&GxEngine::instance()->fslider14;
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	IOTA = 0;
	for (int i=0; i<2048; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2048; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2048; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2048; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2048; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2048; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2048; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2048; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<1024; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<512; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<512; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<256; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = (0.4f * fslider0);
	float 	fSlow1 = (1 - fSlow0);
	float 	fSlow2 = (0.7f + (0.28f * fslider1));
	float 	fSlow3 = fslider2;
	float 	fSlow4 = (0.5f + fSlow3);
	float 	fSlow5 = (0.5f - fSlow3);
	for (int i=0; i<count; i++) {
		fRec9[0] = ((fSlow1 * fRec8[1]) + (fSlow0 * fRec9[1]));
		float fTemp0 = (float)input0[i];
		float fTemp1 = (1.500000e-02f * fTemp0);
		fVec0[IOTA&2047] = (fTemp1 + (fSlow2 * fRec9[0]));
		fRec8[0] = fVec0[(IOTA-1640)&2047];
		fRec11[0] = ((fSlow1 * fRec10[1]) + (fSlow0 * fRec11[1]));
		fVec1[IOTA&2047] = (fTemp1 + (fSlow2 * fRec11[0]));
		fRec10[0] = fVec1[(IOTA-1580)&2047];
		fRec13[0] = ((fSlow1 * fRec12[1]) + (fSlow0 * fRec13[1]));
		fVec2[IOTA&2047] = (fTemp1 + (fSlow2 * fRec13[0]));
		fRec12[0] = fVec2[(IOTA-1514)&2047];
		fRec15[0] = ((fSlow1 * fRec14[1]) + (fSlow0 * fRec15[1]));
		fVec3[IOTA&2047] = (fTemp1 + (fSlow2 * fRec15[0]));
		fRec14[0] = fVec3[(IOTA-1445)&2047];
		fRec17[0] = ((fSlow1 * fRec16[1]) + (fSlow0 * fRec17[1]));
		fVec4[IOTA&2047] = (fTemp1 + (fSlow2 * fRec17[0]));
		fRec16[0] = fVec4[(IOTA-1379)&2047];
		fRec19[0] = ((fSlow1 * fRec18[1]) + (fSlow0 * fRec19[1]));
		fVec5[IOTA&2047] = (fTemp1 + (fSlow2 * fRec19[0]));
		fRec18[0] = fVec5[(IOTA-1300)&2047];
		fRec21[0] = ((fSlow1 * fRec20[1]) + (fSlow0 * fRec21[1]));
		fVec6[IOTA&2047] = (fTemp1 + (fSlow2 * fRec21[0]));
		fRec20[0] = fVec6[(IOTA-1211)&2047];
		fRec23[0] = ((fSlow1 * fRec22[1]) + (fSlow0 * fRec23[1]));
		fVec7[IOTA&2047] = (fTemp1 + (fSlow2 * fRec23[0]));
		fRec22[0] = fVec7[(IOTA-1139)&2047];
		float fTemp2 = (((((((fRec22[0] + fRec20[0]) + fRec18[0]) + fRec16[0]) + fRec14[0]) + fRec12[0]) + fRec10[0]) + fRec8[0]);
		fVec8[IOTA&1023] = (fTemp2 + (0.5f * fRec6[1]));
		fRec6[0] = fVec8[(IOTA-579)&1023];
		float 	fRec7 = (0 - (fTemp2 - fRec6[1]));
		fVec9[IOTA&511] = (fRec7 + (0.5f * fRec4[1]));
		fRec4[0] = fVec9[(IOTA-464)&511];
		float 	fRec5 = (fRec4[1] - fRec7);
		fVec10[IOTA&511] = (fRec5 + (0.5f * fRec2[1]));
		fRec2[0] = fVec10[(IOTA-364)&511];
		float 	fRec3 = (fRec2[1] - fRec5);
		fVec11[IOTA&255] = (fRec3 + (0.5f * fRec0[1]));
		fRec0[0] = fVec11[(IOTA-248)&255];
		float 	fRec1 = (fRec0[1] - fRec3);
		output0[i] = (FAUSTFLOAT)((fSlow5 * fTemp0) + (fSlow4 * fRec1));
		// post processing
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fRec6[1] = fRec6[0];
		fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec8[1] = fRec8[0];
		IOTA = IOTA+1;
		fRec9[1] = fRec9[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("freeverb.wet_dry","wet/dry","S","",&fslider2, 0.0f, -0.5f, 0.5f, 0.1f);
	registerVar("freeverb.RoomSize","","S","",&fslider1, 0.5f, 0.0f, 1.0f, 2.500000e-02f);
	registerVar("freeverb.damp","","S","",&fslider0, 0.5f, 0.0f, 1.0f, 2.500000e-02f);
	registerInit(init);
}

} // end namespace freeverb
