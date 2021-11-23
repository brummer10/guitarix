// generated from file '../src/LV2/faust/gxamp3.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxamp3 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst2;
	double fConst3;
	double fConst5;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec5[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst6;
	double fConst9;
	double fConst11;
	double fConst13;
	double fConst14;
	double fConst16;
	double fConst18;
	double fConst19;
	double fConst22;
	double fConst26;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec23[2];
	double fConst27;
	double fConst28;
	double fRec22[3];
	double fVec0[2];
	double fConst29;
	double fConst30;
	double fRec21[2];
	double fRec20[2];
	double fConst31;
	double fConst33;
	double fConst34;
	double fRec19[3];
	double fVec1[2];
	double fConst35;
	double fConst36;
	double fConst37;
	double fRec18[2];
	double fConst38;
	double fConst39;
	double fRec17[3];
	double fConst40;
	double fConst44;
	double fConst45;
	double fConst46;
	double fConst48;
	double fConst49;
	double fRec16[3];
	double fConst50;
	double fRec27[2];
	double fRec26[3];
	double fConst51;
	double fConst52;
	double fConst53;
	double fRec25[3];
	double fRec24[3];
	double fConst54;
	double fConst55;
	double fConst56;
	double fRec31[2];
	double fRec30[3];
	double fVec2[2];
	double fConst57;
	double fConst58;
	double fRec29[2];
	double fConst59;
	double fRec28[3];
	double fConst60;
	double fConst61;
	double fRec33[2];
	double fRec32[3];
	double fVec3[2];
	double fRec15[2];
	double fVec4[2];
	double fRec14[2];
	double fRec13[3];
	double fConst63;
	double fVec5[2];
	double fConst64;
	double fRec34[2];
	double fRec12[2];
	double fRec11[2];
	double fVec6[2];
	double fRec10[2];
	double fRec9[2];
	double fRec8[3];
	double fConst66;
	double fVec7[2];
	double fConst67;
	double fRec35[2];
	double fRec7[2];
	double fRec6[2];
	double fVec8[2];
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fConst69;
	double fVec9[2];
	double fConst70;
	double fRec36[2];
	double fRec1[2];
	double fRec0[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec37[2];

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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec5[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec23[l1] = 0.0;
	for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) fRec22[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fVec0[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec21[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec20[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec19[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fVec1[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec18[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec17[l9] = 0.0;
	for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) fRec16[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec27[l11] = 0.0;
	for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) fRec26[l12] = 0.0;
	for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) fRec25[l13] = 0.0;
	for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) fRec24[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec31[l15] = 0.0;
	for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) fRec30[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fVec2[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec29[l18] = 0.0;
	for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) fRec28[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fRec33[l20] = 0.0;
	for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) fRec32[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fVec3[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fRec15[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fVec4[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fRec14[l25] = 0.0;
	for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) fRec13[l26] = 0.0;
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) fVec5[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec34[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fRec12[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec11[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fVec6[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fRec10[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fRec9[l33] = 0.0;
	for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) fRec8[l34] = 0.0;
	for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) fVec7[l35] = 0.0;
	for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) fRec35[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fRec7[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fRec6[l38] = 0.0;
	for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) fVec8[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fRec4[l40] = 0.0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) fRec3[l41] = 0.0;
	for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) fRec2[l42] = 0.0;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fVec9[l43] = 0.0;
	for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) fRec36[l44] = 0.0;
	for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) fRec1[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec0[l46] = 0.0;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) fRec37[l47] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = (3.1415926535897931 / fConst0);
	fConst2 = (1.0 / (fConst1 + 1.0));
	fConst3 = (1.0 - fConst1);
	double fConst4 = (1.0 / std::tan((20517.741620594938 / fConst0)));
	fConst5 = (1.0 / (fConst4 + 1.0));
	fConst6 = (1.0 - fConst4);
	double fConst7 = std::tan((3769.9111843077517 / fConst0));
	double fConst8 = (1.0 / fConst7);
	fConst9 = (1.0 / (((fConst8 + 1.0000000000000004) / fConst7) + 1.0));
	double fConst10 = mydsp_faustpower2_f(fConst7);
	fConst11 = (1.0 / fConst10);
	double fConst12 = std::tan((10053.096491487338 / fConst0));
	fConst13 = (1.0 / fConst12);
	fConst14 = (1.0 / (((fConst13 + 1.0000000000000004) / fConst12) + 1.0));
	double fConst15 = (fConst8 + 1.0);
	fConst16 = (1.0 / (fConst7 * fConst15));
	double fConst17 = (fConst13 + 1.0);
	fConst18 = (1.0 / fConst17);
	fConst19 = (1.0 - fConst13);
	double fConst20 = std::tan((47123.889803846898 / fConst0));
	double fConst21 = (1.0 / fConst20);
	fConst22 = (1.0 / (((fConst21 + 1.4142135623730949) / fConst20) + 1.0));
	double fConst23 = std::tan((97.389372261283583 / fConst0));
	double fConst24 = (1.0 / fConst23);
	double fConst25 = (fConst24 + 1.0);
	fConst26 = (1.0 / (fConst23 * fConst25));
	fConst27 = (((fConst21 + -1.4142135623730949) / fConst20) + 1.0);
	fConst28 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fConst20))));
	fConst29 = (0.0 - fConst26);
	fConst30 = ((1.0 - fConst24) / fConst25);
	fConst31 = (((fConst13 + -1.0000000000000004) / fConst12) + 1.0);
	double fConst32 = mydsp_faustpower2_f(fConst12);
	fConst33 = (1.0 / fConst32);
	fConst34 = (2.0 * (1.0 - fConst33));
	fConst35 = (0.0 - fConst16);
	fConst36 = (1.0 - fConst8);
	fConst37 = (fConst36 / fConst15);
	fConst38 = (((fConst8 + -1.0000000000000004) / fConst7) + 1.0);
	fConst39 = (2.0 * (1.0 - fConst11));
	fConst40 = (0.0 - (2.0 / fConst10));
	double fConst41 = std::tan((942.47779607693792 / fConst0));
	double fConst42 = (1.0 / fConst41);
	double fConst43 = (fConst42 + 1.0);
	fConst44 = (1.0 / ((fConst43 / fConst41) + 1.0));
	fConst45 = (1.0 - fConst42);
	fConst46 = (1.0 - (fConst45 / fConst41));
	double fConst47 = mydsp_faustpower2_f(fConst41);
	fConst48 = (1.0 / fConst47);
	fConst49 = (2.0 * (1.0 - fConst48));
	fConst50 = (0.0 - (1.0 / (fConst12 * fConst17)));
	fConst51 = (0.0 - (2.0 / fConst32));
	fConst52 = (1.0 / ((fConst15 / fConst7) + 1.0));
	fConst53 = (1.0 - (fConst36 / fConst7));
	fConst54 = (1.0 / (((fConst42 + 1.0000000000000004) / fConst41) + 1.0));
	fConst55 = (1.0 / (fConst41 * fConst43));
	fConst56 = (1.0 / fConst15);
	fConst57 = (0.0 - fConst55);
	fConst58 = (fConst45 / fConst43);
	fConst59 = (((fConst42 + -1.0000000000000004) / fConst41) + 1.0);
	fConst60 = (0.0 - (2.0 / fConst47));
	fConst61 = (1.0 / fConst43);
	double fConst62 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst63 = (1.0 / (fConst62 + 1.0));
	fConst64 = (1.0 - fConst62);
	double fConst65 = (1.0 / std::tan((414.69023027385271 / fConst0)));
	fConst66 = (1.0 / (fConst65 + 1.0));
	fConst67 = (1.0 - fConst65);
	double fConst68 = (1.0 / std::tan((609.46897479641984 / fConst0)));
	fConst69 = (1.0 / (fConst68 + 1.0));
	fConst70 = (1.0 - fConst68);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	double fSlow0 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider0))));
	double fSlow1 = double(fVslider1);
	double fSlow2 = (2.0 * (fSlow1 + -0.5));
	double fSlow3 = (1.0 - std::max<double>(0.0, (-1.0 * fSlow2)));
	double fSlow4 = std::pow(10.0, (1.2 * fSlow1));
	double fSlow5 = (1.0000000000000009e-05 * double(fVslider2));
	double fSlow6 = std::pow(10.0, (0.80000000000000004 * fSlow1));
	double fSlow7 = (fConst54 * std::pow(10.0, (2.0 * fSlow1)));
	double fSlow8 = (fConst54 * std::pow(10.0, (0.90000000000000002 * fSlow1)));
	double fSlow9 = (1.25 * fSlow1);
	double fSlow10 = (1.0 - std::max<double>(0.0, fSlow2));
	double fSlow11 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider3))));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		fRec5[0] = (fSlow0 + (0.999 * fRec5[1]));
		double fTemp0 = double(input0[i0]);
		fRec23[0] = (fSlow5 + (0.999 * fRec23[1]));
		double fTemp1 = (fTemp0 * fRec23[0]);
		fRec22[0] = (fTemp1 + (1.0000000000000001e-15 - (fConst22 * ((fConst27 * fRec22[2]) + (fConst28 * fRec22[1])))));
		double fTemp2 = (fRec22[2] + (fRec22[0] + (2.0 * fRec22[1])));
		fVec0[0] = fTemp2;
		fRec21[0] = ((fConst22 * ((fConst26 * fTemp2) + (fConst29 * fVec0[1]))) - (fConst30 * fRec21[1]));
		fRec20[0] = (0.0 - (fConst18 * ((fConst19 * fRec20[1]) - (fRec21[0] + fRec21[1]))));
		fRec19[0] = (fRec20[0] - (fConst14 * ((fConst31 * fRec19[2]) + (fConst34 * fRec19[1]))));
		double fTemp3 = (fRec19[2] + (fRec19[0] + (2.0 * fRec19[1])));
		fVec1[0] = fTemp3;
		fRec18[0] = ((fConst14 * ((fConst16 * fTemp3) + (fConst35 * fVec1[1]))) - (fConst37 * fRec18[1]));
		fRec17[0] = (fRec18[0] - (fConst9 * ((fConst38 * fRec17[2]) + (fConst39 * fRec17[1]))));
		double fTemp4 = (fConst49 * fRec16[1]);
		fRec16[0] = ((fConst9 * (((fConst11 * fRec17[0]) + (fConst40 * fRec17[1])) + (fConst11 * fRec17[2]))) - (fConst44 * ((fConst46 * fRec16[2]) + fTemp4)));
		double fTemp5 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow4 * (fRec16[2] + (fConst44 * (fTemp4 + (fConst46 * fRec16[0])))))));
		fRec27[0] = ((fConst50 * fRec21[1]) - (fConst18 * ((fConst19 * fRec27[1]) - (fConst13 * fRec21[0]))));
		fRec26[0] = (fRec27[0] - (fConst14 * ((fConst31 * fRec26[2]) + (fConst34 * fRec26[1]))));
		double fTemp6 = (fConst39 * fRec25[1]);
		fRec25[0] = ((fConst14 * (((fConst33 * fRec26[0]) + (fConst51 * fRec26[1])) + (fConst33 * fRec26[2]))) - (fConst52 * ((fConst53 * fRec25[2]) + fTemp6)));
		double fTemp7 = (fConst49 * fRec24[1]);
		fRec24[0] = ((fRec25[2] + (fConst52 * (fTemp6 + (fConst53 * fRec25[0])))) - (fConst44 * ((fConst46 * fRec24[2]) + fTemp7)));
		double fTemp8 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow6 * (fRec24[2] + (fConst44 * (fTemp7 + (fConst46 * fRec24[0])))))));
		fRec31[0] = (0.0 - (fConst56 * ((fConst36 * fRec31[1]) - (fConst14 * (fTemp3 + fVec1[1])))));
		fRec30[0] = (fRec31[0] - (fConst9 * ((fConst38 * fRec30[2]) + (fConst39 * fRec30[1]))));
		double fTemp9 = (fRec30[2] + (fRec30[0] + (2.0 * fRec30[1])));
		fVec2[0] = fTemp9;
		fRec29[0] = ((fConst9 * ((fConst55 * fTemp9) + (fConst57 * fVec2[1]))) - (fConst58 * fRec29[1]));
		fRec28[0] = (fRec29[0] - (fConst54 * ((fConst59 * fRec28[2]) + (fConst49 * fRec28[1]))));
		double fTemp10 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow7 * (((fConst48 * fRec28[0]) + (fConst60 * fRec28[1])) + (fConst48 * fRec28[2])))));
		fRec33[0] = (0.0 - (fConst61 * ((fConst45 * fRec33[1]) - (fConst9 * (fTemp9 + fVec2[1])))));
		fRec32[0] = (fRec33[0] - (fConst54 * ((fConst59 * fRec32[2]) + (fConst49 * fRec32[1]))));
		double fTemp11 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow8 * (fRec32[2] + (fRec32[0] + (2.0 * fRec32[1]))))));
		double fTemp12 = (((1.333521432 * (fTemp5 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp5))))) + (1.584893192 * ((fTemp8 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp8)))) + (fTemp10 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp10))))))) + (1.2589412 * (fTemp11 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp11))))));
		fVec3[0] = fTemp12;
		fRec15[0] = (0.0 - (fConst5 * ((fConst6 * fRec15[1]) - (fTemp12 + fVec3[1]))));
		double fTemp13 = (fTemp0 * (1.0 - fRec23[0]));
		double fTemp14 = (fTemp13 + 1.0000000000000001e-15);
		double fTemp15 = (((fSlow3 * fRec15[0]) + ((fTemp13 + (fSlow9 * ((4.0 * (fTemp14 * (1.0 - std::fabs(fTemp14)))) + (-1.0000000000000001e-15 - fTemp13)))) + (fSlow10 * (fTemp1 + 1.0000000000000001e-15)))) + 1.0000000000000001e-15);
		fVec4[0] = fTemp15;
		fRec14[0] = ((0.93028479253239138 * (fTemp15 + fVec4[1])) - (0.86056958506478287 * fRec14[1]));
		fRec13[0] = (fRec14[0] - ((1.8405051250752198 * fRec13[1]) + (0.86129424393186271 * fRec13[2])));
		double fTemp16 = (0.92544984225177063 * (fRec13[0] + fRec13[2]));
		double fTemp17 = (1.8508996845035413 * fRec13[1]);
		double fTemp18 = ((fTemp17 + fTemp16) / (double(Ranode(int(TUBE_TABLE_12AU7_68k), double(fRec12[1]))) + 100000.0));
		fVec5[0] = fTemp18;
		fRec34[0] = (fConst63 * ((2700.0 * (fTemp18 + fVec5[1])) - (fConst64 * fRec34[1])));
		fRec12[0] = (double(Ftube(int(TUBE_TABLE_12AU7_68k), double(((fTemp16 + (fRec34[0] + fTemp17)) + -3.7189619999999999)))) + -112.26066666666668);
		fRec11[0] = (fConst2 * ((fConst3 * fRec11[1]) + (0.025000000000000001 * (fRec12[0] - fRec12[1]))));
		double fTemp19 = (fRec11[0] * fRec5[0]);
		fVec6[0] = fTemp19;
		fRec10[0] = (fConst5 * ((2.0 * (fTemp19 + fVec6[1])) - (fConst6 * fRec10[1])));
		fRec9[0] = ((0.93028479253239138 * (fRec10[0] + fRec10[1])) - (0.86056958506478287 * fRec9[1]));
		fRec8[0] = (fRec9[0] - ((1.8405051250752198 * fRec8[1]) + (0.86129424393186271 * fRec8[2])));
		double fTemp20 = (0.92544984225177063 * (fRec8[0] + fRec8[2]));
		double fTemp21 = (1.8508996845035413 * fRec8[1]);
		double fTemp22 = ((fTemp21 + fTemp20) / (double(Ranode(int(TUBE_TABLE_12AU7_250k), double(fRec7[1]))) + 100000.0));
		fVec7[0] = fTemp22;
		fRec35[0] = (fConst66 * ((1500.0 * (fTemp22 + fVec7[1])) - (fConst67 * fRec35[1])));
		fRec7[0] = (double(Ftube(int(TUBE_TABLE_12AU7_250k), double(((fTemp20 + (fRec35[0] + fTemp21)) + -2.3148439999999999)))) + -95.677066666666661);
		fRec6[0] = (fConst2 * ((fConst3 * fRec6[1]) + (0.025000000000000001 * (fRec7[0] - fRec7[1]))));
		double fTemp23 = (fRec5[0] * fRec6[0]);
		fVec8[0] = fTemp23;
		fRec4[0] = (fConst5 * ((2.0 * (fTemp23 + fVec8[1])) - (fConst6 * fRec4[1])));
		fRec3[0] = ((0.93028479253239138 * (fRec4[0] + fRec4[1])) - (0.86056958506478287 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.86129424393186271 * fRec2[2])));
		double fTemp24 = (0.92544984225177063 * (fRec2[0] + fRec2[2]));
		double fTemp25 = (1.8508996845035413 * fRec2[1]);
		double fTemp26 = ((fTemp25 + fTemp24) / (double(Ranode(int(TUBE_TABLE_12AU7_250k), double(fRec1[1]))) + 100000.0));
		fVec9[0] = fTemp26;
		fRec36[0] = (fConst69 * ((820.0 * (fTemp26 + fVec9[1])) - (fConst70 * fRec36[1])));
		fRec1[0] = (double(Ftube(int(TUBE_TABLE_12AU7_250k), double(((fTemp24 + (fRec36[0] + fTemp25)) + -1.3565670000000001)))) + -84.564999999999998);
		fRec0[0] = (fConst2 * ((fConst3 * fRec0[1]) + (0.025000000000000001 * (fRec1[0] - fRec1[1]))));
		fRec37[0] = (fSlow11 + (0.999 * fRec37[1]));
		output0[i0] = FAUSTFLOAT((2.0 * (fRec0[0] * fRec37[0])));
		fRec5[1] = fRec5[0];
		fRec23[1] = fRec23[0];
		fRec22[2] = fRec22[1];
		fRec22[1] = fRec22[0];
		fVec0[1] = fVec0[0];
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fVec1[1] = fVec1[0];
		fRec18[1] = fRec18[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fVec2[1] = fVec2[0];
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fVec3[1] = fVec3[0];
		fRec15[1] = fRec15[0];
		fVec4[1] = fVec4[0];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fVec5[1] = fVec5[0];
		fRec34[1] = fRec34[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fVec6[1] = fVec6[0];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fVec7[1] = fVec7[0];
		fRec35[1] = fRec35[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fVec8[1] = fVec8[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fVec9[1] = fVec9[0];
		fRec36[1] = fRec36[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec37[1] = fRec37[0];
	}
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
	case DRIVE: 
		fVslider1_ = (float*)data; // , 0.34999999999999998, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fVslider2_ = (float*)data; // , 100.0, 0.0, 100.0, 1.0 
		break;
	case PREGAIN: 
		fVslider0_ = (float*)data; // , -6.0, -20.0, 20.0, 0.10000000000000001 
		break;
	case GAIN1: 
		fVslider3_ = (float*)data; // , -6.0, -20.0, 20.0, 0.10000000000000001 
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
   PREGAIN, 
   GAIN1, 
} PortIndex;
*/

} // end namespace gxamp3
