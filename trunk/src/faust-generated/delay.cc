// generated from file '../src/faust/delay.dsp' by dsp2cc:
// Code generated with Faust 0.9.30 (http://faust.grame.fr)

namespace delay {
static int 	IOTA;
static float *fVec0;
static FAUSTFLOAT 	fslider0;
static float 	fConst0;
static FAUSTFLOAT 	fslider1;
static float 	fRec0[2];
static bool mem_allocated = false;
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<262144; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

static void init(int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	fConst0 = (0.001f * fSamplingFreq);
}

static void mem_alloc()
{
	if (!fVec0) fVec0 = new float[262144];
	mem_allocated = true;
}

static void mem_free()
{
	mem_allocated = false;
	if (fVec0) { delete fVec0; fVec0 = 0; }
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

static void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = (fConst0 * fslider0);
	int 	iSlow1 = int(fSlow0);
	int 	iSlow2 = int((iSlow1 & 262143));
	int 	iSlow3 = (1 + iSlow1);
	float 	fSlow4 = (iSlow3 - fSlow0);
	int 	iSlow5 = int((int(iSlow3) & 262143));
	float 	fSlow6 = (fSlow0 - iSlow1);
	float 	fSlow7 = (0.0010000000000000009f * powf(10,(0.05f * fslider1)));
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		fVec0[IOTA&262143] = fTemp0;
		fRec0[0] = (fSlow7 + (0.999f * fRec0[1]));
		output0[i] = (FAUSTFLOAT)(fVec0[IOTA&262143] + (fRec0[0] * ((fSlow6 * fVec0[(IOTA-iSlow5)&262143]) + (fSlow4 * fVec0[(IOTA-iSlow2)&262143]))));
		// post processing
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
	}
}

static int register_params(const ParamReg& reg)
{
	reg.registerVar("delay.gain","","S","",&fslider1, 0.0f, -2e+01f, 2e+01f, 0.1f);
	reg.registerVar("delay.delay","","S","",&fslider0, 0.0f, 0.0f, 5e+03f, 1e+01f);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "delay",  // id
    N_("Delay"),  // name
    0,  // groups
    compute,  // mono_audio
    0,  // stereo_audio
    init,  // set_samplerate
    activate,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace delay
