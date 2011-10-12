// generated from file '../src/faust/phaser_mono.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

namespace phaser_mono {
static int 	iVec0[2];
static FAUSTFLOAT 	fslider0;
static int 	iConst0;
static double 	fConst1;
static double 	fRec1[2];
static double 	fRec2[2];
static double 	fConst2;
static FAUSTFLOAT 	fslider1;
static FAUSTFLOAT 	fslider2;
static double 	fConst3;
static double 	fConst4;
static double 	fConst5;
static double 	fConst6;
static double 	fRec6[3];
static double 	fConst7;
static double 	fRec5[3];
static double 	fConst8;
static double 	fRec4[3];
static double 	fRec3[3];
static double 	fRec0[2];
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

static void init(unsigned int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (6.283185307179586 / iConst0);
	fConst2 = (16.0 / iConst0);
	fConst3 = (2.0 / iConst0);
	fConst4 = exp((0 - (3141.592653589793 / iConst0)));
	fConst5 = (0 - (2 * fConst4));
	fConst6 = faustpower<2>(fConst4);
	fConst7 = (4.0 / iConst0);
	fConst8 = (8.0 / iConst0);
	clear_state();
}

static void compute(int count, float *input0, float *output0, PluginDef *)
{
	double 	fSlow0 = (fConst1 * fslider0);
	double 	fSlow1 = sin(fSlow0);
	double 	fSlow2 = cos(fSlow0);
	double 	fSlow3 = (0 - fSlow1);
	double 	fSlow4 = fslider2;
	double 	fSlow5 = (0.01 * (fSlow4 * pow(10,(0.05 * fslider1))));
	double 	fSlow6 = (1 - (0.01 * fSlow4));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec1[0] = ((fSlow2 * fRec1[1]) + (fSlow1 * fRec2[1]));
		fRec2[0] = ((1 + ((fSlow3 * fRec1[1]) + (fSlow2 * fRec2[1]))) - iVec0[1]);
		double fTemp0 = (628.3185307179587 + (2199.1148575128555 * (1 - fRec1[0])));
		double fTemp1 = (double)input0[i];
		double fTemp2 = (fRec6[1] * cos((fConst3 * fTemp0)));
		fRec6[0] = (0 - (((fConst6 * fRec6[2]) + (fConst5 * fTemp2)) - ((fSlow5 * fTemp1) + (0.5 * fRec0[1]))));
		double fTemp3 = (fRec5[1] * cos((fConst7 * fTemp0)));
		fRec5[0] = ((fConst5 * (fTemp2 - fTemp3)) + (fRec6[2] + (fConst6 * (fRec6[0] - fRec5[2]))));
		double fTemp4 = (fRec4[1] * cos((fConst8 * fTemp0)));
		fRec4[0] = ((fConst5 * (fTemp3 - fTemp4)) + (fRec5[2] + (fConst6 * (fRec5[0] - fRec4[2]))));
		double fTemp5 = (fRec3[1] * cos((fConst2 * fTemp0)));
		fRec3[0] = ((fConst5 * (fTemp4 - fTemp5)) + (fRec4[2] + (fConst6 * (fRec4[0] - fRec3[2]))));
		fRec0[0] = ((fConst6 * fRec3[0]) + (fRec3[2] + (fConst5 * fTemp5)));
		output0[i] = (FAUSTFLOAT)((fSlow6 * fTemp1) - fRec0[0]);
		// post processing
		fRec0[1] = fRec0[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		iVec0[1] = iVec0[0];
	}
}

static int register_params(const ParamReg& reg)
{
	reg.registerVar("phaser_mono.wet_dry","wet/dry","S","percentage of processed signal in output signal",&fslider2, 1e+02, 0.0, 1e+02, 1.0);
	reg.registerVar("phaser_mono.level","","S","",&fslider1, 0.0, -6e+01, 1e+01, 0.1);
	reg.registerVar("phaser_mono.Speed","","S","",&fslider0, 0.5, 0.0, 1e+01, 0.01);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "phaser_mono",  // id
    N_("Phaser Mono"),  // name
    0,  // groups
    compute,  // mono_audio
    0,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace phaser_mono
