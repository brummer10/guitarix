// generated from file '../src/LV2/faust/gxamp_stereo.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp_stereo {

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
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec7[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec10[2];
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fVec0[2];
	double 	fConst10;
	double 	fRec11[2];
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
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fRec19[3];
	double 	fVec1[2];
	double 	fConst41;
	double 	fConst42;
	double 	fRec18[2];
	double 	fConst43;
	double 	fRec17[2];
	double 	fRec16[3];
	double 	fVec2[2];
	double 	fConst44;
	double 	fConst45;
	double 	fRec15[2];
	double 	fRec14[3];
	double 	fConst46;
	double 	fRec13[3];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fVec3[2];
	double 	fConst51;
	double 	fConst52;
	double 	fRec21[2];
	double 	fRec20[3];
	double 	fConst53;
	double 	fConst54;
	double 	fConst55;
	double 	fConst56;
	double 	fRec27[2];
	double 	fRec26[3];
	double 	fConst57;
	double 	fRec25[3];
	double 	fRec24[3];
	double 	fRec29[2];
	double 	fRec28[3];
	double 	fVec4[2];
	double 	fConst58;
	double 	fRec12[2];
	double 	fRec9[2];
	double 	fConst59;
	double 	fRec8[2];
	double 	fVec5[2];
	double 	fRec6[2];
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fVec6[2];
	double 	fConst63;
	double 	fRec30[2];
	double 	fRec5[2];
	double 	fRec4[2];
	double 	fVec7[2];
	double 	fRec3[2];
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fVec8[2];
	double 	fConst67;
	double 	fRec31[2];
	double 	fRec2[2];
	double 	fRec1[2];
	double 	fVec9[2];
	double 	fRec40[2];
	double 	fRec48[3];
	double 	fVec10[2];
	double 	fRec47[2];
	double 	fRec46[2];
	double 	fRec45[3];
	double 	fVec11[2];
	double 	fRec44[2];
	double 	fRec43[3];
	double 	fRec42[3];
	double 	fRec52[2];
	double 	fRec51[3];
	double 	fVec12[2];
	double 	fRec50[2];
	double 	fRec49[3];
	double 	fRec56[2];
	double 	fRec55[3];
	double 	fRec54[3];
	double 	fRec53[3];
	double 	fRec58[2];
	double 	fRec57[3];
	double 	fVec13[2];
	double 	fRec41[2];
	double 	fRec39[2];
	double 	fRec38[2];
	double 	fVec14[2];
	double 	fRec37[2];
	double 	fVec15[2];
	double 	fRec59[2];
	double 	fRec36[2];
	double 	fRec35[2];
	double 	fVec16[2];
	double 	fRec34[2];
	double 	fVec17[2];
	double 	fRec60[2];
	double 	fRec33[2];
	double 	fRec32[2];
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, float *input0, float *input1, float *output0, float *output1);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
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
	id = "12ax7";
	name = N_("12ax7");
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
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<3; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<3; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<3; i++) fRec43[i] = 0;
	for (int i=0; i<3; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<3; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fVec12[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<3; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) fRec56[i] = 0;
	for (int i=0; i<3; i++) fRec55[i] = 0;
	for (int i=0; i<3; i++) fRec54[i] = 0;
	for (int i=0; i<3; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) fRec58[i] = 0;
	for (int i=0; i<3; i++) fRec57[i] = 0;
	for (int i=0; i<2; i++) fVec13[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fVec14[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fVec15[i] = 0;
	for (int i=0; i<2; i++) fRec59[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fVec16[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fVec17[i] = 0;
	for (int i=0; i<2; i++) fRec60[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / tan((97.38937226128358 / iConst0)));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0 / tan((20517.741620594938 / iConst0)));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = (1.0 / tan((270.1769682087222 / iConst0)));
	fConst8 = (1 + fConst7);
	fConst9 = (0 - ((1 - fConst7) / fConst8));
	fConst10 = (1.0 / fConst8);
	fConst11 = tan((942.4777960769379 / iConst0));
	fConst12 = (1.0 / faustpower<2>(fConst11));
	fConst13 = (2 * (1 - fConst12));
	fConst14 = (1.0 / fConst11);
	fConst15 = (1 + ((fConst14 - 1.0) / fConst11));
	fConst16 = (1.0 / (1 + ((1.0 + fConst14) / fConst11)));
	fConst17 = tan((3769.9111843077517 / iConst0));
	fConst18 = (1.0 / faustpower<2>(fConst17));
	fConst19 = (2 * (1 - fConst18));
	fConst20 = (1.0 / fConst17);
	fConst21 = (1 + ((fConst20 - 1.0000000000000004) / fConst17));
	fConst22 = (1 + ((fConst20 + 1.0000000000000004) / fConst17));
	fConst23 = (1.0 / fConst22);
	fConst24 = (1 + fConst20);
	fConst25 = (0 - ((1 - fConst20) / fConst24));
	fConst26 = tan((10053.096491487338 / iConst0));
	fConst27 = (1.0 / faustpower<2>(fConst26));
	fConst28 = (2 * (1 - fConst27));
	fConst29 = (1.0 / fConst26);
	fConst30 = (1 + ((fConst29 - 1.0000000000000004) / fConst26));
	fConst31 = (1 + ((1.0000000000000004 + fConst29) / fConst26));
	fConst32 = (1.0 / fConst31);
	fConst33 = (1 + fConst29);
	fConst34 = (0 - ((1 - fConst29) / fConst33));
	fConst35 = tan((47123.8898038469 / iConst0));
	fConst36 = (2 * (1 - (1.0 / faustpower<2>(fConst35))));
	fConst37 = (1.0 / fConst35);
	fConst38 = (1 + ((fConst37 - 1.414213562373095) / fConst35));
	fConst39 = (1 + ((1.414213562373095 + fConst37) / fConst35));
	fConst40 = (1.0 / fConst39);
	fConst41 = (0 - fConst1);
	fConst42 = (1.0 / (fConst2 * fConst39));
	fConst43 = (1.0 / fConst33);
	fConst44 = (0 - fConst20);
	fConst45 = (1.0 / (fConst24 * fConst31));
	fConst46 = (2 * (0 - fConst18));
	fConst47 = (1 + ((fConst14 - 1.0000000000000004) / fConst11));
	fConst48 = (1.0 / (1 + ((fConst14 + 1.0000000000000004) / fConst11)));
	fConst49 = (1 + fConst14);
	fConst50 = (0 - ((1 - fConst14) / fConst49));
	fConst51 = (0 - fConst14);
	fConst52 = (1.0 / (fConst49 * fConst22));
	fConst53 = (2 * (0 - fConst12));
	fConst54 = (1 + ((fConst20 - 1.0) / fConst17));
	fConst55 = (1.0 / (1 + ((1.0 + fConst20) / fConst17)));
	fConst56 = (0 - fConst29);
	fConst57 = (2 * (0 - fConst27));
	fConst58 = (1.0 / fConst5);
	fConst59 = (0.025 / fConst2);
	fConst60 = (1.0 / tan((414.6902302738527 / iConst0)));
	fConst61 = (1 + fConst60);
	fConst62 = (0 - ((1 - fConst60) / fConst61));
	fConst63 = (1.0 / fConst61);
	fConst64 = (1.0 / tan((609.4689747964198 / iConst0)));
	fConst65 = (1 + fConst64);
	fConst66 = (0 - ((1 - fConst64) / fConst65));
	fConst67 = (1.0 / fConst65);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
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
	double 	fSlow5 = (fConst48 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow6 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow7 = (fConst48 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow8 = (2 * (fSlow3 - 0.5));
	double 	fSlow9 = (1 - max(0, (0 - fSlow8)));
	double 	fSlow10 = (1 - max(0, fSlow8));
	double 	fSlow11 = (1.25 * fSlow3);
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec7[0] = (fSlow1 + (0.999 * fRec7[1]));
		fRec10[0] = (fSlow2 + (0.999 * fRec10[1]));
		double fTemp0 = (1 - fRec10[0]);
		double fTemp1 = (double)input0[i];
		double fTemp2 = (fTemp1 * fTemp0);
		double fTemp3 = (1e-15 + (0.027 * fRec9[1]));
		fVec0[0] = fTemp3;
		fRec11[0] = ((fConst10 * (fVec0[0] + fVec0[1])) + (fConst9 * fRec11[1]));
		double fTemp4 = (fConst13 * fRec13[1]);
		double fTemp5 = (1e-15 + (fTemp1 * fRec10[0]));
		fRec19[0] = (fTemp5 - (fConst40 * ((fConst38 * fRec19[2]) + (fConst36 * fRec19[1]))));
		double fTemp6 = (fRec19[2] + (fRec19[0] + (2 * fRec19[1])));
		fVec1[0] = fTemp6;
		fRec18[0] = ((fConst42 * ((fConst41 * fVec1[1]) + (fConst1 * fVec1[0]))) + (fConst3 * fRec18[1]));
		fRec17[0] = ((fConst43 * (fRec18[0] + fRec18[1])) + (fConst34 * fRec17[1]));
		fRec16[0] = (fRec17[0] - (fConst32 * ((fConst30 * fRec16[2]) + (fConst28 * fRec16[1]))));
		double fTemp7 = (fRec16[2] + (fRec16[0] + (2 * fRec16[1])));
		fVec2[0] = fTemp7;
		fRec15[0] = ((fConst45 * ((fConst44 * fVec2[1]) + (fConst20 * fVec2[0]))) + (fConst25 * fRec15[1]));
		fRec14[0] = (fRec15[0] - (fConst23 * ((fConst21 * fRec14[2]) + (fConst19 * fRec14[1]))));
		fRec13[0] = ((fConst23 * (((fConst18 * fRec14[0]) + (fConst46 * fRec14[1])) + (fConst18 * fRec14[2]))) - (fConst16 * ((fConst15 * fRec13[2]) + fTemp4)));
		double fTemp8 = max(-1, min(1, (fSlow4 * (fRec13[2] + (fConst16 * (fTemp4 + (fConst15 * fRec13[0])))))));
		fRec23[0] = ((fConst45 * (fVec2[0] + fVec2[1])) + (fConst25 * fRec23[1]));
		fRec22[0] = (fRec23[0] - (fConst23 * ((fConst21 * fRec22[2]) + (fConst19 * fRec22[1]))));
		double fTemp9 = (fRec22[2] + (fRec22[0] + (2 * fRec22[1])));
		fVec3[0] = fTemp9;
		fRec21[0] = ((fConst52 * ((fConst51 * fVec3[1]) + (fConst14 * fVec3[0]))) + (fConst50 * fRec21[1]));
		fRec20[0] = (fRec21[0] - (fConst48 * ((fConst47 * fRec20[2]) + (fConst13 * fRec20[1]))));
		double fTemp10 = max(-1, min(1, (fSlow5 * (((fConst12 * fRec20[0]) + (fConst53 * fRec20[1])) + (fConst12 * fRec20[2])))));
		double fTemp11 = (fConst13 * fRec24[1]);
		double fTemp12 = (fConst19 * fRec25[1]);
		fRec27[0] = ((fConst43 * ((fConst56 * fRec18[1]) + (fConst29 * fRec18[0]))) + (fConst34 * fRec27[1]));
		fRec26[0] = (fRec27[0] - (fConst32 * ((fConst30 * fRec26[2]) + (fConst28 * fRec26[1]))));
		fRec25[0] = ((fConst32 * (((fConst27 * fRec26[0]) + (fConst57 * fRec26[1])) + (fConst27 * fRec26[2]))) - (fConst55 * ((fConst54 * fRec25[2]) + fTemp12)));
		fRec24[0] = ((fRec25[2] + (fConst55 * (fTemp12 + (fConst54 * fRec25[0])))) - (fConst16 * ((fConst15 * fRec24[2]) + fTemp11)));
		double fTemp13 = max(-1, min(1, (fSlow6 * (fRec24[2] + (fConst16 * (fTemp11 + (fConst15 * fRec24[0])))))));
		fRec29[0] = ((fConst52 * (fVec3[0] + fVec3[1])) + (fConst50 * fRec29[1]));
		fRec28[0] = (fRec29[0] - (fConst48 * ((fConst47 * fRec28[2]) + (fConst13 * fRec28[1]))));
		double fTemp14 = max(-1, min(1, (fSlow7 * (fRec28[2] + (fRec28[0] + (2 * fRec28[1]))))));
		double fTemp15 = ((1.2589412 * (fTemp14 * (1 - (0.3333333333333333 * faustpower<2>(fTemp14))))) + (1.584893192 * ((fTemp13 * (1 - (0.3333333333333333 * faustpower<2>(fTemp13)))) + ((fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10)))) + (0.8413951417869425 * (fTemp8 * (1 - (0.3333333333333333 * faustpower<2>(fTemp8)))))))));
		fVec4[0] = fTemp15;
		fRec12[0] = ((fConst58 * (fVec4[0] + fVec4[1])) + (fConst6 * fRec12[1]));
		double fTemp16 = (1e-15 + fTemp2);
		fRec9[0] = (Ftube(TUBE_TABLE_12AX7_68k, (((fSlow11 * ((fTemp16 * (4 - (4 * fabs(fTemp16)))) - fTemp16)) + ((fSlow10 * fTemp5) + ((fSlow9 * fRec12[0]) + (fRec11[0] + fTemp2)))) - 1.581655999999998)) - 191.42014814814814);
		fRec8[0] = ((fConst59 * ((fConst41 * fRec9[1]) + (fConst1 * fRec9[0]))) + (fConst3 * fRec8[1]));
		double fTemp17 = (fRec8[0] * fRec7[0]);
		fVec5[0] = fTemp17;
		fRec6[0] = ((fConst58 * (fVec5[0] + fVec5[1])) + (fConst6 * fRec6[1]));
		double fTemp18 = (1e-15 + (0.015 * fRec5[1]));
		fVec6[0] = fTemp18;
		fRec30[0] = ((fConst63 * (fVec6[0] + fVec6[1])) + (fConst62 * fRec30[1]));
		fRec5[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec30[0] + fRec6[0]) - 1.204284999999999)) - 169.71433333333334);
		fRec4[0] = ((fConst59 * ((fConst41 * fRec5[1]) + (fConst1 * fRec5[0]))) + (fConst3 * fRec4[1]));
		double fTemp19 = (fRec7[0] * fRec4[0]);
		fVec7[0] = fTemp19;
		fRec3[0] = ((fConst58 * (fVec7[0] + fVec7[1])) + (fConst6 * fRec3[1]));
		double fTemp20 = (1e-15 + (0.0082 * fRec2[1]));
		fVec8[0] = fTemp20;
		fRec31[0] = ((fConst67 * (fVec8[0] + fVec8[1])) + (fConst66 * fRec31[1]));
		fRec2[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec31[0] + fRec3[0]) - 0.840702999999999)) - 147.47524390243905);
		fRec1[0] = ((fConst59 * ((fConst41 * fRec2[1]) + (fConst1 * fRec2[0]))) + (fConst3 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		double fTemp21 = (double)input1[i];
		double fTemp22 = (fTemp21 * fTemp0);
		double fTemp23 = (1e-15 + (0.027 * fRec39[1]));
		fVec9[0] = fTemp23;
		fRec40[0] = ((fConst10 * (fVec9[0] + fVec9[1])) + (fConst9 * fRec40[1]));
		double fTemp24 = (fConst13 * fRec42[1]);
		double fTemp25 = (1e-15 + (fTemp21 * fRec10[0]));
		fRec48[0] = (fTemp25 - (fConst40 * ((fConst38 * fRec48[2]) + (fConst36 * fRec48[1]))));
		double fTemp26 = (fRec48[2] + (fRec48[0] + (2 * fRec48[1])));
		fVec10[0] = fTemp26;
		fRec47[0] = ((fConst42 * ((fConst41 * fVec10[1]) + (fConst1 * fVec10[0]))) + (fConst3 * fRec47[1]));
		fRec46[0] = ((fConst43 * (fRec47[0] + fRec47[1])) + (fConst34 * fRec46[1]));
		fRec45[0] = (fRec46[0] - (fConst32 * ((fConst30 * fRec45[2]) + (fConst28 * fRec45[1]))));
		double fTemp27 = (fRec45[2] + (fRec45[0] + (2 * fRec45[1])));
		fVec11[0] = fTemp27;
		fRec44[0] = ((fConst45 * ((fConst44 * fVec11[1]) + (fConst20 * fVec11[0]))) + (fConst25 * fRec44[1]));
		fRec43[0] = (fRec44[0] - (fConst23 * ((fConst21 * fRec43[2]) + (fConst19 * fRec43[1]))));
		fRec42[0] = ((fConst23 * (((fConst18 * fRec43[0]) + (fConst46 * fRec43[1])) + (fConst18 * fRec43[2]))) - (fConst16 * ((fConst15 * fRec42[2]) + fTemp24)));
		double fTemp28 = max(-1, min(1, (fSlow4 * (fRec42[2] + (fConst16 * (fTemp24 + (fConst15 * fRec42[0])))))));
		fRec52[0] = ((fConst45 * (fVec11[0] + fVec11[1])) + (fConst25 * fRec52[1]));
		fRec51[0] = (fRec52[0] - (fConst23 * ((fConst21 * fRec51[2]) + (fConst19 * fRec51[1]))));
		double fTemp29 = (fRec51[2] + (fRec51[0] + (2 * fRec51[1])));
		fVec12[0] = fTemp29;
		fRec50[0] = ((fConst52 * ((fConst51 * fVec12[1]) + (fConst14 * fVec12[0]))) + (fConst50 * fRec50[1]));
		fRec49[0] = (fRec50[0] - (fConst48 * ((fConst47 * fRec49[2]) + (fConst13 * fRec49[1]))));
		double fTemp30 = max(-1, min(1, (fSlow5 * (((fConst12 * fRec49[0]) + (fConst53 * fRec49[1])) + (fConst12 * fRec49[2])))));
		double fTemp31 = (fConst13 * fRec53[1]);
		double fTemp32 = (fConst19 * fRec54[1]);
		fRec56[0] = ((fConst43 * ((fConst56 * fRec47[1]) + (fConst29 * fRec47[0]))) + (fConst34 * fRec56[1]));
		fRec55[0] = (fRec56[0] - (fConst32 * ((fConst30 * fRec55[2]) + (fConst28 * fRec55[1]))));
		fRec54[0] = ((fConst32 * (((fConst27 * fRec55[0]) + (fConst57 * fRec55[1])) + (fConst27 * fRec55[2]))) - (fConst55 * ((fConst54 * fRec54[2]) + fTemp32)));
		fRec53[0] = ((fRec54[2] + (fConst55 * (fTemp32 + (fConst54 * fRec54[0])))) - (fConst16 * ((fConst15 * fRec53[2]) + fTemp31)));
		double fTemp33 = max(-1, min(1, (fSlow6 * (fRec53[2] + (fConst16 * (fTemp31 + (fConst15 * fRec53[0])))))));
		fRec58[0] = ((fConst52 * (fVec12[0] + fVec12[1])) + (fConst50 * fRec58[1]));
		fRec57[0] = (fRec58[0] - (fConst48 * ((fConst47 * fRec57[2]) + (fConst13 * fRec57[1]))));
		double fTemp34 = max(-1, min(1, (fSlow7 * (fRec57[2] + (fRec57[0] + (2 * fRec57[1]))))));
		double fTemp35 = ((1.2589412 * (fTemp34 * (1 - (0.3333333333333333 * faustpower<2>(fTemp34))))) + (1.584893192 * ((fTemp33 * (1 - (0.3333333333333333 * faustpower<2>(fTemp33)))) + ((fTemp30 * (1 - (0.3333333333333333 * faustpower<2>(fTemp30)))) + (0.8413951417869425 * (fTemp28 * (1 - (0.3333333333333333 * faustpower<2>(fTemp28)))))))));
		fVec13[0] = fTemp35;
		fRec41[0] = ((fConst58 * (fVec13[0] + fVec13[1])) + (fConst6 * fRec41[1]));
		double fTemp36 = (1e-15 + fTemp22);
		fRec39[0] = (Ftube(TUBE_TABLE_12AX7_68k, (((fSlow11 * ((fTemp36 * (4 - (4 * fabs(fTemp36)))) - fTemp36)) + ((fSlow10 * fTemp25) + ((fSlow9 * fRec41[0]) + (fRec40[0] + fTemp22)))) - 1.581655999999998)) - 191.42014814814814);
		fRec38[0] = ((fConst59 * ((fConst41 * fRec39[1]) + (fConst1 * fRec39[0]))) + (fConst3 * fRec38[1]));
		double fTemp37 = (fRec7[0] * fRec38[0]);
		fVec14[0] = fTemp37;
		fRec37[0] = ((fConst58 * (fVec14[0] + fVec14[1])) + (fConst6 * fRec37[1]));
		double fTemp38 = (1e-15 + (0.015 * fRec36[1]));
		fVec15[0] = fTemp38;
		fRec59[0] = ((fConst63 * (fVec15[0] + fVec15[1])) + (fConst62 * fRec59[1]));
		fRec36[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec59[0] + fRec37[0]) - 1.204284999999999)) - 169.71433333333334);
		fRec35[0] = ((fConst59 * ((fConst41 * fRec36[1]) + (fConst1 * fRec36[0]))) + (fConst3 * fRec35[1]));
		double fTemp39 = (fRec7[0] * fRec35[0]);
		fVec16[0] = fTemp39;
		fRec34[0] = ((fConst58 * (fVec16[0] + fVec16[1])) + (fConst6 * fRec34[1]));
		double fTemp40 = (1e-15 + (0.0082 * fRec33[1]));
		fVec17[0] = fTemp40;
		fRec60[0] = ((fConst67 * (fVec17[0] + fVec17[1])) + (fConst66 * fRec60[1]));
		fRec33[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec60[0] + fRec34[0]) - 0.840702999999999)) - 147.47524390243905);
		fRec32[0] = ((fConst59 * ((fConst41 * fRec33[1]) + (fConst1 * fRec33[0]))) + (fConst3 * fRec32[1]));
		output1[i] = (FAUSTFLOAT)(fRec0[0] * fRec32[0]);
		// post processing
		fRec32[1] = fRec32[0];
		fRec33[1] = fRec33[0];
		fRec60[1] = fRec60[0];
		fVec17[1] = fVec17[0];
		fRec34[1] = fRec34[0];
		fVec16[1] = fVec16[0];
		fRec35[1] = fRec35[0];
		fRec36[1] = fRec36[0];
		fRec59[1] = fRec59[0];
		fVec15[1] = fVec15[0];
		fRec37[1] = fRec37[0];
		fVec14[1] = fVec14[0];
		fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec41[1] = fRec41[0];
		fVec13[1] = fVec13[0];
		fRec57[2] = fRec57[1]; fRec57[1] = fRec57[0];
		fRec58[1] = fRec58[0];
		fRec53[2] = fRec53[1]; fRec53[1] = fRec53[0];
		fRec54[2] = fRec54[1]; fRec54[1] = fRec54[0];
		fRec55[2] = fRec55[1]; fRec55[1] = fRec55[0];
		fRec56[1] = fRec56[0];
		fRec49[2] = fRec49[1]; fRec49[1] = fRec49[0];
		fRec50[1] = fRec50[0];
		fVec12[1] = fVec12[0];
		fRec51[2] = fRec51[1]; fRec51[1] = fRec51[0];
		fRec52[1] = fRec52[0];
		fRec42[2] = fRec42[1]; fRec42[1] = fRec42[0];
		fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
		fRec44[1] = fRec44[0];
		fVec11[1] = fVec11[0];
		fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
		fRec46[1] = fRec46[0];
		fRec47[1] = fRec47[0];
		fVec10[1] = fVec10[0];
		fRec48[2] = fRec48[1]; fRec48[1] = fRec48[0];
		fRec40[1] = fRec40[0];
		fVec9[1] = fVec9[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec31[1] = fRec31[0];
		fVec8[1] = fVec8[0];
		fRec3[1] = fRec3[0];
		fVec7[1] = fVec7[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec30[1] = fRec30[0];
		fVec6[1] = fVec6[0];
		fRec6[1] = fRec6[0];
		fVec5[1] = fVec5[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec12[1] = fRec12[0];
		fVec4[1] = fVec4[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fVec3[1] = fVec3[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec2[1] = fVec2[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fVec1[1] = fVec1[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec11[1] = fRec11[0];
		fVec0[1] = fVec0[0];
		fRec10[1] = fRec10[0];
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

} // end namespace gxamp_stereo
