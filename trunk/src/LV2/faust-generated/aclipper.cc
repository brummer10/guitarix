// generated from file '../src/LV2/faust/aclipper.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "clipping.h"

namespace aclipper {

class Dsp: public PluginLV2 {
private:
	gx_resample::FixedRateResampler smp;
	uint32_t sample_rate;
	uint32_t fSampleRate;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	double fRec0[2];
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fRec4[3];
	double fConst13;
	double fConst14;
	double fVec0[2];
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	double fRec6[2];
	double fRec5[2];
	double fConst19;
	double fRec3[2];
	double fConst20;
	double fConst21;
	double fConst22;
	double fRec2[3];
	double fConst23;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec7[2];
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
	id = "aclipper";
	name = N_("Rat");
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) fRec4[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fVec0[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec6[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec5[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec3[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec2[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec7[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec1[l8] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t RsamplingFreq)
{
	sample_rate = 96000;
	smp.setup(RsamplingFreq, sample_rate);
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	fConst2 = (4.3384046341363998e-10 * fConst0);
	fConst3 = ((fConst0 * (fConst2 + 8.9903789745771695e-09)) + 3.4104193494676199e-08);
	fConst4 = (fConst1 / fConst3);
	fConst5 = (2.0833287160267799e-05 * fConst0);
	fConst6 = (fConst5 + 2.2163071447093401e-06);
	fConst7 = (1.0 / fConst6);
	fConst8 = (0.0 - fConst5);
	fConst9 = (3.6486544757381099e-11 * fConst0);
	fConst10 = (1.0 / ((fConst0 * (fConst9 + 1.9073341271921e-05)) + 0.00041461982678842101));
	fConst11 = (0.00082923965357684201 - (7.2973089514762096e-11 * fConst1));
	fConst12 = ((fConst0 * (fConst9 + -1.9073341271921e-05)) + 0.00041461982678842101);
	fConst13 = (1.8243272378690499e-05 * fConst0);
	fConst14 = (0.0 - fConst13);
	fConst15 = (0.00044179999999999995 * fConst0);
	fConst16 = (1.0 / (fConst15 + 1.0));
	fConst17 = (1.0 - fConst15);
	fConst18 = (9.3999999999999995e-08 * fConst0);
	fConst19 = ((2.2163071447093401e-06 - fConst5) / fConst6);
	fConst20 = (1.0 / fConst3);
	fConst21 = (6.8208386989352305e-08 - (8.6768092682727995e-10 * fConst1));
	fConst22 = ((fConst0 * (fConst2 + -8.9903789745771695e-09)) + 3.4104193494676199e-08);
	fConst23 = (3.9192399049881199e-05 * fConst0);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fHslider0 (*fHslider0_)
#define fHslider1 (*fHslider1_)
#define fVslider0 (*fVslider0_)
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double fSlow0 = (0.0070000000000000062 * std::pow(10.0, (0.050000000000000003 * double(fHslider0))));
	double fSlow1 = (0.0070000000000000062 * double(fHslider1));
	double fSlow2 = (0.0070000000000000062 * (1.0 - double(fVslider0)));
	for (int i = 0; (i < ReCount); i = (i + 1)) {
		fRec0[0] = (fSlow0 + (0.99299999999999999 * fRec0[1]));
		fRec4[0] = (double(buf[i]) - (fConst10 * ((fConst11 * fRec4[1]) + (fConst12 * fRec4[2]))));
		double fTemp0 = (((0.00082923965357684201 * fRec4[1]) + (fConst13 * fRec4[0])) + (fConst14 * fRec4[2]));
		fVec0[0] = fTemp0;
		double fTemp1 = (fConst10 * fTemp0);
		fRec6[0] = (fSlow1 + (0.99299999999999999 * fRec6[1]));
		double fTemp2 = (fConst18 * ((500000.0 * fRec6[0]) + 5700.0));
		fRec5[0] = (0.0 - (fConst16 * ((fConst17 * fRec5[1]) - (fConst10 * ((fTemp0 * (fTemp2 + 1.0)) + (fVec0[1] * (1.0 - fTemp2)))))));
		fRec3[0] = (fTemp1 - (double(opamp(double((fRec5[0] - fTemp1)))) + (fConst19 * fRec3[1])));
		fRec2[0] = ((fConst7 * ((fConst8 * fRec3[1]) + (fConst5 * fRec3[0]))) - (fConst20 * ((fConst21 * fRec2[1]) + (fConst22 * fRec2[2]))));
		double fTemp3 = ((0.75 * fRec6[0]) + 0.5);
		double fTemp4 = (0.0 - (9.2680065673288896e-10 * fTemp3));
		fRec7[0] = (fSlow2 + (0.99299999999999999 * fRec7[1]));
		double fTemp5 = ((fConst0 * ((0.0 - (3.9192399049881199e-05 * fRec7[0])) + 3.9192399049881199e-05)) + 0.059382422802850401);
		fRec1[0] = (double(asymhardclip2(double((fConst4 * (((fRec2[0] * fTemp4) + (1.85360131346578e-09 * (fRec2[1] * fTemp3))) + (fRec2[2] * fTemp4)))))) - ((fRec1[1] * ((fConst23 * (fRec7[0] + -1.0)) + 0.059382422802850401)) / fTemp5));
		buf[i] = FAUSTFLOAT((0.059382422802850401 * ((fRec0[0] * (fRec1[0] + fRec1[1])) / fTemp5)));
		fRec0[1] = fRec0[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fVec0[1] = fVec0[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec7[1] = fRec7[0];
		fRec1[1] = fRec1[0];
	}
	smp.down(buf, output0);
#undef fHslider0
#undef fHslider1
#undef fVslider0
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
		fHslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case LEVEL: 
		fHslider0_ = (float*)data; // , -2.0, -20.0, 12.0, 0.10000000000000001 
		break;
	case TONE: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   LEVEL, 
   TONE, 
} PortIndex;
*/

} // end namespace aclipper
