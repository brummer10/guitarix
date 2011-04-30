namespace autowah {
// generated from file '../src/faust/autowah.dsp'

int 	IOTA;
int 	iVec0[1024];
int 	iRec2[2];
FAUSTFLOAT&	fslider0 = get_alias("crybaby.wah");
double 	fRec1[2];
FAUSTFLOAT&	fslider1 = get_alias("crybaby.level");
FAUSTFLOAT&	fslider2 = get_alias("crybaby.wet_dry");
double 	fConst0;
double 	fConst1;
double 	fRec3[2];
double 	fRec4[2];
double 	fRec0[3];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	for (int i=0; i<1024; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) iRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	fConst0 = (2827.4333882308138 / fSamplingFreq);
	fConst1 = (1413.7166941154069 / fSamplingFreq);
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (4.76837158203125e-09 * fslider0);
	double 	fSlow1 = fslider2;
	double 	fSlow2 = (0.01 * (fSlow1 * fslider1));
	double 	fSlow3 = (1 - (0.01 * fSlow1));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		int iTemp1 = abs(int((4194304 * fTemp0)));
		iVec0[IOTA&1023] = iTemp1;
		iRec2[0] = ((iVec0[IOTA&1023] + iRec2[1]) - iVec0[(IOTA-1000)&1023]);
		double fTemp2 = min(1, max(0, (fSlow0 * double(iRec2[0]))));
		fRec1[0] = ((0.0001000000000000001 * pow(4.0,fTemp2)) + (0.999 * fRec1[1]));
		double fTemp3 = pow(2.0,(2.3 * fTemp2));
		double fTemp4 = (1 - (fConst1 * (fTemp3 / pow(2.0,(1.0 + (2.0 * (1.0 - fTemp2)))))));
		fRec3[0] = ((0.0010000000000000009 * (0 - (2.0 * (fTemp4 * cos((fConst0 * fTemp3)))))) + (0.999 * fRec3[1]));
		fRec4[0] = ((0.0010000000000000009 * faustpower<2>(fTemp4)) + (0.999 * fRec4[1]));
		fRec0[0] = (0 - (((fRec4[0] * fRec0[2]) + (fRec3[0] * fRec0[1])) - (fSlow2 * (fTemp0 * fRec1[0]))));
		output0[i] = (FAUSTFLOAT)((fRec0[0] + (fSlow3 * fTemp0)) - fRec0[1]);
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
	registerInit("autowah", init);
}

} // end namespace autowah
