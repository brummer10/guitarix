// generated from file '../src/plugins/mbcs.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace mbcs {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	double fConst2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	double fVec0[2];
	double fRec12[2];
	double fRec11[3];
	double fVec1[2];
	double fRec10[2];
	double fRec9[3];
	double fVec2[2];
	double fRec8[2];
	double fRec7[3];
	double fVec3[2];
	double fRec6[2];
	double fRec5[3];
	double fVec4[2];
	double fRec20[2];
	double fRec19[3];
	double fVec5[2];
	double fRec18[2];
	double fRec17[3];
	double fVec6[2];
	double fRec16[2];
	double fRec15[3];
	double fVec7[2];
	double fRec14[2];
	double fRec13[3];
	FAUSTFLOAT fHslider6;
	double fRec4[2];
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT fHslider8;
	double fRec3[2];
	FAUSTFLOAT fHslider9;
	double fRec21[2];
	double fRec0[2];
	int iRec1[2];
	double fRec2[2];
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT fHslider11;
	double fRec28[2];
	double fRec27[3];
	double fRec30[2];
	double fRec29[3];
	FAUSTFLOAT fHslider12;
	double fRec26[2];
	FAUSTFLOAT fHslider13;
	FAUSTFLOAT fHslider14;
	double fRec25[2];
	FAUSTFLOAT fHslider15;
	double fRec31[2];
	double fRec22[2];
	int iRec23[2];
	double fRec24[2];
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT fHslider16;
	FAUSTFLOAT fHslider17;
	double fRec39[2];
	double fRec38[3];
	double fRec37[3];
	double fRec42[2];
	double fRec41[3];
	double fRec40[3];
	FAUSTFLOAT fHslider18;
	double fRec36[2];
	FAUSTFLOAT fHslider19;
	FAUSTFLOAT fHslider20;
	double fRec35[2];
	FAUSTFLOAT fHslider21;
	double fRec43[2];
	double fRec32[2];
	int iRec33[2];
	double fRec34[2];
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT fHslider22;
	FAUSTFLOAT fHslider23;
	double fRec52[2];
	double fRec51[3];
	double fRec50[3];
	double fRec49[3];
	double fRec56[2];
	double fRec55[3];
	double fRec54[3];
	double fRec53[3];
	FAUSTFLOAT fHslider24;
	double fRec48[2];
	FAUSTFLOAT fHslider25;
	FAUSTFLOAT fHslider26;
	double fRec47[2];
	FAUSTFLOAT fHslider27;
	double fRec57[2];
	double fRec44[2];
	int iRec45[2];
	double fRec46[2];
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT fHslider28;
	FAUSTFLOAT fHslider29;
	double fRec67[2];
	double fRec66[3];
	double fRec65[3];
	double fRec64[3];
	double fRec63[3];
	double fRec72[2];
	double fRec71[3];
	double fRec70[3];
	double fRec69[3];
	double fRec68[3];
	FAUSTFLOAT fHslider30;
	double fRec62[2];
	FAUSTFLOAT fHslider31;
	FAUSTFLOAT fHslider32;
	double fRec61[2];
	FAUSTFLOAT fHslider33;
	double fRec73[2];
	double fRec58[2];
	int iRec59[2];
	double fRec60[2];
	FAUSTFLOAT fVbargraph4;

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



Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "mbcs";
	name = N_("Multi Band Compressor Stereo");
	groups = 0;
	description = N_("Multi Band Compressor contributed by kokoko3k"); // description (tooltip)
	category = N_("Guitar Effects");       // category
	shortname = N_("MB Comp St");     // shortname
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fVec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec12[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRec11[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fVec1[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec10[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec9[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fVec2[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec8[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec7[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fVec3[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec6[l10] = 0.0;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec5[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fVec4[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec20[l13] = 0.0;
	for (int l14 = 0; l14 < 3; l14 = l14 + 1) fRec19[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fVec5[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec18[l16] = 0.0;
	for (int l17 = 0; l17 < 3; l17 = l17 + 1) fRec17[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fVec6[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec16[l19] = 0.0;
	for (int l20 = 0; l20 < 3; l20 = l20 + 1) fRec15[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fVec7[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec14[l22] = 0.0;
	for (int l23 = 0; l23 < 3; l23 = l23 + 1) fRec13[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec4[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec3[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec21[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec0[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) iRec1[l28] = 0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec2[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec28[l30] = 0.0;
	for (int l31 = 0; l31 < 3; l31 = l31 + 1) fRec27[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fRec30[l32] = 0.0;
	for (int l33 = 0; l33 < 3; l33 = l33 + 1) fRec29[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fRec26[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec25[l35] = 0.0;
	for (int l36 = 0; l36 < 2; l36 = l36 + 1) fRec31[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec22[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) iRec23[l38] = 0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec24[l39] = 0.0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec39[l40] = 0.0;
	for (int l41 = 0; l41 < 3; l41 = l41 + 1) fRec38[l41] = 0.0;
	for (int l42 = 0; l42 < 3; l42 = l42 + 1) fRec37[l42] = 0.0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fRec42[l43] = 0.0;
	for (int l44 = 0; l44 < 3; l44 = l44 + 1) fRec41[l44] = 0.0;
	for (int l45 = 0; l45 < 3; l45 = l45 + 1) fRec40[l45] = 0.0;
	for (int l46 = 0; l46 < 2; l46 = l46 + 1) fRec36[l46] = 0.0;
	for (int l47 = 0; l47 < 2; l47 = l47 + 1) fRec35[l47] = 0.0;
	for (int l48 = 0; l48 < 2; l48 = l48 + 1) fRec43[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec32[l49] = 0.0;
	for (int l50 = 0; l50 < 2; l50 = l50 + 1) iRec33[l50] = 0;
	for (int l51 = 0; l51 < 2; l51 = l51 + 1) fRec34[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fRec52[l52] = 0.0;
	for (int l53 = 0; l53 < 3; l53 = l53 + 1) fRec51[l53] = 0.0;
	for (int l54 = 0; l54 < 3; l54 = l54 + 1) fRec50[l54] = 0.0;
	for (int l55 = 0; l55 < 3; l55 = l55 + 1) fRec49[l55] = 0.0;
	for (int l56 = 0; l56 < 2; l56 = l56 + 1) fRec56[l56] = 0.0;
	for (int l57 = 0; l57 < 3; l57 = l57 + 1) fRec55[l57] = 0.0;
	for (int l58 = 0; l58 < 3; l58 = l58 + 1) fRec54[l58] = 0.0;
	for (int l59 = 0; l59 < 3; l59 = l59 + 1) fRec53[l59] = 0.0;
	for (int l60 = 0; l60 < 2; l60 = l60 + 1) fRec48[l60] = 0.0;
	for (int l61 = 0; l61 < 2; l61 = l61 + 1) fRec47[l61] = 0.0;
	for (int l62 = 0; l62 < 2; l62 = l62 + 1) fRec57[l62] = 0.0;
	for (int l63 = 0; l63 < 2; l63 = l63 + 1) fRec44[l63] = 0.0;
	for (int l64 = 0; l64 < 2; l64 = l64 + 1) iRec45[l64] = 0;
	for (int l65 = 0; l65 < 2; l65 = l65 + 1) fRec46[l65] = 0.0;
	for (int l66 = 0; l66 < 2; l66 = l66 + 1) fRec67[l66] = 0.0;
	for (int l67 = 0; l67 < 3; l67 = l67 + 1) fRec66[l67] = 0.0;
	for (int l68 = 0; l68 < 3; l68 = l68 + 1) fRec65[l68] = 0.0;
	for (int l69 = 0; l69 < 3; l69 = l69 + 1) fRec64[l69] = 0.0;
	for (int l70 = 0; l70 < 3; l70 = l70 + 1) fRec63[l70] = 0.0;
	for (int l71 = 0; l71 < 2; l71 = l71 + 1) fRec72[l71] = 0.0;
	for (int l72 = 0; l72 < 3; l72 = l72 + 1) fRec71[l72] = 0.0;
	for (int l73 = 0; l73 < 3; l73 = l73 + 1) fRec70[l73] = 0.0;
	for (int l74 = 0; l74 < 3; l74 = l74 + 1) fRec69[l74] = 0.0;
	for (int l75 = 0; l75 < 3; l75 = l75 + 1) fRec68[l75] = 0.0;
	for (int l76 = 0; l76 < 2; l76 = l76 + 1) fRec62[l76] = 0.0;
	for (int l77 = 0; l77 < 2; l77 = l77 + 1) fRec61[l77] = 0.0;
	for (int l78 = 0; l78 < 2; l78 = l78 + 1) fRec73[l78] = 0.0;
	for (int l79 = 0; l79 < 2; l79 = l79 + 1) fRec58[l79] = 0.0;
	for (int l80 = 0; l80 < 2; l80 = l80 + 1) iRec59[l80] = 0;
	for (int l81 = 0; l81 < 2; l81 = l81 + 1) fRec60[l81] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 1.0 / fConst0;
	fConst2 = 3.141592653589793 / fConst0;
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	double fSlow0 = double(fHslider0);
	double fSlow1 = std::max<double>(0.0, fSlow0 + -1.0);
	int iSlow2 = int(fSlow1);
	double fSlow3 = double(fHslider1);
	double fSlow4 = 0.5 * fSlow3;
	int iSlow5 = std::fabs(fSlow4) < 2.220446049250313e-16;
	double fSlow6 = ((iSlow5) ? 0.0 : std::exp(-(fConst1 / ((iSlow5) ? 1.0 : fSlow4))));
	double fSlow7 = std::tan(fConst2 * double(fHslider2));
	double fSlow8 = mydsp_faustpower2_f(fSlow7);
	double fSlow9 = 2.0 * (1.0 - 1.0 / fSlow8);
	double fSlow10 = 1.0 / fSlow7;
	double fSlow11 = (fSlow10 + -1.0000000000000004) / fSlow7 + 1.0;
	double fSlow12 = (fSlow10 + 1.0000000000000004) / fSlow7 + 1.0;
	double fSlow13 = 1.0 / fSlow12;
	double fSlow14 = std::tan(fConst2 * double(fHslider3));
	double fSlow15 = mydsp_faustpower2_f(fSlow14);
	double fSlow16 = 2.0 * (1.0 - 1.0 / fSlow15);
	double fSlow17 = 1.0 / fSlow14;
	double fSlow18 = (fSlow17 + -1.0000000000000004) / fSlow14 + 1.0;
	double fSlow19 = (fSlow17 + 1.0000000000000004) / fSlow14 + 1.0;
	double fSlow20 = 1.0 / fSlow19;
	double fSlow21 = std::tan(fConst2 * double(fHslider4));
	double fSlow22 = mydsp_faustpower2_f(fSlow21);
	double fSlow23 = 2.0 * (1.0 - 1.0 / fSlow22);
	double fSlow24 = 1.0 / fSlow21;
	double fSlow25 = (fSlow24 + -1.0000000000000004) / fSlow21 + 1.0;
	double fSlow26 = (fSlow24 + 1.0000000000000004) / fSlow21 + 1.0;
	double fSlow27 = 1.0 / fSlow26;
	double fSlow28 = std::tan(fConst2 * double(fHslider5));
	double fSlow29 = mydsp_faustpower2_f(fSlow28);
	double fSlow30 = 2.0 * (1.0 - 1.0 / fSlow29);
	double fSlow31 = 1.0 / fSlow28;
	double fSlow32 = (fSlow31 + -1.0000000000000004) / fSlow28 + 1.0;
	double fSlow33 = (fSlow31 + 1.0000000000000004) / fSlow28 + 1.0;
	double fSlow34 = 1.0 / fSlow33;
	double fSlow35 = 1.0 - fSlow31;
	double fSlow36 = 1.0 / (fSlow31 + 1.0);
	double fSlow37 = 1.0 - fSlow24;
	double fSlow38 = fSlow24 + 1.0;
	double fSlow39 = 1.0 / fSlow38;
	double fSlow40 = 1.0 - fSlow17;
	double fSlow41 = fSlow17 + 1.0;
	double fSlow42 = 1.0 / fSlow41;
	double fSlow43 = 1.0 - fSlow10;
	double fSlow44 = fSlow10 + 1.0;
	double fSlow45 = 1.0 / fSlow44;
	double fSlow46 = double(fHslider6);
	int iSlow47 = std::fabs(fSlow46) < 2.220446049250313e-16;
	double fSlow48 = ((iSlow47) ? 0.0 : std::exp(-(fConst1 / ((iSlow47) ? 1.0 : fSlow46))));
	int iSlow49 = std::fabs(fSlow3) < 2.220446049250313e-16;
	double fSlow50 = ((iSlow49) ? 0.0 : std::exp(-(fConst1 / ((iSlow49) ? 1.0 : fSlow3))));
	double fSlow51 = double(fHslider7);
	double fSlow52 = 1.0 - fSlow6;
	double fSlow53 = 1.0 / std::max<double>(2.220446049250313e-16, double(fHslider8)) + -1.0;
	double fSlow54 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (fSlow51 - double(fHslider9)) * std::fabs(fSlow1 + -1.0));
	double fSlow55 = std::fabs(std::max<double>(0.0, fSlow0 + -2.0) + -1.0);
	double fSlow56 = double(fHslider10);
	double fSlow57 = std::max<double>(0.0, fSlow56 + -1.0);
	int iSlow58 = int(fSlow57);
	double fSlow59 = double(fHslider11);
	double fSlow60 = 0.5 * fSlow59;
	int iSlow61 = std::fabs(fSlow60) < 2.220446049250313e-16;
	double fSlow62 = ((iSlow61) ? 0.0 : std::exp(-(fConst1 / ((iSlow61) ? 1.0 : fSlow60))));
	double fSlow63 = 1.0 / (fSlow8 * fSlow12);
	double fSlow64 = double(fHslider12);
	int iSlow65 = std::fabs(fSlow64) < 2.220446049250313e-16;
	double fSlow66 = ((iSlow65) ? 0.0 : std::exp(-(fConst1 / ((iSlow65) ? 1.0 : fSlow64))));
	int iSlow67 = std::fabs(fSlow59) < 2.220446049250313e-16;
	double fSlow68 = ((iSlow67) ? 0.0 : std::exp(-(fConst1 / ((iSlow67) ? 1.0 : fSlow59))));
	double fSlow69 = double(fHslider13);
	double fSlow70 = 1.0 - fSlow62;
	double fSlow71 = 1.0 / std::max<double>(2.220446049250313e-16, double(fHslider14)) + -1.0;
	double fSlow72 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (fSlow69 - double(fHslider15)) * std::fabs(fSlow57 + -1.0));
	double fSlow73 = std::fabs(std::max<double>(0.0, fSlow56 + -2.0) + -1.0);
	double fSlow74 = double(fHslider16);
	double fSlow75 = std::max<double>(0.0, fSlow74 + -1.0);
	int iSlow76 = int(fSlow75);
	double fSlow77 = double(fHslider17);
	double fSlow78 = 0.5 * fSlow77;
	int iSlow79 = std::fabs(fSlow78) < 2.220446049250313e-16;
	double fSlow80 = ((iSlow79) ? 0.0 : std::exp(-(fConst1 / ((iSlow79) ? 1.0 : fSlow78))));
	double fSlow81 = 1.0 - fSlow43 / fSlow7;
	double fSlow82 = 1.0 / (fSlow44 / fSlow7 + 1.0);
	double fSlow83 = 1.0 / (fSlow15 * fSlow19);
	double fSlow84 = double(fHslider18);
	int iSlow85 = std::fabs(fSlow84) < 2.220446049250313e-16;
	double fSlow86 = ((iSlow85) ? 0.0 : std::exp(-(fConst1 / ((iSlow85) ? 1.0 : fSlow84))));
	int iSlow87 = std::fabs(fSlow77) < 2.220446049250313e-16;
	double fSlow88 = ((iSlow87) ? 0.0 : std::exp(-(fConst1 / ((iSlow87) ? 1.0 : fSlow77))));
	double fSlow89 = double(fHslider19);
	double fSlow90 = 1.0 - fSlow80;
	double fSlow91 = 1.0 / std::max<double>(2.220446049250313e-16, double(fHslider20)) + -1.0;
	double fSlow92 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (fSlow89 - double(fHslider21)) * std::fabs(fSlow75 + -1.0));
	double fSlow93 = std::fabs(std::max<double>(0.0, fSlow74 + -2.0) + -1.0);
	double fSlow94 = double(fHslider22);
	double fSlow95 = std::max<double>(0.0, fSlow94 + -1.0);
	int iSlow96 = int(fSlow95);
	double fSlow97 = double(fHslider23);
	double fSlow98 = 0.5 * fSlow97;
	int iSlow99 = std::fabs(fSlow98) < 2.220446049250313e-16;
	double fSlow100 = ((iSlow99) ? 0.0 : std::exp(-(fConst1 / ((iSlow99) ? 1.0 : fSlow98))));
	double fSlow101 = 1.0 - fSlow40 / fSlow14;
	double fSlow102 = 1.0 / (fSlow41 / fSlow14 + 1.0);
	double fSlow103 = 1.0 / (fSlow22 * fSlow26);
	double fSlow104 = double(fHslider24);
	int iSlow105 = std::fabs(fSlow104) < 2.220446049250313e-16;
	double fSlow106 = ((iSlow105) ? 0.0 : std::exp(-(fConst1 / ((iSlow105) ? 1.0 : fSlow104))));
	int iSlow107 = std::fabs(fSlow97) < 2.220446049250313e-16;
	double fSlow108 = ((iSlow107) ? 0.0 : std::exp(-(fConst1 / ((iSlow107) ? 1.0 : fSlow97))));
	double fSlow109 = double(fHslider25);
	double fSlow110 = 1.0 - fSlow100;
	double fSlow111 = 1.0 / std::max<double>(2.220446049250313e-16, double(fHslider26)) + -1.0;
	double fSlow112 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (fSlow109 - double(fHslider27)) * std::fabs(fSlow95 + -1.0));
	double fSlow113 = std::fabs(std::max<double>(0.0, fSlow94 + -2.0) + -1.0);
	double fSlow114 = double(fHslider28);
	double fSlow115 = std::max<double>(0.0, fSlow114 + -1.0);
	int iSlow116 = int(fSlow115);
	double fSlow117 = double(fHslider29);
	double fSlow118 = 0.5 * fSlow117;
	int iSlow119 = std::fabs(fSlow118) < 2.220446049250313e-16;
	double fSlow120 = ((iSlow119) ? 0.0 : std::exp(-(fConst1 / ((iSlow119) ? 1.0 : fSlow118))));
	double fSlow121 = 1.0 - fSlow37 / fSlow21;
	double fSlow122 = 1.0 / (fSlow38 / fSlow21 + 1.0);
	double fSlow123 = 1.0 / (fSlow29 * fSlow33);
	double fSlow124 = double(fHslider30);
	int iSlow125 = std::fabs(fSlow124) < 2.220446049250313e-16;
	double fSlow126 = ((iSlow125) ? 0.0 : std::exp(-(fConst1 / ((iSlow125) ? 1.0 : fSlow124))));
	int iSlow127 = std::fabs(fSlow117) < 2.220446049250313e-16;
	double fSlow128 = ((iSlow127) ? 0.0 : std::exp(-(fConst1 / ((iSlow127) ? 1.0 : fSlow117))));
	double fSlow129 = double(fHslider31);
	double fSlow130 = 1.0 - fSlow120;
	double fSlow131 = 1.0 / std::max<double>(2.220446049250313e-16, double(fHslider32)) + -1.0;
	double fSlow132 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (fSlow129 - double(fHslider33)) * std::fabs(fSlow115 + -1.0));
	double fSlow133 = std::fabs(std::max<double>(0.0, fSlow114 + -2.0) + -1.0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		int iTemp0 = iRec1[1] < 4096;
		double fTemp1 = double(input1[i0]);
		fVec0[0] = fTemp1;
		fRec12[0] = -(fSlow36 * (fSlow35 * fRec12[1] - (fTemp1 + fVec0[1])));
		fRec11[0] = fRec12[0] - fSlow34 * (fSlow32 * fRec11[2] + fSlow30 * fRec11[1]);
		double fTemp2 = fSlow34 * (fRec11[2] + fRec11[0] + 2.0 * fRec11[1]);
		fVec1[0] = fTemp2;
		fRec10[0] = -(fSlow39 * (fSlow37 * fRec10[1] - (fTemp2 + fVec1[1])));
		fRec9[0] = fRec10[0] - fSlow27 * (fSlow25 * fRec9[2] + fSlow23 * fRec9[1]);
		double fTemp3 = fSlow27 * (fRec9[2] + fRec9[0] + 2.0 * fRec9[1]);
		fVec2[0] = fTemp3;
		fRec8[0] = -(fSlow42 * (fSlow40 * fRec8[1] - (fTemp3 + fVec2[1])));
		fRec7[0] = fRec8[0] - fSlow20 * (fSlow18 * fRec7[2] + fSlow16 * fRec7[1]);
		double fTemp4 = fSlow20 * (fRec7[2] + fRec7[0] + 2.0 * fRec7[1]);
		fVec3[0] = fTemp4;
		fRec6[0] = -(fSlow45 * (fSlow43 * fRec6[1] - (fTemp4 + fVec3[1])));
		fRec5[0] = fRec6[0] - fSlow13 * (fSlow11 * fRec5[2] + fSlow9 * fRec5[1]);
		double fTemp5 = fSlow13 * (fRec5[2] + fRec5[0] + 2.0 * fRec5[1]);
		double fTemp6 = ((iSlow2) ? 0.0 : fTemp5);
		double fTemp7 = double(input0[i0]);
		fVec4[0] = fTemp7;
		fRec20[0] = -(fSlow36 * (fSlow35 * fRec20[1] - (fTemp7 + fVec4[1])));
		fRec19[0] = fRec20[0] - fSlow34 * (fSlow32 * fRec19[2] + fSlow30 * fRec19[1]);
		double fTemp8 = fSlow34 * (fRec19[2] + fRec19[0] + 2.0 * fRec19[1]);
		fVec5[0] = fTemp8;
		fRec18[0] = -(fSlow39 * (fSlow37 * fRec18[1] - (fTemp8 + fVec5[1])));
		fRec17[0] = fRec18[0] - fSlow27 * (fSlow25 * fRec17[2] + fSlow23 * fRec17[1]);
		double fTemp9 = fSlow27 * (fRec17[2] + fRec17[0] + 2.0 * fRec17[1]);
		fVec6[0] = fTemp9;
		fRec16[0] = -(fSlow42 * (fSlow40 * fRec16[1] - (fTemp9 + fVec6[1])));
		fRec15[0] = fRec16[0] - fSlow20 * (fSlow18 * fRec15[2] + fSlow16 * fRec15[1]);
		double fTemp10 = fSlow20 * (fRec15[2] + fRec15[0] + 2.0 * fRec15[1]);
		fVec7[0] = fTemp10;
		fRec14[0] = -(fSlow45 * (fSlow43 * fRec14[1] - (fTemp10 + fVec7[1])));
		fRec13[0] = fRec14[0] - fSlow13 * (fSlow11 * fRec13[2] + fSlow9 * fRec13[1]);
		double fTemp11 = fSlow13 * (fRec13[2] + fRec13[0] + 2.0 * fRec13[1]);
		double fTemp12 = ((iSlow2) ? 0.0 : fTemp11);
		double fTemp13 = std::fabs(std::fabs(fTemp12) + std::fabs(fTemp6));
		double fTemp14 = ((fTemp13 > fRec4[1]) ? fSlow50 : fSlow48);
		fRec4[0] = fTemp13 * (1.0 - fTemp14) + fRec4[1] * fTemp14;
		fRec3[0] = fSlow53 * fSlow52 * std::max<double>(fSlow51 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec4[0])), 0.0) + fSlow6 * fRec3[1];
		double fTemp15 = std::pow(1e+01, 0.05 * fRec3[0]);
		fRec21[0] = fSlow54 + 0.999 * fRec21[1];
		double fTemp16 = fSlow55 * fRec21[0] * ((iSlow2) ? fTemp5 : fTemp6 * fTemp15);
		double fTemp17 = fSlow55 * fRec21[0] * ((iSlow2) ? fTemp11 : fTemp12 * fTemp15);
		double fTemp18 = std::max<double>(fConst1, std::fabs(fTemp17) + std::fabs(fTemp16));
		fRec0[0] = ((iTemp0) ? fTemp18 + fRec0[1] : fTemp18);
		iRec1[0] = ((iTemp0) ? iRec1[1] + 1 : 1);
		fRec2[0] = ((iTemp0) ? fRec2[1] : 0.000244140625 * fRec0[1]);
		fVbargraph0 = FAUSTFLOAT(0.5 * fRec2[0]);
		int iTemp19 = iRec23[1] < 4096;
		fRec28[0] = -(fSlow45 * (fSlow43 * fRec28[1] - fSlow10 * (fTemp4 - fVec3[1])));
		fRec27[0] = fRec28[0] - fSlow13 * (fSlow11 * fRec27[2] + fSlow9 * fRec27[1]);
		double fTemp20 = fSlow63 * (fRec27[2] + (fRec27[0] - 2.0 * fRec27[1]));
		double fTemp21 = ((iSlow58) ? 0.0 : fTemp20);
		fRec30[0] = -(fSlow45 * (fSlow43 * fRec30[1] - fSlow10 * (fTemp10 - fVec7[1])));
		fRec29[0] = fRec30[0] - fSlow13 * (fSlow11 * fRec29[2] + fSlow9 * fRec29[1]);
		double fTemp22 = fSlow63 * (fRec29[2] + (fRec29[0] - 2.0 * fRec29[1]));
		double fTemp23 = ((iSlow58) ? 0.0 : fTemp22);
		double fTemp24 = std::fabs(std::fabs(fTemp23) + std::fabs(fTemp21));
		double fTemp25 = ((fTemp24 > fRec26[1]) ? fSlow68 : fSlow66);
		fRec26[0] = fTemp24 * (1.0 - fTemp25) + fRec26[1] * fTemp25;
		fRec25[0] = fSlow71 * fSlow70 * std::max<double>(fSlow69 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec26[0])), 0.0) + fSlow62 * fRec25[1];
		double fTemp26 = std::pow(1e+01, 0.05 * fRec25[0]);
		fRec31[0] = fSlow72 + 0.999 * fRec31[1];
		double fTemp27 = fSlow73 * fRec31[0] * ((iSlow58) ? fTemp20 : fTemp21 * fTemp26);
		double fTemp28 = fSlow73 * fRec31[0] * ((iSlow58) ? fTemp22 : fTemp23 * fTemp26);
		double fTemp29 = std::max<double>(fConst1, std::fabs(fTemp28) + std::fabs(fTemp27));
		fRec22[0] = ((iTemp19) ? fTemp29 + fRec22[1] : fTemp29);
		iRec23[0] = ((iTemp19) ? iRec23[1] + 1 : 1);
		fRec24[0] = ((iTemp19) ? fRec24[1] : 0.000244140625 * fRec22[1]);
		fVbargraph1 = FAUSTFLOAT(0.5 * fRec24[0]);
		int iTemp30 = iRec33[1] < 4096;
		double fTemp31 = fSlow9 * fRec37[1];
		fRec39[0] = -(fSlow42 * (fSlow40 * fRec39[1] - fSlow17 * (fTemp3 - fVec2[1])));
		fRec38[0] = fRec39[0] - fSlow20 * (fSlow18 * fRec38[2] + fSlow16 * fRec38[1]);
		fRec37[0] = fSlow83 * (fRec38[2] + (fRec38[0] - 2.0 * fRec38[1])) - fSlow82 * (fSlow81 * fRec37[2] + fTemp31);
		double fTemp32 = fRec37[2] + fSlow82 * (fTemp31 + fSlow81 * fRec37[0]);
		double fTemp33 = ((iSlow76) ? 0.0 : fTemp32);
		double fTemp34 = fSlow9 * fRec40[1];
		fRec42[0] = -(fSlow42 * (fSlow40 * fRec42[1] - fSlow17 * (fTemp9 - fVec6[1])));
		fRec41[0] = fRec42[0] - fSlow20 * (fSlow18 * fRec41[2] + fSlow16 * fRec41[1]);
		fRec40[0] = fSlow83 * (fRec41[2] + (fRec41[0] - 2.0 * fRec41[1])) - fSlow82 * (fSlow81 * fRec40[2] + fTemp34);
		double fTemp35 = fRec40[2] + fSlow82 * (fTemp34 + fSlow81 * fRec40[0]);
		double fTemp36 = ((iSlow76) ? 0.0 : fTemp35);
		double fTemp37 = std::fabs(std::fabs(fTemp36) + std::fabs(fTemp33));
		double fTemp38 = ((fTemp37 > fRec36[1]) ? fSlow88 : fSlow86);
		fRec36[0] = fTemp37 * (1.0 - fTemp38) + fRec36[1] * fTemp38;
		fRec35[0] = fSlow91 * fSlow90 * std::max<double>(fSlow89 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec36[0])), 0.0) + fSlow80 * fRec35[1];
		double fTemp39 = std::pow(1e+01, 0.05 * fRec35[0]);
		fRec43[0] = fSlow92 + 0.999 * fRec43[1];
		double fTemp40 = fSlow93 * fRec43[0] * ((iSlow76) ? fTemp32 : fTemp33 * fTemp39);
		double fTemp41 = fSlow93 * fRec43[0] * ((iSlow76) ? fTemp35 : fTemp36 * fTemp39);
		double fTemp42 = std::max<double>(fConst1, std::fabs(fTemp41) + std::fabs(fTemp40));
		fRec32[0] = ((iTemp30) ? fTemp42 + fRec32[1] : fTemp42);
		iRec33[0] = ((iTemp30) ? iRec33[1] + 1 : 1);
		fRec34[0] = ((iTemp30) ? fRec34[1] : 0.000244140625 * fRec32[1]);
		fVbargraph2 = FAUSTFLOAT(0.5 * fRec34[0]);
		int iTemp43 = iRec45[1] < 4096;
		double fTemp44 = fSlow9 * fRec49[1];
		double fTemp45 = fSlow16 * fRec50[1];
		fRec52[0] = -(fSlow39 * (fSlow37 * fRec52[1] - fSlow24 * (fTemp2 - fVec1[1])));
		fRec51[0] = fRec52[0] - fSlow27 * (fSlow25 * fRec51[2] + fSlow23 * fRec51[1]);
		fRec50[0] = fSlow103 * (fRec51[2] + (fRec51[0] - 2.0 * fRec51[1])) - fSlow102 * (fSlow101 * fRec50[2] + fTemp45);
		fRec49[0] = fRec50[2] + fSlow102 * (fTemp45 + fSlow101 * fRec50[0]) - fSlow82 * (fSlow81 * fRec49[2] + fTemp44);
		double fTemp46 = fRec49[2] + fSlow82 * (fTemp44 + fSlow81 * fRec49[0]);
		double fTemp47 = ((iSlow96) ? 0.0 : fTemp46);
		double fTemp48 = fSlow9 * fRec53[1];
		double fTemp49 = fSlow16 * fRec54[1];
		fRec56[0] = -(fSlow39 * (fSlow37 * fRec56[1] - fSlow24 * (fTemp8 - fVec5[1])));
		fRec55[0] = fRec56[0] - fSlow27 * (fSlow25 * fRec55[2] + fSlow23 * fRec55[1]);
		fRec54[0] = fSlow103 * (fRec55[2] + (fRec55[0] - 2.0 * fRec55[1])) - fSlow102 * (fSlow101 * fRec54[2] + fTemp49);
		fRec53[0] = fRec54[2] + fSlow102 * (fTemp49 + fSlow101 * fRec54[0]) - fSlow82 * (fSlow81 * fRec53[2] + fTemp48);
		double fTemp50 = fRec53[2] + fSlow82 * (fTemp48 + fSlow81 * fRec53[0]);
		double fTemp51 = ((iSlow96) ? 0.0 : fTemp50);
		double fTemp52 = std::fabs(std::fabs(fTemp51) + std::fabs(fTemp47));
		double fTemp53 = ((fTemp52 > fRec48[1]) ? fSlow108 : fSlow106);
		fRec48[0] = fTemp52 * (1.0 - fTemp53) + fRec48[1] * fTemp53;
		fRec47[0] = fSlow111 * fSlow110 * std::max<double>(fSlow109 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec48[0])), 0.0) + fSlow100 * fRec47[1];
		double fTemp54 = std::pow(1e+01, 0.05 * fRec47[0]);
		fRec57[0] = fSlow112 + 0.999 * fRec57[1];
		double fTemp55 = fSlow113 * fRec57[0] * ((iSlow96) ? fTemp46 : fTemp47 * fTemp54);
		double fTemp56 = fSlow113 * fRec57[0] * ((iSlow96) ? fTemp50 : fTemp51 * fTemp54);
		double fTemp57 = std::max<double>(fConst1, std::fabs(fTemp56) + std::fabs(fTemp55));
		fRec44[0] = ((iTemp43) ? fTemp57 + fRec44[1] : fTemp57);
		iRec45[0] = ((iTemp43) ? iRec45[1] + 1 : 1);
		fRec46[0] = ((iTemp43) ? fRec46[1] : 0.000244140625 * fRec44[1]);
		fVbargraph3 = FAUSTFLOAT(0.5 * fRec46[0]);
		int iTemp58 = iRec59[1] < 4096;
		double fTemp59 = fSlow9 * fRec63[1];
		double fTemp60 = fSlow16 * fRec64[1];
		double fTemp61 = fSlow23 * fRec65[1];
		fRec67[0] = -(fSlow36 * (fSlow35 * fRec67[1] - fSlow31 * (fTemp1 - fVec0[1])));
		fRec66[0] = fRec67[0] - fSlow34 * (fSlow32 * fRec66[2] + fSlow30 * fRec66[1]);
		fRec65[0] = fSlow123 * (fRec66[2] + (fRec66[0] - 2.0 * fRec66[1])) - fSlow122 * (fSlow121 * fRec65[2] + fTemp61);
		fRec64[0] = fRec65[2] + fSlow122 * (fTemp61 + fSlow121 * fRec65[0]) - fSlow102 * (fSlow101 * fRec64[2] + fTemp60);
		fRec63[0] = fRec64[2] + fSlow102 * (fTemp60 + fSlow101 * fRec64[0]) - fSlow82 * (fSlow81 * fRec63[2] + fTemp59);
		double fTemp62 = fRec63[2] + fSlow82 * (fTemp59 + fSlow81 * fRec63[0]);
		double fTemp63 = ((iSlow116) ? 0.0 : fTemp62);
		double fTemp64 = fSlow9 * fRec68[1];
		double fTemp65 = fSlow16 * fRec69[1];
		double fTemp66 = fSlow23 * fRec70[1];
		fRec72[0] = -(fSlow36 * (fSlow35 * fRec72[1] - fSlow31 * (fTemp7 - fVec4[1])));
		fRec71[0] = fRec72[0] - fSlow34 * (fSlow32 * fRec71[2] + fSlow30 * fRec71[1]);
		fRec70[0] = fSlow123 * (fRec71[2] + (fRec71[0] - 2.0 * fRec71[1])) - fSlow122 * (fSlow121 * fRec70[2] + fTemp66);
		fRec69[0] = fRec70[2] + fSlow122 * (fTemp66 + fSlow121 * fRec70[0]) - fSlow102 * (fSlow101 * fRec69[2] + fTemp65);
		fRec68[0] = fRec69[2] + fSlow102 * (fTemp65 + fSlow101 * fRec69[0]) - fSlow82 * (fSlow81 * fRec68[2] + fTemp64);
		double fTemp67 = fRec68[2] + fSlow82 * (fTemp64 + fSlow81 * fRec68[0]);
		double fTemp68 = ((iSlow116) ? 0.0 : fTemp67);
		double fTemp69 = std::fabs(std::fabs(fTemp68) + std::fabs(fTemp63));
		double fTemp70 = ((fTemp69 > fRec62[1]) ? fSlow128 : fSlow126);
		fRec62[0] = fTemp69 * (1.0 - fTemp70) + fRec62[1] * fTemp70;
		fRec61[0] = fSlow131 * fSlow130 * std::max<double>(fSlow129 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec62[0])), 0.0) + fSlow120 * fRec61[1];
		double fTemp71 = std::pow(1e+01, 0.05 * fRec61[0]);
		fRec73[0] = fSlow132 + 0.999 * fRec73[1];
		double fTemp72 = fSlow133 * fRec73[0] * ((iSlow116) ? fTemp62 : fTemp63 * fTemp71);
		double fTemp73 = fSlow133 * fRec73[0] * ((iSlow116) ? fTemp67 : fTemp68 * fTemp71);
		double fTemp74 = std::max<double>(fConst1, std::fabs(fTemp73) + std::fabs(fTemp72));
		fRec58[0] = ((iTemp58) ? fTemp74 + fRec58[1] : fTemp74);
		iRec59[0] = ((iTemp58) ? iRec59[1] + 1 : 1);
		fRec60[0] = ((iTemp58) ? fRec60[1] : 0.000244140625 * fRec58[1]);
		fVbargraph4 = FAUSTFLOAT(0.5 * fRec60[0]);
		output0[i0] = FAUSTFLOAT(fTemp73 + fTemp56 + fTemp41 + fTemp28 + fTemp17);
		output1[i0] = FAUSTFLOAT(fTemp16 + fTemp27 + fTemp40 + fTemp72 + fTemp55);
		fVec0[1] = fVec0[0];
		fRec12[1] = fRec12[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fVec1[1] = fVec1[0];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fVec2[1] = fVec2[0];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fVec3[1] = fVec3[0];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fVec4[1] = fVec4[0];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fVec5[1] = fVec5[0];
		fRec18[1] = fRec18[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fVec6[1] = fVec6[0];
		fRec16[1] = fRec16[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		fVec7[1] = fVec7[0];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec21[1] = fRec21[0];
		fRec0[1] = fRec0[0];
		iRec1[1] = iRec1[0];
		fRec2[1] = fRec2[0];
		fRec28[1] = fRec28[0];
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		fRec30[1] = fRec30[0];
		fRec29[2] = fRec29[1];
		fRec29[1] = fRec29[0];
		fRec26[1] = fRec26[0];
		fRec25[1] = fRec25[0];
		fRec31[1] = fRec31[0];
		fRec22[1] = fRec22[0];
		iRec23[1] = iRec23[0];
		fRec24[1] = fRec24[0];
		fRec39[1] = fRec39[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fRec42[1] = fRec42[0];
		fRec41[2] = fRec41[1];
		fRec41[1] = fRec41[0];
		fRec40[2] = fRec40[1];
		fRec40[1] = fRec40[0];
		fRec36[1] = fRec36[0];
		fRec35[1] = fRec35[0];
		fRec43[1] = fRec43[0];
		fRec32[1] = fRec32[0];
		iRec33[1] = iRec33[0];
		fRec34[1] = fRec34[0];
		fRec52[1] = fRec52[0];
		fRec51[2] = fRec51[1];
		fRec51[1] = fRec51[0];
		fRec50[2] = fRec50[1];
		fRec50[1] = fRec50[0];
		fRec49[2] = fRec49[1];
		fRec49[1] = fRec49[0];
		fRec56[1] = fRec56[0];
		fRec55[2] = fRec55[1];
		fRec55[1] = fRec55[0];
		fRec54[2] = fRec54[1];
		fRec54[1] = fRec54[0];
		fRec53[2] = fRec53[1];
		fRec53[1] = fRec53[0];
		fRec48[1] = fRec48[0];
		fRec47[1] = fRec47[0];
		fRec57[1] = fRec57[0];
		fRec44[1] = fRec44[0];
		iRec45[1] = iRec45[0];
		fRec46[1] = fRec46[0];
		fRec67[1] = fRec67[0];
		fRec66[2] = fRec66[1];
		fRec66[1] = fRec66[0];
		fRec65[2] = fRec65[1];
		fRec65[1] = fRec65[0];
		fRec64[2] = fRec64[1];
		fRec64[1] = fRec64[0];
		fRec63[2] = fRec63[1];
		fRec63[1] = fRec63[0];
		fRec72[1] = fRec72[0];
		fRec71[2] = fRec71[1];
		fRec71[1] = fRec71[0];
		fRec70[2] = fRec70[1];
		fRec70[1] = fRec70[0];
		fRec69[2] = fRec69[1];
		fRec69[1] = fRec69[0];
		fRec68[2] = fRec68[1];
		fRec68[1] = fRec68[0];
		fRec62[1] = fRec62[0];
		fRec61[1] = fRec61[0];
		fRec73[1] = fRec73[0];
		fRec58[1] = fRec58[0];
		iRec59[1] = iRec59[0];
		fRec60[1] = fRec60[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	static const value_pair fHslider0_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerFloatVar("mbcs.Mode1","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),&fHslider0, 1.0, 1.0, 3.0, 1.0, fHslider0_values);
	static const value_pair fHslider10_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerFloatVar("mbcs.Mode2","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),&fHslider10, 1.0, 1.0, 3.0, 1.0, fHslider10_values);
	static const value_pair fHslider16_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerFloatVar("mbcs.Mode3","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),&fHslider16, 1.0, 1.0, 3.0, 1.0, fHslider16_values);
	static const value_pair fHslider22_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerFloatVar("mbcs.Mode4","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),&fHslider22, 1.0, 1.0, 3.0, 1.0, fHslider22_values);
	static const value_pair fHslider28_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	reg.registerFloatVar("mbcs.Mode5","","S",N_("Compress or Mute the selected band, or Bypass The Compressor"),&fHslider28, 1.0, 1.0, 3.0, 1.0, fHslider28_values);
	reg.registerFloatVar("mbcs.Makeup1","","S",N_("Post amplification and threshold"),&fHslider7, 13.0, -5e+01, 5e+01, 0.1, 0);
	reg.registerFloatVar("mbcs.Makeup2","","S",N_("Post amplification and threshold"),&fHslider13, 1e+01, -5e+01, 5e+01, 0.1, 0);
	reg.registerFloatVar("mbcs.Makeup3","","S",N_("Post amplification and threshold"),&fHslider19, 4.0, -5e+01, 5e+01, 0.1, 0);
	reg.registerFloatVar("mbcs.Makeup4","","S",N_("Post amplification and threshold"),&fHslider25, 8.0, -5e+01, 5e+01, 0.1, 0);
	reg.registerFloatVar("mbcs.Makeup5","","S",N_("Post amplification and threshold"),&fHslider31, 11.0, -5e+01, 5e+01, 0.1, 0);
	reg.registerFloatVar("mbcs.Makeup-Threshold1","","S",N_("Threshold correction, an anticlip measure"),&fHslider9, 2.0, 0.0, 1e+01, 0.1, 0);
	reg.registerFloatVar("mbcs.Makeup-Threshold2","","S",N_("Threshold correction, an anticlip measure"),&fHslider15, 2.0, 0.0, 1e+01, 0.1, 0);
	reg.registerFloatVar("mbcs.Makeup-Threshold3","","S",N_("Threshold correction, an anticlip measure"),&fHslider21, 2.0, 0.0, 1e+01, 0.1, 0);
	reg.registerFloatVar("mbcs.Makeup-Threshold4","","S",N_("Threshold correction, an anticlip measure"),&fHslider27, 2.0, 0.0, 1e+01, 0.1, 0);
	reg.registerFloatVar("mbcs.Makeup-Threshold5","","S",N_("Threshold correction, an anticlip measure"),&fHslider33, 2.0, 0.0, 1e+01, 0.1, 0);
	reg.registerFloatVar("mbcs.Ratio1","","S",N_("Compression ratio"),&fHslider8, 2.0, 1.0, 1e+02, 0.1, 0);
	reg.registerFloatVar("mbcs.Ratio2","","S",N_("Compression ratio"),&fHslider14, 2.0, 1.0, 1e+02, 0.1, 0);
	reg.registerFloatVar("mbcs.Ratio3","","S",N_("Compression ratio"),&fHslider20, 2.0, 1.0, 1e+02, 0.1, 0);
	reg.registerFloatVar("mbcs.Ratio4","","S",N_("Compression ratio"),&fHslider26, 2.0, 1.0, 1e+02, 0.1, 0);
	reg.registerFloatVar("mbcs.Ratio5","","S",N_("Compression ratio"),&fHslider32, 2.0, 1.0, 1e+02, 0.1, 0);
	reg.registerFloatVar("mbcs.Attack1","","S",N_("Time before the compressor starts to kick in"),&fHslider1, 0.012, 0.001, 1.0, 0.001, 0);
	reg.registerFloatVar("mbcs.Attack2","","S",N_("Time before the compressor starts to kick in"),&fHslider11, 0.012, 0.001, 1.0, 0.001, 0);
	reg.registerFloatVar("mbcs.Attack3","","S",N_("Time before the compressor starts to kick in"),&fHslider17, 0.012, 0.001, 1.0, 0.001, 0);
	reg.registerFloatVar("mbcs.Attack4","","S",N_("Time before the compressor starts to kick in"),&fHslider23, 0.012, 0.001, 1.0, 0.001, 0);
	reg.registerFloatVar("mbcs.Attack5","","S",N_("Time before the compressor starts to kick in"),&fHslider29, 0.012, 0.001, 1.0, 0.001, 0);
	reg.registerFloatVar("mbcs.Release1","","S",N_("Time before the compressor releases the sound"),&fHslider6, 1.25, 0.01, 1e+01, 0.01, 0);
	reg.registerFloatVar("mbcs.Release2","","S",N_("Time before the compressor releases the sound"),&fHslider12, 1.25, 0.01, 1e+01, 0.01, 0);
	reg.registerFloatVar("mbcs.Release3","","S",N_("Time before the compressor releases the sound"),&fHslider18, 1.25, 0.01, 1e+01, 0.01, 0);
	reg.registerFloatVar("mbcs.Release4","","S",N_("Time before the compressor releases the sound"),&fHslider24, 1.25, 0.01, 1e+01, 0.01, 0);
	reg.registerFloatVar("mbcs.Release5","","S",N_("Time before the compressor releases the sound"),&fHslider30, 1.25, 0.01, 1e+01, 0.01, 0);
	reg.registerFloatVar("mbcs.crossover_b1_b2",N_("Crossover B1-B2 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fHslider2, 8e+01, 2e+01, 2e+04, 1.08, 0);
	reg.registerFloatVar("mbcs.crossover_b2_b3",N_("Crossover B2-B3 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fHslider3, 2.1e+02, 2e+01, 2e+04, 1.08, 0);
	reg.registerFloatVar("mbcs.crossover_b3_b4",N_("Crossover B3-B4 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fHslider4, 1.7e+03, 2e+01, 2e+04, 1.08, 0);
	reg.registerFloatVar("mbcs.crossover_b4_b5",N_("Crossover B4-B5 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fHslider5, 5e+03, 2e+01, 2e+04, 1.08, 0);
	reg.registerFloatVar("mbcs.v1","","SOLN",N_("Sum of Band1"),&fVbargraph0, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("mbcs.v2","","SOLN",N_("Sum of Band2"),&fVbargraph1, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("mbcs.v3","","SOLN",N_("Sum of Band3"),&fVbargraph2, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("mbcs.v4","","SOLN",N_("Sum of Band4"),&fVbargraph3, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("mbcs.v5","","SOLN",N_("Sum of Band5"),&fVbargraph4, 0, -7e+01, 5.0, 0, 0);
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
                  <object class=\"GtkNotebook\" id=\"notebook\">\n\
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
                                <property name=\"spacing\">15</property>\n\
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
                                        <property name=\"var_id\">mbcs.Ratio1</property>\n\
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
                                        <property name=\"var_id\">mbcs.Makeup1</property>\n\
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
                                        <property name=\"var_id\">mbcs.Makeup-Threshold1</property>\n\
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
                                <property name=\"var_id\">mbcs.Mode1</property>\n\
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
                            <property name=\"expand\">False</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkGrid\" id=\"table1\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"halign\">center</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <property name=\"column_homogeneous\">True</property>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob1\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.Attack1</property>\n\
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
                                <property name=\"var_id\">mbcs.crossover_b1_b2</property>\n\
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
                                <property name=\"var_id\">mbcs.Release1</property>\n\
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
                                <property name=\"spacing\">15</property>\n\
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
                                        <property name=\"var_id\">mbcs.Ratio2</property>\n\
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
                                        <property name=\"var_id\">mbcs.Makeup2</property>\n\
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
                                        <property name=\"var_id\">mbcs.Makeup-Threshold2</property>\n\
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
                                <property name=\"var_id\">mbcs.Mode2</property>\n\
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
                            <property name=\"expand\">False</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkGrid\" id=\"table2\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"halign\">center</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <property name=\"column_homogeneous\">True</property>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob5\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.Attack2</property>\n\
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
                                <property name=\"var_id\">mbcs.crossover_b2_b3</property>\n\
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
                                <property name=\"var_id\">mbcs.crossover_b1_b2</property>\n\
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
                                <property name=\"var_id\">mbcs.Release2</property>\n\
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
                                <property name=\"spacing\">15</property>\n\
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
                                        <property name=\"var_id\">mbcs.Ratio3</property>\n\
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
                                        <property name=\"var_id\">mbcs.Makeup3</property>\n\
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
                                        <property name=\"var_id\">mbcs.Makeup-Threshold3</property>\n\
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
                                <property name=\"var_id\">mbcs.Mode3</property>\n\
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
                            <property name=\"expand\">False</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkGrid\" id=\"table3\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"halign\">center</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <property name=\"column_homogeneous\">True</property>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob9\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.Attack3</property>\n\
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
                                <property name=\"var_id\">mbcs.crossover_b3_b4</property>\n\
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
                                <property name=\"var_id\">mbcs.crossover_b2_b3</property>\n\
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
                                <property name=\"var_id\">mbcs.Release3</property>\n\
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
                                <property name=\"spacing\">15</property>\n\
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
                                        <property name=\"var_id\">mbcs.Ratio4</property>\n\
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
                                        <property name=\"var_id\">mbcs.Makeup4</property>\n\
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
                                        <property name=\"var_id\">mbcs.Makeup-Threshold4</property>\n\
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
                                <property name=\"var_id\">mbcs.Mode4</property>\n\
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
                            <property name=\"expand\">False</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkGrid\" id=\"table4\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"halign\">center</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <property name=\"column_homogeneous\">True</property>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob13\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.Attack4</property>\n\
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
                                <property name=\"var_id\">mbcs.crossover_b4_b5</property>\n\
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
                                <property name=\"var_id\">mbcs.crossover_b3_b4</property>\n\
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
                                <property name=\"var_id\">mbcs.Release4</property>\n\
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
                                <property name=\"spacing\">15</property>\n\
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
                                        <property name=\"var_id\">mbcs.Ratio5</property>\n\
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
                                        <property name=\"var_id\">mbcs.Makeup5</property>\n\
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
                                        <property name=\"var_id\">mbcs.Makeup-Threshold5</property>\n\
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
                                <property name=\"var_id\">mbcs.Mode5</property>\n\
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
                            <property name=\"expand\">False</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkGrid\" id=\"table5\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"halign\">center</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <property name=\"column_homogeneous\">True</property>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob17\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbcs.Attack5</property>\n\
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
                                <property name=\"var_id\">mbcs.crossover_b4_b5</property>\n\
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
                                <property name=\"var_id\">mbcs.Release5</property>\n\
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
                    <style>\n\
                      <class name=\"tab_rack\"/>\n\
                    </style>\n\
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
                        <property name=\"margin_bottom\">4</property>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter1\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"tooltip_text\" translatable=\"yes\">Sum of Band1 </property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbcs.v1</property>\n\
                            <property name=\"falloff\">True</property>\n\
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
                            <property name=\"tooltip_text\" translatable=\"yes\">Sum of Band2</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbcs.v2</property>\n\
                            <property name=\"falloff\">True</property>\n\
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
                            <property name=\"tooltip_text\" translatable=\"yes\">Sum of Band3</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbcs.v3</property>\n\
                            <property name=\"falloff\">True</property>\n\
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
                            <property name=\"tooltip_text\" translatable=\"yes\">Sum of Band4</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbcs.v4</property>\n\
                            <property name=\"falloff\">True</property>\n\
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
                            <property name=\"tooltip_text\" translatable=\"yes\">Sum of Band5</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbcs.v5</property>\n\
                            <property name=\"falloff\">True</property>\n\
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
#define PARAM(p) ("mbcs" "." p)

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
b.create_small_rackknob(PARAM("Release1") ,N_("Release"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 2"));
b.openpaintampBox("");
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Makeup2"), N_("Makeup (db)"));
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
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b3_b4"),N_("Low (hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b4_b5"),N_("High (hz)"));
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
b.create_small_rackknob(PARAM("Makeup-Threshold5"), N_( "Anticlip (db)"));
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

} // end namespace mbcs
} // end namespace pluginlib
