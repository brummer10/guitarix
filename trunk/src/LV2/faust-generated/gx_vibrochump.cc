// generated from file '../src/LV2/faust/gx_vibrochump.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)

#include "valve.h"

namespace gx_vibrochump {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
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
	double 	fConst10;
	double 	fConst11;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst12;
	int 	iRec7[2];
	int 	iRec6[2];
	double 	fConst13;
	double 	fRec10[2];
	double 	fRec9[2];
	double 	fRec8[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec5[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec12[2];
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	FAUSTFLOAT 	fcheckbox1;
	FAUSTFLOAT	*fcheckbox1_;
	double 	fVec1[2];
	double 	fConst19;
	double 	fConst20;
	double 	fRec17[2];
	double 	fRec16[3];
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fVec2[2];
	double 	fConst29;
	double 	fRec21[2];
	double 	fRec20[2];
	double 	fConst30;
	double 	fConst31;
	double 	fRec19[2];
	double 	fConst32;
	double 	fConst33;
	double 	fRec18[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fRec22[2];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fRec23[2];
	double 	fVec3[2];
	double 	fRec15[2];
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fVec4[2];
	double 	fConst41;
	double 	fRec24[2];
	double 	fRec14[2];
	double 	fRec13[2];
	double 	fVec5[2];
	double 	fRec11[2];
	double 	fVec6[2];
	double 	fConst42;
	double 	fRec25[2];
	double 	fRec4[2];
	double 	fRec3[2];
	double 	fConst43;
	double 	fRec2[2];
	double 	fConst44;
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
	for (int i=0; i<2; i++) iRec7[i] = 0;
	for (int i=0; i<2; i++) iRec6[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
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
	fConst11 = (1.0 / iConst0);
	fConst12 = (0.5 * iConst0);
	fConst13 = (6.283185307179586 / iConst0);
	fConst14 = (1.0 / faustpower<2>(fConst4));
	fConst15 = (2 * (1 - fConst14));
	fConst16 = (1 + ((fConst5 - 1.0000000000000004) / fConst4));
	fConst17 = (1 + ((fConst5 + 1.0000000000000004) / fConst4));
	fConst18 = (1.0 / fConst17);
	fConst19 = (0 - fConst5);
	fConst20 = (1.0 / fConst6);
	fConst21 = (2 * (0 - fConst14));
	fConst22 = (0.4125375446227544 / fConst17);
	fConst23 = (1.0 / tan((5830.795965062656 / iConst0)));
	fConst24 = (1 + fConst23);
	fConst25 = (0 - ((1 - fConst23) / fConst24));
	fConst26 = (1.0 / tan((270.1769682087222 / iConst0)));
	fConst27 = (1 + fConst26);
	fConst28 = (0 - ((1 - fConst26) / fConst27));
	fConst29 = (1.0 / fConst27);
	fConst30 = (0 - fConst8);
	fConst31 = (0.025 / fConst9);
	fConst32 = (0 - fConst23);
	fConst33 = (1.0 / fConst24);
	fConst34 = (1.0 / tan((1281.7698026646356 / iConst0)));
	fConst35 = (1 + fConst34);
	fConst36 = (0 - ((1 - fConst34) / fConst35));
	fConst37 = (1.0 / fConst35);
	fConst38 = (1.0 / tan((314.1592653589793 / iConst0)));
	fConst39 = (1 + fConst38);
	fConst40 = (0 - ((1 - fConst38) / fConst39));
	fConst41 = (1.0 / fConst39);
	fConst42 = (1.0 / fConst2);
	fConst43 = (0.5 / fConst6);
	fConst44 = (0 - fConst1);
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
#define fcheckbox1 (*fcheckbox1_)
#define fslider3 (*fslider3_)
#define fslider4 (*fslider4_)
	double 	fSlow0 = fslider0;
	int 	iSlow1 = int((fConst12 / double(fSlow0)));
	double 	fSlow2 = (1.0 / iSlow1);
	double 	fSlow3 = (fConst13 * fSlow0);
	int 	iSlow4 = int(fcheckbox0);
	double 	fSlow5 = fslider1;
	double 	fSlow6 = (0.0010000000000000009 * pow(10,(0.05 * fslider2)));
	double 	fSlow7 = fcheckbox1;
	double 	fSlow8 = (fConst5 * fSlow7);
	double 	fSlow9 = fslider3;
	double 	fSlow10 = (1 - fSlow9);
	double 	fSlow11 = (0.0010000000000000009 * pow(10,(0.05 * fslider4)));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		double fTemp0 = (fRec5[1] * (1 - (fConst11 / (fConst11 + (0.06 * exp((0 - (2.4849066497880004 * fRec5[1]))))))));
		iRec7[0] = ((int((iRec7[1] > 0)))?((2 * (iRec6[1] < iSlow1)) - 1):(1 - (2 * (iRec6[1] > 0))));
		iRec6[0] = (iRec7[0] + iRec6[1]);
		fRec10[0] = ((fSlow3 * (0 - fRec8[1])) + fRec10[1]);
		fRec9[0] = ((1 + ((fSlow3 * fRec10[0]) + fRec9[1])) - iVec0[1]);
		fRec8[0] = fRec9[0];
		fRec5[0] = (fTemp0 + (fConst11 * (pow((1 + (fSlow5 * ((0.1 * ((iSlow4)?max(0, (0.5 * (1 + fRec8[0]))):(fSlow2 * iRec6[0]))) - 0.1))),1.9) / (fConst11 + (0.06 * exp((0 - (2.4849066497880004 * fTemp0))))))));
		fRec12[0] = (fSlow6 + (0.999 * fRec12[1]));
		double fTemp1 = (fSlow7 * fRec0[1]);
		fVec1[0] = fTemp1;
		fRec17[0] = ((fConst20 * ((fConst19 * fVec1[1]) + (fSlow8 * fRec0[1]))) + (fConst7 * fRec17[1]));
		fRec16[0] = (fRec17[0] - (fConst18 * ((fConst16 * fRec16[2]) + (fConst15 * fRec16[1]))));
		double fTemp2 = (1e-15 + (0.027 * fRec20[1]));
		fVec2[0] = fTemp2;
		fRec21[0] = ((fConst29 * (fVec2[0] + fVec2[1])) + (fConst28 * fRec21[1]));
		fRec20[0] = (Ftube(TUBE_TABLE_12AX7_68k, (((double)input0[i] + fRec21[0]) - 1.5816559999999988)) - 191.42014814814814);
		fRec19[0] = ((fConst31 * ((fConst30 * fRec20[1]) + (fConst8 * fRec20[0]))) + (fConst10 * fRec19[1]));
		fRec18[0] = ((fConst33 * ((fConst32 * fRec19[1]) + (fConst23 * fRec19[0]))) + (fConst25 * fRec18[1]));
		fRec22[0] = ((fConst37 * (fRec19[0] + fRec19[1])) + (fConst36 * fRec22[1]));
		fRec23[0] = (fSlow11 + (0.999 * fRec23[1]));
		double fTemp3 = ((fRec23[0] * ((fSlow10 * fRec22[0]) + (fSlow9 * fRec18[0]))) - (0.5 * (fVec1[0] + (fConst22 * (((fConst14 * fRec16[0]) + (fConst21 * fRec16[1])) + (fConst14 * fRec16[2]))))));
		fVec3[0] = fTemp3;
		fRec15[0] = ((fConst20 * (fVec3[0] + fVec3[1])) + (fConst7 * fRec15[1]));
		double fTemp4 = (1e-15 + (0.015 * fRec14[1]));
		fVec4[0] = fTemp4;
		fRec24[0] = ((fConst41 * (fVec4[0] + fVec4[1])) + (fConst40 * fRec24[1]));
		fRec14[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec24[0] + fRec15[0]) - 1.204284999999999)) - 169.71433333333334);
		fRec13[0] = ((fConst31 * ((fConst30 * fRec14[1]) + (fConst8 * fRec14[0]))) + (fConst10 * fRec13[1]));
		double fTemp5 = (fRec13[0] * fRec12[0]);
		fVec5[0] = fTemp5;
		fRec11[0] = ((fConst20 * (fVec5[0] + fVec5[1])) + (fConst7 * fRec11[1]));
		double fTemp6 = (1e-15 + (0.0082 * fRec4[1]));
		fVec6[0] = fTemp6;
		fRec25[0] = ((fConst42 * (fVec6[0] + fVec6[1])) + (fConst3 * fRec25[1]));
		fRec4[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec25[0] + (2700 * (fRec11[0] / (2700 + exp((13.815510557964274 / log((2.718281828459045 + (8.551967507929417 * fRec5[0]))))))))) - 1.130461999999999)) - 112.13878048780487);
		fRec3[0] = ((fConst31 * ((fConst30 * fRec4[1]) + (fConst8 * fRec4[0]))) + (fConst10 * fRec3[1]));
		fRec2[0] = ((fConst43 * (fRec3[0] + fRec3[1])) + (fConst7 * fRec2[1]));
		fRec1[0] = ((fConst42 * ((fConst44 * fRec2[1]) + (fConst1 * fRec2[0]))) + (fConst3 * fRec1[1]));
		fRec0[0] = fRec1[0];
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec25[1] = fRec25[0];
		fVec6[1] = fVec6[0];
		fRec11[1] = fRec11[0];
		fVec5[1] = fVec5[0];
		fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fRec24[1] = fRec24[0];
		fVec4[1] = fVec4[0];
		fRec15[1] = fRec15[0];
		fVec3[1] = fVec3[0];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fVec2[1] = fVec2[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fVec1[1] = fVec1[0];
		fRec12[1] = fRec12[0];
		fRec5[1] = fRec5[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		iRec6[1] = iRec6[0];
		iRec7[1] = iRec7[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fcheckbox0
#undef fslider1
#undef fslider2
#undef fcheckbox1
#undef fslider3
#undef fslider4
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
		fcheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	// static const value_pair fcheckbox0_values[] = {{"triangle"},{"sine"},{0}};
	case SINEWAVE: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case GAIN: 
		fslider4_ = (float*)data; // , 0.0, -2e+01, 2e+01, 0.1 
		break;
	case TONE: 
		fslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fslider2_ = (float*)data; // , 0.0, -2e+01, 1e+01, 0.1 
		break;
	case INTENSITY: 
		fslider1_ = (float*)data; // , 5.0, 0.0, 1e+01, 0.1 
		break;
	case SPEED: 
		fslider0_ = (float*)data; // , 5.0, 0.1, 1e+01, 0.1 
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
   SINEWAVE, 
   GAIN, 
   TONE, 
   VOLUME, 
   INTENSITY, 
   SPEED, 
} PortIndex;
*/

} // end namespace gx_vibrochump
