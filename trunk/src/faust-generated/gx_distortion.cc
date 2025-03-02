// generated from file '../src/faust/gx_distortion.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace gx_distortion {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	int iVec0[2];
	FAUSTFLOAT fVslider1;
	double fRec0[2];
	FAUSTFLOAT fEntry0;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT fEntry2;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fVslider2;
	double fVec1[2];
	FAUSTFLOAT fVslider3;
	double fRec10[2];
	double fRec11[2];
	double fRec9[3];
	double fVec2[2];
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fRec8[2];
	double fRec7[2];
	double fRec6[3];
	double fVec3[2];
	double fRec5[2];
	double fRec4[3];
	double fVec4[2];
	double fRec3[2];
	double fRec2[3];
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT fVslider7;
	double fRec12[2];
	double fRec14[2];
	double fRec13[3];
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT fVslider9;
	double fRec15[2];
	double fRec18[2];
	double fRec17[3];
	double fRec16[3];
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT fVslider11;
	double fRec19[2];
	double fRec23[2];
	double fRec22[3];
	double fRec21[3];
	double fRec20[3];
	FAUSTFLOAT fVslider12;
	FAUSTFLOAT fVslider13;
	double fRec24[2];
	double fVec5[2];
	double fConst13;
	double fConst14;
	double fConst15;
	double fRec1[2];

	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int sample_rate, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



static const char* parm_groups[] = {
	"resonator", N_("Distortion resonator"),
	0
	};

Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "gx_distortion";
	name = N_("Multi Band Distortion");
	groups = parm_groups;
	description = ""; // description (tooltip)
	category = N_("Distortion");       // category
	shortname = N_("Distortion");     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	load_ui = load_ui_f_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) iVec0[l0] = 0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec0[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fVec1[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec10[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec11[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec9[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fVec2[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec8[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec7[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec6[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fVec3[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec5[l11] = 0.0;
	for (int l12 = 0; l12 < 3; l12 = l12 + 1) fRec4[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fVec4[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec3[l14] = 0.0;
	for (int l15 = 0; l15 < 3; l15 = l15 + 1) fRec2[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec12[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec14[l17] = 0.0;
	for (int l18 = 0; l18 < 3; l18 = l18 + 1) fRec13[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec15[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec18[l20] = 0.0;
	for (int l21 = 0; l21 < 3; l21 = l21 + 1) fRec17[l21] = 0.0;
	for (int l22 = 0; l22 < 3; l22 = l22 + 1) fRec16[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec19[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec23[l24] = 0.0;
	for (int l25 = 0; l25 < 3; l25 = l25 + 1) fRec22[l25] = 0.0;
	for (int l26 = 0; l26 < 3; l26 = l26 + 1) fRec21[l26] = 0.0;
	for (int l27 = 0; l27 < 3; l27 = l27 + 1) fRec20[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec24[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fVec5[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec1[l30] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 3.141592653589793 / fConst0;
	fConst2 = std::tan(47123.8898038469 / fConst0);
	fConst3 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst2));
	fConst4 = 1.0 / fConst2;
	fConst5 = (fConst4 + -1.414213562373095) / fConst2 + 1.0;
	fConst6 = (fConst4 + 1.414213562373095) / fConst2 + 1.0;
	fConst7 = 1.0 / fConst6;
	fConst8 = std::tan(97.38937226128358 / fConst0);
	fConst9 = 1.0 / (fConst8 * fConst6);
	fConst10 = 1.0 / fConst8;
	fConst11 = 1.0 - fConst10;
	fConst12 = 1.0 / (fConst10 + 1.0);
	fConst13 = 1.0 / std::tan(20517.741620594938 / fConst0);
	fConst14 = 1.0 - fConst13;
	fConst15 = 1.0 / (fConst13 + 1.0);
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = 0.01 * double(fVslider0);
	double fSlow1 = 1.0 - fSlow0;
	double fSlow2 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (double(fVslider1) + -1e+01));
	double fSlow3 = std::tan(fConst1 * double(fEntry0));
	double fSlow4 = mydsp_faustpower2_f(fSlow3);
	double fSlow5 = 2.0 * (1.0 - 1.0 / fSlow4);
	double fSlow6 = 1.0 / fSlow3;
	double fSlow7 = (fSlow6 + -1.0000000000000004) / fSlow3 + 1.0;
	double fSlow8 = (fSlow6 + 1.0000000000000004) / fSlow3 + 1.0;
	double fSlow9 = 1.0 / fSlow8;
	double fSlow10 = std::tan(fConst1 * double(fEntry1));
	double fSlow11 = mydsp_faustpower2_f(fSlow10);
	double fSlow12 = 2.0 * (1.0 - 1.0 / fSlow11);
	double fSlow13 = 1.0 / fSlow10;
	double fSlow14 = (fSlow13 + -1.0000000000000004) / fSlow10 + 1.0;
	double fSlow15 = (fSlow13 + 1.0000000000000004) / fSlow10 + 1.0;
	double fSlow16 = 1.0 / fSlow15;
	double fSlow17 = std::tan(fConst1 * double(fEntry2));
	double fSlow18 = mydsp_faustpower2_f(fSlow17);
	double fSlow19 = 2.0 * (1.0 - 1.0 / fSlow18);
	double fSlow20 = 1.0 / fSlow17;
	double fSlow21 = (fSlow20 + -1.0000000000000004) / fSlow17 + 1.0;
	double fSlow22 = (fSlow20 + 1.0000000000000004) / fSlow17 + 1.0;
	double fSlow23 = 1.0 / fSlow22;
	int iSlow24 = int(double(fCheckbox0));
	double fSlow25 = 1.0 - double(fVslider2);
	double fSlow26 = double(fVslider3);
	int iSlow27 = int(std::min<double>(4096.0, std::max<double>(0.0, fSlow26)));
	int iSlow28 = int(std::min<double>(4096.0, std::max<double>(0.0, fSlow26 + -1.0)));
	double fSlow29 = 1.0 - fSlow20;
	double fSlow30 = 1.0 / (fSlow20 + 1.0);
	double fSlow31 = 1.0 - fSlow13;
	double fSlow32 = fSlow13 + 1.0;
	double fSlow33 = 1.0 / fSlow32;
	double fSlow34 = 1.0 - fSlow6;
	double fSlow35 = fSlow6 + 1.0;
	double fSlow36 = 1.0 / fSlow35;
	double fSlow37 = double(fVslider5);
	double fSlow38 = std::pow(1e+01, 2.0 * fSlow37 * double(fVslider4)) / fSlow8;
	double fSlow39 = double(fVslider6);
	double fSlow40 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (double(fVslider7) + -1e+01));
	double fSlow41 = std::pow(1e+01, 2.0 * fSlow37 * double(fVslider8)) / (fSlow4 * fSlow8);
	double fSlow42 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (double(fVslider9) + -1e+01));
	double fSlow43 = 1.0 - fSlow34 / fSlow3;
	double fSlow44 = 1.0 / (fSlow35 / fSlow3 + 1.0);
	double fSlow45 = 1.0 / (fSlow11 * fSlow15);
	double fSlow46 = std::pow(1e+01, 2.0 * fSlow37 * double(fVslider10));
	double fSlow47 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (double(fVslider11) + -1e+01));
	double fSlow48 = 1.0 - fSlow31 / fSlow10;
	double fSlow49 = 1.0 / (fSlow32 / fSlow10 + 1.0);
	double fSlow50 = 1.0 / (fSlow18 * fSlow22);
	double fSlow51 = std::pow(1e+01, 2.0 * fSlow37 * double(fVslider12));
	double fSlow52 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (double(fVslider13) + -1e+01));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		iVec0[0] = 1;
		fRec0[0] = fSlow2 + 0.999 * fRec0[1];
		double fTemp1 = fSlow0 * fTemp0;
		double fTemp2 = fTemp1 + fSlow25 * fRec10[1];
		fVec1[0] = fTemp2;
		fRec10[0] = 0.5 * (fVec1[iSlow28] + fVec1[iSlow27]);
		fRec11[0] = 1e-20 * double(1 - iVec0[1]) - fRec11[1];
		fRec9[0] = fRec11[0] + ((iSlow24) ? fRec10[0] : fTemp1) - fConst7 * (fConst5 * fRec9[2] + fConst3 * fRec9[1]);
		double fTemp3 = fRec9[2] + fRec9[0] + 2.0 * fRec9[1];
		fVec2[0] = fTemp3;
		fRec8[0] = -(fConst12 * (fConst11 * fRec8[1] - fConst9 * (fTemp3 - fVec2[1])));
		fRec7[0] = -(fSlow30 * (fSlow29 * fRec7[1] - (fRec8[0] + fRec8[1])));
		fRec6[0] = fRec7[0] - fSlow23 * (fSlow21 * fRec6[2] + fSlow19 * fRec6[1]);
		double fTemp4 = fSlow23 * (fRec6[2] + fRec6[0] + 2.0 * fRec6[1]);
		fVec3[0] = fTemp4;
		fRec5[0] = -(fSlow33 * (fSlow31 * fRec5[1] - (fTemp4 + fVec3[1])));
		fRec4[0] = fRec5[0] - fSlow16 * (fSlow14 * fRec4[2] + fSlow12 * fRec4[1]);
		double fTemp5 = fSlow16 * (fRec4[2] + fRec4[0] + 2.0 * fRec4[1]);
		fVec4[0] = fTemp5;
		fRec3[0] = -(fSlow36 * (fSlow34 * fRec3[1] - (fTemp5 + fVec4[1])));
		fRec2[0] = fRec3[0] - fSlow9 * (fSlow7 * fRec2[2] + fSlow5 * fRec2[1]);
		double fTemp6 = std::max<double>(-1.0, std::min<double>(1.0, fSlow39 + fSlow38 * (fRec2[2] + fRec2[0] + 2.0 * fRec2[1])));
		fRec12[0] = fSlow40 + 0.999 * fRec12[1];
		fRec14[0] = -(fSlow36 * (fSlow34 * fRec14[1] - fSlow6 * (fTemp5 - fVec4[1])));
		fRec13[0] = fRec14[0] - fSlow9 * (fSlow7 * fRec13[2] + fSlow5 * fRec13[1]);
		double fTemp7 = std::max<double>(-1.0, std::min<double>(1.0, fSlow39 + fSlow41 * (fRec13[2] + (fRec13[0] - 2.0 * fRec13[1]))));
		fRec15[0] = fSlow42 + 0.999 * fRec15[1];
		double fTemp8 = fSlow5 * fRec16[1];
		fRec18[0] = -(fSlow33 * (fSlow31 * fRec18[1] - fSlow13 * (fTemp4 - fVec3[1])));
		fRec17[0] = fRec18[0] - fSlow16 * (fSlow14 * fRec17[2] + fSlow12 * fRec17[1]);
		fRec16[0] = fSlow45 * (fRec17[2] + (fRec17[0] - 2.0 * fRec17[1])) - fSlow44 * (fSlow43 * fRec16[2] + fTemp8);
		double fTemp9 = std::max<double>(-1.0, std::min<double>(1.0, fSlow39 + fSlow46 * (fRec16[2] + fSlow44 * (fTemp8 + fSlow43 * fRec16[0]))));
		fRec19[0] = fSlow47 + 0.999 * fRec19[1];
		double fTemp10 = fSlow5 * fRec20[1];
		double fTemp11 = fSlow12 * fRec21[1];
		fRec23[0] = -(fSlow30 * (fSlow29 * fRec23[1] - fSlow20 * (fRec8[0] - fRec8[1])));
		fRec22[0] = fRec23[0] - fSlow23 * (fSlow21 * fRec22[2] + fSlow19 * fRec22[1]);
		fRec21[0] = fSlow50 * (fRec22[2] + (fRec22[0] - 2.0 * fRec22[1])) - fSlow49 * (fSlow48 * fRec21[2] + fTemp11);
		fRec20[0] = fRec21[2] + fSlow49 * (fTemp11 + fSlow48 * fRec21[0]) - fSlow44 * (fSlow43 * fRec20[2] + fTemp10);
		double fTemp12 = std::max<double>(-1.0, std::min<double>(1.0, fSlow39 + fSlow51 * (fRec20[2] + fSlow44 * (fTemp10 + fSlow43 * fRec20[0]))));
		fRec24[0] = fSlow52 + 0.999 * fRec24[1];
		double fTemp13 = fRec24[0] * fTemp12 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp12)) + fRec19[0] * fTemp9 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp9)) + fRec15[0] * fTemp7 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp7)) + fRec12[0] * fTemp6 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp6));
		fVec5[0] = fTemp13;
		fRec1[0] = -(fConst15 * (fConst14 * fRec1[1] - (fTemp13 + fVec5[1])));
		output0[i0] = FAUSTFLOAT(fRec1[0] * fRec0[0] + fSlow1 * fTemp0);
		iVec0[1] = iVec0[0];
		fRec0[1] = fRec0[0];
		fVec1[1] = fVec1[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fVec2[1] = fVec2[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fVec3[1] = fVec3[0];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fVec4[1] = fVec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec12[1] = fRec12[0];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fRec15[1] = fRec15[0];
		fRec18[1] = fRec18[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fRec19[1] = fRec19[0];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fRec24[1] = fRec24[0];
		fVec5[1] = fVec5[0];
		fRec1[1] = fRec1[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("gx_distortion.drive",N_("Drive"),"S","",&fVslider5, 0.64, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("gx_distortion.gain",N_("Gain"),"S","",&fVslider1, 2.0, -1e+01, 1e+01, 0.1, 0);
	reg.registerFloatVar("gx_distortion.high_drive",N_("Hi"),"S","",&fVslider12, 1.0, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("gx_distortion.high_gain",N_("Hi"),"S","",&fVslider13, 1e+01, -1e+01, 2e+01, 0.1, 0);
	reg.registerFloatVar("gx_distortion.level",N_("Level"),"S","",&fVslider6, 0.0, 0.0, 0.5, 0.01, 0);
	reg.registerFloatVar("gx_distortion.low_drive",N_("Lo"),"S","",&fVslider4, 1.0, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("gx_distortion.low_gain",N_("Lo"),"S","",&fVslider7, 1e+01, -1e+01, 2e+01, 0.1, 0);
	reg.registerFloatVar("gx_distortion.middle_h_drive",N_("HiMid"),"S","",&fVslider10, 1.0, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("gx_distortion.middle_h_gain",N_("HiMid"),"S","",&fVslider11, 1e+01, -1e+01, 2e+01, 0.1, 0);
	reg.registerFloatVar("gx_distortion.middle_l_drive",N_("LoMid"),"S","",&fVslider8, 1.0, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("gx_distortion.middle_l_gain",N_("LoMid"),"S","",&fVslider9, 1e+01, -1e+01, 2e+01, 0.1, 0);
	reg.registerFloatVar("gx_distortion.resonator.on_off",N_("resonat"),"B","",&fCheckbox0, 0.0, 0.0, 1.0, 1.0, 0);
	reg.registerFloatVar("gx_distortion.split_high_freq",N_("Split Hi"),"S","",&fEntry2, 1.25e+03, 1.25e+03, 1.2e+04, 1e+01, 0);
	reg.registerFloatVar("gx_distortion.split_low_freq",N_("Split Lo"),"S","",&fEntry0, 2.5e+02, 2e+01, 6e+02, 1e+01, 0);
	reg.registerFloatVar("gx_distortion.split_middle_freq",N_("Split Mid"),"S","",&fEntry1, 6.5e+02, 6e+02, 1.25e+03, 1e+01, 0);
	reg.registerFloatVar("gx_distortion.trigger",N_("Trigger"),"S","",&fVslider2, 0.12, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("gx_distortion.vibrato",N_("Vibrato"),"S","",&fVslider3, 1.0, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("gx_distortion.wet_dry",N_("Wet/Dry"),"S",N_("percentage of processed signal in output signal"),&fVslider0, 1e+02, 0.0, 1e+02, 1.0, 0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade_file("gx_distortion_ui.glade");
        return 0;
    }
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("gx_distortion" "." p)
// ----- distortion
b.openHorizontalhideBox("");
b.create_master_slider("gx_distortion.drive", _("drive"));
b.closeBox();
b.openHorizontalBox("");
{
    b.openVerticalBox("");
    {
	b.openVerticalBox("");
	{
	    b.openFlipLabelBox(_("  drive "));
	    {
		b.openHorizontalBox("");
		{
		    b.create_small_rackknobr("gx_distortion.drive", _("  drive "));
		    b.create_small_rackknobr("gx_distortion.low_drive", _(" low "));
		    b.create_small_rackknobr("gx_distortion.middle_l_drive", _(" middle l. "));
		    b.create_small_rackknobr("gx_distortion.middle_h_drive", _(" middle h. "));
		    b.create_small_rackknobr("gx_distortion.high_drive", _(" high "));
		}
		b.closeBox();
	    }
	    b.closeBox();
	    b.openFlipLabelBox(_("  gain  "));
	    {
		b.openHorizontalBox("");
		{
		    b.create_small_rackknob("gx_distortion.gain", _("  gain  "));
		    b.create_small_rackknob("gx_distortion.low_gain", _(" low "));
		    b.create_small_rackknob("gx_distortion.middle_l_gain", _(" middle l. "));
		    b.create_small_rackknob("gx_distortion.middle_h_gain", _(" middle h. "));
		    b.create_small_rackknob("gx_distortion.high_gain", _(" high "));
		}
		b.closeBox();
	    }
	    b.closeBox();
	}
	b.closeBox();

	b.openHorizontalBox("");
	{
	    b.create_small_rackknob("gx_distortion.wet_dry", _("dry/wet"));
	    b.create_small_rackknob("gx_distortion.level", _("  level  "));
	    b.openVerticalBox(_("frequency split Hz"));
	    {
		b.openpaintampBox("");
		{
		    b.openHorizontalBox("");
		    {
			b.insertSpacer();
			b.create_wheel("gx_distortion.split_low_freq", _("split low freq"));
			b.insertSpacer();
			b.create_wheel("gx_distortion.split_middle_freq", _("split m. freq"));
			b.insertSpacer();
			b.create_wheel("gx_distortion.split_high_freq", _("split high freq"));
			b.insertSpacer();
		    }
		    b.closeBox();
		}
		b.closeBox();
	    }
	    b.closeBox();
	}
	b.closeBox();
    }
    b.closeBox();

    b.openVerticalBox(_("resonator"));
    {
	b.create_small_rackknob("gx_distortion.trigger", _("trigger "));
	b.create_small_rackknob("gx_distortion.vibrato", _(" vibrato "));
	b.create_switch_no_caption(sw_switchit, "gx_distortion.resonator.on_off");
    }
    b.closeBox();
}
b.closeBox();

#undef PARAM
        return 0;
    }
	return -1;
}

int Dsp::load_ui_f_static(const UiBuilder& b, int form)
{
	return static_cast<Dsp*>(b.plugin)->load_ui_f(b, form);
}
PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace gx_distortion
