// generated from file '/home/drgreenthumb/Programs/Guitarix/fromSFNew/OC_2/guitarix-git/trunk/src/LV2/faust/oc_2.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "triggers_logic.h"

namespace oc_2 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double 	fRec4[4];
	double 	fVec0[2];
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fRec7[2];
	double 	fRec6[2];
	double 	fRec5[2];
	double 	fRec8[2];
	double 	fRec1[4];
	double 	fRec0[4];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
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
	id = "oc_2";
	name = "?oc_2";
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
	for (int i=0; i<4; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<4; i++) fRec1[i] = 0;
	for (int i=0; i<4; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
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
	double 	fSlow0 = double(fslider0);
	double 	fSlow1 = double(fslider1);
	double 	fSlow2 = (4.703703703703703 * double(fslider2));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		double fTemp1 = (4.703703703703703 * fTemp0);
		double fTemp2 = faustpower<2>(fTemp1);
		fRec4[0] = (((0.791348589885 * fRec4[3]) + (fTemp1 + (2.76624876953 * fRec4[1]))) - (2.55902485835 * fRec4[2]));
		double fTemp3 = (0.000178437366415 * fRec4[3]);
		double fTemp4 = (0.000535312099245 * (fRec4[2] + (fRec4[1] + (0.3333333333333333 * fRec4[0]))));
		fVec0[0] = (fTemp4 + fTemp3);
		fRec3[0] = ((fTemp4 + ((0.995 * fRec3[1]) + fTemp3)) - fVec0[1]);
		fRec2[0] = ((0.118571615541 * fRec2[2]) + (fRec3[0] + (0.881254491312 * fRec2[1])));
		double fTemp5 = (0.421473513764 * fRec2[2]);
		double fTemp6 = ((0.421560460338 * fRec2[0]) + (8.69465732366e-05 * fRec2[1]));
		fRec7[0] = (fRec3[0] + (0.0222152690864 * fRec7[1]));
		fRec6[0] = ((0.488892365457 * (fRec7[0] + fRec7[1])) + (0.999793750645 * fRec6[1]));
		double fTemp7 = ((0.673301020934 * fRec6[0]) - (0.673094771579 * fRec6[1]));
		fRec5[0] = (((int((fTemp7 > 0)))?fTemp7:0) + (0.979381443299 * fRec5[1]));
		fRec8[0] = (((int((fTemp7 < 0)))?fTemp7:0) + (0.979381443299 * fRec8[1]));
		double fTemp8 = FF_D_4013_1(FF_D_4013_2(((int(((0.005 + (0.0103092783505 * (fRec5[0] + fRec5[1]))) > (fTemp6 - fTemp5))))?4:-4), ((int((((0.005 + fTemp6) - fTemp5) > (0.0103092783505 * (fRec8[0] + fRec8[1])))))?4:-4)));
		fRec1[0] = (((0.876739124843 * fRec1[3]) + (((int((fTemp8 >= 1.7)))?(0.00405839 + ((fTemp2 * (0.132141 + (fTemp1 * ((fTemp1 * ((fTemp1 * (0.00417957 + (fTemp1 * (0.00240722 + (fTemp1 * ((fTemp1 * ((fTemp1 * (1.10766e-05 + (fTemp1 * (4.53509e-06 + (fTemp1 * (0 - (1.48174e-07 + (5.46329e-08 * fTemp1)))))))) - 0.000147669)) - 0.00031334)))))) - 0.0213111)) - 0.0270142)))) + (1.4608527777777776 * fTemp0))):((fTemp2 * ((fTemp1 * (0.0310416 + (fTemp1 * (0.0243923 + (fTemp1 * ((fTemp1 * ((fTemp1 * (0.000359992 + (fTemp1 * (0.000168921 + (fTemp1 * ((fTemp1 * ((fTemp1 * (1.70224e-07 + (6.24813e-08 * fTemp1))) - 5.18709e-06)) - 1.27253e-05)))))) - 0.00275424)) - 0.00480214)))))) - 0.151369)) - ((1.676635185185185 * fTemp0) + 0.00488712))) + (2.86850153897 * fRec1[1]))) - (2.7455072335 * fRec1[2]));
		double fTemp9 = ((9.99636312588e-05 * (fRec1[2] + (fRec1[1] + (0.3333333333333333 * fRec1[0])))) + (3.33212104196e-05 * fRec1[3]));
		fRec0[0] = (((0.942941660718 * fRec0[3]) + (((int((FF_JK_4027(fTemp8) >= 1.7)))?(0.00405839 + (fTemp9 * (0.310575 + (fTemp9 * (0.132141 + (fTemp9 * ((fTemp9 * ((fTemp9 * (0.00417957 + (fTemp9 * (0.00240722 + (fTemp9 * ((fTemp9 * ((fTemp9 * (1.10766e-05 + (fTemp9 * (4.53509e-06 + (fTemp9 * (0 - (1.48174e-07 + (5.46329e-08 * fTemp9)))))))) - 0.000147669)) - 0.00031334)))))) - 0.0213111)) - 0.0270142))))))):((fTemp9 * ((fTemp9 * ((fTemp9 * (0.0310416 + (fTemp9 * (0.0243923 + (fTemp9 * ((fTemp9 * ((fTemp9 * (0.000359992 + (fTemp9 * (0.000168921 + (fTemp9 * ((fTemp9 * ((fTemp9 * (1.70224e-07 + (6.24813e-08 * fTemp9))) - 5.18709e-06)) - 1.27253e-05)))))) - 0.00275424)) - 0.00480214)))))) - 0.151369)) - 0.35645)) - 0.00488712)) + (2.9412533592 * fRec0[1]))) - (2.88421963731 * fRec0[2]));
		output0[i] = (FAUSTFLOAT)(((fSlow2 * fTemp0) + (fSlow1 * fTemp9)) + (fSlow0 * ((9.23152182183e-06 * (fRec0[2] + (fRec0[1] + (0.3333333333333333 * fRec0[0])))) + (3.07717394061e-06 * fRec0[3]))));
		// post processing
		for (int i=3; i>0; i--) fRec0[i] = fRec0[i-1];
		for (int i=3; i>0; i--) fRec1[i] = fRec1[i-1];
		fRec8[1] = fRec8[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fVec0[1] = fVec0[0];
		for (int i=3; i>0; i--) fRec4[i] = fRec4[i-1];
	}
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
	case DIRECT: 
		fslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.05 
		break;
	case OCTAVE1: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.05 
		break;
	case OCTAVE2: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.05 
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
   DIRECT, 
   OCTAVE1, 
   OCTAVE2, 
} PortIndex;
*/

} // end namespace oc_2
