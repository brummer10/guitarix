// generated from file '../src/LV2/faust/gx_studiopre_st.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#include "valve.h"

namespace gx_studiopre_st {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst6;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fConst7;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fVec0[2];
	double fRec9[2];
	double fRec8[3];
	double fConst8;
	double fConst9;
	double fConst10;
	double fVec1[2];
	double fRec10[2];
	double fRec7[2];
	double fConst11;
	double fConst12;
	double fRec6[2];
	double fConst13;
	double fRec5[4];
	double fVec2[2];
	double fRec4[2];
	double fVec3[2];
	double fRec3[2];
	double fRec2[3];
	double fVec4[2];
	double fRec11[2];
	double fRec1[2];
	double fRec0[2];
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT	*fVslider4_;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT	*fVslider5_;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT	*fVslider6_;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT	*fVslider7_;
	double fVec5[2];
	double fRec21[2];
	double fRec20[3];
	double fVec6[2];
	double fRec22[2];
	double fRec19[2];
	double fRec18[2];
	double fRec17[4];
	double fVec7[2];
	double fRec16[2];
	double fVec8[2];
	double fRec15[2];
	double fRec14[3];
	double fVec9[2];
	double fRec23[2];
	double fRec13[2];
	double fRec12[2];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "gx_studiopre_st";
	name = N_("gx_studiopre_st");
	mono_audio = 0;
	stereo_audio = compute_static;
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fVec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec9[l1] = 0.0;
	for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) fRec8[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fVec1[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec10[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec7[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec6[l6] = 0.0;
	for (int l7 = 0; (l7 < 4); l7 = (l7 + 1)) fRec5[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fVec2[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec4[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fVec3[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec3[l11] = 0.0;
	for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) fRec2[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fVec4[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec11[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec1[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec0[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fVec5[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec21[l18] = 0.0;
	for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) fRec20[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fVec6[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec22[l21] = 0.0;
	for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) fRec19[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fRec18[l23] = 0.0;
	for (int l24 = 0; (l24 < 4); l24 = (l24 + 1)) fRec17[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fVec7[l25] = 0.0;
	for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) fRec16[l26] = 0.0;
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) fVec8[l27] = 0.0;
	for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) fRec15[l28] = 0.0;
	for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) fRec14[l29] = 0.0;
	for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) fVec9[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fRec23[l31] = 0.0;
	for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) fRec13[l32] = 0.0;
	for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) fRec12[l33] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = std::tan((97.389372261283583 / fConst0));
	fConst2 = (1.0 / fConst1);
	fConst3 = (fConst2 + 1.0);
	fConst4 = (1.0 / (fConst3 * fConst1));
	fConst5 = (41887.902047863907 / fConst0);
	fConst6 = (2.0 * fConst0);
	fConst7 = mydsp_faustpower2_f(fConst6);
	fConst8 = (1.0 / std::tan((6.5973445725385655 / fConst0)));
	fConst9 = (1.0 / (fConst8 + 1.0));
	fConst10 = (1.0 - fConst8);
	fConst11 = (0.0 - fConst4);
	fConst12 = ((1.0 - fConst2) / fConst3);
	fConst13 = (3.0 * fConst6);
	fVslider0 = FAUSTFLOAT(5.0);
	fCheckbox0 = FAUSTFLOAT(0.0);
	fVslider1 = FAUSTFLOAT(0.5);
	fVslider2 = FAUSTFLOAT(0.5);
	fVslider3 = FAUSTFLOAT(0.5);
	fVslider4 = FAUSTFLOAT(5.0);
	fCheckbox1 = FAUSTFLOAT(0.0);
	fVslider5 = FAUSTFLOAT(0.5);
	fVslider6 = FAUSTFLOAT(0.5);
	fVslider7 = FAUSTFLOAT(0.5);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fVslider0 (*fVslider0_)
#define fCheckbox0 (*fCheckbox0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
#define fVslider4 (*fVslider4_)
#define fCheckbox1 (*fCheckbox1_)
#define fVslider5 (*fVslider5_)
#define fVslider6 (*fVslider6_)
#define fVslider7 (*fVslider7_)
	double fSlow0 = double(fVslider0);
	double fSlow1 = std::tan((fConst5 / (fSlow0 + 1.0)));
	double fSlow2 = (1.0 / fSlow1);
	double fSlow3 = (fSlow2 + 1.0);
	double fSlow4 = (0.0 - (1.0 / (fSlow3 * fSlow1)));
	double fSlow5 = double(fCheckbox0);
	double fSlow6 = double(fVslider1);
	double fSlow7 = std::exp((3.3999999999999999 * (double(fVslider2) + -1.0)));
	double fSlow8 = ((0.00047000000000000004 * fSlow6) + (0.025062500000000001 * fSlow7));
	double fSlow9 = (fConst6 * (fSlow8 + 0.015765000000000001));
	double fSlow10 = (4.7117500000000004e-07 * fSlow6);
	double fSlow11 = ((((((1.1779375000000001e-05 * fSlow7) + -4.1994500000000009e-06) - fSlow10) * fSlow6) + (0.00011998125000000002 * fSlow7)) + 5.718000000000001e-06);
	double fSlow12 = ((1.0281250000000001e-09 * fSlow7) - (4.1125e-11 * fSlow6));
	double fSlow13 = (7.3437500000000008e-09 * fSlow7);
	double fSlow14 = ((((fSlow12 + -2.5262499999999999e-10) * fSlow6) + fSlow13) + 2.9374999999999999e-10);
	double fSlow15 = (fConst6 * fSlow14);
	double fSlow16 = (-1.0 - (fSlow9 + (fConst7 * (fSlow11 + fSlow15))));
	double fSlow17 = (fSlow5 / fSlow16);
	double fSlow18 = double(fVslider3);
	double fSlow19 = (fConst6 * ((fSlow8 + (6.2500000000000001e-05 * fSlow18)) + 0.0010024999999999999));
	double fSlow20 = (((9.187500000000001e-07 * fSlow18) + (((5.0055000000000002e-07 - fSlow10) * fSlow6) + (fSlow7 * ((1.1779375000000001e-05 * fSlow6) + 2.4812500000000002e-06)))) + 9.9250000000000005e-08);
	double fSlow21 = (((fSlow12 + 4.1125e-11) * fSlow6) + ((fSlow13 - (2.9374999999999999e-10 * (fSlow6 + -1.0))) * fSlow18));
	double fSlow22 = (fConst6 * fSlow21);
	double fSlow23 = (0.0 - (fSlow19 + (fConst7 * (fSlow20 + fSlow22))));
	double fSlow24 = (1.0 / fSlow16);
	double fSlow25 = (fConst13 * fSlow14);
	double fSlow26 = ((fConst7 * (fSlow11 + fSlow25)) + (-3.0 - fSlow9));
	double fSlow27 = ((fSlow9 + (fConst7 * (fSlow11 - fSlow25))) + -3.0);
	double fSlow28 = (fSlow9 + (-1.0 - (fConst7 * (fSlow11 - fSlow15))));
	double fSlow29 = (fConst13 * fSlow21);
	double fSlow30 = ((fConst7 * (fSlow20 + fSlow29)) - fSlow19);
	double fSlow31 = (fSlow19 + (fConst7 * (fSlow20 - fSlow29)));
	double fSlow32 = (fSlow19 - (fConst7 * (fSlow20 - fSlow22)));
	double fSlow33 = (1.0 / fSlow3);
	double fSlow34 = (1.0 - fSlow2);
	double fSlow35 = (fSlow5 / (fSlow16 * fSlow1));
	double fSlow36 = (0.10000000000000001 * (fSlow0 / fSlow16));
	double fSlow37 = double(fVslider4);
	double fSlow38 = std::tan((fConst5 / (fSlow37 + 1.0)));
	double fSlow39 = (1.0 / fSlow38);
	double fSlow40 = (fSlow39 + 1.0);
	double fSlow41 = (0.0 - (1.0 / (fSlow40 * fSlow38)));
	double fSlow42 = double(fCheckbox1);
	double fSlow43 = double(fVslider5);
	double fSlow44 = std::exp((3.3999999999999999 * (double(fVslider6) + -1.0)));
	double fSlow45 = ((0.00047000000000000004 * fSlow43) + (0.025062500000000001 * fSlow44));
	double fSlow46 = (fConst6 * (fSlow45 + 0.015765000000000001));
	double fSlow47 = (4.7117500000000004e-07 * fSlow43);
	double fSlow48 = ((((((1.1779375000000001e-05 * fSlow44) + -4.1994500000000009e-06) - fSlow47) * fSlow43) + (0.00011998125000000002 * fSlow44)) + 5.718000000000001e-06);
	double fSlow49 = ((1.0281250000000001e-09 * fSlow44) - (4.1125e-11 * fSlow43));
	double fSlow50 = (7.3437500000000008e-09 * fSlow44);
	double fSlow51 = ((((fSlow49 + -2.5262499999999999e-10) * fSlow43) + fSlow50) + 2.9374999999999999e-10);
	double fSlow52 = (fConst6 * fSlow51);
	double fSlow53 = (-1.0 - (fSlow46 + (fConst7 * (fSlow48 + fSlow52))));
	double fSlow54 = (fSlow42 / fSlow53);
	double fSlow55 = double(fVslider7);
	double fSlow56 = (fConst6 * ((fSlow45 + (6.2500000000000001e-05 * fSlow55)) + 0.0010024999999999999));
	double fSlow57 = (((9.187500000000001e-07 * fSlow55) + (((5.0055000000000002e-07 - fSlow47) * fSlow43) + (fSlow44 * ((1.1779375000000001e-05 * fSlow43) + 2.4812500000000002e-06)))) + 9.9250000000000005e-08);
	double fSlow58 = (((fSlow49 + 4.1125e-11) * fSlow43) + ((fSlow50 - (2.9374999999999999e-10 * (fSlow43 + -1.0))) * fSlow55));
	double fSlow59 = (fConst6 * fSlow58);
	double fSlow60 = (0.0 - (fSlow56 + (fConst7 * (fSlow57 + fSlow59))));
	double fSlow61 = (1.0 / fSlow53);
	double fSlow62 = (fConst13 * fSlow51);
	double fSlow63 = ((fConst7 * (fSlow48 + fSlow62)) + (-3.0 - fSlow46));
	double fSlow64 = ((fSlow46 + (fConst7 * (fSlow48 - fSlow62))) + -3.0);
	double fSlow65 = (fSlow46 + (-1.0 - (fConst7 * (fSlow48 - fSlow52))));
	double fSlow66 = (fConst13 * fSlow58);
	double fSlow67 = ((fConst7 * (fSlow57 + fSlow66)) - fSlow56);
	double fSlow68 = (fSlow56 + (fConst7 * (fSlow57 - fSlow66)));
	double fSlow69 = (fSlow56 - (fConst7 * (fSlow57 - fSlow59)));
	double fSlow70 = (1.0 / fSlow40);
	double fSlow71 = (1.0 - fSlow39);
	double fSlow72 = (fSlow42 / (fSlow53 * fSlow38));
	double fSlow73 = (0.10000000000000001 * (fSlow37 / fSlow53));
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = (double(input0[i]) + 1.0000000000000001e-15);
		fVec0[0] = fTemp0;
		fRec9[0] = ((0.93028479253239138 * (fVec0[1] + fTemp0)) - (0.86056958506478287 * fRec9[1]));
		fRec8[0] = (fRec9[0] - ((1.8405051250752198 * fRec8[1]) + (0.86129424393186271 * fRec8[2])));
		double fTemp1 = ((0.014999999999999999 * fRec7[1]) + 1.0000000000000001e-15);
		fVec1[0] = fTemp1;
		fRec10[0] = (0.0 - (fConst9 * ((fConst10 * fRec10[1]) - (fTemp1 + fVec1[1]))));
		fRec7[0] = (double(Ftube(int(TUBE_TABLE_12AX7_68k), double((((0.92544984225177063 * (fRec8[0] + fRec8[2])) + (fRec10[0] + (1.8508996845035413 * fRec8[1]))) + -1.2045410000000001)))) + -169.69726666666665);
		fRec6[0] = ((0.025000000000000001 * ((fConst4 * fRec7[0]) + (fConst11 * fRec7[1]))) - (fConst12 * fRec6[1]));
		fRec5[0] = ((10.0 * fRec6[0]) - (fSlow24 * (((fSlow26 * fRec5[1]) + (fSlow27 * fRec5[2])) + (fSlow28 * fRec5[3]))));
		double fTemp2 = ((((fSlow23 * fRec5[0]) + (fSlow30 * fRec5[1])) + (fSlow31 * fRec5[2])) + (fSlow32 * fRec5[3]));
		fVec2[0] = (fSlow17 * fTemp2);
		fRec4[0] = ((fSlow4 * fVec2[1]) - (fSlow33 * ((fSlow34 * fRec4[1]) - (fSlow35 * fTemp2))));
		double fTemp3 = ((fRec4[0] + (fSlow36 * fTemp2)) + 1.0000000000000001e-15);
		fVec3[0] = fTemp3;
		fRec3[0] = ((0.93028479253239138 * (fTemp3 + fVec3[1])) - (0.86056958506478287 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.86129424393186271 * fRec2[2])));
		double fTemp4 = ((0.014999999999999999 * fRec1[1]) + 1.0000000000000001e-15);
		fVec4[0] = fTemp4;
		fRec11[0] = (0.0 - (fConst9 * ((fConst10 * fRec11[1]) - (fTemp4 + fVec4[1]))));
		fRec1[0] = (double(Ftube(int(TUBE_TABLE_12AX7_250k), double((((0.92544984225177063 * (fRec2[0] + fRec2[2])) + (fRec11[0] + (1.8508996845035413 * fRec2[1]))) + -1.204285)))) + -169.71433333333334);
		fRec0[0] = ((0.025000000000000001 * ((fConst4 * fRec1[0]) + (fConst11 * fRec1[1]))) - (fConst12 * fRec0[1]));
		output0[i] = FAUSTFLOAT((0.33339999999999997 * fRec0[0]));
		double fTemp5 = (double(input1[i]) + 1.0000000000000001e-15);
		fVec5[0] = fTemp5;
		fRec21[0] = ((0.93028479253239138 * (fVec5[1] + fTemp5)) - (0.86056958506478287 * fRec21[1]));
		fRec20[0] = (fRec21[0] - ((1.8405051250752198 * fRec20[1]) + (0.86129424393186271 * fRec20[2])));
		double fTemp6 = ((0.014999999999999999 * fRec19[1]) + 1.0000000000000001e-15);
		fVec6[0] = fTemp6;
		fRec22[0] = (0.0 - (fConst9 * ((fConst10 * fRec22[1]) - (fTemp6 + fVec6[1]))));
		fRec19[0] = (double(Ftube(int(TUBE_TABLE_12AX7_68k), double((((0.92544984225177063 * (fRec20[0] + fRec20[2])) + (fRec22[0] + (1.8508996845035413 * fRec20[1]))) + -1.2045410000000001)))) + -169.69726666666665);
		fRec18[0] = ((0.025000000000000001 * ((fConst4 * fRec19[0]) + (fConst11 * fRec19[1]))) - (fConst12 * fRec18[1]));
		fRec17[0] = ((10.0 * fRec18[0]) - (fSlow61 * (((fSlow63 * fRec17[1]) + (fSlow64 * fRec17[2])) + (fSlow65 * fRec17[3]))));
		double fTemp7 = ((((fSlow60 * fRec17[0]) + (fSlow67 * fRec17[1])) + (fSlow68 * fRec17[2])) + (fSlow69 * fRec17[3]));
		fVec7[0] = (fSlow54 * fTemp7);
		fRec16[0] = ((fSlow41 * fVec7[1]) - (fSlow70 * ((fSlow71 * fRec16[1]) - (fSlow72 * fTemp7))));
		double fTemp8 = ((fRec16[0] + (fSlow73 * fTemp7)) + 1.0000000000000001e-15);
		fVec8[0] = fTemp8;
		fRec15[0] = ((0.93028479253239138 * (fTemp8 + fVec8[1])) - (0.86056958506478287 * fRec15[1]));
		fRec14[0] = (fRec15[0] - ((1.8405051250752198 * fRec14[1]) + (0.86129424393186271 * fRec14[2])));
		double fTemp9 = ((0.014999999999999999 * fRec13[1]) + 1.0000000000000001e-15);
		fVec9[0] = fTemp9;
		fRec23[0] = (0.0 - (fConst9 * ((fConst10 * fRec23[1]) - (fTemp9 + fVec9[1]))));
		fRec13[0] = (double(Ftube(int(TUBE_TABLE_12AX7_250k), double((((0.92544984225177063 * (fRec14[0] + fRec14[2])) + (fRec23[0] + (1.8508996845035413 * fRec14[1]))) + -1.204285)))) + -169.71433333333334);
		fRec12[0] = ((0.025000000000000001 * ((fConst4 * fRec13[0]) + (fConst11 * fRec13[1]))) - (fConst12 * fRec12[1]));
		output1[i] = FAUSTFLOAT((0.33339999999999997 * fRec12[0]));
		fVec0[1] = fVec0[0];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fVec1[1] = fVec1[0];
		fRec10[1] = fRec10[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
			fRec5[j0] = fRec5[(j0 - 1)];
		}
		fVec2[1] = fVec2[0];
		fRec4[1] = fRec4[0];
		fVec3[1] = fVec3[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fVec4[1] = fVec4[0];
		fRec11[1] = fRec11[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fVec5[1] = fVec5[0];
		fRec21[1] = fRec21[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fVec6[1] = fVec6[0];
		fRec22[1] = fRec22[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
			fRec17[j1] = fRec17[(j1 - 1)];
		}
		fVec7[1] = fVec7[0];
		fRec16[1] = fRec16[0];
		fVec8[1] = fVec8[0];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fVec9[1] = fVec9[0];
		fRec23[1] = fRec23[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
	}
#undef fVslider0
#undef fCheckbox0
#undef fVslider1
#undef fVslider2
#undef fVslider3
#undef fVslider4
#undef fCheckbox1
#undef fVslider5
#undef fVslider6
#undef fVslider7
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case BASS_L: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case BASS_R: 
		fVslider6_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case MIDDLE_L: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case MIDDLE_R: 
		fVslider5_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TREBLE_L: 
		fVslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TREBLE_R: 
		fVslider7_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME_L: 
		fVslider0_ = (float*)data; // , 5.0, 0.0, 10.0, 0.10000000000000001 
		break;
	case VOLUME_R: 
		fVslider4_ = (float*)data; // , 5.0, 0.0, 10.0, 0.10000000000000001 
		break;
	case BRIGHT_L: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case BRIGHT_R: 
		fCheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
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
   BASS_L, 
   BASS_R, 
   MIDDLE_L, 
   MIDDLE_R, 
   TREBLE_L, 
   TREBLE_R, 
   VOLUME_L, 
   VOLUME_R, 
   BRIGHT_L, 
   BRIGHT_R, 
} PortIndex;
*/

} // end namespace gx_studiopre_st
