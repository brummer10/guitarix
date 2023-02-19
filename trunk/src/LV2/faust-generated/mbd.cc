// generated from file '../src/LV2/faust/mbd.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace mbd {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	int iVec0[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	double fConst1;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT	*fHslider2_;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT	*fHslider3_;
	double fRec13[2];
	double fVec1[2];
	double fRec12[2];
	double fRec11[3];
	double fVec2[2];
	double fRec10[2];
	double fRec9[3];
	double fVec3[2];
	double fRec8[2];
	double fRec7[3];
	double fVec4[2];
	double fRec6[2];
	double fRec5[3];
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT	*fHslider4_;
	double fRec14[2];
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT	*fHslider5_;
	double fRec15[2];
	double fVec5[2];
	double fConst4;
	double fRec4[2];
	double fRec1[2];
	int iRec2[2];
	double fRec3[2];
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT	*fVbargraph0_;
	double fRec21[2];
	double fRec20[3];
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT	*fHslider6_;
	double fRec22[2];
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT	*fHslider7_;
	double fRec23[2];
	double fVec6[2];
	double fRec19[2];
	double fRec16[2];
	int iRec17[2];
	double fRec18[2];
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT	*fVbargraph1_;
	double fRec30[2];
	double fRec29[3];
	double fRec28[3];
	FAUSTFLOAT fHslider8;
	FAUSTFLOAT	*fHslider8_;
	double fRec31[2];
	FAUSTFLOAT fHslider9;
	FAUSTFLOAT	*fHslider9_;
	double fRec32[2];
	double fVec7[2];
	double fRec27[2];
	double fRec24[2];
	int iRec25[2];
	double fRec26[2];
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT	*fVbargraph2_;
	double fRec40[2];
	double fRec39[3];
	double fRec38[3];
	double fRec37[3];
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT	*fHslider10_;
	double fRec41[2];
	FAUSTFLOAT fHslider11;
	FAUSTFLOAT	*fHslider11_;
	double fRec42[2];
	double fVec8[2];
	double fRec36[2];
	double fRec33[2];
	int iRec34[2];
	double fRec35[2];
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT	*fVbargraph3_;
	double fRec51[2];
	double fRec50[3];
	double fRec49[3];
	double fRec48[3];
	double fRec47[3];
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT	*fHslider12_;
	double fRec52[2];
	FAUSTFLOAT fHslider13;
	FAUSTFLOAT	*fHslider13_;
	double fRec53[2];
	double fVec9[2];
	double fRec46[2];
	double fRec43[2];
	int iRec44[2];
	double fRec45[2];
	FAUSTFLOAT fVbargraph4;
	FAUSTFLOAT	*fVbargraph4_;

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "mbd";
	name = N_("MultiBand Distortion");
	mono_audio = compute_static;
	stereo_audio = 0;
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
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec13[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fVec1[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec12[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec11[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fVec2[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec10[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec9[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fVec3[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec8[l10] = 0.0;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec7[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fVec4[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec6[l13] = 0.0;
	for (int l14 = 0; l14 < 3; l14 = l14 + 1) fRec5[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec14[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec15[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fVec5[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec4[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec1[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) iRec2[l20] = 0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec3[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec21[l22] = 0.0;
	for (int l23 = 0; l23 < 3; l23 = l23 + 1) fRec20[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec22[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec23[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fVec6[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec19[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec16[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) iRec17[l29] = 0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec18[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec30[l31] = 0.0;
	for (int l32 = 0; l32 < 3; l32 = l32 + 1) fRec29[l32] = 0.0;
	for (int l33 = 0; l33 < 3; l33 = l33 + 1) fRec28[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fRec31[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec32[l35] = 0.0;
	for (int l36 = 0; l36 < 2; l36 = l36 + 1) fVec7[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec27[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fRec24[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) iRec25[l39] = 0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec26[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec40[l41] = 0.0;
	for (int l42 = 0; l42 < 3; l42 = l42 + 1) fRec39[l42] = 0.0;
	for (int l43 = 0; l43 < 3; l43 = l43 + 1) fRec38[l43] = 0.0;
	for (int l44 = 0; l44 < 3; l44 = l44 + 1) fRec37[l44] = 0.0;
	for (int l45 = 0; l45 < 2; l45 = l45 + 1) fRec41[l45] = 0.0;
	for (int l46 = 0; l46 < 2; l46 = l46 + 1) fRec42[l46] = 0.0;
	for (int l47 = 0; l47 < 2; l47 = l47 + 1) fVec8[l47] = 0.0;
	for (int l48 = 0; l48 < 2; l48 = l48 + 1) fRec36[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec33[l49] = 0.0;
	for (int l50 = 0; l50 < 2; l50 = l50 + 1) iRec34[l50] = 0;
	for (int l51 = 0; l51 < 2; l51 = l51 + 1) fRec35[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fRec51[l52] = 0.0;
	for (int l53 = 0; l53 < 3; l53 = l53 + 1) fRec50[l53] = 0.0;
	for (int l54 = 0; l54 < 3; l54 = l54 + 1) fRec49[l54] = 0.0;
	for (int l55 = 0; l55 < 3; l55 = l55 + 1) fRec48[l55] = 0.0;
	for (int l56 = 0; l56 < 3; l56 = l56 + 1) fRec47[l56] = 0.0;
	for (int l57 = 0; l57 < 2; l57 = l57 + 1) fRec52[l57] = 0.0;
	for (int l58 = 0; l58 < 2; l58 = l58 + 1) fRec53[l58] = 0.0;
	for (int l59 = 0; l59 < 2; l59 = l59 + 1) fVec9[l59] = 0.0;
	for (int l60 = 0; l60 < 2; l60 = l60 + 1) fRec46[l60] = 0.0;
	for (int l61 = 0; l61 < 2; l61 = l61 + 1) fRec43[l61] = 0.0;
	for (int l62 = 0; l62 < 2; l62 = l62 + 1) iRec44[l62] = 0;
	for (int l63 = 0; l63 < 2; l63 = l63 + 1) fRec45[l63] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 1.0 / fConst0;
	fConst2 = 3.141592653589793 / fConst0;
	fConst3 = 1.0 - fConst2;
	fConst4 = 1.0 / (fConst2 + 1.0);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fHslider0 (*fHslider0_)
#define fHslider1 (*fHslider1_)
#define fHslider2 (*fHslider2_)
#define fHslider3 (*fHslider3_)
#define fHslider4 (*fHslider4_)
#define fHslider5 (*fHslider5_)
#define fVbargraph0 (*fVbargraph0_)
#define fHslider6 (*fHslider6_)
#define fHslider7 (*fHslider7_)
#define fVbargraph1 (*fVbargraph1_)
#define fHslider8 (*fHslider8_)
#define fHslider9 (*fHslider9_)
#define fVbargraph2 (*fVbargraph2_)
#define fHslider10 (*fHslider10_)
#define fHslider11 (*fHslider11_)
#define fVbargraph3 (*fVbargraph3_)
#define fHslider12 (*fHslider12_)
#define fHslider13 (*fHslider13_)
#define fVbargraph4 (*fVbargraph4_)
	double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
	double fSlow1 = std::tan(fConst2 * double(fHslider0));
	double fSlow2 = mydsp_faustpower2_f(fSlow1);
	double fSlow3 = 1.0 / fSlow2;
	double fSlow4 = 2.0 * (1.0 - fSlow3);
	double fSlow5 = 1.0 / fSlow1;
	double fSlow6 = (fSlow5 + -1.0000000000000004) / fSlow1 + 1.0;
	double fSlow7 = 1.0 / ((fSlow5 + 1.0000000000000004) / fSlow1 + 1.0);
	double fSlow8 = std::tan(fConst2 * double(fHslider1));
	double fSlow9 = mydsp_faustpower2_f(fSlow8);
	double fSlow10 = 1.0 / fSlow9;
	double fSlow11 = 2.0 * (1.0 - fSlow10);
	double fSlow12 = 1.0 / fSlow8;
	double fSlow13 = (fSlow12 + -1.0000000000000004) / fSlow8 + 1.0;
	double fSlow14 = (fSlow12 + 1.0000000000000004) / fSlow8 + 1.0;
	double fSlow15 = 1.0 / fSlow14;
	double fSlow16 = std::tan(fConst2 * double(fHslider2));
	double fSlow17 = mydsp_faustpower2_f(fSlow16);
	double fSlow18 = 1.0 / fSlow17;
	double fSlow19 = 2.0 * (1.0 - fSlow18);
	double fSlow20 = 1.0 / fSlow16;
	double fSlow21 = (fSlow20 + -1.0000000000000004) / fSlow16 + 1.0;
	double fSlow22 = (fSlow20 + 1.0000000000000004) / fSlow16 + 1.0;
	double fSlow23 = 1.0 / fSlow22;
	double fSlow24 = std::tan(fConst2 * double(fHslider3));
	double fSlow25 = mydsp_faustpower2_f(fSlow24);
	double fSlow26 = 1.0 / fSlow25;
	double fSlow27 = 2.0 * (1.0 - fSlow26);
	double fSlow28 = 1.0 / fSlow24;
	double fSlow29 = (fSlow28 + -1.0000000000000004) / fSlow24 + 1.0;
	double fSlow30 = (fSlow28 + 1.0000000000000004) / fSlow24 + 1.0;
	double fSlow31 = 1.0 / fSlow30;
	double fSlow32 = 1.0 - fSlow28;
	double fSlow33 = fSlow28 + 1.0;
	double fSlow34 = 1.0 / fSlow33;
	double fSlow35 = 1.0 - fSlow20;
	double fSlow36 = fSlow20 + 1.0;
	double fSlow37 = 1.0 / fSlow36;
	double fSlow38 = 1.0 - fSlow12;
	double fSlow39 = fSlow12 + 1.0;
	double fSlow40 = 1.0 / fSlow39;
	double fSlow41 = 1.0 - fSlow5;
	double fSlow42 = fSlow5 + 1.0;
	double fSlow43 = 1.0 / fSlow42;
	double fSlow44 = 0.0010000000000000009 * double(fHslider4);
	double fSlow45 = 0.0010000000000000009 * double(fHslider5);
	double fSlow46 = 1.0 / (fSlow1 * fSlow14);
	double fSlow47 = 0.0 - 1.0 / (fSlow1 * fSlow42);
	double fSlow48 = 0.0 - 2.0 / fSlow2;
	double fSlow49 = 0.0010000000000000009 * double(fHslider6);
	double fSlow50 = 0.0010000000000000009 * double(fHslider7);
	double fSlow51 = 1.0 - fSlow41 / fSlow1;
	double fSlow52 = 1.0 / (fSlow42 / fSlow1 + 1.0);
	double fSlow53 = 1.0 / (fSlow8 * fSlow22);
	double fSlow54 = 0.0 - 1.0 / (fSlow8 * fSlow39);
	double fSlow55 = 0.0 - 2.0 / fSlow9;
	double fSlow56 = 0.0010000000000000009 * double(fHslider8);
	double fSlow57 = 0.0010000000000000009 * double(fHslider9);
	double fSlow58 = 1.0 - fSlow38 / fSlow8;
	double fSlow59 = 1.0 / (fSlow39 / fSlow8 + 1.0);
	double fSlow60 = 1.0 / (fSlow30 * fSlow16);
	double fSlow61 = 0.0 - 1.0 / (fSlow16 * fSlow36);
	double fSlow62 = 0.0 - 2.0 / fSlow17;
	double fSlow63 = 0.0010000000000000009 * double(fHslider10);
	double fSlow64 = 0.0010000000000000009 * double(fHslider11);
	double fSlow65 = 1.0 - fSlow35 / fSlow16;
	double fSlow66 = 1.0 / (fSlow36 / fSlow16 + 1.0);
	double fSlow67 = 0.0 - 1.0 / (fSlow24 * fSlow33);
	double fSlow68 = 0.0 - 2.0 / fSlow25;
	double fSlow69 = 0.0010000000000000009 * double(fHslider12);
	double fSlow70 = 0.0010000000000000009 * double(fHslider13);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		iVec0[0] = 1;
		fRec0[0] = fSlow0 + 0.999 * fRec0[1];
		int iTemp0 = iRec2[1] < 4096;
		fRec13[0] = 1e-20 * double(1 - iVec0[1]) - fRec13[1];
		double fTemp1 = double(input0[i0]) + fRec13[0];
		fVec1[0] = fTemp1;
		fRec12[0] = 0.0 - fSlow34 * (fSlow32 * fRec12[1] - (fTemp1 + fVec1[1]));
		fRec11[0] = fRec12[0] - fSlow31 * (fSlow29 * fRec11[2] + fSlow27 * fRec11[1]);
		double fTemp2 = fRec11[2] + fRec11[0] + 2.0 * fRec11[1];
		double fTemp3 = fSlow31 * fTemp2;
		fVec2[0] = fTemp3;
		fRec10[0] = 0.0 - fSlow37 * (fSlow35 * fRec10[1] - (fTemp3 + fVec2[1]));
		fRec9[0] = fRec10[0] - fSlow23 * (fSlow21 * fRec9[2] + fSlow19 * fRec9[1]);
		double fTemp4 = fRec9[2] + fRec9[0] + 2.0 * fRec9[1];
		double fTemp5 = fSlow23 * fTemp4;
		fVec3[0] = fTemp5;
		fRec8[0] = 0.0 - fSlow40 * (fSlow38 * fRec8[1] - (fTemp5 + fVec3[1]));
		fRec7[0] = fRec8[0] - fSlow15 * (fSlow13 * fRec7[2] + fSlow11 * fRec7[1]);
		double fTemp6 = fRec7[2] + fRec7[0] + 2.0 * fRec7[1];
		double fTemp7 = fSlow15 * fTemp6;
		fVec4[0] = fTemp7;
		fRec6[0] = 0.0 - fSlow43 * (fSlow41 * fRec6[1] - (fTemp7 + fVec4[1]));
		fRec5[0] = fRec6[0] - fSlow7 * (fSlow6 * fRec5[2] + fSlow4 * fRec5[1]);
		fRec14[0] = fSlow44 + 0.999 * fRec14[1];
		fRec15[0] = fSlow45 + 0.999 * fRec15[1];
		double fTemp8 = std::max<double>(-1.0, std::min<double>(1.0, fRec15[0] + fSlow7 * std::pow(1e+01, 2.0 * fRec14[0]) * (fRec5[2] + fRec5[0] + 2.0 * fRec5[1])));
		double fTemp9 = fTemp8 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp8));
		fVec5[0] = fTemp9;
		fRec4[0] = fConst4 * (fTemp9 - fVec5[1] + fConst3 * fRec4[1]);
		double fTemp10 = std::max<double>(fConst1, std::fabs(fRec4[0]));
		fRec1[0] = ((iTemp0) ? std::max<double>(fRec1[1], fTemp10) : fTemp10);
		iRec2[0] = ((iTemp0) ? iRec2[1] + 1 : 1);
		fRec3[0] = ((iTemp0) ? fRec3[1] : fRec1[1]);
		fVbargraph0 = FAUSTFLOAT(fRec3[0]);
		int iTemp11 = iRec17[1] < 4096;
		fRec21[0] = fSlow47 * fVec4[1] - fSlow43 * (fSlow41 * fRec21[1] - fSlow46 * fTemp6);
		fRec20[0] = fRec21[0] - fSlow7 * (fSlow6 * fRec20[2] + fSlow4 * fRec20[1]);
		fRec22[0] = fSlow49 + 0.999 * fRec22[1];
		fRec23[0] = fSlow50 + 0.999 * fRec23[1];
		double fTemp12 = std::max<double>(-1.0, std::min<double>(1.0, fRec23[0] + fSlow7 * std::pow(1e+01, 2.0 * fRec22[0]) * (fSlow3 * fRec20[0] + fSlow48 * fRec20[1] + fSlow3 * fRec20[2])));
		double fTemp13 = fTemp12 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp12));
		fVec6[0] = fTemp13;
		fRec19[0] = fConst4 * (fTemp13 - fVec6[1] + fConst3 * fRec19[1]);
		double fTemp14 = std::max<double>(fConst1, std::fabs(fRec19[0]));
		fRec16[0] = ((iTemp11) ? std::max<double>(fRec16[1], fTemp14) : fTemp14);
		iRec17[0] = ((iTemp11) ? iRec17[1] + 1 : 1);
		fRec18[0] = ((iTemp11) ? fRec18[1] : fRec16[1]);
		fVbargraph1 = FAUSTFLOAT(fRec18[0]);
		int iTemp15 = iRec25[1] < 4096;
		double fTemp16 = fSlow4 * fRec28[1];
		fRec30[0] = fSlow54 * fVec3[1] - fSlow40 * (fSlow38 * fRec30[1] - fSlow53 * fTemp4);
		fRec29[0] = fRec30[0] - fSlow15 * (fSlow13 * fRec29[2] + fSlow11 * fRec29[1]);
		fRec28[0] = fSlow15 * (fSlow10 * fRec29[0] + fSlow55 * fRec29[1] + fSlow10 * fRec29[2]) - fSlow52 * (fSlow51 * fRec28[2] + fTemp16);
		fRec31[0] = fSlow56 + 0.999 * fRec31[1];
		fRec32[0] = fSlow57 + 0.999 * fRec32[1];
		double fTemp17 = std::max<double>(-1.0, std::min<double>(1.0, fRec32[0] + std::pow(1e+01, 2.0 * fRec31[0]) * (fRec28[2] + fSlow52 * (fTemp16 + fSlow51 * fRec28[0]))));
		double fTemp18 = fTemp17 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp17));
		fVec7[0] = fTemp18;
		fRec27[0] = fConst4 * (fTemp18 - fVec7[1] + fConst3 * fRec27[1]);
		double fTemp19 = std::max<double>(fConst1, std::fabs(fRec27[0]));
		fRec24[0] = ((iTemp15) ? std::max<double>(fRec24[1], fTemp19) : fTemp19);
		iRec25[0] = ((iTemp15) ? iRec25[1] + 1 : 1);
		fRec26[0] = ((iTemp15) ? fRec26[1] : fRec24[1]);
		fVbargraph2 = FAUSTFLOAT(fRec26[0]);
		int iTemp20 = iRec34[1] < 4096;
		double fTemp21 = fSlow4 * fRec37[1];
		double fTemp22 = fSlow11 * fRec38[1];
		fRec40[0] = fSlow61 * fVec2[1] - fSlow37 * (fSlow35 * fRec40[1] - fSlow60 * fTemp2);
		fRec39[0] = fRec40[0] - fSlow23 * (fSlow21 * fRec39[2] + fSlow19 * fRec39[1]);
		fRec38[0] = fSlow23 * (fSlow18 * fRec39[0] + fSlow62 * fRec39[1] + fSlow18 * fRec39[2]) - fSlow59 * (fSlow58 * fRec38[2] + fTemp22);
		fRec37[0] = fRec38[2] + fSlow59 * (fTemp22 + fSlow58 * fRec38[0]) - fSlow52 * (fSlow51 * fRec37[2] + fTemp21);
		fRec41[0] = fSlow63 + 0.999 * fRec41[1];
		fRec42[0] = fSlow64 + 0.999 * fRec42[1];
		double fTemp23 = std::max<double>(-1.0, std::min<double>(1.0, fRec42[0] + std::pow(1e+01, 2.0 * fRec41[0]) * (fRec37[2] + fSlow52 * (fTemp21 + fSlow51 * fRec37[0]))));
		double fTemp24 = fTemp23 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp23));
		fVec8[0] = fTemp24;
		fRec36[0] = fConst4 * (fTemp24 - fVec8[1] + fConst3 * fRec36[1]);
		double fTemp25 = std::max<double>(fConst1, std::fabs(fRec36[0]));
		fRec33[0] = ((iTemp20) ? std::max<double>(fRec33[1], fTemp25) : fTemp25);
		iRec34[0] = ((iTemp20) ? iRec34[1] + 1 : 1);
		fRec35[0] = ((iTemp20) ? fRec35[1] : fRec33[1]);
		fVbargraph3 = FAUSTFLOAT(fRec35[0]);
		int iTemp26 = iRec44[1] < 4096;
		double fTemp27 = fSlow4 * fRec47[1];
		double fTemp28 = fSlow11 * fRec48[1];
		double fTemp29 = fSlow19 * fRec49[1];
		fRec51[0] = fSlow67 * fVec1[1] - fSlow34 * (fSlow32 * fRec51[1] - fSlow28 * fTemp1);
		fRec50[0] = fRec51[0] - fSlow31 * (fSlow29 * fRec50[2] + fSlow27 * fRec50[1]);
		fRec49[0] = fSlow31 * (fSlow26 * fRec50[0] + fSlow68 * fRec50[1] + fSlow26 * fRec50[2]) - fSlow66 * (fSlow65 * fRec49[2] + fTemp29);
		fRec48[0] = fRec49[2] + fSlow66 * (fTemp29 + fSlow65 * fRec49[0]) - fSlow59 * (fSlow58 * fRec48[2] + fTemp28);
		fRec47[0] = fRec48[2] + fSlow59 * (fTemp28 + fSlow58 * fRec48[0]) - fSlow52 * (fSlow51 * fRec47[2] + fTemp27);
		fRec52[0] = fSlow69 + 0.999 * fRec52[1];
		fRec53[0] = fSlow70 + 0.999 * fRec53[1];
		double fTemp30 = std::max<double>(-1.0, std::min<double>(1.0, fRec53[0] + std::pow(1e+01, 2.0 * fRec52[0]) * (fRec47[2] + fSlow52 * (fTemp27 + fSlow51 * fRec47[0]))));
		double fTemp31 = fTemp30 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp30));
		fVec9[0] = fTemp31;
		fRec46[0] = fConst4 * (fTemp31 - fVec9[1] + fConst3 * fRec46[1]);
		double fTemp32 = std::max<double>(fConst1, std::fabs(fRec46[0]));
		fRec43[0] = ((iTemp26) ? std::max<double>(fRec43[1], fTemp32) : fTemp32);
		iRec44[0] = ((iTemp26) ? iRec44[1] + 1 : 1);
		fRec45[0] = ((iTemp26) ? fRec45[1] : fRec43[1]);
		fVbargraph4 = FAUSTFLOAT(fRec45[0]);
		output0[i0] = FAUSTFLOAT((fRec46[0] + fRec36[0] + fRec27[0] + fRec19[0] + fRec4[0]) * fRec0[0]);
		iVec0[1] = iVec0[0];
		fRec0[1] = fRec0[0];
		fRec13[1] = fRec13[0];
		fVec1[1] = fVec1[0];
		fRec12[1] = fRec12[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fVec2[1] = fVec2[0];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fVec3[1] = fVec3[0];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fVec4[1] = fVec4[0];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec5[1] = fVec5[0];
		fRec4[1] = fRec4[0];
		fRec1[1] = fRec1[0];
		iRec2[1] = iRec2[0];
		fRec3[1] = fRec3[0];
		fRec21[1] = fRec21[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fVec6[1] = fVec6[0];
		fRec19[1] = fRec19[0];
		fRec16[1] = fRec16[0];
		iRec17[1] = iRec17[0];
		fRec18[1] = fRec18[0];
		fRec30[1] = fRec30[0];
		fRec29[2] = fRec29[1];
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fRec31[1] = fRec31[0];
		fRec32[1] = fRec32[0];
		fVec7[1] = fVec7[0];
		fRec27[1] = fRec27[0];
		fRec24[1] = fRec24[0];
		iRec25[1] = iRec25[0];
		fRec26[1] = fRec26[0];
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fRec41[1] = fRec41[0];
		fRec42[1] = fRec42[0];
		fVec8[1] = fVec8[0];
		fRec36[1] = fRec36[0];
		fRec33[1] = fRec33[0];
		iRec34[1] = iRec34[0];
		fRec35[1] = fRec35[0];
		fRec51[1] = fRec51[0];
		fRec50[2] = fRec50[1];
		fRec50[1] = fRec50[0];
		fRec49[2] = fRec49[1];
		fRec49[1] = fRec49[0];
		fRec48[2] = fRec48[1];
		fRec48[1] = fRec48[0];
		fRec47[2] = fRec47[1];
		fRec47[1] = fRec47[0];
		fRec52[1] = fRec52[0];
		fRec53[1] = fRec53[0];
		fVec9[1] = fVec9[0];
		fRec46[1] = fRec46[0];
		fRec43[1] = fRec43[0];
		iRec44[1] = iRec44[0];
		fRec45[1] = fRec45[0];
	}
#undef fVslider0
#undef fHslider0
#undef fHslider1
#undef fHslider2
#undef fHslider3
#undef fHslider4
#undef fHslider5
#undef fVbargraph0
#undef fHslider6
#undef fHslider7
#undef fVbargraph1
#undef fHslider8
#undef fHslider9
#undef fVbargraph2
#undef fHslider10
#undef fHslider11
#undef fVbargraph3
#undef fHslider12
#undef fHslider13
#undef fVbargraph4
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case DRIVE1: 
		fHslider4_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case DRIVE2: 
		fHslider6_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case DRIVE3: 
		fHslider8_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case DRIVE4: 
		fHslider10_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case DRIVE5: 
		fHslider12_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case GAIN: 
		fVslider0_ = (float*)data; // , 0.0, -4e+01, 4.0, 0.1 
		break;
	case OFFSET1: 
		fHslider5_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case OFFSET2: 
		fHslider7_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case OFFSET3: 
		fHslider9_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case OFFSET4: 
		fHslider11_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case OFFSET5: 
		fHslider13_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case CROSSOVER_B1_B2: 
		fHslider0_ = (float*)data; // , 8e+01, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B2_B3: 
		fHslider1_ = (float*)data; // , 2.1e+02, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B3_B4: 
		fHslider2_ = (float*)data; // , 1.7e+03, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B4_B5: 
		fHslider3_ = (float*)data; // , 5e+03, 2e+01, 2e+04, 1.08 
		break;
	case V1: 
		fVbargraph0_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V2: 
		fVbargraph1_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V3: 
		fVbargraph2_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V4: 
		fVbargraph3_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V5: 
		fVbargraph4_ = (float*)data; // , 0, -7e+01, 5.0, 0 
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
   DRIVE1, 
   DRIVE2, 
   DRIVE3, 
   DRIVE4, 
   DRIVE5, 
   GAIN, 
   OFFSET1, 
   OFFSET2, 
   OFFSET3, 
   OFFSET4, 
   OFFSET5, 
   CROSSOVER_B1_B2, 
   CROSSOVER_B2_B3, 
   CROSSOVER_B3_B4, 
   CROSSOVER_B4_B5, 
   V1, 
   V2, 
   V3, 
   V4, 
   V5, 
} PortIndex;
*/

} // end namespace mbd
