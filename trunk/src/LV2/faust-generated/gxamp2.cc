// generated from file '../src/LV2/faust/gxamp2.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxamp2 {

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
	double fRec10[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst7;
	double fConst10;
	double fConst12;
	double fConst14;
	double fConst15;
	double fConst17;
	double fConst19;
	double fConst20;
	double fConst23;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec24[2];
	double fConst24;
	double fConst25;
	double fRec23[3];
	double fVec0[2];
	double fConst26;
	double fConst27;
	double fRec22[2];
	double fRec21[2];
	double fConst28;
	double fConst30;
	double fConst31;
	double fRec20[3];
	double fVec1[2];
	double fConst32;
	double fConst33;
	double fConst34;
	double fRec19[2];
	double fConst35;
	double fConst36;
	double fRec18[3];
	double fConst37;
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst45;
	double fConst46;
	double fRec17[3];
	double fConst47;
	double fRec28[2];
	double fRec27[3];
	double fConst48;
	double fConst49;
	double fConst50;
	double fRec26[3];
	double fRec25[3];
	double fConst51;
	double fConst52;
	double fConst53;
	double fRec32[2];
	double fRec31[3];
	double fVec2[2];
	double fConst54;
	double fConst55;
	double fRec30[2];
	double fConst56;
	double fRec29[3];
	double fConst57;
	double fConst58;
	double fRec34[2];
	double fRec33[3];
	double fVec3[2];
	double fRec16[2];
	double fVec4[2];
	double fRec15[2];
	double fRec14[3];
	double fConst60;
	double fVec5[2];
	double fConst61;
	double fRec35[2];
	double fRec13[2];
	double fRec12[2];
	double fConst63;
	double fConst64;
	double fRec36[2];
	double fVec6[2];
	double fRec11[2];
	double fVec7[2];
	double fRec9[2];
	double fRec8[3];
	double fConst66;
	double fVec8[2];
	double fConst67;
	double fRec37[2];
	double fRec7[2];
	double fRec6[2];
	double fRec38[2];
	double fVec9[2];
	double fRec5[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec39[2];
	double fConst69;
	double fRec4[3];
	double fVec10[2];
	double fRec3[2];
	double fRec2[3];
	double fConst71;
	double fVec11[2];
	double fConst72;
	double fRec40[2];
	double fRec1[2];
	double fRec0[2];
	double fRec41[2];

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
	id = "6V6";
	name = N_("6V6");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec10[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec24[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRec23[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fVec0[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec22[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec21[l5] = 0.0;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec20[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fVec1[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec19[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec18[l9] = 0.0;
	for (int l10 = 0; l10 < 3; l10 = l10 + 1) fRec17[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec28[l11] = 0.0;
	for (int l12 = 0; l12 < 3; l12 = l12 + 1) fRec27[l12] = 0.0;
	for (int l13 = 0; l13 < 3; l13 = l13 + 1) fRec26[l13] = 0.0;
	for (int l14 = 0; l14 < 3; l14 = l14 + 1) fRec25[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec32[l15] = 0.0;
	for (int l16 = 0; l16 < 3; l16 = l16 + 1) fRec31[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fVec2[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec30[l18] = 0.0;
	for (int l19 = 0; l19 < 3; l19 = l19 + 1) fRec29[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec34[l20] = 0.0;
	for (int l21 = 0; l21 < 3; l21 = l21 + 1) fRec33[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fVec3[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec16[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fVec4[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec15[l25] = 0.0;
	for (int l26 = 0; l26 < 3; l26 = l26 + 1) fRec14[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fVec5[l27] = 0.0;
	for (int l28 = 0; l28 < 2; l28 = l28 + 1) fRec35[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec13[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec12[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec36[l31] = 0.0;
	for (int l32 = 0; l32 < 2; l32 = l32 + 1) fVec6[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fRec11[l33] = 0.0;
	for (int l34 = 0; l34 < 2; l34 = l34 + 1) fVec7[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec9[l35] = 0.0;
	for (int l36 = 0; l36 < 3; l36 = l36 + 1) fRec8[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fVec8[l37] = 0.0;
	for (int l38 = 0; l38 < 2; l38 = l38 + 1) fRec37[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec7[l39] = 0.0;
	for (int l40 = 0; l40 < 2; l40 = l40 + 1) fRec6[l40] = 0.0;
	for (int l41 = 0; l41 < 2; l41 = l41 + 1) fRec38[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) fVec9[l42] = 0.0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fRec5[l43] = 0.0;
	for (int l44 = 0; l44 < 2; l44 = l44 + 1) fRec39[l44] = 0.0;
	for (int l45 = 0; l45 < 3; l45 = l45 + 1) fRec4[l45] = 0.0;
	for (int l46 = 0; l46 < 2; l46 = l46 + 1) fVec10[l46] = 0.0;
	for (int l47 = 0; l47 < 2; l47 = l47 + 1) fRec3[l47] = 0.0;
	for (int l48 = 0; l48 < 3; l48 = l48 + 1) fRec2[l48] = 0.0;
	for (int l49 = 0; l49 < 2; l49 = l49 + 1) fVec11[l49] = 0.0;
	for (int l50 = 0; l50 < 2; l50 = l50 + 1) fRec40[l50] = 0.0;
	for (int l51 = 0; l51 < 2; l51 = l51 + 1) fRec1[l51] = 0.0;
	for (int l52 = 0; l52 < 2; l52 = l52 + 1) fRec0[l52] = 0.0;
	for (int l53 = 0; l53 < 2; l53 = l53 + 1) fRec41[l53] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = std::tan(97.389372261283583 / fConst0);
	double fConst2 = 1.0 / fConst1;
	double fConst3 = fConst2 + 1.0;
	fConst4 = 1.0 / (fConst1 * fConst3);
	double fConst5 = 1.0 / std::tan(20517.741620594938 / fConst0);
	fConst6 = 1.0 / (fConst5 + 1.0);
	fConst7 = 1.0 - fConst5;
	double fConst8 = std::tan(3769.9111843077517 / fConst0);
	double fConst9 = 1.0 / fConst8;
	fConst10 = 1.0 / ((fConst9 + 1.0000000000000004) / fConst8 + 1.0);
	double fConst11 = mydsp_faustpower2_f(fConst8);
	fConst12 = 1.0 / fConst11;
	double fConst13 = std::tan(10053.096491487338 / fConst0);
	fConst14 = 1.0 / fConst13;
	fConst15 = 1.0 / ((fConst14 + 1.0000000000000004) / fConst13 + 1.0);
	double fConst16 = fConst9 + 1.0;
	fConst17 = 1.0 / (fConst8 * fConst16);
	double fConst18 = fConst14 + 1.0;
	fConst19 = 1.0 / fConst18;
	fConst20 = 1.0 - fConst14;
	double fConst21 = std::tan(47123.889803846898 / fConst0);
	double fConst22 = 1.0 / fConst21;
	fConst23 = 1.0 / ((fConst22 + 1.4142135623730949) / fConst21 + 1.0);
	fConst24 = (fConst22 + -1.4142135623730949) / fConst21 + 1.0;
	fConst25 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst21));
	fConst26 = 0.0 - fConst4;
	fConst27 = (1.0 - fConst2) / fConst3;
	fConst28 = (fConst14 + -1.0000000000000004) / fConst13 + 1.0;
	double fConst29 = mydsp_faustpower2_f(fConst13);
	fConst30 = 1.0 / fConst29;
	fConst31 = 2.0 * (1.0 - fConst30);
	fConst32 = 0.0 - fConst17;
	fConst33 = 1.0 - fConst9;
	fConst34 = fConst33 / fConst16;
	fConst35 = (fConst9 + -1.0000000000000004) / fConst8 + 1.0;
	fConst36 = 2.0 * (1.0 - fConst12);
	fConst37 = 0.0 - 2.0 / fConst11;
	double fConst38 = std::tan(942.47779607693792 / fConst0);
	double fConst39 = 1.0 / fConst38;
	double fConst40 = fConst39 + 1.0;
	fConst41 = 1.0 / (fConst40 / fConst38 + 1.0);
	fConst42 = 1.0 - fConst39;
	fConst43 = 1.0 - fConst42 / fConst38;
	double fConst44 = mydsp_faustpower2_f(fConst38);
	fConst45 = 1.0 / fConst44;
	fConst46 = 2.0 * (1.0 - fConst45);
	fConst47 = 0.0 - 1.0 / (fConst13 * fConst18);
	fConst48 = 0.0 - 2.0 / fConst29;
	fConst49 = 1.0 / (fConst16 / fConst8 + 1.0);
	fConst50 = 1.0 - fConst33 / fConst8;
	fConst51 = 1.0 / ((fConst39 + 1.0000000000000004) / fConst38 + 1.0);
	fConst52 = 1.0 / (fConst38 * fConst40);
	fConst53 = 1.0 / fConst16;
	fConst54 = 0.0 - fConst52;
	fConst55 = fConst42 / fConst40;
	fConst56 = (fConst39 + -1.0000000000000004) / fConst38 + 1.0;
	fConst57 = 0.0 - 2.0 / fConst44;
	fConst58 = 1.0 / fConst40;
	double fConst59 = 1.0 / std::tan(270.1769682087222 / fConst0);
	fConst60 = 1.0 / (fConst59 + 1.0);
	fConst61 = 1.0 - fConst59;
	double fConst62 = 3.1415926535897931 / fConst0;
	fConst63 = 1.0 / (fConst62 + 1.0);
	fConst64 = 1.0 - fConst62;
	double fConst65 = 1.0 / std::tan(414.69023027385271 / fConst0);
	fConst66 = 1.0 / (fConst65 + 1.0);
	fConst67 = 1.0 - fConst65;
	double fConst68 = std::log(7539.8223686155034 / fConst0);
	fConst69 = 0.0 - 1.8442000000000001 * std::cos(std::exp(fConst68 * (fConst68 * (fConst68 * (fConst68 * (0.0050615800000000004 * fConst68 + 0.064468059999999994) + 0.27547621) + 0.43359432999999997) + 1.3128224799999999) + 0.072388869999999994));
	double fConst70 = 1.0 / std::tan(609.46897479641984 / fConst0);
	fConst71 = 1.0 / (fConst70 + 1.0);
	fConst72 = 1.0 - fConst70;
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
	double fSlow2 = 0.0010000000000000009 * std::pow(10.0, 0.050000000000000003 * double(fVslider0));
	double fSlow3 = double(fVslider1);
	double fSlow4 = 2.0 * (fSlow3 + -0.5);
	double fSlow5 = 1.0 - std::max<double>(0.0, -1.0 * fSlow4);
	double fSlow6 = std::pow(10.0, 1.2 * fSlow3);
	double fSlow7 = 1.0000000000000009e-05 * double(fVslider2);
	double fSlow8 = std::pow(10.0, 0.80000000000000004 * fSlow3);
	double fSlow9 = fConst51 * std::pow(10.0, 2.0 * fSlow3);
	double fSlow10 = fConst51 * std::pow(10.0, 0.90000000000000002 * fSlow3);
	double fSlow11 = 1.25 * fSlow3;
	double fSlow12 = 1.0 - std::max<double>(0.0, fSlow4);
	double fSlow13 = 0.0010000000000000009 * std::pow(10.0, 0.050000000000000003 * double(fVslider3));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec10[0] = fSlow2 + 0.999 * fRec10[1];
		double fTemp0 = double(input0[i0]);
		fRec24[0] = fSlow7 + 0.999 * fRec24[1];
		double fTemp1 = fTemp0 * fRec24[0];
		fRec23[0] = fTemp1 + 1.0000000000000001e-15 - fConst23 * (fConst24 * fRec23[2] + fConst25 * fRec23[1]);
		double fTemp2 = fRec23[2] + fRec23[0] + 2.0 * fRec23[1];
		fVec0[0] = fTemp2;
		fRec22[0] = fConst23 * (fConst4 * fTemp2 + fConst26 * fVec0[1]) - fConst27 * fRec22[1];
		fRec21[0] = 0.0 - fConst19 * (fConst20 * fRec21[1] - (fRec22[0] + fRec22[1]));
		fRec20[0] = fRec21[0] - fConst15 * (fConst28 * fRec20[2] + fConst31 * fRec20[1]);
		double fTemp3 = fRec20[2] + fRec20[0] + 2.0 * fRec20[1];
		fVec1[0] = fTemp3;
		fRec19[0] = fConst15 * (fConst17 * fTemp3 + fConst32 * fVec1[1]) - fConst34 * fRec19[1];
		fRec18[0] = fRec19[0] - fConst10 * (fConst35 * fRec18[2] + fConst36 * fRec18[1]);
		double fTemp4 = fConst46 * fRec17[1];
		fRec17[0] = fConst10 * (fConst12 * fRec18[0] + fConst37 * fRec18[1] + fConst12 * fRec18[2]) - fConst41 * (fConst43 * fRec17[2] + fTemp4);
		double fTemp5 = std::max<double>(-1.0, std::min<double>(1.0, fSlow6 * (fRec17[2] + fConst41 * (fTemp4 + fConst43 * fRec17[0]))));
		fRec28[0] = fConst47 * fRec22[1] - fConst19 * (fConst20 * fRec28[1] - fConst14 * fRec22[0]);
		fRec27[0] = fRec28[0] - fConst15 * (fConst28 * fRec27[2] + fConst31 * fRec27[1]);
		double fTemp6 = fConst36 * fRec26[1];
		fRec26[0] = fConst15 * (fConst30 * fRec27[0] + fConst48 * fRec27[1] + fConst30 * fRec27[2]) - fConst49 * (fConst50 * fRec26[2] + fTemp6);
		double fTemp7 = fConst46 * fRec25[1];
		fRec25[0] = (fRec26[2] + fConst49 * (fTemp6 + fConst50 * fRec26[0])) - fConst41 * (fConst43 * fRec25[2] + fTemp7);
		double fTemp8 = std::max<double>(-1.0, std::min<double>(1.0, fSlow8 * (fRec25[2] + fConst41 * (fTemp7 + fConst43 * fRec25[0]))));
		fRec32[0] = 0.0 - fConst53 * (fConst33 * fRec32[1] - fConst15 * (fTemp3 + fVec1[1]));
		fRec31[0] = fRec32[0] - fConst10 * (fConst35 * fRec31[2] + fConst36 * fRec31[1]);
		double fTemp9 = fRec31[2] + fRec31[0] + 2.0 * fRec31[1];
		fVec2[0] = fTemp9;
		fRec30[0] = fConst10 * (fConst52 * fTemp9 + fConst54 * fVec2[1]) - fConst55 * fRec30[1];
		fRec29[0] = fRec30[0] - fConst51 * (fConst56 * fRec29[2] + fConst46 * fRec29[1]);
		double fTemp10 = std::max<double>(-1.0, std::min<double>(1.0, fSlow9 * (fConst45 * fRec29[0] + fConst57 * fRec29[1] + fConst45 * fRec29[2])));
		fRec34[0] = 0.0 - fConst58 * (fConst42 * fRec34[1] - fConst10 * (fTemp9 + fVec2[1]));
		fRec33[0] = fRec34[0] - fConst51 * (fConst56 * fRec33[2] + fConst46 * fRec33[1]);
		double fTemp11 = std::max<double>(-1.0, std::min<double>(1.0, fSlow10 * (fRec33[2] + fRec33[0] + 2.0 * fRec33[1])));
		double fTemp12 = 1.333521432 * fTemp5 * (1.0 - 0.33333333333333331 * mydsp_faustpower2_f(fTemp5)) + 1.584893192 * (fTemp8 * (1.0 - 0.33333333333333331 * mydsp_faustpower2_f(fTemp8)) + fTemp10 * (1.0 - 0.33333333333333331 * mydsp_faustpower2_f(fTemp10))) + 1.2589412 * fTemp11 * (1.0 - 0.33333333333333331 * mydsp_faustpower2_f(fTemp11));
		fVec3[0] = fTemp12;
		fRec16[0] = 0.0 - fConst6 * (fConst7 * fRec16[1] - (fTemp12 + fVec3[1]));
		double fTemp13 = fTemp0 * (1.0 - fRec24[0]);
		double fTemp14 = fTemp13 + 1.0000000000000001e-15;
		double fTemp15 = fRec10[0] * (fSlow5 * fRec16[0] + fTemp13 + fSlow11 * (4.0 * fTemp14 * (1.0 - std::fabs(fTemp14)) + -1.0000000000000001e-15 - fTemp13) + fSlow12 * (fTemp1 + 1.0000000000000001e-15) + 1.0000000000000001e-15);
		fVec4[0] = fTemp15;
		fRec15[0] = 0.93028479253239138 * (fTemp15 + fVec4[1]) - 0.86056958506478287 * fRec15[1];
		fRec14[0] = fRec15[0] - (1.8405051250752198 * fRec14[1] + 0.86129424393186271 * fRec14[2]);
		double fTemp16 = 0.92544984225177063 * (fRec14[0] + fRec14[2]);
		double fTemp17 = 1.8508996845035413 * fRec14[1];
		double fTemp18 = (fTemp17 + fTemp16) / (double(Ranode(int(TUBE_TABLE_6V6_68k), double(fRec13[1]))) + 100000.0);
		fVec5[0] = fTemp18;
		fRec35[0] = fConst60 * (2700.0 * (fTemp18 + fVec5[1]) - fConst61 * fRec35[1]);
		fRec13[0] = double(Ftube(int(TUBE_TABLE_6V6_68k), double(fTemp16 + fRec35[0] + fTemp17 + -2.2961499999999999))) + -164.9574074074074;
		fRec12[0] = 0.025000000000000001 * (fConst4 * fRec13[0] + fConst26 * fRec13[1]) - fConst27 * fRec12[1];
		fRec36[0] = fConst63 * (fConst64 * fRec36[1] + 0.025000000000000001 * (fRec13[0] - fRec13[1]));
		double fTemp19 = ((iSlow1) ? fRec36[0] : fRec12[0]);
		fVec6[0] = fTemp19;
		fRec11[0] = fConst6 * (0.77000000000000002 * (fTemp19 + fVec6[1]) - fConst7 * fRec11[1]);
		double fTemp20 = fRec10[0] * fRec11[0];
		fVec7[0] = fTemp20;
		fRec9[0] = 0.93028479253239138 * (fTemp20 + fVec7[1]) - 0.86056958506478287 * fRec9[1];
		fRec8[0] = fRec9[0] - (1.8405051250752198 * fRec8[1] + 0.86129424393186271 * fRec8[2]);
		double fTemp21 = 0.92544984225177063 * (fRec8[0] + fRec8[2]);
		double fTemp22 = 1.8508996845035413 * fRec8[1];
		double fTemp23 = (fTemp22 + fTemp21) / (double(Ranode(int(TUBE_TABLE_6V6_250k), double(fRec7[1]))) + 100000.0);
		fVec8[0] = fTemp23;
		fRec37[0] = fConst66 * (1500.0 * (fTemp23 + fVec8[1]) - fConst67 * fRec37[1]);
		fRec7[0] = double(Ftube(int(TUBE_TABLE_6V6_250k), double(fTemp21 + fRec37[0] + fTemp22 + -1.6755869999999999))) + -138.29419999999999;
		fRec6[0] = 0.025000000000000001 * (fConst4 * fRec7[0] + fConst26 * fRec7[1]) - fConst27 * fRec6[1];
		fRec38[0] = fConst63 * (fConst64 * fRec38[1] + 0.025000000000000001 * (fRec7[0] - fRec7[1]));
		double fTemp24 = ((iSlow1) ? fRec38[0] : fRec6[0]);
		fVec9[0] = fTemp24;
		fRec5[0] = fConst6 * (0.77000000000000002 * (fTemp24 + fVec9[1]) - fConst7 * fRec5[1]);
		fRec39[0] = fSlow13 + 0.999 * fRec39[1];
		fRec4[0] = fRec5[0] * fRec39[0] - (fConst69 * fRec4[1] + 0.85026841000000009 * fRec4[2]);
		double fTemp25 = fRec4[0] - 1.0589999999999999 * fRec4[1];
		fVec10[0] = fTemp25;
		fRec3[0] = 0.93028479253239138 * (fTemp25 + fVec10[1]) - 0.86056958506478287 * fRec3[1];
		fRec2[0] = fRec3[0] - (1.8405051250752198 * fRec2[1] + 0.86129424393186271 * fRec2[2]);
		double fTemp26 = 0.92544984225177063 * (fRec2[0] + fRec2[2]);
		double fTemp27 = 1.8508996845035413 * fRec2[1];
		double fTemp28 = (fTemp27 + fTemp26) / (double(Ranode(int(TUBE_TABLE_6V6_250k), double(fRec1[1]))) + 100000.0);
		fVec11[0] = fTemp28;
		fRec40[0] = fConst71 * (820.0 * (fTemp28 + fVec11[1]) - fConst72 * fRec40[1]);
		fRec1[0] = double(Ftube(int(TUBE_TABLE_6V6_250k), double(fTemp26 + fRec40[0] + fTemp27 + -1.1304620000000001))) + -112.13878048780487;
		fRec0[0] = 0.025000000000000001 * (fConst4 * fRec1[0] + fConst26 * fRec1[1]) - fConst27 * fRec0[1];
		fRec41[0] = fConst63 * (fConst64 * fRec41[1] + 0.025000000000000001 * (fRec1[0] - fRec1[1]));
		output0[i0] = FAUSTFLOAT(0.77000000000000002 * ((iSlow0) ? fRec41[0] : fRec0[0]));
		fRec10[1] = fRec10[0];
		fRec24[1] = fRec24[0];
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
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fRec28[1] = fRec28[0];
		fRec27[2] = fRec27[1];
		fRec27[1] = fRec27[0];
		fRec26[2] = fRec26[1];
		fRec26[1] = fRec26[0];
		fRec25[2] = fRec25[1];
		fRec25[1] = fRec25[0];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fVec2[1] = fVec2[0];
		fRec30[1] = fRec30[0];
		fRec29[2] = fRec29[1];
		fRec29[1] = fRec29[0];
		fRec34[1] = fRec34[0];
		fRec33[2] = fRec33[1];
		fRec33[1] = fRec33[0];
		fVec3[1] = fVec3[0];
		fRec16[1] = fRec16[0];
		fVec4[1] = fVec4[0];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fVec5[1] = fVec5[0];
		fRec35[1] = fRec35[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec36[1] = fRec36[0];
		fVec6[1] = fVec6[0];
		fRec11[1] = fRec11[0];
		fVec7[1] = fVec7[0];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fVec8[1] = fVec8[0];
		fRec37[1] = fRec37[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec38[1] = fRec38[0];
		fVec9[1] = fVec9[0];
		fRec5[1] = fRec5[0];
		fRec39[1] = fRec39[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fVec10[1] = fVec10[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fVec11[1] = fVec11[0];
		fRec40[1] = fRec40[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec41[1] = fRec41[0];
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
   HIGHGAIN, 
   PREGAIN, 
   GAIN1, 
} PortIndex;
*/

} // end namespace gxamp2
