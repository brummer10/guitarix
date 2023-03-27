// generated from file '../src/LV2/faust/gxamp3.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxamp3 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst4;
	double fConst6;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec14[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
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
	double fConst29;
	double fConst31;
	double fConst32;
	double fRec23[3];
	double fVec0[2];
	double fConst33;
	double fConst34;
	double fRec22[2];
	double fConst35;
	double fConst37;
	double fRec21[2];
	double fRec20[3];
	double fVec1[2];
	double fConst38;
	double fConst40;
	double fRec19[2];
	double fRec18[3];
	double fVec2[2];
	double fConst41;
	double fConst43;
	double fRec17[2];
	double fRec16[3];
	double fConst44;
	double fConst45;
	double fConst46;
	double fRec25[2];
	double fRec24[3];
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fRec29[2];
	double fRec28[3];
	double fConst53;
	double fRec27[3];
	double fRec26[3];
	double fConst54;
	double fConst55;
	double fConst56;
	double fRec32[2];
	double fRec31[3];
	double fConst57;
	double fRec30[3];
	double fVec3[2];
	double fConst58;
	double fRec15[2];
	double fVec4[2];
	double fRec13[2];
	double fRec12[3];
	double fConst60;
	double fVec5[2];
	double fConst61;
	double fRec33[2];
	double fRec11[2];
	double fRec10[2];
	double fConst63;
	double fConst64;
	double fRec34[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec35[2];
	double fVec6[2];
	double fRec9[2];
	double fRec8[2];
	double fRec7[3];
	double fConst66;
	double fVec7[2];
	double fConst67;
	double fRec36[2];
	double fRec6[2];
	double fRec5[2];
	double fRec37[2];
	double fVec8[2];
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fConst69;
	double fVec9[2];
	double fConst70;
	double fRec38[2];
	double fRec1[2];
	double fRec0[2];
	double fRec39[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec40[2];

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
	id = "12AU7";
	name = N_("12AU7");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec14[l0] = 0.0;
	for (int l1 = 0; l1 < 3; l1 = l1 + 1) fRec23[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fVec0[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec22[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec21[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec20[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fVec1[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec19[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec18[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fVec2[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec17[l10] = 0.0;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec16[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec25[l12] = 0.0;
	for (int l13 = 0; l13 < 3; l13 = l13 + 1) fRec24[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec29[l14] = 0.0;
	for (int l15 = 0; l15 < 3; l15 = l15 + 1) fRec28[l15] = 0.0;
	for (int l16 = 0; l16 < 3; l16 = l16 + 1) fRec27[l16] = 0.0;
	for (int l17 = 0; l17 < 3; l17 = l17 + 1) fRec26[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec32[l18] = 0.0;
	for (int l19 = 0; l19 < 3; l19 = l19 + 1) fRec31[l19] = 0.0;
	for (int l20 = 0; l20 < 3; l20 = l20 + 1) fRec30[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fVec3[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec15[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fVec4[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec13[l24] = 0.0;
	for (int l25 = 0; l25 < 3; l25 = l25 + 1) fRec12[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fVec5[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec33[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec11[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec10[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec34[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec35[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fVec6[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fRec9[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fRec8[l34] = 0.0;
	for (int l35 = 0; l35 < 3; l35 = l35 + 1) fRec7[l35] = 0.0;
	for (int l36 = 0; l36 < 2; l36 = l36 + 1) fVec7[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec36[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fRec6[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec5[l39] = 0.0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec37[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fVec8[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) fRec4[l42] = 0.0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fRec3[l43] = 0.0;
	for (int l44 = 0; l44 < 3; l44 = l44 + 1) fRec2[l44] = 0.0;
	for (int l45 = 0; l45 < 2; l45 = l45 + 1) fVec9[l45] = 0.0;
	for (int l46 = 0; l46 < 2; l46 = l46 + 1) fRec38[l46] = 0.0;
	for (int l47 = 0; l47 < 2; l47 = l47 + 1) fRec1[l47] = 0.0;
	for (int l48 = 0; l48 < 2; l48 = l48 + 1) fRec0[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec39[l49] = 0.0;
	for (int l50 = 0; l50 < 2; l50 = l50 + 1) fRec40[l50] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = std::tan(97.38937226128358 / fConst0);
	double fConst2 = 1.0 / fConst1;
	double fConst3 = fConst2 + 1.0;
	fConst4 = (1.0 - fConst2) / fConst3;
	double fConst5 = 1.0 / std::tan(20517.741620594938 / fConst0);
	fConst6 = 1.0 - fConst5;
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
	double fConst28 = std::tan(47123.8898038469 / fConst0);
	fConst29 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst28));
	double fConst30 = 1.0 / fConst28;
	fConst31 = (fConst30 + -1.414213562373095) / fConst28 + 1.0;
	fConst32 = 1.0 / ((fConst30 + 1.414213562373095) / fConst28 + 1.0);
	fConst33 = 1.0 / (fConst1 * fConst3);
	fConst34 = 0.0 - fConst33;
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
	fConst58 = 1.0 / (fConst5 + 1.0);
	double fConst59 = 1.0 / std::tan(270.1769682087222 / fConst0);
	fConst60 = 1.0 - fConst59;
	fConst61 = 1.0 / (fConst59 + 1.0);
	double fConst62 = 3.141592653589793 / fConst0;
	fConst63 = 1.0 - fConst62;
	fConst64 = 1.0 / (fConst62 + 1.0);
	double fConst65 = 1.0 / std::tan(414.6902302738527 / fConst0);
	fConst66 = 1.0 - fConst65;
	fConst67 = 1.0 / (fConst65 + 1.0);
	double fConst68 = 1.0 / std::tan(609.4689747964198 / fConst0);
	fConst69 = 1.0 - fConst68;
	fConst70 = 1.0 / (fConst68 + 1.0);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fCheckbox0 (*fCheckbox0_)
#define fCheckbox1 (*fCheckbox1_)
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	int iSlow0 = int(double(fCheckbox0));
	int iSlow1 = int(double(fCheckbox1));
	double fSlow2 = 1.000000000000001e-05 * double(fVslider0);
	double fSlow3 = double(fVslider1);
	double fSlow4 = 2.0 * (fSlow3 + -0.5);
	double fSlow5 = 1.0 - std::max<double>(0.0, fSlow4);
	double fSlow6 = 1.25 * fSlow3;
	double fSlow7 = fConst13 * std::pow(1e+01, 0.9 * fSlow3);
	double fSlow8 = fConst13 * std::pow(1e+01, 2.0 * fSlow3);
	double fSlow9 = std::pow(1e+01, 0.8 * fSlow3);
	double fSlow10 = std::pow(1e+01, 1.2 * fSlow3);
	double fSlow11 = 1.0 - std::max<double>(0.0, -1.0 * fSlow4);
	double fSlow12 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider2));
	double fSlow13 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider3));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec14[0] = fSlow2 + 0.999 * fRec14[1];
		double fTemp0 = double(input0[i0]);
		double fTemp1 = fTemp0 * fRec14[0];
		double fTemp2 = fTemp0 * (1.0 - fRec14[0]);
		double fTemp3 = fTemp2 + 1e-15;
		fRec23[0] = fTemp1 + (1e-15 - fConst32 * (fConst31 * fRec23[2] + fConst29 * fRec23[1]));
		double fTemp4 = fRec23[2] + fRec23[0] + 2.0 * fRec23[1];
		fVec0[0] = fTemp4;
		fRec22[0] = fConst32 * (fConst33 * fTemp4 + fConst34 * fVec0[1]) - fConst4 * fRec22[1];
		fRec21[0] = 0.0 - fConst37 * (fConst35 * fRec21[1] - (fRec22[0] + fRec22[1]));
		fRec20[0] = fRec21[0] - fConst27 * (fConst26 * fRec20[2] + fConst24 * fRec20[1]);
		double fTemp5 = fRec20[2] + fRec20[0] + 2.0 * fRec20[1];
		fVec1[0] = fTemp5;
		fRec19[0] = 0.0 - fConst40 * (fConst38 * fRec19[1] - fConst27 * (fTemp5 + fVec1[1]));
		fRec18[0] = fRec19[0] - fConst20 * (fConst19 * fRec18[2] + fConst17 * fRec18[1]);
		double fTemp6 = fRec18[2] + fRec18[0] + 2.0 * fRec18[1];
		fVec2[0] = fTemp6;
		fRec17[0] = 0.0 - fConst43 * (fConst41 * fRec17[1] - fConst20 * (fTemp6 + fVec2[1]));
		fRec16[0] = fRec17[0] - fConst13 * (fConst12 * fRec16[2] + fConst10 * fRec16[1]);
		double fTemp7 = std::max<double>(-1.0, std::min<double>(1.0, fSlow7 * (fRec16[2] + fRec16[0] + 2.0 * fRec16[1])));
		fRec25[0] = fConst20 * (fConst45 * fTemp6 + fConst46 * fVec2[1]) - fConst44 * fRec25[1];
		fRec24[0] = fRec25[0] - fConst13 * (fConst12 * fRec24[2] + fConst10 * fRec24[1]);
		double fTemp8 = std::max<double>(-1.0, std::min<double>(1.0, fSlow8 * (fConst9 * fRec24[0] + fConst47 * fRec24[1] + fConst9 * fRec24[2])));
		double fTemp9 = fConst10 * fRec26[1];
		double fTemp10 = fConst17 * fRec27[1];
		fRec29[0] = fConst52 * fRec22[1] - fConst37 * (fConst35 * fRec29[1] - fConst25 * fRec22[0]);
		fRec28[0] = fRec29[0] - fConst27 * (fConst26 * fRec28[2] + fConst24 * fRec28[1]);
		fRec27[0] = fConst27 * (fConst23 * fRec28[0] + fConst53 * fRec28[1] + fConst23 * fRec28[2]) - fConst51 * (fConst50 * fRec27[2] + fTemp10);
		fRec26[0] = fRec27[2] + fConst51 * (fTemp10 + fConst50 * fRec27[0]) - fConst49 * (fConst48 * fRec26[2] + fTemp9);
		double fTemp11 = std::max<double>(-1.0, std::min<double>(1.0, fSlow9 * (fRec26[2] + fConst49 * (fTemp9 + fConst48 * fRec26[0]))));
		double fTemp12 = fConst10 * fRec30[1];
		fRec32[0] = fConst27 * (fConst55 * fTemp5 + fConst56 * fVec1[1]) - fConst54 * fRec32[1];
		fRec31[0] = fRec32[0] - fConst20 * (fConst19 * fRec31[2] + fConst17 * fRec31[1]);
		fRec30[0] = fConst20 * (fConst16 * fRec31[0] + fConst57 * fRec31[1] + fConst16 * fRec31[2]) - fConst49 * (fConst48 * fRec30[2] + fTemp12);
		double fTemp13 = std::max<double>(-1.0, std::min<double>(1.0, fSlow10 * (fRec30[2] + fConst49 * (fTemp12 + fConst48 * fRec30[0]))));
		double fTemp14 = 1.333521432 * fTemp13 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp13)) + 1.584893192 * (fTemp11 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp11)) + fTemp8 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp8))) + 1.2589412 * fTemp7 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp7));
		fVec3[0] = fTemp14;
		fRec15[0] = 0.0 - fConst58 * (fConst6 * fRec15[1] - (fTemp14 + fVec3[1]));
		double fTemp15 = fSlow11 * fRec15[0] + fTemp2 + fSlow6 * (4.0 * fTemp3 * (1.0 - std::fabs(fTemp3)) + (-1e-15 - fTemp2)) + fSlow5 * (fTemp1 + 1e-15) + 1e-15;
		fVec4[0] = fTemp15;
		fRec13[0] = 0.9302847925323914 * (fTemp15 + fVec4[1]) - 0.8605695850647829 * fRec13[1];
		fRec12[0] = fRec13[0] - (1.8405051250752198 * fRec12[1] + 0.8612942439318627 * fRec12[2]);
		double fTemp16 = 1.8508996845035413 * fRec12[1];
		double fTemp17 = 0.9254498422517706 * (fRec12[0] + fRec12[2]);
		double fTemp18 = (fTemp16 + fTemp17) / (Ranode(TUBE_TABLE_12AU7_68k, fRec11[1]) + 1e+05);
		fVec5[0] = fTemp18;
		fRec33[0] = fConst61 * (2.7e+03 * (fTemp18 + fVec5[1]) - fConst60 * fRec33[1]);
		fRec11[0] = Ftube(TUBE_TABLE_12AU7_68k, fTemp17 + fRec33[0] + fTemp16 + -3.718962) + -112.26066666666668;
		fRec10[0] = 0.025 * (fConst33 * fRec11[0] + fConst34 * fRec11[1]) - fConst4 * fRec10[1];
		fRec34[0] = fConst64 * (fConst63 * fRec34[1] + 0.025 * (fRec11[0] - fRec11[1]));
		fRec35[0] = fSlow12 + 0.999 * fRec35[1];
		double fTemp19 = fRec35[0] * ((iSlow1) ? fRec34[0] : fRec10[0]);
		fVec6[0] = fTemp19;
		fRec9[0] = fConst58 * (2.0 * (fTemp19 + fVec6[1]) - fConst6 * fRec9[1]);
		fRec8[0] = 0.9302847925323914 * (fRec9[0] + fRec9[1]) - 0.8605695850647829 * fRec8[1];
		fRec7[0] = fRec8[0] - (1.8405051250752198 * fRec7[1] + 0.8612942439318627 * fRec7[2]);
		double fTemp20 = 1.8508996845035413 * fRec7[1];
		double fTemp21 = 0.9254498422517706 * (fRec7[0] + fRec7[2]);
		double fTemp22 = (fTemp20 + fTemp21) / (Ranode(TUBE_TABLE_12AU7_250k, fRec6[1]) + 1e+05);
		fVec7[0] = fTemp22;
		fRec36[0] = fConst67 * (1.5e+03 * (fTemp22 + fVec7[1]) - fConst66 * fRec36[1]);
		fRec6[0] = Ftube(TUBE_TABLE_12AU7_250k, fTemp21 + fRec36[0] + fTemp20 + -2.314844) + -95.67706666666666;
		fRec5[0] = 0.025 * (fConst33 * fRec6[0] + fConst34 * fRec6[1]) - fConst4 * fRec5[1];
		fRec37[0] = fConst64 * (fConst63 * fRec37[1] + 0.025 * (fRec6[0] - fRec6[1]));
		double fTemp23 = fRec35[0] * ((iSlow1) ? fRec37[0] : fRec5[0]);
		fVec8[0] = fTemp23;
		fRec4[0] = fConst58 * (2.0 * (fTemp23 + fVec8[1]) - fConst6 * fRec4[1]);
		fRec3[0] = 0.9302847925323914 * (fRec4[0] + fRec4[1]) - 0.8605695850647829 * fRec3[1];
		fRec2[0] = fRec3[0] - (1.8405051250752198 * fRec2[1] + 0.8612942439318627 * fRec2[2]);
		double fTemp24 = 1.8508996845035413 * fRec2[1];
		double fTemp25 = 0.9254498422517706 * (fRec2[0] + fRec2[2]);
		double fTemp26 = (fTemp24 + fTemp25) / (Ranode(TUBE_TABLE_12AU7_250k, fRec1[1]) + 1e+05);
		fVec9[0] = fTemp26;
		fRec38[0] = fConst70 * (8.2e+02 * (fTemp26 + fVec9[1]) - fConst69 * fRec38[1]);
		fRec1[0] = Ftube(TUBE_TABLE_12AU7_250k, fTemp25 + fRec38[0] + fTemp24 + -1.356567) + -84.565;
		fRec0[0] = 0.025 * (fConst33 * fRec1[0] + fConst34 * fRec1[1]) - fConst4 * fRec0[1];
		fRec39[0] = fConst64 * (fConst63 * fRec39[1] + 0.025 * (fRec1[0] - fRec1[1]));
		fRec40[0] = fSlow13 + 0.999 * fRec40[1];
		output0[i0] = FAUSTFLOAT(2.0 * fRec40[0] * ((iSlow0) ? fRec39[0] : fRec0[0]));
		fRec14[1] = fRec14[0];
		fRec23[2] = fRec23[1];
		fRec23[1] = fRec23[0];
		fVec0[1] = fVec0[0];
		fRec22[1] = fRec22[0];
		fRec21[1] = fRec21[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fVec1[1] = fVec1[0];
		fRec19[1] = fRec19[0];
		fRec18[2] = fRec18[1];
		fRec18[1] = fRec18[0];
		fVec2[1] = fVec2[0];
		fRec17[1] = fRec17[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fVec3[1] = fVec3[0];
		fRec15[1] = fRec15[0];
		fVec4[1] = fVec4[0];
		fRec13[1] = fRec13[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fVec5[1] = fVec5[0];
		fRec33[1] = fRec33[0];
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
		fRec34[1] = fRec34[0];
		fRec35[1] = fRec35[0];
		fVec6[1] = fVec6[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fVec7[1] = fVec7[0];
		fRec36[1] = fRec36[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec37[1] = fRec37[0];
		fVec8[1] = fVec8[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fVec9[1] = fVec9[0];
		fRec38[1] = fRec38[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec39[1] = fRec39[0];
		fRec40[1] = fRec40[0];
	}
#undef fCheckbox0
#undef fCheckbox1
#undef fVslider0
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
		fVslider1_ = (float*)data; // , 0.35, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fVslider0_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
		break;
	case PREGAIN: 
		fVslider2_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
		break;
	case GAIN1: 
		fVslider3_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
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
   WET_DRY, 
   HIGHGAIN, 
   PREGAIN, 
   GAIN1, 
} PortIndex;
*/

} // end namespace gxamp3
