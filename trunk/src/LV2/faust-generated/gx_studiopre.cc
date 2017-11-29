// generated from file '../src/LV2/faust/gx_studiopre.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#include "valve.h"

namespace gx_studiopre {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fVec0[2];
	double 	fRec8[2];
	double 	fRec7[3];
	double 	fVec1[2];
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fRec9[2];
	double 	fRec6[2];
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fRec5[2];
	double 	fRec4[4];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	double 	fVec2[2];
	double 	fConst14;
	double 	fRec10[2];
	double 	fVec3[2];
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fVec4[2];
	double 	fRec11[2];
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
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<4; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
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
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = double(fConst0);
	fConst2 = (2 * fConst1);
	fConst3 = faustpower<2>(fConst2);
	fConst4 = (6 * fConst1);
	fConst5 = (1.0 / tan((6.5973445725385655 / fConst0)));
	fConst6 = (1 + fConst5);
	fConst7 = (1.0 / fConst6);
	fConst8 = (0 - ((1 - fConst5) / fConst6));
	fConst9 = (1.0 / tan((97.38937226128358 / fConst0)));
	fConst10 = (0 - fConst9);
	fConst11 = (1 + fConst9);
	fConst12 = (0.025 / fConst11);
	fConst13 = (0 - ((1 - fConst9) / fConst11));
	fConst14 = (41887.90204786391 / fConst0);
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
#define fslider3 (*fslider3_)
#define fcheckbox0 (*fcheckbox0_)
	double 	fSlow0 = double(fslider0);
	double 	fSlow1 = (4.7117500000000004e-07 * fSlow0);
	double 	fSlow2 = exp((3.4 * (double(fslider1) - 1)));
	double 	fSlow3 = ((0.00011998125000000002 * fSlow2) + (fSlow0 * ((1.1779375000000001e-05 * fSlow2) - (4.199450000000001e-06 + fSlow1))));
	double 	fSlow4 = (5.718000000000001e-06 + fSlow3);
	double 	fSlow5 = (4.1125e-11 * fSlow0);
	double 	fSlow6 = (1.0281250000000001e-09 * fSlow2);
	double 	fSlow7 = (7.343750000000001e-09 * fSlow2);
	double 	fSlow8 = (2.9375e-10 + (fSlow7 + (fSlow0 * (fSlow6 - (fSlow5 + 2.52625e-10)))));
	double 	fSlow9 = (fConst2 * fSlow8);
	double 	fSlow10 = (0.0250625 * fSlow2);
	double 	fSlow11 = (0.00047000000000000004 * fSlow0);
	double 	fSlow12 = (fConst2 * (0.015765 + (fSlow11 + fSlow10)));
	double 	fSlow13 = ((fSlow12 + (fConst3 * (fSlow9 - fSlow4))) - 1);
	double 	fSlow14 = (fConst4 * fSlow8);
	double 	fSlow15 = ((fSlow12 + (fConst3 * (fSlow4 - fSlow14))) - 3);
	double 	fSlow16 = ((fConst3 * (5.718000000000001e-06 + (fSlow3 + fSlow14))) - (3 + fSlow12));
	double 	fSlow17 = (0 - (1 + (fSlow12 + (fConst3 * (5.718000000000001e-06 + (fSlow3 + fSlow9))))));
	double 	fSlow18 = (1.0 / fSlow17);
	double 	fSlow19 = double(fslider2);
	double 	fSlow20 = ((fSlow0 * ((4.1125e-11 + fSlow6) - fSlow5)) + (fSlow19 * ((2.9375e-10 + fSlow7) - (2.9375e-10 * fSlow0))));
	double 	fSlow21 = (fConst2 * fSlow20);
	double 	fSlow22 = (((9.187500000000001e-07 * fSlow19) + (fSlow0 * (5.0055e-07 - fSlow1))) + (fSlow2 * (2.48125e-06 + (1.1779375000000001e-05 * fSlow0))));
	double 	fSlow23 = (fSlow22 + 9.925e-08);
	double 	fSlow24 = ((fSlow10 + (fSlow11 + (6.25e-05 * fSlow19))) + 0.0010025);
	double 	fSlow25 = (fConst2 * fSlow24);
	double 	fSlow26 = (fSlow25 + (fConst3 * (0 - (fSlow23 - fSlow21))));
	double 	fSlow27 = (fConst4 * fSlow20);
	double 	fSlow28 = (fSlow25 + (fConst3 * (fSlow23 - fSlow27)));
	double 	fSlow29 = (fConst2 * (0 - fSlow24));
	double 	fSlow30 = (fSlow29 + (fConst3 * (9.925e-08 + (fSlow22 + fSlow27))));
	double 	fSlow31 = (fSlow29 - (fConst3 * (9.925e-08 + (fSlow22 + fSlow21))));
	double 	fSlow32 = double(fslider3);
	double 	fSlow33 = (0.1 * (fSlow32 / fSlow17));
	double 	fSlow34 = double(fcheckbox0);
	double 	fSlow35 = (fSlow34 / fSlow17);
	double 	fSlow36 = tan((fConst14 / (1.0 + fSlow32)));
	double 	fSlow37 = (1.0 / fSlow36);
	double 	fSlow38 = (0 - fSlow37);
	double 	fSlow39 = (fSlow34 / (fSlow36 * fSlow17));
	double 	fSlow40 = (1 + fSlow37);
	double 	fSlow41 = (1.0 / fSlow40);
	double 	fSlow42 = (0 - ((1 - fSlow37) / fSlow40));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = (fTemp0 + 1e-15);
		fRec8[0] = ((0.9302847925323914 * (1e-15 + (fTemp0 + fVec0[1]))) - (0.8605695850647829 * fRec8[1]));
		fRec7[0] = (fRec8[0] - ((1.8405051250752198 * fRec7[1]) + (0.8612942439318627 * fRec7[2])));
		double fTemp1 = (0.015 * fRec6[1]);
		fVec1[0] = (1e-15 + fTemp1);
		fRec9[0] = ((fConst8 * fRec9[1]) + (fConst7 * (1e-15 + (fTemp1 + fVec1[1]))));
		fRec6[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec9[0] + (0.9254498422517706 * (fRec7[0] + (fRec7[2] + (2.0 * fRec7[1]))))) - 1.204541)) - 169.69726666666665);
		fRec5[0] = ((fConst13 * fRec5[1]) + (fConst12 * ((fConst9 * fRec6[0]) + (fConst10 * fRec6[1]))));
		fRec4[0] = ((10 * fRec5[0]) - (fSlow18 * (((fSlow16 * fRec4[1]) + (fSlow15 * fRec4[2])) + (fSlow13 * fRec4[3]))));
		double fTemp2 = ((((fSlow31 * fRec4[0]) + (fSlow30 * fRec4[1])) + (fSlow28 * fRec4[2])) + (fSlow26 * fRec4[3]));
		fVec2[0] = (fSlow35 * fTemp2);
		fRec10[0] = ((fSlow42 * fRec10[1]) + (fSlow41 * ((fSlow39 * fTemp2) + (fSlow38 * fVec2[1]))));
		double fTemp3 = (fRec10[0] + (fSlow33 * fTemp2));
		fVec3[0] = (1e-15 + fTemp3);
		fRec3[0] = ((0.9302847925323914 * (1e-15 + (fTemp3 + fVec3[1]))) - (0.8605695850647829 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.8612942439318627 * fRec2[2])));
		double fTemp4 = (0.015 * fRec1[1]);
		fVec4[0] = (1e-15 + fTemp4);
		fRec11[0] = ((fConst8 * fRec11[1]) + (fConst7 * (1e-15 + (fTemp4 + fVec4[1]))));
		fRec1[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec11[0] + (0.9254498422517706 * (fRec2[0] + (fRec2[2] + (2.0 * fRec2[1]))))) - 1.204285)) - 169.71433333333334);
		fRec0[0] = ((fConst13 * fRec0[1]) + (fConst12 * ((fConst9 * fRec1[0]) + (fConst10 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec11[1] = fRec11[0];
		fVec4[1] = fVec4[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fVec3[1] = fVec3[0];
		fRec10[1] = fRec10[0];
		fVec2[1] = fVec2[0];
		for (int i=3; i>0; i--) fRec4[i] = fRec4[i-1];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec9[1] = fRec9[0];
		fVec1[1] = fVec1[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fVec0[1] = fVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fcheckbox0
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
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case MIDDLE_L: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
