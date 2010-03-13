namespace distortion {
// generated from file '../src/faust/distortion.dsp'

int 	iVec0[2];
FAUSTFLOAT&	fslider0=*(float*)&GxEngine::instance()->fslider10;
float 	fRec0[2];
FAUSTFLOAT&	fslider1=*(float*)&GxEngine::instance()->fslider4;
int 	IOTA;
float 	fVec1[4096];
FAUSTFLOAT&	fslider2=*(float*)&GxEngine::instance()->fslider5;
float 	fRec2[2];
FAUSTFLOAT&	fentry0=*(float*)&GxEngine::instance()->fentry0;
float 	fConst0;
float 	fRec5[2];
float 	fVec2[2];
float 	fRec4[2];
FAUSTFLOAT&	fentry1=*(float*)&GxEngine::instance()->fentry1;
float 	fConst1;
float 	fConst2;
float 	fVec3[2];
float 	fRec3[2];
FAUSTFLOAT&	fcheckbox0=*(float*)&GxEngine::instance()->fcheckbox2;
FAUSTFLOAT&	fslider3=*(float*)&GxEngine::instance()->fslider6;
FAUSTFLOAT&	fslider4=*(float*)&GxEngine::instance()->fslider7;
float 	fVec4[2];
float 	fRec9[2];
float 	fVec5[2];
float 	fRec8[2];
float 	fRec7[3];
float 	fRec6[3];
FAUSTFLOAT&	fcheckbox1=*(float*)&GxEngine::instance()->fcheckbox3;
FAUSTFLOAT&	fslider5=*(float*)&GxEngine::instance()->fslider8;
FAUSTFLOAT&	fslider6=*(float*)&GxEngine::instance()->fslider9;
float 	fVec6[2];
float 	fRec1[2];
float 	fVec7[2];
float 	fRec13[2];
float 	fVec8[2];
float 	fRec12[2];
float 	fRec11[3];
float 	fRec10[3];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	IOTA = 0;
	for (int i=0; i<4096; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	fConst0 = (3.141593f / fSamplingFreq);
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	fConst1 = (3.141593f * fSamplingFreq);
	fConst2 = (0.5f / fSamplingFreq);
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = (1.000000e-03f * powf(10,(5.000000e-02f * (fslider0 - 10))));
	float 	fSlow1 = (1.0f - fslider1);
	float 	fSlow2 = fslider2;
	int 	iSlow3 = int((int((fSlow2 - 1)) & 4095));
	int 	iSlow4 = int((int(fSlow2) & 4095));
	float 	fSlow5 = (1.0f / tanf((fConst0 * fentry0)));
	float 	fSlow6 = (fSlow5 - 1);
	float 	fSlow7 = (1.0f / (1 + fSlow5));
	float 	fSlow8 = (1.0f / tanf((fConst2 * (fConst1 - (6.283185f * fentry1)))));
	float 	fSlow9 = (1 + fSlow8);
	float 	fSlow10 = (1.0f / fSlow9);
	float 	fSlow11 = (0 - ((fSlow8 - 1) / fSlow9));
	int 	iSlow12 = int(fcheckbox0);
	float 	fSlow13 = tanf((fConst0 * fslider3));
	float 	fSlow14 = (2 * (1 - (1.0f / (fSlow13 * fSlow13))));
	float 	fSlow15 = (1.0f / fSlow13);
	float 	fSlow16 = (1 + ((fSlow15 - 0.765367f) / fSlow13));
	float 	fSlow17 = (1.0f / (1 + ((0.765367f + fSlow15) / fSlow13)));
	float 	fSlow18 = (1 + ((fSlow15 - 1.847759f) / fSlow13));
	float 	fSlow19 = (1.0f / (1 + ((1.847759f + fSlow15) / fSlow13)));
	float 	fSlow20 = (fConst0 * fslider4);
	float 	fSlow21 = (1.0f / (1 + fSlow20));
	float 	fSlow22 = (1 - fSlow20);
	int 	iSlow23 = int(fcheckbox1);
	float 	fSlow24 = fslider5;
	float 	fSlow25 = powf(10.0f,(2 * fslider6));
	for (int i=0; i<count; i++) {
		float 	S0[2];
		iVec0[0] = 1;
		fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
		float 	S1[2];
		float 	S2[2];
		float fTemp0 = ((float)input0[i] + (fSlow1 * fRec2[1]));
		fVec1[IOTA&4095] = fTemp0;
		fRec2[0] = (0.5f * (fVec1[(IOTA-iSlow4)&4095] + fVec1[(IOTA-iSlow3)&4095]));
		S2[0] = fRec2[0];
		fRec5[0] = ((1.000000e-20f * (1 - iVec0[1])) - fRec5[1]);
		float fTemp1 = (fRec2[0] + fRec5[0]);
		fVec2[0] = (fSlow7 * fTemp1);
		fRec4[0] = (fVec2[1] + (fSlow7 * (fTemp1 + (fSlow6 * fRec4[1]))));
		float fTemp2 = (fSlow10 * fRec4[0]);
		fVec3[0] = fTemp2;
		fRec3[0] = ((fVec3[0] + (fSlow11 * fRec3[1])) - fVec3[1]);
		S2[1] = fRec3[0];
		float fTemp3 = S2[iSlow12];
		S1[0] = fTemp3;
		float fTemp4 = (fRec5[0] + fTemp3);
		fVec4[0] = (fSlow21 * fTemp4);
		fRec9[0] = ((fSlow21 * (fTemp4 + (fSlow22 * fRec9[1]))) - fVec4[1]);
		fVec5[0] = (fSlow21 * fRec9[0]);
		fRec8[0] = ((fSlow21 * (fRec9[0] + (fSlow22 * fRec8[1]))) - fVec5[1]);
		fRec7[0] = (fRec8[0] - (fSlow19 * ((fSlow18 * fRec7[2]) + (fSlow14 * fRec7[1]))));
		fRec6[0] = ((fSlow19 * (fRec7[2] + (fRec7[0] + (2 * fRec7[1])))) - (fSlow17 * ((fSlow16 * fRec6[2]) + (fSlow14 * fRec6[1]))));
		S1[1] = (fSlow17 * (fRec6[2] + (fRec6[0] + (2 * fRec6[1]))));
		float fTemp5 = max(-1, min(1, (fSlow25 * (fSlow24 + S1[iSlow23]))));
		float fTemp6 = (fTemp5 * (1 - (0.333333f * (fTemp5 * fTemp5))));
		fVec6[0] = fTemp6;
		fRec1[0] = ((fVec6[0] + (0.995f * fRec1[1])) - fVec6[1]);
		float fTemp7 = (fRec1[0] * fRec0[0]);
		S0[0] = fTemp7;
		float fTemp8 = (fRec5[0] + fTemp7);
		fVec7[0] = (fSlow21 * fTemp8);
		fRec13[0] = ((fSlow21 * (fTemp8 + (fSlow22 * fRec13[1]))) - fVec7[1]);
		fVec8[0] = (fSlow21 * fRec13[0]);
		fRec12[0] = ((fSlow21 * (fRec13[0] + (fSlow22 * fRec12[1]))) - fVec8[1]);
		fRec11[0] = (fRec12[0] - (fSlow19 * ((fSlow18 * fRec11[2]) + (fSlow14 * fRec11[1]))));
		fRec10[0] = ((fSlow19 * (fRec11[2] + (fRec11[0] + (2 * fRec11[1])))) - (fSlow17 * ((fSlow16 * fRec10[2]) + (fSlow14 * fRec10[1]))));
		S0[1] = (fSlow17 * (fRec10[2] + (fRec10[0] + (2 * fRec10[1]))));
		output0[i] = (FAUSTFLOAT)S0[iSlow23];
		// post processing
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fVec8[1] = fVec8[0];
		fRec13[1] = fRec13[0];
		fVec7[1] = fVec7[0];
		fRec1[1] = fRec1[0];
		fVec6[1] = fVec6[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fVec5[1] = fVec5[0];
		fRec9[1] = fRec9[0];
		fVec4[1] = fVec4[0];
		fRec3[1] = fRec3[0];
		fVec3[1] = fVec3[0];
		fRec4[1] = fRec4[0];
		fVec2[1] = fVec2[0];
		fRec5[1] = fRec5[0];
		fRec2[1] = fRec2[0];
		IOTA = IOTA+1;
		fRec0[1] = fRec0[0];
		iVec0[1] = iVec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("distortion.low_highcutoff.on_off","low highcutoff","B","",&fcheckbox1, 0.0, 0.0, 1.0, 1.0);
	registerVar("distortion.low_highpass.on_off","low highpass","B","",&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	registerVar("distortion.low_highpass.high_freq","high freq","S","",&fentry1, 130.0f, 20.0f, 7040.0f, 10.0f);
	registerVar("distortion.low_highpass.low_freq","low freq","S","",&fentry0, 5000.0f, 20.0f, 12000.0f, 10.0f);
	registerVar("distortion.drive","","S","",&fslider6, 0.64f, 0.0f, 1.0f, 1.000000e-02f);
	registerVar("distortion.level","","S","",&fslider5, 1.000000e-02f, 0.0f, 0.5f, 1.000000e-02f);
	registerVar("distortion.low_highcutoff.low_freq","low freq","S","low-freq cutoff Hz",&fslider4, 130.0f, 20.0f, 1000.0f, 10.0f);
	registerVar("distortion.low_highcutoff.high_freq","high freq","S","high-freq cutoff Hz",&fslider3, 5000.0f, 1000.0f, 12000.0f, 10.0f);
	registerVar("distortion.vibrato","","S","",&fslider2, 1.0f, 0.0f, 1.0f, 1.000000e-02f);
	registerVar("distortion.trigger","","S","",&fslider1, 0.12f, 0.0f, 1.0f, 1.000000e-02f);
	registerVar("distortion.gain","","S","",&fslider0, 2.0f, -10.0f, 10.0f, 0.1f);
	registerInit(init);
}

} // end namespace distortion
