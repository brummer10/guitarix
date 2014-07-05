// generated from file '../src/LV2/faust/gx_chump.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "valve.h"

namespace gx_chump {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec3[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	double 	fVec0[2];
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fConst12;
	double 	fRec13[2];
	double 	fRec12[3];
	double 	fConst13;
	double 	fVec1[2];
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fRec17[2];
	double 	fRec16[2];
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fRec15[2];
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fRec14[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fRec18[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec19[2];
	double 	fVec2[2];
	double 	fRec9[2];
	double 	fVec3[2];
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fRec20[2];
	double 	fRec8[2];
	double 	fRec7[2];
	double 	fVec4[2];
	double 	fRec6[2];
	double 	fVec5[2];
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fRec21[2];
	double 	fRec5[2];
	double 	fRec4[2];
	double 	fVec6[2];
	double 	fRec2[2];
	double 	fConst40;
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
	id = "Redeye Chump";
	name = N_("Redeye Chumo");
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
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
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
	fConst1 = tan((20517.741620594938 / double(iConst0)));
	fConst2 = (1.0 / faustpower<2>(fConst1));
	fConst3 = (2 * (1 - fConst2));
	fConst4 = (1.0 / fConst1);
	fConst5 = (1 + ((fConst4 - 1.0000000000000004) / fConst1));
	fConst6 = (1 + ((1.0000000000000004 + fConst4) / fConst1));
	fConst7 = (1.0 / fConst6);
	fConst8 = (0 - fConst4);
	fConst9 = (1 + fConst4);
	fConst10 = (1.0 / fConst9);
	fConst11 = (0 - ((1 - fConst4) / fConst9));
	fConst12 = (2 * (0 - fConst2));
	fConst13 = (0.5 / fConst6);
	fConst14 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst15 = (1 + fConst14);
	fConst16 = (1.0 / fConst15);
	fConst17 = (0 - ((1 - fConst14) / fConst15));
	fConst18 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst19 = (0 - fConst18);
	fConst20 = (1 + fConst18);
	fConst21 = (0.025 / fConst20);
	fConst22 = (0 - ((1 - fConst18) / fConst20));
	fConst23 = (1.0 / tan((1281.7698026646356 / double(iConst0))));
	fConst24 = (1 + fConst23);
	fConst25 = (1.0 / fConst24);
	fConst26 = (0 - ((1 - fConst23) / fConst24));
	fConst27 = (1.0 / tan((5830.795965062656 / double(iConst0))));
	fConst28 = (0 - fConst27);
	fConst29 = (1 + fConst27);
	fConst30 = (1.0 / fConst29);
	fConst31 = (0 - ((1 - fConst27) / fConst29));
	fConst32 = (1.0 / tan((314.1592653589793 / double(iConst0))));
	fConst33 = (1 + fConst32);
	fConst34 = (1.0 / fConst33);
	fConst35 = (0 - ((1 - fConst32) / fConst33));
	fConst36 = (1.0 / tan((376.99111843077515 / double(iConst0))));
	fConst37 = (1 + fConst36);
	fConst38 = (1.0 / fConst37);
	fConst39 = (0 - ((1 - fConst36) / fConst37));
	fConst40 = (0 - fConst36);
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
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider0))));
	double 	fSlow1 = double(fcheckbox0);
	double 	fSlow2 = (fConst4 * fSlow1);
	double 	fSlow3 = double(fslider1);
	double 	fSlow4 = (1 - fSlow3);
	double 	fSlow5 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider2))));
	for (int i=0; i<count; i++) {
		fRec3[0] = ((0.999 * fRec3[1]) + fSlow0);
		double fTemp0 = (fSlow1 * fRec0[1]);
		fVec0[0] = fTemp0;
		fRec11[0] = ((fConst11 * fRec11[1]) + (fConst10 * ((fSlow2 * fRec0[1]) + (fConst8 * fVec0[1]))));
		fRec10[0] = (fRec11[0] - (fConst7 * ((fConst5 * fRec10[2]) + (fConst3 * fRec10[1]))));
		fRec13[0] = ((fConst11 * fRec13[1]) + (fConst10 * (fVec0[0] + fVec0[1])));
		fRec12[0] = (fRec13[0] - (fConst7 * ((fConst5 * fRec12[2]) + (fConst3 * fRec12[1]))));
		double fTemp1 = (1e-15 + (0.027 * fRec16[1]));
		fVec1[0] = fTemp1;
		fRec17[0] = ((fConst17 * fRec17[1]) + (fConst16 * (fVec1[0] + fVec1[1])));
		fRec16[0] = (Ftube(TUBE_TABLE_12AX7_68k, (((double)input0[i] + fRec17[0]) - 1.5816559999999988)) - 191.42014814814814);
		fRec15[0] = ((fConst22 * fRec15[1]) + (fConst21 * ((fConst18 * fRec16[0]) + (fConst19 * fRec16[1]))));
		fRec14[0] = ((fConst26 * fRec14[1]) + (fConst25 * (fRec15[0] + fRec15[1])));
		fRec18[0] = ((fConst31 * fRec18[1]) + (fConst30 * ((fConst27 * fRec15[0]) + (fConst28 * fRec15[1]))));
		fRec19[0] = ((0.999 * fRec19[1]) + fSlow5);
		double fTemp2 = ((fRec19[0] * ((fSlow3 * fRec18[0]) + (fSlow4 * fRec14[0]))) - (fConst13 * ((fRec12[2] + (fRec12[0] + (2 * fRec12[1]))) + (1.4125375446227544 * (((fConst2 * fRec10[0]) + (fConst12 * fRec10[1])) + (fConst2 * fRec10[2]))))));
		fVec2[0] = fTemp2;
		fRec9[0] = ((fConst11 * fRec9[1]) + (fConst10 * (fVec2[0] + fVec2[1])));
		double fTemp3 = (1e-15 + (0.015 * fRec8[1]));
		fVec3[0] = fTemp3;
		fRec20[0] = ((fConst35 * fRec20[1]) + (fConst34 * (fVec3[0] + fVec3[1])));
		fRec8[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec20[0] + fRec9[0]) - 1.204284999999999)) - 169.71433333333334);
		fRec7[0] = ((fConst22 * fRec7[1]) + (fConst21 * ((fConst18 * fRec8[0]) + (fConst19 * fRec8[1]))));
		double fTemp4 = (fRec7[0] * fRec3[0]);
		fVec4[0] = fTemp4;
		fRec6[0] = ((fConst11 * fRec6[1]) + (fConst10 * (fVec4[0] + fVec4[1])));
		double fTemp5 = (1e-15 + (0.0082 * fRec5[1]));
		fVec5[0] = fTemp5;
		fRec21[0] = ((fConst39 * fRec21[1]) + (fConst38 * (fVec5[0] + fVec5[1])));
		fRec5[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec21[0] + fRec6[0]) - 1.130461999999999)) - 112.13878048780487);
		fRec4[0] = ((fConst22 * fRec4[1]) + (fConst21 * ((fConst18 * fRec5[0]) + (fConst19 * fRec5[1]))));
		double fTemp6 = (fRec4[0] * (1 - (0.05 * fRec3[0])));
		fVec6[0] = fTemp6;
		fRec2[0] = ((fConst11 * fRec2[1]) + (fConst10 * (fVec6[0] + fVec6[1])));
		fRec1[0] = ((fConst39 * fRec1[1]) + (fConst38 * ((fConst36 * fRec2[0]) + (fConst40 * fRec2[1]))));
		fRec0[0] = fRec1[0];
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fVec6[1] = fVec6[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec21[1] = fRec21[0];
		fVec5[1] = fVec5[0];
		fRec6[1] = fRec6[0];
		fVec4[1] = fVec4[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec20[1] = fRec20[0];
		fVec3[1] = fVec3[0];
		fRec9[1] = fRec9[0];
		fVec2[1] = fVec2[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fVec1[1] = fVec1[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec0[1] = fVec0[0];
		fRec3[1] = fRec3[0];
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
		fslider2_ = (float*)data; // , 0.0, -2e+01, 2e+01, 0.1 
		break;
	case VOLUME: 
		fslider0_ = (float*)data; // , 0.0, -2e+01, 1e+01, 0.1 
		break;
	case FEEDBACK: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case TONE: 
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
   GAIN, 
   VOLUME, 
   FEEDBACK, 
   TONE, 
} PortIndex;
*/

} // end namespace gx_chump
