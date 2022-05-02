// generated from file '../src/LV2/faust/cstb.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "trany.h"

namespace cstb {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst2;
	double fConst3;
	double fConst4;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec9[2];
	double fConst5;
	double fConst7;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec10[2];
	double fConst9;
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst18;
	double fConst20;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fRec8[5];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec11[2];
	double fVec0[2];
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
	id = "cstb";
	name = N_("Colorsound Tone Blender");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec9[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec10[l1] = 0.0;
	for (int l2 = 0; l2 < 5; l2 = l2 + 1) fRec8[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec11[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fVec0[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec7[l5] = 0.0;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec6[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec5[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec4[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec3[l9] = 0.0;
	for (int l10 = 0; l10 < 3; l10 = l10 + 1) fRec2[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec1[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec0[l12] = 0.0;
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
	fConst4 = 0.93028479253239138 * mydsp_faustpower3_f(fConst0);
	fConst5 = mydsp_faustpower2_f(fConst0);
	double fConst6 = 1.5455220088722401e-16 * fConst5;
	fConst7 = 3.8024832860176197e-12 - fConst6;
	double fConst8 = 2.9055813766798102e-18 * fConst0;
	fConst9 = fConst5 * (-7.6526860195686105e-16 - fConst8) + 7.1691572085722804e-14;
	double fConst10 = 2.8551532306795701e-18 * fConst0;
	fConst11 = fConst5 * (fConst10 + 7.6254875056230998e-16) + -7.1544112485537395e-14;
	fConst12 = 4.3583720650197197e-18 * fConst5 + -3.5743342888565602e-14;
	fConst13 = 3.5667519287136698e-14 - 4.2827298460193598e-18 * fConst5;
	fConst14 = fConst6 + -3.8024832860176197e-12;
	fConst15 = fConst5 * (7.6526860195686105e-16 - fConst8) + -7.1691572085722804e-14;
	fConst16 = fConst5 * (fConst10 + -7.6254875056230998e-16) + 7.1544112485537395e-14;
	double fConst17 = 7.7276100443612104e-17 * fConst0;
	fConst18 = fConst0 * (4.0705776699832999e-14 - fConst17) + -1.9012416430088098e-12;
	double fConst19 = 7.2639534416995302e-19 * fConst0;
	fConst20 = fConst0 * (fConst0 * (fConst19 + -3.8263430097843102e-16) + 1.7871671444282801e-14) + -3.5845786042861402e-14;
	double fConst21 = 7.1378830766989301e-19 * fConst0;
	fConst22 = fConst0 * (fConst0 * (3.8127437528115499e-16 - fConst21) + -1.7833759643568298e-14) + 3.5772056242768697e-14;
	fConst23 = fConst0 * (fConst17 + 4.0705776699832999e-14) + 1.9012416430088098e-12;
	fConst24 = fConst0 * (fConst0 * (fConst19 + 3.8263430097843102e-16) + 1.7871671444282801e-14) + 3.5845786042861402e-14;
	fConst25 = fConst0 * (fConst0 * (-3.8127437528115499e-16 - fConst21) + -1.7833759643568298e-14) + -3.5772056242768697e-14;
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
	double fSlow0 = 7.0000000000000062e-05 * double(fVslider0);
	double fSlow1 = 0.0070000000000000062 * double(fVslider1);
	double fSlow2 = 0.0070000000000000062 * double(fVslider2);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		fRec9[0] = fSlow0 + 0.99299999999999999 * fRec9[1];
		fRec10[0] = fSlow1 + 0.99299999999999999 * fRec10[1];
		double fTemp1 = fConst0 * (fConst23 + fRec10[0] * (fConst24 + fConst25 * fRec10[0])) + 3.8133814939214299e-12;
		fRec8[0] = fTemp0 * fRec9[0] - (fRec8[1] * (fConst0 * (fConst7 + fRec10[0] * (fConst9 + fConst11 * fRec10[0])) + 1.52535259756857e-11) + fRec8[2] * (fConst5 * (fRec10[0] * (fConst12 + fConst13 * fRec10[0]) + -8.1411553399666099e-14) + 2.28802889635286e-11) + fRec8[3] * (fConst0 * (fConst14 + fRec10[0] * (fConst15 + fConst16 * fRec10[0])) + 1.52535259756857e-11) + fRec8[4] * (fConst0 * (fConst18 + fRec10[0] * (fConst20 + fConst22 * fRec10[0])) + 3.8133814939214299e-12)) / fTemp1;
		fRec11[0] = fSlow2 + 0.99299999999999999 * fRec11[1];
		double fTemp2 = fConst0 * fRec10[0] * (fRec10[0] * (2.3467795460067299e-19 * fRec11[0] + 2.3467795460067301e-22) - 2.35728909376724e-17 * fRec11[0] + -2.3572890937672401e-20);
		double fTemp3 = 2.50775435507154e-15 * fRec11[0];
		double fTemp4 = 5.0155087101430697e-15 * fRec11[0];
		double fTemp5 = fConst0 * fRec10[0] * (9.4291563750689799e-17 * fRec11[0] + fRec10[0] * (0.0 - 9.3871181840269195e-19 * fRec11[0] + -9.3871181840269204e-22) + 9.4291563750689797e-20);
		double fTemp6 = (fRec8[0] * (fTemp2 - fTemp3 + -2.50775435507154e-18) + fRec8[1] * (fTemp4 + fTemp5 + 5.0155087101430701e-18) + fConst0 * fRec10[0] * fRec8[2] * (fRec10[0] * (1.4080677276040399e-18 * fRec11[0] + 1.40806772760404e-21) - 1.4143734562603501e-16 * fRec11[0] + -1.4143734562603499e-19) + fRec8[3] * (fTemp5 - fTemp4 + -5.0155087101430701e-18) + fRec8[4] * (fTemp3 + fTemp2 + 2.50775435507154e-18)) / fTemp1;
		fVec0[0] = fTemp6;
		fRec7[0] = fConst4 * (fTemp6 + fVec0[1]) - 0.86056958506478287 * fRec7[1];
		fRec6[0] = fRec7[0] - (1.8405051250752198 * fRec6[1] + 0.86129424393186271 * fRec6[2]);
		double fTemp7 = 1.8508996845035413 * fRec6[1] + 0.92544984225177063 * (fRec6[0] + fRec6[2]);
		double fTemp8 = double(Ftrany(int(TRANY_TABLE_7199P_68k), double(fTemp7 + 2700.0 * fTemp7 / (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fRec5[1]))) + 100000.0) + -3.5719810000000001)));
		fRec5[0] = fTemp8 + 0.001322955925925926 * (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fTemp8))) + 100000.0) + -250.0;
		fRec4[0] = fConst2 * (fConst3 * fRec4[1] + 0.025000000000000001 * (fRec5[0] - fRec5[1]));
		fRec3[0] = 0.93028479253239138 * (fRec4[0] + fRec4[1]) - 0.86056958506478287 * fRec3[1];
		fRec2[0] = fRec3[0] - (1.8405051250752198 * fRec2[1] + 0.86129424393186271 * fRec2[2]);
		double fTemp9 = 1.8508996845035413 * fRec2[1] + 0.92544984225177063 * (fRec2[0] + fRec2[2]);
		double fTemp10 = double(Ftrany(int(TRANY_TABLE_7199P_68k), double(fTemp9 + 2700.0 * fTemp9 / (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fRec1[1]))) + 100000.0) + -3.5719810000000001)));
		fRec1[0] = fTemp10 + 0.001322955925925926 * (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fTemp10))) + 100000.0) + -250.0;
		fRec0[0] = fConst2 * (fConst3 * fRec0[1] + 0.025000000000000001 * (fRec1[0] - fRec1[1]));
		output0[i0] = FAUSTFLOAT(fRec0[0] + fTemp0 * (1.0 - fRec9[0]));
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		for (int j0 = 4; j0 > 0; j0 = j0 - 1) {
			fRec8[j0] = fRec8[j0 - 1];
		}
		fRec11[1] = fRec11[0];
		fVec0[1] = fVec0[0];
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
#undef fVslider2
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case ATTACK: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 0.94999999999999996, 0.01 
		break;
	case LEVEL: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fVslider0_ = (float*)data; // , 100.0, 0.0, 100.0, 1.0 
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
   ATTACK, 
   LEVEL, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace cstb
