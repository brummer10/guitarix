// generated from file '../src/LV2/faust/gx_chump.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)

#include "valve.h"

namespace gx_chump {

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
	double 	fConst7;
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	double 	fVec0[2];
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fRec10[2];
	double 	fRec9[3];
	double 	fConst12;
	double 	fRec12[2];
	double 	fRec11[3];
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec13[2];
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fRec14[4];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec15[2];
	double 	fConst33;
	double 	fVec1[2];
	double 	fRec8[2];
	double 	fVec2[2];
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fVec3[2];
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fRec16[2];
	double 	fRec5[2];
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fRec4[2];
	double 	fRec3[2];
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fRec2[2];
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
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<4; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
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
	fConst14 = double(iConst0);
	fConst15 = (4.16885331779473e-15 * fConst14);
	fConst16 = (3.33921266453749e-09 + (fConst14 * (2.51329500908337e-11 + fConst15)));
	fConst17 = (8.80319430128334e-15 * fConst14);
	fConst18 = ((fConst14 * (0 - (9.77412876487773e-13 + fConst17))) - 2.15618481704215e-11);
	fConst19 = (1.30755824986672e-14 * fConst14);
	fConst20 = (4.21491687148728e-11 + (fConst14 * (1.57726547438855e-12 + fConst19)));
	fConst21 = ((fConst14 * (2.51329500908337e-11 - fConst15)) - 3.33921266453749e-09);
	fConst22 = (2.15618481704215e-11 + (fConst14 * (fConst17 - 9.77412876487773e-13)));
	fConst23 = ((fConst14 * (1.57726547438855e-12 - fConst19)) - 4.21491687148728e-11);
	fConst24 = (2.640958290385e-14 * fConst14);
	fConst25 = (2.15618481704215e-11 + (fConst14 * (9.77412876487773e-13 - fConst24)));
	fConst26 = (3.92267474960017e-14 * fConst14);
	fConst27 = ((fConst14 * (fConst26 - 1.57726547438855e-12)) - 4.21491687148728e-11);
	fConst28 = (1.25065599533842e-14 * fConst14);
	fConst29 = ((fConst14 * (fConst28 - 2.51329500908337e-11)) - 3.33921266453749e-09);
	fConst30 = (3.33921266453749e-09 + (fConst14 * (0 - (2.51329500908337e-11 + fConst28))));
	fConst31 = ((fConst14 * (9.77412876487773e-13 + fConst24)) - 2.15618481704215e-11);
	fConst32 = (4.21491687148728e-11 + (fConst14 * (0 - (1.57726547438855e-12 + fConst26))));
	fConst33 = faustpower<2>(fConst14);
	fConst34 = (1.0 / tan((376.99111843077515 / double(iConst0))));
	fConst35 = (1 + fConst34);
	fConst36 = (1.0 / fConst35);
	fConst37 = (0 - ((1 - fConst34) / fConst35));
	fConst38 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst39 = (0 - fConst38);
	fConst40 = (1 + fConst38);
	fConst41 = (0.025 / fConst40);
	fConst42 = (0 - ((1 - fConst38) / fConst40));
	fConst43 = (1.0 / tan((251.32741228718345 / double(iConst0))));
	fConst44 = (0 - fConst43);
	fConst45 = (1 + fConst43);
	fConst46 = (1.0 / fConst45);
	fConst47 = (0 - ((1 - fConst43) / fConst45));
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
	double 	fSlow0 = (0.0010000000000000009 * double(fslider0));
	double 	fSlow1 = double(fcheckbox0);
	double 	fSlow2 = (fConst4 * fSlow1);
	double 	fSlow3 = (0.004073836948085289 * (exp(double(fslider1)) - 1));
	double 	fSlow4 = (0.004073836948085289 * (exp(double(fslider2)) - 1));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.999 * fRec0[1]) + fSlow0);
		double fTemp0 = (fSlow1 * fRec1[1]);
		fVec0[0] = fTemp0;
		fRec10[0] = ((fConst11 * fRec10[1]) + (fConst10 * ((fSlow2 * fRec1[1]) + (fConst8 * fVec0[1]))));
		fRec9[0] = (fRec10[0] - (fConst7 * ((fConst5 * fRec9[2]) + (fConst3 * fRec9[1]))));
		fRec12[0] = ((fConst11 * fRec12[1]) + (fConst10 * (fVec0[0] + fVec0[1])));
		fRec11[0] = (fRec12[0] - (fConst7 * ((fConst5 * fRec11[2]) + (fConst3 * fRec11[1]))));
		fRec13[0] = ((0.993 * fRec13[1]) + fSlow3);
		double fTemp1 = (1.08009336743453e-07 + (fConst14 * ((fRec13[0] * (fConst20 + (fConst18 * fRec13[0]))) + fConst16)));
		fRec14[0] = ((double)input0[i] - ((((fRec14[1] * (3.24028010230359e-07 + (fConst14 * ((fRec13[0] * (fConst32 + (fConst31 * fRec13[0]))) + fConst30)))) + (fRec14[2] * (3.24028010230359e-07 + (fConst14 * (fConst29 + (fRec13[0] * (fConst27 + (fConst25 * fRec13[0])))))))) + (fRec14[3] * (1.08009336743453e-07 + (fConst14 * ((fRec13[0] * (fConst23 + (fConst22 * fRec13[0]))) + fConst21))))) / fTemp1));
		fRec15[0] = ((0.993 * fRec15[1]) + fSlow4);
		double fTemp2 = (7.37587395491694e-09 * fRec15[0]);
		double fTemp3 = (0 - fTemp2);
		double fTemp4 = ((fConst33 * (((((fRec14[0] * (fTemp2 + (fConst14 * (fRec13[0] * ((6.82678111605089e-12 * fRec15[0]) + (fRec13[0] * (0 - (2.86839542691214e-12 * fRec15[0])))))))) + (fRec14[1] * (fTemp3 + (fConst14 * ((fRec13[0] * fRec15[0]) * ((8.60518628073643e-12 * fRec13[0]) - 2.04803433481527e-11)))))) + (fRec14[2] * (fTemp3 + (fConst14 * (fRec13[0] * ((2.04803433481527e-11 * fRec15[0]) + (fRec13[0] * (0 - (8.60518628073643e-12 * fRec15[0]))))))))) + ((fRec15[0] * fRec14[3]) * (7.37587395491694e-09 + (fConst14 * (fRec13[0] * ((2.86839542691214e-12 * fRec13[0]) - 6.82678111605089e-12)))))) / fTemp1)) - (fConst13 * ((fRec11[2] + (fRec11[0] + (2 * fRec11[1]))) + (1.4125375446227544 * (((fConst2 * fRec9[0]) + (fConst12 * fRec9[1])) + (fConst2 * fRec9[2]))))));
		fVec1[0] = fTemp4;
		fRec8[0] = ((fConst11 * fRec8[1]) + (fConst10 * (fVec1[0] + fVec1[1])));
		double fTemp5 = (1e-15 + fRec8[0]);
		fVec2[0] = fTemp5;
		fRec7[0] = ((0.9302847925323914 * (fVec2[0] + fVec2[1])) - (0.8605695850647829 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.8612942439318627 * fRec6[2])));
		double fTemp6 = (1e-15 + (0.0082 * fRec5[1]));
		fVec3[0] = fTemp6;
		fRec16[0] = ((fConst37 * fRec16[1]) + (fConst36 * (fVec3[0] + fVec3[1])));
		fRec5[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec16[0] + (0.9254498422517706 * (fRec6[2] + (fRec6[0] + (2.0 * fRec6[1]))))) - 1.130462)) - 112.13878048780487);
		fRec4[0] = ((fConst42 * fRec4[1]) + (fConst41 * ((fConst38 * fRec5[0]) + (fConst39 * fRec5[1]))));
		fRec3[0] = ((fConst11 * fRec3[1]) + (fConst10 * (fRec4[0] + fRec4[1])));
		fRec2[0] = ((fConst47 * fRec2[1]) + (fConst46 * ((fConst43 * fRec3[0]) + (fConst44 * fRec3[1]))));
		fRec1[0] = fRec2[0];
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec16[1] = fRec16[0];
		fVec3[1] = fVec3[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fVec2[1] = fVec2[0];
		fRec8[1] = fRec8[0];
		fVec1[1] = fVec1[0];
		fRec15[1] = fRec15[0];
		for (int i=3; i>0; i--) fRec14[i] = fRec14[i-1];
		fRec13[1] = fRec13[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fVec0[1] = fVec0[0];
		fRec0[1] = fRec0[0];
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
		fslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TONE: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case FEEDBACK: 
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
   GAIN, 
   TONE, 
   VOLUME, 
   FEEDBACK, 
} PortIndex;
*/

} // end namespace gx_chump
