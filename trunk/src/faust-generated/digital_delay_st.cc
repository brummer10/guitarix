// generated from file '../src/faust/digital_delay_st.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "beat.h"

namespace digital_delay_st {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fHslider0;
	float fConst1;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fVslider2;
	float fRec2[3];
	float fRec1[3];
	float fVec0[2];
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst13;
	float fConst14;
	float fConst20;
	float fConst21;
	float fConst26;
	float fConst27;
	float fConst32;
	float fConst33;
	float fConst38;
	float fConst39;
	float fConst41;
	float fConst42;
	float fConst44;
	float fConst46;
	float fConst47;
	float fConst48;
	float fRec11[2];
	float fConst49;
	float fConst50;
	float fRec10[3];
	float fConst51;
	float fConst52;
	float fRec9[3];
	float fConst54;
	float fConst55;
	float fConst56;
	float fRec8[3];
	float fConst58;
	float fConst59;
	float fConst60;
	float fRec7[3];
	float fConst62;
	float fConst63;
	float fConst64;
	float fRec6[3];
	float fConst66;
	float fConst67;
	float fConst68;
	float fRec5[3];
	float fConst70;
	float fConst71;
	float fVec1[2];
	float fRec4[2];
	float fConst72;
	float fConst73;
	float fConst74;
	float fRec3[3];
	float fRec18[2];
	float fRec16[2];
	float fRec14[2];
	float fRec12[2];
	float fRec26[2];
	float fRec24[2];
	float fRec22[2];
	float fRec20[2];
	int IOTA;
	float *fVec2;
	FAUSTFLOAT fHslider3;
	float fConst75;
	FAUSTFLOAT fHslider4;
	float fConst76;
	float fConst77;
	float fRec28[2];
	float fRec29[2];
	float fRec30[2];
	float fRec31[2];
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
	for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) fRec2[l0] = 0.0f;
	for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) fRec1[l1] = 0.0f;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fVec0[l2] = 0.0f;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec11[l3] = 0.0f;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec10[l4] = 0.0f;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec9[l5] = 0.0f;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec8[l6] = 0.0f;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRec7[l7] = 0.0f;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec6[l8] = 0.0f;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec5[l9] = 0.0f;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fVec1[l10] = 0.0f;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec4[l11] = 0.0f;
	for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) fRec3[l12] = 0.0f;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec18[l13] = 0.0f;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec16[l14] = 0.0f;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec14[l15] = 0.0f;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec12[l16] = 0.0f;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec26[l17] = 0.0f;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec24[l18] = 0.0f;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec22[l19] = 0.0f;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fRec20[l20] = 0.0f;
	for (int l21 = 0; (l21 < 1048576); l21 = (l21 + 1)) fVec2[l21] = 0.0f;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fRec28[l22] = 0.0f;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fRec29[l23] = 0.0f;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fRec30[l24] = 0.0f;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fRec31[l25] = 0.0f;
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
	float fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
	fConst1 = (3.14159274f / fConst0);
	float fConst2 = std::tan((37699.1133f / fConst0));
	float fConst3 = (1.0f / fConst2);
	float fConst4 = (((fConst3 + 1.0f) / fConst2) + 1.0f);
	fConst5 = (0.800000012f / fConst4);
	fConst6 = (1.0f / (fConst3 + 1.0f));
	fConst7 = (1.0f - fConst3);
	float fConst8 = (25132.7422f / fConst0);
	float fConst9 = std::tan(fConst8);
	float fConst10 = (1.0f / fConst9);
	float fConst11 = (fConst0 * std::sin((50265.4844f / fConst0)));
	float fConst12 = (3141.59277f / fConst11);
	fConst13 = (1.0f / (((fConst10 + fConst12) / fConst9) + 1.0f));
	fConst14 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst9))));
	float fConst15 = (12566.3711f / fConst0);
	float fConst16 = std::tan(fConst15);
	float fConst17 = (1.0f / fConst16);
	float fConst18 = (fConst0 * std::sin(fConst8));
	float fConst19 = (6268.30127f / fConst18);
	fConst20 = (1.0f / (((fConst17 + fConst19) / fConst16) + 1.0f));
	fConst21 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst16))));
	float fConst22 = std::tan((6283.18555f / fConst0));
	float fConst23 = (1.0f / fConst22);
	float fConst24 = (fConst0 * std::sin(fConst15));
	float fConst25 = (1570.79639f / fConst24);
	fConst26 = (1.0f / (((fConst23 + fConst25) / fConst22) + 1.0f));
	fConst27 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst22))));
	float fConst28 = std::tan((1178.09729f / fConst0));
	float fConst29 = (1.0f / fConst28);
	float fConst30 = (fConst0 * std::sin((2356.19458f / fConst0)));
	float fConst31 = (392.699097f / fConst30);
	fConst32 = (1.0f / (((fConst29 + fConst31) / fConst28) + 1.0f));
	fConst33 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst28))));
	float fConst34 = std::tan((628.318542f / fConst0));
	float fConst35 = (1.0f / fConst34);
	float fConst36 = (fConst0 * std::sin((1256.63708f / fConst0)));
	float fConst37 = (221.880875f / fConst36);
	fConst38 = (1.0f / (((fConst35 + fConst37) / fConst34) + 1.0f));
	fConst39 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst34))));
	float fConst40 = std::tan((251.327408f / fConst0));
	fConst41 = (1.0f / fConst40);
	fConst42 = (1.0f / (((fConst41 + 1.0f) / fConst40) + 1.0f));
	float fConst43 = mydsp_faustpower2_f(fConst40);
	fConst44 = (1.0f / fConst43);
	float fConst45 = (fConst41 + 1.0f);
	fConst46 = (0.0f - (1.0f / (fConst40 * fConst45)));
	fConst47 = (1.0f / fConst45);
	fConst48 = (1.0f - fConst41);
	fConst49 = (((fConst41 + -1.0f) / fConst40) + 1.0f);
	fConst50 = (2.0f * (1.0f - fConst44));
	fConst51 = (0.0f - (2.0f / fConst43));
	fConst52 = (((fConst35 - fConst37) / fConst34) + 1.0f);
	float fConst53 = (157.079636f / fConst36);
	fConst54 = (((fConst35 + fConst53) / fConst34) + 1.0f);
	fConst55 = (((fConst35 - fConst53) / fConst34) + 1.0f);
	fConst56 = (((fConst29 - fConst31) / fConst28) + 1.0f);
	float fConst57 = (466.723724f / fConst30);
	fConst58 = (((fConst29 + fConst57) / fConst28) + 1.0f);
	fConst59 = (((fConst29 - fConst57) / fConst28) + 1.0f);
	fConst60 = (((fConst23 - fConst25) / fConst22) + 1.0f);
	float fConst61 = (2218.80884f / fConst24);
	fConst62 = (((fConst23 + fConst61) / fConst22) + 1.0f);
	fConst63 = (((fConst23 - fConst61) / fConst22) + 1.0f);
	fConst64 = (((fConst17 - fConst19) / fConst16) + 1.0f);
	float fConst65 = (3141.59277f / fConst18);
	fConst66 = (((fConst17 + fConst65) / fConst16) + 1.0f);
	fConst67 = (((fConst17 - fConst65) / fConst16) + 1.0f);
	fConst68 = (((fConst10 - fConst12) / fConst9) + 1.0f);
	float fConst69 = (3955.03076f / fConst11);
	fConst70 = (((fConst10 + fConst69) / fConst9) + 1.0f);
	fConst71 = (((fConst10 - fConst69) / fConst9) + 1.0f);
	fConst72 = (1.0f / fConst4);
	fConst73 = (((fConst3 + -1.0f) / fConst2) + 1.0f);
	fConst74 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst2))));
	fConst75 = (60.0f * fConst0);
	fConst76 = (10.0f / fConst0);
	fConst77 = (0.0f - fConst76);
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
	float fSlow4 = float(fHslider0);
	int iSlow5 = int(std::min<float>(2.0f, std::max<float>(0.0f, (fSlow4 + -2.0f))));
	int iSlow6 = (iSlow5 == 0);
	int iSlow7 = (iSlow5 == 1);
	int iSlow8 = int(std::min<float>(2.0f, std::max<float>(0.0f, (fSlow4 + -1.0f))));
	int iSlow9 = (iSlow8 == 0);
	int iSlow10 = (iSlow8 == 1);
	int iSlow11 = int(std::min<float>(2.0f, std::max<float>(0.0f, fSlow4)));
	int iSlow12 = (iSlow11 == 0);
	int iSlow13 = (iSlow11 == 1);
	float fSlow14 = std::tan((fConst1 * float(fHslider1)));
	float fSlow15 = (1.0f / fSlow14);
	float fSlow16 = (((fSlow15 + 1.41421354f) / fSlow14) + 1.0f);
	float fSlow17 = (1.0f / fSlow16);
	float fSlow18 = std::tan((fConst1 * float(fHslider2)));
	float fSlow19 = (1.0f / fSlow18);
	float fSlow20 = (1.0f / (((fSlow19 + 1.41421354f) / fSlow18) + 1.0f));
	float fSlow21 = mydsp_faustpower2_f(fSlow18);
	float fSlow22 = (1.0f / fSlow21);
	float fSlow23 = (0.00999999978f * float(fVslider2));
	float fSlow24 = (((fSlow19 + -1.41421354f) / fSlow18) + 1.0f);
	float fSlow25 = (2.0f * (1.0f - fSlow22));
	float fSlow26 = (0.0f - (2.0f / fSlow21));
	float fSlow27 = (((fSlow15 + -1.41421354f) / fSlow14) + 1.0f);
	float fSlow28 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow14))));
	float fSlow29 = (fConst41 / fSlow16);
	float fSlow30 = (1.0f - fSlow1);
	float fSlow31 = std::min<float>(524288.0f, float(B2N(int(float(fHslider3)), float((fConst75 / float(fHslider4))))));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		float fTemp0 = float(input0[i0]);
		fRec2[0] = ((fSlow23 * fRec0[1]) - (fSlow20 * ((fSlow24 * fRec2[2]) + (fSlow25 * fRec2[1]))));
		fRec1[0] = ((fSlow20 * (((fSlow22 * fRec2[0]) + (fSlow26 * fRec2[1])) + (fSlow22 * fRec2[2]))) - (fSlow17 * ((fSlow27 * fRec1[2]) + (fSlow28 * fRec1[1]))));
		float fTemp1 = (fRec1[2] + (fRec1[0] + (2.0f * fRec1[1])));
		float fTemp2 = (fSlow17 * fTemp1);
		fVec0[0] = fTemp2;
		fRec11[0] = ((fConst46 * fVec0[1]) - (fConst47 * ((fConst48 * fRec11[1]) - (fSlow29 * fTemp1))));
		fRec10[0] = (fRec11[0] - (fConst42 * ((fConst49 * fRec10[2]) + (fConst50 * fRec10[1]))));
		float fTemp3 = (fConst39 * fRec9[1]);
		fRec9[0] = ((fConst42 * (((fConst44 * fRec10[0]) + (fConst51 * fRec10[1])) + (fConst44 * fRec10[2]))) - (fConst38 * ((fConst52 * fRec9[2]) + fTemp3)));
		float fTemp4 = (fConst33 * fRec8[1]);
		fRec8[0] = ((fConst38 * ((fTemp3 + (fConst54 * fRec9[0])) + (fConst55 * fRec9[2]))) - (fConst32 * ((fConst56 * fRec8[2]) + fTemp4)));
		float fTemp5 = (fConst27 * fRec7[1]);
		fRec7[0] = ((fConst32 * ((fTemp4 + (fConst58 * fRec8[0])) + (fConst59 * fRec8[2]))) - (fConst26 * ((fConst60 * fRec7[2]) + fTemp5)));
		float fTemp6 = (fConst21 * fRec6[1]);
		fRec6[0] = ((fConst26 * ((fTemp5 + (fConst62 * fRec7[0])) + (fConst63 * fRec7[2]))) - (fConst20 * ((fConst64 * fRec6[2]) + fTemp6)));
		float fTemp7 = (fConst14 * fRec5[1]);
		fRec5[0] = ((fConst20 * ((fTemp6 + (fConst66 * fRec6[0])) + (fConst67 * fRec6[2]))) - (fConst13 * ((fConst68 * fRec5[2]) + fTemp7)));
		float fTemp8 = ((fTemp7 + (fConst70 * fRec5[0])) + (fConst71 * fRec5[2]));
		fVec1[0] = fTemp8;
		fRec4[0] = (0.0f - (fConst6 * ((fConst7 * fRec4[1]) - (fConst13 * (fTemp8 + fVec1[1])))));
		fRec3[0] = (fRec4[0] - (fConst72 * ((fConst73 * fRec3[2]) + (fConst74 * fRec3[1]))));
		float fElse0 = (fConst5 * (fRec3[2] + (fRec3[0] + (2.0f * fRec3[1]))));
		float fThen1 = (iSlow13 ? fElse0 : fTemp2);
		float fTemp9 = (iSlow12 ? fTemp2 : fThen1);
		float fTemp10 = (0.200000003f * fRec14[1]);
		float fTemp11 = (0.100000001f * fRec12[1]);
		float fTemp12 = ((0.400000006f * fRec16[1]) + fTemp11);
		float fTemp13 = ((fTemp10 + (fTemp9 + (0.600000024f * fRec18[1]))) - fTemp12);
		fRec18[0] = fTemp13;
		float fRec19 = (0.0f - (0.600000024f * fTemp13));
		fRec16[0] = (fRec19 + fRec18[1]);
		float fTemp14 = (fTemp9 + fTemp10);
		float fRec17 = (0.400000006f * (fTemp14 - fTemp12));
		fRec14[0] = (fRec17 + fRec16[1]);
		float fRec15 = (0.0f - (0.200000003f * (fTemp14 - fTemp11)));
		fRec12[0] = (fRec15 + fRec14[1]);
		float fRec13 = (0.100000001f * (fTemp9 - fTemp11));
		float fElse2 = (fRec13 + fRec12[1]);
		float fThen3 = (iSlow10 ? fElse2 : fTemp9);
		float fTemp15 = (iSlow9 ? fTemp9 : fThen3);
		float fTemp16 = (0.300000012f * fRec24[1]);
		float fTemp17 = (0.5f * fRec20[1]);
		float fTemp18 = ((0.400000006f * fRec22[1]) + fTemp17);
		float fTemp19 = ((fTemp16 + (fTemp15 + (0.200000003f * fRec26[1]))) - fTemp18);
		fRec26[0] = fTemp19;
		float fRec27 = (0.0f - (0.200000003f * fTemp19));
		fRec24[0] = (fRec27 + fRec26[1]);
		float fRec25 = (0.0f - (0.300000012f * ((fTemp15 + fTemp16) - fTemp18)));
		fRec22[0] = (fRec25 + fRec24[1]);
		float fRec23 = (0.400000006f * (fTemp15 - fTemp18));
		fRec20[0] = (fRec23 + fRec22[1]);
		float fRec21 = (0.5f * (fTemp15 - fTemp17));
		float fElse4 = (fRec21 + fRec20[1]);
		float fThen5 = (iSlow7 ? fElse4 : fTemp15);
		float fThen6 = (iSlow6 ? fTemp15 : fThen5);
		float fTemp20 = ((iSlow2 ? fRec0[1] : fThen6) + (fSlow30 * fTemp0));
		fVec2[(IOTA & 1048575)] = fTemp20;
		float fThen8 = (((fRec29[1] == 1.0f) & (fSlow31 != fRec31[1])) ? fConst77 : 0.0f);
		float fThen10 = (((fRec29[1] == 0.0f) & (fSlow31 != fRec30[1])) ? fConst76 : fThen8);
		float fElse10 = (((fRec29[1] > 0.0f) & (fRec29[1] < 1.0f)) ? fRec28[1] : 0.0f);
		float fTemp21 = ((fRec28[1] != 0.0f) ? fElse10 : fThen10);
		fRec28[0] = fTemp21;
		fRec29[0] = std::max<float>(0.0f, std::min<float>(1.0f, (fRec29[1] + fTemp21)));
		fRec30[0] = (((fRec29[1] >= 1.0f) & (fRec31[1] != fSlow31)) ? fSlow31 : fRec30[1]);
		fRec31[0] = (((fRec29[1] <= 0.0f) & (fRec30[1] != fSlow31)) ? fSlow31 : fRec31[1]);
		int iTemp22 = int(std::min<float>(524288.0f, std::max<float>(0.0f, fRec30[0])));
		float fTemp23 = fVec2[((IOTA - iTemp22) & 1048575)];
		int iTemp24 = int(std::min<float>(524288.0f, std::max<float>(0.0f, fRec31[0])));
		float fTemp25 = (fTemp23 + (fRec29[0] * (fVec2[((IOTA - iTemp24) & 1048575)] - fTemp23)));
		float fThen13 = (fSlow3 * fTemp25);
		fRec0[0] = (iSlow2 ? fTemp25 : fThen13);
		output0[i0] = FAUSTFLOAT((fTemp0 + (fSlow0 * fRec0[0])));
		float fTemp26 = float(input1[i0]);
		fRec34[0] = ((fSlow23 * fRec32[1]) - (fSlow20 * ((fSlow24 * fRec34[2]) + (fSlow25 * fRec34[1]))));
		fRec33[0] = ((fSlow20 * (((fSlow22 * fRec34[0]) + (fSlow26 * fRec34[1])) + (fSlow22 * fRec34[2]))) - (fSlow17 * ((fSlow27 * fRec33[2]) + (fSlow28 * fRec33[1]))));
		float fTemp27 = (fRec33[2] + (fRec33[0] + (2.0f * fRec33[1])));
		float fTemp28 = (fSlow17 * fTemp27);
		fVec3[0] = fTemp28;
		fRec43[0] = ((fConst46 * fVec3[1]) - (fConst47 * ((fConst48 * fRec43[1]) - (fSlow29 * fTemp27))));
		fRec42[0] = (fRec43[0] - (fConst42 * ((fConst49 * fRec42[2]) + (fConst50 * fRec42[1]))));
		float fTemp29 = (fConst39 * fRec41[1]);
		fRec41[0] = ((fConst42 * (((fConst44 * fRec42[0]) + (fConst51 * fRec42[1])) + (fConst44 * fRec42[2]))) - (fConst38 * ((fConst52 * fRec41[2]) + fTemp29)));
		float fTemp30 = (fConst33 * fRec40[1]);
		fRec40[0] = ((fConst38 * ((fTemp29 + (fConst54 * fRec41[0])) + (fConst55 * fRec41[2]))) - (fConst32 * ((fConst56 * fRec40[2]) + fTemp30)));
		float fTemp31 = (fConst27 * fRec39[1]);
		fRec39[0] = ((fConst32 * ((fTemp30 + (fConst58 * fRec40[0])) + (fConst59 * fRec40[2]))) - (fConst26 * ((fConst60 * fRec39[2]) + fTemp31)));
		float fTemp32 = (fConst21 * fRec38[1]);
		fRec38[0] = ((fConst26 * ((fTemp31 + (fConst62 * fRec39[0])) + (fConst63 * fRec39[2]))) - (fConst20 * ((fConst64 * fRec38[2]) + fTemp32)));
		float fTemp33 = (fConst14 * fRec37[1]);
		fRec37[0] = ((fConst20 * ((fTemp32 + (fConst66 * fRec38[0])) + (fConst67 * fRec38[2]))) - (fConst13 * ((fConst68 * fRec37[2]) + fTemp33)));
		float fTemp34 = ((fTemp33 + (fConst70 * fRec37[0])) + (fConst71 * fRec37[2]));
		fVec4[0] = fTemp34;
		fRec36[0] = (0.0f - (fConst6 * ((fConst7 * fRec36[1]) - (fConst13 * (fTemp34 + fVec4[1])))));
		fRec35[0] = (fRec36[0] - (fConst72 * ((fConst73 * fRec35[2]) + (fConst74 * fRec35[1]))));
		float fElse14 = (fConst5 * (fRec35[2] + (fRec35[0] + (2.0f * fRec35[1]))));
		float fThen15 = (iSlow13 ? fElse14 : fTemp28);
		float fTemp35 = (iSlow12 ? fTemp28 : fThen15);
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
		float fElse16 = (fRec45 + fRec44[1]);
		float fThen17 = (iSlow10 ? fElse16 : fTemp35);
		float fTemp41 = (iSlow9 ? fTemp35 : fThen17);
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
		float fElse18 = (fRec53 + fRec52[1]);
		float fThen19 = (iSlow7 ? fElse18 : fTemp41);
		float fThen20 = (iSlow6 ? fTemp41 : fThen19);
		float fTemp46 = ((iSlow2 ? fRec32[1] : fThen20) + (fSlow30 * fTemp26));
		fVec5[(IOTA & 1048575)] = fTemp46;
		float fTemp47 = fVec5[((IOTA - iTemp22) & 1048575)];
		float fTemp48 = (fTemp47 + (fRec29[0] * (fVec5[((IOTA - iTemp24) & 1048575)] - fTemp47)));
		float fThen21 = (fSlow3 * fTemp48);
		fRec32[0] = (iSlow2 ? fTemp48 : fThen21);
		output1[i0] = FAUSTFLOAT((fTemp26 + (fSlow0 * fRec32[0])));
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
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
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fVec1[1] = fVec1[0];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec18[1] = fRec18[0];
		fRec16[1] = fRec16[0];
		fRec14[1] = fRec14[0];
		fRec12[1] = fRec12[0];
		fRec26[1] = fRec26[0];
		fRec24[1] = fRec24[0];
		fRec22[1] = fRec22[0];
		fRec20[1] = fRec20[0];
		IOTA = (IOTA + 1);
		fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
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
	reg.registerFloatVar("didest.bpm",N_("BPM"),"S",N_("Delay in Beats per Minute"),&fHslider4, 120.0f, 24.0f, 360.0f, 1.0f, 0);
	reg.registerFloatVar("didest.feedback",N_("Feedback"),"S",N_("Percentage of the feedback level in the de.delay loop"),&fVslider2, 50.0f, 1.0f, 100.0f, 1.0f, 0);
	reg.registerFloatVar("didest.gain",N_("Gain"),"S",N_("Overall gain of the de.delay line in percent"),&fVslider0, 100.0f, 0.0f, 120.0f, 1.0f, 0);
	reg.registerFloatVar("didest.highpass",N_("Hipass"),"S",N_("Highpass filter frequency in the feedback loop"),&fHslider2, 120.0f, 20.0f, 20000.0f, 1.0f, 0);
	reg.registerFloatVar("didest.howpass",N_("Lopass"),"S",N_("Lowpass filter frequency in the feedback loop"),&fHslider1, 12000.0f, 20.0f, 20000.0f, 1.0f, 0);
	reg.registerFloatVar("didest.level",N_("Level"),"S",N_("Percentage of the de.delay gain level"),&fVslider1, 50.0f, 1.0f, 100.0f, 1.0f, 0);
	static const value_pair fHslider0_values[] = {{"plain"},{"presence"},{"tape"},{"tape2"},{0}};
	reg.registerFloatVar("didest.mode",N_("Mode"),"S","",&fHslider0, 0.0f, 0.0f, 3.0f, 1.0f, fHslider0_values);
	static const value_pair fHslider3_values[] = {{"Dotted 1/2 note"},{"1/2 note"},{"1/2 note triplets"},{" Dotted 1/4 note"},{"1/4 note"},{"1/4 note triplets"},{"Dotted 1/8 note"},{"1/8 note"},{"1/8 note triplets"},{" Dotted 1/16 note"},{"1/16 note"},{"1/16 note triplets"},{"Dotted 1/32 note"},{"1/32 note"},{"1/32 note triplets"},{" Dotted 1/64 note"},{"1/64 note"},{"1/64 note triplets"},{0}};
	reg.registerFloatVar("didest.notes",N_("Notes"),"S",N_("Note setting for bpm"),&fHslider3, 4.0f, 0.0f, 17.0f, 1.0f, fHslider3_values);
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
