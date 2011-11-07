// generated from file '../src/faust/autowah.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

namespace autowah {
static int 	IOTA;
static int 	iVec0[1024];
static int 	iRec2[2];
FAUSTFLOAT 	fslider0;
FAUSTFLOAT	*fslider0_;
#define fslider0 (*fslider0_)
static double 	fRec1[2];
FAUSTFLOAT 	fslider1;
FAUSTFLOAT	*fslider1_;
#define fslider1 (*fslider1_)
FAUSTFLOAT 	fslider2;
FAUSTFLOAT	*fslider2_;
#define fslider2 (*fslider2_)
static int 	iConst0;
static double 	fConst1;
static double 	fConst2;
static double 	fRec3[2];
static double 	fRec4[2];
static double 	fRec0[3];
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<1024; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) iRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

static void init(unsigned int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (2827.4333882308138 / iConst0);
	fConst2 = (1413.7166941154069 / iConst0);
	clear_state();
}

static void compute(int count, float *input0, float *output0, PluginDef *)
{
	double 	fSlow0 = (2.384185791015625e-10 * fslider0);
	double 	fSlow1 = fslider2;
	double 	fSlow2 = (0.01 * (fSlow1 * fslider1));
	double 	fSlow3 = (1 - (0.01 * fSlow1));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		int iTemp1 = abs(int((4194304 * fTemp0)));
		iVec0[IOTA&1023] = iTemp1;
		iRec2[0] = ((iVec0[IOTA&1023] + iRec2[1]) - iVec0[(IOTA-1000)&1023]);
		double fTemp2 = min(1, max(0, (fSlow0 * double(iRec2[0]))));
		fRec1[0] = ((0.0001000000000000001 * pow(4.0,fTemp2)) + (0.999 * fRec1[1]));
		double fTemp3 = pow(2.0,(2.3 * fTemp2));
		double fTemp4 = (1 - (fConst2 * (fTemp3 / pow(2.0,(1.0 + (2.0 * (1.0 - fTemp2)))))));
		fRec3[0] = ((0.0010000000000000009 * (0 - (2.0 * (fTemp4 * cos((fConst1 * fTemp3)))))) + (0.999 * fRec3[1]));
		fRec4[0] = ((0.0010000000000000009 * faustpower<2>(fTemp4)) + (0.999 * fRec4[1]));
		fRec0[0] = (0 - (((fRec4[0] * fRec0[2]) + (fRec3[0] * fRec0[1])) - (fSlow2 * (fTemp0 * fRec1[0]))));
		output0[i] = (FAUSTFLOAT)((fRec0[0] + (fSlow3 * fTemp0)) - fRec0[1]);
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec1[1] = fRec1[0];
		iRec2[1] = iRec2[0];
		IOTA = IOTA+1;
	}
}

static int register_params(const ParamReg& reg)
{
#undef fslider2
	fslider2_ = reg.registerVar("crybaby.wet_dry",N_("wet/dry"),"SA",N_(""),&fslider2, 1e+02, 0.0, 1e+02, 1.0);
#undef fslider1
	fslider1_ = reg.registerVar("crybaby.level",N_(""),"SA",N_(""),&fslider1, 0.1, 0.0, 1.0, 0.01);
#undef fslider0
	fslider0_ = reg.registerVar("crybaby.wah",N_(""),"SA",N_(""),&fslider0, 0.0, 0.0, 1.0, 0.01);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "auto",  // id
    N_("auto"),  // name
    0,  // groups
    compute,  // mono_audio
    0,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace autowah
