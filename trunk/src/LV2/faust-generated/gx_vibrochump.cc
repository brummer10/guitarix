// generated from file '../src/LV2/faust/gx_vibrochump.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "valve.h"

namespace gx_vibrochump {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst2;
	int 	iRec9[2];
	int 	iRec8[2];
	double 	fConst3;
	double 	fRec12[2];
	double 	fRec11[2];
	double 	fRec10[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec7[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec14[2];
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	FAUSTFLOAT 	fcheckbox1;
	FAUSTFLOAT	*fcheckbox1_;
	double 	fVec1[2];
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fRec21[2];
	double 	fRec20[3];
	double 	fConst15;
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fConst16;
	double 	fVec2[2];
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fVec3[2];
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fRec29[2];
	double 	fRec26[2];
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fRec25[2];
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fRec24[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fRec30[2];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fRec31[2];
	double 	fVec4[2];
	double 	fRec19[2];
	double 	fVec5[2];
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fVec6[2];
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fRec32[2];
	double 	fRec16[2];
	double 	fRec15[2];
	double 	fVec7[2];
	double 	fRec13[2];
	double 	fVec8[2];
	double 	fRec6[2];
	double 	fRec5[3];
	double 	fVec9[2];
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fRec33[2];
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
	for (int i=0; i<2; i++) iRec9[i] = 0;
	for (int i=0; i<2; i++) iRec8[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
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
	fConst1 = (1.0 / double(iConst0));
	fConst2 = (0.5 * iConst0);
	fConst3 = (6.283185307179586 / double(iConst0));
	fConst4 = tan((20517.741620594938 / double(iConst0)));
	fConst5 = (1.0 / faustpower<2>(fConst4));
	fConst6 = (2 * (1 - fConst5));
	fConst7 = (1.0 / fConst4);
	fConst8 = (1 + ((fConst7 - 1.0000000000000004) / fConst4));
	fConst9 = (1 + ((1.0000000000000004 + fConst7) / fConst4));
	fConst10 = (1.0 / fConst9);
	fConst11 = (0 - fConst7);
	fConst12 = (1 + fConst7);
	fConst13 = (1.0 / fConst12);
	fConst14 = (0 - ((1 - fConst7) / fConst12));
	fConst15 = (2 * (0 - fConst5));
	fConst16 = (0.5 / fConst9);
	fConst17 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst18 = (1 + fConst17);
	fConst19 = (1.0 / fConst18);
	fConst20 = (0 - ((1 - fConst17) / fConst18));
	fConst21 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst22 = (0 - fConst21);
	fConst23 = (1 + fConst21);
	fConst24 = (0.025 / fConst23);
	fConst25 = (0 - ((1 - fConst21) / fConst23));
	fConst26 = (1.0 / tan((1281.7698026646356 / double(iConst0))));
	fConst27 = (1 + fConst26);
	fConst28 = (1.0 / fConst27);
	fConst29 = (0 - ((1 - fConst26) / fConst27));
	fConst30 = (1.0 / tan((5830.795965062656 / double(iConst0))));
	fConst31 = (0 - fConst30);
	fConst32 = (1 + fConst30);
	fConst33 = (1.0 / fConst32);
	fConst34 = (0 - ((1 - fConst30) / fConst32));
	fConst35 = (1.0 / tan((314.1592653589793 / double(iConst0))));
	fConst36 = (1 + fConst35);
	fConst37 = (1.0 / fConst36);
	fConst38 = (0 - ((1 - fConst35) / fConst36));
	fConst39 = (1.0 / tan((376.99111843077515 / double(iConst0))));
	fConst40 = (1 + fConst39);
	fConst41 = (1.0 / fConst40);
	fConst42 = (0 - ((1 - fConst39) / fConst40));
	fConst43 = (0.5 / fConst12);
	fConst44 = (0 - fConst39);
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
#define fcheckbox1 (*fcheckbox1_)
#define fslider3 (*fslider3_)
#define fslider4 (*fslider4_)
	double 	fSlow0 = double(fslider0);
	int 	iSlow1 = int((fConst2 / double(fSlow0)));
	double 	fSlow2 = (1.0 / double(iSlow1));
	double 	fSlow3 = (fConst3 * fSlow0);
	int 	iSlow4 = int(double(fcheckbox0));
	double 	fSlow5 = double(fslider1);
	double 	fSlow6 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider2))));
	double 	fSlow7 = double(fcheckbox1);
	double 	fSlow8 = (fConst7 * fSlow7);
	double 	fSlow9 = double(fslider3);
	double 	fSlow10 = (1 - fSlow9);
	double 	fSlow11 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider4))));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		double fTemp0 = (fRec7[1] * (1 - (fConst1 / (fConst1 + (0.06 * exp((0 - (2.4849066497880004 * fRec7[1]))))))));
		iRec9[0] = ((int((iRec9[1] > 0)))?((2 * (iRec8[1] < iSlow1)) - 1):(1 - (2 * (iRec8[1] > 0))));
		iRec8[0] = (iRec9[0] + iRec8[1]);
		fRec12[0] = (fRec12[1] + (fSlow3 * (0 - fRec10[1])));
		fRec11[0] = ((1 + (fRec11[1] + (fSlow3 * fRec12[0]))) - iVec0[1]);
		fRec10[0] = fRec11[0];
		fRec7[0] = (fTemp0 + (fConst1 * (pow((1 + (fSlow5 * ((0.1 * ((iSlow4)?max((double)0, (0.5 * (1 + fRec10[0]))):(fSlow2 * iRec8[0]))) - 0.1))),1.9) / (fConst1 + (0.06 * exp((0 - (2.4849066497880004 * fTemp0))))))));
		fRec14[0] = ((0.999 * fRec14[1]) + fSlow6);
		double fTemp1 = (fSlow7 * fRec0[1]);
		fVec1[0] = fTemp1;
		fRec21[0] = ((fConst14 * fRec21[1]) + (fConst13 * ((fSlow8 * fRec0[1]) + (fConst11 * fVec1[1]))));
		fRec20[0] = (fRec21[0] - (fConst10 * ((fConst8 * fRec20[2]) + (fConst6 * fRec20[1]))));
		fRec23[0] = ((fConst14 * fRec23[1]) + (fConst13 * (fVec1[0] + fVec1[1])));
		fRec22[0] = (fRec23[0] - (fConst10 * ((fConst8 * fRec22[2]) + (fConst6 * fRec22[1]))));
		double fTemp2 = ((double)input0[i] + 1e-15);
		fVec2[0] = fTemp2;
		fRec28[0] = ((0.9302847925323914 * (fVec2[0] + fVec2[1])) - (0.8605695850647829 * fRec28[1]));
		fRec27[0] = (fRec28[0] - ((1.8405051250752198 * fRec27[1]) + (0.8612942439318627 * fRec27[2])));
		double fTemp3 = (1e-15 + (0.027 * fRec26[1]));
		fVec3[0] = fTemp3;
		fRec29[0] = ((fConst20 * fRec29[1]) + (fConst19 * (fVec3[0] + fVec3[1])));
		fRec26[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec29[0] + (0.9254498422517706 * (fRec27[2] + (fRec27[0] + (2.0 * fRec27[1]))))) - 1.581656)) - 191.42014814814814);
		fRec25[0] = ((fConst25 * fRec25[1]) + (fConst24 * ((fConst21 * fRec26[0]) + (fConst22 * fRec26[1]))));
		fRec24[0] = ((fConst29 * fRec24[1]) + (fConst28 * (fRec25[0] + fRec25[1])));
		fRec30[0] = ((fConst34 * fRec30[1]) + (fConst33 * ((fConst30 * fRec25[0]) + (fConst31 * fRec25[1]))));
		fRec31[0] = ((0.999 * fRec31[1]) + fSlow11);
		double fTemp4 = ((fRec31[0] * ((fSlow9 * fRec30[0]) + (fSlow10 * fRec24[0]))) - (fConst16 * ((fRec22[2] + (fRec22[0] + (2 * fRec22[1]))) + (1.4125375446227544 * (((fConst5 * fRec20[0]) + (fConst15 * fRec20[1])) + (fConst5 * fRec20[2]))))));
		fVec4[0] = fTemp4;
		fRec19[0] = ((fConst14 * fRec19[1]) + (fConst13 * (fVec4[0] + fVec4[1])));
		double fTemp5 = (1e-15 + fRec19[0]);
		fVec5[0] = fTemp5;
		fRec18[0] = ((0.9302847925323914 * (fVec5[1] + fVec5[0])) - (0.8605695850647829 * fRec18[1]));
		fRec17[0] = (fRec18[0] - ((1.8405051250752198 * fRec17[1]) + (0.8612942439318627 * fRec17[2])));
		double fTemp6 = (1e-15 + (0.015 * fRec16[1]));
		fVec6[0] = fTemp6;
		fRec32[0] = ((fConst38 * fRec32[1]) + (fConst37 * (fVec6[0] + fVec6[1])));
		fRec16[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec32[0] + (0.9254498422517706 * (fRec17[2] + (fRec17[0] + (2.0 * fRec17[1]))))) - 1.204285)) - 169.71433333333334);
		fRec15[0] = ((fConst25 * fRec15[1]) + (fConst24 * ((fConst21 * fRec16[0]) + (fConst22 * fRec16[1]))));
		double fTemp7 = (fRec15[0] * fRec14[0]);
		fVec7[0] = fTemp7;
		fRec13[0] = ((fConst14 * fRec13[1]) + (fConst13 * (fVec7[0] + fVec7[1])));
		double fTemp8 = (1e-15 + (2700 * (fRec13[0] / (2700 + exp((13.815510557964274 / log((2.718281828459045 + (8.551967507929417 * fRec7[0])))))))));
		fVec8[0] = fTemp8;
		fRec6[0] = ((0.9302847925323914 * (fVec8[0] + fVec8[1])) - (0.8605695850647829 * fRec6[1]));
		fRec5[0] = (fRec6[0] - ((1.8405051250752198 * fRec5[1]) + (0.8612942439318627 * fRec5[2])));
		double fTemp9 = (1e-15 + (0.0082 * fRec4[1]));
		fVec9[0] = fTemp9;
		fRec33[0] = ((fConst42 * fRec33[1]) + (fConst41 * (fVec9[0] + fVec9[1])));
		fRec4[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec33[0] + (0.9254498422517706 * (fRec5[2] + (fRec5[0] + (2.0 * fRec5[1]))))) - 1.130462)) - 112.13878048780487);
		fRec3[0] = ((fConst25 * fRec3[1]) + (fConst24 * ((fConst21 * fRec4[0]) + (fConst22 * fRec4[1]))));
		fRec2[0] = ((fConst14 * fRec2[1]) + (fConst43 * (fRec3[0] + fRec3[1])));
		fRec1[0] = ((fConst42 * fRec1[1]) + (fConst41 * ((fConst39 * fRec2[0]) + (fConst44 * fRec2[1]))));
		fRec0[0] = fRec1[0];
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec33[1] = fRec33[0];
		fVec9[1] = fVec9[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fVec8[1] = fVec8[0];
		fRec13[1] = fRec13[0];
		fVec7[1] = fVec7[0];
		fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fRec32[1] = fRec32[0];
		fVec6[1] = fVec6[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fVec5[1] = fVec5[0];
		fRec19[1] = fRec19[0];
		fVec4[1] = fVec4[0];
		fRec31[1] = fRec31[0];
		fRec30[1] = fRec30[0];
		fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fRec29[1] = fRec29[0];
		fVec3[1] = fVec3[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fVec2[1] = fVec2[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fVec1[1] = fVec1[0];
		fRec14[1] = fRec14[0];
		fRec7[1] = fRec7[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		iRec8[1] = iRec8[0];
		iRec9[1] = iRec9[0];
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

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case GAIN: 
		fslider4_ = (float*)data; // , 0.0, -2e+01, 2e+01, 0.1 
		break;
	// static const value_pair fcheckbox0_values[] = {{"triangle"},{"sine"},{0}};
	case SINEWAVE: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case VOLUME: 
		fslider2_ = (float*)data; // , 0.0, -2e+01, 1e+01, 0.1 
		break;
	case FEEDBACK: 
		fcheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case INTENSITY: 
		fslider1_ = (float*)data; // , 5.0, 0.0, 1e+01, 0.1 
		break;
	case SPEED: 
		fslider0_ = (float*)data; // , 5.0, 0.1, 1e+01, 0.1 
		break;
	case TONE: 
		fslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   SINEWAVE, 
   VOLUME, 
   FEEDBACK, 
   INTENSITY, 
   SPEED, 
   TONE, 
} PortIndex;
*/

} // end namespace gx_vibrochump
