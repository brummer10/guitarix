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
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst0;
	double fConst3;
	double fConst5;
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
	double fConst45;
	double fConst47;
	double fConst49;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst59;
	double fConst61;
	double fConst63;
	double fConst64;
	double fConst65;
	double fConst66;
	double fRec3[5];
	double fConst68;
	double fConst70;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec9[2];
	double fConst72;
	double fConst73;
	double fConst74;
	double fConst75;
	double fConst76;
	double fConst77;
	double fConst78;
	double fConst80;
	double fConst81;
	double fConst82;
	double fRec1[4];
	double fConst84;
	double fConst85;
	double fConst86;
	double fConst89;
	double fConst91;
	double fConst92;
	double fConst94;
	double fConst95;
	double fConst96;
	double fRec10[4];
	double fConst98;
	double fConst99;
	double fConst100;
	double fConst101;
	double fConst102;
	double fRec18[2];
	double fRec17[3];
	double fVec1[2];
	double fConst103;
	double fConst104;
	double fRec16[2];
	double fConst105;
	double fRec15[3];
	double fConst106;
	double fRec14[3];
	double fRec13[3];
	double fRec12[5];
	double fRec11[4];
	double fRec19[4];
	double fConst107;
	double fConst108;
	double fConst109;
	double fRec26[2];
	double fRec25[3];
	double fVec2[2];
	double fConst110;
	double fConst111;
	double fRec24[2];
	double fConst112;
	double fRec23[3];
	double fConst113;
	double fRec22[3];
	double fRec21[5];
	double fRec20[4];
	double fRec27[4];
	double fConst114;
	double fConst115;
	double fConst116;
	double fRec33[2];
	double fRec32[3];
	double fVec3[2];
	double fConst117;
	double fConst118;
	double fRec31[2];
	double fConst119;
	double fRec30[3];
	double fConst120;
	double fRec29[5];
	double fRec28[4];
	double fRec34[4];
	double fConst121;
	double fRec38[2];
	double fRec37[3];
	double fRec36[5];
	double fRec35[4];
	double fRec39[4];

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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec2[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fVec0[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec8[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec7[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec6[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec5[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRec4[l7] = 0.0;
	for (int l8 = 0; (l8 < 5); l8 = (l8 + 1)) fRec3[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec9[l9] = 0.0;
	for (int l10 = 0; (l10 < 4); l10 = (l10 + 1)) fRec1[l10] = 0.0;
	for (int l11 = 0; (l11 < 4); l11 = (l11 + 1)) fRec10[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec18[l12] = 0.0;
	for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) fRec17[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fVec1[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec16[l15] = 0.0;
	for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) fRec15[l16] = 0.0;
	for (int l17 = 0; (l17 < 3); l17 = (l17 + 1)) fRec14[l17] = 0.0;
	for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) fRec13[l18] = 0.0;
	for (int l19 = 0; (l19 < 5); l19 = (l19 + 1)) fRec12[l19] = 0.0;
	for (int l20 = 0; (l20 < 4); l20 = (l20 + 1)) fRec11[l20] = 0.0;
	for (int l21 = 0; (l21 < 4); l21 = (l21 + 1)) fRec19[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fRec26[l22] = 0.0;
	for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) fRec25[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fVec2[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fRec24[l25] = 0.0;
	for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) fRec23[l26] = 0.0;
	for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) fRec22[l27] = 0.0;
	for (int l28 = 0; (l28 < 5); l28 = (l28 + 1)) fRec21[l28] = 0.0;
	for (int l29 = 0; (l29 < 4); l29 = (l29 + 1)) fRec20[l29] = 0.0;
	for (int l30 = 0; (l30 < 4); l30 = (l30 + 1)) fRec27[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fRec33[l31] = 0.0;
	for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) fRec32[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fVec3[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec31[l34] = 0.0;
	for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) fRec30[l35] = 0.0;
	for (int l36 = 0; (l36 < 5); l36 = (l36 + 1)) fRec29[l36] = 0.0;
	for (int l37 = 0; (l37 < 4); l37 = (l37 + 1)) fRec28[l37] = 0.0;
	for (int l38 = 0; (l38 < 4); l38 = (l38 + 1)) fRec34[l38] = 0.0;
	for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) fRec38[l39] = 0.0;
	for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) fRec37[l40] = 0.0;
	for (int l41 = 0; (l41 < 5); l41 = (l41 + 1)) fRec36[l41] = 0.0;
	for (int l42 = 0; (l42 < 4); l42 = (l42 + 1)) fRec35[l42] = 0.0;
	for (int l43 = 0; (l43 < 4); l43 = (l43 + 1)) fRec39[l43] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = (9.0131407655162805e-15 * fConst0);
	double fConst2 = ((fConst0 * ((fConst0 * (fConst1 + 1.3955910672935001e-12)) + 6.8634603814664906e-11)) + 1.7999615809463599e-10);
	fConst3 = (fConst0 / fConst2);
	double fConst4 = (5.2572119847843998e-14 * fConst0);
	fConst5 = ((fConst0 * (fConst4 + 2.22632342602781e-12)) + 5.4199400690979899e-15);
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
	fConst45 = mydsp_faustpower2_f(fConst0);
	double fConst46 = (1.99975590383756e-19 * fConst0);
	fConst47 = ((fConst45 * (-6.0498368275157696e-16 - fConst46)) + 1.3013842919715099e-11);
	double fConst48 = (1.9997559038375601e-18 * fConst0);
	fConst49 = ((fConst45 * (-1.05044706792186e-15 - fConst48)) + 6.19273198244244e-13);
	double fConst50 = (1.9334301783374702e-18 * fConst0);
	fConst51 = (fConst45 * (fConst50 + 9.9148601709850608e-16));
	fConst52 = ((2.9996338557563498e-19 * fConst45) + -2.8037288490136399e-13);
	fConst53 = ((2.9996338557563499e-18 * fConst45) + -5.1188389201318301e-14);
	fConst54 = (2.4770927929769801e-14 - (2.9001452675062101e-18 * fConst45));
	fConst55 = ((fConst45 * (6.0498368275157696e-16 - fConst46)) + -1.3013842919715099e-11);
	fConst56 = ((fConst45 * (1.05044706792186e-15 - fConst48)) + -6.19273198244244e-13);
	fConst57 = (fConst45 * (fConst50 + -9.9148601709850608e-16));
	double fConst58 = (4.9993897595939102e-20 * fConst0);
	fConst59 = ((fConst0 * ((fConst0 * (fConst58 + -3.0249184137578799e-16)) + 1.4018644245068199e-13)) + -6.50692145985754e-12);
	double fConst60 = (4.9993897595939098e-19 * fConst0);
	fConst61 = ((fConst0 * ((fConst0 * (fConst60 + -5.2522353396092803e-16)) + 2.5594194600659201e-14)) + -3.09636599122122e-13);
	double fConst62 = (4.8335754458436803e-19 * fConst0);
	fConst63 = (fConst0 * ((fConst0 * (4.9574300854925304e-16 - fConst62)) + -1.23854639648849e-14));
	fConst64 = ((fConst0 * ((fConst0 * (fConst58 + 3.0249184137578799e-16)) + 1.4018644245068199e-13)) + 6.50692145985754e-12);
	fConst65 = ((fConst0 * ((fConst0 * (fConst60 + 5.2522353396092803e-16)) + 2.5594194600659201e-14)) + 3.09636599122122e-13);
	fConst66 = (fConst0 * ((fConst0 * (-4.9574300854925304e-16 - fConst62)) + -1.23854639648849e-14));
	double fConst67 = (2.8419671458380501e-18 * fConst0);
	fConst68 = ((fConst0 * ((fConst0 * (-2.8798600411158901e-15 - fConst67)) + -7.1428107598729697e-12)) + -9.4732238194602296e-11);
	double fConst69 = (1.42098357291903e-14 * fConst0);
	fConst70 = (fConst0 * (-1.89464476389205e-13 - fConst69));
	double fConst71 = (1.1367868583352201e-17 * fConst0);
	fConst72 = ((fConst45 * (fConst71 + 5.7597200822317897e-15)) + -1.8946447638920501e-10);
	fConst73 = (2.84196714583805e-14 * fConst45);
	fConst74 = (1.4285621519745901e-11 - (1.7051802875028302e-17 * fConst45));
	fConst75 = ((fConst45 * (fConst71 + -5.7597200822317897e-15)) + 1.8946447638920501e-10);
	fConst76 = ((fConst0 * ((fConst0 * (2.8798600411158901e-15 - fConst67)) + -7.1428107598729697e-12)) + 9.4732238194602296e-11);
	fConst77 = (fConst0 * (fConst69 + -1.89464476389205e-13));
	fConst78 = (1.0 / fConst2);
	double fConst79 = (2.70394222965488e-14 * fConst0);
	fConst80 = ((fConst0 * ((fConst0 * (-1.3955910672935001e-12 - fConst79)) + 6.8634603814664906e-11)) + 5.3998847428390896e-10);
	fConst81 = ((fConst0 * ((fConst0 * (fConst79 + -1.3955910672935001e-12)) + -6.8634603814664906e-11)) + 5.3998847428390896e-10);
	fConst82 = ((fConst0 * ((fConst0 * (1.3955910672935001e-12 - fConst1)) + -6.8634603814664906e-11)) + 1.7999615809463599e-10);
	double fConst83 = (1.5771635954353199e-13 * fConst0);
	fConst84 = ((fConst0 * (-2.22632342602781e-12 - fConst83)) + 5.4199400690979899e-15);
	fConst85 = ((fConst0 * (fConst83 + -2.22632342602781e-12)) + -5.4199400690979899e-15);
	fConst86 = ((fConst0 * (2.22632342602781e-12 - fConst4)) + -5.4199400690979899e-15);
	double fConst87 = (9.0005010804055195e-15 * fConst0);
	double fConst88 = ((fConst0 * ((fConst0 * (fConst87 + 2.0014450460927301e-12)) + 1.0947588494129801e-10)) + 2.87117546539927e-10);
	fConst89 = (fConst45 / fConst88);
	double fConst90 = (8.0866550780661702e-14 * fConst0);
	fConst91 = (fConst90 + 3.4244003226293501e-12);
	fConst92 = (1.0 / fConst88);
	double fConst93 = (2.7001503241216599e-14 * fConst0);
	fConst94 = ((fConst0 * ((fConst0 * (-2.0014450460927301e-12 - fConst93)) + 1.0947588494129801e-10)) + 8.6135263961978002e-10);
	fConst95 = ((fConst0 * ((fConst0 * (fConst93 + -2.0014450460927301e-12)) + -1.0947588494129801e-10)) + 8.6135263961978002e-10);
	fConst96 = ((fConst0 * ((fConst0 * (2.0014450460927301e-12 - fConst87)) + -1.0947588494129801e-10)) + 2.87117546539927e-10);
	double fConst97 = (2.4259965234198499e-13 * fConst0);
	fConst98 = (-3.4244003226293501e-12 - fConst97);
	fConst99 = (fConst97 + -3.4244003226293501e-12);
	fConst100 = (3.4244003226293501e-12 - fConst90);
	fConst101 = (1.0 / (((fConst19 + 1.0000000000000004) / fConst18) + 1.0));
	fConst102 = (1.0 / (fConst18 * fConst20));
	fConst103 = (0.0 - fConst102);
	fConst104 = (fConst22 / fConst20);
	fConst105 = (((fConst19 + -1.0000000000000004) / fConst18) + 1.0);
	fConst106 = (0.0 - (2.0 / fConst24));
	fConst107 = (1.0 / (((fConst28 + 1.0000000000000004) / fConst27) + 1.0));
	fConst108 = (1.0 / (fConst27 * fConst29));
	fConst109 = (1.0 / fConst20);
	fConst110 = (0.0 - fConst108);
	fConst111 = (fConst31 / fConst29);
	fConst112 = (((fConst28 + -1.0000000000000004) / fConst27) + 1.0);
	fConst113 = (0.0 - (2.0 / fConst33));
	fConst114 = (1.0 / (((fConst37 + 1.0000000000000004) / fConst36) + 1.0));
	fConst115 = (1.0 / (fConst36 * fConst38));
	fConst116 = (1.0 / fConst29);
	fConst117 = (0.0 - fConst115);
	fConst118 = (fConst40 / fConst38);
	fConst119 = (((fConst37 + -1.0000000000000004) / fConst36) + 1.0);
	fConst120 = (0.0 - (2.0 / fConst42));
	fConst121 = (1.0 / fConst38);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fCheckbox0 (*fCheckbox0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
	double fSlow0 = (0.0010000000000000009 * double(fVslider0));
	int iSlow1 = int(double(fCheckbox0));
	double fSlow2 = (0.00036676987543879196 * (std::exp((3.0 * double(fVslider1))) + -1.0));
	double fSlow3 = (0.0070000000000000062 * double(fVslider2));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
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
		double fTemp4 = ((fConst0 * (fConst47 + (fRec2[0] * (fConst49 + (fConst51 * fRec2[0]))))) + 3.0963659912212198e-10);
		double fTemp5 = ((fConst45 * (fConst52 + (fRec2[0] * (fConst53 + (fConst54 * fRec2[0]))))) + 4.64454898683183e-10);
		double fTemp6 = ((fConst0 * (fConst55 + (fRec2[0] * (fConst56 + (fConst57 * fRec2[0]))))) + 3.0963659912212198e-10);
		double fTemp7 = ((fConst0 * (fConst59 + (fRec2[0] * (fConst61 + (fConst63 * fRec2[0]))))) + 7.7409149780530496e-11);
		double fTemp8 = ((fConst0 * (fConst64 + (fRec2[0] * (fConst65 + (fConst66 * fRec2[0]))))) + 7.7409149780530496e-11);
		fRec3[0] = ((fRec4[2] + (fConst39 * (fTemp3 + (fConst41 * fRec4[0])))) - (((((fRec3[1] * fTemp4) + (fRec3[2] * fTemp5)) + (fRec3[3] * fTemp6)) + (fRec3[4] * fTemp7)) / fTemp8));
		fRec9[0] = (fSlow3 + (0.99299999999999999 * fRec9[1]));
		double fTemp9 = (fConst68 + (fConst70 * fRec9[0]));
		double fTemp10 = (fConst72 + (fConst73 * fRec9[0]));
		double fTemp11 = (fConst74 + (3.7892895277840898e-13 * fRec9[0]));
		double fTemp12 = ((fConst45 * (fRec9[0] * (0.0 - (2.84196714583805e-14 * fRec2[0])))) + (fConst75 * fRec2[0]));
		double fTemp13 = (fConst76 + (fConst77 * fRec9[0]));
		double fTemp14 = (fConst0 * ((((fRec2[0] * (((fRec3[0] * fTemp9) + (fRec3[1] * fTemp10)) + (fConst0 * (fRec3[2] * fTemp11)))) + (fRec3[3] * fTemp12)) + ((fRec2[0] * fRec3[4]) * fTemp13)) / fTemp8));
		double fTemp15 = (int(signbit(double(fTemp14))) ? double(redeyechumppre_negclip(double(fTemp14))) : double(redeyechumppreclip(double(fTemp14))));
		fRec1[0] = (fTemp15 - (fConst78 * (((fConst80 * fRec1[1]) + (fConst81 * fRec1[2])) + (fConst82 * fRec1[3]))));
		double fTemp16 = (fConst3 * ((((fConst5 * fRec1[0]) + (fConst84 * fRec1[1])) + (fConst85 * fRec1[2])) + (fConst86 * fRec1[3])));
		fRec10[0] = (fTemp15 - (fConst92 * (((fConst94 * fRec10[1]) + (fConst95 * fRec10[2])) + (fConst96 * fRec10[3]))));
		double fTemp17 = (fConst89 * ((((fConst91 * fRec10[0]) + (fConst98 * fRec10[1])) + (fConst99 * fRec10[2])) + (fConst100 * fRec10[3])));
		fRec18[0] = (0.0 - (fConst13 * ((fConst14 * fRec18[1]) - (fTemp0 + fVec0[1]))));
		fRec17[0] = (fRec18[0] - (fConst8 * ((fConst15 * fRec17[2]) + (fConst16 * fRec17[1]))));
		double fTemp18 = (fRec17[2] + (fRec17[0] + (2.0 * fRec17[1])));
		fVec1[0] = fTemp18;
		fRec16[0] = ((fConst8 * ((fConst102 * fTemp18) + (fConst103 * fVec1[1]))) - (fConst104 * fRec16[1]));
		fRec15[0] = (fRec16[0] - (fConst101 * ((fConst105 * fRec15[2]) + (fConst26 * fRec15[1]))));
		double fTemp19 = (fConst35 * fRec14[1]);
		fRec14[0] = ((fConst101 * (((fConst25 * fRec15[0]) + (fConst106 * fRec15[1])) + (fConst25 * fRec15[2]))) - (fConst30 * ((fConst32 * fRec14[2]) + fTemp19)));
		double fTemp20 = (fConst44 * fRec13[1]);
		fRec13[0] = ((fRec14[2] + (fConst30 * (fTemp19 + (fConst32 * fRec14[0])))) - (fConst39 * ((fConst41 * fRec13[2]) + fTemp20)));
		fRec12[0] = ((fRec13[2] + (fConst39 * (fTemp20 + (fConst41 * fRec13[0])))) - (((((fTemp4 * fRec12[1]) + (fTemp5 * fRec12[2])) + (fTemp6 * fRec12[3])) + (fTemp7 * fRec12[4])) / fTemp8));
		double fTemp21 = (fRec2[0] * fTemp13);
		double fTemp22 = (fConst0 * ((((fRec2[0] * (((fRec12[0] * fTemp9) + (fTemp10 * fRec12[1])) + (fConst0 * (fTemp11 * fRec12[2])))) + (fTemp12 * fRec12[3])) + (fTemp21 * fRec12[4])) / fTemp8));
		double fTemp23 = (int(signbit(double(fTemp22))) ? double(redeyechumppre_negclip(double(fTemp22))) : double(redeyechumppreclip(double(fTemp22))));
		fRec11[0] = (fTemp23 - (fConst78 * (((fConst80 * fRec11[1]) + (fConst81 * fRec11[2])) + (fConst82 * fRec11[3]))));
		double fTemp24 = (fConst3 * ((((fConst5 * fRec11[0]) + (fConst84 * fRec11[1])) + (fConst85 * fRec11[2])) + (fConst86 * fRec11[3])));
		fRec19[0] = (fTemp23 - (fConst92 * (((fConst94 * fRec19[1]) + (fConst95 * fRec19[2])) + (fConst96 * fRec19[3]))));
		double fTemp25 = (fConst89 * ((((fConst91 * fRec19[0]) + (fConst98 * fRec19[1])) + (fConst99 * fRec19[2])) + (fConst100 * fRec19[3])));
		fRec26[0] = (0.0 - (fConst109 * ((fConst22 * fRec26[1]) - (fConst8 * (fTemp18 + fVec1[1])))));
		fRec25[0] = (fRec26[0] - (fConst101 * ((fConst105 * fRec25[2]) + (fConst26 * fRec25[1]))));
		double fTemp26 = (fRec25[2] + (fRec25[0] + (2.0 * fRec25[1])));
		fVec2[0] = fTemp26;
		fRec24[0] = ((fConst101 * ((fConst108 * fTemp26) + (fConst110 * fVec2[1]))) - (fConst111 * fRec24[1]));
		fRec23[0] = (fRec24[0] - (fConst107 * ((fConst112 * fRec23[2]) + (fConst35 * fRec23[1]))));
		double fTemp27 = (fConst44 * fRec22[1]);
		fRec22[0] = ((fConst107 * (((fConst34 * fRec23[0]) + (fConst113 * fRec23[1])) + (fConst34 * fRec23[2]))) - (fConst39 * ((fConst41 * fRec22[2]) + fTemp27)));
		fRec21[0] = ((fRec22[2] + (fConst39 * (fTemp27 + (fConst41 * fRec22[0])))) - (((((fTemp4 * fRec21[1]) + (fTemp5 * fRec21[2])) + (fTemp6 * fRec21[3])) + (fTemp7 * fRec21[4])) / fTemp8));
		double fTemp28 = (fConst0 * ((((fRec2[0] * (((fRec21[0] * fTemp9) + (fTemp10 * fRec21[1])) + (fConst0 * (fTemp11 * fRec21[2])))) + (fTemp12 * fRec21[3])) + (fTemp21 * fRec21[4])) / fTemp8));
		double fTemp29 = (int(signbit(double(fTemp28))) ? double(redeyechumppre_negclip(double(fTemp28))) : double(redeyechumppreclip(double(fTemp28))));
		fRec20[0] = (fTemp29 - (fConst78 * (((fConst80 * fRec20[1]) + (fConst81 * fRec20[2])) + (fConst82 * fRec20[3]))));
		double fTemp30 = (fConst3 * ((((fConst5 * fRec20[0]) + (fConst84 * fRec20[1])) + (fConst85 * fRec20[2])) + (fConst86 * fRec20[3])));
		fRec27[0] = (fTemp29 - (fConst92 * (((fConst94 * fRec27[1]) + (fConst95 * fRec27[2])) + (fConst96 * fRec27[3]))));
		double fTemp31 = (fConst89 * ((((fConst91 * fRec27[0]) + (fConst98 * fRec27[1])) + (fConst99 * fRec27[2])) + (fConst100 * fRec27[3])));
		fRec33[0] = (0.0 - (fConst116 * ((fConst31 * fRec33[1]) - (fConst101 * (fTemp26 + fVec2[1])))));
		fRec32[0] = (fRec33[0] - (fConst107 * ((fConst112 * fRec32[2]) + (fConst35 * fRec32[1]))));
		double fTemp32 = (fRec32[2] + (fRec32[0] + (2.0 * fRec32[1])));
		fVec3[0] = fTemp32;
		fRec31[0] = ((fConst107 * ((fConst115 * fTemp32) + (fConst117 * fVec3[1]))) - (fConst118 * fRec31[1]));
		fRec30[0] = (fRec31[0] - (fConst114 * ((fConst119 * fRec30[2]) + (fConst44 * fRec30[1]))));
		fRec29[0] = ((fConst114 * (((fConst43 * fRec30[0]) + (fConst120 * fRec30[1])) + (fConst43 * fRec30[2]))) - (((((fTemp4 * fRec29[1]) + (fTemp5 * fRec29[2])) + (fTemp6 * fRec29[3])) + (fTemp7 * fRec29[4])) / fTemp8));
		double fTemp33 = (fConst0 * ((((fRec2[0] * (((fRec29[0] * fTemp9) + (fTemp10 * fRec29[1])) + (fConst0 * (fTemp11 * fRec29[2])))) + (fTemp12 * fRec29[3])) + (fTemp21 * fRec29[4])) / fTemp8));
		double fTemp34 = (int(signbit(double(fTemp33))) ? double(redeyechumppre_negclip(double(fTemp33))) : double(redeyechumppreclip(double(fTemp33))));
		fRec28[0] = (fTemp34 - (fConst78 * (((fConst80 * fRec28[1]) + (fConst81 * fRec28[2])) + (fConst82 * fRec28[3]))));
		double fTemp35 = (fConst3 * ((((fConst5 * fRec28[0]) + (fConst84 * fRec28[1])) + (fConst85 * fRec28[2])) + (fConst86 * fRec28[3])));
		fRec34[0] = (fTemp34 - (fConst92 * (((fConst94 * fRec34[1]) + (fConst95 * fRec34[2])) + (fConst96 * fRec34[3]))));
		double fTemp36 = (fConst89 * ((((fConst91 * fRec34[0]) + (fConst98 * fRec34[1])) + (fConst99 * fRec34[2])) + (fConst100 * fRec34[3])));
		fRec38[0] = (0.0 - (fConst121 * ((fConst40 * fRec38[1]) - (fConst107 * (fTemp32 + fVec3[1])))));
		fRec37[0] = (fRec38[0] - (fConst114 * ((fConst119 * fRec37[2]) + (fConst44 * fRec37[1]))));
		fRec36[0] = ((fConst114 * (fRec37[2] + (fRec37[0] + (2.0 * fRec37[1])))) - (((((fTemp4 * fRec36[1]) + (fTemp5 * fRec36[2])) + (fTemp6 * fRec36[3])) + (fTemp7 * fRec36[4])) / fTemp8));
		double fTemp37 = (fConst0 * ((((fRec2[0] * (((fRec36[0] * fTemp9) + (fTemp10 * fRec36[1])) + (fConst0 * (fTemp11 * fRec36[2])))) + (fTemp12 * fRec36[3])) + (fTemp21 * fRec36[4])) / fTemp8));
		double fTemp38 = (int(signbit(double(fTemp37))) ? double(redeyechumppre_negclip(double(fTemp37))) : double(redeyechumppreclip(double(fTemp37))));
		fRec35[0] = (fTemp38 - (fConst78 * (((fConst80 * fRec35[1]) + (fConst81 * fRec35[2])) + (fConst82 * fRec35[3]))));
		double fTemp39 = (fConst3 * ((((fConst5 * fRec35[0]) + (fConst84 * fRec35[1])) + (fConst85 * fRec35[2])) + (fConst86 * fRec35[3])));
		fRec39[0] = (fTemp38 - (fConst92 * (((fConst94 * fRec39[1]) + (fConst95 * fRec39[2])) + (fConst96 * fRec39[3]))));
		double fTemp40 = (fConst89 * ((((fConst91 * fRec39[0]) + (fConst98 * fRec39[1])) + (fConst99 * fRec39[2])) + (fConst100 * fRec39[3])));
		output0[i0] = FAUSTFLOAT((fRec0[0] * (((((iSlow1 ? (int(signbit(double(fTemp17))) ? double(redeyechumppow_negclip(double(fTemp17))) : double(redeyechumppowclip(double(fTemp17)))) : (int(signbit(double(fTemp16))) ? double(redeyechumppowf_negclip(double(fTemp16))) : double(redeyechumppowfclip(double(fTemp16))))) + (iSlow1 ? (int(signbit(double(fTemp25))) ? double(redeyechumppow_negclip(double(fTemp25))) : double(redeyechumppowclip(double(fTemp25)))) : (int(signbit(double(fTemp24))) ? double(redeyechumppowf_negclip(double(fTemp24))) : double(redeyechumppowfclip(double(fTemp24)))))) + (iSlow1 ? (int(signbit(double(fTemp31))) ? double(redeyechumppow_negclip(double(fTemp31))) : double(redeyechumppowclip(double(fTemp31)))) : (int(signbit(double(fTemp30))) ? double(redeyechumppowf_negclip(double(fTemp30))) : double(redeyechumppowfclip(double(fTemp30)))))) + (iSlow1 ? (int(signbit(double(fTemp36))) ? double(redeyechumppow_negclip(double(fTemp36))) : double(redeyechumppowclip(double(fTemp36)))) : (int(signbit(double(fTemp35))) ? double(redeyechumppowf_negclip(double(fTemp35))) : double(redeyechumppowfclip(double(fTemp35)))))) + (iSlow1 ? (int(signbit(double(fTemp40))) ? double(redeyechumppow_negclip(double(fTemp40))) : double(redeyechumppowclip(double(fTemp40)))) : (int(signbit(double(fTemp39))) ? double(redeyechumppowf_negclip(double(fTemp39))) : double(redeyechumppowfclip(double(fTemp39))))))));
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
		for (int j0 = 4; (j0 > 0); j0 = (j0 - 1)) {
			fRec3[j0] = fRec3[(j0 - 1)];
		}
		fRec9[1] = fRec9[0];
		for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
			fRec1[j1] = fRec1[(j1 - 1)];
		}
		for (int j2 = 3; (j2 > 0); j2 = (j2 - 1)) {
			fRec10[j2] = fRec10[(j2 - 1)];
		}
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
		for (int j3 = 4; (j3 > 0); j3 = (j3 - 1)) {
			fRec12[j3] = fRec12[(j3 - 1)];
		}
		for (int j4 = 3; (j4 > 0); j4 = (j4 - 1)) {
			fRec11[j4] = fRec11[(j4 - 1)];
		}
		for (int j5 = 3; (j5 > 0); j5 = (j5 - 1)) {
			fRec19[j5] = fRec19[(j5 - 1)];
		}
		fRec26[1] = fRec26[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		fVec2[1] = fVec2[0];
		fRec24[1] = fRec24[0];
		fRec23[2] = fRec23[1];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		for (int j6 = 4; (j6 > 0); j6 = (j6 - 1)) {
			fRec21[j6] = fRec21[(j6 - 1)];
		}
		for (int j7 = 3; (j7 > 0); j7 = (j7 - 1)) {
			fRec20[j7] = fRec20[(j7 - 1)];
		}
		for (int j8 = 3; (j8 > 0); j8 = (j8 - 1)) {
			fRec27[j8] = fRec27[(j8 - 1)];
		}
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fVec3[1] = fVec3[0];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		for (int j9 = 4; (j9 > 0); j9 = (j9 - 1)) {
			fRec29[j9] = fRec29[(j9 - 1)];
		}
		for (int j10 = 3; (j10 > 0); j10 = (j10 - 1)) {
			fRec28[j10] = fRec28[(j10 - 1)];
		}
		for (int j11 = 3; (j11 > 0); j11 = (j11 - 1)) {
			fRec34[j11] = fRec34[(j11 - 1)];
		}
		fRec38[1] = fRec38[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		for (int j12 = 4; (j12 > 0); j12 = (j12 - 1)) {
			fRec36[j12] = fRec36[(j12 - 1)];
		}
		for (int j13 = 3; (j13 > 0); j13 = (j13 - 1)) {
			fRec35[j13] = fRec35[(j13 - 1)];
		}
		for (int j14 = 3; (j14 > 0); j14 = (j14 - 1)) {
			fRec39[j14] = fRec39[(j14 - 1)];
		}
	}
#undef fVslider0
#undef fCheckbox0
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
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TONE: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fVslider0_ = (float*)data; // , 2.0, 0.0, 4.0, 0.01 
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
