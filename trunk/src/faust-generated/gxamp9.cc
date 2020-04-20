// generated from file '../src/faust/gxamp9.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxamp9 {

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
	double fRec9[2];
	double fRec8[3];
	double fConst8;
	double fConst9;
	double fConst10;
	double fRec10[2];
	double fRec7[3];
	double fConst11;
	double fConst12;
	double fRec6[2];
	double fRec20[2];
	double fRec19[3];
	double fConst13;
	double fConst14;
	double fConst15;
	double fRec21[2];
	double fRec18[3];
	double fRec17[2];
	double fRec26[2];
	int IOTA;
	double fVec0[32768];
	double fConst16;
	int iConst17;
	double fRec28[2];
	double fRec27[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec29[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec30[2];
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
	double fRec38[3];
	double fVec1[2];
	double fRec37[2];
	double fRec36[2];
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fRec35[3];
	double fVec2[2];
	double fConst40;
	double fConst41;
	double fConst42;
	double fRec34[2];
	double fConst43;
	double fConst44;
	double fRec33[3];
	double fConst45;
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fRec32[3];
	double fConst55;
	double fRec42[2];
	double fRec41[3];
	double fConst56;
	double fConst57;
	double fConst58;
	double fRec40[3];
	double fRec39[3];
	double fConst59;
	double fConst60;
	double fConst61;
	double fRec46[2];
	double fRec45[3];
	double fVec3[2];
	double fConst62;
	double fConst63;
	double fRec44[2];
	double fConst64;
	double fRec43[3];
	double fConst65;
	double fConst66;
	double fRec48[2];
	double fRec47[3];
	double fVec4[2];
	double fRec31[2];
	double fVec5[2];
	double fRec25[2];
	double fRec24[3];
	double fConst67;
	double fConst68;
	double fConst69;
	double fRec49[2];
	double fRec23[3];
	double fRec22[2];
	double fRec16[3];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec50[2];
	double fVec6[2];
	double fRec15[2];
	double fRec14[2];
	double fRec13[3];
	double fRec51[2];
	double fRec12[3];
	double fRec11[2];
	double fRec5[3];
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fRec52[2];
	double fRec1[3];
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
	id = "12ax7 feedback";
	name = N_("12ax7 feedback");
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
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec10[l2] = 0.0;
	for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) fRec7[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec6[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec20[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec19[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec21[l7] = 0.0;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec18[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec17[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec26[l10] = 0.0;
	for (int l11 = 0; (l11 < 32768); l11 = (l11 + 1)) fVec0[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec28[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec27[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec29[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec30[l15] = 0.0;
	for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) fRec38[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fVec1[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec37[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec36[l19] = 0.0;
	for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) fRec35[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fVec2[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fRec34[l22] = 0.0;
	for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) fRec33[l23] = 0.0;
	for (int l24 = 0; (l24 < 3); l24 = (l24 + 1)) fRec32[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fRec42[l25] = 0.0;
	for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) fRec41[l26] = 0.0;
	for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) fRec40[l27] = 0.0;
	for (int l28 = 0; (l28 < 3); l28 = (l28 + 1)) fRec39[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fRec46[l29] = 0.0;
	for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) fRec45[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fVec3[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fRec44[l32] = 0.0;
	for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) fRec43[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec48[l34] = 0.0;
	for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) fRec47[l35] = 0.0;
	for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) fVec4[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fRec31[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fVec5[l38] = 0.0;
	for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) fRec25[l39] = 0.0;
	for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) fRec24[l40] = 0.0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) fRec49[l41] = 0.0;
	for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) fRec23[l42] = 0.0;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fRec22[l43] = 0.0;
	for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) fRec16[l44] = 0.0;
	for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) fRec50[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fVec6[l46] = 0.0;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) fRec15[l47] = 0.0;
	for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) fRec14[l48] = 0.0;
	for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) fRec13[l49] = 0.0;
	for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) fRec51[l50] = 0.0;
	for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) fRec12[l51] = 0.0;
	for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) fRec11[l52] = 0.0;
	for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) fRec5[l53] = 0.0;
	for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) fRec4[l54] = 0.0;
	for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) fRec3[l55] = 0.0;
	for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) fRec2[l56] = 0.0;
	for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) fRec52[l57] = 0.0;
	for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) fRec1[l58] = 0.0;
	for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) fRec0[l59] = 0.0;
	for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) fRec53[l60] = 0.0;
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
	fConst1 = std::tan((97.389372261283583 / fConst0));
	fConst2 = (1.0 / fConst1);
	fConst3 = (fConst2 + 1.0);
	fConst4 = (1.0 / (fConst1 * fConst3));
	fConst5 = (1.0 / std::tan((20517.741620594938 / fConst0)));
	fConst6 = (1.0 / (fConst5 + 1.0));
	fConst7 = (1.0 - fConst5);
	fConst8 = (1.0 / std::tan((609.46897479641984 / fConst0)));
	fConst9 = (1.0 / (fConst8 + 1.0));
	fConst10 = (1.0 - fConst8);
	fConst11 = (0.0 - fConst4);
	fConst12 = ((1.0 - fConst2) / fConst3);
	fConst13 = (1.0 / std::tan((414.69023027385271 / fConst0)));
	fConst14 = (1.0 / (fConst13 + 1.0));
	fConst15 = (1.0 - fConst13);
	fConst16 = (0.009000000000000008 / fConst0);
	iConst17 = int(std::min<double>(65536.0, std::max<double>(0.0, (0.1111111111111111 * fConst0))));
	fConst18 = std::tan((3769.9111843077517 / fConst0));
	fConst19 = (1.0 / fConst18);
	fConst20 = (1.0 / (((fConst19 + 1.0000000000000004) / fConst18) + 1.0));
	fConst21 = mydsp_faustpower2_f(fConst18);
	fConst22 = (1.0 / fConst21);
	fConst23 = std::tan((10053.096491487338 / fConst0));
	fConst24 = (1.0 / fConst23);
	fConst25 = (1.0 / (((fConst24 + 1.0000000000000004) / fConst23) + 1.0));
	fConst26 = (fConst19 + 1.0);
	fConst27 = (1.0 / (fConst18 * fConst26));
	fConst28 = (fConst24 + 1.0);
	fConst29 = (1.0 / fConst28);
	fConst30 = (1.0 - fConst24);
	fConst31 = std::tan((47123.889803846898 / fConst0));
	fConst32 = (1.0 / fConst31);
	fConst33 = (1.0 / (((fConst32 + 1.4142135623730949) / fConst31) + 1.0));
	fConst34 = (((fConst32 + -1.4142135623730949) / fConst31) + 1.0);
	fConst35 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst31))));
	fConst36 = (((fConst24 + -1.0000000000000004) / fConst23) + 1.0);
	fConst37 = mydsp_faustpower2_f(fConst23);
	fConst38 = (1.0 / fConst37);
	fConst39 = (2.0 * (1.0 - fConst38));
	fConst40 = (0.0 - fConst27);
	fConst41 = (1.0 - fConst19);
	fConst42 = (fConst41 / fConst26);
	fConst43 = (((fConst19 + -1.0000000000000004) / fConst18) + 1.0);
	fConst44 = (2.0 * (1.0 - fConst22));
	fConst45 = (0.0 - (2.0 / fConst21));
	fConst46 = std::tan((942.47779607693792 / fConst0));
	fConst47 = (1.0 / fConst46);
	fConst48 = (fConst47 + 1.0);
	fConst49 = (1.0 / ((fConst48 / fConst46) + 1.0));
	fConst50 = (1.0 - fConst47);
	fConst51 = (1.0 - (fConst50 / fConst46));
	fConst52 = mydsp_faustpower2_f(fConst46);
	fConst53 = (1.0 / fConst52);
	fConst54 = (2.0 * (1.0 - fConst53));
	fConst55 = (0.0 - (1.0 / (fConst23 * fConst28)));
	fConst56 = (0.0 - (2.0 / fConst37));
	fConst57 = (1.0 / ((fConst26 / fConst18) + 1.0));
	fConst58 = (1.0 - (fConst41 / fConst18));
	fConst59 = (1.0 / (((fConst47 + 1.0000000000000004) / fConst46) + 1.0));
	fConst60 = (1.0 / (fConst46 * fConst48));
	fConst61 = (1.0 / fConst26);
	fConst62 = (0.0 - fConst60);
	fConst63 = (fConst50 / fConst48);
	fConst64 = (((fConst47 + -1.0000000000000004) / fConst46) + 1.0);
	fConst65 = (0.0 - (2.0 / fConst52));
	fConst66 = (1.0 / fConst48);
	fConst67 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst68 = (1.0 / (fConst67 + 1.0));
	fConst69 = (1.0 - fConst67);
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
		fRec10[0] = (fConst9 * ((0.0082000000000000007 * (fRec7[1] + fRec7[2])) - (fConst10 * fRec10[1])));
		fRec7[0] = (double(Ftube(int(TUBE_TABLE_12AX7_250k), double((((0.92544984225177063 * (fRec8[0] + fRec8[2])) + (fRec10[0] + (1.8508996845035413 * fRec8[1]))) + -0.84070199999999995)))) + -147.47536585365856);
		fRec6[0] = ((0.025000000000000001 * ((fConst4 * fRec7[0]) + (fConst11 * fRec7[1]))) - (fConst12 * fRec6[1]));
		fRec20[0] = ((0.93028479253239138 * (fRec16[1] + fRec16[2])) - (0.86056958506478287 * fRec20[1]));
		fRec19[0] = (fRec20[0] - ((1.8405051250752198 * fRec19[1]) + (0.86129424393186271 * fRec19[2])));
		fRec21[0] = (fConst14 * ((0.014999999999999999 * (fRec18[1] + fRec18[2])) - (fConst15 * fRec21[1])));
		fRec18[0] = (double(Ftube(int(TUBE_TABLE_12AX7_250k), double((((0.92544984225177063 * (fRec19[0] + fRec19[2])) + (fRec21[0] + (1.8508996845035413 * fRec19[1]))) + -1.204285)))) + -169.71433333333334);
		fRec17[0] = ((0.025000000000000001 * ((fConst4 * fRec18[0]) + (fConst11 * fRec18[1]))) - (fConst12 * fRec17[1]));
		double fTemp0 = double(buf[i]);
		double fTemp1 = std::fabs(fTemp0);
		fRec26[0] = ((0.99990000000000001 * fRec26[1]) + (9.9999999999988987e-05 * fTemp1));
		double fTemp2 = std::max<double>(fRec26[0], fTemp1);
		fVec0[(IOTA & 32767)] = fTemp2;
		fRec28[0] = ((fTemp2 + fRec28[1]) - fVec0[((IOTA - iConst17) & 32767)]);
		fRec27[0] = ((0.999 * fRec27[1]) + (fConst16 * fRec28[0]));
		double fTemp3 = std::max<double>(-1.0, std::min<double>(-0.01, (fTemp2 + (-1.0 - (1.02 * fRec27[0])))));
		double fTemp4 = (fTemp0 - fTemp3);
		double fTemp5 = (40.100000000000001 * fTemp4);
		double fTemp6 = std::max<double>(-600.0, fTemp5);
		double fTemp7 = (0.0 - (40.100000000000001 * fTemp3));
		double fTemp8 = std::max<double>(-600.0, fTemp7);
		double fTemp9 = (((std::fabs(fTemp5) > 0.0001) ? ((fTemp6 < -50.0) ? (0.0 - (fTemp6 * std::exp(fTemp6))) : (fTemp6 / (1.0 - std::exp((-1.0 * fTemp6))))) : ((fTemp4 * ((134.00083333333336 * fTemp4) + 20.050000000000001)) + 1.0)) - ((std::fabs(fTemp7) > 0.0001) ? ((fTemp8 < -50.0) ? (0.0 - (fTemp8 * std::exp(fTemp8))) : (fTemp8 / (1.0 - std::exp((-1.0 * fTemp8))))) : ((fTemp7 * ((0.083333333333333329 * fTemp7) + 0.5)) + 1.0)));
		fRec29[0] = (fSlow0 + (0.999 * fRec29[1]));
		double fTemp10 = (1.0 - fRec29[0]);
		fRec30[0] = (fSlow1 + (0.999 * fRec30[1]));
		double fTemp11 = (2.0 * (fRec30[0] + -0.5));
		double fTemp12 = std::pow(10.0, (2.0 * fRec30[0]));
		double fTemp13 = (0.024937655860349125 * (fRec29[0] * fTemp9));
		double fTemp14 = std::max<double>(-1.0, std::min<double>(1.0, (fTemp12 * std::max<double>(-0.69999999999999996, std::min<double>(0.69999999999999996, fTemp13)))));
		fRec38[0] = (fTemp13 - (fConst33 * ((fConst34 * fRec38[2]) + (fConst35 * fRec38[1]))));
		double fTemp15 = (fRec38[2] + (fRec38[0] + (2.0 * fRec38[1])));
		fVec1[0] = fTemp15;
		fRec37[0] = ((fConst33 * ((fConst4 * fTemp15) + (fConst11 * fVec1[1]))) - (fConst12 * fRec37[1]));
		fRec36[0] = (0.0 - (fConst29 * ((fConst30 * fRec36[1]) - (fRec37[0] + fRec37[1]))));
		fRec35[0] = (fRec36[0] - (fConst25 * ((fConst36 * fRec35[2]) + (fConst39 * fRec35[1]))));
		double fTemp16 = (fRec35[2] + (fRec35[0] + (2.0 * fRec35[1])));
		fVec2[0] = fTemp16;
		fRec34[0] = ((fConst25 * ((fConst27 * fTemp16) + (fConst40 * fVec2[1]))) - (fConst42 * fRec34[1]));
		fRec33[0] = (fRec34[0] - (fConst20 * ((fConst43 * fRec33[2]) + (fConst44 * fRec33[1]))));
		double fTemp17 = (fConst54 * fRec32[1]);
		fRec32[0] = ((fConst20 * (((fConst22 * fRec33[0]) + (fConst45 * fRec33[1])) + (fConst22 * fRec33[2]))) - (fConst49 * ((fConst51 * fRec32[2]) + fTemp17)));
		double fTemp18 = std::max<double>(-1.0, std::min<double>(1.0, ((fRec32[2] + (fConst49 * (fTemp17 + (fConst51 * fRec32[0])))) * std::pow(10.0, (1.2 * fRec30[0])))));
		fRec42[0] = ((fConst55 * fRec37[1]) - (fConst29 * ((fConst30 * fRec42[1]) - (fConst24 * fRec37[0]))));
		fRec41[0] = (fRec42[0] - (fConst25 * ((fConst36 * fRec41[2]) + (fConst39 * fRec41[1]))));
		double fTemp19 = (fConst44 * fRec40[1]);
		fRec40[0] = ((fConst25 * (((fConst38 * fRec41[0]) + (fConst56 * fRec41[1])) + (fConst38 * fRec41[2]))) - (fConst57 * ((fConst58 * fRec40[2]) + fTemp19)));
		double fTemp20 = (fConst54 * fRec39[1]);
		fRec39[0] = ((fRec40[2] + (fConst57 * (fTemp19 + (fConst58 * fRec40[0])))) - (fConst49 * ((fConst51 * fRec39[2]) + fTemp20)));
		double fTemp21 = std::max<double>(-1.0, std::min<double>(1.0, ((fRec39[2] + (fConst49 * (fTemp20 + (fConst51 * fRec39[0])))) * std::pow(10.0, (0.80000000000000004 * fRec30[0])))));
		fRec46[0] = (0.0 - (fConst61 * ((fConst41 * fRec46[1]) - (fConst25 * (fTemp16 + fVec2[1])))));
		fRec45[0] = (fRec46[0] - (fConst20 * ((fConst43 * fRec45[2]) + (fConst44 * fRec45[1]))));
		double fTemp22 = (fRec45[2] + (fRec45[0] + (2.0 * fRec45[1])));
		fVec3[0] = fTemp22;
		fRec44[0] = ((fConst20 * ((fConst60 * fTemp22) + (fConst62 * fVec3[1]))) - (fConst63 * fRec44[1]));
		fRec43[0] = (fRec44[0] - (fConst59 * ((fConst64 * fRec43[2]) + (fConst54 * fRec43[1]))));
		double fTemp23 = std::max<double>(-1.0, std::min<double>(1.0, (fConst59 * (fTemp12 * (((fConst53 * fRec43[0]) + (fConst65 * fRec43[1])) + (fConst53 * fRec43[2]))))));
		fRec48[0] = (0.0 - (fConst66 * ((fConst50 * fRec48[1]) - (fConst20 * (fTemp22 + fVec3[1])))));
		fRec47[0] = (fRec48[0] - (fConst59 * ((fConst64 * fRec47[2]) + (fConst54 * fRec47[1]))));
		double fTemp24 = std::max<double>(-1.0, std::min<double>(1.0, (fConst59 * ((fRec47[2] + (fRec47[0] + (2.0 * fRec47[1]))) * std::pow(10.0, (0.90000000000000002 * fRec30[0]))))));
		double fTemp25 = (((1.333521432 * (fTemp18 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp18))))) + (1.584893192 * ((fTemp21 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp21)))) + (fTemp23 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp23))))))) + (1.2589412 * (fTemp24 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp24))))));
		fVec4[0] = fTemp25;
		fRec31[0] = (0.0 - (fConst6 * ((fConst7 * fRec31[1]) - (fTemp25 + fVec4[1]))));
		double fTemp26 = ((fTemp9 * ((fTemp10 * ((1.25 * (fRec30[0] * ((0.099750623441396499 * (1.0 - std::fabs((0.024937655860349125 * (fTemp10 * fTemp9))))) + -0.024937655860349125))) + 0.024937655860349125)) + (0.024937655860349125 * (fRec29[0] * (1.0 - std::max<double>(0.0, fTemp11)))))) + ((0.5 * (fTemp14 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp14))))) + (fRec31[0] * (1.0 - std::max<double>(0.0, (-1.0 * fTemp11))))));
		fVec5[0] = fTemp26;
		fRec25[0] = ((0.93028479253239138 * (fTemp26 + fVec5[1])) - (0.86056958506478287 * fRec25[1]));
		fRec24[0] = (fRec25[0] - ((1.8405051250752198 * fRec24[1]) + (0.86129424393186271 * fRec24[2])));
		fRec49[0] = (fConst68 * ((0.027 * (fRec23[1] + fRec23[2])) - (fConst69 * fRec49[1])));
		fRec23[0] = (double(Ftube(int(TUBE_TABLE_12AX7_68k), double((((0.92544984225177063 * (fRec24[0] + fRec24[2])) + (fRec49[0] + (1.8508996845035413 * fRec24[1]))) + -1.581656)))) + -191.42014814814814);
		fRec22[0] = ((0.025000000000000001 * ((fConst4 * fRec23[0]) + (fConst11 * fRec23[1]))) - (fConst12 * fRec22[1]));
		fRec16[0] = ((0.59999999999999998 * fRec17[0]) - fRec22[0]);
		fRec50[0] = (fSlow2 + (0.999 * fRec50[1]));
		double fTemp27 = (fRec16[0] * fRec50[0]);
		fVec6[0] = fTemp27;
		fRec15[0] = (0.0 - (fConst6 * ((fConst7 * fRec15[1]) - (fTemp27 + fVec6[1]))));
		fRec14[0] = ((0.93028479253239138 * (fRec15[0] + fRec15[1])) - (0.86056958506478287 * fRec14[1]));
		fRec13[0] = (fRec14[0] - ((1.8405051250752198 * fRec13[1]) + (0.86129424393186271 * fRec13[2])));
		fRec51[0] = (fConst14 * ((0.014999999999999999 * (fRec12[1] + fRec12[2])) - (fConst15 * fRec51[1])));
		fRec12[0] = (double(Ftube(int(TUBE_TABLE_12AX7_250k), double((((0.92544984225177063 * (fRec13[0] + fRec13[2])) + (fRec51[0] + (1.8508996845035413 * fRec13[1]))) + -1.204285)))) + -169.71433333333334);
		fRec11[0] = ((0.025000000000000001 * ((fConst4 * fRec12[0]) + (fConst11 * fRec12[1]))) - (fConst12 * fRec11[1]));
		fRec5[0] = ((0.59999999999999998 * fRec6[0]) + fRec11[0]);
		fRec4[0] = (0.0 - (fConst6 * ((fConst7 * fRec4[1]) - (fRec5[0] + fRec5[1]))));
		fRec3[0] = ((0.93028479253239138 * (fRec4[0] + fRec4[1])) - (0.86056958506478287 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.86129424393186271 * fRec2[2])));
		fRec52[0] = (fConst9 * ((0.0082000000000000007 * (fRec1[1] + fRec1[2])) - (fConst10 * fRec52[1])));
		fRec1[0] = (double(Ftube(int(TUBE_TABLE_12AX7_250k), double((((0.92544984225177063 * (fRec2[0] + fRec2[2])) + (fRec52[0] + (1.8508996845035413 * fRec2[1]))) + -0.84070199999999995)))) + -147.47536585365856);
		fRec0[0] = ((0.025000000000000001 * ((fConst4 * fRec1[0]) + (fConst11 * fRec1[1]))) - (fConst12 * fRec0[1]));
		fRec53[0] = (fSlow3 + (0.999 * fRec53[1]));
		buf[i] = FAUSTFLOAT((fRec0[0] * fRec53[0]));
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec10[1] = fRec10[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fRec21[1] = fRec21[0];
		fRec18[2] = fRec18[1];
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
		fVec1[1] = fVec1[0];
		fRec37[1] = fRec37[0];
		fRec36[1] = fRec36[0];
		fRec35[2] = fRec35[1];
		fRec35[1] = fRec35[0];
		fVec2[1] = fVec2[0];
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
		fVec3[1] = fVec3[0];
		fRec44[1] = fRec44[0];
		fRec43[2] = fRec43[1];
		fRec43[1] = fRec43[0];
		fRec48[1] = fRec48[0];
		fRec47[2] = fRec47[1];
		fRec47[1] = fRec47[0];
		fVec4[1] = fVec4[0];
		fRec31[1] = fRec31[0];
		fVec5[1] = fVec5[0];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fRec49[1] = fRec49[0];
		fRec23[2] = fRec23[1];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fRec50[1] = fRec50[0];
		fVec6[1] = fVec6[0];
		fRec15[1] = fRec15[0];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fRec51[1] = fRec51[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec52[1] = fRec52[0];
		fRec1[2] = fRec1[1];
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

} // end namespace gxamp9
