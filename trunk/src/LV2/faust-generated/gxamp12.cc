// generated from file '../src/LV2/faust/gxamp12.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp12 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec4[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec6[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec20[2];
	double 	fVec0[2];
	double 	fRec19[2];
	double 	fRec18[3];
	double 	fVec1[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fRec21[2];
	double 	fRec17[2];
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fRec16[2];
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fRec15[2];
	double 	fVec2[2];
	double 	fRec14[2];
	double 	fRec13[3];
	double 	fVec3[2];
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fRec22[2];
	double 	fRec12[2];
	double 	fRec11[2];
	double 	fVec4[2];
	double 	fRec10[2];
	double 	fRec9[3];
	double 	fVec5[2];
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fRec23[2];
	double 	fRec8[2];
	double 	fRec7[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
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
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fRec32[3];
	double 	fVec6[2];
	double 	fConst48;
	double 	fRec31[2];
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fRec30[2];
	double 	fRec29[3];
	double 	fVec7[2];
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fVec8[2];
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fRec26[2];
	double 	fRec25[3];
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fRec35[2];
	double 	fRec34[3];
	double 	fConst61;
	double 	fRec33[3];
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fRec39[2];
	double 	fRec38[3];
	double 	fConst65;
	double 	fRec37[3];
	double 	fRec36[3];
	double 	fConst66;
	double 	fRec41[2];
	double 	fRec40[3];
	double 	fConst67;
	double 	fVec9[2];
	double 	fRec24[2];
	double 	fVec10[2];
	double 	fRec5[2];
	double 	fVec11[2];
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fVec12[2];
	double 	fRec42[2];
	double 	fRec1[2];
	double 	fConst68;
	double 	fRec0[2];
	double 	fVec13[2];
	double 	fRec45[2];
	double 	fRec44[2];
	double 	fRec43[2];
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
	id = "pre 6DJ8/ master 6V6";
	name = N_("pre 6DJ8/ master 6V6");
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
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<3; i++) fRec34[i] = 0;
	for (int i=0; i<3; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<3; i++) fRec38[i] = 0;
	for (int i=0; i<3; i++) fRec37[i] = 0;
	for (int i=0; i<3; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<3; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fVec12[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fVec13[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<2; i++) fRec43[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst2 = (1 + fConst1);
	fConst3 = (1.0 / fConst2);
	fConst4 = (0 - ((1 - fConst1) / fConst2));
	fConst5 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst6 = (0 - fConst5);
	fConst7 = (1 + fConst5);
	fConst8 = (0.05 / fConst7);
	fConst9 = (0 - ((1 - fConst5) / fConst7));
	fConst10 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst11 = (1 + fConst10);
	fConst12 = (1.0 / fConst11);
	fConst13 = (0 - ((1 - fConst10) / fConst11));
	fConst14 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst15 = (1 + fConst14);
	fConst16 = (1.0 / fConst15);
	fConst17 = (0 - ((1 - fConst14) / fConst15));
	fConst18 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst19 = (1 + fConst18);
	fConst20 = (1.0 / fConst19);
	fConst21 = (0 - ((1 - fConst18) / fConst19));
	fConst22 = tan((942.4777960769379 / double(iConst0)));
	fConst23 = (1.0 / faustpower<2>(fConst22));
	fConst24 = (2 * (1 - fConst23));
	fConst25 = (1.0 / fConst22);
	fConst26 = (1 + ((fConst25 - 1.0000000000000004) / fConst22));
	fConst27 = (1.0 / (1 + ((1.0000000000000004 + fConst25) / fConst22)));
	fConst28 = tan((3769.9111843077517 / double(iConst0)));
	fConst29 = (1.0 / faustpower<2>(fConst28));
	fConst30 = (2 * (1 - fConst29));
	fConst31 = (1.0 / fConst28);
	fConst32 = (1 + ((fConst31 - 1.0000000000000004) / fConst28));
	fConst33 = (1 + ((1.0000000000000004 + fConst31) / fConst28));
	fConst34 = (1.0 / fConst33);
	fConst35 = tan((10053.096491487338 / double(iConst0)));
	fConst36 = (1.0 / faustpower<2>(fConst35));
	fConst37 = (2 * (1 - fConst36));
	fConst38 = (1.0 / fConst35);
	fConst39 = (1 + ((fConst38 - 1.0000000000000004) / fConst35));
	fConst40 = (1 + ((1.0000000000000004 + fConst38) / fConst35));
	fConst41 = (1.0 / fConst40);
	fConst42 = tan((47123.8898038469 / double(iConst0)));
	fConst43 = (2 * (1 - (1.0 / faustpower<2>(fConst42))));
	fConst44 = (1.0 / fConst42);
	fConst45 = (1 + ((fConst44 - 1.414213562373095) / fConst42));
	fConst46 = (1 + ((1.414213562373095 + fConst44) / fConst42));
	fConst47 = (1.0 / fConst46);
	fConst48 = (1.0 / (fConst7 * fConst46));
	fConst49 = (1 + fConst38);
	fConst50 = (1.0 / fConst49);
	fConst51 = (0 - ((1 - fConst38) / fConst49));
	fConst52 = (1 + fConst31);
	fConst53 = (1.0 / (fConst52 * fConst40));
	fConst54 = (0 - ((1 - fConst31) / fConst52));
	fConst55 = (1 + fConst25);
	fConst56 = (1.0 / (fConst55 * fConst33));
	fConst57 = (0 - ((1 - fConst25) / fConst55));
	fConst58 = (1 + ((fConst25 - 1.0) / fConst22));
	fConst59 = (1.0 / (1 + ((1.0 + fConst25) / fConst22)));
	fConst60 = (0 - fConst31);
	fConst61 = (2 * (0 - fConst29));
	fConst62 = (1 + ((fConst31 - 1.0) / fConst28));
	fConst63 = (1.0 / (1 + ((1.0 + fConst31) / fConst28)));
	fConst64 = (0 - fConst38);
	fConst65 = (2 * (0 - fConst36));
	fConst66 = (0 - fConst25);
	fConst67 = (2 * (0 - fConst23));
	fConst68 = (0.025 / fConst7);
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
#define fslider3 (*fslider3_)
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider0))));
	double 	fSlow1 = (1.000000000000001e-05 * double(fslider1));
	double 	fSlow2 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider2))));
	double 	fSlow3 = double(fslider3);
	double 	fSlow4 = (2 * (fSlow3 - 0.5));
	double 	fSlow5 = (1 - max((double)0, fSlow4));
	double 	fSlow6 = (1.25 * fSlow3);
	double 	fSlow7 = (fConst27 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow8 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow9 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow10 = (fConst27 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow11 = (1 - max((double)0, (0 - fSlow4)));
	for (int i=0; i<count; i++) {
		fRec4[0] = ((0.999 * fRec4[1]) + fSlow0);
		fRec6[0] = (fSlow1 + (0.999 * fRec6[1]));
		fRec20[0] = ((0.999 * fRec20[1]) + fSlow2);
		double fTemp0 = (1e-15 + ((double)input0[i] * fRec20[0]));
		fVec0[0] = fTemp0;
		fRec19[0] = ((0.9302847925323914 * (fVec0[0] + fVec0[1])) - (0.8605695850647829 * fRec19[1]));
		fRec18[0] = (fRec19[0] - ((1.8405051250752198 * fRec18[1]) + (0.8612942439318627 * fRec18[2])));
		double fTemp1 = (1e-15 + (0.027 * fRec17[1]));
		fVec1[0] = fTemp1;
		fRec21[0] = ((fConst4 * fRec21[1]) + (fConst3 * (fVec1[0] + fVec1[1])));
		fRec17[0] = (Ftube(TUBE_TABLE_6DJ8_68k, ((fRec21[0] + (0.9254498422517706 * (fRec18[2] + (fRec18[0] + (2.0 * fRec18[1]))))) - 1.863946)) - 60.96496296296296);
		fRec16[0] = ((fConst9 * fRec16[1]) + (fConst8 * ((fConst5 * fRec17[0]) + (fConst6 * fRec17[1]))));
		fRec15[0] = ((fConst13 * fRec15[1]) + (fConst12 * (fRec16[0] + fRec16[1])));
		double fTemp2 = (1e-15 + fRec15[0]);
		fVec2[0] = fTemp2;
		fRec14[0] = ((0.9302847925323914 * (fVec2[0] + fVec2[1])) - (0.8605695850647829 * fRec14[1]));
		fRec13[0] = (fRec14[0] - ((1.8405051250752198 * fRec13[1]) + (0.8612942439318627 * fRec13[2])));
		double fTemp3 = (1e-15 + (0.015 * fRec12[1]));
		fVec3[0] = fTemp3;
		fRec22[0] = ((fConst17 * fRec22[1]) + (fConst16 * (fVec3[0] + fVec3[1])));
		fRec12[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec22[0] + (0.9254498422517706 * (fRec13[2] + (fRec13[0] + (2.0 * fRec13[1]))))) - 1.271609)) - 45.22606666666667);
		fRec11[0] = ((fConst9 * fRec11[1]) + (fConst8 * ((fConst5 * fRec12[0]) + (fConst6 * fRec12[1]))));
		double fTemp4 = (1e-15 + fRec11[0]);
		fVec4[0] = fTemp4;
		fRec10[0] = ((0.9302847925323914 * (fVec4[0] + fVec4[1])) - (0.8605695850647829 * fRec10[1]));
		fRec9[0] = (fRec10[0] - ((1.8405051250752198 * fRec9[1]) + (0.8612942439318627 * fRec9[2])));
		double fTemp5 = (1e-15 + (0.0082 * fRec8[1]));
		fVec5[0] = fTemp5;
		fRec23[0] = ((fConst21 * fRec23[1]) + (fConst20 * (fVec5[0] + fVec5[1])));
		fRec8[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec23[0] + (0.9254498422517706 * (fRec9[2] + (fRec9[0] + (2.0 * fRec9[1]))))) - 0.797043)) - 32.799634146341475);
		fRec7[0] = ((fConst9 * fRec7[1]) + (fConst8 * ((fConst5 * fRec8[0]) + (fConst6 * fRec8[1]))));
		double fTemp6 = (1e-15 + (fRec7[0] * fRec6[0]));
		double fTemp7 = (fRec7[0] * (1 - fRec6[0]));
		double fTemp8 = (1e-15 + fTemp7);
		fRec32[0] = (fTemp6 - (fConst47 * ((fConst45 * fRec32[2]) + (fConst43 * fRec32[1]))));
		double fTemp9 = (fRec32[2] + (fRec32[0] + (2 * fRec32[1])));
		fVec6[0] = fTemp9;
		fRec31[0] = ((fConst9 * fRec31[1]) + (fConst48 * ((fConst5 * fVec6[0]) + (fConst6 * fVec6[1]))));
		fRec30[0] = ((fConst51 * fRec30[1]) + (fConst50 * (fRec31[0] + fRec31[1])));
		fRec29[0] = (fRec30[0] - (fConst41 * ((fConst39 * fRec29[2]) + (fConst37 * fRec29[1]))));
		double fTemp10 = (fRec29[2] + (fRec29[0] + (2 * fRec29[1])));
		fVec7[0] = fTemp10;
		fRec28[0] = ((fConst54 * fRec28[1]) + (fConst53 * (fVec7[0] + fVec7[1])));
		fRec27[0] = (fRec28[0] - (fConst34 * ((fConst32 * fRec27[2]) + (fConst30 * fRec27[1]))));
		double fTemp11 = (fRec27[2] + (fRec27[0] + (2 * fRec27[1])));
		fVec8[0] = fTemp11;
		fRec26[0] = ((fConst57 * fRec26[1]) + (fConst56 * (fVec8[0] + fVec8[1])));
		fRec25[0] = (fRec26[0] - (fConst27 * ((fConst26 * fRec25[2]) + (fConst24 * fRec25[1]))));
		double fTemp12 = max((double)-1, min((double)1, (fSlow7 * (fRec25[2] + (fRec25[0] + (2 * fRec25[1]))))));
		double fTemp13 = (fConst24 * fRec33[1]);
		fRec35[0] = ((fConst54 * fRec35[1]) + (fConst53 * ((fConst31 * fVec7[0]) + (fConst60 * fVec7[1]))));
		fRec34[0] = (fRec35[0] - (fConst34 * ((fConst32 * fRec34[2]) + (fConst30 * fRec34[1]))));
		fRec33[0] = ((fConst34 * (((fConst29 * fRec34[0]) + (fConst61 * fRec34[1])) + (fConst29 * fRec34[2]))) - (fConst59 * ((fConst58 * fRec33[2]) + fTemp13)));
		double fTemp14 = max((double)-1, min((double)1, (fSlow8 * (fRec33[2] + (fConst59 * (fTemp13 + (fConst58 * fRec33[0])))))));
		double fTemp15 = (fConst24 * fRec36[1]);
		double fTemp16 = (fConst30 * fRec37[1]);
		fRec39[0] = ((fConst51 * fRec39[1]) + (fConst50 * ((fConst38 * fRec31[0]) + (fConst64 * fRec31[1]))));
		fRec38[0] = (fRec39[0] - (fConst41 * ((fConst39 * fRec38[2]) + (fConst37 * fRec38[1]))));
		fRec37[0] = ((fConst41 * (((fConst36 * fRec38[0]) + (fConst65 * fRec38[1])) + (fConst36 * fRec38[2]))) - (fConst63 * ((fConst62 * fRec37[2]) + fTemp16)));
		fRec36[0] = ((fRec37[2] + (fConst63 * (fTemp16 + (fConst62 * fRec37[0])))) - (fConst59 * ((fConst58 * fRec36[2]) + fTemp15)));
		double fTemp17 = max((double)-1, min((double)1, (fSlow9 * (fRec36[2] + (fConst59 * (fTemp15 + (fConst58 * fRec36[0])))))));
		fRec41[0] = ((fConst57 * fRec41[1]) + (fConst56 * ((fConst25 * fVec8[0]) + (fConst66 * fVec8[1]))));
		fRec40[0] = (fRec41[0] - (fConst27 * ((fConst26 * fRec40[2]) + (fConst24 * fRec40[1]))));
		double fTemp18 = max((double)-1, min((double)1, (fSlow10 * (((fConst23 * fRec40[0]) + (fConst67 * fRec40[1])) + (fConst23 * fRec40[2])))));
		double fTemp19 = ((1.584893192 * ((fTemp18 * (1 - (0.3333333333333333 * faustpower<2>(fTemp18)))) + ((fTemp17 * (1 - (0.3333333333333333 * faustpower<2>(fTemp17)))) + (0.8413951417869425 * (fTemp14 * (1 - (0.3333333333333333 * faustpower<2>(fTemp14)))))))) + (1.2589412 * (fTemp12 * (1 - (0.3333333333333333 * faustpower<2>(fTemp12))))));
		fVec9[0] = fTemp19;
		fRec24[0] = ((fConst13 * fRec24[1]) + (fConst12 * (fVec9[0] + fVec9[1])));
		double fTemp20 = (1e-15 + ((fSlow11 * fRec24[0]) + ((fTemp7 + (fSlow6 * ((fTemp8 * (4 - (4 * fabs(fTemp8)))) - fTemp8))) + (fSlow5 * fTemp6))));
		fVec10[0] = fTemp20;
		fRec5[0] = ((fConst13 * fRec5[1]) + (fConst12 * (fVec10[0] + fVec10[1])));
		double fTemp21 = (1e-15 + (fRec5[0] * fRec4[0]));
		fVec11[0] = fTemp21;
		fRec3[0] = ((0.9302847925323914 * (fVec11[0] + fVec11[1])) - (0.8605695850647829 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.8612942439318627 * fRec2[2])));
		double fTemp22 = (0.9254498422517706 * (fRec2[2] + (fRec2[0] + (2.0 * fRec2[1]))));
		double fTemp23 = (1e-15 + (0.0082 * fRec1[1]));
		fVec12[0] = fTemp23;
		fRec42[0] = ((fConst13 * fRec42[1]) + (fConst12 * (fVec12[0] + fVec12[1])));
		fRec1[0] = (Ftube(TUBE_TABLE_6V6_68k, ((fRec42[0] + fTemp22) - 1.13074)) - 112.10487804878048);
		fRec0[0] = ((fConst9 * fRec0[1]) + (fConst68 * ((fConst5 * fRec1[0]) + (fConst6 * fRec1[1]))));
		double fTemp24 = (1e-15 + (0.0082 * fRec44[1]));
		fVec13[0] = fTemp24;
		fRec45[0] = ((fConst13 * fRec45[1]) + (fConst12 * (fVec13[0] + fVec13[1])));
		fRec44[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec45[0] + fTemp22) - 1.130462)) - 112.13878048780487);
		fRec43[0] = ((fConst9 * fRec43[1]) + (fConst68 * ((fConst5 * fRec44[0]) + (fConst6 * fRec44[1]))));
		output0[i] = (FAUSTFLOAT)(fRec43[0] + fRec0[0]);
		// post processing
		fRec43[1] = fRec43[0];
		fRec44[1] = fRec44[0];
		fRec45[1] = fRec45[0];
		fVec13[1] = fVec13[0];
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec42[1] = fRec42[0];
		fVec12[1] = fVec12[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fVec11[1] = fVec11[0];
		fRec5[1] = fRec5[0];
		fVec10[1] = fVec10[0];
		fRec24[1] = fRec24[0];
		fVec9[1] = fVec9[0];
		fRec40[2] = fRec40[1]; fRec40[1] = fRec40[0];
		fRec41[1] = fRec41[0];
		fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
		fRec37[2] = fRec37[1]; fRec37[1] = fRec37[0];
		fRec38[2] = fRec38[1]; fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec34[2] = fRec34[1]; fRec34[1] = fRec34[0];
		fRec35[1] = fRec35[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fVec8[1] = fVec8[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fVec7[1] = fVec7[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fVec6[1] = fVec6[0];
		fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec23[1] = fRec23[0];
		fVec5[1] = fVec5[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fVec4[1] = fVec4[0];
		fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fRec22[1] = fRec22[0];
		fVec3[1] = fVec3[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fVec2[1] = fVec2[0];
		fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec21[1] = fRec21[0];
		fVec1[1] = fVec1[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fVec0[1] = fVec0[0];
		fRec20[1] = fRec20[0];
		fRec6[1] = fRec6[0];
		fRec4[1] = fRec4[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
}
		
void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case DRIVE: 
		fslider3_ = (float*)data; // , 0.35, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fslider1_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
		break;
	case PREGAIN: 
		fslider2_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
		break;
	case GAIN1: 
		fslider0_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
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
   DRIVE, 
   WET_DRY, 
   PREGAIN, 
   GAIN1, 
} PortIndex;
*/

} // end namespace gxamp12
