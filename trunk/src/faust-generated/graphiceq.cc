// generated from file '../src/faust/graphiceq.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace graphiceq {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	double fConst1;
	double fConst4;
	double fConst6;
	double fConst8;
	double fConst11;
	double fConst13;
	double fConst15;
	double fConst18;
	double fConst20;
	double fConst22;
	double fConst25;
	double fConst27;
	double fConst29;
	double fConst32;
	double fConst34;
	double fConst36;
	double fConst39;
	double fConst41;
	double fConst43;
	double fConst46;
	double fConst48;
	double fConst50;
	double fConst53;
	double fConst55;
	double fConst57;
	double fConst60;
	double fConst62;
	double fConst64;
	double fConst67;
	double fConst68;
	double fConst69;
	double fConst71;
	double fVec0[2];
	double fConst72;
	double fConst73;
	double fRec22[2];
	double fRec21[3];
	double fVec1[2];
	double fConst74;
	double fConst76;
	double fRec20[2];
	double fRec19[3];
	double fVec2[2];
	double fConst77;
	double fConst79;
	double fRec18[2];
	double fRec17[3];
	double fVec3[2];
	double fConst80;
	double fConst82;
	double fRec16[2];
	double fRec15[3];
	double fVec4[2];
	double fConst83;
	double fConst85;
	double fRec14[2];
	double fRec13[3];
	double fVec5[2];
	double fConst86;
	double fConst88;
	double fRec12[2];
	double fRec11[3];
	double fVec6[2];
	double fConst89;
	double fConst91;
	double fRec10[2];
	double fRec9[3];
	double fVec7[2];
	double fConst92;
	double fConst94;
	double fRec8[2];
	double fRec7[3];
	double fVec8[2];
	double fConst95;
	double fConst97;
	double fRec6[2];
	double fRec5[3];
	double fVec9[2];
	double fConst98;
	double fConst100;
	double fRec4[2];
	double fRec3[3];
	FAUSTFLOAT fVslider0;
	double fRec23[2];
	double fRec0[2];
	int iRec1[2];
	double fRec2[2];
	FAUSTFLOAT fVbargraph0;
	double fConst101;
	double fConst102;
	double fConst103;
	double fRec29[2];
	double fRec28[3];
	double fConst104;
	double fRec27[3];
	FAUSTFLOAT fVslider1;
	double fRec30[2];
	double fRec24[2];
	int iRec25[2];
	double fRec26[2];
	FAUSTFLOAT fVbargraph1;
	double fConst105;
	double fConst106;
	double fConst107;
	double fRec37[2];
	double fRec36[3];
	double fConst108;
	double fRec35[3];
	double fRec34[3];
	FAUSTFLOAT fVslider2;
	double fRec38[2];
	double fRec31[2];
	int iRec32[2];
	double fRec33[2];
	FAUSTFLOAT fVbargraph2;
	double fConst109;
	double fConst110;
	double fConst111;
	double fRec46[2];
	double fRec45[3];
	double fConst112;
	double fRec44[3];
	double fRec43[3];
	double fRec42[3];
	FAUSTFLOAT fVslider3;
	double fRec47[2];
	double fRec39[2];
	int iRec40[2];
	double fRec41[2];
	FAUSTFLOAT fVbargraph3;
	double fConst113;
	double fConst114;
	double fConst115;
	double fRec56[2];
	double fRec55[3];
	double fConst116;
	double fRec54[3];
	double fRec53[3];
	double fRec52[3];
	double fRec51[3];
	FAUSTFLOAT fVslider4;
	double fRec57[2];
	double fRec48[2];
	int iRec49[2];
	double fRec50[2];
	FAUSTFLOAT fVbargraph4;
	double fConst117;
	double fConst118;
	double fConst119;
	double fRec67[2];
	double fRec66[3];
	double fConst120;
	double fRec65[3];
	double fRec64[3];
	double fRec63[3];
	double fRec62[3];
	double fRec61[3];
	FAUSTFLOAT fVslider5;
	double fRec68[2];
	double fRec58[2];
	int iRec59[2];
	double fRec60[2];
	FAUSTFLOAT fVbargraph5;
	double fConst121;
	double fConst122;
	double fConst123;
	double fRec79[2];
	double fRec78[3];
	double fConst124;
	double fRec77[3];
	double fRec76[3];
	double fRec75[3];
	double fRec74[3];
	double fRec73[3];
	double fRec72[3];
	FAUSTFLOAT fVslider6;
	double fRec80[2];
	double fRec69[2];
	int iRec70[2];
	double fRec71[2];
	FAUSTFLOAT fVbargraph6;
	double fConst125;
	double fConst126;
	double fConst127;
	double fRec92[2];
	double fRec91[3];
	double fConst128;
	double fRec90[3];
	double fRec89[3];
	double fRec88[3];
	double fRec87[3];
	double fRec86[3];
	double fRec85[3];
	double fRec84[3];
	FAUSTFLOAT fVslider7;
	double fRec93[2];
	double fRec81[2];
	int iRec82[2];
	double fRec83[2];
	FAUSTFLOAT fVbargraph7;
	double fConst129;
	double fConst130;
	double fConst131;
	double fRec106[2];
	double fRec105[3];
	double fConst132;
	double fRec104[3];
	double fRec103[3];
	double fRec102[3];
	double fRec101[3];
	double fRec100[3];
	double fRec99[3];
	double fRec98[3];
	double fRec97[3];
	FAUSTFLOAT fVslider8;
	double fRec107[2];
	double fRec94[2];
	int iRec95[2];
	double fRec96[2];
	FAUSTFLOAT fVbargraph8;
	double fConst133;
	double fConst134;
	double fRec121[2];
	double fRec120[3];
	double fConst135;
	double fRec119[3];
	double fRec118[3];
	double fRec117[3];
	double fRec116[3];
	double fRec115[3];
	double fRec114[3];
	double fRec113[3];
	double fRec112[3];
	double fRec111[3];
	FAUSTFLOAT fVslider9;
	double fRec122[2];
	double fRec108[2];
	int iRec109[2];
	double fRec110[2];
	FAUSTFLOAT fVbargraph9;
	double fConst136;
	double fRec127[2];
	double fRec126[3];
	FAUSTFLOAT fVslider10;
	double fRec128[2];
	double fConst137;
	double fRec123[2];
	int iRec124[2];
	double fRec125[2];
	FAUSTFLOAT fVbargraph10;

	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int sample_rate, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "graphiceq";
	name = N_("Graphic EQ");
	groups = 0;
	description = N_("Graphic EQ"); // description (tooltip)
	category = N_("Tone Control");       // category
	shortname = "";     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	load_ui = load_ui_f_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fVec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec22[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRec21[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fVec1[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec20[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec19[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fVec2[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec18[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec17[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fVec3[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec16[l10] = 0.0;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec15[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fVec4[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec14[l13] = 0.0;
	for (int l14 = 0; l14 < 3; l14 = l14 + 1) fRec13[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fVec5[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec12[l16] = 0.0;
	for (int l17 = 0; l17 < 3; l17 = l17 + 1) fRec11[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fVec6[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec10[l19] = 0.0;
	for (int l20 = 0; l20 < 3; l20 = l20 + 1) fRec9[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fVec7[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec8[l22] = 0.0;
	for (int l23 = 0; l23 < 3; l23 = l23 + 1) fRec7[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fVec8[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec6[l25] = 0.0;
	for (int l26 = 0; l26 < 3; l26 = l26 + 1) fRec5[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fVec9[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec4[l28] = 0.0;
	for (int l29 = 0; l29 < 3; l29 = l29 + 1) fRec3[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec23[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec0[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) iRec1[l32] = 0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fRec2[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fRec29[l34] = 0.0;
	for (int l35 = 0; l35 < 3; l35 = l35 + 1) fRec28[l35] = 0.0;
	for (int l36 = 0; l36 < 3; l36 = l36 + 1) fRec27[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec30[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fRec24[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) iRec25[l39] = 0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec26[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec37[l41] = 0.0;
	for (int l42 = 0; l42 < 3; l42 = l42 + 1) fRec36[l42] = 0.0;
	for (int l43 = 0; l43 < 3; l43 = l43 + 1) fRec35[l43] = 0.0;
	for (int l44 = 0; l44 < 3; l44 = l44 + 1) fRec34[l44] = 0.0;
	for (int l45 = 0; l45 < 2; l45 = l45 + 1) fRec38[l45] = 0.0;
	for (int l46 = 0; l46 < 2; l46 = l46 + 1) fRec31[l46] = 0.0;
	for (int l47 = 0; l47 < 2; l47 = l47 + 1) iRec32[l47] = 0;
	for (int l48 = 0; l48 < 2; l48 = l48 + 1) fRec33[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec46[l49] = 0.0;
	for (int l50 = 0; l50 < 3; l50 = l50 + 1) fRec45[l50] = 0.0;
	for (int l51 = 0; l51 < 3; l51 = l51 + 1) fRec44[l51] = 0.0;
	for (int l52 = 0; l52 < 3; l52 = l52 + 1) fRec43[l52] = 0.0;
	for (int l53 = 0; l53 < 3; l53 = l53 + 1) fRec42[l53] = 0.0;
	for (int l54 = 0; l54 < 2; l54 = l54 + 1) fRec47[l54] = 0.0;
	for (int l55 = 0; l55 < 2; l55 = l55 + 1) fRec39[l55] = 0.0;
	for (int l56 = 0; l56 < 2; l56 = l56 + 1) iRec40[l56] = 0;
	for (int l57 = 0; l57 < 2; l57 = l57 + 1) fRec41[l57] = 0.0;
	for (int l58 = 0; l58 < 2; l58 = l58 + 1) fRec56[l58] = 0.0;
	for (int l59 = 0; l59 < 3; l59 = l59 + 1) fRec55[l59] = 0.0;
	for (int l60 = 0; l60 < 3; l60 = l60 + 1) fRec54[l60] = 0.0;
	for (int l61 = 0; l61 < 3; l61 = l61 + 1) fRec53[l61] = 0.0;
	for (int l62 = 0; l62 < 3; l62 = l62 + 1) fRec52[l62] = 0.0;
	for (int l63 = 0; l63 < 3; l63 = l63 + 1) fRec51[l63] = 0.0;
	for (int l64 = 0; l64 < 2; l64 = l64 + 1) fRec57[l64] = 0.0;
	for (int l65 = 0; l65 < 2; l65 = l65 + 1) fRec48[l65] = 0.0;
	for (int l66 = 0; l66 < 2; l66 = l66 + 1) iRec49[l66] = 0;
	for (int l67 = 0; l67 < 2; l67 = l67 + 1) fRec50[l67] = 0.0;
	for (int l68 = 0; l68 < 2; l68 = l68 + 1) fRec67[l68] = 0.0;
	for (int l69 = 0; l69 < 3; l69 = l69 + 1) fRec66[l69] = 0.0;
	for (int l70 = 0; l70 < 3; l70 = l70 + 1) fRec65[l70] = 0.0;
	for (int l71 = 0; l71 < 3; l71 = l71 + 1) fRec64[l71] = 0.0;
	for (int l72 = 0; l72 < 3; l72 = l72 + 1) fRec63[l72] = 0.0;
	for (int l73 = 0; l73 < 3; l73 = l73 + 1) fRec62[l73] = 0.0;
	for (int l74 = 0; l74 < 3; l74 = l74 + 1) fRec61[l74] = 0.0;
	for (int l75 = 0; l75 < 2; l75 = l75 + 1) fRec68[l75] = 0.0;
	for (int l76 = 0; l76 < 2; l76 = l76 + 1) fRec58[l76] = 0.0;
	for (int l77 = 0; l77 < 2; l77 = l77 + 1) iRec59[l77] = 0;
	for (int l78 = 0; l78 < 2; l78 = l78 + 1) fRec60[l78] = 0.0;
	for (int l79 = 0; l79 < 2; l79 = l79 + 1) fRec79[l79] = 0.0;
	for (int l80 = 0; l80 < 3; l80 = l80 + 1) fRec78[l80] = 0.0;
	for (int l81 = 0; l81 < 3; l81 = l81 + 1) fRec77[l81] = 0.0;
	for (int l82 = 0; l82 < 3; l82 = l82 + 1) fRec76[l82] = 0.0;
	for (int l83 = 0; l83 < 3; l83 = l83 + 1) fRec75[l83] = 0.0;
	for (int l84 = 0; l84 < 3; l84 = l84 + 1) fRec74[l84] = 0.0;
	for (int l85 = 0; l85 < 3; l85 = l85 + 1) fRec73[l85] = 0.0;
	for (int l86 = 0; l86 < 3; l86 = l86 + 1) fRec72[l86] = 0.0;
	for (int l87 = 0; l87 < 2; l87 = l87 + 1) fRec80[l87] = 0.0;
	for (int l88 = 0; l88 < 2; l88 = l88 + 1) fRec69[l88] = 0.0;
	for (int l89 = 0; l89 < 2; l89 = l89 + 1) iRec70[l89] = 0;
	for (int l90 = 0; l90 < 2; l90 = l90 + 1) fRec71[l90] = 0.0;
	for (int l91 = 0; l91 < 2; l91 = l91 + 1) fRec92[l91] = 0.0;
	for (int l92 = 0; l92 < 3; l92 = l92 + 1) fRec91[l92] = 0.0;
	for (int l93 = 0; l93 < 3; l93 = l93 + 1) fRec90[l93] = 0.0;
	for (int l94 = 0; l94 < 3; l94 = l94 + 1) fRec89[l94] = 0.0;
	for (int l95 = 0; l95 < 3; l95 = l95 + 1) fRec88[l95] = 0.0;
	for (int l96 = 0; l96 < 3; l96 = l96 + 1) fRec87[l96] = 0.0;
	for (int l97 = 0; l97 < 3; l97 = l97 + 1) fRec86[l97] = 0.0;
	for (int l98 = 0; l98 < 3; l98 = l98 + 1) fRec85[l98] = 0.0;
	for (int l99 = 0; l99 < 3; l99 = l99 + 1) fRec84[l99] = 0.0;
	for (int l100 = 0; l100 < 2; l100 = l100 + 1) fRec93[l100] = 0.0;
	for (int l101 = 0; l101 < 2; l101 = l101 + 1) fRec81[l101] = 0.0;
	for (int l102 = 0; l102 < 2; l102 = l102 + 1) iRec82[l102] = 0;
	for (int l103 = 0; l103 < 2; l103 = l103 + 1) fRec83[l103] = 0.0;
	for (int l104 = 0; l104 < 2; l104 = l104 + 1) fRec106[l104] = 0.0;
	for (int l105 = 0; l105 < 3; l105 = l105 + 1) fRec105[l105] = 0.0;
	for (int l106 = 0; l106 < 3; l106 = l106 + 1) fRec104[l106] = 0.0;
	for (int l107 = 0; l107 < 3; l107 = l107 + 1) fRec103[l107] = 0.0;
	for (int l108 = 0; l108 < 3; l108 = l108 + 1) fRec102[l108] = 0.0;
	for (int l109 = 0; l109 < 3; l109 = l109 + 1) fRec101[l109] = 0.0;
	for (int l110 = 0; l110 < 3; l110 = l110 + 1) fRec100[l110] = 0.0;
	for (int l111 = 0; l111 < 3; l111 = l111 + 1) fRec99[l111] = 0.0;
	for (int l112 = 0; l112 < 3; l112 = l112 + 1) fRec98[l112] = 0.0;
	for (int l113 = 0; l113 < 3; l113 = l113 + 1) fRec97[l113] = 0.0;
	for (int l114 = 0; l114 < 2; l114 = l114 + 1) fRec107[l114] = 0.0;
	for (int l115 = 0; l115 < 2; l115 = l115 + 1) fRec94[l115] = 0.0;
	for (int l116 = 0; l116 < 2; l116 = l116 + 1) iRec95[l116] = 0;
	for (int l117 = 0; l117 < 2; l117 = l117 + 1) fRec96[l117] = 0.0;
	for (int l118 = 0; l118 < 2; l118 = l118 + 1) fRec121[l118] = 0.0;
	for (int l119 = 0; l119 < 3; l119 = l119 + 1) fRec120[l119] = 0.0;
	for (int l120 = 0; l120 < 3; l120 = l120 + 1) fRec119[l120] = 0.0;
	for (int l121 = 0; l121 < 3; l121 = l121 + 1) fRec118[l121] = 0.0;
	for (int l122 = 0; l122 < 3; l122 = l122 + 1) fRec117[l122] = 0.0;
	for (int l123 = 0; l123 < 3; l123 = l123 + 1) fRec116[l123] = 0.0;
	for (int l124 = 0; l124 < 3; l124 = l124 + 1) fRec115[l124] = 0.0;
	for (int l125 = 0; l125 < 3; l125 = l125 + 1) fRec114[l125] = 0.0;
	for (int l126 = 0; l126 < 3; l126 = l126 + 1) fRec113[l126] = 0.0;
	for (int l127 = 0; l127 < 3; l127 = l127 + 1) fRec112[l127] = 0.0;
	for (int l128 = 0; l128 < 3; l128 = l128 + 1) fRec111[l128] = 0.0;
	for (int l129 = 0; l129 < 2; l129 = l129 + 1) fRec122[l129] = 0.0;
	for (int l130 = 0; l130 < 2; l130 = l130 + 1) fRec108[l130] = 0.0;
	for (int l131 = 0; l131 < 2; l131 = l131 + 1) iRec109[l131] = 0;
	for (int l132 = 0; l132 < 2; l132 = l132 + 1) fRec110[l132] = 0.0;
	for (int l133 = 0; l133 < 2; l133 = l133 + 1) fRec127[l133] = 0.0;
	for (int l134 = 0; l134 < 3; l134 = l134 + 1) fRec126[l134] = 0.0;
	for (int l135 = 0; l135 < 2; l135 = l135 + 1) fRec128[l135] = 0.0;
	for (int l136 = 0; l136 < 2; l136 = l136 + 1) fRec123[l136] = 0.0;
	for (int l137 = 0; l137 < 2; l137 = l137 + 1) iRec124[l137] = 0;
	for (int l138 = 0; l138 < 2; l138 = l138 + 1) fRec125[l138] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 1.0 / fConst0;
	double fConst2 = std::tan(138.23007675795088 / fConst0);
	double fConst3 = mydsp_faustpower2_f(fConst2);
	fConst4 = 2.0 * (1.0 - 1.0 / fConst3);
	double fConst5 = 1.0 / fConst2;
	fConst6 = (fConst5 + -1.0000000000000004) / fConst2 + 1.0;
	double fConst7 = (fConst5 + 1.0000000000000004) / fConst2 + 1.0;
	fConst8 = 1.0 / fConst7;
	double fConst9 = std::tan(276.46015351590177 / fConst0);
	double fConst10 = mydsp_faustpower2_f(fConst9);
	fConst11 = 2.0 * (1.0 - 1.0 / fConst10);
	double fConst12 = 1.0 / fConst9;
	fConst13 = (fConst12 + -1.0000000000000004) / fConst9 + 1.0;
	double fConst14 = (fConst12 + 1.0000000000000004) / fConst9 + 1.0;
	fConst15 = 1.0 / fConst14;
	double fConst16 = std::tan(556.0618996853934 / fConst0);
	double fConst17 = mydsp_faustpower2_f(fConst16);
	fConst18 = 2.0 * (1.0 - 1.0 / fConst17);
	double fConst19 = 1.0 / fConst16;
	fConst20 = (fConst19 + -1.0000000000000004) / fConst16 + 1.0;
	double fConst21 = (fConst19 + 1.0000000000000004) / fConst16 + 1.0;
	fConst22 = 1.0 / fConst21;
	double fConst23 = std::tan(1112.1237993707869 / fConst0);
	double fConst24 = mydsp_faustpower2_f(fConst23);
	fConst25 = 2.0 * (1.0 - 1.0 / fConst24);
	double fConst26 = 1.0 / fConst23;
	fConst27 = (fConst26 + -1.0000000000000004) / fConst23 + 1.0;
	double fConst28 = (fConst26 + 1.0000000000000004) / fConst23 + 1.0;
	fConst29 = 1.0 / fConst28;
	double fConst30 = std::tan(2221.1060060879836 / fConst0);
	double fConst31 = mydsp_faustpower2_f(fConst30);
	fConst32 = 2.0 * (1.0 - 1.0 / fConst31);
	double fConst33 = 1.0 / fConst30;
	fConst34 = (fConst33 + -1.0000000000000004) / fConst30 + 1.0;
	double fConst35 = (fConst33 + 1.0000000000000004) / fConst30 + 1.0;
	fConst36 = 1.0 / fConst35;
	double fConst37 = std::tan(4442.212012175967 / fConst0);
	double fConst38 = mydsp_faustpower2_f(fConst37);
	fConst39 = 2.0 * (1.0 - 1.0 / fConst38);
	double fConst40 = 1.0 / fConst37;
	fConst41 = (fConst40 + -1.0000000000000004) / fConst37 + 1.0;
	double fConst42 = (fConst40 + 1.0000000000000004) / fConst37 + 1.0;
	fConst43 = 1.0 / fConst42;
	double fConst44 = std::tan(8884.424024351934 / fConst0);
	double fConst45 = mydsp_faustpower2_f(fConst44);
	fConst46 = 2.0 * (1.0 - 1.0 / fConst45);
	double fConst47 = 1.0 / fConst44;
	fConst48 = (fConst47 + -1.0000000000000004) / fConst44 + 1.0;
	double fConst49 = (fConst47 + 1.0000000000000004) / fConst44 + 1.0;
	fConst50 = 1.0 / fConst49;
	double fConst51 = std::tan(17771.98964135746 / fConst0);
	double fConst52 = mydsp_faustpower2_f(fConst51);
	fConst53 = 2.0 * (1.0 - 1.0 / fConst52);
	double fConst54 = 1.0 / fConst51;
	fConst55 = (fConst54 + -1.0000000000000004) / fConst51 + 1.0;
	double fConst56 = (fConst54 + 1.0000000000000004) / fConst51 + 1.0;
	fConst57 = 1.0 / fConst56;
	double fConst58 = std::tan(35763.890768466204 / fConst0);
	double fConst59 = mydsp_faustpower2_f(fConst58);
	fConst60 = 2.0 * (1.0 - 1.0 / fConst59);
	double fConst61 = 1.0 / fConst58;
	fConst62 = (fConst61 + -1.0000000000000004) / fConst58 + 1.0;
	double fConst63 = (fConst61 + 1.0000000000000004) / fConst58 + 1.0;
	fConst64 = 1.0 / fConst63;
	double fConst65 = std::tan(56894.24295651115 / fConst0);
	double fConst66 = mydsp_faustpower2_f(fConst65);
	fConst67 = 2.0 * (1.0 - 1.0 / fConst66);
	fConst68 = 1.0 / fConst65;
	fConst69 = (fConst68 + -1.0000000000000004) / fConst65 + 1.0;
	double fConst70 = (fConst68 + 1.0000000000000004) / fConst65 + 1.0;
	fConst71 = 1.0 / fConst70;
	fConst72 = 1.0 - fConst68;
	fConst73 = 1.0 / (fConst68 + 1.0);
	fConst74 = 1.0 - fConst61;
	double fConst75 = fConst61 + 1.0;
	fConst76 = 1.0 / fConst75;
	fConst77 = 1.0 - fConst54;
	double fConst78 = fConst54 + 1.0;
	fConst79 = 1.0 / fConst78;
	fConst80 = 1.0 - fConst47;
	double fConst81 = fConst47 + 1.0;
	fConst82 = 1.0 / fConst81;
	fConst83 = 1.0 - fConst40;
	double fConst84 = fConst40 + 1.0;
	fConst85 = 1.0 / fConst84;
	fConst86 = 1.0 - fConst33;
	double fConst87 = fConst33 + 1.0;
	fConst88 = 1.0 / fConst87;
	fConst89 = 1.0 - fConst26;
	double fConst90 = fConst26 + 1.0;
	fConst91 = 1.0 / fConst90;
	fConst92 = 1.0 - fConst19;
	double fConst93 = fConst19 + 1.0;
	fConst94 = 1.0 / fConst93;
	fConst95 = 1.0 - fConst12;
	double fConst96 = fConst12 + 1.0;
	fConst97 = 1.0 / fConst96;
	fConst98 = 1.0 - fConst5;
	double fConst99 = fConst5 + 1.0;
	fConst100 = 1.0 / fConst99;
	fConst101 = 1.0 - fConst98 / fConst2;
	fConst102 = 1.0 / (fConst99 / fConst2 + 1.0);
	fConst103 = 1.0 / (fConst9 * fConst21);
	fConst104 = 1.0 / (fConst10 * fConst14);
	fConst105 = 1.0 - fConst95 / fConst9;
	fConst106 = 1.0 / (fConst96 / fConst9 + 1.0);
	fConst107 = 1.0 / (fConst16 * fConst28);
	fConst108 = 1.0 / (fConst17 * fConst21);
	fConst109 = 1.0 - fConst92 / fConst16;
	fConst110 = 1.0 / (fConst93 / fConst16 + 1.0);
	fConst111 = 1.0 / (fConst23 * fConst35);
	fConst112 = 1.0 / (fConst24 * fConst28);
	fConst113 = 1.0 - fConst89 / fConst23;
	fConst114 = 1.0 / (fConst90 / fConst23 + 1.0);
	fConst115 = 1.0 / (fConst30 * fConst42);
	fConst116 = 1.0 / (fConst31 * fConst35);
	fConst117 = 1.0 - fConst86 / fConst30;
	fConst118 = 1.0 / (fConst87 / fConst30 + 1.0);
	fConst119 = 1.0 / (fConst37 * fConst49);
	fConst120 = 1.0 / (fConst38 * fConst42);
	fConst121 = 1.0 - fConst83 / fConst37;
	fConst122 = 1.0 / (fConst84 / fConst37 + 1.0);
	fConst123 = 1.0 / (fConst44 * fConst56);
	fConst124 = 1.0 / (fConst45 * fConst49);
	fConst125 = 1.0 - fConst80 / fConst44;
	fConst126 = 1.0 / (fConst81 / fConst44 + 1.0);
	fConst127 = 1.0 / (fConst51 * fConst63);
	fConst128 = 1.0 / (fConst52 * fConst56);
	fConst129 = 1.0 - fConst77 / fConst51;
	fConst130 = 1.0 / (fConst78 / fConst51 + 1.0);
	fConst131 = 1.0 / (fConst58 * fConst70);
	fConst132 = 1.0 / (fConst59 * fConst63);
	fConst133 = 1.0 - fConst74 / fConst58;
	fConst134 = 1.0 / (fConst75 / fConst58 + 1.0);
	fConst135 = 1.0 / (fConst66 * fConst70);
	fConst136 = 1.0 / (fConst2 * fConst14);
	fConst137 = 1.0 / (fConst3 * fConst7);
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
	double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider1));
	double fSlow2 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider2));
	double fSlow3 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider3));
	double fSlow4 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider4));
	double fSlow5 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider5));
	double fSlow6 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider6));
	double fSlow7 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider7));
	double fSlow8 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider8));
	double fSlow9 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider9));
	double fSlow10 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider10));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		int iTemp0 = iRec1[1] < 4096;
		double fTemp1 = double(input0[i0]);
		fVec0[0] = fTemp1;
		fRec22[0] = -(fConst73 * (fConst72 * fRec22[1] - (fTemp1 + fVec0[1])));
		fRec21[0] = fRec22[0] - fConst71 * (fConst69 * fRec21[2] + fConst67 * fRec21[1]);
		double fTemp2 = fRec21[2] + fRec21[0] + 2.0 * fRec21[1];
		fVec1[0] = fTemp2;
		fRec20[0] = -(fConst76 * (fConst74 * fRec20[1] - fConst71 * (fTemp2 + fVec1[1])));
		fRec19[0] = fRec20[0] - fConst64 * (fConst62 * fRec19[2] + fConst60 * fRec19[1]);
		double fTemp3 = fRec19[2] + fRec19[0] + 2.0 * fRec19[1];
		fVec2[0] = fTemp3;
		fRec18[0] = -(fConst79 * (fConst77 * fRec18[1] - fConst64 * (fTemp3 + fVec2[1])));
		fRec17[0] = fRec18[0] - fConst57 * (fConst55 * fRec17[2] + fConst53 * fRec17[1]);
		double fTemp4 = fRec17[2] + fRec17[0] + 2.0 * fRec17[1];
		fVec3[0] = fTemp4;
		fRec16[0] = -(fConst82 * (fConst80 * fRec16[1] - fConst57 * (fTemp4 + fVec3[1])));
		fRec15[0] = fRec16[0] - fConst50 * (fConst48 * fRec15[2] + fConst46 * fRec15[1]);
		double fTemp5 = fRec15[2] + fRec15[0] + 2.0 * fRec15[1];
		fVec4[0] = fTemp5;
		fRec14[0] = -(fConst85 * (fConst83 * fRec14[1] - fConst50 * (fTemp5 + fVec4[1])));
		fRec13[0] = fRec14[0] - fConst43 * (fConst41 * fRec13[2] + fConst39 * fRec13[1]);
		double fTemp6 = fRec13[2] + fRec13[0] + 2.0 * fRec13[1];
		fVec5[0] = fTemp6;
		fRec12[0] = -(fConst88 * (fConst86 * fRec12[1] - fConst43 * (fTemp6 + fVec5[1])));
		fRec11[0] = fRec12[0] - fConst36 * (fConst34 * fRec11[2] + fConst32 * fRec11[1]);
		double fTemp7 = fRec11[2] + fRec11[0] + 2.0 * fRec11[1];
		fVec6[0] = fTemp7;
		fRec10[0] = -(fConst91 * (fConst89 * fRec10[1] - fConst36 * (fTemp7 + fVec6[1])));
		fRec9[0] = fRec10[0] - fConst29 * (fConst27 * fRec9[2] + fConst25 * fRec9[1]);
		double fTemp8 = fRec9[2] + fRec9[0] + 2.0 * fRec9[1];
		fVec7[0] = fTemp8;
		fRec8[0] = -(fConst94 * (fConst92 * fRec8[1] - fConst29 * (fTemp8 + fVec7[1])));
		fRec7[0] = fRec8[0] - fConst22 * (fConst20 * fRec7[2] + fConst18 * fRec7[1]);
		double fTemp9 = fRec7[2] + fRec7[0] + 2.0 * fRec7[1];
		fVec8[0] = fTemp9;
		fRec6[0] = -(fConst97 * (fConst95 * fRec6[1] - fConst22 * (fTemp9 + fVec8[1])));
		fRec5[0] = fRec6[0] - fConst15 * (fConst13 * fRec5[2] + fConst11 * fRec5[1]);
		double fTemp10 = fRec5[2] + fRec5[0] + 2.0 * fRec5[1];
		fVec9[0] = fTemp10;
		fRec4[0] = -(fConst100 * (fConst98 * fRec4[1] - fConst15 * (fTemp10 + fVec9[1])));
		fRec3[0] = fRec4[0] - fConst8 * (fConst6 * fRec3[2] + fConst4 * fRec3[1]);
		fRec23[0] = fSlow0 + 0.999 * fRec23[1];
		double fTemp11 = fConst8 * fRec23[0] * (fRec3[2] + fRec3[0] + 2.0 * fRec3[1]);
		double fTemp12 = std::max<double>(fConst1, std::fabs(fTemp11));
		fRec0[0] = ((iTemp0) ? std::max<double>(fRec0[1], fTemp12) : fTemp12);
		iRec1[0] = ((iTemp0) ? iRec1[1] + 1 : 1);
		fRec2[0] = ((iTemp0) ? fRec2[1] : fRec0[1]);
		fVbargraph0 = FAUSTFLOAT(fRec2[0]);
		int iTemp13 = iRec25[1] < 4096;
		double fTemp14 = fConst4 * fRec27[1];
		fRec29[0] = -(fConst97 * (fConst95 * fRec29[1] - fConst103 * (fTemp9 - fVec8[1])));
		fRec28[0] = fRec29[0] - fConst15 * (fConst13 * fRec28[2] + fConst11 * fRec28[1]);
		fRec27[0] = fConst104 * (fRec28[2] + (fRec28[0] - 2.0 * fRec28[1])) - fConst102 * (fConst101 * fRec27[2] + fTemp14);
		fRec30[0] = fSlow1 + 0.999 * fRec30[1];
		double fTemp15 = fRec30[0] * (fRec27[2] + fConst102 * (fTemp14 + fConst101 * fRec27[0]));
		double fTemp16 = std::max<double>(fConst1, std::fabs(fTemp15));
		fRec24[0] = ((iTemp13) ? std::max<double>(fRec24[1], fTemp16) : fTemp16);
		iRec25[0] = ((iTemp13) ? iRec25[1] + 1 : 1);
		fRec26[0] = ((iTemp13) ? fRec26[1] : fRec24[1]);
		fVbargraph1 = FAUSTFLOAT(fRec26[0]);
		int iTemp17 = iRec32[1] < 4096;
		double fTemp18 = fConst4 * fRec34[1];
		double fTemp19 = fConst11 * fRec35[1];
		fRec37[0] = -(fConst94 * (fConst92 * fRec37[1] - fConst107 * (fTemp8 - fVec7[1])));
		fRec36[0] = fRec37[0] - fConst22 * (fConst20 * fRec36[2] + fConst18 * fRec36[1]);
		fRec35[0] = fConst108 * (fRec36[2] + (fRec36[0] - 2.0 * fRec36[1])) - fConst106 * (fConst105 * fRec35[2] + fTemp19);
		fRec34[0] = fRec35[2] + fConst106 * (fTemp19 + fConst105 * fRec35[0]) - fConst102 * (fConst101 * fRec34[2] + fTemp18);
		fRec38[0] = fSlow2 + 0.999 * fRec38[1];
		double fTemp20 = fRec38[0] * (fRec34[2] + fConst102 * (fTemp18 + fConst101 * fRec34[0]));
		double fTemp21 = std::max<double>(fConst1, std::fabs(fTemp20));
		fRec31[0] = ((iTemp17) ? std::max<double>(fRec31[1], fTemp21) : fTemp21);
		iRec32[0] = ((iTemp17) ? iRec32[1] + 1 : 1);
		fRec33[0] = ((iTemp17) ? fRec33[1] : fRec31[1]);
		fVbargraph2 = FAUSTFLOAT(fRec33[0]);
		int iTemp22 = iRec40[1] < 4096;
		double fTemp23 = fConst4 * fRec42[1];
		double fTemp24 = fConst11 * fRec43[1];
		double fTemp25 = fConst18 * fRec44[1];
		fRec46[0] = -(fConst91 * (fConst89 * fRec46[1] - fConst111 * (fTemp7 - fVec6[1])));
		fRec45[0] = fRec46[0] - fConst29 * (fConst27 * fRec45[2] + fConst25 * fRec45[1]);
		fRec44[0] = fConst112 * (fRec45[2] + (fRec45[0] - 2.0 * fRec45[1])) - fConst110 * (fConst109 * fRec44[2] + fTemp25);
		fRec43[0] = fRec44[2] + fConst110 * (fTemp25 + fConst109 * fRec44[0]) - fConst106 * (fConst105 * fRec43[2] + fTemp24);
		fRec42[0] = fRec43[2] + fConst106 * (fTemp24 + fConst105 * fRec43[0]) - fConst102 * (fConst101 * fRec42[2] + fTemp23);
		fRec47[0] = fSlow3 + 0.999 * fRec47[1];
		double fTemp26 = fRec47[0] * (fRec42[2] + fConst102 * (fTemp23 + fConst101 * fRec42[0]));
		double fTemp27 = std::max<double>(fConst1, std::fabs(fTemp26));
		fRec39[0] = ((iTemp22) ? std::max<double>(fRec39[1], fTemp27) : fTemp27);
		iRec40[0] = ((iTemp22) ? iRec40[1] + 1 : 1);
		fRec41[0] = ((iTemp22) ? fRec41[1] : fRec39[1]);
		fVbargraph3 = FAUSTFLOAT(fRec41[0]);
		int iTemp28 = iRec49[1] < 4096;
		double fTemp29 = fConst4 * fRec51[1];
		double fTemp30 = fConst11 * fRec52[1];
		double fTemp31 = fConst18 * fRec53[1];
		double fTemp32 = fConst25 * fRec54[1];
		fRec56[0] = -(fConst88 * (fConst86 * fRec56[1] - fConst115 * (fTemp6 - fVec5[1])));
		fRec55[0] = fRec56[0] - fConst36 * (fConst34 * fRec55[2] + fConst32 * fRec55[1]);
		fRec54[0] = fConst116 * (fRec55[2] + (fRec55[0] - 2.0 * fRec55[1])) - fConst114 * (fConst113 * fRec54[2] + fTemp32);
		fRec53[0] = fRec54[2] + fConst114 * (fTemp32 + fConst113 * fRec54[0]) - fConst110 * (fConst109 * fRec53[2] + fTemp31);
		fRec52[0] = fRec53[2] + fConst110 * (fTemp31 + fConst109 * fRec53[0]) - fConst106 * (fConst105 * fRec52[2] + fTemp30);
		fRec51[0] = fRec52[2] + fConst106 * (fTemp30 + fConst105 * fRec52[0]) - fConst102 * (fConst101 * fRec51[2] + fTemp29);
		fRec57[0] = fSlow4 + 0.999 * fRec57[1];
		double fTemp33 = fRec57[0] * (fRec51[2] + fConst102 * (fTemp29 + fConst101 * fRec51[0]));
		double fTemp34 = std::max<double>(fConst1, std::fabs(fTemp33));
		fRec48[0] = ((iTemp28) ? std::max<double>(fRec48[1], fTemp34) : fTemp34);
		iRec49[0] = ((iTemp28) ? iRec49[1] + 1 : 1);
		fRec50[0] = ((iTemp28) ? fRec50[1] : fRec48[1]);
		fVbargraph4 = FAUSTFLOAT(fRec50[0]);
		int iTemp35 = iRec59[1] < 4096;
		double fTemp36 = fConst4 * fRec61[1];
		double fTemp37 = fConst11 * fRec62[1];
		double fTemp38 = fConst18 * fRec63[1];
		double fTemp39 = fConst25 * fRec64[1];
		double fTemp40 = fConst32 * fRec65[1];
		fRec67[0] = -(fConst85 * (fConst83 * fRec67[1] - fConst119 * (fTemp5 - fVec4[1])));
		fRec66[0] = fRec67[0] - fConst43 * (fConst41 * fRec66[2] + fConst39 * fRec66[1]);
		fRec65[0] = fConst120 * (fRec66[2] + (fRec66[0] - 2.0 * fRec66[1])) - fConst118 * (fConst117 * fRec65[2] + fTemp40);
		fRec64[0] = fRec65[2] + fConst118 * (fTemp40 + fConst117 * fRec65[0]) - fConst114 * (fConst113 * fRec64[2] + fTemp39);
		fRec63[0] = fRec64[2] + fConst114 * (fTemp39 + fConst113 * fRec64[0]) - fConst110 * (fConst109 * fRec63[2] + fTemp38);
		fRec62[0] = fRec63[2] + fConst110 * (fTemp38 + fConst109 * fRec63[0]) - fConst106 * (fConst105 * fRec62[2] + fTemp37);
		fRec61[0] = fRec62[2] + fConst106 * (fTemp37 + fConst105 * fRec62[0]) - fConst102 * (fConst101 * fRec61[2] + fTemp36);
		fRec68[0] = fSlow5 + 0.999 * fRec68[1];
		double fTemp41 = fRec68[0] * (fRec61[2] + fConst102 * (fTemp36 + fConst101 * fRec61[0]));
		double fTemp42 = std::max<double>(fConst1, std::fabs(fTemp41));
		fRec58[0] = ((iTemp35) ? std::max<double>(fRec58[1], fTemp42) : fTemp42);
		iRec59[0] = ((iTemp35) ? iRec59[1] + 1 : 1);
		fRec60[0] = ((iTemp35) ? fRec60[1] : fRec58[1]);
		fVbargraph5 = FAUSTFLOAT(fRec60[0]);
		int iTemp43 = iRec70[1] < 4096;
		double fTemp44 = fConst4 * fRec72[1];
		double fTemp45 = fConst11 * fRec73[1];
		double fTemp46 = fConst18 * fRec74[1];
		double fTemp47 = fConst25 * fRec75[1];
		double fTemp48 = fConst32 * fRec76[1];
		double fTemp49 = fConst39 * fRec77[1];
		fRec79[0] = -(fConst82 * (fConst80 * fRec79[1] - fConst123 * (fTemp4 - fVec3[1])));
		fRec78[0] = fRec79[0] - fConst50 * (fConst48 * fRec78[2] + fConst46 * fRec78[1]);
		fRec77[0] = fConst124 * (fRec78[2] + (fRec78[0] - 2.0 * fRec78[1])) - fConst122 * (fConst121 * fRec77[2] + fTemp49);
		fRec76[0] = fRec77[2] + fConst122 * (fTemp49 + fConst121 * fRec77[0]) - fConst118 * (fConst117 * fRec76[2] + fTemp48);
		fRec75[0] = fRec76[2] + fConst118 * (fTemp48 + fConst117 * fRec76[0]) - fConst114 * (fConst113 * fRec75[2] + fTemp47);
		fRec74[0] = fRec75[2] + fConst114 * (fTemp47 + fConst113 * fRec75[0]) - fConst110 * (fConst109 * fRec74[2] + fTemp46);
		fRec73[0] = fRec74[2] + fConst110 * (fTemp46 + fConst109 * fRec74[0]) - fConst106 * (fConst105 * fRec73[2] + fTemp45);
		fRec72[0] = fRec73[2] + fConst106 * (fTemp45 + fConst105 * fRec73[0]) - fConst102 * (fConst101 * fRec72[2] + fTemp44);
		fRec80[0] = fSlow6 + 0.999 * fRec80[1];
		double fTemp50 = fRec80[0] * (fRec72[2] + fConst102 * (fTemp44 + fConst101 * fRec72[0]));
		double fTemp51 = std::max<double>(fConst1, std::fabs(fTemp50));
		fRec69[0] = ((iTemp43) ? std::max<double>(fRec69[1], fTemp51) : fTemp51);
		iRec70[0] = ((iTemp43) ? iRec70[1] + 1 : 1);
		fRec71[0] = ((iTemp43) ? fRec71[1] : fRec69[1]);
		fVbargraph6 = FAUSTFLOAT(fRec71[0]);
		int iTemp52 = iRec82[1] < 4096;
		double fTemp53 = fConst4 * fRec84[1];
		double fTemp54 = fConst11 * fRec85[1];
		double fTemp55 = fConst18 * fRec86[1];
		double fTemp56 = fConst25 * fRec87[1];
		double fTemp57 = fConst32 * fRec88[1];
		double fTemp58 = fConst39 * fRec89[1];
		double fTemp59 = fConst46 * fRec90[1];
		fRec92[0] = -(fConst79 * (fConst77 * fRec92[1] - fConst127 * (fTemp3 - fVec2[1])));
		fRec91[0] = fRec92[0] - fConst57 * (fConst55 * fRec91[2] + fConst53 * fRec91[1]);
		fRec90[0] = fConst128 * (fRec91[2] + (fRec91[0] - 2.0 * fRec91[1])) - fConst126 * (fConst125 * fRec90[2] + fTemp59);
		fRec89[0] = fRec90[2] + fConst126 * (fTemp59 + fConst125 * fRec90[0]) - fConst122 * (fConst121 * fRec89[2] + fTemp58);
		fRec88[0] = fRec89[2] + fConst122 * (fTemp58 + fConst121 * fRec89[0]) - fConst118 * (fConst117 * fRec88[2] + fTemp57);
		fRec87[0] = fRec88[2] + fConst118 * (fTemp57 + fConst117 * fRec88[0]) - fConst114 * (fConst113 * fRec87[2] + fTemp56);
		fRec86[0] = fRec87[2] + fConst114 * (fTemp56 + fConst113 * fRec87[0]) - fConst110 * (fConst109 * fRec86[2] + fTemp55);
		fRec85[0] = fRec86[2] + fConst110 * (fTemp55 + fConst109 * fRec86[0]) - fConst106 * (fConst105 * fRec85[2] + fTemp54);
		fRec84[0] = fRec85[2] + fConst106 * (fTemp54 + fConst105 * fRec85[0]) - fConst102 * (fConst101 * fRec84[2] + fTemp53);
		fRec93[0] = fSlow7 + 0.999 * fRec93[1];
		double fTemp60 = fRec93[0] * (fRec84[2] + fConst102 * (fTemp53 + fConst101 * fRec84[0]));
		double fTemp61 = std::max<double>(fConst1, std::fabs(fTemp60));
		fRec81[0] = ((iTemp52) ? std::max<double>(fRec81[1], fTemp61) : fTemp61);
		iRec82[0] = ((iTemp52) ? iRec82[1] + 1 : 1);
		fRec83[0] = ((iTemp52) ? fRec83[1] : fRec81[1]);
		fVbargraph7 = FAUSTFLOAT(fRec83[0]);
		int iTemp62 = iRec95[1] < 4096;
		double fTemp63 = fConst4 * fRec97[1];
		double fTemp64 = fConst11 * fRec98[1];
		double fTemp65 = fConst18 * fRec99[1];
		double fTemp66 = fConst25 * fRec100[1];
		double fTemp67 = fConst32 * fRec101[1];
		double fTemp68 = fConst39 * fRec102[1];
		double fTemp69 = fConst46 * fRec103[1];
		double fTemp70 = fConst53 * fRec104[1];
		fRec106[0] = -(fConst76 * (fConst74 * fRec106[1] - fConst131 * (fTemp2 - fVec1[1])));
		fRec105[0] = fRec106[0] - fConst64 * (fConst62 * fRec105[2] + fConst60 * fRec105[1]);
		fRec104[0] = fConst132 * (fRec105[2] + (fRec105[0] - 2.0 * fRec105[1])) - fConst130 * (fConst129 * fRec104[2] + fTemp70);
		fRec103[0] = fRec104[2] + fConst130 * (fTemp70 + fConst129 * fRec104[0]) - fConst126 * (fConst125 * fRec103[2] + fTemp69);
		fRec102[0] = fRec103[2] + fConst126 * (fTemp69 + fConst125 * fRec103[0]) - fConst122 * (fConst121 * fRec102[2] + fTemp68);
		fRec101[0] = fRec102[2] + fConst122 * (fTemp68 + fConst121 * fRec102[0]) - fConst118 * (fConst117 * fRec101[2] + fTemp67);
		fRec100[0] = fRec101[2] + fConst118 * (fTemp67 + fConst117 * fRec101[0]) - fConst114 * (fConst113 * fRec100[2] + fTemp66);
		fRec99[0] = fRec100[2] + fConst114 * (fTemp66 + fConst113 * fRec100[0]) - fConst110 * (fConst109 * fRec99[2] + fTemp65);
		fRec98[0] = fRec99[2] + fConst110 * (fTemp65 + fConst109 * fRec99[0]) - fConst106 * (fConst105 * fRec98[2] + fTemp64);
		fRec97[0] = fRec98[2] + fConst106 * (fTemp64 + fConst105 * fRec98[0]) - fConst102 * (fConst101 * fRec97[2] + fTemp63);
		fRec107[0] = fSlow8 + 0.999 * fRec107[1];
		double fTemp71 = fRec107[0] * (fRec97[2] + fConst102 * (fTemp63 + fConst101 * fRec97[0]));
		double fTemp72 = std::max<double>(fConst1, std::fabs(fTemp71));
		fRec94[0] = ((iTemp62) ? std::max<double>(fRec94[1], fTemp72) : fTemp72);
		iRec95[0] = ((iTemp62) ? iRec95[1] + 1 : 1);
		fRec96[0] = ((iTemp62) ? fRec96[1] : fRec94[1]);
		fVbargraph8 = FAUSTFLOAT(fRec96[0]);
		int iTemp73 = iRec109[1] < 4096;
		double fTemp74 = fConst4 * fRec111[1];
		double fTemp75 = fConst11 * fRec112[1];
		double fTemp76 = fConst18 * fRec113[1];
		double fTemp77 = fConst25 * fRec114[1];
		double fTemp78 = fConst32 * fRec115[1];
		double fTemp79 = fConst39 * fRec116[1];
		double fTemp80 = fConst46 * fRec117[1];
		double fTemp81 = fConst53 * fRec118[1];
		double fTemp82 = fConst60 * fRec119[1];
		fRec121[0] = -(fConst73 * (fConst72 * fRec121[1] - fConst68 * (fTemp1 - fVec0[1])));
		fRec120[0] = fRec121[0] - fConst71 * (fConst69 * fRec120[2] + fConst67 * fRec120[1]);
		fRec119[0] = fConst135 * (fRec120[2] + (fRec120[0] - 2.0 * fRec120[1])) - fConst134 * (fConst133 * fRec119[2] + fTemp82);
		fRec118[0] = fRec119[2] + fConst134 * (fTemp82 + fConst133 * fRec119[0]) - fConst130 * (fConst129 * fRec118[2] + fTemp81);
		fRec117[0] = fRec118[2] + fConst130 * (fTemp81 + fConst129 * fRec118[0]) - fConst126 * (fConst125 * fRec117[2] + fTemp80);
		fRec116[0] = fRec117[2] + fConst126 * (fTemp80 + fConst125 * fRec117[0]) - fConst122 * (fConst121 * fRec116[2] + fTemp79);
		fRec115[0] = fRec116[2] + fConst122 * (fTemp79 + fConst121 * fRec116[0]) - fConst118 * (fConst117 * fRec115[2] + fTemp78);
		fRec114[0] = fRec115[2] + fConst118 * (fTemp78 + fConst117 * fRec115[0]) - fConst114 * (fConst113 * fRec114[2] + fTemp77);
		fRec113[0] = fRec114[2] + fConst114 * (fTemp77 + fConst113 * fRec114[0]) - fConst110 * (fConst109 * fRec113[2] + fTemp76);
		fRec112[0] = fRec113[2] + fConst110 * (fTemp76 + fConst109 * fRec113[0]) - fConst106 * (fConst105 * fRec112[2] + fTemp75);
		fRec111[0] = fRec112[2] + fConst106 * (fTemp75 + fConst105 * fRec112[0]) - fConst102 * (fConst101 * fRec111[2] + fTemp74);
		fRec122[0] = fSlow9 + 0.999 * fRec122[1];
		double fTemp83 = fRec122[0] * (fRec111[2] + fConst102 * (fTemp74 + fConst101 * fRec111[0]));
		double fTemp84 = std::max<double>(fConst1, std::fabs(fTemp83));
		fRec108[0] = ((iTemp73) ? std::max<double>(fRec108[1], fTemp84) : fTemp84);
		iRec109[0] = ((iTemp73) ? iRec109[1] + 1 : 1);
		fRec110[0] = ((iTemp73) ? fRec110[1] : fRec108[1]);
		fVbargraph9 = FAUSTFLOAT(fRec110[0]);
		int iTemp85 = iRec124[1] < 4096;
		fRec127[0] = -(fConst100 * (fConst98 * fRec127[1] - fConst136 * (fTemp10 - fVec9[1])));
		fRec126[0] = fRec127[0] - fConst8 * (fConst6 * fRec126[2] + fConst4 * fRec126[1]);
		double fTemp86 = 2.0 * fRec126[1];
		fRec128[0] = fSlow10 + 0.999 * fRec128[1];
		double fTemp87 = std::max<double>(fConst1, std::fabs(fConst137 * fRec128[0] * (fRec126[2] + (fRec126[0] - fTemp86))));
		fRec123[0] = ((iTemp85) ? std::max<double>(fRec123[1], fTemp87) : fTemp87);
		iRec124[0] = ((iTemp85) ? iRec124[1] + 1 : 1);
		fRec125[0] = ((iTemp85) ? fRec125[1] : fRec123[1]);
		fVbargraph10 = FAUSTFLOAT(fRec125[0]);
		output0[i0] = FAUSTFLOAT(fConst137 * fRec128[0] * (fRec126[0] + fRec126[2] - fTemp86) + fTemp83 + fTemp71 + fTemp60 + fTemp50 + fTemp41 + fTemp33 + fTemp26 + fTemp20 + fTemp15 + fTemp11);
		fVec0[1] = fVec0[0];
		fRec22[1] = fRec22[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		fVec1[1] = fVec1[0];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fVec2[1] = fVec2[0];
		fRec18[1] = fRec18[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fVec3[1] = fVec3[0];
		fRec16[1] = fRec16[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		fVec4[1] = fVec4[0];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fVec5[1] = fVec5[0];
		fRec12[1] = fRec12[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fVec6[1] = fVec6[0];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fVec7[1] = fVec7[0];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fVec8[1] = fVec8[0];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fVec9[1] = fVec9[0];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec23[1] = fRec23[0];
		fRec0[1] = fRec0[0];
		iRec1[1] = iRec1[0];
		fRec2[1] = fRec2[0];
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		fRec30[1] = fRec30[0];
		fRec24[1] = fRec24[0];
		iRec25[1] = iRec25[0];
		fRec26[1] = fRec26[0];
		fRec37[1] = fRec37[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		fRec35[2] = fRec35[1];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec38[1] = fRec38[0];
		fRec31[1] = fRec31[0];
		iRec32[1] = iRec32[0];
		fRec33[1] = fRec33[0];
		fRec46[1] = fRec46[0];
		fRec45[2] = fRec45[1];
		fRec45[1] = fRec45[0];
		fRec44[2] = fRec44[1];
		fRec44[1] = fRec44[0];
		fRec43[2] = fRec43[1];
		fRec43[1] = fRec43[0];
		fRec42[2] = fRec42[1];
		fRec42[1] = fRec42[0];
		fRec47[1] = fRec47[0];
		fRec39[1] = fRec39[0];
		iRec40[1] = iRec40[0];
		fRec41[1] = fRec41[0];
		fRec56[1] = fRec56[0];
		fRec55[2] = fRec55[1];
		fRec55[1] = fRec55[0];
		fRec54[2] = fRec54[1];
		fRec54[1] = fRec54[0];
		fRec53[2] = fRec53[1];
		fRec53[1] = fRec53[0];
		fRec52[2] = fRec52[1];
		fRec52[1] = fRec52[0];
		fRec51[2] = fRec51[1];
		fRec51[1] = fRec51[0];
		fRec57[1] = fRec57[0];
		fRec48[1] = fRec48[0];
		iRec49[1] = iRec49[0];
		fRec50[1] = fRec50[0];
		fRec67[1] = fRec67[0];
		fRec66[2] = fRec66[1];
		fRec66[1] = fRec66[0];
		fRec65[2] = fRec65[1];
		fRec65[1] = fRec65[0];
		fRec64[2] = fRec64[1];
		fRec64[1] = fRec64[0];
		fRec63[2] = fRec63[1];
		fRec63[1] = fRec63[0];
		fRec62[2] = fRec62[1];
		fRec62[1] = fRec62[0];
		fRec61[2] = fRec61[1];
		fRec61[1] = fRec61[0];
		fRec68[1] = fRec68[0];
		fRec58[1] = fRec58[0];
		iRec59[1] = iRec59[0];
		fRec60[1] = fRec60[0];
		fRec79[1] = fRec79[0];
		fRec78[2] = fRec78[1];
		fRec78[1] = fRec78[0];
		fRec77[2] = fRec77[1];
		fRec77[1] = fRec77[0];
		fRec76[2] = fRec76[1];
		fRec76[1] = fRec76[0];
		fRec75[2] = fRec75[1];
		fRec75[1] = fRec75[0];
		fRec74[2] = fRec74[1];
		fRec74[1] = fRec74[0];
		fRec73[2] = fRec73[1];
		fRec73[1] = fRec73[0];
		fRec72[2] = fRec72[1];
		fRec72[1] = fRec72[0];
		fRec80[1] = fRec80[0];
		fRec69[1] = fRec69[0];
		iRec70[1] = iRec70[0];
		fRec71[1] = fRec71[0];
		fRec92[1] = fRec92[0];
		fRec91[2] = fRec91[1];
		fRec91[1] = fRec91[0];
		fRec90[2] = fRec90[1];
		fRec90[1] = fRec90[0];
		fRec89[2] = fRec89[1];
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
		fRec93[1] = fRec93[0];
		fRec81[1] = fRec81[0];
		iRec82[1] = iRec82[0];
		fRec83[1] = fRec83[0];
		fRec106[1] = fRec106[0];
		fRec105[2] = fRec105[1];
		fRec105[1] = fRec105[0];
		fRec104[2] = fRec104[1];
		fRec104[1] = fRec104[0];
		fRec103[2] = fRec103[1];
		fRec103[1] = fRec103[0];
		fRec102[2] = fRec102[1];
		fRec102[1] = fRec102[0];
		fRec101[2] = fRec101[1];
		fRec101[1] = fRec101[0];
		fRec100[2] = fRec100[1];
		fRec100[1] = fRec100[0];
		fRec99[2] = fRec99[1];
		fRec99[1] = fRec99[0];
		fRec98[2] = fRec98[1];
		fRec98[1] = fRec98[0];
		fRec97[2] = fRec97[1];
		fRec97[1] = fRec97[0];
		fRec107[1] = fRec107[0];
		fRec94[1] = fRec94[0];
		iRec95[1] = iRec95[0];
		fRec96[1] = fRec96[0];
		fRec121[1] = fRec121[0];
		fRec120[2] = fRec120[1];
		fRec120[1] = fRec120[0];
		fRec119[2] = fRec119[1];
		fRec119[1] = fRec119[0];
		fRec118[2] = fRec118[1];
		fRec118[1] = fRec118[0];
		fRec117[2] = fRec117[1];
		fRec117[1] = fRec117[0];
		fRec116[2] = fRec116[1];
		fRec116[1] = fRec116[0];
		fRec115[2] = fRec115[1];
		fRec115[1] = fRec115[0];
		fRec114[2] = fRec114[1];
		fRec114[1] = fRec114[0];
		fRec113[2] = fRec113[1];
		fRec113[1] = fRec113[0];
		fRec112[2] = fRec112[1];
		fRec112[1] = fRec112[0];
		fRec111[2] = fRec111[1];
		fRec111[1] = fRec111[0];
		fRec122[1] = fRec122[0];
		fRec108[1] = fRec108[0];
		iRec109[1] = iRec109[0];
		fRec110[1] = fRec110[0];
		fRec127[1] = fRec127[0];
		fRec126[2] = fRec126[1];
		fRec126[1] = fRec126[0];
		fRec128[1] = fRec128[0];
		fRec123[1] = fRec123[0];
		iRec124[1] = iRec124[0];
		fRec125[1] = fRec125[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("graphiceq.g10","","S",N_("gain (dB) at 16 kHz"),&fVslider8, 0.0, -3e+01, 2e+01, 0.1, 0);
	reg.registerFloatVar("graphiceq.g11","","S",N_("gain (dB) above 16 kHz"),&fVslider9, 0.0, -3e+01, 2e+01, 0.1, 0);
	reg.registerFloatVar("graphiceq.g1","","S",N_("gain (dB) below 31.25 Hz"),&fVslider0, 0.0, -3e+01, 2e+01, 0.1, 0);
	reg.registerFloatVar("graphiceq.g2","","S",N_("gain (dB) at 62.5 Hz"),&fVslider10, 0.0, -3e+01, 2e+01, 0.1, 0);
	reg.registerFloatVar("graphiceq.g3","","S",N_("gain (dB) at 125 Hz"),&fVslider1, 0.0, -3e+01, 2e+01, 0.1, 0);
	reg.registerFloatVar("graphiceq.g4","","S",N_("gain (dB) at 250 Hz"),&fVslider2, 0.0, -3e+01, 2e+01, 0.1, 0);
	reg.registerFloatVar("graphiceq.g5","","S",N_("gain (dB) at 500 Hz"),&fVslider3, 0.0, -3e+01, 2e+01, 0.1, 0);
	reg.registerFloatVar("graphiceq.g6","","S",N_("gain (dB) at 1 kHz"),&fVslider4, 0.0, -3e+01, 2e+01, 0.1, 0);
	reg.registerFloatVar("graphiceq.g7","","S",N_("gain (dB) at 2 kHz"),&fVslider5, 0.0, -3e+01, 2e+01, 0.1, 0);
	reg.registerFloatVar("graphiceq.g8","","S",N_("gain (dB) at 4 kHz"),&fVslider6, 0.0, -3e+01, 2e+01, 0.1, 0);
	reg.registerFloatVar("graphiceq.g9","","S",N_("gain (dB) at 8 kHz"),&fVslider7, 0.0, -3e+01, 2e+01, 0.1, 0);
	reg.registerFloatVar("graphiceq.v10","","SOLN","",&fVbargraph8, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("graphiceq.v11","","SOLN","",&fVbargraph9, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("graphiceq.v1","","SOLN","",&fVbargraph0, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("graphiceq.v2","","SOLN","",&fVbargraph10, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("graphiceq.v3","","SOLN","",&fVbargraph1, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("graphiceq.v4","","SOLN","",&fVbargraph2, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("graphiceq.v5","","SOLN","",&fVbargraph3, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("graphiceq.v6","","SOLN","",&fVbargraph4, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("graphiceq.v7","","SOLN","",&fVbargraph5, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("graphiceq.v8","","SOLN","",&fVbargraph6, 0, -7e+01, 5.0, 0, 0);
	reg.registerFloatVar("graphiceq.v9","","SOLN","",&fVbargraph7, 0, -7e+01, 5.0, 0, 0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!-- Generated with glade 3.22.1 -->\n\
<interface>\n\
  <requires lib=\"gtk+\" version=\"3.20\"/>\n\
  <requires lib=\"gxwidgets\" version=\"0.0\"/>\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can_focus\">False</property>\n\
    <child>\n\
      <placeholder/>\n\
    </child>\n\
    <child>\n\
      <object class=\"GtkBox\" id=\"vbox1\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can_focus\">False</property>\n\
        <property name=\"orientation\">vertical</property>\n\
        <child>\n\
          <object class=\"GxPaintBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <property name=\"paint_func\">box_uni_2_expose</property>\n\
            <child>\n\
              <object class=\"GtkBox\" id=\"hbox1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">4</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label1:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">&lt; 31</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter1\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"halign\">end</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v1</property>\n\
                            <property name=\"falloff\">True</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxVSlider\" id=\"gxvslider1\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">graphiceq.g1</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <style>\n\
                      <class name=\"metered-slider\"/>\n\
                    </style>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">4</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label2:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">62</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter2\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"halign\">end</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v2</property>\n\
                            <property name=\"falloff\">True</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxVSlider\" id=\"gxvslider2\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">graphiceq.g2</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <style>\n\
                      <class name=\"metered-slider\"/>\n\
                    </style>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">4</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label3:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">125</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox4\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter3\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"halign\">end</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v3</property>\n\
                            <property name=\"falloff\">True</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxVSlider\" id=\"gxvslider3\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">graphiceq.g3</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <style>\n\
                      <class name=\"metered-slider\"/>\n\
                    </style>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox5\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">4</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label4:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">250</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox5\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter4\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"halign\">end</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v4</property>\n\
                            <property name=\"falloff\">True</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxVSlider\" id=\"gxvslider4\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">graphiceq.g4</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <style>\n\
                      <class name=\"metered-slider\"/>\n\
                    </style>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">3</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox6\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">4</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label5:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">500</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox6\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter5\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"halign\">end</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v5</property>\n\
                            <property name=\"falloff\">True</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxVSlider\" id=\"gxvslider5\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">graphiceq.g5</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <style>\n\
                      <class name=\"metered-slider\"/>\n\
                    </style>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">4</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox7\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">4</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label6:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">1k</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox7\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter6\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"halign\">end</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v6</property>\n\
                            <property name=\"falloff\">True</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxVSlider\" id=\"gxvslider6\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">graphiceq.g6</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <style>\n\
                      <class name=\"metered-slider\"/>\n\
                    </style>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">5</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox8\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">4</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label7:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">2k</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox8\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter7\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"halign\">end</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v7</property>\n\
                            <property name=\"falloff\">True</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxVSlider\" id=\"gxvslider7\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">graphiceq.g7</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <style>\n\
                      <class name=\"metered-slider\"/>\n\
                    </style>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">6</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox9\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">4</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label8:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">4k</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox9\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter8\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"halign\">end</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v8</property>\n\
                            <property name=\"falloff\">True</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxVSlider\" id=\"gxvslider8\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">graphiceq.g8</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <style>\n\
                      <class name=\"metered-slider\"/>\n\
                    </style>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">7</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox10\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">4</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label9:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">8k</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox10\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter9\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"halign\">end</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v9</property>\n\
                            <property name=\"falloff\">True</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxVSlider\" id=\"gxvslider9\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">graphiceq.g9</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <style>\n\
                      <class name=\"metered-slider\"/>\n\
                    </style>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">8</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox11\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">4</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label10:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">16k</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox11\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter10\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"halign\">end</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v10</property>\n\
                            <property name=\"falloff\">True</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxVSlider\" id=\"gxvslider10\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">graphiceq.g10</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <style>\n\
                      <class name=\"metered-slider\"/>\n\
                    </style>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">9</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox12\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">4</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label11:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">&gt; 16k</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox12\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter11\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"halign\">end</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v11</property>\n\
                            <property name=\"falloff\">True</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxVSlider\" id=\"gxvslider11\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">graphiceq.g11</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <style>\n\
                      <class name=\"metered-slider\"/>\n\
                    </style>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">10</property>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"pack_type\">end</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">False</property>\n\
            <property name=\"position\">0</property>\n\
          </packing>\n\
        </child>\n\
        <child>\n\
          <object class=\"GtkBox\" id=\"minibox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <child>\n\
              <placeholder/>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">True</property>\n\
            <property name=\"position\">1</property>\n\
          </packing>\n\
        </child>\n\
      </object>\n\
    </child>\n\
  </object>\n\
</interface>\n\
";

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade(glade_def);
        return 0;
    }
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("graphiceq" "." p)
// ----- graphiceq
b.openHorizontalhideBox("");
b.closeBox();
b.openHorizontalBox("");
{
    b.openFrameBox("");
    b.closeBox();
    b.openHorizontalBox("");
    {
    b.create_simple_c_meter(PARAM("v1"), PARAM("g1"),"<31");
    }
    b.closeBox();
    b.openHorizontalBox("");
    {
    b.create_simple_c_meter(PARAM("v2"), PARAM("g2"),"62");
    }
    b.closeBox();
    b.openHorizontalBox("");
    {
    b.create_simple_c_meter(PARAM("v3"), PARAM("g3"),"125");
    }
    b.closeBox();
    b.openHorizontalBox("");
    {
    b.create_simple_c_meter(PARAM("v4"), PARAM("g4"),"250");
    }
    b.closeBox();
    b.openHorizontalBox("");
    {
    b.create_simple_c_meter(PARAM("v5"), PARAM("g5"),"500");
    }
    b.closeBox();
    b.openHorizontalBox("");
    {
    b.create_simple_c_meter(PARAM("v6"), PARAM("g6"),"1k");
    }
    b.closeBox();
    b.openHorizontalBox("");
    {
    b.create_simple_c_meter(PARAM("v7"), PARAM("g7"),"2k");
    }
    b.closeBox();
    b.openHorizontalBox("");
    {
    b.create_simple_c_meter(PARAM("v8"), PARAM("g8"),"4k");
    }
    b.closeBox();
    b.openHorizontalBox("");
    {
    b.create_simple_c_meter(PARAM("v9"), PARAM("g9"),"8k");
    }
    b.closeBox();
    b.openHorizontalBox("");
    {
    b.create_simple_c_meter(PARAM("v10"), PARAM("g10"),"16k");
    }
    b.closeBox();
    b.openHorizontalBox("");
    {
    b.create_simple_c_meter(PARAM("v11"), PARAM("g11"),"<");
    }
    b.closeBox();
    b.openFrameBox("");
    b.closeBox();
}
b.closeBox();

#undef PARAM
        return 0;
    }
	return -1;
}

int Dsp::load_ui_f_static(const UiBuilder& b, int form)
{
	return static_cast<Dsp*>(b.plugin)->load_ui_f(b, form);
}
PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace graphiceq
