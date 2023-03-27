// generated from file '../src/LV2/faust/gx_studiopre.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "alembic_brite_neg_table.h"
#include "alembic_brite_table.h"
#include "alembic_norm_neg_table.h"
#include "alembic_norm_table.h"
#include "alembic_out_neg_table.h"
#include "alembic_out_table.h"
#include "math.h"

namespace gx_studiopre {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec1[2];
	double fConst7;
	double fConst8;
	double fConst10;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec2[2];
	double fConst12;
	double fConst14;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec3[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec4[2];
	double fConst16;
	double fConst18;
	double fConst20;
	double fConst22;
	double fConst24;
	double fConst25;
	double fConst27;
	double fConst29;
	double fConst31;
	double fConst33;
	double fConst35;
	double fConst37;
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
	double fConst47;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst53;
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
	double fConst85;
	double fConst87;
	double fConst89;
	double fConst91;
	double fConst93;
	double fConst95;
	double fConst97;
	double fConst99;
	double fConst101;
	double fConst103;
	double fConst105;
	double fConst107;
	double fConst109;
	double fConst111;
	double fConst113;
	double fConst115;
	double fConst116;
	double fConst117;
	double fConst118;
	double fConst119;
	double fConst120;
	double fConst121;
	double fConst123;
	double fConst125;
	double fConst126;
	double fConst127;
	double fConst129;
	double fConst131;
	double fConst133;
	double fConst135;
	double fConst137;
	double fConst139;
	double fConst141;
	double fConst143;
	double fConst145;
	double fConst147;
	double fConst149;
	double fConst151;
	double fConst153;
	double fConst155;
	double fConst157;
	double fConst159;
	double fConst161;
	double fConst163;
	double fConst164;
	double fConst165;
	double fConst166;
	double fConst167;
	double fConst168;
	double fConst169;
	double fConst171;
	double fConst173;
	double fConst174;
	double fConst175;
	double fConst177;
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
	double fConst197;
	double fConst198;
	double fConst199;
	double fConst200;
	double fConst201;
	double fConst202;
	double fConst203;
	double fConst204;
	double fConst205;
	double fConst206;
	double fConst207;
	double fConst208;
	double fConst209;
	double fConst210;
	double fConst211;
	double fConst212;
	double fConst213;
	double fConst214;
	double fConst215;
	double fConst216;
	double fConst217;
	double fConst218;
	double fConst219;
	double fConst220;
	double fConst221;
	double fConst222;
	double fConst223;
	double fConst224;
	double fConst225;
	double fConst226;
	double fConst227;
	double fConst228;
	double fConst229;
	double fConst230;
	double fConst231;
	double fConst232;
	double fConst233;
	double fConst234;
	double fConst235;
	double fConst238;
	double fConst239;
	double fConst241;
	double fConst242;
	double fConst245;
	double fConst246;
	double fConst248;
	double fConst249;
	double fConst252;
	double fConst253;
	double fConst255;
	double fConst256;
	double fConst259;
	double fConst260;
	double fConst261;
	double fConst262;
	double fConst263;
	double fVec0[2];
	double fConst264;
	double fConst266;
	double fRec13[2];
	double fRec12[3];
	double fVec1[2];
	double fConst267;
	double fConst269;
	double fRec11[2];
	double fRec10[3];
	double fVec2[2];
	double fConst270;
	double fConst272;
	double fRec9[2];
	double fRec8[3];
	double fVec3[2];
	double fConst273;
	double fConst275;
	double fRec7[2];
	double fRec6[3];
	double fRec5[6];
	double fConst277;
	double fConst278;
	double fConst280;
	double fConst282;
	double fConst284;
	double fConst285;
	double fConst286;
	double fConst287;
	double fConst288;
	double fConst289;
	double fConst290;
	double fConst291;
	double fConst293;
	double fConst294;
	double fConst296;
	double fConst298;
	double fConst300;
	double fConst301;
	double fConst302;
	double fConst303;
	double fConst304;
	double fConst305;
	double fConst306;
	double fConst307;
	double fConst309;
	double fConst310;
	double fConst312;
	double fConst314;
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
	double fConst358;
	double fConst359;
	double fConst361;
	double fConst363;
	double fConst365;
	double fConst367;
	double fConst369;
	double fConst371;
	double fConst373;
	double fConst375;
	double fConst377;
	double fConst379;
	double fConst381;
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
	double fConst418;
	double fConst419;
	double fConst420;
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
	double fConst434;
	double fConst435;
	double fRec14[5];
	double fConst437;
	double fConst438;
	double fConst440;
	double fConst442;
	double fConst444;
	double fConst445;
	double fConst447;
	double fConst448;
	double fConst450;
	double fConst452;
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
	double fRec0[3];
	double fConst470;
	double fConst471;
	double fConst472;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	double fRec15[2];
	double fConst473;
	double fConst474;
	double fConst475;
	double fRec19[2];
	double fRec18[3];
	double fConst476;
	double fRec17[6];
	double fRec20[5];
	double fRec16[3];
	double fConst477;
	double fConst478;
	double fConst479;
	double fConst480;
	double fConst481;
	double fRec25[2];
	double fRec24[3];
	double fConst482;
	double fRec23[3];
	double fRec22[6];
	double fRec26[5];
	double fRec21[3];
	double fConst483;
	double fConst484;
	double fConst485;
	double fConst486;
	double fConst487;
	double fRec32[2];
	double fRec31[3];
	double fConst488;
	double fRec30[3];
	double fRec29[3];
	double fRec28[6];
	double fRec33[5];
	double fRec27[3];
	double fConst489;
	double fConst490;
	double fConst491;
	double fRec40[2];
	double fRec39[3];
	double fConst492;
	double fRec38[3];
	double fRec37[3];
	double fRec36[3];
	double fRec35[6];
	double fRec41[5];
	double fRec34[3];

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
	id = "gx_studiopre";
	name = N_("gx_studiopre");
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
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec2[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec3[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec4[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fVec0[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec13[l5] = 0.0;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec12[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fVec1[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec11[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec10[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fVec2[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec9[l11] = 0.0;
	for (int l12 = 0; l12 < 3; l12 = l12 + 1) fRec8[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fVec3[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec7[l14] = 0.0;
	for (int l15 = 0; l15 < 3; l15 = l15 + 1) fRec6[l15] = 0.0;
	for (int l16 = 0; l16 < 6; l16 = l16 + 1) fRec5[l16] = 0.0;
	for (int l17 = 0; l17 < 5; l17 = l17 + 1) fRec14[l17] = 0.0;
	for (int l18 = 0; l18 < 3; l18 = l18 + 1) fRec0[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec15[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec19[l20] = 0.0;
	for (int l21 = 0; l21 < 3; l21 = l21 + 1) fRec18[l21] = 0.0;
	for (int l22 = 0; l22 < 6; l22 = l22 + 1) fRec17[l22] = 0.0;
	for (int l23 = 0; l23 < 5; l23 = l23 + 1) fRec20[l23] = 0.0;
	for (int l24 = 0; l24 < 3; l24 = l24 + 1) fRec16[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec25[l25] = 0.0;
	for (int l26 = 0; l26 < 3; l26 = l26 + 1) fRec24[l26] = 0.0;
	for (int l27 = 0; l27 < 3; l27 = l27 + 1) fRec23[l27] = 0.0;
	for (int l28 = 0; l28 < 6; l28 = l28 + 1) fRec22[l28] = 0.0;
	for (int l29 = 0; l29 < 5; l29 = l29 + 1) fRec26[l29] = 0.0;
	for (int l30 = 0; l30 < 3; l30 = l30 + 1) fRec21[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec32[l31] = 0.0;
	for (int l32 = 0; l32 < 3; l32 = l32 + 1) fRec31[l32] = 0.0;
	for (int l33 = 0; l33 < 3; l33 = l33 + 1) fRec30[l33] = 0.0;
	for (int l34 = 0; l34 < 3; l34 = l34 + 1) fRec29[l34] = 0.0;
	for (int l35 = 0; l35 < 6; l35 = l35 + 1) fRec28[l35] = 0.0;
	for (int l36 = 0; l36 < 5; l36 = l36 + 1) fRec33[l36] = 0.0;
	for (int l37 = 0; l37 < 3; l37 = l37 + 1) fRec27[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fRec40[l38] = 0.0;
	for (int l39 = 0; l39 < 3; l39 = l39 + 1) fRec39[l39] = 0.0;
	for (int l40 = 0; l40 < 3; l40 = l40 + 1) fRec38[l40] = 0.0;
	for (int l41 = 0; l41 < 3; l41 = l41 + 1) fRec37[l41] = 0.0;
	for (int l42 = 0; l42 < 3; l42 = l42 + 1) fRec36[l42] = 0.0;
	for (int l43 = 0; l43 < 6; l43 = l43 + 1) fRec35[l43] = 0.0;
	for (int l44 = 0; l44 < 5; l44 = l44 + 1) fRec41[l44] = 0.0;
	for (int l45 = 0; l45 < 3; l45 = l45 + 1) fRec34[l45] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 4.33864919358014e-10 * fConst0;
	fConst2 = fConst0 * (fConst1 + -7.81664517527894e-09) + 2.68307231780644e-08;
	fConst3 = mydsp_faustpower2_f(fConst0);
	fConst4 = 5.36614463561288e-08 - 8.67729838716027e-10 * fConst3;
	fConst5 = 1.0 / (fConst0 * (fConst1 + 7.81664517527894e-09) + 2.68307231780644e-08);
	double fConst6 = 1.59749650223354e-24 * fConst0;
	fConst7 = mydsp_faustpower3_f(fConst0);
	fConst8 = fConst7 * (fConst0 * (-9.17181360088287e-21 - fConst6) + -1.17096473699268e-19);
	double fConst9 = 9.99285046078002e-23 * fConst0;
	fConst10 = fConst3 * (fConst0 * (-5.73269784908691e-19 - fConst9) + -7.31891791891218e-18);
	double fConst11 = 1.6929383555757e-23 * fConst0;
	fConst12 = fConst3 * (fConst0 * (fConst0 * (-1.25906879957409e-19 - fConst11) + -1.62857548261884e-17) + -1.83118953550983e-16);
	double fConst13 = 1.05898697136012e-21 * fConst0;
	fConst14 = fConst0 * (fConst0 * (fConst0 * (-7.77799604390716e-18 - fConst13) + -6.02464692946613e-16) + -6.14466029015632e-15);
	double fConst15 = 2.40088747236654e-22 * fConst0;
	fConst16 = fConst3 * (fConst0 * (fConst15 + 1.8779602481101e-20) + 1.91826477713424e-19);
	double fConst17 = 2.15430751633278e-22 * fConst0;
	fConst18 = fConst0 * (fConst0 * (fConst0 * (1.90693980601459e-18 - fConst17) + 1.50232520281226e-16) + 1.53616507253908e-15);
	double fConst19 = 1.78443758228215e-23 * fConst0;
	fConst20 = fConst7 * (fConst19 + 2.28327872258084e-22);
	double fConst21 = 2.49821261519501e-23 * fConst0;
	fConst22 = fConst3 * (fConst0 * (1.42192566937971e-19 - fConst21) + 1.82351647640129e-18);
	double fConst23 = 2.85267232541704e-25 * fConst0;
	fConst24 = mydsp_faustpower4_f(fConst0);
	fConst25 = fConst24 * (fConst23 + 3.65013945446597e-24);
	double fConst26 = 3.99374125558385e-25 * fConst0;
	fConst27 = fConst7 * (fConst0 * (2.27132232044654e-21 - fConst26) + 2.91281128466384e-20);
	double fConst28 = 1.54230955969265e-24 * fConst0;
	fConst29 = fConst3 * (fConst0 * (fConst0 * (fConst28 + 5.65134377825805e-21) + -2.30032611736055e-20) + -1.1695046812109e-18);
	double fConst30 = 9.64763852233277e-23 * fConst0;
	fConst31 = fConst0 * (fConst0 * (fConst0 * (fConst30 + 3.53068929659391e-19) + -5.29245486955245e-19) + -6.14466029015632e-17);
	double fConst32 = 3.83815344221861e-24 * fConst0;
	fConst33 = fConst7 * (fConst0 * (fConst32 + 5.06664243269087e-22) + 5.70819680645209e-21);
	double fConst34 = 3.44396099549798e-24 * fConst0;
	fConst35 = fConst3 * (fConst0 * (fConst0 * (3.00670847416855e-20 - fConst34) + 4.03664924154006e-18) + 4.55514105154877e-17);
	double fConst36 = 1.65351911090363e-23 * fConst0;
	fConst37 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst36 + 9.5068384229614e-20) + 1.02988983768651e-17) + -1.30486302011578e-17) + -1.53616507253908e-15);
	double fConst38 = 1.03432897575674e-21 * fConst0;
	fConst39 = fConst0 * (fConst0 * (fConst0 * (fConst38 + 5.85227663541147e-18) + 4.52040346187673e-16) + 4.60849521761724e-15);
	fConst40 = fConst0 * (fConst0 * (-1.01914938263382e-18 - fConst15) + -7.84401701489674e-17) + -7.99276990472601e-16;
	fConst41 = fConst0 * (fConst0 * (fConst17 + -1.00931167420926e-18) + -8.09581504534201e-15) + -6.27504999577649e-13;
	fConst42 = fConst3 * (fConst0 * (-7.45798938006809e-20 - fConst19) + -9.51366134408682e-19);
	fConst43 = fConst0 * (fConst0 * (fConst0 * (fConst21 + -3.81003746381788e-20) + -5.94292545384613e-16) + -7.59798531833873e-15);
	fConst44 = fConst7 * (fConst0 * (-1.19226360837823e-21 - fConst23) + -1.52089143936082e-20);
	fConst45 = fConst3 * (fConst0 * (fConst0 * (fConst26 + -6.07263463953272e-22) + -9.49297111470724e-18) + -1.21367136860993e-16);
	double fConst46 = 5.51869425408882e-26 * fConst0;
	fConst47 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst46 + 1.04066508425183e-20) + 5.30246139994882e-17) + 1.0728203737318e-15) + 4.87293617171206e-15);
	double fConst48 = 3.45211938447258e-24 * fConst0;
	fConst49 = fConst0 * (fConst0 * (fConst0 * (fConst48 + 6.50953455217104e-19) + 3.31397583073083e-15) + 6.32576187894833e-14);
	fConst50 = fConst3 * (fConst0 * (fConst0 * (-1.64989702525133e-20 - fConst32) + -2.11680921042765e-18) + -2.37841533602171e-17);
	fConst51 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst34 + -1.57172472604439e-20) + -1.29316168998563e-16) + -1.68649232502658e-14) + -1.89797543814532e-13);
	double fConst52 = 3.9419244672063e-25 * fConst0;
	fConst53 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst52 + 1.03020062404785e-19) + 6.59092588471003e-16) + 9.2998714565051e-14) + 1.58189673716889e-12);
	double fConst54 = 2.46579956033756e-23 * fConst0;
	fConst55 = fConst0 * (fConst0 * (fConst0 * (fConst54 + 6.44090677084358e-18) + 4.05825720651041e-14) + 3.13857383051234e-12);
	fConst56 = fConst7 * (fConst0 * (fConst6 + -9.17181360088287e-21) + 1.17096473699268e-19);
	fConst57 = fConst3 * (fConst0 * (5.73269784908691e-19 - fConst9) + -7.31891791891218e-18);
	fConst58 = fConst3 * (fConst0 * (fConst0 * (fConst11 + -1.25906879957409e-19) + 1.62857548261884e-17) + -1.83118953550983e-16);
	fConst59 = fConst0 * (fConst0 * (fConst0 * (7.77799604390716e-18 - fConst13) + -6.02464692946613e-16) + 6.14466029015632e-15);
	fConst60 = fConst3 * (fConst0 * (fConst15 + -1.8779602481101e-20) + 1.91826477713424e-19);
	fConst61 = fConst0 * (fConst0 * (fConst0 * (-1.90693980601459e-18 - fConst17) + 1.50232520281226e-16) + -1.53616507253908e-15);
	fConst62 = fConst7 * (fConst19 + -2.28327872258084e-22);
	fConst63 = fConst3 * (fConst0 * (-1.42192566937971e-19 - fConst21) + 1.82351647640129e-18);
	fConst64 = fConst24 * (3.65013945446597e-24 - fConst23);
	fConst65 = fConst7 * (fConst0 * (fConst26 + 2.27132232044654e-21) + -2.91281128466384e-20);
	fConst66 = fConst3 * (fConst0 * (fConst0 * (5.65134377825805e-21 - fConst28) + 2.30032611736055e-20) + -1.1695046812109e-18);
	fConst67 = fConst0 * (fConst0 * (fConst0 * (fConst30 + -3.53068929659391e-19) + -5.29245486955245e-19) + 6.14466029015632e-17);
	fConst68 = fConst7 * (fConst0 * (5.06664243269087e-22 - fConst32) + -5.70819680645209e-21);
	fConst69 = fConst3 * (fConst0 * (fConst0 * (fConst34 + 3.00670847416855e-20) + -4.03664924154006e-18) + 4.55514105154877e-17);
	fConst70 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (9.5068384229614e-20 - fConst36) + -1.02988983768651e-17) + -1.30486302011578e-17) + 1.53616507253908e-15);
	fConst71 = fConst0 * (fConst0 * (fConst0 * (fConst38 + -5.85227663541147e-18) + 4.52040346187673e-16) + -4.60849521761724e-15);
	fConst72 = fConst0 * (fConst0 * (1.01914938263382e-18 - fConst15) + -7.84401701489674e-17) + 7.99276990472601e-16;
	fConst73 = fConst0 * (fConst0 * (fConst17 + 1.00931167420926e-18) + -8.09581504534201e-15) + 6.27504999577649e-13;
	fConst74 = fConst3 * (fConst0 * (7.45798938006809e-20 - fConst19) + -9.51366134408682e-19);
	fConst75 = fConst0 * (fConst0 * (fConst0 * (fConst21 + 3.81003746381788e-20) + -5.94292545384613e-16) + 7.59798531833873e-15);
	fConst76 = fConst7 * (fConst0 * (fConst23 + -1.19226360837823e-21) + 1.52089143936082e-20);
	fConst77 = fConst3 * (fConst0 * (fConst0 * (-6.07263463953272e-22 - fConst26) + 9.49297111470724e-18) + -1.21367136860993e-16);
	fConst78 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (1.04066508425183e-20 - fConst46) + -5.30246139994882e-17) + 1.0728203737318e-15) + -4.87293617171206e-15);
	fConst79 = fConst0 * (fConst0 * (fConst0 * (fConst48 + -6.50953455217104e-19) + 3.31397583073083e-15) + -6.32576187894833e-14);
	fConst80 = fConst3 * (fConst0 * (fConst0 * (fConst32 + -1.64989702525133e-20) + 2.11680921042765e-18) + -2.37841533602171e-17);
	fConst81 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-1.57172472604439e-20 - fConst34) + 1.29316168998563e-16) + -1.68649232502658e-14) + 1.89797543814532e-13);
	fConst82 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (1.03020062404785e-19 - fConst52) + -6.59092588471003e-16) + 9.2998714565051e-14) + -1.58189673716889e-12);
	fConst83 = fConst0 * (fConst0 * (fConst0 * (fConst54 + -6.44090677084358e-18) + 4.05825720651041e-14) + -3.13857383051234e-12);
	double fConst84 = 7.98748251116771e-24 * fConst0;
	fConst85 = fConst7 * (fConst0 * (2.75154408026486e-20 - fConst84) + -1.17096473699268e-19);
	double fConst86 = 2.99785513823401e-22 * fConst0;
	fConst87 = fConst3 * (fConst0 * (fConst86 + -5.73269784908691e-19) + -7.31891791891218e-18);
	double fConst88 = 8.46469177787849e-23 * fConst0;
	fConst89 = fConst3 * (fConst0 * (fConst0 * (3.77720639872226e-19 - fConst88) + -1.62857548261884e-17) + -1.83118953550983e-16);
	double fConst90 = 3.17696091408035e-21 * fConst0;
	fConst91 = fConst0 * (fConst0 * (fConst0 * (fConst90 + -7.77799604390716e-18) + -6.02464692946613e-16) + 1.8433980870469e-14);
	double fConst92 = 7.20266241709961e-22 * fConst0;
	fConst93 = fConst3 * (fConst0 * (1.8779602481101e-20 - fConst92) + 1.91826477713424e-19);
	double fConst94 = 6.46292254899834e-22 * fConst0;
	fConst95 = fConst0 * (fConst0 * (fConst0 * (fConst94 + 1.90693980601459e-18) + 1.50232520281226e-16) + -4.60849521761724e-15);
	double fConst96 = 5.35331274684644e-23 * fConst0;
	fConst97 = fConst7 * (2.28327872258084e-22 - fConst96);
	double fConst98 = 7.49463784558502e-23 * fConst0;
	fConst99 = fConst3 * (fConst0 * (fConst98 + 1.42192566937971e-19) + 1.82351647640129e-18);
	double fConst100 = 1.42633616270852e-24 * fConst0;
	fConst101 = fConst24 * (fConst100 + -1.09504183633979e-23);
	double fConst102 = 1.99687062779193e-24 * fConst0;
	fConst103 = fConst7 * (fConst0 * (-6.81396696133963e-21 - fConst102) + 2.91281128466384e-20);
	double fConst104 = 7.71154779846327e-24 * fConst0;
	fConst105 = fConst3 * (fConst0 * (fConst0 * (fConst104 + -1.69540313347742e-20) + -2.30032611736055e-20) + -1.1695046812109e-18);
	double fConst106 = 2.89429155669983e-22 * fConst0;
	fConst107 = fConst0 * (fConst0 * (fConst0 * (3.53068929659391e-19 - fConst106) + -5.29245486955245e-19) + 1.8433980870469e-16);
	double fConst108 = 1.91907672110931e-23 * fConst0;
	fConst109 = fConst7 * (fConst0 * (fConst108 + -1.51999272980726e-21) + 5.70819680645209e-21);
	double fConst110 = 1.72198049774899e-23 * fConst0;
	fConst111 = fConst3 * (fConst0 * (fConst0 * (-9.02012542250564e-20 - fConst110) + 4.03664924154006e-18) + 4.55514105154877e-17);
	double fConst112 = 8.26759555451817e-23 * fConst0;
	fConst113 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst112 + -2.85205152688842e-19) + 1.02988983768651e-17) + -1.30486302011578e-17) + 4.60849521761724e-15);
	double fConst114 = 3.10298692727022e-21 * fConst0;
	fConst115 = fConst0 * (fConst0 * (fConst0 * (5.85227663541147e-18 - fConst114) + 4.52040346187673e-16) + -1.38254856528517e-14);
	fConst116 = fConst0 * (fConst0 * (fConst92 + -1.01914938263382e-18) + -7.84401701489674e-17) + 2.3978309714178e-15;
	fConst117 = fConst0 * (fConst0 * (-1.00931167420926e-18 - fConst94) + -8.09581504534201e-15) + 1.88251499873295e-12;
	fConst118 = fConst3 * (fConst0 * (fConst96 + -7.45798938006809e-20) + -9.51366134408682e-19);
	fConst119 = fConst0 * (fConst0 * (fConst0 * (-3.81003746381788e-20 - fConst98) + -5.94292545384613e-16) + 2.27939559550162e-14);
	fConst120 = fConst7 * (fConst0 * (3.5767908251347e-21 - fConst100) + -1.52089143936082e-20);
	fConst121 = fConst3 * (fConst0 * (fConst0 * (fConst102 + 1.82179039185982e-21) + -9.49297111470724e-18) + -1.21367136860993e-16);
	double fConst122 = 2.75934712704441e-25 * fConst0;
	fConst123 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst122 + -3.12199525275548e-20) + 5.30246139994882e-17) + 1.0728203737318e-15) + -1.46188085151362e-14);
	double fConst124 = 1.03563581534178e-23 * fConst0;
	fConst125 = fConst0 * (fConst0 * (fConst0 * (6.50953455217104e-19 - fConst124) + 3.31397583073083e-15) + -1.8977285636845e-13);
	fConst126 = fConst3 * (fConst0 * (fConst0 * (4.94969107575399e-20 - fConst108) + -2.11680921042765e-18) + -2.37841533602171e-17);
	fConst127 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst110 + 4.71517417813316e-20) + -1.29316168998563e-16) + -1.68649232502658e-14) + 5.69392631443596e-13);
	double fConst128 = 1.97096223360315e-24 * fConst0;
	fConst129 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst128 + -3.09060187214354e-19) + 6.59092588471003e-16) + 9.2998714565051e-14) + -4.74569021150667e-12);
	double fConst130 = 7.39739868101268e-23 * fConst0;
	fConst131 = fConst0 * (fConst0 * (fConst0 * (6.44090677084358e-18 - fConst130) + 4.05825720651041e-14) + -9.41572149153703e-12);
	double fConst132 = 1.59749650223354e-23 * fConst0;
	fConst133 = fConst7 * (fConst0 * (fConst132 + -1.83436272017657e-20) + -2.34192947398536e-19);
	double fConst134 = 1.998570092156e-22 * fConst0;
	fConst135 = fConst3 * (fConst0 * (-1.14653956981738e-18 - fConst134) + 1.46378358378244e-17);
	double fConst136 = 1.6929383555757e-22 * fConst0;
	fConst137 = fConst3 * (fConst0 * (fConst0 * (fConst136 + -2.51813759914817e-19) + -3.25715096523769e-17) + 3.66237907101966e-16);
	double fConst138 = 2.11797394272023e-21 * fConst0;
	fConst139 = fConst0 * (fConst0 * (fConst0 * (-1.55559920878143e-17 - fConst138) + 1.20492938589323e-15) + 1.22893205803126e-14);
	double fConst140 = 4.80177494473307e-22 * fConst0;
	fConst141 = fConst3 * (fConst0 * (fConst140 + 3.75592049622019e-20) + -3.83652955426848e-19);
	double fConst142 = 4.30861503266556e-22 * fConst0;
	fConst143 = fConst0 * (fConst0 * (fConst0 * (3.81387961202917e-18 - fConst142) + -3.00465040562453e-16) + -3.07233014507816e-15);
	double fConst144 = 3.56887516456429e-23 * fConst0;
	fConst145 = fConst7 * (fConst144 + 4.56655744516168e-22);
	double fConst146 = 4.99642523039001e-23 * fConst0;
	fConst147 = fConst3 * (fConst0 * (2.84385133875941e-19 - fConst146) + -3.64703295280259e-18);
	double fConst148 = 2.85267232541704e-24 * fConst0;
	fConst149 = fConst24 * (7.30027890893193e-24 - fConst148);
	double fConst150 = 3.99374125558385e-24 * fConst0;
	fConst151 = fConst7 * (fConst0 * (fConst150 + 4.54264464089309e-21) + 5.82562256932768e-20);
	double fConst152 = 1.54230955969265e-23 * fConst0;
	fConst153 = fConst3 * (fConst0 * (fConst0 * (1.13026875565161e-20 - fConst152) + -4.60065223472111e-20) + 2.33900936242179e-18);
	double fConst154 = 1.92952770446655e-22 * fConst0;
	fConst155 = fConst0 * (fConst0 * (fConst0 * (fConst154 + 7.06137859318782e-19) + 1.05849097391049e-18) + 1.22893205803126e-16);
	double fConst156 = 3.83815344221861e-23 * fConst0;
	fConst157 = fConst7 * (fConst0 * (1.01332848653817e-21 - fConst156) + 1.14163936129042e-20);
	double fConst158 = 3.44396099549798e-23 * fConst0;
	fConst159 = fConst3 * (fConst0 * (fConst0 * (fConst158 + 6.01341694833709e-20) + 8.07329848308013e-18) + -9.11028210309754e-17);
	double fConst160 = 1.65351911090363e-22 * fConst0;
	fConst161 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (1.90136768459228e-19 - fConst160) + 2.05977967537302e-17) + 2.60972604023156e-17) + 3.07233014507816e-15);
	double fConst162 = 2.06865795151348e-21 * fConst0;
	fConst163 = fConst0 * (fConst0 * (fConst0 * (fConst162 + 1.17045532708229e-17) + -9.04080692375347e-16) + -9.21699043523448e-15);
	fConst164 = fConst0 * (fConst0 * (-2.03829876526765e-18 - fConst140) + 1.56880340297935e-16) + 1.5985539809452e-15;
	fConst165 = fConst0 * (fConst0 * (fConst142 + -2.01862334841852e-18) + 1.6191630090684e-14) + 1.2550099991553e-12;
	fConst166 = fConst3 * (fConst0 * (-1.49159787601362e-19 - fConst144) + 1.90273226881736e-18);
	fConst167 = fConst0 * (fConst0 * (fConst0 * (fConst146 + -7.62007492763576e-20) + 1.18858509076923e-15) + 1.51959706366775e-14);
	fConst168 = fConst7 * (fConst0 * (fConst148 + -2.38452721675646e-21) + -3.04178287872164e-20);
	fConst169 = fConst3 * (fConst0 * (fConst0 * (-1.21452692790654e-21 - fConst150) + -1.89859422294145e-17) + 2.42734273721987e-16);
	double fConst170 = 5.51869425408882e-25 * fConst0;
	fConst171 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (2.08133016850365e-20 - fConst170) + 1.06049227998976e-16) + -2.1456407474636e-15) + -9.74587234342413e-15);
	double fConst172 = 6.90423876894517e-24 * fConst0;
	fConst173 = fConst0 * (fConst0 * (fConst0 * (fConst172 + 1.30190691043421e-18) + -6.62795166146167e-15) + -1.26515237578967e-13);
	fConst174 = fConst3 * (fConst0 * (fConst0 * (fConst156 + -3.29979405050266e-20) + -4.23361842085529e-18) + 4.75683067204341e-17);
	fConst175 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-3.14344945208878e-20 - fConst158) + -2.58632337997126e-16) + 3.37298465005315e-14) + 3.79595087629064e-13);
	double fConst176 = 3.9419244672063e-24 * fConst0;
	fConst177 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (2.06040124809569e-19 - fConst176) + 1.31818517694201e-15) + -1.85997429130102e-13) + -3.16379347433778e-12);
	double fConst178 = 4.93159912067512e-23 * fConst0;
	fConst179 = fConst0 * (fConst0 * (fConst0 * (fConst178 + 1.28818135416872e-17) + -8.11651441302083e-14) + -6.27714766102469e-12);
	fConst180 = fConst7 * (fConst0 * (-1.83436272017657e-20 - fConst132) + 2.34192947398536e-19);
	fConst181 = fConst3 * (fConst0 * (1.14653956981738e-18 - fConst134) + 1.46378358378244e-17);
	fConst182 = fConst3 * (fConst0 * (fConst0 * (-2.51813759914817e-19 - fConst136) + 3.25715096523769e-17) + 3.66237907101966e-16);
	fConst183 = fConst0 * (fConst0 * (fConst0 * (1.55559920878143e-17 - fConst138) + 1.20492938589323e-15) + -1.22893205803126e-14);
	fConst184 = fConst3 * (fConst0 * (fConst140 + -3.75592049622019e-20) + -3.83652955426848e-19);
	fConst185 = fConst0 * (fConst0 * (fConst0 * (-3.81387961202917e-18 - fConst142) + -3.00465040562453e-16) + 3.07233014507816e-15);
	fConst186 = fConst7 * (fConst144 + -4.56655744516168e-22);
	fConst187 = fConst3 * (fConst0 * (-2.84385133875941e-19 - fConst146) + -3.64703295280259e-18);
	fConst188 = fConst24 * (fConst148 + 7.30027890893193e-24);
	fConst189 = fConst7 * (fConst0 * (4.54264464089309e-21 - fConst150) + -5.82562256932768e-20);
	fConst190 = fConst3 * (fConst0 * (fConst0 * (fConst152 + 1.13026875565161e-20) + 4.60065223472111e-20) + 2.33900936242179e-18);
	fConst191 = fConst0 * (fConst0 * (fConst0 * (fConst154 + -7.06137859318782e-19) + 1.05849097391049e-18) + -1.22893205803126e-16);
	fConst192 = fConst7 * (fConst0 * (fConst156 + 1.01332848653817e-21) + -1.14163936129042e-20);
	fConst193 = fConst3 * (fConst0 * (fConst0 * (6.01341694833709e-20 - fConst158) + -8.07329848308013e-18) + -9.11028210309754e-17);
	fConst194 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst160 + 1.90136768459228e-19) + -2.05977967537302e-17) + 2.60972604023156e-17) + -3.07233014507816e-15);
	fConst195 = fConst0 * (fConst0 * (fConst0 * (fConst162 + -1.17045532708229e-17) + -9.04080692375347e-16) + 9.21699043523448e-15);
	fConst196 = fConst0 * (fConst0 * (2.03829876526765e-18 - fConst140) + 1.56880340297935e-16) + -1.5985539809452e-15;
	fConst197 = fConst0 * (fConst0 * (fConst142 + 2.01862334841852e-18) + 1.6191630090684e-14) + -1.2550099991553e-12;
	fConst198 = fConst3 * (fConst0 * (1.49159787601362e-19 - fConst144) + 1.90273226881736e-18);
	fConst199 = fConst0 * (fConst0 * (fConst0 * (fConst146 + 7.62007492763576e-20) + 1.18858509076923e-15) + -1.51959706366775e-14);
	fConst200 = fConst7 * (fConst0 * (-2.38452721675646e-21 - fConst148) + 3.04178287872164e-20);
	fConst201 = fConst3 * (fConst0 * (fConst0 * (fConst150 + -1.21452692790654e-21) + 1.89859422294145e-17) + 2.42734273721987e-16);
	fConst202 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst170 + 2.08133016850365e-20) + -1.06049227998976e-16) + -2.1456407474636e-15) + 9.74587234342413e-15);
	fConst203 = fConst0 * (fConst0 * (fConst0 * (fConst172 + -1.30190691043421e-18) + -6.62795166146167e-15) + 1.26515237578967e-13);
	fConst204 = fConst3 * (fConst0 * (fConst0 * (-3.29979405050266e-20 - fConst156) + 4.23361842085529e-18) + 4.75683067204341e-17);
	fConst205 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst158 + -3.14344945208878e-20) + 2.58632337997126e-16) + 3.37298465005315e-14) + -3.79595087629064e-13);
	fConst206 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst176 + 2.06040124809569e-19) + -1.31818517694201e-15) + -1.85997429130102e-13) + 3.16379347433778e-12);
	fConst207 = fConst0 * (fConst0 * (fConst0 * (fConst178 + -1.28818135416872e-17) + -8.11651441302083e-14) + 6.27714766102469e-12);
	fConst208 = fConst7 * (fConst0 * (fConst84 + 2.75154408026486e-20) + 1.17096473699268e-19);
	fConst209 = fConst3 * (fConst0 * (fConst86 + 5.73269784908691e-19) + -7.31891791891218e-18);
	fConst210 = fConst3 * (fConst0 * (fConst0 * (fConst88 + 3.77720639872226e-19) + 1.62857548261884e-17) + -1.83118953550983e-16);
	fConst211 = fConst0 * (fConst0 * (fConst0 * (fConst90 + 7.77799604390716e-18) + -6.02464692946613e-16) + -1.8433980870469e-14);
	fConst212 = fConst3 * (fConst0 * (-1.8779602481101e-20 - fConst92) + 1.91826477713424e-19);
	fConst213 = fConst0 * (fConst0 * (fConst0 * (fConst94 + -1.90693980601459e-18) + 1.50232520281226e-16) + 4.60849521761724e-15);
	fConst214 = fConst7 * (-2.28327872258084e-22 - fConst96);
	fConst215 = fConst3 * (fConst0 * (fConst98 + -1.42192566937971e-19) + 1.82351647640129e-18);
	fConst216 = fConst24 * (-1.09504183633979e-23 - fConst100);
	fConst217 = fConst7 * (fConst0 * (fConst102 + -6.81396696133963e-21) + -2.91281128466384e-20);
	fConst218 = fConst3 * (fConst0 * (fConst0 * (-1.69540313347742e-20 - fConst104) + 2.30032611736055e-20) + -1.1695046812109e-18);
	fConst219 = fConst0 * (fConst0 * (fConst0 * (-3.53068929659391e-19 - fConst106) + -5.29245486955245e-19) + -1.8433980870469e-16);
	fConst220 = fConst7 * (fConst0 * (-1.51999272980726e-21 - fConst108) + -5.70819680645209e-21);
	fConst221 = fConst3 * (fConst0 * (fConst0 * (fConst110 + -9.02012542250564e-20) + -4.03664924154006e-18) + 4.55514105154877e-17);
	fConst222 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-2.85205152688842e-19 - fConst112) + -1.02988983768651e-17) + -1.30486302011578e-17) + -4.60849521761724e-15);
	fConst223 = fConst0 * (fConst0 * (fConst0 * (-5.85227663541147e-18 - fConst114) + 4.52040346187673e-16) + 1.38254856528517e-14);
	fConst224 = fConst0 * (fConst0 * (fConst92 + 1.01914938263382e-18) + -7.84401701489674e-17) + -2.3978309714178e-15;
	fConst225 = fConst0 * (fConst0 * (1.00931167420926e-18 - fConst94) + -8.09581504534201e-15) + -1.88251499873295e-12;
	fConst226 = fConst3 * (fConst0 * (fConst96 + 7.45798938006809e-20) + -9.51366134408682e-19);
	fConst227 = fConst0 * (fConst0 * (fConst0 * (3.81003746381788e-20 - fConst98) + -5.94292545384613e-16) + -2.27939559550162e-14);
	fConst228 = fConst7 * (fConst0 * (fConst100 + 3.5767908251347e-21) + 1.52089143936082e-20);
	fConst229 = fConst3 * (fConst0 * (fConst0 * (1.82179039185982e-21 - fConst102) + 9.49297111470724e-18) + -1.21367136860993e-16);
	fConst230 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-3.12199525275548e-20 - fConst122) + -5.30246139994882e-17) + 1.0728203737318e-15) + 1.46188085151362e-14);
	fConst231 = fConst0 * (fConst0 * (fConst0 * (-6.50953455217104e-19 - fConst124) + 3.31397583073083e-15) + 1.8977285636845e-13);
	fConst232 = fConst3 * (fConst0 * (fConst0 * (fConst108 + 4.94969107575399e-20) + 2.11680921042765e-18) + -2.37841533602171e-17);
	fConst233 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (4.71517417813316e-20 - fConst110) + 1.29316168998563e-16) + -1.68649232502658e-14) + -5.69392631443596e-13);
	fConst234 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-3.09060187214354e-19 - fConst128) + -6.59092588471003e-16) + 9.2998714565051e-14) + 4.74569021150667e-12);
	fConst235 = fConst0 * (fConst0 * (fConst0 * (-6.44090677084358e-18 - fConst130) + 4.05825720651041e-14) + 9.41572149153703e-12);
	double fConst236 = std::tan(270.1769682087222 / fConst0);
	double fConst237 = mydsp_faustpower2_f(fConst236);
	fConst238 = 1.0 / fConst237;
	fConst239 = 2.0 * (1.0 - fConst238);
	double fConst240 = 1.0 / fConst236;
	fConst241 = (fConst240 + -1.0000000000000004) / fConst236 + 1.0;
	fConst242 = 1.0 / ((fConst240 + 1.0000000000000004) / fConst236 + 1.0);
	double fConst243 = std::tan(659.7344572538566 / fConst0);
	double fConst244 = mydsp_faustpower2_f(fConst243);
	fConst245 = 1.0 / fConst244;
	fConst246 = 2.0 * (1.0 - fConst245);
	double fConst247 = 1.0 / fConst243;
	fConst248 = (fConst247 + -1.0000000000000004) / fConst243 + 1.0;
	fConst249 = 1.0 / ((fConst247 + 1.0000000000000004) / fConst243 + 1.0);
	double fConst250 = std::tan(3769.9111843077517 / fConst0);
	double fConst251 = mydsp_faustpower2_f(fConst250);
	fConst252 = 1.0 / fConst251;
	fConst253 = 2.0 * (1.0 - fConst252);
	double fConst254 = 1.0 / fConst250;
	fConst255 = (fConst254 + -1.0000000000000004) / fConst250 + 1.0;
	fConst256 = 1.0 / ((fConst254 + 1.0000000000000004) / fConst250 + 1.0);
	double fConst257 = std::tan(20517.741620594938 / fConst0);
	double fConst258 = mydsp_faustpower2_f(fConst257);
	fConst259 = 1.0 / fConst258;
	fConst260 = 2.0 * (1.0 - fConst259);
	fConst261 = 1.0 / fConst257;
	fConst262 = (fConst261 + -1.0000000000000004) / fConst257 + 1.0;
	fConst263 = 1.0 / ((fConst261 + 1.0000000000000004) / fConst257 + 1.0);
	fConst264 = 1.0 - fConst261;
	double fConst265 = fConst261 + 1.0;
	fConst266 = 1.0 / fConst265;
	fConst267 = 1.0 - fConst254;
	double fConst268 = fConst254 + 1.0;
	fConst269 = 1.0 / fConst268;
	fConst270 = 1.0 - fConst247;
	double fConst271 = fConst247 + 1.0;
	fConst272 = 1.0 / fConst271;
	fConst273 = 1.0 - fConst240;
	double fConst274 = fConst240 + 1.0;
	fConst275 = 1.0 / fConst274;
	double fConst276 = 4.32789516321643e-20 * fConst0;
	fConst277 = fConst0 * (1.76059952898192e-18 - fConst276) + -9.8138212317832e-18;
	fConst278 = fConst0 * (fConst276 + -1.76059952898192e-18) + 9.8138212317832e-18;
	double fConst279 = 9.68624155577011e-23 * fConst0;
	fConst280 = fConst7 * (fConst0 * (5.55529015703311e-19 - fConst279) + -3.69922177510836e-18);
	double fConst281 = 6.05905322850301e-21 * fConst0;
	fConst282 = fConst3 * (fConst0 * (fConst281 + -3.47224379213122e-17) + 2.31213628220812e-16);
	double fConst283 = 6.91874396840722e-22 * fConst0;
	fConst284 = fConst24 * (fConst283 + -4.6124959789381e-21);
	fConst285 = fConst3 * (fConst0 * (fConst0 * (1.21495106849477e-19 - fConst283) + -5.91080564497569e-16) + 3.93534231394506e-15);
	fConst286 = fConst3 * (fConst0 * (fConst0 * (fConst279 + -9.59122413860399e-19) + 2.31840345387224e-15) + -1.54134240629515e-14);
	fConst287 = fConst0 * (fConst0 * (fConst0 * (5.99684930400747e-17 - fConst281) + -1.44908038300355e-13) + 9.63390117586717e-13);
	fConst288 = fConst7 * (fConst0 * (2.88742248281528e-18 - fConst283) + -1.92187332455754e-17);
	fConst289 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst283 + -3.00430509368582e-18) + 1.09731017637039e-15) + -2.46677102772048e-12) + 1.63972596414378e-11);
	fConst290 = fConst0 * (fConst0 * (fConst276 + -1.82089564663e-16) + 7.34564519198978e-15) + -4.08909217990967e-14;
	fConst291 = fConst0 * (fConst0 * (1.82089564663e-16 - fConst276) + -7.34564519198978e-15) + 4.08909217990967e-14;
	double fConst292 = 1.29836854896493e-19 * fConst0;
	fConst293 = fConst0 * (fConst292 + -1.76059952898192e-18) + -9.8138212317832e-18;
	fConst294 = fConst0 * (1.76059952898192e-18 - fConst292) + 9.8138212317832e-18;
	double fConst295 = 4.84312077788506e-22 * fConst0;
	fConst296 = fConst7 * (fConst0 * (fConst295 + -1.66658704710993e-18) + 3.69922177510836e-18);
	double fConst297 = 1.8177159685509e-20 * fConst0;
	fConst298 = fConst3 * (fConst0 * (3.47224379213122e-17 - fConst297) + 2.31213628220812e-16);
	double fConst299 = 3.45937198420361e-21 * fConst0;
	fConst300 = fConst24 * (1.38374879368143e-20 - fConst299);
	fConst301 = fConst3 * (fConst0 * (fConst0 * (fConst299 + -3.64485320548431e-19) + 5.91080564497569e-16) + 3.93534231394506e-15);
	fConst302 = fConst3 * (fConst0 * (fConst0 * (2.8773672415812e-18 - fConst295) + -2.31840345387224e-15) + -1.54134240629515e-14);
	fConst303 = fConst0 * (fConst0 * (fConst0 * (fConst297 + -5.99684930400747e-17) + -1.44908038300355e-13) + 2.89017035276015e-12);
	fConst304 = fConst7 * (fConst0 * (fConst299 + -8.66226744844584e-18) + 1.92187332455754e-17);
	fConst305 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (9.01291528105746e-18 - fConst299) + -1.09731017637039e-15) + -2.46677102772048e-12) + 4.91917789243133e-11);
	fConst306 = fConst0 * (fConst0 * (1.82089564663e-16 - fConst292) + 7.34564519198978e-15) + -1.2267276539729e-13;
	fConst307 = fConst0 * (fConst0 * (fConst292 + -1.82089564663e-16) + -7.34564519198978e-15) + 1.2267276539729e-13;
	double fConst308 = 8.65579032643287e-20 * fConst0;
	fConst309 = fConst0 * (-3.52119905796384e-18 - fConst308) + 1.96276424635664e-17;
	fConst310 = fConst0 * (fConst308 + 3.52119905796384e-18) + -1.96276424635664e-17;
	double fConst311 = 9.68624155577011e-22 * fConst0;
	fConst312 = fConst7 * (fConst0 * (1.11105803140662e-18 - fConst311) + 7.39844355021672e-18);
	double fConst313 = 1.2118106457006e-20 * fConst0;
	fConst314 = fConst3 * (fConst0 * (fConst313 + 6.94448758426244e-17) + -4.62427256441624e-16);
	double fConst315 = 6.91874396840722e-21 * fConst0;
	fConst316 = fConst24 * (fConst315 + -9.2249919578762e-21);
	fConst317 = fConst3 * (fConst0 * (fConst0 * (2.42990213698954e-19 - fConst315) + 1.18216112899514e-15) + -7.87068462789012e-15);
	fConst318 = fConst3 * (fConst0 * (fConst0 * (fConst311 + -1.9182448277208e-18) + -4.63680690774447e-15) + 3.0826848125903e-14);
	fConst319 = fConst0 * (fConst0 * (fConst0 * (-1.19936986080149e-16 - fConst313) + 2.8981607660071e-13) + 1.92678023517343e-12);
	fConst320 = fConst7 * (fConst0 * (5.77484496563056e-18 - fConst315) + 3.84374664911509e-17);
	fConst321 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst315 + -6.00861018737164e-18) + -2.19462035274078e-15) + 4.93354205544096e-12) + 3.27945192828755e-11);
	fConst322 = fConst0 * (fConst0 * (fConst308 + 3.64179129326e-16) + -1.46912903839796e-14) + -8.17818435981933e-14;
	fConst323 = fConst0 * (fConst0 * (-3.64179129326e-16 - fConst308) + 1.46912903839796e-14) + 8.17818435981933e-14;
	fConst324 = fConst0 * (3.52119905796384e-18 - fConst308) + 1.96276424635664e-17;
	fConst325 = fConst0 * (fConst308 + -3.52119905796384e-18) + -1.96276424635664e-17;
	fConst326 = fConst7 * (fConst0 * (fConst311 + 1.11105803140662e-18) + -7.39844355021672e-18);
	fConst327 = fConst3 * (fConst0 * (fConst313 + -6.94448758426244e-17) + -4.62427256441624e-16);
	fConst328 = fConst24 * (-9.2249919578762e-21 - fConst315);
	fConst329 = fConst3 * (fConst0 * (fConst0 * (fConst315 + 2.42990213698954e-19) + -1.18216112899514e-15) + -7.87068462789012e-15);
	fConst330 = fConst3 * (fConst0 * (fConst0 * (-1.9182448277208e-18 - fConst311) + 4.63680690774447e-15) + 3.0826848125903e-14);
	fConst331 = fConst0 * (fConst0 * (fConst0 * (1.19936986080149e-16 - fConst313) + 2.8981607660071e-13) + -1.92678023517343e-12);
	fConst332 = fConst7 * (fConst0 * (fConst315 + 5.77484496563056e-18) + -3.84374664911509e-17);
	fConst333 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-6.00861018737164e-18 - fConst315) + 2.19462035274078e-15) + 4.93354205544096e-12) + -3.27945192828755e-11);
	fConst334 = fConst0 * (fConst0 * (fConst308 + -3.64179129326e-16) + -1.46912903839796e-14) + 8.17818435981933e-14;
	fConst335 = fConst0 * (fConst0 * (3.64179129326e-16 - fConst308) + 1.46912903839796e-14) + -8.17818435981933e-14;
	fConst336 = fConst0 * (fConst292 + 1.76059952898192e-18) + -9.8138212317832e-18;
	fConst337 = fConst0 * (-1.76059952898192e-18 - fConst292) + 9.8138212317832e-18;
	fConst338 = fConst7 * (fConst0 * (-1.66658704710993e-18 - fConst295) + -3.69922177510836e-18);
	fConst339 = fConst3 * (fConst0 * (-3.47224379213122e-17 - fConst297) + 2.31213628220812e-16);
	fConst340 = fConst24 * (fConst299 + 1.38374879368143e-20);
	fConst341 = fConst3 * (fConst0 * (fConst0 * (-3.64485320548431e-19 - fConst299) + -5.91080564497569e-16) + 3.93534231394506e-15);
	fConst342 = fConst3 * (fConst0 * (fConst0 * (fConst295 + 2.8773672415812e-18) + 2.31840345387224e-15) + -1.54134240629515e-14);
	fConst343 = fConst0 * (fConst0 * (fConst0 * (fConst297 + 5.99684930400747e-17) + -1.44908038300355e-13) + -2.89017035276015e-12);
	fConst344 = fConst7 * (fConst0 * (-8.66226744844584e-18 - fConst299) + -1.92187332455754e-17);
	fConst345 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst299 + 9.01291528105746e-18) + 1.09731017637039e-15) + -2.46677102772048e-12) + -4.91917789243133e-11);
	fConst346 = fConst0 * (fConst0 * (-1.82089564663e-16 - fConst292) + 7.34564519198978e-15) + 1.2267276539729e-13;
	fConst347 = fConst0 * (fConst0 * (fConst292 + 1.82089564663e-16) + -7.34564519198978e-15) + -1.2267276539729e-13;
	fConst348 = fConst0 * (-1.76059952898192e-18 - fConst276) + -9.8138212317832e-18;
	fConst349 = fConst0 * (fConst276 + 1.76059952898192e-18) + 9.8138212317832e-18;
	fConst350 = fConst7 * (fConst0 * (fConst279 + 5.55529015703311e-19) + 3.69922177510836e-18);
	fConst351 = fConst3 * (fConst0 * (fConst281 + 3.47224379213122e-17) + 2.31213628220812e-16);
	fConst352 = fConst24 * (-4.6124959789381e-21 - fConst283);
	fConst353 = fConst3 * (fConst0 * (fConst0 * (fConst283 + 1.21495106849477e-19) + 5.91080564497569e-16) + 3.93534231394506e-15);
	fConst354 = fConst3 * (fConst0 * (fConst0 * (-9.59122413860399e-19 - fConst279) + -2.31840345387224e-15) + -1.54134240629515e-14);
	fConst355 = fConst0 * (fConst0 * (fConst0 * (-5.99684930400747e-17 - fConst281) + -1.44908038300355e-13) + -9.63390117586717e-13);
	fConst356 = fConst7 * (fConst0 * (fConst283 + 2.88742248281528e-18) + 1.92187332455754e-17);
	fConst357 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-3.00430509368582e-18 - fConst283) + -1.09731017637039e-15) + -2.46677102772048e-12) + -1.63972596414378e-11);
	fConst358 = fConst0 * (fConst0 * (fConst276 + 1.82089564663e-16) + 7.34564519198978e-15) + 4.08909217990967e-14;
	fConst359 = fConst0 * (fConst0 * (-1.82089564663e-16 - fConst276) + -7.34564519198978e-15) + -4.08909217990967e-14;
	double fConst360 = 4.09065163112436e-18 * fConst0;
	fConst361 = fConst0 * (-3.1996842386608e-16 - fConst360) + -3.26835558922325e-15;
	double fConst362 = 3.67052678836745e-18 * fConst0;
	fConst363 = fConst0 * (fConst362 + -3.2490595714095e-14) + -2.55967413440181e-12;
	double fConst364 = 3.04033952423208e-19 * fConst0;
	fConst365 = fConst3 * (-3.89026940579609e-18 - fConst364);
	double fConst366 = 4.25647533392492e-19 * fConst0;
	fConst367 = fConst0 * (fConst0 * (fConst366 + -2.42268872585805e-15) + -3.10692264109157e-14);
	double fConst368 = 4.86040672241183e-21 * fConst0;
	fConst369 = fConst7 * (-6.21913816572845e-20 - fConst368);
	double fConst370 = 6.80456941137657e-21 * fConst0;
	fConst371 = fConst3 * (fConst0 * (fConst370 + -3.86989777105262e-17) + -4.9628722562513e-16);
	double fConst372 = 2.8158557055486e-20 * fConst0;
	fConst373 = fConst0 * (fConst0 * (fConst0 * (fConst372 + 2.16252174019074e-16) + 4.38213044301358e-15) + 1.99261186829939e-14);
	double fConst374 = 1.76140761155593e-18 * fConst0;
	fConst375 = fConst0 * (fConst0 * (fConst374 + 1.35192183493901e-14) + 2.58417996561413e-13);
	double fConst376 = 6.53947709737567e-20 * fConst0;
	fConst377 = fConst3 * (fConst0 * (-8.63258735389604e-18 - fConst376) + -9.72567351449023e-17);
	double fConst378 = 5.86784894739014e-20 * fConst0;
	fConst379 = fConst0 * (fConst0 * (fConst0 * (fConst378 + -5.12285438072112e-16) + -6.87767642075504e-14) + -7.76108746456321e-13);
	double fConst380 = 2.95160491394304e-19 * fConst0;
	fConst381 = fConst0 * (fConst0 * (fConst0 * (fConst380 + 2.67064048181331e-15) + 3.79482593534319e-13) + 6.46231565548504e-12);
	double fConst382 = 1.8463230738282e-17 * fConst0;
	fConst383 = fConst0 * (fConst0 * (fConst382 + 1.6533269438527e-13) + 1.28277858723121e-11);
	fConst384 = fConst0 * (fConst360 + -3.1996842386608e-16) + 3.26835558922325e-15;
	fConst385 = fConst0 * (-3.2490595714095e-14 - fConst362) + 2.55967413440181e-12;
	fConst386 = fConst3 * (fConst364 + -3.89026940579609e-18);
	fConst387 = fConst0 * (fConst0 * (-2.42268872585805e-15 - fConst366) + 3.10692264109157e-14);
	fConst388 = fConst7 * (6.21913816572845e-20 - fConst368);
	fConst389 = fConst3 * (fConst0 * (fConst370 + 3.86989777105262e-17) + -4.9628722562513e-16);
	fConst390 = fConst0 * (fConst0 * (fConst0 * (fConst372 + -2.16252174019074e-16) + 4.38213044301358e-15) + -1.99261186829939e-14);
	fConst391 = fConst0 * (fConst0 * (1.35192183493901e-14 - fConst374) + -2.58417996561413e-13);
	fConst392 = fConst3 * (fConst0 * (8.63258735389604e-18 - fConst376) + -9.72567351449023e-17);
	fConst393 = fConst0 * (fConst0 * (fConst0 * (fConst378 + 5.12285438072112e-16) + -6.87767642075504e-14) + 7.76108746456321e-13);
	fConst394 = fConst0 * (fConst0 * (fConst0 * (fConst380 + -2.67064048181331e-15) + 3.79482593534319e-13) + -6.46231565548504e-12);
	fConst395 = fConst0 * (fConst0 * (1.6533269438527e-13 - fConst382) + -1.28277858723121e-11);
	double fConst396 = 8.18130326224871e-18 * fConst3;
	fConst397 = 6.5367111784465e-15 - fConst396;
	double fConst398 = 7.3410535767349e-18 * fConst3;
	fConst399 = fConst398 + 5.11934826880362e-12;
	double fConst400 = 8.51295066784983e-19 * fConst3;
	fConst401 = fConst0 * (fConst400 + 6.21384528218315e-14);
	double fConst402 = 1.94416268896473e-20 * fConst0;
	fConst403 = fConst402 + -1.24382763314569e-19;
	double fConst404 = 2.72182776455063e-20 * fConst0;
	fConst405 = -7.73979554210525e-17 - fConst404;
	double fConst406 = 1.12634228221944e-19 * fConst0;
	fConst407 = fConst0 * (fConst3 * (4.32504348038148e-16 - fConst406) + -3.98522373659879e-14);
	double fConst408 = 3.52281522311187e-18 * fConst3;
	fConst409 = fConst0 * (fConst408 + -5.16835993122826e-13);
	double fConst410 = 2.61579083895027e-19 * fConst0;
	fConst411 = fConst7 * (fConst410 + -1.72651747077921e-17);
	double fConst412 = 2.34713957895606e-19 * fConst0;
	fConst413 = fConst0 * (fConst3 * (-1.02457087614422e-15 - fConst412) + 1.55221749291264e-12);
	double fConst414 = 1.18064196557721e-18 * fConst0;
	fConst415 = fConst0 * (fConst3 * (5.34128096362661e-15 - fConst414) + -1.29246313109701e-11);
	double fConst416 = 3.69264614765639e-17 * fConst3;
	fConst417 = fConst0 * (fConst416 + -2.56555717446241e-11);
	fConst418 = 3.3066538877054e-13 * fConst3;
	fConst419 = fConst3 * (4.08274164682594e-20 * fConst3 + 9.9257445125026e-16);
	fConst420 = fConst3 * (1.68951342332916e-19 * fConst3 + -8.76426088602715e-15);
	fConst421 = 1.94513470289805e-16 - 3.9236862584254e-19 * fConst3;
	fConst422 = 3.52070936843408e-19 * fConst3 + 1.37553528415101e-13;
	fConst423 = 1.77096294836582e-18 * fConst3 + -7.58965187068638e-13;
	fConst424 = fConst396 + -6.5367111784465e-15;
	fConst425 = -5.11934826880362e-12 - fConst398;
	fConst426 = 6.08067904846417e-19 * fConst7;
	fConst427 = fConst0 * (-6.21384528218315e-14 - fConst400);
	fConst428 = fConst402 + 1.24382763314569e-19;
	fConst429 = 7.73979554210525e-17 - fConst404;
	fConst430 = fConst0 * (fConst3 * (-4.32504348038148e-16 - fConst406) + 3.98522373659879e-14);
	fConst431 = fConst0 * (5.16835993122826e-13 - fConst408);
	fConst432 = fConst7 * (fConst410 + 1.72651747077921e-17);
	fConst433 = fConst0 * (fConst3 * (1.02457087614422e-15 - fConst412) + -1.55221749291264e-12);
	fConst434 = fConst0 * (fConst3 * (-5.34128096362661e-15 - fConst414) + 1.29246313109701e-11);
	fConst435 = fConst0 * (2.56555717446241e-11 - fConst416);
	double fConst436 = 7.37390446187197e-16 * fConst0;
	fConst437 = fConst0 * (2.99972440013567e-14 - fConst436) + -1.67208717956279e-13;
	fConst438 = fConst0 * (fConst436 + -2.99972440013567e-14) + 1.67208717956279e-13;
	double fConst439 = 1.65035004622849e-18 * fConst0;
	fConst440 = fConst3 * (fConst0 * (9.46515045560758e-15 - fConst439) + -6.30276541464398e-14);
	double fConst441 = 1.03234662466208e-16 * fConst0;
	fConst442 = fConst0 * (fConst0 * (fConst441 + -5.91603840340603e-13) + 3.93943739504993e-12);
	double fConst443 = 1.17882146159178e-17 * fConst0;
	fConst444 = fConst7 * (fConst443 + -7.85880974394511e-17);
	fConst445 = fConst0 * (fConst0 * (fConst0 * (2.07004392829875e-15 - fConst443) + -1.0070880757276e-11) + 6.70506959004678e-11);
	double fConst446 = 1.47478089237439e-15 * fConst3;
	fConst447 = fConst446 + -3.34417435912558e-13;
	fConst448 = 3.34417435912558e-13 - fConst446;
	double fConst449 = 6.60140018491395e-18 * fConst0;
	fConst450 = fConst7 * (fConst449 + -1.89303009112152e-14);
	double fConst451 = 2.06469324932415e-16 * fConst3;
	fConst452 = fConst0 * (7.87887479009986e-12 - fConst451);
	double fConst453 = 4.71528584636711e-17 * fConst0;
	fConst454 = fConst7 * (1.57176194878902e-16 - fConst453);
	fConst455 = fConst0 * (fConst3 * (fConst453 + -4.1400878565975e-15) + 1.34101391800936e-10);
	fConst456 = 1.2605530829288e-13 - 9.90210027737093e-18 * fConst3;
	fConst457 = 7.07292876955067e-17 * fConst24;
	fConst458 = fConst3 * (2.0141761514552e-11 - 7.07292876955067e-17 * fConst3);
	fConst459 = fConst7 * (fConst449 + 1.89303009112152e-14);
	fConst460 = fConst0 * (fConst451 + -7.87887479009986e-12);
	fConst461 = fConst7 * (-1.57176194878902e-16 - fConst453);
	fConst462 = fConst0 * (fConst3 * (fConst453 + 4.1400878565975e-15) + -1.34101391800936e-10);
	fConst463 = fConst0 * (fConst436 + 2.99972440013567e-14) + 1.67208717956279e-13;
	fConst464 = fConst0 * (-2.99972440013567e-14 - fConst436) + -1.67208717956279e-13;
	fConst465 = fConst3 * (fConst0 * (-9.46515045560758e-15 - fConst439) + -6.30276541464398e-14);
	fConst466 = fConst0 * (fConst0 * (-5.91603840340603e-13 - fConst441) + -3.93943739504993e-12);
	fConst467 = fConst7 * (fConst443 + 7.85880974394511e-17);
	fConst468 = fConst0 * (fConst0 * (fConst0 * (-2.07004392829875e-15 - fConst443) + -1.0070880757276e-11) + -6.70506959004678e-11);
	double fConst469 = 2.54284690253705e-08 * fConst0;
	fConst470 = fConst0 * (1.69523126835804e-07 - fConst469);
	fConst471 = 5.0856938050741e-08 * fConst3;
	fConst472 = fConst0 * (-1.69523126835804e-07 - fConst469);
	fConst473 = fConst273 / fConst274;
	fConst474 = 1.0 / (fConst236 * fConst274);
	fConst475 = 0.0 - fConst474;
	fConst476 = 0.0 - 2.0 / fConst237;
	fConst477 = 1.0 - fConst273 / fConst236;
	fConst478 = 1.0 / (fConst274 / fConst236 + 1.0);
	fConst479 = fConst270 / fConst271;
	fConst480 = 1.0 / (fConst243 * fConst271);
	fConst481 = 0.0 - fConst480;
	fConst482 = 0.0 - 2.0 / fConst244;
	fConst483 = 1.0 - fConst270 / fConst243;
	fConst484 = 1.0 / (fConst271 / fConst243 + 1.0);
	fConst485 = fConst267 / fConst268;
	fConst486 = 1.0 / (fConst250 * fConst268);
	fConst487 = 0.0 - fConst486;
	fConst488 = 0.0 - 2.0 / fConst251;
	fConst489 = 1.0 - fConst267 / fConst250;
	fConst490 = 1.0 / (fConst268 / fConst250 + 1.0);
	fConst491 = 0.0 - 1.0 / (fConst257 * fConst265);
	fConst492 = 0.0 - 2.0 / fConst258;
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fCheckbox0 (*fCheckbox0_)
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
#define fVslider4 (*fVslider4_)
	int iSlow0 = int(double(fCheckbox0));
	double fSlow1 = 0.00036676987543879196 * (std::exp(3.0 * double(fVslider0)) + -1.0);
	double fSlow2 = 0.007000000000000006 * double(fVslider1);
	double fSlow3 = 0.00036676987543879196 * (std::exp(3.0 * double(fVslider2)) + -1.0);
	double fSlow4 = 0.007000000000000006 * (1.0 - double(fVslider3));
	double fSlow5 = 0.00036676987543879196 * (std::exp(3.0 * double(fVslider4)) + -1.0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec1[0] = fSlow1 + 0.993 * fRec1[1];
		fRec2[0] = fSlow2 + 0.993 * fRec2[1];
		fRec3[0] = fSlow3 + 0.993 * fRec3[1];
		fRec4[0] = fSlow4 + 0.993 * fRec4[1];
		double fTemp0 = fConst55 + fRec1[0] * (fConst53 + fRec4[0] * (fConst51 + fConst50 * fRec4[0]) + 6.40068780224617e-12) + fRec2[0] * (fConst49 + fRec1[0] * (fConst47 + fRec4[0] * (fConst45 + fConst44 * fRec4[0])) + fRec4[0] * (fConst43 + fConst42 * fRec4[0]) + 2.56027512089847e-13) + fRec4[0] * (fConst0 * (fConst41 + fConst40 * fRec4[0]) + -6.40068780224617e-12) + fRec3[0] * (fConst39 + fRec1[0] * (fConst37 + fRec4[0] * (fConst35 + fConst33 * fRec4[0])) + fRec2[0] * (fConst31 + fRec1[0] * (fConst29 + fRec4[0] * (fConst27 + fConst25 * fRec4[0])) + fRec4[0] * (fConst22 + fConst20 * fRec4[0])) + fRec4[0] * (fConst18 + fConst16 * fRec4[0]) + fRec3[0] * (fConst14 + fConst12 * fRec1[0] + fRec2[0] * (fConst10 + fConst8 * fRec1[0]))) + 3.20034390112309e-11;
		double fTemp1 = fConst83 + fRec1[0] * (fConst82 + fRec4[0] * (fConst81 + fConst80 * fRec4[0]) + 6.40068780224617e-12) + fRec2[0] * (fConst79 + fRec1[0] * (fConst78 + fRec4[0] * (fConst77 + fConst76 * fRec4[0])) + fRec4[0] * (fConst75 + fConst74 * fRec4[0]) + 2.56027512089847e-13) + fRec4[0] * (fConst0 * (fConst73 + fConst72 * fRec4[0]) + -6.40068780224617e-12) + fRec3[0] * (fConst71 + fRec1[0] * (fConst70 + fRec4[0] * (fConst69 + fConst68 * fRec4[0])) + fRec2[0] * (fConst67 + fRec1[0] * (fConst66 + fRec4[0] * (fConst65 + fConst64 * fRec4[0])) + fRec4[0] * (fConst63 + fConst62 * fRec4[0])) + fRec4[0] * (fConst61 + fConst60 * fRec4[0]) + fRec3[0] * (fConst59 + fConst58 * fRec1[0] + fRec2[0] * (fConst57 + fConst56 * fRec1[0]))) + 3.20034390112309e-11;
		double fTemp2 = fConst131 + fRec1[0] * (fConst129 + fRec4[0] * (fConst127 + fConst126 * fRec4[0]) + 3.20034390112309e-11) + fRec2[0] * (fConst125 + fRec1[0] * (fConst123 + fRec4[0] * (fConst121 + fConst120 * fRec4[0])) + fRec4[0] * (fConst119 + fConst118 * fRec4[0]) + 1.28013756044923e-12) + fRec4[0] * (fConst0 * (fConst117 + fConst116 * fRec4[0]) + -3.20034390112309e-11) + fRec3[0] * (fConst115 + fRec1[0] * (fConst113 + fRec4[0] * (fConst111 + fConst109 * fRec4[0])) + fRec2[0] * (fConst107 + fRec1[0] * (fConst105 + fRec4[0] * (fConst103 + fConst101 * fRec4[0])) + fRec4[0] * (fConst99 + fConst97 * fRec4[0])) + fRec4[0] * (fConst95 + fConst93 * fRec4[0]) + fRec3[0] * (fConst91 + fConst89 * fRec1[0] + fRec2[0] * (fConst87 + fConst85 * fRec1[0]))) + 1.60017195056154e-10;
		double fTemp3 = fConst179 + fRec1[0] * (fConst177 + fRec4[0] * (fConst175 + fConst174 * fRec4[0]) + 6.40068780224617e-11) + fRec2[0] * (fConst173 + fRec1[0] * (fConst171 + fRec4[0] * (fConst169 + fConst168 * fRec4[0])) + fRec4[0] * (fConst167 + fConst166 * fRec4[0]) + 2.56027512089847e-12) + fRec4[0] * (fConst0 * (fConst165 + fConst164 * fRec4[0]) + -6.40068780224617e-11) + fRec3[0] * (fConst163 + fRec1[0] * (fConst161 + fRec4[0] * (fConst159 + fConst157 * fRec4[0])) + fRec2[0] * (fConst155 + fRec1[0] * (fConst153 + fRec4[0] * (fConst151 + fConst149 * fRec4[0])) + fRec4[0] * (fConst147 + fConst145 * fRec4[0])) + fRec4[0] * (fConst143 + fConst141 * fRec4[0]) + fRec3[0] * (fConst139 + fConst137 * fRec1[0] + fRec2[0] * (fConst135 + fConst133 * fRec1[0]))) + 3.20034390112308e-10;
		double fTemp4 = fConst207 + fRec1[0] * (fConst206 + fRec4[0] * (fConst205 + fConst204 * fRec4[0]) + 6.40068780224617e-11) + fRec2[0] * (fConst203 + fRec1[0] * (fConst202 + fRec4[0] * (fConst201 + fConst200 * fRec4[0])) + fRec4[0] * (fConst199 + fConst198 * fRec4[0]) + 2.56027512089847e-12) + fRec4[0] * (fConst0 * (fConst197 + fConst196 * fRec4[0]) + -6.40068780224617e-11) + fRec3[0] * (fConst195 + fRec1[0] * (fConst194 + fRec4[0] * (fConst193 + fConst192 * fRec4[0])) + fRec2[0] * (fConst191 + fRec1[0] * (fConst190 + fRec4[0] * (fConst189 + fConst188 * fRec4[0])) + fRec4[0] * (fConst187 + fConst186 * fRec4[0])) + fRec4[0] * (fConst185 + fConst184 * fRec4[0]) + fRec3[0] * (fConst183 + fConst182 * fRec1[0] + fRec2[0] * (fConst181 + fConst180 * fRec1[0]))) + 3.20034390112308e-10;
		double fTemp5 = fConst235 + fRec1[0] * (fConst234 + fRec4[0] * (fConst233 + fConst232 * fRec4[0]) + 3.20034390112309e-11) + fRec2[0] * (fConst231 + fRec1[0] * (fConst230 + fRec4[0] * (fConst229 + fConst228 * fRec4[0])) + fRec4[0] * (fConst227 + fConst226 * fRec4[0]) + 1.28013756044923e-12) + fRec4[0] * (fConst0 * (fConst225 + fConst224 * fRec4[0]) + -3.20034390112309e-11) + fRec3[0] * (fConst223 + fRec1[0] * (fConst222 + fRec4[0] * (fConst221 + fConst220 * fRec4[0])) + fRec2[0] * (fConst219 + fRec1[0] * (fConst218 + fRec4[0] * (fConst217 + fConst216 * fRec4[0])) + fRec4[0] * (fConst215 + fConst214 * fRec4[0])) + fRec4[0] * (fConst213 + fConst212 * fRec4[0]) + fRec3[0] * (fConst211 + fConst210 * fRec1[0] + fRec2[0] * (fConst209 + fConst208 * fRec1[0]))) + 1.60017195056154e-10;
		double fTemp6 = double(input0[i0]);
		fVec0[0] = fTemp6;
		fRec13[0] = 0.0 - fConst266 * (fConst264 * fRec13[1] - (fTemp6 + fVec0[1]));
		fRec12[0] = fRec13[0] - fConst263 * (fConst262 * fRec12[2] + fConst260 * fRec12[1]);
		double fTemp7 = fRec12[2] + fRec12[0] + 2.0 * fRec12[1];
		fVec1[0] = fTemp7;
		fRec11[0] = 0.0 - fConst269 * (fConst267 * fRec11[1] - fConst263 * (fTemp7 + fVec1[1]));
		fRec10[0] = fRec11[0] - fConst256 * (fConst255 * fRec10[2] + fConst253 * fRec10[1]);
		double fTemp8 = fRec10[2] + fRec10[0] + 2.0 * fRec10[1];
		fVec2[0] = fTemp8;
		fRec9[0] = 0.0 - fConst272 * (fConst270 * fRec9[1] - fConst256 * (fTemp8 + fVec2[1]));
		fRec8[0] = fRec9[0] - fConst249 * (fConst248 * fRec8[2] + fConst246 * fRec8[1]);
		double fTemp9 = fRec8[2] + fRec8[0] + 2.0 * fRec8[1];
		fVec3[0] = fTemp9;
		fRec7[0] = 0.0 - fConst275 * (fConst273 * fRec7[1] - fConst249 * (fTemp9 + fVec3[1]));
		fRec6[0] = fRec7[0] - fConst242 * (fConst241 * fRec6[2] + fConst239 * fRec6[1]);
		double fTemp10 = fConst242 * (fRec6[2] + fRec6[0] + 2.0 * fRec6[1]);
		fRec5[0] = fTemp10 - (fTemp5 * fRec5[1] + fTemp4 * fRec5[2] + fTemp3 * fRec5[3] + fTemp2 * fRec5[4] + fTemp1 * fRec5[5]) / fTemp0;
		double fTemp11 = fConst0 * (fConst291 + fConst290 * fRec4[0]) + fRec1[0] * (fConst289 + fConst288 * fRec4[0]) + fRec2[0] * (fConst287 + fConst286 * fRec1[0]) + fRec3[0] * (fRec1[0] * (fConst285 + fConst284 * fRec4[0]) + fRec2[0] * (fConst282 + fConst280 * fRec1[0]) + fConst3 * (fConst278 + fConst277 * fRec4[0]));
		double fTemp12 = fConst0 * (fConst307 + fConst306 * fRec4[0]) + fRec1[0] * (fConst305 + fConst304 * fRec4[0]) + fRec2[0] * (fConst303 + fConst302 * fRec1[0]) + fRec3[0] * (fRec1[0] * (fConst301 + fConst300 * fRec4[0]) + fRec2[0] * (fConst298 + fConst296 * fRec1[0]) + fConst3 * (fConst294 + fConst293 * fRec4[0]));
		double fTemp13 = fConst0 * (fConst323 + fConst322 * fRec4[0]) + fRec1[0] * (fConst321 + fConst320 * fRec4[0]) + fRec2[0] * (fConst319 + fConst318 * fRec1[0]) + fRec3[0] * (fRec1[0] * (fConst317 + fConst316 * fRec4[0]) + fRec2[0] * (fConst314 + fConst312 * fRec1[0]) + fConst3 * (fConst310 + fConst309 * fRec4[0]));
		double fTemp14 = fConst0 * (fConst335 + fConst334 * fRec4[0]) + fRec1[0] * (fConst333 + fConst332 * fRec4[0]) + fRec2[0] * (fConst331 + fConst330 * fRec1[0]) + fRec3[0] * (fRec1[0] * (fConst329 + fConst328 * fRec4[0]) + fRec2[0] * (fConst327 + fConst326 * fRec1[0]) + fConst3 * (fConst325 + fConst324 * fRec4[0]));
		double fTemp15 = fConst0 * (fConst347 + fConst346 * fRec4[0]) + fRec1[0] * (fConst345 + fConst344 * fRec4[0]) + fRec2[0] * (fConst343 + fConst342 * fRec1[0]) + fRec3[0] * (fRec1[0] * (fConst341 + fConst340 * fRec4[0]) + fRec2[0] * (fConst339 + fConst338 * fRec1[0]) + fConst3 * (fConst337 + fConst336 * fRec4[0]));
		double fTemp16 = fConst0 * (fConst359 + fConst358 * fRec4[0]) + fRec1[0] * (fConst357 + fConst356 * fRec4[0]) + fRec2[0] * (fConst355 + fConst354 * fRec1[0]) + fRec3[0] * (fRec1[0] * (fConst353 + fConst352 * fRec4[0]) + fRec2[0] * (fConst351 + fConst350 * fRec1[0]) + fConst3 * (fConst349 + fConst348 * fRec4[0]));
		double fTemp17 = fRec3[0] * (fRec5[0] * fTemp16 + fTemp15 * fRec5[1] + fTemp14 * fRec5[2] + fTemp13 * fRec5[3] + fTemp12 * fRec5[4] + fTemp11 * fRec5[5]) / fTemp0;
		double fTemp18 = fConst383 + fRec1[0] * (fConst381 + fRec4[0] * (fConst379 + fConst377 * fRec4[0]) + 2.61733091315125e-11) + fRec2[0] * (fConst375 + fRec1[0] * (fConst373 + fRec4[0] * (fConst371 + fConst369 * fRec4[0])) + fRec4[0] * (fConst367 + fConst365 * fRec4[0]) + 1.0469323652605e-12) + fRec4[0] * (fConst0 * (fConst363 + fConst361 * fRec4[0]) + -2.61733091315125e-11) + 1.30866545657562e-10;
		double fTemp19 = fConst395 + fRec1[0] * (fConst394 + fRec4[0] * (fConst393 + fConst392 * fRec4[0]) + 2.61733091315125e-11) + fRec2[0] * (fConst391 + fRec1[0] * (fConst390 + fRec4[0] * (fConst389 + fConst388 * fRec4[0])) + fRec4[0] * (fConst387 + fConst386 * fRec4[0]) + 1.0469323652605e-12) + fRec4[0] * (fConst0 * (fConst385 + fConst384 * fRec4[0]) + -2.61733091315125e-11) + 1.30866545657562e-10;
		double fTemp20 = fConst417 + fRec1[0] * (fConst415 + fRec4[0] * (fConst413 + fConst411 * fRec4[0]) + 1.0469323652605e-10) + fRec2[0] * (fConst409 + fRec1[0] * (fConst407 + fConst7 * fRec4[0] * (fConst405 + fConst403 * fRec4[0])) + fRec4[0] * (fConst401 + fConst7 * (0.0 - 6.08067904846417e-19 * fRec4[0])) + 4.187729461042e-12) + fRec4[0] * (fConst0 * (fConst399 + fConst397 * fRec4[0]) + -1.0469323652605e-10) + 5.2346618263025e-10;
		double fTemp21 = fRec1[0] * (fConst3 * (fConst423 + fRec4[0] * (fConst422 + fConst421 * fRec4[0])) + 1.57039854789075e-10) + fRec2[0] * (fRec1[0] * (fConst420 + fRec4[0] * (fConst419 + fConst24 * (0.0 - 2.9162440334471e-20 * fRec4[0]))) + fConst3 * (fRec4[0] * (7.78053881159219e-18 * fRec4[0] + 4.84537745171611e-15) + -2.70384366987801e-14) + 6.281594191563e-12) + fRec4[0] * (fConst3 * (6.3993684773216e-16 * fRec4[0] + 6.498119142819e-14) + -1.57039854789075e-10) + 7.85199273945375e-10 - fConst418;
		double fTemp22 = fConst435 + fRec1[0] * (fConst434 + fRec4[0] * (fConst433 + fConst432 * fRec4[0]) + 1.0469323652605e-10) + fRec2[0] * (fConst431 + fRec1[0] * (fConst430 + fConst7 * fRec4[0] * (fConst429 + fConst428 * fRec4[0])) + fRec4[0] * (fConst427 + fConst426 * fRec4[0]) + 4.187729461042e-12) + fRec4[0] * (fConst0 * (fConst425 + fConst424 * fRec4[0]) + -1.0469323652605e-10) + 5.2346618263025e-10;
		fRec14[0] = fTemp10 - (fTemp22 * fRec14[1] + fTemp21 * fRec14[2] + fTemp20 * fRec14[3] + fTemp19 * fRec14[4]) / fTemp18;
		double fTemp23 = fRec1[0] * (fConst445 + fConst444 * fRec4[0]) + fRec2[0] * (fConst442 + fConst440 * fRec1[0]) + fConst0 * (fConst438 + fConst437 * fRec4[0]);
		double fTemp24 = fRec1[0] * (fConst455 + fConst454 * fRec4[0]) + fRec2[0] * (fConst452 + fConst450 * fRec1[0]) + fConst0 * (fConst448 + fConst447 * fRec4[0]);
		double fTemp25 = fRec1[0] * (fConst458 + fConst457 * fRec4[0]) + fConst3 * (fRec2[0] * (fConst456 * fRec1[0] + 1.18320768068121e-12) - 5.99944880027134e-14 * fRec4[0] + 5.99944880027134e-14);
		double fTemp26 = fRec1[0] * (fConst462 + fConst461 * fRec4[0]) + fRec2[0] * (fConst460 + fConst459 * fRec1[0]) + fConst0 * (fConst447 + fConst448 * fRec4[0]);
		double fTemp27 = fRec1[0] * (fConst468 + fConst467 * fRec4[0]) + fRec2[0] * (fConst466 + fConst465 * fRec1[0]) + fConst0 * (fConst464 + fConst463 * fRec4[0]);
		double fTemp28 = fRec3[0] * (fRec14[0] * fTemp27 + fTemp26 * fRec14[1] + fTemp25 * fRec14[2] + fTemp24 * fRec14[3] + fTemp23 * fRec14[4]) / fTemp18;
		fRec0[0] = ((iSlow0) ? ((signbit(fTemp28)) ? alembic_norm_negclip(fTemp28) : alembic_normclip(fTemp28)) : ((signbit(fTemp17)) ? alembic_brite_negclip(fTemp17) : alembic_briteclip(fTemp17))) - fConst5 * (fConst4 * fRec0[1] + fConst2 * fRec0[2]);
		fRec15[0] = fSlow5 + 0.993 * fRec15[1];
		double fTemp29 = fConst5 * fRec15[0] * (fConst472 * fRec0[0] + fConst471 * fRec0[1] + fConst470 * fRec0[2]);
		fRec19[0] = fConst249 * (fConst474 * fTemp9 + fConst475 * fVec3[1]) - fConst473 * fRec19[1];
		fRec18[0] = fRec19[0] - fConst242 * (fConst241 * fRec18[2] + fConst239 * fRec18[1]);
		double fTemp30 = fConst242 * (fConst238 * fRec18[0] + fConst476 * fRec18[1] + fConst238 * fRec18[2]);
		fRec17[0] = fTemp30 - (fTemp5 * fRec17[1] + fTemp4 * fRec17[2] + fTemp3 * fRec17[3] + fTemp2 * fRec17[4] + fTemp1 * fRec17[5]) / fTemp0;
		double fTemp31 = fRec3[0] * (fRec17[0] * fTemp16 + fTemp15 * fRec17[1] + fTemp14 * fRec17[2] + fTemp13 * fRec17[3] + fTemp12 * fRec17[4] + fTemp11 * fRec17[5]) / fTemp0;
		fRec20[0] = fTemp30 - (fTemp22 * fRec20[1] + fTemp21 * fRec20[2] + fTemp20 * fRec20[3] + fTemp19 * fRec20[4]) / fTemp18;
		double fTemp32 = fRec3[0] * (fRec20[0] * fTemp27 + fTemp26 * fRec20[1] + fTemp25 * fRec20[2] + fTemp24 * fRec20[3] + fTemp23 * fRec20[4]) / fTemp18;
		fRec16[0] = ((iSlow0) ? ((signbit(fTemp32)) ? alembic_norm_negclip(fTemp32) : alembic_normclip(fTemp32)) : ((signbit(fTemp31)) ? alembic_brite_negclip(fTemp31) : alembic_briteclip(fTemp31))) - fConst5 * (fConst4 * fRec16[1] + fConst2 * fRec16[2]);
		double fTemp33 = fConst5 * fRec15[0] * (fConst472 * fRec16[0] + fConst471 * fRec16[1] + fConst470 * fRec16[2]);
		double fTemp34 = fConst239 * fRec23[1];
		fRec25[0] = fConst256 * (fConst480 * fTemp8 + fConst481 * fVec2[1]) - fConst479 * fRec25[1];
		fRec24[0] = fRec25[0] - fConst249 * (fConst248 * fRec24[2] + fConst246 * fRec24[1]);
		fRec23[0] = fConst249 * (fConst245 * fRec24[0] + fConst482 * fRec24[1] + fConst245 * fRec24[2]) - fConst478 * (fConst477 * fRec23[2] + fTemp34);
		double fTemp35 = fRec23[2] + fConst478 * (fTemp34 + fConst477 * fRec23[0]);
		fRec22[0] = fTemp35 - (fTemp5 * fRec22[1] + fTemp4 * fRec22[2] + fTemp3 * fRec22[3] + fTemp2 * fRec22[4] + fTemp1 * fRec22[5]) / fTemp0;
		double fTemp36 = fRec3[0] * (fRec22[0] * fTemp16 + fTemp15 * fRec22[1] + fTemp14 * fRec22[2] + fTemp13 * fRec22[3] + fTemp12 * fRec22[4] + fTemp11 * fRec22[5]) / fTemp0;
		fRec26[0] = fTemp35 - (fTemp22 * fRec26[1] + fTemp21 * fRec26[2] + fTemp20 * fRec26[3] + fTemp19 * fRec26[4]) / fTemp18;
		double fTemp37 = fRec3[0] * (fRec26[0] * fTemp27 + fTemp26 * fRec26[1] + fTemp25 * fRec26[2] + fTemp24 * fRec26[3] + fTemp23 * fRec26[4]) / fTemp18;
		fRec21[0] = ((iSlow0) ? ((signbit(fTemp37)) ? alembic_norm_negclip(fTemp37) : alembic_normclip(fTemp37)) : ((signbit(fTemp36)) ? alembic_brite_negclip(fTemp36) : alembic_briteclip(fTemp36))) - fConst5 * (fConst4 * fRec21[1] + fConst2 * fRec21[2]);
		double fTemp38 = fConst5 * fRec15[0] * (fConst472 * fRec21[0] + fConst471 * fRec21[1] + fConst470 * fRec21[2]);
		double fTemp39 = fConst239 * fRec29[1];
		double fTemp40 = fConst246 * fRec30[1];
		fRec32[0] = fConst263 * (fConst486 * fTemp7 + fConst487 * fVec1[1]) - fConst485 * fRec32[1];
		fRec31[0] = fRec32[0] - fConst256 * (fConst255 * fRec31[2] + fConst253 * fRec31[1]);
		fRec30[0] = fConst256 * (fConst252 * fRec31[0] + fConst488 * fRec31[1] + fConst252 * fRec31[2]) - fConst484 * (fConst483 * fRec30[2] + fTemp40);
		fRec29[0] = fRec30[2] + fConst484 * (fTemp40 + fConst483 * fRec30[0]) - fConst478 * (fConst477 * fRec29[2] + fTemp39);
		double fTemp41 = fRec29[2] + fConst478 * (fTemp39 + fConst477 * fRec29[0]);
		fRec28[0] = fTemp41 - (fTemp5 * fRec28[1] + fTemp4 * fRec28[2] + fTemp3 * fRec28[3] + fTemp2 * fRec28[4] + fTemp1 * fRec28[5]) / fTemp0;
		double fTemp42 = fRec3[0] * (fRec28[0] * fTemp16 + fTemp15 * fRec28[1] + fTemp14 * fRec28[2] + fTemp13 * fRec28[3] + fTemp12 * fRec28[4] + fTemp11 * fRec28[5]) / fTemp0;
		fRec33[0] = fTemp41 - (fTemp22 * fRec33[1] + fTemp21 * fRec33[2] + fTemp20 * fRec33[3] + fTemp19 * fRec33[4]) / fTemp18;
		double fTemp43 = fRec3[0] * (fRec33[0] * fTemp27 + fTemp26 * fRec33[1] + fTemp25 * fRec33[2] + fTemp24 * fRec33[3] + fTemp23 * fRec33[4]) / fTemp18;
		fRec27[0] = ((iSlow0) ? ((signbit(fTemp43)) ? alembic_norm_negclip(fTemp43) : alembic_normclip(fTemp43)) : ((signbit(fTemp42)) ? alembic_brite_negclip(fTemp42) : alembic_briteclip(fTemp42))) - fConst5 * (fConst4 * fRec27[1] + fConst2 * fRec27[2]);
		double fTemp44 = fConst5 * fRec15[0] * (fConst472 * fRec27[0] + fConst471 * fRec27[1] + fConst470 * fRec27[2]);
		double fTemp45 = fConst239 * fRec36[1];
		double fTemp46 = fConst246 * fRec37[1];
		double fTemp47 = fConst253 * fRec38[1];
		fRec40[0] = fConst491 * fVec0[1] - fConst266 * (fConst264 * fRec40[1] - fConst261 * fTemp6);
		fRec39[0] = fRec40[0] - fConst263 * (fConst262 * fRec39[2] + fConst260 * fRec39[1]);
		fRec38[0] = fConst263 * (fConst259 * fRec39[0] + fConst492 * fRec39[1] + fConst259 * fRec39[2]) - fConst490 * (fConst489 * fRec38[2] + fTemp47);
		fRec37[0] = fRec38[2] + fConst490 * (fTemp47 + fConst489 * fRec38[0]) - fConst484 * (fConst483 * fRec37[2] + fTemp46);
		fRec36[0] = fRec37[2] + fConst484 * (fTemp46 + fConst483 * fRec37[0]) - fConst478 * (fConst477 * fRec36[2] + fTemp45);
		double fTemp48 = fRec36[2] + fConst478 * (fTemp45 + fConst477 * fRec36[0]);
		fRec35[0] = fTemp48 - (fRec35[1] * fTemp5 + fRec35[2] * fTemp4 + fRec35[3] * fTemp3 + fRec35[4] * fTemp2 + fRec35[5] * fTemp1) / fTemp0;
		double fTemp49 = fRec3[0] * (fRec35[0] * fTemp16 + fRec35[1] * fTemp15 + fRec35[2] * fTemp14 + fRec35[3] * fTemp13 + fRec35[4] * fTemp12 + fRec35[5] * fTemp11) / fTemp0;
		fRec41[0] = fTemp48 - (fRec41[1] * fTemp22 + fRec41[2] * fTemp21 + fRec41[3] * fTemp20 + fRec41[4] * fTemp19) / fTemp18;
		double fTemp50 = fRec3[0] * (fRec41[0] * fTemp27 + fRec41[1] * fTemp26 + fRec41[2] * fTemp25 + fRec41[3] * fTemp24 + fRec41[4] * fTemp23) / fTemp18;
		fRec34[0] = ((iSlow0) ? ((signbit(fTemp50)) ? alembic_norm_negclip(fTemp50) : alembic_normclip(fTemp50)) : ((signbit(fTemp49)) ? alembic_brite_negclip(fTemp49) : alembic_briteclip(fTemp49))) - fConst5 * (fConst4 * fRec34[1] + fConst2 * fRec34[2]);
		double fTemp51 = fConst5 * fRec15[0] * (fConst472 * fRec34[0] + fConst471 * fRec34[1] + fConst470 * fRec34[2]);
		output0[i0] = FAUSTFLOAT(((signbit(fTemp51)) ? alembic_out_negclip(fTemp51) : alembic_outclip(fTemp51)) + ((signbit(fTemp44)) ? alembic_out_negclip(fTemp44) : alembic_outclip(fTemp44)) + ((signbit(fTemp38)) ? alembic_out_negclip(fTemp38) : alembic_outclip(fTemp38)) + ((signbit(fTemp33)) ? alembic_out_negclip(fTemp33) : alembic_outclip(fTemp33)) + ((signbit(fTemp29)) ? alembic_out_negclip(fTemp29) : alembic_outclip(fTemp29)));
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fVec0[1] = fVec0[0];
		fRec13[1] = fRec13[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
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
		for (int j0 = 5; j0 > 0; j0 = j0 - 1) {
			fRec5[j0] = fRec5[j0 - 1];
		}
		for (int j1 = 4; j1 > 0; j1 = j1 - 1) {
			fRec14[j1] = fRec14[j1 - 1];
		}
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		fRec15[1] = fRec15[0];
		fRec19[1] = fRec19[0];
		fRec18[2] = fRec18[1];
		fRec18[1] = fRec18[0];
		for (int j2 = 5; j2 > 0; j2 = j2 - 1) {
			fRec17[j2] = fRec17[j2 - 1];
		}
		for (int j3 = 4; j3 > 0; j3 = j3 - 1) {
			fRec20[j3] = fRec20[j3 - 1];
		}
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fRec23[2] = fRec23[1];
		fRec23[1] = fRec23[0];
		for (int j4 = 5; j4 > 0; j4 = j4 - 1) {
			fRec22[j4] = fRec22[j4 - 1];
		}
		for (int j5 = 4; j5 > 0; j5 = j5 - 1) {
			fRec26[j5] = fRec26[j5 - 1];
		}
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fRec29[2] = fRec29[1];
		fRec29[1] = fRec29[0];
		for (int j6 = 5; j6 > 0; j6 = j6 - 1) {
			fRec28[j6] = fRec28[j6 - 1];
		}
		for (int j7 = 4; j7 > 0; j7 = j7 - 1) {
			fRec33[j7] = fRec33[j7 - 1];
		}
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		for (int j8 = 5; j8 > 0; j8 = j8 - 1) {
			fRec35[j8] = fRec35[j8 - 1];
		}
		for (int j9 = 4; j9 > 0; j9 = j9 - 1) {
			fRec41[j9] = fRec41[j9 - 1];
		}
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
	}
#undef fCheckbox0
#undef fVslider0
#undef fVslider1
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
	case BRIGHT_L: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case BASS_L: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case MASTER_L: 
		fVslider4_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case MIDDLE_L: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TREBLE_L: 
		fVslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME_L: 
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
   BASS_L, 
   MASTER_L, 
   MIDDLE_L, 
   TREBLE_L, 
   VOLUME_L, 
   BRIGHT_L, 
} PortIndex;
*/

} // end namespace gx_studiopre
