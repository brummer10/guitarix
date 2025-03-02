// generated from file '../src/LV2/faust/mbe.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace mbe {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	double fConst2;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT	*fHslider2_;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT	*fHslider3_;
	double fVec0[2];
	double fRec11[2];
	double fRec10[3];
	double fVec1[2];
	double fRec9[2];
	double fRec8[3];
	double fVec2[2];
	double fRec7[2];
	double fRec6[3];
	double fVec3[2];
	double fRec5[2];
	double fRec4[3];
	int IOTA0;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT	*fHslider4_;
	double fConst3;
	double fConst4;
	double fRec12[2];
	double fRec13[2];
	double fRec14[2];
	double fRec15[2];
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT	*fHslider5_;
	double fRec16[2];
	double *fRec3;
	double fRec0[2];
	int iRec1[2];
	double fRec2[2];
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT	*fVbargraph0_;
	double fRec22[2];
	double fRec21[3];
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT	*fHslider6_;
	double fRec23[2];
	double fRec24[2];
	double fRec25[2];
	double fRec26[2];
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT	*fHslider7_;
	double fRec27[2];
	double *fRec20;
	double fRec17[2];
	int iRec18[2];
	double fRec19[2];
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT	*fVbargraph1_;
	double fRec34[2];
	double fRec33[3];
	double fRec32[3];
	FAUSTFLOAT fHslider8;
	FAUSTFLOAT	*fHslider8_;
	double fRec35[2];
	double fRec36[2];
	double fRec37[2];
	double fRec38[2];
	FAUSTFLOAT fHslider9;
	FAUSTFLOAT	*fHslider9_;
	double fRec39[2];
	double *fRec31;
	double fRec28[2];
	int iRec29[2];
	double fRec30[2];
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT	*fVbargraph2_;
	double fRec47[2];
	double fRec46[3];
	double fRec45[3];
	double fRec44[3];
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT	*fHslider10_;
	double fRec48[2];
	double fRec49[2];
	double fRec50[2];
	double fRec51[2];
	FAUSTFLOAT fHslider11;
	FAUSTFLOAT	*fHslider11_;
	double fRec52[2];
	double *fRec43;
	double fRec40[2];
	int iRec41[2];
	double fRec42[2];
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT	*fVbargraph3_;
	double fRec61[2];
	double fRec60[3];
	double fRec59[3];
	double fRec58[3];
	double fRec57[3];
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT	*fHslider12_;
	double fRec62[2];
	double fRec63[2];
	double fRec64[2];
	double fRec65[2];
	FAUSTFLOAT fHslider13;
	FAUSTFLOAT	*fHslider13_;
	double fRec66[2];
	double *fRec56;
	double fRec53[2];
	int iRec54[2];
	double fRec55[2];
	FAUSTFLOAT fVbargraph4;
	FAUSTFLOAT	*fVbargraph4_;

	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void connect(uint32_t port,void* data);
	void clear_state_f();
	int activate(bool start);
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static int activate_static(bool start, PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2(),
	  fRec3(0),
	  fRec20(0),
	  fRec31(0),
	  fRec43(0),
	  fRec56(0),
	  mem_allocated(false) {
	version = PLUGINLV2_VERSION;
	id = "mbe";
	name = N_("MultiBand Echo");
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = activate_static;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fVec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec11[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRec10[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fVec1[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec9[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec8[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fVec2[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec7[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec6[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fVec3[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec5[l10] = 0.0;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec4[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec12[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec13[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec14[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec15[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec16[l16] = 0.0;
	for (int l17 = 0; l17 < 524288; l17 = l17 + 1) fRec3[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec0[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) iRec1[l19] = 0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec2[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec22[l21] = 0.0;
	for (int l22 = 0; l22 < 3; l22 = l22 + 1) fRec21[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec23[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec24[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec25[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec26[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec27[l27] = 0.0;
	for (int l28 = 0; l28 < 524288; l28 = l28 + 1) fRec20[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec17[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) iRec18[l30] = 0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec19[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fRec34[l32] = 0.0;
	for (int l33 = 0; l33 < 3; l33 = l33 + 1) fRec33[l33] = 0.0;
	for (int l34 = 0; l34 < 3; l34 = l34 + 1) fRec32[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec35[l35] = 0.0;
	for (int l36 = 0; l36 < 2; l36 = l36 + 1) fRec36[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec37[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fRec38[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec39[l39] = 0.0;
	for (int l40 = 0; l40 < 524288; l40 = l40 + 1) fRec31[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec28[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) iRec29[l42] = 0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fRec30[l43] = 0.0;
	for (int l44 = 0; l44 < 2; l44 = l44 + 1) fRec47[l44] = 0.0;
	for (int l45 = 0; l45 < 3; l45 = l45 + 1) fRec46[l45] = 0.0;
	for (int l46 = 0; l46 < 3; l46 = l46 + 1) fRec45[l46] = 0.0;
	for (int l47 = 0; l47 < 3; l47 = l47 + 1) fRec44[l47] = 0.0;
	for (int l48 = 0; l48 < 2; l48 = l48 + 1) fRec48[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec49[l49] = 0.0;
	for (int l50 = 0; l50 < 2; l50 = l50 + 1) fRec50[l50] = 0.0;
	for (int l51 = 0; l51 < 2; l51 = l51 + 1) fRec51[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fRec52[l52] = 0.0;
	for (int l53 = 0; l53 < 524288; l53 = l53 + 1) fRec43[l53] = 0.0;
	for (int l54 = 0; l54 < 2; l54 = l54 + 1) fRec40[l54] = 0.0;
	for (int l55 = 0; l55 < 2; l55 = l55 + 1) iRec41[l55] = 0;
	for (int l56 = 0; l56 < 2; l56 = l56 + 1) fRec42[l56] = 0.0;
	for (int l57 = 0; l57 < 2; l57 = l57 + 1) fRec61[l57] = 0.0;
	for (int l58 = 0; l58 < 3; l58 = l58 + 1) fRec60[l58] = 0.0;
	for (int l59 = 0; l59 < 3; l59 = l59 + 1) fRec59[l59] = 0.0;
	for (int l60 = 0; l60 < 3; l60 = l60 + 1) fRec58[l60] = 0.0;
	for (int l61 = 0; l61 < 3; l61 = l61 + 1) fRec57[l61] = 0.0;
	for (int l62 = 0; l62 < 2; l62 = l62 + 1) fRec62[l62] = 0.0;
	for (int l63 = 0; l63 < 2; l63 = l63 + 1) fRec63[l63] = 0.0;
	for (int l64 = 0; l64 < 2; l64 = l64 + 1) fRec64[l64] = 0.0;
	for (int l65 = 0; l65 < 2; l65 = l65 + 1) fRec65[l65] = 0.0;
	for (int l66 = 0; l66 < 2; l66 = l66 + 1) fRec66[l66] = 0.0;
	for (int l67 = 0; l67 < 524288; l67 = l67 + 1) fRec56[l67] = 0.0;
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
	fConst3 = 6e+01 * fConst0;
	fConst4 = 1e+01 / fConst0;
	IOTA0 = 0;
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void Dsp::mem_alloc()
{
	if (!fRec3) fRec3 = new double[524288];
	if (!fRec20) fRec20 = new double[524288];
	if (!fRec31) fRec31 = new double[524288];
	if (!fRec43) fRec43 = new double[524288];
	if (!fRec56) fRec56 = new double[524288];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fRec3) { delete fRec3; fRec3 = 0; }
	if (fRec20) { delete fRec20; fRec20 = 0; }
	if (fRec31) { delete fRec31; fRec31 = 0; }
	if (fRec43) { delete fRec43; fRec43 = 0; }
	if (fRec56) { delete fRec56; fRec56 = 0; }
}

int Dsp::activate(bool start)
{
	if (start) {
		if (!mem_allocated) {
			mem_alloc();
			clear_state_f();
		}
	} else if (mem_allocated) {
		mem_free();
	}
	return 0;
}

int Dsp::activate_static(bool start, PluginLV2 *p)
{
	return static_cast<Dsp*>(p)->activate(start);
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
	double fSlow0 = std::tan(fConst2 * double(fHslider0));
	double fSlow1 = mydsp_faustpower2_f(fSlow0);
	double fSlow2 = 2.0 * (1.0 - 1.0 / fSlow1);
	double fSlow3 = 1.0 / fSlow0;
	double fSlow4 = (fSlow3 + -1.0000000000000004) / fSlow0 + 1.0;
	double fSlow5 = (fSlow3 + 1.0000000000000004) / fSlow0 + 1.0;
	double fSlow6 = 1.0 / fSlow5;
	double fSlow7 = std::tan(fConst2 * double(fHslider1));
	double fSlow8 = mydsp_faustpower2_f(fSlow7);
	double fSlow9 = 2.0 * (1.0 - 1.0 / fSlow8);
	double fSlow10 = 1.0 / fSlow7;
	double fSlow11 = (fSlow10 + -1.0000000000000004) / fSlow7 + 1.0;
	double fSlow12 = (fSlow10 + 1.0000000000000004) / fSlow7 + 1.0;
	double fSlow13 = 1.0 / fSlow12;
	double fSlow14 = std::tan(fConst2 * double(fHslider2));
	double fSlow15 = mydsp_faustpower2_f(fSlow14);
	double fSlow16 = 2.0 * (1.0 - 1.0 / fSlow15);
	double fSlow17 = 1.0 / fSlow14;
	double fSlow18 = (fSlow17 + -1.0000000000000004) / fSlow14 + 1.0;
	double fSlow19 = (fSlow17 + 1.0000000000000004) / fSlow14 + 1.0;
	double fSlow20 = 1.0 / fSlow19;
	double fSlow21 = std::tan(fConst2 * double(fHslider3));
	double fSlow22 = mydsp_faustpower2_f(fSlow21);
	double fSlow23 = 2.0 * (1.0 - 1.0 / fSlow22);
	double fSlow24 = 1.0 / fSlow21;
	double fSlow25 = (fSlow24 + -1.0000000000000004) / fSlow21 + 1.0;
	double fSlow26 = (fSlow24 + 1.0000000000000004) / fSlow21 + 1.0;
	double fSlow27 = 1.0 / fSlow26;
	double fSlow28 = 1.0 - fSlow24;
	double fSlow29 = 1.0 / (fSlow24 + 1.0);
	double fSlow30 = 1.0 - fSlow17;
	double fSlow31 = fSlow17 + 1.0;
	double fSlow32 = 1.0 / fSlow31;
	double fSlow33 = 1.0 - fSlow10;
	double fSlow34 = fSlow10 + 1.0;
	double fSlow35 = 1.0 / fSlow34;
	double fSlow36 = 1.0 - fSlow3;
	double fSlow37 = fSlow3 + 1.0;
	double fSlow38 = 1.0 / fSlow37;
	double fSlow39 = fConst3 / double(fHslider4);
	double fSlow40 = 1.000000000000001e-05 * double(fHslider5);
	double fSlow41 = 1.0 / (fSlow1 * fSlow5);
	double fSlow42 = fConst3 / double(fHslider6);
	double fSlow43 = 1.000000000000001e-05 * double(fHslider7);
	double fSlow44 = 1.0 - fSlow36 / fSlow0;
	double fSlow45 = 1.0 / (fSlow37 / fSlow0 + 1.0);
	double fSlow46 = 1.0 / (fSlow8 * fSlow12);
	double fSlow47 = fConst3 / double(fHslider8);
	double fSlow48 = 1.000000000000001e-05 * double(fHslider9);
	double fSlow49 = 1.0 - fSlow33 / fSlow7;
	double fSlow50 = 1.0 / (fSlow34 / fSlow7 + 1.0);
	double fSlow51 = 1.0 / (fSlow15 * fSlow19);
	double fSlow52 = fConst3 / double(fHslider10);
	double fSlow53 = 1.000000000000001e-05 * double(fHslider11);
	double fSlow54 = 1.0 - fSlow30 / fSlow14;
	double fSlow55 = 1.0 / (fSlow31 / fSlow14 + 1.0);
	double fSlow56 = 1.0 / (fSlow22 * fSlow26);
	double fSlow57 = fConst3 / double(fHslider12);
	double fSlow58 = 1.000000000000001e-05 * double(fHslider13);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		int iTemp0 = iRec1[1] < 4096;
		double fTemp1 = double(input0[i0]);
		fVec0[0] = fTemp1;
		fRec11[0] = -(fSlow29 * (fSlow28 * fRec11[1] - (fTemp1 + fVec0[1])));
		fRec10[0] = fRec11[0] - fSlow27 * (fSlow25 * fRec10[2] + fSlow23 * fRec10[1]);
		double fTemp2 = fSlow27 * (fRec10[2] + fRec10[0] + 2.0 * fRec10[1]);
		fVec1[0] = fTemp2;
		fRec9[0] = -(fSlow32 * (fSlow30 * fRec9[1] - (fTemp2 + fVec1[1])));
		fRec8[0] = fRec9[0] - fSlow20 * (fSlow18 * fRec8[2] + fSlow16 * fRec8[1]);
		double fTemp3 = fSlow20 * (fRec8[2] + fRec8[0] + 2.0 * fRec8[1]);
		fVec2[0] = fTemp3;
		fRec7[0] = -(fSlow35 * (fSlow33 * fRec7[1] - (fTemp3 + fVec2[1])));
		fRec6[0] = fRec7[0] - fSlow13 * (fSlow11 * fRec6[2] + fSlow9 * fRec6[1]);
		double fTemp4 = fSlow13 * (fRec6[2] + fRec6[0] + 2.0 * fRec6[1]);
		fVec3[0] = fTemp4;
		fRec5[0] = -(fSlow38 * (fSlow36 * fRec5[1] - (fTemp4 + fVec3[1])));
		fRec4[0] = fRec5[0] - fSlow6 * (fSlow4 * fRec4[2] + fSlow2 * fRec4[1]);
		double fTemp5 = ((fRec12[1] != 0.0) ? (((fRec13[1] > 0.0) & (fRec13[1] < 1.0)) ? fRec12[1] : 0.0) : (((fRec13[1] == 0.0) & (fSlow39 != fRec14[1])) ? fConst4 : (((fRec13[1] == 1.0) & (fSlow39 != fRec15[1])) ? -fConst4 : 0.0)));
		fRec12[0] = fTemp5;
		fRec13[0] = std::max<double>(0.0, std::min<double>(1.0, fRec13[1] + fTemp5));
		fRec14[0] = (((fRec13[1] >= 1.0) & (fRec15[1] != fSlow39)) ? fSlow39 : fRec14[1]);
		fRec15[0] = (((fRec13[1] <= 0.0) & (fRec14[1] != fSlow39)) ? fSlow39 : fRec15[1]);
		double fTemp6 = fRec3[(IOTA0 - (int(std::min<double>(262144.0, std::max<double>(0.0, fRec14[0]))) + 1)) & 524287];
		fRec16[0] = fSlow40 + 0.999 * fRec16[1];
		fRec3[IOTA0 & 524287] = fRec16[0] * (fTemp6 + fRec13[0] * (fRec3[(IOTA0 - (int(std::min<double>(262144.0, std::max<double>(0.0, fRec15[0]))) + 1)) & 524287] - fTemp6)) + fSlow6 * (fRec4[2] + fRec4[0] + 2.0 * fRec4[1]);
		double fTemp7 = fRec3[IOTA0 & 524287];
		double fTemp8 = std::max<double>(fConst1, std::fabs(fTemp7));
		fRec0[0] = ((iTemp0) ? std::max<double>(fRec0[1], fTemp8) : fTemp8);
		iRec1[0] = ((iTemp0) ? iRec1[1] + 1 : 1);
		fRec2[0] = ((iTemp0) ? fRec2[1] : fRec0[1]);
		fVbargraph0 = FAUSTFLOAT(fRec2[0]);
		int iTemp9 = iRec18[1] < 4096;
		fRec22[0] = -(fSlow38 * (fSlow36 * fRec22[1] - fSlow3 * (fTemp4 - fVec3[1])));
		fRec21[0] = fRec22[0] - fSlow6 * (fSlow4 * fRec21[2] + fSlow2 * fRec21[1]);
		double fTemp10 = ((fRec23[1] != 0.0) ? (((fRec24[1] > 0.0) & (fRec24[1] < 1.0)) ? fRec23[1] : 0.0) : (((fRec24[1] == 0.0) & (fSlow42 != fRec25[1])) ? fConst4 : (((fRec24[1] == 1.0) & (fSlow42 != fRec26[1])) ? -fConst4 : 0.0)));
		fRec23[0] = fTemp10;
		fRec24[0] = std::max<double>(0.0, std::min<double>(1.0, fRec24[1] + fTemp10));
		fRec25[0] = (((fRec24[1] >= 1.0) & (fRec26[1] != fSlow42)) ? fSlow42 : fRec25[1]);
		fRec26[0] = (((fRec24[1] <= 0.0) & (fRec25[1] != fSlow42)) ? fSlow42 : fRec26[1]);
		double fTemp11 = fRec20[(IOTA0 - (int(std::min<double>(262144.0, std::max<double>(0.0, fRec25[0]))) + 1)) & 524287];
		fRec27[0] = fSlow43 + 0.999 * fRec27[1];
		fRec20[IOTA0 & 524287] = fRec27[0] * (fTemp11 + fRec24[0] * (fRec20[(IOTA0 - (int(std::min<double>(262144.0, std::max<double>(0.0, fRec26[0]))) + 1)) & 524287] - fTemp11)) + fSlow41 * (fRec21[2] + (fRec21[0] - 2.0 * fRec21[1]));
		double fTemp12 = fRec20[IOTA0 & 524287];
		double fTemp13 = std::max<double>(fConst1, std::fabs(fTemp12));
		fRec17[0] = ((iTemp9) ? std::max<double>(fRec17[1], fTemp13) : fTemp13);
		iRec18[0] = ((iTemp9) ? iRec18[1] + 1 : 1);
		fRec19[0] = ((iTemp9) ? fRec19[1] : fRec17[1]);
		fVbargraph1 = FAUSTFLOAT(fRec19[0]);
		int iTemp14 = iRec29[1] < 4096;
		double fTemp15 = fSlow2 * fRec32[1];
		fRec34[0] = -(fSlow35 * (fSlow33 * fRec34[1] - fSlow10 * (fTemp3 - fVec2[1])));
		fRec33[0] = fRec34[0] - fSlow13 * (fSlow11 * fRec33[2] + fSlow9 * fRec33[1]);
		fRec32[0] = fSlow46 * (fRec33[2] + (fRec33[0] - 2.0 * fRec33[1])) - fSlow45 * (fSlow44 * fRec32[2] + fTemp15);
		double fTemp16 = ((fRec35[1] != 0.0) ? (((fRec36[1] > 0.0) & (fRec36[1] < 1.0)) ? fRec35[1] : 0.0) : (((fRec36[1] == 0.0) & (fSlow47 != fRec37[1])) ? fConst4 : (((fRec36[1] == 1.0) & (fSlow47 != fRec38[1])) ? -fConst4 : 0.0)));
		fRec35[0] = fTemp16;
		fRec36[0] = std::max<double>(0.0, std::min<double>(1.0, fRec36[1] + fTemp16));
		fRec37[0] = (((fRec36[1] >= 1.0) & (fRec38[1] != fSlow47)) ? fSlow47 : fRec37[1]);
		fRec38[0] = (((fRec36[1] <= 0.0) & (fRec37[1] != fSlow47)) ? fSlow47 : fRec38[1]);
		double fTemp17 = fRec31[(IOTA0 - (int(std::min<double>(262144.0, std::max<double>(0.0, fRec37[0]))) + 1)) & 524287];
		fRec39[0] = fSlow48 + 0.999 * fRec39[1];
		fRec31[IOTA0 & 524287] = fSlow45 * (fTemp15 + fSlow44 * fRec32[0]) + fRec39[0] * (fTemp17 + fRec36[0] * (fRec31[(IOTA0 - (int(std::min<double>(262144.0, std::max<double>(0.0, fRec38[0]))) + 1)) & 524287] - fTemp17)) + fRec32[2];
		double fTemp18 = fRec31[IOTA0 & 524287];
		double fTemp19 = std::max<double>(fConst1, std::fabs(fTemp18));
		fRec28[0] = ((iTemp14) ? std::max<double>(fRec28[1], fTemp19) : fTemp19);
		iRec29[0] = ((iTemp14) ? iRec29[1] + 1 : 1);
		fRec30[0] = ((iTemp14) ? fRec30[1] : fRec28[1]);
		fVbargraph2 = FAUSTFLOAT(fRec30[0]);
		int iTemp20 = iRec41[1] < 4096;
		double fTemp21 = fSlow2 * fRec44[1];
		double fTemp22 = fSlow9 * fRec45[1];
		fRec47[0] = -(fSlow32 * (fSlow30 * fRec47[1] - fSlow17 * (fTemp2 - fVec1[1])));
		fRec46[0] = fRec47[0] - fSlow20 * (fSlow18 * fRec46[2] + fSlow16 * fRec46[1]);
		fRec45[0] = fSlow51 * (fRec46[2] + (fRec46[0] - 2.0 * fRec46[1])) - fSlow50 * (fSlow49 * fRec45[2] + fTemp22);
		fRec44[0] = fRec45[2] + fSlow50 * (fTemp22 + fSlow49 * fRec45[0]) - fSlow45 * (fSlow44 * fRec44[2] + fTemp21);
		double fTemp23 = ((fRec48[1] != 0.0) ? (((fRec49[1] > 0.0) & (fRec49[1] < 1.0)) ? fRec48[1] : 0.0) : (((fRec49[1] == 0.0) & (fSlow52 != fRec50[1])) ? fConst4 : (((fRec49[1] == 1.0) & (fSlow52 != fRec51[1])) ? -fConst4 : 0.0)));
		fRec48[0] = fTemp23;
		fRec49[0] = std::max<double>(0.0, std::min<double>(1.0, fRec49[1] + fTemp23));
		fRec50[0] = (((fRec49[1] >= 1.0) & (fRec51[1] != fSlow52)) ? fSlow52 : fRec50[1]);
		fRec51[0] = (((fRec49[1] <= 0.0) & (fRec50[1] != fSlow52)) ? fSlow52 : fRec51[1]);
		double fTemp24 = fRec43[(IOTA0 - (int(std::min<double>(262144.0, std::max<double>(0.0, fRec50[0]))) + 1)) & 524287];
		fRec52[0] = fSlow53 + 0.999 * fRec52[1];
		fRec43[IOTA0 & 524287] = fSlow45 * (fTemp21 + fSlow44 * fRec44[0]) + fRec52[0] * (fTemp24 + fRec49[0] * (fRec43[(IOTA0 - (int(std::min<double>(262144.0, std::max<double>(0.0, fRec51[0]))) + 1)) & 524287] - fTemp24)) + fRec44[2];
		double fTemp25 = fRec43[IOTA0 & 524287];
		double fTemp26 = std::max<double>(fConst1, std::fabs(fTemp25));
		fRec40[0] = ((iTemp20) ? std::max<double>(fRec40[1], fTemp26) : fTemp26);
		iRec41[0] = ((iTemp20) ? iRec41[1] + 1 : 1);
		fRec42[0] = ((iTemp20) ? fRec42[1] : fRec40[1]);
		fVbargraph3 = FAUSTFLOAT(fRec42[0]);
		int iTemp27 = iRec54[1] < 4096;
		double fTemp28 = fSlow2 * fRec57[1];
		double fTemp29 = fSlow9 * fRec58[1];
		double fTemp30 = fSlow16 * fRec59[1];
		fRec61[0] = -(fSlow29 * (fSlow28 * fRec61[1] - fSlow24 * (fTemp1 - fVec0[1])));
		fRec60[0] = fRec61[0] - fSlow27 * (fSlow25 * fRec60[2] + fSlow23 * fRec60[1]);
		fRec59[0] = fSlow56 * (fRec60[2] + (fRec60[0] - 2.0 * fRec60[1])) - fSlow55 * (fSlow54 * fRec59[2] + fTemp30);
		fRec58[0] = fRec59[2] + fSlow55 * (fTemp30 + fSlow54 * fRec59[0]) - fSlow50 * (fSlow49 * fRec58[2] + fTemp29);
		fRec57[0] = fRec58[2] + fSlow50 * (fTemp29 + fSlow49 * fRec58[0]) - fSlow45 * (fSlow44 * fRec57[2] + fTemp28);
		double fTemp31 = ((fRec62[1] != 0.0) ? (((fRec63[1] > 0.0) & (fRec63[1] < 1.0)) ? fRec62[1] : 0.0) : (((fRec63[1] == 0.0) & (fSlow57 != fRec64[1])) ? fConst4 : (((fRec63[1] == 1.0) & (fSlow57 != fRec65[1])) ? -fConst4 : 0.0)));
		fRec62[0] = fTemp31;
		fRec63[0] = std::max<double>(0.0, std::min<double>(1.0, fRec63[1] + fTemp31));
		fRec64[0] = (((fRec63[1] >= 1.0) & (fRec65[1] != fSlow57)) ? fSlow57 : fRec64[1]);
		fRec65[0] = (((fRec63[1] <= 0.0) & (fRec64[1] != fSlow57)) ? fSlow57 : fRec65[1]);
		double fTemp32 = fRec56[(IOTA0 - (int(std::min<double>(262144.0, std::max<double>(0.0, fRec64[0]))) + 1)) & 524287];
		fRec66[0] = fSlow58 + 0.999 * fRec66[1];
		fRec56[IOTA0 & 524287] = fSlow45 * (fTemp28 + fSlow44 * fRec57[0]) + fRec66[0] * (fTemp32 + fRec63[0] * (fRec56[(IOTA0 - (int(std::min<double>(262144.0, std::max<double>(0.0, fRec65[0]))) + 1)) & 524287] - fTemp32)) + fRec57[2];
		double fTemp33 = fRec56[IOTA0 & 524287];
		double fTemp34 = std::max<double>(fConst1, std::fabs(fTemp33));
		fRec53[0] = ((iTemp27) ? std::max<double>(fRec53[1], fTemp34) : fTemp34);
		iRec54[0] = ((iTemp27) ? iRec54[1] + 1 : 1);
		fRec55[0] = ((iTemp27) ? fRec55[1] : fRec53[1]);
		fVbargraph4 = FAUSTFLOAT(fRec55[0]);
		output0[i0] = FAUSTFLOAT(fTemp33 + fTemp25 + fTemp18 + fTemp12 + fTemp7);
		fVec0[1] = fVec0[0];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fVec1[1] = fVec1[0];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fVec2[1] = fVec2[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fVec3[1] = fVec3[0];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		IOTA0 = IOTA0 + 1;
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fRec0[1] = fRec0[0];
		iRec1[1] = iRec1[0];
		fRec2[1] = fRec2[0];
		fRec22[1] = fRec22[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec17[1] = fRec17[0];
		iRec18[1] = iRec18[0];
		fRec19[1] = fRec19[0];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fRec35[1] = fRec35[0];
		fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec28[1] = fRec28[0];
		iRec29[1] = iRec29[0];
		fRec30[1] = fRec30[0];
		fRec47[1] = fRec47[0];
		fRec46[2] = fRec46[1];
		fRec46[1] = fRec46[0];
		fRec45[2] = fRec45[1];
		fRec45[1] = fRec45[0];
		fRec44[2] = fRec44[1];
		fRec44[1] = fRec44[0];
		fRec48[1] = fRec48[0];
		fRec49[1] = fRec49[0];
		fRec50[1] = fRec50[0];
		fRec51[1] = fRec51[0];
		fRec52[1] = fRec52[0];
		fRec40[1] = fRec40[0];
		iRec41[1] = iRec41[0];
		fRec42[1] = fRec42[0];
		fRec61[1] = fRec61[0];
		fRec60[2] = fRec60[1];
		fRec60[1] = fRec60[0];
		fRec59[2] = fRec59[1];
		fRec59[1] = fRec59[0];
		fRec58[2] = fRec58[1];
		fRec58[1] = fRec58[0];
		fRec57[2] = fRec57[1];
		fRec57[1] = fRec57[0];
		fRec62[1] = fRec62[0];
		fRec63[1] = fRec63[0];
		fRec64[1] = fRec64[0];
		fRec65[1] = fRec65[0];
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
	case PERCENT1: 
		fHslider5_ = (float*)data; // , 1e+01, 0.0, 1e+02, 0.1 
		break;
	case PERCENT2: 
		fHslider7_ = (float*)data; // , 3e+01, 0.0, 1e+02, 0.1 
		break;
	case PERCENT3: 
		fHslider9_ = (float*)data; // , 45.0, 0.0, 1e+02, 0.1 
		break;
	case PERCENT4: 
		fHslider11_ = (float*)data; // , 2e+01, 0.0, 1e+02, 0.1 
		break;
	case PERCENT5: 
		fHslider13_ = (float*)data; // , 0.0, 0.0, 1e+02, 0.1 
		break;
	case TIME1: 
		fHslider4_ = (float*)data; // , 3e+01, 24.0, 3.6e+02, 1.0 
		break;
	case TIME2: 
		fHslider6_ = (float*)data; // , 6e+01, 24.0, 3.6e+02, 1.0 
		break;
	case TIME3: 
		fHslider8_ = (float*)data; // , 1.2e+02, 24.0, 3.6e+02, 1.0 
		break;
	case TIME4: 
		fHslider10_ = (float*)data; // , 1.5e+02, 24.0, 3.6e+02, 1.0 
		break;
	case TIME5: 
		fHslider12_ = (float*)data; // , 2.4e+02, 24.0, 3.6e+02, 1.0 
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
   CROSSOVER_B1_B2, 
   CROSSOVER_B2_B3, 
   CROSSOVER_B3_B4, 
   CROSSOVER_B4_B5, 
   PERCENT1, 
   PERCENT2, 
   PERCENT3, 
   PERCENT4, 
   PERCENT5, 
   TIME1, 
   TIME2, 
   TIME3, 
   TIME4, 
   TIME5, 
   V1, 
   V2, 
   V3, 
   V4, 
   V5, 
} PortIndex;
*/

} // end namespace mbe
