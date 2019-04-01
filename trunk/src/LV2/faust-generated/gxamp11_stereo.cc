// generated from file '../src/LV2/faust/gxamp11_stereo.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#include "valve.h"

namespace gxamp11_stereo {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fVec0[2];
	double fRec9[2];
	double fRec8[3];
	double fConst8;
	double fConst9;
	double fConst10;
	double fVec1[2];
	double fRec10[2];
	double fRec7[2];
	double fConst11;
	double fConst12;
	double fRec6[2];
	double fVec2[2];
	double fRec20[2];
	double fRec19[3];
	double fConst13;
	double fConst14;
	double fConst15;
	double fVec3[2];
	double fRec21[2];
	double fRec18[2];
	double fRec17[2];
	double fRec26[2];
	int IOTA;
	double fVec4[32768];
	double fConst16;
	int iConst17;
	double fRec28[2];
	double fRec27[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec29[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
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
	double fRec37[3];
	double fVec5[2];
	double fRec36[2];
	double fRec35[2];
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fRec34[3];
	double fVec6[2];
	double fConst40;
	double fConst41;
	double fConst42;
	double fRec33[2];
	double fConst43;
	double fConst44;
	double fRec32[3];
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
	double fRec31[3];
	double fConst55;
	double fRec41[2];
	double fRec40[3];
	double fConst56;
	double fConst57;
	double fConst58;
	double fRec39[3];
	double fRec38[3];
	double fConst59;
	double fConst60;
	double fConst61;
	double fRec45[2];
	double fRec44[3];
	double fVec7[2];
	double fConst62;
	double fConst63;
	double fRec43[2];
	double fConst64;
	double fRec42[3];
	double fConst65;
	double fConst66;
	double fRec47[2];
	double fRec46[3];
	double fVec8[2];
	double fRec30[2];
	double fVec9[2];
	double fRec25[2];
	double fRec24[3];
	double fConst67;
	double fConst68;
	double fConst69;
	double fVec10[2];
	double fRec48[2];
	double fRec23[2];
	double fRec22[2];
	double fRec16[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec49[2];
	double fVec11[2];
	double fRec15[2];
	double fVec12[2];
	double fRec14[2];
	double fRec13[3];
	double fVec13[2];
	double fRec50[2];
	double fRec12[2];
	double fRec11[2];
	double fRec5[2];
	double fRec4[2];
	double fVec14[2];
	double fRec3[2];
	double fRec2[3];
	double fVec15[2];
	double fRec51[2];
	double fRec1[2];
	double fRec0[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec52[2];
	double fVec16[2];
	double fRec62[2];
	double fRec61[3];
	double fVec17[2];
	double fRec63[2];
	double fRec60[2];
	double fRec59[2];
	double fVec18[2];
	double fRec73[2];
	double fRec72[3];
	double fVec19[2];
	double fRec74[2];
	double fRec71[2];
	double fRec70[2];
	double fRec79[2];
	double fVec20[32768];
	double fRec81[2];
	double fRec80[2];
	double fRec89[3];
	double fVec21[2];
	double fRec88[2];
	double fRec87[2];
	double fRec86[3];
	double fVec22[2];
	double fRec85[2];
	double fRec84[3];
	double fRec83[3];
	double fRec93[2];
	double fRec92[3];
	double fRec91[3];
	double fRec90[3];
	double fRec97[2];
	double fRec96[3];
	double fVec23[2];
	double fRec95[2];
	double fRec94[3];
	double fRec99[2];
	double fRec98[3];
	double fVec24[2];
	double fRec82[2];
	double fVec25[2];
	double fRec78[2];
	double fRec77[3];
	double fVec26[2];
	double fRec100[2];
	double fRec76[2];
	double fRec75[2];
	double fRec69[2];
	double fVec27[2];
	double fRec68[2];
	double fVec28[2];
	double fRec67[2];
	double fRec66[3];
	double fVec29[2];
	double fRec101[2];
	double fRec65[2];
	double fRec64[2];
	double fRec58[2];
	double fRec57[2];
	double fVec30[2];
	double fRec56[2];
	double fRec55[3];
	double fVec31[2];
	double fRec102[2];
	double fRec54[2];
	double fRec53[2];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "12AU7 feedback";
	name = N_("12AU7 feedback");
	mono_audio = 0;
	stereo_audio = compute_static;
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
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec9[l1] = 0.0;
	for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) fRec8[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fVec1[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec10[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec7[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec6[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fVec2[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec20[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec19[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fVec3[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec21[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec18[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec17[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec26[l14] = 0.0;
	for (int l15 = 0; (l15 < 32768); l15 = (l15 + 1)) fVec4[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec28[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec27[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec29[l18] = 0.0;
	for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) fRec37[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fVec5[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec36[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fRec35[l22] = 0.0;
	for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) fRec34[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fVec6[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fRec33[l25] = 0.0;
	for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) fRec32[l26] = 0.0;
	for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) fRec31[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec41[l28] = 0.0;
	for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) fRec40[l29] = 0.0;
	for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) fRec39[l30] = 0.0;
	for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) fRec38[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fRec45[l32] = 0.0;
	for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) fRec44[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fVec7[l34] = 0.0;
	for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) fRec43[l35] = 0.0;
	for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) fRec42[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fRec47[l37] = 0.0;
	for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) fRec46[l38] = 0.0;
	for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) fVec8[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fRec30[l40] = 0.0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) fVec9[l41] = 0.0;
	for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) fRec25[l42] = 0.0;
	for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) fRec24[l43] = 0.0;
	for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) fVec10[l44] = 0.0;
	for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) fRec48[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec23[l46] = 0.0;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) fRec22[l47] = 0.0;
	for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) fRec16[l48] = 0.0;
	for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) fRec49[l49] = 0.0;
	for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) fVec11[l50] = 0.0;
	for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) fRec15[l51] = 0.0;
	for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) fVec12[l52] = 0.0;
	for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) fRec14[l53] = 0.0;
	for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) fRec13[l54] = 0.0;
	for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) fVec13[l55] = 0.0;
	for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) fRec50[l56] = 0.0;
	for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) fRec12[l57] = 0.0;
	for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) fRec11[l58] = 0.0;
	for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) fRec5[l59] = 0.0;
	for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) fRec4[l60] = 0.0;
	for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) fVec14[l61] = 0.0;
	for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) fRec3[l62] = 0.0;
	for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) fRec2[l63] = 0.0;
	for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) fVec15[l64] = 0.0;
	for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) fRec51[l65] = 0.0;
	for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) fRec1[l66] = 0.0;
	for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) fRec0[l67] = 0.0;
	for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) fRec52[l68] = 0.0;
	for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) fVec16[l69] = 0.0;
	for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) fRec62[l70] = 0.0;
	for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) fRec61[l71] = 0.0;
	for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) fVec17[l72] = 0.0;
	for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) fRec63[l73] = 0.0;
	for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) fRec60[l74] = 0.0;
	for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) fRec59[l75] = 0.0;
	for (int l76 = 0; (l76 < 2); l76 = (l76 + 1)) fVec18[l76] = 0.0;
	for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) fRec73[l77] = 0.0;
	for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) fRec72[l78] = 0.0;
	for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) fVec19[l79] = 0.0;
	for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) fRec74[l80] = 0.0;
	for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) fRec71[l81] = 0.0;
	for (int l82 = 0; (l82 < 2); l82 = (l82 + 1)) fRec70[l82] = 0.0;
	for (int l83 = 0; (l83 < 2); l83 = (l83 + 1)) fRec79[l83] = 0.0;
	for (int l84 = 0; (l84 < 32768); l84 = (l84 + 1)) fVec20[l84] = 0.0;
	for (int l85 = 0; (l85 < 2); l85 = (l85 + 1)) fRec81[l85] = 0.0;
	for (int l86 = 0; (l86 < 2); l86 = (l86 + 1)) fRec80[l86] = 0.0;
	for (int l87 = 0; (l87 < 3); l87 = (l87 + 1)) fRec89[l87] = 0.0;
	for (int l88 = 0; (l88 < 2); l88 = (l88 + 1)) fVec21[l88] = 0.0;
	for (int l89 = 0; (l89 < 2); l89 = (l89 + 1)) fRec88[l89] = 0.0;
	for (int l90 = 0; (l90 < 2); l90 = (l90 + 1)) fRec87[l90] = 0.0;
	for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) fRec86[l91] = 0.0;
	for (int l92 = 0; (l92 < 2); l92 = (l92 + 1)) fVec22[l92] = 0.0;
	for (int l93 = 0; (l93 < 2); l93 = (l93 + 1)) fRec85[l93] = 0.0;
	for (int l94 = 0; (l94 < 3); l94 = (l94 + 1)) fRec84[l94] = 0.0;
	for (int l95 = 0; (l95 < 3); l95 = (l95 + 1)) fRec83[l95] = 0.0;
	for (int l96 = 0; (l96 < 2); l96 = (l96 + 1)) fRec93[l96] = 0.0;
	for (int l97 = 0; (l97 < 3); l97 = (l97 + 1)) fRec92[l97] = 0.0;
	for (int l98 = 0; (l98 < 3); l98 = (l98 + 1)) fRec91[l98] = 0.0;
	for (int l99 = 0; (l99 < 3); l99 = (l99 + 1)) fRec90[l99] = 0.0;
	for (int l100 = 0; (l100 < 2); l100 = (l100 + 1)) fRec97[l100] = 0.0;
	for (int l101 = 0; (l101 < 3); l101 = (l101 + 1)) fRec96[l101] = 0.0;
	for (int l102 = 0; (l102 < 2); l102 = (l102 + 1)) fVec23[l102] = 0.0;
	for (int l103 = 0; (l103 < 2); l103 = (l103 + 1)) fRec95[l103] = 0.0;
	for (int l104 = 0; (l104 < 3); l104 = (l104 + 1)) fRec94[l104] = 0.0;
	for (int l105 = 0; (l105 < 2); l105 = (l105 + 1)) fRec99[l105] = 0.0;
	for (int l106 = 0; (l106 < 3); l106 = (l106 + 1)) fRec98[l106] = 0.0;
	for (int l107 = 0; (l107 < 2); l107 = (l107 + 1)) fVec24[l107] = 0.0;
	for (int l108 = 0; (l108 < 2); l108 = (l108 + 1)) fRec82[l108] = 0.0;
	for (int l109 = 0; (l109 < 2); l109 = (l109 + 1)) fVec25[l109] = 0.0;
	for (int l110 = 0; (l110 < 2); l110 = (l110 + 1)) fRec78[l110] = 0.0;
	for (int l111 = 0; (l111 < 3); l111 = (l111 + 1)) fRec77[l111] = 0.0;
	for (int l112 = 0; (l112 < 2); l112 = (l112 + 1)) fVec26[l112] = 0.0;
	for (int l113 = 0; (l113 < 2); l113 = (l113 + 1)) fRec100[l113] = 0.0;
	for (int l114 = 0; (l114 < 2); l114 = (l114 + 1)) fRec76[l114] = 0.0;
	for (int l115 = 0; (l115 < 2); l115 = (l115 + 1)) fRec75[l115] = 0.0;
	for (int l116 = 0; (l116 < 2); l116 = (l116 + 1)) fRec69[l116] = 0.0;
	for (int l117 = 0; (l117 < 2); l117 = (l117 + 1)) fVec27[l117] = 0.0;
	for (int l118 = 0; (l118 < 2); l118 = (l118 + 1)) fRec68[l118] = 0.0;
	for (int l119 = 0; (l119 < 2); l119 = (l119 + 1)) fVec28[l119] = 0.0;
	for (int l120 = 0; (l120 < 2); l120 = (l120 + 1)) fRec67[l120] = 0.0;
	for (int l121 = 0; (l121 < 3); l121 = (l121 + 1)) fRec66[l121] = 0.0;
	for (int l122 = 0; (l122 < 2); l122 = (l122 + 1)) fVec29[l122] = 0.0;
	for (int l123 = 0; (l123 < 2); l123 = (l123 + 1)) fRec101[l123] = 0.0;
	for (int l124 = 0; (l124 < 2); l124 = (l124 + 1)) fRec65[l124] = 0.0;
	for (int l125 = 0; (l125 < 2); l125 = (l125 + 1)) fRec64[l125] = 0.0;
	for (int l126 = 0; (l126 < 2); l126 = (l126 + 1)) fRec58[l126] = 0.0;
	for (int l127 = 0; (l127 < 2); l127 = (l127 + 1)) fRec57[l127] = 0.0;
	for (int l128 = 0; (l128 < 2); l128 = (l128 + 1)) fVec30[l128] = 0.0;
	for (int l129 = 0; (l129 < 2); l129 = (l129 + 1)) fRec56[l129] = 0.0;
	for (int l130 = 0; (l130 < 3); l130 = (l130 + 1)) fRec55[l130] = 0.0;
	for (int l131 = 0; (l131 < 2); l131 = (l131 + 1)) fVec31[l131] = 0.0;
	for (int l132 = 0; (l132 < 2); l132 = (l132 + 1)) fRec102[l132] = 0.0;
	for (int l133 = 0; (l133 < 2); l133 = (l133 + 1)) fRec54[l133] = 0.0;
	for (int l134 = 0; (l134 < 2); l134 = (l134 + 1)) fRec53[l134] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = std::tan((97.389372261283583 / fConst0));
	fConst2 = (1.0 / fConst1);
	fConst3 = (fConst2 + 1.0);
	fConst4 = (1.0 / (fConst3 * fConst1));
	fConst5 = (1.0 / std::tan((20517.741620594938 / fConst0)));
	fConst6 = (1.0 / (fConst5 + 1.0));
	fConst7 = (1.0 - fConst5);
	fConst8 = (1.0 / std::tan((609.46897479641984 / fConst0)));
	fConst9 = (1.0 / (fConst8 + 1.0));
	fConst10 = (1.0 - fConst8);
	fConst11 = (0.0 - fConst4);
	fConst12 = ((1.0 - fConst2) / fConst3);
	fConst13 = (1.0 / std::tan((414.69023027385271 / fConst0)));
	fConst14 = (1.0 / (fConst13 + 1.0));
	fConst15 = (1.0 - fConst13);
	fConst16 = (0.009000000000000008 / fConst0);
	iConst17 = int(std::min<double>(65536.0, std::max<double>(0.0, (0.1111111111111111 * fConst0))));
	fConst18 = std::tan((3769.9111843077517 / fConst0));
	fConst19 = (1.0 / fConst18);
	fConst20 = (1.0 / (((fConst19 + 1.0000000000000004) / fConst18) + 1.0));
	fConst21 = mydsp_faustpower2_f(fConst18);
	fConst22 = (1.0 / fConst21);
	fConst23 = std::tan((10053.096491487338 / fConst0));
	fConst24 = (1.0 / fConst23);
	fConst25 = (1.0 / (((fConst24 + 1.0000000000000004) / fConst23) + 1.0));
	fConst26 = (fConst19 + 1.0);
	fConst27 = (1.0 / (fConst18 * fConst26));
	fConst28 = (fConst24 + 1.0);
	fConst29 = (1.0 / fConst28);
	fConst30 = (1.0 - fConst24);
	fConst31 = std::tan((47123.889803846898 / fConst0));
	fConst32 = (1.0 / fConst31);
	fConst33 = (1.0 / (((fConst32 + 1.4142135623730949) / fConst31) + 1.0));
	fConst34 = (((fConst32 + -1.4142135623730949) / fConst31) + 1.0);
	fConst35 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst31))));
	fConst36 = (((fConst24 + -1.0000000000000004) / fConst23) + 1.0);
	fConst37 = mydsp_faustpower2_f(fConst23);
	fConst38 = (1.0 / fConst37);
	fConst39 = (2.0 * (1.0 - fConst38));
	fConst40 = (0.0 - fConst27);
	fConst41 = (1.0 - fConst19);
	fConst42 = (fConst41 / fConst26);
	fConst43 = (((fConst19 + -1.0000000000000004) / fConst18) + 1.0);
	fConst44 = (2.0 * (1.0 - fConst22));
	fConst45 = (0.0 - (2.0 / fConst21));
	fConst46 = std::tan((942.47779607693792 / fConst0));
	fConst47 = (1.0 / fConst46);
	fConst48 = (fConst47 + 1.0);
	fConst49 = (1.0 / ((fConst48 / fConst46) + 1.0));
	fConst50 = (1.0 - fConst47);
	fConst51 = (1.0 - (fConst50 / fConst46));
	fConst52 = mydsp_faustpower2_f(fConst46);
	fConst53 = (1.0 / fConst52);
	fConst54 = (2.0 * (1.0 - fConst53));
	fConst55 = (0.0 - (1.0 / (fConst28 * fConst23)));
	fConst56 = (0.0 - (2.0 / fConst37));
	fConst57 = (1.0 / ((fConst26 / fConst18) + 1.0));
	fConst58 = (1.0 - (fConst41 / fConst18));
	fConst59 = (1.0 / (((fConst47 + 1.0000000000000004) / fConst46) + 1.0));
	fConst60 = (1.0 / (fConst46 * fConst48));
	fConst61 = (1.0 / fConst26);
	fConst62 = (0.0 - fConst60);
	fConst63 = (fConst50 / fConst48);
	fConst64 = (((fConst47 + -1.0000000000000004) / fConst46) + 1.0);
	fConst65 = (0.0 - (2.0 / fConst52));
	fConst66 = (1.0 / fConst48);
	fConst67 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst68 = (1.0 / (fConst67 + 1.0));
	fConst69 = (1.0 - fConst67);
	fVslider0 = FAUSTFLOAT(100.0);
	fVslider1 = FAUSTFLOAT(0.34999999999999998);
	fVslider2 = FAUSTFLOAT(-6.0);
	fVslider3 = FAUSTFLOAT(-6.0);
			IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	double fSlow0 = (1.0000000000000009e-05 * double(fVslider0));
	double fSlow1 = double(fVslider1);
	double fSlow2 = (1.25 * fSlow1);
	double fSlow3 = (2.0 * (fSlow1 + -0.5));
	double fSlow4 = (0.024937655860349125 * (1.0 - std::max<double>(0.0, fSlow3)));
	double fSlow5 = std::pow(10.0, (2.0 * fSlow1));
	double fSlow6 = (1.0 - std::max<double>(0.0, (-1.0 * fSlow3)));
	double fSlow7 = std::pow(10.0, (1.2 * fSlow1));
	double fSlow8 = std::pow(10.0, (0.80000000000000004 * fSlow1));
	double fSlow9 = (fConst59 * fSlow5);
	double fSlow10 = (fConst59 * std::pow(10.0, (0.90000000000000002 * fSlow1)));
	double fSlow11 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider2))));
	double fSlow12 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider3))));
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = (fRec5[1] + 1.0000000000000001e-15);
		fVec0[0] = fTemp0;
		fRec9[0] = ((0.93028479253239138 * (fTemp0 + fVec0[1])) - (0.86056958506478287 * fRec9[1]));
		fRec8[0] = (fRec9[0] - ((1.8405051250752198 * fRec8[1]) + (0.86129424393186271 * fRec8[2])));
		double fTemp1 = ((0.0082000000000000007 * fRec7[1]) + 1.0000000000000001e-15);
		fVec1[0] = fTemp1;
		fRec10[0] = (0.0 - (fConst9 * ((fConst10 * fRec10[1]) - (fTemp1 + fVec1[1]))));
		fRec7[0] = (double(Ftube(int(TUBE_TABLE_12AU7_250k), double((((0.92544984225177063 * (fRec8[0] + fRec8[2])) + (fRec10[0] + (1.8508996845035413 * fRec8[1]))) + -0.44548700000000002)))) + -75.672317073170731);
		fRec6[0] = ((0.10000000000000001 * ((fConst4 * fRec7[0]) + (fConst11 * fRec7[1]))) - (fConst12 * fRec6[1]));
		double fTemp2 = (fRec16[1] + 1.0000000000000001e-15);
		fVec2[0] = fTemp2;
		fRec20[0] = ((0.93028479253239138 * (fTemp2 + fVec2[1])) - (0.86056958506478287 * fRec20[1]));
		fRec19[0] = (fRec20[0] - ((1.8405051250752198 * fRec19[1]) + (0.86129424393186271 * fRec19[2])));
		double fTemp3 = ((0.014999999999999999 * fRec18[1]) + 1.0000000000000001e-15);
		fVec3[0] = fTemp3;
		fRec21[0] = (0.0 - (fConst14 * ((fConst15 * fRec21[1]) - (fTemp3 + fVec3[1]))));
		fRec18[0] = (double(Ftube(int(TUBE_TABLE_12AU7_250k), double((((0.92544984225177063 * (fRec19[0] + fRec19[2])) + (fRec21[0] + (1.8508996845035413 * fRec19[1]))) + -0.77616200000000002)))) + -78.255866666666662);
		fRec17[0] = ((0.10000000000000001 * ((fConst4 * fRec18[0]) + (fConst11 * fRec18[1]))) - (fConst12 * fRec17[1]));
		double fTemp4 = double(input0[i]);
		double fTemp5 = std::fabs(fTemp4);
		fRec26[0] = ((0.99990000000000001 * fRec26[1]) + (9.9999999999988987e-05 * fTemp5));
		double fTemp6 = std::max<double>(fRec26[0], fTemp5);
		fVec4[(IOTA & 32767)] = fTemp6;
		fRec28[0] = ((fTemp6 + fRec28[1]) - fVec4[((IOTA - iConst17) & 32767)]);
		fRec27[0] = ((0.999 * fRec27[1]) + (fConst16 * fRec28[0]));
		double fTemp7 = std::max<double>(-1.0, std::min<double>(-0.01, (fTemp6 + (-1.0 - (1.02 * fRec27[0])))));
		double fTemp8 = (fTemp4 - fTemp7);
		double fTemp9 = (40.100000000000001 * fTemp8);
		double fTemp10 = std::max<double>(-600.0, fTemp9);
		double fTemp11 = (0.0 - (40.100000000000001 * fTemp7));
		double fTemp12 = std::max<double>(-600.0, fTemp11);
		double fTemp13 = (((std::fabs(fTemp9) > 0.0001)?((fTemp10 < -50.0)?(0.0 - (fTemp10 * std::exp(fTemp10))):(fTemp10 / (1.0 - std::exp((-1.0 * fTemp10))))):((fTemp8 * ((134.00083333333336 * fTemp8) + 20.050000000000001)) + 1.0)) - ((std::fabs(fTemp11) > 0.0001)?((fTemp12 < -50.0)?(0.0 - (fTemp12 * std::exp(fTemp12))):(fTemp12 / (1.0 - std::exp((-1.0 * fTemp12))))):((fTemp11 * ((0.083333333333333329 * fTemp11) + 0.5)) + 1.0)));
		fRec29[0] = (fSlow0 + (0.999 * fRec29[1]));
		double fTemp14 = (1.0 - fRec29[0]);
		double fTemp15 = (fSlow4 * fRec29[0]);
		double fTemp16 = (0.024937655860349125 * (fRec29[0] * fTemp13));
		double fTemp17 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow5 * std::max<double>(-0.69999999999999996, std::min<double>(0.69999999999999996, fTemp16)))));
		fRec37[0] = (fTemp16 - (fConst33 * ((fConst34 * fRec37[2]) + (fConst35 * fRec37[1]))));
		double fTemp18 = (fRec37[2] + (fRec37[0] + (2.0 * fRec37[1])));
		fVec5[0] = fTemp18;
		fRec36[0] = ((fConst33 * ((fConst4 * fTemp18) + (fConst11 * fVec5[1]))) - (fConst12 * fRec36[1]));
		fRec35[0] = (0.0 - (fConst29 * ((fConst30 * fRec35[1]) - (fRec36[0] + fRec36[1]))));
		fRec34[0] = (fRec35[0] - (fConst25 * ((fConst36 * fRec34[2]) + (fConst39 * fRec34[1]))));
		double fTemp19 = (fRec34[2] + (fRec34[0] + (2.0 * fRec34[1])));
		fVec6[0] = fTemp19;
		fRec33[0] = ((fConst25 * ((fConst27 * fTemp19) + (fConst40 * fVec6[1]))) - (fConst42 * fRec33[1]));
		fRec32[0] = (fRec33[0] - (fConst20 * ((fConst43 * fRec32[2]) + (fConst44 * fRec32[1]))));
		double fTemp20 = (fConst54 * fRec31[1]);
		fRec31[0] = ((fConst20 * (((fConst22 * fRec32[0]) + (fConst45 * fRec32[1])) + (fConst22 * fRec32[2]))) - (fConst49 * ((fConst51 * fRec31[2]) + fTemp20)));
		double fTemp21 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow7 * (fRec31[2] + (fConst49 * (fTemp20 + (fConst51 * fRec31[0])))))));
		fRec41[0] = ((fConst55 * fRec36[1]) - (fConst29 * ((fConst30 * fRec41[1]) - (fConst24 * fRec36[0]))));
		fRec40[0] = (fRec41[0] - (fConst25 * ((fConst36 * fRec40[2]) + (fConst39 * fRec40[1]))));
		double fTemp22 = (fConst44 * fRec39[1]);
		fRec39[0] = ((fConst25 * (((fConst38 * fRec40[0]) + (fConst56 * fRec40[1])) + (fConst38 * fRec40[2]))) - (fConst57 * ((fConst58 * fRec39[2]) + fTemp22)));
		double fTemp23 = (fConst54 * fRec38[1]);
		fRec38[0] = ((fRec39[2] + (fConst57 * (fTemp22 + (fConst58 * fRec39[0])))) - (fConst49 * ((fConst51 * fRec38[2]) + fTemp23)));
		double fTemp24 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow8 * (fRec38[2] + (fConst49 * (fTemp23 + (fConst51 * fRec38[0])))))));
		fRec45[0] = (0.0 - (fConst61 * ((fConst41 * fRec45[1]) - (fConst25 * (fTemp19 + fVec6[1])))));
		fRec44[0] = (fRec45[0] - (fConst20 * ((fConst43 * fRec44[2]) + (fConst44 * fRec44[1]))));
		double fTemp25 = (fRec44[2] + (fRec44[0] + (2.0 * fRec44[1])));
		fVec7[0] = fTemp25;
		fRec43[0] = ((fConst20 * ((fConst60 * fTemp25) + (fConst62 * fVec7[1]))) - (fConst63 * fRec43[1]));
		fRec42[0] = (fRec43[0] - (fConst59 * ((fConst64 * fRec42[2]) + (fConst54 * fRec42[1]))));
		double fTemp26 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow9 * (((fConst53 * fRec42[0]) + (fConst65 * fRec42[1])) + (fConst53 * fRec42[2])))));
		fRec47[0] = (0.0 - (fConst66 * ((fConst50 * fRec47[1]) - (fConst20 * (fTemp25 + fVec7[1])))));
		fRec46[0] = (fRec47[0] - (fConst59 * ((fConst64 * fRec46[2]) + (fConst54 * fRec46[1]))));
		double fTemp27 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow10 * (fRec46[2] + (fRec46[0] + (2.0 * fRec46[1]))))));
		double fTemp28 = (((1.333521432 * (fTemp21 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp21))))) + (1.584893192 * ((fTemp24 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp24)))) + (fTemp26 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp26))))))) + (1.2589412 * (fTemp27 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp27))))));
		fVec8[0] = fTemp28;
		fRec30[0] = (0.0 - (fConst6 * ((fConst7 * fRec30[1]) - (fTemp28 + fVec8[1]))));
		double fTemp29 = (((fTemp13 * ((fTemp14 * ((fSlow2 * ((0.099750623441396499 * (1.0 - std::fabs((0.024937655860349125 * (fTemp14 * fTemp13))))) + -0.024937655860349125)) + 0.024937655860349125)) + fTemp15)) + ((0.5 * (fTemp17 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp17))))) + (fSlow6 * fRec30[0]))) + 1.0000000000000001e-15);
		fVec9[0] = fTemp29;
		fRec25[0] = ((0.93028479253239138 * (fTemp29 + fVec9[1])) - (0.86056958506478287 * fRec25[1]));
		fRec24[0] = (fRec25[0] - ((1.8405051250752198 * fRec24[1]) + (0.86129424393186271 * fRec24[2])));
		double fTemp30 = ((0.027 * fRec23[1]) + 1.0000000000000001e-15);
		fVec10[0] = fTemp30;
		fRec48[0] = (0.0 - (fConst68 * ((fConst69 * fRec48[1]) - (fTemp30 + fVec10[1]))));
		fRec23[0] = (double(Ftube(int(TUBE_TABLE_12AU7_68k), double((((0.92544984225177063 * (fRec24[0] + fRec24[2])) + (fRec48[0] + (1.8508996845035413 * fRec24[1]))) + -1.2572399999999999)))) + -83.435555555555567);
		fRec22[0] = ((0.10000000000000001 * ((fConst4 * fRec23[0]) + (fConst11 * fRec23[1]))) - (fConst12 * fRec22[1]));
		fRec16[0] = (fRec17[0] - fRec22[0]);
		fRec49[0] = (fSlow11 + (0.999 * fRec49[1]));
		double fTemp31 = (fRec16[0] * fRec49[0]);
		fVec11[0] = fTemp31;
		fRec15[0] = (0.0 - (fConst6 * ((fConst7 * fRec15[1]) - (fTemp31 + fVec11[1]))));
		double fTemp32 = (fRec15[0] + 1.0000000000000001e-15);
		fVec12[0] = fTemp32;
		fRec14[0] = ((0.93028479253239138 * (fTemp32 + fVec12[1])) - (0.86056958506478287 * fRec14[1]));
		fRec13[0] = (fRec14[0] - ((1.8405051250752198 * fRec13[1]) + (0.86129424393186271 * fRec13[2])));
		double fTemp33 = ((0.014999999999999999 * fRec12[1]) + 1.0000000000000001e-15);
		fVec13[0] = fTemp33;
		fRec50[0] = (0.0 - (fConst14 * ((fConst15 * fRec50[1]) - (fTemp33 + fVec13[1]))));
		fRec12[0] = (double(Ftube(int(TUBE_TABLE_12AU7_250k), double((((0.92544984225177063 * (fRec13[0] + fRec13[2])) + (fRec50[0] + (1.8508996845035413 * fRec13[1]))) + -0.77616200000000002)))) + -78.255866666666662);
		fRec11[0] = ((0.10000000000000001 * ((fConst4 * fRec12[0]) + (fConst11 * fRec12[1]))) - (fConst12 * fRec11[1]));
		fRec5[0] = (fRec6[0] + fRec11[0]);
		fRec4[0] = (0.0 - (fConst6 * ((fConst7 * fRec4[1]) - (fRec5[0] + fRec5[1]))));
		double fTemp34 = (fRec4[0] + 1.0000000000000001e-15);
		fVec14[0] = fTemp34;
		fRec3[0] = ((0.93028479253239138 * (fTemp34 + fVec14[1])) - (0.86056958506478287 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.86129424393186271 * fRec2[2])));
		double fTemp35 = ((0.0082000000000000007 * fRec1[1]) + 1.0000000000000001e-15);
		fVec15[0] = fTemp35;
		fRec51[0] = (0.0 - (fConst9 * ((fConst10 * fRec51[1]) - (fTemp35 + fVec15[1]))));
		fRec1[0] = (double(Ftube(int(TUBE_TABLE_12AU7_250k), double((((0.92544984225177063 * (fRec2[0] + fRec2[2])) + (fRec51[0] + (1.8508996845035413 * fRec2[1]))) + -0.44548700000000002)))) + -75.672317073170731);
		fRec0[0] = ((0.10000000000000001 * ((fConst4 * fRec1[0]) + (fConst11 * fRec1[1]))) - (fConst12 * fRec0[1]));
		fRec52[0] = (fSlow12 + (0.999 * fRec52[1]));
		output0[i] = FAUSTFLOAT((fRec0[0] * fRec52[0]));
		double fTemp36 = (fRec58[1] + 1.0000000000000001e-15);
		fVec16[0] = fTemp36;
		fRec62[0] = ((0.93028479253239138 * (fTemp36 + fVec16[1])) - (0.86056958506478287 * fRec62[1]));
		fRec61[0] = (fRec62[0] - ((1.8405051250752198 * fRec61[1]) + (0.86129424393186271 * fRec61[2])));
		double fTemp37 = ((0.0082000000000000007 * fRec60[1]) + 1.0000000000000001e-15);
		fVec17[0] = fTemp37;
		fRec63[0] = (0.0 - (fConst9 * ((fConst10 * fRec63[1]) - (fTemp37 + fVec17[1]))));
		fRec60[0] = (double(Ftube(int(TUBE_TABLE_12AU7_250k), double((((0.92544984225177063 * (fRec61[0] + fRec61[2])) + (fRec63[0] + (1.8508996845035413 * fRec61[1]))) + -0.44548700000000002)))) + -75.672317073170731);
		fRec59[0] = ((0.10000000000000001 * ((fConst4 * fRec60[0]) + (fConst11 * fRec60[1]))) - (fConst12 * fRec59[1]));
		double fTemp38 = (fRec69[1] + 1.0000000000000001e-15);
		fVec18[0] = fTemp38;
		fRec73[0] = ((0.93028479253239138 * (fTemp38 + fVec18[1])) - (0.86056958506478287 * fRec73[1]));
		fRec72[0] = (fRec73[0] - ((1.8405051250752198 * fRec72[1]) + (0.86129424393186271 * fRec72[2])));
		double fTemp39 = ((0.014999999999999999 * fRec71[1]) + 1.0000000000000001e-15);
		fVec19[0] = fTemp39;
		fRec74[0] = (0.0 - (fConst14 * ((fConst15 * fRec74[1]) - (fTemp39 + fVec19[1]))));
		fRec71[0] = (double(Ftube(int(TUBE_TABLE_12AU7_250k), double((((0.92544984225177063 * (fRec72[0] + fRec72[2])) + (fRec74[0] + (1.8508996845035413 * fRec72[1]))) + -0.77616200000000002)))) + -78.255866666666662);
		fRec70[0] = ((0.10000000000000001 * ((fConst4 * fRec71[0]) + (fConst11 * fRec71[1]))) - (fConst12 * fRec70[1]));
		double fTemp40 = double(input1[i]);
		double fTemp41 = std::fabs(fTemp40);
		fRec79[0] = ((0.99990000000000001 * fRec79[1]) + (9.9999999999988987e-05 * fTemp41));
		double fTemp42 = std::max<double>(fRec79[0], fTemp41);
		fVec20[(IOTA & 32767)] = fTemp42;
		fRec81[0] = ((fTemp42 + fRec81[1]) - fVec20[((IOTA - iConst17) & 32767)]);
		fRec80[0] = ((0.999 * fRec80[1]) + (fConst16 * fRec81[0]));
		double fTemp43 = std::max<double>(-1.0, std::min<double>(-0.01, (fTemp42 + (-1.0 - (1.02 * fRec80[0])))));
		double fTemp44 = (fTemp40 - fTemp43);
		double fTemp45 = (40.100000000000001 * fTemp44);
		double fTemp46 = std::max<double>(-600.0, fTemp45);
		double fTemp47 = (0.0 - (40.100000000000001 * fTemp43));
		double fTemp48 = std::max<double>(-600.0, fTemp47);
		double fTemp49 = (((std::fabs(fTemp45) > 0.0001)?((fTemp46 < -50.0)?(0.0 - (fTemp46 * std::exp(fTemp46))):(fTemp46 / (1.0 - std::exp((-1.0 * fTemp46))))):((fTemp44 * ((134.00083333333336 * fTemp44) + 20.050000000000001)) + 1.0)) - ((std::fabs(fTemp47) > 0.0001)?((fTemp48 < -50.0)?(0.0 - (fTemp48 * std::exp(fTemp48))):(fTemp48 / (1.0 - std::exp((-1.0 * fTemp48))))):((fTemp47 * ((0.083333333333333329 * fTemp47) + 0.5)) + 1.0)));
		double fTemp50 = (0.024937655860349125 * (fRec29[0] * fTemp49));
		double fTemp51 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow5 * std::max<double>(-0.69999999999999996, std::min<double>(0.69999999999999996, fTemp50)))));
		fRec89[0] = (fTemp50 - (fConst33 * ((fConst34 * fRec89[2]) + (fConst35 * fRec89[1]))));
		double fTemp52 = (fRec89[2] + (fRec89[0] + (2.0 * fRec89[1])));
		fVec21[0] = fTemp52;
		fRec88[0] = ((fConst33 * ((fConst4 * fTemp52) + (fConst11 * fVec21[1]))) - (fConst12 * fRec88[1]));
		fRec87[0] = (0.0 - (fConst29 * ((fConst30 * fRec87[1]) - (fRec88[0] + fRec88[1]))));
		fRec86[0] = (fRec87[0] - (fConst25 * ((fConst36 * fRec86[2]) + (fConst39 * fRec86[1]))));
		double fTemp53 = (fRec86[2] + (fRec86[0] + (2.0 * fRec86[1])));
		fVec22[0] = fTemp53;
		fRec85[0] = ((fConst25 * ((fConst27 * fTemp53) + (fConst40 * fVec22[1]))) - (fConst42 * fRec85[1]));
		fRec84[0] = (fRec85[0] - (fConst20 * ((fConst43 * fRec84[2]) + (fConst44 * fRec84[1]))));
		double fTemp54 = (fConst54 * fRec83[1]);
		fRec83[0] = ((fConst20 * (((fConst22 * fRec84[0]) + (fConst45 * fRec84[1])) + (fConst22 * fRec84[2]))) - (fConst49 * ((fConst51 * fRec83[2]) + fTemp54)));
		double fTemp55 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow7 * (fRec83[2] + (fConst49 * (fTemp54 + (fConst51 * fRec83[0])))))));
		fRec93[0] = ((fConst55 * fRec88[1]) - (fConst29 * ((fConst30 * fRec93[1]) - (fConst24 * fRec88[0]))));
		fRec92[0] = (fRec93[0] - (fConst25 * ((fConst36 * fRec92[2]) + (fConst39 * fRec92[1]))));
		double fTemp56 = (fConst44 * fRec91[1]);
		fRec91[0] = ((fConst25 * (((fConst38 * fRec92[0]) + (fConst56 * fRec92[1])) + (fConst38 * fRec92[2]))) - (fConst57 * ((fConst58 * fRec91[2]) + fTemp56)));
		double fTemp57 = (fConst54 * fRec90[1]);
		fRec90[0] = ((fRec91[2] + (fConst57 * (fTemp56 + (fConst58 * fRec91[0])))) - (fConst49 * ((fConst51 * fRec90[2]) + fTemp57)));
		double fTemp58 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow8 * (fRec90[2] + (fConst49 * (fTemp57 + (fConst51 * fRec90[0])))))));
		fRec97[0] = (0.0 - (fConst61 * ((fConst41 * fRec97[1]) - (fConst25 * (fTemp53 + fVec22[1])))));
		fRec96[0] = (fRec97[0] - (fConst20 * ((fConst43 * fRec96[2]) + (fConst44 * fRec96[1]))));
		double fTemp59 = (fRec96[2] + (fRec96[0] + (2.0 * fRec96[1])));
		fVec23[0] = fTemp59;
		fRec95[0] = ((fConst20 * ((fConst60 * fTemp59) + (fConst62 * fVec23[1]))) - (fConst63 * fRec95[1]));
		fRec94[0] = (fRec95[0] - (fConst59 * ((fConst64 * fRec94[2]) + (fConst54 * fRec94[1]))));
		double fTemp60 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow9 * (((fConst53 * fRec94[0]) + (fConst65 * fRec94[1])) + (fConst53 * fRec94[2])))));
		fRec99[0] = (0.0 - (fConst66 * ((fConst50 * fRec99[1]) - (fConst20 * (fTemp59 + fVec23[1])))));
		fRec98[0] = (fRec99[0] - (fConst59 * ((fConst64 * fRec98[2]) + (fConst54 * fRec98[1]))));
		double fTemp61 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow10 * (fRec98[2] + (fRec98[0] + (2.0 * fRec98[1]))))));
		double fTemp62 = (((1.333521432 * (fTemp55 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp55))))) + (1.584893192 * ((fTemp58 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp58)))) + (fTemp60 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp60))))))) + (1.2589412 * (fTemp61 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp61))))));
		fVec24[0] = fTemp62;
		fRec82[0] = (0.0 - (fConst6 * ((fConst7 * fRec82[1]) - (fTemp62 + fVec24[1]))));
		double fTemp63 = (((fTemp49 * (fTemp15 + (fTemp14 * ((fSlow2 * ((0.099750623441396499 * (1.0 - std::fabs((0.024937655860349125 * (fTemp14 * fTemp49))))) + -0.024937655860349125)) + 0.024937655860349125)))) + ((0.5 * (fTemp51 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp51))))) + (fSlow6 * fRec82[0]))) + 1.0000000000000001e-15);
		fVec25[0] = fTemp63;
		fRec78[0] = ((0.93028479253239138 * (fTemp63 + fVec25[1])) - (0.86056958506478287 * fRec78[1]));
		fRec77[0] = (fRec78[0] - ((1.8405051250752198 * fRec77[1]) + (0.86129424393186271 * fRec77[2])));
		double fTemp64 = ((0.027 * fRec76[1]) + 1.0000000000000001e-15);
		fVec26[0] = fTemp64;
		fRec100[0] = (0.0 - (fConst68 * ((fConst69 * fRec100[1]) - (fTemp64 + fVec26[1]))));
		fRec76[0] = (double(Ftube(int(TUBE_TABLE_12AU7_68k), double((((0.92544984225177063 * (fRec77[0] + fRec77[2])) + (fRec100[0] + (1.8508996845035413 * fRec77[1]))) + -1.2572399999999999)))) + -83.435555555555567);
		fRec75[0] = ((0.10000000000000001 * ((fConst4 * fRec76[0]) + (fConst11 * fRec76[1]))) - (fConst12 * fRec75[1]));
		fRec69[0] = (fRec70[0] - fRec75[0]);
		double fTemp65 = (fRec49[0] * fRec69[0]);
		fVec27[0] = fTemp65;
		fRec68[0] = (0.0 - (fConst6 * ((fConst7 * fRec68[1]) - (fTemp65 + fVec27[1]))));
		double fTemp66 = (fRec68[0] + 1.0000000000000001e-15);
		fVec28[0] = fTemp66;
		fRec67[0] = ((0.93028479253239138 * (fTemp66 + fVec28[1])) - (0.86056958506478287 * fRec67[1]));
		fRec66[0] = (fRec67[0] - ((1.8405051250752198 * fRec66[1]) + (0.86129424393186271 * fRec66[2])));
		double fTemp67 = ((0.014999999999999999 * fRec65[1]) + 1.0000000000000001e-15);
		fVec29[0] = fTemp67;
		fRec101[0] = (0.0 - (fConst14 * ((fConst15 * fRec101[1]) - (fTemp67 + fVec29[1]))));
		fRec65[0] = (double(Ftube(int(TUBE_TABLE_12AU7_250k), double((((0.92544984225177063 * (fRec66[0] + fRec66[2])) + (fRec101[0] + (1.8508996845035413 * fRec66[1]))) + -0.77616200000000002)))) + -78.255866666666662);
		fRec64[0] = ((0.10000000000000001 * ((fConst4 * fRec65[0]) + (fConst11 * fRec65[1]))) - (fConst12 * fRec64[1]));
		fRec58[0] = (fRec59[0] + fRec64[0]);
		fRec57[0] = (0.0 - (fConst6 * ((fConst7 * fRec57[1]) - (fRec58[0] + fRec58[1]))));
		double fTemp68 = (fRec57[0] + 1.0000000000000001e-15);
		fVec30[0] = fTemp68;
		fRec56[0] = ((0.93028479253239138 * (fTemp68 + fVec30[1])) - (0.86056958506478287 * fRec56[1]));
		fRec55[0] = (fRec56[0] - ((1.8405051250752198 * fRec55[1]) + (0.86129424393186271 * fRec55[2])));
		double fTemp69 = ((0.0082000000000000007 * fRec54[1]) + 1.0000000000000001e-15);
		fVec31[0] = fTemp69;
		fRec102[0] = (0.0 - (fConst9 * ((fConst10 * fRec102[1]) - (fTemp69 + fVec31[1]))));
		fRec54[0] = (double(Ftube(int(TUBE_TABLE_12AU7_250k), double((((0.92544984225177063 * (fRec55[0] + fRec55[2])) + (fRec102[0] + (1.8508996845035413 * fRec55[1]))) + -0.44548700000000002)))) + -75.672317073170731);
		fRec53[0] = ((0.10000000000000001 * ((fConst4 * fRec54[0]) + (fConst11 * fRec54[1]))) - (fConst12 * fRec53[1]));
		output1[i] = FAUSTFLOAT((fRec52[0] * fRec53[0]));
		fVec0[1] = fVec0[0];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fVec1[1] = fVec1[0];
		fRec10[1] = fRec10[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fVec2[1] = fVec2[0];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fVec3[1] = fVec3[0];
		fRec21[1] = fRec21[0];
		fRec18[1] = fRec18[0];
		fRec17[1] = fRec17[0];
		fRec26[1] = fRec26[0];
		IOTA = (IOTA + 1);
		fRec28[1] = fRec28[0];
		fRec27[1] = fRec27[0];
		fRec29[1] = fRec29[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fVec5[1] = fVec5[0];
		fRec36[1] = fRec36[0];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fVec6[1] = fVec6[0];
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fRec41[1] = fRec41[0];
		fRec40[2] = fRec40[1];
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		fRec45[1] = fRec45[0];
		fRec44[2] = fRec44[1];
		fRec44[1] = fRec44[0];
		fVec7[1] = fVec7[0];
		fRec43[1] = fRec43[0];
		fRec42[2] = fRec42[1];
		fRec42[1] = fRec42[0];
		fRec47[1] = fRec47[0];
		fRec46[2] = fRec46[1];
		fRec46[1] = fRec46[0];
		fVec8[1] = fVec8[0];
		fRec30[1] = fRec30[0];
		fVec9[1] = fVec9[0];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fVec10[1] = fVec10[0];
		fRec48[1] = fRec48[0];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec16[1] = fRec16[0];
		fRec49[1] = fRec49[0];
		fVec11[1] = fVec11[0];
		fRec15[1] = fRec15[0];
		fVec12[1] = fVec12[0];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fVec13[1] = fVec13[0];
		fRec50[1] = fRec50[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fVec14[1] = fVec14[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fVec15[1] = fVec15[0];
		fRec51[1] = fRec51[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec52[1] = fRec52[0];
		fVec16[1] = fVec16[0];
		fRec62[1] = fRec62[0];
		fRec61[2] = fRec61[1];
		fRec61[1] = fRec61[0];
		fVec17[1] = fVec17[0];
		fRec63[1] = fRec63[0];
		fRec60[1] = fRec60[0];
		fRec59[1] = fRec59[0];
		fVec18[1] = fVec18[0];
		fRec73[1] = fRec73[0];
		fRec72[2] = fRec72[1];
		fRec72[1] = fRec72[0];
		fVec19[1] = fVec19[0];
		fRec74[1] = fRec74[0];
		fRec71[1] = fRec71[0];
		fRec70[1] = fRec70[0];
		fRec79[1] = fRec79[0];
		fRec81[1] = fRec81[0];
		fRec80[1] = fRec80[0];
		fRec89[2] = fRec89[1];
		fRec89[1] = fRec89[0];
		fVec21[1] = fVec21[0];
		fRec88[1] = fRec88[0];
		fRec87[1] = fRec87[0];
		fRec86[2] = fRec86[1];
		fRec86[1] = fRec86[0];
		fVec22[1] = fVec22[0];
		fRec85[1] = fRec85[0];
		fRec84[2] = fRec84[1];
		fRec84[1] = fRec84[0];
		fRec83[2] = fRec83[1];
		fRec83[1] = fRec83[0];
		fRec93[1] = fRec93[0];
		fRec92[2] = fRec92[1];
		fRec92[1] = fRec92[0];
		fRec91[2] = fRec91[1];
		fRec91[1] = fRec91[0];
		fRec90[2] = fRec90[1];
		fRec90[1] = fRec90[0];
		fRec97[1] = fRec97[0];
		fRec96[2] = fRec96[1];
		fRec96[1] = fRec96[0];
		fVec23[1] = fVec23[0];
		fRec95[1] = fRec95[0];
		fRec94[2] = fRec94[1];
		fRec94[1] = fRec94[0];
		fRec99[1] = fRec99[0];
		fRec98[2] = fRec98[1];
		fRec98[1] = fRec98[0];
		fVec24[1] = fVec24[0];
		fRec82[1] = fRec82[0];
		fVec25[1] = fVec25[0];
		fRec78[1] = fRec78[0];
		fRec77[2] = fRec77[1];
		fRec77[1] = fRec77[0];
		fVec26[1] = fVec26[0];
		fRec100[1] = fRec100[0];
		fRec76[1] = fRec76[0];
		fRec75[1] = fRec75[0];
		fRec69[1] = fRec69[0];
		fVec27[1] = fVec27[0];
		fRec68[1] = fRec68[0];
		fVec28[1] = fVec28[0];
		fRec67[1] = fRec67[0];
		fRec66[2] = fRec66[1];
		fRec66[1] = fRec66[0];
		fVec29[1] = fVec29[0];
		fRec101[1] = fRec101[0];
		fRec65[1] = fRec65[0];
		fRec64[1] = fRec64[0];
		fRec58[1] = fRec58[0];
		fRec57[1] = fRec57[0];
		fVec30[1] = fVec30[0];
		fRec56[1] = fRec56[0];
		fRec55[2] = fRec55[1];
		fRec55[1] = fRec55[0];
		fVec31[1] = fVec31[0];
		fRec102[1] = fRec102[0];
		fRec54[1] = fRec54[0];
		fRec53[1] = fRec53[0];
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
#undef fVslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case DRIVE: 
		fVslider1_ = (float*)data; // , 0.34999999999999998, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fVslider0_ = (float*)data; // , 100.0, 0.0, 100.0, 1.0 
		break;
	case PREGAIN: 
		fVslider2_ = (float*)data; // , -6.0, -20.0, 20.0, 0.10000000000000001 
		break;
	case GAIN1: 
		fVslider3_ = (float*)data; // , -6.0, -20.0, 20.0, 0.10000000000000001 
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
   WET_DRY, 
   PREGAIN, 
   GAIN1, 
} PortIndex;
*/

} // end namespace gxamp11_stereo
