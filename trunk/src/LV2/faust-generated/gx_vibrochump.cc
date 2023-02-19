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
	double fConst2;
	double fConst4;
	int iVec0[2];
	double fConst5;
	double fConst7;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec2[2];
	double fConst14;
	double fConst16;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst23;
	double fConst24;
	double fConst26;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst37;
	double fConst38;
	double fConst40;
	double fConst41;
	double fConst44;
	double fConst45;
	double fConst47;
	double fConst48;
	double fConst51;
	double fConst52;
	double fConst54;
	double fConst55;
	double fConst58;
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;
	double fVec1[2];
	double fConst63;
	double fConst65;
	double fRec11[2];
	double fRec10[3];
	double fVec2[2];
	double fConst66;
	double fConst68;
	double fRec9[2];
	double fRec8[3];
	double fVec3[2];
	double fConst69;
	double fConst71;
	double fRec7[2];
	double fRec6[3];
	double fVec4[2];
	double fConst72;
	double fConst74;
	double fRec5[2];
	double fRec4[3];
	double fRec3[5];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec12[2];
	double fConst76;
	double fConst78;
	double fConst80;
	double fConst81;
	double fConst82;
	double fConst83;
	double fConst84;
	double fConst85;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst86;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fConst87;
	int iRec15[2];
	int iRec14[2];
	double fConst88;
	double fRec18[2];
	double fRec17[2];
	double fRec16[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec13[2];
	double fRec1[3];
	double fConst90;
	double fConst91;
	double fConst92;
	double fRec0[4];
	double fConst94;
	double fConst96;
	double fConst97;
	double fConst98;
	double fConst99;
	double fConst100;
	double fConst101;
	double fConst102;
	double fRec23[2];
	double fRec22[3];
	double fConst103;
	double fRec21[5];
	double fRec20[3];
	double fRec19[4];
	double fConst104;
	double fConst105;
	double fConst106;
	double fConst107;
	double fConst108;
	double fRec29[2];
	double fRec28[3];
	double fConst109;
	double fRec27[3];
	double fRec26[5];
	double fRec25[3];
	double fRec24[4];
	double fConst110;
	double fConst111;
	double fConst112;
	double fConst113;
	double fConst114;
	double fRec36[2];
	double fRec35[3];
	double fConst115;
	double fRec34[3];
	double fRec33[3];
	double fRec32[5];
	double fRec31[3];
	double fRec30[4];
	double fConst116;
	double fConst117;
	double fConst118;
	double fRec44[2];
	double fRec43[3];
	double fConst119;
	double fRec42[3];
	double fRec41[3];
	double fRec40[3];
	double fRec39[5];
	double fRec38[3];
	double fRec37[4];
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	double fRec45[2];

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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) iVec0[l0] = 0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec2[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fVec1[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec11[l3] = 0.0;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRec10[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fVec2[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec9[l6] = 0.0;
	for (int l7 = 0; l7 < 3; l7 = l7 + 1) fRec8[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fVec3[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec7[l9] = 0.0;
	for (int l10 = 0; l10 < 3; l10 = l10 + 1) fRec6[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fVec4[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec5[l12] = 0.0;
	for (int l13 = 0; l13 < 3; l13 = l13 + 1) fRec4[l13] = 0.0;
	for (int l14 = 0; l14 < 5; l14 = l14 + 1) fRec3[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec12[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) iRec15[l16] = 0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) iRec14[l17] = 0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec18[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec17[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec16[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec13[l21] = 0.0;
	for (int l22 = 0; l22 < 3; l22 = l22 + 1) fRec1[l22] = 0.0;
	for (int l23 = 0; l23 < 4; l23 = l23 + 1) fRec0[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec23[l24] = 0.0;
	for (int l25 = 0; l25 < 3; l25 = l25 + 1) fRec22[l25] = 0.0;
	for (int l26 = 0; l26 < 5; l26 = l26 + 1) fRec21[l26] = 0.0;
	for (int l27 = 0; l27 < 3; l27 = l27 + 1) fRec20[l27] = 0.0;
	for (int l28 = 0; l28 < 4; l28 = l28 + 1) fRec19[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec29[l29] = 0.0;
	for (int l30 = 0; l30 < 3; l30 = l30 + 1) fRec28[l30] = 0.0;
	for (int l31 = 0; l31 < 3; l31 = l31 + 1) fRec27[l31] = 0.0;
	for (int l32 = 0; l32 < 5; l32 = l32 + 1) fRec26[l32] = 0.0;
	for (int l33 = 0; l33 < 3; l33 = l33 + 1) fRec25[l33] = 0.0;
	for (int l34 = 0; l34 < 4; l34 = l34 + 1) fRec24[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec36[l35] = 0.0;
	for (int l36 = 0; l36 < 3; l36 = l36 + 1) fRec35[l36] = 0.0;
	for (int l37 = 0; l37 < 3; l37 = l37 + 1) fRec34[l37] = 0.0;
	for (int l38 = 0; l38 < 3; l38 = l38 + 1) fRec33[l38] = 0.0;
	for (int l39 = 0; l39 < 5; l39 = l39 + 1) fRec32[l39] = 0.0;
	for (int l40 = 0; l40 < 3; l40 = l40 + 1) fRec31[l40] = 0.0;
	for (int l41 = 0; l41 < 4; l41 = l41 + 1) fRec30[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) fRec44[l42] = 0.0;
	for (int l43 = 0; l43 < 3; l43 = l43 + 1) fRec43[l43] = 0.0;
	for (int l44 = 0; l44 < 3; l44 = l44 + 1) fRec42[l44] = 0.0;
	for (int l45 = 0; l45 < 3; l45 = l45 + 1) fRec41[l45] = 0.0;
	for (int l46 = 0; l46 < 3; l46 = l46 + 1) fRec40[l46] = 0.0;
	for (int l47 = 0; l47 < 5; l47 = l47 + 1) fRec39[l47] = 0.0;
	for (int l48 = 0; l48 < 3; l48 = l48 + 1) fRec38[l48] = 0.0;
	for (int l49 = 0; l49 < 4; l49 = l49 + 1) fRec37[l49] = 0.0;
	for (int l50 = 0; l50 < 2; l50 = l50 + 1) fRec45[l50] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 8.9068910724843e-15 * fConst0;
	fConst2 = fConst0 * (fConst0 * (6.49177592127948e-12 - fConst1) + -2.51006655911645e-10) + 2.46970447360129e-09;
	double fConst3 = 2.67206732174529e-14 * fConst0;
	fConst4 = fConst0 * (fConst0 * (fConst3 + -6.49177592127948e-12) + -2.51006655911645e-10) + 7.40911342080386e-09;
	fConst5 = fConst0 * (fConst0 * (-6.49177592127948e-12 - fConst3) + 2.51006655911645e-10) + 7.40911342080386e-09;
	double fConst6 = fConst0 * (fConst0 * (fConst1 + 6.49177592127948e-12) + 2.51006655911645e-10) + 2.46970447360129e-09;
	fConst7 = 1.0 / fConst6;
	double fConst8 = 4.33590667160332e-10 * fConst0;
	fConst9 = fConst0 * (fConst8 + -2.09762235795388e-08) + 2.44130776766847e-07;
	fConst10 = mydsp_faustpower2_f(fConst0);
	fConst11 = 4.88261553533693e-07 - 8.67181334320664e-10 * fConst10;
	fConst12 = 1.0 / (fConst0 * (fConst8 + 2.09762235795388e-08) + 2.44130776766847e-07);
	double fConst13 = 4.83357544584368e-19 * fConst0;
	fConst14 = fConst10 * (fConst0 * (-4.95743008549253e-16 - fConst13) + -1.23854639648849e-14);
	double fConst15 = 4.99938975959391e-19 * fConst0;
	fConst16 = fConst0 * (fConst0 * (fConst0 * (fConst15 + 5.25223533960928e-16) + 2.55941946006592e-14) + 3.09636599122122e-13);
	double fConst17 = 4.99938975959391e-20 * fConst0;
	fConst18 = fConst0 * (fConst0 * (fConst0 * (fConst17 + 3.02491841375788e-16) + 1.40186442450682e-13) + 6.50692145985754e-12);
	fConst19 = fConst10 * (fConst0 * (4.95743008549253e-16 - fConst13) + -1.23854639648849e-14);
	fConst20 = fConst0 * (fConst0 * (fConst0 * (fConst15 + -5.25223533960928e-16) + 2.55941946006592e-14) + -3.09636599122122e-13);
	fConst21 = fConst0 * (fConst0 * (fConst0 * (fConst17 + -3.02491841375788e-16) + 1.40186442450682e-13) + -6.50692145985754e-12);
	double fConst22 = 1.93343017833747e-18 * fConst0;
	fConst23 = mydsp_faustpower3_f(fConst0);
	fConst24 = fConst23 * (fConst22 + -9.91486017098506e-16);
	double fConst25 = 1.99975590383756e-18 * fConst0;
	fConst26 = fConst0 * (fConst10 * (1.05044706792186e-15 - fConst25) + -6.19273198244244e-13);
	double fConst27 = 1.99975590383756e-19 * fConst0;
	fConst28 = fConst0 * (fConst10 * (6.04983682751577e-16 - fConst27) + -1.30138429197151e-11);
	fConst29 = 2.47709279297698e-14 - 2.90014526750621e-18 * fConst10;
	fConst30 = 2.99963385575635e-18 * fConst10 + -5.11883892013183e-14;
	fConst31 = 2.99963385575635e-19 * fConst10 + -2.80372884901364e-13;
	fConst32 = fConst23 * (fConst22 + 9.91486017098506e-16);
	fConst33 = fConst0 * (fConst10 * (-1.05044706792186e-15 - fConst25) + 6.19273198244244e-13);
	fConst34 = fConst0 * (fConst10 * (-6.04983682751577e-16 - fConst27) + 1.30138429197151e-11);
	double fConst35 = std::tan(270.1769682087222 / fConst0);
	double fConst36 = mydsp_faustpower2_f(fConst35);
	fConst37 = 1.0 / fConst36;
	fConst38 = 2.0 * (1.0 - fConst37);
	double fConst39 = 1.0 / fConst35;
	fConst40 = (fConst39 + -1.0000000000000004) / fConst35 + 1.0;
	fConst41 = 1.0 / ((fConst39 + 1.0000000000000004) / fConst35 + 1.0);
	double fConst42 = std::tan(659.7344572538566 / fConst0);
	double fConst43 = mydsp_faustpower2_f(fConst42);
	fConst44 = 1.0 / fConst43;
	fConst45 = 2.0 * (1.0 - fConst44);
	double fConst46 = 1.0 / fConst42;
	fConst47 = (fConst46 + -1.0000000000000004) / fConst42 + 1.0;
	fConst48 = 1.0 / ((fConst46 + 1.0000000000000004) / fConst42 + 1.0);
	double fConst49 = std::tan(3769.9111843077517 / fConst0);
	double fConst50 = mydsp_faustpower2_f(fConst49);
	fConst51 = 1.0 / fConst50;
	fConst52 = 2.0 * (1.0 - fConst51);
	double fConst53 = 1.0 / fConst49;
	fConst54 = (fConst53 + -1.0000000000000004) / fConst49 + 1.0;
	fConst55 = 1.0 / ((fConst53 + 1.0000000000000004) / fConst49 + 1.0);
	double fConst56 = std::tan(20517.741620594938 / fConst0);
	double fConst57 = mydsp_faustpower2_f(fConst56);
	fConst58 = 1.0 / fConst57;
	fConst59 = 2.0 * (1.0 - fConst58);
	fConst60 = 1.0 / fConst56;
	fConst61 = (fConst60 + -1.0000000000000004) / fConst56 + 1.0;
	fConst62 = 1.0 / ((fConst60 + 1.0000000000000004) / fConst56 + 1.0);
	fConst63 = 1.0 - fConst60;
	double fConst64 = fConst60 + 1.0;
	fConst65 = 1.0 / fConst64;
	fConst66 = 1.0 - fConst53;
	double fConst67 = fConst53 + 1.0;
	fConst68 = 1.0 / fConst67;
	fConst69 = 1.0 - fConst46;
	double fConst70 = fConst46 + 1.0;
	fConst71 = 1.0 / fConst70;
	fConst72 = 1.0 - fConst39;
	double fConst73 = fConst39 + 1.0;
	fConst74 = 1.0 / fConst73;
	double fConst75 = 1.42098357291903e-14 * fConst0;
	fConst76 = fConst10 * (fConst75 + -1.89464476389205e-13);
	double fConst77 = 2.84196714583805e-18 * fConst0;
	fConst78 = fConst0 * (fConst0 * (fConst0 * (2.87986004111589e-15 - fConst77) + -7.14281075987297e-12) + 9.47322381946023e-11);
	double fConst79 = 1.13678685833522e-17 * fConst0;
	fConst80 = fConst0 * (fConst10 * (fConst79 + -5.75972008223179e-15) + 1.89464476389205e-10);
	fConst81 = 1.42856215197459e-11 - 1.70518028750283e-17 * fConst10;
	fConst82 = 2.84196714583805e-14 * fConst23;
	fConst83 = fConst0 * (fConst10 * (fConst79 + 5.75972008223179e-15) + -1.89464476389205e-10);
	fConst84 = fConst10 * (-1.89464476389205e-13 - fConst75);
	fConst85 = fConst0 * (fConst0 * (fConst0 * (-2.87986004111589e-15 - fConst77) + -7.14281075987297e-12) + -9.47322381946023e-11);
	fConst86 = 1.0 / fConst0;
	fConst87 = 0.5 * fConst0;
	fConst88 = 6.283185307179586 / fConst0;
	double fConst89 = 2.54860494326417e-08 * fConst0;
	fConst90 = fConst0 * (3.39813992435224e-07 - fConst89);
	fConst91 = 5.09720988652833e-08 * fConst10;
	fConst92 = fConst0 * (-3.39813992435224e-07 - fConst89);
	double fConst93 = 9.01384801641856e-13 * fConst0;
	fConst94 = 1.62986313669617e-11 - fConst93;
	double fConst95 = 2.70415440492557e-12 * fConst0;
	fConst96 = fConst95 + -1.62986313669617e-11;
	fConst97 = -1.62986313669617e-11 - fConst95;
	fConst98 = fConst93 + 1.62986313669617e-11;
	fConst99 = fConst10 / fConst6;
	fConst100 = fConst72 / fConst73;
	fConst101 = 1.0 / (fConst35 * fConst73);
	fConst102 = 0.0 - fConst101;
	fConst103 = 0.0 - 2.0 / fConst36;
	fConst104 = 1.0 - fConst72 / fConst35;
	fConst105 = 1.0 / (fConst73 / fConst35 + 1.0);
	fConst106 = fConst69 / fConst70;
	fConst107 = 1.0 / (fConst42 * fConst70);
	fConst108 = 0.0 - fConst107;
	fConst109 = 0.0 - 2.0 / fConst43;
	fConst110 = 1.0 - fConst69 / fConst42;
	fConst111 = 1.0 / (fConst70 / fConst42 + 1.0);
	fConst112 = fConst66 / fConst67;
	fConst113 = 1.0 / (fConst49 * fConst67);
	fConst114 = 0.0 - fConst113;
	fConst115 = 0.0 - 2.0 / fConst50;
	fConst116 = 1.0 - fConst66 / fConst49;
	fConst117 = 1.0 / (fConst67 / fConst49 + 1.0);
	fConst118 = 0.0 - 1.0 / (fConst56 * fConst64);
	fConst119 = 0.0 - 2.0 / fConst57;
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
#define fCheckbox0 (*fCheckbox0_)
#define fCheckbox1 (*fCheckbox1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
#define fVslider4 (*fVslider4_)
	double fSlow0 = 0.00036676987543879196 * (std::exp(3.0 * double(fVslider0)) + -1.0);
	double fSlow1 = 0.007000000000000006 * double(fVslider1);
	int iSlow2 = int(double(fCheckbox0));
	int iSlow3 = int(double(fCheckbox1));
	double fSlow4 = double(fVslider2);
	int iSlow5 = int(fConst87 / fSlow4);
	double fSlow6 = 1.0 / double(iSlow5);
	double fSlow7 = fConst88 * fSlow4;
	double fSlow8 = 0.09803921568627452 * double(fVslider3);
	double fSlow9 = 0.0010000000000000009 * double(fVslider4);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		iVec0[0] = 1;
		fRec2[0] = fSlow0 + 0.993 * fRec2[1];
		double fTemp0 = fConst18 + fRec2[0] * (fConst16 + fConst14 * fRec2[0]) + 7.74091497805305e-11;
		double fTemp1 = fConst21 + fRec2[0] * (fConst20 + fConst19 * fRec2[0]) + 7.74091497805305e-11;
		double fTemp2 = fConst28 + fRec2[0] * (fConst26 + fConst24 * fRec2[0]) + 3.09636599122122e-10;
		double fTemp3 = fConst10 * (fConst31 + fRec2[0] * (fConst30 + fConst29 * fRec2[0])) + 4.64454898683183e-10;
		double fTemp4 = fConst34 + fRec2[0] * (fConst33 + fConst32 * fRec2[0]) + 3.09636599122122e-10;
		double fTemp5 = double(input0[i0]);
		fVec1[0] = fTemp5;
		fRec11[0] = 0.0 - fConst65 * (fConst63 * fRec11[1] - (fTemp5 + fVec1[1]));
		fRec10[0] = fRec11[0] - fConst62 * (fConst61 * fRec10[2] + fConst59 * fRec10[1]);
		double fTemp6 = fRec10[2] + fRec10[0] + 2.0 * fRec10[1];
		fVec2[0] = fTemp6;
		fRec9[0] = 0.0 - fConst68 * (fConst66 * fRec9[1] - fConst62 * (fTemp6 + fVec2[1]));
		fRec8[0] = fRec9[0] - fConst55 * (fConst54 * fRec8[2] + fConst52 * fRec8[1]);
		double fTemp7 = fRec8[2] + fRec8[0] + 2.0 * fRec8[1];
		fVec3[0] = fTemp7;
		fRec7[0] = 0.0 - fConst71 * (fConst69 * fRec7[1] - fConst55 * (fTemp7 + fVec3[1]));
		fRec6[0] = fRec7[0] - fConst48 * (fConst47 * fRec6[2] + fConst45 * fRec6[1]);
		double fTemp8 = fRec6[2] + fRec6[0] + 2.0 * fRec6[1];
		fVec4[0] = fTemp8;
		fRec5[0] = 0.0 - fConst74 * (fConst72 * fRec5[1] - fConst48 * (fTemp8 + fVec4[1]));
		fRec4[0] = fRec5[0] - fConst41 * (fConst40 * fRec4[2] + fConst38 * fRec4[1]);
		fRec3[0] = fConst41 * (fRec4[2] + fRec4[0] + 2.0 * fRec4[1]) - (fTemp4 * fRec3[1] + fTemp3 * fRec3[2] + fTemp2 * fRec3[3] + fTemp1 * fRec3[4]) / fTemp0;
		fRec12[0] = fSlow1 + 0.993 * fRec12[1];
		double fTemp9 = fConst78 + fConst76 * fRec12[0];
		double fTemp10 = fRec2[0] * fTemp9;
		double fTemp11 = fConst23 * fRec12[0] * (0.0 - 2.84196714583805e-14 * fRec2[0]) + fConst80 * fRec2[0];
		double fTemp12 = fConst81 + 3.78928952778409e-13 * fRec12[0];
		double fTemp13 = fConst83 + fConst82 * fRec12[0];
		double fTemp14 = fConst85 + fConst84 * fRec12[0];
		double fTemp15 = (fRec2[0] * (fRec3[0] * fTemp14 + fTemp13 * fRec3[1] + fConst10 * fTemp12 * fRec3[2]) + fTemp11 * fRec3[3] + fTemp10 * fRec3[4]) / fTemp0;
		double fTemp16 = fRec13[1] * (1.0 - fConst86 / (fConst86 + 0.06 * std::exp(0.0 - 2.4849066497880004 * fRec13[1])));
		iRec15[0] = ((iRec15[1] > 0) ? 2 * (iRec14[1] < iSlow5) + -1 : 1 - 2 * (iRec14[1] > 0));
		iRec14[0] = iRec15[0] + iRec14[1];
		fRec18[0] = fRec18[1] + fSlow7 * (0.0 - fRec16[1]);
		fRec17[0] = fSlow7 * fRec18[0] + double(1 - iVec0[1]) + fRec17[1];
		fRec16[0] = fRec17[0];
		fRec13[0] = fTemp16 + fConst86 * (std::pow(1.0 - fSlow8 * (1.0 - ((iSlow3) ? std::max<double>(0.0, 0.5 * (fRec16[0] + 1.0)) : fSlow6 * double(iRec14[0]))), 1.9) / (fConst86 + 0.06 * std::exp(0.0 - 2.4849066497880004 * fTemp16)));
		double fTemp17 = ((iSlow2) ? 1.0 : 2.7e+03 / (std::exp(13.815510557964274 / std::log(8.551967507929417 * fRec13[0] + 2.718281828459045)) + 2.7e+03));
		fRec1[0] = fTemp17 * ((signbit(fTemp15)) ? bigchumppre_negclip(fTemp15) : bigchumppreclip(fTemp15)) - fConst12 * (fConst11 * fRec1[1] + fConst9 * fRec1[2]);
		double fTemp18 = fConst12 * (fConst92 * fRec1[0] + fConst91 * fRec1[1] + fConst90 * fRec1[2]);
		fRec0[0] = ((signbit(fTemp18)) ? bigchumppre2_negclip(fTemp18) : bigchumppre2clip(fTemp18)) - fConst7 * (fConst5 * fRec0[1] + fConst4 * fRec0[2] + fConst2 * fRec0[3]);
		double fTemp19 = fConst99 * (fConst98 * fRec0[0] + fConst97 * fRec0[1] + fConst96 * fRec0[2] + fConst94 * fRec0[3]);
		fRec23[0] = fConst48 * (fConst101 * fTemp8 + fConst102 * fVec4[1]) - fConst100 * fRec23[1];
		fRec22[0] = fRec23[0] - fConst41 * (fConst40 * fRec22[2] + fConst38 * fRec22[1]);
		fRec21[0] = fConst41 * (fConst37 * fRec22[0] + fConst103 * fRec22[1] + fConst37 * fRec22[2]) - (fTemp4 * fRec21[1] + fTemp3 * fRec21[2] + fTemp2 * fRec21[3] + fTemp1 * fRec21[4]) / fTemp0;
		double fTemp20 = (fRec2[0] * (fRec21[0] * fTemp14 + fTemp13 * fRec21[1] + fConst10 * fTemp12 * fRec21[2]) + fTemp11 * fRec21[3] + fTemp10 * fRec21[4]) / fTemp0;
		fRec20[0] = fTemp17 * ((signbit(fTemp20)) ? bigchumppre_negclip(fTemp20) : bigchumppreclip(fTemp20)) - fConst12 * (fConst11 * fRec20[1] + fConst9 * fRec20[2]);
		double fTemp21 = fConst12 * (fConst92 * fRec20[0] + fConst91 * fRec20[1] + fConst90 * fRec20[2]);
		fRec19[0] = ((signbit(fTemp21)) ? bigchumppre2_negclip(fTemp21) : bigchumppre2clip(fTemp21)) - fConst7 * (fConst5 * fRec19[1] + fConst4 * fRec19[2] + fConst2 * fRec19[3]);
		double fTemp22 = fConst99 * (fConst98 * fRec19[0] + fConst97 * fRec19[1] + fConst96 * fRec19[2] + fConst94 * fRec19[3]);
		double fTemp23 = fConst38 * fRec27[1];
		fRec29[0] = fConst55 * (fConst107 * fTemp7 + fConst108 * fVec3[1]) - fConst106 * fRec29[1];
		fRec28[0] = fRec29[0] - fConst48 * (fConst47 * fRec28[2] + fConst45 * fRec28[1]);
		fRec27[0] = fConst48 * (fConst44 * fRec28[0] + fConst109 * fRec28[1] + fConst44 * fRec28[2]) - fConst105 * (fConst104 * fRec27[2] + fTemp23);
		fRec26[0] = fRec27[2] + fConst105 * (fTemp23 + fConst104 * fRec27[0]) - (fTemp4 * fRec26[1] + fTemp3 * fRec26[2] + fTemp2 * fRec26[3] + fTemp1 * fRec26[4]) / fTemp0;
		double fTemp24 = (fRec2[0] * (fRec26[0] * fTemp14 + fTemp13 * fRec26[1] + fConst10 * fTemp12 * fRec26[2]) + fTemp11 * fRec26[3] + fTemp10 * fRec26[4]) / fTemp0;
		fRec25[0] = fTemp17 * ((signbit(fTemp24)) ? bigchumppre_negclip(fTemp24) : bigchumppreclip(fTemp24)) - fConst12 * (fConst11 * fRec25[1] + fConst9 * fRec25[2]);
		double fTemp25 = fConst12 * (fConst92 * fRec25[0] + fConst91 * fRec25[1] + fConst90 * fRec25[2]);
		fRec24[0] = ((signbit(fTemp25)) ? bigchumppre2_negclip(fTemp25) : bigchumppre2clip(fTemp25)) - fConst7 * (fConst5 * fRec24[1] + fConst4 * fRec24[2] + fConst2 * fRec24[3]);
		double fTemp26 = fConst99 * (fConst98 * fRec24[0] + fConst97 * fRec24[1] + fConst96 * fRec24[2] + fConst94 * fRec24[3]);
		double fTemp27 = fConst38 * fRec33[1];
		double fTemp28 = fConst45 * fRec34[1];
		fRec36[0] = fConst62 * (fConst113 * fTemp6 + fConst114 * fVec2[1]) - fConst112 * fRec36[1];
		fRec35[0] = fRec36[0] - fConst55 * (fConst54 * fRec35[2] + fConst52 * fRec35[1]);
		fRec34[0] = fConst55 * (fConst51 * fRec35[0] + fConst115 * fRec35[1] + fConst51 * fRec35[2]) - fConst111 * (fConst110 * fRec34[2] + fTemp28);
		fRec33[0] = fRec34[2] + fConst111 * (fTemp28 + fConst110 * fRec34[0]) - fConst105 * (fConst104 * fRec33[2] + fTemp27);
		fRec32[0] = fRec33[2] + fConst105 * (fTemp27 + fConst104 * fRec33[0]) - (fTemp4 * fRec32[1] + fTemp3 * fRec32[2] + fTemp2 * fRec32[3] + fTemp1 * fRec32[4]) / fTemp0;
		double fTemp29 = (fRec2[0] * (fRec32[0] * fTemp14 + fTemp13 * fRec32[1] + fConst10 * fTemp12 * fRec32[2]) + fTemp11 * fRec32[3] + fTemp10 * fRec32[4]) / fTemp0;
		fRec31[0] = fTemp17 * ((signbit(fTemp29)) ? bigchumppre_negclip(fTemp29) : bigchumppreclip(fTemp29)) - fConst12 * (fConst11 * fRec31[1] + fConst9 * fRec31[2]);
		double fTemp30 = fConst12 * (fConst92 * fRec31[0] + fConst91 * fRec31[1] + fConst90 * fRec31[2]);
		fRec30[0] = ((signbit(fTemp30)) ? bigchumppre2_negclip(fTemp30) : bigchumppre2clip(fTemp30)) - fConst7 * (fConst5 * fRec30[1] + fConst4 * fRec30[2] + fConst2 * fRec30[3]);
		double fTemp31 = fConst99 * (fConst98 * fRec30[0] + fConst97 * fRec30[1] + fConst96 * fRec30[2] + fConst94 * fRec30[3]);
		double fTemp32 = fConst38 * fRec40[1];
		double fTemp33 = fConst45 * fRec41[1];
		double fTemp34 = fConst52 * fRec42[1];
		fRec44[0] = fConst118 * fVec1[1] - fConst65 * (fConst63 * fRec44[1] - fConst60 * fTemp5);
		fRec43[0] = fRec44[0] - fConst62 * (fConst61 * fRec43[2] + fConst59 * fRec43[1]);
		fRec42[0] = fConst62 * (fConst58 * fRec43[0] + fConst119 * fRec43[1] + fConst58 * fRec43[2]) - fConst117 * (fConst116 * fRec42[2] + fTemp34);
		fRec41[0] = fRec42[2] + fConst117 * (fTemp34 + fConst116 * fRec42[0]) - fConst111 * (fConst110 * fRec41[2] + fTemp33);
		fRec40[0] = fRec41[2] + fConst111 * (fTemp33 + fConst110 * fRec41[0]) - fConst105 * (fConst104 * fRec40[2] + fTemp32);
		fRec39[0] = fRec40[2] + fConst105 * (fTemp32 + fConst104 * fRec40[0]) - (fRec39[1] * fTemp4 + fRec39[2] * fTemp3 + fRec39[3] * fTemp2 + fRec39[4] * fTemp1) / fTemp0;
		double fTemp35 = (fRec2[0] * (fRec39[0] * fTemp14 + fRec39[1] * fTemp13 + fConst10 * fRec39[2] * fTemp12) + fRec39[3] * fTemp11 + fRec2[0] * fRec39[4] * fTemp9) / fTemp0;
		fRec38[0] = ((signbit(fTemp35)) ? bigchumppre_negclip(fTemp35) : bigchumppreclip(fTemp35)) * fTemp17 - fConst12 * (fConst11 * fRec38[1] + fConst9 * fRec38[2]);
		double fTemp36 = fConst12 * (fConst92 * fRec38[0] + fConst91 * fRec38[1] + fConst90 * fRec38[2]);
		fRec37[0] = ((signbit(fTemp36)) ? bigchumppre2_negclip(fTemp36) : bigchumppre2clip(fTemp36)) - fConst7 * (fConst5 * fRec37[1] + fConst4 * fRec37[2] + fConst2 * fRec37[3]);
		double fTemp37 = fConst99 * (fConst98 * fRec37[0] + fConst97 * fRec37[1] + fConst96 * fRec37[2] + fConst94 * fRec37[3]);
		fRec45[0] = fSlow9 + 0.999 * fRec45[1];
		output0[i0] = FAUSTFLOAT(fRec45[0] * (((signbit(fTemp37)) ? bigchumppower_negclip(fTemp37) : bigchumppowerclip(fTemp37)) + ((signbit(fTemp31)) ? bigchumppower_negclip(fTemp31) : bigchumppowerclip(fTemp31)) + ((signbit(fTemp26)) ? bigchumppower_negclip(fTemp26) : bigchumppowerclip(fTemp26)) + ((signbit(fTemp22)) ? bigchumppower_negclip(fTemp22) : bigchumppowerclip(fTemp22)) + ((signbit(fTemp19)) ? bigchumppower_negclip(fTemp19) : bigchumppowerclip(fTemp19))));
		iVec0[1] = iVec0[0];
		fRec2[1] = fRec2[0];
		fVec1[1] = fVec1[0];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fVec2[1] = fVec2[0];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fVec3[1] = fVec3[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fVec4[1] = fVec4[0];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		for (int j0 = 4; j0 > 0; j0 = j0 - 1) {
			fRec3[j0] = fRec3[j0 - 1];
		}
		fRec12[1] = fRec12[0];
		iRec15[1] = iRec15[0];
		iRec14[1] = iRec14[0];
		fRec18[1] = fRec18[0];
		fRec17[1] = fRec17[0];
		fRec16[1] = fRec16[0];
		fRec13[1] = fRec13[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		for (int j1 = 3; j1 > 0; j1 = j1 - 1) {
			fRec0[j1] = fRec0[j1 - 1];
		}
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		for (int j2 = 4; j2 > 0; j2 = j2 - 1) {
			fRec21[j2] = fRec21[j2 - 1];
		}
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		for (int j3 = 3; j3 > 0; j3 = j3 - 1) {
			fRec19[j3] = fRec19[j3 - 1];
		}
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		for (int j4 = 4; j4 > 0; j4 = j4 - 1) {
			fRec26[j4] = fRec26[j4 - 1];
		}
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		for (int j5 = 3; j5 > 0; j5 = j5 - 1) {
			fRec24[j5] = fRec24[j5 - 1];
		}
		fRec36[1] = fRec36[0];
		fRec35[2] = fRec35[1];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		for (int j6 = 4; j6 > 0; j6 = j6 - 1) {
			fRec32[j6] = fRec32[j6 - 1];
		}
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		for (int j7 = 3; j7 > 0; j7 = j7 - 1) {
			fRec30[j7] = fRec30[j7 - 1];
		}
		fRec44[1] = fRec44[0];
		fRec43[2] = fRec43[1];
		fRec43[1] = fRec43[0];
		fRec42[2] = fRec42[1];
		fRec42[1] = fRec42[0];
		fRec41[2] = fRec41[1];
		fRec41[1] = fRec41[0];
		fRec40[2] = fRec40[1];
		fRec40[1] = fRec40[0];
		for (int j8 = 4; j8 > 0; j8 = j8 - 1) {
			fRec39[j8] = fRec39[j8 - 1];
		}
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		for (int j9 = 3; j9 > 0; j9 = j9 - 1) {
			fRec37[j9] = fRec37[j9 - 1];
		}
		fRec45[1] = fRec45[0];
	}
#undef fVslider0
#undef fVslider1
#undef fCheckbox0
#undef fCheckbox1
#undef fVslider2
#undef fVslider3
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
	// static const value_pair fCheckbox1_values[] = {{"os.triangle"},{"sine"},{0}};
	case SINEWAVE: 
		fCheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	// static const value_pair fCheckbox0_values[] = {{"Off"},{"On"},{0}};
	case VIBE: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case VOLUME: 
		fVslider4_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case GAIN: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TONE: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case INTENSITY: 
		fVslider3_ = (float*)data; // , 5.0, 0.0, 1e+01, 0.1 
		break;
	case SPEED: 
		fVslider2_ = (float*)data; // , 5.0, 0.1, 1e+01, 0.1 
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
