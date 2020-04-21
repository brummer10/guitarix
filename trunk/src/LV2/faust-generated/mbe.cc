// generated from file '../src/LV2/faust/mbe.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace mbe {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	double fVec0[2];
	double fRec8[2];
	double fRec7[3];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT	*fHslider2_;
	double fRec6[3];
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT	*fHslider3_;
	double fRec5[3];
	double fRec4[3];
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT	*fHslider4_;
	double fRec9[2];
	double fConst3;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT	*fHslider5_;
	double fConst4;
	double fConst5;
	double fRec10[2];
	double fRec11[2];
	double fRec12[2];
	double fRec13[2];
	int IOTA;
	double *fRec3;
	double fRec0[2];
	int iRec1[2];
	double fRec2[2];
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT	*fVbargraph0_;
	double fRec23[2];
	double fRec22[3];
	double fVec1[2];
	double fRec21[2];
	double fRec20[3];
	double fRec19[3];
	double fRec18[3];
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT	*fHslider6_;
	double fRec24[2];
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT	*fHslider7_;
	double fRec25[2];
	double fRec26[2];
	double fRec27[2];
	double fRec28[2];
	double *fRec17;
	double fRec14[2];
	int iRec15[2];
	double fRec16[2];
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT	*fVbargraph1_;
	double fRec37[2];
	double fRec36[3];
	double fVec2[2];
	double fRec35[2];
	double fRec34[3];
	double fRec33[3];
	FAUSTFLOAT fHslider8;
	FAUSTFLOAT	*fHslider8_;
	double fRec38[2];
	FAUSTFLOAT fHslider9;
	FAUSTFLOAT	*fHslider9_;
	double fRec39[2];
	double fRec40[2];
	double fRec41[2];
	double fRec42[2];
	double *fRec32;
	double fRec29[2];
	int iRec30[2];
	double fRec31[2];
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT	*fVbargraph2_;
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT	*fHslider10_;
	double fRec47[2];
	FAUSTFLOAT fHslider11;
	FAUSTFLOAT	*fHslider11_;
	double fRec48[2];
	double fRec49[2];
	double fRec50[2];
	double fRec51[2];
	double fRec55[2];
	double fRec54[3];
	double fVec3[2];
	double fRec53[2];
	double fRec52[3];
	double *fRec46;
	double fRec43[2];
	int iRec44[2];
	double fRec45[2];
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT	*fVbargraph3_;
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT	*fHslider12_;
	double fRec60[2];
	FAUSTFLOAT fHslider13;
	FAUSTFLOAT	*fHslider13_;
	double fRec61[2];
	double fRec62[2];
	double fRec63[2];
	double fRec64[2];
	double fRec66[2];
	double fRec65[3];
	double *fRec59;
	double fRec56[2];
	int iRec57[2];
	double fRec58[2];
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
	  fRec17(0),
	  fRec32(0),
	  fRec46(0),
	  fRec59(0),
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fVec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec8[l1] = 0.0;
	for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) fRec7[l2] = 0.0;
	for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) fRec6[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec5[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec4[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec9[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec10[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec11[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec12[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec13[l10] = 0.0;
	for (int l11 = 0; (l11 < 524288); l11 = (l11 + 1)) fRec3[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec0[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) iRec1[l13] = 0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec2[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec23[l15] = 0.0;
	for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) fRec22[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fVec1[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec21[l18] = 0.0;
	for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) fRec20[l19] = 0.0;
	for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) fRec19[l20] = 0.0;
	for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) fRec18[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fRec24[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fRec25[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec26[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fRec27[l25] = 0.0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fRec28[l26] = 0.0;
	for (int l27 = 0; (l27 < 524288); l27 = (l27 + 1)) fRec17[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec14[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) iRec15[l29] = 0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec16[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fRec37[l31] = 0.0;
	for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) fRec36[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fVec2[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec35[l34] = 0.0;
	for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) fRec34[l35] = 0.0;
	for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) fRec33[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fRec38[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fRec39[l38] = 0.0;
	for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) fRec40[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fRec41[l40] = 0.0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) fRec42[l41] = 0.0;
	for (int l42 = 0; (l42 < 524288); l42 = (l42 + 1)) fRec32[l42] = 0.0;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fRec29[l43] = 0.0;
	for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) iRec30[l44] = 0;
	for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) fRec31[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec47[l46] = 0.0;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) fRec48[l47] = 0.0;
	for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) fRec49[l48] = 0.0;
	for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) fRec50[l49] = 0.0;
	for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) fRec51[l50] = 0.0;
	for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) fRec55[l51] = 0.0;
	for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) fRec54[l52] = 0.0;
	for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) fVec3[l53] = 0.0;
	for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) fRec53[l54] = 0.0;
	for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) fRec52[l55] = 0.0;
	for (int l56 = 0; (l56 < 524288); l56 = (l56 + 1)) fRec46[l56] = 0.0;
	for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) fRec43[l57] = 0.0;
	for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) iRec44[l58] = 0;
	for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) fRec45[l59] = 0.0;
	for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) fRec60[l60] = 0.0;
	for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) fRec61[l61] = 0.0;
	for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) fRec62[l62] = 0.0;
	for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) fRec63[l63] = 0.0;
	for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) fRec64[l64] = 0.0;
	for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) fRec66[l65] = 0.0;
	for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) fRec65[l66] = 0.0;
	for (int l67 = 0; (l67 < 524288); l67 = (l67 + 1)) fRec59[l67] = 0.0;
	for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) fRec56[l68] = 0.0;
	for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) iRec57[l69] = 0;
	for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) fRec58[l70] = 0.0;
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
	fConst3 = (60.0 * fConst0);
	fConst4 = (10.0 / fConst0);
	fConst5 = (0.0 - fConst4);
	IOTA = 0;
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void Dsp::mem_alloc()
{
	if (!fRec3) fRec3 = new double[524288];
	if (!fRec17) fRec17 = new double[524288];
	if (!fRec32) fRec32 = new double[524288];
	if (!fRec46) fRec46 = new double[524288];
	if (!fRec59) fRec59 = new double[524288];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fRec3) { delete fRec3; fRec3 = 0; }
	if (fRec17) { delete fRec17; fRec17 = 0; }
	if (fRec32) { delete fRec32; fRec32 = 0; }
	if (fRec46) { delete fRec46; fRec46 = 0; }
	if (fRec59) { delete fRec59; fRec59 = 0; }
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
	double fSlow0 = std::tan((fConst2 * double(fHslider0)));
	double fSlow1 = (1.0 / fSlow0);
	double fSlow2 = (fSlow1 + 1.0);
	double fSlow3 = (1.0 / ((fSlow2 / fSlow0) + 1.0));
	double fSlow4 = mydsp_faustpower2_f(fSlow0);
	double fSlow5 = (1.0 / fSlow4);
	double fSlow6 = (2.0 * (1.0 - fSlow5));
	double fSlow7 = std::tan((fConst2 * double(fHslider1)));
	double fSlow8 = (1.0 / fSlow7);
	double fSlow9 = (((fSlow8 + 1.0000000000000004) / fSlow7) + 1.0);
	double fSlow10 = (1.0 / fSlow9);
	double fSlow11 = mydsp_faustpower2_f(fSlow7);
	double fSlow12 = (1.0 / fSlow11);
	double fSlow13 = (fSlow8 + 1.0);
	double fSlow14 = (0.0 - (1.0 / (fSlow7 * fSlow13)));
	double fSlow15 = (1.0 / fSlow13);
	double fSlow16 = (1.0 - fSlow8);
	double fSlow17 = (((fSlow8 + -1.0000000000000004) / fSlow7) + 1.0);
	double fSlow18 = (2.0 * (1.0 - fSlow12));
	double fSlow19 = (0.0 - (2.0 / fSlow11));
	double fSlow20 = std::tan((fConst2 * double(fHslider2)));
	double fSlow21 = (1.0 / fSlow20);
	double fSlow22 = (fSlow21 + 1.0);
	double fSlow23 = (1.0 / ((fSlow22 / fSlow20) + 1.0));
	double fSlow24 = (1.0 - fSlow21);
	double fSlow25 = (1.0 - (fSlow24 / fSlow20));
	double fSlow26 = mydsp_faustpower2_f(fSlow20);
	double fSlow27 = (1.0 / fSlow26);
	double fSlow28 = (2.0 * (1.0 - fSlow27));
	double fSlow29 = std::tan((fConst2 * double(fHslider3)));
	double fSlow30 = (1.0 / fSlow29);
	double fSlow31 = (fSlow30 + 1.0);
	double fSlow32 = (1.0 / ((fSlow31 / fSlow29) + 1.0));
	double fSlow33 = (1.0 - fSlow30);
	double fSlow34 = (1.0 - (fSlow33 / fSlow29));
	double fSlow35 = mydsp_faustpower2_f(fSlow29);
	double fSlow36 = (1.0 / fSlow35);
	double fSlow37 = (2.0 * (1.0 - fSlow36));
	double fSlow38 = (1.0 - fSlow1);
	double fSlow39 = (1.0 - (fSlow38 / fSlow0));
	double fSlow40 = (1.0000000000000009e-05 * double(fHslider4));
	double fSlow41 = (fConst3 / double(fHslider5));
	double fSlow42 = (((fSlow21 + 1.0000000000000004) / fSlow20) + 1.0);
	double fSlow43 = (1.0 / fSlow42);
	double fSlow44 = (0.0 - (1.0 / (fSlow20 * fSlow22)));
	double fSlow45 = (1.0 / fSlow22);
	double fSlow46 = (1.0 / (fSlow20 * fSlow9));
	double fSlow47 = (((fSlow21 + -1.0000000000000004) / fSlow20) + 1.0);
	double fSlow48 = (0.0 - (2.0 / fSlow26));
	double fSlow49 = (1.0000000000000009e-05 * double(fHslider6));
	double fSlow50 = (fConst3 / double(fHslider7));
	double fSlow51 = (((fSlow30 + 1.0000000000000004) / fSlow29) + 1.0);
	double fSlow52 = (1.0 / fSlow51);
	double fSlow53 = (0.0 - (1.0 / (fSlow29 * fSlow31)));
	double fSlow54 = (1.0 / fSlow31);
	double fSlow55 = (1.0 / (fSlow29 * fSlow42));
	double fSlow56 = (((fSlow30 + -1.0000000000000004) / fSlow29) + 1.0);
	double fSlow57 = (0.0 - (2.0 / fSlow35));
	double fSlow58 = (1.0000000000000009e-05 * double(fHslider8));
	double fSlow59 = (fConst3 / double(fHslider9));
	double fSlow60 = (1.0000000000000009e-05 * double(fHslider10));
	double fSlow61 = (fConst3 / double(fHslider11));
	double fSlow62 = (1.0 / (((fSlow1 + 1.0000000000000004) / fSlow0) + 1.0));
	double fSlow63 = (0.0 - (1.0 / (fSlow0 * fSlow2)));
	double fSlow64 = (1.0 / fSlow2);
	double fSlow65 = (1.0 / (fSlow0 * fSlow51));
	double fSlow66 = (((fSlow1 + -1.0000000000000004) / fSlow0) + 1.0);
	double fSlow67 = (0.0 - (2.0 / fSlow4));
	double fSlow68 = (1.0000000000000009e-05 * double(fHslider12));
	double fSlow69 = (fConst3 / double(fHslider13));
	for (int i = 0; (i < count); i = (i + 1)) {
		int iTemp0 = (iRec1[1] < 4096);
		double fTemp1 = double(input0[i]);
		fVec0[0] = fTemp1;
		fRec8[0] = ((fSlow14 * fVec0[1]) - (fSlow15 * ((fSlow16 * fRec8[1]) - (fSlow8 * fTemp1))));
		fRec7[0] = (fRec8[0] - (fSlow10 * ((fSlow17 * fRec7[2]) + (fSlow18 * fRec7[1]))));
		double fTemp2 = (fSlow28 * fRec6[1]);
		fRec6[0] = ((fSlow10 * (((fSlow12 * fRec7[0]) + (fSlow19 * fRec7[1])) + (fSlow12 * fRec7[2]))) - (fSlow23 * ((fSlow25 * fRec6[2]) + fTemp2)));
		double fTemp3 = (fSlow37 * fRec5[1]);
		fRec5[0] = ((fRec6[2] + (fSlow23 * (fTemp2 + (fSlow25 * fRec6[0])))) - (fSlow32 * ((fSlow34 * fRec5[2]) + fTemp3)));
		double fTemp4 = (fSlow6 * fRec4[1]);
		fRec4[0] = ((fRec5[2] + (fSlow32 * (fTemp3 + (fSlow34 * fRec5[0])))) - (fSlow3 * ((fSlow39 * fRec4[2]) + fTemp4)));
		fRec9[0] = (fSlow40 + (0.999 * fRec9[1]));
		double fTemp5 = ((fRec10[1] != 0.0) ? (((fRec11[1] > 0.0) & (fRec11[1] < 1.0)) ? fRec10[1] : 0.0) : (((fRec11[1] == 0.0) & (fSlow41 != fRec12[1])) ? fConst4 : (((fRec11[1] == 1.0) & (fSlow41 != fRec13[1])) ? fConst5 : 0.0)));
		fRec10[0] = fTemp5;
		fRec11[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec11[1] + fTemp5)));
		fRec12[0] = (((fRec11[1] >= 1.0) & (fRec13[1] != fSlow41)) ? fSlow41 : fRec12[1]);
		fRec13[0] = (((fRec11[1] <= 0.0) & (fRec12[1] != fSlow41)) ? fSlow41 : fRec13[1]);
		fRec3[(IOTA & 524287)] = ((fSlow3 * (fTemp4 + (fSlow39 * fRec4[0]))) + ((fRec9[0] * (((1.0 - fRec11[0]) * fRec3[((IOTA - (int(std::min<double>(262144.0, std::max<double>(0.0, fRec12[0]))) + 1)) & 524287)]) + (fRec11[0] * fRec3[((IOTA - (int(std::min<double>(262144.0, std::max<double>(0.0, fRec13[0]))) + 1)) & 524287)]))) + fRec4[2]));
		double fTemp6 = fRec3[((IOTA - 0) & 524287)];
		double fTemp7 = std::max<double>(fConst1, std::fabs(fTemp6));
		fRec0[0] = (iTemp0 ? std::max<double>(fRec0[1], fTemp7) : fTemp7);
		iRec1[0] = (iTemp0 ? (iRec1[1] + 1) : 1);
		fRec2[0] = (iTemp0 ? fRec2[1] : fRec0[1]);
		fVbargraph0 = FAUSTFLOAT(fRec2[0]);
		int iTemp8 = (iRec15[1] < 4096);
		fRec23[0] = (0.0 - (fSlow15 * ((fSlow16 * fRec23[1]) - (fTemp1 + fVec0[1]))));
		fRec22[0] = (fRec23[0] - (fSlow10 * ((fSlow17 * fRec22[2]) + (fSlow18 * fRec22[1]))));
		double fTemp9 = (fRec22[2] + (fRec22[0] + (2.0 * fRec22[1])));
		double fTemp10 = (fSlow10 * fTemp9);
		fVec1[0] = fTemp10;
		fRec21[0] = ((fSlow44 * fVec1[1]) - (fSlow45 * ((fSlow24 * fRec21[1]) - (fSlow46 * fTemp9))));
		fRec20[0] = (fRec21[0] - (fSlow43 * ((fSlow47 * fRec20[2]) + (fSlow28 * fRec20[1]))));
		double fTemp11 = (fSlow37 * fRec19[1]);
		fRec19[0] = ((fSlow43 * (((fSlow27 * fRec20[0]) + (fSlow48 * fRec20[1])) + (fSlow27 * fRec20[2]))) - (fSlow32 * ((fSlow34 * fRec19[2]) + fTemp11)));
		double fTemp12 = (fSlow6 * fRec18[1]);
		fRec18[0] = ((fRec19[2] + (fSlow32 * (fTemp11 + (fSlow34 * fRec19[0])))) - (fSlow3 * ((fSlow39 * fRec18[2]) + fTemp12)));
		fRec24[0] = (fSlow49 + (0.999 * fRec24[1]));
		double fTemp13 = ((fRec25[1] != 0.0) ? (((fRec26[1] > 0.0) & (fRec26[1] < 1.0)) ? fRec25[1] : 0.0) : (((fRec26[1] == 0.0) & (fSlow50 != fRec27[1])) ? fConst4 : (((fRec26[1] == 1.0) & (fSlow50 != fRec28[1])) ? fConst5 : 0.0)));
		fRec25[0] = fTemp13;
		fRec26[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec26[1] + fTemp13)));
		fRec27[0] = (((fRec26[1] >= 1.0) & (fRec28[1] != fSlow50)) ? fSlow50 : fRec27[1]);
		fRec28[0] = (((fRec26[1] <= 0.0) & (fRec27[1] != fSlow50)) ? fSlow50 : fRec28[1]);
		fRec17[(IOTA & 524287)] = ((fSlow3 * (fTemp12 + (fSlow39 * fRec18[0]))) + ((fRec24[0] * (((1.0 - fRec26[0]) * fRec17[((IOTA - (int(std::min<double>(262144.0, std::max<double>(0.0, fRec27[0]))) + 1)) & 524287)]) + (fRec26[0] * fRec17[((IOTA - (int(std::min<double>(262144.0, std::max<double>(0.0, fRec28[0]))) + 1)) & 524287)]))) + fRec18[2]));
		double fTemp14 = fRec17[((IOTA - 0) & 524287)];
		double fTemp15 = std::max<double>(fConst1, std::fabs(fTemp14));
		fRec14[0] = (iTemp8 ? std::max<double>(fRec14[1], fTemp15) : fTemp15);
		iRec15[0] = (iTemp8 ? (iRec15[1] + 1) : 1);
		fRec16[0] = (iTemp8 ? fRec16[1] : fRec14[1]);
		fVbargraph1 = FAUSTFLOAT(fRec16[0]);
		int iTemp16 = (iRec30[1] < 4096);
		fRec37[0] = (0.0 - (fSlow45 * ((fSlow24 * fRec37[1]) - (fTemp10 + fVec1[1]))));
		fRec36[0] = (fRec37[0] - (fSlow43 * ((fSlow47 * fRec36[2]) + (fSlow28 * fRec36[1]))));
		double fTemp17 = (fRec36[2] + (fRec36[0] + (2.0 * fRec36[1])));
		double fTemp18 = (fSlow43 * fTemp17);
		fVec2[0] = fTemp18;
		fRec35[0] = ((fSlow53 * fVec2[1]) - (fSlow54 * ((fSlow33 * fRec35[1]) - (fSlow55 * fTemp17))));
		fRec34[0] = (fRec35[0] - (fSlow52 * ((fSlow56 * fRec34[2]) + (fSlow37 * fRec34[1]))));
		double fTemp19 = (fSlow6 * fRec33[1]);
		fRec33[0] = ((fSlow52 * (((fSlow36 * fRec34[0]) + (fSlow57 * fRec34[1])) + (fSlow36 * fRec34[2]))) - (fSlow3 * ((fSlow39 * fRec33[2]) + fTemp19)));
		fRec38[0] = (fSlow58 + (0.999 * fRec38[1]));
		double fTemp20 = ((fRec39[1] != 0.0) ? (((fRec40[1] > 0.0) & (fRec40[1] < 1.0)) ? fRec39[1] : 0.0) : (((fRec40[1] == 0.0) & (fSlow59 != fRec41[1])) ? fConst4 : (((fRec40[1] == 1.0) & (fSlow59 != fRec42[1])) ? fConst5 : 0.0)));
		fRec39[0] = fTemp20;
		fRec40[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec40[1] + fTemp20)));
		fRec41[0] = (((fRec40[1] >= 1.0) & (fRec42[1] != fSlow59)) ? fSlow59 : fRec41[1]);
		fRec42[0] = (((fRec40[1] <= 0.0) & (fRec41[1] != fSlow59)) ? fSlow59 : fRec42[1]);
		fRec32[(IOTA & 524287)] = ((fSlow3 * (fTemp19 + (fSlow39 * fRec33[0]))) + ((fRec38[0] * (((1.0 - fRec40[0]) * fRec32[((IOTA - (int(std::min<double>(262144.0, std::max<double>(0.0, fRec41[0]))) + 1)) & 524287)]) + (fRec40[0] * fRec32[((IOTA - (int(std::min<double>(262144.0, std::max<double>(0.0, fRec42[0]))) + 1)) & 524287)]))) + fRec33[2]));
		double fTemp21 = fRec32[((IOTA - 0) & 524287)];
		double fTemp22 = std::max<double>(fConst1, std::fabs(fTemp21));
		fRec29[0] = (iTemp16 ? std::max<double>(fRec29[1], fTemp22) : fTemp22);
		iRec30[0] = (iTemp16 ? (iRec30[1] + 1) : 1);
		fRec31[0] = (iTemp16 ? fRec31[1] : fRec29[1]);
		fVbargraph2 = FAUSTFLOAT(fRec31[0]);
		int iTemp23 = (iRec44[1] < 4096);
		fRec47[0] = (fSlow60 + (0.999 * fRec47[1]));
		double fTemp24 = ((fRec48[1] != 0.0) ? (((fRec49[1] > 0.0) & (fRec49[1] < 1.0)) ? fRec48[1] : 0.0) : (((fRec49[1] == 0.0) & (fSlow61 != fRec50[1])) ? fConst4 : (((fRec49[1] == 1.0) & (fSlow61 != fRec51[1])) ? fConst5 : 0.0)));
		fRec48[0] = fTemp24;
		fRec49[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec49[1] + fTemp24)));
		fRec50[0] = (((fRec49[1] >= 1.0) & (fRec51[1] != fSlow61)) ? fSlow61 : fRec50[1]);
		fRec51[0] = (((fRec49[1] <= 0.0) & (fRec50[1] != fSlow61)) ? fSlow61 : fRec51[1]);
		fRec55[0] = (0.0 - (fSlow54 * ((fSlow33 * fRec55[1]) - (fTemp18 + fVec2[1]))));
		fRec54[0] = (fRec55[0] - (fSlow52 * ((fSlow56 * fRec54[2]) + (fSlow37 * fRec54[1]))));
		double fTemp25 = (fRec54[2] + (fRec54[0] + (2.0 * fRec54[1])));
		double fTemp26 = (fSlow52 * fTemp25);
		fVec3[0] = fTemp26;
		fRec53[0] = ((fSlow63 * fVec3[1]) - (fSlow64 * ((fSlow38 * fRec53[1]) - (fSlow65 * fTemp25))));
		fRec52[0] = (fRec53[0] - (fSlow62 * ((fSlow66 * fRec52[2]) + (fSlow6 * fRec52[1]))));
		fRec46[(IOTA & 524287)] = ((fRec47[0] * (((1.0 - fRec49[0]) * fRec46[((IOTA - (int(std::min<double>(262144.0, std::max<double>(0.0, fRec50[0]))) + 1)) & 524287)]) + (fRec49[0] * fRec46[((IOTA - (int(std::min<double>(262144.0, std::max<double>(0.0, fRec51[0]))) + 1)) & 524287)]))) + (fSlow62 * (((fSlow5 * fRec52[0]) + (fSlow67 * fRec52[1])) + (fSlow5 * fRec52[2]))));
		double fTemp27 = fRec46[((IOTA - 0) & 524287)];
		double fTemp28 = std::max<double>(fConst1, std::fabs(fTemp27));
		fRec43[0] = (iTemp23 ? std::max<double>(fRec43[1], fTemp28) : fTemp28);
		iRec44[0] = (iTemp23 ? (iRec44[1] + 1) : 1);
		fRec45[0] = (iTemp23 ? fRec45[1] : fRec43[1]);
		fVbargraph3 = FAUSTFLOAT(fRec45[0]);
		int iTemp29 = (iRec57[1] < 4096);
		fRec60[0] = (fSlow68 + (0.999 * fRec60[1]));
		double fTemp30 = ((fRec61[1] != 0.0) ? (((fRec62[1] > 0.0) & (fRec62[1] < 1.0)) ? fRec61[1] : 0.0) : (((fRec62[1] == 0.0) & (fSlow69 != fRec63[1])) ? fConst4 : (((fRec62[1] == 1.0) & (fSlow69 != fRec64[1])) ? fConst5 : 0.0)));
		fRec61[0] = fTemp30;
		fRec62[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec62[1] + fTemp30)));
		fRec63[0] = (((fRec62[1] >= 1.0) & (fRec64[1] != fSlow69)) ? fSlow69 : fRec63[1]);
		fRec64[0] = (((fRec62[1] <= 0.0) & (fRec63[1] != fSlow69)) ? fSlow69 : fRec64[1]);
		fRec66[0] = (0.0 - (fSlow64 * ((fSlow38 * fRec66[1]) - (fTemp26 + fVec3[1]))));
		fRec65[0] = (fRec66[0] - (fSlow62 * ((fSlow66 * fRec65[2]) + (fSlow6 * fRec65[1]))));
		fRec59[(IOTA & 524287)] = ((fRec60[0] * (((1.0 - fRec62[0]) * fRec59[((IOTA - (int(std::min<double>(262144.0, std::max<double>(0.0, fRec63[0]))) + 1)) & 524287)]) + (fRec62[0] * fRec59[((IOTA - (int(std::min<double>(262144.0, std::max<double>(0.0, fRec64[0]))) + 1)) & 524287)]))) + (fSlow62 * (fRec65[2] + (fRec65[0] + (2.0 * fRec65[1])))));
		double fTemp31 = fRec59[((IOTA - 0) & 524287)];
		double fTemp32 = std::max<double>(fConst1, std::fabs(fTemp31));
		fRec56[0] = (iTemp29 ? std::max<double>(fRec56[1], fTemp32) : fTemp32);
		iRec57[0] = (iTemp29 ? (iRec57[1] + 1) : 1);
		fRec58[0] = (iTemp29 ? fRec58[1] : fRec56[1]);
		fVbargraph4 = FAUSTFLOAT(fRec58[0]);
		output0[i] = FAUSTFLOAT(((((fTemp6 + fTemp14) + fTemp21) + fTemp27) + fTemp31));
		fVec0[1] = fVec0[0];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		IOTA = (IOTA + 1);
		fRec0[1] = fRec0[0];
		iRec1[1] = iRec1[0];
		fRec2[1] = fRec2[0];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fVec1[1] = fVec1[0];
		fRec21[1] = fRec21[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fRec18[2] = fRec18[1];
		fRec18[1] = fRec18[0];
		fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec14[1] = fRec14[0];
		iRec15[1] = iRec15[0];
		fRec16[1] = fRec16[0];
		fRec37[1] = fRec37[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		fVec2[1] = fVec2[0];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec40[1] = fRec40[0];
		fRec41[1] = fRec41[0];
		fRec42[1] = fRec42[0];
		fRec29[1] = fRec29[0];
		iRec30[1] = iRec30[0];
		fRec31[1] = fRec31[0];
		fRec47[1] = fRec47[0];
		fRec48[1] = fRec48[0];
		fRec49[1] = fRec49[0];
		fRec50[1] = fRec50[0];
		fRec51[1] = fRec51[0];
		fRec55[1] = fRec55[0];
		fRec54[2] = fRec54[1];
		fRec54[1] = fRec54[0];
		fVec3[1] = fVec3[0];
		fRec53[1] = fRec53[0];
		fRec52[2] = fRec52[1];
		fRec52[1] = fRec52[0];
		fRec43[1] = fRec43[0];
		iRec44[1] = iRec44[0];
		fRec45[1] = fRec45[0];
		fRec60[1] = fRec60[0];
		fRec61[1] = fRec61[0];
		fRec62[1] = fRec62[0];
		fRec63[1] = fRec63[0];
		fRec64[1] = fRec64[0];
		fRec66[1] = fRec66[0];
		fRec65[2] = fRec65[1];
		fRec65[1] = fRec65[0];
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
		fHslider0_ = (float*)data; // , 80.0, 20.0, 20000.0, 1.0800000000000001 
		break;
	case CROSSOVER_B2_B3: 
		fHslider3_ = (float*)data; // , 210.0, 20.0, 20000.0, 1.0800000000000001 
		break;
	case CROSSOVER_B3_B4: 
		fHslider2_ = (float*)data; // , 1700.0, 20.0, 20000.0, 1.0800000000000001 
		break;
	case CROSSOVER_B4_B5: 
		fHslider1_ = (float*)data; // , 5000.0, 20.0, 20000.0, 1.0800000000000001 
		break;
	case PERCENT1: 
		fHslider12_ = (float*)data; // , 10.0, 0.0, 100.0, 0.10000000000000001 
		break;
	case PERCENT2: 
		fHslider10_ = (float*)data; // , 30.0, 0.0, 100.0, 0.10000000000000001 
		break;
	case PERCENT3: 
		fHslider8_ = (float*)data; // , 45.0, 0.0, 100.0, 0.10000000000000001 
		break;
	case PERCENT4: 
		fHslider6_ = (float*)data; // , 20.0, 0.0, 100.0, 0.10000000000000001 
		break;
	case PERCENT5: 
		fHslider4_ = (float*)data; // , 0.0, 0.0, 100.0, 0.10000000000000001 
		break;
	case TIME1: 
		fHslider13_ = (float*)data; // , 30.0, 24.0, 360.0, 1.0 
		break;
	case TIME2: 
		fHslider11_ = (float*)data; // , 60.0, 24.0, 360.0, 1.0 
		break;
	case TIME3: 
		fHslider9_ = (float*)data; // , 120.0, 24.0, 360.0, 1.0 
		break;
	case TIME4: 
		fHslider7_ = (float*)data; // , 150.0, 24.0, 360.0, 1.0 
		break;
	case TIME5: 
		fHslider5_ = (float*)data; // , 240.0, 24.0, 360.0, 1.0 
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
