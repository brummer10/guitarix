// generated from file '../src/LV2/faust/gx_ampmodul.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gx_ampmodul {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	double fRec0[6];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	double fConst0;
	double fConst1;
	double fConst2;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec13[2];
	double fVec0[2];
	double fRec12[2];
	double fRec11[3];
	double fConst3;
	double fConst4;
	double fConst5;
	double fVec1[2];
	double fRec14[2];
	double fRec10[2];
	double fConst6;
	double fRec9[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec15[2];
	double fVec2[2];
	double fRec8[2];
	double fRec7[3];
	double fConst7;
	double fConst8;
	double fConst9;
	double fVec3[2];
	double fRec16[2];
	double fRec6[2];
	double fRec5[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec17[2];
	double fVec4[2];
	double fRec4[2];
	double fRec3[3];
	double fConst10;
	double fConst11;
	double fConst12;
	double fVec5[2];
	double fRec18[2];
	double fRec2[2];
	double fRec1[6];
	double fRec19[6];
	double fVec6[2];
	double fRec31[2];
	double fRec30[3];
	double fVec7[2];
	double fRec32[2];
	double fRec29[2];
	double fRec28[2];
	double fVec8[2];
	double fRec27[2];
	double fRec26[3];
	double fVec9[2];
	double fRec33[2];
	double fRec25[2];
	double fRec24[2];
	double fVec10[2];
	double fRec23[2];
	double fRec22[3];
	double fVec11[2];
	double fRec34[2];
	double fRec21[2];
	double fRec20[6];

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



static const char* parm_groups[] = {
	"amp2.stage2", N_("Postamp Tube2"),
	"amp2.stage1", N_("Postamp Tube1"),
	0
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
	for (int l0 = 0; (l0 < 6); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec13[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fVec0[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec12[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec11[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fVec1[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec14[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec10[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec9[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec15[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fVec2[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec8[l11] = 0.0;
	for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) fRec7[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fVec3[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec16[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec6[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec5[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec17[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fVec4[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec4[l19] = 0.0;
	for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) fRec3[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fVec5[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fRec18[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fRec2[l23] = 0.0;
	for (int l24 = 0; (l24 < 6); l24 = (l24 + 1)) fRec1[l24] = 0.0;
	for (int l25 = 0; (l25 < 6); l25 = (l25 + 1)) fRec19[l25] = 0.0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fVec6[l26] = 0.0;
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) fRec31[l27] = 0.0;
	for (int l28 = 0; (l28 < 3); l28 = (l28 + 1)) fRec30[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fVec7[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec32[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fRec29[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fRec28[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fVec8[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec27[l34] = 0.0;
	for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) fRec26[l35] = 0.0;
	for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) fVec9[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fRec33[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fRec25[l38] = 0.0;
	for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) fRec24[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fVec10[l40] = 0.0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) fRec23[l41] = 0.0;
	for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) fRec22[l42] = 0.0;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fVec11[l43] = 0.0;
	for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) fRec34[l44] = 0.0;
	for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) fRec21[l45] = 0.0;
	for (int l46 = 0; (l46 < 6); l46 = (l46 + 1)) fRec20[l46] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (1.0 / std::tan((20517.741620594938 / fConst0)));
	fConst2 = (1.0 / (fConst1 + 1.0));
	fConst3 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst4 = (1.0 / (fConst3 + 1.0));
	fConst5 = (1.0 - fConst3);
	fConst6 = (1.0 - fConst1);
	fConst7 = (1.0 / std::tan((414.69023027385271 / fConst0)));
	fConst8 = (1.0 / (fConst7 + 1.0));
	fConst9 = (1.0 - fConst7);
	fConst10 = (1.0 / std::tan((609.46897479641984 / fConst0)));
	fConst11 = (1.0 / (fConst10 + 1.0));
	fConst12 = (1.0 - fConst10);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fVslider0 (*fVslider0_)
#define fHslider0 (*fHslider0_)
#define fHslider1 (*fHslider1_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	double fSlow0 = double(fVslider0);
	double fSlow1 = (1.0 - std::max<double>(0.0, fSlow0));
	double fSlow2 = double(fHslider0);
	double fSlow3 = (1.0 - std::max<double>(0.0, (-1.0 * fSlow0)));
	double fSlow4 = double(fHslider1);
	double fSlow5 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider1))));
	double fSlow6 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider2))));
	double fSlow7 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider3))));
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = double(input0[i]);
		fRec0[0] = (-1.0 * ((fSlow2 * fRec0[5]) - fTemp0));
		fRec13[0] = (fSlow5 + (0.999 * fRec13[1]));
		double fTemp1 = ((fTemp0 * fRec13[0]) + 1.0000000000000001e-15);
		fVec0[0] = fTemp1;
		fRec12[0] = ((0.93028479253239138 * (fTemp1 + fVec0[1])) - (0.86056958506478287 * fRec12[1]));
		fRec11[0] = (fRec12[0] - ((1.8405051250752198 * fRec11[1]) + (0.86129424393186271 * fRec11[2])));
		double fTemp2 = ((0.027 * fRec10[1]) + 1.0000000000000001e-15);
		fVec1[0] = fTemp2;
		fRec14[0] = (0.0 - (fConst4 * ((fConst5 * fRec14[1]) - (fTemp2 + fVec1[1]))));
		fRec10[0] = (double(Ftube(int(TUBE_TABLE_6V6_68k), double((((0.92544984225177063 * (fRec11[0] + fRec11[2])) + (fRec14[0] + (1.8508996845035413 * fRec11[1]))) + -2.2961499999999999)))) + -164.9574074074074);
		fRec9[0] = (fConst2 * ((0.025000000000000001 * (fRec10[0] + fRec10[1])) - (fConst6 * fRec9[1])));
		fRec15[0] = (fSlow6 + (0.999 * fRec15[1]));
		double fTemp3 = ((fRec9[0] * fRec15[0]) + 1.0000000000000001e-15);
		fVec2[0] = fTemp3;
		fRec8[0] = ((0.93028479253239138 * (fTemp3 + fVec2[1])) - (0.86056958506478287 * fRec8[1]));
		fRec7[0] = (fRec8[0] - ((1.8405051250752198 * fRec7[1]) + (0.86129424393186271 * fRec7[2])));
		double fTemp4 = ((0.014999999999999999 * fRec6[1]) + 1.0000000000000001e-15);
		fVec3[0] = fTemp4;
		fRec16[0] = (0.0 - (fConst8 * ((fConst9 * fRec16[1]) - (fTemp4 + fVec3[1]))));
		fRec6[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double((((0.92544984225177063 * (fRec7[0] + fRec7[2])) + (fRec16[0] + (1.8508996845035413 * fRec7[1]))) + -1.6755869999999999)))) + -138.29419999999999);
		fRec5[0] = (fConst2 * ((0.025000000000000001 * (fRec6[0] + fRec6[1])) - (fConst6 * fRec5[1])));
		fRec17[0] = (fSlow7 + (0.999 * fRec17[1]));
		double fTemp5 = ((fRec5[0] * fRec17[0]) + 1.0000000000000001e-15);
		fVec4[0] = fTemp5;
		fRec4[0] = ((0.93028479253239138 * (fTemp5 + fVec4[1])) - (0.86056958506478287 * fRec4[1]));
		fRec3[0] = (fRec4[0] - ((1.8405051250752198 * fRec3[1]) + (0.86129424393186271 * fRec3[2])));
		double fTemp6 = ((0.0082000000000000007 * fRec2[1]) + 1.0000000000000001e-15);
		fVec5[0] = fTemp6;
		fRec18[0] = (0.0 - (fConst11 * ((fConst12 * fRec18[1]) - (fTemp6 + fVec5[1]))));
		fRec2[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double((((0.92544984225177063 * (fRec3[0] + fRec3[2])) + (fRec18[0] + (1.8508996845035413 * fRec3[1]))) + -1.1304620000000001)))) + -112.13878048780487);
		fRec1[0] = (-1.0 * ((fSlow4 * fRec1[5]) - (0.025000000000000001 * fRec2[0])));
		output0[i] = FAUSTFLOAT(((fSlow1 * fRec0[0]) + (fSlow3 * fRec1[0])));
		double fTemp7 = double(input1[i]);
		fRec19[0] = (-1.0 * ((fSlow2 * fRec19[5]) - fTemp7));
		double fTemp8 = ((fTemp7 * fRec13[0]) + 1.0000000000000001e-15);
		fVec6[0] = fTemp8;
		fRec31[0] = ((0.93028479253239138 * (fTemp8 + fVec6[1])) - (0.86056958506478287 * fRec31[1]));
		fRec30[0] = (fRec31[0] - ((1.8405051250752198 * fRec30[1]) + (0.86129424393186271 * fRec30[2])));
		double fTemp9 = ((0.027 * fRec29[1]) + 1.0000000000000001e-15);
		fVec7[0] = fTemp9;
		fRec32[0] = (0.0 - (fConst4 * ((fConst5 * fRec32[1]) - (fTemp9 + fVec7[1]))));
		fRec29[0] = (double(Ftube(int(TUBE_TABLE_6V6_68k), double((((0.92544984225177063 * (fRec30[0] + fRec30[2])) + (fRec32[0] + (1.8508996845035413 * fRec30[1]))) + -2.2961499999999999)))) + -164.9574074074074);
		fRec28[0] = (fConst2 * ((0.025000000000000001 * (fRec29[0] + fRec29[1])) - (fConst6 * fRec28[1])));
		double fTemp10 = ((fRec15[0] * fRec28[0]) + 1.0000000000000001e-15);
		fVec8[0] = fTemp10;
		fRec27[0] = ((0.93028479253239138 * (fTemp10 + fVec8[1])) - (0.86056958506478287 * fRec27[1]));
		fRec26[0] = (fRec27[0] - ((1.8405051250752198 * fRec26[1]) + (0.86129424393186271 * fRec26[2])));
		double fTemp11 = ((0.014999999999999999 * fRec25[1]) + 1.0000000000000001e-15);
		fVec9[0] = fTemp11;
		fRec33[0] = (0.0 - (fConst8 * ((fConst9 * fRec33[1]) - (fTemp11 + fVec9[1]))));
		fRec25[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double((((0.92544984225177063 * (fRec26[0] + fRec26[2])) + (fRec33[0] + (1.8508996845035413 * fRec26[1]))) + -1.6755869999999999)))) + -138.29419999999999);
		fRec24[0] = (fConst2 * ((0.025000000000000001 * (fRec25[0] + fRec25[1])) - (fConst6 * fRec24[1])));
		double fTemp12 = ((fRec17[0] * fRec24[0]) + 1.0000000000000001e-15);
		fVec10[0] = fTemp12;
		fRec23[0] = ((0.93028479253239138 * (fTemp12 + fVec10[1])) - (0.86056958506478287 * fRec23[1]));
		fRec22[0] = (fRec23[0] - ((1.8405051250752198 * fRec22[1]) + (0.86129424393186271 * fRec22[2])));
		double fTemp13 = ((0.0082000000000000007 * fRec21[1]) + 1.0000000000000001e-15);
		fVec11[0] = fTemp13;
		fRec34[0] = (0.0 - (fConst11 * ((fConst12 * fRec34[1]) - (fTemp13 + fVec11[1]))));
		fRec21[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double((((0.92544984225177063 * (fRec22[0] + fRec22[2])) + (fRec34[0] + (1.8508996845035413 * fRec22[1]))) + -1.1304620000000001)))) + -112.13878048780487);
		fRec20[0] = (-1.0 * ((fSlow4 * fRec20[5]) - (0.025000000000000001 * fRec21[0])));
		output1[i] = FAUSTFLOAT(((fSlow1 * fRec19[0]) + (fSlow3 * fRec20[0])));
		for (int j0 = 5; (j0 > 0); j0 = (j0 - 1)) {
			fRec0[j0] = fRec0[(j0 - 1)];
		}
		fRec13[1] = fRec13[0];
		fVec0[1] = fVec0[0];
		fRec12[1] = fRec12[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fVec1[1] = fVec1[0];
		fRec14[1] = fRec14[0];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec15[1] = fRec15[0];
		fVec2[1] = fVec2[0];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fVec3[1] = fVec3[0];
		fRec16[1] = fRec16[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec17[1] = fRec17[0];
		fVec4[1] = fVec4[0];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fVec5[1] = fVec5[0];
		fRec18[1] = fRec18[0];
		fRec2[1] = fRec2[0];
		for (int j1 = 5; (j1 > 0); j1 = (j1 - 1)) {
			fRec1[j1] = fRec1[(j1 - 1)];
		}
		for (int j2 = 5; (j2 > 0); j2 = (j2 - 1)) {
			fRec19[j2] = fRec19[(j2 - 1)];
		}
		fVec6[1] = fVec6[0];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fVec7[1] = fVec7[0];
		fRec32[1] = fRec32[0];
		fRec29[1] = fRec29[0];
		fRec28[1] = fRec28[0];
		fVec8[1] = fVec8[0];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fVec9[1] = fVec9[0];
		fRec33[1] = fRec33[0];
		fRec25[1] = fRec25[0];
		fRec24[1] = fRec24[0];
		fVec10[1] = fVec10[0];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fVec11[1] = fVec11[0];
		fRec34[1] = fRec34[0];
		fRec21[1] = fRec21[0];
		for (int j3 = 5; (j3 > 0); j3 = (j3 - 1)) {
			fRec20[j3] = fRec20[(j3 - 1)];
		}
	}
#undef fVslider0
#undef fHslider0
#undef fHslider1
#undef fVslider1
#undef fVslider2
#undef fVslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case FEEDBAC: 
		fHslider0_ = (float*)data; // , 0.0, -1.0, 1.0, 0.01 
		break;
	case FEEDBACK: 
		fHslider1_ = (float*)data; // , 0.0, -1.0, 1.0, 0.01 
		break;
	case LEVEL: 
		fVslider1_ = (float*)data; // , -20.0, -40.0, 4.0, 0.10000000000000001 
		break;
	case TUBE1: 
		fVslider2_ = (float*)data; // , 6.0, -20.0, 20.0, 0.10000000000000001 
		break;
	case TUBE2: 
		fVslider3_ = (float*)data; // , 6.0, -20.0, 20.0, 0.10000000000000001 
		break;
	case WET_DRY: 
		fVslider0_ = (float*)data; // , 0.0, -1.0, 1.0, 0.10000000000000001 
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
   TUBE1, 
   TUBE2, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace gx_ampmodul
