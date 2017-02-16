// generated from file '../src/LV2/faust/aclipper.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)

#include "clipping.h"

namespace aclipper {

class Dsp: public PluginLV2 {
private:
	double 	fLowVec0[2];
	uint32_t 	iLowConst0;
	double 	fLowConst1;
	double 	fLowConst2;
	double 	fLowConst3;
	double 	fLowConst4;
	double 	fLowRec0[2];
	gx_resample::FixedRateResampler smp;
	uint32_t samplingFreq;
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec2[2];
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
	double 	fRec5[3];
	double 	fConst13;
	double 	fConst14;
	double 	fVec0[2];
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fRec6[2];
	double 	fRec4[2];
	double 	fConst23;
	double 	fConst24;
	double 	fRec3[3];
	double 	fConst25;
	double 	fRec1[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec7[2];
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fLowVec0[i] = 0;
	for (int i=0; i<2; i++) fLowRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t RsamplingFreq)
{
	samplingFreq = 96000;
	smp.setup(RsamplingFreq, samplingFreq);
	iLowConst0 = min(192000, max(1, RsamplingFreq));
	fLowConst1 = (1.0 / tan((1.5707963267948966 * (double(iLowConst0) / double(iLowConst0)))));
	fLowConst2 = (1 + fLowConst1);
	fLowConst3 = (1.0 / fLowConst2);
	fLowConst4 = (0 - ((1 - fLowConst1) / fLowConst2));
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = double(iConst0);
	fConst2 = (4.3384046341364e-10 * fConst1);
	fConst3 = (3.41041934946762e-08 + (fConst1 * (fConst2 - 8.99037897457717e-09)));
	fConst4 = faustpower<2>(fConst1);
	fConst5 = (6.82083869893523e-08 - (8.6768092682728e-10 * fConst4));
	fConst6 = (3.41041934946762e-08 + (fConst1 * (8.99037897457717e-09 + fConst2)));
	fConst7 = (1.0 / fConst6);
	fConst8 = (3.64865447573811e-11 * fConst1);
	fConst9 = (0.000414619826788421 + (fConst1 * (fConst8 - 1.9073341271921e-05)));
	fConst10 = (0.000829239653576842 - (7.29730895147621e-11 * fConst4));
	fConst11 = (0.000414619826788421 + (fConst1 * (1.9073341271921e-05 + fConst8)));
	fConst12 = (1.0 / fConst11);
	fConst13 = (1.82432723786905e-05 * fConst1);
	fConst14 = (0 - fConst13);
	fConst15 = (2.08332871602678e-05 * fConst1);
	fConst16 = (2.21630714470934e-06 + fConst15);
	fConst17 = ((2.21630714470934e-06 - fConst15) / fConst16);
	fConst18 = (9.4e-08 * iConst0);
	fConst19 = (0.00044179999999999995 * iConst0);
	fConst20 = (1 + fConst19);
	fConst21 = (1.0 / (fConst20 * fConst11));
	fConst22 = (0 - ((1 - fConst19) / fConst20));
	fConst23 = (0 - fConst15);
	fConst24 = (1.0 / fConst16);
	fConst25 = (fConst4 / fConst6);
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
#define fslider2 (*fslider2_)
	for (int i=0; i<count; i++) {
		double fLowTemp0 = (double)input0[i];
		fLowVec0[0] = fLowTemp0;
		fLowRec0[0] = ((fLowConst4 * fLowRec0[1]) + (fLowConst3 * (fLowVec0[0] + fLowVec0[1])));
		output0[i] = (FAUSTFLOAT)fLowRec0[0];
		// post processing
		fLowRec0[1] = fLowRec0[0];
		fLowVec0[1] = fLowVec0[0];
	}
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, output0, buf);
	double 	fSlow0 = (0.007000000000000006 * (1.0 - double(fslider0)));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	double 	fSlow2 = (0.007000000000000006 * pow(10,(0.05 * double(fslider2))));
	for (int i=0; i<ReCount; i++) {
		fRec0[0] = (fSlow0 + (0.993 * fRec0[1]));
		double fTemp0 = (3.91923990498812e-05 * fRec0[0]);
		double fTemp1 = (0.0593824228028504 + (fConst1 * (3.91923990498812e-05 + (0 - fTemp0))));
		fRec2[0] = (fSlow1 + (0.993 * fRec2[1]));
		double fTemp2 = (0.5 + (0.75 * fRec2[0]));
		double fTemp3 = (0 - (9.26800656732889e-10 * fTemp2));
		fRec5[0] = ((double)buf[i] - (fConst12 * ((fConst10 * fRec5[1]) + (fConst9 * fRec5[2]))));
		double fTemp4 = (((0.000829239653576842 * fRec5[1]) + (fConst13 * fRec5[0])) + (fConst14 * fRec5[2]));
		fVec0[0] = fTemp4;
		double fTemp5 = (fConst12 * fVec0[0]);
		double fTemp6 = (fConst18 * (5700 + (500000 * fRec2[0])));
		fRec6[0] = ((fConst22 * fRec6[1]) + (fConst21 * ((fVec0[0] * (1 + fTemp6)) + (fVec0[1] * (1 - fTemp6)))));
		fRec4[0] = (0 - ((opamp((fRec6[0] - fTemp5)) + (fConst17 * fRec4[1])) - fTemp5));
		fRec3[0] = ((fConst24 * ((fConst23 * fRec4[1]) + (fConst15 * fRec4[0]))) - (fConst7 * ((fConst5 * fRec3[1]) + (fConst3 * fRec3[2]))));
		fRec1[0] = (asymhardclip2((fConst25 * (((fRec3[0] * fTemp3) + (1.85360131346578e-09 * (fRec3[1] * fTemp2))) + (fRec3[2] * fTemp3)))) - ((fRec1[1] * (0.0593824228028504 + (fConst1 * (fTemp0 - 3.91923990498812e-05)))) / fTemp1));
		fRec7[0] = ((0.993 * fRec7[1]) + fSlow2);
		buf[i] = (FAUSTFLOAT)(0.0593824228028504 * ((fRec7[0] * (fRec1[0] + fRec1[1])) / fTemp1));
		// post processing
		fRec7[1] = fRec7[0];
		fRec1[1] = fRec1[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec6[1] = fRec6[0];
		fVec0[1] = fVec0[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec2[1] = fRec2[0];
		fRec0[1] = fRec0[0];
	}
	smp.down(buf, output0);
#undef fslider0
#undef fslider1
#undef fslider2
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
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case LEVEL: 
		fslider2_ = (float*)data; // , -2.0, -2e+01, 12.0, 0.1 
		break;
	case TONE: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
