// generated from file '../src/faust/stereoverb.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace stereoverb {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	int iVec0[2];
	double fRec9[2];
	int IOTA;
	double fVec1[2048];
	double fRec8[2];
	double fRec11[2];
	double fVec2[2048];
	double fRec10[2];
	double fRec13[2];
	double fVec3[2048];
	double fRec12[2];
	double fRec15[2];
	double fVec4[2048];
	double fRec14[2];
	double fRec17[2];
	double fVec5[2048];
	double fRec16[2];
	double fRec19[2];
	double fVec6[2048];
	double fRec18[2];
	double fRec21[2];
	double fVec7[2048];
	double fRec20[2];
	double fRec23[2];
	double fVec8[2048];
	double fRec22[2];
	double fVec9[1024];
	double fRec6[2];
	double fVec10[512];
	double fRec4[2];
	double fVec11[512];
	double fRec2[2];
	double fVec12[256];
	double fRec0[2];
	FAUSTFLOAT fCheckbox0;
	double fConst0;
	FAUSTFLOAT fHslider0;
	double fRec24[2];
	double fRec25[2];
	double fRec35[2];
	double fVec13[2048];
	double fRec34[2];
	double fRec37[2];
	double fVec14[2048];
	double fRec36[2];
	double fRec39[2];
	double fVec15[2048];
	double fRec38[2];
	double fRec41[2];
	double fVec16[2048];
	double fRec40[2];
	double fRec43[2];
	double fVec17[2048];
	double fRec42[2];
	double fRec45[2];
	double fVec18[2048];
	double fRec44[2];
	double fRec47[2];
	double fVec19[2048];
	double fRec46[2];
	double fRec49[2];
	double fVec20[2048];
	double fRec48[2];
	double fVec21[1024];
	double fRec32[2];
	double fVec22[512];
	double fRec30[2];
	double fVec23[512];
	double fRec28[2];
	double fVec24[256];
	double fRec26[2];

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
	id = "stereoverb";
	name = N_("Stereo Verb");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Reverb");       // category
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) iVec0[l0] = 0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec9[l1] = 0.0;
	for (int l2 = 0; (l2 < 2048); l2 = (l2 + 1)) fVec1[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec8[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec11[l4] = 0.0;
	for (int l5 = 0; (l5 < 2048); l5 = (l5 + 1)) fVec2[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec10[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec13[l7] = 0.0;
	for (int l8 = 0; (l8 < 2048); l8 = (l8 + 1)) fVec3[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec12[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec15[l10] = 0.0;
	for (int l11 = 0; (l11 < 2048); l11 = (l11 + 1)) fVec4[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec14[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec17[l13] = 0.0;
	for (int l14 = 0; (l14 < 2048); l14 = (l14 + 1)) fVec5[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec16[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec19[l16] = 0.0;
	for (int l17 = 0; (l17 < 2048); l17 = (l17 + 1)) fVec6[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec18[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec21[l19] = 0.0;
	for (int l20 = 0; (l20 < 2048); l20 = (l20 + 1)) fVec7[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec20[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fRec23[l22] = 0.0;
	for (int l23 = 0; (l23 < 2048); l23 = (l23 + 1)) fVec8[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec22[l24] = 0.0;
	for (int l25 = 0; (l25 < 1024); l25 = (l25 + 1)) fVec9[l25] = 0.0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fRec6[l26] = 0.0;
	for (int l27 = 0; (l27 < 512); l27 = (l27 + 1)) fVec10[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec4[l28] = 0.0;
	for (int l29 = 0; (l29 < 512); l29 = (l29 + 1)) fVec11[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec2[l30] = 0.0;
	for (int l31 = 0; (l31 < 256); l31 = (l31 + 1)) fVec12[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fRec0[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fRec24[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec25[l34] = 0.0;
	for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) fRec35[l35] = 0.0;
	for (int l36 = 0; (l36 < 2048); l36 = (l36 + 1)) fVec13[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fRec34[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fRec37[l38] = 0.0;
	for (int l39 = 0; (l39 < 2048); l39 = (l39 + 1)) fVec14[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fRec36[l40] = 0.0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) fRec39[l41] = 0.0;
	for (int l42 = 0; (l42 < 2048); l42 = (l42 + 1)) fVec15[l42] = 0.0;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fRec38[l43] = 0.0;
	for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) fRec41[l44] = 0.0;
	for (int l45 = 0; (l45 < 2048); l45 = (l45 + 1)) fVec16[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec40[l46] = 0.0;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) fRec43[l47] = 0.0;
	for (int l48 = 0; (l48 < 2048); l48 = (l48 + 1)) fVec17[l48] = 0.0;
	for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) fRec42[l49] = 0.0;
	for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) fRec45[l50] = 0.0;
	for (int l51 = 0; (l51 < 2048); l51 = (l51 + 1)) fVec18[l51] = 0.0;
	for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) fRec44[l52] = 0.0;
	for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) fRec47[l53] = 0.0;
	for (int l54 = 0; (l54 < 2048); l54 = (l54 + 1)) fVec19[l54] = 0.0;
	for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) fRec46[l55] = 0.0;
	for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) fRec49[l56] = 0.0;
	for (int l57 = 0; (l57 < 2048); l57 = (l57 + 1)) fVec20[l57] = 0.0;
	for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) fRec48[l58] = 0.0;
	for (int l59 = 0; (l59 < 1024); l59 = (l59 + 1)) fVec21[l59] = 0.0;
	for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) fRec32[l60] = 0.0;
	for (int l61 = 0; (l61 < 512); l61 = (l61 + 1)) fVec22[l61] = 0.0;
	for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) fRec30[l62] = 0.0;
	for (int l63 = 0; (l63 < 512); l63 = (l63 + 1)) fVec23[l63] = 0.0;
	for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) fRec28[l64] = 0.0;
	for (int l65 = 0; (l65 < 256); l65 = (l65 + 1)) fVec24[l65] = 0.0;
	for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) fRec26[l66] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (6.2831853071795862 / std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq))));
	fVslider0 = FAUSTFLOAT(50.0);
	fVslider1 = FAUSTFLOAT(0.5);
	fVslider2 = FAUSTFLOAT(0.5);
	fCheckbox0 = FAUSTFLOAT(0.0);
	fHslider0 = FAUSTFLOAT(0.20000000000000001);
			IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	double fSlow0 = double(fVslider0);
	double fSlow1 = (1.0 - (0.01 * fSlow0));
	double fSlow2 = (0.00014999999999999999 * fSlow0);
	double fSlow3 = ((0.28000000000000003 * double(fVslider1)) + 0.69999999999999996);
	double fSlow4 = double(fVslider2);
	double fSlow5 = (1.0 - fSlow4);
	double fSlow6 = (((0.01 * fSlow1) + 0.00014999999999999999) * fSlow0);
	double fSlow7 = double(fCheckbox0);
	double fSlow8 = (fConst0 * double(fHslider0));
	double fSlow9 = std::sin(fSlow8);
	double fSlow10 = std::cos(fSlow8);
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = double(input0[i]);
		double fTemp1 = (fSlow2 * fTemp0);
		iVec0[0] = 1;
		fRec9[0] = ((fSlow4 * fRec9[1]) + (fSlow5 * fRec8[1]));
		fVec1[(IOTA & 2047)] = (fTemp1 + (fSlow3 * fRec9[0]));
		fRec8[0] = fVec1[((IOTA - 1139) & 2047)];
		fRec11[0] = ((fSlow4 * fRec11[1]) + (fSlow5 * fRec10[1]));
		fVec2[(IOTA & 2047)] = (fTemp1 + (fSlow3 * fRec11[0]));
		fRec10[0] = fVec2[((IOTA - 1211) & 2047)];
		fRec13[0] = ((fSlow4 * fRec13[1]) + (fSlow5 * fRec12[1]));
		fVec3[(IOTA & 2047)] = (fTemp1 + (fSlow3 * fRec13[0]));
		fRec12[0] = fVec3[((IOTA - 1300) & 2047)];
		fRec15[0] = ((fSlow4 * fRec15[1]) + (fSlow5 * fRec14[1]));
		fVec4[(IOTA & 2047)] = (fTemp1 + (fSlow3 * fRec15[0]));
		fRec14[0] = fVec4[((IOTA - 1379) & 2047)];
		fRec17[0] = ((fSlow4 * fRec17[1]) + (fSlow5 * fRec16[1]));
		fVec5[(IOTA & 2047)] = (fTemp1 + (fSlow3 * fRec17[0]));
		fRec16[0] = fVec5[((IOTA - 1445) & 2047)];
		fRec19[0] = ((fSlow4 * fRec19[1]) + (fSlow5 * fRec18[1]));
		fVec6[(IOTA & 2047)] = (fTemp1 + (fSlow3 * fRec19[0]));
		fRec18[0] = fVec6[((IOTA - 1514) & 2047)];
		fRec21[0] = ((fSlow4 * fRec21[1]) + (fSlow5 * fRec20[1]));
		fVec7[(IOTA & 2047)] = (fTemp1 + (fSlow3 * fRec21[0]));
		fRec20[0] = fVec7[((IOTA - 1580) & 2047)];
		fRec23[0] = ((fSlow4 * fRec23[1]) + (fSlow5 * fRec22[1]));
		fVec8[(IOTA & 2047)] = (fTemp1 + (fSlow3 * fRec23[0]));
		fRec22[0] = fVec8[((IOTA - 1640) & 2047)];
		double fTemp2 = (((((((fRec8[0] + fRec10[0]) + fRec12[0]) + fRec14[0]) + fRec16[0]) + fRec18[0]) + fRec20[0]) + fRec22[0]);
		fVec9[(IOTA & 1023)] = (fTemp2 + (0.5 * fRec6[1]));
		fRec6[0] = fVec9[((IOTA - 579) & 1023)];
		double fRec7 = (fRec6[1] - fTemp2);
		fVec10[(IOTA & 511)] = (fRec7 + (0.5 * fRec4[1]));
		fRec4[0] = fVec10[((IOTA - 464) & 511)];
		double fRec5 = (fRec4[1] - fRec7);
		fVec11[(IOTA & 511)] = (fRec5 + (0.5 * fRec2[1]));
		fRec2[0] = fVec11[((IOTA - 364) & 511)];
		double fRec3 = (fRec2[1] - fRec5);
		fVec12[(IOTA & 255)] = (fRec3 + (0.5 * fRec0[1]));
		fRec0[0] = fVec12[((IOTA - 248) & 255)];
		double fRec1 = (fRec0[1] - fRec3);
		fRec24[0] = ((fSlow9 * fRec25[1]) + (fSlow10 * fRec24[1]));
		fRec25[0] = ((double((1 - iVec0[1])) + (fSlow10 * fRec25[1])) - (fSlow9 * fRec24[1]));
		output0[i] = FAUSTFLOAT(((fSlow1 * fTemp0) + ((fRec1 + (fSlow6 * fTemp0)) * (1.0 - (fSlow7 * fRec24[0])))));
		double fTemp3 = double(input1[i]);
		double fTemp4 = (fSlow2 * fTemp3);
		fRec35[0] = ((fSlow4 * fRec35[1]) + (fSlow5 * fRec34[1]));
		fVec13[(IOTA & 2047)] = (fTemp4 + (fSlow3 * fRec35[0]));
		fRec34[0] = fVec13[((IOTA - 1139) & 2047)];
		fRec37[0] = ((fSlow4 * fRec37[1]) + (fSlow5 * fRec36[1]));
		fVec14[(IOTA & 2047)] = (fTemp4 + (fSlow3 * fRec37[0]));
		fRec36[0] = fVec14[((IOTA - 1211) & 2047)];
		fRec39[0] = ((fSlow4 * fRec39[1]) + (fSlow5 * fRec38[1]));
		fVec15[(IOTA & 2047)] = (fTemp4 + (fSlow3 * fRec39[0]));
		fRec38[0] = fVec15[((IOTA - 1300) & 2047)];
		fRec41[0] = ((fSlow4 * fRec41[1]) + (fSlow5 * fRec40[1]));
		fVec16[(IOTA & 2047)] = (fTemp4 + (fSlow3 * fRec41[0]));
		fRec40[0] = fVec16[((IOTA - 1379) & 2047)];
		fRec43[0] = ((fSlow4 * fRec43[1]) + (fSlow5 * fRec42[1]));
		fVec17[(IOTA & 2047)] = (fTemp4 + (fSlow3 * fRec43[0]));
		fRec42[0] = fVec17[((IOTA - 1445) & 2047)];
		fRec45[0] = ((fSlow4 * fRec45[1]) + (fSlow5 * fRec44[1]));
		fVec18[(IOTA & 2047)] = (fTemp4 + (fSlow3 * fRec45[0]));
		fRec44[0] = fVec18[((IOTA - 1514) & 2047)];
		fRec47[0] = ((fSlow4 * fRec47[1]) + (fSlow5 * fRec46[1]));
		fVec19[(IOTA & 2047)] = (fTemp4 + (fSlow3 * fRec47[0]));
		fRec46[0] = fVec19[((IOTA - 1580) & 2047)];
		fRec49[0] = ((fSlow4 * fRec49[1]) + (fSlow5 * fRec48[1]));
		fVec20[(IOTA & 2047)] = (fTemp4 + (fSlow3 * fRec49[0]));
		fRec48[0] = fVec20[((IOTA - 1640) & 2047)];
		double fTemp5 = (((((((fRec34[0] + fRec36[0]) + fRec38[0]) + fRec40[0]) + fRec42[0]) + fRec44[0]) + fRec46[0]) + fRec48[0]);
		fVec21[(IOTA & 1023)] = (fTemp5 + (0.5 * fRec32[1]));
		fRec32[0] = fVec21[((IOTA - 579) & 1023)];
		double fRec33 = (fRec32[1] - fTemp5);
		fVec22[(IOTA & 511)] = (fRec33 + (0.5 * fRec30[1]));
		fRec30[0] = fVec22[((IOTA - 464) & 511)];
		double fRec31 = (fRec30[1] - fRec33);
		fVec23[(IOTA & 511)] = (fRec31 + (0.5 * fRec28[1]));
		fRec28[0] = fVec23[((IOTA - 364) & 511)];
		double fRec29 = (fRec28[1] - fRec31);
		fVec24[(IOTA & 255)] = (fRec29 + (0.5 * fRec26[1]));
		fRec26[0] = fVec24[((IOTA - 248) & 255)];
		double fRec27 = (fRec26[1] - fRec29);
		output1[i] = FAUSTFLOAT(((fSlow1 * fTemp3) + ((fRec27 + (fSlow6 * fTemp3)) * (1.0 - (fSlow7 * (0.0 - fRec24[0]))))));
		iVec0[1] = iVec0[0];
		fRec9[1] = fRec9[0];
		IOTA = (IOTA + 1);
		fRec8[1] = fRec8[0];
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec15[1] = fRec15[0];
		fRec14[1] = fRec14[0];
		fRec17[1] = fRec17[0];
		fRec16[1] = fRec16[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec6[1] = fRec6[0];
		fRec4[1] = fRec4[0];
		fRec2[1] = fRec2[0];
		fRec0[1] = fRec0[0];
		fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec35[1] = fRec35[0];
		fRec34[1] = fRec34[0];
		fRec37[1] = fRec37[0];
		fRec36[1] = fRec36[0];
		fRec39[1] = fRec39[0];
		fRec38[1] = fRec38[0];
		fRec41[1] = fRec41[0];
		fRec40[1] = fRec40[0];
		fRec43[1] = fRec43[0];
		fRec42[1] = fRec42[0];
		fRec45[1] = fRec45[0];
		fRec44[1] = fRec44[0];
		fRec47[1] = fRec47[0];
		fRec46[1] = fRec46[0];
		fRec49[1] = fRec49[0];
		fRec48[1] = fRec48[0];
		fRec32[1] = fRec32[0];
		fRec30[1] = fRec30[0];
		fRec28[1] = fRec28[0];
		fRec26[1] = fRec26[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("stereoverb.LFO freq",N_("LFO Freq"),"S","",&fHslider0, 0.20000000000000001, 0.0, 5.0, 0.01);
	reg.registerVar("stereoverb.RoomSize",N_("Room Size"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.025000000000000001);
	reg.registerVar("stereoverb.damp",N_("Damp"),"S","",&fVslider2, 0.5, 0.0, 1.0, 0.025000000000000001);
	static const value_pair fCheckbox0_values[] = {{"linear"},{"pingpong"},{0}};
	reg.registerEnumVar("stereoverb.invert","","B","",fCheckbox0_values,&fCheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("stereoverb.wet_dry",N_("Dry/Wet"),"S","",&fVslider0, 50.0, 0.0, 100.0, 1.0);
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
                  <object class=\"GxSelector\" id=\"gxselector1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">stereoverb.invert</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">5</property>\n\
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
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">stereoverb.LFO freq</property>\n\
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
                    <property name=\"position\">1</property>\n\
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
                      <object class=\"GxMidKnob\" id=\"gxbigknob2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">stereoverb.RoomSize</property>\n\
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
                    <property name=\"position\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">5</property>\n\
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
                        <property name=\"var_id\">stereoverb.damp</property>\n\
                        <property name=\"label_ref\">label3:rack_label</property>\n\
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
                    <property name=\"position\">3</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox5\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">5</property>\n\
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
                        <property name=\"var_id\">stereoverb.wet_dry</property>\n\
                        <property name=\"label_ref\">label4:rack_label</property>\n\
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
                    <property name=\"position\">4</property>\n\
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
                <property name=\"var_id\">stereoverb.RoomSize</property>\n\
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
#define PARAM(p) ("stereoverb" "." p)
//stereoverb
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("RoomSize"), _("RoomSize"));
b.closeBox();
b.openHorizontalBox("");
{
    b.openVerticalBox("");
    {
	b.create_small_rackknobr(PARAM("RoomSize"), _("RoomSize"));
	b.insertSpacer();
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.create_small_rackknob(PARAM("damp"), _("damp"));
	b.insertSpacer();
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.create_small_rackknob(PARAM("wet_dry"), _("dry/wet"));
	b.insertSpacer();
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.create_small_rackknobr(PARAM("LFO freq"), _("LFO"));
	b.insertSpacer();
	b.create_selector(PARAM("invert"), "invert");
	b.openFrameBox("");
	b.closeBox();
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

} // end namespace stereoverb
