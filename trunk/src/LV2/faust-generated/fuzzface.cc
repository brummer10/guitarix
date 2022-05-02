// generated from file '../src/LV2/faust/fuzzface.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "trany.h"

namespace fuzzface {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst6;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec13[2];
	double fConst8;
	double fConst9;
	double fConst11;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst22;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fRec12[6];
	double fConst30;
	double fConst32;
	double fConst33;
	double fConst34;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec14[2];
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst45;
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
	double fVec0[2];
	double fRec11[2];
	double fRec10[3];
	double fRec9[2];
	double fRec8[2];
	double fRec7[2];
	double fRec6[3];
	double fRec5[2];
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fRec1[2];
	double fRec0[2];

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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec13[l0] = 0.0;
	for (int l1 = 0; l1 < 6; l1 = l1 + 1) fRec12[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec14[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fVec0[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec11[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec10[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec9[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec8[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec7[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec6[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec5[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec4[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec3[l12] = 0.0;
	for (int l13 = 0; l13 < 3; l13 = l13 + 1) fRec2[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec1[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec0[l15] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 3.1415926535897931 / fConst0;
	fConst2 = 1.0 / (fConst1 + 1.0);
	fConst3 = 1.0 - fConst1;
	fConst4 = 0.93028479253239138 * mydsp_faustpower2_f(fConst0);
	double fConst5 = 1.1969573227426499e-21 * fConst0;
	fConst6 = fConst0 * (fConst0 * (-1.9904265351089599e-15 - fConst5) + 1.8361560410497099e-13) + 1.59369187419145e-10;
	double fConst7 = 1.86646037645036e-28 * fConst0;
	fConst8 = fConst0 * (fConst0 * (fConst0 * (-3.0492983317998401e-20 - fConst7) + -2.91602352831988e-14) + 2.2963696637004201e-11) + 3.2234731636248798e-09;
	fConst9 = fConst0 * (fConst0 * (fConst0 * (fConst7 + 3.1689940386223803e-20) + 3.1150636903991498e-14) + -2.30719916990074e-11) + -3.22479494130986e-09;
	double fConst10 = 7.97971548495099e-22 * fConst0;
	fConst11 = fConst0 * (fConst0 * (fConst10 + -3.9808530702179302e-15) + -3.6723120820994199e-13) + 1.06246124946097e-10;
	double fConst12 = 3.7329207529007299e-28 * fConst0;
	fConst13 = fConst0 * (fConst0 * (fConst0 * (fConst12 + 2.0328655545332299e-20) + -5.83204705663976e-14) + -4.5927393274008403e-11) + 2.14898210908325e-09;
	fConst14 = fConst0 * (fConst0 * (fConst0 * (-2.1126626924149201e-20 - fConst12) + 6.2301273807982996e-14) + 4.6143983398014799e-11) + -2.1498632942065702e-09;
	fConst15 = fConst0 * (fConst0 * (fConst10 + 3.9808530702179302e-15) + -3.6723120820994199e-13) + -1.06246124946097e-10;
	fConst16 = fConst0 * (fConst0 * (fConst0 * (2.0328655545332299e-20 - fConst12) + 5.83204705663976e-14) + -4.5927393274008403e-11) + -2.14898210908325e-09;
	fConst17 = fConst0 * (fConst0 * (fConst0 * (fConst12 + -2.1126626924149201e-20) + -6.2301273807982996e-14) + 4.6143983398014799e-11) + 2.1498632942065702e-09;
	fConst18 = fConst0 * (fConst0 * (1.9904265351089599e-15 - fConst5) + 1.8361560410497099e-13) + -1.59369187419145e-10;
	fConst19 = fConst0 * (fConst0 * (fConst0 * (fConst7 + -3.0492983317998401e-20) + 2.91602352831988e-14) + 2.2963696637004201e-11) + -3.2234731636248798e-09;
	fConst20 = fConst0 * (fConst0 * (fConst0 * (3.1689940386223803e-20 - fConst7) + -3.1150636903991498e-14) + -2.30719916990074e-11) + 3.22479494130986e-09;
	double fConst21 = 3.9898577424754898e-22 * fConst0;
	fConst22 = fConst0 * (fConst0 * (fConst21 + -1.9904265351089599e-15) + 1.8361560410497099e-13) + -5.3123062473048297e-11;
	double fConst23 = 3.7329207529007301e-29 * fConst0;
	fConst24 = fConst0 * (fConst0 * (fConst0 * (1.0164327772666201e-20 - fConst23) + -2.91602352831988e-14) + 2.2963696637004201e-11) + -1.07449105454163e-09;
	fConst25 = fConst0 * (fConst0 * (fConst0 * (fConst23 + -1.05633134620746e-20) + 3.1150636903991498e-14) + -2.30719916990074e-11) + 1.07493164710329e-09;
	fConst26 = fConst0 * (fConst0 * (fConst21 + 1.9904265351089599e-15) + 1.8361560410497099e-13) + 5.3123062473048297e-11;
	fConst27 = fConst0 * (fConst0 * (fConst0 * (fConst23 + 1.0164327772666201e-20) + 2.91602352831988e-14) + 2.2963696637004201e-11) + 1.07449105454163e-09;
	fConst28 = fConst0 * (fConst0 * (fConst0 * (-1.05633134620746e-20 - fConst23) + -3.1150636903991498e-14) + -2.30719916990074e-11) + -1.07493164710329e-09;
	double fConst29 = 5.0573033918522197e-13 * fConst0;
	fConst30 = fConst29 + 1.1616221542226101e-12;
	double fConst31 = 4.7699151349934602e-20 * fConst0;
	fConst32 = fConst31 + -5.0034671369817102e-13;
	fConst33 = -5.3835170798891596e-15 - fConst31;
	fConst34 = fConst31 + 5.3835170798891596e-15;
	fConst35 = 5.0034671369817102e-13 - fConst31;
	fConst36 = -1.1616221542226101e-12 - fConst29;
	fConst37 = 1.1616221542226101e-12 - fConst29;
	double fConst38 = 1.4309745404980399e-19 * fConst0;
	fConst39 = 5.0034671369817102e-13 - fConst38;
	fConst40 = fConst38 + 5.3835170798891596e-15;
	fConst41 = -5.3835170798891596e-15 - fConst38;
	fConst42 = fConst38 + -5.0034671369817102e-13;
	fConst43 = fConst29 + -1.1616221542226101e-12;
	double fConst44 = 1.0114606783704401e-12 * fConst0;
	fConst45 = -2.3232443084452202e-12 - fConst44;
	double fConst46 = 9.5398302699869301e-20 * fConst0;
	fConst47 = fConst46 + 1.00069342739634e-12;
	fConst48 = 1.07670341597783e-14 - fConst46;
	fConst49 = fConst46 + -1.07670341597783e-14;
	fConst50 = -1.00069342739634e-12 - fConst46;
	fConst51 = fConst44 + 2.3232443084452202e-12;
	fConst52 = fConst44 + -2.3232443084452202e-12;
	fConst53 = fConst46 + -1.00069342739634e-12;
	fConst54 = -1.07670341597783e-14 - fConst46;
	fConst55 = fConst46 + 1.07670341597783e-14;
	fConst56 = 1.00069342739634e-12 - fConst46;
	fConst57 = 2.3232443084452202e-12 - fConst44;
	fConst58 = -5.0034671369817102e-13 - fConst38;
	fConst59 = fConst38 + -5.3835170798891596e-15;
	fConst60 = 5.3835170798891596e-15 - fConst38;
	fConst61 = fConst38 + 5.0034671369817102e-13;
	fConst62 = fConst31 + 5.0034671369817102e-13;
	fConst63 = 5.3835170798891596e-15 - fConst31;
	fConst64 = fConst31 + -5.3835170798891596e-15;
	fConst65 = -5.0034671369817102e-13 - fConst31;
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
	double fSlow0 = 0.0070000000000000062 * (1.0 - double(fVslider0));
	double fSlow1 = 0.0070000000000000062 * (1.0 - double(fVslider1));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec13[0] = fSlow0 + 0.99299999999999999 * fRec13[1];
		double fTemp0 = fConst0 * (fConst26 + fRec13[0] * (fConst27 + fConst28 * fRec13[0])) + 2.4440278174203298e-09;
		fRec12[0] = double(input0[i0]) - (fRec12[1] * (fConst0 * (fConst6 + fRec13[0] * (fConst8 + fConst9 * fRec13[0])) + 1.2220139087101701e-08) + fRec12[2] * (fConst0 * (fConst11 + fRec13[0] * (fConst13 + fConst14 * fRec13[0])) + 2.4440278174203299e-08) + fRec12[3] * (fConst0 * (fConst15 + fRec13[0] * (fConst16 + fConst17 * fRec13[0])) + 2.4440278174203299e-08) + fRec12[4] * (fConst0 * (fConst18 + fRec13[0] * (fConst19 + fConst20 * fRec13[0])) + 1.2220139087101701e-08) + fRec12[5] * (fConst0 * (fConst22 + fRec13[0] * (fConst24 + fConst25 * fRec13[0])) + 2.4440278174203298e-09)) / fTemp0;
		fRec14[0] = fSlow1 + 0.99299999999999999 * fRec14[1];
		double fTemp1 = fConst36 * fRec14[0];
		double fTemp2 = fConst43 * fRec14[0];
		double fTemp3 = (fRec12[0] * (fConst30 + fConst0 * fRec13[0] * (fConst32 + fRec13[0] * (fConst33 + fConst34 * fRec14[0]) + fConst35 * fRec14[0]) + fTemp1) + fRec12[1] * (fConst37 + fConst0 * fRec13[0] * (fConst39 + fRec13[0] * (fConst40 + fConst41 * fRec14[0]) + fConst42 * fRec14[0]) + fTemp2) + fRec12[2] * (fConst45 + fConst0 * fRec13[0] * (fConst47 + fRec13[0] * (fConst48 + fConst49 * fRec14[0]) + fConst50 * fRec14[0]) + fConst51 * fRec14[0]) + fRec12[3] * (fConst52 + fConst0 * fRec13[0] * (fConst53 + fRec13[0] * (fConst54 + fConst55 * fRec14[0]) + fConst56 * fRec14[0]) + fConst57 * fRec14[0]) + fRec12[4] * (fConst30 + fTemp1 + fConst0 * fRec13[0] * (fConst58 + fRec13[0] * (fConst59 + fConst60 * fRec14[0]) + fConst61 * fRec14[0])) + fRec12[5] * (fConst37 + fTemp2 + fConst0 * fRec13[0] * (fConst62 + fRec13[0] * (fConst63 + fConst64 * fRec14[0]) + fConst65 * fRec14[0]))) / fTemp0;
		fVec0[0] = fTemp3;
		fRec11[0] = fConst4 * (fTemp3 + fVec0[1]) - 0.86056958506478287 * fRec11[1];
		fRec10[0] = fRec11[0] - (1.8405051250752198 * fRec10[1] + 0.86129424393186271 * fRec10[2]);
		double fTemp4 = 1.8508996845035413 * fRec10[1] + 0.92544984225177063 * (fRec10[0] + fRec10[2]);
		double fTemp5 = double(Ftrany(int(TRANY_TABLE_7199P_68k), double(fTemp4 + 2700.0 * fTemp4 / (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fRec9[1]))) + 100000.0) + -3.5719810000000001)));
		fRec9[0] = fTemp5 + 0.001322955925925926 * (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fTemp5))) + 100000.0) + -250.0;
		fRec8[0] = fConst2 * (fConst3 * fRec8[1] + 0.025000000000000001 * (fRec9[0] - fRec9[1]));
		fRec7[0] = 0.93028479253239138 * (fRec8[0] + fRec8[1]) - 0.86056958506478287 * fRec7[1];
		fRec6[0] = fRec7[0] - (1.8405051250752198 * fRec6[1] + 0.86129424393186271 * fRec6[2]);
		double fTemp6 = 1.8508996845035413 * fRec6[1] + 0.92544984225177063 * (fRec6[0] + fRec6[2]);
		double fTemp7 = double(Ftrany(int(TRANY_TABLE_7199P_68k), double(fTemp6 + 2700.0 * fTemp6 / (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fRec5[1]))) + 100000.0) + -3.5719810000000001)));
		fRec5[0] = fTemp7 + 0.001322955925925926 * (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fTemp7))) + 100000.0) + -250.0;
		fRec4[0] = fConst2 * (fConst3 * fRec4[1] + 0.025000000000000001 * (fRec5[0] - fRec5[1]));
		fRec3[0] = 0.93028479253239138 * (fRec4[0] + fRec4[1]) - 0.86056958506478287 * fRec3[1];
		fRec2[0] = fRec3[0] - (1.8405051250752198 * fRec2[1] + 0.86129424393186271 * fRec2[2]);
		double fTemp8 = 1.8508996845035413 * fRec2[1] + 0.92544984225177063 * (fRec2[0] + fRec2[2]);
		double fTemp9 = double(Ftrany(int(TRANY_TABLE_7199P_68k), double(fTemp8 + 2700.0 * fTemp8 / (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fRec1[1]))) + 100000.0) + -3.5719810000000001)));
		fRec1[0] = fTemp9 + 0.001322955925925926 * (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fTemp9))) + 100000.0) + -250.0;
		fRec0[0] = fConst2 * (fConst3 * fRec0[1] + 0.025000000000000001 * (fRec1[0] - fRec1[1]));
		output0[i0] = FAUSTFLOAT(fRec0[0]);
		fRec13[1] = fRec13[0];
		for (int j0 = 5; j0 > 0; j0 = j0 - 1) {
			fRec12[j0] = fRec12[j0 - 1];
		}
		fRec14[1] = fRec14[0];
		fVec0[1] = fVec0[0];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
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
