// generated from file '../src/faust/bassbooster.dsp' by dsp2cc:
// Code generated with Faust 0.9.30 (http://faust.grame.fr)

namespace bassbooster {
static double 	fConst0;
static double 	fConst1;
static double 	fConst2;
static double 	fConst3;
static double 	fConst4;
static double 	fRec0[3];
static FAUSTFLOAT 	fslider0;
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

static void init(int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	fConst0 = tan((376.99111843077515 / fSamplingFreq));
	fConst1 = faustpower<2>(fConst0);
	fConst2 = (2 * (fConst1 - 1));
	fConst3 = (1 + (fConst0 * (fConst0 - 1.4142135623730951)));
	fConst4 = (1.0 / (1 + (fConst0 * (1.4142135623730951 + fConst0))));
	clear_state();
}

static void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = pow(10,(0.05 * fslider0));
	double 	fSlow1 = sqrt((2 * fSlow0));
	double 	fSlow2 = (fConst0 * fSlow0);
	double 	fSlow3 = (1 + (fConst0 * (fSlow2 - fSlow1)));
	double 	fSlow4 = (2 * ((fConst1 * fSlow0) - 1));
	double 	fSlow5 = (1 + (fConst0 * (fSlow2 + fSlow1)));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((double)input0[i] - (fConst4 * ((fConst3 * fRec0[2]) + (fConst2 * fRec0[1]))));
		output0[i] = (FAUSTFLOAT)(fConst4 * (((fSlow5 * fRec0[0]) + (fSlow4 * fRec0[1])) + (fSlow3 * fRec0[2])));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
	}
}

static int register_params(const ParamReg& reg)
{
	reg.registerVar("bassbooster.Level","","S","",&fslider0, 1e+01, 0.5, 2e+01, 0.5);
	return 0;
}

static const char* groups[] = {
	".bassbooster", N_("Bassbooster"),
	0
	};

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "amp.bass_boost",  // id
    N_("Bassbooster"),  // name
    groups,  // groups
    compute,  // mono_audio
    0,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace bassbooster
