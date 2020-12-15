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
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec16[2];
	double fVec0[2];
	double fRec15[2];
	double fRec14[3];
	double fConst7;
	double fConst8;
	double fVec1[2];
	double fConst9;
	double fRec17[2];
	double fRec13[2];
	double fRec12[2];
	double fRec11[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec18[2];
	double fVec2[2];
	double fRec10[2];
	double fRec9[3];
	double fConst10;
	double fConst11;
	double fVec3[2];
	double fConst12;
	double fRec19[2];
	double fRec8[2];
	double fRec7[2];
	double fRec6[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec20[2];
	double fVec4[2];
	double fRec5[2];
	double fRec4[3];
	double fConst13;
	double fConst14;
	double fVec5[2];
	double fConst15;
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

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (3.1415926535897931 / fConst0);
	fConst2 = (1.0 / (fConst1 + 1.0));
	fConst3 = (1.0 - fConst1);
	fConst4 = (1.0 / std::tan((20517.741620594938 / fConst0)));
	fConst5 = (1.0 / (fConst4 + 1.0));
	fConst6 = (1.0 - fConst4);
	fConst7 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst8 = (1.0 / (fConst7 + 1.0));
	fConst9 = (1.0 - fConst7);
	fConst10 = (1.0 / std::tan((414.69023027385271 / fConst0)));
	fConst11 = (1.0 / (fConst10 + 1.0));
	fConst12 = (1.0 - fConst10);
	fConst13 = (1.0 / std::tan((609.46897479641984 / fConst0)));
	fConst14 = (1.0 / (fConst13 + 1.0));
	fConst15 = (1.0 - fConst13);
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
		fRec16[0] = (fSlow5 + (0.999 * fRec16[1]));
		double fTemp1 = (fTemp0 * fRec16[0]);
		fVec0[0] = fTemp1;
		fRec15[0] = ((0.93028479253239138 * (fTemp1 + fVec0[1])) - (0.86056958506478287 * fRec15[1]));
		fRec14[0] = (fRec15[0] - ((1.8405051250752198 * fRec14[1]) + (0.86129424393186271 * fRec14[2])));
		double fTemp2 = (0.92544984225177063 * (fRec14[0] + fRec14[2]));
		double fTemp3 = (1.8508996845035413 * fRec14[1]);
		double fTemp4 = ((fTemp3 + fTemp2) / (double(Ranode(int(TUBE_TABLE_6V6_68k), double(fRec13[1]))) + 100000.0));
		fVec1[0] = fTemp4;
		fRec17[0] = (fConst8 * ((2700.0 * (fTemp4 + fVec1[1])) - (fConst9 * fRec17[1])));
		double fTemp5 = double(Ftube(int(TUBE_TABLE_6V6_68k), double(((fTemp2 + (fRec17[0] + fTemp3)) + -2.2961499999999999))));
		fRec13[0] = ((fTemp5 + (0.00085042592592592592 * (double(Ranode(int(TUBE_TABLE_6V6_68k), double(fTemp5))) + 100000.0))) + -250.0);
		fRec12[0] = (fConst2 * ((fConst3 * fRec12[1]) + (0.025000000000000001 * (fRec13[0] - fRec13[1]))));
		fRec11[0] = (0.0 - (fConst5 * ((fConst6 * fRec11[1]) - (fRec12[0] + fRec12[1]))));
		fRec18[0] = (fSlow6 + (0.999 * fRec18[1]));
		double fTemp6 = (fRec11[0] * fRec18[0]);
		fVec2[0] = fTemp6;
		fRec10[0] = ((0.93028479253239138 * (fTemp6 + fVec2[1])) - (0.86056958506478287 * fRec10[1]));
		fRec9[0] = (fRec10[0] - ((1.8405051250752198 * fRec9[1]) + (0.86129424393186271 * fRec9[2])));
		double fTemp7 = (0.92544984225177063 * (fRec9[0] + fRec9[2]));
		double fTemp8 = (1.8508996845035413 * fRec9[1]);
		double fTemp9 = ((fTemp8 + fTemp7) / (double(Ranode(int(TUBE_TABLE_6V6_250k), double(fRec8[1]))) + 100000.0));
		fVec3[0] = fTemp9;
		fRec19[0] = (fConst11 * ((1500.0 * (fTemp9 + fVec3[1])) - (fConst12 * fRec19[1])));
		double fTemp10 = double(Ftube(int(TUBE_TABLE_6V6_250k), double(((fTemp7 + (fRec19[0] + fTemp8)) + -1.6755869999999999))));
		fRec8[0] = ((fTemp10 + (0.001117058 * (double(Ranode(int(TUBE_TABLE_6V6_250k), double(fTemp10))) + 100000.0))) + -250.0);
		fRec7[0] = (fConst2 * ((fConst3 * fRec7[1]) + (0.025000000000000001 * (fRec8[0] - fRec8[1]))));
		fRec6[0] = (0.0 - (fConst5 * ((fConst6 * fRec6[1]) - (fRec7[0] + fRec7[1]))));
		fRec20[0] = (fSlow7 + (0.999 * fRec20[1]));
		double fTemp11 = (fRec6[0] * fRec20[0]);
		fVec4[0] = fTemp11;
		fRec5[0] = ((0.93028479253239138 * (fTemp11 + fVec4[1])) - (0.86056958506478287 * fRec5[1]));
		fRec4[0] = (fRec5[0] - ((1.8405051250752198 * fRec4[1]) + (0.86129424393186271 * fRec4[2])));
		double fTemp12 = (0.92544984225177063 * (fRec4[0] + fRec4[2]));
		double fTemp13 = (1.8508996845035413 * fRec4[1]);
		double fTemp14 = ((fTemp13 + fTemp12) / (double(Ranode(int(TUBE_TABLE_6V6_250k), double(fRec3[1]))) + 100000.0));
		fVec5[0] = fTemp14;
		fRec21[0] = (fConst14 * ((820.0 * (fTemp14 + fVec5[1])) - (fConst15 * fRec21[1])));
		double fTemp15 = double(Ftube(int(TUBE_TABLE_6V6_250k), double(((fTemp12 + (fRec21[0] + fTemp13)) + -1.1304620000000001))));
		fRec3[0] = ((fTemp15 + (0.0013786121951219513 * (double(Ranode(int(TUBE_TABLE_6V6_250k), double(fTemp15))) + 100000.0))) + -250.0);
		fRec2[0] = (fConst2 * ((fConst3 * fRec2[1]) + (0.025000000000000001 * (fRec3[0] - fRec3[1]))));
		fRec1[0] = (-1.0 * ((fSlow4 * fRec1[5]) - fRec2[0]));
		output0[i] = FAUSTFLOAT(((fSlow1 * fRec0[0]) + (fSlow3 * fRec1[0])));
		double fTemp16 = double(input1[i]);
		fRec22[0] = (-1.0 * ((fSlow2 * fRec22[5]) - fTemp16));
		double fTemp17 = (fTemp16 * fRec16[0]);
		fVec6[0] = fTemp17;
		fRec37[0] = ((0.93028479253239138 * (fTemp17 + fVec6[1])) - (0.86056958506478287 * fRec37[1]));
		fRec36[0] = (fRec37[0] - ((1.8405051250752198 * fRec36[1]) + (0.86129424393186271 * fRec36[2])));
		double fTemp18 = (0.92544984225177063 * (fRec36[0] + fRec36[2]));
		double fTemp19 = (1.8508996845035413 * fRec36[1]);
		double fTemp20 = ((fTemp19 + fTemp18) / (double(Ranode(int(TUBE_TABLE_6V6_68k), double(fRec35[1]))) + 100000.0));
		fVec7[0] = fTemp20;
		fRec38[0] = (fConst8 * ((2700.0 * (fTemp20 + fVec7[1])) - (fConst9 * fRec38[1])));
		double fTemp21 = double(Ftube(int(TUBE_TABLE_6V6_68k), double(((fTemp18 + (fRec38[0] + fTemp19)) + -2.2961499999999999))));
		fRec35[0] = ((fTemp21 + (0.00085042592592592592 * (double(Ranode(int(TUBE_TABLE_6V6_68k), double(fTemp21))) + 100000.0))) + -250.0);
		fRec34[0] = (fConst2 * ((fConst3 * fRec34[1]) + (0.025000000000000001 * (fRec35[0] - fRec35[1]))));
		fRec33[0] = (0.0 - (fConst5 * ((fConst6 * fRec33[1]) - (fRec34[0] + fRec34[1]))));
		double fTemp22 = (fRec18[0] * fRec33[0]);
		fVec8[0] = fTemp22;
		fRec32[0] = ((0.93028479253239138 * (fTemp22 + fVec8[1])) - (0.86056958506478287 * fRec32[1]));
		fRec31[0] = (fRec32[0] - ((1.8405051250752198 * fRec31[1]) + (0.86129424393186271 * fRec31[2])));
		double fTemp23 = (0.92544984225177063 * (fRec31[0] + fRec31[2]));
		double fTemp24 = (1.8508996845035413 * fRec31[1]);
		double fTemp25 = ((fTemp24 + fTemp23) / (double(Ranode(int(TUBE_TABLE_6V6_250k), double(fRec30[1]))) + 100000.0));
		fVec9[0] = fTemp25;
		fRec39[0] = (fConst11 * ((1500.0 * (fTemp25 + fVec9[1])) - (fConst12 * fRec39[1])));
		double fTemp26 = double(Ftube(int(TUBE_TABLE_6V6_250k), double(((fTemp23 + (fRec39[0] + fTemp24)) + -1.6755869999999999))));
		fRec30[0] = ((fTemp26 + (0.001117058 * (double(Ranode(int(TUBE_TABLE_6V6_250k), double(fTemp26))) + 100000.0))) + -250.0);
		fRec29[0] = (fConst2 * ((fConst3 * fRec29[1]) + (0.025000000000000001 * (fRec30[0] - fRec30[1]))));
		fRec28[0] = (0.0 - (fConst5 * ((fConst6 * fRec28[1]) - (fRec29[0] + fRec29[1]))));
		double fTemp27 = (fRec20[0] * fRec28[0]);
		fVec10[0] = fTemp27;
		fRec27[0] = ((0.93028479253239138 * (fTemp27 + fVec10[1])) - (0.86056958506478287 * fRec27[1]));
		fRec26[0] = (fRec27[0] - ((1.8405051250752198 * fRec26[1]) + (0.86129424393186271 * fRec26[2])));
		double fTemp28 = (0.92544984225177063 * (fRec26[0] + fRec26[2]));
		double fTemp29 = (1.8508996845035413 * fRec26[1]);
		double fTemp30 = ((fTemp29 + fTemp28) / (double(Ranode(int(TUBE_TABLE_6V6_250k), double(fRec25[1]))) + 100000.0));
		fVec11[0] = fTemp30;
		fRec40[0] = (fConst14 * ((820.0 * (fTemp30 + fVec11[1])) - (fConst15 * fRec40[1])));
		double fTemp31 = double(Ftube(int(TUBE_TABLE_6V6_250k), double(((fTemp28 + (fRec40[0] + fTemp29)) + -1.1304620000000001))));
		fRec25[0] = ((fTemp31 + (0.0013786121951219513 * (double(Ranode(int(TUBE_TABLE_6V6_250k), double(fTemp31))) + 100000.0))) + -250.0);
		fRec24[0] = (fConst2 * ((fConst3 * fRec24[1]) + (0.025000000000000001 * (fRec25[0] - fRec25[1]))));
		fRec23[0] = (-1.0 * ((fSlow4 * fRec23[5]) - fRec24[0]));
		output1[i] = FAUSTFLOAT(((fSlow1 * fRec22[0]) + (fSlow3 * fRec23[0])));
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
