// generated from file '../src/faust/biquad.dsp' by dsp2cc:
// Code generated with Faust 0.9.30 (http://faust.grame.fr)

namespace biquad {
static FAUSTFLOAT 	fslider0;
static double 	fConst0;
static double 	fRec0[3];
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

static void init(int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (6.283185307179586 / fSamplingFreq);
	clear_state();
}

static void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = log((fConst0 * fslider0));
	double 	fSlow1 = (0 - (1.8442 * cos(exp((0.07238887 + (fSlow0 * (1.31282248 + (fSlow0 * (0.43359433 + (fSlow0 * (0.27547621 + (fSlow0 * (0.06446806 + (0.00506158 * fSlow0))))))))))))));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((double)input0[i] - ((0.8502684100000001 * fRec0[2]) + (fSlow1 * fRec0[1])));
		output0[i] = (FAUSTFLOAT)(0.31622776601683794 * (fRec0[0] - (1.059 * fRec0[1])));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
	}
}

static int register_params(const ParamReg& reg)
{
	reg.registerVar("biquad.Freq","","S","",&fslider0, 1.2e+03, 3e+02, 3e+03, 5.0);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "biquad",  // id
    N_("BiQuad Filter"),  // name
    0,  // groups
    compute,  // mono_audio
    0,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace biquad
