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
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec8[2];
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
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst63;
	double fConst64;
	double fConst65;
	double fVec0[2];
	double fConst66;
	double fConst67;
	double fRec15[2];
	double fRec14[3];
	double fVec1[2];
	double fConst68;
	double fConst69;
	double fConst70;
	double fConst71;
	double fRec13[2];
	double fRec12[3];
	double fConst72;
	double fRec11[3];
	double fRec10[3];
	double fRec9[3];
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
	double fRec17[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec18[2];
	double fVec2[2];
	double fConst85;
	double fConst86;
	double fRec16[2];
	double fRec7[4];
	double fConst87;
	double fConst88;
	double fConst89;
	double fConst90;
	double fConst91;
	double fRec6[3];
	double fConst92;
	double fRec5[3];
	int IOTA0;
	double *fVec3;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fConst93;
	double fConst94;
	double fRec19[2];
	double fRec20[2];
	double fRec21[2];
	double fRec22[2];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst95;
	double fRec23[2];
	double fRec24[2];
	double fRec25[2];
	double fRec26[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	double fConst96;
	double fRec27[2];
	double fRec28[2];
	double fRec29[2];
	double fRec30[2];
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT	*fCheckbox2_;
	double fVec4[2];
	double fConst97;
	double fConst98;
	double fConst99;
	double fConst100;
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fConst101;
	double fConst102;
	double fConst103;
	double fConst104;
	double fRec1[3];
	double fConst105;
	double fConst106;
	double fConst107;
	double fConst108;
	double fRec0[3];
	double fConst109;
	double fConst110;
	double fRec44[2];
	double fRec43[3];
	double fConst111;
	double fRec42[3];
	double fRec41[3];
	double fRec40[3];
	double fRec39[3];
	double fRec46[2];
	double fVec5[2];
	double fRec45[2];
	double fRec38[4];
	double fRec37[3];
	double fRec36[3];
	double *fVec6;
	double fVec7[2];
	double fRec35[2];
	double fRec34[2];
	double fRec33[3];
	double fRec32[3];
	double fRec31[3];
	double fConst112;
	double fConst113;
	double fConst114;
	double fRec60[2];
	double fRec59[3];
	double fVec8[2];
	double fConst115;
	double fConst116;
	double fRec58[2];
	double fRec57[3];
	double fConst117;
	double fRec56[3];
	double fRec55[3];
	double fRec62[2];
	double fVec9[2];
	double fRec61[2];
	double fRec54[4];
	double fRec53[3];
	double fRec52[3];
	double *fVec10;
	double fVec11[2];
	double fRec51[2];
	double fRec50[2];
	double fRec49[3];
	double fRec48[3];
	double fRec47[3];
	double fConst118;
	double fConst119;
	double fConst120;
	double fRec75[2];
	double fRec74[3];
	double fVec12[2];
	double fConst121;
	double fConst122;
	double fRec73[2];
	double fRec72[3];
	double fConst123;
	double fRec71[3];
	double fRec77[2];
	double fVec13[2];
	double fRec76[2];
	double fRec70[4];
	double fRec69[3];
	double fRec68[3];
	double *fVec14;
	double fVec15[2];
	double fRec67[2];
	double fRec66[2];
	double fRec65[3];
	double fRec64[3];
	double fRec63[3];
	double fRec88[2];
	double fRec87[3];
	double fRec86[3];
	double fRec90[2];
	double fVec16[2];
	double fRec89[2];
	double fRec85[4];
	double fRec84[3];
	double fRec83[3];
	double *fVec17;
	double fVec18[2];
	double fRec82[2];
	double fRec81[2];
	double fRec80[3];
	double fRec79[3];
	double fRec78[3];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec91[2];
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
	  fVec3(0),
	  fVec6(0),
	  fVec10(0),
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
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec15[l2] = 0.0;
	for (int l3 = 0; l3 < 3; l3 = l3 + 1) fRec14[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fVec1[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec13[l5] = 0.0;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec12[l6] = 0.0;
	for (int l7 = 0; l7 < 3; l7 = l7 + 1) fRec11[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec10[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec9[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec17[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec18[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fVec2[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec16[l13] = 0.0;
	for (int l14 = 0; l14 < 4; l14 = l14 + 1) fRec7[l14] = 0.0;
	for (int l15 = 0; l15 < 3; l15 = l15 + 1) fRec6[l15] = 0.0;
	for (int l16 = 0; l16 < 3; l16 = l16 + 1) fRec5[l16] = 0.0;
	for (int l17 = 0; l17 < 1048576; l17 = l17 + 1) fVec3[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec19[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec20[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec21[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec22[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec23[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec24[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec25[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec26[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec27[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec28[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec29[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec30[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fVec4[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec4[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fRec3[l32] = 0.0;
	for (int l33 = 0; l33 < 3; l33 = l33 + 1) fRec2[l33] = 0.0;
	for (int l34 = 0; l34 < 3; l34 = l34 + 1) fRec1[l34] = 0.0;
	for (int l35 = 0; l35 < 3; l35 = l35 + 1) fRec0[l35] = 0.0;
	for (int l36 = 0; l36 < 2; l36 = l36 + 1) fRec44[l36] = 0.0;
	for (int l37 = 0; l37 < 3; l37 = l37 + 1) fRec43[l37] = 0.0;
	for (int l38 = 0; l38 < 3; l38 = l38 + 1) fRec42[l38] = 0.0;
	for (int l39 = 0; l39 < 3; l39 = l39 + 1) fRec41[l39] = 0.0;
	for (int l40 = 0; l40 < 3; l40 = l40 + 1) fRec40[l40] = 0.0;
	for (int l41 = 0; l41 < 3; l41 = l41 + 1) fRec39[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) fRec46[l42] = 0.0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fVec5[l43] = 0.0;
	for (int l44 = 0; l44 < 2; l44 = l44 + 1) fRec45[l44] = 0.0;
	for (int l45 = 0; l45 < 4; l45 = l45 + 1) fRec38[l45] = 0.0;
	for (int l46 = 0; l46 < 3; l46 = l46 + 1) fRec37[l46] = 0.0;
	for (int l47 = 0; l47 < 3; l47 = l47 + 1) fRec36[l47] = 0.0;
	for (int l48 = 0; l48 < 1048576; l48 = l48 + 1) fVec6[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fVec7[l49] = 0.0;
	for (int l50 = 0; l50 < 2; l50 = l50 + 1) fRec35[l50] = 0.0;
	for (int l51 = 0; l51 < 2; l51 = l51 + 1) fRec34[l51] = 0.0;
	for (int l52 = 0; l52 < 3; l52 = l52 + 1) fRec33[l52] = 0.0;
	for (int l53 = 0; l53 < 3; l53 = l53 + 1) fRec32[l53] = 0.0;
	for (int l54 = 0; l54 < 3; l54 = l54 + 1) fRec31[l54] = 0.0;
	for (int l55 = 0; l55 < 2; l55 = l55 + 1) fRec60[l55] = 0.0;
	for (int l56 = 0; l56 < 3; l56 = l56 + 1) fRec59[l56] = 0.0;
	for (int l57 = 0; l57 < 2; l57 = l57 + 1) fVec8[l57] = 0.0;
	for (int l58 = 0; l58 < 2; l58 = l58 + 1) fRec58[l58] = 0.0;
	for (int l59 = 0; l59 < 3; l59 = l59 + 1) fRec57[l59] = 0.0;
	for (int l60 = 0; l60 < 3; l60 = l60 + 1) fRec56[l60] = 0.0;
	for (int l61 = 0; l61 < 3; l61 = l61 + 1) fRec55[l61] = 0.0;
	for (int l62 = 0; l62 < 2; l62 = l62 + 1) fRec62[l62] = 0.0;
	for (int l63 = 0; l63 < 2; l63 = l63 + 1) fVec9[l63] = 0.0;
	for (int l64 = 0; l64 < 2; l64 = l64 + 1) fRec61[l64] = 0.0;
	for (int l65 = 0; l65 < 4; l65 = l65 + 1) fRec54[l65] = 0.0;
	for (int l66 = 0; l66 < 3; l66 = l66 + 1) fRec53[l66] = 0.0;
	for (int l67 = 0; l67 < 3; l67 = l67 + 1) fRec52[l67] = 0.0;
	for (int l68 = 0; l68 < 1048576; l68 = l68 + 1) fVec10[l68] = 0.0;
	for (int l69 = 0; l69 < 2; l69 = l69 + 1) fVec11[l69] = 0.0;
	for (int l70 = 0; l70 < 2; l70 = l70 + 1) fRec51[l70] = 0.0;
	for (int l71 = 0; l71 < 2; l71 = l71 + 1) fRec50[l71] = 0.0;
	for (int l72 = 0; l72 < 3; l72 = l72 + 1) fRec49[l72] = 0.0;
	for (int l73 = 0; l73 < 3; l73 = l73 + 1) fRec48[l73] = 0.0;
	for (int l74 = 0; l74 < 3; l74 = l74 + 1) fRec47[l74] = 0.0;
	for (int l75 = 0; l75 < 2; l75 = l75 + 1) fRec75[l75] = 0.0;
	for (int l76 = 0; l76 < 3; l76 = l76 + 1) fRec74[l76] = 0.0;
	for (int l77 = 0; l77 < 2; l77 = l77 + 1) fVec12[l77] = 0.0;
	for (int l78 = 0; l78 < 2; l78 = l78 + 1) fRec73[l78] = 0.0;
	for (int l79 = 0; l79 < 3; l79 = l79 + 1) fRec72[l79] = 0.0;
	for (int l80 = 0; l80 < 3; l80 = l80 + 1) fRec71[l80] = 0.0;
	for (int l81 = 0; l81 < 2; l81 = l81 + 1) fRec77[l81] = 0.0;
	for (int l82 = 0; l82 < 2; l82 = l82 + 1) fVec13[l82] = 0.0;
	for (int l83 = 0; l83 < 2; l83 = l83 + 1) fRec76[l83] = 0.0;
	for (int l84 = 0; l84 < 4; l84 = l84 + 1) fRec70[l84] = 0.0;
	for (int l85 = 0; l85 < 3; l85 = l85 + 1) fRec69[l85] = 0.0;
	for (int l86 = 0; l86 < 3; l86 = l86 + 1) fRec68[l86] = 0.0;
	for (int l87 = 0; l87 < 1048576; l87 = l87 + 1) fVec14[l87] = 0.0;
	for (int l88 = 0; l88 < 2; l88 = l88 + 1) fVec15[l88] = 0.0;
	for (int l89 = 0; l89 < 2; l89 = l89 + 1) fRec67[l89] = 0.0;
	for (int l90 = 0; l90 < 2; l90 = l90 + 1) fRec66[l90] = 0.0;
	for (int l91 = 0; l91 < 3; l91 = l91 + 1) fRec65[l91] = 0.0;
	for (int l92 = 0; l92 < 3; l92 = l92 + 1) fRec64[l92] = 0.0;
	for (int l93 = 0; l93 < 3; l93 = l93 + 1) fRec63[l93] = 0.0;
	for (int l94 = 0; l94 < 2; l94 = l94 + 1) fRec88[l94] = 0.0;
	for (int l95 = 0; l95 < 3; l95 = l95 + 1) fRec87[l95] = 0.0;
	for (int l96 = 0; l96 < 3; l96 = l96 + 1) fRec86[l96] = 0.0;
	for (int l97 = 0; l97 < 2; l97 = l97 + 1) fRec90[l97] = 0.0;
	for (int l98 = 0; l98 < 2; l98 = l98 + 1) fVec16[l98] = 0.0;
	for (int l99 = 0; l99 < 2; l99 = l99 + 1) fRec89[l99] = 0.0;
	for (int l100 = 0; l100 < 4; l100 = l100 + 1) fRec85[l100] = 0.0;
	for (int l101 = 0; l101 < 3; l101 = l101 + 1) fRec84[l101] = 0.0;
	for (int l102 = 0; l102 < 3; l102 = l102 + 1) fRec83[l102] = 0.0;
	for (int l103 = 0; l103 < 1048576; l103 = l103 + 1) fVec17[l103] = 0.0;
	for (int l104 = 0; l104 < 2; l104 = l104 + 1) fVec18[l104] = 0.0;
	for (int l105 = 0; l105 < 2; l105 = l105 + 1) fRec82[l105] = 0.0;
	for (int l106 = 0; l106 < 2; l106 = l106 + 1) fRec81[l106] = 0.0;
	for (int l107 = 0; l107 < 3; l107 = l107 + 1) fRec80[l107] = 0.0;
	for (int l108 = 0; l108 < 3; l108 = l108 + 1) fRec79[l108] = 0.0;
	for (int l109 = 0; l109 < 3; l109 = l109 + 1) fRec78[l109] = 0.0;
	for (int l110 = 0; l110 < 2; l110 = l110 + 1) fRec91[l110] = 0.0;
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
	fConst1 = 4.3361242466424e-10 * fConst0;
	fConst2 = fConst0 * (fConst1 + -1.99329936161353e-08) + 1.89880017035189e-07;
	fConst3 = mydsp_faustpower2_f(fConst0);
	fConst4 = 3.79760034070379e-07 - 8.6722484932848e-10 * fConst3;
	fConst5 = 1.0 / (fConst0 * (fConst1 + 1.99329936161353e-08) + 1.89880017035189e-07);
	fConst6 = 4.33785780482415e-10 * fConst0;
	fConst7 = fConst0 * (fConst6 + -1.16144315716444e-08) + 6.90530766455131e-08;
	fConst8 = 1.38106153291026e-07 - 8.6757156096483e-10 * fConst3;
	fConst9 = 1.0 / (fConst0 * (fConst6 + 1.16144315716444e-08) + 6.90530766455131e-08);
	fConst10 = std::tan(125.66370614359172 / fConst0);
	fConst11 = mydsp_faustpower2_f(fConst10);
	fConst12 = 2.0 * (1.0 - 1.0 / fConst11);
	fConst13 = 1.0 / fConst10;
	fConst14 = (fConst13 + -0.7653668647301795) / fConst10 + 1.0;
	fConst15 = (fConst13 + 0.7653668647301795) / fConst10 + 1.0;
	fConst16 = 1.0 / fConst15;
	fConst17 = (fConst13 + -1.8477590650225735) / fConst10 + 1.0;
	fConst18 = (fConst13 + 1.8477590650225735) / fConst10 + 1.0;
	fConst19 = 1.0 / fConst18;
	fConst20 = 6.73029102377671e-15 * fConst0;
	fConst21 = fConst0 * (fConst0 * (1.10493997854221e-10 - fConst20) + -2.30183843147656e-08) + 6.01595252726883e-07;
	fConst22 = 2.01908730713301e-14 * fConst0;
	fConst23 = fConst0 * (fConst0 * (fConst22 + -1.10493997854221e-10) + -2.30183843147656e-08) + 1.80478575818065e-06;
	fConst24 = fConst0 * (fConst0 * (-1.10493997854221e-10 - fConst22) + 2.30183843147656e-08) + 1.80478575818065e-06;
	fConst25 = 1.0 / (fConst0 * (fConst0 * (fConst20 + 1.10493997854221e-10) + 2.30183843147656e-08) + 6.01595252726883e-07);
	fConst26 = 7.83789728824443e-11 * fConst0;
	fConst27 = -3.13458049067171e-09 - fConst26;
	fConst28 = 8.32844278169955e-11 * fConst0;
	fConst29 = fConst28 + 5.0418669893366e-09;
	fConst30 = 4.11425073415965e-10 * fConst0;
	fConst31 = fConst0 * (fConst30 + 2.49068229273233e-08);
	fConst32 = 3.13458049067171e-09 - fConst26;
	fConst33 = fConst28 + -5.0418669893366e-09;
	fConst34 = fConst0 * (fConst30 + -2.49068229273233e-08);
	fConst35 = 8.22850146831931e-10 * fConst3;
	fConst36 = std::tan(270.1769682087222 / fConst0);
	fConst37 = mydsp_faustpower2_f(fConst36);
	fConst38 = 2.0 * (1.0 - 1.0 / fConst37);
	fConst39 = 1.0 / fConst36;
	fConst40 = 1.0 - fConst39;
	fConst41 = 1.0 - fConst40 / fConst36;
	fConst42 = fConst39 + 1.0;
	fConst43 = 1.0 / (fConst42 / fConst36 + 1.0);
	fConst44 = std::tan(659.7344572538566 / fConst0);
	fConst45 = mydsp_faustpower2_f(fConst44);
	fConst46 = 2.0 * (1.0 - 1.0 / fConst45);
	fConst47 = 1.0 / fConst44;
	fConst48 = 1.0 - fConst47;
	fConst49 = 1.0 - fConst48 / fConst44;
	fConst50 = fConst47 + 1.0;
	fConst51 = 1.0 / (fConst50 / fConst44 + 1.0);
	fConst52 = std::tan(3769.9111843077517 / fConst0);
	fConst53 = mydsp_faustpower2_f(fConst52);
	fConst54 = 2.0 * (1.0 - 1.0 / fConst53);
	fConst55 = 1.0 / fConst52;
	fConst56 = (fConst55 + -1.0000000000000004) / fConst52 + 1.0;
	fConst57 = (fConst55 + 1.0000000000000004) / fConst52 + 1.0;
	fConst58 = 1.0 / fConst57;
	fConst59 = std::tan(20517.741620594938 / fConst0);
	fConst60 = mydsp_faustpower2_f(fConst59);
	fConst61 = 2.0 * (1.0 - 1.0 / fConst60);
	fConst62 = 1.0 / fConst59;
	fConst63 = (fConst62 + -1.0000000000000004) / fConst59 + 1.0;
	fConst64 = (fConst62 + 1.0000000000000004) / fConst59 + 1.0;
	fConst65 = 1.0 / fConst64;
	fConst66 = 1.0 - fConst62;
	fConst67 = 1.0 / (fConst62 + 1.0);
	fConst68 = 1.0 / (fConst52 * fConst64);
	fConst69 = 1.0 - fConst55;
	fConst70 = fConst55 + 1.0;
	fConst71 = 1.0 / fConst70;
	fConst72 = 1.0 / (fConst53 * fConst57);
	fConst73 = 2.06740841499587e-08 * fConst0;
	fConst74 = 5.51308910665569e-07 - fConst73;
	fConst75 = fConst0 * fConst74;
	fConst76 = 4.13481682999174e-08 * fConst3;
	fConst77 = -5.51308910665569e-07 - fConst73;
	fConst78 = fConst0 * fConst77;
	fConst79 = std::tan(471.23889803846896 / fConst0);
	fConst80 = 1.0 / fConst79;
	fConst81 = 1.0 - fConst80;
	fConst82 = 1.0 / std::tan(23561.94490192345 / fConst0);
	fConst83 = 1.0 - fConst82;
	fConst84 = 1.0 / (fConst82 + 1.0);
	fConst85 = 0.25 / fConst79;
	fConst86 = 1.0 / (fConst80 + 1.0);
	fConst87 = 1.23938408071082e-08 * fConst0;
	fConst88 = fConst0 * (7.13052376187718e-07 - fConst87) + -9.98795811595446e-06;
	fConst89 = fConst0 * (fConst87 + 7.13052376187718e-07) + -2.99638743478634e-05;
	fConst90 = fConst0 * (fConst87 + -7.13052376187718e-07) + -2.99638743478634e-05;
	fConst91 = fConst0 * (-7.13052376187718e-07 - fConst87) + -9.98795811595446e-06;
	fConst92 = 1.0 / (fConst11 * fConst18);
	fConst93 = 9e+01 * fConst0;
	fConst94 = 1e+01 / fConst0;
	fConst95 = 6e+01 * fConst0;
	fConst96 = 3e+01 * fConst0;
	fConst97 = 1.0 / (fConst11 * fConst15);
	fConst98 = 1.0 / std::tan(20420.352248333656 / fConst0);
	fConst99 = 1.0 - fConst98;
	fConst100 = 1.0 / (fConst98 + 1.0);
	fConst101 = 2.16461324600193e-08 * fConst0;
	fConst102 = fConst0 * (1.31188681575873e-07 - fConst101);
	fConst103 = 4.32922649200386e-08 * fConst3;
	fConst104 = fConst0 * (-1.31188681575873e-07 - fConst101);
	fConst105 = 1.02325156488485e-09 * fConst0;
	fConst106 = fConst0 * (1.05707806289759e-08 - fConst105);
	fConst107 = 2.0465031297697e-09 * fConst3;
	fConst108 = fConst0 * (-1.05707806289759e-08 - fConst105);
	fConst109 = 1.0 - fConst69 / fConst52;
	fConst110 = 1.0 / (fConst70 / fConst52 + 1.0);
	fConst111 = 1.0 / (fConst60 * fConst64);
	fConst112 = (fConst47 + -1.0000000000000004) / fConst44 + 1.0;
	fConst113 = (fConst47 + 1.0000000000000004) / fConst44 + 1.0;
	fConst114 = 1.0 / fConst113;
	fConst115 = 1.0 / (fConst44 * fConst57);
	fConst116 = 1.0 / fConst50;
	fConst117 = 1.0 / (fConst45 * fConst113);
	fConst118 = (fConst39 + -1.0000000000000004) / fConst36 + 1.0;
	fConst119 = (fConst39 + 1.0000000000000004) / fConst36 + 1.0;
	fConst120 = 1.0 / fConst119;
	fConst121 = 1.0 / (fConst36 * fConst113);
	fConst122 = 1.0 / fConst42;
	fConst123 = 1.0 / (fConst37 * fConst119);
	IOTA0 = 0;
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void Dsp::mem_alloc()
{
	if (!fVec3) fVec3 = new double[1048576];
	if (!fVec6) fVec6 = new double[1048576];
	if (!fVec10) fVec10 = new double[1048576];
	if (!fVec14) fVec14 = new double[1048576];
	if (!fVec17) fVec17 = new double[1048576];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec3) { delete fVec3; fVec3 = 0; }
	if (fVec6) { delete fVec6; fVec6 = 0; }
	if (fVec10) { delete fVec10; fVec10 = 0; }
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
	double fSlow3 = fConst93 / fSlow2;
	double fSlow4 = double(fCheckbox0);
	double fSlow5 = fConst95 / fSlow2;
	double fSlow6 = double(fCheckbox1);
	double fSlow7 = fConst96 / fSlow2;
	double fSlow8 = double(fCheckbox2);
	double fSlow9 = 0.004073836948085289 * (std::exp(double(fVslider3)) + -1.0);
	double fSlow10 = 0.00036676987543879196 * (std::exp(3.0 * double(fVslider4)) + -1.0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec8[0] = fSlow0 + 0.993 * fRec8[1];
		double fTemp0 = fConst27 * fRec8[0];
		double fTemp1 = fConst31 + fRec8[0] * (fConst0 * (fConst29 + fTemp0) + 6.26916098134342e-08) + 3.09696552478371e-07;
		double fTemp2 = fConst34 + fRec8[0] * (fConst0 * (fConst33 + fConst32 * fRec8[0]) + 6.26916098134342e-08) + 3.09696552478371e-07;
		double fTemp3 = fRec8[0] * (fConst3 * (1.56757945764889e-10 * fRec8[0] + -1.66568855633991e-10) + 1.25383219626868e-07) + 6.19393104956741e-07 - fConst35;
		double fTemp4 = fConst38 * fRec10[1];
		double fTemp5 = fConst46 * fRec11[1];
		double fTemp6 = double(input0[i0]);
		fVec0[0] = fTemp6;
		fRec15[0] = -(fConst67 * (fConst66 * fRec15[1] - (fTemp6 + fVec0[1])));
		fRec14[0] = fRec15[0] - fConst65 * (fConst63 * fRec14[2] + fConst61 * fRec14[1]);
		double fTemp7 = fRec14[2] + fRec14[0] + 2.0 * fRec14[1];
		fVec1[0] = fTemp7;
		fRec13[0] = -(fConst71 * (fConst69 * fRec13[1] - fConst68 * (fTemp7 - fVec1[1])));
		fRec12[0] = fRec13[0] - fConst58 * (fConst56 * fRec12[2] + fConst54 * fRec12[1]);
		fRec11[0] = fConst72 * (fRec12[2] + (fRec12[0] - 2.0 * fRec12[1])) - fConst51 * (fConst49 * fRec11[2] + fTemp5);
		fRec10[0] = fRec11[2] + fConst51 * (fTemp5 + fConst49 * fRec11[0]) - fConst43 * (fConst41 * fRec10[2] + fTemp4);
		fRec9[0] = fRec10[2] + fConst43 * (fTemp4 + fConst41 * fRec10[0]) - (fTemp3 * fRec9[1] + fTemp2 * fRec9[2]) / fTemp1;
		double fTemp8 = fConst76 * fRec9[1];
		double fTemp9 = fRec8[0] * (fConst78 * fRec9[0] + fTemp8 + fConst75 * fRec9[2]) / fTemp1;
		fRec17[0] = -(fConst84 * (fConst83 * fRec17[1] - (fRec0[1] + fRec0[2])));
		fRec18[0] = fSlow1 + 0.993 * fRec18[1];
		double fTemp10 = fRec18[0] * fRec17[0];
		fVec2[0] = fTemp10;
		fRec16[0] = fConst86 * (fConst85 * (fTemp10 - fVec2[1]) - fConst81 * fRec16[1]);
		fRec7[0] = fRec16[0] + ((signbit(fTemp9)) ? copicat1_negclip(fTemp9) : copicat1clip(fTemp9)) - fConst25 * (fConst24 * fRec7[1] + fConst23 * fRec7[2] + fConst21 * fRec7[3]);
		double fTemp11 = fConst25 * (fConst91 * fRec7[0] + fConst90 * fRec7[1] + fConst89 * fRec7[2] + fConst88 * fRec7[3]);
		fRec6[0] = ((signbit(fTemp11)) ? copicatrecord_2_negclip(fTemp11) : copicatrecord_2clip(fTemp11)) - fConst19 * (fConst17 * fRec6[2] + fConst12 * fRec6[1]);
		fRec5[0] = fConst92 * (fRec6[2] + (fRec6[0] - 2.0 * fRec6[1])) - fConst16 * (fConst14 * fRec5[2] + fConst12 * fRec5[1]);
		double fTemp12 = fRec5[2] + (fRec5[0] - 2.0 * fRec5[1]);
		fVec3[IOTA0 & 1048575] = fTemp12;
		double fTemp13 = ((fRec19[1] != 0.0) ? (((fRec20[1] > 0.0) & (fRec20[1] < 1.0)) ? fRec19[1] : 0.0) : (((fRec20[1] == 0.0) & (fSlow3 != fRec21[1])) ? fConst94 : (((fRec20[1] == 1.0) & (fSlow3 != fRec22[1])) ? -fConst94 : 0.0)));
		fRec19[0] = fTemp13;
		fRec20[0] = std::max<double>(0.0, std::min<double>(1.0, fRec20[1] + fTemp13));
		fRec21[0] = (((fRec20[1] >= 1.0) & (fRec22[1] != fSlow3)) ? fSlow3 : fRec21[1]);
		fRec22[0] = (((fRec20[1] <= 0.0) & (fRec21[1] != fSlow3)) ? fSlow3 : fRec22[1]);
		int iTemp14 = int(std::min<double>(524288.0, std::max<double>(0.0, fRec22[0])));
		int iTemp15 = int(std::min<double>(524288.0, std::max<double>(0.0, fRec21[0])));
		double fTemp16 = fVec3[(IOTA0 - iTemp15) & 1048575];
		double fTemp17 = ((fRec23[1] != 0.0) ? (((fRec24[1] > 0.0) & (fRec24[1] < 1.0)) ? fRec23[1] : 0.0) : (((fRec24[1] == 0.0) & (fSlow5 != fRec25[1])) ? fConst94 : (((fRec24[1] == 1.0) & (fSlow5 != fRec26[1])) ? -fConst94 : 0.0)));
		fRec23[0] = fTemp17;
		fRec24[0] = std::max<double>(0.0, std::min<double>(1.0, fRec24[1] + fTemp17));
		fRec25[0] = (((fRec24[1] >= 1.0) & (fRec26[1] != fSlow5)) ? fSlow5 : fRec25[1]);
		fRec26[0] = (((fRec24[1] <= 0.0) & (fRec25[1] != fSlow5)) ? fSlow5 : fRec26[1]);
		int iTemp18 = int(std::min<double>(524288.0, std::max<double>(0.0, fRec26[0])));
		int iTemp19 = int(std::min<double>(524288.0, std::max<double>(0.0, fRec25[0])));
		double fTemp20 = fVec3[(IOTA0 - iTemp19) & 1048575];
		double fTemp21 = ((fRec27[1] != 0.0) ? (((fRec28[1] > 0.0) & (fRec28[1] < 1.0)) ? fRec27[1] : 0.0) : (((fRec28[1] == 0.0) & (fSlow7 != fRec29[1])) ? fConst94 : (((fRec28[1] == 1.0) & (fSlow7 != fRec30[1])) ? -fConst94 : 0.0)));
		fRec27[0] = fTemp21;
		fRec28[0] = std::max<double>(0.0, std::min<double>(1.0, fRec28[1] + fTemp21));
		fRec29[0] = (((fRec28[1] >= 1.0) & (fRec30[1] != fSlow7)) ? fSlow7 : fRec29[1]);
		fRec30[0] = (((fRec28[1] <= 0.0) & (fRec29[1] != fSlow7)) ? fSlow7 : fRec30[1]);
		int iTemp22 = int(std::min<double>(524288.0, std::max<double>(0.0, fRec30[0])));
		int iTemp23 = int(std::min<double>(524288.0, std::max<double>(0.0, fRec29[0])));
		double fTemp24 = fVec3[(IOTA0 - iTemp23) & 1048575];
		double fTemp25 = fSlow8 * (fTemp24 - fRec28[0] * (fTemp24 - fVec3[(IOTA0 - iTemp22) & 1048575])) + fSlow6 * (fTemp20 - fRec24[0] * (fTemp20 - fVec3[(IOTA0 - iTemp18) & 1048575])) + fSlow4 * (fTemp16 - fRec20[0] * (fTemp16 - fVec3[(IOTA0 - iTemp14) & 1048575]));
		fVec4[0] = fTemp25;
		fRec4[0] = -(fConst100 * (fConst99 * fRec4[1] - fConst97 * (fTemp25 + fVec4[1])));
		fRec3[0] = fRec4[0] + 0.995 * fRec3[1] - fRec4[1];
		fRec2[0] = fRec3[0] - fConst9 * (fConst8 * fRec2[1] + fConst7 * fRec2[2]);
		double fTemp26 = fConst9 * (fConst104 * fRec2[0] + fConst103 * fRec2[1] + fConst102 * fRec2[2]);
		fRec1[0] = ((signbit(fTemp26)) ? copicatreplay1_negclip(fTemp26) : copicatreplay1clip(fTemp26)) - fConst5 * (fConst4 * fRec1[1] + fConst2 * fRec1[2]);
		double fTemp27 = fConst5 * (fConst108 * fRec1[0] + fConst107 * fRec1[1] + fConst106 * fRec1[2]);
		fRec0[0] = ((signbit(fTemp27)) ? copicatreplay2_negclip(fTemp27) : copicatreplay2clip(fTemp27));
		double fTemp28 = fConst38 * fRec40[1];
		double fTemp29 = fConst46 * fRec41[1];
		double fTemp30 = fConst54 * fRec42[1];
		fRec44[0] = -(fConst67 * (fConst66 * fRec44[1] - fConst62 * (fTemp6 - fVec0[1])));
		fRec43[0] = fRec44[0] - fConst65 * (fConst63 * fRec43[2] + fConst61 * fRec43[1]);
		fRec42[0] = fConst111 * (fRec43[2] + (fRec43[0] - 2.0 * fRec43[1])) - fConst110 * (fConst109 * fRec42[2] + fTemp30);
		fRec41[0] = fRec42[2] + fConst110 * (fTemp30 + fConst109 * fRec42[0]) - fConst51 * (fConst49 * fRec41[2] + fTemp29);
		fRec40[0] = fRec41[2] + fConst51 * (fTemp29 + fConst49 * fRec41[0]) - fConst43 * (fConst41 * fRec40[2] + fTemp28);
		fRec39[0] = fRec40[2] + fConst43 * (fTemp28 + fConst41 * fRec40[0]) - (fRec39[1] * fTemp3 + fRec39[2] * fTemp2) / fTemp1;
		double fTemp31 = fConst76 * fRec39[1];
		double fTemp32 = fRec8[0] * (fConst78 * fRec39[0] + fTemp31 + fConst75 * fRec39[2]) / fTemp1;
		fRec46[0] = -(fConst84 * (fConst83 * fRec46[1] - (fRec31[1] + fRec31[2])));
		double fTemp33 = fRec46[0] * fRec18[0];
		fVec5[0] = fTemp33;
		fRec45[0] = fConst86 * (fConst85 * (fTemp33 - fVec5[1]) - fConst81 * fRec45[1]);
		fRec38[0] = fRec45[0] + ((signbit(fTemp32)) ? copicat1_negclip(fTemp32) : copicat1clip(fTemp32)) - fConst25 * (fConst24 * fRec38[1] + fConst23 * fRec38[2] + fConst21 * fRec38[3]);
		double fTemp34 = fConst25 * (fConst91 * fRec38[0] + fConst90 * fRec38[1] + fConst89 * fRec38[2] + fConst88 * fRec38[3]);
		fRec37[0] = ((signbit(fTemp34)) ? copicatrecord_2_negclip(fTemp34) : copicatrecord_2clip(fTemp34)) - fConst19 * (fConst17 * fRec37[2] + fConst12 * fRec37[1]);
		fRec36[0] = fConst92 * (fRec37[2] + (fRec37[0] - 2.0 * fRec37[1])) - fConst16 * (fConst14 * fRec36[2] + fConst12 * fRec36[1]);
		double fTemp35 = fRec36[2] + (fRec36[0] - 2.0 * fRec36[1]);
		fVec6[IOTA0 & 1048575] = fTemp35;
		double fTemp36 = fVec6[(IOTA0 - iTemp15) & 1048575];
		double fTemp37 = fVec6[(IOTA0 - iTemp19) & 1048575];
		double fTemp38 = fVec6[(IOTA0 - iTemp23) & 1048575];
		double fTemp39 = fSlow8 * (fTemp38 - fRec28[0] * (fTemp38 - fVec6[(IOTA0 - iTemp22) & 1048575])) + fSlow6 * (fTemp37 - fRec24[0] * (fTemp37 - fVec6[(IOTA0 - iTemp18) & 1048575])) + fSlow4 * (fTemp36 - fRec20[0] * (fTemp36 - fVec6[(IOTA0 - iTemp14) & 1048575]));
		fVec7[0] = fTemp39;
		fRec35[0] = -(fConst100 * (fConst99 * fRec35[1] - fConst97 * (fTemp39 + fVec7[1])));
		fRec34[0] = fRec35[0] + 0.995 * fRec34[1] - fRec35[1];
		fRec33[0] = fRec34[0] - fConst9 * (fConst8 * fRec33[1] + fConst7 * fRec33[2]);
		double fTemp40 = fConst9 * (fConst104 * fRec33[0] + fConst103 * fRec33[1] + fConst102 * fRec33[2]);
		fRec32[0] = ((signbit(fTemp40)) ? copicatreplay1_negclip(fTemp40) : copicatreplay1clip(fTemp40)) - fConst5 * (fConst4 * fRec32[1] + fConst2 * fRec32[2]);
		double fTemp41 = fConst5 * (fConst108 * fRec32[0] + fConst107 * fRec32[1] + fConst106 * fRec32[2]);
		fRec31[0] = ((signbit(fTemp41)) ? copicatreplay2_negclip(fTemp41) : copicatreplay2clip(fTemp41));
		double fTemp42 = fConst38 * fRec56[1];
		fRec60[0] = -(fConst71 * (fConst69 * fRec60[1] - fConst65 * (fTemp7 + fVec1[1])));
		fRec59[0] = fRec60[0] - fConst58 * (fConst56 * fRec59[2] + fConst54 * fRec59[1]);
		double fTemp43 = fRec59[2] + fRec59[0] + 2.0 * fRec59[1];
		fVec8[0] = fTemp43;
		fRec58[0] = -(fConst116 * (fConst48 * fRec58[1] - fConst115 * (fTemp43 - fVec8[1])));
		fRec57[0] = fRec58[0] - fConst114 * (fConst112 * fRec57[2] + fConst46 * fRec57[1]);
		fRec56[0] = fConst117 * (fRec57[2] + (fRec57[0] - 2.0 * fRec57[1])) - fConst43 * (fConst41 * fRec56[2] + fTemp42);
		fRec55[0] = fRec56[2] + fConst43 * (fTemp42 + fConst41 * fRec56[0]) - (fTemp3 * fRec55[1] + fTemp2 * fRec55[2]) / fTemp1;
		double fTemp44 = fConst76 * fRec55[1];
		double fTemp45 = fRec8[0] * (fConst78 * fRec55[0] + fTemp44 + fConst75 * fRec55[2]) / fTemp1;
		fRec62[0] = -(fConst84 * (fConst83 * fRec62[1] - (fRec47[1] + fRec47[2])));
		double fTemp46 = fRec18[0] * fRec62[0];
		fVec9[0] = fTemp46;
		fRec61[0] = fConst86 * (fConst85 * (fTemp46 - fVec9[1]) - fConst81 * fRec61[1]);
		fRec54[0] = fRec61[0] + ((signbit(fTemp45)) ? copicat1_negclip(fTemp45) : copicat1clip(fTemp45)) - fConst25 * (fConst24 * fRec54[1] + fConst23 * fRec54[2] + fConst21 * fRec54[3]);
		double fTemp47 = fConst25 * (fConst91 * fRec54[0] + fConst90 * fRec54[1] + fConst89 * fRec54[2] + fConst88 * fRec54[3]);
		fRec53[0] = ((signbit(fTemp47)) ? copicatrecord_2_negclip(fTemp47) : copicatrecord_2clip(fTemp47)) - fConst19 * (fConst17 * fRec53[2] + fConst12 * fRec53[1]);
		fRec52[0] = fConst92 * (fRec53[2] + (fRec53[0] - 2.0 * fRec53[1])) - fConst16 * (fConst14 * fRec52[2] + fConst12 * fRec52[1]);
		double fTemp48 = fRec52[2] + (fRec52[0] - 2.0 * fRec52[1]);
		fVec10[IOTA0 & 1048575] = fTemp48;
		double fTemp49 = fVec10[(IOTA0 - iTemp15) & 1048575];
		double fTemp50 = fVec10[(IOTA0 - iTemp19) & 1048575];
		double fTemp51 = fVec10[(IOTA0 - iTemp23) & 1048575];
		double fTemp52 = fSlow8 * (fTemp51 - fRec28[0] * (fTemp51 - fVec10[(IOTA0 - iTemp22) & 1048575])) + fSlow6 * (fTemp50 - fRec24[0] * (fTemp50 - fVec10[(IOTA0 - iTemp18) & 1048575])) + fSlow4 * (fTemp49 - fRec20[0] * (fTemp49 - fVec10[(IOTA0 - iTemp14) & 1048575]));
		fVec11[0] = fTemp52;
		fRec51[0] = -(fConst100 * (fConst99 * fRec51[1] - fConst97 * (fTemp52 + fVec11[1])));
		fRec50[0] = fRec51[0] + 0.995 * fRec50[1] - fRec51[1];
		fRec49[0] = fRec50[0] - fConst9 * (fConst8 * fRec49[1] + fConst7 * fRec49[2]);
		double fTemp53 = fConst9 * (fConst104 * fRec49[0] + fConst103 * fRec49[1] + fConst102 * fRec49[2]);
		fRec48[0] = ((signbit(fTemp53)) ? copicatreplay1_negclip(fTemp53) : copicatreplay1clip(fTemp53)) - fConst5 * (fConst4 * fRec48[1] + fConst2 * fRec48[2]);
		double fTemp54 = fConst5 * (fConst108 * fRec48[0] + fConst107 * fRec48[1] + fConst106 * fRec48[2]);
		fRec47[0] = ((signbit(fTemp54)) ? copicatreplay2_negclip(fTemp54) : copicatreplay2clip(fTemp54));
		fRec75[0] = -(fConst116 * (fConst48 * fRec75[1] - fConst58 * (fTemp43 + fVec8[1])));
		fRec74[0] = fRec75[0] - fConst114 * (fConst112 * fRec74[2] + fConst46 * fRec74[1]);
		double fTemp55 = fRec74[2] + fRec74[0] + 2.0 * fRec74[1];
		fVec12[0] = fTemp55;
		fRec73[0] = -(fConst122 * (fConst40 * fRec73[1] - fConst121 * (fTemp55 - fVec12[1])));
		fRec72[0] = fRec73[0] - fConst120 * (fConst118 * fRec72[2] + fConst38 * fRec72[1]);
		fRec71[0] = fConst123 * (fRec72[2] + (fRec72[0] - 2.0 * fRec72[1])) - (fTemp3 * fRec71[1] + fTemp2 * fRec71[2]) / fTemp1;
		double fTemp56 = fConst76 * fRec71[1];
		double fTemp57 = fRec8[0] * (fConst78 * fRec71[0] + fTemp56 + fConst75 * fRec71[2]) / fTemp1;
		fRec77[0] = -(fConst84 * (fConst83 * fRec77[1] - (fRec63[1] + fRec63[2])));
		double fTemp58 = fRec18[0] * fRec77[0];
		fVec13[0] = fTemp58;
		fRec76[0] = fConst86 * (fConst85 * (fTemp58 - fVec13[1]) - fConst81 * fRec76[1]);
		fRec70[0] = fRec76[0] + ((signbit(fTemp57)) ? copicat1_negclip(fTemp57) : copicat1clip(fTemp57)) - fConst25 * (fConst24 * fRec70[1] + fConst23 * fRec70[2] + fConst21 * fRec70[3]);
		double fTemp59 = fConst25 * (fConst91 * fRec70[0] + fConst90 * fRec70[1] + fConst89 * fRec70[2] + fConst88 * fRec70[3]);
		fRec69[0] = ((signbit(fTemp59)) ? copicatrecord_2_negclip(fTemp59) : copicatrecord_2clip(fTemp59)) - fConst19 * (fConst17 * fRec69[2] + fConst12 * fRec69[1]);
		fRec68[0] = fConst92 * (fRec69[2] + (fRec69[0] - 2.0 * fRec69[1])) - fConst16 * (fConst14 * fRec68[2] + fConst12 * fRec68[1]);
		double fTemp60 = fRec68[2] + (fRec68[0] - 2.0 * fRec68[1]);
		fVec14[IOTA0 & 1048575] = fTemp60;
		double fTemp61 = fVec14[(IOTA0 - iTemp15) & 1048575];
		double fTemp62 = fVec14[(IOTA0 - iTemp19) & 1048575];
		double fTemp63 = fVec14[(IOTA0 - iTemp23) & 1048575];
		double fTemp64 = fSlow8 * (fTemp63 - fRec28[0] * (fTemp63 - fVec14[(IOTA0 - iTemp22) & 1048575])) + fSlow6 * (fTemp62 - fRec24[0] * (fTemp62 - fVec14[(IOTA0 - iTemp18) & 1048575])) + fSlow4 * (fTemp61 - fRec20[0] * (fTemp61 - fVec14[(IOTA0 - iTemp14) & 1048575]));
		fVec15[0] = fTemp64;
		fRec67[0] = -(fConst100 * (fConst99 * fRec67[1] - fConst97 * (fTemp64 + fVec15[1])));
		fRec66[0] = fRec67[0] + 0.995 * fRec66[1] - fRec67[1];
		fRec65[0] = fRec66[0] - fConst9 * (fConst8 * fRec65[1] + fConst7 * fRec65[2]);
		double fTemp65 = fConst9 * (fConst104 * fRec65[0] + fConst103 * fRec65[1] + fConst102 * fRec65[2]);
		fRec64[0] = ((signbit(fTemp65)) ? copicatreplay1_negclip(fTemp65) : copicatreplay1clip(fTemp65)) - fConst5 * (fConst4 * fRec64[1] + fConst2 * fRec64[2]);
		double fTemp66 = fConst5 * (fConst108 * fRec64[0] + fConst107 * fRec64[1] + fConst106 * fRec64[2]);
		fRec63[0] = ((signbit(fTemp66)) ? copicatreplay2_negclip(fTemp66) : copicatreplay2clip(fTemp66));
		fRec88[0] = -(fConst122 * (fConst40 * fRec88[1] - fConst114 * (fTemp55 + fVec12[1])));
		fRec87[0] = fRec88[0] - fConst120 * (fConst118 * fRec87[2] + fConst38 * fRec87[1]);
		fRec86[0] = fConst120 * (fRec87[2] + fRec87[0] + 2.0 * fRec87[1]) - (fTemp3 * fRec86[1] + fTemp2 * fRec86[2]) / fTemp1;
		double fTemp67 = fConst76 * fRec86[1];
		double fTemp68 = fRec8[0] * (fConst78 * fRec86[0] + fTemp67 + fConst75 * fRec86[2]) / fTemp1;
		fRec90[0] = -(fConst84 * (fConst83 * fRec90[1] - (fRec78[1] + fRec78[2])));
		double fTemp69 = fRec18[0] * fRec90[0];
		fVec16[0] = fTemp69;
		fRec89[0] = fConst86 * (fConst85 * (fTemp69 - fVec16[1]) - fConst81 * fRec89[1]);
		fRec85[0] = fRec89[0] + ((signbit(fTemp68)) ? copicat1_negclip(fTemp68) : copicat1clip(fTemp68)) - fConst25 * (fConst24 * fRec85[1] + fConst23 * fRec85[2] + fConst21 * fRec85[3]);
		double fTemp70 = fConst25 * (fConst91 * fRec85[0] + fConst90 * fRec85[1] + fConst89 * fRec85[2] + fConst88 * fRec85[3]);
		fRec84[0] = ((signbit(fTemp70)) ? copicatrecord_2_negclip(fTemp70) : copicatrecord_2clip(fTemp70)) - fConst19 * (fConst17 * fRec84[2] + fConst12 * fRec84[1]);
		fRec83[0] = fConst92 * (fRec84[2] + (fRec84[0] - 2.0 * fRec84[1])) - fConst16 * (fConst14 * fRec83[2] + fConst12 * fRec83[1]);
		double fTemp71 = fRec83[2] + (fRec83[0] - 2.0 * fRec83[1]);
		fVec17[IOTA0 & 1048575] = fTemp71;
		double fTemp72 = fVec17[(IOTA0 - iTemp15) & 1048575];
		double fTemp73 = fVec17[(IOTA0 - iTemp19) & 1048575];
		double fTemp74 = fVec17[(IOTA0 - iTemp23) & 1048575];
		double fTemp75 = fSlow8 * (fTemp74 - fRec28[0] * (fTemp74 - fVec17[(IOTA0 - iTemp22) & 1048575])) + fSlow6 * (fTemp73 + fRec24[0] * (fVec17[(IOTA0 - iTemp18) & 1048575] - fTemp73)) + fSlow4 * (fTemp72 - fRec20[0] * (fTemp72 - fVec17[(IOTA0 - iTemp14) & 1048575]));
		fVec18[0] = fTemp75;
		fRec82[0] = -(fConst100 * (fConst99 * fRec82[1] - fConst97 * (fTemp75 + fVec18[1])));
		fRec81[0] = fRec82[0] + 0.995 * fRec81[1] - fRec82[1];
		fRec80[0] = fRec81[0] - fConst9 * (fConst8 * fRec80[1] + fConst7 * fRec80[2]);
		double fTemp76 = fConst9 * (fConst104 * fRec80[0] + fConst103 * fRec80[1] + fConst102 * fRec80[2]);
		fRec79[0] = ((signbit(fTemp76)) ? copicatreplay1_negclip(fTemp76) : copicatreplay1clip(fTemp76)) - fConst5 * (fConst4 * fRec79[1] + fConst2 * fRec79[2]);
		double fTemp77 = fConst5 * (fConst108 * fRec79[0] + fConst107 * fRec79[1] + fConst106 * fRec79[2]);
		fRec78[0] = ((signbit(fTemp77)) ? copicatreplay2_negclip(fTemp77) : copicatreplay2clip(fTemp77));
		fRec91[0] = fSlow9 + 0.993 * fRec91[1];
		double fTemp78 = fConst31 + fRec8[0] * (fConst0 * (fConst28 + fTemp0 + 5.0418669893366e-09) + 6.26916098134342e-08) + 3.09696552478371e-07;
		double fTemp79 = fRec8[0] * (fTemp67 + fConst0 * (fConst77 * fRec86[0] + fConst74 * fRec86[2])) / fTemp78;
		double fTemp80 = fRec8[0] * (fTemp56 + fConst0 * (fConst77 * fRec71[0] + fConst74 * fRec71[2])) / fTemp78;
		double fTemp81 = fRec8[0] * (fTemp44 + fConst0 * (fConst77 * fRec55[0] + fConst74 * fRec55[2])) / fTemp78;
		double fTemp82 = fRec8[0] * (fTemp8 + fConst0 * (fConst77 * fRec9[0] + fConst74 * fRec9[2])) / fTemp78;
		double fTemp83 = fRec8[0] * (fTemp31 + fConst0 * (fConst77 * fRec39[0] + fConst74 * fRec39[2])) / fTemp78;
		fRec92[0] = fSlow10 + 0.993 * fRec92[1];
		output0[i0] = FAUSTFLOAT(fRec92[0] * (((signbit(fTemp83)) ? copicat1_negclip(fTemp83) : copicat1clip(fTemp83)) + ((signbit(fTemp82)) ? copicat1_negclip(fTemp82) : copicat1clip(fTemp82)) + ((signbit(fTemp81)) ? copicat1_negclip(fTemp81) : copicat1clip(fTemp81)) + ((signbit(fTemp80)) ? copicat1_negclip(fTemp80) : copicat1clip(fTemp80)) + ((signbit(fTemp79)) ? copicat1_negclip(fTemp79) : copicat1clip(fTemp79)) + 0.25 * fRec91[0] * (fRec78[0] + fRec63[0] + fRec47[0] + fRec31[0] + fRec0[0])));
		fRec8[1] = fRec8[0];
		fVec0[1] = fVec0[0];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fVec1[1] = fVec1[0];
		fRec13[1] = fRec13[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fVec2[1] = fVec2[0];
		fRec16[1] = fRec16[0];
		for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
			fRec7[j0] = fRec7[j0 - 1];
		}
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		IOTA0 = IOTA0 + 1;
		fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
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
		fVec4[1] = fVec4[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		fRec44[1] = fRec44[0];
		fRec43[2] = fRec43[1];
		fRec43[1] = fRec43[0];
		fRec42[2] = fRec42[1];
		fRec42[1] = fRec42[0];
		fRec41[2] = fRec41[1];
		fRec41[1] = fRec41[0];
		fRec40[2] = fRec40[1];
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fRec46[1] = fRec46[0];
		fVec5[1] = fVec5[0];
		fRec45[1] = fRec45[0];
		for (int j1 = 3; j1 > 0; j1 = j1 - 1) {
			fRec38[j1] = fRec38[j1 - 1];
		}
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		fVec7[1] = fVec7[0];
		fRec35[1] = fRec35[0];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fRec60[1] = fRec60[0];
		fRec59[2] = fRec59[1];
		fRec59[1] = fRec59[0];
		fVec8[1] = fVec8[0];
		fRec58[1] = fRec58[0];
		fRec57[2] = fRec57[1];
		fRec57[1] = fRec57[0];
		fRec56[2] = fRec56[1];
		fRec56[1] = fRec56[0];
		fRec55[2] = fRec55[1];
		fRec55[1] = fRec55[0];
		fRec62[1] = fRec62[0];
		fVec9[1] = fVec9[0];
		fRec61[1] = fRec61[0];
		for (int j2 = 3; j2 > 0; j2 = j2 - 1) {
			fRec54[j2] = fRec54[j2 - 1];
		}
		fRec53[2] = fRec53[1];
		fRec53[1] = fRec53[0];
		fRec52[2] = fRec52[1];
		fRec52[1] = fRec52[0];
		fVec11[1] = fVec11[0];
		fRec51[1] = fRec51[0];
		fRec50[1] = fRec50[0];
		fRec49[2] = fRec49[1];
		fRec49[1] = fRec49[0];
		fRec48[2] = fRec48[1];
		fRec48[1] = fRec48[0];
		fRec47[2] = fRec47[1];
		fRec47[1] = fRec47[0];
		fRec75[1] = fRec75[0];
		fRec74[2] = fRec74[1];
		fRec74[1] = fRec74[0];
		fVec12[1] = fVec12[0];
		fRec73[1] = fRec73[0];
		fRec72[2] = fRec72[1];
		fRec72[1] = fRec72[0];
		fRec71[2] = fRec71[1];
		fRec71[1] = fRec71[0];
		fRec77[1] = fRec77[0];
		fVec13[1] = fVec13[0];
		fRec76[1] = fRec76[0];
		for (int j3 = 3; j3 > 0; j3 = j3 - 1) {
			fRec70[j3] = fRec70[j3 - 1];
		}
		fRec69[2] = fRec69[1];
		fRec69[1] = fRec69[0];
		fRec68[2] = fRec68[1];
		fRec68[1] = fRec68[0];
		fVec15[1] = fVec15[0];
		fRec67[1] = fRec67[0];
		fRec66[1] = fRec66[0];
		fRec65[2] = fRec65[1];
		fRec65[1] = fRec65[0];
		fRec64[2] = fRec64[1];
		fRec64[1] = fRec64[0];
		fRec63[2] = fRec63[1];
		fRec63[1] = fRec63[0];
		fRec88[1] = fRec88[0];
		fRec87[2] = fRec87[1];
		fRec87[1] = fRec87[0];
		fRec86[2] = fRec86[1];
		fRec86[1] = fRec86[0];
		fRec90[1] = fRec90[0];
		fVec16[1] = fVec16[0];
		fRec89[1] = fRec89[0];
		for (int j4 = 3; j4 > 0; j4 = j4 - 1) {
			fRec85[j4] = fRec85[j4 - 1];
		}
		fRec84[2] = fRec84[1];
		fRec84[1] = fRec84[0];
		fRec83[2] = fRec83[1];
		fRec83[1] = fRec83[0];
		fVec18[1] = fVec18[0];
		fRec82[1] = fRec82[0];
		fRec81[1] = fRec81[0];
		fRec80[2] = fRec80[1];
		fRec80[1] = fRec80[0];
		fRec79[2] = fRec79[1];
		fRec79[1] = fRec79[0];
		fRec78[2] = fRec78[1];
		fRec78[1] = fRec78[0];
		fRec91[1] = fRec91[0];
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
	case AUDIO_IN: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case SUSTAIN: 
		fVslider1_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case SWELL: 
		fVslider3_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
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
   AUDIO_IN, 
   SUSTAIN, 
   SWELL, 
   OUTPUT, 
   BPM, 
   HEAD1, 
   HEAD2, 
   HEAD3, 
} PortIndex;
*/

} // end namespace gxechocat
