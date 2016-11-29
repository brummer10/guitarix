// generated from file '../src/LV2/faust/gx_bigchump.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)

#include "valve.h"

namespace gx_bigchump {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec7[2];
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
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
	double 	fRec8[4];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec9[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec10[2];
	double 	fConst20;
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	double 	fVec0[2];
	double 	fRec6[2];
	double 	fRec5[3];
	double 	fVec1[2];
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fRec11[2];
	double 	fRec4[2];
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fRec3[2];
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fRec2[2];
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fRec1[2];
	double 	fVec2[2];
	double 	fRec17[2];
	double 	fRec16[3];
	double 	fVec3[2];
	double 	fRec18[2];
	double 	fRec15[2];
	double 	fRec14[2];
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fRec13[2];
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fRec12[2];
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
	for (int i=0; i<4; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
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
	fConst1 = double(iConst0);
	fConst2 = (4.16885331779473e-15 * fConst1);
	fConst3 = (3.33921266453749e-09 + (fConst1 * (2.51329500908337e-11 + fConst2)));
	fConst4 = (8.80319430128334e-15 * fConst1);
	fConst5 = ((fConst1 * (0 - (9.77412876487773e-13 + fConst4))) - 2.15618481704215e-11);
	fConst6 = (1.30755824986672e-14 * fConst1);
	fConst7 = (4.21491687148728e-11 + (fConst1 * (1.57726547438855e-12 + fConst6)));
	fConst8 = ((fConst1 * (2.51329500908337e-11 - fConst2)) - 3.33921266453749e-09);
	fConst9 = (2.15618481704215e-11 + (fConst1 * (fConst4 - 9.77412876487773e-13)));
	fConst10 = ((fConst1 * (1.57726547438855e-12 - fConst6)) - 4.21491687148728e-11);
	fConst11 = (2.640958290385e-14 * fConst1);
	fConst12 = (2.15618481704215e-11 + (fConst1 * (9.77412876487773e-13 - fConst11)));
	fConst13 = (3.92267474960017e-14 * fConst1);
	fConst14 = ((fConst1 * (fConst13 - 1.57726547438855e-12)) - 4.21491687148728e-11);
	fConst15 = (1.25065599533842e-14 * fConst1);
	fConst16 = ((fConst1 * (fConst15 - 2.51329500908337e-11)) - 3.33921266453749e-09);
	fConst17 = (3.33921266453749e-09 + (fConst1 * (0 - (2.51329500908337e-11 + fConst15))));
	fConst18 = ((fConst1 * (9.77412876487773e-13 + fConst11)) - 2.15618481704215e-11);
	fConst19 = (4.21491687148728e-11 + (fConst1 * (0 - (1.57726547438855e-12 + fConst13))));
	fConst20 = faustpower<2>(fConst1);
	fConst21 = (1.0 / tan((188.49555921538757 / double(iConst0))));
	fConst22 = (1 + fConst21);
	fConst23 = (1.0 / fConst22);
	fConst24 = (0 - ((1 - fConst21) / fConst22));
	fConst25 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst26 = (0 - fConst25);
	fConst27 = (1 + fConst25);
	fConst28 = (0.025 / fConst27);
	fConst29 = (0 - ((1 - fConst25) / fConst27));
	fConst30 = (1.0 / tan((25368.36067773758 / double(iConst0))));
	fConst31 = (1 + fConst30);
	fConst32 = (1.0 / fConst31);
	fConst33 = (0 - ((1 - fConst30) / fConst31));
	fConst34 = (1.0 / tan((263.89378290154264 / double(iConst0))));
	fConst35 = (0 - fConst34);
	fConst36 = (1 + fConst34);
	fConst37 = (1.0 / fConst36);
	fConst38 = (0 - ((1 - fConst34) / fConst36));
	fConst39 = (1.0 / tan((28038.714433288904 / double(iConst0))));
	fConst40 = (1 + fConst39);
	fConst41 = (1.0 / fConst40);
	fConst42 = (0 - ((1 - fConst39) / fConst40));
	fConst43 = (1.0 / tan((238.76104167282426 / double(iConst0))));
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
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fcheckbox0 (*fcheckbox0_)
	double 	fSlow0 = (0.004073836948085289 * (exp(double(fslider0)) - 1));
	double 	fSlow1 = (0.004073836948085289 * (exp(double(fslider1)) - 1));
	double 	fSlow2 = (0.0010000000000000009 * double(fslider2));
	double 	fSlow3 = (0.5 * double(fcheckbox0));
	for (int i=0; i<count; i++) {
		fRec7[0] = ((0.993 * fRec7[1]) + fSlow0);
		double fTemp0 = (1.08009336743453e-07 + (fConst1 * ((fRec7[0] * (fConst7 + (fConst5 * fRec7[0]))) + fConst3)));
		fRec8[0] = ((double)input0[i] - ((((fRec8[1] * (3.24028010230359e-07 + (fConst1 * ((fRec7[0] * (fConst19 + (fConst18 * fRec7[0]))) + fConst17)))) + (fRec8[2] * (3.24028010230359e-07 + (fConst1 * (fConst16 + (fRec7[0] * (fConst14 + (fConst12 * fRec7[0])))))))) + (fRec8[3] * (1.08009336743453e-07 + (fConst1 * ((fRec7[0] * (fConst10 + (fConst9 * fRec7[0]))) + fConst8))))) / fTemp0));
		fRec9[0] = ((0.993 * fRec9[1]) + fSlow1);
		double fTemp1 = (7.37587395491694e-09 * fRec9[0]);
		double fTemp2 = (0 - fTemp1);
		fRec10[0] = ((0.999 * fRec10[1]) + fSlow2);
		double fTemp3 = ((fSlow3 * fRec0[1]) + (fConst20 * ((fRec10[0] * ((((fRec8[0] * (fTemp1 + (fConst1 * (fRec7[0] * ((6.82678111605089e-12 * fRec9[0]) + (fRec7[0] * (0 - (2.86839542691214e-12 * fRec9[0])))))))) + (fRec8[1] * (fTemp2 + (fConst1 * ((fRec7[0] * fRec9[0]) * ((8.60518628073643e-12 * fRec7[0]) - 2.04803433481527e-11)))))) + (fRec8[2] * (fTemp2 + (fConst1 * (fRec7[0] * ((2.04803433481527e-11 * fRec9[0]) + (fRec7[0] * (0 - (8.60518628073643e-12 * fRec9[0]))))))))) + ((fRec9[0] * fRec8[3]) * (7.37587395491694e-09 + (fConst1 * (fRec7[0] * ((2.86839542691214e-12 * fRec7[0]) - 6.82678111605089e-12))))))) / fTemp0)));
		double fTemp4 = (1e-15 + (fTemp3 * (fTemp3 >= 0.0)));
		fVec0[0] = fTemp4;
		fRec6[0] = ((0.9302847925323914 * (fVec0[0] + fVec0[1])) - (0.8605695850647829 * fRec6[1]));
		fRec5[0] = (fRec6[0] - ((1.8405051250752198 * fRec5[1]) + (0.8612942439318627 * fRec5[2])));
		double fTemp5 = (1e-15 + (0.00822 * fRec4[1]));
		fVec1[0] = fTemp5;
		fRec11[0] = ((fConst24 * fRec11[1]) + (fConst23 * (fVec1[0] + fVec1[1])));
		fRec4[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec11[0] + (0.9254498422517706 * (fRec5[2] + (fRec5[0] + (2.0 * fRec5[1]))))) - 1.130462)) - 112.47420924574209);
		fRec3[0] = ((fConst29 * fRec3[1]) + (fConst28 * ((fConst25 * fRec4[0]) + (fConst26 * fRec4[1]))));
		fRec2[0] = ((fConst33 * fRec2[1]) + (fConst32 * (fRec3[0] + fRec3[1])));
		fRec1[0] = ((fConst38 * fRec1[1]) + (fConst37 * ((fConst34 * fRec2[0]) + (fConst35 * fRec2[1]))));
		double fTemp6 = (1e-15 + (fTemp3 * (fTemp3 <= 0.0)));
		fVec2[0] = fTemp6;
		fRec17[0] = ((0.9302847925323914 * (fVec2[0] + fVec2[1])) - (0.8605695850647829 * fRec17[1]));
		fRec16[0] = (fRec17[0] - ((1.8405051250752198 * fRec16[1]) + (0.8612942439318627 * fRec16[2])));
		double fTemp7 = (1e-15 + (0.00818 * fRec15[1]));
		fVec3[0] = fTemp7;
		fRec18[0] = ((fConst24 * fRec18[1]) + (fConst23 * (fVec3[0] + fVec3[1])));
		fRec15[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec18[0] + (0.9254498422517706 * (fRec16[2] + (fRec16[0] + (2.0 * fRec16[1]))))) - 1.130462)) - 111.80171149144252);
		fRec14[0] = ((fConst29 * fRec14[1]) + (fConst28 * ((fConst25 * fRec15[0]) + (fConst26 * fRec15[1]))));
		fRec13[0] = ((fConst42 * fRec13[1]) + (fConst41 * (fRec14[0] + fRec14[1])));
		fRec12[0] = ((fConst47 * fRec12[1]) + (fConst46 * ((fConst43 * fRec13[0]) + (fConst44 * fRec13[1]))));
		fRec0[0] = (fRec12[0] + (0.98 * fRec1[0]));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec18[1] = fRec18[0];
		fVec3[1] = fVec3[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fVec2[1] = fVec2[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec11[1] = fRec11[0];
		fVec1[1] = fVec1[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fVec0[1] = fVec0[0];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		for (int i=3; i>0; i--) fRec8[i] = fRec8[i-1];
		fRec7[1] = fRec7[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
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
	case GAIN: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TONE: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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

} // end namespace gx_bigchump
