// generated from file '../src/LV2/faust/gxtilttone.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "math.h"
#include "tiltdrivepro_in_neg_table.h"
#include "tiltdrivepro_in_table.h"
#include "tiltdrivepro_out_3_neg_table.h"
#include "tiltdrivepro_out_3_table.h"

namespace gxtilttone {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fVec0[2];
	double fConst11;
	double fConst12;
	double fRec6[2];
	double fConst13;
	double fConst14;
	double fRec5[3];
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
	double fRec4[3];
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fRec3[3];
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fRec2[3];
	double fConst43;
	double fConst44;
	double fConst45;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec7[2];
	double fConst46;
	double fConst47;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec8[2];
	double fConst48;
	double fConst49;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec9[2];
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fConst61;
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
	double fConst72;
	double fConst73;
	double fConst74;
	double fConst75;
	double fConst76;
	double fConst77;
	double fConst78;
	double fConst79;
	double fConst80;
	double fConst81;
	double fConst82;
	double fConst83;
	double fConst84;
	double fConst85;
	double fConst86;
	double fConst87;
	double fConst88;
	double fConst89;
	double fConst90;
	double fConst91;
	double fConst92;
	double fConst93;
	double fConst94;
	double fConst95;
	double fConst96;
	double fConst97;
	double fConst98;
	double fConst99;
	double fConst100;
	double fConst101;
	double fConst102;
	double fConst103;
	double fConst104;
	double fConst105;
	double fConst106;
	double fConst107;
	double fConst108;
	double fConst109;
	double fConst110;
	double fConst111;
	double fConst112;
	double fConst113;
	double fConst114;
	double fConst115;
	double fConst116;
	double fConst117;
	double fConst118;
	double fConst119;
	double fConst120;
	double fConst121;
	double fConst122;
	double fConst123;
	double fConst124;
	double fConst125;
	double fConst126;
	double fConst127;
	double fConst128;
	double fConst129;
	double fConst130;
	double fConst131;
	double fConst132;
	double fConst133;
	double fRec1[5];
	double fConst134;
	double fConst135;
	double fConst136;
	double fConst137;
	double fConst138;
	double fConst139;
	double fConst140;
	double fConst141;
	double fConst142;
	double fConst143;
	double fConst144;
	double fConst145;
	double fConst146;
	double fConst147;
	double fConst148;
	double fConst149;
	double fConst150;
	double fConst151;
	double fConst152;
	double fConst153;
	double fConst154;
	double fConst155;
	double fConst156;
	double fConst157;
	double fConst158;
	double fConst159;
	double fConst160;
	double fConst161;
	double fConst162;
	double fConst163;
	double fConst164;
	double fConst165;
	double fConst166;
	double fConst167;
	double fConst168;
	double fConst169;
	double fConst170;
	double fConst171;
	double fConst172;
	double fConst173;
	double fConst174;
	double fConst175;
	double fConst176;
	double fRec0[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec10[2];
	double fConst177;
	double fConst178;
	double fRec18[2];
	double fRec17[3];
	double fVec1[2];
	double fConst179;
	double fConst180;
	double fRec16[2];
	double fConst181;
	double fRec15[3];
	double fConst182;
	double fRec14[3];
	double fRec13[3];
	double fRec12[5];
	double fRec11[2];
	double fConst183;
	double fConst184;
	double fConst185;
	double fRec25[2];
	double fRec24[3];
	double fVec2[2];
	double fConst186;
	double fConst187;
	double fRec23[2];
	double fConst188;
	double fRec22[3];
	double fConst189;
	double fRec21[3];
	double fRec20[5];
	double fRec19[2];
	double fConst190;
	double fConst191;
	double fConst192;
	double fRec31[2];
	double fRec30[3];
	double fVec3[2];
	double fConst193;
	double fConst194;
	double fRec29[2];
	double fConst195;
	double fRec28[3];
	double fConst196;
	double fRec27[5];
	double fRec26[2];
	double fConst197;
	double fRec35[2];
	double fRec34[3];
	double fRec33[5];
	double fRec32[2];

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
	id = "tiltdrive";
	name = N_("Tilt Tone Pro");
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fVec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec6[l1] = 0.0;
	for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) fRec5[l2] = 0.0;
	for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) fRec4[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec3[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec2[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec7[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec8[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec9[l8] = 0.0;
	for (int l9 = 0; (l9 < 5); l9 = (l9 + 1)) fRec1[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec0[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec10[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec18[l12] = 0.0;
	for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) fRec17[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fVec1[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec16[l15] = 0.0;
	for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) fRec15[l16] = 0.0;
	for (int l17 = 0; (l17 < 3); l17 = (l17 + 1)) fRec14[l17] = 0.0;
	for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) fRec13[l18] = 0.0;
	for (int l19 = 0; (l19 < 5); l19 = (l19 + 1)) fRec12[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fRec11[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec25[l21] = 0.0;
	for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) fRec24[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fVec2[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec23[l24] = 0.0;
	for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) fRec22[l25] = 0.0;
	for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) fRec21[l26] = 0.0;
	for (int l27 = 0; (l27 < 5); l27 = (l27 + 1)) fRec20[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec19[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fRec31[l29] = 0.0;
	for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) fRec30[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fVec3[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fRec29[l32] = 0.0;
	for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) fRec28[l33] = 0.0;
	for (int l34 = 0; (l34 < 5); l34 = (l34 + 1)) fRec27[l34] = 0.0;
	for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) fRec26[l35] = 0.0;
	for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) fRec35[l36] = 0.0;
	for (int l37 = 0; (l37 < 3); l37 = (l37 + 1)) fRec34[l37] = 0.0;
	for (int l38 = 0; (l38 < 5); l38 = (l38 + 1)) fRec33[l38] = 0.0;
	for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) fRec32[l39] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (2.0831309537617601e-05 * fConst0);
	fConst2 = (fConst1 + 9.7142194356639804e-05);
	fConst3 = (fConst0 / fConst2);
	fConst4 = std::tan((20517.741620594938 / fConst0));
	fConst5 = (1.0 / fConst4);
	fConst6 = (1.0 / (((fConst5 + 1.0000000000000004) / fConst4) + 1.0));
	fConst7 = mydsp_faustpower2_f(fConst4);
	fConst8 = (1.0 / fConst7);
	fConst9 = (fConst5 + 1.0);
	fConst10 = (0.0 - (1.0 / (fConst4 * fConst9)));
	fConst11 = (1.0 / fConst9);
	fConst12 = (1.0 - fConst5);
	fConst13 = (((fConst5 + -1.0000000000000004) / fConst4) + 1.0);
	fConst14 = (2.0 * (1.0 - fConst8));
	fConst15 = (0.0 - (2.0 / fConst7));
	fConst16 = std::tan((3769.9111843077517 / fConst0));
	fConst17 = (1.0 / fConst16);
	fConst18 = (fConst17 + 1.0);
	fConst19 = (1.0 / ((fConst18 / fConst16) + 1.0));
	fConst20 = (1.0 - fConst17);
	fConst21 = (1.0 - (fConst20 / fConst16));
	fConst22 = mydsp_faustpower2_f(fConst16);
	fConst23 = (1.0 / fConst22);
	fConst24 = (2.0 * (1.0 - fConst23));
	fConst25 = std::tan((659.73445725385659 / fConst0));
	fConst26 = (1.0 / fConst25);
	fConst27 = (fConst26 + 1.0);
	fConst28 = (1.0 / ((fConst27 / fConst25) + 1.0));
	fConst29 = (1.0 - fConst26);
	fConst30 = (1.0 - (fConst29 / fConst25));
	fConst31 = mydsp_faustpower2_f(fConst25);
	fConst32 = (1.0 / fConst31);
	fConst33 = (2.0 * (1.0 - fConst32));
	fConst34 = std::tan((270.1769682087222 / fConst0));
	fConst35 = (1.0 / fConst34);
	fConst36 = (fConst35 + 1.0);
	fConst37 = (1.0 / ((fConst36 / fConst34) + 1.0));
	fConst38 = (1.0 - fConst35);
	fConst39 = (1.0 - (fConst38 / fConst34));
	fConst40 = mydsp_faustpower2_f(fConst34);
	fConst41 = (1.0 / fConst40);
	fConst42 = (2.0 * (1.0 - fConst41));
	fConst43 = mydsp_faustpower2_f(fConst0);
	fConst44 = (3.7198687211673802e-19 * fConst0);
	fConst45 = (fConst0 * ((fConst43 * (-8.9271744801210908e-16 - fConst44)) + 2.6848634574570702e-10));
	fConst46 = (2.92345034021946e-19 * fConst0);
	fConst47 = (fConst0 * ((fConst43 * (-4.3209287199853602e-16 - fConst46)) + 1.19104615298643e-11));
	fConst48 = (fConst0 * ((fConst43 * (-2.8592035498756302e-16 - fConst46)) + -1.08278915769268e-13));
	fConst49 = ((fConst0 * ((fConst43 * (fConst46 + 3.3464452732455401e-16)) + -3.8979678994419203e-12)) + 7.86732937188467e-25);
	fConst50 = (7.3086258505486595e-20 * fConst0);
	fConst51 = ((fConst0 * ((fConst43 * (fConst50 + 3.2373315465610598e-18)) + -9.7449197486048007e-13)) + 1.96683234297117e-25);
	fConst52 = (1.46172517010973e-19 * fConst0);
	fConst53 = ((fConst43 * (-6.4746630931221197e-18 - fConst52)) + 1.9489839497209601e-12);
	fConst54 = (1.2950265062968101e-19 * fConst0);
	fConst55 = ((fConst43 * (fConst54 + 6.76955704487864e-17)) + 1.47512425722838e-27);
	fConst56 = (6.4751325314840599e-20 * fConst0);
	fConst57 = ((fConst43 * (-3.38477852243932e-17 - fConst56)) + -7.3756212861418796e-28);
	fConst58 = (fConst0 * ((fConst43 * (-7.0672401195374098e-16 - fConst44)) + 1.6537295217553599e-10));
	fConst59 = ((fConst0 * ((fConst43 * (fConst44 + 7.6872182397319701e-16)) + -1.9974408336559301e-10)) + -6.63483897777351e-09);
	fConst60 = (1.8599343605836901e-19 * fConst0);
	fConst61 = (fConst0 * ((fConst43 * (-1.4086414362757599e-16 - fConst60)) + -3.5497184759000299e-11));
	fConst62 = (9.2996718029184397e-20 * fConst0);
	fConst63 = ((fConst0 * ((fConst43 * (fConst62 + 7.0432071813788106e-17)) + 1.7748592379500201e-11)) + 1.65870974444338e-09);
	fConst64 = (1.8379301369603799e-19 * fConst0);
	fConst65 = (fConst0 * ((fConst43 * (fConst64 + 2.6007774594047099e-16)) + -3.1930162580535002e-11));
	fConst66 = (9.1896506848019105e-20 * fConst0);
	fConst67 = ((fConst0 * ((fConst43 * (-1.30038872970235e-16 - fConst66)) + 1.5965081290267501e-11)) + -1.96683234297117e-24);
	fConst68 = (5.5798030817510602e-19 * fConst43);
	fConst69 = (fConst43 * (fConst68 + -1.1549011371724099e-12));
	fConst70 = (4.3851755103291904e-19 * fConst43);
	fConst71 = (fConst43 * (fConst70 + -1.6107472035435801e-13));
	fConst72 = (fConst43 * (fConst70 + -7.2835027944253996e-14));
	fConst73 = ((fConst43 * (1.02248258747622e-13 - fConst70)) + 1.1800994057827e-24);
	fConst74 = ((fConst43 * (-1.64523449411233e-16 - (1.0962938775823e-19 * fConst43))) + 2.9502485144567501e-25);
	fConst75 = ((2.1925877551646e-19 * fConst43) + 3.29046898822466e-16);
	fConst76 = (1.4617379622907199e-14 - (1.9425397594452199e-19 * fConst43));
	fConst77 = ((9.7126987972260802e-20 * fConst43) + -7.3086898114536199e-15);
	fConst78 = (fConst43 * (fConst68 + -7.5919563919601403e-13));
	fConst79 = ((fConst43 * (8.9109747185481199e-13 - fConst68)) + -9.9522584666602605e-09);
	fConst80 = (fConst43 * ((2.7899015408755301e-19 * fConst43) + 7.3320228111598897e-14));
	fConst81 = ((fConst43 * (-3.6660114055799499e-14 - (1.3949507704377701e-19 * fConst43))) + 2.4880646166650701e-09);
	fConst82 = (fConst43 * (1.8469127257477801e-13 - (2.75689520544057e-19 * fConst43)));
	fConst83 = ((fConst43 * ((1.3784476027202901e-19 * fConst43) + -9.2345636287389104e-14)) + -2.9502485144567498e-24);
	fConst84 = (fConst0 * ((fConst43 * (8.9271744801210908e-16 - fConst44)) + -2.6848634574570702e-10));
	fConst85 = (fConst0 * ((fConst43 * (4.3209287199853602e-16 - fConst46)) + -1.19104615298643e-11));
	fConst86 = (fConst0 * ((fConst43 * (2.8592035498756302e-16 - fConst46)) + 1.08278915769268e-13));
	fConst87 = ((fConst0 * ((fConst43 * (fConst46 + -3.3464452732455401e-16)) + 3.8979678994419203e-12)) + 7.86732937188467e-25);
	fConst88 = ((fConst0 * ((fConst43 * (fConst50 + -3.2373315465610598e-18)) + 9.7449197486048007e-13)) + 1.96683234297117e-25);
	fConst89 = ((fConst43 * (6.4746630931221197e-18 - fConst52)) + -1.9489839497209601e-12);
	fConst90 = ((fConst43 * (fConst54 + -6.76955704487864e-17)) + -1.47512425722838e-27);
	fConst91 = ((fConst43 * (3.38477852243932e-17 - fConst56)) + 7.3756212861418796e-28);
	fConst92 = (fConst0 * ((fConst43 * (7.0672401195374098e-16 - fConst44)) + -1.6537295217553599e-10));
	fConst93 = ((fConst0 * ((fConst43 * (fConst44 + -7.6872182397319701e-16)) + 1.9974408336559301e-10)) + -6.63483897777351e-09);
	fConst94 = (fConst0 * ((fConst43 * (1.4086414362757599e-16 - fConst60)) + 3.5497184759000299e-11));
	fConst95 = ((fConst0 * ((fConst43 * (fConst62 + -7.0432071813788106e-17)) + -1.7748592379500201e-11)) + 1.65870974444338e-09);
	fConst96 = (fConst0 * ((fConst43 * (fConst64 + -2.6007774594047099e-16)) + 3.1930162580535002e-11));
	fConst97 = ((fConst0 * ((fConst43 * (1.30038872970235e-16 - fConst66)) + -1.5965081290267501e-11)) + -1.96683234297117e-24);
	fConst98 = (fConst0 * ((fConst0 * ((fConst0 * (fConst62 + -4.4635872400605503e-16)) + 5.7745056858620496e-13)) + -1.34243172872854e-10));
	fConst99 = (fConst0 * ((fConst0 * ((fConst0 * (fConst50 + -2.1604643599926801e-16)) + 8.0537360177179004e-14)) + -5.95523076493215e-12));
	fConst100 = (fConst0 * ((fConst0 * ((fConst0 * (fConst50 + -1.4296017749378099e-16)) + 3.6417513972126998e-14)) + 5.4139457884634198e-14));
	fConst101 = ((fConst0 * ((fConst0 * ((fConst0 * (1.67322263662277e-16 - fConst50)) + -5.1124129373811e-14)) + 1.9489839497209601e-12)) + 1.96683234297117e-25);
	fConst102 = (1.8271564626371601e-20 * fConst0);
	fConst103 = ((fConst0 * ((fConst0 * ((fConst0 * (1.6186657732805299e-18 - fConst102)) + 8.22617247056166e-17)) + 4.8724598743024003e-13)) + 4.9170808574279199e-26);
	fConst104 = (3.6543129252743298e-20 * fConst0);
	fConst105 = ((fConst0 * ((fConst0 * (fConst104 + -3.2373315465610598e-18)) + -1.64523449411233e-16)) + -9.7449197486048007e-13);
	fConst106 = (3.2375662657420299e-20 * fConst0);
	fConst107 = ((fConst0 * ((fConst0 * (3.38477852243932e-17 - fConst106)) + -7.3086898114536199e-15)) + -7.3756212861418796e-28);
	fConst108 = (1.6187831328710099e-20 * fConst0);
	fConst109 = ((fConst0 * ((fConst0 * (fConst108 + -1.69238926121966e-17)) + 3.6543449057268099e-15)) + 3.6878106430709398e-28);
	fConst110 = (fConst0 * ((fConst0 * ((fConst0 * (fConst62 + -3.5336200597687e-16)) + 3.7959781959800702e-13)) + -8.2686476087767995e-11));
	fConst111 = ((fConst0 * ((fConst0 * ((fConst0 * (3.8436091198659801e-16 - fConst62)) + -4.45548735927406e-13)) + 9.9872041682796594e-11)) + -1.65870974444338e-09);
	fConst112 = (4.6498359014592199e-20 * fConst0);
	fConst113 = (fConst0 * ((fConst0 * ((fConst0 * (fConst112 + -7.0432071813788106e-17)) + -3.6660114055799499e-14)) + 1.7748592379500201e-11));
	fConst114 = (2.3249179507296099e-20 * fConst0);
	fConst115 = ((fConst0 * ((fConst0 * ((fConst0 * (3.5216035906894102e-17 - fConst114)) + 1.8330057027899699e-14)) + -8.8742961897500796e-12)) + 4.14677436110845e-10);
	fConst116 = (4.5948253424009601e-20 * fConst0);
	fConst117 = (fConst0 * ((fConst0 * ((fConst0 * (1.30038872970235e-16 - fConst116)) + -9.2345636287389104e-14)) + 1.5965081290267501e-11));
	fConst118 = (2.29741267120048e-20 * fConst0);
	fConst119 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst118 + -6.5019436485117698e-17)) + 4.6172818143694502e-14)) + -7.9825406451337393e-12)) + -4.9170808574279204e-25);
	fConst120 = (fConst0 * ((fConst0 * ((fConst0 * (fConst62 + 4.4635872400605503e-16)) + 5.7745056858620496e-13)) + 1.34243172872854e-10));
	fConst121 = (fConst0 * ((fConst0 * ((fConst0 * (fConst50 + 2.1604643599926801e-16)) + 8.0537360177179004e-14)) + 5.95523076493215e-12));
	fConst122 = (fConst0 * ((fConst0 * ((fConst0 * (fConst50 + 1.4296017749378099e-16)) + 3.6417513972126998e-14)) + -5.4139457884634198e-14));
	fConst123 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.67322263662277e-16 - fConst50)) + -5.1124129373811e-14)) + -1.9489839497209601e-12)) + 1.96683234297117e-25);
	fConst124 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.6186657732805299e-18 - fConst102)) + 8.22617247056166e-17)) + -4.8724598743024003e-13)) + 4.9170808574279199e-26);
	fConst125 = ((fConst0 * ((fConst0 * (fConst104 + 3.2373315465610598e-18)) + -1.64523449411233e-16)) + 9.7449197486048007e-13);
	fConst126 = ((fConst0 * ((fConst0 * (-3.38477852243932e-17 - fConst106)) + -7.3086898114536199e-15)) + 7.3756212861418796e-28);
	fConst127 = ((fConst0 * ((fConst0 * (fConst108 + 1.69238926121966e-17)) + 3.6543449057268099e-15)) + -3.6878106430709398e-28);
	fConst128 = (fConst0 * ((fConst0 * ((fConst0 * (fConst62 + 3.5336200597687e-16)) + 3.7959781959800702e-13)) + 8.2686476087767995e-11));
	fConst129 = ((fConst0 * ((fConst0 * ((fConst0 * (-3.8436091198659801e-16 - fConst62)) + -4.45548735927406e-13)) + -9.9872041682796594e-11)) + -1.65870974444338e-09);
	fConst130 = (fConst0 * ((fConst0 * ((fConst0 * (fConst112 + 7.0432071813788106e-17)) + -3.6660114055799499e-14)) + -1.7748592379500201e-11));
	fConst131 = ((fConst0 * ((fConst0 * ((fConst0 * (-3.5216035906894102e-17 - fConst114)) + 1.8330057027899699e-14)) + 8.8742961897500796e-12)) + 4.14677436110845e-10);
	fConst132 = (fConst0 * ((fConst0 * ((fConst0 * (-1.30038872970235e-16 - fConst116)) + -9.2345636287389104e-14)) + -1.5965081290267501e-11));
	fConst133 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst118 + 6.5019436485117698e-17)) + 4.6172818143694502e-14)) + 7.9825406451337393e-12)) + -4.9170808574279204e-25);
	fConst134 = (9.8607192519763008e-16 * fConst0);
	fConst135 = ((fConst0 * (-3.6684421033095901e-12 - fConst134)) + -5.8401613040721496e-10);
	fConst136 = (7.4702418575577996e-15 * fConst0);
	fConst137 = ((fConst0 * (-1.5908848400354501e-12 - fConst136)) + -5.7640755073748099e-11);
	fConst138 = ((fConst0 * (fConst136 + 1.5908848400354501e-12)) + 5.7640755073748099e-11);
	fConst139 = (3.6573059094293402e-18 * fConst0);
	fConst140 = ((fConst0 * (-6.09550984904878e-16 - fConst139)) + 9.6370856590357308e-28);
	fConst141 = ((fConst0 * (fConst139 + 6.09550984904878e-16)) + -9.6370856590357308e-28);
	fConst142 = ((fConst0 * (fConst134 + 3.6684421033095901e-12)) + 5.8401613040721496e-10);
	fConst143 = (4.8276438004467295e-19 * fConst0);
	fConst144 = ((fConst0 * ((fConst0 * (-8.0460730007443996e-17 - fConst143)) + 3.45844530442491e-12)) + 5.7640755073748003e-10);
	fConst145 = ((fConst0 * ((fConst0 * (fConst143 + 8.0460730007443996e-17)) + -3.45844530442491e-12)) + -5.7640755073748003e-10);
	fConst146 = (1.9721438503952602e-15 * fConst43);
	fConst147 = (fConst146 + -1.1680322608144299e-09);
	fConst148 = (1.4940483715115599e-14 * fConst43);
	fConst149 = (fConst148 + -1.15281510147496e-10);
	fConst150 = (1.15281510147496e-10 - fConst148);
	fConst151 = (1.4629223637717401e-17 * fConst0);
	fConst152 = (fConst151 + 1.21910196980976e-15);
	fConst153 = (-1.21910196980976e-15 - fConst151);
	fConst154 = (1.1680322608144299e-09 - fConst146);
	fConst155 = (1.9310575201786899e-18 * fConst0);
	fConst156 = ((fConst43 * (fConst155 + 1.6092146001488799e-16)) + 1.1528151014749601e-09);
	fConst157 = ((fConst43 * (-1.6092146001488799e-16 - fConst155)) + -1.1528151014749601e-09);
	fConst158 = (2.1943835456576001e-17 * fConst43);
	fConst159 = (-1.9274171318071501e-27 - fConst158);
	fConst160 = (fConst158 + 1.9274171318071501e-27);
	fConst161 = (2.89658628026804e-18 * fConst43);
	fConst162 = (-6.9168906088498296e-12 - fConst161);
	fConst163 = (fConst161 + 6.9168906088498296e-12);
	fConst164 = (fConst151 + -1.21910196980976e-15);
	fConst165 = (1.21910196980976e-15 - fConst151);
	fConst166 = ((fConst43 * (fConst155 + -1.6092146001488799e-16)) + -1.1528151014749601e-09);
	fConst167 = ((fConst43 * (1.6092146001488799e-16 - fConst155)) + 1.1528151014749601e-09);
	fConst168 = ((fConst0 * (fConst134 + -3.6684421033095901e-12)) + 5.8401613040721496e-10);
	fConst169 = ((fConst0 * (fConst136 + -1.5908848400354501e-12)) + 5.7640755073748099e-11);
	fConst170 = ((fConst0 * (1.5908848400354501e-12 - fConst136)) + -5.7640755073748099e-11);
	fConst171 = ((fConst0 * (6.09550984904878e-16 - fConst139)) + 9.6370856590357308e-28);
	fConst172 = ((fConst0 * (fConst139 + -6.09550984904878e-16)) + -9.6370856590357308e-28);
	fConst173 = ((fConst0 * (3.6684421033095901e-12 - fConst134)) + -5.8401613040721496e-10);
	fConst174 = ((fConst0 * ((fConst0 * (8.0460730007443996e-17 - fConst143)) + 3.45844530442491e-12)) + -5.7640755073748003e-10);
	fConst175 = ((fConst0 * ((fConst0 * (fConst143 + -8.0460730007443996e-17)) + -3.45844530442491e-12)) + 5.7640755073748003e-10);
	fConst176 = ((9.7142194356639804e-05 - fConst1) / fConst2);
	fConst177 = (1.0 / (((fConst17 + 1.0000000000000004) / fConst16) + 1.0));
	fConst178 = (1.0 / (fConst16 * fConst18));
	fConst179 = (0.0 - fConst178);
	fConst180 = (fConst20 / fConst18);
	fConst181 = (((fConst17 + -1.0000000000000004) / fConst16) + 1.0);
	fConst182 = (0.0 - (2.0 / fConst22));
	fConst183 = (1.0 / (((fConst26 + 1.0000000000000004) / fConst25) + 1.0));
	fConst184 = (1.0 / (fConst25 * fConst27));
	fConst185 = (1.0 / fConst18);
	fConst186 = (0.0 - fConst184);
	fConst187 = (fConst29 / fConst27);
	fConst188 = (((fConst26 + -1.0000000000000004) / fConst25) + 1.0);
	fConst189 = (0.0 - (2.0 / fConst31));
	fConst190 = (1.0 / (((fConst35 + 1.0000000000000004) / fConst34) + 1.0));
	fConst191 = (1.0 / (fConst34 * fConst36));
	fConst192 = (1.0 / fConst27);
	fConst193 = (0.0 - fConst191);
	fConst194 = (fConst38 / fConst36);
	fConst195 = (((fConst35 + -1.0000000000000004) / fConst34) + 1.0);
	fConst196 = (0.0 - (2.0 / fConst40));
	fConst197 = (1.0 / fConst36);
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
	double fSlow0 = (0.0070000000000000062 * double(fVslider0));
	double fSlow1 = (0.004073836948085289 * (std::exp((1.0 - double(fVslider1))) + -1.0));
	double fSlow2 = (0.004073836948085289 * (std::exp(double(fVslider2)) + -1.0));
	double fSlow3 = (0.00036676987543879196 * (std::exp((3.0 * double(fVslider3))) + -1.0));
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = double(input0[i]);
		fVec0[0] = fTemp0;
		fRec6[0] = ((fConst10 * fVec0[1]) - (fConst11 * ((fConst12 * fRec6[1]) - (fConst5 * fTemp0))));
		fRec5[0] = (fRec6[0] - (fConst6 * ((fConst13 * fRec5[2]) + (fConst14 * fRec5[1]))));
		double fTemp1 = (fConst24 * fRec4[1]);
		fRec4[0] = ((fConst6 * (((fConst8 * fRec5[0]) + (fConst15 * fRec5[1])) + (fConst8 * fRec5[2]))) - (fConst19 * ((fConst21 * fRec4[2]) + fTemp1)));
		double fTemp2 = (fConst33 * fRec3[1]);
		fRec3[0] = ((fRec4[2] + (fConst19 * (fTemp1 + (fConst21 * fRec4[0])))) - (fConst28 * ((fConst30 * fRec3[2]) + fTemp2)));
		double fTemp3 = (fConst42 * fRec2[1]);
		fRec2[0] = ((fRec3[2] + (fConst28 * (fTemp2 + (fConst30 * fRec3[0])))) - (fConst37 * ((fConst39 * fRec2[2]) + fTemp3)));
		fRec7[0] = (fSlow0 + (0.99299999999999999 * fRec7[1]));
		fRec8[0] = (fSlow1 + (0.99299999999999999 * fRec8[1]));
		fRec9[0] = (fSlow2 + (0.99299999999999999 * fRec9[1]));
		double fTemp4 = (fConst45 + ((((fRec7[0] * (fConst47 + (((fRec8[0] * (fConst48 + ((fConst49 * fRec8[0]) + -1.6587097444433901e-10))) + (fRec9[0] * (((fConst51 * fRec8[0]) + (fConst0 * (fConst53 + (fRec9[0] * (fConst55 + (fConst57 * fRec8[0])))))) + -3.9336646859423401e-25))) + 3.3174194888867503e-10))) + (fRec8[0] * (fConst58 + ((fConst59 * fRec8[0]) + 4.9542342647034699e-09)))) + (fRec9[0] * (fConst61 + (((fConst63 * fRec8[0]) + (fRec9[0] * (fConst65 + ((fConst67 * fRec8[0]) + 3.93366468594234e-24)))) + -3.31741948888676e-09)))) + 9.9960484039135697e-09));
		double fTemp5 = (fConst69 + ((((fRec7[0] * (fConst71 + (((fRec8[0] * (fConst72 + ((fConst73 * fRec8[0]) + -2.48806461666508e-10))) + (fRec9[0] * (((fConst74 * fRec8[0]) + (fConst43 * (fConst75 + (fRec9[0] * (fConst76 + (fConst77 * fRec8[0])))))) + -5.9004970289135103e-25))) + 4.9761292333301197e-10))) + (fRec8[0] * (fConst78 + ((fConst79 * fRec8[0]) + 7.4313513970552097e-09)))) + (fRec9[0] * (fConst80 + (((fConst81 * fRec8[0]) + (fRec9[0] * (fConst82 + ((fConst83 * fRec8[0]) + 5.90049702891351e-24)))) + -4.9761292333301402e-09)))) + 1.49940726058704e-08));
		double fTemp6 = (fConst84 + ((((fRec7[0] * (fConst85 + (((fRec8[0] * (fConst86 + ((fConst87 * fRec8[0]) + -1.6587097444433901e-10))) + (fRec9[0] * (((fConst88 * fRec8[0]) + (fConst0 * (fConst89 + (fRec9[0] * (fConst90 + (fConst91 * fRec8[0])))))) + -3.9336646859423401e-25))) + 3.3174194888867503e-10))) + (fRec8[0] * (fConst92 + ((fConst93 * fRec8[0]) + 4.9542342647034699e-09)))) + (fRec9[0] * (fConst94 + (((fConst95 * fRec8[0]) + (fRec9[0] * (fConst96 + ((fConst97 * fRec8[0]) + 3.93366468594234e-24)))) + -3.31741948888676e-09)))) + 9.9960484039135697e-09));
		double fTemp7 = (fConst98 + ((((fRec7[0] * (fConst99 + (((fRec8[0] * (fConst100 + ((fConst101 * fRec8[0]) + -4.1467743611084701e-11))) + (fRec9[0] * (((fConst103 * fRec8[0]) + (fConst0 * (fConst105 + (fRec9[0] * (fConst107 + (fConst109 * fRec8[0])))))) + -9.8341617148558399e-26))) + 8.2935487222168705e-11))) + (fRec8[0] * (fConst110 + ((fConst111 * fRec8[0]) + 1.2385585661758699e-09)))) + (fRec9[0] * (fConst113 + (((fConst115 * fRec8[0]) + (fRec9[0] * (fConst117 + ((fConst119 * fRec8[0]) + 9.8341617148558408e-25)))) + -8.2935487222168999e-10)))) + 2.4990121009783899e-09));
		double fTemp8 = (fConst120 + ((((fRec7[0] * (fConst121 + (((fRec8[0] * (fConst122 + ((fConst123 * fRec8[0]) + -4.1467743611084701e-11))) + (fRec9[0] * (((fConst124 * fRec8[0]) + (fConst0 * (fConst125 + (fRec9[0] * (fConst126 + (fConst127 * fRec8[0])))))) + -9.8341617148558399e-26))) + 8.2935487222168705e-11))) + (fRec8[0] * (fConst128 + ((fConst129 * fRec8[0]) + 1.2385585661758699e-09)))) + (fRec9[0] * (fConst130 + (((fConst131 * fRec8[0]) + (fRec9[0] * (fConst132 + ((fConst133 * fRec8[0]) + 9.8341617148558408e-25)))) + -8.2935487222168999e-10)))) + 2.4990121009783899e-09));
		fRec1[0] = ((fRec2[2] + (fConst37 * (fTemp3 + (fConst39 * fRec2[0])))) - (((((fRec1[1] * fTemp4) + (fRec1[2] * fTemp5)) + (fRec1[3] * fTemp6)) + (fRec1[4] * fTemp7)) / fTemp8));
		double fTemp9 = (fConst135 + (((fRec7[0] * (fConst137 + ((fConst138 * fRec8[0]) + (fConst0 * (fRec9[0] * (fConst140 + (fConst141 * fRec8[0]))))))) + (fConst142 * fRec8[0])) + (fRec9[0] * (fConst144 + (fConst145 * fRec8[0])))));
		double fTemp10 = (fConst147 + (((fRec7[0] * (fConst149 + ((fConst150 * fRec8[0]) + (fConst43 * (fRec9[0] * (fConst152 + (fConst153 * fRec8[0]))))))) + (fConst154 * fRec8[0])) + (fRec9[0] * (fConst156 + (fConst157 * fRec8[0])))));
		double fTemp11 = ((((fRec7[0] * (((0.0 - (3.1817696800708901e-12 * fRec8[0])) + (fRec9[0] * (fConst159 + (fConst160 * fRec8[0])))) + 3.1817696800708901e-12)) - (7.3368842066191899e-12 * fRec8[0])) + (fRec9[0] * (fConst162 + (fConst163 * fRec8[0])))) + 7.3368842066191899e-12);
		double fTemp12 = (fConst154 + (((fRec7[0] * (fConst150 + ((fConst149 * fRec8[0]) + (fConst43 * (fRec9[0] * (fConst164 + (fConst165 * fRec8[0]))))))) + (fConst147 * fRec8[0])) + (fRec9[0] * (fConst166 + (fConst167 * fRec8[0])))));
		double fTemp13 = (fConst168 + (((fRec7[0] * (fConst169 + ((fConst170 * fRec8[0]) + (fConst0 * (fRec9[0] * (fConst171 + (fConst172 * fRec8[0]))))))) + (fConst173 * fRec8[0])) + (fRec9[0] * (fConst174 + (fConst175 * fRec8[0])))));
		double fTemp14 = (fConst0 * ((((((fRec1[0] * fTemp9) + (fRec1[1] * fTemp10)) + (fConst0 * (fRec1[2] * fTemp11))) + (fRec1[3] * fTemp12)) + (fRec1[4] * fTemp13)) / fTemp8));
		fRec0[0] = ((int(signbit(double(fTemp14))) ? double(tiltdrivepro_in_negclip(double(fTemp14))) : double(tiltdrivepro_inclip(double(fTemp14)))) - (fConst176 * fRec0[1]));
		fRec10[0] = (fSlow3 + (0.99299999999999999 * fRec10[1]));
		double fTemp15 = (0.0 - (0.000487217249496405 * fRec10[0]));
		double fTemp16 = (fConst3 * ((fRec0[0] * fTemp15) + (0.000487217249496405 * (fRec10[0] * fRec0[1]))));
		fRec18[0] = (0.0 - (fConst11 * ((fConst12 * fRec18[1]) - (fTemp0 + fVec0[1]))));
		fRec17[0] = (fRec18[0] - (fConst6 * ((fConst13 * fRec17[2]) + (fConst14 * fRec17[1]))));
		double fTemp17 = (fRec17[2] + (fRec17[0] + (2.0 * fRec17[1])));
		fVec1[0] = fTemp17;
		fRec16[0] = ((fConst6 * ((fConst178 * fTemp17) + (fConst179 * fVec1[1]))) - (fConst180 * fRec16[1]));
		fRec15[0] = (fRec16[0] - (fConst177 * ((fConst181 * fRec15[2]) + (fConst24 * fRec15[1]))));
		double fTemp18 = (fConst33 * fRec14[1]);
		fRec14[0] = ((fConst177 * (((fConst23 * fRec15[0]) + (fConst182 * fRec15[1])) + (fConst23 * fRec15[2]))) - (fConst28 * ((fConst30 * fRec14[2]) + fTemp18)));
		double fTemp19 = (fConst42 * fRec13[1]);
		fRec13[0] = ((fRec14[2] + (fConst28 * (fTemp18 + (fConst30 * fRec14[0])))) - (fConst37 * ((fConst39 * fRec13[2]) + fTemp19)));
		fRec12[0] = ((fRec13[2] + (fConst37 * (fTemp19 + (fConst39 * fRec13[0])))) - (((((fTemp4 * fRec12[1]) + (fTemp5 * fRec12[2])) + (fTemp6 * fRec12[3])) + (fTemp7 * fRec12[4])) / fTemp8));
		double fTemp20 = (fConst0 * ((((((fRec12[0] * fTemp9) + (fTemp10 * fRec12[1])) + (fConst0 * (fTemp11 * fRec12[2]))) + (fTemp12 * fRec12[3])) + (fTemp13 * fRec12[4])) / fTemp8));
		fRec11[0] = ((int(signbit(double(fTemp20))) ? double(tiltdrivepro_in_negclip(double(fTemp20))) : double(tiltdrivepro_inclip(double(fTemp20)))) - (fConst176 * fRec11[1]));
		double fTemp21 = (fConst3 * ((fRec11[0] * fTemp15) + (0.000487217249496405 * (fRec10[0] * fRec11[1]))));
		fRec25[0] = (0.0 - (fConst185 * ((fConst20 * fRec25[1]) - (fConst6 * (fTemp17 + fVec1[1])))));
		fRec24[0] = (fRec25[0] - (fConst177 * ((fConst181 * fRec24[2]) + (fConst24 * fRec24[1]))));
		double fTemp22 = (fRec24[2] + (fRec24[0] + (2.0 * fRec24[1])));
		fVec2[0] = fTemp22;
		fRec23[0] = ((fConst177 * ((fConst184 * fTemp22) + (fConst186 * fVec2[1]))) - (fConst187 * fRec23[1]));
		fRec22[0] = (fRec23[0] - (fConst183 * ((fConst188 * fRec22[2]) + (fConst33 * fRec22[1]))));
		double fTemp23 = (fConst42 * fRec21[1]);
		fRec21[0] = ((fConst183 * (((fConst32 * fRec22[0]) + (fConst189 * fRec22[1])) + (fConst32 * fRec22[2]))) - (fConst37 * ((fConst39 * fRec21[2]) + fTemp23)));
		fRec20[0] = ((fRec21[2] + (fConst37 * (fTemp23 + (fConst39 * fRec21[0])))) - (((((fTemp4 * fRec20[1]) + (fTemp5 * fRec20[2])) + (fTemp6 * fRec20[3])) + (fTemp7 * fRec20[4])) / fTemp8));
		double fTemp24 = (fConst0 * ((((((fRec20[0] * fTemp9) + (fTemp10 * fRec20[1])) + (fConst0 * (fTemp11 * fRec20[2]))) + (fTemp12 * fRec20[3])) + (fTemp13 * fRec20[4])) / fTemp8));
		fRec19[0] = ((int(signbit(double(fTemp24))) ? double(tiltdrivepro_in_negclip(double(fTemp24))) : double(tiltdrivepro_inclip(double(fTemp24)))) - (fConst176 * fRec19[1]));
		double fTemp25 = (fConst3 * ((fRec19[0] * fTemp15) + (0.000487217249496405 * (fRec10[0] * fRec19[1]))));
		fRec31[0] = (0.0 - (fConst192 * ((fConst29 * fRec31[1]) - (fConst177 * (fTemp22 + fVec2[1])))));
		fRec30[0] = (fRec31[0] - (fConst183 * ((fConst188 * fRec30[2]) + (fConst33 * fRec30[1]))));
		double fTemp26 = (fRec30[2] + (fRec30[0] + (2.0 * fRec30[1])));
		fVec3[0] = fTemp26;
		fRec29[0] = ((fConst183 * ((fConst191 * fTemp26) + (fConst193 * fVec3[1]))) - (fConst194 * fRec29[1]));
		fRec28[0] = (fRec29[0] - (fConst190 * ((fConst195 * fRec28[2]) + (fConst42 * fRec28[1]))));
		fRec27[0] = ((fConst190 * (((fConst41 * fRec28[0]) + (fConst196 * fRec28[1])) + (fConst41 * fRec28[2]))) - (((((fTemp4 * fRec27[1]) + (fTemp5 * fRec27[2])) + (fTemp6 * fRec27[3])) + (fTemp7 * fRec27[4])) / fTemp8));
		double fTemp27 = (fConst0 * ((((((fRec27[0] * fTemp9) + (fTemp10 * fRec27[1])) + (fConst0 * (fTemp11 * fRec27[2]))) + (fTemp12 * fRec27[3])) + (fTemp13 * fRec27[4])) / fTemp8));
		fRec26[0] = ((int(signbit(double(fTemp27))) ? double(tiltdrivepro_in_negclip(double(fTemp27))) : double(tiltdrivepro_inclip(double(fTemp27)))) - (fConst176 * fRec26[1]));
		double fTemp28 = (fConst3 * ((fRec26[0] * fTemp15) + (0.000487217249496405 * (fRec10[0] * fRec26[1]))));
		fRec35[0] = (0.0 - (fConst197 * ((fConst38 * fRec35[1]) - (fConst183 * (fTemp26 + fVec3[1])))));
		fRec34[0] = (fRec35[0] - (fConst190 * ((fConst195 * fRec34[2]) + (fConst42 * fRec34[1]))));
		fRec33[0] = ((fConst190 * (fRec34[2] + (fRec34[0] + (2.0 * fRec34[1])))) - (((((fTemp4 * fRec33[1]) + (fTemp5 * fRec33[2])) + (fTemp6 * fRec33[3])) + (fTemp7 * fRec33[4])) / fTemp8));
		double fTemp29 = (fConst0 * ((((((fRec33[0] * fTemp9) + (fTemp10 * fRec33[1])) + (fConst0 * (fTemp11 * fRec33[2]))) + (fTemp12 * fRec33[3])) + (fTemp13 * fRec33[4])) / fTemp8));
		fRec32[0] = ((int(signbit(double(fTemp29))) ? double(tiltdrivepro_in_negclip(double(fTemp29))) : double(tiltdrivepro_inclip(double(fTemp29)))) - (fConst176 * fRec32[1]));
		double fTemp30 = (fConst3 * ((fRec32[0] * fTemp15) + (0.000487217249496405 * (fRec10[0] * fRec32[1]))));
		output0[i] = FAUSTFLOAT((((((int(signbit(double(fTemp16))) ? double(tiltdrivepro_out_3_negclip(double(fTemp16))) : double(tiltdrivepro_out_3clip(double(fTemp16)))) + (int(signbit(double(fTemp21))) ? double(tiltdrivepro_out_3_negclip(double(fTemp21))) : double(tiltdrivepro_out_3clip(double(fTemp21))))) + (int(signbit(double(fTemp25))) ? double(tiltdrivepro_out_3_negclip(double(fTemp25))) : double(tiltdrivepro_out_3clip(double(fTemp25))))) + (int(signbit(double(fTemp28))) ? double(tiltdrivepro_out_3_negclip(double(fTemp28))) : double(tiltdrivepro_out_3clip(double(fTemp28))))) + (int(signbit(double(fTemp30))) ? double(tiltdrivepro_out_3_negclip(double(fTemp30))) : double(tiltdrivepro_out_3clip(double(fTemp30))))));
		fVec0[1] = fVec0[0];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		for (int j0 = 4; (j0 > 0); j0 = (j0 - 1)) {
			fRec1[j0] = fRec1[(j0 - 1)];
		}
		fRec0[1] = fRec0[0];
		fRec10[1] = fRec10[0];
		fRec18[1] = fRec18[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fVec1[1] = fVec1[0];
		fRec16[1] = fRec16[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		for (int j1 = 4; (j1 > 0); j1 = (j1 - 1)) {
			fRec12[j1] = fRec12[(j1 - 1)];
		}
		fRec11[1] = fRec11[0];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fVec2[1] = fVec2[0];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		for (int j2 = 4; (j2 > 0); j2 = (j2 - 1)) {
			fRec20[j2] = fRec20[(j2 - 1)];
		}
		fRec19[1] = fRec19[0];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fVec3[1] = fVec3[0];
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		for (int j3 = 4; (j3 > 0); j3 = (j3 - 1)) {
			fRec27[j3] = fRec27[(j3 - 1)];
		}
		fRec26[1] = fRec26[0];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		for (int j4 = 4; (j4 > 0); j4 = (j4 - 1)) {
			fRec33[j4] = fRec33[(j4 - 1)];
		}
		fRec32[1] = fRec32[0];
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
	case BODY: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case DRIVE: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case LEVEL: 
		fVslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TONE: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   BODY, 
   DRIVE, 
   LEVEL, 
   TONE, 
} PortIndex;
*/

} // end namespace gxtilttone
