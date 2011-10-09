// generated from file '../src/faust/phaser.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

namespace phaser {
static FAUSTFLOAT 	fslider0;
static FAUSTFLOAT 	fcheckbox0;
static int 	iVec0[2];
static FAUSTFLOAT 	fslider1;
static FAUSTFLOAT 	fcheckbox1;
static FAUSTFLOAT 	fslider2;
static int 	iConst0;
static double 	fConst1;
static double 	fRec1[2];
static double 	fRec2[2];
static FAUSTFLOAT 	fslider3;
static FAUSTFLOAT 	fslider4;
static FAUSTFLOAT 	fslider5;
static double 	fConst2;
static FAUSTFLOAT 	fslider6;
static FAUSTFLOAT 	fslider7;
static double 	fRec6[3];
static double 	fRec5[3];
static double 	fRec4[3];
static double 	fRec3[3];
static double 	fRec0[2];
static double 	fRec11[3];
static double 	fRec10[3];
static double 	fRec9[3];
static double 	fRec8[3];
static double 	fRec7[2];
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
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
}

static void init(int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (6.283185307179586 / iConst0);
	fConst2 = (1.0 / iConst0);
	clear_state();
}

static void compute(int count, float *input0, float *input1, float *output0, float *output1)
{
	double 	fSlow0 = (0.5 * ((int(fcheckbox0))?2:fslider0));
	double 	fSlow1 = (1 - fSlow0);
	double 	fSlow2 = pow(10,(0.05 * fslider1));
	double 	fSlow3 = ((int(fcheckbox1))?(0 - fSlow0):fSlow0);
	double 	fSlow4 = (fConst1 * fslider2);
	double 	fSlow5 = sin(fSlow4);
	double 	fSlow6 = cos(fSlow4);
	double 	fSlow7 = (0 - fSlow5);
	double 	fSlow8 = fslider3;
	double 	fSlow9 = (6.283185307179586 * fSlow8);
	double 	fSlow10 = (0.5 * ((6.283185307179586 * max(fSlow8, fslider4)) - fSlow9));
	double 	fSlow11 = fslider5;
	double 	fSlow12 = (fConst2 * faustpower<4>(fSlow11));
	double 	fSlow13 = fslider6;
	double 	fSlow14 = (fConst2 * fSlow11);
	double 	fSlow15 = exp((fConst2 * (0 - (3.141592653589793 * fslider7))));
	double 	fSlow16 = (0 - (2 * fSlow15));
	double 	fSlow17 = faustpower<2>(fSlow15);
	double 	fSlow18 = (fConst2 * faustpower<2>(fSlow11));
	double 	fSlow19 = (fConst2 * faustpower<3>(fSlow11));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		double fTemp0 = (double)input0[i];
		fRec1[0] = ((fSlow6 * fRec1[1]) + (fSlow5 * fRec2[1]));
		fRec2[0] = ((1 + ((fSlow7 * fRec1[1]) + (fSlow6 * fRec2[1]))) - iVec0[1]);
		double fTemp1 = (fSlow9 + (fSlow10 * (1 - fRec1[0])));
		double fTemp2 = (fRec6[1] * cos((fSlow14 * fTemp1)));
		fRec6[0] = (0 - (((fSlow17 * fRec6[2]) + (fSlow16 * fTemp2)) - ((fSlow2 * fTemp0) + (fSlow13 * fRec0[1]))));
		double fTemp3 = (fRec5[1] * cos((fSlow18 * fTemp1)));
		fRec5[0] = ((fSlow16 * (fTemp2 - fTemp3)) + (fRec6[2] + (fSlow17 * (fRec6[0] - fRec5[2]))));
		double fTemp4 = (fRec4[1] * cos((fSlow19 * fTemp1)));
		fRec4[0] = ((fSlow16 * (fTemp3 - fTemp4)) + (fRec5[2] + (fSlow17 * (fRec5[0] - fRec4[2]))));
		double fTemp5 = (fRec3[1] * cos((fSlow12 * fTemp1)));
		fRec3[0] = ((fSlow16 * (fTemp4 - fTemp5)) + (fRec4[2] + (fSlow17 * (fRec4[0] - fRec3[2]))));
		fRec0[0] = ((fSlow17 * fRec3[0]) + (fRec3[2] + (fSlow16 * fTemp5)));
		output0[i] = (FAUSTFLOAT)((fRec0[0] * fSlow3) + (fSlow2 * (fTemp0 * fSlow1)));
		double fTemp6 = (double)input1[i];
		double fTemp7 = (fSlow9 + (fSlow10 * (1 - fRec2[0])));
		double fTemp8 = (fRec11[1] * cos((fSlow14 * fTemp7)));
		fRec11[0] = (0 - (((fSlow17 * fRec11[2]) + (fSlow16 * fTemp8)) - ((fSlow2 * fTemp6) + (fSlow13 * fRec7[1]))));
		double fTemp9 = (fRec10[1] * cos((fSlow18 * fTemp7)));
		fRec10[0] = ((fSlow16 * (fTemp8 - fTemp9)) + (fRec11[2] + (fSlow17 * (fRec11[0] - fRec10[2]))));
		double fTemp10 = (fRec9[1] * cos((fSlow19 * fTemp7)));
		fRec9[0] = ((fSlow16 * (fTemp9 - fTemp10)) + (fRec10[2] + (fSlow17 * (fRec10[0] - fRec9[2]))));
		double fTemp11 = (fRec8[1] * cos((fSlow12 * fTemp7)));
		fRec8[0] = ((fSlow16 * (fTemp10 - fTemp11)) + (fRec9[2] + (fSlow17 * (fRec9[0] - fRec8[2]))));
		fRec7[0] = ((fSlow17 * fRec8[0]) + (fRec8[2] + (fSlow16 * fTemp11)));
		output1[i] = (FAUSTFLOAT)((fRec7[0] * fSlow3) + (fSlow2 * (fTemp6 * fSlow1)));
		// post processing
		fRec7[1] = fRec7[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
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
	static const value_pair fcheckbox1_values[] = {{"linear"},{"invert"},{0}};
	reg.registerEnumVar("phaser.invert","","B","",fcheckbox1_values,&fcheckbox1, 0.0, 0.0, 1.0, 1.0);
	static const value_pair fcheckbox0_values[] = {{"direct "},{" vibrato"},{0}};
	reg.registerEnumVar("phaser.VibratoMode","","B","",fcheckbox0_values,&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("phaser.Notch width","","S","",&fslider7, 1e+03, 1e+01, 5e+03, 1.0);
	reg.registerVar("phaser.feedback gain","","S","",&fslider6, 0.0, 0.0, 1.0, 0.01);
	reg.registerVar("phaser.NotchFreq","","S","",&fslider5, 1.5, 1.1, 4.0, 0.01);
	reg.registerVar("phaser.MaxNotch1Freq","","S","",&fslider4, 8e+02, 2e+01, 1e+04, 1.0);
	reg.registerVar("phaser.MinNotch1Freq","","S","",&fslider3, 1e+02, 2e+01, 5e+03, 1.0);
	reg.registerVar("phaser.Speed","","S","",&fslider2, 0.5, 0.0, 1e+01, 0.01);
	reg.registerVar("phaser.level","","S","",&fslider1, 0.0, -6e+01, 1e+01, 0.1);
	reg.registerVar("phaser.depth","","S","",&fslider0, 1.0, 0.0, 1.0, 0.01);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "phaser",  // id
    N_("Phaser"),  // name
    0,  // groups
    0,  // mono_audio
    compute,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace phaser
