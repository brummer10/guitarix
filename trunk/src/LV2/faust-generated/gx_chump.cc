// generated from file '../src/LV2/faust/gx_chump.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)

#include "valve.h"

namespace gx_chump {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec3[2];
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	double 	fVec0[2];
	double 	fConst16;
	double 	fConst17;
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fVec1[2];
	double 	fConst26;
	double 	fRec15[2];
	double 	fRec14[2];
	double 	fConst27;
	double 	fConst28;
	double 	fRec13[2];
	double 	fConst29;
	double 	fConst30;
	double 	fRec12[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fRec16[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec17[2];
	double 	fVec2[2];
	double 	fRec9[2];
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fVec3[2];
	double 	fConst38;
	double 	fRec18[2];
	double 	fRec8[2];
	double 	fRec7[2];
	double 	fVec4[2];
	double 	fRec6[2];
	double 	fVec5[2];
	double 	fConst39;
	double 	fRec19[2];
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
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
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
	fConst1 = (1.0 / tan((376.99111843077515 / iConst0)));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = tan((20517.741620594938 / iConst0));
	fConst5 = (1.0 / fConst4);
	fConst6 = (1 + fConst5);
	fConst7 = (0 - ((1 - fConst5) / fConst6));
	fConst8 = (1.0 / tan((97.38937226128358 / iConst0)));
	fConst9 = (1 + fConst8);
	fConst10 = (0 - ((1 - fConst8) / fConst9));
	fConst11 = (1.0 / faustpower<2>(fConst4));
	fConst12 = (2 * (1 - fConst11));
	fConst13 = (1 + ((fConst5 - 1.0000000000000004) / fConst4));
	fConst14 = (1 + ((fConst5 + 1.0000000000000004) / fConst4));
	fConst15 = (1.0 / fConst14);
	fConst16 = (0 - fConst5);
	fConst17 = (1.0 / fConst6);
	fConst18 = (2 * (0 - fConst11));
	fConst19 = (0.4125375446227544 / fConst14);
	fConst20 = (1.0 / tan((5830.795965062656 / iConst0)));
	fConst21 = (1 + fConst20);
	fConst22 = (0 - ((1 - fConst20) / fConst21));
	fConst23 = (1.0 / tan((270.1769682087222 / iConst0)));
	fConst24 = (1 + fConst23);
	fConst25 = (0 - ((1 - fConst23) / fConst24));
	fConst26 = (1.0 / fConst24);
	fConst27 = (0 - fConst8);
	fConst28 = (0.025 / fConst9);
	fConst29 = (0 - fConst20);
	fConst30 = (1.0 / fConst21);
	fConst31 = (1.0 / tan((1281.7698026646356 / iConst0)));
	fConst32 = (1 + fConst31);
	fConst33 = (0 - ((1 - fConst31) / fConst32));
	fConst34 = (1.0 / fConst32);
	fConst35 = (1.0 / tan((314.1592653589793 / iConst0)));
	fConst36 = (1 + fConst35);
	fConst37 = (0 - ((1 - fConst35) / fConst36));
	fConst38 = (1.0 / fConst36);
	fConst39 = (1.0 / fConst2);
	fConst40 = (0 - fConst1);
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
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = fcheckbox0;
	double 	fSlow2 = (fConst5 * fSlow1);
	double 	fSlow3 = fslider1;
	double 	fSlow4 = (1 - fSlow3);
	double 	fSlow5 = (0.0010000000000000009 * pow(10,(0.05 * fslider2)));
	for (int i=0; i<count; i++) {
		fRec3[0] = (fSlow0 + (0.999 * fRec3[1]));
		double fTemp0 = (fSlow1 * fRec0[1]);
		fVec0[0] = fTemp0;
		fRec11[0] = ((fConst17 * ((fConst16 * fVec0[1]) + (fSlow2 * fRec0[1]))) + (fConst7 * fRec11[1]));
		fRec10[0] = (fRec11[0] - (fConst15 * ((fConst13 * fRec10[2]) + (fConst12 * fRec10[1]))));
		double fTemp1 = (1e-15 + (0.027 * fRec14[1]));
		fVec1[0] = fTemp1;
		fRec15[0] = ((fConst26 * (fVec1[0] + fVec1[1])) + (fConst25 * fRec15[1]));
		fRec14[0] = (Ftube(TUBE_TABLE_12AX7_68k, (((double)input0[i] + fRec15[0]) - 1.5816559999999988)) - 191.42014814814814);
		fRec13[0] = ((fConst28 * ((fConst27 * fRec14[1]) + (fConst8 * fRec14[0]))) + (fConst10 * fRec13[1]));
		fRec12[0] = ((fConst30 * ((fConst29 * fRec13[1]) + (fConst20 * fRec13[0]))) + (fConst22 * fRec12[1]));
		fRec16[0] = ((fConst34 * (fRec13[0] + fRec13[1])) + (fConst33 * fRec16[1]));
		fRec17[0] = (fSlow5 + (0.999 * fRec17[1]));
		double fTemp2 = ((fRec17[0] * ((fSlow4 * fRec16[0]) + (fSlow3 * fRec12[0]))) - (0.5 * (fVec0[0] + (fConst19 * (((fConst11 * fRec10[0]) + (fConst18 * fRec10[1])) + (fConst11 * fRec10[2]))))));
		fVec2[0] = fTemp2;
		fRec9[0] = ((fConst17 * (fVec2[0] + fVec2[1])) + (fConst7 * fRec9[1]));
		double fTemp3 = (1e-15 + (0.015 * fRec8[1]));
		fVec3[0] = fTemp3;
		fRec18[0] = ((fConst38 * (fVec3[0] + fVec3[1])) + (fConst37 * fRec18[1]));
		fRec8[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec18[0] + fRec9[0]) - 1.204284999999999)) - 169.71433333333334);
		fRec7[0] = ((fConst28 * ((fConst27 * fRec8[1]) + (fConst8 * fRec8[0]))) + (fConst10 * fRec7[1]));
		double fTemp4 = (fRec7[0] * fRec3[0]);
		fVec4[0] = fTemp4;
		fRec6[0] = ((fConst17 * (fVec4[0] + fVec4[1])) + (fConst7 * fRec6[1]));
		double fTemp5 = (1e-15 + (0.0082 * fRec5[1]));
		fVec5[0] = fTemp5;
		fRec19[0] = ((fConst39 * (fVec5[0] + fVec5[1])) + (fConst3 * fRec19[1]));
		fRec5[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec19[0] + fRec6[0]) - 1.130461999999999)) - 112.13878048780487);
		fRec4[0] = ((fConst28 * ((fConst27 * fRec5[1]) + (fConst8 * fRec5[0]))) + (fConst10 * fRec4[1]));
		double fTemp6 = (fRec4[0] * (1 - (0.05 * fRec3[0])));
		fVec6[0] = fTemp6;
		fRec2[0] = ((fConst17 * (fVec6[0] + fVec6[1])) + (fConst7 * fRec2[1]));
		fRec1[0] = ((fConst39 * ((fConst40 * fRec2[1]) + (fConst1 * fRec2[0]))) + (fConst3 * fRec1[1]));
		fRec0[0] = fRec1[0];
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fVec6[1] = fVec6[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec19[1] = fRec19[0];
		fVec5[1] = fVec5[0];
		fRec6[1] = fRec6[0];
		fVec4[1] = fVec4[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec18[1] = fRec18[0];
		fVec3[1] = fVec3[0];
		fRec9[1] = fRec9[0];
		fVec2[1] = fVec2[0];
		fRec17[1] = fRec17[0];
		fRec16[1] = fRec16[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec1[1] = fVec1[0];
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

void Dsp::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case FEEDBACK: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case GAIN: 
		fslider2_ = (float*)data; // , 0.0, -2e+01, 2e+01, 0.1 
		break;
	case TONE: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fslider0_ = (float*)data; // , 0.0, -2e+01, 1e+01, 0.1 
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
   FEEDBACK, 
   GAIN, 
   TONE, 
   VOLUME, 
} PortIndex;
*/

} // end namespace gx_chump
