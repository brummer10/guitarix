// generated from file '../src/LV2/faust/gxtubetremelo.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "input12ax7_neg_table.h"
#include "input12ax7_table.h"
#include "math.h"
#include "output12ax7_neg_table.h"
#include "output12ax7_table.h"

namespace gxtubetremelo {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	int iVec0[2];
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fConst5;
	int iRec3[2];
	int iRec2[2];
	double fConst6;
	double fRec6[2];
	double fRec5[2];
	double fRec4[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec1[2];
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
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
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fVec1[2];
	double fConst38;
	double fConst39;
	double fRec15[2];
	double fRec14[3];
	double fVec2[2];
	double fConst40;
	double fConst41;
	double fConst42;
	double fRec13[2];
	double fRec12[3];
	double fVec3[2];
	double fConst43;
	double fConst44;
	double fConst45;
	double fRec11[2];
	double fRec10[3];
	double fVec4[2];
	double fConst46;
	double fConst47;
	double fConst48;
	double fRec9[2];
	double fRec8[3];
	double fRec7[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec16[2];
	double fConst49;
	double fRec0[2];
	double fConst50;
	double fConst51;
	double fRec20[2];
	double fRec19[3];
	double fConst52;
	double fRec18[2];
	double fRec17[2];
	double fConst53;
	double fConst54;
	double fConst55;
	double fRec25[2];
	double fRec24[3];
	double fConst56;
	double fRec23[3];
	double fRec22[2];
	double fRec21[2];
	double fConst57;
	double fConst58;
	double fConst59;
	double fRec31[2];
	double fRec30[3];
	double fConst60;
	double fRec29[3];
	double fRec28[3];
	double fRec27[2];
	double fRec26[2];
	double fConst61;
	double fConst62;
	double fRec38[2];
	double fRec37[3];
	double fConst63;
	double fRec36[3];
	double fRec35[3];
	double fRec34[3];
	double fRec33[2];
	double fRec32[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec39[2];

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
	id = "gxtubetremelo";
	name = N_("Tube Tremolo");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) iVec0[l0] = 0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) iRec3[l1] = 0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) iRec2[l2] = 0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec6[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec5[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec4[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec1[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fVec1[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec15[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec14[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fVec2[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec13[l11] = 0.0;
	for (int l12 = 0; l12 < 3; l12 = l12 + 1) fRec12[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fVec3[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec11[l14] = 0.0;
	for (int l15 = 0; l15 < 3; l15 = l15 + 1) fRec10[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fVec4[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec9[l17] = 0.0;
	for (int l18 = 0; l18 < 3; l18 = l18 + 1) fRec8[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec7[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec16[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec0[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec20[l22] = 0.0;
	for (int l23 = 0; l23 < 3; l23 = l23 + 1) fRec19[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec18[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec17[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec25[l26] = 0.0;
	for (int l27 = 0; l27 < 3; l27 = l27 + 1) fRec24[l27] = 0.0;
	for (int l28 = 0; l28 < 3; l28 = l28 + 1) fRec23[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec22[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fRec21[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec31[l31] = 0.0;
	for (int l32 = 0; l32 < 3; l32 = l32 + 1) fRec30[l32] = 0.0;
	for (int l33 = 0; l33 < 3; l33 = l33 + 1) fRec29[l33] = 0.0;
	for (int l34 = 0; l34 < 3; l34 = l34 + 1) fRec28[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec27[l35] = 0.0;
	for (int l36 = 0; l36 < 2; l36 = l36 + 1) fRec26[l36] = 0.0;
	for (int l37 = 0; l37 < 2; l37 = l37 + 1) fRec38[l37] = 0.0;
	for (int l38 = 0; l38 < 3; l38 = l38 + 1) fRec37[l38] = 0.0;
	for (int l39 = 0; l39 < 3; l39 = l39 + 1) fRec36[l39] = 0.0;
	for (int l40 = 0; l40 < 3; l40 = l40 + 1) fRec35[l40] = 0.0;
	for (int l41 = 0; l41 < 3; l41 = l41 + 1) fRec34[l41] = 0.0;
	for (int l42 = 0; l42 < 2; l42 = l42 + 1) fRec33[l42] = 0.0;
	for (int l43 = 0; l43 < 2; l43 = l43 + 1) fRec32[l43] = 0.0;
	for (int l44 = 0; l44 < 2; l44 = l44 + 1) fRec39[l44] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 2.08240830168832e-05 * fConst0;
	fConst2 = fConst1 + 0.000444015189606219;
	fConst3 = (0.000444015189606219 - fConst1) / fConst2;
	fConst4 = 1.0 / fConst0;
	fConst5 = 0.5 * fConst0;
	fConst6 = 6.283185307179586 / fConst0;
	fConst7 = 2.08240500698813e-05 * fConst0;
	fConst8 = fConst7 + 0.000445596645695992;
	fConst9 = (0.000445596645695992 - fConst7) / fConst8;
	fConst10 = std::tan(270.1769682087222 / fConst0);
	fConst11 = mydsp_faustpower2_f(fConst10);
	fConst12 = 2.0 * (1.0 - 1.0 / fConst11);
	fConst13 = 1.0 / fConst10;
	fConst14 = (fConst13 + -1.0000000000000004) / fConst10 + 1.0;
	fConst15 = (fConst13 + 1.0000000000000004) / fConst10 + 1.0;
	fConst16 = 1.0 / fConst15;
	fConst17 = std::tan(659.7344572538566 / fConst0);
	fConst18 = mydsp_faustpower2_f(fConst17);
	fConst19 = 2.0 * (1.0 - 1.0 / fConst18);
	fConst20 = 1.0 / fConst17;
	fConst21 = (fConst20 + -1.0000000000000004) / fConst17 + 1.0;
	fConst22 = (fConst20 + 1.0000000000000004) / fConst17 + 1.0;
	fConst23 = 1.0 / fConst22;
	fConst24 = std::tan(3769.9111843077517 / fConst0);
	fConst25 = mydsp_faustpower2_f(fConst24);
	fConst26 = 2.0 * (1.0 - 1.0 / fConst25);
	fConst27 = 1.0 / fConst24;
	fConst28 = (fConst27 + -1.0000000000000004) / fConst24 + 1.0;
	fConst29 = (fConst27 + 1.0000000000000004) / fConst24 + 1.0;
	fConst30 = 1.0 / fConst29;
	fConst31 = std::tan(20517.741620594938 / fConst0);
	fConst32 = mydsp_faustpower2_f(fConst31);
	fConst33 = 2.0 * (1.0 - 1.0 / fConst32);
	fConst34 = 1.0 / fConst31;
	fConst35 = (fConst34 + -1.0000000000000004) / fConst31 + 1.0;
	fConst36 = (fConst34 + 1.0000000000000004) / fConst31 + 1.0;
	fConst37 = 1.0 / fConst36;
	fConst38 = 1.0 - fConst34;
	fConst39 = 1.0 / (fConst34 + 1.0);
	fConst40 = 1.0 - fConst27;
	fConst41 = fConst27 + 1.0;
	fConst42 = 1.0 / fConst41;
	fConst43 = 1.0 - fConst20;
	fConst44 = fConst20 + 1.0;
	fConst45 = 1.0 / fConst44;
	fConst46 = 1.0 - fConst13;
	fConst47 = fConst13 + 1.0;
	fConst48 = 1.0 / fConst47;
	fConst49 = 0.000697428436220861 * (fConst0 / fConst8);
	fConst50 = 0.000617187446540506 * (fConst0 / fConst2);
	fConst51 = 1.0 / (fConst10 * fConst22);
	fConst52 = 1.0 / (fConst11 * fConst15);
	fConst53 = 1.0 - fConst46 / fConst10;
	fConst54 = 1.0 / (fConst47 / fConst10 + 1.0);
	fConst55 = 1.0 / (fConst17 * fConst29);
	fConst56 = 1.0 / (fConst18 * fConst22);
	fConst57 = 1.0 - fConst43 / fConst17;
	fConst58 = 1.0 / (fConst44 / fConst17 + 1.0);
	fConst59 = 1.0 / (fConst24 * fConst36);
	fConst60 = 1.0 / (fConst25 * fConst29);
	fConst61 = 1.0 - fConst40 / fConst24;
	fConst62 = 1.0 / (fConst41 / fConst24 + 1.0);
	fConst63 = 1.0 / (fConst32 * fConst36);
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
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	int iSlow0 = int(double(fCheckbox0));
	double fSlow1 = double(fVslider0);
	int iSlow2 = int(fConst5 / fSlow1);
	double fSlow3 = 1.0 / double(iSlow2);
	double fSlow4 = fConst6 * fSlow1;
	double fSlow5 = double(fVslider1);
	double fSlow6 = 0.004073836948085289 * (std::exp(double(fVslider2)) + -1.0);
	double fSlow7 = 0.007000000000000006 * std::pow(1e+01, 0.05 * double(fVslider3));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		iVec0[0] = 1;
		double fTemp0 = fRec1[1] * (1.0 - fConst4 / (fConst4 + 0.06 * std::exp(-(2.4849066497880004 * fRec1[1]))));
		iRec3[0] = ((iRec3[1] > 0) ? 2 * (iRec2[1] < iSlow2) + -1 : 1 - 2 * (iRec2[1] > 0));
		iRec2[0] = iRec3[0] + iRec2[1];
		fRec6[0] = fRec6[1] - fSlow4 * fRec4[1];
		fRec5[0] = fSlow4 * fRec6[0] + double(1 - iVec0[1]) + fRec5[1];
		fRec4[0] = fRec5[0];
		fRec1[0] = fTemp0 + fConst4 * (std::pow(1.0 - fSlow5 * (1.0 - ((iSlow0) ? std::max<double>(0.0, 0.5 * (fRec4[0] + 1.0)) : fSlow3 * double(iRec2[0]))), 1.9) / (fConst4 + 0.06 * std::exp(-(2.4849066497880004 * fTemp0))));
		double fTemp1 = std::exp(13.815510557964274 / std::log(8.551967507929417 * fRec1[0] + 2.718281828459045)) + 2.7e+03;
		double fTemp2 = double(input0[i0]);
		fVec1[0] = fTemp2;
		fRec15[0] = -(fConst39 * (fConst38 * fRec15[1] - (fTemp2 + fVec1[1])));
		fRec14[0] = fRec15[0] - fConst37 * (fConst35 * fRec14[2] + fConst33 * fRec14[1]);
		double fTemp3 = fRec14[2] + fRec14[0] + 2.0 * fRec14[1];
		fVec2[0] = fTemp3;
		fRec13[0] = -(fConst42 * (fConst40 * fRec13[1] - fConst37 * (fTemp3 + fVec2[1])));
		fRec12[0] = fRec13[0] - fConst30 * (fConst28 * fRec12[2] + fConst26 * fRec12[1]);
		double fTemp4 = fRec12[2] + fRec12[0] + 2.0 * fRec12[1];
		fVec3[0] = fTemp4;
		fRec11[0] = -(fConst45 * (fConst43 * fRec11[1] - fConst30 * (fTemp4 + fVec3[1])));
		fRec10[0] = fRec11[0] - fConst23 * (fConst21 * fRec10[2] + fConst19 * fRec10[1]);
		double fTemp5 = fRec10[2] + fRec10[0] + 2.0 * fRec10[1];
		fVec4[0] = fTemp5;
		fRec9[0] = -(fConst48 * (fConst46 * fRec9[1] - fConst23 * (fTemp5 + fVec4[1])));
		fRec8[0] = fRec9[0] - fConst16 * (fConst14 * fRec8[2] + fConst12 * fRec8[1]);
		fRec7[0] = fConst16 * (fRec8[2] + fRec8[0] + 2.0 * fRec8[1]) - fConst9 * fRec7[1];
		fRec16[0] = fSlow6 + 0.993 * fRec16[1];
		double fTemp6 = fConst49 * fRec16[0] * (fRec7[0] - fRec7[1]);
		fRec0[0] = 2.7e+03 * (((signbit(-fTemp6)) ? input12ax7_negclip(-fTemp6) : input12ax7clip(-fTemp6)) / fTemp1) - fConst3 * fRec0[1];
		double fTemp7 = fConst50 * (fRec0[0] - fRec0[1]);
		fRec20[0] = -(fConst48 * (fConst46 * fRec20[1] - fConst51 * (fTemp5 - fVec4[1])));
		fRec19[0] = fRec20[0] - fConst16 * (fConst14 * fRec19[2] + fConst12 * fRec19[1]);
		fRec18[0] = fConst52 * (fRec19[2] + (fRec19[0] - 2.0 * fRec19[1])) - fConst9 * fRec18[1];
		double fTemp8 = fConst49 * fRec16[0] * (fRec18[0] - fRec18[1]);
		fRec17[0] = 2.7e+03 * (((signbit(-fTemp8)) ? input12ax7_negclip(-fTemp8) : input12ax7clip(-fTemp8)) / fTemp1) - fConst3 * fRec17[1];
		double fTemp9 = fConst50 * (fRec17[0] - fRec17[1]);
		double fTemp10 = fConst12 * fRec23[1];
		fRec25[0] = -(fConst45 * (fConst43 * fRec25[1] - fConst55 * (fTemp4 - fVec3[1])));
		fRec24[0] = fRec25[0] - fConst23 * (fConst21 * fRec24[2] + fConst19 * fRec24[1]);
		fRec23[0] = fConst56 * (fRec24[2] + (fRec24[0] - 2.0 * fRec24[1])) - fConst54 * (fConst53 * fRec23[2] + fTemp10);
		fRec22[0] = fRec23[2] + fConst54 * (fTemp10 + fConst53 * fRec23[0]) - fConst9 * fRec22[1];
		double fTemp11 = fConst49 * fRec16[0] * (fRec22[0] - fRec22[1]);
		fRec21[0] = 2.7e+03 * (((signbit(-fTemp11)) ? input12ax7_negclip(-fTemp11) : input12ax7clip(-fTemp11)) / fTemp1) - fConst3 * fRec21[1];
		double fTemp12 = fConst50 * (fRec21[0] - fRec21[1]);
		double fTemp13 = fConst12 * fRec28[1];
		double fTemp14 = fConst19 * fRec29[1];
		fRec31[0] = -(fConst42 * (fConst40 * fRec31[1] - fConst59 * (fTemp3 - fVec2[1])));
		fRec30[0] = fRec31[0] - fConst30 * (fConst28 * fRec30[2] + fConst26 * fRec30[1]);
		fRec29[0] = fConst60 * (fRec30[2] + (fRec30[0] - 2.0 * fRec30[1])) - fConst58 * (fConst57 * fRec29[2] + fTemp14);
		fRec28[0] = fRec29[2] + fConst58 * (fTemp14 + fConst57 * fRec29[0]) - fConst54 * (fConst53 * fRec28[2] + fTemp13);
		fRec27[0] = fRec28[2] + fConst54 * (fTemp13 + fConst53 * fRec28[0]) - fConst9 * fRec27[1];
		double fTemp15 = fConst49 * fRec16[0] * (fRec27[0] - fRec27[1]);
		fRec26[0] = 2.7e+03 * (((signbit(-fTemp15)) ? input12ax7_negclip(-fTemp15) : input12ax7clip(-fTemp15)) / fTemp1) - fConst3 * fRec26[1];
		double fTemp16 = fConst50 * (fRec26[0] - fRec26[1]);
		double fTemp17 = fConst12 * fRec34[1];
		double fTemp18 = fConst19 * fRec35[1];
		double fTemp19 = fConst26 * fRec36[1];
		fRec38[0] = -(fConst39 * (fConst38 * fRec38[1] - fConst34 * (fTemp2 - fVec1[1])));
		fRec37[0] = fRec38[0] - fConst37 * (fConst35 * fRec37[2] + fConst33 * fRec37[1]);
		fRec36[0] = fConst63 * (fRec37[2] + (fRec37[0] - 2.0 * fRec37[1])) - fConst62 * (fConst61 * fRec36[2] + fTemp19);
		fRec35[0] = fRec36[2] + fConst62 * (fTemp19 + fConst61 * fRec36[0]) - fConst58 * (fConst57 * fRec35[2] + fTemp18);
		fRec34[0] = fRec35[2] + fConst58 * (fTemp18 + fConst57 * fRec35[0]) - fConst54 * (fConst53 * fRec34[2] + fTemp17);
		fRec33[0] = fRec34[2] + fConst54 * (fTemp17 + fConst53 * fRec34[0]) - fConst9 * fRec33[1];
		double fTemp20 = fConst49 * fRec16[0] * (fRec33[0] - fRec33[1]);
		fRec32[0] = 2.7e+03 * (((signbit(-fTemp20)) ? input12ax7_negclip(-fTemp20) : input12ax7clip(-fTemp20)) / fTemp1) - fConst3 * fRec32[1];
		double fTemp21 = fConst50 * (fRec32[0] - fRec32[1]);
		fRec39[0] = fSlow7 + 0.993 * fRec39[1];
		output0[i0] = FAUSTFLOAT(fRec39[0] * (((signbit(-fTemp21)) ? output12ax7_negclip(-fTemp21) : output12ax7clip(-fTemp21)) + ((signbit(-fTemp16)) ? output12ax7_negclip(-fTemp16) : output12ax7clip(-fTemp16)) + ((signbit(-fTemp12)) ? output12ax7_negclip(-fTemp12) : output12ax7clip(-fTemp12)) + ((signbit(-fTemp9)) ? output12ax7_negclip(-fTemp9) : output12ax7clip(-fTemp9)) + ((signbit(-fTemp7)) ? output12ax7_negclip(-fTemp7) : output12ax7clip(-fTemp7))));
		iVec0[1] = iVec0[0];
		iRec3[1] = iRec3[0];
		iRec2[1] = iRec2[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec1[1] = fRec1[0];
		fVec1[1] = fVec1[0];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fVec2[1] = fVec2[0];
		fRec13[1] = fRec13[0];
		fRec12[2] = fRec12[1];
		fRec12[1] = fRec12[0];
		fVec3[1] = fVec3[0];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fVec4[1] = fVec4[0];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec16[1] = fRec16[0];
		fRec0[1] = fRec0[0];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec17[1] = fRec17[0];
		fRec25[1] = fRec25[0];
		fRec24[2] = fRec24[1];
		fRec24[1] = fRec24[0];
		fRec23[2] = fRec23[1];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec21[1] = fRec21[0];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fRec29[2] = fRec29[1];
		fRec29[1] = fRec29[0];
		fRec28[2] = fRec28[1];
		fRec28[1] = fRec28[0];
		fRec27[1] = fRec27[0];
		fRec26[1] = fRec26[0];
		fRec38[1] = fRec38[0];
		fRec37[2] = fRec37[1];
		fRec37[1] = fRec37[0];
		fRec36[2] = fRec36[1];
		fRec36[1] = fRec36[0];
		fRec35[2] = fRec35[1];
		fRec35[1] = fRec35[0];
		fRec34[2] = fRec34[1];
		fRec34[1] = fRec34[0];
		fRec33[1] = fRec33[0];
		fRec32[1] = fRec32[0];
		fRec39[1] = fRec39[0];
	}
#undef fCheckbox0
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
	// static const value_pair fCheckbox0_values[] = {{"os.triangle"},{"sine"},{0}};
	case SINEWAVE: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case DRIVE: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case DEPTH: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case OUTPUT: 
		fVslider3_ = (float*)data; // , 0.0, -2e+01, 2e+01, 0.1 
		break;
	case SPEED: 
		fVslider0_ = (float*)data; // , 5.0, 0.1, 14.0, 0.1 
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
   SINEWAVE, 
   DEPTH, 
   OUTPUT, 
   SPEED, 
} PortIndex;
*/

} // end namespace gxtubetremelo
