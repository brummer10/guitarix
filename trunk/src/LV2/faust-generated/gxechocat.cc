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
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	double fConst0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec1[2];
	double fConst2;
	double fConst4;
	double fConst5;
	double fConst7;
	double fConst9;
	double fVec0[2];
	double fConst10;
	double fConst11;
	double fRec7[2];
	double fConst12;
	double fConst13;
	double fRec6[3];
	double fConst14;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst22;
	double fConst23;
	double fRec5[3];
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst31;
	double fConst32;
	double fRec4[3];
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst40;
	double fConst41;
	double fRec3[3];
	double fConst42;
	double fConst43;
	double fConst45;
	double fConst47;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fRec2[3];
	double fConst53;
	double fConst54;
	double fConst57;
	double fConst59;
	double fConst62;
	double fConst64;
	double fConst66;
	double fConst67;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst70;
	double fConst72;
	double fConst73;
	double fConst75;
	double fConst77;
	double fConst81;
	double fConst83;
	double fConst84;
	double fRec17[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec18[2];
	double fVec1[2];
	double fConst85;
	double fConst86;
	double fRec16[2];
	double fConst88;
	double fConst89;
	double fConst90;
	double fRec15[4];
	double fConst91;
	double fConst92;
	double fConst93;
	double fConst94;
	double fConst95;
	double fRec14[3];
	double fConst96;
	double fConst97;
	double fRec13[3];
	int IOTA;
	double *fVec2;
	double fConst98;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fConst99;
	double fConst100;
	double fRec19[2];
	double fRec20[2];
	double fRec21[2];
	double fRec22[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	double fConst101;
	double fRec23[2];
	double fRec24[2];
	double fRec25[2];
	double fRec26[2];
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT	*fCheckbox2_;
	double fConst102;
	double fRec27[2];
	double fRec28[2];
	double fRec29[2];
	double fRec30[2];
	double fVec3[2];
	double fRec12[2];
	double fRec11[2];
	double fConst103;
	double fConst104;
	double fConst105;
	double fRec10[3];
	double fConst106;
	double fConst107;
	double fConst108;
	double fConst109;
	double fConst110;
	double fRec9[3];
	double fConst111;
	double fConst112;
	double fRec8[3];
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	double fRec31[2];
	double fConst113;
	double fConst114;
	double fRec38[2];
	double fRec37[3];
	double fVec4[2];
	double fConst115;
	double fConst116;
	double fRec36[2];
	double fConst117;
	double fRec35[3];
	double fConst118;
	double fRec34[3];
	double fRec33[3];
	double fRec32[3];
	double fRec48[2];
	double fVec5[2];
	double fRec47[2];
	double fRec46[4];
	double fRec45[3];
	double fRec44[3];
	double *fVec6;
	double fVec7[2];
	double fRec43[2];
	double fRec42[2];
	double fRec41[3];
	double fRec40[3];
	double fRec39[3];
	double fConst119;
	double fConst120;
	double fConst121;
	double fRec54[2];
	double fRec53[3];
	double fVec8[2];
	double fConst122;
	double fConst123;
	double fRec52[2];
	double fConst124;
	double fRec51[3];
	double fConst125;
	double fRec50[3];
	double fRec49[3];
	double fRec64[2];
	double fVec9[2];
	double fRec63[2];
	double fRec62[4];
	double fRec61[3];
	double fRec60[3];
	double *fVec10;
	double fVec11[2];
	double fRec59[2];
	double fRec58[2];
	double fRec57[3];
	double fRec56[3];
	double fRec55[3];
	double fConst126;
	double fConst127;
	double fConst128;
	double fRec69[2];
	double fRec68[3];
	double fVec12[2];
	double fConst129;
	double fConst130;
	double fRec67[2];
	double fConst131;
	double fRec66[3];
	double fConst132;
	double fRec65[3];
	double fRec79[2];
	double fVec13[2];
	double fRec78[2];
	double fRec77[4];
	double fRec76[3];
	double fRec75[3];
	double *fVec14;
	double fVec15[2];
	double fRec74[2];
	double fRec73[2];
	double fRec72[3];
	double fRec71[3];
	double fRec70[3];
	double fConst133;
	double fRec82[2];
	double fRec81[3];
	double fRec80[3];
	double fRec92[2];
	double fVec16[2];
	double fRec91[2];
	double fRec90[4];
	double fRec89[3];
	double fRec88[3];
	double *fVec17;
	double fVec18[2];
	double fRec87[2];
	double fRec86[2];
	double fRec85[3];
	double fRec84[3];
	double fRec83[3];

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
	  fVec2(0),
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec1[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fVec0[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec7[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec6[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec5[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec4[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRec3[l7] = 0.0;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec2[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec17[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec18[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fVec1[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec16[l12] = 0.0;
	for (int l13 = 0; (l13 < 4); l13 = (l13 + 1)) fRec15[l13] = 0.0;
	for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) fRec14[l14] = 0.0;
	for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) fRec13[l15] = 0.0;
	for (int l16 = 0; (l16 < 1048576); l16 = (l16 + 1)) fVec2[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec19[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec20[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec21[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fRec22[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec23[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fRec24[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fRec25[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec26[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fRec27[l25] = 0.0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fRec28[l26] = 0.0;
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) fRec29[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec30[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fVec3[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec12[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fRec11[l31] = 0.0;
	for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) fRec10[l32] = 0.0;
	for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) fRec9[l33] = 0.0;
	for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) fRec8[l34] = 0.0;
	for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) fRec31[l35] = 0.0;
	for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) fRec38[l36] = 0.0;
	for (int l37 = 0; (l37 < 3); l37 = (l37 + 1)) fRec37[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fVec4[l38] = 0.0;
	for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) fRec36[l39] = 0.0;
	for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) fRec35[l40] = 0.0;
	for (int l41 = 0; (l41 < 3); l41 = (l41 + 1)) fRec34[l41] = 0.0;
	for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) fRec33[l42] = 0.0;
	for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) fRec32[l43] = 0.0;
	for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) fRec48[l44] = 0.0;
	for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) fVec5[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec47[l46] = 0.0;
	for (int l47 = 0; (l47 < 4); l47 = (l47 + 1)) fRec46[l47] = 0.0;
	for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) fRec45[l48] = 0.0;
	for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) fRec44[l49] = 0.0;
	for (int l50 = 0; (l50 < 1048576); l50 = (l50 + 1)) fVec6[l50] = 0.0;
	for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) fVec7[l51] = 0.0;
	for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) fRec43[l52] = 0.0;
	for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) fRec42[l53] = 0.0;
	for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) fRec41[l54] = 0.0;
	for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) fRec40[l55] = 0.0;
	for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) fRec39[l56] = 0.0;
	for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) fRec54[l57] = 0.0;
	for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) fRec53[l58] = 0.0;
	for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) fVec8[l59] = 0.0;
	for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) fRec52[l60] = 0.0;
	for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) fRec51[l61] = 0.0;
	for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) fRec50[l62] = 0.0;
	for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) fRec49[l63] = 0.0;
	for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) fRec64[l64] = 0.0;
	for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) fVec9[l65] = 0.0;
	for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) fRec63[l66] = 0.0;
	for (int l67 = 0; (l67 < 4); l67 = (l67 + 1)) fRec62[l67] = 0.0;
	for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) fRec61[l68] = 0.0;
	for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) fRec60[l69] = 0.0;
	for (int l70 = 0; (l70 < 1048576); l70 = (l70 + 1)) fVec10[l70] = 0.0;
	for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) fVec11[l71] = 0.0;
	for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) fRec59[l72] = 0.0;
	for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) fRec58[l73] = 0.0;
	for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) fRec57[l74] = 0.0;
	for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) fRec56[l75] = 0.0;
	for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) fRec55[l76] = 0.0;
	for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) fRec69[l77] = 0.0;
	for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) fRec68[l78] = 0.0;
	for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) fVec12[l79] = 0.0;
	for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) fRec67[l80] = 0.0;
	for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) fRec66[l81] = 0.0;
	for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) fRec65[l82] = 0.0;
	for (int l83 = 0; (l83 < 2); l83 = (l83 + 1)) fRec79[l83] = 0.0;
	for (int l84 = 0; (l84 < 2); l84 = (l84 + 1)) fVec13[l84] = 0.0;
	for (int l85 = 0; (l85 < 2); l85 = (l85 + 1)) fRec78[l85] = 0.0;
	for (int l86 = 0; (l86 < 4); l86 = (l86 + 1)) fRec77[l86] = 0.0;
	for (int l87 = 0; (l87 < 3); l87 = (l87 + 1)) fRec76[l87] = 0.0;
	for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) fRec75[l88] = 0.0;
	for (int l89 = 0; (l89 < 1048576); l89 = (l89 + 1)) fVec14[l89] = 0.0;
	for (int l90 = 0; (l90 < 2); l90 = (l90 + 1)) fVec15[l90] = 0.0;
	for (int l91 = 0; (l91 < 2); l91 = (l91 + 1)) fRec74[l91] = 0.0;
	for (int l92 = 0; (l92 < 2); l92 = (l92 + 1)) fRec73[l92] = 0.0;
	for (int l93 = 0; (l93 < 3); l93 = (l93 + 1)) fRec72[l93] = 0.0;
	for (int l94 = 0; (l94 < 3); l94 = (l94 + 1)) fRec71[l94] = 0.0;
	for (int l95 = 0; (l95 < 3); l95 = (l95 + 1)) fRec70[l95] = 0.0;
	for (int l96 = 0; (l96 < 2); l96 = (l96 + 1)) fRec82[l96] = 0.0;
	for (int l97 = 0; (l97 < 3); l97 = (l97 + 1)) fRec81[l97] = 0.0;
	for (int l98 = 0; (l98 < 3); l98 = (l98 + 1)) fRec80[l98] = 0.0;
	for (int l99 = 0; (l99 < 2); l99 = (l99 + 1)) fRec92[l99] = 0.0;
	for (int l100 = 0; (l100 < 2); l100 = (l100 + 1)) fVec16[l100] = 0.0;
	for (int l101 = 0; (l101 < 2); l101 = (l101 + 1)) fRec91[l101] = 0.0;
	for (int l102 = 0; (l102 < 4); l102 = (l102 + 1)) fRec90[l102] = 0.0;
	for (int l103 = 0; (l103 < 3); l103 = (l103 + 1)) fRec89[l103] = 0.0;
	for (int l104 = 0; (l104 < 3); l104 = (l104 + 1)) fRec88[l104] = 0.0;
	for (int l105 = 0; (l105 < 1048576); l105 = (l105 + 1)) fVec17[l105] = 0.0;
	for (int l106 = 0; (l106 < 2); l106 = (l106 + 1)) fVec18[l106] = 0.0;
	for (int l107 = 0; (l107 < 2); l107 = (l107 + 1)) fRec87[l107] = 0.0;
	for (int l108 = 0; (l108 < 2); l108 = (l108 + 1)) fRec86[l108] = 0.0;
	for (int l109 = 0; (l109 < 3); l109 = (l109 + 1)) fRec85[l109] = 0.0;
	for (int l110 = 0; (l110 < 3); l110 = (l110 + 1)) fRec84[l110] = 0.0;
	for (int l111 = 0; (l111 < 3); l111 = (l111 + 1)) fRec83[l111] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = (2.06740841499587e-08 * fConst0);
	fConst2 = (-5.51308910665569e-07 - fConst1);
	double fConst3 = std::tan((20517.741620594938 / fConst0));
	fConst4 = (1.0 / fConst3);
	fConst5 = (1.0 / (((fConst4 + 1.0000000000000004) / fConst3) + 1.0));
	double fConst6 = mydsp_faustpower2_f(fConst3);
	fConst7 = (1.0 / fConst6);
	double fConst8 = (fConst4 + 1.0);
	fConst9 = (0.0 - (1.0 / (fConst3 * fConst8)));
	fConst10 = (1.0 / fConst8);
	fConst11 = (1.0 - fConst4);
	fConst12 = (((fConst4 + -1.0000000000000004) / fConst3) + 1.0);
	fConst13 = (2.0 * (1.0 - fConst7));
	fConst14 = (0.0 - (2.0 / fConst6));
	double fConst15 = std::tan((3769.9111843077517 / fConst0));
	double fConst16 = (1.0 / fConst15);
	double fConst17 = (fConst16 + 1.0);
	fConst18 = (1.0 / ((fConst17 / fConst15) + 1.0));
	fConst19 = (1.0 - fConst16);
	fConst20 = (1.0 - (fConst19 / fConst15));
	double fConst21 = mydsp_faustpower2_f(fConst15);
	fConst22 = (1.0 / fConst21);
	fConst23 = (2.0 * (1.0 - fConst22));
	double fConst24 = std::tan((659.73445725385659 / fConst0));
	double fConst25 = (1.0 / fConst24);
	double fConst26 = (fConst25 + 1.0);
	fConst27 = (1.0 / ((fConst26 / fConst24) + 1.0));
	fConst28 = (1.0 - fConst25);
	fConst29 = (1.0 - (fConst28 / fConst24));
	double fConst30 = mydsp_faustpower2_f(fConst24);
	fConst31 = (1.0 / fConst30);
	fConst32 = (2.0 * (1.0 - fConst31));
	double fConst33 = std::tan((270.1769682087222 / fConst0));
	double fConst34 = (1.0 / fConst33);
	double fConst35 = (fConst34 + 1.0);
	fConst36 = (1.0 / ((fConst35 / fConst33) + 1.0));
	fConst37 = (1.0 - fConst34);
	fConst38 = (1.0 - (fConst37 / fConst33));
	double fConst39 = mydsp_faustpower2_f(fConst33);
	fConst40 = (1.0 / fConst39);
	fConst41 = (2.0 * (1.0 - fConst40));
	fConst42 = mydsp_faustpower2_f(fConst0);
	fConst43 = (8.2285014683193098e-10 * fConst42);
	double fConst44 = (4.1142507341596497e-10 * fConst0);
	fConst45 = (fConst0 * (fConst44 + -2.4906822927323298e-08));
	double fConst46 = (8.3284427816995498e-11 * fConst0);
	fConst47 = (fConst46 + -5.0418669893366e-09);
	double fConst48 = (7.8378972882444297e-11 * fConst0);
	fConst49 = (3.13458049067171e-09 - fConst48);
	fConst50 = (fConst0 * (fConst44 + 2.4906822927323298e-08));
	fConst51 = (fConst46 + 5.0418669893366e-09);
	fConst52 = (-3.13458049067171e-09 - fConst48);
	fConst53 = (4.1348168299917401e-08 * fConst0);
	fConst54 = (5.51308910665569e-07 - fConst1);
	double fConst55 = (4.3361242466424001e-10 * fConst0);
	double fConst56 = ((fConst0 * (fConst55 + 1.9932993616135301e-08)) + 1.8988001703518899e-07);
	fConst57 = (fConst0 / fConst56);
	double fConst58 = (1.02325156488485e-09 * fConst0);
	fConst59 = (-1.0570780628975901e-08 - fConst58);
	double fConst60 = (4.3378578048241502e-10 * fConst0);
	double fConst61 = ((fConst0 * (fConst60 + 1.16144315716444e-08)) + 6.9053076645513103e-08);
	fConst62 = (fConst0 / fConst61);
	double fConst63 = (2.1646132460019299e-08 * fConst0);
	fConst64 = (-1.3118868157587301e-07 - fConst63);
	double fConst65 = (1.0 / std::tan((20420.352248333656 / fConst0)));
	fConst66 = (1.0 / (fConst65 + 1.0));
	fConst67 = (1.0 - fConst65);
	double fConst68 = std::tan((125.66370614359172 / fConst0));
	double fConst69 = (1.0 / fConst68);
	fConst70 = (1.0 / (((fConst69 + 0.76536686473017945) / fConst68) + 1.0));
	double fConst71 = mydsp_faustpower2_f(fConst68);
	fConst72 = (1.0 / fConst71);
	fConst73 = (1.0 / (((fConst69 + 1.8477590650225735) / fConst68) + 1.0));
	double fConst74 = (6.73029102377671e-15 * fConst0);
	fConst75 = (1.0 / ((fConst0 * ((fConst0 * (fConst74 + 1.10493997854221e-10)) + 2.3018384314765601e-08)) + 6.0159525272688304e-07));
	double fConst76 = (1.23938408071082e-08 * fConst0);
	fConst77 = ((fConst0 * (-7.13052376187718e-07 - fConst76)) + -9.9879581159544601e-06);
	double fConst78 = std::tan((471.23889803846896 / fConst0));
	double fConst79 = (1.0 / fConst78);
	double fConst80 = (fConst79 + 1.0);
	fConst81 = (1.0 / (fConst78 * fConst80));
	double fConst82 = (1.0 / std::tan((23561.944901923449 / fConst0)));
	fConst83 = (1.0 / (fConst82 + 1.0));
	fConst84 = (1.0 - fConst82);
	fConst85 = (0.0 - fConst81);
	fConst86 = ((1.0 - fConst79) / fConst80);
	double fConst87 = (2.0190873071330101e-14 * fConst0);
	fConst88 = ((fConst0 * ((fConst0 * (-1.10493997854221e-10 - fConst87)) + 2.3018384314765601e-08)) + 1.80478575818065e-06);
	fConst89 = ((fConst0 * ((fConst0 * (fConst87 + -1.10493997854221e-10)) + -2.3018384314765601e-08)) + 1.80478575818065e-06);
	fConst90 = ((fConst0 * ((fConst0 * (1.10493997854221e-10 - fConst74)) + -2.3018384314765601e-08)) + 6.0159525272688304e-07);
	fConst91 = ((fConst0 * (fConst76 + -7.13052376187718e-07)) + -2.9963874347863399e-05);
	fConst92 = ((fConst0 * (fConst76 + 7.13052376187718e-07)) + -2.9963874347863399e-05);
	fConst93 = ((fConst0 * (7.13052376187718e-07 - fConst76)) + -9.9879581159544601e-06);
	fConst94 = (((fConst69 + -1.8477590650225735) / fConst68) + 1.0);
	fConst95 = (2.0 * (1.0 - fConst72));
	fConst96 = (0.0 - (2.0 / fConst71));
	fConst97 = (((fConst69 + -0.76536686473017945) / fConst68) + 1.0);
	fConst98 = (30.0 * fConst0);
	fConst99 = (10.0 / fConst0);
	fConst100 = (0.0 - fConst99);
	fConst101 = (60.0 * fConst0);
	fConst102 = (90.0 * fConst0);
	fConst103 = (1.0 / fConst61);
	fConst104 = (1.3810615329102599e-07 - (8.6757156096483004e-10 * fConst42));
	fConst105 = ((fConst0 * (fConst60 + -1.16144315716444e-08)) + 6.9053076645513103e-08);
	fConst106 = (4.3292264920038597e-08 * fConst0);
	fConst107 = (1.3118868157587301e-07 - fConst63);
	fConst108 = (1.0 / fConst56);
	fConst109 = (3.7976003407037899e-07 - (8.6722484932848002e-10 * fConst42));
	fConst110 = ((fConst0 * (fConst55 + -1.9932993616135301e-08)) + 1.8988001703518899e-07);
	fConst111 = (2.0465031297697001e-09 * fConst0);
	fConst112 = (1.0570780628975901e-08 - fConst58);
	fConst113 = (1.0 / (((fConst16 + 1.0000000000000004) / fConst15) + 1.0));
	fConst114 = (1.0 / (fConst15 * fConst17));
	fConst115 = (0.0 - fConst114);
	fConst116 = (fConst19 / fConst17);
	fConst117 = (((fConst16 + -1.0000000000000004) / fConst15) + 1.0);
	fConst118 = (0.0 - (2.0 / fConst21));
	fConst119 = (1.0 / (((fConst25 + 1.0000000000000004) / fConst24) + 1.0));
	fConst120 = (1.0 / (fConst24 * fConst26));
	fConst121 = (1.0 / fConst17);
	fConst122 = (0.0 - fConst120);
	fConst123 = (fConst28 / fConst26);
	fConst124 = (((fConst25 + -1.0000000000000004) / fConst24) + 1.0);
	fConst125 = (0.0 - (2.0 / fConst30));
	fConst126 = (1.0 / (((fConst34 + 1.0000000000000004) / fConst33) + 1.0));
	fConst127 = (1.0 / (fConst33 * fConst35));
	fConst128 = (1.0 / fConst26);
	fConst129 = (0.0 - fConst127);
	fConst130 = (fConst37 / fConst35);
	fConst131 = (((fConst34 + -1.0000000000000004) / fConst33) + 1.0);
	fConst132 = (0.0 - (2.0 / fConst39));
	fConst133 = (1.0 / fConst35);
	IOTA = 0;
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void Dsp::mem_alloc()
{
	if (!fVec2) fVec2 = new double[1048576];
	if (!fVec6) fVec6 = new double[1048576];
	if (!fVec10) fVec10 = new double[1048576];
	if (!fVec14) fVec14 = new double[1048576];
	if (!fVec17) fVec17 = new double[1048576];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec2) { delete fVec2; fVec2 = 0; }
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
#define fCheckbox0 (*fCheckbox0_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
#define fCheckbox1 (*fCheckbox1_)
#define fCheckbox2 (*fCheckbox2_)
#define fVslider4 (*fVslider4_)
	double fSlow0 = (0.00036676987543879196 * (std::exp((3.0 * double(fVslider0))) + -1.0));
	double fSlow1 = (0.0070000000000000062 * double(fVslider1));
	double fSlow2 = double(fCheckbox0);
	double fSlow3 = (0.004073836948085289 * (std::exp(double(fVslider2)) + -1.0));
	double fSlow4 = double(fVslider3);
	double fSlow5 = (fConst98 / fSlow4);
	double fSlow6 = double(fCheckbox1);
	double fSlow7 = (fConst101 / fSlow4);
	double fSlow8 = double(fCheckbox2);
	double fSlow9 = (fConst102 / fSlow4);
	double fSlow10 = (0.004073836948085289 * (std::exp(double(fVslider4)) + -1.0));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		fRec0[0] = (fSlow0 + (0.99299999999999999 * fRec0[1]));
		fRec1[0] = (fSlow1 + (0.99299999999999999 * fRec1[1]));
		double fTemp0 = double(input0[i0]);
		fVec0[0] = fTemp0;
		fRec7[0] = ((fConst9 * fVec0[1]) - (fConst10 * ((fConst11 * fRec7[1]) - (fConst4 * fTemp0))));
		fRec6[0] = (fRec7[0] - (fConst5 * ((fConst12 * fRec6[2]) + (fConst13 * fRec6[1]))));
		double fTemp1 = (fConst23 * fRec5[1]);
		fRec5[0] = ((fConst5 * (((fConst7 * fRec6[0]) + (fConst14 * fRec6[1])) + (fConst7 * fRec6[2]))) - (fConst18 * ((fConst20 * fRec5[2]) + fTemp1)));
		double fTemp2 = (fConst32 * fRec4[1]);
		fRec4[0] = ((fRec5[2] + (fConst18 * (fTemp1 + (fConst20 * fRec5[0])))) - (fConst27 * ((fConst29 * fRec4[2]) + fTemp2)));
		double fTemp3 = (fConst41 * fRec3[1]);
		fRec3[0] = ((fRec4[2] + (fConst27 * (fTemp2 + (fConst29 * fRec4[0])))) - (fConst36 * ((fConst38 * fRec3[2]) + fTemp3)));
		double fTemp4 = (((fRec1[0] * ((fConst42 * ((1.5675794576488901e-10 * fRec1[0]) + -1.66568855633991e-10)) + 1.2538321962686799e-07)) + 6.19393104956741e-07) - fConst43);
		double fTemp5 = (fConst45 + ((fRec1[0] * ((fConst0 * (fConst47 + (fConst49 * fRec1[0]))) + 6.2691609813434195e-08)) + 3.0969655247837098e-07));
		double fTemp6 = (fConst50 + ((fRec1[0] * ((fConst0 * (fConst51 + (fConst52 * fRec1[0]))) + 6.2691609813434195e-08)) + 3.0969655247837098e-07));
		fRec2[0] = ((fRec3[2] + (fConst36 * (fTemp3 + (fConst38 * fRec3[0])))) - (((fRec2[1] * fTemp4) + (fRec2[2] * fTemp5)) / fTemp6));
		double fTemp7 = (fConst0 * ((fRec1[0] * (((fConst2 * fRec2[0]) + (fConst53 * fRec2[1])) + (fConst54 * fRec2[2]))) / fTemp6));
		double fTemp8 = (int(signbit(double(fTemp7))) ? double(copicat1_negclip(double(fTemp7))) : double(copicat1clip(double(fTemp7))));
		fRec17[0] = (0.0 - (fConst83 * ((fConst84 * fRec17[1]) - (fRec8[1] + fRec8[2]))));
		fRec18[0] = (fSlow3 + (0.99299999999999999 * fRec18[1]));
		double fTemp9 = (fRec17[0] * fRec18[0]);
		fVec1[0] = fTemp9;
		fRec16[0] = ((0.25 * ((fConst81 * fTemp9) + (fConst85 * fVec1[1]))) - (fConst86 * fRec16[1]));
		fRec15[0] = ((fRec16[0] + fTemp8) - (fConst75 * (((fConst88 * fRec15[1]) + (fConst89 * fRec15[2])) + (fConst90 * fRec15[3]))));
		double fTemp10 = (fConst75 * ((((fConst77 * fRec15[0]) + (fConst91 * fRec15[1])) + (fConst92 * fRec15[2])) + (fConst93 * fRec15[3])));
		fRec14[0] = ((int(signbit(double(fTemp10))) ? double(copicatrecord_2_negclip(double(fTemp10))) : double(copicatrecord_2clip(double(fTemp10)))) - (fConst73 * ((fConst94 * fRec14[2]) + (fConst95 * fRec14[1]))));
		fRec13[0] = ((fConst73 * (((fConst72 * fRec14[0]) + (fConst96 * fRec14[1])) + (fConst72 * fRec14[2]))) - (fConst70 * ((fConst97 * fRec13[2]) + (fConst95 * fRec13[1]))));
		double fTemp11 = (((fConst72 * fRec13[0]) + (fConst96 * fRec13[1])) + (fConst72 * fRec13[2]));
		fVec2[(IOTA & 1048575)] = fTemp11;
		double fTemp12 = ((fRec19[1] != 0.0) ? (((fRec20[1] > 0.0) & (fRec20[1] < 1.0)) ? fRec19[1] : 0.0) : (((fRec20[1] == 0.0) & (fSlow5 != fRec21[1])) ? fConst99 : (((fRec20[1] == 1.0) & (fSlow5 != fRec22[1])) ? fConst100 : 0.0)));
		fRec19[0] = fTemp12;
		fRec20[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec20[1] + fTemp12)));
		fRec21[0] = (((fRec20[1] >= 1.0) & (fRec22[1] != fSlow5)) ? fSlow5 : fRec21[1]);
		fRec22[0] = (((fRec20[1] <= 0.0) & (fRec21[1] != fSlow5)) ? fSlow5 : fRec22[1]);
		int iTemp13 = int(std::min<double>(524288.0, std::max<double>(0.0, fRec21[0])));
		double fTemp14 = fVec2[((IOTA - iTemp13) & 1048575)];
		int iTemp15 = int(std::min<double>(524288.0, std::max<double>(0.0, fRec22[0])));
		double fTemp16 = ((fRec23[1] != 0.0) ? (((fRec24[1] > 0.0) & (fRec24[1] < 1.0)) ? fRec23[1] : 0.0) : (((fRec24[1] == 0.0) & (fSlow7 != fRec25[1])) ? fConst99 : (((fRec24[1] == 1.0) & (fSlow7 != fRec26[1])) ? fConst100 : 0.0)));
		fRec23[0] = fTemp16;
		fRec24[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec24[1] + fTemp16)));
		fRec25[0] = (((fRec24[1] >= 1.0) & (fRec26[1] != fSlow7)) ? fSlow7 : fRec25[1]);
		fRec26[0] = (((fRec24[1] <= 0.0) & (fRec25[1] != fSlow7)) ? fSlow7 : fRec26[1]);
		int iTemp17 = int(std::min<double>(524288.0, std::max<double>(0.0, fRec25[0])));
		double fTemp18 = fVec2[((IOTA - iTemp17) & 1048575)];
		int iTemp19 = int(std::min<double>(524288.0, std::max<double>(0.0, fRec26[0])));
		double fTemp20 = ((fRec27[1] != 0.0) ? (((fRec28[1] > 0.0) & (fRec28[1] < 1.0)) ? fRec27[1] : 0.0) : (((fRec28[1] == 0.0) & (fSlow9 != fRec29[1])) ? fConst99 : (((fRec28[1] == 1.0) & (fSlow9 != fRec30[1])) ? fConst100 : 0.0)));
		fRec27[0] = fTemp20;
		fRec28[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec28[1] + fTemp20)));
		fRec29[0] = (((fRec28[1] >= 1.0) & (fRec30[1] != fSlow9)) ? fSlow9 : fRec29[1]);
		fRec30[0] = (((fRec28[1] <= 0.0) & (fRec29[1] != fSlow9)) ? fSlow9 : fRec30[1]);
		int iTemp21 = int(std::min<double>(524288.0, std::max<double>(0.0, fRec29[0])));
		double fTemp22 = fVec2[((IOTA - iTemp21) & 1048575)];
		int iTemp23 = int(std::min<double>(524288.0, std::max<double>(0.0, fRec30[0])));
		double fTemp24 = (((fSlow2 * ((fConst70 * fTemp14) + (fRec20[0] * (0.0 - (fConst70 * (fTemp14 - fVec2[((IOTA - iTemp15) & 1048575)])))))) + (fSlow6 * ((fConst70 * fTemp18) + (fRec24[0] * (0.0 - (fConst70 * (fTemp18 - fVec2[((IOTA - iTemp19) & 1048575)]))))))) + (fSlow8 * ((fConst70 * fTemp22) + (fRec28[0] * (0.0 - (fConst70 * (fTemp22 - fVec2[((IOTA - iTemp23) & 1048575)])))))));
		fVec3[0] = fTemp24;
		fRec12[0] = (0.0 - (fConst66 * ((fConst67 * fRec12[1]) - (fTemp24 + fVec3[1]))));
		fRec11[0] = ((fRec12[0] + (0.995 * fRec11[1])) - fRec12[1]);
		fRec10[0] = (fRec11[0] - (fConst103 * ((fConst104 * fRec10[1]) + (fConst105 * fRec10[2]))));
		double fTemp25 = (fConst62 * (((fConst64 * fRec10[0]) + (fConst106 * fRec10[1])) + (fConst107 * fRec10[2])));
		fRec9[0] = ((int(signbit(double(fTemp25))) ? double(copicatreplay1_negclip(double(fTemp25))) : double(copicatreplay1clip(double(fTemp25)))) - (fConst108 * ((fConst109 * fRec9[1]) + (fConst110 * fRec9[2]))));
		double fTemp26 = (fConst57 * (((fConst59 * fRec9[0]) + (fConst111 * fRec9[1])) + (fConst112 * fRec9[2])));
		fRec8[0] = (int(signbit(double(fTemp26))) ? double(copicatreplay2_negclip(double(fTemp26))) : double(copicatreplay2clip(double(fTemp26))));
		fRec31[0] = (fSlow10 + (0.99299999999999999 * fRec31[1]));
		fRec38[0] = (0.0 - (fConst10 * ((fConst11 * fRec38[1]) - (fTemp0 + fVec0[1]))));
		fRec37[0] = (fRec38[0] - (fConst5 * ((fConst12 * fRec37[2]) + (fConst13 * fRec37[1]))));
		double fTemp27 = (fRec37[2] + (fRec37[0] + (2.0 * fRec37[1])));
		fVec4[0] = fTemp27;
		fRec36[0] = ((fConst5 * ((fConst114 * fTemp27) + (fConst115 * fVec4[1]))) - (fConst116 * fRec36[1]));
		fRec35[0] = (fRec36[0] - (fConst113 * ((fConst117 * fRec35[2]) + (fConst23 * fRec35[1]))));
		double fTemp28 = (fConst32 * fRec34[1]);
		fRec34[0] = ((fConst113 * (((fConst22 * fRec35[0]) + (fConst118 * fRec35[1])) + (fConst22 * fRec35[2]))) - (fConst27 * ((fConst29 * fRec34[2]) + fTemp28)));
		double fTemp29 = (fConst41 * fRec33[1]);
		fRec33[0] = ((fRec34[2] + (fConst27 * (fTemp28 + (fConst29 * fRec34[0])))) - (fConst36 * ((fConst38 * fRec33[2]) + fTemp29)));
		fRec32[0] = ((fRec33[2] + (fConst36 * (fTemp29 + (fConst38 * fRec33[0])))) - (((fTemp4 * fRec32[1]) + (fTemp5 * fRec32[2])) / fTemp6));
		double fTemp30 = (fConst0 * ((fRec1[0] * (((fConst2 * fRec32[0]) + (fConst53 * fRec32[1])) + (fConst54 * fRec32[2]))) / fTemp6));
		double fTemp31 = (int(signbit(double(fTemp30))) ? double(copicat1_negclip(double(fTemp30))) : double(copicat1clip(double(fTemp30))));
		fRec48[0] = (0.0 - (fConst83 * ((fConst84 * fRec48[1]) - (fRec39[1] + fRec39[2]))));
		double fTemp32 = (fRec18[0] * fRec48[0]);
		fVec5[0] = fTemp32;
		fRec47[0] = ((0.25 * ((fConst81 * fTemp32) + (fConst85 * fVec5[1]))) - (fConst86 * fRec47[1]));
		fRec46[0] = ((fRec47[0] + fTemp31) - (fConst75 * (((fConst88 * fRec46[1]) + (fConst89 * fRec46[2])) + (fConst90 * fRec46[3]))));
		double fTemp33 = (fConst75 * ((((fConst77 * fRec46[0]) + (fConst91 * fRec46[1])) + (fConst92 * fRec46[2])) + (fConst93 * fRec46[3])));
		fRec45[0] = ((int(signbit(double(fTemp33))) ? double(copicatrecord_2_negclip(double(fTemp33))) : double(copicatrecord_2clip(double(fTemp33)))) - (fConst73 * ((fConst94 * fRec45[2]) + (fConst95 * fRec45[1]))));
		fRec44[0] = ((fConst73 * (((fConst72 * fRec45[0]) + (fConst96 * fRec45[1])) + (fConst72 * fRec45[2]))) - (fConst70 * ((fConst97 * fRec44[2]) + (fConst95 * fRec44[1]))));
		double fTemp34 = (((fConst72 * fRec44[0]) + (fConst96 * fRec44[1])) + (fConst72 * fRec44[2]));
		fVec6[(IOTA & 1048575)] = fTemp34;
		double fTemp35 = fVec6[((IOTA - iTemp13) & 1048575)];
		double fTemp36 = fVec6[((IOTA - iTemp17) & 1048575)];
		double fTemp37 = fVec6[((IOTA - iTemp21) & 1048575)];
		double fTemp38 = (((fSlow2 * ((fConst70 * fTemp35) + (fRec20[0] * (0.0 - (fConst70 * (fTemp35 - fVec6[((IOTA - iTemp15) & 1048575)])))))) + (fSlow6 * ((fConst70 * fTemp36) + (fRec24[0] * (0.0 - (fConst70 * (fTemp36 - fVec6[((IOTA - iTemp19) & 1048575)]))))))) + (fSlow8 * ((fConst70 * fTemp37) + (fRec28[0] * (0.0 - (fConst70 * (fTemp37 - fVec6[((IOTA - iTemp23) & 1048575)])))))));
		fVec7[0] = fTemp38;
		fRec43[0] = (0.0 - (fConst66 * ((fConst67 * fRec43[1]) - (fTemp38 + fVec7[1]))));
		fRec42[0] = ((fRec43[0] + (0.995 * fRec42[1])) - fRec43[1]);
		fRec41[0] = (fRec42[0] - (fConst103 * ((fConst104 * fRec41[1]) + (fConst105 * fRec41[2]))));
		double fTemp39 = (fConst62 * (((fConst64 * fRec41[0]) + (fConst106 * fRec41[1])) + (fConst107 * fRec41[2])));
		fRec40[0] = ((int(signbit(double(fTemp39))) ? double(copicatreplay1_negclip(double(fTemp39))) : double(copicatreplay1clip(double(fTemp39)))) - (fConst108 * ((fConst109 * fRec40[1]) + (fConst110 * fRec40[2]))));
		double fTemp40 = (fConst57 * (((fConst59 * fRec40[0]) + (fConst111 * fRec40[1])) + (fConst112 * fRec40[2])));
		fRec39[0] = (int(signbit(double(fTemp40))) ? double(copicatreplay2_negclip(double(fTemp40))) : double(copicatreplay2clip(double(fTemp40))));
		fRec54[0] = (0.0 - (fConst121 * ((fConst19 * fRec54[1]) - (fConst5 * (fTemp27 + fVec4[1])))));
		fRec53[0] = (fRec54[0] - (fConst113 * ((fConst117 * fRec53[2]) + (fConst23 * fRec53[1]))));
		double fTemp41 = (fRec53[2] + (fRec53[0] + (2.0 * fRec53[1])));
		fVec8[0] = fTemp41;
		fRec52[0] = ((fConst113 * ((fConst120 * fTemp41) + (fConst122 * fVec8[1]))) - (fConst123 * fRec52[1]));
		fRec51[0] = (fRec52[0] - (fConst119 * ((fConst124 * fRec51[2]) + (fConst32 * fRec51[1]))));
		double fTemp42 = (fConst41 * fRec50[1]);
		fRec50[0] = ((fConst119 * (((fConst31 * fRec51[0]) + (fConst125 * fRec51[1])) + (fConst31 * fRec51[2]))) - (fConst36 * ((fConst38 * fRec50[2]) + fTemp42)));
		fRec49[0] = ((fRec50[2] + (fConst36 * (fTemp42 + (fConst38 * fRec50[0])))) - (((fTemp4 * fRec49[1]) + (fTemp5 * fRec49[2])) / fTemp6));
		double fTemp43 = (fConst0 * ((fRec1[0] * (((fConst2 * fRec49[0]) + (fConst53 * fRec49[1])) + (fConst54 * fRec49[2]))) / fTemp6));
		double fTemp44 = (int(signbit(double(fTemp43))) ? double(copicat1_negclip(double(fTemp43))) : double(copicat1clip(double(fTemp43))));
		fRec64[0] = (0.0 - (fConst83 * ((fConst84 * fRec64[1]) - (fRec55[1] + fRec55[2]))));
		double fTemp45 = (fRec18[0] * fRec64[0]);
		fVec9[0] = fTemp45;
		fRec63[0] = ((0.25 * ((fConst81 * fTemp45) + (fConst85 * fVec9[1]))) - (fConst86 * fRec63[1]));
		fRec62[0] = ((fRec63[0] + fTemp44) - (fConst75 * (((fConst88 * fRec62[1]) + (fConst89 * fRec62[2])) + (fConst90 * fRec62[3]))));
		double fTemp46 = (fConst75 * ((((fConst77 * fRec62[0]) + (fConst91 * fRec62[1])) + (fConst92 * fRec62[2])) + (fConst93 * fRec62[3])));
		fRec61[0] = ((int(signbit(double(fTemp46))) ? double(copicatrecord_2_negclip(double(fTemp46))) : double(copicatrecord_2clip(double(fTemp46)))) - (fConst73 * ((fConst94 * fRec61[2]) + (fConst95 * fRec61[1]))));
		fRec60[0] = ((fConst73 * (((fConst72 * fRec61[0]) + (fConst96 * fRec61[1])) + (fConst72 * fRec61[2]))) - (fConst70 * ((fConst97 * fRec60[2]) + (fConst95 * fRec60[1]))));
		double fTemp47 = (((fConst72 * fRec60[0]) + (fConst96 * fRec60[1])) + (fConst72 * fRec60[2]));
		fVec10[(IOTA & 1048575)] = fTemp47;
		double fTemp48 = fVec10[((IOTA - iTemp13) & 1048575)];
		double fTemp49 = fVec10[((IOTA - iTemp17) & 1048575)];
		double fTemp50 = fVec10[((IOTA - iTemp21) & 1048575)];
		double fTemp51 = (((fSlow2 * ((fConst70 * fTemp48) + (fRec20[0] * (0.0 - (fConst70 * (fTemp48 - fVec10[((IOTA - iTemp15) & 1048575)])))))) + (fSlow6 * ((fConst70 * fTemp49) + (fRec24[0] * (0.0 - (fConst70 * (fTemp49 - fVec10[((IOTA - iTemp19) & 1048575)]))))))) + (fSlow8 * ((fConst70 * fTemp50) + (fRec28[0] * (0.0 - (fConst70 * (fTemp50 - fVec10[((IOTA - iTemp23) & 1048575)])))))));
		fVec11[0] = fTemp51;
		fRec59[0] = (0.0 - (fConst66 * ((fConst67 * fRec59[1]) - (fTemp51 + fVec11[1]))));
		fRec58[0] = ((fRec59[0] + (0.995 * fRec58[1])) - fRec59[1]);
		fRec57[0] = (fRec58[0] - (fConst103 * ((fConst104 * fRec57[1]) + (fConst105 * fRec57[2]))));
		double fTemp52 = (fConst62 * (((fConst64 * fRec57[0]) + (fConst106 * fRec57[1])) + (fConst107 * fRec57[2])));
		fRec56[0] = ((int(signbit(double(fTemp52))) ? double(copicatreplay1_negclip(double(fTemp52))) : double(copicatreplay1clip(double(fTemp52)))) - (fConst108 * ((fConst109 * fRec56[1]) + (fConst110 * fRec56[2]))));
		double fTemp53 = (fConst57 * (((fConst59 * fRec56[0]) + (fConst111 * fRec56[1])) + (fConst112 * fRec56[2])));
		fRec55[0] = (int(signbit(double(fTemp53))) ? double(copicatreplay2_negclip(double(fTemp53))) : double(copicatreplay2clip(double(fTemp53))));
		fRec69[0] = (0.0 - (fConst128 * ((fConst28 * fRec69[1]) - (fConst113 * (fTemp41 + fVec8[1])))));
		fRec68[0] = (fRec69[0] - (fConst119 * ((fConst124 * fRec68[2]) + (fConst32 * fRec68[1]))));
		double fTemp54 = (fRec68[2] + (fRec68[0] + (2.0 * fRec68[1])));
		fVec12[0] = fTemp54;
		fRec67[0] = ((fConst119 * ((fConst127 * fTemp54) + (fConst129 * fVec12[1]))) - (fConst130 * fRec67[1]));
		fRec66[0] = (fRec67[0] - (fConst126 * ((fConst131 * fRec66[2]) + (fConst41 * fRec66[1]))));
		fRec65[0] = ((fConst126 * (((fConst40 * fRec66[0]) + (fConst132 * fRec66[1])) + (fConst40 * fRec66[2]))) - (((fTemp4 * fRec65[1]) + (fTemp5 * fRec65[2])) / fTemp6));
		double fTemp55 = (fConst0 * ((fRec1[0] * (((fConst2 * fRec65[0]) + (fConst53 * fRec65[1])) + (fConst54 * fRec65[2]))) / fTemp6));
		double fTemp56 = (int(signbit(double(fTemp55))) ? double(copicat1_negclip(double(fTemp55))) : double(copicat1clip(double(fTemp55))));
		fRec79[0] = (0.0 - (fConst83 * ((fConst84 * fRec79[1]) - (fRec70[1] + fRec70[2]))));
		double fTemp57 = (fRec18[0] * fRec79[0]);
		fVec13[0] = fTemp57;
		fRec78[0] = ((0.25 * ((fConst81 * fTemp57) + (fConst85 * fVec13[1]))) - (fConst86 * fRec78[1]));
		fRec77[0] = ((fRec78[0] + fTemp56) - (fConst75 * (((fConst88 * fRec77[1]) + (fConst89 * fRec77[2])) + (fConst90 * fRec77[3]))));
		double fTemp58 = (fConst75 * ((((fConst77 * fRec77[0]) + (fConst91 * fRec77[1])) + (fConst92 * fRec77[2])) + (fConst93 * fRec77[3])));
		fRec76[0] = ((int(signbit(double(fTemp58))) ? double(copicatrecord_2_negclip(double(fTemp58))) : double(copicatrecord_2clip(double(fTemp58)))) - (fConst73 * ((fConst94 * fRec76[2]) + (fConst95 * fRec76[1]))));
		fRec75[0] = ((fConst73 * (((fConst72 * fRec76[0]) + (fConst96 * fRec76[1])) + (fConst72 * fRec76[2]))) - (fConst70 * ((fConst97 * fRec75[2]) + (fConst95 * fRec75[1]))));
		double fTemp59 = (((fConst72 * fRec75[0]) + (fConst96 * fRec75[1])) + (fConst72 * fRec75[2]));
		fVec14[(IOTA & 1048575)] = fTemp59;
		double fTemp60 = fVec14[((IOTA - iTemp13) & 1048575)];
		double fTemp61 = fVec14[((IOTA - iTemp17) & 1048575)];
		double fTemp62 = fVec14[((IOTA - iTemp21) & 1048575)];
		double fTemp63 = (((fSlow2 * ((fConst70 * fTemp60) + (fRec20[0] * (0.0 - (fConst70 * (fTemp60 - fVec14[((IOTA - iTemp15) & 1048575)])))))) + (fSlow6 * ((fConst70 * fTemp61) + (fRec24[0] * (0.0 - (fConst70 * (fTemp61 - fVec14[((IOTA - iTemp19) & 1048575)]))))))) + (fSlow8 * ((fConst70 * fTemp62) + (fRec28[0] * (0.0 - (fConst70 * (fTemp62 - fVec14[((IOTA - iTemp23) & 1048575)])))))));
		fVec15[0] = fTemp63;
		fRec74[0] = (0.0 - (fConst66 * ((fConst67 * fRec74[1]) - (fTemp63 + fVec15[1]))));
		fRec73[0] = ((fRec74[0] + (0.995 * fRec73[1])) - fRec74[1]);
		fRec72[0] = (fRec73[0] - (fConst103 * ((fConst104 * fRec72[1]) + (fConst105 * fRec72[2]))));
		double fTemp64 = (fConst62 * (((fConst64 * fRec72[0]) + (fConst106 * fRec72[1])) + (fConst107 * fRec72[2])));
		fRec71[0] = ((int(signbit(double(fTemp64))) ? double(copicatreplay1_negclip(double(fTemp64))) : double(copicatreplay1clip(double(fTemp64)))) - (fConst108 * ((fConst109 * fRec71[1]) + (fConst110 * fRec71[2]))));
		double fTemp65 = (fConst57 * (((fConst59 * fRec71[0]) + (fConst111 * fRec71[1])) + (fConst112 * fRec71[2])));
		fRec70[0] = (int(signbit(double(fTemp65))) ? double(copicatreplay2_negclip(double(fTemp65))) : double(copicatreplay2clip(double(fTemp65))));
		fRec82[0] = (0.0 - (fConst133 * ((fConst37 * fRec82[1]) - (fConst119 * (fTemp54 + fVec12[1])))));
		fRec81[0] = (fRec82[0] - (fConst126 * ((fConst131 * fRec81[2]) + (fConst41 * fRec81[1]))));
		fRec80[0] = ((fConst126 * (fRec81[2] + (fRec81[0] + (2.0 * fRec81[1])))) - (((fTemp4 * fRec80[1]) + (fTemp5 * fRec80[2])) / fTemp6));
		double fTemp66 = (fConst0 * ((fRec1[0] * (((fConst2 * fRec80[0]) + (fConst53 * fRec80[1])) + (fConst54 * fRec80[2]))) / fTemp6));
		double fTemp67 = (int(signbit(double(fTemp66))) ? double(copicat1_negclip(double(fTemp66))) : double(copicat1clip(double(fTemp66))));
		fRec92[0] = (0.0 - (fConst83 * ((fConst84 * fRec92[1]) - (fRec83[1] + fRec83[2]))));
		double fTemp68 = (fRec18[0] * fRec92[0]);
		fVec16[0] = fTemp68;
		fRec91[0] = ((0.25 * ((fConst81 * fTemp68) + (fConst85 * fVec16[1]))) - (fConst86 * fRec91[1]));
		fRec90[0] = ((fRec91[0] + fTemp67) - (fConst75 * (((fConst88 * fRec90[1]) + (fConst89 * fRec90[2])) + (fConst90 * fRec90[3]))));
		double fTemp69 = (fConst75 * ((((fConst77 * fRec90[0]) + (fConst91 * fRec90[1])) + (fConst92 * fRec90[2])) + (fConst93 * fRec90[3])));
		fRec89[0] = ((int(signbit(double(fTemp69))) ? double(copicatrecord_2_negclip(double(fTemp69))) : double(copicatrecord_2clip(double(fTemp69)))) - (fConst73 * ((fConst94 * fRec89[2]) + (fConst95 * fRec89[1]))));
		fRec88[0] = ((fConst73 * (((fConst72 * fRec89[0]) + (fConst96 * fRec89[1])) + (fConst72 * fRec89[2]))) - (fConst70 * ((fConst97 * fRec88[2]) + (fConst95 * fRec88[1]))));
		double fTemp70 = (((fConst72 * fRec88[0]) + (fConst96 * fRec88[1])) + (fConst72 * fRec88[2]));
		fVec17[(IOTA & 1048575)] = fTemp70;
		double fTemp71 = fVec17[((IOTA - iTemp13) & 1048575)];
		double fTemp72 = fVec17[((IOTA - iTemp17) & 1048575)];
		double fTemp73 = fVec17[((IOTA - iTemp21) & 1048575)];
		double fTemp74 = (((fSlow2 * ((fConst70 * fTemp71) + (fRec20[0] * (0.0 - (fConst70 * (fTemp71 - fVec17[((IOTA - iTemp15) & 1048575)])))))) + (fSlow6 * ((fConst70 * fTemp72) + (fRec24[0] * (0.0 - (fConst70 * (fTemp72 - fVec17[((IOTA - iTemp19) & 1048575)]))))))) + (fSlow8 * ((fConst70 * fTemp73) + (fRec28[0] * (0.0 - (fConst70 * (fTemp73 - fVec17[((IOTA - iTemp23) & 1048575)])))))));
		fVec18[0] = fTemp74;
		fRec87[0] = (0.0 - (fConst66 * ((fConst67 * fRec87[1]) - (fTemp74 + fVec18[1]))));
		fRec86[0] = ((fRec87[0] + (0.995 * fRec86[1])) - fRec87[1]);
		fRec85[0] = (fRec86[0] - (fConst103 * ((fConst104 * fRec85[1]) + (fConst105 * fRec85[2]))));
		double fTemp75 = (fConst62 * (((fConst64 * fRec85[0]) + (fConst106 * fRec85[1])) + (fConst107 * fRec85[2])));
		fRec84[0] = ((int(signbit(double(fTemp75))) ? double(copicatreplay1_negclip(double(fTemp75))) : double(copicatreplay1clip(double(fTemp75)))) - (fConst108 * ((fConst109 * fRec84[1]) + (fConst110 * fRec84[2]))));
		double fTemp76 = (fConst57 * (((fConst59 * fRec84[0]) + (fConst111 * fRec84[1])) + (fConst112 * fRec84[2])));
		fRec83[0] = (int(signbit(double(fTemp76))) ? double(copicatreplay2_negclip(double(fTemp76))) : double(copicatreplay2clip(double(fTemp76))));
		output0[i0] = FAUSTFLOAT((fRec0[0] * (((((fTemp8 + (0.25 * (fRec8[0] * fRec31[0]))) + (fTemp31 + (0.25 * (fRec31[0] * fRec39[0])))) + (fTemp44 + (0.25 * (fRec31[0] * fRec55[0])))) + (fTemp56 + (0.25 * (fRec31[0] * fRec70[0])))) + (fTemp67 + (0.25 * (fRec31[0] * fRec83[0]))))));
		fRec0[1] = fRec0[0];
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
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fVec1[1] = fVec1[0];
		fRec16[1] = fRec16[0];
		for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
			fRec15[j0] = fRec15[(j0 - 1)];
		}
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		IOTA = (IOTA + 1);
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
		fVec3[1] = fVec3[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec31[1] = fRec31[0];
		fRec38[1] = fRec38[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fVec4[1] = fVec4[0];
		fRec36[1] = fRec36[0];
		fRec35[2] = fRec35[1];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fRec48[1] = fRec48[0];
		fVec5[1] = fVec5[0];
		fRec47[1] = fRec47[0];
		for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
			fRec46[j1] = fRec46[(j1 - 1)];
		}
		fRec45[2] = fRec45[1];
		fRec45[1] = fRec45[0];
		fRec44[2] = fRec44[1];
		fRec44[1] = fRec44[0];
		fVec7[1] = fVec7[0];
		fRec43[1] = fRec43[0];
		fRec42[1] = fRec42[0];
		fRec41[2] = fRec41[1];
		fRec41[1] = fRec41[0];
		fRec40[2] = fRec40[1];
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fRec54[1] = fRec54[0];
		fRec53[2] = fRec53[1];
		fRec53[1] = fRec53[0];
		fVec8[1] = fVec8[0];
		fRec52[1] = fRec52[0];
		fRec51[2] = fRec51[1];
		fRec51[1] = fRec51[0];
		fRec50[2] = fRec50[1];
		fRec50[1] = fRec50[0];
		fRec49[2] = fRec49[1];
		fRec49[1] = fRec49[0];
		fRec64[1] = fRec64[0];
		fVec9[1] = fVec9[0];
		fRec63[1] = fRec63[0];
		for (int j2 = 3; (j2 > 0); j2 = (j2 - 1)) {
			fRec62[j2] = fRec62[(j2 - 1)];
		}
		fRec61[2] = fRec61[1];
		fRec61[1] = fRec61[0];
		fRec60[2] = fRec60[1];
		fRec60[1] = fRec60[0];
		fVec11[1] = fVec11[0];
		fRec59[1] = fRec59[0];
		fRec58[1] = fRec58[0];
		fRec57[2] = fRec57[1];
		fRec57[1] = fRec57[0];
		fRec56[2] = fRec56[1];
		fRec56[1] = fRec56[0];
		fRec55[2] = fRec55[1];
		fRec55[1] = fRec55[0];
		fRec69[1] = fRec69[0];
		fRec68[2] = fRec68[1];
		fRec68[1] = fRec68[0];
		fVec12[1] = fVec12[0];
		fRec67[1] = fRec67[0];
		fRec66[2] = fRec66[1];
		fRec66[1] = fRec66[0];
		fRec65[2] = fRec65[1];
		fRec65[1] = fRec65[0];
		fRec79[1] = fRec79[0];
		fVec13[1] = fVec13[0];
		fRec78[1] = fRec78[0];
		for (int j3 = 3; (j3 > 0); j3 = (j3 - 1)) {
			fRec77[j3] = fRec77[(j3 - 1)];
		}
		fRec76[2] = fRec76[1];
		fRec76[1] = fRec76[0];
		fRec75[2] = fRec75[1];
		fRec75[1] = fRec75[0];
		fVec15[1] = fVec15[0];
		fRec74[1] = fRec74[0];
		fRec73[1] = fRec73[0];
		fRec72[2] = fRec72[1];
		fRec72[1] = fRec72[0];
		fRec71[2] = fRec71[1];
		fRec71[1] = fRec71[0];
		fRec70[2] = fRec70[1];
		fRec70[1] = fRec70[0];
		fRec82[1] = fRec82[0];
		fRec81[2] = fRec81[1];
		fRec81[1] = fRec81[0];
		fRec80[2] = fRec80[1];
		fRec80[1] = fRec80[0];
		fRec92[1] = fRec92[0];
		fVec16[1] = fVec16[0];
		fRec91[1] = fRec91[0];
		for (int j4 = 3; (j4 > 0); j4 = (j4 - 1)) {
			fRec90[j4] = fRec90[(j4 - 1)];
		}
		fRec89[2] = fRec89[1];
		fRec89[1] = fRec89[0];
		fRec88[2] = fRec88[1];
		fRec88[1] = fRec88[0];
		fVec18[1] = fVec18[0];
		fRec87[1] = fRec87[0];
		fRec86[1] = fRec86[0];
		fRec85[2] = fRec85[1];
		fRec85[1] = fRec85[0];
		fRec84[2] = fRec84[1];
		fRec84[1] = fRec84[0];
		fRec83[2] = fRec83[1];
		fRec83[1] = fRec83[0];
	}
#undef fVslider0
#undef fVslider1
#undef fCheckbox0
#undef fVslider2
#undef fVslider3
#undef fCheckbox1
#undef fCheckbox2
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
	case SUSTAIN: 
		fVslider2_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case SWELL: 
		fVslider4_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case INPUT: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case OUTPUT: 
		fVslider0_ = (float*)data; // , 1.0, 0.0, 2.0, 0.01 
		break;
	case BPM: 
		fVslider3_ = (float*)data; // , 120.0, 24.0, 360.0, 0.10000000000000001 
		break;
	case HEAD1: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case HEAD2: 
		fCheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case HEAD3: 
		fCheckbox2_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
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
