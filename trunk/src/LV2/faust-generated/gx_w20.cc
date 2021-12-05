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
	double fConst3;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec1[2];
	double fConst5;
	double fConst6;
	double fConst8;
	double fConst10;
	double fVec0[2];
	double fConst11;
	double fConst12;
	double fRec7[2];
	double fConst13;
	double fConst14;
	double fRec6[3];
	double fConst15;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst23;
	double fConst24;
	double fRec5[3];
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst32;
	double fConst33;
	double fRec4[3];
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst41;
	double fConst42;
	double fRec3[3];
	double fConst44;
	double fConst46;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst53;
	double fConst55;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fRec2[4];
	double fConst62;
	double fConst63;
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
	double fRec8[2];
	double fConst72;
	double fConst73;
	double fRec16[2];
	double fRec15[3];
	double fVec1[2];
	double fConst74;
	double fConst75;
	double fRec14[2];
	double fConst76;
	double fRec13[3];
	double fConst77;
	double fRec12[3];
	double fRec11[3];
	double fRec10[4];
	double fRec9[2];
	double fConst78;
	double fConst79;
	double fConst80;
	double fRec23[2];
	double fRec22[3];
	double fVec2[2];
	double fConst81;
	double fConst82;
	double fRec21[2];
	double fConst83;
	double fRec20[3];
	double fConst84;
	double fRec19[3];
	double fRec18[4];
	double fRec17[2];
	double fConst85;
	double fConst86;
	double fConst87;
	double fRec29[2];
	double fRec28[3];
	double fVec3[2];
	double fConst88;
	double fConst89;
	double fRec27[2];
	double fConst90;
	double fRec26[3];
	double fConst91;
	double fRec25[4];
	double fRec24[2];
	double fConst92;
	double fRec33[2];
	double fRec32[3];
	double fRec31[4];
	double fRec30[2];

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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec1[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fVec0[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec7[l2] = 0.0;
	for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) fRec6[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec5[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec4[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec3[l6] = 0.0;
	for (int l7 = 0; (l7 < 4); l7 = (l7 + 1)) fRec2[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec0[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec8[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec16[l10] = 0.0;
	for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) fRec15[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fVec1[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec14[l13] = 0.0;
	for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) fRec13[l14] = 0.0;
	for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) fRec12[l15] = 0.0;
	for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) fRec11[l16] = 0.0;
	for (int l17 = 0; (l17 < 4); l17 = (l17 + 1)) fRec10[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec9[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec23[l19] = 0.0;
	for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) fRec22[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fVec2[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fRec21[l22] = 0.0;
	for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) fRec20[l23] = 0.0;
	for (int l24 = 0; (l24 < 3); l24 = (l24 + 1)) fRec19[l24] = 0.0;
	for (int l25 = 0; (l25 < 4); l25 = (l25 + 1)) fRec18[l25] = 0.0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fRec17[l26] = 0.0;
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) fRec29[l27] = 0.0;
	for (int l28 = 0; (l28 < 3); l28 = (l28 + 1)) fRec28[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fVec3[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec27[l30] = 0.0;
	for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) fRec26[l31] = 0.0;
	for (int l32 = 0; (l32 < 4); l32 = (l32 + 1)) fRec25[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fRec24[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec33[l34] = 0.0;
	for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) fRec32[l35] = 0.0;
	for (int l36 = 0; (l36 < 4); l36 = (l36 + 1)) fRec31[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fRec30[l37] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = (2.07411011655813e-05 * fConst0);
	double fConst2 = (fConst1 + 0.0044271440520969102);
	fConst3 = (fConst0 / fConst2);
	double fConst4 = std::tan((20517.741620594938 / fConst0));
	fConst5 = (1.0 / fConst4);
	fConst6 = (1.0 / (((fConst5 + 1.0000000000000004) / fConst4) + 1.0));
	double fConst7 = mydsp_faustpower2_f(fConst4);
	fConst8 = (1.0 / fConst7);
	double fConst9 = (fConst5 + 1.0);
	fConst10 = (0.0 - (1.0 / (fConst4 * fConst9)));
	fConst11 = (1.0 / fConst9);
	fConst12 = (1.0 - fConst5);
	fConst13 = (((fConst5 + -1.0000000000000004) / fConst4) + 1.0);
	fConst14 = (2.0 * (1.0 - fConst8));
	fConst15 = (0.0 - (2.0 / fConst7));
	double fConst16 = std::tan((3769.9111843077517 / fConst0));
	double fConst17 = (1.0 / fConst16);
	double fConst18 = (fConst17 + 1.0);
	fConst19 = (1.0 / ((fConst18 / fConst16) + 1.0));
	fConst20 = (1.0 - fConst17);
	fConst21 = (1.0 - (fConst20 / fConst16));
	double fConst22 = mydsp_faustpower2_f(fConst16);
	fConst23 = (1.0 / fConst22);
	fConst24 = (2.0 * (1.0 - fConst23));
	double fConst25 = std::tan((659.73445725385659 / fConst0));
	double fConst26 = (1.0 / fConst25);
	double fConst27 = (fConst26 + 1.0);
	fConst28 = (1.0 / ((fConst27 / fConst25) + 1.0));
	fConst29 = (1.0 - fConst26);
	fConst30 = (1.0 - (fConst29 / fConst25));
	double fConst31 = mydsp_faustpower2_f(fConst25);
	fConst32 = (1.0 / fConst31);
	fConst33 = (2.0 * (1.0 - fConst32));
	double fConst34 = std::tan((270.1769682087222 / fConst0));
	double fConst35 = (1.0 / fConst34);
	double fConst36 = (fConst35 + 1.0);
	fConst37 = (1.0 / ((fConst36 / fConst34) + 1.0));
	fConst38 = (1.0 - fConst35);
	fConst39 = (1.0 - (fConst38 / fConst34));
	double fConst40 = mydsp_faustpower2_f(fConst34);
	fConst41 = (1.0 / fConst40);
	fConst42 = (2.0 * (1.0 - fConst41));
	double fConst43 = (2.4303358425833099e-15 * fConst0);
	fConst44 = ((fConst0 * (-1.34509147324758e-10 - fConst43)) + 6.3306072420472404e-08);
	double fConst45 = (6.8704107329372702e-14 * fConst0);
	fConst46 = ((fConst0 * (1.12102439518276e-11 - fConst45)) + -3.4546917434926099e-10);
	double fConst47 = (7.1134443171955998e-14 * fConst0);
	fConst48 = (fConst0 * (fConst47 + 6.9093834869852202e-13));
	fConst49 = ((fConst0 * (fConst43 + -1.34509147324758e-10)) + -6.3306072420472404e-08);
	fConst50 = ((fConst0 * (fConst45 + 1.12102439518276e-11)) + 3.4546917434926099e-10);
	fConst51 = (fConst0 * (6.9093834869852202e-13 - fConst47));
	double fConst52 = (8.1011194752777097e-16 * fConst0);
	fConst53 = ((fConst0 * (1.34509147324758e-10 - fConst52)) + -6.3306072420472404e-08);
	double fConst54 = (2.2901369109790902e-14 * fConst0);
	fConst55 = ((fConst0 * (-1.12102439518276e-11 - fConst54)) + 3.4546917434926099e-10);
	double fConst56 = (2.3711481057318699e-14 * fConst0);
	fConst57 = (fConst0 * (fConst56 + -6.9093834869852202e-13));
	fConst58 = ((fConst0 * (fConst52 + 1.34509147324758e-10)) + 6.3306072420472404e-08);
	fConst59 = ((fConst0 * (fConst54 + -1.12102439518276e-11)) + -3.4546917434926099e-10);
	fConst60 = (fConst0 * (-6.9093834869852202e-13 - fConst56));
	double fConst61 = (1.44375296887024e-12 * fConst0);
	fConst62 = ((fConst0 * (-7.2406398893340597e-09 - fConst61)) + -1.0937522491441e-07);
	fConst63 = (fConst0 * (fConst61 + 2.1875044982882e-11));
	double fConst64 = (4.3312589066107104e-12 * fConst0);
	fConst65 = ((fConst0 * (fConst64 + 7.2406398893340597e-09)) + -1.0937522491441e-07);
	fConst66 = (fConst0 * (-2.1875044982882e-11 - fConst64));
	fConst67 = ((fConst0 * (7.2406398893340597e-09 - fConst64)) + 1.0937522491441e-07);
	fConst68 = (fConst0 * (fConst64 + -2.1875044982882e-11));
	fConst69 = ((fConst0 * (fConst61 + -7.2406398893340597e-09)) + 1.0937522491441e-07);
	fConst70 = (fConst0 * (2.1875044982882e-11 - fConst61));
	fConst71 = ((0.0044271440520969102 - fConst1) / fConst2);
	fConst72 = (1.0 / (((fConst17 + 1.0000000000000004) / fConst16) + 1.0));
	fConst73 = (1.0 / (fConst16 * fConst18));
	fConst74 = (0.0 - fConst73);
	fConst75 = (fConst20 / fConst18);
	fConst76 = (((fConst17 + -1.0000000000000004) / fConst16) + 1.0);
	fConst77 = (0.0 - (2.0 / fConst22));
	fConst78 = (1.0 / (((fConst26 + 1.0000000000000004) / fConst25) + 1.0));
	fConst79 = (1.0 / (fConst25 * fConst27));
	fConst80 = (1.0 / fConst18);
	fConst81 = (0.0 - fConst79);
	fConst82 = (fConst29 / fConst27);
	fConst83 = (((fConst26 + -1.0000000000000004) / fConst25) + 1.0);
	fConst84 = (0.0 - (2.0 / fConst31));
	fConst85 = (1.0 / (((fConst35 + 1.0000000000000004) / fConst34) + 1.0));
	fConst86 = (1.0 / (fConst34 * fConst36));
	fConst87 = (1.0 / fConst27);
	fConst88 = (0.0 - fConst86);
	fConst89 = (fConst38 / fConst36);
	fConst90 = (((fConst35 + -1.0000000000000004) / fConst34) + 1.0);
	fConst91 = (0.0 - (2.0 / fConst40));
	fConst92 = (1.0 / fConst36);
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
	double fSlow0 = (0.00036676987543879196 * (std::exp((3.0 * double(fVslider0))) + -1.0));
	double fSlow1 = (0.00036676987543879196 * (std::exp((3.0 * double(fVslider1))) + -1.0));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		fRec1[0] = (fSlow0 + (0.99299999999999999 * fRec1[1]));
		double fTemp0 = double(input0[i0]);
		fVec0[0] = fTemp0;
		fRec7[0] = ((fConst10 * fVec0[1]) - (fConst11 * ((fConst12 * fRec7[1]) - (fConst5 * fTemp0))));
		fRec6[0] = (fRec7[0] - (fConst6 * ((fConst13 * fRec6[2]) + (fConst14 * fRec6[1]))));
		double fTemp1 = (fConst24 * fRec5[1]);
		fRec5[0] = ((fConst6 * (((fConst8 * fRec6[0]) + (fConst15 * fRec6[1])) + (fConst8 * fRec6[2]))) - (fConst19 * ((fConst21 * fRec5[2]) + fTemp1)));
		double fTemp2 = (fConst33 * fRec4[1]);
		fRec4[0] = ((fRec5[2] + (fConst19 * (fTemp1 + (fConst21 * fRec5[0])))) - (fConst28 * ((fConst30 * fRec4[2]) + fTemp2)));
		double fTemp3 = (fConst42 * fRec3[1]);
		fRec3[0] = ((fRec4[2] + (fConst28 * (fTemp2 + (fConst30 * fRec4[0])))) - (fConst37 * ((fConst39 * fRec3[2]) + fTemp3)));
		double fTemp4 = ((fConst0 * (fConst44 + (fRec1[0] * (fConst46 + (fConst48 * fRec1[0]))))) + 5.1820376152389203e-06);
		double fTemp5 = ((fConst0 * (fConst49 + (fRec1[0] * (fConst50 + (fConst51 * fRec1[0]))))) + 5.1820376152389203e-06);
		double fTemp6 = ((fConst0 * (fConst53 + (fRec1[0] * (fConst55 + (fConst57 * fRec1[0]))))) + 1.72734587174631e-06);
		double fTemp7 = ((fConst0 * (fConst58 + (fRec1[0] * (fConst59 + (fConst60 * fRec1[0]))))) + 1.72734587174631e-06);
		fRec2[0] = ((fRec3[2] + (fConst37 * (fTemp3 + (fConst39 * fRec3[0])))) - ((((fRec2[1] * fTemp4) + (fRec2[2] * fTemp5)) + (fRec2[3] * fTemp6)) / fTemp7));
		double fTemp8 = (fConst62 + (fConst63 * fRec1[0]));
		double fTemp9 = (fConst65 + (fConst66 * fRec1[0]));
		double fTemp10 = (fConst67 + (fConst68 * fRec1[0]));
		double fTemp11 = (fConst69 + (fConst70 * fRec1[0]));
		double fTemp12 = (fConst0 * ((fRec1[0] * ((((fRec2[0] * fTemp8) + (fRec2[1] * fTemp9)) + (fRec2[2] * fTemp10)) + (fRec2[3] * fTemp11))) / fTemp7));
		double fThen0 = double(w20_1clip(double(fTemp12)));
		double fElse0 = double(w20_1_negclip(double(fTemp12)));
		fRec0[0] = ((int(signbit(double(fTemp12))) ? fElse0 : fThen0) - (fConst71 * fRec0[1]));
		fRec8[0] = (fSlow1 + (0.99299999999999999 * fRec8[1]));
		double fTemp13 = (0.0 - (0.00061610099403943601 * fRec8[0]));
		double fTemp14 = (fConst3 * ((fRec0[0] * fTemp13) + (0.00061610099403943601 * (fRec8[0] * fRec0[1]))));
		double fThen1 = double(w20_2aclip(double(fTemp14)));
		double fElse1 = double(w20_2a_negclip(double(fTemp14)));
		fRec16[0] = (0.0 - (fConst11 * ((fConst12 * fRec16[1]) - (fTemp0 + fVec0[1]))));
		fRec15[0] = (fRec16[0] - (fConst6 * ((fConst13 * fRec15[2]) + (fConst14 * fRec15[1]))));
		double fTemp15 = (fRec15[2] + (fRec15[0] + (2.0 * fRec15[1])));
		fVec1[0] = fTemp15;
		fRec14[0] = ((fConst6 * ((fConst73 * fTemp15) + (fConst74 * fVec1[1]))) - (fConst75 * fRec14[1]));
		fRec13[0] = (fRec14[0] - (fConst72 * ((fConst76 * fRec13[2]) + (fConst24 * fRec13[1]))));
		double fTemp16 = (fConst33 * fRec12[1]);
		fRec12[0] = ((fConst72 * (((fConst23 * fRec13[0]) + (fConst77 * fRec13[1])) + (fConst23 * fRec13[2]))) - (fConst28 * ((fConst30 * fRec12[2]) + fTemp16)));
		double fTemp17 = (fConst42 * fRec11[1]);
		fRec11[0] = ((fRec12[2] + (fConst28 * (fTemp16 + (fConst30 * fRec12[0])))) - (fConst37 * ((fConst39 * fRec11[2]) + fTemp17)));
		fRec10[0] = ((fRec11[2] + (fConst37 * (fTemp17 + (fConst39 * fRec11[0])))) - ((((fTemp4 * fRec10[1]) + (fTemp5 * fRec10[2])) + (fTemp6 * fRec10[3])) / fTemp7));
		double fTemp18 = (fConst0 * ((fRec1[0] * ((((fRec10[0] * fTemp8) + (fTemp9 * fRec10[1])) + (fTemp10 * fRec10[2])) + (fTemp11 * fRec10[3]))) / fTemp7));
		double fThen2 = double(w20_1clip(double(fTemp18)));
		double fElse2 = double(w20_1_negclip(double(fTemp18)));
		fRec9[0] = ((int(signbit(double(fTemp18))) ? fElse2 : fThen2) - (fConst71 * fRec9[1]));
		double fTemp19 = (fConst3 * ((fRec9[0] * fTemp13) + (0.00061610099403943601 * (fRec8[0] * fRec9[1]))));
		double fThen3 = double(w20_2aclip(double(fTemp19)));
		double fElse3 = double(w20_2a_negclip(double(fTemp19)));
		fRec23[0] = (0.0 - (fConst80 * ((fConst20 * fRec23[1]) - (fConst6 * (fTemp15 + fVec1[1])))));
		fRec22[0] = (fRec23[0] - (fConst72 * ((fConst76 * fRec22[2]) + (fConst24 * fRec22[1]))));
		double fTemp20 = (fRec22[2] + (fRec22[0] + (2.0 * fRec22[1])));
		fVec2[0] = fTemp20;
		fRec21[0] = ((fConst72 * ((fConst79 * fTemp20) + (fConst81 * fVec2[1]))) - (fConst82 * fRec21[1]));
		fRec20[0] = (fRec21[0] - (fConst78 * ((fConst83 * fRec20[2]) + (fConst33 * fRec20[1]))));
		double fTemp21 = (fConst42 * fRec19[1]);
		fRec19[0] = ((fConst78 * (((fConst32 * fRec20[0]) + (fConst84 * fRec20[1])) + (fConst32 * fRec20[2]))) - (fConst37 * ((fConst39 * fRec19[2]) + fTemp21)));
		fRec18[0] = ((fRec19[2] + (fConst37 * (fTemp21 + (fConst39 * fRec19[0])))) - ((((fTemp4 * fRec18[1]) + (fTemp5 * fRec18[2])) + (fTemp6 * fRec18[3])) / fTemp7));
		double fTemp22 = (fConst0 * ((fRec1[0] * ((((fRec18[0] * fTemp8) + (fTemp9 * fRec18[1])) + (fTemp10 * fRec18[2])) + (fTemp11 * fRec18[3]))) / fTemp7));
		double fThen4 = double(w20_1clip(double(fTemp22)));
		double fElse4 = double(w20_1_negclip(double(fTemp22)));
		fRec17[0] = ((int(signbit(double(fTemp22))) ? fElse4 : fThen4) - (fConst71 * fRec17[1]));
		double fTemp23 = (fConst3 * ((fRec17[0] * fTemp13) + (0.00061610099403943601 * (fRec8[0] * fRec17[1]))));
		double fThen5 = double(w20_2aclip(double(fTemp23)));
		double fElse5 = double(w20_2a_negclip(double(fTemp23)));
		fRec29[0] = (0.0 - (fConst87 * ((fConst29 * fRec29[1]) - (fConst72 * (fTemp20 + fVec2[1])))));
		fRec28[0] = (fRec29[0] - (fConst78 * ((fConst83 * fRec28[2]) + (fConst33 * fRec28[1]))));
		double fTemp24 = (fRec28[2] + (fRec28[0] + (2.0 * fRec28[1])));
		fVec3[0] = fTemp24;
		fRec27[0] = ((fConst78 * ((fConst86 * fTemp24) + (fConst88 * fVec3[1]))) - (fConst89 * fRec27[1]));
		fRec26[0] = (fRec27[0] - (fConst85 * ((fConst90 * fRec26[2]) + (fConst42 * fRec26[1]))));
		fRec25[0] = ((fConst85 * (((fConst41 * fRec26[0]) + (fConst91 * fRec26[1])) + (fConst41 * fRec26[2]))) - ((((fTemp4 * fRec25[1]) + (fTemp5 * fRec25[2])) + (fTemp6 * fRec25[3])) / fTemp7));
		double fTemp25 = (fConst0 * ((fRec1[0] * ((((fRec25[0] * fTemp8) + (fTemp9 * fRec25[1])) + (fTemp10 * fRec25[2])) + (fTemp11 * fRec25[3]))) / fTemp7));
		double fThen6 = double(w20_1clip(double(fTemp25)));
		double fElse6 = double(w20_1_negclip(double(fTemp25)));
		fRec24[0] = ((int(signbit(double(fTemp25))) ? fElse6 : fThen6) - (fConst71 * fRec24[1]));
		double fTemp26 = (fConst3 * ((fRec24[0] * fTemp13) + (0.00061610099403943601 * (fRec8[0] * fRec24[1]))));
		double fThen7 = double(w20_2aclip(double(fTemp26)));
		double fElse7 = double(w20_2a_negclip(double(fTemp26)));
		fRec33[0] = (0.0 - (fConst92 * ((fConst38 * fRec33[1]) - (fConst78 * (fTemp24 + fVec3[1])))));
		fRec32[0] = (fRec33[0] - (fConst85 * ((fConst90 * fRec32[2]) + (fConst42 * fRec32[1]))));
		fRec31[0] = ((fConst85 * (fRec32[2] + (fRec32[0] + (2.0 * fRec32[1])))) - ((((fTemp4 * fRec31[1]) + (fTemp5 * fRec31[2])) + (fTemp6 * fRec31[3])) / fTemp7));
		double fTemp27 = (fConst0 * ((fRec1[0] * ((((fRec31[0] * fTemp8) + (fTemp9 * fRec31[1])) + (fTemp10 * fRec31[2])) + (fTemp11 * fRec31[3]))) / fTemp7));
		double fThen8 = double(w20_1clip(double(fTemp27)));
		double fElse8 = double(w20_1_negclip(double(fTemp27)));
		fRec30[0] = ((int(signbit(double(fTemp27))) ? fElse8 : fThen8) - (fConst71 * fRec30[1]));
		double fTemp28 = (fConst3 * ((fRec30[0] * fTemp13) + (0.00061610099403943601 * (fRec8[0] * fRec30[1]))));
		double fThen9 = double(w20_2aclip(double(fTemp28)));
		double fElse9 = double(w20_2a_negclip(double(fTemp28)));
		output0[i0] = FAUSTFLOAT((((((int(signbit(double(fTemp14))) ? fElse1 : fThen1) + (int(signbit(double(fTemp19))) ? fElse3 : fThen3)) + (int(signbit(double(fTemp23))) ? fElse5 : fThen5)) + (int(signbit(double(fTemp26))) ? fElse7 : fThen7)) + (int(signbit(double(fTemp28))) ? fElse9 : fThen9)));
		fRec1[1] = fRec1[0];
		fVec0[1] = fVec0[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
			fRec2[j0] = fRec2[(j0 - 1)];
		}
		fRec0[1] = fRec0[0];
		fRec8[1] = fRec8[0];
		fRec16[1] = fRec16[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		fVec1[1] = fVec1[0];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
			fRec10[j1] = fRec10[(j1 - 1)];
		}
		fRec9[1] = fRec9[0];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fVec2[1] = fVec2[0];
		fRec21[1] = fRec21[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		for (int j2 = 3; (j2 > 0); j2 = (j2 - 1)) {
			fRec18[j2] = fRec18[(j2 - 1)];
		}
		fRec17[1] = fRec17[0];
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fVec3[1] = fVec3[0];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		for (int j3 = 3; (j3 > 0); j3 = (j3 - 1)) {
			fRec25[j3] = fRec25[(j3 - 1)];
		}
		fRec24[1] = fRec24[0];
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		for (int j4 = 3; (j4 > 0); j4 = (j4 - 1)) {
			fRec31[j4] = fRec31[(j4 - 1)];
		}
		fRec30[1] = fRec30[0];
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
