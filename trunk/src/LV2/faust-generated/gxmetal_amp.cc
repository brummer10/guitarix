// generated from file '../src/LV2/faust/gxmetal_amp.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxmetal_amp {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec1[2];
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fVec0[2];
	double fRec22[2];
	double fRec21[3];
	double fConst18;
	double fConst19;
	double fConst20;
	double fVec1[2];
	double fRec23[2];
	double fRec20[2];
	double fConst21;
	double fConst22;
	double fRec19[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec24[2];
	double fVec2[2];
	double fRec18[2];
	double fVec3[2];
	double fRec17[2];
	double fRec16[3];
	double fConst23;
	double fConst24;
	double fConst25;
	double fVec4[2];
	double fRec25[2];
	double fRec15[2];
	double fRec14[2];
	double fRec13[2];
	double fVec5[2];
	double fRec12[2];
	double fRec11[3];
	double fConst26;
	double fConst27;
	double fConst28;
	double fVec6[2];
	double fRec26[2];
	double fRec10[2];
	double fRec9[2];
	double fConst29;
	double fRec8[4];
	double fConst30;
	double fConst31;
	double fRec27[2];
	double fVec7[2];
	double fRec7[2];
	double fRec6[3];
	double fConst32;
	double fConst33;
	double fConst34;
	double fRec28[2];
	double fRec5[3];
	double fRec4[2];
	double fRec31[2];
	double fRec30[3];
	double fRec29[2];
	double fConst35;
	double fConst36;
	double fRec3[3];
	double fConst37;
	double fConst38;
	double fConst39;
	double fRec2[3];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "metal";
	name = N_("GxMetal_head");
	mono_audio = compute_static;
	stereo_audio = 0;
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec1[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fVec0[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec22[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec21[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fVec1[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec23[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec20[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec19[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec24[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fVec2[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec18[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fVec3[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec17[l13] = 0.0;
	for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) fRec16[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fVec4[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec25[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec15[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec14[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec13[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fVec5[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec12[l21] = 0.0;
	for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) fRec11[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fVec6[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec26[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fRec10[l25] = 0.0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fRec9[l26] = 0.0;
	for (int l27 = 0; (l27 < 4); l27 = (l27 + 1)) fRec8[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec27[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fVec7[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec7[l30] = 0.0;
	for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) fRec6[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fRec28[l32] = 0.0;
	for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) fRec5[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec4[l34] = 0.0;
	for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) fRec31[l35] = 0.0;
	for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) fRec30[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fRec29[l37] = 0.0;
	for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) fRec3[l38] = 0.0;
	for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) fRec2[l39] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = std::tan((37699.111843077517 / fConst0));
	fConst2 = (1.0 / fConst1);
	fConst3 = (1.0 / (((fConst2 + 1.4142135623730949) / fConst1) + 1.0));
	fConst4 = std::tan((125.66370614359172 / fConst0));
	fConst5 = (1.0 / fConst4);
	fConst6 = (1.0 / (((fConst5 + 1.4142135623730949) / fConst4) + 1.0));
	fConst7 = mydsp_faustpower2_f(fConst4);
	fConst8 = (1.0 / fConst7);
	fConst9 = std::tan((97.389372261283583 / fConst0));
	fConst10 = (1.0 / fConst9);
	fConst11 = (fConst10 + 1.0);
	fConst12 = (1.0 / (fConst9 * fConst11));
	fConst13 = (2.0 * fConst0);
	fConst14 = mydsp_faustpower2_f(fConst13);
	fConst15 = (1.0 / std::tan((20517.741620594938 / fConst0)));
	fConst16 = (1.0 / (fConst15 + 1.0));
	fConst17 = (1.0 - fConst15);
	fConst18 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst19 = (1.0 / (fConst18 + 1.0));
	fConst20 = (1.0 - fConst18);
	fConst21 = (0.0 - fConst12);
	fConst22 = ((1.0 - fConst10) / fConst11);
	fConst23 = (1.0 / std::tan((414.69023027385271 / fConst0)));
	fConst24 = (1.0 / (fConst23 + 1.0));
	fConst25 = (1.0 - fConst23);
	fConst26 = (1.0 / std::tan((609.46897479641984 / fConst0)));
	fConst27 = (1.0 / (fConst26 + 1.0));
	fConst28 = (1.0 - fConst26);
	fConst29 = (3.0 * fConst13);
	fConst30 = std::exp((0.0 - (200.0 / fConst0)));
	fConst31 = std::exp((0.0 - (0.10000000000000001 / fConst0)));
	fConst32 = (1.0 / std::tan((804.24771931898704 / fConst0)));
	fConst33 = (1.0 / (fConst32 + 1.0));
	fConst34 = (1.0 - fConst32);
	fConst35 = (((fConst5 + -1.4142135623730949) / fConst4) + 1.0);
	fConst36 = (2.0 * (1.0 - fConst8));
	fConst37 = (0.0 - (2.0 / fConst7));
	fConst38 = (((fConst2 + -1.4142135623730949) / fConst1) + 1.0);
	fConst39 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst1))));
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	double fSlow0 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider0))));
	double fSlow1 = double(fVslider1);
	double fSlow2 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * (0.0 - (0.40000000000000002 * fSlow1)))));
	double fSlow3 = double(fVslider2);
	double fSlow4 = std::exp((3.3999999999999999 * (0.0 - fSlow3)));
	double fSlow5 = (0.022470000000000004 * fSlow4);
	double fSlow6 = (fConst13 * (fSlow5 + 0.0026376999999999998));
	double fSlow7 = ((3.1361660000000006e-05 * fSlow4) + 6.9934810000000012e-07);
	double fSlow8 = ((5.9679378000000017e-09 * fSlow4) + 2.9839689000000005e-11);
	double fSlow9 = (fConst13 * fSlow8);
	double fSlow10 = (1.0 / (-1.0 - (fSlow6 + (fConst14 * (fSlow7 + fSlow9)))));
	double fSlow11 = (fConst13 * ((fSlow5 + (0.00023500000000000002 * fSlow3)) + 0.0003347));
	double fSlow12 = (((4.8598000000000007e-07 * fSlow3) + (8.6136600000000025e-06 * fSlow4)) + 9.9628100000000016e-08);
	double fSlow13 = (((2.6728900000000006e-11 * fSlow3) + (fSlow4 * ((5.3457800000000014e-09 * fSlow3) + 6.2215780000000018e-10))) + 3.1107890000000005e-12);
	double fSlow14 = (fConst13 * fSlow13);
	double fSlow15 = (0.0 - (fSlow11 + (fConst14 * (fSlow12 + fSlow14))));
	double fSlow16 = (fSlow1 + -1.0);
	double fSlow17 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider3))));
	double fSlow18 = (fConst29 * fSlow8);
	double fSlow19 = ((fConst14 * (fSlow7 + fSlow18)) + (-3.0 - fSlow6));
	double fSlow20 = ((fSlow6 + (fConst14 * (fSlow7 - fSlow18))) + -3.0);
	double fSlow21 = (fSlow6 + (-1.0 - (fConst14 * (fSlow7 - fSlow9))));
	double fSlow22 = (fConst29 * fSlow13);
	double fSlow23 = ((fConst14 * (fSlow12 + fSlow22)) - fSlow11);
	double fSlow24 = (fSlow11 + (fConst14 * (fSlow12 - fSlow22)));
	double fSlow25 = (fSlow11 - (fConst14 * (fSlow12 - fSlow14)));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec1[0] = (fSlow2 + (0.999 * fRec1[1]));
		double fTemp0 = double(input0[i]);
		double fTemp1 = std::fabs(fTemp0);
		double fTemp2 = (((fTemp0 * (fSlow1 + fTemp1)) / ((mydsp_faustpower2_f(fTemp0) + (fSlow16 * fTemp1)) + 1.0)) + 1.0000000000000001e-15);
		fVec0[0] = fTemp2;
		fRec22[0] = ((0.93028479253239138 * (fTemp2 + fVec0[1])) - (0.86056958506478287 * fRec22[1]));
		fRec21[0] = (fRec22[0] - ((1.8405051250752198 * fRec21[1]) + (0.86129424393186271 * fRec21[2])));
		double fTemp3 = ((0.027 * fRec20[1]) + 1.0000000000000001e-15);
		fVec1[0] = fTemp3;
		fRec23[0] = (0.0 - (fConst19 * ((fConst20 * fRec23[1]) - (fTemp3 + fVec1[1]))));
		fRec20[0] = (double(Ftube(int(TUBE_TABLE_12AY7_68k), double((((0.92544984225177063 * (fRec21[0] + fRec21[2])) + (fRec23[0] + (1.8508996845035413 * fRec21[1]))) + -2.775058)))) + -147.22007407407409);
		fRec19[0] = ((0.025000000000000001 * ((fConst12 * fRec20[0]) + (fConst21 * fRec20[1]))) - (fConst22 * fRec19[1]));
		fRec24[0] = (fSlow17 + (0.999 * fRec24[1]));
		double fTemp4 = (fRec19[0] * fRec24[0]);
		fVec2[0] = fTemp4;
		fRec18[0] = (0.0 - (fConst16 * ((fConst17 * fRec18[1]) - (fTemp4 + fVec2[1]))));
		double fTemp5 = (fRec18[0] + 1.0000000000000001e-15);
		fVec3[0] = fTemp5;
		fRec17[0] = ((0.93028479253239138 * (fTemp5 + fVec3[1])) - (0.86056958506478287 * fRec17[1]));
		fRec16[0] = (fRec17[0] - ((1.8405051250752198 * fRec16[1]) + (0.86129424393186271 * fRec16[2])));
		double fTemp6 = ((0.014999999999999999 * fRec15[1]) + 1.0000000000000001e-15);
		fVec4[0] = fTemp6;
		fRec25[0] = (0.0 - (fConst24 * ((fConst25 * fRec25[1]) - (fTemp6 + fVec4[1]))));
		fRec15[0] = (double(Ftube(int(TUBE_TABLE_12AY7_250k), double((((0.92544984225177063 * (fRec16[0] + fRec16[2])) + (fRec25[0] + (1.8508996845035413 * fRec16[1]))) + -1.9543079999999999)))) + -119.71279999999999);
		fRec14[0] = ((0.025000000000000001 * ((fConst12 * fRec15[0]) + (fConst21 * fRec15[1]))) - (fConst22 * fRec14[1]));
		fRec13[0] = (0.0 - (fConst16 * ((fConst17 * fRec13[1]) - (fRec14[0] + fRec14[1]))));
		double fTemp7 = (fRec13[0] + 1.0000000000000001e-15);
		fVec5[0] = fTemp7;
		fRec12[0] = ((0.93028479253239138 * (fTemp7 + fVec5[1])) - (0.86056958506478287 * fRec12[1]));
		fRec11[0] = (fRec12[0] - ((1.8405051250752198 * fRec11[1]) + (0.86129424393186271 * fRec11[2])));
		double fTemp8 = ((0.0082000000000000007 * fRec10[1]) + 1.0000000000000001e-15);
		fVec6[0] = fTemp8;
		fRec26[0] = (0.0 - (fConst27 * ((fConst28 * fRec26[1]) - (fTemp8 + fVec6[1]))));
		fRec10[0] = (double(Ftube(int(TUBE_TABLE_12AY7_250k), double((((0.92544984225177063 * (fRec11[0] + fRec11[2])) + (fRec26[0] + (1.8508996845035413 * fRec11[1]))) + -1.2649159999999999)))) + -95.741951219512202);
		fRec9[0] = ((0.025000000000000001 * ((fConst12 * fRec10[0]) + (fConst21 * fRec10[1]))) - (fConst22 * fRec9[1]));
		fRec8[0] = ((fRec9[0] * fRec0[0]) - (fSlow10 * (((fSlow19 * fRec8[1]) + (fSlow20 * fRec8[2])) + (fSlow21 * fRec8[3]))));
		double fTemp9 = ((((fSlow15 * fRec8[0]) + (fSlow23 * fRec8[1])) + (fSlow24 * fRec8[2])) + (fSlow25 * fRec8[3]));
		double fTemp10 = std::max<double>(1.0, std::fabs((fSlow10 * fTemp9)));
		double fTemp11 = ((fConst30 * double((fRec27[1] < fTemp10))) + (fConst31 * double((fRec27[1] >= fTemp10))));
		fRec27[0] = ((fRec27[1] * fTemp11) + (fTemp10 * (1.0 - fTemp11)));
		double fTemp12 = std::max<double>(0.0, ((20.0 * std::log10(fRec27[0])) + 50.0));
		double fTemp13 = (0.5 * std::min<double>(1.0, std::max<double>(0.0, (0.095229025807065992 * fTemp12))));
		double fTemp14 = (fSlow10 * (fTemp9 * std::pow(10.0, (0.050000000000000003 * (((fTemp12 * (0.0 - fTemp13)) / (fTemp13 + 1.0)) + 10.0)))));
		fVec7[0] = fTemp14;
		fRec7[0] = ((0.93028479253239138 * (fTemp14 + fVec7[1])) - (0.86056958506478287 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.86129424393186271 * fRec6[2])));
		double fTemp15 = (0.92544984225177063 * (fRec6[0] + fRec6[2]));
		fRec28[0] = (fConst33 * ((0.065714285714285711 * (fRec5[1] + fRec5[2])) - (fConst34 * fRec28[1])));
		double fTemp16 = (1.8508996845035413 * fRec6[1]);
		fRec5[0] = (double(Ftube(int(TUBE_TABLE_EL34_68k), double(((fTemp15 + (fRec28[0] + fTemp16)) + -15.743945)))) + -255.41822826086957);
		fRec4[0] = ((0.10000000000000001 * ((fConst12 * fRec5[0]) + (fConst21 * fRec5[1]))) - (fConst22 * fRec4[1]));
		fRec31[0] = (fConst33 * ((0.065714285714285711 * (fRec30[1] + fRec30[2])) - (fConst34 * fRec31[1])));
		fRec30[0] = (double(Ftube(int(TUBE_TABLE_EL34_250k), double(((fTemp15 + (fRec31[0] + fTemp16)) + -15.743945)))) + -255.41822826086957);
		fRec29[0] = ((0.10000000000000001 * ((fConst12 * fRec30[0]) + (fConst21 * fRec30[1]))) - (fConst22 * fRec29[1]));
		fRec3[0] = ((fRec4[0] + fRec29[0]) - (fConst6 * ((fConst35 * fRec3[2]) + (fConst36 * fRec3[1]))));
		fRec2[0] = ((fConst6 * (((fConst8 * fRec3[0]) + (fConst37 * fRec3[1])) + (fConst8 * fRec3[2]))) - (fConst3 * ((fConst38 * fRec2[2]) + (fConst39 * fRec2[1]))));
		output0[i] = FAUSTFLOAT((fConst3 * ((fRec0[0] * fRec1[0]) * (fRec2[2] + (fRec2[0] + (2.0 * fRec2[1]))))));
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fVec0[1] = fVec0[0];
		fRec22[1] = fRec22[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		fVec1[1] = fVec1[0];
		fRec23[1] = fRec23[0];
		fRec20[1] = fRec20[0];
		fRec19[1] = fRec19[0];
		fRec24[1] = fRec24[0];
		fVec2[1] = fVec2[0];
		fRec18[1] = fRec18[0];
		fVec3[1] = fVec3[0];
		fRec17[1] = fRec17[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fVec4[1] = fVec4[0];
		fRec25[1] = fRec25[0];
		fRec15[1] = fRec15[0];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fVec5[1] = fVec5[0];
		fRec12[1] = fRec12[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fVec6[1] = fVec6[0];
		fRec26[1] = fRec26[0];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
			fRec8[j0] = fRec8[(j0 - 1)];
		}
		fRec27[1] = fRec27[0];
		fVec7[1] = fVec7[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec28[1] = fRec28[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fRec29[1] = fRec29[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
#undef fVslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case DRIVE: 
		fVslider1_ = (float*)data; // , 1.0, 1.0, 20.0, 0.10000000000000001 
		break;
	case PREGAIN: 
		fVslider3_ = (float*)data; // , -6.0, -20.0, 20.0, 0.10000000000000001 
		break;
	case TONE: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case GAIN1: 
		fVslider0_ = (float*)data; // , -6.0, -20.0, 20.0, 0.10000000000000001 
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
   DRIVE, 
   PREGAIN, 
   TONE, 
   GAIN1, 
} PortIndex;
*/

} // end namespace gxmetal_amp
