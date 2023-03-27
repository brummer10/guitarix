// generated from file '../src/LV2/faust/gx_ampmodul.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gx_ampmodul {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst4;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec5[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec11[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec17[2];
	double fVec0[2];
	double fRec16[2];
	double fRec15[3];
	double fConst6;
	double fVec1[2];
	double fConst7;
	double fRec18[2];
	double fRec14[2];
	double fConst8;
	double fConst9;
	double fRec13[2];
	double fConst11;
	double fConst12;
	double fRec19[2];
	double fVec2[2];
	double fConst14;
	double fConst15;
	double fRec12[2];
	double fVec3[2];
	double fRec10[2];
	double fRec9[3];
	double fConst17;
	double fVec4[2];
	double fConst18;
	double fRec20[2];
	double fRec8[2];
	double fRec7[2];
	double fRec21[2];
	double fVec5[2];
	double fRec6[2];
	double fVec6[2];
	double fRec4[2];
	double fRec3[3];
	double fConst20;
	double fVec7[2];
	double fConst21;
	double fRec22[2];
	double fRec2[2];
	double fRec1[2];
	double fRec23[2];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	double fRec0[6];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	double fRec24[6];
	double fVec8[2];
	double fRec39[2];
	double fRec38[3];
	double fVec9[2];
	double fRec40[2];
	double fRec37[2];
	double fRec36[2];
	double fRec41[2];
	double fVec10[2];
	double fRec35[2];
	double fVec11[2];
	double fRec34[2];
	double fRec33[3];
	double fVec12[2];
	double fRec42[2];
	double fRec32[2];
	double fRec31[2];
	double fRec43[2];
	double fVec13[2];
	double fRec30[2];
	double fVec14[2];
	double fRec29[2];
	double fRec28[3];
	double fVec15[2];
	double fRec44[2];
	double fRec27[2];
	double fRec26[2];
	double fRec45[2];
	double fRec25[6];
	double fRec46[6];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "ampmodul";
	name = N_("Postamp");
	mono_audio = 0;
	stereo_audio = compute_static;
	set_samplerate = init_static;
	activate_plugin = 0;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec5[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec11[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec17[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fVec0[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec16[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec15[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fVec1[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec18[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec14[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec13[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec19[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fVec2[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec12[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fVec3[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec10[l14] = 0.0;
	for (int l15 = 0; l15 < 3; l15 = l15 + 1) fRec9[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fVec4[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec20[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec8[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec7[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec21[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fVec5[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec6[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fVec6[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec4[l24] = 0.0;
	for (int l25 = 0; l25 < 3; l25 = l25 + 1) fRec3[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fVec7[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec22[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec2[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec1[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec23[l30] = 0.0;
	for (int l31 = 0; l31 < 6; l31 = l31 + 1) fRec0[l31] = 0.0;
	for (int l32 = 0; l32 < 6; l32 = l32 + 1) fRec24[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fVec8[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fRec39[l34] = 0.0;
	for (int l35 = 0; l35 < 3; l35 = l35 + 1) fRec38[l35] = 0.0;
	for (int l36 = 0; l36 < 2; l36 = l36 + 1) fVec9[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec40[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fRec37[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec36[l39] = 0.0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec41[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fVec10[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) fRec35[l42] = 0.0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fVec11[l43] = 0.0;
	for (int l44 = 0; l44 < 2; l44 = l44 + 1) fRec34[l44] = 0.0;
	for (int l45 = 0; l45 < 3; l45 = l45 + 1) fRec33[l45] = 0.0;
	for (int l46 = 0; l46 < 2; l46 = l46 + 1) fVec12[l46] = 0.0;
	for (int l47 = 0; l47 < 2; l47 = l47 + 1) fRec42[l47] = 0.0;
	for (int l48 = 0; l48 < 2; l48 = l48 + 1) fRec32[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec31[l49] = 0.0;
	for (int l50 = 0; l50 < 2; l50 = l50 + 1) fRec43[l50] = 0.0;
	for (int l51 = 0; l51 < 2; l51 = l51 + 1) fVec13[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fRec30[l52] = 0.0;
	for (int l53 = 0; l53 < 2; l53 = l53 + 1) fVec14[l53] = 0.0;
	for (int l54 = 0; l54 < 2; l54 = l54 + 1) fRec29[l54] = 0.0;
	for (int l55 = 0; l55 < 3; l55 = l55 + 1) fRec28[l55] = 0.0;
	for (int l56 = 0; l56 < 2; l56 = l56 + 1) fVec15[l56] = 0.0;
	for (int l57 = 0; l57 < 2; l57 = l57 + 1) fRec44[l57] = 0.0;
	for (int l58 = 0; l58 < 2; l58 = l58 + 1) fRec27[l58] = 0.0;
	for (int l59 = 0; l59 < 2; l59 = l59 + 1) fRec26[l59] = 0.0;
	for (int l60 = 0; l60 < 2; l60 = l60 + 1) fRec45[l60] = 0.0;
	for (int l61 = 0; l61 < 6; l61 = l61 + 1) fRec25[l61] = 0.0;
	for (int l62 = 0; l62 < 6; l62 = l62 + 1) fRec46[l62] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = std::tan(97.38937226128358 / fConst0);
	double fConst2 = 1.0 / fConst1;
	double fConst3 = fConst2 + 1.0;
	fConst4 = (1.0 - fConst2) / fConst3;
	double fConst5 = 1.0 / std::tan(270.1769682087222 / fConst0);
	fConst6 = 1.0 - fConst5;
	fConst7 = 1.0 / (fConst5 + 1.0);
	fConst8 = 1.0 / (fConst1 * fConst3);
	fConst9 = 0.0 - fConst8;
	double fConst10 = 3.141592653589793 / fConst0;
	fConst11 = 1.0 - fConst10;
	fConst12 = 1.0 / (fConst10 + 1.0);
	double fConst13 = 1.0 / std::tan(20517.741620594938 / fConst0);
	fConst14 = 1.0 - fConst13;
	fConst15 = 1.0 / (fConst13 + 1.0);
	double fConst16 = 1.0 / std::tan(414.6902302738527 / fConst0);
	fConst17 = 1.0 - fConst16;
	fConst18 = 1.0 / (fConst16 + 1.0);
	double fConst19 = 1.0 / std::tan(609.4689747964198 / fConst0);
	fConst20 = 1.0 - fConst19;
	fConst21 = 1.0 / (fConst19 + 1.0);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fCheckbox0 (*fCheckbox0_)
#define fVslider0 (*fVslider0_)
#define fCheckbox1 (*fCheckbox1_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fHslider0 (*fHslider0_)
#define fVslider3 (*fVslider3_)
#define fHslider1 (*fHslider1_)
	int iSlow0 = int(double(fCheckbox0));
	double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
	int iSlow2 = int(double(fCheckbox1));
	double fSlow3 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider1));
	double fSlow4 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider2));
	double fSlow5 = double(fHslider0);
	double fSlow6 = double(fVslider3);
	double fSlow7 = 1.0 - std::max<double>(0.0, -1.0 * fSlow6);
	double fSlow8 = double(fHslider1);
	double fSlow9 = 1.0 - std::max<double>(0.0, fSlow6);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec5[0] = fSlow1 + 0.999 * fRec5[1];
		fRec11[0] = fSlow3 + 0.999 * fRec11[1];
		fRec17[0] = fSlow4 + 0.999 * fRec17[1];
		double fTemp0 = double(input0[i0]);
		double fTemp1 = fTemp0 * fRec17[0];
		fVec0[0] = fTemp1;
		fRec16[0] = 0.9302847925323914 * (fTemp1 + fVec0[1]) - 0.8605695850647829 * fRec16[1];
		fRec15[0] = fRec16[0] - (1.8405051250752198 * fRec15[1] + 0.8612942439318627 * fRec15[2]);
		double fTemp2 = 1.8508996845035413 * fRec15[1];
		double fTemp3 = 0.9254498422517706 * (fRec15[0] + fRec15[2]);
		double fTemp4 = (fTemp2 + fTemp3) / (Ranode(TUBE_TABLE_6V6_68k, fRec14[1]) + 1e+05);
		fVec1[0] = fTemp4;
		fRec18[0] = fConst7 * (2.7e+03 * (fTemp4 + fVec1[1]) - fConst6 * fRec18[1]);
		fRec14[0] = Ftube(TUBE_TABLE_6V6_68k, fTemp3 + fRec18[0] + fTemp2 + -2.29615) + -164.9574074074074;
		fRec13[0] = 0.025 * (fConst8 * fRec14[0] + fConst9 * fRec14[1]) - fConst4 * fRec13[1];
		fRec19[0] = fConst12 * (fConst11 * fRec19[1] + 0.025 * (fRec14[0] - fRec14[1]));
		double fTemp5 = ((iSlow2) ? fRec19[0] : fRec13[0]);
		fVec2[0] = fTemp5;
		fRec12[0] = 0.0 - fConst15 * (fConst14 * fRec12[1] - (fTemp5 + fVec2[1]));
		double fTemp6 = fRec12[0] * fRec11[0];
		fVec3[0] = fTemp6;
		fRec10[0] = 0.9302847925323914 * (fTemp6 + fVec3[1]) - 0.8605695850647829 * fRec10[1];
		fRec9[0] = fRec10[0] - (1.8405051250752198 * fRec9[1] + 0.8612942439318627 * fRec9[2]);
		double fTemp7 = 1.8508996845035413 * fRec9[1];
		double fTemp8 = 0.9254498422517706 * (fRec9[0] + fRec9[2]);
		double fTemp9 = (fTemp7 + fTemp8) / (Ranode(TUBE_TABLE_6V6_250k, fRec8[1]) + 1e+05);
		fVec4[0] = fTemp9;
		fRec20[0] = fConst18 * (1.5e+03 * (fTemp9 + fVec4[1]) - fConst17 * fRec20[1]);
		fRec8[0] = Ftube(TUBE_TABLE_6V6_250k, fTemp8 + fRec20[0] + fTemp7 + -1.675587) + -138.2942;
		fRec7[0] = 0.025 * (fConst8 * fRec8[0] + fConst9 * fRec8[1]) - fConst4 * fRec7[1];
		fRec21[0] = fConst12 * (fConst11 * fRec21[1] + 0.025 * (fRec8[0] - fRec8[1]));
		double fTemp10 = ((iSlow2) ? fRec21[0] : fRec7[0]);
		fVec5[0] = fTemp10;
		fRec6[0] = 0.0 - fConst15 * (fConst14 * fRec6[1] - (fTemp10 + fVec5[1]));
		double fTemp11 = fRec6[0] * fRec5[0];
		fVec6[0] = fTemp11;
		fRec4[0] = 0.9302847925323914 * (fTemp11 + fVec6[1]) - 0.8605695850647829 * fRec4[1];
		fRec3[0] = fRec4[0] - (1.8405051250752198 * fRec3[1] + 0.8612942439318627 * fRec3[2]);
		double fTemp12 = 1.8508996845035413 * fRec3[1];
		double fTemp13 = 0.9254498422517706 * (fRec3[0] + fRec3[2]);
		double fTemp14 = (fTemp12 + fTemp13) / (Ranode(TUBE_TABLE_6V6_250k, fRec2[1]) + 1e+05);
		fVec7[0] = fTemp14;
		fRec22[0] = fConst21 * (8.2e+02 * (fTemp14 + fVec7[1]) - fConst20 * fRec22[1]);
		fRec2[0] = Ftube(TUBE_TABLE_6V6_250k, fTemp13 + fRec22[0] + fTemp12 + -1.130462) + -112.13878048780487;
		fRec1[0] = 0.025 * (fConst8 * fRec2[0] + fConst9 * fRec2[1]) - fConst4 * fRec1[1];
		fRec23[0] = fConst12 * (fConst11 * fRec23[1] + 0.025 * (fRec2[0] - fRec2[1]));
		fRec0[0] = -1.0 * (fSlow5 * fRec0[5] - ((iSlow0) ? fRec23[0] : fRec1[0]));
		fRec24[0] = -1.0 * (fSlow8 * fRec24[5] - fTemp0);
		output0[i0] = FAUSTFLOAT(fSlow9 * fRec24[0] + fSlow7 * fRec0[0]);
		double fTemp15 = double(input1[i0]);
		double fTemp16 = fTemp15 * fRec17[0];
		fVec8[0] = fTemp16;
		fRec39[0] = 0.9302847925323914 * (fTemp16 + fVec8[1]) - 0.8605695850647829 * fRec39[1];
		fRec38[0] = fRec39[0] - (1.8405051250752198 * fRec38[1] + 0.8612942439318627 * fRec38[2]);
		double fTemp17 = 1.8508996845035413 * fRec38[1];
		double fTemp18 = 0.9254498422517706 * (fRec38[0] + fRec38[2]);
		double fTemp19 = (fTemp17 + fTemp18) / (Ranode(TUBE_TABLE_6V6_68k, fRec37[1]) + 1e+05);
		fVec9[0] = fTemp19;
		fRec40[0] = fConst7 * (2.7e+03 * (fTemp19 + fVec9[1]) - fConst6 * fRec40[1]);
		fRec37[0] = Ftube(TUBE_TABLE_6V6_68k, fTemp18 + fRec40[0] + fTemp17 + -2.29615) + -164.9574074074074;
		fRec36[0] = 0.025 * (fConst8 * fRec37[0] + fConst9 * fRec37[1]) - fConst4 * fRec36[1];
		fRec41[0] = fConst12 * (fConst11 * fRec41[1] + 0.025 * (fRec37[0] - fRec37[1]));
		double fTemp20 = ((iSlow2) ? fRec41[0] : fRec36[0]);
		fVec10[0] = fTemp20;
		fRec35[0] = 0.0 - fConst15 * (fConst14 * fRec35[1] - (fTemp20 + fVec10[1]));
		double fTemp21 = fRec11[0] * fRec35[0];
		fVec11[0] = fTemp21;
		fRec34[0] = 0.9302847925323914 * (fTemp21 + fVec11[1]) - 0.8605695850647829 * fRec34[1];
		fRec33[0] = fRec34[0] - (1.8405051250752198 * fRec33[1] + 0.8612942439318627 * fRec33[2]);
		double fTemp22 = 1.8508996845035413 * fRec33[1];
		double fTemp23 = 0.9254498422517706 * (fRec33[0] + fRec33[2]);
		double fTemp24 = (fTemp22 + fTemp23) / (Ranode(TUBE_TABLE_6V6_250k, fRec32[1]) + 1e+05);
		fVec12[0] = fTemp24;
		fRec42[0] = fConst18 * (1.5e+03 * (fTemp24 + fVec12[1]) - fConst17 * fRec42[1]);
		fRec32[0] = Ftube(TUBE_TABLE_6V6_250k, fTemp23 + fRec42[0] + fTemp22 + -1.675587) + -138.2942;
		fRec31[0] = 0.025 * (fConst8 * fRec32[0] + fConst9 * fRec32[1]) - fConst4 * fRec31[1];
		fRec43[0] = fConst12 * (fConst11 * fRec43[1] + 0.025 * (fRec32[0] - fRec32[1]));
		double fTemp25 = ((iSlow2) ? fRec43[0] : fRec31[0]);
		fVec13[0] = fTemp25;
		fRec30[0] = 0.0 - fConst15 * (fConst14 * fRec30[1] - (fTemp25 + fVec13[1]));
		double fTemp26 = fRec5[0] * fRec30[0];
		fVec14[0] = fTemp26;
		fRec29[0] = 0.9302847925323914 * (fTemp26 + fVec14[1]) - 0.8605695850647829 * fRec29[1];
		fRec28[0] = fRec29[0] - (1.8405051250752198 * fRec28[1] + 0.8612942439318627 * fRec28[2]);
		double fTemp27 = 1.8508996845035413 * fRec28[1];
		double fTemp28 = 0.9254498422517706 * (fRec28[0] + fRec28[2]);
		double fTemp29 = (fTemp27 + fTemp28) / (Ranode(TUBE_TABLE_6V6_250k, fRec27[1]) + 1e+05);
		fVec15[0] = fTemp29;
		fRec44[0] = fConst21 * (8.2e+02 * (fTemp29 + fVec15[1]) - fConst20 * fRec44[1]);
		fRec27[0] = Ftube(TUBE_TABLE_6V6_250k, fTemp28 + fRec44[0] + fTemp27 + -1.130462) + -112.13878048780487;
		fRec26[0] = 0.025 * (fConst8 * fRec27[0] + fConst9 * fRec27[1]) - fConst4 * fRec26[1];
		fRec45[0] = fConst12 * (fConst11 * fRec45[1] + 0.025 * (fRec27[0] - fRec27[1]));
		fRec25[0] = -1.0 * (fSlow5 * fRec25[5] - ((iSlow0) ? fRec45[0] : fRec26[0]));
		fRec46[0] = -1.0 * (fSlow8 * fRec46[5] - fTemp15);
		output1[i0] = FAUSTFLOAT(fSlow9 * fRec46[0] + fSlow7 * fRec25[0]);
		fRec5[1] = fRec5[0];
		fRec11[1] = fRec11[0];
		fRec17[1] = fRec17[0];
		fVec0[1] = fVec0[0];
		fRec16[1] = fRec16[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		fVec1[1] = fVec1[0];
		fRec18[1] = fRec18[0];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec19[1] = fRec19[0];
		fVec2[1] = fVec2[0];
		fRec12[1] = fRec12[0];
		fVec3[1] = fVec3[0];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fVec4[1] = fVec4[0];
		fRec20[1] = fRec20[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec21[1] = fRec21[0];
		fVec5[1] = fVec5[0];
		fRec6[1] = fRec6[0];
		fVec6[1] = fVec6[0];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fVec7[1] = fVec7[0];
		fRec22[1] = fRec22[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec23[1] = fRec23[0];
		for (int j0 = 5; j0 > 0; j0 = j0 - 1) {
			fRec0[j0] = fRec0[j0 - 1];
		}
		for (int j1 = 5; j1 > 0; j1 = j1 - 1) {
			fRec24[j1] = fRec24[j1 - 1];
		}
		fVec8[1] = fVec8[0];
		fRec39[1] = fRec39[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		fVec9[1] = fVec9[0];
		fRec40[1] = fRec40[0];
		fRec37[1] = fRec37[0];
		fRec36[1] = fRec36[0];
		fRec41[1] = fRec41[0];
		fVec10[1] = fVec10[0];
		fRec35[1] = fRec35[0];
		fVec11[1] = fVec11[0];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fVec12[1] = fVec12[0];
		fRec42[1] = fRec42[0];
		fRec32[1] = fRec32[0];
		fRec31[1] = fRec31[0];
		fRec43[1] = fRec43[0];
		fVec13[1] = fVec13[0];
		fRec30[1] = fRec30[0];
		fVec14[1] = fVec14[0];
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fVec15[1] = fVec15[0];
		fRec44[1] = fRec44[0];
		fRec27[1] = fRec27[0];
		fRec26[1] = fRec26[0];
		fRec45[1] = fRec45[0];
		for (int j2 = 5; j2 > 0; j2 = j2 - 1) {
			fRec25[j2] = fRec25[j2 - 1];
		}
		for (int j3 = 5; j3 > 0; j3 = j3 - 1) {
			fRec46[j3] = fRec46[j3 - 1];
		}
	}
#undef fCheckbox0
#undef fVslider0
#undef fCheckbox1
#undef fVslider1
#undef fVslider2
#undef fHslider0
#undef fVslider3
#undef fHslider1
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case HIGHGAIN: 
		fCheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case FEEDBAC: 
		fHslider1_ = (float*)data; // , 0.0, -1.0, 1.0, 0.01 
		break;
	case FEEDBACK: 
		fHslider0_ = (float*)data; // , 0.0, -1.0, 1.0, 0.01 
		break;
	case LEVEL: 
		fVslider2_ = (float*)data; // , -2e+01, -4e+01, 4.0, 0.1 
		break;
	case TUBE1: 
		fVslider1_ = (float*)data; // , 6.0, -2e+01, 2e+01, 0.1 
		break;
	case TUBE2: 
		fVslider0_ = (float*)data; // , 6.0, -2e+01, 2e+01, 0.1 
		break;
	case WET_DRY: 
		fVslider3_ = (float*)data; // , 0.0, -1.0, 1.0, 0.1 
		break;
	default:
		break;
	}
}

void Dsp::connect_static(uint32_t port,void* data, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->connect(port, data);
}


PluginLV2 *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginLV2 *p)
{
	delete static_cast<Dsp*>(p);
}

/*
typedef enum
{
   FEEDBAC, 
   FEEDBACK, 
   LEVEL, 
   HIGHGAIN, 
   TUBE1, 
   TUBE2, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace gx_ampmodul
