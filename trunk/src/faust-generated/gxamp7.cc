// generated from file '../src/faust/gxamp7.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxamp7 {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int sample_rate;
	int fSampleRate;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst4;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec12[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec14[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	double fRec26[2];
	double fRec25[3];
	double fConst6;
	double fVec0[2];
	double fConst7;
	double fRec27[2];
	double fRec24[2];
	double fConst8;
	double fConst9;
	double fRec23[2];
	double fConst11;
	double fConst12;
	double fRec28[2];
	double fRec38[2];
	double fRec37[3];
	double fConst14;
	double fVec1[2];
	double fConst15;
	double fRec39[2];
	double fRec36[2];
	double fRec35[2];
	double fRec40[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec45[2];
	double fVec2[2];
	double fRec44[2];
	double fRec43[3];
	double fConst17;
	double fVec3[2];
	double fConst18;
	double fRec46[2];
	double fRec42[2];
	double fRec41[2];
	double fRec47[2];
	double fRec34[3];
	double fConst20;
	double fConst21;
	double fRec33[2];
	double fRec32[2];
	double fRec31[3];
	double fVec4[2];
	double fRec48[2];
	double fRec30[2];
	double fRec29[2];
	double fRec49[2];
	double fRec22[3];
	double fRec21[2];
	double fRec20[3];
	double fVec5[2];
	double fRec50[2];
	double fRec19[2];
	double fRec18[2];
	double fRec51[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec52[2];
	double fRec17[2];
	int IOTA0;
	double fVec6[32768];
	int iConst22;
	double fRec16[2];
	double fConst23;
	double fRec15[2];
	double fConst26;
	double fConst27;
	double fConst29;
	double fConst30;
	double fConst33;
	double fConst34;
	double fConst36;
	double fConst37;
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst46;
	double fConst48;
	double fConst49;
	double fRec61[3];
	double fVec7[2];
	double fRec60[2];
	double fConst50;
	double fConst52;
	double fRec59[2];
	double fRec58[3];
	double fVec8[2];
	double fConst53;
	double fConst55;
	double fRec57[2];
	double fRec56[3];
	double fVec9[2];
	double fConst56;
	double fConst58;
	double fRec55[2];
	double fRec54[3];
	double fConst59;
	double fConst60;
	double fConst61;
	double fRec63[2];
	double fRec62[3];
	double fConst62;
	double fConst63;
	double fConst64;
	double fConst65;
	double fConst66;
	double fConst67;
	double fRec67[2];
	double fRec66[3];
	double fConst68;
	double fRec65[3];
	double fRec64[3];
	double fConst69;
	double fConst70;
	double fConst71;
	double fRec70[2];
	double fRec69[3];
	double fConst72;
	double fRec68[3];
	double fVec10[2];
	double fRec53[2];
	double fVec11[2];
	double fRec13[2];
	double fVec12[2];
	double fRec11[2];
	double fRec10[3];
	double fVec13[2];
	double fRec71[2];
	double fRec9[2];
	double fRec8[2];
	double fRec72[2];
	double fVec14[2];
	double fRec75[2];
	double fRec74[2];
	double fRec73[2];
	double fRec76[2];
	double fRec6[2];
	double fRec4[2];
	double fRec2[2];
	double fRec0[2];

	void clear_state_f();
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static void init_static(unsigned int sample_rate, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "pre 12ax7/ push-pull 6V6";
	name = N_("pre 12ax7/ push-pull 6V6");
	groups = 0;
	description = ""; // description (tooltip)
	category = "";       // category
	shortname = "";     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	load_ui = 0;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec12[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec14[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec26[l2] = 0.0;
	for (int l3 = 0; l3 < 3; l3 = l3 + 1) fRec25[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fVec0[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec27[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec24[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec23[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec28[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec38[l9] = 0.0;
	for (int l10 = 0; l10 < 3; l10 = l10 + 1) fRec37[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fVec1[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec39[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec36[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec35[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec40[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec45[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fVec2[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec44[l18] = 0.0;
	for (int l19 = 0; l19 < 3; l19 = l19 + 1) fRec43[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fVec3[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec46[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec42[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec41[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec47[l24] = 0.0;
	for (int l25 = 0; l25 < 3; l25 = l25 + 1) fRec34[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec33[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec32[l27] = 0.0;
	for (int l28 = 0; l28 < 3; l28 = l28 + 1) fRec31[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fVec4[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec48[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec30[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fRec29[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fRec49[l33] = 0.0;
	for (int l34 = 0; l34 < 3; l34 = l34 + 1) fRec22[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec21[l35] = 0.0;
	for (int l36 = 0; l36 < 3; l36 = l36 + 1) fRec20[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fVec5[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fRec50[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec19[l39] = 0.0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec18[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec51[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) fRec52[l42] = 0.0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fRec17[l43] = 0.0;
	for (int l44 = 0; l44 < 32768; l44 = l44 + 1) fVec6[l44] = 0.0;
	for (int l45 = 0; l45 < 2; l45 = l45 + 1) fRec16[l45] = 0.0;
	for (int l46 = 0; l46 < 2; l46 = l46 + 1) fRec15[l46] = 0.0;
	for (int l47 = 0; l47 < 3; l47 = l47 + 1) fRec61[l47] = 0.0;
	for (int l48 = 0; l48 < 2; l48 = l48 + 1) fVec7[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec60[l49] = 0.0;
	for (int l50 = 0; l50 < 2; l50 = l50 + 1) fRec59[l50] = 0.0;
	for (int l51 = 0; l51 < 3; l51 = l51 + 1) fRec58[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fVec8[l52] = 0.0;
	for (int l53 = 0; l53 < 2; l53 = l53 + 1) fRec57[l53] = 0.0;
	for (int l54 = 0; l54 < 3; l54 = l54 + 1) fRec56[l54] = 0.0;
	for (int l55 = 0; l55 < 2; l55 = l55 + 1) fVec9[l55] = 0.0;
	for (int l56 = 0; l56 < 2; l56 = l56 + 1) fRec55[l56] = 0.0;
	for (int l57 = 0; l57 < 3; l57 = l57 + 1) fRec54[l57] = 0.0;
	for (int l58 = 0; l58 < 2; l58 = l58 + 1) fRec63[l58] = 0.0;
	for (int l59 = 0; l59 < 3; l59 = l59 + 1) fRec62[l59] = 0.0;
	for (int l60 = 0; l60 < 2; l60 = l60 + 1) fRec67[l60] = 0.0;
	for (int l61 = 0; l61 < 3; l61 = l61 + 1) fRec66[l61] = 0.0;
	for (int l62 = 0; l62 < 3; l62 = l62 + 1) fRec65[l62] = 0.0;
	for (int l63 = 0; l63 < 3; l63 = l63 + 1) fRec64[l63] = 0.0;
	for (int l64 = 0; l64 < 2; l64 = l64 + 1) fRec70[l64] = 0.0;
	for (int l65 = 0; l65 < 3; l65 = l65 + 1) fRec69[l65] = 0.0;
	for (int l66 = 0; l66 < 3; l66 = l66 + 1) fRec68[l66] = 0.0;
	for (int l67 = 0; l67 < 2; l67 = l67 + 1) fVec10[l67] = 0.0;
	for (int l68 = 0; l68 < 2; l68 = l68 + 1) fRec53[l68] = 0.0;
	for (int l69 = 0; l69 < 2; l69 = l69 + 1) fVec11[l69] = 0.0;
	for (int l70 = 0; l70 < 2; l70 = l70 + 1) fRec13[l70] = 0.0;
	for (int l71 = 0; l71 < 2; l71 = l71 + 1) fVec12[l71] = 0.0;
	for (int l72 = 0; l72 < 2; l72 = l72 + 1) fRec11[l72] = 0.0;
	for (int l73 = 0; l73 < 3; l73 = l73 + 1) fRec10[l73] = 0.0;
	for (int l74 = 0; l74 < 2; l74 = l74 + 1) fVec13[l74] = 0.0;
	for (int l75 = 0; l75 < 2; l75 = l75 + 1) fRec71[l75] = 0.0;
	for (int l76 = 0; l76 < 2; l76 = l76 + 1) fRec9[l76] = 0.0;
	for (int l77 = 0; l77 < 2; l77 = l77 + 1) fRec8[l77] = 0.0;
	for (int l78 = 0; l78 < 2; l78 = l78 + 1) fRec72[l78] = 0.0;
	for (int l79 = 0; l79 < 2; l79 = l79 + 1) fVec14[l79] = 0.0;
	for (int l80 = 0; l80 < 2; l80 = l80 + 1) fRec75[l80] = 0.0;
	for (int l81 = 0; l81 < 2; l81 = l81 + 1) fRec74[l81] = 0.0;
	for (int l82 = 0; l82 < 2; l82 = l82 + 1) fRec73[l82] = 0.0;
	for (int l83 = 0; l83 < 2; l83 = l83 + 1) fRec76[l83] = 0.0;
	for (int l84 = 0; l84 < 2; l84 = l84 + 1) fRec6[l84] = 0.0;
	for (int l85 = 0; l85 < 2; l85 = l85 + 1) fRec4[l85] = 0.0;
	for (int l86 = 0; l86 < 2; l86 = l86 + 1) fRec2[l86] = 0.0;
	for (int l87 = 0; l87 < 2; l87 = l87 + 1) fRec0[l87] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int RsamplingFreq)
{
	sample_rate = 96000;
	smp.setup(RsamplingFreq, sample_rate);
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
	double fConst13 = 1.0 / std::tan(414.6902302738527 / fConst0);
	fConst14 = 1.0 - fConst13;
	fConst15 = 1.0 / (fConst13 + 1.0);
	double fConst16 = 1.0 / std::tan(270.1769682087222 / fConst0);
	fConst17 = 1.0 - fConst16;
	fConst18 = 1.0 / (fConst16 + 1.0);
	double fConst19 = 1.0 / std::tan(20517.741620594938 / fConst0);
	fConst20 = 1.0 - fConst19;
	fConst21 = 1.0 / (fConst19 + 1.0);
	iConst22 = int(std::min<double>(65536.0, std::max<double>(0.0, 0.1111111111111111 * fConst0)));
	fConst23 = 0.009000000000000008 / fConst0;
	double fConst24 = std::tan(942.4777960769379 / fConst0);
	double fConst25 = mydsp_faustpower2_f(fConst24);
	fConst26 = 1.0 / fConst25;
	fConst27 = 2.0 * (1.0 - fConst26);
	double fConst28 = 1.0 / fConst24;
	fConst29 = (fConst28 + -1.0000000000000004) / fConst24 + 1.0;
	fConst30 = 1.0 / ((fConst28 + 1.0000000000000004) / fConst24 + 1.0);
	double fConst31 = std::tan(3769.9111843077517 / fConst0);
	double fConst32 = mydsp_faustpower2_f(fConst31);
	fConst33 = 1.0 / fConst32;
	fConst34 = 2.0 * (1.0 - fConst33);
	double fConst35 = 1.0 / fConst31;
	fConst36 = (fConst35 + -1.0000000000000004) / fConst31 + 1.0;
	fConst37 = 1.0 / ((fConst35 + 1.0000000000000004) / fConst31 + 1.0);
	double fConst38 = std::tan(10053.096491487338 / fConst0);
	double fConst39 = mydsp_faustpower2_f(fConst38);
	fConst40 = 1.0 / fConst39;
	fConst41 = 2.0 * (1.0 - fConst40);
	fConst42 = 1.0 / fConst38;
	fConst43 = (fConst42 + -1.0000000000000004) / fConst38 + 1.0;
	fConst44 = 1.0 / ((fConst42 + 1.0000000000000004) / fConst38 + 1.0);
	double fConst45 = std::tan(47123.8898038469 / fConst0);
	fConst46 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst45));
	double fConst47 = 1.0 / fConst45;
	fConst48 = (fConst47 + -1.414213562373095) / fConst45 + 1.0;
	fConst49 = 1.0 / ((fConst47 + 1.414213562373095) / fConst45 + 1.0);
	fConst50 = 1.0 - fConst42;
	double fConst51 = fConst42 + 1.0;
	fConst52 = 1.0 / fConst51;
	fConst53 = 1.0 - fConst35;
	double fConst54 = fConst35 + 1.0;
	fConst55 = 1.0 / fConst54;
	fConst56 = 1.0 - fConst28;
	double fConst57 = fConst28 + 1.0;
	fConst58 = 1.0 / fConst57;
	fConst59 = fConst56 / fConst57;
	fConst60 = 1.0 / (fConst24 * fConst57);
	fConst61 = 0.0 - fConst60;
	fConst62 = 0.0 - 2.0 / fConst25;
	fConst63 = 1.0 - fConst56 / fConst24;
	fConst64 = 1.0 / (fConst57 / fConst24 + 1.0);
	fConst65 = 1.0 - fConst53 / fConst31;
	fConst66 = 1.0 / (fConst54 / fConst31 + 1.0);
	fConst67 = 0.0 - 1.0 / (fConst38 * fConst51);
	fConst68 = 0.0 - 2.0 / fConst39;
	fConst69 = fConst53 / fConst54;
	fConst70 = 1.0 / (fConst31 * fConst54);
	fConst71 = 0.0 - fConst70;
	fConst72 = 0.0 - 2.0 / fConst32;
	IOTA0 = 0;
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fCheckbox0 (*fCheckbox0_)
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fCheckbox1 (*fCheckbox1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	int iSlow0 = int(double(fCheckbox0));
	double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
	double fSlow2 = 0.0010000000000000009 * double(fVslider1);
	int iSlow3 = int(double(fCheckbox1));
	double fSlow4 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider2));
	double fSlow5 = 1.000000000000001e-05 * double(fVslider3);
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		double fTemp0 = 0.4 * fRec2[1];
		double fTemp1 = 0.5 * fRec0[1];
		double fTemp2 = fTemp1 + 0.3 * fRec4[1] + fTemp0;
		fRec12[0] = fSlow1 + 0.999 * fRec12[1];
		fRec14[0] = fSlow2 + 0.999 * fRec14[1];
		double fTemp3 = 2.0 * (fRec14[0] + -0.5);
		fRec26[0] = 0.9302847925323914 * (fRec22[1] + fRec22[2]) - 0.8605695850647829 * fRec26[1];
		fRec25[0] = fRec26[0] - (1.8405051250752198 * fRec25[1] + 0.8612942439318627 * fRec25[2]);
		double fTemp4 = 1.8508996845035413 * fRec25[1];
		double fTemp5 = 0.9254498422517706 * (fRec25[0] + fRec25[2]);
		double fTemp6 = (fTemp4 + fTemp5) / (Ranode(TUBE_TABLE_12AX7_250k, fRec24[1]) + 1e+05);
		fVec0[0] = fTemp6;
		fRec27[0] = fConst7 * (8.2e+02 * (fTemp6 + fVec0[1]) - fConst6 * fRec27[1]);
		fRec24[0] = Ftube(TUBE_TABLE_12AX7_250k, fTemp5 + fRec27[0] + fTemp4 + -0.840703) + -147.47524390243905;
		fRec23[0] = 0.025 * (fConst8 * fRec24[0] + fConst9 * fRec24[1]) - fConst4 * fRec23[1];
		fRec28[0] = fConst12 * (fConst11 * fRec28[1] + 0.025 * (fRec24[0] - fRec24[1]));
		fRec38[0] = 0.9302847925323914 * (fRec34[1] + fRec34[2]) - 0.8605695850647829 * fRec38[1];
		fRec37[0] = fRec38[0] - (1.8405051250752198 * fRec37[1] + 0.8612942439318627 * fRec37[2]);
		double fTemp7 = 1.8508996845035413 * fRec37[1];
		double fTemp8 = 0.9254498422517706 * (fRec37[0] + fRec37[2]);
		double fTemp9 = (fTemp7 + fTemp8) / (Ranode(TUBE_TABLE_12AX7_250k, fRec36[1]) + 1e+05);
		fVec1[0] = fTemp9;
		fRec39[0] = fConst15 * (1.5e+03 * (fTemp9 + fVec1[1]) - fConst14 * fRec39[1]);
		fRec36[0] = Ftube(TUBE_TABLE_12AX7_250k, fTemp8 + fRec39[0] + fTemp7 + -1.204285) + -169.71433333333334;
		fRec35[0] = 0.025 * (fConst8 * fRec36[0] + fConst9 * fRec36[1]) - fConst4 * fRec35[1];
		fRec40[0] = fConst12 * (fConst11 * fRec40[1] + 0.025 * (fRec36[0] - fRec36[1]));
		fRec45[0] = fSlow4 + 0.999 * fRec45[1];
		double fTemp10 = double(buf[i0]) * fRec45[0];
		fVec2[0] = fTemp10;
		fRec44[0] = 0.9302847925323914 * (fTemp10 + fVec2[1]) - 0.8605695850647829 * fRec44[1];
		fRec43[0] = fRec44[0] - (1.8405051250752198 * fRec43[1] + 0.8612942439318627 * fRec43[2]);
		double fTemp11 = 1.8508996845035413 * fRec43[1];
		double fTemp12 = 0.9254498422517706 * (fRec43[0] + fRec43[2]);
		double fTemp13 = (fTemp11 + fTemp12) / (Ranode(TUBE_TABLE_12AX7_68k, fRec42[1]) + 1e+05);
		fVec3[0] = fTemp13;
		fRec46[0] = fConst18 * (2.7e+03 * (fTemp13 + fVec3[1]) - fConst17 * fRec46[1]);
		fRec42[0] = Ftube(TUBE_TABLE_12AX7_68k, fTemp12 + fRec46[0] + fTemp11 + -1.581656) + -191.42014814814814;
		fRec41[0] = 0.025 * (fConst8 * fRec42[0] + fConst9 * fRec42[1]) - fConst4 * fRec41[1];
		fRec47[0] = fConst12 * (fConst11 * fRec47[1] + 0.025 * (fRec42[0] - fRec42[1]));
		fRec34[0] = ((iSlow3) ? fRec47[0] : fRec41[0]) + 0.6 * ((iSlow3) ? fRec40[0] : fRec35[0]);
		fRec33[0] = 0.0 - fConst21 * (fConst20 * fRec33[1] - (fRec34[0] + fRec34[1]));
		fRec32[0] = 0.9302847925323914 * (fRec33[0] + fRec33[1]) - 0.8605695850647829 * fRec32[1];
		fRec31[0] = fRec32[0] - (1.8405051250752198 * fRec31[1] + 0.8612942439318627 * fRec31[2]);
		double fTemp14 = 1.8508996845035413 * fRec31[1];
		double fTemp15 = 0.9254498422517706 * (fRec31[0] + fRec31[2]);
		double fTemp16 = (fTemp14 + fTemp15) / (Ranode(TUBE_TABLE_12AX7_250k, fRec30[1]) + 1e+05);
		fVec4[0] = fTemp16;
		fRec48[0] = fConst15 * (1.5e+03 * (fTemp16 + fVec4[1]) - fConst14 * fRec48[1]);
		fRec30[0] = Ftube(TUBE_TABLE_12AX7_250k, fTemp15 + fRec48[0] + fTemp14 + -1.204285) + -169.71433333333334;
		fRec29[0] = 0.025 * (fConst8 * fRec30[0] + fConst9 * fRec30[1]) - fConst4 * fRec29[1];
		fRec49[0] = fConst12 * (fConst11 * fRec49[1] + 0.025 * (fRec30[0] - fRec30[1]));
		fRec22[0] = ((iSlow3) ? fRec49[0] : fRec29[0]) + 0.6 * ((iSlow3) ? fRec28[0] : fRec23[0]);
		fRec21[0] = 0.9302847925323914 * (fRec22[0] + fRec22[1]) - 0.8605695850647829 * fRec21[1];
		fRec20[0] = fRec21[0] - (1.8405051250752198 * fRec20[1] + 0.8612942439318627 * fRec20[2]);
		double fTemp17 = 1.8508996845035413 * fRec20[1];
		double fTemp18 = 0.9254498422517706 * (fRec20[0] + fRec20[2]);
		double fTemp19 = (fTemp17 + fTemp18) / (Ranode(TUBE_TABLE_12AX7_250k, fRec19[1]) + 1e+05);
		fVec5[0] = fTemp19;
		fRec50[0] = fConst7 * (8.2e+02 * (fTemp19 + fVec5[1]) - fConst6 * fRec50[1]);
		fRec19[0] = Ftube(TUBE_TABLE_12AX7_250k, fTemp18 + fRec50[0] + fTemp17 + -0.840703) + -147.47524390243905;
		fRec18[0] = 0.025 * (fConst8 * fRec19[0] + fConst9 * fRec19[1]) - fConst4 * fRec18[1];
		fRec51[0] = fConst12 * (fConst11 * fRec51[1] + 0.025 * (fRec19[0] - fRec19[1]));
		double fTemp20 = ((iSlow3) ? fRec51[0] : fRec18[0]);
		fRec52[0] = fSlow5 + 0.999 * fRec52[1];
		double fTemp21 = fRec52[0] * fTemp20;
		double fTemp22 = std::fabs(fTemp21);
		fRec17[0] = 0.9999 * fRec17[1] + 9.999999999998899e-05 * fTemp22;
		double fTemp23 = std::max<double>(fRec17[0], fTemp22);
		fVec6[IOTA0 & 32767] = fTemp23;
		fRec16[0] = fTemp23 + fRec16[1] - fVec6[(IOTA0 - iConst22) & 32767];
		fRec15[0] = 0.999 * fRec15[1] + fConst23 * fRec16[0];
		double fTemp24 = std::max<double>(-1.0, std::min<double>(-0.01, fTemp23 + (-1.0 - 1.02 * fRec15[0])));
		double fTemp25 = 0.0 - 40.1 * fTemp24;
		double fTemp26 = std::max<double>(-6e+02, fTemp25);
		double fTemp27 = fTemp21 - fTemp24;
		double fTemp28 = 40.1 * fTemp27;
		double fTemp29 = std::max<double>(-6e+02, fTemp28);
		double fTemp30 = ((std::fabs(fTemp28) > 0.0001) ? ((fTemp29 < -5e+01) ? 0.0 - fTemp29 * std::exp(fTemp29) : fTemp29 / (1.0 - std::exp(-1.0 * fTemp29))) : fTemp27 * (134.00083333333336 * fTemp27 + 20.05) + 1.0) - ((std::fabs(fTemp25) > 0.0001) ? ((fTemp26 < -5e+01) ? 0.0 - fTemp26 * std::exp(fTemp26) : fTemp26 / (1.0 - std::exp(-1.0 * fTemp26))) : fTemp25 * (0.08333333333333333 * fTemp25 + 0.5) + 1.0);
		double fTemp31 = fTemp20 * (1.0 - fRec52[0]);
		fRec61[0] = 0.024937655860349125 * fTemp30 - fConst49 * (fConst48 * fRec61[2] + fConst46 * fRec61[1]);
		double fTemp32 = fRec61[2] + fRec61[0] + 2.0 * fRec61[1];
		fVec7[0] = fTemp32;
		fRec60[0] = fConst49 * (fConst8 * fTemp32 + fConst9 * fVec7[1]) - fConst4 * fRec60[1];
		fRec59[0] = 0.0 - fConst52 * (fConst50 * fRec59[1] - (fRec60[0] + fRec60[1]));
		fRec58[0] = fRec59[0] - fConst44 * (fConst43 * fRec58[2] + fConst41 * fRec58[1]);
		double fTemp33 = fRec58[2] + fRec58[0] + 2.0 * fRec58[1];
		fVec8[0] = fTemp33;
		fRec57[0] = 0.0 - fConst55 * (fConst53 * fRec57[1] - fConst44 * (fTemp33 + fVec8[1]));
		fRec56[0] = fRec57[0] - fConst37 * (fConst36 * fRec56[2] + fConst34 * fRec56[1]);
		double fTemp34 = fRec56[2] + fRec56[0] + 2.0 * fRec56[1];
		fVec9[0] = fTemp34;
		fRec55[0] = 0.0 - fConst58 * (fConst56 * fRec55[1] - fConst37 * (fTemp34 + fVec9[1]));
		fRec54[0] = fRec55[0] - fConst30 * (fConst29 * fRec54[2] + fConst27 * fRec54[1]);
		double fTemp35 = std::max<double>(-1.0, std::min<double>(1.0, fConst30 * (fRec54[2] + fRec54[0] + 2.0 * fRec54[1]) * std::pow(1e+01, 0.9 * fRec14[0])));
		fRec63[0] = fConst37 * (fConst60 * fTemp34 + fConst61 * fVec9[1]) - fConst59 * fRec63[1];
		fRec62[0] = fRec63[0] - fConst30 * (fConst29 * fRec62[2] + fConst27 * fRec62[1]);
		double fTemp36 = std::max<double>(-1.0, std::min<double>(1.0, fConst30 * (fConst26 * fRec62[0] + fConst62 * fRec62[1] + fConst26 * fRec62[2]) * std::pow(1e+01, 2.0 * fRec14[0])));
		double fTemp37 = fConst27 * fRec64[1];
		double fTemp38 = fConst34 * fRec65[1];
		fRec67[0] = fConst67 * fRec60[1] - fConst52 * (fConst50 * fRec67[1] - fConst42 * fRec60[0]);
		fRec66[0] = fRec67[0] - fConst44 * (fConst43 * fRec66[2] + fConst41 * fRec66[1]);
		fRec65[0] = fConst44 * (fConst40 * fRec66[0] + fConst68 * fRec66[1] + fConst40 * fRec66[2]) - fConst66 * (fConst65 * fRec65[2] + fTemp38);
		fRec64[0] = fRec65[2] + fConst66 * (fTemp38 + fConst65 * fRec65[0]) - fConst64 * (fConst63 * fRec64[2] + fTemp37);
		double fTemp39 = std::max<double>(-1.0, std::min<double>(1.0, (fRec64[2] + fConst64 * (fTemp37 + fConst63 * fRec64[0])) * std::pow(1e+01, 0.8 * fRec14[0])));
		double fTemp40 = fConst27 * fRec68[1];
		fRec70[0] = fConst44 * (fConst70 * fTemp33 + fConst71 * fVec8[1]) - fConst69 * fRec70[1];
		fRec69[0] = fRec70[0] - fConst37 * (fConst36 * fRec69[2] + fConst34 * fRec69[1]);
		fRec68[0] = fConst37 * (fConst33 * fRec69[0] + fConst72 * fRec69[1] + fConst33 * fRec69[2]) - fConst64 * (fConst63 * fRec68[2] + fTemp40);
		double fTemp41 = std::max<double>(-1.0, std::min<double>(1.0, (fRec68[2] + fConst64 * (fTemp40 + fConst63 * fRec68[0])) * std::pow(1e+01, 1.2 * fRec14[0])));
		double fTemp42 = 1.333521432 * fTemp41 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp41)) + 1.584893192 * (fTemp39 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp39)) + fTemp36 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp36))) + 1.2589412 * fTemp35 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp35));
		fVec10[0] = fTemp42;
		fRec53[0] = 0.0 - fConst21 * (fConst20 * fRec53[1] - (fTemp42 + fVec10[1]));
		double fTemp43 = fRec53[0] * (1.0 - std::max<double>(0.0, -1.0 * fTemp3)) + fTemp31 * (1.25 * fRec14[0] * (4.0 * (1.0 - std::fabs(fTemp31)) + -1.0) + 1.0) + 0.024937655860349125 * fTemp30 * (1.0 - std::max<double>(0.0, fTemp3));
		fVec11[0] = fTemp43;
		fRec13[0] = 0.0 - fConst21 * (fConst20 * fRec13[1] - (fTemp43 + fVec11[1]));
		double fTemp44 = fRec13[0] * fRec12[0];
		fVec12[0] = fTemp44;
		fRec11[0] = 0.9302847925323914 * (fTemp44 + fVec12[1]) - 0.8605695850647829 * fRec11[1];
		fRec10[0] = fRec11[0] - (1.8405051250752198 * fRec10[1] + 0.8612942439318627 * fRec10[2]);
		double fTemp45 = 1.8508996845035413 * fRec10[1];
		double fTemp46 = 0.9254498422517706 * (fRec10[0] + fRec10[2]);
		double fTemp47 = fTemp45 + fTemp46;
		double fTemp48 = fTemp47 / (Ranode(TUBE_TABLE_6V6_250k, fRec9[1]) + 1e+05);
		fVec13[0] = fTemp48;
		fRec71[0] = fConst21 * (4.1e+02 * (fTemp48 + fVec13[1]) - fConst20 * fRec71[1]);
		fRec9[0] = Ftube(TUBE_TABLE_6V6_250k, fTemp46 + fRec71[0] + fTemp45 + -0.572721) + -110.3119512195122;
		fRec8[0] = 0.025 * (fConst8 * fRec9[0] + fConst9 * fRec9[1]) - fConst4 * fRec8[1];
		fRec72[0] = fConst12 * (fConst11 * fRec72[1] + 0.025 * (fRec9[0] - fRec9[1]));
		double fTemp49 = fTemp47 / (Ranode(TUBE_TABLE_6V6_68k, fRec74[1]) + 1e+05);
		fVec14[0] = fTemp49;
		fRec75[0] = fConst21 * (4.1e+02 * (fTemp49 + fVec14[1]) - fConst20 * fRec75[1]);
		fRec74[0] = Ftube(TUBE_TABLE_6V6_68k, fTemp46 + fRec75[0] + fTemp45 + -0.581274) + -108.22585365853661;
		fRec73[0] = 0.025 * (fConst8 * fRec74[0] + fConst9 * fRec74[1]) - fConst4 * fRec73[1];
		fRec76[0] = fConst12 * (fConst11 * fRec76[1] + 0.025 * (fRec74[0] - fRec74[1]));
		double fTemp50 = std::max<double>(-0.75, ((iSlow0) ? fRec76[0] : fRec73[0])) + std::min<double>(0.7, ((iSlow0) ? fRec72[0] : fRec8[0]));
		double fTemp51 = 0.2 * fRec6[1] + fTemp50 - fTemp2;
		fRec6[0] = fTemp51;
		double fRec7 = 0.0 - 0.2 * fTemp51;
		fRec4[0] = fRec7 + fRec6[1];
		double fRec5 = 0.3 * (fTemp50 - fTemp2);
		fRec2[0] = fRec5 + fRec4[1];
		double fRec3 = 0.4 * (fTemp50 - (fTemp0 + fTemp1));
		fRec0[0] = fRec3 + fRec2[1];
		double fRec1 = 0.5 * (fTemp50 - fTemp1);
		buf[i0] = FAUSTFLOAT(fRec1 + fRec0[1]);
		fRec12[1] = fRec12[0];
		fRec14[1] = fRec14[0];
		fRec26[1] = fRec26[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		fVec0[1] = fVec0[0];
		fRec27[1] = fRec27[0];
		fRec24[1] = fRec24[0];
		fRec23[1] = fRec23[0];
		fRec28[1] = fRec28[0];
		fRec38[1] = fRec38[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fVec1[1] = fVec1[0];
		fRec39[1] = fRec39[0];
		fRec36[1] = fRec36[0];
		fRec35[1] = fRec35[0];
		fRec40[1] = fRec40[0];
		fRec45[1] = fRec45[0];
		fVec2[1] = fVec2[0];
		fRec44[1] = fRec44[0];
		fRec43[2] = fRec43[1];
		fRec43[1] = fRec43[0];
		fVec3[1] = fVec3[0];
		fRec46[1] = fRec46[0];
		fRec42[1] = fRec42[0];
		fRec41[1] = fRec41[0];
		fRec47[1] = fRec47[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec33[1] = fRec33[0];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fVec4[1] = fVec4[0];
		fRec48[1] = fRec48[0];
		fRec30[1] = fRec30[0];
		fRec29[1] = fRec29[0];
		fRec49[1] = fRec49[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fRec21[1] = fRec21[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fVec5[1] = fVec5[0];
		fRec50[1] = fRec50[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec51[1] = fRec51[0];
		fRec52[1] = fRec52[0];
		fRec17[1] = fRec17[0];
		IOTA0 = IOTA0 + 1;
		fRec16[1] = fRec16[0];
		fRec15[1] = fRec15[0];
		fRec61[2] = fRec61[1];
		fRec61[1] = fRec61[0];
		fVec7[1] = fVec7[0];
		fRec60[1] = fRec60[0];
		fRec59[1] = fRec59[0];
		fRec58[2] = fRec58[1];
		fRec58[1] = fRec58[0];
		fVec8[1] = fVec8[0];
		fRec57[1] = fRec57[0];
		fRec56[2] = fRec56[1];
		fRec56[1] = fRec56[0];
		fVec9[1] = fVec9[0];
		fRec55[1] = fRec55[0];
		fRec54[2] = fRec54[1];
		fRec54[1] = fRec54[0];
		fRec63[1] = fRec63[0];
		fRec62[2] = fRec62[1];
		fRec62[1] = fRec62[0];
		fRec67[1] = fRec67[0];
		fRec66[2] = fRec66[1];
		fRec66[1] = fRec66[0];
		fRec65[2] = fRec65[1];
		fRec65[1] = fRec65[0];
		fRec64[2] = fRec64[1];
		fRec64[1] = fRec64[0];
		fRec70[1] = fRec70[0];
		fRec69[2] = fRec69[1];
		fRec69[1] = fRec69[0];
		fRec68[2] = fRec68[1];
		fRec68[1] = fRec68[0];
		fVec10[1] = fVec10[0];
		fRec53[1] = fRec53[0];
		fVec11[1] = fVec11[0];
		fRec13[1] = fRec13[0];
		fVec12[1] = fVec12[0];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fVec13[1] = fVec13[0];
		fRec71[1] = fRec71[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec72[1] = fRec72[0];
		fVec14[1] = fVec14[0];
		fRec75[1] = fRec75[0];
		fRec74[1] = fRec74[0];
		fRec73[1] = fRec73[0];
		fRec76[1] = fRec76[0];
		fRec6[1] = fRec6[0];
		fRec4[1] = fRec4[0];
		fRec2[1] = fRec2[0];
		fRec0[1] = fRec0[0];
	}
	smp.down(buf, output0);
#undef fCheckbox0
#undef fVslider0
#undef fVslider1
#undef fCheckbox1
#undef fVslider2
#undef fVslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	fVslider1_ = reg.registerFloatVar("gxdistortion.drive","","SA","",&fVslider1, 0.35, 0.0, 1.0, 0.01, 0);
	fVslider3_ = reg.registerFloatVar("gxdistortion.wet_dry","","SA","",&fVslider3, 1e+02, 0.0, 1e+02, 1.0, 0);
	fCheckbox1_ = reg.registerFloatVar("amp.highgain","","BA",N_("Allow frequencies below 31Hz"),&fCheckbox1, 0.0, 0.0, 1.0, 1.0, 0);
	fVslider2_ = reg.registerFloatVar("amp2.stage1.Pregain","","SA","",&fVslider2, -6.0, -2e+01, 2e+01, 0.1, 0);
	fCheckbox0_ = reg.registerFloatVar("amp.highgain","","BA",N_("Allow frequencies below 31Hz"),&fCheckbox0, 0.0, 0.0, 1.0, 1.0, 0);
	fVslider0_ = reg.registerFloatVar("amp2.stage2.gain1","","SA","",&fVslider0, -6.0, -2e+01, 2e+01, 0.1, 0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace gxamp7
