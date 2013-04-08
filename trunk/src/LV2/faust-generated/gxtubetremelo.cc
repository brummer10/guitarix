// generated from file '../src/LV2/faust/gxtubetremelo.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)

#include "valve.h"

namespace gxtubetremelo {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst5;
	int 	iRec4[2];
	int 	iRec3[2];
	double 	fConst6;
	double 	fRec7[2];
	double 	fRec6[2];
	double 	fRec5[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec2[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec8[2];
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fVec1[2];
	double 	fConst10;
	double 	fRec11[2];
	double 	fRec10[2];
	double 	fConst11;
	double 	fConst12;
	double 	fRec9[2];
	double 	fVec2[2];
	double 	fRec12[2];
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
	id = "gxtubetremelo";
	name = N_("Tube Tremolo");
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) iRec4[i] = 0;
	for (int i=0; i<2; i++) iRec3[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
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
	fConst4 = (1.0 / iConst0);
	fConst5 = (0.5 * iConst0);
	fConst6 = (6.283185307179586 / iConst0);
	fConst7 = (1.0 / tan((6.5973445725385655 / iConst0)));
	fConst8 = (1 + fConst7);
	fConst9 = (0 - ((1 - fConst7) / fConst8));
	fConst10 = (1.0 / fConst8);
	fConst11 = (0 - fConst1);
	fConst12 = (0.025 / fConst2);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

inline void Dsp::compute(int count, float *input0, float *output0)
{
#define fslider0 (*fslider0_)
#define fcheckbox0 (*fcheckbox0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	double 	fSlow0 = fslider0;
	int 	iSlow1 = int((fConst5 / double(fSlow0)));
	double 	fSlow2 = (1.0 / iSlow1);
	double 	fSlow3 = (fConst6 * fSlow0);
	int 	iSlow4 = int(fcheckbox0);
	double 	fSlow5 = fslider1;
	double 	fSlow6 = (0.0010000000000000009 * pow(10,(0.05 * fslider2)));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		double fTemp0 = (fRec2[1] * (1 - (fConst4 / (fConst4 + (0.06 * exp((0 - (2.4849066497880004 * fRec2[1]))))))));
		iRec4[0] = ((int((iRec4[1] > 0)))?((2 * (iRec3[1] < iSlow1)) - 1):(1 - (2 * (iRec3[1] > 0))));
		iRec3[0] = (iRec4[0] + iRec3[1]);
		fRec7[0] = ((fSlow3 * (0 - fRec5[1])) + fRec7[1]);
		fRec6[0] = ((1 + ((fSlow3 * fRec7[0]) + fRec6[1])) - iVec0[1]);
		fRec5[0] = fRec6[0];
		fRec2[0] = (fTemp0 + (fConst4 * (pow((1 + (fSlow5 * (((iSlow4)?max(0, (0.5 * (1 + fRec5[0]))):(fSlow2 * iRec3[0])) - 1))),1.9) / (fConst4 + (0.06 * exp((0 - (2.4849066497880004 * fTemp0))))))));
		fRec8[0] = (fSlow6 + (0.999 * fRec8[1]));
		double fTemp1 = (1e-15 + (0.015 * fRec10[1]));
		fVec1[0] = fTemp1;
		fRec11[0] = ((fConst10 * (fVec1[0] + fVec1[1])) + (fConst9 * fRec11[1]));
		fRec10[0] = (Ftube(TUBE_TABLE_12AX7_68k, (((double)input0[i] + fRec11[0]) - 1.204540999999999)) - 169.69726666666665);
		fRec9[0] = ((fConst12 * ((fConst11 * fRec10[1]) + (fConst1 * fRec10[0]))) + (fConst3 * fRec9[1]));
		double fTemp2 = (1e-15 + (0.015 * fRec1[1]));
		fVec2[0] = fTemp2;
		fRec12[0] = ((fConst10 * (fVec2[0] + fVec2[1])) + (fConst9 * fRec12[1]));
		fRec1[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec12[0] + (2700 * ((fRec9[0] * fRec8[0]) / (2700 + exp((13.815510557964274 / log((2.718281828459045 + (8.551967507929417 * fRec2[0]))))))))) - 1.204284999999999)) - 169.71433333333334);
		fRec0[0] = ((fConst12 * ((fConst11 * fRec1[1]) + (fConst1 * fRec1[0]))) + (fConst3 * fRec0[1]));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec12[1] = fRec12[0];
		fVec2[1] = fVec2[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec1[1] = fVec1[0];
		fRec8[1] = fRec8[0];
		fRec2[1] = fRec2[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		iRec3[1] = iRec3[0];
		iRec4[1] = iRec4[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fcheckbox0
#undef fslider1
#undef fslider2
}

void Dsp::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case SPEED: 
		fslider0_ = (float*)data; // , 5.0, 0.1, 2e+01, 0.1 
		break;
	case GAIN: 
		fslider2_ = (float*)data; // , 0.0, -12.0, 12.0, 0.1 
		break;
	case DEPTH: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	// static const value_pair fcheckbox0_values[] = {{"triangle"},{"sine"},{0}};
	case SINEWAVE: 
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
   SPEED, 
   GAIN, 
   DEPTH, 
   SINEWAVE, 
} PortIndex;
*/

} // end namespace gxtubetremelo
