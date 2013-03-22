// generated from file '../src/LV2/faust/gxamp14_stereo.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp14_stereo {

class Dsp: public PluginLV2 {
private:
	int fSamplingFreq;
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
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec7[2];
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
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fVec0[2];
	double 	fConst37;
	double 	fConst38;
	double 	fRec16[2];
	double 	fConst39;
	double 	fRec15[2];
	double 	fRec14[3];
	double 	fVec1[2];
	double 	fConst40;
	double 	fConst41;
	double 	fRec13[2];
	double 	fRec12[3];
	double 	fConst42;
	double 	fRec11[3];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fRec22[2];
	double 	fRec21[3];
	double 	fVec2[2];
	double 	fConst47;
	double 	fConst48;
	double 	fRec20[2];
	double 	fRec19[3];
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fRec26[2];
	double 	fRec25[3];
	double 	fConst53;
	double 	fRec24[3];
	double 	fRec23[3];
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fVec3[2];
	double 	fConst54;
	double 	fRec10[2];
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fRec29[2];
	double 	fRec9[3];
	double 	fConst59;
	double 	fRec8[2];
	double 	fVec4[2];
	double 	fRec6[2];
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fRec30[2];
	double 	fRec5[3];
	double 	fRec4[2];
	double 	fVec5[2];
	double 	fRec3[2];
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fRec31[2];
	double 	fRec2[3];
	double 	fRec1[2];
	double 	fRec47[3];
	double 	fVec6[2];
	double 	fRec46[2];
	double 	fRec45[2];
	double 	fRec44[3];
	double 	fVec7[2];
	double 	fRec43[2];
	double 	fRec42[3];
	double 	fRec41[3];
	double 	fRec51[2];
	double 	fRec50[3];
	double 	fVec8[2];
	double 	fRec49[2];
	double 	fRec48[3];
	double 	fRec55[2];
	double 	fRec54[3];
	double 	fRec53[3];
	double 	fRec52[3];
	double 	fRec57[2];
	double 	fRec56[3];
	double 	fVec9[2];
	double 	fRec40[2];
	double 	fRec58[2];
	double 	fRec39[3];
	double 	fRec38[2];
	double 	fVec10[2];
	double 	fRec37[2];
	double 	fRec59[2];
	double 	fRec36[3];
	double 	fRec35[2];
	double 	fVec11[2];
	double 	fRec34[2];
	double 	fRec60[2];
	double 	fRec33[3];
	double 	fRec32[2];
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *input1, float *output0, float *output1);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(unsigned int samplingFreq, PluginLV2*);
	static void compute_static(int count, float *input0, float *input1, float *output0, float *output1, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "12AT7";
	name = N_("12AT7");
	mono_audio = 0;
	stereo_audio = compute_static;
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
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<3; i++) fRec44[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec43[i] = 0;
	for (int i=0; i<3; i++) fRec42[i] = 0;
	for (int i=0; i<3; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<3; i++) fRec50[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<3; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<3; i++) fRec54[i] = 0;
	for (int i=0; i<3; i++) fRec53[i] = 0;
	for (int i=0; i<3; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) fRec57[i] = 0;
	for (int i=0; i<3; i++) fRec56[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec58[i] = 0;
	for (int i=0; i<3; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec59[i] = 0;
	for (int i=0; i<3; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec60[i] = 0;
	for (int i=0; i<3; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / tan((97.38937226128358 / iConst0)));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0 / tan((20517.741620594938 / iConst0)));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = tan((942.4777960769379 / iConst0));
	fConst8 = (1.0 / faustpower<2>(fConst7));
	fConst9 = (2 * (1 - fConst8));
	fConst10 = (1.0 / fConst7);
	fConst11 = (1 + ((fConst10 - 1.0) / fConst7));
	fConst12 = (1.0 / (1 + ((1.0 + fConst10) / fConst7)));
	fConst13 = tan((3769.9111843077517 / iConst0));
	fConst14 = (1.0 / faustpower<2>(fConst13));
	fConst15 = (2 * (1 - fConst14));
	fConst16 = (1.0 / fConst13);
	fConst17 = (1 + ((fConst16 - 1.0000000000000004) / fConst13));
	fConst18 = (1 + ((fConst16 + 1.0000000000000004) / fConst13));
	fConst19 = (1.0 / fConst18);
	fConst20 = (1 + fConst16);
	fConst21 = (0 - ((1 - fConst16) / fConst20));
	fConst22 = tan((10053.096491487338 / iConst0));
	fConst23 = (1.0 / faustpower<2>(fConst22));
	fConst24 = (2 * (1 - fConst23));
	fConst25 = (1.0 / fConst22);
	fConst26 = (1 + ((fConst25 - 1.0000000000000004) / fConst22));
	fConst27 = (1 + ((1.0000000000000004 + fConst25) / fConst22));
	fConst28 = (1.0 / fConst27);
	fConst29 = (1 + fConst25);
	fConst30 = (0 - ((1 - fConst25) / fConst29));
	fConst31 = tan((47123.8898038469 / iConst0));
	fConst32 = (2 * (1 - (1.0 / faustpower<2>(fConst31))));
	fConst33 = (1.0 / fConst31);
	fConst34 = (1 + ((fConst33 - 1.414213562373095) / fConst31));
	fConst35 = (1 + ((1.414213562373095 + fConst33) / fConst31));
	fConst36 = (1.0 / fConst35);
	fConst37 = (0 - fConst1);
	fConst38 = (1.0 / (fConst2 * fConst35));
	fConst39 = (1.0 / fConst29);
	fConst40 = (0 - fConst16);
	fConst41 = (1.0 / (fConst20 * fConst27));
	fConst42 = (2 * (0 - fConst14));
	fConst43 = (1 + ((fConst10 - 1.0000000000000004) / fConst7));
	fConst44 = (1.0 / (1 + ((fConst10 + 1.0000000000000004) / fConst7)));
	fConst45 = (1 + fConst10);
	fConst46 = (0 - ((1 - fConst10) / fConst45));
	fConst47 = (0 - fConst10);
	fConst48 = (1.0 / (fConst45 * fConst18));
	fConst49 = (2 * (0 - fConst8));
	fConst50 = (1 + ((fConst16 - 1.0) / fConst13));
	fConst51 = (1.0 / (1 + ((1.0 + fConst16) / fConst13)));
	fConst52 = (0 - fConst25);
	fConst53 = (2 * (0 - fConst23));
	fConst54 = (1.0 / fConst5);
	fConst55 = (1.0 / tan((270.1769682087222 / iConst0)));
	fConst56 = (1 + fConst55);
	fConst57 = (0 - ((1 - fConst55) / fConst56));
	fConst58 = (0.027 / fConst56);
	fConst59 = (0.025 / fConst2);
	fConst60 = (1.0 / tan((414.6902302738527 / iConst0)));
	fConst61 = (1 + fConst60);
	fConst62 = (0 - ((1 - fConst60) / fConst61));
	fConst63 = (0.015 / fConst61);
	fConst64 = (1.0 / tan((609.4689747964198 / iConst0)));
	fConst65 = (1 + fConst64);
	fConst66 = (0 - ((1 - fConst64) / fConst65));
	fConst67 = (0.0082 / fConst65);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

inline void Dsp::compute(int count, float *input0, float *input1, float *output0, float *output1)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * fslider1)));
	double 	fSlow2 = (1.000000000000001e-05 * fslider2);
	double 	fSlow3 = fslider3;
	double 	fSlow4 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow5 = (fConst44 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow6 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow7 = (fConst44 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow8 = (2 * (fSlow3 - 0.5));
	double 	fSlow9 = (1 - max(0, (0 - fSlow8)));
	double 	fSlow10 = (1.25 * fSlow3);
	double 	fSlow11 = (1 - max(0, fSlow8));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec7[0] = (fSlow1 + (0.999 * fRec7[1]));
		double fTemp0 = (fConst9 * fRec11[1]);
		fRec18[0] = (fSlow2 + (0.999 * fRec18[1]));
		double fTemp1 = (double)input0[i];
		fRec17[0] = ((fTemp1 * fRec18[0]) - (fConst36 * ((fConst34 * fRec17[2]) + (fConst32 * fRec17[1]))));
		double fTemp2 = (fRec17[2] + (fRec17[0] + (2 * fRec17[1])));
		fVec0[0] = fTemp2;
		fRec16[0] = ((fConst38 * ((fConst37 * fVec0[1]) + (fConst1 * fVec0[0]))) + (fConst3 * fRec16[1]));
		fRec15[0] = ((fConst39 * (fRec16[0] + fRec16[1])) + (fConst30 * fRec15[1]));
		fRec14[0] = (fRec15[0] - (fConst28 * ((fConst26 * fRec14[2]) + (fConst24 * fRec14[1]))));
		double fTemp3 = (fRec14[2] + (fRec14[0] + (2 * fRec14[1])));
		fVec1[0] = fTemp3;
		fRec13[0] = ((fConst41 * ((fConst40 * fVec1[1]) + (fConst16 * fVec1[0]))) + (fConst21 * fRec13[1]));
		fRec12[0] = (fRec13[0] - (fConst19 * ((fConst17 * fRec12[2]) + (fConst15 * fRec12[1]))));
		fRec11[0] = ((fConst19 * (((fConst14 * fRec12[0]) + (fConst42 * fRec12[1])) + (fConst14 * fRec12[2]))) - (fConst12 * ((fConst11 * fRec11[2]) + fTemp0)));
		double fTemp4 = max(-1, min(1, (fSlow4 * (fRec11[2] + (fConst12 * (fTemp0 + (fConst11 * fRec11[0])))))));
		fRec22[0] = ((fConst41 * (fVec1[0] + fVec1[1])) + (fConst21 * fRec22[1]));
		fRec21[0] = (fRec22[0] - (fConst19 * ((fConst17 * fRec21[2]) + (fConst15 * fRec21[1]))));
		double fTemp5 = (fRec21[2] + (fRec21[0] + (2 * fRec21[1])));
		fVec2[0] = fTemp5;
		fRec20[0] = ((fConst48 * ((fConst47 * fVec2[1]) + (fConst10 * fVec2[0]))) + (fConst46 * fRec20[1]));
		fRec19[0] = (fRec20[0] - (fConst44 * ((fConst43 * fRec19[2]) + (fConst9 * fRec19[1]))));
		double fTemp6 = max(-1, min(1, (fSlow5 * (((fConst8 * fRec19[0]) + (fConst49 * fRec19[1])) + (fConst8 * fRec19[2])))));
		double fTemp7 = (fConst9 * fRec23[1]);
		double fTemp8 = (fConst15 * fRec24[1]);
		fRec26[0] = ((fConst39 * ((fConst52 * fRec16[1]) + (fConst25 * fRec16[0]))) + (fConst30 * fRec26[1]));
		fRec25[0] = (fRec26[0] - (fConst28 * ((fConst26 * fRec25[2]) + (fConst24 * fRec25[1]))));
		fRec24[0] = ((fConst28 * (((fConst23 * fRec25[0]) + (fConst53 * fRec25[1])) + (fConst23 * fRec25[2]))) - (fConst51 * ((fConst50 * fRec24[2]) + fTemp8)));
		fRec23[0] = ((fRec24[2] + (fConst51 * (fTemp8 + (fConst50 * fRec24[0])))) - (fConst12 * ((fConst11 * fRec23[2]) + fTemp7)));
		double fTemp9 = max(-1, min(1, (fSlow6 * (fRec23[2] + (fConst12 * (fTemp7 + (fConst11 * fRec23[0])))))));
		fRec28[0] = ((fConst48 * (fVec2[0] + fVec2[1])) + (fConst46 * fRec28[1]));
		fRec27[0] = (fRec28[0] - (fConst44 * ((fConst43 * fRec27[2]) + (fConst9 * fRec27[1]))));
		double fTemp10 = max(-1, min(1, (fSlow7 * (fRec27[2] + (fRec27[0] + (2 * fRec27[1]))))));
		double fTemp11 = ((1.2589412 * (fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10))))) + (1.584893192 * ((fTemp9 * (1 - (0.3333333333333333 * faustpower<2>(fTemp9)))) + ((fTemp6 * (1 - (0.3333333333333333 * faustpower<2>(fTemp6)))) + (0.8413951417869425 * (fTemp4 * (1 - (0.3333333333333333 * faustpower<2>(fTemp4)))))))));
		fVec3[0] = fTemp11;
		fRec10[0] = ((fConst54 * (fVec3[0] + fVec3[1])) + (fConst6 * fRec10[1]));
		fRec29[0] = ((fConst58 * (fRec9[1] + fRec9[2])) + (fConst57 * fRec29[1]));
		double fTemp12 = (1 - fRec18[0]);
		double fTemp13 = (fSlow11 * fRec18[0]);
		fRec9[0] = (Ftube(TUBE_TABLE_12AT7_68k, (((fTemp1 * (fTemp13 + (fTemp12 * (1 + (fSlow10 * ((4 - (4 * fabs((fTemp1 * fTemp12)))) - 1)))))) + (fRec29[0] + (fSlow9 * fRec10[0]))) - 2.617753)) - 153.04618518518518);
		fRec8[0] = ((fConst59 * ((fConst37 * fRec9[1]) + (fConst1 * fRec9[0]))) + (fConst3 * fRec8[1]));
		double fTemp14 = (fRec8[0] * fRec7[0]);
		fVec4[0] = fTemp14;
		fRec6[0] = ((fConst54 * (fVec4[0] + fVec4[1])) + (fConst6 * fRec6[1]));
		fRec30[0] = ((fConst63 * (fRec5[1] + fRec5[2])) + (fConst62 * fRec30[1]));
		fRec5[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec30[0] + fRec6[0]) - 1.887332)) - 124.17786666666666);
		fRec4[0] = ((fConst59 * ((fConst37 * fRec5[1]) + (fConst1 * fRec5[0]))) + (fConst3 * fRec4[1]));
		double fTemp15 = (fRec7[0] * fRec4[0]);
		fVec5[0] = fTemp15;
		fRec3[0] = ((fConst54 * (fVec5[0] + fVec5[1])) + (fConst6 * fRec3[1]));
		fRec31[0] = ((fConst67 * (fRec2[1] + fRec2[2])) + (fConst66 * fRec31[1]));
		fRec2[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec31[0] + fRec3[0]) - 1.256962)) - 96.7119512195122);
		fRec1[0] = ((fConst59 * ((fConst37 * fRec2[1]) + (fConst1 * fRec2[0]))) + (fConst3 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		double fTemp16 = (fConst9 * fRec41[1]);
		double fTemp17 = (double)input1[i];
		fRec47[0] = ((fTemp17 * fRec18[0]) - (fConst36 * ((fConst34 * fRec47[2]) + (fConst32 * fRec47[1]))));
		double fTemp18 = (fRec47[2] + (fRec47[0] + (2 * fRec47[1])));
		fVec6[0] = fTemp18;
		fRec46[0] = ((fConst38 * ((fConst37 * fVec6[1]) + (fConst1 * fVec6[0]))) + (fConst3 * fRec46[1]));
		fRec45[0] = ((fConst39 * (fRec46[0] + fRec46[1])) + (fConst30 * fRec45[1]));
		fRec44[0] = (fRec45[0] - (fConst28 * ((fConst26 * fRec44[2]) + (fConst24 * fRec44[1]))));
		double fTemp19 = (fRec44[2] + (fRec44[0] + (2 * fRec44[1])));
		fVec7[0] = fTemp19;
		fRec43[0] = ((fConst41 * ((fConst40 * fVec7[1]) + (fConst16 * fVec7[0]))) + (fConst21 * fRec43[1]));
		fRec42[0] = (fRec43[0] - (fConst19 * ((fConst17 * fRec42[2]) + (fConst15 * fRec42[1]))));
		fRec41[0] = ((fConst19 * (((fConst14 * fRec42[0]) + (fConst42 * fRec42[1])) + (fConst14 * fRec42[2]))) - (fConst12 * ((fConst11 * fRec41[2]) + fTemp16)));
		double fTemp20 = max(-1, min(1, (fSlow4 * (fRec41[2] + (fConst12 * (fTemp16 + (fConst11 * fRec41[0])))))));
		fRec51[0] = ((fConst41 * (fVec7[0] + fVec7[1])) + (fConst21 * fRec51[1]));
		fRec50[0] = (fRec51[0] - (fConst19 * ((fConst17 * fRec50[2]) + (fConst15 * fRec50[1]))));
		double fTemp21 = (fRec50[2] + (fRec50[0] + (2 * fRec50[1])));
		fVec8[0] = fTemp21;
		fRec49[0] = ((fConst48 * ((fConst47 * fVec8[1]) + (fConst10 * fVec8[0]))) + (fConst46 * fRec49[1]));
		fRec48[0] = (fRec49[0] - (fConst44 * ((fConst43 * fRec48[2]) + (fConst9 * fRec48[1]))));
		double fTemp22 = max(-1, min(1, (fSlow5 * (((fConst8 * fRec48[0]) + (fConst49 * fRec48[1])) + (fConst8 * fRec48[2])))));
		double fTemp23 = (fConst9 * fRec52[1]);
		double fTemp24 = (fConst15 * fRec53[1]);
		fRec55[0] = ((fConst39 * ((fConst52 * fRec46[1]) + (fConst25 * fRec46[0]))) + (fConst30 * fRec55[1]));
		fRec54[0] = (fRec55[0] - (fConst28 * ((fConst26 * fRec54[2]) + (fConst24 * fRec54[1]))));
		fRec53[0] = ((fConst28 * (((fConst23 * fRec54[0]) + (fConst53 * fRec54[1])) + (fConst23 * fRec54[2]))) - (fConst51 * ((fConst50 * fRec53[2]) + fTemp24)));
		fRec52[0] = ((fRec53[2] + (fConst51 * (fTemp24 + (fConst50 * fRec53[0])))) - (fConst12 * ((fConst11 * fRec52[2]) + fTemp23)));
		double fTemp25 = max(-1, min(1, (fSlow6 * (fRec52[2] + (fConst12 * (fTemp23 + (fConst11 * fRec52[0])))))));
		fRec57[0] = ((fConst48 * (fVec8[0] + fVec8[1])) + (fConst46 * fRec57[1]));
		fRec56[0] = (fRec57[0] - (fConst44 * ((fConst43 * fRec56[2]) + (fConst9 * fRec56[1]))));
		double fTemp26 = max(-1, min(1, (fSlow7 * (fRec56[2] + (fRec56[0] + (2 * fRec56[1]))))));
		double fTemp27 = ((1.2589412 * (fTemp26 * (1 - (0.3333333333333333 * faustpower<2>(fTemp26))))) + (1.584893192 * ((fTemp25 * (1 - (0.3333333333333333 * faustpower<2>(fTemp25)))) + ((fTemp22 * (1 - (0.3333333333333333 * faustpower<2>(fTemp22)))) + (0.8413951417869425 * (fTemp20 * (1 - (0.3333333333333333 * faustpower<2>(fTemp20)))))))));
		fVec9[0] = fTemp27;
		fRec40[0] = ((fConst54 * (fVec9[0] + fVec9[1])) + (fConst6 * fRec40[1]));
		fRec58[0] = ((fConst58 * (fRec39[1] + fRec39[2])) + (fConst57 * fRec58[1]));
		fRec39[0] = (Ftube(TUBE_TABLE_12AT7_68k, (((fTemp17 * (fTemp13 + (fTemp12 * (1 + (fSlow10 * ((4 - (4 * fabs((fTemp17 * fTemp12)))) - 1)))))) + (fRec58[0] + (fSlow9 * fRec40[0]))) - 2.617753)) - 153.04618518518518);
		fRec38[0] = ((fConst59 * ((fConst37 * fRec39[1]) + (fConst1 * fRec39[0]))) + (fConst3 * fRec38[1]));
		double fTemp28 = (fRec7[0] * fRec38[0]);
		fVec10[0] = fTemp28;
		fRec37[0] = ((fConst54 * (fVec10[0] + fVec10[1])) + (fConst6 * fRec37[1]));
		fRec59[0] = ((fConst63 * (fRec36[1] + fRec36[2])) + (fConst62 * fRec59[1]));
		fRec36[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec59[0] + fRec37[0]) - 1.887332)) - 124.17786666666666);
		fRec35[0] = ((fConst59 * ((fConst37 * fRec36[1]) + (fConst1 * fRec36[0]))) + (fConst3 * fRec35[1]));
		double fTemp29 = (fRec7[0] * fRec35[0]);
		fVec11[0] = fTemp29;
		fRec34[0] = ((fConst54 * (fVec11[0] + fVec11[1])) + (fConst6 * fRec34[1]));
		fRec60[0] = ((fConst67 * (fRec33[1] + fRec33[2])) + (fConst66 * fRec60[1]));
		fRec33[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec60[0] + fRec34[0]) - 1.256962)) - 96.7119512195122);
		fRec32[0] = ((fConst59 * ((fConst37 * fRec33[1]) + (fConst1 * fRec33[0]))) + (fConst3 * fRec32[1]));
		output1[i] = (FAUSTFLOAT)(fRec0[0] * fRec32[0]);
		// post processing
		fRec32[1] = fRec32[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec60[1] = fRec60[0];
		fRec34[1] = fRec34[0];
		fVec11[1] = fVec11[0];
		fRec35[1] = fRec35[0];
		fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
		fRec59[1] = fRec59[0];
		fRec37[1] = fRec37[0];
		fVec10[1] = fVec10[0];
		fRec38[1] = fRec38[0];
		fRec39[2] = fRec39[1]; fRec39[1] = fRec39[0];
		fRec58[1] = fRec58[0];
		fRec40[1] = fRec40[0];
		fVec9[1] = fVec9[0];
		fRec56[2] = fRec56[1]; fRec56[1] = fRec56[0];
		fRec57[1] = fRec57[0];
		fRec52[2] = fRec52[1]; fRec52[1] = fRec52[0];
		fRec53[2] = fRec53[1]; fRec53[1] = fRec53[0];
		fRec54[2] = fRec54[1]; fRec54[1] = fRec54[0];
		fRec55[1] = fRec55[0];
		fRec48[2] = fRec48[1]; fRec48[1] = fRec48[0];
		fRec49[1] = fRec49[0];
		fVec8[1] = fVec8[0];
		fRec50[2] = fRec50[1]; fRec50[1] = fRec50[0];
		fRec51[1] = fRec51[0];
		fRec41[2] = fRec41[1]; fRec41[1] = fRec41[0];
		fRec42[2] = fRec42[1]; fRec42[1] = fRec42[0];
		fRec43[1] = fRec43[0];
		fVec7[1] = fVec7[0];
		fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
		fRec45[1] = fRec45[0];
		fRec46[1] = fRec46[0];
		fVec6[1] = fVec6[0];
		fRec47[2] = fRec47[1]; fRec47[1] = fRec47[0];
		fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec31[1] = fRec31[0];
		fRec3[1] = fRec3[0];
		fVec5[1] = fVec5[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec30[1] = fRec30[0];
		fRec6[1] = fRec6[0];
		fVec4[1] = fVec4[0];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec29[1] = fRec29[0];
		fRec10[1] = fRec10[0];
		fVec3[1] = fVec3[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fVec2[1] = fVec2[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fVec1[1] = fVec1[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fVec0[1] = fVec0[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec7[1] = fRec7[0];
		fRec0[1] = fRec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
}

void Dsp::compute_static(int count, float *input0, float *input1, float *output0, float *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case DRIVE: 
		fslider3_ = (float*)data; // , 0.35, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fslider2_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
		break;
	case PREGAIN: 
		fslider1_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
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

} // end namespace gxamp14_stereo
