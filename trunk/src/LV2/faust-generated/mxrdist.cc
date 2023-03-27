// generated from file '../src/LV2/faust/mxrdist.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "clipping.h"

namespace mxrdist {

class Dsp: public PluginLV2 {
private:
	gx_resample::FixedRateResampler smp;
	uint32_t sample_rate;
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	double fConst2;
	double fConst4;
	double fConst6;
	double fConst8;
	double fConst10;
	double fConst11;
	double fConst13;
	double fConst14;
	double fConst15;
	double fRec4[3];
	double fConst17;
	double fConst18;
	double fConst19;
	double fVec0[2];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	double fRec6[2];
	double fConst20;
	double fRec5[2];
	double fVec1[2];
	double fConst21;
	double fConst22;
	double fRec3[2];
	double fRec2[3];
	double fRec1[3];
	double fConst23;

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
	id = "mxrdis";
	name = N_("MXR Distortion Plus");
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
	for (int l1 = 0; l1 < 3; l1 = l1 + 1) fRec4[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fVec0[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec6[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec5[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fVec1[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec3[l6] = 0.0;
	for (int l7 = 0; l7 < 3; l7 = l7 + 1) fRec2[l7] = 0.0;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec1[l8] = 0.0;
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
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 1.40668739186091e-10 * fConst0;
	fConst2 = fConst0 * (fConst1 + -1.40739073555684e-05) + 0.000351671847965227;
	double fConst3 = mydsp_faustpower2_f(fConst0);
	fConst4 = 0.000703343695930453 - 2.81337478372181e-10 * fConst3;
	double fConst5 = fConst0 * (fConst1 + 1.40739073555684e-05) + 0.000351671847965227;
	fConst6 = 1.0 / fConst5;
	double fConst7 = std::tan(50893.800988154646 / fConst0);
	fConst8 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst7));
	double fConst9 = 1.0 / fConst7;
	fConst10 = (fConst9 + -1.0000000000000004) / fConst7 + 1.0;
	fConst11 = 1.0 / ((fConst9 + 1.0000000000000004) / fConst7 + 1.0);
	double fConst12 = 4.3356710341455e-10 * fConst0;
	fConst13 = fConst0 * (fConst12 + -2.2111922274142e-08) + 2.14637179908193e-08;
	fConst14 = 4.29274359816386e-08 - 8.671342068291e-10 * fConst3;
	fConst15 = 1.0 / (fConst0 * (fConst12 + 2.2111922274142e-08) + 2.14637179908193e-08);
	double fConst16 = 4.29274359816386e-10 * fConst0;
	fConst17 = fConst0 * (fConst16 + -6.43911539724579e-10);
	fConst18 = 0.0 - 8.58548719632772e-10 * fConst3;
	fConst19 = fConst0 * (fConst16 + 6.43911539724579e-10);
	fConst20 = 9.4e-08 * fConst0;
	fConst21 = 1.0 - fConst9;
	fConst22 = 1.0 / (fConst9 + 1.0);
	fConst23 = fConst0 / fConst5;
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
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double fSlow0 = 0.007000000000000006 * double(fVslider0);
	double fSlow1 = 0.007000000000000006 * (0.25 * double(fHslider0) + 0.75);
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		fRec4[0] = double(buf[i0]) - fConst15 * (fConst14 * fRec4[1] + fConst13 * fRec4[2]);
		double fTemp0 = fConst19 * fRec4[0] + fConst18 * fRec4[1] + fConst17 * fRec4[2];
		fVec0[0] = fTemp0;
		double fTemp1 = fConst15 * fTemp0;
		fRec6[0] = fSlow1 + 0.993 * fRec6[1];
		double fTemp2 = 1.0 - fRec6[0];
		double fTemp3 = fConst20 * (5e+05 * fTemp2 + 4.7e+03);
		double fTemp4 = fConst20 * (5e+05 * (fRec6[0] + fTemp2) + 9.7e+03);
		fRec5[0] = 0.0 - (fRec5[1] * (1.0 - fTemp3) - fConst15 * (fTemp0 * (fTemp4 + 1.0) + fVec0[1] * (1.0 - fTemp4))) / (fTemp3 + 1.0);
		double fTemp5 = fTemp1 - opamp2(fRec5[0] - fTemp1);
		fVec1[0] = fTemp5;
		fRec3[0] = 0.0 - fConst22 * (fConst21 * fRec3[1] - (fTemp5 + fVec1[1]));
		fRec2[0] = fRec3[0] - fConst11 * (fConst10 * fRec2[2] + fConst8 * fRec2[1]);
		fRec1[0] = fConst11 * (fRec2[2] + fRec2[0] + 2.0 * fRec2[1]) - fConst6 * (fConst4 * fRec1[1] + fConst2 * fRec1[2]);
		buf[i0] = FAUSTFLOAT(fConst23 * (fRec1[2] * (0.0 - 7.03343695930453e-06 * fRec0[0]) + 7.03343695930453e-06 * fRec1[0] * fRec0[0]));
		fRec0[1] = fRec0[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fVec0[1] = fVec0[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fVec1[1] = fVec1[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
	}
	smp.down(buf, output0);
#undef fVslider0
#undef fHslider0
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case VOLUME: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case DRIVE: 
		fHslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   VOLUME, 
   DRIVE, 
} PortIndex;
*/

} // end namespace mxrdist
