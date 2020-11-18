// generated from file '../src/faust/gxamp18.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxamp18 {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int sample_rate;
	int fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec4[2];
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
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec20[2];
	double fConst24;
	double fConst25;
	double fRec19[3];
	double fVec0[2];
	double fConst26;
	double fConst27;
	double fRec18[2];
	double fRec17[2];
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fRec16[3];
	double fVec1[2];
	double fConst32;
	double fConst33;
	double fConst34;
	double fRec15[2];
	double fConst35;
	double fConst36;
	double fRec14[3];
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
	double fRec13[3];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec21[2];
	double fConst47;
	double fRec25[2];
	double fRec24[3];
	double fConst48;
	double fConst49;
	double fConst50;
	double fRec23[3];
	double fRec22[3];
	double fConst51;
	double fConst52;
	double fConst53;
	double fRec29[2];
	double fRec28[3];
	double fVec2[2];
	double fConst54;
	double fConst55;
	double fRec27[2];
	double fConst56;
	double fRec26[3];
	double fConst57;
	double fConst58;
	double fRec31[2];
	double fRec30[3];
	double fVec3[2];
	double fRec12[2];
	double fVec4[2];
	double fRec11[2];
	double fRec10[3];
	double fConst59;
	double fConst60;
	double fConst61;
	double fRec32[2];
	double fRec9[3];
	double fVec5[2];
	double fRec8[2];
	double fRec7[2];
	double fRec6[3];
	double fConst62;
	double fConst63;
	double fConst64;
	double fRec33[2];
	double fRec5[3];
	double fVec6[2];
	double fRec3[2];
	double fRec2[2];
	double fRec1[3];
	double fConst65;
	double fConst66;
	double fConst67;
	double fRec34[2];
	double fRec0[3];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec35[2];

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
	id = "6C16";
	name = N_("6C16");
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec4[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec20[l1] = 0.0;
	for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) fRec19[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fVec0[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec18[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec17[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec16[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fVec1[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec15[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec14[l9] = 0.0;
	for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) fRec13[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec21[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec25[l12] = 0.0;
	for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) fRec24[l13] = 0.0;
	for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) fRec23[l14] = 0.0;
	for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) fRec22[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec29[l16] = 0.0;
	for (int l17 = 0; (l17 < 3); l17 = (l17 + 1)) fRec28[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fVec2[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec27[l19] = 0.0;
	for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) fRec26[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec31[l21] = 0.0;
	for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) fRec30[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fVec3[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec12[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fVec4[l25] = 0.0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fRec11[l26] = 0.0;
	for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) fRec10[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec32[l28] = 0.0;
	for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) fRec9[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fVec5[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fRec8[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fRec7[l32] = 0.0;
	for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) fRec6[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec33[l34] = 0.0;
	for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) fRec5[l35] = 0.0;
	for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) fVec6[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fRec3[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fRec2[l38] = 0.0;
	for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) fRec1[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fRec34[l40] = 0.0;
	for (int l41 = 0; (l41 < 3); l41 = (l41 + 1)) fRec0[l41] = 0.0;
	for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) fRec35[l42] = 0.0;
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
	fConst24 = (((fConst18 + -1.4142135623730949) / fConst17) + 1.0);
	fConst25 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst17))));
	fConst26 = (0.0 - fConst23);
	fConst27 = ((1.0 - fConst21) / fConst22);
	fConst28 = (((fConst10 + -1.0000000000000004) / fConst9) + 1.0);
	fConst29 = mydsp_faustpower2_f(fConst9);
	fConst30 = (1.0 / fConst29);
	fConst31 = (2.0 * (1.0 - fConst30));
	fConst32 = (0.0 - fConst13);
	fConst33 = (1.0 - fConst5);
	fConst34 = (fConst33 / fConst12);
	fConst35 = (((fConst5 + -1.0000000000000004) / fConst4) + 1.0);
	fConst36 = (2.0 * (1.0 - fConst8));
	fConst37 = (0.0 - (2.0 / fConst7));
	fConst38 = std::tan((942.47779607693792 / fConst0));
	fConst39 = (1.0 / fConst38);
	fConst40 = (fConst39 + 1.0);
	fConst41 = (1.0 / ((fConst40 / fConst38) + 1.0));
	fConst42 = (1.0 - fConst39);
	fConst43 = (1.0 - (fConst42 / fConst38));
	fConst44 = mydsp_faustpower2_f(fConst38);
	fConst45 = (1.0 / fConst44);
	fConst46 = (2.0 * (1.0 - fConst45));
	fConst47 = (0.0 - (1.0 / (fConst9 * fConst14)));
	fConst48 = (0.0 - (2.0 / fConst29));
	fConst49 = (1.0 / ((fConst12 / fConst4) + 1.0));
	fConst50 = (1.0 - (fConst33 / fConst4));
	fConst51 = (1.0 / (((fConst39 + 1.0000000000000004) / fConst38) + 1.0));
	fConst52 = (1.0 / (fConst38 * fConst40));
	fConst53 = (1.0 / fConst12);
	fConst54 = (0.0 - fConst52);
	fConst55 = (fConst42 / fConst40);
	fConst56 = (((fConst39 + -1.0000000000000004) / fConst38) + 1.0);
	fConst57 = (0.0 - (2.0 / fConst44));
	fConst58 = (1.0 / fConst40);
	fConst59 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst60 = (1.0 / (fConst59 + 1.0));
	fConst61 = (1.0 - fConst59);
	fConst62 = (1.0 / std::tan((414.69023027385271 / fConst0)));
	fConst63 = (1.0 / (fConst62 + 1.0));
	fConst64 = (1.0 - fConst62);
	fConst65 = (1.0 / std::tan((609.46897479641984 / fConst0)));
	fConst66 = (1.0 / (fConst65 + 1.0));
	fConst67 = (1.0 - fConst65);
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
		fRec4[0] = (fSlow0 + (0.999 * fRec4[1]));
		double fTemp0 = double(buf[i]);
		fRec20[0] = (fSlow1 + (0.999 * fRec20[1]));
		fRec19[0] = ((fTemp0 * fRec20[0]) - (fConst19 * ((fConst24 * fRec19[2]) + (fConst25 * fRec19[1]))));
		double fTemp1 = (fRec19[2] + (fRec19[0] + (2.0 * fRec19[1])));
		fVec0[0] = fTemp1;
		fRec18[0] = ((fConst19 * ((fConst23 * fTemp1) + (fConst26 * fVec0[1]))) - (fConst27 * fRec18[1]));
		fRec17[0] = (0.0 - (fConst15 * ((fConst16 * fRec17[1]) - (fRec18[0] + fRec18[1]))));
		fRec16[0] = (fRec17[0] - (fConst11 * ((fConst28 * fRec16[2]) + (fConst31 * fRec16[1]))));
		double fTemp2 = (fRec16[2] + (fRec16[0] + (2.0 * fRec16[1])));
		fVec1[0] = fTemp2;
		fRec15[0] = ((fConst11 * ((fConst13 * fTemp2) + (fConst32 * fVec1[1]))) - (fConst34 * fRec15[1]));
		fRec14[0] = (fRec15[0] - (fConst6 * ((fConst35 * fRec14[2]) + (fConst36 * fRec14[1]))));
		double fTemp3 = (fConst46 * fRec13[1]);
		fRec13[0] = ((fConst6 * (((fConst8 * fRec14[0]) + (fConst37 * fRec14[1])) + (fConst8 * fRec14[2]))) - (fConst41 * ((fConst43 * fRec13[2]) + fTemp3)));
		fRec21[0] = (fSlow2 + (0.999 * fRec21[1]));
		double fTemp4 = std::max<double>(-1.0, std::min<double>(1.0, ((fRec13[2] + (fConst41 * (fTemp3 + (fConst43 * fRec13[0])))) * std::pow(10.0, (1.2 * fRec21[0])))));
		fRec25[0] = ((fConst47 * fRec18[1]) - (fConst15 * ((fConst16 * fRec25[1]) - (fConst10 * fRec18[0]))));
		fRec24[0] = (fRec25[0] - (fConst11 * ((fConst28 * fRec24[2]) + (fConst31 * fRec24[1]))));
		double fTemp5 = (fConst36 * fRec23[1]);
		fRec23[0] = ((fConst11 * (((fConst30 * fRec24[0]) + (fConst48 * fRec24[1])) + (fConst30 * fRec24[2]))) - (fConst49 * ((fConst50 * fRec23[2]) + fTemp5)));
		double fTemp6 = (fConst46 * fRec22[1]);
		fRec22[0] = ((fRec23[2] + (fConst49 * (fTemp5 + (fConst50 * fRec23[0])))) - (fConst41 * ((fConst43 * fRec22[2]) + fTemp6)));
		double fTemp7 = std::max<double>(-1.0, std::min<double>(1.0, ((fRec22[2] + (fConst41 * (fTemp6 + (fConst43 * fRec22[0])))) * std::pow(10.0, (0.80000000000000004 * fRec21[0])))));
		fRec29[0] = (0.0 - (fConst53 * ((fConst33 * fRec29[1]) - (fConst11 * (fTemp2 + fVec1[1])))));
		fRec28[0] = (fRec29[0] - (fConst6 * ((fConst35 * fRec28[2]) + (fConst36 * fRec28[1]))));
		double fTemp8 = (fRec28[2] + (fRec28[0] + (2.0 * fRec28[1])));
		fVec2[0] = fTemp8;
		fRec27[0] = ((fConst6 * ((fConst52 * fTemp8) + (fConst54 * fVec2[1]))) - (fConst55 * fRec27[1]));
		fRec26[0] = (fRec27[0] - (fConst51 * ((fConst56 * fRec26[2]) + (fConst46 * fRec26[1]))));
		double fTemp9 = std::max<double>(-1.0, std::min<double>(1.0, (fConst51 * ((((fConst45 * fRec26[0]) + (fConst57 * fRec26[1])) + (fConst45 * fRec26[2])) * std::pow(10.0, (2.0 * fRec21[0]))))));
		fRec31[0] = (0.0 - (fConst58 * ((fConst42 * fRec31[1]) - (fConst6 * (fTemp8 + fVec2[1])))));
		fRec30[0] = (fRec31[0] - (fConst51 * ((fConst56 * fRec30[2]) + (fConst46 * fRec30[1]))));
		double fTemp10 = std::max<double>(-1.0, std::min<double>(1.0, (fConst51 * ((fRec30[2] + (fRec30[0] + (2.0 * fRec30[1]))) * std::pow(10.0, (0.90000000000000002 * fRec21[0]))))));
		double fTemp11 = (((1.333521432 * (fTemp4 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp4))))) + (1.584893192 * ((fTemp7 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp7)))) + (fTemp9 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp9))))))) + (1.2589412 * (fTemp10 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp10))))));
		fVec3[0] = fTemp11;
		fRec12[0] = (0.0 - (fConst2 * ((fConst3 * fRec12[1]) - (fTemp11 + fVec3[1]))));
		double fTemp12 = (2.0 * (fRec21[0] + -0.5));
		double fTemp13 = (1.0 - fRec20[0]);
		double fTemp14 = ((fRec12[0] * (1.0 - std::max<double>(0.0, (-1.0 * fTemp12)))) + (fTemp0 * ((fTemp13 * ((1.25 * (fRec21[0] * ((4.0 * (1.0 - std::fabs((fTemp0 * fTemp13)))) + -1.0))) + 1.0)) + (fRec20[0] * (1.0 - std::max<double>(0.0, fTemp12))))));
		fVec4[0] = fTemp14;
		fRec11[0] = ((0.93028479253239138 * (fTemp14 + fVec4[1])) - (0.86056958506478287 * fRec11[1]));
		fRec10[0] = (fRec11[0] - ((1.8405051250752198 * fRec10[1]) + (0.86129424393186271 * fRec10[2])));
		fRec32[0] = (fConst60 * ((0.027 * (fRec9[1] + fRec9[2])) - (fConst61 * fRec32[1])));
		fRec9[0] = (double(Ftube(int(TUBE_TABLE_6C16_68k), double((((0.92544984225177063 * (fRec10[0] + fRec10[2])) + (fRec32[0] + (1.8508996845035413 * fRec10[1]))) + -2.9218060000000001)))) + -141.78496296296294);
		double fTemp15 = (fRec9[0] * fRec4[0]);
		fVec5[0] = fTemp15;
		fRec8[0] = (fConst2 * ((0.025000000000000001 * (fTemp15 + fVec5[1])) - (fConst3 * fRec8[1])));
		fRec7[0] = ((0.93028479253239138 * (fRec8[0] + fRec8[1])) - (0.86056958506478287 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.86129424393186271 * fRec6[2])));
		fRec33[0] = (fConst63 * ((0.014999999999999999 * (fRec5[1] + fRec5[2])) - (fConst64 * fRec33[1])));
		fRec5[0] = (double(Ftube(int(TUBE_TABLE_6C16_250k), double((((0.92544984225177063 * (fRec6[0] + fRec6[2])) + (fRec33[0] + (1.8508996845035413 * fRec6[1]))) + -2.0977429999999999)))) + -110.15046666666666);
		double fTemp16 = (fRec4[0] * fRec5[0]);
		fVec6[0] = fTemp16;
		fRec3[0] = (fConst2 * ((0.025000000000000001 * (fTemp16 + fVec6[1])) - (fConst3 * fRec3[1])));
		fRec2[0] = ((0.93028479253239138 * (fRec3[0] + fRec3[1])) - (0.86056958506478287 * fRec2[1]));
		fRec1[0] = (fRec2[0] - ((1.8405051250752198 * fRec1[1]) + (0.86129424393186271 * fRec1[2])));
		fRec34[0] = (fConst66 * ((0.0082000000000000007 * (fRec0[1] + fRec0[2])) - (fConst67 * fRec34[1])));
		fRec0[0] = (double(Ftube(int(TUBE_TABLE_6C16_250k), double((((0.92544984225177063 * (fRec1[0] + fRec1[2])) + (fRec34[0] + (1.8508996845035413 * fRec1[1]))) + -1.3787419999999999)))) + -81.860731707317086);
		fRec35[0] = (fSlow3 + (0.999 * fRec35[1]));
		buf[i] = FAUSTFLOAT((0.025000000000000001 * (fRec0[0] * fRec35[0])));
		fRec4[1] = fRec4[0];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fVec0[1] = fVec0[0];
		fRec18[1] = fRec18[0];
		fRec17[1] = fRec17[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fVec1[1] = fVec1[0];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fRec21[1] = fRec21[0];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fRec23[2] = fRec23[1];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fVec2[1] = fVec2[0];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fVec3[1] = fVec3[0];
		fRec12[1] = fRec12[0];
		fVec4[1] = fVec4[0];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec32[1] = fRec32[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fVec5[1] = fVec5[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec33[1] = fRec33[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fVec6[1] = fVec6[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec34[1] = fRec34[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		fRec35[1] = fRec35[0];
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

} // end namespace gxamp18
