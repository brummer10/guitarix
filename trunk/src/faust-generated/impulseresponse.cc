// generated from file '../src/faust/impulseresponse.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

namespace impulseresponse {
static FAUSTFLOAT 	fslider0;
static int 	iConst0;
static double 	fConst1;
static FAUSTFLOAT 	fslider1;
static double 	fConst2;
static double 	fVec0[3];
static FAUSTFLOAT 	fcheckbox0;
static FAUSTFLOAT 	fslider2;
static double 	fRec0[3];
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<3; i++) fVec0[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

static void init(unsigned int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (3.141592653589793 / iConst0);
	fConst2 = (6.283185307179586 / iConst0);
	clear_state();
}

static void compute(int count, float *input0, float *output0, PluginDef *)
{
	double 	fSlow0 = exp((0 - (fConst1 * fslider0)));
	double 	fSlow1 = (2 * cos((fConst2 * fslider1)));
	int 	iSlow2 = int(max(0, min(1, fcheckbox0)));
	double 	fSlow3 = (0.5 * (fslider2 * (1 - faustpower<2>(fSlow0))));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec0[0] = ((fSlow3 * (fVec0[0] - fVec0[2])) + (fSlow0 * ((fRec0[1] * ((iSlow2)?max(-0.6, min(0.6, fVec0[0])):fSlow1)) - (fSlow0 * fRec0[2]))));
		output0[i] = (FAUSTFLOAT)(fVec0[0] + fRec0[0]);
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fVec0[2] = fVec0[1]; fVec0[1] = fVec0[0];
	}
}

static int register_params(const ParamReg& reg)
{
	reg.registerVar("IR.peak",N_(""),"S",N_("peak gain"),&fslider2, 1.0, 0.0, 1e+01, 0.2);
	static const value_pair fcheckbox0_values[] = {{"manual"},{"auto"},{0}};
	reg.registerEnumVar("IR.auto_freq",N_("auto freq"),"B",N_(""),fcheckbox0_values,&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("IR.freq",N_(""),"S",N_("frequency (Hz)"),&fslider1, 4.4e+02, 2e+01, 1.2e+04, 1e+01);
	reg.registerVar("IR.bandwidth",N_(""),"S",N_("bandwidth (Hz)"),&fslider0, 1e+02, 2e+01, 2e+04, 1e+01);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "IR",  // id
    N_("ImpulseResponse"),  // name
    0,  // groups
    compute,  // mono_audio
    0,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace impulseresponse
