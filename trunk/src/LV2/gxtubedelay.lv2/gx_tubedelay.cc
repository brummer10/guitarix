// generated from file 'tubedelay.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)

#include "valve.h"

namespace tubedelay {

class Dsp: public PluginLV2 {
private:
	int fSamplingFreq;
	int 	iConst0;
	float 	fConst1;
	float 	fConst2;
	float 	fConst3;
	float 	fConst4;
	float 	fConst5;
	float 	fConst6;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	float 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	float 	fRec5[2];
	float 	fConst7;
	float 	fConst8;
	float 	fConst9;
	float 	fConst10;
	float 	fRec9[2];
	float 	fRec8[3];
	float 	fConst11;
	float 	fConst12;
	float 	fRec7[2];
	float 	fConst13;
	float 	fRec6[2];
	int 	IOTA;
	float 	fVec0[131072];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	float 	fConst14;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	float 	fRec10[2];
	float 	fRec4[2];
	float 	fConst15;
	float 	fRec11[2];
	float 	fRec2[3];
	float 	fRec1[2];
	float 	fRec0[2];
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(unsigned int samplingFreq, PluginLV2*);
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
	id = "tubedelay";
	name = N_("Tube Delay");
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
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<131072; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0f / tanf((20517.741620594938f / iConst0)));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0f / tanf((97.38937226128358f / iConst0)));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = (1.0f / tanf((125.66370614359172f / iConst0)));
	fConst8 = (1 + fConst7);
	fConst9 = (0 - ((1 - fConst7) / fConst8));
	fConst10 = (0.027f / fConst8);
	fConst11 = (0 - fConst4);
	fConst12 = (0.025f / fConst5);
	fConst13 = (1.0f / fConst2);
	IOTA = 0;
	fConst14 = (0.001f * iConst0);
	fConst15 = (0.015f / fConst8);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

inline void Dsp::compute(int count, float *input0, float *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
	float 	fSlow0 = (0.0010000000000000009f * powf(10,(0.05f * fslider0)));
	float 	fSlow1 = (0.0010000000000000009f * powf(10,(0.05f * fslider1)));
	float 	fSlow2 = (fConst14 * fslider2);
	int 	iSlow3 = int(fSlow2);
	int 	iSlow4 = int((iSlow3 & 131071));
	int 	iSlow5 = (1 + iSlow3);
	float 	fSlow6 = (iSlow5 - fSlow2);
	int 	iSlow7 = int((int(iSlow5) & 131071));
	float 	fSlow8 = (fSlow2 - iSlow3);
	float 	fSlow9 = (0.0010000000000000009f * powf(10,(0.05f * fslider3)));
	for (int i=0; i<count; i++) {
		fRec3[0] = (fSlow0 + (0.999f * fRec3[1]));
		fRec5[0] = (fSlow1 + (0.999f * fRec5[1]));
		fRec9[0] = ((fConst10 * (fRec8[1] + fRec8[2])) + (fConst9 * fRec9[1]));
		fRec8[0] = (Ftube(TUBE_TABLE_12AX7_68k, (((float)input0[i] + fRec9[0]) - 1.83f)) - 182.22222222222223f);
		fRec7[0] = ((fConst12 * ((fConst11 * fRec8[1]) + (fConst4 * fRec8[0]))) + (fConst6 * fRec7[1]));
		fRec6[0] = ((fConst13 * (fRec7[0] + fRec7[1])) + (fConst3 * fRec6[1]));
		float fTemp0 = (fRec6[0] + (fRec5[0] * fRec4[1]));
		fVec0[IOTA&131071] = fTemp0;
		fRec10[0] = (fSlow9 + (0.999f * fRec10[1]));
		fRec4[0] = (fVec0[IOTA&131071] + (fRec10[0] * ((fSlow8 * fVec0[(IOTA-iSlow7)&131071]) + (fSlow6 * fVec0[(IOTA-iSlow4)&131071]))));
		fRec11[0] = ((fConst15 * (fRec2[1] + fRec2[2])) + (fConst9 * fRec11[1]));
		fRec2[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec11[0] + (fRec4[0] * fRec3[0])) - 1.3f)) - 163.33333333333331f);
		fRec1[0] = ((fConst12 * ((fConst11 * fRec2[1]) + (fConst4 * fRec2[0]))) + (fConst6 * fRec1[1]));
		fRec0[0] = ((fConst13 * (fRec1[0] + fRec1[1])) + (fConst3 * fRec0[1]));
		output0[i] = (FAUSTFLOAT)(0.35481338923357547f * fRec0[0]);
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec11[1] = fRec11[0];
		fRec4[1] = fRec4[0];
		fRec10[1] = fRec10[0];
		IOTA = IOTA+1;
		fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec5[1] = fRec5[0];
		fRec3[1] = fRec3[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
}

void Dsp::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case LEVEL: 
		fslider3_ = (float*)data; // , -4e+01f, -4e+01f, 0.0f, 0.1f 
		break;
	case DELAY: 
		fslider2_ = (float*)data; // , 0.0f, 0.0f, 2e+03f, 1e+01f 
		break;
	case FEEDBACK: 
		fslider1_ = (float*)data; // , 0.0f, -4e+01f, 0.0f, 0.1f 
		break;
	case GAIN: 
		fslider0_ = (float*)data; // , 0.0f, -3e+01f, 6.0f, 0.1f 
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

extern "C" __attribute__ ((visibility ("default"))) int
get_gx_plugin(unsigned int idx, PluginLV2 **pplugin)
{
    if (!pplugin) {
        return 1;
    }
    if (idx > 0) {
        return -1;
    }
    *pplugin = new Dsp();
    return 1;
}
} // end namespace tubedelay
