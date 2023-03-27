// generated from file '../src/LV2/faust/gx_zita_rev1.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace gx_zita_rev1 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec1[2];
	int IOTA0;
	double fVec0[16384];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fConst2;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fConst3;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	double fConst4;
	double fRec13[2];
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT	*fVslider5_;
	double fRec12[2];
	double fVec1[16384];
	int iConst6;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT	*fVslider6_;
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
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT	*fVslider7_;
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT	*fVslider8_;
	double fRec42[3];
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT	*fVslider9_;
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT	*fVslider10_;
	double fRec43[3];
	double fRec44[3];
	double fRec45[3];

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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec1[l1] = 0.0;
	for (int l2 = 0; l2 < 16384; l2 = l2 + 1) fVec0[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec13[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec12[l4] = 0.0;
	for (int l5 = 0; l5 < 16384; l5 = l5 + 1) fVec1[l5] = 0.0;
	for (int l6 = 0; l6 < 4096; l6 = l6 + 1) fVec2[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec10[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec17[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec16[l9] = 0.0;
	for (int l10 = 0; l10 < 16384; l10 = l10 + 1) fVec3[l10] = 0.0;
	for (int l11 = 0; l11 < 2048; l11 = l11 + 1) fVec4[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec14[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec21[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec20[l14] = 0.0;
	for (int l15 = 0; l15 < 16384; l15 = l15 + 1) fVec5[l15] = 0.0;
	for (int l16 = 0; l16 < 4096; l16 = l16 + 1) fVec6[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec18[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec25[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec24[l19] = 0.0;
	for (int l20 = 0; l20 < 16384; l20 = l20 + 1) fVec7[l20] = 0.0;
	for (int l21 = 0; l21 < 2048; l21 = l21 + 1) fVec8[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec22[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec29[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec28[l24] = 0.0;
	for (int l25 = 0; l25 < 32768; l25 = l25 + 1) fVec9[l25] = 0.0;
	for (int l26 = 0; l26 < 16384; l26 = l26 + 1) fVec10[l26] = 0.0;
	for (int l27 = 0; l27 < 4096; l27 = l27 + 1) fVec11[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec26[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec33[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec32[l30] = 0.0;
	for (int l31 = 0; l31 < 16384; l31 = l31 + 1) fVec12[l31] = 0.0;
	for (int l32 = 0; l32 < 4096; l32 = l32 + 1) fVec13[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fRec30[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fRec37[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec36[l35] = 0.0;
	for (int l36 = 0; l36 < 32768; l36 = l36 + 1) fVec14[l36] = 0.0;
	for (int l37 = 0; l37 < 4096; l37 = l37 + 1) fVec15[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fRec34[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec41[l39] = 0.0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec40[l40] = 0.0;
	for (int l41 = 0; l41 < 32768; l41 = l41 + 1) fVec16[l41] = 0.0;
	for (int l42 = 0; l42 < 2048; l42 = l42 + 1) fVec17[l42] = 0.0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fRec38[l43] = 0.0;
	for (int l44 = 0; l44 < 3; l44 = l44 + 1) fRec2[l44] = 0.0;
	for (int l45 = 0; l45 < 3; l45 = l45 + 1) fRec3[l45] = 0.0;
	for (int l46 = 0; l46 < 3; l46 = l46 + 1) fRec4[l46] = 0.0;
	for (int l47 = 0; l47 < 3; l47 = l47 + 1) fRec5[l47] = 0.0;
	for (int l48 = 0; l48 < 3; l48 = l48 + 1) fRec6[l48] = 0.0;
	for (int l49 = 0; l49 < 3; l49 = l49 + 1) fRec7[l49] = 0.0;
	for (int l50 = 0; l50 < 3; l50 = l50 + 1) fRec8[l50] = 0.0;
	for (int l51 = 0; l51 < 3; l51 = l51 + 1) fRec9[l51] = 0.0;
	for (int l52 = 0; l52 < 3; l52 = l52 + 1) fRec42[l52] = 0.0;
	for (int l53 = 0; l53 < 3; l53 = l53 + 1) fRec43[l53] = 0.0;
	for (int l54 = 0; l54 < 3; l54 = l54 + 1) fRec44[l54] = 0.0;
	for (int l55 = 0; l55 < 3; l55 = l55 + 1) fRec45[l55] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = std::floor(0.174713 * fConst0 + 0.5);
	fConst2 = (0.0 - 6.907755278982138 * fConst1) / fConst0;
	fConst3 = 6.283185307179586 / fConst0;
	fConst4 = 3.141592653589793 / fConst0;
	double fConst5 = std::floor(0.022904 * fConst0 + 0.5);
	iConst6 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst1 - fConst5)));
	fConst7 = 0.001 * fConst0;
	iConst8 = int(std::min<double>(2048.0, std::max<double>(0.0, fConst5 + -1.0)));
	double fConst9 = std::floor(0.153129 * fConst0 + 0.5);
	fConst10 = (0.0 - 6.907755278982138 * fConst9) / fConst0;
	double fConst11 = std::floor(0.020346 * fConst0 + 0.5);
	iConst12 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst9 - fConst11)));
	iConst13 = int(std::min<double>(1024.0, std::max<double>(0.0, fConst11 + -1.0)));
	double fConst14 = std::floor(0.127837 * fConst0 + 0.5);
	fConst15 = (0.0 - 6.907755278982138 * fConst14) / fConst0;
	double fConst16 = std::floor(0.031604 * fConst0 + 0.5);
	iConst17 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst14 - fConst16)));
	iConst18 = int(std::min<double>(2048.0, std::max<double>(0.0, fConst16 + -1.0)));
	double fConst19 = std::floor(0.125 * fConst0 + 0.5);
	fConst20 = (0.0 - 6.907755278982138 * fConst19) / fConst0;
	double fConst21 = std::floor(0.013458 * fConst0 + 0.5);
	iConst22 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst19 - fConst21)));
	iConst23 = int(std::min<double>(1024.0, std::max<double>(0.0, fConst21 + -1.0)));
	double fConst24 = std::floor(0.210389 * fConst0 + 0.5);
	fConst25 = (0.0 - 6.907755278982138 * fConst24) / fConst0;
	double fConst26 = std::floor(0.024421 * fConst0 + 0.5);
	iConst27 = int(std::min<double>(16384.0, std::max<double>(0.0, fConst24 - fConst26)));
	iConst28 = int(std::min<double>(2048.0, std::max<double>(0.0, fConst26 + -1.0)));
	double fConst29 = std::floor(0.192303 * fConst0 + 0.5);
	fConst30 = (0.0 - 6.907755278982138 * fConst29) / fConst0;
	double fConst31 = std::floor(0.029291 * fConst0 + 0.5);
	iConst32 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst29 - fConst31)));
	iConst33 = int(std::min<double>(2048.0, std::max<double>(0.0, fConst31 + -1.0)));
	double fConst34 = std::floor(0.256891 * fConst0 + 0.5);
	fConst35 = (0.0 - 6.907755278982138 * fConst34) / fConst0;
	double fConst36 = std::floor(0.027333 * fConst0 + 0.5);
	iConst37 = int(std::min<double>(16384.0, std::max<double>(0.0, fConst34 - fConst36)));
	iConst38 = int(std::min<double>(2048.0, std::max<double>(0.0, fConst36 + -1.0)));
	double fConst39 = std::floor(0.219991 * fConst0 + 0.5);
	fConst40 = (0.0 - 6.907755278982138 * fConst39) / fConst0;
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
	double fSlow0 = 0.0010000000000000009 * double(fVslider0);
	double fSlow1 = 0.0010000000000000009 * double(fVslider1);
	double fSlow2 = double(fVslider2);
	double fSlow3 = std::exp(fConst2 / fSlow2);
	double fSlow4 = mydsp_faustpower2_f(fSlow3);
	double fSlow5 = 1.0 - fSlow4;
	double fSlow6 = std::cos(fConst3 * double(fVslider3));
	double fSlow7 = 1.0 - fSlow6 * fSlow4;
	double fSlow8 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow7) / mydsp_faustpower2_f(fSlow5) + -1.0));
	double fSlow9 = fSlow7 / fSlow5;
	double fSlow10 = fSlow9 - fSlow8;
	double fSlow11 = 1.0 / std::tan(fConst4 * double(fVslider4));
	double fSlow12 = 1.0 - fSlow11;
	double fSlow13 = 1.0 / (fSlow11 + 1.0);
	double fSlow14 = double(fVslider5);
	double fSlow15 = std::exp(fConst2 / fSlow14) / fSlow3 + -1.0;
	double fSlow16 = fSlow3 * (fSlow8 + (1.0 - fSlow9));
	int iSlow17 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst7 * double(fVslider6))));
	double fSlow18 = std::exp(fConst10 / fSlow2);
	double fSlow19 = mydsp_faustpower2_f(fSlow18);
	double fSlow20 = 1.0 - fSlow19;
	double fSlow21 = 1.0 - fSlow19 * fSlow6;
	double fSlow22 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow21) / mydsp_faustpower2_f(fSlow20) + -1.0));
	double fSlow23 = fSlow21 / fSlow20;
	double fSlow24 = fSlow23 - fSlow22;
	double fSlow25 = std::exp(fConst10 / fSlow14) / fSlow18 + -1.0;
	double fSlow26 = fSlow18 * (fSlow22 + (1.0 - fSlow23));
	double fSlow27 = std::exp(fConst15 / fSlow2);
	double fSlow28 = mydsp_faustpower2_f(fSlow27);
	double fSlow29 = 1.0 - fSlow28;
	double fSlow30 = 1.0 - fSlow6 * fSlow28;
	double fSlow31 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow30) / mydsp_faustpower2_f(fSlow29) + -1.0));
	double fSlow32 = fSlow30 / fSlow29;
	double fSlow33 = fSlow32 - fSlow31;
	double fSlow34 = std::exp(fConst15 / fSlow14) / fSlow27 + -1.0;
	double fSlow35 = fSlow27 * (fSlow31 + (1.0 - fSlow32));
	double fSlow36 = std::exp(fConst20 / fSlow2);
	double fSlow37 = mydsp_faustpower2_f(fSlow36);
	double fSlow38 = 1.0 - fSlow37;
	double fSlow39 = 1.0 - fSlow6 * fSlow37;
	double fSlow40 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow39) / mydsp_faustpower2_f(fSlow38) + -1.0));
	double fSlow41 = fSlow39 / fSlow38;
	double fSlow42 = fSlow41 - fSlow40;
	double fSlow43 = std::exp(fConst20 / fSlow14) / fSlow36 + -1.0;
	double fSlow44 = fSlow36 * (fSlow40 + (1.0 - fSlow41));
	double fSlow45 = std::exp(fConst25 / fSlow2);
	double fSlow46 = mydsp_faustpower2_f(fSlow45);
	double fSlow47 = 1.0 - fSlow46;
	double fSlow48 = 1.0 - fSlow6 * fSlow46;
	double fSlow49 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow48) / mydsp_faustpower2_f(fSlow47) + -1.0));
	double fSlow50 = fSlow48 / fSlow47;
	double fSlow51 = fSlow50 - fSlow49;
	double fSlow52 = std::exp(fConst25 / fSlow14) / fSlow45 + -1.0;
	double fSlow53 = fSlow45 * (fSlow49 + (1.0 - fSlow50));
	double fSlow54 = std::exp(fConst30 / fSlow2);
	double fSlow55 = mydsp_faustpower2_f(fSlow54);
	double fSlow56 = 1.0 - fSlow55;
	double fSlow57 = 1.0 - fSlow6 * fSlow55;
	double fSlow58 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow57) / mydsp_faustpower2_f(fSlow56) + -1.0));
	double fSlow59 = fSlow57 / fSlow56;
	double fSlow60 = fSlow59 - fSlow58;
	double fSlow61 = std::exp(fConst30 / fSlow14) / fSlow54 + -1.0;
	double fSlow62 = fSlow54 * (fSlow58 + (1.0 - fSlow59));
	double fSlow63 = std::exp(fConst35 / fSlow2);
	double fSlow64 = mydsp_faustpower2_f(fSlow63);
	double fSlow65 = 1.0 - fSlow64;
	double fSlow66 = 1.0 - fSlow6 * fSlow64;
	double fSlow67 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow66) / mydsp_faustpower2_f(fSlow65) + -1.0));
	double fSlow68 = fSlow66 / fSlow65;
	double fSlow69 = fSlow68 - fSlow67;
	double fSlow70 = std::exp(fConst35 / fSlow14) / fSlow63 + -1.0;
	double fSlow71 = fSlow63 * (fSlow67 + (1.0 - fSlow68));
	double fSlow72 = std::exp(fConst40 / fSlow2);
	double fSlow73 = mydsp_faustpower2_f(fSlow72);
	double fSlow74 = 1.0 - fSlow73;
	double fSlow75 = 1.0 - fSlow6 * fSlow73;
	double fSlow76 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow75) / mydsp_faustpower2_f(fSlow74) + -1.0));
	double fSlow77 = fSlow75 / fSlow74;
	double fSlow78 = fSlow77 - fSlow76;
	double fSlow79 = std::exp(fConst40 / fSlow14) / fSlow72 + -1.0;
	double fSlow80 = fSlow72 * (fSlow76 + (1.0 - fSlow77));
	double fSlow81 = std::pow(1e+01, 0.05 * double(fVslider7));
	double fSlow82 = double(fVslider8);
	double fSlow83 = fConst3 * (fSlow82 / std::sqrt(fSlow81));
	double fSlow84 = (1.0 - fSlow83) / (fSlow83 + 1.0);
	double fSlow85 = 0.0 - std::cos(fConst3 * fSlow82) * (fSlow84 + 1.0);
	double fSlow86 = std::pow(1e+01, 0.05 * double(fVslider9));
	double fSlow87 = double(fVslider10);
	double fSlow88 = fConst3 * (fSlow87 / std::sqrt(fSlow86));
	double fSlow89 = (1.0 - fSlow88) / (fSlow88 + 1.0);
	double fSlow90 = 0.0 - std::cos(fConst3 * fSlow87) * (fSlow89 + 1.0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.999 * fRec0[1];
		double fTemp0 = std::pow(1e+01, 0.05 * fRec0[0]);
		fRec1[0] = fSlow1 + 0.999 * fRec1[1];
		double fTemp1 = fRec1[0] + 1.0;
		double fTemp2 = 1.0 - 0.5 * fTemp1;
		double fTemp3 = double(input0[i0]);
		fVec0[IOTA0 & 16383] = fTemp3;
		fRec13[0] = 0.0 - fSlow13 * (fSlow12 * fRec13[1] - (fRec6[1] + fRec6[2]));
		fRec12[0] = fSlow16 * (fRec6[1] + fSlow15 * fRec13[0]) + fSlow10 * fRec12[1];
		fVec1[IOTA0 & 16383] = 0.35355339059327373 * fRec12[0] + 1e-20;
		double fTemp4 = 0.3 * fVec0[(IOTA0 - iSlow17) & 16383];
		double fTemp5 = fTemp4 + fVec1[(IOTA0 - iConst6) & 16383] - 0.6 * fRec10[1];
		fVec2[IOTA0 & 4095] = fTemp5;
		fRec10[0] = fVec2[(IOTA0 - iConst8) & 4095];
		double fRec11 = 0.6 * fTemp5;
		fRec17[0] = 0.0 - fSlow13 * (fSlow12 * fRec17[1] - (fRec2[1] + fRec2[2]));
		fRec16[0] = fSlow26 * (fRec2[1] + fSlow25 * fRec17[0]) + fSlow24 * fRec16[1];
		fVec3[IOTA0 & 16383] = 0.35355339059327373 * fRec16[0] + 1e-20;
		double fTemp6 = fVec3[(IOTA0 - iConst12) & 16383] + fTemp4 - 0.6 * fRec14[1];
		fVec4[IOTA0 & 2047] = fTemp6;
		fRec14[0] = fVec4[(IOTA0 - iConst13) & 2047];
		double fRec15 = 0.6 * fTemp6;
		double fTemp7 = fRec15 + fRec11;
		fRec21[0] = 0.0 - fSlow13 * (fSlow12 * fRec21[1] - (fRec4[1] + fRec4[2]));
		fRec20[0] = fSlow35 * (fRec4[1] + fSlow34 * fRec21[0]) + fSlow33 * fRec20[1];
		fVec5[IOTA0 & 16383] = 0.35355339059327373 * fRec20[0] + 1e-20;
		double fTemp8 = fVec5[(IOTA0 - iConst17) & 16383] - (fTemp4 + 0.6 * fRec18[1]);
		fVec6[IOTA0 & 4095] = fTemp8;
		fRec18[0] = fVec6[(IOTA0 - iConst18) & 4095];
		double fRec19 = 0.6 * fTemp8;
		fRec25[0] = 0.0 - fSlow13 * (fSlow12 * fRec25[1] - (fRec8[1] + fRec8[2]));
		fRec24[0] = fSlow44 * (fRec8[1] + fSlow43 * fRec25[0]) + fSlow42 * fRec24[1];
		fVec7[IOTA0 & 16383] = 0.35355339059327373 * fRec24[0] + 1e-20;
		double fTemp9 = fVec7[(IOTA0 - iConst22) & 16383] - (fTemp4 + 0.6 * fRec22[1]);
		fVec8[IOTA0 & 2047] = fTemp9;
		fRec22[0] = fVec8[(IOTA0 - iConst23) & 2047];
		double fRec23 = 0.6 * fTemp9;
		double fTemp10 = fRec23 + fRec19 + fTemp7;
		fRec29[0] = 0.0 - fSlow13 * (fSlow12 * fRec29[1] - (fRec3[1] + fRec3[2]));
		fRec28[0] = fSlow53 * (fRec3[1] + fSlow52 * fRec29[0]) + fSlow51 * fRec28[1];
		fVec9[IOTA0 & 32767] = 0.35355339059327373 * fRec28[0] + 1e-20;
		double fTemp11 = double(input1[i0]);
		fVec10[IOTA0 & 16383] = fTemp11;
		double fTemp12 = 0.3 * fVec10[(IOTA0 - iSlow17) & 16383];
		double fTemp13 = fTemp12 + 0.6 * fRec26[1] + fVec9[(IOTA0 - iConst27) & 32767];
		fVec11[IOTA0 & 4095] = fTemp13;
		fRec26[0] = fVec11[(IOTA0 - iConst28) & 4095];
		double fRec27 = 0.0 - 0.6 * fTemp13;
		fRec33[0] = 0.0 - fSlow13 * (fSlow12 * fRec33[1] - (fRec7[1] + fRec7[2]));
		fRec32[0] = fSlow62 * (fRec7[1] + fSlow61 * fRec33[0]) + fSlow60 * fRec32[1];
		fVec12[IOTA0 & 16383] = 0.35355339059327373 * fRec32[0] + 1e-20;
		double fTemp14 = fVec12[(IOTA0 - iConst32) & 16383] + fTemp12 + 0.6 * fRec30[1];
		fVec13[IOTA0 & 4095] = fTemp14;
		fRec30[0] = fVec13[(IOTA0 - iConst33) & 4095];
		double fRec31 = 0.0 - 0.6 * fTemp14;
		fRec37[0] = 0.0 - fSlow13 * (fSlow12 * fRec37[1] - (fRec5[1] + fRec5[2]));
		fRec36[0] = fSlow71 * (fRec5[1] + fSlow70 * fRec37[0]) + fSlow69 * fRec36[1];
		fVec14[IOTA0 & 32767] = 0.35355339059327373 * fRec36[0] + 1e-20;
		double fTemp15 = 0.6 * fRec34[1] + fVec14[(IOTA0 - iConst37) & 32767] - fTemp12;
		fVec15[IOTA0 & 4095] = fTemp15;
		fRec34[0] = fVec15[(IOTA0 - iConst38) & 4095];
		double fRec35 = 0.0 - 0.6 * fTemp15;
		fRec41[0] = 0.0 - fSlow13 * (fSlow12 * fRec41[1] - (fRec9[1] + fRec9[2]));
		fRec40[0] = fSlow80 * (fRec9[1] + fSlow79 * fRec41[0]) + fSlow78 * fRec40[1];
		fVec16[IOTA0 & 32767] = 0.35355339059327373 * fRec40[0] + 1e-20;
		double fTemp16 = 0.6 * fRec38[1] + fVec16[(IOTA0 - iConst42) & 32767] - fTemp12;
		fVec17[IOTA0 & 2047] = fTemp16;
		fRec38[0] = fVec17[(IOTA0 - iConst43) & 2047];
		double fRec39 = 0.0 - 0.6 * fTemp16;
		fRec2[0] = fRec38[1] + fRec34[1] + fRec30[1] + fRec26[1] + fRec22[1] + fRec18[1] + fRec10[1] + fRec14[1] + fRec39 + fRec35 + fRec31 + fRec27 + fTemp10;
		fRec3[0] = fRec22[1] + fRec18[1] + fRec10[1] + fRec14[1] + fTemp10 - (fRec38[1] + fRec34[1] + fRec30[1] + fRec26[1] + fRec39 + fRec35 + fRec27 + fRec31);
		double fTemp17 = fRec19 + fRec23;
		fRec4[0] = fRec30[1] + fRec26[1] + fRec10[1] + fRec14[1] + fRec31 + fRec27 + fTemp7 - (fRec38[1] + fRec34[1] + fRec22[1] + fRec18[1] + fRec39 + fRec35 + fTemp17);
		fRec5[0] = fRec38[1] + fRec34[1] + fRec10[1] + fRec14[1] + fRec39 + fRec35 + fTemp7 - (fRec30[1] + fRec26[1] + fRec22[1] + fRec18[1] + fRec31 + fRec27 + fTemp17);
		double fTemp18 = fRec11 + fRec23;
		double fTemp19 = fRec15 + fRec19;
		fRec6[0] = fRec34[1] + fRec26[1] + fRec18[1] + fRec14[1] + fRec35 + fRec27 + fTemp19 - (fRec38[1] + fRec30[1] + fRec22[1] + fRec10[1] + fRec39 + fRec31 + fTemp18);
		fRec7[0] = fRec38[1] + fRec30[1] + fRec18[1] + fRec14[1] + fRec39 + fRec31 + fTemp19 - (fRec34[1] + fRec26[1] + fRec22[1] + fRec10[1] + fRec35 + fRec27 + fTemp18);
		double fTemp20 = fRec11 + fRec19;
		double fTemp21 = fRec15 + fRec23;
		fRec8[0] = fRec38[1] + fRec26[1] + fRec22[1] + fRec14[1] + fRec39 + fRec27 + fTemp21 - (fRec34[1] + fRec30[1] + fRec18[1] + fRec10[1] + fRec35 + fRec31 + fTemp20);
		fRec9[0] = fRec34[1] + fRec30[1] + fRec22[1] + fRec14[1] + fRec35 + fRec31 + fTemp21 - (fRec38[1] + fRec26[1] + fRec18[1] + fRec10[1] + fRec39 + fRec27 + fTemp20);
		double fTemp22 = 0.37 * (fRec3[0] + fRec4[0]);
		double fTemp23 = fSlow85 * fRec42[1];
		fRec42[0] = fTemp22 - (fTemp23 + fSlow84 * fRec42[2]);
		double fTemp24 = fSlow84 * fRec42[0];
		double fTemp25 = 0.5 * (fTemp24 + fRec42[2] + fTemp22 + fTemp23 + fSlow81 * (fTemp24 + fTemp23 + fRec42[2] - fTemp22));
		double fTemp26 = fSlow90 * fRec43[1];
		fRec43[0] = fTemp25 - (fTemp26 + fSlow89 * fRec43[2]);
		double fTemp27 = fSlow89 * fRec43[0];
		output0[i0] = FAUSTFLOAT((0.25 * fTemp1 * (fTemp27 + fRec43[2] + fTemp25 + fTemp26 + fSlow86 * (fTemp27 + fTemp26 + fRec43[2] - fTemp25)) + fTemp3 * fTemp2) * fTemp0);
		double fTemp28 = 0.37 * (fRec3[0] - fRec4[0]);
		double fTemp29 = fSlow85 * fRec44[1];
		fRec44[0] = fTemp28 - (fTemp29 + fSlow84 * fRec44[2]);
		double fTemp30 = fSlow84 * fRec44[0];
		double fTemp31 = 0.5 * (fTemp30 + fRec44[2] + fTemp28 + fTemp29 + fSlow81 * (fTemp30 + fTemp29 + fRec44[2] - fTemp28));
		double fTemp32 = fSlow90 * fRec45[1];
		fRec45[0] = fTemp31 - (fTemp32 + fSlow89 * fRec45[2]);
		double fTemp33 = fSlow89 * fRec45[0];
		output1[i0] = FAUSTFLOAT(fTemp0 * (0.25 * fTemp1 * (fTemp33 + fRec45[2] + fTemp31 + fTemp32 + fSlow86 * (fTemp33 + fTemp32 + fRec45[2] - fTemp31)) + fTemp11 * fTemp2));
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		IOTA0 = IOTA0 + 1;
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
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
		fRec42[2] = fRec42[1];
		fRec42[1] = fRec42[0];
		fRec43[2] = fRec43[1];
		fRec43[1] = fRec43[0];
		fRec44[2] = fRec44[1];
		fRec44[1] = fRec44[0];
		fRec45[2] = fRec45[1];
		fRec45[1] = fRec45[0];
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
		fVslider3_ = (float*)data; // , 6e+03, 1.5e+03, 2.352e+04, 1.0 
		break;
	case LF_X: 
		fVslider4_ = (float*)data; // , 2e+02, 5e+01, 1e+03, 1.0 
		break;
	case LOW_RT60: 
		fVslider5_ = (float*)data; // , 3.0, 1.0, 8.0, 0.1 
		break;
	case MID_RT60: 
		fVslider2_ = (float*)data; // , 2.0, 1.0, 8.0, 0.1 
		break;
	case EQ1_FREQ: 
		fVslider8_ = (float*)data; // , 315.0, 4e+01, 2.5e+03, 1.0 
		break;
	case EQ1_LEVEL: 
		fVslider7_ = (float*)data; // , 0.0, -15.0, 15.0, 0.1 
		break;
	case EQ2_FREQ: 
		fVslider10_ = (float*)data; // , 1.5e+03, 1.6e+02, 1e+04, 1.0 
		break;
	case EQ2_LEVEL: 
		fVslider9_ = (float*)data; // , 0.0, -15.0, 15.0, 0.1 
		break;
	case IN_DELAY: 
		fVslider6_ = (float*)data; // , 6e+01, 2e+01, 1e+02, 1.0 
		break;
	case DRY_WET_MIX: 
		fVslider1_ = (float*)data; // , 0.0, -1.0, 1.0, 0.01 
		break;
	case LEVEL: 
		fVslider0_ = (float*)data; // , 0.0, -7e+01, 4e+01, 0.1 
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
