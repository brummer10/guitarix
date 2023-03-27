// generated from file '../src/LV2/faust/cstb.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "trany.h"

namespace cstb {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec9[2];
	double fConst0;
	double fConst2;
	double fConst4;
	double fConst6;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec10[2];
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst13;
	double fConst14;
	double fConst16;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fRec11[5];
	double fVec0[2];
	double fRec8[2];
	double fRec7[3];
	double fRec6[2];
	double fConst25;
	double fConst26;
	double fRec5[2];
	double fRec4[2];
	double fRec3[3];
	double fRec2[2];
	double fRec1[2];

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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec9[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec10[l2] = 0.0;
	for (int l3 = 0; l3 < 5; l3 = l3 + 1) fRec11[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fVec0[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec8[l5] = 0.0;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec7[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec6[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec5[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec4[l9] = 0.0;
	for (int l10 = 0; l10 < 3; l10 = l10 + 1) fRec3[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec2[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec1[l12] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 7.13788307669893e-19 * fConst0;
	fConst2 = fConst0 * (fConst0 * (-3.81274375281155e-16 - fConst1) + -1.78337596435683e-14) + -3.57720562427687e-14;
	double fConst3 = 7.26395344169953e-19 * fConst0;
	fConst4 = fConst0 * (fConst0 * (fConst3 + 3.82634300978431e-16) + 1.78716714442828e-14) + 3.58457860428614e-14;
	double fConst5 = 7.72761004436121e-17 * fConst0;
	fConst6 = fConst0 * (fConst5 + 4.0705776699833e-14) + 1.90124164300881e-12;
	fConst7 = mydsp_faustpower3_f(fConst0);
	fConst8 = mydsp_faustpower4_f(fConst0);
	fConst9 = fConst0 * (fConst0 * (3.81274375281155e-16 - fConst1) + -1.78337596435683e-14) + 3.57720562427687e-14;
	fConst10 = fConst0 * (fConst0 * (fConst3 + -3.82634300978431e-16) + 1.78716714442828e-14) + -3.58457860428614e-14;
	fConst11 = fConst0 * (4.0705776699833e-14 - fConst5) + -1.90124164300881e-12;
	double fConst12 = 2.85515323067957e-18 * fConst0;
	fConst13 = mydsp_faustpower2_f(fConst0);
	fConst14 = fConst13 * (fConst12 + -7.6254875056231e-16) + 7.15441124855374e-14;
	double fConst15 = 2.90558137667981e-18 * fConst0;
	fConst16 = fConst13 * (7.65268601956861e-16 - fConst15) + -7.16915720857228e-14;
	double fConst17 = 1.54552200887224e-16 * fConst13;
	fConst18 = fConst17 + -3.80248328601762e-12;
	fConst19 = 3.56675192871367e-14 - 4.28272984601936e-18 * fConst13;
	fConst20 = 4.35837206501972e-18 * fConst13 + -3.57433428885656e-14;
	fConst21 = fConst13 * (fConst12 + 7.6254875056231e-16) + -7.15441124855374e-14;
	fConst22 = fConst13 * (-7.65268601956861e-16 - fConst15) + 7.16915720857228e-14;
	fConst23 = 3.80248328601762e-12 - fConst17;
	double fConst24 = 3.141592653589793 / fConst0;
	fConst25 = 1.0 - fConst24;
	fConst26 = 1.0 / (fConst24 + 1.0);
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
	double fSlow0 = 7.000000000000006e-05 * double(fVslider0);
	double fSlow1 = 0.007000000000000006 * double(fVslider1);
	double fSlow2 = 0.007000000000000006 * double(fVslider2);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		double fTemp0 = double(input0[i0]);
		fRec9[0] = fSlow1 + 0.993 * fRec9[1];
		double fTemp1 = fConst0 * (fConst6 + fRec9[0] * (fConst4 + fConst2 * fRec9[0])) + 3.81338149392143e-12;
		fRec10[0] = fSlow2 + 0.993 * fRec10[1];
		double fTemp2 = 2.50775435507154e-15 * fRec10[0];
		double fTemp3 = fConst8 * fRec9[0] * (fRec9[0] * (2.34677954600673e-19 * fRec10[0] + 2.34677954600673e-22) - 2.35728909376724e-17 * fRec10[0] + -2.35728909376724e-20);
		fRec11[0] = fTemp0 * fRec0[0] - (fRec11[1] * (fConst0 * (fConst23 + fRec9[0] * (fConst22 + fConst21 * fRec9[0])) + 1.52535259756857e-11) + fRec11[2] * (fConst13 * (fRec9[0] * (fConst20 + fConst19 * fRec9[0]) + -8.14115533996661e-14) + 2.28802889635286e-11) + fRec11[3] * (fConst0 * (fConst18 + fRec9[0] * (fConst16 + fConst14 * fRec9[0])) + 1.52535259756857e-11) + fRec11[4] * (fConst0 * (fConst11 + fRec9[0] * (fConst10 + fConst9 * fRec9[0])) + 3.81338149392143e-12)) / fTemp1;
		double fTemp4 = 5.01550871014307e-15 * fRec10[0];
		double fTemp5 = fConst8 * fRec9[0] * (9.42915637506898e-17 * fRec10[0] + fRec9[0] * (0.0 - 9.38711818402692e-19 * fRec10[0] + -9.38711818402692e-22) + 9.42915637506898e-20);
		double fTemp6 = (fRec11[0] * (fTemp3 + fConst7 * (-2.50775435507154e-18 - fTemp2)) + fRec11[1] * (fTemp5 + fConst7 * (fTemp4 + 5.01550871014307e-18)) + fConst8 * fRec9[0] * fRec11[2] * (fRec9[0] * (1.40806772760404e-18 * fRec10[0] + 1.40806772760404e-21) - 1.41437345626035e-16 * fRec10[0] + -1.41437345626035e-19) + fRec11[3] * (fTemp5 + fConst7 * (-5.01550871014307e-18 - fTemp4)) + fRec11[4] * (fTemp3 + fConst7 * (fTemp2 + 2.50775435507154e-18))) / fTemp1;
		fVec0[0] = fTemp6;
		fRec8[0] = 0.9302847925323914 * (fTemp6 + fVec0[1]) - 0.8605695850647829 * fRec8[1];
		fRec7[0] = fRec8[0] - (1.8405051250752198 * fRec7[1] + 0.8612942439318627 * fRec7[2]);
		double fTemp7 = 1.8508996845035413 * fRec7[1] + 0.9254498422517706 * (fRec7[0] + fRec7[2]);
		double fTemp8 = Ftrany(TRANY_TABLE_7199P_68k, fTemp7 + 2.7e+03 * (fTemp7 / (Rtrany(TRANY_TABLE_7199P_68k, fRec6[1]) + 1e+05)) + -3.571981);
		fRec6[0] = fTemp8 + 0.001322955925925926 * (Rtrany(TRANY_TABLE_7199P_68k, fTemp8) + 1e+05) + -2.5e+02;
		fRec5[0] = fConst26 * (fConst25 * fRec5[1] + 0.025 * (fRec6[0] - fRec6[1]));
		fRec4[0] = 0.9302847925323914 * (fRec5[0] + fRec5[1]) - 0.8605695850647829 * fRec4[1];
		fRec3[0] = fRec4[0] - (1.8405051250752198 * fRec3[1] + 0.8612942439318627 * fRec3[2]);
		double fTemp9 = 1.8508996845035413 * fRec3[1] + 0.9254498422517706 * (fRec3[0] + fRec3[2]);
		double fTemp10 = Ftrany(TRANY_TABLE_7199P_68k, fTemp9 + 2.7e+03 * (fTemp9 / (Rtrany(TRANY_TABLE_7199P_68k, fRec2[1]) + 1e+05)) + -3.571981);
		fRec2[0] = fTemp10 + 0.001322955925925926 * (Rtrany(TRANY_TABLE_7199P_68k, fTemp10) + 1e+05) + -2.5e+02;
		fRec1[0] = fConst26 * (fConst25 * fRec1[1] + 0.025 * (fRec2[0] - fRec2[1]));
		output0[i0] = FAUSTFLOAT(fRec1[0] + fTemp0 * (1.0 - fRec0[0]));
		fRec0[1] = fRec0[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		for (int j0 = 4; j0 > 0; j0 = j0 - 1) {
			fRec11[j0] = fRec11[j0 - 1];
		}
		fVec0[1] = fVec0[0];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
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
		fVslider1_ = (float*)data; // , 0.5, 0.0, 0.95, 0.01 
		break;
	case LEVEL: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fVslider0_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
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
