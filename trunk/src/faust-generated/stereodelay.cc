// generated from file '../src/faust/stereodelay.dsp' by dsp2cc:
// Code generated with Faust 0.9.30 (http://faust.grame.fr)

namespace stereodelay {
static int 	IOTA;
static float *fVec0;
static FAUSTFLOAT 	fslider0;
static float 	fConst0;
static int 	iVec1[2];
static FAUSTFLOAT 	fslider1;
static float 	fConst1;
static float 	fRec0[2];
static float 	fRec1[2];
static FAUSTFLOAT 	fcheckbox0;
static FAUSTFLOAT 	fslider2;
static float 	fRec2[2];
static float *fVec2;
static FAUSTFLOAT 	fslider3;
static FAUSTFLOAT 	fslider4;
static float 	fRec3[2];
static bool mem_allocated = false;
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<262144; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) iVec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<262144; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
}

static void init(int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	fConst0 = (0.001f * fSamplingFreq);
	fConst1 = (6.283185307179586f / fSamplingFreq);
}

static void mem_alloc()
{
	if (!fVec0) fVec0 = new float[262144];
	if (!fVec2) fVec2 = new float[262144];
	mem_allocated = true;
}

static void mem_free()
{
	mem_allocated = false;
	if (fVec0) { delete fVec0; fVec0 = 0; }
	if (fVec2) { delete fVec2; fVec2 = 0; }
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

static void compute(int count, float *input0, float *input1, float *output0, float *output1)
{
	float 	fSlow0 = (fConst0 * fslider0);
	int 	iSlow1 = int(fSlow0);
	int 	iSlow2 = int((iSlow1 & 262143));
	int 	iSlow3 = (1 + iSlow1);
	float 	fSlow4 = (iSlow3 - fSlow0);
	int 	iSlow5 = int((int(iSlow3) & 262143));
	float 	fSlow6 = (fSlow0 - iSlow1);
	float 	fSlow7 = (fConst1 * fslider1);
	float 	fSlow8 = sinf(fSlow7);
	float 	fSlow9 = cosf(fSlow7);
	float 	fSlow10 = (0 - fSlow8);
	float 	fSlow11 = fcheckbox0;
	float 	fSlow12 = (0.0010000000000000009f * powf(10,(0.05f * fslider2)));
	float 	fSlow13 = (fConst0 * fslider3);
	int 	iSlow14 = int(fSlow13);
	int 	iSlow15 = int((iSlow14 & 262143));
	int 	iSlow16 = (1 + iSlow14);
	float 	fSlow17 = (iSlow16 - fSlow13);
	int 	iSlow18 = int((int(iSlow16) & 262143));
	float 	fSlow19 = (fSlow13 - iSlow14);
	float 	fSlow20 = (0.0010000000000000009f * powf(10,(0.05f * fslider4)));
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		fVec0[IOTA&262143] = fTemp0;
		iVec1[0] = 1;
		fRec0[0] = ((fSlow9 * fRec0[1]) + (fSlow8 * fRec1[1]));
		fRec1[0] = ((1 + ((fSlow10 * fRec0[1]) + (fSlow9 * fRec1[1]))) - iVec1[1]);
		float fTemp1 = (fSlow11 * fRec0[0]);
		fRec2[0] = (fSlow12 + (0.999f * fRec2[1]));
		output0[i] = (FAUSTFLOAT)(fVec0[IOTA&262143] + ((fRec2[0] * (1 + fTemp1)) * ((fSlow6 * fVec0[(IOTA-iSlow5)&262143]) + (fSlow4 * fVec0[(IOTA-iSlow2)&262143]))));
		float fTemp2 = (float)input1[i];
		fVec2[IOTA&262143] = fTemp2;
		fRec3[0] = (fSlow20 + (0.999f * fRec3[1]));
		output1[i] = (FAUSTFLOAT)(fVec2[IOTA&262143] + ((fRec3[0] * (1 - fTemp1)) * ((fSlow19 * fVec2[(IOTA-iSlow18)&262143]) + (fSlow17 * fVec2[(IOTA-iSlow15)&262143]))));
		// post processing
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		iVec1[1] = iVec1[0];
		IOTA = IOTA+1;
	}
}

static int register_params(const ParamReg& reg)
{
	static const value_pair fcheckbox0_values[] = {{"linear"},{"pingpong"},{0}};
	reg.registerEnumVar("stereodelay.invert","","B","",fcheckbox0_values,&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("stereodelay.r_gain","","S","",&fslider4, 0.0f, -2e+01f, 2e+01f, 0.1f);
	reg.registerVar("stereodelay.r_delay","","S","",&fslider3, 0.0f, 0.0f, 5e+03f, 1e+01f);
	reg.registerVar("stereodelay.l_gain","","S","",&fslider2, 0.0f, -2e+01f, 2e+01f, 0.1f);
	reg.registerVar("stereodelay.LFO freq","","S","",&fslider1, 0.2f, 0.0f, 5.0f, 0.01f);
	reg.registerVar("stereodelay.l_delay","","S","",&fslider0, 0.0f, 0.0f, 5e+03f, 1e+01f);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "stereodelay",  // id
    N_("Stereo Delay"),  // name
    0,  // groups
    0,  // mono_audio
    compute,  // stereo_audio
    init,  // set_samplerate
    activate,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace stereodelay
