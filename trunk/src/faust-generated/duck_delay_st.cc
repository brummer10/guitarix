// generated from file '../src/faust/duck_delay_st.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace duck_delay_st {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	int IOTA0;
	double fVec0[524288];
	double fConst10;
	FAUSTFLOAT fHslider2;
	double fConst11;
	double fRec6[2];
	double fConst12;
	double fRec5[2];
	double fRec3[2];
	double fVec1[524288];
	double fRec7[2];
	double fRec4[2];
	double fConst13;
	double fConst15;
	double fConst16;
	double fRec2[2];
	double fRec1[3];
	double fConst17;
	double fRec0[3];
	FAUSTFLOAT fHslider3;
	double fRec10[2];
	double fRec9[3];
	double fRec8[3];
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst29;
	double fRec13[2];
	double fRec12[3];
	double fRec11[3];
	double fConst30;
	double fRec16[2];
	double fRec15[3];
	double fConst31;
	double fRec14[3];
	FAUSTFLOAT fHslider4;
	double fRec17[2];
	FAUSTFLOAT fHslider5;
	double fConst32;
	FAUSTFLOAT fHslider6;
	double fRec20[2];
	double fRec19[2];
	FAUSTFLOAT fHslider7;
	double fRec18[2];
	double fRec23[2];
	double fRec22[3];
	double fRec21[3];
	double fRec26[2];
	double fRec25[3];
	double fRec24[3];
	double fRec29[2];
	double fRec28[3];
	double fRec27[3];
	double fRec32[2];
	double fRec31[3];
	double fRec30[3];
	double fRec35[2];
	double fRec34[2];
	double fRec33[2];

	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int sample_rate, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef*);
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
	id = "duckDelaySt";
	name = N_("Duck Delay St");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Echo / Delay");       // category
	shortname = "";     // shortname
	mono_audio = 0;
	stereo_audio = compute_static;
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
	for (int l0 = 0; l0 < 524288; l0 = l0 + 1) fVec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec6[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec5[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec3[l3] = 0.0;
	for (int l4 = 0; l4 < 524288; l4 = l4 + 1) fVec1[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec7[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec4[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec2[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec1[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec0[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec10[l10] = 0.0;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec9[l11] = 0.0;
	for (int l12 = 0; l12 < 3; l12 = l12 + 1) fRec8[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec13[l13] = 0.0;
	for (int l14 = 0; l14 < 3; l14 = l14 + 1) fRec12[l14] = 0.0;
	for (int l15 = 0; l15 < 3; l15 = l15 + 1) fRec11[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec16[l16] = 0.0;
	for (int l17 = 0; l17 < 3; l17 = l17 + 1) fRec15[l17] = 0.0;
	for (int l18 = 0; l18 < 3; l18 = l18 + 1) fRec14[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec17[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec20[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec19[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec18[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec23[l23] = 0.0;
	for (int l24 = 0; l24 < 3; l24 = l24 + 1) fRec22[l24] = 0.0;
	for (int l25 = 0; l25 < 3; l25 = l25 + 1) fRec21[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec26[l26] = 0.0;
	for (int l27 = 0; l27 < 3; l27 = l27 + 1) fRec25[l27] = 0.0;
	for (int l28 = 0; l28 < 3; l28 = l28 + 1) fRec24[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec29[l29] = 0.0;
	for (int l30 = 0; l30 < 3; l30 = l30 + 1) fRec28[l30] = 0.0;
	for (int l31 = 0; l31 < 3; l31 = l31 + 1) fRec27[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fRec32[l32] = 0.0;
	for (int l33 = 0; l33 < 3; l33 = l33 + 1) fRec31[l33] = 0.0;
	for (int l34 = 0; l34 < 3; l34 = l34 + 1) fRec30[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec35[l35] = 0.0;
	for (int l36 = 0; l36 < 2; l36 = l36 + 1) fRec34[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec33[l37] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = std::tan(2764.601535159018 / fConst0);
	double fConst2 = mydsp_faustpower2_f(fConst1);
	fConst3 = 1.0 / fConst2;
	fConst4 = 2.0 * (1.0 - fConst3);
	fConst5 = 1.0 / fConst1;
	fConst6 = (fConst5 + -0.6180339887498947) / fConst1 + 1.0;
	fConst7 = 1.0 / ((fConst5 + 0.6180339887498947) / fConst1 + 1.0);
	fConst8 = (fConst5 + -1.6180339887498947) / fConst1 + 1.0;
	fConst9 = 1.0 / ((fConst5 + 1.6180339887498947) / fConst1 + 1.0);
	fConst10 = std::exp(0.0 - 1e+01 / fConst0);
	fConst11 = 1.0 - fConst10;
	fConst12 = 0.001 * fConst0;
	fConst13 = 1.0 - fConst5;
	double fConst14 = fConst5 + 1.0;
	fConst15 = 1.0 / fConst14;
	fConst16 = 0.0 - 1.0 / (fConst1 * fConst14);
	fConst17 = 0.0 - 2.0 / fConst2;
	double fConst18 = std::tan(1382.300767579509 / fConst0);
	double fConst19 = mydsp_faustpower2_f(fConst18);
	fConst20 = 1.0 / fConst19;
	fConst21 = 2.0 * (1.0 - fConst20);
	fConst22 = 1.0 / fConst18;
	fConst23 = (fConst22 + -0.6180339887498947) / fConst18 + 1.0;
	fConst24 = 1.0 / ((fConst22 + 0.6180339887498947) / fConst18 + 1.0);
	fConst25 = (fConst22 + -1.6180339887498947) / fConst18 + 1.0;
	fConst26 = 1.0 / ((fConst22 + 1.6180339887498947) / fConst18 + 1.0);
	fConst27 = 1.0 - fConst22;
	double fConst28 = fConst22 + 1.0;
	fConst29 = 1.0 / fConst28;
	fConst30 = 0.0 - 1.0 / (fConst18 * fConst28);
	fConst31 = 0.0 - 2.0 / fConst19;
	fConst32 = 1.0 / fConst0;
	IOTA0 = 0;
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	double fSlow0 = double(fHslider0);
	double fSlow1 = 1.0 - fSlow0;
	double fSlow2 = double(fHslider1);
	double fSlow3 = fConst11 * double(fHslider2);
	double fSlow4 = 1.0 - fSlow0 * fSlow2;
	double fSlow5 = double(fHslider3);
	double fSlow6 = std::pow(1e+01, 0.6 * fSlow5);
	double fSlow7 = std::pow(1e+01, 0.6 * (1.0 - fSlow5));
	double fSlow8 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fHslider4));
	double fSlow9 = double(fHslider5);
	int iSlow10 = std::fabs(fSlow9) < 2.220446049250313e-16;
	double fSlow11 = ((iSlow10) ? 0.0 : std::exp(0.0 - fConst32 / ((iSlow10) ? 1.0 : fSlow9)));
	double fSlow12 = 1.0 - fSlow11;
	double fSlow13 = double(fHslider6);
	int iSlow14 = std::fabs(fSlow13) < 2.220446049250313e-16;
	double fSlow15 = ((iSlow14) ? 0.0 : std::exp(0.0 - fConst32 / ((iSlow14) ? 1.0 : fSlow13)));
	double fSlow16 = 1.0 - fSlow15;
	double fSlow17 = std::pow(1e+01, 0.05 * double(fHslider7));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		double fTemp1 = fTemp0 + fSlow2 * (fSlow1 * fRec5[1] + fSlow0 * fRec4[1]);
		fVec0[IOTA0 & 524287] = fTemp1;
		fRec6[0] = fSlow3 + fConst10 * fRec6[1];
		double fTemp2 = fConst12 * fRec6[0];
		int iTemp3 = int(fTemp2);
		int iTemp4 = std::min<int>(393217, std::max<int>(0, iTemp3 + 1));
		double fTemp5 = std::floor(fTemp2);
		double fTemp6 = fTemp2 - fTemp5;
		double fTemp7 = fTemp5 + (1.0 - fTemp2);
		int iTemp8 = std::min<int>(393217, std::max<int>(0, iTemp3));
		fRec5[0] = fVec0[(IOTA0 - iTemp8) & 524287] * fTemp7 + fTemp6 * fVec0[(IOTA0 - iTemp4) & 524287];
		fRec3[0] = fRec5[0];
		double fTemp9 = double(input1[i0]);
		double fTemp10 = fSlow4 * fTemp9 + fSlow2 * (fSlow1 * fRec7[1] + fSlow0 * fRec3[1]);
		fVec1[IOTA0 & 524287] = fTemp10;
		fRec7[0] = fTemp7 * fVec1[(IOTA0 - iTemp8) & 524287] + fTemp6 * fVec1[(IOTA0 - iTemp4) & 524287];
		fRec4[0] = fRec7[0];
		fRec2[0] = fConst16 * fRec3[1] - fConst15 * (fConst13 * fRec2[1] - fConst5 * fRec3[0]);
		fRec1[0] = fRec2[0] - fConst9 * (fConst8 * fRec1[2] + fConst4 * fRec1[1]);
		fRec0[0] = fConst9 * (fConst3 * fRec1[0] + fConst17 * fRec1[1] + fConst3 * fRec1[2]) - fConst7 * (fConst6 * fRec0[2] + fConst4 * fRec0[1]);
		double fTemp11 = fRec3[0] + fRec3[1];
		fRec10[0] = 0.0 - fConst15 * (fConst13 * fRec10[1] - fTemp11);
		fRec9[0] = fRec10[0] - fConst9 * (fConst8 * fRec9[2] + fConst4 * fRec9[1]);
		fRec8[0] = fConst9 * (fRec9[2] + fRec9[0] + 2.0 * fRec9[1]) - fConst7 * (fConst6 * fRec8[2] + fConst4 * fRec8[1]);
		fRec13[0] = 0.0 - fConst29 * (fConst27 * fRec13[1] - fTemp11);
		fRec12[0] = fRec13[0] - fConst26 * (fConst25 * fRec12[2] + fConst21 * fRec12[1]);
		fRec11[0] = fConst26 * (fRec12[2] + fRec12[0] + 2.0 * fRec12[1]) - fConst24 * (fConst23 * fRec11[2] + fConst21 * fRec11[1]);
		fRec16[0] = fConst30 * fRec3[1] - fConst29 * (fConst27 * fRec16[1] - fConst22 * fRec3[0]);
		fRec15[0] = fRec16[0] - fConst26 * (fConst25 * fRec15[2] + fConst21 * fRec15[1]);
		fRec14[0] = fConst26 * (fConst20 * fRec15[0] + fConst31 * fRec15[1] + fConst20 * fRec15[2]) - fConst24 * (fConst23 * fRec14[2] + fConst21 * fRec14[1]);
		fRec17[0] = fSlow8 + 0.999 * fRec17[1];
		double fTemp12 = std::fabs(fTemp0);
		fRec20[0] = std::max<double>(fTemp12, fRec20[1] * fSlow15 + fTemp12 * fSlow16);
		fRec19[0] = fRec20[0] * fSlow12 + fSlow11 * fRec19[1];
		fRec18[0] = fConst11 * double(1 - ((fSlow17 * fRec19[0]) > 1.0)) + fConst10 * fRec18[1];
		output0[i0] = FAUSTFLOAT(fTemp0 + 0.1778279410038923 * fRec18[0] * fRec17[0] * (fConst24 * (fConst20 * fRec14[0] + fConst31 * fRec14[1] + fConst20 * fRec14[2] + fSlow7 * (fRec11[2] + fRec11[0] + 2.0 * fRec11[1])) + fConst7 * (fRec8[2] + fRec8[0] + 2.0 * fRec8[1] + fSlow6 * (fConst3 * fRec0[0] + fConst17 * fRec0[1] + fConst3 * fRec0[2]))));
		fRec23[0] = fConst16 * fRec4[1] - fConst15 * (fConst13 * fRec23[1] - fConst5 * fRec4[0]);
		fRec22[0] = fRec23[0] - fConst9 * (fConst8 * fRec22[2] + fConst4 * fRec22[1]);
		fRec21[0] = fConst9 * (fConst3 * fRec22[0] + fConst17 * fRec22[1] + fConst3 * fRec22[2]) - fConst7 * (fConst6 * fRec21[2] + fConst4 * fRec21[1]);
		double fTemp13 = fRec4[0] + fRec4[1];
		fRec26[0] = 0.0 - fConst15 * (fConst13 * fRec26[1] - fTemp13);
		fRec25[0] = fRec26[0] - fConst9 * (fConst8 * fRec25[2] + fConst4 * fRec25[1]);
		fRec24[0] = fConst9 * (fRec25[2] + fRec25[0] + 2.0 * fRec25[1]) - fConst7 * (fConst6 * fRec24[2] + fConst4 * fRec24[1]);
		fRec29[0] = 0.0 - fConst29 * (fConst27 * fRec29[1] - fTemp13);
		fRec28[0] = fRec29[0] - fConst26 * (fConst25 * fRec28[2] + fConst21 * fRec28[1]);
		fRec27[0] = fConst26 * (fRec28[2] + fRec28[0] + 2.0 * fRec28[1]) - fConst24 * (fConst23 * fRec27[2] + fConst21 * fRec27[1]);
		fRec32[0] = fConst30 * fRec4[1] - fConst29 * (fConst27 * fRec32[1] - fConst22 * fRec4[0]);
		fRec31[0] = fRec32[0] - fConst26 * (fConst25 * fRec31[2] + fConst21 * fRec31[1]);
		fRec30[0] = fConst26 * (fConst20 * fRec31[0] + fConst31 * fRec31[1] + fConst20 * fRec31[2]) - fConst24 * (fConst23 * fRec30[2] + fConst21 * fRec30[1]);
		double fTemp14 = std::fabs(fTemp9);
		fRec35[0] = std::max<double>(fTemp14, fSlow15 * fRec35[1] + fTemp14 * fSlow16);
		fRec34[0] = fRec35[0] * fSlow12 + fSlow11 * fRec34[1];
		fRec33[0] = fConst11 * double(1 - ((fSlow17 * fRec34[0]) > 1.0)) + fConst10 * fRec33[1];
		output1[i0] = FAUSTFLOAT(fTemp9 + 0.1778279410038923 * fRec17[0] * fRec33[0] * (fConst24 * (fConst20 * fRec30[0] + fConst31 * fRec30[1] + fConst20 * fRec30[2] + fSlow7 * (fRec27[2] + fRec27[0] + 2.0 * fRec27[1])) + fConst7 * (fRec24[2] + fRec24[0] + 2.0 * fRec24[1] + fSlow6 * (fConst3 * fRec21[0] + fConst17 * fRec21[1] + fConst3 * fRec21[2]))));
		IOTA0 = IOTA0 + 1;
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec3[1] = fRec3[0];
		fRec7[1] = fRec7[0];
		fRec4[1] = fRec4[0];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec13[1] = fRec13[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fRec16[1] = fRec16[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fRec17[1] = fRec17[0];
		fRec20[1] = fRec20[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		fRec26[1] = fRec26[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fRec35[1] = fRec35[0];
		fRec34[1] = fRec34[0];
		fRec33[1] = fRec33[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("duckDelaySt.amount",N_("Amount"),"S","",&fHslider7, 0.5, 0.0, 56.0, 0.05, 0);
	reg.registerFloatVar("duckDelaySt.attack",N_("Attack"),"S","",&fHslider5, 0.1, 0.05, 0.5, 0.05, 0);
	reg.registerFloatVar("duckDelaySt.coloration",N_("Coloration"),"S","",&fHslider3, 0.0, -1.0, 1.0, 0.05, 0);
	reg.registerFloatVar("duckDelaySt.effect",N_("Effect"),"S","",&fHslider4, 0.0, -16.0, 4.0, 0.1, 0);
	reg.registerFloatVar("duckDelaySt.feedback",N_("Feedback"),"S","",&fHslider1, 0.0, 0.0, 1.0, 0.05, 0);
	reg.registerFloatVar("duckDelaySt.pingpong",N_("Ping Pong"),"S","",&fHslider0, 0.0, 0.0, 1.0, 0.05, 0);
	reg.registerFloatVar("duckDelaySt.release",N_("Release"),"S","",&fHslider6, 0.1, 0.05, 2.0, 0.05, 0);
	reg.registerFloatVar("duckDelaySt.time",N_("Delay"),"S","",&fHslider2, 5e+02, 1.0, 2e+03, 1.0, 0);
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
          <object class=\"GtkBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GtkBox\" id=\"hbox1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label1:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxBigKnob\" id=\"gxbigknob1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">duckDelaySt.time</property>\n\
                        <property name=\"label_ref\">label1:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label2:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">duckDelaySt.feedback</property>\n\
                        <property name=\"label_ref\">label2:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob6\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">duckDelaySt.attack</property>\n\
                        <property name=\"label_ref\">label2:rack_label_inverse</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">2</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label2:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">3</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label3:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">duckDelaySt.pingpong</property>\n\
                        <property name=\"label_ref\">label3:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob7\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">duckDelaySt.release</property>\n\
                        <property name=\"label_ref\">label3:rack_label_inverse</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">2</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label3:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">3</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox5\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label4:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob4\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">duckDelaySt.coloration</property>\n\
                        <property name=\"label_ref\">label4:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob8\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">duckDelaySt.amount</property>\n\
                        <property name=\"label_ref\">label4:rack_label_inverse</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">2</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label4:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">3</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">3</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox6\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label5:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxBigKnob\" id=\"gxbigknob5\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">duckDelaySt.effect</property>\n\
                        <property name=\"label_ref\">label5:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">4</property>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">False</property>\n\
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
              <object class=\"GxHSlider\" id=\"gxhslider1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">True</property>\n\
                <property name=\"receives_default\">True</property>\n\
                <property name=\"round_digits\">0</property>\n\
                <property name=\"var_id\">duckDelaySt.amount</property>\n\
                <property name=\"show_value\">False</property>\n\
                <property name=\"value_position\">right</property>\n\
                <property name=\"value_xalign\">0.52000000000000002</property>\n\
                <property name=\"label_ref\">label0:rack_label</property>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">False</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
            <child>\n\
              <object class=\"GtkLabel\" id=\"label0:rack_label\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"label\" translatable=\"yes\">Amount</property>\n\
                <property name=\"xalign\">0</property>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">False</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"position\">1</property>\n\
              </packing>\n\
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
#define PARAM(p) ("duckDelaySt" "." p)
// ducking delay stereo

b.openHorizontalhideBox("");
b.create_master_slider(PARAM("effect"), _("effect"));
b.closeBox();


b.openHorizontalBox("");
b.openVerticalBox("");
b.openHorizontalBox("");
{
	b.create_small_rackknob(PARAM("time"),         _(" time ms "));
	b.create_small_rackknob(PARAM("feedback"),     _(" feedback "));
	b.create_small_rackknob(PARAM("pingpong"),     _(" ping-pong"));
	b.create_small_rackknob(PARAM("coloration"),   _("coloration"));	
}
b.closeBox();
b.openHorizontalBox("");
{
	b.create_small_rackknob(PARAM("attack"),        _(" attack "));
	b.create_small_rackknob(PARAM("release"),       _(" release "));
	b.create_small_rackknob(PARAM("amount"),        _(" amount "));
	b.create_small_rackknobr(PARAM("effect"),       _(" effect "));
}
b.closeBox();
b.closeBox();
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

} // end namespace duck_delay_st
