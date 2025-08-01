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
	double fRec26[2];
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
	double fRec27[2];
	double fRec17[2];
	int iRec18[2];
	double fRec19[2];
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT	*fVbargraph3_;
	FAUSTFLOAT fHslider16;
	FAUSTFLOAT	*fHslider16_;
	FAUSTFLOAT fHslider17;
	FAUSTFLOAT	*fHslider17_;
	double fRec38[2];
	double fRec37[3];
	double fRec36[3];
	double fRec33[2];
	int iRec34[2];
	double fRec35[2];
	FAUSTFLOAT fVbargraph4;
	FAUSTFLOAT	*fVbargraph4_;
	FAUSTFLOAT fHslider18;
	FAUSTFLOAT	*fHslider18_;
	double fRec32[2];
	FAUSTFLOAT fHslider19;
	FAUSTFLOAT	*fHslider19_;
	FAUSTFLOAT fHslider20;
	FAUSTFLOAT	*fHslider20_;
	double fRec31[2];
	FAUSTFLOAT fHslider21;
	FAUSTFLOAT	*fHslider21_;
	double fRec39[2];
	double fRec28[2];
	int iRec29[2];
	double fRec30[2];
	FAUSTFLOAT fVbargraph5;
	FAUSTFLOAT	*fVbargraph5_;
	FAUSTFLOAT fHslider22;
	FAUSTFLOAT	*fHslider22_;
	FAUSTFLOAT fHslider23;
	FAUSTFLOAT	*fHslider23_;
	double fRec51[2];
	double fRec50[3];
	double fRec49[3];
	double fRec48[3];
	double fRec45[2];
	int iRec46[2];
	double fRec47[2];
	FAUSTFLOAT fVbargraph6;
	FAUSTFLOAT	*fVbargraph6_;
	FAUSTFLOAT fHslider24;
	FAUSTFLOAT	*fHslider24_;
	double fRec44[2];
	FAUSTFLOAT fHslider25;
	FAUSTFLOAT	*fHslider25_;
	FAUSTFLOAT fHslider26;
	FAUSTFLOAT	*fHslider26_;
	double fRec43[2];
	FAUSTFLOAT fHslider27;
	FAUSTFLOAT	*fHslider27_;
	double fRec52[2];
	double fRec40[2];
	int iRec41[2];
	double fRec42[2];
	FAUSTFLOAT fVbargraph7;
	FAUSTFLOAT	*fVbargraph7_;
	FAUSTFLOAT fHslider28;
	FAUSTFLOAT	*fHslider28_;
	FAUSTFLOAT fHslider29;
	FAUSTFLOAT	*fHslider29_;
	double fRec65[2];
	double fRec64[3];
	double fRec63[3];
	double fRec62[3];
	double fRec61[3];
	double fRec58[2];
	int iRec59[2];
	double fRec60[2];
	FAUSTFLOAT fVbargraph8;
	FAUSTFLOAT	*fVbargraph8_;
	FAUSTFLOAT fHslider30;
	FAUSTFLOAT	*fHslider30_;
	double fRec57[2];
	FAUSTFLOAT fHslider31;
	FAUSTFLOAT	*fHslider31_;
	FAUSTFLOAT fHslider32;
	FAUSTFLOAT	*fHslider32_;
	double fRec56[2];
	FAUSTFLOAT fHslider33;
	FAUSTFLOAT	*fHslider33_;
	double fRec66[2];
	double fRec53[2];
	int iRec54[2];
	double fRec55[2];
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
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec26[l21] = 0.0;
	for (int l22 = 0; l22 < 3; l22 = l22 + 1) fRec25[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec22[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) iRec23[l24] = 0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec24[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec21[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec20[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec27[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec17[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) iRec18[l30] = 0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec19[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fRec38[l32] = 0.0;
	for (int l33 = 0; l33 < 3; l33 = l33 + 1) fRec37[l33] = 0.0;
	for (int l34 = 0; l34 < 3; l34 = l34 + 1) fRec36[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec33[l35] = 0.0;
	for (int l36 = 0; l36 < 2; l36 = l36 + 1) iRec34[l36] = 0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec35[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fRec32[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec31[l39] = 0.0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec39[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec28[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) iRec29[l42] = 0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fRec30[l43] = 0.0;
	for (int l44 = 0; l44 < 2; l44 = l44 + 1) fRec51[l44] = 0.0;
	for (int l45 = 0; l45 < 3; l45 = l45 + 1) fRec50[l45] = 0.0;
	for (int l46 = 0; l46 < 3; l46 = l46 + 1) fRec49[l46] = 0.0;
	for (int l47 = 0; l47 < 3; l47 = l47 + 1) fRec48[l47] = 0.0;
	for (int l48 = 0; l48 < 2; l48 = l48 + 1) fRec45[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) iRec46[l49] = 0;
	for (int l50 = 0; l50 < 2; l50 = l50 + 1) fRec47[l50] = 0.0;
	for (int l51 = 0; l51 < 2; l51 = l51 + 1) fRec44[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fRec43[l52] = 0.0;
	for (int l53 = 0; l53 < 2; l53 = l53 + 1) fRec52[l53] = 0.0;
	for (int l54 = 0; l54 < 2; l54 = l54 + 1) fRec40[l54] = 0.0;
	for (int l55 = 0; l55 < 2; l55 = l55 + 1) iRec41[l55] = 0;
	for (int l56 = 0; l56 < 2; l56 = l56 + 1) fRec42[l56] = 0.0;
	for (int l57 = 0; l57 < 2; l57 = l57 + 1) fRec65[l57] = 0.0;
	for (int l58 = 0; l58 < 3; l58 = l58 + 1) fRec64[l58] = 0.0;
	for (int l59 = 0; l59 < 3; l59 = l59 + 1) fRec63[l59] = 0.0;
	for (int l60 = 0; l60 < 3; l60 = l60 + 1) fRec62[l60] = 0.0;
	for (int l61 = 0; l61 < 3; l61 = l61 + 1) fRec61[l61] = 0.0;
	for (int l62 = 0; l62 < 2; l62 = l62 + 1) fRec58[l62] = 0.0;
	for (int l63 = 0; l63 < 2; l63 = l63 + 1) iRec59[l63] = 0;
	for (int l64 = 0; l64 < 2; l64 = l64 + 1) fRec60[l64] = 0.0;
	for (int l65 = 0; l65 < 2; l65 = l65 + 1) fRec57[l65] = 0.0;
	for (int l66 = 0; l66 < 2; l66 = l66 + 1) fRec56[l66] = 0.0;
	for (int l67 = 0; l67 < 2; l67 = l67 + 1) fRec66[l67] = 0.0;
	for (int l68 = 0; l68 < 2; l68 = l68 + 1) fRec53[l68] = 0.0;
	for (int l69 = 0; l69 < 2; l69 = l69 + 1) iRec54[l69] = 0;
	for (int l70 = 0; l70 < 2; l70 = l70 + 1) fRec55[l70] = 0.0;
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
	double fSlow63 = 1.0 / (fSlow8 * fSlow12);
	double fSlow64 = double(fHslider12);
	int iSlow65 = std::fabs(fSlow64) < 2.220446049250313e-16;
	double fSlow66 = ((iSlow65) ? 0.0 : std::exp(-(fConst1 / ((iSlow65) ? 1.0 : fSlow64))));
	int iSlow67 = std::fabs(fSlow59) < 2.220446049250313e-16;
	double fSlow68 = ((iSlow67) ? 0.0 : std::exp(-(fConst1 / ((iSlow67) ? 1.0 : fSlow59))));
	double fSlow69 = double(fHslider13);
	double fSlow70 = 1.0 - fSlow62;
	double fSlow71 = 1.0 / std::max<double>(2.220446049250313e-16, double(fHslider14)) + -1.0;
	double fSlow72 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (fSlow69 - double(fHslider15)) * std::fabs(fSlow57 + -1.0));
	double fSlow73 = std::fabs(std::max<double>(0.0, fSlow56 + -2.0) + -1.0);
	double fSlow74 = double(fHslider16);
	double fSlow75 = std::max<double>(0.0, fSlow74 + -1.0);
	int iSlow76 = int(fSlow75);
	double fSlow77 = double(fHslider17);
	double fSlow78 = 0.5 * fSlow77;
	int iSlow79 = std::fabs(fSlow78) < 2.220446049250313e-16;
	double fSlow80 = ((iSlow79) ? 0.0 : std::exp(-(fConst1 / ((iSlow79) ? 1.0 : fSlow78))));
	double fSlow81 = 1.0 - fSlow43 / fSlow7;
	double fSlow82 = 1.0 / (fSlow44 / fSlow7 + 1.0);
	double fSlow83 = 1.0 / (fSlow15 * fSlow19);
	double fSlow84 = double(fHslider18);
	int iSlow85 = std::fabs(fSlow84) < 2.220446049250313e-16;
	double fSlow86 = ((iSlow85) ? 0.0 : std::exp(-(fConst1 / ((iSlow85) ? 1.0 : fSlow84))));
	int iSlow87 = std::fabs(fSlow77) < 2.220446049250313e-16;
	double fSlow88 = ((iSlow87) ? 0.0 : std::exp(-(fConst1 / ((iSlow87) ? 1.0 : fSlow77))));
	double fSlow89 = double(fHslider19);
	double fSlow90 = 1.0 - fSlow80;
	double fSlow91 = 1.0 / std::max<double>(2.220446049250313e-16, double(fHslider20)) + -1.0;
	double fSlow92 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (fSlow89 - double(fHslider21)) * std::fabs(fSlow75 + -1.0));
	double fSlow93 = std::fabs(std::max<double>(0.0, fSlow74 + -2.0) + -1.0);
	double fSlow94 = double(fHslider22);
	double fSlow95 = std::max<double>(0.0, fSlow94 + -1.0);
	int iSlow96 = int(fSlow95);
	double fSlow97 = double(fHslider23);
	double fSlow98 = 0.5 * fSlow97;
	int iSlow99 = std::fabs(fSlow98) < 2.220446049250313e-16;
	double fSlow100 = ((iSlow99) ? 0.0 : std::exp(-(fConst1 / ((iSlow99) ? 1.0 : fSlow98))));
	double fSlow101 = 1.0 - fSlow40 / fSlow14;
	double fSlow102 = 1.0 / (fSlow41 / fSlow14 + 1.0);
	double fSlow103 = 1.0 / (fSlow22 * fSlow26);
	double fSlow104 = double(fHslider24);
	int iSlow105 = std::fabs(fSlow104) < 2.220446049250313e-16;
	double fSlow106 = ((iSlow105) ? 0.0 : std::exp(-(fConst1 / ((iSlow105) ? 1.0 : fSlow104))));
	int iSlow107 = std::fabs(fSlow97) < 2.220446049250313e-16;
	double fSlow108 = ((iSlow107) ? 0.0 : std::exp(-(fConst1 / ((iSlow107) ? 1.0 : fSlow97))));
	double fSlow109 = double(fHslider25);
	double fSlow110 = 1.0 - fSlow100;
	double fSlow111 = 1.0 / std::max<double>(2.220446049250313e-16, double(fHslider26)) + -1.0;
	double fSlow112 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (fSlow109 - double(fHslider27)) * std::fabs(fSlow95 + -1.0));
	double fSlow113 = std::fabs(std::max<double>(0.0, fSlow94 + -2.0) + -1.0);
	double fSlow114 = double(fHslider28);
	double fSlow115 = std::max<double>(0.0, fSlow114 + -1.0);
	int iSlow116 = int(fSlow115);
	double fSlow117 = double(fHslider29);
	double fSlow118 = 0.5 * fSlow117;
	int iSlow119 = std::fabs(fSlow118) < 2.220446049250313e-16;
	double fSlow120 = ((iSlow119) ? 0.0 : std::exp(-(fConst1 / ((iSlow119) ? 1.0 : fSlow118))));
	double fSlow121 = 1.0 - fSlow37 / fSlow21;
	double fSlow122 = 1.0 / (fSlow38 / fSlow21 + 1.0);
	double fSlow123 = 1.0 / (fSlow29 * fSlow33);
	double fSlow124 = double(fHslider30);
	int iSlow125 = std::fabs(fSlow124) < 2.220446049250313e-16;
	double fSlow126 = ((iSlow125) ? 0.0 : std::exp(-(fConst1 / ((iSlow125) ? 1.0 : fSlow124))));
	int iSlow127 = std::fabs(fSlow117) < 2.220446049250313e-16;
	double fSlow128 = ((iSlow127) ? 0.0 : std::exp(-(fConst1 / ((iSlow127) ? 1.0 : fSlow117))));
	double fSlow129 = double(fHslider31);
	double fSlow130 = 1.0 - fSlow120;
	double fSlow131 = 1.0 / std::max<double>(2.220446049250313e-16, double(fHslider32)) + -1.0;
	double fSlow132 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (fSlow129 - double(fHslider33)) * std::fabs(fSlow115 + -1.0));
	double fSlow133 = std::fabs(std::max<double>(0.0, fSlow114 + -2.0) + -1.0);
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
		fRec26[0] = -(fSlow45 * (fSlow43 * fRec26[1] - fSlow10 * (fTemp5 - fVec3[1])));
		fRec25[0] = fRec26[0] - fSlow13 * (fSlow11 * fRec25[2] + fSlow9 * fRec25[1]);
		double fTemp16 = fSlow63 * (fRec25[2] + (fRec25[0] - 2.0 * fRec25[1]));
		double fTemp17 = std::max<double>(fConst1, std::fabs(fTemp16));
		fRec22[0] = ((iTemp15) ? std::max<double>(fRec22[1], fTemp17) : fTemp17);
		iRec23[0] = ((iTemp15) ? iRec23[1] + 1 : 1);
		fRec24[0] = ((iTemp15) ? fRec24[1] : fRec22[1]);
		fVbargraph2 = FAUSTFLOAT(fRec24[0]);
		double fTemp18 = fTemp16;
		double fTemp19 = ((iSlow58) ? 0.0 : fTemp18);
		double fTemp20 = std::fabs(fTemp19);
		double fTemp21 = ((fTemp20 > fRec21[1]) ? fSlow68 : fSlow66);
		fRec21[0] = fTemp20 * (1.0 - fTemp21) + fRec21[1] * fTemp21;
		fRec20[0] = fSlow71 * fSlow70 * std::max<double>(fSlow69 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec21[0])), 0.0) + fSlow62 * fRec20[1];
		fRec27[0] = fSlow72 + 0.999 * fRec27[1];
		double fTemp22 = fSlow73 * fRec27[0] * ((iSlow58) ? fTemp18 : fTemp19 * std::pow(1e+01, 0.05 * fRec20[0]));
		double fTemp23 = std::max<double>(fConst1, std::fabs(fTemp22));
		fRec17[0] = ((iTemp14) ? std::max<double>(fRec17[1], fTemp23) : fTemp23);
		iRec18[0] = ((iTemp14) ? iRec18[1] + 1 : 1);
		fRec19[0] = ((iTemp14) ? fRec19[1] : fRec17[1]);
		fVbargraph3 = FAUSTFLOAT(fRec19[0]);
		int iTemp24 = iRec29[1] < 4096;
		int iTemp25 = iRec34[1] < 4096;
		double fTemp26 = fSlow9 * fRec36[1];
		fRec38[0] = -(fSlow42 * (fSlow40 * fRec38[1] - fSlow17 * (fTemp4 - fVec2[1])));
		fRec37[0] = fRec38[0] - fSlow20 * (fSlow18 * fRec37[2] + fSlow16 * fRec37[1]);
		fRec36[0] = fSlow83 * (fRec37[2] + (fRec37[0] - 2.0 * fRec37[1])) - fSlow82 * (fSlow81 * fRec36[2] + fTemp26);
		double fTemp27 = fRec36[2] + fSlow82 * (fTemp26 + fSlow81 * fRec36[0]);
		double fTemp28 = std::max<double>(fConst1, std::fabs(fTemp27));
		fRec33[0] = ((iTemp25) ? std::max<double>(fRec33[1], fTemp28) : fTemp28);
		iRec34[0] = ((iTemp25) ? iRec34[1] + 1 : 1);
		fRec35[0] = ((iTemp25) ? fRec35[1] : fRec33[1]);
		fVbargraph4 = FAUSTFLOAT(fRec35[0]);
		double fTemp29 = fTemp27;
		double fTemp30 = ((iSlow76) ? 0.0 : fTemp29);
		double fTemp31 = std::fabs(fTemp30);
		double fTemp32 = ((fTemp31 > fRec32[1]) ? fSlow88 : fSlow86);
		fRec32[0] = fTemp31 * (1.0 - fTemp32) + fRec32[1] * fTemp32;
		fRec31[0] = fSlow91 * fSlow90 * std::max<double>(fSlow89 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec32[0])), 0.0) + fSlow80 * fRec31[1];
		fRec39[0] = fSlow92 + 0.999 * fRec39[1];
		double fTemp33 = fSlow93 * fRec39[0] * ((iSlow76) ? fTemp29 : fTemp30 * std::pow(1e+01, 0.05 * fRec31[0]));
		double fTemp34 = std::max<double>(fConst1, std::fabs(fTemp33));
		fRec28[0] = ((iTemp24) ? std::max<double>(fRec28[1], fTemp34) : fTemp34);
		iRec29[0] = ((iTemp24) ? iRec29[1] + 1 : 1);
		fRec30[0] = ((iTemp24) ? fRec30[1] : fRec28[1]);
		fVbargraph5 = FAUSTFLOAT(fRec30[0]);
		int iTemp35 = iRec41[1] < 4096;
		int iTemp36 = iRec46[1] < 4096;
		double fTemp37 = fSlow9 * fRec48[1];
		double fTemp38 = fSlow16 * fRec49[1];
		fRec51[0] = -(fSlow39 * (fSlow37 * fRec51[1] - fSlow24 * (fTemp3 - fVec1[1])));
		fRec50[0] = fRec51[0] - fSlow27 * (fSlow25 * fRec50[2] + fSlow23 * fRec50[1]);
		fRec49[0] = fSlow103 * (fRec50[2] + (fRec50[0] - 2.0 * fRec50[1])) - fSlow102 * (fSlow101 * fRec49[2] + fTemp38);
		fRec48[0] = fRec49[2] + fSlow102 * (fTemp38 + fSlow101 * fRec49[0]) - fSlow82 * (fSlow81 * fRec48[2] + fTemp37);
		double fTemp39 = fRec48[2] + fSlow82 * (fTemp37 + fSlow81 * fRec48[0]);
		double fTemp40 = std::max<double>(fConst1, std::fabs(fTemp39));
		fRec45[0] = ((iTemp36) ? std::max<double>(fRec45[1], fTemp40) : fTemp40);
		iRec46[0] = ((iTemp36) ? iRec46[1] + 1 : 1);
		fRec47[0] = ((iTemp36) ? fRec47[1] : fRec45[1]);
		fVbargraph6 = FAUSTFLOAT(fRec47[0]);
		double fTemp41 = fTemp39;
		double fTemp42 = ((iSlow96) ? 0.0 : fTemp41);
		double fTemp43 = std::fabs(fTemp42);
		double fTemp44 = ((fTemp43 > fRec44[1]) ? fSlow108 : fSlow106);
		fRec44[0] = fTemp43 * (1.0 - fTemp44) + fRec44[1] * fTemp44;
		fRec43[0] = fSlow111 * fSlow110 * std::max<double>(fSlow109 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec44[0])), 0.0) + fSlow100 * fRec43[1];
		fRec52[0] = fSlow112 + 0.999 * fRec52[1];
		double fTemp45 = fSlow113 * fRec52[0] * ((iSlow96) ? fTemp41 : fTemp42 * std::pow(1e+01, 0.05 * fRec43[0]));
		double fTemp46 = std::max<double>(fConst1, std::fabs(fTemp45));
		fRec40[0] = ((iTemp35) ? std::max<double>(fRec40[1], fTemp46) : fTemp46);
		iRec41[0] = ((iTemp35) ? iRec41[1] + 1 : 1);
		fRec42[0] = ((iTemp35) ? fRec42[1] : fRec40[1]);
		fVbargraph7 = FAUSTFLOAT(fRec42[0]);
		int iTemp47 = iRec54[1] < 4096;
		int iTemp48 = iRec59[1] < 4096;
		double fTemp49 = fSlow9 * fRec61[1];
		double fTemp50 = fSlow16 * fRec62[1];
		double fTemp51 = fSlow23 * fRec63[1];
		fRec65[0] = -(fSlow36 * (fSlow35 * fRec65[1] - fSlow31 * (fTemp2 - fVec0[1])));
		fRec64[0] = fRec65[0] - fSlow34 * (fSlow32 * fRec64[2] + fSlow30 * fRec64[1]);
		fRec63[0] = fSlow123 * (fRec64[2] + (fRec64[0] - 2.0 * fRec64[1])) - fSlow122 * (fSlow121 * fRec63[2] + fTemp51);
		fRec62[0] = fRec63[2] + fSlow122 * (fTemp51 + fSlow121 * fRec63[0]) - fSlow102 * (fSlow101 * fRec62[2] + fTemp50);
		fRec61[0] = fRec62[2] + fSlow102 * (fTemp50 + fSlow101 * fRec62[0]) - fSlow82 * (fSlow81 * fRec61[2] + fTemp49);
		double fTemp52 = fRec61[2] + fSlow82 * (fTemp49 + fSlow81 * fRec61[0]);
		double fTemp53 = std::max<double>(fConst1, std::fabs(fTemp52));
		fRec58[0] = ((iTemp48) ? std::max<double>(fRec58[1], fTemp53) : fTemp53);
		iRec59[0] = ((iTemp48) ? iRec59[1] + 1 : 1);
		fRec60[0] = ((iTemp48) ? fRec60[1] : fRec58[1]);
		fVbargraph8 = FAUSTFLOAT(fRec60[0]);
		double fTemp54 = fTemp52;
		double fTemp55 = ((iSlow116) ? 0.0 : fTemp54);
		double fTemp56 = std::fabs(fTemp55);
		double fTemp57 = ((fTemp56 > fRec57[1]) ? fSlow128 : fSlow126);
		fRec57[0] = fTemp56 * (1.0 - fTemp57) + fRec57[1] * fTemp57;
		fRec56[0] = fSlow131 * fSlow130 * std::max<double>(fSlow129 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec57[0])), 0.0) + fSlow120 * fRec56[1];
		fRec66[0] = fSlow132 + 0.999 * fRec66[1];
		double fTemp58 = fSlow133 * fRec66[0] * ((iSlow116) ? fTemp54 : fTemp55 * std::pow(1e+01, 0.05 * fRec56[0]));
		double fTemp59 = std::max<double>(fConst1, std::fabs(fTemp58));
		fRec53[0] = ((iTemp47) ? std::max<double>(fRec53[1], fTemp59) : fTemp59);
		iRec54[0] = ((iTemp47) ? iRec54[1] + 1 : 1);
		fRec55[0] = ((iTemp47) ? fRec55[1] : fRec53[1]);
		fVbargraph9 = FAUSTFLOAT(fRec55[0]);
		output0[i0] = FAUSTFLOAT(fTemp58 + fTemp45 + fTemp33 + fTemp22 + fTemp12);
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
		fRec26[1] = fRec26[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		fRec22[1] = fRec22[0];
		iRec23[1] = iRec23[0];
		fRec24[1] = fRec24[0];
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fRec27[1] = fRec27[0];
		fRec17[1] = fRec17[0];
		iRec18[1] = iRec18[0];
		fRec19[1] = fRec19[0];
		fRec38[1] = fRec38[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		fRec33[1] = fRec33[0];
		iRec34[1] = iRec34[0];
		fRec35[1] = fRec35[0];
		fRec32[1] = fRec32[0];
		fRec31[1] = fRec31[0];
		fRec39[1] = fRec39[0];
		fRec28[1] = fRec28[0];
		iRec29[1] = iRec29[0];
		fRec30[1] = fRec30[0];
		fRec51[1] = fRec51[0];
		fRec50[2] = fRec50[1];
		fRec50[1] = fRec50[0];
		fRec49[2] = fRec49[1];
		fRec49[1] = fRec49[0];
		fRec48[2] = fRec48[1];
		fRec48[1] = fRec48[0];
		fRec45[1] = fRec45[0];
		iRec46[1] = iRec46[0];
		fRec47[1] = fRec47[0];
		fRec44[1] = fRec44[0];
		fRec43[1] = fRec43[0];
		fRec52[1] = fRec52[0];
		fRec40[1] = fRec40[0];
		iRec41[1] = iRec41[0];
		fRec42[1] = fRec42[0];
		fRec65[1] = fRec65[0];
		fRec64[2] = fRec64[1];
		fRec64[1] = fRec64[0];
		fRec63[2] = fRec63[1];
		fRec63[1] = fRec63[0];
		fRec62[2] = fRec62[1];
		fRec62[1] = fRec62[0];
		fRec61[2] = fRec61[1];
		fRec61[1] = fRec61[0];
		fRec58[1] = fRec58[0];
		iRec59[1] = iRec59[0];
		fRec60[1] = fRec60[0];
		fRec57[1] = fRec57[0];
		fRec56[1] = fRec56[0];
		fRec66[1] = fRec66[0];
		fRec53[1] = fRec53[0];
		iRec54[1] = iRec54[0];
		fRec55[1] = fRec55[0];
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
	// static const value_pair fHslider10_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE2: 
		fHslider10_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fHslider16_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE3: 
		fHslider16_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fHslider22_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE4: 
		fHslider22_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fHslider28_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE5: 
		fHslider28_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	case MAKEUP1: 
		fHslider7_ = (float*)data; // , 13.0, -5e+01, 5e+01, 0.1 
		break;
	case MAKEUP2: 
		fHslider13_ = (float*)data; // , 1e+01, -5e+01, 5e+01, 0.1 
		break;
	case MAKEUP3: 
		fHslider19_ = (float*)data; // , 4.0, -5e+01, 5e+01, 0.1 
		break;
	case MAKEUP4: 
		fHslider25_ = (float*)data; // , 8.0, -5e+01, 5e+01, 0.1 
		break;
	case MAKEUP5: 
		fHslider31_ = (float*)data; // , 11.0, -5e+01, 5e+01, 0.1 
		break;
	case MAKEUPTHRESHOLD1: 
		fHslider9_ = (float*)data; // , 2.0, 0.0, 1e+01, 0.1 
		break;
	case MAKEUPTHRESHOLD2: 
		fHslider15_ = (float*)data; // , 2.0, 0.0, 1e+01, 0.1 
		break;
	case MAKEUPTHRESHOLD3: 
		fHslider21_ = (float*)data; // , 2.0, 0.0, 1e+01, 0.1 
		break;
	case MAKEUPTHRESHOLD4: 
		fHslider27_ = (float*)data; // , 2.0, 0.0, 1e+01, 0.1 
		break;
	case MAKEUPTHRESHOLD5: 
		fHslider33_ = (float*)data; // , 2.0, 0.0, 1e+01, 0.1 
		break;
	case RATIO1: 
		fHslider8_ = (float*)data; // , 2.0, 1.0, 1e+02, 0.1 
		break;
	case RATIO2: 
		fHslider14_ = (float*)data; // , 2.0, 1.0, 1e+02, 0.1 
		break;
	case RATIO3: 
		fHslider20_ = (float*)data; // , 2.0, 1.0, 1e+02, 0.1 
		break;
	case RATIO4: 
		fHslider26_ = (float*)data; // , 2.0, 1.0, 1e+02, 0.1 
		break;
	case RATIO5: 
		fHslider32_ = (float*)data; // , 2.0, 1.0, 1e+02, 0.1 
		break;
	case ATTACK1: 
		fHslider1_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK2: 
		fHslider11_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK3: 
		fHslider17_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK4: 
		fHslider23_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK5: 
		fHslider29_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case RELEASE1: 
		fHslider6_ = (float*)data; // , 1.25, 0.01, 1e+01, 0.01 
		break;
	case RELEASE2: 
		fHslider12_ = (float*)data; // , 1.25, 0.01, 1e+01, 0.01 
		break;
	case RELEASE3: 
		fHslider18_ = (float*)data; // , 1.25, 0.01, 1e+01, 0.01 
		break;
	case RELEASE4: 
		fHslider24_ = (float*)data; // , 1.25, 0.01, 1e+01, 0.01 
		break;
	case RELEASE5: 
		fHslider30_ = (float*)data; // , 1.25, 0.01, 1e+01, 0.01 
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
		fVbargraph8_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V1: 
		fVbargraph1_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V2: 
		fVbargraph3_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V3: 
		fVbargraph5_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V4: 
		fVbargraph7_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V5: 
		fVbargraph9_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V6: 
		fVbargraph0_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V7: 
		fVbargraph2_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V8: 
		fVbargraph4_ = (float*)data; // , 0, -7e+01, 5.0, 0 
		break;
	case V9: 
		fVbargraph6_ = (float*)data; // , 0, -7e+01, 5.0, 0 
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
