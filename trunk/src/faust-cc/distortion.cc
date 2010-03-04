namespace distortion {
// generated from file '../src/faust/distortion.dsp'

FAUSTFLOAT&	fslider0=GxEngine::instance()->fslider4;
int 	IOTA;
float 	fVec0[4096];
FAUSTFLOAT&	fslider1=GxEngine::instance()->;
float 	fRec1[2];
FAUSTFLOAT&	fentry0=GxEngine::instance()->;
float 	fConst0;
float 	fVec1[2];
float 	fRec3[2];
FAUSTFLOAT&	fentry1=GxEngine::instance()->;
float 	fConst1;
float 	fConst2;
float 	fVec2[2];
float 	fRec2[2];
FAUSTFLOAT&	fcheckbox0=GxEngine::instance()->;
FAUSTFLOAT&	fslider2=GxEngine::instance()->;
FAUSTFLOAT&	fslider3=GxEngine::instance()->;
float 	fVec3[2];
float 	fRec7[2];
float 	fVec4[2];
float 	fRec6[2];
float 	fRec5[3];
float 	fRec4[3];
FAUSTFLOAT&	fcheckbox1=GxEngine::instance()->;
FAUSTFLOAT&	fslider4=GxEngine::instance()->;
FAUSTFLOAT&	fslider5=GxEngine::instance()->fslider9;
float 	fVec5[2];
float 	fRec0[2];
FAUSTFLOAT&	fslider6=GxEngine::instance()->;
float 	fRec8[2];
float 	fVec6[2];
float 	fRec12[2];
float 	fVec7[2];
float 	fRec11[2];
float 	fRec10[3];
float 	fRec9[3];
FAUSTFLOAT&	fslider7=GxEngine::instance()->;
float 	fRec13[2];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	for (int i=0; i<4096; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	fConst0 = (3.141593f / fSamplingFreq);
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	fConst1 = (3.141593f * fSamplingFreq);
	fConst2 = (0.5f / fSamplingFreq);
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	fcheckbox0 = 0.0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	fcheckbox1 = 0.0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = (1.0f - fslider0);
	float 	fSlow1 = fslider1;
	int 	iSlow2 = int((int((fSlow1 - 1)) & 4095));
	int 	iSlow3 = int((int(fSlow1) & 4095));
	float 	fSlow4 = (1.0f / tanf((fConst0 * fentry0)));
	float 	fSlow5 = (fSlow4 - 1);
	float 	fSlow6 = (1.0f / (1 + fSlow4));
	float 	fSlow7 = (1.0f / tanf((fConst2 * (fConst1 - (6.283185f * fentry1)))));
	float 	fSlow8 = (1 + fSlow7);
	float 	fSlow9 = (1.0f / fSlow8);
	float 	fSlow10 = (0 - ((fSlow7 - 1) / fSlow8));
	int 	iSlow11 = int(fcheckbox0);
	float 	fSlow12 = tanf((fConst0 * fslider2));
	float 	fSlow13 = (2 * (1 - (1.0f / (fSlow12 * fSlow12))));
	float 	fSlow14 = (1.0f / fSlow12);
	float 	fSlow15 = (1 + ((fSlow14 - 0.765367f) / fSlow12));
	float 	fSlow16 = (1.0f / (1 + ((0.765367f + fSlow14) / fSlow12)));
	float 	fSlow17 = (1 + ((fSlow14 - 1.847759f) / fSlow12));
	float 	fSlow18 = (1.0f / (1 + ((1.847759f + fSlow14) / fSlow12)));
	float 	fSlow19 = (fConst0 * fslider3);
	float 	fSlow20 = (1.0f / (1 + fSlow19));
	float 	fSlow21 = (1 - fSlow19);
	int 	iSlow22 = int(fcheckbox1);
	float 	fSlow23 = fslider4;
	float 	fSlow24 = powf(10.0f,(2 * fslider5));
	float 	fSlow25 = (1.000000e-03f * powf(10,(5.000000e-02f * (fslider6 - 10))));
	float 	fSlow26 = (1.000000e-03f * powf(10,(5.000000e-02f * (fslider7 - 10))));
	for (int i=0; i<count; i++) {
		float 	S0[2];
		float 	S1[2];
		float 	S2[2];
		float fTemp0 = (float)input0[i];
		float fTemp1 = (fTemp0 + (fSlow0 * fRec1[1]));
		fVec0[IOTA&4095] = fTemp1;
		fRec1[0] = (0.5f * (fVec0[(IOTA-iSlow3)&4095] + fVec0[(IOTA-iSlow2)&4095]));
		S2[0] = fRec1[0];
		fVec1[0] = (fSlow6 * fRec1[0]);
		fRec3[0] = (fVec1[1] + (fSlow6 * (fRec1[0] + (fSlow5 * fRec3[1]))));
		float fTemp2 = (fSlow9 * fRec3[0]);
		fVec2[0] = fTemp2;
		fRec2[0] = ((fVec2[0] + (fSlow10 * fRec2[1])) - fVec2[1]);
		S2[1] = fRec2[0];
		float fTemp3 = S2[iSlow11];
		S1[0] = fTemp3;
		fVec3[0] = (fSlow20 * fTemp3);
		fRec7[0] = ((fSlow20 * (fTemp3 + (fSlow21 * fRec7[1]))) - fVec3[1]);
		fVec4[0] = (fSlow20 * fRec7[0]);
		fRec6[0] = ((fSlow20 * (fRec7[0] + (fSlow21 * fRec6[1]))) - fVec4[1]);
		fRec5[0] = (fRec6[0] - (fSlow18 * ((fSlow17 * fRec5[2]) + (fSlow13 * fRec5[1]))));
		fRec4[0] = ((fSlow18 * (fRec5[2] + (fRec5[0] + (2 * fRec5[1])))) - (fSlow16 * ((fSlow15 * fRec4[2]) + (fSlow13 * fRec4[1]))));
		S1[1] = (fSlow16 * (fRec4[2] + (fRec4[0] + (2 * fRec4[1]))));
		float fTemp4 = max(-1, min(1, (fSlow24 * (fSlow23 + S1[iSlow22]))));
		float fTemp5 = (fTemp4 * (1 - (0.333333f * (fTemp4 * fTemp4))));
		fVec5[0] = fTemp5;
		fRec0[0] = ((fVec5[0] + (0.995f * fRec0[1])) - fVec5[1]);
		fRec8[0] = (fSlow25 + (0.999f * fRec8[1]));
		float fTemp6 = (fRec8[0] * fRec0[0]);
		S0[0] = fTemp6;
		fVec6[0] = (fSlow20 * fTemp6);
		fRec12[0] = ((fSlow20 * (fTemp6 + (fSlow21 * fRec12[1]))) - fVec6[1]);
		fVec7[0] = (fSlow20 * fRec12[0]);
		fRec11[0] = ((fSlow20 * (fRec12[0] + (fSlow21 * fRec11[1]))) - fVec7[1]);
		fRec10[0] = (fRec11[0] - (fSlow18 * ((fSlow17 * fRec10[2]) + (fSlow13 * fRec10[1]))));
		fRec9[0] = ((fSlow18 * (fRec10[2] + (fRec10[0] + (2 * fRec10[1])))) - (fSlow16 * ((fSlow15 * fRec9[2]) + (fSlow13 * fRec9[1]))));
		S0[1] = (fSlow16 * (fRec9[2] + (fRec9[0] + (2 * fRec9[1]))));
		fRec13[0] = (fSlow26 + (0.999f * fRec13[1]));
		output0[i] = (FAUSTFLOAT)((fTemp0 * fRec13[0]) > S0[iSlow22]);
		// post processing
		fRec13[1] = fRec13[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec7[1] = fVec7[0];
		fRec12[1] = fRec12[0];
		fVec6[1] = fVec6[0];
		fRec8[1] = fRec8[0];
		fRec0[1] = fRec0[0];
		fVec5[1] = fVec5[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fVec4[1] = fVec4[0];
		fRec7[1] = fRec7[0];
		fVec3[1] = fVec3[0];
		fRec2[1] = fRec2[0];
		fVec2[1] = fVec2[0];
		fRec3[1] = fRec3[0];
		fVec1[1] = fVec1[0];
		fRec1[1] = fRec1[0];
		IOTA = IOTA+1;
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("distortion.sp.on/off","","S","",&fcheckbox1);
	registerVar("distortion.low/highpass.on/off","","S","",&fcheckbox0);
	registerVar("distortion.low/highpass..freqhigh","","S","",&fentry1, 720.0f, 20.0f, 7040.0f, 1.0f);
	registerVar("distortion.low/highpass..freqlow","","S","",&fentry0, 723.0f, 20.0f, 7040.0f, 1.0f);
	registerVar("distortion.pregain","","S","",&fslider7, 2.0f, 0.0f, 10.0f, 0.1f);
	registerVar("distortion.gain","","S","",&fslider6, 2.0f, 0.0f, 10.0f, 0.1f);
	registerVar("distortion.drive","","S","",&fslider5, 0.64f, 0.0f, 1.0f, 1.000000e-02f);
	registerVar("distortion.drivelevel","","S","",&fslider4, 1.000000e-02f, 0.0f, 1.0f, 1.000000e-02f);
	registerVar("distortion.sp.low-freq cutoff Hz","","S","",&fslider3, 130.0f, 20.0f, 1000.0f, 1.0f);
	registerVar("distortion.sp.high-freq cutoff Hz","","S","",&fslider2, 5000.0f, 1000.0f, 10000.0f, 1.0f);
	registerVar("distortion.resonans.vibrato","","S","",&fslider1, 1.0f, 0.0f, 1.0f, 1.000000e-02f);
	registerVar("distortion.resonans.trigger","","S","",&fslider0, 0.12f, 0.0f, 1.0f, 1.000000e-02f);
	registerInit(init);
}

} // end namespace distortion
