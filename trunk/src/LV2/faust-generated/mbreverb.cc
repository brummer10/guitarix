// generated from file '../src/LV2/faust/mbreverb.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace mbreverb {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst1;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fConst2;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	double fVec0[2];
	double fRec16[2];
	double fRec15[3];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	double fRec14[3];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT	*fHslider2_;
	double fRec13[3];
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT	*fHslider3_;
	double fRec12[3];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec17[2];
	int IOTA;
	double fVec1[2048];
	double fRec11[2];
	double fRec19[2];
	double fVec2[2048];
	double fRec18[2];
	double fRec21[2];
	double fVec3[2048];
	double fRec20[2];
	double fRec23[2];
	double fVec4[2048];
	double fRec22[2];
	double fRec25[2];
	double fVec5[2048];
	double fRec24[2];
	double fRec27[2];
	double fVec6[2048];
	double fRec26[2];
	double fRec29[2];
	double fVec7[2048];
	double fRec28[2];
	double fRec31[2];
	double fVec8[2048];
	double fRec30[2];
	double fVec9[1024];
	double fRec9[2];
	double fVec10[512];
	double fRec7[2];
	double fVec11[512];
	double fRec5[2];
	double fVec12[256];
	double fRec3[2];
	double fRec0[2];
	int iRec1[2];
	double fRec2[2];
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT	*fVbargraph0_;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec49[2];
	double fRec48[3];
	double fVec13[2];
	double fRec47[2];
	double fRec46[3];
	double fRec45[3];
	double fRec44[3];
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT	*fVslider5_;
	double fRec50[2];
	double fVec14[2048];
	double fRec43[2];
	double fRec52[2];
	double fVec15[2048];
	double fRec51[2];
	double fRec54[2];
	double fVec16[2048];
	double fRec53[2];
	double fRec56[2];
	double fVec17[2048];
	double fRec55[2];
	double fRec58[2];
	double fVec18[2048];
	double fRec57[2];
	double fRec60[2];
	double fVec19[2048];
	double fRec59[2];
	double fRec62[2];
	double fVec20[2048];
	double fRec61[2];
	double fRec64[2];
	double fVec21[2048];
	double fRec63[2];
	double fVec22[1024];
	double fRec41[2];
	double fVec23[512];
	double fRec39[2];
	double fVec24[512];
	double fRec37[2];
	double fVec25[256];
	double fRec35[2];
	double fRec32[2];
	int iRec33[2];
	double fRec34[2];
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT	*fVbargraph1_;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT	*fVslider6_;
	double fRec81[2];
	double fRec80[3];
	double fVec26[2];
	double fRec79[2];
	double fRec78[3];
	double fRec77[3];
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT	*fVslider7_;
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT	*fVslider8_;
	double fRec82[2];
	double fVec27[2048];
	double fRec76[2];
	double fRec84[2];
	double fVec28[2048];
	double fRec83[2];
	double fRec86[2];
	double fVec29[2048];
	double fRec85[2];
	double fRec88[2];
	double fVec30[2048];
	double fRec87[2];
	double fRec90[2];
	double fVec31[2048];
	double fRec89[2];
	double fRec92[2];
	double fVec32[2048];
	double fRec91[2];
	double fRec94[2];
	double fVec33[2048];
	double fRec93[2];
	double fRec96[2];
	double fVec34[2048];
	double fRec95[2];
	double fVec35[1024];
	double fRec74[2];
	double fVec36[512];
	double fRec72[2];
	double fVec37[512];
	double fRec70[2];
	double fVec38[256];
	double fRec68[2];
	double fRec65[2];
	int iRec66[2];
	double fRec67[2];
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT	*fVbargraph2_;
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT	*fVslider9_;
	double fRec112[2];
	double fRec111[3];
	double fVec39[2];
	double fRec110[2];
	double fRec109[3];
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT	*fVslider10_;
	FAUSTFLOAT fVslider11;
	FAUSTFLOAT	*fVslider11_;
	double fRec113[2];
	double fVec40[2048];
	double fRec108[2];
	double fRec115[2];
	double fVec41[2048];
	double fRec114[2];
	double fRec117[2];
	double fVec42[2048];
	double fRec116[2];
	double fRec119[2];
	double fVec43[2048];
	double fRec118[2];
	double fRec121[2];
	double fVec44[2048];
	double fRec120[2];
	double fRec123[2];
	double fVec45[2048];
	double fRec122[2];
	double fRec125[2];
	double fVec46[2048];
	double fRec124[2];
	double fRec127[2];
	double fVec47[2048];
	double fRec126[2];
	double fVec48[1024];
	double fRec106[2];
	double fVec49[512];
	double fRec104[2];
	double fVec50[512];
	double fRec102[2];
	double fVec51[256];
	double fRec100[2];
	double fRec97[2];
	int iRec98[2];
	double fRec99[2];
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT	*fVbargraph3_;
	FAUSTFLOAT fVslider12;
	FAUSTFLOAT	*fVslider12_;
	double fRec141[2];
	double fRec140[3];
	FAUSTFLOAT fVslider13;
	FAUSTFLOAT	*fVslider13_;
	FAUSTFLOAT fVslider14;
	FAUSTFLOAT	*fVslider14_;
	double fRec142[2];
	double fVec52[2048];
	double fRec139[2];
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
	double fRec137[2];
	double fVec61[512];
	double fRec135[2];
	double fVec62[512];
	double fRec133[2];
	double fVec63[256];
	double fRec131[2];
	double fRec128[2];
	int iRec129[2];
	double fRec130[2];
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fVec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec16[l1] = 0.0;
	for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) fRec15[l2] = 0.0;
	for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) fRec14[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec13[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec12[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec17[l6] = 0.0;
	for (int l7 = 0; (l7 < 2048); l7 = (l7 + 1)) fVec1[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec11[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec19[l9] = 0.0;
	for (int l10 = 0; (l10 < 2048); l10 = (l10 + 1)) fVec2[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec18[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec21[l12] = 0.0;
	for (int l13 = 0; (l13 < 2048); l13 = (l13 + 1)) fVec3[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec20[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec23[l15] = 0.0;
	for (int l16 = 0; (l16 < 2048); l16 = (l16 + 1)) fVec4[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec22[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec25[l18] = 0.0;
	for (int l19 = 0; (l19 < 2048); l19 = (l19 + 1)) fVec5[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fRec24[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec27[l21] = 0.0;
	for (int l22 = 0; (l22 < 2048); l22 = (l22 + 1)) fVec6[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fRec26[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec29[l24] = 0.0;
	for (int l25 = 0; (l25 < 2048); l25 = (l25 + 1)) fVec7[l25] = 0.0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fRec28[l26] = 0.0;
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) fRec31[l27] = 0.0;
	for (int l28 = 0; (l28 < 2048); l28 = (l28 + 1)) fVec8[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fRec30[l29] = 0.0;
	for (int l30 = 0; (l30 < 1024); l30 = (l30 + 1)) fVec9[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fRec9[l31] = 0.0;
	for (int l32 = 0; (l32 < 512); l32 = (l32 + 1)) fVec10[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fRec7[l33] = 0.0;
	for (int l34 = 0; (l34 < 512); l34 = (l34 + 1)) fVec11[l34] = 0.0;
	for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) fRec5[l35] = 0.0;
	for (int l36 = 0; (l36 < 256); l36 = (l36 + 1)) fVec12[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fRec3[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fRec0[l38] = 0.0;
	for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) iRec1[l39] = 0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fRec2[l40] = 0.0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) fRec49[l41] = 0.0;
	for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) fRec48[l42] = 0.0;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fVec13[l43] = 0.0;
	for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) fRec47[l44] = 0.0;
	for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) fRec46[l45] = 0.0;
	for (int l46 = 0; (l46 < 3); l46 = (l46 + 1)) fRec45[l46] = 0.0;
	for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) fRec44[l47] = 0.0;
	for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) fRec50[l48] = 0.0;
	for (int l49 = 0; (l49 < 2048); l49 = (l49 + 1)) fVec14[l49] = 0.0;
	for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) fRec43[l50] = 0.0;
	for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) fRec52[l51] = 0.0;
	for (int l52 = 0; (l52 < 2048); l52 = (l52 + 1)) fVec15[l52] = 0.0;
	for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) fRec51[l53] = 0.0;
	for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) fRec54[l54] = 0.0;
	for (int l55 = 0; (l55 < 2048); l55 = (l55 + 1)) fVec16[l55] = 0.0;
	for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) fRec53[l56] = 0.0;
	for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) fRec56[l57] = 0.0;
	for (int l58 = 0; (l58 < 2048); l58 = (l58 + 1)) fVec17[l58] = 0.0;
	for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) fRec55[l59] = 0.0;
	for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) fRec58[l60] = 0.0;
	for (int l61 = 0; (l61 < 2048); l61 = (l61 + 1)) fVec18[l61] = 0.0;
	for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) fRec57[l62] = 0.0;
	for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) fRec60[l63] = 0.0;
	for (int l64 = 0; (l64 < 2048); l64 = (l64 + 1)) fVec19[l64] = 0.0;
	for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) fRec59[l65] = 0.0;
	for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) fRec62[l66] = 0.0;
	for (int l67 = 0; (l67 < 2048); l67 = (l67 + 1)) fVec20[l67] = 0.0;
	for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) fRec61[l68] = 0.0;
	for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) fRec64[l69] = 0.0;
	for (int l70 = 0; (l70 < 2048); l70 = (l70 + 1)) fVec21[l70] = 0.0;
	for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) fRec63[l71] = 0.0;
	for (int l72 = 0; (l72 < 1024); l72 = (l72 + 1)) fVec22[l72] = 0.0;
	for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) fRec41[l73] = 0.0;
	for (int l74 = 0; (l74 < 512); l74 = (l74 + 1)) fVec23[l74] = 0.0;
	for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) fRec39[l75] = 0.0;
	for (int l76 = 0; (l76 < 512); l76 = (l76 + 1)) fVec24[l76] = 0.0;
	for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) fRec37[l77] = 0.0;
	for (int l78 = 0; (l78 < 256); l78 = (l78 + 1)) fVec25[l78] = 0.0;
	for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) fRec35[l79] = 0.0;
	for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) fRec32[l80] = 0.0;
	for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) iRec33[l81] = 0;
	for (int l82 = 0; (l82 < 2); l82 = (l82 + 1)) fRec34[l82] = 0.0;
	for (int l83 = 0; (l83 < 2); l83 = (l83 + 1)) fRec81[l83] = 0.0;
	for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) fRec80[l84] = 0.0;
	for (int l85 = 0; (l85 < 2); l85 = (l85 + 1)) fVec26[l85] = 0.0;
	for (int l86 = 0; (l86 < 2); l86 = (l86 + 1)) fRec79[l86] = 0.0;
	for (int l87 = 0; (l87 < 3); l87 = (l87 + 1)) fRec78[l87] = 0.0;
	for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) fRec77[l88] = 0.0;
	for (int l89 = 0; (l89 < 2); l89 = (l89 + 1)) fRec82[l89] = 0.0;
	for (int l90 = 0; (l90 < 2048); l90 = (l90 + 1)) fVec27[l90] = 0.0;
	for (int l91 = 0; (l91 < 2); l91 = (l91 + 1)) fRec76[l91] = 0.0;
	for (int l92 = 0; (l92 < 2); l92 = (l92 + 1)) fRec84[l92] = 0.0;
	for (int l93 = 0; (l93 < 2048); l93 = (l93 + 1)) fVec28[l93] = 0.0;
	for (int l94 = 0; (l94 < 2); l94 = (l94 + 1)) fRec83[l94] = 0.0;
	for (int l95 = 0; (l95 < 2); l95 = (l95 + 1)) fRec86[l95] = 0.0;
	for (int l96 = 0; (l96 < 2048); l96 = (l96 + 1)) fVec29[l96] = 0.0;
	for (int l97 = 0; (l97 < 2); l97 = (l97 + 1)) fRec85[l97] = 0.0;
	for (int l98 = 0; (l98 < 2); l98 = (l98 + 1)) fRec88[l98] = 0.0;
	for (int l99 = 0; (l99 < 2048); l99 = (l99 + 1)) fVec30[l99] = 0.0;
	for (int l100 = 0; (l100 < 2); l100 = (l100 + 1)) fRec87[l100] = 0.0;
	for (int l101 = 0; (l101 < 2); l101 = (l101 + 1)) fRec90[l101] = 0.0;
	for (int l102 = 0; (l102 < 2048); l102 = (l102 + 1)) fVec31[l102] = 0.0;
	for (int l103 = 0; (l103 < 2); l103 = (l103 + 1)) fRec89[l103] = 0.0;
	for (int l104 = 0; (l104 < 2); l104 = (l104 + 1)) fRec92[l104] = 0.0;
	for (int l105 = 0; (l105 < 2048); l105 = (l105 + 1)) fVec32[l105] = 0.0;
	for (int l106 = 0; (l106 < 2); l106 = (l106 + 1)) fRec91[l106] = 0.0;
	for (int l107 = 0; (l107 < 2); l107 = (l107 + 1)) fRec94[l107] = 0.0;
	for (int l108 = 0; (l108 < 2048); l108 = (l108 + 1)) fVec33[l108] = 0.0;
	for (int l109 = 0; (l109 < 2); l109 = (l109 + 1)) fRec93[l109] = 0.0;
	for (int l110 = 0; (l110 < 2); l110 = (l110 + 1)) fRec96[l110] = 0.0;
	for (int l111 = 0; (l111 < 2048); l111 = (l111 + 1)) fVec34[l111] = 0.0;
	for (int l112 = 0; (l112 < 2); l112 = (l112 + 1)) fRec95[l112] = 0.0;
	for (int l113 = 0; (l113 < 1024); l113 = (l113 + 1)) fVec35[l113] = 0.0;
	for (int l114 = 0; (l114 < 2); l114 = (l114 + 1)) fRec74[l114] = 0.0;
	for (int l115 = 0; (l115 < 512); l115 = (l115 + 1)) fVec36[l115] = 0.0;
	for (int l116 = 0; (l116 < 2); l116 = (l116 + 1)) fRec72[l116] = 0.0;
	for (int l117 = 0; (l117 < 512); l117 = (l117 + 1)) fVec37[l117] = 0.0;
	for (int l118 = 0; (l118 < 2); l118 = (l118 + 1)) fRec70[l118] = 0.0;
	for (int l119 = 0; (l119 < 256); l119 = (l119 + 1)) fVec38[l119] = 0.0;
	for (int l120 = 0; (l120 < 2); l120 = (l120 + 1)) fRec68[l120] = 0.0;
	for (int l121 = 0; (l121 < 2); l121 = (l121 + 1)) fRec65[l121] = 0.0;
	for (int l122 = 0; (l122 < 2); l122 = (l122 + 1)) iRec66[l122] = 0;
	for (int l123 = 0; (l123 < 2); l123 = (l123 + 1)) fRec67[l123] = 0.0;
	for (int l124 = 0; (l124 < 2); l124 = (l124 + 1)) fRec112[l124] = 0.0;
	for (int l125 = 0; (l125 < 3); l125 = (l125 + 1)) fRec111[l125] = 0.0;
	for (int l126 = 0; (l126 < 2); l126 = (l126 + 1)) fVec39[l126] = 0.0;
	for (int l127 = 0; (l127 < 2); l127 = (l127 + 1)) fRec110[l127] = 0.0;
	for (int l128 = 0; (l128 < 3); l128 = (l128 + 1)) fRec109[l128] = 0.0;
	for (int l129 = 0; (l129 < 2); l129 = (l129 + 1)) fRec113[l129] = 0.0;
	for (int l130 = 0; (l130 < 2048); l130 = (l130 + 1)) fVec40[l130] = 0.0;
	for (int l131 = 0; (l131 < 2); l131 = (l131 + 1)) fRec108[l131] = 0.0;
	for (int l132 = 0; (l132 < 2); l132 = (l132 + 1)) fRec115[l132] = 0.0;
	for (int l133 = 0; (l133 < 2048); l133 = (l133 + 1)) fVec41[l133] = 0.0;
	for (int l134 = 0; (l134 < 2); l134 = (l134 + 1)) fRec114[l134] = 0.0;
	for (int l135 = 0; (l135 < 2); l135 = (l135 + 1)) fRec117[l135] = 0.0;
	for (int l136 = 0; (l136 < 2048); l136 = (l136 + 1)) fVec42[l136] = 0.0;
	for (int l137 = 0; (l137 < 2); l137 = (l137 + 1)) fRec116[l137] = 0.0;
	for (int l138 = 0; (l138 < 2); l138 = (l138 + 1)) fRec119[l138] = 0.0;
	for (int l139 = 0; (l139 < 2048); l139 = (l139 + 1)) fVec43[l139] = 0.0;
	for (int l140 = 0; (l140 < 2); l140 = (l140 + 1)) fRec118[l140] = 0.0;
	for (int l141 = 0; (l141 < 2); l141 = (l141 + 1)) fRec121[l141] = 0.0;
	for (int l142 = 0; (l142 < 2048); l142 = (l142 + 1)) fVec44[l142] = 0.0;
	for (int l143 = 0; (l143 < 2); l143 = (l143 + 1)) fRec120[l143] = 0.0;
	for (int l144 = 0; (l144 < 2); l144 = (l144 + 1)) fRec123[l144] = 0.0;
	for (int l145 = 0; (l145 < 2048); l145 = (l145 + 1)) fVec45[l145] = 0.0;
	for (int l146 = 0; (l146 < 2); l146 = (l146 + 1)) fRec122[l146] = 0.0;
	for (int l147 = 0; (l147 < 2); l147 = (l147 + 1)) fRec125[l147] = 0.0;
	for (int l148 = 0; (l148 < 2048); l148 = (l148 + 1)) fVec46[l148] = 0.0;
	for (int l149 = 0; (l149 < 2); l149 = (l149 + 1)) fRec124[l149] = 0.0;
	for (int l150 = 0; (l150 < 2); l150 = (l150 + 1)) fRec127[l150] = 0.0;
	for (int l151 = 0; (l151 < 2048); l151 = (l151 + 1)) fVec47[l151] = 0.0;
	for (int l152 = 0; (l152 < 2); l152 = (l152 + 1)) fRec126[l152] = 0.0;
	for (int l153 = 0; (l153 < 1024); l153 = (l153 + 1)) fVec48[l153] = 0.0;
	for (int l154 = 0; (l154 < 2); l154 = (l154 + 1)) fRec106[l154] = 0.0;
	for (int l155 = 0; (l155 < 512); l155 = (l155 + 1)) fVec49[l155] = 0.0;
	for (int l156 = 0; (l156 < 2); l156 = (l156 + 1)) fRec104[l156] = 0.0;
	for (int l157 = 0; (l157 < 512); l157 = (l157 + 1)) fVec50[l157] = 0.0;
	for (int l158 = 0; (l158 < 2); l158 = (l158 + 1)) fRec102[l158] = 0.0;
	for (int l159 = 0; (l159 < 256); l159 = (l159 + 1)) fVec51[l159] = 0.0;
	for (int l160 = 0; (l160 < 2); l160 = (l160 + 1)) fRec100[l160] = 0.0;
	for (int l161 = 0; (l161 < 2); l161 = (l161 + 1)) fRec97[l161] = 0.0;
	for (int l162 = 0; (l162 < 2); l162 = (l162 + 1)) iRec98[l162] = 0;
	for (int l163 = 0; (l163 < 2); l163 = (l163 + 1)) fRec99[l163] = 0.0;
	for (int l164 = 0; (l164 < 2); l164 = (l164 + 1)) fRec141[l164] = 0.0;
	for (int l165 = 0; (l165 < 3); l165 = (l165 + 1)) fRec140[l165] = 0.0;
	for (int l166 = 0; (l166 < 2); l166 = (l166 + 1)) fRec142[l166] = 0.0;
	for (int l167 = 0; (l167 < 2048); l167 = (l167 + 1)) fVec52[l167] = 0.0;
	for (int l168 = 0; (l168 < 2); l168 = (l168 + 1)) fRec139[l168] = 0.0;
	for (int l169 = 0; (l169 < 2); l169 = (l169 + 1)) fRec144[l169] = 0.0;
	for (int l170 = 0; (l170 < 2048); l170 = (l170 + 1)) fVec53[l170] = 0.0;
	for (int l171 = 0; (l171 < 2); l171 = (l171 + 1)) fRec143[l171] = 0.0;
	for (int l172 = 0; (l172 < 2); l172 = (l172 + 1)) fRec146[l172] = 0.0;
	for (int l173 = 0; (l173 < 2048); l173 = (l173 + 1)) fVec54[l173] = 0.0;
	for (int l174 = 0; (l174 < 2); l174 = (l174 + 1)) fRec145[l174] = 0.0;
	for (int l175 = 0; (l175 < 2); l175 = (l175 + 1)) fRec148[l175] = 0.0;
	for (int l176 = 0; (l176 < 2048); l176 = (l176 + 1)) fVec55[l176] = 0.0;
	for (int l177 = 0; (l177 < 2); l177 = (l177 + 1)) fRec147[l177] = 0.0;
	for (int l178 = 0; (l178 < 2); l178 = (l178 + 1)) fRec150[l178] = 0.0;
	for (int l179 = 0; (l179 < 2048); l179 = (l179 + 1)) fVec56[l179] = 0.0;
	for (int l180 = 0; (l180 < 2); l180 = (l180 + 1)) fRec149[l180] = 0.0;
	for (int l181 = 0; (l181 < 2); l181 = (l181 + 1)) fRec152[l181] = 0.0;
	for (int l182 = 0; (l182 < 2048); l182 = (l182 + 1)) fVec57[l182] = 0.0;
	for (int l183 = 0; (l183 < 2); l183 = (l183 + 1)) fRec151[l183] = 0.0;
	for (int l184 = 0; (l184 < 2); l184 = (l184 + 1)) fRec154[l184] = 0.0;
	for (int l185 = 0; (l185 < 2048); l185 = (l185 + 1)) fVec58[l185] = 0.0;
	for (int l186 = 0; (l186 < 2); l186 = (l186 + 1)) fRec153[l186] = 0.0;
	for (int l187 = 0; (l187 < 2); l187 = (l187 + 1)) fRec156[l187] = 0.0;
	for (int l188 = 0; (l188 < 2048); l188 = (l188 + 1)) fVec59[l188] = 0.0;
	for (int l189 = 0; (l189 < 2); l189 = (l189 + 1)) fRec155[l189] = 0.0;
	for (int l190 = 0; (l190 < 1024); l190 = (l190 + 1)) fVec60[l190] = 0.0;
	for (int l191 = 0; (l191 < 2); l191 = (l191 + 1)) fRec137[l191] = 0.0;
	for (int l192 = 0; (l192 < 512); l192 = (l192 + 1)) fVec61[l192] = 0.0;
	for (int l193 = 0; (l193 < 2); l193 = (l193 + 1)) fRec135[l193] = 0.0;
	for (int l194 = 0; (l194 < 512); l194 = (l194 + 1)) fVec62[l194] = 0.0;
	for (int l195 = 0; (l195 < 2); l195 = (l195 + 1)) fRec133[l195] = 0.0;
	for (int l196 = 0; (l196 < 256); l196 = (l196 + 1)) fVec63[l196] = 0.0;
	for (int l197 = 0; (l197 < 2); l197 = (l197 + 1)) fRec131[l197] = 0.0;
	for (int l198 = 0; (l198 < 2); l198 = (l198 + 1)) fRec128[l198] = 0.0;
	for (int l199 = 0; (l199 < 2); l199 = (l199 + 1)) iRec129[l199] = 0;
	for (int l200 = 0; (l200 < 2); l200 = (l200 + 1)) fRec130[l200] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (1.0 / fConst0);
	fConst2 = (3.1415926535897931 / fConst0);
	IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fHslider0 (*fHslider0_)
#define fHslider1 (*fHslider1_)
#define fHslider2 (*fHslider2_)
#define fHslider3 (*fHslider3_)
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
	double fSlow0 = double(fVslider0);
	double fSlow1 = (0.00014999999999999999 * fSlow0);
	double fSlow2 = std::tan((fConst2 * double(fHslider0)));
	double fSlow3 = (1.0 / fSlow2);
	double fSlow4 = (((fSlow3 + 1.0000000000000004) / fSlow2) + 1.0);
	double fSlow5 = (1.0 / fSlow4);
	double fSlow6 = mydsp_faustpower2_f(fSlow2);
	double fSlow7 = (1.0 / fSlow6);
	double fSlow8 = (fSlow3 + 1.0);
	double fSlow9 = (0.0 - (1.0 / (fSlow2 * fSlow8)));
	double fSlow10 = (1.0 / fSlow8);
	double fSlow11 = (1.0 - fSlow3);
	double fSlow12 = (((fSlow3 + -1.0000000000000004) / fSlow2) + 1.0);
	double fSlow13 = (2.0 * (1.0 - fSlow7));
	double fSlow14 = (0.0 - (2.0 / fSlow6));
	double fSlow15 = std::tan((fConst2 * double(fHslider1)));
	double fSlow16 = (1.0 / fSlow15);
	double fSlow17 = (fSlow16 + 1.0);
	double fSlow18 = (1.0 / ((fSlow17 / fSlow15) + 1.0));
	double fSlow19 = (1.0 - fSlow16);
	double fSlow20 = (1.0 - (fSlow19 / fSlow15));
	double fSlow21 = mydsp_faustpower2_f(fSlow15);
	double fSlow22 = (1.0 / fSlow21);
	double fSlow23 = (2.0 * (1.0 - fSlow22));
	double fSlow24 = std::tan((fConst2 * double(fHslider2)));
	double fSlow25 = (1.0 / fSlow24);
	double fSlow26 = (fSlow25 + 1.0);
	double fSlow27 = (1.0 / ((fSlow26 / fSlow24) + 1.0));
	double fSlow28 = (1.0 - fSlow25);
	double fSlow29 = (1.0 - (fSlow28 / fSlow24));
	double fSlow30 = mydsp_faustpower2_f(fSlow24);
	double fSlow31 = (1.0 / fSlow30);
	double fSlow32 = (2.0 * (1.0 - fSlow31));
	double fSlow33 = std::tan((fConst2 * double(fHslider3)));
	double fSlow34 = (1.0 / fSlow33);
	double fSlow35 = (fSlow34 + 1.0);
	double fSlow36 = (1.0 / ((fSlow35 / fSlow33) + 1.0));
	double fSlow37 = (1.0 - fSlow34);
	double fSlow38 = (1.0 - (fSlow37 / fSlow33));
	double fSlow39 = mydsp_faustpower2_f(fSlow33);
	double fSlow40 = (1.0 / fSlow39);
	double fSlow41 = (2.0 * (1.0 - fSlow40));
	double fSlow42 = ((0.28000000000000003 * double(fVslider1)) + 0.69999999999999996);
	double fSlow43 = double(fVslider2);
	double fSlow44 = (1.0 - fSlow43);
	double fSlow45 = (1.0 - (0.01 * fSlow0));
	double fSlow46 = (fSlow45 + (fSlow0 * ((0.01 * fSlow45) + 0.00014999999999999999)));
	double fSlow47 = double(fVslider3);
	double fSlow48 = (0.00014999999999999999 * fSlow47);
	double fSlow49 = (((fSlow16 + 1.0000000000000004) / fSlow15) + 1.0);
	double fSlow50 = (1.0 / fSlow49);
	double fSlow51 = (0.0 - (1.0 / (fSlow15 * fSlow17)));
	double fSlow52 = (1.0 / fSlow17);
	double fSlow53 = (1.0 / (fSlow15 * fSlow4));
	double fSlow54 = (((fSlow16 + -1.0000000000000004) / fSlow15) + 1.0);
	double fSlow55 = (0.0 - (2.0 / fSlow21));
	double fSlow56 = ((0.28000000000000003 * double(fVslider4)) + 0.69999999999999996);
	double fSlow57 = double(fVslider5);
	double fSlow58 = (1.0 - fSlow57);
	double fSlow59 = (1.0 - (0.01 * fSlow47));
	double fSlow60 = (fSlow59 + (fSlow47 * ((0.01 * fSlow59) + 0.00014999999999999999)));
	double fSlow61 = double(fVslider6);
	double fSlow62 = (0.00014999999999999999 * fSlow61);
	double fSlow63 = (((fSlow25 + 1.0000000000000004) / fSlow24) + 1.0);
	double fSlow64 = (1.0 / fSlow63);
	double fSlow65 = (0.0 - (1.0 / (fSlow24 * fSlow26)));
	double fSlow66 = (1.0 / fSlow26);
	double fSlow67 = (1.0 / (fSlow24 * fSlow49));
	double fSlow68 = (((fSlow25 + -1.0000000000000004) / fSlow24) + 1.0);
	double fSlow69 = (0.0 - (2.0 / fSlow30));
	double fSlow70 = ((0.28000000000000003 * double(fVslider7)) + 0.69999999999999996);
	double fSlow71 = double(fVslider8);
	double fSlow72 = (1.0 - fSlow71);
	double fSlow73 = (1.0 - (0.01 * fSlow61));
	double fSlow74 = (fSlow73 + (fSlow61 * ((0.01 * fSlow73) + 0.00014999999999999999)));
	double fSlow75 = double(fVslider9);
	double fSlow76 = (((fSlow34 + 1.0000000000000004) / fSlow33) + 1.0);
	double fSlow77 = (0.00014999999999999999 * (fSlow75 / fSlow76));
	double fSlow78 = (0.0 - (1.0 / (fSlow33 * fSlow35)));
	double fSlow79 = (1.0 / fSlow35);
	double fSlow80 = (1.0 / (fSlow33 * fSlow63));
	double fSlow81 = (1.0 / fSlow76);
	double fSlow82 = (((fSlow34 + -1.0000000000000004) / fSlow33) + 1.0);
	double fSlow83 = (0.0 - (2.0 / fSlow39));
	double fSlow84 = ((0.28000000000000003 * double(fVslider10)) + 0.69999999999999996);
	double fSlow85 = double(fVslider11);
	double fSlow86 = (1.0 - fSlow85);
	double fSlow87 = (1.0 - (0.01 * fSlow75));
	double fSlow88 = ((fSlow87 + (fSlow75 * ((0.01 * fSlow87) + 0.00014999999999999999))) / fSlow76);
	double fSlow89 = double(fVslider12);
	double fSlow90 = (0.00014999999999999999 * (fSlow89 / fSlow76));
	double fSlow91 = ((0.28000000000000003 * double(fVslider13)) + 0.69999999999999996);
	double fSlow92 = double(fVslider14);
	double fSlow93 = (1.0 - fSlow92);
	double fSlow94 = (1.0 - (0.01 * fSlow89));
	double fSlow95 = ((fSlow94 + (fSlow89 * ((0.01 * fSlow94) + 0.00014999999999999999))) / fSlow76);
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		int iTemp0 = (iRec1[1] < 4096);
		double fTemp1 = double(input0[i0]);
		fVec0[0] = fTemp1;
		fRec16[0] = ((fSlow9 * fVec0[1]) - (fSlow10 * ((fSlow11 * fRec16[1]) - (fSlow3 * fTemp1))));
		fRec15[0] = (fRec16[0] - (fSlow5 * ((fSlow12 * fRec15[2]) + (fSlow13 * fRec15[1]))));
		double fTemp2 = (fSlow23 * fRec14[1]);
		fRec14[0] = ((fSlow5 * (((fSlow7 * fRec15[0]) + (fSlow14 * fRec15[1])) + (fSlow7 * fRec15[2]))) - (fSlow18 * ((fSlow20 * fRec14[2]) + fTemp2)));
		double fTemp3 = (fSlow32 * fRec13[1]);
		fRec13[0] = ((fRec14[2] + (fSlow18 * (fTemp2 + (fSlow20 * fRec14[0])))) - (fSlow27 * ((fSlow29 * fRec13[2]) + fTemp3)));
		double fTemp4 = (fSlow41 * fRec12[1]);
		fRec12[0] = ((fRec13[2] + (fSlow27 * (fTemp3 + (fSlow29 * fRec13[0])))) - (fSlow36 * ((fSlow38 * fRec12[2]) + fTemp4)));
		double fTemp5 = (fRec12[2] + (fSlow36 * (fTemp4 + (fSlow38 * fRec12[0]))));
		double fTemp6 = (fSlow1 * fTemp5);
		fRec17[0] = ((fSlow43 * fRec17[1]) + (fSlow44 * fRec11[1]));
		fVec1[(IOTA & 2047)] = (fTemp6 + (fSlow42 * fRec17[0]));
		fRec11[0] = fVec1[((IOTA - 1139) & 2047)];
		fRec19[0] = ((fSlow43 * fRec19[1]) + (fSlow44 * fRec18[1]));
		fVec2[(IOTA & 2047)] = (fTemp6 + (fSlow42 * fRec19[0]));
		fRec18[0] = fVec2[((IOTA - 1211) & 2047)];
		fRec21[0] = ((fSlow43 * fRec21[1]) + (fSlow44 * fRec20[1]));
		fVec3[(IOTA & 2047)] = (fTemp6 + (fSlow42 * fRec21[0]));
		fRec20[0] = fVec3[((IOTA - 1300) & 2047)];
		fRec23[0] = ((fSlow43 * fRec23[1]) + (fSlow44 * fRec22[1]));
		fVec4[(IOTA & 2047)] = (fTemp6 + (fSlow42 * fRec23[0]));
		fRec22[0] = fVec4[((IOTA - 1379) & 2047)];
		fRec25[0] = ((fSlow43 * fRec25[1]) + (fSlow44 * fRec24[1]));
		fVec5[(IOTA & 2047)] = (fTemp6 + (fSlow42 * fRec25[0]));
		fRec24[0] = fVec5[((IOTA - 1445) & 2047)];
		fRec27[0] = ((fSlow43 * fRec27[1]) + (fSlow44 * fRec26[1]));
		fVec6[(IOTA & 2047)] = (fTemp6 + (fSlow42 * fRec27[0]));
		fRec26[0] = fVec6[((IOTA - 1514) & 2047)];
		fRec29[0] = ((fSlow43 * fRec29[1]) + (fSlow44 * fRec28[1]));
		fVec7[(IOTA & 2047)] = (fTemp6 + (fSlow42 * fRec29[0]));
		fRec28[0] = fVec7[((IOTA - 1580) & 2047)];
		fRec31[0] = ((fSlow43 * fRec31[1]) + (fSlow44 * fRec30[1]));
		fVec8[(IOTA & 2047)] = (fTemp6 + (fSlow42 * fRec31[0]));
		fRec30[0] = fVec8[((IOTA - 1640) & 2047)];
		double fTemp7 = (((((((fRec11[0] + fRec18[0]) + fRec20[0]) + fRec22[0]) + fRec24[0]) + fRec26[0]) + fRec28[0]) + fRec30[0]);
		fVec9[(IOTA & 1023)] = (fTemp7 + (0.5 * fRec9[1]));
		fRec9[0] = fVec9[((IOTA - 579) & 1023)];
		double fRec10 = (fRec9[1] - fTemp7);
		fVec10[(IOTA & 511)] = (fRec10 + (0.5 * fRec7[1]));
		fRec7[0] = fVec10[((IOTA - 464) & 511)];
		double fRec8 = (fRec7[1] - fRec10);
		fVec11[(IOTA & 511)] = (fRec8 + (0.5 * fRec5[1]));
		fRec5[0] = fVec11[((IOTA - 364) & 511)];
		double fRec6 = (fRec5[1] - fRec8);
		fVec12[(IOTA & 255)] = (fRec6 + (0.5 * fRec3[1]));
		fRec3[0] = fVec12[((IOTA - 248) & 255)];
		double fRec4 = (fRec3[1] - fRec6);
		double fTemp8 = (fRec4 + (fSlow46 * fTemp5));
		double fTemp9 = std::max<double>(fConst1, std::fabs(fTemp8));
		fRec0[0] = (iTemp0 ? std::max<double>(fRec0[1], fTemp9) : fTemp9);
		iRec1[0] = (iTemp0 ? (iRec1[1] + 1) : 1);
		fRec2[0] = (iTemp0 ? fRec2[1] : fRec0[1]);
		fVbargraph0 = FAUSTFLOAT(fRec2[0]);
		int iTemp10 = (iRec33[1] < 4096);
		fRec49[0] = (0.0 - (fSlow10 * ((fSlow11 * fRec49[1]) - (fTemp1 + fVec0[1]))));
		fRec48[0] = (fRec49[0] - (fSlow5 * ((fSlow12 * fRec48[2]) + (fSlow13 * fRec48[1]))));
		double fTemp11 = (fRec48[2] + (fRec48[0] + (2.0 * fRec48[1])));
		double fTemp12 = (fSlow5 * fTemp11);
		fVec13[0] = fTemp12;
		fRec47[0] = ((fSlow51 * fVec13[1]) - (fSlow52 * ((fSlow19 * fRec47[1]) - (fSlow53 * fTemp11))));
		fRec46[0] = (fRec47[0] - (fSlow50 * ((fSlow54 * fRec46[2]) + (fSlow23 * fRec46[1]))));
		double fTemp13 = (fSlow32 * fRec45[1]);
		fRec45[0] = ((fSlow50 * (((fSlow22 * fRec46[0]) + (fSlow55 * fRec46[1])) + (fSlow22 * fRec46[2]))) - (fSlow27 * ((fSlow29 * fRec45[2]) + fTemp13)));
		double fTemp14 = (fSlow41 * fRec44[1]);
		fRec44[0] = ((fRec45[2] + (fSlow27 * (fTemp13 + (fSlow29 * fRec45[0])))) - (fSlow36 * ((fSlow38 * fRec44[2]) + fTemp14)));
		double fTemp15 = (fRec44[2] + (fSlow36 * (fTemp14 + (fSlow38 * fRec44[0]))));
		double fTemp16 = (fSlow48 * fTemp15);
		fRec50[0] = ((fSlow57 * fRec50[1]) + (fSlow58 * fRec43[1]));
		fVec14[(IOTA & 2047)] = (fTemp16 + (fSlow56 * fRec50[0]));
		fRec43[0] = fVec14[((IOTA - 1139) & 2047)];
		fRec52[0] = ((fSlow57 * fRec52[1]) + (fSlow58 * fRec51[1]));
		fVec15[(IOTA & 2047)] = (fTemp16 + (fSlow56 * fRec52[0]));
		fRec51[0] = fVec15[((IOTA - 1211) & 2047)];
		fRec54[0] = ((fSlow57 * fRec54[1]) + (fSlow58 * fRec53[1]));
		fVec16[(IOTA & 2047)] = (fTemp16 + (fSlow56 * fRec54[0]));
		fRec53[0] = fVec16[((IOTA - 1300) & 2047)];
		fRec56[0] = ((fSlow57 * fRec56[1]) + (fSlow58 * fRec55[1]));
		fVec17[(IOTA & 2047)] = (fTemp16 + (fSlow56 * fRec56[0]));
		fRec55[0] = fVec17[((IOTA - 1379) & 2047)];
		fRec58[0] = ((fSlow57 * fRec58[1]) + (fSlow58 * fRec57[1]));
		fVec18[(IOTA & 2047)] = (fTemp16 + (fSlow56 * fRec58[0]));
		fRec57[0] = fVec18[((IOTA - 1445) & 2047)];
		fRec60[0] = ((fSlow57 * fRec60[1]) + (fSlow58 * fRec59[1]));
		fVec19[(IOTA & 2047)] = (fTemp16 + (fSlow56 * fRec60[0]));
		fRec59[0] = fVec19[((IOTA - 1514) & 2047)];
		fRec62[0] = ((fSlow57 * fRec62[1]) + (fSlow58 * fRec61[1]));
		fVec20[(IOTA & 2047)] = (fTemp16 + (fSlow56 * fRec62[0]));
		fRec61[0] = fVec20[((IOTA - 1580) & 2047)];
		fRec64[0] = ((fSlow57 * fRec64[1]) + (fSlow58 * fRec63[1]));
		fVec21[(IOTA & 2047)] = (fTemp16 + (fSlow56 * fRec64[0]));
		fRec63[0] = fVec21[((IOTA - 1640) & 2047)];
		double fTemp17 = (((((((fRec43[0] + fRec51[0]) + fRec53[0]) + fRec55[0]) + fRec57[0]) + fRec59[0]) + fRec61[0]) + fRec63[0]);
		fVec22[(IOTA & 1023)] = (fTemp17 + (0.5 * fRec41[1]));
		fRec41[0] = fVec22[((IOTA - 579) & 1023)];
		double fRec42 = (fRec41[1] - fTemp17);
		fVec23[(IOTA & 511)] = (fRec42 + (0.5 * fRec39[1]));
		fRec39[0] = fVec23[((IOTA - 464) & 511)];
		double fRec40 = (fRec39[1] - fRec42);
		fVec24[(IOTA & 511)] = (fRec40 + (0.5 * fRec37[1]));
		fRec37[0] = fVec24[((IOTA - 364) & 511)];
		double fRec38 = (fRec37[1] - fRec40);
		fVec25[(IOTA & 255)] = (fRec38 + (0.5 * fRec35[1]));
		fRec35[0] = fVec25[((IOTA - 248) & 255)];
		double fRec36 = (fRec35[1] - fRec38);
		double fTemp18 = (fRec36 + (fSlow60 * fTemp15));
		double fTemp19 = std::max<double>(fConst1, std::fabs(fTemp18));
		fRec32[0] = (iTemp10 ? std::max<double>(fRec32[1], fTemp19) : fTemp19);
		iRec33[0] = (iTemp10 ? (iRec33[1] + 1) : 1);
		fRec34[0] = (iTemp10 ? fRec34[1] : fRec32[1]);
		fVbargraph1 = FAUSTFLOAT(fRec34[0]);
		int iTemp20 = (iRec66[1] < 4096);
		fRec81[0] = (0.0 - (fSlow52 * ((fSlow19 * fRec81[1]) - (fTemp12 + fVec13[1]))));
		fRec80[0] = (fRec81[0] - (fSlow50 * ((fSlow54 * fRec80[2]) + (fSlow23 * fRec80[1]))));
		double fTemp21 = (fRec80[2] + (fRec80[0] + (2.0 * fRec80[1])));
		double fTemp22 = (fSlow50 * fTemp21);
		fVec26[0] = fTemp22;
		fRec79[0] = ((fSlow65 * fVec26[1]) - (fSlow66 * ((fSlow28 * fRec79[1]) - (fSlow67 * fTemp21))));
		fRec78[0] = (fRec79[0] - (fSlow64 * ((fSlow68 * fRec78[2]) + (fSlow32 * fRec78[1]))));
		double fTemp23 = (fSlow41 * fRec77[1]);
		fRec77[0] = ((fSlow64 * (((fSlow31 * fRec78[0]) + (fSlow69 * fRec78[1])) + (fSlow31 * fRec78[2]))) - (fSlow36 * ((fSlow38 * fRec77[2]) + fTemp23)));
		double fTemp24 = (fRec77[2] + (fSlow36 * (fTemp23 + (fSlow38 * fRec77[0]))));
		double fTemp25 = (fSlow62 * fTemp24);
		fRec82[0] = ((fSlow71 * fRec82[1]) + (fSlow72 * fRec76[1]));
		fVec27[(IOTA & 2047)] = (fTemp25 + (fSlow70 * fRec82[0]));
		fRec76[0] = fVec27[((IOTA - 1139) & 2047)];
		fRec84[0] = ((fSlow71 * fRec84[1]) + (fSlow72 * fRec83[1]));
		fVec28[(IOTA & 2047)] = (fTemp25 + (fSlow70 * fRec84[0]));
		fRec83[0] = fVec28[((IOTA - 1211) & 2047)];
		fRec86[0] = ((fSlow71 * fRec86[1]) + (fSlow72 * fRec85[1]));
		fVec29[(IOTA & 2047)] = (fTemp25 + (fSlow70 * fRec86[0]));
		fRec85[0] = fVec29[((IOTA - 1300) & 2047)];
		fRec88[0] = ((fSlow71 * fRec88[1]) + (fSlow72 * fRec87[1]));
		fVec30[(IOTA & 2047)] = (fTemp25 + (fSlow70 * fRec88[0]));
		fRec87[0] = fVec30[((IOTA - 1379) & 2047)];
		fRec90[0] = ((fSlow71 * fRec90[1]) + (fSlow72 * fRec89[1]));
		fVec31[(IOTA & 2047)] = (fTemp25 + (fSlow70 * fRec90[0]));
		fRec89[0] = fVec31[((IOTA - 1445) & 2047)];
		fRec92[0] = ((fSlow71 * fRec92[1]) + (fSlow72 * fRec91[1]));
		fVec32[(IOTA & 2047)] = (fTemp25 + (fSlow70 * fRec92[0]));
		fRec91[0] = fVec32[((IOTA - 1514) & 2047)];
		fRec94[0] = ((fSlow71 * fRec94[1]) + (fSlow72 * fRec93[1]));
		fVec33[(IOTA & 2047)] = (fTemp25 + (fSlow70 * fRec94[0]));
		fRec93[0] = fVec33[((IOTA - 1580) & 2047)];
		fRec96[0] = ((fSlow71 * fRec96[1]) + (fSlow72 * fRec95[1]));
		fVec34[(IOTA & 2047)] = (fTemp25 + (fSlow70 * fRec96[0]));
		fRec95[0] = fVec34[((IOTA - 1640) & 2047)];
		double fTemp26 = (((((((fRec76[0] + fRec83[0]) + fRec85[0]) + fRec87[0]) + fRec89[0]) + fRec91[0]) + fRec93[0]) + fRec95[0]);
		fVec35[(IOTA & 1023)] = (fTemp26 + (0.5 * fRec74[1]));
		fRec74[0] = fVec35[((IOTA - 579) & 1023)];
		double fRec75 = (fRec74[1] - fTemp26);
		fVec36[(IOTA & 511)] = (fRec75 + (0.5 * fRec72[1]));
		fRec72[0] = fVec36[((IOTA - 464) & 511)];
		double fRec73 = (fRec72[1] - fRec75);
		fVec37[(IOTA & 511)] = (fRec73 + (0.5 * fRec70[1]));
		fRec70[0] = fVec37[((IOTA - 364) & 511)];
		double fRec71 = (fRec70[1] - fRec73);
		fVec38[(IOTA & 255)] = (fRec71 + (0.5 * fRec68[1]));
		fRec68[0] = fVec38[((IOTA - 248) & 255)];
		double fRec69 = (fRec68[1] - fRec71);
		double fTemp27 = (fRec69 + (fSlow74 * fTemp24));
		double fTemp28 = std::max<double>(fConst1, std::fabs(fTemp27));
		fRec65[0] = (iTemp20 ? std::max<double>(fRec65[1], fTemp28) : fTemp28);
		iRec66[0] = (iTemp20 ? (iRec66[1] + 1) : 1);
		fRec67[0] = (iTemp20 ? fRec67[1] : fRec65[1]);
		fVbargraph2 = FAUSTFLOAT(fRec67[0]);
		int iTemp29 = (iRec98[1] < 4096);
		fRec112[0] = (0.0 - (fSlow66 * ((fSlow28 * fRec112[1]) - (fTemp22 + fVec26[1]))));
		fRec111[0] = (fRec112[0] - (fSlow64 * ((fSlow68 * fRec111[2]) + (fSlow32 * fRec111[1]))));
		double fTemp30 = (fRec111[2] + (fRec111[0] + (2.0 * fRec111[1])));
		double fTemp31 = (fSlow64 * fTemp30);
		fVec39[0] = fTemp31;
		fRec110[0] = ((fSlow78 * fVec39[1]) - (fSlow79 * ((fSlow37 * fRec110[1]) - (fSlow80 * fTemp30))));
		fRec109[0] = (fRec110[0] - (fSlow81 * ((fSlow82 * fRec109[2]) + (fSlow41 * fRec109[1]))));
		double fTemp32 = (((fSlow40 * fRec109[0]) + (fSlow83 * fRec109[1])) + (fSlow40 * fRec109[2]));
		double fTemp33 = (fSlow77 * fTemp32);
		fRec113[0] = ((fSlow85 * fRec113[1]) + (fSlow86 * fRec108[1]));
		fVec40[(IOTA & 2047)] = (fTemp33 + (fSlow84 * fRec113[0]));
		fRec108[0] = fVec40[((IOTA - 1139) & 2047)];
		fRec115[0] = ((fSlow85 * fRec115[1]) + (fSlow86 * fRec114[1]));
		fVec41[(IOTA & 2047)] = (fTemp33 + (fSlow84 * fRec115[0]));
		fRec114[0] = fVec41[((IOTA - 1211) & 2047)];
		fRec117[0] = ((fSlow85 * fRec117[1]) + (fSlow86 * fRec116[1]));
		fVec42[(IOTA & 2047)] = (fTemp33 + (fSlow84 * fRec117[0]));
		fRec116[0] = fVec42[((IOTA - 1300) & 2047)];
		fRec119[0] = ((fSlow85 * fRec119[1]) + (fSlow86 * fRec118[1]));
		fVec43[(IOTA & 2047)] = (fTemp33 + (fSlow84 * fRec119[0]));
		fRec118[0] = fVec43[((IOTA - 1379) & 2047)];
		fRec121[0] = ((fSlow85 * fRec121[1]) + (fSlow86 * fRec120[1]));
		fVec44[(IOTA & 2047)] = (fTemp33 + (fSlow84 * fRec121[0]));
		fRec120[0] = fVec44[((IOTA - 1445) & 2047)];
		fRec123[0] = ((fSlow85 * fRec123[1]) + (fSlow86 * fRec122[1]));
		fVec45[(IOTA & 2047)] = (fTemp33 + (fSlow84 * fRec123[0]));
		fRec122[0] = fVec45[((IOTA - 1514) & 2047)];
		fRec125[0] = ((fSlow85 * fRec125[1]) + (fSlow86 * fRec124[1]));
		fVec46[(IOTA & 2047)] = (fTemp33 + (fSlow84 * fRec125[0]));
		fRec124[0] = fVec46[((IOTA - 1580) & 2047)];
		fRec127[0] = ((fSlow85 * fRec127[1]) + (fSlow86 * fRec126[1]));
		fVec47[(IOTA & 2047)] = (fTemp33 + (fSlow84 * fRec127[0]));
		fRec126[0] = fVec47[((IOTA - 1640) & 2047)];
		double fTemp34 = (((((((fRec108[0] + fRec114[0]) + fRec116[0]) + fRec118[0]) + fRec120[0]) + fRec122[0]) + fRec124[0]) + fRec126[0]);
		fVec48[(IOTA & 1023)] = (fTemp34 + (0.5 * fRec106[1]));
		fRec106[0] = fVec48[((IOTA - 579) & 1023)];
		double fRec107 = (fRec106[1] - fTemp34);
		fVec49[(IOTA & 511)] = (fRec107 + (0.5 * fRec104[1]));
		fRec104[0] = fVec49[((IOTA - 464) & 511)];
		double fRec105 = (fRec104[1] - fRec107);
		fVec50[(IOTA & 511)] = (fRec105 + (0.5 * fRec102[1]));
		fRec102[0] = fVec50[((IOTA - 364) & 511)];
		double fRec103 = (fRec102[1] - fRec105);
		fVec51[(IOTA & 255)] = (fRec103 + (0.5 * fRec100[1]));
		fRec100[0] = fVec51[((IOTA - 248) & 255)];
		double fRec101 = (fRec100[1] - fRec103);
		double fTemp35 = (fRec101 + (fSlow88 * fTemp32));
		double fTemp36 = std::max<double>(fConst1, std::fabs(fTemp35));
		fRec97[0] = (iTemp29 ? std::max<double>(fRec97[1], fTemp36) : fTemp36);
		iRec98[0] = (iTemp29 ? (iRec98[1] + 1) : 1);
		fRec99[0] = (iTemp29 ? fRec99[1] : fRec97[1]);
		fVbargraph3 = FAUSTFLOAT(fRec99[0]);
		int iTemp37 = (iRec129[1] < 4096);
		fRec141[0] = (0.0 - (fSlow79 * ((fSlow37 * fRec141[1]) - (fTemp31 + fVec39[1]))));
		fRec140[0] = (fRec141[0] - (fSlow81 * ((fSlow82 * fRec140[2]) + (fSlow41 * fRec140[1]))));
		double fTemp38 = (fRec140[2] + (fRec140[0] + (2.0 * fRec140[1])));
		double fTemp39 = (fSlow90 * fTemp38);
		fRec142[0] = ((fSlow92 * fRec142[1]) + (fSlow93 * fRec139[1]));
		fVec52[(IOTA & 2047)] = (fTemp39 + (fSlow91 * fRec142[0]));
		fRec139[0] = fVec52[((IOTA - 1139) & 2047)];
		fRec144[0] = ((fSlow92 * fRec144[1]) + (fSlow93 * fRec143[1]));
		fVec53[(IOTA & 2047)] = (fTemp39 + (fSlow91 * fRec144[0]));
		fRec143[0] = fVec53[((IOTA - 1211) & 2047)];
		fRec146[0] = ((fSlow92 * fRec146[1]) + (fSlow93 * fRec145[1]));
		fVec54[(IOTA & 2047)] = (fTemp39 + (fSlow91 * fRec146[0]));
		fRec145[0] = fVec54[((IOTA - 1300) & 2047)];
		fRec148[0] = ((fSlow92 * fRec148[1]) + (fSlow93 * fRec147[1]));
		fVec55[(IOTA & 2047)] = (fTemp39 + (fSlow91 * fRec148[0]));
		fRec147[0] = fVec55[((IOTA - 1379) & 2047)];
		fRec150[0] = ((fSlow92 * fRec150[1]) + (fSlow93 * fRec149[1]));
		fVec56[(IOTA & 2047)] = (fTemp39 + (fSlow91 * fRec150[0]));
		fRec149[0] = fVec56[((IOTA - 1445) & 2047)];
		fRec152[0] = ((fSlow92 * fRec152[1]) + (fSlow93 * fRec151[1]));
		fVec57[(IOTA & 2047)] = (fTemp39 + (fSlow91 * fRec152[0]));
		fRec151[0] = fVec57[((IOTA - 1514) & 2047)];
		fRec154[0] = ((fSlow92 * fRec154[1]) + (fSlow93 * fRec153[1]));
		fVec58[(IOTA & 2047)] = (fTemp39 + (fSlow91 * fRec154[0]));
		fRec153[0] = fVec58[((IOTA - 1580) & 2047)];
		fRec156[0] = ((fSlow92 * fRec156[1]) + (fSlow93 * fRec155[1]));
		fVec59[(IOTA & 2047)] = (fTemp39 + (fSlow91 * fRec156[0]));
		fRec155[0] = fVec59[((IOTA - 1640) & 2047)];
		double fTemp40 = (((((((fRec139[0] + fRec143[0]) + fRec145[0]) + fRec147[0]) + fRec149[0]) + fRec151[0]) + fRec153[0]) + fRec155[0]);
		fVec60[(IOTA & 1023)] = (fTemp40 + (0.5 * fRec137[1]));
		fRec137[0] = fVec60[((IOTA - 579) & 1023)];
		double fRec138 = (fRec137[1] - fTemp40);
		fVec61[(IOTA & 511)] = (fRec138 + (0.5 * fRec135[1]));
		fRec135[0] = fVec61[((IOTA - 464) & 511)];
		double fRec136 = (fRec135[1] - fRec138);
		fVec62[(IOTA & 511)] = (fRec136 + (0.5 * fRec133[1]));
		fRec133[0] = fVec62[((IOTA - 364) & 511)];
		double fRec134 = (fRec133[1] - fRec136);
		fVec63[(IOTA & 255)] = (fRec134 + (0.5 * fRec131[1]));
		fRec131[0] = fVec63[((IOTA - 248) & 255)];
		double fRec132 = (fRec131[1] - fRec134);
		double fTemp41 = (fRec132 + (fSlow95 * fTemp38));
		double fTemp42 = std::max<double>(fConst1, std::fabs(fTemp41));
		fRec128[0] = (iTemp37 ? std::max<double>(fRec128[1], fTemp42) : fTemp42);
		iRec129[0] = (iTemp37 ? (iRec129[1] + 1) : 1);
		fRec130[0] = (iTemp37 ? fRec130[1] : fRec128[1]);
		fVbargraph4 = FAUSTFLOAT(fRec130[0]);
		output0[i0] = FAUSTFLOAT(((((fTemp8 + fTemp18) + fTemp27) + fTemp35) + fTemp41));
		fVec0[1] = fVec0[0];
		fRec16[1] = fRec16[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fRec17[1] = fRec17[0];
		IOTA = (IOTA + 1);
		fRec11[1] = fRec11[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec25[1] = fRec25[0];
		fRec24[1] = fRec24[0];
		fRec27[1] = fRec27[0];
		fRec26[1] = fRec26[0];
		fRec29[1] = fRec29[0];
		fRec28[1] = fRec28[0];
		fRec31[1] = fRec31[0];
		fRec30[1] = fRec30[0];
		fRec9[1] = fRec9[0];
		fRec7[1] = fRec7[0];
		fRec5[1] = fRec5[0];
		fRec3[1] = fRec3[0];
		fRec0[1] = fRec0[0];
		iRec1[1] = iRec1[0];
		fRec2[1] = fRec2[0];
		fRec49[1] = fRec49[0];
		fRec48[2] = fRec48[1];
		fRec48[1] = fRec48[0];
		fVec13[1] = fVec13[0];
		fRec47[1] = fRec47[0];
		fRec46[2] = fRec46[1];
		fRec46[1] = fRec46[0];
		fRec45[2] = fRec45[1];
		fRec45[1] = fRec45[0];
		fRec44[2] = fRec44[1];
		fRec44[1] = fRec44[0];
		fRec50[1] = fRec50[0];
		fRec43[1] = fRec43[0];
		fRec52[1] = fRec52[0];
		fRec51[1] = fRec51[0];
		fRec54[1] = fRec54[0];
		fRec53[1] = fRec53[0];
		fRec56[1] = fRec56[0];
		fRec55[1] = fRec55[0];
		fRec58[1] = fRec58[0];
		fRec57[1] = fRec57[0];
		fRec60[1] = fRec60[0];
		fRec59[1] = fRec59[0];
		fRec62[1] = fRec62[0];
		fRec61[1] = fRec61[0];
		fRec64[1] = fRec64[0];
		fRec63[1] = fRec63[0];
		fRec41[1] = fRec41[0];
		fRec39[1] = fRec39[0];
		fRec37[1] = fRec37[0];
		fRec35[1] = fRec35[0];
		fRec32[1] = fRec32[0];
		iRec33[1] = iRec33[0];
		fRec34[1] = fRec34[0];
		fRec81[1] = fRec81[0];
		fRec80[2] = fRec80[1];
		fRec80[1] = fRec80[0];
		fVec26[1] = fVec26[0];
		fRec79[1] = fRec79[0];
		fRec78[2] = fRec78[1];
		fRec78[1] = fRec78[0];
		fRec77[2] = fRec77[1];
		fRec77[1] = fRec77[0];
		fRec82[1] = fRec82[0];
		fRec76[1] = fRec76[0];
		fRec84[1] = fRec84[0];
		fRec83[1] = fRec83[0];
		fRec86[1] = fRec86[0];
		fRec85[1] = fRec85[0];
		fRec88[1] = fRec88[0];
		fRec87[1] = fRec87[0];
		fRec90[1] = fRec90[0];
		fRec89[1] = fRec89[0];
		fRec92[1] = fRec92[0];
		fRec91[1] = fRec91[0];
		fRec94[1] = fRec94[0];
		fRec93[1] = fRec93[0];
		fRec96[1] = fRec96[0];
		fRec95[1] = fRec95[0];
		fRec74[1] = fRec74[0];
		fRec72[1] = fRec72[0];
		fRec70[1] = fRec70[0];
		fRec68[1] = fRec68[0];
		fRec65[1] = fRec65[0];
		iRec66[1] = iRec66[0];
		fRec67[1] = fRec67[0];
		fRec112[1] = fRec112[0];
		fRec111[2] = fRec111[1];
		fRec111[1] = fRec111[0];
		fVec39[1] = fVec39[0];
		fRec110[1] = fRec110[0];
		fRec109[2] = fRec109[1];
		fRec109[1] = fRec109[0];
		fRec113[1] = fRec113[0];
		fRec108[1] = fRec108[0];
		fRec115[1] = fRec115[0];
		fRec114[1] = fRec114[0];
		fRec117[1] = fRec117[0];
		fRec116[1] = fRec116[0];
		fRec119[1] = fRec119[0];
		fRec118[1] = fRec118[0];
		fRec121[1] = fRec121[0];
		fRec120[1] = fRec120[0];
		fRec123[1] = fRec123[0];
		fRec122[1] = fRec122[0];
		fRec125[1] = fRec125[0];
		fRec124[1] = fRec124[0];
		fRec127[1] = fRec127[0];
		fRec126[1] = fRec126[0];
		fRec106[1] = fRec106[0];
		fRec104[1] = fRec104[0];
		fRec102[1] = fRec102[0];
		fRec100[1] = fRec100[0];
		fRec97[1] = fRec97[0];
		iRec98[1] = iRec98[0];
		fRec99[1] = fRec99[0];
		fRec141[1] = fRec141[0];
		fRec140[2] = fRec140[1];
		fRec140[1] = fRec140[0];
		fRec142[1] = fRec142[0];
		fRec139[1] = fRec139[0];
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
		fRec137[1] = fRec137[0];
		fRec135[1] = fRec135[0];
		fRec133[1] = fRec133[0];
		fRec131[1] = fRec131[0];
		fRec128[1] = fRec128[0];
		iRec129[1] = iRec129[0];
		fRec130[1] = fRec130[0];
	}
#undef fVslider0
#undef fHslider0
#undef fHslider1
#undef fHslider2
#undef fHslider3
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
		fVslider13_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025000000000000001 
		break;
	case ROOMSIZE2: 
		fVslider10_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025000000000000001 
		break;
	case ROOMSIZE3: 
		fVslider7_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025000000000000001 
		break;
	case ROOMSIZE4: 
		fVslider4_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025000000000000001 
		break;
	case ROOMSIZE5: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025000000000000001 
		break;
	case CROSSOVER_B1_B2: 
		fHslider3_ = (float*)data; // , 80.0, 20.0, 20000.0, 1.0800000000000001 
		break;
	case CROSSOVER_B2_B3: 
		fHslider2_ = (float*)data; // , 210.0, 20.0, 20000.0, 1.0800000000000001 
		break;
	case CROSSOVER_B3_B4: 
		fHslider1_ = (float*)data; // , 1700.0, 20.0, 20000.0, 1.0800000000000001 
		break;
	case CROSSOVER_B4_B5: 
		fHslider0_ = (float*)data; // , 5000.0, 20.0, 20000.0, 1.0800000000000001 
		break;
	case DAMP1: 
		fVslider14_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025000000000000001 
		break;
	case DAMP2: 
		fVslider11_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025000000000000001 
		break;
	case DAMP3: 
		fVslider8_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025000000000000001 
		break;
	case DAMP4: 
		fVslider5_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025000000000000001 
		break;
	case DAMP5: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025000000000000001 
		break;
	case WET_DRY1: 
		fVslider12_ = (float*)data; // , 50.0, 0.0, 100.0, 1.0 
		break;
	case WET_DRY2: 
		fVslider9_ = (float*)data; // , 50.0, 0.0, 100.0, 1.0 
		break;
	case WET_DRY3: 
		fVslider6_ = (float*)data; // , 50.0, 0.0, 100.0, 1.0 
		break;
	case WET_DRY4: 
		fVslider3_ = (float*)data; // , 50.0, 0.0, 100.0, 1.0 
		break;
	case WET_DRY5: 
		fVslider0_ = (float*)data; // , 50.0, 0.0, 100.0, 1.0 
		break;
	case V1: 
		fVbargraph4_ = (float*)data; // , 0, -70.0, 5.0, 0 
		break;
	case V2: 
		fVbargraph3_ = (float*)data; // , 0, -70.0, 5.0, 0 
		break;
	case V3: 
		fVbargraph2_ = (float*)data; // , 0, -70.0, 5.0, 0 
		break;
	case V4: 
		fVbargraph1_ = (float*)data; // , 0, -70.0, 5.0, 0 
		break;
	case V5: 
		fVbargraph0_ = (float*)data; // , 0, -70.0, 5.0, 0 
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
