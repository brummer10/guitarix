// generated from file '../src/faust/crybaby.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

namespace crybaby {
FAUSTFLOAT 	fslider0;
FAUSTFLOAT	*fslider0_;
#define fslider0 (*fslider0_)
static int 	iConst0;
static double 	fConst1;
static double 	fConst2;
static double 	fRec1[2];
static double 	fRec2[2];
static double 	fRec3[2];
FAUSTFLOAT 	fslider1;
FAUSTFLOAT	*fslider1_;
#define fslider1 (*fslider1_)
FAUSTFLOAT 	fslider2;
FAUSTFLOAT	*fslider2_;
#define fslider2 (*fslider2_)
static double 	fRec0[3];
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

static void init(unsigned int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1413.7166941154069 / iConst0);
	fConst2 = (2827.4333882308138 / iConst0);
	clear_state();
}

static void compute(int count, float *input0, float *output0, PluginDef *)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = pow(2.0,(2.3 * fSlow0));
	double 	fSlow2 = (1 - (fConst1 * (fSlow1 / pow(2.0,(1.0 + (2.0 * (1.0 - fSlow0)))))));
	double 	fSlow3 = (0.0010000000000000009 * (0 - (2.0 * (cos((fConst2 * fSlow1)) * fSlow2))));
	double 	fSlow4 = (0.0010000000000000009 * faustpower<2>(fSlow2));
	double 	fSlow5 = (0.0001000000000000001 * pow(4.0,fSlow0));
	double 	fSlow6 = fslider2;
	double 	fSlow7 = (0.01 * (fSlow6 * fslider1));
	double 	fSlow8 = (1 - (0.01 * fSlow6));
	for (int i=0; i<count; i++) {
		fRec1[0] = (fSlow3 + (0.999 * fRec1[1]));
		fRec2[0] = (fSlow4 + (0.999 * fRec2[1]));
		fRec3[0] = (fSlow5 + (0.999 * fRec3[1]));
		double fTemp0 = (double)input0[i];
		fRec0[0] = ((fSlow7 * (fTemp0 * fRec3[0])) - (0.996 * ((fRec2[0] * fRec0[2]) + (fRec1[0] * fRec0[1]))));
		output0[i] = (FAUSTFLOAT)((fRec0[0] + (fSlow8 * fTemp0)) - (0.996 * fRec0[1]));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
	}
}

static int register_params(const ParamReg& reg)
{
#undef fslider2
	fslider2_ = reg.registerVar("crybaby.wet_dry","wet/dry","SA","",&fslider2, 1e+02, 0.0, 1e+02, 1.0);
#undef fslider1
	fslider1_ = reg.registerVar("crybaby.level","","SA","",&fslider1, 0.1, 0.0, 1.0, 0.01);
#undef fslider0
	fslider0_ = reg.registerVar("crybaby.wah","","SA","",&fslider0, 0.0, 0.0, 1.0, 0.01);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "manual",  // id
    N_("manual"),  // name
    0,  // groups
    compute,  // mono_audio
    0,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace crybaby
