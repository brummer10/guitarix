// generated from file '../src/LV2/faust/gxamp5_stereo.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxamp5_stereo {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec4[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec19[2];
	double fVec0[2];
	double fRec18[2];
	double fRec17[3];
	double fConst4;
	double fConst5;
	double fVec1[2];
	double fConst6;
	double fRec20[2];
	double fRec16[2];
	double fConst7;
	double fConst8;
	double fRec15[2];
	double fConst9;
	double fConst10;
	double fConst11;
	double fRec21[2];
	double fVec2[2];
	double fConst12;
	double fConst13;
	double fConst14;
	double fRec14[2];
	double fRec13[2];
	double fRec12[3];
	double fConst15;
	double fConst16;
	double fVec3[2];
	double fConst17;
	double fRec22[2];
	double fRec11[2];
	double fRec10[2];
	double fRec23[2];
	double fVec4[2];
	double fRec9[2];
	double fRec8[3];
	double fConst18;
	double fConst19;
	double fVec5[2];
	double fConst20;
	double fRec24[2];
	double fRec7[2];
	double fRec6[2];
	double fRec25[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec26[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
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
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
	double fConst46;
	double fConst47;
	double fRec35[3];
	double fVec6[2];
	double fConst48;
	double fRec34[2];
	double fConst49;
	double fConst50;
	double fRec33[2];
	double fRec32[3];
	double fVec7[2];
	double fConst51;
	double fConst52;
	double fConst53;
	double fRec31[2];
	double fRec30[3];
	double fVec8[2];
	double fConst54;
	double fConst55;
	double fConst56;
	double fRec29[2];
	double fRec28[3];
	double fConst57;
	double fRec37[2];
	double fRec36[3];
	double fConst58;
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;
	double fRec41[2];
	double fRec40[3];
	double fConst63;
	double fRec39[3];
	double fRec38[3];
	double fConst64;
	double fRec44[2];
	double fRec43[3];
	double fConst65;
	double fRec42[3];
	double fVec9[2];
	double fRec27[2];
	double fVec10[2];
	double fRec5[2];
	double fVec11[2];
	double fRec3[2];
	double fRec2[3];
	double fVec12[2];
	double fRec45[2];
	double fRec1[2];
	double fRec0[2];
	double fRec46[2];
	double fVec13[2];
	double fRec49[2];
	double fRec48[2];
	double fRec47[2];
	double fRec50[2];
	double fVec14[2];
	double fRec68[2];
	double fRec67[3];
	double fVec15[2];
	double fRec69[2];
	double fRec66[2];
	double fRec65[2];
	double fRec70[2];
	double fVec16[2];
	double fRec64[2];
	double fRec63[2];
	double fRec62[3];
	double fVec17[2];
	double fRec71[2];
	double fRec61[2];
	double fRec60[2];
	double fRec72[2];
	double fVec18[2];
	double fRec59[2];
	double fRec58[3];
	double fVec19[2];
	double fRec73[2];
	double fRec57[2];
	double fRec56[2];
	double fRec74[2];
	double fRec83[3];
	double fVec20[2];
	double fRec82[2];
	double fRec81[2];
	double fRec80[3];
	double fVec21[2];
	double fRec79[2];
	double fRec78[3];
	double fVec22[2];
	double fRec77[2];
	double fRec76[3];
	double fRec85[2];
	double fRec84[3];
	double fRec89[2];
	double fRec88[3];
	double fRec87[3];
	double fRec86[3];
	double fRec92[2];
	double fRec91[3];
	double fRec90[3];
	double fVec23[2];
	double fRec75[2];
	double fVec24[2];
	double fRec55[2];
	double fVec25[2];
	double fRec54[2];
	double fRec53[3];
	double fVec26[2];
	double fRec93[2];
	double fRec52[2];
	double fRec51[2];
	double fRec94[2];
	double fVec27[2];
	double fRec97[2];
	double fRec96[2];
	double fRec95[2];
	double fRec98[2];

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
	id = "pre 12ax7/ master 6V6";
	name = N_("pre 12ax7/ master 6V6");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec4[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec19[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fVec0[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec18[l3] = 0.0;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRec17[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fVec1[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec20[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec16[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec15[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec21[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fVec2[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec14[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec13[l12] = 0.0;
	for (int l13 = 0; l13 < 3; l13 = l13 + 1) fRec12[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fVec3[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec22[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec11[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec10[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec23[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fVec4[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec9[l20] = 0.0;
	for (int l21 = 0; l21 < 3; l21 = l21 + 1) fRec8[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fVec5[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec24[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec7[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec6[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec25[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec26[l27] = 0.0;
	for (int l28 = 0; l28 < 3; l28 = l28 + 1) fRec35[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fVec6[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec34[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec33[l31] = 0.0;
	for (int l32 = 0; l32 < 3; l32 = l32 + 1) fRec32[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fVec7[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fRec31[l34] = 0.0;
	for (int l35 = 0; l35 < 3; l35 = l35 + 1) fRec30[l35] = 0.0;
	for (int l36 = 0; l36 < 2; l36 = l36 + 1) fVec8[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec29[l37] = 0.0;
	for (int l38 = 0; l38 < 3; l38 = l38 + 1) fRec28[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec37[l39] = 0.0;
	for (int l40 = 0; l40 < 3; l40 = l40 + 1) fRec36[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec41[l41] = 0.0;
	for (int l42 = 0; l42 < 3; l42 = l42 + 1) fRec40[l42] = 0.0;
	for (int l43 = 0; l43 < 3; l43 = l43 + 1) fRec39[l43] = 0.0;
	for (int l44 = 0; l44 < 3; l44 = l44 + 1) fRec38[l44] = 0.0;
	for (int l45 = 0; l45 < 2; l45 = l45 + 1) fRec44[l45] = 0.0;
	for (int l46 = 0; l46 < 3; l46 = l46 + 1) fRec43[l46] = 0.0;
	for (int l47 = 0; l47 < 3; l47 = l47 + 1) fRec42[l47] = 0.0;
	for (int l48 = 0; l48 < 2; l48 = l48 + 1) fVec9[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec27[l49] = 0.0;
	for (int l50 = 0; l50 < 2; l50 = l50 + 1) fVec10[l50] = 0.0;
	for (int l51 = 0; l51 < 2; l51 = l51 + 1) fRec5[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fVec11[l52] = 0.0;
	for (int l53 = 0; l53 < 2; l53 = l53 + 1) fRec3[l53] = 0.0;
	for (int l54 = 0; l54 < 3; l54 = l54 + 1) fRec2[l54] = 0.0;
	for (int l55 = 0; l55 < 2; l55 = l55 + 1) fVec12[l55] = 0.0;
	for (int l56 = 0; l56 < 2; l56 = l56 + 1) fRec45[l56] = 0.0;
	for (int l57 = 0; l57 < 2; l57 = l57 + 1) fRec1[l57] = 0.0;
	for (int l58 = 0; l58 < 2; l58 = l58 + 1) fRec0[l58] = 0.0;
	for (int l59 = 0; l59 < 2; l59 = l59 + 1) fRec46[l59] = 0.0;
	for (int l60 = 0; l60 < 2; l60 = l60 + 1) fVec13[l60] = 0.0;
	for (int l61 = 0; l61 < 2; l61 = l61 + 1) fRec49[l61] = 0.0;
	for (int l62 = 0; l62 < 2; l62 = l62 + 1) fRec48[l62] = 0.0;
	for (int l63 = 0; l63 < 2; l63 = l63 + 1) fRec47[l63] = 0.0;
	for (int l64 = 0; l64 < 2; l64 = l64 + 1) fRec50[l64] = 0.0;
	for (int l65 = 0; l65 < 2; l65 = l65 + 1) fVec14[l65] = 0.0;
	for (int l66 = 0; l66 < 2; l66 = l66 + 1) fRec68[l66] = 0.0;
	for (int l67 = 0; l67 < 3; l67 = l67 + 1) fRec67[l67] = 0.0;
	for (int l68 = 0; l68 < 2; l68 = l68 + 1) fVec15[l68] = 0.0;
	for (int l69 = 0; l69 < 2; l69 = l69 + 1) fRec69[l69] = 0.0;
	for (int l70 = 0; l70 < 2; l70 = l70 + 1) fRec66[l70] = 0.0;
	for (int l71 = 0; l71 < 2; l71 = l71 + 1) fRec65[l71] = 0.0;
	for (int l72 = 0; l72 < 2; l72 = l72 + 1) fRec70[l72] = 0.0;
	for (int l73 = 0; l73 < 2; l73 = l73 + 1) fVec16[l73] = 0.0;
	for (int l74 = 0; l74 < 2; l74 = l74 + 1) fRec64[l74] = 0.0;
	for (int l75 = 0; l75 < 2; l75 = l75 + 1) fRec63[l75] = 0.0;
	for (int l76 = 0; l76 < 3; l76 = l76 + 1) fRec62[l76] = 0.0;
	for (int l77 = 0; l77 < 2; l77 = l77 + 1) fVec17[l77] = 0.0;
	for (int l78 = 0; l78 < 2; l78 = l78 + 1) fRec71[l78] = 0.0;
	for (int l79 = 0; l79 < 2; l79 = l79 + 1) fRec61[l79] = 0.0;
	for (int l80 = 0; l80 < 2; l80 = l80 + 1) fRec60[l80] = 0.0;
	for (int l81 = 0; l81 < 2; l81 = l81 + 1) fRec72[l81] = 0.0;
	for (int l82 = 0; l82 < 2; l82 = l82 + 1) fVec18[l82] = 0.0;
	for (int l83 = 0; l83 < 2; l83 = l83 + 1) fRec59[l83] = 0.0;
	for (int l84 = 0; l84 < 3; l84 = l84 + 1) fRec58[l84] = 0.0;
	for (int l85 = 0; l85 < 2; l85 = l85 + 1) fVec19[l85] = 0.0;
	for (int l86 = 0; l86 < 2; l86 = l86 + 1) fRec73[l86] = 0.0;
	for (int l87 = 0; l87 < 2; l87 = l87 + 1) fRec57[l87] = 0.0;
	for (int l88 = 0; l88 < 2; l88 = l88 + 1) fRec56[l88] = 0.0;
	for (int l89 = 0; l89 < 2; l89 = l89 + 1) fRec74[l89] = 0.0;
	for (int l90 = 0; l90 < 3; l90 = l90 + 1) fRec83[l90] = 0.0;
	for (int l91 = 0; l91 < 2; l91 = l91 + 1) fVec20[l91] = 0.0;
	for (int l92 = 0; l92 < 2; l92 = l92 + 1) fRec82[l92] = 0.0;
	for (int l93 = 0; l93 < 2; l93 = l93 + 1) fRec81[l93] = 0.0;
	for (int l94 = 0; l94 < 3; l94 = l94 + 1) fRec80[l94] = 0.0;
	for (int l95 = 0; l95 < 2; l95 = l95 + 1) fVec21[l95] = 0.0;
	for (int l96 = 0; l96 < 2; l96 = l96 + 1) fRec79[l96] = 0.0;
	for (int l97 = 0; l97 < 3; l97 = l97 + 1) fRec78[l97] = 0.0;
	for (int l98 = 0; l98 < 2; l98 = l98 + 1) fVec22[l98] = 0.0;
	for (int l99 = 0; l99 < 2; l99 = l99 + 1) fRec77[l99] = 0.0;
	for (int l100 = 0; l100 < 3; l100 = l100 + 1) fRec76[l100] = 0.0;
	for (int l101 = 0; l101 < 2; l101 = l101 + 1) fRec85[l101] = 0.0;
	for (int l102 = 0; l102 < 3; l102 = l102 + 1) fRec84[l102] = 0.0;
	for (int l103 = 0; l103 < 2; l103 = l103 + 1) fRec89[l103] = 0.0;
	for (int l104 = 0; l104 < 3; l104 = l104 + 1) fRec88[l104] = 0.0;
	for (int l105 = 0; l105 < 3; l105 = l105 + 1) fRec87[l105] = 0.0;
	for (int l106 = 0; l106 < 3; l106 = l106 + 1) fRec86[l106] = 0.0;
	for (int l107 = 0; l107 < 2; l107 = l107 + 1) fRec92[l107] = 0.0;
	for (int l108 = 0; l108 < 3; l108 = l108 + 1) fRec91[l108] = 0.0;
	for (int l109 = 0; l109 < 3; l109 = l109 + 1) fRec90[l109] = 0.0;
	for (int l110 = 0; l110 < 2; l110 = l110 + 1) fVec23[l110] = 0.0;
	for (int l111 = 0; l111 < 2; l111 = l111 + 1) fRec75[l111] = 0.0;
	for (int l112 = 0; l112 < 2; l112 = l112 + 1) fVec24[l112] = 0.0;
	for (int l113 = 0; l113 < 2; l113 = l113 + 1) fRec55[l113] = 0.0;
	for (int l114 = 0; l114 < 2; l114 = l114 + 1) fVec25[l114] = 0.0;
	for (int l115 = 0; l115 < 2; l115 = l115 + 1) fRec54[l115] = 0.0;
	for (int l116 = 0; l116 < 3; l116 = l116 + 1) fRec53[l116] = 0.0;
	for (int l117 = 0; l117 < 2; l117 = l117 + 1) fVec26[l117] = 0.0;
	for (int l118 = 0; l118 < 2; l118 = l118 + 1) fRec93[l118] = 0.0;
	for (int l119 = 0; l119 < 2; l119 = l119 + 1) fRec52[l119] = 0.0;
	for (int l120 = 0; l120 < 2; l120 = l120 + 1) fRec51[l120] = 0.0;
	for (int l121 = 0; l121 < 2; l121 = l121 + 1) fRec94[l121] = 0.0;
	for (int l122 = 0; l122 < 2; l122 = l122 + 1) fVec27[l122] = 0.0;
	for (int l123 = 0; l123 < 2; l123 = l123 + 1) fRec97[l123] = 0.0;
	for (int l124 = 0; l124 < 2; l124 = l124 + 1) fRec96[l124] = 0.0;
	for (int l125 = 0; l125 < 2; l125 = l125 + 1) fRec95[l125] = 0.0;
	for (int l126 = 0; l126 < 2; l126 = l126 + 1) fRec98[l126] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = std::tan(97.38937226128358 / fConst0);
	fConst2 = 1.0 / fConst1;
	fConst3 = 1.0 - fConst2;
	fConst4 = 1.0 / std::tan(270.1769682087222 / fConst0);
	fConst5 = 1.0 - fConst4;
	fConst6 = 1.0 / (fConst4 + 1.0);
	fConst7 = 0.025 / fConst1;
	fConst8 = 1.0 / (fConst2 + 1.0);
	fConst9 = 3.141592653589793 / fConst0;
	fConst10 = 1.0 - fConst9;
	fConst11 = 1.0 / (fConst9 + 1.0);
	fConst12 = 1.0 / std::tan(20517.741620594938 / fConst0);
	fConst13 = 1.0 - fConst12;
	fConst14 = 1.0 / (fConst12 + 1.0);
	fConst15 = 1.0 / std::tan(414.6902302738527 / fConst0);
	fConst16 = 1.0 - fConst15;
	fConst17 = 1.0 / (fConst15 + 1.0);
	fConst18 = 1.0 / std::tan(609.4689747964198 / fConst0);
	fConst19 = 1.0 - fConst18;
	fConst20 = 1.0 / (fConst18 + 1.0);
	fConst21 = std::tan(942.4777960769379 / fConst0);
	fConst22 = mydsp_faustpower2_f(fConst21);
	fConst23 = 2.0 * (1.0 - 1.0 / fConst22);
	fConst24 = 1.0 / fConst21;
	fConst25 = (fConst24 + -1.0000000000000004) / fConst21 + 1.0;
	fConst26 = (fConst24 + 1.0000000000000004) / fConst21 + 1.0;
	fConst27 = 1.0 / fConst26;
	fConst28 = std::tan(3769.9111843077517 / fConst0);
	fConst29 = mydsp_faustpower2_f(fConst28);
	fConst30 = 2.0 * (1.0 - 1.0 / fConst29);
	fConst31 = 1.0 / fConst28;
	fConst32 = (fConst31 + -1.0000000000000004) / fConst28 + 1.0;
	fConst33 = (fConst31 + 1.0000000000000004) / fConst28 + 1.0;
	fConst34 = 1.0 / fConst33;
	fConst35 = std::tan(10053.096491487338 / fConst0);
	fConst36 = mydsp_faustpower2_f(fConst35);
	fConst37 = 2.0 * (1.0 - 1.0 / fConst36);
	fConst38 = 1.0 / fConst35;
	fConst39 = (fConst38 + -1.0000000000000004) / fConst35 + 1.0;
	fConst40 = (fConst38 + 1.0000000000000004) / fConst35 + 1.0;
	fConst41 = 1.0 / fConst40;
	fConst42 = std::tan(47123.8898038469 / fConst0);
	fConst43 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst42));
	fConst44 = 1.0 / fConst42;
	fConst45 = (fConst44 + -1.414213562373095) / fConst42 + 1.0;
	fConst46 = (fConst44 + 1.414213562373095) / fConst42 + 1.0;
	fConst47 = 1.0 / fConst46;
	fConst48 = 1.0 / (fConst1 * fConst46);
	fConst49 = 1.0 - fConst38;
	fConst50 = 1.0 / (fConst38 + 1.0);
	fConst51 = 1.0 - fConst31;
	fConst52 = fConst31 + 1.0;
	fConst53 = 1.0 / fConst52;
	fConst54 = 1.0 - fConst24;
	fConst55 = fConst24 + 1.0;
	fConst56 = 1.0 / fConst55;
	fConst57 = 1.0 / (fConst21 * fConst33);
	fConst58 = 1.0 / (fConst22 * fConst26);
	fConst59 = 1.0 - fConst54 / fConst21;
	fConst60 = 1.0 / (fConst55 / fConst21 + 1.0);
	fConst61 = 1.0 - fConst51 / fConst28;
	fConst62 = 1.0 / (fConst52 / fConst28 + 1.0);
	fConst63 = 1.0 / (fConst36 * fConst40);
	fConst64 = 1.0 / (fConst28 * fConst40);
	fConst65 = 1.0 / (fConst29 * fConst33);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fCheckbox0 (*fCheckbox0_)
#define fVslider0 (*fVslider0_)
#define fCheckbox1 (*fCheckbox1_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	int iSlow0 = int(double(fCheckbox0));
	double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
	int iSlow2 = int(double(fCheckbox1));
	double fSlow3 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider1));
	double fSlow4 = 1.000000000000001e-05 * double(fVslider2);
	double fSlow5 = double(fVslider3);
	double fSlow6 = 2.0 * (fSlow5 + -0.5);
	double fSlow7 = 1.0 - std::max<double>(0.0, fSlow6);
	double fSlow8 = 1.25 * fSlow5;
	double fSlow9 = fConst27 * std::pow(1e+01, 0.9 * fSlow5);
	double fSlow10 = fConst58 * std::pow(1e+01, 2.0 * fSlow5);
	double fSlow11 = std::pow(1e+01, 0.8 * fSlow5);
	double fSlow12 = std::pow(1e+01, 1.2 * fSlow5);
	double fSlow13 = 1.0 - std::max<double>(0.0, -fSlow6);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec4[0] = fSlow1 + 0.999 * fRec4[1];
		fRec19[0] = fSlow3 + 0.999 * fRec19[1];
		double fTemp0 = double(input0[i0]) * fRec19[0];
		fVec0[0] = fTemp0;
		fRec18[0] = 0.9302847925323914 * (fTemp0 + fVec0[1]) - 0.8605695850647829 * fRec18[1];
		fRec17[0] = fRec18[0] - (1.8405051250752198 * fRec17[1] + 0.8612942439318627 * fRec17[2]);
		double fTemp1 = 1.8508996845035413 * fRec17[1];
		double fTemp2 = 0.9254498422517706 * (fRec17[0] + fRec17[2]);
		double fTemp3 = (fTemp1 + fTemp2) / (Ranode(TUBE_TABLE_12AX7_68k, fRec16[1]) + 1e+05);
		fVec1[0] = fTemp3;
		fRec20[0] = fConst6 * (2.7e+03 * (fTemp3 + fVec1[1]) - fConst5 * fRec20[1]);
		fRec16[0] = Ftube(TUBE_TABLE_12AX7_68k, fTemp2 + fRec20[0] + fTemp1 + -1.581656) + -191.42014814814814;
		double fTemp4 = fRec16[0] - fRec16[1];
		fRec15[0] = fConst8 * (fConst7 * fTemp4 - fConst3 * fRec15[1]);
		fRec21[0] = fConst11 * (fConst10 * fRec21[1] + 0.025 * fTemp4);
		double fTemp5 = ((iSlow2) ? fRec21[0] : fRec15[0]);
		fVec2[0] = fTemp5;
		fRec14[0] = -(fConst14 * (fConst13 * fRec14[1] - (fTemp5 + fVec2[1])));
		fRec13[0] = 0.9302847925323914 * (fRec14[0] + fRec14[1]) - 0.8605695850647829 * fRec13[1];
		fRec12[0] = fRec13[0] - (1.8405051250752198 * fRec12[1] + 0.8612942439318627 * fRec12[2]);
		double fTemp6 = 1.8508996845035413 * fRec12[1];
		double fTemp7 = 0.9254498422517706 * (fRec12[0] + fRec12[2]);
		double fTemp8 = (fTemp6 + fTemp7) / (Ranode(TUBE_TABLE_12AX7_250k, fRec11[1]) + 1e+05);
		fVec3[0] = fTemp8;
		fRec22[0] = fConst17 * (1.5e+03 * (fTemp8 + fVec3[1]) - fConst16 * fRec22[1]);
		fRec11[0] = Ftube(TUBE_TABLE_12AX7_250k, fTemp7 + fRec22[0] + fTemp6 + -1.204285) + -169.71433333333334;
		double fTemp9 = fRec11[0] - fRec11[1];
		fRec10[0] = fConst8 * (fConst7 * fTemp9 - fConst3 * fRec10[1]);
		fRec23[0] = fConst11 * (fConst10 * fRec23[1] + 0.025 * fTemp9);
		double fTemp10 = ((iSlow2) ? fRec23[0] : fRec10[0]);
		fVec4[0] = fTemp10;
		fRec9[0] = 0.9302847925323914 * (fTemp10 + fVec4[1]) - 0.8605695850647829 * fRec9[1];
		fRec8[0] = fRec9[0] - (1.8405051250752198 * fRec8[1] + 0.8612942439318627 * fRec8[2]);
		double fTemp11 = 1.8508996845035413 * fRec8[1];
		double fTemp12 = 0.9254498422517706 * (fRec8[0] + fRec8[2]);
		double fTemp13 = (fTemp11 + fTemp12) / (Ranode(TUBE_TABLE_12AX7_250k, fRec7[1]) + 1e+05);
		fVec5[0] = fTemp13;
		fRec24[0] = fConst20 * (8.2e+02 * (fTemp13 + fVec5[1]) - fConst19 * fRec24[1]);
		fRec7[0] = Ftube(TUBE_TABLE_12AX7_250k, fTemp12 + fRec24[0] + fTemp11 + -0.840703) + -147.47524390243905;
		double fTemp14 = fRec7[0] - fRec7[1];
		fRec6[0] = fConst8 * (fConst7 * fTemp14 - fConst3 * fRec6[1]);
		fRec25[0] = fConst11 * (fConst10 * fRec25[1] + 0.025 * fTemp14);
		double fTemp15 = ((iSlow2) ? fRec25[0] : fRec6[0]);
		fRec26[0] = fSlow4 + 0.999 * fRec26[1];
		double fTemp16 = fRec26[0] * fTemp15;
		double fTemp17 = 1.0 - fRec26[0];
		double fTemp18 = fTemp15 * fTemp17;
		double fTemp19 = fTemp18 + 1e-15;
		fRec35[0] = fTemp16 + (1e-15 - fConst47 * (fConst45 * fRec35[2] + fConst43 * fRec35[1]));
		double fTemp20 = fRec35[2] + fRec35[0] + 2.0 * fRec35[1];
		fVec6[0] = fTemp20;
		fRec34[0] = -(fConst8 * (fConst3 * fRec34[1] - fConst48 * (fTemp20 - fVec6[1])));
		fRec33[0] = -(fConst50 * (fConst49 * fRec33[1] - (fRec34[0] + fRec34[1])));
		fRec32[0] = fRec33[0] - fConst41 * (fConst39 * fRec32[2] + fConst37 * fRec32[1]);
		double fTemp21 = fRec32[2] + fRec32[0] + 2.0 * fRec32[1];
		fVec7[0] = fTemp21;
		fRec31[0] = -(fConst53 * (fConst51 * fRec31[1] - fConst41 * (fTemp21 + fVec7[1])));
		fRec30[0] = fRec31[0] - fConst34 * (fConst32 * fRec30[2] + fConst30 * fRec30[1]);
		double fTemp22 = fRec30[2] + fRec30[0] + 2.0 * fRec30[1];
		fVec8[0] = fTemp22;
		fRec29[0] = -(fConst56 * (fConst54 * fRec29[1] - fConst34 * (fTemp22 + fVec8[1])));
		fRec28[0] = fRec29[0] - fConst27 * (fConst25 * fRec28[2] + fConst23 * fRec28[1]);
		double fTemp23 = std::max<double>(-1.0, std::min<double>(1.0, fSlow9 * (fRec28[2] + fRec28[0] + 2.0 * fRec28[1])));
		fRec37[0] = -(fConst56 * (fConst54 * fRec37[1] - fConst57 * (fTemp22 - fVec8[1])));
		fRec36[0] = fRec37[0] - fConst27 * (fConst25 * fRec36[2] + fConst23 * fRec36[1]);
		double fTemp24 = std::max<double>(-1.0, std::min<double>(1.0, fSlow10 * (fRec36[2] + (fRec36[0] - 2.0 * fRec36[1]))));
		double fTemp25 = fConst23 * fRec38[1];
		double fTemp26 = fConst30 * fRec39[1];
		fRec41[0] = -(fConst50 * (fConst49 * fRec41[1] - fConst38 * (fRec34[0] - fRec34[1])));
		fRec40[0] = fRec41[0] - fConst41 * (fConst39 * fRec40[2] + fConst37 * fRec40[1]);
		fRec39[0] = fConst63 * (fRec40[2] + (fRec40[0] - 2.0 * fRec40[1])) - fConst62 * (fConst61 * fRec39[2] + fTemp26);
		fRec38[0] = fRec39[2] + fConst62 * (fTemp26 + fConst61 * fRec39[0]) - fConst60 * (fConst59 * fRec38[2] + fTemp25);
		double fTemp27 = std::max<double>(-1.0, std::min<double>(1.0, fSlow11 * (fRec38[2] + fConst60 * (fTemp25 + fConst59 * fRec38[0]))));
		double fTemp28 = fConst23 * fRec42[1];
		fRec44[0] = -(fConst53 * (fConst51 * fRec44[1] - fConst64 * (fTemp21 - fVec7[1])));
		fRec43[0] = fRec44[0] - fConst34 * (fConst32 * fRec43[2] + fConst30 * fRec43[1]);
		fRec42[0] = fConst65 * (fRec43[2] + (fRec43[0] - 2.0 * fRec43[1])) - fConst60 * (fConst59 * fRec42[2] + fTemp28);
		double fTemp29 = std::max<double>(-1.0, std::min<double>(1.0, fSlow12 * (fRec42[2] + fConst60 * (fTemp28 + fConst59 * fRec42[0]))));
		double fTemp30 = 1.333521432 * fTemp29 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp29)) + 1.584893192 * (fTemp27 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp27)) + fTemp24 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp24))) + 1.2589412 * fTemp23 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp23));
		fVec9[0] = fTemp30;
		fRec27[0] = -(fConst14 * (fConst13 * fRec27[1] - (fTemp30 + fVec9[1])));
		double fTemp31 = fSlow13 * fRec27[0] + fTemp18 + fSlow8 * (4.0 * fTemp19 * (1.0 - std::fabs(fTemp19)) + (-1e-15 - fTemp18)) + fSlow7 * (fTemp16 + 1e-15) + 1e-15;
		fVec10[0] = fTemp31;
		fRec5[0] = -(fConst14 * (fConst13 * fRec5[1] - (fTemp31 + fVec10[1])));
		double fTemp32 = fRec5[0] * fRec4[0];
		fVec11[0] = fTemp32;
		fRec3[0] = 0.9302847925323914 * (fTemp32 + fVec11[1]) - 0.8605695850647829 * fRec3[1];
		fRec2[0] = fRec3[0] - (1.8405051250752198 * fRec2[1] + 0.8612942439318627 * fRec2[2]);
		double fTemp33 = 1.8508996845035413 * fRec2[1];
		double fTemp34 = 0.9254498422517706 * (fRec2[0] + fRec2[2]);
		double fTemp35 = fTemp33 + fTemp34;
		double fTemp36 = fTemp35 / (Ranode(TUBE_TABLE_6V6_250k, fRec1[1]) + 1e+05);
		fVec12[0] = fTemp36;
		fRec45[0] = fConst14 * (8.2e+02 * (fTemp36 + fVec12[1]) - fConst13 * fRec45[1]);
		fRec1[0] = Ftube(TUBE_TABLE_6V6_250k, fTemp34 + fRec45[0] + fTemp33 + -1.130462) + -112.13878048780487;
		double fTemp37 = fRec1[0] - fRec1[1];
		fRec0[0] = fConst8 * (fConst7 * fTemp37 - fConst3 * fRec0[1]);
		fRec46[0] = fConst11 * (fConst10 * fRec46[1] + 0.025 * fTemp37);
		double fTemp38 = fTemp35 / (Ranode(TUBE_TABLE_6V6_68k, fRec48[1]) + 1e+05);
		fVec13[0] = fTemp38;
		fRec49[0] = fConst14 * (8.2e+02 * (fTemp38 + fVec13[1]) - fConst13 * fRec49[1]);
		fRec48[0] = Ftube(TUBE_TABLE_6V6_68k, fTemp34 + fRec49[0] + fTemp33 + -1.13074) + -112.10487804878048;
		double fTemp39 = fRec48[0] - fRec48[1];
		fRec47[0] = fConst8 * (fConst7 * fTemp39 - fConst3 * fRec47[1]);
		fRec50[0] = fConst11 * (fConst10 * fRec50[1] + 0.025 * fTemp39);
		output0[i0] = FAUSTFLOAT(((iSlow0) ? fRec50[0] : fRec47[0]) + ((iSlow0) ? fRec46[0] : fRec0[0]));
		double fTemp40 = double(input1[i0]) * fRec19[0];
		fVec14[0] = fTemp40;
		fRec68[0] = 0.9302847925323914 * (fTemp40 + fVec14[1]) - 0.8605695850647829 * fRec68[1];
		fRec67[0] = fRec68[0] - (1.8405051250752198 * fRec67[1] + 0.8612942439318627 * fRec67[2]);
		double fTemp41 = 1.8508996845035413 * fRec67[1];
		double fTemp42 = 0.9254498422517706 * (fRec67[0] + fRec67[2]);
		double fTemp43 = (fTemp41 + fTemp42) / (Ranode(TUBE_TABLE_12AX7_68k, fRec66[1]) + 1e+05);
		fVec15[0] = fTemp43;
		fRec69[0] = fConst6 * (2.7e+03 * (fTemp43 + fVec15[1]) - fConst5 * fRec69[1]);
		fRec66[0] = Ftube(TUBE_TABLE_12AX7_68k, fTemp42 + fRec69[0] + fTemp41 + -1.581656) + -191.42014814814814;
		double fTemp44 = fRec66[0] - fRec66[1];
		fRec65[0] = fConst8 * (fConst7 * fTemp44 - fConst3 * fRec65[1]);
		fRec70[0] = fConst11 * (fConst10 * fRec70[1] + 0.025 * fTemp44);
		double fTemp45 = ((iSlow2) ? fRec70[0] : fRec65[0]);
		fVec16[0] = fTemp45;
		fRec64[0] = -(fConst14 * (fConst13 * fRec64[1] - (fTemp45 + fVec16[1])));
		fRec63[0] = 0.9302847925323914 * (fRec64[0] + fRec64[1]) - 0.8605695850647829 * fRec63[1];
		fRec62[0] = fRec63[0] - (1.8405051250752198 * fRec62[1] + 0.8612942439318627 * fRec62[2]);
		double fTemp46 = 1.8508996845035413 * fRec62[1];
		double fTemp47 = 0.9254498422517706 * (fRec62[0] + fRec62[2]);
		double fTemp48 = (fTemp46 + fTemp47) / (Ranode(TUBE_TABLE_12AX7_250k, fRec61[1]) + 1e+05);
		fVec17[0] = fTemp48;
		fRec71[0] = fConst17 * (1.5e+03 * (fTemp48 + fVec17[1]) - fConst16 * fRec71[1]);
		fRec61[0] = Ftube(TUBE_TABLE_12AX7_250k, fTemp47 + fRec71[0] + fTemp46 + -1.204285) + -169.71433333333334;
		double fTemp49 = fRec61[0] - fRec61[1];
		fRec60[0] = fConst8 * (fConst7 * fTemp49 - fConst3 * fRec60[1]);
		fRec72[0] = fConst11 * (fConst10 * fRec72[1] + 0.025 * fTemp49);
		double fTemp50 = ((iSlow2) ? fRec72[0] : fRec60[0]);
		fVec18[0] = fTemp50;
		fRec59[0] = 0.9302847925323914 * (fTemp50 + fVec18[1]) - 0.8605695850647829 * fRec59[1];
		fRec58[0] = fRec59[0] - (1.8405051250752198 * fRec58[1] + 0.8612942439318627 * fRec58[2]);
		double fTemp51 = 1.8508996845035413 * fRec58[1];
		double fTemp52 = 0.9254498422517706 * (fRec58[0] + fRec58[2]);
		double fTemp53 = (fTemp51 + fTemp52) / (Ranode(TUBE_TABLE_12AX7_250k, fRec57[1]) + 1e+05);
		fVec19[0] = fTemp53;
		fRec73[0] = fConst20 * (8.2e+02 * (fTemp53 + fVec19[1]) - fConst19 * fRec73[1]);
		fRec57[0] = Ftube(TUBE_TABLE_12AX7_250k, fTemp52 + fRec73[0] + fTemp51 + -0.840703) + -147.47524390243905;
		double fTemp54 = fRec57[0] - fRec57[1];
		fRec56[0] = fConst8 * (fConst7 * fTemp54 - fConst3 * fRec56[1]);
		fRec74[0] = fConst11 * (fConst10 * fRec74[1] + 0.025 * fTemp54);
		double fTemp55 = ((iSlow2) ? fRec74[0] : fRec56[0]);
		double fTemp56 = fRec26[0] * fTemp55;
		double fTemp57 = fTemp17 * fTemp55;
		double fTemp58 = fTemp57 + 1e-15;
		fRec83[0] = fTemp56 + (1e-15 - fConst47 * (fConst45 * fRec83[2] + fConst43 * fRec83[1]));
		double fTemp59 = fRec83[2] + fRec83[0] + 2.0 * fRec83[1];
		fVec20[0] = fTemp59;
		fRec82[0] = -(fConst8 * (fConst3 * fRec82[1] - fConst48 * (fTemp59 - fVec20[1])));
		fRec81[0] = -(fConst50 * (fConst49 * fRec81[1] - (fRec82[0] + fRec82[1])));
		fRec80[0] = fRec81[0] - fConst41 * (fConst39 * fRec80[2] + fConst37 * fRec80[1]);
		double fTemp60 = fRec80[2] + fRec80[0] + 2.0 * fRec80[1];
		fVec21[0] = fTemp60;
		fRec79[0] = -(fConst53 * (fConst51 * fRec79[1] - fConst41 * (fTemp60 + fVec21[1])));
		fRec78[0] = fRec79[0] - fConst34 * (fConst32 * fRec78[2] + fConst30 * fRec78[1]);
		double fTemp61 = fRec78[2] + fRec78[0] + 2.0 * fRec78[1];
		fVec22[0] = fTemp61;
		fRec77[0] = -(fConst56 * (fConst54 * fRec77[1] - fConst34 * (fTemp61 + fVec22[1])));
		fRec76[0] = fRec77[0] - fConst27 * (fConst25 * fRec76[2] + fConst23 * fRec76[1]);
		double fTemp62 = std::max<double>(-1.0, std::min<double>(1.0, fSlow9 * (fRec76[2] + fRec76[0] + 2.0 * fRec76[1])));
		fRec85[0] = -(fConst56 * (fConst54 * fRec85[1] - fConst57 * (fTemp61 - fVec22[1])));
		fRec84[0] = fRec85[0] - fConst27 * (fConst25 * fRec84[2] + fConst23 * fRec84[1]);
		double fTemp63 = std::max<double>(-1.0, std::min<double>(1.0, fSlow10 * (fRec84[2] + (fRec84[0] - 2.0 * fRec84[1]))));
		double fTemp64 = fConst23 * fRec86[1];
		double fTemp65 = fConst30 * fRec87[1];
		fRec89[0] = -(fConst50 * (fConst49 * fRec89[1] - fConst38 * (fRec82[0] - fRec82[1])));
		fRec88[0] = fRec89[0] - fConst41 * (fConst39 * fRec88[2] + fConst37 * fRec88[1]);
		fRec87[0] = fConst63 * (fRec88[2] + (fRec88[0] - 2.0 * fRec88[1])) - fConst62 * (fConst61 * fRec87[2] + fTemp65);
		fRec86[0] = fRec87[2] + fConst62 * (fTemp65 + fConst61 * fRec87[0]) - fConst60 * (fConst59 * fRec86[2] + fTemp64);
		double fTemp66 = std::max<double>(-1.0, std::min<double>(1.0, fSlow11 * (fRec86[2] + fConst60 * (fTemp64 + fConst59 * fRec86[0]))));
		double fTemp67 = fConst23 * fRec90[1];
		fRec92[0] = -(fConst53 * (fConst51 * fRec92[1] - fConst64 * (fTemp60 - fVec21[1])));
		fRec91[0] = fRec92[0] - fConst34 * (fConst32 * fRec91[2] + fConst30 * fRec91[1]);
		fRec90[0] = fConst65 * (fRec91[2] + (fRec91[0] - 2.0 * fRec91[1])) - fConst60 * (fConst59 * fRec90[2] + fTemp67);
		double fTemp68 = std::max<double>(-1.0, std::min<double>(1.0, fSlow12 * (fRec90[2] + fConst60 * (fTemp67 + fConst59 * fRec90[0]))));
		double fTemp69 = 1.333521432 * fTemp68 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp68)) + 1.584893192 * (fTemp66 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp66)) + fTemp63 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp63))) + 1.2589412 * fTemp62 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp62));
		fVec23[0] = fTemp69;
		fRec75[0] = -(fConst14 * (fConst13 * fRec75[1] - (fTemp69 + fVec23[1])));
		double fTemp70 = fSlow13 * fRec75[0] + fTemp57 + fSlow8 * (4.0 * fTemp58 * (1.0 - std::fabs(fTemp58)) + (-1e-15 - fTemp57)) + fSlow7 * (fTemp56 + 1e-15) + 1e-15;
		fVec24[0] = fTemp70;
		fRec55[0] = -(fConst14 * (fConst13 * fRec55[1] - (fTemp70 + fVec24[1])));
		double fTemp71 = fRec4[0] * fRec55[0];
		fVec25[0] = fTemp71;
		fRec54[0] = 0.9302847925323914 * (fTemp71 + fVec25[1]) - 0.8605695850647829 * fRec54[1];
		fRec53[0] = fRec54[0] - (1.8405051250752198 * fRec53[1] + 0.8612942439318627 * fRec53[2]);
		double fTemp72 = 1.8508996845035413 * fRec53[1];
		double fTemp73 = 0.9254498422517706 * (fRec53[0] + fRec53[2]);
		double fTemp74 = fTemp72 + fTemp73;
		double fTemp75 = fTemp74 / (Ranode(TUBE_TABLE_6V6_250k, fRec52[1]) + 1e+05);
		fVec26[0] = fTemp75;
		fRec93[0] = fConst14 * (8.2e+02 * (fTemp75 + fVec26[1]) - fConst13 * fRec93[1]);
		fRec52[0] = Ftube(TUBE_TABLE_6V6_250k, fTemp73 + fRec93[0] + fTemp72 + -1.130462) + -112.13878048780487;
		double fTemp76 = fRec52[0] - fRec52[1];
		fRec51[0] = fConst8 * (fConst7 * fTemp76 - fConst3 * fRec51[1]);
		fRec94[0] = fConst11 * (fConst10 * fRec94[1] + 0.025 * fTemp76);
		double fTemp77 = fTemp74 / (Ranode(TUBE_TABLE_6V6_68k, fRec96[1]) + 1e+05);
		fVec27[0] = fTemp77;
		fRec97[0] = fConst14 * (8.2e+02 * (fTemp77 + fVec27[1]) - fConst13 * fRec97[1]);
		fRec96[0] = Ftube(TUBE_TABLE_6V6_68k, fTemp73 + fRec97[0] + fTemp72 + -1.13074) + -112.10487804878048;
		double fTemp78 = fRec96[0] - fRec96[1];
		fRec95[0] = fConst8 * (fConst7 * fTemp78 - fConst3 * fRec95[1]);
		fRec98[0] = fConst11 * (fConst10 * fRec98[1] + 0.025 * fTemp78);
		output1[i0] = FAUSTFLOAT(((iSlow0) ? fRec98[0] : fRec95[0]) + ((iSlow0) ? fRec94[0] : fRec51[0]));
		fRec4[1] = fRec4[0];
		fRec19[1] = fRec19[0];
		fVec0[1] = fVec0[0];
		fRec18[1] = fRec18[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fVec1[1] = fVec1[0];
		fRec20[1] = fRec20[0];
		fRec16[1] = fRec16[0];
		fRec15[1] = fRec15[0];
		fRec21[1] = fRec21[0];
		fVec2[1] = fVec2[0];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fVec3[1] = fVec3[0];
		fRec22[1] = fRec22[0];
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
		fRec23[1] = fRec23[0];
		fVec4[1] = fVec4[0];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fVec5[1] = fVec5[0];
		fRec24[1] = fRec24[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fRec35[2] = fRec35[1];
		fRec35[1] = fRec35[0];
		fVec6[1] = fVec6[0];
		fRec34[1] = fRec34[0];
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fVec7[1] = fVec7[0];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fVec8[1] = fVec8[0];
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
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
		fVec9[1] = fVec9[0];
		fRec27[1] = fRec27[0];
		fVec10[1] = fVec10[0];
		fRec5[1] = fRec5[0];
		fVec11[1] = fVec11[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fVec12[1] = fVec12[0];
		fRec45[1] = fRec45[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec46[1] = fRec46[0];
		fVec13[1] = fVec13[0];
		fRec49[1] = fRec49[0];
		fRec48[1] = fRec48[0];
		fRec47[1] = fRec47[0];
		fRec50[1] = fRec50[0];
		fVec14[1] = fVec14[0];
		fRec68[1] = fRec68[0];
		fRec67[2] = fRec67[1];
		fRec67[1] = fRec67[0];
		fVec15[1] = fVec15[0];
		fRec69[1] = fRec69[0];
		fRec66[1] = fRec66[0];
		fRec65[1] = fRec65[0];
		fRec70[1] = fRec70[0];
		fVec16[1] = fVec16[0];
		fRec64[1] = fRec64[0];
		fRec63[1] = fRec63[0];
		fRec62[2] = fRec62[1];
		fRec62[1] = fRec62[0];
		fVec17[1] = fVec17[0];
		fRec71[1] = fRec71[0];
		fRec61[1] = fRec61[0];
		fRec60[1] = fRec60[0];
		fRec72[1] = fRec72[0];
		fVec18[1] = fVec18[0];
		fRec59[1] = fRec59[0];
		fRec58[2] = fRec58[1];
		fRec58[1] = fRec58[0];
		fVec19[1] = fVec19[0];
		fRec73[1] = fRec73[0];
		fRec57[1] = fRec57[0];
		fRec56[1] = fRec56[0];
		fRec74[1] = fRec74[0];
		fRec83[2] = fRec83[1];
		fRec83[1] = fRec83[0];
		fVec20[1] = fVec20[0];
		fRec82[1] = fRec82[0];
		fRec81[1] = fRec81[0];
		fRec80[2] = fRec80[1];
		fRec80[1] = fRec80[0];
		fVec21[1] = fVec21[0];
		fRec79[1] = fRec79[0];
		fRec78[2] = fRec78[1];
		fRec78[1] = fRec78[0];
		fVec22[1] = fVec22[0];
		fRec77[1] = fRec77[0];
		fRec76[2] = fRec76[1];
		fRec76[1] = fRec76[0];
		fRec85[1] = fRec85[0];
		fRec84[2] = fRec84[1];
		fRec84[1] = fRec84[0];
		fRec89[1] = fRec89[0];
		fRec88[2] = fRec88[1];
		fRec88[1] = fRec88[0];
		fRec87[2] = fRec87[1];
		fRec87[1] = fRec87[0];
		fRec86[2] = fRec86[1];
		fRec86[1] = fRec86[0];
		fRec92[1] = fRec92[0];
		fRec91[2] = fRec91[1];
		fRec91[1] = fRec91[0];
		fRec90[2] = fRec90[1];
		fRec90[1] = fRec90[0];
		fVec23[1] = fVec23[0];
		fRec75[1] = fRec75[0];
		fVec24[1] = fVec24[0];
		fRec55[1] = fRec55[0];
		fVec25[1] = fVec25[0];
		fRec54[1] = fRec54[0];
		fRec53[2] = fRec53[1];
		fRec53[1] = fRec53[0];
		fVec26[1] = fVec26[0];
		fRec93[1] = fRec93[0];
		fRec52[1] = fRec52[0];
		fRec51[1] = fRec51[0];
		fRec94[1] = fRec94[0];
		fVec27[1] = fVec27[0];
		fRec97[1] = fRec97[0];
		fRec96[1] = fRec96[0];
		fRec95[1] = fRec95[0];
		fRec98[1] = fRec98[0];
	}
#undef fCheckbox0
#undef fVslider0
#undef fCheckbox1
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
		fVslider3_ = (float*)data; // , 0.35, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fVslider2_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
		break;
	case PREGAIN: 
		fVslider1_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
		break;
	case GAIN1: 
		fVslider0_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
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

} // end namespace gxamp5_stereo
