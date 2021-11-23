// generated from file '../src/LV2/faust/gx_vibrochump.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "bigchumppower_neg_table.h"
#include "bigchumppower_table.h"
#include "bigchumppre2_neg_table.h"
#include "bigchumppre2_table.h"
#include "bigchumppre_neg_table.h"
#include "bigchumppre_table.h"
#include "math.h"

namespace gx_vibrochump {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	int iVec0[2];
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
	double fVec1[2];
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
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst83;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	double fConst84;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	int iRec13[2];
	int iRec12[2];
	double fConst85;
	double fRec16[2];
	double fRec15[2];
	double fRec14[2];
	double fRec11[2];
	double fConst86;
	double fConst87;
	double fConst88;
	double fRec2[3];
	double fConst89;
	double fConst90;
	double fConst91;
	double fConst93;
	double fConst94;
	double fConst95;
	double fRec1[4];
	double fConst97;
	double fConst98;
	double fConst99;
	double fConst100;
	double fConst101;
	double fRec25[2];
	double fRec24[3];
	double fVec2[2];
	double fConst102;
	double fConst103;
	double fRec23[2];
	double fConst104;
	double fRec22[3];
	double fConst105;
	double fRec21[3];
	double fRec20[3];
	double fRec19[5];
	double fRec18[3];
	double fRec17[4];
	double fConst106;
	double fConst107;
	double fConst108;
	double fRec33[2];
	double fRec32[3];
	double fVec3[2];
	double fConst109;
	double fConst110;
	double fRec31[2];
	double fConst111;
	double fRec30[3];
	double fConst112;
	double fRec29[3];
	double fRec28[5];
	double fRec27[3];
	double fRec26[4];
	double fConst113;
	double fConst114;
	double fConst115;
	double fRec40[2];
	double fRec39[3];
	double fVec4[2];
	double fConst116;
	double fConst117;
	double fRec38[2];
	double fConst118;
	double fRec37[3];
	double fConst119;
	double fRec36[5];
	double fRec35[3];
	double fRec34[4];
	double fConst120;
	double fRec45[2];
	double fRec44[3];
	double fRec43[5];
	double fRec42[3];
	double fRec41[4];

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
	id = "Redeye Vibro Chump";
	name = N_("Redeye Vibro Chumo");
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) iVec0[l0] = 0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec0[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec3[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fVec1[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec9[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec8[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec7[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRec6[l7] = 0.0;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec5[l8] = 0.0;
	for (int l9 = 0; (l9 < 5); l9 = (l9 + 1)) fRec4[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec10[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) iRec13[l11] = 0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) iRec12[l12] = 0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec16[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec15[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec14[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec11[l16] = 0.0;
	for (int l17 = 0; (l17 < 3); l17 = (l17 + 1)) fRec2[l17] = 0.0;
	for (int l18 = 0; (l18 < 4); l18 = (l18 + 1)) fRec1[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec25[l19] = 0.0;
	for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) fRec24[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fVec2[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fRec23[l22] = 0.0;
	for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) fRec22[l23] = 0.0;
	for (int l24 = 0; (l24 < 3); l24 = (l24 + 1)) fRec21[l24] = 0.0;
	for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) fRec20[l25] = 0.0;
	for (int l26 = 0; (l26 < 5); l26 = (l26 + 1)) fRec19[l26] = 0.0;
	for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) fRec18[l27] = 0.0;
	for (int l28 = 0; (l28 < 4); l28 = (l28 + 1)) fRec17[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fRec33[l29] = 0.0;
	for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) fRec32[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fVec3[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fRec31[l32] = 0.0;
	for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) fRec30[l33] = 0.0;
	for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) fRec29[l34] = 0.0;
	for (int l35 = 0; (l35 < 5); l35 = (l35 + 1)) fRec28[l35] = 0.0;
	for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) fRec27[l36] = 0.0;
	for (int l37 = 0; (l37 < 4); l37 = (l37 + 1)) fRec26[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fRec40[l38] = 0.0;
	for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) fRec39[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fVec4[l40] = 0.0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) fRec38[l41] = 0.0;
	for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) fRec37[l42] = 0.0;
	for (int l43 = 0; (l43 < 5); l43 = (l43 + 1)) fRec36[l43] = 0.0;
	for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) fRec35[l44] = 0.0;
	for (int l45 = 0; (l45 < 4); l45 = (l45 + 1)) fRec34[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec45[l46] = 0.0;
	for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) fRec44[l47] = 0.0;
	for (int l48 = 0; (l48 < 5); l48 = (l48 + 1)) fRec43[l48] = 0.0;
	for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) fRec42[l49] = 0.0;
	for (int l50 = 0; (l50 < 4); l50 = (l50 + 1)) fRec41[l50] = 0.0;
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
	double fConst2 = (8.9068910724842994e-15 * fConst0);
	double fConst3 = ((fConst0 * ((fConst0 * (fConst2 + 6.4917759212794798e-12)) + 2.5100665591164499e-10)) + 2.4697044736012902e-09);
	fConst4 = (fConst1 / fConst3);
	double fConst5 = (9.0138480164185596e-13 * fConst0);
	fConst6 = (fConst5 + 1.6298631366961702e-11);
	double fConst7 = (4.3359066716033201e-10 * fConst0);
	double fConst8 = ((fConst0 * (fConst7 + 2.0976223579538801e-08)) + 2.44130776766847e-07);
	fConst9 = (fConst0 / fConst8);
	double fConst10 = (2.5486049432641702e-08 * fConst0);
	fConst11 = (-3.39813992435224e-07 - fConst10);
	double fConst12 = std::tan((20517.741620594938 / fConst0));
	fConst13 = (1.0 / fConst12);
	fConst14 = (1.0 / (((fConst13 + 1.0000000000000004) / fConst12) + 1.0));
	double fConst15 = mydsp_faustpower2_f(fConst12);
	fConst16 = (1.0 / fConst15);
	double fConst17 = (fConst13 + 1.0);
	fConst18 = (0.0 - (1.0 / (fConst12 * fConst17)));
	fConst19 = (1.0 / fConst17);
	fConst20 = (1.0 - fConst13);
	fConst21 = (((fConst13 + -1.0000000000000004) / fConst12) + 1.0);
	fConst22 = (2.0 * (1.0 - fConst16));
	fConst23 = (0.0 - (2.0 / fConst15));
	double fConst24 = std::tan((3769.9111843077517 / fConst0));
	double fConst25 = (1.0 / fConst24);
	double fConst26 = (fConst25 + 1.0);
	fConst27 = (1.0 / ((fConst26 / fConst24) + 1.0));
	fConst28 = (1.0 - fConst25);
	fConst29 = (1.0 - (fConst28 / fConst24));
	double fConst30 = mydsp_faustpower2_f(fConst24);
	fConst31 = (1.0 / fConst30);
	fConst32 = (2.0 * (1.0 - fConst31));
	double fConst33 = std::tan((659.73445725385659 / fConst0));
	double fConst34 = (1.0 / fConst33);
	double fConst35 = (fConst34 + 1.0);
	fConst36 = (1.0 / ((fConst35 / fConst33) + 1.0));
	fConst37 = (1.0 - fConst34);
	fConst38 = (1.0 - (fConst37 / fConst33));
	double fConst39 = mydsp_faustpower2_f(fConst33);
	fConst40 = (1.0 / fConst39);
	fConst41 = (2.0 * (1.0 - fConst40));
	double fConst42 = std::tan((270.1769682087222 / fConst0));
	double fConst43 = (1.0 / fConst42);
	double fConst44 = (fConst43 + 1.0);
	fConst45 = (1.0 / ((fConst44 / fConst42) + 1.0));
	fConst46 = (1.0 - fConst43);
	fConst47 = (1.0 - (fConst46 / fConst42));
	double fConst48 = mydsp_faustpower2_f(fConst42);
	fConst49 = (1.0 / fConst48);
	fConst50 = (2.0 * (1.0 - fConst49));
	double fConst51 = (1.99975590383756e-19 * fConst0);
	fConst52 = ((fConst1 * (-6.0498368275157696e-16 - fConst51)) + 1.3013842919715099e-11);
	double fConst53 = (1.9997559038375601e-18 * fConst0);
	fConst54 = ((fConst1 * (-1.05044706792186e-15 - fConst53)) + 6.19273198244244e-13);
	double fConst55 = (1.9334301783374702e-18 * fConst0);
	fConst56 = (fConst1 * (fConst55 + 9.9148601709850608e-16));
	fConst57 = ((2.9996338557563498e-19 * fConst1) + -2.8037288490136399e-13);
	fConst58 = ((2.9996338557563499e-18 * fConst1) + -5.1188389201318301e-14);
	fConst59 = (2.4770927929769801e-14 - (2.9001452675062101e-18 * fConst1));
	fConst60 = ((fConst1 * (6.0498368275157696e-16 - fConst51)) + -1.3013842919715099e-11);
	fConst61 = ((fConst1 * (1.05044706792186e-15 - fConst53)) + -6.19273198244244e-13);
	fConst62 = (fConst1 * (fConst55 + -9.9148601709850608e-16));
	double fConst63 = (4.9993897595939102e-20 * fConst0);
	fConst64 = ((fConst0 * ((fConst0 * (fConst63 + -3.0249184137578799e-16)) + 1.4018644245068199e-13)) + -6.50692145985754e-12);
	double fConst65 = (4.9993897595939098e-19 * fConst0);
	fConst66 = ((fConst0 * ((fConst0 * (fConst65 + -5.2522353396092803e-16)) + 2.5594194600659201e-14)) + -3.09636599122122e-13);
	double fConst67 = (4.8335754458436803e-19 * fConst0);
	fConst68 = (fConst0 * ((fConst0 * (4.9574300854925304e-16 - fConst67)) + -1.23854639648849e-14));
	fConst69 = ((fConst0 * ((fConst0 * (fConst63 + 3.0249184137578799e-16)) + 1.4018644245068199e-13)) + 6.50692145985754e-12);
	fConst70 = ((fConst0 * ((fConst0 * (fConst65 + 5.2522353396092803e-16)) + 2.5594194600659201e-14)) + 3.09636599122122e-13);
	fConst71 = (fConst0 * ((fConst0 * (-4.9574300854925304e-16 - fConst67)) + -1.23854639648849e-14));
	double fConst72 = (2.8419671458380501e-18 * fConst0);
	fConst73 = ((fConst0 * ((fConst0 * (-2.8798600411158901e-15 - fConst72)) + -7.1428107598729697e-12)) + -9.4732238194602296e-11);
	double fConst74 = (1.42098357291903e-14 * fConst0);
	fConst75 = (fConst0 * (-1.89464476389205e-13 - fConst74));
	double fConst76 = (1.1367868583352201e-17 * fConst0);
	fConst77 = ((fConst1 * (fConst76 + 5.7597200822317897e-15)) + -1.8946447638920501e-10);
	fConst78 = (2.84196714583805e-14 * fConst1);
	fConst79 = (1.4285621519745901e-11 - (1.7051802875028302e-17 * fConst1));
	fConst80 = ((fConst1 * (fConst76 + -5.7597200822317897e-15)) + 1.8946447638920501e-10);
	fConst81 = ((fConst0 * ((fConst0 * (2.8798600411158901e-15 - fConst72)) + -7.1428107598729697e-12)) + 9.4732238194602296e-11);
	fConst82 = (fConst0 * (fConst74 + -1.89464476389205e-13));
	fConst83 = (1.0 / fConst0);
	fConst84 = (0.5 * fConst0);
	fConst85 = (6.2831853071795862 / fConst0);
	fConst86 = (1.0 / fConst8);
	fConst87 = (4.8826155353369304e-07 - (8.6718133432066401e-10 * fConst1));
	fConst88 = ((fConst0 * (fConst7 + -2.0976223579538801e-08)) + 2.44130776766847e-07);
	fConst89 = (5.0972098865283297e-08 * fConst0);
	fConst90 = (3.39813992435224e-07 - fConst10);
	fConst91 = (1.0 / fConst3);
	double fConst92 = (2.6720673217452901e-14 * fConst0);
	fConst93 = ((fConst0 * ((fConst0 * (-6.4917759212794798e-12 - fConst92)) + 2.5100665591164499e-10)) + 7.4091134208038597e-09);
	fConst94 = ((fConst0 * ((fConst0 * (fConst92 + -6.4917759212794798e-12)) + -2.5100665591164499e-10)) + 7.4091134208038597e-09);
	fConst95 = ((fConst0 * ((fConst0 * (6.4917759212794798e-12 - fConst2)) + -2.5100665591164499e-10)) + 2.4697044736012902e-09);
	double fConst96 = (2.7041544049255698e-12 * fConst0);
	fConst97 = (-1.6298631366961702e-11 - fConst96);
	fConst98 = (fConst96 + -1.6298631366961702e-11);
	fConst99 = (1.6298631366961702e-11 - fConst5);
	fConst100 = (1.0 / (((fConst25 + 1.0000000000000004) / fConst24) + 1.0));
	fConst101 = (1.0 / (fConst24 * fConst26));
	fConst102 = (0.0 - fConst101);
	fConst103 = (fConst28 / fConst26);
	fConst104 = (((fConst25 + -1.0000000000000004) / fConst24) + 1.0);
	fConst105 = (0.0 - (2.0 / fConst30));
	fConst106 = (1.0 / (((fConst34 + 1.0000000000000004) / fConst33) + 1.0));
	fConst107 = (1.0 / (fConst33 * fConst35));
	fConst108 = (1.0 / fConst26);
	fConst109 = (0.0 - fConst107);
	fConst110 = (fConst37 / fConst35);
	fConst111 = (((fConst34 + -1.0000000000000004) / fConst33) + 1.0);
	fConst112 = (0.0 - (2.0 / fConst39));
	fConst113 = (1.0 / (((fConst43 + 1.0000000000000004) / fConst42) + 1.0));
	fConst114 = (1.0 / (fConst42 * fConst44));
	fConst115 = (1.0 / fConst35);
	fConst116 = (0.0 - fConst114);
	fConst117 = (fConst46 / fConst44);
	fConst118 = (((fConst43 + -1.0000000000000004) / fConst42) + 1.0);
	fConst119 = (0.0 - (2.0 / fConst48));
	fConst120 = (1.0 / fConst44);
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
#define fCheckbox0 (*fCheckbox0_)
#define fVslider3 (*fVslider3_)
#define fCheckbox1 (*fCheckbox1_)
#define fVslider4 (*fVslider4_)
	double fSlow0 = (0.0010000000000000009 * double(fVslider0));
	double fSlow1 = (0.00036676987543879196 * (std::exp((3.0 * double(fVslider1))) + -1.0));
	double fSlow2 = (0.0070000000000000062 * double(fVslider2));
	int iSlow3 = int(double(fCheckbox0));
	double fSlow4 = (0.098039215686274522 * double(fVslider3));
	int iSlow5 = int(double(fCheckbox1));
	double fSlow6 = double(fVslider4);
	int iSlow7 = int((fConst84 / fSlow6));
	double fSlow8 = (1.0 / double(iSlow7));
	double fSlow9 = (fConst85 * fSlow6);
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		iVec0[0] = 1;
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec3[0] = (fSlow1 + (0.99299999999999999 * fRec3[1]));
		double fTemp0 = double(input0[i0]);
		fVec1[0] = fTemp0;
		fRec9[0] = ((fConst18 * fVec1[1]) - (fConst19 * ((fConst20 * fRec9[1]) - (fConst13 * fTemp0))));
		fRec8[0] = (fRec9[0] - (fConst14 * ((fConst21 * fRec8[2]) + (fConst22 * fRec8[1]))));
		double fTemp1 = (fConst32 * fRec7[1]);
		fRec7[0] = ((fConst14 * (((fConst16 * fRec8[0]) + (fConst23 * fRec8[1])) + (fConst16 * fRec8[2]))) - (fConst27 * ((fConst29 * fRec7[2]) + fTemp1)));
		double fTemp2 = (fConst41 * fRec6[1]);
		fRec6[0] = ((fRec7[2] + (fConst27 * (fTemp1 + (fConst29 * fRec7[0])))) - (fConst36 * ((fConst38 * fRec6[2]) + fTemp2)));
		double fTemp3 = (fConst50 * fRec5[1]);
		fRec5[0] = ((fRec6[2] + (fConst36 * (fTemp2 + (fConst38 * fRec6[0])))) - (fConst45 * ((fConst47 * fRec5[2]) + fTemp3)));
		double fTemp4 = ((fConst0 * (fConst52 + (fRec3[0] * (fConst54 + (fConst56 * fRec3[0]))))) + 3.0963659912212198e-10);
		double fTemp5 = ((fConst1 * (fConst57 + (fRec3[0] * (fConst58 + (fConst59 * fRec3[0]))))) + 4.64454898683183e-10);
		double fTemp6 = ((fConst0 * (fConst60 + (fRec3[0] * (fConst61 + (fConst62 * fRec3[0]))))) + 3.0963659912212198e-10);
		double fTemp7 = ((fConst0 * (fConst64 + (fRec3[0] * (fConst66 + (fConst68 * fRec3[0]))))) + 7.7409149780530496e-11);
		double fTemp8 = ((fConst0 * (fConst69 + (fRec3[0] * (fConst70 + (fConst71 * fRec3[0]))))) + 7.7409149780530496e-11);
		fRec4[0] = ((fRec5[2] + (fConst45 * (fTemp3 + (fConst47 * fRec5[0])))) - (((((fRec4[1] * fTemp4) + (fRec4[2] * fTemp5)) + (fRec4[3] * fTemp6)) + (fRec4[4] * fTemp7)) / fTemp8));
		fRec10[0] = (fSlow2 + (0.99299999999999999 * fRec10[1]));
		double fTemp9 = (fConst73 + (fConst75 * fRec10[0]));
		double fTemp10 = (fConst77 + (fConst78 * fRec10[0]));
		double fTemp11 = (fConst79 + (3.7892895277840898e-13 * fRec10[0]));
		double fTemp12 = ((fConst1 * (fRec10[0] * (0.0 - (2.84196714583805e-14 * fRec3[0])))) + (fConst80 * fRec3[0]));
		double fTemp13 = (fConst81 + (fConst82 * fRec10[0]));
		double fTemp14 = (fConst0 * ((((fRec3[0] * (((fRec4[0] * fTemp9) + (fRec4[1] * fTemp10)) + (fConst0 * (fRec4[2] * fTemp11)))) + (fRec4[3] * fTemp12)) + ((fRec3[0] * fRec4[4]) * fTemp13)) / fTemp8));
		double fTemp15 = (fRec11[1] * (1.0 - (fConst83 / (fConst83 + (0.059999999999999998 * std::exp((0.0 - (2.4849066497880004 * fRec11[1]))))))));
		iRec13[0] = ((iRec13[1] > 0) ? ((2 * (iRec12[1] < iSlow7)) + -1) : (1 - (2 * (iRec12[1] > 0))));
		iRec12[0] = (iRec13[0] + iRec12[1]);
		fRec16[0] = (fRec16[1] + (fSlow9 * (0.0 - fRec14[1])));
		fRec15[0] = ((fSlow9 * fRec16[0]) + (double((1 - iVec0[1])) + fRec15[1]));
		fRec14[0] = fRec15[0];
		fRec11[0] = (fTemp15 + (fConst83 * (std::pow(((fSlow4 * ((iSlow5 ? std::max<double>(0.0, (0.5 * (fRec14[0] + 1.0))) : (fSlow8 * double(iRec12[0]))) + -1.0)) + 1.0), 1.8999999999999999) / (fConst83 + (0.059999999999999998 * std::exp((0.0 - (2.4849066497880004 * fTemp15))))))));
		double fTemp16 = (iSlow3 ? 1.0 : (2700.0 / (std::exp((13.815510557964274 / std::log(((8.5519675079294171 * fRec11[0]) + 2.7182818284590451)))) + 2700.0)));
		fRec2[0] = (((int(signbit(double(fTemp14))) ? double(bigchumppre_negclip(double(fTemp14))) : double(bigchumppreclip(double(fTemp14)))) * fTemp16) - (fConst86 * ((fConst87 * fRec2[1]) + (fConst88 * fRec2[2]))));
		double fTemp17 = (fConst9 * (((fConst11 * fRec2[0]) + (fConst89 * fRec2[1])) + (fConst90 * fRec2[2])));
		fRec1[0] = ((int(signbit(double(fTemp17))) ? double(bigchumppre2_negclip(double(fTemp17))) : double(bigchumppre2clip(double(fTemp17)))) - (fConst91 * (((fConst93 * fRec1[1]) + (fConst94 * fRec1[2])) + (fConst95 * fRec1[3]))));
		double fTemp18 = (fConst4 * ((((fConst6 * fRec1[0]) + (fConst97 * fRec1[1])) + (fConst98 * fRec1[2])) + (fConst99 * fRec1[3])));
		fRec25[0] = (0.0 - (fConst19 * ((fConst20 * fRec25[1]) - (fTemp0 + fVec1[1]))));
		fRec24[0] = (fRec25[0] - (fConst14 * ((fConst21 * fRec24[2]) + (fConst22 * fRec24[1]))));
		double fTemp19 = (fRec24[2] + (fRec24[0] + (2.0 * fRec24[1])));
		fVec2[0] = fTemp19;
		fRec23[0] = ((fConst14 * ((fConst101 * fTemp19) + (fConst102 * fVec2[1]))) - (fConst103 * fRec23[1]));
		fRec22[0] = (fRec23[0] - (fConst100 * ((fConst104 * fRec22[2]) + (fConst32 * fRec22[1]))));
		double fTemp20 = (fConst41 * fRec21[1]);
		fRec21[0] = ((fConst100 * (((fConst31 * fRec22[0]) + (fConst105 * fRec22[1])) + (fConst31 * fRec22[2]))) - (fConst36 * ((fConst38 * fRec21[2]) + fTemp20)));
		double fTemp21 = (fConst50 * fRec20[1]);
		fRec20[0] = ((fRec21[2] + (fConst36 * (fTemp20 + (fConst38 * fRec21[0])))) - (fConst45 * ((fConst47 * fRec20[2]) + fTemp21)));
		fRec19[0] = ((fRec20[2] + (fConst45 * (fTemp21 + (fConst47 * fRec20[0])))) - (((((fTemp4 * fRec19[1]) + (fTemp5 * fRec19[2])) + (fTemp6 * fRec19[3])) + (fTemp7 * fRec19[4])) / fTemp8));
		double fTemp22 = (fRec3[0] * fTemp13);
		double fTemp23 = (fConst0 * ((((fRec3[0] * (((fRec19[0] * fTemp9) + (fTemp10 * fRec19[1])) + (fConst0 * (fTemp11 * fRec19[2])))) + (fTemp12 * fRec19[3])) + (fTemp22 * fRec19[4])) / fTemp8));
		fRec18[0] = ((fTemp16 * (int(signbit(double(fTemp23))) ? double(bigchumppre_negclip(double(fTemp23))) : double(bigchumppreclip(double(fTemp23))))) - (fConst86 * ((fConst87 * fRec18[1]) + (fConst88 * fRec18[2]))));
		double fTemp24 = (fConst9 * (((fConst11 * fRec18[0]) + (fConst89 * fRec18[1])) + (fConst90 * fRec18[2])));
		fRec17[0] = ((int(signbit(double(fTemp24))) ? double(bigchumppre2_negclip(double(fTemp24))) : double(bigchumppre2clip(double(fTemp24)))) - (fConst91 * (((fConst93 * fRec17[1]) + (fConst94 * fRec17[2])) + (fConst95 * fRec17[3]))));
		double fTemp25 = (fConst4 * ((((fConst6 * fRec17[0]) + (fConst97 * fRec17[1])) + (fConst98 * fRec17[2])) + (fConst99 * fRec17[3])));
		fRec33[0] = (0.0 - (fConst108 * ((fConst28 * fRec33[1]) - (fConst14 * (fTemp19 + fVec2[1])))));
		fRec32[0] = (fRec33[0] - (fConst100 * ((fConst104 * fRec32[2]) + (fConst32 * fRec32[1]))));
		double fTemp26 = (fRec32[2] + (fRec32[0] + (2.0 * fRec32[1])));
		fVec3[0] = fTemp26;
		fRec31[0] = ((fConst100 * ((fConst107 * fTemp26) + (fConst109 * fVec3[1]))) - (fConst110 * fRec31[1]));
		fRec30[0] = (fRec31[0] - (fConst106 * ((fConst111 * fRec30[2]) + (fConst41 * fRec30[1]))));
		double fTemp27 = (fConst50 * fRec29[1]);
		fRec29[0] = ((fConst106 * (((fConst40 * fRec30[0]) + (fConst112 * fRec30[1])) + (fConst40 * fRec30[2]))) - (fConst45 * ((fConst47 * fRec29[2]) + fTemp27)));
		fRec28[0] = ((fRec29[2] + (fConst45 * (fTemp27 + (fConst47 * fRec29[0])))) - (((((fTemp4 * fRec28[1]) + (fTemp5 * fRec28[2])) + (fTemp6 * fRec28[3])) + (fTemp7 * fRec28[4])) / fTemp8));
		double fTemp28 = (fConst0 * ((((fRec3[0] * (((fRec28[0] * fTemp9) + (fTemp10 * fRec28[1])) + (fConst0 * (fTemp11 * fRec28[2])))) + (fTemp12 * fRec28[3])) + (fTemp22 * fRec28[4])) / fTemp8));
		fRec27[0] = ((fTemp16 * (int(signbit(double(fTemp28))) ? double(bigchumppre_negclip(double(fTemp28))) : double(bigchumppreclip(double(fTemp28))))) - (fConst86 * ((fConst87 * fRec27[1]) + (fConst88 * fRec27[2]))));
		double fTemp29 = (fConst9 * (((fConst11 * fRec27[0]) + (fConst89 * fRec27[1])) + (fConst90 * fRec27[2])));
		fRec26[0] = ((int(signbit(double(fTemp29))) ? double(bigchumppre2_negclip(double(fTemp29))) : double(bigchumppre2clip(double(fTemp29)))) - (fConst91 * (((fConst93 * fRec26[1]) + (fConst94 * fRec26[2])) + (fConst95 * fRec26[3]))));
		double fTemp30 = (fConst4 * ((((fConst6 * fRec26[0]) + (fConst97 * fRec26[1])) + (fConst98 * fRec26[2])) + (fConst99 * fRec26[3])));
		fRec40[0] = (0.0 - (fConst115 * ((fConst37 * fRec40[1]) - (fConst100 * (fTemp26 + fVec3[1])))));
		fRec39[0] = (fRec40[0] - (fConst106 * ((fConst111 * fRec39[2]) + (fConst41 * fRec39[1]))));
		double fTemp31 = (fRec39[2] + (fRec39[0] + (2.0 * fRec39[1])));
		fVec4[0] = fTemp31;
		fRec38[0] = ((fConst106 * ((fConst114 * fTemp31) + (fConst116 * fVec4[1]))) - (fConst117 * fRec38[1]));
		fRec37[0] = (fRec38[0] - (fConst113 * ((fConst118 * fRec37[2]) + (fConst50 * fRec37[1]))));
		fRec36[0] = ((fConst113 * (((fConst49 * fRec37[0]) + (fConst119 * fRec37[1])) + (fConst49 * fRec37[2]))) - (((((fTemp4 * fRec36[1]) + (fTemp5 * fRec36[2])) + (fTemp6 * fRec36[3])) + (fTemp7 * fRec36[4])) / fTemp8));
		double fTemp32 = (fConst0 * ((((fRec3[0] * (((fRec36[0] * fTemp9) + (fTemp10 * fRec36[1])) + (fConst0 * (fTemp11 * fRec36[2])))) + (fTemp12 * fRec36[3])) + (fTemp22 * fRec36[4])) / fTemp8));
		fRec35[0] = ((fTemp16 * (int(signbit(double(fTemp32))) ? double(bigchumppre_negclip(double(fTemp32))) : double(bigchumppreclip(double(fTemp32))))) - (fConst86 * ((fConst87 * fRec35[1]) + (fConst88 * fRec35[2]))));
		double fTemp33 = (fConst9 * (((fConst11 * fRec35[0]) + (fConst89 * fRec35[1])) + (fConst90 * fRec35[2])));
		fRec34[0] = ((int(signbit(double(fTemp33))) ? double(bigchumppre2_negclip(double(fTemp33))) : double(bigchumppre2clip(double(fTemp33)))) - (fConst91 * (((fConst93 * fRec34[1]) + (fConst94 * fRec34[2])) + (fConst95 * fRec34[3]))));
		double fTemp34 = (fConst4 * ((((fConst6 * fRec34[0]) + (fConst97 * fRec34[1])) + (fConst98 * fRec34[2])) + (fConst99 * fRec34[3])));
		fRec45[0] = (0.0 - (fConst120 * ((fConst46 * fRec45[1]) - (fConst106 * (fTemp31 + fVec4[1])))));
		fRec44[0] = (fRec45[0] - (fConst113 * ((fConst118 * fRec44[2]) + (fConst50 * fRec44[1]))));
		fRec43[0] = ((fConst113 * (fRec44[2] + (fRec44[0] + (2.0 * fRec44[1])))) - (((((fTemp4 * fRec43[1]) + (fTemp5 * fRec43[2])) + (fTemp6 * fRec43[3])) + (fTemp7 * fRec43[4])) / fTemp8));
		double fTemp35 = (fConst0 * ((((fRec3[0] * (((fRec43[0] * fTemp9) + (fTemp10 * fRec43[1])) + (fConst0 * (fTemp11 * fRec43[2])))) + (fTemp12 * fRec43[3])) + (fTemp22 * fRec43[4])) / fTemp8));
		fRec42[0] = ((fTemp16 * (int(signbit(double(fTemp35))) ? double(bigchumppre_negclip(double(fTemp35))) : double(bigchumppreclip(double(fTemp35))))) - (fConst86 * ((fConst87 * fRec42[1]) + (fConst88 * fRec42[2]))));
		double fTemp36 = (fConst9 * (((fConst11 * fRec42[0]) + (fConst89 * fRec42[1])) + (fConst90 * fRec42[2])));
		fRec41[0] = ((int(signbit(double(fTemp36))) ? double(bigchumppre2_negclip(double(fTemp36))) : double(bigchumppre2clip(double(fTemp36)))) - (fConst91 * (((fConst93 * fRec41[1]) + (fConst94 * fRec41[2])) + (fConst95 * fRec41[3]))));
		double fTemp37 = (fConst4 * ((((fConst6 * fRec41[0]) + (fConst97 * fRec41[1])) + (fConst98 * fRec41[2])) + (fConst99 * fRec41[3])));
		output0[i0] = FAUSTFLOAT((fRec0[0] * (((((int(signbit(double(fTemp18))) ? double(bigchumppower_negclip(double(fTemp18))) : double(bigchumppowerclip(double(fTemp18)))) + (int(signbit(double(fTemp25))) ? double(bigchumppower_negclip(double(fTemp25))) : double(bigchumppowerclip(double(fTemp25))))) + (int(signbit(double(fTemp30))) ? double(bigchumppower_negclip(double(fTemp30))) : double(bigchumppowerclip(double(fTemp30))))) + (int(signbit(double(fTemp34))) ? double(bigchumppower_negclip(double(fTemp34))) : double(bigchumppowerclip(double(fTemp34))))) + (int(signbit(double(fTemp37))) ? double(bigchumppower_negclip(double(fTemp37))) : double(bigchumppowerclip(double(fTemp37)))))));
		iVec0[1] = iVec0[0];
		fRec0[1] = fRec0[0];
		fRec3[1] = fRec3[0];
		fVec1[1] = fVec1[0];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		for (int j0 = 4; (j0 > 0); j0 = (j0 - 1)) {
			fRec4[j0] = fRec4[(j0 - 1)];
		}
		fRec10[1] = fRec10[0];
		iRec13[1] = iRec13[0];
		iRec12[1] = iRec12[0];
		fRec16[1] = fRec16[0];
		fRec15[1] = fRec15[0];
		fRec14[1] = fRec14[0];
		fRec11[1] = fRec11[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
			fRec1[j1] = fRec1[(j1 - 1)];
		}
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fVec2[1] = fVec2[0];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		for (int j2 = 4; (j2 > 0); j2 = (j2 - 1)) {
			fRec19[j2] = fRec19[(j2 - 1)];
		}
		fRec18[2] = fRec18[1];
		fRec18[1] = fRec18[0];
		for (int j3 = 3; (j3 > 0); j3 = (j3 - 1)) {
			fRec17[j3] = fRec17[(j3 - 1)];
		}
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fVec3[1] = fVec3[0];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fRec29[2] = fRec29[1];
		fRec29[1] = fRec29[0];
		for (int j4 = 4; (j4 > 0); j4 = (j4 - 1)) {
			fRec28[j4] = fRec28[(j4 - 1)];
		}
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		for (int j5 = 3; (j5 > 0); j5 = (j5 - 1)) {
			fRec26[j5] = fRec26[(j5 - 1)];
		}
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fVec4[1] = fVec4[0];
		fRec38[1] = fRec38[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		for (int j6 = 4; (j6 > 0); j6 = (j6 - 1)) {
			fRec36[j6] = fRec36[(j6 - 1)];
		}
		fRec35[2] = fRec35[1];
		fRec35[1] = fRec35[0];
		for (int j7 = 3; (j7 > 0); j7 = (j7 - 1)) {
			fRec34[j7] = fRec34[(j7 - 1)];
		}
		fRec45[1] = fRec45[0];
		fRec44[2] = fRec44[1];
		fRec44[1] = fRec44[0];
		for (int j8 = 4; (j8 > 0); j8 = (j8 - 1)) {
			fRec43[j8] = fRec43[(j8 - 1)];
		}
		fRec42[2] = fRec42[1];
		fRec42[1] = fRec42[0];
		for (int j9 = 3; (j9 > 0); j9 = (j9 - 1)) {
			fRec41[j9] = fRec41[(j9 - 1)];
		}
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
#undef fCheckbox0
#undef fVslider3
#undef fCheckbox1
#undef fVslider4
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case VOLUME: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case GAIN: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TONE: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	// static const value_pair fCheckbox1_values[] = {{"os.triangle"},{"sine"},{0}};
	case SINEWAVE: 
		fCheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case INTENSITY: 
		fVslider3_ = (float*)data; // , 5.0, 0.0, 10.0, 0.10000000000000001 
		break;
	case SPEED: 
		fVslider4_ = (float*)data; // , 5.0, 0.10000000000000001, 10.0, 0.10000000000000001 
		break;
	// static const value_pair fCheckbox0_values[] = {{"Off"},{"On"},{0}};
	case VIBE: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
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
   VOLUME, 
   GAIN, 
   TONE, 
   SINEWAVE, 
   INTENSITY, 
   SPEED, 
   VIBE, 
} PortIndex;
*/

} // end namespace gx_vibrochump
