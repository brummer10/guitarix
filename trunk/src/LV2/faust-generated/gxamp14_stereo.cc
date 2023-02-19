// generated from file '../src/LV2/faust/gxamp14_stereo.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxamp14_stereo {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst4;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec14[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst7;
	double fConst8;
	double fConst10;
	double fConst11;
	double fConst14;
	double fConst15;
	double fConst17;
	double fConst18;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst27;
	double fConst29;
	double fConst30;
	double fRec23[3];
	double fVec0[2];
	double fConst31;
	double fConst32;
	double fRec22[2];
	double fConst33;
	double fConst35;
	double fRec21[2];
	double fRec20[3];
	double fVec1[2];
	double fConst36;
	double fConst38;
	double fRec19[2];
	double fRec18[3];
	double fVec2[2];
	double fConst39;
	double fConst41;
	double fRec17[2];
	double fRec16[3];
	double fConst42;
	double fConst43;
	double fConst44;
	double fRec25[2];
	double fRec24[3];
	double fConst45;
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fRec29[2];
	double fRec28[3];
	double fConst51;
	double fRec27[3];
	double fRec26[3];
	double fConst52;
	double fConst53;
	double fConst54;
	double fRec32[2];
	double fRec31[3];
	double fConst55;
	double fRec30[3];
	double fVec3[2];
	double fConst57;
	double fConst58;
	double fRec15[2];
	double fVec4[2];
	double fRec13[2];
	double fRec12[3];
	double fConst60;
	double fVec5[2];
	double fConst61;
	double fRec33[2];
	double fRec11[2];
	double fRec10[2];
	double fConst63;
	double fConst64;
	double fRec34[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec35[2];
	double fVec6[2];
	double fRec9[2];
	double fRec8[2];
	double fRec7[3];
	double fConst66;
	double fVec7[2];
	double fConst67;
	double fRec36[2];
	double fRec6[2];
	double fRec5[2];
	double fRec37[2];
	double fVec8[2];
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fConst69;
	double fVec9[2];
	double fConst70;
	double fRec38[2];
	double fRec1[2];
	double fRec0[2];
	double fRec39[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec40[2];
	double fRec63[3];
	double fVec10[2];
	double fRec62[2];
	double fRec61[2];
	double fRec60[3];
	double fVec11[2];
	double fRec59[2];
	double fRec58[3];
	double fVec12[2];
	double fRec57[2];
	double fRec56[3];
	double fRec65[2];
	double fRec64[3];
	double fRec69[2];
	double fRec68[3];
	double fRec67[3];
	double fRec66[3];
	double fRec72[2];
	double fRec71[3];
	double fRec70[3];
	double fVec13[2];
	double fRec55[2];
	double fVec14[2];
	double fRec54[2];
	double fRec53[3];
	double fVec15[2];
	double fRec73[2];
	double fRec52[2];
	double fRec51[2];
	double fRec74[2];
	double fVec16[2];
	double fRec50[2];
	double fRec49[2];
	double fRec48[3];
	double fVec17[2];
	double fRec75[2];
	double fRec47[2];
	double fRec46[2];
	double fRec76[2];
	double fVec18[2];
	double fRec45[2];
	double fRec44[2];
	double fRec43[3];
	double fVec19[2];
	double fRec77[2];
	double fRec42[2];
	double fRec41[2];
	double fRec78[2];

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
	id = "12AT7";
	name = N_("12AT7");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec14[l0] = 0.0;
	for (int l1 = 0; l1 < 3; l1 = l1 + 1) fRec23[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fVec0[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec22[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec21[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec20[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fVec1[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec19[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec18[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fVec2[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec17[l10] = 0.0;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec16[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec25[l12] = 0.0;
	for (int l13 = 0; l13 < 3; l13 = l13 + 1) fRec24[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec29[l14] = 0.0;
	for (int l15 = 0; l15 < 3; l15 = l15 + 1) fRec28[l15] = 0.0;
	for (int l16 = 0; l16 < 3; l16 = l16 + 1) fRec27[l16] = 0.0;
	for (int l17 = 0; l17 < 3; l17 = l17 + 1) fRec26[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec32[l18] = 0.0;
	for (int l19 = 0; l19 < 3; l19 = l19 + 1) fRec31[l19] = 0.0;
	for (int l20 = 0; l20 < 3; l20 = l20 + 1) fRec30[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fVec3[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec15[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fVec4[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec13[l24] = 0.0;
	for (int l25 = 0; l25 < 3; l25 = l25 + 1) fRec12[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fVec5[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec33[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec11[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec10[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec34[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec35[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fVec6[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fRec9[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fRec8[l34] = 0.0;
	for (int l35 = 0; l35 < 3; l35 = l35 + 1) fRec7[l35] = 0.0;
	for (int l36 = 0; l36 < 2; l36 = l36 + 1) fVec7[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec36[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fRec6[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec5[l39] = 0.0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec37[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fVec8[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) fRec4[l42] = 0.0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fRec3[l43] = 0.0;
	for (int l44 = 0; l44 < 3; l44 = l44 + 1) fRec2[l44] = 0.0;
	for (int l45 = 0; l45 < 2; l45 = l45 + 1) fVec9[l45] = 0.0;
	for (int l46 = 0; l46 < 2; l46 = l46 + 1) fRec38[l46] = 0.0;
	for (int l47 = 0; l47 < 2; l47 = l47 + 1) fRec1[l47] = 0.0;
	for (int l48 = 0; l48 < 2; l48 = l48 + 1) fRec0[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec39[l49] = 0.0;
	for (int l50 = 0; l50 < 2; l50 = l50 + 1) fRec40[l50] = 0.0;
	for (int l51 = 0; l51 < 3; l51 = l51 + 1) fRec63[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fVec10[l52] = 0.0;
	for (int l53 = 0; l53 < 2; l53 = l53 + 1) fRec62[l53] = 0.0;
	for (int l54 = 0; l54 < 2; l54 = l54 + 1) fRec61[l54] = 0.0;
	for (int l55 = 0; l55 < 3; l55 = l55 + 1) fRec60[l55] = 0.0;
	for (int l56 = 0; l56 < 2; l56 = l56 + 1) fVec11[l56] = 0.0;
	for (int l57 = 0; l57 < 2; l57 = l57 + 1) fRec59[l57] = 0.0;
	for (int l58 = 0; l58 < 3; l58 = l58 + 1) fRec58[l58] = 0.0;
	for (int l59 = 0; l59 < 2; l59 = l59 + 1) fVec12[l59] = 0.0;
	for (int l60 = 0; l60 < 2; l60 = l60 + 1) fRec57[l60] = 0.0;
	for (int l61 = 0; l61 < 3; l61 = l61 + 1) fRec56[l61] = 0.0;
	for (int l62 = 0; l62 < 2; l62 = l62 + 1) fRec65[l62] = 0.0;
	for (int l63 = 0; l63 < 3; l63 = l63 + 1) fRec64[l63] = 0.0;
	for (int l64 = 0; l64 < 2; l64 = l64 + 1) fRec69[l64] = 0.0;
	for (int l65 = 0; l65 < 3; l65 = l65 + 1) fRec68[l65] = 0.0;
	for (int l66 = 0; l66 < 3; l66 = l66 + 1) fRec67[l66] = 0.0;
	for (int l67 = 0; l67 < 3; l67 = l67 + 1) fRec66[l67] = 0.0;
	for (int l68 = 0; l68 < 2; l68 = l68 + 1) fRec72[l68] = 0.0;
	for (int l69 = 0; l69 < 3; l69 = l69 + 1) fRec71[l69] = 0.0;
	for (int l70 = 0; l70 < 3; l70 = l70 + 1) fRec70[l70] = 0.0;
	for (int l71 = 0; l71 < 2; l71 = l71 + 1) fVec13[l71] = 0.0;
	for (int l72 = 0; l72 < 2; l72 = l72 + 1) fRec55[l72] = 0.0;
	for (int l73 = 0; l73 < 2; l73 = l73 + 1) fVec14[l73] = 0.0;
	for (int l74 = 0; l74 < 2; l74 = l74 + 1) fRec54[l74] = 0.0;
	for (int l75 = 0; l75 < 3; l75 = l75 + 1) fRec53[l75] = 0.0;
	for (int l76 = 0; l76 < 2; l76 = l76 + 1) fVec15[l76] = 0.0;
	for (int l77 = 0; l77 < 2; l77 = l77 + 1) fRec73[l77] = 0.0;
	for (int l78 = 0; l78 < 2; l78 = l78 + 1) fRec52[l78] = 0.0;
	for (int l79 = 0; l79 < 2; l79 = l79 + 1) fRec51[l79] = 0.0;
	for (int l80 = 0; l80 < 2; l80 = l80 + 1) fRec74[l80] = 0.0;
	for (int l81 = 0; l81 < 2; l81 = l81 + 1) fVec16[l81] = 0.0;
	for (int l82 = 0; l82 < 2; l82 = l82 + 1) fRec50[l82] = 0.0;
	for (int l83 = 0; l83 < 2; l83 = l83 + 1) fRec49[l83] = 0.0;
	for (int l84 = 0; l84 < 3; l84 = l84 + 1) fRec48[l84] = 0.0;
	for (int l85 = 0; l85 < 2; l85 = l85 + 1) fVec17[l85] = 0.0;
	for (int l86 = 0; l86 < 2; l86 = l86 + 1) fRec75[l86] = 0.0;
	for (int l87 = 0; l87 < 2; l87 = l87 + 1) fRec47[l87] = 0.0;
	for (int l88 = 0; l88 < 2; l88 = l88 + 1) fRec46[l88] = 0.0;
	for (int l89 = 0; l89 < 2; l89 = l89 + 1) fRec76[l89] = 0.0;
	for (int l90 = 0; l90 < 2; l90 = l90 + 1) fVec18[l90] = 0.0;
	for (int l91 = 0; l91 < 2; l91 = l91 + 1) fRec45[l91] = 0.0;
	for (int l92 = 0; l92 < 2; l92 = l92 + 1) fRec44[l92] = 0.0;
	for (int l93 = 0; l93 < 3; l93 = l93 + 1) fRec43[l93] = 0.0;
	for (int l94 = 0; l94 < 2; l94 = l94 + 1) fVec19[l94] = 0.0;
	for (int l95 = 0; l95 < 2; l95 = l95 + 1) fRec77[l95] = 0.0;
	for (int l96 = 0; l96 < 2; l96 = l96 + 1) fRec42[l96] = 0.0;
	for (int l97 = 0; l97 < 2; l97 = l97 + 1) fRec41[l97] = 0.0;
	for (int l98 = 0; l98 < 2; l98 = l98 + 1) fRec78[l98] = 0.0;
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
	double fConst5 = std::tan(942.4777960769379 / fConst0);
	double fConst6 = mydsp_faustpower2_f(fConst5);
	fConst7 = 1.0 / fConst6;
	fConst8 = 2.0 * (1.0 - fConst7);
	double fConst9 = 1.0 / fConst5;
	fConst10 = (fConst9 + -1.0000000000000004) / fConst5 + 1.0;
	fConst11 = 1.0 / ((fConst9 + 1.0000000000000004) / fConst5 + 1.0);
	double fConst12 = std::tan(3769.9111843077517 / fConst0);
	double fConst13 = mydsp_faustpower2_f(fConst12);
	fConst14 = 1.0 / fConst13;
	fConst15 = 2.0 * (1.0 - fConst14);
	double fConst16 = 1.0 / fConst12;
	fConst17 = (fConst16 + -1.0000000000000004) / fConst12 + 1.0;
	fConst18 = 1.0 / ((fConst16 + 1.0000000000000004) / fConst12 + 1.0);
	double fConst19 = std::tan(10053.096491487338 / fConst0);
	double fConst20 = mydsp_faustpower2_f(fConst19);
	fConst21 = 1.0 / fConst20;
	fConst22 = 2.0 * (1.0 - fConst21);
	fConst23 = 1.0 / fConst19;
	fConst24 = (fConst23 + -1.0000000000000004) / fConst19 + 1.0;
	fConst25 = 1.0 / ((fConst23 + 1.0000000000000004) / fConst19 + 1.0);
	double fConst26 = std::tan(47123.8898038469 / fConst0);
	fConst27 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst26));
	double fConst28 = 1.0 / fConst26;
	fConst29 = (fConst28 + -1.414213562373095) / fConst26 + 1.0;
	fConst30 = 1.0 / ((fConst28 + 1.414213562373095) / fConst26 + 1.0);
	fConst31 = 1.0 / (fConst1 * fConst3);
	fConst32 = 0.0 - fConst31;
	fConst33 = 1.0 - fConst23;
	double fConst34 = fConst23 + 1.0;
	fConst35 = 1.0 / fConst34;
	fConst36 = 1.0 - fConst16;
	double fConst37 = fConst16 + 1.0;
	fConst38 = 1.0 / fConst37;
	fConst39 = 1.0 - fConst9;
	double fConst40 = fConst9 + 1.0;
	fConst41 = 1.0 / fConst40;
	fConst42 = fConst39 / fConst40;
	fConst43 = 1.0 / (fConst5 * fConst40);
	fConst44 = 0.0 - fConst43;
	fConst45 = 0.0 - 2.0 / fConst6;
	fConst46 = 1.0 - fConst39 / fConst5;
	fConst47 = 1.0 / (fConst40 / fConst5 + 1.0);
	fConst48 = 1.0 - fConst36 / fConst12;
	fConst49 = 1.0 / (fConst37 / fConst12 + 1.0);
	fConst50 = 0.0 - 1.0 / (fConst19 * fConst34);
	fConst51 = 0.0 - 2.0 / fConst20;
	fConst52 = fConst36 / fConst37;
	fConst53 = 1.0 / (fConst12 * fConst37);
	fConst54 = 0.0 - fConst53;
	fConst55 = 0.0 - 2.0 / fConst13;
	double fConst56 = 1.0 / std::tan(20517.741620594938 / fConst0);
	fConst57 = 1.0 - fConst56;
	fConst58 = 1.0 / (fConst56 + 1.0);
	double fConst59 = 1.0 / std::tan(270.1769682087222 / fConst0);
	fConst60 = 1.0 - fConst59;
	fConst61 = 1.0 / (fConst59 + 1.0);
	double fConst62 = 3.141592653589793 / fConst0;
	fConst63 = 1.0 - fConst62;
	fConst64 = 1.0 / (fConst62 + 1.0);
	double fConst65 = 1.0 / std::tan(414.6902302738527 / fConst0);
	fConst66 = 1.0 - fConst65;
	fConst67 = 1.0 / (fConst65 + 1.0);
	double fConst68 = 1.0 / std::tan(609.4689747964198 / fConst0);
	fConst69 = 1.0 - fConst68;
	fConst70 = 1.0 / (fConst68 + 1.0);
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
	double fSlow2 = 1.000000000000001e-05 * double(fVslider0);
	double fSlow3 = double(fVslider1);
	double fSlow4 = 2.0 * (fSlow3 + -0.5);
	double fSlow5 = 1.0 - std::max<double>(0.0, fSlow4);
	double fSlow6 = 1.25 * fSlow3;
	double fSlow7 = fConst11 * std::pow(1e+01, 0.9 * fSlow3);
	double fSlow8 = fConst11 * std::pow(1e+01, 2.0 * fSlow3);
	double fSlow9 = std::pow(1e+01, 0.8 * fSlow3);
	double fSlow10 = std::pow(1e+01, 1.2 * fSlow3);
	double fSlow11 = 1.0 - std::max<double>(0.0, -1.0 * fSlow4);
	double fSlow12 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider2));
	double fSlow13 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider3));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec14[0] = fSlow2 + 0.999 * fRec14[1];
		double fTemp0 = double(input0[i0]);
		double fTemp1 = fTemp0 * fRec14[0];
		double fTemp2 = 1.0 - fRec14[0];
		double fTemp3 = fTemp0 * fTemp2;
		double fTemp4 = fTemp3 + 1e-15;
		fRec23[0] = fTemp1 + (1e-15 - fConst30 * (fConst29 * fRec23[2] + fConst27 * fRec23[1]));
		double fTemp5 = fRec23[2] + fRec23[0] + 2.0 * fRec23[1];
		fVec0[0] = fTemp5;
		fRec22[0] = fConst30 * (fConst31 * fTemp5 + fConst32 * fVec0[1]) - fConst4 * fRec22[1];
		fRec21[0] = 0.0 - fConst35 * (fConst33 * fRec21[1] - (fRec22[0] + fRec22[1]));
		fRec20[0] = fRec21[0] - fConst25 * (fConst24 * fRec20[2] + fConst22 * fRec20[1]);
		double fTemp6 = fRec20[2] + fRec20[0] + 2.0 * fRec20[1];
		fVec1[0] = fTemp6;
		fRec19[0] = 0.0 - fConst38 * (fConst36 * fRec19[1] - fConst25 * (fTemp6 + fVec1[1]));
		fRec18[0] = fRec19[0] - fConst18 * (fConst17 * fRec18[2] + fConst15 * fRec18[1]);
		double fTemp7 = fRec18[2] + fRec18[0] + 2.0 * fRec18[1];
		fVec2[0] = fTemp7;
		fRec17[0] = 0.0 - fConst41 * (fConst39 * fRec17[1] - fConst18 * (fTemp7 + fVec2[1]));
		fRec16[0] = fRec17[0] - fConst11 * (fConst10 * fRec16[2] + fConst8 * fRec16[1]);
		double fTemp8 = std::max<double>(-1.0, std::min<double>(1.0, fSlow7 * (fRec16[2] + fRec16[0] + 2.0 * fRec16[1])));
		fRec25[0] = fConst18 * (fConst43 * fTemp7 + fConst44 * fVec2[1]) - fConst42 * fRec25[1];
		fRec24[0] = fRec25[0] - fConst11 * (fConst10 * fRec24[2] + fConst8 * fRec24[1]);
		double fTemp9 = std::max<double>(-1.0, std::min<double>(1.0, fSlow8 * (fConst7 * fRec24[0] + fConst45 * fRec24[1] + fConst7 * fRec24[2])));
		double fTemp10 = fConst8 * fRec26[1];
		double fTemp11 = fConst15 * fRec27[1];
		fRec29[0] = fConst50 * fRec22[1] - fConst35 * (fConst33 * fRec29[1] - fConst23 * fRec22[0]);
		fRec28[0] = fRec29[0] - fConst25 * (fConst24 * fRec28[2] + fConst22 * fRec28[1]);
		fRec27[0] = fConst25 * (fConst21 * fRec28[0] + fConst51 * fRec28[1] + fConst21 * fRec28[2]) - fConst49 * (fConst48 * fRec27[2] + fTemp11);
		fRec26[0] = fRec27[2] + fConst49 * (fTemp11 + fConst48 * fRec27[0]) - fConst47 * (fConst46 * fRec26[2] + fTemp10);
		double fTemp12 = std::max<double>(-1.0, std::min<double>(1.0, fSlow9 * (fRec26[2] + fConst47 * (fTemp10 + fConst46 * fRec26[0]))));
		double fTemp13 = fConst8 * fRec30[1];
		fRec32[0] = fConst25 * (fConst53 * fTemp6 + fConst54 * fVec1[1]) - fConst52 * fRec32[1];
		fRec31[0] = fRec32[0] - fConst18 * (fConst17 * fRec31[2] + fConst15 * fRec31[1]);
		fRec30[0] = fConst18 * (fConst14 * fRec31[0] + fConst55 * fRec31[1] + fConst14 * fRec31[2]) - fConst47 * (fConst46 * fRec30[2] + fTemp13);
		double fTemp14 = std::max<double>(-1.0, std::min<double>(1.0, fSlow10 * (fRec30[2] + fConst47 * (fTemp13 + fConst46 * fRec30[0]))));
		double fTemp15 = 1.333521432 * fTemp14 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp14)) + 1.584893192 * (fTemp12 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp12)) + fTemp9 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp9))) + 1.2589412 * fTemp8 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp8));
		fVec3[0] = fTemp15;
		fRec15[0] = 0.0 - fConst58 * (fConst57 * fRec15[1] - (fTemp15 + fVec3[1]));
		double fTemp16 = fSlow11 * fRec15[0] + fTemp3 + fSlow6 * (4.0 * fTemp4 * (1.0 - std::fabs(fTemp4)) + (-1e-15 - fTemp3)) + fSlow5 * (fTemp1 + 1e-15) + 1e-15;
		fVec4[0] = fTemp16;
		fRec13[0] = 0.9302847925323914 * (fTemp16 + fVec4[1]) - 0.8605695850647829 * fRec13[1];
		fRec12[0] = fRec13[0] - (1.8405051250752198 * fRec12[1] + 0.8612942439318627 * fRec12[2]);
		double fTemp17 = 1.8508996845035413 * fRec12[1];
		double fTemp18 = 0.9254498422517706 * (fRec12[0] + fRec12[2]);
		double fTemp19 = (fTemp17 + fTemp18) / (Ranode(TUBE_TABLE_12AT7_68k, fRec11[1]) + 1e+05);
		fVec5[0] = fTemp19;
		fRec33[0] = fConst61 * (2.7e+03 * (fTemp19 + fVec5[1]) - fConst60 * fRec33[1]);
		fRec11[0] = Ftube(TUBE_TABLE_12AT7_68k, fTemp18 + fRec33[0] + fTemp17 + -2.617753) + -153.04618518518518;
		fRec10[0] = 0.025 * (fConst31 * fRec11[0] + fConst32 * fRec11[1]) - fConst4 * fRec10[1];
		fRec34[0] = fConst64 * (fConst63 * fRec34[1] + 0.025 * (fRec11[0] - fRec11[1]));
		fRec35[0] = fSlow12 + 0.999 * fRec35[1];
		double fTemp20 = fRec35[0] * ((iSlow1) ? fRec34[0] : fRec10[0]);
		fVec6[0] = fTemp20;
		fRec9[0] = 0.0 - fConst58 * (fConst57 * fRec9[1] - (fTemp20 + fVec6[1]));
		fRec8[0] = 0.9302847925323914 * (fRec9[0] + fRec9[1]) - 0.8605695850647829 * fRec8[1];
		fRec7[0] = fRec8[0] - (1.8405051250752198 * fRec7[1] + 0.8612942439318627 * fRec7[2]);
		double fTemp21 = 1.8508996845035413 * fRec7[1];
		double fTemp22 = 0.9254498422517706 * (fRec7[0] + fRec7[2]);
		double fTemp23 = (fTemp21 + fTemp22) / (Ranode(TUBE_TABLE_12AT7_250k, fRec6[1]) + 1e+05);
		fVec7[0] = fTemp23;
		fRec36[0] = fConst67 * (1.5e+03 * (fTemp23 + fVec7[1]) - fConst66 * fRec36[1]);
		fRec6[0] = Ftube(TUBE_TABLE_12AT7_250k, fTemp22 + fRec36[0] + fTemp21 + -1.887332) + -124.17786666666666;
		fRec5[0] = 0.025 * (fConst31 * fRec6[0] + fConst32 * fRec6[1]) - fConst4 * fRec5[1];
		fRec37[0] = fConst64 * (fConst63 * fRec37[1] + 0.025 * (fRec6[0] - fRec6[1]));
		double fTemp24 = fRec35[0] * ((iSlow1) ? fRec37[0] : fRec5[0]);
		fVec8[0] = fTemp24;
		fRec4[0] = 0.0 - fConst58 * (fConst57 * fRec4[1] - (fTemp24 + fVec8[1]));
		fRec3[0] = 0.9302847925323914 * (fRec4[0] + fRec4[1]) - 0.8605695850647829 * fRec3[1];
		fRec2[0] = fRec3[0] - (1.8405051250752198 * fRec2[1] + 0.8612942439318627 * fRec2[2]);
		double fTemp25 = 1.8508996845035413 * fRec2[1];
		double fTemp26 = 0.9254498422517706 * (fRec2[0] + fRec2[2]);
		double fTemp27 = (fTemp25 + fTemp26) / (Ranode(TUBE_TABLE_12AT7_250k, fRec1[1]) + 1e+05);
		fVec9[0] = fTemp27;
		fRec38[0] = fConst70 * (8.2e+02 * (fTemp27 + fVec9[1]) - fConst69 * fRec38[1]);
		fRec1[0] = Ftube(TUBE_TABLE_12AT7_250k, fTemp26 + fRec38[0] + fTemp25 + -1.256962) + -96.7119512195122;
		fRec0[0] = 0.025 * (fConst31 * fRec1[0] + fConst32 * fRec1[1]) - fConst4 * fRec0[1];
		fRec39[0] = fConst64 * (fConst63 * fRec39[1] + 0.025 * (fRec1[0] - fRec1[1]));
		fRec40[0] = fSlow13 + 0.999 * fRec40[1];
		output0[i0] = FAUSTFLOAT(fRec40[0] * ((iSlow0) ? fRec39[0] : fRec0[0]));
		double fTemp28 = double(input1[i0]);
		double fTemp29 = fTemp28 * fRec14[0];
		double fTemp30 = fTemp28 * fTemp2;
		double fTemp31 = fTemp30 + 1e-15;
		fRec63[0] = fTemp29 + (1e-15 - fConst30 * (fConst29 * fRec63[2] + fConst27 * fRec63[1]));
		double fTemp32 = fRec63[2] + fRec63[0] + 2.0 * fRec63[1];
		fVec10[0] = fTemp32;
		fRec62[0] = fConst30 * (fConst31 * fTemp32 + fConst32 * fVec10[1]) - fConst4 * fRec62[1];
		fRec61[0] = 0.0 - fConst35 * (fConst33 * fRec61[1] - (fRec62[0] + fRec62[1]));
		fRec60[0] = fRec61[0] - fConst25 * (fConst24 * fRec60[2] + fConst22 * fRec60[1]);
		double fTemp33 = fRec60[2] + fRec60[0] + 2.0 * fRec60[1];
		fVec11[0] = fTemp33;
		fRec59[0] = 0.0 - fConst38 * (fConst36 * fRec59[1] - fConst25 * (fTemp33 + fVec11[1]));
		fRec58[0] = fRec59[0] - fConst18 * (fConst17 * fRec58[2] + fConst15 * fRec58[1]);
		double fTemp34 = fRec58[2] + fRec58[0] + 2.0 * fRec58[1];
		fVec12[0] = fTemp34;
		fRec57[0] = 0.0 - fConst41 * (fConst39 * fRec57[1] - fConst18 * (fTemp34 + fVec12[1]));
		fRec56[0] = fRec57[0] - fConst11 * (fConst10 * fRec56[2] + fConst8 * fRec56[1]);
		double fTemp35 = std::max<double>(-1.0, std::min<double>(1.0, fSlow7 * (fRec56[2] + fRec56[0] + 2.0 * fRec56[1])));
		fRec65[0] = fConst18 * (fConst43 * fTemp34 + fConst44 * fVec12[1]) - fConst42 * fRec65[1];
		fRec64[0] = fRec65[0] - fConst11 * (fConst10 * fRec64[2] + fConst8 * fRec64[1]);
		double fTemp36 = std::max<double>(-1.0, std::min<double>(1.0, fSlow8 * (fConst7 * fRec64[0] + fConst45 * fRec64[1] + fConst7 * fRec64[2])));
		double fTemp37 = fConst8 * fRec66[1];
		double fTemp38 = fConst15 * fRec67[1];
		fRec69[0] = fConst50 * fRec62[1] - fConst35 * (fConst33 * fRec69[1] - fConst23 * fRec62[0]);
		fRec68[0] = fRec69[0] - fConst25 * (fConst24 * fRec68[2] + fConst22 * fRec68[1]);
		fRec67[0] = fConst25 * (fConst21 * fRec68[0] + fConst51 * fRec68[1] + fConst21 * fRec68[2]) - fConst49 * (fConst48 * fRec67[2] + fTemp38);
		fRec66[0] = fRec67[2] + fConst49 * (fTemp38 + fConst48 * fRec67[0]) - fConst47 * (fConst46 * fRec66[2] + fTemp37);
		double fTemp39 = std::max<double>(-1.0, std::min<double>(1.0, fSlow9 * (fRec66[2] + fConst47 * (fTemp37 + fConst46 * fRec66[0]))));
		double fTemp40 = fConst8 * fRec70[1];
		fRec72[0] = fConst25 * (fConst53 * fTemp33 + fConst54 * fVec11[1]) - fConst52 * fRec72[1];
		fRec71[0] = fRec72[0] - fConst18 * (fConst17 * fRec71[2] + fConst15 * fRec71[1]);
		fRec70[0] = fConst18 * (fConst14 * fRec71[0] + fConst55 * fRec71[1] + fConst14 * fRec71[2]) - fConst47 * (fConst46 * fRec70[2] + fTemp40);
		double fTemp41 = std::max<double>(-1.0, std::min<double>(1.0, fSlow10 * (fRec70[2] + fConst47 * (fTemp40 + fConst46 * fRec70[0]))));
		double fTemp42 = 1.333521432 * fTemp41 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp41)) + 1.584893192 * (fTemp39 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp39)) + fTemp36 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp36))) + 1.2589412 * fTemp35 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp35));
		fVec13[0] = fTemp42;
		fRec55[0] = 0.0 - fConst58 * (fConst57 * fRec55[1] - (fTemp42 + fVec13[1]));
		double fTemp43 = fSlow11 * fRec55[0] + fTemp30 + fSlow6 * (4.0 * fTemp31 * (1.0 - std::fabs(fTemp31)) + (-1e-15 - fTemp30)) + fSlow5 * (fTemp29 + 1e-15) + 1e-15;
		fVec14[0] = fTemp43;
		fRec54[0] = 0.9302847925323914 * (fTemp43 + fVec14[1]) - 0.8605695850647829 * fRec54[1];
		fRec53[0] = fRec54[0] - (1.8405051250752198 * fRec53[1] + 0.8612942439318627 * fRec53[2]);
		double fTemp44 = 1.8508996845035413 * fRec53[1];
		double fTemp45 = 0.9254498422517706 * (fRec53[0] + fRec53[2]);
		double fTemp46 = (fTemp44 + fTemp45) / (Ranode(TUBE_TABLE_12AT7_68k, fRec52[1]) + 1e+05);
		fVec15[0] = fTemp46;
		fRec73[0] = fConst61 * (2.7e+03 * (fTemp46 + fVec15[1]) - fConst60 * fRec73[1]);
		fRec52[0] = Ftube(TUBE_TABLE_12AT7_68k, fTemp45 + fRec73[0] + fTemp44 + -2.617753) + -153.04618518518518;
		fRec51[0] = 0.025 * (fConst31 * fRec52[0] + fConst32 * fRec52[1]) - fConst4 * fRec51[1];
		fRec74[0] = fConst64 * (fConst63 * fRec74[1] + 0.025 * (fRec52[0] - fRec52[1]));
		double fTemp47 = fRec35[0] * ((iSlow1) ? fRec74[0] : fRec51[0]);
		fVec16[0] = fTemp47;
		fRec50[0] = 0.0 - fConst58 * (fConst57 * fRec50[1] - (fTemp47 + fVec16[1]));
		fRec49[0] = 0.9302847925323914 * (fRec50[0] + fRec50[1]) - 0.8605695850647829 * fRec49[1];
		fRec48[0] = fRec49[0] - (1.8405051250752198 * fRec48[1] + 0.8612942439318627 * fRec48[2]);
		double fTemp48 = 1.8508996845035413 * fRec48[1];
		double fTemp49 = 0.9254498422517706 * (fRec48[0] + fRec48[2]);
		double fTemp50 = (fTemp48 + fTemp49) / (Ranode(TUBE_TABLE_12AT7_250k, fRec47[1]) + 1e+05);
		fVec17[0] = fTemp50;
		fRec75[0] = fConst67 * (1.5e+03 * (fTemp50 + fVec17[1]) - fConst66 * fRec75[1]);
		fRec47[0] = Ftube(TUBE_TABLE_12AT7_250k, fTemp49 + fRec75[0] + fTemp48 + -1.887332) + -124.17786666666666;
		fRec46[0] = 0.025 * (fConst31 * fRec47[0] + fConst32 * fRec47[1]) - fConst4 * fRec46[1];
		fRec76[0] = fConst64 * (fConst63 * fRec76[1] + 0.025 * (fRec47[0] - fRec47[1]));
		double fTemp51 = fRec35[0] * ((iSlow1) ? fRec76[0] : fRec46[0]);
		fVec18[0] = fTemp51;
		fRec45[0] = 0.0 - fConst58 * (fConst57 * fRec45[1] - (fTemp51 + fVec18[1]));
		fRec44[0] = 0.9302847925323914 * (fRec45[0] + fRec45[1]) - 0.8605695850647829 * fRec44[1];
		fRec43[0] = fRec44[0] - (1.8405051250752198 * fRec43[1] + 0.8612942439318627 * fRec43[2]);
		double fTemp52 = 1.8508996845035413 * fRec43[1];
		double fTemp53 = 0.9254498422517706 * (fRec43[0] + fRec43[2]);
		double fTemp54 = (fTemp52 + fTemp53) / (Ranode(TUBE_TABLE_12AT7_250k, fRec42[1]) + 1e+05);
		fVec19[0] = fTemp54;
		fRec77[0] = fConst70 * (8.2e+02 * (fTemp54 + fVec19[1]) - fConst69 * fRec77[1]);
		fRec42[0] = Ftube(TUBE_TABLE_12AT7_250k, fTemp53 + fRec77[0] + fTemp52 + -1.256962) + -96.7119512195122;
		fRec41[0] = 0.025 * (fConst31 * fRec42[0] + fConst32 * fRec42[1]) - fConst4 * fRec41[1];
		fRec78[0] = fConst64 * (fConst63 * fRec78[1] + 0.025 * (fRec42[0] - fRec42[1]));
		output1[i0] = FAUSTFLOAT(fRec40[0] * ((iSlow0) ? fRec78[0] : fRec41[0]));
		fRec14[1] = fRec14[0];
		fRec23[2] = fRec23[1];
		fRec23[1] = fRec23[0];
		fVec0[1] = fVec0[0];
		fRec22[1] = fRec22[0];
		fRec21[1] = fRec21[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fVec1[1] = fVec1[0];
		fRec19[1] = fRec19[0];
		fRec18[2] = fRec18[1];
		fRec18[1] = fRec18[0];
		fVec2[1] = fVec2[0];
		fRec17[1] = fRec17[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fVec3[1] = fVec3[0];
		fRec15[1] = fRec15[0];
		fVec4[1] = fVec4[0];
		fRec13[1] = fRec13[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fVec5[1] = fVec5[0];
		fRec33[1] = fRec33[0];
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
		fRec34[1] = fRec34[0];
		fRec35[1] = fRec35[0];
		fVec6[1] = fVec6[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fVec7[1] = fVec7[0];
		fRec36[1] = fRec36[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec37[1] = fRec37[0];
		fVec8[1] = fVec8[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fVec9[1] = fVec9[0];
		fRec38[1] = fRec38[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec39[1] = fRec39[0];
		fRec40[1] = fRec40[0];
		fRec63[2] = fRec63[1];
		fRec63[1] = fRec63[0];
		fVec10[1] = fVec10[0];
		fRec62[1] = fRec62[0];
		fRec61[1] = fRec61[0];
		fRec60[2] = fRec60[1];
		fRec60[1] = fRec60[0];
		fVec11[1] = fVec11[0];
		fRec59[1] = fRec59[0];
		fRec58[2] = fRec58[1];
		fRec58[1] = fRec58[0];
		fVec12[1] = fVec12[0];
		fRec57[1] = fRec57[0];
		fRec56[2] = fRec56[1];
		fRec56[1] = fRec56[0];
		fRec65[1] = fRec65[0];
		fRec64[2] = fRec64[1];
		fRec64[1] = fRec64[0];
		fRec69[1] = fRec69[0];
		fRec68[2] = fRec68[1];
		fRec68[1] = fRec68[0];
		fRec67[2] = fRec67[1];
		fRec67[1] = fRec67[0];
		fRec66[2] = fRec66[1];
		fRec66[1] = fRec66[0];
		fRec72[1] = fRec72[0];
		fRec71[2] = fRec71[1];
		fRec71[1] = fRec71[0];
		fRec70[2] = fRec70[1];
		fRec70[1] = fRec70[0];
		fVec13[1] = fVec13[0];
		fRec55[1] = fRec55[0];
		fVec14[1] = fVec14[0];
		fRec54[1] = fRec54[0];
		fRec53[2] = fRec53[1];
		fRec53[1] = fRec53[0];
		fVec15[1] = fVec15[0];
		fRec73[1] = fRec73[0];
		fRec52[1] = fRec52[0];
		fRec51[1] = fRec51[0];
		fRec74[1] = fRec74[0];
		fVec16[1] = fVec16[0];
		fRec50[1] = fRec50[0];
		fRec49[1] = fRec49[0];
		fRec48[2] = fRec48[1];
		fRec48[1] = fRec48[0];
		fVec17[1] = fVec17[0];
		fRec75[1] = fRec75[0];
		fRec47[1] = fRec47[0];
		fRec46[1] = fRec46[0];
		fRec76[1] = fRec76[0];
		fVec18[1] = fVec18[0];
		fRec45[1] = fRec45[0];
		fRec44[1] = fRec44[0];
		fRec43[2] = fRec43[1];
		fRec43[1] = fRec43[0];
		fVec19[1] = fVec19[0];
		fRec77[1] = fRec77[0];
		fRec42[1] = fRec42[0];
		fRec41[1] = fRec41[0];
		fRec78[1] = fRec78[0];
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
		fVslider1_ = (float*)data; // , 0.35, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fVslider0_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
		break;
	case PREGAIN: 
		fVslider2_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
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

} // end namespace gxamp14_stereo
