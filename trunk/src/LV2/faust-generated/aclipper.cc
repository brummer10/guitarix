// generated from file '../src/LV2/faust/aclipper.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "clipping.h"

namespace aclipper {

class Dsp: public PluginLV2 {
private:
	gx_resample::FixedRateResampler smp;
	uint32_t sample_rate;
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	double fConst0;
	double fConst1;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	double fRec2[2];
	double fConst3;
	double fConst5;
	double fConst7;
	double fConst8;
	double fConst10;
	double fConst12;
	double fConst13;
	double fConst14;
	double fRec5[3];
	double fConst15;
	double fConst16;
	double fVec0[2];
	double fConst17;
	double fConst19;
	double fConst20;
	double fRec6[2];
	double fRec4[2];
	double fConst21;
	double fConst22;
	double fRec3[3];
	double fConst23;
	double fRec1[2];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	double fRec7[2];

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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec2[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRec5[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fVec0[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec6[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec4[l5] = 0.0;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec3[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec1[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec7[l8] = 0.0;
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
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 3.91923990498812e-05 * fConst0;
	double fConst2 = 4.3384046341364e-10 * fConst0;
	fConst3 = fConst0 * (fConst2 + -8.99037897457717e-09) + 3.41041934946762e-08;
	double fConst4 = mydsp_faustpower2_f(fConst0);
	fConst5 = 6.82083869893523e-08 - 8.6768092682728e-10 * fConst4;
	double fConst6 = fConst0 * (fConst2 + 8.99037897457717e-09) + 3.41041934946762e-08;
	fConst7 = 1.0 / fConst6;
	fConst8 = 2.08332871602678e-05 * fConst0;
	double fConst9 = fConst8 + 2.21630714470934e-06;
	fConst10 = (2.21630714470934e-06 - fConst8) / fConst9;
	double fConst11 = 3.64865447573811e-11 * fConst0;
	fConst12 = fConst0 * (fConst11 + -1.9073341271921e-05) + 0.000414619826788421;
	fConst13 = 0.000829239653576842 - 7.29730895147621e-11 * fConst4;
	fConst14 = 1.0 / (fConst0 * (fConst11 + 1.9073341271921e-05) + 0.000414619826788421);
	fConst15 = 1.82432723786905e-05 * fConst0;
	fConst16 = 0.0 - fConst15;
	fConst17 = 9.4e-08 * fConst0;
	double fConst18 = 0.00044179999999999995 * fConst0;
	fConst19 = 1.0 - fConst18;
	fConst20 = 1.0 / (fConst18 + 1.0);
	fConst21 = 0.0 - fConst8;
	fConst22 = 1.0 / fConst9;
	fConst23 = fConst4 / fConst6;
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fHslider0 (*fHslider0_)
#define fHslider1 (*fHslider1_)
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double fSlow0 = 0.007000000000000006 * (1.0 - double(fVslider0));
	double fSlow1 = 0.007000000000000006 * double(fHslider0);
	double fSlow2 = 0.007000000000000006 * std::pow(1e+01, 0.05 * double(fHslider1));
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		double fTemp0 = fConst0 * (0.0 - 3.91923990498812e-05 * fRec0[0] + 3.91923990498812e-05) + 0.0593824228028504;
		fRec2[0] = fSlow1 + 0.993 * fRec2[1];
		double fTemp1 = 0.75 * fRec2[0] + 0.5;
		double fTemp2 = 0.0 - 9.26800656732889e-10 * fTemp1;
		fRec5[0] = double(buf[i0]) - fConst14 * (fConst13 * fRec5[1] + fConst12 * fRec5[2]);
		double fTemp3 = 0.000829239653576842 * fRec5[1] + fConst15 * fRec5[0] + fConst16 * fRec5[2];
		fVec0[0] = fTemp3;
		double fTemp4 = fConst14 * fTemp3;
		double fTemp5 = fConst17 * (5e+05 * fRec2[0] + 5.7e+03);
		fRec6[0] = 0.0 - fConst20 * (fConst19 * fRec6[1] - fConst14 * (fTemp3 * (fTemp5 + 1.0) + fVec0[1] * (1.0 - fTemp5)));
		fRec4[0] = fTemp4 - (opamp(fRec6[0] - fTemp4) + fConst10 * fRec4[1]);
		fRec3[0] = fConst22 * (fConst21 * fRec4[1] + fConst8 * fRec4[0]) - fConst7 * (fConst5 * fRec3[1] + fConst3 * fRec3[2]);
		fRec1[0] = asymhardclip2(fConst23 * (fRec3[0] * fTemp2 + 1.85360131346578e-09 * fRec3[1] * fTemp1 + fRec3[2] * fTemp2)) - fRec1[1] * (0.0593824228028504 - fConst1 * (1.0 - fRec0[0])) / fTemp0;
		fRec7[0] = fSlow2 + 0.993 * fRec7[1];
		buf[i0] = FAUSTFLOAT(0.0593824228028504 * (fRec7[0] * (fRec1[0] + fRec1[1]) / fTemp0));
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fVec0[1] = fVec0[0];
		fRec6[1] = fRec6[0];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec1[1] = fRec1[0];
		fRec7[1] = fRec7[0];
	}
	smp.down(buf, output0);
#undef fVslider0
#undef fHslider0
#undef fHslider1
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
		fHslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case LEVEL: 
		fHslider1_ = (float*)data; // , -2.0, -2e+01, 12.0, 0.1 
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
