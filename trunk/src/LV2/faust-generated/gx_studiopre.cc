// generated from file '../src/LV2/faust/gx_studiopre.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)

#include "valve.h"

namespace gx_studiopre {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst4;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fVec0[2];
	double 	fConst11;
	double 	fRec6[2];
	double 	fRec5[2];
	double 	fConst12;
	double 	fConst13;
	double 	fRec4[2];
	double 	fRec3[4];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	double 	fVec1[2];
	double 	fRec2[2];
	double 	fVec2[2];
	double 	fRec7[2];
	double 	fRec1[2];
	double 	fRec0[2];
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
	id = "gx_studiopre";
	name = "?gx_studiopre";
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
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<4; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / tan((97.38937226128358 / iConst0)));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (41887.90204786391 / iConst0);
	fConst5 = (2 * double(iConst0));
	fConst6 = faustpower<2>(fConst5);
	fConst7 = (3 * fConst5);
	fConst8 = (1.0 / tan((6.5973445725385655 / iConst0)));
	fConst9 = (1 + fConst8);
	fConst10 = (0 - ((1 - fConst8) / fConst9));
	fConst11 = (1.0 / fConst9);
	fConst12 = (0 - fConst1);
	fConst13 = (0.025 / fConst2);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

inline void Dsp::compute(int count, float *input0, float *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
#define fcheckbox0 (*fcheckbox0_)
	double 	fSlow0 = fslider0;
	double 	fSlow1 = tan((fConst4 / (1.0 + fSlow0)));
	double 	fSlow2 = (1.0 / fSlow1);
	double 	fSlow3 = (1 + fSlow2);
	double 	fSlow4 = (0 - ((1 - fSlow2) / fSlow3));
	double 	fSlow5 = fslider1;
	double 	fSlow6 = (4.7117500000000004e-07 * fSlow5);
	double 	fSlow7 = exp((3.4 * (fslider2 - 1)));
	double 	fSlow8 = (5.718000000000001e-06 + ((0.00011998125000000002 * fSlow7) + (fSlow5 * (((1.1779375000000001e-05 * fSlow7) - 4.199450000000001e-06) - fSlow6))));
	double 	fSlow9 = ((1.0281250000000001e-09 * fSlow7) - (4.1125e-11 * fSlow5));
	double 	fSlow10 = (7.343750000000001e-09 * fSlow7);
	double 	fSlow11 = (2.9375e-10 + (fSlow10 + (fSlow5 * (fSlow9 - 2.52625e-10))));
	double 	fSlow12 = (fConst5 * fSlow11);
	double 	fSlow13 = (0.00047000000000000004 * fSlow5);
	double 	fSlow14 = (0.0250625 * fSlow7);
	double 	fSlow15 = (fConst5 * (0.015765 + (fSlow14 + fSlow13)));
	double 	fSlow16 = ((fSlow15 + (fConst6 * (fSlow12 - fSlow8))) - 1);
	double 	fSlow17 = (fConst7 * fSlow11);
	double 	fSlow18 = ((fConst6 * (fSlow8 + fSlow17)) - (3 + fSlow15));
	double 	fSlow19 = ((fSlow15 + (fConst6 * (fSlow8 - fSlow17))) - 3);
	double 	fSlow20 = (0 - (1 + (fSlow15 + (fConst6 * (fSlow8 + fSlow12)))));
	double 	fSlow21 = (1.0 / fSlow20);
	double 	fSlow22 = fslider3;
	double 	fSlow23 = ((fSlow5 * (4.1125e-11 + fSlow9)) + (fSlow22 * (fSlow10 + (2.9375e-10 - (2.9375e-10 * fSlow5)))));
	double 	fSlow24 = (fConst7 * fSlow23);
	double 	fSlow25 = (9.925e-08 + (((9.187500000000001e-07 * fSlow22) + (fSlow5 * (5.0055e-07 - fSlow6))) + (fSlow7 * (2.48125e-06 + (1.1779375000000001e-05 * fSlow5)))));
	double 	fSlow26 = (0.0010025 + (fSlow14 + (fSlow13 + (6.25e-05 * fSlow22))));
	double 	fSlow27 = (fConst5 * fSlow26);
	double 	fSlow28 = (fSlow27 + (fConst6 * (fSlow25 - fSlow24)));
	double 	fSlow29 = (fConst5 * fSlow23);
	double 	fSlow30 = (fSlow27 + (fConst6 * (fSlow29 - fSlow25)));
	double 	fSlow31 = (fConst5 * (0 - fSlow26));
	double 	fSlow32 = (fSlow31 + (fConst6 * (fSlow25 + fSlow24)));
	double 	fSlow33 = (fSlow31 - (fConst6 * (fSlow25 + fSlow29)));
	double 	fSlow34 = fcheckbox0;
	double 	fSlow35 = (fSlow34 / (fSlow1 * fSlow20));
	double 	fSlow36 = (fSlow34 / fSlow20);
	double 	fSlow37 = (0 - fSlow2);
	double 	fSlow38 = (1.0 / fSlow3);
	double 	fSlow39 = (0.1 * (fSlow0 / fSlow20));
	for (int i=0; i<count; i++) {
		double fTemp0 = (1e-15 + (0.015 * fRec5[1]));
		fVec0[0] = fTemp0;
		fRec6[0] = ((fConst11 * (fVec0[0] + fVec0[1])) + (fConst10 * fRec6[1]));
		fRec5[0] = (Ftube(TUBE_TABLE_12AX7_68k, (((double)input0[i] + fRec6[0]) - 1.204540999999999)) - 169.69726666666665);
		fRec4[0] = ((fConst13 * ((fConst12 * fRec5[1]) + (fConst1 * fRec5[0]))) + (fConst3 * fRec4[1]));
		fRec3[0] = ((10 * fRec4[0]) - (fSlow21 * (((fSlow19 * fRec3[2]) + (fSlow18 * fRec3[1])) + (fSlow16 * fRec3[3]))));
		double fTemp1 = ((fSlow33 * fRec3[0]) + ((fSlow32 * fRec3[1]) + ((fSlow30 * fRec3[3]) + (fSlow28 * fRec3[2]))));
		fVec1[0] = (fSlow36 * fTemp1);
		fRec2[0] = ((fSlow38 * ((fSlow37 * fVec1[1]) + (fSlow35 * fTemp1))) + (fSlow4 * fRec2[1]));
		double fTemp2 = (1e-15 + (0.015 * fRec1[1]));
		fVec2[0] = fTemp2;
		fRec7[0] = ((fConst11 * (fVec2[0] + fVec2[1])) + (fConst10 * fRec7[1]));
		fRec1[0] = (Ftube(TUBE_TABLE_12AX7_250k, (((fSlow39 * fTemp1) + (fRec7[0] + fRec2[0])) - 1.204284999999999)) - 169.71433333333334);
		fRec0[0] = ((fConst13 * ((fConst12 * fRec1[1]) + (fConst1 * fRec1[0]))) + (fConst3 * fRec0[1]));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec7[1] = fRec7[0];
		fVec2[1] = fVec2[0];
		fRec2[1] = fRec2[0];
		fVec1[1] = fVec1[0];
		for (int i=3; i>0; i--) fRec3[i] = fRec3[i-1];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fVec0[1] = fVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fcheckbox0
}

void Dsp::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case BRIGHT_L: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case TREBLE_L: 
		fslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case BASS_L: 
		fslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case MIDDLE_L: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME_L: 
		fslider0_ = (float*)data; // , 5.0, 0.0, 1e+01, 0.1 
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
   BRIGHT_L, 
   TREBLE_L, 
   BASS_L, 
   MIDDLE_L, 
   VOLUME_L, 
} PortIndex;
*/

} // end namespace gx_studiopre
