// generated from file '../src/LV2/faust/mbc.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace mbc {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT	*fHslider2_;
	double fConst2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT	*fHslider3_;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT	*fHslider4_;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT	*fHslider5_;
	double fVec0[2];
	double fRec15[2];
	double fRec14[3];
	double fVec1[2];
	double fRec13[2];
	double fRec12[3];
	double fVec2[2];
	double fRec11[2];
	double fRec10[3];
	double fVec3[2];
	double fRec9[2];
	double fRec8[3];
	double fRec5[2];
	int iRec6[2];
	double fRec7[2];
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT	*fVbargraph0_;
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT	*fHslider6_;
	double fRec4[2];
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT	*fHslider7_;
	FAUSTFLOAT fHslider8;
	FAUSTFLOAT	*fHslider8_;
	double fRec3[2];
	FAUSTFLOAT fHslider9;
	FAUSTFLOAT	*fHslider9_;
	double fRec16[2];
	double fRec0[2];
	int iRec1[2];
	double fRec2[2];
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT	*fVbargraph1_;
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT	*fHslider10_;
	FAUSTFLOAT fHslider11;
	FAUSTFLOAT	*fHslider11_;
	double fRec27[2];
	double fRec26[3];
	double fRec25[3];
	double fRec22[2];
	int iRec23[2];
	double fRec24[2];
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT	*fVbargraph2_;
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT	*fHslider12_;
	double fRec21[2];
	FAUSTFLOAT fHslider13;
	FAUSTFLOAT	*fHslider13_;
	FAUSTFLOAT fHslider14;
	FAUSTFLOAT	*fHslider14_;
	double fRec20[2];
	FAUSTFLOAT fHslider15;
	FAUSTFLOAT	*fHslider15_;
	double fRec28[2];
	double fRec17[2];
	int iRec18[2];
	double fRec19[2];
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT	*fVbargraph3_;
	FAUSTFLOAT fHslider16;
	FAUSTFLOAT	*fHslider16_;
	FAUSTFLOAT fHslider17;
	FAUSTFLOAT	*fHslider17_;
	double fRec40[2];
	double fRec39[3];
	double fRec38[3];
	double fRec37[3];
	double fRec34[2];
	int iRec35[2];
	double fRec36[2];
	FAUSTFLOAT fVbargraph4;
	FAUSTFLOAT	*fVbargraph4_;
	FAUSTFLOAT fHslider18;
	FAUSTFLOAT	*fHslider18_;
	double fRec33[2];
	FAUSTFLOAT fHslider19;
	FAUSTFLOAT	*fHslider19_;
	FAUSTFLOAT fHslider20;
	FAUSTFLOAT	*fHslider20_;
	double fRec32[2];
	FAUSTFLOAT fHslider21;
	FAUSTFLOAT	*fHslider21_;
	double fRec41[2];
	double fRec29[2];
	int iRec30[2];
	double fRec31[2];
	FAUSTFLOAT fVbargraph5;
	FAUSTFLOAT	*fVbargraph5_;
	FAUSTFLOAT fHslider22;
	FAUSTFLOAT	*fHslider22_;
	FAUSTFLOAT fHslider23;
	FAUSTFLOAT	*fHslider23_;
	double fRec54[2];
	double fRec53[3];
	double fRec52[3];
	double fRec51[3];
	double fRec50[3];
	double fRec47[2];
	int iRec48[2];
	double fRec49[2];
	FAUSTFLOAT fVbargraph6;
	FAUSTFLOAT	*fVbargraph6_;
	FAUSTFLOAT fHslider24;
	FAUSTFLOAT	*fHslider24_;
	double fRec46[2];
	FAUSTFLOAT fHslider25;
	FAUSTFLOAT	*fHslider25_;
	FAUSTFLOAT fHslider26;
	FAUSTFLOAT	*fHslider26_;
	double fRec45[2];
	FAUSTFLOAT fHslider27;
	FAUSTFLOAT	*fHslider27_;
	double fRec55[2];
	double fRec42[2];
	int iRec43[2];
	double fRec44[2];
	FAUSTFLOAT fVbargraph7;
	FAUSTFLOAT	*fVbargraph7_;
	FAUSTFLOAT fHslider28;
	FAUSTFLOAT	*fHslider28_;
	FAUSTFLOAT fHslider29;
	FAUSTFLOAT	*fHslider29_;
	double fRec65[2];
	double fRec64[3];
	double fRec61[2];
	int iRec62[2];
	double fRec63[2];
	FAUSTFLOAT fVbargraph8;
	FAUSTFLOAT	*fVbargraph8_;
	FAUSTFLOAT fHslider30;
	FAUSTFLOAT	*fHslider30_;
	double fRec60[2];
	FAUSTFLOAT fHslider31;
	FAUSTFLOAT	*fHslider31_;
	FAUSTFLOAT fHslider32;
	FAUSTFLOAT	*fHslider32_;
	double fRec59[2];
	FAUSTFLOAT fHslider33;
	FAUSTFLOAT	*fHslider33_;
	double fRec66[2];
	double fRec56[2];
	int iRec57[2];
	double fRec58[2];
	FAUSTFLOAT fVbargraph9;
	FAUSTFLOAT	*fVbargraph9_;

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
	id = "mbc";
	name = N_("Multi Band Compressor");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fVec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec15[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRec14[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fVec1[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec13[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec12[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fVec2[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec11[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec10[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fVec3[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec9[l10] = 0.0;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec8[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec5[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) iRec6[l13] = 0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec7[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec4[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec3[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec16[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec0[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) iRec1[l19] = 0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec2[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec27[l21] = 0.0;
	for (int l22 = 0; l22 < 3; l22 = l22 + 1) fRec26[l22] = 0.0;
	for (int l23 = 0; l23 < 3; l23 = l23 + 1) fRec25[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec22[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) iRec23[l25] = 0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec24[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec21[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec20[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec28[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec17[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) iRec18[l31] = 0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fRec19[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fRec40[l33] = 0.0;
	for (int l34 = 0; l34 < 3; l34 = l34 + 1) fRec39[l34] = 0.0;
	for (int l35 = 0; l35 < 3; l35 = l35 + 1) fRec38[l35] = 0.0;
	for (int l36 = 0; l36 < 3; l36 = l36 + 1) fRec37[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec34[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) iRec35[l38] = 0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec36[l39] = 0.0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec33[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec32[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) fRec41[l42] = 0.0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fRec29[l43] = 0.0;
	for (int l44 = 0; l44 < 2; l44 = l44 + 1) iRec30[l44] = 0;
	for (int l45 = 0; l45 < 2; l45 = l45 + 1) fRec31[l45] = 0.0;
	for (int l46 = 0; l46 < 2; l46 = l46 + 1) fRec54[l46] = 0.0;
	for (int l47 = 0; l47 < 3; l47 = l47 + 1) fRec53[l47] = 0.0;
	for (int l48 = 0; l48 < 3; l48 = l48 + 1) fRec52[l48] = 0.0;
	for (int l49 = 0; l49 < 3; l49 = l49 + 1) fRec51[l49] = 0.0;
	for (int l50 = 0; l50 < 3; l50 = l50 + 1) fRec50[l50] = 0.0;
	for (int l51 = 0; l51 < 2; l51 = l51 + 1) fRec47[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) iRec48[l52] = 0;
	for (int l53 = 0; l53 < 2; l53 = l53 + 1) fRec49[l53] = 0.0;
	for (int l54 = 0; l54 < 2; l54 = l54 + 1) fRec46[l54] = 0.0;
	for (int l55 = 0; l55 < 2; l55 = l55 + 1) fRec45[l55] = 0.0;
	for (int l56 = 0; l56 < 2; l56 = l56 + 1) fRec55[l56] = 0.0;
	for (int l57 = 0; l57 < 2; l57 = l57 + 1) fRec42[l57] = 0.0;
	for (int l58 = 0; l58 < 2; l58 = l58 + 1) iRec43[l58] = 0;
	for (int l59 = 0; l59 < 2; l59 = l59 + 1) fRec44[l59] = 0.0;
	for (int l60 = 0; l60 < 2; l60 = l60 + 1) fRec65[l60] = 0.0;
	for (int l61 = 0; l61 < 3; l61 = l61 + 1) fRec64[l61] = 0.0;
	for (int l62 = 0; l62 < 2; l62 = l62 + 1) fRec61[l62] = 0.0;
	for (int l63 = 0; l63 < 2; l63 = l63 + 1) iRec62[l63] = 0;
	for (int l64 = 0; l64 < 2; l64 = l64 + 1) fRec63[l64] = 0.0;
	for (int l65 = 0; l65 < 2; l65 = l65 + 1) fRec60[l65] = 0.0;
	for (int l66 = 0; l66 < 2; l66 = l66 + 1) fRec59[l66] = 0.0;
	for (int l67 = 0; l67 < 2; l67 = l67 + 1) fRec66[l67] = 0.0;
	for (int l68 = 0; l68 < 2; l68 = l68 + 1) fRec56[l68] = 0.0;
	for (int l69 = 0; l69 < 2; l69 = l69 + 1) iRec57[l69] = 0;
	for (int l70 = 0; l70 < 2; l70 = l70 + 1) fRec58[l70] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 1.0 / fConst0;
	fConst2 = 3.141592653589793 / fConst0;
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
#define fHslider8 (*fHslider8_)
#define fHslider9 (*fHslider9_)
#define fVbargraph1 (*fVbargraph1_)
#define fHslider10 (*fHslider10_)
#define fHslider11 (*fHslider11_)
#define fVbargraph2 (*fVbargraph2_)
#define fHslider12 (*fHslider12_)
#define fHslider13 (*fHslider13_)
#define fHslider14 (*fHslider14_)
#define fHslider15 (*fHslider15_)
#define fVbargraph3 (*fVbargraph3_)
#define fHslider16 (*fHslider16_)
#define fHslider17 (*fHslider17_)
#define fVbargraph4 (*fVbargraph4_)
#define fHslider18 (*fHslider18_)
#define fHslider19 (*fHslider19_)
#define fHslider20 (*fHslider20_)
#define fHslider21 (*fHslider21_)
#define fVbargraph5 (*fVbargraph5_)
#define fHslider22 (*fHslider22_)
#define fHslider23 (*fHslider23_)
#define fVbargraph6 (*fVbargraph6_)
#define fHslider24 (*fHslider24_)
#define fHslider25 (*fHslider25_)
#define fHslider26 (*fHslider26_)
#define fHslider27 (*fHslider27_)
#define fVbargraph7 (*fVbargraph7_)
#define fHslider28 (*fHslider28_)
#define fHslider29 (*fHslider29_)
#define fVbargraph8 (*fVbargraph8_)
#define fHslider30 (*fHslider30_)
#define fHslider31 (*fHslider31_)
#define fHslider32 (*fHslider32_)
#define fHslider33 (*fHslider33_)
#define fVbargraph9 (*fVbargraph9_)
	double fSlow0 = double(fHslider0);
	double fSlow1 = std::max<double>(0.0, fSlow0 + -1.0);
	int iSlow2 = int(fSlow1);
	double fSlow3 = double(fHslider1);
	double fSlow4 = 0.5 * fSlow3;
	int iSlow5 = std::fabs(fSlow4) < 2.220446049250313e-16;
	double fSlow6 = ((iSlow5) ? 0.0 : std::exp(-(fConst1 / ((iSlow5) ? 1.0 : fSlow4))));
	double fSlow7 = std::tan(fConst2 * double(fHslider2));
	double fSlow8 = mydsp_faustpower2_f(fSlow7);
	double fSlow9 = 2.0 * (1.0 - 1.0 / fSlow8);
	double fSlow10 = 1.0 / fSlow7;
	double fSlow11 = (fSlow10 + -1.0000000000000004) / fSlow7 + 1.0;
	double fSlow12 = (fSlow10 + 1.0000000000000004) / fSlow7 + 1.0;
	double fSlow13 = 1.0 / fSlow12;
	double fSlow14 = std::tan(fConst2 * double(fHslider3));
	double fSlow15 = mydsp_faustpower2_f(fSlow14);
	double fSlow16 = 2.0 * (1.0 - 1.0 / fSlow15);
	double fSlow17 = 1.0 / fSlow14;
	double fSlow18 = (fSlow17 + -1.0000000000000004) / fSlow14 + 1.0;
	double fSlow19 = (fSlow17 + 1.0000000000000004) / fSlow14 + 1.0;
	double fSlow20 = 1.0 / fSlow19;
	double fSlow21 = std::tan(fConst2 * double(fHslider4));
	double fSlow22 = mydsp_faustpower2_f(fSlow21);
	double fSlow23 = 2.0 * (1.0 - 1.0 / fSlow22);
	double fSlow24 = 1.0 / fSlow21;
	double fSlow25 = (fSlow24 + -1.0000000000000004) / fSlow21 + 1.0;
	double fSlow26 = (fSlow24 + 1.0000000000000004) / fSlow21 + 1.0;
	double fSlow27 = 1.0 / fSlow26;
	double fSlow28 = std::tan(fConst2 * double(fHslider5));
	double fSlow29 = mydsp_faustpower2_f(fSlow28);
	double fSlow30 = 2.0 * (1.0 - 1.0 / fSlow29);
	double fSlow31 = 1.0 / fSlow28;
	double fSlow32 = (fSlow31 + -1.0000000000000004) / fSlow28 + 1.0;
	double fSlow33 = (fSlow31 + 1.0000000000000004) / fSlow28 + 1.0;
	double fSlow34 = 1.0 / fSlow33;
	double fSlow35 = 1.0 - fSlow31;
	double fSlow36 = 1.0 / (fSlow31 + 1.0);
	double fSlow37 = 1.0 - fSlow24;
	double fSlow38 = fSlow24 + 1.0;
	double fSlow39 = 1.0 / fSlow38;
	double fSlow40 = 1.0 - fSlow17;
	double fSlow41 = fSlow17 + 1.0;
	double fSlow42 = 1.0 / fSlow41;
	double fSlow43 = 1.0 - fSlow10;
	double fSlow44 = fSlow10 + 1.0;
	double fSlow45 = 1.0 / fSlow44;
	double fSlow46 = double(fHslider6);
	int iSlow47 = std::fabs(fSlow46) < 2.220446049250313e-16;
	double fSlow48 = ((iSlow47) ? 0.0 : std::exp(-(fConst1 / ((iSlow47) ? 1.0 : fSlow46))));
	int iSlow49 = std::fabs(fSlow3) < 2.220446049250313e-16;
	double fSlow50 = ((iSlow49) ? 0.0 : std::exp(-(fConst1 / ((iSlow49) ? 1.0 : fSlow3))));
	double fSlow51 = double(fHslider7);
	double fSlow52 = 1.0 - fSlow6;
	double fSlow53 = 1.0 / std::max<double>(2.220446049250313e-16, double(fHslider8)) + -1.0;
	double fSlow54 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (fSlow51 - double(fHslider9)) * std::fabs(fSlow1 + -1.0));
	double fSlow55 = std::fabs(std::max<double>(0.0, fSlow0 + -2.0) + -1.0);
	double fSlow56 = double(fHslider10);
	double fSlow57 = std::max<double>(0.0, fSlow56 + -1.0);
	int iSlow58 = int(fSlow57);
	double fSlow59 = double(fHslider11);
	double fSlow60 = 0.5 * fSlow59;
	int iSlow61 = std::fabs(fSlow60) < 2.220446049250313e-16;
	double fSlow62 = ((iSlow61) ? 0.0 : std::exp(-(fConst1 / ((iSlow61) ? 1.0 : fSlow60))));
	double fSlow63 = 1.0 - fSlow43 / fSlow7;
	double fSlow64 = 1.0 / (fSlow44 / fSlow7 + 1.0);
	double fSlow65 = 1.0 / (fSlow15 * fSlow19);
	double fSlow66 = double(fHslider12);
	int iSlow67 = std::fabs(fSlow66) < 2.220446049250313e-16;
	double fSlow68 = ((iSlow67) ? 0.0 : std::exp(-(fConst1 / ((iSlow67) ? 1.0 : fSlow66))));
	int iSlow69 = std::fabs(fSlow59) < 2.220446049250313e-16;
	double fSlow70 = ((iSlow69) ? 0.0 : std::exp(-(fConst1 / ((iSlow69) ? 1.0 : fSlow59))));
	double fSlow71 = double(fHslider13);
	double fSlow72 = 1.0 - fSlow62;
	double fSlow73 = 1.0 / std::max<double>(2.220446049250313e-16, double(fHslider14)) + -1.0;
	double fSlow74 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (fSlow71 - double(fHslider15)) * std::fabs(fSlow57 + -1.0));
	double fSlow75 = std::fabs(std::max<double>(0.0, fSlow56 + -2.0) + -1.0);
	double fSlow76 = double(fHslider16);
	double fSlow77 = std::max<double>(0.0, fSlow76 + -1.0);
	int iSlow78 = int(fSlow77);
	double fSlow79 = double(fHslider17);
	double fSlow80 = 0.5 * fSlow79;
	int iSlow81 = std::fabs(fSlow80) < 2.220446049250313e-16;
	double fSlow82 = ((iSlow81) ? 0.0 : std::exp(-(fConst1 / ((iSlow81) ? 1.0 : fSlow80))));
	double fSlow83 = 1.0 - fSlow40 / fSlow14;
	double fSlow84 = 1.0 / (fSlow41 / fSlow14 + 1.0);
	double fSlow85 = 1.0 / (fSlow22 * fSlow26);
	double fSlow86 = double(fHslider18);
	int iSlow87 = std::fabs(fSlow86) < 2.220446049250313e-16;
	double fSlow88 = ((iSlow87) ? 0.0 : std::exp(-(fConst1 / ((iSlow87) ? 1.0 : fSlow86))));
	int iSlow89 = std::fabs(fSlow79) < 2.220446049250313e-16;
	double fSlow90 = ((iSlow89) ? 0.0 : std::exp(-(fConst1 / ((iSlow89) ? 1.0 : fSlow79))));
	double fSlow91 = double(fHslider19);
	double fSlow92 = 1.0 - fSlow82;
	double fSlow93 = 1.0 / std::max<double>(2.220446049250313e-16, double(fHslider20)) + -1.0;
	double fSlow94 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (fSlow91 - double(fHslider21)) * std::fabs(fSlow77 + -1.0));
	double fSlow95 = std::fabs(std::max<double>(0.0, fSlow76 + -2.0) + -1.0);
	double fSlow96 = double(fHslider22);
	double fSlow97 = std::max<double>(0.0, fSlow96 + -1.0);
	int iSlow98 = int(fSlow97);
	double fSlow99 = double(fHslider23);
	double fSlow100 = 0.5 * fSlow99;
	int iSlow101 = std::fabs(fSlow100) < 2.220446049250313e-16;
	double fSlow102 = ((iSlow101) ? 0.0 : std::exp(-(fConst1 / ((iSlow101) ? 1.0 : fSlow100))));
	double fSlow103 = 1.0 - fSlow37 / fSlow21;
	double fSlow104 = 1.0 / (fSlow38 / fSlow21 + 1.0);
	double fSlow105 = 1.0 / (fSlow29 * fSlow33);
	double fSlow106 = double(fHslider24);
	int iSlow107 = std::fabs(fSlow106) < 2.220446049250313e-16;
	double fSlow108 = ((iSlow107) ? 0.0 : std::exp(-(fConst1 / ((iSlow107) ? 1.0 : fSlow106))));
	int iSlow109 = std::fabs(fSlow99) < 2.220446049250313e-16;
	double fSlow110 = ((iSlow109) ? 0.0 : std::exp(-(fConst1 / ((iSlow109) ? 1.0 : fSlow99))));
	double fSlow111 = double(fHslider25);
	double fSlow112 = 1.0 - fSlow102;
	double fSlow113 = 1.0 / std::max<double>(2.220446049250313e-16, double(fHslider26)) + -1.0;
	double fSlow114 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (fSlow111 - double(fHslider27)) * std::fabs(fSlow97 + -1.0));
	double fSlow115 = std::fabs(std::max<double>(0.0, fSlow96 + -2.0) + -1.0);
	double fSlow116 = double(fHslider28);
	double fSlow117 = std::max<double>(0.0, fSlow116 + -1.0);
	int iSlow118 = int(fSlow117);
	double fSlow119 = double(fHslider29);
	double fSlow120 = 0.5 * fSlow119;
	int iSlow121 = std::fabs(fSlow120) < 2.220446049250313e-16;
	double fSlow122 = ((iSlow121) ? 0.0 : std::exp(-(fConst1 / ((iSlow121) ? 1.0 : fSlow120))));
	double fSlow123 = 1.0 / (fSlow8 * fSlow12);
	double fSlow124 = double(fHslider30);
	int iSlow125 = std::fabs(fSlow124) < 2.220446049250313e-16;
	double fSlow126 = ((iSlow125) ? 0.0 : std::exp(-(fConst1 / ((iSlow125) ? 1.0 : fSlow124))));
	int iSlow127 = std::fabs(fSlow119) < 2.220446049250313e-16;
	double fSlow128 = ((iSlow127) ? 0.0 : std::exp(-(fConst1 / ((iSlow127) ? 1.0 : fSlow119))));
	double fSlow129 = double(fHslider31);
	double fSlow130 = 1.0 - fSlow122;
	double fSlow131 = 1.0 / std::max<double>(2.220446049250313e-16, double(fHslider32)) + -1.0;
	double fSlow132 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (fSlow129 - double(fHslider33)) * std::fabs(fSlow117 + -1.0));
	double fSlow133 = std::fabs(std::max<double>(0.0, fSlow116 + -2.0) + -1.0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		int iTemp0 = iRec1[1] < 4096;
		int iTemp1 = iRec6[1] < 4096;
		double fTemp2 = double(input0[i0]);
		fVec0[0] = fTemp2;
		fRec15[0] = -(fSlow36 * (fSlow35 * fRec15[1] - (fTemp2 + fVec0[1])));
		fRec14[0] = fRec15[0] - fSlow34 * (fSlow32 * fRec14[2] + fSlow30 * fRec14[1]);
		double fTemp3 = fSlow34 * (fRec14[2] + fRec14[0] + 2.0 * fRec14[1]);
		fVec1[0] = fTemp3;
		fRec13[0] = -(fSlow39 * (fSlow37 * fRec13[1] - (fTemp3 + fVec1[1])));
		fRec12[0] = fRec13[0] - fSlow27 * (fSlow25 * fRec12[2] + fSlow23 * fRec12[1]);
		double fTemp4 = fSlow27 * (fRec12[2] + fRec12[0] + 2.0 * fRec12[1]);
		fVec2[0] = fTemp4;
		fRec11[0] = -(fSlow42 * (fSlow40 * fRec11[1] - (fTemp4 + fVec2[1])));
		fRec10[0] = fRec11[0] - fSlow20 * (fSlow18 * fRec10[2] + fSlow16 * fRec10[1]);
		double fTemp5 = fSlow20 * (fRec10[2] + fRec10[0] + 2.0 * fRec10[1]);
		fVec3[0] = fTemp5;
		fRec9[0] = -(fSlow45 * (fSlow43 * fRec9[1] - (fTemp5 + fVec3[1])));
		fRec8[0] = fRec9[0] - fSlow13 * (fSlow11 * fRec8[2] + fSlow9 * fRec8[1]);
		double fTemp6 = fSlow13 * (fRec8[2] + fRec8[0] + 2.0 * fRec8[1]);
		double fTemp7 = std::max<double>(fConst1, std::fabs(fTemp6));
		fRec5[0] = ((iTemp1) ? std::max<double>(fRec5[1], fTemp7) : fTemp7);
		iRec6[0] = ((iTemp1) ? iRec6[1] + 1 : 1);
		fRec7[0] = ((iTemp1) ? fRec7[1] : fRec5[1]);
		fVbargraph0 = FAUSTFLOAT(fRec7[0]);
		double fTemp8 = fTemp6;
		double fTemp9 = ((iSlow2) ? 0.0 : fTemp8);
		double fTemp10 = std::fabs(fTemp9);
		double fTemp11 = ((fTemp10 > fRec4[1]) ? fSlow50 : fSlow48);
		fRec4[0] = fTemp10 * (1.0 - fTemp11) + fRec4[1] * fTemp11;
		fRec3[0] = fSlow53 * fSlow52 * std::max<double>(fSlow51 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec4[0])), 0.0) + fSlow6 * fRec3[1];
		fRec16[0] = fSlow54 + 0.999 * fRec16[1];
		double fTemp12 = fSlow55 * fRec16[0] * ((iSlow2) ? fTemp8 : fTemp9 * std::pow(1e+01, 0.05 * fRec3[0]));
		double fTemp13 = std::max<double>(fConst1, std::fabs(fTemp12));
		fRec0[0] = ((iTemp0) ? std::max<double>(fRec0[1], fTemp13) : fTemp13);
		iRec1[0] = ((iTemp0) ? iRec1[1] + 1 : 1);
		fRec2[0] = ((iTemp0) ? fRec2[1] : fRec0[1]);
		fVbargraph1 = FAUSTFLOAT(fRec2[0]);
		int iTemp14 = iRec18[1] < 4096;
		int iTemp15 = iRec23[1] < 4096;
		double fTemp16 = fSlow9 * fRec25[1];
		fRec27[0] = -(fSlow42 * (fSlow40 * fRec27[1] - fSlow17 * (fTemp4 - fVec2[1])));
		fRec26[0] = fRec27[0] - fSlow20 * (fSlow18 * fRec26[2] + fSlow16 * fRec26[1]);
		fRec25[0] = fSlow65 * (fRec26[2] + (fRec26[0] - 2.0 * fRec26[1])) - fSlow64 * (fSlow63 * fRec25[2] + fTemp16);
		double fTemp17 = fRec25[2] + fSlow64 * (fTemp16 + fSlow63 * fRec25[0]);
		double fTemp18 = std::max<double>(fConst1, std::fabs(fTemp17));
		fRec22[0] = ((iTemp15) ? std::max<double>(fRec22[1], fTemp18) : fTemp18);
		iRec23[0] = ((iTemp15) ? iRec23[1] + 1 : 1);
		fRec24[0] = ((iTemp15) ? fRec24[1] : fRec22[1]);
		fVbargraph2 = FAUSTFLOAT(fRec24[0]);
		double fTemp19 = fTemp17;
		double fTemp20 = ((iSlow58) ? 0.0 : fTemp19);
		double fTemp21 = std::fabs(fTemp20);
		double fTemp22 = ((fTemp21 > fRec21[1]) ? fSlow70 : fSlow68);
		fRec21[0] = fTemp21 * (1.0 - fTemp22) + fRec21[1] * fTemp22;
		fRec20[0] = fSlow73 * fSlow72 * std::max<double>(fSlow71 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec21[0])), 0.0) + fSlow62 * fRec20[1];
		fRec28[0] = fSlow74 + 0.999 * fRec28[1];
		double fTemp23 = fSlow75 * fRec28[0] * ((iSlow58) ? fTemp19 : fTemp20 * std::pow(1e+01, 0.05 * fRec20[0]));
		double fTemp24 = std::max<double>(fConst1, std::fabs(fTemp23));
		fRec17[0] = ((iTemp14) ? std::max<double>(fRec17[1], fTemp24) : fTemp24);
		iRec18[0] = ((iTemp14) ? iRec18[1] + 1 : 1);
		fRec19[0] = ((iTemp14) ? fRec19[1] : fRec17[1]);
		fVbargraph3 = FAUSTFLOAT(fRec19[0]);
		int iTemp25 = iRec30[1] < 4096;
		int iTemp26 = iRec35[1] < 4096;
		double fTemp27 = fSlow9 * fRec37[1];
		double fTemp28 = fSlow16 * fRec38[1];
		fRec40[0] = -(fSlow39 * (fSlow37 * fRec40[1] - fSlow24 * (fTemp3 - fVec1[1])));
		fRec39[0] = fRec40[0] - fSlow27 * (fSlow25 * fRec39[2] + fSlow23 * fRec39[1]);
		fRec38[0] = fSlow85 * (fRec39[2] + (fRec39[0] - 2.0 * fRec39[1])) - fSlow84 * (fSlow83 * fRec38[2] + fTemp28);
		fRec37[0] = fRec38[2] + fSlow84 * (fTemp28 + fSlow83 * fRec38[0]) - fSlow64 * (fSlow63 * fRec37[2] + fTemp27);
		double fTemp29 = fRec37[2] + fSlow64 * (fTemp27 + fSlow63 * fRec37[0]);
		double fTemp30 = std::max<double>(fConst1, std::fabs(fTemp29));
		fRec34[0] = ((iTemp26) ? std::max<double>(fRec34[1], fTemp30) : fTemp30);
		iRec35[0] = ((iTemp26) ? iRec35[1] + 1 : 1);
		fRec36[0] = ((iTemp26) ? fRec36[1] : fRec34[1]);
		fVbargraph4 = FAUSTFLOAT(fRec36[0]);
		double fTemp31 = fTemp29;
		double fTemp32 = ((iSlow78) ? 0.0 : fTemp31);
		double fTemp33 = std::fabs(fTemp32);
		double fTemp34 = ((fTemp33 > fRec33[1]) ? fSlow90 : fSlow88);
		fRec33[0] = fTemp33 * (1.0 - fTemp34) + fRec33[1] * fTemp34;
		fRec32[0] = fSlow93 * fSlow92 * std::max<double>(fSlow91 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec33[0])), 0.0) + fSlow82 * fRec32[1];
		fRec41[0] = fSlow94 + 0.999 * fRec41[1];
		double fTemp35 = fSlow95 * fRec41[0] * ((iSlow78) ? fTemp31 : fTemp32 * std::pow(1e+01, 0.05 * fRec32[0]));
		double fTemp36 = std::max<double>(fConst1, std::fabs(fTemp35));
		fRec29[0] = ((iTemp25) ? std::max<double>(fRec29[1], fTemp36) : fTemp36);
		iRec30[0] = ((iTemp25) ? iRec30[1] + 1 : 1);
		fRec31[0] = ((iTemp25) ? fRec31[1] : fRec29[1]);
		fVbargraph5 = FAUSTFLOAT(fRec31[0]);
		int iTemp37 = iRec43[1] < 4096;
		int iTemp38 = iRec48[1] < 4096;
		double fTemp39 = fSlow9 * fRec50[1];
		double fTemp40 = fSlow16 * fRec51[1];
		double fTemp41 = fSlow23 * fRec52[1];
		fRec54[0] = -(fSlow36 * (fSlow35 * fRec54[1] - fSlow31 * (fTemp2 - fVec0[1])));
		fRec53[0] = fRec54[0] - fSlow34 * (fSlow32 * fRec53[2] + fSlow30 * fRec53[1]);
		fRec52[0] = fSlow105 * (fRec53[2] + (fRec53[0] - 2.0 * fRec53[1])) - fSlow104 * (fSlow103 * fRec52[2] + fTemp41);
		fRec51[0] = fRec52[2] + fSlow104 * (fTemp41 + fSlow103 * fRec52[0]) - fSlow84 * (fSlow83 * fRec51[2] + fTemp40);
		fRec50[0] = fRec51[2] + fSlow84 * (fTemp40 + fSlow83 * fRec51[0]) - fSlow64 * (fSlow63 * fRec50[2] + fTemp39);
		double fTemp42 = fRec50[2] + fSlow64 * (fTemp39 + fSlow63 * fRec50[0]);
		double fTemp43 = std::max<double>(fConst1, std::fabs(fTemp42));
		fRec47[0] = ((iTemp38) ? std::max<double>(fRec47[1], fTemp43) : fTemp43);
		iRec48[0] = ((iTemp38) ? iRec48[1] + 1 : 1);
		fRec49[0] = ((iTemp38) ? fRec49[1] : fRec47[1]);
		fVbargraph6 = FAUSTFLOAT(fRec49[0]);
		double fTemp44 = fTemp42;
		double fTemp45 = ((iSlow98) ? 0.0 : fTemp44);
		double fTemp46 = std::fabs(fTemp45);
		double fTemp47 = ((fTemp46 > fRec46[1]) ? fSlow110 : fSlow108);
		fRec46[0] = fTemp46 * (1.0 - fTemp47) + fRec46[1] * fTemp47;
		fRec45[0] = fSlow113 * fSlow112 * std::max<double>(fSlow111 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec46[0])), 0.0) + fSlow102 * fRec45[1];
		fRec55[0] = fSlow114 + 0.999 * fRec55[1];
		double fTemp48 = fSlow115 * fRec55[0] * ((iSlow98) ? fTemp44 : fTemp45 * std::pow(1e+01, 0.05 * fRec45[0]));
		double fTemp49 = std::max<double>(fConst1, std::fabs(fTemp48));
		fRec42[0] = ((iTemp37) ? std::max<double>(fRec42[1], fTemp49) : fTemp49);
		iRec43[0] = ((iTemp37) ? iRec43[1] + 1 : 1);
		fRec44[0] = ((iTemp37) ? fRec44[1] : fRec42[1]);
		fVbargraph7 = FAUSTFLOAT(fRec44[0]);
		int iTemp50 = iRec57[1] < 4096;
		int iTemp51 = iRec62[1] < 4096;
		fRec65[0] = -(fSlow45 * (fSlow43 * fRec65[1] - fSlow10 * (fTemp5 - fVec3[1])));
		fRec64[0] = fRec65[0] - fSlow13 * (fSlow11 * fRec64[2] + fSlow9 * fRec64[1]);
		double fTemp52 = 2.0 * fRec64[1];
		double fTemp53 = fSlow123 * (fRec64[2] + (fRec64[0] - fTemp52));
		double fTemp54 = std::max<double>(fConst1, std::fabs(fTemp53));
		fRec61[0] = ((iTemp51) ? std::max<double>(fRec61[1], fTemp54) : fTemp54);
		iRec62[0] = ((iTemp51) ? iRec62[1] + 1 : 1);
		fRec63[0] = ((iTemp51) ? fRec63[1] : fRec61[1]);
		fVbargraph8 = FAUSTFLOAT(fRec63[0]);
		double fTemp55 = fVbargraph8;
		double fTemp56 = fTemp53;
		double fTemp57 = ((iSlow118) ? 0.0 : fTemp56);
		double fTemp58 = std::fabs(fTemp57);
		double fTemp59 = ((fTemp58 > fRec60[1]) ? fSlow128 : fSlow126);
		fRec60[0] = fTemp58 * (1.0 - fTemp59) + fRec60[1] * fTemp59;
		fRec59[0] = fSlow131 * fSlow130 * std::max<double>(fSlow129 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec60[0])), 0.0) + fSlow122 * fRec59[1];
		double fTemp60 = std::pow(1e+01, 0.05 * fRec59[0]);
		fRec66[0] = fSlow132 + 0.999 * fRec66[1];
		double fTemp61 = std::max<double>(fConst1, std::fabs(fSlow133 * fRec66[0] * ((iSlow118) ? fTemp56 : fTemp57 * fTemp60)));
		fRec56[0] = ((iTemp50) ? std::max<double>(fRec56[1], fTemp61) : fTemp61);
		iRec57[0] = ((iTemp50) ? iRec57[1] + 1 : 1);
		fRec58[0] = ((iTemp50) ? fRec58[1] : fRec56[1]);
		fVbargraph9 = FAUSTFLOAT(fRec58[0]);
		double fTemp62 = fSlow123 * (fRec64[0] + fRec64[2] - fTemp52);
		output0[i0] = FAUSTFLOAT(fSlow133 * fRec66[0] * ((iSlow118) ? fTemp62 : fTemp60 * ((iSlow118) ? 0.0 : fTemp62)) + fTemp48 + fTemp35 + fTemp23 + fTemp12);
		fVec0[1] = fVec0[0];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fVec1[1] = fVec1[0];
		fRec13[1] = fRec13[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fVec2[1] = fVec2[0];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fVec3[1] = fVec3[0];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec5[1] = fRec5[0];
		iRec6[1] = iRec6[0];
		fRec7[1] = fRec7[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec16[1] = fRec16[0];
		fRec0[1] = fRec0[0];
		iRec1[1] = iRec1[0];
		fRec2[1] = fRec2[0];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		fRec22[1] = fRec22[0];
		iRec23[1] = iRec23[0];
		fRec24[1] = fRec24[0];
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fRec28[1] = fRec28[0];
		fRec17[1] = fRec17[0];
		iRec18[1] = iRec18[0];
		fRec19[1] = fRec19[0];
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fRec34[1] = fRec34[0];
		iRec35[1] = iRec35[0];
		fRec36[1] = fRec36[0];
		fRec33[1] = fRec33[0];
		fRec32[1] = fRec32[0];
		fRec41[1] = fRec41[0];
		fRec29[1] = fRec29[0];
		iRec30[1] = iRec30[0];
		fRec31[1] = fRec31[0];
		fRec54[1] = fRec54[0];
		fRec53[2] = fRec53[1];
		fRec53[1] = fRec53[0];
		fRec52[2] = fRec52[1];
		fRec52[1] = fRec52[0];
		fRec51[2] = fRec51[1];
		fRec51[1] = fRec51[0];
		fRec50[2] = fRec50[1];
		fRec50[1] = fRec50[0];
		fRec47[1] = fRec47[0];
		iRec48[1] = iRec48[0];
		fRec49[1] = fRec49[0];
		fRec46[1] = fRec46[0];
		fRec45[1] = fRec45[0];
		fRec55[1] = fRec55[0];
		fRec42[1] = fRec42[0];
		iRec43[1] = iRec43[0];
		fRec44[1] = fRec44[0];
		fRec65[1] = fRec65[0];
		fRec64[2] = fRec64[1];
		fRec64[1] = fRec64[0];
		fRec61[1] = fRec61[0];
		iRec62[1] = iRec62[0];
		fRec63[1] = fRec63[0];
		fRec60[1] = fRec60[0];
		fRec59[1] = fRec59[0];
		fRec66[1] = fRec66[0];
		fRec56[1] = fRec56[0];
		iRec57[1] = iRec57[0];
		fRec58[1] = fRec58[0];
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
#undef fHslider8
#undef fHslider9
#undef fVbargraph1
#undef fHslider10
#undef fHslider11
#undef fVbargraph2
#undef fHslider12
#undef fHslider13
#undef fHslider14
#undef fHslider15
#undef fVbargraph3
#undef fHslider16
#undef fHslider17
#undef fVbargraph4
#undef fHslider18
#undef fHslider19
#undef fHslider20
#undef fHslider21
#undef fVbargraph5
#undef fHslider22
#undef fHslider23
#undef fVbargraph6
#undef fHslider24
#undef fHslider25
#undef fHslider26
#undef fHslider27
#undef fVbargraph7
#undef fHslider28
#undef fHslider29
#undef fVbargraph8
#undef fHslider30
#undef fHslider31
#undef fHslider32
#undef fHslider33
#undef fVbargraph9
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	// static const value_pair fHslider0_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE1: 
		fHslider0_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fHslider28_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE2: 
		fHslider28_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fHslider10_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE3: 
		fHslider10_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fHslider16_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE4: 
		fHslider16_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fHslider22_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE5: 
		fHslider22_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	case MAKEUP1: 
		fHslider7_ = (float*)data; // , 13.0, -5e+01, 5e+01, 0.1 
		break;
	case MAKEUP2: 
		fHslider31_ = (float*)data; // , 1e+01, -5e+01, 5e+01, 0.1 
		break;
	case MAKEUP3: 
		fHslider13_ = (float*)data; // , 4.0, -5e+01, 5e+01, 0.1 
		break;
	case MAKEUP4: 
		fHslider19_ = (float*)data; // , 8.0, -5e+01, 5e+01, 0.1 
		break;
	case MAKEUP5: 
		fHslider25_ = (float*)data; // , 11.0, -5e+01, 5e+01, 0.1 
		break;
	case MAKEUPTHRESHOLD1: 
		fHslider9_ = (float*)data; // , 2.0, 0.0, 1e+01, 0.1 
		break;
	case MAKEUPTHRESHOLD2: 
		fHslider33_ = (float*)data; // , 2.0, 0.0, 1e+01, 0.1 
		break;
	case MAKEUPTHRESHOLD3: 
		fHslider15_ = (float*)data; // , 2.0, 0.0, 1e+01, 0.1 
		break;
	case MAKEUPTHRESHOLD4: 
		fHslider21_ = (float*)data; // , 2.0, 0.0, 1e+01, 0.1 
		break;
	case MAKEUPTHRESHOLD5: 
		fHslider27_ = (float*)data; // , 2.0, 0.0, 1e+01, 0.1 
		break;
	case RATIO1: 
		fHslider8_ = (float*)data; // , 2.0, 1.0, 1e+02, 0.1 
		break;
	case RATIO2: 
		fHslider32_ = (float*)data; // , 2.0, 1.0, 1e+02, 0.1 
		break;
	case RATIO3: 
		fHslider14_ = (float*)data; // , 2.0, 1.0, 1e+02, 0.1 
		break;
	case RATIO4: 
		fHslider20_ = (float*)data; // , 2.0, 1.0, 1e+02, 0.1 
		break;
	case RATIO5: 
		fHslider26_ = (float*)data; // , 2.0, 1.0, 1e+02, 0.1 
		break;
	case ATTACK1: 
		fHslider1_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK2: 
		fHslider29_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK3: 
		fHslider11_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK4: 
		fHslider17_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK5: 
		fHslider23_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case RELEASE1: 
		fHslider6_ = (float*)data; // , 1.25, 0.01, 1e+01, 0.01 
		break;
	case RELEASE2: 
		fHslider30_ = (float*)data; // , 1.25, 0.01, 1e+01, 0.01 
		break;
	case RELEASE3: 
		fHslider12_ = (float*)data; // , 1.25, 0.01, 1e+01, 0.01 
		break;
	case RELEASE4: 
		fHslider18_ = (float*)data; // , 1.25, 0.01, 1e+01, 0.01 
		break;
	case RELEASE5: 
		fHslider24_ = (float*)data; // , 1.25, 0.01, 1e+01, 0.01 
		break;
	case CROSSOVER_B1_B2: 
		fHslider2_ = (float*)data; // , 8e+01, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B2_B3: 
		fHslider3_ = (float*)data; // , 2.1e+02, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B3_B4: 
		fHslider4_ = (float*)data; // , 1.7e+03, 2e+01, 2e+04, 1.08 
		break;
	case CROSSOVER_B4_B5: 
		fHslider5_ = (float*)data; // , 5e+03, 2e+01, 2e+04, 1.08 
		break;
	case V10: 
		fVbargraph6_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V1: 
		fVbargraph1_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V2: 
		fVbargraph9_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V3: 
		fVbargraph3_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V4: 
		fVbargraph5_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V5: 
		fVbargraph7_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V6: 
		fVbargraph0_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V7: 
		fVbargraph8_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V8: 
		fVbargraph2_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V9: 
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
   MODE1, 
   MODE2, 
   MODE3, 
   MODE4, 
   MODE5, 
   MAKEUP1, 
   MAKEUP2, 
   MAKEUP3, 
   MAKEUP4, 
   MAKEUP5, 
   MAKEUPTHRESHOLD1, 
   MAKEUPTHRESHOLD2, 
   MAKEUPTHRESHOLD3, 
   MAKEUPTHRESHOLD4, 
   MAKEUPTHRESHOLD5, 
   RATIO1, 
   RATIO2, 
   RATIO3, 
   RATIO4, 
   RATIO5, 
   ATTACK1, 
   ATTACK2, 
   ATTACK3, 
   ATTACK4, 
   ATTACK5, 
   RELEASE1, 
   RELEASE2, 
   RELEASE3, 
   RELEASE4, 
   RELEASE5, 
   CROSSOVER_B1_B2, 
   CROSSOVER_B2_B3, 
   CROSSOVER_B3_B4, 
   CROSSOVER_B4_B5, 
   V10, 
   V1, 
   V2, 
   V3, 
   V4, 
   V5, 
   V6, 
   V7, 
   V8, 
   V9, 
} PortIndex;
*/

} // end namespace mbc
