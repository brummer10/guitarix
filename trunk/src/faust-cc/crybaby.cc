namespace crybaby {
// generated from file '../src/faust/crybaby.dsp'

FAUSTFLOAT&	fslider0=*(float*)&GxEngine::instance()->fslider13;
FAUSTFLOAT&	fslider1=*(float*)&GxEngine::instance()->fslider11;
float 	fConst0;
float 	fConst1;
float 	fRec1[2];
float 	fRec2[2];
float 	fRec3[2];
FAUSTFLOAT&	fslider2=*(float*)&GxEngine::instance()->fslider12;
float 	fRec0[3];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (1413.716694f / fSamplingFreq);
	fConst1 = (2827.433388f / fSamplingFreq);
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = fslider0;
	float 	fSlow1 = (1 - max(0, fSlow0));
	float 	fSlow2 = fslider1;
	float 	fSlow3 = powf(2.0f,(2.3f * fSlow2));
	float 	fSlow4 = (1 - (fConst0 * (fSlow3 / powf(2.0f,(1.0f + (2.0f * (1.0f - fSlow2)))))));
	float 	fSlow5 = (1.000000e-03f * (0 - (2.0f * (cosf((fConst1 * fSlow3)) * fSlow4))));
	float 	fSlow6 = (1.000000e-03f * (fSlow4 * fSlow4));
	float 	fSlow7 = (1.000000e-04f * powf(4.0f,fSlow2));
	float 	fSlow8 = fslider2;
	float 	fSlow9 = (1 - max(0, (0 - fSlow0)));
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		fRec1[0] = (fSlow5 + (0.999f * fRec1[1]));
		fRec2[0] = (fSlow6 + (0.999f * fRec2[1]));
		fRec3[0] = (fSlow7 + (0.999f * fRec3[1]));
		fRec0[0] = ((fSlow8 * (fTemp0 * fRec3[0])) - (0.996f * ((fRec2[0] * fRec0[2]) + (fRec1[0] * fRec0[1]))));
		output0[i] = (FAUSTFLOAT)((fSlow9 * (fRec0[0] - (0.996f * fRec0[1]))) + (fSlow1 * fTemp0));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("crybaby.level","","S","",&fslider2, 0.1f, 0.0f, 1.0f, 1.000000e-02f);
	registerVar("crybaby.wah","","S","",&fslider1, 0.0f, 0.0f, 1.0f, 1.000000e-02f);
	registerVar("crybaby.wet_dry","wet/dry","S","",&fslider0, 0.0f, -1.0f, 1.0f, 0.1f);
	registerInit(init);
}

} // end namespace crybaby
