// generated from file '../src/LV2/faust/mxrdist.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)

#include "clipping.h"

namespace mxrdist {

class Dsp: public PluginLV2 {
private:
	gx_resample::FixedRateResampler smp;
	uint32_t samplingFreq;
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
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fRec4[3];
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fVec0[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec6[2];
	double 	fConst21;
	double 	fConst22;
	double 	fRec5[2];
	double 	fVec1[2];
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fRec1[3];
	double 	fConst26;
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t RsamplingFreq)
{
	samplingFreq = 96000;
	smp.setup(RsamplingFreq, samplingFreq);
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = double(iConst0);
	fConst2 = (1.40668739186091e-10 * fConst1);
	fConst3 = (0.000351671847965227 + (fConst1 * (fConst2 - 1.40739073555684e-05)));
	fConst4 = faustpower<2>(fConst1);
	fConst5 = (0.000703343695930453 - (2.81337478372181e-10 * fConst4));
	fConst6 = (0.000351671847965227 + (fConst1 * (1.40739073555684e-05 + fConst2)));
	fConst7 = (1.0 / fConst6);
	fConst8 = tan((50893.800988154646 / double(iConst0)));
	fConst9 = (2 * (1 - (1.0 / faustpower<2>(fConst8))));
	fConst10 = (1.0 / fConst8);
	fConst11 = (1 + ((fConst10 - 1.0000000000000004) / fConst8));
	fConst12 = (1.0 / (1 + ((1.0000000000000004 + fConst10) / fConst8)));
	fConst13 = (4.3356710341455e-10 * fConst1);
	fConst14 = (2.14637179908193e-08 + (fConst1 * (fConst13 - 2.2111922274142e-08)));
	fConst15 = (4.29274359816386e-08 - (8.671342068291e-10 * fConst4));
	fConst16 = (1.0 / (2.14637179908193e-08 + (fConst1 * (2.2111922274142e-08 + fConst13))));
	fConst17 = (4.29274359816386e-10 * fConst1);
	fConst18 = (fConst1 * (fConst17 - 6.43911539724579e-10));
	fConst19 = (0 - (8.58548719632772e-10 * fConst4));
	fConst20 = (fConst1 * (6.43911539724579e-10 + fConst17));
	fConst21 = (9.4e-08 * iConst0);
	fConst22 = (0.047 * iConst0);
	fConst23 = (1 + fConst10);
	fConst24 = (1.0 / fConst23);
	fConst25 = (0 - ((1 - fConst10) / fConst23));
	fConst26 = (fConst1 / fConst6);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * (0.75 + (0.25 * double(fslider1))));
	for (int i=0; i<ReCount; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		fRec4[0] = ((double)buf[i] - (fConst16 * ((fConst15 * fRec4[1]) + (fConst14 * fRec4[2]))));
		double fTemp0 = (((fConst20 * fRec4[0]) + (fConst19 * fRec4[1])) + (fConst18 * fRec4[2]));
		fVec0[0] = fTemp0;
		double fTemp1 = (fConst16 * fVec0[0]);
		fRec6[0] = (fSlow1 + (0.993 * fRec6[1]));
		double fTemp2 = (1.0 - fRec6[0]);
		double fTemp3 = (fConst21 * (4700 + (500000 * fTemp2)));
		double fTemp4 = (1 + fTemp3);
		double fTemp5 = (fConst22 * (0.0194 + (fRec6[0] + fTemp2)));
		fRec5[0] = ((fRec5[1] * (0 - ((1 - fTemp3) / fTemp4))) + (fConst16 * (((fVec0[0] * (1 + fTemp5)) + (fVec0[1] * (1 - fTemp5))) / fTemp4)));
		double fTemp6 = (fTemp1 - opamp2((fRec5[0] - fTemp1)));
		fVec1[0] = fTemp6;
		fRec3[0] = ((fConst25 * fRec3[1]) + (fConst24 * (fVec1[0] + fVec1[1])));
		fRec2[0] = (fRec3[0] - (fConst12 * ((fConst11 * fRec2[2]) + (fConst9 * fRec2[1]))));
		fRec1[0] = ((fConst12 * (fRec2[2] + (fRec2[0] + (2 * fRec2[1])))) - (fConst7 * ((fConst5 * fRec1[1]) + (fConst3 * fRec1[2]))));
		buf[i] = (FAUSTFLOAT)(fConst26 * ((fRec1[2] * (0 - (7.03343695930453e-06 * fRec0[0]))) + (7.03343695930453e-06 * (fRec1[0] * fRec0[0]))));
		// post processing
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fVec1[1] = fVec1[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fVec0[1] = fVec0[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec0[1] = fRec0[0];
	}
	smp.down(buf, output0);
#undef fslider0
#undef fslider1
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
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case DRIVE: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
