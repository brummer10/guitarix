// generated from file '../src/faust/graphiceq.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace graphiceq {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider0;
	double fRec3[2];
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fVec0[2];
	double fConst9;
	double fConst10;
	double fRec14[2];
	double fConst11;
	double fConst12;
	double fRec13[3];
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
	double fRec12[3];
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fRec11[3];
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst40;
	double fRec10[3];
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fRec9[3];
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fRec8[3];
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst63;
	double fConst64;
	double fConst65;
	double fConst66;
	double fConst67;
	double fRec7[3];
	double fConst68;
	double fConst69;
	double fConst70;
	double fConst71;
	double fConst72;
	double fConst73;
	double fConst74;
	double fConst75;
	double fConst76;
	double fRec6[3];
	double fConst77;
	double fConst78;
	double fConst79;
	double fConst80;
	double fConst81;
	double fConst82;
	double fConst83;
	double fConst84;
	double fConst85;
	double fRec5[3];
	double fConst86;
	double fConst87;
	double fConst88;
	double fConst89;
	double fConst90;
	double fConst91;
	double fConst92;
	double fConst93;
	double fConst94;
	double fRec4[3];
	double fRec0[2];
	int iRec1[2];
	double fRec2[2];
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT fVslider1;
	double fRec18[2];
	double fConst95;
	double fConst96;
	double fRec30[2];
	double fRec29[3];
	double fVec1[2];
	double fConst97;
	double fConst98;
	double fRec28[2];
	double fConst99;
	double fRec27[3];
	double fConst100;
	double fRec26[3];
	double fRec25[3];
	double fRec24[3];
	double fRec23[3];
	double fRec22[3];
	double fRec21[3];
	double fRec20[3];
	double fRec19[3];
	double fRec15[2];
	int iRec16[2];
	double fRec17[2];
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT fVslider2;
	double fRec34[2];
	double fConst101;
	double fConst102;
	double fConst103;
	double fRec45[2];
	double fRec44[3];
	double fVec2[2];
	double fConst104;
	double fConst105;
	double fRec43[2];
	double fConst106;
	double fRec42[3];
	double fConst107;
	double fRec41[3];
	double fRec40[3];
	double fRec39[3];
	double fRec38[3];
	double fRec37[3];
	double fRec36[3];
	double fRec35[3];
	double fRec31[2];
	int iRec32[2];
	double fRec33[2];
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT fVslider3;
	double fRec49[2];
	double fConst108;
	double fConst109;
	double fConst110;
	double fRec59[2];
	double fRec58[3];
	double fVec3[2];
	double fConst111;
	double fConst112;
	double fRec57[2];
	double fConst113;
	double fRec56[3];
	double fConst114;
	double fRec55[3];
	double fRec54[3];
	double fRec53[3];
	double fRec52[3];
	double fRec51[3];
	double fRec50[3];
	double fRec46[2];
	int iRec47[2];
	double fRec48[2];
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT fVslider4;
	double fRec63[2];
	double fConst115;
	double fConst116;
	double fConst117;
	double fRec72[2];
	double fRec71[3];
	double fVec4[2];
	double fConst118;
	double fConst119;
	double fRec70[2];
	double fConst120;
	double fRec69[3];
	double fConst121;
	double fRec68[3];
	double fRec67[3];
	double fRec66[3];
	double fRec65[3];
	double fRec64[3];
	double fRec60[2];
	int iRec61[2];
	double fRec62[2];
	FAUSTFLOAT fVbargraph4;
	FAUSTFLOAT fVslider5;
	double fRec76[2];
	double fConst122;
	double fConst123;
	double fConst124;
	double fRec84[2];
	double fRec83[3];
	double fVec5[2];
	double fConst125;
	double fConst126;
	double fRec82[2];
	double fConst127;
	double fRec81[3];
	double fConst128;
	double fRec80[3];
	double fRec79[3];
	double fRec78[3];
	double fRec77[3];
	double fRec73[2];
	int iRec74[2];
	double fRec75[2];
	FAUSTFLOAT fVbargraph5;
	FAUSTFLOAT fVslider6;
	double fRec88[2];
	double fConst129;
	double fConst130;
	double fConst131;
	double fRec95[2];
	double fRec94[3];
	double fVec6[2];
	double fConst132;
	double fConst133;
	double fRec93[2];
	double fConst134;
	double fRec92[3];
	double fConst135;
	double fRec91[3];
	double fRec90[3];
	double fRec89[3];
	double fRec85[2];
	int iRec86[2];
	double fRec87[2];
	FAUSTFLOAT fVbargraph6;
	FAUSTFLOAT fVslider7;
	double fRec99[2];
	double fConst136;
	double fConst137;
	double fConst138;
	double fRec105[2];
	double fRec104[3];
	double fVec7[2];
	double fConst139;
	double fConst140;
	double fRec103[2];
	double fConst141;
	double fRec102[3];
	double fConst142;
	double fRec101[3];
	double fRec100[3];
	double fRec96[2];
	int iRec97[2];
	double fRec98[2];
	FAUSTFLOAT fVbargraph7;
	FAUSTFLOAT fVslider8;
	double fRec109[2];
	double fConst143;
	double fConst144;
	double fConst145;
	double fRec114[2];
	double fRec113[3];
	double fVec8[2];
	double fConst146;
	double fConst147;
	double fRec112[2];
	double fConst148;
	double fRec111[3];
	double fConst149;
	double fRec110[3];
	double fRec106[2];
	int iRec107[2];
	double fRec108[2];
	FAUSTFLOAT fVbargraph8;
	double fConst150;
	FAUSTFLOAT fVslider9;
	double fRec118[2];
	double fConst151;
	double fConst152;
	double fRec122[2];
	double fRec121[3];
	double fVec9[2];
	double fConst153;
	double fConst154;
	double fRec120[2];
	double fConst155;
	double fRec119[3];
	double fConst156;
	double fRec115[2];
	int iRec116[2];
	double fRec117[2];
	FAUSTFLOAT fVbargraph9;
	FAUSTFLOAT fVslider10;
	double fRec126[2];
	double fConst157;
	double fRec128[2];
	double fRec127[3];
	double fRec123[2];
	int iRec124[2];
	double fRec125[2];
	FAUSTFLOAT fVbargraph10;

	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec3[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fVec0[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec14[l2] = 0.0;
	for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) fRec13[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec12[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec11[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec10[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRec9[l7] = 0.0;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec8[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec7[l9] = 0.0;
	for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) fRec6[l10] = 0.0;
	for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) fRec5[l11] = 0.0;
	for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) fRec4[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec0[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) iRec1[l14] = 0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec2[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec18[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec30[l17] = 0.0;
	for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) fRec29[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fVec1[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fRec28[l20] = 0.0;
	for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) fRec27[l21] = 0.0;
	for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) fRec26[l22] = 0.0;
	for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) fRec25[l23] = 0.0;
	for (int l24 = 0; (l24 < 3); l24 = (l24 + 1)) fRec24[l24] = 0.0;
	for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) fRec23[l25] = 0.0;
	for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) fRec22[l26] = 0.0;
	for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) fRec21[l27] = 0.0;
	for (int l28 = 0; (l28 < 3); l28 = (l28 + 1)) fRec20[l28] = 0.0;
	for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) fRec19[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec15[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) iRec16[l31] = 0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fRec17[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fRec34[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec45[l34] = 0.0;
	for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) fRec44[l35] = 0.0;
	for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) fVec2[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fRec43[l37] = 0.0;
	for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) fRec42[l38] = 0.0;
	for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) fRec41[l39] = 0.0;
	for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) fRec40[l40] = 0.0;
	for (int l41 = 0; (l41 < 3); l41 = (l41 + 1)) fRec39[l41] = 0.0;
	for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) fRec38[l42] = 0.0;
	for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) fRec37[l43] = 0.0;
	for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) fRec36[l44] = 0.0;
	for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) fRec35[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec31[l46] = 0.0;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) iRec32[l47] = 0;
	for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) fRec33[l48] = 0.0;
	for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) fRec49[l49] = 0.0;
	for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) fRec59[l50] = 0.0;
	for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) fRec58[l51] = 0.0;
	for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) fVec3[l52] = 0.0;
	for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) fRec57[l53] = 0.0;
	for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) fRec56[l54] = 0.0;
	for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) fRec55[l55] = 0.0;
	for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) fRec54[l56] = 0.0;
	for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) fRec53[l57] = 0.0;
	for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) fRec52[l58] = 0.0;
	for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) fRec51[l59] = 0.0;
	for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) fRec50[l60] = 0.0;
	for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) fRec46[l61] = 0.0;
	for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) iRec47[l62] = 0;
	for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) fRec48[l63] = 0.0;
	for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) fRec63[l64] = 0.0;
	for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) fRec72[l65] = 0.0;
	for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) fRec71[l66] = 0.0;
	for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) fVec4[l67] = 0.0;
	for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) fRec70[l68] = 0.0;
	for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) fRec69[l69] = 0.0;
	for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) fRec68[l70] = 0.0;
	for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) fRec67[l71] = 0.0;
	for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) fRec66[l72] = 0.0;
	for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) fRec65[l73] = 0.0;
	for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) fRec64[l74] = 0.0;
	for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) fRec60[l75] = 0.0;
	for (int l76 = 0; (l76 < 2); l76 = (l76 + 1)) iRec61[l76] = 0;
	for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) fRec62[l77] = 0.0;
	for (int l78 = 0; (l78 < 2); l78 = (l78 + 1)) fRec76[l78] = 0.0;
	for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) fRec84[l79] = 0.0;
	for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) fRec83[l80] = 0.0;
	for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) fVec5[l81] = 0.0;
	for (int l82 = 0; (l82 < 2); l82 = (l82 + 1)) fRec82[l82] = 0.0;
	for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) fRec81[l83] = 0.0;
	for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) fRec80[l84] = 0.0;
	for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) fRec79[l85] = 0.0;
	for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) fRec78[l86] = 0.0;
	for (int l87 = 0; (l87 < 3); l87 = (l87 + 1)) fRec77[l87] = 0.0;
	for (int l88 = 0; (l88 < 2); l88 = (l88 + 1)) fRec73[l88] = 0.0;
	for (int l89 = 0; (l89 < 2); l89 = (l89 + 1)) iRec74[l89] = 0;
	for (int l90 = 0; (l90 < 2); l90 = (l90 + 1)) fRec75[l90] = 0.0;
	for (int l91 = 0; (l91 < 2); l91 = (l91 + 1)) fRec88[l91] = 0.0;
	for (int l92 = 0; (l92 < 2); l92 = (l92 + 1)) fRec95[l92] = 0.0;
	for (int l93 = 0; (l93 < 3); l93 = (l93 + 1)) fRec94[l93] = 0.0;
	for (int l94 = 0; (l94 < 2); l94 = (l94 + 1)) fVec6[l94] = 0.0;
	for (int l95 = 0; (l95 < 2); l95 = (l95 + 1)) fRec93[l95] = 0.0;
	for (int l96 = 0; (l96 < 3); l96 = (l96 + 1)) fRec92[l96] = 0.0;
	for (int l97 = 0; (l97 < 3); l97 = (l97 + 1)) fRec91[l97] = 0.0;
	for (int l98 = 0; (l98 < 3); l98 = (l98 + 1)) fRec90[l98] = 0.0;
	for (int l99 = 0; (l99 < 3); l99 = (l99 + 1)) fRec89[l99] = 0.0;
	for (int l100 = 0; (l100 < 2); l100 = (l100 + 1)) fRec85[l100] = 0.0;
	for (int l101 = 0; (l101 < 2); l101 = (l101 + 1)) iRec86[l101] = 0;
	for (int l102 = 0; (l102 < 2); l102 = (l102 + 1)) fRec87[l102] = 0.0;
	for (int l103 = 0; (l103 < 2); l103 = (l103 + 1)) fRec99[l103] = 0.0;
	for (int l104 = 0; (l104 < 2); l104 = (l104 + 1)) fRec105[l104] = 0.0;
	for (int l105 = 0; (l105 < 3); l105 = (l105 + 1)) fRec104[l105] = 0.0;
	for (int l106 = 0; (l106 < 2); l106 = (l106 + 1)) fVec7[l106] = 0.0;
	for (int l107 = 0; (l107 < 2); l107 = (l107 + 1)) fRec103[l107] = 0.0;
	for (int l108 = 0; (l108 < 3); l108 = (l108 + 1)) fRec102[l108] = 0.0;
	for (int l109 = 0; (l109 < 3); l109 = (l109 + 1)) fRec101[l109] = 0.0;
	for (int l110 = 0; (l110 < 3); l110 = (l110 + 1)) fRec100[l110] = 0.0;
	for (int l111 = 0; (l111 < 2); l111 = (l111 + 1)) fRec96[l111] = 0.0;
	for (int l112 = 0; (l112 < 2); l112 = (l112 + 1)) iRec97[l112] = 0;
	for (int l113 = 0; (l113 < 2); l113 = (l113 + 1)) fRec98[l113] = 0.0;
	for (int l114 = 0; (l114 < 2); l114 = (l114 + 1)) fRec109[l114] = 0.0;
	for (int l115 = 0; (l115 < 2); l115 = (l115 + 1)) fRec114[l115] = 0.0;
	for (int l116 = 0; (l116 < 3); l116 = (l116 + 1)) fRec113[l116] = 0.0;
	for (int l117 = 0; (l117 < 2); l117 = (l117 + 1)) fVec8[l117] = 0.0;
	for (int l118 = 0; (l118 < 2); l118 = (l118 + 1)) fRec112[l118] = 0.0;
	for (int l119 = 0; (l119 < 3); l119 = (l119 + 1)) fRec111[l119] = 0.0;
	for (int l120 = 0; (l120 < 3); l120 = (l120 + 1)) fRec110[l120] = 0.0;
	for (int l121 = 0; (l121 < 2); l121 = (l121 + 1)) fRec106[l121] = 0.0;
	for (int l122 = 0; (l122 < 2); l122 = (l122 + 1)) iRec107[l122] = 0;
	for (int l123 = 0; (l123 < 2); l123 = (l123 + 1)) fRec108[l123] = 0.0;
	for (int l124 = 0; (l124 < 2); l124 = (l124 + 1)) fRec118[l124] = 0.0;
	for (int l125 = 0; (l125 < 2); l125 = (l125 + 1)) fRec122[l125] = 0.0;
	for (int l126 = 0; (l126 < 3); l126 = (l126 + 1)) fRec121[l126] = 0.0;
	for (int l127 = 0; (l127 < 2); l127 = (l127 + 1)) fVec9[l127] = 0.0;
	for (int l128 = 0; (l128 < 2); l128 = (l128 + 1)) fRec120[l128] = 0.0;
	for (int l129 = 0; (l129 < 3); l129 = (l129 + 1)) fRec119[l129] = 0.0;
	for (int l130 = 0; (l130 < 2); l130 = (l130 + 1)) fRec115[l130] = 0.0;
	for (int l131 = 0; (l131 < 2); l131 = (l131 + 1)) iRec116[l131] = 0;
	for (int l132 = 0; (l132 < 2); l132 = (l132 + 1)) fRec117[l132] = 0.0;
	for (int l133 = 0; (l133 < 2); l133 = (l133 + 1)) fRec126[l133] = 0.0;
	for (int l134 = 0; (l134 < 2); l134 = (l134 + 1)) fRec128[l134] = 0.0;
	for (int l135 = 0; (l135 < 3); l135 = (l135 + 1)) fRec127[l135] = 0.0;
	for (int l136 = 0; (l136 < 2); l136 = (l136 + 1)) fRec123[l136] = 0.0;
	for (int l137 = 0; (l137 < 2); l137 = (l137 + 1)) iRec124[l137] = 0;
	for (int l138 = 0; (l138 < 2); l138 = (l138 + 1)) fRec125[l138] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = (1.0 / fConst0);
	fConst2 = std::tan((56894.242956511152 / fConst0));
	fConst3 = (1.0 / fConst2);
	fConst4 = (1.0 / (((fConst3 + 1.0000000000000004) / fConst2) + 1.0));
	fConst5 = mydsp_faustpower2_f(fConst2);
	fConst6 = (1.0 / fConst5);
	fConst7 = (fConst3 + 1.0);
	fConst8 = (0.0 - (1.0 / (fConst7 * fConst2)));
	fConst9 = (1.0 / fConst7);
	fConst10 = (1.0 - fConst3);
	fConst11 = (((fConst3 + -1.0000000000000004) / fConst2) + 1.0);
	fConst12 = (2.0 * (1.0 - fConst6));
	fConst13 = (0.0 - (2.0 / fConst5));
	fConst14 = std::tan((35763.890768466204 / fConst0));
	fConst15 = (1.0 / fConst14);
	fConst16 = (fConst15 + 1.0);
	fConst17 = (1.0 / ((fConst16 / fConst14) + 1.0));
	fConst18 = (1.0 - fConst15);
	fConst19 = (1.0 - (fConst18 / fConst14));
	fConst20 = mydsp_faustpower2_f(fConst14);
	fConst21 = (1.0 / fConst20);
	fConst22 = (2.0 * (1.0 - fConst21));
	fConst23 = std::tan((17771.989641357461 / fConst0));
	fConst24 = (1.0 / fConst23);
	fConst25 = (fConst24 + 1.0);
	fConst26 = (1.0 / ((fConst25 / fConst23) + 1.0));
	fConst27 = (1.0 - fConst24);
	fConst28 = (1.0 - (fConst27 / fConst23));
	fConst29 = mydsp_faustpower2_f(fConst23);
	fConst30 = (1.0 / fConst29);
	fConst31 = (2.0 * (1.0 - fConst30));
	fConst32 = std::tan((8884.4240243519343 / fConst0));
	fConst33 = (1.0 / fConst32);
	fConst34 = (fConst33 + 1.0);
	fConst35 = (1.0 / ((fConst34 / fConst32) + 1.0));
	fConst36 = (1.0 - fConst33);
	fConst37 = (1.0 - (fConst36 / fConst32));
	fConst38 = mydsp_faustpower2_f(fConst32);
	fConst39 = (1.0 / fConst38);
	fConst40 = (2.0 * (1.0 - fConst39));
	fConst41 = std::tan((4442.2120121759672 / fConst0));
	fConst42 = (1.0 / fConst41);
	fConst43 = (fConst42 + 1.0);
	fConst44 = (1.0 / ((fConst43 / fConst41) + 1.0));
	fConst45 = (1.0 - fConst42);
	fConst46 = (1.0 - (fConst45 / fConst41));
	fConst47 = mydsp_faustpower2_f(fConst41);
	fConst48 = (1.0 / fConst47);
	fConst49 = (2.0 * (1.0 - fConst48));
	fConst50 = std::tan((2221.1060060879836 / fConst0));
	fConst51 = (1.0 / fConst50);
	fConst52 = (fConst51 + 1.0);
	fConst53 = (1.0 / ((fConst52 / fConst50) + 1.0));
	fConst54 = (1.0 - fConst51);
	fConst55 = (1.0 - (fConst54 / fConst50));
	fConst56 = mydsp_faustpower2_f(fConst50);
	fConst57 = (1.0 / fConst56);
	fConst58 = (2.0 * (1.0 - fConst57));
	fConst59 = std::tan((1112.1237993707869 / fConst0));
	fConst60 = (1.0 / fConst59);
	fConst61 = (fConst60 + 1.0);
	fConst62 = (1.0 / ((fConst61 / fConst59) + 1.0));
	fConst63 = (1.0 - fConst60);
	fConst64 = (1.0 - (fConst63 / fConst59));
	fConst65 = mydsp_faustpower2_f(fConst59);
	fConst66 = (1.0 / fConst65);
	fConst67 = (2.0 * (1.0 - fConst66));
	fConst68 = std::tan((556.06189968539343 / fConst0));
	fConst69 = (1.0 / fConst68);
	fConst70 = (fConst69 + 1.0);
	fConst71 = (1.0 / ((fConst70 / fConst68) + 1.0));
	fConst72 = (1.0 - fConst69);
	fConst73 = (1.0 - (fConst72 / fConst68));
	fConst74 = mydsp_faustpower2_f(fConst68);
	fConst75 = (1.0 / fConst74);
	fConst76 = (2.0 * (1.0 - fConst75));
	fConst77 = std::tan((276.46015351590177 / fConst0));
	fConst78 = (1.0 / fConst77);
	fConst79 = (fConst78 + 1.0);
	fConst80 = (1.0 / ((fConst79 / fConst77) + 1.0));
	fConst81 = (1.0 - fConst78);
	fConst82 = (1.0 - (fConst81 / fConst77));
	fConst83 = mydsp_faustpower2_f(fConst77);
	fConst84 = (1.0 / fConst83);
	fConst85 = (2.0 * (1.0 - fConst84));
	fConst86 = std::tan((138.23007675795088 / fConst0));
	fConst87 = (1.0 / fConst86);
	fConst88 = (fConst87 + 1.0);
	fConst89 = (1.0 / ((fConst88 / fConst86) + 1.0));
	fConst90 = (1.0 - fConst87);
	fConst91 = (1.0 - (fConst90 / fConst86));
	fConst92 = mydsp_faustpower2_f(fConst86);
	fConst93 = (1.0 / fConst92);
	fConst94 = (2.0 * (1.0 - fConst93));
	fConst95 = (1.0 / (((fConst15 + 1.0000000000000004) / fConst14) + 1.0));
	fConst96 = (1.0 / (fConst14 * fConst16));
	fConst97 = (0.0 - fConst96);
	fConst98 = (fConst18 / fConst16);
	fConst99 = (((fConst15 + -1.0000000000000004) / fConst14) + 1.0);
	fConst100 = (0.0 - (2.0 / fConst20));
	fConst101 = (1.0 / (((fConst24 + 1.0000000000000004) / fConst23) + 1.0));
	fConst102 = (1.0 / (fConst23 * fConst25));
	fConst103 = (1.0 / fConst16);
	fConst104 = (0.0 - fConst102);
	fConst105 = (fConst27 / fConst25);
	fConst106 = (((fConst24 + -1.0000000000000004) / fConst23) + 1.0);
	fConst107 = (0.0 - (2.0 / fConst29));
	fConst108 = (1.0 / (((fConst33 + 1.0000000000000004) / fConst32) + 1.0));
	fConst109 = (1.0 / (fConst32 * fConst34));
	fConst110 = (1.0 / fConst25);
	fConst111 = (0.0 - fConst109);
	fConst112 = (fConst36 / fConst34);
	fConst113 = (((fConst33 + -1.0000000000000004) / fConst32) + 1.0);
	fConst114 = (0.0 - (2.0 / fConst38));
	fConst115 = (1.0 / (((fConst42 + 1.0000000000000004) / fConst41) + 1.0));
	fConst116 = (1.0 / (fConst41 * fConst43));
	fConst117 = (1.0 / fConst34);
	fConst118 = (0.0 - fConst116);
	fConst119 = (fConst45 / fConst43);
	fConst120 = (((fConst42 + -1.0000000000000004) / fConst41) + 1.0);
	fConst121 = (0.0 - (2.0 / fConst47));
	fConst122 = (1.0 / (((fConst51 + 1.0000000000000004) / fConst50) + 1.0));
	fConst123 = (1.0 / (fConst50 * fConst52));
	fConst124 = (1.0 / fConst43);
	fConst125 = (0.0 - fConst123);
	fConst126 = (fConst54 / fConst52);
	fConst127 = (((fConst51 + -1.0000000000000004) / fConst50) + 1.0);
	fConst128 = (0.0 - (2.0 / fConst56));
	fConst129 = (1.0 / (((fConst60 + 1.0000000000000004) / fConst59) + 1.0));
	fConst130 = (1.0 / (fConst59 * fConst61));
	fConst131 = (1.0 / fConst52);
	fConst132 = (0.0 - fConst130);
	fConst133 = (fConst63 / fConst61);
	fConst134 = (((fConst60 + -1.0000000000000004) / fConst59) + 1.0);
	fConst135 = (0.0 - (2.0 / fConst65));
	fConst136 = (1.0 / (((fConst69 + 1.0000000000000004) / fConst68) + 1.0));
	fConst137 = (1.0 / (fConst68 * fConst70));
	fConst138 = (1.0 / fConst61);
	fConst139 = (0.0 - fConst137);
	fConst140 = (fConst72 / fConst70);
	fConst141 = (((fConst69 + -1.0000000000000004) / fConst68) + 1.0);
	fConst142 = (0.0 - (2.0 / fConst74));
	fConst143 = (1.0 / (((fConst78 + 1.0000000000000004) / fConst77) + 1.0));
	fConst144 = (1.0 / (fConst77 * fConst79));
	fConst145 = (1.0 / fConst70);
	fConst146 = (0.0 - fConst144);
	fConst147 = (fConst81 / fConst79);
	fConst148 = (((fConst78 + -1.0000000000000004) / fConst77) + 1.0);
	fConst149 = (0.0 - (2.0 / fConst83));
	fConst150 = (1.0 / (((fConst87 + 1.0000000000000004) / fConst86) + 1.0));
	fConst151 = (1.0 / (fConst86 * fConst88));
	fConst152 = (1.0 / fConst79);
	fConst153 = (0.0 - fConst151);
	fConst154 = (fConst90 / fConst88);
	fConst155 = (((fConst87 + -1.0000000000000004) / fConst86) + 1.0);
	fConst156 = (0.0 - (2.0 / fConst92));
	fConst157 = (1.0 / fConst88);
	fVslider0 = FAUSTFLOAT(0.0);
	fVslider1 = FAUSTFLOAT(0.0);
	fVslider2 = FAUSTFLOAT(0.0);
	fVslider3 = FAUSTFLOAT(0.0);
	fVslider4 = FAUSTFLOAT(0.0);
	fVslider5 = FAUSTFLOAT(0.0);
	fVslider6 = FAUSTFLOAT(0.0);
	fVslider7 = FAUSTFLOAT(0.0);
	fVslider8 = FAUSTFLOAT(0.0);
	fVslider9 = FAUSTFLOAT(0.0);
	fVslider10 = FAUSTFLOAT(0.0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider0))));
	double fSlow1 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider1))));
	double fSlow2 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider2))));
	double fSlow3 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider3))));
	double fSlow4 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider4))));
	double fSlow5 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider5))));
	double fSlow6 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider6))));
	double fSlow7 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider7))));
	double fSlow8 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider8))));
	double fSlow9 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider9))));
	double fSlow10 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider10))));
	for (int i = 0; (i < count); i = (i + 1)) {
		int iTemp0 = (iRec1[1] < 4096);
		fRec3[0] = (fSlow0 + (0.999 * fRec3[1]));
		double fTemp1 = double(input0[i]);
		fVec0[0] = fTemp1;
		fRec14[0] = ((fConst8 * fVec0[1]) - (fConst9 * ((fConst10 * fRec14[1]) - (fConst3 * fTemp1))));
		fRec13[0] = (fRec14[0] - (fConst4 * ((fConst11 * fRec13[2]) + (fConst12 * fRec13[1]))));
		double fTemp2 = (fConst22 * fRec12[1]);
		fRec12[0] = ((fConst4 * (((fConst6 * fRec13[0]) + (fConst13 * fRec13[1])) + (fConst6 * fRec13[2]))) - (fConst17 * ((fConst19 * fRec12[2]) + fTemp2)));
		double fTemp3 = (fConst31 * fRec11[1]);
		fRec11[0] = ((fRec12[2] + (fConst17 * (fTemp2 + (fConst19 * fRec12[0])))) - (fConst26 * ((fConst28 * fRec11[2]) + fTemp3)));
		double fTemp4 = (fConst40 * fRec10[1]);
		fRec10[0] = ((fRec11[2] + (fConst26 * (fTemp3 + (fConst28 * fRec11[0])))) - (fConst35 * ((fConst37 * fRec10[2]) + fTemp4)));
		double fTemp5 = (fConst49 * fRec9[1]);
		fRec9[0] = ((fRec10[2] + (fConst35 * (fTemp4 + (fConst37 * fRec10[0])))) - (fConst44 * ((fConst46 * fRec9[2]) + fTemp5)));
		double fTemp6 = (fConst58 * fRec8[1]);
		fRec8[0] = ((fRec9[2] + (fConst44 * (fTemp5 + (fConst46 * fRec9[0])))) - (fConst53 * ((fConst55 * fRec8[2]) + fTemp6)));
		double fTemp7 = (fConst67 * fRec7[1]);
		fRec7[0] = ((fRec8[2] + (fConst53 * (fTemp6 + (fConst55 * fRec8[0])))) - (fConst62 * ((fConst64 * fRec7[2]) + fTemp7)));
		double fTemp8 = (fConst76 * fRec6[1]);
		fRec6[0] = ((fRec7[2] + (fConst62 * (fTemp7 + (fConst64 * fRec7[0])))) - (fConst71 * ((fConst73 * fRec6[2]) + fTemp8)));
		double fTemp9 = (fConst85 * fRec5[1]);
		fRec5[0] = ((fRec6[2] + (fConst71 * (fTemp8 + (fConst73 * fRec6[0])))) - (fConst80 * ((fConst82 * fRec5[2]) + fTemp9)));
		double fTemp10 = (fConst94 * fRec4[1]);
		fRec4[0] = ((fRec5[2] + (fConst80 * (fTemp9 + (fConst82 * fRec5[0])))) - (fConst89 * ((fConst91 * fRec4[2]) + fTemp10)));
		double fTemp11 = (fRec3[0] * (fRec4[2] + (fConst89 * (fTemp10 + (fConst91 * fRec4[0])))));
		double fTemp12 = std::max<double>(fConst1, std::fabs(fTemp11));
		fRec0[0] = (iTemp0?std::max<double>(fRec0[1], fTemp12):fTemp12);
		iRec1[0] = (iTemp0?(iRec1[1] + 1):1);
		fRec2[0] = (iTemp0?fRec2[1]:fRec0[1]);
		fVbargraph0 = FAUSTFLOAT(fRec2[0]);
		int iTemp13 = (iRec16[1] < 4096);
		fRec18[0] = (fSlow1 + (0.999 * fRec18[1]));
		fRec30[0] = (0.0 - (fConst9 * ((fConst10 * fRec30[1]) - (fVec0[1] + fTemp1))));
		fRec29[0] = (fRec30[0] - (fConst4 * ((fConst11 * fRec29[2]) + (fConst12 * fRec29[1]))));
		double fTemp14 = (fRec29[2] + (fRec29[0] + (2.0 * fRec29[1])));
		fVec1[0] = fTemp14;
		fRec28[0] = ((fConst4 * ((fConst96 * fTemp14) + (fConst97 * fVec1[1]))) - (fConst98 * fRec28[1]));
		fRec27[0] = (fRec28[0] - (fConst95 * ((fConst99 * fRec27[2]) + (fConst22 * fRec27[1]))));
		double fTemp15 = (fConst31 * fRec26[1]);
		fRec26[0] = ((fConst95 * (((fConst21 * fRec27[0]) + (fConst100 * fRec27[1])) + (fConst21 * fRec27[2]))) - (fConst26 * ((fConst28 * fRec26[2]) + fTemp15)));
		double fTemp16 = (fConst40 * fRec25[1]);
		fRec25[0] = ((fRec26[2] + (fConst26 * (fTemp15 + (fConst28 * fRec26[0])))) - (fConst35 * ((fConst37 * fRec25[2]) + fTemp16)));
		double fTemp17 = (fConst49 * fRec24[1]);
		fRec24[0] = ((fRec25[2] + (fConst35 * (fTemp16 + (fConst37 * fRec25[0])))) - (fConst44 * ((fConst46 * fRec24[2]) + fTemp17)));
		double fTemp18 = (fConst58 * fRec23[1]);
		fRec23[0] = ((fRec24[2] + (fConst44 * (fTemp17 + (fConst46 * fRec24[0])))) - (fConst53 * ((fConst55 * fRec23[2]) + fTemp18)));
		double fTemp19 = (fConst67 * fRec22[1]);
		fRec22[0] = ((fRec23[2] + (fConst53 * (fTemp18 + (fConst55 * fRec23[0])))) - (fConst62 * ((fConst64 * fRec22[2]) + fTemp19)));
		double fTemp20 = (fConst76 * fRec21[1]);
		fRec21[0] = ((fRec22[2] + (fConst62 * (fTemp19 + (fConst64 * fRec22[0])))) - (fConst71 * ((fConst73 * fRec21[2]) + fTemp20)));
		double fTemp21 = (fConst85 * fRec20[1]);
		fRec20[0] = ((fRec21[2] + (fConst71 * (fTemp20 + (fConst73 * fRec21[0])))) - (fConst80 * ((fConst82 * fRec20[2]) + fTemp21)));
		double fTemp22 = (fConst94 * fRec19[1]);
		fRec19[0] = ((fRec20[2] + (fConst80 * (fTemp21 + (fConst82 * fRec20[0])))) - (fConst89 * ((fConst91 * fRec19[2]) + fTemp22)));
		double fTemp23 = (fRec18[0] * (fRec19[2] + (fConst89 * (fTemp22 + (fConst91 * fRec19[0])))));
		double fTemp24 = std::max<double>(fConst1, std::fabs(fTemp23));
		fRec15[0] = (iTemp13?std::max<double>(fRec15[1], fTemp24):fTemp24);
		iRec16[0] = (iTemp13?(iRec16[1] + 1):1);
		fRec17[0] = (iTemp13?fRec17[1]:fRec15[1]);
		fVbargraph1 = FAUSTFLOAT(fRec17[0]);
		int iTemp25 = (iRec32[1] < 4096);
		fRec34[0] = (fSlow2 + (0.999 * fRec34[1]));
		fRec45[0] = (0.0 - (fConst103 * ((fConst18 * fRec45[1]) - (fConst4 * (fTemp14 + fVec1[1])))));
		fRec44[0] = (fRec45[0] - (fConst95 * ((fConst99 * fRec44[2]) + (fConst22 * fRec44[1]))));
		double fTemp26 = (fRec44[2] + (fRec44[0] + (2.0 * fRec44[1])));
		fVec2[0] = fTemp26;
		fRec43[0] = ((fConst95 * ((fConst102 * fTemp26) + (fConst104 * fVec2[1]))) - (fConst105 * fRec43[1]));
		fRec42[0] = (fRec43[0] - (fConst101 * ((fConst106 * fRec42[2]) + (fConst31 * fRec42[1]))));
		double fTemp27 = (fConst40 * fRec41[1]);
		fRec41[0] = ((fConst101 * (((fConst30 * fRec42[0]) + (fConst107 * fRec42[1])) + (fConst30 * fRec42[2]))) - (fConst35 * ((fConst37 * fRec41[2]) + fTemp27)));
		double fTemp28 = (fConst49 * fRec40[1]);
		fRec40[0] = ((fRec41[2] + (fConst35 * (fTemp27 + (fConst37 * fRec41[0])))) - (fConst44 * ((fConst46 * fRec40[2]) + fTemp28)));
		double fTemp29 = (fConst58 * fRec39[1]);
		fRec39[0] = ((fRec40[2] + (fConst44 * (fTemp28 + (fConst46 * fRec40[0])))) - (fConst53 * ((fConst55 * fRec39[2]) + fTemp29)));
		double fTemp30 = (fConst67 * fRec38[1]);
		fRec38[0] = ((fRec39[2] + (fConst53 * (fTemp29 + (fConst55 * fRec39[0])))) - (fConst62 * ((fConst64 * fRec38[2]) + fTemp30)));
		double fTemp31 = (fConst76 * fRec37[1]);
		fRec37[0] = ((fRec38[2] + (fConst62 * (fTemp30 + (fConst64 * fRec38[0])))) - (fConst71 * ((fConst73 * fRec37[2]) + fTemp31)));
		double fTemp32 = (fConst85 * fRec36[1]);
		fRec36[0] = ((fRec37[2] + (fConst71 * (fTemp31 + (fConst73 * fRec37[0])))) - (fConst80 * ((fConst82 * fRec36[2]) + fTemp32)));
		double fTemp33 = (fConst94 * fRec35[1]);
		fRec35[0] = ((fRec36[2] + (fConst80 * (fTemp32 + (fConst82 * fRec36[0])))) - (fConst89 * ((fConst91 * fRec35[2]) + fTemp33)));
		double fTemp34 = (fRec34[0] * (fRec35[2] + (fConst89 * (fTemp33 + (fConst91 * fRec35[0])))));
		double fTemp35 = std::max<double>(fConst1, std::fabs(fTemp34));
		fRec31[0] = (iTemp25?std::max<double>(fRec31[1], fTemp35):fTemp35);
		iRec32[0] = (iTemp25?(iRec32[1] + 1):1);
		fRec33[0] = (iTemp25?fRec33[1]:fRec31[1]);
		fVbargraph2 = FAUSTFLOAT(fRec33[0]);
		int iTemp36 = (iRec47[1] < 4096);
		fRec49[0] = (fSlow3 + (0.999 * fRec49[1]));
		fRec59[0] = (0.0 - (fConst110 * ((fConst27 * fRec59[1]) - (fConst95 * (fTemp26 + fVec2[1])))));
		fRec58[0] = (fRec59[0] - (fConst101 * ((fConst106 * fRec58[2]) + (fConst31 * fRec58[1]))));
		double fTemp37 = (fRec58[2] + (fRec58[0] + (2.0 * fRec58[1])));
		fVec3[0] = fTemp37;
		fRec57[0] = ((fConst101 * ((fConst109 * fTemp37) + (fConst111 * fVec3[1]))) - (fConst112 * fRec57[1]));
		fRec56[0] = (fRec57[0] - (fConst108 * ((fConst113 * fRec56[2]) + (fConst40 * fRec56[1]))));
		double fTemp38 = (fConst49 * fRec55[1]);
		fRec55[0] = ((fConst108 * (((fConst39 * fRec56[0]) + (fConst114 * fRec56[1])) + (fConst39 * fRec56[2]))) - (fConst44 * ((fConst46 * fRec55[2]) + fTemp38)));
		double fTemp39 = (fConst58 * fRec54[1]);
		fRec54[0] = ((fRec55[2] + (fConst44 * (fTemp38 + (fConst46 * fRec55[0])))) - (fConst53 * ((fConst55 * fRec54[2]) + fTemp39)));
		double fTemp40 = (fConst67 * fRec53[1]);
		fRec53[0] = ((fRec54[2] + (fConst53 * (fTemp39 + (fConst55 * fRec54[0])))) - (fConst62 * ((fConst64 * fRec53[2]) + fTemp40)));
		double fTemp41 = (fConst76 * fRec52[1]);
		fRec52[0] = ((fRec53[2] + (fConst62 * (fTemp40 + (fConst64 * fRec53[0])))) - (fConst71 * ((fConst73 * fRec52[2]) + fTemp41)));
		double fTemp42 = (fConst85 * fRec51[1]);
		fRec51[0] = ((fRec52[2] + (fConst71 * (fTemp41 + (fConst73 * fRec52[0])))) - (fConst80 * ((fConst82 * fRec51[2]) + fTemp42)));
		double fTemp43 = (fConst94 * fRec50[1]);
		fRec50[0] = ((fRec51[2] + (fConst80 * (fTemp42 + (fConst82 * fRec51[0])))) - (fConst89 * ((fConst91 * fRec50[2]) + fTemp43)));
		double fTemp44 = (fRec49[0] * (fRec50[2] + (fConst89 * (fTemp43 + (fConst91 * fRec50[0])))));
		double fTemp45 = std::max<double>(fConst1, std::fabs(fTemp44));
		fRec46[0] = (iTemp36?std::max<double>(fRec46[1], fTemp45):fTemp45);
		iRec47[0] = (iTemp36?(iRec47[1] + 1):1);
		fRec48[0] = (iTemp36?fRec48[1]:fRec46[1]);
		fVbargraph3 = FAUSTFLOAT(fRec48[0]);
		int iTemp46 = (iRec61[1] < 4096);
		fRec63[0] = (fSlow4 + (0.999 * fRec63[1]));
		fRec72[0] = (0.0 - (fConst117 * ((fConst36 * fRec72[1]) - (fConst101 * (fTemp37 + fVec3[1])))));
		fRec71[0] = (fRec72[0] - (fConst108 * ((fConst113 * fRec71[2]) + (fConst40 * fRec71[1]))));
		double fTemp47 = (fRec71[2] + (fRec71[0] + (2.0 * fRec71[1])));
		fVec4[0] = fTemp47;
		fRec70[0] = ((fConst108 * ((fConst116 * fTemp47) + (fConst118 * fVec4[1]))) - (fConst119 * fRec70[1]));
		fRec69[0] = (fRec70[0] - (fConst115 * ((fConst120 * fRec69[2]) + (fConst49 * fRec69[1]))));
		double fTemp48 = (fConst58 * fRec68[1]);
		fRec68[0] = ((fConst115 * (((fConst48 * fRec69[0]) + (fConst121 * fRec69[1])) + (fConst48 * fRec69[2]))) - (fConst53 * ((fConst55 * fRec68[2]) + fTemp48)));
		double fTemp49 = (fConst67 * fRec67[1]);
		fRec67[0] = ((fRec68[2] + (fConst53 * (fTemp48 + (fConst55 * fRec68[0])))) - (fConst62 * ((fConst64 * fRec67[2]) + fTemp49)));
		double fTemp50 = (fConst76 * fRec66[1]);
		fRec66[0] = ((fRec67[2] + (fConst62 * (fTemp49 + (fConst64 * fRec67[0])))) - (fConst71 * ((fConst73 * fRec66[2]) + fTemp50)));
		double fTemp51 = (fConst85 * fRec65[1]);
		fRec65[0] = ((fRec66[2] + (fConst71 * (fTemp50 + (fConst73 * fRec66[0])))) - (fConst80 * ((fConst82 * fRec65[2]) + fTemp51)));
		double fTemp52 = (fConst94 * fRec64[1]);
		fRec64[0] = ((fRec65[2] + (fConst80 * (fTemp51 + (fConst82 * fRec65[0])))) - (fConst89 * ((fConst91 * fRec64[2]) + fTemp52)));
		double fTemp53 = (fRec63[0] * (fRec64[2] + (fConst89 * (fTemp52 + (fConst91 * fRec64[0])))));
		double fTemp54 = std::max<double>(fConst1, std::fabs(fTemp53));
		fRec60[0] = (iTemp46?std::max<double>(fRec60[1], fTemp54):fTemp54);
		iRec61[0] = (iTemp46?(iRec61[1] + 1):1);
		fRec62[0] = (iTemp46?fRec62[1]:fRec60[1]);
		fVbargraph4 = FAUSTFLOAT(fRec62[0]);
		int iTemp55 = (iRec74[1] < 4096);
		fRec76[0] = (fSlow5 + (0.999 * fRec76[1]));
		fRec84[0] = (0.0 - (fConst124 * ((fConst45 * fRec84[1]) - (fConst108 * (fTemp47 + fVec4[1])))));
		fRec83[0] = (fRec84[0] - (fConst115 * ((fConst120 * fRec83[2]) + (fConst49 * fRec83[1]))));
		double fTemp56 = (fRec83[2] + (fRec83[0] + (2.0 * fRec83[1])));
		fVec5[0] = fTemp56;
		fRec82[0] = ((fConst115 * ((fConst123 * fTemp56) + (fConst125 * fVec5[1]))) - (fConst126 * fRec82[1]));
		fRec81[0] = (fRec82[0] - (fConst122 * ((fConst127 * fRec81[2]) + (fConst58 * fRec81[1]))));
		double fTemp57 = (fConst67 * fRec80[1]);
		fRec80[0] = ((fConst122 * (((fConst57 * fRec81[0]) + (fConst128 * fRec81[1])) + (fConst57 * fRec81[2]))) - (fConst62 * ((fConst64 * fRec80[2]) + fTemp57)));
		double fTemp58 = (fConst76 * fRec79[1]);
		fRec79[0] = ((fRec80[2] + (fConst62 * (fTemp57 + (fConst64 * fRec80[0])))) - (fConst71 * ((fConst73 * fRec79[2]) + fTemp58)));
		double fTemp59 = (fConst85 * fRec78[1]);
		fRec78[0] = ((fRec79[2] + (fConst71 * (fTemp58 + (fConst73 * fRec79[0])))) - (fConst80 * ((fConst82 * fRec78[2]) + fTemp59)));
		double fTemp60 = (fConst94 * fRec77[1]);
		fRec77[0] = ((fRec78[2] + (fConst80 * (fTemp59 + (fConst82 * fRec78[0])))) - (fConst89 * ((fConst91 * fRec77[2]) + fTemp60)));
		double fTemp61 = (fRec76[0] * (fRec77[2] + (fConst89 * (fTemp60 + (fConst91 * fRec77[0])))));
		double fTemp62 = std::max<double>(fConst1, std::fabs(fTemp61));
		fRec73[0] = (iTemp55?std::max<double>(fRec73[1], fTemp62):fTemp62);
		iRec74[0] = (iTemp55?(iRec74[1] + 1):1);
		fRec75[0] = (iTemp55?fRec75[1]:fRec73[1]);
		fVbargraph5 = FAUSTFLOAT(fRec75[0]);
		int iTemp63 = (iRec86[1] < 4096);
		fRec88[0] = (fSlow6 + (0.999 * fRec88[1]));
		fRec95[0] = (0.0 - (fConst131 * ((fConst54 * fRec95[1]) - (fConst115 * (fTemp56 + fVec5[1])))));
		fRec94[0] = (fRec95[0] - (fConst122 * ((fConst127 * fRec94[2]) + (fConst58 * fRec94[1]))));
		double fTemp64 = (fRec94[2] + (fRec94[0] + (2.0 * fRec94[1])));
		fVec6[0] = fTemp64;
		fRec93[0] = ((fConst122 * ((fConst130 * fTemp64) + (fConst132 * fVec6[1]))) - (fConst133 * fRec93[1]));
		fRec92[0] = (fRec93[0] - (fConst129 * ((fConst134 * fRec92[2]) + (fConst67 * fRec92[1]))));
		double fTemp65 = (fConst76 * fRec91[1]);
		fRec91[0] = ((fConst129 * (((fConst66 * fRec92[0]) + (fConst135 * fRec92[1])) + (fConst66 * fRec92[2]))) - (fConst71 * ((fConst73 * fRec91[2]) + fTemp65)));
		double fTemp66 = (fConst85 * fRec90[1]);
		fRec90[0] = ((fRec91[2] + (fConst71 * (fTemp65 + (fConst73 * fRec91[0])))) - (fConst80 * ((fConst82 * fRec90[2]) + fTemp66)));
		double fTemp67 = (fConst94 * fRec89[1]);
		fRec89[0] = ((fRec90[2] + (fConst80 * (fTemp66 + (fConst82 * fRec90[0])))) - (fConst89 * ((fConst91 * fRec89[2]) + fTemp67)));
		double fTemp68 = (fRec88[0] * (fRec89[2] + (fConst89 * (fTemp67 + (fConst91 * fRec89[0])))));
		double fTemp69 = std::max<double>(fConst1, std::fabs(fTemp68));
		fRec85[0] = (iTemp63?std::max<double>(fRec85[1], fTemp69):fTemp69);
		iRec86[0] = (iTemp63?(iRec86[1] + 1):1);
		fRec87[0] = (iTemp63?fRec87[1]:fRec85[1]);
		fVbargraph6 = FAUSTFLOAT(fRec87[0]);
		int iTemp70 = (iRec97[1] < 4096);
		fRec99[0] = (fSlow7 + (0.999 * fRec99[1]));
		fRec105[0] = (0.0 - (fConst138 * ((fConst63 * fRec105[1]) - (fConst122 * (fTemp64 + fVec6[1])))));
		fRec104[0] = (fRec105[0] - (fConst129 * ((fConst134 * fRec104[2]) + (fConst67 * fRec104[1]))));
		double fTemp71 = (fRec104[2] + (fRec104[0] + (2.0 * fRec104[1])));
		fVec7[0] = fTemp71;
		fRec103[0] = ((fConst129 * ((fConst137 * fTemp71) + (fConst139 * fVec7[1]))) - (fConst140 * fRec103[1]));
		fRec102[0] = (fRec103[0] - (fConst136 * ((fConst141 * fRec102[2]) + (fConst76 * fRec102[1]))));
		double fTemp72 = (fConst85 * fRec101[1]);
		fRec101[0] = ((fConst136 * (((fConst75 * fRec102[0]) + (fConst142 * fRec102[1])) + (fConst75 * fRec102[2]))) - (fConst80 * ((fConst82 * fRec101[2]) + fTemp72)));
		double fTemp73 = (fConst94 * fRec100[1]);
		fRec100[0] = ((fRec101[2] + (fConst80 * (fTemp72 + (fConst82 * fRec101[0])))) - (fConst89 * ((fConst91 * fRec100[2]) + fTemp73)));
		double fTemp74 = (fRec99[0] * (fRec100[2] + (fConst89 * (fTemp73 + (fConst91 * fRec100[0])))));
		double fTemp75 = std::max<double>(fConst1, std::fabs(fTemp74));
		fRec96[0] = (iTemp70?std::max<double>(fRec96[1], fTemp75):fTemp75);
		iRec97[0] = (iTemp70?(iRec97[1] + 1):1);
		fRec98[0] = (iTemp70?fRec98[1]:fRec96[1]);
		fVbargraph7 = FAUSTFLOAT(fRec98[0]);
		int iTemp76 = (iRec107[1] < 4096);
		fRec109[0] = (fSlow8 + (0.999 * fRec109[1]));
		fRec114[0] = (0.0 - (fConst145 * ((fConst72 * fRec114[1]) - (fConst129 * (fTemp71 + fVec7[1])))));
		fRec113[0] = (fRec114[0] - (fConst136 * ((fConst141 * fRec113[2]) + (fConst76 * fRec113[1]))));
		double fTemp77 = (fRec113[2] + (fRec113[0] + (2.0 * fRec113[1])));
		fVec8[0] = fTemp77;
		fRec112[0] = ((fConst136 * ((fConst144 * fTemp77) + (fConst146 * fVec8[1]))) - (fConst147 * fRec112[1]));
		fRec111[0] = (fRec112[0] - (fConst143 * ((fConst148 * fRec111[2]) + (fConst85 * fRec111[1]))));
		double fTemp78 = (fConst94 * fRec110[1]);
		fRec110[0] = ((fConst143 * (((fConst84 * fRec111[0]) + (fConst149 * fRec111[1])) + (fConst84 * fRec111[2]))) - (fConst89 * ((fConst91 * fRec110[2]) + fTemp78)));
		double fTemp79 = (fRec109[0] * (fRec110[2] + (fConst89 * (fTemp78 + (fConst91 * fRec110[0])))));
		double fTemp80 = std::max<double>(fConst1, std::fabs(fTemp79));
		fRec106[0] = (iTemp76?std::max<double>(fRec106[1], fTemp80):fTemp80);
		iRec107[0] = (iTemp76?(iRec107[1] + 1):1);
		fRec108[0] = (iTemp76?fRec108[1]:fRec106[1]);
		fVbargraph8 = FAUSTFLOAT(fRec108[0]);
		int iTemp81 = (iRec116[1] < 4096);
		fRec118[0] = (fSlow9 + (0.999 * fRec118[1]));
		fRec122[0] = (0.0 - (fConst152 * ((fConst81 * fRec122[1]) - (fConst136 * (fTemp77 + fVec8[1])))));
		fRec121[0] = (fRec122[0] - (fConst143 * ((fConst148 * fRec121[2]) + (fConst85 * fRec121[1]))));
		double fTemp82 = (fRec121[2] + (fRec121[0] + (2.0 * fRec121[1])));
		fVec9[0] = fTemp82;
		fRec120[0] = ((fConst143 * ((fConst151 * fTemp82) + (fConst153 * fVec9[1]))) - (fConst154 * fRec120[1]));
		fRec119[0] = (fRec120[0] - (fConst150 * ((fConst155 * fRec119[2]) + (fConst94 * fRec119[1]))));
		double fTemp83 = (fConst150 * (fRec118[0] * (((fConst93 * fRec119[0]) + (fConst156 * fRec119[1])) + (fConst93 * fRec119[2]))));
		double fTemp84 = std::max<double>(fConst1, std::fabs(fTemp83));
		fRec115[0] = (iTemp81?std::max<double>(fRec115[1], fTemp84):fTemp84);
		iRec116[0] = (iTemp81?(iRec116[1] + 1):1);
		fRec117[0] = (iTemp81?fRec117[1]:fRec115[1]);
		fVbargraph9 = FAUSTFLOAT(fRec117[0]);
		int iTemp85 = (iRec124[1] < 4096);
		fRec126[0] = (fSlow10 + (0.999 * fRec126[1]));
		fRec128[0] = (0.0 - (fConst157 * ((fConst90 * fRec128[1]) - (fConst143 * (fTemp82 + fVec9[1])))));
		fRec127[0] = (fRec128[0] - (fConst150 * ((fConst155 * fRec127[2]) + (fConst94 * fRec127[1]))));
		double fTemp86 = (fConst150 * (fRec126[0] * (fRec127[2] + (fRec127[0] + (2.0 * fRec127[1])))));
		double fTemp87 = std::max<double>(fConst1, std::fabs(fTemp86));
		fRec123[0] = (iTemp85?std::max<double>(fRec123[1], fTemp87):fTemp87);
		iRec124[0] = (iTemp85?(iRec124[1] + 1):1);
		fRec125[0] = (iTemp85?fRec125[1]:fRec123[1]);
		fVbargraph10 = FAUSTFLOAT(fRec125[0]);
		output0[i] = FAUSTFLOAT(((((((((((fTemp11 + fTemp23) + fTemp34) + fTemp44) + fTemp53) + fTemp61) + fTemp68) + fTemp74) + fTemp79) + fTemp83) + fTemp86));
		fRec3[1] = fRec3[0];
		fVec0[1] = fVec0[0];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec0[1] = fRec0[0];
		iRec1[1] = iRec1[0];
		fRec2[1] = fRec2[0];
		fRec18[1] = fRec18[0];
		fRec30[1] = fRec30[0];
		fRec29[2] = fRec29[1];
		fRec29[1] = fRec29[0];
		fVec1[1] = fVec1[0];
		fRec28[1] = fRec28[0];
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fRec23[2] = fRec23[1];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fRec15[1] = fRec15[0];
		iRec16[1] = iRec16[0];
		fRec17[1] = fRec17[0];
		fRec34[1] = fRec34[0];
		fRec45[1] = fRec45[0];
		fRec44[2] = fRec44[1];
		fRec44[1] = fRec44[0];
		fVec2[1] = fVec2[0];
		fRec43[1] = fRec43[0];
		fRec42[2] = fRec42[1];
		fRec42[1] = fRec42[0];
		fRec41[2] = fRec41[1];
		fRec41[1] = fRec41[0];
		fRec40[2] = fRec40[1];
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		fRec35[2] = fRec35[1];
		fRec35[1] = fRec35[0];
		fRec31[1] = fRec31[0];
		iRec32[1] = iRec32[0];
		fRec33[1] = fRec33[0];
		fRec49[1] = fRec49[0];
		fRec59[1] = fRec59[0];
		fRec58[2] = fRec58[1];
		fRec58[1] = fRec58[0];
		fVec3[1] = fVec3[0];
		fRec57[1] = fRec57[0];
		fRec56[2] = fRec56[1];
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
		fRec50[2] = fRec50[1];
		fRec50[1] = fRec50[0];
		fRec46[1] = fRec46[0];
		iRec47[1] = iRec47[0];
		fRec48[1] = fRec48[0];
		fRec63[1] = fRec63[0];
		fRec72[1] = fRec72[0];
		fRec71[2] = fRec71[1];
		fRec71[1] = fRec71[0];
		fVec4[1] = fVec4[0];
		fRec70[1] = fRec70[0];
		fRec69[2] = fRec69[1];
		fRec69[1] = fRec69[0];
		fRec68[2] = fRec68[1];
		fRec68[1] = fRec68[0];
		fRec67[2] = fRec67[1];
		fRec67[1] = fRec67[0];
		fRec66[2] = fRec66[1];
		fRec66[1] = fRec66[0];
		fRec65[2] = fRec65[1];
		fRec65[1] = fRec65[0];
		fRec64[2] = fRec64[1];
		fRec64[1] = fRec64[0];
		fRec60[1] = fRec60[0];
		iRec61[1] = iRec61[0];
		fRec62[1] = fRec62[0];
		fRec76[1] = fRec76[0];
		fRec84[1] = fRec84[0];
		fRec83[2] = fRec83[1];
		fRec83[1] = fRec83[0];
		fVec5[1] = fVec5[0];
		fRec82[1] = fRec82[0];
		fRec81[2] = fRec81[1];
		fRec81[1] = fRec81[0];
		fRec80[2] = fRec80[1];
		fRec80[1] = fRec80[0];
		fRec79[2] = fRec79[1];
		fRec79[1] = fRec79[0];
		fRec78[2] = fRec78[1];
		fRec78[1] = fRec78[0];
		fRec77[2] = fRec77[1];
		fRec77[1] = fRec77[0];
		fRec73[1] = fRec73[0];
		iRec74[1] = iRec74[0];
		fRec75[1] = fRec75[0];
		fRec88[1] = fRec88[0];
		fRec95[1] = fRec95[0];
		fRec94[2] = fRec94[1];
		fRec94[1] = fRec94[0];
		fVec6[1] = fVec6[0];
		fRec93[1] = fRec93[0];
		fRec92[2] = fRec92[1];
		fRec92[1] = fRec92[0];
		fRec91[2] = fRec91[1];
		fRec91[1] = fRec91[0];
		fRec90[2] = fRec90[1];
		fRec90[1] = fRec90[0];
		fRec89[2] = fRec89[1];
		fRec89[1] = fRec89[0];
		fRec85[1] = fRec85[0];
		iRec86[1] = iRec86[0];
		fRec87[1] = fRec87[0];
		fRec99[1] = fRec99[0];
		fRec105[1] = fRec105[0];
		fRec104[2] = fRec104[1];
		fRec104[1] = fRec104[0];
		fVec7[1] = fVec7[0];
		fRec103[1] = fRec103[0];
		fRec102[2] = fRec102[1];
		fRec102[1] = fRec102[0];
		fRec101[2] = fRec101[1];
		fRec101[1] = fRec101[0];
		fRec100[2] = fRec100[1];
		fRec100[1] = fRec100[0];
		fRec96[1] = fRec96[0];
		iRec97[1] = iRec97[0];
		fRec98[1] = fRec98[0];
		fRec109[1] = fRec109[0];
		fRec114[1] = fRec114[0];
		fRec113[2] = fRec113[1];
		fRec113[1] = fRec113[0];
		fVec8[1] = fVec8[0];
		fRec112[1] = fRec112[0];
		fRec111[2] = fRec111[1];
		fRec111[1] = fRec111[0];
		fRec110[2] = fRec110[1];
		fRec110[1] = fRec110[0];
		fRec106[1] = fRec106[0];
		iRec107[1] = iRec107[0];
		fRec108[1] = fRec108[0];
		fRec118[1] = fRec118[0];
		fRec122[1] = fRec122[0];
		fRec121[2] = fRec121[1];
		fRec121[1] = fRec121[0];
		fVec9[1] = fVec9[0];
		fRec120[1] = fRec120[0];
		fRec119[2] = fRec119[1];
		fRec119[1] = fRec119[0];
		fRec115[1] = fRec115[0];
		iRec116[1] = iRec116[0];
		fRec117[1] = fRec117[0];
		fRec126[1] = fRec126[0];
		fRec128[1] = fRec128[0];
		fRec127[2] = fRec127[1];
		fRec127[1] = fRec127[0];
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
	reg.registerVar("graphiceq.g10","","S",N_("gain (dB) at 16 kHz"),&fVslider1, 0.0, -30.0, 20.0, 0.10000000000000001);
	reg.registerVar("graphiceq.g11","","S",N_("gain (dB) above 16 kHz"),&fVslider0, 0.0, -30.0, 20.0, 0.10000000000000001);
	reg.registerVar("graphiceq.g1","","S",N_("gain (dB) below 31.25 Hz"),&fVslider10, 0.0, -30.0, 20.0, 0.10000000000000001);
	reg.registerVar("graphiceq.g2","","S",N_("gain (dB) at 62.5 Hz"),&fVslider9, 0.0, -30.0, 20.0, 0.10000000000000001);
	reg.registerVar("graphiceq.g3","","S",N_("gain (dB) at 125 Hz"),&fVslider8, 0.0, -30.0, 20.0, 0.10000000000000001);
	reg.registerVar("graphiceq.g4","","S",N_("gain (dB) at 250 Hz"),&fVslider7, 0.0, -30.0, 20.0, 0.10000000000000001);
	reg.registerVar("graphiceq.g5","","S",N_("gain (dB) at 500 Hz"),&fVslider6, 0.0, -30.0, 20.0, 0.10000000000000001);
	reg.registerVar("graphiceq.g6","","S",N_("gain (dB) at 1 kHz"),&fVslider5, 0.0, -30.0, 20.0, 0.10000000000000001);
	reg.registerVar("graphiceq.g7","","S",N_("gain (dB) at 2 kHz"),&fVslider4, 0.0, -30.0, 20.0, 0.10000000000000001);
	reg.registerVar("graphiceq.g8","","S",N_("gain (dB) at 4 kHz"),&fVslider3, 0.0, -30.0, 20.0, 0.10000000000000001);
	reg.registerVar("graphiceq.g9","","S",N_("gain (dB) at 8 kHz"),&fVslider2, 0.0, -30.0, 20.0, 0.10000000000000001);
	reg.registerNonMidiFloatVar("graphiceq.v10",&fVbargraph1, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("graphiceq.v11",&fVbargraph0, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("graphiceq.v1",&fVbargraph10, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("graphiceq.v2",&fVbargraph9, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("graphiceq.v3",&fVbargraph8, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("graphiceq.v4",&fVbargraph7, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("graphiceq.v5",&fVbargraph6, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("graphiceq.v6",&fVbargraph5, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("graphiceq.v7",&fVbargraph4, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("graphiceq.v8",&fVbargraph3, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("graphiceq.v9",&fVbargraph2, false, true, -70.0, -70.0, 4.0, 0.00001);
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
                <property name=\"spacing\">7</property>\n\
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
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v1</property>\n\
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
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v2</property>\n\
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
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v3</property>\n\
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
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v4</property>\n\
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
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v5</property>\n\
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
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v6</property>\n\
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
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v7</property>\n\
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
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v8</property>\n\
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
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v9</property>\n\
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
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v10</property>\n\
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
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">graphiceq.v11</property>\n\
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
