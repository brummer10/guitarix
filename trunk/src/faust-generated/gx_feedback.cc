// generated from file '../src/faust/gx_feedback.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

namespace gx_feedback {
static FAUSTFLOAT 	fslider0;
static FAUSTFLOAT 	fslider1;
static double 	fRec0[6];
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<6; i++) fRec0[i] = 0;
}

static void init(int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	clear_state();
}

static void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.01 * fslider0);
	double 	fSlow1 = (1 - fSlow0);
	double 	fSlow2 = fslider1;
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec0[0] = ((fSlow0 * fTemp0) - (fSlow2 * fRec0[5]));
		output0[i] = (FAUSTFLOAT)(fRec0[0] + (fSlow1 * fTemp0));
		// post processing
		for (int i=5; i>0; i--) fRec0[i] = fRec0[i-1];
	}
}

static int register_params(const ParamReg& reg)
{
	reg.registerVar("feedback.feedback","","S","",&fslider1, 0.0, -1.0, 1.0, 0.01);
	reg.registerVar("feedback.wet_dry","","S","",&fslider0, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "feedback",  // id
    N_("Feedback"),  // name
    0,  // groups
    compute,  // mono_audio
    0,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace gx_feedback
