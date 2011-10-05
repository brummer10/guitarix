// generated from file '../src/faust/moog.dsp' by dsp2cc:
// Code generated with Faust 0.9.30 (http://faust.grame.fr)

namespace moog {
static int 	iVec0[2];
static FAUSTFLOAT 	fslider0;
static double 	fRec1[2];
static double 	fConst0;
static FAUSTFLOAT 	fslider1;
static double 	fRec6[2];
static double 	fRec5[2];
static double 	fRec4[2];
static double 	fRec3[2];
static double 	fRec2[2];
static double 	fRec0[2];
static double 	fRec11[2];
static double 	fRec10[2];
static double 	fRec9[2];
static double 	fRec8[2];
static double 	fRec7[2];
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
}

static void init(int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (6.283185307179586 / fSamplingFreq);
	clear_state();
}

static void compute(int count, float *input0, float *input1, float *output0, float *output1)
{
	double 	fSlow0 = (0.0010000000000000009 * fslider0);
	double 	fSlow1 = (0 - fslider1);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec1[0] = (fSlow0 + (0.999 * fRec1[1]));
		double fTemp0 = (fConst0 * fRec1[0]);
		double fTemp1 = faustpower<4>(fTemp0);
		double fTemp2 = (1.0 - fTemp0);
		fRec6[0] = ((1e-20 * (1 - iVec0[1])) - fRec6[1]);
		fRec5[0] = ((((double)input0[i] + fRec6[0]) + (fSlow1 * fRec0[1])) + (fTemp2 * fRec5[1]));
		fRec4[0] = (fRec5[0] + (fTemp2 * fRec4[1]));
		fRec3[0] = (fRec4[0] + (fTemp2 * fRec3[1]));
		fRec2[0] = (fRec3[0] + (fTemp2 * fRec2[1]));
		fRec0[0] = (fRec2[0] * fTemp1);
		output0[i] = (FAUSTFLOAT)fRec0[0];
		fRec11[0] = ((((double)input1[i] + fRec6[0]) + (fSlow1 * fRec7[1])) + (fTemp2 * fRec11[1]));
		fRec10[0] = (fRec11[0] + (fTemp2 * fRec10[1]));
		fRec9[0] = (fRec10[0] + (fTemp2 * fRec9[1]));
		fRec8[0] = (fRec9[0] + (fTemp2 * fRec8[1]));
		fRec7[0] = (fRec8[0] * fTemp1);
		output1[i] = (FAUSTFLOAT)fRec7[0];
		// post processing
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec1[1] = fRec1[0];
		iVec0[1] = iVec0[0];
	}
}

static int register_params(const ParamReg& reg)
{
	reg.registerVar("moog.Q","","S","",&fslider1, 1.0, 0.0, 4.0, 0.1);
	reg.registerVar("moog.fr","","S","",&fslider0, 3e+03, 4.4e+02, 6e+03, 1e+01);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "moog",  // id
    N_("Moog Filter"),  // name
    0,  // groups
    0,  // mono_audio
    compute,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace moog
