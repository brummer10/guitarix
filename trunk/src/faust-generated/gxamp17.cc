// generated from file '../src/faust/gxamp17.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxamp17 {

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
	double fRec9[2];
	double fRec8[3];
	double fConst7;
	double fConst8;
	double fVec0[2];
	double fConst9;
	double fRec10[2];
	double fRec7[2];
	double fRec6[2];
	double fRec20[2];
	double fRec19[3];
	double fConst10;
	double fConst11;
	double fVec1[2];
	double fConst12;
	double fRec21[2];
	double fRec18[2];
	double fRec17[2];
	double fRec26[2];
	int IOTA;
	double fVec2[32768];
	double fConst13;
	int iConst14;
	double fRec28[2];
	double fRec27[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec29[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec30[2];
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
	double fRec38[3];
	double fVec3[2];
	double fConst37;
	double fConst38;
	double fRec37[2];
	double fRec36[2];
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fRec35[3];
	double fVec4[2];
	double fConst43;
	double fConst44;
	double fConst45;
	double fRec34[2];
	double fConst46;
	double fConst47;
	double fRec33[3];
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fRec32[3];
	double fConst58;
	double fRec42[2];
	double fRec41[3];
	double fConst59;
	double fConst60;
	double fConst61;
	double fRec40[3];
	double fRec39[3];
	double fConst62;
	double fConst63;
	double fConst64;
	double fRec46[2];
	double fRec45[3];
	double fVec5[2];
	double fConst65;
	double fConst66;
	double fRec44[2];
	double fConst67;
	double fRec43[3];
	double fConst68;
	double fConst69;
	double fRec48[2];
	double fRec47[3];
	double fVec6[2];
	double fRec31[2];
	double fVec7[2];
	double fRec25[2];
	double fRec24[3];
	double fConst70;
	double fConst71;
	double fVec8[2];
	double fConst72;
	double fRec49[2];
	double fRec23[2];
	double fRec22[2];
	double fRec16[3];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec50[2];
	double fVec9[2];
	double fRec15[2];
	double fRec14[2];
	double fRec13[3];
	double fVec10[2];
	double fRec51[2];
	double fRec12[2];
	double fRec11[2];
	double fRec5[3];
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fVec11[2];
	double fRec52[2];
	double fRec1[2];
	double fRec0[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec53[2];

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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec9[l0] = 0.0;
	for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) fRec8[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fVec0[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec10[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec7[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec6[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec20[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRec19[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fVec1[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec21[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec18[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec17[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec26[l12] = 0.0;
	for (int l13 = 0; (l13 < 32768); l13 = (l13 + 1)) fVec2[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec28[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec27[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec29[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec30[l17] = 0.0;
	for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) fRec38[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fVec3[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fRec37[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec36[l21] = 0.0;
	for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) fRec35[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fVec4[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec34[l24] = 0.0;
	for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) fRec33[l25] = 0.0;
	for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) fRec32[l26] = 0.0;
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) fRec42[l27] = 0.0;
	for (int l28 = 0; (l28 < 3); l28 = (l28 + 1)) fRec41[l28] = 0.0;
	for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) fRec40[l29] = 0.0;
	for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) fRec39[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fRec46[l31] = 0.0;
	for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) fRec45[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fVec5[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec44[l34] = 0.0;
	for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) fRec43[l35] = 0.0;
	for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) fRec48[l36] = 0.0;
	for (int l37 = 0; (l37 < 3); l37 = (l37 + 1)) fRec47[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fVec6[l38] = 0.0;
	for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) fRec31[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fVec7[l40] = 0.0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) fRec25[l41] = 0.0;
	for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) fRec24[l42] = 0.0;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fVec8[l43] = 0.0;
	for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) fRec49[l44] = 0.0;
	for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) fRec23[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec22[l46] = 0.0;
	for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) fRec16[l47] = 0.0;
	for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) fRec50[l48] = 0.0;
	for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) fVec9[l49] = 0.0;
	for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) fRec15[l50] = 0.0;
	for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) fRec14[l51] = 0.0;
	for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) fRec13[l52] = 0.0;
	for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) fVec10[l53] = 0.0;
	for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) fRec51[l54] = 0.0;
	for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) fRec12[l55] = 0.0;
	for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) fRec11[l56] = 0.0;
	for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) fRec5[l57] = 0.0;
	for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) fRec4[l58] = 0.0;
	for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) fRec3[l59] = 0.0;
	for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) fRec2[l60] = 0.0;
	for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) fVec11[l61] = 0.0;
	for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) fRec52[l62] = 0.0;
	for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) fRec1[l63] = 0.0;
	for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) fRec0[l64] = 0.0;
	for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) fRec53[l65] = 0.0;
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
	fConst7 = (1.0 / std::tan((609.46897479641984 / fConst0)));
	fConst8 = (1.0 / (fConst7 + 1.0));
	fConst9 = (1.0 - fConst7);
	fConst10 = (1.0 / std::tan((414.69023027385271 / fConst0)));
	fConst11 = (1.0 / (fConst10 + 1.0));
	fConst12 = (1.0 - fConst10);
	fConst13 = (0.009000000000000008 / fConst0);
	iConst14 = int(std::min<double>(65536.0, std::max<double>(0.0, (0.1111111111111111 * fConst0))));
	fConst15 = std::tan((3769.9111843077517 / fConst0));
	fConst16 = (1.0 / fConst15);
	fConst17 = (1.0 / (((fConst16 + 1.0000000000000004) / fConst15) + 1.0));
	fConst18 = mydsp_faustpower2_f(fConst15);
	fConst19 = (1.0 / fConst18);
	fConst20 = std::tan((10053.096491487338 / fConst0));
	fConst21 = (1.0 / fConst20);
	fConst22 = (1.0 / (((fConst21 + 1.0000000000000004) / fConst20) + 1.0));
	fConst23 = (fConst16 + 1.0);
	fConst24 = (1.0 / (fConst15 * fConst23));
	fConst25 = (fConst21 + 1.0);
	fConst26 = (1.0 / fConst25);
	fConst27 = (1.0 - fConst21);
	fConst28 = std::tan((47123.889803846898 / fConst0));
	fConst29 = (1.0 / fConst28);
	fConst30 = (1.0 / (((fConst29 + 1.4142135623730949) / fConst28) + 1.0));
	fConst31 = std::tan((97.389372261283583 / fConst0));
	fConst32 = (1.0 / fConst31);
	fConst33 = (fConst32 + 1.0);
	fConst34 = (1.0 / (fConst31 * fConst33));
	fConst35 = (((fConst29 + -1.4142135623730949) / fConst28) + 1.0);
	fConst36 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst28))));
	fConst37 = (0.0 - fConst34);
	fConst38 = ((1.0 - fConst32) / fConst33);
	fConst39 = (((fConst21 + -1.0000000000000004) / fConst20) + 1.0);
	fConst40 = mydsp_faustpower2_f(fConst20);
	fConst41 = (1.0 / fConst40);
	fConst42 = (2.0 * (1.0 - fConst41));
	fConst43 = (0.0 - fConst24);
	fConst44 = (1.0 - fConst16);
	fConst45 = (fConst44 / fConst23);
	fConst46 = (((fConst16 + -1.0000000000000004) / fConst15) + 1.0);
	fConst47 = (2.0 * (1.0 - fConst19));
	fConst48 = (0.0 - (2.0 / fConst18));
	fConst49 = std::tan((942.47779607693792 / fConst0));
	fConst50 = (1.0 / fConst49);
	fConst51 = (fConst50 + 1.0);
	fConst52 = (1.0 / ((fConst51 / fConst49) + 1.0));
	fConst53 = (1.0 - fConst50);
	fConst54 = (1.0 - (fConst53 / fConst49));
	fConst55 = mydsp_faustpower2_f(fConst49);
	fConst56 = (1.0 / fConst55);
	fConst57 = (2.0 * (1.0 - fConst56));
	fConst58 = (0.0 - (1.0 / (fConst20 * fConst25)));
	fConst59 = (0.0 - (2.0 / fConst40));
	fConst60 = (1.0 / ((fConst23 / fConst15) + 1.0));
	fConst61 = (1.0 - (fConst44 / fConst15));
	fConst62 = (1.0 / (((fConst50 + 1.0000000000000004) / fConst49) + 1.0));
	fConst63 = (1.0 / (fConst49 * fConst51));
	fConst64 = (1.0 / fConst23);
	fConst65 = (0.0 - fConst63);
	fConst66 = (fConst53 / fConst51);
	fConst67 = (((fConst50 + -1.0000000000000004) / fConst49) + 1.0);
	fConst68 = (0.0 - (2.0 / fConst55));
	fConst69 = (1.0 / fConst51);
	fConst70 = (1.0 / std::tan((270.1769682087222 / fConst0)));
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
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double fSlow0 = (1.0000000000000009e-05 * double(fVslider0));
	double fSlow1 = (0.0010000000000000009 * double(fVslider1));
	double fSlow2 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider2))));
	double fSlow3 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider3))));
	for (int i = 0; (i < ReCount); i = (i + 1)) {
		fRec9[0] = ((0.93028479253239138 * (fRec5[1] + fRec5[2])) - (0.86056958506478287 * fRec9[1]));
		fRec8[0] = (fRec9[0] - ((1.8405051250752198 * fRec8[1]) + (0.86129424393186271 * fRec8[2])));
		double fTemp0 = (0.92544984225177063 * (fRec8[0] + fRec8[2]));
		double fTemp1 = (1.8508996845035413 * fRec8[1]);
		double fTemp2 = ((fTemp1 + fTemp0) / (double(Ranode(int(TUBE_TABLE_12AT7_250k), double(fRec7[1]))) + 100000.0));
		fVec0[0] = fTemp2;
		fRec10[0] = (fConst8 * ((820.0 * (fTemp2 + fVec0[1])) - (fConst9 * fRec10[1])));
		double fTemp3 = double(Ftube(int(TUBE_TABLE_12AT7_250k), double(((fTemp0 + (fRec10[0] + fTemp1)) + -1.2569619999999999))));
		fRec7[0] = ((fTemp3 + (0.001532880487804878 * (double(Ranode(int(TUBE_TABLE_12AT7_250k), double(fTemp3))) + 100000.0))) + -250.0);
		fRec6[0] = (fConst2 * ((fConst3 * fRec6[1]) + (0.025000000000000001 * (fRec7[0] - fRec7[1]))));
		fRec20[0] = ((0.93028479253239138 * (fRec16[1] + fRec16[2])) - (0.86056958506478287 * fRec20[1]));
		fRec19[0] = (fRec20[0] - ((1.8405051250752198 * fRec19[1]) + (0.86129424393186271 * fRec19[2])));
		double fTemp4 = (0.92544984225177063 * (fRec19[0] + fRec19[2]));
		double fTemp5 = (1.8508996845035413 * fRec19[1]);
		double fTemp6 = ((fTemp5 + fTemp4) / (double(Ranode(int(TUBE_TABLE_12AT7_250k), double(fRec18[1]))) + 100000.0));
		fVec1[0] = fTemp6;
		fRec21[0] = (fConst11 * ((1500.0 * (fTemp6 + fVec1[1])) - (fConst12 * fRec21[1])));
		double fTemp7 = double(Ftube(int(TUBE_TABLE_12AT7_250k), double(((fTemp4 + (fRec21[0] + fTemp5)) + -1.887332))));
		fRec18[0] = ((fTemp7 + (0.0012582213333333333 * (double(Ranode(int(TUBE_TABLE_12AT7_250k), double(fTemp7))) + 100000.0))) + -250.0);
		fRec17[0] = (fConst2 * ((fConst3 * fRec17[1]) + (0.025000000000000001 * (fRec18[0] - fRec18[1]))));
		double fTemp8 = double(buf[i]);
		double fTemp9 = std::fabs(fTemp8);
		fRec26[0] = ((0.99990000000000001 * fRec26[1]) + (9.9999999999988987e-05 * fTemp9));
		double fTemp10 = std::max<double>(fRec26[0], fTemp9);
		fVec2[(IOTA & 32767)] = fTemp10;
		fRec28[0] = ((fTemp10 + fRec28[1]) - fVec2[((IOTA - iConst14) & 32767)]);
		fRec27[0] = ((0.999 * fRec27[1]) + (fConst13 * fRec28[0]));
		double fTemp11 = std::max<double>(-1.0, std::min<double>(-0.01, (fTemp10 + (-1.0 - (1.02 * fRec27[0])))));
		double fTemp12 = (fTemp8 - fTemp11);
		double fTemp13 = (40.100000000000001 * fTemp12);
		double fTemp14 = std::max<double>(-600.0, fTemp13);
		double fTemp15 = (0.0 - (40.100000000000001 * fTemp11));
		double fTemp16 = std::max<double>(-600.0, fTemp15);
		double fTemp17 = (((std::fabs(fTemp13) > 0.0001) ? ((fTemp14 < -50.0) ? (0.0 - (fTemp14 * std::exp(fTemp14))) : (fTemp14 / (1.0 - std::exp((-1.0 * fTemp14))))) : ((fTemp12 * ((134.00083333333336 * fTemp12) + 20.050000000000001)) + 1.0)) - ((std::fabs(fTemp15) > 0.0001) ? ((fTemp16 < -50.0) ? (0.0 - (fTemp16 * std::exp(fTemp16))) : (fTemp16 / (1.0 - std::exp((-1.0 * fTemp16))))) : ((fTemp15 * ((0.083333333333333329 * fTemp15) + 0.5)) + 1.0)));
		fRec29[0] = (fSlow0 + (0.999 * fRec29[1]));
		double fTemp18 = (1.0 - fRec29[0]);
		fRec30[0] = (fSlow1 + (0.999 * fRec30[1]));
		double fTemp19 = (2.0 * (fRec30[0] + -0.5));
		double fTemp20 = std::pow(10.0, (2.0 * fRec30[0]));
		double fTemp21 = (0.024937655860349125 * (fRec29[0] * fTemp17));
		double fTemp22 = std::max<double>(-1.0, std::min<double>(1.0, (fTemp20 * std::max<double>(-0.69999999999999996, std::min<double>(0.69999999999999996, fTemp21)))));
		fRec38[0] = (fTemp21 - (fConst30 * ((fConst35 * fRec38[2]) + (fConst36 * fRec38[1]))));
		double fTemp23 = (fRec38[2] + (fRec38[0] + (2.0 * fRec38[1])));
		fVec3[0] = fTemp23;
		fRec37[0] = ((fConst30 * ((fConst34 * fTemp23) + (fConst37 * fVec3[1]))) - (fConst38 * fRec37[1]));
		fRec36[0] = (0.0 - (fConst26 * ((fConst27 * fRec36[1]) - (fRec37[0] + fRec37[1]))));
		fRec35[0] = (fRec36[0] - (fConst22 * ((fConst39 * fRec35[2]) + (fConst42 * fRec35[1]))));
		double fTemp24 = (fRec35[2] + (fRec35[0] + (2.0 * fRec35[1])));
		fVec4[0] = fTemp24;
		fRec34[0] = ((fConst22 * ((fConst24 * fTemp24) + (fConst43 * fVec4[1]))) - (fConst45 * fRec34[1]));
		fRec33[0] = (fRec34[0] - (fConst17 * ((fConst46 * fRec33[2]) + (fConst47 * fRec33[1]))));
		double fTemp25 = (fConst57 * fRec32[1]);
		fRec32[0] = ((fConst17 * (((fConst19 * fRec33[0]) + (fConst48 * fRec33[1])) + (fConst19 * fRec33[2]))) - (fConst52 * ((fConst54 * fRec32[2]) + fTemp25)));
		double fTemp26 = std::max<double>(-1.0, std::min<double>(1.0, ((fRec32[2] + (fConst52 * (fTemp25 + (fConst54 * fRec32[0])))) * std::pow(10.0, (1.2 * fRec30[0])))));
		fRec42[0] = ((fConst58 * fRec37[1]) - (fConst26 * ((fConst27 * fRec42[1]) - (fConst21 * fRec37[0]))));
		fRec41[0] = (fRec42[0] - (fConst22 * ((fConst39 * fRec41[2]) + (fConst42 * fRec41[1]))));
		double fTemp27 = (fConst47 * fRec40[1]);
		fRec40[0] = ((fConst22 * (((fConst41 * fRec41[0]) + (fConst59 * fRec41[1])) + (fConst41 * fRec41[2]))) - (fConst60 * ((fConst61 * fRec40[2]) + fTemp27)));
		double fTemp28 = (fConst57 * fRec39[1]);
		fRec39[0] = ((fRec40[2] + (fConst60 * (fTemp27 + (fConst61 * fRec40[0])))) - (fConst52 * ((fConst54 * fRec39[2]) + fTemp28)));
		double fTemp29 = std::max<double>(-1.0, std::min<double>(1.0, ((fRec39[2] + (fConst52 * (fTemp28 + (fConst54 * fRec39[0])))) * std::pow(10.0, (0.80000000000000004 * fRec30[0])))));
		fRec46[0] = (0.0 - (fConst64 * ((fConst44 * fRec46[1]) - (fConst22 * (fTemp24 + fVec4[1])))));
		fRec45[0] = (fRec46[0] - (fConst17 * ((fConst46 * fRec45[2]) + (fConst47 * fRec45[1]))));
		double fTemp30 = (fRec45[2] + (fRec45[0] + (2.0 * fRec45[1])));
		fVec5[0] = fTemp30;
		fRec44[0] = ((fConst17 * ((fConst63 * fTemp30) + (fConst65 * fVec5[1]))) - (fConst66 * fRec44[1]));
		fRec43[0] = (fRec44[0] - (fConst62 * ((fConst67 * fRec43[2]) + (fConst57 * fRec43[1]))));
		double fTemp31 = std::max<double>(-1.0, std::min<double>(1.0, (fConst62 * (fTemp20 * (((fConst56 * fRec43[0]) + (fConst68 * fRec43[1])) + (fConst56 * fRec43[2]))))));
		fRec48[0] = (0.0 - (fConst69 * ((fConst53 * fRec48[1]) - (fConst17 * (fTemp30 + fVec5[1])))));
		fRec47[0] = (fRec48[0] - (fConst62 * ((fConst67 * fRec47[2]) + (fConst57 * fRec47[1]))));
		double fTemp32 = std::max<double>(-1.0, std::min<double>(1.0, (fConst62 * ((fRec47[2] + (fRec47[0] + (2.0 * fRec47[1]))) * std::pow(10.0, (0.90000000000000002 * fRec30[0]))))));
		double fTemp33 = (((1.333521432 * (fTemp26 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp26))))) + (1.584893192 * ((fTemp29 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp29)))) + (fTemp31 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp31))))))) + (1.2589412 * (fTemp32 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp32))))));
		fVec6[0] = fTemp33;
		fRec31[0] = (0.0 - (fConst5 * ((fConst6 * fRec31[1]) - (fTemp33 + fVec6[1]))));
		double fTemp34 = ((fTemp17 * ((fTemp18 * ((1.25 * (fRec30[0] * ((0.099750623441396499 * (1.0 - std::fabs((0.024937655860349125 * (fTemp18 * fTemp17))))) + -0.024937655860349125))) + 0.024937655860349125)) + (0.024937655860349125 * (fRec29[0] * (1.0 - std::max<double>(0.0, fTemp19)))))) + ((0.5 * (fTemp22 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp22))))) + (fRec31[0] * (1.0 - std::max<double>(0.0, (-1.0 * fTemp19))))));
		fVec7[0] = fTemp34;
		fRec25[0] = ((0.93028479253239138 * (fTemp34 + fVec7[1])) - (0.86056958506478287 * fRec25[1]));
		fRec24[0] = (fRec25[0] - ((1.8405051250752198 * fRec24[1]) + (0.86129424393186271 * fRec24[2])));
		double fTemp35 = (0.92544984225177063 * (fRec24[0] + fRec24[2]));
		double fTemp36 = (1.8508996845035413 * fRec24[1]);
		double fTemp37 = ((fTemp36 + fTemp35) / (double(Ranode(int(TUBE_TABLE_12AT7_68k), double(fRec23[1]))) + 100000.0));
		fVec8[0] = fTemp37;
		fRec49[0] = (fConst71 * ((2700.0 * (fTemp37 + fVec8[1])) - (fConst72 * fRec49[1])));
		double fTemp38 = double(Ftube(int(TUBE_TABLE_12AT7_68k), double(((fTemp35 + (fRec49[0] + fTemp36)) + -2.617753))));
		fRec23[0] = ((fTemp38 + (0.00096953814814814819 * (double(Ranode(int(TUBE_TABLE_12AT7_68k), double(fTemp38))) + 100000.0))) + -250.0);
		fRec22[0] = (fConst2 * ((fConst3 * fRec22[1]) + (0.025000000000000001 * (fRec23[0] - fRec23[1]))));
		fRec16[0] = ((0.59999999999999998 * fRec17[0]) - fRec22[0]);
		fRec50[0] = (fSlow2 + (0.999 * fRec50[1]));
		double fTemp39 = (fRec16[0] * fRec50[0]);
		fVec9[0] = fTemp39;
		fRec15[0] = (0.0 - (fConst5 * ((fConst6 * fRec15[1]) - (fTemp39 + fVec9[1]))));
		fRec14[0] = ((0.93028479253239138 * (fRec15[0] + fRec15[1])) - (0.86056958506478287 * fRec14[1]));
		fRec13[0] = (fRec14[0] - ((1.8405051250752198 * fRec13[1]) + (0.86129424393186271 * fRec13[2])));
		double fTemp40 = (0.92544984225177063 * (fRec13[0] + fRec13[2]));
		double fTemp41 = (1.8508996845035413 * fRec13[1]);
		double fTemp42 = ((fTemp41 + fTemp40) / (double(Ranode(int(TUBE_TABLE_12AT7_250k), double(fRec12[1]))) + 100000.0));
		fVec10[0] = fTemp42;
		fRec51[0] = (fConst11 * ((1500.0 * (fTemp42 + fVec10[1])) - (fConst12 * fRec51[1])));
		double fTemp43 = double(Ftube(int(TUBE_TABLE_12AT7_250k), double(((fTemp40 + (fRec51[0] + fTemp41)) + -1.887332))));
		fRec12[0] = ((fTemp43 + (0.0012582213333333333 * (double(Ranode(int(TUBE_TABLE_12AT7_250k), double(fTemp43))) + 100000.0))) + -250.0);
		fRec11[0] = (fConst2 * ((fConst3 * fRec11[1]) + (0.025000000000000001 * (fRec12[0] - fRec12[1]))));
		fRec5[0] = ((0.59999999999999998 * fRec6[0]) + fRec11[0]);
		fRec4[0] = (0.0 - (fConst5 * ((fConst6 * fRec4[1]) - (fRec5[0] + fRec5[1]))));
		fRec3[0] = ((0.93028479253239138 * (fRec4[0] + fRec4[1])) - (0.86056958506478287 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.86129424393186271 * fRec2[2])));
		double fTemp44 = (0.92544984225177063 * (fRec2[0] + fRec2[2]));
		double fTemp45 = (1.8508996845035413 * fRec2[1]);
		double fTemp46 = ((fTemp45 + fTemp44) / (double(Ranode(int(TUBE_TABLE_12AT7_250k), double(fRec1[1]))) + 100000.0));
		fVec11[0] = fTemp46;
		fRec52[0] = (fConst8 * ((820.0 * (fTemp46 + fVec11[1])) - (fConst9 * fRec52[1])));
		double fTemp47 = double(Ftube(int(TUBE_TABLE_12AT7_250k), double(((fTemp44 + (fRec52[0] + fTemp45)) + -1.2569619999999999))));
		fRec1[0] = ((fTemp47 + (0.001532880487804878 * (double(Ranode(int(TUBE_TABLE_12AT7_250k), double(fTemp47))) + 100000.0))) + -250.0);
		fRec0[0] = (fConst2 * ((fConst3 * fRec0[1]) + (0.025000000000000001 * (fRec1[0] - fRec1[1]))));
		fRec53[0] = (fSlow3 + (0.999 * fRec53[1]));
		buf[i] = FAUSTFLOAT((fRec0[0] * fRec53[0]));
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fVec0[1] = fVec0[0];
		fRec10[1] = fRec10[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fVec1[1] = fVec1[0];
		fRec21[1] = fRec21[0];
		fRec18[1] = fRec18[0];
		fRec17[1] = fRec17[0];
		fRec26[1] = fRec26[0];
		IOTA = (IOTA + 1);
		fRec28[1] = fRec28[0];
		fRec27[1] = fRec27[0];
		fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		fVec3[1] = fVec3[0];
		fRec37[1] = fRec37[0];
		fRec36[1] = fRec36[0];
		fRec35[2] = fRec35[1];
		fRec35[1] = fRec35[0];
		fVec4[1] = fVec4[0];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fRec42[1] = fRec42[0];
		fRec41[2] = fRec41[1];
		fRec41[1] = fRec41[0];
		fRec40[2] = fRec40[1];
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fRec46[1] = fRec46[0];
		fRec45[2] = fRec45[1];
		fRec45[1] = fRec45[0];
		fVec5[1] = fVec5[0];
		fRec44[1] = fRec44[0];
		fRec43[2] = fRec43[1];
		fRec43[1] = fRec43[0];
		fRec48[1] = fRec48[0];
		fRec47[2] = fRec47[1];
		fRec47[1] = fRec47[0];
		fVec6[1] = fVec6[0];
		fRec31[1] = fRec31[0];
		fVec7[1] = fVec7[0];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fVec8[1] = fVec8[0];
		fRec49[1] = fRec49[0];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fRec50[1] = fRec50[0];
		fVec9[1] = fVec9[0];
		fRec15[1] = fRec15[0];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fVec10[1] = fVec10[0];
		fRec51[1] = fRec51[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fVec11[1] = fVec11[0];
		fRec52[1] = fRec52[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec53[1] = fRec53[0];
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
	fVslider1_ = reg.registerFloatVar("gxdistortion.drive","","SA","",&fVslider1, 0.34999999999999998, 0.0, 1.0, 0.01, 0);
	fVslider0_ = reg.registerFloatVar("gxdistortion.wet_dry","","SA","",&fVslider0, 100.0, 0.0, 100.0, 1.0, 0);
	fVslider2_ = reg.registerFloatVar("amp2.stage1.Pregain","","SA","",&fVslider2, -6.0, -20.0, 20.0, 0.10000000000000001, 0);
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

} // end namespace gxamp17
