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
	double fConst6;
	double fConst7;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	double fRec9[2];
	double fRec8[3];
	double fConst9;
	double fVec0[2];
	double fConst10;
	double fRec10[2];
	double fRec7[2];
	double fConst11;
	double fConst12;
	double fRec6[2];
	double fConst14;
	double fConst15;
	double fRec11[2];
	double fRec21[2];
	double fRec20[3];
	double fConst17;
	double fVec1[2];
	double fConst18;
	double fRec22[2];
	double fRec19[2];
	double fRec18[2];
	double fRec23[2];
	double fRec28[2];
	int IOTA;
	double fVec2[32768];
	double fConst19;
	int iConst20;
	double fRec30[2];
	double fRec29[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec31[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst23;
	double fConst25;
	double fConst27;
	double fConst28;
	double fConst30;
	double fConst32;
	double fConst33;
	double fConst36;
	double fConst37;
	double fConst38;
	double fRec39[3];
	double fVec3[2];
	double fRec38[2];
	double fRec37[2];
	double fConst39;
	double fConst41;
	double fConst42;
	double fRec36[3];
	double fVec4[2];
	double fConst43;
	double fConst44;
	double fConst45;
	double fRec35[2];
	double fConst46;
	double fConst47;
	double fRec34[3];
	double fConst48;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst56;
	double fConst57;
	double fRec33[3];
	double fConst58;
	double fRec43[2];
	double fRec42[3];
	double fConst59;
	double fConst60;
	double fConst61;
	double fRec41[3];
	double fRec40[3];
	double fConst62;
	double fConst63;
	double fConst64;
	double fRec47[2];
	double fRec46[3];
	double fVec5[2];
	double fConst65;
	double fConst66;
	double fRec45[2];
	double fConst67;
	double fRec44[3];
	double fConst68;
	double fConst69;
	double fRec49[2];
	double fRec48[3];
	double fVec6[2];
	double fRec32[2];
	double fVec7[2];
	double fRec27[2];
	double fRec26[3];
	double fConst71;
	double fVec8[2];
	double fConst72;
	double fRec50[2];
	double fRec25[2];
	double fRec24[2];
	double fRec51[2];
	double fRec17[3];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec52[2];
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
	double fRec79[2];
	double fRec78[3];
	double fVec13[2];
	double fRec80[2];
	double fRec77[2];
	double fRec76[2];
	double fRec81[2];
	double fRec86[2];
	double fVec14[32768];
	double fRec88[2];
	double fRec87[2];
	double fRec96[3];
	double fVec15[2];
	double fRec95[2];
	double fRec94[2];
	double fRec93[3];
	double fVec16[2];
	double fRec92[2];
	double fRec91[3];
	double fRec90[3];
	double fRec100[2];
	double fRec99[3];
	double fRec98[3];
	double fRec97[3];
	double fRec104[2];
	double fRec103[3];
	double fVec17[2];
	double fRec102[2];
	double fRec101[3];
	double fRec106[2];
	double fRec105[3];
	double fVec18[2];
	double fRec89[2];
	double fVec19[2];
	double fRec85[2];
	double fRec84[3];
	double fVec20[2];
	double fRec107[2];
	double fRec83[2];
	double fRec82[2];
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec9[l0] = 0.0;
	for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) fRec8[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fVec0[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec10[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec7[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec6[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec11[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec21[l7] = 0.0;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec20[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fVec1[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec22[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec19[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec18[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec23[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec28[l14] = 0.0;
	for (int l15 = 0; (l15 < 32768); l15 = (l15 + 1)) fVec2[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec30[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec29[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec31[l18] = 0.0;
	for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) fRec39[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fVec3[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec38[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fRec37[l22] = 0.0;
	for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) fRec36[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fVec4[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fRec35[l25] = 0.0;
	for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) fRec34[l26] = 0.0;
	for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) fRec33[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec43[l28] = 0.0;
	for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) fRec42[l29] = 0.0;
	for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) fRec41[l30] = 0.0;
	for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) fRec40[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fRec47[l32] = 0.0;
	for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) fRec46[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fVec5[l34] = 0.0;
	for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) fRec45[l35] = 0.0;
	for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) fRec44[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fRec49[l37] = 0.0;
	for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) fRec48[l38] = 0.0;
	for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) fVec6[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fRec32[l40] = 0.0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) fVec7[l41] = 0.0;
	for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) fRec27[l42] = 0.0;
	for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) fRec26[l43] = 0.0;
	for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) fVec8[l44] = 0.0;
	for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) fRec50[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec25[l46] = 0.0;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) fRec24[l47] = 0.0;
	for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) fRec51[l48] = 0.0;
	for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) fRec17[l49] = 0.0;
	for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) fRec52[l50] = 0.0;
	for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) fVec9[l51] = 0.0;
	for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) fRec16[l52] = 0.0;
	for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) fRec15[l53] = 0.0;
	for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) fRec14[l54] = 0.0;
	for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) fVec10[l55] = 0.0;
	for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) fRec53[l56] = 0.0;
	for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) fRec13[l57] = 0.0;
	for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) fRec12[l58] = 0.0;
	for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) fRec54[l59] = 0.0;
	for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) fRec5[l60] = 0.0;
	for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) fRec4[l61] = 0.0;
	for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) fRec3[l62] = 0.0;
	for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) fRec2[l63] = 0.0;
	for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) fVec11[l64] = 0.0;
	for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) fRec55[l65] = 0.0;
	for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) fRec1[l66] = 0.0;
	for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) fRec0[l67] = 0.0;
	for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) fRec56[l68] = 0.0;
	for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) fRec57[l69] = 0.0;
	for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) fRec67[l70] = 0.0;
	for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) fRec66[l71] = 0.0;
	for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) fVec12[l72] = 0.0;
	for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) fRec68[l73] = 0.0;
	for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) fRec65[l74] = 0.0;
	for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) fRec64[l75] = 0.0;
	for (int l76 = 0; (l76 < 2); l76 = (l76 + 1)) fRec69[l76] = 0.0;
	for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) fRec79[l77] = 0.0;
	for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) fRec78[l78] = 0.0;
	for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) fVec13[l79] = 0.0;
	for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) fRec80[l80] = 0.0;
	for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) fRec77[l81] = 0.0;
	for (int l82 = 0; (l82 < 2); l82 = (l82 + 1)) fRec76[l82] = 0.0;
	for (int l83 = 0; (l83 < 2); l83 = (l83 + 1)) fRec81[l83] = 0.0;
	for (int l84 = 0; (l84 < 2); l84 = (l84 + 1)) fRec86[l84] = 0.0;
	for (int l85 = 0; (l85 < 32768); l85 = (l85 + 1)) fVec14[l85] = 0.0;
	for (int l86 = 0; (l86 < 2); l86 = (l86 + 1)) fRec88[l86] = 0.0;
	for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) fRec87[l87] = 0.0;
	for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) fRec96[l88] = 0.0;
	for (int l89 = 0; (l89 < 2); l89 = (l89 + 1)) fVec15[l89] = 0.0;
	for (int l90 = 0; (l90 < 2); l90 = (l90 + 1)) fRec95[l90] = 0.0;
	for (int l91 = 0; (l91 < 2); l91 = (l91 + 1)) fRec94[l91] = 0.0;
	for (int l92 = 0; (l92 < 3); l92 = (l92 + 1)) fRec93[l92] = 0.0;
	for (int l93 = 0; (l93 < 2); l93 = (l93 + 1)) fVec16[l93] = 0.0;
	for (int l94 = 0; (l94 < 2); l94 = (l94 + 1)) fRec92[l94] = 0.0;
	for (int l95 = 0; (l95 < 3); l95 = (l95 + 1)) fRec91[l95] = 0.0;
	for (int l96 = 0; (l96 < 3); l96 = (l96 + 1)) fRec90[l96] = 0.0;
	for (int l97 = 0; (l97 < 2); l97 = (l97 + 1)) fRec100[l97] = 0.0;
	for (int l98 = 0; (l98 < 3); l98 = (l98 + 1)) fRec99[l98] = 0.0;
	for (int l99 = 0; (l99 < 3); l99 = (l99 + 1)) fRec98[l99] = 0.0;
	for (int l100 = 0; (l100 < 3); l100 = (l100 + 1)) fRec97[l100] = 0.0;
	for (int l101 = 0; (l101 < 2); l101 = (l101 + 1)) fRec104[l101] = 0.0;
	for (int l102 = 0; (l102 < 3); l102 = (l102 + 1)) fRec103[l102] = 0.0;
	for (int l103 = 0; (l103 < 2); l103 = (l103 + 1)) fVec17[l103] = 0.0;
	for (int l104 = 0; (l104 < 2); l104 = (l104 + 1)) fRec102[l104] = 0.0;
	for (int l105 = 0; (l105 < 3); l105 = (l105 + 1)) fRec101[l105] = 0.0;
	for (int l106 = 0; (l106 < 2); l106 = (l106 + 1)) fRec106[l106] = 0.0;
	for (int l107 = 0; (l107 < 3); l107 = (l107 + 1)) fRec105[l107] = 0.0;
	for (int l108 = 0; (l108 < 2); l108 = (l108 + 1)) fVec18[l108] = 0.0;
	for (int l109 = 0; (l109 < 2); l109 = (l109 + 1)) fRec89[l109] = 0.0;
	for (int l110 = 0; (l110 < 2); l110 = (l110 + 1)) fVec19[l110] = 0.0;
	for (int l111 = 0; (l111 < 2); l111 = (l111 + 1)) fRec85[l111] = 0.0;
	for (int l112 = 0; (l112 < 3); l112 = (l112 + 1)) fRec84[l112] = 0.0;
	for (int l113 = 0; (l113 < 2); l113 = (l113 + 1)) fVec20[l113] = 0.0;
	for (int l114 = 0; (l114 < 2); l114 = (l114 + 1)) fRec107[l114] = 0.0;
	for (int l115 = 0; (l115 < 2); l115 = (l115 + 1)) fRec83[l115] = 0.0;
	for (int l116 = 0; (l116 < 2); l116 = (l116 + 1)) fRec82[l116] = 0.0;
	for (int l117 = 0; (l117 < 2); l117 = (l117 + 1)) fRec108[l117] = 0.0;
	for (int l118 = 0; (l118 < 3); l118 = (l118 + 1)) fRec75[l118] = 0.0;
	for (int l119 = 0; (l119 < 2); l119 = (l119 + 1)) fVec21[l119] = 0.0;
	for (int l120 = 0; (l120 < 2); l120 = (l120 + 1)) fRec74[l120] = 0.0;
	for (int l121 = 0; (l121 < 2); l121 = (l121 + 1)) fRec73[l121] = 0.0;
	for (int l122 = 0; (l122 < 3); l122 = (l122 + 1)) fRec72[l122] = 0.0;
	for (int l123 = 0; (l123 < 2); l123 = (l123 + 1)) fVec22[l123] = 0.0;
	for (int l124 = 0; (l124 < 2); l124 = (l124 + 1)) fRec109[l124] = 0.0;
	for (int l125 = 0; (l125 < 2); l125 = (l125 + 1)) fRec71[l125] = 0.0;
	for (int l126 = 0; (l126 < 2); l126 = (l126 + 1)) fRec70[l126] = 0.0;
	for (int l127 = 0; (l127 < 2); l127 = (l127 + 1)) fRec110[l127] = 0.0;
	for (int l128 = 0; (l128 < 3); l128 = (l128 + 1)) fRec63[l128] = 0.0;
	for (int l129 = 0; (l129 < 2); l129 = (l129 + 1)) fRec62[l129] = 0.0;
	for (int l130 = 0; (l130 < 2); l130 = (l130 + 1)) fRec61[l130] = 0.0;
	for (int l131 = 0; (l131 < 3); l131 = (l131 + 1)) fRec60[l131] = 0.0;
	for (int l132 = 0; (l132 < 2); l132 = (l132 + 1)) fVec23[l132] = 0.0;
	for (int l133 = 0; (l133 < 2); l133 = (l133 + 1)) fRec111[l133] = 0.0;
	for (int l134 = 0; (l134 < 2); l134 = (l134 + 1)) fRec59[l134] = 0.0;
	for (int l135 = 0; (l135 < 2); l135 = (l135 + 1)) fRec58[l135] = 0.0;
	for (int l136 = 0; (l136 < 2); l136 = (l136 + 1)) fRec112[l136] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = std::tan((97.389372261283583 / fConst0));
	double fConst2 = (1.0 / fConst1);
	double fConst3 = (fConst2 + 1.0);
	fConst4 = (1.0 / (fConst1 * fConst3));
	double fConst5 = (1.0 / std::tan((20517.741620594938 / fConst0)));
	fConst6 = (1.0 / (fConst5 + 1.0));
	fConst7 = (1.0 - fConst5);
	double fConst8 = (1.0 / std::tan((609.46897479641984 / fConst0)));
	fConst9 = (1.0 / (fConst8 + 1.0));
	fConst10 = (1.0 - fConst8);
	fConst11 = (0.0 - fConst4);
	fConst12 = ((1.0 - fConst2) / fConst3);
	double fConst13 = (3.1415926535897931 / fConst0);
	fConst14 = (1.0 / (fConst13 + 1.0));
	fConst15 = (1.0 - fConst13);
	double fConst16 = (1.0 / std::tan((414.69023027385271 / fConst0)));
	fConst17 = (1.0 / (fConst16 + 1.0));
	fConst18 = (1.0 - fConst16);
	fConst19 = (0.009000000000000008 / fConst0);
	iConst20 = int(std::min<double>(65536.0, std::max<double>(0.0, (0.1111111111111111 * fConst0))));
	double fConst21 = std::tan((3769.9111843077517 / fConst0));
	double fConst22 = (1.0 / fConst21);
	fConst23 = (1.0 / (((fConst22 + 1.0000000000000004) / fConst21) + 1.0));
	double fConst24 = mydsp_faustpower2_f(fConst21);
	fConst25 = (1.0 / fConst24);
	double fConst26 = std::tan((10053.096491487338 / fConst0));
	fConst27 = (1.0 / fConst26);
	fConst28 = (1.0 / (((fConst27 + 1.0000000000000004) / fConst26) + 1.0));
	double fConst29 = (fConst22 + 1.0);
	fConst30 = (1.0 / (fConst21 * fConst29));
	double fConst31 = (fConst27 + 1.0);
	fConst32 = (1.0 / fConst31);
	fConst33 = (1.0 - fConst27);
	double fConst34 = std::tan((47123.889803846898 / fConst0));
	double fConst35 = (1.0 / fConst34);
	fConst36 = (1.0 / (((fConst35 + 1.4142135623730949) / fConst34) + 1.0));
	fConst37 = (((fConst35 + -1.4142135623730949) / fConst34) + 1.0);
	fConst38 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst34))));
	fConst39 = (((fConst27 + -1.0000000000000004) / fConst26) + 1.0);
	double fConst40 = mydsp_faustpower2_f(fConst26);
	fConst41 = (1.0 / fConst40);
	fConst42 = (2.0 * (1.0 - fConst41));
	fConst43 = (0.0 - fConst30);
	fConst44 = (1.0 - fConst22);
	fConst45 = (fConst44 / fConst29);
	fConst46 = (((fConst22 + -1.0000000000000004) / fConst21) + 1.0);
	fConst47 = (2.0 * (1.0 - fConst25));
	fConst48 = (0.0 - (2.0 / fConst24));
	double fConst49 = std::tan((942.47779607693792 / fConst0));
	double fConst50 = (1.0 / fConst49);
	double fConst51 = (fConst50 + 1.0);
	fConst52 = (1.0 / ((fConst51 / fConst49) + 1.0));
	fConst53 = (1.0 - fConst50);
	fConst54 = (1.0 - (fConst53 / fConst49));
	double fConst55 = mydsp_faustpower2_f(fConst49);
	fConst56 = (1.0 / fConst55);
	fConst57 = (2.0 * (1.0 - fConst56));
	fConst58 = (0.0 - (1.0 / (fConst26 * fConst31)));
	fConst59 = (0.0 - (2.0 / fConst40));
	fConst60 = (1.0 / ((fConst29 / fConst21) + 1.0));
	fConst61 = (1.0 - (fConst44 / fConst21));
	fConst62 = (1.0 / (((fConst50 + 1.0000000000000004) / fConst49) + 1.0));
	fConst63 = (1.0 / (fConst49 * fConst51));
	fConst64 = (1.0 / fConst29);
	fConst65 = (0.0 - fConst63);
	fConst66 = (fConst53 / fConst51);
	fConst67 = (((fConst50 + -1.0000000000000004) / fConst49) + 1.0);
	fConst68 = (0.0 - (2.0 / fConst55));
	fConst69 = (1.0 / fConst51);
	double fConst70 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst71 = (1.0 / (fConst70 + 1.0));
	fConst72 = (1.0 - fConst70);
	IOTA = 0;
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
	double fSlow2 = (1.0000000000000009e-05 * double(fVslider0));
	double fSlow3 = double(fVslider1);
	double fSlow4 = (1.25 * fSlow3);
	double fSlow5 = (2.0 * (fSlow3 + -0.5));
	double fSlow6 = (0.024937655860349125 * (1.0 - std::max<double>(0.0, fSlow5)));
	double fSlow7 = std::pow(10.0, (2.0 * fSlow3));
	double fSlow8 = (1.0 - std::max<double>(0.0, (-1.0 * fSlow5)));
	double fSlow9 = std::pow(10.0, (1.2 * fSlow3));
	double fSlow10 = std::pow(10.0, (0.80000000000000004 * fSlow3));
	double fSlow11 = (fConst62 * fSlow7);
	double fSlow12 = (fConst62 * std::pow(10.0, (0.90000000000000002 * fSlow3)));
	double fSlow13 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider2))));
	double fSlow14 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider3))));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		fRec9[0] = ((0.93028479253239138 * (fRec5[1] + fRec5[2])) - (0.86056958506478287 * fRec9[1]));
		fRec8[0] = (fRec9[0] - ((1.8405051250752198 * fRec8[1]) + (0.86129424393186271 * fRec8[2])));
		double fTemp0 = (0.92544984225177063 * (fRec8[0] + fRec8[2]));
		double fTemp1 = (1.8508996845035413 * fRec8[1]);
		double fTemp2 = ((fTemp1 + fTemp0) / (double(Ranode(int(TUBE_TABLE_12AT7_250k), double(fRec7[1]))) + 100000.0));
		fVec0[0] = fTemp2;
		fRec10[0] = (fConst9 * ((820.0 * (fTemp2 + fVec0[1])) - (fConst10 * fRec10[1])));
		fRec7[0] = (double(Ftube(int(TUBE_TABLE_12AT7_250k), double(((fTemp0 + (fRec10[0] + fTemp1)) + -1.2569619999999999)))) + -96.711951219512201);
		fRec6[0] = ((0.025000000000000001 * ((fConst4 * fRec7[0]) + (fConst11 * fRec7[1]))) - (fConst12 * fRec6[1]));
		fRec11[0] = (fConst14 * ((fConst15 * fRec11[1]) + (0.025000000000000001 * (fRec7[0] - fRec7[1]))));
		fRec21[0] = ((0.93028479253239138 * (fRec17[1] + fRec17[2])) - (0.86056958506478287 * fRec21[1]));
		fRec20[0] = (fRec21[0] - ((1.8405051250752198 * fRec20[1]) + (0.86129424393186271 * fRec20[2])));
		double fTemp3 = (0.92544984225177063 * (fRec20[0] + fRec20[2]));
		double fTemp4 = (1.8508996845035413 * fRec20[1]);
		double fTemp5 = ((fTemp4 + fTemp3) / (double(Ranode(int(TUBE_TABLE_12AT7_250k), double(fRec19[1]))) + 100000.0));
		fVec1[0] = fTemp5;
		fRec22[0] = (fConst17 * ((1500.0 * (fTemp5 + fVec1[1])) - (fConst18 * fRec22[1])));
		fRec19[0] = (double(Ftube(int(TUBE_TABLE_12AT7_250k), double(((fTemp3 + (fRec22[0] + fTemp4)) + -1.887332)))) + -124.17786666666666);
		fRec18[0] = ((0.025000000000000001 * ((fConst4 * fRec19[0]) + (fConst11 * fRec19[1]))) - (fConst12 * fRec18[1]));
		fRec23[0] = (fConst14 * ((fConst15 * fRec23[1]) + (0.025000000000000001 * (fRec19[0] - fRec19[1]))));
		double fTemp6 = double(input0[i0]);
		double fTemp7 = std::fabs(fTemp6);
		fRec28[0] = ((0.99990000000000001 * fRec28[1]) + (9.9999999999988987e-05 * fTemp7));
		double fTemp8 = std::max<double>(fRec28[0], fTemp7);
		fVec2[(IOTA & 32767)] = fTemp8;
		fRec30[0] = ((fTemp8 + fRec30[1]) - fVec2[((IOTA - iConst20) & 32767)]);
		fRec29[0] = ((0.999 * fRec29[1]) + (fConst19 * fRec30[0]));
		double fTemp9 = std::max<double>(-1.0, std::min<double>(-0.01, (fTemp8 + (-1.0 - (1.02 * fRec29[0])))));
		double fTemp10 = (fTemp6 - fTemp9);
		double fTemp11 = (40.100000000000001 * fTemp10);
		double fTemp12 = std::max<double>(-600.0, fTemp11);
		double fTemp13 = (0.0 - (40.100000000000001 * fTemp9));
		double fTemp14 = std::max<double>(-600.0, fTemp13);
		double fTemp15 = (((std::fabs(fTemp11) > 0.0001) ? ((fTemp12 < -50.0) ? (0.0 - (fTemp12 * std::exp(fTemp12))) : (fTemp12 / (1.0 - std::exp((-1.0 * fTemp12))))) : ((fTemp10 * ((134.00083333333336 * fTemp10) + 20.050000000000001)) + 1.0)) - ((std::fabs(fTemp13) > 0.0001) ? ((fTemp14 < -50.0) ? (0.0 - (fTemp14 * std::exp(fTemp14))) : (fTemp14 / (1.0 - std::exp((-1.0 * fTemp14))))) : ((fTemp13 * ((0.083333333333333329 * fTemp13) + 0.5)) + 1.0)));
		fRec31[0] = (fSlow2 + (0.999 * fRec31[1]));
		double fTemp16 = (1.0 - fRec31[0]);
		double fTemp17 = (fSlow6 * fRec31[0]);
		double fTemp18 = (0.024937655860349125 * (fRec31[0] * fTemp15));
		double fTemp19 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow7 * std::max<double>(-0.69999999999999996, std::min<double>(0.69999999999999996, fTemp18)))));
		fRec39[0] = (fTemp18 - (fConst36 * ((fConst37 * fRec39[2]) + (fConst38 * fRec39[1]))));
		double fTemp20 = (fRec39[2] + (fRec39[0] + (2.0 * fRec39[1])));
		fVec3[0] = fTemp20;
		fRec38[0] = ((fConst36 * ((fConst4 * fTemp20) + (fConst11 * fVec3[1]))) - (fConst12 * fRec38[1]));
		fRec37[0] = (0.0 - (fConst32 * ((fConst33 * fRec37[1]) - (fRec38[0] + fRec38[1]))));
		fRec36[0] = (fRec37[0] - (fConst28 * ((fConst39 * fRec36[2]) + (fConst42 * fRec36[1]))));
		double fTemp21 = (fRec36[2] + (fRec36[0] + (2.0 * fRec36[1])));
		fVec4[0] = fTemp21;
		fRec35[0] = ((fConst28 * ((fConst30 * fTemp21) + (fConst43 * fVec4[1]))) - (fConst45 * fRec35[1]));
		fRec34[0] = (fRec35[0] - (fConst23 * ((fConst46 * fRec34[2]) + (fConst47 * fRec34[1]))));
		double fTemp22 = (fConst57 * fRec33[1]);
		fRec33[0] = ((fConst23 * (((fConst25 * fRec34[0]) + (fConst48 * fRec34[1])) + (fConst25 * fRec34[2]))) - (fConst52 * ((fConst54 * fRec33[2]) + fTemp22)));
		double fTemp23 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow9 * (fRec33[2] + (fConst52 * (fTemp22 + (fConst54 * fRec33[0])))))));
		fRec43[0] = ((fConst58 * fRec38[1]) - (fConst32 * ((fConst33 * fRec43[1]) - (fConst27 * fRec38[0]))));
		fRec42[0] = (fRec43[0] - (fConst28 * ((fConst39 * fRec42[2]) + (fConst42 * fRec42[1]))));
		double fTemp24 = (fConst47 * fRec41[1]);
		fRec41[0] = ((fConst28 * (((fConst41 * fRec42[0]) + (fConst59 * fRec42[1])) + (fConst41 * fRec42[2]))) - (fConst60 * ((fConst61 * fRec41[2]) + fTemp24)));
		double fTemp25 = (fConst57 * fRec40[1]);
		fRec40[0] = ((fRec41[2] + (fConst60 * (fTemp24 + (fConst61 * fRec41[0])))) - (fConst52 * ((fConst54 * fRec40[2]) + fTemp25)));
		double fTemp26 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow10 * (fRec40[2] + (fConst52 * (fTemp25 + (fConst54 * fRec40[0])))))));
		fRec47[0] = (0.0 - (fConst64 * ((fConst44 * fRec47[1]) - (fConst28 * (fTemp21 + fVec4[1])))));
		fRec46[0] = (fRec47[0] - (fConst23 * ((fConst46 * fRec46[2]) + (fConst47 * fRec46[1]))));
		double fTemp27 = (fRec46[2] + (fRec46[0] + (2.0 * fRec46[1])));
		fVec5[0] = fTemp27;
		fRec45[0] = ((fConst23 * ((fConst63 * fTemp27) + (fConst65 * fVec5[1]))) - (fConst66 * fRec45[1]));
		fRec44[0] = (fRec45[0] - (fConst62 * ((fConst67 * fRec44[2]) + (fConst57 * fRec44[1]))));
		double fTemp28 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow11 * (((fConst56 * fRec44[0]) + (fConst68 * fRec44[1])) + (fConst56 * fRec44[2])))));
		fRec49[0] = (0.0 - (fConst69 * ((fConst53 * fRec49[1]) - (fConst23 * (fTemp27 + fVec5[1])))));
		fRec48[0] = (fRec49[0] - (fConst62 * ((fConst67 * fRec48[2]) + (fConst57 * fRec48[1]))));
		double fTemp29 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow12 * (fRec48[2] + (fRec48[0] + (2.0 * fRec48[1]))))));
		double fTemp30 = (((1.333521432 * (fTemp23 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp23))))) + (1.584893192 * ((fTemp26 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp26)))) + (fTemp28 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp28))))))) + (1.2589412 * (fTemp29 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp29))))));
		fVec6[0] = fTemp30;
		fRec32[0] = (0.0 - (fConst6 * ((fConst7 * fRec32[1]) - (fTemp30 + fVec6[1]))));
		double fTemp31 = ((fTemp15 * ((fTemp16 * ((fSlow4 * ((0.099750623441396499 * (1.0 - std::fabs((0.024937655860349125 * (fTemp16 * fTemp15))))) + -0.024937655860349125)) + 0.024937655860349125)) + fTemp17)) + ((0.5 * (fTemp19 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp19))))) + (fSlow8 * fRec32[0])));
		fVec7[0] = fTemp31;
		fRec27[0] = ((0.93028479253239138 * (fTemp31 + fVec7[1])) - (0.86056958506478287 * fRec27[1]));
		fRec26[0] = (fRec27[0] - ((1.8405051250752198 * fRec26[1]) + (0.86129424393186271 * fRec26[2])));
		double fTemp32 = (0.92544984225177063 * (fRec26[0] + fRec26[2]));
		double fTemp33 = (1.8508996845035413 * fRec26[1]);
		double fTemp34 = ((fTemp33 + fTemp32) / (double(Ranode(int(TUBE_TABLE_12AT7_68k), double(fRec25[1]))) + 100000.0));
		fVec8[0] = fTemp34;
		fRec50[0] = (fConst71 * ((2700.0 * (fTemp34 + fVec8[1])) - (fConst72 * fRec50[1])));
		fRec25[0] = (double(Ftube(int(TUBE_TABLE_12AT7_68k), double(((fTemp32 + (fRec50[0] + fTemp33)) + -2.617753)))) + -153.04618518518518);
		fRec24[0] = ((0.025000000000000001 * ((fConst4 * fRec25[0]) + (fConst11 * fRec25[1]))) - (fConst12 * fRec24[1]));
		fRec51[0] = (fConst14 * ((fConst15 * fRec51[1]) + (0.025000000000000001 * (fRec25[0] - fRec25[1]))));
		fRec17[0] = ((0.59999999999999998 * (iSlow1 ? fRec23[0] : fRec18[0])) - (iSlow1 ? fRec51[0] : fRec24[0]));
		fRec52[0] = (fSlow13 + (0.999 * fRec52[1]));
		double fTemp35 = (fRec17[0] * fRec52[0]);
		fVec9[0] = fTemp35;
		fRec16[0] = (0.0 - (fConst6 * ((fConst7 * fRec16[1]) - (fTemp35 + fVec9[1]))));
		fRec15[0] = ((0.93028479253239138 * (fRec16[0] + fRec16[1])) - (0.86056958506478287 * fRec15[1]));
		fRec14[0] = (fRec15[0] - ((1.8405051250752198 * fRec14[1]) + (0.86129424393186271 * fRec14[2])));
		double fTemp36 = (0.92544984225177063 * (fRec14[0] + fRec14[2]));
		double fTemp37 = (1.8508996845035413 * fRec14[1]);
		double fTemp38 = ((fTemp37 + fTemp36) / (double(Ranode(int(TUBE_TABLE_12AT7_250k), double(fRec13[1]))) + 100000.0));
		fVec10[0] = fTemp38;
		fRec53[0] = (fConst17 * ((1500.0 * (fTemp38 + fVec10[1])) - (fConst18 * fRec53[1])));
		fRec13[0] = (double(Ftube(int(TUBE_TABLE_12AT7_250k), double(((fTemp36 + (fRec53[0] + fTemp37)) + -1.887332)))) + -124.17786666666666);
		fRec12[0] = ((0.025000000000000001 * ((fConst4 * fRec13[0]) + (fConst11 * fRec13[1]))) - (fConst12 * fRec12[1]));
		fRec54[0] = (fConst14 * ((fConst15 * fRec54[1]) + (0.025000000000000001 * (fRec13[0] - fRec13[1]))));
		fRec5[0] = ((0.59999999999999998 * (iSlow1 ? fRec11[0] : fRec6[0])) + (iSlow1 ? fRec54[0] : fRec12[0]));
		fRec4[0] = (0.0 - (fConst6 * ((fConst7 * fRec4[1]) - (fRec5[0] + fRec5[1]))));
		fRec3[0] = ((0.93028479253239138 * (fRec4[0] + fRec4[1])) - (0.86056958506478287 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.86129424393186271 * fRec2[2])));
		double fTemp39 = (0.92544984225177063 * (fRec2[0] + fRec2[2]));
		double fTemp40 = (1.8508996845035413 * fRec2[1]);
		double fTemp41 = ((fTemp40 + fTemp39) / (double(Ranode(int(TUBE_TABLE_12AT7_250k), double(fRec1[1]))) + 100000.0));
		fVec11[0] = fTemp41;
		fRec55[0] = (fConst9 * ((820.0 * (fTemp41 + fVec11[1])) - (fConst10 * fRec55[1])));
		fRec1[0] = (double(Ftube(int(TUBE_TABLE_12AT7_250k), double(((fTemp39 + (fRec55[0] + fTemp40)) + -1.2569619999999999)))) + -96.711951219512201);
		fRec0[0] = ((0.025000000000000001 * ((fConst4 * fRec1[0]) + (fConst11 * fRec1[1]))) - (fConst12 * fRec0[1]));
		fRec56[0] = (fConst14 * ((fConst15 * fRec56[1]) + (0.025000000000000001 * (fRec1[0] - fRec1[1]))));
		fRec57[0] = (fSlow14 + (0.999 * fRec57[1]));
		output0[i0] = FAUSTFLOAT(((iSlow0 ? fRec56[0] : fRec0[0]) * fRec57[0]));
		fRec67[0] = ((0.93028479253239138 * (fRec63[1] + fRec63[2])) - (0.86056958506478287 * fRec67[1]));
		fRec66[0] = (fRec67[0] - ((1.8405051250752198 * fRec66[1]) + (0.86129424393186271 * fRec66[2])));
		double fTemp42 = (0.92544984225177063 * (fRec66[0] + fRec66[2]));
		double fTemp43 = (1.8508996845035413 * fRec66[1]);
		double fTemp44 = ((fTemp43 + fTemp42) / (double(Ranode(int(TUBE_TABLE_12AT7_250k), double(fRec65[1]))) + 100000.0));
		fVec12[0] = fTemp44;
		fRec68[0] = (fConst9 * ((820.0 * (fTemp44 + fVec12[1])) - (fConst10 * fRec68[1])));
		fRec65[0] = (double(Ftube(int(TUBE_TABLE_12AT7_250k), double(((fTemp42 + (fRec68[0] + fTemp43)) + -1.2569619999999999)))) + -96.711951219512201);
		fRec64[0] = ((0.025000000000000001 * ((fConst4 * fRec65[0]) + (fConst11 * fRec65[1]))) - (fConst12 * fRec64[1]));
		fRec69[0] = (fConst14 * ((fConst15 * fRec69[1]) + (0.025000000000000001 * (fRec65[0] - fRec65[1]))));
		fRec79[0] = ((0.93028479253239138 * (fRec75[1] + fRec75[2])) - (0.86056958506478287 * fRec79[1]));
		fRec78[0] = (fRec79[0] - ((1.8405051250752198 * fRec78[1]) + (0.86129424393186271 * fRec78[2])));
		double fTemp45 = (0.92544984225177063 * (fRec78[0] + fRec78[2]));
		double fTemp46 = (1.8508996845035413 * fRec78[1]);
		double fTemp47 = ((fTemp46 + fTemp45) / (double(Ranode(int(TUBE_TABLE_12AT7_250k), double(fRec77[1]))) + 100000.0));
		fVec13[0] = fTemp47;
		fRec80[0] = (fConst17 * ((1500.0 * (fTemp47 + fVec13[1])) - (fConst18 * fRec80[1])));
		fRec77[0] = (double(Ftube(int(TUBE_TABLE_12AT7_250k), double(((fTemp45 + (fRec80[0] + fTemp46)) + -1.887332)))) + -124.17786666666666);
		fRec76[0] = ((0.025000000000000001 * ((fConst4 * fRec77[0]) + (fConst11 * fRec77[1]))) - (fConst12 * fRec76[1]));
		fRec81[0] = (fConst14 * ((fConst15 * fRec81[1]) + (0.025000000000000001 * (fRec77[0] - fRec77[1]))));
		double fTemp48 = double(input1[i0]);
		double fTemp49 = std::fabs(fTemp48);
		fRec86[0] = ((0.99990000000000001 * fRec86[1]) + (9.9999999999988987e-05 * fTemp49));
		double fTemp50 = std::max<double>(fRec86[0], fTemp49);
		fVec14[(IOTA & 32767)] = fTemp50;
		fRec88[0] = ((fTemp50 + fRec88[1]) - fVec14[((IOTA - iConst20) & 32767)]);
		fRec87[0] = ((0.999 * fRec87[1]) + (fConst19 * fRec88[0]));
		double fTemp51 = std::max<double>(-1.0, std::min<double>(-0.01, (fTemp50 + (-1.0 - (1.02 * fRec87[0])))));
		double fTemp52 = (fTemp48 - fTemp51);
		double fTemp53 = (40.100000000000001 * fTemp52);
		double fTemp54 = std::max<double>(-600.0, fTemp53);
		double fTemp55 = (0.0 - (40.100000000000001 * fTemp51));
		double fTemp56 = std::max<double>(-600.0, fTemp55);
		double fTemp57 = (((std::fabs(fTemp53) > 0.0001) ? ((fTemp54 < -50.0) ? (0.0 - (fTemp54 * std::exp(fTemp54))) : (fTemp54 / (1.0 - std::exp((-1.0 * fTemp54))))) : ((fTemp52 * ((134.00083333333336 * fTemp52) + 20.050000000000001)) + 1.0)) - ((std::fabs(fTemp55) > 0.0001) ? ((fTemp56 < -50.0) ? (0.0 - (fTemp56 * std::exp(fTemp56))) : (fTemp56 / (1.0 - std::exp((-1.0 * fTemp56))))) : ((fTemp55 * ((0.083333333333333329 * fTemp55) + 0.5)) + 1.0)));
		double fTemp58 = (0.024937655860349125 * (fRec31[0] * fTemp57));
		double fTemp59 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow7 * std::max<double>(-0.69999999999999996, std::min<double>(0.69999999999999996, fTemp58)))));
		fRec96[0] = (fTemp58 - (fConst36 * ((fConst37 * fRec96[2]) + (fConst38 * fRec96[1]))));
		double fTemp60 = (fRec96[2] + (fRec96[0] + (2.0 * fRec96[1])));
		fVec15[0] = fTemp60;
		fRec95[0] = ((fConst36 * ((fConst4 * fTemp60) + (fConst11 * fVec15[1]))) - (fConst12 * fRec95[1]));
		fRec94[0] = (0.0 - (fConst32 * ((fConst33 * fRec94[1]) - (fRec95[0] + fRec95[1]))));
		fRec93[0] = (fRec94[0] - (fConst28 * ((fConst39 * fRec93[2]) + (fConst42 * fRec93[1]))));
		double fTemp61 = (fRec93[2] + (fRec93[0] + (2.0 * fRec93[1])));
		fVec16[0] = fTemp61;
		fRec92[0] = ((fConst28 * ((fConst30 * fTemp61) + (fConst43 * fVec16[1]))) - (fConst45 * fRec92[1]));
		fRec91[0] = (fRec92[0] - (fConst23 * ((fConst46 * fRec91[2]) + (fConst47 * fRec91[1]))));
		double fTemp62 = (fConst57 * fRec90[1]);
		fRec90[0] = ((fConst23 * (((fConst25 * fRec91[0]) + (fConst48 * fRec91[1])) + (fConst25 * fRec91[2]))) - (fConst52 * ((fConst54 * fRec90[2]) + fTemp62)));
		double fTemp63 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow9 * (fRec90[2] + (fConst52 * (fTemp62 + (fConst54 * fRec90[0])))))));
		fRec100[0] = ((fConst58 * fRec95[1]) - (fConst32 * ((fConst33 * fRec100[1]) - (fConst27 * fRec95[0]))));
		fRec99[0] = (fRec100[0] - (fConst28 * ((fConst39 * fRec99[2]) + (fConst42 * fRec99[1]))));
		double fTemp64 = (fConst47 * fRec98[1]);
		fRec98[0] = ((fConst28 * (((fConst41 * fRec99[0]) + (fConst59 * fRec99[1])) + (fConst41 * fRec99[2]))) - (fConst60 * ((fConst61 * fRec98[2]) + fTemp64)));
		double fTemp65 = (fConst57 * fRec97[1]);
		fRec97[0] = ((fRec98[2] + (fConst60 * (fTemp64 + (fConst61 * fRec98[0])))) - (fConst52 * ((fConst54 * fRec97[2]) + fTemp65)));
		double fTemp66 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow10 * (fRec97[2] + (fConst52 * (fTemp65 + (fConst54 * fRec97[0])))))));
		fRec104[0] = (0.0 - (fConst64 * ((fConst44 * fRec104[1]) - (fConst28 * (fTemp61 + fVec16[1])))));
		fRec103[0] = (fRec104[0] - (fConst23 * ((fConst46 * fRec103[2]) + (fConst47 * fRec103[1]))));
		double fTemp67 = (fRec103[2] + (fRec103[0] + (2.0 * fRec103[1])));
		fVec17[0] = fTemp67;
		fRec102[0] = ((fConst23 * ((fConst63 * fTemp67) + (fConst65 * fVec17[1]))) - (fConst66 * fRec102[1]));
		fRec101[0] = (fRec102[0] - (fConst62 * ((fConst67 * fRec101[2]) + (fConst57 * fRec101[1]))));
		double fTemp68 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow11 * (((fConst56 * fRec101[0]) + (fConst68 * fRec101[1])) + (fConst56 * fRec101[2])))));
		fRec106[0] = (0.0 - (fConst69 * ((fConst53 * fRec106[1]) - (fConst23 * (fTemp67 + fVec17[1])))));
		fRec105[0] = (fRec106[0] - (fConst62 * ((fConst67 * fRec105[2]) + (fConst57 * fRec105[1]))));
		double fTemp69 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow12 * (fRec105[2] + (fRec105[0] + (2.0 * fRec105[1]))))));
		double fTemp70 = (((1.333521432 * (fTemp63 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp63))))) + (1.584893192 * ((fTemp66 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp66)))) + (fTemp68 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp68))))))) + (1.2589412 * (fTemp69 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp69))))));
		fVec18[0] = fTemp70;
		fRec89[0] = (0.0 - (fConst6 * ((fConst7 * fRec89[1]) - (fTemp70 + fVec18[1]))));
		double fTemp71 = ((fTemp57 * (fTemp17 + (fTemp16 * ((fSlow4 * ((0.099750623441396499 * (1.0 - std::fabs((0.024937655860349125 * (fTemp16 * fTemp57))))) + -0.024937655860349125)) + 0.024937655860349125)))) + ((0.5 * (fTemp59 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp59))))) + (fSlow8 * fRec89[0])));
		fVec19[0] = fTemp71;
		fRec85[0] = ((0.93028479253239138 * (fTemp71 + fVec19[1])) - (0.86056958506478287 * fRec85[1]));
		fRec84[0] = (fRec85[0] - ((1.8405051250752198 * fRec84[1]) + (0.86129424393186271 * fRec84[2])));
		double fTemp72 = (0.92544984225177063 * (fRec84[0] + fRec84[2]));
		double fTemp73 = (1.8508996845035413 * fRec84[1]);
		double fTemp74 = ((fTemp73 + fTemp72) / (double(Ranode(int(TUBE_TABLE_12AT7_68k), double(fRec83[1]))) + 100000.0));
		fVec20[0] = fTemp74;
		fRec107[0] = (fConst71 * ((2700.0 * (fTemp74 + fVec20[1])) - (fConst72 * fRec107[1])));
		fRec83[0] = (double(Ftube(int(TUBE_TABLE_12AT7_68k), double(((fTemp72 + (fRec107[0] + fTemp73)) + -2.617753)))) + -153.04618518518518);
		fRec82[0] = ((0.025000000000000001 * ((fConst4 * fRec83[0]) + (fConst11 * fRec83[1]))) - (fConst12 * fRec82[1]));
		fRec108[0] = (fConst14 * ((fConst15 * fRec108[1]) + (0.025000000000000001 * (fRec83[0] - fRec83[1]))));
		fRec75[0] = ((0.59999999999999998 * (iSlow1 ? fRec81[0] : fRec76[0])) - (iSlow1 ? fRec108[0] : fRec82[0]));
		double fTemp75 = (fRec52[0] * fRec75[0]);
		fVec21[0] = fTemp75;
		fRec74[0] = (0.0 - (fConst6 * ((fConst7 * fRec74[1]) - (fTemp75 + fVec21[1]))));
		fRec73[0] = ((0.93028479253239138 * (fRec74[0] + fRec74[1])) - (0.86056958506478287 * fRec73[1]));
		fRec72[0] = (fRec73[0] - ((1.8405051250752198 * fRec72[1]) + (0.86129424393186271 * fRec72[2])));
		double fTemp76 = (0.92544984225177063 * (fRec72[0] + fRec72[2]));
		double fTemp77 = (1.8508996845035413 * fRec72[1]);
		double fTemp78 = ((fTemp77 + fTemp76) / (double(Ranode(int(TUBE_TABLE_12AT7_250k), double(fRec71[1]))) + 100000.0));
		fVec22[0] = fTemp78;
		fRec109[0] = (fConst17 * ((1500.0 * (fTemp78 + fVec22[1])) - (fConst18 * fRec109[1])));
		fRec71[0] = (double(Ftube(int(TUBE_TABLE_12AT7_250k), double(((fTemp76 + (fRec109[0] + fTemp77)) + -1.887332)))) + -124.17786666666666);
		fRec70[0] = ((0.025000000000000001 * ((fConst4 * fRec71[0]) + (fConst11 * fRec71[1]))) - (fConst12 * fRec70[1]));
		fRec110[0] = (fConst14 * ((fConst15 * fRec110[1]) + (0.025000000000000001 * (fRec71[0] - fRec71[1]))));
		fRec63[0] = ((0.59999999999999998 * (iSlow1 ? fRec69[0] : fRec64[0])) + (iSlow1 ? fRec110[0] : fRec70[0]));
		fRec62[0] = (0.0 - (fConst6 * ((fConst7 * fRec62[1]) - (fRec63[0] + fRec63[1]))));
		fRec61[0] = ((0.93028479253239138 * (fRec62[0] + fRec62[1])) - (0.86056958506478287 * fRec61[1]));
		fRec60[0] = (fRec61[0] - ((1.8405051250752198 * fRec60[1]) + (0.86129424393186271 * fRec60[2])));
		double fTemp79 = (0.92544984225177063 * (fRec60[0] + fRec60[2]));
		double fTemp80 = (1.8508996845035413 * fRec60[1]);
		double fTemp81 = ((fTemp80 + fTemp79) / (double(Ranode(int(TUBE_TABLE_12AT7_250k), double(fRec59[1]))) + 100000.0));
		fVec23[0] = fTemp81;
		fRec111[0] = (fConst9 * ((820.0 * (fTemp81 + fVec23[1])) - (fConst10 * fRec111[1])));
		fRec59[0] = (double(Ftube(int(TUBE_TABLE_12AT7_250k), double(((fTemp79 + (fRec111[0] + fTemp80)) + -1.2569619999999999)))) + -96.711951219512201);
		fRec58[0] = ((0.025000000000000001 * ((fConst4 * fRec59[0]) + (fConst11 * fRec59[1]))) - (fConst12 * fRec58[1]));
		fRec112[0] = (fConst14 * ((fConst15 * fRec112[1]) + (0.025000000000000001 * (fRec59[0] - fRec59[1]))));
		output1[i0] = FAUSTFLOAT((fRec57[0] * (iSlow0 ? fRec112[0] : fRec58[0])));
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fVec0[1] = fVec0[0];
		fRec10[1] = fRec10[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec11[1] = fRec11[0];
		fRec21[1] = fRec21[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fVec1[1] = fVec1[0];
		fRec22[1] = fRec22[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec23[1] = fRec23[0];
		fRec28[1] = fRec28[0];
		IOTA = (IOTA + 1);
		fRec30[1] = fRec30[0];
		fRec29[1] = fRec29[0];
		fRec31[1] = fRec31[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fVec3[1] = fVec3[0];
		fRec38[1] = fRec38[0];
		fRec37[1] = fRec37[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		fVec4[1] = fVec4[0];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fRec43[1] = fRec43[0];
		fRec42[2] = fRec42[1];
		fRec42[1] = fRec42[0];
		fRec41[2] = fRec41[1];
		fRec41[1] = fRec41[0];
		fRec40[2] = fRec40[1];
		fRec40[1] = fRec40[0];
		fRec47[1] = fRec47[0];
		fRec46[2] = fRec46[1];
		fRec46[1] = fRec46[0];
		fVec5[1] = fVec5[0];
		fRec45[1] = fRec45[0];
		fRec44[2] = fRec44[1];
		fRec44[1] = fRec44[0];
		fRec49[1] = fRec49[0];
		fRec48[2] = fRec48[1];
		fRec48[1] = fRec48[0];
		fVec6[1] = fVec6[0];
		fRec32[1] = fRec32[0];
		fVec7[1] = fVec7[0];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fVec8[1] = fVec8[0];
		fRec50[1] = fRec50[0];
		fRec25[1] = fRec25[0];
		fRec24[1] = fRec24[0];
		fRec51[1] = fRec51[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fRec52[1] = fRec52[0];
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
		fRec79[1] = fRec79[0];
		fRec78[2] = fRec78[1];
		fRec78[1] = fRec78[0];
		fVec13[1] = fVec13[0];
		fRec80[1] = fRec80[0];
		fRec77[1] = fRec77[0];
		fRec76[1] = fRec76[0];
		fRec81[1] = fRec81[0];
		fRec86[1] = fRec86[0];
		fRec88[1] = fRec88[0];
		fRec87[1] = fRec87[0];
		fRec96[2] = fRec96[1];
		fRec96[1] = fRec96[0];
		fVec15[1] = fVec15[0];
		fRec95[1] = fRec95[0];
		fRec94[1] = fRec94[0];
		fRec93[2] = fRec93[1];
		fRec93[1] = fRec93[0];
		fVec16[1] = fVec16[0];
		fRec92[1] = fRec92[0];
		fRec91[2] = fRec91[1];
		fRec91[1] = fRec91[0];
		fRec90[2] = fRec90[1];
		fRec90[1] = fRec90[0];
		fRec100[1] = fRec100[0];
		fRec99[2] = fRec99[1];
		fRec99[1] = fRec99[0];
		fRec98[2] = fRec98[1];
		fRec98[1] = fRec98[0];
		fRec97[2] = fRec97[1];
		fRec97[1] = fRec97[0];
		fRec104[1] = fRec104[0];
		fRec103[2] = fRec103[1];
		fRec103[1] = fRec103[0];
		fVec17[1] = fVec17[0];
		fRec102[1] = fRec102[0];
		fRec101[2] = fRec101[1];
		fRec101[1] = fRec101[0];
		fRec106[1] = fRec106[0];
		fRec105[2] = fRec105[1];
		fRec105[1] = fRec105[0];
		fVec18[1] = fVec18[0];
		fRec89[1] = fRec89[0];
		fVec19[1] = fVec19[0];
		fRec85[1] = fRec85[0];
		fRec84[2] = fRec84[1];
		fRec84[1] = fRec84[0];
		fVec20[1] = fVec20[0];
		fRec107[1] = fRec107[0];
		fRec83[1] = fRec83[0];
		fRec82[1] = fRec82[0];
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
   HIGHGAIN, 
   PREGAIN, 
   GAIN1, 
} PortIndex;
*/

} // end namespace gxamp17_stereo
