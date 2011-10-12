// generated from file '../src/faust/chorus.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

namespace chorus {
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
static int 	IOTA;
static float *fVec0;
static FAUSTFLOAT 	fslider0;
static int 	iConst0;
static float 	fConst1;
static float 	fRec0[2];
static float 	ftbl0[65536];
static FAUSTFLOAT 	fslider1;
static FAUSTFLOAT 	fslider2;
static float 	fConst2;
static FAUSTFLOAT 	fslider3;
static float *fVec1;
static bool mem_allocated = false;
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<65536; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<65536; i++) fVec1[i] = 0;
}

static void init(unsigned int samplingFreq, PluginDef* = 0)
{
	SIG0 sig0;
	sig0.init(samplingFreq);
	sig0.fill(65536,ftbl0);
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0f / iConst0);
	fConst2 = (0.5f * iConst0);
}

static void mem_alloc()
{
	if (!fVec0) fVec0 = new float[65536];
	if (!fVec1) fVec1 = new float[65536];
	mem_allocated = true;
}

static void mem_free()
{
	mem_allocated = false;
	if (fVec0) { delete fVec0; fVec0 = 0; }
	if (fVec1) { delete fVec1; fVec1 = 0; }
}


static int activate(bool start, PluginDef* = 0)
{
    if (start) {
        if (!mem_allocated) {
            mem_alloc();
            clear_state();
        }
    } else if (!mem_allocated) {
        mem_free();
    }
    return 0;
}

static void compute(int count, float *input0, float *input1, float *output0, float *output1, PluginDef *)
{
	float 	fSlow0 = (fConst1 * fslider0);
	float 	fSlow1 = fslider1;
	float 	fSlow2 = (fConst2 * fslider2);
	float 	fSlow3 = fslider3;
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		fVec0[IOTA&65535] = fTemp0;
		float fTemp1 = (fSlow0 + fRec0[1]);
		fRec0[0] = (fTemp1 - floorf(fTemp1));
		float fTemp2 = (65536 * (fRec0[0] - floorf(fRec0[0])));
		float fTemp3 = floorf(fTemp2);
		int iTemp4 = int(fTemp3);
		float fTemp5 = (fSlow2 * (1 + (fSlow1 * ((ftbl0[((1 + iTemp4) & 65535)] * (fTemp2 - fTemp3)) + (ftbl0[(iTemp4 & 65535)] * ((1 + fTemp3) - fTemp2))))));
		int iTemp6 = int(fTemp5);
		int iTemp7 = (1 + iTemp6);
		output0[i] = (FAUSTFLOAT)(fVec0[IOTA&65535] + (fSlow3 * (((fTemp5 - iTemp6) * fVec0[(IOTA-int((int(iTemp7) & 65535)))&65535]) + ((iTemp7 - fTemp5) * fVec0[(IOTA-int((iTemp6 & 65535)))&65535]))));
		float fTemp8 = (float)input1[i];
		fVec1[IOTA&65535] = fTemp8;
		float fTemp9 = (0.25f + fRec0[0]);
		float fTemp10 = (65536 * (fTemp9 - floorf(fTemp9)));
		float fTemp11 = floorf(fTemp10);
		int iTemp12 = int(fTemp11);
		float fTemp13 = (fSlow2 * (1 + (fSlow1 * ((ftbl0[((1 + iTemp12) & 65535)] * (fTemp10 - fTemp11)) + (ftbl0[(iTemp12 & 65535)] * ((1 + fTemp11) - fTemp10))))));
		int iTemp14 = int(fTemp13);
		int iTemp15 = (1 + iTemp14);
		output1[i] = (FAUSTFLOAT)(fVec1[IOTA&65535] + (fSlow3 * (((fTemp13 - iTemp14) * fVec1[(IOTA-int((int(iTemp15) & 65535)))&65535]) + ((iTemp15 - fTemp13) * fVec1[(IOTA-int((iTemp14 & 65535)))&65535]))));
		// post processing
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
	}
}

static int register_params(const ParamReg& reg)
{
	reg.registerVar("chorus.level","","S","",&fslider3, 0.5f, 0.0f, 1.0f, 0.01f);
	reg.registerVar("chorus.delay","","S","",&fslider2, 0.02f, 0.0f, 0.2f, 0.01f);
	reg.registerVar("chorus.depth","","S","",&fslider1, 0.02f, 0.0f, 1.0f, 0.01f);
	reg.registerVar("chorus.freq","","S","",&fslider0, 3.0f, 0.0f, 1e+01f, 0.01f);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "chorus",  // id
    N_("Chorus"),  // name
    0,  // groups
    0,  // mono_audio
    compute,  // stereo_audio
    init,  // set_samplerate
    activate,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace chorus
