// generated from file '../src/faust/tonecontroll.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

namespace tonecontroll {
static int 	iConst0;
static double 	fConst1;
static double 	fConst2;
static double 	fConst3;
static double 	fConst4;
static double 	fConst5;
static double 	fConst6;
static double 	fConst7;
static double 	fConst8;
static double 	fConst9;
static double 	fConst10;
static double 	fConst11;
static double 	fConst12;
static double 	fConst13;
static double 	fConst14;
static double 	fConst15;
static double 	fConst16;
static double 	fConst17;
static double 	fVec0[2];
static double 	fConst18;
static double 	fRec3[2];
static double 	fRec2[3];
static double 	fVec1[2];
static double 	fConst19;
static double 	fConst20;
static double 	fRec1[2];
static double 	fRec0[3];
static double 	fConst21;
static FAUSTFLOAT 	fslider0;
static double 	fRec4[2];
static double 	fRec6[2];
static double 	fRec5[3];
static FAUSTFLOAT 	fslider1;
static double 	fRec7[2];
static double 	fConst22;
static double 	fConst23;
static double 	fConst24;
static double 	fRec10[2];
static double 	fRec9[3];
static double 	fConst25;
static double 	fRec8[3];
static FAUSTFLOAT 	fslider2;
static double 	fRec11[2];
static double 	fConst26;
static double 	fConst27;
static double 	fRec12[2];
static FAUSTFLOAT 	fslider3;
static FAUSTFLOAT 	fcheckbox0;
static double 	fVec2[2];
static double 	fRec16[2];
static double 	fRec15[3];
static double 	fVec3[2];
static double 	fRec14[2];
static double 	fRec13[3];
static double 	fRec18[2];
static double 	fRec17[3];
static double 	fRec21[2];
static double 	fRec20[3];
static double 	fRec19[3];
static double 	fRec22[2];
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
}

static void init(unsigned int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = tan((1884.9555921538758 / iConst0));
	fConst2 = (1.0 / faustpower<2>(fConst1));
	fConst3 = (2 * (1 - fConst2));
	fConst4 = (1.0 / fConst1);
	fConst5 = (1 + ((fConst4 - 1.0000000000000004) / fConst1));
	fConst6 = (1.0 / (1 + ((fConst4 + 1.0000000000000004) / fConst1)));
	fConst7 = (1 + fConst4);
	fConst8 = (0 - ((1 - fConst4) / fConst7));
	fConst9 = tan((7539.822368615503 / iConst0));
	fConst10 = (1.0 / faustpower<2>(fConst9));
	fConst11 = (2 * (1 - fConst10));
	fConst12 = (1.0 / fConst9);
	fConst13 = (1 + ((fConst12 - 1.0000000000000004) / fConst9));
	fConst14 = (1 + ((1.0000000000000004 + fConst12) / fConst9));
	fConst15 = (1.0 / fConst14);
	fConst16 = (1 + fConst12);
	fConst17 = (0 - ((1 - fConst12) / fConst16));
	fConst18 = (1.0 / fConst16);
	fConst19 = (0 - fConst4);
	fConst20 = (1.0 / (fConst7 * fConst14));
	fConst21 = (2 * (0 - fConst2));
	fConst22 = (1 + ((fConst4 - 1.0) / fConst1));
	fConst23 = (1.0 / (1 + ((1.0 + fConst4) / fConst1)));
	fConst24 = (0 - fConst12);
	fConst25 = (2 * (0 - fConst10));
	fConst26 = exp((0 - (2e+02 / iConst0)));
	fConst27 = exp((0 - (0.1 / iConst0)));
	clear_state();
}

static void compute(int count, float *input0, float *input1, float *output0, float *output1, PluginDef *)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * fslider1)));
	double 	fSlow2 = (0.0010000000000000009 * pow(10,(0.05 * fslider2)));
	double 	fSlow3 = fslider3;
	double 	fSlow4 = (5 * fSlow3);
	int 	iSlow5 = int(fcheckbox0);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec3[0] = ((fConst18 * (fVec0[0] + fVec0[1])) + (fConst17 * fRec3[1]));
		fRec2[0] = (fRec3[0] - (fConst15 * ((fConst13 * fRec2[2]) + (fConst11 * fRec2[1]))));
		double fTemp1 = (fRec2[2] + (fRec2[0] + (2 * fRec2[1])));
		fVec1[0] = fTemp1;
		fRec1[0] = ((fConst20 * ((fConst19 * fVec1[1]) + (fConst4 * fVec1[0]))) + (fConst8 * fRec1[1]));
		fRec0[0] = (fRec1[0] - (fConst6 * ((fConst5 * fRec0[2]) + (fConst3 * fRec0[1]))));
		fRec4[0] = (fSlow0 + (0.999 * fRec4[1]));
		fRec6[0] = ((fConst20 * (fVec1[0] + fVec1[1])) + (fConst8 * fRec6[1]));
		fRec5[0] = (fRec6[0] - (fConst6 * ((fConst5 * fRec5[2]) + (fConst3 * fRec5[1]))));
		fRec7[0] = (fSlow1 + (0.999 * fRec7[1]));
		double fTemp2 = (fConst3 * fRec8[1]);
		fRec10[0] = ((fConst18 * ((fConst24 * fVec0[1]) + (fConst12 * fVec0[0]))) + (fConst17 * fRec10[1]));
		fRec9[0] = (fRec10[0] - (fConst15 * ((fConst13 * fRec9[2]) + (fConst11 * fRec9[1]))));
		fRec8[0] = ((fConst15 * (((fConst10 * fRec9[0]) + (fConst25 * fRec9[1])) + (fConst10 * fRec9[2]))) - (fConst23 * ((fConst22 * fRec8[2]) + fTemp2)));
		fRec11[0] = (fSlow2 + (0.999 * fRec11[1]));
		double fTemp3 = ((fRec11[0] * (fRec8[2] + (fConst23 * (fTemp2 + (fConst22 * fRec8[0]))))) + (fConst6 * ((fRec7[0] * (fRec5[2] + (fRec5[0] + (2 * fRec5[1])))) + (fRec4[0] * (((fConst2 * fRec0[0]) + (fConst21 * fRec0[1])) + (fConst2 * fRec0[2]))))));
		double fTemp4 = max(1, fabs(fTemp3));
		double fTemp5 = ((fConst27 * (fRec12[1] >= fTemp4)) + (fConst26 * (fRec12[1] < fTemp4)));
		fRec12[0] = ((fTemp4 * (0 - (fTemp5 - 1))) + (fRec12[1] * fTemp5));
		double fTemp6 = max(0, (fSlow4 + (20 * log10(fRec12[0]))));
		double fTemp7 = (0.5 * min(1, max(0, (0.09522902580706599 * fTemp6))));
		output0[i] = (FAUSTFLOAT)((iSlow5)?(fTemp3 * pow(10,(0.05 * (fSlow3 + ((fTemp6 * (0 - fTemp7)) / (1 + fTemp7)))))):fTemp3);
		double fTemp8 = (double)input1[i];
		fVec2[0] = fTemp8;
		fRec16[0] = ((fConst18 * (fVec2[0] + fVec2[1])) + (fConst17 * fRec16[1]));
		fRec15[0] = (fRec16[0] - (fConst15 * ((fConst13 * fRec15[2]) + (fConst11 * fRec15[1]))));
		double fTemp9 = (fRec15[2] + (fRec15[0] + (2 * fRec15[1])));
		fVec3[0] = fTemp9;
		fRec14[0] = ((fConst20 * ((fConst19 * fVec3[1]) + (fConst4 * fVec3[0]))) + (fConst8 * fRec14[1]));
		fRec13[0] = (fRec14[0] - (fConst6 * ((fConst5 * fRec13[2]) + (fConst3 * fRec13[1]))));
		fRec18[0] = ((fConst20 * (fVec3[0] + fVec3[1])) + (fConst8 * fRec18[1]));
		fRec17[0] = (fRec18[0] - (fConst6 * ((fConst5 * fRec17[2]) + (fConst3 * fRec17[1]))));
		double fTemp10 = (fConst3 * fRec19[1]);
		fRec21[0] = ((fConst18 * ((fConst24 * fVec2[1]) + (fConst12 * fVec2[0]))) + (fConst17 * fRec21[1]));
		fRec20[0] = (fRec21[0] - (fConst15 * ((fConst13 * fRec20[2]) + (fConst11 * fRec20[1]))));
		fRec19[0] = ((fConst15 * (((fConst10 * fRec20[0]) + (fConst25 * fRec20[1])) + (fConst10 * fRec20[2]))) - (fConst23 * ((fConst22 * fRec19[2]) + fTemp10)));
		double fTemp11 = ((fRec11[0] * (fRec19[2] + (fConst23 * (fTemp10 + (fConst22 * fRec19[0]))))) + (fConst6 * ((fRec7[0] * (fRec17[2] + (fRec17[0] + (2 * fRec17[1])))) + (fRec4[0] * (((fConst2 * fRec13[0]) + (fConst21 * fRec13[1])) + (fConst2 * fRec13[2]))))));
		double fTemp12 = max(1, fabs(fTemp11));
		double fTemp13 = ((fConst27 * (fRec22[1] >= fTemp12)) + (fConst26 * (fRec22[1] < fTemp12)));
		fRec22[0] = ((fTemp12 * (0 - (fTemp13 - 1))) + (fRec22[1] * fTemp13));
		double fTemp14 = max(0, (fSlow4 + (20 * log10(fRec22[0]))));
		double fTemp15 = (0.5 * min(1, max(0, (0.09522902580706599 * fTemp14))));
		output1[i] = (FAUSTFLOAT)((iSlow5)?(fTemp11 * pow(10,(0.05 * (fSlow3 + ((fTemp14 * (0 - fTemp15)) / (1 + fTemp15)))))):fTemp11);
		// post processing
		fRec22[1] = fRec22[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fVec3[1] = fVec3[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fVec2[1] = fVec2[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec7[1] = fRec7[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec4[1] = fRec4[0];
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fVec1[1] = fVec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fVec0[1] = fVec0[0];
	}
}

static int register_params(const ParamReg& reg)
{
	reg.registerVar("tonemodul.Treble",N_(""),"S",N_(""),&fslider2, 0.0, -5.0, 5.0, 0.01);
	reg.registerVar("tonemodul.sharper",N_("sharper"),"S",N_(""),&fslider3, 1.0, 1.0, 1e+01, 1.0);
	reg.registerVar("tonemodul.ON",N_(""),"B",N_(""),&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("tonemodul.Bass",N_(""),"S",N_(""),&fslider1, 0.0, -5.0, 5.0, 0.01);
	reg.registerVar("tonemodul.Middle",N_(""),"S",N_(""),&fslider0, 0.0, -5.0, 5.0, 0.01);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "tonemodul",  // id
    N_("3 Band EQ"),  // name
    0,  // groups
    0,  // mono_audio
    compute,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace tonecontroll
