// generated from file '../src/LV2/faust/gxtape.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "input12au7_neg_table.h"
#include "input12au7_table.h"
#include "math.h"
#include "output12au7_neg_table.h"
#include "output12au7_table.h"

namespace gxtape {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	int iVec0[2];
	double fConst0;
	double fConst2;
	double fConst4;
	double fConst5;
	double fConst8;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst11;
	double fConst14;
	double fConst15;
	double fConst17;
	double fConst18;
	double fConst21;
	double fConst22;
	double fConst24;
	double fConst25;
	double fConst28;
	double fConst29;
	double fConst31;
	double fConst32;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fVec1[2];
	double fConst40;
	double fConst42;
	double fRec10[2];
	double fRec9[3];
	double fVec2[2];
	double fConst43;
	double fConst45;
	double fRec8[2];
	double fRec7[3];
	double fVec3[2];
	double fConst46;
	double fConst48;
	double fRec6[2];
	double fRec5[3];
	double fVec4[2];
	double fConst49;
	double fConst51;
	double fRec4[2];
	double fRec3[3];
	double fRec2[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec11[2];
	double fConst52;
	double fVec5[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	double fConst53;
	double fRec13[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst55;
	double fConst57;
	double fConst58;
	double fConst60;
	double fConst64;
	double fConst65;
	double fConst67;
	double fConst69;
	double fConst70;
	double fConst71;
	double fConst72;
	double fRec23[2];
	double fRec22[2];
	double fRec21[2];
	double fConst73;
	double fConst74;
	double fRec20[2];
	double fRec19[3];
	double fVec6[2];
	double fConst75;
	double fConst76;
	double fRec18[2];
	double fConst77;
	double fRec17[2];
	double fRec16[3];
	double fConst79;
	double fConst80;
	double fVec7[2];
	double fConst83;
	double fConst84;
	double fRec15[2];
	double fRec14[3];
	double fConst85;
	double fConst86;
	double fConst87;
	double fConst90;
	double fConst91;
	double fRec25[2];
	double fRec24[3];
	double fConst92;
	double fConst93;
	double fConst94;
	double fConst95;
	double fConst97;
	double fConst98;
	double fRec29[2];
	double fConst100;
	double fConst104;
	double fConst105;
	double fConst107;
	double fConst108;
	double fConst110;
	double fConst111;
	double fRec31[2];
	double fRec30[3];
	double fConst113;
	double fConst114;
	double fRec28[3];
	double fRec27[3];
	double fRec26[3];
	double fConst115;
	double fConst116;
	double fConst117;
	double fConst118;
	double fConst119;
	double fRec35[2];
	double fRec36[3];
	double fRec34[3];
	double fRec33[3];
	double fRec32[3];
	double fConst120;
	double fConst124;
	int iRec39[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec40[2];
	double fVec8[2];
	double fConst125;
	double fConst126;
	double fRec38[2];
	double fConst128;
	double fConst129;
	double fRec41[2];
	double fRec37[3];
	int IOTA0;
	double *fVec9;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fConst130;
	double fRec48[2];
	double fRec47[2];
	double fRec46[2];
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	double fConst131;
	double fConst132;
	double fConst133;
	double fRec42[2];
	double fRec43[2];
	double fRec44[2];
	double fRec45[2];
	double *fVec10;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT	*fVslider5_;
	double fRec55[2];
	double fRec54[2];
	double fRec53[2];
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT	*fVslider6_;
	double fRec49[2];
	double fRec50[2];
	double fRec51[2];
	double fRec52[2];
	double fRec12[3];
	double fRec1[2];
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT	*fVslider7_;
	double fRec56[2];
	double fConst134;
	double fConst135;
	double fRec0[3];
	double fConst136;
	double fConst137;
	double fConst138;
	double fRec61[2];
	double fRec60[3];
	double fConst139;
	double fRec59[2];
	double fVec11[2];
	double fRec63[2];
	double fRec73[2];
	double fRec72[2];
	double fRec71[2];
	double fRec70[2];
	double fRec69[3];
	double fVec12[2];
	double fRec68[2];
	double fRec67[2];
	double fRec66[3];
	double fVec13[2];
	double fRec65[2];
	double fRec64[3];
	double fRec75[2];
	double fRec74[3];
	double fRec79[2];
	double fRec81[2];
	double fRec80[3];
	double fRec78[3];
	double fRec77[3];
	double fRec76[3];
	double fRec85[2];
	double fRec86[3];
	double fRec84[3];
	double fRec83[3];
	double fRec82[3];
	double *fVec14;
	double *fVec15;
	double fRec62[3];
	double fRec58[2];
	double fRec57[3];
	double fConst140;
	double fConst141;
	double fConst142;
	double fConst143;
	double fConst144;
	double fRec92[2];
	double fRec91[3];
	double fConst145;
	double fRec90[3];
	double fRec89[2];
	double fVec16[2];
	double fRec94[2];
	double fRec104[2];
	double fRec103[2];
	double fRec102[2];
	double fRec101[2];
	double fRec100[3];
	double fVec17[2];
	double fRec99[2];
	double fRec98[2];
	double fRec97[3];
	double fVec18[2];
	double fRec96[2];
	double fRec95[3];
	double fRec106[2];
	double fRec105[3];
	double fRec110[2];
	double fRec112[2];
	double fRec111[3];
	double fRec109[3];
	double fRec108[3];
	double fRec107[3];
	double fRec116[2];
	double fRec117[3];
	double fRec115[3];
	double fRec114[3];
	double fRec113[3];
	double *fVec19;
	double *fVec20;
	double fRec93[3];
	double fRec88[2];
	double fRec87[3];
	double fConst146;
	double fConst147;
	double fConst148;
	double fConst149;
	double fConst150;
	double fRec124[2];
	double fRec123[3];
	double fConst151;
	double fRec122[3];
	double fRec121[3];
	double fRec120[2];
	double fVec21[2];
	double fRec126[2];
	double fRec136[2];
	double fRec135[2];
	double fRec134[2];
	double fRec133[2];
	double fRec132[3];
	double fVec22[2];
	double fRec131[2];
	double fRec130[2];
	double fRec129[3];
	double fVec23[2];
	double fRec128[2];
	double fRec127[3];
	double fRec138[2];
	double fRec137[3];
	double fRec142[2];
	double fRec144[2];
	double fRec143[3];
	double fRec141[3];
	double fRec140[3];
	double fRec139[3];
	double fRec148[2];
	double fRec149[3];
	double fRec147[3];
	double fRec146[3];
	double fRec145[3];
	double *fVec24;
	double *fVec25;
	double fRec125[3];
	double fRec119[2];
	double fRec118[3];
	double fConst152;
	double fConst153;
	double fConst154;
	double fRec157[2];
	double fRec156[3];
	double fConst155;
	double fRec155[3];
	double fRec154[3];
	double fRec153[3];
	double fRec152[2];
	double fVec26[2];
	double fRec159[2];
	double fRec169[2];
	double fRec168[2];
	double fRec167[2];
	double fRec166[2];
	double fRec165[3];
	double fVec27[2];
	double fRec164[2];
	double fRec163[2];
	double fRec162[3];
	double fVec28[2];
	double fRec161[2];
	double fRec160[3];
	double fRec171[2];
	double fRec170[3];
	double fRec175[2];
	double fRec177[2];
	double fRec176[3];
	double fRec174[3];
	double fRec173[3];
	double fRec172[3];
	double fRec181[2];
	double fRec182[3];
	double fRec180[3];
	double fRec179[3];
	double fRec178[3];
	double *fVec29;
	double *fVec30;
	double fRec158[3];
	double fRec151[2];
	double fRec150[3];

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
	  fVec9(0),
	  fVec10(0),
	  fVec14(0),
	  fVec15(0),
	  fVec19(0),
	  fVec20(0),
	  fVec24(0),
	  fVec25(0),
	  fVec29(0),
	  fVec30(0),
	  mem_allocated(false) {
	version = PLUGINLV2_VERSION;
	id = "gxtape";
	name = N_("gxtape");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) iVec0[l0] = 0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fVec1[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec10[l2] = 0.0;
	for (int l3 = 0; l3 < 3; l3 = l3 + 1) fRec9[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fVec2[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec8[l5] = 0.0;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec7[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fVec3[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec6[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec5[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fVec4[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec4[l11] = 0.0;
	for (int l12 = 0; l12 < 3; l12 = l12 + 1) fRec3[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec2[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec11[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fVec5[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec13[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec23[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec22[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec21[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec20[l20] = 0.0;
	for (int l21 = 0; l21 < 3; l21 = l21 + 1) fRec19[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fVec6[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec18[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec17[l24] = 0.0;
	for (int l25 = 0; l25 < 3; l25 = l25 + 1) fRec16[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fVec7[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec15[l27] = 0.0;
	for (int l28 = 0; l28 < 3; l28 = l28 + 1) fRec14[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec25[l29] = 0.0;
	for (int l30 = 0; l30 < 3; l30 = l30 + 1) fRec24[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec29[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fRec31[l32] = 0.0;
	for (int l33 = 0; l33 < 3; l33 = l33 + 1) fRec30[l33] = 0.0;
	for (int l34 = 0; l34 < 3; l34 = l34 + 1) fRec28[l34] = 0.0;
	for (int l35 = 0; l35 < 3; l35 = l35 + 1) fRec27[l35] = 0.0;
	for (int l36 = 0; l36 < 3; l36 = l36 + 1) fRec26[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec35[l37] = 0.0;
	for (int l38 = 0; l38 < 3; l38 = l38 + 1) fRec36[l38] = 0.0;
	for (int l39 = 0; l39 < 3; l39 = l39 + 1) fRec34[l39] = 0.0;
	for (int l40 = 0; l40 < 3; l40 = l40 + 1) fRec33[l40] = 0.0;
	for (int l41 = 0; l41 < 3; l41 = l41 + 1) fRec32[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) iRec39[l42] = 0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fRec40[l43] = 0.0;
	for (int l44 = 0; l44 < 2; l44 = l44 + 1) fVec8[l44] = 0.0;
	for (int l45 = 0; l45 < 2; l45 = l45 + 1) fRec38[l45] = 0.0;
	for (int l46 = 0; l46 < 2; l46 = l46 + 1) fRec41[l46] = 0.0;
	for (int l47 = 0; l47 < 3; l47 = l47 + 1) fRec37[l47] = 0.0;
	for (int l48 = 0; l48 < 8192; l48 = l48 + 1) fVec9[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec48[l49] = 0.0;
	for (int l50 = 0; l50 < 2; l50 = l50 + 1) fRec47[l50] = 0.0;
	for (int l51 = 0; l51 < 2; l51 = l51 + 1) fRec46[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fRec42[l52] = 0.0;
	for (int l53 = 0; l53 < 2; l53 = l53 + 1) fRec43[l53] = 0.0;
	for (int l54 = 0; l54 < 2; l54 = l54 + 1) fRec44[l54] = 0.0;
	for (int l55 = 0; l55 < 2; l55 = l55 + 1) fRec45[l55] = 0.0;
	for (int l56 = 0; l56 < 8192; l56 = l56 + 1) fVec10[l56] = 0.0;
	for (int l57 = 0; l57 < 2; l57 = l57 + 1) fRec55[l57] = 0.0;
	for (int l58 = 0; l58 < 2; l58 = l58 + 1) fRec54[l58] = 0.0;
	for (int l59 = 0; l59 < 2; l59 = l59 + 1) fRec53[l59] = 0.0;
	for (int l60 = 0; l60 < 2; l60 = l60 + 1) fRec49[l60] = 0.0;
	for (int l61 = 0; l61 < 2; l61 = l61 + 1) fRec50[l61] = 0.0;
	for (int l62 = 0; l62 < 2; l62 = l62 + 1) fRec51[l62] = 0.0;
	for (int l63 = 0; l63 < 2; l63 = l63 + 1) fRec52[l63] = 0.0;
	for (int l64 = 0; l64 < 3; l64 = l64 + 1) fRec12[l64] = 0.0;
	for (int l65 = 0; l65 < 2; l65 = l65 + 1) fRec1[l65] = 0.0;
	for (int l66 = 0; l66 < 2; l66 = l66 + 1) fRec56[l66] = 0.0;
	for (int l67 = 0; l67 < 3; l67 = l67 + 1) fRec0[l67] = 0.0;
	for (int l68 = 0; l68 < 2; l68 = l68 + 1) fRec61[l68] = 0.0;
	for (int l69 = 0; l69 < 3; l69 = l69 + 1) fRec60[l69] = 0.0;
	for (int l70 = 0; l70 < 2; l70 = l70 + 1) fRec59[l70] = 0.0;
	for (int l71 = 0; l71 < 2; l71 = l71 + 1) fVec11[l71] = 0.0;
	for (int l72 = 0; l72 < 2; l72 = l72 + 1) fRec63[l72] = 0.0;
	for (int l73 = 0; l73 < 2; l73 = l73 + 1) fRec73[l73] = 0.0;
	for (int l74 = 0; l74 < 2; l74 = l74 + 1) fRec72[l74] = 0.0;
	for (int l75 = 0; l75 < 2; l75 = l75 + 1) fRec71[l75] = 0.0;
	for (int l76 = 0; l76 < 2; l76 = l76 + 1) fRec70[l76] = 0.0;
	for (int l77 = 0; l77 < 3; l77 = l77 + 1) fRec69[l77] = 0.0;
	for (int l78 = 0; l78 < 2; l78 = l78 + 1) fVec12[l78] = 0.0;
	for (int l79 = 0; l79 < 2; l79 = l79 + 1) fRec68[l79] = 0.0;
	for (int l80 = 0; l80 < 2; l80 = l80 + 1) fRec67[l80] = 0.0;
	for (int l81 = 0; l81 < 3; l81 = l81 + 1) fRec66[l81] = 0.0;
	for (int l82 = 0; l82 < 2; l82 = l82 + 1) fVec13[l82] = 0.0;
	for (int l83 = 0; l83 < 2; l83 = l83 + 1) fRec65[l83] = 0.0;
	for (int l84 = 0; l84 < 3; l84 = l84 + 1) fRec64[l84] = 0.0;
	for (int l85 = 0; l85 < 2; l85 = l85 + 1) fRec75[l85] = 0.0;
	for (int l86 = 0; l86 < 3; l86 = l86 + 1) fRec74[l86] = 0.0;
	for (int l87 = 0; l87 < 2; l87 = l87 + 1) fRec79[l87] = 0.0;
	for (int l88 = 0; l88 < 2; l88 = l88 + 1) fRec81[l88] = 0.0;
	for (int l89 = 0; l89 < 3; l89 = l89 + 1) fRec80[l89] = 0.0;
	for (int l90 = 0; l90 < 3; l90 = l90 + 1) fRec78[l90] = 0.0;
	for (int l91 = 0; l91 < 3; l91 = l91 + 1) fRec77[l91] = 0.0;
	for (int l92 = 0; l92 < 3; l92 = l92 + 1) fRec76[l92] = 0.0;
	for (int l93 = 0; l93 < 2; l93 = l93 + 1) fRec85[l93] = 0.0;
	for (int l94 = 0; l94 < 3; l94 = l94 + 1) fRec86[l94] = 0.0;
	for (int l95 = 0; l95 < 3; l95 = l95 + 1) fRec84[l95] = 0.0;
	for (int l96 = 0; l96 < 3; l96 = l96 + 1) fRec83[l96] = 0.0;
	for (int l97 = 0; l97 < 3; l97 = l97 + 1) fRec82[l97] = 0.0;
	for (int l98 = 0; l98 < 8192; l98 = l98 + 1) fVec14[l98] = 0.0;
	for (int l99 = 0; l99 < 8192; l99 = l99 + 1) fVec15[l99] = 0.0;
	for (int l100 = 0; l100 < 3; l100 = l100 + 1) fRec62[l100] = 0.0;
	for (int l101 = 0; l101 < 2; l101 = l101 + 1) fRec58[l101] = 0.0;
	for (int l102 = 0; l102 < 3; l102 = l102 + 1) fRec57[l102] = 0.0;
	for (int l103 = 0; l103 < 2; l103 = l103 + 1) fRec92[l103] = 0.0;
	for (int l104 = 0; l104 < 3; l104 = l104 + 1) fRec91[l104] = 0.0;
	for (int l105 = 0; l105 < 3; l105 = l105 + 1) fRec90[l105] = 0.0;
	for (int l106 = 0; l106 < 2; l106 = l106 + 1) fRec89[l106] = 0.0;
	for (int l107 = 0; l107 < 2; l107 = l107 + 1) fVec16[l107] = 0.0;
	for (int l108 = 0; l108 < 2; l108 = l108 + 1) fRec94[l108] = 0.0;
	for (int l109 = 0; l109 < 2; l109 = l109 + 1) fRec104[l109] = 0.0;
	for (int l110 = 0; l110 < 2; l110 = l110 + 1) fRec103[l110] = 0.0;
	for (int l111 = 0; l111 < 2; l111 = l111 + 1) fRec102[l111] = 0.0;
	for (int l112 = 0; l112 < 2; l112 = l112 + 1) fRec101[l112] = 0.0;
	for (int l113 = 0; l113 < 3; l113 = l113 + 1) fRec100[l113] = 0.0;
	for (int l114 = 0; l114 < 2; l114 = l114 + 1) fVec17[l114] = 0.0;
	for (int l115 = 0; l115 < 2; l115 = l115 + 1) fRec99[l115] = 0.0;
	for (int l116 = 0; l116 < 2; l116 = l116 + 1) fRec98[l116] = 0.0;
	for (int l117 = 0; l117 < 3; l117 = l117 + 1) fRec97[l117] = 0.0;
	for (int l118 = 0; l118 < 2; l118 = l118 + 1) fVec18[l118] = 0.0;
	for (int l119 = 0; l119 < 2; l119 = l119 + 1) fRec96[l119] = 0.0;
	for (int l120 = 0; l120 < 3; l120 = l120 + 1) fRec95[l120] = 0.0;
	for (int l121 = 0; l121 < 2; l121 = l121 + 1) fRec106[l121] = 0.0;
	for (int l122 = 0; l122 < 3; l122 = l122 + 1) fRec105[l122] = 0.0;
	for (int l123 = 0; l123 < 2; l123 = l123 + 1) fRec110[l123] = 0.0;
	for (int l124 = 0; l124 < 2; l124 = l124 + 1) fRec112[l124] = 0.0;
	for (int l125 = 0; l125 < 3; l125 = l125 + 1) fRec111[l125] = 0.0;
	for (int l126 = 0; l126 < 3; l126 = l126 + 1) fRec109[l126] = 0.0;
	for (int l127 = 0; l127 < 3; l127 = l127 + 1) fRec108[l127] = 0.0;
	for (int l128 = 0; l128 < 3; l128 = l128 + 1) fRec107[l128] = 0.0;
	for (int l129 = 0; l129 < 2; l129 = l129 + 1) fRec116[l129] = 0.0;
	for (int l130 = 0; l130 < 3; l130 = l130 + 1) fRec117[l130] = 0.0;
	for (int l131 = 0; l131 < 3; l131 = l131 + 1) fRec115[l131] = 0.0;
	for (int l132 = 0; l132 < 3; l132 = l132 + 1) fRec114[l132] = 0.0;
	for (int l133 = 0; l133 < 3; l133 = l133 + 1) fRec113[l133] = 0.0;
	for (int l134 = 0; l134 < 8192; l134 = l134 + 1) fVec19[l134] = 0.0;
	for (int l135 = 0; l135 < 8192; l135 = l135 + 1) fVec20[l135] = 0.0;
	for (int l136 = 0; l136 < 3; l136 = l136 + 1) fRec93[l136] = 0.0;
	for (int l137 = 0; l137 < 2; l137 = l137 + 1) fRec88[l137] = 0.0;
	for (int l138 = 0; l138 < 3; l138 = l138 + 1) fRec87[l138] = 0.0;
	for (int l139 = 0; l139 < 2; l139 = l139 + 1) fRec124[l139] = 0.0;
	for (int l140 = 0; l140 < 3; l140 = l140 + 1) fRec123[l140] = 0.0;
	for (int l141 = 0; l141 < 3; l141 = l141 + 1) fRec122[l141] = 0.0;
	for (int l142 = 0; l142 < 3; l142 = l142 + 1) fRec121[l142] = 0.0;
	for (int l143 = 0; l143 < 2; l143 = l143 + 1) fRec120[l143] = 0.0;
	for (int l144 = 0; l144 < 2; l144 = l144 + 1) fVec21[l144] = 0.0;
	for (int l145 = 0; l145 < 2; l145 = l145 + 1) fRec126[l145] = 0.0;
	for (int l146 = 0; l146 < 2; l146 = l146 + 1) fRec136[l146] = 0.0;
	for (int l147 = 0; l147 < 2; l147 = l147 + 1) fRec135[l147] = 0.0;
	for (int l148 = 0; l148 < 2; l148 = l148 + 1) fRec134[l148] = 0.0;
	for (int l149 = 0; l149 < 2; l149 = l149 + 1) fRec133[l149] = 0.0;
	for (int l150 = 0; l150 < 3; l150 = l150 + 1) fRec132[l150] = 0.0;
	for (int l151 = 0; l151 < 2; l151 = l151 + 1) fVec22[l151] = 0.0;
	for (int l152 = 0; l152 < 2; l152 = l152 + 1) fRec131[l152] = 0.0;
	for (int l153 = 0; l153 < 2; l153 = l153 + 1) fRec130[l153] = 0.0;
	for (int l154 = 0; l154 < 3; l154 = l154 + 1) fRec129[l154] = 0.0;
	for (int l155 = 0; l155 < 2; l155 = l155 + 1) fVec23[l155] = 0.0;
	for (int l156 = 0; l156 < 2; l156 = l156 + 1) fRec128[l156] = 0.0;
	for (int l157 = 0; l157 < 3; l157 = l157 + 1) fRec127[l157] = 0.0;
	for (int l158 = 0; l158 < 2; l158 = l158 + 1) fRec138[l158] = 0.0;
	for (int l159 = 0; l159 < 3; l159 = l159 + 1) fRec137[l159] = 0.0;
	for (int l160 = 0; l160 < 2; l160 = l160 + 1) fRec142[l160] = 0.0;
	for (int l161 = 0; l161 < 2; l161 = l161 + 1) fRec144[l161] = 0.0;
	for (int l162 = 0; l162 < 3; l162 = l162 + 1) fRec143[l162] = 0.0;
	for (int l163 = 0; l163 < 3; l163 = l163 + 1) fRec141[l163] = 0.0;
	for (int l164 = 0; l164 < 3; l164 = l164 + 1) fRec140[l164] = 0.0;
	for (int l165 = 0; l165 < 3; l165 = l165 + 1) fRec139[l165] = 0.0;
	for (int l166 = 0; l166 < 2; l166 = l166 + 1) fRec148[l166] = 0.0;
	for (int l167 = 0; l167 < 3; l167 = l167 + 1) fRec149[l167] = 0.0;
	for (int l168 = 0; l168 < 3; l168 = l168 + 1) fRec147[l168] = 0.0;
	for (int l169 = 0; l169 < 3; l169 = l169 + 1) fRec146[l169] = 0.0;
	for (int l170 = 0; l170 < 3; l170 = l170 + 1) fRec145[l170] = 0.0;
	for (int l171 = 0; l171 < 8192; l171 = l171 + 1) fVec24[l171] = 0.0;
	for (int l172 = 0; l172 < 8192; l172 = l172 + 1) fVec25[l172] = 0.0;
	for (int l173 = 0; l173 < 3; l173 = l173 + 1) fRec125[l173] = 0.0;
	for (int l174 = 0; l174 < 2; l174 = l174 + 1) fRec119[l174] = 0.0;
	for (int l175 = 0; l175 < 3; l175 = l175 + 1) fRec118[l175] = 0.0;
	for (int l176 = 0; l176 < 2; l176 = l176 + 1) fRec157[l176] = 0.0;
	for (int l177 = 0; l177 < 3; l177 = l177 + 1) fRec156[l177] = 0.0;
	for (int l178 = 0; l178 < 3; l178 = l178 + 1) fRec155[l178] = 0.0;
	for (int l179 = 0; l179 < 3; l179 = l179 + 1) fRec154[l179] = 0.0;
	for (int l180 = 0; l180 < 3; l180 = l180 + 1) fRec153[l180] = 0.0;
	for (int l181 = 0; l181 < 2; l181 = l181 + 1) fRec152[l181] = 0.0;
	for (int l182 = 0; l182 < 2; l182 = l182 + 1) fVec26[l182] = 0.0;
	for (int l183 = 0; l183 < 2; l183 = l183 + 1) fRec159[l183] = 0.0;
	for (int l184 = 0; l184 < 2; l184 = l184 + 1) fRec169[l184] = 0.0;
	for (int l185 = 0; l185 < 2; l185 = l185 + 1) fRec168[l185] = 0.0;
	for (int l186 = 0; l186 < 2; l186 = l186 + 1) fRec167[l186] = 0.0;
	for (int l187 = 0; l187 < 2; l187 = l187 + 1) fRec166[l187] = 0.0;
	for (int l188 = 0; l188 < 3; l188 = l188 + 1) fRec165[l188] = 0.0;
	for (int l189 = 0; l189 < 2; l189 = l189 + 1) fVec27[l189] = 0.0;
	for (int l190 = 0; l190 < 2; l190 = l190 + 1) fRec164[l190] = 0.0;
	for (int l191 = 0; l191 < 2; l191 = l191 + 1) fRec163[l191] = 0.0;
	for (int l192 = 0; l192 < 3; l192 = l192 + 1) fRec162[l192] = 0.0;
	for (int l193 = 0; l193 < 2; l193 = l193 + 1) fVec28[l193] = 0.0;
	for (int l194 = 0; l194 < 2; l194 = l194 + 1) fRec161[l194] = 0.0;
	for (int l195 = 0; l195 < 3; l195 = l195 + 1) fRec160[l195] = 0.0;
	for (int l196 = 0; l196 < 2; l196 = l196 + 1) fRec171[l196] = 0.0;
	for (int l197 = 0; l197 < 3; l197 = l197 + 1) fRec170[l197] = 0.0;
	for (int l198 = 0; l198 < 2; l198 = l198 + 1) fRec175[l198] = 0.0;
	for (int l199 = 0; l199 < 2; l199 = l199 + 1) fRec177[l199] = 0.0;
	for (int l200 = 0; l200 < 3; l200 = l200 + 1) fRec176[l200] = 0.0;
	for (int l201 = 0; l201 < 3; l201 = l201 + 1) fRec174[l201] = 0.0;
	for (int l202 = 0; l202 < 3; l202 = l202 + 1) fRec173[l202] = 0.0;
	for (int l203 = 0; l203 < 3; l203 = l203 + 1) fRec172[l203] = 0.0;
	for (int l204 = 0; l204 < 2; l204 = l204 + 1) fRec181[l204] = 0.0;
	for (int l205 = 0; l205 < 3; l205 = l205 + 1) fRec182[l205] = 0.0;
	for (int l206 = 0; l206 < 3; l206 = l206 + 1) fRec180[l206] = 0.0;
	for (int l207 = 0; l207 < 3; l207 = l207 + 1) fRec179[l207] = 0.0;
	for (int l208 = 0; l208 < 3; l208 = l208 + 1) fRec178[l208] = 0.0;
	for (int l209 = 0; l209 < 8192; l209 = l209 + 1) fVec29[l209] = 0.0;
	for (int l210 = 0; l210 < 8192; l210 = l210 + 1) fVec30[l210] = 0.0;
	for (int l211 = 0; l211 < 3; l211 = l211 + 1) fRec158[l211] = 0.0;
	for (int l212 = 0; l212 < 2; l212 = l212 + 1) fRec151[l212] = 0.0;
	for (int l213 = 0; l213 < 3; l213 = l213 + 1) fRec150[l213] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = std::tan(62831.853071795864 / fConst0);
	fConst2 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst1));
	double fConst3 = 1.0 / fConst1;
	fConst4 = (fConst3 + -1.414213562373095) / fConst1 + 1.0;
	fConst5 = 1.0 / ((fConst3 + 1.414213562373095) / fConst1 + 1.0);
	double fConst6 = 2.08237464600982e-05 * fConst0;
	double fConst7 = fConst6 + 0.000460169915286817;
	fConst8 = (0.000460169915286817 - fConst6) / fConst7;
	double fConst9 = 2.08237184654756e-05 * fConst0;
	double fConst10 = fConst9 + 0.000461513657169036;
	fConst11 = (0.000461513657169036 - fConst9) / fConst10;
	double fConst12 = std::tan(270.1769682087222 / fConst0);
	double fConst13 = mydsp_faustpower2_f(fConst12);
	fConst14 = 1.0 / fConst13;
	fConst15 = 2.0 * (1.0 - fConst14);
	double fConst16 = 1.0 / fConst12;
	fConst17 = (fConst16 + -1.0000000000000004) / fConst12 + 1.0;
	fConst18 = 1.0 / ((fConst16 + 1.0000000000000004) / fConst12 + 1.0);
	double fConst19 = std::tan(659.7344572538566 / fConst0);
	double fConst20 = mydsp_faustpower2_f(fConst19);
	fConst21 = 1.0 / fConst20;
	fConst22 = 2.0 * (1.0 - fConst21);
	double fConst23 = 1.0 / fConst19;
	fConst24 = (fConst23 + -1.0000000000000004) / fConst19 + 1.0;
	fConst25 = 1.0 / ((fConst23 + 1.0000000000000004) / fConst19 + 1.0);
	double fConst26 = std::tan(3769.9111843077517 / fConst0);
	double fConst27 = mydsp_faustpower2_f(fConst26);
	fConst28 = 1.0 / fConst27;
	fConst29 = 2.0 * (1.0 - fConst28);
	double fConst30 = 1.0 / fConst26;
	fConst31 = (fConst30 + -1.0000000000000004) / fConst26 + 1.0;
	fConst32 = 1.0 / ((fConst30 + 1.0000000000000004) / fConst26 + 1.0);
	double fConst33 = std::tan(20517.741620594938 / fConst0);
	double fConst34 = mydsp_faustpower2_f(fConst33);
	fConst35 = 1.0 / fConst34;
	fConst36 = 2.0 * (1.0 - fConst35);
	fConst37 = 1.0 / fConst33;
	fConst38 = (fConst37 + -1.0000000000000004) / fConst33 + 1.0;
	fConst39 = 1.0 / ((fConst37 + 1.0000000000000004) / fConst33 + 1.0);
	fConst40 = 1.0 - fConst37;
	double fConst41 = fConst37 + 1.0;
	fConst42 = 1.0 / fConst41;
	fConst43 = 1.0 - fConst30;
	double fConst44 = fConst30 + 1.0;
	fConst45 = 1.0 / fConst44;
	fConst46 = 1.0 - fConst23;
	double fConst47 = fConst23 + 1.0;
	fConst48 = 1.0 / fConst47;
	fConst49 = 1.0 - fConst16;
	double fConst50 = fConst16 + 1.0;
	fConst51 = 1.0 / fConst50;
	fConst52 = fConst0 / fConst10;
	fConst53 = 3.141592653589793 / fConst0;
	double fConst54 = std::tan(47123.8898038469 / fConst0);
	fConst55 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst54));
	double fConst56 = 1.0 / fConst54;
	fConst57 = (fConst56 + -1.414213562373095) / fConst54 + 1.0;
	fConst58 = 1.0 / ((fConst56 + 1.414213562373095) / fConst54 + 1.0);
	double fConst59 = std::tan(157.07963267948966 / fConst0);
	fConst60 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst59));
	double fConst61 = fConst0 * std::sin(314.1592653589793 / fConst0);
	double fConst62 = 392.6990816987241 / fConst61;
	double fConst63 = 1.0 / fConst59;
	fConst64 = (fConst63 - fConst62) / fConst59 + 1.0;
	fConst65 = 1.0 / ((fConst63 + fConst62) / fConst59 + 1.0);
	double fConst66 = std::tan(78.53981633974483 / fConst0);
	fConst67 = 1.0 / fConst66;
	double fConst68 = fConst67 + 1.0;
	fConst69 = 1.0 - fConst67;
	fConst70 = fConst69 / fConst68;
	fConst71 = (fConst56 + -1.0000000000000004) / fConst54 + 1.0;
	fConst72 = 1.0 / ((fConst56 + 1.0000000000000004) / fConst54 + 1.0);
	fConst73 = 1.0 - fConst56;
	fConst74 = 1.0 / (fConst56 + 1.0);
	fConst75 = 1.0 / (fConst66 * fConst68);
	fConst76 = 0.0 - fConst75;
	fConst77 = 1.0 / fConst68;
	double fConst78 = 554.7021966383262 / fConst61;
	fConst79 = (fConst63 - fConst78) / fConst59 + 1.0;
	fConst80 = (fConst63 + fConst78) / fConst59 + 1.0;
	double fConst81 = std::tan(39269.90816987241 / fConst0);
	double fConst82 = 1.0 / fConst81;
	fConst83 = 1.0 - fConst82;
	fConst84 = 1.0 / (fConst82 + 1.0);
	fConst85 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst81));
	fConst86 = (fConst82 + -1.414213562373095) / fConst81 + 1.0;
	fConst87 = 1.0 / ((fConst82 + 1.414213562373095) / fConst81 + 1.0);
	double fConst88 = std::tan(31415.926535897932 / fConst0);
	double fConst89 = 1.0 / fConst88;
	fConst90 = 1.0 - fConst89;
	fConst91 = 1.0 / (fConst89 + 1.0);
	fConst92 = (fConst56 + -0.7653668647301795) / fConst54 + 1.0;
	fConst93 = 1.0 / ((fConst56 + 0.7653668647301795) / fConst54 + 1.0);
	fConst94 = (fConst56 + -1.8477590650225735) / fConst54 + 1.0;
	fConst95 = 1.0 / ((fConst56 + 1.8477590650225735) / fConst54 + 1.0);
	double fConst96 = 1.0 / std::tan(14284.82179587279 / fConst0);
	fConst97 = 1.0 - fConst96;
	fConst98 = 1.0 / (fConst96 + 1.0);
	double fConst99 = std::tan(235.61944901923448 / fConst0);
	fConst100 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst99));
	double fConst101 = fConst0 * std::sin(471.23889803846896 / fConst0);
	double fConst102 = 589.0486225480862 / fConst101;
	double fConst103 = 1.0 / fConst99;
	fConst104 = (fConst103 - fConst102) / fConst99 + 1.0;
	fConst105 = 1.0 / ((fConst103 + fConst102) / fConst99 + 1.0);
	double fConst106 = std::tan(109.95574287564276 / fConst0);
	fConst107 = 1.0 / fConst106;
	fConst108 = 1.0 - fConst107;
	double fConst109 = fConst107 + 1.0;
	fConst110 = 1.0 / fConst109;
	fConst111 = 0.0 - 1.0 / (fConst106 * fConst109);
	double fConst112 = 1175.3065182545242 / fConst101;
	fConst113 = (fConst103 - fConst112) / fConst99 + 1.0;
	fConst114 = (fConst103 + fConst112) / fConst99 + 1.0;
	fConst115 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst88));
	fConst116 = (fConst89 + -0.7653668647301795) / fConst88 + 1.0;
	fConst117 = 1.0 / ((fConst89 + 0.7653668647301795) / fConst88 + 1.0);
	fConst118 = (fConst89 + -1.8477590650225735) / fConst88 + 1.0;
	fConst119 = 1.0 / ((fConst89 + 1.8477590650225735) / fConst88 + 1.0);
	fConst120 = 23561.94490192345 / fConst0;
	double fConst121 = std::tan(9424.77796076938 / fConst0);
	double fConst122 = 1.0 / fConst121;
	double fConst123 = fConst122 + 1.0;
	fConst124 = (1.0 - fConst122) / fConst123;
	fConst125 = 1.0 / (fConst121 * fConst123);
	fConst126 = 0.0 - fConst125;
	double fConst127 = 1.0 / std::tan(785.3981633974482 / fConst0);
	fConst128 = 1.0 - fConst127;
	fConst129 = 1.0 / (fConst127 + 1.0);
	fConst130 = 6.283185307179586 / fConst0;
	fConst131 = 0.005 * fConst0;
	fConst132 = 1e+01 / fConst0;
	fConst133 = 0.0 - fConst132;
	fConst134 = 0.000257077078239627 * fConst0;
	fConst135 = 1.0 / fConst7;
	fConst136 = fConst49 / fConst50;
	fConst137 = 1.0 / (fConst12 * fConst50);
	fConst138 = 0.0 - fConst137;
	fConst139 = 0.0 - 2.0 / fConst13;
	fConst140 = 1.0 - fConst49 / fConst12;
	fConst141 = 1.0 / (fConst50 / fConst12 + 1.0);
	fConst142 = fConst46 / fConst47;
	fConst143 = 1.0 / (fConst19 * fConst47);
	fConst144 = 0.0 - fConst143;
	fConst145 = 0.0 - 2.0 / fConst20;
	fConst146 = 1.0 - fConst46 / fConst19;
	fConst147 = 1.0 / (fConst47 / fConst19 + 1.0);
	fConst148 = fConst43 / fConst44;
	fConst149 = 1.0 / (fConst26 * fConst44);
	fConst150 = 0.0 - fConst149;
	fConst151 = 0.0 - 2.0 / fConst27;
	fConst152 = 1.0 - fConst43 / fConst26;
	fConst153 = 1.0 / (fConst44 / fConst26 + 1.0);
	fConst154 = 0.0 - 1.0 / (fConst33 * fConst41);
	fConst155 = 0.0 - 2.0 / fConst34;
	IOTA0 = 0;
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void Dsp::mem_alloc()
{
	if (!fVec9) fVec9 = new double[8192];
	if (!fVec10) fVec10 = new double[8192];
	if (!fVec14) fVec14 = new double[8192];
	if (!fVec15) fVec15 = new double[8192];
	if (!fVec19) fVec19 = new double[8192];
	if (!fVec20) fVec20 = new double[8192];
	if (!fVec24) fVec24 = new double[8192];
	if (!fVec25) fVec25 = new double[8192];
	if (!fVec29) fVec29 = new double[8192];
	if (!fVec30) fVec30 = new double[8192];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec9) { delete fVec9; fVec9 = 0; }
	if (fVec10) { delete fVec10; fVec10 = 0; }
	if (fVec14) { delete fVec14; fVec14 = 0; }
	if (fVec15) { delete fVec15; fVec15 = 0; }
	if (fVec19) { delete fVec19; fVec19 = 0; }
	if (fVec20) { delete fVec20; fVec20 = 0; }
	if (fVec24) { delete fVec24; fVec24 = 0; }
	if (fVec25) { delete fVec25; fVec25 = 0; }
	if (fVec29) { delete fVec29; fVec29 = 0; }
	if (fVec30) { delete fVec30; fVec30 = 0; }
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
#define fCheckbox0 (*fCheckbox0_)
#define fVslider0 (*fVslider0_)
#define fCheckbox1 (*fCheckbox1_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
#define fVslider4 (*fVslider4_)
#define fVslider5 (*fVslider5_)
#define fVslider6 (*fVslider6_)
#define fVslider7 (*fVslider7_)
	int iSlow0 = int(double(fCheckbox0));
	double fSlow1 = 0.00036676987543879196 * (std::exp(3.0 * double(fVslider0)) + -1.0);
	double fSlow2 = double(fCheckbox1);
	int iSlow3 = int(fSlow2);
	double fSlow4 = 1.0 / std::tan(fConst53 * double(((iSlow3) ? 2274 : 4547)));
	double fSlow5 = fSlow4 + 1.0;
	double fSlow6 = 1.0 - fSlow4;
	int iSlow7 = int(double(fVslider1));
	double fSlow8 = std::tan(fConst120 * (2.0 - fSlow2));
	double fSlow9 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fSlow8));
	double fSlow10 = 1.0 / fSlow8;
	double fSlow11 = (fSlow10 + -1.414213562373095) / fSlow8 + 1.0;
	double fSlow12 = 1.0 / ((fSlow10 + 1.414213562373095) / fSlow8 + 1.0);
	double fSlow13 = 4.739999999999478e-06 * double(fVslider2);
	double fSlow14 = fConst130 * double(fVslider3);
	double fSlow15 = fConst131 * double(fVslider4);
	double fSlow16 = fConst130 * double(fVslider5);
	double fSlow17 = fConst131 * double(fVslider6);
	double fSlow18 = 0.00036676987543879196 * (std::exp(3.0 * (1.0 - double(fVslider7))) + -1.0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		iVec0[0] = 1;
		double fTemp0 = double(input0[i0]);
		fVec1[0] = fTemp0;
		fRec10[0] = 0.0 - fConst42 * (fConst40 * fRec10[1] - (fTemp0 + fVec1[1]));
		fRec9[0] = fRec10[0] - fConst39 * (fConst38 * fRec9[2] + fConst36 * fRec9[1]);
		double fTemp1 = fRec9[2] + fRec9[0] + 2.0 * fRec9[1];
		fVec2[0] = fTemp1;
		fRec8[0] = 0.0 - fConst45 * (fConst43 * fRec8[1] - fConst39 * (fTemp1 + fVec2[1]));
		fRec7[0] = fRec8[0] - fConst32 * (fConst31 * fRec7[2] + fConst29 * fRec7[1]);
		double fTemp2 = fRec7[2] + fRec7[0] + 2.0 * fRec7[1];
		fVec3[0] = fTemp2;
		fRec6[0] = 0.0 - fConst48 * (fConst46 * fRec6[1] - fConst32 * (fTemp2 + fVec3[1]));
		fRec5[0] = fRec6[0] - fConst25 * (fConst24 * fRec5[2] + fConst22 * fRec5[1]);
		double fTemp3 = fRec5[2] + fRec5[0] + 2.0 * fRec5[1];
		fVec4[0] = fTemp3;
		fRec4[0] = 0.0 - fConst51 * (fConst49 * fRec4[1] - fConst25 * (fTemp3 + fVec4[1]));
		fRec3[0] = fRec4[0] - fConst18 * (fConst17 * fRec3[2] + fConst15 * fRec3[1]);
		fRec2[0] = fConst18 * (fRec3[2] + fRec3[0] + 2.0 * fRec3[1]) - fConst11 * fRec2[1];
		fRec11[0] = fSlow1 + 0.993 * fRec11[1];
		double fTemp4 = 0.0 - 0.000275189947996364 * fRec11[0];
		double fTemp5 = fConst52 * (fRec2[0] * fTemp4 + 0.000275189947996364 * fRec11[0] * fRec2[1]);
		double fTemp6 = ((signbit(fTemp5)) ? input12au7_negclip(fTemp5) : input12au7clip(fTemp5));
		fVec5[0] = fTemp6;
		fRec13[0] = 0.0 - (fSlow6 * fRec13[1] - (fRec12[1] + fRec12[2])) / fSlow5;
		double fTemp7 = fConst60 * fRec16[1];
		fRec23[0] = 0.0 - (fSlow6 * fRec23[1] - (fTemp6 + fVec5[1])) / fSlow5;
		fRec22[0] = fRec23[0] - 0.3 * fRec22[1];
		fRec21[0] = 2.0 / (std::exp(0.0 - 5.0 * fRec22[0]) + 1.0) + 0.3 * fRec21[1] + -1.0;
		fRec20[0] = 0.0 - fConst74 * (fConst73 * fRec20[1] - (fRec21[0] + fRec21[1]));
		fRec19[0] = fRec20[0] - fConst72 * (fConst71 * fRec19[2] + fConst55 * fRec19[1]);
		double fTemp8 = fRec19[2] + fRec19[0] + 2.0 * fRec19[1];
		fVec6[0] = fTemp8;
		fRec18[0] = fConst72 * (fConst75 * fTemp8 + fConst76 * fVec6[1]) - fConst70 * fRec18[1];
		fRec17[0] = fConst76 * fRec18[1] - fConst77 * (fConst69 * fRec17[1] - fConst67 * fRec18[0]);
		fRec16[0] = fRec17[0] - fConst65 * (fConst64 * fRec16[2] + fTemp7);
		double fTemp9 = fTemp7 + fConst80 * fRec16[0] + fConst79 * fRec16[2];
		fVec7[0] = fTemp9;
		fRec15[0] = 0.0 - fConst84 * (fConst83 * fRec15[1] - fConst65 * (fTemp9 + fVec7[1]));
		fRec14[0] = fRec15[0] - fConst58 * (fConst57 * fRec14[2] + fConst55 * fRec14[1]);
		fRec25[0] = 0.0 - fConst91 * (fConst90 * fRec25[1] - (fRec17[0] + fRec17[1]));
		fRec24[0] = fRec25[0] - fConst87 * (fConst86 * fRec24[2] + fConst85 * fRec24[1]);
		fRec29[0] = 0.0 - fConst98 * (fConst97 * fRec29[1] - (fRec28[1] + fRec28[2]));
		double fTemp10 = fConst100 * fRec30[1];
		fRec31[0] = fConst111 * fRec18[1] - fConst110 * (fConst108 * fRec31[1] - fConst107 * fRec18[0]);
		fRec30[0] = fRec31[0] - fConst105 * (fConst104 * fRec30[2] + fTemp10);
		fRec28[0] = fConst105 * (fTemp10 + fConst114 * fRec30[0] + fConst113 * fRec30[2]) - fRec29[0];
		fRec27[0] = fRec28[0] - fConst95 * (fConst94 * fRec27[2] + fConst55 * fRec27[1]);
		fRec26[0] = fConst95 * (fRec27[2] + fRec27[0] + 2.0 * fRec27[1]) - fConst93 * (fConst92 * fRec26[2] + fConst55 * fRec26[1]);
		fRec35[0] = 0.0 - fConst98 * (fConst97 * fRec35[1] - (fRec34[1] + fRec34[2]));
		double fTemp11 = fConst100 * fRec36[1];
		fRec36[0] = fRec17[0] - fConst105 * (fConst104 * fRec36[2] + fTemp11);
		fRec34[0] = fConst105 * (fTemp11 + fConst114 * fRec36[0] + fConst113 * fRec36[2]) - fRec35[0];
		fRec33[0] = fRec34[0] - fConst119 * (fConst118 * fRec33[2] + fConst115 * fRec33[1]);
		fRec32[0] = fConst119 * (fRec33[2] + fRec33[0] + 2.0 * fRec33[1]) - fConst117 * (fConst116 * fRec32[2] + fConst115 * fRec32[1]);
		iRec39[0] = 1103515245 * iRec39[1] + 12345;
		fRec40[0] = fSlow13 + 0.9999 * fRec40[1];
		double fTemp12 = fRec40[0] * double(iRec39[0]);
		fVec8[0] = fTemp12;
		fRec38[0] = 4.656612875245797e-10 * (fConst125 * fTemp12 + fConst126 * fVec8[1]) - fConst124 * fRec38[1];
		fRec41[0] = fConst129 * (4.656612875245797e-10 * (fTemp12 + fVec8[1]) - fConst128 * fRec41[1]);
		fRec37[0] = fRec41[0] + 0.2 * fRec38[0] - fSlow12 * (fSlow11 * fRec37[2] + fSlow9 * fRec37[1]);
		double fTemp13 = fSlow12 * (fRec37[2] + fRec37[0] + 2.0 * fRec37[1]);
		double fTemp14 = fTemp13 + ((iSlow7) ? ((iSlow3) ? fConst117 * (fRec32[2] + fRec32[0] + 2.0 * fRec32[1]) : fConst93 * (fRec26[2] + fRec26[0] + 2.0 * fRec26[1])) : ((iSlow3) ? fConst87 * (fRec24[2] + fRec24[0] + 2.0 * fRec24[1]) : fConst58 * (fRec14[2] + fRec14[0] + 2.0 * fRec14[1])));
		fVec9[IOTA0 & 8191] = fTemp14;
		double fTemp15 = double(1 - iVec0[1]);
		fRec48[0] = fRec48[1] + fSlow14 * (0.0 - fRec46[1]);
		fRec47[0] = fSlow14 * fRec48[0] + fTemp15 + fRec47[1];
		fRec46[0] = fRec47[0];
		double fTemp16 = fSlow15 * (std::max<double>(0.0, 0.5 * (fRec46[0] + 1.0)) + 1.0);
		double fTemp17 = ((fRec42[1] != 0.0) ? (((fRec43[1] > 0.0) & (fRec43[1] < 1.0)) ? fRec42[1] : 0.0) : (((fRec43[1] == 0.0) & (fTemp16 != fRec44[1])) ? fConst132 : (((fRec43[1] == 1.0) & (fTemp16 != fRec45[1])) ? fConst133 : 0.0)));
		fRec42[0] = fTemp17;
		fRec43[0] = std::max<double>(0.0, std::min<double>(1.0, fRec43[1] + fTemp17));
		fRec44[0] = (((fRec43[1] >= 1.0) & (fRec45[1] != fTemp16)) ? fTemp16 : fRec44[1]);
		fRec45[0] = (((fRec43[1] <= 0.0) & (fRec44[1] != fTemp16)) ? fTemp16 : fRec45[1]);
		int iTemp18 = int(std::min<double>(4096.0, std::max<double>(0.0, fRec44[0])));
		double fTemp19 = fVec9[(IOTA0 - iTemp18) & 8191];
		int iTemp20 = int(std::min<double>(4096.0, std::max<double>(0.0, fRec45[0])));
		double fTemp21 = fTemp19 + fRec43[0] * (fVec9[(IOTA0 - iTemp20) & 8191] - fTemp19);
		fVec10[IOTA0 & 8191] = fTemp21;
		fRec55[0] = fRec55[1] + fSlow16 * (0.0 - fRec53[1]);
		fRec54[0] = fSlow16 * fRec55[0] + fTemp15 + fRec54[1];
		fRec53[0] = fRec54[0];
		double fTemp22 = fSlow17 * (std::max<double>(0.0, 0.5 * (fRec53[0] + 1.0)) + 1.0);
		double fTemp23 = ((fRec49[1] != 0.0) ? (((fRec50[1] > 0.0) & (fRec50[1] < 1.0)) ? fRec49[1] : 0.0) : (((fRec50[1] == 0.0) & (fTemp22 != fRec51[1])) ? fConst132 : (((fRec50[1] == 1.0) & (fTemp22 != fRec52[1])) ? fConst133 : 0.0)));
		fRec49[0] = fTemp23;
		fRec50[0] = std::max<double>(0.0, std::min<double>(1.0, fRec50[1] + fTemp23));
		fRec51[0] = (((fRec50[1] >= 1.0) & (fRec52[1] != fTemp22)) ? fTemp22 : fRec51[1]);
		fRec52[0] = (((fRec50[1] <= 0.0) & (fRec51[1] != fTemp22)) ? fTemp22 : fRec52[1]);
		int iTemp24 = int(std::min<double>(4096.0, std::max<double>(0.0, fRec51[0])));
		double fTemp25 = fVec10[(IOTA0 - iTemp24) & 8191];
		int iTemp26 = int(std::min<double>(4096.0, std::max<double>(0.0, fRec52[0])));
		fRec12[0] = fTemp25 + fRec50[0] * (fVec10[(IOTA0 - iTemp26) & 8191] - fTemp25) - fRec13[0];
		fRec1[0] = ((iSlow0) ? fRec12[0] : fTemp6) - fConst8 * fRec1[1];
		fRec56[0] = fSlow18 + 0.993 * fRec56[1];
		double fTemp27 = 0.0 - 0.000257077078239627 * fRec56[0] + 0.000257077078239627;
		double fTemp28 = 0.0 - fConst134 * (1.0 - fRec56[0]);
		double fTemp29 = fConst135 * (fRec1[0] * fTemp28 + fConst0 * fTemp27 * fRec1[1]);
		fRec0[0] = ((signbit(fTemp29)) ? output12au7_negclip(fTemp29) : output12au7clip(fTemp29)) - fConst5 * (fConst4 * fRec0[2] + fConst2 * fRec0[1]);
		fRec61[0] = fConst25 * (fConst137 * fTemp3 + fConst138 * fVec4[1]) - fConst136 * fRec61[1];
		fRec60[0] = fRec61[0] - fConst18 * (fConst17 * fRec60[2] + fConst15 * fRec60[1]);
		fRec59[0] = fConst18 * (fConst14 * fRec60[0] + fConst139 * fRec60[1] + fConst14 * fRec60[2]) - fConst11 * fRec59[1];
		double fTemp30 = fConst52 * (fRec59[0] * fTemp4 + 0.000275189947996364 * fRec11[0] * fRec59[1]);
		double fTemp31 = ((signbit(fTemp30)) ? input12au7_negclip(fTemp30) : input12au7clip(fTemp30));
		fVec11[0] = fTemp31;
		fRec63[0] = 0.0 - (fSlow6 * fRec63[1] - (fRec62[1] + fRec62[2])) / fSlow5;
		double fTemp32 = fConst60 * fRec66[1];
		fRec73[0] = 0.0 - (fSlow6 * fRec73[1] - (fTemp31 + fVec11[1])) / fSlow5;
		fRec72[0] = fRec73[0] - 0.3 * fRec72[1];
		fRec71[0] = 2.0 / (std::exp(0.0 - 5.0 * fRec72[0]) + 1.0) + 0.3 * fRec71[1] + -1.0;
		fRec70[0] = 0.0 - fConst74 * (fConst73 * fRec70[1] - (fRec71[0] + fRec71[1]));
		fRec69[0] = fRec70[0] - fConst72 * (fConst71 * fRec69[2] + fConst55 * fRec69[1]);
		double fTemp33 = fRec69[2] + fRec69[0] + 2.0 * fRec69[1];
		fVec12[0] = fTemp33;
		fRec68[0] = fConst72 * (fConst75 * fTemp33 + fConst76 * fVec12[1]) - fConst70 * fRec68[1];
		fRec67[0] = fConst76 * fRec68[1] - fConst77 * (fConst69 * fRec67[1] - fConst67 * fRec68[0]);
		fRec66[0] = fRec67[0] - fConst65 * (fConst64 * fRec66[2] + fTemp32);
		double fTemp34 = fTemp32 + fConst80 * fRec66[0] + fConst79 * fRec66[2];
		fVec13[0] = fTemp34;
		fRec65[0] = 0.0 - fConst84 * (fConst83 * fRec65[1] - fConst65 * (fTemp34 + fVec13[1]));
		fRec64[0] = fRec65[0] - fConst58 * (fConst57 * fRec64[2] + fConst55 * fRec64[1]);
		fRec75[0] = 0.0 - fConst91 * (fConst90 * fRec75[1] - (fRec67[0] + fRec67[1]));
		fRec74[0] = fRec75[0] - fConst87 * (fConst86 * fRec74[2] + fConst85 * fRec74[1]);
		fRec79[0] = 0.0 - fConst98 * (fConst97 * fRec79[1] - (fRec78[1] + fRec78[2]));
		double fTemp35 = fConst100 * fRec80[1];
		fRec81[0] = fConst111 * fRec68[1] - fConst110 * (fConst108 * fRec81[1] - fConst107 * fRec68[0]);
		fRec80[0] = fRec81[0] - fConst105 * (fConst104 * fRec80[2] + fTemp35);
		fRec78[0] = fConst105 * (fTemp35 + fConst114 * fRec80[0] + fConst113 * fRec80[2]) - fRec79[0];
		fRec77[0] = fRec78[0] - fConst95 * (fConst94 * fRec77[2] + fConst55 * fRec77[1]);
		fRec76[0] = fConst95 * (fRec77[2] + fRec77[0] + 2.0 * fRec77[1]) - fConst93 * (fConst92 * fRec76[2] + fConst55 * fRec76[1]);
		fRec85[0] = 0.0 - fConst98 * (fConst97 * fRec85[1] - (fRec84[1] + fRec84[2]));
		double fTemp36 = fConst100 * fRec86[1];
		fRec86[0] = fRec67[0] - fConst105 * (fConst104 * fRec86[2] + fTemp36);
		fRec84[0] = fConst105 * (fTemp36 + fConst114 * fRec86[0] + fConst113 * fRec86[2]) - fRec85[0];
		fRec83[0] = fRec84[0] - fConst119 * (fConst118 * fRec83[2] + fConst115 * fRec83[1]);
		fRec82[0] = fConst119 * (fRec83[2] + fRec83[0] + 2.0 * fRec83[1]) - fConst117 * (fConst116 * fRec82[2] + fConst115 * fRec82[1]);
		double fTemp37 = fTemp13 + ((iSlow7) ? ((iSlow3) ? fConst117 * (fRec82[2] + fRec82[0] + 2.0 * fRec82[1]) : fConst93 * (fRec76[2] + fRec76[0] + 2.0 * fRec76[1])) : ((iSlow3) ? fConst87 * (fRec74[2] + fRec74[0] + 2.0 * fRec74[1]) : fConst58 * (fRec64[2] + fRec64[0] + 2.0 * fRec64[1])));
		fVec14[IOTA0 & 8191] = fTemp37;
		double fTemp38 = fVec14[(IOTA0 - iTemp18) & 8191];
		double fTemp39 = fTemp38 + fRec43[0] * (fVec14[(IOTA0 - iTemp20) & 8191] - fTemp38);
		fVec15[IOTA0 & 8191] = fTemp39;
		double fTemp40 = fVec15[(IOTA0 - iTemp24) & 8191];
		fRec62[0] = fTemp40 + fRec50[0] * (fVec15[(IOTA0 - iTemp26) & 8191] - fTemp40) - fRec63[0];
		fRec58[0] = ((iSlow0) ? fRec62[0] : fTemp31) - fConst8 * fRec58[1];
		double fTemp41 = fConst135 * (fRec58[0] * fTemp28 + fConst0 * fTemp27 * fRec58[1]);
		fRec57[0] = ((signbit(fTemp41)) ? output12au7_negclip(fTemp41) : output12au7clip(fTemp41)) - fConst5 * (fConst4 * fRec57[2] + fConst2 * fRec57[1]);
		double fTemp42 = fConst15 * fRec90[1];
		fRec92[0] = fConst32 * (fConst143 * fTemp2 + fConst144 * fVec3[1]) - fConst142 * fRec92[1];
		fRec91[0] = fRec92[0] - fConst25 * (fConst24 * fRec91[2] + fConst22 * fRec91[1]);
		fRec90[0] = fConst25 * (fConst21 * fRec91[0] + fConst145 * fRec91[1] + fConst21 * fRec91[2]) - fConst141 * (fConst140 * fRec90[2] + fTemp42);
		fRec89[0] = fRec90[2] + fConst141 * (fTemp42 + fConst140 * fRec90[0]) - fConst11 * fRec89[1];
		double fTemp43 = fConst52 * (fRec89[0] * fTemp4 + 0.000275189947996364 * fRec11[0] * fRec89[1]);
		double fTemp44 = ((signbit(fTemp43)) ? input12au7_negclip(fTemp43) : input12au7clip(fTemp43));
		fVec16[0] = fTemp44;
		fRec94[0] = 0.0 - (fSlow6 * fRec94[1] - (fRec93[1] + fRec93[2])) / fSlow5;
		double fTemp45 = fConst60 * fRec97[1];
		fRec104[0] = 0.0 - (fSlow6 * fRec104[1] - (fTemp44 + fVec16[1])) / fSlow5;
		fRec103[0] = fRec104[0] - 0.3 * fRec103[1];
		fRec102[0] = 2.0 / (std::exp(0.0 - 5.0 * fRec103[0]) + 1.0) + 0.3 * fRec102[1] + -1.0;
		fRec101[0] = 0.0 - fConst74 * (fConst73 * fRec101[1] - (fRec102[0] + fRec102[1]));
		fRec100[0] = fRec101[0] - fConst72 * (fConst71 * fRec100[2] + fConst55 * fRec100[1]);
		double fTemp46 = fRec100[2] + fRec100[0] + 2.0 * fRec100[1];
		fVec17[0] = fTemp46;
		fRec99[0] = fConst72 * (fConst75 * fTemp46 + fConst76 * fVec17[1]) - fConst70 * fRec99[1];
		fRec98[0] = fConst76 * fRec99[1] - fConst77 * (fConst69 * fRec98[1] - fConst67 * fRec99[0]);
		fRec97[0] = fRec98[0] - fConst65 * (fConst64 * fRec97[2] + fTemp45);
		double fTemp47 = fTemp45 + fConst80 * fRec97[0] + fConst79 * fRec97[2];
		fVec18[0] = fTemp47;
		fRec96[0] = 0.0 - fConst84 * (fConst83 * fRec96[1] - fConst65 * (fTemp47 + fVec18[1]));
		fRec95[0] = fRec96[0] - fConst58 * (fConst57 * fRec95[2] + fConst55 * fRec95[1]);
		fRec106[0] = 0.0 - fConst91 * (fConst90 * fRec106[1] - (fRec98[0] + fRec98[1]));
		fRec105[0] = fRec106[0] - fConst87 * (fConst86 * fRec105[2] + fConst85 * fRec105[1]);
		fRec110[0] = 0.0 - fConst98 * (fConst97 * fRec110[1] - (fRec109[1] + fRec109[2]));
		double fTemp48 = fConst100 * fRec111[1];
		fRec112[0] = fConst111 * fRec99[1] - fConst110 * (fConst108 * fRec112[1] - fConst107 * fRec99[0]);
		fRec111[0] = fRec112[0] - fConst105 * (fConst104 * fRec111[2] + fTemp48);
		fRec109[0] = fConst105 * (fTemp48 + fConst114 * fRec111[0] + fConst113 * fRec111[2]) - fRec110[0];
		fRec108[0] = fRec109[0] - fConst95 * (fConst94 * fRec108[2] + fConst55 * fRec108[1]);
		fRec107[0] = fConst95 * (fRec108[2] + fRec108[0] + 2.0 * fRec108[1]) - fConst93 * (fConst92 * fRec107[2] + fConst55 * fRec107[1]);
		fRec116[0] = 0.0 - fConst98 * (fConst97 * fRec116[1] - (fRec115[1] + fRec115[2]));
		double fTemp49 = fConst100 * fRec117[1];
		fRec117[0] = fRec98[0] - fConst105 * (fConst104 * fRec117[2] + fTemp49);
		fRec115[0] = fConst105 * (fTemp49 + fConst114 * fRec117[0] + fConst113 * fRec117[2]) - fRec116[0];
		fRec114[0] = fRec115[0] - fConst119 * (fConst118 * fRec114[2] + fConst115 * fRec114[1]);
		fRec113[0] = fConst119 * (fRec114[2] + fRec114[0] + 2.0 * fRec114[1]) - fConst117 * (fConst116 * fRec113[2] + fConst115 * fRec113[1]);
		double fTemp50 = fTemp13 + ((iSlow7) ? ((iSlow3) ? fConst117 * (fRec113[2] + fRec113[0] + 2.0 * fRec113[1]) : fConst93 * (fRec107[2] + fRec107[0] + 2.0 * fRec107[1])) : ((iSlow3) ? fConst87 * (fRec105[2] + fRec105[0] + 2.0 * fRec105[1]) : fConst58 * (fRec95[2] + fRec95[0] + 2.0 * fRec95[1])));
		fVec19[IOTA0 & 8191] = fTemp50;
		double fTemp51 = fVec19[(IOTA0 - iTemp18) & 8191];
		double fTemp52 = fTemp51 + fRec43[0] * (fVec19[(IOTA0 - iTemp20) & 8191] - fTemp51);
		fVec20[IOTA0 & 8191] = fTemp52;
		double fTemp53 = fVec20[(IOTA0 - iTemp24) & 8191];
		fRec93[0] = fTemp53 + fRec50[0] * (fVec20[(IOTA0 - iTemp26) & 8191] - fTemp53) - fRec94[0];
		fRec88[0] = ((iSlow0) ? fRec93[0] : fTemp44) - fConst8 * fRec88[1];
		double fTemp54 = fConst135 * (fRec88[0] * fTemp28 + fConst0 * fTemp27 * fRec88[1]);
		fRec87[0] = ((signbit(fTemp54)) ? output12au7_negclip(fTemp54) : output12au7clip(fTemp54)) - fConst5 * (fConst4 * fRec87[2] + fConst2 * fRec87[1]);
		double fTemp55 = fConst15 * fRec121[1];
		double fTemp56 = fConst22 * fRec122[1];
		fRec124[0] = fConst39 * (fConst149 * fTemp1 + fConst150 * fVec2[1]) - fConst148 * fRec124[1];
		fRec123[0] = fRec124[0] - fConst32 * (fConst31 * fRec123[2] + fConst29 * fRec123[1]);
		fRec122[0] = fConst32 * (fConst28 * fRec123[0] + fConst151 * fRec123[1] + fConst28 * fRec123[2]) - fConst147 * (fConst146 * fRec122[2] + fTemp56);
		fRec121[0] = fRec122[2] + fConst147 * (fTemp56 + fConst146 * fRec122[0]) - fConst141 * (fConst140 * fRec121[2] + fTemp55);
		fRec120[0] = fRec121[2] + fConst141 * (fTemp55 + fConst140 * fRec121[0]) - fConst11 * fRec120[1];
		double fTemp57 = fConst52 * (fRec120[0] * fTemp4 + 0.000275189947996364 * fRec11[0] * fRec120[1]);
		double fTemp58 = ((signbit(fTemp57)) ? input12au7_negclip(fTemp57) : input12au7clip(fTemp57));
		fVec21[0] = fTemp58;
		fRec126[0] = 0.0 - (fSlow6 * fRec126[1] - (fRec125[1] + fRec125[2])) / fSlow5;
		double fTemp59 = fConst60 * fRec129[1];
		fRec136[0] = 0.0 - (fSlow6 * fRec136[1] - (fTemp58 + fVec21[1])) / fSlow5;
		fRec135[0] = fRec136[0] - 0.3 * fRec135[1];
		fRec134[0] = 2.0 / (std::exp(0.0 - 5.0 * fRec135[0]) + 1.0) + 0.3 * fRec134[1] + -1.0;
		fRec133[0] = 0.0 - fConst74 * (fConst73 * fRec133[1] - (fRec134[0] + fRec134[1]));
		fRec132[0] = fRec133[0] - fConst72 * (fConst71 * fRec132[2] + fConst55 * fRec132[1]);
		double fTemp60 = fRec132[2] + fRec132[0] + 2.0 * fRec132[1];
		fVec22[0] = fTemp60;
		fRec131[0] = fConst72 * (fConst75 * fTemp60 + fConst76 * fVec22[1]) - fConst70 * fRec131[1];
		fRec130[0] = fConst76 * fRec131[1] - fConst77 * (fConst69 * fRec130[1] - fConst67 * fRec131[0]);
		fRec129[0] = fRec130[0] - fConst65 * (fConst64 * fRec129[2] + fTemp59);
		double fTemp61 = fTemp59 + fConst80 * fRec129[0] + fConst79 * fRec129[2];
		fVec23[0] = fTemp61;
		fRec128[0] = 0.0 - fConst84 * (fConst83 * fRec128[1] - fConst65 * (fTemp61 + fVec23[1]));
		fRec127[0] = fRec128[0] - fConst58 * (fConst57 * fRec127[2] + fConst55 * fRec127[1]);
		fRec138[0] = 0.0 - fConst91 * (fConst90 * fRec138[1] - (fRec130[0] + fRec130[1]));
		fRec137[0] = fRec138[0] - fConst87 * (fConst86 * fRec137[2] + fConst85 * fRec137[1]);
		fRec142[0] = 0.0 - fConst98 * (fConst97 * fRec142[1] - (fRec141[1] + fRec141[2]));
		double fTemp62 = fConst100 * fRec143[1];
		fRec144[0] = fConst111 * fRec131[1] - fConst110 * (fConst108 * fRec144[1] - fConst107 * fRec131[0]);
		fRec143[0] = fRec144[0] - fConst105 * (fConst104 * fRec143[2] + fTemp62);
		fRec141[0] = fConst105 * (fTemp62 + fConst114 * fRec143[0] + fConst113 * fRec143[2]) - fRec142[0];
		fRec140[0] = fRec141[0] - fConst95 * (fConst94 * fRec140[2] + fConst55 * fRec140[1]);
		fRec139[0] = fConst95 * (fRec140[2] + fRec140[0] + 2.0 * fRec140[1]) - fConst93 * (fConst92 * fRec139[2] + fConst55 * fRec139[1]);
		fRec148[0] = 0.0 - fConst98 * (fConst97 * fRec148[1] - (fRec147[1] + fRec147[2]));
		double fTemp63 = fConst100 * fRec149[1];
		fRec149[0] = fRec130[0] - fConst105 * (fConst104 * fRec149[2] + fTemp63);
		fRec147[0] = fConst105 * (fTemp63 + fConst114 * fRec149[0] + fConst113 * fRec149[2]) - fRec148[0];
		fRec146[0] = fRec147[0] - fConst119 * (fConst118 * fRec146[2] + fConst115 * fRec146[1]);
		fRec145[0] = fConst119 * (fRec146[2] + fRec146[0] + 2.0 * fRec146[1]) - fConst117 * (fConst116 * fRec145[2] + fConst115 * fRec145[1]);
		double fTemp64 = fTemp13 + ((iSlow7) ? ((iSlow3) ? fConst117 * (fRec145[2] + fRec145[0] + 2.0 * fRec145[1]) : fConst93 * (fRec139[2] + fRec139[0] + 2.0 * fRec139[1])) : ((iSlow3) ? fConst87 * (fRec137[2] + fRec137[0] + 2.0 * fRec137[1]) : fConst58 * (fRec127[2] + fRec127[0] + 2.0 * fRec127[1])));
		fVec24[IOTA0 & 8191] = fTemp64;
		double fTemp65 = fVec24[(IOTA0 - iTemp18) & 8191];
		double fTemp66 = fTemp65 + fRec43[0] * (fVec24[(IOTA0 - iTemp20) & 8191] - fTemp65);
		fVec25[IOTA0 & 8191] = fTemp66;
		double fTemp67 = fVec25[(IOTA0 - iTemp24) & 8191];
		fRec125[0] = fTemp67 + fRec50[0] * (fVec25[(IOTA0 - iTemp26) & 8191] - fTemp67) - fRec126[0];
		fRec119[0] = ((iSlow0) ? fRec125[0] : fTemp58) - fConst8 * fRec119[1];
		double fTemp68 = fConst135 * (fRec119[0] * fTemp28 + fConst0 * fTemp27 * fRec119[1]);
		fRec118[0] = ((signbit(fTemp68)) ? output12au7_negclip(fTemp68) : output12au7clip(fTemp68)) - fConst5 * (fConst4 * fRec118[2] + fConst2 * fRec118[1]);
		double fTemp69 = fConst15 * fRec153[1];
		double fTemp70 = fConst22 * fRec154[1];
		double fTemp71 = fConst29 * fRec155[1];
		fRec157[0] = fConst154 * fVec1[1] - fConst42 * (fConst40 * fRec157[1] - fConst37 * fTemp0);
		fRec156[0] = fRec157[0] - fConst39 * (fConst38 * fRec156[2] + fConst36 * fRec156[1]);
		fRec155[0] = fConst39 * (fConst35 * fRec156[0] + fConst155 * fRec156[1] + fConst35 * fRec156[2]) - fConst153 * (fConst152 * fRec155[2] + fTemp71);
		fRec154[0] = fRec155[2] + fConst153 * (fTemp71 + fConst152 * fRec155[0]) - fConst147 * (fConst146 * fRec154[2] + fTemp70);
		fRec153[0] = fRec154[2] + fConst147 * (fTemp70 + fConst146 * fRec154[0]) - fConst141 * (fConst140 * fRec153[2] + fTemp69);
		fRec152[0] = fRec153[2] + fConst141 * (fTemp69 + fConst140 * fRec153[0]) - fConst11 * fRec152[1];
		double fTemp72 = fConst52 * (fRec152[0] * fTemp4 + 0.000275189947996364 * fRec11[0] * fRec152[1]);
		double fTemp73 = ((signbit(fTemp72)) ? input12au7_negclip(fTemp72) : input12au7clip(fTemp72));
		fVec26[0] = fTemp73;
		fRec159[0] = 0.0 - (fSlow6 * fRec159[1] - (fRec158[1] + fRec158[2])) / fSlow5;
		double fTemp74 = fConst60 * fRec162[1];
		fRec169[0] = 0.0 - (fRec169[1] * fSlow6 - (fTemp73 + fVec26[1])) / fSlow5;
		fRec168[0] = fRec169[0] - 0.3 * fRec168[1];
		fRec167[0] = 2.0 / (std::exp(0.0 - 5.0 * fRec168[0]) + 1.0) + 0.3 * fRec167[1] + -1.0;
		fRec166[0] = 0.0 - fConst74 * (fConst73 * fRec166[1] - (fRec167[0] + fRec167[1]));
		fRec165[0] = fRec166[0] - fConst72 * (fConst71 * fRec165[2] + fConst55 * fRec165[1]);
		double fTemp75 = fRec165[2] + fRec165[0] + 2.0 * fRec165[1];
		fVec27[0] = fTemp75;
		fRec164[0] = fConst72 * (fConst75 * fTemp75 + fConst76 * fVec27[1]) - fConst70 * fRec164[1];
		fRec163[0] = fConst76 * fRec164[1] - fConst77 * (fConst69 * fRec163[1] - fConst67 * fRec164[0]);
		fRec162[0] = fRec163[0] - fConst65 * (fConst64 * fRec162[2] + fTemp74);
		double fTemp76 = fTemp74 + fConst80 * fRec162[0] + fConst79 * fRec162[2];
		fVec28[0] = fTemp76;
		fRec161[0] = 0.0 - fConst84 * (fConst83 * fRec161[1] - fConst65 * (fTemp76 + fVec28[1]));
		fRec160[0] = fRec161[0] - fConst58 * (fConst57 * fRec160[2] + fConst55 * fRec160[1]);
		fRec171[0] = 0.0 - fConst91 * (fConst90 * fRec171[1] - (fRec163[0] + fRec163[1]));
		fRec170[0] = fRec171[0] - fConst87 * (fConst86 * fRec170[2] + fConst85 * fRec170[1]);
		fRec175[0] = 0.0 - fConst98 * (fConst97 * fRec175[1] - (fRec174[1] + fRec174[2]));
		double fTemp77 = fConst100 * fRec176[1];
		fRec177[0] = fConst111 * fRec164[1] - fConst110 * (fConst108 * fRec177[1] - fConst107 * fRec164[0]);
		fRec176[0] = fRec177[0] - fConst105 * (fConst104 * fRec176[2] + fTemp77);
		fRec174[0] = fConst105 * (fTemp77 + fConst114 * fRec176[0] + fConst113 * fRec176[2]) - fRec175[0];
		fRec173[0] = fRec174[0] - fConst95 * (fConst94 * fRec173[2] + fConst55 * fRec173[1]);
		fRec172[0] = fConst95 * (fRec173[2] + fRec173[0] + 2.0 * fRec173[1]) - fConst93 * (fConst92 * fRec172[2] + fConst55 * fRec172[1]);
		fRec181[0] = 0.0 - fConst98 * (fConst97 * fRec181[1] - (fRec180[1] + fRec180[2]));
		double fTemp78 = fConst100 * fRec182[1];
		fRec182[0] = fRec163[0] - fConst105 * (fConst104 * fRec182[2] + fTemp78);
		fRec180[0] = fConst105 * (fTemp78 + fConst114 * fRec182[0] + fConst113 * fRec182[2]) - fRec181[0];
		fRec179[0] = fRec180[0] - fConst119 * (fConst118 * fRec179[2] + fConst115 * fRec179[1]);
		fRec178[0] = fConst119 * (fRec179[2] + fRec179[0] + 2.0 * fRec179[1]) - fConst117 * (fConst116 * fRec178[2] + fConst115 * fRec178[1]);
		double fTemp79 = ((iSlow7) ? ((iSlow3) ? fConst117 * (fRec178[2] + fRec178[0] + 2.0 * fRec178[1]) : fConst93 * (fRec172[2] + fRec172[0] + 2.0 * fRec172[1])) : ((iSlow3) ? fConst87 * (fRec170[2] + fRec170[0] + 2.0 * fRec170[1]) : fConst58 * (fRec160[2] + fRec160[0] + 2.0 * fRec160[1]))) + fTemp13;
		fVec29[IOTA0 & 8191] = fTemp79;
		double fTemp80 = fVec29[(IOTA0 - iTemp18) & 8191];
		double fTemp81 = fTemp80 + fRec43[0] * (fVec29[(IOTA0 - iTemp20) & 8191] - fTemp80);
		fVec30[IOTA0 & 8191] = fTemp81;
		double fTemp82 = fVec30[(IOTA0 - iTemp24) & 8191];
		fRec158[0] = fTemp82 + fRec50[0] * (fVec30[(IOTA0 - iTemp26) & 8191] - fTemp82) - fRec159[0];
		fRec151[0] = ((iSlow0) ? fRec158[0] : fTemp73) - fConst8 * fRec151[1];
		double fTemp83 = fConst135 * (fRec151[0] * fTemp28 + fConst0 * fRec151[1] * fTemp27);
		fRec150[0] = ((signbit(fTemp83)) ? output12au7_negclip(fTemp83) : output12au7clip(fTemp83)) - fConst5 * (fConst4 * fRec150[2] + fConst2 * fRec150[1]);
		output0[i0] = FAUSTFLOAT(fConst5 * (fRec150[2] + fRec150[0] + 2.0 * fRec150[1] + fRec118[2] + fRec118[0] + 2.0 * fRec118[1] + fRec87[2] + fRec87[0] + 2.0 * fRec87[1] + fRec57[2] + fRec57[0] + 2.0 * fRec57[1] + fRec0[2] + fRec0[0] + 2.0 * fRec0[1]));
		iVec0[1] = iVec0[0];
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
		fVec4[1] = fVec4[0];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec11[1] = fRec11[0];
		fVec5[1] = fVec5[0];
		fRec13[1] = fRec13[0];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fVec6[1] = fVec6[0];
		fRec18[1] = fRec18[0];
		fRec17[1] = fRec17[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fVec7[1] = fVec7[0];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fRec29[1] = fRec29[0];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fRec35[1] = fRec35[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		iRec39[1] = iRec39[0];
		fRec40[1] = fRec40[0];
		fVec8[1] = fVec8[0];
		fRec38[1] = fRec38[0];
		fRec41[1] = fRec41[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		IOTA0 = IOTA0 + 1;
		fRec48[1] = fRec48[0];
		fRec47[1] = fRec47[0];
		fRec46[1] = fRec46[0];
		fRec42[1] = fRec42[0];
		fRec43[1] = fRec43[0];
		fRec44[1] = fRec44[0];
		fRec45[1] = fRec45[0];
		fRec55[1] = fRec55[0];
		fRec54[1] = fRec54[0];
		fRec53[1] = fRec53[0];
		fRec49[1] = fRec49[0];
		fRec50[1] = fRec50[0];
		fRec51[1] = fRec51[0];
		fRec52[1] = fRec52[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fRec1[1] = fRec1[0];
		fRec56[1] = fRec56[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		fRec61[1] = fRec61[0];
		fRec60[2] = fRec60[1];
		fRec60[1] = fRec60[0];
		fRec59[1] = fRec59[0];
		fVec11[1] = fVec11[0];
		fRec63[1] = fRec63[0];
		fRec73[1] = fRec73[0];
		fRec72[1] = fRec72[0];
		fRec71[1] = fRec71[0];
		fRec70[1] = fRec70[0];
		fRec69[2] = fRec69[1];
		fRec69[1] = fRec69[0];
		fVec12[1] = fVec12[0];
		fRec68[1] = fRec68[0];
		fRec67[1] = fRec67[0];
		fRec66[2] = fRec66[1];
		fRec66[1] = fRec66[0];
		fVec13[1] = fVec13[0];
		fRec65[1] = fRec65[0];
		fRec64[2] = fRec64[1];
		fRec64[1] = fRec64[0];
		fRec75[1] = fRec75[0];
		fRec74[2] = fRec74[1];
		fRec74[1] = fRec74[0];
		fRec79[1] = fRec79[0];
		fRec81[1] = fRec81[0];
		fRec80[2] = fRec80[1];
		fRec80[1] = fRec80[0];
		fRec78[2] = fRec78[1];
		fRec78[1] = fRec78[0];
		fRec77[2] = fRec77[1];
		fRec77[1] = fRec77[0];
		fRec76[2] = fRec76[1];
		fRec76[1] = fRec76[0];
		fRec85[1] = fRec85[0];
		fRec86[2] = fRec86[1];
		fRec86[1] = fRec86[0];
		fRec84[2] = fRec84[1];
		fRec84[1] = fRec84[0];
		fRec83[2] = fRec83[1];
		fRec83[1] = fRec83[0];
		fRec82[2] = fRec82[1];
		fRec82[1] = fRec82[0];
		fRec62[2] = fRec62[1];
		fRec62[1] = fRec62[0];
		fRec58[1] = fRec58[0];
		fRec57[2] = fRec57[1];
		fRec57[1] = fRec57[0];
		fRec92[1] = fRec92[0];
		fRec91[2] = fRec91[1];
		fRec91[1] = fRec91[0];
		fRec90[2] = fRec90[1];
		fRec90[1] = fRec90[0];
		fRec89[1] = fRec89[0];
		fVec16[1] = fVec16[0];
		fRec94[1] = fRec94[0];
		fRec104[1] = fRec104[0];
		fRec103[1] = fRec103[0];
		fRec102[1] = fRec102[0];
		fRec101[1] = fRec101[0];
		fRec100[2] = fRec100[1];
		fRec100[1] = fRec100[0];
		fVec17[1] = fVec17[0];
		fRec99[1] = fRec99[0];
		fRec98[1] = fRec98[0];
		fRec97[2] = fRec97[1];
		fRec97[1] = fRec97[0];
		fVec18[1] = fVec18[0];
		fRec96[1] = fRec96[0];
		fRec95[2] = fRec95[1];
		fRec95[1] = fRec95[0];
		fRec106[1] = fRec106[0];
		fRec105[2] = fRec105[1];
		fRec105[1] = fRec105[0];
		fRec110[1] = fRec110[0];
		fRec112[1] = fRec112[0];
		fRec111[2] = fRec111[1];
		fRec111[1] = fRec111[0];
		fRec109[2] = fRec109[1];
		fRec109[1] = fRec109[0];
		fRec108[2] = fRec108[1];
		fRec108[1] = fRec108[0];
		fRec107[2] = fRec107[1];
		fRec107[1] = fRec107[0];
		fRec116[1] = fRec116[0];
		fRec117[2] = fRec117[1];
		fRec117[1] = fRec117[0];
		fRec115[2] = fRec115[1];
		fRec115[1] = fRec115[0];
		fRec114[2] = fRec114[1];
		fRec114[1] = fRec114[0];
		fRec113[2] = fRec113[1];
		fRec113[1] = fRec113[0];
		fRec93[2] = fRec93[1];
		fRec93[1] = fRec93[0];
		fRec88[1] = fRec88[0];
		fRec87[2] = fRec87[1];
		fRec87[1] = fRec87[0];
		fRec124[1] = fRec124[0];
		fRec123[2] = fRec123[1];
		fRec123[1] = fRec123[0];
		fRec122[2] = fRec122[1];
		fRec122[1] = fRec122[0];
		fRec121[2] = fRec121[1];
		fRec121[1] = fRec121[0];
		fRec120[1] = fRec120[0];
		fVec21[1] = fVec21[0];
		fRec126[1] = fRec126[0];
		fRec136[1] = fRec136[0];
		fRec135[1] = fRec135[0];
		fRec134[1] = fRec134[0];
		fRec133[1] = fRec133[0];
		fRec132[2] = fRec132[1];
		fRec132[1] = fRec132[0];
		fVec22[1] = fVec22[0];
		fRec131[1] = fRec131[0];
		fRec130[1] = fRec130[0];
		fRec129[2] = fRec129[1];
		fRec129[1] = fRec129[0];
		fVec23[1] = fVec23[0];
		fRec128[1] = fRec128[0];
		fRec127[2] = fRec127[1];
		fRec127[1] = fRec127[0];
		fRec138[1] = fRec138[0];
		fRec137[2] = fRec137[1];
		fRec137[1] = fRec137[0];
		fRec142[1] = fRec142[0];
		fRec144[1] = fRec144[0];
		fRec143[2] = fRec143[1];
		fRec143[1] = fRec143[0];
		fRec141[2] = fRec141[1];
		fRec141[1] = fRec141[0];
		fRec140[2] = fRec140[1];
		fRec140[1] = fRec140[0];
		fRec139[2] = fRec139[1];
		fRec139[1] = fRec139[0];
		fRec148[1] = fRec148[0];
		fRec149[2] = fRec149[1];
		fRec149[1] = fRec149[0];
		fRec147[2] = fRec147[1];
		fRec147[1] = fRec147[0];
		fRec146[2] = fRec146[1];
		fRec146[1] = fRec146[0];
		fRec145[2] = fRec145[1];
		fRec145[1] = fRec145[0];
		fRec125[2] = fRec125[1];
		fRec125[1] = fRec125[0];
		fRec119[1] = fRec119[0];
		fRec118[2] = fRec118[1];
		fRec118[1] = fRec118[0];
		fRec157[1] = fRec157[0];
		fRec156[2] = fRec156[1];
		fRec156[1] = fRec156[0];
		fRec155[2] = fRec155[1];
		fRec155[1] = fRec155[0];
		fRec154[2] = fRec154[1];
		fRec154[1] = fRec154[0];
		fRec153[2] = fRec153[1];
		fRec153[1] = fRec153[0];
		fRec152[1] = fRec152[0];
		fVec26[1] = fVec26[0];
		fRec159[1] = fRec159[0];
		fRec169[1] = fRec169[0];
		fRec168[1] = fRec168[0];
		fRec167[1] = fRec167[0];
		fRec166[1] = fRec166[0];
		fRec165[2] = fRec165[1];
		fRec165[1] = fRec165[0];
		fVec27[1] = fVec27[0];
		fRec164[1] = fRec164[0];
		fRec163[1] = fRec163[0];
		fRec162[2] = fRec162[1];
		fRec162[1] = fRec162[0];
		fVec28[1] = fVec28[0];
		fRec161[1] = fRec161[0];
		fRec160[2] = fRec160[1];
		fRec160[1] = fRec160[0];
		fRec171[1] = fRec171[0];
		fRec170[2] = fRec170[1];
		fRec170[1] = fRec170[0];
		fRec175[1] = fRec175[0];
		fRec177[1] = fRec177[0];
		fRec176[2] = fRec176[1];
		fRec176[1] = fRec176[0];
		fRec174[2] = fRec174[1];
		fRec174[1] = fRec174[0];
		fRec173[2] = fRec173[1];
		fRec173[1] = fRec173[0];
		fRec172[2] = fRec172[1];
		fRec172[1] = fRec172[0];
		fRec181[1] = fRec181[0];
		fRec182[2] = fRec182[1];
		fRec182[1] = fRec182[0];
		fRec180[2] = fRec180[1];
		fRec180[1] = fRec180[0];
		fRec179[2] = fRec179[1];
		fRec179[1] = fRec179[0];
		fRec178[2] = fRec178[1];
		fRec178[1] = fRec178[0];
		fRec158[2] = fRec158[1];
		fRec158[1] = fRec158[0];
		fRec151[1] = fRec151[0];
		fRec150[2] = fRec150[1];
		fRec150[1] = fRec150[0];
	}
#undef fCheckbox0
#undef fVslider0
#undef fCheckbox1
#undef fVslider1
#undef fVslider2
#undef fVslider3
#undef fVslider4
#undef fVslider5
#undef fVslider6
#undef fVslider7
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case ON: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case SPEED: 
		fCheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case DRIVE: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case FLUTTERDEPTH: 
		fVslider6_ = (float*)data; // , 0.0, 0.0, 0.03, 0.001 
		break;
	case FLUTTERFREQ: 
		fVslider5_ = (float*)data; // , 4.0, 4.0, 6e+01, 0.1 
		break;
	case GAIN: 
		fVslider7_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case WOWDEPTH: 
		fVslider4_ = (float*)data; // , 0.0, 0.0, 0.03, 0.001 
		break;
	case WOWFREQ: 
		fVslider3_ = (float*)data; // , 0.0, 0.0, 4.0, 0.1 
		break;
	case TAPEHISS: 
		fVslider2_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case TAPETYPE: 
		fVslider1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
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
   DRIVE, 
   FLUTTERDEPTH, 
   FLUTTERFREQ, 
   GAIN, 
   ON, 
   WOWDEPTH, 
   WOWFREQ, 
   SPEED, 
   TAPEHISS, 
   TAPETYPE, 
} PortIndex;
*/

} // end namespace gxtape
