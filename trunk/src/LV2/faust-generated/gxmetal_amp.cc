// generated from file '../src/LV2/faust/gxmetal_amp.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "valve.h"

namespace gxmetal_amp {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst2;
	double fConst4;
	double fConst5;
	double fConst8;
	double fConst9;
	double fConst11;
	double fConst12;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fConst13;
	double fConst14;
	double fConst15;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst19;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fVec0[2];
	double fRec20[2];
	double fRec19[3];
	double fConst21;
	double fVec1[2];
	double fConst22;
	double fRec21[2];
	double fRec18[2];
	double fConst23;
	double fConst24;
	double fRec17[2];
	double fConst26;
	double fConst27;
	double fRec22[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec23[2];
	double fVec2[2];
	double fConst29;
	double fConst30;
	double fRec16[2];
	double fRec15[2];
	double fRec14[3];
	double fConst32;
	double fVec3[2];
	double fConst33;
	double fRec24[2];
	double fRec13[2];
	double fRec12[2];
	double fRec25[2];
	double fVec4[2];
	double fRec11[2];
	double fRec10[2];
	double fRec9[3];
	double fConst35;
	double fVec5[2];
	double fConst36;
	double fRec26[2];
	double fRec8[2];
	double fRec7[2];
	double fRec27[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec28[2];
	double fRec6[4];
	double fConst37;
	double fConst38;
	double fConst39;
	double fRec5[2];
	double fVec6[2];
	double fRec4[2];
	double fRec3[3];
	double fConst41;
	double fConst42;
	double fRec29[2];
	double fRec2[3];
	double fRec31[2];
	double fRec30[3];
	double fRec1[3];
	double fConst43;
	double fRec0[3];
	double fRec32[2];

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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fVec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec20[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRec19[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fVec1[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec21[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec18[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec17[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec22[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec23[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fVec2[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec16[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec15[l11] = 0.0;
	for (int l12 = 0; l12 < 3; l12 = l12 + 1) fRec14[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fVec3[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec24[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec13[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec12[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec25[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fVec4[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec11[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec10[l20] = 0.0;
	for (int l21 = 0; l21 < 3; l21 = l21 + 1) fRec9[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fVec5[l22] = 0.0;
	for (int l23 = 0; l23 < 2; l23 = l23 + 1) fRec26[l23] = 0.0;
	for (int l24 = 0; l24 < 2; l24 = l24 + 1) fRec8[l24] = 0.0;
	for (int l25 = 0; l25 < 2; l25 = l25 + 1) fRec7[l25] = 0.0;
	for (int l26 = 0; l26 < 2; l26 = l26 + 1) fRec27[l26] = 0.0;
	for (int l27 = 0; l27 < 2; l27 = l27 + 1) fRec28[l27] = 0.0;
	for (int l28 = 0; l28 < 4; l28 = l28 + 1) fRec6[l28] = 0.0;
	for (int l29 = 0; l29 < 2; l29 = l29 + 1) fRec5[l29] = 0.0;
	for (int l30 = 0; l30 < 2; l30 = l30 + 1) fVec6[l30] = 0.0;
	for (int l31 = 0; l31 < 2; l31 = l31 + 1) fRec4[l31] = 0.0;
	for (int l32 = 0; l32 < 3; l32 = l32 + 1) fRec3[l32] = 0.0;
	for (int l33 = 0; l33 < 2; l33 = l33 + 1) fRec29[l33] = 0.0;
	for (int l34 = 0; l34 < 3; l34 = l34 + 1) fRec2[l34] = 0.0;
	for (int l35 = 0; l35 < 2; l35 = l35 + 1) fRec31[l35] = 0.0;
	for (int l36 = 0; l36 < 3; l36 = l36 + 1) fRec30[l36] = 0.0;
	for (int l37 = 0; l37 < 3; l37 = l37 + 1) fRec1[l37] = 0.0;
	for (int l38 = 0; l38 < 3; l38 = l38 + 1) fRec0[l38] = 0.0;
	for (int l39 = 0; l39 < 2; l39 = l39 + 1) fRec32[l39] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = std::tan(37699.11184307752 / fConst0);
	fConst2 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst1));
	double fConst3 = 1.0 / fConst1;
	fConst4 = (fConst3 + -1.414213562373095) / fConst1 + 1.0;
	fConst5 = 1.0 / ((fConst3 + 1.414213562373095) / fConst1 + 1.0);
	double fConst6 = std::tan(125.66370614359172 / fConst0);
	double fConst7 = mydsp_faustpower2_f(fConst6);
	fConst8 = 1.0 / fConst7;
	fConst9 = 2.0 * (1.0 - fConst8);
	double fConst10 = 1.0 / fConst6;
	fConst11 = (fConst10 + -1.414213562373095) / fConst6 + 1.0;
	fConst12 = 1.0 / ((fConst10 + 1.414213562373095) / fConst6 + 1.0);
	fConst13 = 2.0 * fConst0;
	fConst14 = mydsp_faustpower2_f(fConst13);
	fConst15 = mydsp_faustpower3_f(fConst13);
	double fConst16 = std::tan(97.38937226128358 / fConst0);
	double fConst17 = 1.0 / fConst16;
	double fConst18 = fConst17 + 1.0;
	fConst19 = (1.0 - fConst17) / fConst18;
	double fConst20 = 1.0 / std::tan(270.1769682087222 / fConst0);
	fConst21 = 1.0 - fConst20;
	fConst22 = 1.0 / (fConst20 + 1.0);
	fConst23 = 1.0 / (fConst16 * fConst18);
	fConst24 = 0.0 - fConst23;
	double fConst25 = 3.141592653589793 / fConst0;
	fConst26 = 1.0 - fConst25;
	fConst27 = 1.0 / (fConst25 + 1.0);
	double fConst28 = 1.0 / std::tan(20517.741620594938 / fConst0);
	fConst29 = 1.0 - fConst28;
	fConst30 = 1.0 / (fConst28 + 1.0);
	double fConst31 = 1.0 / std::tan(414.6902302738527 / fConst0);
	fConst32 = 1.0 - fConst31;
	fConst33 = 1.0 / (fConst31 + 1.0);
	double fConst34 = 1.0 / std::tan(609.4689747964198 / fConst0);
	fConst35 = 1.0 - fConst34;
	fConst36 = 1.0 / (fConst34 + 1.0);
	fConst37 = 3.0 * fConst15;
	fConst38 = std::exp(0.0 - 0.1 / fConst0);
	fConst39 = std::exp(0.0 - 2e+02 / fConst0);
	double fConst40 = 1.0 / std::tan(804.247719318987 / fConst0);
	fConst41 = 1.0 - fConst40;
	fConst42 = 1.0 / (fConst40 + 1.0);
	fConst43 = 0.0 - 2.0 / fConst7;
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
	double fSlow1 = std::exp(3.4 * (0.0 - fSlow0));
	double fSlow2 = fConst14 * (3.1361660000000006e-05 * fSlow1 + 6.993481000000001e-07);
	double fSlow3 = fConst15 * (5.967937800000002e-09 * fSlow1 + 2.9839689000000005e-11);
	double fSlow4 = 0.022470000000000004 * fSlow1;
	double fSlow5 = fConst13 * (fSlow4 + 0.0026376999999999998);
	double fSlow6 = fSlow5 + fSlow3 + (-1.0 - fSlow2);
	double fSlow7 = fSlow5 + fSlow2;
	double fSlow8 = fSlow7 - 3.0 * (fSlow3 + 1.0);
	double fSlow9 = fSlow2 - (fSlow5 + 3.0 * (1.0 - fSlow3));
	double fSlow10 = 1.0 / (-1.0 - (fSlow7 + fSlow3));
	int iSlow11 = int(double(fCheckbox0));
	int iSlow12 = int(double(fCheckbox1));
	double fSlow13 = double(fVslider1);
	double fSlow14 = fSlow13 + -1.0;
	double fSlow15 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider2));
	double fSlow16 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider3));
	double fSlow17 = fConst14 * (4.859800000000001e-07 * fSlow0 + 8.613660000000003e-06 * fSlow1 + 9.962810000000002e-08);
	double fSlow18 = 6.221578000000002e-10 * fSlow1 + fSlow0 * (5.345780000000001e-09 * fSlow1 + 2.6728900000000006e-11) + 3.1107890000000005e-12;
	double fSlow19 = fConst15 * fSlow18;
	double fSlow20 = fConst13 * (fSlow4 + 0.00023500000000000002 * fSlow0 + 0.0003347);
	double fSlow21 = fSlow20 + fSlow19 - fSlow17;
	double fSlow22 = fConst37 * fSlow18;
	double fSlow23 = fSlow20 + fSlow17;
	double fSlow24 = fSlow23 - fSlow22;
	double fSlow25 = fSlow17 + fSlow22 - fSlow20;
	double fSlow26 = 0.0 - (fSlow23 + fSlow19);
	double fSlow27 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * (0.0 - 0.4 * fSlow13));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		double fTemp1 = std::fabs(fTemp0);
		double fTemp2 = fTemp0 * (fSlow13 + fTemp1) / (mydsp_faustpower2_f(fTemp0) + fSlow14 * fTemp1 + 1.0);
		fVec0[0] = fTemp2;
		fRec20[0] = 0.9302847925323914 * (fTemp2 + fVec0[1]) - 0.8605695850647829 * fRec20[1];
		fRec19[0] = fRec20[0] - (1.8405051250752198 * fRec19[1] + 0.8612942439318627 * fRec19[2]);
		double fTemp3 = 1.8508996845035413 * fRec19[1];
		double fTemp4 = 0.9254498422517706 * (fRec19[0] + fRec19[2]);
		double fTemp5 = (fTemp3 + fTemp4) / (Ranode(TUBE_TABLE_12AY7_68k, fRec18[1]) + 1e+05);
		fVec1[0] = fTemp5;
		fRec21[0] = fConst22 * (2.7e+03 * (fTemp5 + fVec1[1]) - fConst21 * fRec21[1]);
		fRec18[0] = Ftube(TUBE_TABLE_12AY7_68k, fTemp4 + fRec21[0] + fTemp3 + -2.775058) + -147.2200740740741;
		fRec17[0] = 0.025 * (fConst23 * fRec18[0] + fConst24 * fRec18[1]) - fConst19 * fRec17[1];
		fRec22[0] = fConst27 * (fConst26 * fRec22[1] + 0.025 * (fRec18[0] - fRec18[1]));
		fRec23[0] = fSlow15 + 0.999 * fRec23[1];
		double fTemp6 = fRec23[0] * ((iSlow12) ? fRec22[0] : fRec17[0]);
		fVec2[0] = fTemp6;
		fRec16[0] = 0.0 - fConst30 * (fConst29 * fRec16[1] - (fTemp6 + fVec2[1]));
		fRec15[0] = 0.9302847925323914 * (fRec16[0] + fRec16[1]) - 0.8605695850647829 * fRec15[1];
		fRec14[0] = fRec15[0] - (1.8405051250752198 * fRec14[1] + 0.8612942439318627 * fRec14[2]);
		double fTemp7 = 1.8508996845035413 * fRec14[1];
		double fTemp8 = 0.9254498422517706 * (fRec14[0] + fRec14[2]);
		double fTemp9 = (fTemp7 + fTemp8) / (Ranode(TUBE_TABLE_12AY7_250k, fRec13[1]) + 1e+05);
		fVec3[0] = fTemp9;
		fRec24[0] = fConst33 * (1.5e+03 * (fTemp9 + fVec3[1]) - fConst32 * fRec24[1]);
		fRec13[0] = Ftube(TUBE_TABLE_12AY7_250k, fTemp8 + fRec24[0] + fTemp7 + -1.954308) + -119.71279999999999;
		fRec12[0] = 0.025 * (fConst23 * fRec13[0] + fConst24 * fRec13[1]) - fConst19 * fRec12[1];
		fRec25[0] = fConst27 * (fConst26 * fRec25[1] + 0.025 * (fRec13[0] - fRec13[1]));
		double fTemp10 = ((iSlow12) ? fRec25[0] : fRec12[0]);
		fVec4[0] = fTemp10;
		fRec11[0] = 0.0 - fConst30 * (fConst29 * fRec11[1] - (fTemp10 + fVec4[1]));
		fRec10[0] = 0.9302847925323914 * (fRec11[0] + fRec11[1]) - 0.8605695850647829 * fRec10[1];
		fRec9[0] = fRec10[0] - (1.8405051250752198 * fRec9[1] + 0.8612942439318627 * fRec9[2]);
		double fTemp11 = 1.8508996845035413 * fRec9[1];
		double fTemp12 = 0.9254498422517706 * (fRec9[0] + fRec9[2]);
		double fTemp13 = (fTemp11 + fTemp12) / (Ranode(TUBE_TABLE_12AY7_250k, fRec8[1]) + 1e+05);
		fVec5[0] = fTemp13;
		fRec26[0] = fConst36 * (8.2e+02 * (fTemp13 + fVec5[1]) - fConst35 * fRec26[1]);
		fRec8[0] = Ftube(TUBE_TABLE_12AY7_250k, fTemp12 + fRec26[0] + fTemp11 + -1.264916) + -95.7419512195122;
		fRec7[0] = 0.025 * (fConst23 * fRec8[0] + fConst24 * fRec8[1]) - fConst19 * fRec7[1];
		fRec27[0] = fConst27 * (fConst26 * fRec27[1] + 0.025 * (fRec8[0] - fRec8[1]));
		fRec28[0] = fSlow16 + 0.999 * fRec28[1];
		fRec6[0] = fRec28[0] * ((iSlow11) ? fRec27[0] : fRec7[0]) - fSlow10 * (fSlow9 * fRec6[1] + fSlow8 * fRec6[2] + fSlow6 * fRec6[3]);
		double fTemp14 = fSlow26 * fRec6[0] + fSlow25 * fRec6[1] + fSlow24 * fRec6[2] + fSlow21 * fRec6[3];
		double fTemp15 = std::max<double>(1.0, std::fabs(fSlow10 * fTemp14));
		double fTemp16 = fConst39 * double(fRec5[1] < fTemp15) + fConst38 * double(fRec5[1] >= fTemp15);
		fRec5[0] = fRec5[1] * fTemp16 + fTemp15 * (1.0 - fTemp16);
		double fTemp17 = std::max<double>(0.0, 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec5[0])) + 5e+01);
		double fTemp18 = 0.5 * std::min<double>(1.0, std::max<double>(0.0, 0.09522902580706599 * fTemp17));
		double fTemp19 = fSlow10 * fTemp14 * std::pow(1e+01, 0.05 * (fTemp17 * (0.0 - fTemp18) / (fTemp18 + 1.0) + 1e+01));
		fVec6[0] = fTemp19;
		fRec4[0] = 0.9302847925323914 * (fTemp19 + fVec6[1]) - 0.8605695850647829 * fRec4[1];
		fRec3[0] = fRec4[0] - (1.8405051250752198 * fRec3[1] + 0.8612942439318627 * fRec3[2]);
		double fTemp20 = 1.8508996845035413 * fRec3[1];
		fRec29[0] = fConst42 * (0.06571428571428571 * (fRec2[1] + fRec2[2]) - fConst41 * fRec29[1]);
		double fTemp21 = 0.9254498422517706 * (fRec3[0] + fRec3[2]);
		fRec2[0] = Ftube(TUBE_TABLE_EL34_250k, fTemp21 + fRec29[0] + fTemp20 + -15.743945) + -255.41822826086957;
		fRec31[0] = fConst42 * (0.06571428571428571 * (fRec30[1] + fRec30[2]) - fConst41 * fRec31[1]);
		fRec30[0] = Ftube(TUBE_TABLE_EL34_68k, fTemp21 + fRec31[0] + fTemp20 + -15.743945) + -255.41822826086957;
		fRec1[0] = 0.1 * (fRec30[0] + fRec2[0]) - fConst12 * (fConst11 * fRec1[2] + fConst9 * fRec1[1]);
		fRec0[0] = fConst12 * (fConst8 * fRec1[0] + fConst43 * fRec1[1] + fConst8 * fRec1[2]) - fConst5 * (fConst4 * fRec0[2] + fConst2 * fRec0[1]);
		fRec32[0] = fSlow27 + 0.999 * fRec32[1];
		output0[i0] = FAUSTFLOAT(fConst5 * fRec28[0] * fRec32[0] * (fRec0[2] + fRec0[0] + 2.0 * fRec0[1]));
		fVec0[1] = fVec0[0];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fVec1[1] = fVec1[0];
		fRec21[1] = fRec21[0];
		fRec18[1] = fRec18[0];
		fRec17[1] = fRec17[0];
		fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fVec2[1] = fVec2[0];
		fRec16[1] = fRec16[0];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fVec3[1] = fVec3[0];
		fRec24[1] = fRec24[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec25[1] = fRec25[0];
		fVec4[1] = fVec4[0];
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fVec5[1] = fVec5[0];
		fRec26[1] = fRec26[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
			fRec6[j0] = fRec6[j0 - 1];
		}
		fRec5[1] = fRec5[0];
		fVec6[1] = fVec6[0];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec29[1] = fRec29[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec31[1] = fRec31[0];
		fRec30[2] = fRec30[1];
		fRec30[1] = fRec30[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		fRec32[1] = fRec32[0];
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
		fVslider1_ = (float*)data; // , 1.0, 1.0, 2e+01, 0.1 
		break;
	case PREGAIN: 
		fVslider2_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
		break;
	case TONE: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   HIGHGAIN, 
   PREGAIN, 
   TONE, 
   GAIN1, 
} PortIndex;
*/

} // end namespace gxmetal_amp
