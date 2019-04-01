// generated from file '../src/LV2/faust/gxamp8.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#include "valve.h"

namespace gxamp8 {

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
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
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
	double fVec0[2];
	double fRec29[2];
	double fRec28[3];
	double fConst24;
	double fConst25;
	double fConst26;
	double fVec1[2];
	double fRec30[2];
	double fRec27[2];
	double fConst27;
	double fConst28;
	double fRec26[2];
	double fVec2[2];
	double fRec40[2];
	double fRec39[3];
	double fConst29;
	double fConst30;
	double fConst31;
	double fVec3[2];
	double fRec41[2];
	double fRec38[2];
	double fRec37[2];
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec46[2];
	double fConst36;
	double fConst37;
	double fConst38;
	double fVec4[2];
	double fConst39;
	double fRec50[2];
	double fRec49[2];
	double fConst40;
	double fConst41;
	double fRec48[3];
	double fConst42;
	double fConst43;
	double fRec47[3];
	double fVec5[2];
	double fRec45[2];
	double fRec44[3];
	double fConst44;
	double fConst45;
	double fConst46;
	double fVec6[2];
	double fRec51[2];
	double fRec43[2];
	double fRec42[2];
	double fRec36[2];
	double fRec35[2];
	double fVec7[2];
	double fRec34[2];
	double fRec33[3];
	double fVec8[2];
	double fRec52[2];
	double fRec32[2];
	double fRec31[2];
	double fRec25[2];
	double fVec9[2];
	double fRec24[2];
	double fRec23[3];
	double fVec10[2];
	double fRec53[2];
	double fRec22[2];
	double fRec21[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec54[2];
	double fRec55[2];
	int IOTA;
	double fVec11[32768];
	double fConst47;
	int iConst48;
	double fRec57[2];
	double fRec56[2];
	double fConst49;
	double fConst50;
	double fRec20[3];
	double fVec12[2];
	double fRec19[2];
	double fRec18[2];
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fRec17[3];
	double fVec13[2];
	double fConst55;
	double fConst56;
	double fConst57;
	double fRec16[2];
	double fConst58;
	double fConst59;
	double fRec15[3];
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst63;
	double fConst64;
	double fConst65;
	double fConst66;
	double fConst67;
	double fConst68;
	double fConst69;
	double fRec14[3];
	double fConst70;
	double fRec61[2];
	double fRec60[3];
	double fConst71;
	double fConst72;
	double fConst73;
	double fRec59[3];
	double fRec58[3];
	double fConst74;
	double fConst75;
	double fConst76;
	double fRec65[2];
	double fRec64[3];
	double fVec14[2];
	double fConst77;
	double fConst78;
	double fRec63[2];
	double fConst79;
	double fRec62[3];
	double fConst80;
	double fConst81;
	double fRec67[2];
	double fRec66[3];
	double fVec15[2];
	double fRec13[2];
	double fVec16[2];
	double fRec12[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec68[2];
	double fVec17[2];
	double fRec11[2];
	double fRec10[3];
	double fVec18[2];
	double fRec69[2];
	double fRec9[2];
	double fRec8[2];
	double fVec19[2];
	double fRec72[2];
	double fRec71[2];
	double fRec70[2];
	double fRec6[2];
	double fRec4[2];
	double fRec2[2];
	double fRec0[2];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
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
	id = "pre 12AU7/ push-pull 6V6";
	name = N_("pre 12AU7/ push-pull 6V6");
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
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec29[l1] = 0.0;
	for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) fRec28[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fVec1[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec30[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec27[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec26[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fVec2[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec40[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec39[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fVec3[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec41[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec38[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec37[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec46[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fVec4[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec50[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec49[l17] = 0.0;
	for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) fRec48[l18] = 0.0;
	for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) fRec47[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fVec5[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec45[l21] = 0.0;
	for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) fRec44[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fVec6[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec51[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fRec43[l25] = 0.0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fRec42[l26] = 0.0;
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) fRec36[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec35[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fVec7[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec34[l30] = 0.0;
	for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) fRec33[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fVec8[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fRec52[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec32[l34] = 0.0;
	for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) fRec31[l35] = 0.0;
	for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) fRec25[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fVec9[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fRec24[l38] = 0.0;
	for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) fRec23[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fVec10[l40] = 0.0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) fRec53[l41] = 0.0;
	for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) fRec22[l42] = 0.0;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fRec21[l43] = 0.0;
	for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) fRec54[l44] = 0.0;
	for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) fRec55[l45] = 0.0;
	for (int l46 = 0; (l46 < 32768); l46 = (l46 + 1)) fVec11[l46] = 0.0;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) fRec57[l47] = 0.0;
	for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) fRec56[l48] = 0.0;
	for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) fRec20[l49] = 0.0;
	for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) fVec12[l50] = 0.0;
	for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) fRec19[l51] = 0.0;
	for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) fRec18[l52] = 0.0;
	for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) fRec17[l53] = 0.0;
	for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) fVec13[l54] = 0.0;
	for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) fRec16[l55] = 0.0;
	for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) fRec15[l56] = 0.0;
	for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) fRec14[l57] = 0.0;
	for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) fRec61[l58] = 0.0;
	for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) fRec60[l59] = 0.0;
	for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) fRec59[l60] = 0.0;
	for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) fRec58[l61] = 0.0;
	for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) fRec65[l62] = 0.0;
	for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) fRec64[l63] = 0.0;
	for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) fVec14[l64] = 0.0;
	for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) fRec63[l65] = 0.0;
	for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) fRec62[l66] = 0.0;
	for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) fRec67[l67] = 0.0;
	for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) fRec66[l68] = 0.0;
	for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) fVec15[l69] = 0.0;
	for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) fRec13[l70] = 0.0;
	for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) fVec16[l71] = 0.0;
	for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) fRec12[l72] = 0.0;
	for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) fRec68[l73] = 0.0;
	for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) fVec17[l74] = 0.0;
	for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) fRec11[l75] = 0.0;
	for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) fRec10[l76] = 0.0;
	for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) fVec18[l77] = 0.0;
	for (int l78 = 0; (l78 < 2); l78 = (l78 + 1)) fRec69[l78] = 0.0;
	for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) fRec9[l79] = 0.0;
	for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) fRec8[l80] = 0.0;
	for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) fVec19[l81] = 0.0;
	for (int l82 = 0; (l82 < 2); l82 = (l82 + 1)) fRec72[l82] = 0.0;
	for (int l83 = 0; (l83 < 2); l83 = (l83 + 1)) fRec71[l83] = 0.0;
	for (int l84 = 0; (l84 < 2); l84 = (l84 + 1)) fRec70[l84] = 0.0;
	for (int l85 = 0; (l85 < 2); l85 = (l85 + 1)) fRec6[l85] = 0.0;
	for (int l86 = 0; (l86 < 2); l86 = (l86 + 1)) fRec4[l86] = 0.0;
	for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) fRec2[l87] = 0.0;
	for (int l88 = 0; (l88 < 2); l88 = (l88 + 1)) fRec0[l88] = 0.0;
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
	fConst8 = std::tan((3769.9111843077517 / fConst0));
	fConst9 = (1.0 / fConst8);
	fConst10 = (1.0 / (((fConst9 + 1.0000000000000004) / fConst8) + 1.0));
	fConst11 = mydsp_faustpower2_f(fConst8);
	fConst12 = (1.0 / fConst11);
	fConst13 = std::tan((10053.096491487338 / fConst0));
	fConst14 = (1.0 / fConst13);
	fConst15 = (1.0 / (((fConst14 + 1.0000000000000004) / fConst13) + 1.0));
	fConst16 = (fConst9 + 1.0);
	fConst17 = (1.0 / (fConst8 * fConst16));
	fConst18 = (fConst14 + 1.0);
	fConst19 = (1.0 / fConst18);
	fConst20 = (1.0 - fConst14);
	fConst21 = std::tan((47123.889803846898 / fConst0));
	fConst22 = (1.0 / fConst21);
	fConst23 = (1.0 / (((fConst22 + 1.4142135623730949) / fConst21) + 1.0));
	fConst24 = (1.0 / std::tan((609.46897479641984 / fConst0)));
	fConst25 = (1.0 / (fConst24 + 1.0));
	fConst26 = (1.0 - fConst24);
	fConst27 = (0.0 - fConst4);
	fConst28 = ((1.0 - fConst2) / fConst3);
	fConst29 = (1.0 / std::tan((414.69023027385271 / fConst0)));
	fConst30 = (1.0 / (fConst29 + 1.0));
	fConst31 = (1.0 - fConst29);
	fConst32 = std::tan((37699.111843077517 / fConst0));
	fConst33 = (1.0 / fConst32);
	fConst34 = (((fConst33 + 0.76536686473017945) / fConst32) + 1.0);
	fConst35 = (2.0 / fConst34);
	fConst36 = (1.0 / (((fConst33 + 1.8477590650225735) / fConst32) + 1.0));
	fConst37 = (973.89372261283586 / fConst0);
	fConst38 = (1.0 / (fConst37 + 1.0));
	fConst39 = (1.0 - fConst37);
	fConst40 = (((fConst33 + -1.8477590650225735) / fConst32) + 1.0);
	fConst41 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst32))));
	fConst42 = (1.0 / fConst34);
	fConst43 = (((fConst33 + -0.76536686473017945) / fConst32) + 1.0);
	fConst44 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst45 = (1.0 / (fConst44 + 1.0));
	fConst46 = (1.0 - fConst44);
	fConst47 = (0.009000000000000008 / fConst0);
	iConst48 = int(std::min<double>(65536.0, std::max<double>(0.0, (0.1111111111111111 * fConst0))));
	fConst49 = (((fConst22 + -1.4142135623730949) / fConst21) + 1.0);
	fConst50 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst21))));
	fConst51 = (((fConst14 + -1.0000000000000004) / fConst13) + 1.0);
	fConst52 = mydsp_faustpower2_f(fConst13);
	fConst53 = (1.0 / fConst52);
	fConst54 = (2.0 * (1.0 - fConst53));
	fConst55 = (0.0 - fConst17);
	fConst56 = (1.0 - fConst9);
	fConst57 = (fConst56 / fConst16);
	fConst58 = (((fConst9 + -1.0000000000000004) / fConst8) + 1.0);
	fConst59 = (2.0 * (1.0 - fConst12));
	fConst60 = (0.0 - (2.0 / fConst11));
	fConst61 = std::tan((942.47779607693792 / fConst0));
	fConst62 = (1.0 / fConst61);
	fConst63 = (fConst62 + 1.0);
	fConst64 = (1.0 / ((fConst63 / fConst61) + 1.0));
	fConst65 = (1.0 - fConst62);
	fConst66 = (1.0 - (fConst65 / fConst61));
	fConst67 = mydsp_faustpower2_f(fConst61);
	fConst68 = (1.0 / fConst67);
	fConst69 = (2.0 * (1.0 - fConst68));
	fConst70 = (0.0 - (1.0 / (fConst18 * fConst13)));
	fConst71 = (0.0 - (2.0 / fConst52));
	fConst72 = (1.0 / ((fConst16 / fConst8) + 1.0));
	fConst73 = (1.0 - (fConst56 / fConst8));
	fConst74 = (1.0 / (((fConst62 + 1.0000000000000004) / fConst61) + 1.0));
	fConst75 = (1.0 / (fConst61 * fConst63));
	fConst76 = (1.0 / fConst16);
	fConst77 = (0.0 - fConst75);
	fConst78 = (fConst65 / fConst63);
	fConst79 = (((fConst62 + -1.0000000000000004) / fConst61) + 1.0);
	fConst80 = (0.0 - (2.0 / fConst67));
	fConst81 = (1.0 / fConst63);
	fVslider0 = FAUSTFLOAT(0.34999999999999998);
	fVslider1 = FAUSTFLOAT(-6.0);
	fVslider2 = FAUSTFLOAT(100.0);
	fVslider3 = FAUSTFLOAT(-6.0);
			IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
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
	double fSlow7 = (fConst74 * std::pow(10.0, (2.0 * fSlow0)));
	double fSlow8 = (fConst74 * std::pow(10.0, (0.90000000000000002 * fSlow0)));
	double fSlow9 = (1.25 * fSlow0);
	double fSlow10 = (0.024937655860349125 * (1.0 - std::max<double>(0.0, fSlow1)));
	double fSlow11 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider3))));
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = (fRec25[1] + 1.0000000000000001e-15);
		fVec0[0] = fTemp0;
		fRec29[0] = ((0.93028479253239138 * (fTemp0 + fVec0[1])) - (0.86056958506478287 * fRec29[1]));
		fRec28[0] = (fRec29[0] - ((1.8405051250752198 * fRec28[1]) + (0.86129424393186271 * fRec28[2])));
		double fTemp1 = ((0.0082000000000000007 * fRec27[1]) + 1.0000000000000001e-15);
		fVec1[0] = fTemp1;
		fRec30[0] = (0.0 - (fConst25 * ((fConst26 * fRec30[1]) - (fTemp1 + fVec1[1]))));
		fRec27[0] = (double(Ftube(int(TUBE_TABLE_12AU7_250k), double((((0.92544984225177063 * (fRec28[0] + fRec28[2])) + (fRec30[0] + (1.8508996845035413 * fRec28[1]))) + -0.44548700000000002)))) + -75.672317073170731);
		fRec26[0] = ((0.10000000000000001 * ((fConst4 * fRec27[0]) + (fConst27 * fRec27[1]))) - (fConst28 * fRec26[1]));
		double fTemp2 = (fRec36[1] + 1.0000000000000001e-15);
		fVec2[0] = fTemp2;
		fRec40[0] = ((0.93028479253239138 * (fTemp2 + fVec2[1])) - (0.86056958506478287 * fRec40[1]));
		fRec39[0] = (fRec40[0] - ((1.8405051250752198 * fRec39[1]) + (0.86129424393186271 * fRec39[2])));
		double fTemp3 = ((0.014999999999999999 * fRec38[1]) + 1.0000000000000001e-15);
		fVec3[0] = fTemp3;
		fRec41[0] = (0.0 - (fConst30 * ((fConst31 * fRec41[1]) - (fTemp3 + fVec3[1]))));
		fRec38[0] = (double(Ftube(int(TUBE_TABLE_12AU7_250k), double((((0.92544984225177063 * (fRec39[0] + fRec39[2])) + (fRec41[0] + (1.8508996845035413 * fRec39[1]))) + -0.77616200000000002)))) + -78.255866666666662);
		fRec37[0] = ((0.10000000000000001 * ((fConst4 * fRec38[0]) + (fConst27 * fRec38[1]))) - (fConst28 * fRec37[1]));
		fRec46[0] = (fSlow4 + (0.999 * fRec46[1]));
		double fTemp4 = double(input0[i]);
		fVec4[0] = fTemp4;
		fRec50[0] = (fConst38 * ((fTemp4 - fVec4[1]) + (fConst39 * fRec50[1])));
		fRec49[0] = (fConst38 * ((fRec50[0] - fRec50[1]) + (fConst39 * fRec49[1])));
		fRec48[0] = (fRec49[0] - (fConst36 * ((fConst40 * fRec48[2]) + (fConst41 * fRec48[1]))));
		fRec47[0] = ((fConst36 * (fRec48[2] + (fRec48[0] + (2.0 * fRec48[1])))) - (fConst42 * ((fConst43 * fRec47[2]) + (fConst41 * fRec47[1]))));
		double fTemp5 = ((fConst35 * (fRec46[0] * (fRec47[2] + (fRec47[0] + (2.0 * fRec47[1]))))) + 1.0000000000000001e-15);
		fVec5[0] = fTemp5;
		fRec45[0] = ((0.93028479253239138 * (fTemp5 + fVec5[1])) - (0.86056958506478287 * fRec45[1]));
		fRec44[0] = (fRec45[0] - ((1.8405051250752198 * fRec44[1]) + (0.86129424393186271 * fRec44[2])));
		double fTemp6 = ((0.027 * fRec43[1]) + 1.0000000000000001e-15);
		fVec6[0] = fTemp6;
		fRec51[0] = (0.0 - (fConst45 * ((fConst46 * fRec51[1]) - (fTemp6 + fVec6[1]))));
		fRec43[0] = (double(Ftube(int(TUBE_TABLE_12AU7_68k), double((((0.92544984225177063 * (fRec44[0] + fRec44[2])) + (fRec51[0] + (1.8508996845035413 * fRec44[1]))) + -1.2572399999999999)))) + -83.435555555555567);
		fRec42[0] = ((0.10000000000000001 * ((fConst4 * fRec43[0]) + (fConst27 * fRec43[1]))) - (fConst28 * fRec42[1]));
		fRec36[0] = ((0.59999999999999998 * fRec37[0]) + fRec42[0]);
		fRec35[0] = (0.0 - (fConst6 * ((fConst7 * fRec35[1]) - (fRec36[0] + fRec36[1]))));
		double fTemp7 = (fRec35[0] + 1.0000000000000001e-15);
		fVec7[0] = fTemp7;
		fRec34[0] = ((0.93028479253239138 * (fTemp7 + fVec7[1])) - (0.86056958506478287 * fRec34[1]));
		fRec33[0] = (fRec34[0] - ((1.8405051250752198 * fRec33[1]) + (0.86129424393186271 * fRec33[2])));
		double fTemp8 = ((0.014999999999999999 * fRec32[1]) + 1.0000000000000001e-15);
		fVec8[0] = fTemp8;
		fRec52[0] = (0.0 - (fConst30 * ((fConst31 * fRec52[1]) - (fTemp8 + fVec8[1]))));
		fRec32[0] = (double(Ftube(int(TUBE_TABLE_12AU7_250k), double((((0.92544984225177063 * (fRec33[0] + fRec33[2])) + (fRec52[0] + (1.8508996845035413 * fRec33[1]))) + -0.77616200000000002)))) + -78.255866666666662);
		fRec31[0] = ((0.10000000000000001 * ((fConst4 * fRec32[0]) + (fConst27 * fRec32[1]))) - (fConst28 * fRec31[1]));
		fRec25[0] = ((0.59999999999999998 * fRec26[0]) + fRec31[0]);
		double fTemp9 = (fRec25[0] + 1.0000000000000001e-15);
		fVec9[0] = fTemp9;
		fRec24[0] = ((0.93028479253239138 * (fTemp9 + fVec9[1])) - (0.86056958506478287 * fRec24[1]));
		fRec23[0] = (fRec24[0] - ((1.8405051250752198 * fRec23[1]) + (0.86129424393186271 * fRec23[2])));
		double fTemp10 = ((0.0082000000000000007 * fRec22[1]) + 1.0000000000000001e-15);
		fVec10[0] = fTemp10;
		fRec53[0] = (0.0 - (fConst25 * ((fConst26 * fRec53[1]) - (fTemp10 + fVec10[1]))));
		fRec22[0] = (double(Ftube(int(TUBE_TABLE_12AU7_250k), double((((0.92544984225177063 * (fRec23[0] + fRec23[2])) + (fRec53[0] + (1.8508996845035413 * fRec23[1]))) + -0.44548700000000002)))) + -75.672317073170731);
		fRec21[0] = ((0.10000000000000001 * ((fConst4 * fRec22[0]) + (fConst27 * fRec22[1]))) - (fConst28 * fRec21[1]));
		fRec54[0] = (fSlow5 + (0.999 * fRec54[1]));
		double fTemp11 = (fRec21[0] * fRec54[0]);
		double fTemp12 = std::fabs(fTemp11);
		fRec55[0] = ((0.99990000000000001 * fRec55[1]) + (9.9999999999988987e-05 * fTemp12));
		double fTemp13 = std::max<double>(fRec55[0], fTemp12);
		fVec11[(IOTA & 32767)] = fTemp13;
		fRec57[0] = ((fTemp13 + fRec57[1]) - fVec11[((IOTA - iConst48) & 32767)]);
		fRec56[0] = ((0.999 * fRec56[1]) + (fConst47 * fRec57[0]));
		double fTemp14 = std::max<double>(-1.0, std::min<double>(-0.01, (fTemp13 + (-1.0 - (1.02 * fRec56[0])))));
		double fTemp15 = (fTemp11 - fTemp14);
		double fTemp16 = (40.100000000000001 * fTemp15);
		double fTemp17 = std::max<double>(-600.0, fTemp16);
		double fTemp18 = (0.0 - (40.100000000000001 * fTemp14));
		double fTemp19 = std::max<double>(-600.0, fTemp18);
		double fTemp20 = (((std::fabs(fTemp16) > 0.0001)?((fTemp17 < -50.0)?(0.0 - (fTemp17 * std::exp(fTemp17))):(fTemp17 / (1.0 - std::exp((-1.0 * fTemp17))))):((fTemp15 * ((134.00083333333336 * fTemp15) + 20.050000000000001)) + 1.0)) - ((std::fabs(fTemp18) > 0.0001)?((fTemp19 < -50.0)?(0.0 - (fTemp19 * std::exp(fTemp19))):(fTemp19 / (1.0 - std::exp((-1.0 * fTemp19))))):((fTemp18 * ((0.083333333333333329 * fTemp18) + 0.5)) + 1.0)));
		fRec20[0] = ((0.024937655860349125 * fTemp20) - (fConst23 * ((fConst49 * fRec20[2]) + (fConst50 * fRec20[1]))));
		double fTemp21 = (fRec20[2] + (fRec20[0] + (2.0 * fRec20[1])));
		fVec12[0] = fTemp21;
		fRec19[0] = ((fConst23 * ((fConst4 * fTemp21) + (fConst27 * fVec12[1]))) - (fConst28 * fRec19[1]));
		fRec18[0] = (0.0 - (fConst19 * ((fConst20 * fRec18[1]) - (fRec19[0] + fRec19[1]))));
		fRec17[0] = (fRec18[0] - (fConst15 * ((fConst51 * fRec17[2]) + (fConst54 * fRec17[1]))));
		double fTemp22 = (fRec17[2] + (fRec17[0] + (2.0 * fRec17[1])));
		fVec13[0] = fTemp22;
		fRec16[0] = ((fConst15 * ((fConst17 * fTemp22) + (fConst55 * fVec13[1]))) - (fConst57 * fRec16[1]));
		fRec15[0] = (fRec16[0] - (fConst10 * ((fConst58 * fRec15[2]) + (fConst59 * fRec15[1]))));
		double fTemp23 = (fConst69 * fRec14[1]);
		fRec14[0] = ((fConst10 * (((fConst12 * fRec15[0]) + (fConst60 * fRec15[1])) + (fConst12 * fRec15[2]))) - (fConst64 * ((fConst66 * fRec14[2]) + fTemp23)));
		double fTemp24 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow3 * (fRec14[2] + (fConst64 * (fTemp23 + (fConst66 * fRec14[0])))))));
		fRec61[0] = ((fConst70 * fRec19[1]) - (fConst19 * ((fConst20 * fRec61[1]) - (fConst14 * fRec19[0]))));
		fRec60[0] = (fRec61[0] - (fConst15 * ((fConst51 * fRec60[2]) + (fConst54 * fRec60[1]))));
		double fTemp25 = (fConst59 * fRec59[1]);
		fRec59[0] = ((fConst15 * (((fConst53 * fRec60[0]) + (fConst71 * fRec60[1])) + (fConst53 * fRec60[2]))) - (fConst72 * ((fConst73 * fRec59[2]) + fTemp25)));
		double fTemp26 = (fConst69 * fRec58[1]);
		fRec58[0] = ((fRec59[2] + (fConst72 * (fTemp25 + (fConst73 * fRec59[0])))) - (fConst64 * ((fConst66 * fRec58[2]) + fTemp26)));
		double fTemp27 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow6 * (fRec58[2] + (fConst64 * (fTemp26 + (fConst66 * fRec58[0])))))));
		fRec65[0] = (0.0 - (fConst76 * ((fConst56 * fRec65[1]) - (fConst15 * (fTemp22 + fVec13[1])))));
		fRec64[0] = (fRec65[0] - (fConst10 * ((fConst58 * fRec64[2]) + (fConst59 * fRec64[1]))));
		double fTemp28 = (fRec64[2] + (fRec64[0] + (2.0 * fRec64[1])));
		fVec14[0] = fTemp28;
		fRec63[0] = ((fConst10 * ((fConst75 * fTemp28) + (fConst77 * fVec14[1]))) - (fConst78 * fRec63[1]));
		fRec62[0] = (fRec63[0] - (fConst74 * ((fConst79 * fRec62[2]) + (fConst69 * fRec62[1]))));
		double fTemp29 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow7 * (((fConst68 * fRec62[0]) + (fConst80 * fRec62[1])) + (fConst68 * fRec62[2])))));
		fRec67[0] = (0.0 - (fConst81 * ((fConst65 * fRec67[1]) - (fConst10 * (fTemp28 + fVec14[1])))));
		fRec66[0] = (fRec67[0] - (fConst74 * ((fConst79 * fRec66[2]) + (fConst69 * fRec66[1]))));
		double fTemp30 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow8 * (fRec66[2] + (fRec66[0] + (2.0 * fRec66[1]))))));
		double fTemp31 = (((1.333521432 * (fTemp24 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp24))))) + (1.584893192 * ((fTemp27 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp27)))) + (fTemp29 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp29))))))) + (1.2589412 * (fTemp30 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp30))))));
		fVec15[0] = fTemp31;
		fRec13[0] = (0.0 - (fConst6 * ((fConst7 * fRec13[1]) - (fTemp31 + fVec15[1]))));
		double fTemp32 = (fRec21[0] * (1.0 - fRec54[0]));
		double fTemp33 = ((fSlow2 * fRec13[0]) + ((fTemp32 * ((fSlow9 * ((4.0 * (1.0 - std::fabs(fTemp32))) + -1.0)) + 1.0)) + (fSlow10 * fTemp20)));
		fVec16[0] = fTemp33;
		fRec12[0] = (0.0 - (fConst6 * ((fConst7 * fRec12[1]) - (fTemp33 + fVec16[1]))));
		fRec68[0] = (fSlow11 + (0.999 * fRec68[1]));
		double fTemp34 = ((fRec12[0] * fRec68[0]) + 1.0000000000000001e-15);
		fVec17[0] = fTemp34;
		fRec11[0] = ((0.93028479253239138 * (fTemp34 + fVec17[1])) - (0.86056958506478287 * fRec11[1]));
		fRec10[0] = (fRec11[0] - ((1.8405051250752198 * fRec10[1]) + (0.86129424393186271 * fRec10[2])));
		double fTemp35 = (0.92544984225177063 * (fRec10[0] + fRec10[2]));
		double fTemp36 = ((0.0041000000000000003 * fRec9[1]) + 1.0000000000000001e-15);
		fVec18[0] = fTemp36;
		fRec69[0] = (0.0 - (fConst6 * ((fConst7 * fRec69[1]) - (fTemp36 + fVec18[1]))));
		double fTemp37 = (1.8508996845035413 * fRec10[1]);
		fRec9[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double(((fTemp35 + (fRec69[0] + fTemp37)) + -0.65976100000000004)))) + -89.08268292682925);
		fRec8[0] = ((0.025000000000000001 * ((fConst4 * fRec9[0]) + (fConst27 * fRec9[1]))) - (fConst28 * fRec8[1]));
		double fTemp38 = ((0.0041000000000000003 * fRec71[1]) + 1.0000000000000001e-15);
		fVec19[0] = fTemp38;
		fRec72[0] = (0.0 - (fConst6 * ((fConst7 * fRec72[1]) - (fTemp38 + fVec19[1]))));
		fRec71[0] = (double(Ftube(int(TUBE_TABLE_6V6_68k), double(((fTemp35 + (fRec72[0] + fTemp37)) + -0.66454100000000005)))) + -87.916829268292673);
		fRec70[0] = ((0.025000000000000001 * ((fConst4 * fRec71[0]) + (fConst27 * fRec71[1]))) - (fConst28 * fRec70[1]));
		double fTemp39 = (std::min<double>(0.69999999999999996, fRec8[0]) + std::max<double>(-0.75, fRec70[0]));
		double fTemp40 = (0.5 * fRec0[1]);
		double fTemp41 = (0.40000000000000002 * fRec2[1]);
		double fTemp42 = (fTemp40 + ((0.29999999999999999 * fRec4[1]) + fTemp41));
		double fTemp43 = ((fTemp39 + (0.20000000000000001 * fRec6[1])) - fTemp42);
		fRec6[0] = fTemp43;
		double fRec7 = (0.0 - (0.20000000000000001 * fTemp43));
		fRec4[0] = (fRec7 + fRec6[1]);
		double fRec5 = (0.29999999999999999 * (fTemp39 - fTemp42));
		fRec2[0] = (fRec5 + fRec4[1]);
		double fRec3 = (0.40000000000000002 * (fTemp39 - (fTemp41 + fTemp40)));
		fRec0[0] = (fRec3 + fRec2[1]);
		double fRec1 = (0.5 * (fTemp39 - fTemp40));
		output0[i] = FAUSTFLOAT((fRec1 + fRec0[1]));
		fVec0[1] = fVec0[0];
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fVec1[1] = fVec1[0];
		fRec30[1] = fRec30[0];
		fRec27[1] = fRec27[0];
		fRec26[1] = fRec26[0];
		fVec2[1] = fVec2[0];
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fVec3[1] = fVec3[0];
		fRec41[1] = fRec41[0];
		fRec38[1] = fRec38[0];
		fRec37[1] = fRec37[0];
		fRec46[1] = fRec46[0];
		fVec4[1] = fVec4[0];
		fRec50[1] = fRec50[0];
		fRec49[1] = fRec49[0];
		fRec48[2] = fRec48[1];
		fRec48[1] = fRec48[0];
		fRec47[2] = fRec47[1];
		fRec47[1] = fRec47[0];
		fVec5[1] = fVec5[0];
		fRec45[1] = fRec45[0];
		fRec44[2] = fRec44[1];
		fRec44[1] = fRec44[0];
		fVec6[1] = fVec6[0];
		fRec51[1] = fRec51[0];
		fRec43[1] = fRec43[0];
		fRec42[1] = fRec42[0];
		fRec36[1] = fRec36[0];
		fRec35[1] = fRec35[0];
		fVec7[1] = fVec7[0];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fVec8[1] = fVec8[0];
		fRec52[1] = fRec52[0];
		fRec32[1] = fRec32[0];
		fRec31[1] = fRec31[0];
		fRec25[1] = fRec25[0];
		fVec9[1] = fVec9[0];
		fRec24[1] = fRec24[0];
		fRec23[2] = fRec23[1];
		fRec23[1] = fRec23[0];
		fVec10[1] = fVec10[0];
		fRec53[1] = fRec53[0];
		fRec22[1] = fRec22[0];
		fRec21[1] = fRec21[0];
		fRec54[1] = fRec54[0];
		fRec55[1] = fRec55[0];
		IOTA = (IOTA + 1);
		fRec57[1] = fRec57[0];
		fRec56[1] = fRec56[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fVec12[1] = fVec12[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fVec13[1] = fVec13[0];
		fRec16[1] = fRec16[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fRec61[1] = fRec61[0];
		fRec60[2] = fRec60[1];
		fRec60[1] = fRec60[0];
		fRec59[2] = fRec59[1];
		fRec59[1] = fRec59[0];
		fRec58[2] = fRec58[1];
		fRec58[1] = fRec58[0];
		fRec65[1] = fRec65[0];
		fRec64[2] = fRec64[1];
		fRec64[1] = fRec64[0];
		fVec14[1] = fVec14[0];
		fRec63[1] = fRec63[0];
		fRec62[2] = fRec62[1];
		fRec62[1] = fRec62[0];
		fRec67[1] = fRec67[0];
		fRec66[2] = fRec66[1];
		fRec66[1] = fRec66[0];
		fVec15[1] = fVec15[0];
		fRec13[1] = fRec13[0];
		fVec16[1] = fVec16[0];
		fRec12[1] = fRec12[0];
		fRec68[1] = fRec68[0];
		fVec17[1] = fVec17[0];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fVec18[1] = fVec18[0];
		fRec69[1] = fRec69[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fVec19[1] = fVec19[0];
		fRec72[1] = fRec72[0];
		fRec71[1] = fRec71[0];
		fRec70[1] = fRec70[0];
		fRec6[1] = fRec6[0];
		fRec4[1] = fRec4[0];
		fRec2[1] = fRec2[0];
		fRec0[1] = fRec0[0];
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
#undef fVslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
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

} // end namespace gxamp8
