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
	double fRec3[2];
	double fConst2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT	*fHslider3_;
	double fVec0[2];
	double fRec11[2];
	double fRec10[3];
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT	*fHslider4_;
	double fRec9[3];
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT	*fHslider5_;
	double fRec8[3];
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT	*fHslider6_;
	double fRec7[3];
	double fRec4[2];
	int iRec5[2];
	double fRec6[2];
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT	*fVbargraph0_;
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT	*fHslider7_;
	FAUSTFLOAT fHslider8;
	FAUSTFLOAT	*fHslider8_;
	FAUSTFLOAT fHslider9;
	FAUSTFLOAT	*fHslider9_;
	double fRec14[2];
	double fRec13[2];
	double fRec12[2];
	double fRec0[2];
	int iRec1[2];
	double fRec2[2];
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT	*fVbargraph1_;
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT	*fHslider10_;
	FAUSTFLOAT fHslider11;
	FAUSTFLOAT	*fHslider11_;
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT	*fHslider12_;
	double fRec18[2];
	double fRec27[2];
	double fRec26[3];
	double fVec1[2];
	double fRec25[2];
	double fRec24[3];
	double fRec23[3];
	double fRec22[3];
	double fRec19[2];
	int iRec20[2];
	double fRec21[2];
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT	*fVbargraph2_;
	FAUSTFLOAT fHslider13;
	FAUSTFLOAT	*fHslider13_;
	FAUSTFLOAT fHslider14;
	FAUSTFLOAT	*fHslider14_;
	FAUSTFLOAT fHslider15;
	FAUSTFLOAT	*fHslider15_;
	double fRec30[2];
	double fRec29[2];
	double fRec28[2];
	double fRec15[2];
	int iRec16[2];
	double fRec17[2];
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT	*fVbargraph3_;
	FAUSTFLOAT fHslider16;
	FAUSTFLOAT	*fHslider16_;
	FAUSTFLOAT fHslider17;
	FAUSTFLOAT	*fHslider17_;
	FAUSTFLOAT fHslider18;
	FAUSTFLOAT	*fHslider18_;
	double fRec34[2];
	double fRec42[2];
	double fRec41[3];
	double fVec2[2];
	double fRec40[2];
	double fRec39[3];
	double fRec38[3];
	double fRec35[2];
	int iRec36[2];
	double fRec37[2];
	FAUSTFLOAT fVbargraph4;
	FAUSTFLOAT	*fVbargraph4_;
	FAUSTFLOAT fHslider19;
	FAUSTFLOAT	*fHslider19_;
	FAUSTFLOAT fHslider20;
	FAUSTFLOAT	*fHslider20_;
	FAUSTFLOAT fHslider21;
	FAUSTFLOAT	*fHslider21_;
	double fRec45[2];
	double fRec44[2];
	double fRec43[2];
	double fRec31[2];
	int iRec32[2];
	double fRec33[2];
	FAUSTFLOAT fVbargraph5;
	FAUSTFLOAT	*fVbargraph5_;
	FAUSTFLOAT fHslider22;
	FAUSTFLOAT	*fHslider22_;
	FAUSTFLOAT fHslider23;
	FAUSTFLOAT	*fHslider23_;
	FAUSTFLOAT fHslider24;
	FAUSTFLOAT	*fHslider24_;
	double fRec49[2];
	double fRec56[2];
	double fRec55[3];
	double fVec3[2];
	double fRec54[2];
	double fRec53[3];
	double fRec50[2];
	int iRec51[2];
	double fRec52[2];
	FAUSTFLOAT fVbargraph6;
	FAUSTFLOAT	*fVbargraph6_;
	FAUSTFLOAT fHslider25;
	FAUSTFLOAT	*fHslider25_;
	FAUSTFLOAT fHslider26;
	FAUSTFLOAT	*fHslider26_;
	FAUSTFLOAT fHslider27;
	FAUSTFLOAT	*fHslider27_;
	double fRec59[2];
	double fRec58[2];
	double fRec57[2];
	double fRec46[2];
	int iRec47[2];
	double fRec48[2];
	FAUSTFLOAT fVbargraph7;
	FAUSTFLOAT	*fVbargraph7_;
	FAUSTFLOAT fHslider28;
	FAUSTFLOAT	*fHslider28_;
	FAUSTFLOAT fHslider29;
	FAUSTFLOAT	*fHslider29_;
	FAUSTFLOAT fHslider30;
	FAUSTFLOAT	*fHslider30_;
	double fRec63[2];
	double fRec68[2];
	double fRec67[3];
	double fRec64[2];
	int iRec65[2];
	double fRec66[2];
	FAUSTFLOAT fVbargraph8;
	FAUSTFLOAT	*fVbargraph8_;
	FAUSTFLOAT fHslider31;
	FAUSTFLOAT	*fHslider31_;
	FAUSTFLOAT fHslider32;
	FAUSTFLOAT	*fHslider32_;
	FAUSTFLOAT fHslider33;
	FAUSTFLOAT	*fHslider33_;
	double fRec71[2];
	double fRec70[2];
	double fRec69[2];
	double fRec60[2];
	int iRec61[2];
	double fRec62[2];
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec3[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fVec0[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec11[l2] = 0.0;
	for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) fRec10[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec9[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec8[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec7[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec4[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) iRec5[l8] = 0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec6[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec14[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec13[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec12[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec0[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) iRec1[l14] = 0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec2[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec18[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec27[l17] = 0.0;
	for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) fRec26[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fVec1[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fRec25[l20] = 0.0;
	for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) fRec24[l21] = 0.0;
	for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) fRec23[l22] = 0.0;
	for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) fRec22[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec19[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) iRec20[l25] = 0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fRec21[l26] = 0.0;
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) fRec30[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec29[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fRec28[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec15[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) iRec16[l31] = 0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fRec17[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fRec34[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec42[l34] = 0.0;
	for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) fRec41[l35] = 0.0;
	for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) fVec2[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fRec40[l37] = 0.0;
	for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) fRec39[l38] = 0.0;
	for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) fRec38[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fRec35[l40] = 0.0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) iRec36[l41] = 0;
	for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) fRec37[l42] = 0.0;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fRec45[l43] = 0.0;
	for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) fRec44[l44] = 0.0;
	for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) fRec43[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec31[l46] = 0.0;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) iRec32[l47] = 0;
	for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) fRec33[l48] = 0.0;
	for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) fRec49[l49] = 0.0;
	for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) fRec56[l50] = 0.0;
	for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) fRec55[l51] = 0.0;
	for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) fVec3[l52] = 0.0;
	for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) fRec54[l53] = 0.0;
	for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) fRec53[l54] = 0.0;
	for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) fRec50[l55] = 0.0;
	for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) iRec51[l56] = 0;
	for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) fRec52[l57] = 0.0;
	for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) fRec59[l58] = 0.0;
	for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) fRec58[l59] = 0.0;
	for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) fRec57[l60] = 0.0;
	for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) fRec46[l61] = 0.0;
	for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) iRec47[l62] = 0;
	for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) fRec48[l63] = 0.0;
	for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) fRec63[l64] = 0.0;
	for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) fRec68[l65] = 0.0;
	for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) fRec67[l66] = 0.0;
	for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) fRec64[l67] = 0.0;
	for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) iRec65[l68] = 0;
	for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) fRec66[l69] = 0.0;
	for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) fRec71[l70] = 0.0;
	for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) fRec70[l71] = 0.0;
	for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) fRec69[l72] = 0.0;
	for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) fRec60[l73] = 0.0;
	for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) iRec61[l74] = 0;
	for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) fRec62[l75] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (1.0 / fConst0);
	fConst2 = (3.1415926535897931 / fConst0);
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
#define fHslider6 (*fHslider6_)
#define fVbargraph0 (*fVbargraph0_)
#define fHslider7 (*fHslider7_)
#define fHslider8 (*fHslider8_)
#define fHslider9 (*fHslider9_)
#define fVbargraph1 (*fVbargraph1_)
#define fHslider10 (*fHslider10_)
#define fHslider11 (*fHslider11_)
#define fHslider12 (*fHslider12_)
#define fVbargraph2 (*fVbargraph2_)
#define fHslider13 (*fHslider13_)
#define fHslider14 (*fHslider14_)
#define fHslider15 (*fHslider15_)
#define fVbargraph3 (*fVbargraph3_)
#define fHslider16 (*fHslider16_)
#define fHslider17 (*fHslider17_)
#define fHslider18 (*fHslider18_)
#define fVbargraph4 (*fVbargraph4_)
#define fHslider19 (*fHslider19_)
#define fHslider20 (*fHslider20_)
#define fHslider21 (*fHslider21_)
#define fVbargraph5 (*fVbargraph5_)
#define fHslider22 (*fHslider22_)
#define fHslider23 (*fHslider23_)
#define fHslider24 (*fHslider24_)
#define fVbargraph6 (*fVbargraph6_)
#define fHslider25 (*fHslider25_)
#define fHslider26 (*fHslider26_)
#define fHslider27 (*fHslider27_)
#define fVbargraph7 (*fVbargraph7_)
#define fHslider28 (*fHslider28_)
#define fHslider29 (*fHslider29_)
#define fHslider30 (*fHslider30_)
#define fVbargraph8 (*fVbargraph8_)
#define fHslider31 (*fHslider31_)
#define fHslider32 (*fHslider32_)
#define fHslider33 (*fHslider33_)
#define fVbargraph9 (*fVbargraph9_)
	double fSlow0 = double(fHslider0);
	double fSlow1 = std::fabs((std::max<double>(0.0, (fSlow0 + -2.0)) + -1.0));
	double fSlow2 = double(fHslider1);
	double fSlow3 = std::max<double>(0.0, (fSlow0 + -1.0));
	double fSlow4 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * ((fSlow2 - double(fHslider2)) * std::fabs((fSlow3 + -1.0))))));
	int iSlow5 = int(fSlow3);
	double fSlow6 = std::tan((fConst2 * double(fHslider3)));
	double fSlow7 = (1.0 / fSlow6);
	double fSlow8 = (((fSlow7 + 1.0000000000000004) / fSlow6) + 1.0);
	double fSlow9 = (1.0 / fSlow8);
	double fSlow10 = mydsp_faustpower2_f(fSlow6);
	double fSlow11 = (1.0 / fSlow10);
	double fSlow12 = (fSlow7 + 1.0);
	double fSlow13 = (0.0 - (1.0 / (fSlow6 * fSlow12)));
	double fSlow14 = (1.0 / fSlow12);
	double fSlow15 = (1.0 - fSlow7);
	double fSlow16 = (((fSlow7 + -1.0000000000000004) / fSlow6) + 1.0);
	double fSlow17 = (2.0 * (1.0 - fSlow11));
	double fSlow18 = (0.0 - (2.0 / fSlow10));
	double fSlow19 = std::tan((fConst2 * double(fHslider4)));
	double fSlow20 = (1.0 / fSlow19);
	double fSlow21 = (fSlow20 + 1.0);
	double fSlow22 = (1.0 / ((fSlow21 / fSlow19) + 1.0));
	double fSlow23 = (1.0 - fSlow20);
	double fSlow24 = (1.0 - (fSlow23 / fSlow19));
	double fSlow25 = mydsp_faustpower2_f(fSlow19);
	double fSlow26 = (1.0 / fSlow25);
	double fSlow27 = (2.0 * (1.0 - fSlow26));
	double fSlow28 = std::tan((fConst2 * double(fHslider5)));
	double fSlow29 = (1.0 / fSlow28);
	double fSlow30 = (fSlow29 + 1.0);
	double fSlow31 = (1.0 / ((fSlow30 / fSlow28) + 1.0));
	double fSlow32 = (1.0 - fSlow29);
	double fSlow33 = (1.0 - (fSlow32 / fSlow28));
	double fSlow34 = mydsp_faustpower2_f(fSlow28);
	double fSlow35 = (1.0 / fSlow34);
	double fSlow36 = (2.0 * (1.0 - fSlow35));
	double fSlow37 = std::tan((fConst2 * double(fHslider6)));
	double fSlow38 = (1.0 / fSlow37);
	double fSlow39 = (fSlow38 + 1.0);
	double fSlow40 = (1.0 / ((fSlow39 / fSlow37) + 1.0));
	double fSlow41 = (1.0 - fSlow38);
	double fSlow42 = (1.0 - (fSlow41 / fSlow37));
	double fSlow43 = mydsp_faustpower2_f(fSlow37);
	double fSlow44 = (1.0 / fSlow43);
	double fSlow45 = (2.0 * (1.0 - fSlow44));
	double fSlow46 = double(fHslider7);
	double fSlow47 = (0.5 * fSlow46);
	int iSlow48 = (std::fabs(fSlow47) < 2.2204460492503131e-16);
	double fSlow49 = (iSlow48 ? 0.0 : std::exp((0.0 - (fConst1 / (iSlow48 ? 1.0 : fSlow47)))));
	double fSlow50 = ((1.0 / std::max<double>(9.9999999999999995e-08, double(fHslider8))) + -1.0);
	int iSlow51 = (std::fabs(fSlow46) < 2.2204460492503131e-16);
	double fSlow52 = (iSlow51 ? 0.0 : std::exp((0.0 - (fConst1 / (iSlow51 ? 1.0 : fSlow46)))));
	double fSlow53 = double(fHslider9);
	int iSlow54 = (std::fabs(fSlow53) < 2.2204460492503131e-16);
	double fSlow55 = (iSlow54 ? 0.0 : std::exp((0.0 - (fConst1 / (iSlow54 ? 1.0 : fSlow53)))));
	double fSlow56 = (1.0 - fSlow49);
	double fSlow57 = double(fHslider10);
	double fSlow58 = std::fabs((std::max<double>(0.0, (fSlow57 + -2.0)) + -1.0));
	double fSlow59 = double(fHslider11);
	double fSlow60 = std::max<double>(0.0, (fSlow57 + -1.0));
	double fSlow61 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * ((fSlow59 - double(fHslider12)) * std::fabs((fSlow60 + -1.0))))));
	int iSlow62 = int(fSlow60);
	double fSlow63 = (((fSlow20 + 1.0000000000000004) / fSlow19) + 1.0);
	double fSlow64 = (1.0 / fSlow63);
	double fSlow65 = (0.0 - (1.0 / (fSlow19 * fSlow21)));
	double fSlow66 = (1.0 / fSlow21);
	double fSlow67 = (1.0 / (fSlow19 * fSlow8));
	double fSlow68 = (((fSlow20 + -1.0000000000000004) / fSlow19) + 1.0);
	double fSlow69 = (0.0 - (2.0 / fSlow25));
	double fSlow70 = double(fHslider13);
	double fSlow71 = (0.5 * fSlow70);
	int iSlow72 = (std::fabs(fSlow71) < 2.2204460492503131e-16);
	double fSlow73 = (iSlow72 ? 0.0 : std::exp((0.0 - (fConst1 / (iSlow72 ? 1.0 : fSlow71)))));
	double fSlow74 = ((1.0 / std::max<double>(9.9999999999999995e-08, double(fHslider14))) + -1.0);
	int iSlow75 = (std::fabs(fSlow70) < 2.2204460492503131e-16);
	double fSlow76 = (iSlow75 ? 0.0 : std::exp((0.0 - (fConst1 / (iSlow75 ? 1.0 : fSlow70)))));
	double fSlow77 = double(fHslider15);
	int iSlow78 = (std::fabs(fSlow77) < 2.2204460492503131e-16);
	double fSlow79 = (iSlow78 ? 0.0 : std::exp((0.0 - (fConst1 / (iSlow78 ? 1.0 : fSlow77)))));
	double fSlow80 = (1.0 - fSlow73);
	double fSlow81 = double(fHslider16);
	double fSlow82 = std::fabs((std::max<double>(0.0, (fSlow81 + -2.0)) + -1.0));
	double fSlow83 = double(fHslider17);
	double fSlow84 = std::max<double>(0.0, (fSlow81 + -1.0));
	double fSlow85 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * ((fSlow83 - double(fHslider18)) * std::fabs((fSlow84 + -1.0))))));
	int iSlow86 = int(fSlow84);
	double fSlow87 = (((fSlow29 + 1.0000000000000004) / fSlow28) + 1.0);
	double fSlow88 = (1.0 / fSlow87);
	double fSlow89 = (0.0 - (1.0 / (fSlow28 * fSlow30)));
	double fSlow90 = (1.0 / fSlow30);
	double fSlow91 = (1.0 / (fSlow28 * fSlow63));
	double fSlow92 = (((fSlow29 + -1.0000000000000004) / fSlow28) + 1.0);
	double fSlow93 = (0.0 - (2.0 / fSlow34));
	double fSlow94 = double(fHslider19);
	double fSlow95 = (0.5 * fSlow94);
	int iSlow96 = (std::fabs(fSlow95) < 2.2204460492503131e-16);
	double fSlow97 = (iSlow96 ? 0.0 : std::exp((0.0 - (fConst1 / (iSlow96 ? 1.0 : fSlow95)))));
	double fSlow98 = ((1.0 / std::max<double>(9.9999999999999995e-08, double(fHslider20))) + -1.0);
	int iSlow99 = (std::fabs(fSlow94) < 2.2204460492503131e-16);
	double fSlow100 = (iSlow99 ? 0.0 : std::exp((0.0 - (fConst1 / (iSlow99 ? 1.0 : fSlow94)))));
	double fSlow101 = double(fHslider21);
	int iSlow102 = (std::fabs(fSlow101) < 2.2204460492503131e-16);
	double fSlow103 = (iSlow102 ? 0.0 : std::exp((0.0 - (fConst1 / (iSlow102 ? 1.0 : fSlow101)))));
	double fSlow104 = (1.0 - fSlow97);
	double fSlow105 = double(fHslider22);
	double fSlow106 = std::fabs((std::max<double>(0.0, (fSlow105 + -2.0)) + -1.0));
	double fSlow107 = double(fHslider23);
	double fSlow108 = std::max<double>(0.0, (fSlow105 + -1.0));
	double fSlow109 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * ((fSlow107 - double(fHslider24)) * std::fabs((fSlow108 + -1.0))))));
	int iSlow110 = int(fSlow108);
	double fSlow111 = (1.0 / (((fSlow38 + 1.0000000000000004) / fSlow37) + 1.0));
	double fSlow112 = (0.0 - (1.0 / (fSlow37 * fSlow39)));
	double fSlow113 = (1.0 / fSlow39);
	double fSlow114 = (1.0 / (fSlow37 * fSlow87));
	double fSlow115 = (((fSlow38 + -1.0000000000000004) / fSlow37) + 1.0);
	double fSlow116 = (0.0 - (2.0 / fSlow43));
	double fSlow117 = double(fHslider25);
	double fSlow118 = (0.5 * fSlow117);
	int iSlow119 = (std::fabs(fSlow118) < 2.2204460492503131e-16);
	double fSlow120 = (iSlow119 ? 0.0 : std::exp((0.0 - (fConst1 / (iSlow119 ? 1.0 : fSlow118)))));
	double fSlow121 = ((1.0 / std::max<double>(9.9999999999999995e-08, double(fHslider26))) + -1.0);
	int iSlow122 = (std::fabs(fSlow117) < 2.2204460492503131e-16);
	double fSlow123 = (iSlow122 ? 0.0 : std::exp((0.0 - (fConst1 / (iSlow122 ? 1.0 : fSlow117)))));
	double fSlow124 = double(fHslider27);
	int iSlow125 = (std::fabs(fSlow124) < 2.2204460492503131e-16);
	double fSlow126 = (iSlow125 ? 0.0 : std::exp((0.0 - (fConst1 / (iSlow125 ? 1.0 : fSlow124)))));
	double fSlow127 = (1.0 - fSlow120);
	double fSlow128 = double(fHslider28);
	double fSlow129 = std::fabs((std::max<double>(0.0, (fSlow128 + -2.0)) + -1.0));
	double fSlow130 = double(fHslider29);
	double fSlow131 = std::max<double>(0.0, (fSlow128 + -1.0));
	double fSlow132 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * ((fSlow130 - double(fHslider30)) * std::fabs((fSlow131 + -1.0))))));
	int iSlow133 = int(fSlow131);
	double fSlow134 = double(fHslider31);
	double fSlow135 = (0.5 * fSlow134);
	int iSlow136 = (std::fabs(fSlow135) < 2.2204460492503131e-16);
	double fSlow137 = (iSlow136 ? 0.0 : std::exp((0.0 - (fConst1 / (iSlow136 ? 1.0 : fSlow135)))));
	double fSlow138 = ((1.0 / std::max<double>(9.9999999999999995e-08, double(fHslider32))) + -1.0);
	int iSlow139 = (std::fabs(fSlow134) < 2.2204460492503131e-16);
	double fSlow140 = (iSlow139 ? 0.0 : std::exp((0.0 - (fConst1 / (iSlow139 ? 1.0 : fSlow134)))));
	double fSlow141 = double(fHslider33);
	int iSlow142 = (std::fabs(fSlow141) < 2.2204460492503131e-16);
	double fSlow143 = (iSlow142 ? 0.0 : std::exp((0.0 - (fConst1 / (iSlow142 ? 1.0 : fSlow141)))));
	double fSlow144 = (1.0 - fSlow137);
	for (int i = 0; (i < count); i = (i + 1)) {
		int iTemp0 = (iRec1[1] < 4096);
		fRec3[0] = (fSlow4 + (0.999 * fRec3[1]));
		int iTemp1 = (iRec5[1] < 4096);
		double fTemp2 = double(input0[i]);
		fVec0[0] = fTemp2;
		fRec11[0] = ((fSlow13 * fVec0[1]) - (fSlow14 * ((fSlow15 * fRec11[1]) - (fSlow7 * fTemp2))));
		fRec10[0] = (fRec11[0] - (fSlow9 * ((fSlow16 * fRec10[2]) + (fSlow17 * fRec10[1]))));
		double fTemp3 = (fSlow27 * fRec9[1]);
		fRec9[0] = ((fSlow9 * (((fSlow11 * fRec10[0]) + (fSlow18 * fRec10[1])) + (fSlow11 * fRec10[2]))) - (fSlow22 * ((fSlow24 * fRec9[2]) + fTemp3)));
		double fTemp4 = (fSlow36 * fRec8[1]);
		fRec8[0] = ((fRec9[2] + (fSlow22 * (fTemp3 + (fSlow24 * fRec9[0])))) - (fSlow31 * ((fSlow33 * fRec8[2]) + fTemp4)));
		double fTemp5 = (fSlow45 * fRec7[1]);
		fRec7[0] = ((fRec8[2] + (fSlow31 * (fTemp4 + (fSlow33 * fRec8[0])))) - (fSlow40 * ((fSlow42 * fRec7[2]) + fTemp5)));
		double fTemp6 = (fRec7[2] + (fSlow40 * (fTemp5 + (fSlow42 * fRec7[0]))));
		double fTemp7 = std::max<double>(fConst1, std::fabs(fTemp6));
		fRec4[0] = (iTemp1 ? std::max<double>(fRec4[1], fTemp7) : fTemp7);
		iRec5[0] = (iTemp1 ? (iRec5[1] + 1) : 1);
		fRec6[0] = (iTemp1 ? fRec6[1] : fRec4[1]);
		fVbargraph0 = FAUSTFLOAT(fRec6[0]);
		double fTemp8 = (iSlow5 ? 0.0 : fTemp6);
		double fTemp9 = std::fabs(fTemp8);
		double fTemp10 = ((fRec13[1] > fTemp9) ? fSlow55 : fSlow52);
		fRec14[0] = ((fRec14[1] * fTemp10) + (fTemp9 * (1.0 - fTemp10)));
		fRec13[0] = fRec14[0];
		fRec12[0] = ((fRec12[1] * fSlow49) + (fSlow50 * (std::max<double>((fSlow2 + (20.0 * std::log10(fRec13[0]))), 0.0) * fSlow56)));
		double fTemp11 = (fSlow1 * (fRec3[0] * (iSlow5 ? fTemp6 : (fTemp8 * std::pow(10.0, (0.050000000000000003 * fRec12[0]))))));
		double fTemp12 = std::max<double>(fConst1, std::fabs(fTemp11));
		fRec0[0] = (iTemp0 ? std::max<double>(fRec0[1], fTemp12) : fTemp12);
		iRec1[0] = (iTemp0 ? (iRec1[1] + 1) : 1);
		fRec2[0] = (iTemp0 ? fRec2[1] : fRec0[1]);
		fVbargraph1 = FAUSTFLOAT(fRec2[0]);
		int iTemp13 = (iRec16[1] < 4096);
		fRec18[0] = (fSlow61 + (0.999 * fRec18[1]));
		int iTemp14 = (iRec20[1] < 4096);
		fRec27[0] = (0.0 - (fSlow14 * ((fSlow15 * fRec27[1]) - (fTemp2 + fVec0[1]))));
		fRec26[0] = (fRec27[0] - (fSlow9 * ((fSlow16 * fRec26[2]) + (fSlow17 * fRec26[1]))));
		double fTemp15 = (fRec26[2] + (fRec26[0] + (2.0 * fRec26[1])));
		double fTemp16 = (fSlow9 * fTemp15);
		fVec1[0] = fTemp16;
		fRec25[0] = ((fSlow65 * fVec1[1]) - (fSlow66 * ((fSlow23 * fRec25[1]) - (fSlow67 * fTemp15))));
		fRec24[0] = (fRec25[0] - (fSlow64 * ((fSlow68 * fRec24[2]) + (fSlow27 * fRec24[1]))));
		double fTemp17 = (fSlow36 * fRec23[1]);
		fRec23[0] = ((fSlow64 * (((fSlow26 * fRec24[0]) + (fSlow69 * fRec24[1])) + (fSlow26 * fRec24[2]))) - (fSlow31 * ((fSlow33 * fRec23[2]) + fTemp17)));
		double fTemp18 = (fSlow45 * fRec22[1]);
		fRec22[0] = ((fRec23[2] + (fSlow31 * (fTemp17 + (fSlow33 * fRec23[0])))) - (fSlow40 * ((fSlow42 * fRec22[2]) + fTemp18)));
		double fTemp19 = (fRec22[2] + (fSlow40 * (fTemp18 + (fSlow42 * fRec22[0]))));
		double fTemp20 = std::max<double>(fConst1, std::fabs(fTemp19));
		fRec19[0] = (iTemp14 ? std::max<double>(fRec19[1], fTemp20) : fTemp20);
		iRec20[0] = (iTemp14 ? (iRec20[1] + 1) : 1);
		fRec21[0] = (iTemp14 ? fRec21[1] : fRec19[1]);
		fVbargraph2 = FAUSTFLOAT(fRec21[0]);
		double fTemp21 = (iSlow62 ? 0.0 : fTemp19);
		double fTemp22 = std::fabs(fTemp21);
		double fTemp23 = ((fRec29[1] > fTemp22) ? fSlow79 : fSlow76);
		fRec30[0] = ((fRec30[1] * fTemp23) + (fTemp22 * (1.0 - fTemp23)));
		fRec29[0] = fRec30[0];
		fRec28[0] = ((fRec28[1] * fSlow73) + (fSlow74 * (std::max<double>((fSlow59 + (20.0 * std::log10(fRec29[0]))), 0.0) * fSlow80)));
		double fTemp24 = (fSlow58 * (fRec18[0] * (iSlow62 ? fTemp19 : (fTemp21 * std::pow(10.0, (0.050000000000000003 * fRec28[0]))))));
		double fTemp25 = std::max<double>(fConst1, std::fabs(fTemp24));
		fRec15[0] = (iTemp13 ? std::max<double>(fRec15[1], fTemp25) : fTemp25);
		iRec16[0] = (iTemp13 ? (iRec16[1] + 1) : 1);
		fRec17[0] = (iTemp13 ? fRec17[1] : fRec15[1]);
		fVbargraph3 = FAUSTFLOAT(fRec17[0]);
		int iTemp26 = (iRec32[1] < 4096);
		fRec34[0] = (fSlow85 + (0.999 * fRec34[1]));
		int iTemp27 = (iRec36[1] < 4096);
		fRec42[0] = (0.0 - (fSlow66 * ((fSlow23 * fRec42[1]) - (fTemp16 + fVec1[1]))));
		fRec41[0] = (fRec42[0] - (fSlow64 * ((fSlow68 * fRec41[2]) + (fSlow27 * fRec41[1]))));
		double fTemp28 = (fRec41[2] + (fRec41[0] + (2.0 * fRec41[1])));
		double fTemp29 = (fSlow64 * fTemp28);
		fVec2[0] = fTemp29;
		fRec40[0] = ((fSlow89 * fVec2[1]) - (fSlow90 * ((fSlow32 * fRec40[1]) - (fSlow91 * fTemp28))));
		fRec39[0] = (fRec40[0] - (fSlow88 * ((fSlow92 * fRec39[2]) + (fSlow36 * fRec39[1]))));
		double fTemp30 = (fSlow45 * fRec38[1]);
		fRec38[0] = ((fSlow88 * (((fSlow35 * fRec39[0]) + (fSlow93 * fRec39[1])) + (fSlow35 * fRec39[2]))) - (fSlow40 * ((fSlow42 * fRec38[2]) + fTemp30)));
		double fTemp31 = (fRec38[2] + (fSlow40 * (fTemp30 + (fSlow42 * fRec38[0]))));
		double fTemp32 = std::max<double>(fConst1, std::fabs(fTemp31));
		fRec35[0] = (iTemp27 ? std::max<double>(fRec35[1], fTemp32) : fTemp32);
		iRec36[0] = (iTemp27 ? (iRec36[1] + 1) : 1);
		fRec37[0] = (iTemp27 ? fRec37[1] : fRec35[1]);
		fVbargraph4 = FAUSTFLOAT(fRec37[0]);
		double fTemp33 = (iSlow86 ? 0.0 : fTemp31);
		double fTemp34 = std::fabs(fTemp33);
		double fTemp35 = ((fRec44[1] > fTemp34) ? fSlow103 : fSlow100);
		fRec45[0] = ((fRec45[1] * fTemp35) + (fTemp34 * (1.0 - fTemp35)));
		fRec44[0] = fRec45[0];
		fRec43[0] = ((fRec43[1] * fSlow97) + (fSlow98 * (std::max<double>((fSlow83 + (20.0 * std::log10(fRec44[0]))), 0.0) * fSlow104)));
		double fTemp36 = (fSlow82 * (fRec34[0] * (iSlow86 ? fTemp31 : (fTemp33 * std::pow(10.0, (0.050000000000000003 * fRec43[0]))))));
		double fTemp37 = std::max<double>(fConst1, std::fabs(fTemp36));
		fRec31[0] = (iTemp26 ? std::max<double>(fRec31[1], fTemp37) : fTemp37);
		iRec32[0] = (iTemp26 ? (iRec32[1] + 1) : 1);
		fRec33[0] = (iTemp26 ? fRec33[1] : fRec31[1]);
		fVbargraph5 = FAUSTFLOAT(fRec33[0]);
		int iTemp38 = (iRec47[1] < 4096);
		fRec49[0] = (fSlow109 + (0.999 * fRec49[1]));
		int iTemp39 = (iRec51[1] < 4096);
		fRec56[0] = (0.0 - (fSlow90 * ((fSlow32 * fRec56[1]) - (fTemp29 + fVec2[1]))));
		fRec55[0] = (fRec56[0] - (fSlow88 * ((fSlow92 * fRec55[2]) + (fSlow36 * fRec55[1]))));
		double fTemp40 = (fRec55[2] + (fRec55[0] + (2.0 * fRec55[1])));
		double fTemp41 = (fSlow88 * fTemp40);
		fVec3[0] = fTemp41;
		fRec54[0] = ((fSlow112 * fVec3[1]) - (fSlow113 * ((fSlow41 * fRec54[1]) - (fSlow114 * fTemp40))));
		fRec53[0] = (fRec54[0] - (fSlow111 * ((fSlow115 * fRec53[2]) + (fSlow45 * fRec53[1]))));
		double fTemp42 = (fSlow111 * (((fSlow44 * fRec53[0]) + (fSlow116 * fRec53[1])) + (fSlow44 * fRec53[2])));
		double fTemp43 = std::max<double>(fConst1, std::fabs(fTemp42));
		fRec50[0] = (iTemp39 ? std::max<double>(fRec50[1], fTemp43) : fTemp43);
		iRec51[0] = (iTemp39 ? (iRec51[1] + 1) : 1);
		fRec52[0] = (iTemp39 ? fRec52[1] : fRec50[1]);
		fVbargraph6 = FAUSTFLOAT(fRec52[0]);
		double fTemp44 = (iSlow110 ? 0.0 : fTemp42);
		double fTemp45 = std::fabs(fTemp44);
		double fTemp46 = ((fRec58[1] > fTemp45) ? fSlow126 : fSlow123);
		fRec59[0] = ((fRec59[1] * fTemp46) + (fTemp45 * (1.0 - fTemp46)));
		fRec58[0] = fRec59[0];
		fRec57[0] = ((fRec57[1] * fSlow120) + (fSlow121 * (std::max<double>((fSlow107 + (20.0 * std::log10(fRec58[0]))), 0.0) * fSlow127)));
		double fTemp47 = (fSlow106 * (fRec49[0] * (iSlow110 ? fTemp42 : (fTemp44 * std::pow(10.0, (0.050000000000000003 * fRec57[0]))))));
		double fTemp48 = std::max<double>(fConst1, std::fabs(fTemp47));
		fRec46[0] = (iTemp38 ? std::max<double>(fRec46[1], fTemp48) : fTemp48);
		iRec47[0] = (iTemp38 ? (iRec47[1] + 1) : 1);
		fRec48[0] = (iTemp38 ? fRec48[1] : fRec46[1]);
		fVbargraph7 = FAUSTFLOAT(fRec48[0]);
		int iTemp49 = (iRec61[1] < 4096);
		fRec63[0] = (fSlow132 + (0.999 * fRec63[1]));
		int iTemp50 = (iRec65[1] < 4096);
		fRec68[0] = (0.0 - (fSlow113 * ((fSlow41 * fRec68[1]) - (fTemp41 + fVec3[1]))));
		fRec67[0] = (fRec68[0] - (fSlow111 * ((fSlow115 * fRec67[2]) + (fSlow45 * fRec67[1]))));
		double fTemp51 = (fSlow111 * (fRec67[2] + (fRec67[0] + (2.0 * fRec67[1]))));
		double fTemp52 = std::max<double>(fConst1, std::fabs(fTemp51));
		fRec64[0] = (iTemp50 ? std::max<double>(fRec64[1], fTemp52) : fTemp52);
		iRec65[0] = (iTemp50 ? (iRec65[1] + 1) : 1);
		fRec66[0] = (iTemp50 ? fRec66[1] : fRec64[1]);
		fVbargraph8 = FAUSTFLOAT(fRec66[0]);
		double fTemp53 = (iSlow133 ? 0.0 : fTemp51);
		double fTemp54 = std::fabs(fTemp53);
		double fTemp55 = ((fRec70[1] > fTemp54) ? fSlow143 : fSlow140);
		fRec71[0] = ((fRec71[1] * fTemp55) + (fTemp54 * (1.0 - fTemp55)));
		fRec70[0] = fRec71[0];
		fRec69[0] = ((fRec69[1] * fSlow137) + (fSlow138 * (std::max<double>((fSlow130 + (20.0 * std::log10(fRec70[0]))), 0.0) * fSlow144)));
		double fTemp56 = (fSlow129 * (fRec63[0] * (iSlow133 ? fTemp51 : (fTemp53 * std::pow(10.0, (0.050000000000000003 * fRec69[0]))))));
		double fTemp57 = std::max<double>(fConst1, std::fabs(fTemp56));
		fRec60[0] = (iTemp49 ? std::max<double>(fRec60[1], fTemp57) : fTemp57);
		iRec61[0] = (iTemp49 ? (iRec61[1] + 1) : 1);
		fRec62[0] = (iTemp49 ? fRec62[1] : fRec60[1]);
		fVbargraph9 = FAUSTFLOAT(fRec62[0]);
		output0[i] = FAUSTFLOAT(((((fTemp11 + fTemp24) + fTemp36) + fTemp47) + fTemp56));
		fRec3[1] = fRec3[0];
		fVec0[1] = fVec0[0];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec4[1] = fRec4[0];
		iRec5[1] = iRec5[0];
		fRec6[1] = fRec6[0];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec0[1] = fRec0[0];
		iRec1[1] = iRec1[0];
		fRec2[1] = fRec2[0];
		fRec18[1] = fRec18[0];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fVec1[1] = fVec1[0];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fRec23[2] = fRec23[1];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fRec19[1] = fRec19[0];
		iRec20[1] = iRec20[0];
		fRec21[1] = fRec21[0];
		fRec30[1] = fRec30[0];
		fRec29[1] = fRec29[0];
		fRec28[1] = fRec28[0];
		fRec15[1] = fRec15[0];
		iRec16[1] = iRec16[0];
		fRec17[1] = fRec17[0];
		fRec34[1] = fRec34[0];
		fRec42[1] = fRec42[0];
		fRec41[2] = fRec41[1];
		fRec41[1] = fRec41[0];
		fVec2[1] = fVec2[0];
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		fRec35[1] = fRec35[0];
		iRec36[1] = iRec36[0];
		fRec37[1] = fRec37[0];
		fRec45[1] = fRec45[0];
		fRec44[1] = fRec44[0];
		fRec43[1] = fRec43[0];
		fRec31[1] = fRec31[0];
		iRec32[1] = iRec32[0];
		fRec33[1] = fRec33[0];
		fRec49[1] = fRec49[0];
		fRec56[1] = fRec56[0];
		fRec55[2] = fRec55[1];
		fRec55[1] = fRec55[0];
		fVec3[1] = fVec3[0];
		fRec54[1] = fRec54[0];
		fRec53[2] = fRec53[1];
		fRec53[1] = fRec53[0];
		fRec50[1] = fRec50[0];
		iRec51[1] = iRec51[0];
		fRec52[1] = fRec52[0];
		fRec59[1] = fRec59[0];
		fRec58[1] = fRec58[0];
		fRec57[1] = fRec57[0];
		fRec46[1] = fRec46[0];
		iRec47[1] = iRec47[0];
		fRec48[1] = fRec48[0];
		fRec63[1] = fRec63[0];
		fRec68[1] = fRec68[0];
		fRec67[2] = fRec67[1];
		fRec67[1] = fRec67[0];
		fRec64[1] = fRec64[0];
		iRec65[1] = iRec65[0];
		fRec66[1] = fRec66[0];
		fRec71[1] = fRec71[0];
		fRec70[1] = fRec70[0];
		fRec69[1] = fRec69[0];
		fRec60[1] = fRec60[0];
		iRec61[1] = iRec61[0];
		fRec62[1] = fRec62[0];
	}
#undef fHslider0
#undef fHslider1
#undef fHslider2
#undef fHslider3
#undef fHslider4
#undef fHslider5
#undef fHslider6
#undef fVbargraph0
#undef fHslider7
#undef fHslider8
#undef fHslider9
#undef fVbargraph1
#undef fHslider10
#undef fHslider11
#undef fHslider12
#undef fVbargraph2
#undef fHslider13
#undef fHslider14
#undef fHslider15
#undef fVbargraph3
#undef fHslider16
#undef fHslider17
#undef fHslider18
#undef fVbargraph4
#undef fHslider19
#undef fHslider20
#undef fHslider21
#undef fVbargraph5
#undef fHslider22
#undef fHslider23
#undef fHslider24
#undef fVbargraph6
#undef fHslider25
#undef fHslider26
#undef fHslider27
#undef fVbargraph7
#undef fHslider28
#undef fHslider29
#undef fHslider30
#undef fVbargraph8
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
	// static const value_pair fHslider28_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE1: 
		fHslider28_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fHslider22_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE2: 
		fHslider22_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fHslider16_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE3: 
		fHslider16_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fHslider10_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE4: 
		fHslider10_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	// static const value_pair fHslider0_values[] = {{"Compress"},{"Bypass"},{"Mute"},{0}};
	case MODE5: 
		fHslider0_ = (float*)data; // , 1.0, 1.0, 3.0, 1.0 
		break;
	case MAKEUP1: 
		fHslider29_ = (float*)data; // , 13.0, -50.0, 50.0, 0.10000000000000001 
		break;
	case MAKEUP2: 
		fHslider23_ = (float*)data; // , 10.0, -50.0, 50.0, 0.10000000000000001 
		break;
	case MAKEUP3: 
		fHslider17_ = (float*)data; // , 4.0, -50.0, 50.0, 0.10000000000000001 
		break;
	case MAKEUP4: 
		fHslider11_ = (float*)data; // , 8.0, -50.0, 50.0, 0.10000000000000001 
		break;
	case MAKEUP5: 
		fHslider1_ = (float*)data; // , 11.0, -50.0, 50.0, 0.10000000000000001 
		break;
	case MAKEUPTHRESHOLD1: 
		fHslider30_ = (float*)data; // , 2.0, 0.0, 10.0, 0.10000000000000001 
		break;
	case MAKEUPTHRESHOLD2: 
		fHslider24_ = (float*)data; // , 2.0, 0.0, 10.0, 0.10000000000000001 
		break;
	case MAKEUPTHRESHOLD3: 
		fHslider18_ = (float*)data; // , 2.0, 0.0, 10.0, 0.10000000000000001 
		break;
	case MAKEUPTHRESHOLD4: 
		fHslider12_ = (float*)data; // , 2.0, 0.0, 10.0, 0.10000000000000001 
		break;
	case MAKEUPTHRESHOLD5: 
		fHslider2_ = (float*)data; // , 2.0, 0.0, 10.0, 0.10000000000000001 
		break;
	case RATIO1: 
		fHslider32_ = (float*)data; // , 2.0, 1.0, 100.0, 0.10000000000000001 
		break;
	case RATIO2: 
		fHslider26_ = (float*)data; // , 2.0, 1.0, 100.0, 0.10000000000000001 
		break;
	case RATIO3: 
		fHslider20_ = (float*)data; // , 2.0, 1.0, 100.0, 0.10000000000000001 
		break;
	case RATIO4: 
		fHslider14_ = (float*)data; // , 2.0, 1.0, 100.0, 0.10000000000000001 
		break;
	case RATIO5: 
		fHslider8_ = (float*)data; // , 2.0, 1.0, 100.0, 0.10000000000000001 
		break;
	case ATTACK1: 
		fHslider31_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK2: 
		fHslider25_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK3: 
		fHslider19_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK4: 
		fHslider13_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case ATTACK5: 
		fHslider7_ = (float*)data; // , 0.012, 0.001, 1.0, 0.001 
		break;
	case RELEASE1: 
		fHslider33_ = (float*)data; // , 1.25, 0.01, 10.0, 0.01 
		break;
	case RELEASE2: 
		fHslider27_ = (float*)data; // , 1.25, 0.01, 10.0, 0.01 
		break;
	case RELEASE3: 
		fHslider21_ = (float*)data; // , 1.25, 0.01, 10.0, 0.01 
		break;
	case RELEASE4: 
		fHslider15_ = (float*)data; // , 1.25, 0.01, 10.0, 0.01 
		break;
	case RELEASE5: 
		fHslider9_ = (float*)data; // , 1.25, 0.01, 10.0, 0.01 
		break;
	case CROSSOVER_B1_B2: 
		fHslider6_ = (float*)data; // , 80.0, 20.0, 20000.0, 1.0800000000000001 
		break;
	case CROSSOVER_B2_B3: 
		fHslider5_ = (float*)data; // , 210.0, 20.0, 20000.0, 1.0800000000000001 
		break;
	case CROSSOVER_B3_B4: 
		fHslider4_ = (float*)data; // , 1700.0, 20.0, 20000.0, 1.0800000000000001 
		break;
	case CROSSOVER_B4_B5: 
		fHslider3_ = (float*)data; // , 5000.0, 20.0, 20000.0, 1.0800000000000001 
		break;
	case V10: 
		fVbargraph0_ = (float*)data; // , 0, -70.0, 5.0, 0 
		break;
	case V1: 
		fVbargraph9_ = (float*)data; // , 0, -70.0, 5.0, 0 
		break;
	case V2: 
		fVbargraph7_ = (float*)data; // , 0, -70.0, 5.0, 0 
		break;
	case V3: 
		fVbargraph5_ = (float*)data; // , 0, -70.0, 5.0, 0 
		break;
	case V4: 
		fVbargraph3_ = (float*)data; // , 0, -70.0, 5.0, 0 
		break;
	case V5: 
		fVbargraph1_ = (float*)data; // , 0, -70.0, 5.0, 0 
		break;
	case V6: 
		fVbargraph8_ = (float*)data; // , 0, -70.0, 5.0, 0 
		break;
	case V7: 
		fVbargraph6_ = (float*)data; // , 0, -70.0, 5.0, 0 
		break;
	case V8: 
		fVbargraph4_ = (float*)data; // , 0, -70.0, 5.0, 0 
		break;
	case V9: 
		fVbargraph2_ = (float*)data; // , 0, -70.0, 5.0, 0 
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
