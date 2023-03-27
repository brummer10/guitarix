// generated from file '../src/LV2/faust/mbreverb.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace mbreverb {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst1;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	double fConst2;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT	*fHslider2_;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT	*fHslider3_;
	double fVec0[2];
	double fRec10[2];
	double fRec9[3];
	double fVec1[2];
	double fRec8[2];
	double fRec7[3];
	double fVec2[2];
	double fRec6[2];
	double fRec5[3];
	double fVec3[2];
	double fRec4[2];
	double fRec3[3];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec20[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	int IOTA0;
	double fVec4[2048];
	double fRec19[2];
	double fRec22[2];
	double fVec5[2048];
	double fRec21[2];
	double fRec24[2];
	double fVec6[2048];
	double fRec23[2];
	double fRec26[2];
	double fVec7[2048];
	double fRec25[2];
	double fRec28[2];
	double fVec8[2048];
	double fRec27[2];
	double fRec30[2];
	double fVec9[2048];
	double fRec29[2];
	double fRec32[2];
	double fVec10[2048];
	double fRec31[2];
	double fRec34[2];
	double fVec11[2048];
	double fRec33[2];
	double fVec12[1024];
	double fRec17[2];
	double fVec13[512];
	double fRec15[2];
	double fVec14[512];
	double fRec13[2];
	double fVec15[256];
	double fRec11[2];
	double fRec0[2];
	int iRec1[2];
	double fRec2[2];
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT	*fVbargraph0_;
	double fRec39[2];
	double fRec38[3];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	double fRec49[2];
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT	*fVslider5_;
	double fVec16[2048];
	double fRec48[2];
	double fRec51[2];
	double fVec17[2048];
	double fRec50[2];
	double fRec53[2];
	double fVec18[2048];
	double fRec52[2];
	double fRec55[2];
	double fVec19[2048];
	double fRec54[2];
	double fRec57[2];
	double fVec20[2048];
	double fRec56[2];
	double fRec59[2];
	double fVec21[2048];
	double fRec58[2];
	double fRec61[2];
	double fVec22[2048];
	double fRec60[2];
	double fRec63[2];
	double fVec23[2048];
	double fRec62[2];
	double fVec24[1024];
	double fRec46[2];
	double fVec25[512];
	double fRec44[2];
	double fVec26[512];
	double fRec42[2];
	double fVec27[256];
	double fRec40[2];
	double fRec35[2];
	int iRec36[2];
	double fRec37[2];
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT	*fVbargraph1_;
	double fRec69[2];
	double fRec68[3];
	double fRec67[3];
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT	*fVslider6_;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT	*fVslider7_;
	double fRec79[2];
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT	*fVslider8_;
	double fVec28[2048];
	double fRec78[2];
	double fRec81[2];
	double fVec29[2048];
	double fRec80[2];
	double fRec83[2];
	double fVec30[2048];
	double fRec82[2];
	double fRec85[2];
	double fVec31[2048];
	double fRec84[2];
	double fRec87[2];
	double fVec32[2048];
	double fRec86[2];
	double fRec89[2];
	double fVec33[2048];
	double fRec88[2];
	double fRec91[2];
	double fVec34[2048];
	double fRec90[2];
	double fRec93[2];
	double fVec35[2048];
	double fRec92[2];
	double fVec36[1024];
	double fRec76[2];
	double fVec37[512];
	double fRec74[2];
	double fVec38[512];
	double fRec72[2];
	double fVec39[256];
	double fRec70[2];
	double fRec64[2];
	int iRec65[2];
	double fRec66[2];
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT	*fVbargraph2_;
	double fRec100[2];
	double fRec99[3];
	double fRec98[3];
	double fRec97[3];
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT	*fVslider9_;
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT	*fVslider10_;
	double fRec110[2];
	FAUSTFLOAT fVslider11;
	FAUSTFLOAT	*fVslider11_;
	double fVec40[2048];
	double fRec109[2];
	double fRec112[2];
	double fVec41[2048];
	double fRec111[2];
	double fRec114[2];
	double fVec42[2048];
	double fRec113[2];
	double fRec116[2];
	double fVec43[2048];
	double fRec115[2];
	double fRec118[2];
	double fVec44[2048];
	double fRec117[2];
	double fRec120[2];
	double fVec45[2048];
	double fRec119[2];
	double fRec122[2];
	double fVec46[2048];
	double fRec121[2];
	double fRec124[2];
	double fVec47[2048];
	double fRec123[2];
	double fVec48[1024];
	double fRec107[2];
	double fVec49[512];
	double fRec105[2];
	double fVec50[512];
	double fRec103[2];
	double fVec51[256];
	double fRec101[2];
	double fRec94[2];
	int iRec95[2];
	double fRec96[2];
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT	*fVbargraph3_;
	double fRec132[2];
	double fRec131[3];
	double fRec130[3];
	double fRec129[3];
	double fRec128[3];
	FAUSTFLOAT fVslider12;
	FAUSTFLOAT	*fVslider12_;
	FAUSTFLOAT fVslider13;
	FAUSTFLOAT	*fVslider13_;
	double fRec142[2];
	FAUSTFLOAT fVslider14;
	FAUSTFLOAT	*fVslider14_;
	double fVec52[2048];
	double fRec141[2];
	double fRec144[2];
	double fVec53[2048];
	double fRec143[2];
	double fRec146[2];
	double fVec54[2048];
	double fRec145[2];
	double fRec148[2];
	double fVec55[2048];
	double fRec147[2];
	double fRec150[2];
	double fVec56[2048];
	double fRec149[2];
	double fRec152[2];
	double fVec57[2048];
	double fRec151[2];
	double fRec154[2];
	double fVec58[2048];
	double fRec153[2];
	double fRec156[2];
	double fVec59[2048];
	double fRec155[2];
	double fVec60[1024];
	double fRec139[2];
	double fVec61[512];
	double fRec137[2];
	double fVec62[512];
	double fRec135[2];
	double fVec63[256];
	double fRec133[2];
	double fRec125[2];
	int iRec126[2];
	double fRec127[2];
	FAUSTFLOAT fVbargraph4;
	FAUSTFLOAT	*fVbargraph4_;

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
	id = "mbe";
	name = N_("MultiBand Reverb");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fVec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec10[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRec9[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fVec1[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec8[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec7[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fVec2[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec6[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec5[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fVec3[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec4[l10] = 0.0;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec3[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec20[l12] = 0.0;
	for (int l13 = 0; l13 < 2048; l13 = l13 + 1) fVec4[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec19[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec22[l15] = 0.0;
	for (int l16 = 0; l16 < 2048; l16 = l16 + 1) fVec5[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec21[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec24[l18] = 0.0;
	for (int l19 = 0; l19 < 2048; l19 = l19 + 1) fVec6[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec23[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec26[l21] = 0.0;
	for (int l22 = 0; l22 < 2048; l22 = l22 + 1) fVec7[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec25[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec28[l24] = 0.0;
	for (int l25 = 0; l25 < 2048; l25 = l25 + 1) fVec8[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec27[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec30[l27] = 0.0;
	for (int l28 = 0; l28 < 2048; l28 = l28 + 1) fVec9[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec29[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec32[l30] = 0.0;
	for (int l31 = 0; l31 < 2048; l31 = l31 + 1) fVec10[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fRec31[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fRec34[l33] = 0.0;
	for (int l34 = 0; l34 < 2048; l34 = l34 + 1) fVec11[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec33[l35] = 0.0;
	for (int l36 = 0; l36 < 1024; l36 = l36 + 1) fVec12[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec17[l37] = 0.0;
	for (int l38 = 0; l38 < 512; l38 = l38 + 1) fVec13[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec15[l39] = 0.0;
	for (int l40 = 0; l40 < 512; l40 = l40 + 1) fVec14[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec13[l41] = 0.0;
	for (int l42 = 0; l42 < 256; l42 = l42 + 1) fVec15[l42] = 0.0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fRec11[l43] = 0.0;
	for (int l44 = 0; l44 < 2; l44 = l44 + 1) fRec0[l44] = 0.0;
	for (int l45 = 0; l45 < 2; l45 = l45 + 1) iRec1[l45] = 0;
	for (int l46 = 0; l46 < 2; l46 = l46 + 1) fRec2[l46] = 0.0;
	for (int l47 = 0; l47 < 2; l47 = l47 + 1) fRec39[l47] = 0.0;
	for (int l48 = 0; l48 < 3; l48 = l48 + 1) fRec38[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec49[l49] = 0.0;
	for (int l50 = 0; l50 < 2048; l50 = l50 + 1) fVec16[l50] = 0.0;
	for (int l51 = 0; l51 < 2; l51 = l51 + 1) fRec48[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fRec51[l52] = 0.0;
	for (int l53 = 0; l53 < 2048; l53 = l53 + 1) fVec17[l53] = 0.0;
	for (int l54 = 0; l54 < 2; l54 = l54 + 1) fRec50[l54] = 0.0;
	for (int l55 = 0; l55 < 2; l55 = l55 + 1) fRec53[l55] = 0.0;
	for (int l56 = 0; l56 < 2048; l56 = l56 + 1) fVec18[l56] = 0.0;
	for (int l57 = 0; l57 < 2; l57 = l57 + 1) fRec52[l57] = 0.0;
	for (int l58 = 0; l58 < 2; l58 = l58 + 1) fRec55[l58] = 0.0;
	for (int l59 = 0; l59 < 2048; l59 = l59 + 1) fVec19[l59] = 0.0;
	for (int l60 = 0; l60 < 2; l60 = l60 + 1) fRec54[l60] = 0.0;
	for (int l61 = 0; l61 < 2; l61 = l61 + 1) fRec57[l61] = 0.0;
	for (int l62 = 0; l62 < 2048; l62 = l62 + 1) fVec20[l62] = 0.0;
	for (int l63 = 0; l63 < 2; l63 = l63 + 1) fRec56[l63] = 0.0;
	for (int l64 = 0; l64 < 2; l64 = l64 + 1) fRec59[l64] = 0.0;
	for (int l65 = 0; l65 < 2048; l65 = l65 + 1) fVec21[l65] = 0.0;
	for (int l66 = 0; l66 < 2; l66 = l66 + 1) fRec58[l66] = 0.0;
	for (int l67 = 0; l67 < 2; l67 = l67 + 1) fRec61[l67] = 0.0;
	for (int l68 = 0; l68 < 2048; l68 = l68 + 1) fVec22[l68] = 0.0;
	for (int l69 = 0; l69 < 2; l69 = l69 + 1) fRec60[l69] = 0.0;
	for (int l70 = 0; l70 < 2; l70 = l70 + 1) fRec63[l70] = 0.0;
	for (int l71 = 0; l71 < 2048; l71 = l71 + 1) fVec23[l71] = 0.0;
	for (int l72 = 0; l72 < 2; l72 = l72 + 1) fRec62[l72] = 0.0;
	for (int l73 = 0; l73 < 1024; l73 = l73 + 1) fVec24[l73] = 0.0;
	for (int l74 = 0; l74 < 2; l74 = l74 + 1) fRec46[l74] = 0.0;
	for (int l75 = 0; l75 < 512; l75 = l75 + 1) fVec25[l75] = 0.0;
	for (int l76 = 0; l76 < 2; l76 = l76 + 1) fRec44[l76] = 0.0;
	for (int l77 = 0; l77 < 512; l77 = l77 + 1) fVec26[l77] = 0.0;
	for (int l78 = 0; l78 < 2; l78 = l78 + 1) fRec42[l78] = 0.0;
	for (int l79 = 0; l79 < 256; l79 = l79 + 1) fVec27[l79] = 0.0;
	for (int l80 = 0; l80 < 2; l80 = l80 + 1) fRec40[l80] = 0.0;
	for (int l81 = 0; l81 < 2; l81 = l81 + 1) fRec35[l81] = 0.0;
	for (int l82 = 0; l82 < 2; l82 = l82 + 1) iRec36[l82] = 0;
	for (int l83 = 0; l83 < 2; l83 = l83 + 1) fRec37[l83] = 0.0;
	for (int l84 = 0; l84 < 2; l84 = l84 + 1) fRec69[l84] = 0.0;
	for (int l85 = 0; l85 < 3; l85 = l85 + 1) fRec68[l85] = 0.0;
	for (int l86 = 0; l86 < 3; l86 = l86 + 1) fRec67[l86] = 0.0;
	for (int l87 = 0; l87 < 2; l87 = l87 + 1) fRec79[l87] = 0.0;
	for (int l88 = 0; l88 < 2048; l88 = l88 + 1) fVec28[l88] = 0.0;
	for (int l89 = 0; l89 < 2; l89 = l89 + 1) fRec78[l89] = 0.0;
	for (int l90 = 0; l90 < 2; l90 = l90 + 1) fRec81[l90] = 0.0;
	for (int l91 = 0; l91 < 2048; l91 = l91 + 1) fVec29[l91] = 0.0;
	for (int l92 = 0; l92 < 2; l92 = l92 + 1) fRec80[l92] = 0.0;
	for (int l93 = 0; l93 < 2; l93 = l93 + 1) fRec83[l93] = 0.0;
	for (int l94 = 0; l94 < 2048; l94 = l94 + 1) fVec30[l94] = 0.0;
	for (int l95 = 0; l95 < 2; l95 = l95 + 1) fRec82[l95] = 0.0;
	for (int l96 = 0; l96 < 2; l96 = l96 + 1) fRec85[l96] = 0.0;
	for (int l97 = 0; l97 < 2048; l97 = l97 + 1) fVec31[l97] = 0.0;
	for (int l98 = 0; l98 < 2; l98 = l98 + 1) fRec84[l98] = 0.0;
	for (int l99 = 0; l99 < 2; l99 = l99 + 1) fRec87[l99] = 0.0;
	for (int l100 = 0; l100 < 2048; l100 = l100 + 1) fVec32[l100] = 0.0;
	for (int l101 = 0; l101 < 2; l101 = l101 + 1) fRec86[l101] = 0.0;
	for (int l102 = 0; l102 < 2; l102 = l102 + 1) fRec89[l102] = 0.0;
	for (int l103 = 0; l103 < 2048; l103 = l103 + 1) fVec33[l103] = 0.0;
	for (int l104 = 0; l104 < 2; l104 = l104 + 1) fRec88[l104] = 0.0;
	for (int l105 = 0; l105 < 2; l105 = l105 + 1) fRec91[l105] = 0.0;
	for (int l106 = 0; l106 < 2048; l106 = l106 + 1) fVec34[l106] = 0.0;
	for (int l107 = 0; l107 < 2; l107 = l107 + 1) fRec90[l107] = 0.0;
	for (int l108 = 0; l108 < 2; l108 = l108 + 1) fRec93[l108] = 0.0;
	for (int l109 = 0; l109 < 2048; l109 = l109 + 1) fVec35[l109] = 0.0;
	for (int l110 = 0; l110 < 2; l110 = l110 + 1) fRec92[l110] = 0.0;
	for (int l111 = 0; l111 < 1024; l111 = l111 + 1) fVec36[l111] = 0.0;
	for (int l112 = 0; l112 < 2; l112 = l112 + 1) fRec76[l112] = 0.0;
	for (int l113 = 0; l113 < 512; l113 = l113 + 1) fVec37[l113] = 0.0;
	for (int l114 = 0; l114 < 2; l114 = l114 + 1) fRec74[l114] = 0.0;
	for (int l115 = 0; l115 < 512; l115 = l115 + 1) fVec38[l115] = 0.0;
	for (int l116 = 0; l116 < 2; l116 = l116 + 1) fRec72[l116] = 0.0;
	for (int l117 = 0; l117 < 256; l117 = l117 + 1) fVec39[l117] = 0.0;
	for (int l118 = 0; l118 < 2; l118 = l118 + 1) fRec70[l118] = 0.0;
	for (int l119 = 0; l119 < 2; l119 = l119 + 1) fRec64[l119] = 0.0;
	for (int l120 = 0; l120 < 2; l120 = l120 + 1) iRec65[l120] = 0;
	for (int l121 = 0; l121 < 2; l121 = l121 + 1) fRec66[l121] = 0.0;
	for (int l122 = 0; l122 < 2; l122 = l122 + 1) fRec100[l122] = 0.0;
	for (int l123 = 0; l123 < 3; l123 = l123 + 1) fRec99[l123] = 0.0;
	for (int l124 = 0; l124 < 3; l124 = l124 + 1) fRec98[l124] = 0.0;
	for (int l125 = 0; l125 < 3; l125 = l125 + 1) fRec97[l125] = 0.0;
	for (int l126 = 0; l126 < 2; l126 = l126 + 1) fRec110[l126] = 0.0;
	for (int l127 = 0; l127 < 2048; l127 = l127 + 1) fVec40[l127] = 0.0;
	for (int l128 = 0; l128 < 2; l128 = l128 + 1) fRec109[l128] = 0.0;
	for (int l129 = 0; l129 < 2; l129 = l129 + 1) fRec112[l129] = 0.0;
	for (int l130 = 0; l130 < 2048; l130 = l130 + 1) fVec41[l130] = 0.0;
	for (int l131 = 0; l131 < 2; l131 = l131 + 1) fRec111[l131] = 0.0;
	for (int l132 = 0; l132 < 2; l132 = l132 + 1) fRec114[l132] = 0.0;
	for (int l133 = 0; l133 < 2048; l133 = l133 + 1) fVec42[l133] = 0.0;
	for (int l134 = 0; l134 < 2; l134 = l134 + 1) fRec113[l134] = 0.0;
	for (int l135 = 0; l135 < 2; l135 = l135 + 1) fRec116[l135] = 0.0;
	for (int l136 = 0; l136 < 2048; l136 = l136 + 1) fVec43[l136] = 0.0;
	for (int l137 = 0; l137 < 2; l137 = l137 + 1) fRec115[l137] = 0.0;
	for (int l138 = 0; l138 < 2; l138 = l138 + 1) fRec118[l138] = 0.0;
	for (int l139 = 0; l139 < 2048; l139 = l139 + 1) fVec44[l139] = 0.0;
	for (int l140 = 0; l140 < 2; l140 = l140 + 1) fRec117[l140] = 0.0;
	for (int l141 = 0; l141 < 2; l141 = l141 + 1) fRec120[l141] = 0.0;
	for (int l142 = 0; l142 < 2048; l142 = l142 + 1) fVec45[l142] = 0.0;
	for (int l143 = 0; l143 < 2; l143 = l143 + 1) fRec119[l143] = 0.0;
	for (int l144 = 0; l144 < 2; l144 = l144 + 1) fRec122[l144] = 0.0;
	for (int l145 = 0; l145 < 2048; l145 = l145 + 1) fVec46[l145] = 0.0;
	for (int l146 = 0; l146 < 2; l146 = l146 + 1) fRec121[l146] = 0.0;
	for (int l147 = 0; l147 < 2; l147 = l147 + 1) fRec124[l147] = 0.0;
	for (int l148 = 0; l148 < 2048; l148 = l148 + 1) fVec47[l148] = 0.0;
	for (int l149 = 0; l149 < 2; l149 = l149 + 1) fRec123[l149] = 0.0;
	for (int l150 = 0; l150 < 1024; l150 = l150 + 1) fVec48[l150] = 0.0;
	for (int l151 = 0; l151 < 2; l151 = l151 + 1) fRec107[l151] = 0.0;
	for (int l152 = 0; l152 < 512; l152 = l152 + 1) fVec49[l152] = 0.0;
	for (int l153 = 0; l153 < 2; l153 = l153 + 1) fRec105[l153] = 0.0;
	for (int l154 = 0; l154 < 512; l154 = l154 + 1) fVec50[l154] = 0.0;
	for (int l155 = 0; l155 < 2; l155 = l155 + 1) fRec103[l155] = 0.0;
	for (int l156 = 0; l156 < 256; l156 = l156 + 1) fVec51[l156] = 0.0;
	for (int l157 = 0; l157 < 2; l157 = l157 + 1) fRec101[l157] = 0.0;
	for (int l158 = 0; l158 < 2; l158 = l158 + 1) fRec94[l158] = 0.0;
	for (int l159 = 0; l159 < 2; l159 = l159 + 1) iRec95[l159] = 0;
	for (int l160 = 0; l160 < 2; l160 = l160 + 1) fRec96[l160] = 0.0;
	for (int l161 = 0; l161 < 2; l161 = l161 + 1) fRec132[l161] = 0.0;
	for (int l162 = 0; l162 < 3; l162 = l162 + 1) fRec131[l162] = 0.0;
	for (int l163 = 0; l163 < 3; l163 = l163 + 1) fRec130[l163] = 0.0;
	for (int l164 = 0; l164 < 3; l164 = l164 + 1) fRec129[l164] = 0.0;
	for (int l165 = 0; l165 < 3; l165 = l165 + 1) fRec128[l165] = 0.0;
	for (int l166 = 0; l166 < 2; l166 = l166 + 1) fRec142[l166] = 0.0;
	for (int l167 = 0; l167 < 2048; l167 = l167 + 1) fVec52[l167] = 0.0;
	for (int l168 = 0; l168 < 2; l168 = l168 + 1) fRec141[l168] = 0.0;
	for (int l169 = 0; l169 < 2; l169 = l169 + 1) fRec144[l169] = 0.0;
	for (int l170 = 0; l170 < 2048; l170 = l170 + 1) fVec53[l170] = 0.0;
	for (int l171 = 0; l171 < 2; l171 = l171 + 1) fRec143[l171] = 0.0;
	for (int l172 = 0; l172 < 2; l172 = l172 + 1) fRec146[l172] = 0.0;
	for (int l173 = 0; l173 < 2048; l173 = l173 + 1) fVec54[l173] = 0.0;
	for (int l174 = 0; l174 < 2; l174 = l174 + 1) fRec145[l174] = 0.0;
	for (int l175 = 0; l175 < 2; l175 = l175 + 1) fRec148[l175] = 0.0;
	for (int l176 = 0; l176 < 2048; l176 = l176 + 1) fVec55[l176] = 0.0;
	for (int l177 = 0; l177 < 2; l177 = l177 + 1) fRec147[l177] = 0.0;
	for (int l178 = 0; l178 < 2; l178 = l178 + 1) fRec150[l178] = 0.0;
	for (int l179 = 0; l179 < 2048; l179 = l179 + 1) fVec56[l179] = 0.0;
	for (int l180 = 0; l180 < 2; l180 = l180 + 1) fRec149[l180] = 0.0;
	for (int l181 = 0; l181 < 2; l181 = l181 + 1) fRec152[l181] = 0.0;
	for (int l182 = 0; l182 < 2048; l182 = l182 + 1) fVec57[l182] = 0.0;
	for (int l183 = 0; l183 < 2; l183 = l183 + 1) fRec151[l183] = 0.0;
	for (int l184 = 0; l184 < 2; l184 = l184 + 1) fRec154[l184] = 0.0;
	for (int l185 = 0; l185 < 2048; l185 = l185 + 1) fVec58[l185] = 0.0;
	for (int l186 = 0; l186 < 2; l186 = l186 + 1) fRec153[l186] = 0.0;
	for (int l187 = 0; l187 < 2; l187 = l187 + 1) fRec156[l187] = 0.0;
	for (int l188 = 0; l188 < 2048; l188 = l188 + 1) fVec59[l188] = 0.0;
	for (int l189 = 0; l189 < 2; l189 = l189 + 1) fRec155[l189] = 0.0;
	for (int l190 = 0; l190 < 1024; l190 = l190 + 1) fVec60[l190] = 0.0;
	for (int l191 = 0; l191 < 2; l191 = l191 + 1) fRec139[l191] = 0.0;
	for (int l192 = 0; l192 < 512; l192 = l192 + 1) fVec61[l192] = 0.0;
	for (int l193 = 0; l193 < 2; l193 = l193 + 1) fRec137[l193] = 0.0;
	for (int l194 = 0; l194 < 512; l194 = l194 + 1) fVec62[l194] = 0.0;
	for (int l195 = 0; l195 < 2; l195 = l195 + 1) fRec135[l195] = 0.0;
	for (int l196 = 0; l196 < 256; l196 = l196 + 1) fVec63[l196] = 0.0;
	for (int l197 = 0; l197 < 2; l197 = l197 + 1) fRec133[l197] = 0.0;
	for (int l198 = 0; l198 < 2; l198 = l198 + 1) fRec125[l198] = 0.0;
	for (int l199 = 0; l199 < 2; l199 = l199 + 1) iRec126[l199] = 0;
	for (int l200 = 0; l200 < 2; l200 = l200 + 1) fRec127[l200] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 1.0 / fConst0;
	fConst2 = 3.141592653589793 / fConst0;
	IOTA0 = 0;
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fHslider0 (*fHslider0_)
#define fHslider1 (*fHslider1_)
#define fHslider2 (*fHslider2_)
#define fHslider3 (*fHslider3_)
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVbargraph0 (*fVbargraph0_)
#define fVslider3 (*fVslider3_)
#define fVslider4 (*fVslider4_)
#define fVslider5 (*fVslider5_)
#define fVbargraph1 (*fVbargraph1_)
#define fVslider6 (*fVslider6_)
#define fVslider7 (*fVslider7_)
#define fVslider8 (*fVslider8_)
#define fVbargraph2 (*fVbargraph2_)
#define fVslider9 (*fVslider9_)
#define fVslider10 (*fVslider10_)
#define fVslider11 (*fVslider11_)
#define fVbargraph3 (*fVbargraph3_)
#define fVslider12 (*fVslider12_)
#define fVslider13 (*fVslider13_)
#define fVslider14 (*fVslider14_)
#define fVbargraph4 (*fVbargraph4_)
	double fSlow0 = std::tan(fConst2 * double(fHslider0));
	double fSlow1 = mydsp_faustpower2_f(fSlow0);
	double fSlow2 = 1.0 / fSlow1;
	double fSlow3 = 2.0 * (1.0 - fSlow2);
	double fSlow4 = 1.0 / fSlow0;
	double fSlow5 = (fSlow4 + -1.0000000000000004) / fSlow0 + 1.0;
	double fSlow6 = (fSlow4 + 1.0000000000000004) / fSlow0 + 1.0;
	double fSlow7 = 1.0 / fSlow6;
	double fSlow8 = std::tan(fConst2 * double(fHslider1));
	double fSlow9 = mydsp_faustpower2_f(fSlow8);
	double fSlow10 = 1.0 / fSlow9;
	double fSlow11 = 2.0 * (1.0 - fSlow10);
	double fSlow12 = 1.0 / fSlow8;
	double fSlow13 = (fSlow12 + -1.0000000000000004) / fSlow8 + 1.0;
	double fSlow14 = (fSlow12 + 1.0000000000000004) / fSlow8 + 1.0;
	double fSlow15 = 1.0 / fSlow14;
	double fSlow16 = std::tan(fConst2 * double(fHslider2));
	double fSlow17 = mydsp_faustpower2_f(fSlow16);
	double fSlow18 = 1.0 / fSlow17;
	double fSlow19 = 2.0 * (1.0 - fSlow18);
	double fSlow20 = 1.0 / fSlow16;
	double fSlow21 = (fSlow20 + -1.0000000000000004) / fSlow16 + 1.0;
	double fSlow22 = (fSlow20 + 1.0000000000000004) / fSlow16 + 1.0;
	double fSlow23 = 1.0 / fSlow22;
	double fSlow24 = std::tan(fConst2 * double(fHslider3));
	double fSlow25 = mydsp_faustpower2_f(fSlow24);
	double fSlow26 = 1.0 / fSlow25;
	double fSlow27 = 2.0 * (1.0 - fSlow26);
	double fSlow28 = 1.0 / fSlow24;
	double fSlow29 = (fSlow28 + -1.0000000000000004) / fSlow24 + 1.0;
	double fSlow30 = (fSlow28 + 1.0000000000000004) / fSlow24 + 1.0;
	double fSlow31 = 1.0 / fSlow30;
	double fSlow32 = 1.0 - fSlow28;
	double fSlow33 = fSlow28 + 1.0;
	double fSlow34 = 1.0 / fSlow33;
	double fSlow35 = 1.0 - fSlow20;
	double fSlow36 = fSlow20 + 1.0;
	double fSlow37 = 1.0 / fSlow36;
	double fSlow38 = 1.0 - fSlow12;
	double fSlow39 = fSlow12 + 1.0;
	double fSlow40 = 1.0 / fSlow39;
	double fSlow41 = 1.0 - fSlow4;
	double fSlow42 = fSlow4 + 1.0;
	double fSlow43 = 1.0 / fSlow42;
	double fSlow44 = double(fVslider0);
	double fSlow45 = 1.0 - 0.01 * fSlow44;
	double fSlow46 = (fSlow45 + fSlow44 * (0.01 * fSlow45 + 0.00015)) / fSlow6;
	double fSlow47 = double(fVslider1);
	double fSlow48 = 1.0 - fSlow47;
	double fSlow49 = 0.28 * double(fVslider2) + 0.7;
	double fSlow50 = 0.00015 * (fSlow44 / fSlow6);
	double fSlow51 = 1.0 / (fSlow0 * fSlow14);
	double fSlow52 = 0.0 - 1.0 / (fSlow0 * fSlow42);
	double fSlow53 = 0.0 - 2.0 / fSlow1;
	double fSlow54 = double(fVslider3);
	double fSlow55 = 1.0 - 0.01 * fSlow54;
	double fSlow56 = (fSlow55 + fSlow54 * (0.01 * fSlow55 + 0.00015)) / fSlow6;
	double fSlow57 = double(fVslider4);
	double fSlow58 = 1.0 - fSlow57;
	double fSlow59 = 0.28 * double(fVslider5) + 0.7;
	double fSlow60 = 0.00015 * (fSlow54 / fSlow6);
	double fSlow61 = 1.0 - fSlow41 / fSlow0;
	double fSlow62 = 1.0 / (fSlow42 / fSlow0 + 1.0);
	double fSlow63 = 1.0 / (fSlow8 * fSlow22);
	double fSlow64 = 0.0 - 1.0 / (fSlow8 * fSlow39);
	double fSlow65 = 0.0 - 2.0 / fSlow9;
	double fSlow66 = double(fVslider6);
	double fSlow67 = 1.0 - 0.01 * fSlow66;
	double fSlow68 = fSlow67 + fSlow66 * (0.01 * fSlow67 + 0.00015);
	double fSlow69 = double(fVslider7);
	double fSlow70 = 1.0 - fSlow69;
	double fSlow71 = 0.28 * double(fVslider8) + 0.7;
	double fSlow72 = 0.00015 * fSlow66;
	double fSlow73 = 1.0 - fSlow38 / fSlow8;
	double fSlow74 = 1.0 / (fSlow39 / fSlow8 + 1.0);
	double fSlow75 = 1.0 / (fSlow30 * fSlow16);
	double fSlow76 = 0.0 - 1.0 / (fSlow16 * fSlow36);
	double fSlow77 = 0.0 - 2.0 / fSlow17;
	double fSlow78 = double(fVslider9);
	double fSlow79 = 1.0 - 0.01 * fSlow78;
	double fSlow80 = fSlow79 + fSlow78 * (0.01 * fSlow79 + 0.00015);
	double fSlow81 = double(fVslider10);
	double fSlow82 = 1.0 - fSlow81;
	double fSlow83 = 0.28 * double(fVslider11) + 0.7;
	double fSlow84 = 0.00015 * fSlow78;
	double fSlow85 = 1.0 - fSlow35 / fSlow16;
	double fSlow86 = 1.0 / (fSlow36 / fSlow16 + 1.0);
	double fSlow87 = 0.0 - 1.0 / (fSlow24 * fSlow33);
	double fSlow88 = 0.0 - 2.0 / fSlow25;
	double fSlow89 = double(fVslider12);
	double fSlow90 = 1.0 - 0.01 * fSlow89;
	double fSlow91 = fSlow90 + fSlow89 * (0.01 * fSlow90 + 0.00015);
	double fSlow92 = double(fVslider13);
	double fSlow93 = 1.0 - fSlow92;
	double fSlow94 = 0.28 * double(fVslider14) + 0.7;
	double fSlow95 = 0.00015 * fSlow89;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		int iTemp0 = iRec1[1] < 4096;
		double fTemp1 = double(input0[i0]);
		fVec0[0] = fTemp1;
		fRec10[0] = 0.0 - fSlow34 * (fSlow32 * fRec10[1] - (fTemp1 + fVec0[1]));
		fRec9[0] = fRec10[0] - fSlow31 * (fSlow29 * fRec9[2] + fSlow27 * fRec9[1]);
		double fTemp2 = fRec9[2] + fRec9[0] + 2.0 * fRec9[1];
		double fTemp3 = fSlow31 * fTemp2;
		fVec1[0] = fTemp3;
		fRec8[0] = 0.0 - fSlow37 * (fSlow35 * fRec8[1] - (fTemp3 + fVec1[1]));
		fRec7[0] = fRec8[0] - fSlow23 * (fSlow21 * fRec7[2] + fSlow19 * fRec7[1]);
		double fTemp4 = fRec7[2] + fRec7[0] + 2.0 * fRec7[1];
		double fTemp5 = fSlow23 * fTemp4;
		fVec2[0] = fTemp5;
		fRec6[0] = 0.0 - fSlow40 * (fSlow38 * fRec6[1] - (fTemp5 + fVec2[1]));
		fRec5[0] = fRec6[0] - fSlow15 * (fSlow13 * fRec5[2] + fSlow11 * fRec5[1]);
		double fTemp6 = fRec5[2] + fRec5[0] + 2.0 * fRec5[1];
		double fTemp7 = fSlow15 * fTemp6;
		fVec3[0] = fTemp7;
		fRec4[0] = 0.0 - fSlow43 * (fSlow41 * fRec4[1] - (fTemp7 + fVec3[1]));
		fRec3[0] = fRec4[0] - fSlow7 * (fSlow5 * fRec3[2] + fSlow3 * fRec3[1]);
		double fTemp8 = fRec3[2] + fRec3[0] + 2.0 * fRec3[1];
		fRec20[0] = fSlow47 * fRec20[1] + fSlow48 * fRec19[1];
		double fTemp9 = fSlow50 * fTemp8;
		fVec4[IOTA0 & 2047] = fTemp9 + fSlow49 * fRec20[0];
		fRec19[0] = fVec4[(IOTA0 - 1640) & 2047];
		fRec22[0] = fSlow47 * fRec22[1] + fSlow48 * fRec21[1];
		fVec5[IOTA0 & 2047] = fTemp9 + fSlow49 * fRec22[0];
		fRec21[0] = fVec5[(IOTA0 - 1580) & 2047];
		fRec24[0] = fSlow47 * fRec24[1] + fSlow48 * fRec23[1];
		fVec6[IOTA0 & 2047] = fTemp9 + fSlow49 * fRec24[0];
		fRec23[0] = fVec6[(IOTA0 - 1514) & 2047];
		fRec26[0] = fSlow47 * fRec26[1] + fSlow48 * fRec25[1];
		fVec7[IOTA0 & 2047] = fTemp9 + fSlow49 * fRec26[0];
		fRec25[0] = fVec7[(IOTA0 - 1445) & 2047];
		fRec28[0] = fSlow47 * fRec28[1] + fSlow48 * fRec27[1];
		fVec8[IOTA0 & 2047] = fTemp9 + fSlow49 * fRec28[0];
		fRec27[0] = fVec8[(IOTA0 - 1379) & 2047];
		fRec30[0] = fSlow47 * fRec30[1] + fSlow48 * fRec29[1];
		fVec9[IOTA0 & 2047] = fTemp9 + fSlow49 * fRec30[0];
		fRec29[0] = fVec9[(IOTA0 - 1300) & 2047];
		fRec32[0] = fSlow47 * fRec32[1] + fSlow48 * fRec31[1];
		fVec10[IOTA0 & 2047] = fTemp9 + fSlow49 * fRec32[0];
		fRec31[0] = fVec10[(IOTA0 - 1211) & 2047];
		fRec34[0] = fSlow47 * fRec34[1] + fSlow48 * fRec33[1];
		fVec11[IOTA0 & 2047] = fTemp9 + fSlow49 * fRec34[0];
		fRec33[0] = fVec11[(IOTA0 - 1139) & 2047];
		double fTemp10 = fRec33[0] + fRec31[0] + fRec29[0] + fRec27[0] + fRec25[0] + fRec23[0] + fRec21[0] + fRec19[0];
		fVec12[IOTA0 & 1023] = fTemp10 + 0.5 * fRec17[1];
		fRec17[0] = fVec12[(IOTA0 - 579) & 1023];
		double fRec18 = fRec17[1] - fTemp10;
		fVec13[IOTA0 & 511] = fRec18 + 0.5 * fRec15[1];
		fRec15[0] = fVec13[(IOTA0 - 464) & 511];
		double fRec16 = fRec15[1] - fRec18;
		fVec14[IOTA0 & 511] = fRec16 + 0.5 * fRec13[1];
		fRec13[0] = fVec14[(IOTA0 - 364) & 511];
		double fRec14 = fRec13[1] - fRec16;
		fVec15[IOTA0 & 255] = fRec14 + 0.5 * fRec11[1];
		fRec11[0] = fVec15[(IOTA0 - 248) & 255];
		double fRec12 = fRec11[1] - fRec14;
		double fTemp11 = fRec12 + fSlow46 * fTemp8;
		double fTemp12 = std::max<double>(fConst1, std::fabs(fTemp11));
		fRec0[0] = ((iTemp0) ? std::max<double>(fRec0[1], fTemp12) : fTemp12);
		iRec1[0] = ((iTemp0) ? iRec1[1] + 1 : 1);
		fRec2[0] = ((iTemp0) ? fRec2[1] : fRec0[1]);
		fVbargraph0 = FAUSTFLOAT(fRec2[0]);
		int iTemp13 = iRec36[1] < 4096;
		fRec39[0] = fSlow52 * fVec3[1] - fSlow43 * (fSlow41 * fRec39[1] - fSlow51 * fTemp6);
		fRec38[0] = fRec39[0] - fSlow7 * (fSlow5 * fRec38[2] + fSlow3 * fRec38[1]);
		double fTemp14 = fSlow2 * fRec38[0] + fSlow53 * fRec38[1] + fSlow2 * fRec38[2];
		fRec49[0] = fSlow57 * fRec49[1] + fSlow58 * fRec48[1];
		double fTemp15 = fSlow60 * fTemp14;
		fVec16[IOTA0 & 2047] = fTemp15 + fSlow59 * fRec49[0];
		fRec48[0] = fVec16[(IOTA0 - 1640) & 2047];
		fRec51[0] = fSlow57 * fRec51[1] + fSlow58 * fRec50[1];
		fVec17[IOTA0 & 2047] = fTemp15 + fSlow59 * fRec51[0];
		fRec50[0] = fVec17[(IOTA0 - 1580) & 2047];
		fRec53[0] = fSlow57 * fRec53[1] + fSlow58 * fRec52[1];
		fVec18[IOTA0 & 2047] = fTemp15 + fSlow59 * fRec53[0];
		fRec52[0] = fVec18[(IOTA0 - 1514) & 2047];
		fRec55[0] = fSlow57 * fRec55[1] + fSlow58 * fRec54[1];
		fVec19[IOTA0 & 2047] = fTemp15 + fSlow59 * fRec55[0];
		fRec54[0] = fVec19[(IOTA0 - 1445) & 2047];
		fRec57[0] = fSlow57 * fRec57[1] + fSlow58 * fRec56[1];
		fVec20[IOTA0 & 2047] = fTemp15 + fSlow59 * fRec57[0];
		fRec56[0] = fVec20[(IOTA0 - 1379) & 2047];
		fRec59[0] = fSlow57 * fRec59[1] + fSlow58 * fRec58[1];
		fVec21[IOTA0 & 2047] = fTemp15 + fSlow59 * fRec59[0];
		fRec58[0] = fVec21[(IOTA0 - 1300) & 2047];
		fRec61[0] = fSlow57 * fRec61[1] + fSlow58 * fRec60[1];
		fVec22[IOTA0 & 2047] = fTemp15 + fSlow59 * fRec61[0];
		fRec60[0] = fVec22[(IOTA0 - 1211) & 2047];
		fRec63[0] = fSlow57 * fRec63[1] + fSlow58 * fRec62[1];
		fVec23[IOTA0 & 2047] = fTemp15 + fSlow59 * fRec63[0];
		fRec62[0] = fVec23[(IOTA0 - 1139) & 2047];
		double fTemp16 = fRec62[0] + fRec60[0] + fRec58[0] + fRec56[0] + fRec54[0] + fRec52[0] + fRec50[0] + fRec48[0];
		fVec24[IOTA0 & 1023] = fTemp16 + 0.5 * fRec46[1];
		fRec46[0] = fVec24[(IOTA0 - 579) & 1023];
		double fRec47 = fRec46[1] - fTemp16;
		fVec25[IOTA0 & 511] = fRec47 + 0.5 * fRec44[1];
		fRec44[0] = fVec25[(IOTA0 - 464) & 511];
		double fRec45 = fRec44[1] - fRec47;
		fVec26[IOTA0 & 511] = fRec45 + 0.5 * fRec42[1];
		fRec42[0] = fVec26[(IOTA0 - 364) & 511];
		double fRec43 = fRec42[1] - fRec45;
		fVec27[IOTA0 & 255] = fRec43 + 0.5 * fRec40[1];
		fRec40[0] = fVec27[(IOTA0 - 248) & 255];
		double fRec41 = fRec40[1] - fRec43;
		double fTemp17 = fRec41 + fSlow56 * fTemp14;
		double fTemp18 = std::max<double>(fConst1, std::fabs(fTemp17));
		fRec35[0] = ((iTemp13) ? std::max<double>(fRec35[1], fTemp18) : fTemp18);
		iRec36[0] = ((iTemp13) ? iRec36[1] + 1 : 1);
		fRec37[0] = ((iTemp13) ? fRec37[1] : fRec35[1]);
		fVbargraph1 = FAUSTFLOAT(fRec37[0]);
		int iTemp19 = iRec65[1] < 4096;
		double fTemp20 = fSlow3 * fRec67[1];
		fRec69[0] = fSlow64 * fVec2[1] - fSlow40 * (fSlow38 * fRec69[1] - fSlow63 * fTemp4);
		fRec68[0] = fRec69[0] - fSlow15 * (fSlow13 * fRec68[2] + fSlow11 * fRec68[1]);
		fRec67[0] = fSlow15 * (fSlow10 * fRec68[0] + fSlow65 * fRec68[1] + fSlow10 * fRec68[2]) - fSlow62 * (fSlow61 * fRec67[2] + fTemp20);
		double fTemp21 = fRec67[2] + fSlow62 * (fTemp20 + fSlow61 * fRec67[0]);
		fRec79[0] = fSlow69 * fRec79[1] + fSlow70 * fRec78[1];
		double fTemp22 = fSlow72 * fTemp21;
		fVec28[IOTA0 & 2047] = fTemp22 + fSlow71 * fRec79[0];
		fRec78[0] = fVec28[(IOTA0 - 1640) & 2047];
		fRec81[0] = fSlow69 * fRec81[1] + fSlow70 * fRec80[1];
		fVec29[IOTA0 & 2047] = fTemp22 + fSlow71 * fRec81[0];
		fRec80[0] = fVec29[(IOTA0 - 1580) & 2047];
		fRec83[0] = fSlow69 * fRec83[1] + fSlow70 * fRec82[1];
		fVec30[IOTA0 & 2047] = fTemp22 + fSlow71 * fRec83[0];
		fRec82[0] = fVec30[(IOTA0 - 1514) & 2047];
		fRec85[0] = fSlow69 * fRec85[1] + fSlow70 * fRec84[1];
		fVec31[IOTA0 & 2047] = fTemp22 + fSlow71 * fRec85[0];
		fRec84[0] = fVec31[(IOTA0 - 1445) & 2047];
		fRec87[0] = fSlow69 * fRec87[1] + fSlow70 * fRec86[1];
		fVec32[IOTA0 & 2047] = fTemp22 + fSlow71 * fRec87[0];
		fRec86[0] = fVec32[(IOTA0 - 1379) & 2047];
		fRec89[0] = fSlow69 * fRec89[1] + fSlow70 * fRec88[1];
		fVec33[IOTA0 & 2047] = fTemp22 + fSlow71 * fRec89[0];
		fRec88[0] = fVec33[(IOTA0 - 1300) & 2047];
		fRec91[0] = fSlow69 * fRec91[1] + fSlow70 * fRec90[1];
		fVec34[IOTA0 & 2047] = fTemp22 + fSlow71 * fRec91[0];
		fRec90[0] = fVec34[(IOTA0 - 1211) & 2047];
		fRec93[0] = fSlow69 * fRec93[1] + fSlow70 * fRec92[1];
		fVec35[IOTA0 & 2047] = fTemp22 + fSlow71 * fRec93[0];
		fRec92[0] = fVec35[(IOTA0 - 1139) & 2047];
		double fTemp23 = fRec92[0] + fRec90[0] + fRec88[0] + fRec86[0] + fRec84[0] + fRec82[0] + fRec80[0] + fRec78[0];
		fVec36[IOTA0 & 1023] = fTemp23 + 0.5 * fRec76[1];
		fRec76[0] = fVec36[(IOTA0 - 579) & 1023];
		double fRec77 = fRec76[1] - fTemp23;
		fVec37[IOTA0 & 511] = fRec77 + 0.5 * fRec74[1];
		fRec74[0] = fVec37[(IOTA0 - 464) & 511];
		double fRec75 = fRec74[1] - fRec77;
		fVec38[IOTA0 & 511] = fRec75 + 0.5 * fRec72[1];
		fRec72[0] = fVec38[(IOTA0 - 364) & 511];
		double fRec73 = fRec72[1] - fRec75;
		fVec39[IOTA0 & 255] = fRec73 + 0.5 * fRec70[1];
		fRec70[0] = fVec39[(IOTA0 - 248) & 255];
		double fRec71 = fRec70[1] - fRec73;
		double fTemp24 = fRec71 + fSlow68 * fTemp21;
		double fTemp25 = std::max<double>(fConst1, std::fabs(fTemp24));
		fRec64[0] = ((iTemp19) ? std::max<double>(fRec64[1], fTemp25) : fTemp25);
		iRec65[0] = ((iTemp19) ? iRec65[1] + 1 : 1);
		fRec66[0] = ((iTemp19) ? fRec66[1] : fRec64[1]);
		fVbargraph2 = FAUSTFLOAT(fRec66[0]);
		int iTemp26 = iRec95[1] < 4096;
		double fTemp27 = fSlow3 * fRec97[1];
		double fTemp28 = fSlow11 * fRec98[1];
		fRec100[0] = fSlow76 * fVec1[1] - fSlow37 * (fSlow35 * fRec100[1] - fSlow75 * fTemp2);
		fRec99[0] = fRec100[0] - fSlow23 * (fSlow21 * fRec99[2] + fSlow19 * fRec99[1]);
		fRec98[0] = fSlow23 * (fSlow18 * fRec99[0] + fSlow77 * fRec99[1] + fSlow18 * fRec99[2]) - fSlow74 * (fSlow73 * fRec98[2] + fTemp28);
		fRec97[0] = fRec98[2] + fSlow74 * (fTemp28 + fSlow73 * fRec98[0]) - fSlow62 * (fSlow61 * fRec97[2] + fTemp27);
		double fTemp29 = fRec97[2] + fSlow62 * (fTemp27 + fSlow61 * fRec97[0]);
		fRec110[0] = fSlow81 * fRec110[1] + fSlow82 * fRec109[1];
		double fTemp30 = fSlow84 * fTemp29;
		fVec40[IOTA0 & 2047] = fTemp30 + fSlow83 * fRec110[0];
		fRec109[0] = fVec40[(IOTA0 - 1640) & 2047];
		fRec112[0] = fSlow81 * fRec112[1] + fSlow82 * fRec111[1];
		fVec41[IOTA0 & 2047] = fTemp30 + fSlow83 * fRec112[0];
		fRec111[0] = fVec41[(IOTA0 - 1580) & 2047];
		fRec114[0] = fSlow81 * fRec114[1] + fSlow82 * fRec113[1];
		fVec42[IOTA0 & 2047] = fTemp30 + fSlow83 * fRec114[0];
		fRec113[0] = fVec42[(IOTA0 - 1514) & 2047];
		fRec116[0] = fSlow81 * fRec116[1] + fSlow82 * fRec115[1];
		fVec43[IOTA0 & 2047] = fTemp30 + fSlow83 * fRec116[0];
		fRec115[0] = fVec43[(IOTA0 - 1445) & 2047];
		fRec118[0] = fSlow81 * fRec118[1] + fSlow82 * fRec117[1];
		fVec44[IOTA0 & 2047] = fTemp30 + fSlow83 * fRec118[0];
		fRec117[0] = fVec44[(IOTA0 - 1379) & 2047];
		fRec120[0] = fSlow81 * fRec120[1] + fSlow82 * fRec119[1];
		fVec45[IOTA0 & 2047] = fTemp30 + fSlow83 * fRec120[0];
		fRec119[0] = fVec45[(IOTA0 - 1300) & 2047];
		fRec122[0] = fSlow81 * fRec122[1] + fSlow82 * fRec121[1];
		fVec46[IOTA0 & 2047] = fTemp30 + fSlow83 * fRec122[0];
		fRec121[0] = fVec46[(IOTA0 - 1211) & 2047];
		fRec124[0] = fSlow81 * fRec124[1] + fSlow82 * fRec123[1];
		fVec47[IOTA0 & 2047] = fTemp30 + fSlow83 * fRec124[0];
		fRec123[0] = fVec47[(IOTA0 - 1139) & 2047];
		double fTemp31 = fRec123[0] + fRec121[0] + fRec119[0] + fRec117[0] + fRec115[0] + fRec113[0] + fRec111[0] + fRec109[0];
		fVec48[IOTA0 & 1023] = fTemp31 + 0.5 * fRec107[1];
		fRec107[0] = fVec48[(IOTA0 - 579) & 1023];
		double fRec108 = fRec107[1] - fTemp31;
		fVec49[IOTA0 & 511] = fRec108 + 0.5 * fRec105[1];
		fRec105[0] = fVec49[(IOTA0 - 464) & 511];
		double fRec106 = fRec105[1] - fRec108;
		fVec50[IOTA0 & 511] = fRec106 + 0.5 * fRec103[1];
		fRec103[0] = fVec50[(IOTA0 - 364) & 511];
		double fRec104 = fRec103[1] - fRec106;
		fVec51[IOTA0 & 255] = fRec104 + 0.5 * fRec101[1];
		fRec101[0] = fVec51[(IOTA0 - 248) & 255];
		double fRec102 = fRec101[1] - fRec104;
		double fTemp32 = fRec102 + fSlow80 * fTemp29;
		double fTemp33 = std::max<double>(fConst1, std::fabs(fTemp32));
		fRec94[0] = ((iTemp26) ? std::max<double>(fRec94[1], fTemp33) : fTemp33);
		iRec95[0] = ((iTemp26) ? iRec95[1] + 1 : 1);
		fRec96[0] = ((iTemp26) ? fRec96[1] : fRec94[1]);
		fVbargraph3 = FAUSTFLOAT(fRec96[0]);
		int iTemp34 = iRec126[1] < 4096;
		double fTemp35 = fSlow3 * fRec128[1];
		double fTemp36 = fSlow11 * fRec129[1];
		double fTemp37 = fSlow19 * fRec130[1];
		fRec132[0] = fSlow87 * fVec0[1] - fSlow34 * (fSlow32 * fRec132[1] - fSlow28 * fTemp1);
		fRec131[0] = fRec132[0] - fSlow31 * (fSlow29 * fRec131[2] + fSlow27 * fRec131[1]);
		fRec130[0] = fSlow31 * (fSlow26 * fRec131[0] + fSlow88 * fRec131[1] + fSlow26 * fRec131[2]) - fSlow86 * (fSlow85 * fRec130[2] + fTemp37);
		fRec129[0] = fRec130[2] + fSlow86 * (fTemp37 + fSlow85 * fRec130[0]) - fSlow74 * (fSlow73 * fRec129[2] + fTemp36);
		fRec128[0] = fRec129[2] + fSlow74 * (fTemp36 + fSlow73 * fRec129[0]) - fSlow62 * (fSlow61 * fRec128[2] + fTemp35);
		double fTemp38 = fRec128[2] + fSlow62 * (fTemp35 + fSlow61 * fRec128[0]);
		fRec142[0] = fSlow92 * fRec142[1] + fSlow93 * fRec141[1];
		double fTemp39 = fSlow95 * fTemp38;
		fVec52[IOTA0 & 2047] = fTemp39 + fSlow94 * fRec142[0];
		fRec141[0] = fVec52[(IOTA0 - 1640) & 2047];
		fRec144[0] = fSlow92 * fRec144[1] + fSlow93 * fRec143[1];
		fVec53[IOTA0 & 2047] = fTemp39 + fSlow94 * fRec144[0];
		fRec143[0] = fVec53[(IOTA0 - 1580) & 2047];
		fRec146[0] = fSlow92 * fRec146[1] + fSlow93 * fRec145[1];
		fVec54[IOTA0 & 2047] = fTemp39 + fSlow94 * fRec146[0];
		fRec145[0] = fVec54[(IOTA0 - 1514) & 2047];
		fRec148[0] = fSlow92 * fRec148[1] + fSlow93 * fRec147[1];
		fVec55[IOTA0 & 2047] = fTemp39 + fSlow94 * fRec148[0];
		fRec147[0] = fVec55[(IOTA0 - 1445) & 2047];
		fRec150[0] = fSlow92 * fRec150[1] + fSlow93 * fRec149[1];
		fVec56[IOTA0 & 2047] = fTemp39 + fSlow94 * fRec150[0];
		fRec149[0] = fVec56[(IOTA0 - 1379) & 2047];
		fRec152[0] = fSlow92 * fRec152[1] + fSlow93 * fRec151[1];
		fVec57[IOTA0 & 2047] = fTemp39 + fSlow94 * fRec152[0];
		fRec151[0] = fVec57[(IOTA0 - 1300) & 2047];
		fRec154[0] = fSlow92 * fRec154[1] + fSlow93 * fRec153[1];
		fVec58[IOTA0 & 2047] = fTemp39 + fSlow94 * fRec154[0];
		fRec153[0] = fVec58[(IOTA0 - 1211) & 2047];
		fRec156[0] = fSlow92 * fRec156[1] + fSlow93 * fRec155[1];
		fVec59[IOTA0 & 2047] = fTemp39 + fSlow94 * fRec156[0];
		fRec155[0] = fVec59[(IOTA0 - 1139) & 2047];
		double fTemp40 = fRec155[0] + fRec153[0] + fRec151[0] + fRec149[0] + fRec147[0] + fRec145[0] + fRec143[0] + fRec141[0];
		fVec60[IOTA0 & 1023] = fTemp40 + 0.5 * fRec139[1];
		fRec139[0] = fVec60[(IOTA0 - 579) & 1023];
		double fRec140 = fRec139[1] - fTemp40;
		fVec61[IOTA0 & 511] = fRec140 + 0.5 * fRec137[1];
		fRec137[0] = fVec61[(IOTA0 - 464) & 511];
		double fRec138 = fRec137[1] - fRec140;
		fVec62[IOTA0 & 511] = fRec138 + 0.5 * fRec135[1];
		fRec135[0] = fVec62[(IOTA0 - 364) & 511];
		double fRec136 = fRec135[1] - fRec138;
		fVec63[IOTA0 & 255] = fRec136 + 0.5 * fRec133[1];
		fRec133[0] = fVec63[(IOTA0 - 248) & 255];
		double fRec134 = fRec133[1] - fRec136;
		double fTemp41 = fRec134 + fSlow91 * fTemp38;
		double fTemp42 = std::max<double>(fConst1, std::fabs(fTemp41));
		fRec125[0] = ((iTemp34) ? std::max<double>(fRec125[1], fTemp42) : fTemp42);
		iRec126[0] = ((iTemp34) ? iRec126[1] + 1 : 1);
		fRec127[0] = ((iTemp34) ? fRec127[1] : fRec125[1]);
		fVbargraph4 = FAUSTFLOAT(fRec127[0]);
		output0[i0] = FAUSTFLOAT(fTemp41 + fTemp32 + fTemp24 + fTemp17 + fTemp11);
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
		fRec20[1] = fRec20[0];
		IOTA0 = IOTA0 + 1;
		fRec19[1] = fRec19[0];
		fRec22[1] = fRec22[0];
		fRec21[1] = fRec21[0];
		fRec24[1] = fRec24[0];
		fRec23[1] = fRec23[0];
		fRec26[1] = fRec26[0];
		fRec25[1] = fRec25[0];
		fRec28[1] = fRec28[0];
		fRec27[1] = fRec27[0];
		fRec30[1] = fRec30[0];
		fRec29[1] = fRec29[0];
		fRec32[1] = fRec32[0];
		fRec31[1] = fRec31[0];
		fRec34[1] = fRec34[0];
		fRec33[1] = fRec33[0];
		fRec17[1] = fRec17[0];
		fRec15[1] = fRec15[0];
		fRec13[1] = fRec13[0];
		fRec11[1] = fRec11[0];
		fRec0[1] = fRec0[0];
		iRec1[1] = iRec1[0];
		fRec2[1] = fRec2[0];
		fRec39[1] = fRec39[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		fRec49[1] = fRec49[0];
		fRec48[1] = fRec48[0];
		fRec51[1] = fRec51[0];
		fRec50[1] = fRec50[0];
		fRec53[1] = fRec53[0];
		fRec52[1] = fRec52[0];
		fRec55[1] = fRec55[0];
		fRec54[1] = fRec54[0];
		fRec57[1] = fRec57[0];
		fRec56[1] = fRec56[0];
		fRec59[1] = fRec59[0];
		fRec58[1] = fRec58[0];
		fRec61[1] = fRec61[0];
		fRec60[1] = fRec60[0];
		fRec63[1] = fRec63[0];
		fRec62[1] = fRec62[0];
		fRec46[1] = fRec46[0];
		fRec44[1] = fRec44[0];
		fRec42[1] = fRec42[0];
		fRec40[1] = fRec40[0];
		fRec35[1] = fRec35[0];
		iRec36[1] = iRec36[0];
		fRec37[1] = fRec37[0];
		fRec69[1] = fRec69[0];
		fRec68[2] = fRec68[1];
		fRec68[1] = fRec68[0];
		fRec67[2] = fRec67[1];
		fRec67[1] = fRec67[0];
		fRec79[1] = fRec79[0];
		fRec78[1] = fRec78[0];
		fRec81[1] = fRec81[0];
		fRec80[1] = fRec80[0];
		fRec83[1] = fRec83[0];
		fRec82[1] = fRec82[0];
		fRec85[1] = fRec85[0];
		fRec84[1] = fRec84[0];
		fRec87[1] = fRec87[0];
		fRec86[1] = fRec86[0];
		fRec89[1] = fRec89[0];
		fRec88[1] = fRec88[0];
		fRec91[1] = fRec91[0];
		fRec90[1] = fRec90[0];
		fRec93[1] = fRec93[0];
		fRec92[1] = fRec92[0];
		fRec76[1] = fRec76[0];
		fRec74[1] = fRec74[0];
		fRec72[1] = fRec72[0];
		fRec70[1] = fRec70[0];
		fRec64[1] = fRec64[0];
		iRec65[1] = iRec65[0];
		fRec66[1] = fRec66[0];
		fRec100[1] = fRec100[0];
		fRec99[2] = fRec99[1];
		fRec99[1] = fRec99[0];
		fRec98[2] = fRec98[1];
		fRec98[1] = fRec98[0];
		fRec97[2] = fRec97[1];
		fRec97[1] = fRec97[0];
		fRec110[1] = fRec110[0];
		fRec109[1] = fRec109[0];
		fRec112[1] = fRec112[0];
		fRec111[1] = fRec111[0];
		fRec114[1] = fRec114[0];
		fRec113[1] = fRec113[0];
		fRec116[1] = fRec116[0];
		fRec115[1] = fRec115[0];
		fRec118[1] = fRec118[0];
		fRec117[1] = fRec117[0];
		fRec120[1] = fRec120[0];
		fRec119[1] = fRec119[0];
		fRec122[1] = fRec122[0];
		fRec121[1] = fRec121[0];
		fRec124[1] = fRec124[0];
		fRec123[1] = fRec123[0];
		fRec107[1] = fRec107[0];
		fRec105[1] = fRec105[0];
		fRec103[1] = fRec103[0];
		fRec101[1] = fRec101[0];
		fRec94[1] = fRec94[0];
		iRec95[1] = iRec95[0];
		fRec96[1] = fRec96[0];
		fRec132[1] = fRec132[0];
		fRec131[2] = fRec131[1];
		fRec131[1] = fRec131[0];
		fRec130[2] = fRec130[1];
		fRec130[1] = fRec130[0];
		fRec129[2] = fRec129[1];
		fRec129[1] = fRec129[0];
		fRec128[2] = fRec128[1];
		fRec128[1] = fRec128[0];
		fRec142[1] = fRec142[0];
		fRec141[1] = fRec141[0];
		fRec144[1] = fRec144[0];
		fRec143[1] = fRec143[0];
		fRec146[1] = fRec146[0];
		fRec145[1] = fRec145[0];
		fRec148[1] = fRec148[0];
		fRec147[1] = fRec147[0];
		fRec150[1] = fRec150[0];
		fRec149[1] = fRec149[0];
		fRec152[1] = fRec152[0];
		fRec151[1] = fRec151[0];
		fRec154[1] = fRec154[0];
		fRec153[1] = fRec153[0];
		fRec156[1] = fRec156[0];
		fRec155[1] = fRec155[0];
		fRec139[1] = fRec139[0];
		fRec137[1] = fRec137[0];
		fRec135[1] = fRec135[0];
		fRec133[1] = fRec133[0];
		fRec125[1] = fRec125[0];
		iRec126[1] = iRec126[0];
		fRec127[1] = fRec127[0];
	}
#undef fHslider0
#undef fHslider1
#undef fHslider2
#undef fHslider3
#undef fVslider0
#undef fVslider1
#undef fVslider2
#undef fVbargraph0
#undef fVslider3
#undef fVslider4
#undef fVslider5
#undef fVbargraph1
#undef fVslider6
#undef fVslider7
#undef fVslider8
#undef fVbargraph2
#undef fVslider9
#undef fVslider10
#undef fVslider11
#undef fVbargraph3
#undef fVslider12
#undef fVslider13
#undef fVslider14
#undef fVbargraph4
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case ROOMSIZE1: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case ROOMSIZE2: 
		fVslider5_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case ROOMSIZE3: 
		fVslider8_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case ROOMSIZE4: 
		fVslider11_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case ROOMSIZE5: 
		fVslider14_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case CROSSOVER_B1_B2: 
		fHslider0_ = (float*)data; // , 8e+01, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B2_B3: 
		fHslider1_ = (float*)data; // , 2.1e+02, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B3_B4: 
		fHslider2_ = (float*)data; // , 1.7e+03, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B4_B5: 
		fHslider3_ = (float*)data; // , 5e+03, 2e+01, 2e+04, 1.08 
		break;
	case DAMP1: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case DAMP2: 
		fVslider4_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case DAMP3: 
		fVslider7_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case DAMP4: 
		fVslider10_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case DAMP5: 
		fVslider13_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case WET_DRY1: 
		fVslider0_ = (float*)data; // , 5e+01, 0.0, 1e+02, 1.0 
		break;
	case WET_DRY2: 
		fVslider3_ = (float*)data; // , 5e+01, 0.0, 1e+02, 1.0 
		break;
	case WET_DRY3: 
		fVslider6_ = (float*)data; // , 5e+01, 0.0, 1e+02, 1.0 
		break;
	case WET_DRY4: 
		fVslider9_ = (float*)data; // , 5e+01, 0.0, 1e+02, 1.0 
		break;
	case WET_DRY5: 
		fVslider12_ = (float*)data; // , 5e+01, 0.0, 1e+02, 1.0 
		break;
	case V1: 
		fVbargraph0_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V2: 
		fVbargraph1_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V3: 
		fVbargraph2_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V4: 
		fVbargraph3_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V5: 
		fVbargraph4_ = (float*)data; // , 0, -7e+01, 5.0, 0 
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
   ROOMSIZE1, 
   ROOMSIZE2, 
   ROOMSIZE3, 
   ROOMSIZE4, 
   ROOMSIZE5, 
   CROSSOVER_B1_B2, 
   CROSSOVER_B2_B3, 
   CROSSOVER_B3_B4, 
   CROSSOVER_B4_B5, 
   DAMP1, 
   DAMP2, 
   DAMP3, 
   DAMP4, 
   DAMP5, 
   V1, 
   V2, 
   V3, 
   V4, 
   V5, 
   WET_DRY1, 
   WET_DRY2, 
   WET_DRY3, 
   WET_DRY4, 
   WET_DRY5, 
} PortIndex;
*/

} // end namespace mbreverb
