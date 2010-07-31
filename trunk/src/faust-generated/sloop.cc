namespace sloop {
// generated from file '../src/faust/sloop.dsp'

volatile bool inited = false;
FAUSTFLOAT 	fslider0;
float 	fRec0[2];
FAUSTFLOAT 	fcheckbox0;
int 	IOTA;
float *fVec0;
int 	iVec1[2];
int 	iRec2[2];
float 	fRec1[2];
FAUSTFLOAT 	fcheckbox1;
int	fSamplingFreq;

void init(int samplingFreq)
{
	if (!fVec0) fVec0 = new float[2097152];
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	IOTA = 0;
	for (int i=0; i<2097152; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) iVec1[i] = 0;
	for (int i=0; i<2; i++) iRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	inited = true;
}

void mem_free()
{
	inited = false;
	jack_sync();
	if (fVec0) { delete fVec0; fVec0 = 0; }
}

inline bool is_inited()
{
    return inited;
}


void activate(bool start, int samplingFreq)
{
	if (start) {
		if (!is_inited()) {
			init(samplingFreq);
		}
	} else {
		if (is_inited()) {
			mem_free();
		}
	}
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = (0.0010000000000000009f * powf(10,(0.05f * fslider0)));
	float 	fSlow1 = fcheckbox0;
	float 	fSlow2 = (1.0f - fSlow1);
	int 	iSlow3 = int(fSlow1);
	float 	fSlow4 = fcheckbox1;
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
		float fTemp0 = (float)input0[i];
		float fTemp1 = ((fSlow1 * fTemp0) + (fSlow2 * fRec1[1]));
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
	registerVar("SampleLooper.gain","","S","",&fslider0, 0.0f, -96.0f, 4.0f, 0.1f);
	registerInit("SampleLooper", init);
}

} // end namespace sloop
