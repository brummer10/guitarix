// generated from file '../src/faust/selecteq.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace selecteq {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	double fRec0[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	double fConst0;
	FAUSTFLOAT fVslider3;
	double fRec2[2];
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT fVslider6;
	double fRec4[2];
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT fVslider9;
	double fRec6[2];
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT fVslider11;
	FAUSTFLOAT fVslider12;
	double fRec8[2];
	FAUSTFLOAT fVslider13;
	FAUSTFLOAT fVslider14;
	FAUSTFLOAT fVslider15;
	double fRec10[2];
	FAUSTFLOAT fVslider16;
	FAUSTFLOAT fVslider17;
	FAUSTFLOAT fVslider18;
	double fRec12[2];
	FAUSTFLOAT fVslider19;
	FAUSTFLOAT fVslider20;
	FAUSTFLOAT fVslider21;
	double fRec14[2];
	FAUSTFLOAT fVslider22;
	FAUSTFLOAT fVslider23;
	FAUSTFLOAT fVslider24;
	double fRec16[2];
	FAUSTFLOAT fVslider25;
	FAUSTFLOAT fVslider26;
	FAUSTFLOAT fVslider27;
	double fRec18[2];
	FAUSTFLOAT fVslider28;
	FAUSTFLOAT fVslider29;
	double fRec19[3];
	double fRec17[3];
	double fRec15[3];
	double fRec13[3];
	double fRec11[3];
	double fRec9[3];
	double fRec7[3];
	double fRec5[3];
	double fRec3[3];
	double fRec1[3];

	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
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



Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "eqs";
	name = N_("Scaleable EQ");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Tone Control");       // category
	shortname = "";     // shortname
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec2[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec4[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec6[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec8[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec10[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec12[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec14[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec16[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec18[l9] = 0.0;
	for (int l10 = 0; l10 < 3; l10 = l10 + 1) fRec19[l10] = 0.0;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec17[l11] = 0.0;
	for (int l12 = 0; l12 < 3; l12 = l12 + 1) fRec15[l12] = 0.0;
	for (int l13 = 0; l13 < 3; l13 = l13 + 1) fRec13[l13] = 0.0;
	for (int l14 = 0; l14 < 3; l14 = l14 + 1) fRec11[l14] = 0.0;
	for (int l15 = 0; l15 < 3; l15 = l15 + 1) fRec9[l15] = 0.0;
	for (int l16 = 0; l16 < 3; l16 = l16 + 1) fRec7[l16] = 0.0;
	for (int l17 = 0; l17 < 3; l17 = l17 + 1) fRec5[l17] = 0.0;
	for (int l18 = 0; l18 < 3; l18 = l18 + 1) fRec3[l18] = 0.0;
	for (int l19 = 0; l19 < 3; l19 = l19 + 1) fRec1[l19] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = 3.141592653589793 / std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
	double fSlow1 = 1.0 / double(fVslider1);
	double fSlow2 = std::tan(fConst0 * double(fVslider2));
	double fSlow3 = 2.0 * (mydsp_faustpower2_f(fSlow2) + -1.0);
	double fSlow4 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider3));
	double fSlow5 = 1.0 / double(fVslider4);
	double fSlow6 = std::tan(fConst0 * double(fVslider5));
	double fSlow7 = 2.0 * (mydsp_faustpower2_f(fSlow6) + -1.0);
	double fSlow8 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider6));
	double fSlow9 = 1.0 / double(fVslider7);
	double fSlow10 = std::tan(fConst0 * double(fVslider8));
	double fSlow11 = 2.0 * (mydsp_faustpower2_f(fSlow10) + -1.0);
	double fSlow12 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider9));
	double fSlow13 = 1.0 / double(fVslider10);
	double fSlow14 = std::tan(fConst0 * double(fVslider11));
	double fSlow15 = 2.0 * (mydsp_faustpower2_f(fSlow14) + -1.0);
	double fSlow16 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider12));
	double fSlow17 = 1.0 / double(fVslider13);
	double fSlow18 = std::tan(fConst0 * double(fVslider14));
	double fSlow19 = 2.0 * (mydsp_faustpower2_f(fSlow18) + -1.0);
	double fSlow20 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider15));
	double fSlow21 = 1.0 / double(fVslider16);
	double fSlow22 = std::tan(fConst0 * double(fVslider17));
	double fSlow23 = 2.0 * (mydsp_faustpower2_f(fSlow22) + -1.0);
	double fSlow24 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider18));
	double fSlow25 = 1.0 / double(fVslider19);
	double fSlow26 = std::tan(fConst0 * double(fVslider20));
	double fSlow27 = 2.0 * (mydsp_faustpower2_f(fSlow26) + -1.0);
	double fSlow28 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider21));
	double fSlow29 = 1.0 / double(fVslider22);
	double fSlow30 = std::tan(fConst0 * double(fVslider23));
	double fSlow31 = 2.0 * (mydsp_faustpower2_f(fSlow30) + -1.0);
	double fSlow32 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider24));
	double fSlow33 = 1.0 / double(fVslider25);
	double fSlow34 = std::tan(fConst0 * double(fVslider26));
	double fSlow35 = 2.0 * (mydsp_faustpower2_f(fSlow34) + -1.0);
	double fSlow36 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider27));
	double fSlow37 = 1.0 / double(fVslider28);
	double fSlow38 = std::tan(fConst0 * double(fVslider29));
	double fSlow39 = 2.0 * (mydsp_faustpower2_f(fSlow38) + -1.0);
	double fSlow40 = 1.0 - fSlow38 * (fSlow37 - fSlow38);
	double fSlow41 = fSlow38 * (fSlow37 + fSlow38) + 1.0;
	double fSlow42 = 1.0 - fSlow34 * (fSlow33 - fSlow34);
	double fSlow43 = fSlow34 * (fSlow33 + fSlow34) + 1.0;
	double fSlow44 = 1.0 - fSlow30 * (fSlow29 - fSlow30);
	double fSlow45 = fSlow30 * (fSlow29 + fSlow30) + 1.0;
	double fSlow46 = 1.0 - fSlow26 * (fSlow25 - fSlow26);
	double fSlow47 = fSlow26 * (fSlow25 + fSlow26) + 1.0;
	double fSlow48 = 1.0 - fSlow22 * (fSlow21 - fSlow22);
	double fSlow49 = fSlow22 * (fSlow21 + fSlow22) + 1.0;
	double fSlow50 = 1.0 - fSlow18 * (fSlow17 - fSlow18);
	double fSlow51 = fSlow18 * (fSlow17 + fSlow18) + 1.0;
	double fSlow52 = 1.0 - fSlow14 * (fSlow13 - fSlow14);
	double fSlow53 = fSlow14 * (fSlow13 + fSlow14) + 1.0;
	double fSlow54 = 1.0 - fSlow10 * (fSlow9 - fSlow10);
	double fSlow55 = fSlow10 * (fSlow9 + fSlow10) + 1.0;
	double fSlow56 = 1.0 - fSlow6 * (fSlow5 - fSlow6);
	double fSlow57 = fSlow6 * (fSlow5 + fSlow6) + 1.0;
	double fSlow58 = 1.0 - fSlow2 * (fSlow1 - fSlow2);
	double fSlow59 = fSlow2 * (fSlow1 + fSlow2) + 1.0;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.999 * fRec0[1];
		double fTemp0 = fSlow1 / fRec0[0];
		double fTemp1 = fSlow2 * (fSlow2 + fTemp0) + 1.0;
		double fTemp2 = fSlow3 * fRec1[1];
		fRec2[0] = fSlow4 + 0.999 * fRec2[1];
		double fTemp3 = fSlow5 / fRec2[0];
		double fTemp4 = fSlow6 * (fSlow6 + fTemp3) + 1.0;
		double fTemp5 = fSlow7 * fRec3[1];
		fRec4[0] = fSlow8 + 0.999 * fRec4[1];
		double fTemp6 = fSlow9 / fRec4[0];
		double fTemp7 = fSlow10 * (fSlow10 + fTemp6) + 1.0;
		double fTemp8 = fSlow11 * fRec5[1];
		fRec6[0] = fSlow12 + 0.999 * fRec6[1];
		double fTemp9 = fSlow13 / fRec6[0];
		double fTemp10 = fSlow14 * (fSlow14 + fTemp9) + 1.0;
		double fTemp11 = fSlow15 * fRec7[1];
		fRec8[0] = fSlow16 + 0.999 * fRec8[1];
		double fTemp12 = fSlow17 / fRec8[0];
		double fTemp13 = fSlow18 * (fSlow18 + fTemp12) + 1.0;
		double fTemp14 = fSlow19 * fRec9[1];
		fRec10[0] = fSlow20 + 0.999 * fRec10[1];
		double fTemp15 = fSlow21 / fRec10[0];
		double fTemp16 = fSlow22 * (fSlow22 + fTemp15) + 1.0;
		double fTemp17 = fSlow23 * fRec11[1];
		fRec12[0] = fSlow24 + 0.999 * fRec12[1];
		double fTemp18 = fSlow25 / fRec12[0];
		double fTemp19 = fSlow26 * (fSlow26 + fTemp18) + 1.0;
		double fTemp20 = fSlow27 * fRec13[1];
		fRec14[0] = fSlow28 + 0.999 * fRec14[1];
		double fTemp21 = fSlow29 / fRec14[0];
		double fTemp22 = fSlow30 * (fSlow30 + fTemp21) + 1.0;
		double fTemp23 = fSlow31 * fRec15[1];
		fRec16[0] = fSlow32 + 0.999 * fRec16[1];
		double fTemp24 = fSlow33 / fRec16[0];
		double fTemp25 = fSlow34 * (fSlow34 + fTemp24) + 1.0;
		double fTemp26 = fSlow35 * fRec17[1];
		fRec18[0] = fSlow36 + 0.999 * fRec18[1];
		double fTemp27 = fSlow37 / fRec18[0];
		double fTemp28 = fSlow38 * (fSlow38 + fTemp27) + 1.0;
		double fTemp29 = fSlow39 * fRec19[1];
		fRec19[0] = double(input0[i0]) - ((fSlow38 * (fSlow38 - fTemp27) + 1.0) * fRec19[2] + fTemp29) / fTemp28;
		fRec17[0] = (fTemp29 + fSlow41 * fRec19[0] + fSlow40 * fRec19[2]) / fTemp28 - ((fSlow34 * (fSlow34 - fTemp24) + 1.0) * fRec17[2] + fTemp26) / fTemp25;
		fRec15[0] = (fTemp26 + fSlow43 * fRec17[0] + fSlow42 * fRec17[2]) / fTemp25 - ((fSlow30 * (fSlow30 - fTemp21) + 1.0) * fRec15[2] + fTemp23) / fTemp22;
		fRec13[0] = (fTemp23 + fSlow45 * fRec15[0] + fSlow44 * fRec15[2]) / fTemp22 - ((fSlow26 * (fSlow26 - fTemp18) + 1.0) * fRec13[2] + fTemp20) / fTemp19;
		fRec11[0] = (fTemp20 + fSlow47 * fRec13[0] + fSlow46 * fRec13[2]) / fTemp19 - ((fSlow22 * (fSlow22 - fTemp15) + 1.0) * fRec11[2] + fTemp17) / fTemp16;
		fRec9[0] = (fTemp17 + fSlow49 * fRec11[0] + fSlow48 * fRec11[2]) / fTemp16 - ((fSlow18 * (fSlow18 - fTemp12) + 1.0) * fRec9[2] + fTemp14) / fTemp13;
		fRec7[0] = (fTemp14 + fSlow51 * fRec9[0] + fSlow50 * fRec9[2]) / fTemp13 - ((fSlow14 * (fSlow14 - fTemp9) + 1.0) * fRec7[2] + fTemp11) / fTemp10;
		fRec5[0] = (fTemp11 + fSlow53 * fRec7[0] + fSlow52 * fRec7[2]) / fTemp10 - ((fSlow10 * (fSlow10 - fTemp6) + 1.0) * fRec5[2] + fTemp8) / fTemp7;
		fRec3[0] = (fTemp8 + fSlow55 * fRec5[0] + fSlow54 * fRec5[2]) / fTemp7 - ((fSlow6 * (fSlow6 - fTemp3) + 1.0) * fRec3[2] + fTemp5) / fTemp4;
		fRec1[0] = (fTemp5 + fSlow57 * fRec3[0] + fSlow56 * fRec3[2]) / fTemp4 - ((fSlow2 * (fSlow2 - fTemp0) + 1.0) * fRec1[2] + fTemp2) / fTemp1;
		output0[i0] = FAUSTFLOAT((fTemp2 + fSlow59 * fRec1[0] + fSlow58 * fRec1[2]) / fTemp1);
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fRec6[1] = fRec6[0];
		fRec8[1] = fRec8[0];
		fRec10[1] = fRec10[0];
		fRec12[1] = fRec12[0];
		fRec14[1] = fRec14[0];
		fRec16[1] = fRec16[0];
		fRec18[1] = fRec18[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("eqs.Qs125","","S",N_("bandwidth"),&fVslider22, 5e+01, 1.0, 1e+02, 1.0, 0);
	reg.registerFloatVar("eqs.Qs16k","","S","",&fVslider1, 5e+01, 1.0, 1e+02, 1.0, 0);
	reg.registerFloatVar("eqs.Qs1k","","S",N_("bandwidth"),&fVslider13, 5e+01, 1.0, 1e+02, 1.0, 0);
	reg.registerFloatVar("eqs.Qs250","","S",N_("bandwidth"),&fVslider19, 5e+01, 1.0, 1e+02, 1.0, 0);
	reg.registerFloatVar("eqs.Qs2k","","S",N_("bandwidth"),&fVslider10, 5e+01, 1.0, 1e+02, 1.0, 0);
	reg.registerFloatVar("eqs.Qs31_25","","S",N_("bandwidth"),&fVslider28, 5e+01, 1.0, 1e+02, 1.0, 0);
	reg.registerFloatVar("eqs.Qs4k","","S","",&fVslider7, 5e+01, 1.0, 1e+02, 1.0, 0);
	reg.registerFloatVar("eqs.Qs500","","S",N_("bandwidth"),&fVslider16, 5e+01, 1.0, 1e+02, 1.0, 0);
	reg.registerFloatVar("eqs.Qs62_5","","S",N_("bandwidth"),&fVslider25, 5e+01, 1.0, 1e+02, 1.0, 0);
	reg.registerFloatVar("eqs.Qs8k","","S","",&fVslider4, 5e+01, 1.0, 1e+02, 1.0, 0);
	reg.registerFloatVar("eqs.freq125","","S",N_("Hz"),&fVslider23, 125.0, 2e+01, 2e+04, 1.0, 0);
	reg.registerFloatVar("eqs.freq16k","","S",N_("Hz"),&fVslider2, 1.6e+04, 2e+01, 2e+04, 1.0, 0);
	reg.registerFloatVar("eqs.freq1k","","S",N_("Hz"),&fVslider14, 1e+03, 2e+01, 2e+04, 1.0, 0);
	reg.registerFloatVar("eqs.freq250","","S",N_("Hz"),&fVslider20, 2.5e+02, 2e+01, 2e+04, 1.0, 0);
	reg.registerFloatVar("eqs.freq2k","","S",N_("Hz"),&fVslider11, 2e+03, 2e+01, 2e+04, 1.0, 0);
	reg.registerFloatVar("eqs.freq31_25","","S",N_("Hz"),&fVslider29, 31.25, 2e+01, 2e+04, 1.0, 0);
	reg.registerFloatVar("eqs.freq4k","","S",N_("Hz"),&fVslider8, 4e+03, 2e+01, 2e+04, 1.0, 0);
	reg.registerFloatVar("eqs.freq500","","S",N_("Hz"),&fVslider17, 5e+02, 2e+01, 2e+04, 1.0, 0);
	reg.registerFloatVar("eqs.freq62_5","","S",N_("Hz"),&fVslider26, 62.5, 2e+01, 2e+04, 1.0, 0);
	reg.registerFloatVar("eqs.freq8k","","S",N_("Hz"),&fVslider5, 8e+03, 2e+01, 2e+04, 1.0, 0);
	reg.registerFloatVar("eqs.fs125","","S",N_("gain (dB) at 125 Hz"),&fVslider21, 0.0, -4e+01, 3e+01, 0.1, 0);
	reg.registerFloatVar("eqs.fs16k","","S",N_("gain (dB) at 16 kHz"),&fVslider0, 0.0, -4e+01, 3e+01, 0.1, 0);
	reg.registerFloatVar("eqs.fs1k","","S",N_("gain (dB) at 1 kHz"),&fVslider12, 0.0, -4e+01, 3e+01, 0.1, 0);
	reg.registerFloatVar("eqs.fs250","","S",N_("gain (dB) at 250 Hz"),&fVslider18, 0.0, -4e+01, 3e+01, 0.1, 0);
	reg.registerFloatVar("eqs.fs2k","","S",N_("gain (dB) at 2 kHz"),&fVslider9, 0.0, -4e+01, 3e+01, 0.1, 0);
	reg.registerFloatVar("eqs.fs31_25","","S",N_("gain (dB) at 31.25 Hz"),&fVslider27, 0.0, -4e+01, 3e+01, 0.1, 0);
	reg.registerFloatVar("eqs.fs4k","","S",N_("gain (dB) at 4 kHz"),&fVslider6, 0.0, -4e+01, 3e+01, 0.1, 0);
	reg.registerFloatVar("eqs.fs500","","S",N_("gain (dB) at 500 Hz"),&fVslider15, 0.0, -4e+01, 3e+01, 0.1, 0);
	reg.registerFloatVar("eqs.fs62_5","","S",N_("gain (dB) at 62.5 Hz"),&fVslider24, 0.0, -4e+01, 3e+01, 0.1, 0);
	reg.registerFloatVar("eqs.fs8k","","S",N_("gain (dB) at 8 kHz"),&fVslider3, 0.0, -4e+01, 3e+01, 0.1, 0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!-- Generated with glade 3.22.1 -->\n\
<interface>\n\
  <requires lib=\"gtk+\" version=\"3.20\"/>\n\
  <requires lib=\"gxwidgets\" version=\"0.0\"/>\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can_focus\">False</property>\n\
    <child>\n\
      <placeholder/>\n\
    </child>\n\
    <child>\n\
      <object class=\"GtkBox\" id=\"vbox1\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can_focus\">False</property>\n\
        <property name=\"orientation\">vertical</property>\n\
        <child>\n\
          <object class=\"GxPaintBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"margin_left\">4</property>\n\
            <property name=\"margin_right\">5</property>\n\
            <property name=\"paint_func\">box_uni_2_expose</property>\n\
            <child>\n\
              <object class=\"GtkGrid\" id=\"table1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"margin_left\">10</property>\n\
                <property name=\"margin_right\">10</property>\n\
                <property name=\"row_spacing\">10</property>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label1:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Q</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnob\" id=\"gxbigknob1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">eqs.Qs31_25</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">0</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label2:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Q</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnob\" id=\"gxbigknob2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">eqs.Qs62_5</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">1</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label3:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Q</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnob\" id=\"gxbigknob3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">eqs.Qs125</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">2</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox5\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label4:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Q</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnob\" id=\"gxbigknob4\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">eqs.Qs250</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">3</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox6\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label5:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Q</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnob\" id=\"gxbigknob5\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">eqs.Qs500</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">4</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox7\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label6:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Q</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnob\" id=\"gxbigknob6\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">eqs.Qs1k</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">5</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox8\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label7:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Q</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnob\" id=\"gxbigknob7\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">eqs.Qs2k</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">6</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox9\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label8:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Q</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnob\" id=\"gxbigknob8\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">eqs.Qs4k</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">7</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox10\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label9:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Q</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnob\" id=\"gxbigknob9\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">eqs.Qs8k</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">8</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox11\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label10:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Q</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnob\" id=\"gxbigknob10\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">eqs.Qs16k</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">9</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxVSlider\" id=\"gxvslider1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"hexpand\">True</property>\n\
                    <property name=\"var_id\">eqs.fs31_25</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">0</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxVSlider\" id=\"gxvslider2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"margin_left\">8</property>\n\
                    <property name=\"margin_right\">8</property>\n\
                    <property name=\"hexpand\">True</property>\n\
                    <property name=\"var_id\">eqs.fs62_5</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">1</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxVSlider\" id=\"gxvslider3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"hexpand\">True</property>\n\
                    <property name=\"var_id\">eqs.fs125</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">2</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxVSlider\" id=\"gxvslider4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"hexpand\">True</property>\n\
                    <property name=\"var_id\">eqs.fs250</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">3</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxVSlider\" id=\"gxvslider5\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"hexpand\">True</property>\n\
                    <property name=\"var_id\">eqs.fs500</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">4</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxVSlider\" id=\"gxvslider6\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"hexpand\">True</property>\n\
                    <property name=\"var_id\">eqs.fs1k</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">5</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxVSlider\" id=\"gxvslider7\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"hexpand\">True</property>\n\
                    <property name=\"var_id\">eqs.fs2k</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">6</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxVSlider\" id=\"gxvslider8\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"hexpand\">False</property>\n\
                    <property name=\"var_id\">eqs.fs4k</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">7</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxVSlider\" id=\"gxvslider9\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"hexpand\">True</property>\n\
                    <property name=\"var_id\">eqs.fs8k</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">8</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxVSlider\" id=\"gxvslider10\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"hexpand\">True</property>\n\
                    <property name=\"var_id\">eqs.fs16k</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">9</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.freq31_25</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">0</property>\n\
                    <property name=\"top_attach\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.freq62_5</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">1</property>\n\
                    <property name=\"top_attach\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.freq125</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">2</property>\n\
                    <property name=\"top_attach\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.freq250</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">3</property>\n\
                    <property name=\"top_attach\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay5\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.freq500</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">4</property>\n\
                    <property name=\"top_attach\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay6\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.freq1k</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">5</property>\n\
                    <property name=\"top_attach\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay7\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.freq2k</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">6</property>\n\
                    <property name=\"top_attach\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay8\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.freq4k</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">7</property>\n\
                    <property name=\"top_attach\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay9\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.freq8k</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">8</property>\n\
                    <property name=\"top_attach\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay10\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.freq16k</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">9</property>\n\
                    <property name=\"top_attach\">0</property>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">True</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">False</property>\n\
            <property name=\"fill\">False</property>\n\
            <property name=\"position\">0</property>\n\
          </packing>\n\
        </child>\n\
        <child>\n\
          <object class=\"GtkBox\" id=\"minibox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <placeholder/>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">True</property>\n\
            <property name=\"position\">1</property>\n\
          </packing>\n\
        </child>\n\
      </object>\n\
    </child>\n\
  </object>\n\
</interface>\n\
";

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade(glade_def);
        return 0;
    }
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("eqs" "." p)
// EQ
b.openHorizontalhideBox("");
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalTableBox("");
    {
	b.create_simple_spin_value("eqs.freq31_25");
	b.create_simple_spin_value("eqs.freq62_5");
	b.create_simple_spin_value("eqs.freq125");
	b.create_simple_spin_value("eqs.freq250");
	b.create_simple_spin_value("eqs.freq500");
	b.create_simple_spin_value("eqs.freq1k");
	b.create_simple_spin_value("eqs.freq2k");
	b.create_simple_spin_value("eqs.freq4k");
	b.create_simple_spin_value("eqs.freq8k");
	b.create_simple_spin_value("eqs.freq16k");
    }
    b.closeBox();
    b.openHorizontalTableBox("");
    {
	b.create_small_rackknob("eqs.fs31_25", "");
	b.create_small_rackknob("eqs.fs62_5", "");
	b.create_small_rackknob("eqs.fs125", "");
	b.create_small_rackknob("eqs.fs250", "");
	b.create_small_rackknob("eqs.fs500", "");
	b.create_small_rackknob("eqs.fs1k", "");
	b.create_small_rackknob("eqs.fs2k", "");
	b.create_small_rackknob("eqs.fs4k", "");
	b.create_small_rackknob("eqs.fs8k", "");
	b.create_small_rackknob("eqs.fs16k", "");
    }
    b.closeBox();
    b.openHorizontalTableBox("");
    {
	b.create_small_rackknob("eqs.Qs31_25", "Q");
	b.create_small_rackknob("eqs.Qs62_5", "Q");
	b.create_small_rackknob("eqs.Qs125", "Q");
	b.create_small_rackknob("eqs.Qs250", "Q");
	b.create_small_rackknob("eqs.Qs500", "Q");
	b.create_small_rackknob("eqs.Qs1k", "Q");
	b.create_small_rackknob("eqs.Qs2k", "Q");
	b.create_small_rackknob("eqs.Qs4k", "Q");
	b.create_small_rackknob("eqs.Qs8k", "Q");
	b.create_small_rackknob("eqs.Qs16k", "Q");
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

} // end namespace selecteq
