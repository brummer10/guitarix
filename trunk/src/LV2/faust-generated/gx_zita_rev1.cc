// generated from file '../src/LV2/faust/gx_zita_rev1.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace gx_zita_rev1 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	double fConst1;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
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
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT	*fVslider7_;
	double fConst4;
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT	*fVslider8_;
	double fRec14[2];
	double fRec13[2];
	int IOTA0;
	double fVec0[32768];
	int iConst6;
	double fVec1[16384];
	double fConst7;
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT	*fVslider9_;
	double fVec2[2048];
	int iConst8;
	double fRec11[2];
	double fConst10;
	double fRec18[2];
	double fRec17[2];
	double fVec3[32768];
	int iConst12;
	double fVec4[4096];
	int iConst13;
	double fRec15[2];
	double fConst15;
	double fRec22[2];
	double fRec21[2];
	double fVec5[16384];
	int iConst17;
	double fVec6[4096];
	int iConst18;
	double fRec19[2];
	double fConst20;
	double fRec26[2];
	double fRec25[2];
	double fVec7[32768];
	int iConst22;
	double fVec8[4096];
	int iConst23;
	double fRec23[2];
	double fConst25;
	double fRec30[2];
	double fRec29[2];
	double fVec9[16384];
	int iConst27;
	double fVec10[16384];
	double fVec11[2048];
	int iConst28;
	double fRec27[2];
	double fConst30;
	double fRec34[2];
	double fRec33[2];
	double fVec12[16384];
	int iConst32;
	double fVec13[4096];
	int iConst33;
	double fRec31[2];
	double fConst35;
	double fRec38[2];
	double fRec37[2];
	double fVec14[16384];
	int iConst37;
	double fVec15[4096];
	int iConst38;
	double fRec35[2];
	double fConst40;
	double fRec42[2];
	double fRec41[2];
	double fVec16[16384];
	int iConst42;
	double fVec17[2048];
	int iConst43;
	double fRec39[2];
	double fRec3[3];
	double fRec4[3];
	double fRec5[3];
	double fRec6[3];
	double fRec7[3];
	double fRec8[3];
	double fRec9[3];
	double fRec10[3];
	double fRec2[3];
	double fRec1[3];
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec14[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec13[l2] = 0.0;
	for (int l3 = 0; l3 < 32768; l3 = l3 + 1) fVec0[l3] = 0.0;
	for (int l4 = 0; l4 < 16384; l4 = l4 + 1) fVec1[l4] = 0.0;
	for (int l5 = 0; l5 < 2048; l5 = l5 + 1) fVec2[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec11[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec18[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec17[l8] = 0.0;
	for (int l9 = 0; l9 < 32768; l9 = l9 + 1) fVec3[l9] = 0.0;
	for (int l10 = 0; l10 < 4096; l10 = l10 + 1) fVec4[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec15[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec22[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec21[l13] = 0.0;
	for (int l14 = 0; l14 < 16384; l14 = l14 + 1) fVec5[l14] = 0.0;
	for (int l15 = 0; l15 < 4096; l15 = l15 + 1) fVec6[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec19[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec26[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec25[l18] = 0.0;
	for (int l19 = 0; l19 < 32768; l19 = l19 + 1) fVec7[l19] = 0.0;
	for (int l20 = 0; l20 < 4096; l20 = l20 + 1) fVec8[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec23[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec30[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec29[l23] = 0.0;
	for (int l24 = 0; l24 < 16384; l24 = l24 + 1) fVec9[l24] = 0.0;
	for (int l25 = 0; l25 < 16384; l25 = l25 + 1) fVec10[l25] = 0.0;
	for (int l26 = 0; l26 < 2048; l26 = l26 + 1) fVec11[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec27[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec34[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec33[l29] = 0.0;
	for (int l30 = 0; l30 < 16384; l30 = l30 + 1) fVec12[l30] = 0.0;
	for (int l31 = 0; l31 < 4096; l31 = l31 + 1) fVec13[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fRec31[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fRec38[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fRec37[l34] = 0.0;
	for (int l35 = 0; l35 < 16384; l35 = l35 + 1) fVec14[l35] = 0.0;
	for (int l36 = 0; l36 < 4096; l36 = l36 + 1) fVec15[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec35[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fRec42[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec41[l39] = 0.0;
	for (int l40 = 0; l40 < 16384; l40 = l40 + 1) fVec16[l40] = 0.0;
	for (int l41 = 0; l41 < 2048; l41 = l41 + 1) fVec17[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) fRec39[l42] = 0.0;
	for (int l43 = 0; l43 < 3; l43 = l43 + 1) fRec3[l43] = 0.0;
	for (int l44 = 0; l44 < 3; l44 = l44 + 1) fRec4[l44] = 0.0;
	for (int l45 = 0; l45 < 3; l45 = l45 + 1) fRec5[l45] = 0.0;
	for (int l46 = 0; l46 < 3; l46 = l46 + 1) fRec6[l46] = 0.0;
	for (int l47 = 0; l47 < 3; l47 = l47 + 1) fRec7[l47] = 0.0;
	for (int l48 = 0; l48 < 3; l48 = l48 + 1) fRec8[l48] = 0.0;
	for (int l49 = 0; l49 < 3; l49 = l49 + 1) fRec9[l49] = 0.0;
	for (int l50 = 0; l50 < 3; l50 = l50 + 1) fRec10[l50] = 0.0;
	for (int l51 = 0; l51 < 3; l51 = l51 + 1) fRec2[l51] = 0.0;
	for (int l52 = 0; l52 < 3; l52 = l52 + 1) fRec1[l52] = 0.0;
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
	double fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 6.2831853071795862 / fConst0;
	double fConst2 = std::floor(0.21999099999999999 * fConst0 + 0.5);
	fConst3 = (0.0 - 6.9077552789821377 * fConst2) / fConst0;
	fConst4 = 3.1415926535897931 / fConst0;
	double fConst5 = std::floor(0.019123000000000001 * fConst0 + 0.5);
	iConst6 = int(std::min<double>(16384.0, std::max<double>(0.0, fConst2 - fConst5)));
	fConst7 = 0.001 * fConst0;
	iConst8 = int(std::min<double>(1024.0, std::max<double>(0.0, fConst5 + -1.0)));
	double fConst9 = std::floor(0.25689099999999998 * fConst0 + 0.5);
	fConst10 = (0.0 - 6.9077552789821377 * fConst9) / fConst0;
	double fConst11 = std::floor(0.027333 * fConst0 + 0.5);
	iConst12 = int(std::min<double>(16384.0, std::max<double>(0.0, fConst9 - fConst11)));
	iConst13 = int(std::min<double>(2048.0, std::max<double>(0.0, fConst11 + -1.0)));
	double fConst14 = std::floor(0.192303 * fConst0 + 0.5);
	fConst15 = (0.0 - 6.9077552789821377 * fConst14) / fConst0;
	double fConst16 = std::floor(0.029291000000000001 * fConst0 + 0.5);
	iConst17 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst14 - fConst16)));
	iConst18 = int(std::min<double>(2048.0, std::max<double>(0.0, fConst16 + -1.0)));
	double fConst19 = std::floor(0.21038899999999999 * fConst0 + 0.5);
	fConst20 = (0.0 - 6.9077552789821377 * fConst19) / fConst0;
	double fConst21 = std::floor(0.024421000000000002 * fConst0 + 0.5);
	iConst22 = int(std::min<double>(16384.0, std::max<double>(0.0, fConst19 - fConst21)));
	iConst23 = int(std::min<double>(2048.0, std::max<double>(0.0, fConst21 + -1.0)));
	double fConst24 = std::floor(0.125 * fConst0 + 0.5);
	fConst25 = (0.0 - 6.9077552789821377 * fConst24) / fConst0;
	double fConst26 = std::floor(0.013457999999999999 * fConst0 + 0.5);
	iConst27 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst24 - fConst26)));
	iConst28 = int(std::min<double>(1024.0, std::max<double>(0.0, fConst26 + -1.0)));
	double fConst29 = std::floor(0.12783700000000001 * fConst0 + 0.5);
	fConst30 = (0.0 - 6.9077552789821377 * fConst29) / fConst0;
	double fConst31 = std::floor(0.031604 * fConst0 + 0.5);
	iConst32 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst29 - fConst31)));
	iConst33 = int(std::min<double>(2048.0, std::max<double>(0.0, fConst31 + -1.0)));
	double fConst34 = std::floor(0.17471300000000001 * fConst0 + 0.5);
	fConst35 = (0.0 - 6.9077552789821377 * fConst34) / fConst0;
	double fConst36 = std::floor(0.022904000000000001 * fConst0 + 0.5);
	iConst37 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst34 - fConst36)));
	iConst38 = int(std::min<double>(2048.0, std::max<double>(0.0, fConst36 + -1.0)));
	double fConst39 = std::floor(0.15312899999999999 * fConst0 + 0.5);
	fConst40 = (0.0 - 6.9077552789821377 * fConst39) / fConst0;
	double fConst41 = std::floor(0.020346 * fConst0 + 0.5);
	iConst42 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst39 - fConst41)));
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
	double fSlow1 = double(fVslider1);
	double fSlow2 = std::pow(10.0, 0.050000000000000003 * double(fVslider2));
	double fSlow3 = fConst1 * fSlow1 / std::sqrt(fSlow2);
	double fSlow4 = (1.0 - fSlow3) / (fSlow3 + 1.0);
	double fSlow5 = double(fVslider3);
	double fSlow6 = std::pow(10.0, 0.050000000000000003 * double(fVslider4));
	double fSlow7 = fConst1 * fSlow5 / std::sqrt(fSlow6);
	double fSlow8 = (1.0 - fSlow7) / (fSlow7 + 1.0);
	double fSlow9 = double(fVslider5);
	double fSlow10 = std::exp(fConst3 / fSlow9);
	double fSlow11 = mydsp_faustpower2_f(fSlow10);
	double fSlow12 = std::cos(fConst1 * double(fVslider6));
	double fSlow13 = 1.0 - fSlow11 * fSlow12;
	double fSlow14 = 1.0 - fSlow11;
	double fSlow15 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow13) / mydsp_faustpower2_f(fSlow14) + -1.0));
	double fSlow16 = fSlow13 / fSlow14;
	double fSlow17 = fSlow10 * (fSlow15 + 1.0 - fSlow16);
	double fSlow18 = double(fVslider7);
	double fSlow19 = std::exp(fConst3 / fSlow18) / fSlow10 + -1.0;
	double fSlow20 = 1.0 / std::tan(fConst4 * double(fVslider8));
	double fSlow21 = 1.0 / (fSlow20 + 1.0);
	double fSlow22 = 1.0 - fSlow20;
	double fSlow23 = fSlow16 - fSlow15;
	int iSlow24 = int(std::min<double>(8192.0, std::max<double>(0.0, fConst7 * double(fVslider9))));
	double fSlow25 = std::exp(fConst10 / fSlow9);
	double fSlow26 = mydsp_faustpower2_f(fSlow25);
	double fSlow27 = 1.0 - fSlow26 * fSlow12;
	double fSlow28 = 1.0 - fSlow26;
	double fSlow29 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow27) / mydsp_faustpower2_f(fSlow28) + -1.0));
	double fSlow30 = fSlow27 / fSlow28;
	double fSlow31 = fSlow25 * (fSlow29 + 1.0 - fSlow30);
	double fSlow32 = std::exp(fConst10 / fSlow18) / fSlow25 + -1.0;
	double fSlow33 = fSlow30 - fSlow29;
	double fSlow34 = std::exp(fConst15 / fSlow9);
	double fSlow35 = mydsp_faustpower2_f(fSlow34);
	double fSlow36 = 1.0 - fSlow35 * fSlow12;
	double fSlow37 = 1.0 - fSlow35;
	double fSlow38 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow36) / mydsp_faustpower2_f(fSlow37) + -1.0));
	double fSlow39 = fSlow36 / fSlow37;
	double fSlow40 = fSlow34 * (fSlow38 + 1.0 - fSlow39);
	double fSlow41 = std::exp(fConst15 / fSlow18) / fSlow34 + -1.0;
	double fSlow42 = fSlow39 - fSlow38;
	double fSlow43 = std::exp(fConst20 / fSlow9);
	double fSlow44 = mydsp_faustpower2_f(fSlow43);
	double fSlow45 = 1.0 - fSlow44 * fSlow12;
	double fSlow46 = 1.0 - fSlow44;
	double fSlow47 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow45) / mydsp_faustpower2_f(fSlow46) + -1.0));
	double fSlow48 = fSlow45 / fSlow46;
	double fSlow49 = fSlow43 * (fSlow47 + 1.0 - fSlow48);
	double fSlow50 = std::exp(fConst20 / fSlow18) / fSlow43 + -1.0;
	double fSlow51 = fSlow48 - fSlow47;
	double fSlow52 = std::exp(fConst25 / fSlow9);
	double fSlow53 = mydsp_faustpower2_f(fSlow52);
	double fSlow54 = 1.0 - fSlow53 * fSlow12;
	double fSlow55 = 1.0 - fSlow53;
	double fSlow56 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow54) / mydsp_faustpower2_f(fSlow55) + -1.0));
	double fSlow57 = fSlow54 / fSlow55;
	double fSlow58 = fSlow52 * (fSlow56 + 1.0 - fSlow57);
	double fSlow59 = std::exp(fConst25 / fSlow18) / fSlow52 + -1.0;
	double fSlow60 = fSlow57 - fSlow56;
	double fSlow61 = std::exp(fConst30 / fSlow9);
	double fSlow62 = mydsp_faustpower2_f(fSlow61);
	double fSlow63 = 1.0 - fSlow62 * fSlow12;
	double fSlow64 = 1.0 - fSlow62;
	double fSlow65 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow63) / mydsp_faustpower2_f(fSlow64) + -1.0));
	double fSlow66 = fSlow63 / fSlow64;
	double fSlow67 = fSlow61 * (fSlow65 + 1.0 - fSlow66);
	double fSlow68 = std::exp(fConst30 / fSlow18) / fSlow61 + -1.0;
	double fSlow69 = fSlow66 - fSlow65;
	double fSlow70 = std::exp(fConst35 / fSlow9);
	double fSlow71 = mydsp_faustpower2_f(fSlow70);
	double fSlow72 = 1.0 - fSlow71 * fSlow12;
	double fSlow73 = 1.0 - fSlow71;
	double fSlow74 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow72) / mydsp_faustpower2_f(fSlow73) + -1.0));
	double fSlow75 = fSlow72 / fSlow73;
	double fSlow76 = fSlow70 * (fSlow74 + 1.0 - fSlow75);
	double fSlow77 = std::exp(fConst35 / fSlow18) / fSlow70 + -1.0;
	double fSlow78 = fSlow75 - fSlow74;
	double fSlow79 = std::exp(fConst40 / fSlow9);
	double fSlow80 = mydsp_faustpower2_f(fSlow79);
	double fSlow81 = 1.0 - fSlow80 * fSlow12;
	double fSlow82 = 1.0 - fSlow80;
	double fSlow83 = std::sqrt(std::max<double>(0.0, mydsp_faustpower2_f(fSlow81) / mydsp_faustpower2_f(fSlow82) + -1.0));
	double fSlow84 = fSlow81 / fSlow82;
	double fSlow85 = fSlow79 * (fSlow83 + 1.0 - fSlow84);
	double fSlow86 = std::exp(fConst40 / fSlow18) / fSlow79 + -1.0;
	double fSlow87 = fSlow84 - fSlow83;
	double fSlow88 = 0.0 - std::cos(fConst1 * fSlow5) * (fSlow8 + 1.0);
	double fSlow89 = 0.0 - std::cos(fConst1 * fSlow1) * (fSlow4 + 1.0);
	double fSlow90 = 0.0010000000000000009 * double(fVslider10);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.999 * fRec0[1];
		double fTemp0 = fRec0[0] + 1.0;
		fRec14[0] = 0.0 - fSlow21 * (fSlow22 * fRec14[1] - (fRec10[1] + fRec10[2]));
		fRec13[0] = fSlow17 * (fRec10[1] + fSlow19 * fRec14[0]) + fSlow23 * fRec13[1];
		fVec0[IOTA0 & 32767] = 0.35355339059327373 * fRec13[0] + 9.9999999999999995e-21;
		double fTemp1 = double(input1[i0]);
		fVec1[IOTA0 & 16383] = fTemp1;
		double fTemp2 = 0.29999999999999999 * fVec1[(IOTA0 - iSlow24) & 16383];
		double fTemp3 = (0.59999999999999998 * fRec11[1] + fVec0[(IOTA0 - iConst6) & 32767]) - fTemp2;
		fVec2[IOTA0 & 2047] = fTemp3;
		fRec11[0] = fVec2[(IOTA0 - iConst8) & 2047];
		double fRec12 = 0.0 - 0.59999999999999998 * fTemp3;
		fRec18[0] = 0.0 - fSlow21 * (fSlow22 * fRec18[1] - (fRec6[1] + fRec6[2]));
		fRec17[0] = fSlow31 * (fRec6[1] + fSlow32 * fRec18[0]) + fSlow33 * fRec17[1];
		fVec3[IOTA0 & 32767] = 0.35355339059327373 * fRec17[0] + 9.9999999999999995e-21;
		double fTemp4 = (0.59999999999999998 * fRec15[1] + fVec3[(IOTA0 - iConst12) & 32767]) - fTemp2;
		fVec4[IOTA0 & 4095] = fTemp4;
		fRec15[0] = fVec4[(IOTA0 - iConst13) & 4095];
		double fRec16 = 0.0 - 0.59999999999999998 * fTemp4;
		fRec22[0] = 0.0 - fSlow21 * (fSlow22 * fRec22[1] - (fRec8[1] + fRec8[2]));
		fRec21[0] = fSlow40 * (fRec8[1] + fSlow41 * fRec22[0]) + fSlow42 * fRec21[1];
		fVec5[IOTA0 & 16383] = 0.35355339059327373 * fRec21[0] + 9.9999999999999995e-21;
		double fTemp5 = fVec5[(IOTA0 - iConst17) & 16383] + fTemp2 + 0.59999999999999998 * fRec19[1];
		fVec6[IOTA0 & 4095] = fTemp5;
		fRec19[0] = fVec6[(IOTA0 - iConst18) & 4095];
		double fRec20 = 0.0 - 0.59999999999999998 * fTemp5;
		fRec26[0] = 0.0 - fSlow21 * (fSlow22 * fRec26[1] - (fRec4[1] + fRec4[2]));
		fRec25[0] = fSlow49 * (fRec4[1] + fSlow50 * fRec26[0]) + fSlow51 * fRec25[1];
		fVec7[IOTA0 & 32767] = 0.35355339059327373 * fRec25[0] + 9.9999999999999995e-21;
		double fTemp6 = fTemp2 + 0.59999999999999998 * fRec23[1] + fVec7[(IOTA0 - iConst22) & 32767];
		fVec8[IOTA0 & 4095] = fTemp6;
		fRec23[0] = fVec8[(IOTA0 - iConst23) & 4095];
		double fRec24 = 0.0 - 0.59999999999999998 * fTemp6;
		fRec30[0] = 0.0 - fSlow21 * (fSlow22 * fRec30[1] - (fRec9[1] + fRec9[2]));
		fRec29[0] = fSlow58 * (fRec9[1] + fSlow59 * fRec30[0]) + fSlow60 * fRec29[1];
		fVec9[IOTA0 & 16383] = 0.35355339059327373 * fRec29[0] + 9.9999999999999995e-21;
		double fTemp7 = double(input0[i0]);
		fVec10[IOTA0 & 16383] = fTemp7;
		double fTemp8 = 0.29999999999999999 * fVec10[(IOTA0 - iSlow24) & 16383];
		double fTemp9 = fVec9[(IOTA0 - iConst27) & 16383] - (fTemp8 + 0.59999999999999998 * fRec27[1]);
		fVec11[IOTA0 & 2047] = fTemp9;
		fRec27[0] = fVec11[(IOTA0 - iConst28) & 2047];
		double fRec28 = 0.59999999999999998 * fTemp9;
		fRec34[0] = 0.0 - fSlow21 * (fSlow22 * fRec34[1] - (fRec5[1] + fRec5[2]));
		fRec33[0] = fSlow67 * (fRec5[1] + fSlow68 * fRec34[0]) + fSlow69 * fRec33[1];
		fVec12[IOTA0 & 16383] = 0.35355339059327373 * fRec33[0] + 9.9999999999999995e-21;
		double fTemp10 = fVec12[(IOTA0 - iConst32) & 16383] - (fTemp8 + 0.59999999999999998 * fRec31[1]);
		fVec13[IOTA0 & 4095] = fTemp10;
		fRec31[0] = fVec13[(IOTA0 - iConst33) & 4095];
		double fRec32 = 0.59999999999999998 * fTemp10;
		fRec38[0] = 0.0 - fSlow21 * (fSlow22 * fRec38[1] - (fRec7[1] + fRec7[2]));
		fRec37[0] = fSlow76 * (fRec7[1] + fSlow77 * fRec38[0]) + fSlow78 * fRec37[1];
		fVec14[IOTA0 & 16383] = 0.35355339059327373 * fRec37[0] + 9.9999999999999995e-21;
		double fTemp11 = (fTemp8 + fVec14[(IOTA0 - iConst37) & 16383]) - 0.59999999999999998 * fRec35[1];
		fVec15[IOTA0 & 4095] = fTemp11;
		fRec35[0] = fVec15[(IOTA0 - iConst38) & 4095];
		double fRec36 = 0.59999999999999998 * fTemp11;
		fRec42[0] = 0.0 - fSlow21 * (fSlow22 * fRec42[1] - (fRec3[1] + fRec3[2]));
		fRec41[0] = fSlow85 * (fRec3[1] + fSlow86 * fRec42[0]) + fSlow87 * fRec41[1];
		fVec16[IOTA0 & 16383] = 0.35355339059327373 * fRec41[0] + 9.9999999999999995e-21;
		double fTemp12 = (fVec16[(IOTA0 - iConst42) & 16383] + fTemp8) - 0.59999999999999998 * fRec39[1];
		fVec17[IOTA0 & 2047] = fTemp12;
		fRec39[0] = fVec17[(IOTA0 - iConst43) & 2047];
		double fRec40 = 0.59999999999999998 * fTemp12;
		double fTemp13 = fRec40 + fRec36;
		double fTemp14 = fRec28 + fRec32 + fTemp13;
		fRec3[0] = fRec11[1] + fRec15[1] + fRec19[1] + fRec23[1] + fRec27[1] + fRec31[1] + fRec35[1] + fRec39[1] + fRec12 + fRec16 + fRec20 + fRec24 + fTemp14;
		fRec4[0] = (fRec27[1] + fRec31[1] + fRec35[1] + fRec39[1] + fTemp14) - (fRec11[1] + fRec15[1] + fRec19[1] + fRec23[1] + fRec12 + fRec16 + fRec24 + fRec20);
		double fTemp15 = fRec32 + fRec28;
		fRec5[0] = (fRec19[1] + fRec23[1] + fRec35[1] + fRec39[1] + fRec20 + fRec24 + fTemp13) - (fRec11[1] + fRec15[1] + fRec27[1] + fRec31[1] + fRec12 + fRec16 + fTemp15);
		fRec6[0] = (fRec11[1] + fRec15[1] + fRec35[1] + fRec39[1] + fRec12 + fRec16 + fTemp13) - (fRec19[1] + fRec23[1] + fRec27[1] + fRec31[1] + fRec20 + fRec24 + fTemp15);
		double fTemp16 = fRec40 + fRec32;
		double fTemp17 = fRec36 + fRec28;
		fRec7[0] = (fRec15[1] + fRec23[1] + fRec31[1] + fRec39[1] + fRec16 + fRec24 + fTemp16) - (fRec11[1] + fRec19[1] + fRec27[1] + fRec35[1] + fRec12 + fRec20 + fTemp17);
		fRec8[0] = (fRec11[1] + fRec19[1] + fRec31[1] + fRec39[1] + fRec12 + fRec20 + fTemp16) - (fRec15[1] + fRec23[1] + fRec27[1] + fRec35[1] + fRec16 + fRec24 + fTemp17);
		double fTemp18 = fRec40 + fRec28;
		double fTemp19 = fRec36 + fRec32;
		fRec9[0] = (fRec11[1] + fRec23[1] + fRec27[1] + fRec39[1] + fRec12 + fRec24 + fTemp18) - (fRec15[1] + fRec19[1] + fRec31[1] + fRec35[1] + fRec16 + fRec20 + fTemp19);
		fRec10[0] = (fRec15[1] + fRec19[1] + fRec27[1] + fRec39[1] + fRec16 + fRec20 + fTemp18) - (fRec11[1] + fRec23[1] + fRec31[1] + fRec35[1] + fRec12 + fRec24 + fTemp19);
		double fTemp20 = 0.37 * (fRec4[0] + fRec5[0]);
		double fTemp21 = fSlow88 * fRec2[1];
		fRec2[0] = fTemp20 - (fTemp21 + fSlow8 * fRec2[2]);
		double fTemp22 = fSlow8 * fRec2[0];
		double fTemp23 = 0.5 * (fTemp22 + fRec2[2] + fTemp20 + fTemp21 + fSlow6 * ((fTemp22 + fTemp21 + fRec2[2]) - fTemp20));
		double fTemp24 = fSlow89 * fRec1[1];
		fRec1[0] = fTemp23 - (fTemp24 + fSlow4 * fRec1[2]);
		double fTemp25 = fSlow4 * fRec1[0];
		double fTemp26 = 1.0 - 0.5 * fTemp0;
		fRec43[0] = fSlow90 + 0.999 * fRec43[1];
		double fTemp27 = std::pow(10.0, 0.050000000000000003 * fRec43[0]);
		output0[i0] = FAUSTFLOAT((0.25 * fTemp0 * (fTemp25 + fRec1[2] + fTemp23 + fTemp24 + fSlow2 * ((fTemp25 + fTemp24 + fRec1[2]) - fTemp23)) + fTemp7 * fTemp26) * fTemp27);
		double fTemp28 = 0.37 * (fRec4[0] - fRec5[0]);
		double fTemp29 = fSlow88 * fRec45[1];
		fRec45[0] = fTemp28 - (fTemp29 + fSlow8 * fRec45[2]);
		double fTemp30 = fSlow8 * fRec45[0];
		double fTemp31 = 0.5 * (fTemp30 + fRec45[2] + fTemp28 + fTemp29 + fSlow6 * ((fTemp30 + fTemp29 + fRec45[2]) - fTemp28));
		double fTemp32 = fSlow89 * fRec44[1];
		fRec44[0] = fTemp31 - (fTemp32 + fSlow4 * fRec44[2]);
		double fTemp33 = fSlow4 * fRec44[0];
		output1[i0] = FAUSTFLOAT(fTemp27 * (0.25 * fTemp0 * (fTemp33 + fRec44[2] + fTemp31 + fTemp32 + fSlow2 * ((fTemp33 + fTemp32 + fRec44[2]) - fTemp31)) + fTemp1 * fTemp26));
		fRec0[1] = fRec0[0];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		IOTA0 = IOTA0 + 1;
		fRec11[1] = fRec11[0];
		fRec18[1] = fRec18[0];
		fRec17[1] = fRec17[0];
		fRec15[1] = fRec15[0];
		fRec22[1] = fRec22[0];
		fRec21[1] = fRec21[0];
		fRec19[1] = fRec19[0];
		fRec26[1] = fRec26[0];
		fRec25[1] = fRec25[0];
		fRec23[1] = fRec23[0];
		fRec30[1] = fRec30[0];
		fRec29[1] = fRec29[0];
		fRec27[1] = fRec27[0];
		fRec34[1] = fRec34[0];
		fRec33[1] = fRec33[0];
		fRec31[1] = fRec31[0];
		fRec38[1] = fRec38[0];
		fRec37[1] = fRec37[0];
		fRec35[1] = fRec35[0];
		fRec42[1] = fRec42[0];
		fRec41[1] = fRec41[0];
		fRec39[1] = fRec39[0];
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
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
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
		fVslider6_ = (float*)data; // , 6000.0, 1500.0, 23520.0, 1.0 
		break;
	case LF_X: 
		fVslider8_ = (float*)data; // , 200.0, 50.0, 1000.0, 1.0 
		break;
	case LOW_RT60: 
		fVslider7_ = (float*)data; // , 3.0, 1.0, 8.0, 0.10000000000000001 
		break;
	case MID_RT60: 
		fVslider5_ = (float*)data; // , 2.0, 1.0, 8.0, 0.10000000000000001 
		break;
	case EQ1_FREQ: 
		fVslider3_ = (float*)data; // , 315.0, 40.0, 2500.0, 1.0 
		break;
	case EQ1_LEVEL: 
		fVslider4_ = (float*)data; // , 0.0, -15.0, 15.0, 0.10000000000000001 
		break;
	case EQ2_FREQ: 
		fVslider1_ = (float*)data; // , 1500.0, 160.0, 10000.0, 1.0 
		break;
	case EQ2_LEVEL: 
		fVslider2_ = (float*)data; // , 0.0, -15.0, 15.0, 0.10000000000000001 
		break;
	case IN_DELAY: 
		fVslider9_ = (float*)data; // , 60.0, 20.0, 100.0, 1.0 
		break;
	case DRY_WET_MIX: 
		fVslider0_ = (float*)data; // , 0.0, -1.0, 1.0, 0.01 
		break;
	case LEVEL: 
		fVslider10_ = (float*)data; // , 0.0, -70.0, 40.0, 0.10000000000000001 
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
