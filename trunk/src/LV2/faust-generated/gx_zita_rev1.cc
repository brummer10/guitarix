// generated from file '../src/LV2/faust/gx_zita_rev1.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace gx_zita_rev1 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst1;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	double fConst3;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT	*fVslider5_;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT	*fVslider6_;
	double fConst4;
	double fRec13[2];
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT	*fVslider7_;
	double fRec12[2];
	int IOTA0;
	double fVec0[16384];
	int iConst6;
	double fVec1[16384];
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT	*fVslider8_;
	double fConst7;
	double fVec2[4096];
	int iConst8;
	double fRec10[2];
	double fConst10;
	double fRec17[2];
	double fRec16[2];
	double fVec3[16384];
	int iConst12;
	double fVec4[2048];
	int iConst13;
	double fRec14[2];
	double fConst15;
	double fRec21[2];
	double fRec20[2];
	double fVec5[16384];
	int iConst17;
	double fVec6[4096];
	int iConst18;
	double fRec18[2];
	double fConst20;
	double fRec25[2];
	double fRec24[2];
	double fVec7[16384];
	int iConst22;
	double fVec8[2048];
	int iConst23;
	double fRec22[2];
	double fConst25;
	double fRec29[2];
	double fRec28[2];
	double fVec9[32768];
	int iConst27;
	double fVec10[16384];
	double fVec11[4096];
	int iConst28;
	double fRec26[2];
	double fConst30;
	double fRec33[2];
	double fRec32[2];
	double fVec12[16384];
	int iConst32;
	double fVec13[4096];
	int iConst33;
	double fRec30[2];
	double fConst35;
	double fRec37[2];
	double fRec36[2];
	double fVec14[32768];
	int iConst37;
	double fVec15[4096];
	int iConst38;
	double fRec34[2];
	double fConst40;
	double fRec41[2];
	double fRec40[2];
	double fVec16[32768];
	int iConst42;
	double fVec17[2048];
	int iConst43;
	double fRec38[2];
	double fRec2[3];
	double fRec3[3];
	double fRec4[3];
	double fRec5[3];
	double fRec6[3];
	double fRec7[3];
	double fRec8[3];
	double fRec9[3];
	double fRec1[3];
	double fRec0[3];
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT	*fVslider9_;
	double fRec42[2];
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT	*fVslider10_;
	double fRec43[2];
	double fRec45[3];
	double fRec44[3];

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
	id = "zita_rev1";
	name = N_("Zita Rev1");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec13[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec12[l1] = 0.0;
	for (int l2 = 0; l2 < 16384; l2 = l2 + 1) fVec0[l2] = 0.0;
	for (int l3 = 0; l3 < 16384; l3 = l3 + 1) fVec1[l3] = 0.0;
	for (int l4 = 0; l4 < 4096; l4 = l4 + 1) fVec2[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec10[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec17[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec16[l7] = 0.0;
	for (int l8 = 0; l8 < 16384; l8 = l8 + 1) fVec3[l8] = 0.0;
	for (int l9 = 0; l9 < 2048; l9 = l9 + 1) fVec4[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec14[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec21[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec20[l12] = 0.0;
	for (int l13 = 0; l13 < 16384; l13 = l13 + 1) fVec5[l13] = 0.0;
	for (int l14 = 0; l14 < 4096; l14 = l14 + 1) fVec6[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec18[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec25[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec24[l17] = 0.0;
	for (int l18 = 0; l18 < 16384; l18 = l18 + 1) fVec7[l18] = 0.0;
	for (int l19 = 0; l19 < 2048; l19 = l19 + 1) fVec8[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec22[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec29[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec28[l22] = 0.0;
	for (int l23 = 0; l23 < 32768; l23 = l23 + 1) fVec9[l23] = 0.0;
	for (int l24 = 0; l24 < 16384; l24 = l24 + 1) fVec10[l24] = 0.0;
	for (int l25 = 0; l25 < 4096; l25 = l25 + 1) fVec11[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec26[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec33[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec32[l28] = 0.0;
	for (int l29 = 0; l29 < 16384; l29 = l29 + 1) fVec12[l29] = 0.0;
	for (int l30 = 0; l30 < 4096; l30 = l30 + 1) fVec13[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec30[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fRec37[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fRec36[l33] = 0.0;
	for (int l34 = 0; l34 < 32768; l34 = l34 + 1) fVec14[l34] = 0.0;
	for (int l35 = 0; l35 < 4096; l35 = l35 + 1) fVec15[l35] = 0.0;
	for (int l36 = 0; l36 < 2; l36 = l36 + 1) fRec34[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec41[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fRec40[l38] = 0.0;
	for (int l39 = 0; l39 < 32768; l39 = l39 + 1) fVec16[l39] = 0.0;
	for (int l40 = 0; l40 < 2048; l40 = l40 + 1) fVec17[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec38[l41] = 0.0;
	for (int l42 = 0; l42 < 3; l42 = l42 + 1) fRec2[l42] = 0.0;
	for (int l43 = 0; l43 < 3; l43 = l43 + 1) fRec3[l43] = 0.0;
	for (int l44 = 0; l44 < 3; l44 = l44 + 1) fRec4[l44] = 0.0;
	for (int l45 = 0; l45 < 3; l45 = l45 + 1) fRec5[l45] = 0.0;
	for (int l46 = 0; l46 < 3; l46 = l46 + 1) fRec6[l46] = 0.0;
	for (int l47 = 0; l47 < 3; l47 = l47 + 1) fRec7[l47] = 0.0;
	for (int l48 = 0; l48 < 3; l48 = l48 + 1) fRec8[l48] = 0.0;
	for (int l49 = 0; l49 < 3; l49 = l49 + 1) fRec9[l49] = 0.0;
	for (int l50 = 0; l50 < 3; l50 = l50 + 1) fRec1[l50] = 0.0;
	for (int l51 = 0; l51 < 3; l51 = l51 + 1) fRec0[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fRec42[l52] = 0.0;
	for (int l53 = 0; l53 < 2; l53 = l53 + 1) fRec43[l53] = 0.0;
	for (int l54 = 0; l54 < 3; l54 = l54 + 1) fRec45[l54] = 0.0;
	for (int l55 = 0; l55 < 3; l55 = l55 + 1) fRec44[l55] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 6.283185307179586 / fConst0;
	double fConst2 = std::floor(0.174713 * fConst0 + 0.5);
	fConst3 = 6.907755278982138 * (fConst2 / fConst0);
	fConst4 = 3.141592653589793 / fConst0;
	double fConst5 = std::floor(0.022904 * fConst0 + 0.5);
	iConst6 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst2 - fConst5)));
	fConst7 = 0.001 * fConst0;
	iConst8 = int(std::min<double>(2048.0, std::max<double>(0.0, fConst5 + -1.0)));
	double fConst9 = std::floor(0.153129 * fConst0 + 0.5);
	fConst10 = 6.907755278982138 * (fConst9 / fConst0);
	double fConst11 = std::floor(0.020346 * fConst0 + 0.5);
	iConst12 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst9 - fConst11)));
	iConst13 = int(std::min<double>(1024.0, std::max<double>(0.0, fConst11 + -1.0)));
	double fConst14 = std::floor(0.127837 * fConst0 + 0.5);
	fConst15 = 6.907755278982138 * (fConst14 / fConst0);
	double fConst16 = std::floor(0.031604 * fConst0 + 0.5);
	iConst17 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst14 - fConst16)));
	iConst18 = int(std::min<double>(2048.0, std::max<double>(0.0, fConst16 + -1.0)));
	double fConst19 = std::floor(0.125 * fConst0 + 0.5);
	fConst20 = 6.907755278982138 * (fConst19 / fConst0);
	double fConst21 = std::floor(0.013458 * fConst0 + 0.5);
	iConst22 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst19 - fConst21)));
	iConst23 = int(std::min<double>(1024.0, std::max<double>(0.0, fConst21 + -1.0)));
	double fConst24 = std::floor(0.210389 * fConst0 + 0.5);
	fConst25 = 6.907755278982138 * (fConst24 / fConst0);
	double fConst26 = std::floor(0.024421 * fConst0 + 0.5);
	iConst27 = int(std::min<double>(16384.0, std::max<double>(0.0, fConst24 - fConst26)));
	iConst28 = int(std::min<double>(2048.0, std::max<double>(0.0, fConst26 + -1.0)));
	double fConst29 = std::floor(0.192303 * fConst0 + 0.5);
	fConst30 = 6.907755278982138 * (fConst29 / fConst0);
	double fConst31 = std::floor(0.029291 * fConst0 + 0.5);
	iConst32 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst29 - fConst31)));
	iConst33 = int(std::min<double>(2048.0, std::max<double>(0.0, fConst31 + -1.0)));
	double fConst34 = std::floor(0.256891 * fConst0 + 0.5);
	fConst35 = 6.907755278982138 * (fConst34 / fConst0);
	double fConst36 = std::floor(0.027333 * fConst0 + 0.5);
	iConst37 = int(std::min<double>(16384.0, std::max<double>(0.0, fConst34 - fConst36)));
	iConst38 = int(std::min<double>(2048.0, std::max<double>(0.0, fConst36 + -1.0)));
	double fConst39 = std::floor(0.219991 * fConst0 + 0.5);
	fConst40 = 6.907755278982138 * (fConst39 / fConst0);
	double fConst41 = std::floor(0.019123 * fConst0 + 0.5);
	iConst42 = int(std::min<double>(16384.0, std::max<double>(0.0, fConst39 - fConst41)));
	iConst43 = int(std::min<double>(1024.0, std::max<double>(0.0, fConst41 + -1.0)));
	IOTA0 = 0;
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
#define fVslider4 (*fVslider4_)
#define fVslider5 (*fVslider5_)
#define fVslider6 (*fVslider6_)
#define fVslider7 (*fVslider7_)
#define fVslider8 (*fVslider8_)
#define fVslider9 (*fVslider9_)
#define fVslider10 (*fVslider10_)
	double fSlow0 = std::pow(1e+01, 0.05 * double(fVslider0));
	double fSlow1 = double(fVslider1);
	double fSlow2 = fConst1 * (fSlow1 / std::sqrt(fSlow0));
	double fSlow3 = (1.0 - fSlow2) / (fSlow2 + 1.0);
	double fSlow4 = std::cos(fConst1 * fSlow1) * (fSlow3 + 1.0);
	double fSlow5 = std::pow(1e+01, 0.05 * double(fVslider2));
	double fSlow6 = double(fVslider3);
	double fSlow7 = fConst1 * (fSlow6 / std::sqrt(fSlow5));
	double fSlow8 = (1.0 - fSlow7) / (fSlow7 + 1.0);
	double fSlow9 = std::cos(fConst1 * fSlow6) * (fSlow8 + 1.0);
	double fSlow10 = double(fVslider4);
	double fSlow11 = std::exp(-(fConst3 / fSlow10));
	double fSlow12 = mydsp_faustpower2_f(fSlow11);
	double fSlow13 = 1.0 - fSlow12;
	double fSlow14 = std::cos(fConst1 * double(fVslider5));
	double fSlow15 = 1.0 - fSlow14 * fSlow12;
	double fSlow16 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow15) / mydsp_faustpower2_f(fSlow13) + -1.0));
	double fSlow17 = fSlow15 / fSlow13;
	double fSlow18 = fSlow17 - fSlow16;
	double fSlow19 = 1.0 / std::tan(fConst4 * double(fVslider6));
	double fSlow20 = 1.0 - fSlow19;
	double fSlow21 = 1.0 / (fSlow19 + 1.0);
	double fSlow22 = double(fVslider7);
	double fSlow23 = std::exp(-(fConst3 / fSlow22)) / fSlow11 + -1.0;
	double fSlow24 = fSlow11 * (fSlow16 + (1.0 - fSlow17));
	int iSlow25 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst7 * double(fVslider8))));
	double fSlow26 = std::exp(-(fConst10 / fSlow10));
	double fSlow27 = mydsp_faustpower2_f(fSlow26);
	double fSlow28 = 1.0 - fSlow27;
	double fSlow29 = 1.0 - fSlow27 * fSlow14;
	double fSlow30 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow29) / mydsp_faustpower2_f(fSlow28) + -1.0));
	double fSlow31 = fSlow29 / fSlow28;
	double fSlow32 = fSlow31 - fSlow30;
	double fSlow33 = std::exp(-(fConst10 / fSlow22)) / fSlow26 + -1.0;
	double fSlow34 = fSlow26 * (fSlow30 + (1.0 - fSlow31));
	double fSlow35 = std::exp(-(fConst15 / fSlow10));
	double fSlow36 = mydsp_faustpower2_f(fSlow35);
	double fSlow37 = 1.0 - fSlow36;
	double fSlow38 = 1.0 - fSlow14 * fSlow36;
	double fSlow39 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow38) / mydsp_faustpower2_f(fSlow37) + -1.0));
	double fSlow40 = fSlow38 / fSlow37;
	double fSlow41 = fSlow40 - fSlow39;
	double fSlow42 = std::exp(-(fConst15 / fSlow22)) / fSlow35 + -1.0;
	double fSlow43 = fSlow35 * (fSlow39 + (1.0 - fSlow40));
	double fSlow44 = std::exp(-(fConst20 / fSlow10));
	double fSlow45 = mydsp_faustpower2_f(fSlow44);
	double fSlow46 = 1.0 - fSlow45;
	double fSlow47 = 1.0 - fSlow14 * fSlow45;
	double fSlow48 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow47) / mydsp_faustpower2_f(fSlow46) + -1.0));
	double fSlow49 = fSlow47 / fSlow46;
	double fSlow50 = fSlow49 - fSlow48;
	double fSlow51 = std::exp(-(fConst20 / fSlow22)) / fSlow44 + -1.0;
	double fSlow52 = fSlow44 * (fSlow48 + (1.0 - fSlow49));
	double fSlow53 = std::exp(-(fConst25 / fSlow10));
	double fSlow54 = mydsp_faustpower2_f(fSlow53);
	double fSlow55 = 1.0 - fSlow54;
	double fSlow56 = 1.0 - fSlow14 * fSlow54;
	double fSlow57 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow56) / mydsp_faustpower2_f(fSlow55) + -1.0));
	double fSlow58 = fSlow56 / fSlow55;
	double fSlow59 = fSlow58 - fSlow57;
	double fSlow60 = std::exp(-(fConst25 / fSlow22)) / fSlow53 + -1.0;
	double fSlow61 = fSlow53 * (fSlow57 + (1.0 - fSlow58));
	double fSlow62 = std::exp(-(fConst30 / fSlow10));
	double fSlow63 = mydsp_faustpower2_f(fSlow62);
	double fSlow64 = 1.0 - fSlow63;
	double fSlow65 = 1.0 - fSlow14 * fSlow63;
	double fSlow66 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow65) / mydsp_faustpower2_f(fSlow64) + -1.0));
	double fSlow67 = fSlow65 / fSlow64;
	double fSlow68 = fSlow67 - fSlow66;
	double fSlow69 = std::exp(-(fConst30 / fSlow22)) / fSlow62 + -1.0;
	double fSlow70 = fSlow62 * (fSlow66 + (1.0 - fSlow67));
	double fSlow71 = std::exp(-(fConst35 / fSlow10));
	double fSlow72 = mydsp_faustpower2_f(fSlow71);
	double fSlow73 = 1.0 - fSlow72;
	double fSlow74 = 1.0 - fSlow14 * fSlow72;
	double fSlow75 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow74) / mydsp_faustpower2_f(fSlow73) + -1.0));
	double fSlow76 = fSlow74 / fSlow73;
	double fSlow77 = fSlow76 - fSlow75;
	double fSlow78 = std::exp(-(fConst35 / fSlow22)) / fSlow71 + -1.0;
	double fSlow79 = fSlow71 * (fSlow75 + (1.0 - fSlow76));
	double fSlow80 = std::exp(-(fConst40 / fSlow10));
	double fSlow81 = mydsp_faustpower2_f(fSlow80);
	double fSlow82 = 1.0 - fSlow81;
	double fSlow83 = 1.0 - fSlow14 * fSlow81;
	double fSlow84 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow83) / mydsp_faustpower2_f(fSlow82) + -1.0));
	double fSlow85 = fSlow83 / fSlow82;
	double fSlow86 = fSlow85 - fSlow84;
	double fSlow87 = std::exp(-(fConst40 / fSlow22)) / fSlow80 + -1.0;
	double fSlow88 = fSlow80 * (fSlow84 + (1.0 - fSlow85));
	double fSlow89 = 0.0010000000000000009 * double(fVslider9);
	double fSlow90 = 0.0010000000000000009 * double(fVslider10);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = fSlow4 * fRec0[1];
		double fTemp1 = fSlow9 * fRec1[1];
		fRec13[0] = -(fSlow21 * (fSlow20 * fRec13[1] - (fRec6[1] + fRec6[2])));
		fRec12[0] = fSlow24 * (fRec6[1] + fSlow23 * fRec13[0]) + fSlow18 * fRec12[1];
		fVec0[IOTA0 & 16383] = 0.35355339059327373 * fRec12[0] + 1e-20;
		double fTemp2 = double(input0[i0]);
		fVec1[IOTA0 & 16383] = fTemp2;
		double fTemp3 = 0.3 * fVec1[(IOTA0 - iSlow25) & 16383];
		double fTemp4 = fTemp3 + fVec0[(IOTA0 - iConst6) & 16383] - 0.6 * fRec10[1];
		fVec2[IOTA0 & 4095] = fTemp4;
		fRec10[0] = fVec2[(IOTA0 - iConst8) & 4095];
		double fRec11 = 0.6 * fTemp4;
		fRec17[0] = -(fSlow21 * (fSlow20 * fRec17[1] - (fRec2[1] + fRec2[2])));
		fRec16[0] = fSlow34 * (fRec2[1] + fSlow33 * fRec17[0]) + fSlow32 * fRec16[1];
		fVec3[IOTA0 & 16383] = 0.35355339059327373 * fRec16[0] + 1e-20;
		double fTemp5 = fVec3[(IOTA0 - iConst12) & 16383] + fTemp3 - 0.6 * fRec14[1];
		fVec4[IOTA0 & 2047] = fTemp5;
		fRec14[0] = fVec4[(IOTA0 - iConst13) & 2047];
		double fRec15 = 0.6 * fTemp5;
		double fTemp6 = fRec15 + fRec11;
		fRec21[0] = -(fSlow21 * (fSlow20 * fRec21[1] - (fRec4[1] + fRec4[2])));
		fRec20[0] = fSlow43 * (fRec4[1] + fSlow42 * fRec21[0]) + fSlow41 * fRec20[1];
		fVec5[IOTA0 & 16383] = 0.35355339059327373 * fRec20[0] + 1e-20;
		double fTemp7 = fVec5[(IOTA0 - iConst17) & 16383] - (fTemp3 + 0.6 * fRec18[1]);
		fVec6[IOTA0 & 4095] = fTemp7;
		fRec18[0] = fVec6[(IOTA0 - iConst18) & 4095];
		double fRec19 = 0.6 * fTemp7;
		fRec25[0] = -(fSlow21 * (fSlow20 * fRec25[1] - (fRec8[1] + fRec8[2])));
		fRec24[0] = fSlow52 * (fRec8[1] + fSlow51 * fRec25[0]) + fSlow50 * fRec24[1];
		fVec7[IOTA0 & 16383] = 0.35355339059327373 * fRec24[0] + 1e-20;
		double fTemp8 = fVec7[(IOTA0 - iConst22) & 16383] - (fTemp3 + 0.6 * fRec22[1]);
		fVec8[IOTA0 & 2047] = fTemp8;
		fRec22[0] = fVec8[(IOTA0 - iConst23) & 2047];
		double fRec23 = 0.6 * fTemp8;
		double fTemp9 = fRec23 + fRec19 + fTemp6;
		fRec29[0] = -(fSlow21 * (fSlow20 * fRec29[1] - (fRec3[1] + fRec3[2])));
		fRec28[0] = fSlow61 * (fRec3[1] + fSlow60 * fRec29[0]) + fSlow59 * fRec28[1];
		fVec9[IOTA0 & 32767] = 0.35355339059327373 * fRec28[0] + 1e-20;
		double fTemp10 = double(input1[i0]);
		fVec10[IOTA0 & 16383] = fTemp10;
		double fTemp11 = 0.3 * fVec10[(IOTA0 - iSlow25) & 16383];
		double fTemp12 = fTemp11 + 0.6 * fRec26[1] + fVec9[(IOTA0 - iConst27) & 32767];
		fVec11[IOTA0 & 4095] = fTemp12;
		fRec26[0] = fVec11[(IOTA0 - iConst28) & 4095];
		double fRec27 = -(0.6 * fTemp12);
		fRec33[0] = -(fSlow21 * (fSlow20 * fRec33[1] - (fRec7[1] + fRec7[2])));
		fRec32[0] = fSlow70 * (fRec7[1] + fSlow69 * fRec33[0]) + fSlow68 * fRec32[1];
		fVec12[IOTA0 & 16383] = 0.35355339059327373 * fRec32[0] + 1e-20;
		double fTemp13 = fVec12[(IOTA0 - iConst32) & 16383] + fTemp11 + 0.6 * fRec30[1];
		fVec13[IOTA0 & 4095] = fTemp13;
		fRec30[0] = fVec13[(IOTA0 - iConst33) & 4095];
		double fRec31 = -(0.6 * fTemp13);
		fRec37[0] = -(fSlow21 * (fSlow20 * fRec37[1] - (fRec5[1] + fRec5[2])));
		fRec36[0] = fSlow79 * (fRec5[1] + fSlow78 * fRec37[0]) + fSlow77 * fRec36[1];
		fVec14[IOTA0 & 32767] = 0.35355339059327373 * fRec36[0] + 1e-20;
		double fTemp14 = 0.6 * fRec34[1] + fVec14[(IOTA0 - iConst37) & 32767];
		fVec15[IOTA0 & 4095] = fTemp14 - fTemp11;
		fRec34[0] = fVec15[(IOTA0 - iConst38) & 4095];
		double fRec35 = 0.6 * (fTemp11 - fTemp14);
		fRec41[0] = -(fSlow21 * (fSlow20 * fRec41[1] - (fRec9[1] + fRec9[2])));
		fRec40[0] = fSlow88 * (fRec9[1] + fSlow87 * fRec41[0]) + fSlow86 * fRec40[1];
		fVec16[IOTA0 & 32767] = 0.35355339059327373 * fRec40[0] + 1e-20;
		double fTemp15 = 0.6 * fRec38[1] + fVec16[(IOTA0 - iConst42) & 32767];
		fVec17[IOTA0 & 2047] = fTemp15 - fTemp11;
		fRec38[0] = fVec17[(IOTA0 - iConst43) & 2047];
		double fRec39 = 0.6 * (fTemp11 - fTemp15);
		fRec2[0] = fRec38[1] + fRec34[1] + fRec30[1] + fRec26[1] + fRec22[1] + fRec18[1] + fRec10[1] + fRec14[1] + fRec39 + fRec35 + fRec31 + fRec27 + fTemp9;
		fRec3[0] = fRec22[1] + fRec18[1] + fRec10[1] + fRec14[1] + fTemp9 - (fRec38[1] + fRec34[1] + fRec30[1] + fRec26[1] + fRec39 + fRec35 + fRec27 + fRec31);
		double fTemp16 = fRec19 + fRec23;
		fRec4[0] = fRec30[1] + fRec26[1] + fRec10[1] + fRec14[1] + fRec31 + fRec27 + fTemp6 - (fRec38[1] + fRec34[1] + fRec22[1] + fRec18[1] + fRec39 + fRec35 + fTemp16);
		fRec5[0] = fRec38[1] + fRec34[1] + fRec10[1] + fRec14[1] + fRec39 + fRec35 + fTemp6 - (fRec30[1] + fRec26[1] + fRec22[1] + fRec18[1] + fRec31 + fRec27 + fTemp16);
		double fTemp17 = fRec11 + fRec23;
		double fTemp18 = fRec15 + fRec19;
		fRec6[0] = fRec34[1] + fRec26[1] + fRec18[1] + fRec14[1] + fRec35 + fRec27 + fTemp18 - (fRec38[1] + fRec30[1] + fRec22[1] + fRec10[1] + fRec39 + fRec31 + fTemp17);
		fRec7[0] = fRec38[1] + fRec30[1] + fRec18[1] + fRec14[1] + fRec39 + fRec31 + fTemp18 - (fRec34[1] + fRec26[1] + fRec22[1] + fRec10[1] + fRec35 + fRec27 + fTemp17);
		double fTemp19 = fRec11 + fRec19;
		double fTemp20 = fRec15 + fRec23;
		fRec8[0] = fRec38[1] + fRec26[1] + fRec22[1] + fRec14[1] + fRec39 + fRec27 + fTemp20 - (fRec34[1] + fRec30[1] + fRec18[1] + fRec10[1] + fRec35 + fRec31 + fTemp19);
		fRec9[0] = fRec34[1] + fRec30[1] + fRec22[1] + fRec14[1] + fRec35 + fRec31 + fTemp20 - (fRec38[1] + fRec26[1] + fRec18[1] + fRec10[1] + fRec39 + fRec27 + fTemp19);
		double fTemp21 = 0.37 * (fRec3[0] + fRec4[0]);
		double fTemp22 = fTemp21 + fTemp1;
		fRec1[0] = fTemp22 - fSlow8 * fRec1[2];
		double fTemp23 = fSlow8 * fRec1[0];
		double fTemp24 = fSlow5 * (fRec1[2] + fTemp23 - fTemp22);
		double fTemp25 = fTemp23 + fTemp21 + fRec1[2];
		fRec0[0] = 0.5 * (fTemp25 - fTemp1 + fTemp24) + fTemp0 - fSlow3 * fRec0[2];
		double fTemp26 = 0.5 * (fTemp25 + fTemp24 - fTemp1);
		double fTemp27 = fRec0[2] + fSlow3 * fRec0[0];
		fRec42[0] = fSlow89 + 0.999 * fRec42[1];
		double fTemp28 = fRec42[0] + 1.0;
		double fTemp29 = 1.0 - 0.5 * fTemp28;
		fRec43[0] = fSlow90 + 0.999 * fRec43[1];
		double fTemp30 = std::pow(1e+01, 0.05 * fRec43[0]);
		output0[i0] = FAUSTFLOAT(fTemp30 * (fTemp2 * fTemp29 + 0.25 * fTemp28 * (fTemp27 + fTemp26 + fSlow0 * (fTemp27 - (fTemp0 + fTemp26)) - fTemp0)));
		double fTemp31 = fSlow4 * fRec44[1];
		double fTemp32 = fSlow9 * fRec45[1];
		double fTemp33 = 0.37 * (fRec3[0] - fRec4[0]);
		double fTemp34 = fTemp33 + fTemp32;
		fRec45[0] = fTemp34 - fSlow8 * fRec45[2];
		double fTemp35 = fSlow8 * fRec45[0];
		double fTemp36 = fSlow5 * (fRec45[2] + fTemp35 - fTemp34);
		double fTemp37 = fTemp35 + fTemp33 + fRec45[2];
		fRec44[0] = 0.5 * (fTemp37 - fTemp32 + fTemp36) + fTemp31 - fSlow3 * fRec44[2];
		double fTemp38 = 0.5 * (fTemp37 + fTemp36 - fTemp32);
		double fTemp39 = fRec44[2] + fSlow3 * fRec44[0];
		output1[i0] = FAUSTFLOAT(fTemp30 * (fTemp10 * fTemp29 + 0.25 * fTemp28 * (fTemp39 + fTemp38 + fSlow0 * (fTemp39 - (fTemp31 + fTemp38)) - fTemp31)));
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		IOTA0 = IOTA0 + 1;
		fRec10[1] = fRec10[0];
		fRec17[1] = fRec17[0];
		fRec16[1] = fRec16[0];
		fRec14[1] = fRec14[0];
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fRec18[1] = fRec18[0];
		fRec25[1] = fRec25[0];
		fRec24[1] = fRec24[0];
		fRec22[1] = fRec22[0];
		fRec29[1] = fRec29[0];
		fRec28[1] = fRec28[0];
		fRec26[1] = fRec26[0];
		fRec33[1] = fRec33[0];
		fRec32[1] = fRec32[0];
		fRec30[1] = fRec30[0];
		fRec37[1] = fRec37[0];
		fRec36[1] = fRec36[0];
		fRec34[1] = fRec34[0];
		fRec41[1] = fRec41[0];
		fRec40[1] = fRec40[0];
		fRec38[1] = fRec38[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		fRec42[1] = fRec42[0];
		fRec43[1] = fRec43[0];
		fRec45[2] = fRec45[1];
		fRec45[1] = fRec45[0];
		fRec44[2] = fRec44[1];
		fRec44[1] = fRec44[0];
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
#undef fVslider3
#undef fVslider4
#undef fVslider5
#undef fVslider6
#undef fVslider7
#undef fVslider8
#undef fVslider9
#undef fVslider10
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case HF_DAMPING: 
		fVslider5_ = (float*)data; // , 6e+03, 1.5e+03, 2.352e+04, 1.0 
		break;
	case LF_X: 
		fVslider6_ = (float*)data; // , 2e+02, 5e+01, 1e+03, 1.0 
		break;
	case LOW_RT60: 
		fVslider7_ = (float*)data; // , 3.0, 1.0, 8.0, 0.1 
		break;
	case MID_RT60: 
		fVslider4_ = (float*)data; // , 2.0, 1.0, 8.0, 0.1 
		break;
	case EQ1_FREQ: 
		fVslider3_ = (float*)data; // , 315.0, 4e+01, 2.5e+03, 1.0 
		break;
	case EQ1_LEVEL: 
		fVslider2_ = (float*)data; // , 0.0, -15.0, 15.0, 0.1 
		break;
	case EQ2_FREQ: 
		fVslider1_ = (float*)data; // , 1.5e+03, 1.6e+02, 1e+04, 1.0 
		break;
	case EQ2_LEVEL: 
		fVslider0_ = (float*)data; // , 0.0, -15.0, 15.0, 0.1 
		break;
	case IN_DELAY: 
		fVslider8_ = (float*)data; // , 6e+01, 2e+01, 1e+02, 1.0 
		break;
	case DRY_WET_MIX: 
		fVslider9_ = (float*)data; // , 0.0, -1.0, 1.0, 0.01 
		break;
	case LEVEL: 
		fVslider10_ = (float*)data; // , 0.0, -7e+01, 4e+01, 0.1 
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
   HF_DAMPING, 
   LF_X, 
   LOW_RT60, 
   MID_RT60, 
   EQ1_FREQ, 
   EQ1_LEVEL, 
   EQ2_FREQ, 
   EQ2_LEVEL, 
   IN_DELAY, 
   DRY_WET_MIX, 
   LEVEL, 
} PortIndex;
*/

} // end namespace gx_zita_rev1
