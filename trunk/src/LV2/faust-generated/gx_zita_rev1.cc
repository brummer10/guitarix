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
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT	*fVslider5_;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT	*fVslider6_;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT	*fVslider7_;
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT	*fVslider8_;
	double fConst4;
	double fRec15[2];
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT	*fVslider9_;
	double fRec14[2];
	double fVec1[16384];
	double fConst5;
	int iConst6;
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT	*fVslider10_;
	double fConst7;
	double fVec2[4096];
	int iConst8;
	double fRec12[2];
	double fConst9;
	double fConst10;
	double fRec19[2];
	double fRec18[2];
	double fVec3[16384];
	double fConst11;
	int iConst12;
	double fVec4[2048];
	int iConst13;
	double fRec16[2];
	double fConst14;
	double fConst15;
	double fRec23[2];
	double fRec22[2];
	double fVec5[16384];
	double fConst16;
	int iConst17;
	double fVec6[4096];
	int iConst18;
	double fRec20[2];
	double fConst19;
	double fConst20;
	double fRec27[2];
	double fRec26[2];
	double fVec7[16384];
	double fConst21;
	int iConst22;
	double fVec8[2048];
	int iConst23;
	double fRec24[2];
	double fConst24;
	double fConst25;
	double fRec31[2];
	double fRec30[2];
	double fVec9[32768];
	double fConst26;
	int iConst27;
	double fVec10[16384];
	double fVec11[4096];
	int iConst28;
	double fRec28[2];
	double fConst29;
	double fConst30;
	double fRec35[2];
	double fRec34[2];
	double fVec12[16384];
	double fConst31;
	int iConst32;
	double fVec13[4096];
	int iConst33;
	double fRec32[2];
	double fConst34;
	double fConst35;
	double fRec39[2];
	double fRec38[2];
	double fVec14[32768];
	double fConst36;
	int iConst37;
	double fVec15[4096];
	int iConst38;
	double fRec36[2];
	double fConst39;
	double fConst40;
	double fRec43[2];
	double fRec42[2];
	double fVec16[32768];
	double fConst41;
	int iConst42;
	double fVec17[2048];
	int iConst43;
	double fRec40[2];
	double fRec4[3];
	double fRec5[3];
	double fRec6[3];
	double fRec7[3];
	double fRec8[3];
	double fRec9[3];
	double fRec10[3];
	double fRec11[3];
	double fRec3[3];
	double fRec2[3];
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec1[l1] = 0.0;
	for (int l2 = 0; l2 < 16384; l2 = l2 + 1) fVec0[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec15[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec14[l4] = 0.0;
	for (int l5 = 0; l5 < 16384; l5 = l5 + 1) fVec1[l5] = 0.0;
	for (int l6 = 0; l6 < 4096; l6 = l6 + 1) fVec2[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec12[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec19[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec18[l9] = 0.0;
	for (int l10 = 0; l10 < 16384; l10 = l10 + 1) fVec3[l10] = 0.0;
	for (int l11 = 0; l11 < 2048; l11 = l11 + 1) fVec4[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec16[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec23[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec22[l14] = 0.0;
	for (int l15 = 0; l15 < 16384; l15 = l15 + 1) fVec5[l15] = 0.0;
	for (int l16 = 0; l16 < 4096; l16 = l16 + 1) fVec6[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec20[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec27[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec26[l19] = 0.0;
	for (int l20 = 0; l20 < 16384; l20 = l20 + 1) fVec7[l20] = 0.0;
	for (int l21 = 0; l21 < 2048; l21 = l21 + 1) fVec8[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec24[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec31[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec30[l24] = 0.0;
	for (int l25 = 0; l25 < 32768; l25 = l25 + 1) fVec9[l25] = 0.0;
	for (int l26 = 0; l26 < 16384; l26 = l26 + 1) fVec10[l26] = 0.0;
	for (int l27 = 0; l27 < 4096; l27 = l27 + 1) fVec11[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec28[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec35[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec34[l30] = 0.0;
	for (int l31 = 0; l31 < 16384; l31 = l31 + 1) fVec12[l31] = 0.0;
	for (int l32 = 0; l32 < 4096; l32 = l32 + 1) fVec13[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fRec32[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fRec39[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec38[l35] = 0.0;
	for (int l36 = 0; l36 < 32768; l36 = l36 + 1) fVec14[l36] = 0.0;
	for (int l37 = 0; l37 < 4096; l37 = l37 + 1) fVec15[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fRec36[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec43[l39] = 0.0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec42[l40] = 0.0;
	for (int l41 = 0; l41 < 32768; l41 = l41 + 1) fVec16[l41] = 0.0;
	for (int l42 = 0; l42 < 2048; l42 = l42 + 1) fVec17[l42] = 0.0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fRec40[l43] = 0.0;
	for (int l44 = 0; l44 < 3; l44 = l44 + 1) fRec4[l44] = 0.0;
	for (int l45 = 0; l45 < 3; l45 = l45 + 1) fRec5[l45] = 0.0;
	for (int l46 = 0; l46 < 3; l46 = l46 + 1) fRec6[l46] = 0.0;
	for (int l47 = 0; l47 < 3; l47 = l47 + 1) fRec7[l47] = 0.0;
	for (int l48 = 0; l48 < 3; l48 = l48 + 1) fRec8[l48] = 0.0;
	for (int l49 = 0; l49 < 3; l49 = l49 + 1) fRec9[l49] = 0.0;
	for (int l50 = 0; l50 < 3; l50 = l50 + 1) fRec10[l50] = 0.0;
	for (int l51 = 0; l51 < 3; l51 = l51 + 1) fRec11[l51] = 0.0;
	for (int l52 = 0; l52 < 3; l52 = l52 + 1) fRec3[l52] = 0.0;
	for (int l53 = 0; l53 < 3; l53 = l53 + 1) fRec2[l53] = 0.0;
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
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 6.283185307179586 / fConst0;
	fConst2 = std::floor(0.174713 * fConst0 + 0.5);
	fConst3 = 6.907755278982138 * (fConst2 / fConst0);
	fConst4 = 3.141592653589793 / fConst0;
	fConst5 = std::floor(0.022904 * fConst0 + 0.5);
	iConst6 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst2 - fConst5)));
	fConst7 = 0.001 * fConst0;
	iConst8 = int(std::min<double>(2048.0, std::max<double>(0.0, fConst5 + -1.0)));
	fConst9 = std::floor(0.153129 * fConst0 + 0.5);
	fConst10 = 6.907755278982138 * (fConst9 / fConst0);
	fConst11 = std::floor(0.020346 * fConst0 + 0.5);
	iConst12 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst9 - fConst11)));
	iConst13 = int(std::min<double>(1024.0, std::max<double>(0.0, fConst11 + -1.0)));
	fConst14 = std::floor(0.127837 * fConst0 + 0.5);
	fConst15 = 6.907755278982138 * (fConst14 / fConst0);
	fConst16 = std::floor(0.031604 * fConst0 + 0.5);
	iConst17 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst14 - fConst16)));
	iConst18 = int(std::min<double>(2048.0, std::max<double>(0.0, fConst16 + -1.0)));
	fConst19 = std::floor(0.125 * fConst0 + 0.5);
	fConst20 = 6.907755278982138 * (fConst19 / fConst0);
	fConst21 = std::floor(0.013458 * fConst0 + 0.5);
	iConst22 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst19 - fConst21)));
	iConst23 = int(std::min<double>(1024.0, std::max<double>(0.0, fConst21 + -1.0)));
	fConst24 = std::floor(0.210389 * fConst0 + 0.5);
	fConst25 = 6.907755278982138 * (fConst24 / fConst0);
	fConst26 = std::floor(0.024421 * fConst0 + 0.5);
	iConst27 = int(std::min<double>(16384.0, std::max<double>(0.0, fConst24 - fConst26)));
	iConst28 = int(std::min<double>(2048.0, std::max<double>(0.0, fConst26 + -1.0)));
	fConst29 = std::floor(0.192303 * fConst0 + 0.5);
	fConst30 = 6.907755278982138 * (fConst29 / fConst0);
	fConst31 = std::floor(0.029291 * fConst0 + 0.5);
	iConst32 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst29 - fConst31)));
	iConst33 = int(std::min<double>(2048.0, std::max<double>(0.0, fConst31 + -1.0)));
	fConst34 = std::floor(0.256891 * fConst0 + 0.5);
	fConst35 = 6.907755278982138 * (fConst34 / fConst0);
	fConst36 = std::floor(0.027333 * fConst0 + 0.5);
	iConst37 = int(std::min<double>(16384.0, std::max<double>(0.0, fConst34 - fConst36)));
	iConst38 = int(std::min<double>(2048.0, std::max<double>(0.0, fConst36 + -1.0)));
	fConst39 = std::floor(0.219991 * fConst0 + 0.5);
	fConst40 = 6.907755278982138 * (fConst39 / fConst0);
	fConst41 = std::floor(0.019123 * fConst0 + 0.5);
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
	double fSlow2 = std::pow(1e+01, 0.05 * double(fVslider2));
	double fSlow3 = double(fVslider3);
	double fSlow4 = fConst1 * (fSlow3 / std::sqrt(fSlow2));
	double fSlow5 = (1.0 - fSlow4) / (fSlow4 + 1.0);
	double fSlow6 = std::cos(fConst1 * fSlow3) * (fSlow5 + 1.0);
	double fSlow7 = std::pow(1e+01, 0.05 * double(fVslider4));
	double fSlow8 = double(fVslider5);
	double fSlow9 = fConst1 * (fSlow8 / std::sqrt(fSlow7));
	double fSlow10 = (1.0 - fSlow9) / (fSlow9 + 1.0);
	double fSlow11 = std::cos(fConst1 * fSlow8) * (fSlow10 + 1.0);
	double fSlow12 = double(fVslider6);
	double fSlow13 = std::exp(-(fConst3 / fSlow12));
	double fSlow14 = mydsp_faustpower2_f(fSlow13);
	double fSlow15 = 1.0 - fSlow14;
	double fSlow16 = std::cos(fConst1 * double(fVslider7));
	double fSlow17 = 1.0 - fSlow16 * fSlow14;
	double fSlow18 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow17) / mydsp_faustpower2_f(fSlow15) + -1.0));
	double fSlow19 = fSlow17 / fSlow15;
	double fSlow20 = fSlow19 - fSlow18;
	double fSlow21 = 1.0 / std::tan(fConst4 * double(fVslider8));
	double fSlow22 = 1.0 - fSlow21;
	double fSlow23 = 1.0 / (fSlow21 + 1.0);
	double fSlow24 = double(fVslider9);
	double fSlow25 = std::exp(-(fConst3 / fSlow24)) / fSlow13 + -1.0;
	double fSlow26 = fSlow13 * (fSlow18 + (1.0 - fSlow19));
	int iSlow27 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst7 * double(fVslider10))));
	double fSlow28 = std::exp(-(fConst10 / fSlow12));
	double fSlow29 = mydsp_faustpower2_f(fSlow28);
	double fSlow30 = 1.0 - fSlow29;
	double fSlow31 = 1.0 - fSlow29 * fSlow16;
	double fSlow32 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow31) / mydsp_faustpower2_f(fSlow30) + -1.0));
	double fSlow33 = fSlow31 / fSlow30;
	double fSlow34 = fSlow33 - fSlow32;
	double fSlow35 = std::exp(-(fConst10 / fSlow24)) / fSlow28 + -1.0;
	double fSlow36 = fSlow28 * (fSlow32 + (1.0 - fSlow33));
	double fSlow37 = std::exp(-(fConst15 / fSlow12));
	double fSlow38 = mydsp_faustpower2_f(fSlow37);
	double fSlow39 = 1.0 - fSlow38;
	double fSlow40 = 1.0 - fSlow16 * fSlow38;
	double fSlow41 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow40) / mydsp_faustpower2_f(fSlow39) + -1.0));
	double fSlow42 = fSlow40 / fSlow39;
	double fSlow43 = fSlow42 - fSlow41;
	double fSlow44 = std::exp(-(fConst15 / fSlow24)) / fSlow37 + -1.0;
	double fSlow45 = fSlow37 * (fSlow41 + (1.0 - fSlow42));
	double fSlow46 = std::exp(-(fConst20 / fSlow12));
	double fSlow47 = mydsp_faustpower2_f(fSlow46);
	double fSlow48 = 1.0 - fSlow47;
	double fSlow49 = 1.0 - fSlow16 * fSlow47;
	double fSlow50 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow49) / mydsp_faustpower2_f(fSlow48) + -1.0));
	double fSlow51 = fSlow49 / fSlow48;
	double fSlow52 = fSlow51 - fSlow50;
	double fSlow53 = std::exp(-(fConst20 / fSlow24)) / fSlow46 + -1.0;
	double fSlow54 = fSlow46 * (fSlow50 + (1.0 - fSlow51));
	double fSlow55 = std::exp(-(fConst25 / fSlow12));
	double fSlow56 = mydsp_faustpower2_f(fSlow55);
	double fSlow57 = 1.0 - fSlow56;
	double fSlow58 = 1.0 - fSlow16 * fSlow56;
	double fSlow59 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow58) / mydsp_faustpower2_f(fSlow57) + -1.0));
	double fSlow60 = fSlow58 / fSlow57;
	double fSlow61 = fSlow60 - fSlow59;
	double fSlow62 = std::exp(-(fConst25 / fSlow24)) / fSlow55 + -1.0;
	double fSlow63 = fSlow55 * (fSlow59 + (1.0 - fSlow60));
	double fSlow64 = std::exp(-(fConst30 / fSlow12));
	double fSlow65 = mydsp_faustpower2_f(fSlow64);
	double fSlow66 = 1.0 - fSlow65;
	double fSlow67 = 1.0 - fSlow16 * fSlow65;
	double fSlow68 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow67) / mydsp_faustpower2_f(fSlow66) + -1.0));
	double fSlow69 = fSlow67 / fSlow66;
	double fSlow70 = fSlow69 - fSlow68;
	double fSlow71 = std::exp(-(fConst30 / fSlow24)) / fSlow64 + -1.0;
	double fSlow72 = fSlow64 * (fSlow68 + (1.0 - fSlow69));
	double fSlow73 = std::exp(-(fConst35 / fSlow12));
	double fSlow74 = mydsp_faustpower2_f(fSlow73);
	double fSlow75 = 1.0 - fSlow74;
	double fSlow76 = 1.0 - fSlow16 * fSlow74;
	double fSlow77 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow76) / mydsp_faustpower2_f(fSlow75) + -1.0));
	double fSlow78 = fSlow76 / fSlow75;
	double fSlow79 = fSlow78 - fSlow77;
	double fSlow80 = std::exp(-(fConst35 / fSlow24)) / fSlow73 + -1.0;
	double fSlow81 = fSlow73 * (fSlow77 + (1.0 - fSlow78));
	double fSlow82 = std::exp(-(fConst40 / fSlow12));
	double fSlow83 = mydsp_faustpower2_f(fSlow82);
	double fSlow84 = 1.0 - fSlow83;
	double fSlow85 = 1.0 - fSlow16 * fSlow83;
	double fSlow86 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow85) / mydsp_faustpower2_f(fSlow84) + -1.0));
	double fSlow87 = fSlow85 / fSlow84;
	double fSlow88 = fSlow87 - fSlow86;
	double fSlow89 = std::exp(-(fConst40 / fSlow24)) / fSlow82 + -1.0;
	double fSlow90 = fSlow82 * (fSlow86 + (1.0 - fSlow87));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.999 * fRec0[1];
		double fTemp0 = std::pow(1e+01, 0.05 * fRec0[0]);
		fRec1[0] = fSlow1 + 0.999 * fRec1[1];
		double fTemp1 = fRec1[0] + 1.0;
		double fTemp2 = 1.0 - 0.5 * fTemp1;
		double fTemp3 = double(input0[i0]);
		fVec0[IOTA0 & 16383] = fTemp3;
		double fTemp4 = fSlow6 * fRec2[1];
		double fTemp5 = fSlow11 * fRec3[1];
		fRec15[0] = -(fSlow23 * (fSlow22 * fRec15[1] - (fRec8[1] + fRec8[2])));
		fRec14[0] = fSlow26 * (fRec8[1] + fSlow25 * fRec15[0]) + fSlow20 * fRec14[1];
		fVec1[IOTA0 & 16383] = 0.35355339059327373 * fRec14[0] + 1e-20;
		double fTemp6 = 0.3 * fVec0[(IOTA0 - iSlow27) & 16383];
		double fTemp7 = fTemp6 + fVec1[(IOTA0 - iConst6) & 16383] - 0.6 * fRec12[1];
		fVec2[IOTA0 & 4095] = fTemp7;
		fRec12[0] = fVec2[(IOTA0 - iConst8) & 4095];
		double fRec13 = 0.6 * fTemp7;
		fRec19[0] = -(fSlow23 * (fSlow22 * fRec19[1] - (fRec4[1] + fRec4[2])));
		fRec18[0] = fSlow36 * (fRec4[1] + fSlow35 * fRec19[0]) + fSlow34 * fRec18[1];
		fVec3[IOTA0 & 16383] = 0.35355339059327373 * fRec18[0] + 1e-20;
		double fTemp8 = fVec3[(IOTA0 - iConst12) & 16383] + fTemp6 - 0.6 * fRec16[1];
		fVec4[IOTA0 & 2047] = fTemp8;
		fRec16[0] = fVec4[(IOTA0 - iConst13) & 2047];
		double fRec17 = 0.6 * fTemp8;
		double fTemp9 = fRec17 + fRec13;
		fRec23[0] = -(fSlow23 * (fSlow22 * fRec23[1] - (fRec6[1] + fRec6[2])));
		fRec22[0] = fSlow45 * (fRec6[1] + fSlow44 * fRec23[0]) + fSlow43 * fRec22[1];
		fVec5[IOTA0 & 16383] = 0.35355339059327373 * fRec22[0] + 1e-20;
		double fTemp10 = fVec5[(IOTA0 - iConst17) & 16383] - (fTemp6 + 0.6 * fRec20[1]);
		fVec6[IOTA0 & 4095] = fTemp10;
		fRec20[0] = fVec6[(IOTA0 - iConst18) & 4095];
		double fRec21 = 0.6 * fTemp10;
		fRec27[0] = -(fSlow23 * (fSlow22 * fRec27[1] - (fRec10[1] + fRec10[2])));
		fRec26[0] = fSlow54 * (fRec10[1] + fSlow53 * fRec27[0]) + fSlow52 * fRec26[1];
		fVec7[IOTA0 & 16383] = 0.35355339059327373 * fRec26[0] + 1e-20;
		double fTemp11 = fVec7[(IOTA0 - iConst22) & 16383] - (fTemp6 + 0.6 * fRec24[1]);
		fVec8[IOTA0 & 2047] = fTemp11;
		fRec24[0] = fVec8[(IOTA0 - iConst23) & 2047];
		double fRec25 = 0.6 * fTemp11;
		double fTemp12 = fRec25 + fRec21 + fTemp9;
		fRec31[0] = -(fSlow23 * (fSlow22 * fRec31[1] - (fRec5[1] + fRec5[2])));
		fRec30[0] = fSlow63 * (fRec5[1] + fSlow62 * fRec31[0]) + fSlow61 * fRec30[1];
		fVec9[IOTA0 & 32767] = 0.35355339059327373 * fRec30[0] + 1e-20;
		double fTemp13 = double(input1[i0]);
		fVec10[IOTA0 & 16383] = fTemp13;
		double fTemp14 = 0.3 * fVec10[(IOTA0 - iSlow27) & 16383];
		double fTemp15 = fTemp14 + 0.6 * fRec28[1] + fVec9[(IOTA0 - iConst27) & 32767];
		fVec11[IOTA0 & 4095] = fTemp15;
		fRec28[0] = fVec11[(IOTA0 - iConst28) & 4095];
		double fRec29 = -(0.6 * fTemp15);
		fRec35[0] = -(fSlow23 * (fSlow22 * fRec35[1] - (fRec9[1] + fRec9[2])));
		fRec34[0] = fSlow72 * (fRec9[1] + fSlow71 * fRec35[0]) + fSlow70 * fRec34[1];
		fVec12[IOTA0 & 16383] = 0.35355339059327373 * fRec34[0] + 1e-20;
		double fTemp16 = fVec12[(IOTA0 - iConst32) & 16383] + fTemp14 + 0.6 * fRec32[1];
		fVec13[IOTA0 & 4095] = fTemp16;
		fRec32[0] = fVec13[(IOTA0 - iConst33) & 4095];
		double fRec33 = -(0.6 * fTemp16);
		fRec39[0] = -(fSlow23 * (fSlow22 * fRec39[1] - (fRec7[1] + fRec7[2])));
		fRec38[0] = fSlow81 * (fRec7[1] + fSlow80 * fRec39[0]) + fSlow79 * fRec38[1];
		fVec14[IOTA0 & 32767] = 0.35355339059327373 * fRec38[0] + 1e-20;
		double fTemp17 = 0.6 * fRec36[1] + fVec14[(IOTA0 - iConst37) & 32767];
		fVec15[IOTA0 & 4095] = fTemp17 - fTemp14;
		fRec36[0] = fVec15[(IOTA0 - iConst38) & 4095];
		double fRec37 = 0.6 * (fTemp14 - fTemp17);
		fRec43[0] = -(fSlow23 * (fSlow22 * fRec43[1] - (fRec11[1] + fRec11[2])));
		fRec42[0] = fSlow90 * (fRec11[1] + fSlow89 * fRec43[0]) + fSlow88 * fRec42[1];
		fVec16[IOTA0 & 32767] = 0.35355339059327373 * fRec42[0] + 1e-20;
		double fTemp18 = 0.6 * fRec40[1] + fVec16[(IOTA0 - iConst42) & 32767];
		fVec17[IOTA0 & 2047] = fTemp18 - fTemp14;
		fRec40[0] = fVec17[(IOTA0 - iConst43) & 2047];
		double fRec41 = 0.6 * (fTemp14 - fTemp18);
		fRec4[0] = fRec40[1] + fRec36[1] + fRec32[1] + fRec28[1] + fRec24[1] + fRec20[1] + fRec12[1] + fRec16[1] + fRec41 + fRec37 + fRec33 + fRec29 + fTemp12;
		fRec5[0] = fRec24[1] + fRec20[1] + fRec12[1] + fRec16[1] + fTemp12 - (fRec40[1] + fRec36[1] + fRec32[1] + fRec28[1] + fRec41 + fRec37 + fRec29 + fRec33);
		double fTemp19 = fRec21 + fRec25;
		fRec6[0] = fRec32[1] + fRec28[1] + fRec12[1] + fRec16[1] + fRec33 + fRec29 + fTemp9 - (fRec40[1] + fRec36[1] + fRec24[1] + fRec20[1] + fRec41 + fRec37 + fTemp19);
		fRec7[0] = fRec40[1] + fRec36[1] + fRec12[1] + fRec16[1] + fRec41 + fRec37 + fTemp9 - (fRec32[1] + fRec28[1] + fRec24[1] + fRec20[1] + fRec33 + fRec29 + fTemp19);
		double fTemp20 = fRec13 + fRec25;
		double fTemp21 = fRec17 + fRec21;
		fRec8[0] = fRec36[1] + fRec28[1] + fRec20[1] + fRec16[1] + fRec37 + fRec29 + fTemp21 - (fRec40[1] + fRec32[1] + fRec24[1] + fRec12[1] + fRec41 + fRec33 + fTemp20);
		fRec9[0] = fRec40[1] + fRec32[1] + fRec20[1] + fRec16[1] + fRec41 + fRec33 + fTemp21 - (fRec36[1] + fRec28[1] + fRec24[1] + fRec12[1] + fRec37 + fRec29 + fTemp20);
		double fTemp22 = fRec13 + fRec21;
		double fTemp23 = fRec17 + fRec25;
		fRec10[0] = fRec40[1] + fRec28[1] + fRec24[1] + fRec16[1] + fRec41 + fRec29 + fTemp23 - (fRec36[1] + fRec32[1] + fRec20[1] + fRec12[1] + fRec37 + fRec33 + fTemp22);
		fRec11[0] = fRec36[1] + fRec32[1] + fRec24[1] + fRec16[1] + fRec37 + fRec33 + fTemp23 - (fRec40[1] + fRec28[1] + fRec20[1] + fRec12[1] + fRec41 + fRec29 + fTemp22);
		double fTemp24 = 0.37 * (fRec5[0] + fRec6[0]);
		double fTemp25 = fTemp24 + fTemp5;
		fRec3[0] = fTemp25 - fSlow10 * fRec3[2];
		double fTemp26 = fSlow10 * fRec3[0];
		double fTemp27 = 0.5 * (fTemp26 + fTemp24 + fRec3[2] - fTemp5 + fSlow7 * (fRec3[2] + fTemp26 - fTemp25));
		double fTemp28 = fTemp27 + fTemp4;
		fRec2[0] = fTemp28 - fSlow5 * fRec2[2];
		double fTemp29 = fSlow5 * fRec2[0];
		output0[i0] = FAUSTFLOAT((0.25 * fTemp1 * (fTemp29 + fTemp27 + fRec2[2] - fTemp4 + fSlow2 * (fRec2[2] + fTemp29 - fTemp28)) + fTemp3 * fTemp2) * fTemp0);
		double fTemp30 = fSlow6 * fRec44[1];
		double fTemp31 = fSlow11 * fRec45[1];
		double fTemp32 = 0.37 * (fRec5[0] - fRec6[0]);
		double fTemp33 = fTemp32 + fTemp31;
		fRec45[0] = fTemp33 - fSlow10 * fRec45[2];
		double fTemp34 = fSlow10 * fRec45[0];
		double fTemp35 = 0.5 * (fTemp34 + fTemp32 + fRec45[2] - fTemp31 + fSlow7 * (fRec45[2] + fTemp34 - fTemp33));
		double fTemp36 = fTemp35 + fTemp30;
		fRec44[0] = fTemp36 - fSlow5 * fRec44[2];
		double fTemp37 = fSlow5 * fRec44[0];
		output1[i0] = FAUSTFLOAT(fTemp0 * (0.25 * fTemp1 * (fTemp37 + fTemp35 + fRec44[2] - fTemp30 + fSlow2 * (fRec44[2] + fTemp37 - fTemp36)) + fTemp13 * fTemp2));
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		IOTA0 = IOTA0 + 1;
		fRec15[1] = fRec15[0];
		fRec14[1] = fRec14[0];
		fRec12[1] = fRec12[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec16[1] = fRec16[0];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec20[1] = fRec20[0];
		fRec27[1] = fRec27[0];
		fRec26[1] = fRec26[0];
		fRec24[1] = fRec24[0];
		fRec31[1] = fRec31[0];
		fRec30[1] = fRec30[0];
		fRec28[1] = fRec28[0];
		fRec35[1] = fRec35[0];
		fRec34[1] = fRec34[0];
		fRec32[1] = fRec32[0];
		fRec39[1] = fRec39[0];
		fRec38[1] = fRec38[0];
		fRec36[1] = fRec36[0];
		fRec43[1] = fRec43[0];
		fRec42[1] = fRec42[0];
		fRec40[1] = fRec40[0];
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
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
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
		fVslider7_ = (float*)data; // , 6e+03, 1.5e+03, 2.352e+04, 1.0 
		break;
	case LF_X: 
		fVslider8_ = (float*)data; // , 2e+02, 5e+01, 1e+03, 1.0 
		break;
	case LOW_RT60: 
		fVslider9_ = (float*)data; // , 3.0, 1.0, 8.0, 0.1 
		break;
	case MID_RT60: 
		fVslider6_ = (float*)data; // , 2.0, 1.0, 8.0, 0.1 
		break;
	case EQ1_FREQ: 
		fVslider5_ = (float*)data; // , 315.0, 4e+01, 2.5e+03, 1.0 
		break;
	case EQ1_LEVEL: 
		fVslider4_ = (float*)data; // , 0.0, -15.0, 15.0, 0.1 
		break;
	case EQ2_FREQ: 
		fVslider3_ = (float*)data; // , 1.5e+03, 1.6e+02, 1e+04, 1.0 
		break;
	case EQ2_LEVEL: 
		fVslider2_ = (float*)data; // , 0.0, -15.0, 15.0, 0.1 
		break;
	case IN_DELAY: 
		fVslider10_ = (float*)data; // , 6e+01, 2e+01, 1e+02, 1.0 
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
