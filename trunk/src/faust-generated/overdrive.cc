// generated from file '../src/faust/overdrive.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

namespace overdrive {
static FAUSTFLOAT 	fslider0;
static FAUSTFLOAT 	fslider1;
static double 	fRec0[2];
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

static void init(unsigned int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	clear_state();
}

static void compute(int count, float *input0, float *output0, PluginDef *)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (0.0001 * faustpower<2>(fSlow0));
	double 	fSlow2 = (0.01 * fSlow0);
	double 	fSlow3 = fslider1;
	double 	fSlow4 = (fSlow3 - 1);
	double 	fSlow5 = (0.0010000000000000009 * pow(10,(0.05 * (0 - (0.5 * fSlow3)))));
	double 	fSlow6 = (1 - fSlow2);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		double fTemp1 = fabs((fSlow2 * fTemp0));
		fRec0[0] = (fSlow5 + (0.999 * fRec0[1]));
		output0[i] = (FAUSTFLOAT)(fTemp0 * (fSlow6 + (fSlow2 * ((fRec0[0] * (fSlow3 + fTemp1)) / (1 + ((fSlow4 * fTemp1) + (fSlow1 * faustpower<2>(fTemp0))))))));
		// post processing
		fRec0[1] = fRec0[0];
	}
}

static int register_params(const ParamReg& reg)
{
	reg.registerVar("overdrive.drive","","S","",&fslider1, 1.0, 1.0, 2e+01, 0.1);
	reg.registerVar("overdrive.wet_dry","wet/dry","S","percentage of processed signal in output signal",&fslider0, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "overdrive",  // id
    N_("Overdrive"),  // name
    0,  // groups
    compute,  // mono_audio
    0,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace overdrive
