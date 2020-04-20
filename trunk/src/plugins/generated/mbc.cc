// generated from file '../src/plugins/mbc.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace mbc {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	double fRec3[2];
	double fConst2;
	FAUSTFLOAT fHslider3;
	double fVec0[2];
	double fRec8[2];
	double fRec7[3];
	FAUSTFLOAT fHslider4;
	double fRec6[3];
	FAUSTFLOAT fHslider5;
	double fRec5[3];
	FAUSTFLOAT fHslider6;
	double fRec4[3];
	double fConst3;
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT fHslider8;
	FAUSTFLOAT fHslider9;
	double fRec11[2];
	double fRec10[2];
	double fRec9[2];
	double fRec0[2];
	int iRec1[2];
	double fRec2[2];
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT fHslider11;
	FAUSTFLOAT fHslider12;
	double fRec15[2];
	double fRec21[2];
	double fRec20[3];
	double fVec1[2];
	double fRec19[2];
	double fRec18[3];
	double fRec17[3];
	double fRec16[3];
	FAUSTFLOAT fHslider13;
	FAUSTFLOAT fHslider14;
	FAUSTFLOAT fHslider15;
	double fRec24[2];
	double fRec23[2];
	double fRec22[2];
	double fRec12[2];
	int iRec13[2];
	double fRec14[2];
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT fHslider16;
	FAUSTFLOAT fHslider17;
	FAUSTFLOAT fHslider18;
	double fRec28[2];
	double fRec33[2];
	double fRec32[3];
	double fVec2[2];
	double fRec31[2];
	double fRec30[3];
	double fRec29[3];
	FAUSTFLOAT fHslider19;
	FAUSTFLOAT fHslider20;
	FAUSTFLOAT fHslider21;
	double fRec36[2];
	double fRec35[2];
	double fRec34[2];
	double fRec25[2];
	int iRec26[2];
	double fRec27[2];
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT fHslider22;
	FAUSTFLOAT fHslider23;
	FAUSTFLOAT fHslider24;
	double fRec40[2];
	double fRec44[2];
	double fRec43[3];
	double fVec3[2];
	double fRec42[2];
	double fRec41[3];
	FAUSTFLOAT fHslider25;
	FAUSTFLOAT fHslider26;
	FAUSTFLOAT fHslider27;
	double fRec47[2];
	double fRec46[2];
	double fRec45[2];
	double fRec37[2];
	int iRec38[2];
	double fRec39[2];
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT fHslider28;
	FAUSTFLOAT fHslider29;
	FAUSTFLOAT fHslider30;
	double fRec51[2];
	double fRec53[2];
	double fRec52[3];
	FAUSTFLOAT fHslider31;
	FAUSTFLOAT fHslider32;
	FAUSTFLOAT fHslider33;
	double fRec56[2];
	double fRec55[2];
	double fRec54[2];
	double fRec48[2];
	int iRec49[2];
	double fRec50[2];
	FAUSTFLOAT fVbargraph4;

	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "mbc";
	name = N_("Multi Band Compressor");
	groups = 0;
	description = N_("Multi Band Compressor contributed by kokoko3k"); // description (tooltip)
	category = N_("Guitar Effects");       // category
	shortname = N_("MB Comp");     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec3[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fVec0[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec8[l2] = 0.0;
	for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) fRec7[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec6[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec5[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec4[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec11[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec10[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec9[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec0[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) iRec1[l11] = 0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec2[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec15[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec21[l14] = 0.0;
	for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) fRec20[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fVec1[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec19[l17] = 0.0;
	for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) fRec18[l18] = 0.0;
	for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) fRec17[l19] = 0.0;
	for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) fRec16[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec24[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fRec23[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fRec22[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec12[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) iRec13[l25] = 0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fRec14[l26] = 0.0;
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) fRec28[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec33[l28] = 0.0;
	for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) fRec32[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fVec2[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fRec31[l31] = 0.0;
	for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) fRec30[l32] = 0.0;
	for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) fRec29[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec36[l34] = 0.0;
	for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) fRec35[l35] = 0.0;
	for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) fRec34[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fRec25[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) iRec26[l38] = 0;
	for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) fRec27[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fRec40[l40] = 0.0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) fRec44[l41] = 0.0;
	for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) fRec43[l42] = 0.0;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fVec3[l43] = 0.0;
	for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) fRec42[l44] = 0.0;
	for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) fRec41[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec47[l46] = 0.0;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) fRec46[l47] = 0.0;
	for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) fRec45[l48] = 0.0;
	for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) fRec37[l49] = 0.0;
	for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) iRec38[l50] = 0;
	for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) fRec39[l51] = 0.0;
	for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) fRec51[l52] = 0.0;
	for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) fRec53[l53] = 0.0;
	for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) fRec52[l54] = 0.0;
	for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) fRec56[l55] = 0.0;
	for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) fRec55[l56] = 0.0;
	for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) fRec54[l57] = 0.0;
	for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) fRec48[l58] = 0.0;
	for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) iRec49[l59] = 0;
	for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) fRec50[l60] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = (1.0 / fConst0);
	fConst2 = (3.1415926535897931 / fConst0);
	fConst3 = (2.0 / fConst0);
	fHslider0 = FAUSTFLOAT(1.0);
	fHslider1 = FAUSTFLOAT(11.0);
	fHslider2 = FAUSTFLOAT(2.0);
	fHslider3 = FAUSTFLOAT(5000.0);
	fHslider4 = FAUSTFLOAT(1700.0);
	fHslider5 = FAUSTFLOAT(210.0);
	fHslider6 = FAUSTFLOAT(80.0);
	fHslider7 = FAUSTFLOAT(0.012);
	fHslider8 = FAUSTFLOAT(2.0);
	fHslider9 = FAUSTFLOAT(1.25);
	fHslider10 = FAUSTFLOAT(1.0);
	fHslider11 = FAUSTFLOAT(8.0);
	fHslider12 = FAUSTFLOAT(2.0);
	fHslider13 = FAUSTFLOAT(0.012);
	fHslider14 = FAUSTFLOAT(2.0);
	fHslider15 = FAUSTFLOAT(1.25);
	fHslider16 = FAUSTFLOAT(1.0);
	fHslider17 = FAUSTFLOAT(4.0);
	fHslider18 = FAUSTFLOAT(2.0);
	fHslider19 = FAUSTFLOAT(0.012);
	fHslider20 = FAUSTFLOAT(2.0);
	fHslider21 = FAUSTFLOAT(1.25);
	fHslider22 = FAUSTFLOAT(1.0);
	fHslider23 = FAUSTFLOAT(10.0);
	fHslider24 = FAUSTFLOAT(2.0);
	fHslider25 = FAUSTFLOAT(0.012);
	fHslider26 = FAUSTFLOAT(2.0);
	fHslider27 = FAUSTFLOAT(1.25);
	fHslider28 = FAUSTFLOAT(1.0);
	fHslider29 = FAUSTFLOAT(13.0);
	fHslider30 = FAUSTFLOAT(2.0);
	fHslider31 = FAUSTFLOAT(0.012);
	fHslider32 = FAUSTFLOAT(2.0);
	fHslider33 = FAUSTFLOAT(1.25);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = double(fHslider0);
	double fSlow1 = std::fabs((std::max<double>(0.0, (fSlow0 + -2.0)) + -1.0));
	double fSlow2 = std::max<double>(0.0, (fSlow0 + -1.0));
	double fSlow3 = double(fHslider1);
	double fSlow4 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * (std::fabs((fSlow2 + -1.0)) * (fSlow3 - double(fHslider2))))));
	int iSlow5 = int(fSlow2);
	double fSlow6 = std::tan((fConst2 * double(fHslider3)));
	double fSlow7 = (1.0 / fSlow6);
	double fSlow8 = (((fSlow7 + 1.0000000000000004) / fSlow6) + 1.0);
	double fSlow9 = (1.0 / fSlow8);
	double fSlow10 = mydsp_faustpower2_f(fSlow6);
	double fSlow11 = (1.0 / fSlow10);
	double fSlow12 = (fSlow7 + 1.0);
	double fSlow13 = (0.0 - (1.0 / (fSlow12 * fSlow6)));
	double fSlow14 = (1.0 / fSlow12);
	double fSlow15 = (1.0 - fSlow7);
	double fSlow16 = (((fSlow7 + -1.0000000000000004) / fSlow6) + 1.0);
	double fSlow17 = (2.0 * (1.0 - fSlow11));
	double fSlow18 = (0.0 - (2.0 / fSlow10));
	double fSlow19 = std::tan((fConst2 * double(fHslider4)));
	double fSlow20 = (1.0 / fSlow19);
	double fSlow21 = (fSlow20 + 1.0);
	double fSlow22 = (1.0 / ((fSlow21 / fSlow19) + 1.0));
	double fSlow23 = (1.0 - fSlow20);
	double fSlow24 = (1.0 - (fSlow23 / fSlow19));
	double fSlow25 = mydsp_faustpower2_f(fSlow19);
	double fSlow26 = (1.0 / fSlow25);
	double fSlow27 = (2.0 * (1.0 - fSlow26));
	double fSlow28 = std::tan((fConst2 * double(fHslider5)));
	double fSlow29 = (1.0 / fSlow28);
	double fSlow30 = (fSlow29 + 1.0);
	double fSlow31 = (1.0 / ((fSlow30 / fSlow28) + 1.0));
	double fSlow32 = (1.0 - fSlow29);
	double fSlow33 = (1.0 - (fSlow32 / fSlow28));
	double fSlow34 = mydsp_faustpower2_f(fSlow28);
	double fSlow35 = (1.0 / fSlow34);
	double fSlow36 = (2.0 * (1.0 - fSlow35));
	double fSlow37 = std::tan((fConst2 * double(fHslider6)));
	double fSlow38 = (1.0 / fSlow37);
	double fSlow39 = (fSlow38 + 1.0);
	double fSlow40 = (1.0 / ((fSlow39 / fSlow37) + 1.0));
	double fSlow41 = (1.0 - fSlow38);
	double fSlow42 = (1.0 - (fSlow41 / fSlow37));
	double fSlow43 = mydsp_faustpower2_f(fSlow37);
	double fSlow44 = (1.0 / fSlow43);
	double fSlow45 = (2.0 * (1.0 - fSlow44));
	double fSlow46 = double(fHslider7);
	double fSlow47 = std::exp((0.0 - (fConst3 / fSlow46)));
	double fSlow48 = (((1.0 / double(fHslider8)) + -1.0) * (1.0 - fSlow47));
	double fSlow49 = std::exp((0.0 - (fConst1 / fSlow46)));
	double fSlow50 = std::exp((0.0 - (fConst1 / double(fHslider9))));
	double fSlow51 = double(fHslider10);
	double fSlow52 = std::fabs((std::max<double>(0.0, (fSlow51 + -2.0)) + -1.0));
	double fSlow53 = std::max<double>(0.0, (fSlow51 + -1.0));
	double fSlow54 = double(fHslider11);
	double fSlow55 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * (std::fabs((fSlow53 + -1.0)) * (fSlow54 - double(fHslider12))))));
	int iSlow56 = int(fSlow53);
	double fSlow57 = (((fSlow20 + 1.0000000000000004) / fSlow19) + 1.0);
	double fSlow58 = (1.0 / fSlow57);
	double fSlow59 = (0.0 - (1.0 / (fSlow19 * fSlow21)));
	double fSlow60 = (1.0 / fSlow21);
	double fSlow61 = (1.0 / (fSlow8 * fSlow19));
	double fSlow62 = (((fSlow20 + -1.0000000000000004) / fSlow19) + 1.0);
	double fSlow63 = (0.0 - (2.0 / fSlow25));
	double fSlow64 = double(fHslider13);
	double fSlow65 = std::exp((0.0 - (fConst3 / fSlow64)));
	double fSlow66 = (((1.0 / double(fHslider14)) + -1.0) * (1.0 - fSlow65));
	double fSlow67 = std::exp((0.0 - (fConst1 / fSlow64)));
	double fSlow68 = std::exp((0.0 - (fConst1 / double(fHslider15))));
	double fSlow69 = double(fHslider16);
	double fSlow70 = std::fabs((std::max<double>(0.0, (fSlow69 + -2.0)) + -1.0));
	double fSlow71 = std::max<double>(0.0, (fSlow69 + -1.0));
	double fSlow72 = double(fHslider17);
	double fSlow73 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * (std::fabs((fSlow71 + -1.0)) * (fSlow72 - double(fHslider18))))));
	int iSlow74 = int(fSlow71);
	double fSlow75 = (((fSlow29 + 1.0000000000000004) / fSlow28) + 1.0);
	double fSlow76 = (1.0 / fSlow75);
	double fSlow77 = (0.0 - (1.0 / (fSlow28 * fSlow30)));
	double fSlow78 = (1.0 / fSlow30);
	double fSlow79 = (1.0 / (fSlow57 * fSlow28));
	double fSlow80 = (((fSlow29 + -1.0000000000000004) / fSlow28) + 1.0);
	double fSlow81 = (0.0 - (2.0 / fSlow34));
	double fSlow82 = double(fHslider19);
	double fSlow83 = std::exp((0.0 - (fConst3 / fSlow82)));
	double fSlow84 = (((1.0 / double(fHslider20)) + -1.0) * (1.0 - fSlow83));
	double fSlow85 = std::exp((0.0 - (fConst1 / fSlow82)));
	double fSlow86 = std::exp((0.0 - (fConst1 / double(fHslider21))));
	double fSlow87 = double(fHslider22);
	double fSlow88 = std::fabs((std::max<double>(0.0, (fSlow87 + -2.0)) + -1.0));
	double fSlow89 = std::max<double>(0.0, (fSlow87 + -1.0));
	double fSlow90 = double(fHslider23);
	double fSlow91 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * (std::fabs((fSlow89 + -1.0)) * (fSlow90 - double(fHslider24))))));
	int iSlow92 = int(fSlow89);
	double fSlow93 = (1.0 / (((fSlow38 + 1.0000000000000004) / fSlow37) + 1.0));
	double fSlow94 = (0.0 - (1.0 / (fSlow37 * fSlow39)));
	double fSlow95 = (1.0 / fSlow39);
	double fSlow96 = (1.0 / (fSlow75 * fSlow37));
	double fSlow97 = (((fSlow38 + -1.0000000000000004) / fSlow37) + 1.0);
	double fSlow98 = (0.0 - (2.0 / fSlow43));
	double fSlow99 = double(fHslider25);
	double fSlow100 = std::exp((0.0 - (fConst3 / fSlow99)));
	double fSlow101 = (((1.0 / double(fHslider26)) + -1.0) * (1.0 - fSlow100));
	double fSlow102 = std::exp((0.0 - (fConst1 / fSlow99)));
	double fSlow103 = std::exp((0.0 - (fConst1 / double(fHslider27))));
	double fSlow104 = double(fHslider28);
	double fSlow105 = std::fabs((std::max<double>(0.0, (fSlow104 + -2.0)) + -1.0));
	double fSlow106 = std::max<double>(0.0, (fSlow104 + -1.0));
	double fSlow107 = double(fHslider29);
	double fSlow108 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * (std::fabs((fSlow106 + -1.0)) * (fSlow107 - double(fHslider30))))));
	int iSlow109 = int(fSlow106);
	double fSlow110 = double(fHslider31);
	double fSlow111 = std::exp((0.0 - (fConst3 / fSlow110)));
	double fSlow112 = (((1.0 / double(fHslider32)) + -1.0) * (1.0 - fSlow111));
	double fSlow113 = std::exp((0.0 - (fConst1 / fSlow110)));
	double fSlow114 = std::exp((0.0 - (fConst1 / double(fHslider33))));
	for (int i = 0; (i < count); i = (i + 1)) {
		int iTemp0 = (iRec1[1] < 4096);
		fRec3[0] = (fSlow4 + (0.999 * fRec3[1]));
		double fTemp1 = double(input0[i]);
		fVec0[0] = fTemp1;
		fRec8[0] = ((fSlow13 * fVec0[1]) - (fSlow14 * ((fSlow15 * fRec8[1]) - (fSlow7 * fTemp1))));
		fRec7[0] = (fRec8[0] - (fSlow9 * ((fSlow16 * fRec7[2]) + (fSlow17 * fRec7[1]))));
		double fTemp2 = (fSlow27 * fRec6[1]);
		fRec6[0] = ((fSlow9 * (((fSlow11 * fRec7[0]) + (fSlow18 * fRec7[1])) + (fSlow11 * fRec7[2]))) - (fSlow22 * ((fSlow24 * fRec6[2]) + fTemp2)));
		double fTemp3 = (fSlow36 * fRec5[1]);
		fRec5[0] = ((fRec6[2] + (fSlow22 * (fTemp2 + (fSlow24 * fRec6[0])))) - (fSlow31 * ((fSlow33 * fRec5[2]) + fTemp3)));
		double fTemp4 = (fSlow45 * fRec4[1]);
		fRec4[0] = ((fRec5[2] + (fSlow31 * (fTemp3 + (fSlow33 * fRec5[0])))) - (fSlow40 * ((fSlow42 * fRec4[2]) + fTemp4)));
		double fTemp5 = (fRec4[2] + (fSlow40 * (fTemp4 + (fSlow42 * fRec4[0]))));
		double fTemp6 = (iSlow5?0.0:fTemp5);
		double fTemp7 = std::fabs(fTemp6);
		double fTemp8 = ((fRec10[1] > fTemp7)?fSlow50:fSlow49);
		fRec11[0] = ((fRec11[1] * fTemp8) + (fTemp7 * (1.0 - fTemp8)));
		fRec10[0] = fRec11[0];
		fRec9[0] = ((fSlow47 * fRec9[1]) + (fSlow48 * std::max<double>((fSlow3 + (20.0 * std::log10(fRec10[0]))), 0.0)));
		double fTemp9 = (fSlow1 * (fRec3[0] * (iSlow5?fTemp5:(fTemp6 * std::pow(10.0, (0.050000000000000003 * fRec9[0]))))));
		double fTemp10 = std::max<double>(fConst1, std::fabs(fTemp9));
		fRec0[0] = (iTemp0?(fTemp10 + fRec0[1]):fTemp10);
		iRec1[0] = (iTemp0?(iRec1[1] + 1):1);
		fRec2[0] = (iTemp0?fRec2[1]:(0.000244140625 * fRec0[1]));
		fVbargraph0 = FAUSTFLOAT(fRec2[0]);
		int iTemp11 = (iRec13[1] < 4096);
		fRec15[0] = (fSlow55 + (0.999 * fRec15[1]));
		fRec21[0] = (0.0 - (fSlow14 * ((fSlow15 * fRec21[1]) - (fVec0[1] + fTemp1))));
		fRec20[0] = (fRec21[0] - (fSlow9 * ((fSlow16 * fRec20[2]) + (fSlow17 * fRec20[1]))));
		double fTemp12 = (fRec20[2] + (fRec20[0] + (2.0 * fRec20[1])));
		double fTemp13 = (fSlow9 * fTemp12);
		fVec1[0] = fTemp13;
		fRec19[0] = ((fSlow59 * fVec1[1]) - (fSlow60 * ((fSlow23 * fRec19[1]) - (fSlow61 * fTemp12))));
		fRec18[0] = (fRec19[0] - (fSlow58 * ((fSlow62 * fRec18[2]) + (fSlow27 * fRec18[1]))));
		double fTemp14 = (fSlow36 * fRec17[1]);
		fRec17[0] = ((fSlow58 * (((fSlow26 * fRec18[0]) + (fSlow63 * fRec18[1])) + (fSlow26 * fRec18[2]))) - (fSlow31 * ((fSlow33 * fRec17[2]) + fTemp14)));
		double fTemp15 = (fSlow45 * fRec16[1]);
		fRec16[0] = ((fRec17[2] + (fSlow31 * (fTemp14 + (fSlow33 * fRec17[0])))) - (fSlow40 * ((fSlow42 * fRec16[2]) + fTemp15)));
		double fTemp16 = (fRec16[2] + (fSlow40 * (fTemp15 + (fSlow42 * fRec16[0]))));
		double fTemp17 = (iSlow56?0.0:fTemp16);
		double fTemp18 = std::fabs(fTemp17);
		double fTemp19 = ((fRec23[1] > fTemp18)?fSlow68:fSlow67);
		fRec24[0] = ((fRec24[1] * fTemp19) + (fTemp18 * (1.0 - fTemp19)));
		fRec23[0] = fRec24[0];
		fRec22[0] = ((fSlow65 * fRec22[1]) + (fSlow66 * std::max<double>((fSlow54 + (20.0 * std::log10(fRec23[0]))), 0.0)));
		double fTemp20 = (fSlow52 * (fRec15[0] * (iSlow56?fTemp16:(fTemp17 * std::pow(10.0, (0.050000000000000003 * fRec22[0]))))));
		double fTemp21 = std::max<double>(fConst1, std::fabs(fTemp20));
		fRec12[0] = (iTemp11?(fTemp21 + fRec12[1]):fTemp21);
		iRec13[0] = (iTemp11?(iRec13[1] + 1):1);
		fRec14[0] = (iTemp11?fRec14[1]:(0.000244140625 * fRec12[1]));
		fVbargraph1 = FAUSTFLOAT(fRec14[0]);
		int iTemp22 = (iRec26[1] < 4096);
		fRec28[0] = (fSlow73 + (0.999 * fRec28[1]));
		fRec33[0] = (0.0 - (fSlow60 * ((fSlow23 * fRec33[1]) - (fTemp13 + fVec1[1]))));
		fRec32[0] = (fRec33[0] - (fSlow58 * ((fSlow62 * fRec32[2]) + (fSlow27 * fRec32[1]))));
		double fTemp23 = (fRec32[2] + (fRec32[0] + (2.0 * fRec32[1])));
		double fTemp24 = (fSlow58 * fTemp23);
		fVec2[0] = fTemp24;
		fRec31[0] = ((fSlow77 * fVec2[1]) - (fSlow78 * ((fSlow32 * fRec31[1]) - (fSlow79 * fTemp23))));
		fRec30[0] = (fRec31[0] - (fSlow76 * ((fSlow80 * fRec30[2]) + (fSlow36 * fRec30[1]))));
		double fTemp25 = (fSlow45 * fRec29[1]);
		fRec29[0] = ((fSlow76 * (((fSlow35 * fRec30[0]) + (fSlow81 * fRec30[1])) + (fSlow35 * fRec30[2]))) - (fSlow40 * ((fSlow42 * fRec29[2]) + fTemp25)));
		double fTemp26 = (fRec29[2] + (fSlow40 * (fTemp25 + (fSlow42 * fRec29[0]))));
		double fTemp27 = (iSlow74?0.0:fTemp26);
		double fTemp28 = std::fabs(fTemp27);
		double fTemp29 = ((fRec35[1] > fTemp28)?fSlow86:fSlow85);
		fRec36[0] = ((fRec36[1] * fTemp29) + (fTemp28 * (1.0 - fTemp29)));
		fRec35[0] = fRec36[0];
		fRec34[0] = ((fSlow83 * fRec34[1]) + (fSlow84 * std::max<double>((fSlow72 + (20.0 * std::log10(fRec35[0]))), 0.0)));
		double fTemp30 = (fSlow70 * (fRec28[0] * (iSlow74?fTemp26:(fTemp27 * std::pow(10.0, (0.050000000000000003 * fRec34[0]))))));
		double fTemp31 = std::max<double>(fConst1, std::fabs(fTemp30));
		fRec25[0] = (iTemp22?(fTemp31 + fRec25[1]):fTemp31);
		iRec26[0] = (iTemp22?(iRec26[1] + 1):1);
		fRec27[0] = (iTemp22?fRec27[1]:(0.000244140625 * fRec25[1]));
		fVbargraph2 = FAUSTFLOAT(fRec27[0]);
		int iTemp32 = (iRec38[1] < 4096);
		fRec40[0] = (fSlow91 + (0.999 * fRec40[1]));
		fRec44[0] = (0.0 - (fSlow78 * ((fSlow32 * fRec44[1]) - (fTemp24 + fVec2[1]))));
		fRec43[0] = (fRec44[0] - (fSlow76 * ((fSlow80 * fRec43[2]) + (fSlow36 * fRec43[1]))));
		double fTemp33 = (fRec43[2] + (fRec43[0] + (2.0 * fRec43[1])));
		double fTemp34 = (fSlow76 * fTemp33);
		fVec3[0] = fTemp34;
		fRec42[0] = ((fSlow94 * fVec3[1]) - (fSlow95 * ((fSlow41 * fRec42[1]) - (fSlow96 * fTemp33))));
		fRec41[0] = (fRec42[0] - (fSlow93 * ((fSlow97 * fRec41[2]) + (fSlow45 * fRec41[1]))));
		double fTemp35 = (fSlow93 * (((fSlow44 * fRec41[0]) + (fSlow98 * fRec41[1])) + (fSlow44 * fRec41[2])));
		double fTemp36 = (iSlow92?0.0:fTemp35);
		double fTemp37 = std::fabs(fTemp36);
		double fTemp38 = ((fRec46[1] > fTemp37)?fSlow103:fSlow102);
		fRec47[0] = ((fRec47[1] * fTemp38) + (fTemp37 * (1.0 - fTemp38)));
		fRec46[0] = fRec47[0];
		fRec45[0] = ((fSlow100 * fRec45[1]) + (fSlow101 * std::max<double>((fSlow90 + (20.0 * std::log10(fRec46[0]))), 0.0)));
		double fTemp39 = (fSlow88 * (fRec40[0] * (iSlow92?fTemp35:(fTemp36 * std::pow(10.0, (0.050000000000000003 * fRec45[0]))))));
		double fTemp40 = std::max<double>(fConst1, std::fabs(fTemp39));
		fRec37[0] = (iTemp32?(fTemp40 + fRec37[1]):fTemp40);
		iRec38[0] = (iTemp32?(iRec38[1] + 1):1);
		fRec39[0] = (iTemp32?fRec39[1]:(0.000244140625 * fRec37[1]));
		fVbargraph3 = FAUSTFLOAT(fRec39[0]);
		int iTemp41 = (iRec49[1] < 4096);
		fRec51[0] = (fSlow108 + (0.999 * fRec51[1]));
		fRec53[0] = (0.0 - (fSlow95 * ((fSlow41 * fRec53[1]) - (fTemp34 + fVec3[1]))));
		fRec52[0] = (fRec53[0] - (fSlow93 * ((fSlow97 * fRec52[2]) + (fSlow45 * fRec52[1]))));
		double fTemp42 = (fSlow93 * (fRec52[2] + (fRec52[0] + (2.0 * fRec52[1]))));
		double fTemp43 = (iSlow109?0.0:fTemp42);
		double fTemp44 = std::fabs(fTemp43);
		double fTemp45 = ((fRec55[1] > fTemp44)?fSlow114:fSlow113);
		fRec56[0] = ((fRec56[1] * fTemp45) + (fTemp44 * (1.0 - fTemp45)));
		fRec55[0] = fRec56[0];
		fRec54[0] = ((fSlow111 * fRec54[1]) + (fSlow112 * std::max<double>((fSlow107 + (20.0 * std::log10(fRec55[0]))), 0.0)));
		double fTemp46 = (fSlow105 * (fRec51[0] * (iSlow109?fTemp42:(fTemp43 * std::pow(10.0, (0.050000000000000003 * fRec54[0]))))));
		double fTemp47 = std::max<double>(fConst1, std::fabs(fTemp46));
		fRec48[0] = (iTemp41?(fTemp47 + fRec48[1]):fTemp47);
		iRec49[0] = (iTemp41?(iRec49[1] + 1):1);
		fRec50[0] = (iTemp41?fRec50[1]:(0.000244140625 * fRec48[1]));
		fVbargraph4 = FAUSTFLOAT(fRec50[0]);
		output0[i] = FAUSTFLOAT(((((fTemp9 + fTemp20) + fTemp30) + fTemp39) + fTemp46));
		fRec3[1] = fRec3[0];
		fVec0[1] = fVec0[0];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec0[1] = fRec0[0];
		iRec1[1] = iRec1[0];
		fRec2[1] = fRec2[0];
		fRec15[1] = fRec15[0];
		fRec21[1] = fRec21[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fVec1[1] = fVec1[0];
		fRec19[1] = fRec19[0];
		fRec18[2] = fRec18[1];
		fRec18[1] = fRec18[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fRec24[1] = fRec24[0];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec12[1] = fRec12[0];
		iRec13[1] = iRec13[0];
		fRec14[1] = fRec14[0];
		fRec28[1] = fRec28[0];
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fVec2[1] = fVec2[0];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fRec29[2] = fRec29[1];
		fRec29[1] = fRec29[0];
		fRec36[1] = fRec36[0];
		fRec35[1] = fRec35[0];
		fRec34[1] = fRec34[0];
		fRec25[1] = fRec25[0];
		iRec26[1] = iRec26[0];
		fRec27[1] = fRec27[0];
		fRec40[1] = fRec40[0];
		fRec44[1] = fRec44[0];
		fRec43[2] = fRec43[1];
		fRec43[1] = fRec43[0];
		fVec3[1] = fVec3[0];
		fRec42[1] = fRec42[0];
		fRec41[2] = fRec41[1];
		fRec41[1] = fRec41[0];
		fRec47[1] = fRec47[0];
		fRec46[1] = fRec46[0];
		fRec45[1] = fRec45[0];
		fRec37[1] = fRec37[0];
		iRec38[1] = iRec38[0];
		fRec39[1] = fRec39[0];
		fRec51[1] = fRec51[0];
		fRec53[1] = fRec53[0];
		fRec52[2] = fRec52[1];
		fRec52[1] = fRec52[0];
		fRec56[1] = fRec56[0];
		fRec55[1] = fRec55[0];
		fRec54[1] = fRec54[0];
		fRec48[1] = fRec48[0];
		iRec49[1] = iRec49[0];
		fRec50[1] = fRec50[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	static const value_pair fHslider28_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbc.Mode1","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fHslider28_values,&fHslider28, 1.0, 1.0, 3.0, 1.0);
	static const value_pair fHslider22_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbc.Mode2","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fHslider22_values,&fHslider22, 1.0, 1.0, 3.0, 1.0);
	static const value_pair fHslider16_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbc.Mode3","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fHslider16_values,&fHslider16, 1.0, 1.0, 3.0, 1.0);
	static const value_pair fHslider10_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbc.Mode4","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fHslider10_values,&fHslider10, 1.0, 1.0, 3.0, 1.0);
	static const value_pair fHslider0_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerEnumVar("mbc.Mode5","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),fHslider0_values,&fHslider0, 1.0, 1.0, 3.0, 1.0);
	reg.registerVar("mbc.Makeup1","","S",N_("Post amplification and threshold"),&fHslider29, 13.0, -50.0, 50.0, 0.10000000000000001);
	reg.registerVar("mbc.Makeup2","","S",N_("Post amplification and threshold"),&fHslider23, 10.0, -50.0, 50.0, 0.10000000000000001);
	reg.registerVar("mbc.Makeup3","","S",N_("Post amplification and threshold"),&fHslider17, 4.0, -50.0, 50.0, 0.10000000000000001);
	reg.registerVar("mbc.Makeup4","","S",N_("Post amplification and threshold"),&fHslider11, 8.0, -50.0, 50.0, 0.10000000000000001);
	reg.registerVar("mbc.Makeup5","","S",N_("Post amplification and threshold"),&fHslider1, 11.0, -50.0, 50.0, 0.10000000000000001);
	reg.registerVar("mbc.Makeup-Threshold1","","S",N_("Threshold correction, an anticlip measure"),&fHslider30, 2.0, 0.0, 10.0, 0.10000000000000001);
	reg.registerVar("mbc.Makeup-Threshold2","","S",N_("Threshold correction, an anticlip measure"),&fHslider24, 2.0, 0.0, 10.0, 0.10000000000000001);
	reg.registerVar("mbc.Makeup-Threshold3","","S",N_("Threshold correction, an anticlip measure"),&fHslider18, 2.0, 0.0, 10.0, 0.10000000000000001);
	reg.registerVar("mbc.Makeup-Threshold4","","S",N_("Threshold correction, an anticlip measure"),&fHslider12, 2.0, 0.0, 10.0, 0.10000000000000001);
	reg.registerVar("mbc.Makeup-Threshold5","","S",N_("Threshold correction, an anticlip measure"),&fHslider2, 2.0, 0.0, 10.0, 0.10000000000000001);
	reg.registerVar("mbc.Ratio1","","S",N_("Compression ratio"),&fHslider32, 2.0, 1.0, 100.0, 0.10000000000000001);
	reg.registerVar("mbc.Ratio2","","S",N_("Compression ratio"),&fHslider26, 2.0, 1.0, 100.0, 0.10000000000000001);
	reg.registerVar("mbc.Ratio3","","S",N_("Compression ratio"),&fHslider20, 2.0, 1.0, 100.0, 0.10000000000000001);
	reg.registerVar("mbc.Ratio4","","S",N_("Compression ratio"),&fHslider14, 2.0, 1.0, 100.0, 0.10000000000000001);
	reg.registerVar("mbc.Ratio5","","S",N_("Compression ratio"),&fHslider8, 2.0, 1.0, 100.0, 0.10000000000000001);
	reg.registerVar("mbc.Attack1","","S",N_("Time before the compressor starts to kick in"),&fHslider31, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbc.Attack2","","S",N_("Time before the compressor starts to kick in"),&fHslider25, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbc.Attack3","","S",N_("Time before the compressor starts to kick in"),&fHslider19, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbc.Attack4","","S",N_("Time before the compressor starts to kick in"),&fHslider13, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbc.Attack5","","S",N_("Time before the compressor starts to kick in"),&fHslider7, 0.012, 0.001, 1.0, 0.001);
	reg.registerVar("mbc.Release1","","S",N_("Time before the compressor releases the sound"),&fHslider33, 1.25, 0.01, 10.0, 0.01);
	reg.registerVar("mbc.Release2","","S",N_("Time before the compressor releases the sound"),&fHslider27, 1.25, 0.01, 10.0, 0.01);
	reg.registerVar("mbc.Release3","","S",N_("Time before the compressor releases the sound"),&fHslider21, 1.25, 0.01, 10.0, 0.01);
	reg.registerVar("mbc.Release4","","S",N_("Time before the compressor releases the sound"),&fHslider15, 1.25, 0.01, 10.0, 0.01);
	reg.registerVar("mbc.Release5","","S",N_("Time before the compressor releases the sound"),&fHslider9, 1.25, 0.01, 10.0, 0.01);
	reg.registerVar("mbc.crossover_b1_b2",N_("Crossover B1-B2 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fHslider6, 80.0, 20.0, 20000.0, 1.0800000000000001);
	reg.registerVar("mbc.crossover_b2_b3",N_("Crossover B2-B3 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fHslider5, 210.0, 20.0, 20000.0, 1.0800000000000001);
	reg.registerVar("mbc.crossover_b3_b4",N_("Crossover B3-B4 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fHslider4, 1700.0, 20.0, 20000.0, 1.0800000000000001);
	reg.registerVar("mbc.crossover_b4_b5",N_("Crossover B4-B5 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fHslider3, 5000.0, 20.0, 20000.0, 1.0800000000000001);
	reg.registerNonMidiFloatVar("mbc.v1",&fVbargraph4, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbc.v2",&fVbargraph3, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbc.v3",&fVbargraph2, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbc.v4",&fVbargraph1, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbc.v5",&fVbargraph0, false, true, -70.0, -70.0, 4.0, 0.00001);
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
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GtkBox\" id=\"hbox1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"spacing\">8</property>\n\
                <child>\n\
                  <object class=\"GtkNotebook\" id=\"notebook:tab_rack\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GtkBox\" id=\"vbox3\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"spacing\">4</property>\n\
                            <child>\n\
                              <object class=\"GtkBox\" id=\"hbox4\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox4\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"orientation\">vertical</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_1:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Ratio</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob1\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbc.Ratio1</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox5\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"orientation\">vertical</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_2:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Makeup</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob2\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbc.Makeup1</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
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
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox6\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"orientation\">vertical</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_3:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Anticlip</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob3\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbc.Makeup-Threshold1</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">2</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSelector\" id=\"gxselector1\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.Mode1</property>\n\
                                <property name=\"value_position\">right</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkGrid\" id=\"table1\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob1\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.Attack1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"top_attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob4\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.crossover_b1_b2</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">3</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_4:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">Att</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">0</property>\n\
                                <property name=\"top_attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_7:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">2</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_5:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">Rel</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">2</property>\n\
                                <property name=\"top_attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob3\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.Release1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">3</property>\n\
                                <property name=\"top_attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
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
                    <child type=\"tab\">\n\
                      <object class=\"GtkLabel\" id=\"label1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Band 1</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"tab_fill\">False</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox5\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GtkBox\" id=\"vbox7\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"spacing\">4</property>\n\
                            <child>\n\
                              <object class=\"GtkBox\" id=\"hbox6\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox8\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"orientation\">vertical</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_8:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Ratio</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob4\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbc.Ratio2</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox9\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"orientation\">vertical</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_9:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Makeup</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob5\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbc.Makeup2</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
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
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox10\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"orientation\">vertical</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_10:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Anticlip</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob6\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbc.Makeup-Threshold2</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">2</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSelector\" id=\"gxselector2\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.Mode2</property>\n\
                                <property name=\"value_position\">right</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkGrid\" id=\"table2\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob5\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.Attack2</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"top_attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob6\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.crossover_b2_b3</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">3</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_11:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">Att</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">0</property>\n\
                                <property name=\"top_attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_14:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">2</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_13:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">Low</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">0</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_12:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">Rel</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">2</property>\n\
                                <property name=\"top_attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob7\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.crossover_b1_b2</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob8\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.Release2</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">3</property>\n\
                                <property name=\"top_attach\">0</property>\n\
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
                      <packing>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child type=\"tab\">\n\
                      <object class=\"GtkLabel\" id=\"label2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Band 2</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">1</property>\n\
                        <property name=\"tab_fill\">False</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox7\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GtkBox\" id=\"vbox11\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"spacing\">4</property>\n\
                            <child>\n\
                              <object class=\"GtkBox\" id=\"hbox8\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox12\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"orientation\">vertical</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_15:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Ratio</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob7\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbc.Ratio3</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox13\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"orientation\">vertical</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_16:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Makeup</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob8\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbc.Makeup3</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
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
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox14\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"orientation\">vertical</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_17:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Anticlip</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob9\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbc.Makeup-Threshold3</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">2</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSelector\" id=\"gxselector3\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.Mode3</property>\n\
                                <property name=\"value_position\">right</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkGrid\" id=\"table3\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob9\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.Attack3</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"top_attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob10\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.crossover_b3_b4</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">3</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_18:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">Att</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">0</property>\n\
                                <property name=\"top_attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_21:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">2</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_20:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">Low</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">0</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_19:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">Rel</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">2</property>\n\
                                <property name=\"top_attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob11\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.crossover_b2_b3</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob12\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.Release3</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">3</property>\n\
                                <property name=\"top_attach\">0</property>\n\
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
                      <packing>\n\
                        <property name=\"position\">2</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child type=\"tab\">\n\
                      <object class=\"GtkLabel\" id=\"label3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Band 3</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">2</property>\n\
                        <property name=\"tab_fill\">False</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox9\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GtkBox\" id=\"vbox15\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"spacing\">4</property>\n\
                            <child>\n\
                              <object class=\"GtkBox\" id=\"hbox10\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox16\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"orientation\">vertical</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_22:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Ratio</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob10\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbc.Ratio4</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox17\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"orientation\">vertical</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_23:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Makeup</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob11\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbc.Makeup4</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
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
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox18\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"orientation\">vertical</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_24:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Anticlip</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob12\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbc.Makeup-Threshold4</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">2</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSelector\" id=\"gxselector4\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.Mode4</property>\n\
                                <property name=\"value_position\">right</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkGrid\" id=\"table4\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob13\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.Attack4</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"top_attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob14\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.crossover_b4_b5</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">3</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_25:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">Att</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">0</property>\n\
                                <property name=\"top_attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_28:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">2</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_27:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">Low</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">0</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_26:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">Rel</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">2</property>\n\
                                <property name=\"top_attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob15\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.crossover_b3_b4</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob16\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.Release4</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">3</property>\n\
                                <property name=\"top_attach\">0</property>\n\
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
                      <packing>\n\
                        <property name=\"position\">3</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child type=\"tab\">\n\
                      <object class=\"GtkLabel\" id=\"label4\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Band 4</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">3</property>\n\
                        <property name=\"tab_fill\">False</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox11\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GtkBox\" id=\"vbox19\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"spacing\">4</property>\n\
                            <child>\n\
                              <object class=\"GtkBox\" id=\"hbox12\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox20\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"orientation\">vertical</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_29:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Ratio</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob13\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbc.Ratio5</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox21\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"orientation\">vertical</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_30:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Makeup</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob14\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbc.Makeup5</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
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
                                <child>\n\
                                  <object class=\"GtkBox\" id=\"vbox22\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"orientation\">vertical</property>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label_31:rack_label\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">Anticlip</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnobR\" id=\"gxmediumknob15\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">mbc.Makeup-Threshold5</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">True</property>\n\
                                        <property name=\"fill\">True</property>\n\
                                        <property name=\"position\">1</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">2</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSelector\" id=\"gxselector5\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.Mode5</property>\n\
                                <property name=\"value_position\">right</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkGrid\" id=\"table5\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob17\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.Attack5</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"top_attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_32:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">Att</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">0</property>\n\
                                <property name=\"top_attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_34:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">Low</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">0</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_33:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">Rel</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">2</property>\n\
                                <property name=\"top_attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob19\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.crossover_b4_b5</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob20\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbc.Release5</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">3</property>\n\
                                <property name=\"top_attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_35:rack_label\">\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">2</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">4</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child type=\"tab\">\n\
                      <object class=\"GtkLabel\" id=\"label6\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Band 5</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">4</property>\n\
                        <property name=\"tab_fill\">False</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label5:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Levels</property>\n\
                        <property name=\"xalign\">0</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter1\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbc.v1</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter2\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbc.v2</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter3\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbc.v3</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">2</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter4\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbc.v4</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">3</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter5\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbc.v5</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">4</property>\n\
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
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">True</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">True</property>\n\
            <property name=\"position\">0</property>\n\
          </packing>\n\
        </child>\n\
        <child>\n\
          <object class=\"GtkBox\" id=\"minibox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <placeholder/>\n\
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
#define PARAM(p) ("mbc" "." p)

b.openHorizontalhideBox("");
b.closeBox();

b.openHorizontalBox("");
b.openVerticalBox("");

b.openTabBox("");

b.openHorizontalBox(N_("Band 1"));
b.openpaintampBox("");
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup1"), N_("Makeup (db)"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup-Threshold1"), N_("Anticlip (db)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b1_b2"), N_("Low Shelf (Hz)"));
b.closeBox();
b.openHorizontalBox("");
b.create_selector_no_caption(PARAM("Mode1"));
b.create_small_rackknob(PARAM("Ratio1"), N_("Ratio"));
b.create_small_rackknob(PARAM("Attack1"), N_("Attack"));
b.create_small_rackknob(PARAM("Release1"), N_("Release"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 2"));
b.openpaintampBox("");
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup2"),  N_("Makeup (db)"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup-Threshold2"), N_("Anticlip (db)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b1_b2"), N_("Low (hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b2_b3"), N_("High (hz)"));
b.closeBox();
b.openHorizontalBox("");
b.create_selector_no_caption(PARAM("Mode2"));
b.create_small_rackknob(PARAM("Ratio2"), N_("Ratio"));
b.create_small_rackknob(PARAM("Attack2"), N_("Attack"));
b.create_small_rackknob(PARAM("Release2"), N_("Release"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 3"));
b.openpaintampBox("");
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup3"), N_("Makeup (db)"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup-Threshold3"), N_("Anticlip (db)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b2_b3"), N_("Low (hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b3_b4"), N_("High (hz)"));
b.closeBox();
b.openHorizontalBox("");
b.create_selector_no_caption(PARAM("Mode3"));
b.create_small_rackknob(PARAM("Ratio3"), N_("Ratio"));
b.create_small_rackknob(PARAM("Attack3"), N_("Attack"));
b.create_small_rackknob(PARAM("Release3"), N_("Release"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 4"));
b.openpaintampBox("");
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup4"), N_("Makeup (db)"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup-Threshold4"), N_("Anticlip (db)"));
b.set_next_flags(UI_NUM_RIGHT);
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b3_b4"), N_("Low (hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b4_b5"), N_("High (hz)"));
b.closeBox();
b.openHorizontalBox("");
b.create_selector_no_caption(PARAM("Mode4"));
b.create_small_rackknob(PARAM("Ratio4"), N_("Ratio"));
b.create_small_rackknob(PARAM("Attack4"), N_("Attack"));
b.create_small_rackknob(PARAM("Release4"), N_("Release"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 5"));
b.openpaintampBox("");
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup5"), N_("Makeup (db)"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup-Threshold5"), N_("Anticlip (db)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b4_b5"), N_("High Shelf (hz)"));
b.closeBox();
b.openHorizontalBox("");
b.create_selector_no_caption(PARAM("Mode5"));
b.create_small_rackknob(PARAM("Ratio5"), N_("Ratio"));
b.create_small_rackknob(PARAM("Attack5"), N_("Attack"));
b.create_small_rackknob(PARAM("Release5"), N_("Release"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.closeBox();
b.closeBox();
b.openVerticalBox2("Analyze");
b.create_simple_meter(PARAM("v1"));
b.create_simple_meter(PARAM("v2"));
b.create_simple_meter(PARAM("v3"));
b.create_simple_meter(PARAM("v4"));
b.create_simple_meter(PARAM("v5"));
b.closeBox();
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

} // end namespace mbc
} // end namespace pluginlib
