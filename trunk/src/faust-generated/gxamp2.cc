// generated from file '../src/faust/gxamp2.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxamp2 {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int sample_rate;
	int fSampleRate;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst4;
	double fConst6;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec5[2];
	double fConst8;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec16[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec17[2];
	double fConst11;
	double fConst12;
	double fConst14;
	double fConst15;
	double fConst18;
	double fConst19;
	double fConst21;
	double fConst22;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst31;
	double fConst33;
	double fConst34;
	double fRec26[3];
	double fVec0[2];
	double fConst35;
	double fConst36;
	double fRec25[2];
	double fConst37;
	double fConst39;
	double fRec24[2];
	double fRec23[3];
	double fVec1[2];
	double fConst40;
	double fConst42;
	double fRec22[2];
	double fRec21[3];
	double fVec2[2];
	double fConst43;
	double fConst45;
	double fRec20[2];
	double fRec19[3];
	double fConst46;
	double fConst47;
	double fConst48;
	double fRec28[2];
	double fRec27[3];
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fRec32[2];
	double fRec31[3];
	double fConst55;
	double fRec30[3];
	double fRec29[3];
	double fConst56;
	double fConst57;
	double fConst58;
	double fRec35[2];
	double fRec34[3];
	double fConst59;
	double fRec33[3];
	double fVec3[2];
	double fConst60;
	double fRec18[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec36[2];
	double fVec4[2];
	double fRec15[2];
	double fRec14[3];
	double fConst62;
	double fVec5[2];
	double fConst63;
	double fRec37[2];
	double fRec13[2];
	double fRec12[2];
	double fConst65;
	double fConst66;
	double fRec38[2];
	double fVec6[2];
	double fRec11[2];
	double fVec7[2];
	double fRec10[2];
	double fRec9[3];
	double fConst68;
	double fVec8[2];
	double fConst69;
	double fRec39[2];
	double fRec8[2];
	double fRec7[2];
	double fRec40[2];
	double fVec9[2];
	double fRec6[2];
	double fRec4[3];
	double fVec10[2];
	double fRec3[2];
	double fRec2[3];
	double fConst71;
	double fVec11[2];
	double fConst72;
	double fRec41[2];
	double fRec1[2];
	double fRec0[2];
	double fRec42[2];

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
	id = "6V6";
	name = N_("6V6");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec5[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec16[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec17[l2] = 0.0;
	for (int l3 = 0; l3 < 3; l3 = l3 + 1) fRec26[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fVec0[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec25[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec24[l6] = 0.0;
	for (int l7 = 0; l7 < 3; l7 = l7 + 1) fRec23[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fVec1[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec22[l9] = 0.0;
	for (int l10 = 0; l10 < 3; l10 = l10 + 1) fRec21[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fVec2[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec20[l12] = 0.0;
	for (int l13 = 0; l13 < 3; l13 = l13 + 1) fRec19[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec28[l14] = 0.0;
	for (int l15 = 0; l15 < 3; l15 = l15 + 1) fRec27[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec32[l16] = 0.0;
	for (int l17 = 0; l17 < 3; l17 = l17 + 1) fRec31[l17] = 0.0;
	for (int l18 = 0; l18 < 3; l18 = l18 + 1) fRec30[l18] = 0.0;
	for (int l19 = 0; l19 < 3; l19 = l19 + 1) fRec29[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec35[l20] = 0.0;
	for (int l21 = 0; l21 < 3; l21 = l21 + 1) fRec34[l21] = 0.0;
	for (int l22 = 0; l22 < 3; l22 = l22 + 1) fRec33[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fVec3[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec18[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec36[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fVec4[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec15[l27] = 0.0;
	for (int l28 = 0; l28 < 3; l28 = l28 + 1) fRec14[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fVec5[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec37[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec13[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fRec12[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fRec38[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fVec6[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec11[l35] = 0.0;
	for (int l36 = 0; l36 < 2; l36 = l36 + 1) fVec7[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec10[l37] = 0.0;
	for (int l38 = 0; l38 < 3; l38 = l38 + 1) fRec9[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fVec8[l39] = 0.0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec39[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec8[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) fRec7[l42] = 0.0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fRec40[l43] = 0.0;
	for (int l44 = 0; l44 < 2; l44 = l44 + 1) fVec9[l44] = 0.0;
	for (int l45 = 0; l45 < 2; l45 = l45 + 1) fRec6[l45] = 0.0;
	for (int l46 = 0; l46 < 3; l46 = l46 + 1) fRec4[l46] = 0.0;
	for (int l47 = 0; l47 < 2; l47 = l47 + 1) fVec10[l47] = 0.0;
	for (int l48 = 0; l48 < 2; l48 = l48 + 1) fRec3[l48] = 0.0;
	for (int l49 = 0; l49 < 3; l49 = l49 + 1) fRec2[l49] = 0.0;
	for (int l50 = 0; l50 < 2; l50 = l50 + 1) fVec11[l50] = 0.0;
	for (int l51 = 0; l51 < 2; l51 = l51 + 1) fRec41[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fRec1[l52] = 0.0;
	for (int l53 = 0; l53 < 2; l53 = l53 + 1) fRec0[l53] = 0.0;
	for (int l54 = 0; l54 < 2; l54 = l54 + 1) fRec42[l54] = 0.0;
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
	double fConst5 = std::log(7539.822368615503 / fConst0);
	fConst6 = 0.0 - 1.8442 * std::cos(std::exp(0.43359433 * mydsp_faustpower2_f(fConst5) + 0.27547621 * mydsp_faustpower3_f(fConst5) + 0.06446806 * mydsp_faustpower4_f(fConst5) + 0.00506158 * mydsp_faustpower5_f(fConst5) + 1.31282248 * fConst5 + 0.07238887));
	double fConst7 = 1.0 / std::tan(20517.741620594938 / fConst0);
	fConst8 = 1.0 - fConst7;
	double fConst9 = std::tan(942.4777960769379 / fConst0);
	double fConst10 = mydsp_faustpower2_f(fConst9);
	fConst11 = 1.0 / fConst10;
	fConst12 = 2.0 * (1.0 - fConst11);
	double fConst13 = 1.0 / fConst9;
	fConst14 = (fConst13 + -1.0000000000000004) / fConst9 + 1.0;
	fConst15 = 1.0 / ((fConst13 + 1.0000000000000004) / fConst9 + 1.0);
	double fConst16 = std::tan(3769.9111843077517 / fConst0);
	double fConst17 = mydsp_faustpower2_f(fConst16);
	fConst18 = 1.0 / fConst17;
	fConst19 = 2.0 * (1.0 - fConst18);
	double fConst20 = 1.0 / fConst16;
	fConst21 = (fConst20 + -1.0000000000000004) / fConst16 + 1.0;
	fConst22 = 1.0 / ((fConst20 + 1.0000000000000004) / fConst16 + 1.0);
	double fConst23 = std::tan(10053.096491487338 / fConst0);
	double fConst24 = mydsp_faustpower2_f(fConst23);
	fConst25 = 1.0 / fConst24;
	fConst26 = 2.0 * (1.0 - fConst25);
	fConst27 = 1.0 / fConst23;
	fConst28 = (fConst27 + -1.0000000000000004) / fConst23 + 1.0;
	fConst29 = 1.0 / ((fConst27 + 1.0000000000000004) / fConst23 + 1.0);
	double fConst30 = std::tan(47123.8898038469 / fConst0);
	fConst31 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst30));
	double fConst32 = 1.0 / fConst30;
	fConst33 = (fConst32 + -1.414213562373095) / fConst30 + 1.0;
	fConst34 = 1.0 / ((fConst32 + 1.414213562373095) / fConst30 + 1.0);
	fConst35 = 1.0 / (fConst1 * fConst3);
	fConst36 = 0.0 - fConst35;
	fConst37 = 1.0 - fConst27;
	double fConst38 = fConst27 + 1.0;
	fConst39 = 1.0 / fConst38;
	fConst40 = 1.0 - fConst20;
	double fConst41 = fConst20 + 1.0;
	fConst42 = 1.0 / fConst41;
	fConst43 = 1.0 - fConst13;
	double fConst44 = fConst13 + 1.0;
	fConst45 = 1.0 / fConst44;
	fConst46 = fConst43 / fConst44;
	fConst47 = 1.0 / (fConst9 * fConst44);
	fConst48 = 0.0 - fConst47;
	fConst49 = 0.0 - 2.0 / fConst10;
	fConst50 = 1.0 - fConst43 / fConst9;
	fConst51 = 1.0 / (fConst44 / fConst9 + 1.0);
	fConst52 = 1.0 - fConst40 / fConst16;
	fConst53 = 1.0 / (fConst41 / fConst16 + 1.0);
	fConst54 = 0.0 - 1.0 / (fConst23 * fConst38);
	fConst55 = 0.0 - 2.0 / fConst24;
	fConst56 = fConst40 / fConst41;
	fConst57 = 1.0 / (fConst16 * fConst41);
	fConst58 = 0.0 - fConst57;
	fConst59 = 0.0 - 2.0 / fConst17;
	fConst60 = 1.0 / (fConst7 + 1.0);
	double fConst61 = 1.0 / std::tan(270.1769682087222 / fConst0);
	fConst62 = 1.0 - fConst61;
	fConst63 = 1.0 / (fConst61 + 1.0);
	double fConst64 = 3.141592653589793 / fConst0;
	fConst65 = 1.0 - fConst64;
	fConst66 = 1.0 / (fConst64 + 1.0);
	double fConst67 = 1.0 / std::tan(414.6902302738527 / fConst0);
	fConst68 = 1.0 - fConst67;
	fConst69 = 1.0 / (fConst67 + 1.0);
	double fConst70 = 1.0 / std::tan(609.4689747964198 / fConst0);
	fConst71 = 1.0 - fConst70;
	fConst72 = 1.0 / (fConst70 + 1.0);
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
#define fCheckbox1 (*fCheckbox1_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	int iSlow0 = int(double(fCheckbox0));
	double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
	int iSlow2 = int(double(fCheckbox1));
	double fSlow3 = 0.0010000000000000009 * double(fVslider1);
	double fSlow4 = 1.000000000000001e-05 * double(fVslider2);
	double fSlow5 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider3));
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		fRec5[0] = fSlow1 + 0.999 * fRec5[1];
		fRec16[0] = fSlow3 + 0.999 * fRec16[1];
		double fTemp0 = 2.0 * (fRec16[0] + -0.5);
		fRec17[0] = fSlow4 + 0.999 * fRec17[1];
		double fTemp1 = 1.0 - fRec17[0];
		double fTemp2 = double(buf[i0]);
		fRec26[0] = fTemp2 * fRec17[0] - fConst34 * (fConst33 * fRec26[2] + fConst31 * fRec26[1]);
		double fTemp3 = fRec26[2] + fRec26[0] + 2.0 * fRec26[1];
		fVec0[0] = fTemp3;
		fRec25[0] = fConst34 * (fConst35 * fTemp3 + fConst36 * fVec0[1]) - fConst4 * fRec25[1];
		fRec24[0] = 0.0 - fConst39 * (fConst37 * fRec24[1] - (fRec25[0] + fRec25[1]));
		fRec23[0] = fRec24[0] - fConst29 * (fConst28 * fRec23[2] + fConst26 * fRec23[1]);
		double fTemp4 = fRec23[2] + fRec23[0] + 2.0 * fRec23[1];
		fVec1[0] = fTemp4;
		fRec22[0] = 0.0 - fConst42 * (fConst40 * fRec22[1] - fConst29 * (fTemp4 + fVec1[1]));
		fRec21[0] = fRec22[0] - fConst22 * (fConst21 * fRec21[2] + fConst19 * fRec21[1]);
		double fTemp5 = fRec21[2] + fRec21[0] + 2.0 * fRec21[1];
		fVec2[0] = fTemp5;
		fRec20[0] = 0.0 - fConst45 * (fConst43 * fRec20[1] - fConst22 * (fTemp5 + fVec2[1]));
		fRec19[0] = fRec20[0] - fConst15 * (fConst14 * fRec19[2] + fConst12 * fRec19[1]);
		double fTemp6 = std::max<double>(-1.0, std::min<double>(1.0, fConst15 * (fRec19[2] + fRec19[0] + 2.0 * fRec19[1]) * std::pow(1e+01, 0.9 * fRec16[0])));
		fRec28[0] = fConst22 * (fConst47 * fTemp5 + fConst48 * fVec2[1]) - fConst46 * fRec28[1];
		fRec27[0] = fRec28[0] - fConst15 * (fConst14 * fRec27[2] + fConst12 * fRec27[1]);
		double fTemp7 = std::max<double>(-1.0, std::min<double>(1.0, fConst15 * (fConst11 * fRec27[0] + fConst49 * fRec27[1] + fConst11 * fRec27[2]) * std::pow(1e+01, 2.0 * fRec16[0])));
		double fTemp8 = fConst12 * fRec29[1];
		double fTemp9 = fConst19 * fRec30[1];
		fRec32[0] = fConst54 * fRec25[1] - fConst39 * (fConst37 * fRec32[1] - fConst27 * fRec25[0]);
		fRec31[0] = fRec32[0] - fConst29 * (fConst28 * fRec31[2] + fConst26 * fRec31[1]);
		fRec30[0] = fConst29 * (fConst25 * fRec31[0] + fConst55 * fRec31[1] + fConst25 * fRec31[2]) - fConst53 * (fConst52 * fRec30[2] + fTemp9);
		fRec29[0] = fRec30[2] + fConst53 * (fTemp9 + fConst52 * fRec30[0]) - fConst51 * (fConst50 * fRec29[2] + fTemp8);
		double fTemp10 = std::max<double>(-1.0, std::min<double>(1.0, (fRec29[2] + fConst51 * (fTemp8 + fConst50 * fRec29[0])) * std::pow(1e+01, 0.8 * fRec16[0])));
		double fTemp11 = fConst12 * fRec33[1];
		fRec35[0] = fConst29 * (fConst57 * fTemp4 + fConst58 * fVec1[1]) - fConst56 * fRec35[1];
		fRec34[0] = fRec35[0] - fConst22 * (fConst21 * fRec34[2] + fConst19 * fRec34[1]);
		fRec33[0] = fConst22 * (fConst18 * fRec34[0] + fConst59 * fRec34[1] + fConst18 * fRec34[2]) - fConst51 * (fConst50 * fRec33[2] + fTemp11);
		double fTemp12 = std::max<double>(-1.0, std::min<double>(1.0, (fRec33[2] + fConst51 * (fTemp11 + fConst50 * fRec33[0])) * std::pow(1e+01, 1.2 * fRec16[0])));
		double fTemp13 = 1.333521432 * fTemp12 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp12)) + 1.584893192 * (fTemp10 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp10)) + fTemp7 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp7))) + 1.2589412 * fTemp6 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp6));
		fVec3[0] = fTemp13;
		fRec18[0] = 0.0 - fConst60 * (fConst8 * fRec18[1] - (fTemp13 + fVec3[1]));
		fRec36[0] = fSlow5 + 0.999 * fRec36[1];
		double fTemp14 = fRec36[0] * (fRec18[0] * (1.0 - std::max<double>(0.0, -1.0 * fTemp0)) + fTemp2 * (fTemp1 * (1.25 * fRec16[0] * (4.0 * (1.0 - std::fabs(fTemp2 * fTemp1)) + -1.0) + 1.0) + fRec17[0] * (1.0 - std::max<double>(0.0, fTemp0))));
		fVec4[0] = fTemp14;
		fRec15[0] = 0.9302847925323914 * (fTemp14 + fVec4[1]) - 0.8605695850647829 * fRec15[1];
		fRec14[0] = fRec15[0] - (1.8405051250752198 * fRec14[1] + 0.8612942439318627 * fRec14[2]);
		double fTemp15 = 1.8508996845035413 * fRec14[1];
		double fTemp16 = 0.9254498422517706 * (fRec14[0] + fRec14[2]);
		double fTemp17 = (fTemp15 + fTemp16) / (Ranode(TUBE_TABLE_6V6_68k, fRec13[1]) + 1e+05);
		fVec5[0] = fTemp17;
		fRec37[0] = fConst63 * (2.7e+03 * (fTemp17 + fVec5[1]) - fConst62 * fRec37[1]);
		fRec13[0] = Ftube(TUBE_TABLE_6V6_68k, fTemp16 + fRec37[0] + fTemp15 + -1.784417) + -183.9104814814815;
		fRec12[0] = 0.025 * (fConst35 * fRec13[0] + fConst36 * fRec13[1]) - fConst4 * fRec12[1];
		fRec38[0] = fConst66 * (fConst65 * fRec38[1] + 0.025 * (fRec13[0] - fRec13[1]));
		double fTemp18 = ((iSlow2) ? fRec38[0] : fRec12[0]);
		fVec6[0] = fTemp18;
		fRec11[0] = fConst60 * (0.77 * (fTemp18 + fVec6[1]) - fConst8 * fRec11[1]);
		double fTemp19 = fRec36[0] * fRec11[0];
		fVec7[0] = fTemp19;
		fRec10[0] = 0.9302847925323914 * (fTemp19 + fVec7[1]) - 0.8605695850647829 * fRec10[1];
		fRec9[0] = fRec10[0] - (1.8405051250752198 * fRec9[1] + 0.8612942439318627 * fRec9[2]);
		double fTemp20 = 1.8508996845035413 * fRec9[1];
		double fTemp21 = 0.9254498422517706 * (fRec9[0] + fRec9[2]);
		double fTemp22 = (fTemp20 + fTemp21) / (Ranode(TUBE_TABLE_6V6_250k, fRec8[1]) + 1e+05);
		fVec8[0] = fTemp22;
		fRec39[0] = fConst69 * (1.5e+03 * (fTemp22 + fVec8[1]) - fConst68 * fRec39[1]);
		fRec8[0] = Ftube(TUBE_TABLE_6V6_250k, fTemp21 + fRec39[0] + fTemp20 + -1.364616) + -159.0256;
		fRec7[0] = 0.025 * (fConst35 * fRec8[0] + fConst36 * fRec8[1]) - fConst4 * fRec7[1];
		fRec40[0] = fConst66 * (fConst65 * fRec40[1] + 0.025 * (fRec8[0] - fRec8[1]));
		double fTemp23 = ((iSlow2) ? fRec40[0] : fRec7[0]);
		fVec9[0] = fTemp23;
		fRec6[0] = fConst60 * (0.77 * (fTemp23 + fVec9[1]) - fConst8 * fRec6[1]);
		fRec4[0] = fRec6[0] * fRec5[0] - (fConst6 * fRec4[1] + 0.8502684100000001 * fRec4[2]);
		double fTemp24 = fRec4[0] - 1.059 * fRec4[1];
		fVec10[0] = fTemp24;
		fRec3[0] = 0.9302847925323914 * (fTemp24 + fVec10[1]) - 0.8605695850647829 * fRec3[1];
		fRec2[0] = fRec3[0] - (1.8405051250752198 * fRec2[1] + 0.8612942439318627 * fRec2[2]);
		double fTemp25 = 1.8508996845035413 * fRec2[1];
		double fTemp26 = 0.9254498422517706 * (fRec2[0] + fRec2[2]);
		double fTemp27 = (fTemp25 + fTemp26) / (Ranode(TUBE_TABLE_6V6_250k, fRec1[1]) + 1e+05);
		fVec11[0] = fTemp27;
		fRec41[0] = fConst72 * (8.2e+02 * (fTemp27 + fVec11[1]) - fConst71 * fRec41[1]);
		fRec1[0] = Ftube(TUBE_TABLE_6V6_250k, fTemp26 + fRec41[0] + fTemp25 + -0.962132) + -132.6668292682927;
		fRec0[0] = 0.025 * (fConst35 * fRec1[0] + fConst36 * fRec1[1]) - fConst4 * fRec0[1];
		fRec42[0] = fConst66 * (fConst65 * fRec42[1] + 0.025 * (fRec1[0] - fRec1[1]));
		buf[i0] = FAUSTFLOAT(0.77 * ((iSlow0) ? fRec42[0] : fRec0[0]));
		fRec5[1] = fRec5[0];
		fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fVec0[1] = fVec0[0];
		fRec25[1] = fRec25[0];
		fRec24[1] = fRec24[0];
		fRec23[2] = fRec23[1];
		fRec23[1] = fRec23[0];
		fVec1[1] = fVec1[0];
		fRec22[1] = fRec22[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		fVec2[1] = fVec2[0];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fRec28[1] = fRec28[0];
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fRec29[2] = fRec29[1];
		fRec29[1] = fRec29[0];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fVec3[1] = fVec3[0];
		fRec18[1] = fRec18[0];
		fRec36[1] = fRec36[0];
		fVec4[1] = fVec4[0];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fVec5[1] = fVec5[0];
		fRec37[1] = fRec37[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec38[1] = fRec38[0];
		fVec6[1] = fVec6[0];
		fRec11[1] = fRec11[0];
		fVec7[1] = fVec7[0];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fVec8[1] = fVec8[0];
		fRec39[1] = fRec39[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec40[1] = fRec40[0];
		fVec9[1] = fVec9[0];
		fRec6[1] = fRec6[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fVec10[1] = fVec10[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fVec11[1] = fVec11[0];
		fRec41[1] = fRec41[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec42[1] = fRec42[0];
	}
	smp.down(buf, output0);
#undef fCheckbox0
#undef fVslider0
#undef fCheckbox1
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
	fVslider3_ = reg.registerFloatVar("amp2.stage1.Pregain","","SA","",&fVslider3, -6.0, -2e+01, 2e+01, 0.1, 0);
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

} // end namespace gxamp2
