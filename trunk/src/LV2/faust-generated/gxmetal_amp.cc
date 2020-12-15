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
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fVec0[2];
	double fRec21[2];
	double fRec20[3];
	double fConst17;
	double fConst18;
	double fVec1[2];
	double fConst19;
	double fRec22[2];
	double fRec19[2];
	double fRec18[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec23[2];
	double fVec2[2];
	double fRec17[2];
	double fRec16[2];
	double fRec15[3];
	double fConst20;
	double fConst21;
	double fVec3[2];
	double fConst22;
	double fRec24[2];
	double fRec14[2];
	double fRec13[2];
	double fRec12[2];
	double fRec11[2];
	double fRec10[3];
	double fConst23;
	double fConst24;
	double fVec4[2];
	double fConst25;
	double fRec25[2];
	double fRec9[2];
	double fRec8[2];
	double fConst26;
	double fRec7[4];
	double fConst27;
	double fConst28;
	double fRec26[2];
	double fVec5[2];
	double fRec6[2];
	double fRec5[3];
	double fConst29;
	double fConst30;
	double fConst31;
	double fRec27[2];
	double fRec4[3];
	double fRec29[2];
	double fRec28[3];
	double fConst32;
	double fConst33;
	double fRec3[3];
	double fConst34;
	double fConst35;
	double fConst36;
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
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec21[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec20[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fVec1[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec22[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec19[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec18[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec23[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fVec2[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec17[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec16[l12] = 0.0;
	for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) fRec15[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fVec3[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec24[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec14[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec13[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec12[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec11[l19] = 0.0;
	for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) fRec10[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fVec4[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fRec25[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fRec9[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec8[l24] = 0.0;
	for (int l25 = 0; (l25 < 4); l25 = (l25 + 1)) fRec7[l25] = 0.0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fRec26[l26] = 0.0;
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) fVec5[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec6[l28] = 0.0;
	for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) fRec5[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec27[l30] = 0.0;
	for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) fRec4[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fRec29[l32] = 0.0;
	for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) fRec28[l33] = 0.0;
	for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) fRec3[l34] = 0.0;
	for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) fRec2[l35] = 0.0;
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
	fConst9 = (2.0 * fConst0);
	fConst10 = mydsp_faustpower2_f(fConst9);
	fConst11 = (3.1415926535897931 / fConst0);
	fConst12 = (1.0 / (fConst11 + 1.0));
	fConst13 = (1.0 - fConst11);
	fConst14 = (1.0 / std::tan((20517.741620594938 / fConst0)));
	fConst15 = (1.0 / (fConst14 + 1.0));
	fConst16 = (1.0 - fConst14);
	fConst17 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst18 = (1.0 / (fConst17 + 1.0));
	fConst19 = (1.0 - fConst17);
	fConst20 = (1.0 / std::tan((414.69023027385271 / fConst0)));
	fConst21 = (1.0 / (fConst20 + 1.0));
	fConst22 = (1.0 - fConst20);
	fConst23 = (1.0 / std::tan((609.46897479641984 / fConst0)));
	fConst24 = (1.0 / (fConst23 + 1.0));
	fConst25 = (1.0 - fConst23);
	fConst26 = (3.0 * fConst9);
	fConst27 = std::exp((0.0 - (200.0 / fConst0)));
	fConst28 = std::exp((0.0 - (0.10000000000000001 / fConst0)));
	fConst29 = (1.0 / std::tan((804.24771931898704 / fConst0)));
	fConst30 = (1.0 / (fConst29 + 1.0));
	fConst31 = (1.0 - fConst29);
	fConst32 = (((fConst5 + -1.4142135623730949) / fConst4) + 1.0);
	fConst33 = (2.0 * (1.0 - fConst8));
	fConst34 = (0.0 - (2.0 / fConst7));
	fConst35 = (((fConst2 + -1.4142135623730949) / fConst1) + 1.0);
	fConst36 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst1))));
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
	double fSlow6 = (fConst9 * (fSlow5 + 0.0026376999999999998));
	double fSlow7 = ((3.1361660000000006e-05 * fSlow4) + 6.9934810000000012e-07);
	double fSlow8 = ((5.9679378000000017e-09 * fSlow4) + 2.9839689000000005e-11);
	double fSlow9 = (fConst9 * fSlow8);
	double fSlow10 = (1.0 / (-1.0 - (fSlow6 + (fConst10 * (fSlow7 + fSlow9)))));
	double fSlow11 = (fConst9 * ((fSlow5 + (0.00023500000000000002 * fSlow3)) + 0.0003347));
	double fSlow12 = (((4.8598000000000007e-07 * fSlow3) + (8.6136600000000025e-06 * fSlow4)) + 9.9628100000000016e-08);
	double fSlow13 = (((2.6728900000000006e-11 * fSlow3) + (fSlow4 * ((5.3457800000000014e-09 * fSlow3) + 6.2215780000000018e-10))) + 3.1107890000000005e-12);
	double fSlow14 = (fConst9 * fSlow13);
	double fSlow15 = (0.0 - (fSlow11 + (fConst10 * (fSlow12 + fSlow14))));
	double fSlow16 = (fSlow1 + -1.0);
	double fSlow17 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider3))));
	double fSlow18 = (fConst26 * fSlow8);
	double fSlow19 = ((fConst10 * (fSlow7 + fSlow18)) + (-3.0 - fSlow6));
	double fSlow20 = ((fSlow6 + (fConst10 * (fSlow7 - fSlow18))) + -3.0);
	double fSlow21 = (fSlow6 + (-1.0 - (fConst10 * (fSlow7 - fSlow9))));
	double fSlow22 = (fConst26 * fSlow13);
	double fSlow23 = ((fConst10 * (fSlow12 + fSlow22)) - fSlow11);
	double fSlow24 = (fSlow11 + (fConst10 * (fSlow12 - fSlow22)));
	double fSlow25 = (fSlow11 - (fConst10 * (fSlow12 - fSlow14)));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec1[0] = (fSlow2 + (0.999 * fRec1[1]));
		double fTemp0 = double(input0[i]);
		double fTemp1 = std::fabs(fTemp0);
		double fTemp2 = ((fTemp0 * (fSlow1 + fTemp1)) / ((mydsp_faustpower2_f(fTemp0) + (fSlow16 * fTemp1)) + 1.0));
		fVec0[0] = fTemp2;
		fRec21[0] = ((0.93028479253239138 * (fTemp2 + fVec0[1])) - (0.86056958506478287 * fRec21[1]));
		fRec20[0] = (fRec21[0] - ((1.8405051250752198 * fRec20[1]) + (0.86129424393186271 * fRec20[2])));
		double fTemp3 = (0.92544984225177063 * (fRec20[0] + fRec20[2]));
		double fTemp4 = (1.8508996845035413 * fRec20[1]);
		double fTemp5 = ((fTemp4 + fTemp3) / (double(Ranode(int(TUBE_TABLE_12AY7_68k), double(fRec19[1]))) + 100000.0));
		fVec1[0] = fTemp5;
		fRec22[0] = (fConst18 * ((2700.0 * (fTemp5 + fVec1[1])) - (fConst19 * fRec22[1])));
		double fTemp6 = double(Ftube(int(TUBE_TABLE_12AY7_68k), double(((fTemp3 + (fRec22[0] + fTemp4)) + -2.775058))));
		fRec19[0] = ((fTemp6 + (0.0010277992592592593 * (double(Ranode(int(TUBE_TABLE_12AY7_68k), double(fTemp6))) + 100000.0))) + -250.0);
		fRec18[0] = (fConst12 * ((fConst13 * fRec18[1]) + (0.025000000000000001 * (fRec19[0] - fRec19[1]))));
		fRec23[0] = (fSlow17 + (0.999 * fRec23[1]));
		double fTemp7 = (fRec18[0] * fRec23[0]);
		fVec2[0] = fTemp7;
		fRec17[0] = (0.0 - (fConst15 * ((fConst16 * fRec17[1]) - (fTemp7 + fVec2[1]))));
		fRec16[0] = ((0.93028479253239138 * (fRec17[0] + fRec17[1])) - (0.86056958506478287 * fRec16[1]));
		fRec15[0] = (fRec16[0] - ((1.8405051250752198 * fRec15[1]) + (0.86129424393186271 * fRec15[2])));
		double fTemp8 = (0.92544984225177063 * (fRec15[0] + fRec15[2]));
		double fTemp9 = (1.8508996845035413 * fRec15[1]);
		double fTemp10 = ((fTemp9 + fTemp8) / (double(Ranode(int(TUBE_TABLE_12AY7_250k), double(fRec14[1]))) + 100000.0));
		fVec3[0] = fTemp10;
		fRec24[0] = (fConst21 * ((1500.0 * (fTemp10 + fVec3[1])) - (fConst22 * fRec24[1])));
		double fTemp11 = double(Ftube(int(TUBE_TABLE_12AY7_250k), double(((fTemp8 + (fRec24[0] + fTemp9)) + -1.9543079999999999))));
		fRec14[0] = ((fTemp11 + (0.0013028720000000001 * (double(Ranode(int(TUBE_TABLE_12AY7_250k), double(fTemp11))) + 100000.0))) + -250.0);
		fRec13[0] = (fConst12 * ((fConst13 * fRec13[1]) + (0.025000000000000001 * (fRec14[0] - fRec14[1]))));
		fRec12[0] = (0.0 - (fConst15 * ((fConst16 * fRec12[1]) - (fRec13[0] + fRec13[1]))));
		fRec11[0] = ((0.93028479253239138 * (fRec12[0] + fRec12[1])) - (0.86056958506478287 * fRec11[1]));
		fRec10[0] = (fRec11[0] - ((1.8405051250752198 * fRec10[1]) + (0.86129424393186271 * fRec10[2])));
		double fTemp12 = (0.92544984225177063 * (fRec10[0] + fRec10[2]));
		double fTemp13 = (1.8508996845035413 * fRec10[1]);
		double fTemp14 = ((fTemp13 + fTemp12) / (double(Ranode(int(TUBE_TABLE_12AY7_250k), double(fRec9[1]))) + 100000.0));
		fVec4[0] = fTemp14;
		fRec25[0] = (fConst24 * ((820.0 * (fTemp14 + fVec4[1])) - (fConst25 * fRec25[1])));
		double fTemp15 = double(Ftube(int(TUBE_TABLE_12AY7_250k), double(((fTemp12 + (fRec25[0] + fTemp13)) + -1.2649159999999999))));
		fRec9[0] = ((fTemp15 + (0.0015425804878048779 * (double(Ranode(int(TUBE_TABLE_12AY7_250k), double(fTemp15))) + 100000.0))) + -250.0);
		fRec8[0] = (fConst12 * ((fConst13 * fRec8[1]) + (0.025000000000000001 * (fRec9[0] - fRec9[1]))));
		fRec7[0] = ((fRec8[0] * fRec0[0]) - (fSlow10 * (((fSlow19 * fRec7[1]) + (fSlow20 * fRec7[2])) + (fSlow21 * fRec7[3]))));
		double fTemp16 = ((((fSlow15 * fRec7[0]) + (fSlow23 * fRec7[1])) + (fSlow24 * fRec7[2])) + (fSlow25 * fRec7[3]));
		double fTemp17 = std::max<double>(1.0, std::fabs((fSlow10 * fTemp16)));
		double fTemp18 = ((fConst27 * double((fRec26[1] < fTemp17))) + (fConst28 * double((fRec26[1] >= fTemp17))));
		fRec26[0] = ((fRec26[1] * fTemp18) + (fTemp17 * (1.0 - fTemp18)));
		double fTemp19 = std::max<double>(0.0, ((20.0 * std::log10(fRec26[0])) + 50.0));
		double fTemp20 = (0.5 * std::min<double>(1.0, std::max<double>(0.0, (0.095229025807065992 * fTemp19))));
		double fTemp21 = (fSlow10 * (fTemp16 * std::pow(10.0, (0.050000000000000003 * (((fTemp19 * (0.0 - fTemp20)) / (fTemp20 + 1.0)) + 10.0)))));
		fVec5[0] = fTemp21;
		fRec6[0] = ((0.93028479253239138 * (fTemp21 + fVec5[1])) - (0.86056958506478287 * fRec6[1]));
		fRec5[0] = (fRec6[0] - ((1.8405051250752198 * fRec5[1]) + (0.86129424393186271 * fRec5[2])));
		double fTemp22 = (0.92544984225177063 * (fRec5[0] + fRec5[2]));
		fRec27[0] = (fConst30 * ((0.065714285714285711 * (fRec4[1] + fRec4[2])) - (fConst31 * fRec27[1])));
		double fTemp23 = (1.8508996845035413 * fRec5[1]);
		fRec4[0] = (double(Ftube(int(TUBE_TABLE_EL34_68k), double(((fTemp22 + (fRec27[0] + fTemp23)) + -15.743945)))) + -255.41822826086957);
		fRec29[0] = (fConst30 * ((0.065714285714285711 * (fRec28[1] + fRec28[2])) - (fConst31 * fRec29[1])));
		fRec28[0] = (double(Ftube(int(TUBE_TABLE_EL34_250k), double(((fTemp22 + (fRec29[0] + fTemp23)) + -15.743945)))) + -255.41822826086957);
		fRec3[0] = ((0.10000000000000001 * (fRec4[0] + fRec28[0])) - (fConst6 * ((fConst32 * fRec3[2]) + (fConst33 * fRec3[1]))));
		fRec2[0] = ((fConst6 * (((fConst8 * fRec3[0]) + (fConst34 * fRec3[1])) + (fConst8 * fRec3[2]))) - (fConst3 * ((fConst35 * fRec2[2]) + (fConst36 * fRec2[1]))));
		output0[i] = FAUSTFLOAT((fConst3 * ((fRec0[0] * fRec1[0]) * (fRec2[2] + (fRec2[0] + (2.0 * fRec2[1]))))));
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fVec0[1] = fVec0[0];
		fRec21[1] = fRec21[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fVec1[1] = fVec1[0];
		fRec22[1] = fRec22[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec23[1] = fRec23[0];
		fVec2[1] = fVec2[0];
		fRec17[1] = fRec17[0];
		fRec16[1] = fRec16[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		fVec3[1] = fVec3[0];
		fRec24[1] = fRec24[0];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fVec4[1] = fVec4[0];
		fRec25[1] = fRec25[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
			fRec7[j0] = fRec7[(j0 - 1)];
		}
		fRec26[1] = fRec26[0];
		fVec5[1] = fVec5[0];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec27[1] = fRec27[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
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
