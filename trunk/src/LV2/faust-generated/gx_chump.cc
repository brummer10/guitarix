// generated from file '../src/LV2/faust/gx_chump.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#include "valve.h"

namespace gx_chump {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec8[2];
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec9[2];
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fRec10[4];
	double 	fVec0[2];
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fRec7[2];
	double 	fVec1[2];
	double 	fRec6[2];
	double 	fRec5[3];
	double 	fVec2[2];
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fRec11[2];
	double 	fRec4[2];
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fRec3[2];
	double 	fConst33;
	double 	fRec2[2];
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fRec1[2];

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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<4; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
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
	fConst2 = (8.80319430128334e-15 * fConst1);
	fConst3 = ((fConst1 * (0 - (9.77412876487773e-13 + fConst2))) - 2.15618481704215e-11);
	fConst4 = (1.30755824986672e-14 * fConst1);
	fConst5 = (4.21491687148728e-11 + (fConst1 * (1.57726547438855e-12 + fConst4)));
	fConst6 = (4.16885331779473e-15 * fConst1);
	fConst7 = (3.33921266453749e-09 + (fConst1 * (2.51329500908337e-11 + fConst6)));
	fConst8 = (2.15618481704215e-11 + (fConst1 * (fConst2 - 9.77412876487773e-13)));
	fConst9 = ((fConst1 * (1.57726547438855e-12 - fConst4)) - 4.21491687148728e-11);
	fConst10 = ((fConst1 * (2.51329500908337e-11 - fConst6)) - 3.33921266453749e-09);
	fConst11 = (2.640958290385e-14 * fConst1);
	fConst12 = ((fConst1 * (9.77412876487773e-13 + fConst11)) - 2.15618481704215e-11);
	fConst13 = (3.92267474960017e-14 * fConst1);
	fConst14 = (4.21491687148728e-11 + (fConst1 * (0 - (1.57726547438855e-12 + fConst13))));
	fConst15 = (1.25065599533842e-14 * fConst1);
	fConst16 = (3.33921266453749e-09 + (fConst1 * (0 - (2.51329500908337e-11 + fConst15))));
	fConst17 = (2.15618481704215e-11 + (fConst1 * (9.77412876487773e-13 - fConst11)));
	fConst18 = ((fConst1 * (fConst13 - 1.57726547438855e-12)) - 4.21491687148728e-11);
	fConst19 = ((fConst1 * (fConst15 - 2.51329500908337e-11)) - 3.33921266453749e-09);
	fConst20 = (1.0 / tan((20517.741620594938 / fConst0)));
	fConst21 = (1 + fConst20);
	fConst22 = (0.1 * (faustpower<2>(fConst1) / fConst21));
	fConst23 = (0 - ((1 - fConst20) / fConst21));
	fConst24 = (1.0 / tan((376.99111843077515 / fConst0)));
	fConst25 = (1 + fConst24);
	fConst26 = (1.0 / fConst25);
	fConst27 = (0 - ((1 - fConst24) / fConst25));
	fConst28 = (1.0 / tan((97.38937226128358 / fConst0)));
	fConst29 = (0 - fConst28);
	fConst30 = (1 + fConst28);
	fConst31 = (0.025 / fConst30);
	fConst32 = (0 - ((1 - fConst28) / fConst30));
	fConst33 = (1.0 / fConst21);
	fConst34 = (1.0 / tan((251.32741228718345 / fConst0)));
	fConst35 = (0 - fConst34);
	fConst36 = (1 + fConst34);
	fConst37 = (1.0 / fConst36);
	fConst38 = (0 - ((1 - fConst34) / fConst36));
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
	double 	fSlow0 = (0.0010000000000000009 * double(fslider0));
	double 	fSlow1 = (0.004073836948085289 * (exp(double(fslider1)) - 1));
	double 	fSlow2 = (0.004073836948085289 * (exp(double(fslider2)) - 1));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec8[0] = (fSlow1 + (0.993 * fRec8[1]));
		double fTemp0 = (1.08009336743453e-07 + (fConst1 * (fConst7 + (fRec8[0] * (fConst5 + (fConst3 * fRec8[0]))))));
		fRec9[0] = (fSlow2 + (0.993 * fRec9[1]));
		double fTemp1 = (7.37587395491694e-09 * fRec9[0]);
		fRec10[0] = ((double)input0[i] - ((((fRec10[2] * (3.24028010230359e-07 + (fConst1 * (fConst19 + (fRec8[0] * (fConst18 + (fConst17 * fRec8[0]))))))) + (fRec10[1] * (3.24028010230359e-07 + (fConst1 * (fConst16 + (fRec8[0] * (fConst14 + (fConst12 * fRec8[0])))))))) + (fRec10[3] * (1.08009336743453e-07 + (fConst1 * (fConst10 + (fRec8[0] * (fConst9 + (fConst8 * fRec8[0])))))))) / fTemp0));
		double fTemp2 = (((fRec9[0] * ((fRec10[1] * ((fConst1 * (fRec8[0] * ((8.60518628073643e-12 * fRec8[0]) - 2.04803433481527e-11))) - 7.37587395491694e-09)) + (fRec10[3] * (7.37587395491694e-09 + (fConst1 * (fRec8[0] * ((2.86839542691214e-12 * fRec8[0]) - 6.82678111605089e-12))))))) + ((fRec10[0] * (fTemp1 + (fConst1 * (fRec8[0] * ((fRec8[0] * (0 - (2.86839542691214e-12 * fRec9[0]))) + (6.82678111605089e-12 * fRec9[0])))))) + (fRec10[2] * ((fConst1 * (fRec8[0] * ((2.04803433481527e-11 * fRec9[0]) + (fRec8[0] * (0 - (8.60518628073643e-12 * fRec9[0])))))) - fTemp1)))) / fTemp0);
		fVec0[0] = fTemp2;
		fRec7[0] = ((fConst23 * fRec7[1]) + (fConst22 * (fVec0[0] + fVec0[1])));
		fVec1[0] = (1e-15 + fRec7[0]);
		fRec6[0] = ((0.9302847925323914 * (1e-15 + (fRec7[0] + fVec1[1]))) - (0.8605695850647829 * fRec6[1]));
		fRec5[0] = (fRec6[0] - ((1.8405051250752198 * fRec5[1]) + (0.8612942439318627 * fRec5[2])));
		double fTemp3 = (0.0082 * fRec4[1]);
		fVec2[0] = (1e-15 + fTemp3);
		fRec11[0] = ((fConst27 * fRec11[1]) + (fConst26 * (1e-15 + (fTemp3 + fVec2[1]))));
		fRec4[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec11[0] + (0.9254498422517706 * (fRec5[0] + (fRec5[2] + (2.0 * fRec5[1]))))) - 1.130462)) - 112.13878048780487);
		fRec3[0] = ((fConst32 * fRec3[1]) + (fConst31 * ((fConst28 * fRec4[0]) + (fConst29 * fRec4[1]))));
		fRec2[0] = ((fConst23 * fRec2[1]) + (fConst33 * (fRec3[1] + fRec3[0])));
		fRec1[0] = ((fConst38 * fRec1[1]) + (fConst37 * ((fConst34 * fRec2[0]) + (fConst35 * fRec2[1]))));
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec11[1] = fRec11[0];
		fVec2[1] = fVec2[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fVec1[1] = fVec1[0];
		fRec7[1] = fRec7[0];
		fVec0[1] = fVec0[0];
		for (int i=3; i>0; i--) fRec10[i] = fRec10[i-1];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec0[1] = fRec0[0];
	}
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
		fslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TONE: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   TONE, 
   VOLUME, 
} PortIndex;
*/

} // end namespace gx_chump
