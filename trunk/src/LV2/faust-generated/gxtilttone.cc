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
	double fConst3;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec1[2];
	double fConst5;
	double fConst7;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec2[2];
	double fConst9;
	double fConst11;
	double fConst13;
	double fConst14;
	double fConst16;
	double fConst18;
	double fConst20;
	double fConst22;
	double fConst24;
	double fConst25;
	double fConst26;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec3[2];
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
	double fConst43;
	double fConst44;
	double fConst46;
	double fConst47;
	double fConst49;
	double fConst51;
	double fConst52;
	double fConst54;
	double fConst56;
	double fConst58;
	double fConst59;
	double fConst61;
	double fConst62;
	double fConst63;
	double fConst64;
	double fConst65;
	double fConst66;
	double fConst67;
	double fConst68;
	double fConst70;
	double fConst71;
	double fConst72;
	double fConst73;
	double fConst74;
	double fConst75;
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
	double fConst97;
	double fConst98;
	double fConst100;
	double fConst101;
	double fConst104;
	double fConst105;
	double fConst107;
	double fConst108;
	double fConst111;
	double fConst112;
	double fConst114;
	double fConst115;
	double fConst118;
	double fConst119;
	double fConst120;
	double fConst121;
	double fConst122;
	double fVec0[2];
	double fConst123;
	double fConst125;
	double fRec12[2];
	double fRec11[3];
	double fVec1[2];
	double fConst126;
	double fConst128;
	double fRec10[2];
	double fRec9[3];
	double fVec2[2];
	double fConst129;
	double fConst131;
	double fRec8[2];
	double fRec7[3];
	double fVec3[2];
	double fConst132;
	double fConst134;
	double fRec6[2];
	double fRec5[3];
	double fRec4[5];
	double fConst136;
	double fConst138;
	double fConst139;
	double fConst140;
	double fConst142;
	double fConst143;
	double fConst145;
	double fConst146;
	double fConst148;
	double fConst150;
	double fConst151;
	double fConst152;
	double fConst154;
	double fConst155;
	double fConst157;
	double fConst158;
	double fConst159;
	double fConst161;
	double fConst162;
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
	double fRec0[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec13[2];
	double fConst178;
	double fConst179;
	double fConst180;
	double fConst181;
	double fRec17[2];
	double fRec16[3];
	double fConst182;
	double fRec15[5];
	double fRec14[2];
	double fConst183;
	double fConst184;
	double fConst185;
	double fConst186;
	double fConst187;
	double fRec22[2];
	double fRec21[3];
	double fConst188;
	double fRec20[3];
	double fRec19[5];
	double fRec18[2];
	double fConst189;
	double fConst190;
	double fConst191;
	double fConst192;
	double fConst193;
	double fRec28[2];
	double fRec27[3];
	double fConst194;
	double fRec26[3];
	double fRec25[3];
	double fRec24[5];
	double fRec23[2];
	double fConst195;
	double fConst196;
	double fConst197;
	double fRec35[2];
	double fRec34[3];
	double fConst198;
	double fRec33[3];
	double fRec32[3];
	double fRec31[3];
	double fRec30[5];
	double fRec29[2];

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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec1[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec2[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec3[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fVec0[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec12[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec11[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fVec1[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec10[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec9[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fVec2[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec8[l10] = 0.0;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec7[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fVec3[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec6[l13] = 0.0;
	for (int l14 = 0; l14 < 3; l14 = l14 + 1) fRec5[l14] = 0.0;
	for (int l15 = 0; l15 < 5; l15 = l15 + 1) fRec4[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec0[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec13[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec17[l18] = 0.0;
	for (int l19 = 0; l19 < 3; l19 = l19 + 1) fRec16[l19] = 0.0;
	for (int l20 = 0; l20 < 5; l20 = l20 + 1) fRec15[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec14[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec22[l22] = 0.0;
	for (int l23 = 0; l23 < 3; l23 = l23 + 1) fRec21[l23] = 0.0;
	for (int l24 = 0; l24 < 3; l24 = l24 + 1) fRec20[l24] = 0.0;
	for (int l25 = 0; l25 < 5; l25 = l25 + 1) fRec19[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec18[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec28[l27] = 0.0;
	for (int l28 = 0; l28 < 3; l28 = l28 + 1) fRec27[l28] = 0.0;
	for (int l29 = 0; l29 < 3; l29 = l29 + 1) fRec26[l29] = 0.0;
	for (int l30 = 0; l30 < 3; l30 = l30 + 1) fRec25[l30] = 0.0;
	for (int l31 = 0; l31 < 5; l31 = l31 + 1) fRec24[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fRec23[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fRec35[l33] = 0.0;
	for (int l34 = 0; l34 < 3; l34 = l34 + 1) fRec34[l34] = 0.0;
	for (int l35 = 0; l35 < 3; l35 = l35 + 1) fRec33[l35] = 0.0;
	for (int l36 = 0; l36 < 3; l36 = l36 + 1) fRec32[l36] = 0.0;
	for (int l37 = 0; l37 < 3; l37 = l37 + 1) fRec31[l37] = 0.0;
	for (int l38 = 0; l38 < 5; l38 = l38 + 1) fRec30[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec29[l39] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 2.08313095376176e-05 * fConst0;
	double fConst2 = fConst1 + 9.71421943566398e-05;
	fConst3 = (9.71421943566398e-05 - fConst1) / fConst2;
	double fConst4 = 2.29741267120048e-20 * fConst0;
	fConst5 = fConst0 * (fConst0 * (fConst0 * (fConst4 + 6.50194364851177e-17) + 4.61728181436945e-14) + 7.98254064513374e-12) + -4.91708085742792e-25;
	double fConst6 = 4.59482534240096e-20 * fConst0;
	fConst7 = fConst0 * (fConst0 * (fConst0 * (-1.30038872970235e-16 - fConst6) + -9.23456362873891e-14) + -1.59650812902675e-11);
	double fConst8 = 2.32491795072961e-20 * fConst0;
	fConst9 = fConst0 * (fConst0 * (fConst0 * (-3.52160359068941e-17 - fConst8) + 1.83300570278997e-14) + 8.87429618975008e-12) + 4.14677436110845e-10;
	double fConst10 = 4.64983590145922e-20 * fConst0;
	fConst11 = fConst0 * (fConst0 * (fConst0 * (fConst10 + 7.04320718137881e-17) + -3.66601140557995e-14) + -1.77485923795002e-11);
	double fConst12 = 9.29967180291844e-20 * fConst0;
	fConst13 = fConst0 * (fConst0 * (fConst0 * (-3.84360911986598e-16 - fConst12) + -4.45548735927406e-13) + -9.98720416827966e-11) + -1.65870974444338e-09;
	fConst14 = fConst0 * (fConst0 * (fConst0 * (fConst12 + 3.5336200597687e-16) + 3.79597819598007e-13) + 8.2686476087768e-11);
	double fConst15 = 1.61878313287101e-20 * fConst0;
	fConst16 = fConst0 * (fConst0 * (fConst15 + 1.69238926121966e-17) + 3.65434490572681e-15) + -3.68781064307094e-28;
	double fConst17 = 3.23756626574203e-20 * fConst0;
	fConst18 = fConst0 * (fConst0 * (-3.38477852243932e-17 - fConst17) + -7.30868981145362e-15) + 7.37562128614188e-28;
	double fConst19 = 3.65431292527433e-20 * fConst0;
	fConst20 = fConst0 * (fConst0 * (fConst19 + 3.23733154656106e-18) + -1.64523449411233e-16) + 9.7449197486048e-13;
	double fConst21 = 1.82715646263716e-20 * fConst0;
	fConst22 = fConst0 * (fConst0 * (fConst0 * (-1.61866577328053e-18 - fConst21) + 8.22617247056166e-17) + -4.8724598743024e-13) + 4.91708085742792e-26;
	double fConst23 = 7.30862585054866e-20 * fConst0;
	fConst24 = fConst0 * (fConst0 * (fConst0 * (-1.67322263662277e-16 - fConst23) + -5.1124129373811e-14) + -1.94898394972096e-12) + 1.96683234297117e-25;
	fConst25 = fConst0 * (fConst0 * (fConst0 * (fConst23 + 1.42960177493781e-16) + 3.6417513972127e-14) + -5.41394578846342e-14);
	fConst26 = fConst0 * (fConst0 * (fConst0 * (fConst23 + 2.16046435999268e-16) + 8.0537360177179e-14) + 5.95523076493215e-12);
	fConst27 = fConst0 * (fConst0 * (fConst0 * (fConst12 + 4.46358724006055e-16) + 5.77450568586205e-13) + 1.34243172872854e-10);
	fConst28 = fConst0 * (fConst0 * (fConst0 * (fConst4 + -6.50194364851177e-17) + 4.61728181436945e-14) + -7.98254064513374e-12) + -4.91708085742792e-25;
	fConst29 = fConst0 * (fConst0 * (fConst0 * (1.30038872970235e-16 - fConst6) + -9.23456362873891e-14) + 1.59650812902675e-11);
	fConst30 = fConst0 * (fConst0 * (fConst0 * (3.52160359068941e-17 - fConst8) + 1.83300570278997e-14) + -8.87429618975008e-12) + 4.14677436110845e-10;
	fConst31 = fConst0 * (fConst0 * (fConst0 * (fConst10 + -7.04320718137881e-17) + -3.66601140557995e-14) + 1.77485923795002e-11);
	fConst32 = fConst0 * (fConst0 * (fConst0 * (3.84360911986598e-16 - fConst12) + -4.45548735927406e-13) + 9.98720416827966e-11) + -1.65870974444338e-09;
	fConst33 = fConst0 * (fConst0 * (fConst0 * (fConst12 + -3.5336200597687e-16) + 3.79597819598007e-13) + -8.2686476087768e-11);
	fConst34 = fConst0 * (fConst0 * (fConst15 + -1.69238926121966e-17) + 3.65434490572681e-15) + 3.68781064307094e-28;
	fConst35 = fConst0 * (fConst0 * (3.38477852243932e-17 - fConst17) + -7.30868981145362e-15) + -7.37562128614188e-28;
	fConst36 = fConst0 * (fConst0 * (fConst19 + -3.23733154656106e-18) + -1.64523449411233e-16) + -9.7449197486048e-13;
	fConst37 = fConst0 * (fConst0 * (fConst0 * (1.61866577328053e-18 - fConst21) + 8.22617247056166e-17) + 4.8724598743024e-13) + 4.91708085742792e-26;
	fConst38 = fConst0 * (fConst0 * (fConst0 * (1.67322263662277e-16 - fConst23) + -5.1124129373811e-14) + 1.94898394972096e-12) + 1.96683234297117e-25;
	fConst39 = fConst0 * (fConst0 * (fConst0 * (fConst23 + -1.42960177493781e-16) + 3.6417513972127e-14) + 5.41394578846342e-14);
	fConst40 = fConst0 * (fConst0 * (fConst0 * (fConst23 + -2.16046435999268e-16) + 8.0537360177179e-14) + -5.95523076493215e-12);
	fConst41 = fConst0 * (fConst0 * (fConst0 * (fConst12 + -4.46358724006055e-16) + 5.77450568586205e-13) + -1.34243172872854e-10);
	double fConst42 = 9.18965068480191e-20 * fConst0;
	fConst43 = mydsp_faustpower2_f(fConst0);
	fConst44 = fConst0 * (fConst43 * (1.30038872970235e-16 - fConst42) + -1.59650812902675e-11) + -1.96683234297117e-24;
	double fConst45 = 1.83793013696038e-19 * fConst0;
	fConst46 = fConst0 * (fConst43 * (fConst45 + -2.60077745940471e-16) + 3.1930162580535e-11);
	fConst47 = fConst0 * (fConst43 * (fConst12 + -7.04320718137881e-17) + -1.77485923795002e-11) + 1.65870974444338e-09;
	double fConst48 = 1.85993436058369e-19 * fConst0;
	fConst49 = fConst0 * (fConst43 * (1.40864143627576e-16 - fConst48) + 3.54971847590003e-11);
	double fConst50 = 3.71986872116738e-19 * fConst0;
	fConst51 = fConst0 * (fConst43 * (fConst50 + -7.68721823973197e-16) + 1.99744083365593e-10) + -6.63483897777351e-09;
	fConst52 = fConst0 * (fConst43 * (7.06724011953741e-16 - fConst50) + -1.65372952175536e-10);
	double fConst53 = 6.47513253148406e-20 * fConst0;
	fConst54 = fConst43 * (3.38477852243932e-17 - fConst53) + 7.37562128614188e-28;
	double fConst55 = 1.29502650629681e-19 * fConst0;
	fConst56 = fConst43 * (fConst55 + -6.76955704487864e-17) + -1.47512425722838e-27;
	double fConst57 = 1.46172517010973e-19 * fConst0;
	fConst58 = fConst43 * (6.47466309312212e-18 - fConst57) + -1.94898394972096e-12;
	fConst59 = fConst0 * (fConst43 * (fConst23 + -3.23733154656106e-18) + 9.7449197486048e-13) + 1.96683234297117e-25;
	double fConst60 = 2.92345034021946e-19 * fConst0;
	fConst61 = fConst0 * (fConst43 * (fConst60 + -3.34644527324554e-16) + 3.89796789944192e-12) + 7.86732937188467e-25;
	fConst62 = fConst0 * (fConst43 * (2.85920354987563e-16 - fConst60) + 1.08278915769268e-13);
	fConst63 = fConst0 * (fConst43 * (4.32092871998536e-16 - fConst60) + -1.19104615298643e-11);
	fConst64 = fConst0 * (fConst43 * (8.92717448012109e-16 - fConst50) + -2.68486345745707e-10);
	fConst65 = fConst43 * (1.37844760272029e-19 * fConst43 + -9.23456362873891e-14) + -2.95024851445675e-24;
	fConst66 = fConst43 * (1.84691272574778e-13 - 2.75689520544057e-19 * fConst43);
	fConst67 = fConst43 * (-3.66601140557995e-14 - 1.39495077043777e-19 * fConst43) + 2.48806461666507e-09;
	fConst68 = fConst43 * (2.78990154087553e-19 * fConst43 + 7.33202281115989e-14);
	double fConst69 = 5.57980308175106e-19 * fConst43;
	fConst70 = fConst43 * (8.91097471854812e-13 - fConst69) + -9.95225846666026e-09;
	fConst71 = fConst43 * (fConst69 + -7.59195639196014e-13);
	fConst72 = 9.71269879722608e-20 * fConst43 + -7.30868981145362e-15;
	fConst73 = 1.46173796229072e-14 - 1.94253975944522e-19 * fConst43;
	fConst74 = 2.1925877551646e-19 * fConst43 + 3.29046898822466e-16;
	fConst75 = fConst43 * (-1.64523449411233e-16 - 1.0962938775823e-19 * fConst43) + 2.95024851445675e-25;
	double fConst76 = 4.38517551032919e-19 * fConst43;
	fConst77 = fConst43 * (1.02248258747622e-13 - fConst76) + 1.1800994057827e-24;
	fConst78 = fConst43 * (fConst76 + -7.2835027944254e-14);
	fConst79 = fConst43 * (fConst76 + -1.61074720354358e-13);
	fConst80 = fConst43 * (fConst69 + -1.15490113717241e-12);
	fConst81 = fConst0 * (fConst43 * (-1.30038872970235e-16 - fConst42) + 1.59650812902675e-11) + -1.96683234297117e-24;
	fConst82 = fConst0 * (fConst43 * (fConst45 + 2.60077745940471e-16) + -3.1930162580535e-11);
	fConst83 = fConst0 * (fConst43 * (fConst12 + 7.04320718137881e-17) + 1.77485923795002e-11) + 1.65870974444338e-09;
	fConst84 = fConst0 * (fConst43 * (-1.40864143627576e-16 - fConst48) + -3.54971847590003e-11);
	fConst85 = fConst0 * (fConst43 * (fConst50 + 7.68721823973197e-16) + -1.99744083365593e-10) + -6.63483897777351e-09;
	fConst86 = fConst0 * (fConst43 * (-7.06724011953741e-16 - fConst50) + 1.65372952175536e-10);
	fConst87 = fConst43 * (-3.38477852243932e-17 - fConst53) + -7.37562128614188e-28;
	fConst88 = fConst43 * (fConst55 + 6.76955704487864e-17) + 1.47512425722838e-27;
	fConst89 = fConst43 * (-6.47466309312212e-18 - fConst57) + 1.94898394972096e-12;
	fConst90 = fConst0 * (fConst43 * (fConst23 + 3.23733154656106e-18) + -9.7449197486048e-13) + 1.96683234297117e-25;
	fConst91 = fConst0 * (fConst43 * (fConst60 + 3.34644527324554e-16) + -3.89796789944192e-12) + 7.86732937188467e-25;
	fConst92 = fConst0 * (fConst43 * (-2.85920354987563e-16 - fConst60) + -1.08278915769268e-13);
	fConst93 = fConst0 * (fConst43 * (-4.32092871998536e-16 - fConst60) + 1.19104615298643e-11);
	fConst94 = fConst0 * (fConst43 * (-8.92717448012109e-16 - fConst50) + 2.68486345745707e-10);
	double fConst95 = std::tan(270.1769682087222 / fConst0);
	double fConst96 = mydsp_faustpower2_f(fConst95);
	fConst97 = 1.0 / fConst96;
	fConst98 = 2.0 * (1.0 - fConst97);
	double fConst99 = 1.0 / fConst95;
	fConst100 = (fConst99 + -1.0000000000000004) / fConst95 + 1.0;
	fConst101 = 1.0 / ((fConst99 + 1.0000000000000004) / fConst95 + 1.0);
	double fConst102 = std::tan(659.7344572538566 / fConst0);
	double fConst103 = mydsp_faustpower2_f(fConst102);
	fConst104 = 1.0 / fConst103;
	fConst105 = 2.0 * (1.0 - fConst104);
	double fConst106 = 1.0 / fConst102;
	fConst107 = (fConst106 + -1.0000000000000004) / fConst102 + 1.0;
	fConst108 = 1.0 / ((fConst106 + 1.0000000000000004) / fConst102 + 1.0);
	double fConst109 = std::tan(3769.9111843077517 / fConst0);
	double fConst110 = mydsp_faustpower2_f(fConst109);
	fConst111 = 1.0 / fConst110;
	fConst112 = 2.0 * (1.0 - fConst111);
	double fConst113 = 1.0 / fConst109;
	fConst114 = (fConst113 + -1.0000000000000004) / fConst109 + 1.0;
	fConst115 = 1.0 / ((fConst113 + 1.0000000000000004) / fConst109 + 1.0);
	double fConst116 = std::tan(20517.741620594938 / fConst0);
	double fConst117 = mydsp_faustpower2_f(fConst116);
	fConst118 = 1.0 / fConst117;
	fConst119 = 2.0 * (1.0 - fConst118);
	fConst120 = 1.0 / fConst116;
	fConst121 = (fConst120 + -1.0000000000000004) / fConst116 + 1.0;
	fConst122 = 1.0 / ((fConst120 + 1.0000000000000004) / fConst116 + 1.0);
	fConst123 = 1.0 - fConst120;
	double fConst124 = fConst120 + 1.0;
	fConst125 = 1.0 / fConst124;
	fConst126 = 1.0 - fConst113;
	double fConst127 = fConst113 + 1.0;
	fConst128 = 1.0 / fConst127;
	fConst129 = 1.0 - fConst106;
	double fConst130 = fConst106 + 1.0;
	fConst131 = 1.0 / fConst130;
	fConst132 = 1.0 - fConst99;
	double fConst133 = fConst99 + 1.0;
	fConst134 = 1.0 / fConst133;
	double fConst135 = 9.8607192519763e-16 * fConst0;
	fConst136 = fConst0 * (3.66844210330959e-12 - fConst135) + -5.84016130407215e-10;
	double fConst137 = 4.82764380044673e-19 * fConst0;
	fConst138 = fConst0 * (fConst0 * (fConst137 + -8.0460730007444e-17) + -3.45844530442491e-12) + 5.7640755073748e-10;
	fConst139 = fConst0 * (fConst0 * (8.0460730007444e-17 - fConst137) + 3.45844530442491e-12) + -5.7640755073748e-10;
	fConst140 = fConst0 * (fConst135 + -3.66844210330959e-12) + 5.84016130407215e-10;
	double fConst141 = 7.4702418575578e-15 * fConst0;
	fConst142 = fConst0 * (1.59088484003545e-12 - fConst141) + -5.76407550737481e-11;
	fConst143 = fConst0 * (fConst141 + -1.59088484003545e-12) + 5.76407550737481e-11;
	double fConst144 = 3.65730590942934e-18 * fConst0;
	fConst145 = fConst0 * (fConst144 + -6.09550984904878e-16) + -9.63708565903573e-28;
	fConst146 = fConst0 * (6.09550984904878e-16 - fConst144) + 9.63708565903573e-28;
	double fConst147 = 1.97214385039526e-15 * fConst43;
	fConst148 = fConst147 + -1.16803226081443e-09;
	double fConst149 = 1.93105752017869e-18 * fConst0;
	fConst150 = fConst43 * (1.60921460014888e-16 - fConst149) + 1.15281510147496e-09;
	fConst151 = fConst43 * (fConst149 + -1.60921460014888e-16) + -1.15281510147496e-09;
	fConst152 = 1.16803226081443e-09 - fConst147;
	double fConst153 = 1.49404837151156e-14 * fConst43;
	fConst154 = fConst153 + -1.15281510147496e-10;
	fConst155 = 1.15281510147496e-10 - fConst153;
	double fConst156 = 1.46292236377174e-17 * fConst0;
	fConst157 = 1.21910196980976e-15 - fConst156;
	fConst158 = fConst156 + -1.21910196980976e-15;
	fConst159 = mydsp_faustpower3_f(fConst0);
	double fConst160 = 2.89658628026804e-18 * fConst43;
	fConst161 = fConst160 + 6.91689060884983e-12;
	fConst162 = -6.91689060884983e-12 - fConst160;
	double fConst163 = 2.1943835456576e-17 * fConst43;
	fConst164 = fConst163 + 1.92741713180715e-27;
	fConst165 = -1.92741713180715e-27 - fConst163;
	fConst166 = fConst43 * (-1.60921460014888e-16 - fConst149) + -1.15281510147496e-09;
	fConst167 = fConst43 * (fConst149 + 1.60921460014888e-16) + 1.15281510147496e-09;
	fConst168 = -1.21910196980976e-15 - fConst156;
	fConst169 = fConst156 + 1.21910196980976e-15;
	fConst170 = fConst0 * (fConst135 + 3.66844210330959e-12) + 5.84016130407215e-10;
	fConst171 = fConst0 * (fConst0 * (fConst137 + 8.0460730007444e-17) + -3.45844530442491e-12) + -5.7640755073748e-10;
	fConst172 = fConst0 * (fConst0 * (-8.0460730007444e-17 - fConst137) + 3.45844530442491e-12) + 5.7640755073748e-10;
	fConst173 = fConst0 * (-3.66844210330959e-12 - fConst135) + -5.84016130407215e-10;
	fConst174 = fConst0 * (fConst141 + 1.59088484003545e-12) + 5.76407550737481e-11;
	fConst175 = fConst0 * (-1.59088484003545e-12 - fConst141) + -5.76407550737481e-11;
	fConst176 = fConst0 * (fConst144 + 6.09550984904878e-16) + -9.63708565903573e-28;
	fConst177 = fConst0 * (-6.09550984904878e-16 - fConst144) + 9.63708565903573e-28;
	fConst178 = fConst0 / fConst2;
	fConst179 = fConst132 / fConst133;
	fConst180 = 1.0 / (fConst95 * fConst133);
	fConst181 = 0.0 - fConst180;
	fConst182 = 0.0 - 2.0 / fConst96;
	fConst183 = 1.0 - fConst132 / fConst95;
	fConst184 = 1.0 / (fConst133 / fConst95 + 1.0);
	fConst185 = fConst129 / fConst130;
	fConst186 = 1.0 / (fConst102 * fConst130);
	fConst187 = 0.0 - fConst186;
	fConst188 = 0.0 - 2.0 / fConst103;
	fConst189 = 1.0 - fConst129 / fConst102;
	fConst190 = 1.0 / (fConst130 / fConst102 + 1.0);
	fConst191 = fConst126 / fConst127;
	fConst192 = 1.0 / (fConst109 * fConst127);
	fConst193 = 0.0 - fConst192;
	fConst194 = 0.0 - 2.0 / fConst110;
	fConst195 = 1.0 - fConst126 / fConst109;
	fConst196 = 1.0 / (fConst127 / fConst109 + 1.0);
	fConst197 = 0.0 - 1.0 / (fConst116 * fConst124);
	fConst198 = 0.0 - 2.0 / fConst117;
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
	double fSlow0 = 0.004073836948085289 * (std::exp(1.0 - double(fVslider0)) + -1.0);
	double fSlow1 = 0.004073836948085289 * (std::exp(double(fVslider1)) + -1.0);
	double fSlow2 = 0.007000000000000006 * double(fVslider2);
	double fSlow3 = 0.00036676987543879196 * (std::exp(3.0 * double(fVslider3)) + -1.0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec1[0] = fSlow0 + 0.993 * fRec1[1];
		fRec2[0] = fSlow1 + 0.993 * fRec2[1];
		fRec3[0] = fSlow2 + 0.993 * fRec3[1];
		double fTemp0 = fConst27 + fRec3[0] * (fConst26 + fRec1[0] * (fConst25 + fConst24 * fRec1[0] + -4.14677436110847e-11) + fRec2[0] * (fConst22 * fRec1[0] + fConst0 * (fConst20 + fRec2[0] * (fConst18 + fConst16 * fRec1[0])) + -9.83416171485584e-26) + 8.29354872221687e-11) + fRec1[0] * (fConst14 + fConst13 * fRec1[0] + 1.23855856617587e-09) + fRec2[0] * (fConst11 + fConst9 * fRec1[0] + fRec2[0] * (fConst7 + fConst5 * fRec1[0] + 9.83416171485584e-25) + -8.2935487222169e-10) + 2.49901210097839e-09;
		double fTemp1 = fConst41 + fRec3[0] * (fConst40 + fRec1[0] * (fConst39 + fConst38 * fRec1[0] + -4.14677436110847e-11) + fRec2[0] * (fConst37 * fRec1[0] + fConst0 * (fConst36 + fRec2[0] * (fConst35 + fConst34 * fRec1[0])) + -9.83416171485584e-26) + 8.29354872221687e-11) + fRec1[0] * (fConst33 + fConst32 * fRec1[0] + 1.23855856617587e-09) + fRec2[0] * (fConst31 + fConst30 * fRec1[0] + fRec2[0] * (fConst29 + fConst28 * fRec1[0] + 9.83416171485584e-25) + -8.2935487222169e-10) + 2.49901210097839e-09;
		double fTemp2 = fConst64 + fRec3[0] * (fConst63 + fRec1[0] * (fConst62 + fConst61 * fRec1[0] + -1.65870974444339e-10) + fRec2[0] * (fConst59 * fRec1[0] + fConst0 * (fConst58 + fRec2[0] * (fConst56 + fConst54 * fRec1[0])) + -3.93366468594234e-25) + 3.31741948888675e-10) + fRec1[0] * (fConst52 + fConst51 * fRec1[0] + 4.95423426470347e-09) + fRec2[0] * (fConst49 + fConst47 * fRec1[0] + fRec2[0] * (fConst46 + fConst44 * fRec1[0] + 3.93366468594234e-24) + -3.31741948888676e-09) + 9.99604840391357e-09;
		double fTemp3 = fConst80 + fRec3[0] * (fConst79 + fRec1[0] * (fConst78 + fConst77 * fRec1[0] + -2.48806461666508e-10) + fRec2[0] * (fConst75 * fRec1[0] + fConst43 * (fConst74 + fRec2[0] * (fConst73 + fConst72 * fRec1[0])) + -5.90049702891351e-25) + 4.97612923333012e-10) + fRec1[0] * (fConst71 + fConst70 * fRec1[0] + 7.43135139705521e-09) + fRec2[0] * (fConst68 + fConst67 * fRec1[0] + fRec2[0] * (fConst66 + fConst65 * fRec1[0] + 5.90049702891351e-24) + -4.97612923333014e-09) + 1.49940726058704e-08;
		double fTemp4 = fConst94 + fRec3[0] * (fConst93 + fRec1[0] * (fConst92 + fConst91 * fRec1[0] + -1.65870974444339e-10) + fRec2[0] * (fConst90 * fRec1[0] + fConst0 * (fConst89 + fRec2[0] * (fConst88 + fConst87 * fRec1[0])) + -3.93366468594234e-25) + 3.31741948888675e-10) + fRec1[0] * (fConst86 + fConst85 * fRec1[0] + 4.95423426470347e-09) + fRec2[0] * (fConst84 + fConst83 * fRec1[0] + fRec2[0] * (fConst82 + fConst81 * fRec1[0] + 3.93366468594234e-24) + -3.31741948888676e-09) + 9.99604840391357e-09;
		double fTemp5 = double(input0[i0]);
		fVec0[0] = fTemp5;
		fRec12[0] = 0.0 - fConst125 * (fConst123 * fRec12[1] - (fTemp5 + fVec0[1]));
		fRec11[0] = fRec12[0] - fConst122 * (fConst121 * fRec11[2] + fConst119 * fRec11[1]);
		double fTemp6 = fRec11[2] + fRec11[0] + 2.0 * fRec11[1];
		fVec1[0] = fTemp6;
		fRec10[0] = 0.0 - fConst128 * (fConst126 * fRec10[1] - fConst122 * (fTemp6 + fVec1[1]));
		fRec9[0] = fRec10[0] - fConst115 * (fConst114 * fRec9[2] + fConst112 * fRec9[1]);
		double fTemp7 = fRec9[2] + fRec9[0] + 2.0 * fRec9[1];
		fVec2[0] = fTemp7;
		fRec8[0] = 0.0 - fConst131 * (fConst129 * fRec8[1] - fConst115 * (fTemp7 + fVec2[1]));
		fRec7[0] = fRec8[0] - fConst108 * (fConst107 * fRec7[2] + fConst105 * fRec7[1]);
		double fTemp8 = fRec7[2] + fRec7[0] + 2.0 * fRec7[1];
		fVec3[0] = fTemp8;
		fRec6[0] = 0.0 - fConst134 * (fConst132 * fRec6[1] - fConst108 * (fTemp8 + fVec3[1]));
		fRec5[0] = fRec6[0] - fConst101 * (fConst100 * fRec5[2] + fConst98 * fRec5[1]);
		fRec4[0] = fConst101 * (fRec5[2] + fRec5[0] + 2.0 * fRec5[1]) - (fTemp4 * fRec4[1] + fTemp3 * fRec4[2] + fTemp2 * fRec4[3] + fTemp1 * fRec4[4]) / fTemp0;
		double fTemp9 = fRec3[0] * (fConst43 * fRec2[0] * (fConst146 + fConst145 * fRec1[0]) + fConst0 * (fConst143 + fConst142 * fRec1[0])) + fConst0 * (fConst140 + fRec2[0] * (fConst139 + fConst138 * fRec1[0]) + fConst136 * fRec1[0]);
		double fTemp10 = fRec3[0] * (fConst159 * fRec2[0] * (fConst158 + fConst157 * fRec1[0]) + fConst0 * (fConst155 + fConst154 * fRec1[0])) + fConst0 * (fConst152 + fRec2[0] * (fConst151 + fConst150 * fRec1[0]) + fConst148 * fRec1[0]);
		double fTemp11 = fRec3[0] * (0.0 - 3.18176968007089e-12 * fRec1[0] + fRec2[0] * (fConst165 + fConst164 * fRec1[0]) + 3.18176968007089e-12) - 7.33688420661919e-12 * fRec1[0] + fRec2[0] * (fConst162 + fConst161 * fRec1[0]) + 7.33688420661919e-12;
		double fTemp12 = fRec3[0] * (fConst159 * fRec2[0] * (fConst169 + fConst168 * fRec1[0]) + fConst0 * (fConst154 + fConst155 * fRec1[0])) + fConst0 * (fConst148 + fRec2[0] * (fConst167 + fConst166 * fRec1[0]) + fConst152 * fRec1[0]);
		double fTemp13 = fRec3[0] * (fConst43 * fRec2[0] * (fConst177 + fConst176 * fRec1[0]) + fConst0 * (fConst175 + fConst174 * fRec1[0])) + fConst0 * (fConst173 + fRec2[0] * (fConst172 + fConst171 * fRec1[0]) + fConst170 * fRec1[0]);
		double fTemp14 = (fRec4[0] * fTemp13 + fTemp12 * fRec4[1] + fConst43 * fTemp11 * fRec4[2] + fTemp10 * fRec4[3] + fTemp9 * fRec4[4]) / fTemp0;
		fRec0[0] = ((signbit(fTemp14)) ? tiltdrivepro_in_negclip(fTemp14) : tiltdrivepro_inclip(fTemp14)) - fConst3 * fRec0[1];
		fRec13[0] = fSlow3 + 0.993 * fRec13[1];
		double fTemp15 = 0.0 - 0.000487217249496405 * fRec13[0];
		double fTemp16 = fConst178 * (fRec0[0] * fTemp15 + 0.000487217249496405 * fRec13[0] * fRec0[1]);
		fRec17[0] = fConst108 * (fConst180 * fTemp8 + fConst181 * fVec3[1]) - fConst179 * fRec17[1];
		fRec16[0] = fRec17[0] - fConst101 * (fConst100 * fRec16[2] + fConst98 * fRec16[1]);
		fRec15[0] = fConst101 * (fConst97 * fRec16[0] + fConst182 * fRec16[1] + fConst97 * fRec16[2]) - (fTemp4 * fRec15[1] + fTemp3 * fRec15[2] + fTemp2 * fRec15[3] + fTemp1 * fRec15[4]) / fTemp0;
		double fTemp17 = (fRec15[0] * fTemp13 + fTemp12 * fRec15[1] + fConst43 * fTemp11 * fRec15[2] + fTemp10 * fRec15[3] + fTemp9 * fRec15[4]) / fTemp0;
		fRec14[0] = ((signbit(fTemp17)) ? tiltdrivepro_in_negclip(fTemp17) : tiltdrivepro_inclip(fTemp17)) - fConst3 * fRec14[1];
		double fTemp18 = fConst178 * (fRec14[0] * fTemp15 + 0.000487217249496405 * fRec13[0] * fRec14[1]);
		double fTemp19 = fConst98 * fRec20[1];
		fRec22[0] = fConst115 * (fConst186 * fTemp7 + fConst187 * fVec2[1]) - fConst185 * fRec22[1];
		fRec21[0] = fRec22[0] - fConst108 * (fConst107 * fRec21[2] + fConst105 * fRec21[1]);
		fRec20[0] = fConst108 * (fConst104 * fRec21[0] + fConst188 * fRec21[1] + fConst104 * fRec21[2]) - fConst184 * (fConst183 * fRec20[2] + fTemp19);
		fRec19[0] = fRec20[2] + fConst184 * (fTemp19 + fConst183 * fRec20[0]) - (fTemp4 * fRec19[1] + fTemp3 * fRec19[2] + fTemp2 * fRec19[3] + fTemp1 * fRec19[4]) / fTemp0;
		double fTemp20 = (fRec19[0] * fTemp13 + fTemp12 * fRec19[1] + fConst43 * fTemp11 * fRec19[2] + fTemp10 * fRec19[3] + fTemp9 * fRec19[4]) / fTemp0;
		fRec18[0] = ((signbit(fTemp20)) ? tiltdrivepro_in_negclip(fTemp20) : tiltdrivepro_inclip(fTemp20)) - fConst3 * fRec18[1];
		double fTemp21 = fConst178 * (fRec18[0] * fTemp15 + 0.000487217249496405 * fRec13[0] * fRec18[1]);
		double fTemp22 = fConst98 * fRec25[1];
		double fTemp23 = fConst105 * fRec26[1];
		fRec28[0] = fConst122 * (fConst192 * fTemp6 + fConst193 * fVec1[1]) - fConst191 * fRec28[1];
		fRec27[0] = fRec28[0] - fConst115 * (fConst114 * fRec27[2] + fConst112 * fRec27[1]);
		fRec26[0] = fConst115 * (fConst111 * fRec27[0] + fConst194 * fRec27[1] + fConst111 * fRec27[2]) - fConst190 * (fConst189 * fRec26[2] + fTemp23);
		fRec25[0] = fRec26[2] + fConst190 * (fTemp23 + fConst189 * fRec26[0]) - fConst184 * (fConst183 * fRec25[2] + fTemp22);
		fRec24[0] = fRec25[2] + fConst184 * (fTemp22 + fConst183 * fRec25[0]) - (fTemp4 * fRec24[1] + fTemp3 * fRec24[2] + fTemp2 * fRec24[3] + fTemp1 * fRec24[4]) / fTemp0;
		double fTemp24 = (fRec24[0] * fTemp13 + fTemp12 * fRec24[1] + fConst43 * fTemp11 * fRec24[2] + fTemp10 * fRec24[3] + fTemp9 * fRec24[4]) / fTemp0;
		fRec23[0] = ((signbit(fTemp24)) ? tiltdrivepro_in_negclip(fTemp24) : tiltdrivepro_inclip(fTemp24)) - fConst3 * fRec23[1];
		double fTemp25 = fConst178 * (fRec23[0] * fTemp15 + 0.000487217249496405 * fRec13[0] * fRec23[1]);
		double fTemp26 = fConst98 * fRec31[1];
		double fTemp27 = fConst105 * fRec32[1];
		double fTemp28 = fConst112 * fRec33[1];
		fRec35[0] = fConst197 * fVec0[1] - fConst125 * (fConst123 * fRec35[1] - fConst120 * fTemp5);
		fRec34[0] = fRec35[0] - fConst122 * (fConst121 * fRec34[2] + fConst119 * fRec34[1]);
		fRec33[0] = fConst122 * (fConst118 * fRec34[0] + fConst198 * fRec34[1] + fConst118 * fRec34[2]) - fConst196 * (fConst195 * fRec33[2] + fTemp28);
		fRec32[0] = fRec33[2] + fConst196 * (fTemp28 + fConst195 * fRec33[0]) - fConst190 * (fConst189 * fRec32[2] + fTemp27);
		fRec31[0] = fRec32[2] + fConst190 * (fTemp27 + fConst189 * fRec32[0]) - fConst184 * (fConst183 * fRec31[2] + fTemp26);
		fRec30[0] = fRec31[2] + fConst184 * (fTemp26 + fConst183 * fRec31[0]) - (fRec30[1] * fTemp4 + fRec30[2] * fTemp3 + fRec30[3] * fTemp2 + fRec30[4] * fTemp1) / fTemp0;
		double fTemp29 = (fRec30[0] * fTemp13 + fRec30[1] * fTemp12 + fConst43 * fRec30[2] * fTemp11 + fRec30[3] * fTemp10 + fRec30[4] * fTemp9) / fTemp0;
		fRec29[0] = ((signbit(fTemp29)) ? tiltdrivepro_in_negclip(fTemp29) : tiltdrivepro_inclip(fTemp29)) - fConst3 * fRec29[1];
		double fTemp30 = fConst178 * (fRec29[0] * fTemp15 + 0.000487217249496405 * fRec13[0] * fRec29[1]);
		output0[i0] = FAUSTFLOAT(((signbit(fTemp30)) ? tiltdrivepro_out_3_negclip(fTemp30) : tiltdrivepro_out_3clip(fTemp30)) + ((signbit(fTemp25)) ? tiltdrivepro_out_3_negclip(fTemp25) : tiltdrivepro_out_3clip(fTemp25)) + ((signbit(fTemp21)) ? tiltdrivepro_out_3_negclip(fTemp21) : tiltdrivepro_out_3clip(fTemp21)) + ((signbit(fTemp18)) ? tiltdrivepro_out_3_negclip(fTemp18) : tiltdrivepro_out_3clip(fTemp18)) + ((signbit(fTemp16)) ? tiltdrivepro_out_3_negclip(fTemp16) : tiltdrivepro_out_3clip(fTemp16)));
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fVec0[1] = fVec0[0];
		fRec12[1] = fRec12[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fVec1[1] = fVec1[0];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fVec2[1] = fVec2[0];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fVec3[1] = fVec3[0];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		for (int j0 = 4; j0 > 0; j0 = j0 - 1) {
			fRec4[j0] = fRec4[j0 - 1];
		}
		fRec0[1] = fRec0[0];
		fRec13[1] = fRec13[0];
		fRec17[1] = fRec17[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		for (int j1 = 4; j1 > 0; j1 = j1 - 1) {
			fRec15[j1] = fRec15[j1 - 1];
		}
		fRec14[1] = fRec14[0];
		fRec22[1] = fRec22[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		for (int j2 = 4; j2 > 0; j2 = j2 - 1) {
			fRec19[j2] = fRec19[j2 - 1];
		}
		fRec18[1] = fRec18[0];
		fRec28[1] = fRec28[0];
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		for (int j3 = 4; j3 > 0; j3 = j3 - 1) {
			fRec24[j3] = fRec24[j3 - 1];
		}
		fRec23[1] = fRec23[0];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		for (int j4 = 4; j4 > 0; j4 = j4 - 1) {
			fRec30[j4] = fRec30[j4 - 1];
		}
		fRec29[1] = fRec29[0];
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
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case DRIVE: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case LEVEL: 
		fVslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TONE: 
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
   BODY, 
   DRIVE, 
   LEVEL, 
   TONE, 
} PortIndex;
*/

} // end namespace gxtilttone
