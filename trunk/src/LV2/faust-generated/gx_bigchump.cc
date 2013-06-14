// generated from file '../src/LV2/faust/gx_bigchump.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)

#include "valve.h"

namespace gx_bigchump {

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
	double 	fConst8;
	double 	fConst9;
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec5[2];
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fVec0[2];
	double 	fConst19;
	double 	fRec12[2];
	double 	fRec11[2];
	double 	fConst20;
	double 	fConst21;
	double 	fRec10[2];
	double 	fConst22;
	double 	fConst23;
	double 	fRec9[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fRec13[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec14[2];
	double 	fVec1[2];
	double 	fConst28;
	double 	fRec8[2];
	double 	fVec2[2];
	double 	fRec15[2];
	double 	fRec7[2];
	double 	fRec6[2];
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fVec3[2];
	double 	fConst32;
	double 	fRec16[2];
	double 	fRec4[2];
	double 	fRec3[2];
	double 	fConst33;
	double 	fRec2[2];
	double 	fConst34;
	double 	fConst35;
	double 	fRec1[2];
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fVec4[2];
	double 	fRec21[2];
	double 	fRec20[2];
	double 	fRec19[2];
	double 	fConst42;
	double 	fRec18[2];
	double 	fConst43;
	double 	fConst44;
	double 	fRec17[2];
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
	id = "gx_bigchump";
	name = N_("Redeye Big Chump");
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
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
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
	fConst1 = (1.0 / tan((263.89378290154264 / double(iConst0))));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0 / tan((25368.36067773758 / double(iConst0))));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst8 = (1 + fConst7);
	fConst9 = (0 - ((1 - fConst7) / fConst8));
	fConst10 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst11 = (1 + fConst10);
	fConst12 = (0 - ((1 - fConst10) / fConst11));
	fConst13 = (1.0 / tan((5830.795965062656 / double(iConst0))));
	fConst14 = (1 + fConst13);
	fConst15 = (0 - ((1 - fConst13) / fConst14));
	fConst16 = (1.0 / tan((125.66370614359172 / double(iConst0))));
	fConst17 = (1 + fConst16);
	fConst18 = (0 - ((1 - fConst16) / fConst17));
	fConst19 = (1.0 / fConst17);
	fConst20 = (0 - fConst7);
	fConst21 = (0.025 / fConst8);
	fConst22 = (0 - fConst13);
	fConst23 = (1.0 / fConst14);
	fConst24 = (1.0 / tan((1281.7698026646356 / double(iConst0))));
	fConst25 = (1 + fConst24);
	fConst26 = (0 - ((1 - fConst24) / fConst25));
	fConst27 = (1.0 / fConst25);
	fConst28 = (1.0 / fConst11);
	fConst29 = (1.0 / tan((188.49555921538757 / double(iConst0))));
	fConst30 = (1 + fConst29);
	fConst31 = (0 - ((1 - fConst29) / fConst30));
	fConst32 = (1.0 / fConst30);
	fConst33 = (1.0 / fConst5);
	fConst34 = (0 - fConst1);
	fConst35 = (1.0 / fConst2);
	fConst36 = (1.0 / tan((238.76104167282426 / double(iConst0))));
	fConst37 = (1 + fConst36);
	fConst38 = (0 - ((1 - fConst36) / fConst37));
	fConst39 = (1.0 / tan((28038.714433288904 / double(iConst0))));
	fConst40 = (1 + fConst39);
	fConst41 = (0 - ((1 - fConst39) / fConst40));
	fConst42 = (1.0 / fConst40);
	fConst43 = (0 - fConst36);
	fConst44 = (1.0 / fConst37);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, float *input0, float *output0)
{
#define fcheckbox0 (*fcheckbox0_)
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	double 	fSlow0 = (0.5 * fcheckbox0);
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow2 = fslider1;
	double 	fSlow3 = (1 - fSlow2);
	double 	fSlow4 = (0.0010000000000000009 * pow(10,(0.05 * fslider2)));
	for (int i=0; i<count; i++) {
		fRec5[0] = (fSlow1 + (0.999 * fRec5[1]));
		double fTemp0 = (1e-15 + (0.027 * fRec11[1]));
		fVec0[0] = fTemp0;
		fRec12[0] = ((fConst19 * (fVec0[0] + fVec0[1])) + (fConst18 * fRec12[1]));
		fRec11[0] = (Ftube(TUBE_TABLE_12AX7_68k, (((double)input0[i] + fRec12[0]) - 1.829999999999999)) - 182.22222222222223);
		fRec10[0] = ((fConst21 * ((fConst20 * fRec11[1]) + (fConst7 * fRec11[0]))) + (fConst9 * fRec10[1]));
		fRec9[0] = ((fConst23 * ((fConst22 * fRec10[1]) + (fConst13 * fRec10[0]))) + (fConst15 * fRec9[1]));
		fRec13[0] = ((fConst27 * (fRec10[0] + fRec10[1])) + (fConst26 * fRec13[1]));
		fRec14[0] = (fSlow4 + (0.999 * fRec14[1]));
		double fTemp1 = (fRec14[0] * ((fSlow3 * fRec13[0]) + (fSlow2 * fRec9[0])));
		fVec1[0] = fTemp1;
		fRec8[0] = ((fConst28 * (fVec1[0] + fVec1[1])) + (fConst12 * fRec8[1]));
		double fTemp2 = (1e-15 + (0.027 * fRec7[1]));
		fVec2[0] = fTemp2;
		fRec15[0] = ((fConst19 * (fVec2[0] + fVec2[1])) + (fConst18 * fRec15[1]));
		fRec7[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec15[0] + fRec8[0]) - 1.829999999999999)) - 182.22222222222223);
		fRec6[0] = ((fConst21 * ((fConst20 * fRec7[1]) + (fConst7 * fRec7[0]))) + (fConst9 * fRec6[1]));
		double fTemp3 = ((fRec6[0] * fRec5[0]) + (fSlow0 * fRec0[1]));
		double fTemp4 = (1e-15 + (0.00822 * fRec4[1]));
		fVec3[0] = fTemp4;
		fRec16[0] = ((fConst32 * (fVec3[0] + fVec3[1])) + (fConst31 * fRec16[1]));
		fRec4[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec16[0] + (fTemp3 * (fTemp3 >= 0.0))) - 1.130461999999999)) - 112.47420924574209);
		fRec3[0] = ((fConst21 * ((fConst20 * fRec4[1]) + (fConst7 * fRec4[0]))) + (fConst9 * fRec3[1]));
		fRec2[0] = ((fConst33 * (fRec3[0] + fRec3[1])) + (fConst6 * fRec2[1]));
		fRec1[0] = ((fConst35 * ((fConst34 * fRec2[1]) + (fConst1 * fRec2[0]))) + (fConst3 * fRec1[1]));
		double fTemp5 = (1e-15 + (0.00818 * fRec20[1]));
		fVec4[0] = fTemp5;
		fRec21[0] = ((fConst32 * (fVec4[0] + fVec4[1])) + (fConst31 * fRec21[1]));
		fRec20[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec21[0] + (fTemp3 * (fTemp3 <= 0.0))) - 1.130461999999999)) - 111.80171149144252);
		fRec19[0] = ((fConst21 * ((fConst20 * fRec20[1]) + (fConst7 * fRec20[0]))) + (fConst9 * fRec19[1]));
		fRec18[0] = ((fConst42 * (fRec19[0] + fRec19[1])) + (fConst41 * fRec18[1]));
		fRec17[0] = ((fConst44 * ((fConst43 * fRec18[1]) + (fConst36 * fRec18[0]))) + (fConst38 * fRec17[1]));
		fRec0[0] = (fRec17[0] + (0.98 * fRec1[0]));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fVec4[1] = fVec4[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec16[1] = fRec16[0];
		fVec3[1] = fVec3[0];
		fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec15[1] = fRec15[0];
		fVec2[1] = fVec2[0];
		fRec8[1] = fRec8[0];
		fVec1[1] = fVec1[0];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fVec0[1] = fVec0[0];
		fRec5[1] = fRec5[0];
	}
#undef fcheckbox0
#undef fslider0
#undef fslider1
#undef fslider2
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
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
		fslider2_ = (float*)data; // , 0.0, -24.0, 1e+01, 0.1 
		break;
	case TONE: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fslider0_ = (float*)data; // , 0.0, -24.0, 6.0, 0.1 
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

} // end namespace gx_bigchump
