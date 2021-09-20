// generated from file '../src/faust/gx_ampmodul.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gx_ampmodul {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	gx_resample::FixedRateResampler smps;
	int sample_rate;
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fHslider0;
	double fRec0[6];
	FAUSTFLOAT fHslider1;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	FAUSTFLOAT fVslider1;
	double fRec16[2];
	double fVec0[2];
	double fRec15[2];
	double fRec14[3];
	double fConst8;
	double fConst9;
	double fVec1[2];
	double fConst10;
	double fRec17[2];
	double fRec13[2];
	double fConst11;
	double fConst12;
	double fRec12[2];
	double fRec11[2];
	FAUSTFLOAT fVslider2;
	double fRec18[2];
	double fVec2[2];
	double fRec10[2];
	double fRec9[3];
	double fConst13;
	double fConst14;
	double fVec3[2];
	double fConst15;
	double fRec19[2];
	double fRec8[2];
	double fRec7[2];
	double fRec6[2];
	FAUSTFLOAT fVslider3;
	double fRec20[2];
	double fVec4[2];
	double fRec5[2];
	double fRec4[3];
	double fConst16;
	double fConst17;
	double fVec5[2];
	double fConst18;
	double fRec21[2];
	double fRec3[2];
	double fRec2[2];
	double fRec1[6];
	double fRec22[6];
	double fVec6[2];
	double fRec37[2];
	double fRec36[3];
	double fVec7[2];
	double fRec38[2];
	double fRec35[2];
	double fRec34[2];
	double fRec33[2];
	double fVec8[2];
	double fRec32[2];
	double fRec31[3];
	double fVec9[2];
	double fRec39[2];
	double fRec30[2];
	double fRec29[2];
	double fRec28[2];
	double fVec10[2];
	double fRec27[2];
	double fRec26[3];
	double fVec11[2];
	double fRec40[2];
	double fRec25[2];
	double fRec24[2];
	double fRec23[6];

	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int sample_rate, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



static const char* parm_groups[] = {
	"amp2.stage2", N_("Postamp Tube2"),
	"amp2.stage1", N_("Postamp Tube1"),
	0
	};

Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "ampmodul";
	name = N_("Postamp");
	groups = parm_groups;
	description = ""; // description (tooltip)
	category = N_("Distortion");       // category
	shortname = "";     // shortname
	mono_audio = 0;
	stereo_audio = compute_static;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	load_ui = load_ui_f_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; (l0 < 6); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec16[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fVec0[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec15[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec14[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fVec1[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec17[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec13[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec12[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec11[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec18[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fVec2[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec10[l12] = 0.0;
	for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) fRec9[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fVec3[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec19[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec8[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec7[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec6[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec20[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fVec4[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec5[l21] = 0.0;
	for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) fRec4[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fVec5[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec21[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fRec3[l25] = 0.0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fRec2[l26] = 0.0;
	for (int l27 = 0; (l27 < 6); l27 = (l27 + 1)) fRec1[l27] = 0.0;
	for (int l28 = 0; (l28 < 6); l28 = (l28 + 1)) fRec22[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fVec6[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec37[l30] = 0.0;
	for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) fRec36[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fVec7[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fRec38[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec35[l34] = 0.0;
	for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) fRec34[l35] = 0.0;
	for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) fRec33[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fVec8[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fRec32[l38] = 0.0;
	for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) fRec31[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fVec9[l40] = 0.0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) fRec39[l41] = 0.0;
	for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) fRec30[l42] = 0.0;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fRec29[l43] = 0.0;
	for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) fRec28[l44] = 0.0;
	for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) fVec10[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec27[l46] = 0.0;
	for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) fRec26[l47] = 0.0;
	for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) fVec11[l48] = 0.0;
	for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) fRec40[l49] = 0.0;
	for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) fRec25[l50] = 0.0;
	for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) fRec24[l51] = 0.0;
	for (int l52 = 0; (l52 < 6); l52 = (l52 + 1)) fRec23[l52] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int RsamplingFreq)
{
	sample_rate = 96000;
	smp.setup(RsamplingFreq, sample_rate);
	smps.setup(RsamplingFreq, sample_rate);
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = std::tan((97.389372261283583 / fConst0));
	fConst2 = (1.0 / fConst1);
	fConst3 = (fConst2 + 1.0);
	fConst4 = (1.0 / (fConst1 * fConst3));
	fConst5 = (1.0 / std::tan((20517.741620594938 / fConst0)));
	fConst6 = (1.0 / (fConst5 + 1.0));
	fConst7 = (1.0 - fConst5);
	fConst8 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst9 = (1.0 / (fConst8 + 1.0));
	fConst10 = (1.0 - fConst8);
	fConst11 = (0.0 - fConst4);
	fConst12 = ((1.0 - fConst2) / fConst3);
	fConst13 = (1.0 / std::tan((414.69023027385271 / fConst0)));
	fConst14 = (1.0 / (fConst13 + 1.0));
	fConst15 = (1.0 - fConst13);
	fConst16 = (1.0 / std::tan((609.46897479641984 / fConst0)));
	fConst17 = (1.0 / (fConst16 + 1.0));
	fConst18 = (1.0 - fConst16);
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	FAUSTFLOAT buf[smp.max_out_count(count)];
	FAUSTFLOAT bufs[smps.max_out_count(count)];
	smps.up(count, input1, bufs);
	int ReCount = smp.up(count, input0, buf);
	double fSlow0 = double(fVslider0);
	double fSlow1 = (1.0 - std::max<double>(0.0, fSlow0));
	double fSlow2 = double(fHslider0);
	double fSlow3 = (1.0 - std::max<double>(0.0, (-1.0 * fSlow0)));
	double fSlow4 = double(fHslider1);
	double fSlow5 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider1))));
	double fSlow6 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider2))));
	double fSlow7 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider3))));
	for (int i = 0; (i < ReCount); i = (i + 1)) {
		double fTemp0 = double(buf[i]);
		fRec0[0] = (-1.0 * ((fSlow2 * fRec0[5]) - fTemp0));
		fRec16[0] = (fSlow5 + (0.999 * fRec16[1]));
		double fTemp1 = (fTemp0 * fRec16[0]);
		fVec0[0] = fTemp1;
		fRec15[0] = ((0.93028479253239138 * (fTemp1 + fVec0[1])) - (0.86056958506478287 * fRec15[1]));
		fRec14[0] = (fRec15[0] - ((1.8405051250752198 * fRec14[1]) + (0.86129424393186271 * fRec14[2])));
		double fTemp2 = (0.92544984225177063 * (fRec14[0] + fRec14[2]));
		double fTemp3 = (1.8508996845035413 * fRec14[1]);
		double fTemp4 = ((fTemp3 + fTemp2) / (double(Ranode(int(TUBE_TABLE_6V6_68k), double(fRec13[1]))) + 100000.0));
		fVec1[0] = fTemp4;
		fRec17[0] = (fConst9 * ((2700.0 * (fTemp4 + fVec1[1])) - (fConst10 * fRec17[1])));
		fRec13[0] = (double(Ftube(int(TUBE_TABLE_6V6_68k), double(((fTemp2 + (fRec17[0] + fTemp3)) + -1.7844169999999999)))) + -183.9104814814815);
		fRec12[0] = ((0.025000000000000001 * ((fConst4 * fRec13[0]) + (fConst11 * fRec13[1]))) - (fConst12 * fRec12[1]));
		fRec11[0] = (0.0 - (fConst6 * ((fConst7 * fRec11[1]) - (fRec12[0] + fRec12[1]))));
		fRec18[0] = (fSlow6 + (0.999 * fRec18[1]));
		double fTemp5 = (fRec11[0] * fRec18[0]);
		fVec2[0] = fTemp5;
		fRec10[0] = ((0.93028479253239138 * (fTemp5 + fVec2[1])) - (0.86056958506478287 * fRec10[1]));
		fRec9[0] = (fRec10[0] - ((1.8405051250752198 * fRec9[1]) + (0.86129424393186271 * fRec9[2])));
		double fTemp6 = (0.92544984225177063 * (fRec9[0] + fRec9[2]));
		double fTemp7 = (1.8508996845035413 * fRec9[1]);
		double fTemp8 = ((fTemp7 + fTemp6) / (double(Ranode(int(TUBE_TABLE_6V6_250k), double(fRec8[1]))) + 100000.0));
		fVec3[0] = fTemp8;
		fRec19[0] = (fConst14 * ((1500.0 * (fTemp8 + fVec3[1])) - (fConst15 * fRec19[1])));
		fRec8[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double(((fTemp6 + (fRec19[0] + fTemp7)) + -1.3646160000000001)))) + -159.0256);
		fRec7[0] = ((0.025000000000000001 * ((fConst4 * fRec8[0]) + (fConst11 * fRec8[1]))) - (fConst12 * fRec7[1]));
		fRec6[0] = (0.0 - (fConst6 * ((fConst7 * fRec6[1]) - (fRec7[0] + fRec7[1]))));
		fRec20[0] = (fSlow7 + (0.999 * fRec20[1]));
		double fTemp9 = (fRec6[0] * fRec20[0]);
		fVec4[0] = fTemp9;
		fRec5[0] = ((0.93028479253239138 * (fTemp9 + fVec4[1])) - (0.86056958506478287 * fRec5[1]));
		fRec4[0] = (fRec5[0] - ((1.8405051250752198 * fRec4[1]) + (0.86129424393186271 * fRec4[2])));
		double fTemp10 = (0.92544984225177063 * (fRec4[0] + fRec4[2]));
		double fTemp11 = (1.8508996845035413 * fRec4[1]);
		double fTemp12 = ((fTemp11 + fTemp10) / (double(Ranode(int(TUBE_TABLE_6V6_250k), double(fRec3[1]))) + 100000.0));
		fVec5[0] = fTemp12;
		fRec21[0] = (fConst17 * ((820.0 * (fTemp12 + fVec5[1])) - (fConst18 * fRec21[1])));
		fRec3[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double(((fTemp10 + (fRec21[0] + fTemp11)) + -0.96213199999999999)))) + -132.6668292682927);
		fRec2[0] = ((0.025000000000000001 * ((fConst4 * fRec3[0]) + (fConst11 * fRec3[1]))) - (fConst12 * fRec2[1]));
		fRec1[0] = (-1.0 * ((fSlow4 * fRec1[5]) - fRec2[0]));
		buf[i] = FAUSTFLOAT(((fSlow1 * fRec0[0]) + (fSlow3 * fRec1[0])));
		double fTemp13 = double(bufs[i]);
		fRec22[0] = (-1.0 * ((fSlow2 * fRec22[5]) - fTemp13));
		double fTemp14 = (fTemp13 * fRec16[0]);
		fVec6[0] = fTemp14;
		fRec37[0] = ((0.93028479253239138 * (fTemp14 + fVec6[1])) - (0.86056958506478287 * fRec37[1]));
		fRec36[0] = (fRec37[0] - ((1.8405051250752198 * fRec36[1]) + (0.86129424393186271 * fRec36[2])));
		double fTemp15 = (0.92544984225177063 * (fRec36[0] + fRec36[2]));
		double fTemp16 = (1.8508996845035413 * fRec36[1]);
		double fTemp17 = ((fTemp16 + fTemp15) / (double(Ranode(int(TUBE_TABLE_6V6_68k), double(fRec35[1]))) + 100000.0));
		fVec7[0] = fTemp17;
		fRec38[0] = (fConst9 * ((2700.0 * (fTemp17 + fVec7[1])) - (fConst10 * fRec38[1])));
		fRec35[0] = (double(Ftube(int(TUBE_TABLE_6V6_68k), double(((fTemp15 + (fRec38[0] + fTemp16)) + -1.7844169999999999)))) + -183.9104814814815);
		fRec34[0] = ((0.025000000000000001 * ((fConst4 * fRec35[0]) + (fConst11 * fRec35[1]))) - (fConst12 * fRec34[1]));
		fRec33[0] = (0.0 - (fConst6 * ((fConst7 * fRec33[1]) - (fRec34[0] + fRec34[1]))));
		double fTemp18 = (fRec18[0] * fRec33[0]);
		fVec8[0] = fTemp18;
		fRec32[0] = ((0.93028479253239138 * (fTemp18 + fVec8[1])) - (0.86056958506478287 * fRec32[1]));
		fRec31[0] = (fRec32[0] - ((1.8405051250752198 * fRec31[1]) + (0.86129424393186271 * fRec31[2])));
		double fTemp19 = (0.92544984225177063 * (fRec31[0] + fRec31[2]));
		double fTemp20 = (1.8508996845035413 * fRec31[1]);
		double fTemp21 = ((fTemp20 + fTemp19) / (double(Ranode(int(TUBE_TABLE_6V6_250k), double(fRec30[1]))) + 100000.0));
		fVec9[0] = fTemp21;
		fRec39[0] = (fConst14 * ((1500.0 * (fTemp21 + fVec9[1])) - (fConst15 * fRec39[1])));
		fRec30[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double(((fTemp19 + (fRec39[0] + fTemp20)) + -1.3646160000000001)))) + -159.0256);
		fRec29[0] = ((0.025000000000000001 * ((fConst4 * fRec30[0]) + (fConst11 * fRec30[1]))) - (fConst12 * fRec29[1]));
		fRec28[0] = (0.0 - (fConst6 * ((fConst7 * fRec28[1]) - (fRec29[0] + fRec29[1]))));
		double fTemp22 = (fRec20[0] * fRec28[0]);
		fVec10[0] = fTemp22;
		fRec27[0] = ((0.93028479253239138 * (fTemp22 + fVec10[1])) - (0.86056958506478287 * fRec27[1]));
		fRec26[0] = (fRec27[0] - ((1.8405051250752198 * fRec26[1]) + (0.86129424393186271 * fRec26[2])));
		double fTemp23 = (0.92544984225177063 * (fRec26[0] + fRec26[2]));
		double fTemp24 = (1.8508996845035413 * fRec26[1]);
		double fTemp25 = ((fTemp24 + fTemp23) / (double(Ranode(int(TUBE_TABLE_6V6_250k), double(fRec25[1]))) + 100000.0));
		fVec11[0] = fTemp25;
		fRec40[0] = (fConst17 * ((820.0 * (fTemp25 + fVec11[1])) - (fConst18 * fRec40[1])));
		fRec25[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double(((fTemp23 + (fRec40[0] + fTemp24)) + -0.96213199999999999)))) + -132.6668292682927);
		fRec24[0] = ((0.025000000000000001 * ((fConst4 * fRec25[0]) + (fConst11 * fRec25[1]))) - (fConst12 * fRec24[1]));
		fRec23[0] = (-1.0 * ((fSlow4 * fRec23[5]) - fRec24[0]));
		bufs[i] = FAUSTFLOAT(((fSlow1 * fRec22[0]) + (fSlow3 * fRec23[0])));
		for (int j0 = 5; (j0 > 0); j0 = (j0 - 1)) {
			fRec0[j0] = fRec0[(j0 - 1)];
		}
		fRec16[1] = fRec16[0];
		fVec0[1] = fVec0[0];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fVec1[1] = fVec1[0];
		fRec17[1] = fRec17[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fRec18[1] = fRec18[0];
		fVec2[1] = fVec2[0];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fVec3[1] = fVec3[0];
		fRec19[1] = fRec19[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec20[1] = fRec20[0];
		fVec4[1] = fVec4[0];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fVec5[1] = fVec5[0];
		fRec21[1] = fRec21[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		for (int j1 = 5; (j1 > 0); j1 = (j1 - 1)) {
			fRec1[j1] = fRec1[(j1 - 1)];
		}
		for (int j2 = 5; (j2 > 0); j2 = (j2 - 1)) {
			fRec22[j2] = fRec22[(j2 - 1)];
		}
		fVec6[1] = fVec6[0];
		fRec37[1] = fRec37[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		fVec7[1] = fVec7[0];
		fRec38[1] = fRec38[0];
		fRec35[1] = fRec35[0];
		fRec34[1] = fRec34[0];
		fRec33[1] = fRec33[0];
		fVec8[1] = fVec8[0];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fVec9[1] = fVec9[0];
		fRec39[1] = fRec39[0];
		fRec30[1] = fRec30[0];
		fRec29[1] = fRec29[0];
		fRec28[1] = fRec28[0];
		fVec10[1] = fVec10[0];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fVec11[1] = fVec11[0];
		fRec40[1] = fRec40[0];
		fRec25[1] = fRec25[0];
		fRec24[1] = fRec24[0];
		for (int j3 = 5; (j3 > 0); j3 = (j3 - 1)) {
			fRec23[j3] = fRec23[(j3 - 1)];
		}
	}
	smp.down(buf, output0);
	smps.down(bufs, output1);
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("ampmodul.feedbac",N_("Dry/FB"),"S","",&fHslider0, 0.0, -1.0, 1.0, 0.01, 0);
	reg.registerFloatVar("ampmodul.feedback",N_("Wet/FB"),"S","",&fHslider1, 0.0, -1.0, 1.0, 0.01, 0);
	reg.registerFloatVar("ampmodul.level",N_("Level"),"S","",&fVslider1, -20.0, -40.0, 4.0, 0.10000000000000001, 0);
	reg.registerFloatVar("ampmodul.amp2.stage1.tube1",N_("Tube I"),"S","",&fVslider2, 6.0, -20.0, 20.0, 0.10000000000000001, 0);
	reg.registerFloatVar("ampmodul.amp2.stage2.tube2",N_("Tube II"),"S","",&fVslider3, 6.0, -20.0, 20.0, 0.10000000000000001, 0);
	reg.registerFloatVar("ampmodul.wet_dry",N_("Dry/Wet"),"S","",&fVslider0, 0.0, -1.0, 1.0, 0.10000000000000001, 0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!-- Generated with glade 3.22.1 -->\n\
<interface>\n\
  <requires lib=\"gtk+\" version=\"3.20\"/>\n\
  <requires lib=\"gxwidgets\" version=\"0.0\"/>\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can_focus\">False</property>\n\
    <child>\n\
      <placeholder/>\n\
    </child>\n\
    <child>\n\
      <object class=\"GtkBox\" id=\"vbox1\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can_focus\">False</property>\n\
        <property name=\"orientation\">vertical</property>\n\
        <child>\n\
          <object class=\"GtkBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">8</property>\n\
            <child>\n\
              <object class=\"GtkBox\" id=\"hbox1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label1:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxMidKnob\" id=\"gxbigknob1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">ampmodul.feedbac</property>\n\
                        <property name=\"label_ref\">label1:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label2:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">ampmodul.wet_dry</property>\n\
                        <property name=\"label_ref\">label2:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label3:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">ampmodul.level</property>\n\
                        <property name=\"label_ref\">label3:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox5\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label4:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob4\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">ampmodul.amp2.stage1.tube1</property>\n\
                        <property name=\"label_ref\">label4:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">3</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox6\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label5:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob5\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">ampmodul.amp2.stage2.tube2</property>\n\
                        <property name=\"label_ref\">label5:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">4</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox7\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label6:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxMidKnob\" id=\"gxbigknob6\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">ampmodul.feedback</property>\n\
                        <property name=\"label_ref\">label6:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">5</property>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"pack_type\">end</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">False</property>\n\
            <property name=\"position\">0</property>\n\
          </packing>\n\
        </child>\n\
        <child>\n\
          <object class=\"GtkBox\" id=\"minibox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GxHSlider\" id=\"gxhslider1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">True</property>\n\
                <property name=\"receives_default\">True</property>\n\
                <property name=\"round_digits\">0</property>\n\
                <property name=\"var_id\">ampmodul.level</property>\n\
                <property name=\"show_value\">False</property>\n\
                <property name=\"value_position\">right</property>\n\
                <property name=\"value_xalign\">0.52000000000000002</property>\n\
                <property name=\"label_ref\">label0:rack_label</property>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">False</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
            <child>\n\
              <object class=\"GtkLabel\" id=\"label0:rack_label\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"label\" translatable=\"yes\">Level</property>\n\
                <property name=\"xalign\">0</property>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">False</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"position\">1</property>\n\
              </packing>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">True</property>\n\
            <property name=\"position\">1</property>\n\
          </packing>\n\
        </child>\n\
      </object>\n\
    </child>\n\
  </object>\n\
</interface>\n\
";

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade(glade_def);
        return 0;
    }
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("ampmodul" "." p)
// postamp
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("level"), _("level"));
b.closeBox();
b.openHorizontalBox("");
{
    b.insertSpacer();
    b.create_small_rackknobr(PARAM("feedbac"), _("dry/feedback  "));
    b.create_small_rackknob(PARAM("wet_dry"), _("dry/wet"));
    b.create_small_rackknob(PARAM("level"), _("level"));
    b.create_small_rackknob(PARAM("amp2.stage1.tube1"), _("tube1"));
    b.create_small_rackknob(PARAM("amp2.stage2.tube2"), _("tube2"));
    b.create_small_rackknobr(PARAM("feedback"), _("  wet/feedback"));
    b.insertSpacer();
}
b.closeBox();

#undef PARAM
        return 0;
    }
	return -1;
}

int Dsp::load_ui_f_static(const UiBuilder& b, int form)
{
	return static_cast<Dsp*>(b.plugin)->load_ui_f(b, form);
}
PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace gx_ampmodul
