// generated from file '../src/LV2/faust/gx_vibrochump.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)

#include "valve.h"

namespace gx_vibrochump {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	int 	iVec0[2];
	double 	fRec0[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec7[2];
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst9;
	int 	iRec10[2];
	int 	iRec9[2];
	double 	fConst10;
	double 	fRec13[2];
	double 	fRec12[2];
	double 	fRec11[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec8[2];
	FAUSTFLOAT 	fcheckbox1;
	FAUSTFLOAT	*fcheckbox1_;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fRec14[4];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fRec15[2];
	double 	fConst23;
	double 	fVec1[2];
	double 	fRec6[2];
	double 	fRec5[3];
	double 	fVec2[2];
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fRec16[2];
	double 	fRec4[2];
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fRec3[2];
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fRec2[2];
	double 	fConst37;
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
	id = "Redeye Vibro Chump";
	name = N_("Redeye Vibro Chumo");
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) iRec10[i] = 0;
	for (int i=0; i<2; i++) iRec9[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<4; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
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
	fConst1 = double(iConst0);
	fConst2 = (4.16885331779473e-15 * fConst1);
	fConst3 = (3.33921266453749e-09 + (fConst1 * (2.51329500908337e-11 + fConst2)));
	fConst4 = (8.80319430128334e-15 * fConst1);
	fConst5 = ((fConst1 * (0 - (9.77412876487773e-13 + fConst4))) - 2.15618481704215e-11);
	fConst6 = (1.30755824986672e-14 * fConst1);
	fConst7 = (4.21491687148728e-11 + (fConst1 * (1.57726547438855e-12 + fConst6)));
	fConst8 = (1.0 / double(iConst0));
	fConst9 = (0.5 * iConst0);
	fConst10 = (6.283185307179586 / double(iConst0));
	fConst11 = ((fConst1 * (2.51329500908337e-11 - fConst2)) - 3.33921266453749e-09);
	fConst12 = (2.15618481704215e-11 + (fConst1 * (fConst4 - 9.77412876487773e-13)));
	fConst13 = ((fConst1 * (1.57726547438855e-12 - fConst6)) - 4.21491687148728e-11);
	fConst14 = (2.640958290385e-14 * fConst1);
	fConst15 = (2.15618481704215e-11 + (fConst1 * (9.77412876487773e-13 - fConst14)));
	fConst16 = (3.92267474960017e-14 * fConst1);
	fConst17 = ((fConst1 * (fConst16 - 1.57726547438855e-12)) - 4.21491687148728e-11);
	fConst18 = (1.25065599533842e-14 * fConst1);
	fConst19 = ((fConst1 * (fConst18 - 2.51329500908337e-11)) - 3.33921266453749e-09);
	fConst20 = (3.33921266453749e-09 + (fConst1 * (0 - (2.51329500908337e-11 + fConst18))));
	fConst21 = ((fConst1 * (9.77412876487773e-13 + fConst14)) - 2.15618481704215e-11);
	fConst22 = (4.21491687148728e-11 + (fConst1 * (0 - (1.57726547438855e-12 + fConst16))));
	fConst23 = (0.1 * faustpower<2>(fConst1));
	fConst24 = (1.0 / tan((376.99111843077515 / double(iConst0))));
	fConst25 = (1 + fConst24);
	fConst26 = (1.0 / fConst25);
	fConst27 = (0 - ((1 - fConst24) / fConst25));
	fConst28 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst29 = (0 - fConst28);
	fConst30 = (1 + fConst28);
	fConst31 = (0.025 / fConst30);
	fConst32 = (0 - ((1 - fConst28) / fConst30));
	fConst33 = (1.0 / tan((17278.75959474386 / double(iConst0))));
	fConst34 = (1 + fConst33);
	fConst35 = (1.0 / fConst34);
	fConst36 = (0 - ((1 - fConst33) / fConst34));
	fConst37 = (0 - fConst24);
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
#define fslider3 (*fslider3_)
#define fcheckbox1 (*fcheckbox1_)
#define fslider4 (*fslider4_)
	double 	fSlow0 = (0.0010000000000000009 * double(fslider0));
	double 	fSlow1 = (0.004073836948085289 * (exp(double(fslider1)) - 1));
	double 	fSlow2 = double(fslider2);
	int 	iSlow3 = int((fConst9 / double(fSlow2)));
	double 	fSlow4 = (1.0 / double(iSlow3));
	double 	fSlow5 = (fConst10 * fSlow2);
	int 	iSlow6 = int(double(fcheckbox0));
	double 	fSlow7 = double(fslider3);
	int 	iSlow8 = int(double(fcheckbox1));
	double 	fSlow9 = (0.004073836948085289 * (exp(double(fslider4)) - 1));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec0[0] = ((0.999 * fRec0[1]) + fSlow0);
		fRec7[0] = ((0.993 * fRec7[1]) + fSlow1);
		double fTemp0 = (1.08009336743453e-07 + (fConst1 * ((fRec7[0] * (fConst7 + (fConst5 * fRec7[0]))) + fConst3)));
		double fTemp1 = (fRec8[1] * (1 - (fConst8 / (fConst8 + (0.06 * exp((0 - (2.4849066497880004 * fRec8[1]))))))));
		iRec10[0] = ((int((iRec10[1] > 0)))?((2 * (iRec9[1] < iSlow3)) - 1):(1 - (2 * (iRec9[1] > 0))));
		iRec9[0] = (iRec10[0] + iRec9[1]);
		fRec13[0] = (fRec13[1] + (fSlow5 * (0 - fRec11[1])));
		fRec12[0] = ((1 + (fRec12[1] + (fSlow5 * fRec13[0]))) - iVec0[1]);
		fRec11[0] = fRec12[0];
		fRec8[0] = (fTemp1 + (fConst8 * (pow((1 + (fSlow7 * ((0.09803921568627452 * ((iSlow6)?max((double)0, (0.5 * (1 + fRec11[0]))):(fSlow4 * iRec9[0]))) - 0.09803921568627452))),1.9) / (fConst8 + (0.06 * exp((0 - (2.4849066497880004 * fTemp1))))))));
		fRec14[0] = ((double)input0[i] - ((((fRec14[1] * (3.24028010230359e-07 + (fConst1 * ((fRec7[0] * (fConst22 + (fConst21 * fRec7[0]))) + fConst20)))) + (fRec14[2] * (3.24028010230359e-07 + (fConst1 * (fConst19 + (fRec7[0] * (fConst17 + (fConst15 * fRec7[0])))))))) + (fRec14[3] * (1.08009336743453e-07 + (fConst1 * ((fRec7[0] * (fConst13 + (fConst12 * fRec7[0]))) + fConst11))))) / fTemp0));
		fRec15[0] = ((0.993 * fRec15[1]) + fSlow9);
		double fTemp2 = (7.37587395491694e-09 * fRec15[0]);
		double fTemp3 = (0 - fTemp2);
		double fTemp4 = (1e-15 + (fConst23 * ((((((fRec14[0] * (fTemp2 + (fConst1 * (fRec7[0] * ((6.82678111605089e-12 * fRec15[0]) + (fRec7[0] * (0 - (2.86839542691214e-12 * fRec15[0])))))))) + (fRec14[1] * (fTemp3 + (fConst1 * ((fRec7[0] * fRec15[0]) * ((8.60518628073643e-12 * fRec7[0]) - 2.04803433481527e-11)))))) + (fRec14[2] * (fTemp3 + (fConst1 * (fRec7[0] * ((2.04803433481527e-11 * fRec15[0]) + (fRec7[0] * (0 - (8.60518628073643e-12 * fRec15[0]))))))))) + ((fRec15[0] * fRec14[3]) * (7.37587395491694e-09 + (fConst1 * (fRec7[0] * ((2.86839542691214e-12 * fRec7[0]) - 6.82678111605089e-12)))))) * ((iSlow8)?(double(2700) / (2700 + exp((13.815510557964274 / log((2.718281828459045 + (8.551967507929417 * fRec8[0]))))))):1.0)) / fTemp0)));
		fVec1[0] = fTemp4;
		fRec6[0] = ((0.9302847925323914 * (fVec1[0] + fVec1[1])) - (0.8605695850647829 * fRec6[1]));
		fRec5[0] = (fRec6[0] - ((1.8405051250752198 * fRec5[1]) + (0.8612942439318627 * fRec5[2])));
		double fTemp5 = (1e-15 + (0.0082 * fRec4[1]));
		fVec2[0] = fTemp5;
		fRec16[0] = ((fConst27 * fRec16[1]) + (fConst26 * (fVec2[0] + fVec2[1])));
		fRec4[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec16[0] + (0.9254498422517706 * (fRec5[2] + (fRec5[0] + (2.0 * fRec5[1]))))) - 1.130462)) - 112.13878048780487);
		fRec3[0] = ((fConst32 * fRec3[1]) + (fConst31 * ((fConst28 * fRec4[0]) + (fConst29 * fRec4[1]))));
		fRec2[0] = ((fConst36 * fRec2[1]) + (fConst35 * (fRec3[0] + fRec3[1])));
		fRec1[0] = ((fConst27 * fRec1[1]) + (fConst26 * ((fConst24 * fRec2[0]) + (fConst37 * fRec2[1]))));
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec16[1] = fRec16[0];
		fVec2[1] = fVec2[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fVec1[1] = fVec1[0];
		fRec15[1] = fRec15[0];
		for (int i=3; i>0; i--) fRec14[i] = fRec14[i-1];
		fRec8[1] = fRec8[0];
		fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		iRec9[1] = iRec9[0];
		iRec10[1] = iRec10[0];
		fRec7[1] = fRec7[0];
		fRec0[1] = fRec0[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fcheckbox0
#undef fslider3
#undef fcheckbox1
#undef fslider4
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
		fslider4_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TONE: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	// static const value_pair fcheckbox0_values[] = {{"triangle"},{"sine"},{0}};
	case SINEWAVE: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case INTENSITY: 
		fslider3_ = (float*)data; // , 5.0, 0.0, 1e+01, 0.1 
		break;
	case SPEED: 
		fslider2_ = (float*)data; // , 5.0, 0.1, 1e+01, 0.1 
		break;
	// static const value_pair fcheckbox1_values[] = {{"Off"},{"On"},{0}};
	case VIBE: 
		fcheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
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
   SINEWAVE, 
   INTENSITY, 
   SPEED, 
   VIBE, 
} PortIndex;
*/

} // end namespace gx_vibrochump
