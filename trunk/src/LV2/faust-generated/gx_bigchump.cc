// generated from file '../src/LV2/faust/gx_bigchump.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)

#include "valve.h"

namespace gx_bigchump {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec7[2];
	double 	fVec0[2];
	double 	fRec17[2];
	double 	fRec16[3];
	double 	fVec1[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fRec18[2];
	double 	fRec15[2];
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fRec14[2];
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fRec13[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fRec19[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec20[2];
	double 	fVec2[2];
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fRec12[2];
	double 	fVec3[2];
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fVec4[2];
	double 	fRec21[2];
	double 	fRec9[2];
	double 	fRec8[2];
	double 	fVec5[2];
	double 	fRec6[2];
	double 	fRec5[3];
	double 	fVec6[2];
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fRec22[2];
	double 	fRec4[2];
	double 	fRec3[2];
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fRec2[2];
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fRec1[2];
	double 	fVec7[2];
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fVec8[2];
	double 	fRec29[2];
	double 	fRec26[2];
	double 	fRec25[2];
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fRec24[2];
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fRec23[2];
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
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
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
	fConst1 = (1.0 / tan((125.66370614359172 / double(iConst0))));
	fConst2 = (1 + fConst1);
	fConst3 = (1.0 / fConst2);
	fConst4 = (0 - ((1 - fConst1) / fConst2));
	fConst5 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst6 = (0 - fConst5);
	fConst7 = (1 + fConst5);
	fConst8 = (0.025 / fConst7);
	fConst9 = (0 - ((1 - fConst5) / fConst7));
	fConst10 = (1.0 / tan((1281.7698026646356 / double(iConst0))));
	fConst11 = (1 + fConst10);
	fConst12 = (1.0 / fConst11);
	fConst13 = (0 - ((1 - fConst10) / fConst11));
	fConst14 = (1.0 / tan((5830.795965062656 / double(iConst0))));
	fConst15 = (0 - fConst14);
	fConst16 = (1 + fConst14);
	fConst17 = (1.0 / fConst16);
	fConst18 = (0 - ((1 - fConst14) / fConst16));
	fConst19 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst20 = (1 + fConst19);
	fConst21 = (1.0 / fConst20);
	fConst22 = (0 - ((1 - fConst19) / fConst20));
	fConst23 = (1.0 / tan((188.49555921538757 / double(iConst0))));
	fConst24 = (1 + fConst23);
	fConst25 = (1.0 / fConst24);
	fConst26 = (0 - ((1 - fConst23) / fConst24));
	fConst27 = (1.0 / tan((25368.36067773758 / double(iConst0))));
	fConst28 = (1 + fConst27);
	fConst29 = (1.0 / fConst28);
	fConst30 = (0 - ((1 - fConst27) / fConst28));
	fConst31 = (1.0 / tan((263.89378290154264 / double(iConst0))));
	fConst32 = (0 - fConst31);
	fConst33 = (1 + fConst31);
	fConst34 = (1.0 / fConst33);
	fConst35 = (0 - ((1 - fConst31) / fConst33));
	fConst36 = (1.0 / tan((28038.714433288904 / double(iConst0))));
	fConst37 = (1 + fConst36);
	fConst38 = (1.0 / fConst37);
	fConst39 = (0 - ((1 - fConst36) / fConst37));
	fConst40 = (1.0 / tan((238.76104167282426 / double(iConst0))));
	fConst41 = (0 - fConst40);
	fConst42 = (1 + fConst40);
	fConst43 = (1.0 / fConst42);
	fConst44 = (0 - ((1 - fConst40) / fConst42));
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fcheckbox0 (*fcheckbox0_)
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	double 	fSlow0 = (0.5 * double(fcheckbox0));
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider0))));
	double 	fSlow2 = double(fslider1);
	double 	fSlow3 = (1 - fSlow2);
	double 	fSlow4 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider2))));
	for (int i=0; i<count; i++) {
		fRec7[0] = ((0.999 * fRec7[1]) + fSlow1);
		double fTemp0 = ((double)input0[i] + 1e-15);
		fVec0[0] = fTemp0;
		fRec17[0] = ((0.9302847925323914 * (fVec0[0] + fVec0[1])) - (0.8605695850647829 * fRec17[1]));
		fRec16[0] = (fRec17[0] - ((1.8405051250752198 * fRec16[1]) + (0.8612942439318627 * fRec16[2])));
		double fTemp1 = (1e-15 + (0.027 * fRec15[1]));
		fVec1[0] = fTemp1;
		fRec18[0] = ((fConst4 * fRec18[1]) + (fConst3 * (fVec1[0] + fVec1[1])));
		fRec15[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec18[0] + (0.9254498422517706 * (fRec16[2] + (fRec16[0] + (2.0 * fRec16[1]))))) - 1.83)) - 182.22222222222223);
		fRec14[0] = ((fConst9 * fRec14[1]) + (fConst8 * ((fConst5 * fRec15[0]) + (fConst6 * fRec15[1]))));
		fRec13[0] = ((fConst13 * fRec13[1]) + (fConst12 * (fRec14[0] + fRec14[1])));
		fRec19[0] = ((fConst18 * fRec19[1]) + (fConst17 * ((fConst14 * fRec14[0]) + (fConst15 * fRec14[1]))));
		fRec20[0] = ((0.999 * fRec20[1]) + fSlow4);
		double fTemp2 = (fRec20[0] * ((fSlow2 * fRec19[0]) + (fSlow3 * fRec13[0])));
		fVec2[0] = fTemp2;
		fRec12[0] = ((fConst22 * fRec12[1]) + (fConst21 * (fVec2[0] + fVec2[1])));
		double fTemp3 = (1e-15 + fRec12[0]);
		fVec3[0] = fTemp3;
		fRec11[0] = ((0.9302847925323914 * (fVec3[0] + fVec3[1])) - (0.8605695850647829 * fRec11[1]));
		fRec10[0] = (fRec11[0] - ((1.8405051250752198 * fRec10[1]) + (0.8612942439318627 * fRec10[2])));
		double fTemp4 = (1e-15 + (0.027 * fRec9[1]));
		fVec4[0] = fTemp4;
		fRec21[0] = ((fConst4 * fRec21[1]) + (fConst3 * (fVec4[0] + fVec4[1])));
		fRec9[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec21[0] + (0.9254498422517706 * (fRec10[2] + (fRec10[0] + (2.0 * fRec10[1]))))) - 1.83)) - 182.22222222222223);
		fRec8[0] = ((fConst9 * fRec8[1]) + (fConst8 * ((fConst5 * fRec9[0]) + (fConst6 * fRec9[1]))));
		double fTemp5 = ((fRec8[0] * fRec7[0]) + (fSlow0 * fRec0[1]));
		double fTemp6 = (1e-15 + (fTemp5 * (fTemp5 >= 0.0)));
		fVec5[0] = fTemp6;
		fRec6[0] = ((0.9302847925323914 * (fVec5[0] + fVec5[1])) - (0.8605695850647829 * fRec6[1]));
		fRec5[0] = (fRec6[0] - ((1.8405051250752198 * fRec5[1]) + (0.8612942439318627 * fRec5[2])));
		double fTemp7 = (1e-15 + (0.00822 * fRec4[1]));
		fVec6[0] = fTemp7;
		fRec22[0] = ((fConst26 * fRec22[1]) + (fConst25 * (fVec6[0] + fVec6[1])));
		fRec4[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec22[0] + (0.9254498422517706 * (fRec5[2] + (fRec5[0] + (2.0 * fRec5[1]))))) - 1.130462)) - 112.47420924574209);
		fRec3[0] = ((fConst9 * fRec3[1]) + (fConst8 * ((fConst5 * fRec4[0]) + (fConst6 * fRec4[1]))));
		fRec2[0] = ((fConst30 * fRec2[1]) + (fConst29 * (fRec3[0] + fRec3[1])));
		fRec1[0] = ((fConst35 * fRec1[1]) + (fConst34 * ((fConst31 * fRec2[0]) + (fConst32 * fRec2[1]))));
		double fTemp8 = (1e-15 + (fTemp5 * (fTemp5 <= 0.0)));
		fVec7[0] = fTemp8;
		fRec28[0] = ((0.9302847925323914 * (fVec7[1] + fVec7[0])) - (0.8605695850647829 * fRec28[1]));
		fRec27[0] = (fRec28[0] - ((1.8405051250752198 * fRec27[1]) + (0.8612942439318627 * fRec27[2])));
		double fTemp9 = (1e-15 + (0.00818 * fRec26[1]));
		fVec8[0] = fTemp9;
		fRec29[0] = ((fConst26 * fRec29[1]) + (fConst25 * (fVec8[0] + fVec8[1])));
		fRec26[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec29[0] + (0.9254498422517706 * (fRec27[2] + (fRec27[0] + (2.0 * fRec27[1]))))) - 1.130462)) - 111.80171149144252);
		fRec25[0] = ((fConst9 * fRec25[1]) + (fConst8 * ((fConst5 * fRec26[0]) + (fConst6 * fRec26[1]))));
		fRec24[0] = ((fConst39 * fRec24[1]) + (fConst38 * (fRec25[0] + fRec25[1])));
		fRec23[0] = ((fConst44 * fRec23[1]) + (fConst43 * ((fConst40 * fRec24[0]) + (fConst41 * fRec24[1]))));
		fRec0[0] = (fRec23[0] + (0.98 * fRec1[0]));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fRec29[1] = fRec29[0];
		fVec8[1] = fVec8[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fVec7[1] = fVec7[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec22[1] = fRec22[0];
		fVec6[1] = fVec6[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fVec5[1] = fVec5[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec21[1] = fRec21[0];
		fVec4[1] = fVec4[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec3[1] = fVec3[0];
		fRec12[1] = fRec12[0];
		fVec2[1] = fVec2[0];
		fRec20[1] = fRec20[0];
		fRec19[1] = fRec19[0];
		fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec18[1] = fRec18[0];
		fVec1[1] = fVec1[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fVec0[1] = fVec0[0];
		fRec7[1] = fRec7[0];
	}
#undef fcheckbox0
#undef fslider0
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
		fslider2_ = (float*)data; // , 0.0, -24.0, 1e+01, 0.1 
		break;
	case VOLUME: 
		fslider0_ = (float*)data; // , 0.0, -24.0, 6.0, 0.1 
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

} // end namespace gx_bigchump
