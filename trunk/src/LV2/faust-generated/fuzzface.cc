// generated from file '../src/LV2/faust/fuzzface.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#include "trany.h"

namespace fuzzface {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec13[2];
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
	double fRec12[6];
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec14[2];
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
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst63;
	double fConst64;
	double fConst65;
	double fConst66;
	double fVec0[2];
	double fRec11[2];
	double fRec10[3];
	double fConst67;
	double fConst68;
	double fConst69;
	double fRec15[2];
	double fRec9[3];
	double fConst70;
	double fConst71;
	double fRec8[2];
	double fRec7[2];
	double fRec6[3];
	double fRec16[2];
	double fRec5[3];
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fRec17[2];
	double fRec1[3];
	double fRec0[2];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
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
	id = "fuzzface";
	name = N_("Fuzz Face");
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec13[l0] = 0.0;
	for (int l1 = 0; (l1 < 6); l1 = (l1 + 1)) fRec12[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec14[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fVec0[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec11[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec10[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec15[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRec9[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec8[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec7[l9] = 0.0;
	for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) fRec6[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec16[l11] = 0.0;
	for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) fRec5[l12] = 0.0;
	for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) fRec4[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec3[l14] = 0.0;
	for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) fRec2[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec17[l16] = 0.0;
	for (int l17 = 0; (l17 < 3); l17 = (l17 + 1)) fRec1[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec0[l18] = 0.0;
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
	fConst5 = (0.93028479253239138 * mydsp_faustpower2_f(fConst0));
	fConst6 = (1.1969573227426499e-21 * fConst0);
	fConst7 = (((((-1.9904265351089599e-15 - fConst6) * fConst0) + 1.8361560410497099e-13) * fConst0) + 1.59369187419145e-10);
	fConst8 = (1.86646037645036e-28 * fConst0);
	fConst9 = (((((((-3.0492983317998401e-20 - fConst8) * fConst0) + -2.91602352831988e-14) * fConst0) + 2.2963696637004201e-11) * fConst0) + 3.2234731636248798e-09);
	fConst10 = (((((((fConst8 + 3.1689940386223803e-20) * fConst0) + 3.1150636903991498e-14) * fConst0) + -2.30719916990074e-11) * fConst0) + -3.22479494130986e-09);
	fConst11 = (7.97971548495099e-22 * fConst0);
	fConst12 = (((((fConst11 + -3.9808530702179302e-15) * fConst0) + -3.6723120820994199e-13) * fConst0) + 1.06246124946097e-10);
	fConst13 = (3.7329207529007299e-28 * fConst0);
	fConst14 = (((((((fConst13 + 2.0328655545332299e-20) * fConst0) + -5.83204705663976e-14) * fConst0) + -4.5927393274008403e-11) * fConst0) + 2.14898210908325e-09);
	fConst15 = (((((((-2.1126626924149201e-20 - fConst13) * fConst0) + 6.2301273807982996e-14) * fConst0) + 4.6143983398014799e-11) * fConst0) + -2.1498632942065702e-09);
	fConst16 = (((((fConst11 + 3.9808530702179302e-15) * fConst0) + -3.6723120820994199e-13) * fConst0) + -1.06246124946097e-10);
	fConst17 = (((((((2.0328655545332299e-20 - fConst13) * fConst0) + 5.83204705663976e-14) * fConst0) + -4.5927393274008403e-11) * fConst0) + -2.14898210908325e-09);
	fConst18 = (((((((fConst13 + -2.1126626924149201e-20) * fConst0) + -6.2301273807982996e-14) * fConst0) + 4.6143983398014799e-11) * fConst0) + 2.1498632942065702e-09);
	fConst19 = (((((1.9904265351089599e-15 - fConst6) * fConst0) + 1.8361560410497099e-13) * fConst0) + -1.59369187419145e-10);
	fConst20 = (((((((fConst8 + -3.0492983317998401e-20) * fConst0) + 2.91602352831988e-14) * fConst0) + 2.2963696637004201e-11) * fConst0) + -3.2234731636248798e-09);
	fConst21 = (((((((3.1689940386223803e-20 - fConst8) * fConst0) + -3.1150636903991498e-14) * fConst0) + -2.30719916990074e-11) * fConst0) + 3.22479494130986e-09);
	fConst22 = (3.9898577424754898e-22 * fConst0);
	fConst23 = (((((fConst22 + -1.9904265351089599e-15) * fConst0) + 1.8361560410497099e-13) * fConst0) + -5.3123062473048297e-11);
	fConst24 = (3.7329207529007301e-29 * fConst0);
	fConst25 = (((((((1.0164327772666201e-20 - fConst24) * fConst0) + -2.91602352831988e-14) * fConst0) + 2.2963696637004201e-11) * fConst0) + -1.07449105454163e-09);
	fConst26 = (((((((fConst24 + -1.05633134620746e-20) * fConst0) + 3.1150636903991498e-14) * fConst0) + -2.30719916990074e-11) * fConst0) + 1.07493164710329e-09);
	fConst27 = (((((fConst22 + 1.9904265351089599e-15) * fConst0) + 1.8361560410497099e-13) * fConst0) + 5.3123062473048297e-11);
	fConst28 = (((((((fConst24 + 1.0164327772666201e-20) * fConst0) + 2.91602352831988e-14) * fConst0) + 2.2963696637004201e-11) * fConst0) + 1.07449105454163e-09);
	fConst29 = (((((((-1.05633134620746e-20 - fConst24) * fConst0) + -3.1150636903991498e-14) * fConst0) + -2.30719916990074e-11) * fConst0) + -1.07493164710329e-09);
	fConst30 = (5.0573033918522197e-13 * fConst0);
	fConst31 = (fConst30 + 1.1616221542226101e-12);
	fConst32 = (4.7699151349934602e-20 * fConst0);
	fConst33 = (fConst32 + -5.0034671369817102e-13);
	fConst34 = (-5.3835170798891596e-15 - fConst32);
	fConst35 = (fConst32 + 5.3835170798891596e-15);
	fConst36 = (5.0034671369817102e-13 - fConst32);
	fConst37 = (-1.1616221542226101e-12 - fConst30);
	fConst38 = (1.1616221542226101e-12 - fConst30);
	fConst39 = (1.4309745404980399e-19 * fConst0);
	fConst40 = (5.0034671369817102e-13 - fConst39);
	fConst41 = (fConst39 + 5.3835170798891596e-15);
	fConst42 = (-5.3835170798891596e-15 - fConst39);
	fConst43 = (fConst39 + -5.0034671369817102e-13);
	fConst44 = (fConst30 + -1.1616221542226101e-12);
	fConst45 = (1.0114606783704401e-12 * fConst0);
	fConst46 = (-2.3232443084452202e-12 - fConst45);
	fConst47 = (9.5398302699869301e-20 * fConst0);
	fConst48 = (fConst47 + 1.00069342739634e-12);
	fConst49 = (1.07670341597783e-14 - fConst47);
	fConst50 = (fConst47 + -1.07670341597783e-14);
	fConst51 = (-1.00069342739634e-12 - fConst47);
	fConst52 = (fConst45 + 2.3232443084452202e-12);
	fConst53 = (fConst45 + -2.3232443084452202e-12);
	fConst54 = (fConst47 + -1.00069342739634e-12);
	fConst55 = (-1.07670341597783e-14 - fConst47);
	fConst56 = (fConst47 + 1.07670341597783e-14);
	fConst57 = (1.00069342739634e-12 - fConst47);
	fConst58 = (2.3232443084452202e-12 - fConst45);
	fConst59 = (-5.0034671369817102e-13 - fConst39);
	fConst60 = (fConst39 + -5.3835170798891596e-15);
	fConst61 = (5.3835170798891596e-15 - fConst39);
	fConst62 = (fConst39 + 5.0034671369817102e-13);
	fConst63 = (fConst32 + 5.0034671369817102e-13);
	fConst64 = (5.3835170798891596e-15 - fConst32);
	fConst65 = (fConst32 + -5.3835170798891596e-15);
	fConst66 = (-5.0034671369817102e-13 - fConst32);
	fConst67 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst68 = (1.0 / (fConst67 + 1.0));
	fConst69 = (1.0 - fConst67);
	fConst70 = (0.0 - fConst4);
	fConst71 = ((1.0 - fConst2) / fConst3);
	fVslider0 = FAUSTFLOAT(0.5);
	fVslider1 = FAUSTFLOAT(0.5);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
	double fSlow0 = (0.0070000000000000062 * (1.0 - double(fVslider0)));
	double fSlow1 = (0.0070000000000000062 * (1.0 - double(fVslider1)));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec13[0] = (fSlow0 + (0.99299999999999999 * fRec13[1]));
		double fTemp0 = ((fConst0 * (fConst27 + (fRec13[0] * (fConst28 + (fConst29 * fRec13[0]))))) + 2.4440278174203298e-09);
		fRec12[0] = (double(input0[i]) - ((((((fRec12[1] * ((fConst0 * (fConst7 + (fRec13[0] * (fConst9 + (fConst10 * fRec13[0]))))) + 1.2220139087101701e-08)) + (fRec12[2] * ((fConst0 * (fConst12 + (fRec13[0] * (fConst14 + (fConst15 * fRec13[0]))))) + 2.4440278174203299e-08))) + (fRec12[3] * ((fConst0 * (fConst16 + (fRec13[0] * (fConst17 + (fConst18 * fRec13[0]))))) + 2.4440278174203299e-08))) + (fRec12[4] * ((fConst0 * (fConst19 + (fRec13[0] * (fConst20 + (fConst21 * fRec13[0]))))) + 1.2220139087101701e-08))) + (fRec12[5] * ((fConst0 * (fConst23 + (fRec13[0] * (fConst25 + (fConst26 * fRec13[0]))))) + 2.4440278174203298e-09))) / fTemp0));
		fRec14[0] = (fSlow1 + (0.99299999999999999 * fRec14[1]));
		double fTemp1 = (fConst37 * fRec14[0]);
		double fTemp2 = (fConst44 * fRec14[0]);
		double fTemp3 = (((((((fRec12[0] * (fConst31 + ((fConst0 * (fRec13[0] * (fConst33 + ((fRec13[0] * (fConst34 + (fConst35 * fRec14[0]))) + (fConst36 * fRec14[0]))))) + fTemp1))) + (fRec12[1] * (fConst38 + ((fConst0 * (fRec13[0] * (fConst40 + ((fRec13[0] * (fConst41 + (fConst42 * fRec14[0]))) + (fConst43 * fRec14[0]))))) + fTemp2)))) + (fRec12[2] * (fConst46 + ((fConst0 * (fRec13[0] * (fConst48 + ((fRec13[0] * (fConst49 + (fConst50 * fRec14[0]))) + (fConst51 * fRec14[0]))))) + (fConst52 * fRec14[0]))))) + (fRec12[3] * (fConst53 + ((fConst0 * (fRec13[0] * (fConst54 + ((fRec13[0] * (fConst55 + (fConst56 * fRec14[0]))) + (fConst57 * fRec14[0]))))) + (fConst58 * fRec14[0]))))) + (fRec12[4] * (fConst31 + (fTemp1 + (fConst0 * (fRec13[0] * (fConst59 + ((fRec13[0] * (fConst60 + (fConst61 * fRec14[0]))) + (fConst62 * fRec14[0]))))))))) + (fRec12[5] * (fConst38 + (fTemp2 + (fConst0 * (fRec13[0] * (fConst63 + ((fRec13[0] * (fConst64 + (fConst65 * fRec14[0]))) + (fConst66 * fRec14[0]))))))))) / fTemp0);
		fVec0[0] = fTemp3;
		fRec11[0] = ((fConst5 * (fTemp3 + fVec0[1])) - (0.86056958506478287 * fRec11[1]));
		fRec10[0] = (fRec11[0] - ((1.8405051250752198 * fRec10[1]) + (0.86129424393186271 * fRec10[2])));
		fRec15[0] = (fConst68 * ((0.027 * (fRec9[1] + fRec9[2])) - (fConst69 * fRec15[1])));
		fRec9[0] = (double(Ftrany(int(TRANY_TABLE_7199P_68k), double((((0.92544984225177063 * (fRec10[0] + fRec10[2])) + (fRec15[0] + (1.8508996845035413 * fRec10[1]))) + -3.5719810000000001)))) + -117.70440740740739);
		fRec8[0] = ((0.025000000000000001 * ((fConst4 * fRec9[0]) + (fConst70 * fRec9[1]))) - (fConst71 * fRec8[1]));
		fRec7[0] = ((0.93028479253239138 * (fRec8[0] + fRec8[1])) - (0.86056958506478287 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.86129424393186271 * fRec6[2])));
		fRec16[0] = (fConst68 * ((0.027 * (fRec5[1] + fRec5[2])) - (fConst69 * fRec16[1])));
		fRec5[0] = (double(Ftrany(int(TRANY_TABLE_7199P_68k), double((((0.92544984225177063 * (fRec6[0] + fRec6[2])) + (fRec16[0] + (1.8508996845035413 * fRec6[1]))) + -3.5719810000000001)))) + -117.70440740740739);
		fRec4[0] = ((0.025000000000000001 * ((fConst4 * fRec5[0]) + (fConst70 * fRec5[1]))) - (fConst71 * fRec4[1]));
		fRec3[0] = ((0.93028479253239138 * (fRec4[0] + fRec4[1])) - (0.86056958506478287 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.86129424393186271 * fRec2[2])));
		fRec17[0] = (fConst68 * ((0.027 * (fRec1[1] + fRec1[2])) - (fConst69 * fRec17[1])));
		fRec1[0] = (double(Ftrany(int(TRANY_TABLE_7199P_68k), double((((0.92544984225177063 * (fRec2[0] + fRec2[2])) + (fRec17[0] + (1.8508996845035413 * fRec2[1]))) + -3.5719810000000001)))) + -117.70440740740739);
		fRec0[0] = ((0.025000000000000001 * ((fConst4 * fRec1[0]) + (fConst70 * fRec1[1]))) - (fConst71 * fRec0[1]));
		output0[i] = FAUSTFLOAT(fRec0[0]);
		fRec13[1] = fRec13[0];
		for (int j0 = 5; (j0 > 0); j0 = (j0 - 1)) {
			fRec12[j0] = fRec12[(j0 - 1)];
		}
		fRec14[1] = fRec14[0];
		fVec0[1] = fVec0[0];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec15[1] = fRec15[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec16[1] = fRec16[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec17[1] = fRec17[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
#undef fVslider0
#undef fVslider1
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case FUZZ: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case LEVEL: 
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
   FUZZ, 
   LEVEL, 
} PortIndex;
*/

} // end namespace fuzzface
