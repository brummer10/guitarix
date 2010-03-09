namespace distortion {
// generated from file '../src/faust/distortion.dsp'

FAUSTFLOAT&	fslider0=*(float*)&GxEngine::instance()->fslider6;
float 	fConst0;
FAUSTFLOAT&	fslider1=*(float*)&GxEngine::instance()->fslider10;
float 	fRec4[2];
FAUSTFLOAT&	fentry0=*(float*)&GxEngine::instance()->fentry0;
FAUSTFLOAT&	fslider2=*(float*)&GxEngine::instance()->fslider4;
int 	IOTA;
float 	fVec0[4096];
FAUSTFLOAT&	fslider3=*(float*)&GxEngine::instance()->fslider5;
float 	fRec12[2];
float 	fVec1[2];
float 	fRec11[2];
FAUSTFLOAT&	fentry1=*(float*)&GxEngine::instance()->fentry1;
float 	fConst1;
float 	fConst2;
float 	fVec2[2];
float 	fRec10[2];
FAUSTFLOAT&	fcheckbox0=*(float*)&GxEngine::instance()->fcheckbox2;
FAUSTFLOAT&	fslider4=*(float*)&GxEngine::instance()->fslider7;
float 	fVec3[2];
float 	fRec9[2];
float 	fVec4[2];
float 	fRec8[2];
float 	fRec7[3];
float 	fRec6[3];
FAUSTFLOAT&	fcheckbox1=*(float*)&GxEngine::instance()->fcheckbox3;
FAUSTFLOAT&	fslider5=*(float*)&GxEngine::instance()->fslider8;
FAUSTFLOAT&	fslider6=*(float*)&GxEngine::instance()->fslider9;
float 	fVec5[2];
float 	fRec5[2];
float 	fVec6[2];
float 	fRec3[2];
float 	fVec7[2];
float 	fRec2[2];
float 	fRec1[3];
float 	fRec0[3];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (3.141593f / fSamplingFreq);
	for (int i=0; i<2; i++) fRec4[i] = 0;
	IOTA = 0;
	for (int i=0; i<4096; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	fConst1 = (3.141593f * fSamplingFreq);
	fConst2 = (0.5f / fSamplingFreq);
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	fcheckbox0 = 0.0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	fcheckbox1 = 0.0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = tanf((fConst0 * fslider0));
	float 	fSlow1 = (2 * (1 - (1.0f / (fSlow0 * fSlow0))));
	float 	fSlow2 = (1.0f / fSlow0);
	float 	fSlow3 = (1 + ((fSlow2 - 0.765367f) / fSlow0));
	float 	fSlow4 = (1.0f / (1 + ((0.765367f + fSlow2) / fSlow0)));
	float 	fSlow5 = (1 + ((fSlow2 - 1.847759f) / fSlow0));
	float 	fSlow6 = (1.0f / (1 + ((1.847759f + fSlow2) / fSlow0)));
	float 	fSlow7 = (1.000000e-03f * powf(10,(5.000000e-02f * (fslider1 - 10))));
	float 	fSlow8 = (1.0f / tanf((fConst0 * fentry0)));
	float 	fSlow9 = (fSlow8 - 1);
	float 	fSlow10 = (1.0f - fslider2);
	float 	fSlow11 = fslider3;
	int 	iSlow12 = int((int((fSlow11 - 1)) & 4095));
	int 	iSlow13 = int((int(fSlow11) & 4095));
	float 	fSlow14 = (1.0f / (1 + fSlow8));
	float 	fSlow15 = (1.0f / tanf((fConst2 * (fConst1 - (6.283185f * fentry1)))));
	float 	fSlow16 = (1 + fSlow15);
	float 	fSlow17 = (1.0f / fSlow16);
	float 	fSlow18 = (0 - ((fSlow15 - 1) / fSlow16));
	int 	iSlow19 = int(max(0, min(1, fcheckbox0)));
	float 	fSlow20 = (fConst0 * fslider4);
	float 	fSlow21 = (1.0f / (1 + fSlow20));
	float 	fSlow22 = (1 - fSlow20);
	int 	iSlow23 = int(max(0, min(1, fcheckbox1)));
	float 	fSlow24 = fslider5;
	float 	fSlow25 = powf(10.0f,(2 * fslider6));
	for (int i=0; i<count; i++) {
		float 	S0[2];
		fRec4[0] = (fSlow7 + (0.999f * fRec4[1]));
		float 	S1[2];
		float 	S2[2];
		float fTemp0 = ((float)input0[i] + (fSlow10 * fRec12[1]));
		fVec0[IOTA&4095] = fTemp0;
		fRec12[0] = (0.5f * (fVec0[(IOTA-iSlow13)&4095] + fVec0[(IOTA-iSlow12)&4095]));
		fVec1[0] = (fSlow14 * fRec12[0]);
		fRec11[0] = (fVec1[1] + (fSlow14 * (fRec12[0] + (fSlow9 * fRec11[1]))));
		float fTemp1 = (fSlow17 * fRec11[0]);
		fVec2[0] = fTemp1;
		fRec10[0] = ((fVec2[0] + (fSlow18 * fRec10[1])) - fVec2[1]);
		S2[0] = fRec10[0];
		S2[1] = fRec12[0];
		float fTemp2 = S2[iSlow19];
		fVec3[0] = (fSlow21 * fTemp2);
		fRec9[0] = ((fSlow21 * (fTemp2 + (fSlow22 * fRec9[1]))) - fVec3[1]);
		fVec4[0] = (fSlow21 * fRec9[0]);
		fRec8[0] = ((fSlow21 * (fRec9[0] + (fSlow22 * fRec8[1]))) - fVec4[1]);
		fRec7[0] = (fRec8[0] - (fSlow6 * ((fSlow5 * fRec7[2]) + (fSlow1 * fRec7[1]))));
		fRec6[0] = ((fSlow6 * (fRec7[2] + (fRec7[0] + (2 * fRec7[1])))) - (fSlow4 * ((fSlow3 * fRec6[2]) + (fSlow1 * fRec6[1]))));
		S1[0] = (fSlow4 * (fRec6[2] + (fRec6[0] + (2 * fRec6[1]))));
		S1[1] = fTemp2;
		float fTemp3 = max(-1, min(1, (fSlow25 * (fSlow24 + S1[iSlow23]))));
		float fTemp4 = (fTemp3 * (1 - (0.333333f * (fTemp3 * fTemp3))));
		fVec5[0] = fTemp4;
		fRec5[0] = ((fVec5[0] + (0.995f * fRec5[1])) - fVec5[1]);
		float fTemp5 = (fRec5[0] * fRec4[0]);
		fVec6[0] = (fSlow21 * fTemp5);
		fRec3[0] = ((fSlow21 * (fTemp5 + (fSlow22 * fRec3[1]))) - fVec6[1]);
		fVec7[0] = (fSlow21 * fRec3[0]);
		fRec2[0] = ((fSlow21 * (fRec3[0] + (fSlow22 * fRec2[1]))) - fVec7[1]);
		fRec1[0] = (fRec2[0] - (fSlow6 * ((fSlow5 * fRec1[2]) + (fSlow1 * fRec1[1]))));
		fRec0[0] = ((fSlow6 * (fRec1[2] + (fRec1[0] + (2 * fRec1[1])))) - (fSlow4 * ((fSlow3 * fRec0[2]) + (fSlow1 * fRec0[1]))));
		S0[0] = (fSlow4 * (fRec0[2] + (fRec0[0] + (2 * fRec0[1]))));
		S0[1] = fTemp5;
		output0[i] = (FAUSTFLOAT)S0[iSlow23];
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fVec7[1] = fVec7[0];
		fRec3[1] = fRec3[0];
		fVec6[1] = fVec6[0];
		fRec5[1] = fRec5[0];
		fVec5[1] = fVec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fVec4[1] = fVec4[0];
		fRec9[1] = fRec9[0];
		fVec3[1] = fVec3[0];
		fRec10[1] = fRec10[0];
		fVec2[1] = fVec2[0];
		fRec11[1] = fRec11[0];
		fVec1[1] = fVec1[0];
		fRec12[1] = fRec12[0];
		IOTA = IOTA+1;
		fRec4[1] = fRec4[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("distortion.low_highcutoff.on_off","low highcutoff","S","",&fcheckbox1);
	registerVar("distortion.low_highpass.on_off","low highpass","S","",&fcheckbox0);
	registerVar("distortion.low_highpass.high_freq","high freq","S","",&fentry1, 130.0f, 20.0f, 7040.0f, 10.0f);
	registerVar("distortion.low_highpass.low_freq","low freq","S","",&fentry0, 5000.0f, 20.0f, 12000.0f, 10.0f);
	registerVar("distortion.drive","","S","",&fslider6, 0.64f, 0.0f, 1.0f, 1.000000e-02f);
	registerVar("distortion.level","","S","",&fslider5, 1.000000e-02f, 0.0f, 0.5f, 1.000000e-02f);
	registerVar("distortion.low_highcutoff.low_freq","low freq","S","low-freq cutoff Hz",&fslider4, 130.0f, 20.0f, 1000.0f, 10.0f);
	registerVar("distortion.vibrato","","S","",&fslider3, 1.0f, 0.0f, 1.0f, 1.000000e-02f);
	registerVar("distortion.trigger","","S","",&fslider2, 0.12f, 0.0f, 1.0f, 1.000000e-02f);
	registerVar("distortion.gain","","S","",&fslider1, 2.0f, -10.0f, 10.0f, 0.1f);
	registerVar("distortion.low_highcutoff.high_freq","high freq","S","high-freq cutoff Hz",&fslider0, 5000.0f, 1000.0f, 12000.0f, 10.0f);
	registerInit(init);
}

} // end namespace distortion
