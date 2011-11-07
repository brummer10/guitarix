// generated from file '../src/faust/freeverb.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

namespace freeverb {
static FAUSTFLOAT 	fslider0;
static FAUSTFLOAT 	fslider1;
static double 	fRec9[2];
static FAUSTFLOAT 	fslider2;
static int 	IOTA;
static double 	fVec0[2048];
static double 	fRec8[2];
static double 	fRec11[2];
static double 	fVec1[2048];
static double 	fRec10[2];
static double 	fRec13[2];
static double 	fVec2[2048];
static double 	fRec12[2];
static double 	fRec15[2];
static double 	fVec3[2048];
static double 	fRec14[2];
static double 	fRec17[2];
static double 	fVec4[2048];
static double 	fRec16[2];
static double 	fRec19[2];
static double 	fVec5[2048];
static double 	fRec18[2];
static double 	fRec21[2];
static double 	fVec6[2048];
static double 	fRec20[2];
static double 	fRec23[2];
static double 	fVec7[2048];
static double 	fRec22[2];
static double 	fVec8[1024];
static double 	fRec6[2];
static double 	fVec9[512];
static double 	fRec4[2];
static double 	fVec10[512];
static double 	fRec2[2];
static double 	fVec11[256];
static double 	fRec0[2];
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2048; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2048; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2048; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2048; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2048; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2048; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2048; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2048; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<1024; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<512; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<512; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<256; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

static void init(unsigned int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	clear_state();
}

static void compute(int count, float *input0, float *output0, PluginDef *)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (1 - (0.01 * fSlow0));
	double 	fSlow2 = (fSlow1 + (fSlow0 * (0.00015 + (0.01 * fSlow1))));
	double 	fSlow3 = fslider1;
	double 	fSlow4 = (1 - fSlow3);
	double 	fSlow5 = (0.7 + (0.28 * fslider2));
	double 	fSlow6 = (0.00015 * fSlow0);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec9[0] = ((fSlow4 * fRec8[1]) + (fSlow3 * fRec9[1]));
		double fTemp1 = (fSlow6 * fTemp0);
		fVec0[IOTA&2047] = (fTemp1 + (fSlow5 * fRec9[0]));
		fRec8[0] = fVec0[(IOTA-1640)&2047];
		fRec11[0] = ((fSlow4 * fRec10[1]) + (fSlow3 * fRec11[1]));
		fVec1[IOTA&2047] = (fTemp1 + (fSlow5 * fRec11[0]));
		fRec10[0] = fVec1[(IOTA-1580)&2047];
		fRec13[0] = ((fSlow4 * fRec12[1]) + (fSlow3 * fRec13[1]));
		fVec2[IOTA&2047] = (fTemp1 + (fSlow5 * fRec13[0]));
		fRec12[0] = fVec2[(IOTA-1514)&2047];
		fRec15[0] = ((fSlow4 * fRec14[1]) + (fSlow3 * fRec15[1]));
		fVec3[IOTA&2047] = (fTemp1 + (fSlow5 * fRec15[0]));
		fRec14[0] = fVec3[(IOTA-1445)&2047];
		fRec17[0] = ((fSlow4 * fRec16[1]) + (fSlow3 * fRec17[1]));
		fVec4[IOTA&2047] = (fTemp1 + (fSlow5 * fRec17[0]));
		fRec16[0] = fVec4[(IOTA-1379)&2047];
		fRec19[0] = ((fSlow4 * fRec18[1]) + (fSlow3 * fRec19[1]));
		fVec5[IOTA&2047] = (fTemp1 + (fSlow5 * fRec19[0]));
		fRec18[0] = fVec5[(IOTA-1300)&2047];
		fRec21[0] = ((fSlow4 * fRec20[1]) + (fSlow3 * fRec21[1]));
		fVec6[IOTA&2047] = (fTemp1 + (fSlow5 * fRec21[0]));
		fRec20[0] = fVec6[(IOTA-1211)&2047];
		fRec23[0] = ((fSlow4 * fRec22[1]) + (fSlow3 * fRec23[1]));
		fVec7[IOTA&2047] = (fTemp1 + (fSlow5 * fRec23[0]));
		fRec22[0] = fVec7[(IOTA-1139)&2047];
		double fTemp2 = (((((((fRec22[0] + fRec20[0]) + fRec18[0]) + fRec16[0]) + fRec14[0]) + fRec12[0]) + fRec10[0]) + fRec8[0]);
		fVec8[IOTA&1023] = (fTemp2 + (0.5 * fRec6[1]));
		fRec6[0] = fVec8[(IOTA-579)&1023];
		double 	fRec7 = (0 - (fTemp2 - fRec6[1]));
		fVec9[IOTA&511] = (fRec7 + (0.5 * fRec4[1]));
		fRec4[0] = fVec9[(IOTA-464)&511];
		double 	fRec5 = (fRec4[1] - fRec7);
		fVec10[IOTA&511] = (fRec5 + (0.5 * fRec2[1]));
		fRec2[0] = fVec10[(IOTA-364)&511];
		double 	fRec3 = (fRec2[1] - fRec5);
		fVec11[IOTA&255] = (fRec3 + (0.5 * fRec0[1]));
		fRec0[0] = fVec11[(IOTA-248)&255];
		double 	fRec1 = (fRec0[1] - fRec3);
		output0[i] = (FAUSTFLOAT)(fRec1 + (fSlow2 * fTemp0));
		// post processing
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fRec6[1] = fRec6[0];
		fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec8[1] = fRec8[0];
		IOTA = IOTA+1;
		fRec9[1] = fRec9[0];
	}
}

static int register_params(const ParamReg& reg)
{
	reg.registerVar("freeverb.RoomSize",N_(""),"S",N_(""),&fslider2, 0.5, 0.0, 1.0, 0.025);
	reg.registerVar("freeverb.damp",N_(""),"S",N_(""),&fslider1, 0.5, 0.0, 1.0, 0.025);
	reg.registerVar("freeverb.wet_dry",N_("wet/dry"),"S",N_(""),&fslider0, 5e+01, 0.0, 1e+02, 1.0);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "freeverb",  // id
    N_("Freeverb"),  // name
    0,  // groups
    compute,  // mono_audio
    0,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace freeverb
