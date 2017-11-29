// generated from file '../src/LV2/faust/gxamp18.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp18 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec15[2];
	double 	fConst0;
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
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fRec24[3];
	double 	fVec0[2];
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fRec23[2];
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fRec22[2];
	double 	fRec21[3];
	double 	fVec1[2];
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fRec20[2];
	double 	fRec19[3];
	double 	fVec2[2];
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fRec18[2];
	double 	fRec17[3];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fConst46;
	double 	fRec26[3];
	double 	fRec25[3];
	double 	fConst47;
	double 	fRec30[2];
	double 	fRec29[3];
	double 	fConst48;
	double 	fConst49;
	double 	fRec33[2];
	double 	fRec32[3];
	double 	fConst50;
	double 	fRec31[3];
	double 	fVec3[2];
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	double 	fRec16[2];
	double 	fVec4[2];
	double 	fRec14[2];
	double 	fRec13[3];
	double 	fVec5[2];
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fRec34[2];
	double 	fRec12[2];
	double 	fConst59;
	double 	fRec11[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec35[2];
	double 	fVec6[2];
	double 	fRec10[2];
	double 	fVec7[2];
	double 	fRec9[2];
	double 	fRec8[3];
	double 	fVec8[2];
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fRec36[2];
	double 	fRec7[2];
	double 	fRec6[2];
	double 	fVec9[2];
	double 	fRec5[2];
	double 	fVec10[2];
	double 	fRec4[2];
	double 	fRec3[3];
	double 	fVec11[2];
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fRec37[2];
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
	id = "6C16";
	name = N_("6C16");
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
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<3; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
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
	fConst1 = tan((942.4777960769379 / fConst0));
	fConst2 = (1.0 / fConst1);
	fConst3 = (1 + ((fConst2 - 1.0000000000000004) / fConst1));
	fConst4 = (1.0 / faustpower<2>(fConst1));
	fConst5 = (2 * (1 - fConst4));
	fConst6 = (1.0 / (1 + ((1.0000000000000004 + fConst2) / fConst1)));
	fConst7 = tan((3769.9111843077517 / fConst0));
	fConst8 = (1.0 / fConst7);
	fConst9 = (1 + ((fConst8 - 1.0000000000000004) / fConst7));
	fConst10 = (1.0 / faustpower<2>(fConst7));
	fConst11 = (2 * (1 - fConst10));
	fConst12 = (1 + ((1.0000000000000004 + fConst8) / fConst7));
	fConst13 = (1.0 / fConst12);
	fConst14 = tan((10053.096491487338 / fConst0));
	fConst15 = (1.0 / faustpower<2>(fConst14));
	fConst16 = (2 * (1 - fConst15));
	fConst17 = (1.0 / fConst14);
	fConst18 = (1 + ((fConst17 - 1.0000000000000004) / fConst14));
	fConst19 = (1 + ((1.0000000000000004 + fConst17) / fConst14));
	fConst20 = (1.0 / fConst19);
	fConst21 = tan((47123.8898038469 / fConst0));
	fConst22 = (2 * (1 - (1.0 / faustpower<2>(fConst21))));
	fConst23 = (1.0 / fConst21);
	fConst24 = (1 + ((fConst23 - 1.414213562373095) / fConst21));
	fConst25 = (1 + ((1.414213562373095 + fConst23) / fConst21));
	fConst26 = (1.0 / fConst25);
	fConst27 = (1.0 / tan((97.38937226128358 / fConst0)));
	fConst28 = (0 - fConst27);
	fConst29 = (1 + fConst27);
	fConst30 = (1.0 / (fConst29 * fConst25));
	fConst31 = (0 - ((1 - fConst27) / fConst29));
	fConst32 = (1 + fConst17);
	fConst33 = (1.0 / fConst32);
	fConst34 = (0 - ((1 - fConst17) / fConst32));
	fConst35 = (1 + fConst8);
	fConst36 = (1.0 / (fConst35 * fConst19));
	fConst37 = (0 - ((1 - fConst8) / fConst35));
	fConst38 = (1 + fConst2);
	fConst39 = (1.0 / (fConst38 * fConst12));
	fConst40 = (0 - ((1 - fConst2) / fConst38));
	fConst41 = (1 + ((fConst2 - 1.0) / fConst1));
	fConst42 = (1.0 / (1 + ((1.0 + fConst2) / fConst1)));
	fConst43 = (1 + ((fConst8 - 1.0) / fConst7));
	fConst44 = (1.0 / (1 + ((1.0 + fConst8) / fConst7)));
	fConst45 = (0 - fConst17);
	fConst46 = (2 * (0 - fConst15));
	fConst47 = (0 - fConst2);
	fConst48 = (2 * (0 - fConst4));
	fConst49 = (0 - fConst8);
	fConst50 = (2 * (0 - fConst10));
	fConst51 = (1.0 / tan((20517.741620594938 / fConst0)));
	fConst52 = (1 + fConst51);
	fConst53 = (1.0 / fConst52);
	fConst54 = (0 - ((1 - fConst51) / fConst52));
	fConst55 = (1.0 / tan((270.1769682087222 / fConst0)));
	fConst56 = (1 + fConst55);
	fConst57 = (1.0 / fConst56);
	fConst58 = (0 - ((1 - fConst55) / fConst56));
	fConst59 = (0.025 / fConst29);
	fConst60 = (1.0 / tan((414.6902302738527 / fConst0)));
	fConst61 = (1 + fConst60);
	fConst62 = (1.0 / fConst61);
	fConst63 = (0 - ((1 - fConst60) / fConst61));
	fConst64 = (1.0 / tan((609.4689747964198 / fConst0)));
	fConst65 = (1 + fConst64);
	fConst66 = (1.0 / fConst65);
	fConst67 = (0 - ((1 - fConst64) / fConst65));
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
	double 	fSlow2 = double(fslider2);
	double 	fSlow3 = (fConst6 * pow(1e+01,(0.9 * fSlow2)));
	double 	fSlow4 = pow(1e+01,(0.8 * fSlow2));
	double 	fSlow5 = (fConst6 * pow(1e+01,(2 * fSlow2)));
	double 	fSlow6 = pow(1e+01,(1.2 * fSlow2));
	double 	fSlow7 = (2 * (fSlow2 - 0.5));
	double 	fSlow8 = (1 - max((double)0, (0 - fSlow7)));
	double 	fSlow9 = (1.25 * fSlow2);
	double 	fSlow10 = (1 - max((double)0, fSlow7));
	double 	fSlow11 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider3))));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec15[0] = (fSlow1 + (0.999 * fRec15[1]));
		double fTemp0 = (double)input0[i];
		double fTemp1 = (fTemp0 * (1 - fRec15[0]));
		double fTemp2 = (1e-15 + (fTemp0 * fRec15[0]));
		fRec24[0] = (fTemp2 - (fConst26 * ((fConst24 * fRec24[2]) + (fConst22 * fRec24[1]))));
		double fTemp3 = (fRec24[0] + (fRec24[2] + (2 * fRec24[1])));
		fVec0[0] = fTemp3;
		fRec23[0] = ((fConst31 * fRec23[1]) + (fConst30 * ((fConst27 * fVec0[0]) + (fConst28 * fVec0[1]))));
		fRec22[0] = ((fConst34 * fRec22[1]) + (fConst33 * (fRec23[1] + fRec23[0])));
		fRec21[0] = (fRec22[0] - (fConst20 * ((fConst18 * fRec21[2]) + (fConst16 * fRec21[1]))));
		double fTemp4 = (fRec21[0] + (fRec21[2] + (2 * fRec21[1])));
		fVec1[0] = fTemp4;
		fRec20[0] = ((fConst37 * fRec20[1]) + (fConst36 * (fVec1[0] + fVec1[1])));
		fRec19[0] = (fRec20[0] - (fConst13 * ((fConst11 * fRec19[1]) + (fConst9 * fRec19[2]))));
		double fTemp5 = (fRec19[0] + (fRec19[2] + (2 * fRec19[1])));
		fVec2[0] = fTemp5;
		fRec18[0] = ((fConst40 * fRec18[1]) + (fConst39 * (fVec2[0] + fVec2[1])));
		fRec17[0] = (fRec18[0] - (fConst6 * ((fConst5 * fRec17[1]) + (fConst3 * fRec17[2]))));
		double fTemp6 = max((double)-1, min((double)1, (fSlow3 * (fRec17[0] + (fRec17[2] + (2 * fRec17[1]))))));
		double fTemp7 = (fConst5 * fRec25[1]);
		double fTemp8 = (fConst11 * fRec26[1]);
		fRec28[0] = ((fConst34 * fRec28[1]) + (fConst33 * ((fConst17 * fRec23[0]) + (fConst45 * fRec23[1]))));
		fRec27[0] = (fRec28[0] - (fConst20 * ((fConst18 * fRec27[2]) + (fConst16 * fRec27[1]))));
		fRec26[0] = ((fConst20 * ((fConst46 * fRec27[1]) + (fConst15 * (fRec27[2] + fRec27[0])))) - (fConst44 * ((fConst43 * fRec26[2]) + fTemp8)));
		fRec25[0] = ((fRec26[2] + (fConst44 * (fTemp8 + (fConst43 * fRec26[0])))) - (fConst42 * ((fConst41 * fRec25[2]) + fTemp7)));
		double fTemp9 = max((double)-1, min((double)1, (fSlow4 * (fRec25[2] + (fConst42 * (fTemp7 + (fConst41 * fRec25[0])))))));
		fRec30[0] = ((fConst40 * fRec30[1]) + (fConst39 * ((fConst2 * fVec2[0]) + (fConst47 * fVec2[1]))));
		fRec29[0] = (fRec30[0] - (fConst6 * ((fConst5 * fRec29[1]) + (fConst3 * fRec29[2]))));
		double fTemp10 = max((double)-1, min((double)1, (fSlow5 * ((fConst48 * fRec29[1]) + (fConst4 * (fRec29[2] + fRec29[0]))))));
		double fTemp11 = (fConst5 * fRec31[1]);
		fRec33[0] = ((fConst37 * fRec33[1]) + (fConst36 * ((fConst8 * fVec1[0]) + (fConst49 * fVec1[1]))));
		fRec32[0] = (fRec33[0] - (fConst13 * ((fConst11 * fRec32[1]) + (fConst9 * fRec32[2]))));
		fRec31[0] = ((fConst13 * ((fConst50 * fRec32[1]) + (fConst10 * (fRec32[2] + fRec32[0])))) - (fConst42 * ((fConst41 * fRec31[2]) + fTemp11)));
		double fTemp12 = max((double)-1, min((double)1, (fSlow6 * (fRec31[2] + (fConst42 * (fTemp11 + (fConst41 * fRec31[0])))))));
		double fTemp13 = ((1.584893192 * ((0.8413951417869425 * (fTemp12 * (1 - (0.3333333333333333 * faustpower<2>(fTemp12))))) + ((fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10)))) + (fTemp9 * (1 - (0.3333333333333333 * faustpower<2>(fTemp9))))))) + (1.2589412 * (fTemp6 * (1 - (0.3333333333333333 * faustpower<2>(fTemp6))))));
		fVec3[0] = fTemp13;
		fRec16[0] = ((fConst54 * fRec16[1]) + (fConst53 * (fVec3[0] + fVec3[1])));
		double fTemp14 = (1e-15 + fTemp1);
		double fTemp15 = ((fSlow10 * fTemp2) + ((fSlow9 * ((fTemp14 * (4 - (4 * fabs(fTemp14)))) - fTemp14)) + ((fSlow8 * fRec16[0]) + fTemp1)));
		fVec4[0] = (2e-15 + fTemp15);
		fRec14[0] = ((0.9302847925323914 * (2e-15 + (fTemp15 + fVec4[1]))) - (0.8605695850647829 * fRec14[1]));
		fRec13[0] = (fRec14[0] - ((1.8405051250752198 * fRec13[1]) + (0.8612942439318627 * fRec13[2])));
		double fTemp16 = (0.027 * fRec12[1]);
		fVec5[0] = (1e-15 + fTemp16);
		fRec34[0] = ((fConst58 * fRec34[1]) + (fConst57 * (1e-15 + (fTemp16 + fVec5[1]))));
		fRec12[0] = (Ftube(TUBE_TABLE_6C16_68k, ((fRec34[0] + (0.9254498422517706 * (fRec13[0] + (fRec13[2] + (2.0 * fRec13[1]))))) - 2.921806)) - 141.78496296296294);
		fRec11[0] = ((fConst31 * fRec11[1]) + (fConst59 * ((fConst27 * fRec12[0]) + (fConst28 * fRec12[1]))));
		fRec35[0] = (fSlow11 + (0.999 * fRec35[1]));
		double fTemp17 = (fRec35[0] * fRec11[0]);
		fVec6[0] = fTemp17;
		fRec10[0] = ((fConst54 * fRec10[1]) + (fConst53 * (fVec6[0] + fVec6[1])));
		fVec7[0] = (1e-15 + fRec10[0]);
		fRec9[0] = ((0.9302847925323914 * (1e-15 + (fRec10[0] + fVec7[1]))) - (0.8605695850647829 * fRec9[1]));
		fRec8[0] = (fRec9[0] - ((1.8405051250752198 * fRec8[1]) + (0.8612942439318627 * fRec8[2])));
		double fTemp18 = (0.015 * fRec7[1]);
		fVec8[0] = (1e-15 + fTemp18);
		fRec36[0] = ((fConst63 * fRec36[1]) + (fConst62 * (1e-15 + (fTemp18 + fVec8[1]))));
		fRec7[0] = (Ftube(TUBE_TABLE_6C16_250k, ((fRec36[0] + (0.9254498422517706 * (fRec8[0] + (fRec8[2] + (2.0 * fRec8[1]))))) - 2.097743)) - 110.15046666666666);
		fRec6[0] = ((fConst31 * fRec6[1]) + (fConst59 * ((fConst27 * fRec7[0]) + (fConst28 * fRec7[1]))));
		double fTemp19 = (fRec35[0] * fRec6[0]);
		fVec9[0] = fTemp19;
		fRec5[0] = ((fConst54 * fRec5[1]) + (fConst53 * (fVec9[0] + fVec9[1])));
		fVec10[0] = (1e-15 + fRec5[0]);
		fRec4[0] = ((0.9302847925323914 * (1e-15 + (fRec5[0] + fVec10[1]))) - (0.8605695850647829 * fRec4[1]));
		fRec3[0] = (fRec4[0] - ((1.8405051250752198 * fRec3[1]) + (0.8612942439318627 * fRec3[2])));
		double fTemp20 = (0.0082 * fRec2[1]);
		fVec11[0] = (1e-15 + fTemp20);
		fRec37[0] = ((fConst67 * fRec37[1]) + (fConst66 * (1e-15 + (fTemp20 + fVec11[1]))));
		fRec2[0] = (Ftube(TUBE_TABLE_6C16_250k, ((fRec37[0] + (0.9254498422517706 * (fRec3[0] + (fRec3[2] + (2.0 * fRec3[1]))))) - 1.378742)) - 81.86073170731709);
		fRec1[0] = ((fConst31 * fRec1[1]) + (fConst59 * ((fConst27 * fRec2[0]) + (fConst28 * fRec2[1]))));
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec37[1] = fRec37[0];
		fVec11[1] = fVec11[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fVec10[1] = fVec10[0];
		fRec5[1] = fRec5[0];
		fVec9[1] = fVec9[0];
		fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec36[1] = fRec36[0];
		fVec8[1] = fVec8[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fVec7[1] = fVec7[0];
		fRec10[1] = fRec10[0];
		fVec6[1] = fVec6[0];
		fRec35[1] = fRec35[0];
		fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fRec34[1] = fRec34[0];
		fVec5[1] = fVec5[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fVec4[1] = fVec4[0];
		fRec16[1] = fRec16[0];
		fVec3[1] = fVec3[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
		fRec33[1] = fRec33[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fVec2[1] = fVec2[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fVec1[1] = fVec1[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fVec0[1] = fVec0[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec15[1] = fRec15[0];
		fRec0[1] = fRec0[0];
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
		fslider2_ = (float*)data; // , 0.35, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fslider1_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
		break;
	case PREGAIN: 
		fslider3_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
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

} // end namespace gxamp18
