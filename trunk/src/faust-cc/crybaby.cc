namespace crybaby {
// generated from file '../src/faust/crybaby.dsp'

FAUSTFLOAT&	fslider0=*(float*)&GxEngine::instance()->fslider11;
float 	fRec1[2];
float 	fConst0;
float 	fConst1;
float 	fRec2[2];
float 	fRec3[2];
float 	fRec0[3];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	fConst0 = (1413.716694f / fSamplingFreq);
	fConst1 = (2827.433388f / fSamplingFreq);
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = fslider0;
	float 	fSlow1 = (1.000000e-04f * powf(4.0f,fSlow0));
	float 	fSlow2 = powf(2.0f,(2.3f * fSlow0));
	float 	fSlow3 = (1 - (fConst0 * (fSlow2 / powf(2.0f,(1.0f + (2.0f * (1.0f - fSlow0)))))));
	float 	fSlow4 = (1.000000e-03f * (0 - (2.0f * (cosf((fConst1 * fSlow2)) * fSlow3))));
	float 	fSlow5 = (1.000000e-03f * (fSlow3 * fSlow3));
	for (int i=0; i<count; i++) {
		fRec1[0] = (fSlow1 + (0.999f * fRec1[1]));
		fRec2[0] = (fSlow4 + (0.999f * fRec2[1]));
		fRec3[0] = (fSlow5 + (0.999f * fRec3[1]));
		fRec0[0] = (0 - (((fRec3[0] * fRec0[2]) + (fRec2[0] * fRec0[1])) - ((float)input0[i] * fRec1[0])));
		output0[i] = (FAUSTFLOAT)(fRec0[0] - fRec0[1]);
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
	registerVar("crybaby.wah","","S","",&fslider0, 0.0f, 0.0f, 1.0f, 1.000000e-02f);
	registerInit(init);
}

} // end namespace crybaby
