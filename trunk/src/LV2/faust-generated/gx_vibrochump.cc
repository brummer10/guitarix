// generated from file '../src/LV2/faust/gx_vibrochump.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)

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
	int 	iRec8[2];
	int 	iRec7[2];
	double 	fConst3;
	double 	fRec11[2];
	double 	fRec10[2];
	double 	fRec9[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec6[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec13[2];
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
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec24[2];
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fVec2[2];
	double 	fRec29[2];
	double 	fRec28[3];
	double 	fVec3[2];
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fRec30[2];
	double 	fRec27[2];
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fRec26[2];
	double 	fRec25[3];
	double 	fConst36;
	double 	fConst37;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	double 	fRec31[2];
	double 	fVec4[2];
	double 	fRec19[2];
	double 	fVec5[2];
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fVec6[2];
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fRec32[2];
	double 	fRec16[2];
	double 	fRec15[2];
	double 	fRec14[2];
	double 	fVec7[2];
	double 	fRec12[2];
	double 	fVec8[2];
	double 	fRec5[2];
	double 	fRec4[3];
	double 	fVec9[2];
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fRec33[2];
	double 	fRec3[2];
	double 	fRec2[2];
	double 	fConst46;
	double 	fRec1[2];
	double 	fConst47;
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
	for (int i=0; i<2; i++) iRec8[i] = 0;
	for (int i=0; i<2; i++) iRec7[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
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
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
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
	fConst9 = (1 + ((fConst7 + 1.0000000000000004) / fConst4));
	fConst10 = (1.0 / fConst9);
	fConst11 = (0 - fConst7);
	fConst12 = (1 + fConst7);
	fConst13 = (1.0 / fConst12);
	fConst14 = (0 - ((1 - fConst7) / fConst12));
	fConst15 = (2 * (0 - fConst5));
	fConst16 = (0.5 / fConst9);
	fConst17 = double(iConst0);
	fConst18 = (8.67101574539126e-07 * fConst17);
	fConst19 = (0.00401435914138484 - fConst18);
	fConst20 = faustpower<2>(fConst17);
	fConst21 = ((3.68688858465455e-10 * fConst20) - 0.00316091270975185);
	fConst22 = (3.68688858465455e-10 * fConst17);
	fConst23 = (0.00486780557301784 + (fConst17 * (fConst22 - 3.03485551088694e-06)));
	fConst24 = (7.37377716930911e-10 * fConst20);
	fConst25 = (0.00973561114603569 - fConst24);
	fConst26 = (1.0 / (0.00486780557301784 + (fConst17 * (3.03485551088694e-06 + fConst22))));
	fConst27 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst28 = (1 + fConst27);
	fConst29 = (1.0 / fConst28);
	fConst30 = (0 - ((1 - fConst27) / fConst28));
	fConst31 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst32 = (0 - fConst31);
	fConst33 = (1 + fConst31);
	fConst34 = (0.025 / fConst33);
	fConst35 = (0 - ((1 - fConst31) / fConst33));
	fConst36 = (0 - (0.00632182541950369 + fConst24));
	fConst37 = (0.00401435914138484 + fConst18);
	fConst38 = (1.0 / tan((314.1592653589793 / double(iConst0))));
	fConst39 = (1 + fConst38);
	fConst40 = (1.0 / fConst39);
	fConst41 = (0 - ((1 - fConst38) / fConst39));
	fConst42 = (1.0 / tan((376.99111843077515 / double(iConst0))));
	fConst43 = (1 + fConst42);
	fConst44 = (1.0 / fConst43);
	fConst45 = (0 - ((1 - fConst42) / fConst43));
	fConst46 = (0.5 / fConst12);
	fConst47 = (0 - fConst42);
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
	double 	fSlow6 = (0.007000000000000006 * pow(10,(0.05 * double(fslider2))));
	double 	fSlow7 = double(fcheckbox1);
	double 	fSlow8 = (fConst7 * fSlow7);
	double 	fSlow9 = (0.007000000000000006 * double(fslider3));
	double 	fSlow10 = (0.007000000000000006 * pow(10,(0.05 * double(fslider4))));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		double fTemp0 = (fRec6[1] * (1 - (fConst1 / (fConst1 + (0.06 * exp((0 - (2.4849066497880004 * fRec6[1]))))))));
		iRec8[0] = ((int((iRec8[1] > 0)))?((2 * (iRec7[1] < iSlow1)) - 1):(1 - (2 * (iRec7[1] > 0))));
		iRec7[0] = (iRec8[0] + iRec7[1]);
		fRec11[0] = (fRec11[1] + (fSlow3 * (0 - fRec9[1])));
		fRec10[0] = ((1 + (fRec10[1] + (fSlow3 * fRec11[0]))) - iVec0[1]);
		fRec9[0] = fRec10[0];
		fRec6[0] = (fTemp0 + (fConst1 * (pow((1 + (fSlow5 * ((0.1 * ((iSlow4)?max((double)0, (0.5 * (1 + fRec9[0]))):(fSlow2 * iRec7[0]))) - 0.1))),1.9) / (fConst1 + (0.06 * exp((0 - (2.4849066497880004 * fTemp0))))))));
		fRec13[0] = ((0.993 * fRec13[1]) + fSlow6);
		double fTemp1 = (fSlow7 * fRec14[1]);
		fVec1[0] = fTemp1;
		fRec21[0] = ((fConst14 * fRec21[1]) + (fConst13 * ((fSlow8 * fRec14[1]) + (fConst11 * fVec1[1]))));
		fRec20[0] = (fRec21[0] - (fConst10 * ((fConst8 * fRec20[2]) + (fConst6 * fRec20[1]))));
		fRec23[0] = ((fConst14 * fRec23[1]) + (fConst13 * (fVec1[0] + fVec1[1])));
		fRec22[0] = (fRec23[0] - (fConst10 * ((fConst8 * fRec22[2]) + (fConst6 * fRec22[1]))));
		fRec24[0] = ((0.993 * fRec24[1]) + fSlow9);
		double fTemp2 = (fConst21 * fRec24[0]);
		double fTemp3 = ((double)input0[i] + 1e-15);
		fVec2[0] = fTemp3;
		fRec29[0] = ((0.9302847925323914 * (fVec2[0] + fVec2[1])) - (0.8605695850647829 * fRec29[1]));
		fRec28[0] = (fRec29[0] - ((1.8405051250752198 * fRec28[1]) + (0.8612942439318627 * fRec28[2])));
		double fTemp4 = (1e-15 + (0.027 * fRec27[1]));
		fVec3[0] = fTemp4;
		fRec30[0] = ((fConst30 * fRec30[1]) + (fConst29 * (fVec3[0] + fVec3[1])));
		fRec27[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec30[0] + (0.9254498422517706 * (fRec28[2] + (fRec28[0] + (2.0 * fRec28[1]))))) - 1.581656)) - 191.42014814814814);
		fRec26[0] = ((fConst35 * fRec26[1]) + (fConst34 * ((fConst31 * fRec27[0]) + (fConst32 * fRec27[1]))));
		fRec25[0] = (fRec26[0] - (fConst26 * ((fConst25 * fRec25[1]) + (fConst23 * fRec25[2]))));
		fRec31[0] = ((0.993 * fRec31[1]) + fSlow10);
		double fTemp5 = ((fConst26 * (fRec31[0] * (((fRec25[0] * (fTemp2 + fConst37)) + (fRec25[1] * (0.00802871828276969 + (fConst36 * fRec24[0])))) + (fRec25[2] * (fTemp2 + fConst19))))) - (fConst16 * ((fRec22[2] + (fRec22[0] + (2 * fRec22[1]))) + (1.4125375446227544 * (((fConst5 * fRec20[0]) + (fConst15 * fRec20[1])) + (fConst5 * fRec20[2]))))));
		fVec4[0] = fTemp5;
		fRec19[0] = ((fConst14 * fRec19[1]) + (fConst13 * (fVec4[0] + fVec4[1])));
		double fTemp6 = (1e-15 + fRec19[0]);
		fVec5[0] = fTemp6;
		fRec18[0] = ((0.9302847925323914 * (fVec5[0] + fVec5[1])) - (0.8605695850647829 * fRec18[1]));
		fRec17[0] = (fRec18[0] - ((1.8405051250752198 * fRec17[1]) + (0.8612942439318627 * fRec17[2])));
		double fTemp7 = (1e-15 + (0.015 * fRec16[1]));
		fVec6[0] = fTemp7;
		fRec32[0] = ((fConst41 * fRec32[1]) + (fConst40 * (fVec6[0] + fVec6[1])));
		fRec16[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec32[0] + (0.9254498422517706 * (fRec17[2] + (fRec17[0] + (2.0 * fRec17[1]))))) - 1.204285)) - 169.71433333333334);
		fRec15[0] = ((fConst35 * fRec15[1]) + (fConst34 * ((fConst31 * fRec16[0]) + (fConst32 * fRec16[1]))));
		fRec14[0] = fRec15[0];
		double fTemp8 = (fRec14[0] * fRec13[0]);
		fVec7[0] = fTemp8;
		fRec12[0] = ((fConst14 * fRec12[1]) + (fConst13 * (fVec7[0] + fVec7[1])));
		double fTemp9 = (1e-15 + (2700 * (fRec12[0] / (2700 + exp((13.815510557964274 / log((2.718281828459045 + (8.551967507929417 * fRec6[0])))))))));
		fVec8[0] = fTemp9;
		fRec5[0] = ((0.9302847925323914 * (fVec8[0] + fVec8[1])) - (0.8605695850647829 * fRec5[1]));
		fRec4[0] = (fRec5[0] - ((1.8405051250752198 * fRec4[1]) + (0.8612942439318627 * fRec4[2])));
		double fTemp10 = (1e-15 + (0.0082 * fRec3[1]));
		fVec9[0] = fTemp10;
		fRec33[0] = ((fConst45 * fRec33[1]) + (fConst44 * (fVec9[0] + fVec9[1])));
		fRec3[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec33[0] + (0.9254498422517706 * (fRec4[2] + (fRec4[0] + (2.0 * fRec4[1]))))) - 1.130462)) - 112.13878048780487);
		fRec2[0] = ((fConst35 * fRec2[1]) + (fConst34 * ((fConst31 * fRec3[0]) + (fConst32 * fRec3[1]))));
		fRec1[0] = ((fConst14 * fRec1[1]) + (fConst46 * (fRec2[0] + fRec2[1])));
		fRec0[0] = ((fConst45 * fRec0[1]) + (fConst44 * ((fConst42 * fRec1[0]) + (fConst47 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec33[1] = fRec33[0];
		fVec9[1] = fVec9[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec8[1] = fVec8[0];
		fRec12[1] = fRec12[0];
		fVec7[1] = fVec7[0];
		fRec14[1] = fRec14[0];
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
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec30[1] = fRec30[0];
		fVec3[1] = fVec3[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fVec2[1] = fVec2[0];
		fRec24[1] = fRec24[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fVec1[1] = fVec1[0];
		fRec13[1] = fRec13[0];
		fRec6[1] = fRec6[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		iRec7[1] = iRec7[0];
		iRec8[1] = iRec8[0];
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
	case TONE: 
		fslider3_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   TONE, 
   VOLUME, 
   FEEDBACK, 
   INTENSITY, 
   SPEED, 
} PortIndex;
*/

} // end namespace gx_vibrochump
