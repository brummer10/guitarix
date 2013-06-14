// generated from file '../src/LV2/faust/gxtilttone.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)

#include "valve.h"

namespace gxtilttone {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fVec0[2];
	double 	fConst13;
	double 	fRec7[2];
	double 	fRec6[2];
	double 	fConst14;
	double 	fConst15;
	double 	fRec5[2];
	double 	fConst16;
	double 	fConst17;
	double 	fRec4[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fRec8[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec9[2];
	double 	fVec1[2];
	double 	fConst22;
	double 	fRec3[2];
	double 	fVec2[2];
	double 	fRec10[2];
	double 	fRec2[2];
	double 	fRec1[2];
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, float *input0, float *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, float *input0, float *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "gxtilttone";
	name = N_("Gx Tilt Tone");
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = (1.0 / tan((5830.795965062656 / double(iConst0))));
	fConst8 = (1 + fConst7);
	fConst9 = (0 - ((1 - fConst7) / fConst8));
	fConst10 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst11 = (1 + fConst10);
	fConst12 = (0 - ((1 - fConst10) / fConst11));
	fConst13 = (1.0 / fConst11);
	fConst14 = (0 - fConst1);
	fConst15 = (0.025 / fConst2);
	fConst16 = (0 - fConst7);
	fConst17 = (1.0 / fConst8);
	fConst18 = (1.0 / tan((1281.7698026646356 / double(iConst0))));
	fConst19 = (1 + fConst18);
	fConst20 = (0 - ((1 - fConst18) / fConst19));
	fConst21 = (1.0 / fConst19);
	fConst22 = (1.0 / fConst5);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, float *input0, float *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = fslider1;
	double 	fSlow2 = (1 - fSlow1);
	double 	fSlow3 = (0.0010000000000000009 * pow(10,(0.05 * fslider2)));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		double fTemp0 = (1e-15 + (0.027 * fRec6[1]));
		fVec0[0] = fTemp0;
		fRec7[0] = ((fConst13 * (fVec0[0] + fVec0[1])) + (fConst12 * fRec7[1]));
		fRec6[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec7[0] + ((double)input0[i] * fRec0[0])) - 1.5816559999999988)) - 191.42014814814814);
		fRec5[0] = ((fConst15 * ((fConst14 * fRec6[1]) + (fConst1 * fRec6[0]))) + (fConst3 * fRec5[1]));
		fRec4[0] = ((fConst17 * ((fConst16 * fRec5[1]) + (fConst7 * fRec5[0]))) + (fConst9 * fRec4[1]));
		fRec8[0] = ((fConst21 * (fRec5[0] + fRec5[1])) + (fConst20 * fRec8[1]));
		fRec9[0] = (fSlow3 + (0.999 * fRec9[1]));
		double fTemp1 = (fRec9[0] * ((fSlow2 * fRec8[0]) + (fSlow1 * fRec4[0])));
		fVec1[0] = fTemp1;
		fRec3[0] = ((fConst22 * (fVec1[0] + fVec1[1])) + (fConst6 * fRec3[1]));
		double fTemp2 = (1e-15 + (0.027 * fRec2[1]));
		fVec2[0] = fTemp2;
		fRec10[0] = ((fConst13 * (fVec2[0] + fVec2[1])) + (fConst12 * fRec10[1]));
		fRec2[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec10[0] + fRec3[0]) - 1.5816559999999988)) - 191.42014814814814);
		fRec1[0] = ((fConst15 * ((fConst14 * fRec2[1]) + (fConst1 * fRec2[0]))) + (fConst3 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(fRec1[0] / fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec10[1] = fRec10[0];
		fVec2[1] = fVec2[0];
		fRec3[1] = fRec3[0];
		fVec1[1] = fVec1[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fVec0[1] = fVec0[0];
		fRec0[1] = fRec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case GAIN: 
		fslider2_ = (float*)data; // , 0.0, 0.0, 2e+01, 0.1 
		break;
	case TONE: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case DRIVE: 
		fslider0_ = (float*)data; // , 0.0, 0.0, 2e+01, 0.1 
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
   GAIN, 
   TONE, 
   DRIVE, 
} PortIndex;
*/

} // end namespace gxtilttone
