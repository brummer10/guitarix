// generated from file '../src/LV2/faust/gxamp12_stereo.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxamp12_stereo {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
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
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec22[2];
	double fVec0[2];
	double fRec21[2];
	double fRec20[3];
	double fConst24;
	double fConst25;
	double fConst26;
	double fVec1[2];
	double fRec23[2];
	double fRec19[2];
	double fRec18[2];
	double fVec2[2];
	double fRec17[2];
	double fRec16[3];
	double fConst27;
	double fConst28;
	double fConst29;
	double fVec3[2];
	double fRec24[2];
	double fRec15[2];
	double fVec4[2];
	double fRec14[2];
	double fRec13[3];
	double fConst30;
	double fConst31;
	double fConst32;
	double fVec5[2];
	double fRec25[2];
	double fRec12[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec26[2];
	double fConst33;
	double fConst34;
	double fRec11[3];
	double fVec6[2];
	double fConst35;
	double fConst36;
	double fRec10[2];
	double fRec9[2];
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst40;
	double fRec8[3];
	double fVec7[2];
	double fConst41;
	double fConst42;
	double fConst43;
	double fRec7[2];
	double fConst44;
	double fConst45;
	double fRec6[3];
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fRec5[3];
	double fConst56;
	double fRec30[2];
	double fRec29[3];
	double fConst57;
	double fConst58;
	double fConst59;
	double fRec28[3];
	double fRec27[3];
	double fConst60;
	double fConst61;
	double fConst62;
	double fRec34[2];
	double fRec33[3];
	double fVec8[2];
	double fConst63;
	double fConst64;
	double fRec32[2];
	double fConst65;
	double fRec31[3];
	double fConst66;
	double fConst67;
	double fRec36[2];
	double fRec35[3];
	double fVec9[2];
	double fRec4[2];
	double fVec10[2];
	double fRec3[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec37[2];
	double fVec11[2];
	double fRec2[2];
	double fRec1[3];
	double fVec12[2];
	double fRec38[2];
	double fRec0[2];
	double fVec13[2];
	double fRec40[2];
	double fRec39[2];
	double fVec14[2];
	double fRec62[2];
	double fRec61[3];
	double fVec15[2];
	double fRec63[2];
	double fRec60[2];
	double fRec59[2];
	double fVec16[2];
	double fRec58[2];
	double fRec57[3];
	double fVec17[2];
	double fRec64[2];
	double fRec56[2];
	double fVec18[2];
	double fRec55[2];
	double fRec54[3];
	double fVec19[2];
	double fRec65[2];
	double fRec53[2];
	double fRec52[3];
	double fVec20[2];
	double fRec51[2];
	double fRec50[2];
	double fRec49[3];
	double fVec21[2];
	double fRec48[2];
	double fRec47[3];
	double fRec46[3];
	double fRec69[2];
	double fRec68[3];
	double fRec67[3];
	double fRec66[3];
	double fRec73[2];
	double fRec72[3];
	double fVec22[2];
	double fRec71[2];
	double fRec70[3];
	double fRec75[2];
	double fRec74[3];
	double fVec23[2];
	double fRec45[2];
	double fVec24[2];
	double fRec44[2];
	double fVec25[2];
	double fRec43[2];
	double fRec42[3];
	double fVec26[2];
	double fRec76[2];
	double fRec41[2];
	double fVec27[2];
	double fRec78[2];
	double fRec77[2];

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
	id = "pre 6DJ8/ master 6V6";
	name = N_("pre 6DJ8/ master 6V6");
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec22[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fVec0[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec21[l2] = 0.0;
	for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) fRec20[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fVec1[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec23[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec19[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec18[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fVec2[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec17[l9] = 0.0;
	for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) fRec16[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fVec3[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec24[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec15[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fVec4[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec14[l15] = 0.0;
	for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) fRec13[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fVec5[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec25[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec12[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fRec26[l20] = 0.0;
	for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) fRec11[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fVec6[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fRec10[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec9[l24] = 0.0;
	for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) fRec8[l25] = 0.0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fVec7[l26] = 0.0;
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) fRec7[l27] = 0.0;
	for (int l28 = 0; (l28 < 3); l28 = (l28 + 1)) fRec6[l28] = 0.0;
	for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) fRec5[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec30[l30] = 0.0;
	for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) fRec29[l31] = 0.0;
	for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) fRec28[l32] = 0.0;
	for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) fRec27[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec34[l34] = 0.0;
	for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) fRec33[l35] = 0.0;
	for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) fVec8[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fRec32[l37] = 0.0;
	for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) fRec31[l38] = 0.0;
	for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) fRec36[l39] = 0.0;
	for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) fRec35[l40] = 0.0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) fVec9[l41] = 0.0;
	for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) fRec4[l42] = 0.0;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fVec10[l43] = 0.0;
	for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) fRec3[l44] = 0.0;
	for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) fRec37[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fVec11[l46] = 0.0;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) fRec2[l47] = 0.0;
	for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) fRec1[l48] = 0.0;
	for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) fVec12[l49] = 0.0;
	for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) fRec38[l50] = 0.0;
	for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) fRec0[l51] = 0.0;
	for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) fVec13[l52] = 0.0;
	for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) fRec40[l53] = 0.0;
	for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) fRec39[l54] = 0.0;
	for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) fVec14[l55] = 0.0;
	for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) fRec62[l56] = 0.0;
	for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) fRec61[l57] = 0.0;
	for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) fVec15[l58] = 0.0;
	for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) fRec63[l59] = 0.0;
	for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) fRec60[l60] = 0.0;
	for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) fRec59[l61] = 0.0;
	for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) fVec16[l62] = 0.0;
	for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) fRec58[l63] = 0.0;
	for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) fRec57[l64] = 0.0;
	for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) fVec17[l65] = 0.0;
	for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) fRec64[l66] = 0.0;
	for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) fRec56[l67] = 0.0;
	for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) fVec18[l68] = 0.0;
	for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) fRec55[l69] = 0.0;
	for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) fRec54[l70] = 0.0;
	for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) fVec19[l71] = 0.0;
	for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) fRec65[l72] = 0.0;
	for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) fRec53[l73] = 0.0;
	for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) fRec52[l74] = 0.0;
	for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) fVec20[l75] = 0.0;
	for (int l76 = 0; (l76 < 2); l76 = (l76 + 1)) fRec51[l76] = 0.0;
	for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) fRec50[l77] = 0.0;
	for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) fRec49[l78] = 0.0;
	for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) fVec21[l79] = 0.0;
	for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) fRec48[l80] = 0.0;
	for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) fRec47[l81] = 0.0;
	for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) fRec46[l82] = 0.0;
	for (int l83 = 0; (l83 < 2); l83 = (l83 + 1)) fRec69[l83] = 0.0;
	for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) fRec68[l84] = 0.0;
	for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) fRec67[l85] = 0.0;
	for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) fRec66[l86] = 0.0;
	for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) fRec73[l87] = 0.0;
	for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) fRec72[l88] = 0.0;
	for (int l89 = 0; (l89 < 2); l89 = (l89 + 1)) fVec22[l89] = 0.0;
	for (int l90 = 0; (l90 < 2); l90 = (l90 + 1)) fRec71[l90] = 0.0;
	for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) fRec70[l91] = 0.0;
	for (int l92 = 0; (l92 < 2); l92 = (l92 + 1)) fRec75[l92] = 0.0;
	for (int l93 = 0; (l93 < 3); l93 = (l93 + 1)) fRec74[l93] = 0.0;
	for (int l94 = 0; (l94 < 2); l94 = (l94 + 1)) fVec23[l94] = 0.0;
	for (int l95 = 0; (l95 < 2); l95 = (l95 + 1)) fRec45[l95] = 0.0;
	for (int l96 = 0; (l96 < 2); l96 = (l96 + 1)) fVec24[l96] = 0.0;
	for (int l97 = 0; (l97 < 2); l97 = (l97 + 1)) fRec44[l97] = 0.0;
	for (int l98 = 0; (l98 < 2); l98 = (l98 + 1)) fVec25[l98] = 0.0;
	for (int l99 = 0; (l99 < 2); l99 = (l99 + 1)) fRec43[l99] = 0.0;
	for (int l100 = 0; (l100 < 3); l100 = (l100 + 1)) fRec42[l100] = 0.0;
	for (int l101 = 0; (l101 < 2); l101 = (l101 + 1)) fVec26[l101] = 0.0;
	for (int l102 = 0; (l102 < 2); l102 = (l102 + 1)) fRec76[l102] = 0.0;
	for (int l103 = 0; (l103 < 2); l103 = (l103 + 1)) fRec41[l103] = 0.0;
	for (int l104 = 0; (l104 < 2); l104 = (l104 + 1)) fVec27[l104] = 0.0;
	for (int l105 = 0; (l105 < 2); l105 = (l105 + 1)) fRec78[l105] = 0.0;
	for (int l106 = 0; (l106 < 2); l106 = (l106 + 1)) fRec77[l106] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (1.0 / std::tan((20517.741620594938 / fConst0)));
	fConst2 = (1.0 / (fConst1 + 1.0));
	fConst3 = (1.0 - fConst1);
	fConst4 = std::tan((3769.9111843077517 / fConst0));
	fConst5 = (1.0 / fConst4);
	fConst6 = (1.0 / (((fConst5 + 1.0000000000000004) / fConst4) + 1.0));
	fConst7 = mydsp_faustpower2_f(fConst4);
	fConst8 = (1.0 / fConst7);
	fConst9 = std::tan((10053.096491487338 / fConst0));
	fConst10 = (1.0 / fConst9);
	fConst11 = (1.0 / (((fConst10 + 1.0000000000000004) / fConst9) + 1.0));
	fConst12 = (fConst5 + 1.0);
	fConst13 = (1.0 / (fConst4 * fConst12));
	fConst14 = (fConst10 + 1.0);
	fConst15 = (1.0 / fConst14);
	fConst16 = (1.0 - fConst10);
	fConst17 = std::tan((47123.889803846898 / fConst0));
	fConst18 = (1.0 / fConst17);
	fConst19 = (1.0 / (((fConst18 + 1.4142135623730949) / fConst17) + 1.0));
	fConst20 = std::tan((97.389372261283583 / fConst0));
	fConst21 = (1.0 / fConst20);
	fConst22 = (fConst21 + 1.0);
	fConst23 = (1.0 / (fConst20 * fConst22));
	fConst24 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst25 = (1.0 / (fConst24 + 1.0));
	fConst26 = (1.0 - fConst24);
	fConst27 = (1.0 / std::tan((414.69023027385271 / fConst0)));
	fConst28 = (1.0 / (fConst27 + 1.0));
	fConst29 = (1.0 - fConst27);
	fConst30 = (1.0 / std::tan((609.46897479641984 / fConst0)));
	fConst31 = (1.0 / (fConst30 + 1.0));
	fConst32 = (1.0 - fConst30);
	fConst33 = (((fConst18 + -1.4142135623730949) / fConst17) + 1.0);
	fConst34 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst17))));
	fConst35 = (0.0 - fConst23);
	fConst36 = ((1.0 - fConst21) / fConst22);
	fConst37 = (((fConst10 + -1.0000000000000004) / fConst9) + 1.0);
	fConst38 = mydsp_faustpower2_f(fConst9);
	fConst39 = (1.0 / fConst38);
	fConst40 = (2.0 * (1.0 - fConst39));
	fConst41 = (0.0 - fConst13);
	fConst42 = (1.0 - fConst5);
	fConst43 = (fConst42 / fConst12);
	fConst44 = (((fConst5 + -1.0000000000000004) / fConst4) + 1.0);
	fConst45 = (2.0 * (1.0 - fConst8));
	fConst46 = (0.0 - (2.0 / fConst7));
	fConst47 = std::tan((942.47779607693792 / fConst0));
	fConst48 = (1.0 / fConst47);
	fConst49 = (fConst48 + 1.0);
	fConst50 = (1.0 / ((fConst49 / fConst47) + 1.0));
	fConst51 = (1.0 - fConst48);
	fConst52 = (1.0 - (fConst51 / fConst47));
	fConst53 = mydsp_faustpower2_f(fConst47);
	fConst54 = (1.0 / fConst53);
	fConst55 = (2.0 * (1.0 - fConst54));
	fConst56 = (0.0 - (1.0 / (fConst9 * fConst14)));
	fConst57 = (0.0 - (2.0 / fConst38));
	fConst58 = (1.0 / ((fConst12 / fConst4) + 1.0));
	fConst59 = (1.0 - (fConst42 / fConst4));
	fConst60 = (1.0 / (((fConst48 + 1.0000000000000004) / fConst47) + 1.0));
	fConst61 = (1.0 / (fConst47 * fConst49));
	fConst62 = (1.0 / fConst12);
	fConst63 = (0.0 - fConst61);
	fConst64 = (fConst51 / fConst49);
	fConst65 = (((fConst48 + -1.0000000000000004) / fConst47) + 1.0);
	fConst66 = (0.0 - (2.0 / fConst53));
	fConst67 = (1.0 / fConst49);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	double fSlow0 = double(fVslider0);
	double fSlow1 = (2.0 * (fSlow0 + -0.5));
	double fSlow2 = (1.0 - std::max<double>(0.0, (-1.0 * fSlow1)));
	double fSlow3 = std::pow(10.0, (1.2 * fSlow0));
	double fSlow4 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider1))));
	double fSlow5 = (1.0000000000000009e-05 * double(fVslider2));
	double fSlow6 = std::pow(10.0, (0.80000000000000004 * fSlow0));
	double fSlow7 = (fConst60 * std::pow(10.0, (2.0 * fSlow0)));
	double fSlow8 = (fConst60 * std::pow(10.0, (0.90000000000000002 * fSlow0)));
	double fSlow9 = (1.25 * fSlow0);
	double fSlow10 = (1.0 - std::max<double>(0.0, fSlow1));
	double fSlow11 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider3))));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec22[0] = (fSlow4 + (0.999 * fRec22[1]));
		double fTemp0 = ((double(input0[i]) * fRec22[0]) + 1.0000000000000001e-15);
		fVec0[0] = fTemp0;
		fRec21[0] = ((0.93028479253239138 * (fTemp0 + fVec0[1])) - (0.86056958506478287 * fRec21[1]));
		fRec20[0] = (fRec21[0] - ((1.8405051250752198 * fRec20[1]) + (0.86129424393186271 * fRec20[2])));
		double fTemp1 = ((0.027 * fRec19[1]) + 1.0000000000000001e-15);
		fVec1[0] = fTemp1;
		fRec23[0] = (0.0 - (fConst25 * ((fConst26 * fRec23[1]) - (fTemp1 + fVec1[1]))));
		fRec19[0] = (double(Ftube(int(TUBE_TABLE_6DJ8_68k), double((((0.92544984225177063 * (fRec20[0] + fRec20[2])) + (fRec23[0] + (1.8508996845035413 * fRec20[1]))) + -1.8639460000000001)))) + -60.964962962962957);
		fRec18[0] = (fConst2 * ((0.050000000000000003 * (fRec19[0] + fRec19[1])) - (fConst3 * fRec18[1])));
		double fTemp2 = (fRec18[0] + 1.0000000000000001e-15);
		fVec2[0] = fTemp2;
		fRec17[0] = ((0.93028479253239138 * (fTemp2 + fVec2[1])) - (0.86056958506478287 * fRec17[1]));
		fRec16[0] = (fRec17[0] - ((1.8405051250752198 * fRec16[1]) + (0.86129424393186271 * fRec16[2])));
		double fTemp3 = ((0.014999999999999999 * fRec15[1]) + 1.0000000000000001e-15);
		fVec3[0] = fTemp3;
		fRec24[0] = (0.0 - (fConst28 * ((fConst29 * fRec24[1]) - (fTemp3 + fVec3[1]))));
		fRec15[0] = (double(Ftube(int(TUBE_TABLE_6DJ8_250k), double((((0.92544984225177063 * (fRec16[0] + fRec16[2])) + (fRec24[0] + (1.8508996845035413 * fRec16[1]))) + -1.271609)))) + -45.226066666666668);
		double fTemp4 = ((0.050000000000000003 * fRec15[0]) + 1.0000000000000001e-15);
		fVec4[0] = fTemp4;
		fRec14[0] = ((0.93028479253239138 * (fTemp4 + fVec4[1])) - (0.86056958506478287 * fRec14[1]));
		fRec13[0] = (fRec14[0] - ((1.8405051250752198 * fRec13[1]) + (0.86129424393186271 * fRec13[2])));
		double fTemp5 = ((0.0082000000000000007 * fRec12[1]) + 1.0000000000000001e-15);
		fVec5[0] = fTemp5;
		fRec25[0] = (0.0 - (fConst31 * ((fConst32 * fRec25[1]) - (fTemp5 + fVec5[1]))));
		fRec12[0] = (double(Ftube(int(TUBE_TABLE_6DJ8_250k), double((((0.92544984225177063 * (fRec13[0] + fRec13[2])) + (fRec25[0] + (1.8508996845035413 * fRec13[1]))) + -0.79704299999999995)))) + -32.799634146341475);
		fRec26[0] = (fSlow5 + (0.999 * fRec26[1]));
		double fTemp6 = (0.050000000000000003 * (fRec12[0] * fRec26[0]));
		fRec11[0] = (fTemp6 + (1.0000000000000001e-15 - (fConst19 * ((fConst33 * fRec11[2]) + (fConst34 * fRec11[1])))));
		double fTemp7 = (fRec11[2] + (fRec11[0] + (2.0 * fRec11[1])));
		fVec6[0] = fTemp7;
		fRec10[0] = ((fConst19 * ((fConst23 * fTemp7) + (fConst35 * fVec6[1]))) - (fConst36 * fRec10[1]));
		fRec9[0] = (0.0 - (fConst15 * ((fConst16 * fRec9[1]) - (fRec10[0] + fRec10[1]))));
		fRec8[0] = (fRec9[0] - (fConst11 * ((fConst37 * fRec8[2]) + (fConst40 * fRec8[1]))));
		double fTemp8 = (fRec8[2] + (fRec8[0] + (2.0 * fRec8[1])));
		fVec7[0] = fTemp8;
		fRec7[0] = ((fConst11 * ((fConst13 * fTemp8) + (fConst41 * fVec7[1]))) - (fConst43 * fRec7[1]));
		fRec6[0] = (fRec7[0] - (fConst6 * ((fConst44 * fRec6[2]) + (fConst45 * fRec6[1]))));
		double fTemp9 = (fConst55 * fRec5[1]);
		fRec5[0] = ((fConst6 * (((fConst8 * fRec6[0]) + (fConst46 * fRec6[1])) + (fConst8 * fRec6[2]))) - (fConst50 * ((fConst52 * fRec5[2]) + fTemp9)));
		double fTemp10 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow3 * (fRec5[2] + (fConst50 * (fTemp9 + (fConst52 * fRec5[0])))))));
		fRec30[0] = ((fConst56 * fRec10[1]) - (fConst15 * ((fConst16 * fRec30[1]) - (fConst10 * fRec10[0]))));
		fRec29[0] = (fRec30[0] - (fConst11 * ((fConst37 * fRec29[2]) + (fConst40 * fRec29[1]))));
		double fTemp11 = (fConst45 * fRec28[1]);
		fRec28[0] = ((fConst11 * (((fConst39 * fRec29[0]) + (fConst57 * fRec29[1])) + (fConst39 * fRec29[2]))) - (fConst58 * ((fConst59 * fRec28[2]) + fTemp11)));
		double fTemp12 = (fConst55 * fRec27[1]);
		fRec27[0] = ((fRec28[2] + (fConst58 * (fTemp11 + (fConst59 * fRec28[0])))) - (fConst50 * ((fConst52 * fRec27[2]) + fTemp12)));
		double fTemp13 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow6 * (fRec27[2] + (fConst50 * (fTemp12 + (fConst52 * fRec27[0])))))));
		fRec34[0] = (0.0 - (fConst62 * ((fConst42 * fRec34[1]) - (fConst11 * (fTemp8 + fVec7[1])))));
		fRec33[0] = (fRec34[0] - (fConst6 * ((fConst44 * fRec33[2]) + (fConst45 * fRec33[1]))));
		double fTemp14 = (fRec33[2] + (fRec33[0] + (2.0 * fRec33[1])));
		fVec8[0] = fTemp14;
		fRec32[0] = ((fConst6 * ((fConst61 * fTemp14) + (fConst63 * fVec8[1]))) - (fConst64 * fRec32[1]));
		fRec31[0] = (fRec32[0] - (fConst60 * ((fConst65 * fRec31[2]) + (fConst55 * fRec31[1]))));
		double fTemp15 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow7 * (((fConst54 * fRec31[0]) + (fConst66 * fRec31[1])) + (fConst54 * fRec31[2])))));
		fRec36[0] = (0.0 - (fConst67 * ((fConst51 * fRec36[1]) - (fConst6 * (fTemp14 + fVec8[1])))));
		fRec35[0] = (fRec36[0] - (fConst60 * ((fConst65 * fRec35[2]) + (fConst55 * fRec35[1]))));
		double fTemp16 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow8 * (fRec35[2] + (fRec35[0] + (2.0 * fRec35[1]))))));
		double fTemp17 = (((1.333521432 * (fTemp10 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp10))))) + (1.584893192 * ((fTemp13 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp13)))) + (fTemp15 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp15))))))) + (1.2589412 * (fTemp16 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp16))))));
		fVec9[0] = fTemp17;
		fRec4[0] = (0.0 - (fConst2 * ((fConst3 * fRec4[1]) - (fTemp17 + fVec9[1]))));
		double fTemp18 = (1.0 - fRec26[0]);
		double fTemp19 = (0.050000000000000003 * (fRec12[0] * fTemp18));
		double fTemp20 = (fTemp19 + 1.0000000000000001e-15);
		double fTemp21 = (((fSlow2 * fRec4[0]) + ((fTemp19 + (fSlow9 * ((4.0 * (fTemp20 * (1.0 - std::fabs(fTemp20)))) + (-1.0000000000000001e-15 - fTemp19)))) + (fSlow10 * (fTemp6 + 1.0000000000000001e-15)))) + 1.0000000000000001e-15);
		fVec10[0] = fTemp21;
		fRec3[0] = (0.0 - (fConst2 * ((fConst3 * fRec3[1]) - (fTemp21 + fVec10[1]))));
		fRec37[0] = (fSlow11 + (0.999 * fRec37[1]));
		double fTemp22 = ((fRec3[0] * fRec37[0]) + 1.0000000000000001e-15);
		fVec11[0] = fTemp22;
		fRec2[0] = ((0.93028479253239138 * (fTemp22 + fVec11[1])) - (0.86056958506478287 * fRec2[1]));
		fRec1[0] = (fRec2[0] - ((1.8405051250752198 * fRec1[1]) + (0.86129424393186271 * fRec1[2])));
		double fTemp23 = (0.92544984225177063 * (fRec1[0] + fRec1[2]));
		double fTemp24 = ((0.0082000000000000007 * fRec0[1]) + 1.0000000000000001e-15);
		fVec12[0] = fTemp24;
		fRec38[0] = (0.0 - (fConst2 * ((fConst3 * fRec38[1]) - (fTemp24 + fVec12[1]))));
		double fTemp25 = (1.8508996845035413 * fRec1[1]);
		fRec0[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double(((fTemp23 + (fRec38[0] + fTemp25)) + -1.1304620000000001)))) + -112.13878048780487);
		double fTemp26 = ((0.0082000000000000007 * fRec39[1]) + 1.0000000000000001e-15);
		fVec13[0] = fTemp26;
		fRec40[0] = (0.0 - (fConst2 * ((fConst3 * fRec40[1]) - (fTemp26 + fVec13[1]))));
		fRec39[0] = (double(Ftube(int(TUBE_TABLE_6V6_68k), double(((fTemp23 + (fRec40[0] + fTemp25)) + -1.1307400000000001)))) + -112.10487804878048);
		output0[i] = FAUSTFLOAT((0.025000000000000001 * (fRec0[0] + fRec39[0])));
		double fTemp27 = ((double(input1[i]) * fRec22[0]) + 1.0000000000000001e-15);
		fVec14[0] = fTemp27;
		fRec62[0] = ((0.93028479253239138 * (fTemp27 + fVec14[1])) - (0.86056958506478287 * fRec62[1]));
		fRec61[0] = (fRec62[0] - ((1.8405051250752198 * fRec61[1]) + (0.86129424393186271 * fRec61[2])));
		double fTemp28 = ((0.027 * fRec60[1]) + 1.0000000000000001e-15);
		fVec15[0] = fTemp28;
		fRec63[0] = (0.0 - (fConst25 * ((fConst26 * fRec63[1]) - (fTemp28 + fVec15[1]))));
		fRec60[0] = (double(Ftube(int(TUBE_TABLE_6DJ8_68k), double((((0.92544984225177063 * (fRec61[0] + fRec61[2])) + (fRec63[0] + (1.8508996845035413 * fRec61[1]))) + -1.8639460000000001)))) + -60.964962962962957);
		fRec59[0] = (fConst2 * ((0.050000000000000003 * (fRec60[0] + fRec60[1])) - (fConst3 * fRec59[1])));
		double fTemp29 = (fRec59[0] + 1.0000000000000001e-15);
		fVec16[0] = fTemp29;
		fRec58[0] = ((0.93028479253239138 * (fTemp29 + fVec16[1])) - (0.86056958506478287 * fRec58[1]));
		fRec57[0] = (fRec58[0] - ((1.8405051250752198 * fRec57[1]) + (0.86129424393186271 * fRec57[2])));
		double fTemp30 = ((0.014999999999999999 * fRec56[1]) + 1.0000000000000001e-15);
		fVec17[0] = fTemp30;
		fRec64[0] = (0.0 - (fConst28 * ((fConst29 * fRec64[1]) - (fTemp30 + fVec17[1]))));
		fRec56[0] = (double(Ftube(int(TUBE_TABLE_6DJ8_250k), double((((0.92544984225177063 * (fRec57[0] + fRec57[2])) + (fRec64[0] + (1.8508996845035413 * fRec57[1]))) + -1.271609)))) + -45.226066666666668);
		double fTemp31 = ((0.050000000000000003 * fRec56[0]) + 1.0000000000000001e-15);
		fVec18[0] = fTemp31;
		fRec55[0] = ((0.93028479253239138 * (fTemp31 + fVec18[1])) - (0.86056958506478287 * fRec55[1]));
		fRec54[0] = (fRec55[0] - ((1.8405051250752198 * fRec54[1]) + (0.86129424393186271 * fRec54[2])));
		double fTemp32 = ((0.0082000000000000007 * fRec53[1]) + 1.0000000000000001e-15);
		fVec19[0] = fTemp32;
		fRec65[0] = (0.0 - (fConst31 * ((fConst32 * fRec65[1]) - (fTemp32 + fVec19[1]))));
		fRec53[0] = (double(Ftube(int(TUBE_TABLE_6DJ8_250k), double((((0.92544984225177063 * (fRec54[0] + fRec54[2])) + (fRec65[0] + (1.8508996845035413 * fRec54[1]))) + -0.79704299999999995)))) + -32.799634146341475);
		double fTemp33 = (0.050000000000000003 * (fRec26[0] * fRec53[0]));
		fRec52[0] = (fTemp33 + (1.0000000000000001e-15 - (fConst19 * ((fConst33 * fRec52[2]) + (fConst34 * fRec52[1])))));
		double fTemp34 = (fRec52[2] + (fRec52[0] + (2.0 * fRec52[1])));
		fVec20[0] = fTemp34;
		fRec51[0] = ((fConst19 * ((fConst23 * fTemp34) + (fConst35 * fVec20[1]))) - (fConst36 * fRec51[1]));
		fRec50[0] = (0.0 - (fConst15 * ((fConst16 * fRec50[1]) - (fRec51[0] + fRec51[1]))));
		fRec49[0] = (fRec50[0] - (fConst11 * ((fConst37 * fRec49[2]) + (fConst40 * fRec49[1]))));
		double fTemp35 = (fRec49[2] + (fRec49[0] + (2.0 * fRec49[1])));
		fVec21[0] = fTemp35;
		fRec48[0] = ((fConst11 * ((fConst13 * fTemp35) + (fConst41 * fVec21[1]))) - (fConst43 * fRec48[1]));
		fRec47[0] = (fRec48[0] - (fConst6 * ((fConst44 * fRec47[2]) + (fConst45 * fRec47[1]))));
		double fTemp36 = (fConst55 * fRec46[1]);
		fRec46[0] = ((fConst6 * (((fConst8 * fRec47[0]) + (fConst46 * fRec47[1])) + (fConst8 * fRec47[2]))) - (fConst50 * ((fConst52 * fRec46[2]) + fTemp36)));
		double fTemp37 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow3 * (fRec46[2] + (fConst50 * (fTemp36 + (fConst52 * fRec46[0])))))));
		fRec69[0] = ((fConst56 * fRec51[1]) - (fConst15 * ((fConst16 * fRec69[1]) - (fConst10 * fRec51[0]))));
		fRec68[0] = (fRec69[0] - (fConst11 * ((fConst37 * fRec68[2]) + (fConst40 * fRec68[1]))));
		double fTemp38 = (fConst45 * fRec67[1]);
		fRec67[0] = ((fConst11 * (((fConst39 * fRec68[0]) + (fConst57 * fRec68[1])) + (fConst39 * fRec68[2]))) - (fConst58 * ((fConst59 * fRec67[2]) + fTemp38)));
		double fTemp39 = (fConst55 * fRec66[1]);
		fRec66[0] = ((fRec67[2] + (fConst58 * (fTemp38 + (fConst59 * fRec67[0])))) - (fConst50 * ((fConst52 * fRec66[2]) + fTemp39)));
		double fTemp40 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow6 * (fRec66[2] + (fConst50 * (fTemp39 + (fConst52 * fRec66[0])))))));
		fRec73[0] = (0.0 - (fConst62 * ((fConst42 * fRec73[1]) - (fConst11 * (fTemp35 + fVec21[1])))));
		fRec72[0] = (fRec73[0] - (fConst6 * ((fConst44 * fRec72[2]) + (fConst45 * fRec72[1]))));
		double fTemp41 = (fRec72[2] + (fRec72[0] + (2.0 * fRec72[1])));
		fVec22[0] = fTemp41;
		fRec71[0] = ((fConst6 * ((fConst61 * fTemp41) + (fConst63 * fVec22[1]))) - (fConst64 * fRec71[1]));
		fRec70[0] = (fRec71[0] - (fConst60 * ((fConst65 * fRec70[2]) + (fConst55 * fRec70[1]))));
		double fTemp42 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow7 * (((fConst54 * fRec70[0]) + (fConst66 * fRec70[1])) + (fConst54 * fRec70[2])))));
		fRec75[0] = (0.0 - (fConst67 * ((fConst51 * fRec75[1]) - (fConst6 * (fTemp41 + fVec22[1])))));
		fRec74[0] = (fRec75[0] - (fConst60 * ((fConst65 * fRec74[2]) + (fConst55 * fRec74[1]))));
		double fTemp43 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow8 * (fRec74[2] + (fRec74[0] + (2.0 * fRec74[1]))))));
		double fTemp44 = (((1.333521432 * (fTemp37 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp37))))) + (1.584893192 * ((fTemp40 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp40)))) + (fTemp42 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp42))))))) + (1.2589412 * (fTemp43 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp43))))));
		fVec23[0] = fTemp44;
		fRec45[0] = (0.0 - (fConst2 * ((fConst3 * fRec45[1]) - (fTemp44 + fVec23[1]))));
		double fTemp45 = (0.050000000000000003 * (fRec53[0] * fTemp18));
		double fTemp46 = (fTemp45 + 1.0000000000000001e-15);
		double fTemp47 = (((fSlow2 * fRec45[0]) + ((fTemp45 + (fSlow9 * ((4.0 * (fTemp46 * (1.0 - std::fabs(fTemp46)))) + (-1.0000000000000001e-15 - fTemp45)))) + (fSlow10 * (fTemp33 + 1.0000000000000001e-15)))) + 1.0000000000000001e-15);
		fVec24[0] = fTemp47;
		fRec44[0] = (0.0 - (fConst2 * ((fConst3 * fRec44[1]) - (fTemp47 + fVec24[1]))));
		double fTemp48 = ((fRec37[0] * fRec44[0]) + 1.0000000000000001e-15);
		fVec25[0] = fTemp48;
		fRec43[0] = ((0.93028479253239138 * (fTemp48 + fVec25[1])) - (0.86056958506478287 * fRec43[1]));
		fRec42[0] = (fRec43[0] - ((1.8405051250752198 * fRec42[1]) + (0.86129424393186271 * fRec42[2])));
		double fTemp49 = (0.92544984225177063 * (fRec42[0] + fRec42[2]));
		double fTemp50 = ((0.0082000000000000007 * fRec41[1]) + 1.0000000000000001e-15);
		fVec26[0] = fTemp50;
		fRec76[0] = (0.0 - (fConst2 * ((fConst3 * fRec76[1]) - (fTemp50 + fVec26[1]))));
		double fTemp51 = (1.8508996845035413 * fRec42[1]);
		fRec41[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double(((fTemp49 + (fRec76[0] + fTemp51)) + -1.1304620000000001)))) + -112.13878048780487);
		double fTemp52 = ((0.0082000000000000007 * fRec77[1]) + 1.0000000000000001e-15);
		fVec27[0] = fTemp52;
		fRec78[0] = (0.0 - (fConst2 * ((fConst3 * fRec78[1]) - (fTemp52 + fVec27[1]))));
		fRec77[0] = (double(Ftube(int(TUBE_TABLE_6V6_68k), double(((fTemp49 + (fRec78[0] + fTemp51)) + -1.1307400000000001)))) + -112.10487804878048);
		output1[i] = FAUSTFLOAT((0.025000000000000001 * (fRec41[0] + fRec77[0])));
		fRec22[1] = fRec22[0];
		fVec0[1] = fVec0[0];
		fRec21[1] = fRec21[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fVec1[1] = fVec1[0];
		fRec23[1] = fRec23[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fVec2[1] = fVec2[0];
		fRec17[1] = fRec17[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fVec3[1] = fVec3[0];
		fRec24[1] = fRec24[0];
		fRec15[1] = fRec15[0];
		fVec4[1] = fVec4[0];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fVec5[1] = fVec5[0];
		fRec25[1] = fRec25[0];
		fRec12[1] = fRec12[0];
		fRec26[1] = fRec26[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fVec6[1] = fVec6[0];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fVec7[1] = fVec7[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec30[1] = fRec30[0];
		fRec29[2] = fRec29[1];
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fVec8[1] = fVec8[0];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fRec36[1] = fRec36[0];
		fRec35[2] = fRec35[1];
		fRec35[1] = fRec35[0];
		fVec9[1] = fVec9[0];
		fRec4[1] = fRec4[0];
		fVec10[1] = fVec10[0];
		fRec3[1] = fRec3[0];
		fRec37[1] = fRec37[0];
		fVec11[1] = fVec11[0];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fVec12[1] = fVec12[0];
		fRec38[1] = fRec38[0];
		fRec0[1] = fRec0[0];
		fVec13[1] = fVec13[0];
		fRec40[1] = fRec40[0];
		fRec39[1] = fRec39[0];
		fVec14[1] = fVec14[0];
		fRec62[1] = fRec62[0];
		fRec61[2] = fRec61[1];
		fRec61[1] = fRec61[0];
		fVec15[1] = fVec15[0];
		fRec63[1] = fRec63[0];
		fRec60[1] = fRec60[0];
		fRec59[1] = fRec59[0];
		fVec16[1] = fVec16[0];
		fRec58[1] = fRec58[0];
		fRec57[2] = fRec57[1];
		fRec57[1] = fRec57[0];
		fVec17[1] = fVec17[0];
		fRec64[1] = fRec64[0];
		fRec56[1] = fRec56[0];
		fVec18[1] = fVec18[0];
		fRec55[1] = fRec55[0];
		fRec54[2] = fRec54[1];
		fRec54[1] = fRec54[0];
		fVec19[1] = fVec19[0];
		fRec65[1] = fRec65[0];
		fRec53[1] = fRec53[0];
		fRec52[2] = fRec52[1];
		fRec52[1] = fRec52[0];
		fVec20[1] = fVec20[0];
		fRec51[1] = fRec51[0];
		fRec50[1] = fRec50[0];
		fRec49[2] = fRec49[1];
		fRec49[1] = fRec49[0];
		fVec21[1] = fVec21[0];
		fRec48[1] = fRec48[0];
		fRec47[2] = fRec47[1];
		fRec47[1] = fRec47[0];
		fRec46[2] = fRec46[1];
		fRec46[1] = fRec46[0];
		fRec69[1] = fRec69[0];
		fRec68[2] = fRec68[1];
		fRec68[1] = fRec68[0];
		fRec67[2] = fRec67[1];
		fRec67[1] = fRec67[0];
		fRec66[2] = fRec66[1];
		fRec66[1] = fRec66[0];
		fRec73[1] = fRec73[0];
		fRec72[2] = fRec72[1];
		fRec72[1] = fRec72[0];
		fVec22[1] = fVec22[0];
		fRec71[1] = fRec71[0];
		fRec70[2] = fRec70[1];
		fRec70[1] = fRec70[0];
		fRec75[1] = fRec75[0];
		fRec74[2] = fRec74[1];
		fRec74[1] = fRec74[0];
		fVec23[1] = fVec23[0];
		fRec45[1] = fRec45[0];
		fVec24[1] = fVec24[0];
		fRec44[1] = fRec44[0];
		fVec25[1] = fVec25[0];
		fRec43[1] = fRec43[0];
		fRec42[2] = fRec42[1];
		fRec42[1] = fRec42[0];
		fVec26[1] = fVec26[0];
		fRec76[1] = fRec76[0];
		fRec41[1] = fRec41[0];
		fVec27[1] = fVec27[0];
		fRec78[1] = fRec78[0];
		fRec77[1] = fRec77[0];
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
		fVslider0_ = (float*)data; // , 0.34999999999999998, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fVslider2_ = (float*)data; // , 100.0, 0.0, 100.0, 1.0 
		break;
	case PREGAIN: 
		fVslider1_ = (float*)data; // , -6.0, -20.0, 20.0, 0.10000000000000001 
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

} // end namespace gxamp12_stereo
