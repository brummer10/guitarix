// generated from file '../src/faust/digital_delay_st.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "beat.h"

namespace digital_delay_st {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fVslider0;
	float fRec2[3];
	float fRec1[3];
	float fVec0[2];
	float fConst2;
	float fConst3;
	float fConst4;
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
	float fConst52;
	float fConst53;
	float fRec11[2];
	float fRec10[3];
	float fConst54;
	float fRec9[3];
	float fConst55;
	float fConst56;
	float fConst57;
	float fRec8[3];
	float fConst58;
	float fConst59;
	float fConst60;
	float fRec7[3];
	float fConst61;
	float fConst62;
	float fConst63;
	float fRec6[3];
	float fConst64;
	float fConst65;
	float fConst66;
	float fRec5[3];
	float fConst67;
	float fConst68;
	float fConst69;
	float fVec1[2];
	float fConst70;
	float fConst71;
	float fRec4[2];
	float fRec3[3];
	float fConst72;
	float fRec18[2];
	float fRec16[2];
	float fRec14[2];
	float fRec12[2];
	float fRec26[2];
	float fRec24[2];
	float fRec22[2];
	float fRec20[2];
	int IOTA0;
	float *fVec2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	float fConst73;
	float fConst74;
	float fRec28[2];
	float fRec29[2];
	float fRec30[2];
	float fRec31[2];
	FAUSTFLOAT fVslider1;
	float fRec0[2];
	FAUSTFLOAT fVslider2;
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
	for (int l0 = 0; l0 < 3; l0 = l0 + 1) fRec2[l0] = 0.0f;
	for (int l1 = 0; l1 < 3; l1 = l1 + 1) fRec1[l1] = 0.0f;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fVec0[l2] = 0.0f;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec11[l3] = 0.0f;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRec10[l4] = 0.0f;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec9[l5] = 0.0f;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec8[l6] = 0.0f;
	for (int l7 = 0; l7 < 3; l7 = l7 + 1) fRec7[l7] = 0.0f;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec6[l8] = 0.0f;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec5[l9] = 0.0f;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fVec1[l10] = 0.0f;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec4[l11] = 0.0f;
	for (int l12 = 0; l12 < 3; l12 = l12 + 1) fRec3[l12] = 0.0f;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec18[l13] = 0.0f;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec16[l14] = 0.0f;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec14[l15] = 0.0f;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec12[l16] = 0.0f;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec26[l17] = 0.0f;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec24[l18] = 0.0f;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec22[l19] = 0.0f;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec20[l20] = 0.0f;
	for (int l21 = 0; l21 < 1048576; l21 = l21 + 1) fVec2[l21] = 0.0f;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec28[l22] = 0.0f;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec29[l23] = 0.0f;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec30[l24] = 0.0f;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec31[l25] = 0.0f;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec0[l26] = 0.0f;
	for (int l27 = 0; l27 < 3; l27 = l27 + 1) fRec34[l27] = 0.0f;
	for (int l28 = 0; l28 < 3; l28 = l28 + 1) fRec33[l28] = 0.0f;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fVec3[l29] = 0.0f;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec43[l30] = 0.0f;
	for (int l31 = 0; l31 < 3; l31 = l31 + 1) fRec42[l31] = 0.0f;
	for (int l32 = 0; l32 < 3; l32 = l32 + 1) fRec41[l32] = 0.0f;
	for (int l33 = 0; l33 < 3; l33 = l33 + 1) fRec40[l33] = 0.0f;
	for (int l34 = 0; l34 < 3; l34 = l34 + 1) fRec39[l34] = 0.0f;
	for (int l35 = 0; l35 < 3; l35 = l35 + 1) fRec38[l35] = 0.0f;
	for (int l36 = 0; l36 < 3; l36 = l36 + 1) fRec37[l36] = 0.0f;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fVec4[l37] = 0.0f;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fRec36[l38] = 0.0f;
	for (int l39 = 0; l39 < 3; l39 = l39 + 1) fRec35[l39] = 0.0f;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec50[l40] = 0.0f;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec48[l41] = 0.0f;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) fRec46[l42] = 0.0f;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fRec44[l43] = 0.0f;
	for (int l44 = 0; l44 < 2; l44 = l44 + 1) fRec58[l44] = 0.0f;
	for (int l45 = 0; l45 < 2; l45 = l45 + 1) fRec56[l45] = 0.0f;
	for (int l46 = 0; l46 < 2; l46 = l46 + 1) fRec54[l46] = 0.0f;
	for (int l47 = 0; l47 < 2; l47 = l47 + 1) fRec52[l47] = 0.0f;
	for (int l48 = 0; l48 < 1048576; l48 = l48 + 1) fVec5[l48] = 0.0f;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec32[l49] = 0.0f;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
	fConst1 = 3.1415927f / fConst0;
	fConst2 = std::tan(37699.113f / fConst0);
	fConst3 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst2));
	fConst4 = 1.0f / fConst2;
	fConst5 = (fConst4 + -1.0f) / fConst2 + 1.0f;
	fConst6 = (fConst4 + 1.0f) / fConst2 + 1.0f;
	fConst7 = 1.0f / fConst6;
	fConst8 = 25132.742f / fConst0;
	fConst9 = std::tan(fConst8);
	fConst10 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst9));
	fConst11 = fConst0 * std::sin(50265.484f / fConst0);
	fConst12 = 3141.5928f / fConst11;
	fConst13 = 1.0f / fConst9;
	fConst14 = (fConst13 - fConst12) / fConst9 + 1.0f;
	fConst15 = 1.0f / ((fConst13 + fConst12) / fConst9 + 1.0f);
	fConst16 = 12566.371f / fConst0;
	fConst17 = std::tan(fConst16);
	fConst18 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst17));
	fConst19 = fConst0 * std::sin(fConst8);
	fConst20 = 6268.3013f / fConst19;
	fConst21 = 1.0f / fConst17;
	fConst22 = (fConst21 - fConst20) / fConst17 + 1.0f;
	fConst23 = 1.0f / ((fConst21 + fConst20) / fConst17 + 1.0f);
	fConst24 = std::tan(6283.1855f / fConst0);
	fConst25 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst24));
	fConst26 = fConst0 * std::sin(fConst16);
	fConst27 = 1570.7964f / fConst26;
	fConst28 = 1.0f / fConst24;
	fConst29 = (fConst28 - fConst27) / fConst24 + 1.0f;
	fConst30 = 1.0f / ((fConst28 + fConst27) / fConst24 + 1.0f);
	fConst31 = std::tan(1178.0973f / fConst0);
	fConst32 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst31));
	fConst33 = fConst0 * std::sin(2356.1946f / fConst0);
	fConst34 = 392.6991f / fConst33;
	fConst35 = 1.0f / fConst31;
	fConst36 = (fConst35 - fConst34) / fConst31 + 1.0f;
	fConst37 = 1.0f / ((fConst35 + fConst34) / fConst31 + 1.0f);
	fConst38 = std::tan(628.31854f / fConst0);
	fConst39 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst38));
	fConst40 = fConst0 * std::sin(1256.6371f / fConst0);
	fConst41 = 221.88087f / fConst40;
	fConst42 = 1.0f / fConst38;
	fConst43 = (fConst42 - fConst41) / fConst38 + 1.0f;
	fConst44 = 1.0f / ((fConst42 + fConst41) / fConst38 + 1.0f);
	fConst45 = std::tan(251.32741f / fConst0);
	fConst46 = mydsp_faustpower2_f(fConst45);
	fConst47 = 2.0f * (1.0f - 1.0f / fConst46);
	fConst48 = 1.0f / fConst45;
	fConst49 = (fConst48 + -1.0f) / fConst45 + 1.0f;
	fConst50 = (fConst48 + 1.0f) / fConst45 + 1.0f;
	fConst51 = 1.0f / fConst50;
	fConst52 = 1.0f - fConst48;
	fConst53 = 1.0f / (fConst48 + 1.0f);
	fConst54 = 1.0f / (fConst46 * fConst50);
	fConst55 = 157.07964f / fConst40;
	fConst56 = (fConst42 - fConst55) / fConst38 + 1.0f;
	fConst57 = (fConst42 + fConst55) / fConst38 + 1.0f;
	fConst58 = 466.72372f / fConst33;
	fConst59 = (fConst35 - fConst58) / fConst31 + 1.0f;
	fConst60 = (fConst35 + fConst58) / fConst31 + 1.0f;
	fConst61 = 2218.8088f / fConst26;
	fConst62 = (fConst28 - fConst61) / fConst24 + 1.0f;
	fConst63 = (fConst28 + fConst61) / fConst24 + 1.0f;
	fConst64 = 3141.5928f / fConst19;
	fConst65 = (fConst21 - fConst64) / fConst17 + 1.0f;
	fConst66 = (fConst21 + fConst64) / fConst17 + 1.0f;
	fConst67 = 3955.0308f / fConst11;
	fConst68 = (fConst13 - fConst67) / fConst9 + 1.0f;
	fConst69 = (fConst13 + fConst67) / fConst9 + 1.0f;
	fConst70 = 1.0f - fConst4;
	fConst71 = 1.0f / (fConst4 + 1.0f);
	fConst72 = 0.8f / fConst6;
	fConst73 = 6e+01f * fConst0;
	fConst74 = 1e+01f / fConst0;
	IOTA0 = 0;
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
	float fSlow0 = float(fCheckbox0);
	int iSlow1 = int(fSlow0);
	float fSlow2 = 1.0f - fSlow0;
	float fSlow3 = float(fHslider0);
	float fSlow4 = std::min<float>(2.0f, std::max<float>(0.0f, fSlow3 + -2.0f));
	int iSlow5 = fSlow4 == 0.0f;
	int iSlow6 = fSlow4 == 1.0f;
	float fSlow7 = std::min<float>(2.0f, std::max<float>(0.0f, fSlow3 + -1.0f));
	int iSlow8 = fSlow7 == 0.0f;
	int iSlow9 = fSlow7 == 1.0f;
	float fSlow10 = std::min<float>(2.0f, std::max<float>(0.0f, fSlow3));
	int iSlow11 = fSlow10 == 0.0f;
	int iSlow12 = fSlow10 == 1.0f;
	float fSlow13 = std::tan(fConst1 * float(fHslider1));
	float fSlow14 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fSlow13));
	float fSlow15 = 1.0f / fSlow13;
	float fSlow16 = (fSlow15 + -1.4142135f) / fSlow13 + 1.0f;
	float fSlow17 = 1.0f / ((fSlow15 + 1.4142135f) / fSlow13 + 1.0f);
	float fSlow18 = std::tan(fConst1 * float(fHslider2));
	float fSlow19 = mydsp_faustpower2_f(fSlow18);
	float fSlow20 = 2.0f * (1.0f - 1.0f / fSlow19);
	float fSlow21 = 1.0f / fSlow18;
	float fSlow22 = (fSlow21 + -1.4142135f) / fSlow18 + 1.0f;
	float fSlow23 = (fSlow21 + 1.4142135f) / fSlow18 + 1.0f;
	float fSlow24 = 1.0f / fSlow23;
	float fSlow25 = 0.01f * float(fVslider0);
	float fSlow26 = 1.0f / (fSlow19 * fSlow23);
	float fSlow27 = std::min<float>(524288.0f, B2N(int(float(fHslider3)), fConst73 / float(fHslider4)));
	float fSlow28 = 0.01f * float(fVslider1);
	float fSlow29 = 0.01f * float(fVslider2);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		float fTemp0 = float(input0[i0]);
		fRec2[0] = fSlow25 * fRec0[1] - fSlow24 * (fSlow22 * fRec2[2] + fSlow20 * fRec2[1]);
		fRec1[0] = fSlow26 * (fRec2[2] + (fRec2[0] - 2.0f * fRec2[1])) - fSlow17 * (fSlow16 * fRec1[2] + fSlow14 * fRec1[1]);
		float fTemp1 = fSlow17 * (fRec1[2] + fRec1[0] + 2.0f * fRec1[1]);
		fVec0[0] = fTemp1;
		float fTemp2 = fConst10 * fRec5[1];
		float fTemp3 = fConst18 * fRec6[1];
		float fTemp4 = fConst25 * fRec7[1];
		float fTemp5 = fConst32 * fRec8[1];
		float fTemp6 = fConst39 * fRec9[1];
		fRec11[0] = -(fConst53 * (fConst52 * fRec11[1] - fConst48 * (fTemp1 - fVec0[1])));
		fRec10[0] = fRec11[0] - fConst51 * (fConst49 * fRec10[2] + fConst47 * fRec10[1]);
		fRec9[0] = fConst54 * (fRec10[2] + (fRec10[0] - 2.0f * fRec10[1])) - fConst44 * (fConst43 * fRec9[2] + fTemp6);
		fRec8[0] = fConst44 * (fTemp6 + fConst57 * fRec9[0] + fConst56 * fRec9[2]) - fConst37 * (fConst36 * fRec8[2] + fTemp5);
		fRec7[0] = fConst37 * (fTemp5 + fConst60 * fRec8[0] + fConst59 * fRec8[2]) - fConst30 * (fConst29 * fRec7[2] + fTemp4);
		fRec6[0] = fConst30 * (fTemp4 + fConst63 * fRec7[0] + fConst62 * fRec7[2]) - fConst23 * (fConst22 * fRec6[2] + fTemp3);
		fRec5[0] = fConst23 * (fTemp3 + fConst66 * fRec6[0] + fConst65 * fRec6[2]) - fConst15 * (fConst14 * fRec5[2] + fTemp2);
		float fTemp7 = fTemp2 + fConst69 * fRec5[0] + fConst68 * fRec5[2];
		fVec1[0] = fTemp7;
		fRec4[0] = -(fConst71 * (fConst70 * fRec4[1] - fConst15 * (fTemp7 + fVec1[1])));
		fRec3[0] = fRec4[0] - fConst7 * (fConst5 * fRec3[2] + fConst3 * fRec3[1]);
		float fTemp8 = ((iSlow11) ? fTemp1 : ((iSlow12) ? fConst72 * (fRec3[2] + fRec3[0] + 2.0f * fRec3[1]) : fTemp1));
		float fTemp9 = 0.1f * fRec12[1];
		float fTemp10 = 0.4f * fRec16[1] + fTemp9;
		float fTemp11 = 0.2f * fRec14[1];
		float fTemp12 = fTemp11 + fTemp8 + 0.6f * fRec18[1];
		fRec18[0] = fTemp12 - fTemp10;
		float fRec19 = 0.6f * (fTemp10 - fTemp12);
		fRec16[0] = fRec19 + fRec18[1];
		float fTemp13 = fTemp8 + fTemp11;
		float fRec17 = 0.4f * (fTemp13 - fTemp10);
		fRec14[0] = fRec17 + fRec16[1];
		float fRec15 = 0.2f * (fTemp9 - fTemp13);
		fRec12[0] = fRec15 + fRec14[1];
		float fRec13 = 0.1f * (fTemp8 - fTemp9);
		float fTemp14 = ((iSlow8) ? fTemp8 : ((iSlow9) ? fRec13 + fRec12[1] : fTemp8));
		float fTemp15 = 0.5f * fRec20[1];
		float fTemp16 = 0.4f * fRec22[1] + fTemp15;
		float fTemp17 = 0.3f * fRec24[1];
		float fTemp18 = fTemp17 + fTemp14 + 0.2f * fRec26[1];
		fRec26[0] = fTemp18 - fTemp16;
		float fRec27 = 0.2f * (fTemp16 - fTemp18);
		fRec24[0] = fRec27 + fRec26[1];
		float fRec25 = 0.3f * (fTemp16 - (fTemp14 + fTemp17));
		fRec22[0] = fRec25 + fRec24[1];
		float fRec23 = 0.4f * (fTemp14 - fTemp16);
		fRec20[0] = fRec23 + fRec22[1];
		float fRec21 = 0.5f * (fTemp14 - fTemp15);
		float fTemp19 = ((iSlow1) ? fRec0[1] : ((iSlow5) ? fTemp14 : ((iSlow6) ? fRec21 + fRec20[1] : fTemp14))) + fSlow2 * fTemp0;
		fVec2[IOTA0 & 1048575] = fTemp19;
		float fTemp20 = ((fRec28[1] != 0.0f) ? (((fRec29[1] > 0.0f) & (fRec29[1] < 1.0f)) ? fRec28[1] : 0.0f) : (((fRec29[1] == 0.0f) & (fSlow27 != fRec30[1])) ? fConst74 : (((fRec29[1] == 1.0f) & (fSlow27 != fRec31[1])) ? -fConst74 : 0.0f)));
		fRec28[0] = fTemp20;
		fRec29[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec29[1] + fTemp20));
		fRec30[0] = (((fRec29[1] >= 1.0f) & (fRec31[1] != fSlow27)) ? fSlow27 : fRec30[1]);
		fRec31[0] = (((fRec29[1] <= 0.0f) & (fRec30[1] != fSlow27)) ? fSlow27 : fRec31[1]);
		int iTemp21 = int(std::min<float>(524288.0f, std::max<float>(0.0f, fRec30[0])));
		float fTemp22 = fVec2[(IOTA0 - iTemp21) & 1048575];
		int iTemp23 = int(std::min<float>(524288.0f, std::max<float>(0.0f, fRec31[0])));
		float fTemp24 = fTemp22 + fRec29[0] * (fVec2[(IOTA0 - iTemp23) & 1048575] - fTemp22);
		fRec0[0] = ((iSlow1) ? fTemp24 : fSlow28 * fTemp24);
		output0[i0] = FAUSTFLOAT(fTemp0 + fSlow29 * fRec0[0]);
		float fTemp25 = float(input1[i0]);
		fRec34[0] = fSlow25 * fRec32[1] - fSlow24 * (fSlow22 * fRec34[2] + fSlow20 * fRec34[1]);
		fRec33[0] = fSlow26 * (fRec34[2] + (fRec34[0] - 2.0f * fRec34[1])) - fSlow17 * (fSlow16 * fRec33[2] + fSlow14 * fRec33[1]);
		float fTemp26 = fSlow17 * (fRec33[2] + fRec33[0] + 2.0f * fRec33[1]);
		fVec3[0] = fTemp26;
		float fTemp27 = fConst10 * fRec37[1];
		float fTemp28 = fConst18 * fRec38[1];
		float fTemp29 = fConst25 * fRec39[1];
		float fTemp30 = fConst32 * fRec40[1];
		float fTemp31 = fConst39 * fRec41[1];
		fRec43[0] = -(fConst53 * (fConst52 * fRec43[1] - fConst48 * (fTemp26 - fVec3[1])));
		fRec42[0] = fRec43[0] - fConst51 * (fConst49 * fRec42[2] + fConst47 * fRec42[1]);
		fRec41[0] = fConst54 * (fRec42[2] + (fRec42[0] - 2.0f * fRec42[1])) - fConst44 * (fConst43 * fRec41[2] + fTemp31);
		fRec40[0] = fConst44 * (fTemp31 + fConst57 * fRec41[0] + fConst56 * fRec41[2]) - fConst37 * (fConst36 * fRec40[2] + fTemp30);
		fRec39[0] = fConst37 * (fTemp30 + fConst60 * fRec40[0] + fConst59 * fRec40[2]) - fConst30 * (fConst29 * fRec39[2] + fTemp29);
		fRec38[0] = fConst30 * (fTemp29 + fConst63 * fRec39[0] + fConst62 * fRec39[2]) - fConst23 * (fConst22 * fRec38[2] + fTemp28);
		fRec37[0] = fConst23 * (fTemp28 + fConst66 * fRec38[0] + fConst65 * fRec38[2]) - fConst15 * (fConst14 * fRec37[2] + fTemp27);
		float fTemp32 = fTemp27 + fConst69 * fRec37[0] + fConst68 * fRec37[2];
		fVec4[0] = fTemp32;
		fRec36[0] = -(fConst71 * (fConst70 * fRec36[1] - fConst15 * (fTemp32 + fVec4[1])));
		fRec35[0] = fRec36[0] - fConst7 * (fConst5 * fRec35[2] + fConst3 * fRec35[1]);
		float fTemp33 = ((iSlow11) ? fTemp26 : ((iSlow12) ? fConst72 * (fRec35[2] + fRec35[0] + 2.0f * fRec35[1]) : fTemp26));
		float fTemp34 = 0.1f * fRec44[1];
		float fTemp35 = 0.4f * fRec48[1] + fTemp34;
		float fTemp36 = 0.2f * fRec46[1];
		float fTemp37 = fTemp36 + fTemp33 + 0.6f * fRec50[1];
		fRec50[0] = fTemp37 - fTemp35;
		float fRec51 = 0.6f * (fTemp35 - fTemp37);
		fRec48[0] = fRec51 + fRec50[1];
		float fTemp38 = fTemp33 + fTemp36;
		float fRec49 = 0.4f * (fTemp38 - fTemp35);
		fRec46[0] = fRec49 + fRec48[1];
		float fRec47 = 0.2f * (fTemp34 - fTemp38);
		fRec44[0] = fRec47 + fRec46[1];
		float fRec45 = 0.1f * (fTemp33 - fTemp34);
		float fTemp39 = ((iSlow8) ? fTemp33 : ((iSlow9) ? fRec45 + fRec44[1] : fTemp33));
		float fTemp40 = 0.5f * fRec52[1];
		float fTemp41 = 0.4f * fRec54[1] + fTemp40;
		float fTemp42 = 0.3f * fRec56[1];
		float fTemp43 = fTemp42 + fTemp39 + 0.2f * fRec58[1];
		fRec58[0] = fTemp43 - fTemp41;
		float fRec59 = 0.2f * (fTemp41 - fTemp43);
		fRec56[0] = fRec59 + fRec58[1];
		float fRec57 = 0.3f * (fTemp41 - (fTemp39 + fTemp42));
		fRec54[0] = fRec57 + fRec56[1];
		float fRec55 = 0.4f * (fTemp39 - fTemp41);
		fRec52[0] = fRec55 + fRec54[1];
		float fRec53 = 0.5f * (fTemp39 - fTemp40);
		float fTemp44 = ((iSlow1) ? fRec32[1] : ((iSlow5) ? fTemp39 : ((iSlow6) ? fRec53 + fRec52[1] : fTemp39))) + fSlow2 * fTemp25;
		fVec5[IOTA0 & 1048575] = fTemp44;
		float fTemp45 = fVec5[(IOTA0 - iTemp21) & 1048575];
		float fTemp46 = fTemp45 + fRec29[0] * (fVec5[(IOTA0 - iTemp23) & 1048575] - fTemp45);
		fRec32[0] = ((iSlow1) ? fTemp46 : fSlow28 * fTemp46);
		output1[i0] = FAUSTFLOAT(fTemp25 + fSlow29 * fRec32[0]);
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
		IOTA0 = IOTA0 + 1;
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
	reg.registerFloatVar("didest.bpm",N_("BPM"),"S",N_("Delay in Beats per Minute"),&fHslider4, 1.2e+02f, 24.0f, 3.6e+02f, 1.0f, 0);
	reg.registerFloatVar("didest.feedback",N_("Feedback"),"S",N_("Percentage of the feedback level in the de.delay loop"),&fVslider0, 5e+01f, 1.0f, 1e+02f, 1.0f, 0);
	reg.registerFloatVar("didest.gain",N_("Gain"),"S",N_("Overall gain of the de.delay line in percent"),&fVslider2, 1e+02f, 0.0f, 1.2e+02f, 1.0f, 0);
	reg.registerFloatVar("didest.highpass",N_("Hipass"),"S",N_("Highpass filter frequency in the feedback loop"),&fHslider2, 1.2e+02f, 2e+01f, 2e+04f, 1.0f, 0);
	reg.registerFloatVar("didest.howpass",N_("Lopass"),"S",N_("Lowpass filter frequency in the feedback loop"),&fHslider1, 1.2e+04f, 2e+01f, 2e+04f, 1.0f, 0);
	reg.registerFloatVar("didest.level",N_("Level"),"S",N_("Percentage of the de.delay gain level"),&fVslider1, 5e+01f, 1.0f, 1e+02f, 1.0f, 0);
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
