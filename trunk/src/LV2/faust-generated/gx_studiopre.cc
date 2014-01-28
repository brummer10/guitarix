// generated from file '../src/LV2/faust/gx_studiopre.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "valve.h"

namespace gx_studiopre {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fVec0[2];
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fRec6[2];
	double 	fRec5[2];
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fRec4[2];
	double 	fRec3[4];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	double 	fVec1[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst13;
	double 	fRec2[2];
	double 	fVec2[2];
	double 	fRec7[2];
	double 	fRec1[2];
	double 	fRec0[2];
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
	fConst1 = (2 * double(iConst0));
	fConst2 = faustpower<2>(fConst1);
	fConst3 = (3 * fConst1);
	fConst4 = (1.0 / tan((6.5973445725385655 / double(iConst0))));
	fConst5 = (1 + fConst4);
	fConst6 = (1.0 / fConst5);
	fConst7 = (0 - ((1 - fConst4) / fConst5));
	fConst8 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst9 = (0 - fConst8);
	fConst10 = (1 + fConst8);
	fConst11 = (0.025 / fConst10);
	fConst12 = (0 - ((1 - fConst8) / fConst10));
	fConst13 = (41887.90204786391 / double(iConst0));
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
#define fcheckbox0 (*fcheckbox0_)
#define fslider3 (*fslider3_)
	double 	fSlow0 = exp((3.4 * (double(fslider0) - 1)));
	double 	fSlow1 = double(fslider1);
	double 	fSlow2 = (4.7117500000000004e-07 * fSlow1);
	double 	fSlow3 = (((fSlow1 * (((1.1779375000000001e-05 * fSlow0) - 4.199450000000001e-06) - fSlow2)) + (0.00011998125000000002 * fSlow0)) + 5.718000000000001e-06);
	double 	fSlow4 = (7.343750000000001e-09 * fSlow0);
	double 	fSlow5 = ((1.0281250000000001e-09 * fSlow0) - (4.1125e-11 * fSlow1));
	double 	fSlow6 = (2.9375e-10 + ((fSlow1 * (fSlow5 - 2.52625e-10)) + fSlow4));
	double 	fSlow7 = (fConst1 * fSlow6);
	double 	fSlow8 = (0.0250625 * fSlow0);
	double 	fSlow9 = (0.00047000000000000004 * fSlow1);
	double 	fSlow10 = (fConst1 * (0.015765 + (fSlow9 + fSlow8)));
	double 	fSlow11 = ((fSlow10 + (fConst2 * (fSlow7 - fSlow3))) - 1);
	double 	fSlow12 = (fConst3 * fSlow6);
	double 	fSlow13 = ((fSlow10 + (fConst2 * (fSlow3 - fSlow12))) - 3);
	double 	fSlow14 = ((fConst2 * (fSlow3 + fSlow12)) - (3 + fSlow10));
	double 	fSlow15 = (0 - (1 + (fSlow10 + (fConst2 * (fSlow3 + fSlow7)))));
	double 	fSlow16 = (1.0 / fSlow15);
	double 	fSlow17 = double(fslider2);
	double 	fSlow18 = ((((9.187500000000001e-07 * fSlow17) + (fSlow1 * (5.0055e-07 - fSlow2))) + (fSlow0 * (2.48125e-06 + (1.1779375000000001e-05 * fSlow1)))) + 9.925e-08);
	double 	fSlow19 = ((fSlow1 * (4.1125e-11 + fSlow5)) + (fSlow17 * (fSlow4 + (2.9375e-10 - (2.9375e-10 * fSlow1)))));
	double 	fSlow20 = (fConst1 * fSlow19);
	double 	fSlow21 = ((fSlow8 + (fSlow9 + (6.25e-05 * fSlow17))) + 0.0010025);
	double 	fSlow22 = (fConst1 * fSlow21);
	double 	fSlow23 = (fSlow22 + (fConst2 * (fSlow20 - fSlow18)));
	double 	fSlow24 = (fConst3 * fSlow19);
	double 	fSlow25 = (fSlow22 + (fConst2 * (fSlow18 - fSlow24)));
	double 	fSlow26 = (fConst1 * (0 - fSlow21));
	double 	fSlow27 = (fSlow26 - (fConst2 * (fSlow18 + fSlow20)));
	double 	fSlow28 = (fSlow26 + (fConst2 * (fSlow18 + fSlow24)));
	double 	fSlow29 = double(fcheckbox0);
	double 	fSlow30 = (fSlow29 / fSlow15);
	double 	fSlow31 = double(fslider3);
	double 	fSlow32 = tan((fConst13 / (1.0 + fSlow31)));
	double 	fSlow33 = (1.0 / fSlow32);
	double 	fSlow34 = (0 - fSlow33);
	double 	fSlow35 = (fSlow29 / (fSlow32 * fSlow15));
	double 	fSlow36 = (1 + fSlow33);
	double 	fSlow37 = (1.0 / fSlow36);
	double 	fSlow38 = (0 - ((1 - fSlow33) / fSlow36));
	double 	fSlow39 = (0.1 * (fSlow31 / fSlow15));
	for (int i=0; i<count; i++) {
		double fTemp0 = (1e-15 + (0.015 * fRec5[1]));
		fVec0[0] = fTemp0;
		fRec6[0] = ((fConst7 * fRec6[1]) + (fConst6 * (fVec0[0] + fVec0[1])));
		fRec5[0] = (Ftube(TUBE_TABLE_12AX7_68k, (((double)input0[i] + fRec6[0]) - 1.204540999999999)) - 169.69726666666665);
		fRec4[0] = ((fConst12 * fRec4[1]) + (fConst11 * ((fConst8 * fRec5[0]) + (fConst9 * fRec5[1]))));
		fRec3[0] = ((10 * fRec4[0]) - (fSlow16 * (((fSlow14 * fRec3[1]) + (fSlow13 * fRec3[2])) + (fSlow11 * fRec3[3]))));
		double fTemp1 = (((fSlow28 * fRec3[1]) + ((fSlow27 * fRec3[0]) + (fSlow25 * fRec3[2]))) + (fSlow23 * fRec3[3]));
		fVec1[0] = (fSlow30 * fTemp1);
		fRec2[0] = ((fSlow38 * fRec2[1]) + (fSlow37 * ((fSlow35 * fTemp1) + (fSlow34 * fVec1[1]))));
		double fTemp2 = (1e-15 + (0.015 * fRec1[1]));
		fVec2[0] = fTemp2;
		fRec7[0] = ((fConst7 * fRec7[1]) + (fConst6 * (fVec2[0] + fVec2[1])));
		fRec1[0] = (Ftube(TUBE_TABLE_12AX7_250k, (((fSlow39 * fTemp1) + (fRec7[0] + fRec2[0])) - 1.204284999999999)) - 169.71433333333334);
		fRec0[0] = ((fConst12 * fRec0[1]) + (fConst11 * ((fConst8 * fRec1[0]) + (fConst9 * fRec1[1]))));
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
#undef fcheckbox0
#undef fslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case BASS_L: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case MIDDLE_L: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TREBLE_L: 
		fslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME_L: 
		fslider3_ = (float*)data; // , 5.0, 0.0, 1e+01, 0.1 
		break;
	case BRIGHT_L: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
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
   BASS_L, 
   MIDDLE_L, 
   TREBLE_L, 
   VOLUME_L, 
   BRIGHT_L, 
} PortIndex;
*/

} // end namespace gx_studiopre
