// generated from file '../src/faust/panoram_enhancer.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace panoram_enhancer {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	double fConst3;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	int IOTA0;
	double fVec0[131072];
	double fVec1[131072];
	double fRec1[3];
	double fRec0[3];
	double fConst10;
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst20;
	double fConst22;
	double fConst24;
	double fConst25;
	double fConst27;
	double fConst28;
	double fConst30;
	FAUSTFLOAT fHslider0;
	double fRec8[2];
	double fConst31;
	double fRec7[3];
	double fConst32;
	double fRec6[3];
	double fConst33;
	double fRec5[3];
	double fConst34;
	double fRec4[3];
	double fRec3[3];
	double fRec2[3];
	FAUSTFLOAT fHslider1;
	double fConst37;
	double fConst39;
	double fConst41;
	double fConst42;
	double fConst44;
	double fConst45;
	double fConst47;
	double fConst48;
	double fConst49;
	double fRec14[3];
	double fConst50;
	double fRec13[3];
	double fConst51;
	double fRec12[3];
	double fConst52;
	double fRec11[3];
	double fRec10[3];
	double fRec9[3];
	double fConst53;
	double fConst55;
	double fConst56;
	double fConst58;
	double fConst59;
	double fConst61;
	double fRec20[3];
	double fConst62;
	double fRec19[3];
	double fConst63;
	double fRec18[3];
	double fConst64;
	double fRec17[3];
	double fRec16[3];
	double fRec15[3];
	double fConst65;
	double fConst66;
	double fRec26[3];
	double fRec25[3];
	double fRec24[3];
	double fRec23[3];
	double fRec22[3];
	double fRec21[3];
	double fRec32[3];
	double fRec31[3];
	double fRec30[3];
	double fRec29[3];
	double fRec28[3];
	double fRec27[3];
	double fConst67;
	double fRec38[3];
	double fRec37[3];
	double fRec36[3];
	double fRec35[3];
	double fRec34[3];
	double fRec33[3];

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
	id = "panoram_enhancer";
	name = N_("Panoram Enhancer");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Misc");       // category
	shortname = N_("Panoram");     // shortname
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
	for (int l0 = 0; l0 < 131072; l0 = l0 + 1) fVec0[l0] = 0.0;
	for (int l1 = 0; l1 < 131072; l1 = l1 + 1) fVec1[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRec1[l2] = 0.0;
	for (int l3 = 0; l3 < 3; l3 = l3 + 1) fRec0[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec8[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec7[l5] = 0.0;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec6[l6] = 0.0;
	for (int l7 = 0; l7 < 3; l7 = l7 + 1) fRec5[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec4[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec3[l9] = 0.0;
	for (int l10 = 0; l10 < 3; l10 = l10 + 1) fRec2[l10] = 0.0;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec14[l11] = 0.0;
	for (int l12 = 0; l12 < 3; l12 = l12 + 1) fRec13[l12] = 0.0;
	for (int l13 = 0; l13 < 3; l13 = l13 + 1) fRec12[l13] = 0.0;
	for (int l14 = 0; l14 < 3; l14 = l14 + 1) fRec11[l14] = 0.0;
	for (int l15 = 0; l15 < 3; l15 = l15 + 1) fRec10[l15] = 0.0;
	for (int l16 = 0; l16 < 3; l16 = l16 + 1) fRec9[l16] = 0.0;
	for (int l17 = 0; l17 < 3; l17 = l17 + 1) fRec20[l17] = 0.0;
	for (int l18 = 0; l18 < 3; l18 = l18 + 1) fRec19[l18] = 0.0;
	for (int l19 = 0; l19 < 3; l19 = l19 + 1) fRec18[l19] = 0.0;
	for (int l20 = 0; l20 < 3; l20 = l20 + 1) fRec17[l20] = 0.0;
	for (int l21 = 0; l21 < 3; l21 = l21 + 1) fRec16[l21] = 0.0;
	for (int l22 = 0; l22 < 3; l22 = l22 + 1) fRec15[l22] = 0.0;
	for (int l23 = 0; l23 < 3; l23 = l23 + 1) fRec26[l23] = 0.0;
	for (int l24 = 0; l24 < 3; l24 = l24 + 1) fRec25[l24] = 0.0;
	for (int l25 = 0; l25 < 3; l25 = l25 + 1) fRec24[l25] = 0.0;
	for (int l26 = 0; l26 < 3; l26 = l26 + 1) fRec23[l26] = 0.0;
	for (int l27 = 0; l27 < 3; l27 = l27 + 1) fRec22[l27] = 0.0;
	for (int l28 = 0; l28 < 3; l28 = l28 + 1) fRec21[l28] = 0.0;
	for (int l29 = 0; l29 < 3; l29 = l29 + 1) fRec32[l29] = 0.0;
	for (int l30 = 0; l30 < 3; l30 = l30 + 1) fRec31[l30] = 0.0;
	for (int l31 = 0; l31 < 3; l31 = l31 + 1) fRec30[l31] = 0.0;
	for (int l32 = 0; l32 < 3; l32 = l32 + 1) fRec29[l32] = 0.0;
	for (int l33 = 0; l33 < 3; l33 = l33 + 1) fRec28[l33] = 0.0;
	for (int l34 = 0; l34 < 3; l34 = l34 + 1) fRec27[l34] = 0.0;
	for (int l35 = 0; l35 < 3; l35 = l35 + 1) fRec38[l35] = 0.0;
	for (int l36 = 0; l36 < 3; l36 = l36 + 1) fRec37[l36] = 0.0;
	for (int l37 = 0; l37 < 3; l37 = l37 + 1) fRec36[l37] = 0.0;
	for (int l38 = 0; l38 < 3; l38 = l38 + 1) fRec35[l38] = 0.0;
	for (int l39 = 0; l39 < 3; l39 = l39 + 1) fRec34[l39] = 0.0;
	for (int l40 = 0; l40 < 3; l40 = l40 + 1) fRec33[l40] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = std::tan(5654.8667764616275 / fConst0);
	double fConst2 = mydsp_faustpower2_f(fConst1);
	fConst3 = 2.0 * (1.0 - 1.0 / fConst2);
	double fConst4 = 1.0 / fConst1;
	fConst5 = (fConst4 + -0.7653668647301795) / fConst1 + 1.0;
	fConst6 = 1.0 / ((fConst4 + 0.7653668647301795) / fConst1 + 1.0);
	fConst7 = (fConst4 + -1.8477590650225735) / fConst1 + 1.0;
	fConst8 = 1.0 / ((fConst4 + 1.8477590650225735) / fConst1 + 1.0);
	double fConst9 = std::tan(62831.853071795864 / fConst0);
	fConst10 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst9));
	double fConst11 = 1.0 / fConst9;
	fConst12 = (fConst11 + -0.5176380902050413) / fConst9 + 1.0;
	fConst13 = 1.0 / ((fConst11 + 0.5176380902050413) / fConst9 + 1.0);
	fConst14 = (fConst11 + -1.414213562373095) / fConst9 + 1.0;
	fConst15 = 1.0 / ((fConst11 + 1.414213562373095) / fConst9 + 1.0);
	fConst16 = (fConst11 + -1.9318516525781364) / fConst9 + 1.0;
	fConst17 = 1.0 / ((fConst11 + 1.9318516525781364) / fConst9 + 1.0);
	double fConst18 = std::tan(20106.192982974677 / fConst0);
	double fConst19 = mydsp_faustpower2_f(fConst18);
	fConst20 = 2.0 * (1.0 - 1.0 / fConst19);
	double fConst21 = 1.0 / fConst18;
	fConst22 = (fConst21 + -0.5176380902050413) / fConst18 + 1.0;
	double fConst23 = (fConst21 + 0.5176380902050413) / fConst18 + 1.0;
	fConst24 = 1.0 / fConst23;
	fConst25 = (fConst21 + -1.414213562373095) / fConst18 + 1.0;
	double fConst26 = (fConst21 + 1.414213562373095) / fConst18 + 1.0;
	fConst27 = 1.0 / fConst26;
	fConst28 = (fConst21 + -1.9318516525781364) / fConst18 + 1.0;
	double fConst29 = (fConst21 + 1.9318516525781364) / fConst18 + 1.0;
	fConst30 = 1.0 / fConst29;
	fConst31 = 0.13999999999999999 * fConst0;
	fConst32 = 1.0 / (fConst19 * fConst29);
	fConst33 = 1.0 / (fConst19 * fConst26);
	fConst34 = 1.0 / (fConst19 * fConst23);
	double fConst35 = std::tan(11309.733552923255 / fConst0);
	double fConst36 = mydsp_faustpower2_f(fConst35);
	fConst37 = 2.0 * (1.0 - 1.0 / fConst36);
	double fConst38 = 1.0 / fConst35;
	fConst39 = (fConst38 + -0.5176380902050413) / fConst35 + 1.0;
	double fConst40 = (fConst38 + 0.5176380902050413) / fConst35 + 1.0;
	fConst41 = 1.0 / fConst40;
	fConst42 = (fConst38 + -1.414213562373095) / fConst35 + 1.0;
	double fConst43 = (fConst38 + 1.414213562373095) / fConst35 + 1.0;
	fConst44 = 1.0 / fConst43;
	fConst45 = (fConst38 + -1.9318516525781364) / fConst35 + 1.0;
	double fConst46 = (fConst38 + 1.9318516525781364) / fConst35 + 1.0;
	fConst47 = 1.0 / fConst46;
	fConst48 = 0.2 * fConst0;
	fConst49 = std::sqrt(fConst48 + 0.3);
	fConst50 = 1.0 / (fConst36 * fConst46);
	fConst51 = 1.0 / (fConst36 * fConst43);
	fConst52 = 1.0 / (fConst36 * fConst40);
	fConst53 = (fConst4 + -0.5176380902050413) / fConst1 + 1.0;
	double fConst54 = (fConst4 + 0.5176380902050413) / fConst1 + 1.0;
	fConst55 = 1.0 / fConst54;
	fConst56 = (fConst4 + -1.414213562373095) / fConst1 + 1.0;
	double fConst57 = (fConst4 + 1.414213562373095) / fConst1 + 1.0;
	fConst58 = 1.0 / fConst57;
	fConst59 = (fConst4 + -1.9318516525781364) / fConst1 + 1.0;
	double fConst60 = (fConst4 + 1.9318516525781364) / fConst1 + 1.0;
	fConst61 = 1.0 / fConst60;
	fConst62 = 1.0 / (fConst2 * fConst60);
	fConst63 = 1.0 / (fConst2 * fConst57);
	fConst64 = 1.0 / (fConst2 * fConst54);
	fConst65 = 3.141592653589793 / fConst0;
	fConst66 = std::cos(0.246 * fConst0);
	fConst67 = std::log10(fConst48 + 9.0);
	IOTA0 = 0;
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	double fSlow0 = 0.0010000000000000009 * double(fHslider0);
	double fSlow1 = double(fHslider1);
	double fSlow2 = 0.4 * std::sin(3.14 * fSlow1) + 0.6;
	double fSlow3 = fConst13 * fSlow2;
	double fSlow4 = 0.27999999999999997 * fSlow1 + 0.6;
	double fSlow5 = fConst24 * fSlow4;
	double fSlow6 = fConst41 * (0.4 * std::cos(1.23 * fSlow1) + 0.6);
	double fSlow7 = 1.5e+03 * fSlow1;
	double fSlow8 = std::tan(fConst65 * (3.6e+03 - fSlow7));
	double fSlow9 = mydsp_faustpower2_f(fSlow8);
	double fSlow10 = 2.0 * (1.0 - 1.0 / fSlow9);
	double fSlow11 = 1.0 / fSlow8;
	double fSlow12 = (fSlow11 + -0.5176380902050413) / fSlow8 + 1.0;
	double fSlow13 = (fSlow11 + 0.5176380902050413) / fSlow8 + 1.0;
	double fSlow14 = 1.0 / fSlow13;
	double fSlow15 = (fSlow11 + -1.414213562373095) / fSlow8 + 1.0;
	double fSlow16 = (fSlow11 + 1.414213562373095) / fSlow8 + 1.0;
	double fSlow17 = 1.0 / fSlow16;
	double fSlow18 = (fSlow11 + -1.9318516525781364) / fSlow8 + 1.0;
	double fSlow19 = (fSlow11 + 1.9318516525781364) / fSlow8 + 1.0;
	double fSlow20 = 1.0 / fSlow19;
	double fSlow21 = std::tan(fConst65 * (1.8e+03 - fSlow7));
	double fSlow22 = mydsp_faustpower2_f(fSlow21);
	double fSlow23 = 2.0 * (1.0 - 1.0 / fSlow22);
	double fSlow24 = 1.0 / fSlow21;
	double fSlow25 = (fSlow24 + -0.5176380902050413) / fSlow21 + 1.0;
	double fSlow26 = (fSlow24 + 0.5176380902050413) / fSlow21 + 1.0;
	double fSlow27 = 1.0 / fSlow26;
	double fSlow28 = (fSlow24 + -1.414213562373095) / fSlow21 + 1.0;
	double fSlow29 = (fSlow24 + 1.414213562373095) / fSlow21 + 1.0;
	double fSlow30 = 1.0 / fSlow29;
	double fSlow31 = (fSlow24 + -1.9318516525781364) / fSlow21 + 1.0;
	double fSlow32 = (fSlow24 + 1.9318516525781364) / fSlow21 + 1.0;
	double fSlow33 = 1.0 / fSlow32;
	double fSlow34 = 1.0 / (fSlow22 * fSlow32);
	double fSlow35 = 1.0 / (fSlow22 * fSlow29);
	double fSlow36 = 1.0 / (fSlow22 * fSlow26);
	double fSlow37 = (0.4 * std::sqrt(fSlow1 + 0.3) + 0.6) / fSlow13;
	double fSlow38 = std::tan(fConst65 * (6.4e+03 - fSlow7));
	double fSlow39 = mydsp_faustpower2_f(fSlow38);
	double fSlow40 = 2.0 * (1.0 - 1.0 / fSlow39);
	double fSlow41 = 1.0 / fSlow38;
	double fSlow42 = (fSlow41 + -0.5176380902050413) / fSlow38 + 1.0;
	double fSlow43 = (fSlow41 + 0.5176380902050413) / fSlow38 + 1.0;
	double fSlow44 = 1.0 / fSlow43;
	double fSlow45 = (fSlow41 + -1.414213562373095) / fSlow38 + 1.0;
	double fSlow46 = (fSlow41 + 1.414213562373095) / fSlow38 + 1.0;
	double fSlow47 = 1.0 / fSlow46;
	double fSlow48 = (fSlow41 + -1.9318516525781364) / fSlow38 + 1.0;
	double fSlow49 = (fSlow41 + 1.9318516525781364) / fSlow38 + 1.0;
	double fSlow50 = 1.0 / fSlow49;
	double fSlow51 = 1.0 / (fSlow9 * fSlow19);
	double fSlow52 = 1.0 / (fSlow9 * fSlow16);
	double fSlow53 = 1.0 / (fSlow9 * fSlow13);
	double fSlow54 = fSlow2 / fSlow43;
	double fSlow55 = std::tan(fConst65 * (2e+04 - fSlow7));
	double fSlow56 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fSlow55));
	double fSlow57 = 1.0 / fSlow55;
	double fSlow58 = (fSlow57 + -0.5176380902050413) / fSlow55 + 1.0;
	double fSlow59 = (fSlow57 + 0.5176380902050413) / fSlow55 + 1.0;
	double fSlow60 = 1.0 / fSlow59;
	double fSlow61 = (fSlow57 + -1.414213562373095) / fSlow55 + 1.0;
	double fSlow62 = 1.0 / ((fSlow57 + 1.414213562373095) / fSlow55 + 1.0);
	double fSlow63 = (fSlow57 + -1.9318516525781364) / fSlow55 + 1.0;
	double fSlow64 = 1.0 / ((fSlow57 + 1.9318516525781364) / fSlow55 + 1.0);
	double fSlow65 = 1.0 / (fSlow39 * fSlow49);
	double fSlow66 = 1.0 / (fSlow39 * fSlow46);
	double fSlow67 = 1.0 / (fSlow39 * fSlow43);
	double fSlow68 = fSlow4 / fSlow59;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input1[i0]);
		fVec0[IOTA0 & 131071] = fTemp0;
		double fTemp1 = double(input0[i0]);
		fVec1[IOTA0 & 131071] = fTemp1;
		fRec1[0] = 0.5 * (fTemp1 + fTemp0) - fConst8 * (fConst7 * fRec1[2] + fConst3 * fRec1[1]);
		fRec0[0] = fConst8 * (fRec1[2] + fRec1[0] + 2.0 * fRec1[1]) - fConst6 * (fConst5 * fRec0[2] + fConst3 * fRec0[1]);
		double fTemp2 = fConst6 * (fRec0[2] + fRec0[0] + 2.0 * fRec0[1]);
		fRec8[0] = fSlow0 + 0.999 * fRec8[1];
		double fTemp3 = fConst31 * fRec8[0];
		int iTemp4 = int(fTemp3);
		double fTemp5 = std::floor(fTemp3);
		fRec7[0] = fVec1[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp4))) & 131071] * (fTemp5 + (1.0 - fTemp3)) + (fTemp3 - fTemp5) * fVec1[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp4 + 1))) & 131071] - fConst30 * (fConst28 * fRec7[2] + fConst20 * fRec7[1]);
		fRec6[0] = fConst32 * (fRec7[2] + (fRec7[0] - 2.0 * fRec7[1])) - fConst27 * (fConst25 * fRec6[2] + fConst20 * fRec6[1]);
		fRec5[0] = fConst33 * (fRec6[2] + (fRec6[0] - 2.0 * fRec6[1])) - fConst24 * (fConst22 * fRec5[2] + fConst20 * fRec5[1]);
		fRec4[0] = fConst34 * (fRec5[2] + (fRec5[0] - 2.0 * fRec5[1])) - fConst17 * (fConst16 * fRec4[2] + fConst10 * fRec4[1]);
		fRec3[0] = fConst17 * (fRec4[2] + fRec4[0] + 2.0 * fRec4[1]) - fConst15 * (fConst14 * fRec3[2] + fConst10 * fRec3[1]);
		fRec2[0] = fConst15 * (fRec3[2] + fRec3[0] + 2.0 * fRec3[1]) - fConst13 * (fConst12 * fRec2[2] + fConst10 * fRec2[1]);
		double fTemp6 = fConst49 * fRec8[0];
		int iTemp7 = int(fTemp6);
		double fTemp8 = std::floor(fTemp6);
		fRec14[0] = fVec1[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp7))) & 131071] * (fTemp8 + (1.0 - fTemp6)) + (fTemp6 - fTemp8) * fVec1[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp7 + 1))) & 131071] - fConst47 * (fConst45 * fRec14[2] + fConst37 * fRec14[1]);
		fRec13[0] = fConst50 * (fRec14[2] + (fRec14[0] - 2.0 * fRec14[1])) - fConst44 * (fConst42 * fRec13[2] + fConst37 * fRec13[1]);
		fRec12[0] = fConst51 * (fRec13[2] + (fRec13[0] - 2.0 * fRec13[1])) - fConst41 * (fConst39 * fRec12[2] + fConst37 * fRec12[1]);
		fRec11[0] = fConst52 * (fRec12[2] + (fRec12[0] - 2.0 * fRec12[1])) - fConst30 * (fConst28 * fRec11[2] + fConst20 * fRec11[1]);
		fRec10[0] = fConst30 * (fRec11[2] + fRec11[0] + 2.0 * fRec11[1]) - fConst27 * (fConst25 * fRec10[2] + fConst20 * fRec10[1]);
		fRec9[0] = fConst27 * (fRec10[2] + fRec10[0] + 2.0 * fRec10[1]) - fConst24 * (fConst22 * fRec9[2] + fConst20 * fRec9[1]);
		double fTemp9 = fConst48 * fRec8[0];
		int iTemp10 = int(fTemp9);
		int iTemp11 = std::min<int>(65537, std::max<int>(0, iTemp10 + 1));
		double fTemp12 = std::floor(fTemp9);
		double fTemp13 = fTemp9 - fTemp12;
		double fTemp14 = fTemp12 + (1.0 - fTemp9);
		int iTemp15 = std::min<int>(65537, std::max<int>(0, iTemp10));
		fRec20[0] = fVec1[(IOTA0 - iTemp15) & 131071] * fTemp14 + fTemp13 * fVec1[(IOTA0 - iTemp11) & 131071] - fConst61 * (fConst59 * fRec20[2] + fConst3 * fRec20[1]);
		fRec19[0] = fConst62 * (fRec20[2] + (fRec20[0] - 2.0 * fRec20[1])) - fConst58 * (fConst56 * fRec19[2] + fConst3 * fRec19[1]);
		fRec18[0] = fConst63 * (fRec19[2] + (fRec19[0] - 2.0 * fRec19[1])) - fConst55 * (fConst53 * fRec18[2] + fConst3 * fRec18[1]);
		fRec17[0] = fConst64 * (fRec18[2] + (fRec18[0] - 2.0 * fRec18[1])) - fConst47 * (fConst45 * fRec17[2] + fConst37 * fRec17[1]);
		fRec16[0] = fConst47 * (fRec17[2] + fRec17[0] + 2.0 * fRec17[1]) - fConst44 * (fConst42 * fRec16[2] + fConst37 * fRec16[1]);
		fRec15[0] = fConst44 * (fRec16[2] + fRec16[0] + 2.0 * fRec16[1]) - fConst41 * (fConst39 * fRec15[2] + fConst37 * fRec15[1]);
		output0[i0] = FAUSTFLOAT(fSlow6 * (fRec15[2] + fRec15[0] + 2.0 * fRec15[1]) + fSlow5 * (fRec9[2] + fRec9[0] + 2.0 * fRec9[1]) + fSlow3 * (fRec2[2] + fRec2[0] + 2.0 * fRec2[1]) + fTemp2);
		double fTemp16 = fConst66 * fRec8[0];
		int iTemp17 = int(fTemp16);
		double fTemp18 = std::floor(fTemp16);
		fRec26[0] = fVec0[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp17))) & 131071] * (fTemp18 + (1.0 - fTemp16)) + (fTemp16 - fTemp18) * fVec0[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp17 + 1))) & 131071] - fSlow33 * (fSlow31 * fRec26[2] + fSlow23 * fRec26[1]);
		fRec25[0] = fSlow34 * (fRec26[2] + (fRec26[0] - 2.0 * fRec26[1])) - fSlow30 * (fSlow28 * fRec25[2] + fSlow23 * fRec25[1]);
		fRec24[0] = fSlow35 * (fRec25[2] + (fRec25[0] - 2.0 * fRec25[1])) - fSlow27 * (fSlow25 * fRec24[2] + fSlow23 * fRec24[1]);
		fRec23[0] = fSlow36 * (fRec24[2] + (fRec24[0] - 2.0 * fRec24[1])) - fSlow20 * (fSlow18 * fRec23[2] + fSlow10 * fRec23[1]);
		fRec22[0] = fSlow20 * (fRec23[2] + fRec23[0] + 2.0 * fRec23[1]) - fSlow17 * (fSlow15 * fRec22[2] + fSlow10 * fRec22[1]);
		fRec21[0] = fSlow17 * (fRec22[2] + fRec22[0] + 2.0 * fRec22[1]) - fSlow14 * (fSlow12 * fRec21[2] + fSlow10 * fRec21[1]);
		fRec32[0] = fVec0[(IOTA0 - iTemp15) & 131071] * fTemp14 + fTemp13 * fVec0[(IOTA0 - iTemp11) & 131071] - fSlow20 * (fSlow18 * fRec32[2] + fSlow10 * fRec32[1]);
		fRec31[0] = fSlow51 * (fRec32[2] + (fRec32[0] - 2.0 * fRec32[1])) - fSlow17 * (fSlow15 * fRec31[2] + fSlow10 * fRec31[1]);
		fRec30[0] = fSlow52 * (fRec31[2] + (fRec31[0] - 2.0 * fRec31[1])) - fSlow14 * (fSlow12 * fRec30[2] + fSlow10 * fRec30[1]);
		fRec29[0] = fSlow53 * (fRec30[2] + (fRec30[0] - 2.0 * fRec30[1])) - fSlow50 * (fSlow48 * fRec29[2] + fSlow40 * fRec29[1]);
		fRec28[0] = fSlow50 * (fRec29[2] + fRec29[0] + 2.0 * fRec29[1]) - fSlow47 * (fSlow45 * fRec28[2] + fSlow40 * fRec28[1]);
		fRec27[0] = fSlow47 * (fRec28[2] + fRec28[0] + 2.0 * fRec28[1]) - fSlow44 * (fSlow42 * fRec27[2] + fSlow40 * fRec27[1]);
		double fTemp19 = fConst67 * fRec8[0];
		int iTemp20 = int(fTemp19);
		double fTemp21 = std::floor(fTemp19);
		fRec38[0] = fVec0[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp20))) & 131071] * (fTemp21 + (1.0 - fTemp19)) + (fTemp19 - fTemp21) * fVec0[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp20 + 1))) & 131071] - fSlow50 * (fSlow48 * fRec38[2] + fSlow40 * fRec38[1]);
		fRec37[0] = fSlow65 * (fRec38[2] + (fRec38[0] - 2.0 * fRec38[1])) - fSlow47 * (fSlow45 * fRec37[2] + fSlow40 * fRec37[1]);
		fRec36[0] = fSlow66 * (fRec37[2] + (fRec37[0] - 2.0 * fRec37[1])) - fSlow44 * (fSlow42 * fRec36[2] + fSlow40 * fRec36[1]);
		fRec35[0] = fSlow67 * (fRec36[2] + (fRec36[0] - 2.0 * fRec36[1])) - fSlow64 * (fSlow63 * fRec35[2] + fSlow56 * fRec35[1]);
		fRec34[0] = fSlow64 * (fRec35[2] + fRec35[0] + 2.0 * fRec35[1]) - fSlow62 * (fSlow61 * fRec34[2] + fSlow56 * fRec34[1]);
		fRec33[0] = fSlow62 * (fRec34[2] + fRec34[0] + 2.0 * fRec34[1]) - fSlow60 * (fSlow58 * fRec33[2] + fSlow56 * fRec33[1]);
		output1[i0] = FAUSTFLOAT(fSlow68 * (fRec33[2] + fRec33[0] + 2.0 * fRec33[1]) + fSlow54 * (fRec27[2] + fRec27[0] + 2.0 * fRec27[1]) + fTemp2 + fSlow37 * (fRec21[2] + fRec21[0] + 2.0 * fRec21[1]));
		IOTA0 = IOTA0 + 1;
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fRec18[2] = fRec18[1];
		fRec18[1] = fRec18[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fRec23[2] = fRec23[1];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fRec29[2] = fRec29[1];
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		fRec35[2] = fRec35[1];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("panoram_enhancer.Delay width",N_("Delay"),"S",N_("Delay Width"),&fHslider0, 0.0, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("panoram_enhancer.Frequency width",N_("Frequency"),"S",N_("Frequency Width"),&fHslider1, 0.0, 0.0, 1.0, 0.01, 0);
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
                <property name=\"spacing\">10</property>\n\
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
                      <object class=\"GxMidKnob\" id=\"gxbigknob1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">panoram_enhancer.Delay width</property>\n\
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
                    <property name=\"fill\">False</property>\n\
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
                        <property name=\"var_id\">panoram_enhancer.Frequency width</property>\n\
                        <property name=\"label_ref\">label2:rack_label</property>\n\
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
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"pack_type\">end</property>\n\
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
                <property name=\"var_id\">panoram_enhancer.Delay width</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Level</property>\n\
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
#define PARAM(p) ("panoram_enhancer" "." p)
// ----- panoram enhancer
b.openHorizontalhideBox("");
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalTableBox("");
    {
	b.create_small_rackknob(PARAM("Delay width"), _("  delay width  "));
	b.create_small_rackknob(PARAM("Frequency width"), _("  freq width   "));
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

} // end namespace panoram_enhancer
