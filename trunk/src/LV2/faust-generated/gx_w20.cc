// generated from file '../src/LV2/faust/gx_w20.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "math.h"
#include "w20_1_neg_table.h"
#include "w20_1_table.h"
#include "w20_2a_neg_table.h"
#include "w20_2a_table.h"

namespace gx_w20 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
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
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fVec0[2];
	double fConst51;
	double fConst52;
	double fRec10[2];
	double fRec9[3];
	double fVec1[2];
	double fConst53;
	double fConst54;
	double fConst55;
	double fRec8[2];
	double fRec7[3];
	double fVec2[2];
	double fConst56;
	double fConst57;
	double fConst58;
	double fRec6[2];
	double fRec5[3];
	double fVec3[2];
	double fConst59;
	double fConst60;
	double fConst61;
	double fRec4[2];
	double fRec3[3];
	double fRec2[4];
	double fConst62;
	double fConst63;
	double fConst64;
	double fConst65;
	double fConst66;
	double fConst67;
	double fConst68;
	double fConst69;
	double fConst70;
	double fConst71;
	double fRec0[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec11[2];
	double fConst72;
	double fConst73;
	double fRec15[2];
	double fRec14[3];
	double fConst74;
	double fRec13[4];
	double fRec12[2];
	double fConst75;
	double fConst76;
	double fConst77;
	double fRec20[2];
	double fRec19[3];
	double fConst78;
	double fRec18[3];
	double fRec17[4];
	double fRec16[2];
	double fConst79;
	double fConst80;
	double fConst81;
	double fRec26[2];
	double fRec25[3];
	double fConst82;
	double fRec24[3];
	double fRec23[3];
	double fRec22[4];
	double fRec21[2];
	double fConst83;
	double fConst84;
	double fRec33[2];
	double fRec32[3];
	double fConst85;
	double fRec31[3];
	double fRec30[3];
	double fRec29[3];
	double fRec28[4];
	double fRec27[2];

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
	id = "w20";
	name = N_("Westbury W-20");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec1[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fVec0[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec10[l2] = 0.0;
	for (int l3 = 0; l3 < 3; l3 = l3 + 1) fRec9[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fVec1[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec8[l5] = 0.0;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec7[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fVec2[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec6[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec5[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fVec3[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec4[l11] = 0.0;
	for (int l12 = 0; l12 < 3; l12 = l12 + 1) fRec3[l12] = 0.0;
	for (int l13 = 0; l13 < 4; l13 = l13 + 1) fRec2[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec0[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec11[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec15[l16] = 0.0;
	for (int l17 = 0; l17 < 3; l17 = l17 + 1) fRec14[l17] = 0.0;
	for (int l18 = 0; l18 < 4; l18 = l18 + 1) fRec13[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec12[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec20[l20] = 0.0;
	for (int l21 = 0; l21 < 3; l21 = l21 + 1) fRec19[l21] = 0.0;
	for (int l22 = 0; l22 < 3; l22 = l22 + 1) fRec18[l22] = 0.0;
	for (int l23 = 0; l23 < 4; l23 = l23 + 1) fRec17[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec16[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec26[l25] = 0.0;
	for (int l26 = 0; l26 < 3; l26 = l26 + 1) fRec25[l26] = 0.0;
	for (int l27 = 0; l27 < 3; l27 = l27 + 1) fRec24[l27] = 0.0;
	for (int l28 = 0; l28 < 3; l28 = l28 + 1) fRec23[l28] = 0.0;
	for (int l29 = 0; l29 < 4; l29 = l29 + 1) fRec22[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec21[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec33[l31] = 0.0;
	for (int l32 = 0; l32 < 3; l32 = l32 + 1) fRec32[l32] = 0.0;
	for (int l33 = 0; l33 < 3; l33 = l33 + 1) fRec31[l33] = 0.0;
	for (int l34 = 0; l34 < 3; l34 = l34 + 1) fRec30[l34] = 0.0;
	for (int l35 = 0; l35 < 3; l35 = l35 + 1) fRec29[l35] = 0.0;
	for (int l36 = 0; l36 < 4; l36 = l36 + 1) fRec28[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec27[l37] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 2.07411011655813e-05 * fConst0;
	fConst2 = fConst1 + 0.00442714405209691;
	fConst3 = (0.00442714405209691 - fConst1) / fConst2;
	fConst4 = 2.37114810573187e-14 * fConst0;
	fConst5 = mydsp_faustpower2_f(fConst0);
	fConst6 = fConst5 * (-6.90938348698522e-13 - fConst4);
	fConst7 = 2.29013691097909e-14 * fConst0;
	fConst8 = fConst0 * (fConst0 * (fConst7 + -1.12102439518276e-11) + -3.45469174349261e-10);
	fConst9 = 8.10111947527771e-16 * fConst0;
	fConst10 = fConst0 * (fConst0 * (fConst9 + 1.34509147324758e-10) + 6.33060724204724e-08);
	fConst11 = fConst5 * (fConst4 + -6.90938348698522e-13);
	fConst12 = fConst0 * (fConst0 * (-1.12102439518276e-11 - fConst7) + 3.45469174349261e-10);
	fConst13 = fConst0 * (fConst0 * (1.34509147324758e-10 - fConst9) + -6.33060724204724e-08);
	fConst14 = 7.1134443171956e-14 * fConst0;
	fConst15 = fConst5 * (6.90938348698522e-13 - fConst14);
	fConst16 = 6.87041073293727e-14 * fConst0;
	fConst17 = fConst0 * (fConst0 * (fConst16 + 1.12102439518276e-11) + 3.45469174349261e-10);
	fConst18 = 2.43033584258331e-15 * fConst0;
	fConst19 = fConst0 * (fConst0 * (fConst18 + -1.34509147324758e-10) + -6.33060724204724e-08);
	fConst20 = fConst5 * (fConst14 + 6.90938348698522e-13);
	fConst21 = fConst0 * (fConst0 * (1.12102439518276e-11 - fConst16) + -3.45469174349261e-10);
	fConst22 = fConst0 * (fConst0 * (-1.34509147324758e-10 - fConst18) + 6.33060724204724e-08);
	fConst23 = std::tan(270.1769682087222 / fConst0);
	fConst24 = mydsp_faustpower2_f(fConst23);
	fConst25 = 2.0 * (1.0 - 1.0 / fConst24);
	fConst26 = 1.0 / fConst23;
	fConst27 = (fConst26 + -1.0000000000000004) / fConst23 + 1.0;
	fConst28 = (fConst26 + 1.0000000000000004) / fConst23 + 1.0;
	fConst29 = 1.0 / fConst28;
	fConst30 = std::tan(659.7344572538566 / fConst0);
	fConst31 = mydsp_faustpower2_f(fConst30);
	fConst32 = 2.0 * (1.0 - 1.0 / fConst31);
	fConst33 = 1.0 / fConst30;
	fConst34 = (fConst33 + -1.0000000000000004) / fConst30 + 1.0;
	fConst35 = (fConst33 + 1.0000000000000004) / fConst30 + 1.0;
	fConst36 = 1.0 / fConst35;
	fConst37 = std::tan(3769.9111843077517 / fConst0);
	fConst38 = mydsp_faustpower2_f(fConst37);
	fConst39 = 2.0 * (1.0 - 1.0 / fConst38);
	fConst40 = 1.0 / fConst37;
	fConst41 = (fConst40 + -1.0000000000000004) / fConst37 + 1.0;
	fConst42 = (fConst40 + 1.0000000000000004) / fConst37 + 1.0;
	fConst43 = 1.0 / fConst42;
	fConst44 = std::tan(20517.741620594938 / fConst0);
	fConst45 = mydsp_faustpower2_f(fConst44);
	fConst46 = 2.0 * (1.0 - 1.0 / fConst45);
	fConst47 = 1.0 / fConst44;
	fConst48 = (fConst47 + -1.0000000000000004) / fConst44 + 1.0;
	fConst49 = (fConst47 + 1.0000000000000004) / fConst44 + 1.0;
	fConst50 = 1.0 / fConst49;
	fConst51 = 1.0 - fConst47;
	fConst52 = 1.0 / (fConst47 + 1.0);
	fConst53 = 1.0 - fConst40;
	fConst54 = fConst40 + 1.0;
	fConst55 = 1.0 / fConst54;
	fConst56 = 1.0 - fConst33;
	fConst57 = fConst33 + 1.0;
	fConst58 = 1.0 / fConst57;
	fConst59 = 1.0 - fConst26;
	fConst60 = fConst26 + 1.0;
	fConst61 = 1.0 / fConst60;
	fConst62 = 1.44375296887024e-12 * fConst0;
	fConst63 = fConst5 * (2.1875044982882e-11 - fConst62);
	fConst64 = fConst0 * (fConst0 * (fConst62 + -7.24063988933406e-09) + 1.0937522491441e-07);
	fConst65 = 4.33125890661071e-12 * fConst0;
	fConst66 = fConst5 * (fConst65 + -2.1875044982882e-11);
	fConst67 = fConst0 * (fConst0 * (7.24063988933406e-09 - fConst65) + 1.0937522491441e-07);
	fConst68 = fConst5 * (-2.1875044982882e-11 - fConst65);
	fConst69 = fConst0 * (fConst0 * (fConst65 + 7.24063988933406e-09) + -1.0937522491441e-07);
	fConst70 = fConst5 * (fConst62 + 2.1875044982882e-11);
	fConst71 = fConst0 * (fConst0 * (-7.24063988933406e-09 - fConst62) + -1.0937522491441e-07);
	fConst72 = 0.000616100994039436 * (fConst0 / fConst2);
	fConst73 = 1.0 / (fConst23 * fConst35);
	fConst74 = 1.0 / (fConst24 * fConst28);
	fConst75 = 1.0 - fConst59 / fConst23;
	fConst76 = 1.0 / (fConst60 / fConst23 + 1.0);
	fConst77 = 1.0 / (fConst30 * fConst42);
	fConst78 = 1.0 / (fConst31 * fConst35);
	fConst79 = 1.0 - fConst56 / fConst30;
	fConst80 = 1.0 / (fConst57 / fConst30 + 1.0);
	fConst81 = 1.0 / (fConst37 * fConst49);
	fConst82 = 1.0 / (fConst38 * fConst42);
	fConst83 = 1.0 - fConst53 / fConst37;
	fConst84 = 1.0 / (fConst54 / fConst37 + 1.0);
	fConst85 = 1.0 / (fConst45 * fConst49);
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
	double fSlow0 = 0.00036676987543879196 * (std::exp(3.0 * double(fVslider0)) + -1.0);
	double fSlow1 = 0.00036676987543879196 * (std::exp(3.0 * double(fVslider1)) + -1.0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec1[0] = fSlow0 + 0.993 * fRec1[1];
		double fTemp0 = fConst10 + fRec1[0] * (fConst8 + fConst6 * fRec1[0]) + 1.72734587174631e-06;
		double fTemp1 = fConst13 + fRec1[0] * (fConst12 + fConst11 * fRec1[0]) + 1.72734587174631e-06;
		double fTemp2 = fConst19 + fRec1[0] * (fConst17 + fConst15 * fRec1[0]) + 5.18203761523892e-06;
		double fTemp3 = fConst22 + fRec1[0] * (fConst21 + fConst20 * fRec1[0]) + 5.18203761523892e-06;
		double fTemp4 = double(input0[i0]);
		fVec0[0] = fTemp4;
		fRec10[0] = -(fConst52 * (fConst51 * fRec10[1] - (fTemp4 + fVec0[1])));
		fRec9[0] = fRec10[0] - fConst50 * (fConst48 * fRec9[2] + fConst46 * fRec9[1]);
		double fTemp5 = fRec9[2] + fRec9[0] + 2.0 * fRec9[1];
		fVec1[0] = fTemp5;
		fRec8[0] = -(fConst55 * (fConst53 * fRec8[1] - fConst50 * (fTemp5 + fVec1[1])));
		fRec7[0] = fRec8[0] - fConst43 * (fConst41 * fRec7[2] + fConst39 * fRec7[1]);
		double fTemp6 = fRec7[2] + fRec7[0] + 2.0 * fRec7[1];
		fVec2[0] = fTemp6;
		fRec6[0] = -(fConst58 * (fConst56 * fRec6[1] - fConst43 * (fTemp6 + fVec2[1])));
		fRec5[0] = fRec6[0] - fConst36 * (fConst34 * fRec5[2] + fConst32 * fRec5[1]);
		double fTemp7 = fRec5[2] + fRec5[0] + 2.0 * fRec5[1];
		fVec3[0] = fTemp7;
		fRec4[0] = -(fConst61 * (fConst59 * fRec4[1] - fConst36 * (fTemp7 + fVec3[1])));
		fRec3[0] = fRec4[0] - fConst29 * (fConst27 * fRec3[2] + fConst25 * fRec3[1]);
		fRec2[0] = fConst29 * (fRec3[2] + fRec3[0] + 2.0 * fRec3[1]) - (fTemp3 * fRec2[1] + fTemp2 * fRec2[2] + fTemp1 * fRec2[3]) / fTemp0;
		double fTemp8 = fConst64 + fConst63 * fRec1[0];
		double fTemp9 = fConst67 + fConst66 * fRec1[0];
		double fTemp10 = fConst69 + fConst68 * fRec1[0];
		double fTemp11 = fConst71 + fConst70 * fRec1[0];
		double fTemp12 = fRec1[0] * (fRec2[0] * fTemp11 + fTemp10 * fRec2[1] + fTemp9 * fRec2[2] + fTemp8 * fRec2[3]) / fTemp0;
		fRec0[0] = ((signbit(fTemp12)) ? w20_1_negclip(fTemp12) : w20_1clip(fTemp12)) - fConst3 * fRec0[1];
		fRec11[0] = fSlow1 + 0.993 * fRec11[1];
		double fTemp13 = fConst72 * fRec11[0] * (fRec0[0] - fRec0[1]);
		fRec15[0] = -(fConst61 * (fConst59 * fRec15[1] - fConst73 * (fTemp7 - fVec3[1])));
		fRec14[0] = fRec15[0] - fConst29 * (fConst27 * fRec14[2] + fConst25 * fRec14[1]);
		fRec13[0] = fConst74 * (fRec14[2] + (fRec14[0] - 2.0 * fRec14[1])) - (fTemp3 * fRec13[1] + fTemp2 * fRec13[2] + fTemp1 * fRec13[3]) / fTemp0;
		double fTemp14 = fRec1[0] * (fRec13[0] * fTemp11 + fTemp10 * fRec13[1] + fTemp9 * fRec13[2] + fTemp8 * fRec13[3]) / fTemp0;
		fRec12[0] = ((signbit(fTemp14)) ? w20_1_negclip(fTemp14) : w20_1clip(fTemp14)) - fConst3 * fRec12[1];
		double fTemp15 = fConst72 * fRec11[0] * (fRec12[0] - fRec12[1]);
		double fTemp16 = fConst25 * fRec18[1];
		fRec20[0] = -(fConst58 * (fConst56 * fRec20[1] - fConst77 * (fTemp6 - fVec2[1])));
		fRec19[0] = fRec20[0] - fConst36 * (fConst34 * fRec19[2] + fConst32 * fRec19[1]);
		fRec18[0] = fConst78 * (fRec19[2] + (fRec19[0] - 2.0 * fRec19[1])) - fConst76 * (fConst75 * fRec18[2] + fTemp16);
		fRec17[0] = fRec18[2] + fConst76 * (fTemp16 + fConst75 * fRec18[0]) - (fTemp3 * fRec17[1] + fTemp2 * fRec17[2] + fTemp1 * fRec17[3]) / fTemp0;
		double fTemp17 = fRec1[0] * (fRec17[0] * fTemp11 + fTemp10 * fRec17[1] + fTemp9 * fRec17[2] + fTemp8 * fRec17[3]) / fTemp0;
		fRec16[0] = ((signbit(fTemp17)) ? w20_1_negclip(fTemp17) : w20_1clip(fTemp17)) - fConst3 * fRec16[1];
		double fTemp18 = fConst72 * fRec11[0] * (fRec16[0] - fRec16[1]);
		double fTemp19 = fConst25 * fRec23[1];
		double fTemp20 = fConst32 * fRec24[1];
		fRec26[0] = -(fConst55 * (fConst53 * fRec26[1] - fConst81 * (fTemp5 - fVec1[1])));
		fRec25[0] = fRec26[0] - fConst43 * (fConst41 * fRec25[2] + fConst39 * fRec25[1]);
		fRec24[0] = fConst82 * (fRec25[2] + (fRec25[0] - 2.0 * fRec25[1])) - fConst80 * (fConst79 * fRec24[2] + fTemp20);
		fRec23[0] = fRec24[2] + fConst80 * (fTemp20 + fConst79 * fRec24[0]) - fConst76 * (fConst75 * fRec23[2] + fTemp19);
		fRec22[0] = fRec23[2] + fConst76 * (fTemp19 + fConst75 * fRec23[0]) - (fTemp3 * fRec22[1] + fTemp2 * fRec22[2] + fTemp1 * fRec22[3]) / fTemp0;
		double fTemp21 = fRec1[0] * (fRec22[0] * fTemp11 + fTemp10 * fRec22[1] + fTemp9 * fRec22[2] + fTemp8 * fRec22[3]) / fTemp0;
		fRec21[0] = ((signbit(fTemp21)) ? w20_1_negclip(fTemp21) : w20_1clip(fTemp21)) - fConst3 * fRec21[1];
		double fTemp22 = fConst72 * fRec11[0] * (fRec21[0] - fRec21[1]);
		double fTemp23 = fConst25 * fRec29[1];
		double fTemp24 = fConst32 * fRec30[1];
		double fTemp25 = fConst39 * fRec31[1];
		fRec33[0] = -(fConst52 * (fConst51 * fRec33[1] - fConst47 * (fTemp4 - fVec0[1])));
		fRec32[0] = fRec33[0] - fConst50 * (fConst48 * fRec32[2] + fConst46 * fRec32[1]);
		fRec31[0] = fConst85 * (fRec32[2] + (fRec32[0] - 2.0 * fRec32[1])) - fConst84 * (fConst83 * fRec31[2] + fTemp25);
		fRec30[0] = fRec31[2] + fConst84 * (fTemp25 + fConst83 * fRec31[0]) - fConst80 * (fConst79 * fRec30[2] + fTemp24);
		fRec29[0] = fRec30[2] + fConst80 * (fTemp24 + fConst79 * fRec30[0]) - fConst76 * (fConst75 * fRec29[2] + fTemp23);
		fRec28[0] = fRec29[2] + fConst76 * (fTemp23 + fConst75 * fRec29[0]) - (fRec28[1] * fTemp3 + fRec28[2] * fTemp2 + fRec28[3] * fTemp1) / fTemp0;
		double fTemp26 = fRec1[0] * (fRec28[0] * fTemp11 + fRec28[1] * fTemp10 + fRec28[2] * fTemp9 + fRec28[3] * fTemp8) / fTemp0;
		fRec27[0] = ((signbit(fTemp26)) ? w20_1_negclip(fTemp26) : w20_1clip(fTemp26)) - fConst3 * fRec27[1];
		double fTemp27 = fConst72 * fRec11[0] * (fRec27[0] - fRec27[1]);
		output0[i0] = FAUSTFLOAT(((signbit(-fTemp27)) ? w20_2a_negclip(-fTemp27) : w20_2aclip(-fTemp27)) + ((signbit(-fTemp22)) ? w20_2a_negclip(-fTemp22) : w20_2aclip(-fTemp22)) + ((signbit(-fTemp18)) ? w20_2a_negclip(-fTemp18) : w20_2aclip(-fTemp18)) + ((signbit(-fTemp15)) ? w20_2a_negclip(-fTemp15) : w20_2aclip(-fTemp15)) + ((signbit(-fTemp13)) ? w20_2a_negclip(-fTemp13) : w20_2aclip(-fTemp13)));
		fRec1[1] = fRec1[0];
		fVec0[1] = fVec0[0];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fVec1[1] = fVec1[0];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fVec2[1] = fVec2[0];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fVec3[1] = fVec3[0];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
			fRec2[j0] = fRec2[j0 - 1];
		}
		fRec0[1] = fRec0[0];
		fRec11[1] = fRec11[0];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		for (int j1 = 3; j1 > 0; j1 = j1 - 1) {
			fRec13[j1] = fRec13[j1 - 1];
		}
		fRec12[1] = fRec12[0];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fRec18[2] = fRec18[1];
		fRec18[1] = fRec18[0];
		for (int j2 = 3; j2 > 0; j2 = j2 - 1) {
			fRec17[j2] = fRec17[j2 - 1];
		}
		fRec16[1] = fRec16[0];
		fRec26[1] = fRec26[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fRec23[2] = fRec23[1];
		fRec23[1] = fRec23[0];
		for (int j3 = 3; j3 > 0; j3 = j3 - 1) {
			fRec22[j3] = fRec22[j3 - 1];
		}
		fRec21[1] = fRec21[0];
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fRec29[2] = fRec29[1];
		fRec29[1] = fRec29[0];
		for (int j4 = 3; j4 > 0; j4 = j4 - 1) {
			fRec28[j4] = fRec28[j4 - 1];
		}
		fRec27[1] = fRec27[0];
	}
#undef fVslider0
#undef fVslider1
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case GAIN: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case LEVEL: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   GAIN, 
   LEVEL, 
} PortIndex;
*/

} // end namespace gx_w20
