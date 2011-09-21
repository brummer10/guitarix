// generated from file '../src/faust/chorus_mono.dsp' by dsp2cc:
namespace chorus_mono {
volatile bool inited = false;
class SIG0 {
  private:
	int 	fSamplingFreq;
	int 	iRec1[2];
  public:
	int getNumInputs() 	{ return 0; }
	int getNumOutputs() 	{ return 1; }
	void init(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		for (int i=0; i<2; i++) iRec1[i] = 0;
	}
	void fill (int count, float output[]) {
		for (int i=0; i<count; i++) {
			iRec1[0] = (1 + iRec1[1]);
			output[i] = sinf((9.587379924285257e-05f * (iRec1[0] - 1)));
			// post processing
			iRec1[1] = iRec1[0];
		}
	}
};
static FAUSTFLOAT 	fslider0;
static int 	IOTA;
static float *fVec0;
static FAUSTFLOAT 	fslider1;
static float 	fConst0;
static float 	fRec0[2];
static float 	ftbl0[65536];
static float 	fConst1;
static FAUSTFLOAT 	fslider2;
static int	fSamplingFreq;

static void init(int samplingFreq)
{
	if (!fVec0) fVec0 = new float[65536];
	SIG0 sig0;
	sig0.init(samplingFreq);
	sig0.fill(65536,ftbl0);
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	for (int i=0; i<65536; i++) fVec0[i] = 0;
	fConst0 = (1.0f / fSamplingFreq);
	for (int i=0; i<2; i++) fRec0[i] = 0;
	fConst1 = (0.01f * fSamplingFreq);
	inited = true;
}

static void mem_free()
{
	inited = false;
	jack_sync();
	if (fVec0) { delete fVec0; fVec0 = 0; }
}

inline bool is_inited()
{
    return inited;
}


static void activate(bool start, int samplingFreq)
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
	float 	fSlow0 = (0.01f * fslider0);
	float 	fSlow1 = (fSlow0 + (1 - fSlow0));
	float 	fSlow2 = (fConst0 * fslider1);
	float 	fSlow3 = fslider2;
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		float fTemp1 = (fSlow0 * fTemp0);
		fVec0[IOTA&65535] = fTemp1;
		float fTemp2 = (fSlow2 + fRec0[1]);
		fRec0[0] = (fTemp2 - floorf(fTemp2));
		float fTemp3 = (65536 * (fRec0[0] - floorf(fRec0[0])));
		float fTemp4 = floorf(fTemp3);
		int iTemp5 = int(fTemp4);
		float fTemp6 = (fConst1 * (1 + (0.02f * ((ftbl0[((1 + iTemp5) & 65535)] * (fTemp3 - fTemp4)) + (ftbl0[(iTemp5 & 65535)] * ((1 + fTemp4) - fTemp3))))));
		int iTemp7 = int(fTemp6);
		int iTemp8 = (1 + iTemp7);
		output0[i] = (FAUSTFLOAT)((fSlow3 * (((fTemp6 - iTemp7) * fVec0[(IOTA-int((int(iTemp8) & 65535)))&65535]) + ((iTemp8 - fTemp6) * fVec0[(IOTA-int((iTemp7 & 65535)))&65535]))) + (fSlow1 * fTemp0));
		// post processing
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("chorus_mono.level","","S","",&fslider2, 0.5f, 0.0f, 1.0f, 0.01f);
	registerVar("chorus_mono.freq","","S","",&fslider1, 2.0f, 0.0f, 1e+01f, 0.01f);
	registerVar("chorus_mono.wet_dry","wet/dry","S","percentage of processed signal in output signal",&fslider0, 1e+02f, 0.0f, 1e+02f, 1.0f);
	registerInit("chorus_mono", init);
}

} // end namespace chorus_mono
