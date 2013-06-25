// generated from file '../src/LV2/faust/gxmetal_amp.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)

#include "valve.h"

namespace gxmetal_amp {

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
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec6[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec13[2];
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fVec0[2];
	double 	fConst13;
	double 	fRec16[2];
	double 	fRec15[2];
	double 	fConst14;
	double 	fConst15;
	double 	fRec14[2];
	double 	fVec1[2];
	double 	fConst16;
	double 	fRec12[2];
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fVec2[2];
	double 	fConst20;
	double 	fRec17[2];
	double 	fRec11[2];
	double 	fRec10[2];
	double 	fRec9[2];
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fVec3[2];
	double 	fConst24;
	double 	fRec18[2];
	double 	fRec8[2];
	double 	fRec7[2];
	double 	fRec5[4];
	double 	fConst25;
	double 	fConst26;
	double 	fRec4[2];
	double 	fVec4[2];
	double 	fRec19[2];
	double 	fRec3[2];
	double 	fRec2[2];
	double 	fVec5[2];
	double 	fRec22[2];
	double 	fRec21[2];
	double 	fRec20[2];
	double 	fVec6[2];
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
	id = "metal";
	name = N_("GxMetal_head");
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
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<4; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
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
	fConst1 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = (2 * double(iConst0));
	fConst8 = faustpower<2>(fConst7);
	fConst9 = (3 * fConst7);
	fConst10 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst11 = (1 + fConst10);
	fConst12 = (0 - ((1 - fConst10) / fConst11));
	fConst13 = (1.0 / fConst11);
	fConst14 = (0 - fConst4);
	fConst15 = (0.025 / fConst5);
	fConst16 = (1.0 / fConst2);
	fConst17 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst18 = (1 + fConst17);
	fConst19 = (0 - ((1 - fConst17) / fConst18));
	fConst20 = (1.0 / fConst18);
	fConst21 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst22 = (1 + fConst21);
	fConst23 = (0 - ((1 - fConst21) / fConst22));
	fConst24 = (1.0 / fConst22);
	fConst25 = exp((0 - (2e+02 / double(iConst0))));
	fConst26 = exp((0 - (0.1 / double(iConst0))));
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
#define fslider3 (*fslider3_)
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * (0 - (0.4 * fSlow0)))));
	double 	fSlow2 = fslider1;
	double 	fSlow3 = exp((3.4 * (0 - fSlow2)));
	double 	fSlow4 = ((3.1361660000000006e-05 * fSlow3) + 6.993481000000001e-07);
	double 	fSlow5 = ((5.967937800000002e-09 * fSlow3) + 2.9839689000000005e-11);
	double 	fSlow6 = (fConst7 * fSlow5);
	double 	fSlow7 = (0.022470000000000004 * fSlow3);
	double 	fSlow8 = (fConst7 * (fSlow7 + 0.0026376999999999998));
	double 	fSlow9 = ((fSlow8 + (fConst8 * (fSlow6 - fSlow4))) - 1);
	double 	fSlow10 = (fConst9 * fSlow5);
	double 	fSlow11 = ((fConst8 * (fSlow4 + fSlow10)) - (3 + fSlow8));
	double 	fSlow12 = ((fSlow8 + (fConst8 * (fSlow4 - fSlow10))) - 3);
	double 	fSlow13 = (1.0 / (0 - (1 + (fSlow8 + (fConst8 * (fSlow4 + fSlow6))))));
	double 	fSlow14 = (0.0010000000000000009 * pow(10,(0.05 * fslider2)));
	double 	fSlow15 = (0.0010000000000000009 * pow(10,(0.05 * fslider3)));
	double 	fSlow16 = (fSlow0 - 1);
	double 	fSlow17 = (3.1107890000000005e-12 + ((6.221578000000002e-10 * fSlow3) + (fSlow2 * ((5.345780000000001e-09 * fSlow3) + 2.6728900000000006e-11))));
	double 	fSlow18 = (fConst9 * fSlow17);
	double 	fSlow19 = (((4.859800000000001e-07 * fSlow2) + (8.613660000000003e-06 * fSlow3)) + 9.962810000000002e-08);
	double 	fSlow20 = ((fSlow7 + (0.00023500000000000002 * fSlow2)) + 0.0003347);
	double 	fSlow21 = (fConst7 * fSlow20);
	double 	fSlow22 = (fSlow21 + (fConst8 * (fSlow19 - fSlow18)));
	double 	fSlow23 = (fConst7 * fSlow17);
	double 	fSlow24 = (fSlow21 + (fConst8 * (fSlow23 - fSlow19)));
	double 	fSlow25 = (fConst7 * (0 - fSlow20));
	double 	fSlow26 = (fSlow25 + (fConst8 * (fSlow19 + fSlow18)));
	double 	fSlow27 = (fSlow25 - (fConst8 * (fSlow19 + fSlow23)));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow1 + (0.999 * fRec0[1]));
		fRec6[0] = (fSlow14 + (0.999 * fRec6[1]));
		fRec13[0] = (fSlow15 + (0.999 * fRec13[1]));
		double fTemp0 = (double)input0[i];
		double fTemp1 = fabs(fTemp0);
		double fTemp2 = (1e-15 + (0.027 * fRec15[1]));
		fVec0[0] = fTemp2;
		fRec16[0] = ((fConst13 * (fVec0[0] + fVec0[1])) + (fConst12 * fRec16[1]));
		fRec15[0] = (Ftube(TUBE_TABLE_12AY7_68k, ((fRec16[0] + ((fTemp0 * (fSlow0 + fTemp1)) / (1 + ((fSlow16 * fTemp1) + faustpower<2>(fTemp0))))) - 2.775057999999999)) - 147.2200740740741);
		fRec14[0] = ((fConst15 * ((fConst14 * fRec15[1]) + (fConst4 * fRec15[0]))) + (fConst6 * fRec14[1]));
		double fTemp3 = (fRec14[0] * fRec13[0]);
		fVec1[0] = fTemp3;
		fRec12[0] = ((fConst16 * (fVec1[0] + fVec1[1])) + (fConst3 * fRec12[1]));
		double fTemp4 = (1e-15 + (0.015 * fRec11[1]));
		fVec2[0] = fTemp4;
		fRec17[0] = ((fConst20 * (fVec2[0] + fVec2[1])) + (fConst19 * fRec17[1]));
		fRec11[0] = (Ftube(TUBE_TABLE_12AY7_250k, ((fRec17[0] + fRec12[0]) - 1.9543079999999988)) - 119.71279999999999);
		fRec10[0] = ((fConst15 * ((fConst14 * fRec11[1]) + (fConst4 * fRec11[0]))) + (fConst6 * fRec10[1]));
		fRec9[0] = ((fConst16 * (fRec10[0] + fRec10[1])) + (fConst3 * fRec9[1]));
		double fTemp5 = (1e-15 + (0.0082 * fRec8[1]));
		fVec3[0] = fTemp5;
		fRec18[0] = ((fConst24 * (fVec3[0] + fVec3[1])) + (fConst23 * fRec18[1]));
		fRec8[0] = (Ftube(TUBE_TABLE_12AY7_250k, ((fRec18[0] + fRec9[0]) - 1.2649159999999988)) - 95.7419512195122);
		fRec7[0] = ((fConst15 * ((fConst14 * fRec8[1]) + (fConst4 * fRec8[0]))) + (fConst6 * fRec7[1]));
		fRec5[0] = ((fRec7[0] * fRec6[0]) - (fSlow13 * (((fSlow12 * fRec5[2]) + (fSlow11 * fRec5[1])) + (fSlow9 * fRec5[3]))));
		double fTemp6 = ((fSlow27 * fRec5[0]) + ((fSlow26 * fRec5[1]) + ((fSlow24 * fRec5[3]) + (fSlow22 * fRec5[2]))));
		double fTemp7 = max((double)1, fabs((fSlow13 * fTemp6)));
		double fTemp8 = ((fConst26 * (fRec4[1] >= fTemp7)) + (fConst25 * (fRec4[1] < fTemp7)));
		fRec4[0] = ((fTemp7 * (0 - (fTemp8 - 1))) + (fRec4[1] * fTemp8));
		double fTemp9 = max((double)0, ((20 * log10(fRec4[0])) + 5e+01));
		double fTemp10 = (0.5 * min((double)1, max((double)0, (0.09522902580706599 * fTemp9))));
		double fTemp11 = (fSlow13 * (fTemp6 * pow(10,(0.05 * (1e+01 + ((fTemp9 * (0 - fTemp10)) / (1 + fTemp10)))))));
		double fTemp12 = (1e-15 + (0.0082 * fRec3[1]));
		fVec4[0] = fTemp12;
		fRec19[0] = ((fConst16 * (fVec4[0] + fVec4[1])) + (fConst3 * fRec19[1]));
		fRec3[0] = (Ftube(TUBE_TABLE_EL34_250k, ((fRec19[0] + fTemp11) - 0.964749999999999)) - 132.34756097560975);
		fRec2[0] = ((fConst15 * ((fConst14 * fRec3[1]) + (fConst4 * fRec3[0]))) + (fConst6 * fRec2[1]));
		double fTemp13 = (1e-15 + (0.0082 * fRec21[1]));
		fVec5[0] = fTemp13;
		fRec22[0] = ((fConst16 * (fVec5[0] + fVec5[1])) + (fConst3 * fRec22[1]));
		fRec21[0] = (Ftube(TUBE_TABLE_EL34_68k, ((fRec22[0] + fTemp11) - 0.965916999999999)) - 132.205243902439);
		fRec20[0] = ((fConst15 * ((fConst14 * fRec21[1]) + (fConst4 * fRec21[0]))) + (fConst6 * fRec20[1]));
		double fTemp14 = (fRec20[0] + fRec2[0]);
		fVec6[0] = fTemp14;
		fRec1[0] = ((fConst16 * (fVec6[0] + fVec6[1])) + (fConst3 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fVec6[1] = fVec6[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fVec5[1] = fVec5[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec19[1] = fRec19[0];
		fVec4[1] = fVec4[0];
		fRec4[1] = fRec4[0];
		for (int i=3; i>0; i--) fRec5[i] = fRec5[i-1];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec18[1] = fRec18[0];
		fVec3[1] = fVec3[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec17[1] = fRec17[0];
		fVec2[1] = fVec2[0];
		fRec12[1] = fRec12[0];
		fVec1[1] = fVec1[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fVec0[1] = fVec0[0];
		fRec13[1] = fRec13[0];
		fRec6[1] = fRec6[0];
		fRec0[1] = fRec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case PREGAIN: 
		fslider3_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
		break;
	case GAIN1: 
		fslider2_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
		break;
	case TONE: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case DRIVE: 
		fslider0_ = (float*)data; // , 1.0, 1.0, 2e+01, 0.1 
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
   PREGAIN, 
   GAIN1, 
   TONE, 
   DRIVE, 
} PortIndex;
*/

} // end namespace gxmetal_amp
