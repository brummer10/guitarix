// generated from file '../src/LV2/faust/gxamp7.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxamp7 {

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
	double fRec12[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	double fRec25[2];
	double fRec24[3];
	double fConst4;
	double fConst5;
	double fVec0[2];
	double fConst6;
	double fRec26[2];
	double fRec23[2];
	double fConst7;
	double fConst8;
	double fRec22[2];
	double fConst9;
	double fConst10;
	double fConst11;
	double fRec27[2];
	double fRec37[2];
	double fRec36[3];
	double fConst12;
	double fConst13;
	double fVec1[2];
	double fConst14;
	double fRec38[2];
	double fRec35[2];
	double fRec34[2];
	double fRec39[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec44[2];
	double fVec2[2];
	double fRec43[2];
	double fRec42[3];
	double fConst15;
	double fConst16;
	double fVec3[2];
	double fConst17;
	double fRec45[2];
	double fRec41[2];
	double fRec40[2];
	double fRec46[2];
	double fRec33[3];
	double fConst18;
	double fConst19;
	double fConst20;
	double fRec32[2];
	double fRec31[2];
	double fRec30[3];
	double fVec4[2];
	double fRec47[2];
	double fRec29[2];
	double fRec28[2];
	double fRec48[2];
	double fRec21[3];
	double fRec20[2];
	double fRec19[3];
	double fVec5[2];
	double fRec49[2];
	double fRec18[2];
	double fRec17[2];
	double fRec50[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec51[2];
	double fRec16[2];
	int IOTA0;
	double fVec6[32768];
	int iConst21;
	double fRec15[2];
	double fConst22;
	double fRec14[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
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
	double fConst48;
	double fConst49;
	double fRec60[3];
	double fVec7[2];
	double fConst50;
	double fRec59[2];
	double fConst51;
	double fConst52;
	double fRec58[2];
	double fRec57[3];
	double fVec8[2];
	double fConst53;
	double fConst54;
	double fConst55;
	double fRec56[2];
	double fRec55[3];
	double fVec9[2];
	double fConst56;
	double fConst57;
	double fConst58;
	double fRec54[2];
	double fRec53[3];
	double fConst59;
	double fRec62[2];
	double fRec61[3];
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst63;
	double fConst64;
	double fRec66[2];
	double fRec65[3];
	double fConst65;
	double fRec64[3];
	double fRec63[3];
	double fConst66;
	double fRec69[2];
	double fRec68[3];
	double fConst67;
	double fRec67[3];
	double fVec10[2];
	double fRec52[2];
	double fVec11[2];
	double fRec13[2];
	double fVec12[2];
	double fRec11[2];
	double fRec10[3];
	double fVec13[2];
	double fRec70[2];
	double fRec9[2];
	double fRec8[2];
	double fRec71[2];
	double fVec14[2];
	double fRec74[2];
	double fRec73[2];
	double fRec72[2];
	double fRec75[2];
	double fRec6[2];
	double fRec4[2];
	double fRec2[2];
	double fRec0[2];

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
	id = "pre 12ax7/ push-pull 6V6";
	name = N_("pre 12ax7/ push-pull 6V6");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec12[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec25[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRec24[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fVec0[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec26[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec23[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec22[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec27[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec37[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec36[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fVec1[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec38[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec35[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec34[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec39[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec44[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fVec2[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec43[l17] = 0.0;
	for (int l18 = 0; l18 < 3; l18 = l18 + 1) fRec42[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fVec3[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec45[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec41[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec40[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec46[l23] = 0.0;
	for (int l24 = 0; l24 < 3; l24 = l24 + 1) fRec33[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec32[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec31[l26] = 0.0;
	for (int l27 = 0; l27 < 3; l27 = l27 + 1) fRec30[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fVec4[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec47[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec29[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec28[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fRec48[l32] = 0.0;
	for (int l33 = 0; l33 < 3; l33 = l33 + 1) fRec21[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fRec20[l34] = 0.0;
	for (int l35 = 0; l35 < 3; l35 = l35 + 1) fRec19[l35] = 0.0;
	for (int l36 = 0; l36 < 2; l36 = l36 + 1) fVec5[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec49[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fRec18[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec17[l39] = 0.0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec50[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec51[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) fRec16[l42] = 0.0;
	for (int l43 = 0; l43 < 32768; l43 = l43 + 1) fVec6[l43] = 0.0;
	for (int l44 = 0; l44 < 2; l44 = l44 + 1) fRec15[l44] = 0.0;
	for (int l45 = 0; l45 < 2; l45 = l45 + 1) fRec14[l45] = 0.0;
	for (int l46 = 0; l46 < 3; l46 = l46 + 1) fRec60[l46] = 0.0;
	for (int l47 = 0; l47 < 2; l47 = l47 + 1) fVec7[l47] = 0.0;
	for (int l48 = 0; l48 < 2; l48 = l48 + 1) fRec59[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec58[l49] = 0.0;
	for (int l50 = 0; l50 < 3; l50 = l50 + 1) fRec57[l50] = 0.0;
	for (int l51 = 0; l51 < 2; l51 = l51 + 1) fVec8[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fRec56[l52] = 0.0;
	for (int l53 = 0; l53 < 3; l53 = l53 + 1) fRec55[l53] = 0.0;
	for (int l54 = 0; l54 < 2; l54 = l54 + 1) fVec9[l54] = 0.0;
	for (int l55 = 0; l55 < 2; l55 = l55 + 1) fRec54[l55] = 0.0;
	for (int l56 = 0; l56 < 3; l56 = l56 + 1) fRec53[l56] = 0.0;
	for (int l57 = 0; l57 < 2; l57 = l57 + 1) fRec62[l57] = 0.0;
	for (int l58 = 0; l58 < 3; l58 = l58 + 1) fRec61[l58] = 0.0;
	for (int l59 = 0; l59 < 2; l59 = l59 + 1) fRec66[l59] = 0.0;
	for (int l60 = 0; l60 < 3; l60 = l60 + 1) fRec65[l60] = 0.0;
	for (int l61 = 0; l61 < 3; l61 = l61 + 1) fRec64[l61] = 0.0;
	for (int l62 = 0; l62 < 3; l62 = l62 + 1) fRec63[l62] = 0.0;
	for (int l63 = 0; l63 < 2; l63 = l63 + 1) fRec69[l63] = 0.0;
	for (int l64 = 0; l64 < 3; l64 = l64 + 1) fRec68[l64] = 0.0;
	for (int l65 = 0; l65 < 3; l65 = l65 + 1) fRec67[l65] = 0.0;
	for (int l66 = 0; l66 < 2; l66 = l66 + 1) fVec10[l66] = 0.0;
	for (int l67 = 0; l67 < 2; l67 = l67 + 1) fRec52[l67] = 0.0;
	for (int l68 = 0; l68 < 2; l68 = l68 + 1) fVec11[l68] = 0.0;
	for (int l69 = 0; l69 < 2; l69 = l69 + 1) fRec13[l69] = 0.0;
	for (int l70 = 0; l70 < 2; l70 = l70 + 1) fVec12[l70] = 0.0;
	for (int l71 = 0; l71 < 2; l71 = l71 + 1) fRec11[l71] = 0.0;
	for (int l72 = 0; l72 < 3; l72 = l72 + 1) fRec10[l72] = 0.0;
	for (int l73 = 0; l73 < 2; l73 = l73 + 1) fVec13[l73] = 0.0;
	for (int l74 = 0; l74 < 2; l74 = l74 + 1) fRec70[l74] = 0.0;
	for (int l75 = 0; l75 < 2; l75 = l75 + 1) fRec9[l75] = 0.0;
	for (int l76 = 0; l76 < 2; l76 = l76 + 1) fRec8[l76] = 0.0;
	for (int l77 = 0; l77 < 2; l77 = l77 + 1) fRec71[l77] = 0.0;
	for (int l78 = 0; l78 < 2; l78 = l78 + 1) fVec14[l78] = 0.0;
	for (int l79 = 0; l79 < 2; l79 = l79 + 1) fRec74[l79] = 0.0;
	for (int l80 = 0; l80 < 2; l80 = l80 + 1) fRec73[l80] = 0.0;
	for (int l81 = 0; l81 < 2; l81 = l81 + 1) fRec72[l81] = 0.0;
	for (int l82 = 0; l82 < 2; l82 = l82 + 1) fRec75[l82] = 0.0;
	for (int l83 = 0; l83 < 2; l83 = l83 + 1) fRec6[l83] = 0.0;
	for (int l84 = 0; l84 < 2; l84 = l84 + 1) fRec4[l84] = 0.0;
	for (int l85 = 0; l85 < 2; l85 = l85 + 1) fRec2[l85] = 0.0;
	for (int l86 = 0; l86 < 2; l86 = l86 + 1) fRec0[l86] = 0.0;
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
	fConst4 = 1.0 / std::tan(609.4689747964198 / fConst0);
	fConst5 = 1.0 - fConst4;
	fConst6 = 1.0 / (fConst4 + 1.0);
	fConst7 = 0.025 / fConst1;
	fConst8 = 1.0 / (fConst2 + 1.0);
	fConst9 = 3.141592653589793 / fConst0;
	fConst10 = 1.0 - fConst9;
	fConst11 = 1.0 / (fConst9 + 1.0);
	fConst12 = 1.0 / std::tan(414.6902302738527 / fConst0);
	fConst13 = 1.0 - fConst12;
	fConst14 = 1.0 / (fConst12 + 1.0);
	fConst15 = 1.0 / std::tan(270.1769682087222 / fConst0);
	fConst16 = 1.0 - fConst15;
	fConst17 = 1.0 / (fConst15 + 1.0);
	fConst18 = 1.0 / std::tan(20517.741620594938 / fConst0);
	fConst19 = 1.0 - fConst18;
	fConst20 = 1.0 / (fConst18 + 1.0);
	iConst21 = int(std::min<double>(65536.0, std::max<double>(0.0, 0.1111111111111111 * fConst0)));
	fConst22 = 0.009000000000000008 / fConst0;
	fConst23 = std::tan(942.4777960769379 / fConst0);
	fConst24 = mydsp_faustpower2_f(fConst23);
	fConst25 = 2.0 * (1.0 - 1.0 / fConst24);
	fConst26 = 1.0 / fConst23;
	fConst27 = (fConst26 + -1.0000000000000004) / fConst23 + 1.0;
	fConst28 = (fConst26 + 1.0000000000000004) / fConst23 + 1.0;
	fConst29 = 1.0 / fConst28;
	fConst30 = std::tan(3769.9111843077517 / fConst0);
	fConst31 = mydsp_faustpower2_f(fConst30);
	fConst32 = 2.0 * (1.0 - 1.0 / fConst31);
	fConst33 = 1.0 / fConst30;
	fConst34 = (fConst33 + -1.0000000000000004) / fConst30 + 1.0;
	fConst35 = (fConst33 + 1.0000000000000004) / fConst30 + 1.0;
	fConst36 = 1.0 / fConst35;
	fConst37 = std::tan(10053.096491487338 / fConst0);
	fConst38 = mydsp_faustpower2_f(fConst37);
	fConst39 = 2.0 * (1.0 - 1.0 / fConst38);
	fConst40 = 1.0 / fConst37;
	fConst41 = (fConst40 + -1.0000000000000004) / fConst37 + 1.0;
	fConst42 = (fConst40 + 1.0000000000000004) / fConst37 + 1.0;
	fConst43 = 1.0 / fConst42;
	fConst44 = std::tan(47123.8898038469 / fConst0);
	fConst45 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst44));
	fConst46 = 1.0 / fConst44;
	fConst47 = (fConst46 + -1.414213562373095) / fConst44 + 1.0;
	fConst48 = (fConst46 + 1.414213562373095) / fConst44 + 1.0;
	fConst49 = 1.0 / fConst48;
	fConst50 = 1.0 / (fConst1 * fConst48);
	fConst51 = 1.0 - fConst40;
	fConst52 = 1.0 / (fConst40 + 1.0);
	fConst53 = 1.0 - fConst33;
	fConst54 = fConst33 + 1.0;
	fConst55 = 1.0 / fConst54;
	fConst56 = 1.0 - fConst26;
	fConst57 = fConst26 + 1.0;
	fConst58 = 1.0 / fConst57;
	fConst59 = 1.0 / (fConst23 * fConst35);
	fConst60 = 1.0 / (fConst24 * fConst28);
	fConst61 = 1.0 - fConst56 / fConst23;
	fConst62 = 1.0 / (fConst57 / fConst23 + 1.0);
	fConst63 = 1.0 - fConst53 / fConst30;
	fConst64 = 1.0 / (fConst54 / fConst30 + 1.0);
	fConst65 = 1.0 / (fConst38 * fConst42);
	fConst66 = 1.0 / (fConst30 * fConst42);
	fConst67 = 1.0 / (fConst31 * fConst35);
	IOTA0 = 0;
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
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
	double fSlow7 = 0.024937655860349125 * (1.0 - std::max<double>(0.0, fSlow6));
	double fSlow8 = 1.25 * fSlow5;
	double fSlow9 = fConst29 * std::pow(1e+01, 0.9 * fSlow5);
	double fSlow10 = fConst60 * std::pow(1e+01, 2.0 * fSlow5);
	double fSlow11 = std::pow(1e+01, 0.8 * fSlow5);
	double fSlow12 = std::pow(1e+01, 1.2 * fSlow5);
	double fSlow13 = 1.0 - std::max<double>(0.0, -fSlow6);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = 0.4 * fRec2[1];
		double fTemp1 = 0.5 * fRec0[1];
		double fTemp2 = fTemp1 + 0.3 * fRec4[1] + fTemp0;
		fRec12[0] = fSlow1 + 0.999 * fRec12[1];
		fRec25[0] = 0.9302847925323914 * (fRec21[1] + fRec21[2]) - 0.8605695850647829 * fRec25[1];
		fRec24[0] = fRec25[0] - (1.8405051250752198 * fRec24[1] + 0.8612942439318627 * fRec24[2]);
		double fTemp3 = 1.8508996845035413 * fRec24[1];
		double fTemp4 = 0.9254498422517706 * (fRec24[0] + fRec24[2]);
		double fTemp5 = (fTemp3 + fTemp4) / (Ranode(TUBE_TABLE_12AX7_250k, fRec23[1]) + 1e+05);
		fVec0[0] = fTemp5;
		fRec26[0] = fConst6 * (8.2e+02 * (fTemp5 + fVec0[1]) - fConst5 * fRec26[1]);
		fRec23[0] = Ftube(TUBE_TABLE_12AX7_250k, fTemp4 + fRec26[0] + fTemp3 + -0.840703) + -147.47524390243905;
		double fTemp6 = fRec23[0] - fRec23[1];
		fRec22[0] = fConst8 * (fConst7 * fTemp6 - fConst3 * fRec22[1]);
		fRec27[0] = fConst11 * (fConst10 * fRec27[1] + 0.025 * fTemp6);
		fRec37[0] = 0.9302847925323914 * (fRec33[1] + fRec33[2]) - 0.8605695850647829 * fRec37[1];
		fRec36[0] = fRec37[0] - (1.8405051250752198 * fRec36[1] + 0.8612942439318627 * fRec36[2]);
		double fTemp7 = 1.8508996845035413 * fRec36[1];
		double fTemp8 = 0.9254498422517706 * (fRec36[0] + fRec36[2]);
		double fTemp9 = (fTemp7 + fTemp8) / (Ranode(TUBE_TABLE_12AX7_250k, fRec35[1]) + 1e+05);
		fVec1[0] = fTemp9;
		fRec38[0] = fConst14 * (1.5e+03 * (fTemp9 + fVec1[1]) - fConst13 * fRec38[1]);
		fRec35[0] = Ftube(TUBE_TABLE_12AX7_250k, fTemp8 + fRec38[0] + fTemp7 + -1.204285) + -169.71433333333334;
		double fTemp10 = fRec35[0] - fRec35[1];
		fRec34[0] = fConst8 * (fConst7 * fTemp10 - fConst3 * fRec34[1]);
		fRec39[0] = fConst11 * (fConst10 * fRec39[1] + 0.025 * fTemp10);
		fRec44[0] = fSlow3 + 0.999 * fRec44[1];
		double fTemp11 = double(input0[i0]) * fRec44[0];
		fVec2[0] = fTemp11;
		fRec43[0] = 0.9302847925323914 * (fTemp11 + fVec2[1]) - 0.8605695850647829 * fRec43[1];
		fRec42[0] = fRec43[0] - (1.8405051250752198 * fRec42[1] + 0.8612942439318627 * fRec42[2]);
		double fTemp12 = 1.8508996845035413 * fRec42[1];
		double fTemp13 = 0.9254498422517706 * (fRec42[0] + fRec42[2]);
		double fTemp14 = (fTemp12 + fTemp13) / (Ranode(TUBE_TABLE_12AX7_68k, fRec41[1]) + 1e+05);
		fVec3[0] = fTemp14;
		fRec45[0] = fConst17 * (2.7e+03 * (fTemp14 + fVec3[1]) - fConst16 * fRec45[1]);
		fRec41[0] = Ftube(TUBE_TABLE_12AX7_68k, fTemp13 + fRec45[0] + fTemp12 + -1.581656) + -191.42014814814814;
		double fTemp15 = fRec41[0] - fRec41[1];
		fRec40[0] = fConst8 * (fConst7 * fTemp15 - fConst3 * fRec40[1]);
		fRec46[0] = fConst11 * (fConst10 * fRec46[1] + 0.025 * fTemp15);
		fRec33[0] = ((iSlow2) ? fRec46[0] : fRec40[0]) + 0.6 * ((iSlow2) ? fRec39[0] : fRec34[0]);
		fRec32[0] = -(fConst20 * (fConst19 * fRec32[1] - (fRec33[0] + fRec33[1])));
		fRec31[0] = 0.9302847925323914 * (fRec32[0] + fRec32[1]) - 0.8605695850647829 * fRec31[1];
		fRec30[0] = fRec31[0] - (1.8405051250752198 * fRec30[1] + 0.8612942439318627 * fRec30[2]);
		double fTemp16 = 1.8508996845035413 * fRec30[1];
		double fTemp17 = 0.9254498422517706 * (fRec30[0] + fRec30[2]);
		double fTemp18 = (fTemp16 + fTemp17) / (Ranode(TUBE_TABLE_12AX7_250k, fRec29[1]) + 1e+05);
		fVec4[0] = fTemp18;
		fRec47[0] = fConst14 * (1.5e+03 * (fTemp18 + fVec4[1]) - fConst13 * fRec47[1]);
		fRec29[0] = Ftube(TUBE_TABLE_12AX7_250k, fTemp17 + fRec47[0] + fTemp16 + -1.204285) + -169.71433333333334;
		double fTemp19 = fRec29[0] - fRec29[1];
		fRec28[0] = fConst8 * (fConst7 * fTemp19 - fConst3 * fRec28[1]);
		fRec48[0] = fConst11 * (fConst10 * fRec48[1] + 0.025 * fTemp19);
		fRec21[0] = ((iSlow2) ? fRec48[0] : fRec28[0]) + 0.6 * ((iSlow2) ? fRec27[0] : fRec22[0]);
		fRec20[0] = 0.9302847925323914 * (fRec21[0] + fRec21[1]) - 0.8605695850647829 * fRec20[1];
		fRec19[0] = fRec20[0] - (1.8405051250752198 * fRec19[1] + 0.8612942439318627 * fRec19[2]);
		double fTemp20 = 1.8508996845035413 * fRec19[1];
		double fTemp21 = 0.9254498422517706 * (fRec19[0] + fRec19[2]);
		double fTemp22 = (fTemp20 + fTemp21) / (Ranode(TUBE_TABLE_12AX7_250k, fRec18[1]) + 1e+05);
		fVec5[0] = fTemp22;
		fRec49[0] = fConst6 * (8.2e+02 * (fTemp22 + fVec5[1]) - fConst5 * fRec49[1]);
		fRec18[0] = Ftube(TUBE_TABLE_12AX7_250k, fTemp21 + fRec49[0] + fTemp20 + -0.840703) + -147.47524390243905;
		double fTemp23 = fRec18[0] - fRec18[1];
		fRec17[0] = fConst8 * (fConst7 * fTemp23 - fConst3 * fRec17[1]);
		fRec50[0] = fConst11 * (fConst10 * fRec50[1] + 0.025 * fTemp23);
		double fTemp24 = ((iSlow2) ? fRec50[0] : fRec17[0]);
		fRec51[0] = fSlow4 + 0.999 * fRec51[1];
		double fTemp25 = fRec51[0] * fTemp24;
		double fTemp26 = std::fabs(fTemp25);
		fRec16[0] = 0.9999 * fRec16[1] + 9.999999999998899e-05 * fTemp26;
		double fTemp27 = std::max<double>(fRec16[0], fTemp26);
		fVec6[IOTA0 & 32767] = fTemp27;
		fRec15[0] = fTemp27 + fRec15[1] - fVec6[(IOTA0 - iConst21) & 32767];
		fRec14[0] = 0.999 * fRec14[1] + fConst22 * fRec15[0];
		double fTemp28 = std::max<double>(-1.0, std::min<double>(-0.01, fTemp27 + (-1.0 - 1.02 * fRec14[0])));
		double fTemp29 = -40.1 * fTemp28;
		double fTemp30 = std::max<double>(-6e+02, fTemp29);
		double fTemp31 = fTemp25 - fTemp28;
		double fTemp32 = 40.1 * fTemp31;
		double fTemp33 = std::max<double>(-6e+02, fTemp32);
		double fTemp34 = ((std::fabs(fTemp32) > 0.0001) ? ((fTemp33 < -5e+01) ? -(fTemp33 * std::exp(fTemp33)) : fTemp33 / (1.0 - std::exp(-fTemp33))) : fTemp31 * (134.00083333333336 * fTemp31 + 20.05) + 1.0) - ((std::fabs(fTemp29) > 0.0001) ? ((fTemp30 < -5e+01) ? -(fTemp30 * std::exp(fTemp30)) : fTemp30 / (1.0 - std::exp(-fTemp30))) : fTemp28 * (134.00083333333336 * fTemp28 + -20.05) + 1.0);
		double fTemp35 = fTemp24 * (1.0 - fRec51[0]);
		fRec60[0] = 0.024937655860349125 * fTemp34 - fConst49 * (fConst47 * fRec60[2] + fConst45 * fRec60[1]);
		double fTemp36 = fRec60[2] + fRec60[0] + 2.0 * fRec60[1];
		fVec7[0] = fTemp36;
		fRec59[0] = -(fConst8 * (fConst3 * fRec59[1] - fConst50 * (fTemp36 - fVec7[1])));
		fRec58[0] = -(fConst52 * (fConst51 * fRec58[1] - (fRec59[0] + fRec59[1])));
		fRec57[0] = fRec58[0] - fConst43 * (fConst41 * fRec57[2] + fConst39 * fRec57[1]);
		double fTemp37 = fRec57[2] + fRec57[0] + 2.0 * fRec57[1];
		fVec8[0] = fTemp37;
		fRec56[0] = -(fConst55 * (fConst53 * fRec56[1] - fConst43 * (fTemp37 + fVec8[1])));
		fRec55[0] = fRec56[0] - fConst36 * (fConst34 * fRec55[2] + fConst32 * fRec55[1]);
		double fTemp38 = fRec55[2] + fRec55[0] + 2.0 * fRec55[1];
		fVec9[0] = fTemp38;
		fRec54[0] = -(fConst58 * (fConst56 * fRec54[1] - fConst36 * (fTemp38 + fVec9[1])));
		fRec53[0] = fRec54[0] - fConst29 * (fConst27 * fRec53[2] + fConst25 * fRec53[1]);
		double fTemp39 = std::max<double>(-1.0, std::min<double>(1.0, fSlow9 * (fRec53[2] + fRec53[0] + 2.0 * fRec53[1])));
		fRec62[0] = -(fConst58 * (fConst56 * fRec62[1] - fConst59 * (fTemp38 - fVec9[1])));
		fRec61[0] = fRec62[0] - fConst29 * (fConst27 * fRec61[2] + fConst25 * fRec61[1]);
		double fTemp40 = std::max<double>(-1.0, std::min<double>(1.0, fSlow10 * (fRec61[2] + (fRec61[0] - 2.0 * fRec61[1]))));
		double fTemp41 = fConst25 * fRec63[1];
		double fTemp42 = fConst32 * fRec64[1];
		fRec66[0] = -(fConst52 * (fConst51 * fRec66[1] - fConst40 * (fRec59[0] - fRec59[1])));
		fRec65[0] = fRec66[0] - fConst43 * (fConst41 * fRec65[2] + fConst39 * fRec65[1]);
		fRec64[0] = fConst65 * (fRec65[2] + (fRec65[0] - 2.0 * fRec65[1])) - fConst64 * (fConst63 * fRec64[2] + fTemp42);
		fRec63[0] = fRec64[2] + fConst64 * (fTemp42 + fConst63 * fRec64[0]) - fConst62 * (fConst61 * fRec63[2] + fTemp41);
		double fTemp43 = std::max<double>(-1.0, std::min<double>(1.0, fSlow11 * (fRec63[2] + fConst62 * (fTemp41 + fConst61 * fRec63[0]))));
		double fTemp44 = fConst25 * fRec67[1];
		fRec69[0] = -(fConst55 * (fConst53 * fRec69[1] - fConst66 * (fTemp37 - fVec8[1])));
		fRec68[0] = fRec69[0] - fConst36 * (fConst34 * fRec68[2] + fConst32 * fRec68[1]);
		fRec67[0] = fConst67 * (fRec68[2] + (fRec68[0] - 2.0 * fRec68[1])) - fConst62 * (fConst61 * fRec67[2] + fTemp44);
		double fTemp45 = std::max<double>(-1.0, std::min<double>(1.0, fSlow12 * (fRec67[2] + fConst62 * (fTemp44 + fConst61 * fRec67[0]))));
		double fTemp46 = 1.333521432 * fTemp45 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp45)) + 1.584893192 * (fTemp43 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp43)) + fTemp40 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp40))) + 1.2589412 * fTemp39 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp39));
		fVec10[0] = fTemp46;
		fRec52[0] = -(fConst20 * (fConst19 * fRec52[1] - (fTemp46 + fVec10[1])));
		double fTemp47 = fSlow13 * fRec52[0] + fTemp35 * (fSlow8 * (4.0 * (1.0 - std::fabs(fTemp35)) + -1.0) + 1.0) + fSlow7 * fTemp34;
		fVec11[0] = fTemp47;
		fRec13[0] = -(fConst20 * (fConst19 * fRec13[1] - (fTemp47 + fVec11[1])));
		double fTemp48 = fRec13[0] * fRec12[0];
		fVec12[0] = fTemp48;
		fRec11[0] = 0.9302847925323914 * (fTemp48 + fVec12[1]) - 0.8605695850647829 * fRec11[1];
		fRec10[0] = fRec11[0] - (1.8405051250752198 * fRec10[1] + 0.8612942439318627 * fRec10[2]);
		double fTemp49 = 1.8508996845035413 * fRec10[1];
		double fTemp50 = 0.9254498422517706 * (fRec10[0] + fRec10[2]);
		double fTemp51 = fTemp49 + fTemp50;
		double fTemp52 = fTemp51 / (Ranode(TUBE_TABLE_6V6_250k, fRec9[1]) + 1e+05);
		fVec13[0] = fTemp52;
		fRec70[0] = fConst20 * (4.1e+02 * (fTemp52 + fVec13[1]) - fConst19 * fRec70[1]);
		fRec9[0] = Ftube(TUBE_TABLE_6V6_250k, fTemp50 + fRec70[0] + fTemp49 + -0.659761) + -89.08268292682925;
		double fTemp53 = fRec9[0] - fRec9[1];
		fRec8[0] = fConst8 * (fConst7 * fTemp53 - fConst3 * fRec8[1]);
		fRec71[0] = fConst11 * (fConst10 * fRec71[1] + 0.025 * fTemp53);
		double fTemp54 = fTemp51 / (Ranode(TUBE_TABLE_6V6_68k, fRec73[1]) + 1e+05);
		fVec14[0] = fTemp54;
		fRec74[0] = fConst20 * (4.1e+02 * (fTemp54 + fVec14[1]) - fConst19 * fRec74[1]);
		fRec73[0] = Ftube(TUBE_TABLE_6V6_68k, fTemp50 + fRec74[0] + fTemp49 + -0.664541) + -87.91682926829267;
		double fTemp55 = fRec73[0] - fRec73[1];
		fRec72[0] = fConst8 * (fConst7 * fTemp55 - fConst3 * fRec72[1]);
		fRec75[0] = fConst11 * (fConst10 * fRec75[1] + 0.025 * fTemp55);
		double fTemp56 = std::max<double>(-0.75, ((iSlow0) ? fRec75[0] : fRec72[0])) + std::min<double>(0.7, ((iSlow0) ? fRec71[0] : fRec8[0]));
		double fTemp57 = 0.2 * fRec6[1] + fTemp56;
		fRec6[0] = fTemp57 - fTemp2;
		double fRec7 = 0.2 * (fTemp2 - fTemp57);
		fRec4[0] = fRec7 + fRec6[1];
		double fRec5 = 0.3 * (fTemp56 - fTemp2);
		fRec2[0] = fRec5 + fRec4[1];
		double fRec3 = 0.4 * (fTemp56 - (fTemp0 + fTemp1));
		fRec0[0] = fRec3 + fRec2[1];
		double fRec1 = 0.5 * (fTemp56 - fTemp1);
		output0[i0] = FAUSTFLOAT(fRec1 + fRec0[1]);
		fRec12[1] = fRec12[0];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fVec0[1] = fVec0[0];
		fRec26[1] = fRec26[0];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec27[1] = fRec27[0];
		fRec37[1] = fRec37[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		fVec1[1] = fVec1[0];
		fRec38[1] = fRec38[0];
		fRec35[1] = fRec35[0];
		fRec34[1] = fRec34[0];
		fRec39[1] = fRec39[0];
		fRec44[1] = fRec44[0];
		fVec2[1] = fVec2[0];
		fRec43[1] = fRec43[0];
		fRec42[2] = fRec42[1];
		fRec42[1] = fRec42[0];
		fVec3[1] = fVec3[0];
		fRec45[1] = fRec45[0];
		fRec41[1] = fRec41[0];
		fRec40[1] = fRec40[0];
		fRec46[1] = fRec46[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fRec32[1] = fRec32[0];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fVec4[1] = fVec4[0];
		fRec47[1] = fRec47[0];
		fRec29[1] = fRec29[0];
		fRec28[1] = fRec28[0];
		fRec48[1] = fRec48[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fVec5[1] = fVec5[0];
		fRec49[1] = fRec49[0];
		fRec18[1] = fRec18[0];
		fRec17[1] = fRec17[0];
		fRec50[1] = fRec50[0];
		fRec51[1] = fRec51[0];
		fRec16[1] = fRec16[0];
		IOTA0 = IOTA0 + 1;
		fRec15[1] = fRec15[0];
		fRec14[1] = fRec14[0];
		fRec60[2] = fRec60[1];
		fRec60[1] = fRec60[0];
		fVec7[1] = fVec7[0];
		fRec59[1] = fRec59[0];
		fRec58[1] = fRec58[0];
		fRec57[2] = fRec57[1];
		fRec57[1] = fRec57[0];
		fVec8[1] = fVec8[0];
		fRec56[1] = fRec56[0];
		fRec55[2] = fRec55[1];
		fRec55[1] = fRec55[0];
		fVec9[1] = fVec9[0];
		fRec54[1] = fRec54[0];
		fRec53[2] = fRec53[1];
		fRec53[1] = fRec53[0];
		fRec62[1] = fRec62[0];
		fRec61[2] = fRec61[1];
		fRec61[1] = fRec61[0];
		fRec66[1] = fRec66[0];
		fRec65[2] = fRec65[1];
		fRec65[1] = fRec65[0];
		fRec64[2] = fRec64[1];
		fRec64[1] = fRec64[0];
		fRec63[2] = fRec63[1];
		fRec63[1] = fRec63[0];
		fRec69[1] = fRec69[0];
		fRec68[2] = fRec68[1];
		fRec68[1] = fRec68[0];
		fRec67[2] = fRec67[1];
		fRec67[1] = fRec67[0];
		fVec10[1] = fVec10[0];
		fRec52[1] = fRec52[0];
		fVec11[1] = fVec11[0];
		fRec13[1] = fRec13[0];
		fVec12[1] = fVec12[0];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fVec13[1] = fVec13[0];
		fRec70[1] = fRec70[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec71[1] = fRec71[0];
		fVec14[1] = fVec14[0];
		fRec74[1] = fRec74[0];
		fRec73[1] = fRec73[0];
		fRec72[1] = fRec72[0];
		fRec75[1] = fRec75[0];
		fRec6[1] = fRec6[0];
		fRec4[1] = fRec4[0];
		fRec2[1] = fRec2[0];
		fRec0[1] = fRec0[0];
	}
#undef fCheckbox0
#undef fVslider0
#undef fCheckbox1
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

} // end namespace gxamp7
