// generated from file '../src/LV2/faust/gxechocat.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "copicat1_neg_table.h"
#include "copicat1_table.h"
#include "copicatrecord_2_neg_table.h"
#include "copicatrecord_2_table.h"
#include "copicatreplay1_neg_table.h"
#include "copicatreplay1_table.h"
#include "copicatreplay2_neg_table.h"
#include "copicatreplay2_table.h"
#include "math.h"

namespace gxechocat {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst12;
	double fConst13;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst20;
	double fConst22;
	double fConst23;
	double fConst24;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec8[2];
	double fConst26;
	double fConst28;
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
	double fVec0[2];
	double fConst63;
	double fConst65;
	double fRec17[2];
	double fRec16[3];
	double fVec1[2];
	double fConst66;
	double fConst68;
	double fRec15[2];
	double fRec14[3];
	double fVec2[2];
	double fConst69;
	double fConst71;
	double fRec13[2];
	double fRec12[3];
	double fVec3[2];
	double fConst72;
	double fConst74;
	double fRec11[2];
	double fRec10[3];
	double fRec9[3];
	double fConst76;
	double fConst77;
	double fConst78;
	double fConst82;
	double fConst84;
	double fConst85;
	double fRec19[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec20[2];
	double fVec4[2];
	double fConst86;
	double fConst87;
	double fRec18[2];
	double fRec7[4];
	double fConst89;
	double fConst90;
	double fConst91;
	double fConst92;
	double fRec6[3];
	double fConst93;
	double fRec5[3];
	int IOTA0;
	double *fVec5;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fConst94;
	double fConst95;
	double fConst96;
	double fRec21[2];
	double fRec22[2];
	double fRec23[2];
	double fRec24[2];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst97;
	double fRec25[2];
	double fRec26[2];
	double fRec27[2];
	double fRec28[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	double fConst98;
	double fRec29[2];
	double fRec30[2];
	double fRec31[2];
	double fRec32[2];
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT	*fCheckbox2_;
	double fVec6[2];
	double fConst100;
	double fConst101;
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fConst103;
	double fConst104;
	double fConst105;
	double fRec1[3];
	double fConst107;
	double fConst108;
	double fConst109;
	double fRec0[3];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec33[2];
	double fConst110;
	double fConst111;
	double fConst112;
	double fRec44[2];
	double fRec43[3];
	double fConst113;
	double fRec42[3];
	double fRec46[2];
	double fVec7[2];
	double fRec45[2];
	double fRec41[4];
	double fRec40[3];
	double fRec39[3];
	double *fVec8;
	double fVec9[2];
	double fRec38[2];
	double fRec37[2];
	double fRec36[3];
	double fRec35[3];
	double fRec34[3];
	double fConst114;
	double fConst115;
	double fConst116;
	double fConst117;
	double fConst118;
	double fRec58[2];
	double fRec57[3];
	double fConst119;
	double fRec56[3];
	double fRec55[3];
	double fRec60[2];
	double fVec10[2];
	double fRec59[2];
	double fRec54[4];
	double fRec53[3];
	double fRec52[3];
	double *fVec11;
	double fVec12[2];
	double fRec51[2];
	double fRec50[2];
	double fRec49[3];
	double fRec48[3];
	double fRec47[3];
	double fConst120;
	double fConst121;
	double fConst122;
	double fConst123;
	double fConst124;
	double fRec73[2];
	double fRec72[3];
	double fConst125;
	double fRec71[3];
	double fRec70[3];
	double fRec69[3];
	double fRec75[2];
	double fVec13[2];
	double fRec74[2];
	double fRec68[4];
	double fRec67[3];
	double fRec66[3];
	double *fVec14;
	double fVec15[2];
	double fRec65[2];
	double fRec64[2];
	double fRec63[3];
	double fRec62[3];
	double fRec61[3];
	double fConst126;
	double fConst127;
	double fConst128;
	double fRec89[2];
	double fRec88[3];
	double fConst129;
	double fRec87[3];
	double fRec86[3];
	double fRec85[3];
	double fRec84[3];
	double fRec91[2];
	double fVec16[2];
	double fRec90[2];
	double fRec83[4];
	double fRec82[3];
	double fRec81[3];
	double *fVec17;
	double fVec18[2];
	double fRec80[2];
	double fRec79[2];
	double fRec78[3];
	double fRec77[3];
	double fRec76[3];
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	double fRec92[2];

	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void connect(uint32_t port,void* data);
	void clear_state_f();
	int activate(bool start);
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static int activate_static(bool start, PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2(),
	  fVec5(0),
	  fVec8(0),
	  fVec11(0),
	  fVec14(0),
	  fVec17(0),
	  mem_allocated(false) {
	version = PLUGINLV2_VERSION;
	id = "gxechocat";
	name = N_("Tape Delay");
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = activate_static;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec8[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fVec0[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec17[l2] = 0.0;
	for (int l3 = 0; l3 < 3; l3 = l3 + 1) fRec16[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fVec1[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec15[l5] = 0.0;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec14[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fVec2[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec13[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec12[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fVec3[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec11[l11] = 0.0;
	for (int l12 = 0; l12 < 3; l12 = l12 + 1) fRec10[l12] = 0.0;
	for (int l13 = 0; l13 < 3; l13 = l13 + 1) fRec9[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec19[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec20[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fVec4[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec18[l17] = 0.0;
	for (int l18 = 0; l18 < 4; l18 = l18 + 1) fRec7[l18] = 0.0;
	for (int l19 = 0; l19 < 3; l19 = l19 + 1) fRec6[l19] = 0.0;
	for (int l20 = 0; l20 < 3; l20 = l20 + 1) fRec5[l20] = 0.0;
	for (int l21 = 0; l21 < 1048576; l21 = l21 + 1) fVec5[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec21[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec22[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec23[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec24[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec25[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec26[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec27[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec28[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec29[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec30[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fRec31[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fRec32[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fVec6[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec4[l35] = 0.0;
	for (int l36 = 0; l36 < 2; l36 = l36 + 1) fRec3[l36] = 0.0;
	for (int l37 = 0; l37 < 3; l37 = l37 + 1) fRec2[l37] = 0.0;
	for (int l38 = 0; l38 < 3; l38 = l38 + 1) fRec1[l38] = 0.0;
	for (int l39 = 0; l39 < 3; l39 = l39 + 1) fRec0[l39] = 0.0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec33[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec44[l41] = 0.0;
	for (int l42 = 0; l42 < 3; l42 = l42 + 1) fRec43[l42] = 0.0;
	for (int l43 = 0; l43 < 3; l43 = l43 + 1) fRec42[l43] = 0.0;
	for (int l44 = 0; l44 < 2; l44 = l44 + 1) fRec46[l44] = 0.0;
	for (int l45 = 0; l45 < 2; l45 = l45 + 1) fVec7[l45] = 0.0;
	for (int l46 = 0; l46 < 2; l46 = l46 + 1) fRec45[l46] = 0.0;
	for (int l47 = 0; l47 < 4; l47 = l47 + 1) fRec41[l47] = 0.0;
	for (int l48 = 0; l48 < 3; l48 = l48 + 1) fRec40[l48] = 0.0;
	for (int l49 = 0; l49 < 3; l49 = l49 + 1) fRec39[l49] = 0.0;
	for (int l50 = 0; l50 < 1048576; l50 = l50 + 1) fVec8[l50] = 0.0;
	for (int l51 = 0; l51 < 2; l51 = l51 + 1) fVec9[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fRec38[l52] = 0.0;
	for (int l53 = 0; l53 < 2; l53 = l53 + 1) fRec37[l53] = 0.0;
	for (int l54 = 0; l54 < 3; l54 = l54 + 1) fRec36[l54] = 0.0;
	for (int l55 = 0; l55 < 3; l55 = l55 + 1) fRec35[l55] = 0.0;
	for (int l56 = 0; l56 < 3; l56 = l56 + 1) fRec34[l56] = 0.0;
	for (int l57 = 0; l57 < 2; l57 = l57 + 1) fRec58[l57] = 0.0;
	for (int l58 = 0; l58 < 3; l58 = l58 + 1) fRec57[l58] = 0.0;
	for (int l59 = 0; l59 < 3; l59 = l59 + 1) fRec56[l59] = 0.0;
	for (int l60 = 0; l60 < 3; l60 = l60 + 1) fRec55[l60] = 0.0;
	for (int l61 = 0; l61 < 2; l61 = l61 + 1) fRec60[l61] = 0.0;
	for (int l62 = 0; l62 < 2; l62 = l62 + 1) fVec10[l62] = 0.0;
	for (int l63 = 0; l63 < 2; l63 = l63 + 1) fRec59[l63] = 0.0;
	for (int l64 = 0; l64 < 4; l64 = l64 + 1) fRec54[l64] = 0.0;
	for (int l65 = 0; l65 < 3; l65 = l65 + 1) fRec53[l65] = 0.0;
	for (int l66 = 0; l66 < 3; l66 = l66 + 1) fRec52[l66] = 0.0;
	for (int l67 = 0; l67 < 1048576; l67 = l67 + 1) fVec11[l67] = 0.0;
	for (int l68 = 0; l68 < 2; l68 = l68 + 1) fVec12[l68] = 0.0;
	for (int l69 = 0; l69 < 2; l69 = l69 + 1) fRec51[l69] = 0.0;
	for (int l70 = 0; l70 < 2; l70 = l70 + 1) fRec50[l70] = 0.0;
	for (int l71 = 0; l71 < 3; l71 = l71 + 1) fRec49[l71] = 0.0;
	for (int l72 = 0; l72 < 3; l72 = l72 + 1) fRec48[l72] = 0.0;
	for (int l73 = 0; l73 < 3; l73 = l73 + 1) fRec47[l73] = 0.0;
	for (int l74 = 0; l74 < 2; l74 = l74 + 1) fRec73[l74] = 0.0;
	for (int l75 = 0; l75 < 3; l75 = l75 + 1) fRec72[l75] = 0.0;
	for (int l76 = 0; l76 < 3; l76 = l76 + 1) fRec71[l76] = 0.0;
	for (int l77 = 0; l77 < 3; l77 = l77 + 1) fRec70[l77] = 0.0;
	for (int l78 = 0; l78 < 3; l78 = l78 + 1) fRec69[l78] = 0.0;
	for (int l79 = 0; l79 < 2; l79 = l79 + 1) fRec75[l79] = 0.0;
	for (int l80 = 0; l80 < 2; l80 = l80 + 1) fVec13[l80] = 0.0;
	for (int l81 = 0; l81 < 2; l81 = l81 + 1) fRec74[l81] = 0.0;
	for (int l82 = 0; l82 < 4; l82 = l82 + 1) fRec68[l82] = 0.0;
	for (int l83 = 0; l83 < 3; l83 = l83 + 1) fRec67[l83] = 0.0;
	for (int l84 = 0; l84 < 3; l84 = l84 + 1) fRec66[l84] = 0.0;
	for (int l85 = 0; l85 < 1048576; l85 = l85 + 1) fVec14[l85] = 0.0;
	for (int l86 = 0; l86 < 2; l86 = l86 + 1) fVec15[l86] = 0.0;
	for (int l87 = 0; l87 < 2; l87 = l87 + 1) fRec65[l87] = 0.0;
	for (int l88 = 0; l88 < 2; l88 = l88 + 1) fRec64[l88] = 0.0;
	for (int l89 = 0; l89 < 3; l89 = l89 + 1) fRec63[l89] = 0.0;
	for (int l90 = 0; l90 < 3; l90 = l90 + 1) fRec62[l90] = 0.0;
	for (int l91 = 0; l91 < 3; l91 = l91 + 1) fRec61[l91] = 0.0;
	for (int l92 = 0; l92 < 2; l92 = l92 + 1) fRec89[l92] = 0.0;
	for (int l93 = 0; l93 < 3; l93 = l93 + 1) fRec88[l93] = 0.0;
	for (int l94 = 0; l94 < 3; l94 = l94 + 1) fRec87[l94] = 0.0;
	for (int l95 = 0; l95 < 3; l95 = l95 + 1) fRec86[l95] = 0.0;
	for (int l96 = 0; l96 < 3; l96 = l96 + 1) fRec85[l96] = 0.0;
	for (int l97 = 0; l97 < 3; l97 = l97 + 1) fRec84[l97] = 0.0;
	for (int l98 = 0; l98 < 2; l98 = l98 + 1) fRec91[l98] = 0.0;
	for (int l99 = 0; l99 < 2; l99 = l99 + 1) fVec16[l99] = 0.0;
	for (int l100 = 0; l100 < 2; l100 = l100 + 1) fRec90[l100] = 0.0;
	for (int l101 = 0; l101 < 4; l101 = l101 + 1) fRec83[l101] = 0.0;
	for (int l102 = 0; l102 < 3; l102 = l102 + 1) fRec82[l102] = 0.0;
	for (int l103 = 0; l103 < 3; l103 = l103 + 1) fRec81[l103] = 0.0;
	for (int l104 = 0; l104 < 1048576; l104 = l104 + 1) fVec17[l104] = 0.0;
	for (int l105 = 0; l105 < 2; l105 = l105 + 1) fVec18[l105] = 0.0;
	for (int l106 = 0; l106 < 2; l106 = l106 + 1) fRec80[l106] = 0.0;
	for (int l107 = 0; l107 < 2; l107 = l107 + 1) fRec79[l107] = 0.0;
	for (int l108 = 0; l108 < 3; l108 = l108 + 1) fRec78[l108] = 0.0;
	for (int l109 = 0; l109 < 3; l109 = l109 + 1) fRec77[l109] = 0.0;
	for (int l110 = 0; l110 < 3; l110 = l110 + 1) fRec76[l110] = 0.0;
	for (int l111 = 0; l111 < 2; l111 = l111 + 1) fRec92[l111] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 4.3361242466424e-10 * fConst0;
	fConst2 = fConst0 * (fConst1 + -1.99329936161353e-08) + 1.89880017035189e-07;
	fConst3 = mydsp_faustpower2_f(fConst0);
	fConst4 = 3.79760034070379e-07 - 8.6722484932848e-10 * fConst3;
	fConst5 = 1.0 / (fConst0 * (fConst1 + 1.99329936161353e-08) + 1.89880017035189e-07);
	double fConst6 = 4.33785780482415e-10 * fConst0;
	fConst7 = fConst0 * (fConst6 + -1.16144315716444e-08) + 6.90530766455131e-08;
	fConst8 = 1.38106153291026e-07 - 8.6757156096483e-10 * fConst3;
	fConst9 = 1.0 / (fConst0 * (fConst6 + 1.16144315716444e-08) + 6.90530766455131e-08);
	double fConst10 = std::tan(125.66370614359172 / fConst0);
	double fConst11 = mydsp_faustpower2_f(fConst10);
	fConst12 = 1.0 / fConst11;
	fConst13 = 2.0 * (1.0 - fConst12);
	double fConst14 = 1.0 / fConst10;
	fConst15 = (fConst14 + -0.7653668647301795) / fConst10 + 1.0;
	fConst16 = 1.0 / ((fConst14 + 0.7653668647301795) / fConst10 + 1.0);
	fConst17 = (fConst14 + -1.8477590650225735) / fConst10 + 1.0;
	fConst18 = 1.0 / ((fConst14 + 1.8477590650225735) / fConst10 + 1.0);
	double fConst19 = 6.73029102377671e-15 * fConst0;
	fConst20 = fConst0 * (fConst0 * (1.10493997854221e-10 - fConst19) + -2.30183843147656e-08) + 6.01595252726883e-07;
	double fConst21 = 2.01908730713301e-14 * fConst0;
	fConst22 = fConst0 * (fConst0 * (fConst21 + -1.10493997854221e-10) + -2.30183843147656e-08) + 1.80478575818065e-06;
	fConst23 = fConst0 * (fConst0 * (-1.10493997854221e-10 - fConst21) + 2.30183843147656e-08) + 1.80478575818065e-06;
	fConst24 = 1.0 / (fConst0 * (fConst0 * (fConst19 + 1.10493997854221e-10) + 2.30183843147656e-08) + 6.01595252726883e-07);
	double fConst25 = 7.83789728824443e-11 * fConst0;
	fConst26 = -3.13458049067171e-09 - fConst25;
	double fConst27 = 8.32844278169955e-11 * fConst0;
	fConst28 = fConst27 + 5.0418669893366e-09;
	double fConst29 = 4.11425073415965e-10 * fConst0;
	fConst30 = fConst0 * (fConst29 + 2.49068229273233e-08);
	fConst31 = 3.13458049067171e-09 - fConst25;
	fConst32 = fConst27 + -5.0418669893366e-09;
	fConst33 = fConst0 * (fConst29 + -2.49068229273233e-08);
	fConst34 = 8.22850146831931e-10 * fConst3;
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
	double fConst75 = 2.06740841499587e-08 * fConst0;
	fConst76 = fConst0 * (5.51308910665569e-07 - fConst75);
	fConst77 = 4.13481682999174e-08 * fConst3;
	fConst78 = fConst0 * (-5.51308910665569e-07 - fConst75);
	double fConst79 = std::tan(471.23889803846896 / fConst0);
	double fConst80 = 1.0 / fConst79;
	double fConst81 = fConst80 + 1.0;
	fConst82 = (1.0 - fConst80) / fConst81;
	double fConst83 = 1.0 / std::tan(23561.94490192345 / fConst0);
	fConst84 = 1.0 - fConst83;
	fConst85 = 1.0 / (fConst83 + 1.0);
	fConst86 = 1.0 / (fConst79 * fConst81);
	fConst87 = 0.0 - fConst86;
	double fConst88 = 1.23938408071082e-08 * fConst0;
	fConst89 = fConst0 * (7.13052376187718e-07 - fConst88) + -9.98795811595446e-06;
	fConst90 = fConst0 * (fConst88 + 7.13052376187718e-07) + -2.99638743478634e-05;
	fConst91 = fConst0 * (fConst88 + -7.13052376187718e-07) + -2.99638743478634e-05;
	fConst92 = fConst0 * (-7.13052376187718e-07 - fConst88) + -9.98795811595446e-06;
	fConst93 = 0.0 - 2.0 / fConst11;
	fConst94 = 9e+01 * fConst0;
	fConst95 = 1e+01 / fConst0;
	fConst96 = 0.0 - fConst95;
	fConst97 = 6e+01 * fConst0;
	fConst98 = 3e+01 * fConst0;
	double fConst99 = 1.0 / std::tan(20420.352248333656 / fConst0);
	fConst100 = 1.0 - fConst99;
	fConst101 = 1.0 / (fConst99 + 1.0);
	double fConst102 = 2.16461324600193e-08 * fConst0;
	fConst103 = fConst0 * (1.31188681575873e-07 - fConst102);
	fConst104 = 4.32922649200386e-08 * fConst3;
	fConst105 = fConst0 * (-1.31188681575873e-07 - fConst102);
	double fConst106 = 1.02325156488485e-09 * fConst0;
	fConst107 = fConst0 * (1.05707806289759e-08 - fConst106);
	fConst108 = 2.0465031297697e-09 * fConst3;
	fConst109 = fConst0 * (-1.05707806289759e-08 - fConst106);
	fConst110 = fConst72 / fConst73;
	fConst111 = 1.0 / (fConst35 * fConst73);
	fConst112 = 0.0 - fConst111;
	fConst113 = 0.0 - 2.0 / fConst36;
	fConst114 = 1.0 - fConst72 / fConst35;
	fConst115 = 1.0 / (fConst73 / fConst35 + 1.0);
	fConst116 = fConst69 / fConst70;
	fConst117 = 1.0 / (fConst42 * fConst70);
	fConst118 = 0.0 - fConst117;
	fConst119 = 0.0 - 2.0 / fConst43;
	fConst120 = 1.0 - fConst69 / fConst42;
	fConst121 = 1.0 / (fConst70 / fConst42 + 1.0);
	fConst122 = fConst66 / fConst67;
	fConst123 = 1.0 / (fConst49 * fConst67);
	fConst124 = 0.0 - fConst123;
	fConst125 = 0.0 - 2.0 / fConst50;
	fConst126 = 1.0 - fConst66 / fConst49;
	fConst127 = 1.0 / (fConst67 / fConst49 + 1.0);
	fConst128 = 0.0 - 1.0 / (fConst56 * fConst64);
	fConst129 = 0.0 - 2.0 / fConst57;
	IOTA0 = 0;
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void Dsp::mem_alloc()
{
	if (!fVec5) fVec5 = new double[1048576];
	if (!fVec8) fVec8 = new double[1048576];
	if (!fVec11) fVec11 = new double[1048576];
	if (!fVec14) fVec14 = new double[1048576];
	if (!fVec17) fVec17 = new double[1048576];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec5) { delete fVec5; fVec5 = 0; }
	if (fVec8) { delete fVec8; fVec8 = 0; }
	if (fVec11) { delete fVec11; fVec11 = 0; }
	if (fVec14) { delete fVec14; fVec14 = 0; }
	if (fVec17) { delete fVec17; fVec17 = 0; }
}

int Dsp::activate(bool start)
{
	if (start) {
		if (!mem_allocated) {
			mem_alloc();
			clear_state_f();
		}
	} else if (mem_allocated) {
		mem_free();
	}
	return 0;
}

int Dsp::activate_static(bool start, PluginLV2 *p)
{
	return static_cast<Dsp*>(p)->activate(start);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fCheckbox0 (*fCheckbox0_)
#define fCheckbox1 (*fCheckbox1_)
#define fCheckbox2 (*fCheckbox2_)
#define fVslider3 (*fVslider3_)
#define fVslider4 (*fVslider4_)
	double fSlow0 = 0.007000000000000006 * double(fVslider0);
	double fSlow1 = 0.004073836948085289 * (std::exp(double(fVslider1)) + -1.0);
	double fSlow2 = double(fVslider2);
	double fSlow3 = fConst94 / fSlow2;
	double fSlow4 = double(fCheckbox0);
	double fSlow5 = fConst97 / fSlow2;
	double fSlow6 = double(fCheckbox1);
	double fSlow7 = fConst98 / fSlow2;
	double fSlow8 = double(fCheckbox2);
	double fSlow9 = 0.004073836948085289 * (std::exp(double(fVslider3)) + -1.0);
	double fSlow10 = 0.00036676987543879196 * (std::exp(3.0 * double(fVslider4)) + -1.0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec8[0] = fSlow0 + 0.993 * fRec8[1];
		double fTemp0 = fConst30 + fRec8[0] * (fConst0 * (fConst28 + fConst26 * fRec8[0]) + 6.26916098134342e-08) + 3.09696552478371e-07;
		double fTemp1 = fConst33 + fRec8[0] * (fConst0 * (fConst32 + fConst31 * fRec8[0]) + 6.26916098134342e-08) + 3.09696552478371e-07;
		double fTemp2 = fRec8[0] * (fConst3 * (1.56757945764889e-10 * fRec8[0] + -1.66568855633991e-10) + 1.25383219626868e-07) + 6.19393104956741e-07 - fConst34;
		double fTemp3 = double(input0[i0]);
		fVec0[0] = fTemp3;
		fRec17[0] = 0.0 - fConst65 * (fConst63 * fRec17[1] - (fTemp3 + fVec0[1]));
		fRec16[0] = fRec17[0] - fConst62 * (fConst61 * fRec16[2] + fConst59 * fRec16[1]);
		double fTemp4 = fRec16[2] + fRec16[0] + 2.0 * fRec16[1];
		fVec1[0] = fTemp4;
		fRec15[0] = 0.0 - fConst68 * (fConst66 * fRec15[1] - fConst62 * (fTemp4 + fVec1[1]));
		fRec14[0] = fRec15[0] - fConst55 * (fConst54 * fRec14[2] + fConst52 * fRec14[1]);
		double fTemp5 = fRec14[2] + fRec14[0] + 2.0 * fRec14[1];
		fVec2[0] = fTemp5;
		fRec13[0] = 0.0 - fConst71 * (fConst69 * fRec13[1] - fConst55 * (fTemp5 + fVec2[1]));
		fRec12[0] = fRec13[0] - fConst48 * (fConst47 * fRec12[2] + fConst45 * fRec12[1]);
		double fTemp6 = fRec12[2] + fRec12[0] + 2.0 * fRec12[1];
		fVec3[0] = fTemp6;
		fRec11[0] = 0.0 - fConst74 * (fConst72 * fRec11[1] - fConst48 * (fTemp6 + fVec3[1]));
		fRec10[0] = fRec11[0] - fConst41 * (fConst40 * fRec10[2] + fConst38 * fRec10[1]);
		fRec9[0] = fConst41 * (fRec10[2] + fRec10[0] + 2.0 * fRec10[1]) - (fTemp2 * fRec9[1] + fTemp1 * fRec9[2]) / fTemp0;
		double fTemp7 = fRec8[0] * (fConst78 * fRec9[0] + fConst77 * fRec9[1] + fConst76 * fRec9[2]) / fTemp0;
		double fTemp8 = ((signbit(fTemp7)) ? copicat1_negclip(fTemp7) : copicat1clip(fTemp7));
		fRec19[0] = 0.0 - fConst85 * (fConst84 * fRec19[1] - (fRec0[1] + fRec0[2]));
		fRec20[0] = fSlow1 + 0.993 * fRec20[1];
		double fTemp9 = fRec20[0] * fRec19[0];
		fVec4[0] = fTemp9;
		fRec18[0] = 0.25 * (fConst86 * fTemp9 + fConst87 * fVec4[1]) - fConst82 * fRec18[1];
		fRec7[0] = fRec18[0] + fTemp8 - fConst24 * (fConst23 * fRec7[1] + fConst22 * fRec7[2] + fConst20 * fRec7[3]);
		double fTemp10 = fConst24 * (fConst92 * fRec7[0] + fConst91 * fRec7[1] + fConst90 * fRec7[2] + fConst89 * fRec7[3]);
		fRec6[0] = ((signbit(fTemp10)) ? copicatrecord_2_negclip(fTemp10) : copicatrecord_2clip(fTemp10)) - fConst18 * (fConst17 * fRec6[2] + fConst13 * fRec6[1]);
		fRec5[0] = fConst18 * (fConst12 * fRec6[0] + fConst93 * fRec6[1] + fConst12 * fRec6[2]) - fConst16 * (fConst15 * fRec5[2] + fConst13 * fRec5[1]);
		double fTemp11 = fConst12 * fRec5[0] + fConst93 * fRec5[1] + fConst12 * fRec5[2];
		fVec5[IOTA0 & 1048575] = fTemp11;
		double fTemp12 = ((fRec21[1] != 0.0) ? (((fRec22[1] > 0.0) & (fRec22[1] < 1.0)) ? fRec21[1] : 0.0) : (((fRec22[1] == 0.0) & (fSlow3 != fRec23[1])) ? fConst95 : (((fRec22[1] == 1.0) & (fSlow3 != fRec24[1])) ? fConst96 : 0.0)));
		fRec21[0] = fTemp12;
		fRec22[0] = std::max<double>(0.0, std::min<double>(1.0, fRec22[1] + fTemp12));
		fRec23[0] = (((fRec22[1] >= 1.0) & (fRec24[1] != fSlow3)) ? fSlow3 : fRec23[1]);
		fRec24[0] = (((fRec22[1] <= 0.0) & (fRec23[1] != fSlow3)) ? fSlow3 : fRec24[1]);
		int iTemp13 = int(std::min<double>(524288.0, std::max<double>(0.0, fRec24[0])));
		int iTemp14 = int(std::min<double>(524288.0, std::max<double>(0.0, fRec23[0])));
		double fTemp15 = fVec5[(IOTA0 - iTemp14) & 1048575];
		double fTemp16 = ((fRec25[1] != 0.0) ? (((fRec26[1] > 0.0) & (fRec26[1] < 1.0)) ? fRec25[1] : 0.0) : (((fRec26[1] == 0.0) & (fSlow5 != fRec27[1])) ? fConst95 : (((fRec26[1] == 1.0) & (fSlow5 != fRec28[1])) ? fConst96 : 0.0)));
		fRec25[0] = fTemp16;
		fRec26[0] = std::max<double>(0.0, std::min<double>(1.0, fRec26[1] + fTemp16));
		fRec27[0] = (((fRec26[1] >= 1.0) & (fRec28[1] != fSlow5)) ? fSlow5 : fRec27[1]);
		fRec28[0] = (((fRec26[1] <= 0.0) & (fRec27[1] != fSlow5)) ? fSlow5 : fRec28[1]);
		int iTemp17 = int(std::min<double>(524288.0, std::max<double>(0.0, fRec28[0])));
		int iTemp18 = int(std::min<double>(524288.0, std::max<double>(0.0, fRec27[0])));
		double fTemp19 = fVec5[(IOTA0 - iTemp18) & 1048575];
		double fTemp20 = ((fRec29[1] != 0.0) ? (((fRec30[1] > 0.0) & (fRec30[1] < 1.0)) ? fRec29[1] : 0.0) : (((fRec30[1] == 0.0) & (fSlow7 != fRec31[1])) ? fConst95 : (((fRec30[1] == 1.0) & (fSlow7 != fRec32[1])) ? fConst96 : 0.0)));
		fRec29[0] = fTemp20;
		fRec30[0] = std::max<double>(0.0, std::min<double>(1.0, fRec30[1] + fTemp20));
		fRec31[0] = (((fRec30[1] >= 1.0) & (fRec32[1] != fSlow7)) ? fSlow7 : fRec31[1]);
		fRec32[0] = (((fRec30[1] <= 0.0) & (fRec31[1] != fSlow7)) ? fSlow7 : fRec32[1]);
		int iTemp21 = int(std::min<double>(524288.0, std::max<double>(0.0, fRec32[0])));
		int iTemp22 = int(std::min<double>(524288.0, std::max<double>(0.0, fRec31[0])));
		double fTemp23 = fVec5[(IOTA0 - iTemp22) & 1048575];
		double fTemp24 = fSlow8 * (fConst16 * fTemp23 + fRec30[0] * (0.0 - fConst16 * (fTemp23 - fVec5[(IOTA0 - iTemp21) & 1048575]))) + fSlow6 * (fConst16 * fTemp19 + fRec26[0] * (0.0 - fConst16 * (fTemp19 - fVec5[(IOTA0 - iTemp17) & 1048575]))) + fSlow4 * (fConst16 * fTemp15 + fRec22[0] * (0.0 - fConst16 * (fTemp15 - fVec5[(IOTA0 - iTemp13) & 1048575])));
		fVec6[0] = fTemp24;
		fRec4[0] = 0.0 - fConst101 * (fConst100 * fRec4[1] - (fTemp24 + fVec6[1]));
		fRec3[0] = fRec4[0] + 0.995 * fRec3[1] - fRec4[1];
		fRec2[0] = fRec3[0] - fConst9 * (fConst8 * fRec2[1] + fConst7 * fRec2[2]);
		double fTemp25 = fConst9 * (fConst105 * fRec2[0] + fConst104 * fRec2[1] + fConst103 * fRec2[2]);
		fRec1[0] = ((signbit(fTemp25)) ? copicatreplay1_negclip(fTemp25) : copicatreplay1clip(fTemp25)) - fConst5 * (fConst4 * fRec1[1] + fConst2 * fRec1[2]);
		double fTemp26 = fConst5 * (fConst109 * fRec1[0] + fConst108 * fRec1[1] + fConst107 * fRec1[2]);
		fRec0[0] = ((signbit(fTemp26)) ? copicatreplay2_negclip(fTemp26) : copicatreplay2clip(fTemp26));
		fRec33[0] = fSlow9 + 0.993 * fRec33[1];
		fRec44[0] = fConst48 * (fConst111 * fTemp6 + fConst112 * fVec3[1]) - fConst110 * fRec44[1];
		fRec43[0] = fRec44[0] - fConst41 * (fConst40 * fRec43[2] + fConst38 * fRec43[1]);
		fRec42[0] = fConst41 * (fConst37 * fRec43[0] + fConst113 * fRec43[1] + fConst37 * fRec43[2]) - (fTemp2 * fRec42[1] + fTemp1 * fRec42[2]) / fTemp0;
		double fTemp27 = fRec8[0] * (fConst78 * fRec42[0] + fConst77 * fRec42[1] + fConst76 * fRec42[2]) / fTemp0;
		double fTemp28 = ((signbit(fTemp27)) ? copicat1_negclip(fTemp27) : copicat1clip(fTemp27));
		fRec46[0] = 0.0 - fConst85 * (fConst84 * fRec46[1] - (fRec34[1] + fRec34[2]));
		double fTemp29 = fRec20[0] * fRec46[0];
		fVec7[0] = fTemp29;
		fRec45[0] = 0.25 * (fConst86 * fTemp29 + fConst87 * fVec7[1]) - fConst82 * fRec45[1];
		fRec41[0] = fRec45[0] + fTemp28 - fConst24 * (fConst23 * fRec41[1] + fConst22 * fRec41[2] + fConst20 * fRec41[3]);
		double fTemp30 = fConst24 * (fConst92 * fRec41[0] + fConst91 * fRec41[1] + fConst90 * fRec41[2] + fConst89 * fRec41[3]);
		fRec40[0] = ((signbit(fTemp30)) ? copicatrecord_2_negclip(fTemp30) : copicatrecord_2clip(fTemp30)) - fConst18 * (fConst17 * fRec40[2] + fConst13 * fRec40[1]);
		fRec39[0] = fConst18 * (fConst12 * fRec40[0] + fConst93 * fRec40[1] + fConst12 * fRec40[2]) - fConst16 * (fConst15 * fRec39[2] + fConst13 * fRec39[1]);
		double fTemp31 = fConst12 * fRec39[0] + fConst93 * fRec39[1] + fConst12 * fRec39[2];
		fVec8[IOTA0 & 1048575] = fTemp31;
		double fTemp32 = fVec8[(IOTA0 - iTemp14) & 1048575];
		double fTemp33 = fVec8[(IOTA0 - iTemp18) & 1048575];
		double fTemp34 = fVec8[(IOTA0 - iTemp22) & 1048575];
		double fTemp35 = fSlow8 * (fConst16 * fTemp34 + fRec30[0] * (0.0 - fConst16 * (fTemp34 - fVec8[(IOTA0 - iTemp21) & 1048575]))) + fSlow6 * (fConst16 * fTemp33 + fRec26[0] * (0.0 - fConst16 * (fTemp33 - fVec8[(IOTA0 - iTemp17) & 1048575]))) + fSlow4 * (fConst16 * fTemp32 + fRec22[0] * (0.0 - fConst16 * (fTemp32 - fVec8[(IOTA0 - iTemp13) & 1048575])));
		fVec9[0] = fTemp35;
		fRec38[0] = 0.0 - fConst101 * (fConst100 * fRec38[1] - (fTemp35 + fVec9[1]));
		fRec37[0] = fRec38[0] + 0.995 * fRec37[1] - fRec38[1];
		fRec36[0] = fRec37[0] - fConst9 * (fConst8 * fRec36[1] + fConst7 * fRec36[2]);
		double fTemp36 = fConst9 * (fConst105 * fRec36[0] + fConst104 * fRec36[1] + fConst103 * fRec36[2]);
		fRec35[0] = ((signbit(fTemp36)) ? copicatreplay1_negclip(fTemp36) : copicatreplay1clip(fTemp36)) - fConst5 * (fConst4 * fRec35[1] + fConst2 * fRec35[2]);
		double fTemp37 = fConst5 * (fConst109 * fRec35[0] + fConst108 * fRec35[1] + fConst107 * fRec35[2]);
		fRec34[0] = ((signbit(fTemp37)) ? copicatreplay2_negclip(fTemp37) : copicatreplay2clip(fTemp37));
		double fTemp38 = fConst38 * fRec56[1];
		fRec58[0] = fConst55 * (fConst117 * fTemp5 + fConst118 * fVec2[1]) - fConst116 * fRec58[1];
		fRec57[0] = fRec58[0] - fConst48 * (fConst47 * fRec57[2] + fConst45 * fRec57[1]);
		fRec56[0] = fConst48 * (fConst44 * fRec57[0] + fConst119 * fRec57[1] + fConst44 * fRec57[2]) - fConst115 * (fConst114 * fRec56[2] + fTemp38);
		fRec55[0] = fRec56[2] + fConst115 * (fTemp38 + fConst114 * fRec56[0]) - (fTemp2 * fRec55[1] + fTemp1 * fRec55[2]) / fTemp0;
		double fTemp39 = fRec8[0] * (fConst78 * fRec55[0] + fConst77 * fRec55[1] + fConst76 * fRec55[2]) / fTemp0;
		double fTemp40 = ((signbit(fTemp39)) ? copicat1_negclip(fTemp39) : copicat1clip(fTemp39));
		fRec60[0] = 0.0 - fConst85 * (fConst84 * fRec60[1] - (fRec47[1] + fRec47[2]));
		double fTemp41 = fRec20[0] * fRec60[0];
		fVec10[0] = fTemp41;
		fRec59[0] = 0.25 * (fConst86 * fTemp41 + fConst87 * fVec10[1]) - fConst82 * fRec59[1];
		fRec54[0] = fRec59[0] + fTemp40 - fConst24 * (fConst23 * fRec54[1] + fConst22 * fRec54[2] + fConst20 * fRec54[3]);
		double fTemp42 = fConst24 * (fConst92 * fRec54[0] + fConst91 * fRec54[1] + fConst90 * fRec54[2] + fConst89 * fRec54[3]);
		fRec53[0] = ((signbit(fTemp42)) ? copicatrecord_2_negclip(fTemp42) : copicatrecord_2clip(fTemp42)) - fConst18 * (fConst17 * fRec53[2] + fConst13 * fRec53[1]);
		fRec52[0] = fConst18 * (fConst12 * fRec53[0] + fConst93 * fRec53[1] + fConst12 * fRec53[2]) - fConst16 * (fConst15 * fRec52[2] + fConst13 * fRec52[1]);
		double fTemp43 = fConst12 * fRec52[0] + fConst93 * fRec52[1] + fConst12 * fRec52[2];
		fVec11[IOTA0 & 1048575] = fTemp43;
		double fTemp44 = fVec11[(IOTA0 - iTemp14) & 1048575];
		double fTemp45 = fVec11[(IOTA0 - iTemp18) & 1048575];
		double fTemp46 = fVec11[(IOTA0 - iTemp22) & 1048575];
		double fTemp47 = fSlow8 * (fConst16 * fTemp46 + fRec30[0] * (0.0 - fConst16 * (fTemp46 - fVec11[(IOTA0 - iTemp21) & 1048575]))) + fSlow6 * (fConst16 * fTemp45 + fRec26[0] * (0.0 - fConst16 * (fTemp45 - fVec11[(IOTA0 - iTemp17) & 1048575]))) + fSlow4 * (fConst16 * fTemp44 + fRec22[0] * (0.0 - fConst16 * (fTemp44 - fVec11[(IOTA0 - iTemp13) & 1048575])));
		fVec12[0] = fTemp47;
		fRec51[0] = 0.0 - fConst101 * (fConst100 * fRec51[1] - (fTemp47 + fVec12[1]));
		fRec50[0] = fRec51[0] + 0.995 * fRec50[1] - fRec51[1];
		fRec49[0] = fRec50[0] - fConst9 * (fConst8 * fRec49[1] + fConst7 * fRec49[2]);
		double fTemp48 = fConst9 * (fConst105 * fRec49[0] + fConst104 * fRec49[1] + fConst103 * fRec49[2]);
		fRec48[0] = ((signbit(fTemp48)) ? copicatreplay1_negclip(fTemp48) : copicatreplay1clip(fTemp48)) - fConst5 * (fConst4 * fRec48[1] + fConst2 * fRec48[2]);
		double fTemp49 = fConst5 * (fConst109 * fRec48[0] + fConst108 * fRec48[1] + fConst107 * fRec48[2]);
		fRec47[0] = ((signbit(fTemp49)) ? copicatreplay2_negclip(fTemp49) : copicatreplay2clip(fTemp49));
		double fTemp50 = fConst38 * fRec70[1];
		double fTemp51 = fConst45 * fRec71[1];
		fRec73[0] = fConst62 * (fConst123 * fTemp4 + fConst124 * fVec1[1]) - fConst122 * fRec73[1];
		fRec72[0] = fRec73[0] - fConst55 * (fConst54 * fRec72[2] + fConst52 * fRec72[1]);
		fRec71[0] = fConst55 * (fConst51 * fRec72[0] + fConst125 * fRec72[1] + fConst51 * fRec72[2]) - fConst121 * (fConst120 * fRec71[2] + fTemp51);
		fRec70[0] = fRec71[2] + fConst121 * (fTemp51 + fConst120 * fRec71[0]) - fConst115 * (fConst114 * fRec70[2] + fTemp50);
		fRec69[0] = fRec70[2] + fConst115 * (fTemp50 + fConst114 * fRec70[0]) - (fTemp2 * fRec69[1] + fTemp1 * fRec69[2]) / fTemp0;
		double fTemp52 = fRec8[0] * (fConst78 * fRec69[0] + fConst77 * fRec69[1] + fConst76 * fRec69[2]) / fTemp0;
		double fTemp53 = ((signbit(fTemp52)) ? copicat1_negclip(fTemp52) : copicat1clip(fTemp52));
		fRec75[0] = 0.0 - fConst85 * (fConst84 * fRec75[1] - (fRec61[1] + fRec61[2]));
		double fTemp54 = fRec20[0] * fRec75[0];
		fVec13[0] = fTemp54;
		fRec74[0] = 0.25 * (fConst86 * fTemp54 + fConst87 * fVec13[1]) - fConst82 * fRec74[1];
		fRec68[0] = fRec74[0] + fTemp53 - fConst24 * (fConst23 * fRec68[1] + fConst22 * fRec68[2] + fConst20 * fRec68[3]);
		double fTemp55 = fConst24 * (fConst92 * fRec68[0] + fConst91 * fRec68[1] + fConst90 * fRec68[2] + fConst89 * fRec68[3]);
		fRec67[0] = ((signbit(fTemp55)) ? copicatrecord_2_negclip(fTemp55) : copicatrecord_2clip(fTemp55)) - fConst18 * (fConst17 * fRec67[2] + fConst13 * fRec67[1]);
		fRec66[0] = fConst18 * (fConst12 * fRec67[0] + fConst93 * fRec67[1] + fConst12 * fRec67[2]) - fConst16 * (fConst15 * fRec66[2] + fConst13 * fRec66[1]);
		double fTemp56 = fConst12 * fRec66[0] + fConst93 * fRec66[1] + fConst12 * fRec66[2];
		fVec14[IOTA0 & 1048575] = fTemp56;
		double fTemp57 = fVec14[(IOTA0 - iTemp14) & 1048575];
		double fTemp58 = fVec14[(IOTA0 - iTemp18) & 1048575];
		double fTemp59 = fVec14[(IOTA0 - iTemp22) & 1048575];
		double fTemp60 = fSlow8 * (fConst16 * fTemp59 + fRec30[0] * (0.0 - fConst16 * (fTemp59 - fVec14[(IOTA0 - iTemp21) & 1048575]))) + fSlow6 * (fConst16 * fTemp58 + fRec26[0] * (0.0 - fConst16 * (fTemp58 - fVec14[(IOTA0 - iTemp17) & 1048575]))) + fSlow4 * (fConst16 * fTemp57 + fRec22[0] * (0.0 - fConst16 * (fTemp57 - fVec14[(IOTA0 - iTemp13) & 1048575])));
		fVec15[0] = fTemp60;
		fRec65[0] = 0.0 - fConst101 * (fConst100 * fRec65[1] - (fTemp60 + fVec15[1]));
		fRec64[0] = fRec65[0] + 0.995 * fRec64[1] - fRec65[1];
		fRec63[0] = fRec64[0] - fConst9 * (fConst8 * fRec63[1] + fConst7 * fRec63[2]);
		double fTemp61 = fConst9 * (fConst105 * fRec63[0] + fConst104 * fRec63[1] + fConst103 * fRec63[2]);
		fRec62[0] = ((signbit(fTemp61)) ? copicatreplay1_negclip(fTemp61) : copicatreplay1clip(fTemp61)) - fConst5 * (fConst4 * fRec62[1] + fConst2 * fRec62[2]);
		double fTemp62 = fConst5 * (fConst109 * fRec62[0] + fConst108 * fRec62[1] + fConst107 * fRec62[2]);
		fRec61[0] = ((signbit(fTemp62)) ? copicatreplay2_negclip(fTemp62) : copicatreplay2clip(fTemp62));
		double fTemp63 = fConst38 * fRec85[1];
		double fTemp64 = fConst45 * fRec86[1];
		double fTemp65 = fConst52 * fRec87[1];
		fRec89[0] = fConst128 * fVec0[1] - fConst65 * (fConst63 * fRec89[1] - fConst60 * fTemp3);
		fRec88[0] = fRec89[0] - fConst62 * (fConst61 * fRec88[2] + fConst59 * fRec88[1]);
		fRec87[0] = fConst62 * (fConst58 * fRec88[0] + fConst129 * fRec88[1] + fConst58 * fRec88[2]) - fConst127 * (fConst126 * fRec87[2] + fTemp65);
		fRec86[0] = fRec87[2] + fConst127 * (fTemp65 + fConst126 * fRec87[0]) - fConst121 * (fConst120 * fRec86[2] + fTemp64);
		fRec85[0] = fRec86[2] + fConst121 * (fTemp64 + fConst120 * fRec86[0]) - fConst115 * (fConst114 * fRec85[2] + fTemp63);
		fRec84[0] = fRec85[2] + fConst115 * (fTemp63 + fConst114 * fRec85[0]) - (fRec84[1] * fTemp2 + fRec84[2] * fTemp1) / fTemp0;
		double fTemp66 = fRec8[0] * (fConst78 * fRec84[0] + fConst77 * fRec84[1] + fConst76 * fRec84[2]) / fTemp0;
		double fTemp67 = ((signbit(fTemp66)) ? copicat1_negclip(fTemp66) : copicat1clip(fTemp66));
		fRec91[0] = 0.0 - fConst85 * (fConst84 * fRec91[1] - (fRec76[1] + fRec76[2]));
		double fTemp68 = fRec91[0] * fRec20[0];
		fVec16[0] = fTemp68;
		fRec90[0] = 0.25 * (fConst86 * fTemp68 + fConst87 * fVec16[1]) - fConst82 * fRec90[1];
		fRec83[0] = fRec90[0] + fTemp67 - fConst24 * (fConst23 * fRec83[1] + fConst22 * fRec83[2] + fConst20 * fRec83[3]);
		double fTemp69 = fConst24 * (fConst92 * fRec83[0] + fConst91 * fRec83[1] + fConst90 * fRec83[2] + fConst89 * fRec83[3]);
		fRec82[0] = ((signbit(fTemp69)) ? copicatrecord_2_negclip(fTemp69) : copicatrecord_2clip(fTemp69)) - fConst18 * (fConst17 * fRec82[2] + fConst13 * fRec82[1]);
		fRec81[0] = fConst18 * (fConst12 * fRec82[0] + fConst93 * fRec82[1] + fConst12 * fRec82[2]) - fConst16 * (fConst15 * fRec81[2] + fConst13 * fRec81[1]);
		double fTemp70 = fConst12 * fRec81[0] + fConst93 * fRec81[1] + fConst12 * fRec81[2];
		fVec17[IOTA0 & 1048575] = fTemp70;
		double fTemp71 = fVec17[(IOTA0 - iTemp14) & 1048575];
		double fTemp72 = fVec17[(IOTA0 - iTemp18) & 1048575];
		double fTemp73 = fVec17[(IOTA0 - iTemp22) & 1048575];
		double fTemp74 = fSlow8 * (fConst16 * fTemp73 + fRec30[0] * (0.0 - fConst16 * (fTemp73 - fVec17[(IOTA0 - iTemp21) & 1048575]))) + fSlow6 * (fConst16 * fTemp72 + fRec26[0] * (0.0 - fConst16 * (fTemp72 - fVec17[(IOTA0 - iTemp17) & 1048575]))) + fSlow4 * (fConst16 * fTemp71 + fRec22[0] * (0.0 - fConst16 * (fTemp71 - fVec17[(IOTA0 - iTemp13) & 1048575])));
		fVec18[0] = fTemp74;
		fRec80[0] = 0.0 - fConst101 * (fConst100 * fRec80[1] - (fTemp74 + fVec18[1]));
		fRec79[0] = fRec80[0] + 0.995 * fRec79[1] - fRec80[1];
		fRec78[0] = fRec79[0] - fConst9 * (fConst8 * fRec78[1] + fConst7 * fRec78[2]);
		double fTemp75 = fConst9 * (fConst105 * fRec78[0] + fConst104 * fRec78[1] + fConst103 * fRec78[2]);
		fRec77[0] = ((signbit(fTemp75)) ? copicatreplay1_negclip(fTemp75) : copicatreplay1clip(fTemp75)) - fConst5 * (fConst4 * fRec77[1] + fConst2 * fRec77[2]);
		double fTemp76 = fConst5 * (fConst109 * fRec77[0] + fConst108 * fRec77[1] + fConst107 * fRec77[2]);
		fRec76[0] = ((signbit(fTemp76)) ? copicatreplay2_negclip(fTemp76) : copicatreplay2clip(fTemp76));
		fRec92[0] = fSlow10 + 0.993 * fRec92[1];
		output0[i0] = FAUSTFLOAT(fRec92[0] * (fTemp67 + 0.25 * fRec76[0] * fRec33[0] + fTemp53 + 0.25 * fRec33[0] * fRec61[0] + fTemp40 + 0.25 * fRec33[0] * fRec47[0] + fTemp28 + 0.25 * fRec33[0] * fRec34[0] + fTemp8 + 0.25 * fRec33[0] * fRec0[0]));
		fRec8[1] = fRec8[0];
		fVec0[1] = fVec0[0];
		fRec17[1] = fRec17[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fVec1[1] = fVec1[0];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fVec2[1] = fVec2[0];
		fRec13[1] = fRec13[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fVec3[1] = fVec3[0];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fVec4[1] = fVec4[0];
		fRec18[1] = fRec18[0];
		for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
			fRec7[j0] = fRec7[j0 - 1];
		}
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		IOTA0 = IOTA0 + 1;
		fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fRec32[1] = fRec32[0];
		fVec6[1] = fVec6[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		fRec33[1] = fRec33[0];
		fRec44[1] = fRec44[0];
		fRec43[2] = fRec43[1];
		fRec43[1] = fRec43[0];
		fRec42[2] = fRec42[1];
		fRec42[1] = fRec42[0];
		fRec46[1] = fRec46[0];
		fVec7[1] = fVec7[0];
		fRec45[1] = fRec45[0];
		for (int j1 = 3; j1 > 0; j1 = j1 - 1) {
			fRec41[j1] = fRec41[j1 - 1];
		}
		fRec40[2] = fRec40[1];
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fVec9[1] = fVec9[0];
		fRec38[1] = fRec38[0];
		fRec37[1] = fRec37[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		fRec35[2] = fRec35[1];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec58[1] = fRec58[0];
		fRec57[2] = fRec57[1];
		fRec57[1] = fRec57[0];
		fRec56[2] = fRec56[1];
		fRec56[1] = fRec56[0];
		fRec55[2] = fRec55[1];
		fRec55[1] = fRec55[0];
		fRec60[1] = fRec60[0];
		fVec10[1] = fVec10[0];
		fRec59[1] = fRec59[0];
		for (int j2 = 3; j2 > 0; j2 = j2 - 1) {
			fRec54[j2] = fRec54[j2 - 1];
		}
		fRec53[2] = fRec53[1];
		fRec53[1] = fRec53[0];
		fRec52[2] = fRec52[1];
		fRec52[1] = fRec52[0];
		fVec12[1] = fVec12[0];
		fRec51[1] = fRec51[0];
		fRec50[1] = fRec50[0];
		fRec49[2] = fRec49[1];
		fRec49[1] = fRec49[0];
		fRec48[2] = fRec48[1];
		fRec48[1] = fRec48[0];
		fRec47[2] = fRec47[1];
		fRec47[1] = fRec47[0];
		fRec73[1] = fRec73[0];
		fRec72[2] = fRec72[1];
		fRec72[1] = fRec72[0];
		fRec71[2] = fRec71[1];
		fRec71[1] = fRec71[0];
		fRec70[2] = fRec70[1];
		fRec70[1] = fRec70[0];
		fRec69[2] = fRec69[1];
		fRec69[1] = fRec69[0];
		fRec75[1] = fRec75[0];
		fVec13[1] = fVec13[0];
		fRec74[1] = fRec74[0];
		for (int j3 = 3; j3 > 0; j3 = j3 - 1) {
			fRec68[j3] = fRec68[j3 - 1];
		}
		fRec67[2] = fRec67[1];
		fRec67[1] = fRec67[0];
		fRec66[2] = fRec66[1];
		fRec66[1] = fRec66[0];
		fVec15[1] = fVec15[0];
		fRec65[1] = fRec65[0];
		fRec64[1] = fRec64[0];
		fRec63[2] = fRec63[1];
		fRec63[1] = fRec63[0];
		fRec62[2] = fRec62[1];
		fRec62[1] = fRec62[0];
		fRec61[2] = fRec61[1];
		fRec61[1] = fRec61[0];
		fRec89[1] = fRec89[0];
		fRec88[2] = fRec88[1];
		fRec88[1] = fRec88[0];
		fRec87[2] = fRec87[1];
		fRec87[1] = fRec87[0];
		fRec86[2] = fRec86[1];
		fRec86[1] = fRec86[0];
		fRec85[2] = fRec85[1];
		fRec85[1] = fRec85[0];
		fRec84[2] = fRec84[1];
		fRec84[1] = fRec84[0];
		fRec91[1] = fRec91[0];
		fVec16[1] = fVec16[0];
		fRec90[1] = fRec90[0];
		for (int j4 = 3; j4 > 0; j4 = j4 - 1) {
			fRec83[j4] = fRec83[j4 - 1];
		}
		fRec82[2] = fRec82[1];
		fRec82[1] = fRec82[0];
		fRec81[2] = fRec81[1];
		fRec81[1] = fRec81[0];
		fVec18[1] = fVec18[0];
		fRec80[1] = fRec80[0];
		fRec79[1] = fRec79[0];
		fRec78[2] = fRec78[1];
		fRec78[1] = fRec78[0];
		fRec77[2] = fRec77[1];
		fRec77[1] = fRec77[0];
		fRec76[2] = fRec76[1];
		fRec76[1] = fRec76[0];
		fRec92[1] = fRec92[0];
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
#undef fCheckbox0
#undef fCheckbox1
#undef fCheckbox2
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
	case HEAD1: 
		fCheckbox2_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case HEAD2: 
		fCheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case HEAD3: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case SUSTAIN: 
		fVslider1_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case SWELL: 
		fVslider3_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case AUDIO_IN: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case OUTPUT: 
		fVslider4_ = (float*)data; // , 1.0, 0.0, 2.0, 0.01 
		break;
	case BPM: 
		fVslider2_ = (float*)data; // , 1.2e+02, 24.0, 3.6e+02, 0.1 
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
   SUSTAIN, 
   SWELL, 
   INPUT, 
   OUTPUT, 
   BPM, 
   HEAD1, 
   HEAD2, 
   HEAD3, 
} PortIndex;
*/

} // end namespace gxechocat
