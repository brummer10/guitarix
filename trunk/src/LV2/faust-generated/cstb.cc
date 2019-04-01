// generated from file '../src/LV2/faust/cstb.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#include "trany.h"

namespace cstb {

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
	double fRec9[2];
	double fConst6;
	double fConst7;
	double fConst8;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec10[2];
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
	double fRec8[5];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec11[2];
	double fVec0[2];
	double fRec7[2];
	double fRec6[3];
	double fConst27;
	double fConst28;
	double fConst29;
	double fRec12[2];
	double fRec5[3];
	double fConst30;
	double fConst31;
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fRec13[2];
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec9[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec10[l1] = 0.0;
	for (int l2 = 0; (l2 < 5); l2 = (l2 + 1)) fRec8[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec11[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fVec0[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec7[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec6[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec12[l7] = 0.0;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec5[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec4[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec3[l10] = 0.0;
	for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) fRec2[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec13[l12] = 0.0;
	for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) fRec1[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec0[l14] = 0.0;
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
	fConst5 = (0.93028479253239138 * mydsp_faustpower3_f(fConst0));
	fConst6 = mydsp_faustpower2_f(fConst0);
	fConst7 = (1.5455220088722401e-16 * fConst6);
	fConst8 = (3.8024832860176197e-12 - fConst7);
	fConst9 = (2.9055813766798102e-18 * fConst0);
	fConst10 = (((-7.6526860195686105e-16 - fConst9) * fConst6) + 7.1691572085722804e-14);
	fConst11 = (2.8551532306795701e-18 * fConst0);
	fConst12 = (((fConst11 + 7.6254875056230998e-16) * fConst6) + -7.1544112485537395e-14);
	fConst13 = ((4.3583720650197197e-18 * fConst6) + -3.5743342888565602e-14);
	fConst14 = (3.5667519287136698e-14 - (4.2827298460193598e-18 * fConst6));
	fConst15 = (fConst7 + -3.8024832860176197e-12);
	fConst16 = (((7.6526860195686105e-16 - fConst9) * fConst6) + -7.1691572085722804e-14);
	fConst17 = (((fConst11 + -7.6254875056230998e-16) * fConst6) + 7.1544112485537395e-14);
	fConst18 = (7.7276100443612104e-17 * fConst0);
	fConst19 = (((4.0705776699832999e-14 - fConst18) * fConst0) + -1.9012416430088098e-12);
	fConst20 = (7.2639534416995302e-19 * fConst0);
	fConst21 = (((((fConst20 + -3.8263430097843102e-16) * fConst0) + 1.7871671444282801e-14) * fConst0) + -3.5845786042861402e-14);
	fConst22 = (7.1378830766989301e-19 * fConst0);
	fConst23 = (((((3.8127437528115499e-16 - fConst22) * fConst0) + -1.7833759643568298e-14) * fConst0) + 3.5772056242768697e-14);
	fConst24 = (((fConst18 + 4.0705776699832999e-14) * fConst0) + 1.9012416430088098e-12);
	fConst25 = (((((fConst20 + 3.8263430097843102e-16) * fConst0) + 1.7871671444282801e-14) * fConst0) + 3.5845786042861402e-14);
	fConst26 = (((((-3.8127437528115499e-16 - fConst22) * fConst0) + -1.7833759643568298e-14) * fConst0) + -3.5772056242768697e-14);
	fConst27 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst28 = (1.0 / (fConst27 + 1.0));
	fConst29 = (1.0 - fConst27);
	fConst30 = (0.0 - fConst4);
	fConst31 = ((1.0 - fConst2) / fConst3);
	fVslider0 = FAUSTFLOAT(100.0);
	fVslider1 = FAUSTFLOAT(0.5);
	fVslider2 = FAUSTFLOAT(0.5);
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
#define fVslider2 (*fVslider2_)
	double fSlow0 = (7.0000000000000062e-05 * double(fVslider0));
	double fSlow1 = (0.0070000000000000062 * double(fVslider1));
	double fSlow2 = (0.0070000000000000062 * double(fVslider2));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec9[0] = (fSlow0 + (0.99299999999999999 * fRec9[1]));
		double fTemp0 = double(input0[i]);
		fRec10[0] = (fSlow1 + (0.99299999999999999 * fRec10[1]));
		double fTemp1 = ((fConst0 * (fConst24 + (fRec10[0] * (fConst25 + (fConst26 * fRec10[0]))))) + 3.8133814939214299e-12);
		fRec8[0] = ((fRec9[0] * fTemp0) - (((((fRec8[1] * ((fConst0 * (fConst8 + (fRec10[0] * (fConst10 + (fConst12 * fRec10[0]))))) + 1.52535259756857e-11)) + (fRec8[2] * ((fConst6 * ((fRec10[0] * (fConst13 + (fConst14 * fRec10[0]))) + -8.1411553399666099e-14)) + 2.28802889635286e-11))) + (fRec8[3] * ((fConst0 * (fConst15 + (fRec10[0] * (fConst16 + (fConst17 * fRec10[0]))))) + 1.52535259756857e-11))) + (fRec8[4] * ((fConst0 * (fConst19 + (fRec10[0] * (fConst21 + (fConst23 * fRec10[0]))))) + 3.8133814939214299e-12))) / fTemp1));
		fRec11[0] = (fSlow2 + (0.99299999999999999 * fRec11[1]));
		double fTemp2 = (fConst0 * (fRec10[0] * (((fRec10[0] * ((2.3467795460067299e-19 * fRec11[0]) + 2.3467795460067301e-22)) - (2.35728909376724e-17 * fRec11[0])) + -2.3572890937672401e-20)));
		double fTemp3 = (2.50775435507154e-15 * fRec11[0]);
		double fTemp4 = (5.0155087101430697e-15 * fRec11[0]);
		double fTemp5 = (fConst0 * (fRec10[0] * (((9.4291563750689799e-17 * fRec11[0]) + (fRec10[0] * ((0.0 - (9.3871181840269195e-19 * fRec11[0])) + -9.3871181840269204e-22))) + 9.4291563750689797e-20)));
		double fTemp6 = ((((((fRec8[0] * ((fTemp2 - fTemp3) + -2.50775435507154e-18)) + (fRec8[1] * ((fTemp4 + fTemp5) + 5.0155087101430701e-18))) + (fConst0 * ((fRec10[0] * fRec8[2]) * (((fRec10[0] * ((1.4080677276040399e-18 * fRec11[0]) + 1.40806772760404e-21)) - (1.4143734562603501e-16 * fRec11[0])) + -1.4143734562603499e-19)))) + (fRec8[3] * ((fTemp5 - fTemp4) + -5.0155087101430701e-18))) + (fRec8[4] * ((fTemp3 + fTemp2) + 2.50775435507154e-18))) / fTemp1);
		fVec0[0] = fTemp6;
		fRec7[0] = ((fConst5 * (fTemp6 + fVec0[1])) - (0.86056958506478287 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.86129424393186271 * fRec6[2])));
		fRec12[0] = (fConst28 * ((0.027 * (fRec5[1] + fRec5[2])) - (fConst29 * fRec12[1])));
		fRec5[0] = (double(Ftrany(int(TRANY_TABLE_KT88_68k), double((((0.92544984225177063 * (fRec6[0] + fRec6[2])) + (fRec12[0] + (1.8508996845035413 * fRec6[1]))) + -5.5628950000000001)))) + -43.966851851851828);
		fRec4[0] = ((0.025000000000000001 * ((fConst4 * fRec5[0]) + (fConst30 * fRec5[1]))) - (fConst31 * fRec4[1]));
		fRec3[0] = ((0.93028479253239138 * (fRec4[0] + fRec4[1])) - (0.86056958506478287 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.86129424393186271 * fRec2[2])));
		fRec13[0] = (fConst28 * ((0.027 * (fRec1[1] + fRec1[2])) - (fConst29 * fRec13[1])));
		fRec1[0] = (double(Ftrany(int(TRANY_TABLE_KT88_68k), double((((0.92544984225177063 * (fRec2[0] + fRec2[2])) + (fRec13[0] + (1.8508996845035413 * fRec2[1]))) + -5.5628950000000001)))) + -43.966851851851828);
		fRec0[0] = ((0.025000000000000001 * ((fConst4 * fRec1[0]) + (fConst30 * fRec1[1]))) - (fConst31 * fRec0[1]));
		output0[i] = FAUSTFLOAT((fRec0[0] + ((1.0 - fRec9[0]) * fTemp0)));
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		for (int j0 = 4; (j0 > 0); j0 = (j0 - 1)) {
			fRec8[j0] = fRec8[(j0 - 1)];
		}
		fRec11[1] = fRec11[0];
		fVec0[1] = fVec0[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec12[1] = fRec12[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec13[1] = fRec13[0];
		fRec1[2] = fRec1[1];
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
