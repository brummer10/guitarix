// generated from file '../src/plugins/mbclipper.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "clipping.h"

namespace pluginlib {
namespace mbclipper {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	int iVec0[2];
	double fConst0;
	double fConst1;
	FAUSTFLOAT fHslider0;
	double fConst2;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	double fRec11[2];
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
	double fRec4[2];
	double fRec3[3];
	FAUSTFLOAT fHslider4;
	double fRec12[2];
	double fRec0[2];
	int iRec1[2];
	double fRec2[2];
	FAUSTFLOAT fVbargraph0;
	double fRec18[2];
	double fRec17[3];
	double fRec16[3];
	FAUSTFLOAT fHslider5;
	double fRec19[2];
	double fRec13[2];
	int iRec14[2];
	double fRec15[2];
	FAUSTFLOAT fVbargraph1;
	double fRec26[2];
	double fRec25[3];
	double fRec24[3];
	double fRec23[3];
	FAUSTFLOAT fHslider6;
	double fRec27[2];
	double fRec20[2];
	int iRec21[2];
	double fRec22[2];
	FAUSTFLOAT fVbargraph2;
	double fRec35[2];
	double fRec34[3];
	double fRec33[3];
	double fRec32[3];
	double fRec31[3];
	FAUSTFLOAT fHslider7;
	double fRec36[2];
	double fRec28[2];
	int iRec29[2];
	double fRec30[2];
	FAUSTFLOAT fVbargraph3;
	double fRec41[2];
	double fRec40[3];
	FAUSTFLOAT fHslider8;
	double fRec42[2];
	double fRec37[2];
	int iRec38[2];
	double fRec39[2];
	FAUSTFLOAT fVbargraph4;
	FAUSTFLOAT fVslider0;
	double fRec43[2];

	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int sample_rate, PluginDef*);
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) iVec0[l0] = 0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec11[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fVec1[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec10[l3] = 0.0;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRec9[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fVec2[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec8[l6] = 0.0;
	for (int l7 = 0; l7 < 3; l7 = l7 + 1) fRec7[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fVec3[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec6[l9] = 0.0;
	for (int l10 = 0; l10 < 3; l10 = l10 + 1) fRec5[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fVec4[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec4[l12] = 0.0;
	for (int l13 = 0; l13 < 3; l13 = l13 + 1) fRec3[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec12[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec0[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) iRec1[l16] = 0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec2[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec18[l18] = 0.0;
	for (int l19 = 0; l19 < 3; l19 = l19 + 1) fRec17[l19] = 0.0;
	for (int l20 = 0; l20 < 3; l20 = l20 + 1) fRec16[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec19[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec13[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) iRec14[l23] = 0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec15[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec26[l25] = 0.0;
	for (int l26 = 0; l26 < 3; l26 = l26 + 1) fRec25[l26] = 0.0;
	for (int l27 = 0; l27 < 3; l27 = l27 + 1) fRec24[l27] = 0.0;
	for (int l28 = 0; l28 < 3; l28 = l28 + 1) fRec23[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec27[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec20[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) iRec21[l31] = 0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fRec22[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fRec35[l33] = 0.0;
	for (int l34 = 0; l34 < 3; l34 = l34 + 1) fRec34[l34] = 0.0;
	for (int l35 = 0; l35 < 3; l35 = l35 + 1) fRec33[l35] = 0.0;
	for (int l36 = 0; l36 < 3; l36 = l36 + 1) fRec32[l36] = 0.0;
	for (int l37 = 0; l37 < 3; l37 = l37 + 1) fRec31[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fRec36[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec28[l39] = 0.0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) iRec29[l40] = 0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec30[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) fRec41[l42] = 0.0;
	for (int l43 = 0; l43 < 3; l43 = l43 + 1) fRec40[l43] = 0.0;
	for (int l44 = 0; l44 < 2; l44 = l44 + 1) fRec42[l44] = 0.0;
	for (int l45 = 0; l45 < 2; l45 = l45 + 1) fRec37[l45] = 0.0;
	for (int l46 = 0; l46 < 2; l46 = l46 + 1) iRec38[l46] = 0;
	for (int l47 = 0; l47 < 2; l47 = l47 + 1) fRec39[l47] = 0.0;
	for (int l48 = 0; l48 < 2; l48 = l48 + 1) fRec43[l48] = 0.0;
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

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = std::tan(fConst2 * double(fHslider0));
	double fSlow1 = mydsp_faustpower2_f(fSlow0);
	double fSlow2 = 2.0 * (1.0 - 1.0 / fSlow1);
	double fSlow3 = 1.0 / fSlow0;
	double fSlow4 = (fSlow3 + -1.0000000000000004) / fSlow0 + 1.0;
	double fSlow5 = (fSlow3 + 1.0000000000000004) / fSlow0 + 1.0;
	double fSlow6 = 1.0 / fSlow5;
	double fSlow7 = std::tan(fConst2 * double(fHslider1));
	double fSlow8 = mydsp_faustpower2_f(fSlow7);
	double fSlow9 = 2.0 * (1.0 - 1.0 / fSlow8);
	double fSlow10 = 1.0 / fSlow7;
	double fSlow11 = (fSlow10 + -1.0000000000000004) / fSlow7 + 1.0;
	double fSlow12 = (fSlow10 + 1.0000000000000004) / fSlow7 + 1.0;
	double fSlow13 = 1.0 / fSlow12;
	double fSlow14 = std::tan(fConst2 * double(fHslider2));
	double fSlow15 = mydsp_faustpower2_f(fSlow14);
	double fSlow16 = 2.0 * (1.0 - 1.0 / fSlow15);
	double fSlow17 = 1.0 / fSlow14;
	double fSlow18 = (fSlow17 + -1.0000000000000004) / fSlow14 + 1.0;
	double fSlow19 = (fSlow17 + 1.0000000000000004) / fSlow14 + 1.0;
	double fSlow20 = 1.0 / fSlow19;
	double fSlow21 = std::tan(fConst2 * double(fHslider3));
	double fSlow22 = mydsp_faustpower2_f(fSlow21);
	double fSlow23 = 2.0 * (1.0 - 1.0 / fSlow22);
	double fSlow24 = 1.0 / fSlow21;
	double fSlow25 = (fSlow24 + -1.0000000000000004) / fSlow21 + 1.0;
	double fSlow26 = (fSlow24 + 1.0000000000000004) / fSlow21 + 1.0;
	double fSlow27 = 1.0 / fSlow26;
	double fSlow28 = 1.0 - fSlow24;
	double fSlow29 = 1.0 / (fSlow24 + 1.0);
	double fSlow30 = 1.0 - fSlow17;
	double fSlow31 = fSlow17 + 1.0;
	double fSlow32 = 1.0 / fSlow31;
	double fSlow33 = 1.0 - fSlow10;
	double fSlow34 = fSlow10 + 1.0;
	double fSlow35 = 1.0 / fSlow34;
	double fSlow36 = 1.0 - fSlow3;
	double fSlow37 = fSlow3 + 1.0;
	double fSlow38 = 1.0 / fSlow37;
	double fSlow39 = 0.0010000000000000009 * double(fHslider4);
	double fSlow40 = 1.0 - fSlow36 / fSlow0;
	double fSlow41 = 1.0 / (fSlow37 / fSlow0 + 1.0);
	double fSlow42 = 1.0 / (fSlow8 * fSlow12);
	double fSlow43 = 0.0010000000000000009 * double(fHslider5);
	double fSlow44 = 1.0 - fSlow33 / fSlow7;
	double fSlow45 = 1.0 / (fSlow34 / fSlow7 + 1.0);
	double fSlow46 = 1.0 / (fSlow15 * fSlow19);
	double fSlow47 = 0.0010000000000000009 * double(fHslider6);
	double fSlow48 = 1.0 - fSlow30 / fSlow14;
	double fSlow49 = 1.0 / (fSlow31 / fSlow14 + 1.0);
	double fSlow50 = 1.0 / (fSlow22 * fSlow26);
	double fSlow51 = 0.0010000000000000009 * double(fHslider7);
	double fSlow52 = 0.0010000000000000009 * double(fHslider8);
	double fSlow53 = 1.0 / (fSlow1 * fSlow5);
	double fSlow54 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		iVec0[0] = 1;
		int iTemp0 = iRec1[1] < 4096;
		fRec11[0] = 1e-20 * double(1 - iVec0[1]) - fRec11[1];
		double fTemp1 = double(input0[i0]) + fRec11[0];
		fVec1[0] = fTemp1;
		fRec10[0] = -(fSlow29 * (fSlow28 * fRec10[1] - (fTemp1 + fVec1[1])));
		fRec9[0] = fRec10[0] - fSlow27 * (fSlow25 * fRec9[2] + fSlow23 * fRec9[1]);
		double fTemp2 = fSlow27 * (fRec9[2] + fRec9[0] + 2.0 * fRec9[1]);
		fVec2[0] = fTemp2;
		fRec8[0] = -(fSlow32 * (fSlow30 * fRec8[1] - (fTemp2 + fVec2[1])));
		fRec7[0] = fRec8[0] - fSlow20 * (fSlow18 * fRec7[2] + fSlow16 * fRec7[1]);
		double fTemp3 = fSlow20 * (fRec7[2] + fRec7[0] + 2.0 * fRec7[1]);
		fVec3[0] = fTemp3;
		fRec6[0] = -(fSlow35 * (fSlow33 * fRec6[1] - (fTemp3 + fVec3[1])));
		fRec5[0] = fRec6[0] - fSlow13 * (fSlow11 * fRec5[2] + fSlow9 * fRec5[1]);
		double fTemp4 = fSlow13 * (fRec5[2] + fRec5[0] + 2.0 * fRec5[1]);
		fVec4[0] = fTemp4;
		fRec4[0] = -(fSlow38 * (fSlow36 * fRec4[1] - (fTemp4 + fVec4[1])));
		fRec3[0] = fRec4[0] - fSlow6 * (fSlow4 * fRec3[2] + fSlow2 * fRec3[1]);
		fRec12[0] = fSlow39 + 0.999 * fRec12[1];
		double fTemp5 = std::pow(1e+01, 2.0 * fRec12[0]);
		double fTemp6 = std::max<double>(1.0, 1.0 / fTemp5) * symclip(fSlow6 * fTemp5 * (fRec3[2] + fRec3[0] + 2.0 * fRec3[1]));
		double fTemp7 = std::max<double>(fConst1, std::fabs(fTemp6));
		fRec0[0] = ((iTemp0) ? fTemp7 + fRec0[1] : fTemp7);
		iRec1[0] = ((iTemp0) ? iRec1[1] + 1 : 1);
		fRec2[0] = ((iTemp0) ? fRec2[1] : 0.000244140625 * fRec0[1]);
		fVbargraph0 = FAUSTFLOAT(fRec2[0]);
		int iTemp8 = iRec14[1] < 4096;
		double fTemp9 = fSlow2 * fRec16[1];
		fRec18[0] = -(fSlow35 * (fSlow33 * fRec18[1] - fSlow10 * (fTemp3 - fVec3[1])));
		fRec17[0] = fRec18[0] - fSlow13 * (fSlow11 * fRec17[2] + fSlow9 * fRec17[1]);
		fRec16[0] = fSlow42 * (fRec17[2] + (fRec17[0] - 2.0 * fRec17[1])) - fSlow41 * (fSlow40 * fRec16[2] + fTemp9);
		fRec19[0] = fSlow43 + 0.999 * fRec19[1];
		double fTemp10 = std::pow(1e+01, 2.0 * fRec19[0]);
		double fTemp11 = std::max<double>(1.0, 1.0 / fTemp10) * symclip(fTemp10 * (fRec16[2] + fSlow41 * (fTemp9 + fSlow40 * fRec16[0])));
		double fTemp12 = std::max<double>(fConst1, std::fabs(fTemp11));
		fRec13[0] = ((iTemp8) ? fTemp12 + fRec13[1] : fTemp12);
		iRec14[0] = ((iTemp8) ? iRec14[1] + 1 : 1);
		fRec15[0] = ((iTemp8) ? fRec15[1] : 0.000244140625 * fRec13[1]);
		fVbargraph1 = FAUSTFLOAT(fRec15[0]);
		int iTemp13 = iRec21[1] < 4096;
		double fTemp14 = fSlow2 * fRec23[1];
		double fTemp15 = fSlow9 * fRec24[1];
		fRec26[0] = -(fSlow32 * (fSlow30 * fRec26[1] - fSlow17 * (fTemp2 - fVec2[1])));
		fRec25[0] = fRec26[0] - fSlow20 * (fSlow18 * fRec25[2] + fSlow16 * fRec25[1]);
		fRec24[0] = fSlow46 * (fRec25[2] + (fRec25[0] - 2.0 * fRec25[1])) - fSlow45 * (fSlow44 * fRec24[2] + fTemp15);
		fRec23[0] = fRec24[2] + fSlow45 * (fTemp15 + fSlow44 * fRec24[0]) - fSlow41 * (fSlow40 * fRec23[2] + fTemp14);
		fRec27[0] = fSlow47 + 0.999 * fRec27[1];
		double fTemp16 = std::pow(1e+01, 2.0 * fRec27[0]);
		double fTemp17 = std::max<double>(1.0, 1.0 / fTemp16) * symclip(fTemp16 * (fRec23[2] + fSlow41 * (fTemp14 + fSlow40 * fRec23[0])));
		double fTemp18 = std::max<double>(fConst1, std::fabs(fTemp17));
		fRec20[0] = ((iTemp13) ? fTemp18 + fRec20[1] : fTemp18);
		iRec21[0] = ((iTemp13) ? iRec21[1] + 1 : 1);
		fRec22[0] = ((iTemp13) ? fRec22[1] : 0.000244140625 * fRec20[1]);
		fVbargraph2 = FAUSTFLOAT(fRec22[0]);
		int iTemp19 = iRec29[1] < 4096;
		double fTemp20 = fSlow2 * fRec31[1];
		double fTemp21 = fSlow9 * fRec32[1];
		double fTemp22 = fSlow16 * fRec33[1];
		fRec35[0] = -(fSlow29 * (fSlow28 * fRec35[1] - fSlow24 * (fTemp1 - fVec1[1])));
		fRec34[0] = fRec35[0] - fSlow27 * (fSlow25 * fRec34[2] + fSlow23 * fRec34[1]);
		fRec33[0] = fSlow50 * (fRec34[2] + (fRec34[0] - 2.0 * fRec34[1])) - fSlow49 * (fSlow48 * fRec33[2] + fTemp22);
		fRec32[0] = fRec33[2] + fSlow49 * (fTemp22 + fSlow48 * fRec33[0]) - fSlow45 * (fSlow44 * fRec32[2] + fTemp21);
		fRec31[0] = fRec32[2] + fSlow45 * (fTemp21 + fSlow44 * fRec32[0]) - fSlow41 * (fSlow40 * fRec31[2] + fTemp20);
		fRec36[0] = fSlow51 + 0.999 * fRec36[1];
		double fTemp23 = std::pow(1e+01, 2.0 * fRec36[0]);
		double fTemp24 = std::max<double>(1.0, 1.0 / fTemp23) * symclip(fTemp23 * (fRec31[2] + fSlow41 * (fTemp20 + fSlow40 * fRec31[0])));
		double fTemp25 = std::max<double>(fConst1, std::fabs(fTemp24));
		fRec28[0] = ((iTemp19) ? fTemp25 + fRec28[1] : fTemp25);
		iRec29[0] = ((iTemp19) ? iRec29[1] + 1 : 1);
		fRec30[0] = ((iTemp19) ? fRec30[1] : 0.000244140625 * fRec28[1]);
		fVbargraph3 = FAUSTFLOAT(fRec30[0]);
		int iTemp26 = iRec38[1] < 4096;
		fRec41[0] = -(fSlow38 * (fSlow36 * fRec41[1] - fSlow3 * (fTemp4 - fVec4[1])));
		fRec40[0] = fRec41[0] - fSlow6 * (fSlow4 * fRec40[2] + fSlow2 * fRec40[1]);
		double fTemp27 = 2.0 * fRec40[1];
		fRec42[0] = fSlow52 + 0.999 * fRec42[1];
		double fTemp28 = std::pow(1e+01, 2.0 * fRec42[0]);
		double fTemp29 = std::max<double>(1.0, 1.0 / fTemp28);
		double fTemp30 = std::max<double>(fConst1, std::fabs(fTemp29 * symclip(fSlow53 * fTemp28 * (fRec40[2] + (fRec40[0] - fTemp27)))));
		fRec37[0] = ((iTemp26) ? fTemp30 + fRec37[1] : fTemp30);
		iRec38[0] = ((iTemp26) ? iRec38[1] + 1 : 1);
		fRec39[0] = ((iTemp26) ? fRec39[1] : 0.000244140625 * fRec37[1]);
		fVbargraph4 = FAUSTFLOAT(fRec39[0]);
		fRec43[0] = fSlow54 + 0.999 * fRec43[1];
		output0[i0] = FAUSTFLOAT(fRec43[0] * (fTemp29 * symclip(fSlow53 * fTemp28 * (fRec40[0] + fRec40[2] - fTemp27)) + fTemp24 + fTemp17 + fTemp11 + fTemp6));
		iVec0[1] = iVec0[0];
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
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec12[1] = fRec12[0];
		fRec0[1] = fRec0[0];
		iRec1[1] = iRec1[0];
		fRec2[1] = fRec2[0];
		fRec18[1] = fRec18[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fRec19[1] = fRec19[0];
		fRec13[1] = fRec13[0];
		iRec14[1] = iRec14[0];
		fRec15[1] = fRec15[0];
		fRec26[1] = fRec26[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fRec23[2] = fRec23[1];
		fRec23[1] = fRec23[0];
		fRec27[1] = fRec27[0];
		fRec20[1] = fRec20[0];
		iRec21[1] = iRec21[0];
		fRec22[1] = fRec22[0];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fRec36[1] = fRec36[0];
		fRec28[1] = fRec28[0];
		iRec29[1] = iRec29[0];
		fRec30[1] = fRec30[0];
		fRec41[1] = fRec41[0];
		fRec40[2] = fRec40[1];
		fRec40[1] = fRec40[0];
		fRec42[1] = fRec42[0];
		fRec37[1] = fRec37[0];
		iRec38[1] = iRec38[0];
		fRec39[1] = fRec39[0];
		fRec43[1] = fRec43[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("mbclip.Drive1","","S",N_("Amount of distortion"),&fHslider4, 0.33, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("mbclip.Drive2","","S",N_("Amount of distortion"),&fHslider8, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("mbclip.Drive3","","S",N_("Amount of distortion"),&fHslider5, 0.65, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("mbclip.Drive4","","S",N_("Amount of distortion"),&fHslider6, 0.33, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("mbclip.Drive5","","S",N_("Amount of distortion"),&fHslider7, 0.1, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("mbclip.Gain","","S","",&fVslider0, 0.0, -4e+01, 4.0, 0.1, 0);
	reg.registerFloatVar("mbclip.crossover_b1_b2",N_("Crossover B1-B2 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fHslider0, 8e+01, 2e+01, 2e+04, 1.08, 0);
	reg.registerFloatVar("mbclip.crossover_b2_b3",N_("Crossover B2-B3 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fHslider1, 2.1e+02, 2e+01, 2e+04, 1.08, 0);
	reg.registerFloatVar("mbclip.crossover_b3_b4",N_("Crossover B3-B4 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fHslider2, 1.7e+03, 2e+01, 2e+04, 1.08, 0);
	reg.registerFloatVar("mbclip.crossover_b4_b5",N_("Crossover B4-B5 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fHslider3, 5e+03, 2e+01, 2e+04, 1.08, 0);
	reg.registerFloatVar("mbclip.v1","","SOLN","",&fVbargraph0, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("mbclip.v2","","SOLN","",&fVbargraph4, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("mbclip.v3","","SOLN","",&fVbargraph1, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("mbclip.v4","","SOLN","",&fVbargraph2, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("mbclip.v5","","SOLN","",&fVbargraph3, 0, -7e+01, 5.0, 0, 0);
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
                  <object class=\"GtkNotebook\" id=\"notebook\">\n\
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
                            <property name=\"row_homogeneous\">True</property>\n\
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
                              <object class=\"GtkLabel\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">0</property>\n\
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
                            <property name=\"row_homogeneous\">True</property>\n\
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
                            <property name=\"row_homogeneous\">True</property>\n\
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
                            <property name=\"row_homogeneous\">True</property>\n\
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
                            <property name=\"row_homogeneous\">True</property>\n\
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
                              <object class=\"GtkLabel\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">0</property>\n\
                                <property name=\"top_attach\">0</property>\n\
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
                        <property name=\"margin_bottom\">4</property>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter1\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbclip.v1</property>\n\
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
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbclip.v2</property>\n\
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
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbclip.v3</property>\n\
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
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbclip.v4</property>\n\
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
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbclip.v5</property>\n\
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
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("mbclip" "." p)

b.openHorizontalhideBox("");
b.closeBox();

b.openHorizontalBox("");

b.openTabBox("");

b.openHorizontalBox(N_("Band 1"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.create_small_rackknob(PARAM("Drive1"), N_("Drive"));
b.insertSpacer();
b.insertSpacer();
b.insertSpacer();
b.create_small_rackknob(PARAM("crossover_b1_b2"), N_("High"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 2"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.create_small_rackknob(PARAM("Drive2"), N_("Drive"));
b.create_small_rackknob(PARAM("crossover_b1_b2"), N_("Low"));
b.create_small_rackknob(PARAM("crossover_b2_b3"), N_("High"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 3"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.create_small_rackknob(PARAM("Drive3"), N_("Drive"));
b.create_small_rackknob(PARAM("crossover_b2_b3"), N_("Low"));
b.create_small_rackknob(PARAM("crossover_b3_b4"), N_("High"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 4"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.create_small_rackknob(PARAM("Drive4"), N_("Drive"));
b.create_small_rackknob(PARAM("crossover_b3_b4"), N_("Low"));
b.create_small_rackknob(PARAM("crossover_b4_b5"), N_("High"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 5"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.create_small_rackknob(PARAM("Drive5"), N_("Drive"));
b.create_small_rackknob(PARAM("crossover_b4_b5"), N_("Low"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.closeBox();

b.create_mid_rackknob(PARAM("Gain"), N_("Gain"));

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

} // end namespace mbclipper
} // end namespace pluginlib
