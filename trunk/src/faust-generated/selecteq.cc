// generated from file '../src/faust/selecteq.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace selecteq {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double fConst0;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT fVslider11;
	double fRec10[2];
	double fRec9[3];
	FAUSTFLOAT fVslider12;
	FAUSTFLOAT fVslider13;
	double fRec11[2];
	double fRec8[3];
	FAUSTFLOAT fVslider14;
	FAUSTFLOAT fVslider15;
	double fRec12[2];
	double fRec7[3];
	FAUSTFLOAT fVslider16;
	FAUSTFLOAT fVslider17;
	double fRec13[2];
	double fRec6[3];
	FAUSTFLOAT fVslider18;
	FAUSTFLOAT fVslider19;
	double fRec14[2];
	double fRec5[3];
	FAUSTFLOAT fVslider20;
	FAUSTFLOAT fVslider21;
	double fRec15[2];
	double fRec4[3];
	FAUSTFLOAT fVslider22;
	FAUSTFLOAT fVslider23;
	double fRec16[2];
	double fRec3[3];
	FAUSTFLOAT fVslider24;
	FAUSTFLOAT fVslider25;
	double fRec17[2];
	double fRec2[3];
	FAUSTFLOAT fVslider26;
	FAUSTFLOAT fVslider27;
	double fRec18[2];
	double fRec1[3];
	FAUSTFLOAT fVslider28;
	FAUSTFLOAT fVslider29;
	double fRec19[2];
	double fRec0[3];

	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec10[l0] = 0.0;
	for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) fRec9[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec11[l2] = 0.0;
	for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) fRec8[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec12[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec7[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec13[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRec6[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec14[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec5[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec15[l10] = 0.0;
	for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) fRec4[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec16[l12] = 0.0;
	for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) fRec3[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec17[l14] = 0.0;
	for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) fRec2[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec18[l16] = 0.0;
	for (int l17 = 0; (l17 < 3); l17 = (l17 + 1)) fRec1[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec19[l18] = 0.0;
	for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) fRec0[l19] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (3.1415926535897931 / std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq))));
	fVslider0 = FAUSTFLOAT(16000.0);
	fVslider1 = FAUSTFLOAT(8000.0);
	fVslider2 = FAUSTFLOAT(4000.0);
	fVslider3 = FAUSTFLOAT(2000.0);
	fVslider4 = FAUSTFLOAT(1000.0);
	fVslider5 = FAUSTFLOAT(500.0);
	fVslider6 = FAUSTFLOAT(250.0);
	fVslider7 = FAUSTFLOAT(125.0);
	fVslider8 = FAUSTFLOAT(62.5);
	fVslider9 = FAUSTFLOAT(31.25);
	fVslider10 = FAUSTFLOAT(50.0);
	fVslider11 = FAUSTFLOAT(0.0);
	fVslider12 = FAUSTFLOAT(50.0);
	fVslider13 = FAUSTFLOAT(0.0);
	fVslider14 = FAUSTFLOAT(50.0);
	fVslider15 = FAUSTFLOAT(0.0);
	fVslider16 = FAUSTFLOAT(50.0);
	fVslider17 = FAUSTFLOAT(0.0);
	fVslider18 = FAUSTFLOAT(50.0);
	fVslider19 = FAUSTFLOAT(0.0);
	fVslider20 = FAUSTFLOAT(50.0);
	fVslider21 = FAUSTFLOAT(0.0);
	fVslider22 = FAUSTFLOAT(50.0);
	fVslider23 = FAUSTFLOAT(0.0);
	fVslider24 = FAUSTFLOAT(50.0);
	fVslider25 = FAUSTFLOAT(0.0);
	fVslider26 = FAUSTFLOAT(50.0);
	fVslider27 = FAUSTFLOAT(0.0);
	fVslider28 = FAUSTFLOAT(50.0);
	fVslider29 = FAUSTFLOAT(0.0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = std::tan((fConst0 * double(fVslider0)));
	double fSlow1 = (2.0 * (mydsp_faustpower2_f(fSlow0) + -1.0));
	double fSlow2 = std::tan((fConst0 * double(fVslider1)));
	double fSlow3 = (2.0 * (mydsp_faustpower2_f(fSlow2) + -1.0));
	double fSlow4 = std::tan((fConst0 * double(fVslider2)));
	double fSlow5 = (2.0 * (mydsp_faustpower2_f(fSlow4) + -1.0));
	double fSlow6 = std::tan((fConst0 * double(fVslider3)));
	double fSlow7 = (2.0 * (mydsp_faustpower2_f(fSlow6) + -1.0));
	double fSlow8 = std::tan((fConst0 * double(fVslider4)));
	double fSlow9 = (2.0 * (mydsp_faustpower2_f(fSlow8) + -1.0));
	double fSlow10 = std::tan((fConst0 * double(fVslider5)));
	double fSlow11 = (2.0 * (mydsp_faustpower2_f(fSlow10) + -1.0));
	double fSlow12 = std::tan((fConst0 * double(fVslider6)));
	double fSlow13 = (2.0 * (mydsp_faustpower2_f(fSlow12) + -1.0));
	double fSlow14 = std::tan((fConst0 * double(fVslider7)));
	double fSlow15 = (2.0 * (mydsp_faustpower2_f(fSlow14) + -1.0));
	double fSlow16 = std::tan((fConst0 * double(fVslider8)));
	double fSlow17 = (2.0 * (mydsp_faustpower2_f(fSlow16) + -1.0));
	double fSlow18 = std::tan((fConst0 * double(fVslider9)));
	double fSlow19 = (2.0 * (mydsp_faustpower2_f(fSlow18) + -1.0));
	double fSlow20 = (1.0 / double(fVslider10));
	double fSlow21 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider11))));
	double fSlow22 = ((fSlow18 * (fSlow18 + fSlow20)) + 1.0);
	double fSlow23 = (1.0 - (fSlow18 * (fSlow20 - fSlow18)));
	double fSlow24 = (1.0 / double(fVslider12));
	double fSlow25 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider13))));
	double fSlow26 = ((fSlow16 * (fSlow16 + fSlow24)) + 1.0);
	double fSlow27 = (1.0 - (fSlow16 * (fSlow24 - fSlow16)));
	double fSlow28 = (1.0 / double(fVslider14));
	double fSlow29 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider15))));
	double fSlow30 = ((fSlow14 * (fSlow14 + fSlow28)) + 1.0);
	double fSlow31 = (1.0 - (fSlow14 * (fSlow28 - fSlow14)));
	double fSlow32 = (1.0 / double(fVslider16));
	double fSlow33 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider17))));
	double fSlow34 = ((fSlow12 * (fSlow12 + fSlow32)) + 1.0);
	double fSlow35 = (1.0 - (fSlow12 * (fSlow32 - fSlow12)));
	double fSlow36 = (1.0 / double(fVslider18));
	double fSlow37 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider19))));
	double fSlow38 = ((fSlow10 * (fSlow10 + fSlow36)) + 1.0);
	double fSlow39 = (1.0 - (fSlow10 * (fSlow36 - fSlow10)));
	double fSlow40 = (1.0 / double(fVslider20));
	double fSlow41 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider21))));
	double fSlow42 = ((fSlow8 * (fSlow8 + fSlow40)) + 1.0);
	double fSlow43 = (1.0 - (fSlow8 * (fSlow40 - fSlow8)));
	double fSlow44 = (1.0 / double(fVslider22));
	double fSlow45 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider23))));
	double fSlow46 = ((fSlow6 * (fSlow6 + fSlow44)) + 1.0);
	double fSlow47 = (1.0 - (fSlow6 * (fSlow44 - fSlow6)));
	double fSlow48 = (1.0 / double(fVslider24));
	double fSlow49 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider25))));
	double fSlow50 = ((fSlow4 * (fSlow4 + fSlow48)) + 1.0);
	double fSlow51 = (1.0 - (fSlow4 * (fSlow48 - fSlow4)));
	double fSlow52 = (1.0 / double(fVslider26));
	double fSlow53 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider27))));
	double fSlow54 = ((fSlow2 * (fSlow2 + fSlow52)) + 1.0);
	double fSlow55 = (1.0 - (fSlow2 * (fSlow52 - fSlow2)));
	double fSlow56 = (1.0 / double(fVslider28));
	double fSlow57 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider29))));
	double fSlow58 = ((fSlow0 * (fSlow0 + fSlow56)) + 1.0);
	double fSlow59 = (1.0 - (fSlow0 * (fSlow56 - fSlow0)));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec10[0] = (fSlow21 + (0.999 * fRec10[1]));
		double fTemp0 = (fSlow20 / fRec10[0]);
		double fTemp1 = (fSlow19 * fRec9[1]);
		double fTemp2 = ((fSlow18 * (fSlow18 + fTemp0)) + 1.0);
		fRec9[0] = (double(input0[i]) - ((((1.0 - (fSlow18 * (fTemp0 - fSlow18))) * fRec9[2]) + fTemp1) / fTemp2));
		fRec11[0] = (fSlow25 + (0.999 * fRec11[1]));
		double fTemp3 = (fSlow24 / fRec11[0]);
		double fTemp4 = (fSlow17 * fRec8[1]);
		double fTemp5 = ((fSlow16 * (fSlow16 + fTemp3)) + 1.0);
		fRec8[0] = ((((fTemp1 + (fSlow22 * fRec9[0])) + (fSlow23 * fRec9[2])) / fTemp2) - ((((1.0 - (fSlow16 * (fTemp3 - fSlow16))) * fRec8[2]) + fTemp4) / fTemp5));
		fRec12[0] = (fSlow29 + (0.999 * fRec12[1]));
		double fTemp6 = (fSlow28 / fRec12[0]);
		double fTemp7 = (fSlow15 * fRec7[1]);
		double fTemp8 = ((fSlow14 * (fSlow14 + fTemp6)) + 1.0);
		fRec7[0] = ((((fTemp4 + (fSlow26 * fRec8[0])) + (fSlow27 * fRec8[2])) / fTemp5) - ((((1.0 - (fSlow14 * (fTemp6 - fSlow14))) * fRec7[2]) + fTemp7) / fTemp8));
		fRec13[0] = (fSlow33 + (0.999 * fRec13[1]));
		double fTemp9 = (fSlow32 / fRec13[0]);
		double fTemp10 = (fSlow13 * fRec6[1]);
		double fTemp11 = ((fSlow12 * (fSlow12 + fTemp9)) + 1.0);
		fRec6[0] = ((((fTemp7 + (fSlow30 * fRec7[0])) + (fSlow31 * fRec7[2])) / fTemp8) - ((((1.0 - (fSlow12 * (fTemp9 - fSlow12))) * fRec6[2]) + fTemp10) / fTemp11));
		fRec14[0] = (fSlow37 + (0.999 * fRec14[1]));
		double fTemp12 = (fSlow36 / fRec14[0]);
		double fTemp13 = (fSlow11 * fRec5[1]);
		double fTemp14 = ((fSlow10 * (fSlow10 + fTemp12)) + 1.0);
		fRec5[0] = ((((fTemp10 + (fSlow34 * fRec6[0])) + (fSlow35 * fRec6[2])) / fTemp11) - ((((1.0 - (fSlow10 * (fTemp12 - fSlow10))) * fRec5[2]) + fTemp13) / fTemp14));
		fRec15[0] = (fSlow41 + (0.999 * fRec15[1]));
		double fTemp15 = (fSlow40 / fRec15[0]);
		double fTemp16 = (fSlow9 * fRec4[1]);
		double fTemp17 = ((fSlow8 * (fSlow8 + fTemp15)) + 1.0);
		fRec4[0] = ((((fTemp13 + (fSlow38 * fRec5[0])) + (fSlow39 * fRec5[2])) / fTemp14) - ((((1.0 - (fSlow8 * (fTemp15 - fSlow8))) * fRec4[2]) + fTemp16) / fTemp17));
		fRec16[0] = (fSlow45 + (0.999 * fRec16[1]));
		double fTemp18 = (fSlow44 / fRec16[0]);
		double fTemp19 = (fSlow7 * fRec3[1]);
		double fTemp20 = ((fSlow6 * (fSlow6 + fTemp18)) + 1.0);
		fRec3[0] = ((((fTemp16 + (fSlow42 * fRec4[0])) + (fSlow43 * fRec4[2])) / fTemp17) - ((((1.0 - (fSlow6 * (fTemp18 - fSlow6))) * fRec3[2]) + fTemp19) / fTemp20));
		fRec17[0] = (fSlow49 + (0.999 * fRec17[1]));
		double fTemp21 = (fSlow48 / fRec17[0]);
		double fTemp22 = (fSlow5 * fRec2[1]);
		double fTemp23 = ((fSlow4 * (fSlow4 + fTemp21)) + 1.0);
		fRec2[0] = ((((fTemp19 + (fSlow46 * fRec3[0])) + (fSlow47 * fRec3[2])) / fTemp20) - ((((1.0 - (fSlow4 * (fTemp21 - fSlow4))) * fRec2[2]) + fTemp22) / fTemp23));
		fRec18[0] = (fSlow53 + (0.999 * fRec18[1]));
		double fTemp24 = (fSlow52 / fRec18[0]);
		double fTemp25 = (fSlow3 * fRec1[1]);
		double fTemp26 = ((fSlow2 * (fSlow2 + fTemp24)) + 1.0);
		fRec1[0] = ((((fTemp22 + (fSlow50 * fRec2[0])) + (fSlow51 * fRec2[2])) / fTemp23) - ((((1.0 - (fSlow2 * (fTemp24 - fSlow2))) * fRec1[2]) + fTemp25) / fTemp26));
		fRec19[0] = (fSlow57 + (0.999 * fRec19[1]));
		double fTemp27 = (fSlow56 / fRec19[0]);
		double fTemp28 = (fSlow1 * fRec0[1]);
		double fTemp29 = ((fSlow0 * (fSlow0 + fTemp27)) + 1.0);
		fRec0[0] = ((((fTemp25 + (fSlow54 * fRec1[0])) + (fSlow55 * fRec1[2])) / fTemp26) - ((((1.0 - (fSlow0 * (fTemp27 - fSlow0))) * fRec0[2]) + fTemp28) / fTemp29));
		output0[i] = FAUSTFLOAT((((fTemp28 + (fSlow58 * fRec0[0])) + (fSlow59 * fRec0[2])) / fTemp29));
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec11[1] = fRec11[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec12[1] = fRec12[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec13[1] = fRec13[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec14[1] = fRec14[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec15[1] = fRec15[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec16[1] = fRec16[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec17[1] = fRec17[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec18[1] = fRec18[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec19[1] = fRec19[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("eqs.Qs125","","S",N_("bandwidth"),&fVslider14, 50.0, 1.0, 100.0, 1.0);
	reg.registerVar("eqs.Qs16k","","S","",&fVslider28, 50.0, 1.0, 100.0, 1.0);
	reg.registerVar("eqs.Qs1k","","S",N_("bandwidth"),&fVslider20, 50.0, 1.0, 100.0, 1.0);
	reg.registerVar("eqs.Qs250","","S",N_("bandwidth"),&fVslider16, 50.0, 1.0, 100.0, 1.0);
	reg.registerVar("eqs.Qs2k","","S",N_("bandwidth"),&fVslider22, 50.0, 1.0, 100.0, 1.0);
	reg.registerVar("eqs.Qs31_25","","S",N_("bandwidth"),&fVslider10, 50.0, 1.0, 100.0, 1.0);
	reg.registerVar("eqs.Qs4k","","S","",&fVslider24, 50.0, 1.0, 100.0, 1.0);
	reg.registerVar("eqs.Qs500","","S",N_("bandwidth"),&fVslider18, 50.0, 1.0, 100.0, 1.0);
	reg.registerVar("eqs.Qs62_5","","S",N_("bandwidth"),&fVslider12, 50.0, 1.0, 100.0, 1.0);
	reg.registerVar("eqs.Qs8k","","S","",&fVslider26, 50.0, 1.0, 100.0, 1.0);
	reg.registerVar("eqs.freq125","","S",N_("Hz"),&fVslider7, 125.0, 20.0, 20000.0, 1.0);
	reg.registerVar("eqs.freq16k","","S",N_("Hz"),&fVslider0, 16000.0, 20.0, 20000.0, 1.0);
	reg.registerVar("eqs.freq1k","","S",N_("Hz"),&fVslider4, 1000.0, 20.0, 20000.0, 1.0);
	reg.registerVar("eqs.freq250","","S",N_("Hz"),&fVslider6, 250.0, 20.0, 20000.0, 1.0);
	reg.registerVar("eqs.freq2k","","S",N_("Hz"),&fVslider3, 2000.0, 20.0, 20000.0, 1.0);
	reg.registerVar("eqs.freq31_25","","S",N_("Hz"),&fVslider9, 31.25, 20.0, 20000.0, 1.0);
	reg.registerVar("eqs.freq4k","","S",N_("Hz"),&fVslider2, 4000.0, 20.0, 20000.0, 1.0);
	reg.registerVar("eqs.freq500","","S",N_("Hz"),&fVslider5, 500.0, 20.0, 20000.0, 1.0);
	reg.registerVar("eqs.freq62_5","","S",N_("Hz"),&fVslider8, 62.5, 20.0, 20000.0, 1.0);
	reg.registerVar("eqs.freq8k","","S",N_("Hz"),&fVslider1, 8000.0, 20.0, 20000.0, 1.0);
	reg.registerVar("eqs.fs125","","S",N_("gain (dB) at 125 Hz"),&fVslider15, 0.0, -40.0, 30.0, 0.10000000000000001);
	reg.registerVar("eqs.fs16k","","S",N_("gain (dB) at 16 kHz"),&fVslider29, 0.0, -40.0, 30.0, 0.10000000000000001);
	reg.registerVar("eqs.fs1k","","S",N_("gain (dB) at 1 kHz"),&fVslider21, 0.0, -40.0, 30.0, 0.10000000000000001);
	reg.registerVar("eqs.fs250","","S",N_("gain (dB) at 250 Hz"),&fVslider17, 0.0, -40.0, 30.0, 0.10000000000000001);
	reg.registerVar("eqs.fs2k","","S",N_("gain (dB) at 2 kHz"),&fVslider23, 0.0, -40.0, 30.0, 0.10000000000000001);
	reg.registerVar("eqs.fs31_25","","S",N_("gain (dB) at 31.25 Hz"),&fVslider11, 0.0, -40.0, 30.0, 0.10000000000000001);
	reg.registerVar("eqs.fs4k","","S",N_("gain (dB) at 4 kHz"),&fVslider25, 0.0, -40.0, 30.0, 0.10000000000000001);
	reg.registerVar("eqs.fs500","","S",N_("gain (dB) at 500 Hz"),&fVslider19, 0.0, -40.0, 30.0, 0.10000000000000001);
	reg.registerVar("eqs.fs62_5","","S",N_("gain (dB) at 62.5 Hz"),&fVslider13, 0.0, -40.0, 30.0, 0.10000000000000001);
	reg.registerVar("eqs.fs8k","","S",N_("gain (dB) at 8 kHz"),&fVslider27, 0.0, -40.0, 30.0, 0.10000000000000001);
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
            <property name=\"spacing\">4</property>\n\
            <property name=\"paint_func\">box_uni_2_expose</property>\n\
            <child>\n\
              <object class=\"GtkGrid\" id=\"table1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"row_spacing\">10</property>\n\
                <property name=\"column_spacing\">3</property>\n\
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
            <property name=\"expand\">True</property>\n\
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
	b.create_eq_rackslider_no_caption("eqs.fs31_25");
	b.create_eq_rackslider_no_caption("eqs.fs62_5");
	b.create_eq_rackslider_no_caption("eqs.fs125");
	b.create_eq_rackslider_no_caption("eqs.fs250");
	b.create_eq_rackslider_no_caption("eqs.fs500");
	b.create_eq_rackslider_no_caption("eqs.fs1k");
	b.create_eq_rackslider_no_caption("eqs.fs2k");
	b.create_eq_rackslider_no_caption("eqs.fs4k");
	b.create_eq_rackslider_no_caption("eqs.fs8k");
	b.create_eq_rackslider_no_caption("eqs.fs16k");
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
