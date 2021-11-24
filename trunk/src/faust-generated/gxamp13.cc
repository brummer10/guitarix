// generated from file '../src/faust/gxamp13.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxamp13 {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int sample_rate;
	int fSampleRate;
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
	double fRec32[2];
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
	double fRec40[3];
	double fVec3[2];
	double fRec39[2];
	double fRec38[2];
	double fConst39;
	double fConst41;
	double fConst42;
	double fRec37[3];
	double fVec4[2];
	double fConst43;
	double fConst44;
	double fConst45;
	double fRec36[2];
	double fConst46;
	double fConst47;
	double fRec35[3];
	double fConst48;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst56;
	double fConst57;
	double fRec34[3];
	double fConst58;
	double fRec44[2];
	double fRec43[3];
	double fConst59;
	double fConst60;
	double fConst61;
	double fRec42[3];
	double fRec41[3];
	double fConst62;
	double fConst63;
	double fConst64;
	double fRec48[2];
	double fRec47[3];
	double fVec5[2];
	double fConst65;
	double fConst66;
	double fRec46[2];
	double fConst67;
	double fRec45[3];
	double fConst68;
	double fConst69;
	double fRec50[2];
	double fRec49[3];
	double fVec6[2];
	double fRec33[2];
	double fVec7[2];
	double fRec27[2];
	double fRec26[3];
	double fConst71;
	double fVec8[2];
	double fConst72;
	double fRec51[2];
	double fRec25[2];
	double fRec24[2];
	double fRec52[2];
	double fRec17[3];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec53[2];
	double fVec9[2];
	double fRec16[2];
	double fRec15[2];
	double fRec14[3];
	double fVec10[2];
	double fRec54[2];
	double fRec13[2];
	double fRec12[2];
	double fRec55[2];
	double fRec5[3];
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fVec11[2];
	double fRec56[2];
	double fRec1[2];
	double fRec0[2];
	double fRec57[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec58[2];

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
	id = "6DJ8 feedback";
	name = N_("6DJ8 feedback");
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
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec32[l19] = 0.0;
	for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) fRec40[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fVec3[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fRec39[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fRec38[l23] = 0.0;
	for (int l24 = 0; (l24 < 3); l24 = (l24 + 1)) fRec37[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fVec4[l25] = 0.0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fRec36[l26] = 0.0;
	for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) fRec35[l27] = 0.0;
	for (int l28 = 0; (l28 < 3); l28 = (l28 + 1)) fRec34[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fRec44[l29] = 0.0;
	for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) fRec43[l30] = 0.0;
	for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) fRec42[l31] = 0.0;
	for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) fRec41[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fRec48[l33] = 0.0;
	for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) fRec47[l34] = 0.0;
	for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) fVec5[l35] = 0.0;
	for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) fRec46[l36] = 0.0;
	for (int l37 = 0; (l37 < 3); l37 = (l37 + 1)) fRec45[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fRec50[l38] = 0.0;
	for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) fRec49[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fVec6[l40] = 0.0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) fRec33[l41] = 0.0;
	for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) fVec7[l42] = 0.0;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fRec27[l43] = 0.0;
	for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) fRec26[l44] = 0.0;
	for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) fVec8[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec51[l46] = 0.0;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) fRec25[l47] = 0.0;
	for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) fRec24[l48] = 0.0;
	for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) fRec52[l49] = 0.0;
	for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) fRec17[l50] = 0.0;
	for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) fRec53[l51] = 0.0;
	for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) fVec9[l52] = 0.0;
	for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) fRec16[l53] = 0.0;
	for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) fRec15[l54] = 0.0;
	for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) fRec14[l55] = 0.0;
	for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) fVec10[l56] = 0.0;
	for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) fRec54[l57] = 0.0;
	for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) fRec13[l58] = 0.0;
	for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) fRec12[l59] = 0.0;
	for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) fRec55[l60] = 0.0;
	for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) fRec5[l61] = 0.0;
	for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) fRec4[l62] = 0.0;
	for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) fRec3[l63] = 0.0;
	for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) fRec2[l64] = 0.0;
	for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) fVec11[l65] = 0.0;
	for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) fRec56[l66] = 0.0;
	for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) fRec1[l67] = 0.0;
	for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) fRec0[l68] = 0.0;
	for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) fRec57[l69] = 0.0;
	for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) fRec58[l70] = 0.0;
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

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fCheckbox0 (*fCheckbox0_)
#define fCheckbox1 (*fCheckbox1_)
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	int iSlow0 = int(double(fCheckbox0));
	int iSlow1 = int(double(fCheckbox1));
	double fSlow2 = (1.0000000000000009e-05 * double(fVslider0));
	double fSlow3 = (0.0010000000000000009 * double(fVslider1));
	double fSlow4 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider2))));
	double fSlow5 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider3))));
	for (int i0 = 0; (i0 < ReCount); i0 = (i0 + 1)) {
		fRec9[0] = ((0.93028479253239138 * (fRec5[1] + fRec5[2])) - (0.86056958506478287 * fRec9[1]));
		fRec8[0] = (fRec9[0] - ((1.8405051250752198 * fRec8[1]) + (0.86129424393186271 * fRec8[2])));
		double fTemp0 = (0.92544984225177063 * (fRec8[0] + fRec8[2]));
		double fTemp1 = (1.8508996845035413 * fRec8[1]);
		double fTemp2 = ((fTemp1 + fTemp0) / (double(Ranode(int(TUBE_TABLE_6DJ8_250k), double(fRec7[1]))) + 100000.0));
		fVec0[0] = fTemp2;
		fRec10[0] = (fConst9 * ((820.0 * (fTemp2 + fVec0[1])) - (fConst10 * fRec10[1])));
		fRec7[0] = (double(Ftube(int(TUBE_TABLE_6DJ8_250k), double(((fTemp0 + (fRec10[0] + fTemp1)) + -0.79704299999999995)))) + -32.799634146341475);
		fRec6[0] = ((0.050000000000000003 * ((fConst4 * fRec7[0]) + (fConst11 * fRec7[1]))) - (fConst12 * fRec6[1]));
		fRec11[0] = (fConst14 * ((fConst15 * fRec11[1]) + (0.050000000000000003 * (fRec7[0] - fRec7[1]))));
		fRec21[0] = ((0.93028479253239138 * (fRec17[1] + fRec17[2])) - (0.86056958506478287 * fRec21[1]));
		fRec20[0] = (fRec21[0] - ((1.8405051250752198 * fRec20[1]) + (0.86129424393186271 * fRec20[2])));
		double fTemp3 = (0.92544984225177063 * (fRec20[0] + fRec20[2]));
		double fTemp4 = (1.8508996845035413 * fRec20[1]);
		double fTemp5 = ((fTemp4 + fTemp3) / (double(Ranode(int(TUBE_TABLE_6DJ8_250k), double(fRec19[1]))) + 100000.0));
		fVec1[0] = fTemp5;
		fRec22[0] = (fConst17 * ((1500.0 * (fTemp5 + fVec1[1])) - (fConst18 * fRec22[1])));
		fRec19[0] = (double(Ftube(int(TUBE_TABLE_6DJ8_250k), double(((fTemp3 + (fRec22[0] + fTemp4)) + -1.271609)))) + -45.226066666666668);
		fRec18[0] = ((0.050000000000000003 * ((fConst4 * fRec19[0]) + (fConst11 * fRec19[1]))) - (fConst12 * fRec18[1]));
		fRec23[0] = (fConst14 * ((fConst15 * fRec23[1]) + (0.050000000000000003 * (fRec19[0] - fRec19[1]))));
		double fTemp6 = double(buf[i0]);
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
		fRec32[0] = (fSlow3 + (0.999 * fRec32[1]));
		double fTemp17 = (2.0 * (fRec32[0] + -0.5));
		double fTemp18 = std::pow(10.0, (2.0 * fRec32[0]));
		double fTemp19 = (0.024937655860349125 * (fRec31[0] * fTemp15));
		double fTemp20 = std::max<double>(-1.0, std::min<double>(1.0, (fTemp18 * std::max<double>(-0.69999999999999996, std::min<double>(0.69999999999999996, fTemp19)))));
		fRec40[0] = (fTemp19 - (fConst36 * ((fConst37 * fRec40[2]) + (fConst38 * fRec40[1]))));
		double fTemp21 = (fRec40[2] + (fRec40[0] + (2.0 * fRec40[1])));
		fVec3[0] = fTemp21;
		fRec39[0] = ((fConst36 * ((fConst4 * fTemp21) + (fConst11 * fVec3[1]))) - (fConst12 * fRec39[1]));
		fRec38[0] = (0.0 - (fConst32 * ((fConst33 * fRec38[1]) - (fRec39[0] + fRec39[1]))));
		fRec37[0] = (fRec38[0] - (fConst28 * ((fConst39 * fRec37[2]) + (fConst42 * fRec37[1]))));
		double fTemp22 = (fRec37[2] + (fRec37[0] + (2.0 * fRec37[1])));
		fVec4[0] = fTemp22;
		fRec36[0] = ((fConst28 * ((fConst30 * fTemp22) + (fConst43 * fVec4[1]))) - (fConst45 * fRec36[1]));
		fRec35[0] = (fRec36[0] - (fConst23 * ((fConst46 * fRec35[2]) + (fConst47 * fRec35[1]))));
		double fTemp23 = (fConst57 * fRec34[1]);
		fRec34[0] = ((fConst23 * (((fConst25 * fRec35[0]) + (fConst48 * fRec35[1])) + (fConst25 * fRec35[2]))) - (fConst52 * ((fConst54 * fRec34[2]) + fTemp23)));
		double fTemp24 = std::max<double>(-1.0, std::min<double>(1.0, ((fRec34[2] + (fConst52 * (fTemp23 + (fConst54 * fRec34[0])))) * std::pow(10.0, (1.2 * fRec32[0])))));
		fRec44[0] = ((fConst58 * fRec39[1]) - (fConst32 * ((fConst33 * fRec44[1]) - (fConst27 * fRec39[0]))));
		fRec43[0] = (fRec44[0] - (fConst28 * ((fConst39 * fRec43[2]) + (fConst42 * fRec43[1]))));
		double fTemp25 = (fConst47 * fRec42[1]);
		fRec42[0] = ((fConst28 * (((fConst41 * fRec43[0]) + (fConst59 * fRec43[1])) + (fConst41 * fRec43[2]))) - (fConst60 * ((fConst61 * fRec42[2]) + fTemp25)));
		double fTemp26 = (fConst57 * fRec41[1]);
		fRec41[0] = ((fRec42[2] + (fConst60 * (fTemp25 + (fConst61 * fRec42[0])))) - (fConst52 * ((fConst54 * fRec41[2]) + fTemp26)));
		double fTemp27 = std::max<double>(-1.0, std::min<double>(1.0, ((fRec41[2] + (fConst52 * (fTemp26 + (fConst54 * fRec41[0])))) * std::pow(10.0, (0.80000000000000004 * fRec32[0])))));
		fRec48[0] = (0.0 - (fConst64 * ((fConst44 * fRec48[1]) - (fConst28 * (fTemp22 + fVec4[1])))));
		fRec47[0] = (fRec48[0] - (fConst23 * ((fConst46 * fRec47[2]) + (fConst47 * fRec47[1]))));
		double fTemp28 = (fRec47[2] + (fRec47[0] + (2.0 * fRec47[1])));
		fVec5[0] = fTemp28;
		fRec46[0] = ((fConst23 * ((fConst63 * fTemp28) + (fConst65 * fVec5[1]))) - (fConst66 * fRec46[1]));
		fRec45[0] = (fRec46[0] - (fConst62 * ((fConst67 * fRec45[2]) + (fConst57 * fRec45[1]))));
		double fTemp29 = std::max<double>(-1.0, std::min<double>(1.0, (fConst62 * (fTemp18 * (((fConst56 * fRec45[0]) + (fConst68 * fRec45[1])) + (fConst56 * fRec45[2]))))));
		fRec50[0] = (0.0 - (fConst69 * ((fConst53 * fRec50[1]) - (fConst23 * (fTemp28 + fVec5[1])))));
		fRec49[0] = (fRec50[0] - (fConst62 * ((fConst67 * fRec49[2]) + (fConst57 * fRec49[1]))));
		double fTemp30 = std::max<double>(-1.0, std::min<double>(1.0, (fConst62 * ((fRec49[2] + (fRec49[0] + (2.0 * fRec49[1]))) * std::pow(10.0, (0.90000000000000002 * fRec32[0]))))));
		double fTemp31 = (((1.333521432 * (fTemp24 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp24))))) + (1.584893192 * ((fTemp27 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp27)))) + (fTemp29 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp29))))))) + (1.2589412 * (fTemp30 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp30))))));
		fVec6[0] = fTemp31;
		fRec33[0] = (0.0 - (fConst6 * ((fConst7 * fRec33[1]) - (fTemp31 + fVec6[1]))));
		double fTemp32 = ((fTemp15 * ((fTemp16 * ((1.25 * (fRec32[0] * ((0.099750623441396499 * (1.0 - std::fabs((0.024937655860349125 * (fTemp16 * fTemp15))))) + -0.024937655860349125))) + 0.024937655860349125)) + (0.024937655860349125 * (fRec31[0] * (1.0 - std::max<double>(0.0, fTemp17)))))) + ((0.5 * (fTemp20 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp20))))) + (fRec33[0] * (1.0 - std::max<double>(0.0, (-1.0 * fTemp17))))));
		fVec7[0] = fTemp32;
		fRec27[0] = ((0.93028479253239138 * (fTemp32 + fVec7[1])) - (0.86056958506478287 * fRec27[1]));
		fRec26[0] = (fRec27[0] - ((1.8405051250752198 * fRec26[1]) + (0.86129424393186271 * fRec26[2])));
		double fTemp33 = (0.92544984225177063 * (fRec26[0] + fRec26[2]));
		double fTemp34 = (1.8508996845035413 * fRec26[1]);
		double fTemp35 = ((fTemp34 + fTemp33) / (double(Ranode(int(TUBE_TABLE_6DJ8_68k), double(fRec25[1]))) + 100000.0));
		fVec8[0] = fTemp35;
		fRec51[0] = (fConst71 * ((2700.0 * (fTemp35 + fVec8[1])) - (fConst72 * fRec51[1])));
		fRec25[0] = (double(Ftube(int(TUBE_TABLE_6DJ8_68k), double(((fTemp33 + (fRec51[0] + fTemp34)) + -1.8639460000000001)))) + -60.964962962962957);
		fRec24[0] = ((0.050000000000000003 * ((fConst4 * fRec25[0]) + (fConst11 * fRec25[1]))) - (fConst12 * fRec24[1]));
		fRec52[0] = (fConst14 * ((fConst15 * fRec52[1]) + (0.050000000000000003 * (fRec25[0] - fRec25[1]))));
		fRec17[0] = ((0.59999999999999998 * (iSlow1 ? fRec23[0] : fRec18[0])) - (iSlow1 ? fRec52[0] : fRec24[0]));
		fRec53[0] = (fSlow4 + (0.999 * fRec53[1]));
		double fTemp36 = (fRec17[0] * fRec53[0]);
		fVec9[0] = fTemp36;
		fRec16[0] = (0.0 - (fConst6 * ((fConst7 * fRec16[1]) - (fTemp36 + fVec9[1]))));
		fRec15[0] = ((0.93028479253239138 * (fRec16[0] + fRec16[1])) - (0.86056958506478287 * fRec15[1]));
		fRec14[0] = (fRec15[0] - ((1.8405051250752198 * fRec14[1]) + (0.86129424393186271 * fRec14[2])));
		double fTemp37 = (0.92544984225177063 * (fRec14[0] + fRec14[2]));
		double fTemp38 = (1.8508996845035413 * fRec14[1]);
		double fTemp39 = ((fTemp38 + fTemp37) / (double(Ranode(int(TUBE_TABLE_6DJ8_250k), double(fRec13[1]))) + 100000.0));
		fVec10[0] = fTemp39;
		fRec54[0] = (fConst17 * ((1500.0 * (fTemp39 + fVec10[1])) - (fConst18 * fRec54[1])));
		fRec13[0] = (double(Ftube(int(TUBE_TABLE_6DJ8_250k), double(((fTemp37 + (fRec54[0] + fTemp38)) + -1.271609)))) + -45.226066666666668);
		fRec12[0] = ((0.050000000000000003 * ((fConst4 * fRec13[0]) + (fConst11 * fRec13[1]))) - (fConst12 * fRec12[1]));
		fRec55[0] = (fConst14 * ((fConst15 * fRec55[1]) + (0.050000000000000003 * (fRec13[0] - fRec13[1]))));
		fRec5[0] = ((0.59999999999999998 * (iSlow1 ? fRec11[0] : fRec6[0])) + (iSlow1 ? fRec55[0] : fRec12[0]));
		fRec4[0] = (0.0 - (fConst6 * ((fConst7 * fRec4[1]) - (fRec5[0] + fRec5[1]))));
		fRec3[0] = ((0.93028479253239138 * (fRec4[0] + fRec4[1])) - (0.86056958506478287 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.86129424393186271 * fRec2[2])));
		double fTemp40 = (0.92544984225177063 * (fRec2[0] + fRec2[2]));
		double fTemp41 = (1.8508996845035413 * fRec2[1]);
		double fTemp42 = ((fTemp41 + fTemp40) / (double(Ranode(int(TUBE_TABLE_6DJ8_250k), double(fRec1[1]))) + 100000.0));
		fVec11[0] = fTemp42;
		fRec56[0] = (fConst9 * ((820.0 * (fTemp42 + fVec11[1])) - (fConst10 * fRec56[1])));
		fRec1[0] = (double(Ftube(int(TUBE_TABLE_6DJ8_250k), double(((fTemp40 + (fRec56[0] + fTemp41)) + -0.79704299999999995)))) + -32.799634146341475);
		fRec0[0] = ((0.050000000000000003 * ((fConst4 * fRec1[0]) + (fConst11 * fRec1[1]))) - (fConst12 * fRec0[1]));
		fRec57[0] = (fConst14 * ((fConst15 * fRec57[1]) + (0.050000000000000003 * (fRec1[0] - fRec1[1]))));
		fRec58[0] = (fSlow5 + (0.999 * fRec58[1]));
		buf[i0] = FAUSTFLOAT(((iSlow0 ? fRec57[0] : fRec0[0]) * fRec58[0]));
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
		fRec32[1] = fRec32[0];
		fRec40[2] = fRec40[1];
		fRec40[1] = fRec40[0];
		fVec3[1] = fVec3[0];
		fRec39[1] = fRec39[0];
		fRec38[1] = fRec38[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fVec4[1] = fVec4[0];
		fRec36[1] = fRec36[0];
		fRec35[2] = fRec35[1];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec44[1] = fRec44[0];
		fRec43[2] = fRec43[1];
		fRec43[1] = fRec43[0];
		fRec42[2] = fRec42[1];
		fRec42[1] = fRec42[0];
		fRec41[2] = fRec41[1];
		fRec41[1] = fRec41[0];
		fRec48[1] = fRec48[0];
		fRec47[2] = fRec47[1];
		fRec47[1] = fRec47[0];
		fVec5[1] = fVec5[0];
		fRec46[1] = fRec46[0];
		fRec45[2] = fRec45[1];
		fRec45[1] = fRec45[0];
		fRec50[1] = fRec50[0];
		fRec49[2] = fRec49[1];
		fRec49[1] = fRec49[0];
		fVec6[1] = fVec6[0];
		fRec33[1] = fRec33[0];
		fVec7[1] = fVec7[0];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fVec8[1] = fVec8[0];
		fRec51[1] = fRec51[0];
		fRec25[1] = fRec25[0];
		fRec24[1] = fRec24[0];
		fRec52[1] = fRec52[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fRec53[1] = fRec53[0];
		fVec9[1] = fVec9[0];
		fRec16[1] = fRec16[0];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fVec10[1] = fVec10[0];
		fRec54[1] = fRec54[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec55[1] = fRec55[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fVec11[1] = fVec11[0];
		fRec56[1] = fRec56[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec57[1] = fRec57[0];
		fRec58[1] = fRec58[0];
	}
	smp.down(buf, output0);
#undef fCheckbox0
#undef fCheckbox1
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
	fVslider1_ = reg.registerFloatVar("gxdistortion.drive","","SA","",&fVslider1, 0.34999999999999998, 0.0, 1.0, 0.01, 0);
	fVslider0_ = reg.registerFloatVar("gxdistortion.wet_dry","","SA","",&fVslider0, 100.0, 0.0, 100.0, 1.0, 0);
	fCheckbox1_ = reg.registerFloatVar("amp.highgain","","BA",N_("Allow frequencies below 31Hz"),&fCheckbox1, 0.0, 0.0, 1.0, 1.0, 0);
	fVslider2_ = reg.registerFloatVar("amp2.stage1.Pregain","","SA","",&fVslider2, -6.0, -20.0, 20.0, 0.10000000000000001, 0);
	fCheckbox0_ = reg.registerFloatVar("amp.highgain","","BA",N_("Allow frequencies below 31Hz"),&fCheckbox0, 0.0, 0.0, 1.0, 1.0, 0);
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

} // end namespace gxamp13
