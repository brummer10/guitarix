// generated from file '../src/LV2/faust/gx_studiopre_st.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "alembic_brite_neg_table.h"
#include "alembic_brite_table.h"
#include "alembic_norm_neg_table.h"
#include "alembic_norm_table.h"
#include "alembic_out_neg_table.h"
#include "alembic_out_table.h"
#include "math.h"

namespace gx_studiopre_st {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst3;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	double fConst5;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec2[2];
	double fConst7;
	double fConst8;
	double fConst10;
	double fConst12;
	double fVec0[2];
	double fConst13;
	double fConst14;
	double fRec8[2];
	double fConst15;
	double fConst16;
	double fRec7[3];
	double fConst17;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst25;
	double fConst26;
	double fRec6[3];
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst34;
	double fConst35;
	double fRec5[3];
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst43;
	double fConst44;
	double fRec4[3];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec9[2];
	double fConst46;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec10[2];
	double fConst48;
	double fConst50;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	double fRec11[2];
	double fConst52;
	double fConst54;
	double fConst56;
	double fConst58;
	double fConst60;
	double fConst62;
	double fConst64;
	double fConst66;
	double fConst68;
	double fConst70;
	double fConst72;
	double fConst73;
	double fConst74;
	double fConst76;
	double fConst78;
	double fConst79;
	double fConst80;
	double fConst81;
	double fConst82;
	double fConst83;
	double fConst84;
	double fConst86;
	double fConst88;
	double fConst90;
	double fConst92;
	double fConst94;
	double fConst96;
	double fConst98;
	double fConst100;
	double fConst102;
	double fConst104;
	double fConst106;
	double fConst108;
	double fConst110;
	double fConst112;
	double fConst114;
	double fConst116;
	double fConst118;
	double fConst120;
	double fConst121;
	double fConst122;
	double fConst124;
	double fConst126;
	double fConst127;
	double fConst128;
	double fConst129;
	double fConst130;
	double fConst131;
	double fConst132;
	double fConst134;
	double fConst136;
	double fConst138;
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
	double fConst177;
	double fConst178;
	double fConst179;
	double fConst180;
	double fConst181;
	double fConst182;
	double fConst183;
	double fConst184;
	double fConst185;
	double fConst186;
	double fConst187;
	double fConst188;
	double fConst189;
	double fConst190;
	double fConst191;
	double fConst192;
	double fConst193;
	double fConst194;
	double fConst195;
	double fConst196;
	double fConst198;
	double fConst200;
	double fConst202;
	double fConst204;
	double fConst206;
	double fConst208;
	double fConst210;
	double fConst212;
	double fConst214;
	double fConst216;
	double fConst218;
	double fConst220;
	double fConst222;
	double fConst224;
	double fConst225;
	double fConst226;
	double fConst228;
	double fConst230;
	double fConst231;
	double fConst232;
	double fConst233;
	double fConst234;
	double fConst235;
	double fConst236;
	double fConst238;
	double fConst240;
	double fConst242;
	double fConst244;
	double fConst245;
	double fConst246;
	double fConst247;
	double fConst248;
	double fConst249;
	double fConst250;
	double fConst251;
	double fConst252;
	double fConst253;
	double fConst254;
	double fConst255;
	double fConst256;
	double fConst257;
	double fConst258;
	double fConst259;
	double fConst260;
	double fConst261;
	double fConst262;
	double fConst263;
	double fConst264;
	double fConst265;
	double fConst266;
	double fConst267;
	double fConst268;
	double fConst269;
	double fConst270;
	double fConst271;
	double fConst272;
	double fRec3[6];
	double fConst274;
	double fConst276;
	double fConst277;
	double fConst278;
	double fConst280;
	double fConst282;
	double fConst283;
	double fConst284;
	double fConst285;
	double fConst286;
	double fConst287;
	double fConst288;
	double fConst289;
	double fConst291;
	double fConst293;
	double fConst294;
	double fConst296;
	double fConst298;
	double fConst299;
	double fConst300;
	double fConst301;
	double fConst302;
	double fConst303;
	double fConst304;
	double fConst305;
	double fConst307;
	double fConst309;
	double fConst310;
	double fConst312;
	double fConst314;
	double fConst315;
	double fConst316;
	double fConst317;
	double fConst318;
	double fConst319;
	double fConst320;
	double fConst321;
	double fConst322;
	double fConst323;
	double fConst324;
	double fConst325;
	double fConst326;
	double fConst327;
	double fConst328;
	double fConst329;
	double fConst330;
	double fConst331;
	double fConst332;
	double fConst333;
	double fConst334;
	double fConst335;
	double fConst336;
	double fConst337;
	double fConst338;
	double fConst339;
	double fConst340;
	double fConst341;
	double fConst342;
	double fConst343;
	double fConst344;
	double fConst345;
	double fConst346;
	double fConst347;
	double fConst348;
	double fConst349;
	double fConst350;
	double fConst351;
	double fConst352;
	double fConst353;
	double fConst354;
	double fConst355;
	double fConst356;
	double fConst357;
	double fConst359;
	double fConst361;
	double fConst363;
	double fConst365;
	double fConst367;
	double fConst369;
	double fConst371;
	double fConst373;
	double fConst375;
	double fConst376;
	double fConst378;
	double fConst380;
	double fConst381;
	double fConst382;
	double fConst383;
	double fConst384;
	double fConst385;
	double fConst386;
	double fConst387;
	double fConst388;
	double fConst389;
	double fConst390;
	double fConst391;
	double fConst392;
	double fConst393;
	double fConst394;
	double fConst395;
	double fConst396;
	double fConst397;
	double fConst399;
	double fConst401;
	double fConst403;
	double fConst405;
	double fConst407;
	double fConst409;
	double fConst411;
	double fConst413;
	double fConst415;
	double fConst417;
	double fConst419;
	double fConst421;
	double fConst422;
	double fConst423;
	double fConst424;
	double fConst425;
	double fConst426;
	double fConst427;
	double fConst428;
	double fConst429;
	double fConst430;
	double fConst431;
	double fConst432;
	double fConst433;
	double fRec12[5];
	double fConst435;
	double fConst437;
	double fConst438;
	double fConst440;
	double fConst442;
	double fConst443;
	double fConst445;
	double fConst447;
	double fConst448;
	double fConst450;
	double fConst452;
	double fConst453;
	double fConst454;
	double fConst455;
	double fConst456;
	double fConst457;
	double fConst458;
	double fConst459;
	double fConst460;
	double fConst461;
	double fConst462;
	double fConst463;
	double fConst464;
	double fConst465;
	double fConst466;
	double fConst467;
	double fConst468;
	double fConst469;
	double fRec1[3];
	double fConst470;
	double fConst471;
	double fConst472;
	double fConst473;
	double fRec20[2];
	double fRec19[3];
	double fVec1[2];
	double fConst474;
	double fConst475;
	double fRec18[2];
	double fConst476;
	double fRec17[3];
	double fConst477;
	double fRec16[3];
	double fRec15[3];
	double fRec14[6];
	double fRec21[5];
	double fRec13[3];
	double fConst478;
	double fConst479;
	double fConst480;
	double fRec28[2];
	double fRec27[3];
	double fVec2[2];
	double fConst481;
	double fConst482;
	double fRec26[2];
	double fConst483;
	double fRec25[3];
	double fConst484;
	double fRec24[3];
	double fRec23[6];
	double fRec29[5];
	double fRec22[3];
	double fConst485;
	double fConst486;
	double fConst487;
	double fRec35[2];
	double fRec34[3];
	double fVec3[2];
	double fConst488;
	double fConst489;
	double fRec33[2];
	double fConst490;
	double fRec32[3];
	double fConst491;
	double fRec31[6];
	double fRec36[5];
	double fRec30[3];
	double fConst492;
	double fRec40[2];
	double fRec39[3];
	double fRec38[6];
	double fRec41[5];
	double fRec37[3];
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT	*fVslider5_;
	double fRec42[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT	*fVslider6_;
	double fRec44[2];
	double fVec4[2];
	double fRec50[2];
	double fRec49[3];
	double fRec48[3];
	double fRec47[3];
	double fRec46[3];
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT	*fVslider7_;
	double fRec51[2];
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT	*fVslider8_;
	double fRec52[2];
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT	*fVslider9_;
	double fRec53[2];
	double fRec45[6];
	double fRec54[5];
	double fRec43[3];
	double fRec62[2];
	double fRec61[3];
	double fVec5[2];
	double fRec60[2];
	double fRec59[3];
	double fRec58[3];
	double fRec57[3];
	double fRec56[6];
	double fRec63[5];
	double fRec55[3];
	double fRec70[2];
	double fRec69[3];
	double fVec6[2];
	double fRec68[2];
	double fRec67[3];
	double fRec66[3];
	double fRec65[6];
	double fRec71[5];
	double fRec64[3];
	double fRec77[2];
	double fRec76[3];
	double fVec7[2];
	double fRec75[2];
	double fRec74[3];
	double fRec73[6];
	double fRec78[5];
	double fRec72[3];
	double fRec82[2];
	double fRec81[3];
	double fRec80[6];
	double fRec83[5];
	double fRec79[3];

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
	id = "gx_studiopre_st";
	name = N_("gx_studiopre_st");
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec2[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fVec0[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec8[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec7[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec6[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec5[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRec4[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec9[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec10[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec11[l10] = 0.0;
	for (int l11 = 0; (l11 < 6); l11 = (l11 + 1)) fRec3[l11] = 0.0;
	for (int l12 = 0; (l12 < 5); l12 = (l12 + 1)) fRec12[l12] = 0.0;
	for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) fRec1[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec20[l14] = 0.0;
	for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) fRec19[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fVec1[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec18[l17] = 0.0;
	for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) fRec17[l18] = 0.0;
	for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) fRec16[l19] = 0.0;
	for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) fRec15[l20] = 0.0;
	for (int l21 = 0; (l21 < 6); l21 = (l21 + 1)) fRec14[l21] = 0.0;
	for (int l22 = 0; (l22 < 5); l22 = (l22 + 1)) fRec21[l22] = 0.0;
	for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) fRec13[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec28[l24] = 0.0;
	for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) fRec27[l25] = 0.0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fVec2[l26] = 0.0;
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) fRec26[l27] = 0.0;
	for (int l28 = 0; (l28 < 3); l28 = (l28 + 1)) fRec25[l28] = 0.0;
	for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) fRec24[l29] = 0.0;
	for (int l30 = 0; (l30 < 6); l30 = (l30 + 1)) fRec23[l30] = 0.0;
	for (int l31 = 0; (l31 < 5); l31 = (l31 + 1)) fRec29[l31] = 0.0;
	for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) fRec22[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fRec35[l33] = 0.0;
	for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) fRec34[l34] = 0.0;
	for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) fVec3[l35] = 0.0;
	for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) fRec33[l36] = 0.0;
	for (int l37 = 0; (l37 < 3); l37 = (l37 + 1)) fRec32[l37] = 0.0;
	for (int l38 = 0; (l38 < 6); l38 = (l38 + 1)) fRec31[l38] = 0.0;
	for (int l39 = 0; (l39 < 5); l39 = (l39 + 1)) fRec36[l39] = 0.0;
	for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) fRec30[l40] = 0.0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) fRec40[l41] = 0.0;
	for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) fRec39[l42] = 0.0;
	for (int l43 = 0; (l43 < 6); l43 = (l43 + 1)) fRec38[l43] = 0.0;
	for (int l44 = 0; (l44 < 5); l44 = (l44 + 1)) fRec41[l44] = 0.0;
	for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) fRec37[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec42[l46] = 0.0;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) fRec44[l47] = 0.0;
	for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) fVec4[l48] = 0.0;
	for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) fRec50[l49] = 0.0;
	for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) fRec49[l50] = 0.0;
	for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) fRec48[l51] = 0.0;
	for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) fRec47[l52] = 0.0;
	for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) fRec46[l53] = 0.0;
	for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) fRec51[l54] = 0.0;
	for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) fRec52[l55] = 0.0;
	for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) fRec53[l56] = 0.0;
	for (int l57 = 0; (l57 < 6); l57 = (l57 + 1)) fRec45[l57] = 0.0;
	for (int l58 = 0; (l58 < 5); l58 = (l58 + 1)) fRec54[l58] = 0.0;
	for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) fRec43[l59] = 0.0;
	for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) fRec62[l60] = 0.0;
	for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) fRec61[l61] = 0.0;
	for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) fVec5[l62] = 0.0;
	for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) fRec60[l63] = 0.0;
	for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) fRec59[l64] = 0.0;
	for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) fRec58[l65] = 0.0;
	for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) fRec57[l66] = 0.0;
	for (int l67 = 0; (l67 < 6); l67 = (l67 + 1)) fRec56[l67] = 0.0;
	for (int l68 = 0; (l68 < 5); l68 = (l68 + 1)) fRec63[l68] = 0.0;
	for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) fRec55[l69] = 0.0;
	for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) fRec70[l70] = 0.0;
	for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) fRec69[l71] = 0.0;
	for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) fVec6[l72] = 0.0;
	for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) fRec68[l73] = 0.0;
	for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) fRec67[l74] = 0.0;
	for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) fRec66[l75] = 0.0;
	for (int l76 = 0; (l76 < 6); l76 = (l76 + 1)) fRec65[l76] = 0.0;
	for (int l77 = 0; (l77 < 5); l77 = (l77 + 1)) fRec71[l77] = 0.0;
	for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) fRec64[l78] = 0.0;
	for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) fRec77[l79] = 0.0;
	for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) fRec76[l80] = 0.0;
	for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) fVec7[l81] = 0.0;
	for (int l82 = 0; (l82 < 2); l82 = (l82 + 1)) fRec75[l82] = 0.0;
	for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) fRec74[l83] = 0.0;
	for (int l84 = 0; (l84 < 6); l84 = (l84 + 1)) fRec73[l84] = 0.0;
	for (int l85 = 0; (l85 < 5); l85 = (l85 + 1)) fRec78[l85] = 0.0;
	for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) fRec72[l86] = 0.0;
	for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) fRec82[l87] = 0.0;
	for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) fRec81[l88] = 0.0;
	for (int l89 = 0; (l89 < 6); l89 = (l89 + 1)) fRec80[l89] = 0.0;
	for (int l90 = 0; (l90 < 5); l90 = (l90 + 1)) fRec83[l90] = 0.0;
	for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) fRec79[l91] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = (4.33864919358014e-10 * fConst0);
	double fConst2 = ((fConst0 * (fConst1 + 7.8166451752789406e-09)) + 2.6830723178064399e-08);
	fConst3 = (fConst0 / fConst2);
	double fConst4 = (2.5428469025370501e-08 * fConst0);
	fConst5 = (-1.69523126835804e-07 - fConst4);
	double fConst6 = std::tan((20517.741620594938 / fConst0));
	fConst7 = (1.0 / fConst6);
	fConst8 = (1.0 / (((fConst7 + 1.0000000000000004) / fConst6) + 1.0));
	double fConst9 = mydsp_faustpower2_f(fConst6);
	fConst10 = (1.0 / fConst9);
	double fConst11 = (fConst7 + 1.0);
	fConst12 = (0.0 - (1.0 / (fConst6 * fConst11)));
	fConst13 = (1.0 / fConst11);
	fConst14 = (1.0 - fConst7);
	fConst15 = (((fConst7 + -1.0000000000000004) / fConst6) + 1.0);
	fConst16 = (2.0 * (1.0 - fConst10));
	fConst17 = (0.0 - (2.0 / fConst9));
	double fConst18 = std::tan((3769.9111843077517 / fConst0));
	double fConst19 = (1.0 / fConst18);
	double fConst20 = (fConst19 + 1.0);
	fConst21 = (1.0 / ((fConst20 / fConst18) + 1.0));
	fConst22 = (1.0 - fConst19);
	fConst23 = (1.0 - (fConst22 / fConst18));
	double fConst24 = mydsp_faustpower2_f(fConst18);
	fConst25 = (1.0 / fConst24);
	fConst26 = (2.0 * (1.0 - fConst25));
	double fConst27 = std::tan((659.73445725385659 / fConst0));
	double fConst28 = (1.0 / fConst27);
	double fConst29 = (fConst28 + 1.0);
	fConst30 = (1.0 / ((fConst29 / fConst27) + 1.0));
	fConst31 = (1.0 - fConst28);
	fConst32 = (1.0 - (fConst31 / fConst27));
	double fConst33 = mydsp_faustpower2_f(fConst27);
	fConst34 = (1.0 / fConst33);
	fConst35 = (2.0 * (1.0 - fConst34));
	double fConst36 = std::tan((270.1769682087222 / fConst0));
	double fConst37 = (1.0 / fConst36);
	double fConst38 = (fConst37 + 1.0);
	fConst39 = (1.0 / ((fConst38 / fConst36) + 1.0));
	fConst40 = (1.0 - fConst37);
	fConst41 = (1.0 - (fConst40 / fConst36));
	double fConst42 = mydsp_faustpower2_f(fConst36);
	fConst43 = (1.0 / fConst42);
	fConst44 = (2.0 * (1.0 - fConst43));
	double fConst45 = (1.9709622336031499e-24 * fConst0);
	fConst46 = ((fConst0 * ((fConst0 * ((fConst0 * (-3.0906018721435401e-19 - fConst45)) + -6.5909258847100303e-16)) + 9.2998714565051006e-14)) + 4.7456902115066703e-12);
	double fConst47 = (1.7219804977489901e-23 * fConst0);
	fConst48 = ((fConst0 * ((fConst0 * ((fConst0 * (4.7151741781331599e-20 - fConst47)) + 1.2931616899856299e-16)) + -1.6864923250265801e-14)) + -5.6939263144359597e-13);
	double fConst49 = (1.9190767211093099e-23 * fConst0);
	fConst50 = (fConst0 * ((fConst0 * ((fConst0 * (fConst49 + 4.9496910757539898e-20)) + 2.11680921042765e-18)) + -2.3784153360217099e-17));
	double fConst51 = (1.03563581534178e-23 * fConst0);
	fConst52 = ((fConst0 * ((fConst0 * (-6.5095345521710396e-19 - fConst51)) + 3.3139758307308302e-15)) + 1.8977285636844999e-13);
	double fConst53 = (2.7593471270444099e-25 * fConst0);
	fConst54 = ((fConst0 * ((fConst0 * ((fConst0 * (-3.1219952527554802e-20 - fConst53)) + -5.3024613999488199e-17)) + 1.0728203737318001e-15)) + 1.4618808515136201e-14);
	double fConst55 = (1.99687062779193e-24 * fConst0);
	fConst56 = ((fConst0 * ((fConst0 * (1.82179039185982e-21 - fConst55)) + 9.4929711147072402e-18)) + -1.21367136860993e-16);
	double fConst57 = (1.42633616270852e-24 * fConst0);
	fConst58 = (fConst0 * ((fConst0 * (fConst57 + 3.5767908251347002e-21)) + 1.5208914393608201e-20));
	double fConst59 = (7.4946378455850202e-23 * fConst0);
	fConst60 = ((fConst0 * ((fConst0 * (3.8100374638178802e-20 - fConst59)) + -5.9429254538461295e-16)) + -2.2793955955016199e-14);
	double fConst61 = (5.3533127468464398e-23 * fConst0);
	fConst62 = (fConst0 * ((fConst0 * (fConst61 + 7.4579893800680899e-20)) + -9.5136613440868197e-19));
	double fConst63 = (6.4629225489983404e-22 * fConst0);
	fConst64 = ((fConst0 * ((fConst0 * (1.00931167420926e-18 - fConst63)) + -8.0958150453420106e-15)) + -1.8825149987329498e-12);
	double fConst65 = (7.2026624170996101e-22 * fConst0);
	fConst66 = ((fConst0 * ((fConst0 * (fConst65 + 1.0191493826338201e-18)) + -7.8440170148967401e-17)) + -2.3978309714178e-15);
	double fConst67 = (7.3973986810126806e-23 * fConst0);
	fConst68 = ((fConst0 * ((fConst0 * (-6.4409067708435797e-18 - fConst67)) + 4.0582572065104097e-14)) + 9.4157214915370298e-12);
	double fConst69 = (3.10298692727022e-21 * fConst0);
	fConst70 = ((fConst0 * ((fConst0 * (-5.8522766354114703e-18 - fConst69)) + 4.5204034618767297e-16)) + 1.38254856528517e-14);
	double fConst71 = (8.2675955545181699e-23 * fConst0);
	fConst72 = ((fConst0 * ((fConst0 * ((fConst0 * (-2.8520515268884202e-19 - fConst71)) + -1.02988983768651e-17)) + -1.30486302011578e-17)) + -4.60849521761724e-15);
	fConst73 = ((fConst0 * ((fConst0 * (fConst47 + -9.0201254225056399e-20)) + -4.03664924154006e-18)) + 4.5551410515487698e-17);
	fConst74 = (fConst0 * ((fConst0 * (-1.5199927298072599e-21 - fConst49)) + -5.7081968064520901e-21));
	double fConst75 = (2.8942915566998301e-22 * fConst0);
	fConst76 = ((fConst0 * ((fConst0 * (-3.5306892965939102e-19 - fConst75)) + -5.2924548695524496e-19)) + -1.8433980870468999e-16);
	double fConst77 = (7.7115477984632695e-24 * fConst0);
	fConst78 = ((fConst0 * ((fConst0 * (-1.69540313347742e-20 - fConst77)) + 2.3003261173605501e-20)) + -1.1695046812109e-18);
	fConst79 = ((fConst0 * (fConst55 + -6.8139669613396302e-21)) + -2.9128112846638402e-20);
	fConst80 = (fConst0 * (-1.0950418363397899e-23 - fConst57));
	fConst81 = ((fConst0 * (fConst59 + -1.42192566937971e-19)) + 1.82351647640129e-18);
	fConst82 = (fConst0 * (-2.2832787225808402e-22 - fConst61));
	fConst83 = ((fConst0 * ((fConst0 * (fConst63 + -1.9069398060145901e-18)) + 1.50232520281226e-16)) + 4.60849521761724e-15);
	fConst84 = (fConst0 * ((fConst0 * (-1.8779602481101e-20 - fConst65)) + 1.9182647771342399e-19));
	double fConst85 = (3.17696091408035e-21 * fConst0);
	fConst86 = ((fConst0 * ((fConst0 * (fConst85 + 7.77799604390716e-18)) + -6.0246469294661299e-16)) + -1.8433980870469001e-14);
	double fConst87 = (2.99785513823401e-22 * fConst0);
	fConst88 = ((fConst0 * (fConst87 + 5.7326978490869098e-19)) + -7.3189179189121795e-18);
	double fConst89 = (7.9874825111677096e-24 * fConst0);
	fConst90 = (fConst0 * ((fConst0 * (fConst89 + 2.75154408026486e-20)) + 1.1709647369926799e-19));
	double fConst91 = (8.4646917778784898e-23 * fConst0);
	fConst92 = ((fConst0 * ((fConst0 * (fConst91 + 3.77720639872226e-19)) + 1.6285754826188399e-17)) + -1.8311895355098301e-16);
	double fConst93 = (3.9419244672062999e-24 * fConst0);
	fConst94 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst93 + 2.0604012480956899e-19)) + -1.31818517694201e-15)) + -1.8599742913010201e-13)) + 3.1637934743377799e-12);
	double fConst95 = (3.4439609954979802e-23 * fConst0);
	fConst96 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst95 + -3.1434494520887799e-20)) + 2.5863233799712599e-16)) + 3.3729846500531501e-14)) + -3.7959508762906402e-13);
	double fConst97 = (3.8381534422186099e-23 * fConst0);
	fConst98 = (fConst0 * ((fConst0 * ((fConst0 * (-3.2997940505026598e-20 - fConst97)) + 4.23361842085529e-18)) + 4.75683067204341e-17));
	double fConst99 = (6.9042387689451705e-24 * fConst0);
	fConst100 = ((fConst0 * ((fConst0 * (fConst99 + -1.30190691043421e-18)) + -6.6279516614616698e-15)) + 1.26515237578967e-13);
	double fConst101 = (5.5186942540888197e-25 * fConst0);
	fConst102 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst101 + 2.0813301685036501e-20)) + -1.06049227998976e-16)) + -2.1456407474636001e-15)) + 9.7458723434241307e-15);
	double fConst103 = (3.9937412555838496e-24 * fConst0);
	fConst104 = ((fConst0 * ((fConst0 * (fConst103 + -1.2145269279065401e-21)) + 1.8985942229414499e-17)) + 2.4273427372198698e-16);
	double fConst105 = (2.8526723254170401e-24 * fConst0);
	fConst106 = (fConst0 * ((fConst0 * (-2.38452721675646e-21 - fConst105)) + 3.0417828787216402e-20));
	double fConst107 = (4.9964252303900098e-23 * fConst0);
	fConst108 = ((fConst0 * ((fConst0 * (fConst107 + 7.6200749276357604e-20)) + 1.1885850907692301e-15)) + -1.5195970636677501e-14);
	double fConst109 = (3.5688751645642901e-23 * fConst0);
	fConst110 = (fConst0 * ((fConst0 * (1.4915978760136199e-19 - fConst109)) + 1.9027322688173601e-18));
	double fConst111 = (4.3086150326655603e-22 * fConst0);
	fConst112 = ((fConst0 * ((fConst0 * (fConst111 + 2.01862334841852e-18)) + 1.6191630090683999e-14)) + -1.2550099991553001e-12);
	double fConst113 = (4.8017749447330699e-22 * fConst0);
	fConst114 = ((fConst0 * ((fConst0 * (2.0382987652676502e-18 - fConst113)) + 1.56880340297935e-16)) + -1.5985539809451999e-15);
	double fConst115 = (4.9315991206751198e-23 * fConst0);
	fConst116 = ((fConst0 * ((fConst0 * (fConst115 + -1.28818135416872e-17)) + -8.1165144130208295e-14)) + 6.2771476610246903e-12);
	double fConst117 = (2.0686579515134799e-21 * fConst0);
	fConst118 = ((fConst0 * ((fConst0 * (fConst117 + -1.1704553270822901e-17)) + -9.0408069237534692e-16)) + 9.2169904352344801e-15);
	double fConst119 = (1.65351911090363e-22 * fConst0);
	fConst120 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst119 + 1.9013676845922801e-19)) + -2.0597796753730201e-17)) + 2.60972604023156e-17)) + -3.0723301450781599e-15);
	fConst121 = ((fConst0 * ((fConst0 * (6.01341694833709e-20 - fConst95)) + -8.0732984830801307e-18)) + -9.1102821030975396e-17);
	fConst122 = (fConst0 * ((fConst0 * (fConst97 + 1.01332848653817e-21)) + -1.14163936129042e-20));
	double fConst123 = (1.9295277044665501e-22 * fConst0);
	fConst124 = ((fConst0 * ((fConst0 * (fConst123 + -7.0613785931878203e-19)) + 1.0584909739104899e-18)) + -1.22893205803126e-16);
	double fConst125 = (1.5423095596926501e-23 * fConst0);
	fConst126 = ((fConst0 * ((fConst0 * (fConst125 + 1.13026875565161e-20)) + 4.6006522347211099e-20)) + 2.3390093624217899e-18);
	fConst127 = ((fConst0 * (4.5426446408930901e-21 - fConst103)) + -5.8256225693276804e-20);
	fConst128 = (fConst0 * (fConst105 + 7.3002789089319305e-24));
	fConst129 = ((fConst0 * (-2.8438513387594098e-19 - fConst107)) + -3.6470329528025899e-18);
	fConst130 = (fConst0 * (fConst109 + -4.5665574451616804e-22));
	fConst131 = ((fConst0 * ((fConst0 * (-3.8138796120291703e-18 - fConst111)) + -3.0046504056245298e-16)) + 3.0723301450781599e-15);
	fConst132 = (fConst0 * ((fConst0 * (fConst113 + -3.7559204962201898e-20)) + -3.8365295542684798e-19));
	double fConst133 = (2.11797394272023e-21 * fConst0);
	fConst134 = ((fConst0 * ((fConst0 * (1.5555992087814301e-17 - fConst133)) + 1.2049293858932299e-15)) + -1.22893205803126e-14);
	double fConst135 = (1.9985700921559999e-22 * fConst0);
	fConst136 = ((fConst0 * (1.14653956981738e-18 - fConst135)) + 1.4637835837824399e-17);
	double fConst137 = (1.5974965022335399e-23 * fConst0);
	fConst138 = (fConst0 * ((fConst0 * (-1.8343627201765701e-20 - fConst137)) + 2.3419294739853598e-19));
	double fConst139 = (1.6929383555757001e-22 * fConst0);
	fConst140 = ((fConst0 * ((fConst0 * (-2.5181375991481698e-19 - fConst139)) + 3.2571509652376903e-17)) + 3.6623790710196602e-16);
	fConst141 = ((fConst0 * ((fConst0 * ((fConst0 * (2.0604012480956899e-19 - fConst93)) + 1.31818517694201e-15)) + -1.8599742913010201e-13)) + -3.1637934743377799e-12);
	fConst142 = ((fConst0 * ((fConst0 * ((fConst0 * (-3.1434494520887799e-20 - fConst95)) + -2.5863233799712599e-16)) + 3.3729846500531501e-14)) + 3.7959508762906402e-13);
	fConst143 = (fConst0 * ((fConst0 * ((fConst0 * (fConst97 + -3.2997940505026598e-20)) + -4.23361842085529e-18)) + 4.75683067204341e-17));
	fConst144 = ((fConst0 * ((fConst0 * (fConst99 + 1.30190691043421e-18)) + -6.6279516614616698e-15)) + -1.26515237578967e-13);
	fConst145 = ((fConst0 * ((fConst0 * ((fConst0 * (2.0813301685036501e-20 - fConst101)) + 1.06049227998976e-16)) + -2.1456407474636001e-15)) + -9.7458723434241307e-15);
	fConst146 = ((fConst0 * ((fConst0 * (-1.2145269279065401e-21 - fConst103)) + -1.8985942229414499e-17)) + 2.4273427372198698e-16);
	fConst147 = (fConst0 * ((fConst0 * (fConst105 + -2.38452721675646e-21)) + -3.0417828787216402e-20));
	fConst148 = ((fConst0 * ((fConst0 * (fConst107 + -7.6200749276357604e-20)) + 1.1885850907692301e-15)) + 1.5195970636677501e-14);
	fConst149 = (fConst0 * ((fConst0 * (-1.4915978760136199e-19 - fConst109)) + 1.9027322688173601e-18));
	fConst150 = ((fConst0 * ((fConst0 * (fConst111 + -2.01862334841852e-18)) + 1.6191630090683999e-14)) + 1.2550099991553001e-12);
	fConst151 = ((fConst0 * ((fConst0 * (-2.0382987652676502e-18 - fConst113)) + 1.56880340297935e-16)) + 1.5985539809451999e-15);
	fConst152 = ((fConst0 * ((fConst0 * (fConst115 + 1.28818135416872e-17)) + -8.1165144130208295e-14)) + -6.2771476610246903e-12);
	fConst153 = ((fConst0 * ((fConst0 * (fConst117 + 1.1704553270822901e-17)) + -9.0408069237534692e-16)) + -9.2169904352344801e-15);
	fConst154 = ((fConst0 * ((fConst0 * ((fConst0 * (1.9013676845922801e-19 - fConst119)) + 2.0597796753730201e-17)) + 2.60972604023156e-17)) + 3.0723301450781599e-15);
	fConst155 = ((fConst0 * ((fConst0 * (fConst95 + 6.01341694833709e-20)) + 8.0732984830801307e-18)) + -9.1102821030975396e-17);
	fConst156 = (fConst0 * ((fConst0 * (1.01332848653817e-21 - fConst97)) + 1.14163936129042e-20));
	fConst157 = ((fConst0 * ((fConst0 * (fConst123 + 7.0613785931878203e-19)) + 1.0584909739104899e-18)) + 1.22893205803126e-16);
	fConst158 = ((fConst0 * ((fConst0 * (1.13026875565161e-20 - fConst125)) + -4.6006522347211099e-20)) + 2.3390093624217899e-18);
	fConst159 = ((fConst0 * (fConst103 + 4.5426446408930901e-21)) + 5.8256225693276804e-20);
	fConst160 = (fConst0 * (7.3002789089319305e-24 - fConst105));
	fConst161 = ((fConst0 * (2.8438513387594098e-19 - fConst107)) + -3.6470329528025899e-18);
	fConst162 = (fConst0 * (fConst109 + 4.5665574451616804e-22));
	fConst163 = ((fConst0 * ((fConst0 * (3.8138796120291703e-18 - fConst111)) + -3.0046504056245298e-16)) + -3.0723301450781599e-15);
	fConst164 = (fConst0 * ((fConst0 * (fConst113 + 3.7559204962201898e-20)) + -3.8365295542684798e-19));
	fConst165 = ((fConst0 * ((fConst0 * (-1.5555992087814301e-17 - fConst133)) + 1.2049293858932299e-15)) + 1.22893205803126e-14);
	fConst166 = ((fConst0 * (-1.14653956981738e-18 - fConst135)) + 1.4637835837824399e-17);
	fConst167 = (fConst0 * ((fConst0 * (fConst137 + -1.8343627201765701e-20)) + -2.3419294739853598e-19));
	fConst168 = ((fConst0 * ((fConst0 * (fConst139 + -2.5181375991481698e-19)) + -3.2571509652376903e-17)) + 3.6623790710196602e-16);
	fConst169 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst45 + -3.0906018721435401e-19)) + 6.5909258847100303e-16)) + 9.2998714565051006e-14)) + -4.7456902115066703e-12);
	fConst170 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst47 + 4.7151741781331599e-20)) + -1.2931616899856299e-16)) + -1.6864923250265801e-14)) + 5.6939263144359597e-13);
	fConst171 = (fConst0 * ((fConst0 * ((fConst0 * (4.9496910757539898e-20 - fConst49)) + -2.11680921042765e-18)) + -2.3784153360217099e-17));
	fConst172 = ((fConst0 * ((fConst0 * (6.5095345521710396e-19 - fConst51)) + 3.3139758307308302e-15)) + -1.8977285636844999e-13);
	fConst173 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst53 + -3.1219952527554802e-20)) + 5.3024613999488199e-17)) + 1.0728203737318001e-15)) + -1.4618808515136201e-14);
	fConst174 = ((fConst0 * ((fConst0 * (fConst55 + 1.82179039185982e-21)) + -9.4929711147072402e-18)) + -1.21367136860993e-16);
	fConst175 = (fConst0 * ((fConst0 * (3.5767908251347002e-21 - fConst57)) + -1.5208914393608201e-20));
	fConst176 = ((fConst0 * ((fConst0 * (-3.8100374638178802e-20 - fConst59)) + -5.9429254538461295e-16)) + 2.2793955955016199e-14);
	fConst177 = (fConst0 * ((fConst0 * (fConst61 + -7.4579893800680899e-20)) + -9.5136613440868197e-19));
	fConst178 = ((fConst0 * ((fConst0 * (-1.00931167420926e-18 - fConst63)) + -8.0958150453420106e-15)) + 1.8825149987329498e-12);
	fConst179 = ((fConst0 * ((fConst0 * (fConst65 + -1.0191493826338201e-18)) + -7.8440170148967401e-17)) + 2.3978309714178e-15);
	fConst180 = ((fConst0 * ((fConst0 * (6.4409067708435797e-18 - fConst67)) + 4.0582572065104097e-14)) + -9.4157214915370298e-12);
	fConst181 = ((fConst0 * ((fConst0 * (5.8522766354114703e-18 - fConst69)) + 4.5204034618767297e-16)) + -1.38254856528517e-14);
	fConst182 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst71 + -2.8520515268884202e-19)) + 1.02988983768651e-17)) + -1.30486302011578e-17)) + 4.60849521761724e-15);
	fConst183 = ((fConst0 * ((fConst0 * (-9.0201254225056399e-20 - fConst47)) + 4.03664924154006e-18)) + 4.5551410515487698e-17);
	fConst184 = (fConst0 * ((fConst0 * (fConst49 + -1.5199927298072599e-21)) + 5.7081968064520901e-21));
	fConst185 = ((fConst0 * ((fConst0 * (3.5306892965939102e-19 - fConst75)) + -5.2924548695524496e-19)) + 1.8433980870468999e-16);
	fConst186 = ((fConst0 * ((fConst0 * (fConst77 + -1.69540313347742e-20)) + -2.3003261173605501e-20)) + -1.1695046812109e-18);
	fConst187 = ((fConst0 * (-6.8139669613396302e-21 - fConst55)) + 2.9128112846638402e-20);
	fConst188 = (fConst0 * (fConst57 + -1.0950418363397899e-23));
	fConst189 = ((fConst0 * (fConst59 + 1.42192566937971e-19)) + 1.82351647640129e-18);
	fConst190 = (fConst0 * (2.2832787225808402e-22 - fConst61));
	fConst191 = ((fConst0 * ((fConst0 * (fConst63 + 1.9069398060145901e-18)) + 1.50232520281226e-16)) + -4.60849521761724e-15);
	fConst192 = (fConst0 * ((fConst0 * (1.8779602481101e-20 - fConst65)) + 1.9182647771342399e-19));
	fConst193 = ((fConst0 * ((fConst0 * (fConst85 + -7.77799604390716e-18)) + -6.0246469294661299e-16)) + 1.8433980870469001e-14);
	fConst194 = ((fConst0 * (fConst87 + -5.7326978490869098e-19)) + -7.3189179189121795e-18);
	fConst195 = (fConst0 * ((fConst0 * (2.75154408026486e-20 - fConst89)) + -1.1709647369926799e-19));
	fConst196 = ((fConst0 * ((fConst0 * (3.77720639872226e-19 - fConst91)) + -1.6285754826188399e-17)) + -1.8311895355098301e-16);
	double fConst197 = (3.9419244672063001e-25 * fConst0);
	fConst198 = ((fConst0 * ((fConst0 * ((fConst0 * (1.03020062404785e-19 - fConst197)) + -6.5909258847100303e-16)) + 9.2998714565051006e-14)) + -1.5818967371688899e-12);
	double fConst199 = (3.4439609954979804e-24 * fConst0);
	fConst200 = ((fConst0 * ((fConst0 * ((fConst0 * (-1.5717247260443899e-20 - fConst199)) + 1.2931616899856299e-16)) + -1.6864923250265801e-14)) + 1.8979754381453201e-13);
	double fConst201 = (3.8381534422186099e-24 * fConst0);
	fConst202 = (fConst0 * ((fConst0 * ((fConst0 * (fConst201 + -1.6498970252513299e-20)) + 2.11680921042765e-18)) + -2.3784153360217099e-17));
	double fConst203 = (3.4521193844725801e-24 * fConst0);
	fConst204 = ((fConst0 * ((fConst0 * (fConst203 + -6.5095345521710396e-19)) + 3.3139758307308302e-15)) + -6.3257618789483297e-14);
	double fConst205 = (5.5186942540888197e-26 * fConst0);
	fConst206 = ((fConst0 * ((fConst0 * ((fConst0 * (1.04066508425183e-20 - fConst205)) + -5.3024613999488199e-17)) + 1.0728203737318001e-15)) + -4.8729361717120598e-15);
	double fConst207 = (3.99374125558385e-25 * fConst0);
	fConst208 = ((fConst0 * ((fConst0 * (-6.07263463953272e-22 - fConst207)) + 9.4929711147072402e-18)) + -1.21367136860993e-16);
	double fConst209 = (2.85267232541704e-25 * fConst0);
	fConst210 = (fConst0 * ((fConst0 * (fConst209 + -1.19226360837823e-21)) + 1.5208914393608201e-20));
	double fConst211 = (2.4982126151950099e-23 * fConst0);
	fConst212 = ((fConst0 * ((fConst0 * (fConst211 + 3.8100374638178802e-20)) + -5.9429254538461295e-16)) + 7.5979853183387302e-15);
	double fConst213 = (1.78443758228215e-23 * fConst0);
	fConst214 = (fConst0 * ((fConst0 * (7.4579893800680899e-20 - fConst213)) + -9.5136613440868197e-19));
	double fConst215 = (2.1543075163327801e-22 * fConst0);
	fConst216 = ((fConst0 * ((fConst0 * (fConst215 + 1.00931167420926e-18)) + -8.0958150453420106e-15)) + 6.2750499957764903e-13);
	double fConst217 = (2.4008874723665401e-22 * fConst0);
	fConst218 = ((fConst0 * ((fConst0 * (1.0191493826338201e-18 - fConst217)) + -7.8440170148967401e-17)) + 7.9927699047260104e-16);
	double fConst219 = (2.4657995603375599e-23 * fConst0);
	fConst220 = ((fConst0 * ((fConst0 * (fConst219 + -6.4409067708435797e-18)) + 4.0582572065104097e-14)) + -3.1385738305123399e-12);
	double fConst221 = (1.0343289757567399e-21 * fConst0);
	fConst222 = ((fConst0 * ((fConst0 * (fConst221 + -5.8522766354114703e-18)) + 4.5204034618767297e-16)) + -4.60849521761724e-15);
	double fConst223 = (1.6535191109036301e-23 * fConst0);
	fConst224 = ((fConst0 * ((fConst0 * ((fConst0 * (9.5068384229614006e-20 - fConst223)) + -1.02988983768651e-17)) + -1.30486302011578e-17)) + 1.5361650725390799e-15);
	fConst225 = ((fConst0 * ((fConst0 * (fConst199 + 3.0067084741685498e-20)) + -4.03664924154006e-18)) + 4.5551410515487698e-17);
	fConst226 = (fConst0 * ((fConst0 * (5.0666424326908704e-22 - fConst201)) + -5.7081968064520901e-21));
	double fConst227 = (9.6476385223327706e-23 * fConst0);
	fConst228 = ((fConst0 * ((fConst0 * (fConst227 + -3.5306892965939102e-19)) + -5.2924548695524496e-19)) + 6.1446602901563198e-17);
	double fConst229 = (1.54230955969265e-24 * fConst0);
	fConst230 = ((fConst0 * ((fConst0 * (5.6513437782580501e-21 - fConst229)) + 2.3003261173605501e-20)) + -1.1695046812109e-18);
	fConst231 = ((fConst0 * (fConst207 + 2.2713223204465401e-21)) + -2.9128112846638402e-20);
	fConst232 = (fConst0 * (3.6501394544659697e-24 - fConst209));
	fConst233 = ((fConst0 * (-1.42192566937971e-19 - fConst211)) + 1.82351647640129e-18);
	fConst234 = (fConst0 * (fConst213 + -2.2832787225808402e-22));
	fConst235 = ((fConst0 * ((fConst0 * (-1.9069398060145901e-18 - fConst215)) + 1.50232520281226e-16)) + -1.5361650725390799e-15);
	fConst236 = (fConst0 * ((fConst0 * (fConst217 + -1.8779602481101e-20)) + 1.9182647771342399e-19));
	double fConst237 = (1.0589869713601201e-21 * fConst0);
	fConst238 = ((fConst0 * ((fConst0 * (7.77799604390716e-18 - fConst237)) + -6.0246469294661299e-16)) + 6.1446602901563198e-15);
	double fConst239 = (9.9928504607800195e-23 * fConst0);
	fConst240 = ((fConst0 * (5.7326978490869098e-19 - fConst239)) + -7.3189179189121795e-18);
	double fConst241 = (1.59749650223354e-24 * fConst0);
	fConst242 = (fConst0 * ((fConst0 * (fConst241 + -9.1718136008828703e-21)) + 1.1709647369926799e-19));
	double fConst243 = (1.6929383555756999e-23 * fConst0);
	fConst244 = ((fConst0 * ((fConst0 * (fConst243 + -1.2590687995740899e-19)) + 1.6285754826188399e-17)) + -1.8311895355098301e-16);
	fConst245 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst197 + 1.03020062404785e-19)) + 6.5909258847100303e-16)) + 9.2998714565051006e-14)) + 1.5818967371688899e-12);
	fConst246 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst199 + -1.5717247260443899e-20)) + -1.2931616899856299e-16)) + -1.6864923250265801e-14)) + -1.8979754381453201e-13);
	fConst247 = (fConst0 * ((fConst0 * ((fConst0 * (-1.6498970252513299e-20 - fConst201)) + -2.11680921042765e-18)) + -2.3784153360217099e-17));
	fConst248 = ((fConst0 * ((fConst0 * (fConst203 + 6.5095345521710396e-19)) + 3.3139758307308302e-15)) + 6.3257618789483297e-14);
	fConst249 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst205 + 1.04066508425183e-20)) + 5.3024613999488199e-17)) + 1.0728203737318001e-15)) + 4.8729361717120598e-15);
	fConst250 = ((fConst0 * ((fConst0 * (fConst207 + -6.07263463953272e-22)) + -9.4929711147072402e-18)) + -1.21367136860993e-16);
	fConst251 = (fConst0 * ((fConst0 * (-1.19226360837823e-21 - fConst209)) + -1.5208914393608201e-20));
	fConst252 = ((fConst0 * ((fConst0 * (fConst211 + -3.8100374638178802e-20)) + -5.9429254538461295e-16)) + -7.5979853183387302e-15);
	fConst253 = (fConst0 * ((fConst0 * (-7.4579893800680899e-20 - fConst213)) + -9.5136613440868197e-19));
	fConst254 = ((fConst0 * ((fConst0 * (fConst215 + -1.00931167420926e-18)) + -8.0958150453420106e-15)) + -6.2750499957764903e-13);
	fConst255 = ((fConst0 * ((fConst0 * (-1.0191493826338201e-18 - fConst217)) + -7.8440170148967401e-17)) + -7.9927699047260104e-16);
	fConst256 = ((fConst0 * ((fConst0 * (fConst219 + 6.4409067708435797e-18)) + 4.0582572065104097e-14)) + 3.1385738305123399e-12);
	fConst257 = ((fConst0 * ((fConst0 * (fConst221 + 5.8522766354114703e-18)) + 4.5204034618767297e-16)) + 4.60849521761724e-15);
	fConst258 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst223 + 9.5068384229614006e-20)) + 1.02988983768651e-17)) + -1.30486302011578e-17)) + -1.5361650725390799e-15);
	fConst259 = ((fConst0 * ((fConst0 * (3.0067084741685498e-20 - fConst199)) + 4.03664924154006e-18)) + 4.5551410515487698e-17);
	fConst260 = (fConst0 * ((fConst0 * (fConst201 + 5.0666424326908704e-22)) + 5.7081968064520901e-21));
	fConst261 = ((fConst0 * ((fConst0 * (fConst227 + 3.5306892965939102e-19)) + -5.2924548695524496e-19)) + -6.1446602901563198e-17);
	fConst262 = ((fConst0 * ((fConst0 * (fConst229 + 5.6513437782580501e-21)) + -2.3003261173605501e-20)) + -1.1695046812109e-18);
	fConst263 = ((fConst0 * (2.2713223204465401e-21 - fConst207)) + 2.9128112846638402e-20);
	fConst264 = (fConst0 * (fConst209 + 3.6501394544659697e-24));
	fConst265 = ((fConst0 * (1.42192566937971e-19 - fConst211)) + 1.82351647640129e-18);
	fConst266 = (fConst0 * (fConst213 + 2.2832787225808402e-22));
	fConst267 = ((fConst0 * ((fConst0 * (1.9069398060145901e-18 - fConst215)) + 1.50232520281226e-16)) + 1.5361650725390799e-15);
	fConst268 = (fConst0 * ((fConst0 * (fConst217 + 1.8779602481101e-20)) + 1.9182647771342399e-19));
	fConst269 = ((fConst0 * ((fConst0 * (-7.77799604390716e-18 - fConst237)) + -6.0246469294661299e-16)) + -6.1446602901563198e-15);
	fConst270 = ((fConst0 * (-5.7326978490869098e-19 - fConst239)) + -7.3189179189121795e-18);
	fConst271 = (fConst0 * ((fConst0 * (-9.1718136008828703e-21 - fConst241)) + -1.1709647369926799e-19));
	fConst272 = ((fConst0 * ((fConst0 * (-1.2590687995740899e-19 - fConst243)) + -1.6285754826188399e-17)) + -1.8311895355098301e-16);
	double fConst273 = (4.3278951632164298e-20 * fConst0);
	fConst274 = ((fConst0 * ((fConst0 * (-1.82089564663e-16 - fConst273)) + -7.34564519198978e-15)) + -4.0890921799096699e-14);
	double fConst275 = (6.9187439684072196e-22 * fConst0);
	fConst276 = ((fConst0 * ((fConst0 * ((fConst0 * (-3.00430509368582e-18 - fConst275)) + -1.0973101763703901e-15)) + -2.4667710277204801e-12)) + -1.6397259641437801e-11);
	fConst277 = mydsp_faustpower2_f(fConst0);
	fConst278 = (fConst277 * ((fConst0 * (fConst275 + 2.8874224828152799e-18)) + 1.92187332455754e-17));
	double fConst279 = (6.0590532285030101e-21 * fConst0);
	fConst280 = ((fConst0 * ((fConst0 * (-5.9968493040074702e-17 - fConst279)) + -1.4490803830035499e-13)) + -9.6339011758671695e-13);
	double fConst281 = (9.68624155577011e-23 * fConst0);
	fConst282 = (fConst0 * ((fConst0 * ((fConst0 * (-9.5912241386039909e-19 - fConst281)) + -2.3184034538722398e-15)) + -1.5413424062951501e-14));
	fConst283 = ((fConst0 * ((fConst0 * (fConst273 + 1.82089564663e-16)) + 7.34564519198978e-15)) + 4.0890921799096699e-14);
	fConst284 = ((fConst0 * (fConst273 + 1.7605995289819199e-18)) + 9.8138212317832004e-18);
	fConst285 = ((fConst0 * ((fConst0 * (fConst275 + 1.21495106849477e-19)) + 5.91080564497569e-16)) + 3.9353423139450596e-15);
	fConst286 = (fConst277 * (-4.6124959789380998e-21 - fConst275));
	fConst287 = ((fConst0 * (fConst279 + 3.47224379213122e-17)) + 2.3121362822081199e-16);
	fConst288 = (fConst0 * ((fConst0 * (fConst281 + 5.5552901570331097e-19)) + 3.6992217751083603e-18));
	fConst289 = ((fConst0 * (-1.7605995289819199e-18 - fConst273)) + -9.8138212317832004e-18);
	double fConst290 = (1.29836854896493e-19 * fConst0);
	fConst291 = ((fConst0 * ((fConst0 * (fConst290 + 1.82089564663e-16)) + -7.34564519198978e-15)) + -1.2267276539728999e-13);
	double fConst292 = (3.4593719842036099e-21 * fConst0);
	fConst293 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst292 + 9.0129152810574599e-18)) + 1.0973101763703901e-15)) + -2.4667710277204801e-12)) + -4.9191778924313303e-11);
	fConst294 = (fConst277 * ((fConst0 * (-8.66226744844584e-18 - fConst292)) + -1.92187332455754e-17));
	double fConst295 = (1.8177159685509e-20 * fConst0);
	fConst296 = ((fConst0 * ((fConst0 * (fConst295 + 5.9968493040074702e-17)) + -1.4490803830035499e-13)) + -2.89017035276015e-12);
	double fConst297 = (4.8431207778850602e-22 * fConst0);
	fConst298 = (fConst0 * ((fConst0 * ((fConst0 * (fConst297 + 2.8773672415812002e-18)) + 2.3184034538722398e-15)) + -1.5413424062951501e-14));
	fConst299 = ((fConst0 * ((fConst0 * (-1.82089564663e-16 - fConst290)) + 7.34564519198978e-15)) + 1.2267276539728999e-13);
	fConst300 = ((fConst0 * (-1.7605995289819199e-18 - fConst290)) + 9.8138212317832004e-18);
	fConst301 = ((fConst0 * ((fConst0 * (-3.6448532054843101e-19 - fConst292)) + -5.91080564497569e-16)) + 3.9353423139450596e-15);
	fConst302 = (fConst277 * (fConst292 + 1.3837487936814301e-20));
	fConst303 = ((fConst0 * (-3.47224379213122e-17 - fConst295)) + 2.3121362822081199e-16);
	fConst304 = (fConst0 * ((fConst0 * (-1.6665870471099299e-18 - fConst297)) + -3.6992217751083603e-18));
	fConst305 = ((fConst0 * (fConst290 + 1.7605995289819199e-18)) + -9.8138212317832004e-18);
	double fConst306 = (8.6557903264328705e-20 * fConst0);
	fConst307 = ((fConst0 * ((fConst0 * (3.64179129326e-16 - fConst306)) + 1.4691290383979601e-14)) + -8.1781843598193296e-14);
	double fConst308 = (6.9187439684072197e-21 * fConst0);
	fConst309 = ((fConst0 * ((fConst0 * ((fConst0 * (-6.0086101873716399e-18 - fConst308)) + 2.1946203527407802e-15)) + 4.9335420554409602e-12)) + -3.2794519282875499e-11);
	fConst310 = (fConst277 * ((fConst0 * (fConst308 + 5.7748449656305597e-18)) + -3.8437466491150898e-17));
	double fConst311 = (1.2118106457006001e-20 * fConst0);
	fConst312 = ((fConst0 * ((fConst0 * (1.1993698608014901e-16 - fConst311)) + 2.8981607660070998e-13)) + -1.9267802351734299e-12);
	double fConst313 = (9.6862415557701091e-22 * fConst0);
	fConst314 = (fConst0 * ((fConst0 * ((fConst0 * (-1.9182448277208001e-18 - fConst313)) + 4.6368069077444702e-15)) + 3.0826848125903001e-14));
	fConst315 = ((fConst0 * ((fConst0 * (fConst306 + -3.64179129326e-16)) + -1.4691290383979601e-14)) + 8.1781843598193296e-14);
	fConst316 = ((fConst0 * (fConst306 + -3.5211990579638398e-18)) + -1.9627642463566401e-17);
	fConst317 = ((fConst0 * ((fConst0 * (fConst308 + 2.4299021369895399e-19)) + -1.18216112899514e-15)) + -7.8706846278901192e-15);
	fConst318 = (fConst277 * (-9.2249919578761997e-21 - fConst308));
	fConst319 = ((fConst0 * (fConst311 + -6.9444875842624399e-17)) + -4.6242725644162398e-16);
	fConst320 = (fConst0 * ((fConst0 * (fConst313 + 1.11105803140662e-18)) + -7.3984435502167207e-18));
	fConst321 = ((fConst0 * (3.5211990579638398e-18 - fConst306)) + 1.9627642463566401e-17);
	fConst322 = ((fConst0 * ((fConst0 * (-3.64179129326e-16 - fConst306)) + 1.4691290383979601e-14)) + 8.1781843598193296e-14);
	fConst323 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst308 + -6.0086101873716399e-18)) + -2.1946203527407802e-15)) + 4.9335420554409602e-12)) + 3.2794519282875499e-11);
	fConst324 = (fConst277 * ((fConst0 * (5.7748449656305597e-18 - fConst308)) + 3.8437466491150898e-17));
	fConst325 = ((fConst0 * ((fConst0 * (-1.1993698608014901e-16 - fConst311)) + 2.8981607660070998e-13)) + 1.9267802351734299e-12);
	fConst326 = (fConst0 * ((fConst0 * ((fConst0 * (fConst313 + -1.9182448277208001e-18)) + -4.6368069077444702e-15)) + 3.0826848125903001e-14));
	fConst327 = ((fConst0 * ((fConst0 * (fConst306 + 3.64179129326e-16)) + -1.4691290383979601e-14)) + -8.1781843598193296e-14);
	fConst328 = ((fConst0 * (fConst306 + 3.5211990579638398e-18)) + -1.9627642463566401e-17);
	fConst329 = ((fConst0 * ((fConst0 * (2.4299021369895399e-19 - fConst308)) + 1.18216112899514e-15)) + -7.8706846278901192e-15);
	fConst330 = (fConst277 * (fConst308 + -9.2249919578761997e-21));
	fConst331 = ((fConst0 * (fConst311 + 6.9444875842624399e-17)) + -4.6242725644162398e-16);
	fConst332 = (fConst0 * ((fConst0 * (1.11105803140662e-18 - fConst313)) + 7.3984435502167207e-18));
	fConst333 = ((fConst0 * (-3.5211990579638398e-18 - fConst306)) + 1.9627642463566401e-17);
	fConst334 = ((fConst0 * ((fConst0 * (fConst290 + -1.82089564663e-16)) + -7.34564519198978e-15)) + 1.2267276539728999e-13);
	fConst335 = ((fConst0 * ((fConst0 * ((fConst0 * (9.0129152810574599e-18 - fConst292)) + -1.0973101763703901e-15)) + -2.4667710277204801e-12)) + 4.9191778924313303e-11);
	fConst336 = (fConst277 * ((fConst0 * (fConst292 + -8.66226744844584e-18)) + 1.92187332455754e-17));
	fConst337 = ((fConst0 * ((fConst0 * (fConst295 + -5.9968493040074702e-17)) + -1.4490803830035499e-13)) + 2.89017035276015e-12);
	fConst338 = (fConst0 * ((fConst0 * ((fConst0 * (2.8773672415812002e-18 - fConst297)) + -2.3184034538722398e-15)) + -1.5413424062951501e-14));
	fConst339 = ((fConst0 * ((fConst0 * (1.82089564663e-16 - fConst290)) + 7.34564519198978e-15)) + -1.2267276539728999e-13);
	fConst340 = ((fConst0 * (1.7605995289819199e-18 - fConst290)) + 9.8138212317832004e-18);
	fConst341 = ((fConst0 * ((fConst0 * (fConst292 + -3.6448532054843101e-19)) + 5.91080564497569e-16)) + 3.9353423139450596e-15);
	fConst342 = (fConst277 * (1.3837487936814301e-20 - fConst292));
	fConst343 = ((fConst0 * (3.47224379213122e-17 - fConst295)) + 2.3121362822081199e-16);
	fConst344 = (fConst0 * ((fConst0 * (fConst297 + -1.6665870471099299e-18)) + 3.6992217751083603e-18));
	fConst345 = ((fConst0 * (fConst290 + -1.7605995289819199e-18)) + -9.8138212317832004e-18);
	fConst346 = ((fConst0 * ((fConst0 * (1.82089564663e-16 - fConst273)) + -7.34564519198978e-15)) + 4.0890921799096699e-14);
	fConst347 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst275 + -3.00430509368582e-18)) + 1.0973101763703901e-15)) + -2.4667710277204801e-12)) + 1.6397259641437801e-11);
	fConst348 = (fConst277 * ((fConst0 * (2.8874224828152799e-18 - fConst275)) + -1.92187332455754e-17));
	fConst349 = ((fConst0 * ((fConst0 * (5.9968493040074702e-17 - fConst279)) + -1.4490803830035499e-13)) + 9.6339011758671695e-13);
	fConst350 = (fConst0 * ((fConst0 * ((fConst0 * (fConst281 + -9.5912241386039909e-19)) + 2.3184034538722398e-15)) + -1.5413424062951501e-14));
	fConst351 = ((fConst0 * ((fConst0 * (fConst273 + -1.82089564663e-16)) + 7.34564519198978e-15)) + -4.0890921799096699e-14);
	fConst352 = ((fConst0 * (fConst273 + -1.7605995289819199e-18)) + 9.8138212317832004e-18);
	fConst353 = ((fConst0 * ((fConst0 * (1.21495106849477e-19 - fConst275)) + -5.91080564497569e-16)) + 3.9353423139450596e-15);
	fConst354 = (fConst277 * (fConst275 + -4.6124959789380998e-21));
	fConst355 = ((fConst0 * (fConst279 + -3.47224379213122e-17)) + 2.3121362822081199e-16);
	fConst356 = (fConst0 * ((fConst0 * (5.5552901570331097e-19 - fConst281)) + -3.6992217751083603e-18));
	fConst357 = ((fConst0 * (1.7605995289819199e-18 - fConst273)) + -9.8138212317832004e-18);
	double fConst358 = (3.6926461476563902e-17 * fConst277);
	fConst359 = (fConst0 * (2.5655571744624101e-11 - fConst358));
	double fConst360 = (1.1806419655772101e-18 * fConst0);
	fConst361 = ((fConst277 * (-5.3412809636266102e-15 - fConst360)) + 1.29246313109701e-11);
	double fConst362 = (2.3471395789560598e-19 * fConst0);
	fConst363 = ((fConst277 * (1.0245708761442199e-15 - fConst362)) + -1.55221749291264e-12);
	double fConst364 = (2.6157908389502699e-19 * fConst0);
	fConst365 = (fConst277 * (fConst364 + 1.7265174707792101e-17));
	double fConst366 = (3.5228152231118703e-18 * fConst277);
	fConst367 = (5.16835993122826e-13 - fConst366);
	double fConst368 = (1.1263422822194399e-19 * fConst0);
	fConst369 = ((fConst277 * (-4.3250434803814798e-16 - fConst368)) + 3.9852237365987899e-14);
	double fConst370 = (2.7218277645506301e-20 * fConst0);
	fConst371 = (7.7397955421052495e-17 - fConst370);
	double fConst372 = (1.94416268896473e-20 * fConst0);
	fConst373 = (fConst372 + 1.24382763314569e-19);
	double fConst374 = (8.51295066784983e-19 * fConst277);
	fConst375 = (-6.2138452821831494e-14 - fConst374);
	fConst376 = (6.08067904846417e-19 * fConst277);
	double fConst377 = (7.3410535767348997e-18 * fConst277);
	fConst378 = (-5.1193482688036201e-12 - fConst377);
	double fConst379 = (8.1813032622487096e-18 * fConst277);
	fConst380 = (fConst379 + -6.5367111784464996e-15);
	fConst381 = ((1.7709629483658201e-18 * fConst277) + -7.5896518706863803e-13);
	fConst382 = ((3.5207093684340799e-19 * fConst277) + 1.3755352841510101e-13);
	fConst383 = (1.9451347028980501e-16 - (3.9236862584254002e-19 * fConst277));
	fConst384 = ((1.68951342332916e-19 * fConst277) + -8.7642608860271497e-15);
	fConst385 = ((4.0827416468259401e-20 * fConst277) + 9.9257445125025999e-16);
	fConst386 = (3.3066538877053999e-13 * fConst277);
	fConst387 = (fConst0 * (fConst358 + -2.5655571744624101e-11));
	fConst388 = ((fConst277 * (5.3412809636266102e-15 - fConst360)) + -1.29246313109701e-11);
	fConst389 = ((fConst277 * (-1.0245708761442199e-15 - fConst362)) + 1.55221749291264e-12);
	fConst390 = (fConst277 * (fConst364 + -1.7265174707792101e-17));
	fConst391 = (fConst366 + -5.16835993122826e-13);
	fConst392 = ((fConst277 * (4.3250434803814798e-16 - fConst368)) + -3.9852237365987899e-14);
	fConst393 = (-7.7397955421052495e-17 - fConst370);
	fConst394 = (fConst372 + -1.24382763314569e-19);
	fConst395 = (fConst374 + 6.2138452821831494e-14);
	fConst396 = (fConst377 + 5.1193482688036201e-12);
	fConst397 = (6.5367111784464996e-15 - fConst379);
	double fConst398 = (1.8463230738282e-17 * fConst0);
	fConst399 = (fConst0 * ((fConst0 * (1.6533269438526999e-13 - fConst398)) + -1.2827785872312101e-11));
	double fConst400 = (2.9516049139430401e-19 * fConst0);
	fConst401 = ((fConst0 * ((fConst0 * (fConst400 + -2.6706404818133099e-15)) + 3.7948259353431901e-13)) + -6.4623156554850397e-12);
	double fConst402 = (5.86784894739014e-20 * fConst0);
	fConst403 = ((fConst0 * ((fConst0 * (fConst402 + 5.1228543807211202e-16)) + -6.8776764207550403e-14)) + 7.7610874645632099e-13);
	double fConst404 = (6.5394770973756699e-20 * fConst0);
	fConst405 = (fConst0 * ((fConst0 * (8.6325873538960399e-18 - fConst404)) + -9.7256735144902295e-17));
	double fConst406 = (1.7614076115559301e-18 * fConst0);
	fConst407 = ((fConst0 * (1.3519218349390101e-14 - fConst406)) + -2.58417996561413e-13);
	double fConst408 = (2.8158557055485999e-20 * fConst0);
	fConst409 = ((fConst0 * ((fConst0 * (fConst408 + -2.1625217401907399e-16)) + 4.3821304430135804e-15)) + -1.9926118682993899e-14);
	double fConst410 = (6.8045694113765693e-21 * fConst0);
	fConst411 = ((fConst0 * (fConst410 + 3.8698977710526198e-17)) + -4.9628722562513e-16);
	double fConst412 = (4.8604067224118302e-21 * fConst0);
	fConst413 = (fConst0 * (6.21913816572845e-20 - fConst412));
	double fConst414 = (4.2564753339249198e-19 * fConst0);
	fConst415 = ((fConst0 * (-2.4226887258580501e-15 - fConst414)) + 3.1069226410915703e-14);
	double fConst416 = (3.0403395242320802e-19 * fConst0);
	fConst417 = (fConst0 * (fConst416 + -3.8902694057960899e-18));
	double fConst418 = (3.6705267883674499e-18 * fConst0);
	fConst419 = ((fConst0 * (-3.2490595714095e-14 - fConst418)) + 2.5596741344018101e-12);
	double fConst420 = (4.0906516311243602e-18 * fConst0);
	fConst421 = ((fConst0 * (fConst420 + -3.1996842386607998e-16)) + 3.2683555892232498e-15);
	fConst422 = (fConst0 * ((fConst0 * (fConst398 + 1.6533269438526999e-13)) + 1.2827785872312101e-11));
	fConst423 = ((fConst0 * ((fConst0 * (fConst400 + 2.6706404818133099e-15)) + 3.7948259353431901e-13)) + 6.4623156554850397e-12);
	fConst424 = ((fConst0 * ((fConst0 * (fConst402 + -5.1228543807211202e-16)) + -6.8776764207550403e-14)) + -7.7610874645632099e-13);
	fConst425 = (fConst0 * ((fConst0 * (-8.6325873538960399e-18 - fConst404)) + -9.7256735144902295e-17));
	fConst426 = ((fConst0 * (fConst406 + 1.3519218349390101e-14)) + 2.58417996561413e-13);
	fConst427 = ((fConst0 * ((fConst0 * (fConst408 + 2.1625217401907399e-16)) + 4.3821304430135804e-15)) + 1.9926118682993899e-14);
	fConst428 = ((fConst0 * (fConst410 + -3.8698977710526198e-17)) + -4.9628722562513e-16);
	fConst429 = (fConst0 * (-6.21913816572845e-20 - fConst412));
	fConst430 = ((fConst0 * (fConst414 + -2.4226887258580501e-15)) + -3.1069226410915703e-14);
	fConst431 = (fConst0 * (-3.8902694057960899e-18 - fConst416));
	fConst432 = ((fConst0 * (fConst418 + -3.2490595714095e-14)) + -2.5596741344018101e-12);
	fConst433 = ((fConst0 * (-3.1996842386607998e-16 - fConst420)) + -3.2683555892232498e-15);
	double fConst434 = (7.3739044618719696e-16 * fConst0);
	fConst435 = ((fConst0 * (-2.9997244001356698e-14 - fConst434)) + -1.67208717956279e-13);
	double fConst436 = (1.1788214615917801e-17 * fConst0);
	fConst437 = ((fConst0 * ((fConst0 * (-2.0700439282987502e-15 - fConst436)) + -1.0070880757276e-11)) + -6.7050695900467804e-11);
	fConst438 = (fConst277 * (fConst436 + 7.85880974394511e-17));
	double fConst439 = (1.03234662466208e-16 * fConst0);
	fConst440 = ((fConst0 * (-5.9160384034060297e-13 - fConst439)) + -3.9394373950499296e-12);
	double fConst441 = (1.65035004622849e-18 * fConst0);
	fConst442 = (fConst0 * ((fConst0 * (-9.4651504556075802e-15 - fConst441)) + -6.30276541464398e-14));
	fConst443 = ((fConst0 * (fConst434 + 2.9997244001356698e-14)) + 1.67208717956279e-13);
	double fConst444 = (1.47478089237439e-15 * fConst277);
	fConst445 = (fConst444 + -3.34417435912558e-13);
	double fConst446 = (4.7152858463671098e-17 * fConst0);
	fConst447 = ((fConst277 * (fConst446 + 4.1400878565975003e-15)) + -1.34101391800936e-10);
	fConst448 = (fConst277 * (-1.57176194878902e-16 - fConst446));
	double fConst449 = (2.0646932493241501e-16 * fConst277);
	fConst450 = (fConst449 + -7.8788747900998592e-12);
	double fConst451 = (6.6014001849139498e-18 * fConst0);
	fConst452 = (fConst277 * (fConst451 + 1.8930300911215201e-14));
	fConst453 = (3.34417435912558e-13 - fConst444);
	fConst454 = (7.0729287695506699e-17 * fConst277);
	fConst455 = (2.0141761514552e-11 - fConst454);
	fConst456 = (1.2605530829288e-13 - (9.9021002773709305e-18 * fConst277));
	fConst457 = ((fConst277 * (fConst446 + -4.1400878565975003e-15)) + 1.34101391800936e-10);
	fConst458 = (fConst277 * (1.57176194878902e-16 - fConst446));
	fConst459 = (7.8788747900998592e-12 - fConst449);
	fConst460 = (fConst277 * (fConst451 + -1.8930300911215201e-14));
	fConst461 = ((fConst0 * (fConst434 + -2.9997244001356698e-14)) + 1.67208717956279e-13);
	fConst462 = ((fConst0 * ((fConst0 * (2.0700439282987502e-15 - fConst436)) + -1.0070880757276e-11)) + 6.7050695900467804e-11);
	fConst463 = (fConst277 * (fConst436 + -7.85880974394511e-17));
	fConst464 = ((fConst0 * (fConst439 + -5.9160384034060297e-13)) + 3.9394373950499296e-12);
	fConst465 = (fConst0 * ((fConst0 * (9.4651504556075802e-15 - fConst441)) + -6.30276541464398e-14));
	fConst466 = ((fConst0 * (2.9997244001356698e-14 - fConst434)) + -1.67208717956279e-13);
	fConst467 = (1.0 / fConst2);
	fConst468 = (5.3661446356128799e-08 - (8.6772983871602696e-10 * fConst277));
	fConst469 = ((fConst0 * (fConst1 + -7.8166451752789406e-09)) + 2.6830723178064399e-08);
	fConst470 = (5.0856938050741003e-08 * fConst0);
	fConst471 = (1.69523126835804e-07 - fConst4);
	fConst472 = (1.0 / (((fConst19 + 1.0000000000000004) / fConst18) + 1.0));
	fConst473 = (1.0 / (fConst18 * fConst20));
	fConst474 = (0.0 - fConst473);
	fConst475 = (fConst22 / fConst20);
	fConst476 = (((fConst19 + -1.0000000000000004) / fConst18) + 1.0);
	fConst477 = (0.0 - (2.0 / fConst24));
	fConst478 = (1.0 / (((fConst28 + 1.0000000000000004) / fConst27) + 1.0));
	fConst479 = (1.0 / (fConst27 * fConst29));
	fConst480 = (1.0 / fConst20);
	fConst481 = (0.0 - fConst479);
	fConst482 = (fConst31 / fConst29);
	fConst483 = (((fConst28 + -1.0000000000000004) / fConst27) + 1.0);
	fConst484 = (0.0 - (2.0 / fConst33));
	fConst485 = (1.0 / (((fConst37 + 1.0000000000000004) / fConst36) + 1.0));
	fConst486 = (1.0 / (fConst36 * fConst38));
	fConst487 = (1.0 / fConst29);
	fConst488 = (0.0 - fConst486);
	fConst489 = (fConst40 / fConst38);
	fConst490 = (((fConst37 + -1.0000000000000004) / fConst36) + 1.0);
	fConst491 = (0.0 - (2.0 / fConst42));
	fConst492 = (1.0 / fConst38);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fVslider0 (*fVslider0_)
#define fCheckbox0 (*fCheckbox0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
#define fVslider4 (*fVslider4_)
#define fVslider5 (*fVslider5_)
#define fCheckbox1 (*fCheckbox1_)
#define fVslider6 (*fVslider6_)
#define fVslider7 (*fVslider7_)
#define fVslider8 (*fVslider8_)
#define fVslider9 (*fVslider9_)
	double fSlow0 = (0.00036676987543879196 * (std::exp((3.0 * double(fVslider0))) + -1.0));
	int iSlow1 = int(double(fCheckbox0));
	double fSlow2 = (0.00036676987543879196 * (std::exp((3.0 * double(fVslider1))) + -1.0));
	double fSlow3 = (0.00036676987543879196 * (std::exp((3.0 * double(fVslider2))) + -1.0));
	double fSlow4 = (0.0070000000000000062 * (1.0 - double(fVslider3)));
	double fSlow5 = (0.0070000000000000062 * double(fVslider4));
	double fSlow6 = (0.00036676987543879196 * (std::exp((3.0 * double(fVslider5))) + -1.0));
	int iSlow7 = int(double(fCheckbox1));
	double fSlow8 = (0.00036676987543879196 * (std::exp((3.0 * double(fVslider6))) + -1.0));
	double fSlow9 = (0.00036676987543879196 * (std::exp((3.0 * double(fVslider7))) + -1.0));
	double fSlow10 = (0.0070000000000000062 * (1.0 - double(fVslider8)));
	double fSlow11 = (0.0070000000000000062 * double(fVslider9));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		fRec0[0] = (fSlow0 + (0.99299999999999999 * fRec0[1]));
		fRec2[0] = (fSlow2 + (0.99299999999999999 * fRec2[1]));
		double fTemp0 = double(input0[i0]);
		fVec0[0] = fTemp0;
		fRec8[0] = ((fConst12 * fVec0[1]) - (fConst13 * ((fConst14 * fRec8[1]) - (fConst7 * fTemp0))));
		fRec7[0] = (fRec8[0] - (fConst8 * ((fConst15 * fRec7[2]) + (fConst16 * fRec7[1]))));
		double fTemp1 = (fConst26 * fRec6[1]);
		fRec6[0] = ((fConst8 * (((fConst10 * fRec7[0]) + (fConst17 * fRec7[1])) + (fConst10 * fRec7[2]))) - (fConst21 * ((fConst23 * fRec6[2]) + fTemp1)));
		double fTemp2 = (fConst35 * fRec5[1]);
		fRec5[0] = ((fRec6[2] + (fConst21 * (fTemp1 + (fConst23 * fRec6[0])))) - (fConst30 * ((fConst32 * fRec5[2]) + fTemp2)));
		double fTemp3 = (fConst44 * fRec4[1]);
		fRec4[0] = ((fRec5[2] + (fConst30 * (fTemp2 + (fConst32 * fRec5[0])))) - (fConst39 * ((fConst41 * fRec4[2]) + fTemp3)));
		double fTemp4 = (fRec4[2] + (fConst39 * (fTemp3 + (fConst41 * fRec4[0]))));
		fRec9[0] = (fSlow3 + (0.99299999999999999 * fRec9[1]));
		fRec10[0] = (fSlow4 + (0.99299999999999999 * fRec10[1]));
		fRec11[0] = (fSlow5 + (0.99299999999999999 * fRec11[1]));
		double fTemp5 = (((((fRec9[0] * ((fConst0 * (fConst46 + (fRec10[0] * (fConst48 + (fConst50 * fRec10[0]))))) + 3.2003439011230903e-11)) + (fRec11[0] * ((fConst0 * (fConst52 + ((fRec9[0] * (fConst54 + (fConst0 * (fRec10[0] * (fConst56 + (fConst58 * fRec10[0])))))) + (fRec10[0] * (fConst60 + (fConst62 * fRec10[0])))))) + 1.2801375604492301e-12))) + (fRec10[0] * ((fConst0 * (fConst64 + (fConst66 * fRec10[0]))) + -3.2003439011230903e-11))) + (fConst0 * (fConst68 + (fRec2[0] * (fConst70 + ((((fRec9[0] * (fConst72 + (fConst0 * (fRec10[0] * (fConst73 + (fConst74 * fRec10[0])))))) + (fRec11[0] * (fConst76 + (fConst0 * ((fRec9[0] * (fConst78 + (fConst0 * (fRec10[0] * (fConst79 + (fConst80 * fRec10[0])))))) + (fRec10[0] * (fConst81 + (fConst82 * fRec10[0])))))))) + (fRec10[0] * (fConst83 + (fConst84 * fRec10[0])))) + (fRec2[0] * (fConst86 + (fConst0 * ((fRec11[0] * (fConst88 + (fConst90 * fRec9[0]))) + (fConst92 * fRec9[0]))))))))))) + 1.6001719505615401e-10);
		double fTemp6 = (((((fRec9[0] * ((fConst0 * (fConst94 + (fRec10[0] * (fConst96 + (fConst98 * fRec10[0]))))) + 6.4006878022461703e-11)) + (fRec11[0] * ((fConst0 * (fConst100 + ((fRec9[0] * (fConst102 + (fConst0 * (fRec10[0] * (fConst104 + (fConst106 * fRec10[0])))))) + (fRec10[0] * (fConst108 + (fConst110 * fRec10[0])))))) + 2.5602751208984699e-12))) + (fRec10[0] * ((fConst0 * (fConst112 + (fConst114 * fRec10[0]))) + -6.4006878022461703e-11))) + (fConst0 * (fConst116 + (fRec2[0] * (fConst118 + ((((fRec9[0] * (fConst120 + (fConst0 * (fRec10[0] * (fConst121 + (fConst122 * fRec10[0])))))) + (fRec11[0] * (fConst124 + (fConst0 * ((fRec9[0] * (fConst126 + (fConst0 * (fRec10[0] * (fConst127 + (fConst128 * fRec10[0])))))) + (fRec10[0] * (fConst129 + (fConst130 * fRec10[0])))))))) + (fRec10[0] * (fConst131 + (fConst132 * fRec10[0])))) + (fRec2[0] * (fConst134 + (fConst0 * ((fRec11[0] * (fConst136 + (fConst138 * fRec9[0]))) + (fConst140 * fRec9[0]))))))))))) + 3.2003439011230801e-10);
		double fTemp7 = (((((fRec9[0] * ((fConst0 * (fConst141 + (fRec10[0] * (fConst142 + (fConst143 * fRec10[0]))))) + 6.4006878022461703e-11)) + (fRec11[0] * ((fConst0 * (fConst144 + ((fRec9[0] * (fConst145 + (fConst0 * (fRec10[0] * (fConst146 + (fConst147 * fRec10[0])))))) + (fRec10[0] * (fConst148 + (fConst149 * fRec10[0])))))) + 2.5602751208984699e-12))) + (fRec10[0] * ((fConst0 * (fConst150 + (fConst151 * fRec10[0]))) + -6.4006878022461703e-11))) + (fConst0 * (fConst152 + (fRec2[0] * (fConst153 + ((((fRec9[0] * (fConst154 + (fConst0 * (fRec10[0] * (fConst155 + (fConst156 * fRec10[0])))))) + (fRec11[0] * (fConst157 + (fConst0 * ((fRec9[0] * (fConst158 + (fConst0 * (fRec10[0] * (fConst159 + (fConst160 * fRec10[0])))))) + (fRec10[0] * (fConst161 + (fConst162 * fRec10[0])))))))) + (fRec10[0] * (fConst163 + (fConst164 * fRec10[0])))) + (fRec2[0] * (fConst165 + (fConst0 * ((fRec11[0] * (fConst166 + (fConst167 * fRec9[0]))) + (fConst168 * fRec9[0]))))))))))) + 3.2003439011230801e-10);
		double fTemp8 = (((((fRec9[0] * ((fConst0 * (fConst169 + (fRec10[0] * (fConst170 + (fConst171 * fRec10[0]))))) + 3.2003439011230903e-11)) + (fRec11[0] * ((fConst0 * (fConst172 + ((fRec9[0] * (fConst173 + (fConst0 * (fRec10[0] * (fConst174 + (fConst175 * fRec10[0])))))) + (fRec10[0] * (fConst176 + (fConst177 * fRec10[0])))))) + 1.2801375604492301e-12))) + (fRec10[0] * ((fConst0 * (fConst178 + (fConst179 * fRec10[0]))) + -3.2003439011230903e-11))) + (fConst0 * (fConst180 + (fRec2[0] * (fConst181 + ((((fRec9[0] * (fConst182 + (fConst0 * (fRec10[0] * (fConst183 + (fConst184 * fRec10[0])))))) + (fRec11[0] * (fConst185 + (fConst0 * ((fRec9[0] * (fConst186 + (fConst0 * (fRec10[0] * (fConst187 + (fConst188 * fRec10[0])))))) + (fRec10[0] * (fConst189 + (fConst190 * fRec10[0])))))))) + (fRec10[0] * (fConst191 + (fConst192 * fRec10[0])))) + (fRec2[0] * (fConst193 + (fConst0 * ((fRec11[0] * (fConst194 + (fConst195 * fRec9[0]))) + (fConst196 * fRec9[0]))))))))))) + 1.6001719505615401e-10);
		double fTemp9 = (((((fRec9[0] * ((fConst0 * (fConst198 + (fRec10[0] * (fConst200 + (fConst202 * fRec10[0]))))) + 6.40068780224617e-12)) + (fRec11[0] * ((fConst0 * (fConst204 + ((fRec9[0] * (fConst206 + (fConst0 * (fRec10[0] * (fConst208 + (fConst210 * fRec10[0])))))) + (fRec10[0] * (fConst212 + (fConst214 * fRec10[0])))))) + 2.5602751208984701e-13))) + (fRec10[0] * ((fConst0 * (fConst216 + (fConst218 * fRec10[0]))) + -6.40068780224617e-12))) + (fConst0 * (fConst220 + (fRec2[0] * (fConst222 + ((((fRec9[0] * (fConst224 + (fConst0 * (fRec10[0] * (fConst225 + (fConst226 * fRec10[0])))))) + (fRec11[0] * (fConst228 + (fConst0 * ((fRec9[0] * (fConst230 + (fConst0 * (fRec10[0] * (fConst231 + (fConst232 * fRec10[0])))))) + (fRec10[0] * (fConst233 + (fConst234 * fRec10[0])))))))) + (fRec10[0] * (fConst235 + (fConst236 * fRec10[0])))) + (fRec2[0] * (fConst238 + (fConst0 * ((fRec11[0] * (fConst240 + (fConst242 * fRec9[0]))) + (fConst244 * fRec9[0]))))))))))) + 3.2003439011230903e-11);
		double fTemp10 = (((((fRec9[0] * ((fConst0 * (fConst245 + (fRec10[0] * (fConst246 + (fConst247 * fRec10[0]))))) + 6.40068780224617e-12)) + (fRec11[0] * ((fConst0 * (fConst248 + ((fRec9[0] * (fConst249 + (fConst0 * (fRec10[0] * (fConst250 + (fConst251 * fRec10[0])))))) + (fRec10[0] * (fConst252 + (fConst253 * fRec10[0])))))) + 2.5602751208984701e-13))) + (fRec10[0] * ((fConst0 * (fConst254 + (fConst255 * fRec10[0]))) + -6.40068780224617e-12))) + (fConst0 * (fConst256 + (fRec2[0] * (fConst257 + ((((fRec9[0] * (fConst258 + (fConst0 * (fRec10[0] * (fConst259 + (fConst260 * fRec10[0])))))) + (fRec11[0] * (fConst261 + (fConst0 * ((fRec9[0] * (fConst262 + (fConst0 * (fRec10[0] * (fConst263 + (fConst264 * fRec10[0])))))) + (fRec10[0] * (fConst265 + (fConst266 * fRec10[0])))))))) + (fRec10[0] * (fConst267 + (fConst268 * fRec10[0])))) + (fRec2[0] * (fConst269 + (fConst0 * ((fRec11[0] * (fConst270 + (fConst271 * fRec9[0]))) + (fConst272 * fRec9[0]))))))))))) + 3.2003439011230903e-11);
		fRec3[0] = (fTemp4 - ((((((fRec3[1] * fTemp5) + (fRec3[2] * fTemp6)) + (fRec3[3] * fTemp7)) + (fRec3[4] * fTemp8)) + (fRec3[5] * fTemp9)) / fTemp10));
		double fTemp11 = (fConst274 + ((((fRec9[0] * (fConst276 + (fConst278 * fRec10[0]))) + (fRec11[0] * (fConst280 + (fConst282 * fRec9[0])))) + (fConst283 * fRec10[0])) + (fConst0 * (fRec2[0] * (fConst284 + (((fRec9[0] * (fConst285 + (fConst286 * fRec10[0]))) + (fRec11[0] * (fConst287 + (fConst288 * fRec9[0])))) + (fConst289 * fRec10[0])))))));
		double fTemp12 = (fConst291 + ((((fRec9[0] * (fConst293 + (fConst294 * fRec10[0]))) + (fRec11[0] * (fConst296 + (fConst298 * fRec9[0])))) + (fConst299 * fRec10[0])) + (fConst0 * (fRec2[0] * (fConst300 + (((fRec9[0] * (fConst301 + (fConst302 * fRec10[0]))) + (fRec11[0] * (fConst303 + (fConst304 * fRec9[0])))) + (fConst305 * fRec10[0])))))));
		double fTemp13 = (fConst307 + ((((fRec9[0] * (fConst309 + (fConst310 * fRec10[0]))) + (fRec11[0] * (fConst312 + (fConst314 * fRec9[0])))) + (fConst315 * fRec10[0])) + (fConst0 * (fRec2[0] * (fConst316 + (((fRec9[0] * (fConst317 + (fConst318 * fRec10[0]))) + (fRec11[0] * (fConst319 + (fConst320 * fRec9[0])))) + (fConst321 * fRec10[0])))))));
		double fTemp14 = (fConst322 + ((((fRec9[0] * (fConst323 + (fConst324 * fRec10[0]))) + (fRec11[0] * (fConst325 + (fConst326 * fRec9[0])))) + (fConst327 * fRec10[0])) + (fConst0 * (fRec2[0] * (fConst328 + (((fRec9[0] * (fConst329 + (fConst330 * fRec10[0]))) + (fRec11[0] * (fConst331 + (fConst332 * fRec9[0])))) + (fConst333 * fRec10[0])))))));
		double fTemp15 = (fConst334 + ((((fRec9[0] * (fConst335 + (fConst336 * fRec10[0]))) + (fRec11[0] * (fConst337 + (fConst338 * fRec9[0])))) + (fConst339 * fRec10[0])) + (fConst0 * (fRec2[0] * (fConst340 + (((fRec9[0] * (fConst341 + (fConst342 * fRec10[0]))) + (fRec11[0] * (fConst343 + (fConst344 * fRec9[0])))) + (fConst345 * fRec10[0])))))));
		double fTemp16 = (fConst346 + ((((fRec9[0] * (fConst347 + (fConst348 * fRec10[0]))) + (fRec11[0] * (fConst349 + (fConst350 * fRec9[0])))) + (fConst351 * fRec10[0])) + (fConst0 * (fRec2[0] * (fConst352 + (((fRec9[0] * (fConst353 + (fConst354 * fRec10[0]))) + (fRec11[0] * (fConst355 + (fConst356 * fRec9[0])))) + (fConst357 * fRec10[0])))))));
		double fTemp17 = (fConst0 * ((fRec2[0] * ((((((fRec3[0] * fTemp11) + (fRec3[1] * fTemp12)) + (fRec3[2] * fTemp13)) + (fRec3[3] * fTemp14)) + (fRec3[4] * fTemp15)) + (fRec3[5] * fTemp16))) / fTemp10));
		double fThen0 = double(alembic_briteclip(double(fTemp17)));
		double fElse0 = double(alembic_brite_negclip(double(fTemp17)));
		double fTemp18 = (fConst359 + ((((fRec9[0] * ((fConst0 * (fConst361 + (fRec10[0] * (fConst363 + (fConst365 * fRec10[0]))))) + 1.0469323652605e-10)) + (fRec11[0] * ((fConst0 * (fConst367 + ((fRec9[0] * (fConst369 + (fConst277 * (fRec10[0] * (fConst371 + (fConst373 * fRec10[0])))))) + (fRec10[0] * (fConst375 + (fConst376 * fRec10[0])))))) + 4.1877294610420001e-12))) + (fRec10[0] * ((fConst0 * (fConst378 + (fConst380 * fRec10[0]))) + -1.0469323652605e-10))) + 5.2346618263024998e-10));
		double fTemp19 = (((((fRec9[0] * ((fConst277 * (fConst381 + (fRec10[0] * (fConst382 + (fConst383 * fRec10[0]))))) + 1.57039854789075e-10)) + (fRec11[0] * ((fConst277 * (((fRec9[0] * (fConst384 + (fRec10[0] * (fConst385 + (fConst277 * (0.0 - (2.9162440334471001e-20 * fRec10[0]))))))) + (fRec10[0] * ((7.7805388115921905e-18 * fRec10[0]) + 4.8453774517161096e-15))) + -2.7038436698780101e-14)) + 6.2815941915630002e-12))) + (fRec10[0] * ((fConst277 * ((6.3993684773215997e-16 * fRec10[0]) + 6.4981191428189999e-14)) + -1.57039854789075e-10))) + 7.8519927394537503e-10) - fConst386);
		double fTemp20 = (fConst387 + ((((fRec9[0] * ((fConst0 * (fConst388 + (fRec10[0] * (fConst389 + (fConst390 * fRec10[0]))))) + 1.0469323652605e-10)) + (fRec11[0] * ((fConst0 * (fConst391 + ((fRec9[0] * (fConst392 + (fConst277 * (fRec10[0] * (fConst393 + (fConst394 * fRec10[0])))))) + (fRec10[0] * (fConst395 + (fConst277 * (0.0 - (6.08067904846417e-19 * fRec10[0])))))))) + 4.1877294610420001e-12))) + (fRec10[0] * ((fConst0 * (fConst396 + (fConst397 * fRec10[0]))) + -1.0469323652605e-10))) + 5.2346618263024998e-10));
		double fTemp21 = (fConst399 + ((((fRec9[0] * ((fConst0 * (fConst401 + (fRec10[0] * (fConst403 + (fConst405 * fRec10[0]))))) + 2.6173309131512501e-11)) + (fRec11[0] * ((fConst0 * (fConst407 + ((fRec9[0] * (fConst409 + (fConst0 * (fRec10[0] * (fConst411 + (fConst413 * fRec10[0])))))) + (fRec10[0] * (fConst415 + (fConst417 * fRec10[0])))))) + 1.0469323652605e-12))) + (fRec10[0] * ((fConst0 * (fConst419 + (fConst421 * fRec10[0]))) + -2.6173309131512501e-11))) + 1.3086654565756201e-10));
		double fTemp22 = (fConst422 + ((((fRec9[0] * ((fConst0 * (fConst423 + (fRec10[0] * (fConst424 + (fConst425 * fRec10[0]))))) + 2.6173309131512501e-11)) + (fRec11[0] * ((fConst0 * (fConst426 + ((fRec9[0] * (fConst427 + (fConst0 * (fRec10[0] * (fConst428 + (fConst429 * fRec10[0])))))) + (fRec10[0] * (fConst430 + (fConst431 * fRec10[0])))))) + 1.0469323652605e-12))) + (fRec10[0] * ((fConst0 * (fConst432 + (fConst433 * fRec10[0]))) + -2.6173309131512501e-11))) + 1.3086654565756201e-10));
		fRec12[0] = (fTemp4 - (((((fRec12[1] * fTemp18) + (fRec12[2] * fTemp19)) + (fRec12[3] * fTemp20)) + (fRec12[4] * fTemp21)) / fTemp22));
		double fTemp23 = (fConst435 + (((fRec9[0] * (fConst437 + (fConst438 * fRec10[0]))) + (fRec11[0] * (fConst440 + (fConst442 * fRec9[0])))) + (fConst443 * fRec10[0])));
		double fTemp24 = (fConst445 + (((fRec9[0] * (fConst447 + (fConst448 * fRec10[0]))) + (fRec11[0] * (fConst450 + (fConst452 * fRec9[0])))) + (fConst453 * fRec10[0])));
		double fTemp25 = ((((fRec9[0] * (fConst455 + (fConst454 * fRec10[0]))) + (fRec11[0] * ((fConst456 * fRec9[0]) + 1.18320768068121e-12))) - (5.9994488002713396e-14 * fRec10[0])) + 5.9994488002713396e-14);
		double fTemp26 = (fConst453 + (((fRec9[0] * (fConst457 + (fConst458 * fRec10[0]))) + (fRec11[0] * (fConst459 + (fConst460 * fRec9[0])))) + (fConst445 * fRec10[0])));
		double fTemp27 = (fConst461 + (((fRec9[0] * (fConst462 + (fConst463 * fRec10[0]))) + (fRec11[0] * (fConst464 + (fConst465 * fRec9[0])))) + (fConst466 * fRec10[0])));
		double fTemp28 = (fConst0 * ((fRec2[0] * (((((fRec12[0] * fTemp23) + (fRec12[1] * fTemp24)) + (fConst0 * (fRec12[2] * fTemp25))) + (fRec12[3] * fTemp26)) + (fRec12[4] * fTemp27))) / fTemp22));
		double fThen1 = double(alembic_normclip(double(fTemp28)));
		double fElse1 = double(alembic_norm_negclip(double(fTemp28)));
		double fThen2 = (int(signbit(double(fTemp17))) ? fElse0 : fThen0);
		double fElse2 = (int(signbit(double(fTemp28))) ? fElse1 : fThen1);
		fRec1[0] = ((iSlow1 ? fElse2 : fThen2) - (fConst467 * ((fConst468 * fRec1[1]) + (fConst469 * fRec1[2]))));
		double fTemp29 = (fConst3 * (fRec0[0] * (((fConst5 * fRec1[0]) + (fConst470 * fRec1[1])) + (fConst471 * fRec1[2]))));
		double fThen3 = double(alembic_outclip(double(fTemp29)));
		double fElse3 = double(alembic_out_negclip(double(fTemp29)));
		fRec20[0] = (0.0 - (fConst13 * ((fConst14 * fRec20[1]) - (fTemp0 + fVec0[1]))));
		fRec19[0] = (fRec20[0] - (fConst8 * ((fConst15 * fRec19[2]) + (fConst16 * fRec19[1]))));
		double fTemp30 = (fRec19[2] + (fRec19[0] + (2.0 * fRec19[1])));
		fVec1[0] = fTemp30;
		fRec18[0] = ((fConst8 * ((fConst473 * fTemp30) + (fConst474 * fVec1[1]))) - (fConst475 * fRec18[1]));
		fRec17[0] = (fRec18[0] - (fConst472 * ((fConst476 * fRec17[2]) + (fConst26 * fRec17[1]))));
		double fTemp31 = (fConst35 * fRec16[1]);
		fRec16[0] = ((fConst472 * (((fConst25 * fRec17[0]) + (fConst477 * fRec17[1])) + (fConst25 * fRec17[2]))) - (fConst30 * ((fConst32 * fRec16[2]) + fTemp31)));
		double fTemp32 = (fConst44 * fRec15[1]);
		fRec15[0] = ((fRec16[2] + (fConst30 * (fTemp31 + (fConst32 * fRec16[0])))) - (fConst39 * ((fConst41 * fRec15[2]) + fTemp32)));
		double fTemp33 = (fRec15[2] + (fConst39 * (fTemp32 + (fConst41 * fRec15[0]))));
		fRec14[0] = (fTemp33 - ((((((fTemp5 * fRec14[1]) + (fTemp6 * fRec14[2])) + (fTemp7 * fRec14[3])) + (fTemp8 * fRec14[4])) + (fTemp9 * fRec14[5])) / fTemp10));
		double fTemp34 = (fConst0 * ((fRec2[0] * ((((((fRec14[0] * fTemp11) + (fTemp12 * fRec14[1])) + (fTemp13 * fRec14[2])) + (fTemp14 * fRec14[3])) + (fTemp15 * fRec14[4])) + (fTemp16 * fRec14[5]))) / fTemp10));
		double fThen4 = double(alembic_briteclip(double(fTemp34)));
		double fElse4 = double(alembic_brite_negclip(double(fTemp34)));
		fRec21[0] = (fTemp33 - (((((fTemp18 * fRec21[1]) + (fTemp19 * fRec21[2])) + (fTemp20 * fRec21[3])) + (fTemp21 * fRec21[4])) / fTemp22));
		double fTemp35 = (fConst0 * ((fRec2[0] * (((((fRec21[0] * fTemp23) + (fTemp24 * fRec21[1])) + (fConst0 * (fTemp25 * fRec21[2]))) + (fTemp26 * fRec21[3])) + (fTemp27 * fRec21[4]))) / fTemp22));
		double fThen5 = double(alembic_normclip(double(fTemp35)));
		double fElse5 = double(alembic_norm_negclip(double(fTemp35)));
		double fThen6 = (int(signbit(double(fTemp34))) ? fElse4 : fThen4);
		double fElse6 = (int(signbit(double(fTemp35))) ? fElse5 : fThen5);
		fRec13[0] = ((iSlow1 ? fElse6 : fThen6) - (fConst467 * ((fConst468 * fRec13[1]) + (fConst469 * fRec13[2]))));
		double fTemp36 = (fConst3 * (fRec0[0] * (((fConst5 * fRec13[0]) + (fConst470 * fRec13[1])) + (fConst471 * fRec13[2]))));
		double fThen7 = double(alembic_outclip(double(fTemp36)));
		double fElse7 = double(alembic_out_negclip(double(fTemp36)));
		fRec28[0] = (0.0 - (fConst480 * ((fConst22 * fRec28[1]) - (fConst8 * (fTemp30 + fVec1[1])))));
		fRec27[0] = (fRec28[0] - (fConst472 * ((fConst476 * fRec27[2]) + (fConst26 * fRec27[1]))));
		double fTemp37 = (fRec27[2] + (fRec27[0] + (2.0 * fRec27[1])));
		fVec2[0] = fTemp37;
		fRec26[0] = ((fConst472 * ((fConst479 * fTemp37) + (fConst481 * fVec2[1]))) - (fConst482 * fRec26[1]));
		fRec25[0] = (fRec26[0] - (fConst478 * ((fConst483 * fRec25[2]) + (fConst35 * fRec25[1]))));
		double fTemp38 = (fConst44 * fRec24[1]);
		fRec24[0] = ((fConst478 * (((fConst34 * fRec25[0]) + (fConst484 * fRec25[1])) + (fConst34 * fRec25[2]))) - (fConst39 * ((fConst41 * fRec24[2]) + fTemp38)));
		double fTemp39 = (fRec24[2] + (fConst39 * (fTemp38 + (fConst41 * fRec24[0]))));
		fRec23[0] = (fTemp39 - ((((((fTemp5 * fRec23[1]) + (fTemp6 * fRec23[2])) + (fTemp7 * fRec23[3])) + (fTemp8 * fRec23[4])) + (fTemp9 * fRec23[5])) / fTemp10));
		double fTemp40 = (fConst0 * ((fRec2[0] * ((((((fRec23[0] * fTemp11) + (fTemp12 * fRec23[1])) + (fTemp13 * fRec23[2])) + (fTemp14 * fRec23[3])) + (fTemp15 * fRec23[4])) + (fTemp16 * fRec23[5]))) / fTemp10));
		double fThen8 = double(alembic_briteclip(double(fTemp40)));
		double fElse8 = double(alembic_brite_negclip(double(fTemp40)));
		fRec29[0] = (fTemp39 - (((((fTemp18 * fRec29[1]) + (fTemp19 * fRec29[2])) + (fTemp20 * fRec29[3])) + (fTemp21 * fRec29[4])) / fTemp22));
		double fTemp41 = (fConst0 * ((fRec2[0] * (((((fRec29[0] * fTemp23) + (fTemp24 * fRec29[1])) + (fConst0 * (fTemp25 * fRec29[2]))) + (fTemp26 * fRec29[3])) + (fTemp27 * fRec29[4]))) / fTemp22));
		double fThen9 = double(alembic_normclip(double(fTemp41)));
		double fElse9 = double(alembic_norm_negclip(double(fTemp41)));
		double fThen10 = (int(signbit(double(fTemp40))) ? fElse8 : fThen8);
		double fElse10 = (int(signbit(double(fTemp41))) ? fElse9 : fThen9);
		fRec22[0] = ((iSlow1 ? fElse10 : fThen10) - (fConst467 * ((fConst468 * fRec22[1]) + (fConst469 * fRec22[2]))));
		double fTemp42 = (fConst3 * (fRec0[0] * (((fConst5 * fRec22[0]) + (fConst470 * fRec22[1])) + (fConst471 * fRec22[2]))));
		double fThen11 = double(alembic_outclip(double(fTemp42)));
		double fElse11 = double(alembic_out_negclip(double(fTemp42)));
		fRec35[0] = (0.0 - (fConst487 * ((fConst31 * fRec35[1]) - (fConst472 * (fTemp37 + fVec2[1])))));
		fRec34[0] = (fRec35[0] - (fConst478 * ((fConst483 * fRec34[2]) + (fConst35 * fRec34[1]))));
		double fTemp43 = (fRec34[2] + (fRec34[0] + (2.0 * fRec34[1])));
		fVec3[0] = fTemp43;
		fRec33[0] = ((fConst478 * ((fConst486 * fTemp43) + (fConst488 * fVec3[1]))) - (fConst489 * fRec33[1]));
		fRec32[0] = (fRec33[0] - (fConst485 * ((fConst490 * fRec32[2]) + (fConst44 * fRec32[1]))));
		double fTemp44 = (fConst485 * (((fConst43 * fRec32[0]) + (fConst491 * fRec32[1])) + (fConst43 * fRec32[2])));
		fRec31[0] = (fTemp44 - ((((((fTemp5 * fRec31[1]) + (fTemp6 * fRec31[2])) + (fTemp7 * fRec31[3])) + (fTemp8 * fRec31[4])) + (fTemp9 * fRec31[5])) / fTemp10));
		double fTemp45 = (fConst0 * ((fRec2[0] * ((((((fRec31[0] * fTemp11) + (fTemp12 * fRec31[1])) + (fTemp13 * fRec31[2])) + (fTemp14 * fRec31[3])) + (fTemp15 * fRec31[4])) + (fTemp16 * fRec31[5]))) / fTemp10));
		double fThen12 = double(alembic_briteclip(double(fTemp45)));
		double fElse12 = double(alembic_brite_negclip(double(fTemp45)));
		fRec36[0] = (fTemp44 - (((((fTemp18 * fRec36[1]) + (fTemp19 * fRec36[2])) + (fTemp20 * fRec36[3])) + (fTemp21 * fRec36[4])) / fTemp22));
		double fTemp46 = (fConst0 * ((fRec2[0] * (((((fRec36[0] * fTemp23) + (fTemp24 * fRec36[1])) + (fConst0 * (fTemp25 * fRec36[2]))) + (fTemp26 * fRec36[3])) + (fTemp27 * fRec36[4]))) / fTemp22));
		double fThen13 = double(alembic_normclip(double(fTemp46)));
		double fElse13 = double(alembic_norm_negclip(double(fTemp46)));
		double fThen14 = (int(signbit(double(fTemp45))) ? fElse12 : fThen12);
		double fElse14 = (int(signbit(double(fTemp46))) ? fElse13 : fThen13);
		fRec30[0] = ((iSlow1 ? fElse14 : fThen14) - (fConst467 * ((fConst468 * fRec30[1]) + (fConst469 * fRec30[2]))));
		double fTemp47 = (fConst3 * (fRec0[0] * (((fConst5 * fRec30[0]) + (fConst470 * fRec30[1])) + (fConst471 * fRec30[2]))));
		double fThen15 = double(alembic_outclip(double(fTemp47)));
		double fElse15 = double(alembic_out_negclip(double(fTemp47)));
		fRec40[0] = (0.0 - (fConst492 * ((fConst40 * fRec40[1]) - (fConst478 * (fTemp43 + fVec3[1])))));
		fRec39[0] = (fRec40[0] - (fConst485 * ((fConst490 * fRec39[2]) + (fConst44 * fRec39[1]))));
		double fTemp48 = (fConst485 * (fRec39[2] + (fRec39[0] + (2.0 * fRec39[1]))));
		fRec38[0] = (fTemp48 - ((((((fTemp5 * fRec38[1]) + (fTemp6 * fRec38[2])) + (fTemp7 * fRec38[3])) + (fTemp8 * fRec38[4])) + (fTemp9 * fRec38[5])) / fTemp10));
		double fTemp49 = (fConst0 * ((fRec2[0] * ((((((fRec38[0] * fTemp11) + (fTemp12 * fRec38[1])) + (fTemp13 * fRec38[2])) + (fTemp14 * fRec38[3])) + (fTemp15 * fRec38[4])) + (fTemp16 * fRec38[5]))) / fTemp10));
		double fThen16 = double(alembic_briteclip(double(fTemp49)));
		double fElse16 = double(alembic_brite_negclip(double(fTemp49)));
		fRec41[0] = (fTemp48 - (((((fTemp18 * fRec41[1]) + (fTemp19 * fRec41[2])) + (fTemp20 * fRec41[3])) + (fTemp21 * fRec41[4])) / fTemp22));
		double fTemp50 = (fConst0 * ((fRec2[0] * (((((fRec41[0] * fTemp23) + (fTemp24 * fRec41[1])) + (fConst0 * (fTemp25 * fRec41[2]))) + (fTemp26 * fRec41[3])) + (fTemp27 * fRec41[4]))) / fTemp22));
		double fThen17 = double(alembic_normclip(double(fTemp50)));
		double fElse17 = double(alembic_norm_negclip(double(fTemp50)));
		double fThen18 = (int(signbit(double(fTemp49))) ? fElse16 : fThen16);
		double fElse18 = (int(signbit(double(fTemp50))) ? fElse17 : fThen17);
		fRec37[0] = ((iSlow1 ? fElse18 : fThen18) - (fConst467 * ((fConst468 * fRec37[1]) + (fConst469 * fRec37[2]))));
		double fTemp51 = (fConst3 * (fRec0[0] * (((fConst5 * fRec37[0]) + (fConst470 * fRec37[1])) + (fConst471 * fRec37[2]))));
		double fThen19 = double(alembic_outclip(double(fTemp51)));
		double fElse19 = double(alembic_out_negclip(double(fTemp51)));
		output0[i0] = FAUSTFLOAT((((((int(signbit(double(fTemp29))) ? fElse3 : fThen3) + (int(signbit(double(fTemp36))) ? fElse7 : fThen7)) + (int(signbit(double(fTemp42))) ? fElse11 : fThen11)) + (int(signbit(double(fTemp47))) ? fElse15 : fThen15)) + (int(signbit(double(fTemp51))) ? fElse19 : fThen19)));
		fRec42[0] = (fSlow6 + (0.99299999999999999 * fRec42[1]));
		fRec44[0] = (fSlow8 + (0.99299999999999999 * fRec44[1]));
		double fTemp52 = double(input1[i0]);
		fVec4[0] = fTemp52;
		fRec50[0] = ((fConst12 * fVec4[1]) - (fConst13 * ((fConst14 * fRec50[1]) - (fConst7 * fTemp52))));
		fRec49[0] = (fRec50[0] - (fConst8 * ((fConst15 * fRec49[2]) + (fConst16 * fRec49[1]))));
		double fTemp53 = (fConst26 * fRec48[1]);
		fRec48[0] = ((fConst8 * (((fConst10 * fRec49[0]) + (fConst17 * fRec49[1])) + (fConst10 * fRec49[2]))) - (fConst21 * ((fConst23 * fRec48[2]) + fTemp53)));
		double fTemp54 = (fConst35 * fRec47[1]);
		fRec47[0] = ((fRec48[2] + (fConst21 * (fTemp53 + (fConst23 * fRec48[0])))) - (fConst30 * ((fConst32 * fRec47[2]) + fTemp54)));
		double fTemp55 = (fConst44 * fRec46[1]);
		fRec46[0] = ((fRec47[2] + (fConst30 * (fTemp54 + (fConst32 * fRec47[0])))) - (fConst39 * ((fConst41 * fRec46[2]) + fTemp55)));
		double fTemp56 = (fRec46[2] + (fConst39 * (fTemp55 + (fConst41 * fRec46[0]))));
		fRec51[0] = (fSlow9 + (0.99299999999999999 * fRec51[1]));
		fRec52[0] = (fSlow10 + (0.99299999999999999 * fRec52[1]));
		fRec53[0] = (fSlow11 + (0.99299999999999999 * fRec53[1]));
		double fTemp57 = (((((fRec51[0] * ((fConst0 * (fConst46 + (fRec52[0] * (fConst48 + (fConst50 * fRec52[0]))))) + 3.2003439011230903e-11)) + (fRec53[0] * ((fConst0 * (fConst52 + ((fRec51[0] * (fConst54 + (fConst0 * (fRec52[0] * (fConst56 + (fConst58 * fRec52[0])))))) + (fRec52[0] * (fConst60 + (fConst62 * fRec52[0])))))) + 1.2801375604492301e-12))) + (fRec52[0] * ((fConst0 * (fConst64 + (fConst66 * fRec52[0]))) + -3.2003439011230903e-11))) + (fConst0 * (fConst68 + (fRec44[0] * (fConst70 + ((((fRec51[0] * (fConst72 + (fConst0 * (fRec52[0] * (fConst73 + (fConst74 * fRec52[0])))))) + (fRec53[0] * (fConst76 + (fConst0 * ((fRec51[0] * (fConst78 + (fConst0 * (fRec52[0] * (fConst79 + (fConst80 * fRec52[0])))))) + (fRec52[0] * (fConst81 + (fConst82 * fRec52[0])))))))) + (fRec52[0] * (fConst83 + (fConst84 * fRec52[0])))) + (fRec44[0] * (fConst86 + (fConst0 * ((fRec53[0] * (fConst88 + (fConst90 * fRec51[0]))) + (fConst92 * fRec51[0]))))))))))) + 1.6001719505615401e-10);
		double fTemp58 = (((((fRec51[0] * ((fConst0 * (fConst94 + (fRec52[0] * (fConst96 + (fConst98 * fRec52[0]))))) + 6.4006878022461703e-11)) + (fRec53[0] * ((fConst0 * (fConst100 + ((fRec51[0] * (fConst102 + (fConst0 * (fRec52[0] * (fConst104 + (fConst106 * fRec52[0])))))) + (fRec52[0] * (fConst108 + (fConst110 * fRec52[0])))))) + 2.5602751208984699e-12))) + (fRec52[0] * ((fConst0 * (fConst112 + (fConst114 * fRec52[0]))) + -6.4006878022461703e-11))) + (fConst0 * (fConst116 + (fRec44[0] * (fConst118 + ((((fRec51[0] * (fConst120 + (fConst0 * (fRec52[0] * (fConst121 + (fConst122 * fRec52[0])))))) + (fRec53[0] * (fConst124 + (fConst0 * ((fRec51[0] * (fConst126 + (fConst0 * (fRec52[0] * (fConst127 + (fConst128 * fRec52[0])))))) + (fRec52[0] * (fConst129 + (fConst130 * fRec52[0])))))))) + (fRec52[0] * (fConst131 + (fConst132 * fRec52[0])))) + (fRec44[0] * (fConst134 + (fConst0 * ((fRec53[0] * (fConst136 + (fConst138 * fRec51[0]))) + (fConst140 * fRec51[0]))))))))))) + 3.2003439011230801e-10);
		double fTemp59 = (((((fRec51[0] * ((fConst0 * (fConst141 + (fRec52[0] * (fConst142 + (fConst143 * fRec52[0]))))) + 6.4006878022461703e-11)) + (fRec53[0] * ((fConst0 * (fConst144 + ((fRec51[0] * (fConst145 + (fConst0 * (fRec52[0] * (fConst146 + (fConst147 * fRec52[0])))))) + (fRec52[0] * (fConst148 + (fConst149 * fRec52[0])))))) + 2.5602751208984699e-12))) + (fRec52[0] * ((fConst0 * (fConst150 + (fConst151 * fRec52[0]))) + -6.4006878022461703e-11))) + (fConst0 * (fConst152 + (fRec44[0] * (fConst153 + ((((fRec51[0] * (fConst154 + (fConst0 * (fRec52[0] * (fConst155 + (fConst156 * fRec52[0])))))) + (fRec53[0] * (fConst157 + (fConst0 * ((fRec51[0] * (fConst158 + (fConst0 * (fRec52[0] * (fConst159 + (fConst160 * fRec52[0])))))) + (fRec52[0] * (fConst161 + (fConst162 * fRec52[0])))))))) + (fRec52[0] * (fConst163 + (fConst164 * fRec52[0])))) + (fRec44[0] * (fConst165 + (fConst0 * ((fRec53[0] * (fConst166 + (fConst167 * fRec51[0]))) + (fConst168 * fRec51[0]))))))))))) + 3.2003439011230801e-10);
		double fTemp60 = (((((fRec51[0] * ((fConst0 * (fConst169 + (fRec52[0] * (fConst170 + (fConst171 * fRec52[0]))))) + 3.2003439011230903e-11)) + (fRec53[0] * ((fConst0 * (fConst172 + ((fRec51[0] * (fConst173 + (fConst0 * (fRec52[0] * (fConst174 + (fConst175 * fRec52[0])))))) + (fRec52[0] * (fConst176 + (fConst177 * fRec52[0])))))) + 1.2801375604492301e-12))) + (fRec52[0] * ((fConst0 * (fConst178 + (fConst179 * fRec52[0]))) + -3.2003439011230903e-11))) + (fConst0 * (fConst180 + (fRec44[0] * (fConst181 + ((((fRec51[0] * (fConst182 + (fConst0 * (fRec52[0] * (fConst183 + (fConst184 * fRec52[0])))))) + (fRec53[0] * (fConst185 + (fConst0 * ((fRec51[0] * (fConst186 + (fConst0 * (fRec52[0] * (fConst187 + (fConst188 * fRec52[0])))))) + (fRec52[0] * (fConst189 + (fConst190 * fRec52[0])))))))) + (fRec52[0] * (fConst191 + (fConst192 * fRec52[0])))) + (fRec44[0] * (fConst193 + (fConst0 * ((fRec53[0] * (fConst194 + (fConst195 * fRec51[0]))) + (fConst196 * fRec51[0]))))))))))) + 1.6001719505615401e-10);
		double fTemp61 = (((((fRec51[0] * ((fConst0 * (fConst198 + (fRec52[0] * (fConst200 + (fConst202 * fRec52[0]))))) + 6.40068780224617e-12)) + (fRec53[0] * ((fConst0 * (fConst204 + ((fRec51[0] * (fConst206 + (fConst0 * (fRec52[0] * (fConst208 + (fConst210 * fRec52[0])))))) + (fRec52[0] * (fConst212 + (fConst214 * fRec52[0])))))) + 2.5602751208984701e-13))) + (fRec52[0] * ((fConst0 * (fConst216 + (fConst218 * fRec52[0]))) + -6.40068780224617e-12))) + (fConst0 * (fConst220 + (fRec44[0] * (fConst222 + ((((fRec51[0] * (fConst224 + (fConst0 * (fRec52[0] * (fConst225 + (fConst226 * fRec52[0])))))) + (fRec53[0] * (fConst228 + (fConst0 * ((fRec51[0] * (fConst230 + (fConst0 * (fRec52[0] * (fConst231 + (fConst232 * fRec52[0])))))) + (fRec52[0] * (fConst233 + (fConst234 * fRec52[0])))))))) + (fRec52[0] * (fConst235 + (fConst236 * fRec52[0])))) + (fRec44[0] * (fConst238 + (fConst0 * ((fRec53[0] * (fConst240 + (fConst242 * fRec51[0]))) + (fConst244 * fRec51[0]))))))))))) + 3.2003439011230903e-11);
		double fTemp62 = (((((fRec51[0] * ((fConst0 * (fConst245 + (fRec52[0] * (fConst246 + (fConst247 * fRec52[0]))))) + 6.40068780224617e-12)) + (fRec53[0] * ((fConst0 * (fConst248 + ((fRec51[0] * (fConst249 + (fConst0 * (fRec52[0] * (fConst250 + (fConst251 * fRec52[0])))))) + (fRec52[0] * (fConst252 + (fConst253 * fRec52[0])))))) + 2.5602751208984701e-13))) + (fRec52[0] * ((fConst0 * (fConst254 + (fConst255 * fRec52[0]))) + -6.40068780224617e-12))) + (fConst0 * (fConst256 + (fRec44[0] * (fConst257 + ((((fRec51[0] * (fConst258 + (fConst0 * (fRec52[0] * (fConst259 + (fConst260 * fRec52[0])))))) + (fRec53[0] * (fConst261 + (fConst0 * ((fRec51[0] * (fConst262 + (fConst0 * (fRec52[0] * (fConst263 + (fConst264 * fRec52[0])))))) + (fRec52[0] * (fConst265 + (fConst266 * fRec52[0])))))))) + (fRec52[0] * (fConst267 + (fConst268 * fRec52[0])))) + (fRec44[0] * (fConst269 + (fConst0 * ((fRec53[0] * (fConst270 + (fConst271 * fRec51[0]))) + (fConst272 * fRec51[0]))))))))))) + 3.2003439011230903e-11);
		fRec45[0] = (fTemp56 - ((((((fRec45[1] * fTemp57) + (fRec45[2] * fTemp58)) + (fRec45[3] * fTemp59)) + (fRec45[4] * fTemp60)) + (fRec45[5] * fTemp61)) / fTemp62));
		double fTemp63 = (fConst274 + ((((fRec51[0] * (fConst276 + (fConst278 * fRec52[0]))) + (fRec53[0] * (fConst280 + (fConst282 * fRec51[0])))) + (fConst283 * fRec52[0])) + (fConst0 * (fRec44[0] * (fConst284 + (((fRec51[0] * (fConst285 + (fConst286 * fRec52[0]))) + (fRec53[0] * (fConst287 + (fConst288 * fRec51[0])))) + (fConst289 * fRec52[0])))))));
		double fTemp64 = (fConst291 + ((((fRec51[0] * (fConst293 + (fConst294 * fRec52[0]))) + (fRec53[0] * (fConst296 + (fConst298 * fRec51[0])))) + (fConst299 * fRec52[0])) + (fConst0 * (fRec44[0] * (fConst300 + (((fRec51[0] * (fConst301 + (fConst302 * fRec52[0]))) + (fRec53[0] * (fConst303 + (fConst304 * fRec51[0])))) + (fConst305 * fRec52[0])))))));
		double fTemp65 = (fConst307 + ((((fRec51[0] * (fConst309 + (fConst310 * fRec52[0]))) + (fRec53[0] * (fConst312 + (fConst314 * fRec51[0])))) + (fConst315 * fRec52[0])) + (fConst0 * (fRec44[0] * (fConst316 + (((fRec51[0] * (fConst317 + (fConst318 * fRec52[0]))) + (fRec53[0] * (fConst319 + (fConst320 * fRec51[0])))) + (fConst321 * fRec52[0])))))));
		double fTemp66 = (fConst322 + ((((fRec51[0] * (fConst323 + (fConst324 * fRec52[0]))) + (fRec53[0] * (fConst325 + (fConst326 * fRec51[0])))) + (fConst327 * fRec52[0])) + (fConst0 * (fRec44[0] * (fConst328 + (((fRec51[0] * (fConst329 + (fConst330 * fRec52[0]))) + (fRec53[0] * (fConst331 + (fConst332 * fRec51[0])))) + (fConst333 * fRec52[0])))))));
		double fTemp67 = (fConst334 + ((((fRec51[0] * (fConst335 + (fConst336 * fRec52[0]))) + (fRec53[0] * (fConst337 + (fConst338 * fRec51[0])))) + (fConst339 * fRec52[0])) + (fConst0 * (fRec44[0] * (fConst340 + (((fRec51[0] * (fConst341 + (fConst342 * fRec52[0]))) + (fRec53[0] * (fConst343 + (fConst344 * fRec51[0])))) + (fConst345 * fRec52[0])))))));
		double fTemp68 = (fConst346 + ((((fRec51[0] * (fConst347 + (fConst348 * fRec52[0]))) + (fRec53[0] * (fConst349 + (fConst350 * fRec51[0])))) + (fConst351 * fRec52[0])) + (fConst0 * (fRec44[0] * (fConst352 + (((fRec51[0] * (fConst353 + (fConst354 * fRec52[0]))) + (fRec53[0] * (fConst355 + (fConst356 * fRec51[0])))) + (fConst357 * fRec52[0])))))));
		double fTemp69 = (fConst0 * ((fRec44[0] * ((((((fRec45[0] * fTemp63) + (fRec45[1] * fTemp64)) + (fRec45[2] * fTemp65)) + (fRec45[3] * fTemp66)) + (fRec45[4] * fTemp67)) + (fRec45[5] * fTemp68))) / fTemp62));
		double fThen20 = double(alembic_briteclip(double(fTemp69)));
		double fElse20 = double(alembic_brite_negclip(double(fTemp69)));
		double fTemp70 = (fConst359 + ((((fRec51[0] * ((fConst0 * (fConst361 + (fRec52[0] * (fConst363 + (fConst365 * fRec52[0]))))) + 1.0469323652605e-10)) + (fRec53[0] * ((fConst0 * (fConst367 + ((fRec51[0] * (fConst369 + (fConst277 * (fRec52[0] * (fConst371 + (fConst373 * fRec52[0])))))) + (fRec52[0] * (fConst375 + (fConst376 * fRec52[0])))))) + 4.1877294610420001e-12))) + (fRec52[0] * ((fConst0 * (fConst378 + (fConst380 * fRec52[0]))) + -1.0469323652605e-10))) + 5.2346618263024998e-10));
		double fTemp71 = (((((fRec51[0] * ((fConst277 * (fConst381 + (fRec52[0] * (fConst382 + (fConst383 * fRec52[0]))))) + 1.57039854789075e-10)) + (fRec53[0] * ((fConst277 * (((fRec51[0] * (fConst384 + (fRec52[0] * (fConst385 + (fConst277 * (0.0 - (2.9162440334471001e-20 * fRec52[0]))))))) + (fRec52[0] * ((7.7805388115921905e-18 * fRec52[0]) + 4.8453774517161096e-15))) + -2.7038436698780101e-14)) + 6.2815941915630002e-12))) + (fRec52[0] * ((fConst277 * ((6.3993684773215997e-16 * fRec52[0]) + 6.4981191428189999e-14)) + -1.57039854789075e-10))) + 7.8519927394537503e-10) - fConst386);
		double fTemp72 = (fConst387 + ((((fRec51[0] * ((fConst0 * (fConst388 + (fRec52[0] * (fConst389 + (fConst390 * fRec52[0]))))) + 1.0469323652605e-10)) + (fRec53[0] * ((fConst0 * (fConst391 + ((fRec51[0] * (fConst392 + (fConst277 * (fRec52[0] * (fConst393 + (fConst394 * fRec52[0])))))) + (fRec52[0] * (fConst395 + (fConst277 * (0.0 - (6.08067904846417e-19 * fRec52[0])))))))) + 4.1877294610420001e-12))) + (fRec52[0] * ((fConst0 * (fConst396 + (fConst397 * fRec52[0]))) + -1.0469323652605e-10))) + 5.2346618263024998e-10));
		double fTemp73 = (fConst399 + ((((fRec51[0] * ((fConst0 * (fConst401 + (fRec52[0] * (fConst403 + (fConst405 * fRec52[0]))))) + 2.6173309131512501e-11)) + (fRec53[0] * ((fConst0 * (fConst407 + ((fRec51[0] * (fConst409 + (fConst0 * (fRec52[0] * (fConst411 + (fConst413 * fRec52[0])))))) + (fRec52[0] * (fConst415 + (fConst417 * fRec52[0])))))) + 1.0469323652605e-12))) + (fRec52[0] * ((fConst0 * (fConst419 + (fConst421 * fRec52[0]))) + -2.6173309131512501e-11))) + 1.3086654565756201e-10));
		double fTemp74 = (fConst422 + ((((fRec51[0] * ((fConst0 * (fConst423 + (fRec52[0] * (fConst424 + (fConst425 * fRec52[0]))))) + 2.6173309131512501e-11)) + (fRec53[0] * ((fConst0 * (fConst426 + ((fRec51[0] * (fConst427 + (fConst0 * (fRec52[0] * (fConst428 + (fConst429 * fRec52[0])))))) + (fRec52[0] * (fConst430 + (fConst431 * fRec52[0])))))) + 1.0469323652605e-12))) + (fRec52[0] * ((fConst0 * (fConst432 + (fConst433 * fRec52[0]))) + -2.6173309131512501e-11))) + 1.3086654565756201e-10));
		fRec54[0] = (fTemp56 - (((((fRec54[1] * fTemp70) + (fRec54[2] * fTemp71)) + (fRec54[3] * fTemp72)) + (fRec54[4] * fTemp73)) / fTemp74));
		double fTemp75 = (fConst435 + (((fRec51[0] * (fConst437 + (fConst438 * fRec52[0]))) + (fRec53[0] * (fConst440 + (fConst442 * fRec51[0])))) + (fConst443 * fRec52[0])));
		double fTemp76 = (fConst445 + (((fRec51[0] * (fConst447 + (fConst448 * fRec52[0]))) + (fRec53[0] * (fConst450 + (fConst452 * fRec51[0])))) + (fConst453 * fRec52[0])));
		double fTemp77 = ((((fRec51[0] * (fConst455 + (fConst454 * fRec52[0]))) + (fRec53[0] * ((fConst456 * fRec51[0]) + 1.18320768068121e-12))) - (5.9994488002713396e-14 * fRec52[0])) + 5.9994488002713396e-14);
		double fTemp78 = (fConst453 + (((fRec51[0] * (fConst457 + (fConst458 * fRec52[0]))) + (fRec53[0] * (fConst459 + (fConst460 * fRec51[0])))) + (fConst445 * fRec52[0])));
		double fTemp79 = (fConst461 + (((fRec51[0] * (fConst462 + (fConst463 * fRec52[0]))) + (fRec53[0] * (fConst464 + (fConst465 * fRec51[0])))) + (fConst466 * fRec52[0])));
		double fTemp80 = (fConst0 * ((fRec44[0] * (((((fRec54[0] * fTemp75) + (fRec54[1] * fTemp76)) + (fConst0 * (fRec54[2] * fTemp77))) + (fRec54[3] * fTemp78)) + (fRec54[4] * fTemp79))) / fTemp74));
		double fThen21 = double(alembic_normclip(double(fTemp80)));
		double fElse21 = double(alembic_norm_negclip(double(fTemp80)));
		double fThen22 = (int(signbit(double(fTemp69))) ? fElse20 : fThen20);
		double fElse22 = (int(signbit(double(fTemp80))) ? fElse21 : fThen21);
		fRec43[0] = ((iSlow7 ? fElse22 : fThen22) - (fConst467 * ((fConst468 * fRec43[1]) + (fConst469 * fRec43[2]))));
		double fTemp81 = (fConst3 * (fRec42[0] * (((fConst5 * fRec43[0]) + (fConst470 * fRec43[1])) + (fConst471 * fRec43[2]))));
		double fThen23 = double(alembic_outclip(double(fTemp81)));
		double fElse23 = double(alembic_out_negclip(double(fTemp81)));
		fRec62[0] = (0.0 - (fConst13 * ((fConst14 * fRec62[1]) - (fTemp52 + fVec4[1]))));
		fRec61[0] = (fRec62[0] - (fConst8 * ((fConst15 * fRec61[2]) + (fConst16 * fRec61[1]))));
		double fTemp82 = (fRec61[2] + (fRec61[0] + (2.0 * fRec61[1])));
		fVec5[0] = fTemp82;
		fRec60[0] = ((fConst8 * ((fConst473 * fTemp82) + (fConst474 * fVec5[1]))) - (fConst475 * fRec60[1]));
		fRec59[0] = (fRec60[0] - (fConst472 * ((fConst476 * fRec59[2]) + (fConst26 * fRec59[1]))));
		double fTemp83 = (fConst35 * fRec58[1]);
		fRec58[0] = ((fConst472 * (((fConst25 * fRec59[0]) + (fConst477 * fRec59[1])) + (fConst25 * fRec59[2]))) - (fConst30 * ((fConst32 * fRec58[2]) + fTemp83)));
		double fTemp84 = (fConst44 * fRec57[1]);
		fRec57[0] = ((fRec58[2] + (fConst30 * (fTemp83 + (fConst32 * fRec58[0])))) - (fConst39 * ((fConst41 * fRec57[2]) + fTemp84)));
		double fTemp85 = (fRec57[2] + (fConst39 * (fTemp84 + (fConst41 * fRec57[0]))));
		fRec56[0] = (fTemp85 - ((((((fTemp57 * fRec56[1]) + (fTemp58 * fRec56[2])) + (fTemp59 * fRec56[3])) + (fTemp60 * fRec56[4])) + (fTemp61 * fRec56[5])) / fTemp62));
		double fTemp86 = (fConst0 * ((fRec44[0] * ((((((fRec56[0] * fTemp63) + (fTemp64 * fRec56[1])) + (fTemp65 * fRec56[2])) + (fTemp66 * fRec56[3])) + (fTemp67 * fRec56[4])) + (fTemp68 * fRec56[5]))) / fTemp62));
		double fThen24 = double(alembic_briteclip(double(fTemp86)));
		double fElse24 = double(alembic_brite_negclip(double(fTemp86)));
		fRec63[0] = (fTemp85 - (((((fTemp70 * fRec63[1]) + (fTemp71 * fRec63[2])) + (fTemp72 * fRec63[3])) + (fTemp73 * fRec63[4])) / fTemp74));
		double fTemp87 = (fConst0 * ((fRec44[0] * (((((fRec63[0] * fTemp75) + (fTemp76 * fRec63[1])) + (fConst0 * (fTemp77 * fRec63[2]))) + (fTemp78 * fRec63[3])) + (fTemp79 * fRec63[4]))) / fTemp74));
		double fThen25 = double(alembic_normclip(double(fTemp87)));
		double fElse25 = double(alembic_norm_negclip(double(fTemp87)));
		double fThen26 = (int(signbit(double(fTemp86))) ? fElse24 : fThen24);
		double fElse26 = (int(signbit(double(fTemp87))) ? fElse25 : fThen25);
		fRec55[0] = ((iSlow7 ? fElse26 : fThen26) - (fConst467 * ((fConst468 * fRec55[1]) + (fConst469 * fRec55[2]))));
		double fTemp88 = (fConst3 * (fRec42[0] * (((fConst5 * fRec55[0]) + (fConst470 * fRec55[1])) + (fConst471 * fRec55[2]))));
		double fThen27 = double(alembic_outclip(double(fTemp88)));
		double fElse27 = double(alembic_out_negclip(double(fTemp88)));
		fRec70[0] = (0.0 - (fConst480 * ((fConst22 * fRec70[1]) - (fConst8 * (fTemp82 + fVec5[1])))));
		fRec69[0] = (fRec70[0] - (fConst472 * ((fConst476 * fRec69[2]) + (fConst26 * fRec69[1]))));
		double fTemp89 = (fRec69[2] + (fRec69[0] + (2.0 * fRec69[1])));
		fVec6[0] = fTemp89;
		fRec68[0] = ((fConst472 * ((fConst479 * fTemp89) + (fConst481 * fVec6[1]))) - (fConst482 * fRec68[1]));
		fRec67[0] = (fRec68[0] - (fConst478 * ((fConst483 * fRec67[2]) + (fConst35 * fRec67[1]))));
		double fTemp90 = (fConst44 * fRec66[1]);
		fRec66[0] = ((fConst478 * (((fConst34 * fRec67[0]) + (fConst484 * fRec67[1])) + (fConst34 * fRec67[2]))) - (fConst39 * ((fConst41 * fRec66[2]) + fTemp90)));
		double fTemp91 = (fRec66[2] + (fConst39 * (fTemp90 + (fConst41 * fRec66[0]))));
		fRec65[0] = (fTemp91 - ((((((fTemp57 * fRec65[1]) + (fTemp58 * fRec65[2])) + (fTemp59 * fRec65[3])) + (fTemp60 * fRec65[4])) + (fTemp61 * fRec65[5])) / fTemp62));
		double fTemp92 = (fConst0 * ((fRec44[0] * ((((((fRec65[0] * fTemp63) + (fTemp64 * fRec65[1])) + (fTemp65 * fRec65[2])) + (fTemp66 * fRec65[3])) + (fTemp67 * fRec65[4])) + (fTemp68 * fRec65[5]))) / fTemp62));
		double fThen28 = double(alembic_briteclip(double(fTemp92)));
		double fElse28 = double(alembic_brite_negclip(double(fTemp92)));
		fRec71[0] = (fTemp91 - (((((fTemp70 * fRec71[1]) + (fTemp71 * fRec71[2])) + (fTemp72 * fRec71[3])) + (fTemp73 * fRec71[4])) / fTemp74));
		double fTemp93 = (fConst0 * ((fRec44[0] * (((((fRec71[0] * fTemp75) + (fTemp76 * fRec71[1])) + (fConst0 * (fTemp77 * fRec71[2]))) + (fTemp78 * fRec71[3])) + (fTemp79 * fRec71[4]))) / fTemp74));
		double fThen29 = double(alembic_normclip(double(fTemp93)));
		double fElse29 = double(alembic_norm_negclip(double(fTemp93)));
		double fThen30 = (int(signbit(double(fTemp92))) ? fElse28 : fThen28);
		double fElse30 = (int(signbit(double(fTemp93))) ? fElse29 : fThen29);
		fRec64[0] = ((iSlow7 ? fElse30 : fThen30) - (fConst467 * ((fConst468 * fRec64[1]) + (fConst469 * fRec64[2]))));
		double fTemp94 = (fConst3 * (fRec42[0] * (((fConst5 * fRec64[0]) + (fConst470 * fRec64[1])) + (fConst471 * fRec64[2]))));
		double fThen31 = double(alembic_outclip(double(fTemp94)));
		double fElse31 = double(alembic_out_negclip(double(fTemp94)));
		fRec77[0] = (0.0 - (fConst487 * ((fConst31 * fRec77[1]) - (fConst472 * (fTemp89 + fVec6[1])))));
		fRec76[0] = (fRec77[0] - (fConst478 * ((fConst483 * fRec76[2]) + (fConst35 * fRec76[1]))));
		double fTemp95 = (fRec76[2] + (fRec76[0] + (2.0 * fRec76[1])));
		fVec7[0] = fTemp95;
		fRec75[0] = ((fConst478 * ((fConst486 * fTemp95) + (fConst488 * fVec7[1]))) - (fConst489 * fRec75[1]));
		fRec74[0] = (fRec75[0] - (fConst485 * ((fConst490 * fRec74[2]) + (fConst44 * fRec74[1]))));
		double fTemp96 = (fConst485 * (((fConst43 * fRec74[0]) + (fConst491 * fRec74[1])) + (fConst43 * fRec74[2])));
		fRec73[0] = (fTemp96 - ((((((fTemp57 * fRec73[1]) + (fTemp58 * fRec73[2])) + (fTemp59 * fRec73[3])) + (fTemp60 * fRec73[4])) + (fTemp61 * fRec73[5])) / fTemp62));
		double fTemp97 = (fConst0 * ((fRec44[0] * ((((((fRec73[0] * fTemp63) + (fTemp64 * fRec73[1])) + (fTemp65 * fRec73[2])) + (fTemp66 * fRec73[3])) + (fTemp67 * fRec73[4])) + (fTemp68 * fRec73[5]))) / fTemp62));
		double fThen32 = double(alembic_briteclip(double(fTemp97)));
		double fElse32 = double(alembic_brite_negclip(double(fTemp97)));
		fRec78[0] = (fTemp96 - (((((fTemp70 * fRec78[1]) + (fTemp71 * fRec78[2])) + (fTemp72 * fRec78[3])) + (fTemp73 * fRec78[4])) / fTemp74));
		double fTemp98 = (fConst0 * ((fRec44[0] * (((((fRec78[0] * fTemp75) + (fTemp76 * fRec78[1])) + (fConst0 * (fTemp77 * fRec78[2]))) + (fTemp78 * fRec78[3])) + (fTemp79 * fRec78[4]))) / fTemp74));
		double fThen33 = double(alembic_normclip(double(fTemp98)));
		double fElse33 = double(alembic_norm_negclip(double(fTemp98)));
		double fThen34 = (int(signbit(double(fTemp97))) ? fElse32 : fThen32);
		double fElse34 = (int(signbit(double(fTemp98))) ? fElse33 : fThen33);
		fRec72[0] = ((iSlow7 ? fElse34 : fThen34) - (fConst467 * ((fConst468 * fRec72[1]) + (fConst469 * fRec72[2]))));
		double fTemp99 = (fConst3 * (fRec42[0] * (((fConst5 * fRec72[0]) + (fConst470 * fRec72[1])) + (fConst471 * fRec72[2]))));
		double fThen35 = double(alembic_outclip(double(fTemp99)));
		double fElse35 = double(alembic_out_negclip(double(fTemp99)));
		fRec82[0] = (0.0 - (fConst492 * ((fConst40 * fRec82[1]) - (fConst478 * (fTemp95 + fVec7[1])))));
		fRec81[0] = (fRec82[0] - (fConst485 * ((fConst490 * fRec81[2]) + (fConst44 * fRec81[1]))));
		double fTemp100 = (fConst485 * (fRec81[2] + (fRec81[0] + (2.0 * fRec81[1]))));
		fRec80[0] = (fTemp100 - ((((((fTemp57 * fRec80[1]) + (fTemp58 * fRec80[2])) + (fTemp59 * fRec80[3])) + (fTemp60 * fRec80[4])) + (fTemp61 * fRec80[5])) / fTemp62));
		double fTemp101 = (fConst0 * ((fRec44[0] * ((((((fRec80[0] * fTemp63) + (fTemp64 * fRec80[1])) + (fTemp65 * fRec80[2])) + (fTemp66 * fRec80[3])) + (fTemp67 * fRec80[4])) + (fTemp68 * fRec80[5]))) / fTemp62));
		double fThen36 = double(alembic_briteclip(double(fTemp101)));
		double fElse36 = double(alembic_brite_negclip(double(fTemp101)));
		fRec83[0] = (fTemp100 - (((((fTemp70 * fRec83[1]) + (fTemp71 * fRec83[2])) + (fTemp72 * fRec83[3])) + (fTemp73 * fRec83[4])) / fTemp74));
		double fTemp102 = (fConst0 * ((fRec44[0] * (((((fRec83[0] * fTemp75) + (fTemp76 * fRec83[1])) + (fConst0 * (fTemp77 * fRec83[2]))) + (fTemp78 * fRec83[3])) + (fTemp79 * fRec83[4]))) / fTemp74));
		double fThen37 = double(alembic_normclip(double(fTemp102)));
		double fElse37 = double(alembic_norm_negclip(double(fTemp102)));
		double fThen38 = (int(signbit(double(fTemp101))) ? fElse36 : fThen36);
		double fElse38 = (int(signbit(double(fTemp102))) ? fElse37 : fThen37);
		fRec79[0] = ((iSlow7 ? fElse38 : fThen38) - (fConst467 * ((fConst468 * fRec79[1]) + (fConst469 * fRec79[2]))));
		double fTemp103 = (fConst3 * (fRec42[0] * (((fConst5 * fRec79[0]) + (fConst470 * fRec79[1])) + (fConst471 * fRec79[2]))));
		double fThen39 = double(alembic_outclip(double(fTemp103)));
		double fElse39 = double(alembic_out_negclip(double(fTemp103)));
		output1[i0] = FAUSTFLOAT((((((int(signbit(double(fTemp81))) ? fElse23 : fThen23) + (int(signbit(double(fTemp88))) ? fElse27 : fThen27)) + (int(signbit(double(fTemp94))) ? fElse31 : fThen31)) + (int(signbit(double(fTemp99))) ? fElse35 : fThen35)) + (int(signbit(double(fTemp103))) ? fElse39 : fThen39)));
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fVec0[1] = fVec0[0];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		for (int j0 = 5; (j0 > 0); j0 = (j0 - 1)) {
			fRec3[j0] = fRec3[(j0 - 1)];
		}
		for (int j1 = 4; (j1 > 0); j1 = (j1 - 1)) {
			fRec12[j1] = fRec12[(j1 - 1)];
		}
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fVec1[1] = fVec1[0];
		fRec18[1] = fRec18[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		for (int j2 = 5; (j2 > 0); j2 = (j2 - 1)) {
			fRec14[j2] = fRec14[(j2 - 1)];
		}
		for (int j3 = 4; (j3 > 0); j3 = (j3 - 1)) {
			fRec21[j3] = fRec21[(j3 - 1)];
		}
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fRec28[1] = fRec28[0];
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		fVec2[1] = fVec2[0];
		fRec26[1] = fRec26[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		for (int j4 = 5; (j4 > 0); j4 = (j4 - 1)) {
			fRec23[j4] = fRec23[(j4 - 1)];
		}
		for (int j5 = 4; (j5 > 0); j5 = (j5 - 1)) {
			fRec29[j5] = fRec29[(j5 - 1)];
		}
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fVec3[1] = fVec3[0];
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		for (int j6 = 5; (j6 > 0); j6 = (j6 - 1)) {
			fRec31[j6] = fRec31[(j6 - 1)];
		}
		for (int j7 = 4; (j7 > 0); j7 = (j7 - 1)) {
			fRec36[j7] = fRec36[(j7 - 1)];
		}
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		for (int j8 = 5; (j8 > 0); j8 = (j8 - 1)) {
			fRec38[j8] = fRec38[(j8 - 1)];
		}
		for (int j9 = 4; (j9 > 0); j9 = (j9 - 1)) {
			fRec41[j9] = fRec41[(j9 - 1)];
		}
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fRec42[1] = fRec42[0];
		fRec44[1] = fRec44[0];
		fVec4[1] = fVec4[0];
		fRec50[1] = fRec50[0];
		fRec49[2] = fRec49[1];
		fRec49[1] = fRec49[0];
		fRec48[2] = fRec48[1];
		fRec48[1] = fRec48[0];
		fRec47[2] = fRec47[1];
		fRec47[1] = fRec47[0];
		fRec46[2] = fRec46[1];
		fRec46[1] = fRec46[0];
		fRec51[1] = fRec51[0];
		fRec52[1] = fRec52[0];
		fRec53[1] = fRec53[0];
		for (int j10 = 5; (j10 > 0); j10 = (j10 - 1)) {
			fRec45[j10] = fRec45[(j10 - 1)];
		}
		for (int j11 = 4; (j11 > 0); j11 = (j11 - 1)) {
			fRec54[j11] = fRec54[(j11 - 1)];
		}
		fRec43[2] = fRec43[1];
		fRec43[1] = fRec43[0];
		fRec62[1] = fRec62[0];
		fRec61[2] = fRec61[1];
		fRec61[1] = fRec61[0];
		fVec5[1] = fVec5[0];
		fRec60[1] = fRec60[0];
		fRec59[2] = fRec59[1];
		fRec59[1] = fRec59[0];
		fRec58[2] = fRec58[1];
		fRec58[1] = fRec58[0];
		fRec57[2] = fRec57[1];
		fRec57[1] = fRec57[0];
		for (int j12 = 5; (j12 > 0); j12 = (j12 - 1)) {
			fRec56[j12] = fRec56[(j12 - 1)];
		}
		for (int j13 = 4; (j13 > 0); j13 = (j13 - 1)) {
			fRec63[j13] = fRec63[(j13 - 1)];
		}
		fRec55[2] = fRec55[1];
		fRec55[1] = fRec55[0];
		fRec70[1] = fRec70[0];
		fRec69[2] = fRec69[1];
		fRec69[1] = fRec69[0];
		fVec6[1] = fVec6[0];
		fRec68[1] = fRec68[0];
		fRec67[2] = fRec67[1];
		fRec67[1] = fRec67[0];
		fRec66[2] = fRec66[1];
		fRec66[1] = fRec66[0];
		for (int j14 = 5; (j14 > 0); j14 = (j14 - 1)) {
			fRec65[j14] = fRec65[(j14 - 1)];
		}
		for (int j15 = 4; (j15 > 0); j15 = (j15 - 1)) {
			fRec71[j15] = fRec71[(j15 - 1)];
		}
		fRec64[2] = fRec64[1];
		fRec64[1] = fRec64[0];
		fRec77[1] = fRec77[0];
		fRec76[2] = fRec76[1];
		fRec76[1] = fRec76[0];
		fVec7[1] = fVec7[0];
		fRec75[1] = fRec75[0];
		fRec74[2] = fRec74[1];
		fRec74[1] = fRec74[0];
		for (int j16 = 5; (j16 > 0); j16 = (j16 - 1)) {
			fRec73[j16] = fRec73[(j16 - 1)];
		}
		for (int j17 = 4; (j17 > 0); j17 = (j17 - 1)) {
			fRec78[j17] = fRec78[(j17 - 1)];
		}
		fRec72[2] = fRec72[1];
		fRec72[1] = fRec72[0];
		fRec82[1] = fRec82[0];
		fRec81[2] = fRec81[1];
		fRec81[1] = fRec81[0];
		for (int j18 = 5; (j18 > 0); j18 = (j18 - 1)) {
			fRec80[j18] = fRec80[(j18 - 1)];
		}
		for (int j19 = 4; (j19 > 0); j19 = (j19 - 1)) {
			fRec83[j19] = fRec83[(j19 - 1)];
		}
		fRec79[2] = fRec79[1];
		fRec79[1] = fRec79[0];
	}
#undef fVslider0
#undef fCheckbox0
#undef fVslider1
#undef fVslider2
#undef fVslider3
#undef fVslider4
#undef fVslider5
#undef fCheckbox1
#undef fVslider6
#undef fVslider7
#undef fVslider8
#undef fVslider9
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case BRIGHT_L: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case BRIGHT_R: 
		fCheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case BASS_L: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case BASS_R: 
		fVslider7_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case MASTER_L: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case MASTER_R: 
		fVslider5_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case MIDDLE_L: 
		fVslider4_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case MIDDLE_R: 
		fVslider9_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TREBLE_L: 
		fVslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TREBLE_R: 
		fVslider8_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME_L: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME_R: 
		fVslider6_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   BASS_L, 
   BASS_R, 
   MASTER_L, 
   MASTER_R, 
   MIDDLE_L, 
   MIDDLE_R, 
   TREBLE_L, 
   TREBLE_R, 
   VOLUME_L, 
   VOLUME_R, 
   BRIGHT_L, 
   BRIGHT_R, 
} PortIndex;
*/

} // end namespace gx_studiopre_st
