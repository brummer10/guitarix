// generated from file '../src/faust/panoram_enhancer.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace panoram_enhancer {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fHslider0;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	int IOTA;
	double fVec0[131072];
	double fConst13;
	FAUSTFLOAT fHslider1;
	double fRec6[2];
	double fConst14;
	double fConst15;
	double fRec5[3];
	double fConst16;
	double fConst17;
	double fRec4[3];
	double fConst18;
	double fRec3[3];
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	double fRec2[3];
	double fConst23;
	double fRec1[3];
	double fConst24;
	double fRec0[3];
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fRec12[3];
	double fConst31;
	double fRec11[3];
	double fRec10[3];
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fRec9[3];
	double fConst36;
	double fRec8[3];
	double fConst37;
	double fRec7[3];
	double fConst38;
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fRec18[3];
	double fConst44;
	double fRec17[3];
	double fRec16[3];
	double fConst45;
	double fConst46;
	double fRec15[3];
	double fConst47;
	double fRec14[3];
	double fConst48;
	double fRec13[3];
	double fConst49;
	double fConst50;
	double fVec1[131072];
	double fConst51;
	double fRec20[3];
	double fConst52;
	double fRec19[3];
	double fConst53;
	double fConst54;
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
	double fConst55;
	double fRec38[3];
	double fRec37[3];
	double fRec36[3];
	double fRec35[3];
	double fRec34[3];
	double fRec33[3];

	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
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
	for (int l0 = 0; (l0 < 131072); l0 = (l0 + 1)) fVec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec6[l1] = 0.0;
	for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) fRec5[l2] = 0.0;
	for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) fRec4[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec3[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec2[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec1[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRec0[l7] = 0.0;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec12[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec11[l9] = 0.0;
	for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) fRec10[l10] = 0.0;
	for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) fRec9[l11] = 0.0;
	for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) fRec8[l12] = 0.0;
	for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) fRec7[l13] = 0.0;
	for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) fRec18[l14] = 0.0;
	for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) fRec17[l15] = 0.0;
	for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) fRec16[l16] = 0.0;
	for (int l17 = 0; (l17 < 3); l17 = (l17 + 1)) fRec15[l17] = 0.0;
	for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) fRec14[l18] = 0.0;
	for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) fRec13[l19] = 0.0;
	for (int l20 = 0; (l20 < 131072); l20 = (l20 + 1)) fVec1[l20] = 0.0;
	for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) fRec20[l21] = 0.0;
	for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) fRec19[l22] = 0.0;
	for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) fRec26[l23] = 0.0;
	for (int l24 = 0; (l24 < 3); l24 = (l24 + 1)) fRec25[l24] = 0.0;
	for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) fRec24[l25] = 0.0;
	for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) fRec23[l26] = 0.0;
	for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) fRec22[l27] = 0.0;
	for (int l28 = 0; (l28 < 3); l28 = (l28 + 1)) fRec21[l28] = 0.0;
	for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) fRec32[l29] = 0.0;
	for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) fRec31[l30] = 0.0;
	for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) fRec30[l31] = 0.0;
	for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) fRec29[l32] = 0.0;
	for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) fRec28[l33] = 0.0;
	for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) fRec27[l34] = 0.0;
	for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) fRec38[l35] = 0.0;
	for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) fRec37[l36] = 0.0;
	for (int l37 = 0; (l37 < 3); l37 = (l37 + 1)) fRec36[l37] = 0.0;
	for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) fRec35[l38] = 0.0;
	for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) fRec34[l39] = 0.0;
	for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) fRec33[l40] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = std::tan((11309.733552923255 / fConst0));
	fConst2 = (1.0 / fConst1);
	fConst3 = (1.0 / (((fConst2 + 0.51763809020504126) / fConst1) + 1.0));
	fConst4 = (1.0 / (((fConst2 + 1.4142135623730949) / fConst1) + 1.0));
	fConst5 = (1.0 / (((fConst2 + 1.9318516525781364) / fConst1) + 1.0));
	fConst6 = std::tan((5654.8667764616275 / fConst0));
	fConst7 = (1.0 / fConst6);
	fConst8 = (1.0 / (((fConst7 + 0.51763809020504126) / fConst6) + 1.0));
	fConst9 = mydsp_faustpower2_f(fConst6);
	fConst10 = (1.0 / fConst9);
	fConst11 = (1.0 / (((fConst7 + 1.4142135623730949) / fConst6) + 1.0));
	fConst12 = (1.0 / (((fConst7 + 1.9318516525781364) / fConst6) + 1.0));
	fConst13 = (0.20000000000000001 * fConst0);
	fConst14 = (((fConst7 + -1.9318516525781364) / fConst6) + 1.0);
	fConst15 = (2.0 * (1.0 - fConst10));
	fConst16 = (0.0 - (2.0 / fConst9));
	fConst17 = (((fConst7 + -1.4142135623730949) / fConst6) + 1.0);
	fConst18 = (((fConst7 + -0.51763809020504126) / fConst6) + 1.0);
	fConst19 = (((fConst2 + -1.9318516525781364) / fConst1) + 1.0);
	fConst20 = mydsp_faustpower2_f(fConst1);
	fConst21 = (1.0 / fConst20);
	fConst22 = (2.0 * (1.0 - fConst21));
	fConst23 = (((fConst2 + -1.4142135623730949) / fConst1) + 1.0);
	fConst24 = (((fConst2 + -0.51763809020504126) / fConst1) + 1.0);
	fConst25 = std::tan((20106.192982974677 / fConst0));
	fConst26 = (1.0 / fConst25);
	fConst27 = (1.0 / (((fConst26 + 0.51763809020504126) / fConst25) + 1.0));
	fConst28 = (1.0 / (((fConst26 + 1.4142135623730949) / fConst25) + 1.0));
	fConst29 = (1.0 / (((fConst26 + 1.9318516525781364) / fConst25) + 1.0));
	fConst30 = std::sqrt((fConst13 + 0.29999999999999999));
	fConst31 = (0.0 - (2.0 / fConst20));
	fConst32 = (((fConst26 + -1.9318516525781364) / fConst25) + 1.0);
	fConst33 = mydsp_faustpower2_f(fConst25);
	fConst34 = (1.0 / fConst33);
	fConst35 = (2.0 * (1.0 - fConst34));
	fConst36 = (((fConst26 + -1.4142135623730949) / fConst25) + 1.0);
	fConst37 = (((fConst26 + -0.51763809020504126) / fConst25) + 1.0);
	fConst38 = std::tan((62831.853071795864 / fConst0));
	fConst39 = (1.0 / fConst38);
	fConst40 = (1.0 / (((fConst39 + 0.51763809020504126) / fConst38) + 1.0));
	fConst41 = (1.0 / (((fConst39 + 1.4142135623730949) / fConst38) + 1.0));
	fConst42 = (1.0 / (((fConst39 + 1.9318516525781364) / fConst38) + 1.0));
	fConst43 = (0.13999999999999999 * fConst0);
	fConst44 = (0.0 - (2.0 / fConst33));
	fConst45 = (((fConst39 + -1.9318516525781364) / fConst38) + 1.0);
	fConst46 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst38))));
	fConst47 = (((fConst39 + -1.4142135623730949) / fConst38) + 1.0);
	fConst48 = (((fConst39 + -0.51763809020504126) / fConst38) + 1.0);
	fConst49 = (1.0 / (((fConst7 + 0.76536686473017945) / fConst6) + 1.0));
	fConst50 = (1.0 / (((fConst7 + 1.8477590650225735) / fConst6) + 1.0));
	fConst51 = (((fConst7 + -1.8477590650225735) / fConst6) + 1.0);
	fConst52 = (((fConst7 + -0.76536686473017945) / fConst6) + 1.0);
	fConst53 = (3.1415926535897931 / fConst0);
	fConst54 = std::log10((fConst13 + 9.0));
	fConst55 = std::cos((0.246 * fConst0));
	fHslider0 = FAUSTFLOAT(0.0);
	fHslider1 = FAUSTFLOAT(0.0);
			IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	double fSlow0 = double(fHslider0);
	double fSlow1 = (fConst3 * ((0.40000000000000002 * std::cos((1.23 * fSlow0))) + 0.59999999999999998));
	double fSlow2 = (0.0010000000000000009 * double(fHslider1));
	double fSlow3 = ((0.27999999999999997 * fSlow0) + 0.59999999999999998);
	double fSlow4 = (fConst27 * fSlow3);
	double fSlow5 = ((0.40000000000000002 * std::sin((3.1400000000000001 * fSlow0))) + 0.59999999999999998);
	double fSlow6 = (fConst40 * fSlow5);
	double fSlow7 = (1500.0 * fSlow0);
	double fSlow8 = std::tan((fConst53 * (20000.0 - fSlow7)));
	double fSlow9 = (1.0 / fSlow8);
	double fSlow10 = (((fSlow9 + 0.51763809020504126) / fSlow8) + 1.0);
	double fSlow11 = (fSlow3 / fSlow10);
	double fSlow12 = (1.0 / (((fSlow9 + 1.4142135623730949) / fSlow8) + 1.0));
	double fSlow13 = (1.0 / (((fSlow9 + 1.9318516525781364) / fSlow8) + 1.0));
	double fSlow14 = std::tan((fConst53 * (6400.0 - fSlow7)));
	double fSlow15 = (1.0 / fSlow14);
	double fSlow16 = (((fSlow15 + 0.51763809020504126) / fSlow14) + 1.0);
	double fSlow17 = (1.0 / fSlow16);
	double fSlow18 = mydsp_faustpower2_f(fSlow14);
	double fSlow19 = (1.0 / fSlow18);
	double fSlow20 = (1.0 / (((fSlow15 + 1.4142135623730949) / fSlow14) + 1.0));
	double fSlow21 = (1.0 / (((fSlow15 + 1.9318516525781364) / fSlow14) + 1.0));
	double fSlow22 = (((fSlow15 + -1.9318516525781364) / fSlow14) + 1.0);
	double fSlow23 = (2.0 * (1.0 - fSlow19));
	double fSlow24 = (0.0 - (2.0 / fSlow18));
	double fSlow25 = (((fSlow15 + -1.4142135623730949) / fSlow14) + 1.0);
	double fSlow26 = (((fSlow15 + -0.51763809020504126) / fSlow14) + 1.0);
	double fSlow27 = (((fSlow9 + -1.9318516525781364) / fSlow8) + 1.0);
	double fSlow28 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fSlow8))));
	double fSlow29 = (((fSlow9 + -1.4142135623730949) / fSlow8) + 1.0);
	double fSlow30 = (1.0 / fSlow10);
	double fSlow31 = (((fSlow9 + -0.51763809020504126) / fSlow8) + 1.0);
	double fSlow32 = (fSlow5 / fSlow16);
	double fSlow33 = std::tan((fConst53 * (3600.0 - fSlow7)));
	double fSlow34 = (1.0 / fSlow33);
	double fSlow35 = (((fSlow34 + 0.51763809020504126) / fSlow33) + 1.0);
	double fSlow36 = (1.0 / fSlow35);
	double fSlow37 = mydsp_faustpower2_f(fSlow33);
	double fSlow38 = (1.0 / fSlow37);
	double fSlow39 = (1.0 / (((fSlow34 + 1.4142135623730949) / fSlow33) + 1.0));
	double fSlow40 = (1.0 / (((fSlow34 + 1.9318516525781364) / fSlow33) + 1.0));
	double fSlow41 = (((fSlow34 + -1.9318516525781364) / fSlow33) + 1.0);
	double fSlow42 = (2.0 * (1.0 - fSlow38));
	double fSlow43 = (0.0 - (2.0 / fSlow37));
	double fSlow44 = (((fSlow34 + -1.4142135623730949) / fSlow33) + 1.0);
	double fSlow45 = (((fSlow34 + -0.51763809020504126) / fSlow33) + 1.0);
	double fSlow46 = (((0.40000000000000002 * std::sqrt((fSlow0 + 0.29999999999999999))) + 0.59999999999999998) / fSlow35);
	double fSlow47 = std::tan((fConst53 * (1800.0 - fSlow7)));
	double fSlow48 = (1.0 / fSlow47);
	double fSlow49 = (1.0 / (((fSlow48 + 0.51763809020504126) / fSlow47) + 1.0));
	double fSlow50 = mydsp_faustpower2_f(fSlow47);
	double fSlow51 = (1.0 / fSlow50);
	double fSlow52 = (1.0 / (((fSlow48 + 1.4142135623730949) / fSlow47) + 1.0));
	double fSlow53 = (1.0 / (((fSlow48 + 1.9318516525781364) / fSlow47) + 1.0));
	double fSlow54 = (((fSlow48 + -1.9318516525781364) / fSlow47) + 1.0);
	double fSlow55 = (2.0 * (1.0 - fSlow51));
	double fSlow56 = (0.0 - (2.0 / fSlow50));
	double fSlow57 = (((fSlow48 + -1.4142135623730949) / fSlow47) + 1.0);
	double fSlow58 = (((fSlow48 + -0.51763809020504126) / fSlow47) + 1.0);
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = double(input0[i]);
		fVec0[(IOTA & 131071)] = fTemp0;
		fRec6[0] = (fSlow2 + (0.999 * fRec6[1]));
		double fTemp1 = (fConst13 * fRec6[0]);
		int iTemp2 = int(fTemp1);
		int iTemp3 = std::min<int>(65537, std::max<int>(0, iTemp2));
		double fTemp4 = std::floor(fTemp1);
		double fTemp5 = (fTemp4 + (1.0 - fTemp1));
		double fTemp6 = (fTemp1 - fTemp4);
		int iTemp7 = std::min<int>(65537, std::max<int>(0, (iTemp2 + 1)));
		fRec5[0] = (((fVec0[((IOTA - iTemp3) & 131071)] * fTemp5) + (fTemp6 * fVec0[((IOTA - iTemp7) & 131071)])) - (fConst12 * ((fConst14 * fRec5[2]) + (fConst15 * fRec5[1]))));
		fRec4[0] = ((fConst12 * (((fConst10 * fRec5[0]) + (fConst16 * fRec5[1])) + (fConst10 * fRec5[2]))) - (fConst11 * ((fConst17 * fRec4[2]) + (fConst15 * fRec4[1]))));
		fRec3[0] = ((fConst11 * (((fConst10 * fRec4[0]) + (fConst16 * fRec4[1])) + (fConst10 * fRec4[2]))) - (fConst8 * ((fConst18 * fRec3[2]) + (fConst15 * fRec3[1]))));
		fRec2[0] = ((fConst8 * (((fConst10 * fRec3[0]) + (fConst16 * fRec3[1])) + (fConst10 * fRec3[2]))) - (fConst5 * ((fConst19 * fRec2[2]) + (fConst22 * fRec2[1]))));
		fRec1[0] = ((fConst5 * (fRec2[2] + (fRec2[0] + (2.0 * fRec2[1])))) - (fConst4 * ((fConst23 * fRec1[2]) + (fConst22 * fRec1[1]))));
		fRec0[0] = ((fConst4 * (fRec1[2] + (fRec1[0] + (2.0 * fRec1[1])))) - (fConst3 * ((fConst24 * fRec0[2]) + (fConst22 * fRec0[1]))));
		double fTemp8 = (fConst30 * fRec6[0]);
		int iTemp9 = int(fTemp8);
		double fTemp10 = std::floor(fTemp8);
		fRec12[0] = (((fVec0[((IOTA - std::min<int>(65537, std::max<int>(0, iTemp9))) & 131071)] * (fTemp10 + (1.0 - fTemp8))) + ((fTemp8 - fTemp10) * fVec0[((IOTA - std::min<int>(65537, std::max<int>(0, (iTemp9 + 1)))) & 131071)])) - (fConst5 * ((fConst19 * fRec12[2]) + (fConst22 * fRec12[1]))));
		fRec11[0] = ((fConst5 * (((fConst21 * fRec12[0]) + (fConst31 * fRec12[1])) + (fConst21 * fRec12[2]))) - (fConst4 * ((fConst23 * fRec11[2]) + (fConst22 * fRec11[1]))));
		fRec10[0] = ((fConst4 * (((fConst21 * fRec11[0]) + (fConst31 * fRec11[1])) + (fConst21 * fRec11[2]))) - (fConst3 * ((fConst24 * fRec10[2]) + (fConst22 * fRec10[1]))));
		fRec9[0] = ((fConst3 * (((fConst21 * fRec10[0]) + (fConst31 * fRec10[1])) + (fConst21 * fRec10[2]))) - (fConst29 * ((fConst32 * fRec9[2]) + (fConst35 * fRec9[1]))));
		fRec8[0] = ((fConst29 * (fRec9[2] + (fRec9[0] + (2.0 * fRec9[1])))) - (fConst28 * ((fConst36 * fRec8[2]) + (fConst35 * fRec8[1]))));
		fRec7[0] = ((fConst28 * (fRec8[2] + (fRec8[0] + (2.0 * fRec8[1])))) - (fConst27 * ((fConst37 * fRec7[2]) + (fConst35 * fRec7[1]))));
		double fTemp11 = (fConst43 * fRec6[0]);
		int iTemp12 = int(fTemp11);
		double fTemp13 = std::floor(fTemp11);
		fRec18[0] = (((fVec0[((IOTA - std::min<int>(65537, std::max<int>(0, iTemp12))) & 131071)] * (fTemp13 + (1.0 - fTemp11))) + ((fTemp11 - fTemp13) * fVec0[((IOTA - std::min<int>(65537, std::max<int>(0, (iTemp12 + 1)))) & 131071)])) - (fConst29 * ((fConst32 * fRec18[2]) + (fConst35 * fRec18[1]))));
		fRec17[0] = ((fConst29 * (((fConst34 * fRec18[0]) + (fConst44 * fRec18[1])) + (fConst34 * fRec18[2]))) - (fConst28 * ((fConst36 * fRec17[2]) + (fConst35 * fRec17[1]))));
		fRec16[0] = ((fConst28 * (((fConst34 * fRec17[0]) + (fConst44 * fRec17[1])) + (fConst34 * fRec17[2]))) - (fConst27 * ((fConst37 * fRec16[2]) + (fConst35 * fRec16[1]))));
		fRec15[0] = ((fConst27 * (((fConst34 * fRec16[0]) + (fConst44 * fRec16[1])) + (fConst34 * fRec16[2]))) - (fConst42 * ((fConst45 * fRec15[2]) + (fConst46 * fRec15[1]))));
		fRec14[0] = ((fConst42 * (fRec15[2] + (fRec15[0] + (2.0 * fRec15[1])))) - (fConst41 * ((fConst47 * fRec14[2]) + (fConst46 * fRec14[1]))));
		fRec13[0] = ((fConst41 * (fRec14[2] + (fRec14[0] + (2.0 * fRec14[1])))) - (fConst40 * ((fConst48 * fRec13[2]) + (fConst46 * fRec13[1]))));
		double fTemp14 = double(input1[i]);
		fVec1[(IOTA & 131071)] = fTemp14;
		fRec20[0] = ((0.5 * (fTemp0 + fTemp14)) - (fConst50 * ((fConst51 * fRec20[2]) + (fConst15 * fRec20[1]))));
		fRec19[0] = ((fConst50 * (fRec20[2] + (fRec20[0] + (2.0 * fRec20[1])))) - (fConst49 * ((fConst52 * fRec19[2]) + (fConst15 * fRec19[1]))));
		double fTemp15 = (fConst49 * (fRec19[2] + (fRec19[0] + (2.0 * fRec19[1]))));
		output0[i] = FAUSTFLOAT(((((fSlow1 * (fRec0[2] + (fRec0[0] + (2.0 * fRec0[1])))) + (fSlow4 * (fRec7[2] + (fRec7[0] + (2.0 * fRec7[1]))))) + (fSlow6 * (fRec13[2] + (fRec13[0] + (2.0 * fRec13[1]))))) + fTemp15));
		double fTemp16 = (fConst54 * fRec6[0]);
		int iTemp17 = int(fTemp16);
		double fTemp18 = std::floor(fTemp16);
		fRec26[0] = (((fVec1[((IOTA - std::min<int>(65537, std::max<int>(0, iTemp17))) & 131071)] * (fTemp18 + (1.0 - fTemp16))) + ((fTemp16 - fTemp18) * fVec1[((IOTA - std::min<int>(65537, std::max<int>(0, (iTemp17 + 1)))) & 131071)])) - (fSlow21 * ((fSlow22 * fRec26[2]) + (fSlow23 * fRec26[1]))));
		fRec25[0] = ((fSlow21 * (((fSlow19 * fRec26[0]) + (fSlow24 * fRec26[1])) + (fSlow19 * fRec26[2]))) - (fSlow20 * ((fSlow25 * fRec25[2]) + (fSlow23 * fRec25[1]))));
		fRec24[0] = ((fSlow20 * (((fSlow19 * fRec25[0]) + (fSlow24 * fRec25[1])) + (fSlow19 * fRec25[2]))) - (fSlow17 * ((fSlow26 * fRec24[2]) + (fSlow23 * fRec24[1]))));
		fRec23[0] = ((fSlow17 * (((fSlow19 * fRec24[0]) + (fSlow24 * fRec24[1])) + (fSlow19 * fRec24[2]))) - (fSlow13 * ((fSlow27 * fRec23[2]) + (fSlow28 * fRec23[1]))));
		fRec22[0] = ((fSlow13 * (fRec23[2] + (fRec23[0] + (2.0 * fRec23[1])))) - (fSlow12 * ((fSlow29 * fRec22[2]) + (fSlow28 * fRec22[1]))));
		fRec21[0] = ((fSlow12 * (fRec22[2] + (fRec22[0] + (2.0 * fRec22[1])))) - (fSlow30 * ((fSlow31 * fRec21[2]) + (fSlow28 * fRec21[1]))));
		fRec32[0] = (((fVec1[((IOTA - iTemp3) & 131071)] * fTemp5) + (fTemp6 * fVec1[((IOTA - iTemp7) & 131071)])) - (fSlow40 * ((fSlow41 * fRec32[2]) + (fSlow42 * fRec32[1]))));
		fRec31[0] = ((fSlow40 * (((fSlow38 * fRec32[0]) + (fSlow43 * fRec32[1])) + (fSlow38 * fRec32[2]))) - (fSlow39 * ((fSlow44 * fRec31[2]) + (fSlow42 * fRec31[1]))));
		fRec30[0] = ((fSlow39 * (((fSlow38 * fRec31[0]) + (fSlow43 * fRec31[1])) + (fSlow38 * fRec31[2]))) - (fSlow36 * ((fSlow45 * fRec30[2]) + (fSlow42 * fRec30[1]))));
		fRec29[0] = ((fSlow36 * (((fSlow38 * fRec30[0]) + (fSlow43 * fRec30[1])) + (fSlow38 * fRec30[2]))) - (fSlow21 * ((fSlow22 * fRec29[2]) + (fSlow23 * fRec29[1]))));
		fRec28[0] = ((fSlow21 * (fRec29[2] + (fRec29[0] + (2.0 * fRec29[1])))) - (fSlow20 * ((fSlow25 * fRec28[2]) + (fSlow23 * fRec28[1]))));
		fRec27[0] = ((fSlow20 * (fRec28[2] + (fRec28[0] + (2.0 * fRec28[1])))) - (fSlow17 * ((fSlow26 * fRec27[2]) + (fSlow23 * fRec27[1]))));
		double fTemp19 = (fConst55 * fRec6[0]);
		int iTemp20 = int(fTemp19);
		double fTemp21 = std::floor(fTemp19);
		fRec38[0] = (((fVec1[((IOTA - std::min<int>(65537, std::max<int>(0, iTemp20))) & 131071)] * (fTemp21 + (1.0 - fTemp19))) + ((fTemp19 - fTemp21) * fVec1[((IOTA - std::min<int>(65537, std::max<int>(0, (iTemp20 + 1)))) & 131071)])) - (fSlow53 * ((fSlow54 * fRec38[2]) + (fSlow55 * fRec38[1]))));
		fRec37[0] = ((fSlow53 * (((fSlow51 * fRec38[0]) + (fSlow56 * fRec38[1])) + (fSlow51 * fRec38[2]))) - (fSlow52 * ((fSlow57 * fRec37[2]) + (fSlow55 * fRec37[1]))));
		fRec36[0] = ((fSlow52 * (((fSlow51 * fRec37[0]) + (fSlow56 * fRec37[1])) + (fSlow51 * fRec37[2]))) - (fSlow49 * ((fSlow58 * fRec36[2]) + (fSlow55 * fRec36[1]))));
		fRec35[0] = ((fSlow49 * (((fSlow51 * fRec36[0]) + (fSlow56 * fRec36[1])) + (fSlow51 * fRec36[2]))) - (fSlow40 * ((fSlow41 * fRec35[2]) + (fSlow42 * fRec35[1]))));
		fRec34[0] = ((fSlow40 * (fRec35[2] + (fRec35[0] + (2.0 * fRec35[1])))) - (fSlow39 * ((fSlow44 * fRec34[2]) + (fSlow42 * fRec34[1]))));
		fRec33[0] = ((fSlow39 * (fRec34[2] + (fRec34[0] + (2.0 * fRec34[1])))) - (fSlow36 * ((fSlow45 * fRec33[2]) + (fSlow42 * fRec33[1]))));
		output1[i] = FAUSTFLOAT(((fSlow11 * (fRec21[2] + (fRec21[0] + (2.0 * fRec21[1])))) + ((fSlow32 * (fRec27[2] + (fRec27[0] + (2.0 * fRec27[1])))) + (fTemp15 + (fSlow46 * (fRec33[2] + (fRec33[0] + (2.0 * fRec33[1]))))))));
		IOTA = (IOTA + 1);
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec18[2] = fRec18[1];
		fRec18[1] = fRec18[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
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
	reg.registerVar("panoram_enhancer.Delay width",N_("Delay"),"S",N_("Delay Width"),&fHslider1, 0.0, 0.0, 1.0, 0.01);
	reg.registerVar("panoram_enhancer.Frequency width",N_("Frequency"),"S",N_("Frequency Width"),&fHslider0, 0.0, 0.0, 1.0, 0.01);
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
