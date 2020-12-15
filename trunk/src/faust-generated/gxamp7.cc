// generated from file '../src/faust/gxamp7.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxamp7 {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int sample_rate;
	int fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
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
	double fConst24;
	double fConst25;
	double fConst26;
	double fRec29[2];
	double fRec28[3];
	double fConst27;
	double fConst28;
	double fVec0[2];
	double fConst29;
	double fRec30[2];
	double fRec27[2];
	double fRec26[2];
	double fRec40[2];
	double fRec39[3];
	double fConst30;
	double fConst31;
	double fVec1[2];
	double fConst32;
	double fRec41[2];
	double fRec38[2];
	double fRec37[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec46[2];
	double fVec2[2];
	double fRec45[2];
	double fRec44[3];
	double fConst33;
	double fConst34;
	double fVec3[2];
	double fConst35;
	double fRec47[2];
	double fRec43[2];
	double fRec42[2];
	double fRec36[3];
	double fRec35[2];
	double fRec34[2];
	double fRec33[3];
	double fVec4[2];
	double fRec48[2];
	double fRec32[2];
	double fRec31[2];
	double fRec25[3];
	double fRec24[2];
	double fRec23[3];
	double fVec5[2];
	double fRec49[2];
	double fRec22[2];
	double fRec21[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec50[2];
	double fRec51[2];
	int IOTA;
	double fVec6[32768];
	double fConst36;
	int iConst37;
	double fRec53[2];
	double fRec52[2];
	double fConst38;
	double fConst39;
	double fRec20[3];
	double fVec7[2];
	double fConst40;
	double fConst41;
	double fRec19[2];
	double fRec18[2];
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
	double fRec17[3];
	double fVec8[2];
	double fConst46;
	double fConst47;
	double fConst48;
	double fRec16[2];
	double fConst49;
	double fConst50;
	double fRec15[3];
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fRec14[3];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec54[2];
	double fConst61;
	double fRec58[2];
	double fRec57[3];
	double fConst62;
	double fConst63;
	double fConst64;
	double fRec56[3];
	double fRec55[3];
	double fConst65;
	double fConst66;
	double fConst67;
	double fRec62[2];
	double fRec61[3];
	double fVec9[2];
	double fConst68;
	double fConst69;
	double fRec60[2];
	double fConst70;
	double fRec59[3];
	double fConst71;
	double fConst72;
	double fRec64[2];
	double fRec63[3];
	double fVec10[2];
	double fRec13[2];
	double fVec11[2];
	double fRec12[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec65[2];
	double fVec12[2];
	double fRec11[2];
	double fRec10[3];
	double fVec13[2];
	double fRec66[2];
	double fRec9[2];
	double fRec8[2];
	double fVec14[2];
	double fRec69[2];
	double fRec68[2];
	double fRec67[2];
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec29[l0] = 0.0;
	for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) fRec28[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fVec0[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec30[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec27[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec26[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec40[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRec39[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fVec1[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec41[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec38[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec37[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec46[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fVec2[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec45[l14] = 0.0;
	for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) fRec44[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fVec3[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec47[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec43[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec42[l19] = 0.0;
	for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) fRec36[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec35[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fRec34[l22] = 0.0;
	for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) fRec33[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fVec4[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fRec48[l25] = 0.0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fRec32[l26] = 0.0;
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) fRec31[l27] = 0.0;
	for (int l28 = 0; (l28 < 3); l28 = (l28 + 1)) fRec25[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fRec24[l29] = 0.0;
	for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) fRec23[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fVec5[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fRec49[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fRec22[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec21[l34] = 0.0;
	for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) fRec50[l35] = 0.0;
	for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) fRec51[l36] = 0.0;
	for (int l37 = 0; (l37 < 32768); l37 = (l37 + 1)) fVec6[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fRec53[l38] = 0.0;
	for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) fRec52[l39] = 0.0;
	for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) fRec20[l40] = 0.0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) fVec7[l41] = 0.0;
	for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) fRec19[l42] = 0.0;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fRec18[l43] = 0.0;
	for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) fRec17[l44] = 0.0;
	for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) fVec8[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec16[l46] = 0.0;
	for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) fRec15[l47] = 0.0;
	for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) fRec14[l48] = 0.0;
	for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) fRec54[l49] = 0.0;
	for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) fRec58[l50] = 0.0;
	for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) fRec57[l51] = 0.0;
	for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) fRec56[l52] = 0.0;
	for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) fRec55[l53] = 0.0;
	for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) fRec62[l54] = 0.0;
	for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) fRec61[l55] = 0.0;
	for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) fVec9[l56] = 0.0;
	for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) fRec60[l57] = 0.0;
	for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) fRec59[l58] = 0.0;
	for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) fRec64[l59] = 0.0;
	for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) fRec63[l60] = 0.0;
	for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) fVec10[l61] = 0.0;
	for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) fRec13[l62] = 0.0;
	for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) fVec11[l63] = 0.0;
	for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) fRec12[l64] = 0.0;
	for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) fRec65[l65] = 0.0;
	for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) fVec12[l66] = 0.0;
	for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) fRec11[l67] = 0.0;
	for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) fRec10[l68] = 0.0;
	for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) fVec13[l69] = 0.0;
	for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) fRec66[l70] = 0.0;
	for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) fRec9[l71] = 0.0;
	for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) fRec8[l72] = 0.0;
	for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) fVec14[l73] = 0.0;
	for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) fRec69[l74] = 0.0;
	for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) fRec68[l75] = 0.0;
	for (int l76 = 0; (l76 < 2); l76 = (l76 + 1)) fRec67[l76] = 0.0;
	for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) fRec6[l77] = 0.0;
	for (int l78 = 0; (l78 < 2); l78 = (l78 + 1)) fRec4[l78] = 0.0;
	for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) fRec2[l79] = 0.0;
	for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) fRec0[l80] = 0.0;
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
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (3.1415926535897931 / fConst0);
	fConst2 = (1.0 / (fConst1 + 1.0));
	fConst3 = (1.0 - fConst1);
	fConst4 = (1.0 / std::tan((20517.741620594938 / fConst0)));
	fConst5 = (1.0 / (fConst4 + 1.0));
	fConst6 = (1.0 - fConst4);
	fConst7 = std::tan((3769.9111843077517 / fConst0));
	fConst8 = (1.0 / fConst7);
	fConst9 = (1.0 / (((fConst8 + 1.0000000000000004) / fConst7) + 1.0));
	fConst10 = mydsp_faustpower2_f(fConst7);
	fConst11 = (1.0 / fConst10);
	fConst12 = std::tan((10053.096491487338 / fConst0));
	fConst13 = (1.0 / fConst12);
	fConst14 = (1.0 / (((fConst13 + 1.0000000000000004) / fConst12) + 1.0));
	fConst15 = (fConst8 + 1.0);
	fConst16 = (1.0 / (fConst7 * fConst15));
	fConst17 = (fConst13 + 1.0);
	fConst18 = (1.0 / fConst17);
	fConst19 = (1.0 - fConst13);
	fConst20 = std::tan((47123.889803846898 / fConst0));
	fConst21 = (1.0 / fConst20);
	fConst22 = (1.0 / (((fConst21 + 1.4142135623730949) / fConst20) + 1.0));
	fConst23 = std::tan((97.389372261283583 / fConst0));
	fConst24 = (1.0 / fConst23);
	fConst25 = (fConst24 + 1.0);
	fConst26 = (1.0 / (fConst23 * fConst25));
	fConst27 = (1.0 / std::tan((609.46897479641984 / fConst0)));
	fConst28 = (1.0 / (fConst27 + 1.0));
	fConst29 = (1.0 - fConst27);
	fConst30 = (1.0 / std::tan((414.69023027385271 / fConst0)));
	fConst31 = (1.0 / (fConst30 + 1.0));
	fConst32 = (1.0 - fConst30);
	fConst33 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst34 = (1.0 / (fConst33 + 1.0));
	fConst35 = (1.0 - fConst33);
	fConst36 = (0.009000000000000008 / fConst0);
	iConst37 = int(std::min<double>(65536.0, std::max<double>(0.0, (0.1111111111111111 * fConst0))));
	fConst38 = (((fConst21 + -1.4142135623730949) / fConst20) + 1.0);
	fConst39 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst20))));
	fConst40 = (0.0 - fConst26);
	fConst41 = ((1.0 - fConst24) / fConst25);
	fConst42 = (((fConst13 + -1.0000000000000004) / fConst12) + 1.0);
	fConst43 = mydsp_faustpower2_f(fConst12);
	fConst44 = (1.0 / fConst43);
	fConst45 = (2.0 * (1.0 - fConst44));
	fConst46 = (0.0 - fConst16);
	fConst47 = (1.0 - fConst8);
	fConst48 = (fConst47 / fConst15);
	fConst49 = (((fConst8 + -1.0000000000000004) / fConst7) + 1.0);
	fConst50 = (2.0 * (1.0 - fConst11));
	fConst51 = (0.0 - (2.0 / fConst10));
	fConst52 = std::tan((942.47779607693792 / fConst0));
	fConst53 = (1.0 / fConst52);
	fConst54 = (fConst53 + 1.0);
	fConst55 = (1.0 / ((fConst54 / fConst52) + 1.0));
	fConst56 = (1.0 - fConst53);
	fConst57 = (1.0 - (fConst56 / fConst52));
	fConst58 = mydsp_faustpower2_f(fConst52);
	fConst59 = (1.0 / fConst58);
	fConst60 = (2.0 * (1.0 - fConst59));
	fConst61 = (0.0 - (1.0 / (fConst12 * fConst17)));
	fConst62 = (0.0 - (2.0 / fConst43));
	fConst63 = (1.0 / ((fConst15 / fConst7) + 1.0));
	fConst64 = (1.0 - (fConst47 / fConst7));
	fConst65 = (1.0 / (((fConst53 + 1.0000000000000004) / fConst52) + 1.0));
	fConst66 = (1.0 / (fConst52 * fConst54));
	fConst67 = (1.0 / fConst15);
	fConst68 = (0.0 - fConst66);
	fConst69 = (fConst56 / fConst54);
	fConst70 = (((fConst53 + -1.0000000000000004) / fConst52) + 1.0);
	fConst71 = (0.0 - (2.0 / fConst58));
	fConst72 = (1.0 / fConst54);
	IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double fSlow0 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider0))));
	double fSlow1 = (1.0000000000000009e-05 * double(fVslider1));
	double fSlow2 = (0.0010000000000000009 * double(fVslider2));
	double fSlow3 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider3))));
	for (int i = 0; (i < ReCount); i = (i + 1)) {
		fRec29[0] = ((0.93028479253239138 * (fRec25[1] + fRec25[2])) - (0.86056958506478287 * fRec29[1]));
		fRec28[0] = (fRec29[0] - ((1.8405051250752198 * fRec28[1]) + (0.86129424393186271 * fRec28[2])));
		double fTemp0 = (0.92544984225177063 * (fRec28[0] + fRec28[2]));
		double fTemp1 = (1.8508996845035413 * fRec28[1]);
		double fTemp2 = ((fTemp1 + fTemp0) / (double(Ranode(int(TUBE_TABLE_12AX7_250k), double(fRec27[1]))) + 100000.0));
		fVec0[0] = fTemp2;
		fRec30[0] = (fConst28 * ((820.0 * (fTemp2 + fVec0[1])) - (fConst29 * fRec30[1])));
		double fTemp3 = double(Ftube(int(TUBE_TABLE_12AX7_250k), double(((fTemp0 + (fRec30[0] + fTemp1)) + -0.84070299999999998))));
		fRec27[0] = ((fTemp3 + (0.0010252475609756097 * (double(Ranode(int(TUBE_TABLE_12AX7_250k), double(fTemp3))) + 100000.0))) + -250.0);
		fRec26[0] = (fConst2 * ((fConst3 * fRec26[1]) + (0.025000000000000001 * (fRec27[0] - fRec27[1]))));
		fRec40[0] = ((0.93028479253239138 * (fRec36[1] + fRec36[2])) - (0.86056958506478287 * fRec40[1]));
		fRec39[0] = (fRec40[0] - ((1.8405051250752198 * fRec39[1]) + (0.86129424393186271 * fRec39[2])));
		double fTemp4 = (0.92544984225177063 * (fRec39[0] + fRec39[2]));
		double fTemp5 = (1.8508996845035413 * fRec39[1]);
		double fTemp6 = ((fTemp5 + fTemp4) / (double(Ranode(int(TUBE_TABLE_12AX7_250k), double(fRec38[1]))) + 100000.0));
		fVec1[0] = fTemp6;
		fRec41[0] = (fConst31 * ((1500.0 * (fTemp6 + fVec1[1])) - (fConst32 * fRec41[1])));
		double fTemp7 = double(Ftube(int(TUBE_TABLE_12AX7_250k), double(((fTemp4 + (fRec41[0] + fTemp5)) + -1.204285))));
		fRec38[0] = ((fTemp7 + (0.00080285666666666665 * (double(Ranode(int(TUBE_TABLE_12AX7_250k), double(fTemp7))) + 100000.0))) + -250.0);
		fRec37[0] = (fConst2 * ((fConst3 * fRec37[1]) + (0.025000000000000001 * (fRec38[0] - fRec38[1]))));
		fRec46[0] = (fSlow0 + (0.999 * fRec46[1]));
		double fTemp8 = (double(buf[i]) * fRec46[0]);
		fVec2[0] = fTemp8;
		fRec45[0] = ((0.93028479253239138 * (fTemp8 + fVec2[1])) - (0.86056958506478287 * fRec45[1]));
		fRec44[0] = (fRec45[0] - ((1.8405051250752198 * fRec44[1]) + (0.86129424393186271 * fRec44[2])));
		double fTemp9 = (0.92544984225177063 * (fRec44[0] + fRec44[2]));
		double fTemp10 = (1.8508996845035413 * fRec44[1]);
		double fTemp11 = ((fTemp10 + fTemp9) / (double(Ranode(int(TUBE_TABLE_12AX7_68k), double(fRec43[1]))) + 100000.0));
		fVec3[0] = fTemp11;
		fRec47[0] = (fConst34 * ((2700.0 * (fTemp11 + fVec3[1])) - (fConst35 * fRec47[1])));
		double fTemp12 = double(Ftube(int(TUBE_TABLE_12AX7_68k), double(((fTemp9 + (fRec47[0] + fTemp10)) + -1.581656))));
		fRec43[0] = ((fTemp12 + (0.00058579851851851849 * (double(Ranode(int(TUBE_TABLE_12AX7_68k), double(fTemp12))) + 100000.0))) + -250.0);
		fRec42[0] = (fConst2 * ((fConst3 * fRec42[1]) + (0.025000000000000001 * (fRec43[0] - fRec43[1]))));
		fRec36[0] = ((0.59999999999999998 * fRec37[0]) + fRec42[0]);
		fRec35[0] = (0.0 - (fConst5 * ((fConst6 * fRec35[1]) - (fRec36[0] + fRec36[1]))));
		fRec34[0] = ((0.93028479253239138 * (fRec35[0] + fRec35[1])) - (0.86056958506478287 * fRec34[1]));
		fRec33[0] = (fRec34[0] - ((1.8405051250752198 * fRec33[1]) + (0.86129424393186271 * fRec33[2])));
		double fTemp13 = (0.92544984225177063 * (fRec33[0] + fRec33[2]));
		double fTemp14 = (1.8508996845035413 * fRec33[1]);
		double fTemp15 = ((fTemp14 + fTemp13) / (double(Ranode(int(TUBE_TABLE_12AX7_250k), double(fRec32[1]))) + 100000.0));
		fVec4[0] = fTemp15;
		fRec48[0] = (fConst31 * ((1500.0 * (fTemp15 + fVec4[1])) - (fConst32 * fRec48[1])));
		double fTemp16 = double(Ftube(int(TUBE_TABLE_12AX7_250k), double(((fTemp13 + (fRec48[0] + fTemp14)) + -1.204285))));
		fRec32[0] = ((fTemp16 + (0.00080285666666666665 * (double(Ranode(int(TUBE_TABLE_12AX7_250k), double(fTemp16))) + 100000.0))) + -250.0);
		fRec31[0] = (fConst2 * ((fConst3 * fRec31[1]) + (0.025000000000000001 * (fRec32[0] - fRec32[1]))));
		fRec25[0] = ((0.59999999999999998 * fRec26[0]) + fRec31[0]);
		fRec24[0] = ((0.93028479253239138 * (fRec25[0] + fRec25[1])) - (0.86056958506478287 * fRec24[1]));
		fRec23[0] = (fRec24[0] - ((1.8405051250752198 * fRec23[1]) + (0.86129424393186271 * fRec23[2])));
		double fTemp17 = (0.92544984225177063 * (fRec23[0] + fRec23[2]));
		double fTemp18 = (1.8508996845035413 * fRec23[1]);
		double fTemp19 = ((fTemp18 + fTemp17) / (double(Ranode(int(TUBE_TABLE_12AX7_250k), double(fRec22[1]))) + 100000.0));
		fVec5[0] = fTemp19;
		fRec49[0] = (fConst28 * ((820.0 * (fTemp19 + fVec5[1])) - (fConst29 * fRec49[1])));
		double fTemp20 = double(Ftube(int(TUBE_TABLE_12AX7_250k), double(((fTemp17 + (fRec49[0] + fTemp18)) + -0.84070299999999998))));
		fRec22[0] = ((fTemp20 + (0.0010252475609756097 * (double(Ranode(int(TUBE_TABLE_12AX7_250k), double(fTemp20))) + 100000.0))) + -250.0);
		fRec21[0] = (fConst2 * ((fConst3 * fRec21[1]) + (0.025000000000000001 * (fRec22[0] - fRec22[1]))));
		fRec50[0] = (fSlow1 + (0.999 * fRec50[1]));
		double fTemp21 = (fRec21[0] * fRec50[0]);
		double fTemp22 = std::fabs(fTemp21);
		fRec51[0] = ((0.99990000000000001 * fRec51[1]) + (9.9999999999988987e-05 * fTemp22));
		double fTemp23 = std::max<double>(fRec51[0], fTemp22);
		fVec6[(IOTA & 32767)] = fTemp23;
		fRec53[0] = ((fTemp23 + fRec53[1]) - fVec6[((IOTA - iConst37) & 32767)]);
		fRec52[0] = ((0.999 * fRec52[1]) + (fConst36 * fRec53[0]));
		double fTemp24 = std::max<double>(-1.0, std::min<double>(-0.01, (fTemp23 + (-1.0 - (1.02 * fRec52[0])))));
		double fTemp25 = (fTemp21 - fTemp24);
		double fTemp26 = (40.100000000000001 * fTemp25);
		double fTemp27 = std::max<double>(-600.0, fTemp26);
		double fTemp28 = (0.0 - (40.100000000000001 * fTemp24));
		double fTemp29 = std::max<double>(-600.0, fTemp28);
		double fTemp30 = (((std::fabs(fTemp26) > 0.0001) ? ((fTemp27 < -50.0) ? (0.0 - (fTemp27 * std::exp(fTemp27))) : (fTemp27 / (1.0 - std::exp((-1.0 * fTemp27))))) : ((fTemp25 * ((134.00083333333336 * fTemp25) + 20.050000000000001)) + 1.0)) - ((std::fabs(fTemp28) > 0.0001) ? ((fTemp29 < -50.0) ? (0.0 - (fTemp29 * std::exp(fTemp29))) : (fTemp29 / (1.0 - std::exp((-1.0 * fTemp29))))) : ((fTemp28 * ((0.083333333333333329 * fTemp28) + 0.5)) + 1.0)));
		fRec20[0] = ((0.024937655860349125 * fTemp30) - (fConst22 * ((fConst38 * fRec20[2]) + (fConst39 * fRec20[1]))));
		double fTemp31 = (fRec20[2] + (fRec20[0] + (2.0 * fRec20[1])));
		fVec7[0] = fTemp31;
		fRec19[0] = ((fConst22 * ((fConst26 * fTemp31) + (fConst40 * fVec7[1]))) - (fConst41 * fRec19[1]));
		fRec18[0] = (0.0 - (fConst18 * ((fConst19 * fRec18[1]) - (fRec19[0] + fRec19[1]))));
		fRec17[0] = (fRec18[0] - (fConst14 * ((fConst42 * fRec17[2]) + (fConst45 * fRec17[1]))));
		double fTemp32 = (fRec17[2] + (fRec17[0] + (2.0 * fRec17[1])));
		fVec8[0] = fTemp32;
		fRec16[0] = ((fConst14 * ((fConst16 * fTemp32) + (fConst46 * fVec8[1]))) - (fConst48 * fRec16[1]));
		fRec15[0] = (fRec16[0] - (fConst9 * ((fConst49 * fRec15[2]) + (fConst50 * fRec15[1]))));
		double fTemp33 = (fConst60 * fRec14[1]);
		fRec14[0] = ((fConst9 * (((fConst11 * fRec15[0]) + (fConst51 * fRec15[1])) + (fConst11 * fRec15[2]))) - (fConst55 * ((fConst57 * fRec14[2]) + fTemp33)));
		fRec54[0] = (fSlow2 + (0.999 * fRec54[1]));
		double fTemp34 = std::max<double>(-1.0, std::min<double>(1.0, ((fRec14[2] + (fConst55 * (fTemp33 + (fConst57 * fRec14[0])))) * std::pow(10.0, (1.2 * fRec54[0])))));
		fRec58[0] = ((fConst61 * fRec19[1]) - (fConst18 * ((fConst19 * fRec58[1]) - (fConst13 * fRec19[0]))));
		fRec57[0] = (fRec58[0] - (fConst14 * ((fConst42 * fRec57[2]) + (fConst45 * fRec57[1]))));
		double fTemp35 = (fConst50 * fRec56[1]);
		fRec56[0] = ((fConst14 * (((fConst44 * fRec57[0]) + (fConst62 * fRec57[1])) + (fConst44 * fRec57[2]))) - (fConst63 * ((fConst64 * fRec56[2]) + fTemp35)));
		double fTemp36 = (fConst60 * fRec55[1]);
		fRec55[0] = ((fRec56[2] + (fConst63 * (fTemp35 + (fConst64 * fRec56[0])))) - (fConst55 * ((fConst57 * fRec55[2]) + fTemp36)));
		double fTemp37 = std::max<double>(-1.0, std::min<double>(1.0, ((fRec55[2] + (fConst55 * (fTemp36 + (fConst57 * fRec55[0])))) * std::pow(10.0, (0.80000000000000004 * fRec54[0])))));
		fRec62[0] = (0.0 - (fConst67 * ((fConst47 * fRec62[1]) - (fConst14 * (fTemp32 + fVec8[1])))));
		fRec61[0] = (fRec62[0] - (fConst9 * ((fConst49 * fRec61[2]) + (fConst50 * fRec61[1]))));
		double fTemp38 = (fRec61[2] + (fRec61[0] + (2.0 * fRec61[1])));
		fVec9[0] = fTemp38;
		fRec60[0] = ((fConst9 * ((fConst66 * fTemp38) + (fConst68 * fVec9[1]))) - (fConst69 * fRec60[1]));
		fRec59[0] = (fRec60[0] - (fConst65 * ((fConst70 * fRec59[2]) + (fConst60 * fRec59[1]))));
		double fTemp39 = std::max<double>(-1.0, std::min<double>(1.0, (fConst65 * ((((fConst59 * fRec59[0]) + (fConst71 * fRec59[1])) + (fConst59 * fRec59[2])) * std::pow(10.0, (2.0 * fRec54[0]))))));
		fRec64[0] = (0.0 - (fConst72 * ((fConst56 * fRec64[1]) - (fConst9 * (fTemp38 + fVec9[1])))));
		fRec63[0] = (fRec64[0] - (fConst65 * ((fConst70 * fRec63[2]) + (fConst60 * fRec63[1]))));
		double fTemp40 = std::max<double>(-1.0, std::min<double>(1.0, (fConst65 * ((fRec63[2] + (fRec63[0] + (2.0 * fRec63[1]))) * std::pow(10.0, (0.90000000000000002 * fRec54[0]))))));
		double fTemp41 = (((1.333521432 * (fTemp34 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp34))))) + (1.584893192 * ((fTemp37 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp37)))) + (fTemp39 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp39))))))) + (1.2589412 * (fTemp40 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp40))))));
		fVec10[0] = fTemp41;
		fRec13[0] = (0.0 - (fConst5 * ((fConst6 * fRec13[1]) - (fTemp41 + fVec10[1]))));
		double fTemp42 = (2.0 * (fRec54[0] + -0.5));
		double fTemp43 = (fRec21[0] * (1.0 - fRec50[0]));
		double fTemp44 = ((fRec13[0] * (1.0 - std::max<double>(0.0, (-1.0 * fTemp42)))) + ((fTemp43 * ((1.25 * (fRec54[0] * ((4.0 * (1.0 - std::fabs(fTemp43))) + -1.0))) + 1.0)) + (0.024937655860349125 * (fTemp30 * (1.0 - std::max<double>(0.0, fTemp42))))));
		fVec11[0] = fTemp44;
		fRec12[0] = (0.0 - (fConst5 * ((fConst6 * fRec12[1]) - (fTemp44 + fVec11[1]))));
		fRec65[0] = (fSlow3 + (0.999 * fRec65[1]));
		double fTemp45 = (fRec12[0] * fRec65[0]);
		fVec12[0] = fTemp45;
		fRec11[0] = ((0.93028479253239138 * (fTemp45 + fVec12[1])) - (0.86056958506478287 * fRec11[1]));
		fRec10[0] = (fRec11[0] - ((1.8405051250752198 * fRec10[1]) + (0.86129424393186271 * fRec10[2])));
		double fTemp46 = (0.92544984225177063 * (fRec10[0] + fRec10[2]));
		double fTemp47 = (1.8508996845035413 * fRec10[1]);
		double fTemp48 = (fTemp47 + fTemp46);
		double fTemp49 = (fTemp48 / (double(Ranode(int(TUBE_TABLE_6V6_250k), double(fRec9[1]))) + 100000.0));
		fVec13[0] = fTemp49;
		fRec66[0] = (fConst5 * ((410.0 * (fTemp49 + fVec13[1])) - (fConst6 * fRec66[1])));
		double fTemp50 = double(Ftube(int(TUBE_TABLE_6V6_250k), double(((fTemp46 + (fRec66[0] + fTemp47)) + -0.65976100000000004))));
		fRec9[0] = ((fTemp50 + (0.0016091731707317074 * (double(Ranode(int(TUBE_TABLE_6V6_250k), double(fTemp50))) + 100000.0))) + -250.0);
		fRec8[0] = (fConst2 * ((fConst3 * fRec8[1]) + (0.025000000000000001 * (fRec9[0] - fRec9[1]))));
		double fTemp51 = (fTemp48 / (double(Ranode(int(TUBE_TABLE_6V6_68k), double(fRec68[1]))) + 100000.0));
		fVec14[0] = fTemp51;
		fRec69[0] = (fConst5 * ((410.0 * (fTemp51 + fVec14[1])) - (fConst6 * fRec69[1])));
		double fTemp52 = double(Ftube(int(TUBE_TABLE_6V6_68k), double(((fTemp46 + (fRec69[0] + fTemp47)) + -0.66454100000000005))));
		fRec68[0] = ((fTemp52 + (0.0016208317073170733 * (double(Ranode(int(TUBE_TABLE_6V6_68k), double(fTemp52))) + 100000.0))) + -250.0);
		fRec67[0] = (fConst2 * ((fConst3 * fRec67[1]) + (0.025000000000000001 * (fRec68[0] - fRec68[1]))));
		double fTemp53 = (std::min<double>(0.69999999999999996, fRec8[0]) + std::max<double>(-0.75, fRec67[0]));
		double fTemp54 = (0.5 * fRec0[1]);
		double fTemp55 = (0.40000000000000002 * fRec2[1]);
		double fTemp56 = (fTemp54 + ((0.29999999999999999 * fRec4[1]) + fTemp55));
		double fTemp57 = ((fTemp53 + (0.20000000000000001 * fRec6[1])) - fTemp56);
		fRec6[0] = fTemp57;
		double fRec7 = (0.0 - (0.20000000000000001 * fTemp57));
		fRec4[0] = (fRec7 + fRec6[1]);
		double fRec5 = (0.29999999999999999 * (fTemp53 - fTemp56));
		fRec2[0] = (fRec5 + fRec4[1]);
		double fRec3 = (0.40000000000000002 * (fTemp53 - (fTemp55 + fTemp54)));
		fRec0[0] = (fRec3 + fRec2[1]);
		double fRec1 = (0.5 * (fTemp53 - fTemp54));
		buf[i] = FAUSTFLOAT((fRec1 + fRec0[1]));
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fVec0[1] = fVec0[0];
		fRec30[1] = fRec30[0];
		fRec27[1] = fRec27[0];
		fRec26[1] = fRec26[0];
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fVec1[1] = fVec1[0];
		fRec41[1] = fRec41[0];
		fRec38[1] = fRec38[0];
		fRec37[1] = fRec37[0];
		fRec46[1] = fRec46[0];
		fVec2[1] = fVec2[0];
		fRec45[1] = fRec45[0];
		fRec44[2] = fRec44[1];
		fRec44[1] = fRec44[0];
		fVec3[1] = fVec3[0];
		fRec47[1] = fRec47[0];
		fRec43[1] = fRec43[0];
		fRec42[1] = fRec42[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		fRec35[1] = fRec35[0];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fVec4[1] = fVec4[0];
		fRec48[1] = fRec48[0];
		fRec32[1] = fRec32[0];
		fRec31[1] = fRec31[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		fRec24[1] = fRec24[0];
		fRec23[2] = fRec23[1];
		fRec23[1] = fRec23[0];
		fVec5[1] = fVec5[0];
		fRec49[1] = fRec49[0];
		fRec22[1] = fRec22[0];
		fRec21[1] = fRec21[0];
		fRec50[1] = fRec50[0];
		fRec51[1] = fRec51[0];
		IOTA = (IOTA + 1);
		fRec53[1] = fRec53[0];
		fRec52[1] = fRec52[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fVec7[1] = fVec7[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fVec8[1] = fVec8[0];
		fRec16[1] = fRec16[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fRec54[1] = fRec54[0];
		fRec58[1] = fRec58[0];
		fRec57[2] = fRec57[1];
		fRec57[1] = fRec57[0];
		fRec56[2] = fRec56[1];
		fRec56[1] = fRec56[0];
		fRec55[2] = fRec55[1];
		fRec55[1] = fRec55[0];
		fRec62[1] = fRec62[0];
		fRec61[2] = fRec61[1];
		fRec61[1] = fRec61[0];
		fVec9[1] = fVec9[0];
		fRec60[1] = fRec60[0];
		fRec59[2] = fRec59[1];
		fRec59[1] = fRec59[0];
		fRec64[1] = fRec64[0];
		fRec63[2] = fRec63[1];
		fRec63[1] = fRec63[0];
		fVec10[1] = fVec10[0];
		fRec13[1] = fRec13[0];
		fVec11[1] = fVec11[0];
		fRec12[1] = fRec12[0];
		fRec65[1] = fRec65[0];
		fVec12[1] = fVec12[0];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fVec13[1] = fVec13[0];
		fRec66[1] = fRec66[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fVec14[1] = fVec14[0];
		fRec69[1] = fRec69[0];
		fRec68[1] = fRec68[0];
		fRec67[1] = fRec67[0];
		fRec6[1] = fRec6[0];
		fRec4[1] = fRec4[0];
		fRec2[1] = fRec2[0];
		fRec0[1] = fRec0[0];
	}
	smp.down(buf, output0);
#undef fVslider0
#undef fVslider1
#undef fVslider2
#undef fVslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	fVslider2_ = reg.registerFloatVar("gxdistortion.drive","","SA","",&fVslider2, 0.34999999999999998, 0.0, 1.0, 0.01, 0);
	fVslider1_ = reg.registerFloatVar("gxdistortion.wet_dry","","SA","",&fVslider1, 100.0, 0.0, 100.0, 1.0, 0);
	fVslider0_ = reg.registerFloatVar("amp2.stage1.Pregain","","SA","",&fVslider0, -6.0, -20.0, 20.0, 0.10000000000000001, 0);
	fVslider3_ = reg.registerFloatVar("amp2.stage2.gain1","","SA","",&fVslider3, -6.0, -20.0, 20.0, 0.10000000000000001, 0);
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
