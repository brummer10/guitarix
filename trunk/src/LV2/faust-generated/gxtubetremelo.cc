// generated from file '../src/LV2/faust/gxtubetremelo.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "valve.h"

namespace gxtubetremelo {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst2;
	int 	iRec6[2];
	int 	iRec5[2];
	double 	fConst3;
	double 	fRec9[2];
	double 	fRec8[2];
	double 	fRec7[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec4[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec10[2];
	double 	fVec1[2];
	double 	fRec14[2];
	double 	fRec13[3];
	double 	fVec2[2];
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fRec15[2];
	double 	fRec12[2];
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fRec11[2];
	double 	fVec3[2];
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fVec4[2];
	double 	fRec16[2];
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
	for (int i=0; i<2; i++) iRec6[i] = 0;
	for (int i=0; i<2; i++) iRec5[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
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
	fConst1 = (1.0 / double(iConst0));
	fConst2 = (0.5 * iConst0);
	fConst3 = (6.283185307179586 / double(iConst0));
	fConst4 = (1.0 / tan((6.5973445725385655 / double(iConst0))));
	fConst5 = (1 + fConst4);
	fConst6 = (1.0 / fConst5);
	fConst7 = (0 - ((1 - fConst4) / fConst5));
	fConst8 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst9 = (0 - fConst8);
	fConst10 = (1 + fConst8);
	fConst11 = (0.025 / fConst10);
	fConst12 = (0 - ((1 - fConst8) / fConst10));
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fcheckbox0 (*fcheckbox0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	double 	fSlow0 = double(fslider0);
	int 	iSlow1 = int((fConst2 / double(fSlow0)));
	double 	fSlow2 = (1.0 / double(iSlow1));
	double 	fSlow3 = (fConst3 * fSlow0);
	int 	iSlow4 = int(double(fcheckbox0));
	double 	fSlow5 = double(fslider1);
	double 	fSlow6 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider2))));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		double fTemp0 = (fRec4[1] * (1 - (fConst1 / (fConst1 + (0.06 * exp((0 - (2.4849066497880004 * fRec4[1]))))))));
		iRec6[0] = ((int((iRec6[1] > 0)))?((2 * (iRec5[1] < iSlow1)) - 1):(1 - (2 * (iRec5[1] > 0))));
		iRec5[0] = (iRec6[0] + iRec5[1]);
		fRec9[0] = (fRec9[1] + (fSlow3 * (0 - fRec7[1])));
		fRec8[0] = ((1 + (fRec8[1] + (fSlow3 * fRec9[0]))) - iVec0[1]);
		fRec7[0] = fRec8[0];
		fRec4[0] = (fTemp0 + (fConst1 * (pow((1 + (fSlow5 * (((iSlow4)?max((double)0, (0.5 * (1 + fRec7[0]))):(fSlow2 * iRec5[0])) - 1))),1.9) / (fConst1 + (0.06 * exp((0 - (2.4849066497880004 * fTemp0))))))));
		fRec10[0] = ((0.999 * fRec10[1]) + fSlow6);
		double fTemp1 = ((double)input0[i] + 1e-15);
		fVec1[0] = fTemp1;
		fRec14[0] = ((0.9302847925323914 * (fVec1[0] + fVec1[1])) - (0.8605695850647829 * fRec14[1]));
		fRec13[0] = (fRec14[0] - ((1.8405051250752198 * fRec13[1]) + (0.8612942439318627 * fRec13[2])));
		double fTemp2 = (1e-15 + (0.015 * fRec12[1]));
		fVec2[0] = fTemp2;
		fRec15[0] = ((fConst7 * fRec15[1]) + (fConst6 * (fVec2[0] + fVec2[1])));
		fRec12[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec15[0] + (0.9254498422517706 * (fRec13[2] + (fRec13[0] + (2.0 * fRec13[1]))))) - 1.204541)) - 169.69726666666665);
		fRec11[0] = ((fConst12 * fRec11[1]) + (fConst11 * ((fConst8 * fRec12[0]) + (fConst9 * fRec12[1]))));
		double fTemp3 = (1e-15 + (2700 * ((fRec11[0] * fRec10[0]) / (2700 + exp((13.815510557964274 / log((2.718281828459045 + (8.551967507929417 * fRec4[0])))))))));
		fVec3[0] = fTemp3;
		fRec3[0] = ((0.9302847925323914 * (fVec3[0] + fVec3[1])) - (0.8605695850647829 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.8612942439318627 * fRec2[2])));
		double fTemp4 = (1e-15 + (0.015 * fRec1[1]));
		fVec4[0] = fTemp4;
		fRec16[0] = ((fConst7 * fRec16[1]) + (fConst6 * (fVec4[0] + fVec4[1])));
		fRec1[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec16[0] + (0.9254498422517706 * (fRec2[2] + (fRec2[0] + (2.0 * fRec2[1]))))) - 1.204285)) - 169.71433333333334);
		fRec0[0] = ((fConst12 * fRec0[1]) + (fConst11 * ((fConst8 * fRec1[0]) + (fConst9 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec16[1] = fRec16[0];
		fVec4[1] = fVec4[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fVec3[1] = fVec3[0];
		fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fRec15[1] = fRec15[0];
		fVec2[1] = fVec2[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fVec1[1] = fVec1[0];
		fRec10[1] = fRec10[0];
		fRec4[1] = fRec4[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		iRec5[1] = iRec5[0];
		iRec6[1] = iRec6[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fcheckbox0
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
	case GAIN: 
		fslider2_ = (float*)data; // , 0.0, -12.0, 12.0, 0.1 
		break;
	// static const value_pair fcheckbox0_values[] = {{"triangle"},{"sine"},{0}};
	case SINEWAVE: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case DEPTH: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case SPEED: 
		fslider0_ = (float*)data; // , 5.0, 0.1, 2e+01, 0.1 
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
   SINEWAVE, 
   DEPTH, 
   SPEED, 
} PortIndex;
*/

} // end namespace gxtubetremelo
