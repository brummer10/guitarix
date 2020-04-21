// generated from file '../src/LV2/faust/gxmetal_head.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxmetal_head {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec1[2];
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fVec0[2];
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fRec29[2];
	double fConst29;
	double fConst30;
	double fRec28[2];
	double fRec27[2];
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fRec26[3];
	double fVec1[2];
	double fConst35;
	double fConst36;
	double fConst37;
	double fRec25[2];
	double fConst38;
	double fConst39;
	double fRec24[3];
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fRec23[3];
	double fConst50;
	double fRec33[2];
	double fRec32[3];
	double fConst51;
	double fConst52;
	double fConst53;
	double fRec31[3];
	double fRec30[3];
	double fConst54;
	double fConst55;
	double fConst56;
	double fRec37[2];
	double fRec36[3];
	double fVec2[2];
	double fConst57;
	double fConst58;
	double fRec35[2];
	double fConst59;
	double fRec34[3];
	double fConst60;
	double fConst61;
	double fRec39[2];
	double fRec38[3];
	double fVec3[2];
	double fRec22[2];
	double fRec21[2];
	double fVec4[2];
	double fRec20[2];
	double fRec19[3];
	double fConst62;
	double fConst63;
	double fConst64;
	double fVec5[2];
	double fRec40[2];
	double fRec18[2];
	double fConst65;
	double fConst66;
	double fRec17[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec41[2];
	double fVec6[2];
	double fRec16[2];
	double fVec7[2];
	double fRec15[2];
	double fRec14[3];
	double fConst67;
	double fConst68;
	double fConst69;
	double fVec8[2];
	double fRec42[2];
	double fRec13[2];
	double fRec12[2];
	double fRec11[2];
	double fVec9[2];
	double fRec10[2];
	double fRec9[3];
	double fConst70;
	double fConst71;
	double fConst72;
	double fVec10[2];
	double fRec43[2];
	double fRec8[2];
	double fRec7[2];
	double fConst73;
	double fConst74;
	double fRec6[2];
	double fConst75;
	double fConst76;
	double fConst77;
	double fRec44[2];
	double fVec11[2];
	double fRec5[2];
	double fRec4[3];
	double fConst78;
	double fConst79;
	double fConst80;
	double fRec45[2];
	double fRec3[3];
	double fRec2[2];
	double fRec48[2];
	double fRec47[3];
	double fRec46[2];
	double fVec12[2];
	double fRec0[2];
	double fRec49[2];

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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec1[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fVec0[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec29[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec28[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec27[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec26[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fVec1[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec25[l7] = 0.0;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec24[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec23[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec33[l10] = 0.0;
	for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) fRec32[l11] = 0.0;
	for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) fRec31[l12] = 0.0;
	for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) fRec30[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec37[l14] = 0.0;
	for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) fRec36[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fVec2[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec35[l17] = 0.0;
	for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) fRec34[l18] = 0.0;
	for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) fRec39[l19] = 0.0;
	for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) fRec38[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fVec3[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fRec22[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fRec21[l23] = 0.0;
	for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) fVec4[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fRec20[l25] = 0.0;
	for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) fRec19[l26] = 0.0;
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) fVec5[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec40[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fRec18[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fRec17[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fRec41[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fVec6[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fRec16[l33] = 0.0;
	for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) fVec7[l34] = 0.0;
	for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) fRec15[l35] = 0.0;
	for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) fRec14[l36] = 0.0;
	for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) fVec8[l37] = 0.0;
	for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) fRec42[l38] = 0.0;
	for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) fRec13[l39] = 0.0;
	for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) fRec12[l40] = 0.0;
	for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) fRec11[l41] = 0.0;
	for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) fVec9[l42] = 0.0;
	for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) fRec10[l43] = 0.0;
	for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) fRec9[l44] = 0.0;
	for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) fVec10[l45] = 0.0;
	for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) fRec43[l46] = 0.0;
	for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) fRec8[l47] = 0.0;
	for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) fRec7[l48] = 0.0;
	for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) fRec6[l49] = 0.0;
	for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) fRec44[l50] = 0.0;
	for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) fVec11[l51] = 0.0;
	for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) fRec5[l52] = 0.0;
	for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) fRec4[l53] = 0.0;
	for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) fRec45[l54] = 0.0;
	for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) fRec3[l55] = 0.0;
	for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) fRec2[l56] = 0.0;
	for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) fRec48[l57] = 0.0;
	for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) fRec47[l58] = 0.0;
	for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) fRec46[l59] = 0.0;
	for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) fVec12[l60] = 0.0;
	for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) fRec0[l61] = 0.0;
	for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) fRec49[l62] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (1.0 / std::tan((20517.741620594938 / fConst0)));
	fConst2 = (1.0 / (fConst1 + 1.0));
	fConst3 = (1.0 - fConst1);
	fConst4 = std::tan((97.389372261283583 / fConst0));
	fConst5 = (1.0 / fConst4);
	fConst6 = (fConst5 + 1.0);
	fConst7 = (1.0 / (fConst4 * fConst6));
	fConst8 = std::tan((5830.7959650626563 / fConst0));
	fConst9 = (1.0 / fConst8);
	fConst10 = (fConst9 + 1.0);
	fConst11 = (0.0 - (1.0 / (fConst8 * fConst10)));
	fConst12 = std::tan((376.99111843077515 / fConst0));
	fConst13 = (1.0 / fConst12);
	fConst14 = (fConst13 + 1.0);
	fConst15 = (0.0 - (1.0 / (fConst12 * fConst14)));
	fConst16 = std::tan((3769.9111843077517 / fConst0));
	fConst17 = (1.0 / fConst16);
	fConst18 = (1.0 / (((fConst17 + 1.0000000000000004) / fConst16) + 1.0));
	fConst19 = mydsp_faustpower2_f(fConst16);
	fConst20 = (1.0 / fConst19);
	fConst21 = std::tan((10053.096491487338 / fConst0));
	fConst22 = (1.0 / fConst21);
	fConst23 = (1.0 / (((fConst22 + 1.0000000000000004) / fConst21) + 1.0));
	fConst24 = (fConst17 + 1.0);
	fConst25 = (1.0 / (fConst16 * fConst24));
	fConst26 = (fConst22 + 1.0);
	fConst27 = (1.0 / fConst26);
	fConst28 = (1.0 - fConst22);
	fConst29 = (1.0 / fConst14);
	fConst30 = (1.0 - fConst13);
	fConst31 = (((fConst22 + -1.0000000000000004) / fConst21) + 1.0);
	fConst32 = mydsp_faustpower2_f(fConst21);
	fConst33 = (1.0 / fConst32);
	fConst34 = (2.0 * (1.0 - fConst33));
	fConst35 = (0.0 - fConst25);
	fConst36 = (1.0 - fConst17);
	fConst37 = (fConst36 / fConst24);
	fConst38 = (((fConst17 + -1.0000000000000004) / fConst16) + 1.0);
	fConst39 = (2.0 * (1.0 - fConst20));
	fConst40 = (0.0 - (2.0 / fConst19));
	fConst41 = std::tan((942.47779607693792 / fConst0));
	fConst42 = (1.0 / fConst41);
	fConst43 = (fConst42 + 1.0);
	fConst44 = (1.0 / ((fConst43 / fConst41) + 1.0));
	fConst45 = (1.0 - fConst42);
	fConst46 = (1.0 - (fConst45 / fConst41));
	fConst47 = mydsp_faustpower2_f(fConst41);
	fConst48 = (1.0 / fConst47);
	fConst49 = (2.0 * (1.0 - fConst48));
	fConst50 = (0.0 - (1.0 / (fConst21 * fConst26)));
	fConst51 = (0.0 - (2.0 / fConst32));
	fConst52 = (1.0 / ((fConst24 / fConst16) + 1.0));
	fConst53 = (1.0 - (fConst36 / fConst16));
	fConst54 = (1.0 / (((fConst42 + 1.0000000000000004) / fConst41) + 1.0));
	fConst55 = (1.0 / (fConst41 * fConst43));
	fConst56 = (1.0 / fConst24);
	fConst57 = (0.0 - fConst55);
	fConst58 = (fConst45 / fConst43);
	fConst59 = (((fConst42 + -1.0000000000000004) / fConst41) + 1.0);
	fConst60 = (0.0 - (2.0 / fConst47));
	fConst61 = (1.0 / fConst43);
	fConst62 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst63 = (1.0 / (fConst62 + 1.0));
	fConst64 = (1.0 - fConst62);
	fConst65 = (0.0 - fConst7);
	fConst66 = ((1.0 - fConst5) / fConst6);
	fConst67 = (1.0 / std::tan((414.69023027385271 / fConst0)));
	fConst68 = (1.0 / (fConst67 + 1.0));
	fConst69 = (1.0 - fConst67);
	fConst70 = (1.0 / std::tan((609.46897479641984 / fConst0)));
	fConst71 = (1.0 / (fConst70 + 1.0));
	fConst72 = (1.0 - fConst70);
	fConst73 = (1.0 / fConst10);
	fConst74 = (1.0 - fConst9);
	fConst75 = (1.0 / std::tan((1281.7698026646356 / fConst0)));
	fConst76 = (1.0 / (fConst75 + 1.0));
	fConst77 = (1.0 - fConst75);
	fConst78 = (1.0 / std::tan((804.24771931898704 / fConst0)));
	fConst79 = (1.0 / (fConst78 + 1.0));
	fConst80 = (1.0 - fConst78);
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
	double fSlow2 = double(fVslider2);
	double fSlow3 = (2.0 * (fSlow2 + -0.5));
	double fSlow4 = (1.0 - std::max<double>(0.0, fSlow3));
	double fSlow5 = (1.0 - std::max<double>(0.0, (-1.0 * fSlow3)));
	double fSlow6 = std::pow(10.0, (1.2 * fSlow2));
	double fSlow7 = std::pow(10.0, (1.6000000000000001 * fSlow2));
	double fSlow8 = (fConst54 * fSlow7);
	double fSlow9 = (fConst54 * std::pow(10.0, (0.80000000000000004 * fSlow2)));
	double fSlow10 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider3))));
	double fSlow11 = (1.0 - fSlow1);
	double fSlow12 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * (0.0 - (12.0 * fSlow2)))));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec1[0] = (fSlow0 + (0.999 * fRec1[1]));
		double fTemp0 = double(input0[i]);
		fVec0[0] = fTemp0;
		fRec29[0] = (0.0 - (fConst2 * ((fConst3 * fRec29[1]) - (fTemp0 + fVec0[1]))));
		fRec28[0] = ((fConst15 * fRec29[1]) - (fConst29 * ((fConst30 * fRec28[1]) - (fConst13 * fRec29[0]))));
		fRec27[0] = (0.0 - (fConst27 * ((fConst28 * fRec27[1]) - (fRec28[0] + fRec28[1]))));
		fRec26[0] = (fRec27[0] - (fConst23 * ((fConst31 * fRec26[2]) + (fConst34 * fRec26[1]))));
		double fTemp1 = (fRec26[2] + (fRec26[0] + (2.0 * fRec26[1])));
		fVec1[0] = fTemp1;
		fRec25[0] = ((fConst23 * ((fConst25 * fTemp1) + (fConst35 * fVec1[1]))) - (fConst37 * fRec25[1]));
		fRec24[0] = (fRec25[0] - (fConst18 * ((fConst38 * fRec24[2]) + (fConst39 * fRec24[1]))));
		double fTemp2 = (fConst49 * fRec23[1]);
		fRec23[0] = ((fConst18 * (((fConst20 * fRec24[0]) + (fConst40 * fRec24[1])) + (fConst20 * fRec24[2]))) - (fConst44 * ((fConst46 * fRec23[2]) + fTemp2)));
		double fTemp3 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow6 * (fRec23[2] + (fConst44 * (fTemp2 + (fConst46 * fRec23[0])))))));
		fRec33[0] = ((fConst50 * fRec28[1]) - (fConst27 * ((fConst28 * fRec33[1]) - (fConst22 * fRec28[0]))));
		fRec32[0] = (fRec33[0] - (fConst23 * ((fConst31 * fRec32[2]) + (fConst34 * fRec32[1]))));
		double fTemp4 = (fConst39 * fRec31[1]);
		fRec31[0] = ((fConst23 * (((fConst33 * fRec32[0]) + (fConst51 * fRec32[1])) + (fConst33 * fRec32[2]))) - (fConst52 * ((fConst53 * fRec31[2]) + fTemp4)));
		double fTemp5 = (fConst49 * fRec30[1]);
		fRec30[0] = ((fRec31[2] + (fConst52 * (fTemp4 + (fConst53 * fRec31[0])))) - (fConst44 * ((fConst46 * fRec30[2]) + fTemp5)));
		double fTemp6 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow7 * (fRec30[2] + (fConst44 * (fTemp5 + (fConst46 * fRec30[0])))))));
		fRec37[0] = (0.0 - (fConst56 * ((fConst36 * fRec37[1]) - (fConst23 * (fTemp1 + fVec1[1])))));
		fRec36[0] = (fRec37[0] - (fConst18 * ((fConst38 * fRec36[2]) + (fConst39 * fRec36[1]))));
		double fTemp7 = (fRec36[2] + (fRec36[0] + (2.0 * fRec36[1])));
		fVec2[0] = fTemp7;
		fRec35[0] = ((fConst18 * ((fConst55 * fTemp7) + (fConst57 * fVec2[1]))) - (fConst58 * fRec35[1]));
		fRec34[0] = (fRec35[0] - (fConst54 * ((fConst59 * fRec34[2]) + (fConst49 * fRec34[1]))));
		double fTemp8 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow8 * (((fConst48 * fRec34[0]) + (fConst60 * fRec34[1])) + (fConst48 * fRec34[2])))));
		fRec39[0] = (0.0 - (fConst61 * ((fConst45 * fRec39[1]) - (fConst18 * (fTemp7 + fVec2[1])))));
		fRec38[0] = (fRec39[0] - (fConst54 * ((fConst59 * fRec38[2]) + (fConst49 * fRec38[1]))));
		double fTemp9 = std::max<double>(-1.0, std::min<double>(1.0, (fSlow9 * (fRec38[2] + (fRec38[0] + (2.0 * fRec38[1]))))));
		double fTemp10 = (((1.333521432 * (fTemp3 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp3))))) + (1.584893192 * ((fTemp6 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp6)))) + (fTemp8 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp8))))))) + (1.2589412 * (fTemp9 * (1.0 - (0.33333333333333331 * mydsp_faustpower2_f(fTemp9))))));
		fVec3[0] = fTemp10;
		fRec22[0] = (0.0 - (fConst2 * ((fConst3 * fRec22[1]) - (fTemp10 + fVec3[1]))));
		fRec21[0] = ((fConst15 * fRec22[1]) - (fConst29 * ((fConst30 * fRec21[1]) - (fConst13 * fRec22[0]))));
		double fTemp11 = (((fSlow4 * fTemp0) + (fSlow5 * fRec21[0])) + 1.0000000000000001e-15);
		fVec4[0] = fTemp11;
		fRec20[0] = ((0.93028479253239138 * (fTemp11 + fVec4[1])) - (0.86056958506478287 * fRec20[1]));
		fRec19[0] = (fRec20[0] - ((1.8405051250752198 * fRec19[1]) + (0.86129424393186271 * fRec19[2])));
		double fTemp12 = ((0.027 * fRec18[1]) + 1.0000000000000001e-15);
		fVec5[0] = fTemp12;
		fRec40[0] = (0.0 - (fConst63 * ((fConst64 * fRec40[1]) - (fTemp12 + fVec5[1]))));
		fRec18[0] = (double(Ftube(int(TUBE_TABLE_12AX7_68k), double((((0.92544984225177063 * (fRec19[0] + fRec19[2])) + (fRec40[0] + (1.8508996845035413 * fRec19[1]))) + -1.581656)))) + -191.42014814814814);
		fRec17[0] = ((0.025000000000000001 * ((fConst7 * fRec18[0]) + (fConst65 * fRec18[1]))) - (fConst66 * fRec17[1]));
		fRec41[0] = (fSlow10 + (0.999 * fRec41[1]));
		double fTemp13 = (fRec17[0] * fRec41[0]);
		fVec6[0] = fTemp13;
		fRec16[0] = (0.0 - (fConst2 * ((fConst3 * fRec16[1]) - (fTemp13 + fVec6[1]))));
		double fTemp14 = (fRec16[0] + 1.0000000000000001e-15);
		fVec7[0] = fTemp14;
		fRec15[0] = ((0.93028479253239138 * (fTemp14 + fVec7[1])) - (0.86056958506478287 * fRec15[1]));
		fRec14[0] = (fRec15[0] - ((1.8405051250752198 * fRec14[1]) + (0.86129424393186271 * fRec14[2])));
		double fTemp15 = ((0.014999999999999999 * fRec13[1]) + 1.0000000000000001e-15);
		fVec8[0] = fTemp15;
		fRec42[0] = (0.0 - (fConst68 * ((fConst69 * fRec42[1]) - (fTemp15 + fVec8[1]))));
		fRec13[0] = (double(Ftube(int(TUBE_TABLE_12AX7_250k), double((((0.92544984225177063 * (fRec14[0] + fRec14[2])) + (fRec42[0] + (1.8508996845035413 * fRec14[1]))) + -1.204285)))) + -169.71433333333334);
		fRec12[0] = ((0.025000000000000001 * ((fConst7 * fRec13[0]) + (fConst65 * fRec13[1]))) - (fConst66 * fRec12[1]));
		fRec11[0] = (0.0 - (fConst2 * ((fConst3 * fRec11[1]) - (fRec12[0] + fRec12[1]))));
		double fTemp16 = (fRec11[0] + 1.0000000000000001e-15);
		fVec9[0] = fTemp16;
		fRec10[0] = ((0.93028479253239138 * (fTemp16 + fVec9[1])) - (0.86056958506478287 * fRec10[1]));
		fRec9[0] = (fRec10[0] - ((1.8405051250752198 * fRec9[1]) + (0.86129424393186271 * fRec9[2])));
		double fTemp17 = ((0.0082000000000000007 * fRec8[1]) + 1.0000000000000001e-15);
		fVec10[0] = fTemp17;
		fRec43[0] = (0.0 - (fConst71 * ((fConst72 * fRec43[1]) - (fTemp17 + fVec10[1]))));
		fRec8[0] = (double(Ftube(int(TUBE_TABLE_12AX7_250k), double((((0.92544984225177063 * (fRec9[0] + fRec9[2])) + (fRec43[0] + (1.8508996845035413 * fRec9[1]))) + -0.84070299999999998)))) + -147.47524390243905);
		fRec7[0] = ((0.025000000000000001 * ((fConst7 * fRec8[0]) + (fConst65 * fRec8[1]))) - (fConst66 * fRec7[1]));
		fRec6[0] = ((fConst11 * fRec7[1]) - (fConst73 * ((fConst74 * fRec6[1]) - (fConst9 * fRec7[0]))));
		fRec44[0] = (0.0 - (fConst76 * ((fConst77 * fRec44[1]) - (fRec7[0] + fRec7[1]))));
		double fTemp18 = (fRec1[0] * ((fSlow1 * fRec6[0]) + (fSlow11 * fRec44[0])));
		fVec11[0] = fTemp18;
		fRec5[0] = ((0.93028479253239138 * (fTemp18 + fVec11[1])) - (0.86056958506478287 * fRec5[1]));
		fRec4[0] = (fRec5[0] - ((1.8405051250752198 * fRec4[1]) + (0.86129424393186271 * fRec4[2])));
		double fTemp19 = (0.92544984225177063 * (fRec4[0] + fRec4[2]));
		fRec45[0] = (fConst79 * ((0.098000000000000004 * (fRec3[1] + fRec3[2])) - (fConst80 * fRec45[1])));
		double fTemp20 = (1.8508996845035413 * fRec4[1]);
		fRec3[0] = (double(Ftube(int(TUBE_TABLE_6L6CG_68k), double(((fTemp19 + (fRec45[0] + fTemp20)) + -20.063656999999999)))) + -245.26880612244898);
		fRec2[0] = ((0.025000000000000001 * ((fConst7 * fRec3[0]) + (fConst65 * fRec3[1]))) - (fConst66 * fRec2[1]));
		fRec48[0] = (fConst79 * ((0.098000000000000004 * (fRec47[1] + fRec47[2])) - (fConst80 * fRec48[1])));
		fRec47[0] = (double(Ftube(int(TUBE_TABLE_6L6CG_250k), double(((fTemp19 + (fRec48[0] + fTemp20)) + -20.063656999999999)))) + -245.26880612244898);
		fRec46[0] = ((0.025000000000000001 * ((fConst7 * fRec47[0]) + (fConst65 * fRec47[1]))) - (fConst66 * fRec46[1]));
		double fTemp21 = (fRec1[0] * (fRec2[0] + fRec46[0]));
		fVec12[0] = fTemp21;
		fRec0[0] = (0.0 - (fConst2 * ((fConst3 * fRec0[1]) - (fTemp21 + fVec12[1]))));
		fRec49[0] = (fSlow12 + (0.999 * fRec49[1]));
		output0[i] = FAUSTFLOAT((fRec0[0] * fRec49[0]));
		fRec1[1] = fRec1[0];
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
		fRec23[2] = fRec23[1];
		fRec23[1] = fRec23[0];
		fRec33[1] = fRec33[0];
		fRec32[2] = fRec32[1];
		fRec32[1] = fRec32[0];
		fRec31[2] = fRec31[1];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fRec37[1] = fRec37[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		fVec2[1] = fVec2[0];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec39[1] = fRec39[0];
		fRec38[2] = fRec38[1];
		fRec38[1] = fRec38[0];
		fVec3[1] = fVec3[0];
		fRec22[1] = fRec22[0];
		fRec21[1] = fRec21[0];
		fVec4[1] = fVec4[0];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fVec5[1] = fVec5[0];
		fRec40[1] = fRec40[0];
		fRec18[1] = fRec18[0];
		fRec17[1] = fRec17[0];
		fRec41[1] = fRec41[0];
		fVec6[1] = fVec6[0];
		fRec16[1] = fRec16[0];
		fVec7[1] = fVec7[0];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fVec8[1] = fVec8[0];
		fRec42[1] = fRec42[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fVec9[1] = fVec9[0];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fVec10[1] = fVec10[0];
		fRec43[1] = fRec43[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec44[1] = fRec44[0];
		fVec11[1] = fVec11[0];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec45[1] = fRec45[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec48[1] = fRec48[0];
		fRec47[2] = fRec47[1];
		fRec47[1] = fRec47[0];
		fRec46[1] = fRec46[0];
		fVec12[1] = fVec12[0];
		fRec0[1] = fRec0[0];
		fRec49[1] = fRec49[0];
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
		fVslider2_ = (float*)data; // , 0.34999999999999998, 0.0, 1.0, 0.01 
		break;
	case PREGAIN: 
		fVslider3_ = (float*)data; // , -6.0, -20.0, 20.0, 0.10000000000000001 
		break;
	case GAIN1: 
		fVslider0_ = (float*)data; // , -6.0, -20.0, 20.0, 0.10000000000000001 
		break;
	case TONE: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   PREGAIN, 
   GAIN1, 
   TONE, 
} PortIndex;
*/

} // end namespace gxmetal_head
