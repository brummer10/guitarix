// generated from file '../src/faust/gxamp17.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxamp17 {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int sample_rate;
	int fSampleRate;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst4;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	double fRec9[2];
	double fRec8[3];
	double fConst6;
	double fVec0[2];
	double fConst7;
	double fRec10[2];
	double fRec7[2];
	double fConst8;
	double fConst9;
	double fRec6[2];
	double fConst11;
	double fConst12;
	double fRec11[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec17[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec23[2];
	double fConst15;
	double fConst16;
	double fConst18;
	double fConst19;
	double fConst22;
	double fConst23;
	double fConst25;
	double fConst26;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst35;
	double fConst37;
	double fConst38;
	double fRec35[2];
	int IOTA0;
	double fVec1[32768];
	int iConst39;
	double fRec34[2];
	double fConst40;
	double fRec33[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec36[2];
	double fRec32[3];
	double fVec2[2];
	double fRec31[2];
	double fConst41;
	double fConst43;
	double fRec30[2];
	double fRec29[3];
	double fVec3[2];
	double fConst44;
	double fConst46;
	double fRec28[2];
	double fRec27[3];
	double fVec4[2];
	double fConst47;
	double fConst49;
	double fRec26[2];
	double fRec25[3];
	double fConst50;
	double fConst51;
	double fConst52;
	double fRec38[2];
	double fRec37[3];
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fRec42[2];
	double fRec41[3];
	double fConst59;
	double fRec40[3];
	double fRec39[3];
	double fConst60;
	double fConst61;
	double fConst62;
	double fRec45[2];
	double fRec44[3];
	double fConst63;
	double fRec43[3];
	double fVec5[2];
	double fConst65;
	double fConst66;
	double fRec24[2];
	double fVec6[2];
	double fRec22[2];
	double fRec21[3];
	double fConst68;
	double fVec7[2];
	double fConst69;
	double fRec46[2];
	double fRec20[2];
	double fRec19[2];
	double fRec47[2];
	double fRec51[2];
	double fRec50[3];
	double fConst71;
	double fVec8[2];
	double fConst72;
	double fRec52[2];
	double fRec49[2];
	double fRec48[2];
	double fRec53[2];
	double fRec18[3];
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
	id = "12AT7 feedback";
	name = N_("12AT7 feedback");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec9[l0] = 0.0;
	for (int l1 = 0; l1 < 3; l1 = l1 + 1) fRec8[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fVec0[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec10[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec7[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec6[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec11[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec17[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec23[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec35[l9] = 0.0;
	for (int l10 = 0; l10 < 32768; l10 = l10 + 1) fVec1[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec34[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec33[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec36[l13] = 0.0;
	for (int l14 = 0; l14 < 3; l14 = l14 + 1) fRec32[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fVec2[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec31[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec30[l17] = 0.0;
	for (int l18 = 0; l18 < 3; l18 = l18 + 1) fRec29[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fVec3[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec28[l20] = 0.0;
	for (int l21 = 0; l21 < 3; l21 = l21 + 1) fRec27[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fVec4[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec26[l23] = 0.0;
	for (int l24 = 0; l24 < 3; l24 = l24 + 1) fRec25[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec38[l25] = 0.0;
	for (int l26 = 0; l26 < 3; l26 = l26 + 1) fRec37[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec42[l27] = 0.0;
	for (int l28 = 0; l28 < 3; l28 = l28 + 1) fRec41[l28] = 0.0;
	for (int l29 = 0; l29 < 3; l29 = l29 + 1) fRec40[l29] = 0.0;
	for (int l30 = 0; l30 < 3; l30 = l30 + 1) fRec39[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec45[l31] = 0.0;
	for (int l32 = 0; l32 < 3; l32 = l32 + 1) fRec44[l32] = 0.0;
	for (int l33 = 0; l33 < 3; l33 = l33 + 1) fRec43[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fVec5[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec24[l35] = 0.0;
	for (int l36 = 0; l36 < 2; l36 = l36 + 1) fVec6[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec22[l37] = 0.0;
	for (int l38 = 0; l38 < 3; l38 = l38 + 1) fRec21[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fVec7[l39] = 0.0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec46[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec20[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) fRec19[l42] = 0.0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fRec47[l43] = 0.0;
	for (int l44 = 0; l44 < 2; l44 = l44 + 1) fRec51[l44] = 0.0;
	for (int l45 = 0; l45 < 3; l45 = l45 + 1) fRec50[l45] = 0.0;
	for (int l46 = 0; l46 < 2; l46 = l46 + 1) fVec8[l46] = 0.0;
	for (int l47 = 0; l47 < 2; l47 = l47 + 1) fRec52[l47] = 0.0;
	for (int l48 = 0; l48 < 2; l48 = l48 + 1) fRec49[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec48[l49] = 0.0;
	for (int l50 = 0; l50 < 2; l50 = l50 + 1) fRec53[l50] = 0.0;
	for (int l51 = 0; l51 < 3; l51 = l51 + 1) fRec18[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fVec9[l52] = 0.0;
	for (int l53 = 0; l53 < 2; l53 = l53 + 1) fRec16[l53] = 0.0;
	for (int l54 = 0; l54 < 2; l54 = l54 + 1) fRec15[l54] = 0.0;
	for (int l55 = 0; l55 < 3; l55 = l55 + 1) fRec14[l55] = 0.0;
	for (int l56 = 0; l56 < 2; l56 = l56 + 1) fVec10[l56] = 0.0;
	for (int l57 = 0; l57 < 2; l57 = l57 + 1) fRec54[l57] = 0.0;
	for (int l58 = 0; l58 < 2; l58 = l58 + 1) fRec13[l58] = 0.0;
	for (int l59 = 0; l59 < 2; l59 = l59 + 1) fRec12[l59] = 0.0;
	for (int l60 = 0; l60 < 2; l60 = l60 + 1) fRec55[l60] = 0.0;
	for (int l61 = 0; l61 < 3; l61 = l61 + 1) fRec5[l61] = 0.0;
	for (int l62 = 0; l62 < 2; l62 = l62 + 1) fRec4[l62] = 0.0;
	for (int l63 = 0; l63 < 2; l63 = l63 + 1) fRec3[l63] = 0.0;
	for (int l64 = 0; l64 < 3; l64 = l64 + 1) fRec2[l64] = 0.0;
	for (int l65 = 0; l65 < 2; l65 = l65 + 1) fVec11[l65] = 0.0;
	for (int l66 = 0; l66 < 2; l66 = l66 + 1) fRec56[l66] = 0.0;
	for (int l67 = 0; l67 < 2; l67 = l67 + 1) fRec1[l67] = 0.0;
	for (int l68 = 0; l68 < 2; l68 = l68 + 1) fRec0[l68] = 0.0;
	for (int l69 = 0; l69 < 2; l69 = l69 + 1) fRec57[l69] = 0.0;
	for (int l70 = 0; l70 < 2; l70 = l70 + 1) fRec58[l70] = 0.0;
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
	double fConst13 = std::tan(942.4777960769379 / fConst0);
	double fConst14 = mydsp_faustpower2_f(fConst13);
	fConst15 = 1.0 / fConst14;
	fConst16 = 2.0 * (1.0 - fConst15);
	double fConst17 = 1.0 / fConst13;
	fConst18 = (fConst17 + -1.0000000000000004) / fConst13 + 1.0;
	fConst19 = 1.0 / ((fConst17 + 1.0000000000000004) / fConst13 + 1.0);
	double fConst20 = std::tan(3769.9111843077517 / fConst0);
	double fConst21 = mydsp_faustpower2_f(fConst20);
	fConst22 = 1.0 / fConst21;
	fConst23 = 2.0 * (1.0 - fConst22);
	double fConst24 = 1.0 / fConst20;
	fConst25 = (fConst24 + -1.0000000000000004) / fConst20 + 1.0;
	fConst26 = 1.0 / ((fConst24 + 1.0000000000000004) / fConst20 + 1.0);
	double fConst27 = std::tan(10053.096491487338 / fConst0);
	double fConst28 = mydsp_faustpower2_f(fConst27);
	fConst29 = 1.0 / fConst28;
	fConst30 = 2.0 * (1.0 - fConst29);
	fConst31 = 1.0 / fConst27;
	fConst32 = (fConst31 + -1.0000000000000004) / fConst27 + 1.0;
	fConst33 = 1.0 / ((fConst31 + 1.0000000000000004) / fConst27 + 1.0);
	double fConst34 = std::tan(47123.8898038469 / fConst0);
	fConst35 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst34));
	double fConst36 = 1.0 / fConst34;
	fConst37 = (fConst36 + -1.414213562373095) / fConst34 + 1.0;
	fConst38 = 1.0 / ((fConst36 + 1.414213562373095) / fConst34 + 1.0);
	iConst39 = int(std::min<double>(65536.0, std::max<double>(0.0, 0.1111111111111111 * fConst0)));
	fConst40 = 0.009000000000000008 / fConst0;
	fConst41 = 1.0 - fConst31;
	double fConst42 = fConst31 + 1.0;
	fConst43 = 1.0 / fConst42;
	fConst44 = 1.0 - fConst24;
	double fConst45 = fConst24 + 1.0;
	fConst46 = 1.0 / fConst45;
	fConst47 = 1.0 - fConst17;
	double fConst48 = fConst17 + 1.0;
	fConst49 = 1.0 / fConst48;
	fConst50 = fConst47 / fConst48;
	fConst51 = 1.0 / (fConst13 * fConst48);
	fConst52 = 0.0 - fConst51;
	fConst53 = 0.0 - 2.0 / fConst14;
	fConst54 = 1.0 - fConst47 / fConst13;
	fConst55 = 1.0 / (fConst48 / fConst13 + 1.0);
	fConst56 = 1.0 - fConst44 / fConst20;
	fConst57 = 1.0 / (fConst45 / fConst20 + 1.0);
	fConst58 = 0.0 - 1.0 / (fConst27 * fConst42);
	fConst59 = 0.0 - 2.0 / fConst28;
	fConst60 = fConst44 / fConst45;
	fConst61 = 1.0 / (fConst20 * fConst45);
	fConst62 = 0.0 - fConst61;
	fConst63 = 0.0 - 2.0 / fConst21;
	double fConst64 = 1.0 / std::tan(20517.741620594938 / fConst0);
	fConst65 = 1.0 - fConst64;
	fConst66 = 1.0 / (fConst64 + 1.0);
	double fConst67 = 1.0 / std::tan(270.1769682087222 / fConst0);
	fConst68 = 1.0 - fConst67;
	fConst69 = 1.0 / (fConst67 + 1.0);
	double fConst70 = 1.0 / std::tan(414.6902302738527 / fConst0);
	fConst71 = 1.0 - fConst70;
	fConst72 = 1.0 / (fConst70 + 1.0);
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
#define fCheckbox1 (*fCheckbox1_)
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	int iSlow0 = int(double(fCheckbox0));
	int iSlow1 = int(double(fCheckbox1));
	double fSlow2 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
	double fSlow3 = 0.0010000000000000009 * double(fVslider1);
	double fSlow4 = 1.000000000000001e-05 * double(fVslider2);
	double fSlow5 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider3));
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		fRec9[0] = 0.9302847925323914 * (fRec5[1] + fRec5[2]) - 0.8605695850647829 * fRec9[1];
		fRec8[0] = fRec9[0] - (1.8405051250752198 * fRec8[1] + 0.8612942439318627 * fRec8[2]);
		double fTemp0 = 1.8508996845035413 * fRec8[1];
		double fTemp1 = 0.9254498422517706 * (fRec8[0] + fRec8[2]);
		double fTemp2 = (fTemp0 + fTemp1) / (Ranode(TUBE_TABLE_12AT7_250k, fRec7[1]) + 1e+05);
		fVec0[0] = fTemp2;
		fRec10[0] = fConst7 * (8.2e+02 * (fTemp2 + fVec0[1]) - fConst6 * fRec10[1]);
		fRec7[0] = Ftube(TUBE_TABLE_12AT7_250k, fTemp1 + fRec10[0] + fTemp0 + -1.256962) + -96.7119512195122;
		fRec6[0] = 0.025 * (fConst8 * fRec7[0] + fConst9 * fRec7[1]) - fConst4 * fRec6[1];
		fRec11[0] = fConst12 * (fConst11 * fRec11[1] + 0.025 * (fRec7[0] - fRec7[1]));
		fRec17[0] = fSlow2 + 0.999 * fRec17[1];
		fRec23[0] = fSlow3 + 0.999 * fRec23[1];
		double fTemp3 = 2.0 * (fRec23[0] + -0.5);
		double fTemp4 = double(buf[i0]);
		double fTemp5 = std::fabs(fTemp4);
		fRec35[0] = 0.9999 * fRec35[1] + 9.999999999998899e-05 * fTemp5;
		double fTemp6 = std::max<double>(fRec35[0], fTemp5);
		fVec1[IOTA0 & 32767] = fTemp6;
		fRec34[0] = fTemp6 + fRec34[1] - fVec1[(IOTA0 - iConst39) & 32767];
		fRec33[0] = 0.999 * fRec33[1] + fConst40 * fRec34[0];
		double fTemp7 = std::max<double>(-1.0, std::min<double>(-0.01, fTemp6 + (-1.0 - 1.02 * fRec33[0])));
		double fTemp8 = 0.0 - 40.1 * fTemp7;
		double fTemp9 = std::max<double>(-6e+02, fTemp8);
		double fTemp10 = fTemp4 - fTemp7;
		double fTemp11 = 40.1 * fTemp10;
		double fTemp12 = std::max<double>(-6e+02, fTemp11);
		double fTemp13 = ((std::fabs(fTemp11) > 0.0001) ? ((fTemp12 < -5e+01) ? 0.0 - fTemp12 * std::exp(fTemp12) : fTemp12 / (1.0 - std::exp(-1.0 * fTemp12))) : fTemp10 * (134.00083333333336 * fTemp10 + 20.05) + 1.0) - ((std::fabs(fTemp8) > 0.0001) ? ((fTemp9 < -5e+01) ? 0.0 - fTemp9 * std::exp(fTemp9) : fTemp9 / (1.0 - std::exp(-1.0 * fTemp9))) : fTemp8 * (0.08333333333333333 * fTemp8 + 0.5) + 1.0);
		fRec36[0] = fSlow4 + 0.999 * fRec36[1];
		double fTemp14 = 0.024937655860349125 * fRec36[0] * fTemp13;
		fRec32[0] = fTemp14 - fConst38 * (fConst37 * fRec32[2] + fConst35 * fRec32[1]);
		double fTemp15 = fRec32[2] + fRec32[0] + 2.0 * fRec32[1];
		fVec2[0] = fTemp15;
		fRec31[0] = fConst38 * (fConst8 * fTemp15 + fConst9 * fVec2[1]) - fConst4 * fRec31[1];
		fRec30[0] = 0.0 - fConst43 * (fConst41 * fRec30[1] - (fRec31[0] + fRec31[1]));
		fRec29[0] = fRec30[0] - fConst33 * (fConst32 * fRec29[2] + fConst30 * fRec29[1]);
		double fTemp16 = fRec29[2] + fRec29[0] + 2.0 * fRec29[1];
		fVec3[0] = fTemp16;
		fRec28[0] = 0.0 - fConst46 * (fConst44 * fRec28[1] - fConst33 * (fTemp16 + fVec3[1]));
		fRec27[0] = fRec28[0] - fConst26 * (fConst25 * fRec27[2] + fConst23 * fRec27[1]);
		double fTemp17 = fRec27[2] + fRec27[0] + 2.0 * fRec27[1];
		fVec4[0] = fTemp17;
		fRec26[0] = 0.0 - fConst49 * (fConst47 * fRec26[1] - fConst26 * (fTemp17 + fVec4[1]));
		fRec25[0] = fRec26[0] - fConst19 * (fConst18 * fRec25[2] + fConst16 * fRec25[1]);
		double fTemp18 = std::max<double>(-1.0, std::min<double>(1.0, fConst19 * (fRec25[2] + fRec25[0] + 2.0 * fRec25[1]) * std::pow(1e+01, 0.9 * fRec23[0])));
		fRec38[0] = fConst26 * (fConst51 * fTemp17 + fConst52 * fVec4[1]) - fConst50 * fRec38[1];
		fRec37[0] = fRec38[0] - fConst19 * (fConst18 * fRec37[2] + fConst16 * fRec37[1]);
		double fTemp19 = std::pow(1e+01, 2.0 * fRec23[0]);
		double fTemp20 = std::max<double>(-1.0, std::min<double>(1.0, fConst19 * fTemp19 * (fConst15 * fRec37[0] + fConst53 * fRec37[1] + fConst15 * fRec37[2])));
		double fTemp21 = fConst16 * fRec39[1];
		double fTemp22 = fConst23 * fRec40[1];
		fRec42[0] = fConst58 * fRec31[1] - fConst43 * (fConst41 * fRec42[1] - fConst31 * fRec31[0]);
		fRec41[0] = fRec42[0] - fConst33 * (fConst32 * fRec41[2] + fConst30 * fRec41[1]);
		fRec40[0] = fConst33 * (fConst29 * fRec41[0] + fConst59 * fRec41[1] + fConst29 * fRec41[2]) - fConst57 * (fConst56 * fRec40[2] + fTemp22);
		fRec39[0] = fRec40[2] + fConst57 * (fTemp22 + fConst56 * fRec40[0]) - fConst55 * (fConst54 * fRec39[2] + fTemp21);
		double fTemp23 = std::max<double>(-1.0, std::min<double>(1.0, (fRec39[2] + fConst55 * (fTemp21 + fConst54 * fRec39[0])) * std::pow(1e+01, 0.8 * fRec23[0])));
		double fTemp24 = fConst16 * fRec43[1];
		fRec45[0] = fConst33 * (fConst61 * fTemp16 + fConst62 * fVec3[1]) - fConst60 * fRec45[1];
		fRec44[0] = fRec45[0] - fConst26 * (fConst25 * fRec44[2] + fConst23 * fRec44[1]);
		fRec43[0] = fConst26 * (fConst22 * fRec44[0] + fConst63 * fRec44[1] + fConst22 * fRec44[2]) - fConst55 * (fConst54 * fRec43[2] + fTemp24);
		double fTemp25 = std::max<double>(-1.0, std::min<double>(1.0, (fRec43[2] + fConst55 * (fTemp24 + fConst54 * fRec43[0])) * std::pow(1e+01, 1.2 * fRec23[0])));
		double fTemp26 = 1.333521432 * fTemp25 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp25)) + 1.584893192 * (fTemp23 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp23)) + fTemp20 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp20))) + 1.2589412 * fTemp18 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp18));
		fVec5[0] = fTemp26;
		fRec24[0] = 0.0 - fConst66 * (fConst65 * fRec24[1] - (fTemp26 + fVec5[1]));
		double fTemp27 = std::max<double>(-1.0, std::min<double>(1.0, fTemp19 * std::max<double>(-0.7, std::min<double>(0.7, fTemp14))));
		double fTemp28 = 1.0 - fRec36[0];
		double fTemp29 = fTemp13 * (fTemp28 * (1.25 * fRec23[0] * (0.0997506234413965 * (1.0 - std::fabs(0.024937655860349125 * fTemp28 * fTemp13)) + -0.024937655860349125) + 0.024937655860349125) + 0.024937655860349125 * fRec36[0] * (1.0 - std::max<double>(0.0, fTemp3))) + 0.5 * fTemp27 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp27)) + fRec24[0] * (1.0 - std::max<double>(0.0, -1.0 * fTemp3));
		fVec6[0] = fTemp29;
		fRec22[0] = 0.9302847925323914 * (fTemp29 + fVec6[1]) - 0.8605695850647829 * fRec22[1];
		fRec21[0] = fRec22[0] - (1.8405051250752198 * fRec21[1] + 0.8612942439318627 * fRec21[2]);
		double fTemp30 = 1.8508996845035413 * fRec21[1];
		double fTemp31 = 0.9254498422517706 * (fRec21[0] + fRec21[2]);
		double fTemp32 = (fTemp30 + fTemp31) / (Ranode(TUBE_TABLE_12AT7_68k, fRec20[1]) + 1e+05);
		fVec7[0] = fTemp32;
		fRec46[0] = fConst69 * (2.7e+03 * (fTemp32 + fVec7[1]) - fConst68 * fRec46[1]);
		fRec20[0] = Ftube(TUBE_TABLE_12AT7_68k, fTemp31 + fRec46[0] + fTemp30 + -2.617753) + -153.04618518518518;
		fRec19[0] = 0.025 * (fConst8 * fRec20[0] + fConst9 * fRec20[1]) - fConst4 * fRec19[1];
		fRec47[0] = fConst12 * (fConst11 * fRec47[1] + 0.025 * (fRec20[0] - fRec20[1]));
		fRec51[0] = 0.9302847925323914 * (fRec18[1] + fRec18[2]) - 0.8605695850647829 * fRec51[1];
		fRec50[0] = fRec51[0] - (1.8405051250752198 * fRec50[1] + 0.8612942439318627 * fRec50[2]);
		double fTemp33 = 1.8508996845035413 * fRec50[1];
		double fTemp34 = 0.9254498422517706 * (fRec50[0] + fRec50[2]);
		double fTemp35 = (fTemp33 + fTemp34) / (Ranode(TUBE_TABLE_12AT7_250k, fRec49[1]) + 1e+05);
		fVec8[0] = fTemp35;
		fRec52[0] = fConst72 * (1.5e+03 * (fTemp35 + fVec8[1]) - fConst71 * fRec52[1]);
		fRec49[0] = Ftube(TUBE_TABLE_12AT7_250k, fTemp34 + fRec52[0] + fTemp33 + -1.887332) + -124.17786666666666;
		fRec48[0] = 0.025 * (fConst8 * fRec49[0] + fConst9 * fRec49[1]) - fConst4 * fRec48[1];
		fRec53[0] = fConst12 * (fConst11 * fRec53[1] + 0.025 * (fRec49[0] - fRec49[1]));
		fRec18[0] = 0.6 * ((iSlow1) ? fRec53[0] : fRec48[0]) - ((iSlow1) ? fRec47[0] : fRec19[0]);
		double fTemp36 = fRec18[0] * fRec17[0];
		fVec9[0] = fTemp36;
		fRec16[0] = 0.0 - fConst66 * (fConst65 * fRec16[1] - (fTemp36 + fVec9[1]));
		fRec15[0] = 0.9302847925323914 * (fRec16[0] + fRec16[1]) - 0.8605695850647829 * fRec15[1];
		fRec14[0] = fRec15[0] - (1.8405051250752198 * fRec14[1] + 0.8612942439318627 * fRec14[2]);
		double fTemp37 = 1.8508996845035413 * fRec14[1];
		double fTemp38 = 0.9254498422517706 * (fRec14[0] + fRec14[2]);
		double fTemp39 = (fTemp37 + fTemp38) / (Ranode(TUBE_TABLE_12AT7_250k, fRec13[1]) + 1e+05);
		fVec10[0] = fTemp39;
		fRec54[0] = fConst72 * (1.5e+03 * (fTemp39 + fVec10[1]) - fConst71 * fRec54[1]);
		fRec13[0] = Ftube(TUBE_TABLE_12AT7_250k, fTemp38 + fRec54[0] + fTemp37 + -1.887332) + -124.17786666666666;
		fRec12[0] = 0.025 * (fConst8 * fRec13[0] + fConst9 * fRec13[1]) - fConst4 * fRec12[1];
		fRec55[0] = fConst12 * (fConst11 * fRec55[1] + 0.025 * (fRec13[0] - fRec13[1]));
		fRec5[0] = ((iSlow1) ? fRec55[0] : fRec12[0]) + 0.6 * ((iSlow1) ? fRec11[0] : fRec6[0]);
		fRec4[0] = 0.0 - fConst66 * (fConst65 * fRec4[1] - (fRec5[0] + fRec5[1]));
		fRec3[0] = 0.9302847925323914 * (fRec4[0] + fRec4[1]) - 0.8605695850647829 * fRec3[1];
		fRec2[0] = fRec3[0] - (1.8405051250752198 * fRec2[1] + 0.8612942439318627 * fRec2[2]);
		double fTemp40 = 1.8508996845035413 * fRec2[1];
		double fTemp41 = 0.9254498422517706 * (fRec2[0] + fRec2[2]);
		double fTemp42 = (fTemp40 + fTemp41) / (Ranode(TUBE_TABLE_12AT7_250k, fRec1[1]) + 1e+05);
		fVec11[0] = fTemp42;
		fRec56[0] = fConst7 * (8.2e+02 * (fTemp42 + fVec11[1]) - fConst6 * fRec56[1]);
		fRec1[0] = Ftube(TUBE_TABLE_12AT7_250k, fTemp41 + fRec56[0] + fTemp40 + -1.256962) + -96.7119512195122;
		fRec0[0] = 0.025 * (fConst8 * fRec1[0] + fConst9 * fRec1[1]) - fConst4 * fRec0[1];
		fRec57[0] = fConst12 * (fConst11 * fRec57[1] + 0.025 * (fRec1[0] - fRec1[1]));
		fRec58[0] = fSlow5 + 0.999 * fRec58[1];
		buf[i0] = FAUSTFLOAT(fRec58[0] * ((iSlow0) ? fRec57[0] : fRec0[0]));
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fVec0[1] = fVec0[0];
		fRec10[1] = fRec10[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec11[1] = fRec11[0];
		fRec17[1] = fRec17[0];
		fRec23[1] = fRec23[0];
		fRec35[1] = fRec35[0];
		IOTA0 = IOTA0 + 1;
		fRec34[1] = fRec34[0];
		fRec33[1] = fRec33[0];
		fRec36[1] = fRec36[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fVec2[1] = fVec2[0];
		fRec31[1] = fRec31[0];
		fRec30[1] = fRec30[0];
		fRec29[2] = fRec29[1];
		fRec29[1] = fRec29[0];
		fVec3[1] = fVec3[0];
		fRec28[1] = fRec28[0];
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		fVec4[1] = fVec4[0];
		fRec26[1] = fRec26[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		fRec38[1] = fRec38[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fRec42[1] = fRec42[0];
		fRec41[2] = fRec41[1];
		fRec41[1] = fRec41[0];
		fRec40[2] = fRec40[1];
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fRec45[1] = fRec45[0];
		fRec44[2] = fRec44[1];
		fRec44[1] = fRec44[0];
		fRec43[2] = fRec43[1];
		fRec43[1] = fRec43[0];
		fVec5[1] = fVec5[0];
		fRec24[1] = fRec24[0];
		fVec6[1] = fVec6[0];
		fRec22[1] = fRec22[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		fVec7[1] = fVec7[0];
		fRec46[1] = fRec46[0];
		fRec20[1] = fRec20[0];
		fRec19[1] = fRec19[0];
		fRec47[1] = fRec47[0];
		fRec51[1] = fRec51[0];
		fRec50[2] = fRec50[1];
		fRec50[1] = fRec50[0];
		fVec8[1] = fVec8[0];
		fRec52[1] = fRec52[0];
		fRec49[1] = fRec49[0];
		fRec48[1] = fRec48[0];
		fRec53[1] = fRec53[0];
		fRec18[2] = fRec18[1];
		fRec18[1] = fRec18[0];
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
	fVslider1_ = reg.registerFloatVar("gxdistortion.drive","","SA","",&fVslider1, 0.35, 0.0, 1.0, 0.01, 0);
	fVslider2_ = reg.registerFloatVar("gxdistortion.wet_dry","","SA","",&fVslider2, 1e+02, 0.0, 1e+02, 1.0, 0);
	fCheckbox1_ = reg.registerFloatVar("amp.highgain","","BA",N_("Allow frequencies below 31Hz"),&fCheckbox1, 0.0, 0.0, 1.0, 1.0, 0);
	fVslider0_ = reg.registerFloatVar("amp2.stage1.Pregain","","SA","",&fVslider0, -6.0, -2e+01, 2e+01, 0.1, 0);
	fCheckbox0_ = reg.registerFloatVar("amp.highgain","","BA",N_("Allow frequencies below 31Hz"),&fCheckbox0, 0.0, 0.0, 1.0, 1.0, 0);
	fVslider3_ = reg.registerFloatVar("amp2.stage2.gain1","","SA","",&fVslider3, -6.0, -2e+01, 2e+01, 0.1, 0);
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

} // end namespace gxamp17
