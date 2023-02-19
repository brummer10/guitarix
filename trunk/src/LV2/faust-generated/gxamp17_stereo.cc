// generated from file '../src/LV2/faust/gxamp17_stereo.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxamp17_stereo {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst4;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	double fRec9[2];
	double fRec8[3];
	double fConst6;
	double fVec0[2];
	double fConst7;
	double fRec10[2];
	double fRec7[2];
	double fConst8;
	double fConst9;
	double fRec6[2];
	double fConst11;
	double fConst12;
	double fRec11[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec17[2];
	double fConst15;
	double fConst16;
	double fConst18;
	double fConst19;
	double fConst22;
	double fConst23;
	double fConst25;
	double fConst26;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst35;
	double fConst37;
	double fConst38;
	double fRec34[2];
	int IOTA0;
	double fVec1[32768];
	int iConst39;
	double fRec33[2];
	double fConst40;
	double fRec32[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec35[2];
	double fRec31[3];
	double fVec2[2];
	double fRec30[2];
	double fConst41;
	double fConst43;
	double fRec29[2];
	double fRec28[3];
	double fVec3[2];
	double fConst44;
	double fConst46;
	double fRec27[2];
	double fRec26[3];
	double fVec4[2];
	double fConst47;
	double fConst49;
	double fRec25[2];
	double fRec24[3];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fConst50;
	double fConst51;
	double fConst52;
	double fRec37[2];
	double fRec36[3];
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fRec41[2];
	double fRec40[3];
	double fConst59;
	double fRec39[3];
	double fRec38[3];
	double fConst60;
	double fConst61;
	double fConst62;
	double fRec44[2];
	double fRec43[3];
	double fConst63;
	double fRec42[3];
	double fVec5[2];
	double fConst65;
	double fConst66;
	double fRec23[2];
	double fVec6[2];
	double fRec22[2];
	double fRec21[3];
	double fConst68;
	double fVec7[2];
	double fConst69;
	double fRec45[2];
	double fRec20[2];
	double fRec19[2];
	double fRec46[2];
	double fRec50[2];
	double fRec49[3];
	double fConst71;
	double fVec8[2];
	double fConst72;
	double fRec51[2];
	double fRec48[2];
	double fRec47[2];
	double fRec52[2];
	double fRec18[3];
	double fVec9[2];
	double fRec16[2];
	double fRec15[2];
	double fRec14[3];
	double fVec10[2];
	double fRec53[2];
	double fRec13[2];
	double fRec12[2];
	double fRec54[2];
	double fRec5[3];
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fVec11[2];
	double fRec55[2];
	double fRec1[2];
	double fRec0[2];
	double fRec56[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec57[2];
	double fRec67[2];
	double fRec66[3];
	double fVec12[2];
	double fRec68[2];
	double fRec65[2];
	double fRec64[2];
	double fRec69[2];
	double fRec91[2];
	double fVec13[32768];
	double fRec90[2];
	double fRec89[2];
	double fRec88[3];
	double fVec14[2];
	double fRec87[2];
	double fRec86[2];
	double fRec85[3];
	double fVec15[2];
	double fRec84[2];
	double fRec83[3];
	double fVec16[2];
	double fRec82[2];
	double fRec81[3];
	double fRec93[2];
	double fRec92[3];
	double fRec97[2];
	double fRec96[3];
	double fRec95[3];
	double fRec94[3];
	double fRec100[2];
	double fRec99[3];
	double fRec98[3];
	double fVec17[2];
	double fRec80[2];
	double fVec18[2];
	double fRec79[2];
	double fRec78[3];
	double fVec19[2];
	double fRec101[2];
	double fRec77[2];
	double fRec76[2];
	double fRec102[2];
	double fRec106[2];
	double fRec105[3];
	double fVec20[2];
	double fRec107[2];
	double fRec104[2];
	double fRec103[2];
	double fRec108[2];
	double fRec75[3];
	double fVec21[2];
	double fRec74[2];
	double fRec73[2];
	double fRec72[3];
	double fVec22[2];
	double fRec109[2];
	double fRec71[2];
	double fRec70[2];
	double fRec110[2];
	double fRec63[3];
	double fRec62[2];
	double fRec61[2];
	double fRec60[3];
	double fVec23[2];
	double fRec111[2];
	double fRec59[2];
	double fRec58[2];
	double fRec112[2];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
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
	id = "12AT7 feedback";
	name = N_("12AT7 feedback");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec9[l0] = 0.0;
	for (int l1 = 0; l1 < 3; l1 = l1 + 1) fRec8[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fVec0[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec10[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec7[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec6[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec11[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec17[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec34[l8] = 0.0;
	for (int l9 = 0; l9 < 32768; l9 = l9 + 1) fVec1[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec33[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec32[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec35[l12] = 0.0;
	for (int l13 = 0; l13 < 3; l13 = l13 + 1) fRec31[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fVec2[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec30[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec29[l16] = 0.0;
	for (int l17 = 0; l17 < 3; l17 = l17 + 1) fRec28[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fVec3[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec27[l19] = 0.0;
	for (int l20 = 0; l20 < 3; l20 = l20 + 1) fRec26[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fVec4[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec25[l22] = 0.0;
	for (int l23 = 0; l23 < 3; l23 = l23 + 1) fRec24[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec37[l24] = 0.0;
	for (int l25 = 0; l25 < 3; l25 = l25 + 1) fRec36[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec41[l26] = 0.0;
	for (int l27 = 0; l27 < 3; l27 = l27 + 1) fRec40[l27] = 0.0;
	for (int l28 = 0; l28 < 3; l28 = l28 + 1) fRec39[l28] = 0.0;
	for (int l29 = 0; l29 < 3; l29 = l29 + 1) fRec38[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec44[l30] = 0.0;
	for (int l31 = 0; l31 < 3; l31 = l31 + 1) fRec43[l31] = 0.0;
	for (int l32 = 0; l32 < 3; l32 = l32 + 1) fRec42[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fVec5[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fRec23[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fVec6[l35] = 0.0;
	for (int l36 = 0; l36 < 2; l36 = l36 + 1) fRec22[l36] = 0.0;
	for (int l37 = 0; l37 < 3; l37 = l37 + 1) fRec21[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fVec7[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec45[l39] = 0.0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec20[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec19[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) fRec46[l42] = 0.0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fRec50[l43] = 0.0;
	for (int l44 = 0; l44 < 3; l44 = l44 + 1) fRec49[l44] = 0.0;
	for (int l45 = 0; l45 < 2; l45 = l45 + 1) fVec8[l45] = 0.0;
	for (int l46 = 0; l46 < 2; l46 = l46 + 1) fRec51[l46] = 0.0;
	for (int l47 = 0; l47 < 2; l47 = l47 + 1) fRec48[l47] = 0.0;
	for (int l48 = 0; l48 < 2; l48 = l48 + 1) fRec47[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec52[l49] = 0.0;
	for (int l50 = 0; l50 < 3; l50 = l50 + 1) fRec18[l50] = 0.0;
	for (int l51 = 0; l51 < 2; l51 = l51 + 1) fVec9[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fRec16[l52] = 0.0;
	for (int l53 = 0; l53 < 2; l53 = l53 + 1) fRec15[l53] = 0.0;
	for (int l54 = 0; l54 < 3; l54 = l54 + 1) fRec14[l54] = 0.0;
	for (int l55 = 0; l55 < 2; l55 = l55 + 1) fVec10[l55] = 0.0;
	for (int l56 = 0; l56 < 2; l56 = l56 + 1) fRec53[l56] = 0.0;
	for (int l57 = 0; l57 < 2; l57 = l57 + 1) fRec13[l57] = 0.0;
	for (int l58 = 0; l58 < 2; l58 = l58 + 1) fRec12[l58] = 0.0;
	for (int l59 = 0; l59 < 2; l59 = l59 + 1) fRec54[l59] = 0.0;
	for (int l60 = 0; l60 < 3; l60 = l60 + 1) fRec5[l60] = 0.0;
	for (int l61 = 0; l61 < 2; l61 = l61 + 1) fRec4[l61] = 0.0;
	for (int l62 = 0; l62 < 2; l62 = l62 + 1) fRec3[l62] = 0.0;
	for (int l63 = 0; l63 < 3; l63 = l63 + 1) fRec2[l63] = 0.0;
	for (int l64 = 0; l64 < 2; l64 = l64 + 1) fVec11[l64] = 0.0;
	for (int l65 = 0; l65 < 2; l65 = l65 + 1) fRec55[l65] = 0.0;
	for (int l66 = 0; l66 < 2; l66 = l66 + 1) fRec1[l66] = 0.0;
	for (int l67 = 0; l67 < 2; l67 = l67 + 1) fRec0[l67] = 0.0;
	for (int l68 = 0; l68 < 2; l68 = l68 + 1) fRec56[l68] = 0.0;
	for (int l69 = 0; l69 < 2; l69 = l69 + 1) fRec57[l69] = 0.0;
	for (int l70 = 0; l70 < 2; l70 = l70 + 1) fRec67[l70] = 0.0;
	for (int l71 = 0; l71 < 3; l71 = l71 + 1) fRec66[l71] = 0.0;
	for (int l72 = 0; l72 < 2; l72 = l72 + 1) fVec12[l72] = 0.0;
	for (int l73 = 0; l73 < 2; l73 = l73 + 1) fRec68[l73] = 0.0;
	for (int l74 = 0; l74 < 2; l74 = l74 + 1) fRec65[l74] = 0.0;
	for (int l75 = 0; l75 < 2; l75 = l75 + 1) fRec64[l75] = 0.0;
	for (int l76 = 0; l76 < 2; l76 = l76 + 1) fRec69[l76] = 0.0;
	for (int l77 = 0; l77 < 2; l77 = l77 + 1) fRec91[l77] = 0.0;
	for (int l78 = 0; l78 < 32768; l78 = l78 + 1) fVec13[l78] = 0.0;
	for (int l79 = 0; l79 < 2; l79 = l79 + 1) fRec90[l79] = 0.0;
	for (int l80 = 0; l80 < 2; l80 = l80 + 1) fRec89[l80] = 0.0;
	for (int l81 = 0; l81 < 3; l81 = l81 + 1) fRec88[l81] = 0.0;
	for (int l82 = 0; l82 < 2; l82 = l82 + 1) fVec14[l82] = 0.0;
	for (int l83 = 0; l83 < 2; l83 = l83 + 1) fRec87[l83] = 0.0;
	for (int l84 = 0; l84 < 2; l84 = l84 + 1) fRec86[l84] = 0.0;
	for (int l85 = 0; l85 < 3; l85 = l85 + 1) fRec85[l85] = 0.0;
	for (int l86 = 0; l86 < 2; l86 = l86 + 1) fVec15[l86] = 0.0;
	for (int l87 = 0; l87 < 2; l87 = l87 + 1) fRec84[l87] = 0.0;
	for (int l88 = 0; l88 < 3; l88 = l88 + 1) fRec83[l88] = 0.0;
	for (int l89 = 0; l89 < 2; l89 = l89 + 1) fVec16[l89] = 0.0;
	for (int l90 = 0; l90 < 2; l90 = l90 + 1) fRec82[l90] = 0.0;
	for (int l91 = 0; l91 < 3; l91 = l91 + 1) fRec81[l91] = 0.0;
	for (int l92 = 0; l92 < 2; l92 = l92 + 1) fRec93[l92] = 0.0;
	for (int l93 = 0; l93 < 3; l93 = l93 + 1) fRec92[l93] = 0.0;
	for (int l94 = 0; l94 < 2; l94 = l94 + 1) fRec97[l94] = 0.0;
	for (int l95 = 0; l95 < 3; l95 = l95 + 1) fRec96[l95] = 0.0;
	for (int l96 = 0; l96 < 3; l96 = l96 + 1) fRec95[l96] = 0.0;
	for (int l97 = 0; l97 < 3; l97 = l97 + 1) fRec94[l97] = 0.0;
	for (int l98 = 0; l98 < 2; l98 = l98 + 1) fRec100[l98] = 0.0;
	for (int l99 = 0; l99 < 3; l99 = l99 + 1) fRec99[l99] = 0.0;
	for (int l100 = 0; l100 < 3; l100 = l100 + 1) fRec98[l100] = 0.0;
	for (int l101 = 0; l101 < 2; l101 = l101 + 1) fVec17[l101] = 0.0;
	for (int l102 = 0; l102 < 2; l102 = l102 + 1) fRec80[l102] = 0.0;
	for (int l103 = 0; l103 < 2; l103 = l103 + 1) fVec18[l103] = 0.0;
	for (int l104 = 0; l104 < 2; l104 = l104 + 1) fRec79[l104] = 0.0;
	for (int l105 = 0; l105 < 3; l105 = l105 + 1) fRec78[l105] = 0.0;
	for (int l106 = 0; l106 < 2; l106 = l106 + 1) fVec19[l106] = 0.0;
	for (int l107 = 0; l107 < 2; l107 = l107 + 1) fRec101[l107] = 0.0;
	for (int l108 = 0; l108 < 2; l108 = l108 + 1) fRec77[l108] = 0.0;
	for (int l109 = 0; l109 < 2; l109 = l109 + 1) fRec76[l109] = 0.0;
	for (int l110 = 0; l110 < 2; l110 = l110 + 1) fRec102[l110] = 0.0;
	for (int l111 = 0; l111 < 2; l111 = l111 + 1) fRec106[l111] = 0.0;
	for (int l112 = 0; l112 < 3; l112 = l112 + 1) fRec105[l112] = 0.0;
	for (int l113 = 0; l113 < 2; l113 = l113 + 1) fVec20[l113] = 0.0;
	for (int l114 = 0; l114 < 2; l114 = l114 + 1) fRec107[l114] = 0.0;
	for (int l115 = 0; l115 < 2; l115 = l115 + 1) fRec104[l115] = 0.0;
	for (int l116 = 0; l116 < 2; l116 = l116 + 1) fRec103[l116] = 0.0;
	for (int l117 = 0; l117 < 2; l117 = l117 + 1) fRec108[l117] = 0.0;
	for (int l118 = 0; l118 < 3; l118 = l118 + 1) fRec75[l118] = 0.0;
	for (int l119 = 0; l119 < 2; l119 = l119 + 1) fVec21[l119] = 0.0;
	for (int l120 = 0; l120 < 2; l120 = l120 + 1) fRec74[l120] = 0.0;
	for (int l121 = 0; l121 < 2; l121 = l121 + 1) fRec73[l121] = 0.0;
	for (int l122 = 0; l122 < 3; l122 = l122 + 1) fRec72[l122] = 0.0;
	for (int l123 = 0; l123 < 2; l123 = l123 + 1) fVec22[l123] = 0.0;
	for (int l124 = 0; l124 < 2; l124 = l124 + 1) fRec109[l124] = 0.0;
	for (int l125 = 0; l125 < 2; l125 = l125 + 1) fRec71[l125] = 0.0;
	for (int l126 = 0; l126 < 2; l126 = l126 + 1) fRec70[l126] = 0.0;
	for (int l127 = 0; l127 < 2; l127 = l127 + 1) fRec110[l127] = 0.0;
	for (int l128 = 0; l128 < 3; l128 = l128 + 1) fRec63[l128] = 0.0;
	for (int l129 = 0; l129 < 2; l129 = l129 + 1) fRec62[l129] = 0.0;
	for (int l130 = 0; l130 < 2; l130 = l130 + 1) fRec61[l130] = 0.0;
	for (int l131 = 0; l131 < 3; l131 = l131 + 1) fRec60[l131] = 0.0;
	for (int l132 = 0; l132 < 2; l132 = l132 + 1) fVec23[l132] = 0.0;
	for (int l133 = 0; l133 < 2; l133 = l133 + 1) fRec111[l133] = 0.0;
	for (int l134 = 0; l134 < 2; l134 = l134 + 1) fRec59[l134] = 0.0;
	for (int l135 = 0; l135 < 2; l135 = l135 + 1) fRec58[l135] = 0.0;
	for (int l136 = 0; l136 < 2; l136 = l136 + 1) fRec112[l136] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = std::tan(97.38937226128358 / fConst0);
	double fConst2 = 1.0 / fConst1;
	double fConst3 = fConst2 + 1.0;
	fConst4 = (1.0 - fConst2) / fConst3;
	double fConst5 = 1.0 / std::tan(609.4689747964198 / fConst0);
	fConst6 = 1.0 - fConst5;
	fConst7 = 1.0 / (fConst5 + 1.0);
	fConst8 = 1.0 / (fConst1 * fConst3);
	fConst9 = 0.0 - fConst8;
	double fConst10 = 3.141592653589793 / fConst0;
	fConst11 = 1.0 - fConst10;
	fConst12 = 1.0 / (fConst10 + 1.0);
	double fConst13 = std::tan(942.4777960769379 / fConst0);
	double fConst14 = mydsp_faustpower2_f(fConst13);
	fConst15 = 1.0 / fConst14;
	fConst16 = 2.0 * (1.0 - fConst15);
	double fConst17 = 1.0 / fConst13;
	fConst18 = (fConst17 + -1.0000000000000004) / fConst13 + 1.0;
	fConst19 = 1.0 / ((fConst17 + 1.0000000000000004) / fConst13 + 1.0);
	double fConst20 = std::tan(3769.9111843077517 / fConst0);
	double fConst21 = mydsp_faustpower2_f(fConst20);
	fConst22 = 1.0 / fConst21;
	fConst23 = 2.0 * (1.0 - fConst22);
	double fConst24 = 1.0 / fConst20;
	fConst25 = (fConst24 + -1.0000000000000004) / fConst20 + 1.0;
	fConst26 = 1.0 / ((fConst24 + 1.0000000000000004) / fConst20 + 1.0);
	double fConst27 = std::tan(10053.096491487338 / fConst0);
	double fConst28 = mydsp_faustpower2_f(fConst27);
	fConst29 = 1.0 / fConst28;
	fConst30 = 2.0 * (1.0 - fConst29);
	fConst31 = 1.0 / fConst27;
	fConst32 = (fConst31 + -1.0000000000000004) / fConst27 + 1.0;
	fConst33 = 1.0 / ((fConst31 + 1.0000000000000004) / fConst27 + 1.0);
	double fConst34 = std::tan(47123.8898038469 / fConst0);
	fConst35 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst34));
	double fConst36 = 1.0 / fConst34;
	fConst37 = (fConst36 + -1.414213562373095) / fConst34 + 1.0;
	fConst38 = 1.0 / ((fConst36 + 1.414213562373095) / fConst34 + 1.0);
	iConst39 = int(std::min<double>(65536.0, std::max<double>(0.0, 0.1111111111111111 * fConst0)));
	fConst40 = 0.009000000000000008 / fConst0;
	fConst41 = 1.0 - fConst31;
	double fConst42 = fConst31 + 1.0;
	fConst43 = 1.0 / fConst42;
	fConst44 = 1.0 - fConst24;
	double fConst45 = fConst24 + 1.0;
	fConst46 = 1.0 / fConst45;
	fConst47 = 1.0 - fConst17;
	double fConst48 = fConst17 + 1.0;
	fConst49 = 1.0 / fConst48;
	fConst50 = fConst47 / fConst48;
	fConst51 = 1.0 / (fConst13 * fConst48);
	fConst52 = 0.0 - fConst51;
	fConst53 = 0.0 - 2.0 / fConst14;
	fConst54 = 1.0 - fConst47 / fConst13;
	fConst55 = 1.0 / (fConst48 / fConst13 + 1.0);
	fConst56 = 1.0 - fConst44 / fConst20;
	fConst57 = 1.0 / (fConst45 / fConst20 + 1.0);
	fConst58 = 0.0 - 1.0 / (fConst27 * fConst42);
	fConst59 = 0.0 - 2.0 / fConst28;
	fConst60 = fConst44 / fConst45;
	fConst61 = 1.0 / (fConst20 * fConst45);
	fConst62 = 0.0 - fConst61;
	fConst63 = 0.0 - 2.0 / fConst21;
	double fConst64 = 1.0 / std::tan(20517.741620594938 / fConst0);
	fConst65 = 1.0 - fConst64;
	fConst66 = 1.0 / (fConst64 + 1.0);
	double fConst67 = 1.0 / std::tan(270.1769682087222 / fConst0);
	fConst68 = 1.0 - fConst67;
	fConst69 = 1.0 / (fConst67 + 1.0);
	double fConst70 = 1.0 / std::tan(414.6902302738527 / fConst0);
	fConst71 = 1.0 - fConst70;
	fConst72 = 1.0 / (fConst70 + 1.0);
	IOTA0 = 0;
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fCheckbox0 (*fCheckbox0_)
#define fCheckbox1 (*fCheckbox1_)
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	int iSlow0 = int(double(fCheckbox0));
	int iSlow1 = int(double(fCheckbox1));
	double fSlow2 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
	double fSlow3 = 1.000000000000001e-05 * double(fVslider1);
	double fSlow4 = double(fVslider2);
	double fSlow5 = fConst19 * std::pow(1e+01, 0.9 * fSlow4);
	double fSlow6 = std::pow(1e+01, 2.0 * fSlow4);
	double fSlow7 = fConst19 * fSlow6;
	double fSlow8 = std::pow(1e+01, 0.8 * fSlow4);
	double fSlow9 = std::pow(1e+01, 1.2 * fSlow4);
	double fSlow10 = 2.0 * (fSlow4 + -0.5);
	double fSlow11 = 1.0 - std::max<double>(0.0, -1.0 * fSlow10);
	double fSlow12 = 0.024937655860349125 * (1.0 - std::max<double>(0.0, fSlow10));
	double fSlow13 = 1.25 * fSlow4;
	double fSlow14 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider3));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec9[0] = 0.9302847925323914 * (fRec5[1] + fRec5[2]) - 0.8605695850647829 * fRec9[1];
		fRec8[0] = fRec9[0] - (1.8405051250752198 * fRec8[1] + 0.8612942439318627 * fRec8[2]);
		double fTemp0 = 1.8508996845035413 * fRec8[1];
		double fTemp1 = 0.9254498422517706 * (fRec8[0] + fRec8[2]);
		double fTemp2 = (fTemp0 + fTemp1) / (Ranode(TUBE_TABLE_12AT7_250k, fRec7[1]) + 1e+05);
		fVec0[0] = fTemp2;
		fRec10[0] = fConst7 * (8.2e+02 * (fTemp2 + fVec0[1]) - fConst6 * fRec10[1]);
		fRec7[0] = Ftube(TUBE_TABLE_12AT7_250k, fTemp1 + fRec10[0] + fTemp0 + -1.256962) + -96.7119512195122;
		fRec6[0] = 0.025 * (fConst8 * fRec7[0] + fConst9 * fRec7[1]) - fConst4 * fRec6[1];
		fRec11[0] = fConst12 * (fConst11 * fRec11[1] + 0.025 * (fRec7[0] - fRec7[1]));
		fRec17[0] = fSlow2 + 0.999 * fRec17[1];
		double fTemp3 = double(input0[i0]);
		double fTemp4 = std::fabs(fTemp3);
		fRec34[0] = 0.9999 * fRec34[1] + 9.999999999998899e-05 * fTemp4;
		double fTemp5 = std::max<double>(fRec34[0], fTemp4);
		fVec1[IOTA0 & 32767] = fTemp5;
		fRec33[0] = fTemp5 + fRec33[1] - fVec1[(IOTA0 - iConst39) & 32767];
		fRec32[0] = 0.999 * fRec32[1] + fConst40 * fRec33[0];
		double fTemp6 = std::max<double>(-1.0, std::min<double>(-0.01, fTemp5 + (-1.0 - 1.02 * fRec32[0])));
		double fTemp7 = 0.0 - 40.1 * fTemp6;
		double fTemp8 = std::max<double>(-6e+02, fTemp7);
		double fTemp9 = fTemp3 - fTemp6;
		double fTemp10 = 40.1 * fTemp9;
		double fTemp11 = std::max<double>(-6e+02, fTemp10);
		double fTemp12 = ((std::fabs(fTemp10) > 0.0001) ? ((fTemp11 < -5e+01) ? 0.0 - fTemp11 * std::exp(fTemp11) : fTemp11 / (1.0 - std::exp(-1.0 * fTemp11))) : fTemp9 * (134.00083333333336 * fTemp9 + 20.05) + 1.0) - ((std::fabs(fTemp7) > 0.0001) ? ((fTemp8 < -5e+01) ? 0.0 - fTemp8 * std::exp(fTemp8) : fTemp8 / (1.0 - std::exp(-1.0 * fTemp8))) : fTemp7 * (0.08333333333333333 * fTemp7 + 0.5) + 1.0);
		fRec35[0] = fSlow3 + 0.999 * fRec35[1];
		double fTemp13 = 0.024937655860349125 * fRec35[0] * fTemp12;
		fRec31[0] = fTemp13 - fConst38 * (fConst37 * fRec31[2] + fConst35 * fRec31[1]);
		double fTemp14 = fRec31[2] + fRec31[0] + 2.0 * fRec31[1];
		fVec2[0] = fTemp14;
		fRec30[0] = fConst38 * (fConst8 * fTemp14 + fConst9 * fVec2[1]) - fConst4 * fRec30[1];
		fRec29[0] = 0.0 - fConst43 * (fConst41 * fRec29[1] - (fRec30[0] + fRec30[1]));
		fRec28[0] = fRec29[0] - fConst33 * (fConst32 * fRec28[2] + fConst30 * fRec28[1]);
		double fTemp15 = fRec28[2] + fRec28[0] + 2.0 * fRec28[1];
		fVec3[0] = fTemp15;
		fRec27[0] = 0.0 - fConst46 * (fConst44 * fRec27[1] - fConst33 * (fTemp15 + fVec3[1]));
		fRec26[0] = fRec27[0] - fConst26 * (fConst25 * fRec26[2] + fConst23 * fRec26[1]);
		double fTemp16 = fRec26[2] + fRec26[0] + 2.0 * fRec26[1];
		fVec4[0] = fTemp16;
		fRec25[0] = 0.0 - fConst49 * (fConst47 * fRec25[1] - fConst26 * (fTemp16 + fVec4[1]));
		fRec24[0] = fRec25[0] - fConst19 * (fConst18 * fRec24[2] + fConst16 * fRec24[1]);
		double fTemp17 = std::max<double>(-1.0, std::min<double>(1.0, fSlow5 * (fRec24[2] + fRec24[0] + 2.0 * fRec24[1])));
		fRec37[0] = fConst26 * (fConst51 * fTemp16 + fConst52 * fVec4[1]) - fConst50 * fRec37[1];
		fRec36[0] = fRec37[0] - fConst19 * (fConst18 * fRec36[2] + fConst16 * fRec36[1]);
		double fTemp18 = std::max<double>(-1.0, std::min<double>(1.0, fSlow7 * (fConst15 * fRec36[0] + fConst53 * fRec36[1] + fConst15 * fRec36[2])));
		double fTemp19 = fConst16 * fRec38[1];
		double fTemp20 = fConst23 * fRec39[1];
		fRec41[0] = fConst58 * fRec30[1] - fConst43 * (fConst41 * fRec41[1] - fConst31 * fRec30[0]);
		fRec40[0] = fRec41[0] - fConst33 * (fConst32 * fRec40[2] + fConst30 * fRec40[1]);
		fRec39[0] = fConst33 * (fConst29 * fRec40[0] + fConst59 * fRec40[1] + fConst29 * fRec40[2]) - fConst57 * (fConst56 * fRec39[2] + fTemp20);
		fRec38[0] = fRec39[2] + fConst57 * (fTemp20 + fConst56 * fRec39[0]) - fConst55 * (fConst54 * fRec38[2] + fTemp19);
		double fTemp21 = std::max<double>(-1.0, std::min<double>(1.0, fSlow8 * (fRec38[2] + fConst55 * (fTemp19 + fConst54 * fRec38[0]))));
		double fTemp22 = fConst16 * fRec42[1];
		fRec44[0] = fConst33 * (fConst61 * fTemp15 + fConst62 * fVec3[1]) - fConst60 * fRec44[1];
		fRec43[0] = fRec44[0] - fConst26 * (fConst25 * fRec43[2] + fConst23 * fRec43[1]);
		fRec42[0] = fConst26 * (fConst22 * fRec43[0] + fConst63 * fRec43[1] + fConst22 * fRec43[2]) - fConst55 * (fConst54 * fRec42[2] + fTemp22);
		double fTemp23 = std::max<double>(-1.0, std::min<double>(1.0, fSlow9 * (fRec42[2] + fConst55 * (fTemp22 + fConst54 * fRec42[0]))));
		double fTemp24 = 1.333521432 * fTemp23 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp23)) + 1.584893192 * (fTemp21 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp21)) + fTemp18 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp18))) + 1.2589412 * fTemp17 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp17));
		fVec5[0] = fTemp24;
		fRec23[0] = 0.0 - fConst66 * (fConst65 * fRec23[1] - (fTemp24 + fVec5[1]));
		double fTemp25 = std::max<double>(-1.0, std::min<double>(1.0, fSlow6 * std::max<double>(-0.7, std::min<double>(0.7, fTemp13))));
		double fTemp26 = fSlow12 * fRec35[0];
		double fTemp27 = 1.0 - fRec35[0];
		double fTemp28 = fTemp12 * (fTemp27 * (fSlow13 * (0.0997506234413965 * (1.0 - std::fabs(0.024937655860349125 * fTemp27 * fTemp12)) + -0.024937655860349125) + 0.024937655860349125) + fTemp26) + 0.5 * fTemp25 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp25)) + fSlow11 * fRec23[0];
		fVec6[0] = fTemp28;
		fRec22[0] = 0.9302847925323914 * (fTemp28 + fVec6[1]) - 0.8605695850647829 * fRec22[1];
		fRec21[0] = fRec22[0] - (1.8405051250752198 * fRec21[1] + 0.8612942439318627 * fRec21[2]);
		double fTemp29 = 1.8508996845035413 * fRec21[1];
		double fTemp30 = 0.9254498422517706 * (fRec21[0] + fRec21[2]);
		double fTemp31 = (fTemp29 + fTemp30) / (Ranode(TUBE_TABLE_12AT7_68k, fRec20[1]) + 1e+05);
		fVec7[0] = fTemp31;
		fRec45[0] = fConst69 * (2.7e+03 * (fTemp31 + fVec7[1]) - fConst68 * fRec45[1]);
		fRec20[0] = Ftube(TUBE_TABLE_12AT7_68k, fTemp30 + fRec45[0] + fTemp29 + -2.617753) + -153.04618518518518;
		fRec19[0] = 0.025 * (fConst8 * fRec20[0] + fConst9 * fRec20[1]) - fConst4 * fRec19[1];
		fRec46[0] = fConst12 * (fConst11 * fRec46[1] + 0.025 * (fRec20[0] - fRec20[1]));
		fRec50[0] = 0.9302847925323914 * (fRec18[1] + fRec18[2]) - 0.8605695850647829 * fRec50[1];
		fRec49[0] = fRec50[0] - (1.8405051250752198 * fRec49[1] + 0.8612942439318627 * fRec49[2]);
		double fTemp32 = 1.8508996845035413 * fRec49[1];
		double fTemp33 = 0.9254498422517706 * (fRec49[0] + fRec49[2]);
		double fTemp34 = (fTemp32 + fTemp33) / (Ranode(TUBE_TABLE_12AT7_250k, fRec48[1]) + 1e+05);
		fVec8[0] = fTemp34;
		fRec51[0] = fConst72 * (1.5e+03 * (fTemp34 + fVec8[1]) - fConst71 * fRec51[1]);
		fRec48[0] = Ftube(TUBE_TABLE_12AT7_250k, fTemp33 + fRec51[0] + fTemp32 + -1.887332) + -124.17786666666666;
		fRec47[0] = 0.025 * (fConst8 * fRec48[0] + fConst9 * fRec48[1]) - fConst4 * fRec47[1];
		fRec52[0] = fConst12 * (fConst11 * fRec52[1] + 0.025 * (fRec48[0] - fRec48[1]));
		fRec18[0] = 0.6 * ((iSlow1) ? fRec52[0] : fRec47[0]) - ((iSlow1) ? fRec46[0] : fRec19[0]);
		double fTemp35 = fRec18[0] * fRec17[0];
		fVec9[0] = fTemp35;
		fRec16[0] = 0.0 - fConst66 * (fConst65 * fRec16[1] - (fTemp35 + fVec9[1]));
		fRec15[0] = 0.9302847925323914 * (fRec16[0] + fRec16[1]) - 0.8605695850647829 * fRec15[1];
		fRec14[0] = fRec15[0] - (1.8405051250752198 * fRec14[1] + 0.8612942439318627 * fRec14[2]);
		double fTemp36 = 1.8508996845035413 * fRec14[1];
		double fTemp37 = 0.9254498422517706 * (fRec14[0] + fRec14[2]);
		double fTemp38 = (fTemp36 + fTemp37) / (Ranode(TUBE_TABLE_12AT7_250k, fRec13[1]) + 1e+05);
		fVec10[0] = fTemp38;
		fRec53[0] = fConst72 * (1.5e+03 * (fTemp38 + fVec10[1]) - fConst71 * fRec53[1]);
		fRec13[0] = Ftube(TUBE_TABLE_12AT7_250k, fTemp37 + fRec53[0] + fTemp36 + -1.887332) + -124.17786666666666;
		fRec12[0] = 0.025 * (fConst8 * fRec13[0] + fConst9 * fRec13[1]) - fConst4 * fRec12[1];
		fRec54[0] = fConst12 * (fConst11 * fRec54[1] + 0.025 * (fRec13[0] - fRec13[1]));
		fRec5[0] = ((iSlow1) ? fRec54[0] : fRec12[0]) + 0.6 * ((iSlow1) ? fRec11[0] : fRec6[0]);
		fRec4[0] = 0.0 - fConst66 * (fConst65 * fRec4[1] - (fRec5[0] + fRec5[1]));
		fRec3[0] = 0.9302847925323914 * (fRec4[0] + fRec4[1]) - 0.8605695850647829 * fRec3[1];
		fRec2[0] = fRec3[0] - (1.8405051250752198 * fRec2[1] + 0.8612942439318627 * fRec2[2]);
		double fTemp39 = 1.8508996845035413 * fRec2[1];
		double fTemp40 = 0.9254498422517706 * (fRec2[0] + fRec2[2]);
		double fTemp41 = (fTemp39 + fTemp40) / (Ranode(TUBE_TABLE_12AT7_250k, fRec1[1]) + 1e+05);
		fVec11[0] = fTemp41;
		fRec55[0] = fConst7 * (8.2e+02 * (fTemp41 + fVec11[1]) - fConst6 * fRec55[1]);
		fRec1[0] = Ftube(TUBE_TABLE_12AT7_250k, fTemp40 + fRec55[0] + fTemp39 + -1.256962) + -96.7119512195122;
		fRec0[0] = 0.025 * (fConst8 * fRec1[0] + fConst9 * fRec1[1]) - fConst4 * fRec0[1];
		fRec56[0] = fConst12 * (fConst11 * fRec56[1] + 0.025 * (fRec1[0] - fRec1[1]));
		fRec57[0] = fSlow14 + 0.999 * fRec57[1];
		output0[i0] = FAUSTFLOAT(fRec57[0] * ((iSlow0) ? fRec56[0] : fRec0[0]));
		fRec67[0] = 0.9302847925323914 * (fRec63[1] + fRec63[2]) - 0.8605695850647829 * fRec67[1];
		fRec66[0] = fRec67[0] - (1.8405051250752198 * fRec66[1] + 0.8612942439318627 * fRec66[2]);
		double fTemp42 = 1.8508996845035413 * fRec66[1];
		double fTemp43 = 0.9254498422517706 * (fRec66[0] + fRec66[2]);
		double fTemp44 = (fTemp42 + fTemp43) / (Ranode(TUBE_TABLE_12AT7_250k, fRec65[1]) + 1e+05);
		fVec12[0] = fTemp44;
		fRec68[0] = fConst7 * (8.2e+02 * (fTemp44 + fVec12[1]) - fConst6 * fRec68[1]);
		fRec65[0] = Ftube(TUBE_TABLE_12AT7_250k, fTemp43 + fRec68[0] + fTemp42 + -1.256962) + -96.7119512195122;
		fRec64[0] = 0.025 * (fConst8 * fRec65[0] + fConst9 * fRec65[1]) - fConst4 * fRec64[1];
		fRec69[0] = fConst12 * (fConst11 * fRec69[1] + 0.025 * (fRec65[0] - fRec65[1]));
		double fTemp45 = double(input1[i0]);
		double fTemp46 = std::fabs(fTemp45);
		fRec91[0] = 0.9999 * fRec91[1] + 9.999999999998899e-05 * fTemp46;
		double fTemp47 = std::max<double>(fRec91[0], fTemp46);
		fVec13[IOTA0 & 32767] = fTemp47;
		fRec90[0] = fTemp47 + fRec90[1] - fVec13[(IOTA0 - iConst39) & 32767];
		fRec89[0] = 0.999 * fRec89[1] + fConst40 * fRec90[0];
		double fTemp48 = std::max<double>(-1.0, std::min<double>(-0.01, fTemp47 + (-1.0 - 1.02 * fRec89[0])));
		double fTemp49 = 0.0 - 40.1 * fTemp48;
		double fTemp50 = std::max<double>(-6e+02, fTemp49);
		double fTemp51 = fTemp45 - fTemp48;
		double fTemp52 = 40.1 * fTemp51;
		double fTemp53 = std::max<double>(-6e+02, fTemp52);
		double fTemp54 = ((std::fabs(fTemp52) > 0.0001) ? ((fTemp53 < -5e+01) ? 0.0 - fTemp53 * std::exp(fTemp53) : fTemp53 / (1.0 - std::exp(-1.0 * fTemp53))) : fTemp51 * (134.00083333333336 * fTemp51 + 20.05) + 1.0) - ((std::fabs(fTemp49) > 0.0001) ? ((fTemp50 < -5e+01) ? 0.0 - fTemp50 * std::exp(fTemp50) : fTemp50 / (1.0 - std::exp(-1.0 * fTemp50))) : fTemp49 * (0.08333333333333333 * fTemp49 + 0.5) + 1.0);
		double fTemp55 = 0.024937655860349125 * fRec35[0] * fTemp54;
		fRec88[0] = fTemp55 - fConst38 * (fConst37 * fRec88[2] + fConst35 * fRec88[1]);
		double fTemp56 = fRec88[2] + fRec88[0] + 2.0 * fRec88[1];
		fVec14[0] = fTemp56;
		fRec87[0] = fConst38 * (fConst8 * fTemp56 + fConst9 * fVec14[1]) - fConst4 * fRec87[1];
		fRec86[0] = 0.0 - fConst43 * (fConst41 * fRec86[1] - (fRec87[0] + fRec87[1]));
		fRec85[0] = fRec86[0] - fConst33 * (fConst32 * fRec85[2] + fConst30 * fRec85[1]);
		double fTemp57 = fRec85[2] + fRec85[0] + 2.0 * fRec85[1];
		fVec15[0] = fTemp57;
		fRec84[0] = 0.0 - fConst46 * (fConst44 * fRec84[1] - fConst33 * (fTemp57 + fVec15[1]));
		fRec83[0] = fRec84[0] - fConst26 * (fConst25 * fRec83[2] + fConst23 * fRec83[1]);
		double fTemp58 = fRec83[2] + fRec83[0] + 2.0 * fRec83[1];
		fVec16[0] = fTemp58;
		fRec82[0] = 0.0 - fConst49 * (fConst47 * fRec82[1] - fConst26 * (fTemp58 + fVec16[1]));
		fRec81[0] = fRec82[0] - fConst19 * (fConst18 * fRec81[2] + fConst16 * fRec81[1]);
		double fTemp59 = std::max<double>(-1.0, std::min<double>(1.0, fSlow5 * (fRec81[2] + fRec81[0] + 2.0 * fRec81[1])));
		fRec93[0] = fConst26 * (fConst51 * fTemp58 + fConst52 * fVec16[1]) - fConst50 * fRec93[1];
		fRec92[0] = fRec93[0] - fConst19 * (fConst18 * fRec92[2] + fConst16 * fRec92[1]);
		double fTemp60 = std::max<double>(-1.0, std::min<double>(1.0, fSlow7 * (fConst15 * fRec92[0] + fConst53 * fRec92[1] + fConst15 * fRec92[2])));
		double fTemp61 = fConst16 * fRec94[1];
		double fTemp62 = fConst23 * fRec95[1];
		fRec97[0] = fConst58 * fRec87[1] - fConst43 * (fConst41 * fRec97[1] - fConst31 * fRec87[0]);
		fRec96[0] = fRec97[0] - fConst33 * (fConst32 * fRec96[2] + fConst30 * fRec96[1]);
		fRec95[0] = fConst33 * (fConst29 * fRec96[0] + fConst59 * fRec96[1] + fConst29 * fRec96[2]) - fConst57 * (fConst56 * fRec95[2] + fTemp62);
		fRec94[0] = fRec95[2] + fConst57 * (fTemp62 + fConst56 * fRec95[0]) - fConst55 * (fConst54 * fRec94[2] + fTemp61);
		double fTemp63 = std::max<double>(-1.0, std::min<double>(1.0, fSlow8 * (fRec94[2] + fConst55 * (fTemp61 + fConst54 * fRec94[0]))));
		double fTemp64 = fConst16 * fRec98[1];
		fRec100[0] = fConst33 * (fConst61 * fTemp57 + fConst62 * fVec15[1]) - fConst60 * fRec100[1];
		fRec99[0] = fRec100[0] - fConst26 * (fConst25 * fRec99[2] + fConst23 * fRec99[1]);
		fRec98[0] = fConst26 * (fConst22 * fRec99[0] + fConst63 * fRec99[1] + fConst22 * fRec99[2]) - fConst55 * (fConst54 * fRec98[2] + fTemp64);
		double fTemp65 = std::max<double>(-1.0, std::min<double>(1.0, fSlow9 * (fRec98[2] + fConst55 * (fTemp64 + fConst54 * fRec98[0]))));
		double fTemp66 = 1.333521432 * fTemp65 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp65)) + 1.584893192 * (fTemp63 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp63)) + fTemp60 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp60))) + 1.2589412 * fTemp59 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp59));
		fVec17[0] = fTemp66;
		fRec80[0] = 0.0 - fConst66 * (fConst65 * fRec80[1] - (fTemp66 + fVec17[1]));
		double fTemp67 = std::max<double>(-1.0, std::min<double>(1.0, fSlow6 * std::max<double>(-0.7, std::min<double>(0.7, fTemp55))));
		double fTemp68 = fTemp54 * (fTemp26 + fTemp27 * (fSlow13 * (0.0997506234413965 * (1.0 - std::fabs(0.024937655860349125 * fTemp27 * fTemp54)) + -0.024937655860349125) + 0.024937655860349125)) + 0.5 * fTemp67 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp67)) + fSlow11 * fRec80[0];
		fVec18[0] = fTemp68;
		fRec79[0] = 0.9302847925323914 * (fTemp68 + fVec18[1]) - 0.8605695850647829 * fRec79[1];
		fRec78[0] = fRec79[0] - (1.8405051250752198 * fRec78[1] + 0.8612942439318627 * fRec78[2]);
		double fTemp69 = 1.8508996845035413 * fRec78[1];
		double fTemp70 = 0.9254498422517706 * (fRec78[0] + fRec78[2]);
		double fTemp71 = (fTemp69 + fTemp70) / (Ranode(TUBE_TABLE_12AT7_68k, fRec77[1]) + 1e+05);
		fVec19[0] = fTemp71;
		fRec101[0] = fConst69 * (2.7e+03 * (fTemp71 + fVec19[1]) - fConst68 * fRec101[1]);
		fRec77[0] = Ftube(TUBE_TABLE_12AT7_68k, fTemp70 + fRec101[0] + fTemp69 + -2.617753) + -153.04618518518518;
		fRec76[0] = 0.025 * (fConst8 * fRec77[0] + fConst9 * fRec77[1]) - fConst4 * fRec76[1];
		fRec102[0] = fConst12 * (fConst11 * fRec102[1] + 0.025 * (fRec77[0] - fRec77[1]));
		fRec106[0] = 0.9302847925323914 * (fRec75[1] + fRec75[2]) - 0.8605695850647829 * fRec106[1];
		fRec105[0] = fRec106[0] - (1.8405051250752198 * fRec105[1] + 0.8612942439318627 * fRec105[2]);
		double fTemp72 = 1.8508996845035413 * fRec105[1];
		double fTemp73 = 0.9254498422517706 * (fRec105[0] + fRec105[2]);
		double fTemp74 = (fTemp72 + fTemp73) / (Ranode(TUBE_TABLE_12AT7_250k, fRec104[1]) + 1e+05);
		fVec20[0] = fTemp74;
		fRec107[0] = fConst72 * (1.5e+03 * (fTemp74 + fVec20[1]) - fConst71 * fRec107[1]);
		fRec104[0] = Ftube(TUBE_TABLE_12AT7_250k, fTemp73 + fRec107[0] + fTemp72 + -1.887332) + -124.17786666666666;
		fRec103[0] = 0.025 * (fConst8 * fRec104[0] + fConst9 * fRec104[1]) - fConst4 * fRec103[1];
		fRec108[0] = fConst12 * (fConst11 * fRec108[1] + 0.025 * (fRec104[0] - fRec104[1]));
		fRec75[0] = 0.6 * ((iSlow1) ? fRec108[0] : fRec103[0]) - ((iSlow1) ? fRec102[0] : fRec76[0]);
		double fTemp75 = fRec17[0] * fRec75[0];
		fVec21[0] = fTemp75;
		fRec74[0] = 0.0 - fConst66 * (fConst65 * fRec74[1] - (fTemp75 + fVec21[1]));
		fRec73[0] = 0.9302847925323914 * (fRec74[0] + fRec74[1]) - 0.8605695850647829 * fRec73[1];
		fRec72[0] = fRec73[0] - (1.8405051250752198 * fRec72[1] + 0.8612942439318627 * fRec72[2]);
		double fTemp76 = 1.8508996845035413 * fRec72[1];
		double fTemp77 = 0.9254498422517706 * (fRec72[0] + fRec72[2]);
		double fTemp78 = (fTemp76 + fTemp77) / (Ranode(TUBE_TABLE_12AT7_250k, fRec71[1]) + 1e+05);
		fVec22[0] = fTemp78;
		fRec109[0] = fConst72 * (1.5e+03 * (fTemp78 + fVec22[1]) - fConst71 * fRec109[1]);
		fRec71[0] = Ftube(TUBE_TABLE_12AT7_250k, fTemp77 + fRec109[0] + fTemp76 + -1.887332) + -124.17786666666666;
		fRec70[0] = 0.025 * (fConst8 * fRec71[0] + fConst9 * fRec71[1]) - fConst4 * fRec70[1];
		fRec110[0] = fConst12 * (fConst11 * fRec110[1] + 0.025 * (fRec71[0] - fRec71[1]));
		fRec63[0] = ((iSlow1) ? fRec110[0] : fRec70[0]) + 0.6 * ((iSlow1) ? fRec69[0] : fRec64[0]);
		fRec62[0] = 0.0 - fConst66 * (fConst65 * fRec62[1] - (fRec63[0] + fRec63[1]));
		fRec61[0] = 0.9302847925323914 * (fRec62[0] + fRec62[1]) - 0.8605695850647829 * fRec61[1];
		fRec60[0] = fRec61[0] - (1.8405051250752198 * fRec60[1] + 0.8612942439318627 * fRec60[2]);
		double fTemp79 = 1.8508996845035413 * fRec60[1];
		double fTemp80 = 0.9254498422517706 * (fRec60[0] + fRec60[2]);
		double fTemp81 = (fTemp79 + fTemp80) / (Ranode(TUBE_TABLE_12AT7_250k, fRec59[1]) + 1e+05);
		fVec23[0] = fTemp81;
		fRec111[0] = fConst7 * (8.2e+02 * (fTemp81 + fVec23[1]) - fConst6 * fRec111[1]);
		fRec59[0] = Ftube(TUBE_TABLE_12AT7_250k, fTemp80 + fRec111[0] + fTemp79 + -1.256962) + -96.7119512195122;
		fRec58[0] = 0.025 * (fConst8 * fRec59[0] + fConst9 * fRec59[1]) - fConst4 * fRec58[1];
		fRec112[0] = fConst12 * (fConst11 * fRec112[1] + 0.025 * (fRec59[0] - fRec59[1]));
		output1[i0] = FAUSTFLOAT(fRec57[0] * ((iSlow0) ? fRec112[0] : fRec58[0]));
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fVec0[1] = fVec0[0];
		fRec10[1] = fRec10[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec11[1] = fRec11[0];
		fRec17[1] = fRec17[0];
		fRec34[1] = fRec34[0];
		IOTA0 = IOTA0 + 1;
		fRec33[1] = fRec33[0];
		fRec32[1] = fRec32[0];
		fRec35[1] = fRec35[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fVec2[1] = fVec2[0];
		fRec30[1] = fRec30[0];
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fVec3[1] = fVec3[0];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fVec4[1] = fVec4[0];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fRec37[1] = fRec37[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		fRec41[1] = fRec41[0];
		fRec40[2] = fRec40[1];
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		fRec44[1] = fRec44[0];
		fRec43[2] = fRec43[1];
		fRec43[1] = fRec43[0];
		fRec42[2] = fRec42[1];
		fRec42[1] = fRec42[0];
		fVec5[1] = fVec5[0];
		fRec23[1] = fRec23[0];
		fVec6[1] = fVec6[0];
		fRec22[1] = fRec22[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		fVec7[1] = fVec7[0];
		fRec45[1] = fRec45[0];
		fRec20[1] = fRec20[0];
		fRec19[1] = fRec19[0];
		fRec46[1] = fRec46[0];
		fRec50[1] = fRec50[0];
		fRec49[2] = fRec49[1];
		fRec49[1] = fRec49[0];
		fVec8[1] = fVec8[0];
		fRec51[1] = fRec51[0];
		fRec48[1] = fRec48[0];
		fRec47[1] = fRec47[0];
		fRec52[1] = fRec52[0];
		fRec18[2] = fRec18[1];
		fRec18[1] = fRec18[0];
		fVec9[1] = fVec9[0];
		fRec16[1] = fRec16[0];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fVec10[1] = fVec10[0];
		fRec53[1] = fRec53[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec54[1] = fRec54[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fVec11[1] = fVec11[0];
		fRec55[1] = fRec55[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec56[1] = fRec56[0];
		fRec57[1] = fRec57[0];
		fRec67[1] = fRec67[0];
		fRec66[2] = fRec66[1];
		fRec66[1] = fRec66[0];
		fVec12[1] = fVec12[0];
		fRec68[1] = fRec68[0];
		fRec65[1] = fRec65[0];
		fRec64[1] = fRec64[0];
		fRec69[1] = fRec69[0];
		fRec91[1] = fRec91[0];
		fRec90[1] = fRec90[0];
		fRec89[1] = fRec89[0];
		fRec88[2] = fRec88[1];
		fRec88[1] = fRec88[0];
		fVec14[1] = fVec14[0];
		fRec87[1] = fRec87[0];
		fRec86[1] = fRec86[0];
		fRec85[2] = fRec85[1];
		fRec85[1] = fRec85[0];
		fVec15[1] = fVec15[0];
		fRec84[1] = fRec84[0];
		fRec83[2] = fRec83[1];
		fRec83[1] = fRec83[0];
		fVec16[1] = fVec16[0];
		fRec82[1] = fRec82[0];
		fRec81[2] = fRec81[1];
		fRec81[1] = fRec81[0];
		fRec93[1] = fRec93[0];
		fRec92[2] = fRec92[1];
		fRec92[1] = fRec92[0];
		fRec97[1] = fRec97[0];
		fRec96[2] = fRec96[1];
		fRec96[1] = fRec96[0];
		fRec95[2] = fRec95[1];
		fRec95[1] = fRec95[0];
		fRec94[2] = fRec94[1];
		fRec94[1] = fRec94[0];
		fRec100[1] = fRec100[0];
		fRec99[2] = fRec99[1];
		fRec99[1] = fRec99[0];
		fRec98[2] = fRec98[1];
		fRec98[1] = fRec98[0];
		fVec17[1] = fVec17[0];
		fRec80[1] = fRec80[0];
		fVec18[1] = fVec18[0];
		fRec79[1] = fRec79[0];
		fRec78[2] = fRec78[1];
		fRec78[1] = fRec78[0];
		fVec19[1] = fVec19[0];
		fRec101[1] = fRec101[0];
		fRec77[1] = fRec77[0];
		fRec76[1] = fRec76[0];
		fRec102[1] = fRec102[0];
		fRec106[1] = fRec106[0];
		fRec105[2] = fRec105[1];
		fRec105[1] = fRec105[0];
		fVec20[1] = fVec20[0];
		fRec107[1] = fRec107[0];
		fRec104[1] = fRec104[0];
		fRec103[1] = fRec103[0];
		fRec108[1] = fRec108[0];
		fRec75[2] = fRec75[1];
		fRec75[1] = fRec75[0];
		fVec21[1] = fVec21[0];
		fRec74[1] = fRec74[0];
		fRec73[1] = fRec73[0];
		fRec72[2] = fRec72[1];
		fRec72[1] = fRec72[0];
		fVec22[1] = fVec22[0];
		fRec109[1] = fRec109[0];
		fRec71[1] = fRec71[0];
		fRec70[1] = fRec70[0];
		fRec110[1] = fRec110[0];
		fRec63[2] = fRec63[1];
		fRec63[1] = fRec63[0];
		fRec62[1] = fRec62[0];
		fRec61[1] = fRec61[0];
		fRec60[2] = fRec60[1];
		fRec60[1] = fRec60[0];
		fVec23[1] = fVec23[0];
		fRec111[1] = fRec111[0];
		fRec59[1] = fRec59[0];
		fRec58[1] = fRec58[0];
		fRec112[1] = fRec112[0];
	}
#undef fCheckbox0
#undef fCheckbox1
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
	case HIGHGAIN: 
		fCheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case DRIVE: 
		fVslider2_ = (float*)data; // , 0.35, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fVslider1_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
		break;
	case PREGAIN: 
		fVslider0_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
		break;
	case GAIN1: 
		fVslider3_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
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
   HIGHGAIN, 
   PREGAIN, 
   GAIN1, 
} PortIndex;
*/

} // end namespace gxamp17_stereo
