// generated from file '../src/LV2/faust/mbdel.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace mbdel {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fVec0[2];
	double fConst0;
	double fConst1;
	double fConst2;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	double fConst3;
	double fConst4;
	double fRec4[2];
	double fRec5[2];
	double fRec6[2];
	double fRec7[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec8[2];
	double fConst5;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	double fRec13[2];
	double fRec12[3];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT	*fHslider2_;
	double fRec11[3];
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT	*fHslider3_;
	double fRec10[3];
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT	*fHslider4_;
	double fRec9[3];
	int IOTA;
	double *fVec1;
	double fRec3[2];
	double fRec0[2];
	int iRec1[2];
	double fRec2[2];
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT	*fVbargraph0_;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT	*fHslider5_;
	double fRec18[2];
	double fRec19[2];
	double fRec20[2];
	double fRec21[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec22[2];
	double fRec28[2];
	double fRec27[3];
	double fVec2[2];
	double fRec26[2];
	double fRec25[3];
	double fRec24[3];
	double fRec23[3];
	double *fVec3;
	double fRec17[2];
	double fRec14[2];
	int iRec15[2];
	double fRec16[2];
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT	*fVbargraph1_;
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT	*fHslider6_;
	double fRec33[2];
	double fRec34[2];
	double fRec35[2];
	double fRec36[2];
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT	*fVslider5_;
	double fRec37[2];
	double fRec42[2];
	double fRec41[3];
	double fVec4[2];
	double fRec40[2];
	double fRec39[3];
	double fRec38[3];
	double *fVec5;
	double fRec32[2];
	double fRec29[2];
	int iRec30[2];
	double fRec31[2];
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT	*fVbargraph2_;
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT	*fHslider7_;
	double fRec47[2];
	double fRec48[2];
	double fRec49[2];
	double fRec50[2];
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT	*fVslider6_;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT	*fVslider7_;
	double fRec51[2];
	double fRec55[2];
	double fRec54[3];
	double fVec6[2];
	double fRec53[2];
	double fRec52[3];
	double *fVec7;
	double fRec46[2];
	double fRec43[2];
	int iRec44[2];
	double fRec45[2];
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT	*fVbargraph3_;
	FAUSTFLOAT fHslider8;
	FAUSTFLOAT	*fHslider8_;
	double fRec60[2];
	double fRec61[2];
	double fRec62[2];
	double fRec63[2];
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT	*fVslider8_;
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT	*fVslider9_;
	double fRec64[2];
	double fRec66[2];
	double fRec65[3];
	double *fVec8;
	double fRec59[2];
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
	  fVec1(0),
	  fVec3(0),
	  fVec5(0),
	  fVec7(0),
	  fVec8(0),
	  mem_allocated(false) {
	version = PLUGINLV2_VERSION;
	id = "mbdel";
	name = N_("MultiBand Delay");
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
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec4[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec5[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec6[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec7[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec8[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec13[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRec12[l7] = 0.0;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec11[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec10[l9] = 0.0;
	for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) fRec9[l10] = 0.0;
	for (int l11 = 0; (l11 < 524288); l11 = (l11 + 1)) fVec1[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec3[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec0[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) iRec1[l14] = 0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec2[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec18[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec19[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec20[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec21[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fRec22[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec28[l21] = 0.0;
	for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) fRec27[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fVec2[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec26[l24] = 0.0;
	for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) fRec25[l25] = 0.0;
	for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) fRec24[l26] = 0.0;
	for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) fRec23[l27] = 0.0;
	for (int l28 = 0; (l28 < 524288); l28 = (l28 + 1)) fVec3[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fRec17[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec14[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) iRec15[l31] = 0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fRec16[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fRec33[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fRec34[l34] = 0.0;
	for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) fRec35[l35] = 0.0;
	for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) fRec36[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fRec37[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fRec42[l38] = 0.0;
	for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) fRec41[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fVec4[l40] = 0.0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) fRec40[l41] = 0.0;
	for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) fRec39[l42] = 0.0;
	for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) fRec38[l43] = 0.0;
	for (int l44 = 0; (l44 < 524288); l44 = (l44 + 1)) fVec5[l44] = 0.0;
	for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) fRec32[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec29[l46] = 0.0;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) iRec30[l47] = 0;
	for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) fRec31[l48] = 0.0;
	for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) fRec47[l49] = 0.0;
	for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) fRec48[l50] = 0.0;
	for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) fRec49[l51] = 0.0;
	for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) fRec50[l52] = 0.0;
	for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) fRec51[l53] = 0.0;
	for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) fRec55[l54] = 0.0;
	for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) fRec54[l55] = 0.0;
	for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) fVec6[l56] = 0.0;
	for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) fRec53[l57] = 0.0;
	for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) fRec52[l58] = 0.0;
	for (int l59 = 0; (l59 < 524288); l59 = (l59 + 1)) fVec7[l59] = 0.0;
	for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) fRec46[l60] = 0.0;
	for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) fRec43[l61] = 0.0;
	for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) iRec44[l62] = 0;
	for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) fRec45[l63] = 0.0;
	for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) fRec60[l64] = 0.0;
	for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) fRec61[l65] = 0.0;
	for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) fRec62[l66] = 0.0;
	for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) fRec63[l67] = 0.0;
	for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) fRec64[l68] = 0.0;
	for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) fRec66[l69] = 0.0;
	for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) fRec65[l70] = 0.0;
	for (int l71 = 0; (l71 < 524288); l71 = (l71 + 1)) fVec8[l71] = 0.0;
	for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) fRec59[l72] = 0.0;
	for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) fRec56[l73] = 0.0;
	for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) iRec57[l74] = 0;
	for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) fRec58[l75] = 0.0;
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
	fConst2 = (60.0 * fConst0);
	fConst3 = (10.0 / fConst0);
	fConst4 = (0.0 - fConst3);
	fConst5 = (3.1415926535897931 / fConst0);
	IOTA = 0;
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void Dsp::mem_alloc()
{
	if (!fVec1) fVec1 = new double[524288];
	if (!fVec3) fVec3 = new double[524288];
	if (!fVec5) fVec5 = new double[524288];
	if (!fVec7) fVec7 = new double[524288];
	if (!fVec8) fVec8 = new double[524288];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec1) { delete fVec1; fVec1 = 0; }
	if (fVec3) { delete fVec3; fVec3 = 0; }
	if (fVec5) { delete fVec5; fVec5 = 0; }
	if (fVec7) { delete fVec7; fVec7 = 0; }
	if (fVec8) { delete fVec8; fVec8 = 0; }
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
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fHslider1 (*fHslider1_)
#define fHslider2 (*fHslider2_)
#define fHslider3 (*fHslider3_)
#define fHslider4 (*fHslider4_)
#define fVbargraph0 (*fVbargraph0_)
#define fHslider5 (*fHslider5_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
#define fVbargraph1 (*fVbargraph1_)
#define fHslider6 (*fHslider6_)
#define fVslider4 (*fVslider4_)
#define fVslider5 (*fVslider5_)
#define fVbargraph2 (*fVbargraph2_)
#define fHslider7 (*fHslider7_)
#define fVslider6 (*fVslider6_)
#define fVslider7 (*fVslider7_)
#define fVbargraph3 (*fVbargraph3_)
#define fHslider8 (*fHslider8_)
#define fVslider8 (*fVslider8_)
#define fVslider9 (*fVslider9_)
#define fVbargraph4 (*fVbargraph4_)
	double fSlow0 = (fConst2 / double(fHslider0));
	double fSlow1 = (0.01 * double(fVslider0));
	double fSlow2 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider1))));
	double fSlow3 = std::tan((fConst5 * double(fHslider1)));
	double fSlow4 = (1.0 / fSlow3);
	double fSlow5 = (((fSlow4 + 1.0000000000000004) / fSlow3) + 1.0);
	double fSlow6 = (1.0 / fSlow5);
	double fSlow7 = mydsp_faustpower2_f(fSlow3);
	double fSlow8 = (1.0 / fSlow7);
	double fSlow9 = (fSlow4 + 1.0);
	double fSlow10 = (0.0 - (1.0 / (fSlow3 * fSlow9)));
	double fSlow11 = (1.0 / fSlow9);
	double fSlow12 = (1.0 - fSlow4);
	double fSlow13 = (((fSlow4 + -1.0000000000000004) / fSlow3) + 1.0);
	double fSlow14 = (2.0 * (1.0 - fSlow8));
	double fSlow15 = (0.0 - (2.0 / fSlow7));
	double fSlow16 = std::tan((fConst5 * double(fHslider2)));
	double fSlow17 = (1.0 / fSlow16);
	double fSlow18 = (fSlow17 + 1.0);
	double fSlow19 = (1.0 / ((fSlow18 / fSlow16) + 1.0));
	double fSlow20 = (1.0 - fSlow17);
	double fSlow21 = (1.0 - (fSlow20 / fSlow16));
	double fSlow22 = mydsp_faustpower2_f(fSlow16);
	double fSlow23 = (1.0 / fSlow22);
	double fSlow24 = (2.0 * (1.0 - fSlow23));
	double fSlow25 = std::tan((fConst5 * double(fHslider3)));
	double fSlow26 = (1.0 / fSlow25);
	double fSlow27 = (fSlow26 + 1.0);
	double fSlow28 = (1.0 / ((fSlow27 / fSlow25) + 1.0));
	double fSlow29 = (1.0 - fSlow26);
	double fSlow30 = (1.0 - (fSlow29 / fSlow25));
	double fSlow31 = mydsp_faustpower2_f(fSlow25);
	double fSlow32 = (1.0 / fSlow31);
	double fSlow33 = (2.0 * (1.0 - fSlow32));
	double fSlow34 = std::tan((fConst5 * double(fHslider4)));
	double fSlow35 = (1.0 / fSlow34);
	double fSlow36 = (fSlow35 + 1.0);
	double fSlow37 = (1.0 / ((fSlow36 / fSlow34) + 1.0));
	double fSlow38 = (1.0 - fSlow35);
	double fSlow39 = (1.0 - (fSlow38 / fSlow34));
	double fSlow40 = mydsp_faustpower2_f(fSlow34);
	double fSlow41 = (1.0 / fSlow40);
	double fSlow42 = (2.0 * (1.0 - fSlow41));
	double fSlow43 = (fConst2 / double(fHslider5));
	double fSlow44 = (0.01 * double(fVslider2));
	double fSlow45 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider3))));
	double fSlow46 = (((fSlow17 + 1.0000000000000004) / fSlow16) + 1.0);
	double fSlow47 = (1.0 / fSlow46);
	double fSlow48 = (0.0 - (1.0 / (fSlow16 * fSlow18)));
	double fSlow49 = (1.0 / fSlow18);
	double fSlow50 = (1.0 / (fSlow16 * fSlow5));
	double fSlow51 = (((fSlow17 + -1.0000000000000004) / fSlow16) + 1.0);
	double fSlow52 = (0.0 - (2.0 / fSlow22));
	double fSlow53 = (fConst2 / double(fHslider6));
	double fSlow54 = (0.01 * double(fVslider4));
	double fSlow55 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider5))));
	double fSlow56 = (((fSlow26 + 1.0000000000000004) / fSlow25) + 1.0);
	double fSlow57 = (1.0 / fSlow56);
	double fSlow58 = (0.0 - (1.0 / (fSlow25 * fSlow27)));
	double fSlow59 = (1.0 / fSlow27);
	double fSlow60 = (1.0 / (fSlow25 * fSlow46));
	double fSlow61 = (((fSlow26 + -1.0000000000000004) / fSlow25) + 1.0);
	double fSlow62 = (0.0 - (2.0 / fSlow31));
	double fSlow63 = (fConst2 / double(fHslider7));
	double fSlow64 = (0.01 * double(fVslider6));
	double fSlow65 = (1.0 / (((fSlow35 + 1.0000000000000004) / fSlow34) + 1.0));
	double fSlow66 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider7))));
	double fSlow67 = (0.0 - (1.0 / (fSlow34 * fSlow36)));
	double fSlow68 = (1.0 / fSlow36);
	double fSlow69 = (1.0 / (fSlow34 * fSlow56));
	double fSlow70 = (((fSlow35 + -1.0000000000000004) / fSlow34) + 1.0);
	double fSlow71 = (0.0 - (2.0 / fSlow40));
	double fSlow72 = (fConst2 / double(fHslider8));
	double fSlow73 = (0.01 * double(fVslider8));
	double fSlow74 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider9))));
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = double(input0[i]);
		fVec0[0] = fTemp0;
		int iTemp1 = (iRec1[1] < 4096);
		double fTemp2 = ((fRec4[1] != 0.0) ? (((fRec5[1] > 0.0) & (fRec5[1] < 1.0)) ? fRec4[1] : 0.0) : (((fRec5[1] == 0.0) & (fSlow0 != fRec6[1])) ? fConst3 : (((fRec5[1] == 1.0) & (fSlow0 != fRec7[1])) ? fConst4 : 0.0)));
		fRec4[0] = fTemp2;
		fRec5[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec5[1] + fTemp2)));
		fRec6[0] = (((fRec5[1] >= 1.0) & (fRec7[1] != fSlow0)) ? fSlow0 : fRec6[1]);
		fRec7[0] = (((fRec5[1] <= 0.0) & (fRec6[1] != fSlow0)) ? fSlow0 : fRec7[1]);
		fRec8[0] = (fSlow2 + (0.999 * fRec8[1]));
		fRec13[0] = ((fSlow10 * fVec0[1]) - (fSlow11 * ((fSlow12 * fRec13[1]) - (fSlow4 * fTemp0))));
		fRec12[0] = (fRec13[0] - (fSlow6 * ((fSlow13 * fRec12[2]) + (fSlow14 * fRec12[1]))));
		double fTemp3 = (fSlow24 * fRec11[1]);
		fRec11[0] = ((fSlow6 * (((fSlow8 * fRec12[0]) + (fSlow15 * fRec12[1])) + (fSlow8 * fRec12[2]))) - (fSlow19 * ((fSlow21 * fRec11[2]) + fTemp3)));
		double fTemp4 = (fSlow33 * fRec10[1]);
		fRec10[0] = ((fRec11[2] + (fSlow19 * (fTemp3 + (fSlow21 * fRec11[0])))) - (fSlow28 * ((fSlow30 * fRec10[2]) + fTemp4)));
		double fTemp5 = (fSlow42 * fRec9[1]);
		fRec9[0] = ((fRec10[2] + (fSlow28 * (fTemp4 + (fSlow30 * fRec10[0])))) - (fSlow37 * ((fSlow39 * fRec9[2]) + fTemp5)));
		double fTemp6 = ((fSlow1 * fRec3[1]) + (fRec8[0] * (fRec9[2] + (fSlow37 * (fTemp5 + (fSlow39 * fRec9[0]))))));
		fVec1[(IOTA & 524287)] = fTemp6;
		fRec3[0] = (((1.0 - fRec5[0]) * fVec1[((IOTA - int(std::min<double>(262144.0, std::max<double>(0.0, fRec6[0])))) & 524287)]) + (fRec5[0] * fVec1[((IOTA - int(std::min<double>(262144.0, std::max<double>(0.0, fRec7[0])))) & 524287)]));
		double fTemp7 = std::max<double>(fConst1, std::fabs(fRec3[0]));
		fRec0[0] = (iTemp1 ? std::max<double>(fRec0[1], fTemp7) : fTemp7);
		iRec1[0] = (iTemp1 ? (iRec1[1] + 1) : 1);
		fRec2[0] = (iTemp1 ? fRec2[1] : fRec0[1]);
		fVbargraph0 = FAUSTFLOAT(fRec2[0]);
		int iTemp8 = (iRec15[1] < 4096);
		double fTemp9 = ((fRec18[1] != 0.0) ? (((fRec19[1] > 0.0) & (fRec19[1] < 1.0)) ? fRec18[1] : 0.0) : (((fRec19[1] == 0.0) & (fSlow43 != fRec20[1])) ? fConst3 : (((fRec19[1] == 1.0) & (fSlow43 != fRec21[1])) ? fConst4 : 0.0)));
		fRec18[0] = fTemp9;
		fRec19[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec19[1] + fTemp9)));
		fRec20[0] = (((fRec19[1] >= 1.0) & (fRec21[1] != fSlow43)) ? fSlow43 : fRec20[1]);
		fRec21[0] = (((fRec19[1] <= 0.0) & (fRec20[1] != fSlow43)) ? fSlow43 : fRec21[1]);
		fRec22[0] = (fSlow45 + (0.999 * fRec22[1]));
		fRec28[0] = (0.0 - (fSlow11 * ((fSlow12 * fRec28[1]) - (fTemp0 + fVec0[1]))));
		fRec27[0] = (fRec28[0] - (fSlow6 * ((fSlow13 * fRec27[2]) + (fSlow14 * fRec27[1]))));
		double fTemp10 = (fRec27[2] + (fRec27[0] + (2.0 * fRec27[1])));
		double fTemp11 = (fSlow6 * fTemp10);
		fVec2[0] = fTemp11;
		fRec26[0] = ((fSlow48 * fVec2[1]) - (fSlow49 * ((fSlow20 * fRec26[1]) - (fSlow50 * fTemp10))));
		fRec25[0] = (fRec26[0] - (fSlow47 * ((fSlow51 * fRec25[2]) + (fSlow24 * fRec25[1]))));
		double fTemp12 = (fSlow33 * fRec24[1]);
		fRec24[0] = ((fSlow47 * (((fSlow23 * fRec25[0]) + (fSlow52 * fRec25[1])) + (fSlow23 * fRec25[2]))) - (fSlow28 * ((fSlow30 * fRec24[2]) + fTemp12)));
		double fTemp13 = (fSlow42 * fRec23[1]);
		fRec23[0] = ((fRec24[2] + (fSlow28 * (fTemp12 + (fSlow30 * fRec24[0])))) - (fSlow37 * ((fSlow39 * fRec23[2]) + fTemp13)));
		double fTemp14 = ((fSlow44 * fRec17[1]) + (fRec22[0] * (fRec23[2] + (fSlow37 * (fTemp13 + (fSlow39 * fRec23[0]))))));
		fVec3[(IOTA & 524287)] = fTemp14;
		fRec17[0] = (((1.0 - fRec19[0]) * fVec3[((IOTA - int(std::min<double>(262144.0, std::max<double>(0.0, fRec20[0])))) & 524287)]) + (fRec19[0] * fVec3[((IOTA - int(std::min<double>(262144.0, std::max<double>(0.0, fRec21[0])))) & 524287)]));
		double fTemp15 = std::max<double>(fConst1, std::fabs(fRec17[0]));
		fRec14[0] = (iTemp8 ? std::max<double>(fRec14[1], fTemp15) : fTemp15);
		iRec15[0] = (iTemp8 ? (iRec15[1] + 1) : 1);
		fRec16[0] = (iTemp8 ? fRec16[1] : fRec14[1]);
		fVbargraph1 = FAUSTFLOAT(fRec16[0]);
		int iTemp16 = (iRec30[1] < 4096);
		double fTemp17 = ((fRec33[1] != 0.0) ? (((fRec34[1] > 0.0) & (fRec34[1] < 1.0)) ? fRec33[1] : 0.0) : (((fRec34[1] == 0.0) & (fSlow53 != fRec35[1])) ? fConst3 : (((fRec34[1] == 1.0) & (fSlow53 != fRec36[1])) ? fConst4 : 0.0)));
		fRec33[0] = fTemp17;
		fRec34[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec34[1] + fTemp17)));
		fRec35[0] = (((fRec34[1] >= 1.0) & (fRec36[1] != fSlow53)) ? fSlow53 : fRec35[1]);
		fRec36[0] = (((fRec34[1] <= 0.0) & (fRec35[1] != fSlow53)) ? fSlow53 : fRec36[1]);
		fRec37[0] = (fSlow55 + (0.999 * fRec37[1]));
		fRec42[0] = (0.0 - (fSlow49 * ((fSlow20 * fRec42[1]) - (fTemp11 + fVec2[1]))));
		fRec41[0] = (fRec42[0] - (fSlow47 * ((fSlow51 * fRec41[2]) + (fSlow24 * fRec41[1]))));
		double fTemp18 = (fRec41[2] + (fRec41[0] + (2.0 * fRec41[1])));
		double fTemp19 = (fSlow47 * fTemp18);
		fVec4[0] = fTemp19;
		fRec40[0] = ((fSlow58 * fVec4[1]) - (fSlow59 * ((fSlow29 * fRec40[1]) - (fSlow60 * fTemp18))));
		fRec39[0] = (fRec40[0] - (fSlow57 * ((fSlow61 * fRec39[2]) + (fSlow33 * fRec39[1]))));
		double fTemp20 = (fSlow42 * fRec38[1]);
		fRec38[0] = ((fSlow57 * (((fSlow32 * fRec39[0]) + (fSlow62 * fRec39[1])) + (fSlow32 * fRec39[2]))) - (fSlow37 * ((fSlow39 * fRec38[2]) + fTemp20)));
		double fTemp21 = ((fSlow54 * fRec32[1]) + (fRec37[0] * (fRec38[2] + (fSlow37 * (fTemp20 + (fSlow39 * fRec38[0]))))));
		fVec5[(IOTA & 524287)] = fTemp21;
		fRec32[0] = (((1.0 - fRec34[0]) * fVec5[((IOTA - int(std::min<double>(262144.0, std::max<double>(0.0, fRec35[0])))) & 524287)]) + (fRec34[0] * fVec5[((IOTA - int(std::min<double>(262144.0, std::max<double>(0.0, fRec36[0])))) & 524287)]));
		double fTemp22 = std::max<double>(fConst1, std::fabs(fRec32[0]));
		fRec29[0] = (iTemp16 ? std::max<double>(fRec29[1], fTemp22) : fTemp22);
		iRec30[0] = (iTemp16 ? (iRec30[1] + 1) : 1);
		fRec31[0] = (iTemp16 ? fRec31[1] : fRec29[1]);
		fVbargraph2 = FAUSTFLOAT(fRec31[0]);
		int iTemp23 = (iRec44[1] < 4096);
		double fTemp24 = ((fRec47[1] != 0.0) ? (((fRec48[1] > 0.0) & (fRec48[1] < 1.0)) ? fRec47[1] : 0.0) : (((fRec48[1] == 0.0) & (fSlow63 != fRec49[1])) ? fConst3 : (((fRec48[1] == 1.0) & (fSlow63 != fRec50[1])) ? fConst4 : 0.0)));
		fRec47[0] = fTemp24;
		fRec48[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec48[1] + fTemp24)));
		fRec49[0] = (((fRec48[1] >= 1.0) & (fRec50[1] != fSlow63)) ? fSlow63 : fRec49[1]);
		fRec50[0] = (((fRec48[1] <= 0.0) & (fRec49[1] != fSlow63)) ? fSlow63 : fRec50[1]);
		fRec51[0] = (fSlow66 + (0.999 * fRec51[1]));
		fRec55[0] = (0.0 - (fSlow59 * ((fSlow29 * fRec55[1]) - (fTemp19 + fVec4[1]))));
		fRec54[0] = (fRec55[0] - (fSlow57 * ((fSlow61 * fRec54[2]) + (fSlow33 * fRec54[1]))));
		double fTemp25 = (fRec54[2] + (fRec54[0] + (2.0 * fRec54[1])));
		double fTemp26 = (fSlow57 * fTemp25);
		fVec6[0] = fTemp26;
		fRec53[0] = ((fSlow67 * fVec6[1]) - (fSlow68 * ((fSlow38 * fRec53[1]) - (fSlow69 * fTemp25))));
		fRec52[0] = (fRec53[0] - (fSlow65 * ((fSlow70 * fRec52[2]) + (fSlow42 * fRec52[1]))));
		double fTemp27 = ((fSlow64 * fRec46[1]) + (fSlow65 * (fRec51[0] * (((fSlow41 * fRec52[0]) + (fSlow71 * fRec52[1])) + (fSlow41 * fRec52[2])))));
		fVec7[(IOTA & 524287)] = fTemp27;
		fRec46[0] = (((1.0 - fRec48[0]) * fVec7[((IOTA - int(std::min<double>(262144.0, std::max<double>(0.0, fRec49[0])))) & 524287)]) + (fRec48[0] * fVec7[((IOTA - int(std::min<double>(262144.0, std::max<double>(0.0, fRec50[0])))) & 524287)]));
		double fTemp28 = std::max<double>(fConst1, std::fabs(fRec46[0]));
		fRec43[0] = (iTemp23 ? std::max<double>(fRec43[1], fTemp28) : fTemp28);
		iRec44[0] = (iTemp23 ? (iRec44[1] + 1) : 1);
		fRec45[0] = (iTemp23 ? fRec45[1] : fRec43[1]);
		fVbargraph3 = FAUSTFLOAT(fRec45[0]);
		int iTemp29 = (iRec57[1] < 4096);
		double fTemp30 = ((fRec60[1] != 0.0) ? (((fRec61[1] > 0.0) & (fRec61[1] < 1.0)) ? fRec60[1] : 0.0) : (((fRec61[1] == 0.0) & (fSlow72 != fRec62[1])) ? fConst3 : (((fRec61[1] == 1.0) & (fSlow72 != fRec63[1])) ? fConst4 : 0.0)));
		fRec60[0] = fTemp30;
		fRec61[0] = std::max<double>(0.0, std::min<double>(1.0, (fRec61[1] + fTemp30)));
		fRec62[0] = (((fRec61[1] >= 1.0) & (fRec63[1] != fSlow72)) ? fSlow72 : fRec62[1]);
		fRec63[0] = (((fRec61[1] <= 0.0) & (fRec62[1] != fSlow72)) ? fSlow72 : fRec63[1]);
		fRec64[0] = (fSlow74 + (0.999 * fRec64[1]));
		fRec66[0] = (0.0 - (fSlow68 * ((fSlow38 * fRec66[1]) - (fTemp26 + fVec6[1]))));
		fRec65[0] = (fRec66[0] - (fSlow65 * ((fSlow70 * fRec65[2]) + (fSlow42 * fRec65[1]))));
		double fTemp31 = ((fSlow73 * fRec59[1]) + (fSlow65 * (fRec64[0] * (fRec65[2] + (fRec65[0] + (2.0 * fRec65[1]))))));
		fVec8[(IOTA & 524287)] = fTemp31;
		fRec59[0] = (((1.0 - fRec61[0]) * fVec8[((IOTA - int(std::min<double>(262144.0, std::max<double>(0.0, fRec62[0])))) & 524287)]) + (fRec61[0] * fVec8[((IOTA - int(std::min<double>(262144.0, std::max<double>(0.0, fRec63[0])))) & 524287)]));
		double fTemp32 = std::max<double>(fConst1, std::fabs(fRec59[0]));
		fRec56[0] = (iTemp29 ? std::max<double>(fRec56[1], fTemp32) : fTemp32);
		iRec57[0] = (iTemp29 ? (iRec57[1] + 1) : 1);
		fRec58[0] = (iTemp29 ? fRec58[1] : fRec56[1]);
		fVbargraph4 = FAUSTFLOAT(fRec58[0]);
		output0[i] = FAUSTFLOAT((fTemp0 + ((((fRec3[0] + fRec17[0]) + fRec32[0]) + fRec46[0]) + fRec59[0])));
		fVec0[1] = fVec0[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec13[1] = fRec13[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		IOTA = (IOTA + 1);
		fRec3[1] = fRec3[0];
		fRec0[1] = fRec0[0];
		iRec1[1] = iRec1[0];
		fRec2[1] = fRec2[0];
		fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fRec28[1] = fRec28[0];
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		fVec2[1] = fVec2[0];
		fRec26[1] = fRec26[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fRec23[2] = fRec23[1];
		fRec23[1] = fRec23[0];
		fRec17[1] = fRec17[0];
		fRec14[1] = fRec14[0];
		iRec15[1] = iRec15[0];
		fRec16[1] = fRec16[0];
		fRec33[1] = fRec33[0];
		fRec34[1] = fRec34[0];
		fRec35[1] = fRec35[0];
		fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fRec42[1] = fRec42[0];
		fRec41[2] = fRec41[1];
		fRec41[1] = fRec41[0];
		fVec4[1] = fVec4[0];
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		fRec32[1] = fRec32[0];
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
		fVec6[1] = fVec6[0];
		fRec53[1] = fRec53[0];
		fRec52[2] = fRec52[1];
		fRec52[1] = fRec52[0];
		fRec46[1] = fRec46[0];
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
		fRec59[1] = fRec59[0];
		fRec56[1] = fRec56[0];
		iRec57[1] = iRec57[0];
		fRec58[1] = fRec58[0];
	}
#undef fHslider0
#undef fVslider0
#undef fVslider1
#undef fHslider1
#undef fHslider2
#undef fHslider3
#undef fHslider4
#undef fVbargraph0
#undef fHslider5
#undef fVslider2
#undef fVslider3
#undef fVbargraph1
#undef fHslider6
#undef fVslider4
#undef fVslider5
#undef fVbargraph2
#undef fHslider7
#undef fVslider6
#undef fVslider7
#undef fVbargraph3
#undef fHslider8
#undef fVslider8
#undef fVslider9
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
		fHslider4_ = (float*)data; // , 80.0, 20.0, 20000.0, 1.0800000000000001 
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
	case DELAY1: 
		fHslider8_ = (float*)data; // , 30.0, 24.0, 360.0, 1.0 
		break;
	case DELAY2: 
		fHslider7_ = (float*)data; // , 60.0, 24.0, 360.0, 1.0 
		break;
	case DELAY3: 
		fHslider6_ = (float*)data; // , 90.0, 24.0, 360.0, 1.0 
		break;
	case DELAY4: 
		fHslider5_ = (float*)data; // , 120.0, 24.0, 360.0, 1.0 
		break;
	case DELAY5: 
		fHslider0_ = (float*)data; // , 150.0, 24.0, 360.0, 1.0 
		break;
	case FEEDBACK1: 
		fVslider8_ = (float*)data; // , 50.0, 1.0, 100.0, 1.0 
		break;
	case FEEDBACK2: 
		fVslider6_ = (float*)data; // , 50.0, 1.0, 100.0, 1.0 
		break;
	case FEEDBACK3: 
		fVslider4_ = (float*)data; // , 50.0, 1.0, 100.0, 1.0 
		break;
	case FEEDBACK4: 
		fVslider2_ = (float*)data; // , 50.0, 1.0, 100.0, 1.0 
		break;
	case FEEDBACK5: 
		fVslider0_ = (float*)data; // , 50.0, 1.0, 100.0, 1.0 
		break;
	case GAIN1: 
		fVslider9_ = (float*)data; // , -10.0, -20.0, 20.0, 0.10000000000000001 
		break;
	case GAIN2: 
		fVslider7_ = (float*)data; // , -5.0, -20.0, 20.0, 0.10000000000000001 
		break;
	case GAIN3: 
		fVslider5_ = (float*)data; // , -2.0, -20.0, 20.0, 0.10000000000000001 
		break;
	case GAIN4: 
		fVslider3_ = (float*)data; // , 0.0, -20.0, 20.0, 0.10000000000000001 
		break;
	case GAIN5: 
		fVslider1_ = (float*)data; // , -10.0, -20.0, 20.0, 0.10000000000000001 
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
   DELAY1, 
   DELAY2, 
   DELAY3, 
   DELAY4, 
   DELAY5, 
   FEEDBACK1, 
   FEEDBACK2, 
   FEEDBACK3, 
   FEEDBACK4, 
   FEEDBACK5, 
   GAIN1, 
   GAIN2, 
   GAIN3, 
   GAIN4, 
   GAIN5, 
   V1, 
   V2, 
   V3, 
   V4, 
   V5, 
} PortIndex;
*/

} // end namespace mbdel
