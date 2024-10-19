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
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
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
	double fVec1[2];
	double fConst42;
	double fConst43;
	double fRec8[2];
	double fRec7[3];
	double fVec2[2];
	double fConst44;
	double fConst45;
	double fConst46;
	double fConst47;
	double fRec6[2];
	double fRec5[3];
	double fConst48;
	double fRec4[3];
	double fRec3[3];
	double fRec2[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec9[2];
	double fConst49;
	double fVec3[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	double fConst50;
	double fRec11[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
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
	double fRec21[2];
	double fRec20[2];
	double fRec19[2];
	double fConst66;
	double fConst67;
	double fRec18[2];
	double fRec17[3];
	double fVec4[2];
	double fConst68;
	double fConst69;
	double fConst70;
	double fConst71;
	double fConst72;
	double fRec16[2];
	double fRec15[2];
	double fRec14[3];
	double fConst73;
	double fConst74;
	double fConst75;
	double fVec5[2];
	double fConst76;
	double fConst77;
	double fConst78;
	double fConst79;
	double fRec13[2];
	double fRec12[3];
	double fConst80;
	double fConst81;
	double fConst82;
	double fConst83;
	double fConst84;
	double fConst85;
	double fConst86;
	double fRec23[2];
	double fRec22[3];
	double fConst87;
	double fConst88;
	double fConst89;
	double fConst90;
	double fConst91;
	double fConst92;
	double fConst93;
	double fRec27[2];
	double fConst94;
	double fConst95;
	double fConst96;
	double fConst97;
	double fConst98;
	double fConst99;
	double fConst100;
	double fConst101;
	double fConst102;
	double fConst103;
	double fRec29[2];
	double fRec28[3];
	double fConst104;
	double fConst105;
	double fConst106;
	double fRec26[3];
	double fRec25[3];
	double fRec24[3];
	double fConst107;
	double fConst108;
	double fConst109;
	double fConst110;
	double fConst111;
	double fRec33[2];
	double fRec34[3];
	double fRec32[3];
	double fRec31[3];
	double fRec30[3];
	double fConst112;
	double fConst113;
	double fConst114;
	double fConst115;
	int iRec37[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec38[2];
	double fVec6[2];
	double fConst116;
	double fConst117;
	double fRec36[2];
	double fConst118;
	double fConst119;
	double fConst120;
	double fRec39[2];
	double fRec35[3];
	int IOTA0;
	double *fVec7;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fConst121;
	double fRec46[2];
	double fRec45[2];
	double fRec44[2];
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	double fConst122;
	double fConst123;
	double fRec40[2];
	double fRec41[2];
	double fRec42[2];
	double fRec43[2];
	double *fVec8;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT	*fVslider5_;
	double fRec53[2];
	double fRec52[2];
	double fRec51[2];
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT	*fVslider6_;
	double fRec47[2];
	double fRec48[2];
	double fRec49[2];
	double fRec50[2];
	double fRec10[3];
	double fRec1[2];
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT	*fVslider7_;
	double fRec54[2];
	double fConst124;
	double fRec0[3];
	double fConst125;
	double fConst126;
	double fRec62[2];
	double fRec61[3];
	double fConst127;
	double fRec60[3];
	double fRec59[3];
	double fRec58[3];
	double fRec57[2];
	double fVec9[2];
	double fRec64[2];
	double fRec74[2];
	double fRec73[2];
	double fRec72[2];
	double fRec71[2];
	double fRec70[3];
	double fVec10[2];
	double fRec69[2];
	double fRec68[2];
	double fRec67[3];
	double fVec11[2];
	double fRec66[2];
	double fRec65[3];
	double fRec76[2];
	double fRec75[3];
	double fRec80[2];
	double fRec82[2];
	double fRec81[3];
	double fRec79[3];
	double fRec78[3];
	double fRec77[3];
	double fRec86[2];
	double fRec87[3];
	double fRec85[3];
	double fRec84[3];
	double fRec83[3];
	double *fVec12;
	double *fVec13;
	double fRec63[3];
	double fRec56[2];
	double fRec55[3];
	double fConst128;
	double fConst129;
	double fConst130;
	double fRec95[2];
	double fRec94[3];
	double fVec14[2];
	double fConst131;
	double fConst132;
	double fRec93[2];
	double fRec92[3];
	double fConst133;
	double fRec91[3];
	double fRec90[2];
	double fVec15[2];
	double fRec97[2];
	double fRec107[2];
	double fRec106[2];
	double fRec105[2];
	double fRec104[2];
	double fRec103[3];
	double fVec16[2];
	double fRec102[2];
	double fRec101[2];
	double fRec100[3];
	double fVec17[2];
	double fRec99[2];
	double fRec98[3];
	double fRec109[2];
	double fRec108[3];
	double fRec113[2];
	double fRec115[2];
	double fRec114[3];
	double fRec112[3];
	double fRec111[3];
	double fRec110[3];
	double fRec119[2];
	double fRec120[3];
	double fRec118[3];
	double fRec117[3];
	double fRec116[3];
	double *fVec18;
	double *fVec19;
	double fRec96[3];
	double fRec89[2];
	double fRec88[3];
	double fConst134;
	double fConst135;
	double fConst136;
	double fRec127[2];
	double fRec126[3];
	double fVec20[2];
	double fConst137;
	double fConst138;
	double fRec125[2];
	double fRec124[3];
	double fConst139;
	double fRec123[2];
	double fVec21[2];
	double fRec129[2];
	double fRec139[2];
	double fRec138[2];
	double fRec137[2];
	double fRec136[2];
	double fRec135[3];
	double fVec22[2];
	double fRec134[2];
	double fRec133[2];
	double fRec132[3];
	double fVec23[2];
	double fRec131[2];
	double fRec130[3];
	double fRec141[2];
	double fRec140[3];
	double fRec145[2];
	double fRec147[2];
	double fRec146[3];
	double fRec144[3];
	double fRec143[3];
	double fRec142[3];
	double fRec151[2];
	double fRec152[3];
	double fRec150[3];
	double fRec149[3];
	double fRec148[3];
	double *fVec24;
	double *fVec25;
	double fRec128[3];
	double fRec122[2];
	double fRec121[3];
	double fRec157[2];
	double fRec156[3];
	double fRec155[2];
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
	double fRec154[2];
	double fRec153[3];

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
	  fVec7(0),
	  fVec8(0),
	  fVec12(0),
	  fVec13(0),
	  fVec18(0),
	  fVec19(0),
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
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec8[l2] = 0.0;
	for (int l3 = 0; l3 < 3; l3 = l3 + 1) fRec7[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fVec2[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec6[l5] = 0.0;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec5[l6] = 0.0;
	for (int l7 = 0; l7 < 3; l7 = l7 + 1) fRec4[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec3[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec2[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec9[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fVec3[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec11[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec21[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec20[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec19[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec18[l16] = 0.0;
	for (int l17 = 0; l17 < 3; l17 = l17 + 1) fRec17[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fVec4[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec16[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec15[l20] = 0.0;
	for (int l21 = 0; l21 < 3; l21 = l21 + 1) fRec14[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fVec5[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec13[l23] = 0.0;
	for (int l24 = 0; l24 < 3; l24 = l24 + 1) fRec12[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec23[l25] = 0.0;
	for (int l26 = 0; l26 < 3; l26 = l26 + 1) fRec22[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec27[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec29[l28] = 0.0;
	for (int l29 = 0; l29 < 3; l29 = l29 + 1) fRec28[l29] = 0.0;
	for (int l30 = 0; l30 < 3; l30 = l30 + 1) fRec26[l30] = 0.0;
	for (int l31 = 0; l31 < 3; l31 = l31 + 1) fRec25[l31] = 0.0;
	for (int l32 = 0; l32 < 3; l32 = l32 + 1) fRec24[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fRec33[l33] = 0.0;
	for (int l34 = 0; l34 < 3; l34 = l34 + 1) fRec34[l34] = 0.0;
	for (int l35 = 0; l35 < 3; l35 = l35 + 1) fRec32[l35] = 0.0;
	for (int l36 = 0; l36 < 3; l36 = l36 + 1) fRec31[l36] = 0.0;
	for (int l37 = 0; l37 < 3; l37 = l37 + 1) fRec30[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) iRec37[l38] = 0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec38[l39] = 0.0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fVec6[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec36[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) fRec39[l42] = 0.0;
	for (int l43 = 0; l43 < 3; l43 = l43 + 1) fRec35[l43] = 0.0;
	for (int l44 = 0; l44 < 8192; l44 = l44 + 1) fVec7[l44] = 0.0;
	for (int l45 = 0; l45 < 2; l45 = l45 + 1) fRec46[l45] = 0.0;
	for (int l46 = 0; l46 < 2; l46 = l46 + 1) fRec45[l46] = 0.0;
	for (int l47 = 0; l47 < 2; l47 = l47 + 1) fRec44[l47] = 0.0;
	for (int l48 = 0; l48 < 2; l48 = l48 + 1) fRec40[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec41[l49] = 0.0;
	for (int l50 = 0; l50 < 2; l50 = l50 + 1) fRec42[l50] = 0.0;
	for (int l51 = 0; l51 < 2; l51 = l51 + 1) fRec43[l51] = 0.0;
	for (int l52 = 0; l52 < 8192; l52 = l52 + 1) fVec8[l52] = 0.0;
	for (int l53 = 0; l53 < 2; l53 = l53 + 1) fRec53[l53] = 0.0;
	for (int l54 = 0; l54 < 2; l54 = l54 + 1) fRec52[l54] = 0.0;
	for (int l55 = 0; l55 < 2; l55 = l55 + 1) fRec51[l55] = 0.0;
	for (int l56 = 0; l56 < 2; l56 = l56 + 1) fRec47[l56] = 0.0;
	for (int l57 = 0; l57 < 2; l57 = l57 + 1) fRec48[l57] = 0.0;
	for (int l58 = 0; l58 < 2; l58 = l58 + 1) fRec49[l58] = 0.0;
	for (int l59 = 0; l59 < 2; l59 = l59 + 1) fRec50[l59] = 0.0;
	for (int l60 = 0; l60 < 3; l60 = l60 + 1) fRec10[l60] = 0.0;
	for (int l61 = 0; l61 < 2; l61 = l61 + 1) fRec1[l61] = 0.0;
	for (int l62 = 0; l62 < 2; l62 = l62 + 1) fRec54[l62] = 0.0;
	for (int l63 = 0; l63 < 3; l63 = l63 + 1) fRec0[l63] = 0.0;
	for (int l64 = 0; l64 < 2; l64 = l64 + 1) fRec62[l64] = 0.0;
	for (int l65 = 0; l65 < 3; l65 = l65 + 1) fRec61[l65] = 0.0;
	for (int l66 = 0; l66 < 3; l66 = l66 + 1) fRec60[l66] = 0.0;
	for (int l67 = 0; l67 < 3; l67 = l67 + 1) fRec59[l67] = 0.0;
	for (int l68 = 0; l68 < 3; l68 = l68 + 1) fRec58[l68] = 0.0;
	for (int l69 = 0; l69 < 2; l69 = l69 + 1) fRec57[l69] = 0.0;
	for (int l70 = 0; l70 < 2; l70 = l70 + 1) fVec9[l70] = 0.0;
	for (int l71 = 0; l71 < 2; l71 = l71 + 1) fRec64[l71] = 0.0;
	for (int l72 = 0; l72 < 2; l72 = l72 + 1) fRec74[l72] = 0.0;
	for (int l73 = 0; l73 < 2; l73 = l73 + 1) fRec73[l73] = 0.0;
	for (int l74 = 0; l74 < 2; l74 = l74 + 1) fRec72[l74] = 0.0;
	for (int l75 = 0; l75 < 2; l75 = l75 + 1) fRec71[l75] = 0.0;
	for (int l76 = 0; l76 < 3; l76 = l76 + 1) fRec70[l76] = 0.0;
	for (int l77 = 0; l77 < 2; l77 = l77 + 1) fVec10[l77] = 0.0;
	for (int l78 = 0; l78 < 2; l78 = l78 + 1) fRec69[l78] = 0.0;
	for (int l79 = 0; l79 < 2; l79 = l79 + 1) fRec68[l79] = 0.0;
	for (int l80 = 0; l80 < 3; l80 = l80 + 1) fRec67[l80] = 0.0;
	for (int l81 = 0; l81 < 2; l81 = l81 + 1) fVec11[l81] = 0.0;
	for (int l82 = 0; l82 < 2; l82 = l82 + 1) fRec66[l82] = 0.0;
	for (int l83 = 0; l83 < 3; l83 = l83 + 1) fRec65[l83] = 0.0;
	for (int l84 = 0; l84 < 2; l84 = l84 + 1) fRec76[l84] = 0.0;
	for (int l85 = 0; l85 < 3; l85 = l85 + 1) fRec75[l85] = 0.0;
	for (int l86 = 0; l86 < 2; l86 = l86 + 1) fRec80[l86] = 0.0;
	for (int l87 = 0; l87 < 2; l87 = l87 + 1) fRec82[l87] = 0.0;
	for (int l88 = 0; l88 < 3; l88 = l88 + 1) fRec81[l88] = 0.0;
	for (int l89 = 0; l89 < 3; l89 = l89 + 1) fRec79[l89] = 0.0;
	for (int l90 = 0; l90 < 3; l90 = l90 + 1) fRec78[l90] = 0.0;
	for (int l91 = 0; l91 < 3; l91 = l91 + 1) fRec77[l91] = 0.0;
	for (int l92 = 0; l92 < 2; l92 = l92 + 1) fRec86[l92] = 0.0;
	for (int l93 = 0; l93 < 3; l93 = l93 + 1) fRec87[l93] = 0.0;
	for (int l94 = 0; l94 < 3; l94 = l94 + 1) fRec85[l94] = 0.0;
	for (int l95 = 0; l95 < 3; l95 = l95 + 1) fRec84[l95] = 0.0;
	for (int l96 = 0; l96 < 3; l96 = l96 + 1) fRec83[l96] = 0.0;
	for (int l97 = 0; l97 < 8192; l97 = l97 + 1) fVec12[l97] = 0.0;
	for (int l98 = 0; l98 < 8192; l98 = l98 + 1) fVec13[l98] = 0.0;
	for (int l99 = 0; l99 < 3; l99 = l99 + 1) fRec63[l99] = 0.0;
	for (int l100 = 0; l100 < 2; l100 = l100 + 1) fRec56[l100] = 0.0;
	for (int l101 = 0; l101 < 3; l101 = l101 + 1) fRec55[l101] = 0.0;
	for (int l102 = 0; l102 < 2; l102 = l102 + 1) fRec95[l102] = 0.0;
	for (int l103 = 0; l103 < 3; l103 = l103 + 1) fRec94[l103] = 0.0;
	for (int l104 = 0; l104 < 2; l104 = l104 + 1) fVec14[l104] = 0.0;
	for (int l105 = 0; l105 < 2; l105 = l105 + 1) fRec93[l105] = 0.0;
	for (int l106 = 0; l106 < 3; l106 = l106 + 1) fRec92[l106] = 0.0;
	for (int l107 = 0; l107 < 3; l107 = l107 + 1) fRec91[l107] = 0.0;
	for (int l108 = 0; l108 < 2; l108 = l108 + 1) fRec90[l108] = 0.0;
	for (int l109 = 0; l109 < 2; l109 = l109 + 1) fVec15[l109] = 0.0;
	for (int l110 = 0; l110 < 2; l110 = l110 + 1) fRec97[l110] = 0.0;
	for (int l111 = 0; l111 < 2; l111 = l111 + 1) fRec107[l111] = 0.0;
	for (int l112 = 0; l112 < 2; l112 = l112 + 1) fRec106[l112] = 0.0;
	for (int l113 = 0; l113 < 2; l113 = l113 + 1) fRec105[l113] = 0.0;
	for (int l114 = 0; l114 < 2; l114 = l114 + 1) fRec104[l114] = 0.0;
	for (int l115 = 0; l115 < 3; l115 = l115 + 1) fRec103[l115] = 0.0;
	for (int l116 = 0; l116 < 2; l116 = l116 + 1) fVec16[l116] = 0.0;
	for (int l117 = 0; l117 < 2; l117 = l117 + 1) fRec102[l117] = 0.0;
	for (int l118 = 0; l118 < 2; l118 = l118 + 1) fRec101[l118] = 0.0;
	for (int l119 = 0; l119 < 3; l119 = l119 + 1) fRec100[l119] = 0.0;
	for (int l120 = 0; l120 < 2; l120 = l120 + 1) fVec17[l120] = 0.0;
	for (int l121 = 0; l121 < 2; l121 = l121 + 1) fRec99[l121] = 0.0;
	for (int l122 = 0; l122 < 3; l122 = l122 + 1) fRec98[l122] = 0.0;
	for (int l123 = 0; l123 < 2; l123 = l123 + 1) fRec109[l123] = 0.0;
	for (int l124 = 0; l124 < 3; l124 = l124 + 1) fRec108[l124] = 0.0;
	for (int l125 = 0; l125 < 2; l125 = l125 + 1) fRec113[l125] = 0.0;
	for (int l126 = 0; l126 < 2; l126 = l126 + 1) fRec115[l126] = 0.0;
	for (int l127 = 0; l127 < 3; l127 = l127 + 1) fRec114[l127] = 0.0;
	for (int l128 = 0; l128 < 3; l128 = l128 + 1) fRec112[l128] = 0.0;
	for (int l129 = 0; l129 < 3; l129 = l129 + 1) fRec111[l129] = 0.0;
	for (int l130 = 0; l130 < 3; l130 = l130 + 1) fRec110[l130] = 0.0;
	for (int l131 = 0; l131 < 2; l131 = l131 + 1) fRec119[l131] = 0.0;
	for (int l132 = 0; l132 < 3; l132 = l132 + 1) fRec120[l132] = 0.0;
	for (int l133 = 0; l133 < 3; l133 = l133 + 1) fRec118[l133] = 0.0;
	for (int l134 = 0; l134 < 3; l134 = l134 + 1) fRec117[l134] = 0.0;
	for (int l135 = 0; l135 < 3; l135 = l135 + 1) fRec116[l135] = 0.0;
	for (int l136 = 0; l136 < 8192; l136 = l136 + 1) fVec18[l136] = 0.0;
	for (int l137 = 0; l137 < 8192; l137 = l137 + 1) fVec19[l137] = 0.0;
	for (int l138 = 0; l138 < 3; l138 = l138 + 1) fRec96[l138] = 0.0;
	for (int l139 = 0; l139 < 2; l139 = l139 + 1) fRec89[l139] = 0.0;
	for (int l140 = 0; l140 < 3; l140 = l140 + 1) fRec88[l140] = 0.0;
	for (int l141 = 0; l141 < 2; l141 = l141 + 1) fRec127[l141] = 0.0;
	for (int l142 = 0; l142 < 3; l142 = l142 + 1) fRec126[l142] = 0.0;
	for (int l143 = 0; l143 < 2; l143 = l143 + 1) fVec20[l143] = 0.0;
	for (int l144 = 0; l144 < 2; l144 = l144 + 1) fRec125[l144] = 0.0;
	for (int l145 = 0; l145 < 3; l145 = l145 + 1) fRec124[l145] = 0.0;
	for (int l146 = 0; l146 < 2; l146 = l146 + 1) fRec123[l146] = 0.0;
	for (int l147 = 0; l147 < 2; l147 = l147 + 1) fVec21[l147] = 0.0;
	for (int l148 = 0; l148 < 2; l148 = l148 + 1) fRec129[l148] = 0.0;
	for (int l149 = 0; l149 < 2; l149 = l149 + 1) fRec139[l149] = 0.0;
	for (int l150 = 0; l150 < 2; l150 = l150 + 1) fRec138[l150] = 0.0;
	for (int l151 = 0; l151 < 2; l151 = l151 + 1) fRec137[l151] = 0.0;
	for (int l152 = 0; l152 < 2; l152 = l152 + 1) fRec136[l152] = 0.0;
	for (int l153 = 0; l153 < 3; l153 = l153 + 1) fRec135[l153] = 0.0;
	for (int l154 = 0; l154 < 2; l154 = l154 + 1) fVec22[l154] = 0.0;
	for (int l155 = 0; l155 < 2; l155 = l155 + 1) fRec134[l155] = 0.0;
	for (int l156 = 0; l156 < 2; l156 = l156 + 1) fRec133[l156] = 0.0;
	for (int l157 = 0; l157 < 3; l157 = l157 + 1) fRec132[l157] = 0.0;
	for (int l158 = 0; l158 < 2; l158 = l158 + 1) fVec23[l158] = 0.0;
	for (int l159 = 0; l159 < 2; l159 = l159 + 1) fRec131[l159] = 0.0;
	for (int l160 = 0; l160 < 3; l160 = l160 + 1) fRec130[l160] = 0.0;
	for (int l161 = 0; l161 < 2; l161 = l161 + 1) fRec141[l161] = 0.0;
	for (int l162 = 0; l162 < 3; l162 = l162 + 1) fRec140[l162] = 0.0;
	for (int l163 = 0; l163 < 2; l163 = l163 + 1) fRec145[l163] = 0.0;
	for (int l164 = 0; l164 < 2; l164 = l164 + 1) fRec147[l164] = 0.0;
	for (int l165 = 0; l165 < 3; l165 = l165 + 1) fRec146[l165] = 0.0;
	for (int l166 = 0; l166 < 3; l166 = l166 + 1) fRec144[l166] = 0.0;
	for (int l167 = 0; l167 < 3; l167 = l167 + 1) fRec143[l167] = 0.0;
	for (int l168 = 0; l168 < 3; l168 = l168 + 1) fRec142[l168] = 0.0;
	for (int l169 = 0; l169 < 2; l169 = l169 + 1) fRec151[l169] = 0.0;
	for (int l170 = 0; l170 < 3; l170 = l170 + 1) fRec152[l170] = 0.0;
	for (int l171 = 0; l171 < 3; l171 = l171 + 1) fRec150[l171] = 0.0;
	for (int l172 = 0; l172 < 3; l172 = l172 + 1) fRec149[l172] = 0.0;
	for (int l173 = 0; l173 < 3; l173 = l173 + 1) fRec148[l173] = 0.0;
	for (int l174 = 0; l174 < 8192; l174 = l174 + 1) fVec24[l174] = 0.0;
	for (int l175 = 0; l175 < 8192; l175 = l175 + 1) fVec25[l175] = 0.0;
	for (int l176 = 0; l176 < 3; l176 = l176 + 1) fRec128[l176] = 0.0;
	for (int l177 = 0; l177 < 2; l177 = l177 + 1) fRec122[l177] = 0.0;
	for (int l178 = 0; l178 < 3; l178 = l178 + 1) fRec121[l178] = 0.0;
	for (int l179 = 0; l179 < 2; l179 = l179 + 1) fRec157[l179] = 0.0;
	for (int l180 = 0; l180 < 3; l180 = l180 + 1) fRec156[l180] = 0.0;
	for (int l181 = 0; l181 < 2; l181 = l181 + 1) fRec155[l181] = 0.0;
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
	for (int l212 = 0; l212 < 2; l212 = l212 + 1) fRec154[l212] = 0.0;
	for (int l213 = 0; l213 < 3; l213 = l213 + 1) fRec153[l213] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = std::tan(62831.853071795864 / fConst0);
	fConst2 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst1));
	fConst3 = 1.0 / fConst1;
	fConst4 = (fConst3 + -1.414213562373095) / fConst1 + 1.0;
	fConst5 = 1.0 / ((fConst3 + 1.414213562373095) / fConst1 + 1.0);
	fConst6 = 2.08237464600982e-05 * fConst0;
	fConst7 = fConst6 + 0.000460169915286817;
	fConst8 = (0.000460169915286817 - fConst6) / fConst7;
	fConst9 = 2.08237184654756e-05 * fConst0;
	fConst10 = fConst9 + 0.000461513657169036;
	fConst11 = (0.000461513657169036 - fConst9) / fConst10;
	fConst12 = std::tan(270.1769682087222 / fConst0);
	fConst13 = mydsp_faustpower2_f(fConst12);
	fConst14 = 2.0 * (1.0 - 1.0 / fConst13);
	fConst15 = 1.0 / fConst12;
	fConst16 = 1.0 - fConst15;
	fConst17 = 1.0 - fConst16 / fConst12;
	fConst18 = fConst15 + 1.0;
	fConst19 = 1.0 / (fConst18 / fConst12 + 1.0);
	fConst20 = std::tan(659.7344572538566 / fConst0);
	fConst21 = mydsp_faustpower2_f(fConst20);
	fConst22 = 2.0 * (1.0 - 1.0 / fConst21);
	fConst23 = 1.0 / fConst20;
	fConst24 = 1.0 - fConst23;
	fConst25 = 1.0 - fConst24 / fConst20;
	fConst26 = fConst23 + 1.0;
	fConst27 = 1.0 / (fConst26 / fConst20 + 1.0);
	fConst28 = std::tan(3769.9111843077517 / fConst0);
	fConst29 = mydsp_faustpower2_f(fConst28);
	fConst30 = 2.0 * (1.0 - 1.0 / fConst29);
	fConst31 = 1.0 / fConst28;
	fConst32 = (fConst31 + -1.0000000000000004) / fConst28 + 1.0;
	fConst33 = (fConst31 + 1.0000000000000004) / fConst28 + 1.0;
	fConst34 = 1.0 / fConst33;
	fConst35 = std::tan(20517.741620594938 / fConst0);
	fConst36 = mydsp_faustpower2_f(fConst35);
	fConst37 = 2.0 * (1.0 - 1.0 / fConst36);
	fConst38 = 1.0 / fConst35;
	fConst39 = (fConst38 + -1.0000000000000004) / fConst35 + 1.0;
	fConst40 = (fConst38 + 1.0000000000000004) / fConst35 + 1.0;
	fConst41 = 1.0 / fConst40;
	fConst42 = 1.0 - fConst38;
	fConst43 = 1.0 / (fConst38 + 1.0);
	fConst44 = 1.0 / (fConst28 * fConst40);
	fConst45 = 1.0 - fConst31;
	fConst46 = fConst31 + 1.0;
	fConst47 = 1.0 / fConst46;
	fConst48 = 1.0 / (fConst29 * fConst33);
	fConst49 = 0.000275189947996364 * (fConst0 / fConst10);
	fConst50 = 3.141592653589793 / fConst0;
	fConst51 = std::tan(47123.8898038469 / fConst0);
	fConst52 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst51));
	fConst53 = 1.0 / fConst51;
	fConst54 = (fConst53 + -1.414213562373095) / fConst51 + 1.0;
	fConst55 = 1.0 / ((fConst53 + 1.414213562373095) / fConst51 + 1.0);
	fConst56 = std::tan(157.07963267948966 / fConst0);
	fConst57 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst56));
	fConst58 = fConst0 * std::sin(314.1592653589793 / fConst0);
	fConst59 = 392.6990816987241 / fConst58;
	fConst60 = 1.0 / fConst56;
	fConst61 = (fConst60 - fConst59) / fConst56 + 1.0;
	fConst62 = 1.0 / ((fConst60 + fConst59) / fConst56 + 1.0);
	fConst63 = (fConst53 + -1.0000000000000004) / fConst51 + 1.0;
	fConst64 = (fConst53 + 1.0000000000000004) / fConst51 + 1.0;
	fConst65 = 1.0 / fConst64;
	fConst66 = 1.0 - fConst53;
	fConst67 = 1.0 / (fConst53 + 1.0);
	fConst68 = std::tan(78.53981633974483 / fConst0);
	fConst69 = 1.0 / (fConst68 * fConst64);
	fConst70 = 1.0 / fConst68;
	fConst71 = 1.0 - fConst70;
	fConst72 = 1.0 / (fConst70 + 1.0);
	fConst73 = 554.7021966383262 / fConst58;
	fConst74 = (fConst60 - fConst73) / fConst56 + 1.0;
	fConst75 = (fConst60 + fConst73) / fConst56 + 1.0;
	fConst76 = std::tan(39269.90816987241 / fConst0);
	fConst77 = 1.0 / fConst76;
	fConst78 = 1.0 - fConst77;
	fConst79 = 1.0 / (fConst77 + 1.0);
	fConst80 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst76));
	fConst81 = (fConst77 + -1.414213562373095) / fConst76 + 1.0;
	fConst82 = 1.0 / ((fConst77 + 1.414213562373095) / fConst76 + 1.0);
	fConst83 = std::tan(31415.926535897932 / fConst0);
	fConst84 = 1.0 / fConst83;
	fConst85 = 1.0 - fConst84;
	fConst86 = 1.0 / (fConst84 + 1.0);
	fConst87 = (fConst53 + -0.7653668647301795) / fConst51 + 1.0;
	fConst88 = 1.0 / ((fConst53 + 0.7653668647301795) / fConst51 + 1.0);
	fConst89 = (fConst53 + -1.8477590650225735) / fConst51 + 1.0;
	fConst90 = 1.0 / ((fConst53 + 1.8477590650225735) / fConst51 + 1.0);
	fConst91 = 1.0 / std::tan(14284.82179587279 / fConst0);
	fConst92 = 1.0 - fConst91;
	fConst93 = 1.0 / (fConst91 + 1.0);
	fConst94 = std::tan(235.61944901923448 / fConst0);
	fConst95 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst94));
	fConst96 = fConst0 * std::sin(471.23889803846896 / fConst0);
	fConst97 = 589.0486225480862 / fConst96;
	fConst98 = 1.0 / fConst94;
	fConst99 = (fConst98 - fConst97) / fConst94 + 1.0;
	fConst100 = 1.0 / ((fConst98 + fConst97) / fConst94 + 1.0);
	fConst101 = 1.0 / std::tan(109.95574287564276 / fConst0);
	fConst102 = 1.0 - fConst101;
	fConst103 = 1.0 / (fConst101 + 1.0);
	fConst104 = 1175.3065182545242 / fConst96;
	fConst105 = (fConst98 - fConst104) / fConst94 + 1.0;
	fConst106 = (fConst98 + fConst104) / fConst94 + 1.0;
	fConst107 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst83));
	fConst108 = (fConst84 + -0.7653668647301795) / fConst83 + 1.0;
	fConst109 = 1.0 / ((fConst84 + 0.7653668647301795) / fConst83 + 1.0);
	fConst110 = (fConst84 + -1.8477590650225735) / fConst83 + 1.0;
	fConst111 = 1.0 / ((fConst84 + 1.8477590650225735) / fConst83 + 1.0);
	fConst112 = 23561.94490192345 / fConst0;
	fConst113 = std::tan(9424.77796076938 / fConst0);
	fConst114 = 1.0 / fConst113;
	fConst115 = 1.0 - fConst114;
	fConst116 = 4.656612875245797e-10 / fConst113;
	fConst117 = 1.0 / (fConst114 + 1.0);
	fConst118 = 1.0 / std::tan(785.3981633974482 / fConst0);
	fConst119 = 1.0 - fConst118;
	fConst120 = 1.0 / (fConst118 + 1.0);
	fConst121 = 6.283185307179586 / fConst0;
	fConst122 = 0.005 * fConst0;
	fConst123 = 1e+01 / fConst0;
	fConst124 = 0.000257077078239627 * (fConst0 / fConst7);
	fConst125 = 1.0 - fConst45 / fConst28;
	fConst126 = 1.0 / (fConst46 / fConst28 + 1.0);
	fConst127 = 1.0 / (fConst36 * fConst40);
	fConst128 = (fConst23 + -1.0000000000000004) / fConst20 + 1.0;
	fConst129 = (fConst23 + 1.0000000000000004) / fConst20 + 1.0;
	fConst130 = 1.0 / fConst129;
	fConst131 = 1.0 / (fConst20 * fConst33);
	fConst132 = 1.0 / fConst26;
	fConst133 = 1.0 / (fConst21 * fConst129);
	fConst134 = (fConst15 + -1.0000000000000004) / fConst12 + 1.0;
	fConst135 = (fConst15 + 1.0000000000000004) / fConst12 + 1.0;
	fConst136 = 1.0 / fConst135;
	fConst137 = 1.0 / (fConst12 * fConst129);
	fConst138 = 1.0 / fConst18;
	fConst139 = 1.0 / (fConst13 * fConst135);
	IOTA0 = 0;
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void Dsp::mem_alloc()
{
	if (!fVec7) fVec7 = new double[8192];
	if (!fVec8) fVec8 = new double[8192];
	if (!fVec12) fVec12 = new double[8192];
	if (!fVec13) fVec13 = new double[8192];
	if (!fVec18) fVec18 = new double[8192];
	if (!fVec19) fVec19 = new double[8192];
	if (!fVec24) fVec24 = new double[8192];
	if (!fVec25) fVec25 = new double[8192];
	if (!fVec29) fVec29 = new double[8192];
	if (!fVec30) fVec30 = new double[8192];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec7) { delete fVec7; fVec7 = 0; }
	if (fVec8) { delete fVec8; fVec8 = 0; }
	if (fVec12) { delete fVec12; fVec12 = 0; }
	if (fVec13) { delete fVec13; fVec13 = 0; }
	if (fVec18) { delete fVec18; fVec18 = 0; }
	if (fVec19) { delete fVec19; fVec19 = 0; }
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
	double fSlow4 = 1.0 / std::tan(fConst50 * double(((iSlow3) ? 2274 : 4547)));
	double fSlow5 = fSlow4 + 1.0;
	double fSlow6 = 1.0 - fSlow4;
	int iSlow7 = int(double(fVslider1));
	double fSlow8 = std::tan(fConst112 * (2.0 - fSlow2));
	double fSlow9 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fSlow8));
	double fSlow10 = 1.0 / fSlow8;
	double fSlow11 = (fSlow10 + -1.414213562373095) / fSlow8 + 1.0;
	double fSlow12 = 1.0 / ((fSlow10 + 1.414213562373095) / fSlow8 + 1.0);
	double fSlow13 = 4.739999999999478e-06 * double(fVslider2);
	double fSlow14 = fConst121 * double(fVslider3);
	double fSlow15 = fConst122 * double(fVslider4);
	double fSlow16 = fConst121 * double(fVslider5);
	double fSlow17 = fConst122 * double(fVslider6);
	double fSlow18 = 0.00036676987543879196 * (std::exp(3.0 * (1.0 - double(fVslider7))) + -1.0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		iVec0[0] = 1;
		double fTemp0 = fConst14 * fRec3[1];
		double fTemp1 = fConst22 * fRec4[1];
		double fTemp2 = double(input0[i0]);
		fVec1[0] = fTemp2;
		fRec8[0] = -(fConst43 * (fConst42 * fRec8[1] - (fTemp2 + fVec1[1])));
		fRec7[0] = fRec8[0] - fConst41 * (fConst39 * fRec7[2] + fConst37 * fRec7[1]);
		double fTemp3 = fRec7[2] + fRec7[0] + 2.0 * fRec7[1];
		fVec2[0] = fTemp3;
		fRec6[0] = -(fConst47 * (fConst45 * fRec6[1] - fConst44 * (fTemp3 - fVec2[1])));
		fRec5[0] = fRec6[0] - fConst34 * (fConst32 * fRec5[2] + fConst30 * fRec5[1]);
		fRec4[0] = fConst48 * (fRec5[2] + (fRec5[0] - 2.0 * fRec5[1])) - fConst27 * (fConst25 * fRec4[2] + fTemp1);
		fRec3[0] = fRec4[2] + fConst27 * (fTemp1 + fConst25 * fRec4[0]) - fConst19 * (fConst17 * fRec3[2] + fTemp0);
		fRec2[0] = fRec3[2] + fConst19 * (fTemp0 + fConst17 * fRec3[0]) - fConst11 * fRec2[1];
		fRec9[0] = fSlow1 + 0.993 * fRec9[1];
		double fTemp4 = fConst49 * fRec9[0] * (fRec2[0] - fRec2[1]);
		double fTemp5 = ((signbit(-fTemp4)) ? input12au7_negclip(-fTemp4) : input12au7clip(-fTemp4));
		fVec3[0] = fTemp5;
		fRec11[0] = -((fSlow6 * fRec11[1] - (fRec10[1] + fRec10[2])) / fSlow5);
		double fTemp6 = fConst57 * fRec14[1];
		fRec21[0] = -((fSlow6 * fRec21[1] - (fTemp5 + fVec3[1])) / fSlow5);
		fRec20[0] = fRec21[0] - 0.3 * fRec20[1];
		fRec19[0] = 2.0 / (std::exp(-(5.0 * fRec20[0])) + 1.0) + 0.3 * fRec19[1] + -1.0;
		fRec18[0] = -(fConst67 * (fConst66 * fRec18[1] - (fRec19[0] + fRec19[1])));
		fRec17[0] = fRec18[0] - fConst65 * (fConst63 * fRec17[2] + fConst52 * fRec17[1]);
		double fTemp7 = fRec17[2] + fRec17[0] + 2.0 * fRec17[1];
		fVec4[0] = fTemp7;
		fRec16[0] = -(fConst72 * (fConst71 * fRec16[1] - fConst69 * (fTemp7 - fVec4[1])));
		double fTemp8 = fRec16[0] - fRec16[1];
		fRec15[0] = -(fConst72 * (fConst71 * fRec15[1] - fConst70 * fTemp8));
		fRec14[0] = fRec15[0] - fConst62 * (fConst61 * fRec14[2] + fTemp6);
		double fTemp9 = fTemp6 + fConst75 * fRec14[0] + fConst74 * fRec14[2];
		fVec5[0] = fTemp9;
		fRec13[0] = -(fConst79 * (fConst78 * fRec13[1] - fConst62 * (fTemp9 + fVec5[1])));
		fRec12[0] = fRec13[0] - fConst55 * (fConst54 * fRec12[2] + fConst52 * fRec12[1]);
		fRec23[0] = -(fConst86 * (fConst85 * fRec23[1] - (fRec15[0] + fRec15[1])));
		fRec22[0] = fRec23[0] - fConst82 * (fConst81 * fRec22[2] + fConst80 * fRec22[1]);
		fRec27[0] = -(fConst93 * (fConst92 * fRec27[1] - (fRec26[1] + fRec26[2])));
		double fTemp10 = fConst95 * fRec28[1];
		fRec29[0] = -(fConst103 * (fConst102 * fRec29[1] - fConst101 * fTemp8));
		fRec28[0] = fRec29[0] - fConst100 * (fConst99 * fRec28[2] + fTemp10);
		fRec26[0] = fConst100 * (fTemp10 + fConst106 * fRec28[0] + fConst105 * fRec28[2]) - fRec27[0];
		fRec25[0] = fRec26[0] - fConst90 * (fConst89 * fRec25[2] + fConst52 * fRec25[1]);
		fRec24[0] = fConst90 * (fRec25[2] + fRec25[0] + 2.0 * fRec25[1]) - fConst88 * (fConst87 * fRec24[2] + fConst52 * fRec24[1]);
		fRec33[0] = -(fConst93 * (fConst92 * fRec33[1] - (fRec32[1] + fRec32[2])));
		double fTemp11 = fConst95 * fRec34[1];
		fRec34[0] = fRec15[0] - fConst100 * (fConst99 * fRec34[2] + fTemp11);
		fRec32[0] = fConst100 * (fTemp11 + fConst106 * fRec34[0] + fConst105 * fRec34[2]) - fRec33[0];
		fRec31[0] = fRec32[0] - fConst111 * (fConst110 * fRec31[2] + fConst107 * fRec31[1]);
		fRec30[0] = fConst111 * (fRec31[2] + fRec31[0] + 2.0 * fRec31[1]) - fConst109 * (fConst108 * fRec30[2] + fConst107 * fRec30[1]);
		iRec37[0] = 1103515245 * iRec37[1] + 12345;
		fRec38[0] = fSlow13 + 0.9999 * fRec38[1];
		double fTemp12 = fRec38[0] * double(iRec37[0]);
		fVec6[0] = fTemp12;
		fRec36[0] = fConst117 * (fConst116 * (fTemp12 - fVec6[1]) - fConst115 * fRec36[1]);
		fRec39[0] = fConst120 * (4.656612875245797e-10 * (fTemp12 + fVec6[1]) - fConst119 * fRec39[1]);
		fRec35[0] = fRec39[0] + 0.2 * fRec36[0] - fSlow12 * (fSlow11 * fRec35[2] + fSlow9 * fRec35[1]);
		double fTemp13 = fSlow12 * (fRec35[2] + fRec35[0] + 2.0 * fRec35[1]);
		double fTemp14 = fTemp13 + ((iSlow7) ? ((iSlow3) ? fConst109 * (fRec30[2] + fRec30[0] + 2.0 * fRec30[1]) : fConst88 * (fRec24[2] + fRec24[0] + 2.0 * fRec24[1])) : ((iSlow3) ? fConst82 * (fRec22[2] + fRec22[0] + 2.0 * fRec22[1]) : fConst55 * (fRec12[2] + fRec12[0] + 2.0 * fRec12[1])));
		fVec7[IOTA0 & 8191] = fTemp14;
		double fTemp15 = double(1 - iVec0[1]);
		fRec46[0] = fRec46[1] - fSlow14 * fRec44[1];
		fRec45[0] = fSlow14 * fRec46[0] + fTemp15 + fRec45[1];
		fRec44[0] = fRec45[0];
		double fTemp16 = fSlow15 * (std::max<double>(0.0, 0.5 * (fRec44[0] + 1.0)) + 1.0);
		double fTemp17 = ((fRec40[1] != 0.0) ? (((fRec41[1] > 0.0) & (fRec41[1] < 1.0)) ? fRec40[1] : 0.0) : (((fRec41[1] == 0.0) & (fTemp16 != fRec42[1])) ? fConst123 : (((fRec41[1] == 1.0) & (fTemp16 != fRec43[1])) ? -fConst123 : 0.0)));
		fRec40[0] = fTemp17;
		fRec41[0] = std::max<double>(0.0, std::min<double>(1.0, fRec41[1] + fTemp17));
		fRec42[0] = (((fRec41[1] >= 1.0) & (fRec43[1] != fTemp16)) ? fTemp16 : fRec42[1]);
		fRec43[0] = (((fRec41[1] <= 0.0) & (fRec42[1] != fTemp16)) ? fTemp16 : fRec43[1]);
		int iTemp18 = int(std::min<double>(4096.0, std::max<double>(0.0, fRec42[0])));
		double fTemp19 = fVec7[(IOTA0 - iTemp18) & 8191];
		int iTemp20 = int(std::min<double>(4096.0, std::max<double>(0.0, fRec43[0])));
		double fTemp21 = fTemp19 + fRec41[0] * (fVec7[(IOTA0 - iTemp20) & 8191] - fTemp19);
		fVec8[IOTA0 & 8191] = fTemp21;
		fRec53[0] = fRec53[1] - fSlow16 * fRec51[1];
		fRec52[0] = fSlow16 * fRec53[0] + fTemp15 + fRec52[1];
		fRec51[0] = fRec52[0];
		double fTemp22 = fSlow17 * (std::max<double>(0.0, 0.5 * (fRec51[0] + 1.0)) + 1.0);
		double fTemp23 = ((fRec47[1] != 0.0) ? (((fRec48[1] > 0.0) & (fRec48[1] < 1.0)) ? fRec47[1] : 0.0) : (((fRec48[1] == 0.0) & (fTemp22 != fRec49[1])) ? fConst123 : (((fRec48[1] == 1.0) & (fTemp22 != fRec50[1])) ? -fConst123 : 0.0)));
		fRec47[0] = fTemp23;
		fRec48[0] = std::max<double>(0.0, std::min<double>(1.0, fRec48[1] + fTemp23));
		fRec49[0] = (((fRec48[1] >= 1.0) & (fRec50[1] != fTemp22)) ? fTemp22 : fRec49[1]);
		fRec50[0] = (((fRec48[1] <= 0.0) & (fRec49[1] != fTemp22)) ? fTemp22 : fRec50[1]);
		int iTemp24 = int(std::min<double>(4096.0, std::max<double>(0.0, fRec49[0])));
		double fTemp25 = fVec8[(IOTA0 - iTemp24) & 8191];
		int iTemp26 = int(std::min<double>(4096.0, std::max<double>(0.0, fRec50[0])));
		fRec10[0] = fTemp25 + fRec48[0] * (fVec8[(IOTA0 - iTemp26) & 8191] - fTemp25) - fRec11[0];
		fRec1[0] = ((iSlow0) ? fRec10[0] : fTemp5) - fConst8 * fRec1[1];
		fRec54[0] = fSlow18 + 0.993 * fRec54[1];
		double fTemp27 = 1.0 - fRec54[0];
		double fTemp28 = fConst124 * fTemp27 * (fRec1[0] - fRec1[1]);
		fRec0[0] = ((signbit(-fTemp28)) ? output12au7_negclip(-fTemp28) : output12au7clip(-fTemp28)) - fConst5 * (fConst4 * fRec0[2] + fConst2 * fRec0[1]);
		double fTemp29 = fConst14 * fRec58[1];
		double fTemp30 = fConst22 * fRec59[1];
		double fTemp31 = fConst30 * fRec60[1];
		fRec62[0] = -(fConst43 * (fConst42 * fRec62[1] - fConst38 * (fTemp2 - fVec1[1])));
		fRec61[0] = fRec62[0] - fConst41 * (fConst39 * fRec61[2] + fConst37 * fRec61[1]);
		fRec60[0] = fConst127 * (fRec61[2] + (fRec61[0] - 2.0 * fRec61[1])) - fConst126 * (fConst125 * fRec60[2] + fTemp31);
		fRec59[0] = fRec60[2] + fConst126 * (fTemp31 + fConst125 * fRec60[0]) - fConst27 * (fConst25 * fRec59[2] + fTemp30);
		fRec58[0] = fRec59[2] + fConst27 * (fTemp30 + fConst25 * fRec59[0]) - fConst19 * (fConst17 * fRec58[2] + fTemp29);
		fRec57[0] = fRec58[2] + fConst19 * (fTemp29 + fConst17 * fRec58[0]) - fConst11 * fRec57[1];
		double fTemp32 = fConst49 * fRec9[0] * (fRec57[0] - fRec57[1]);
		double fTemp33 = ((signbit(-fTemp32)) ? input12au7_negclip(-fTemp32) : input12au7clip(-fTemp32));
		fVec9[0] = fTemp33;
		fRec64[0] = -((fSlow6 * fRec64[1] - (fRec63[1] + fRec63[2])) / fSlow5);
		double fTemp34 = fConst57 * fRec67[1];
		fRec74[0] = -((fRec74[1] * fSlow6 - (fTemp33 + fVec9[1])) / fSlow5);
		fRec73[0] = fRec74[0] - 0.3 * fRec73[1];
		fRec72[0] = 2.0 / (std::exp(-(5.0 * fRec73[0])) + 1.0) + 0.3 * fRec72[1] + -1.0;
		fRec71[0] = -(fConst67 * (fConst66 * fRec71[1] - (fRec72[0] + fRec72[1])));
		fRec70[0] = fRec71[0] - fConst65 * (fConst63 * fRec70[2] + fConst52 * fRec70[1]);
		double fTemp35 = fRec70[2] + fRec70[0] + 2.0 * fRec70[1];
		fVec10[0] = fTemp35;
		fRec69[0] = -(fConst72 * (fConst71 * fRec69[1] - fConst69 * (fTemp35 - fVec10[1])));
		double fTemp36 = fRec69[0] - fRec69[1];
		fRec68[0] = -(fConst72 * (fConst71 * fRec68[1] - fConst70 * fTemp36));
		fRec67[0] = fRec68[0] - fConst62 * (fConst61 * fRec67[2] + fTemp34);
		double fTemp37 = fTemp34 + fConst75 * fRec67[0] + fConst74 * fRec67[2];
		fVec11[0] = fTemp37;
		fRec66[0] = -(fConst79 * (fConst78 * fRec66[1] - fConst62 * (fTemp37 + fVec11[1])));
		fRec65[0] = fRec66[0] - fConst55 * (fConst54 * fRec65[2] + fConst52 * fRec65[1]);
		fRec76[0] = -(fConst86 * (fConst85 * fRec76[1] - (fRec68[0] + fRec68[1])));
		fRec75[0] = fRec76[0] - fConst82 * (fConst81 * fRec75[2] + fConst80 * fRec75[1]);
		fRec80[0] = -(fConst93 * (fConst92 * fRec80[1] - (fRec79[1] + fRec79[2])));
		double fTemp38 = fConst95 * fRec81[1];
		fRec82[0] = -(fConst103 * (fConst102 * fRec82[1] - fConst101 * fTemp36));
		fRec81[0] = fRec82[0] - fConst100 * (fConst99 * fRec81[2] + fTemp38);
		fRec79[0] = fConst100 * (fTemp38 + fConst106 * fRec81[0] + fConst105 * fRec81[2]) - fRec80[0];
		fRec78[0] = fRec79[0] - fConst90 * (fConst89 * fRec78[2] + fConst52 * fRec78[1]);
		fRec77[0] = fConst90 * (fRec78[2] + fRec78[0] + 2.0 * fRec78[1]) - fConst88 * (fConst87 * fRec77[2] + fConst52 * fRec77[1]);
		fRec86[0] = -(fConst93 * (fConst92 * fRec86[1] - (fRec85[1] + fRec85[2])));
		double fTemp39 = fConst95 * fRec87[1];
		fRec87[0] = fRec68[0] - fConst100 * (fConst99 * fRec87[2] + fTemp39);
		fRec85[0] = fConst100 * (fTemp39 + fConst106 * fRec87[0] + fConst105 * fRec87[2]) - fRec86[0];
		fRec84[0] = fRec85[0] - fConst111 * (fConst110 * fRec84[2] + fConst107 * fRec84[1]);
		fRec83[0] = fConst111 * (fRec84[2] + fRec84[0] + 2.0 * fRec84[1]) - fConst109 * (fConst108 * fRec83[2] + fConst107 * fRec83[1]);
		double fTemp40 = ((iSlow7) ? ((iSlow3) ? fConst109 * (fRec83[2] + fRec83[0] + 2.0 * fRec83[1]) : fConst88 * (fRec77[2] + fRec77[0] + 2.0 * fRec77[1])) : ((iSlow3) ? fConst82 * (fRec75[2] + fRec75[0] + 2.0 * fRec75[1]) : fConst55 * (fRec65[2] + fRec65[0] + 2.0 * fRec65[1]))) + fTemp13;
		fVec12[IOTA0 & 8191] = fTemp40;
		double fTemp41 = fVec12[(IOTA0 - iTemp18) & 8191];
		double fTemp42 = fTemp41 + fRec41[0] * (fVec12[(IOTA0 - iTemp20) & 8191] - fTemp41);
		fVec13[IOTA0 & 8191] = fTemp42;
		double fTemp43 = fVec13[(IOTA0 - iTemp24) & 8191];
		fRec63[0] = fTemp43 + fRec48[0] * (fVec13[(IOTA0 - iTemp26) & 8191] - fTemp43) - fRec64[0];
		fRec56[0] = ((iSlow0) ? fRec63[0] : fTemp33) - fConst8 * fRec56[1];
		double fTemp44 = fConst124 * fTemp27 * (fRec56[0] - fRec56[1]);
		fRec55[0] = ((signbit(-fTemp44)) ? output12au7_negclip(-fTemp44) : output12au7clip(-fTemp44)) - fConst5 * (fConst4 * fRec55[2] + fConst2 * fRec55[1]);
		double fTemp45 = fConst14 * fRec91[1];
		fRec95[0] = -(fConst47 * (fConst45 * fRec95[1] - fConst41 * (fTemp3 + fVec2[1])));
		fRec94[0] = fRec95[0] - fConst34 * (fConst32 * fRec94[2] + fConst30 * fRec94[1]);
		double fTemp46 = fRec94[2] + fRec94[0] + 2.0 * fRec94[1];
		fVec14[0] = fTemp46;
		fRec93[0] = -(fConst132 * (fConst24 * fRec93[1] - fConst131 * (fTemp46 - fVec14[1])));
		fRec92[0] = fRec93[0] - fConst130 * (fConst128 * fRec92[2] + fConst22 * fRec92[1]);
		fRec91[0] = fConst133 * (fRec92[2] + (fRec92[0] - 2.0 * fRec92[1])) - fConst19 * (fConst17 * fRec91[2] + fTemp45);
		fRec90[0] = fRec91[2] + fConst19 * (fTemp45 + fConst17 * fRec91[0]) - fConst11 * fRec90[1];
		double fTemp47 = fConst49 * fRec9[0] * (fRec90[0] - fRec90[1]);
		double fTemp48 = ((signbit(-fTemp47)) ? input12au7_negclip(-fTemp47) : input12au7clip(-fTemp47));
		fVec15[0] = fTemp48;
		fRec97[0] = -((fSlow6 * fRec97[1] - (fRec96[1] + fRec96[2])) / fSlow5);
		double fTemp49 = fConst57 * fRec100[1];
		fRec107[0] = -((fSlow6 * fRec107[1] - (fTemp48 + fVec15[1])) / fSlow5);
		fRec106[0] = fRec107[0] - 0.3 * fRec106[1];
		fRec105[0] = 2.0 / (std::exp(-(5.0 * fRec106[0])) + 1.0) + 0.3 * fRec105[1] + -1.0;
		fRec104[0] = -(fConst67 * (fConst66 * fRec104[1] - (fRec105[0] + fRec105[1])));
		fRec103[0] = fRec104[0] - fConst65 * (fConst63 * fRec103[2] + fConst52 * fRec103[1]);
		double fTemp50 = fRec103[2] + fRec103[0] + 2.0 * fRec103[1];
		fVec16[0] = fTemp50;
		fRec102[0] = -(fConst72 * (fConst71 * fRec102[1] - fConst69 * (fTemp50 - fVec16[1])));
		double fTemp51 = fRec102[0] - fRec102[1];
		fRec101[0] = -(fConst72 * (fConst71 * fRec101[1] - fConst70 * fTemp51));
		fRec100[0] = fRec101[0] - fConst62 * (fConst61 * fRec100[2] + fTemp49);
		double fTemp52 = fTemp49 + fConst75 * fRec100[0] + fConst74 * fRec100[2];
		fVec17[0] = fTemp52;
		fRec99[0] = -(fConst79 * (fConst78 * fRec99[1] - fConst62 * (fTemp52 + fVec17[1])));
		fRec98[0] = fRec99[0] - fConst55 * (fConst54 * fRec98[2] + fConst52 * fRec98[1]);
		fRec109[0] = -(fConst86 * (fConst85 * fRec109[1] - (fRec101[0] + fRec101[1])));
		fRec108[0] = fRec109[0] - fConst82 * (fConst81 * fRec108[2] + fConst80 * fRec108[1]);
		fRec113[0] = -(fConst93 * (fConst92 * fRec113[1] - (fRec112[1] + fRec112[2])));
		double fTemp53 = fConst95 * fRec114[1];
		fRec115[0] = -(fConst103 * (fConst102 * fRec115[1] - fConst101 * fTemp51));
		fRec114[0] = fRec115[0] - fConst100 * (fConst99 * fRec114[2] + fTemp53);
		fRec112[0] = fConst100 * (fTemp53 + fConst106 * fRec114[0] + fConst105 * fRec114[2]) - fRec113[0];
		fRec111[0] = fRec112[0] - fConst90 * (fConst89 * fRec111[2] + fConst52 * fRec111[1]);
		fRec110[0] = fConst90 * (fRec111[2] + fRec111[0] + 2.0 * fRec111[1]) - fConst88 * (fConst87 * fRec110[2] + fConst52 * fRec110[1]);
		fRec119[0] = -(fConst93 * (fConst92 * fRec119[1] - (fRec118[1] + fRec118[2])));
		double fTemp54 = fConst95 * fRec120[1];
		fRec120[0] = fRec101[0] - fConst100 * (fConst99 * fRec120[2] + fTemp54);
		fRec118[0] = fConst100 * (fTemp54 + fConst106 * fRec120[0] + fConst105 * fRec120[2]) - fRec119[0];
		fRec117[0] = fRec118[0] - fConst111 * (fConst110 * fRec117[2] + fConst107 * fRec117[1]);
		fRec116[0] = fConst111 * (fRec117[2] + fRec117[0] + 2.0 * fRec117[1]) - fConst109 * (fConst108 * fRec116[2] + fConst107 * fRec116[1]);
		double fTemp55 = fTemp13 + ((iSlow7) ? ((iSlow3) ? fConst109 * (fRec116[2] + fRec116[0] + 2.0 * fRec116[1]) : fConst88 * (fRec110[2] + fRec110[0] + 2.0 * fRec110[1])) : ((iSlow3) ? fConst82 * (fRec108[2] + fRec108[0] + 2.0 * fRec108[1]) : fConst55 * (fRec98[2] + fRec98[0] + 2.0 * fRec98[1])));
		fVec18[IOTA0 & 8191] = fTemp55;
		double fTemp56 = fVec18[(IOTA0 - iTemp18) & 8191];
		double fTemp57 = fTemp56 + fRec41[0] * (fVec18[(IOTA0 - iTemp20) & 8191] - fTemp56);
		fVec19[IOTA0 & 8191] = fTemp57;
		double fTemp58 = fVec19[(IOTA0 - iTemp24) & 8191];
		fRec96[0] = fTemp58 + fRec48[0] * (fVec19[(IOTA0 - iTemp26) & 8191] - fTemp58) - fRec97[0];
		fRec89[0] = ((iSlow0) ? fRec96[0] : fTemp48) - fConst8 * fRec89[1];
		double fTemp59 = fConst124 * fTemp27 * (fRec89[0] - fRec89[1]);
		fRec88[0] = ((signbit(-fTemp59)) ? output12au7_negclip(-fTemp59) : output12au7clip(-fTemp59)) - fConst5 * (fConst4 * fRec88[2] + fConst2 * fRec88[1]);
		fRec127[0] = -(fConst132 * (fConst24 * fRec127[1] - fConst34 * (fTemp46 + fVec14[1])));
		fRec126[0] = fRec127[0] - fConst130 * (fConst128 * fRec126[2] + fConst22 * fRec126[1]);
		double fTemp60 = fRec126[2] + fRec126[0] + 2.0 * fRec126[1];
		fVec20[0] = fTemp60;
		fRec125[0] = -(fConst138 * (fConst16 * fRec125[1] - fConst137 * (fTemp60 - fVec20[1])));
		fRec124[0] = fRec125[0] - fConst136 * (fConst134 * fRec124[2] + fConst14 * fRec124[1]);
		fRec123[0] = fConst139 * (fRec124[2] + (fRec124[0] - 2.0 * fRec124[1])) - fConst11 * fRec123[1];
		double fTemp61 = fConst49 * fRec9[0] * (fRec123[0] - fRec123[1]);
		double fTemp62 = ((signbit(-fTemp61)) ? input12au7_negclip(-fTemp61) : input12au7clip(-fTemp61));
		fVec21[0] = fTemp62;
		fRec129[0] = -((fSlow6 * fRec129[1] - (fRec128[1] + fRec128[2])) / fSlow5);
		double fTemp63 = fConst57 * fRec132[1];
		fRec139[0] = -((fSlow6 * fRec139[1] - (fTemp62 + fVec21[1])) / fSlow5);
		fRec138[0] = fRec139[0] - 0.3 * fRec138[1];
		fRec137[0] = 2.0 / (std::exp(-(5.0 * fRec138[0])) + 1.0) + 0.3 * fRec137[1] + -1.0;
		fRec136[0] = -(fConst67 * (fConst66 * fRec136[1] - (fRec137[0] + fRec137[1])));
		fRec135[0] = fRec136[0] - fConst65 * (fConst63 * fRec135[2] + fConst52 * fRec135[1]);
		double fTemp64 = fRec135[2] + fRec135[0] + 2.0 * fRec135[1];
		fVec22[0] = fTemp64;
		fRec134[0] = -(fConst72 * (fConst71 * fRec134[1] - fConst69 * (fTemp64 - fVec22[1])));
		double fTemp65 = fRec134[0] - fRec134[1];
		fRec133[0] = -(fConst72 * (fConst71 * fRec133[1] - fConst70 * fTemp65));
		fRec132[0] = fRec133[0] - fConst62 * (fConst61 * fRec132[2] + fTemp63);
		double fTemp66 = fTemp63 + fConst75 * fRec132[0] + fConst74 * fRec132[2];
		fVec23[0] = fTemp66;
		fRec131[0] = -(fConst79 * (fConst78 * fRec131[1] - fConst62 * (fTemp66 + fVec23[1])));
		fRec130[0] = fRec131[0] - fConst55 * (fConst54 * fRec130[2] + fConst52 * fRec130[1]);
		fRec141[0] = -(fConst86 * (fConst85 * fRec141[1] - (fRec133[0] + fRec133[1])));
		fRec140[0] = fRec141[0] - fConst82 * (fConst81 * fRec140[2] + fConst80 * fRec140[1]);
		fRec145[0] = -(fConst93 * (fConst92 * fRec145[1] - (fRec144[1] + fRec144[2])));
		double fTemp67 = fConst95 * fRec146[1];
		fRec147[0] = -(fConst103 * (fConst102 * fRec147[1] - fConst101 * fTemp65));
		fRec146[0] = fRec147[0] - fConst100 * (fConst99 * fRec146[2] + fTemp67);
		fRec144[0] = fConst100 * (fTemp67 + fConst106 * fRec146[0] + fConst105 * fRec146[2]) - fRec145[0];
		fRec143[0] = fRec144[0] - fConst90 * (fConst89 * fRec143[2] + fConst52 * fRec143[1]);
		fRec142[0] = fConst90 * (fRec143[2] + fRec143[0] + 2.0 * fRec143[1]) - fConst88 * (fConst87 * fRec142[2] + fConst52 * fRec142[1]);
		fRec151[0] = -(fConst93 * (fConst92 * fRec151[1] - (fRec150[1] + fRec150[2])));
		double fTemp68 = fConst95 * fRec152[1];
		fRec152[0] = fRec133[0] - fConst100 * (fConst99 * fRec152[2] + fTemp68);
		fRec150[0] = fConst100 * (fTemp68 + fConst106 * fRec152[0] + fConst105 * fRec152[2]) - fRec151[0];
		fRec149[0] = fRec150[0] - fConst111 * (fConst110 * fRec149[2] + fConst107 * fRec149[1]);
		fRec148[0] = fConst111 * (fRec149[2] + fRec149[0] + 2.0 * fRec149[1]) - fConst109 * (fConst108 * fRec148[2] + fConst107 * fRec148[1]);
		double fTemp69 = fTemp13 + ((iSlow7) ? ((iSlow3) ? fConst109 * (fRec148[2] + fRec148[0] + 2.0 * fRec148[1]) : fConst88 * (fRec142[2] + fRec142[0] + 2.0 * fRec142[1])) : ((iSlow3) ? fConst82 * (fRec140[2] + fRec140[0] + 2.0 * fRec140[1]) : fConst55 * (fRec130[2] + fRec130[0] + 2.0 * fRec130[1])));
		fVec24[IOTA0 & 8191] = fTemp69;
		double fTemp70 = fVec24[(IOTA0 - iTemp18) & 8191];
		double fTemp71 = fTemp70 + fRec41[0] * (fVec24[(IOTA0 - iTemp20) & 8191] - fTemp70);
		fVec25[IOTA0 & 8191] = fTemp71;
		double fTemp72 = fVec25[(IOTA0 - iTemp24) & 8191];
		fRec128[0] = fTemp72 + fRec48[0] * (fVec25[(IOTA0 - iTemp26) & 8191] - fTemp72) - fRec129[0];
		fRec122[0] = ((iSlow0) ? fRec128[0] : fTemp62) - fConst8 * fRec122[1];
		double fTemp73 = fConst124 * fTemp27 * (fRec122[0] - fRec122[1]);
		fRec121[0] = ((signbit(-fTemp73)) ? output12au7_negclip(-fTemp73) : output12au7clip(-fTemp73)) - fConst5 * (fConst4 * fRec121[2] + fConst2 * fRec121[1]);
		fRec157[0] = -(fConst138 * (fConst16 * fRec157[1] - fConst130 * (fTemp60 + fVec20[1])));
		fRec156[0] = fRec157[0] - fConst136 * (fConst134 * fRec156[2] + fConst14 * fRec156[1]);
		fRec155[0] = fConst136 * (fRec156[2] + fRec156[0] + 2.0 * fRec156[1]) - fConst11 * fRec155[1];
		double fTemp74 = fConst49 * fRec9[0] * (fRec155[0] - fRec155[1]);
		double fTemp75 = ((signbit(-fTemp74)) ? input12au7_negclip(-fTemp74) : input12au7clip(-fTemp74));
		fVec26[0] = fTemp75;
		fRec159[0] = -((fSlow6 * fRec159[1] - (fRec158[1] + fRec158[2])) / fSlow5);
		double fTemp76 = fConst57 * fRec162[1];
		fRec169[0] = -((fSlow6 * fRec169[1] - (fTemp75 + fVec26[1])) / fSlow5);
		fRec168[0] = fRec169[0] - 0.3 * fRec168[1];
		fRec167[0] = 2.0 / (std::exp(-(5.0 * fRec168[0])) + 1.0) + 0.3 * fRec167[1] + -1.0;
		fRec166[0] = -(fConst67 * (fConst66 * fRec166[1] - (fRec167[0] + fRec167[1])));
		fRec165[0] = fRec166[0] - fConst65 * (fConst63 * fRec165[2] + fConst52 * fRec165[1]);
		double fTemp77 = fRec165[2] + fRec165[0] + 2.0 * fRec165[1];
		fVec27[0] = fTemp77;
		fRec164[0] = -(fConst72 * (fConst71 * fRec164[1] - fConst69 * (fTemp77 - fVec27[1])));
		double fTemp78 = fRec164[0] - fRec164[1];
		fRec163[0] = -(fConst72 * (fConst71 * fRec163[1] - fConst70 * fTemp78));
		fRec162[0] = fRec163[0] - fConst62 * (fConst61 * fRec162[2] + fTemp76);
		double fTemp79 = fTemp76 + fConst75 * fRec162[0] + fConst74 * fRec162[2];
		fVec28[0] = fTemp79;
		fRec161[0] = -(fConst79 * (fConst78 * fRec161[1] - fConst62 * (fTemp79 + fVec28[1])));
		fRec160[0] = fRec161[0] - fConst55 * (fConst54 * fRec160[2] + fConst52 * fRec160[1]);
		fRec171[0] = -(fConst86 * (fConst85 * fRec171[1] - (fRec163[0] + fRec163[1])));
		fRec170[0] = fRec171[0] - fConst82 * (fConst81 * fRec170[2] + fConst80 * fRec170[1]);
		fRec175[0] = -(fConst93 * (fConst92 * fRec175[1] - (fRec174[1] + fRec174[2])));
		double fTemp80 = fConst95 * fRec176[1];
		fRec177[0] = -(fConst103 * (fConst102 * fRec177[1] - fConst101 * fTemp78));
		fRec176[0] = fRec177[0] - fConst100 * (fConst99 * fRec176[2] + fTemp80);
		fRec174[0] = fConst100 * (fTemp80 + fConst106 * fRec176[0] + fConst105 * fRec176[2]) - fRec175[0];
		fRec173[0] = fRec174[0] - fConst90 * (fConst89 * fRec173[2] + fConst52 * fRec173[1]);
		fRec172[0] = fConst90 * (fRec173[2] + fRec173[0] + 2.0 * fRec173[1]) - fConst88 * (fConst87 * fRec172[2] + fConst52 * fRec172[1]);
		fRec181[0] = -(fConst93 * (fConst92 * fRec181[1] - (fRec180[1] + fRec180[2])));
		double fTemp81 = fConst95 * fRec182[1];
		fRec182[0] = fRec163[0] - fConst100 * (fConst99 * fRec182[2] + fTemp81);
		fRec180[0] = fConst100 * (fTemp81 + fConst106 * fRec182[0] + fConst105 * fRec182[2]) - fRec181[0];
		fRec179[0] = fRec180[0] - fConst111 * (fConst110 * fRec179[2] + fConst107 * fRec179[1]);
		fRec178[0] = fConst111 * (fRec179[2] + fRec179[0] + 2.0 * fRec179[1]) - fConst109 * (fConst108 * fRec178[2] + fConst107 * fRec178[1]);
		double fTemp82 = fTemp13 + ((iSlow7) ? ((iSlow3) ? fConst109 * (fRec178[2] + fRec178[0] + 2.0 * fRec178[1]) : fConst88 * (fRec172[2] + fRec172[0] + 2.0 * fRec172[1])) : ((iSlow3) ? fConst82 * (fRec170[2] + fRec170[0] + 2.0 * fRec170[1]) : fConst55 * (fRec160[2] + fRec160[0] + 2.0 * fRec160[1])));
		fVec29[IOTA0 & 8191] = fTemp82;
		double fTemp83 = fVec29[(IOTA0 - iTemp18) & 8191];
		double fTemp84 = fTemp83 + fRec41[0] * (fVec29[(IOTA0 - iTemp20) & 8191] - fTemp83);
		fVec30[IOTA0 & 8191] = fTemp84;
		double fTemp85 = fVec30[(IOTA0 - iTemp24) & 8191];
		fRec158[0] = fTemp85 + fRec48[0] * (fVec30[(IOTA0 - iTemp26) & 8191] - fTemp85) - fRec159[0];
		fRec154[0] = ((iSlow0) ? fRec158[0] : fTemp75) - fConst8 * fRec154[1];
		double fTemp86 = fConst124 * fTemp27 * (fRec154[0] - fRec154[1]);
		fRec153[0] = ((signbit(-fTemp86)) ? output12au7_negclip(-fTemp86) : output12au7clip(-fTemp86)) - fConst5 * (fConst4 * fRec153[2] + fConst2 * fRec153[1]);
		output0[i0] = FAUSTFLOAT(fConst5 * (2.0 * (fRec153[1] + fRec121[1] + fRec88[1] + fRec55[1] + fRec0[1]) + fRec153[2] + fRec121[2] + fRec88[2] + fRec0[2] + fRec55[2] + fRec153[0] + fRec121[0] + fRec88[0] + fRec55[0] + fRec0[0]));
		iVec0[1] = iVec0[0];
		fVec1[1] = fVec1[0];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fVec2[1] = fVec2[0];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec9[1] = fRec9[0];
		fVec3[1] = fVec3[0];
		fRec11[1] = fRec11[0];
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fVec4[1] = fVec4[0];
		fRec16[1] = fRec16[0];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fVec5[1] = fVec5[0];
		fRec13[1] = fRec13[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fRec27[1] = fRec27[0];
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fRec33[1] = fRec33[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		iRec37[1] = iRec37[0];
		fRec38[1] = fRec38[0];
		fVec6[1] = fVec6[0];
		fRec36[1] = fRec36[0];
		fRec39[1] = fRec39[0];
		fRec35[2] = fRec35[1];
		fRec35[1] = fRec35[0];
		IOTA0 = IOTA0 + 1;
		fRec46[1] = fRec46[0];
		fRec45[1] = fRec45[0];
		fRec44[1] = fRec44[0];
		fRec40[1] = fRec40[0];
		fRec41[1] = fRec41[0];
		fRec42[1] = fRec42[0];
		fRec43[1] = fRec43[0];
		fRec53[1] = fRec53[0];
		fRec52[1] = fRec52[0];
		fRec51[1] = fRec51[0];
		fRec47[1] = fRec47[0];
		fRec48[1] = fRec48[0];
		fRec49[1] = fRec49[0];
		fRec50[1] = fRec50[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec1[1] = fRec1[0];
		fRec54[1] = fRec54[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		fRec62[1] = fRec62[0];
		fRec61[2] = fRec61[1];
		fRec61[1] = fRec61[0];
		fRec60[2] = fRec60[1];
		fRec60[1] = fRec60[0];
		fRec59[2] = fRec59[1];
		fRec59[1] = fRec59[0];
		fRec58[2] = fRec58[1];
		fRec58[1] = fRec58[0];
		fRec57[1] = fRec57[0];
		fVec9[1] = fVec9[0];
		fRec64[1] = fRec64[0];
		fRec74[1] = fRec74[0];
		fRec73[1] = fRec73[0];
		fRec72[1] = fRec72[0];
		fRec71[1] = fRec71[0];
		fRec70[2] = fRec70[1];
		fRec70[1] = fRec70[0];
		fVec10[1] = fVec10[0];
		fRec69[1] = fRec69[0];
		fRec68[1] = fRec68[0];
		fRec67[2] = fRec67[1];
		fRec67[1] = fRec67[0];
		fVec11[1] = fVec11[0];
		fRec66[1] = fRec66[0];
		fRec65[2] = fRec65[1];
		fRec65[1] = fRec65[0];
		fRec76[1] = fRec76[0];
		fRec75[2] = fRec75[1];
		fRec75[1] = fRec75[0];
		fRec80[1] = fRec80[0];
		fRec82[1] = fRec82[0];
		fRec81[2] = fRec81[1];
		fRec81[1] = fRec81[0];
		fRec79[2] = fRec79[1];
		fRec79[1] = fRec79[0];
		fRec78[2] = fRec78[1];
		fRec78[1] = fRec78[0];
		fRec77[2] = fRec77[1];
		fRec77[1] = fRec77[0];
		fRec86[1] = fRec86[0];
		fRec87[2] = fRec87[1];
		fRec87[1] = fRec87[0];
		fRec85[2] = fRec85[1];
		fRec85[1] = fRec85[0];
		fRec84[2] = fRec84[1];
		fRec84[1] = fRec84[0];
		fRec83[2] = fRec83[1];
		fRec83[1] = fRec83[0];
		fRec63[2] = fRec63[1];
		fRec63[1] = fRec63[0];
		fRec56[1] = fRec56[0];
		fRec55[2] = fRec55[1];
		fRec55[1] = fRec55[0];
		fRec95[1] = fRec95[0];
		fRec94[2] = fRec94[1];
		fRec94[1] = fRec94[0];
		fVec14[1] = fVec14[0];
		fRec93[1] = fRec93[0];
		fRec92[2] = fRec92[1];
		fRec92[1] = fRec92[0];
		fRec91[2] = fRec91[1];
		fRec91[1] = fRec91[0];
		fRec90[1] = fRec90[0];
		fVec15[1] = fVec15[0];
		fRec97[1] = fRec97[0];
		fRec107[1] = fRec107[0];
		fRec106[1] = fRec106[0];
		fRec105[1] = fRec105[0];
		fRec104[1] = fRec104[0];
		fRec103[2] = fRec103[1];
		fRec103[1] = fRec103[0];
		fVec16[1] = fVec16[0];
		fRec102[1] = fRec102[0];
		fRec101[1] = fRec101[0];
		fRec100[2] = fRec100[1];
		fRec100[1] = fRec100[0];
		fVec17[1] = fVec17[0];
		fRec99[1] = fRec99[0];
		fRec98[2] = fRec98[1];
		fRec98[1] = fRec98[0];
		fRec109[1] = fRec109[0];
		fRec108[2] = fRec108[1];
		fRec108[1] = fRec108[0];
		fRec113[1] = fRec113[0];
		fRec115[1] = fRec115[0];
		fRec114[2] = fRec114[1];
		fRec114[1] = fRec114[0];
		fRec112[2] = fRec112[1];
		fRec112[1] = fRec112[0];
		fRec111[2] = fRec111[1];
		fRec111[1] = fRec111[0];
		fRec110[2] = fRec110[1];
		fRec110[1] = fRec110[0];
		fRec119[1] = fRec119[0];
		fRec120[2] = fRec120[1];
		fRec120[1] = fRec120[0];
		fRec118[2] = fRec118[1];
		fRec118[1] = fRec118[0];
		fRec117[2] = fRec117[1];
		fRec117[1] = fRec117[0];
		fRec116[2] = fRec116[1];
		fRec116[1] = fRec116[0];
		fRec96[2] = fRec96[1];
		fRec96[1] = fRec96[0];
		fRec89[1] = fRec89[0];
		fRec88[2] = fRec88[1];
		fRec88[1] = fRec88[0];
		fRec127[1] = fRec127[0];
		fRec126[2] = fRec126[1];
		fRec126[1] = fRec126[0];
		fVec20[1] = fVec20[0];
		fRec125[1] = fRec125[0];
		fRec124[2] = fRec124[1];
		fRec124[1] = fRec124[0];
		fRec123[1] = fRec123[0];
		fVec21[1] = fVec21[0];
		fRec129[1] = fRec129[0];
		fRec139[1] = fRec139[0];
		fRec138[1] = fRec138[0];
		fRec137[1] = fRec137[0];
		fRec136[1] = fRec136[0];
		fRec135[2] = fRec135[1];
		fRec135[1] = fRec135[0];
		fVec22[1] = fVec22[0];
		fRec134[1] = fRec134[0];
		fRec133[1] = fRec133[0];
		fRec132[2] = fRec132[1];
		fRec132[1] = fRec132[0];
		fVec23[1] = fVec23[0];
		fRec131[1] = fRec131[0];
		fRec130[2] = fRec130[1];
		fRec130[1] = fRec130[0];
		fRec141[1] = fRec141[0];
		fRec140[2] = fRec140[1];
		fRec140[1] = fRec140[0];
		fRec145[1] = fRec145[0];
		fRec147[1] = fRec147[0];
		fRec146[2] = fRec146[1];
		fRec146[1] = fRec146[0];
		fRec144[2] = fRec144[1];
		fRec144[1] = fRec144[0];
		fRec143[2] = fRec143[1];
		fRec143[1] = fRec143[0];
		fRec142[2] = fRec142[1];
		fRec142[1] = fRec142[0];
		fRec151[1] = fRec151[0];
		fRec152[2] = fRec152[1];
		fRec152[1] = fRec152[0];
		fRec150[2] = fRec150[1];
		fRec150[1] = fRec150[0];
		fRec149[2] = fRec149[1];
		fRec149[1] = fRec149[0];
		fRec148[2] = fRec148[1];
		fRec148[1] = fRec148[0];
		fRec128[2] = fRec128[1];
		fRec128[1] = fRec128[0];
		fRec122[1] = fRec122[0];
		fRec121[2] = fRec121[1];
		fRec121[1] = fRec121[0];
		fRec157[1] = fRec157[0];
		fRec156[2] = fRec156[1];
		fRec156[1] = fRec156[0];
		fRec155[1] = fRec155[0];
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
		fRec154[1] = fRec154[0];
		fRec153[2] = fRec153[1];
		fRec153[1] = fRec153[0];
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
