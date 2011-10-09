// generated from file '../src/faust/softclip.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

namespace softclip {
static FAUSTFLOAT 	fslider0;
static int	fSamplingFreq;

static void init(int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
}

static void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.88 * (2 - fslider0));
	double 	fSlow1 = (0 - fSlow0);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		double fTemp1 = max(fSlow1, min(fSlow0, fTemp0));
		output0[i] = (FAUSTFLOAT)(fTemp1 + (0.33 * (fTemp0 - max(fSlow1, min(fSlow0, fTemp1)))));
	}
}

static int register_params(const ParamReg& reg)
{
	reg.registerVar("amp.fuzz","","S","",&fslider0, 0.0, 0.0, 1.99, 0.01);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "amp.clip",  // id
    "?softclip",  // name
    0,  // groups
    compute,  // mono_audio
    0,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    0,  // clear_state
};

} // end namespace softclip
