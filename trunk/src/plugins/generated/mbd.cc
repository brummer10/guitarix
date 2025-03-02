// generated from file '../src/plugins/mbd.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace mbd {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int sample_rate;
	int fSampleRate;
	int iVec0[2];
	FAUSTFLOAT fVslider0;
	double fRec0[2];
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider1;
	double fRec4[2];
	double fConst2;
	double fConst3;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	double fRec14[2];
	double fVec1[2];
	double fRec13[2];
	double fRec12[3];
	double fVec2[2];
	double fRec11[2];
	double fRec10[3];
	double fVec3[2];
	double fRec9[2];
	double fRec8[3];
	double fVec4[2];
	double fRec7[2];
	double fRec6[3];
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	double fRec15[2];
	double fVec5[2];
	double fConst4;
	double fRec5[2];
	double fRec1[2];
	int iRec2[2];
	double fRec3[2];
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT fVslider2;
	double fRec19[2];
	double fRec22[2];
	double fRec21[3];
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT fHslider7;
	double fRec23[2];
	double fVec6[2];
	double fRec20[2];
	double fRec16[2];
	int iRec17[2];
	double fRec18[2];
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT fVslider3;
	double fRec27[2];
	double fRec31[2];
	double fRec30[3];
	double fRec29[3];
	FAUSTFLOAT fHslider8;
	FAUSTFLOAT fHslider9;
	double fRec32[2];
	double fVec7[2];
	double fRec28[2];
	double fRec24[2];
	int iRec25[2];
	double fRec26[2];
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT fVslider4;
	double fRec36[2];
	double fRec41[2];
	double fRec40[3];
	double fRec39[3];
	double fRec38[3];
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT fHslider11;
	double fRec42[2];
	double fVec8[2];
	double fRec37[2];
	double fRec33[2];
	int iRec34[2];
	double fRec35[2];
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT fVslider5;
	double fRec46[2];
	double fRec52[2];
	double fRec51[3];
	double fRec50[3];
	double fRec49[3];
	double fRec48[3];
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT fHslider13;
	double fRec53[2];
	double fVec9[2];
	double fRec47[2];
	double fRec43[2];
	int iRec44[2];
	double fRec45[2];
	FAUSTFLOAT fVbargraph4;

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
	id = "mbd";
	name = N_("MultiBand Distortion");
	groups = 0;
	description = N_("MultiBand Distortion"); // description (tooltip)
	category = N_("Distortion");       // category
	shortname = N_("MB Distortion");     // shortname
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
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec0[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec4[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec14[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fVec1[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec13[l5] = 0.0;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec12[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fVec2[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec11[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec10[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fVec3[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec9[l11] = 0.0;
	for (int l12 = 0; l12 < 3; l12 = l12 + 1) fRec8[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fVec4[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec7[l14] = 0.0;
	for (int l15 = 0; l15 < 3; l15 = l15 + 1) fRec6[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec15[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fVec5[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec5[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec1[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) iRec2[l20] = 0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec3[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec19[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec22[l23] = 0.0;
	for (int l24 = 0; l24 < 3; l24 = l24 + 1) fRec21[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec23[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fVec6[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec20[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec16[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) iRec17[l29] = 0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec18[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec27[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fRec31[l32] = 0.0;
	for (int l33 = 0; l33 < 3; l33 = l33 + 1) fRec30[l33] = 0.0;
	for (int l34 = 0; l34 < 3; l34 = l34 + 1) fRec29[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec32[l35] = 0.0;
	for (int l36 = 0; l36 < 2; l36 = l36 + 1) fVec7[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec28[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fRec24[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) iRec25[l39] = 0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec26[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec36[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) fRec41[l42] = 0.0;
	for (int l43 = 0; l43 < 3; l43 = l43 + 1) fRec40[l43] = 0.0;
	for (int l44 = 0; l44 < 3; l44 = l44 + 1) fRec39[l44] = 0.0;
	for (int l45 = 0; l45 < 3; l45 = l45 + 1) fRec38[l45] = 0.0;
	for (int l46 = 0; l46 < 2; l46 = l46 + 1) fRec42[l46] = 0.0;
	for (int l47 = 0; l47 < 2; l47 = l47 + 1) fVec8[l47] = 0.0;
	for (int l48 = 0; l48 < 2; l48 = l48 + 1) fRec37[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec33[l49] = 0.0;
	for (int l50 = 0; l50 < 2; l50 = l50 + 1) iRec34[l50] = 0;
	for (int l51 = 0; l51 < 2; l51 = l51 + 1) fRec35[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fRec46[l52] = 0.0;
	for (int l53 = 0; l53 < 2; l53 = l53 + 1) fRec52[l53] = 0.0;
	for (int l54 = 0; l54 < 3; l54 = l54 + 1) fRec51[l54] = 0.0;
	for (int l55 = 0; l55 < 3; l55 = l55 + 1) fRec50[l55] = 0.0;
	for (int l56 = 0; l56 < 3; l56 = l56 + 1) fRec49[l56] = 0.0;
	for (int l57 = 0; l57 < 3; l57 = l57 + 1) fRec48[l57] = 0.0;
	for (int l58 = 0; l58 < 2; l58 = l58 + 1) fRec53[l58] = 0.0;
	for (int l59 = 0; l59 < 2; l59 = l59 + 1) fVec9[l59] = 0.0;
	for (int l60 = 0; l60 < 2; l60 = l60 + 1) fRec47[l60] = 0.0;
	for (int l61 = 0; l61 < 2; l61 = l61 + 1) fRec43[l61] = 0.0;
	for (int l62 = 0; l62 < 2; l62 = l62 + 1) iRec44[l62] = 0;
	for (int l63 = 0; l63 < 2; l63 = l63 + 1) fRec45[l63] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int RsamplingFreq)
{
	sample_rate = 96000;
	smp.setup(RsamplingFreq, sample_rate);
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 1.0 / fConst0;
	fConst2 = 3.141592653589793 / fConst0;
	fConst3 = 1.0 - fConst2;
	fConst4 = 1.0 / (fConst2 + 1.0);
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
	double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider1));
	double fSlow2 = std::tan(fConst2 * double(fHslider0));
	double fSlow3 = mydsp_faustpower2_f(fSlow2);
	double fSlow4 = 2.0 * (1.0 - 1.0 / fSlow3);
	double fSlow5 = 1.0 / fSlow2;
	double fSlow6 = (fSlow5 + -1.0000000000000004) / fSlow2 + 1.0;
	double fSlow7 = (fSlow5 + 1.0000000000000004) / fSlow2 + 1.0;
	double fSlow8 = 1.0 / fSlow7;
	double fSlow9 = std::tan(fConst2 * double(fHslider1));
	double fSlow10 = mydsp_faustpower2_f(fSlow9);
	double fSlow11 = 2.0 * (1.0 - 1.0 / fSlow10);
	double fSlow12 = 1.0 / fSlow9;
	double fSlow13 = (fSlow12 + -1.0000000000000004) / fSlow9 + 1.0;
	double fSlow14 = (fSlow12 + 1.0000000000000004) / fSlow9 + 1.0;
	double fSlow15 = 1.0 / fSlow14;
	double fSlow16 = std::tan(fConst2 * double(fHslider2));
	double fSlow17 = mydsp_faustpower2_f(fSlow16);
	double fSlow18 = 2.0 * (1.0 - 1.0 / fSlow17);
	double fSlow19 = 1.0 / fSlow16;
	double fSlow20 = (fSlow19 + -1.0000000000000004) / fSlow16 + 1.0;
	double fSlow21 = (fSlow19 + 1.0000000000000004) / fSlow16 + 1.0;
	double fSlow22 = 1.0 / fSlow21;
	double fSlow23 = std::tan(fConst2 * double(fHslider3));
	double fSlow24 = mydsp_faustpower2_f(fSlow23);
	double fSlow25 = 2.0 * (1.0 - 1.0 / fSlow24);
	double fSlow26 = 1.0 / fSlow23;
	double fSlow27 = (fSlow26 + -1.0000000000000004) / fSlow23 + 1.0;
	double fSlow28 = (fSlow26 + 1.0000000000000004) / fSlow23 + 1.0;
	double fSlow29 = 1.0 / fSlow28;
	double fSlow30 = 1.0 - fSlow26;
	double fSlow31 = 1.0 / (fSlow26 + 1.0);
	double fSlow32 = 1.0 - fSlow19;
	double fSlow33 = fSlow19 + 1.0;
	double fSlow34 = 1.0 / fSlow33;
	double fSlow35 = 1.0 - fSlow12;
	double fSlow36 = fSlow12 + 1.0;
	double fSlow37 = 1.0 / fSlow36;
	double fSlow38 = 1.0 - fSlow5;
	double fSlow39 = fSlow5 + 1.0;
	double fSlow40 = 1.0 / fSlow39;
	double fSlow41 = std::pow(1e+01, 2.0 * double(fHslider4)) / fSlow7;
	double fSlow42 = 0.0010000000000000009 * double(fHslider5);
	double fSlow43 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider2));
	double fSlow44 = std::pow(1e+01, 2.0 * double(fHslider6)) / (fSlow3 * fSlow7);
	double fSlow45 = 0.0010000000000000009 * double(fHslider7);
	double fSlow46 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider3));
	double fSlow47 = 1.0 - fSlow38 / fSlow2;
	double fSlow48 = 1.0 / (fSlow39 / fSlow2 + 1.0);
	double fSlow49 = 1.0 / (fSlow10 * fSlow14);
	double fSlow50 = std::pow(1e+01, 2.0 * double(fHslider8));
	double fSlow51 = 0.0010000000000000009 * double(fHslider9);
	double fSlow52 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider4));
	double fSlow53 = 1.0 - fSlow35 / fSlow9;
	double fSlow54 = 1.0 / (fSlow36 / fSlow9 + 1.0);
	double fSlow55 = 1.0 / (fSlow17 * fSlow21);
	double fSlow56 = std::pow(1e+01, 2.0 * double(fHslider10));
	double fSlow57 = 0.0010000000000000009 * double(fHslider11);
	double fSlow58 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider5));
	double fSlow59 = 1.0 - fSlow32 / fSlow16;
	double fSlow60 = 1.0 / (fSlow33 / fSlow16 + 1.0);
	double fSlow61 = 1.0 / (fSlow24 * fSlow28);
	double fSlow62 = std::pow(1e+01, 2.0 * double(fHslider12));
	double fSlow63 = 0.0010000000000000009 * double(fHslider13);
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		iVec0[0] = 1;
		fRec0[0] = fSlow0 + 0.999 * fRec0[1];
		int iTemp0 = iRec2[1] < 4096;
		fRec4[0] = fSlow1 + 0.999 * fRec4[1];
		fRec14[0] = 1e-20 * double(1 - iVec0[1]) - fRec14[1];
		double fTemp1 = double(buf[i0]) + fRec14[0];
		fVec1[0] = fTemp1;
		fRec13[0] = -(fSlow31 * (fSlow30 * fRec13[1] - (fTemp1 + fVec1[1])));
		fRec12[0] = fRec13[0] - fSlow29 * (fSlow27 * fRec12[2] + fSlow25 * fRec12[1]);
		double fTemp2 = fSlow29 * (fRec12[2] + fRec12[0] + 2.0 * fRec12[1]);
		fVec2[0] = fTemp2;
		fRec11[0] = -(fSlow34 * (fSlow32 * fRec11[1] - (fTemp2 + fVec2[1])));
		fRec10[0] = fRec11[0] - fSlow22 * (fSlow20 * fRec10[2] + fSlow18 * fRec10[1]);
		double fTemp3 = fSlow22 * (fRec10[2] + fRec10[0] + 2.0 * fRec10[1]);
		fVec3[0] = fTemp3;
		fRec9[0] = -(fSlow37 * (fSlow35 * fRec9[1] - (fTemp3 + fVec3[1])));
		fRec8[0] = fRec9[0] - fSlow15 * (fSlow13 * fRec8[2] + fSlow11 * fRec8[1]);
		double fTemp4 = fSlow15 * (fRec8[2] + fRec8[0] + 2.0 * fRec8[1]);
		fVec4[0] = fTemp4;
		fRec7[0] = -(fSlow40 * (fSlow38 * fRec7[1] - (fTemp4 + fVec4[1])));
		fRec6[0] = fRec7[0] - fSlow8 * (fSlow6 * fRec6[2] + fSlow4 * fRec6[1]);
		fRec15[0] = fSlow42 + 0.999 * fRec15[1];
		double fTemp5 = std::max<double>(-1.0, std::min<double>(1.0, fRec15[0] + fSlow41 * (fRec6[2] + fRec6[0] + 2.0 * fRec6[1])));
		double fTemp6 = fTemp5 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp5));
		fVec5[0] = fTemp6;
		fRec5[0] = fConst4 * (fTemp6 - fVec5[1] + fConst3 * fRec5[1]);
		double fTemp7 = fRec5[0] * fRec4[0];
		double fTemp8 = std::max<double>(fConst1, std::fabs(fTemp7));
		fRec1[0] = ((iTemp0) ? fTemp8 + fRec1[1] : fTemp8);
		iRec2[0] = ((iTemp0) ? iRec2[1] + 1 : 1);
		fRec3[0] = ((iTemp0) ? fRec3[1] : 0.000244140625 * fRec1[1]);
		fVbargraph0 = FAUSTFLOAT(fRec3[0]);
		int iTemp9 = iRec17[1] < 4096;
		fRec19[0] = fSlow43 + 0.999 * fRec19[1];
		fRec22[0] = -(fSlow40 * (fSlow38 * fRec22[1] - fSlow5 * (fTemp4 - fVec4[1])));
		fRec21[0] = fRec22[0] - fSlow8 * (fSlow6 * fRec21[2] + fSlow4 * fRec21[1]);
		fRec23[0] = fSlow45 + 0.999 * fRec23[1];
		double fTemp10 = std::max<double>(-1.0, std::min<double>(1.0, fRec23[0] + fSlow44 * (fRec21[2] + (fRec21[0] - 2.0 * fRec21[1]))));
		double fTemp11 = fTemp10 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp10));
		fVec6[0] = fTemp11;
		fRec20[0] = fConst4 * (fTemp11 - fVec6[1] + fConst3 * fRec20[1]);
		double fTemp12 = fRec20[0] * fRec19[0];
		double fTemp13 = std::max<double>(fConst1, std::fabs(fTemp12));
		fRec16[0] = ((iTemp9) ? fTemp13 + fRec16[1] : fTemp13);
		iRec17[0] = ((iTemp9) ? iRec17[1] + 1 : 1);
		fRec18[0] = ((iTemp9) ? fRec18[1] : 0.000244140625 * fRec16[1]);
		fVbargraph1 = FAUSTFLOAT(fRec18[0]);
		int iTemp14 = iRec25[1] < 4096;
		fRec27[0] = fSlow46 + 0.999 * fRec27[1];
		double fTemp15 = fSlow4 * fRec29[1];
		fRec31[0] = -(fSlow37 * (fSlow35 * fRec31[1] - fSlow12 * (fTemp3 - fVec3[1])));
		fRec30[0] = fRec31[0] - fSlow15 * (fSlow13 * fRec30[2] + fSlow11 * fRec30[1]);
		fRec29[0] = fSlow49 * (fRec30[2] + (fRec30[0] - 2.0 * fRec30[1])) - fSlow48 * (fSlow47 * fRec29[2] + fTemp15);
		fRec32[0] = fSlow51 + 0.999 * fRec32[1];
		double fTemp16 = std::max<double>(-1.0, std::min<double>(1.0, fRec32[0] + fSlow50 * (fRec29[2] + fSlow48 * (fTemp15 + fSlow47 * fRec29[0]))));
		double fTemp17 = fTemp16 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp16));
		fVec7[0] = fTemp17;
		fRec28[0] = fConst4 * (fTemp17 - fVec7[1] + fConst3 * fRec28[1]);
		double fTemp18 = fRec28[0] * fRec27[0];
		double fTemp19 = std::max<double>(fConst1, std::fabs(fTemp18));
		fRec24[0] = ((iTemp14) ? fTemp19 + fRec24[1] : fTemp19);
		iRec25[0] = ((iTemp14) ? iRec25[1] + 1 : 1);
		fRec26[0] = ((iTemp14) ? fRec26[1] : 0.000244140625 * fRec24[1]);
		fVbargraph2 = FAUSTFLOAT(fRec26[0]);
		int iTemp20 = iRec34[1] < 4096;
		fRec36[0] = fSlow52 + 0.999 * fRec36[1];
		double fTemp21 = fSlow4 * fRec38[1];
		double fTemp22 = fSlow11 * fRec39[1];
		fRec41[0] = -(fSlow34 * (fSlow32 * fRec41[1] - fSlow19 * (fTemp2 - fVec2[1])));
		fRec40[0] = fRec41[0] - fSlow22 * (fSlow20 * fRec40[2] + fSlow18 * fRec40[1]);
		fRec39[0] = fSlow55 * (fRec40[2] + (fRec40[0] - 2.0 * fRec40[1])) - fSlow54 * (fSlow53 * fRec39[2] + fTemp22);
		fRec38[0] = fRec39[2] + fSlow54 * (fTemp22 + fSlow53 * fRec39[0]) - fSlow48 * (fSlow47 * fRec38[2] + fTemp21);
		fRec42[0] = fSlow57 + 0.999 * fRec42[1];
		double fTemp23 = std::max<double>(-1.0, std::min<double>(1.0, fRec42[0] + fSlow56 * (fRec38[2] + fSlow48 * (fTemp21 + fSlow47 * fRec38[0]))));
		double fTemp24 = fTemp23 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp23));
		fVec8[0] = fTemp24;
		fRec37[0] = fConst4 * (fTemp24 - fVec8[1] + fConst3 * fRec37[1]);
		double fTemp25 = fRec37[0] * fRec36[0];
		double fTemp26 = std::max<double>(fConst1, std::fabs(fTemp25));
		fRec33[0] = ((iTemp20) ? fTemp26 + fRec33[1] : fTemp26);
		iRec34[0] = ((iTemp20) ? iRec34[1] + 1 : 1);
		fRec35[0] = ((iTemp20) ? fRec35[1] : 0.000244140625 * fRec33[1]);
		fVbargraph3 = FAUSTFLOAT(fRec35[0]);
		int iTemp27 = iRec44[1] < 4096;
		fRec46[0] = fSlow58 + 0.999 * fRec46[1];
		double fTemp28 = fSlow4 * fRec48[1];
		double fTemp29 = fSlow11 * fRec49[1];
		double fTemp30 = fSlow18 * fRec50[1];
		fRec52[0] = -(fSlow31 * (fSlow30 * fRec52[1] - fSlow26 * (fTemp1 - fVec1[1])));
		fRec51[0] = fRec52[0] - fSlow29 * (fSlow27 * fRec51[2] + fSlow25 * fRec51[1]);
		fRec50[0] = fSlow61 * (fRec51[2] + (fRec51[0] - 2.0 * fRec51[1])) - fSlow60 * (fSlow59 * fRec50[2] + fTemp30);
		fRec49[0] = fRec50[2] + fSlow60 * (fTemp30 + fSlow59 * fRec50[0]) - fSlow54 * (fSlow53 * fRec49[2] + fTemp29);
		fRec48[0] = fRec49[2] + fSlow54 * (fTemp29 + fSlow53 * fRec49[0]) - fSlow48 * (fSlow47 * fRec48[2] + fTemp28);
		fRec53[0] = fSlow63 + 0.999 * fRec53[1];
		double fTemp31 = std::max<double>(-1.0, std::min<double>(1.0, fRec53[0] + fSlow62 * (fRec48[2] + fSlow48 * (fTemp28 + fSlow47 * fRec48[0]))));
		double fTemp32 = fTemp31 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp31));
		fVec9[0] = fTemp32;
		fRec47[0] = fConst4 * (fTemp32 - fVec9[1] + fConst3 * fRec47[1]);
		double fTemp33 = fRec47[0] * fRec46[0];
		double fTemp34 = std::max<double>(fConst1, std::fabs(fTemp33));
		fRec43[0] = ((iTemp27) ? fTemp34 + fRec43[1] : fTemp34);
		iRec44[0] = ((iTemp27) ? iRec44[1] + 1 : 1);
		fRec45[0] = ((iTemp27) ? fRec45[1] : 0.000244140625 * fRec43[1]);
		fVbargraph4 = FAUSTFLOAT(fRec45[0]);
		buf[i0] = FAUSTFLOAT((fTemp33 + fTemp25 + fTemp18 + fTemp12 + fTemp7) * fRec0[0]);
		iVec0[1] = iVec0[0];
		fRec0[1] = fRec0[0];
		fRec4[1] = fRec4[0];
		fRec14[1] = fRec14[0];
		fVec1[1] = fVec1[0];
		fRec13[1] = fRec13[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fVec2[1] = fVec2[0];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fVec3[1] = fVec3[0];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fVec4[1] = fVec4[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec15[1] = fRec15[0];
		fVec5[1] = fVec5[0];
		fRec5[1] = fRec5[0];
		fRec1[1] = fRec1[0];
		iRec2[1] = iRec2[0];
		fRec3[1] = fRec3[0];
		fRec19[1] = fRec19[0];
		fRec22[1] = fRec22[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		fRec23[1] = fRec23[0];
		fVec6[1] = fVec6[0];
		fRec20[1] = fRec20[0];
		fRec16[1] = fRec16[0];
		iRec17[1] = iRec17[0];
		fRec18[1] = fRec18[0];
		fRec27[1] = fRec27[0];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fRec29[2] = fRec29[1];
		fRec29[1] = fRec29[0];
		fRec32[1] = fRec32[0];
		fVec7[1] = fVec7[0];
		fRec28[1] = fRec28[0];
		fRec24[1] = fRec24[0];
		iRec25[1] = iRec25[0];
		fRec26[1] = fRec26[0];
		fRec36[1] = fRec36[0];
		fRec41[1] = fRec41[0];
		fRec40[2] = fRec40[1];
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		fRec42[1] = fRec42[0];
		fVec8[1] = fVec8[0];
		fRec37[1] = fRec37[0];
		fRec33[1] = fRec33[0];
		iRec34[1] = iRec34[0];
		fRec35[1] = fRec35[0];
		fRec46[1] = fRec46[0];
		fRec52[1] = fRec52[0];
		fRec51[2] = fRec51[1];
		fRec51[1] = fRec51[0];
		fRec50[2] = fRec50[1];
		fRec50[1] = fRec50[0];
		fRec49[2] = fRec49[1];
		fRec49[1] = fRec49[0];
		fRec48[2] = fRec48[1];
		fRec48[1] = fRec48[0];
		fRec53[1] = fRec53[0];
		fVec9[1] = fVec9[0];
		fRec47[1] = fRec47[0];
		fRec43[1] = fRec43[0];
		iRec44[1] = iRec44[0];
		fRec45[1] = fRec45[0];
	}
	smp.down(buf, output0);
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("mbd.Drive1","","S",N_("Amount of distortion"),&fHslider4, 0.0, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("mbd.Drive2","","S",N_("Amount of distortion"),&fHslider6, 0.0, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("mbd.Drive3","","S",N_("Amount of distortion"),&fHslider8, 0.0, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("mbd.Drive4","","S",N_("Amount of distortion"),&fHslider10, 0.0, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("mbd.Drive5","","S",N_("Amount of distortion"),&fHslider12, 0.0, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("mbd.Gain","","S","",&fVslider0, 0.0, -4e+01, 4.0, 0.1, 0);
	reg.registerFloatVar("mbd.Gain1","","S","",&fVslider1, 0.0, -25.0, 4.0, 0.1, 0);
	reg.registerFloatVar("mbd.Gain2","","S","",&fVslider2, 0.0, -25.0, 4.0, 0.1, 0);
	reg.registerFloatVar("mbd.Gain3","","S","",&fVslider3, 0.0, -25.0, 4.0, 0.1, 0);
	reg.registerFloatVar("mbd.Gain4","","S","",&fVslider4, 0.0, -25.0, 4.0, 0.1, 0);
	reg.registerFloatVar("mbd.Gain5","","S","",&fVslider5, 0.0, -25.0, 4.0, 0.1, 0);
	reg.registerFloatVar("mbd.Offset1","","S",N_("Brings in even harmonics"),&fHslider5, 0.0, 0.0, 0.5, 0.01, 0);
	reg.registerFloatVar("mbd.Offset2","","S",N_("Brings in even harmonics"),&fHslider7, 0.0, 0.0, 0.5, 0.01, 0);
	reg.registerFloatVar("mbd.Offset3","","S",N_("Brings in even harmonics"),&fHslider9, 0.0, 0.0, 0.5, 0.01, 0);
	reg.registerFloatVar("mbd.Offset4","","S",N_("Brings in even harmonics"),&fHslider11, 0.0, 0.0, 0.5, 0.01, 0);
	reg.registerFloatVar("mbd.Offset5","","S",N_("Brings in even harmonics"),&fHslider13, 0.0, 0.0, 0.5, 0.01, 0);
	reg.registerFloatVar("mbd.crossover_b1_b2",N_("Crossover B1-B2 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fHslider0, 8e+01, 2e+01, 2e+04, 1.08, 0);
	reg.registerFloatVar("mbd.crossover_b2_b3",N_("Crossover B2-B3 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fHslider1, 2.1e+02, 2e+01, 2e+04, 1.08, 0);
	reg.registerFloatVar("mbd.crossover_b3_b4",N_("Crossover B3-B4 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fHslider2, 1.7e+03, 2e+01, 2e+04, 1.08, 0);
	reg.registerFloatVar("mbd.crossover_b4_b5",N_("Crossover B4-B5 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fHslider3, 5e+03, 2e+01, 2e+04, 1.08, 0);
	reg.registerFloatVar("mbd.v1","","SOLN","",&fVbargraph0, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("mbd.v2","","SOLN","",&fVbargraph1, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("mbd.v3","","SOLN","",&fVbargraph2, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("mbd.v4","","SOLN","",&fVbargraph3, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("mbd.v5","","SOLN","",&fVbargraph4, 0, -7e+01, 5.0, 0, 0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!-- Generated with glade 3.40.0 -->\n\
<interface>\n\
  <requires lib=\"gtk+\" version=\"3.0\"/>\n\
  <requires lib=\"gxwidgets\" version=\"0.0\"/>\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can-focus\">False</property>\n\
    <child>\n\
      <placeholder/>\n\
    </child>\n\
    <child>\n\
      <object class=\"GtkBox\" id=\"vbox1\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can-focus\">False</property>\n\
        <property name=\"orientation\">vertical</property>\n\
        <child>\n\
          <object class=\"GtkBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can-focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GtkBox\" id=\"hbox1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can-focus\">False</property>\n\
                <child>\n\
                  <object class=\"GtkNotebook\" id=\"notebook\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can-focus\">True</property>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can-focus\">False</property>\n\
                        <property name=\"margin-left\">4</property>\n\
                        <property name=\"margin-right\">4</property>\n\
                        <property name=\"margin-top\">4</property>\n\
                        <property name=\"margin-bottom\">4</property>\n\
                        <property name=\"spacing\">4</property>\n\
                        <child>\n\
                          <object class=\"GtkBox\" id=\"hbox4\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can-focus\">False</property>\n\
                            <child>\n\
                              <object class=\"GtkBox\" id=\"vbox3\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_81:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can-focus\">False</property>\n\
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
                                    <property name=\"can-focus\">True</property>\n\
                                    <property name=\"receives-default\">True</property>\n\
                                    <property name=\"show-fill-level\">True</property>\n\
                                    <property name=\"var_id\">mbd.Drive1</property>\n\
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
                              <object class=\"GtkBox\" id=\"vbox4\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_91:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can-focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Offset</property>\n\
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
                                    <property name=\"can-focus\">True</property>\n\
                                    <property name=\"receives-default\">True</property>\n\
                                    <property name=\"var_id\">mbd.Offset1</property>\n\
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
                            <child>\n\
                              <object class=\"GtkBox\" id=\"vbox6\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_10:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can-focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Gain</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GxSmallKnobR\" id=\"gxmediumknob3\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can-focus\">True</property>\n\
                                    <property name=\"receives-default\">True</property>\n\
                                    <property name=\"var_id\">mbd.Gain1</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">False</property>\n\
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
                          <!-- n-columns=3 n-rows=3 -->\n\
                          <object class=\"GtkGrid\" id=\"table1\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can-focus\">False</property>\n\
                            <property name=\"halign\">center</property>\n\
                            <property name=\"margin-left\">4</property>\n\
                            <property name=\"margin-right\">4</property>\n\
                            <property name=\"margin-top\">4</property>\n\
                            <property name=\"margin-bottom\">4</property>\n\
                            <property name=\"row-spacing\">4</property>\n\
                            <property name=\"column-spacing\">4</property>\n\
                            <property name=\"row-homogeneous\">True</property>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_141:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"hexpand\">True</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left-attach\">0</property>\n\
                                <property name=\"top-attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob2\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">True</property>\n\
                                <property name=\"receives-default\">True</property>\n\
                                <property name=\"var_id\">mbd.crossover_b1_b2</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left-attach\">1</property>\n\
                                <property name=\"top-attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left-attach\">0</property>\n\
                                <property name=\"top-attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
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
                        <property name=\"can-focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Band 1</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"tab-fill\">False</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox5\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can-focus\">False</property>\n\
                        <property name=\"margin-left\">4</property>\n\
                        <property name=\"margin-right\">4</property>\n\
                        <property name=\"margin-top\">4</property>\n\
                        <property name=\"margin-bottom\">4</property>\n\
                        <property name=\"spacing\">4</property>\n\
                        <child>\n\
                          <object class=\"GtkBox\" id=\"hbox6\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can-focus\">False</property>\n\
                            <child>\n\
                              <object class=\"GtkBox\" id=\"vbox8\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_8:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can-focus\">False</property>\n\
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
                                    <property name=\"can-focus\">True</property>\n\
                                    <property name=\"receives-default\">True</property>\n\
                                    <property name=\"show-fill-level\">True</property>\n\
                                    <property name=\"var_id\">mbd.Drive2</property>\n\
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
                              <object class=\"GtkBox\" id=\"vbox9\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_9:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can-focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Offset</property>\n\
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
                                    <property name=\"can-focus\">True</property>\n\
                                    <property name=\"receives-default\">True</property>\n\
                                    <property name=\"var_id\">mbd.Offset2</property>\n\
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
                            <child>\n\
                              <object class=\"GtkBox\" id=\"vbox10\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_11:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can-focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Gain</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GxSmallKnobR\" id=\"gxmediumknob6\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can-focus\">True</property>\n\
                                    <property name=\"receives-default\">True</property>\n\
                                    <property name=\"var_id\">mbd.Gain2</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">False</property>\n\
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
                          <!-- n-columns=3 n-rows=3 -->\n\
                          <object class=\"GtkGrid\" id=\"table2\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can-focus\">False</property>\n\
                            <property name=\"halign\">center</property>\n\
                            <property name=\"margin-left\">4</property>\n\
                            <property name=\"margin-right\">4</property>\n\
                            <property name=\"margin-top\">4</property>\n\
                            <property name=\"margin-bottom\">4</property>\n\
                            <property name=\"row-spacing\">4</property>\n\
                            <property name=\"column-spacing\">4</property>\n\
                            <property name=\"row-homogeneous\">True</property>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_13:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"hexpand\">True</property>\n\
                                <property name=\"label\" translatable=\"yes\">Low</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left-attach\">0</property>\n\
                                <property name=\"top-attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob7\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">True</property>\n\
                                <property name=\"receives-default\">True</property>\n\
                                <property name=\"var_id\">mbd.crossover_b1_b2</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left-attach\">1</property>\n\
                                <property name=\"top-attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_14:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"hexpand\">True</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left-attach\">0</property>\n\
                                <property name=\"top-attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob6\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">True</property>\n\
                                <property name=\"receives-default\">True</property>\n\
                                <property name=\"var_id\">mbd.crossover_b2_b3</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left-attach\">1</property>\n\
                                <property name=\"top-attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
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
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child type=\"tab\">\n\
                      <object class=\"GtkLabel\" id=\"label2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can-focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Band 2</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">1</property>\n\
                        <property name=\"tab-fill\">False</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox7\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can-focus\">False</property>\n\
                        <property name=\"margin-left\">4</property>\n\
                        <property name=\"margin-right\">4</property>\n\
                        <property name=\"margin-top\">4</property>\n\
                        <property name=\"margin-bottom\">4</property>\n\
                        <property name=\"spacing\">4</property>\n\
                        <child>\n\
                          <object class=\"GtkBox\" id=\"hbox8\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can-focus\">False</property>\n\
                            <child>\n\
                              <object class=\"GtkBox\" id=\"vbox7\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_82:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can-focus\">False</property>\n\
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
                                    <property name=\"can-focus\">True</property>\n\
                                    <property name=\"receives-default\">True</property>\n\
                                    <property name=\"show-fill-level\">True</property>\n\
                                    <property name=\"var_id\">mbd.Drive3</property>\n\
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
                              <object class=\"GtkBox\" id=\"vbox11\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_92:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can-focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Offset</property>\n\
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
                                    <property name=\"can-focus\">True</property>\n\
                                    <property name=\"receives-default\">True</property>\n\
                                    <property name=\"var_id\">mbd.Offset3</property>\n\
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
                            <child>\n\
                              <object class=\"GtkBox\" id=\"vbox12\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_12:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can-focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Gain</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GxSmallKnobR\" id=\"gxmediumknob9\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can-focus\">True</property>\n\
                                    <property name=\"receives-default\">True</property>\n\
                                    <property name=\"var_id\">mbd.Gain3</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">False</property>\n\
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
                          <!-- n-columns=3 n-rows=3 -->\n\
                          <object class=\"GtkGrid\" id=\"table3\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can-focus\">False</property>\n\
                            <property name=\"halign\">center</property>\n\
                            <property name=\"margin-left\">4</property>\n\
                            <property name=\"margin-right\">4</property>\n\
                            <property name=\"margin-top\">4</property>\n\
                            <property name=\"margin-bottom\">4</property>\n\
                            <property name=\"row-spacing\">4</property>\n\
                            <property name=\"column-spacing\">4</property>\n\
                            <property name=\"row-homogeneous\">True</property>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_132:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"hexpand\">True</property>\n\
                                <property name=\"label\" translatable=\"yes\">Low</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left-attach\">0</property>\n\
                                <property name=\"top-attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob3\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">True</property>\n\
                                <property name=\"receives-default\">True</property>\n\
                                <property name=\"var_id\">mbd.crossover_b2_b3</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left-attach\">1</property>\n\
                                <property name=\"top-attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_142:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"hexpand\">True</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left-attach\">0</property>\n\
                                <property name=\"top-attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob4\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">True</property>\n\
                                <property name=\"receives-default\">True</property>\n\
                                <property name=\"var_id\">mbd.crossover_b3_b4</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left-attach\">1</property>\n\
                                <property name=\"top-attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
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
                        <property name=\"position\">2</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child type=\"tab\">\n\
                      <object class=\"GtkLabel\" id=\"label3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can-focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Band 3</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">2</property>\n\
                        <property name=\"tab-fill\">False</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox9\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can-focus\">False</property>\n\
                        <property name=\"margin-left\">4</property>\n\
                        <property name=\"margin-right\">4</property>\n\
                        <property name=\"margin-top\">4</property>\n\
                        <property name=\"margin-bottom\">4</property>\n\
                        <property name=\"spacing\">4</property>\n\
                        <child>\n\
                          <object class=\"GtkBox\" id=\"hbox10\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can-focus\">False</property>\n\
                            <child>\n\
                              <object class=\"GtkBox\" id=\"vbox14\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_83:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can-focus\">False</property>\n\
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
                                    <property name=\"can-focus\">True</property>\n\
                                    <property name=\"receives-default\">True</property>\n\
                                    <property name=\"show-fill-level\">True</property>\n\
                                    <property name=\"var_id\">mbd.Drive4</property>\n\
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
                              <object class=\"GtkBox\" id=\"vbox15\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_93:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can-focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Offset</property>\n\
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
                                    <property name=\"can-focus\">True</property>\n\
                                    <property name=\"receives-default\">True</property>\n\
                                    <property name=\"var_id\">mbd.Offset4</property>\n\
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
                            <child>\n\
                              <object class=\"GtkBox\" id=\"vbox13\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_1:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can-focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Gain</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GxSmallKnobR\" id=\"gxmediumknob12\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can-focus\">True</property>\n\
                                    <property name=\"receives-default\">True</property>\n\
                                    <property name=\"var_id\">mbd.Gain4</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">False</property>\n\
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
                          <!-- n-columns=3 n-rows=3 -->\n\
                          <object class=\"GtkGrid\" id=\"table4\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can-focus\">False</property>\n\
                            <property name=\"halign\">center</property>\n\
                            <property name=\"margin-left\">4</property>\n\
                            <property name=\"margin-right\">4</property>\n\
                            <property name=\"margin-top\">4</property>\n\
                            <property name=\"margin-bottom\">4</property>\n\
                            <property name=\"row-spacing\">4</property>\n\
                            <property name=\"column-spacing\">4</property>\n\
                            <property name=\"row-homogeneous\">True</property>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_133:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"hexpand\">True</property>\n\
                                <property name=\"label\" translatable=\"yes\">Low</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left-attach\">0</property>\n\
                                <property name=\"top-attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob5\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">True</property>\n\
                                <property name=\"receives-default\">True</property>\n\
                                <property name=\"var_id\">mbd.crossover_b3_b4</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left-attach\">1</property>\n\
                                <property name=\"top-attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_143:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"hexpand\">True</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left-attach\">0</property>\n\
                                <property name=\"top-attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob8\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">True</property>\n\
                                <property name=\"receives-default\">True</property>\n\
                                <property name=\"var_id\">mbd.crossover_b4_b5</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left-attach\">1</property>\n\
                                <property name=\"top-attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
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
                        <property name=\"position\">3</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child type=\"tab\">\n\
                      <object class=\"GtkLabel\" id=\"label4\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can-focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Band 4</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">3</property>\n\
                        <property name=\"tab-fill\">False</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox11\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can-focus\">False</property>\n\
                        <property name=\"margin-left\">4</property>\n\
                        <property name=\"margin-right\">4</property>\n\
                        <property name=\"margin-top\">4</property>\n\
                        <property name=\"margin-bottom\">4</property>\n\
                        <property name=\"spacing\">4</property>\n\
                        <child>\n\
                          <object class=\"GtkBox\" id=\"hbox12\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can-focus\">False</property>\n\
                            <child>\n\
                              <object class=\"GtkBox\" id=\"vbox18\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_84:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can-focus\">False</property>\n\
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
                                    <property name=\"can-focus\">True</property>\n\
                                    <property name=\"receives-default\">True</property>\n\
                                    <property name=\"show-fill-level\">True</property>\n\
                                    <property name=\"var_id\">mbd.Drive5</property>\n\
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
                              <object class=\"GtkBox\" id=\"vbox19\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_94:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can-focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Offset</property>\n\
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
                                    <property name=\"can-focus\">True</property>\n\
                                    <property name=\"receives-default\">True</property>\n\
                                    <property name=\"var_id\">mbd.Offset5</property>\n\
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
                            <child>\n\
                              <object class=\"GtkBox\" id=\"vbox16\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_15:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can-focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Gain</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GxSmallKnobR\" id=\"gxmediumknob15\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can-focus\">True</property>\n\
                                    <property name=\"receives-default\">True</property>\n\
                                    <property name=\"var_id\">mbd.Gain5</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">False</property>\n\
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
                          <!-- n-columns=3 n-rows=3 -->\n\
                          <object class=\"GtkGrid\" id=\"table5\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can-focus\">False</property>\n\
                            <property name=\"halign\">center</property>\n\
                            <property name=\"margin-left\">4</property>\n\
                            <property name=\"margin-right\">4</property>\n\
                            <property name=\"margin-top\">4</property>\n\
                            <property name=\"margin-bottom\">4</property>\n\
                            <property name=\"row-spacing\">4</property>\n\
                            <property name=\"column-spacing\">4</property>\n\
                            <property name=\"row-homogeneous\">True</property>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_134:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                                <property name=\"hexpand\">True</property>\n\
                                <property name=\"label\" translatable=\"yes\">Low</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left-attach\">0</property>\n\
                                <property name=\"top-attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob9\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">True</property>\n\
                                <property name=\"receives-default\">True</property>\n\
                                <property name=\"var_id\">mbd.crossover_b4_b5</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left-attach\">1</property>\n\
                                <property name=\"top-attach\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can-focus\">False</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left-attach\">0</property>\n\
                                <property name=\"top-attach\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
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
                        <property name=\"can-focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Band 5</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">4</property>\n\
                        <property name=\"tab-fill\">False</property>\n\
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
                    <property name=\"can-focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label_99:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can-focus\">False</property>\n\
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
                        <property name=\"can-focus\">True</property>\n\
                        <property name=\"receives-default\">True</property>\n\
                        <property name=\"var_id\">mbd.Gain</property>\n\
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
                    <property name=\"can-focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label5:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can-focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Levels</property>\n\
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
                        <property name=\"can-focus\">False</property>\n\
                        <property name=\"margin-bottom\">4</property>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter1\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can-focus\">False</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbd.v1</property>\n\
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
                            <property name=\"can-focus\">False</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbd.v2</property>\n\
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
                            <property name=\"can-focus\">False</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbd.v3</property>\n\
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
                            <property name=\"can-focus\">False</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbd.v4</property>\n\
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
                            <property name=\"can-focus\">False</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbd.v5</property>\n\
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
            <property name=\"can-focus\">False</property>\n\
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
#define PARAM(p) ("mbd" "." p)

b.openHorizontalhideBox("");
b.create_master_slider(PARAM("Gain"), N_("Gain"));
b.closeBox();

b.openHorizontalBox("");
b.openVerticalBox("");

b.openTabBox("");

b.openHorizontalBox(N_("Band 1"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Drive1"), N_("Drive"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Offset1"), N_("Offset"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Gain1"), N_("Gain"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b1_b2"), N_("Low Shelf (Hz)"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 2"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Drive2"), N_("Drive"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Offset2"), N_("Offset"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Gain2"), N_("Gain"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b1_b2"), N_("Low (Hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b2_b3"), N_("High (hz)"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 3"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Drive3"), N_("Drive"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Offset3"), N_("Offset"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Gain3"), N_("Gain"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b2_b3"), N_("Low (Hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b3_b4"), N_("High (hz)"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 4"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Drive4"), N_("Drive"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Offset4"), N_("Offset"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Gain4"), N_("Gain"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b3_b4"), N_("Low (Hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b4_b5"), N_("High (hz)"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 5"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Drive5"), N_("Drive"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Offset5"), N_("Offset"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Gain5"), N_("Gain"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b4_b5"), N_("High Shelf (Hz)"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.closeBox();
b.closeBox();
b.create_small_rackknob(PARAM("Gain"), N_("Gain"));
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

} // end namespace mbd
} // end namespace pluginlib
