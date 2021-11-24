// generated from file '../src/LV2/faust/mbd.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace mbd {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	int iVec0[2];
	double fConst1;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	double fRec4[2];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	double fRec5[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT	*fHslider2_;
	double fRec11[2];
	double fVec1[2];
	double fRec10[2];
	double fRec9[3];
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT	*fHslider3_;
	double fRec8[3];
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT	*fHslider4_;
	double fRec7[3];
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT	*fHslider5_;
	double fRec6[3];
	double fVec2[2];
	double fConst4;
	double fRec3[2];
	double fRec0[2];
	int iRec1[2];
	double fRec2[2];
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT	*fVbargraph0_;
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT	*fHslider6_;
	double fRec16[2];
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT	*fHslider7_;
	double fRec17[2];
	double fRec23[2];
	double fRec22[3];
	double fVec3[2];
	double fRec21[2];
	double fRec20[3];
	double fRec19[3];
	double fRec18[3];
	double fVec4[2];
	double fRec15[2];
	double fRec12[2];
	int iRec13[2];
	double fRec14[2];
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT	*fVbargraph1_;
	FAUSTFLOAT fHslider8;
	FAUSTFLOAT	*fHslider8_;
	double fRec28[2];
	FAUSTFLOAT fHslider9;
	FAUSTFLOAT	*fHslider9_;
	double fRec29[2];
	double fRec34[2];
	double fRec33[3];
	double fVec5[2];
	double fRec32[2];
	double fRec31[3];
	double fRec30[3];
	double fVec6[2];
	double fRec27[2];
	double fRec24[2];
	int iRec25[2];
	double fRec26[2];
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT	*fVbargraph2_;
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT	*fHslider10_;
	double fRec39[2];
	FAUSTFLOAT fHslider11;
	FAUSTFLOAT	*fHslider11_;
	double fRec40[2];
	double fRec44[2];
	double fRec43[3];
	double fVec7[2];
	double fRec42[2];
	double fRec41[3];
	double fVec8[2];
	double fRec38[2];
	double fRec35[2];
	int iRec36[2];
	double fRec37[2];
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT	*fVbargraph3_;
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT	*fHslider12_;
	double fRec49[2];
	FAUSTFLOAT fHslider13;
	FAUSTFLOAT	*fHslider13_;
	double fRec50[2];
	double fRec52[2];
	double fRec51[3];
	double fVec9[2];
	double fRec48[2];
	double fRec45[2];
	int iRec46[2];
	double fRec47[2];
	FAUSTFLOAT fVbargraph4;
	FAUSTFLOAT	*fVbargraph4_;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec53[2];

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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) iVec0[l0] = 0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec4[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec5[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec11[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fVec1[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec10[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec9[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRec8[l7] = 0.0;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec7[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec6[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fVec2[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec3[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec0[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) iRec1[l13] = 0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec2[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec16[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec17[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec23[l17] = 0.0;
	for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) fRec22[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fVec3[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fRec21[l20] = 0.0;
	for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) fRec20[l21] = 0.0;
	for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) fRec19[l22] = 0.0;
	for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) fRec18[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fVec4[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fRec15[l25] = 0.0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fRec12[l26] = 0.0;
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) iRec13[l27] = 0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec14[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fRec28[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec29[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fRec34[l31] = 0.0;
	for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) fRec33[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fVec5[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec32[l34] = 0.0;
	for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) fRec31[l35] = 0.0;
	for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) fRec30[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fVec6[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fRec27[l38] = 0.0;
	for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) fRec24[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) iRec25[l40] = 0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) fRec26[l41] = 0.0;
	for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) fRec39[l42] = 0.0;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fRec40[l43] = 0.0;
	for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) fRec44[l44] = 0.0;
	for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) fRec43[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fVec7[l46] = 0.0;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) fRec42[l47] = 0.0;
	for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) fRec41[l48] = 0.0;
	for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) fVec8[l49] = 0.0;
	for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) fRec38[l50] = 0.0;
	for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) fRec35[l51] = 0.0;
	for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) iRec36[l52] = 0;
	for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) fRec37[l53] = 0.0;
	for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) fRec49[l54] = 0.0;
	for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) fRec50[l55] = 0.0;
	for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) fRec52[l56] = 0.0;
	for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) fRec51[l57] = 0.0;
	for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) fVec9[l58] = 0.0;
	for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) fRec48[l59] = 0.0;
	for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) fRec45[l60] = 0.0;
	for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) iRec46[l61] = 0;
	for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) fRec47[l62] = 0.0;
	for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) fRec53[l63] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (1.0 / fConst0);
	fConst2 = (3.1415926535897931 / fConst0);
	fConst3 = (1.0 / (fConst2 + 1.0));
	fConst4 = (1.0 - fConst2);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
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
#define fVslider0 (*fVslider0_)
	double fSlow0 = (0.0010000000000000009 * double(fHslider0));
	double fSlow1 = (0.0010000000000000009 * double(fHslider1));
	double fSlow2 = std::tan((fConst2 * double(fHslider2)));
	double fSlow3 = (1.0 / fSlow2);
	double fSlow4 = (((fSlow3 + 1.0000000000000004) / fSlow2) + 1.0);
	double fSlow5 = (1.0 / fSlow4);
	double fSlow6 = mydsp_faustpower2_f(fSlow2);
	double fSlow7 = (1.0 / fSlow6);
	double fSlow8 = (fSlow3 + 1.0);
	double fSlow9 = (0.0 - (1.0 / (fSlow2 * fSlow8)));
	double fSlow10 = (1.0 / fSlow8);
	double fSlow11 = (1.0 - fSlow3);
	double fSlow12 = (((fSlow3 + -1.0000000000000004) / fSlow2) + 1.0);
	double fSlow13 = (2.0 * (1.0 - fSlow7));
	double fSlow14 = (0.0 - (2.0 / fSlow6));
	double fSlow15 = std::tan((fConst2 * double(fHslider3)));
	double fSlow16 = (1.0 / fSlow15);
	double fSlow17 = (fSlow16 + 1.0);
	double fSlow18 = (1.0 / ((fSlow17 / fSlow15) + 1.0));
	double fSlow19 = (1.0 - fSlow16);
	double fSlow20 = (1.0 - (fSlow19 / fSlow15));
	double fSlow21 = mydsp_faustpower2_f(fSlow15);
	double fSlow22 = (1.0 / fSlow21);
	double fSlow23 = (2.0 * (1.0 - fSlow22));
	double fSlow24 = std::tan((fConst2 * double(fHslider4)));
	double fSlow25 = (1.0 / fSlow24);
	double fSlow26 = (fSlow25 + 1.0);
	double fSlow27 = (1.0 / ((fSlow26 / fSlow24) + 1.0));
	double fSlow28 = (1.0 - fSlow25);
	double fSlow29 = (1.0 - (fSlow28 / fSlow24));
	double fSlow30 = mydsp_faustpower2_f(fSlow24);
	double fSlow31 = (1.0 / fSlow30);
	double fSlow32 = (2.0 * (1.0 - fSlow31));
	double fSlow33 = std::tan((fConst2 * double(fHslider5)));
	double fSlow34 = (1.0 / fSlow33);
	double fSlow35 = (fSlow34 + 1.0);
	double fSlow36 = (1.0 / ((fSlow35 / fSlow33) + 1.0));
	double fSlow37 = (1.0 - fSlow34);
	double fSlow38 = (1.0 - (fSlow37 / fSlow33));
	double fSlow39 = mydsp_faustpower2_f(fSlow33);
	double fSlow40 = (1.0 / fSlow39);
	double fSlow41 = (2.0 * (1.0 - fSlow40));
	double fSlow42 = (0.0010000000000000009 * double(fHslider6));
	double fSlow43 = (0.0010000000000000009 * double(fHslider7));
	double fSlow44 = (((fSlow16 + 1.0000000000000004) / fSlow15) + 1.0);
	double fSlow45 = (1.0 / fSlow44);
	double fSlow46 = (0.0 - (1.0 / (fSlow15 * fSlow17)));
	double fSlow47 = (1.0 / fSlow17);
	double fSlow48 = (1.0 / (fSlow15 * fSlow4));
	double fSlow49 = (((fSlow16 + -1.0000000000000004) / fSlow15) + 1.0);
	double fSlow50 = (0.0 - (2.0 / fSlow21));
	double fSlow51 = (0.0010000000000000009 * double(fHslider8));
	double fSlow52 = (0.0010000000000000009 * double(fHslider9));
	double fSlow53 = (((fSlow25 + 1.0000000000000004) / fSlow24) + 1.0);
	double fSlow54 = (1.0 / fSlow53);
	double fSlow55 = (0.0 - (1.0 / (fSlow24 * fSlow26)));
	double fSlow56 = (1.0 / fSlow26);
	double fSlow57 = (1.0 / (fSlow24 * fSlow44));
	double fSlow58 = (((fSlow25 + -1.0000000000000004) / fSlow24) + 1.0);
	double fSlow59 = (0.0 - (2.0 / fSlow30));
	double fSlow60 = (0.0010000000000000009 * double(fHslider10));
	double fSlow61 = (1.0 / (((fSlow34 + 1.0000000000000004) / fSlow33) + 1.0));
	double fSlow62 = (0.0010000000000000009 * double(fHslider11));
	double fSlow63 = (0.0 - (1.0 / (fSlow33 * fSlow35)));
	double fSlow64 = (1.0 / fSlow35);
	double fSlow65 = (1.0 / (fSlow33 * fSlow53));
	double fSlow66 = (((fSlow34 + -1.0000000000000004) / fSlow33) + 1.0);
	double fSlow67 = (0.0 - (2.0 / fSlow39));
	double fSlow68 = (0.0010000000000000009 * double(fHslider12));
	double fSlow69 = (0.0010000000000000009 * double(fHslider13));
	double fSlow70 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider0))));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		iVec0[0] = 1;
		int iTemp0 = (iRec1[1] < 4096);
		fRec4[0] = (fSlow0 + (0.999 * fRec4[1]));
		fRec5[0] = (fSlow1 + (0.999 * fRec5[1]));
		fRec11[0] = ((9.9999999999999995e-21 * double((1 - iVec0[1]))) - fRec11[1]);
		double fTemp1 = (double(input0[i0]) + fRec11[0]);
		fVec1[0] = fTemp1;
		fRec10[0] = ((fSlow9 * fVec1[1]) - (fSlow10 * ((fSlow11 * fRec10[1]) - (fSlow3 * fTemp1))));
		fRec9[0] = (fRec10[0] - (fSlow5 * ((fSlow12 * fRec9[2]) + (fSlow13 * fRec9[1]))));
		double fTemp2 = (fSlow23 * fRec8[1]);
		fRec8[0] = ((fSlow5 * (((fSlow7 * fRec9[0]) + (fSlow14 * fRec9[1])) + (fSlow7 * fRec9[2]))) - (fSlow18 * ((fSlow20 * fRec8[2]) + fTemp2)));
		double fTemp3 = (fSlow32 * fRec7[1]);
		fRec7[0] = ((fRec8[2] + (fSlow18 * (fTemp2 + (fSlow20 * fRec8[0])))) - (fSlow27 * ((fSlow29 * fRec7[2]) + fTemp3)));
		double fTemp4 = (fSlow41 * fRec6[1]);
		fRec6[0] = ((fRec7[2] + (fSlow27 * (fTemp3 + (fSlow29 * fRec7[0])))) - (fSlow36 * ((fSlow38 * fRec6[2]) + fTemp4)));
		double fTemp5 = std::max<double>(-1.0, std::min<double>(1.0, (fRec4[0] + (std::pow(10.0, (2.0 * fRec5[0])) * (fRec6[2] + (fSlow36 * (fTemp4 + (fSlow38 * fRec6[0]))))))));
		double fTemp6 = (fTemp5 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp5))));
		fVec2[0] = fTemp6;
		fRec3[0] = (fConst3 * ((fTemp6 - fVec2[1]) + (fConst4 * fRec3[1])));
		double fTemp7 = std::max<double>(fConst1, std::fabs(fRec3[0]));
		fRec0[0] = (iTemp0 ? std::max<double>(fRec0[1], fTemp7) : fTemp7);
		iRec1[0] = (iTemp0 ? (iRec1[1] + 1) : 1);
		fRec2[0] = (iTemp0 ? fRec2[1] : fRec0[1]);
		fVbargraph0 = FAUSTFLOAT(fRec2[0]);
		int iTemp8 = (iRec13[1] < 4096);
		fRec16[0] = (fSlow42 + (0.999 * fRec16[1]));
		fRec17[0] = (fSlow43 + (0.999 * fRec17[1]));
		fRec23[0] = (0.0 - (fSlow10 * ((fSlow11 * fRec23[1]) - (fTemp1 + fVec1[1]))));
		fRec22[0] = (fRec23[0] - (fSlow5 * ((fSlow12 * fRec22[2]) + (fSlow13 * fRec22[1]))));
		double fTemp9 = (fRec22[2] + (fRec22[0] + (2.0 * fRec22[1])));
		double fTemp10 = (fSlow5 * fTemp9);
		fVec3[0] = fTemp10;
		fRec21[0] = ((fSlow46 * fVec3[1]) - (fSlow47 * ((fSlow19 * fRec21[1]) - (fSlow48 * fTemp9))));
		fRec20[0] = (fRec21[0] - (fSlow45 * ((fSlow49 * fRec20[2]) + (fSlow23 * fRec20[1]))));
		double fTemp11 = (fSlow32 * fRec19[1]);
		fRec19[0] = ((fSlow45 * (((fSlow22 * fRec20[0]) + (fSlow50 * fRec20[1])) + (fSlow22 * fRec20[2]))) - (fSlow27 * ((fSlow29 * fRec19[2]) + fTemp11)));
		double fTemp12 = (fSlow41 * fRec18[1]);
		fRec18[0] = ((fRec19[2] + (fSlow27 * (fTemp11 + (fSlow29 * fRec19[0])))) - (fSlow36 * ((fSlow38 * fRec18[2]) + fTemp12)));
		double fTemp13 = std::max<double>(-1.0, std::min<double>(1.0, (fRec16[0] + (std::pow(10.0, (2.0 * fRec17[0])) * (fRec18[2] + (fSlow36 * (fTemp12 + (fSlow38 * fRec18[0]))))))));
		double fTemp14 = (fTemp13 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp13))));
		fVec4[0] = fTemp14;
		fRec15[0] = (fConst3 * ((fTemp14 - fVec4[1]) + (fConst4 * fRec15[1])));
		double fTemp15 = std::max<double>(fConst1, std::fabs(fRec15[0]));
		fRec12[0] = (iTemp8 ? std::max<double>(fRec12[1], fTemp15) : fTemp15);
		iRec13[0] = (iTemp8 ? (iRec13[1] + 1) : 1);
		fRec14[0] = (iTemp8 ? fRec14[1] : fRec12[1]);
		fVbargraph1 = FAUSTFLOAT(fRec14[0]);
		int iTemp16 = (iRec25[1] < 4096);
		fRec28[0] = (fSlow51 + (0.999 * fRec28[1]));
		fRec29[0] = (fSlow52 + (0.999 * fRec29[1]));
		fRec34[0] = (0.0 - (fSlow47 * ((fSlow19 * fRec34[1]) - (fTemp10 + fVec3[1]))));
		fRec33[0] = (fRec34[0] - (fSlow45 * ((fSlow49 * fRec33[2]) + (fSlow23 * fRec33[1]))));
		double fTemp17 = (fRec33[2] + (fRec33[0] + (2.0 * fRec33[1])));
		double fTemp18 = (fSlow45 * fTemp17);
		fVec5[0] = fTemp18;
		fRec32[0] = ((fSlow55 * fVec5[1]) - (fSlow56 * ((fSlow28 * fRec32[1]) - (fSlow57 * fTemp17))));
		fRec31[0] = (fRec32[0] - (fSlow54 * ((fSlow58 * fRec31[2]) + (fSlow32 * fRec31[1]))));
		double fTemp19 = (fSlow41 * fRec30[1]);
		fRec30[0] = ((fSlow54 * (((fSlow31 * fRec31[0]) + (fSlow59 * fRec31[1])) + (fSlow31 * fRec31[2]))) - (fSlow36 * ((fSlow38 * fRec30[2]) + fTemp19)));
		double fTemp20 = std::max<double>(-1.0, std::min<double>(1.0, (fRec28[0] + (std::pow(10.0, (2.0 * fRec29[0])) * (fRec30[2] + (fSlow36 * (fTemp19 + (fSlow38 * fRec30[0]))))))));
		double fTemp21 = (fTemp20 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp20))));
		fVec6[0] = fTemp21;
		fRec27[0] = (fConst3 * ((fTemp21 - fVec6[1]) + (fConst4 * fRec27[1])));
		double fTemp22 = std::max<double>(fConst1, std::fabs(fRec27[0]));
		fRec24[0] = (iTemp16 ? std::max<double>(fRec24[1], fTemp22) : fTemp22);
		iRec25[0] = (iTemp16 ? (iRec25[1] + 1) : 1);
		fRec26[0] = (iTemp16 ? fRec26[1] : fRec24[1]);
		fVbargraph2 = FAUSTFLOAT(fRec26[0]);
		int iTemp23 = (iRec36[1] < 4096);
		fRec39[0] = (fSlow60 + (0.999 * fRec39[1]));
		fRec40[0] = (fSlow62 + (0.999 * fRec40[1]));
		fRec44[0] = (0.0 - (fSlow56 * ((fSlow28 * fRec44[1]) - (fTemp18 + fVec5[1]))));
		fRec43[0] = (fRec44[0] - (fSlow54 * ((fSlow58 * fRec43[2]) + (fSlow32 * fRec43[1]))));
		double fTemp24 = (fRec43[2] + (fRec43[0] + (2.0 * fRec43[1])));
		double fTemp25 = (fSlow54 * fTemp24);
		fVec7[0] = fTemp25;
		fRec42[0] = ((fSlow63 * fVec7[1]) - (fSlow64 * ((fSlow37 * fRec42[1]) - (fSlow65 * fTemp24))));
		fRec41[0] = (fRec42[0] - (fSlow61 * ((fSlow66 * fRec41[2]) + (fSlow41 * fRec41[1]))));
		double fTemp26 = std::max<double>(-1.0, std::min<double>(1.0, (fRec39[0] + (fSlow61 * (std::pow(10.0, (2.0 * fRec40[0])) * (((fSlow40 * fRec41[0]) + (fSlow67 * fRec41[1])) + (fSlow40 * fRec41[2])))))));
		double fTemp27 = (fTemp26 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp26))));
		fVec8[0] = fTemp27;
		fRec38[0] = (fConst3 * ((fTemp27 - fVec8[1]) + (fConst4 * fRec38[1])));
		double fTemp28 = std::max<double>(fConst1, std::fabs(fRec38[0]));
		fRec35[0] = (iTemp23 ? std::max<double>(fRec35[1], fTemp28) : fTemp28);
		iRec36[0] = (iTemp23 ? (iRec36[1] + 1) : 1);
		fRec37[0] = (iTemp23 ? fRec37[1] : fRec35[1]);
		fVbargraph3 = FAUSTFLOAT(fRec37[0]);
		int iTemp29 = (iRec46[1] < 4096);
		fRec49[0] = (fSlow68 + (0.999 * fRec49[1]));
		fRec50[0] = (fSlow69 + (0.999 * fRec50[1]));
		fRec52[0] = (0.0 - (fSlow64 * ((fSlow37 * fRec52[1]) - (fTemp25 + fVec7[1]))));
		fRec51[0] = (fRec52[0] - (fSlow61 * ((fSlow66 * fRec51[2]) + (fSlow41 * fRec51[1]))));
		double fTemp30 = std::max<double>(-1.0, std::min<double>(1.0, (fRec49[0] + (fSlow61 * (std::pow(10.0, (2.0 * fRec50[0])) * (fRec51[2] + (fRec51[0] + (2.0 * fRec51[1]))))))));
		double fTemp31 = (fTemp30 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp30))));
		fVec9[0] = fTemp31;
		fRec48[0] = (fConst3 * ((fTemp31 - fVec9[1]) + (fConst4 * fRec48[1])));
		double fTemp32 = std::max<double>(fConst1, std::fabs(fRec48[0]));
		fRec45[0] = (iTemp29 ? std::max<double>(fRec45[1], fTemp32) : fTemp32);
		iRec46[0] = (iTemp29 ? (iRec46[1] + 1) : 1);
		fRec47[0] = (iTemp29 ? fRec47[1] : fRec45[1]);
		fVbargraph4 = FAUSTFLOAT(fRec47[0]);
		fRec53[0] = (fSlow70 + (0.999 * fRec53[1]));
		output0[i0] = FAUSTFLOAT((((((fRec3[0] + fRec15[0]) + fRec27[0]) + fRec38[0]) + fRec48[0]) * fRec53[0]));
		iVec0[1] = iVec0[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec11[1] = fRec11[0];
		fVec1[1] = fVec1[0];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fVec2[1] = fVec2[0];
		fRec3[1] = fRec3[0];
		fRec0[1] = fRec0[0];
		iRec1[1] = iRec1[0];
		fRec2[1] = fRec2[0];
		fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fVec3[1] = fVec3[0];
		fRec21[1] = fRec21[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fRec18[2] = fRec18[1];
		fRec18[1] = fRec18[0];
		fVec4[1] = fVec4[0];
		fRec15[1] = fRec15[0];
		fRec12[1] = fRec12[0];
		iRec13[1] = iRec13[0];
		fRec14[1] = fRec14[0];
		fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fVec5[1] = fVec5[0];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fVec6[1] = fVec6[0];
		fRec27[1] = fRec27[0];
		fRec24[1] = fRec24[0];
		iRec25[1] = iRec25[0];
		fRec26[1] = fRec26[0];
		fRec39[1] = fRec39[0];
		fRec40[1] = fRec40[0];
		fRec44[1] = fRec44[0];
		fRec43[2] = fRec43[1];
		fRec43[1] = fRec43[0];
		fVec7[1] = fVec7[0];
		fRec42[1] = fRec42[0];
		fRec41[2] = fRec41[1];
		fRec41[1] = fRec41[0];
		fVec8[1] = fVec8[0];
		fRec38[1] = fRec38[0];
		fRec35[1] = fRec35[0];
		iRec36[1] = iRec36[0];
		fRec37[1] = fRec37[0];
		fRec49[1] = fRec49[0];
		fRec50[1] = fRec50[0];
		fRec52[1] = fRec52[0];
		fRec51[2] = fRec51[1];
		fRec51[1] = fRec51[0];
		fVec9[1] = fVec9[0];
		fRec48[1] = fRec48[0];
		fRec45[1] = fRec45[0];
		iRec46[1] = iRec46[0];
		fRec47[1] = fRec47[0];
		fRec53[1] = fRec53[0];
	}
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
#undef fVslider0
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
		fHslider13_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case DRIVE2: 
		fHslider11_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case DRIVE3: 
		fHslider9_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case DRIVE4: 
		fHslider7_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case DRIVE5: 
		fHslider1_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case GAIN: 
		fVslider0_ = (float*)data; // , 0.0, -40.0, 4.0, 0.10000000000000001 
		break;
	case OFFSET1: 
		fHslider12_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case OFFSET2: 
		fHslider10_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case OFFSET3: 
		fHslider8_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case OFFSET4: 
		fHslider6_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case OFFSET5: 
		fHslider0_ = (float*)data; // , 0.0, 0.0, 0.5, 0.01 
		break;
	case CROSSOVER_B1_B2: 
		fHslider5_ = (float*)data; // , 80.0, 20.0, 20000.0, 1.0800000000000001 
		break;
	case CROSSOVER_B2_B3: 
		fHslider4_ = (float*)data; // , 210.0, 20.0, 20000.0, 1.0800000000000001 
		break;
	case CROSSOVER_B3_B4: 
		fHslider3_ = (float*)data; // , 1700.0, 20.0, 20000.0, 1.0800000000000001 
		break;
	case CROSSOVER_B4_B5: 
		fHslider2_ = (float*)data; // , 5000.0, 20.0, 20000.0, 1.0800000000000001 
		break;
	case V1: 
		fVbargraph4_ = (float*)data; // , 0, -70.0, 5.0, 0 
		break;
	case V2: 
		fVbargraph3_ = (float*)data; // , 0, -70.0, 5.0, 0 
		break;
	case V3: 
		fVbargraph2_ = (float*)data; // , 0, -70.0, 5.0, 0 
		break;
	case V4: 
		fVbargraph1_ = (float*)data; // , 0, -70.0, 5.0, 0 
		break;
	case V5: 
		fVbargraph0_ = (float*)data; // , 0, -70.0, 5.0, 0 
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
