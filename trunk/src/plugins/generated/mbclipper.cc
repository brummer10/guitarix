// generated from file '../src/plugins/mbclipper.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "clipping.h"

namespace pluginlib {
namespace mbclipper {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT fVslider0;
	int iVec0[2];
	double fRec0[2];
	double fConst0;
	double fConst1;
	FAUSTFLOAT fHslider0;
	double fRec4[2];
	double fConst2;
	FAUSTFLOAT fHslider1;
	double fRec10[2];
	double fVec1[2];
	double fRec9[2];
	double fRec8[3];
	FAUSTFLOAT fHslider2;
	double fRec7[3];
	FAUSTFLOAT fHslider3;
	double fRec6[3];
	FAUSTFLOAT fHslider4;
	double fRec5[3];
	double fRec1[2];
	int iRec2[2];
	double fRec3[2];
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT fHslider5;
	double fRec14[2];
	double fRec20[2];
	double fRec19[3];
	double fVec2[2];
	double fRec18[2];
	double fRec17[3];
	double fRec16[3];
	double fRec15[3];
	double fRec11[2];
	int iRec12[2];
	double fRec13[2];
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT fHslider6;
	double fRec24[2];
	double fRec29[2];
	double fRec28[3];
	double fVec3[2];
	double fRec27[2];
	double fRec26[3];
	double fRec25[3];
	double fRec21[2];
	int iRec22[2];
	double fRec23[2];
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT fHslider7;
	double fRec33[2];
	double fRec37[2];
	double fRec36[3];
	double fVec4[2];
	double fRec35[2];
	double fRec34[3];
	double fRec30[2];
	int iRec31[2];
	double fRec32[2];
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT fHslider8;
	double fRec41[2];
	double fRec43[2];
	double fRec42[3];
	double fRec38[2];
	int iRec39[2];
	double fRec40[2];
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
	id = "mbclip";
	name = N_("MultiBand Clipper");
	groups = 0;
	description = N_("MultiBand Clipper"); // description (tooltip)
	category = N_("Distortion");       // category
	shortname = N_("MB Clipper");     // shortname
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) iVec0[l0] = 0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec0[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec4[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec10[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fVec1[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec9[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec8[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRec7[l7] = 0.0;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec6[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec5[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec1[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) iRec2[l11] = 0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec3[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec14[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec20[l14] = 0.0;
	for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) fRec19[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fVec2[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec18[l17] = 0.0;
	for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) fRec17[l18] = 0.0;
	for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) fRec16[l19] = 0.0;
	for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) fRec15[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec11[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) iRec12[l22] = 0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fRec13[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec24[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fRec29[l25] = 0.0;
	for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) fRec28[l26] = 0.0;
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) fVec3[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec27[l28] = 0.0;
	for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) fRec26[l29] = 0.0;
	for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) fRec25[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fRec21[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) iRec22[l32] = 0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fRec23[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec33[l34] = 0.0;
	for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) fRec37[l35] = 0.0;
	for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) fRec36[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fVec4[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fRec35[l38] = 0.0;
	for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) fRec34[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fRec30[l40] = 0.0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) iRec31[l41] = 0;
	for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) fRec32[l42] = 0.0;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fRec41[l43] = 0.0;
	for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) fRec43[l44] = 0.0;
	for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) fRec42[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec38[l46] = 0.0;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) iRec39[l47] = 0;
	for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) fRec40[l48] = 0.0;
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
	fVslider0 = FAUSTFLOAT(0.0);
	fHslider0 = FAUSTFLOAT(0.10000000000000001);
	fHslider1 = FAUSTFLOAT(5000.0);
	fHslider2 = FAUSTFLOAT(1700.0);
	fHslider3 = FAUSTFLOAT(210.0);
	fHslider4 = FAUSTFLOAT(80.0);
	fHslider5 = FAUSTFLOAT(0.33000000000000002);
	fHslider6 = FAUSTFLOAT(0.65000000000000002);
	fHslider7 = FAUSTFLOAT(0.5);
	fHslider8 = FAUSTFLOAT(0.33000000000000002);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider0))));
	double fSlow1 = (0.0010000000000000009 * double(fHslider0));
	double fSlow2 = std::tan((fConst2 * double(fHslider1)));
	double fSlow3 = (1.0 / fSlow2);
	double fSlow4 = (((fSlow3 + 1.0000000000000004) / fSlow2) + 1.0);
	double fSlow5 = (1.0 / fSlow4);
	double fSlow6 = mydsp_faustpower2_f(fSlow2);
	double fSlow7 = (1.0 / fSlow6);
	double fSlow8 = (fSlow3 + 1.0);
	double fSlow9 = (0.0 - (1.0 / (fSlow8 * fSlow2)));
	double fSlow10 = (1.0 / fSlow8);
	double fSlow11 = (1.0 - fSlow3);
	double fSlow12 = (((fSlow3 + -1.0000000000000004) / fSlow2) + 1.0);
	double fSlow13 = (2.0 * (1.0 - fSlow7));
	double fSlow14 = (0.0 - (2.0 / fSlow6));
	double fSlow15 = std::tan((fConst2 * double(fHslider2)));
	double fSlow16 = (1.0 / fSlow15);
	double fSlow17 = (fSlow16 + 1.0);
	double fSlow18 = (1.0 / ((fSlow17 / fSlow15) + 1.0));
	double fSlow19 = (1.0 - fSlow16);
	double fSlow20 = (1.0 - (fSlow19 / fSlow15));
	double fSlow21 = mydsp_faustpower2_f(fSlow15);
	double fSlow22 = (1.0 / fSlow21);
	double fSlow23 = (2.0 * (1.0 - fSlow22));
	double fSlow24 = std::tan((fConst2 * double(fHslider3)));
	double fSlow25 = (1.0 / fSlow24);
	double fSlow26 = (fSlow25 + 1.0);
	double fSlow27 = (1.0 / ((fSlow26 / fSlow24) + 1.0));
	double fSlow28 = (1.0 - fSlow25);
	double fSlow29 = (1.0 - (fSlow28 / fSlow24));
	double fSlow30 = mydsp_faustpower2_f(fSlow24);
	double fSlow31 = (1.0 / fSlow30);
	double fSlow32 = (2.0 * (1.0 - fSlow31));
	double fSlow33 = std::tan((fConst2 * double(fHslider4)));
	double fSlow34 = (1.0 / fSlow33);
	double fSlow35 = (fSlow34 + 1.0);
	double fSlow36 = (1.0 / ((fSlow35 / fSlow33) + 1.0));
	double fSlow37 = (1.0 - fSlow34);
	double fSlow38 = (1.0 - (fSlow37 / fSlow33));
	double fSlow39 = mydsp_faustpower2_f(fSlow33);
	double fSlow40 = (1.0 / fSlow39);
	double fSlow41 = (2.0 * (1.0 - fSlow40));
	double fSlow42 = (0.0010000000000000009 * double(fHslider5));
	double fSlow43 = (((fSlow16 + 1.0000000000000004) / fSlow15) + 1.0);
	double fSlow44 = (1.0 / fSlow43);
	double fSlow45 = (0.0 - (1.0 / (fSlow15 * fSlow17)));
	double fSlow46 = (1.0 / fSlow17);
	double fSlow47 = (1.0 / (fSlow4 * fSlow15));
	double fSlow48 = (((fSlow16 + -1.0000000000000004) / fSlow15) + 1.0);
	double fSlow49 = (0.0 - (2.0 / fSlow21));
	double fSlow50 = (0.0010000000000000009 * double(fHslider6));
	double fSlow51 = (((fSlow25 + 1.0000000000000004) / fSlow24) + 1.0);
	double fSlow52 = (1.0 / fSlow51);
	double fSlow53 = (0.0 - (1.0 / (fSlow24 * fSlow26)));
	double fSlow54 = (1.0 / fSlow26);
	double fSlow55 = (1.0 / (fSlow43 * fSlow24));
	double fSlow56 = (((fSlow25 + -1.0000000000000004) / fSlow24) + 1.0);
	double fSlow57 = (0.0 - (2.0 / fSlow30));
	double fSlow58 = (0.0010000000000000009 * double(fHslider7));
	double fSlow59 = (1.0 / (((fSlow34 + 1.0000000000000004) / fSlow33) + 1.0));
	double fSlow60 = (0.0 - (1.0 / (fSlow33 * fSlow35)));
	double fSlow61 = (1.0 / fSlow35);
	double fSlow62 = (1.0 / (fSlow51 * fSlow33));
	double fSlow63 = (((fSlow34 + -1.0000000000000004) / fSlow33) + 1.0);
	double fSlow64 = (0.0 - (2.0 / fSlow39));
	double fSlow65 = (0.0010000000000000009 * double(fHslider8));
	for (int i = 0; (i < count); i = (i + 1)) {
		iVec0[0] = 1;
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		int iTemp0 = (iRec2[1] < 4096);
		fRec4[0] = (fSlow1 + (0.999 * fRec4[1]));
		double fTemp1 = std::pow(10.0, (2.0 * fRec4[0]));
		fRec10[0] = ((9.9999999999999995e-21 * double((1 - iVec0[1]))) - fRec10[1]);
		double fTemp2 = (fRec10[0] + double(input0[i]));
		fVec1[0] = fTemp2;
		fRec9[0] = ((fSlow9 * fVec1[1]) - (fSlow10 * ((fSlow11 * fRec9[1]) - (fSlow3 * fTemp2))));
		fRec8[0] = (fRec9[0] - (fSlow5 * ((fSlow12 * fRec8[2]) + (fSlow13 * fRec8[1]))));
		double fTemp3 = (fSlow23 * fRec7[1]);
		fRec7[0] = ((fSlow5 * (((fSlow7 * fRec8[0]) + (fSlow14 * fRec8[1])) + (fSlow7 * fRec8[2]))) - (fSlow18 * ((fSlow20 * fRec7[2]) + fTemp3)));
		double fTemp4 = (fSlow32 * fRec6[1]);
		fRec6[0] = ((fRec7[2] + (fSlow18 * (fTemp3 + (fSlow20 * fRec7[0])))) - (fSlow27 * ((fSlow29 * fRec6[2]) + fTemp4)));
		double fTemp5 = (fSlow41 * fRec5[1]);
		fRec5[0] = ((fRec6[2] + (fSlow27 * (fTemp4 + (fSlow29 * fRec6[0])))) - (fSlow36 * ((fSlow38 * fRec5[2]) + fTemp5)));
		double fTemp6 = (std::max<double>(1.0, (1.0 / fTemp1)) * double(symclip(double((fTemp1 * (fRec5[2] + (fSlow36 * (fTemp5 + (fSlow38 * fRec5[0])))))))));
		double fTemp7 = std::max<double>(fConst1, std::fabs(fTemp6));
		fRec1[0] = (iTemp0?(fTemp7 + fRec1[1]):fTemp7);
		iRec2[0] = (iTemp0?(iRec2[1] + 1):1);
		fRec3[0] = (iTemp0?fRec3[1]:(0.000244140625 * fRec1[1]));
		fVbargraph0 = FAUSTFLOAT(fRec3[0]);
		int iTemp8 = (iRec12[1] < 4096);
		fRec14[0] = (fSlow42 + (0.999 * fRec14[1]));
		double fTemp9 = std::pow(10.0, (2.0 * fRec14[0]));
		fRec20[0] = (0.0 - (fSlow10 * ((fSlow11 * fRec20[1]) - (fTemp2 + fVec1[1]))));
		fRec19[0] = (fRec20[0] - (fSlow5 * ((fSlow12 * fRec19[2]) + (fSlow13 * fRec19[1]))));
		double fTemp10 = (fRec19[2] + (fRec19[0] + (2.0 * fRec19[1])));
		double fTemp11 = (fSlow5 * fTemp10);
		fVec2[0] = fTemp11;
		fRec18[0] = ((fSlow45 * fVec2[1]) - (fSlow46 * ((fSlow19 * fRec18[1]) - (fSlow47 * fTemp10))));
		fRec17[0] = (fRec18[0] - (fSlow44 * ((fSlow48 * fRec17[2]) + (fSlow23 * fRec17[1]))));
		double fTemp12 = (fSlow32 * fRec16[1]);
		fRec16[0] = ((fSlow44 * (((fSlow22 * fRec17[0]) + (fSlow49 * fRec17[1])) + (fSlow22 * fRec17[2]))) - (fSlow27 * ((fSlow29 * fRec16[2]) + fTemp12)));
		double fTemp13 = (fSlow41 * fRec15[1]);
		fRec15[0] = ((fRec16[2] + (fSlow27 * (fTemp12 + (fSlow29 * fRec16[0])))) - (fSlow36 * ((fSlow38 * fRec15[2]) + fTemp13)));
		double fTemp14 = (std::max<double>(1.0, (1.0 / fTemp9)) * double(symclip(double((fTemp9 * (fRec15[2] + (fSlow36 * (fTemp13 + (fSlow38 * fRec15[0])))))))));
		double fTemp15 = std::max<double>(fConst1, std::fabs(fTemp14));
		fRec11[0] = (iTemp8?(fTemp15 + fRec11[1]):fTemp15);
		iRec12[0] = (iTemp8?(iRec12[1] + 1):1);
		fRec13[0] = (iTemp8?fRec13[1]:(0.000244140625 * fRec11[1]));
		fVbargraph1 = FAUSTFLOAT(fRec13[0]);
		int iTemp16 = (iRec22[1] < 4096);
		fRec24[0] = (fSlow50 + (0.999 * fRec24[1]));
		double fTemp17 = std::pow(10.0, (2.0 * fRec24[0]));
		fRec29[0] = (0.0 - (fSlow46 * ((fSlow19 * fRec29[1]) - (fTemp11 + fVec2[1]))));
		fRec28[0] = (fRec29[0] - (fSlow44 * ((fSlow48 * fRec28[2]) + (fSlow23 * fRec28[1]))));
		double fTemp18 = (fRec28[2] + (fRec28[0] + (2.0 * fRec28[1])));
		double fTemp19 = (fSlow44 * fTemp18);
		fVec3[0] = fTemp19;
		fRec27[0] = ((fSlow53 * fVec3[1]) - (fSlow54 * ((fSlow28 * fRec27[1]) - (fSlow55 * fTemp18))));
		fRec26[0] = (fRec27[0] - (fSlow52 * ((fSlow56 * fRec26[2]) + (fSlow32 * fRec26[1]))));
		double fTemp20 = (fSlow41 * fRec25[1]);
		fRec25[0] = ((fSlow52 * (((fSlow31 * fRec26[0]) + (fSlow57 * fRec26[1])) + (fSlow31 * fRec26[2]))) - (fSlow36 * ((fSlow38 * fRec25[2]) + fTemp20)));
		double fTemp21 = (std::max<double>(1.0, (1.0 / fTemp17)) * double(symclip(double((fTemp17 * (fRec25[2] + (fSlow36 * (fTemp20 + (fSlow38 * fRec25[0])))))))));
		double fTemp22 = std::max<double>(fConst1, std::fabs(fTemp21));
		fRec21[0] = (iTemp16?(fTemp22 + fRec21[1]):fTemp22);
		iRec22[0] = (iTemp16?(iRec22[1] + 1):1);
		fRec23[0] = (iTemp16?fRec23[1]:(0.000244140625 * fRec21[1]));
		fVbargraph2 = FAUSTFLOAT(fRec23[0]);
		int iTemp23 = (iRec31[1] < 4096);
		fRec33[0] = (fSlow58 + (0.999 * fRec33[1]));
		double fTemp24 = std::pow(10.0, (2.0 * fRec33[0]));
		fRec37[0] = (0.0 - (fSlow54 * ((fSlow28 * fRec37[1]) - (fTemp19 + fVec3[1]))));
		fRec36[0] = (fRec37[0] - (fSlow52 * ((fSlow56 * fRec36[2]) + (fSlow32 * fRec36[1]))));
		double fTemp25 = (fRec36[2] + (fRec36[0] + (2.0 * fRec36[1])));
		double fTemp26 = (fSlow52 * fTemp25);
		fVec4[0] = fTemp26;
		fRec35[0] = ((fSlow60 * fVec4[1]) - (fSlow61 * ((fSlow37 * fRec35[1]) - (fSlow62 * fTemp25))));
		fRec34[0] = (fRec35[0] - (fSlow59 * ((fSlow63 * fRec34[2]) + (fSlow41 * fRec34[1]))));
		double fTemp27 = (std::max<double>(1.0, (1.0 / fTemp24)) * double(symclip(double((fSlow59 * (fTemp24 * (((fSlow40 * fRec34[0]) + (fSlow64 * fRec34[1])) + (fSlow40 * fRec34[2]))))))));
		double fTemp28 = std::max<double>(fConst1, std::fabs(fTemp27));
		fRec30[0] = (iTemp23?(fTemp28 + fRec30[1]):fTemp28);
		iRec31[0] = (iTemp23?(iRec31[1] + 1):1);
		fRec32[0] = (iTemp23?fRec32[1]:(0.000244140625 * fRec30[1]));
		fVbargraph3 = FAUSTFLOAT(fRec32[0]);
		int iTemp29 = (iRec39[1] < 4096);
		fRec41[0] = (fSlow65 + (0.999 * fRec41[1]));
		double fTemp30 = std::pow(10.0, (2.0 * fRec41[0]));
		fRec43[0] = (0.0 - (fSlow61 * ((fSlow37 * fRec43[1]) - (fTemp26 + fVec4[1]))));
		fRec42[0] = (fRec43[0] - (fSlow59 * ((fSlow63 * fRec42[2]) + (fSlow41 * fRec42[1]))));
		double fTemp31 = (std::max<double>(1.0, (1.0 / fTemp30)) * double(symclip(double((fSlow59 * (fTemp30 * (fRec42[2] + (fRec42[0] + (2.0 * fRec42[1])))))))));
		double fTemp32 = std::max<double>(fConst1, std::fabs(fTemp31));
		fRec38[0] = (iTemp29?(fTemp32 + fRec38[1]):fTemp32);
		iRec39[0] = (iTemp29?(iRec39[1] + 1):1);
		fRec40[0] = (iTemp29?fRec40[1]:(0.000244140625 * fRec38[1]));
		fVbargraph4 = FAUSTFLOAT(fRec40[0]);
		output0[i] = FAUSTFLOAT((fRec0[0] * ((((fTemp6 + fTemp14) + fTemp21) + fTemp27) + fTemp31)));
		iVec0[1] = iVec0[0];
		fRec0[1] = fRec0[0];
		fRec4[1] = fRec4[0];
		fRec10[1] = fRec10[0];
		fVec1[1] = fVec1[0];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec1[1] = fRec1[0];
		iRec2[1] = iRec2[0];
		fRec3[1] = fRec3[0];
		fRec14[1] = fRec14[0];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fVec2[1] = fVec2[0];
		fRec18[1] = fRec18[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		fRec11[1] = fRec11[0];
		iRec12[1] = iRec12[0];
		fRec13[1] = fRec13[0];
		fRec24[1] = fRec24[0];
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fVec3[1] = fVec3[0];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		fRec21[1] = fRec21[0];
		iRec22[1] = iRec22[0];
		fRec23[1] = fRec23[0];
		fRec33[1] = fRec33[0];
		fRec37[1] = fRec37[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		fVec4[1] = fVec4[0];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec30[1] = fRec30[0];
		iRec31[1] = iRec31[0];
		fRec32[1] = fRec32[0];
		fRec41[1] = fRec41[0];
		fRec43[1] = fRec43[0];
		fRec42[2] = fRec42[1];
		fRec42[1] = fRec42[0];
		fRec38[1] = fRec38[0];
		iRec39[1] = iRec39[0];
		fRec40[1] = fRec40[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("mbclip.Drive1","","S",N_("Amount of distortion"),&fHslider8, 0.33000000000000002, 0.0, 1.0, 0.01);
	reg.registerVar("mbclip.Drive2","","S",N_("Amount of distortion"),&fHslider7, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("mbclip.Drive3","","S",N_("Amount of distortion"),&fHslider6, 0.65000000000000002, 0.0, 1.0, 0.01);
	reg.registerVar("mbclip.Drive4","","S",N_("Amount of distortion"),&fHslider5, 0.33000000000000002, 0.0, 1.0, 0.01);
	reg.registerVar("mbclip.Drive5","","S",N_("Amount of distortion"),&fHslider0, 0.10000000000000001, 0.0, 1.0, 0.01);
	reg.registerVar("mbclip.Gain","","S","",&fVslider0, 0.0, -40.0, 4.0, 0.10000000000000001);
	reg.registerVar("mbclip.crossover_b1_b2",N_("Crossover B1-B2 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fHslider4, 80.0, 20.0, 20000.0, 1.0800000000000001);
	reg.registerVar("mbclip.crossover_b2_b3",N_("Crossover B2-B3 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fHslider3, 210.0, 20.0, 20000.0, 1.0800000000000001);
	reg.registerVar("mbclip.crossover_b3_b4",N_("Crossover B3-B4 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fHslider2, 1700.0, 20.0, 20000.0, 1.0800000000000001);
	reg.registerVar("mbclip.crossover_b4_b5",N_("Crossover B4-B5 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fHslider1, 5000.0, 20.0, 20000.0, 1.0800000000000001);
	reg.registerNonMidiFloatVar("mbclip.v1",&fVbargraph4, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbclip.v2",&fVbargraph3, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbclip.v3",&fVbargraph2, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbclip.v4",&fVbargraph1, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbclip.v5",&fVbargraph0, false, true, -70.0, -70.0, 4.0, 0.00001);
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
  <requires lib=\"gtk+\" version=\"3.0\"/>\n\
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
                <child>\n\
                  <object class=\"GtkNotebook\" id=\"notebook:tab_rack\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"margin_left\">4</property>\n\
                        <property name=\"margin_right\">4</property>\n\
                        <property name=\"margin_top\">4</property>\n\
                        <property name=\"margin_bottom\">4</property>\n\
                        <property name=\"spacing\">4</property>\n\
                        <child>\n\
                          <object class=\"GtkBox\" id=\"hbox4\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <child>\n\
                              <object class=\"GtkBox\" id=\"vbox3\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_81:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Drive</property>\n\
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
                                    <property name=\"show_fill_level\">True</property>\n\
                                    <property name=\"var_id\">mbclip.Drive1</property>\n\
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
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
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
                            <property name=\"margin_left\">4</property>\n\
                            <property name=\"margin_right\">4</property>\n\
                            <property name=\"margin_top\">4</property>\n\
                            <property name=\"margin_bottom\">4</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <property name=\"column_spacing\">4</property>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_141:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"hexpand\">True</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">0</property>\n\
                                <property name=\"top_attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob2\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbclip.crossover_b1_b2</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
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
                        <property name=\"margin_left\">4</property>\n\
                        <property name=\"margin_right\">4</property>\n\
                        <property name=\"margin_top\">4</property>\n\
                        <property name=\"margin_bottom\">4</property>\n\
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
                                    <property name=\"label\" translatable=\"yes\">Drive</property>\n\
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
                                    <property name=\"show_fill_level\">True</property>\n\
                                    <property name=\"var_id\">mbclip.Drive2</property>\n\
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
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
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
                            <property name=\"margin_left\">4</property>\n\
                            <property name=\"margin_right\">4</property>\n\
                            <property name=\"margin_top\">4</property>\n\
                            <property name=\"margin_bottom\">4</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <property name=\"column_spacing\">4</property>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_13:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"hexpand\">True</property>\n\
                                <property name=\"label\" translatable=\"yes\">Low</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">0</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob7\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbclip.crossover_b1_b2</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_14:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"hexpand\">True</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">0</property>\n\
                                <property name=\"top_attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob6\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbclip.crossover_b2_b3</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
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
                        <property name=\"margin_left\">4</property>\n\
                        <property name=\"margin_right\">4</property>\n\
                        <property name=\"margin_top\">4</property>\n\
                        <property name=\"margin_bottom\">4</property>\n\
                        <property name=\"spacing\">4</property>\n\
                        <child>\n\
                          <object class=\"GtkBox\" id=\"hbox8\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <child>\n\
                              <object class=\"GtkBox\" id=\"vbox7\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_82:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Drive</property>\n\
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
                                    <property name=\"show_fill_level\">True</property>\n\
                                    <property name=\"var_id\">mbclip.Drive3</property>\n\
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
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
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
                            <property name=\"margin_left\">4</property>\n\
                            <property name=\"margin_right\">4</property>\n\
                            <property name=\"margin_top\">4</property>\n\
                            <property name=\"margin_bottom\">4</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <property name=\"column_spacing\">4</property>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_132:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"hexpand\">True</property>\n\
                                <property name=\"label\" translatable=\"yes\">Low</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">0</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob3\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbclip.crossover_b2_b3</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_142:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"hexpand\">True</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">0</property>\n\
                                <property name=\"top_attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob4\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbclip.crossover_b3_b4</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
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
                        <property name=\"margin_left\">4</property>\n\
                        <property name=\"margin_right\">4</property>\n\
                        <property name=\"margin_top\">4</property>\n\
                        <property name=\"margin_bottom\">4</property>\n\
                        <property name=\"spacing\">4</property>\n\
                        <child>\n\
                          <object class=\"GtkBox\" id=\"hbox10\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <child>\n\
                              <object class=\"GtkBox\" id=\"vbox14\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_83:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Drive</property>\n\
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
                                    <property name=\"show_fill_level\">True</property>\n\
                                    <property name=\"var_id\">mbclip.Drive4</property>\n\
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
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
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
                            <property name=\"margin_left\">4</property>\n\
                            <property name=\"margin_right\">4</property>\n\
                            <property name=\"margin_top\">4</property>\n\
                            <property name=\"margin_bottom\">4</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <property name=\"column_spacing\">4</property>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_133:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"hexpand\">True</property>\n\
                                <property name=\"label\" translatable=\"yes\">Low</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">0</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob5\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbclip.crossover_b3_b4</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_143:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"hexpand\">True</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">0</property>\n\
                                <property name=\"top_attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob8\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbclip.crossover_b4_b5</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
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
                        <property name=\"margin_left\">4</property>\n\
                        <property name=\"margin_right\">4</property>\n\
                        <property name=\"margin_top\">4</property>\n\
                        <property name=\"margin_bottom\">4</property>\n\
                        <property name=\"spacing\">4</property>\n\
                        <child>\n\
                          <object class=\"GtkBox\" id=\"hbox12\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <child>\n\
                              <object class=\"GtkBox\" id=\"vbox18\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_84:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Drive</property>\n\
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
                                    <property name=\"show_fill_level\">True</property>\n\
                                    <property name=\"var_id\">mbclip.Drive5</property>\n\
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
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
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
                            <property name=\"margin_left\">4</property>\n\
                            <property name=\"margin_right\">4</property>\n\
                            <property name=\"margin_top\">4</property>\n\
                            <property name=\"margin_bottom\">4</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <property name=\"column_spacing\">4</property>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_134:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"hexpand\">True</property>\n\
                                <property name=\"label\" translatable=\"yes\">Low</property>\n\
                                <property name=\"xalign\">1</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">0</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob9\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbclip.crossover_b4_b5</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"top_attach\">1</property>\n\
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
                    <property name=\"expand\">False</property>\n\
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
                      <object class=\"GtkLabel\" id=\"label_99:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Gain</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxMidKnob\" id=\"gxmidknob1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">mbclip.Gain</property>\n\
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
                            <property name=\"var_id\">mbclip.v1</property>\n\
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
                            <property name=\"var_id\">mbclip.v2</property>\n\
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
                            <property name=\"var_id\">mbclip.v3</property>\n\
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
                            <property name=\"var_id\">mbclip.v4</property>\n\
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
                            <property name=\"var_id\">mbclip.v5</property>\n\
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

} // end namespace mbclipper
} // end namespace pluginlib
