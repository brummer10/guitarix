// generated from file '../src/LV2/faust/mbc.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace mbc {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
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
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
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
	double fSlow6 = ((iSlow5) ? 0.0 : std::exp(0.0 - fConst1 / ((iSlow5) ? 1.0 : fSlow4)));
	double fSlow7 = std::tan(fConst2 * double(fHslider2));
	double fSlow8 = mydsp_faustpower2_f(fSlow7);
	double fSlow9 = 1.0 / fSlow8;
	double fSlow10 = 2.0 * (1.0 - fSlow9);
	double fSlow11 = 1.0 / fSlow7;
	double fSlow12 = (fSlow11 + -1.0000000000000004) / fSlow7 + 1.0;
	double fSlow13 = 1.0 / ((fSlow11 + 1.0000000000000004) / fSlow7 + 1.0);
	double fSlow14 = std::tan(fConst2 * double(fHslider3));
	double fSlow15 = mydsp_faustpower2_f(fSlow14);
	double fSlow16 = 1.0 / fSlow15;
	double fSlow17 = 2.0 * (1.0 - fSlow16);
	double fSlow18 = 1.0 / fSlow14;
	double fSlow19 = (fSlow18 + -1.0000000000000004) / fSlow14 + 1.0;
	double fSlow20 = (fSlow18 + 1.0000000000000004) / fSlow14 + 1.0;
	double fSlow21 = 1.0 / fSlow20;
	double fSlow22 = std::tan(fConst2 * double(fHslider4));
	double fSlow23 = mydsp_faustpower2_f(fSlow22);
	double fSlow24 = 1.0 / fSlow23;
	double fSlow25 = 2.0 * (1.0 - fSlow24);
	double fSlow26 = 1.0 / fSlow22;
	double fSlow27 = (fSlow26 + -1.0000000000000004) / fSlow22 + 1.0;
	double fSlow28 = (fSlow26 + 1.0000000000000004) / fSlow22 + 1.0;
	double fSlow29 = 1.0 / fSlow28;
	double fSlow30 = std::tan(fConst2 * double(fHslider5));
	double fSlow31 = mydsp_faustpower2_f(fSlow30);
	double fSlow32 = 1.0 / fSlow31;
	double fSlow33 = 2.0 * (1.0 - fSlow32);
	double fSlow34 = 1.0 / fSlow30;
	double fSlow35 = (fSlow34 + -1.0000000000000004) / fSlow30 + 1.0;
	double fSlow36 = (fSlow34 + 1.0000000000000004) / fSlow30 + 1.0;
	double fSlow37 = 1.0 / fSlow36;
	double fSlow38 = 1.0 - fSlow34;
	double fSlow39 = fSlow34 + 1.0;
	double fSlow40 = 1.0 / fSlow39;
	double fSlow41 = 1.0 - fSlow26;
	double fSlow42 = fSlow26 + 1.0;
	double fSlow43 = 1.0 / fSlow42;
	double fSlow44 = 1.0 - fSlow18;
	double fSlow45 = fSlow18 + 1.0;
	double fSlow46 = 1.0 / fSlow45;
	double fSlow47 = 1.0 - fSlow11;
	double fSlow48 = fSlow11 + 1.0;
	double fSlow49 = 1.0 / fSlow48;
	double fSlow50 = double(fHslider6);
	int iSlow51 = std::fabs(fSlow50) < 2.220446049250313e-16;
	double fSlow52 = ((iSlow51) ? 0.0 : std::exp(0.0 - fConst1 / ((iSlow51) ? 1.0 : fSlow50)));
	int iSlow53 = std::fabs(fSlow3) < 2.220446049250313e-16;
	double fSlow54 = ((iSlow53) ? 0.0 : std::exp(0.0 - fConst1 / ((iSlow53) ? 1.0 : fSlow3)));
	double fSlow55 = double(fHslider7);
	double fSlow56 = 1.0 - fSlow6;
	double fSlow57 = 1.0 / std::max<double>(2.220446049250313e-16, double(fHslider8)) + -1.0;
	double fSlow58 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (fSlow55 - double(fHslider9)) * std::fabs(fSlow1 + -1.0));
	double fSlow59 = std::fabs(std::max<double>(0.0, fSlow0 + -2.0) + -1.0);
	double fSlow60 = double(fHslider10);
	double fSlow61 = std::max<double>(0.0, fSlow60 + -1.0);
	int iSlow62 = int(fSlow61);
	double fSlow63 = double(fHslider11);
	double fSlow64 = 0.5 * fSlow63;
	int iSlow65 = std::fabs(fSlow64) < 2.220446049250313e-16;
	double fSlow66 = ((iSlow65) ? 0.0 : std::exp(0.0 - fConst1 / ((iSlow65) ? 1.0 : fSlow64)));
	double fSlow67 = 1.0 / (fSlow7 * fSlow20);
	double fSlow68 = 0.0 - 1.0 / (fSlow7 * fSlow48);
	double fSlow69 = 0.0 - 2.0 / fSlow8;
	double fSlow70 = double(fHslider12);
	int iSlow71 = std::fabs(fSlow70) < 2.220446049250313e-16;
	double fSlow72 = ((iSlow71) ? 0.0 : std::exp(0.0 - fConst1 / ((iSlow71) ? 1.0 : fSlow70)));
	int iSlow73 = std::fabs(fSlow63) < 2.220446049250313e-16;
	double fSlow74 = ((iSlow73) ? 0.0 : std::exp(0.0 - fConst1 / ((iSlow73) ? 1.0 : fSlow63)));
	double fSlow75 = double(fHslider13);
	double fSlow76 = 1.0 - fSlow66;
	double fSlow77 = 1.0 / std::max<double>(2.220446049250313e-16, double(fHslider14)) + -1.0;
	double fSlow78 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (fSlow75 - double(fHslider15)) * std::fabs(fSlow61 + -1.0));
	double fSlow79 = std::fabs(std::max<double>(0.0, fSlow60 + -2.0) + -1.0);
	double fSlow80 = double(fHslider16);
	double fSlow81 = std::max<double>(0.0, fSlow80 + -1.0);
	int iSlow82 = int(fSlow81);
	double fSlow83 = double(fHslider17);
	double fSlow84 = 0.5 * fSlow83;
	int iSlow85 = std::fabs(fSlow84) < 2.220446049250313e-16;
	double fSlow86 = ((iSlow85) ? 0.0 : std::exp(0.0 - fConst1 / ((iSlow85) ? 1.0 : fSlow84)));
	double fSlow87 = 1.0 - fSlow47 / fSlow7;
	double fSlow88 = 1.0 / (fSlow48 / fSlow7 + 1.0);
	double fSlow89 = 1.0 / (fSlow14 * fSlow28);
	double fSlow90 = 0.0 - 1.0 / (fSlow14 * fSlow45);
	double fSlow91 = 0.0 - 2.0 / fSlow15;
	double fSlow92 = double(fHslider18);
	int iSlow93 = std::fabs(fSlow92) < 2.220446049250313e-16;
	double fSlow94 = ((iSlow93) ? 0.0 : std::exp(0.0 - fConst1 / ((iSlow93) ? 1.0 : fSlow92)));
	int iSlow95 = std::fabs(fSlow83) < 2.220446049250313e-16;
	double fSlow96 = ((iSlow95) ? 0.0 : std::exp(0.0 - fConst1 / ((iSlow95) ? 1.0 : fSlow83)));
	double fSlow97 = double(fHslider19);
	double fSlow98 = 1.0 - fSlow86;
	double fSlow99 = 1.0 / std::max<double>(2.220446049250313e-16, double(fHslider20)) + -1.0;
	double fSlow100 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (fSlow97 - double(fHslider21)) * std::fabs(fSlow81 + -1.0));
	double fSlow101 = std::fabs(std::max<double>(0.0, fSlow80 + -2.0) + -1.0);
	double fSlow102 = double(fHslider22);
	double fSlow103 = std::max<double>(0.0, fSlow102 + -1.0);
	int iSlow104 = int(fSlow103);
	double fSlow105 = double(fHslider23);
	double fSlow106 = 0.5 * fSlow105;
	int iSlow107 = std::fabs(fSlow106) < 2.220446049250313e-16;
	double fSlow108 = ((iSlow107) ? 0.0 : std::exp(0.0 - fConst1 / ((iSlow107) ? 1.0 : fSlow106)));
	double fSlow109 = 1.0 - fSlow44 / fSlow14;
	double fSlow110 = 1.0 / (fSlow45 / fSlow14 + 1.0);
	double fSlow111 = 1.0 / (fSlow36 * fSlow22);
	double fSlow112 = 0.0 - 1.0 / (fSlow22 * fSlow42);
	double fSlow113 = 0.0 - 2.0 / fSlow23;
	double fSlow114 = double(fHslider24);
	int iSlow115 = std::fabs(fSlow114) < 2.220446049250313e-16;
	double fSlow116 = ((iSlow115) ? 0.0 : std::exp(0.0 - fConst1 / ((iSlow115) ? 1.0 : fSlow114)));
	int iSlow117 = std::fabs(fSlow105) < 2.220446049250313e-16;
	double fSlow118 = ((iSlow117) ? 0.0 : std::exp(0.0 - fConst1 / ((iSlow117) ? 1.0 : fSlow105)));
	double fSlow119 = double(fHslider25);
	double fSlow120 = 1.0 - fSlow108;
	double fSlow121 = 1.0 / std::max<double>(2.220446049250313e-16, double(fHslider26)) + -1.0;
	double fSlow122 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (fSlow119 - double(fHslider27)) * std::fabs(fSlow103 + -1.0));
	double fSlow123 = std::fabs(std::max<double>(0.0, fSlow102 + -2.0) + -1.0);
	double fSlow124 = double(fHslider28);
	double fSlow125 = std::max<double>(0.0, fSlow124 + -1.0);
	int iSlow126 = int(fSlow125);
	double fSlow127 = double(fHslider29);
	double fSlow128 = 0.5 * fSlow127;
	int iSlow129 = std::fabs(fSlow128) < 2.220446049250313e-16;
	double fSlow130 = ((iSlow129) ? 0.0 : std::exp(0.0 - fConst1 / ((iSlow129) ? 1.0 : fSlow128)));
	double fSlow131 = 1.0 - fSlow41 / fSlow22;
	double fSlow132 = 1.0 / (fSlow42 / fSlow22 + 1.0);
	double fSlow133 = 0.0 - 1.0 / (fSlow30 * fSlow39);
	double fSlow134 = 0.0 - 2.0 / fSlow31;
	double fSlow135 = double(fHslider30);
	int iSlow136 = std::fabs(fSlow135) < 2.220446049250313e-16;
	double fSlow137 = ((iSlow136) ? 0.0 : std::exp(0.0 - fConst1 / ((iSlow136) ? 1.0 : fSlow135)));
	int iSlow138 = std::fabs(fSlow127) < 2.220446049250313e-16;
	double fSlow139 = ((iSlow138) ? 0.0 : std::exp(0.0 - fConst1 / ((iSlow138) ? 1.0 : fSlow127)));
	double fSlow140 = double(fHslider31);
	double fSlow141 = 1.0 - fSlow130;
	double fSlow142 = 1.0 / std::max<double>(2.220446049250313e-16, double(fHslider32)) + -1.0;
	double fSlow143 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (fSlow140 - double(fHslider33)) * std::fabs(fSlow125 + -1.0));
	double fSlow144 = std::fabs(std::max<double>(0.0, fSlow124 + -2.0) + -1.0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		int iTemp0 = iRec1[1] < 4096;
		int iTemp1 = iRec6[1] < 4096;
		double fTemp2 = double(input0[i0]);
		fVec0[0] = fTemp2;
		fRec15[0] = 0.0 - fSlow40 * (fSlow38 * fRec15[1] - (fTemp2 + fVec0[1]));
		fRec14[0] = fRec15[0] - fSlow37 * (fSlow35 * fRec14[2] + fSlow33 * fRec14[1]);
		double fTemp3 = fRec14[2] + fRec14[0] + 2.0 * fRec14[1];
		double fTemp4 = fSlow37 * fTemp3;
		fVec1[0] = fTemp4;
		fRec13[0] = 0.0 - fSlow43 * (fSlow41 * fRec13[1] - (fTemp4 + fVec1[1]));
		fRec12[0] = fRec13[0] - fSlow29 * (fSlow27 * fRec12[2] + fSlow25 * fRec12[1]);
		double fTemp5 = fRec12[2] + fRec12[0] + 2.0 * fRec12[1];
		double fTemp6 = fSlow29 * fTemp5;
		fVec2[0] = fTemp6;
		fRec11[0] = 0.0 - fSlow46 * (fSlow44 * fRec11[1] - (fTemp6 + fVec2[1]));
		fRec10[0] = fRec11[0] - fSlow21 * (fSlow19 * fRec10[2] + fSlow17 * fRec10[1]);
		double fTemp7 = fRec10[2] + fRec10[0] + 2.0 * fRec10[1];
		double fTemp8 = fSlow21 * fTemp7;
		fVec3[0] = fTemp8;
		fRec9[0] = 0.0 - fSlow49 * (fSlow47 * fRec9[1] - (fTemp8 + fVec3[1]));
		fRec8[0] = fRec9[0] - fSlow13 * (fSlow12 * fRec8[2] + fSlow10 * fRec8[1]);
		double fTemp9 = fSlow13 * (fRec8[2] + fRec8[0] + 2.0 * fRec8[1]);
		double fTemp10 = std::max<double>(fConst1, std::fabs(fTemp9));
		fRec5[0] = ((iTemp1) ? std::max<double>(fRec5[1], fTemp10) : fTemp10);
		iRec6[0] = ((iTemp1) ? iRec6[1] + 1 : 1);
		fRec7[0] = ((iTemp1) ? fRec7[1] : fRec5[1]);
		fVbargraph0 = FAUSTFLOAT(fRec7[0]);
		double fTemp11 = fTemp9;
		double fTemp12 = ((iSlow2) ? 0.0 : fTemp11);
		double fTemp13 = std::fabs(fTemp12);
		double fTemp14 = ((fTemp13 > fRec4[1]) ? fSlow54 : fSlow52);
		fRec4[0] = fTemp13 * (1.0 - fTemp14) + fRec4[1] * fTemp14;
		fRec3[0] = fSlow57 * fSlow56 * std::max<double>(fSlow55 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec4[0])), 0.0) + fSlow6 * fRec3[1];
		fRec16[0] = fSlow58 + 0.999 * fRec16[1];
		double fTemp15 = fSlow59 * fRec16[0] * ((iSlow2) ? fTemp11 : fTemp12 * std::pow(1e+01, 0.05 * fRec3[0]));
		double fTemp16 = std::max<double>(fConst1, std::fabs(fTemp15));
		fRec0[0] = ((iTemp0) ? std::max<double>(fRec0[1], fTemp16) : fTemp16);
		iRec1[0] = ((iTemp0) ? iRec1[1] + 1 : 1);
		fRec2[0] = ((iTemp0) ? fRec2[1] : fRec0[1]);
		fVbargraph1 = FAUSTFLOAT(fRec2[0]);
		int iTemp17 = iRec18[1] < 4096;
		int iTemp18 = iRec23[1] < 4096;
		fRec26[0] = fSlow68 * fVec3[1] - fSlow49 * (fSlow47 * fRec26[1] - fSlow67 * fTemp7);
		fRec25[0] = fRec26[0] - fSlow13 * (fSlow12 * fRec25[2] + fSlow10 * fRec25[1]);
		double fTemp19 = fSlow13 * (fSlow9 * fRec25[0] + fSlow69 * fRec25[1] + fSlow9 * fRec25[2]);
		double fTemp20 = std::max<double>(fConst1, std::fabs(fTemp19));
		fRec22[0] = ((iTemp18) ? std::max<double>(fRec22[1], fTemp20) : fTemp20);
		iRec23[0] = ((iTemp18) ? iRec23[1] + 1 : 1);
		fRec24[0] = ((iTemp18) ? fRec24[1] : fRec22[1]);
		fVbargraph2 = FAUSTFLOAT(fRec24[0]);
		double fTemp21 = fTemp19;
		double fTemp22 = ((iSlow62) ? 0.0 : fTemp21);
		double fTemp23 = std::fabs(fTemp22);
		double fTemp24 = ((fTemp23 > fRec21[1]) ? fSlow74 : fSlow72);
		fRec21[0] = fTemp23 * (1.0 - fTemp24) + fRec21[1] * fTemp24;
		fRec20[0] = fSlow77 * fSlow76 * std::max<double>(fSlow75 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec21[0])), 0.0) + fSlow66 * fRec20[1];
		fRec27[0] = fSlow78 + 0.999 * fRec27[1];
		double fTemp25 = fSlow79 * fRec27[0] * ((iSlow62) ? fTemp21 : fTemp22 * std::pow(1e+01, 0.05 * fRec20[0]));
		double fTemp26 = std::max<double>(fConst1, std::fabs(fTemp25));
		fRec17[0] = ((iTemp17) ? std::max<double>(fRec17[1], fTemp26) : fTemp26);
		iRec18[0] = ((iTemp17) ? iRec18[1] + 1 : 1);
		fRec19[0] = ((iTemp17) ? fRec19[1] : fRec17[1]);
		fVbargraph3 = FAUSTFLOAT(fRec19[0]);
		int iTemp27 = iRec29[1] < 4096;
		int iTemp28 = iRec34[1] < 4096;
		double fTemp29 = fSlow10 * fRec36[1];
		fRec38[0] = fSlow90 * fVec2[1] - fSlow46 * (fSlow44 * fRec38[1] - fSlow89 * fTemp5);
		fRec37[0] = fRec38[0] - fSlow21 * (fSlow19 * fRec37[2] + fSlow17 * fRec37[1]);
		fRec36[0] = fSlow21 * (fSlow16 * fRec37[0] + fSlow91 * fRec37[1] + fSlow16 * fRec37[2]) - fSlow88 * (fSlow87 * fRec36[2] + fTemp29);
		double fTemp30 = fRec36[2] + fSlow88 * (fTemp29 + fSlow87 * fRec36[0]);
		double fTemp31 = std::max<double>(fConst1, std::fabs(fTemp30));
		fRec33[0] = ((iTemp28) ? std::max<double>(fRec33[1], fTemp31) : fTemp31);
		iRec34[0] = ((iTemp28) ? iRec34[1] + 1 : 1);
		fRec35[0] = ((iTemp28) ? fRec35[1] : fRec33[1]);
		fVbargraph4 = FAUSTFLOAT(fRec35[0]);
		double fTemp32 = fTemp30;
		double fTemp33 = ((iSlow82) ? 0.0 : fTemp32);
		double fTemp34 = std::fabs(fTemp33);
		double fTemp35 = ((fTemp34 > fRec32[1]) ? fSlow96 : fSlow94);
		fRec32[0] = fTemp34 * (1.0 - fTemp35) + fRec32[1] * fTemp35;
		fRec31[0] = fSlow99 * fSlow98 * std::max<double>(fSlow97 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec32[0])), 0.0) + fSlow86 * fRec31[1];
		fRec39[0] = fSlow100 + 0.999 * fRec39[1];
		double fTemp36 = fSlow101 * fRec39[0] * ((iSlow82) ? fTemp32 : fTemp33 * std::pow(1e+01, 0.05 * fRec31[0]));
		double fTemp37 = std::max<double>(fConst1, std::fabs(fTemp36));
		fRec28[0] = ((iTemp27) ? std::max<double>(fRec28[1], fTemp37) : fTemp37);
		iRec29[0] = ((iTemp27) ? iRec29[1] + 1 : 1);
		fRec30[0] = ((iTemp27) ? fRec30[1] : fRec28[1]);
		fVbargraph5 = FAUSTFLOAT(fRec30[0]);
		int iTemp38 = iRec41[1] < 4096;
		int iTemp39 = iRec46[1] < 4096;
		double fTemp40 = fSlow10 * fRec48[1];
		double fTemp41 = fSlow17 * fRec49[1];
		fRec51[0] = fSlow112 * fVec1[1] - fSlow43 * (fSlow41 * fRec51[1] - fSlow111 * fTemp3);
		fRec50[0] = fRec51[0] - fSlow29 * (fSlow27 * fRec50[2] + fSlow25 * fRec50[1]);
		fRec49[0] = fSlow29 * (fSlow24 * fRec50[0] + fSlow113 * fRec50[1] + fSlow24 * fRec50[2]) - fSlow110 * (fSlow109 * fRec49[2] + fTemp41);
		fRec48[0] = fRec49[2] + fSlow110 * (fTemp41 + fSlow109 * fRec49[0]) - fSlow88 * (fSlow87 * fRec48[2] + fTemp40);
		double fTemp42 = fRec48[2] + fSlow88 * (fTemp40 + fSlow87 * fRec48[0]);
		double fTemp43 = std::max<double>(fConst1, std::fabs(fTemp42));
		fRec45[0] = ((iTemp39) ? std::max<double>(fRec45[1], fTemp43) : fTemp43);
		iRec46[0] = ((iTemp39) ? iRec46[1] + 1 : 1);
		fRec47[0] = ((iTemp39) ? fRec47[1] : fRec45[1]);
		fVbargraph6 = FAUSTFLOAT(fRec47[0]);
		double fTemp44 = fTemp42;
		double fTemp45 = ((iSlow104) ? 0.0 : fTemp44);
		double fTemp46 = std::fabs(fTemp45);
		double fTemp47 = ((fTemp46 > fRec44[1]) ? fSlow118 : fSlow116);
		fRec44[0] = fTemp46 * (1.0 - fTemp47) + fRec44[1] * fTemp47;
		fRec43[0] = fSlow121 * fSlow120 * std::max<double>(fSlow119 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec44[0])), 0.0) + fSlow108 * fRec43[1];
		fRec52[0] = fSlow122 + 0.999 * fRec52[1];
		double fTemp48 = fSlow123 * fRec52[0] * ((iSlow104) ? fTemp44 : fTemp45 * std::pow(1e+01, 0.05 * fRec43[0]));
		double fTemp49 = std::max<double>(fConst1, std::fabs(fTemp48));
		fRec40[0] = ((iTemp38) ? std::max<double>(fRec40[1], fTemp49) : fTemp49);
		iRec41[0] = ((iTemp38) ? iRec41[1] + 1 : 1);
		fRec42[0] = ((iTemp38) ? fRec42[1] : fRec40[1]);
		fVbargraph7 = FAUSTFLOAT(fRec42[0]);
		int iTemp50 = iRec54[1] < 4096;
		int iTemp51 = iRec59[1] < 4096;
		double fTemp52 = fSlow10 * fRec61[1];
		double fTemp53 = fSlow17 * fRec62[1];
		double fTemp54 = fSlow25 * fRec63[1];
		fRec65[0] = fSlow133 * fVec0[1] - fSlow40 * (fSlow38 * fRec65[1] - fSlow34 * fTemp2);
		fRec64[0] = fRec65[0] - fSlow37 * (fSlow35 * fRec64[2] + fSlow33 * fRec64[1]);
		fRec63[0] = fSlow37 * (fSlow32 * fRec64[0] + fSlow134 * fRec64[1] + fSlow32 * fRec64[2]) - fSlow132 * (fSlow131 * fRec63[2] + fTemp54);
		fRec62[0] = fRec63[2] + fSlow132 * (fTemp54 + fSlow131 * fRec63[0]) - fSlow110 * (fSlow109 * fRec62[2] + fTemp53);
		fRec61[0] = fRec62[2] + fSlow110 * (fTemp53 + fSlow109 * fRec62[0]) - fSlow88 * (fSlow87 * fRec61[2] + fTemp52);
		double fTemp55 = fRec61[2] + fSlow88 * (fTemp52 + fSlow87 * fRec61[0]);
		double fTemp56 = std::max<double>(fConst1, std::fabs(fTemp55));
		fRec58[0] = ((iTemp51) ? std::max<double>(fRec58[1], fTemp56) : fTemp56);
		iRec59[0] = ((iTemp51) ? iRec59[1] + 1 : 1);
		fRec60[0] = ((iTemp51) ? fRec60[1] : fRec58[1]);
		fVbargraph8 = FAUSTFLOAT(fRec60[0]);
		double fTemp57 = fTemp55;
		double fTemp58 = ((iSlow126) ? 0.0 : fTemp57);
		double fTemp59 = std::fabs(fTemp58);
		double fTemp60 = ((fTemp59 > fRec57[1]) ? fSlow139 : fSlow137);
		fRec57[0] = fTemp59 * (1.0 - fTemp60) + fRec57[1] * fTemp60;
		fRec56[0] = fSlow142 * fSlow141 * std::max<double>(fSlow140 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec57[0])), 0.0) + fSlow130 * fRec56[1];
		fRec66[0] = fSlow143 + 0.999 * fRec66[1];
		double fTemp61 = fSlow144 * fRec66[0] * ((iSlow126) ? fTemp57 : fTemp58 * std::pow(1e+01, 0.05 * fRec56[0]));
		double fTemp62 = std::max<double>(fConst1, std::fabs(fTemp61));
		fRec53[0] = ((iTemp50) ? std::max<double>(fRec53[1], fTemp62) : fTemp62);
		iRec54[0] = ((iTemp50) ? iRec54[1] + 1 : 1);
		fRec55[0] = ((iTemp50) ? fRec55[1] : fRec53[1]);
		fVbargraph9 = FAUSTFLOAT(fRec55[0]);
		output0[i0] = FAUSTFLOAT(fTemp61 + fTemp48 + fTemp36 + fTemp25 + fTemp15);
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
