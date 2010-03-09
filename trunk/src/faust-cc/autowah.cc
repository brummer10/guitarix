namespace autowah {
// generated from file '../src/faust/autowah.dsp'

int 	IOTA;
int 	iVec0[1024];
int 	iRec2[2];
float 	fRec1[2];
float 	fConst0;
float 	fConst1;
float 	fRec3[2];
float 	fRec4[2];
float 	fRec0[3];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	for (int i=0; i<1024; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) iRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	fConst0 = (2827.433388f / fSamplingFreq);
	fConst1 = (1413.716694f / fSamplingFreq);
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		int iTemp1 = abs(int((4194304 * fTemp0)));
		iVec0[IOTA&1023] = iTemp1;
		iRec2[0] = ((iVec0[IOTA&1023] + iRec2[1]) - iVec0[(IOTA-1000)&1023]);
		float fTemp2 = min(1, max(0, (2.384186e-10f * float(iRec2[0]))));
		fRec1[0] = ((1.000000e-04f * powf(4.0f,fTemp2)) + (0.999f * fRec1[1]));
		float fTemp3 = powf(2.0f,(2.3f * fTemp2));
		float fTemp4 = (1 - (fConst1 * (fTemp3 / powf(2.0f,(1.0f + (2.0f * (1.0f - fTemp2)))))));
		fRec3[0] = ((1.000000e-03f * (0 - (2.0f * (fTemp4 * cosf((fConst0 * fTemp3)))))) + (0.999f * fRec3[1]));
		fRec4[0] = ((1.000000e-03f * (fTemp4 * fTemp4)) + (0.999f * fRec4[1]));
		fRec0[0] = (0 - (((fRec4[0] * fRec0[2]) + (fRec3[0] * fRec0[1])) - (fTemp0 * fRec1[0])));
		output0[i] = (FAUSTFLOAT)(fRec0[0] - fRec0[1]);
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec1[1] = fRec1[0];
		iRec2[1] = iRec2[0];
		IOTA = IOTA+1;
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerInit(init);
}

} // end namespace autowah
