// generated from file '../src/LV2/faust/gxamp5.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxamp5 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec4[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec19[2];
	double fVec0[2];
	double fRec18[2];
	double fRec17[3];
	double fConst4;
	double fConst5;
	double fVec1[2];
	double fConst6;
	double fRec20[2];
	double fRec16[2];
	double fConst7;
	double fConst8;
	double fRec15[2];
	double fConst9;
	double fConst10;
	double fConst11;
	double fRec21[2];
	double fVec2[2];
	double fConst12;
	double fConst13;
	double fConst14;
	double fRec14[2];
	double fRec13[2];
	double fRec12[3];
	double fConst15;
	double fConst16;
	double fVec3[2];
	double fConst17;
	double fRec22[2];
	double fRec11[2];
	double fRec10[2];
	double fRec23[2];
	double fVec4[2];
	double fRec9[2];
	double fRec8[3];
	double fConst18;
	double fConst19;
	double fVec5[2];
	double fConst20;
	double fRec24[2];
	double fRec7[2];
	double fRec6[2];
	double fRec25[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec26[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
	double fConst46;
	double fConst47;
	double fRec35[3];
	double fVec6[2];
	double fConst48;
	double fRec34[2];
	double fConst49;
	double fConst50;
	double fRec33[2];
	double fRec32[3];
	double fVec7[2];
	double fConst51;
	double fConst52;
	double fConst53;
	double fRec31[2];
	double fRec30[3];
	double fVec8[2];
	double fConst54;
	double fConst55;
	double fConst56;
	double fRec29[2];
	double fRec28[3];
	double fConst57;
	double fRec37[2];
	double fRec36[3];
	double fConst58;
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;
	double fRec41[2];
	double fRec40[3];
	double fConst63;
	double fRec39[3];
	double fRec38[3];
	double fConst64;
	double fRec44[2];
	double fRec43[3];
	double fConst65;
	double fRec42[3];
	double fVec9[2];
	double fRec27[2];
	double fVec10[2];
	double fRec5[2];
	double fVec11[2];
	double fRec3[2];
	double fRec2[3];
	double fVec12[2];
	double fRec45[2];
	double fRec1[2];
	double fRec0[2];
	double fRec46[2];
	double fVec13[2];
	double fRec49[2];
	double fRec48[2];
	double fRec47[2];
	double fRec50[2];

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
	id = "pre 12ax7/ master 6V6";
	name = N_("pre 12ax7/ master 6V6");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec4[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec19[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fVec0[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec18[l3] = 0.0;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRec17[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fVec1[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec20[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec16[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec15[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec21[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fVec2[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec14[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec13[l12] = 0.0;
	for (int l13 = 0; l13 < 3; l13 = l13 + 1) fRec12[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fVec3[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec22[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec11[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec10[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec23[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fVec4[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec9[l20] = 0.0;
	for (int l21 = 0; l21 < 3; l21 = l21 + 1) fRec8[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fVec5[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec24[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec7[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec6[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec25[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec26[l27] = 0.0;
	for (int l28 = 0; l28 < 3; l28 = l28 + 1) fRec35[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fVec6[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec34[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec33[l31] = 0.0;
	for (int l32 = 0; l32 < 3; l32 = l32 + 1) fRec32[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fVec7[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fRec31[l34] = 0.0;
	for (int l35 = 0; l35 < 3; l35 = l35 + 1) fRec30[l35] = 0.0;
	for (int l36 = 0; l36 < 2; l36 = l36 + 1) fVec8[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec29[l37] = 0.0;
	for (int l38 = 0; l38 < 3; l38 = l38 + 1) fRec28[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec37[l39] = 0.0;
	for (int l40 = 0; l40 < 3; l40 = l40 + 1) fRec36[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec41[l41] = 0.0;
	for (int l42 = 0; l42 < 3; l42 = l42 + 1) fRec40[l42] = 0.0;
	for (int l43 = 0; l43 < 3; l43 = l43 + 1) fRec39[l43] = 0.0;
	for (int l44 = 0; l44 < 3; l44 = l44 + 1) fRec38[l44] = 0.0;
	for (int l45 = 0; l45 < 2; l45 = l45 + 1) fRec44[l45] = 0.0;
	for (int l46 = 0; l46 < 3; l46 = l46 + 1) fRec43[l46] = 0.0;
	for (int l47 = 0; l47 < 3; l47 = l47 + 1) fRec42[l47] = 0.0;
	for (int l48 = 0; l48 < 2; l48 = l48 + 1) fVec9[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fRec27[l49] = 0.0;
	for (int l50 = 0; l50 < 2; l50 = l50 + 1) fVec10[l50] = 0.0;
	for (int l51 = 0; l51 < 2; l51 = l51 + 1) fRec5[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fVec11[l52] = 0.0;
	for (int l53 = 0; l53 < 2; l53 = l53 + 1) fRec3[l53] = 0.0;
	for (int l54 = 0; l54 < 3; l54 = l54 + 1) fRec2[l54] = 0.0;
	for (int l55 = 0; l55 < 2; l55 = l55 + 1) fVec12[l55] = 0.0;
	for (int l56 = 0; l56 < 2; l56 = l56 + 1) fRec45[l56] = 0.0;
	for (int l57 = 0; l57 < 2; l57 = l57 + 1) fRec1[l57] = 0.0;
	for (int l58 = 0; l58 < 2; l58 = l58 + 1) fRec0[l58] = 0.0;
	for (int l59 = 0; l59 < 2; l59 = l59 + 1) fRec46[l59] = 0.0;
	for (int l60 = 0; l60 < 2; l60 = l60 + 1) fVec13[l60] = 0.0;
	for (int l61 = 0; l61 < 2; l61 = l61 + 1) fRec49[l61] = 0.0;
	for (int l62 = 0; l62 < 2; l62 = l62 + 1) fRec48[l62] = 0.0;
	for (int l63 = 0; l63 < 2; l63 = l63 + 1) fRec47[l63] = 0.0;
	for (int l64 = 0; l64 < 2; l64 = l64 + 1) fRec50[l64] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = std::tan(97.38937226128358 / fConst0);
	fConst2 = 1.0 / fConst1;
	fConst3 = 1.0 - fConst2;
	fConst4 = 1.0 / std::tan(270.1769682087222 / fConst0);
	fConst5 = 1.0 - fConst4;
	fConst6 = 1.0 / (fConst4 + 1.0);
	fConst7 = 0.025 / fConst1;
	fConst8 = 1.0 / (fConst2 + 1.0);
	fConst9 = 3.141592653589793 / fConst0;
	fConst10 = 1.0 - fConst9;
	fConst11 = 1.0 / (fConst9 + 1.0);
	fConst12 = 1.0 / std::tan(20517.741620594938 / fConst0);
	fConst13 = 1.0 - fConst12;
	fConst14 = 1.0 / (fConst12 + 1.0);
	fConst15 = 1.0 / std::tan(414.6902302738527 / fConst0);
	fConst16 = 1.0 - fConst15;
	fConst17 = 1.0 / (fConst15 + 1.0);
	fConst18 = 1.0 / std::tan(609.4689747964198 / fConst0);
	fConst19 = 1.0 - fConst18;
	fConst20 = 1.0 / (fConst18 + 1.0);
	fConst21 = std::tan(942.4777960769379 / fConst0);
	fConst22 = mydsp_faustpower2_f(fConst21);
	fConst23 = 2.0 * (1.0 - 1.0 / fConst22);
	fConst24 = 1.0 / fConst21;
	fConst25 = (fConst24 + -1.0000000000000004) / fConst21 + 1.0;
	fConst26 = (fConst24 + 1.0000000000000004) / fConst21 + 1.0;
	fConst27 = 1.0 / fConst26;
	fConst28 = std::tan(3769.9111843077517 / fConst0);
	fConst29 = mydsp_faustpower2_f(fConst28);
	fConst30 = 2.0 * (1.0 - 1.0 / fConst29);
	fConst31 = 1.0 / fConst28;
	fConst32 = (fConst31 + -1.0000000000000004) / fConst28 + 1.0;
	fConst33 = (fConst31 + 1.0000000000000004) / fConst28 + 1.0;
	fConst34 = 1.0 / fConst33;
	fConst35 = std::tan(10053.096491487338 / fConst0);
	fConst36 = mydsp_faustpower2_f(fConst35);
	fConst37 = 2.0 * (1.0 - 1.0 / fConst36);
	fConst38 = 1.0 / fConst35;
	fConst39 = (fConst38 + -1.0000000000000004) / fConst35 + 1.0;
	fConst40 = (fConst38 + 1.0000000000000004) / fConst35 + 1.0;
	fConst41 = 1.0 / fConst40;
	fConst42 = std::tan(47123.8898038469 / fConst0);
	fConst43 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst42));
	fConst44 = 1.0 / fConst42;
	fConst45 = (fConst44 + -1.414213562373095) / fConst42 + 1.0;
	fConst46 = (fConst44 + 1.414213562373095) / fConst42 + 1.0;
	fConst47 = 1.0 / fConst46;
	fConst48 = 1.0 / (fConst1 * fConst46);
	fConst49 = 1.0 - fConst38;
	fConst50 = 1.0 / (fConst38 + 1.0);
	fConst51 = 1.0 - fConst31;
	fConst52 = fConst31 + 1.0;
	fConst53 = 1.0 / fConst52;
	fConst54 = 1.0 - fConst24;
	fConst55 = fConst24 + 1.0;
	fConst56 = 1.0 / fConst55;
	fConst57 = 1.0 / (fConst21 * fConst33);
	fConst58 = 1.0 / (fConst22 * fConst26);
	fConst59 = 1.0 - fConst54 / fConst21;
	fConst60 = 1.0 / (fConst55 / fConst21 + 1.0);
	fConst61 = 1.0 - fConst51 / fConst28;
	fConst62 = 1.0 / (fConst52 / fConst28 + 1.0);
	fConst63 = 1.0 / (fConst36 * fConst40);
	fConst64 = 1.0 / (fConst28 * fConst40);
	fConst65 = 1.0 / (fConst29 * fConst33);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fCheckbox0 (*fCheckbox0_)
#define fVslider0 (*fVslider0_)
#define fCheckbox1 (*fCheckbox1_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	int iSlow0 = int(double(fCheckbox0));
	double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
	int iSlow2 = int(double(fCheckbox1));
	double fSlow3 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider1));
	double fSlow4 = 1.000000000000001e-05 * double(fVslider2);
	double fSlow5 = double(fVslider3);
	double fSlow6 = 2.0 * (fSlow5 + -0.5);
	double fSlow7 = 1.0 - std::max<double>(0.0, fSlow6);
	double fSlow8 = 1.25 * fSlow5;
	double fSlow9 = fConst27 * std::pow(1e+01, 0.9 * fSlow5);
	double fSlow10 = fConst58 * std::pow(1e+01, 2.0 * fSlow5);
	double fSlow11 = std::pow(1e+01, 0.8 * fSlow5);
	double fSlow12 = std::pow(1e+01, 1.2 * fSlow5);
	double fSlow13 = 1.0 - std::max<double>(0.0, -fSlow6);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec4[0] = fSlow1 + 0.999 * fRec4[1];
		fRec19[0] = fSlow3 + 0.999 * fRec19[1];
		double fTemp0 = double(input0[i0]) * fRec19[0];
		fVec0[0] = fTemp0;
		fRec18[0] = 0.9302847925323914 * (fTemp0 + fVec0[1]) - 0.8605695850647829 * fRec18[1];
		fRec17[0] = fRec18[0] - (1.8405051250752198 * fRec17[1] + 0.8612942439318627 * fRec17[2]);
		double fTemp1 = 1.8508996845035413 * fRec17[1];
		double fTemp2 = 0.9254498422517706 * (fRec17[0] + fRec17[2]);
		double fTemp3 = (fTemp1 + fTemp2) / (Ranode(TUBE_TABLE_12AX7_68k, fRec16[1]) + 1e+05);
		fVec1[0] = fTemp3;
		fRec20[0] = fConst6 * (2.7e+03 * (fTemp3 + fVec1[1]) - fConst5 * fRec20[1]);
		fRec16[0] = Ftube(TUBE_TABLE_12AX7_68k, fTemp2 + fRec20[0] + fTemp1 + -1.581656) + -191.42014814814814;
		double fTemp4 = fRec16[0] - fRec16[1];
		fRec15[0] = fConst8 * (fConst7 * fTemp4 - fConst3 * fRec15[1]);
		fRec21[0] = fConst11 * (fConst10 * fRec21[1] + 0.025 * fTemp4);
		double fTemp5 = ((iSlow2) ? fRec21[0] : fRec15[0]);
		fVec2[0] = fTemp5;
		fRec14[0] = -(fConst14 * (fConst13 * fRec14[1] - (fTemp5 + fVec2[1])));
		fRec13[0] = 0.9302847925323914 * (fRec14[0] + fRec14[1]) - 0.8605695850647829 * fRec13[1];
		fRec12[0] = fRec13[0] - (1.8405051250752198 * fRec12[1] + 0.8612942439318627 * fRec12[2]);
		double fTemp6 = 1.8508996845035413 * fRec12[1];
		double fTemp7 = 0.9254498422517706 * (fRec12[0] + fRec12[2]);
		double fTemp8 = (fTemp6 + fTemp7) / (Ranode(TUBE_TABLE_12AX7_250k, fRec11[1]) + 1e+05);
		fVec3[0] = fTemp8;
		fRec22[0] = fConst17 * (1.5e+03 * (fTemp8 + fVec3[1]) - fConst16 * fRec22[1]);
		fRec11[0] = Ftube(TUBE_TABLE_12AX7_250k, fTemp7 + fRec22[0] + fTemp6 + -1.204285) + -169.71433333333334;
		double fTemp9 = fRec11[0] - fRec11[1];
		fRec10[0] = fConst8 * (fConst7 * fTemp9 - fConst3 * fRec10[1]);
		fRec23[0] = fConst11 * (fConst10 * fRec23[1] + 0.025 * fTemp9);
		double fTemp10 = ((iSlow2) ? fRec23[0] : fRec10[0]);
		fVec4[0] = fTemp10;
		fRec9[0] = 0.9302847925323914 * (fTemp10 + fVec4[1]) - 0.8605695850647829 * fRec9[1];
		fRec8[0] = fRec9[0] - (1.8405051250752198 * fRec8[1] + 0.8612942439318627 * fRec8[2]);
		double fTemp11 = 1.8508996845035413 * fRec8[1];
		double fTemp12 = 0.9254498422517706 * (fRec8[0] + fRec8[2]);
		double fTemp13 = (fTemp11 + fTemp12) / (Ranode(TUBE_TABLE_12AX7_250k, fRec7[1]) + 1e+05);
		fVec5[0] = fTemp13;
		fRec24[0] = fConst20 * (8.2e+02 * (fTemp13 + fVec5[1]) - fConst19 * fRec24[1]);
		fRec7[0] = Ftube(TUBE_TABLE_12AX7_250k, fTemp12 + fRec24[0] + fTemp11 + -0.840703) + -147.47524390243905;
		double fTemp14 = fRec7[0] - fRec7[1];
		fRec6[0] = fConst8 * (fConst7 * fTemp14 - fConst3 * fRec6[1]);
		fRec25[0] = fConst11 * (fConst10 * fRec25[1] + 0.025 * fTemp14);
		double fTemp15 = ((iSlow2) ? fRec25[0] : fRec6[0]);
		fRec26[0] = fSlow4 + 0.999 * fRec26[1];
		double fTemp16 = fRec26[0] * fTemp15;
		double fTemp17 = fTemp15 * (1.0 - fRec26[0]);
		double fTemp18 = fTemp17 + 1e-15;
		fRec35[0] = fTemp16 + (1e-15 - fConst47 * (fConst45 * fRec35[2] + fConst43 * fRec35[1]));
		double fTemp19 = fRec35[2] + fRec35[0] + 2.0 * fRec35[1];
		fVec6[0] = fTemp19;
		fRec34[0] = -(fConst8 * (fConst3 * fRec34[1] - fConst48 * (fTemp19 - fVec6[1])));
		fRec33[0] = -(fConst50 * (fConst49 * fRec33[1] - (fRec34[0] + fRec34[1])));
		fRec32[0] = fRec33[0] - fConst41 * (fConst39 * fRec32[2] + fConst37 * fRec32[1]);
		double fTemp20 = fRec32[2] + fRec32[0] + 2.0 * fRec32[1];
		fVec7[0] = fTemp20;
		fRec31[0] = -(fConst53 * (fConst51 * fRec31[1] - fConst41 * (fTemp20 + fVec7[1])));
		fRec30[0] = fRec31[0] - fConst34 * (fConst32 * fRec30[2] + fConst30 * fRec30[1]);
		double fTemp21 = fRec30[2] + fRec30[0] + 2.0 * fRec30[1];
		fVec8[0] = fTemp21;
		fRec29[0] = -(fConst56 * (fConst54 * fRec29[1] - fConst34 * (fTemp21 + fVec8[1])));
		fRec28[0] = fRec29[0] - fConst27 * (fConst25 * fRec28[2] + fConst23 * fRec28[1]);
		double fTemp22 = std::max<double>(-1.0, std::min<double>(1.0, fSlow9 * (fRec28[2] + fRec28[0] + 2.0 * fRec28[1])));
		fRec37[0] = -(fConst56 * (fConst54 * fRec37[1] - fConst57 * (fTemp21 - fVec8[1])));
		fRec36[0] = fRec37[0] - fConst27 * (fConst25 * fRec36[2] + fConst23 * fRec36[1]);
		double fTemp23 = std::max<double>(-1.0, std::min<double>(1.0, fSlow10 * (fRec36[2] + (fRec36[0] - 2.0 * fRec36[1]))));
		double fTemp24 = fConst23 * fRec38[1];
		double fTemp25 = fConst30 * fRec39[1];
		fRec41[0] = -(fConst50 * (fConst49 * fRec41[1] - fConst38 * (fRec34[0] - fRec34[1])));
		fRec40[0] = fRec41[0] - fConst41 * (fConst39 * fRec40[2] + fConst37 * fRec40[1]);
		fRec39[0] = fConst63 * (fRec40[2] + (fRec40[0] - 2.0 * fRec40[1])) - fConst62 * (fConst61 * fRec39[2] + fTemp25);
		fRec38[0] = fRec39[2] + fConst62 * (fTemp25 + fConst61 * fRec39[0]) - fConst60 * (fConst59 * fRec38[2] + fTemp24);
		double fTemp26 = std::max<double>(-1.0, std::min<double>(1.0, fSlow11 * (fRec38[2] + fConst60 * (fTemp24 + fConst59 * fRec38[0]))));
		double fTemp27 = fConst23 * fRec42[1];
		fRec44[0] = -(fConst53 * (fConst51 * fRec44[1] - fConst64 * (fTemp20 - fVec7[1])));
		fRec43[0] = fRec44[0] - fConst34 * (fConst32 * fRec43[2] + fConst30 * fRec43[1]);
		fRec42[0] = fConst65 * (fRec43[2] + (fRec43[0] - 2.0 * fRec43[1])) - fConst60 * (fConst59 * fRec42[2] + fTemp27);
		double fTemp28 = std::max<double>(-1.0, std::min<double>(1.0, fSlow12 * (fRec42[2] + fConst60 * (fTemp27 + fConst59 * fRec42[0]))));
		double fTemp29 = 1.333521432 * fTemp28 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp28)) + 1.584893192 * (fTemp26 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp26)) + fTemp23 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp23))) + 1.2589412 * fTemp22 * (1.0 - 0.3333333333333333 * mydsp_faustpower2_f(fTemp22));
		fVec9[0] = fTemp29;
		fRec27[0] = -(fConst14 * (fConst13 * fRec27[1] - (fTemp29 + fVec9[1])));
		double fTemp30 = fSlow13 * fRec27[0] + fTemp17 + fSlow8 * (4.0 * fTemp18 * (1.0 - std::fabs(fTemp18)) + (-1e-15 - fTemp17)) + fSlow7 * (fTemp16 + 1e-15) + 1e-15;
		fVec10[0] = fTemp30;
		fRec5[0] = -(fConst14 * (fConst13 * fRec5[1] - (fTemp30 + fVec10[1])));
		double fTemp31 = fRec5[0] * fRec4[0];
		fVec11[0] = fTemp31;
		fRec3[0] = 0.9302847925323914 * (fTemp31 + fVec11[1]) - 0.8605695850647829 * fRec3[1];
		fRec2[0] = fRec3[0] - (1.8405051250752198 * fRec2[1] + 0.8612942439318627 * fRec2[2]);
		double fTemp32 = 1.8508996845035413 * fRec2[1];
		double fTemp33 = 0.9254498422517706 * (fRec2[0] + fRec2[2]);
		double fTemp34 = fTemp32 + fTemp33;
		double fTemp35 = fTemp34 / (Ranode(TUBE_TABLE_6V6_250k, fRec1[1]) + 1e+05);
		fVec12[0] = fTemp35;
		fRec45[0] = fConst14 * (8.2e+02 * (fTemp35 + fVec12[1]) - fConst13 * fRec45[1]);
		fRec1[0] = Ftube(TUBE_TABLE_6V6_250k, fTemp33 + fRec45[0] + fTemp32 + -1.130462) + -112.13878048780487;
		double fTemp36 = fRec1[0] - fRec1[1];
		fRec0[0] = fConst8 * (fConst7 * fTemp36 - fConst3 * fRec0[1]);
		fRec46[0] = fConst11 * (fConst10 * fRec46[1] + 0.025 * fTemp36);
		double fTemp37 = fTemp34 / (Ranode(TUBE_TABLE_6V6_68k, fRec48[1]) + 1e+05);
		fVec13[0] = fTemp37;
		fRec49[0] = fConst14 * (8.2e+02 * (fTemp37 + fVec13[1]) - fConst13 * fRec49[1]);
		fRec48[0] = Ftube(TUBE_TABLE_6V6_68k, fTemp33 + fRec49[0] + fTemp32 + -1.13074) + -112.10487804878048;
		double fTemp38 = fRec48[0] - fRec48[1];
		fRec47[0] = fConst8 * (fConst7 * fTemp38 - fConst3 * fRec47[1]);
		fRec50[0] = fConst11 * (fConst10 * fRec50[1] + 0.025 * fTemp38);
		output0[i0] = FAUSTFLOAT(((iSlow0) ? fRec50[0] : fRec47[0]) + ((iSlow0) ? fRec46[0] : fRec0[0]));
		fRec4[1] = fRec4[0];
		fRec19[1] = fRec19[0];
		fVec0[1] = fVec0[0];
		fRec18[1] = fRec18[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fVec1[1] = fVec1[0];
		fRec20[1] = fRec20[0];
		fRec16[1] = fRec16[0];
		fRec15[1] = fRec15[0];
		fRec21[1] = fRec21[0];
		fVec2[1] = fVec2[0];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fVec3[1] = fVec3[0];
		fRec22[1] = fRec22[0];
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
		fRec23[1] = fRec23[0];
		fVec4[1] = fVec4[0];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fVec5[1] = fVec5[0];
		fRec24[1] = fRec24[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fRec35[2] = fRec35[1];
		fRec35[1] = fRec35[0];
		fVec6[1] = fVec6[0];
		fRec34[1] = fRec34[0];
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fVec7[1] = fVec7[0];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fVec8[1] = fVec8[0];
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fRec37[1] = fRec37[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		fRec41[1] = fRec41[0];
		fRec40[2] = fRec40[1];
		fRec40[1] = fRec40[0];
		fRec39[2] = fRec39[1];
		fRec39[1] = fRec39[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		fRec44[1] = fRec44[0];
		fRec43[2] = fRec43[1];
		fRec43[1] = fRec43[0];
		fRec42[2] = fRec42[1];
		fRec42[1] = fRec42[0];
		fVec9[1] = fVec9[0];
		fRec27[1] = fRec27[0];
		fVec10[1] = fVec10[0];
		fRec5[1] = fRec5[0];
		fVec11[1] = fVec11[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fVec12[1] = fVec12[0];
		fRec45[1] = fRec45[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec46[1] = fRec46[0];
		fVec13[1] = fVec13[0];
		fRec49[1] = fRec49[0];
		fRec48[1] = fRec48[0];
		fRec47[1] = fRec47[0];
		fRec50[1] = fRec50[0];
	}
#undef fCheckbox0
#undef fVslider0
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
		fVslider3_ = (float*)data; // , 0.35, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fVslider2_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
		break;
	case PREGAIN: 
		fVslider1_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
		break;
	case GAIN1: 
		fVslider0_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
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

} // end namespace gxamp5
