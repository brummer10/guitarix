// generated from file '../src/LV2/faust/gx_chump.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "math.h"
#include "redeyechumppow_neg_table.h"
#include "redeyechumppow_table.h"
#include "redeyechumppowf_neg_table.h"
#include "redeyechumppowf_table.h"
#include "redeyechumppre_neg_table.h"
#include "redeyechumppre_table.h"

namespace gx_chump {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec1[2];
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
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fVec0[2];
	double fConst59;
	double fConst60;
	double fRec10[2];
	double fRec9[3];
	double fVec1[2];
	double fConst61;
	double fConst62;
	double fConst63;
	double fRec8[2];
	double fRec7[3];
	double fVec2[2];
	double fConst64;
	double fConst65;
	double fConst66;
	double fRec6[2];
	double fRec5[3];
	double fVec3[2];
	double fConst67;
	double fConst68;
	double fConst69;
	double fRec4[2];
	double fRec3[3];
	double fRec2[5];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec11[2];
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
	double fRec0[4];
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
	double fRec12[4];
	double fConst95;
	double fConst96;
	double fConst97;
	double fConst98;
	double fConst99;
	double fConst100;
	double fConst101;
	double fConst102;
	double fRec16[2];
	double fRec15[3];
	double fConst103;
	double fRec14[5];
	double fRec13[4];
	double fRec17[4];
	double fConst104;
	double fConst105;
	double fConst106;
	double fRec22[2];
	double fRec21[3];
	double fConst107;
	double fRec20[3];
	double fRec19[5];
	double fRec18[4];
	double fRec23[4];
	double fConst108;
	double fConst109;
	double fConst110;
	double fRec29[2];
	double fRec28[3];
	double fConst111;
	double fRec27[3];
	double fRec26[3];
	double fRec25[5];
	double fRec24[4];
	double fRec30[4];
	double fConst112;
	double fConst113;
	double fRec37[2];
	double fRec36[3];
	double fConst114;
	double fRec35[3];
	double fRec34[3];
	double fRec33[3];
	double fRec32[5];
	double fRec31[4];
	double fRec38[4];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec39[2];

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
	id = "Redeye Chump";
	name = N_("Redeye Chump");
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
	for (int l13 = 0; l13 < 5; l13 = l13 + 1) fRec2[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec11[l14] = 0.0;
	for (int l15 = 0; l15 < 4; l15 = l15 + 1) fRec0[l15] = 0.0;
	for (int l16 = 0; l16 < 4; l16 = l16 + 1) fRec12[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec16[l17] = 0.0;
	for (int l18 = 0; l18 < 3; l18 = l18 + 1) fRec15[l18] = 0.0;
	for (int l19 = 0; l19 < 5; l19 = l19 + 1) fRec14[l19] = 0.0;
	for (int l20 = 0; l20 < 4; l20 = l20 + 1) fRec13[l20] = 0.0;
	for (int l21 = 0; l21 < 4; l21 = l21 + 1) fRec17[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec22[l22] = 0.0;
	for (int l23 = 0; l23 < 3; l23 = l23 + 1) fRec21[l23] = 0.0;
	for (int l24 = 0; l24 < 3; l24 = l24 + 1) fRec20[l24] = 0.0;
	for (int l25 = 0; l25 < 5; l25 = l25 + 1) fRec19[l25] = 0.0;
	for (int l26 = 0; l26 < 4; l26 = l26 + 1) fRec18[l26] = 0.0;
	for (int l27 = 0; l27 < 4; l27 = l27 + 1) fRec23[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec29[l28] = 0.0;
	for (int l29 = 0; l29 < 3; l29 = l29 + 1) fRec28[l29] = 0.0;
	for (int l30 = 0; l30 < 3; l30 = l30 + 1) fRec27[l30] = 0.0;
	for (int l31 = 0; l31 < 3; l31 = l31 + 1) fRec26[l31] = 0.0;
	for (int l32 = 0; l32 < 5; l32 = l32 + 1) fRec25[l32] = 0.0;
	for (int l33 = 0; l33 < 4; l33 = l33 + 1) fRec24[l33] = 0.0;
	for (int l34 = 0; l34 < 4; l34 = l34 + 1) fRec30[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec37[l35] = 0.0;
	for (int l36 = 0; l36 < 3; l36 = l36 + 1) fRec36[l36] = 0.0;
	for (int l37 = 0; l37 < 3; l37 = l37 + 1) fRec35[l37] = 0.0;
	for (int l38 = 0; l38 < 3; l38 = l38 + 1) fRec34[l38] = 0.0;
	for (int l39 = 0; l39 < 3; l39 = l39 + 1) fRec33[l39] = 0.0;
	for (int l40 = 0; l40 < 5; l40 = l40 + 1) fRec32[l40] = 0.0;
	for (int l41 = 0; l41 < 4; l41 = l41 + 1) fRec31[l41] = 0.0;
	for (int l42 = 0; l42 < 4; l42 = l42 + 1) fRec38[l42] = 0.0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fRec39[l43] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 9.01314076551628e-15 * fConst0;
	fConst2 = fConst0 * (fConst0 * (1.3955910672935e-12 - fConst1) + -6.86346038146649e-11) + 1.79996158094636e-10;
	fConst3 = 2.70394222965488e-14 * fConst0;
	fConst4 = fConst0 * (fConst0 * (fConst3 + -1.3955910672935e-12) + -6.86346038146649e-11) + 5.39988474283909e-10;
	fConst5 = fConst0 * (fConst0 * (-1.3955910672935e-12 - fConst3) + 6.86346038146649e-11) + 5.39988474283909e-10;
	fConst6 = fConst0 * (fConst0 * (fConst1 + 1.3955910672935e-12) + 6.86346038146649e-11) + 1.79996158094636e-10;
	fConst7 = 1.0 / fConst6;
	fConst8 = 4.83357544584368e-19 * fConst0;
	fConst9 = mydsp_faustpower2_f(fConst0);
	fConst10 = fConst9 * (fConst0 * (-4.95743008549253e-16 - fConst8) + -1.23854639648849e-14);
	fConst11 = 4.99938975959391e-19 * fConst0;
	fConst12 = fConst0 * (fConst0 * (fConst0 * (fConst11 + 5.25223533960928e-16) + 2.55941946006592e-14) + 3.09636599122122e-13);
	fConst13 = 4.99938975959391e-20 * fConst0;
	fConst14 = fConst0 * (fConst0 * (fConst0 * (fConst13 + 3.02491841375788e-16) + 1.40186442450682e-13) + 6.50692145985754e-12);
	fConst15 = fConst9 * (fConst0 * (4.95743008549253e-16 - fConst8) + -1.23854639648849e-14);
	fConst16 = fConst0 * (fConst0 * (fConst0 * (fConst11 + -5.25223533960928e-16) + 2.55941946006592e-14) + -3.09636599122122e-13);
	fConst17 = fConst0 * (fConst0 * (fConst0 * (fConst13 + -3.02491841375788e-16) + 1.40186442450682e-13) + -6.50692145985754e-12);
	fConst18 = 1.93343017833747e-18 * fConst0;
	fConst19 = mydsp_faustpower3_f(fConst0);
	fConst20 = fConst19 * (fConst18 + -9.91486017098506e-16);
	fConst21 = 1.99975590383756e-18 * fConst0;
	fConst22 = fConst0 * (fConst9 * (1.05044706792186e-15 - fConst21) + -6.19273198244244e-13);
	fConst23 = 1.99975590383756e-19 * fConst0;
	fConst24 = fConst0 * (fConst9 * (6.04983682751577e-16 - fConst23) + -1.30138429197151e-11);
	fConst25 = 2.47709279297698e-14 - 2.90014526750621e-18 * fConst9;
	fConst26 = 2.99963385575635e-18 * fConst9 + -5.11883892013183e-14;
	fConst27 = 2.99963385575635e-19 * fConst9 + -2.80372884901364e-13;
	fConst28 = fConst19 * (fConst18 + 9.91486017098506e-16);
	fConst29 = fConst0 * (fConst9 * (-1.05044706792186e-15 - fConst21) + 6.19273198244244e-13);
	fConst30 = fConst0 * (fConst9 * (-6.04983682751577e-16 - fConst23) + 1.30138429197151e-11);
	fConst31 = std::tan(270.1769682087222 / fConst0);
	fConst32 = mydsp_faustpower2_f(fConst31);
	fConst33 = 2.0 * (1.0 - 1.0 / fConst32);
	fConst34 = 1.0 / fConst31;
	fConst35 = (fConst34 + -1.0000000000000004) / fConst31 + 1.0;
	fConst36 = (fConst34 + 1.0000000000000004) / fConst31 + 1.0;
	fConst37 = 1.0 / fConst36;
	fConst38 = std::tan(659.7344572538566 / fConst0);
	fConst39 = mydsp_faustpower2_f(fConst38);
	fConst40 = 2.0 * (1.0 - 1.0 / fConst39);
	fConst41 = 1.0 / fConst38;
	fConst42 = (fConst41 + -1.0000000000000004) / fConst38 + 1.0;
	fConst43 = (fConst41 + 1.0000000000000004) / fConst38 + 1.0;
	fConst44 = 1.0 / fConst43;
	fConst45 = std::tan(3769.9111843077517 / fConst0);
	fConst46 = mydsp_faustpower2_f(fConst45);
	fConst47 = 2.0 * (1.0 - 1.0 / fConst46);
	fConst48 = 1.0 / fConst45;
	fConst49 = (fConst48 + -1.0000000000000004) / fConst45 + 1.0;
	fConst50 = (fConst48 + 1.0000000000000004) / fConst45 + 1.0;
	fConst51 = 1.0 / fConst50;
	fConst52 = std::tan(20517.741620594938 / fConst0);
	fConst53 = mydsp_faustpower2_f(fConst52);
	fConst54 = 2.0 * (1.0 - 1.0 / fConst53);
	fConst55 = 1.0 / fConst52;
	fConst56 = (fConst55 + -1.0000000000000004) / fConst52 + 1.0;
	fConst57 = (fConst55 + 1.0000000000000004) / fConst52 + 1.0;
	fConst58 = 1.0 / fConst57;
	fConst59 = 1.0 - fConst55;
	fConst60 = 1.0 / (fConst55 + 1.0);
	fConst61 = 1.0 - fConst48;
	fConst62 = fConst48 + 1.0;
	fConst63 = 1.0 / fConst62;
	fConst64 = 1.0 - fConst41;
	fConst65 = fConst41 + 1.0;
	fConst66 = 1.0 / fConst65;
	fConst67 = 1.0 - fConst34;
	fConst68 = fConst34 + 1.0;
	fConst69 = 1.0 / fConst68;
	fConst70 = 1.42098357291903e-14 * fConst0;
	fConst71 = fConst9 * (fConst70 + -1.89464476389205e-13);
	fConst72 = 2.84196714583805e-18 * fConst0;
	fConst73 = fConst0 * (fConst0 * (fConst0 * (2.87986004111589e-15 - fConst72) + -7.14281075987297e-12) + 9.47322381946023e-11);
	fConst74 = 2.84196714583805e-14 * fConst19;
	fConst75 = 1.13678685833522e-17 * fConst0;
	fConst76 = fConst0 * (fConst9 * (fConst75 + -5.75972008223179e-15) + 1.89464476389205e-10);
	fConst77 = 1.42856215197459e-11 - 1.70518028750283e-17 * fConst9;
	fConst78 = fConst0 * (fConst9 * (fConst75 + 5.75972008223179e-15) + -1.89464476389205e-10);
	fConst79 = fConst9 * (-1.89464476389205e-13 - fConst70);
	fConst80 = fConst0 * (fConst0 * (fConst0 * (-2.87986004111589e-15 - fConst72) + -7.14281075987297e-12) + -9.47322381946023e-11);
	fConst81 = 5.2572119847844e-14 * fConst0;
	fConst82 = fConst0 * (2.22632342602781e-12 - fConst81) + -5.41994006909799e-15;
	fConst83 = 1.57716359543532e-13 * fConst0;
	fConst84 = fConst0 * (fConst83 + -2.22632342602781e-12) + -5.41994006909799e-15;
	fConst85 = fConst0 * (-2.22632342602781e-12 - fConst83) + 5.41994006909799e-15;
	fConst86 = fConst0 * (fConst81 + 2.22632342602781e-12) + 5.41994006909799e-15;
	fConst87 = fConst0 / fConst6;
	fConst88 = 9.00050108040552e-15 * fConst0;
	fConst89 = fConst0 * (fConst0 * (2.00144504609273e-12 - fConst88) + -1.09475884941298e-10) + 2.87117546539927e-10;
	fConst90 = 2.70015032412166e-14 * fConst0;
	fConst91 = fConst0 * (fConst0 * (fConst90 + -2.00144504609273e-12) + -1.09475884941298e-10) + 8.6135263961978e-10;
	fConst92 = fConst0 * (fConst0 * (-2.00144504609273e-12 - fConst90) + 1.09475884941298e-10) + 8.6135263961978e-10;
	fConst93 = (fConst0 * (fConst88 + 2.00144504609273e-12) + 1.09475884941298e-10) * fConst0 + 2.87117546539927e-10;
	fConst94 = 1.0 / fConst93;
	fConst95 = 8.08665507806617e-14 * fConst0;
	fConst96 = 3.42440032262935e-12 - fConst95;
	fConst97 = 2.42599652341985e-13 * fConst0;
	fConst98 = fConst97 + -3.42440032262935e-12;
	fConst99 = -3.42440032262935e-12 - fConst97;
	fConst100 = fConst95 + 3.42440032262935e-12;
	fConst101 = fConst9 / fConst93;
	fConst102 = 1.0 / (fConst31 * fConst43);
	fConst103 = 1.0 / (fConst32 * fConst36);
	fConst104 = 1.0 - fConst67 / fConst31;
	fConst105 = 1.0 / (fConst68 / fConst31 + 1.0);
	fConst106 = 1.0 / (fConst38 * fConst50);
	fConst107 = 1.0 / (fConst39 * fConst43);
	fConst108 = 1.0 - fConst64 / fConst38;
	fConst109 = 1.0 / (fConst65 / fConst38 + 1.0);
	fConst110 = 1.0 / (fConst45 * fConst57);
	fConst111 = 1.0 / (fConst46 * fConst50);
	fConst112 = 1.0 - fConst61 / fConst45;
	fConst113 = 1.0 / (fConst62 / fConst45 + 1.0);
	fConst114 = 1.0 / (fConst53 * fConst57);
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
	int iSlow0 = int(double(fCheckbox0));
	double fSlow1 = 0.00036676987543879196 * (std::exp(3.0 * double(fVslider0)) + -1.0);
	double fSlow2 = 0.007000000000000006 * double(fVslider1);
	double fSlow3 = 0.0010000000000000009 * double(fVslider2);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec1[0] = fSlow1 + 0.993 * fRec1[1];
		double fTemp0 = fConst14 + fRec1[0] * (fConst12 + fConst10 * fRec1[0]) + 7.74091497805305e-11;
		double fTemp1 = fConst17 + fRec1[0] * (fConst16 + fConst15 * fRec1[0]) + 7.74091497805305e-11;
		double fTemp2 = fConst24 + fRec1[0] * (fConst22 + fConst20 * fRec1[0]) + 3.09636599122122e-10;
		double fTemp3 = fConst9 * (fConst27 + fRec1[0] * (fConst26 + fConst25 * fRec1[0])) + 4.64454898683183e-10;
		double fTemp4 = fConst30 + fRec1[0] * (fConst29 + fConst28 * fRec1[0]) + 3.09636599122122e-10;
		double fTemp5 = double(input0[i0]);
		fVec0[0] = fTemp5;
		fRec10[0] = -(fConst60 * (fConst59 * fRec10[1] - (fTemp5 + fVec0[1])));
		fRec9[0] = fRec10[0] - fConst58 * (fConst56 * fRec9[2] + fConst54 * fRec9[1]);
		double fTemp6 = fRec9[2] + fRec9[0] + 2.0 * fRec9[1];
		fVec1[0] = fTemp6;
		fRec8[0] = -(fConst63 * (fConst61 * fRec8[1] - fConst58 * (fTemp6 + fVec1[1])));
		fRec7[0] = fRec8[0] - fConst51 * (fConst49 * fRec7[2] + fConst47 * fRec7[1]);
		double fTemp7 = fRec7[2] + fRec7[0] + 2.0 * fRec7[1];
		fVec2[0] = fTemp7;
		fRec6[0] = -(fConst66 * (fConst64 * fRec6[1] - fConst51 * (fTemp7 + fVec2[1])));
		fRec5[0] = fRec6[0] - fConst44 * (fConst42 * fRec5[2] + fConst40 * fRec5[1]);
		double fTemp8 = fRec5[2] + fRec5[0] + 2.0 * fRec5[1];
		fVec3[0] = fTemp8;
		fRec4[0] = -(fConst69 * (fConst67 * fRec4[1] - fConst44 * (fTemp8 + fVec3[1])));
		fRec3[0] = fRec4[0] - fConst37 * (fConst35 * fRec3[2] + fConst33 * fRec3[1]);
		fRec2[0] = fConst37 * (fRec3[2] + fRec3[0] + 2.0 * fRec3[1]) - (fTemp4 * fRec2[1] + fTemp3 * fRec2[2] + fTemp2 * fRec2[3] + fTemp1 * fRec2[4]) / fTemp0;
		fRec11[0] = fSlow2 + 0.993 * fRec11[1];
		double fTemp9 = fConst73 + fConst71 * fRec11[0];
		double fTemp10 = fConst74 * fRec11[0];
		double fTemp11 = fConst76 - fTemp10;
		double fTemp12 = fConst77 + 3.78928952778409e-13 * fRec11[0];
		double fTemp13 = fConst78 + fTemp10;
		double fTemp14 = fConst80 + fConst79 * fRec11[0];
		double fTemp15 = fRec1[0] * (fRec2[0] * fTemp14 + fTemp13 * fRec2[1] + fConst9 * fTemp12 * fRec2[2] + fTemp11 * fRec2[3] + fTemp9 * fRec2[4]) / fTemp0;
		double fTemp16 = ((signbit(fTemp15)) ? redeyechumppre_negclip(fTemp15) : redeyechumppreclip(fTemp15));
		fRec0[0] = fTemp16 - fConst7 * (fConst5 * fRec0[1] + fConst4 * fRec0[2] + fConst2 * fRec0[3]);
		double fTemp17 = fConst87 * (fConst86 * fRec0[0] + fConst85 * fRec0[1] + fConst84 * fRec0[2] + fConst82 * fRec0[3]);
		fRec12[0] = fTemp16 - fConst94 * (fConst92 * fRec12[1] + fConst91 * fRec12[2] + fConst89 * fRec12[3]);
		double fTemp18 = fConst101 * (fConst100 * fRec12[0] + fConst99 * fRec12[1] + fConst98 * fRec12[2] + fConst96 * fRec12[3]);
		fRec16[0] = -(fConst69 * (fConst67 * fRec16[1] - fConst102 * (fTemp8 - fVec3[1])));
		fRec15[0] = fRec16[0] - fConst37 * (fConst35 * fRec15[2] + fConst33 * fRec15[1]);
		fRec14[0] = fConst103 * (fRec15[2] + (fRec15[0] - 2.0 * fRec15[1])) - (fTemp2 * fRec14[3] + fTemp4 * fRec14[1] + fTemp3 * fRec14[2] + fTemp1 * fRec14[4]) / fTemp0;
		double fTemp19 = fRec1[0] * (fRec14[0] * fTemp14 + fTemp13 * fRec14[1] + fConst9 * fTemp12 * fRec14[2] + fTemp11 * fRec14[3] + fTemp9 * fRec14[4]) / fTemp0;
		double fTemp20 = ((signbit(fTemp19)) ? redeyechumppre_negclip(fTemp19) : redeyechumppreclip(fTemp19));
		fRec13[0] = fTemp20 - fConst7 * (fConst5 * fRec13[1] + fConst4 * fRec13[2] + fConst2 * fRec13[3]);
		double fTemp21 = fConst87 * (fConst86 * fRec13[0] + fConst85 * fRec13[1] + fConst84 * fRec13[2] + fConst82 * fRec13[3]);
		fRec17[0] = fTemp20 - fConst94 * (fConst92 * fRec17[1] + fConst91 * fRec17[2] + fConst89 * fRec17[3]);
		double fTemp22 = fConst101 * (fConst100 * fRec17[0] + fConst99 * fRec17[1] + fConst98 * fRec17[2] + fConst96 * fRec17[3]);
		double fTemp23 = fConst33 * fRec20[1];
		fRec22[0] = -(fConst66 * (fConst64 * fRec22[1] - fConst106 * (fTemp7 - fVec2[1])));
		fRec21[0] = fRec22[0] - fConst44 * (fConst42 * fRec21[2] + fConst40 * fRec21[1]);
		fRec20[0] = fConst107 * (fRec21[2] + (fRec21[0] - 2.0 * fRec21[1])) - fConst105 * (fConst104 * fRec20[2] + fTemp23);
		fRec19[0] = fRec20[2] + fConst105 * (fTemp23 + fConst104 * fRec20[0]) - (fTemp4 * fRec19[1] + fTemp3 * fRec19[2] + fTemp2 * fRec19[3] + fTemp1 * fRec19[4]) / fTemp0;
		double fTemp24 = fRec1[0] * (fRec19[0] * fTemp14 + fTemp13 * fRec19[1] + fConst9 * fTemp12 * fRec19[2] + fTemp11 * fRec19[3] + fTemp9 * fRec19[4]) / fTemp0;
		double fTemp25 = ((signbit(fTemp24)) ? redeyechumppre_negclip(fTemp24) : redeyechumppreclip(fTemp24));
		fRec18[0] = fTemp25 - fConst7 * (fConst5 * fRec18[1] + fConst4 * fRec18[2] + fConst2 * fRec18[3]);
		double fTemp26 = fConst87 * (fConst86 * fRec18[0] + fConst85 * fRec18[1] + fConst84 * fRec18[2] + fConst82 * fRec18[3]);
		fRec23[0] = fTemp25 - fConst94 * (fConst92 * fRec23[1] + fConst91 * fRec23[2] + fConst89 * fRec23[3]);
		double fTemp27 = fConst101 * (fConst100 * fRec23[0] + fConst99 * fRec23[1] + fConst98 * fRec23[2] + fConst96 * fRec23[3]);
		double fTemp28 = fConst33 * fRec26[1];
		double fTemp29 = fConst40 * fRec27[1];
		fRec29[0] = -(fConst63 * (fConst61 * fRec29[1] - fConst110 * (fTemp6 - fVec1[1])));
		fRec28[0] = fRec29[0] - fConst51 * (fConst49 * fRec28[2] + fConst47 * fRec28[1]);
		fRec27[0] = fConst111 * (fRec28[2] + (fRec28[0] - 2.0 * fRec28[1])) - fConst109 * (fConst108 * fRec27[2] + fTemp29);
		fRec26[0] = fRec27[2] + fConst109 * (fTemp29 + fConst108 * fRec27[0]) - fConst105 * (fConst104 * fRec26[2] + fTemp28);
		fRec25[0] = fRec26[2] + fConst105 * (fTemp28 + fConst104 * fRec26[0]) - (fTemp2 * fRec25[3] + fTemp4 * fRec25[1] + fTemp3 * fRec25[2] + fTemp1 * fRec25[4]) / fTemp0;
		double fTemp30 = fRec1[0] * (fRec25[0] * fTemp14 + fTemp13 * fRec25[1] + fConst9 * fTemp12 * fRec25[2] + fTemp11 * fRec25[3] + fTemp9 * fRec25[4]) / fTemp0;
		double fTemp31 = ((signbit(fTemp30)) ? redeyechumppre_negclip(fTemp30) : redeyechumppreclip(fTemp30));
		fRec24[0] = fTemp31 - fConst7 * (fConst5 * fRec24[1] + fConst4 * fRec24[2] + fConst2 * fRec24[3]);
		double fTemp32 = fConst87 * (fConst86 * fRec24[0] + fConst85 * fRec24[1] + fConst84 * fRec24[2] + fConst82 * fRec24[3]);
		fRec30[0] = fTemp31 - fConst94 * (fConst92 * fRec30[1] + fConst91 * fRec30[2] + fConst89 * fRec30[3]);
		double fTemp33 = fConst101 * (fConst100 * fRec30[0] + fConst99 * fRec30[1] + fConst98 * fRec30[2] + fConst96 * fRec30[3]);
		double fTemp34 = fConst33 * fRec33[1];
		double fTemp35 = fConst40 * fRec34[1];
		double fTemp36 = fConst47 * fRec35[1];
		fRec37[0] = -(fConst60 * (fConst59 * fRec37[1] - fConst55 * (fTemp5 - fVec0[1])));
		fRec36[0] = fRec37[0] - fConst58 * (fConst56 * fRec36[2] + fConst54 * fRec36[1]);
		fRec35[0] = fConst114 * (fRec36[2] + (fRec36[0] - 2.0 * fRec36[1])) - fConst113 * (fConst112 * fRec35[2] + fTemp36);
		fRec34[0] = fRec35[2] + fConst113 * (fTemp36 + fConst112 * fRec35[0]) - fConst109 * (fConst108 * fRec34[2] + fTemp35);
		fRec33[0] = fRec34[2] + fConst109 * (fTemp35 + fConst108 * fRec34[0]) - fConst105 * (fConst104 * fRec33[2] + fTemp34);
		fRec32[0] = fRec33[2] + fConst105 * (fTemp34 + fConst104 * fRec33[0]) - (fRec32[1] * fTemp4 + fRec32[2] * fTemp3 + fRec32[3] * fTemp2 + fRec32[4] * fTemp1) / fTemp0;
		double fTemp37 = fRec1[0] * (fRec32[0] * fTemp14 + fRec32[1] * fTemp13 + fConst9 * fRec32[2] * fTemp12 + fRec32[3] * fTemp11 + fRec32[4] * fTemp9) / fTemp0;
		double fTemp38 = ((signbit(fTemp37)) ? redeyechumppre_negclip(fTemp37) : redeyechumppreclip(fTemp37));
		fRec31[0] = fTemp38 - fConst7 * (fConst5 * fRec31[1] + fConst4 * fRec31[2] + fConst2 * fRec31[3]);
		double fTemp39 = fConst87 * (fConst86 * fRec31[0] + fConst85 * fRec31[1] + fConst84 * fRec31[2] + fConst82 * fRec31[3]);
		fRec38[0] = fTemp38 - fConst94 * (fConst92 * fRec38[1] + fConst91 * fRec38[2] + fConst89 * fRec38[3]);
		double fTemp40 = fConst101 * (fConst100 * fRec38[0] + fConst99 * fRec38[1] + fConst98 * fRec38[2] + fConst96 * fRec38[3]);
		fRec39[0] = fSlow3 + 0.999 * fRec39[1];
		output0[i0] = FAUSTFLOAT(fRec39[0] * (((iSlow0) ? ((signbit(fTemp40)) ? redeyechumppow_negclip(fTemp40) : redeyechumppowclip(fTemp40)) : ((signbit(fTemp39)) ? redeyechumppowf_negclip(fTemp39) : redeyechumppowfclip(fTemp39))) + ((iSlow0) ? ((signbit(fTemp33)) ? redeyechumppow_negclip(fTemp33) : redeyechumppowclip(fTemp33)) : ((signbit(fTemp32)) ? redeyechumppowf_negclip(fTemp32) : redeyechumppowfclip(fTemp32))) + ((iSlow0) ? ((signbit(fTemp27)) ? redeyechumppow_negclip(fTemp27) : redeyechumppowclip(fTemp27)) : ((signbit(fTemp26)) ? redeyechumppowf_negclip(fTemp26) : redeyechumppowfclip(fTemp26))) + ((iSlow0) ? ((signbit(fTemp22)) ? redeyechumppow_negclip(fTemp22) : redeyechumppowclip(fTemp22)) : ((signbit(fTemp21)) ? redeyechumppowf_negclip(fTemp21) : redeyechumppowfclip(fTemp21))) + ((iSlow0) ? ((signbit(fTemp18)) ? redeyechumppow_negclip(fTemp18) : redeyechumppowclip(fTemp18)) : ((signbit(fTemp17)) ? redeyechumppowf_negclip(fTemp17) : redeyechumppowfclip(fTemp17)))));
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
		for (int j0 = 4; j0 > 0; j0 = j0 - 1) {
			fRec2[j0] = fRec2[j0 - 1];
		}
		fRec11[1] = fRec11[0];
		for (int j1 = 3; j1 > 0; j1 = j1 - 1) {
			fRec0[j1] = fRec0[j1 - 1];
		}
		for (int j2 = 3; j2 > 0; j2 = j2 - 1) {
			fRec12[j2] = fRec12[j2 - 1];
		}
		fRec16[1] = fRec16[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		for (int j3 = 4; j3 > 0; j3 = j3 - 1) {
			fRec14[j3] = fRec14[j3 - 1];
		}
		for (int j4 = 3; j4 > 0; j4 = j4 - 1) {
			fRec13[j4] = fRec13[j4 - 1];
		}
		for (int j5 = 3; j5 > 0; j5 = j5 - 1) {
			fRec17[j5] = fRec17[j5 - 1];
		}
		fRec22[1] = fRec22[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		for (int j6 = 4; j6 > 0; j6 = j6 - 1) {
			fRec19[j6] = fRec19[j6 - 1];
		}
		for (int j7 = 3; j7 > 0; j7 = j7 - 1) {
			fRec18[j7] = fRec18[j7 - 1];
		}
		for (int j8 = 3; j8 > 0; j8 = j8 - 1) {
			fRec23[j8] = fRec23[j8 - 1];
		}
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		for (int j9 = 4; j9 > 0; j9 = j9 - 1) {
			fRec25[j9] = fRec25[j9 - 1];
		}
		for (int j10 = 3; j10 > 0; j10 = j10 - 1) {
			fRec24[j10] = fRec24[j10 - 1];
		}
		for (int j11 = 3; j11 > 0; j11 = j11 - 1) {
			fRec30[j11] = fRec30[j11 - 1];
		}
		fRec37[1] = fRec37[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		fRec35[2] = fRec35[1];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		for (int j12 = 4; j12 > 0; j12 = j12 - 1) {
			fRec32[j12] = fRec32[j12 - 1];
		}
		for (int j13 = 3; j13 > 0; j13 = j13 - 1) {
			fRec31[j13] = fRec31[j13 - 1];
		}
		for (int j14 = 3; j14 > 0; j14 = j14 - 1) {
			fRec38[j14] = fRec38[j14 - 1];
		}
		fRec39[1] = fRec39[0];
	}
#undef fCheckbox0
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
	case FEEDBACK: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case GAIN: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TONE: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fVslider2_ = (float*)data; // , 2.0, 0.0, 4.0, 0.01 
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
   FEEDBACK, 
} PortIndex;
*/

} // end namespace gx_chump
