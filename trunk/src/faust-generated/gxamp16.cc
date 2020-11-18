// generated from file '../src/faust/gxamp16.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxamp16 {

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
	double fRec26[2];
	double fRec25[3];
	double fConst24;
	double fConst25;
	double fConst26;
	double fRec27[2];
	double fRec24[3];
	double fRec35[2];
	double fRec34[3];
	double fConst27;
	double fConst28;
	double fConst29;
	double fRec36[2];
	double fRec33[3];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec40[2];
	double fVec0[2];
	double fRec39[2];
	double fRec38[3];
	double fConst30;
	double fConst31;
	double fConst32;
	double fRec41[2];
	double fRec37[3];
	double fRec32[3];
	double fRec31[2];
	double fRec30[2];
	double fRec29[3];
	double fRec42[2];
	double fRec28[3];
	double fRec23[3];
	double fRec22[2];
	double fRec21[3];
	double fRec43[2];
	double fRec20[3];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec44[2];
	double fRec45[2];
	int IOTA;
	double fVec1[32768];
	double fConst33;
	int iConst34;
	double fRec47[2];
	double fRec46[2];
	double fConst35;
	double fConst36;
	double fRec19[3];
	double fVec2[2];
	double fConst37;
	double fConst38;
	double fRec18[2];
	double fRec17[2];
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fRec16[3];
	double fVec3[2];
	double fConst43;
	double fConst44;
	double fConst45;
	double fRec15[2];
	double fConst46;
	double fConst47;
	double fRec14[3];
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
	double fRec13[3];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec48[2];
	double fConst58;
	double fRec52[2];
	double fRec51[3];
	double fConst59;
	double fConst60;
	double fConst61;
	double fRec50[3];
	double fRec49[3];
	double fConst62;
	double fConst63;
	double fConst64;
	double fRec56[2];
	double fRec55[3];
	double fVec4[2];
	double fConst65;
	double fConst66;
	double fRec54[2];
	double fConst67;
	double fRec53[3];
	double fConst68;
	double fConst69;
	double fRec58[2];
	double fRec57[3];
	double fVec5[2];
	double fRec12[2];
	double fVec6[2];
	double fRec11[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec59[2];
	double fVec7[2];
	double fRec10[2];
	double fRec9[3];
	double fRec60[2];
	double fRec8[3];
	double fRec62[2];
	double fRec61[3];
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
	id = "pre 12AT7/ push pull 6V6";
	name = N_("pre 12AT7/ push pull 6V6");
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec26[l0] = 0.0;
	for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) fRec25[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec27[l2] = 0.0;
	for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) fRec24[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec35[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec34[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec36[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRec33[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec40[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fVec0[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec39[l10] = 0.0;
	for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) fRec38[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec41[l12] = 0.0;
	for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) fRec37[l13] = 0.0;
	for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) fRec32[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec31[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec30[l16] = 0.0;
	for (int l17 = 0; (l17 < 3); l17 = (l17 + 1)) fRec29[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec42[l18] = 0.0;
	for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) fRec28[l19] = 0.0;
	for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) fRec23[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec22[l21] = 0.0;
	for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) fRec21[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fRec43[l23] = 0.0;
	for (int l24 = 0; (l24 < 3); l24 = (l24 + 1)) fRec20[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fRec44[l25] = 0.0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fRec45[l26] = 0.0;
	for (int l27 = 0; (l27 < 32768); l27 = (l27 + 1)) fVec1[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec47[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fRec46[l29] = 0.0;
	for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) fRec19[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fVec2[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fRec18[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fRec17[l33] = 0.0;
	for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) fRec16[l34] = 0.0;
	for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) fVec3[l35] = 0.0;
	for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) fRec15[l36] = 0.0;
	for (int l37 = 0; (l37 < 3); l37 = (l37 + 1)) fRec14[l37] = 0.0;
	for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) fRec13[l38] = 0.0;
	for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) fRec48[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fRec52[l40] = 0.0;
	for (int l41 = 0; (l41 < 3); l41 = (l41 + 1)) fRec51[l41] = 0.0;
	for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) fRec50[l42] = 0.0;
	for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) fRec49[l43] = 0.0;
	for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) fRec56[l44] = 0.0;
	for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) fRec55[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fVec4[l46] = 0.0;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) fRec54[l47] = 0.0;
	for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) fRec53[l48] = 0.0;
	for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) fRec58[l49] = 0.0;
	for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) fRec57[l50] = 0.0;
	for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) fVec5[l51] = 0.0;
	for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) fRec12[l52] = 0.0;
	for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) fVec6[l53] = 0.0;
	for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) fRec11[l54] = 0.0;
	for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) fRec59[l55] = 0.0;
	for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) fVec7[l56] = 0.0;
	for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) fRec10[l57] = 0.0;
	for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) fRec9[l58] = 0.0;
	for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) fRec60[l59] = 0.0;
	for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) fRec8[l60] = 0.0;
	for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) fRec62[l61] = 0.0;
	for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) fRec61[l62] = 0.0;
	for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) fRec6[l63] = 0.0;
	for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) fRec4[l64] = 0.0;
	for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) fRec2[l65] = 0.0;
	for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) fRec0[l66] = 0.0;
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
	fConst24 = (1.0 / std::tan((609.46897479641984 / fConst0)));
	fConst25 = (1.0 / (fConst24 + 1.0));
	fConst26 = (1.0 - fConst24);
	fConst27 = (1.0 / std::tan((414.69023027385271 / fConst0)));
	fConst28 = (1.0 / (fConst27 + 1.0));
	fConst29 = (1.0 - fConst27);
	fConst30 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst31 = (1.0 / (fConst30 + 1.0));
	fConst32 = (1.0 - fConst30);
	fConst33 = (0.009000000000000008 / fConst0);
	iConst34 = int(std::min<double>(65536.0, std::max<double>(0.0, (0.1111111111111111 * fConst0))));
	fConst35 = (((fConst18 + -1.4142135623730949) / fConst17) + 1.0);
	fConst36 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst17))));
	fConst37 = (0.0 - fConst23);
	fConst38 = ((1.0 - fConst21) / fConst22);
	fConst39 = (((fConst10 + -1.0000000000000004) / fConst9) + 1.0);
	fConst40 = mydsp_faustpower2_f(fConst9);
	fConst41 = (1.0 / fConst40);
	fConst42 = (2.0 * (1.0 - fConst41));
	fConst43 = (0.0 - fConst13);
	fConst44 = (1.0 - fConst5);
	fConst45 = (fConst44 / fConst12);
	fConst46 = (((fConst5 + -1.0000000000000004) / fConst4) + 1.0);
	fConst47 = (2.0 * (1.0 - fConst8));
	fConst48 = (0.0 - (2.0 / fConst7));
	fConst49 = std::tan((942.47779607693792 / fConst0));
	fConst50 = (1.0 / fConst49);
	fConst51 = (fConst50 + 1.0);
	fConst52 = (1.0 / ((fConst51 / fConst49) + 1.0));
	fConst53 = (1.0 - fConst50);
	fConst54 = (1.0 - (fConst53 / fConst49));
	fConst55 = mydsp_faustpower2_f(fConst49);
	fConst56 = (1.0 / fConst55);
	fConst57 = (2.0 * (1.0 - fConst56));
	fConst58 = (0.0 - (1.0 / (fConst9 * fConst14)));
	fConst59 = (0.0 - (2.0 / fConst40));
	fConst60 = (1.0 / ((fConst12 / fConst4) + 1.0));
	fConst61 = (1.0 - (fConst44 / fConst4));
	fConst62 = (1.0 / (((fConst50 + 1.0000000000000004) / fConst49) + 1.0));
	fConst63 = (1.0 / (fConst49 * fConst51));
	fConst64 = (1.0 / fConst12);
	fConst65 = (0.0 - fConst63);
	fConst66 = (fConst53 / fConst51);
	fConst67 = (((fConst50 + -1.0000000000000004) / fConst49) + 1.0);
	fConst68 = (0.0 - (2.0 / fConst55));
	fConst69 = (1.0 / fConst51);
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
		fRec26[0] = ((0.93028479253239138 * (fRec23[1] + fRec23[2])) - (0.86056958506478287 * fRec26[1]));
		fRec25[0] = (fRec26[0] - ((1.8405051250752198 * fRec25[1]) + (0.86129424393186271 * fRec25[2])));
		fRec27[0] = (fConst25 * ((0.0082000000000000007 * (fRec24[1] + fRec24[2])) - (fConst26 * fRec27[1])));
		fRec24[0] = (double(Ftube(int(TUBE_TABLE_12AT7_250k), double((((0.92544984225177063 * (fRec25[0] + fRec25[2])) + (fRec27[0] + (1.8508996845035413 * fRec25[1]))) + -1.2569619999999999)))) + -96.711951219512201);
		fRec35[0] = ((0.93028479253239138 * (fRec32[1] + fRec32[2])) - (0.86056958506478287 * fRec35[1]));
		fRec34[0] = (fRec35[0] - ((1.8405051250752198 * fRec34[1]) + (0.86129424393186271 * fRec34[2])));
		fRec36[0] = (fConst28 * ((0.014999999999999999 * (fRec33[1] + fRec33[2])) - (fConst29 * fRec36[1])));
		fRec33[0] = (double(Ftube(int(TUBE_TABLE_12AT7_250k), double((((0.92544984225177063 * (fRec34[0] + fRec34[2])) + (fRec36[0] + (1.8508996845035413 * fRec34[1]))) + -1.8873329999999999)))) + -124.17779999999999);
		fRec40[0] = (fSlow0 + (0.999 * fRec40[1]));
		double fTemp0 = (double(buf[i]) * fRec40[0]);
		fVec0[0] = fTemp0;
		fRec39[0] = ((0.93028479253239138 * (fTemp0 + fVec0[1])) - (0.86056958506478287 * fRec39[1]));
		fRec38[0] = (fRec39[0] - ((1.8405051250752198 * fRec38[1]) + (0.86129424393186271 * fRec38[2])));
		fRec41[0] = (fConst31 * ((0.027 * (fRec37[1] + fRec37[2])) - (fConst32 * fRec41[1])));
		fRec37[0] = (double(Ftube(int(TUBE_TABLE_12AT7_68k), double((((0.92544984225177063 * (fRec38[0] + fRec38[2])) + (fRec41[0] + (1.8508996845035413 * fRec38[1]))) + -2.617753)))) + -153.04618518518518);
		fRec32[0] = ((0.014999999999999999 * fRec33[0]) + (0.025000000000000001 * fRec37[0]));
		fRec31[0] = (0.0 - (fConst2 * ((fConst3 * fRec31[1]) - (fRec32[0] + fRec32[1]))));
		fRec30[0] = ((0.93028479253239138 * (fRec31[0] + fRec31[1])) - (0.86056958506478287 * fRec30[1]));
		fRec29[0] = (fRec30[0] - ((1.8405051250752198 * fRec29[1]) + (0.86129424393186271 * fRec29[2])));
		fRec42[0] = (fConst28 * ((0.014999999999999999 * (fRec28[1] + fRec28[2])) - (fConst29 * fRec42[1])));
		fRec28[0] = (double(Ftube(int(TUBE_TABLE_12AT7_250k), double((((0.92544984225177063 * (fRec29[0] + fRec29[2])) + (fRec42[0] + (1.8508996845035413 * fRec29[1]))) + -1.8873329999999999)))) + -124.17779999999999);
		fRec23[0] = ((0.014999999999999999 * fRec24[0]) + (0.025000000000000001 * fRec28[0]));
		fRec22[0] = ((0.93028479253239138 * (fRec23[0] + fRec23[1])) - (0.86056958506478287 * fRec22[1]));
		fRec21[0] = (fRec22[0] - ((1.8405051250752198 * fRec21[1]) + (0.86129424393186271 * fRec21[2])));
		fRec43[0] = (fConst25 * ((0.0082000000000000007 * (fRec20[1] + fRec20[2])) - (fConst26 * fRec43[1])));
		fRec20[0] = (double(Ftube(int(TUBE_TABLE_12AT7_250k), double((((0.92544984225177063 * (fRec21[0] + fRec21[2])) + (fRec43[0] + (1.8508996845035413 * fRec21[1]))) + -1.2569619999999999)))) + -96.711951219512201);
		fRec44[0] = (fSlow1 + (0.999 * fRec44[1]));
		double fTemp1 = (0.025000000000000001 * (fRec20[0] * fRec44[0]));
		double fTemp2 = std::fabs(fTemp1);
		fRec45[0] = ((0.99990000000000001 * fRec45[1]) + (9.9999999999988987e-05 * fTemp2));
		double fTemp3 = std::max<double>(fRec45[0], fTemp2);
		fVec1[(IOTA & 32767)] = fTemp3;
		fRec47[0] = ((fTemp3 + fRec47[1]) - fVec1[((IOTA - iConst34) & 32767)]);
		fRec46[0] = ((0.999 * fRec46[1]) + (fConst33 * fRec47[0]));
		double fTemp4 = std::max<double>(-1.0, std::min<double>(-0.01, (fTemp3 + (-1.0 - (1.02 * fRec46[0])))));
		double fTemp5 = (fTemp1 - fTemp4);
		double fTemp6 = (40.100000000000001 * fTemp5);
		double fTemp7 = std::max<double>(-600.0, fTemp6);
		double fTemp8 = (0.0 - (40.100000000000001 * fTemp4));
		double fTemp9 = std::max<double>(-600.0, fTemp8);
		double fTemp10 = (((std::fabs(fTemp6) > 0.0001) ? ((fTemp7 < -50.0) ? (0.0 - (fTemp7 * std::exp(fTemp7))) : (fTemp7 / (1.0 - std::exp((-1.0 * fTemp7))))) : ((fTemp5 * ((134.00083333333336 * fTemp5) + 20.050000000000001)) + 1.0)) - ((std::fabs(fTemp8) > 0.0001) ? ((fTemp9 < -50.0) ? (0.0 - (fTemp9 * std::exp(fTemp9))) : (fTemp9 / (1.0 - std::exp((-1.0 * fTemp9))))) : ((fTemp8 * ((0.083333333333333329 * fTemp8) + 0.5)) + 1.0)));
		fRec19[0] = ((0.024937655860349125 * fTemp10) - (fConst19 * ((fConst35 * fRec19[2]) + (fConst36 * fRec19[1]))));
		double fTemp11 = (fRec19[2] + (fRec19[0] + (2.0 * fRec19[1])));
		fVec2[0] = fTemp11;
		fRec18[0] = ((fConst19 * ((fConst23 * fTemp11) + (fConst37 * fVec2[1]))) - (fConst38 * fRec18[1]));
		fRec17[0] = (0.0 - (fConst15 * ((fConst16 * fRec17[1]) - (fRec18[0] + fRec18[1]))));
		fRec16[0] = (fRec17[0] - (fConst11 * ((fConst39 * fRec16[2]) + (fConst42 * fRec16[1]))));
		double fTemp12 = (fRec16[2] + (fRec16[0] + (2.0 * fRec16[1])));
		fVec3[0] = fTemp12;
		fRec15[0] = ((fConst11 * ((fConst13 * fTemp12) + (fConst43 * fVec3[1]))) - (fConst45 * fRec15[1]));
		fRec14[0] = (fRec15[0] - (fConst6 * ((fConst46 * fRec14[2]) + (fConst47 * fRec14[1]))));
		double fTemp13 = (fConst57 * fRec13[1]);
		fRec13[0] = ((fConst6 * (((fConst8 * fRec14[0]) + (fConst48 * fRec14[1])) + (fConst8 * fRec14[2]))) - (fConst52 * ((fConst54 * fRec13[2]) + fTemp13)));
		fRec48[0] = (fSlow2 + (0.999 * fRec48[1]));
		double fTemp14 = std::max<double>(-1.0, std::min<double>(1.0, ((fRec13[2] + (fConst52 * (fTemp13 + (fConst54 * fRec13[0])))) * std::pow(10.0, (1.2 * fRec48[0])))));
		fRec52[0] = ((fConst58 * fRec18[1]) - (fConst15 * ((fConst16 * fRec52[1]) - (fConst10 * fRec18[0]))));
		fRec51[0] = (fRec52[0] - (fConst11 * ((fConst39 * fRec51[2]) + (fConst42 * fRec51[1]))));
		double fTemp15 = (fConst47 * fRec50[1]);
		fRec50[0] = ((fConst11 * (((fConst41 * fRec51[0]) + (fConst59 * fRec51[1])) + (fConst41 * fRec51[2]))) - (fConst60 * ((fConst61 * fRec50[2]) + fTemp15)));
		double fTemp16 = (fConst57 * fRec49[1]);
		fRec49[0] = ((fRec50[2] + (fConst60 * (fTemp15 + (fConst61 * fRec50[0])))) - (fConst52 * ((fConst54 * fRec49[2]) + fTemp16)));
		double fTemp17 = std::max<double>(-1.0, std::min<double>(1.0, ((fRec49[2] + (fConst52 * (fTemp16 + (fConst54 * fRec49[0])))) * std::pow(10.0, (0.80000000000000004 * fRec48[0])))));
		fRec56[0] = (0.0 - (fConst64 * ((fConst44 * fRec56[1]) - (fConst11 * (fTemp12 + fVec3[1])))));
		fRec55[0] = (fRec56[0] - (fConst6 * ((fConst46 * fRec55[2]) + (fConst47 * fRec55[1]))));
		double fTemp18 = (fRec55[2] + (fRec55[0] + (2.0 * fRec55[1])));
		fVec4[0] = fTemp18;
		fRec54[0] = ((fConst6 * ((fConst63 * fTemp18) + (fConst65 * fVec4[1]))) - (fConst66 * fRec54[1]));
		fRec53[0] = (fRec54[0] - (fConst62 * ((fConst67 * fRec53[2]) + (fConst57 * fRec53[1]))));
		double fTemp19 = std::max<double>(-1.0, std::min<double>(1.0, (fConst62 * ((((fConst56 * fRec53[0]) + (fConst68 * fRec53[1])) + (fConst56 * fRec53[2])) * std::pow(10.0, (2.0 * fRec48[0]))))));
		fRec58[0] = (0.0 - (fConst69 * ((fConst53 * fRec58[1]) - (fConst6 * (fTemp18 + fVec4[1])))));
		fRec57[0] = (fRec58[0] - (fConst62 * ((fConst67 * fRec57[2]) + (fConst57 * fRec57[1]))));
		double fTemp20 = std::max<double>(-1.0, std::min<double>(1.0, (fConst62 * ((fRec57[2] + (fRec57[0] + (2.0 * fRec57[1]))) * std::pow(10.0, (0.90000000000000002 * fRec48[0]))))));
		double fTemp21 = (((1.333521432 * (fTemp14 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp14))))) + (1.584893192 * ((fTemp17 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp17)))) + (fTemp19 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp19))))))) + (1.2589412 * (fTemp20 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp20))))));
		fVec5[0] = fTemp21;
		fRec12[0] = (0.0 - (fConst2 * ((fConst3 * fRec12[1]) - (fTemp21 + fVec5[1]))));
		double fTemp22 = (2.0 * (fRec48[0] + -0.5));
		double fTemp23 = (fRec20[0] * (1.0 - fRec44[0]));
		double fTemp24 = ((fRec12[0] * (1.0 - std::max<double>(0.0, (-1.0 * fTemp22)))) + ((fTemp23 * ((1.25 * (fRec48[0] * ((0.10000000000000001 * (1.0 - std::fabs((0.025000000000000001 * fTemp23)))) + -0.025000000000000001))) + 0.025000000000000001)) + (0.024937655860349125 * (fTemp10 * (1.0 - std::max<double>(0.0, fTemp22))))));
		fVec6[0] = fTemp24;
		fRec11[0] = (0.0 - (fConst2 * ((fConst3 * fRec11[1]) - (fTemp24 + fVec6[1]))));
		fRec59[0] = (fSlow3 + (0.999 * fRec59[1]));
		double fTemp25 = (fRec11[0] * fRec59[0]);
		fVec7[0] = fTemp25;
		fRec10[0] = ((0.93028479253239138 * (fTemp25 + fVec7[1])) - (0.86056958506478287 * fRec10[1]));
		fRec9[0] = (fRec10[0] - ((1.8405051250752198 * fRec9[1]) + (0.86129424393186271 * fRec9[2])));
		double fTemp26 = (0.92544984225177063 * (fRec9[0] + fRec9[2]));
		fRec60[0] = (fConst2 * ((0.0041000000000000003 * (fRec8[1] + fRec8[2])) - (fConst3 * fRec60[1])));
		double fTemp27 = (1.8508996845035413 * fRec9[1]);
		fRec8[0] = (double(Ftube(int(TUBE_TABLE_6V6_68k), double(((fTemp26 + (fRec60[0] + fTemp27)) + -0.66454100000000005)))) + -87.916829268292673);
		double fTemp28 = std::max<double>(-0.75, (0.025000000000000001 * fRec8[0]));
		fRec62[0] = (fConst2 * ((0.0041000000000000003 * (fRec61[1] + fRec61[2])) - (fConst3 * fRec62[1])));
		fRec61[0] = (double(Ftube(int(TUBE_TABLE_6V6_250k), double(((fTemp26 + (fRec62[0] + fTemp27)) + -0.65976100000000004)))) + -89.08268292682925);
		double fTemp29 = std::min<double>(0.69999999999999996, (0.025000000000000001 * fRec61[0]));
		double fTemp30 = (0.5 * fRec0[1]);
		double fTemp31 = (0.40000000000000002 * fRec2[1]);
		double fTemp32 = (fTemp30 + ((0.29999999999999999 * fRec4[1]) + fTemp31));
		double fTemp33 = ((fTemp28 + ((0.20000000000000001 * fRec6[1]) + fTemp29)) - fTemp32);
		fRec6[0] = fTemp33;
		double fRec7 = (0.0 - (0.20000000000000001 * fTemp33));
		fRec4[0] = (fRec7 + fRec6[1]);
		double fTemp34 = (fTemp29 + fTemp28);
		double fRec5 = (0.29999999999999999 * (fTemp34 - fTemp32));
		fRec2[0] = (fRec5 + fRec4[1]);
		double fRec3 = (0.40000000000000002 * (fTemp34 - (fTemp31 + fTemp30)));
		fRec0[0] = (fRec3 + fRec2[1]);
		double fRec1 = (0.5 * (fTemp34 - fTemp30));
		buf[i] = FAUSTFLOAT((fRec1 + fRec0[1]));
		fRec26[1] = fRec26[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		fRec27[1] = fRec27[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec36[1] = fRec36[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fRec40[1] = fRec40[0];
		fVec0[1] = fVec0[0];
		fRec39[1] = fRec39[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		fRec41[1] = fRec41[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fRec31[1] = fRec31[0];
		fRec30[1] = fRec30[0];
		fRec29[2] = fRec29[1];
		fRec29[1] = fRec29[0];
		fRec42[1] = fRec42[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fRec23[2] = fRec23[1];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		fRec43[1] = fRec43[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fRec44[1] = fRec44[0];
		fRec45[1] = fRec45[0];
		IOTA = (IOTA + 1);
		fRec47[1] = fRec47[0];
		fRec46[1] = fRec46[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fVec2[1] = fVec2[0];
		fRec18[1] = fRec18[0];
		fRec17[1] = fRec17[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fVec3[1] = fVec3[0];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fRec48[1] = fRec48[0];
		fRec52[1] = fRec52[0];
		fRec51[2] = fRec51[1];
		fRec51[1] = fRec51[0];
		fRec50[2] = fRec50[1];
		fRec50[1] = fRec50[0];
		fRec49[2] = fRec49[1];
		fRec49[1] = fRec49[0];
		fRec56[1] = fRec56[0];
		fRec55[2] = fRec55[1];
		fRec55[1] = fRec55[0];
		fVec4[1] = fVec4[0];
		fRec54[1] = fRec54[0];
		fRec53[2] = fRec53[1];
		fRec53[1] = fRec53[0];
		fRec58[1] = fRec58[0];
		fRec57[2] = fRec57[1];
		fRec57[1] = fRec57[0];
		fVec5[1] = fVec5[0];
		fRec12[1] = fRec12[0];
		fVec6[1] = fVec6[0];
		fRec11[1] = fRec11[0];
		fRec59[1] = fRec59[0];
		fVec7[1] = fVec7[0];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec60[1] = fRec60[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec62[1] = fRec62[0];
		fRec61[2] = fRec61[1];
		fRec61[1] = fRec61[0];
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

} // end namespace gxamp16
