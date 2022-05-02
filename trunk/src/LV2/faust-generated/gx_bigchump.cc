// generated from file '../src/LV2/faust/gx_bigchump.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "bigchumppower_neg_table.h"
#include "bigchumppower_table.h"
#include "bigchumppre2_neg_table.h"
#include "bigchumppre2_table.h"
#include "bigchumppre_neg_table.h"
#include "bigchumppre_table.h"
#include "math.h"

namespace gx_bigchump {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	double fConst0;
	double fConst1;
	double fConst4;
	double fConst6;
	double fConst9;
	double fConst11;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec3[2];
	double fConst13;
	double fConst14;
	double fConst16;
	double fConst18;
	double fVec0[2];
	double fConst19;
	double fConst20;
	double fRec9[2];
	double fConst21;
	double fConst22;
	double fRec8[3];
	double fConst23;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst31;
	double fConst32;
	double fRec7[3];
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst40;
	double fConst41;
	double fRec6[3];
	double fConst45;
	double fConst46;
	double fConst47;
	double fConst49;
	double fConst50;
	double fRec5[3];
	double fConst52;
	double fConst54;
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst64;
	double fConst66;
	double fConst68;
	double fConst69;
	double fConst70;
	double fConst71;
	double fRec4[5];
	double fConst73;
	double fConst75;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec10[2];
	double fConst77;
	double fConst78;
	double fConst79;
	double fConst80;
	double fConst81;
	double fConst82;
	double fConst83;
	double fConst84;
	double fConst85;
	double fRec2[3];
	double fConst86;
	double fConst87;
	double fConst88;
	double fConst90;
	double fConst91;
	double fConst92;
	double fRec1[4];
	double fConst94;
	double fConst95;
	double fConst96;
	double fConst97;
	double fConst98;
	double fRec19[2];
	double fRec18[3];
	double fVec1[2];
	double fConst99;
	double fConst100;
	double fRec17[2];
	double fConst101;
	double fRec16[3];
	double fConst102;
	double fRec15[3];
	double fRec14[3];
	double fRec13[5];
	double fRec12[3];
	double fRec11[4];
	double fConst103;
	double fConst104;
	double fConst105;
	double fRec27[2];
	double fRec26[3];
	double fVec2[2];
	double fConst106;
	double fConst107;
	double fRec25[2];
	double fConst108;
	double fRec24[3];
	double fConst109;
	double fRec23[3];
	double fRec22[5];
	double fRec21[3];
	double fRec20[4];
	double fConst110;
	double fConst111;
	double fConst112;
	double fRec34[2];
	double fRec33[3];
	double fVec3[2];
	double fConst113;
	double fConst114;
	double fRec32[2];
	double fConst115;
	double fRec31[3];
	double fConst116;
	double fRec30[5];
	double fRec29[3];
	double fRec28[4];
	double fConst117;
	double fRec39[2];
	double fRec38[3];
	double fRec37[5];
	double fRec36[3];
	double fRec35[4];

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
	id = "gx_bigchump";
	name = N_("Redeye Big Chump");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec3[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fVec0[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec9[l3] = 0.0;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRec8[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec7[l5] = 0.0;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec6[l6] = 0.0;
	for (int l7 = 0; l7 < 3; l7 = l7 + 1) fRec5[l7] = 0.0;
	for (int l8 = 0; l8 < 5; l8 = l8 + 1) fRec4[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec10[l9] = 0.0;
	for (int l10 = 0; l10 < 3; l10 = l10 + 1) fRec2[l10] = 0.0;
	for (int l11 = 0; l11 < 4; l11 = l11 + 1) fRec1[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec19[l12] = 0.0;
	for (int l13 = 0; l13 < 3; l13 = l13 + 1) fRec18[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fVec1[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec17[l15] = 0.0;
	for (int l16 = 0; l16 < 3; l16 = l16 + 1) fRec16[l16] = 0.0;
	for (int l17 = 0; l17 < 3; l17 = l17 + 1) fRec15[l17] = 0.0;
	for (int l18 = 0; l18 < 3; l18 = l18 + 1) fRec14[l18] = 0.0;
	for (int l19 = 0; l19 < 5; l19 = l19 + 1) fRec13[l19] = 0.0;
	for (int l20 = 0; l20 < 3; l20 = l20 + 1) fRec12[l20] = 0.0;
	for (int l21 = 0; l21 < 4; l21 = l21 + 1) fRec11[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec27[l22] = 0.0;
	for (int l23 = 0; l23 < 3; l23 = l23 + 1) fRec26[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fVec2[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec25[l25] = 0.0;
	for (int l26 = 0; l26 < 3; l26 = l26 + 1) fRec24[l26] = 0.0;
	for (int l27 = 0; l27 < 3; l27 = l27 + 1) fRec23[l27] = 0.0;
	for (int l28 = 0; l28 < 5; l28 = l28 + 1) fRec22[l28] = 0.0;
	for (int l29 = 0; l29 < 3; l29 = l29 + 1) fRec21[l29] = 0.0;
	for (int l30 = 0; l30 < 4; l30 = l30 + 1) fRec20[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec34[l31] = 0.0;
	for (int l32 = 0; l32 < 3; l32 = l32 + 1) fRec33[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fVec3[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fRec32[l34] = 0.0;
	for (int l35 = 0; l35 < 3; l35 = l35 + 1) fRec31[l35] = 0.0;
	for (int l36 = 0; l36 < 5; l36 = l36 + 1) fRec30[l36] = 0.0;
	for (int l37 = 0; l37 < 3; l37 = l37 + 1) fRec29[l37] = 0.0;
	for (int l38 = 0; l38 < 4; l38 = l38 + 1) fRec28[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec39[l39] = 0.0;
	for (int l40 = 0; l40 < 3; l40 = l40 + 1) fRec38[l40] = 0.0;
	for (int l41 = 0; l41 < 5; l41 = l41 + 1) fRec37[l41] = 0.0;
	for (int l42 = 0; l42 < 3; l42 = l42 + 1) fRec36[l42] = 0.0;
	for (int l43 = 0; l43 < 4; l43 = l43 + 1) fRec35[l43] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	double fConst2 = 8.9068910724842994e-15 * fConst0;
	double fConst3 = fConst0 * (fConst0 * (fConst2 + 6.4917759212794798e-12) + 2.5100665591164499e-10) + 2.4697044736012902e-09;
	fConst4 = fConst1 / fConst3;
	double fConst5 = 9.0138480164185596e-13 * fConst0;
	fConst6 = fConst5 + 1.6298631366961702e-11;
	double fConst7 = 4.3359066716033201e-10 * fConst0;
	double fConst8 = fConst0 * (fConst7 + 2.0976223579538801e-08) + 2.44130776766847e-07;
	fConst9 = fConst0 / fConst8;
	double fConst10 = 2.5486049432641702e-08 * fConst0;
	fConst11 = -3.39813992435224e-07 - fConst10;
	double fConst12 = std::tan(20517.741620594938 / fConst0);
	fConst13 = 1.0 / fConst12;
	fConst14 = 1.0 / ((fConst13 + 1.0000000000000004) / fConst12 + 1.0);
	double fConst15 = mydsp_faustpower2_f(fConst12);
	fConst16 = 1.0 / fConst15;
	double fConst17 = fConst13 + 1.0;
	fConst18 = 0.0 - 1.0 / (fConst12 * fConst17);
	fConst19 = 1.0 / fConst17;
	fConst20 = 1.0 - fConst13;
	fConst21 = (fConst13 + -1.0000000000000004) / fConst12 + 1.0;
	fConst22 = 2.0 * (1.0 - fConst16);
	fConst23 = 0.0 - 2.0 / fConst15;
	double fConst24 = std::tan(3769.9111843077517 / fConst0);
	double fConst25 = 1.0 / fConst24;
	double fConst26 = fConst25 + 1.0;
	fConst27 = 1.0 / (fConst26 / fConst24 + 1.0);
	fConst28 = 1.0 - fConst25;
	fConst29 = 1.0 - fConst28 / fConst24;
	double fConst30 = mydsp_faustpower2_f(fConst24);
	fConst31 = 1.0 / fConst30;
	fConst32 = 2.0 * (1.0 - fConst31);
	double fConst33 = std::tan(659.73445725385659 / fConst0);
	double fConst34 = 1.0 / fConst33;
	double fConst35 = fConst34 + 1.0;
	fConst36 = 1.0 / (fConst35 / fConst33 + 1.0);
	fConst37 = 1.0 - fConst34;
	fConst38 = 1.0 - fConst37 / fConst33;
	double fConst39 = mydsp_faustpower2_f(fConst33);
	fConst40 = 1.0 / fConst39;
	fConst41 = 2.0 * (1.0 - fConst40);
	double fConst42 = std::tan(270.1769682087222 / fConst0);
	double fConst43 = 1.0 / fConst42;
	double fConst44 = fConst43 + 1.0;
	fConst45 = 1.0 / (fConst44 / fConst42 + 1.0);
	fConst46 = 1.0 - fConst43;
	fConst47 = 1.0 - fConst46 / fConst42;
	double fConst48 = mydsp_faustpower2_f(fConst42);
	fConst49 = 1.0 / fConst48;
	fConst50 = 2.0 * (1.0 - fConst49);
	double fConst51 = 1.99975590383756e-19 * fConst0;
	fConst52 = fConst1 * (-6.0498368275157696e-16 - fConst51) + 1.3013842919715099e-11;
	double fConst53 = 1.9997559038375601e-18 * fConst0;
	fConst54 = fConst1 * (-1.05044706792186e-15 - fConst53) + 6.19273198244244e-13;
	double fConst55 = 1.9334301783374702e-18 * fConst0;
	fConst56 = fConst1 * (fConst55 + 9.9148601709850608e-16);
	fConst57 = 2.9996338557563498e-19 * fConst1 + -2.8037288490136399e-13;
	fConst58 = 2.9996338557563499e-18 * fConst1 + -5.1188389201318301e-14;
	fConst59 = 2.4770927929769801e-14 - 2.9001452675062101e-18 * fConst1;
	fConst60 = fConst1 * (6.0498368275157696e-16 - fConst51) + -1.3013842919715099e-11;
	fConst61 = fConst1 * (1.05044706792186e-15 - fConst53) + -6.19273198244244e-13;
	fConst62 = fConst1 * (fConst55 + -9.9148601709850608e-16);
	double fConst63 = 4.9993897595939102e-20 * fConst0;
	fConst64 = fConst0 * (fConst0 * (fConst63 + -3.0249184137578799e-16) + 1.4018644245068199e-13) + -6.50692145985754e-12;
	double fConst65 = 4.9993897595939098e-19 * fConst0;
	fConst66 = fConst0 * (fConst0 * (fConst65 + -5.2522353396092803e-16) + 2.5594194600659201e-14) + -3.09636599122122e-13;
	double fConst67 = 4.8335754458436803e-19 * fConst0;
	fConst68 = fConst0 * (fConst0 * (4.9574300854925304e-16 - fConst67) + -1.23854639648849e-14);
	fConst69 = fConst0 * (fConst0 * (fConst63 + 3.0249184137578799e-16) + 1.4018644245068199e-13) + 6.50692145985754e-12;
	fConst70 = fConst0 * (fConst0 * (fConst65 + 5.2522353396092803e-16) + 2.5594194600659201e-14) + 3.09636599122122e-13;
	fConst71 = fConst0 * (fConst0 * (-4.9574300854925304e-16 - fConst67) + -1.23854639648849e-14);
	double fConst72 = 2.8419671458380501e-18 * fConst0;
	fConst73 = fConst0 * (fConst0 * (-2.8798600411158901e-15 - fConst72) + -7.1428107598729697e-12) + -9.4732238194602296e-11;
	double fConst74 = 1.42098357291903e-14 * fConst0;
	fConst75 = fConst0 * (-1.89464476389205e-13 - fConst74);
	double fConst76 = 1.1367868583352201e-17 * fConst0;
	fConst77 = fConst1 * (fConst76 + 5.7597200822317897e-15) + -1.8946447638920501e-10;
	fConst78 = 2.84196714583805e-14 * fConst1;
	fConst79 = 1.4285621519745901e-11 - 1.7051802875028302e-17 * fConst1;
	fConst80 = fConst1 * (fConst76 + -5.7597200822317897e-15) + 1.8946447638920501e-10;
	fConst81 = fConst0 * (fConst0 * (2.8798600411158901e-15 - fConst72) + -7.1428107598729697e-12) + 9.4732238194602296e-11;
	fConst82 = fConst0 * (fConst74 + -1.89464476389205e-13);
	fConst83 = 1.0 / fConst8;
	fConst84 = 4.8826155353369304e-07 - 8.6718133432066401e-10 * fConst1;
	fConst85 = fConst0 * (fConst7 + -2.0976223579538801e-08) + 2.44130776766847e-07;
	fConst86 = 5.0972098865283297e-08 * fConst0;
	fConst87 = 3.39813992435224e-07 - fConst10;
	fConst88 = 1.0 / fConst3;
	double fConst89 = 2.6720673217452901e-14 * fConst0;
	fConst90 = fConst0 * (fConst0 * (-6.4917759212794798e-12 - fConst89) + 2.5100665591164499e-10) + 7.4091134208038597e-09;
	fConst91 = fConst0 * (fConst0 * (fConst89 + -6.4917759212794798e-12) + -2.5100665591164499e-10) + 7.4091134208038597e-09;
	fConst92 = fConst0 * (fConst0 * (6.4917759212794798e-12 - fConst2) + -2.5100665591164499e-10) + 2.4697044736012902e-09;
	double fConst93 = 2.7041544049255698e-12 * fConst0;
	fConst94 = -1.6298631366961702e-11 - fConst93;
	fConst95 = fConst93 + -1.6298631366961702e-11;
	fConst96 = 1.6298631366961702e-11 - fConst5;
	fConst97 = 1.0 / ((fConst25 + 1.0000000000000004) / fConst24 + 1.0);
	fConst98 = 1.0 / (fConst24 * fConst26);
	fConst99 = 0.0 - fConst98;
	fConst100 = fConst28 / fConst26;
	fConst101 = (fConst25 + -1.0000000000000004) / fConst24 + 1.0;
	fConst102 = 0.0 - 2.0 / fConst30;
	fConst103 = 1.0 / ((fConst34 + 1.0000000000000004) / fConst33 + 1.0);
	fConst104 = 1.0 / (fConst33 * fConst35);
	fConst105 = 1.0 / fConst26;
	fConst106 = 0.0 - fConst104;
	fConst107 = fConst37 / fConst35;
	fConst108 = (fConst34 + -1.0000000000000004) / fConst33 + 1.0;
	fConst109 = 0.0 - 2.0 / fConst39;
	fConst110 = 1.0 / ((fConst43 + 1.0000000000000004) / fConst42 + 1.0);
	fConst111 = 1.0 / (fConst42 * fConst44);
	fConst112 = 1.0 / fConst35;
	fConst113 = 0.0 - fConst111;
	fConst114 = fConst46 / fConst44;
	fConst115 = (fConst43 + -1.0000000000000004) / fConst42 + 1.0;
	fConst116 = 0.0 - 2.0 / fConst48;
	fConst117 = 1.0 / fConst44;
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
	double fSlow0 = 0.0010000000000000009 * double(fVslider0);
	double fSlow1 = 0.00036676987543879196 * (std::exp(3.0 * double(fVslider1)) + -1.0);
	double fSlow2 = 0.0070000000000000062 * double(fVslider2);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.999 * fRec0[1];
		fRec3[0] = fSlow1 + 0.99299999999999999 * fRec3[1];
		double fTemp0 = double(input0[i0]);
		fVec0[0] = fTemp0;
		fRec9[0] = fConst18 * fVec0[1] - fConst19 * (fConst20 * fRec9[1] - fConst13 * fTemp0);
		fRec8[0] = fRec9[0] - fConst14 * (fConst21 * fRec8[2] + fConst22 * fRec8[1]);
		double fTemp1 = fConst32 * fRec7[1];
		fRec7[0] = fConst14 * (fConst16 * fRec8[0] + fConst23 * fRec8[1] + fConst16 * fRec8[2]) - fConst27 * (fConst29 * fRec7[2] + fTemp1);
		double fTemp2 = fConst41 * fRec6[1];
		fRec6[0] = (fRec7[2] + fConst27 * (fTemp1 + fConst29 * fRec7[0])) - fConst36 * (fConst38 * fRec6[2] + fTemp2);
		double fTemp3 = fConst50 * fRec5[1];
		fRec5[0] = (fRec6[2] + fConst36 * (fTemp2 + fConst38 * fRec6[0])) - fConst45 * (fConst47 * fRec5[2] + fTemp3);
		double fTemp4 = fConst0 * (fConst52 + fRec3[0] * (fConst54 + fConst56 * fRec3[0])) + 3.0963659912212198e-10;
		double fTemp5 = fConst1 * (fConst57 + fRec3[0] * (fConst58 + fConst59 * fRec3[0])) + 4.64454898683183e-10;
		double fTemp6 = fConst0 * (fConst60 + fRec3[0] * (fConst61 + fConst62 * fRec3[0])) + 3.0963659912212198e-10;
		double fTemp7 = fConst0 * (fConst64 + fRec3[0] * (fConst66 + fConst68 * fRec3[0])) + 7.7409149780530496e-11;
		double fTemp8 = fConst0 * (fConst69 + fRec3[0] * (fConst70 + fConst71 * fRec3[0])) + 7.7409149780530496e-11;
		fRec4[0] = (fRec5[2] + fConst45 * (fTemp3 + fConst47 * fRec5[0])) - (fRec4[1] * fTemp4 + fRec4[2] * fTemp5 + fRec4[3] * fTemp6 + fRec4[4] * fTemp7) / fTemp8;
		fRec10[0] = fSlow2 + 0.99299999999999999 * fRec10[1];
		double fTemp9 = fConst73 + fConst75 * fRec10[0];
		double fTemp10 = fConst77 + fConst78 * fRec10[0];
		double fTemp11 = fConst79 + 3.7892895277840898e-13 * fRec10[0];
		double fTemp12 = fConst1 * fRec10[0] * (0.0 - 2.84196714583805e-14 * fRec3[0]) + fConst80 * fRec3[0];
		double fTemp13 = fConst81 + fConst82 * fRec10[0];
		double fTemp14 = fConst0 * (fRec3[0] * (fRec4[0] * fTemp9 + fRec4[1] * fTemp10 + fConst0 * fRec4[2] * fTemp11) + fRec4[3] * fTemp12 + fRec3[0] * fRec4[4] * fTemp13) / fTemp8;
		double fThen0 = double(bigchumppreclip(double(fTemp14)));
		double fElse0 = double(bigchumppre_negclip(double(fTemp14)));
		fRec2[0] = ((int(signbit(double(fTemp14)))) ? fElse0 : fThen0) - fConst83 * (fConst84 * fRec2[1] + fConst85 * fRec2[2]);
		double fTemp15 = fConst9 * (fConst11 * fRec2[0] + fConst86 * fRec2[1] + fConst87 * fRec2[2]);
		double fThen1 = double(bigchumppre2clip(double(fTemp15)));
		double fElse1 = double(bigchumppre2_negclip(double(fTemp15)));
		fRec1[0] = ((int(signbit(double(fTemp15)))) ? fElse1 : fThen1) - fConst88 * (fConst90 * fRec1[1] + fConst91 * fRec1[2] + fConst92 * fRec1[3]);
		double fTemp16 = fConst4 * (fConst6 * fRec1[0] + fConst94 * fRec1[1] + fConst95 * fRec1[2] + fConst96 * fRec1[3]);
		double fThen2 = double(bigchumppowerclip(double(fTemp16)));
		double fElse2 = double(bigchumppower_negclip(double(fTemp16)));
		fRec19[0] = 0.0 - fConst19 * (fConst20 * fRec19[1] - (fTemp0 + fVec0[1]));
		fRec18[0] = fRec19[0] - fConst14 * (fConst21 * fRec18[2] + fConst22 * fRec18[1]);
		double fTemp17 = fRec18[2] + fRec18[0] + 2.0 * fRec18[1];
		fVec1[0] = fTemp17;
		fRec17[0] = fConst14 * (fConst98 * fTemp17 + fConst99 * fVec1[1]) - fConst100 * fRec17[1];
		fRec16[0] = fRec17[0] - fConst97 * (fConst101 * fRec16[2] + fConst32 * fRec16[1]);
		double fTemp18 = fConst41 * fRec15[1];
		fRec15[0] = fConst97 * (fConst31 * fRec16[0] + fConst102 * fRec16[1] + fConst31 * fRec16[2]) - fConst36 * (fConst38 * fRec15[2] + fTemp18);
		double fTemp19 = fConst50 * fRec14[1];
		fRec14[0] = (fRec15[2] + fConst36 * (fTemp18 + fConst38 * fRec15[0])) - fConst45 * (fConst47 * fRec14[2] + fTemp19);
		fRec13[0] = (fRec14[2] + fConst45 * (fTemp19 + fConst47 * fRec14[0])) - (fTemp4 * fRec13[1] + fTemp5 * fRec13[2] + fTemp6 * fRec13[3] + fTemp7 * fRec13[4]) / fTemp8;
		double fTemp20 = fRec3[0] * fTemp13;
		double fTemp21 = fConst0 * (fRec3[0] * (fRec13[0] * fTemp9 + fTemp10 * fRec13[1] + fConst0 * fTemp11 * fRec13[2]) + fTemp12 * fRec13[3] + fTemp20 * fRec13[4]) / fTemp8;
		double fThen3 = double(bigchumppreclip(double(fTemp21)));
		double fElse3 = double(bigchumppre_negclip(double(fTemp21)));
		fRec12[0] = ((int(signbit(double(fTemp21)))) ? fElse3 : fThen3) - fConst83 * (fConst84 * fRec12[1] + fConst85 * fRec12[2]);
		double fTemp22 = fConst9 * (fConst11 * fRec12[0] + fConst86 * fRec12[1] + fConst87 * fRec12[2]);
		double fThen4 = double(bigchumppre2clip(double(fTemp22)));
		double fElse4 = double(bigchumppre2_negclip(double(fTemp22)));
		fRec11[0] = ((int(signbit(double(fTemp22)))) ? fElse4 : fThen4) - fConst88 * (fConst90 * fRec11[1] + fConst91 * fRec11[2] + fConst92 * fRec11[3]);
		double fTemp23 = fConst4 * (fConst6 * fRec11[0] + fConst94 * fRec11[1] + fConst95 * fRec11[2] + fConst96 * fRec11[3]);
		double fThen5 = double(bigchumppowerclip(double(fTemp23)));
		double fElse5 = double(bigchumppower_negclip(double(fTemp23)));
		fRec27[0] = 0.0 - fConst105 * (fConst28 * fRec27[1] - fConst14 * (fTemp17 + fVec1[1]));
		fRec26[0] = fRec27[0] - fConst97 * (fConst101 * fRec26[2] + fConst32 * fRec26[1]);
		double fTemp24 = fRec26[2] + fRec26[0] + 2.0 * fRec26[1];
		fVec2[0] = fTemp24;
		fRec25[0] = fConst97 * (fConst104 * fTemp24 + fConst106 * fVec2[1]) - fConst107 * fRec25[1];
		fRec24[0] = fRec25[0] - fConst103 * (fConst108 * fRec24[2] + fConst41 * fRec24[1]);
		double fTemp25 = fConst50 * fRec23[1];
		fRec23[0] = fConst103 * (fConst40 * fRec24[0] + fConst109 * fRec24[1] + fConst40 * fRec24[2]) - fConst45 * (fConst47 * fRec23[2] + fTemp25);
		fRec22[0] = (fRec23[2] + fConst45 * (fTemp25 + fConst47 * fRec23[0])) - (fTemp4 * fRec22[1] + fTemp5 * fRec22[2] + fTemp6 * fRec22[3] + fTemp7 * fRec22[4]) / fTemp8;
		double fTemp26 = fConst0 * (fRec3[0] * (fRec22[0] * fTemp9 + fTemp10 * fRec22[1] + fConst0 * fTemp11 * fRec22[2]) + fTemp12 * fRec22[3] + fTemp20 * fRec22[4]) / fTemp8;
		double fThen6 = double(bigchumppreclip(double(fTemp26)));
		double fElse6 = double(bigchumppre_negclip(double(fTemp26)));
		fRec21[0] = ((int(signbit(double(fTemp26)))) ? fElse6 : fThen6) - fConst83 * (fConst84 * fRec21[1] + fConst85 * fRec21[2]);
		double fTemp27 = fConst9 * (fConst11 * fRec21[0] + fConst86 * fRec21[1] + fConst87 * fRec21[2]);
		double fThen7 = double(bigchumppre2clip(double(fTemp27)));
		double fElse7 = double(bigchumppre2_negclip(double(fTemp27)));
		fRec20[0] = ((int(signbit(double(fTemp27)))) ? fElse7 : fThen7) - fConst88 * (fConst90 * fRec20[1] + fConst91 * fRec20[2] + fConst92 * fRec20[3]);
		double fTemp28 = fConst4 * (fConst6 * fRec20[0] + fConst94 * fRec20[1] + fConst95 * fRec20[2] + fConst96 * fRec20[3]);
		double fThen8 = double(bigchumppowerclip(double(fTemp28)));
		double fElse8 = double(bigchumppower_negclip(double(fTemp28)));
		fRec34[0] = 0.0 - fConst112 * (fConst37 * fRec34[1] - fConst97 * (fTemp24 + fVec2[1]));
		fRec33[0] = fRec34[0] - fConst103 * (fConst108 * fRec33[2] + fConst41 * fRec33[1]);
		double fTemp29 = fRec33[2] + fRec33[0] + 2.0 * fRec33[1];
		fVec3[0] = fTemp29;
		fRec32[0] = fConst103 * (fConst111 * fTemp29 + fConst113 * fVec3[1]) - fConst114 * fRec32[1];
		fRec31[0] = fRec32[0] - fConst110 * (fConst115 * fRec31[2] + fConst50 * fRec31[1]);
		fRec30[0] = fConst110 * (fConst49 * fRec31[0] + fConst116 * fRec31[1] + fConst49 * fRec31[2]) - (fTemp4 * fRec30[1] + fTemp5 * fRec30[2] + fTemp6 * fRec30[3] + fTemp7 * fRec30[4]) / fTemp8;
		double fTemp30 = fConst0 * (fRec3[0] * (fRec30[0] * fTemp9 + fTemp10 * fRec30[1] + fConst0 * fTemp11 * fRec30[2]) + fTemp12 * fRec30[3] + fTemp20 * fRec30[4]) / fTemp8;
		double fThen9 = double(bigchumppreclip(double(fTemp30)));
		double fElse9 = double(bigchumppre_negclip(double(fTemp30)));
		fRec29[0] = ((int(signbit(double(fTemp30)))) ? fElse9 : fThen9) - fConst83 * (fConst84 * fRec29[1] + fConst85 * fRec29[2]);
		double fTemp31 = fConst9 * (fConst11 * fRec29[0] + fConst86 * fRec29[1] + fConst87 * fRec29[2]);
		double fThen10 = double(bigchumppre2clip(double(fTemp31)));
		double fElse10 = double(bigchumppre2_negclip(double(fTemp31)));
		fRec28[0] = ((int(signbit(double(fTemp31)))) ? fElse10 : fThen10) - fConst88 * (fConst90 * fRec28[1] + fConst91 * fRec28[2] + fConst92 * fRec28[3]);
		double fTemp32 = fConst4 * (fConst6 * fRec28[0] + fConst94 * fRec28[1] + fConst95 * fRec28[2] + fConst96 * fRec28[3]);
		double fThen11 = double(bigchumppowerclip(double(fTemp32)));
		double fElse11 = double(bigchumppower_negclip(double(fTemp32)));
		fRec39[0] = 0.0 - fConst117 * (fConst46 * fRec39[1] - fConst103 * (fTemp29 + fVec3[1]));
		fRec38[0] = fRec39[0] - fConst110 * (fConst115 * fRec38[2] + fConst50 * fRec38[1]);
		fRec37[0] = fConst110 * (fRec38[2] + fRec38[0] + 2.0 * fRec38[1]) - (fTemp4 * fRec37[1] + fTemp5 * fRec37[2] + fTemp6 * fRec37[3] + fTemp7 * fRec37[4]) / fTemp8;
		double fTemp33 = fConst0 * (fRec3[0] * (fRec37[0] * fTemp9 + fTemp10 * fRec37[1] + fConst0 * fTemp11 * fRec37[2]) + fTemp12 * fRec37[3] + fTemp20 * fRec37[4]) / fTemp8;
		double fThen12 = double(bigchumppreclip(double(fTemp33)));
		double fElse12 = double(bigchumppre_negclip(double(fTemp33)));
		fRec36[0] = ((int(signbit(double(fTemp33)))) ? fElse12 : fThen12) - fConst83 * (fConst84 * fRec36[1] + fConst85 * fRec36[2]);
		double fTemp34 = fConst9 * (fConst11 * fRec36[0] + fConst86 * fRec36[1] + fConst87 * fRec36[2]);
		double fThen13 = double(bigchumppre2clip(double(fTemp34)));
		double fElse13 = double(bigchumppre2_negclip(double(fTemp34)));
		fRec35[0] = ((int(signbit(double(fTemp34)))) ? fElse13 : fThen13) - fConst88 * (fConst90 * fRec35[1] + fConst91 * fRec35[2] + fConst92 * fRec35[3]);
		double fTemp35 = fConst4 * (fConst6 * fRec35[0] + fConst94 * fRec35[1] + fConst95 * fRec35[2] + fConst96 * fRec35[3]);
		double fThen14 = double(bigchumppowerclip(double(fTemp35)));
		double fElse14 = double(bigchumppower_negclip(double(fTemp35)));
		output0[i0] = FAUSTFLOAT(fRec0[0] * (((int(signbit(double(fTemp16)))) ? fElse2 : fThen2) + ((int(signbit(double(fTemp23)))) ? fElse5 : fThen5) + ((int(signbit(double(fTemp28)))) ? fElse8 : fThen8) + ((int(signbit(double(fTemp32)))) ? fElse11 : fThen11) + ((int(signbit(double(fTemp35)))) ? fElse14 : fThen14)));
		fRec0[1] = fRec0[0];
		fRec3[1] = fRec3[0];
		fVec0[1] = fVec0[0];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		for (int j0 = 4; j0 > 0; j0 = j0 - 1) {
			fRec4[j0] = fRec4[j0 - 1];
		}
		fRec10[1] = fRec10[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		for (int j1 = 3; j1 > 0; j1 = j1 - 1) {
			fRec1[j1] = fRec1[j1 - 1];
		}
		fRec19[1] = fRec19[0];
		fRec18[2] = fRec18[1];
		fRec18[1] = fRec18[0];
		fVec1[1] = fVec1[0];
		fRec17[1] = fRec17[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		for (int j2 = 4; j2 > 0; j2 = j2 - 1) {
			fRec13[j2] = fRec13[j2 - 1];
		}
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		for (int j3 = 3; j3 > 0; j3 = j3 - 1) {
			fRec11[j3] = fRec11[j3 - 1];
		}
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fVec2[1] = fVec2[0];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fRec23[2] = fRec23[1];
		fRec23[1] = fRec23[0];
		for (int j4 = 4; j4 > 0; j4 = j4 - 1) {
			fRec22[j4] = fRec22[j4 - 1];
		}
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		for (int j5 = 3; j5 > 0; j5 = j5 - 1) {
			fRec20[j5] = fRec20[j5 - 1];
		}
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fVec3[1] = fVec3[0];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		for (int j6 = 4; j6 > 0; j6 = j6 - 1) {
			fRec30[j6] = fRec30[j6 - 1];
		}
		fRec29[2] = fRec29[1];
		fRec29[1] = fRec29[0];
		for (int j7 = 3; j7 > 0; j7 = j7 - 1) {
			fRec28[j7] = fRec28[j7 - 1];
		}
		fRec39[1] = fRec39[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		for (int j8 = 4; j8 > 0; j8 = j8 - 1) {
			fRec37[j8] = fRec37[j8 - 1];
		}
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		for (int j9 = 3; j9 > 0; j9 = j9 - 1) {
			fRec35[j9] = fRec35[j9 - 1];
		}
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
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
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TONE: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   TONE, 
   VOLUME, 
} PortIndex;
*/

} // end namespace gx_bigchump
