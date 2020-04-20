// generated from file '../src/faust/digital_delay_st.dsp' by dsp2cc:
// Code generated with Faust 2.20.2 (https://faust.grame.fr)

#include "beat.h"

namespace digital_delay_st {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fHslider0;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider1;
	float fConst2;
	float fConst3;
	float fRec1[2];
	float fRec2[2];
	float fRec3[2];
	float fRec4[2];
	FAUSTFLOAT fHslider2;
	float fConst4;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fVslider2;
	float fRec6[3];
	float fRec5[3];
	float fVec0[2];
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
	float fConst10;
	float fConst11;
	float fConst12;
	float fConst13;
	float fConst14;
	float fConst15;
	float fConst16;
	float fConst17;
	float fConst18;
	float fConst19;
	float fConst20;
	float fConst21;
	float fConst22;
	float fConst23;
	float fConst24;
	float fConst25;
	float fConst26;
	float fConst27;
	float fConst28;
	float fConst29;
	float fConst30;
	float fConst31;
	float fConst32;
	float fConst33;
	float fConst34;
	float fConst35;
	float fConst36;
	float fConst37;
	float fConst38;
	float fConst39;
	float fConst40;
	float fConst41;
	float fConst42;
	float fConst43;
	float fConst44;
	float fConst45;
	float fConst46;
	float fConst47;
	float fConst48;
	float fConst49;
	float fConst50;
	float fConst51;
	float fRec15[2];
	float fConst52;
	float fConst53;
	float fRec14[3];
	float fConst54;
	float fConst55;
	float fRec13[3];
	float fConst56;
	float fConst57;
	float fConst58;
	float fConst59;
	float fRec12[3];
	float fConst60;
	float fConst61;
	float fConst62;
	float fConst63;
	float fRec11[3];
	float fConst64;
	float fConst65;
	float fConst66;
	float fConst67;
	float fRec10[3];
	float fConst68;
	float fConst69;
	float fConst70;
	float fConst71;
	float fRec9[3];
	float fConst72;
	float fConst73;
	float fConst74;
	float fVec1[2];
	float fRec8[2];
	float fConst75;
	float fConst76;
	float fConst77;
	float fRec7[3];
	float fRec22[2];
	float fRec20[2];
	float fRec18[2];
	float fRec16[2];
	float fRec30[2];
	float fRec28[2];
	float fRec26[2];
	float fRec24[2];
	int IOTA;
	float *fVec2;
	float fRec0[2];
	float fRec34[3];
	float fRec33[3];
	float fVec3[2];
	float fRec43[2];
	float fRec42[3];
	float fRec41[3];
	float fRec40[3];
	float fRec39[3];
	float fRec38[3];
	float fRec37[3];
	float fVec4[2];
	float fRec36[2];
	float fRec35[3];
	float fRec50[2];
	float fRec48[2];
	float fRec46[2];
	float fRec44[2];
	float fRec58[2];
	float fRec56[2];
	float fRec54[2];
	float fRec52[2];
	float *fVec5;
	float fRec32[2];

	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void clear_state_f();
	int activate(bool start);
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int activate_static(bool start, PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int sample_rate, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginDef(),
	  fVec2(0),
	  fVec5(0),
	  mem_allocated(false) {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "didest";
	name = N_("Digital Stereo Delay");
	groups = 0;
	description = N_("Digital Delay Stereo Version"); // description (tooltip)
	category = N_("Echo / Delay");       // category
	shortname = N_("Digi Delay S");     // shortname
	mono_audio = 0;
	stereo_audio = compute_static;
	set_samplerate = init_static;
	activate_plugin = activate_static;
	register_params = register_params_static;
	load_ui = load_ui_f_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec1[l0] = 0.0f;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec2[l1] = 0.0f;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec3[l2] = 0.0f;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec4[l3] = 0.0f;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec6[l4] = 0.0f;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec5[l5] = 0.0f;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fVec0[l6] = 0.0f;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec15[l7] = 0.0f;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec14[l8] = 0.0f;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec13[l9] = 0.0f;
	for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) fRec12[l10] = 0.0f;
	for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) fRec11[l11] = 0.0f;
	for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) fRec10[l12] = 0.0f;
	for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) fRec9[l13] = 0.0f;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fVec1[l14] = 0.0f;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec8[l15] = 0.0f;
	for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) fRec7[l16] = 0.0f;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec22[l17] = 0.0f;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec20[l18] = 0.0f;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec18[l19] = 0.0f;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fRec16[l20] = 0.0f;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec30[l21] = 0.0f;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fRec28[l22] = 0.0f;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fRec26[l23] = 0.0f;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec24[l24] = 0.0f;
	for (int l25 = 0; (l25 < 1048576); l25 = (l25 + 1)) fVec2[l25] = 0.0f;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fRec0[l26] = 0.0f;
	for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) fRec34[l27] = 0.0f;
	for (int l28 = 0; (l28 < 3); l28 = (l28 + 1)) fRec33[l28] = 0.0f;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fVec3[l29] = 0.0f;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec43[l30] = 0.0f;
	for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) fRec42[l31] = 0.0f;
	for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) fRec41[l32] = 0.0f;
	for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) fRec40[l33] = 0.0f;
	for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) fRec39[l34] = 0.0f;
	for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) fRec38[l35] = 0.0f;
	for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) fRec37[l36] = 0.0f;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fVec4[l37] = 0.0f;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fRec36[l38] = 0.0f;
	for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) fRec35[l39] = 0.0f;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fRec50[l40] = 0.0f;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) fRec48[l41] = 0.0f;
	for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) fRec46[l42] = 0.0f;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fRec44[l43] = 0.0f;
	for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) fRec58[l44] = 0.0f;
	for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) fRec56[l45] = 0.0f;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec54[l46] = 0.0f;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) fRec52[l47] = 0.0f;
	for (int l48 = 0; (l48 < 1048576); l48 = (l48 + 1)) fVec5[l48] = 0.0f;
	for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) fRec32[l49] = 0.0f;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
	fConst1 = (60.0f * fConst0);
	fConst2 = (10.0f / fConst0);
	fConst3 = (0.0f - fConst2);
	fConst4 = (3.14159274f / fConst0);
	fConst5 = std::tan((37699.1133f / fConst0));
	fConst6 = (1.0f / fConst5);
	fConst7 = (((fConst6 + 1.0f) / fConst5) + 1.0f);
	fConst8 = (0.800000012f / fConst7);
	fConst9 = (1.0f / (fConst6 + 1.0f));
	fConst10 = (1.0f - fConst6);
	fConst11 = (25132.7422f / fConst0);
	fConst12 = std::tan(fConst11);
	fConst13 = (1.0f / fConst12);
	fConst14 = (fConst0 * std::sin((50265.4844f / fConst0)));
	fConst15 = (3141.59277f / fConst14);
	fConst16 = (1.0f / (((fConst13 + fConst15) / fConst12) + 1.0f));
	fConst17 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst12))));
	fConst18 = (12566.3711f / fConst0);
	fConst19 = std::tan(fConst18);
	fConst20 = (1.0f / fConst19);
	fConst21 = (fConst0 * std::sin(fConst11));
	fConst22 = (6268.30127f / fConst21);
	fConst23 = (1.0f / (((fConst20 + fConst22) / fConst19) + 1.0f));
	fConst24 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst19))));
	fConst25 = std::tan((6283.18555f / fConst0));
	fConst26 = (1.0f / fConst25);
	fConst27 = (fConst0 * std::sin(fConst18));
	fConst28 = (1570.79639f / fConst27);
	fConst29 = (1.0f / (((fConst26 + fConst28) / fConst25) + 1.0f));
	fConst30 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst25))));
	fConst31 = std::tan((1178.09729f / fConst0));
	fConst32 = (1.0f / fConst31);
	fConst33 = (fConst0 * std::sin((2356.19458f / fConst0)));
	fConst34 = (392.699097f / fConst33);
	fConst35 = (1.0f / (((fConst32 + fConst34) / fConst31) + 1.0f));
	fConst36 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst31))));
	fConst37 = std::tan((628.318542f / fConst0));
	fConst38 = (1.0f / fConst37);
	fConst39 = (fConst0 * std::sin((1256.63708f / fConst0)));
	fConst40 = (221.880875f / fConst39);
	fConst41 = (1.0f / (((fConst38 + fConst40) / fConst37) + 1.0f));
	fConst42 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst37))));
	fConst43 = std::tan((251.327408f / fConst0));
	fConst44 = (1.0f / fConst43);
	fConst45 = (1.0f / (((fConst44 + 1.0f) / fConst43) + 1.0f));
	fConst46 = mydsp_faustpower2_f(fConst43);
	fConst47 = (1.0f / fConst46);
	fConst48 = (fConst44 + 1.0f);
	fConst49 = (0.0f - (1.0f / (fConst43 * fConst48)));
	fConst50 = (1.0f / fConst48);
	fConst51 = (1.0f - fConst44);
	fConst52 = (((fConst44 + -1.0f) / fConst43) + 1.0f);
	fConst53 = (2.0f * (1.0f - fConst47));
	fConst54 = (0.0f - (2.0f / fConst46));
	fConst55 = (((fConst38 - fConst40) / fConst37) + 1.0f);
	fConst56 = (157.079636f / fConst39);
	fConst57 = (((fConst38 + fConst56) / fConst37) + 1.0f);
	fConst58 = (((fConst38 - fConst56) / fConst37) + 1.0f);
	fConst59 = (((fConst32 - fConst34) / fConst31) + 1.0f);
	fConst60 = (466.723724f / fConst33);
	fConst61 = (((fConst32 + fConst60) / fConst31) + 1.0f);
	fConst62 = (((fConst32 - fConst60) / fConst31) + 1.0f);
	fConst63 = (((fConst26 - fConst28) / fConst25) + 1.0f);
	fConst64 = (2218.80884f / fConst27);
	fConst65 = (((fConst26 + fConst64) / fConst25) + 1.0f);
	fConst66 = (((fConst26 - fConst64) / fConst25) + 1.0f);
	fConst67 = (((fConst20 - fConst22) / fConst19) + 1.0f);
	fConst68 = (3141.59277f / fConst21);
	fConst69 = (((fConst20 + fConst68) / fConst19) + 1.0f);
	fConst70 = (((fConst20 - fConst68) / fConst19) + 1.0f);
	fConst71 = (((fConst13 - fConst15) / fConst12) + 1.0f);
	fConst72 = (3955.03076f / fConst14);
	fConst73 = (((fConst13 + fConst72) / fConst12) + 1.0f);
	fConst74 = (((fConst13 - fConst72) / fConst12) + 1.0f);
	fConst75 = (1.0f / fConst7);
	fConst76 = (((fConst6 + -1.0f) / fConst5) + 1.0f);
	fConst77 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst5))));
	IOTA = 0;
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void Dsp::mem_alloc()
{
	if (!fVec2) fVec2 = new float[1048576];
	if (!fVec5) fVec5 = new float[1048576];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec2) { delete fVec2; fVec2 = 0; }
	if (fVec5) { delete fVec5; fVec5 = 0; }
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

int Dsp::activate_static(bool start, PluginDef *p)
{
	return static_cast<Dsp*>(p)->activate(start);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	float fSlow0 = (0.00999999978f * float(fVslider0));
	float fSlow1 = float(fCheckbox0);
	int iSlow2 = int(fSlow1);
	float fSlow3 = (0.00999999978f * float(fVslider1));
	float fSlow4 = std::min<float>(524288.0f, float(B2N(int(float(fHslider0)), float((fConst1 / float(fHslider1))))));
	float fSlow5 = float(fHslider2);
	int iSlow6 = int(std::min<float>(2.0f, std::max<float>(0.0f, (fSlow5 + -2.0f))));
	int iSlow7 = (iSlow6 == 0);
	int iSlow8 = (iSlow6 == 1);
	int iSlow9 = int(std::min<float>(2.0f, std::max<float>(0.0f, (fSlow5 + -1.0f))));
	int iSlow10 = (iSlow9 == 0);
	int iSlow11 = (iSlow9 == 1);
	int iSlow12 = int(std::min<float>(2.0f, std::max<float>(0.0f, fSlow5)));
	int iSlow13 = (iSlow12 == 0);
	int iSlow14 = (iSlow12 == 1);
	float fSlow15 = std::tan((fConst4 * float(fHslider3)));
	float fSlow16 = (1.0f / fSlow15);
	float fSlow17 = (((fSlow16 + 1.41421354f) / fSlow15) + 1.0f);
	float fSlow18 = (1.0f / fSlow17);
	float fSlow19 = std::tan((fConst4 * float(fHslider4)));
	float fSlow20 = (1.0f / fSlow19);
	float fSlow21 = (1.0f / (((fSlow20 + 1.41421354f) / fSlow19) + 1.0f));
	float fSlow22 = mydsp_faustpower2_f(fSlow19);
	float fSlow23 = (1.0f / fSlow22);
	float fSlow24 = (0.00999999978f * float(fVslider2));
	float fSlow25 = (((fSlow20 + -1.41421354f) / fSlow19) + 1.0f);
	float fSlow26 = (2.0f * (1.0f - fSlow23));
	float fSlow27 = (0.0f - (2.0f / fSlow22));
	float fSlow28 = (((fSlow16 + -1.41421354f) / fSlow15) + 1.0f);
	float fSlow29 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow15))));
	float fSlow30 = (fConst44 / fSlow17);
	float fSlow31 = (1.0f - fSlow1);
	for (int i = 0; (i < count); i = (i + 1)) {
		float fTemp0 = float(input0[i]);
		float fTemp1 = ((fRec1[1] != 0.0f) ? (((fRec2[1] > 0.0f) & (fRec2[1] < 1.0f)) ? fRec1[1] : 0.0f) : (((fRec2[1] == 0.0f) & (fSlow4 != fRec3[1])) ? fConst2 : (((fRec2[1] == 1.0f) & (fSlow4 != fRec4[1])) ? fConst3 : 0.0f)));
		fRec1[0] = fTemp1;
		fRec2[0] = std::max<float>(0.0f, std::min<float>(1.0f, (fRec2[1] + fTemp1)));
		fRec3[0] = (((fRec2[1] >= 1.0f) & (fRec4[1] != fSlow4)) ? fSlow4 : fRec3[1]);
		fRec4[0] = (((fRec2[1] <= 0.0f) & (fRec3[1] != fSlow4)) ? fSlow4 : fRec4[1]);
		float fTemp2 = (1.0f - fRec2[0]);
		fRec6[0] = ((fSlow24 * fRec0[1]) - (fSlow21 * ((fSlow25 * fRec6[2]) + (fSlow26 * fRec6[1]))));
		fRec5[0] = ((fSlow21 * (((fSlow23 * fRec6[0]) + (fSlow27 * fRec6[1])) + (fSlow23 * fRec6[2]))) - (fSlow18 * ((fSlow28 * fRec5[2]) + (fSlow29 * fRec5[1]))));
		float fTemp3 = (fRec5[2] + (fRec5[0] + (2.0f * fRec5[1])));
		float fTemp4 = (fSlow18 * fTemp3);
		fVec0[0] = fTemp4;
		fRec15[0] = ((fConst49 * fVec0[1]) - (fConst50 * ((fConst51 * fRec15[1]) - (fSlow30 * fTemp3))));
		fRec14[0] = (fRec15[0] - (fConst45 * ((fConst52 * fRec14[2]) + (fConst53 * fRec14[1]))));
		float fTemp5 = (fConst42 * fRec13[1]);
		fRec13[0] = ((fConst45 * (((fConst47 * fRec14[0]) + (fConst54 * fRec14[1])) + (fConst47 * fRec14[2]))) - (fConst41 * ((fConst55 * fRec13[2]) + fTemp5)));
		float fTemp6 = (fConst36 * fRec12[1]);
		fRec12[0] = ((fConst41 * ((fTemp5 + (fConst57 * fRec13[0])) + (fConst58 * fRec13[2]))) - (fConst35 * ((fConst59 * fRec12[2]) + fTemp6)));
		float fTemp7 = (fConst30 * fRec11[1]);
		fRec11[0] = ((fConst35 * ((fTemp6 + (fConst61 * fRec12[0])) + (fConst62 * fRec12[2]))) - (fConst29 * ((fConst63 * fRec11[2]) + fTemp7)));
		float fTemp8 = (fConst24 * fRec10[1]);
		fRec10[0] = ((fConst29 * ((fTemp7 + (fConst65 * fRec11[0])) + (fConst66 * fRec11[2]))) - (fConst23 * ((fConst67 * fRec10[2]) + fTemp8)));
		float fTemp9 = (fConst17 * fRec9[1]);
		fRec9[0] = ((fConst23 * ((fTemp8 + (fConst69 * fRec10[0])) + (fConst70 * fRec10[2]))) - (fConst16 * ((fConst71 * fRec9[2]) + fTemp9)));
		float fTemp10 = ((fTemp9 + (fConst73 * fRec9[0])) + (fConst74 * fRec9[2]));
		fVec1[0] = fTemp10;
		fRec8[0] = (0.0f - (fConst9 * ((fConst10 * fRec8[1]) - (fConst16 * (fTemp10 + fVec1[1])))));
		fRec7[0] = (fRec8[0] - (fConst75 * ((fConst76 * fRec7[2]) + (fConst77 * fRec7[1]))));
		float fTemp11 = (iSlow13 ? fTemp4 : (iSlow14 ? (fConst8 * (fRec7[2] + (fRec7[0] + (2.0f * fRec7[1])))) : fTemp4));
		float fTemp12 = (0.200000003f * fRec18[1]);
		float fTemp13 = (0.100000001f * fRec16[1]);
		float fTemp14 = ((0.400000006f * fRec20[1]) + fTemp13);
		float fTemp15 = ((fTemp12 + (fTemp11 + (0.600000024f * fRec22[1]))) - fTemp14);
		fRec22[0] = fTemp15;
		float fRec23 = (0.0f - (0.600000024f * fTemp15));
		fRec20[0] = (fRec23 + fRec22[1]);
		float fTemp16 = (fTemp11 + fTemp12);
		float fRec21 = (0.400000006f * (fTemp16 - fTemp14));
		fRec18[0] = (fRec21 + fRec20[1]);
		float fRec19 = (0.0f - (0.200000003f * (fTemp16 - fTemp13)));
		fRec16[0] = (fRec19 + fRec18[1]);
		float fRec17 = (0.100000001f * (fTemp11 - fTemp13));
		float fTemp17 = (iSlow10 ? fTemp11 : (iSlow11 ? (fRec17 + fRec16[1]) : fTemp11));
		float fTemp18 = (0.300000012f * fRec28[1]);
		float fTemp19 = (0.5f * fRec24[1]);
		float fTemp20 = ((0.400000006f * fRec26[1]) + fTemp19);
		float fTemp21 = ((fTemp18 + (fTemp17 + (0.200000003f * fRec30[1]))) - fTemp20);
		fRec30[0] = fTemp21;
		float fRec31 = (0.0f - (0.200000003f * fTemp21));
		fRec28[0] = (fRec31 + fRec30[1]);
		float fRec29 = (0.0f - (0.300000012f * ((fTemp17 + fTemp18) - fTemp20)));
		fRec26[0] = (fRec29 + fRec28[1]);
		float fRec27 = (0.400000006f * (fTemp17 - fTemp20));
		fRec24[0] = (fRec27 + fRec26[1]);
		float fRec25 = (0.5f * (fTemp17 - fTemp19));
		float fTemp22 = ((iSlow2 ? fRec0[1] : (iSlow7 ? fTemp17 : (iSlow8 ? (fRec25 + fRec24[1]) : fTemp17))) + (fSlow31 * fTemp0));
		fVec2[(IOTA & 1048575)] = fTemp22;
		int iTemp23 = int(std::min<float>(524288.0f, std::max<float>(0.0f, fRec3[0])));
		int iTemp24 = int(std::min<float>(524288.0f, std::max<float>(0.0f, fRec4[0])));
		float fTemp25 = ((fTemp2 * fVec2[((IOTA - iTemp23) & 1048575)]) + (fRec2[0] * fVec2[((IOTA - iTemp24) & 1048575)]));
		fRec0[0] = (iSlow2 ? fTemp25 : (fSlow3 * fTemp25));
		output0[i] = FAUSTFLOAT((fTemp0 + (fSlow0 * fRec0[0])));
		float fTemp26 = float(input1[i]);
		fRec34[0] = ((fSlow24 * fRec32[1]) - (fSlow21 * ((fSlow25 * fRec34[2]) + (fSlow26 * fRec34[1]))));
		fRec33[0] = ((fSlow21 * (((fSlow23 * fRec34[0]) + (fSlow27 * fRec34[1])) + (fSlow23 * fRec34[2]))) - (fSlow18 * ((fSlow28 * fRec33[2]) + (fSlow29 * fRec33[1]))));
		float fTemp27 = (fRec33[2] + (fRec33[0] + (2.0f * fRec33[1])));
		float fTemp28 = (fSlow18 * fTemp27);
		fVec3[0] = fTemp28;
		fRec43[0] = ((fConst49 * fVec3[1]) - (fConst50 * ((fConst51 * fRec43[1]) - (fSlow30 * fTemp27))));
		fRec42[0] = (fRec43[0] - (fConst45 * ((fConst52 * fRec42[2]) + (fConst53 * fRec42[1]))));
		float fTemp29 = (fConst42 * fRec41[1]);
		fRec41[0] = ((fConst45 * (((fConst47 * fRec42[0]) + (fConst54 * fRec42[1])) + (fConst47 * fRec42[2]))) - (fConst41 * ((fConst55 * fRec41[2]) + fTemp29)));
		float fTemp30 = (fConst36 * fRec40[1]);
		fRec40[0] = ((fConst41 * ((fTemp29 + (fConst57 * fRec41[0])) + (fConst58 * fRec41[2]))) - (fConst35 * ((fConst59 * fRec40[2]) + fTemp30)));
		float fTemp31 = (fConst30 * fRec39[1]);
		fRec39[0] = ((fConst35 * ((fTemp30 + (fConst61 * fRec40[0])) + (fConst62 * fRec40[2]))) - (fConst29 * ((fConst63 * fRec39[2]) + fTemp31)));
		float fTemp32 = (fConst24 * fRec38[1]);
		fRec38[0] = ((fConst29 * ((fTemp31 + (fConst65 * fRec39[0])) + (fConst66 * fRec39[2]))) - (fConst23 * ((fConst67 * fRec38[2]) + fTemp32)));
		float fTemp33 = (fConst17 * fRec37[1]);
		fRec37[0] = ((fConst23 * ((fTemp32 + (fConst69 * fRec38[0])) + (fConst70 * fRec38[2]))) - (fConst16 * ((fConst71 * fRec37[2]) + fTemp33)));
		float fTemp34 = ((fTemp33 + (fConst73 * fRec37[0])) + (fConst74 * fRec37[2]));
		fVec4[0] = fTemp34;
		fRec36[0] = (0.0f - (fConst9 * ((fConst10 * fRec36[1]) - (fConst16 * (fTemp34 + fVec4[1])))));
		fRec35[0] = (fRec36[0] - (fConst75 * ((fConst76 * fRec35[2]) + (fConst77 * fRec35[1]))));
		float fTemp35 = (iSlow13 ? fTemp28 : (iSlow14 ? (fConst8 * (fRec35[2] + (fRec35[0] + (2.0f * fRec35[1])))) : fTemp28));
		float fTemp36 = (0.200000003f * fRec46[1]);
		float fTemp37 = (0.100000001f * fRec44[1]);
		float fTemp38 = ((0.400000006f * fRec48[1]) + fTemp37);
		float fTemp39 = ((fTemp36 + (fTemp35 + (0.600000024f * fRec50[1]))) - fTemp38);
		fRec50[0] = fTemp39;
		float fRec51 = (0.0f - (0.600000024f * fTemp39));
		fRec48[0] = (fRec51 + fRec50[1]);
		float fTemp40 = (fTemp35 + fTemp36);
		float fRec49 = (0.400000006f * (fTemp40 - fTemp38));
		fRec46[0] = (fRec49 + fRec48[1]);
		float fRec47 = (0.0f - (0.200000003f * (fTemp40 - fTemp37)));
		fRec44[0] = (fRec47 + fRec46[1]);
		float fRec45 = (0.100000001f * (fTemp35 - fTemp37));
		float fTemp41 = (iSlow10 ? fTemp35 : (iSlow11 ? (fRec45 + fRec44[1]) : fTemp35));
		float fTemp42 = (0.300000012f * fRec56[1]);
		float fTemp43 = (0.5f * fRec52[1]);
		float fTemp44 = ((0.400000006f * fRec54[1]) + fTemp43);
		float fTemp45 = ((fTemp42 + (fTemp41 + (0.200000003f * fRec58[1]))) - fTemp44);
		fRec58[0] = fTemp45;
		float fRec59 = (0.0f - (0.200000003f * fTemp45));
		fRec56[0] = (fRec59 + fRec58[1]);
		float fRec57 = (0.0f - (0.300000012f * ((fTemp41 + fTemp42) - fTemp44)));
		fRec54[0] = (fRec57 + fRec56[1]);
		float fRec55 = (0.400000006f * (fTemp41 - fTemp44));
		fRec52[0] = (fRec55 + fRec54[1]);
		float fRec53 = (0.5f * (fTemp41 - fTemp43));
		float fTemp46 = ((iSlow2 ? fRec32[1] : (iSlow7 ? fTemp41 : (iSlow8 ? (fRec53 + fRec52[1]) : fTemp41))) + (fSlow31 * fTemp26));
		fVec5[(IOTA & 1048575)] = fTemp46;
		float fTemp47 = ((fTemp2 * fVec5[((IOTA - iTemp23) & 1048575)]) + (fRec2[0] * fVec5[((IOTA - iTemp24) & 1048575)]));
		fRec32[0] = (iSlow2 ? fTemp47 : (fSlow3 * fTemp47));
		output1[i] = FAUSTFLOAT((fTemp26 + (fSlow0 * fRec32[0])));
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fVec0[1] = fVec0[0];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fVec1[1] = fVec1[0];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec22[1] = fRec22[0];
		fRec20[1] = fRec20[0];
		fRec18[1] = fRec18[0];
		fRec16[1] = fRec16[0];
		fRec30[1] = fRec30[0];
		fRec28[1] = fRec28[0];
		fRec26[1] = fRec26[0];
		fRec24[1] = fRec24[0];
		IOTA = (IOTA + 1);
		fRec0[1] = fRec0[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fVec3[1] = fVec3[0];
		fRec43[1] = fRec43[0];
		fRec42[2] = fRec42[1];
		fRec42[1] = fRec42[0];
		fRec41[2] = fRec41[1];
		fRec41[1] = fRec41[0];
		fRec40[2] = fRec40[1];
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fVec4[1] = fVec4[0];
		fRec36[1] = fRec36[0];
		fRec35[2] = fRec35[1];
		fRec35[1] = fRec35[0];
		fRec50[1] = fRec50[0];
		fRec48[1] = fRec48[0];
		fRec46[1] = fRec46[0];
		fRec44[1] = fRec44[0];
		fRec58[1] = fRec58[0];
		fRec56[1] = fRec56[0];
		fRec54[1] = fRec54[0];
		fRec52[1] = fRec52[0];
		fRec32[1] = fRec32[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("didest.Freeze",N_("Freeze"),"B",N_("Freeze the current delay"),&fCheckbox0, 0.0, 0.0, 1.0, 1.0, 0);
	reg.registerFloatVar("didest.bpm",N_("BPM"),"S",N_("Delay in Beats per Minute"),&fHslider1, 120.0f, 24.0f, 360.0f, 1.0f, 0);
	reg.registerFloatVar("didest.feedback",N_("Feedback"),"S",N_("Percentage of the feedback level in the de.delay loop"),&fVslider2, 50.0f, 1.0f, 100.0f, 1.0f, 0);
	reg.registerFloatVar("didest.gain",N_("Gain"),"S",N_("Overall gain of the de.delay line in percent"),&fVslider0, 100.0f, 0.0f, 120.0f, 1.0f, 0);
	reg.registerFloatVar("didest.highpass",N_("Hipass"),"S",N_("Highpass filter frequency in the feddback loop"),&fHslider4, 120.0f, 20.0f, 20000.0f, 1.0f, 0);
	reg.registerFloatVar("didest.howpass",N_("Lopass"),"S",N_("Lowpass filter frequency in the feddback loop"),&fHslider3, 12000.0f, 20.0f, 20000.0f, 1.0f, 0);
	reg.registerFloatVar("didest.level",N_("Level"),"S",N_("Percentage of the de.delay gain level"),&fVslider1, 50.0f, 1.0f, 100.0f, 1.0f, 0);
	static const value_pair fHslider2_values[] = {{"plain"},{"presence"},{"tape"},{"tape2"},{0}};
	reg.registerFloatVar("didest.mode",N_("Mode"),"S","",&fHslider2, 0.0f, 0.0f, 3.0f, 1.0f, fHslider2_values);
	static const value_pair fHslider0_values[] = {{"Dotted 1/2 note"},{"1/2 note"},{"1/2 note triplets"},{" Dotted 1/4 note"},{"1/4 note"},{"1/4 note triplets"},{"Dotted 1/8 note"},{"1/8 note"},{"1/8 note triplets"},{" Dotted 1/16 note"},{"1/16 note"},{"1/16 note triplets"},{"Dotted 1/32 note"},{"1/32 note"},{"1/32 note triplets"},{" Dotted 1/64 note"},{"1/64 note"},{"1/64 note triplets"},{0}};
	reg.registerFloatVar("didest.notes",N_("Notes"),"S",N_("Note setting for bpm"),&fHslider0, 4.0f, 0.0f, 17.0f, 1.0f, fHslider0_values);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!-- Generated with glade 3.22.1 -->\n\
<interface>\n\
  <requires lib=\"gtk+\" version=\"3.20\"/>\n\
  <requires lib=\"gxwidgets\" version=\"0.0\"/>\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can_focus\">False</property>\n\
    <child>\n\
      <placeholder/>\n\
    </child>\n\
    <child>\n\
      <object class=\"GtkBox\" id=\"vbox1\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can_focus\">False</property>\n\
        <property name=\"orientation\">vertical</property>\n\
        <child>\n\
          <object class=\"GtkBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <child>\n\
              <object class=\"GtkBox\" id=\"vbox2\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"orientation\">vertical</property>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label1:rack_label\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"label\" translatable=\"yes\">label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxMidKnob\" id=\"GxMidKnob1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">didest.bpm</property>\n\
                    <property name=\"label_ref\">label1:rack_label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">3</property>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">True</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
            <child>\n\
              <object class=\"GtkBox\" id=\"vbox8\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"halign\">center</property>\n\
                <property name=\"margin_bottom\">4</property>\n\
                <property name=\"orientation\">vertical</property>\n\
                <property name=\"spacing\">10</property>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"hbox1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"spacing\">4</property>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"vbox3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"orientation\">vertical</property>\n\
                        <child>\n\
                          <object class=\"GtkLabel\" id=\"label2:rack_label\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"label\" translatable=\"yes\">label</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">False</property>\n\
                            <property name=\"fill\">False</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxSmallKnobR\" id=\"GxMidKnob2\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">didest.feedback</property>\n\
                            <property name=\"label_ref\">label2:rack_label</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">False</property>\n\
                            <property name=\"fill\">False</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"vbox4\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"orientation\">vertical</property>\n\
                        <child>\n\
                          <object class=\"GtkLabel\" id=\"label3:rack_label\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"label\" translatable=\"yes\">label</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">False</property>\n\
                            <property name=\"fill\">False</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxSmallKnobR\" id=\"GxMidKnob3\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">didest.level</property>\n\
                            <property name=\"label_ref\">label3:rack_label</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">False</property>\n\
                            <property name=\"fill\">False</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"vbox5\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"orientation\">vertical</property>\n\
                        <child>\n\
                          <object class=\"GtkLabel\" id=\"label4:rack_label\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"label\" translatable=\"yes\">label</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">False</property>\n\
                            <property name=\"fill\">False</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxSmallKnobR\" id=\"GxMidKnob4\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">didest.highpass</property>\n\
                            <property name=\"label_ref\">label4:rack_label</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">False</property>\n\
                            <property name=\"fill\">False</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">2</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"vbox6\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"orientation\">vertical</property>\n\
                        <child>\n\
                          <object class=\"GtkLabel\" id=\"label5:rack_label\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"label\" translatable=\"yes\">label</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">False</property>\n\
                            <property name=\"fill\">False</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxSmallKnobR\" id=\"GxMidKnob5\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">didest.howpass</property>\n\
                            <property name=\"label_ref\">label5:rack_label</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">False</property>\n\
                            <property name=\"fill\">False</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">3</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkGrid\" id=\"table1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"margin_left\">8</property>\n\
                    <property name=\"margin_right\">8</property>\n\
                    <property name=\"row_spacing\">3</property>\n\
                    <property name=\"column_spacing\">6</property>\n\
                    <child>\n\
                      <object class=\"GxSelector\" id=\"gxselector2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"hexpand\">True</property>\n\
                        <property name=\"var_id\">didest.mode</property>\n\
                        <property name=\"label_ref\">label21:rack_label_inverse</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"left_attach\">1</property>\n\
                        <property name=\"top_attach\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label11:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                        <property name=\"xalign\">1</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"left_attach\">0</property>\n\
                        <property name=\"top_attach\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label21:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                        <property name=\"xalign\">1</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"left_attach\">0</property>\n\
                        <property name=\"top_attach\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSelector\" id=\"gxselector1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"hexpand\">True</property>\n\
                        <property name=\"var_id\">didest.notes</property>\n\
                        <property name=\"label_ref\">label11:rack_label_inverse</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"left_attach\">1</property>\n\
                        <property name=\"top_attach\">0</property>\n\
                        <property name=\"width\">3</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label31:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                        <property name=\"xalign\">1</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"left_attach\">2</property>\n\
                        <property name=\"top_attach\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSwitch\" id=\"gxswitch1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"use_stock\">True</property>\n\
                        <property name=\"draw_indicator\">True</property>\n\
                        <property name=\"var_id\">didest.Freeze</property>\n\
                        <property name=\"base_name\">frbutton</property>\n\
                        <property name=\"label_ref\">label31:rack_label_inverse</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"left_attach\">3</property>\n\
                        <property name=\"top_attach\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">True</property>\n\
                <property name=\"position\">1</property>\n\
              </packing>\n\
            </child>\n\
            <child>\n\
              <object class=\"GtkBox\" id=\"vbox7\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"orientation\">vertical</property>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label6:rack_label1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label6:rack_label\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"label\" translatable=\"yes\">label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxMidKnob\" id=\"GxMidKnob6\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">didest.gain</property>\n\
                    <property name=\"label_ref\">label6:rack_label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label6:rack_label2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">3</property>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">True</property>\n\
                <property name=\"position\">2</property>\n\
              </packing>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">False</property>\n\
            <property name=\"position\">0</property>\n\
          </packing>\n\
        </child>\n\
        <child>\n\
          <object class=\"GtkBox\" id=\"minibox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GxHSlider\" id=\"gxhslider1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">True</property>\n\
                <property name=\"receives_default\">True</property>\n\
                <property name=\"round_digits\">0</property>\n\
                <property name=\"var_id\">didest.gain</property>\n\
                <property name=\"show_value\">False</property>\n\
                <property name=\"value_position\">right</property>\n\
                <property name=\"value_xalign\">0.52000000000000002</property>\n\
                <property name=\"label_ref\">label0:rack_label</property>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">False</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
            <child>\n\
              <object class=\"GtkLabel\" id=\"label0:rack_label\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"label\" translatable=\"yes\">Amount</property>\n\
                <property name=\"xalign\">0</property>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">False</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"position\">1</property>\n\
              </packing>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">True</property>\n\
            <property name=\"position\">1</property>\n\
          </packing>\n\
        </child>\n\
      </object>\n\
    </child>\n\
  </object>\n\
</interface>\n\
";

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade(glade_def);
        return 0;
    }
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("didest" "." p)
// -----delay
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("bpm"), _(" delay (bpm)"));
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalBox("");
    {
	b.openVerticalBox("");
        {
            b.create_selector(PARAM("notes"), "tact");
            b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_TOP);
            b.create_small_rackknob(PARAM("bpm"), _(" delay (bpm)"));
        }
        b.closeBox();
	b.openVerticalBox("");
        {
            b.openHorizontalBox("");
            b.openFrameBox("");
            b.closeBox();
            b.create_selector(PARAM("mode"), "mode");
            b.closeBox();
            b.openHorizontalBox("");
            {
                b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_TOP);
                b.create_small_rackknob(PARAM("highpass"), _("highpass (hz)"));
                b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_TOP);
                b.create_small_rackknob(PARAM("howpass"), _("lowpass (hz)"));
            }
            b.closeBox();
        }
        b.closeBox();
        b.openVerticalBox("");
        {
            b.create_small_rackknob(PARAM("level"), _("level"));
            b.create_small_rackknob(PARAM("feedback"), _("feedback"));
        }
        b.closeBox();
        b.openVerticalBox("");
        {
            b.create_small_rackknobr(PARAM("gain"), _("amount"));
            b.openFrameBox("");
            b.closeBox();
            b.create_switch(sw_frbutton,PARAM("Freeze"), _("freeze"));
        }
        b.closeBox();
    }
    b.closeBox();
}
b.closeBox();

#undef PARAM
        return 0;
    }
	return -1;
}

int Dsp::load_ui_f_static(const UiBuilder& b, int form)
{
	return static_cast<Dsp*>(b.plugin)->load_ui_f(b, form);
}
PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace digital_delay_st
