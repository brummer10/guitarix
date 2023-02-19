// generated from file '../src/LV2/faust/stereoverb.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace stereoverb {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	int iVec0[2];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	double fConst0;
	double fRec0[2];
	double fRec1[2];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec11[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	int IOTA0;
	double fVec1[2048];
	double fRec10[2];
	double fRec13[2];
	double fVec2[2048];
	double fRec12[2];
	double fRec15[2];
	double fVec3[2048];
	double fRec14[2];
	double fRec17[2];
	double fVec4[2048];
	double fRec16[2];
	double fRec19[2];
	double fVec5[2048];
	double fRec18[2];
	double fRec21[2];
	double fVec6[2048];
	double fRec20[2];
	double fRec23[2];
	double fVec7[2048];
	double fRec22[2];
	double fRec25[2];
	double fVec8[2048];
	double fRec24[2];
	double fVec9[1024];
	double fRec8[2];
	double fVec10[512];
	double fRec6[2];
	double fVec11[512];
	double fRec4[2];
	double fVec12[256];
	double fRec2[2];
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

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "stereoverb";
	name = N_("Stereo Verb");
	mono_audio = 0;
	stereo_audio = compute_static;
	set_samplerate = init_static;
	activate_plugin = 0;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) iVec0[l0] = 0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec0[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec1[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec11[l3] = 0.0;
	for (int l4 = 0; l4 < 2048; l4 = l4 + 1) fVec1[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec10[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec13[l6] = 0.0;
	for (int l7 = 0; l7 < 2048; l7 = l7 + 1) fVec2[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec12[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec15[l9] = 0.0;
	for (int l10 = 0; l10 < 2048; l10 = l10 + 1) fVec3[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec14[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec17[l12] = 0.0;
	for (int l13 = 0; l13 < 2048; l13 = l13 + 1) fVec4[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec16[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec19[l15] = 0.0;
	for (int l16 = 0; l16 < 2048; l16 = l16 + 1) fVec5[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec18[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec21[l18] = 0.0;
	for (int l19 = 0; l19 < 2048; l19 = l19 + 1) fVec6[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec20[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec23[l21] = 0.0;
	for (int l22 = 0; l22 < 2048; l22 = l22 + 1) fVec7[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec22[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec25[l24] = 0.0;
	for (int l25 = 0; l25 < 2048; l25 = l25 + 1) fVec8[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec24[l26] = 0.0;
	for (int l27 = 0; l27 < 1024; l27 = l27 + 1) fVec9[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec8[l28] = 0.0;
	for (int l29 = 0; l29 < 512; l29 = l29 + 1) fVec10[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec6[l30] = 0.0;
	for (int l31 = 0; l31 < 512; l31 = l31 + 1) fVec11[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fRec4[l32] = 0.0;
	for (int l33 = 0; l33 < 256; l33 = l33 + 1) fVec12[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fRec2[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec35[l35] = 0.0;
	for (int l36 = 0; l36 < 2048; l36 = l36 + 1) fVec13[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec34[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fRec37[l38] = 0.0;
	for (int l39 = 0; l39 < 2048; l39 = l39 + 1) fVec14[l39] = 0.0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec36[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec39[l41] = 0.0;
	for (int l42 = 0; l42 < 2048; l42 = l42 + 1) fVec15[l42] = 0.0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fRec38[l43] = 0.0;
	for (int l44 = 0; l44 < 2; l44 = l44 + 1) fRec41[l44] = 0.0;
	for (int l45 = 0; l45 < 2048; l45 = l45 + 1) fVec16[l45] = 0.0;
	for (int l46 = 0; l46 < 2; l46 = l46 + 1) fRec40[l46] = 0.0;
	for (int l47 = 0; l47 < 2; l47 = l47 + 1) fRec43[l47] = 0.0;
	for (int l48 = 0; l48 < 2048; l48 = l48 + 1) fVec17[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec42[l49] = 0.0;
	for (int l50 = 0; l50 < 2; l50 = l50 + 1) fRec45[l50] = 0.0;
	for (int l51 = 0; l51 < 2048; l51 = l51 + 1) fVec18[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fRec44[l52] = 0.0;
	for (int l53 = 0; l53 < 2; l53 = l53 + 1) fRec47[l53] = 0.0;
	for (int l54 = 0; l54 < 2048; l54 = l54 + 1) fVec19[l54] = 0.0;
	for (int l55 = 0; l55 < 2; l55 = l55 + 1) fRec46[l55] = 0.0;
	for (int l56 = 0; l56 < 2; l56 = l56 + 1) fRec49[l56] = 0.0;
	for (int l57 = 0; l57 < 2048; l57 = l57 + 1) fVec20[l57] = 0.0;
	for (int l58 = 0; l58 < 2; l58 = l58 + 1) fRec48[l58] = 0.0;
	for (int l59 = 0; l59 < 1024; l59 = l59 + 1) fVec21[l59] = 0.0;
	for (int l60 = 0; l60 < 2; l60 = l60 + 1) fRec32[l60] = 0.0;
	for (int l61 = 0; l61 < 512; l61 = l61 + 1) fVec22[l61] = 0.0;
	for (int l62 = 0; l62 < 2; l62 = l62 + 1) fRec30[l62] = 0.0;
	for (int l63 = 0; l63 < 512; l63 = l63 + 1) fVec23[l63] = 0.0;
	for (int l64 = 0; l64 < 2; l64 = l64 + 1) fRec28[l64] = 0.0;
	for (int l65 = 0; l65 < 256; l65 = l65 + 1) fVec24[l65] = 0.0;
	for (int l66 = 0; l66 < 2; l66 = l66 + 1) fRec26[l66] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = 6.283185307179586 / std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	IOTA0 = 0;
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fHslider0 (*fHslider0_)
#define fCheckbox0 (*fCheckbox0_)
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
	double fSlow0 = fConst0 * double(fHslider0);
	double fSlow1 = std::cos(fSlow0);
	double fSlow2 = std::sin(fSlow0);
	double fSlow3 = double(fCheckbox0);
	double fSlow4 = double(fVslider0);
	double fSlow5 = 1.0 - 0.01 * fSlow4;
	double fSlow6 = fSlow4 * (0.01 * fSlow5 + 0.00015);
	double fSlow7 = double(fVslider1);
	double fSlow8 = 1.0 - fSlow7;
	double fSlow9 = 0.28 * double(fVslider2) + 0.7;
	double fSlow10 = 0.00015 * fSlow4;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		iVec0[0] = 1;
		fRec0[0] = fSlow2 * fRec1[1] + fSlow1 * fRec0[1];
		fRec1[0] = double(1 - iVec0[1]) + fSlow1 * fRec1[1] - fSlow2 * fRec0[1];
		double fTemp0 = double(input0[i0]);
		fRec11[0] = fSlow7 * fRec11[1] + fSlow8 * fRec10[1];
		double fTemp1 = fSlow10 * fTemp0;
		fVec1[IOTA0 & 2047] = fTemp1 + fSlow9 * fRec11[0];
		fRec10[0] = fVec1[(IOTA0 - 1640) & 2047];
		fRec13[0] = fSlow7 * fRec13[1] + fSlow8 * fRec12[1];
		fVec2[IOTA0 & 2047] = fTemp1 + fSlow9 * fRec13[0];
		fRec12[0] = fVec2[(IOTA0 - 1580) & 2047];
		fRec15[0] = fSlow7 * fRec15[1] + fSlow8 * fRec14[1];
		fVec3[IOTA0 & 2047] = fTemp1 + fSlow9 * fRec15[0];
		fRec14[0] = fVec3[(IOTA0 - 1514) & 2047];
		fRec17[0] = fSlow7 * fRec17[1] + fSlow8 * fRec16[1];
		fVec4[IOTA0 & 2047] = fTemp1 + fSlow9 * fRec17[0];
		fRec16[0] = fVec4[(IOTA0 - 1445) & 2047];
		fRec19[0] = fSlow7 * fRec19[1] + fSlow8 * fRec18[1];
		fVec5[IOTA0 & 2047] = fTemp1 + fSlow9 * fRec19[0];
		fRec18[0] = fVec5[(IOTA0 - 1379) & 2047];
		fRec21[0] = fSlow7 * fRec21[1] + fSlow8 * fRec20[1];
		fVec6[IOTA0 & 2047] = fTemp1 + fSlow9 * fRec21[0];
		fRec20[0] = fVec6[(IOTA0 - 1300) & 2047];
		fRec23[0] = fSlow7 * fRec23[1] + fSlow8 * fRec22[1];
		fVec7[IOTA0 & 2047] = fTemp1 + fSlow9 * fRec23[0];
		fRec22[0] = fVec7[(IOTA0 - 1211) & 2047];
		fRec25[0] = fSlow7 * fRec25[1] + fSlow8 * fRec24[1];
		fVec8[IOTA0 & 2047] = fTemp1 + fSlow9 * fRec25[0];
		fRec24[0] = fVec8[(IOTA0 - 1139) & 2047];
		double fTemp2 = fRec24[0] + fRec22[0] + fRec20[0] + fRec18[0] + fRec16[0] + fRec14[0] + fRec12[0] + fRec10[0];
		fVec9[IOTA0 & 1023] = fTemp2 + 0.5 * fRec8[1];
		fRec8[0] = fVec9[(IOTA0 - 579) & 1023];
		double fRec9 = fRec8[1] - fTemp2;
		fVec10[IOTA0 & 511] = fRec9 + 0.5 * fRec6[1];
		fRec6[0] = fVec10[(IOTA0 - 464) & 511];
		double fRec7 = fRec6[1] - fRec9;
		fVec11[IOTA0 & 511] = fRec7 + 0.5 * fRec4[1];
		fRec4[0] = fVec11[(IOTA0 - 364) & 511];
		double fRec5 = fRec4[1] - fRec7;
		fVec12[IOTA0 & 255] = fRec5 + 0.5 * fRec2[1];
		fRec2[0] = fVec12[(IOTA0 - 248) & 255];
		double fRec3 = fRec2[1] - fRec5;
		output0[i0] = FAUSTFLOAT(fSlow5 * fTemp0 + (fRec3 + fSlow6 * fTemp0) * (1.0 - fSlow3 * fRec0[0]));
		double fTemp3 = double(input1[i0]);
		fRec35[0] = fSlow7 * fRec35[1] + fSlow8 * fRec34[1];
		double fTemp4 = fSlow10 * fTemp3;
		fVec13[IOTA0 & 2047] = fTemp4 + fSlow9 * fRec35[0];
		fRec34[0] = fVec13[(IOTA0 - 1640) & 2047];
		fRec37[0] = fSlow7 * fRec37[1] + fSlow8 * fRec36[1];
		fVec14[IOTA0 & 2047] = fTemp4 + fSlow9 * fRec37[0];
		fRec36[0] = fVec14[(IOTA0 - 1580) & 2047];
		fRec39[0] = fSlow7 * fRec39[1] + fSlow8 * fRec38[1];
		fVec15[IOTA0 & 2047] = fTemp4 + fSlow9 * fRec39[0];
		fRec38[0] = fVec15[(IOTA0 - 1514) & 2047];
		fRec41[0] = fSlow7 * fRec41[1] + fSlow8 * fRec40[1];
		fVec16[IOTA0 & 2047] = fTemp4 + fSlow9 * fRec41[0];
		fRec40[0] = fVec16[(IOTA0 - 1445) & 2047];
		fRec43[0] = fSlow7 * fRec43[1] + fSlow8 * fRec42[1];
		fVec17[IOTA0 & 2047] = fTemp4 + fSlow9 * fRec43[0];
		fRec42[0] = fVec17[(IOTA0 - 1379) & 2047];
		fRec45[0] = fSlow7 * fRec45[1] + fSlow8 * fRec44[1];
		fVec18[IOTA0 & 2047] = fTemp4 + fSlow9 * fRec45[0];
		fRec44[0] = fVec18[(IOTA0 - 1300) & 2047];
		fRec47[0] = fSlow7 * fRec47[1] + fSlow8 * fRec46[1];
		fVec19[IOTA0 & 2047] = fTemp4 + fSlow9 * fRec47[0];
		fRec46[0] = fVec19[(IOTA0 - 1211) & 2047];
		fRec49[0] = fSlow7 * fRec49[1] + fSlow8 * fRec48[1];
		fVec20[IOTA0 & 2047] = fTemp4 + fSlow9 * fRec49[0];
		fRec48[0] = fVec20[(IOTA0 - 1139) & 2047];
		double fTemp5 = fRec48[0] + fRec46[0] + fRec44[0] + fRec42[0] + fRec40[0] + fRec38[0] + fRec36[0] + fRec34[0];
		fVec21[IOTA0 & 1023] = fTemp5 + 0.5 * fRec32[1];
		fRec32[0] = fVec21[(IOTA0 - 579) & 1023];
		double fRec33 = fRec32[1] - fTemp5;
		fVec22[IOTA0 & 511] = fRec33 + 0.5 * fRec30[1];
		fRec30[0] = fVec22[(IOTA0 - 464) & 511];
		double fRec31 = fRec30[1] - fRec33;
		fVec23[IOTA0 & 511] = fRec31 + 0.5 * fRec28[1];
		fRec28[0] = fVec23[(IOTA0 - 364) & 511];
		double fRec29 = fRec28[1] - fRec31;
		fVec24[IOTA0 & 255] = fRec29 + 0.5 * fRec26[1];
		fRec26[0] = fVec24[(IOTA0 - 248) & 255];
		double fRec27 = fRec26[1] - fRec29;
		output1[i0] = FAUSTFLOAT(fSlow5 * fTemp3 + (fRec27 + fSlow6 * fTemp3) * (1.0 - fSlow3 * (0.0 - fRec0[0])));
		iVec0[1] = iVec0[0];
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec11[1] = fRec11[0];
		IOTA0 = IOTA0 + 1;
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
		fRec25[1] = fRec25[0];
		fRec24[1] = fRec24[0];
		fRec8[1] = fRec8[0];
		fRec6[1] = fRec6[0];
		fRec4[1] = fRec4[0];
		fRec2[1] = fRec2[0];
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
#undef fHslider0
#undef fCheckbox0
#undef fVslider0
#undef fVslider1
#undef fVslider2
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	// static const value_pair fCheckbox0_values[] = {{"linear"},{"pingpong"},{0}};
	case INVERT: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case LFOFREQ: 
		fHslider0_ = (float*)data; // , 0.2, 0.0, 5.0, 0.01 
		break;
	case ROOMSIZE: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case DAMP: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.025 
		break;
	case WET_DRY: 
		fVslider0_ = (float*)data; // , 5e+01, 0.0, 1e+02, 1.0 
		break;
	default:
		break;
	}
}

void Dsp::connect_static(uint32_t port,void* data, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->connect(port, data);
}


PluginLV2 *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginLV2 *p)
{
	delete static_cast<Dsp*>(p);
}

/*
typedef enum
{
   LFOFREQ, 
   ROOMSIZE, 
   DAMP, 
   INVERT, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace stereoverb
