// generated from file '../src/LV2/faust/gxamp2_stereo.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxamp2_stereo {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst2;
	double fConst3;
	double fConst5;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec10[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst6;
	double fConst9;
	double fConst11;
	double fConst13;
	double fConst14;
	double fConst16;
	double fConst18;
	double fConst19;
	double fConst22;
	double fConst26;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec24[2];
	double fConst27;
	double fConst28;
	double fRec23[3];
	double fVec0[2];
	double fConst29;
	double fConst30;
	double fRec22[2];
	double fRec21[2];
	double fConst31;
	double fConst33;
	double fConst34;
	double fRec20[3];
	double fVec1[2];
	double fConst35;
	double fConst36;
	double fConst37;
	double fRec19[2];
	double fConst38;
	double fConst39;
	double fRec18[3];
	double fConst40;
	double fConst44;
	double fConst45;
	double fConst46;
	double fConst48;
	double fConst49;
	double fRec17[3];
	double fConst50;
	double fRec28[2];
	double fRec27[3];
	double fConst51;
	double fConst52;
	double fConst53;
	double fRec26[3];
	double fRec25[3];
	double fConst54;
	double fConst55;
	double fConst56;
	double fRec32[2];
	double fRec31[3];
	double fVec2[2];
	double fConst57;
	double fConst58;
	double fRec30[2];
	double fConst59;
	double fRec29[3];
	double fConst60;
	double fConst61;
	double fRec34[2];
	double fRec33[3];
	double fVec3[2];
	double fRec16[2];
	double fVec4[2];
	double fRec15[2];
	double fRec14[3];
	double fConst63;
	double fVec5[2];
	double fConst64;
	double fRec35[2];
	double fRec13[2];
	double fRec12[2];
	double fRec11[2];
	double fVec6[2];
	double fRec9[2];
	double fRec8[3];
	double fConst66;
	double fVec7[2];
	double fConst67;
	double fRec36[2];
	double fRec7[2];
	double fRec6[2];
	double fRec5[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec37[2];
	double fConst69;
	double fRec4[3];
	double fVec8[2];
	double fRec3[2];
	double fRec2[3];
	double fConst71;
	double fVec9[2];
	double fConst72;
	double fRec38[2];
	double fRec1[2];
	double fRec0[2];
	double fRec61[3];
	double fVec10[2];
	double fRec60[2];
	double fRec59[2];
	double fRec58[3];
	double fVec11[2];
	double fRec57[2];
	double fRec56[3];
	double fRec55[3];
	double fRec65[2];
	double fRec64[3];
	double fRec63[3];
	double fRec62[3];
	double fRec69[2];
	double fRec68[3];
	double fVec12[2];
	double fRec67[2];
	double fRec66[3];
	double fRec71[2];
	double fRec70[3];
	double fVec13[2];
	double fRec54[2];
	double fVec14[2];
	double fRec53[2];
	double fRec52[3];
	double fVec15[2];
	double fRec72[2];
	double fRec51[2];
	double fRec50[2];
	double fRec49[2];
	double fVec16[2];
	double fRec48[2];
	double fRec47[3];
	double fVec17[2];
	double fRec73[2];
	double fRec46[2];
	double fRec45[2];
	double fRec44[2];
	double fRec43[3];
	double fVec18[2];
	double fRec42[2];
	double fRec41[3];
	double fVec19[2];
	double fRec74[2];
	double fRec40[2];
	double fRec39[2];

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
	id = "6V6";
	name = N_("6V6");
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec10[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec24[l1] = 0.0;
	for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) fRec23[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fVec0[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec22[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec21[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec20[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fVec1[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec19[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec18[l9] = 0.0;
	for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) fRec17[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec28[l11] = 0.0;
	for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) fRec27[l12] = 0.0;
	for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) fRec26[l13] = 0.0;
	for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) fRec25[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec32[l15] = 0.0;
	for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) fRec31[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fVec2[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec30[l18] = 0.0;
	for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) fRec29[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fRec34[l20] = 0.0;
	for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) fRec33[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fVec3[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fRec16[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fVec4[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fRec15[l25] = 0.0;
	for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) fRec14[l26] = 0.0;
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) fVec5[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec35[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fRec13[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec12[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fRec11[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fVec6[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fRec9[l33] = 0.0;
	for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) fRec8[l34] = 0.0;
	for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) fVec7[l35] = 0.0;
	for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) fRec36[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fRec7[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fRec6[l38] = 0.0;
	for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) fRec5[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fRec37[l40] = 0.0;
	for (int l41 = 0; (l41 < 3); l41 = (l41 + 1)) fRec4[l41] = 0.0;
	for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) fVec8[l42] = 0.0;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fRec3[l43] = 0.0;
	for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) fRec2[l44] = 0.0;
	for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) fVec9[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec38[l46] = 0.0;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) fRec1[l47] = 0.0;
	for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) fRec0[l48] = 0.0;
	for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) fRec61[l49] = 0.0;
	for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) fVec10[l50] = 0.0;
	for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) fRec60[l51] = 0.0;
	for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) fRec59[l52] = 0.0;
	for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) fRec58[l53] = 0.0;
	for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) fVec11[l54] = 0.0;
	for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) fRec57[l55] = 0.0;
	for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) fRec56[l56] = 0.0;
	for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) fRec55[l57] = 0.0;
	for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) fRec65[l58] = 0.0;
	for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) fRec64[l59] = 0.0;
	for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) fRec63[l60] = 0.0;
	for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) fRec62[l61] = 0.0;
	for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) fRec69[l62] = 0.0;
	for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) fRec68[l63] = 0.0;
	for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) fVec12[l64] = 0.0;
	for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) fRec67[l65] = 0.0;
	for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) fRec66[l66] = 0.0;
	for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) fRec71[l67] = 0.0;
	for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) fRec70[l68] = 0.0;
	for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) fVec13[l69] = 0.0;
	for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) fRec54[l70] = 0.0;
	for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) fVec14[l71] = 0.0;
	for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) fRec53[l72] = 0.0;
	for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) fRec52[l73] = 0.0;
	for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) fVec15[l74] = 0.0;
	for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) fRec72[l75] = 0.0;
	for (int l76 = 0; (l76 < 2); l76 = (l76 + 1)) fRec51[l76] = 0.0;
	for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) fRec50[l77] = 0.0;
	for (int l78 = 0; (l78 < 2); l78 = (l78 + 1)) fRec49[l78] = 0.0;
	for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) fVec16[l79] = 0.0;
	for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) fRec48[l80] = 0.0;
	for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) fRec47[l81] = 0.0;
	for (int l82 = 0; (l82 < 2); l82 = (l82 + 1)) fVec17[l82] = 0.0;
	for (int l83 = 0; (l83 < 2); l83 = (l83 + 1)) fRec73[l83] = 0.0;
	for (int l84 = 0; (l84 < 2); l84 = (l84 + 1)) fRec46[l84] = 0.0;
	for (int l85 = 0; (l85 < 2); l85 = (l85 + 1)) fRec45[l85] = 0.0;
	for (int l86 = 0; (l86 < 2); l86 = (l86 + 1)) fRec44[l86] = 0.0;
	for (int l87 = 0; (l87 < 3); l87 = (l87 + 1)) fRec43[l87] = 0.0;
	for (int l88 = 0; (l88 < 2); l88 = (l88 + 1)) fVec18[l88] = 0.0;
	for (int l89 = 0; (l89 < 2); l89 = (l89 + 1)) fRec42[l89] = 0.0;
	for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) fRec41[l90] = 0.0;
	for (int l91 = 0; (l91 < 2); l91 = (l91 + 1)) fVec19[l91] = 0.0;
	for (int l92 = 0; (l92 < 2); l92 = (l92 + 1)) fRec74[l92] = 0.0;
	for (int l93 = 0; (l93 < 2); l93 = (l93 + 1)) fRec40[l93] = 0.0;
	for (int l94 = 0; (l94 < 2); l94 = (l94 + 1)) fRec39[l94] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = (3.1415926535897931 / fConst0);
	fConst2 = (1.0 / (fConst1 + 1.0));
	fConst3 = (1.0 - fConst1);
	double fConst4 = (1.0 / std::tan((20517.741620594938 / fConst0)));
	fConst5 = (1.0 / (fConst4 + 1.0));
	fConst6 = (1.0 - fConst4);
	double fConst7 = std::tan((3769.9111843077517 / fConst0));
	double fConst8 = (1.0 / fConst7);
	fConst9 = (1.0 / (((fConst8 + 1.0000000000000004) / fConst7) + 1.0));
	double fConst10 = mydsp_faustpower2_f(fConst7);
	fConst11 = (1.0 / fConst10);
	double fConst12 = std::tan((10053.096491487338 / fConst0));
	fConst13 = (1.0 / fConst12);
	fConst14 = (1.0 / (((fConst13 + 1.0000000000000004) / fConst12) + 1.0));
	double fConst15 = (fConst8 + 1.0);
	fConst16 = (1.0 / (fConst7 * fConst15));
	double fConst17 = (fConst13 + 1.0);
	fConst18 = (1.0 / fConst17);
	fConst19 = (1.0 - fConst13);
	double fConst20 = std::tan((47123.889803846898 / fConst0));
	double fConst21 = (1.0 / fConst20);
	fConst22 = (1.0 / (((fConst21 + 1.4142135623730949) / fConst20) + 1.0));
	double fConst23 = std::tan((97.389372261283583 / fConst0));
	double fConst24 = (1.0 / fConst23);
	double fConst25 = (fConst24 + 1.0);
	fConst26 = (1.0 / (fConst23 * fConst25));
	fConst27 = (((fConst21 + -1.4142135623730949) / fConst20) + 1.0);
	fConst28 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst20))));
	fConst29 = (0.0 - fConst26);
	fConst30 = ((1.0 - fConst24) / fConst25);
	fConst31 = (((fConst13 + -1.0000000000000004) / fConst12) + 1.0);
	double fConst32 = mydsp_faustpower2_f(fConst12);
	fConst33 = (1.0 / fConst32);
	fConst34 = (2.0 * (1.0 - fConst33));
	fConst35 = (0.0 - fConst16);
	fConst36 = (1.0 - fConst8);
	fConst37 = (fConst36 / fConst15);
	fConst38 = (((fConst8 + -1.0000000000000004) / fConst7) + 1.0);
	fConst39 = (2.0 * (1.0 - fConst11));
	fConst40 = (0.0 - (2.0 / fConst10));
	double fConst41 = std::tan((942.47779607693792 / fConst0));
	double fConst42 = (1.0 / fConst41);
	double fConst43 = (fConst42 + 1.0);
	fConst44 = (1.0 / ((fConst43 / fConst41) + 1.0));
	fConst45 = (1.0 - fConst42);
	fConst46 = (1.0 - (fConst45 / fConst41));
	double fConst47 = mydsp_faustpower2_f(fConst41);
	fConst48 = (1.0 / fConst47);
	fConst49 = (2.0 * (1.0 - fConst48));
	fConst50 = (0.0 - (1.0 / (fConst12 * fConst17)));
	fConst51 = (0.0 - (2.0 / fConst32));
	fConst52 = (1.0 / ((fConst15 / fConst7) + 1.0));
	fConst53 = (1.0 - (fConst36 / fConst7));
	fConst54 = (1.0 / (((fConst42 + 1.0000000000000004) / fConst41) + 1.0));
	fConst55 = (1.0 / (fConst41 * fConst43));
	fConst56 = (1.0 / fConst15);
	fConst57 = (0.0 - fConst55);
	fConst58 = (fConst45 / fConst43);
	fConst59 = (((fConst42 + -1.0000000000000004) / fConst41) + 1.0);
	fConst60 = (0.0 - (2.0 / fConst47));
	fConst61 = (1.0 / fConst43);
	double fConst62 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst63 = (1.0 / (fConst62 + 1.0));
	fConst64 = (1.0 - fConst62);
	double fConst65 = (1.0 / std::tan((414.69023027385271 / fConst0)));
	fConst66 = (1.0 / (fConst65 + 1.0));
	fConst67 = (1.0 - fConst65);
	double fConst68 = std::log((7539.8223686155034 / fConst0));
	fConst69 = (0.0 - (1.8442000000000001 * std::cos(std::exp(((fConst68 * ((fConst68 * ((fConst68 * ((fConst68 * ((0.0050615800000000004 * fConst68) + 0.064468059999999994)) + 0.27547621)) + 0.43359432999999997)) + 1.3128224799999999)) + 0.072388869999999994)))));
	double fConst70 = (1.0 / std::tan((609.46897479641984 / fConst0)));
	fConst71 = (1.0 / (fConst70 + 1.0));
	fConst72 = (1.0 - fConst70);
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
	double fSlow0 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider0))));
	double fSlow1 = double(fVslider1);
	double fSlow2 = (2.0 * (fSlow1 + -0.5));
	double fSlow3 = (1.0 - std::max<double>(0.0, (-1.0 * fSlow2)));
	double fSlow4 = std::pow(10.0, (1.2 * fSlow1));
	double fSlow5 = (1.0000000000000009e-05 * double(fVslider2));
	double fSlow6 = std::pow(10.0, (0.80000000000000004 * fSlow1));
	double fSlow7 = (fConst54 * std::pow(10.0, (2.0 * fSlow1)));
	double fSlow8 = (fConst54 * std::pow(10.0, (0.90000000000000002 * fSlow1)));
	double fSlow9 = (1.25 * fSlow1);
	double fSlow10 = (1.0 - std::max<double>(0.0, fSlow2));
	double fSlow11 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider3))));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		fRec10[0] = (fSlow0 + (0.999 * fRec10[1]));
		double fTemp0 = double(input0[i0]);
		fRec24[0] = (fSlow5 + (0.999 * fRec24[1]));
		double fTemp1 = (fTemp0 * fRec24[0]);
		fRec23[0] = (fTemp1 + (1.0000000000000001e-15 - (fConst22 * ((fConst27 * fRec23[2]) + (fConst28 * fRec23[1])))));
		double fTemp2 = (fRec23[2] + (fRec23[0] + (2.0 * fRec23[1])));
		fVec0[0] = fTemp2;
		fRec22[0] = ((fConst22 * ((fConst26 * fTemp2) + (fConst29 * fVec0[1]))) - (fConst30 * fRec22[1]));
		fRec21[0] = (0.0 - (fConst18 * ((fConst19 * fRec21[1]) - (fRec22[0] + fRec22[1]))));
		fRec20[0] = (fRec21[0] - (fConst14 * ((fConst31 * fRec20[2]) + (fConst34 * fRec20[1]))));
		double fTemp3 = (fRec20[2] + (fRec20[0] + (2.0 * fRec20[1])));
		fVec1[0] = fTemp3;
		fRec19[0] = ((fConst14 * ((fConst16 * fTemp3) + (fConst35 * fVec1[1]))) - (fConst37 * fRec19[1]));
		fRec18[0] = (fRec19[0] - (fConst9 * ((fConst38 * fRec18[2]) + (fConst39 * fRec18[1]))));
		double fTemp4 = (fConst49 * fRec17[1]);
		fRec17[0] = ((fConst9 * (((fConst11 * fRec18[0]) + (fConst40 * fRec18[1])) + (fConst11 * fRec18[2]))) - (fConst44 * ((fConst46 * fRec17[2]) + fTemp4)));
		double fTemp5 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow4 * (fRec17[2] + (fConst44 * (fTemp4 + (fConst46 * fRec17[0])))))));
		fRec28[0] = ((fConst50 * fRec22[1]) - (fConst18 * ((fConst19 * fRec28[1]) - (fConst13 * fRec22[0]))));
		fRec27[0] = (fRec28[0] - (fConst14 * ((fConst31 * fRec27[2]) + (fConst34 * fRec27[1]))));
		double fTemp6 = (fConst39 * fRec26[1]);
		fRec26[0] = ((fConst14 * (((fConst33 * fRec27[0]) + (fConst51 * fRec27[1])) + (fConst33 * fRec27[2]))) - (fConst52 * ((fConst53 * fRec26[2]) + fTemp6)));
		double fTemp7 = (fConst49 * fRec25[1]);
		fRec25[0] = ((fRec26[2] + (fConst52 * (fTemp6 + (fConst53 * fRec26[0])))) - (fConst44 * ((fConst46 * fRec25[2]) + fTemp7)));
		double fTemp8 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow6 * (fRec25[2] + (fConst44 * (fTemp7 + (fConst46 * fRec25[0])))))));
		fRec32[0] = (0.0 - (fConst56 * ((fConst36 * fRec32[1]) - (fConst14 * (fTemp3 + fVec1[1])))));
		fRec31[0] = (fRec32[0] - (fConst9 * ((fConst38 * fRec31[2]) + (fConst39 * fRec31[1]))));
		double fTemp9 = (fRec31[2] + (fRec31[0] + (2.0 * fRec31[1])));
		fVec2[0] = fTemp9;
		fRec30[0] = ((fConst9 * ((fConst55 * fTemp9) + (fConst57 * fVec2[1]))) - (fConst58 * fRec30[1]));
		fRec29[0] = (fRec30[0] - (fConst54 * ((fConst59 * fRec29[2]) + (fConst49 * fRec29[1]))));
		double fTemp10 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow7 * (((fConst48 * fRec29[0]) + (fConst60 * fRec29[1])) + (fConst48 * fRec29[2])))));
		fRec34[0] = (0.0 - (fConst61 * ((fConst45 * fRec34[1]) - (fConst9 * (fTemp9 + fVec2[1])))));
		fRec33[0] = (fRec34[0] - (fConst54 * ((fConst59 * fRec33[2]) + (fConst49 * fRec33[1]))));
		double fTemp11 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow8 * (fRec33[2] + (fRec33[0] + (2.0 * fRec33[1]))))));
		double fTemp12 = (((1.333521432 * (fTemp5 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp5))))) + (1.584893192 * ((fTemp8 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp8)))) + (fTemp10 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp10))))))) + (1.2589412 * (fTemp11 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp11))))));
		fVec3[0] = fTemp12;
		fRec16[0] = (0.0 - (fConst5 * ((fConst6 * fRec16[1]) - (fTemp12 + fVec3[1]))));
		double fTemp13 = (1.0 - fRec24[0]);
		double fTemp14 = (fTemp0 * fTemp13);
		double fTemp15 = (fTemp14 + 1.0000000000000001e-15);
		double fTemp16 = (fRec10[0] * (((fSlow3 * fRec16[0]) + ((fTemp14 + (fSlow9 * ((4.0 * (fTemp15 * (1.0 - std::fabs(fTemp15)))) + (-1.0000000000000001e-15 - fTemp14)))) + (fSlow10 * (fTemp1 + 1.0000000000000001e-15)))) + 1.0000000000000001e-15));
		fVec4[0] = fTemp16;
		fRec15[0] = ((0.93028479253239138 * (fTemp16 + fVec4[1])) - (0.86056958506478287 * fRec15[1]));
		fRec14[0] = (fRec15[0] - ((1.8405051250752198 * fRec14[1]) + (0.86129424393186271 * fRec14[2])));
		double fTemp17 = (0.92544984225177063 * (fRec14[0] + fRec14[2]));
		double fTemp18 = (1.8508996845035413 * fRec14[1]);
		double fTemp19 = ((fTemp18 + fTemp17) / (double(Ranode(int(TUBE_TABLE_6V6_68k), double(fRec13[1]))) + 100000.0));
		fVec5[0] = fTemp19;
		fRec35[0] = (fConst63 * ((2700.0 * (fTemp19 + fVec5[1])) - (fConst64 * fRec35[1])));
		fRec13[0] = (double(Ftube(int(TUBE_TABLE_6V6_68k), double(((fTemp17 + (fRec35[0] + fTemp18)) + -2.2961499999999999)))) + -164.9574074074074);
		fRec12[0] = (fConst2 * ((fConst3 * fRec12[1]) + (0.025000000000000001 * (fRec13[0] - fRec13[1]))));
		fRec11[0] = (fConst5 * ((0.77000000000000002 * (fRec12[0] + fRec12[1])) - (fConst6 * fRec11[1])));
		double fTemp20 = (fRec10[0] * fRec11[0]);
		fVec6[0] = fTemp20;
		fRec9[0] = ((0.93028479253239138 * (fTemp20 + fVec6[1])) - (0.86056958506478287 * fRec9[1]));
		fRec8[0] = (fRec9[0] - ((1.8405051250752198 * fRec8[1]) + (0.86129424393186271 * fRec8[2])));
		double fTemp21 = (0.92544984225177063 * (fRec8[0] + fRec8[2]));
		double fTemp22 = (1.8508996845035413 * fRec8[1]);
		double fTemp23 = ((fTemp22 + fTemp21) / (double(Ranode(int(TUBE_TABLE_6V6_250k), double(fRec7[1]))) + 100000.0));
		fVec7[0] = fTemp23;
		fRec36[0] = (fConst66 * ((1500.0 * (fTemp23 + fVec7[1])) - (fConst67 * fRec36[1])));
		fRec7[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double(((fTemp21 + (fRec36[0] + fTemp22)) + -1.6755869999999999)))) + -138.29419999999999);
		fRec6[0] = (fConst2 * ((fConst3 * fRec6[1]) + (0.025000000000000001 * (fRec7[0] - fRec7[1]))));
		fRec5[0] = (fConst5 * ((0.77000000000000002 * (fRec6[0] + fRec6[1])) - (fConst6 * fRec5[1])));
		fRec37[0] = (fSlow11 + (0.999 * fRec37[1]));
		fRec4[0] = ((fRec5[0] * fRec37[0]) - ((fConst69 * fRec4[1]) + (0.85026841000000009 * fRec4[2])));
		double fTemp24 = (fRec4[0] - (1.0589999999999999 * fRec4[1]));
		fVec8[0] = fTemp24;
		fRec3[0] = ((0.93028479253239138 * (fTemp24 + fVec8[1])) - (0.86056958506478287 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.86129424393186271 * fRec2[2])));
		double fTemp25 = (0.92544984225177063 * (fRec2[0] + fRec2[2]));
		double fTemp26 = (1.8508996845035413 * fRec2[1]);
		double fTemp27 = ((fTemp26 + fTemp25) / (double(Ranode(int(TUBE_TABLE_6V6_250k), double(fRec1[1]))) + 100000.0));
		fVec9[0] = fTemp27;
		fRec38[0] = (fConst71 * ((820.0 * (fTemp27 + fVec9[1])) - (fConst72 * fRec38[1])));
		fRec1[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double(((fTemp25 + (fRec38[0] + fTemp26)) + -1.1304620000000001)))) + -112.13878048780487);
		fRec0[0] = (fConst2 * ((fConst3 * fRec0[1]) + (0.025000000000000001 * (fRec1[0] - fRec1[1]))));
		output0[i0] = FAUSTFLOAT((0.77000000000000002 * fRec0[0]));
		double fTemp28 = double(input1[i0]);
		double fTemp29 = (fTemp28 * fRec24[0]);
		fRec61[0] = (fTemp29 + (1.0000000000000001e-15 - (fConst22 * ((fConst27 * fRec61[2]) + (fConst28 * fRec61[1])))));
		double fTemp30 = (fRec61[2] + (fRec61[0] + (2.0 * fRec61[1])));
		fVec10[0] = fTemp30;
		fRec60[0] = ((fConst22 * ((fConst26 * fTemp30) + (fConst29 * fVec10[1]))) - (fConst30 * fRec60[1]));
		fRec59[0] = (0.0 - (fConst18 * ((fConst19 * fRec59[1]) - (fRec60[0] + fRec60[1]))));
		fRec58[0] = (fRec59[0] - (fConst14 * ((fConst31 * fRec58[2]) + (fConst34 * fRec58[1]))));
		double fTemp31 = (fRec58[2] + (fRec58[0] + (2.0 * fRec58[1])));
		fVec11[0] = fTemp31;
		fRec57[0] = ((fConst14 * ((fConst16 * fTemp31) + (fConst35 * fVec11[1]))) - (fConst37 * fRec57[1]));
		fRec56[0] = (fRec57[0] - (fConst9 * ((fConst38 * fRec56[2]) + (fConst39 * fRec56[1]))));
		double fTemp32 = (fConst49 * fRec55[1]);
		fRec55[0] = ((fConst9 * (((fConst11 * fRec56[0]) + (fConst40 * fRec56[1])) + (fConst11 * fRec56[2]))) - (fConst44 * ((fConst46 * fRec55[2]) + fTemp32)));
		double fTemp33 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow4 * (fRec55[2] + (fConst44 * (fTemp32 + (fConst46 * fRec55[0])))))));
		fRec65[0] = ((fConst50 * fRec60[1]) - (fConst18 * ((fConst19 * fRec65[1]) - (fConst13 * fRec60[0]))));
		fRec64[0] = (fRec65[0] - (fConst14 * ((fConst31 * fRec64[2]) + (fConst34 * fRec64[1]))));
		double fTemp34 = (fConst39 * fRec63[1]);
		fRec63[0] = ((fConst14 * (((fConst33 * fRec64[0]) + (fConst51 * fRec64[1])) + (fConst33 * fRec64[2]))) - (fConst52 * ((fConst53 * fRec63[2]) + fTemp34)));
		double fTemp35 = (fConst49 * fRec62[1]);
		fRec62[0] = ((fRec63[2] + (fConst52 * (fTemp34 + (fConst53 * fRec63[0])))) - (fConst44 * ((fConst46 * fRec62[2]) + fTemp35)));
		double fTemp36 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow6 * (fRec62[2] + (fConst44 * (fTemp35 + (fConst46 * fRec62[0])))))));
		fRec69[0] = (0.0 - (fConst56 * ((fConst36 * fRec69[1]) - (fConst14 * (fTemp31 + fVec11[1])))));
		fRec68[0] = (fRec69[0] - (fConst9 * ((fConst38 * fRec68[2]) + (fConst39 * fRec68[1]))));
		double fTemp37 = (fRec68[2] + (fRec68[0] + (2.0 * fRec68[1])));
		fVec12[0] = fTemp37;
		fRec67[0] = ((fConst9 * ((fConst55 * fTemp37) + (fConst57 * fVec12[1]))) - (fConst58 * fRec67[1]));
		fRec66[0] = (fRec67[0] - (fConst54 * ((fConst59 * fRec66[2]) + (fConst49 * fRec66[1]))));
		double fTemp38 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow7 * (((fConst48 * fRec66[0]) + (fConst60 * fRec66[1])) + (fConst48 * fRec66[2])))));
		fRec71[0] = (0.0 - (fConst61 * ((fConst45 * fRec71[1]) - (fConst9 * (fTemp37 + fVec12[1])))));
		fRec70[0] = (fRec71[0] - (fConst54 * ((fConst59 * fRec70[2]) + (fConst49 * fRec70[1]))));
		double fTemp39 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow8 * (fRec70[2] + (fRec70[0] + (2.0 * fRec70[1]))))));
		double fTemp40 = (((1.333521432 * (fTemp33 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp33))))) + (1.584893192 * ((fTemp36 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp36)))) + (fTemp38 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp38))))))) + (1.2589412 * (fTemp39 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp39))))));
		fVec13[0] = fTemp40;
		fRec54[0] = (0.0 - (fConst5 * ((fConst6 * fRec54[1]) - (fTemp40 + fVec13[1]))));
		double fTemp41 = (fTemp28 * fTemp13);
		double fTemp42 = (fTemp41 + 1.0000000000000001e-15);
		double fTemp43 = (fRec10[0] * (((fSlow3 * fRec54[0]) + ((fTemp41 + (fSlow9 * ((4.0 * (fTemp42 * (1.0 - std::fabs(fTemp42)))) + (-1.0000000000000001e-15 - fTemp41)))) + (fSlow10 * (fTemp29 + 1.0000000000000001e-15)))) + 1.0000000000000001e-15));
		fVec14[0] = fTemp43;
		fRec53[0] = ((0.93028479253239138 * (fTemp43 + fVec14[1])) - (0.86056958506478287 * fRec53[1]));
		fRec52[0] = (fRec53[0] - ((1.8405051250752198 * fRec52[1]) + (0.86129424393186271 * fRec52[2])));
		double fTemp44 = (0.92544984225177063 * (fRec52[0] + fRec52[2]));
		double fTemp45 = (1.8508996845035413 * fRec52[1]);
		double fTemp46 = ((fTemp45 + fTemp44) / (double(Ranode(int(TUBE_TABLE_6V6_68k), double(fRec51[1]))) + 100000.0));
		fVec15[0] = fTemp46;
		fRec72[0] = (fConst63 * ((2700.0 * (fTemp46 + fVec15[1])) - (fConst64 * fRec72[1])));
		fRec51[0] = (double(Ftube(int(TUBE_TABLE_6V6_68k), double(((fTemp44 + (fRec72[0] + fTemp45)) + -2.2961499999999999)))) + -164.9574074074074);
		fRec50[0] = (fConst2 * ((fConst3 * fRec50[1]) + (0.025000000000000001 * (fRec51[0] - fRec51[1]))));
		fRec49[0] = (fConst5 * ((0.77000000000000002 * (fRec50[0] + fRec50[1])) - (fConst6 * fRec49[1])));
		double fTemp47 = (fRec10[0] * fRec49[0]);
		fVec16[0] = fTemp47;
		fRec48[0] = ((0.93028479253239138 * (fTemp47 + fVec16[1])) - (0.86056958506478287 * fRec48[1]));
		fRec47[0] = (fRec48[0] - ((1.8405051250752198 * fRec47[1]) + (0.86129424393186271 * fRec47[2])));
		double fTemp48 = (0.92544984225177063 * (fRec47[0] + fRec47[2]));
		double fTemp49 = (1.8508996845035413 * fRec47[1]);
		double fTemp50 = ((fTemp49 + fTemp48) / (double(Ranode(int(TUBE_TABLE_6V6_250k), double(fRec46[1]))) + 100000.0));
		fVec17[0] = fTemp50;
		fRec73[0] = (fConst66 * ((1500.0 * (fTemp50 + fVec17[1])) - (fConst67 * fRec73[1])));
		fRec46[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double(((fTemp48 + (fRec73[0] + fTemp49)) + -1.6755869999999999)))) + -138.29419999999999);
		fRec45[0] = (fConst2 * ((fConst3 * fRec45[1]) + (0.025000000000000001 * (fRec46[0] - fRec46[1]))));
		fRec44[0] = (fConst5 * ((0.77000000000000002 * (fRec45[0] + fRec45[1])) - (fConst6 * fRec44[1])));
		fRec43[0] = ((fRec37[0] * fRec44[0]) - ((fConst69 * fRec43[1]) + (0.85026841000000009 * fRec43[2])));
		double fTemp51 = (fRec43[0] - (1.0589999999999999 * fRec43[1]));
		fVec18[0] = fTemp51;
		fRec42[0] = ((0.93028479253239138 * (fTemp51 + fVec18[1])) - (0.86056958506478287 * fRec42[1]));
		fRec41[0] = (fRec42[0] - ((1.8405051250752198 * fRec41[1]) + (0.86129424393186271 * fRec41[2])));
		double fTemp52 = (0.92544984225177063 * (fRec41[0] + fRec41[2]));
		double fTemp53 = (1.8508996845035413 * fRec41[1]);
		double fTemp54 = ((fTemp53 + fTemp52) / (double(Ranode(int(TUBE_TABLE_6V6_250k), double(fRec40[1]))) + 100000.0));
		fVec19[0] = fTemp54;
		fRec74[0] = (fConst71 * ((820.0 * (fTemp54 + fVec19[1])) - (fConst72 * fRec74[1])));
		fRec40[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double(((fTemp52 + (fRec74[0] + fTemp53)) + -1.1304620000000001)))) + -112.13878048780487);
		fRec39[0] = (fConst2 * ((fConst3 * fRec39[1]) + (0.025000000000000001 * (fRec40[0] - fRec40[1]))));
		output1[i0] = FAUSTFLOAT((0.77000000000000002 * fRec39[0]));
		fRec10[1] = fRec10[0];
		fRec24[1] = fRec24[0];
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
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fRec28[1] = fRec28[0];
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fVec2[1] = fVec2[0];
		fRec30[1] = fRec30[0];
		fRec29[2] = fRec29[1];
		fRec29[1] = fRec29[0];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fVec3[1] = fVec3[0];
		fRec16[1] = fRec16[0];
		fVec4[1] = fVec4[0];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fVec5[1] = fVec5[0];
		fRec35[1] = fRec35[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fVec6[1] = fVec6[0];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fVec7[1] = fVec7[0];
		fRec36[1] = fRec36[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec37[1] = fRec37[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fVec8[1] = fVec8[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fVec9[1] = fVec9[0];
		fRec38[1] = fRec38[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec61[2] = fRec61[1];
		fRec61[1] = fRec61[0];
		fVec10[1] = fVec10[0];
		fRec60[1] = fRec60[0];
		fRec59[1] = fRec59[0];
		fRec58[2] = fRec58[1];
		fRec58[1] = fRec58[0];
		fVec11[1] = fVec11[0];
		fRec57[1] = fRec57[0];
		fRec56[2] = fRec56[1];
		fRec56[1] = fRec56[0];
		fRec55[2] = fRec55[1];
		fRec55[1] = fRec55[0];
		fRec65[1] = fRec65[0];
		fRec64[2] = fRec64[1];
		fRec64[1] = fRec64[0];
		fRec63[2] = fRec63[1];
		fRec63[1] = fRec63[0];
		fRec62[2] = fRec62[1];
		fRec62[1] = fRec62[0];
		fRec69[1] = fRec69[0];
		fRec68[2] = fRec68[1];
		fRec68[1] = fRec68[0];
		fVec12[1] = fVec12[0];
		fRec67[1] = fRec67[0];
		fRec66[2] = fRec66[1];
		fRec66[1] = fRec66[0];
		fRec71[1] = fRec71[0];
		fRec70[2] = fRec70[1];
		fRec70[1] = fRec70[0];
		fVec13[1] = fVec13[0];
		fRec54[1] = fRec54[0];
		fVec14[1] = fVec14[0];
		fRec53[1] = fRec53[0];
		fRec52[2] = fRec52[1];
		fRec52[1] = fRec52[0];
		fVec15[1] = fVec15[0];
		fRec72[1] = fRec72[0];
		fRec51[1] = fRec51[0];
		fRec50[1] = fRec50[0];
		fRec49[1] = fRec49[0];
		fVec16[1] = fVec16[0];
		fRec48[1] = fRec48[0];
		fRec47[2] = fRec47[1];
		fRec47[1] = fRec47[0];
		fVec17[1] = fVec17[0];
		fRec73[1] = fRec73[0];
		fRec46[1] = fRec46[0];
		fRec45[1] = fRec45[0];
		fRec44[1] = fRec44[0];
		fRec43[2] = fRec43[1];
		fRec43[1] = fRec43[0];
		fVec18[1] = fVec18[0];
		fRec42[1] = fRec42[0];
		fRec41[2] = fRec41[1];
		fRec41[1] = fRec41[0];
		fVec19[1] = fVec19[0];
		fRec74[1] = fRec74[0];
		fRec40[1] = fRec40[0];
		fRec39[1] = fRec39[0];
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
		fVslider2_ = (float*)data; // , 100.0, 0.0, 100.0, 1.0 
		break;
	case PREGAIN: 
		fVslider0_ = (float*)data; // , -6.0, -20.0, 20.0, 0.10000000000000001 
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

} // end namespace gxamp2_stereo
