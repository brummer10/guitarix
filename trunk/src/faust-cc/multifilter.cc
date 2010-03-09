namespace multifilter {
// generated from file '../src/faust/multifilter.dsp'

float 	fConst0;
float 	fConst1;
FAUSTFLOAT&	fslider0=*(float*)&GxEngine::instance()->fslMulti0;
float 	fConst2;
float 	fConst3;
FAUSTFLOAT&	fslider1=*(float*)&GxEngine::instance()->fslMulti1;
float 	fConst4;
float 	fConst5;
FAUSTFLOAT&	fslider2=*(float*)&GxEngine::instance()->fslMulti2;
float 	fConst6;
float 	fConst7;
FAUSTFLOAT&	fslider3=*(float*)&GxEngine::instance()->fslMulti3;
float 	fConst8;
float 	fConst9;
FAUSTFLOAT&	fslider4=*(float*)&GxEngine::instance()->fslMulti4;
float 	fConst10;
float 	fConst11;
FAUSTFLOAT&	fslider5=*(float*)&GxEngine::instance()->fslMulti5;
float 	fConst12;
float 	fConst13;
FAUSTFLOAT&	fslider6=*(float*)&GxEngine::instance()->fslMulti6;
float 	fConst14;
float 	fConst15;
FAUSTFLOAT&	fslider7=*(float*)&GxEngine::instance()->fslMulti7;
float 	fConst16;
float 	fConst17;
FAUSTFLOAT&	fslider8=*(float*)&GxEngine::instance()->fslMulti8;
float 	fConst18;
float 	fConst19;
FAUSTFLOAT&	fslider9=*(float*)&GxEngine::instance()->fslMulti9;
float 	fRec9[3];
float 	fConst20;
float 	fConst21;
float 	fRec8[3];
float 	fConst22;
float 	fConst23;
float 	fRec7[3];
float 	fConst24;
float 	fConst25;
float 	fRec6[3];
float 	fConst26;
float 	fConst27;
float 	fRec5[3];
float 	fConst28;
float 	fConst29;
float 	fRec4[3];
float 	fConst30;
float 	fConst31;
float 	fRec3[3];
float 	fConst32;
float 	fConst33;
float 	fRec2[3];
float 	fConst34;
float 	fConst35;
float 	fRec1[3];
float 	fConst36;
float 	fConst37;
float 	fRec0[3];
float 	fConst38;
float 	fConst39;
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = tanf((50265.482457f / fSamplingFreq));
	fConst1 = (2 * ((fConst0 * fConst0) - 1));
	fConst2 = tanf((25132.741229f / fSamplingFreq));
	fConst3 = (2 * ((fConst2 * fConst2) - 1));
	fConst4 = tanf((12566.370614f / fSamplingFreq));
	fConst5 = (2 * ((fConst4 * fConst4) - 1));
	fConst6 = tanf((6283.185307f / fSamplingFreq));
	fConst7 = (2 * ((fConst6 * fConst6) - 1));
	fConst8 = tanf((3141.592654f / fSamplingFreq));
	fConst9 = (2 * ((fConst8 * fConst8) - 1));
	fConst10 = tanf((1570.796327f / fSamplingFreq));
	fConst11 = (2 * ((fConst10 * fConst10) - 1));
	fConst12 = tanf((785.398163f / fSamplingFreq));
	fConst13 = (2 * ((fConst12 * fConst12) - 1));
	fConst14 = tanf((392.699082f / fSamplingFreq));
	fConst15 = (2 * ((fConst14 * fConst14) - 1));
	fConst16 = tanf((196.349541f / fSamplingFreq));
	fConst17 = (2 * ((fConst16 * fConst16) - 1));
	fConst18 = tanf((98.17477f / fSamplingFreq));
	fConst19 = (2 * ((fConst18 * fConst18) - 1));
	for (int i=0; i<3; i++) fRec9[i] = 0;
	fConst20 = (1 + (fConst18 * (fConst18 - 1.000000e-02f)));
	fConst21 = (1 + (fConst18 * (1.000000e-02f + fConst18)));
	for (int i=0; i<3; i++) fRec8[i] = 0;
	fConst22 = (1 + (fConst16 * (fConst16 - 1.000000e-02f)));
	fConst23 = (1 + (fConst16 * (1.000000e-02f + fConst16)));
	for (int i=0; i<3; i++) fRec7[i] = 0;
	fConst24 = (1 + (fConst14 * (fConst14 - 1.000000e-02f)));
	fConst25 = (1 + (fConst14 * (1.000000e-02f + fConst14)));
	for (int i=0; i<3; i++) fRec6[i] = 0;
	fConst26 = (1 + (fConst12 * (fConst12 - 1.000000e-02f)));
	fConst27 = (1 + (fConst12 * (1.000000e-02f + fConst12)));
	for (int i=0; i<3; i++) fRec5[i] = 0;
	fConst28 = (1 + (fConst10 * (fConst10 - 1.000000e-02f)));
	fConst29 = (1 + (fConst10 * (1.000000e-02f + fConst10)));
	for (int i=0; i<3; i++) fRec4[i] = 0;
	fConst30 = (1 + (fConst8 * (fConst8 - 1.000000e-02f)));
	fConst31 = (1 + (fConst8 * (1.000000e-02f + fConst8)));
	for (int i=0; i<3; i++) fRec3[i] = 0;
	fConst32 = (1 + (fConst6 * (fConst6 - 1.000000e-02f)));
	fConst33 = (1 + (fConst6 * (1.000000e-02f + fConst6)));
	for (int i=0; i<3; i++) fRec2[i] = 0;
	fConst34 = (1 + (fConst4 * (fConst4 - 1.000000e-02f)));
	fConst35 = (1 + (fConst4 * (1.000000e-02f + fConst4)));
	for (int i=0; i<3; i++) fRec1[i] = 0;
	fConst36 = (1 + (fConst2 * (fConst2 - 1.000000e-02f)));
	fConst37 = (1 + (fConst2 * (1.000000e-02f + fConst2)));
	for (int i=0; i<3; i++) fRec0[i] = 0;
	fConst38 = (1 + (fConst0 * (fConst0 - 1.000000e-02f)));
	fConst39 = (1 + (fConst0 * (fConst0 + 1.000000e-02f)));
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = (1.000000e-02f * powf(10,(5.000000e-02f * (0 - fslider0))));
	float 	fSlow1 = (1 + (fConst0 * (fConst0 - fSlow0)));
	float 	fSlow2 = (1.0f / (1 + (fConst0 * (fConst0 + fSlow0))));
	float 	fSlow3 = (1.000000e-02f * powf(10,(5.000000e-02f * (0 - fslider1))));
	float 	fSlow4 = (1 + (fConst2 * (fConst2 - fSlow3)));
	float 	fSlow5 = (1.0f / (1 + (fConst2 * (fConst2 + fSlow3))));
	float 	fSlow6 = (1.000000e-02f * powf(10,(5.000000e-02f * (0 - fslider2))));
	float 	fSlow7 = (1 + (fConst4 * (fConst4 - fSlow6)));
	float 	fSlow8 = (1.0f / (1 + (fConst4 * (fConst4 + fSlow6))));
	float 	fSlow9 = (1.000000e-02f * powf(10,(5.000000e-02f * (0 - fslider3))));
	float 	fSlow10 = (1 + (fConst6 * (fConst6 - fSlow9)));
	float 	fSlow11 = (1.0f / (1 + (fConst6 * (fConst6 + fSlow9))));
	float 	fSlow12 = (1.000000e-02f * powf(10,(5.000000e-02f * (0 - fslider4))));
	float 	fSlow13 = (1 + (fConst8 * (fConst8 - fSlow12)));
	float 	fSlow14 = (1.0f / (1 + (fConst8 * (fConst8 + fSlow12))));
	float 	fSlow15 = (1.000000e-02f * powf(10,(5.000000e-02f * (0 - fslider5))));
	float 	fSlow16 = (1 + (fConst10 * (fConst10 - fSlow15)));
	float 	fSlow17 = (1.0f / (1 + (fConst10 * (fConst10 + fSlow15))));
	float 	fSlow18 = (1.000000e-02f * powf(10,(5.000000e-02f * (0 - fslider6))));
	float 	fSlow19 = (1 + (fConst12 * (fConst12 - fSlow18)));
	float 	fSlow20 = (1.0f / (1 + (fConst12 * (fConst12 + fSlow18))));
	float 	fSlow21 = (1.000000e-02f * powf(10,(5.000000e-02f * (0 - fslider7))));
	float 	fSlow22 = (1 + (fConst14 * (fConst14 - fSlow21)));
	float 	fSlow23 = (1.0f / (1 + (fConst14 * (fConst14 + fSlow21))));
	float 	fSlow24 = (1.000000e-02f * powf(10,(5.000000e-02f * (0 - fslider8))));
	float 	fSlow25 = (1 + (fConst16 * (fConst16 - fSlow24)));
	float 	fSlow26 = (1.0f / (1 + (fConst16 * (fConst16 + fSlow24))));
	float 	fSlow27 = (1.000000e-02f * powf(10,(5.000000e-02f * (0 - fslider9))));
	float 	fSlow28 = (1 + (fConst18 * (fConst18 - fSlow27)));
	float 	fSlow29 = (1.0f / (1 + (fConst18 * (fConst18 + fSlow27))));
	for (int i=0; i<count; i++) {
		float fTemp0 = (fConst1 * fRec0[1]);
		float fTemp1 = (fConst3 * fRec1[1]);
		float fTemp2 = (fConst5 * fRec2[1]);
		float fTemp3 = (fConst7 * fRec3[1]);
		float fTemp4 = (fConst9 * fRec4[1]);
		float fTemp5 = (fConst11 * fRec5[1]);
		float fTemp6 = (fConst13 * fRec6[1]);
		float fTemp7 = (fConst15 * fRec7[1]);
		float fTemp8 = (fConst17 * fRec8[1]);
		float fTemp9 = (fConst19 * fRec9[1]);
		fRec9[0] = ((float)input0[i] - (fSlow29 * ((fSlow28 * fRec9[2]) + fTemp9)));
		fRec8[0] = ((fSlow29 * ((fTemp9 + (fConst21 * fRec9[0])) + (fConst20 * fRec9[2]))) - (fSlow26 * ((fSlow25 * fRec8[2]) + fTemp8)));
		fRec7[0] = ((fSlow26 * ((fTemp8 + (fConst23 * fRec8[0])) + (fConst22 * fRec8[2]))) - (fSlow23 * ((fSlow22 * fRec7[2]) + fTemp7)));
		fRec6[0] = ((fSlow23 * ((fTemp7 + (fConst25 * fRec7[0])) + (fConst24 * fRec7[2]))) - (fSlow20 * ((fSlow19 * fRec6[2]) + fTemp6)));
		fRec5[0] = ((fSlow20 * ((fTemp6 + (fConst27 * fRec6[0])) + (fConst26 * fRec6[2]))) - (fSlow17 * ((fSlow16 * fRec5[2]) + fTemp5)));
		fRec4[0] = ((fSlow17 * ((fTemp5 + (fConst29 * fRec5[0])) + (fConst28 * fRec5[2]))) - (fSlow14 * ((fSlow13 * fRec4[2]) + fTemp4)));
		fRec3[0] = ((fSlow14 * ((fTemp4 + (fConst31 * fRec4[0])) + (fConst30 * fRec4[2]))) - (fSlow11 * ((fSlow10 * fRec3[2]) + fTemp3)));
		fRec2[0] = ((fSlow11 * ((fTemp3 + (fConst33 * fRec3[0])) + (fConst32 * fRec3[2]))) - (fSlow8 * ((fSlow7 * fRec2[2]) + fTemp2)));
		fRec1[0] = ((fSlow8 * ((fTemp2 + (fConst35 * fRec2[0])) + (fConst34 * fRec2[2]))) - (fSlow5 * ((fSlow4 * fRec1[2]) + fTemp1)));
		fRec0[0] = ((fSlow5 * ((fTemp1 + (fConst37 * fRec1[0])) + (fConst36 * fRec1[2]))) - (fSlow2 * ((fSlow1 * fRec0[2]) + fTemp0)));
		output0[i] = (FAUSTFLOAT)(fSlow2 * ((fTemp0 + (fConst39 * fRec0[0])) + (fConst38 * fRec0[2])));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("MultiBandFilter.f125","","S","gain (dB) at 125 Hz",&fslider7, 0.0f, -50.0f, 10.0f, 0.1f);
	registerVar("MultiBandFilter.f250","","S","gain (dB) at 250 Hz",&fslider6, 0.0f, -50.0f, 10.0f, 0.1f);
	registerVar("MultiBandFilter.f500","","S","gain (dB) at 500 Hz",&fslider5, 0.0f, -50.0f, 10.0f, 0.1f);
	registerVar("MultiBandFilter.f1k","","S","gain (dB) at 1 kHz",&fslider4, 0.0f, -50.0f, 10.0f, 0.1f);
	registerVar("MultiBandFilter.f2k","","S","gain (dB) at 2 kHz",&fslider3, 0.0f, -50.0f, 10.0f, 0.1f);
	registerVar("MultiBandFilter.f4k","","S","gain (dB) at 4 kHz",&fslider2, 0.0f, -50.0f, 10.0f, 0.1f);
	registerVar("MultiBandFilter.f8k","","S","gain (dB) at 8 kHz",&fslider1, 0.0f, -50.0f, 10.0f, 0.1f);
	registerVar("MultiBandFilter.f16k","","S","gain (dB) at 16 kHz",&fslider0, 0.0f, -50.0f, 10.0f, 0.1f);
	registerVar("MultiBandFilter.f31_25","","S","gain (dB) at 31.25 Hz",&fslider9, 0.0f, -50.0f, 10.0f, 0.1f);
	registerVar("MultiBandFilter.f62_5","","S","gain (dB) at 62.5 Hz",&fslider8, 0.0f, -50.0f, 10.0f, 0.1f);
	registerInit(init);
}

} // end namespace multifilter
