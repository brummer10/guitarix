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
	double fConst2;
	double fConst3;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	double fRec13[2];
	double fVec1[2];
	double fRec12[2];
	double fRec11[3];
	double fVec2[2];
	double fRec10[2];
	double fRec9[3];
	double fVec3[2];
	double fRec8[2];
	double fRec7[3];
	double fVec4[2];
	double fRec6[2];
	double fRec5[3];
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	double fRec14[2];
	double fVec5[2];
	double fConst4;
	double fRec4[2];
	double fRec1[2];
	int iRec2[2];
	double fRec3[2];
	FAUSTFLOAT fVbargraph0;
	double fRec20[2];
	double fRec19[3];
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT fHslider7;
	double fRec21[2];
	double fVec6[2];
	double fRec18[2];
	double fRec15[2];
	int iRec16[2];
	double fRec17[2];
	FAUSTFLOAT fVbargraph1;
	double fRec28[2];
	double fRec27[3];
	double fRec26[3];
	FAUSTFLOAT fHslider8;
	FAUSTFLOAT fHslider9;
	double fRec29[2];
	double fVec7[2];
	double fRec25[2];
	double fRec22[2];
	int iRec23[2];
	double fRec24[2];
	FAUSTFLOAT fVbargraph2;
	double fRec37[2];
	double fRec36[3];
	double fRec35[3];
	double fRec34[3];
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT fHslider11;
	double fRec38[2];
	double fVec8[2];
	double fRec33[2];
	double fRec30[2];
	int iRec31[2];
	double fRec32[2];
	FAUSTFLOAT fVbargraph3;
	double fRec47[2];
	double fRec46[3];
	double fRec45[3];
	double fRec44[3];
	double fRec43[3];
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT fHslider13;
	double fRec48[2];
	double fVec9[2];
	double fRec42[2];
	double fRec39[2];
	int iRec40[2];
	double fRec41[2];
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
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec13[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fVec1[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec12[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec11[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fVec2[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec10[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec9[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fVec3[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec8[l10] = 0.0;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec7[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fVec4[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec6[l13] = 0.0;
	for (int l14 = 0; l14 < 3; l14 = l14 + 1) fRec5[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec14[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fVec5[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec4[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec1[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) iRec2[l19] = 0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec3[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec20[l21] = 0.0;
	for (int l22 = 0; l22 < 3; l22 = l22 + 1) fRec19[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec21[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fVec6[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec18[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec15[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) iRec16[l27] = 0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec17[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec28[l29] = 0.0;
	for (int l30 = 0; l30 < 3; l30 = l30 + 1) fRec27[l30] = 0.0;
	for (int l31 = 0; l31 < 3; l31 = l31 + 1) fRec26[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fRec29[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fVec7[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fRec25[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec22[l35] = 0.0;
	for (int l36 = 0; l36 < 2; l36 = l36 + 1) iRec23[l36] = 0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec24[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fRec37[l38] = 0.0;
	for (int l39 = 0; l39 < 3; l39 = l39 + 1) fRec36[l39] = 0.0;
	for (int l40 = 0; l40 < 3; l40 = l40 + 1) fRec35[l40] = 0.0;
	for (int l41 = 0; l41 < 3; l41 = l41 + 1) fRec34[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) fRec38[l42] = 0.0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fVec8[l43] = 0.0;
	for (int l44 = 0; l44 < 2; l44 = l44 + 1) fRec33[l44] = 0.0;
	for (int l45 = 0; l45 < 2; l45 = l45 + 1) fRec30[l45] = 0.0;
	for (int l46 = 0; l46 < 2; l46 = l46 + 1) iRec31[l46] = 0;
	for (int l47 = 0; l47 < 2; l47 = l47 + 1) fRec32[l47] = 0.0;
	for (int l48 = 0; l48 < 2; l48 = l48 + 1) fRec47[l48] = 0.0;
	for (int l49 = 0; l49 < 3; l49 = l49 + 1) fRec46[l49] = 0.0;
	for (int l50 = 0; l50 < 3; l50 = l50 + 1) fRec45[l50] = 0.0;
	for (int l51 = 0; l51 < 3; l51 = l51 + 1) fRec44[l51] = 0.0;
	for (int l52 = 0; l52 < 3; l52 = l52 + 1) fRec43[l52] = 0.0;
	for (int l53 = 0; l53 < 2; l53 = l53 + 1) fRec48[l53] = 0.0;
	for (int l54 = 0; l54 < 2; l54 = l54 + 1) fVec9[l54] = 0.0;
	for (int l55 = 0; l55 < 2; l55 = l55 + 1) fRec42[l55] = 0.0;
	for (int l56 = 0; l56 < 2; l56 = l56 + 1) fRec39[l56] = 0.0;
	for (int l57 = 0; l57 < 2; l57 = l57 + 1) iRec40[l57] = 0;
	for (int l58 = 0; l58 < 2; l58 = l58 + 1) fRec41[l58] = 0.0;
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
	double fSlow1 = std::tan(fConst2 * double(fHslider0));
	double fSlow2 = mydsp_faustpower2_f(fSlow1);
	double fSlow3 = 2.0 * (1.0 - 1.0 / fSlow2);
	double fSlow4 = 1.0 / fSlow1;
	double fSlow5 = (fSlow4 + -1.0000000000000004) / fSlow1 + 1.0;
	double fSlow6 = (fSlow4 + 1.0000000000000004) / fSlow1 + 1.0;
	double fSlow7 = 1.0 / fSlow6;
	double fSlow8 = std::tan(fConst2 * double(fHslider1));
	double fSlow9 = mydsp_faustpower2_f(fSlow8);
	double fSlow10 = 2.0 * (1.0 - 1.0 / fSlow9);
	double fSlow11 = 1.0 / fSlow8;
	double fSlow12 = (fSlow11 + -1.0000000000000004) / fSlow8 + 1.0;
	double fSlow13 = (fSlow11 + 1.0000000000000004) / fSlow8 + 1.0;
	double fSlow14 = 1.0 / fSlow13;
	double fSlow15 = std::tan(fConst2 * double(fHslider2));
	double fSlow16 = mydsp_faustpower2_f(fSlow15);
	double fSlow17 = 2.0 * (1.0 - 1.0 / fSlow16);
	double fSlow18 = 1.0 / fSlow15;
	double fSlow19 = (fSlow18 + -1.0000000000000004) / fSlow15 + 1.0;
	double fSlow20 = (fSlow18 + 1.0000000000000004) / fSlow15 + 1.0;
	double fSlow21 = 1.0 / fSlow20;
	double fSlow22 = std::tan(fConst2 * double(fHslider3));
	double fSlow23 = mydsp_faustpower2_f(fSlow22);
	double fSlow24 = 2.0 * (1.0 - 1.0 / fSlow23);
	double fSlow25 = 1.0 / fSlow22;
	double fSlow26 = (fSlow25 + -1.0000000000000004) / fSlow22 + 1.0;
	double fSlow27 = (fSlow25 + 1.0000000000000004) / fSlow22 + 1.0;
	double fSlow28 = 1.0 / fSlow27;
	double fSlow29 = 1.0 - fSlow25;
	double fSlow30 = 1.0 / (fSlow25 + 1.0);
	double fSlow31 = 1.0 - fSlow18;
	double fSlow32 = fSlow18 + 1.0;
	double fSlow33 = 1.0 / fSlow32;
	double fSlow34 = 1.0 - fSlow11;
	double fSlow35 = fSlow11 + 1.0;
	double fSlow36 = 1.0 / fSlow35;
	double fSlow37 = 1.0 - fSlow4;
	double fSlow38 = fSlow4 + 1.0;
	double fSlow39 = 1.0 / fSlow38;
	double fSlow40 = std::pow(1e+01, 2.0 * double(fHslider4)) / fSlow6;
	double fSlow41 = 0.0010000000000000009 * double(fHslider5);
	double fSlow42 = std::pow(1e+01, 2.0 * double(fHslider6)) / (fSlow2 * fSlow6);
	double fSlow43 = 0.0010000000000000009 * double(fHslider7);
	double fSlow44 = 1.0 - fSlow37 / fSlow1;
	double fSlow45 = 1.0 / (fSlow38 / fSlow1 + 1.0);
	double fSlow46 = 1.0 / (fSlow9 * fSlow13);
	double fSlow47 = std::pow(1e+01, 2.0 * double(fHslider8));
	double fSlow48 = 0.0010000000000000009 * double(fHslider9);
	double fSlow49 = 1.0 - fSlow34 / fSlow8;
	double fSlow50 = 1.0 / (fSlow35 / fSlow8 + 1.0);
	double fSlow51 = 1.0 / (fSlow16 * fSlow20);
	double fSlow52 = std::pow(1e+01, 2.0 * double(fHslider10));
	double fSlow53 = 0.0010000000000000009 * double(fHslider11);
	double fSlow54 = 1.0 - fSlow31 / fSlow15;
	double fSlow55 = 1.0 / (fSlow32 / fSlow15 + 1.0);
	double fSlow56 = 1.0 / (fSlow23 * fSlow27);
	double fSlow57 = std::pow(1e+01, 2.0 * double(fHslider12));
	double fSlow58 = 0.0010000000000000009 * double(fHslider13);
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		iVec0[0] = 1;
		fRec0[0] = fSlow0 + 0.999 * fRec0[1];
		int iTemp0 = iRec2[1] < 4096;
		fRec13[0] = 1e-20 * double(1 - iVec0[1]) - fRec13[1];
		double fTemp1 = double(buf[i0]) + fRec13[0];
		fVec1[0] = fTemp1;
		fRec12[0] = -(fSlow30 * (fSlow29 * fRec12[1] - (fTemp1 + fVec1[1])));
		fRec11[0] = fRec12[0] - fSlow28 * (fSlow26 * fRec11[2] + fSlow24 * fRec11[1]);
		double fTemp2 = fSlow28 * (fRec11[2] + fRec11[0] + 2.0 * fRec11[1]);
		fVec2[0] = fTemp2;
		fRec10[0] = -(fSlow33 * (fSlow31 * fRec10[1] - (fTemp2 + fVec2[1])));
		fRec9[0] = fRec10[0] - fSlow21 * (fSlow19 * fRec9[2] + fSlow17 * fRec9[1]);
		double fTemp3 = fSlow21 * (fRec9[2] + fRec9[0] + 2.0 * fRec9[1]);
		fVec3[0] = fTemp3;
		fRec8[0] = -(fSlow36 * (fSlow34 * fRec8[1] - (fTemp3 + fVec3[1])));
		fRec7[0] = fRec8[0] - fSlow14 * (fSlow12 * fRec7[2] + fSlow10 * fRec7[1]);
		double fTemp4 = fSlow14 * (fRec7[2] + fRec7[0] + 2.0 * fRec7[1]);
		fVec4[0] = fTemp4;
		fRec6[0] = -(fSlow39 * (fSlow37 * fRec6[1] - (fTemp4 + fVec4[1])));
		fRec5[0] = fRec6[0] - fSlow7 * (fSlow5 * fRec5[2] + fSlow3 * fRec5[1]);
		fRec14[0] = fSlow41 + 0.999 * fRec14[1];
		double fTemp5 = std::max<double>(-1.0, std::min<double>(1.0, fRec14[0] + fSlow40 * (fRec5[2] + fRec5[0] + 2.0 * fRec5[1])));
		double fTemp6 = fTemp5 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp5));
		fVec5[0] = fTemp6;
		fRec4[0] = fConst4 * (fTemp6 - fVec5[1] + fConst3 * fRec4[1]);
		double fTemp7 = std::max<double>(fConst1, std::fabs(fRec4[0]));
		fRec1[0] = ((iTemp0) ? fTemp7 + fRec1[1] : fTemp7);
		iRec2[0] = ((iTemp0) ? iRec2[1] + 1 : 1);
		fRec3[0] = ((iTemp0) ? fRec3[1] : 0.000244140625 * fRec1[1]);
		fVbargraph0 = FAUSTFLOAT(fRec3[0]);
		int iTemp8 = iRec16[1] < 4096;
		fRec20[0] = -(fSlow39 * (fSlow37 * fRec20[1] - fSlow4 * (fTemp4 - fVec4[1])));
		fRec19[0] = fRec20[0] - fSlow7 * (fSlow5 * fRec19[2] + fSlow3 * fRec19[1]);
		fRec21[0] = fSlow43 + 0.999 * fRec21[1];
		double fTemp9 = std::max<double>(-1.0, std::min<double>(1.0, fRec21[0] + fSlow42 * (fRec19[2] + (fRec19[0] - 2.0 * fRec19[1]))));
		double fTemp10 = fTemp9 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp9));
		fVec6[0] = fTemp10;
		fRec18[0] = fConst4 * (fTemp10 - fVec6[1] + fConst3 * fRec18[1]);
		double fTemp11 = std::max<double>(fConst1, std::fabs(fRec18[0]));
		fRec15[0] = ((iTemp8) ? fTemp11 + fRec15[1] : fTemp11);
		iRec16[0] = ((iTemp8) ? iRec16[1] + 1 : 1);
		fRec17[0] = ((iTemp8) ? fRec17[1] : 0.000244140625 * fRec15[1]);
		fVbargraph1 = FAUSTFLOAT(fRec17[0]);
		int iTemp12 = iRec23[1] < 4096;
		double fTemp13 = fSlow3 * fRec26[1];
		fRec28[0] = -(fSlow36 * (fSlow34 * fRec28[1] - fSlow11 * (fTemp3 - fVec3[1])));
		fRec27[0] = fRec28[0] - fSlow14 * (fSlow12 * fRec27[2] + fSlow10 * fRec27[1]);
		fRec26[0] = fSlow46 * (fRec27[2] + (fRec27[0] - 2.0 * fRec27[1])) - fSlow45 * (fSlow44 * fRec26[2] + fTemp13);
		fRec29[0] = fSlow48 + 0.999 * fRec29[1];
		double fTemp14 = std::max<double>(-1.0, std::min<double>(1.0, fRec29[0] + fSlow47 * (fRec26[2] + fSlow45 * (fTemp13 + fSlow44 * fRec26[0]))));
		double fTemp15 = fTemp14 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp14));
		fVec7[0] = fTemp15;
		fRec25[0] = fConst4 * (fTemp15 - fVec7[1] + fConst3 * fRec25[1]);
		double fTemp16 = std::max<double>(fConst1, std::fabs(fRec25[0]));
		fRec22[0] = ((iTemp12) ? fTemp16 + fRec22[1] : fTemp16);
		iRec23[0] = ((iTemp12) ? iRec23[1] + 1 : 1);
		fRec24[0] = ((iTemp12) ? fRec24[1] : 0.000244140625 * fRec22[1]);
		fVbargraph2 = FAUSTFLOAT(fRec24[0]);
		int iTemp17 = iRec31[1] < 4096;
		double fTemp18 = fSlow3 * fRec34[1];
		double fTemp19 = fSlow10 * fRec35[1];
		fRec37[0] = -(fSlow33 * (fSlow31 * fRec37[1] - fSlow18 * (fTemp2 - fVec2[1])));
		fRec36[0] = fRec37[0] - fSlow21 * (fSlow19 * fRec36[2] + fSlow17 * fRec36[1]);
		fRec35[0] = fSlow51 * (fRec36[2] + (fRec36[0] - 2.0 * fRec36[1])) - fSlow50 * (fSlow49 * fRec35[2] + fTemp19);
		fRec34[0] = fRec35[2] + fSlow50 * (fTemp19 + fSlow49 * fRec35[0]) - fSlow45 * (fSlow44 * fRec34[2] + fTemp18);
		fRec38[0] = fSlow53 + 0.999 * fRec38[1];
		double fTemp20 = std::max<double>(-1.0, std::min<double>(1.0, fRec38[0] + fSlow52 * (fRec34[2] + fSlow45 * (fTemp18 + fSlow44 * fRec34[0]))));
		double fTemp21 = fTemp20 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp20));
		fVec8[0] = fTemp21;
		fRec33[0] = fConst4 * (fTemp21 - fVec8[1] + fConst3 * fRec33[1]);
		double fTemp22 = std::max<double>(fConst1, std::fabs(fRec33[0]));
		fRec30[0] = ((iTemp17) ? fTemp22 + fRec30[1] : fTemp22);
		iRec31[0] = ((iTemp17) ? iRec31[1] + 1 : 1);
		fRec32[0] = ((iTemp17) ? fRec32[1] : 0.000244140625 * fRec30[1]);
		fVbargraph3 = FAUSTFLOAT(fRec32[0]);
		int iTemp23 = iRec40[1] < 4096;
		double fTemp24 = fSlow3 * fRec43[1];
		double fTemp25 = fSlow10 * fRec44[1];
		double fTemp26 = fSlow17 * fRec45[1];
		fRec47[0] = -(fSlow30 * (fSlow29 * fRec47[1] - fSlow25 * (fTemp1 - fVec1[1])));
		fRec46[0] = fRec47[0] - fSlow28 * (fSlow26 * fRec46[2] + fSlow24 * fRec46[1]);
		fRec45[0] = fSlow56 * (fRec46[2] + (fRec46[0] - 2.0 * fRec46[1])) - fSlow55 * (fSlow54 * fRec45[2] + fTemp26);
		fRec44[0] = fRec45[2] + fSlow55 * (fTemp26 + fSlow54 * fRec45[0]) - fSlow50 * (fSlow49 * fRec44[2] + fTemp25);
		fRec43[0] = fRec44[2] + fSlow50 * (fTemp25 + fSlow49 * fRec44[0]) - fSlow45 * (fSlow44 * fRec43[2] + fTemp24);
		fRec48[0] = fSlow58 + 0.999 * fRec48[1];
		double fTemp27 = std::max<double>(-1.0, std::min<double>(1.0, fRec48[0] + fSlow57 * (fRec43[2] + fSlow45 * (fTemp24 + fSlow44 * fRec43[0]))));
		double fTemp28 = fTemp27 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp27));
		fVec9[0] = fTemp28;
		fRec42[0] = fConst4 * (fTemp28 - fVec9[1] + fConst3 * fRec42[1]);
		double fTemp29 = std::max<double>(fConst1, std::fabs(fRec42[0]));
		fRec39[0] = ((iTemp23) ? fTemp29 + fRec39[1] : fTemp29);
		iRec40[0] = ((iTemp23) ? iRec40[1] + 1 : 1);
		fRec41[0] = ((iTemp23) ? fRec41[1] : 0.000244140625 * fRec39[1]);
		fVbargraph4 = FAUSTFLOAT(fRec41[0]);
		buf[i0] = FAUSTFLOAT((fRec42[0] + fRec33[0] + fRec25[0] + fRec18[0] + fRec4[0]) * fRec0[0]);
		iVec0[1] = iVec0[0];
		fRec0[1] = fRec0[0];
		fRec13[1] = fRec13[0];
		fVec1[1] = fVec1[0];
		fRec12[1] = fRec12[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fVec2[1] = fVec2[0];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fVec3[1] = fVec3[0];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fVec4[1] = fVec4[0];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec14[1] = fRec14[0];
		fVec5[1] = fVec5[0];
		fRec4[1] = fRec4[0];
		fRec1[1] = fRec1[0];
		iRec2[1] = iRec2[0];
		fRec3[1] = fRec3[0];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fRec21[1] = fRec21[0];
		fVec6[1] = fVec6[0];
		fRec18[1] = fRec18[0];
		fRec15[1] = fRec15[0];
		iRec16[1] = iRec16[0];
		fRec17[1] = fRec17[0];
		fRec28[1] = fRec28[0];
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fRec29[1] = fRec29[0];
		fVec7[1] = fVec7[0];
		fRec25[1] = fRec25[0];
		fRec22[1] = fRec22[0];
		iRec23[1] = iRec23[0];
		fRec24[1] = fRec24[0];
		fRec37[1] = fRec37[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		fRec35[2] = fRec35[1];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec38[1] = fRec38[0];
		fVec8[1] = fVec8[0];
		fRec33[1] = fRec33[0];
		fRec30[1] = fRec30[0];
		iRec31[1] = iRec31[0];
		fRec32[1] = fRec32[0];
		fRec47[1] = fRec47[0];
		fRec46[2] = fRec46[1];
		fRec46[1] = fRec46[0];
		fRec45[2] = fRec45[1];
		fRec45[1] = fRec45[0];
		fRec44[2] = fRec44[1];
		fRec44[1] = fRec44[0];
		fRec43[2] = fRec43[1];
		fRec43[1] = fRec43[0];
		fRec48[1] = fRec48[0];
		fVec9[1] = fVec9[0];
		fRec42[1] = fRec42[0];
		fRec39[1] = fRec39[0];
		iRec40[1] = iRec40[0];
		fRec41[1] = fRec41[0];
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
                        <property name=\"homogeneous\">True</property>\n\
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
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_91:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
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
                                    <property name=\"can_focus\">True</property>\n\
                                    <property name=\"receives_default\">True</property>\n\
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
                            <property name=\"halign\">center</property>\n\
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
                                <property name=\"var_id\">mbd.crossover_b1_b2</property>\n\
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
                        <property name=\"homogeneous\">True</property>\n\
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
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_9:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
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
                                    <property name=\"can_focus\">True</property>\n\
                                    <property name=\"receives_default\">True</property>\n\
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
                            <property name=\"halign\">center</property>\n\
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
                                <property name=\"var_id\">mbd.crossover_b1_b2</property>\n\
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
                                <property name=\"var_id\">mbd.crossover_b2_b3</property>\n\
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
                        <property name=\"homogeneous\">True</property>\n\
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
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_92:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
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
                                    <property name=\"can_focus\">True</property>\n\
                                    <property name=\"receives_default\">True</property>\n\
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
                            <property name=\"halign\">center</property>\n\
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
                                <property name=\"var_id\">mbd.crossover_b2_b3</property>\n\
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
                                <property name=\"var_id\">mbd.crossover_b3_b4</property>\n\
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
                        <property name=\"homogeneous\">True</property>\n\
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
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_93:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
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
                                    <property name=\"can_focus\">True</property>\n\
                                    <property name=\"receives_default\">True</property>\n\
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
                            <property name=\"halign\">center</property>\n\
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
                                <property name=\"var_id\">mbd.crossover_b3_b4</property>\n\
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
                                <property name=\"var_id\">mbd.crossover_b4_b5</property>\n\
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
                        <property name=\"homogeneous\">True</property>\n\
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
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"orientation\">vertical</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_94:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
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
                                    <property name=\"can_focus\">True</property>\n\
                                    <property name=\"receives_default\">True</property>\n\
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
                            <property name=\"halign\">center</property>\n\
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
                                <property name=\"var_id\">mbd.crossover_b4_b5</property>\n\
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
                            <property name=\"can_focus\">False</property>\n\
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
                            <property name=\"can_focus\">False</property>\n\
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
                            <property name=\"can_focus\">False</property>\n\
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
                            <property name=\"can_focus\">False</property>\n\
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
