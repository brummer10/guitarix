// generated from file '../src/LV2/faust/gxmetal_head.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxmetal_head {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	double fConst2;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst6;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	double fConst9;
	double fConst10;
	double fConst12;
	double fConst13;
	double fConst16;
	double fConst17;
	double fConst19;
	double fConst20;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fVec0[2];
	double fConst28;
	double fRec29[2];
	double fConst30;
	double fConst31;
	double fConst33;
	double fConst34;
	double fRec28[2];
	double fConst35;
	double fConst37;
	double fRec27[2];
	double fRec26[3];
	double fVec1[2];
	double fConst38;
	double fConst40;
	double fRec25[2];
	double fRec24[3];
	double fVec2[2];
	double fConst41;
	double fConst43;
	double fRec23[2];
	double fRec22[3];
	double fConst44;
	double fConst45;
	double fConst46;
	double fRec31[2];
	double fRec30[3];
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fRec35[2];
	double fRec34[3];
	double fConst53;
	double fRec33[3];
	double fRec32[3];
	double fConst54;
	double fConst55;
	double fConst56;
	double fRec38[2];
	double fRec37[3];
	double fConst57;
	double fRec36[3];
	double fVec3[2];
	double fRec21[2];
	double fRec20[2];
	double fVec4[2];
	double fRec19[2];
	double fRec18[3];
	double fConst59;
	double fVec5[2];
	double fConst60;
	double fRec39[2];
	double fRec17[2];
	double fConst61;
	double fConst62;
	double fRec16[2];
	double fConst64;
	double fConst65;
	double fRec40[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec41[2];
	double fVec6[2];
	double fRec15[2];
	double fRec14[2];
	double fRec13[3];
	double fConst67;
	double fVec7[2];
	double fConst68;
	double fRec42[2];
	double fRec12[2];
	double fRec11[2];
	double fRec43[2];
	double fVec8[2];
	double fRec10[2];
	double fRec9[2];
	double fRec8[3];
	double fConst70;
	double fVec9[2];
	double fConst71;
	double fRec44[2];
	double fRec7[2];
	double fRec6[2];
	double fRec45[2];
	double fVec10[2];
	double fConst73;
	double fConst74;
	double fRec5[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fConst76;
	double fConst77;
	double fConst79;
	double fConst80;
	double fRec46[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec47[2];
	double fVec11[2];
	double fRec4[2];
	double fRec3[3];
	double fConst82;
	double fConst83;
	double fRec48[2];
	double fRec2[3];
	double fRec50[2];
	double fRec49[3];
	double fVec12[2];
	double fRec1[2];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "metal";
	name = N_("GxMetal_head");
	mono_audio = compute_static;
	stereo_audio = 0;
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
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fVec0[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec29[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec28[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec27[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec26[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fVec1[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec25[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec24[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fVec2[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec23[l10] = 0.0;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec22[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec31[l12] = 0.0;
	for (int l13 = 0; l13 < 3; l13 = l13 + 1) fRec30[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec35[l14] = 0.0;
	for (int l15 = 0; l15 < 3; l15 = l15 + 1) fRec34[l15] = 0.0;
	for (int l16 = 0; l16 < 3; l16 = l16 + 1) fRec33[l16] = 0.0;
	for (int l17 = 0; l17 < 3; l17 = l17 + 1) fRec32[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec38[l18] = 0.0;
	for (int l19 = 0; l19 < 3; l19 = l19 + 1) fRec37[l19] = 0.0;
	for (int l20 = 0; l20 < 3; l20 = l20 + 1) fRec36[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fVec3[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec21[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec20[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fVec4[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec19[l25] = 0.0;
	for (int l26 = 0; l26 < 3; l26 = l26 + 1) fRec18[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fVec5[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec39[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec17[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec16[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec40[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fRec41[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fVec6[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fRec15[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec14[l35] = 0.0;
	for (int l36 = 0; l36 < 3; l36 = l36 + 1) fRec13[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fVec7[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fRec42[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec12[l39] = 0.0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec11[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec43[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) fVec8[l42] = 0.0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fRec10[l43] = 0.0;
	for (int l44 = 0; l44 < 2; l44 = l44 + 1) fRec9[l44] = 0.0;
	for (int l45 = 0; l45 < 3; l45 = l45 + 1) fRec8[l45] = 0.0;
	for (int l46 = 0; l46 < 2; l46 = l46 + 1) fVec9[l46] = 0.0;
	for (int l47 = 0; l47 < 2; l47 = l47 + 1) fRec44[l47] = 0.0;
	for (int l48 = 0; l48 < 2; l48 = l48 + 1) fRec7[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec6[l49] = 0.0;
	for (int l50 = 0; l50 < 2; l50 = l50 + 1) fRec45[l50] = 0.0;
	for (int l51 = 0; l51 < 2; l51 = l51 + 1) fVec10[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fRec5[l52] = 0.0;
	for (int l53 = 0; l53 < 2; l53 = l53 + 1) fRec46[l53] = 0.0;
	for (int l54 = 0; l54 < 2; l54 = l54 + 1) fRec47[l54] = 0.0;
	for (int l55 = 0; l55 < 2; l55 = l55 + 1) fVec11[l55] = 0.0;
	for (int l56 = 0; l56 < 2; l56 = l56 + 1) fRec4[l56] = 0.0;
	for (int l57 = 0; l57 < 3; l57 = l57 + 1) fRec3[l57] = 0.0;
	for (int l58 = 0; l58 < 2; l58 = l58 + 1) fRec48[l58] = 0.0;
	for (int l59 = 0; l59 < 3; l59 = l59 + 1) fRec2[l59] = 0.0;
	for (int l60 = 0; l60 < 2; l60 = l60 + 1) fRec50[l60] = 0.0;
	for (int l61 = 0; l61 < 3; l61 = l61 + 1) fRec49[l61] = 0.0;
	for (int l62 = 0; l62 < 2; l62 = l62 + 1) fVec12[l62] = 0.0;
	for (int l63 = 0; l63 < 2; l63 = l63 + 1) fRec1[l63] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 1.0 / std::tan(20517.741620594938 / fConst0);
	fConst2 = 1.0 - fConst1;
	double fConst3 = std::tan(97.38937226128358 / fConst0);
	double fConst4 = 1.0 / fConst3;
	double fConst5 = fConst4 + 1.0;
	fConst6 = (1.0 - fConst4) / fConst5;
	double fConst7 = std::tan(942.4777960769379 / fConst0);
	double fConst8 = mydsp_faustpower2_f(fConst7);
	fConst9 = 1.0 / fConst8;
	fConst10 = 2.0 * (1.0 - fConst9);
	double fConst11 = 1.0 / fConst7;
	fConst12 = (fConst11 + -1.0000000000000004) / fConst7 + 1.0;
	fConst13 = 1.0 / ((fConst11 + 1.0000000000000004) / fConst7 + 1.0);
	double fConst14 = std::tan(3769.9111843077517 / fConst0);
	double fConst15 = mydsp_faustpower2_f(fConst14);
	fConst16 = 1.0 / fConst15;
	fConst17 = 2.0 * (1.0 - fConst16);
	double fConst18 = 1.0 / fConst14;
	fConst19 = (fConst18 + -1.0000000000000004) / fConst14 + 1.0;
	fConst20 = 1.0 / ((fConst18 + 1.0000000000000004) / fConst14 + 1.0);
	double fConst21 = std::tan(10053.096491487338 / fConst0);
	double fConst22 = mydsp_faustpower2_f(fConst21);
	fConst23 = 1.0 / fConst22;
	fConst24 = 2.0 * (1.0 - fConst23);
	fConst25 = 1.0 / fConst21;
	fConst26 = (fConst25 + -1.0000000000000004) / fConst21 + 1.0;
	fConst27 = 1.0 / ((fConst25 + 1.0000000000000004) / fConst21 + 1.0);
	fConst28 = 1.0 / (fConst1 + 1.0);
	double fConst29 = std::tan(376.99111843077515 / fConst0);
	fConst30 = 1.0 / fConst29;
	fConst31 = 1.0 - fConst30;
	double fConst32 = fConst30 + 1.0;
	fConst33 = 1.0 / fConst32;
	fConst34 = 0.0 - 1.0 / (fConst29 * fConst32);
	fConst35 = 1.0 - fConst25;
	double fConst36 = fConst25 + 1.0;
	fConst37 = 1.0 / fConst36;
	fConst38 = 1.0 - fConst18;
	double fConst39 = fConst18 + 1.0;
	fConst40 = 1.0 / fConst39;
	fConst41 = 1.0 - fConst11;
	double fConst42 = fConst11 + 1.0;
	fConst43 = 1.0 / fConst42;
	fConst44 = fConst41 / fConst42;
	fConst45 = 1.0 / (fConst7 * fConst42);
	fConst46 = 0.0 - fConst45;
	fConst47 = 0.0 - 2.0 / fConst8;
	fConst48 = 1.0 - fConst41 / fConst7;
	fConst49 = 1.0 / (fConst42 / fConst7 + 1.0);
	fConst50 = 1.0 - fConst38 / fConst14;
	fConst51 = 1.0 / (fConst39 / fConst14 + 1.0);
	fConst52 = 0.0 - 1.0 / (fConst21 * fConst36);
	fConst53 = 0.0 - 2.0 / fConst22;
	fConst54 = fConst38 / fConst39;
	fConst55 = 1.0 / (fConst14 * fConst39);
	fConst56 = 0.0 - fConst55;
	fConst57 = 0.0 - 2.0 / fConst15;
	double fConst58 = 1.0 / std::tan(270.1769682087222 / fConst0);
	fConst59 = 1.0 - fConst58;
	fConst60 = 1.0 / (fConst58 + 1.0);
	fConst61 = 1.0 / (fConst3 * fConst5);
	fConst62 = 0.0 - fConst61;
	double fConst63 = 3.141592653589793 / fConst0;
	fConst64 = 1.0 - fConst63;
	fConst65 = 1.0 / (fConst63 + 1.0);
	double fConst66 = 1.0 / std::tan(414.6902302738527 / fConst0);
	fConst67 = 1.0 - fConst66;
	fConst68 = 1.0 / (fConst66 + 1.0);
	double fConst69 = 1.0 / std::tan(609.4689747964198 / fConst0);
	fConst70 = 1.0 - fConst69;
	fConst71 = 1.0 / (fConst69 + 1.0);
	double fConst72 = 1.0 / std::tan(1281.7698026646356 / fConst0);
	fConst73 = 1.0 - fConst72;
	fConst74 = 1.0 / (fConst72 + 1.0);
	double fConst75 = std::tan(5830.795965062656 / fConst0);
	fConst76 = 1.0 / fConst75;
	fConst77 = 1.0 - fConst76;
	double fConst78 = fConst76 + 1.0;
	fConst79 = 1.0 / fConst78;
	fConst80 = 0.0 - 1.0 / (fConst75 * fConst78);
	double fConst81 = 1.0 / std::tan(804.247719318987 / fConst0);
	fConst82 = 1.0 - fConst81;
	fConst83 = 1.0 / (fConst81 + 1.0);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fCheckbox0 (*fCheckbox0_)
#define fCheckbox1 (*fCheckbox1_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	double fSlow0 = double(fVslider0);
	double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (0.0 - 12.0 * fSlow0));
	int iSlow2 = int(double(fCheckbox0));
	int iSlow3 = int(double(fCheckbox1));
	double fSlow4 = fConst13 * std::pow(1e+01, 0.8 * fSlow0);
	double fSlow5 = std::pow(1e+01, 1.6 * fSlow0);
	double fSlow6 = fConst13 * fSlow5;
	double fSlow7 = std::pow(1e+01, 1.2 * fSlow0);
	double fSlow8 = 2.0 * (fSlow0 + -0.5);
	double fSlow9 = 1.0 - std::max<double>(0.0, -1.0 * fSlow8);
	double fSlow10 = 1.0 - std::max<double>(0.0, fSlow8);
	double fSlow11 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider1));
	double fSlow12 = double(fVslider2);
	double fSlow13 = 1.0 - fSlow12;
	double fSlow14 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider3));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow1 + 0.999 * fRec0[1];
		double fTemp0 = double(input0[i0]);
		fVec0[0] = fTemp0;
		fRec29[0] = 0.0 - fConst28 * (fConst2 * fRec29[1] - (fTemp0 + fVec0[1]));
		fRec28[0] = fConst34 * fRec29[1] - fConst33 * (fConst31 * fRec28[1] - fConst30 * fRec29[0]);
		fRec27[0] = 0.0 - fConst37 * (fConst35 * fRec27[1] - (fRec28[0] + fRec28[1]));
		fRec26[0] = fRec27[0] - fConst27 * (fConst26 * fRec26[2] + fConst24 * fRec26[1]);
		double fTemp1 = fRec26[2] + fRec26[0] + 2.0 * fRec26[1];
		fVec1[0] = fTemp1;
		fRec25[0] = 0.0 - fConst40 * (fConst38 * fRec25[1] - fConst27 * (fTemp1 + fVec1[1]));
		fRec24[0] = fRec25[0] - fConst20 * (fConst19 * fRec24[2] + fConst17 * fRec24[1]);
		double fTemp2 = fRec24[2] + fRec24[0] + 2.0 * fRec24[1];
		fVec2[0] = fTemp2;
		fRec23[0] = 0.0 - fConst43 * (fConst41 * fRec23[1] - fConst20 * (fTemp2 + fVec2[1]));
		fRec22[0] = fRec23[0] - fConst13 * (fConst12 * fRec22[2] + fConst10 * fRec22[1]);
		double fTemp3 = std::max<double>(-1.0, std::min<double>(1.0, fSlow4 * (fRec22[2] + fRec22[0] + 2.0 * fRec22[1])));
		fRec31[0] = fConst20 * (fConst45 * fTemp2 + fConst46 * fVec2[1]) - fConst44 * fRec31[1];
		fRec30[0] = fRec31[0] - fConst13 * (fConst12 * fRec30[2] + fConst10 * fRec30[1]);
		double fTemp4 = std::max<double>(-1.0, std::min<double>(1.0, fSlow6 * (fConst9 * fRec30[0] + fConst47 * fRec30[1] + fConst9 * fRec30[2])));
		double fTemp5 = fConst10 * fRec32[1];
		double fTemp6 = fConst17 * fRec33[1];
		fRec35[0] = fConst52 * fRec28[1] - fConst37 * (fConst35 * fRec35[1] - fConst25 * fRec28[0]);
		fRec34[0] = fRec35[0] - fConst27 * (fConst26 * fRec34[2] + fConst24 * fRec34[1]);
		fRec33[0] = fConst27 * (fConst23 * fRec34[0] + fConst53 * fRec34[1] + fConst23 * fRec34[2]) - fConst51 * (fConst50 * fRec33[2] + fTemp6);
		fRec32[0] = fRec33[2] + fConst51 * (fTemp6 + fConst50 * fRec33[0]) - fConst49 * (fConst48 * fRec32[2] + fTemp5);
		double fTemp7 = std::max<double>(-1.0, std::min<double>(1.0, fSlow5 * (fRec32[2] + fConst49 * (fTemp5 + fConst48 * fRec32[0]))));
		double fTemp8 = fConst10 * fRec36[1];
		fRec38[0] = fConst27 * (fConst55 * fTemp1 + fConst56 * fVec1[1]) - fConst54 * fRec38[1];
		fRec37[0] = fRec38[0] - fConst20 * (fConst19 * fRec37[2] + fConst17 * fRec37[1]);
		fRec36[0] = fConst20 * (fConst16 * fRec37[0] + fConst57 * fRec37[1] + fConst16 * fRec37[2]) - fConst49 * (fConst48 * fRec36[2] + fTemp8);
		double fTemp9 = std::max<double>(-1.0, std::min<double>(1.0, fSlow7 * (fRec36[2] + fConst49 * (fTemp8 + fConst48 * fRec36[0]))));
		double fTemp10 = 1.333521432 * fTemp9 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp9)) + 1.584893192 * (fTemp7 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp7)) + fTemp4 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp4))) + 1.2589412 * fTemp3 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp3));
		fVec3[0] = fTemp10;
		fRec21[0] = 0.0 - fConst28 * (fConst2 * fRec21[1] - (fTemp10 + fVec3[1]));
		fRec20[0] = fConst34 * fRec21[1] - fConst33 * (fConst31 * fRec20[1] - fConst30 * fRec21[0]);
		double fTemp11 = fSlow10 * fTemp0 + fSlow9 * fRec20[0];
		fVec4[0] = fTemp11;
		fRec19[0] = 0.9302847925323914 * (fTemp11 + fVec4[1]) - 0.8605695850647829 * fRec19[1];
		fRec18[0] = fRec19[0] - (1.8405051250752198 * fRec18[1] + 0.8612942439318627 * fRec18[2]);
		double fTemp12 = 1.8508996845035413 * fRec18[1];
		double fTemp13 = 0.9254498422517706 * (fRec18[0] + fRec18[2]);
		double fTemp14 = (fTemp12 + fTemp13) / (Ranode(TUBE_TABLE_12AX7_68k, fRec17[1]) + 1e+05);
		fVec5[0] = fTemp14;
		fRec39[0] = fConst60 * (2.7e+03 * (fTemp14 + fVec5[1]) - fConst59 * fRec39[1]);
		fRec17[0] = Ftube(TUBE_TABLE_12AX7_68k, fTemp13 + fRec39[0] + fTemp12 + -1.581656) + -191.42014814814814;
		fRec16[0] = 0.025 * (fConst61 * fRec17[0] + fConst62 * fRec17[1]) - fConst6 * fRec16[1];
		fRec40[0] = fConst65 * (fConst64 * fRec40[1] + 0.025 * (fRec17[0] - fRec17[1]));
		fRec41[0] = fSlow11 + 0.999 * fRec41[1];
		double fTemp15 = fRec41[0] * ((iSlow3) ? fRec40[0] : fRec16[0]);
		fVec6[0] = fTemp15;
		fRec15[0] = 0.0 - fConst28 * (fConst2 * fRec15[1] - (fTemp15 + fVec6[1]));
		fRec14[0] = 0.9302847925323914 * (fRec15[0] + fRec15[1]) - 0.8605695850647829 * fRec14[1];
		fRec13[0] = fRec14[0] - (1.8405051250752198 * fRec13[1] + 0.8612942439318627 * fRec13[2]);
		double fTemp16 = 1.8508996845035413 * fRec13[1];
		double fTemp17 = 0.9254498422517706 * (fRec13[0] + fRec13[2]);
		double fTemp18 = (fTemp16 + fTemp17) / (Ranode(TUBE_TABLE_12AX7_250k, fRec12[1]) + 1e+05);
		fVec7[0] = fTemp18;
		fRec42[0] = fConst68 * (1.5e+03 * (fTemp18 + fVec7[1]) - fConst67 * fRec42[1]);
		fRec12[0] = Ftube(TUBE_TABLE_12AX7_250k, fTemp17 + fRec42[0] + fTemp16 + -1.204285) + -169.71433333333334;
		fRec11[0] = 0.025 * (fConst61 * fRec12[0] + fConst62 * fRec12[1]) - fConst6 * fRec11[1];
		fRec43[0] = fConst65 * (fConst64 * fRec43[1] + 0.025 * (fRec12[0] - fRec12[1]));
		double fTemp19 = ((iSlow3) ? fRec43[0] : fRec11[0]);
		fVec8[0] = fTemp19;
		fRec10[0] = 0.0 - fConst28 * (fConst2 * fRec10[1] - (fTemp19 + fVec8[1]));
		fRec9[0] = 0.9302847925323914 * (fRec10[0] + fRec10[1]) - 0.8605695850647829 * fRec9[1];
		fRec8[0] = fRec9[0] - (1.8405051250752198 * fRec8[1] + 0.8612942439318627 * fRec8[2]);
		double fTemp20 = 1.8508996845035413 * fRec8[1];
		double fTemp21 = 0.9254498422517706 * (fRec8[0] + fRec8[2]);
		double fTemp22 = (fTemp20 + fTemp21) / (Ranode(TUBE_TABLE_12AX7_250k, fRec7[1]) + 1e+05);
		fVec9[0] = fTemp22;
		fRec44[0] = fConst71 * (8.2e+02 * (fTemp22 + fVec9[1]) - fConst70 * fRec44[1]);
		fRec7[0] = Ftube(TUBE_TABLE_12AX7_250k, fTemp21 + fRec44[0] + fTemp20 + -0.840703) + -147.47524390243905;
		fRec6[0] = 0.025 * (fConst61 * fRec7[0] + fConst62 * fRec7[1]) - fConst6 * fRec6[1];
		fRec45[0] = fConst65 * (fConst64 * fRec45[1] + 0.025 * (fRec7[0] - fRec7[1]));
		double fTemp23 = ((iSlow2) ? fRec45[0] : fRec6[0]);
		fVec10[0] = fTemp23;
		fRec5[0] = 0.0 - fConst74 * (fConst73 * fRec5[1] - (fTemp23 + fVec10[1]));
		fRec46[0] = fConst80 * fVec10[1] - fConst79 * (fConst77 * fRec46[1] - fConst76 * fTemp23);
		fRec47[0] = fSlow14 + 0.999 * fRec47[1];
		double fTemp24 = fRec47[0] * (fSlow12 * fRec46[0] + fSlow13 * fRec5[0]);
		fVec11[0] = fTemp24;
		fRec4[0] = 0.9302847925323914 * (fTemp24 + fVec11[1]) - 0.8605695850647829 * fRec4[1];
		fRec3[0] = fRec4[0] - (1.8405051250752198 * fRec3[1] + 0.8612942439318627 * fRec3[2]);
		double fTemp25 = 1.8508996845035413 * fRec3[1];
		fRec48[0] = fConst83 * (0.098 * (fRec2[1] + fRec2[2]) - fConst82 * fRec48[1]);
		double fTemp26 = 0.9254498422517706 * (fRec3[0] + fRec3[2]);
		fRec2[0] = Ftube(TUBE_TABLE_6L6CG_250k, fTemp26 + fRec48[0] + fTemp25 + -20.063657) + -245.26880612244898;
		fRec50[0] = fConst83 * (0.098 * (fRec49[1] + fRec49[2]) - fConst82 * fRec50[1]);
		fRec49[0] = Ftube(TUBE_TABLE_6L6CG_68k, fTemp26 + fRec50[0] + fTemp25 + -20.063657) + -245.26880612244898;
		double fTemp27 = fRec47[0] * (fRec49[0] + fRec2[0]);
		fVec12[0] = fTemp27;
		fRec1[0] = fConst28 * (0.025 * (fTemp27 + fVec12[1]) - fConst2 * fRec1[1]);
		output0[i0] = FAUSTFLOAT(fRec1[0] * fRec0[0]);
		fRec0[1] = fRec0[0];
		fVec0[1] = fVec0[0];
		fRec29[1] = fRec29[0];
		fRec28[1] = fRec28[0];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fVec1[1] = fVec1[0];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fVec2[1] = fVec2[0];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fRec38[1] = fRec38[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		fVec3[1] = fVec3[0];
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fVec4[1] = fVec4[0];
		fRec19[1] = fRec19[0];
		fRec18[2] = fRec18[1];
		fRec18[1] = fRec18[0];
		fVec5[1] = fVec5[0];
		fRec39[1] = fRec39[0];
		fRec17[1] = fRec17[0];
		fRec16[1] = fRec16[0];
		fRec40[1] = fRec40[0];
		fRec41[1] = fRec41[0];
		fVec6[1] = fVec6[0];
		fRec15[1] = fRec15[0];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fVec7[1] = fVec7[0];
		fRec42[1] = fRec42[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fRec43[1] = fRec43[0];
		fVec8[1] = fVec8[0];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fVec9[1] = fVec9[0];
		fRec44[1] = fRec44[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec45[1] = fRec45[0];
		fVec10[1] = fVec10[0];
		fRec5[1] = fRec5[0];
		fRec46[1] = fRec46[0];
		fRec47[1] = fRec47[0];
		fVec11[1] = fVec11[0];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec48[1] = fRec48[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec50[1] = fRec50[0];
		fRec49[2] = fRec49[1];
		fRec49[1] = fRec49[0];
		fVec12[1] = fVec12[0];
		fRec1[1] = fRec1[0];
	}
#undef fVslider0
#undef fCheckbox0
#undef fCheckbox1
#undef fVslider1
#undef fVslider2
#undef fVslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case HIGHGAIN: 
		fCheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case DRIVE: 
		fVslider0_ = (float*)data; // , 0.35, 0.0, 1.0, 0.01 
		break;
	case PREGAIN: 
		fVslider1_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
		break;
	case GAIN1: 
		fVslider3_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
		break;
	case TONE: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   DRIVE, 
   HIGHGAIN, 
   PREGAIN, 
   GAIN1, 
   TONE, 
} PortIndex;
*/

} // end namespace gxmetal_head
