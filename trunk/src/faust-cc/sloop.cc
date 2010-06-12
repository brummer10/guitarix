namespace sloop {
// generated from file '../src/faust/sloop.dsp'

FAUSTFLOAT 	fslider0;
double 	fRec0[2];
FAUSTFLOAT 	fcheckbox0;
int 	IOTA;
double 	fVec0[2097152];
int 	iVec1[2];
int 	iRec2[2];
double 	fRec1[2];
FAUSTFLOAT 	fcheckbox1;
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	IOTA = 0;
	for (int i=0; i<2097152; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) iVec1[i] = 0;
	for (int i=0; i<2; i++) iRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = fcheckbox0;
	double 	fSlow2 = (1.0 - fSlow1);
	int 	iSlow3 = int(fSlow1);
	double 	fSlow4 = fcheckbox1;
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		double fTemp0 = (double)input0[i];
		double fTemp1 = ((fSlow1 * fTemp0) + (fSlow2 * fRec1[1]));
		fVec0[IOTA&2097151] = fTemp1;
		iVec1[0] = iSlow3;
		iRec2[0] = (((iSlow3 - iVec1[1]) <= 0) * (iSlow3 + iRec2[1]));
		int iTemp2 = int((iRec2[0] - 1));
		int iTemp3 = (1 + iTemp2);
		fRec1[0] = (((0 - (iTemp3 - iRec2[0])) * fVec0[(IOTA-int((int(iTemp3) & 2097151)))&2097151]) + (((2 + iTemp2) - iRec2[0]) * fVec0[(IOTA-int((iTemp2 & 2097151)))&2097151]));
		output0[i] = (FAUSTFLOAT)(fTemp0 + (fSlow4 * (fRec1[0] * fRec0[0])));
		// post processing
		fRec1[1] = fRec1[0];
		iRec2[1] = iRec2[0];
		iVec1[1] = iVec1[0];
		IOTA = IOTA+1;
		fRec0[1] = fRec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("SampleLooper.Play","","B","",&fcheckbox1, 0.0, 0.0, 1.0, 1.0);
	registerVar("SampleLooper.Capture","","B","",&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	registerVar("SampleLooper.gain","","S","",&fslider0, 0.0, -96.0, 4.0, 0.1);
	registerInit(init);
}

} // end namespace sloop
