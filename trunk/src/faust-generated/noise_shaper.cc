// generated from file '../src/faust/noise_shaper.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

namespace noise_shaper {
static int 	iConst0;
static double 	fConst1;
static double 	fConst2;
static double 	fRec0[2];
static FAUSTFLOAT 	fslider0;
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

static void init(unsigned int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = exp((0 - (2e+02 / iConst0)));
	fConst2 = exp((0 - (0.1 / iConst0)));
	clear_state();
}

static void compute(int count, float *input0, float *output0, PluginDef *)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (5 * fSlow0);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		double fTemp1 = max(1, fabs(fTemp0));
		double fTemp2 = ((fConst2 * (fRec0[1] >= fTemp1)) + (fConst1 * (fRec0[1] < fTemp1)));
		fRec0[0] = ((fTemp1 * (0 - (fTemp2 - 1))) + (fRec0[1] * fTemp2));
		double fTemp3 = max(0, (fSlow1 + (20 * log10(fRec0[0]))));
		double fTemp4 = (0.5 * min(1, max(0, (0.09522902580706599 * fTemp3))));
		output0[i] = (FAUSTFLOAT)(fTemp0 * pow(10,(0.05 * (fSlow0 + ((fTemp3 * (0 - fTemp4)) / (1 + fTemp4))))));
		// post processing
		fRec0[1] = fRec0[0];
	}
}

static int register_params(const ParamReg& reg)
{
	reg.registerVar("shaper.sharper",N_("sharper"),"S",N_(""),&fslider0, 1.0, 1.0, 1e+01, 1.0);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "shaper",  // id
    N_("Shaper"),  // name
    0,  // groups
    compute,  // mono_audio
    0,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace noise_shaper
