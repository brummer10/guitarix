// generated from file '../src/LV2/faust/gxamp9_stereo.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp9_stereo {

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
	double 	fRec8[2];
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
	double 	fRec22[2];
	int 	IOTA;
	double 	fVec0[32768];
	int 	iConst37;
	double 	fRec21[2];
	double 	fConst38;
	double 	fRec20[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec23[2];
	double 	fRec19[3];
	double 	fVec1[2];
	double 	fConst39;
	double 	fConst40;
	double 	fRec18[2];
	double 	fConst41;
	double 	fRec17[2];
	double 	fRec16[3];
	double 	fVec2[2];
	double 	fConst42;
	double 	fConst43;
	double 	fRec15[2];
	double 	fRec14[3];
	double 	fConst44;
	double 	fRec13[3];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fRec27[2];
	double 	fRec26[3];
	double 	fVec3[2];
	double 	fConst49;
	double 	fConst50;
	double 	fRec25[2];
	double 	fRec24[3];
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	double 	fRec31[2];
	double 	fRec30[3];
	double 	fConst55;
	double 	fRec29[3];
	double 	fRec28[3];
	double 	fRec33[2];
	double 	fRec32[3];
	double 	fVec4[2];
	double 	fConst56;
	double 	fRec12[2];
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fRec34[2];
	double 	fRec11[3];
	double 	fConst61;
	double 	fRec10[2];
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fRec37[2];
	double 	fRec36[3];
	double 	fRec35[2];
	double 	fRec9[2];
	double 	fVec5[2];
	double 	fRec7[2];
	double 	fRec38[2];
	double 	fRec6[3];
	double 	fRec5[2];
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fRec41[2];
	double 	fRec40[3];
	double 	fRec39[2];
	double 	fRec4[2];
	double 	fRec3[2];
	double 	fRec42[2];
	double 	fRec2[3];
	double 	fRec1[2];
	double 	fRec63[2];
	double 	fVec6[32768];
	double 	fRec62[2];
	double 	fRec61[2];
	double 	fRec60[3];
	double 	fVec7[2];
	double 	fRec59[2];
	double 	fRec58[2];
	double 	fRec57[3];
	double 	fVec8[2];
	double 	fRec56[2];
	double 	fRec55[3];
	double 	fRec54[3];
	double 	fRec67[2];
	double 	fRec66[3];
	double 	fVec9[2];
	double 	fRec65[2];
	double 	fRec64[3];
	double 	fRec71[2];
	double 	fRec70[3];
	double 	fRec69[3];
	double 	fRec68[3];
	double 	fRec73[2];
	double 	fRec72[3];
	double 	fVec10[2];
	double 	fRec53[2];
	double 	fRec74[2];
	double 	fRec52[3];
	double 	fRec51[2];
	double 	fRec77[2];
	double 	fRec76[3];
	double 	fRec75[2];
	double 	fRec50[2];
	double 	fVec11[2];
	double 	fRec49[2];
	double 	fRec78[2];
	double 	fRec48[3];
	double 	fRec47[2];
	double 	fRec81[2];
	double 	fRec80[3];
	double 	fRec79[2];
	double 	fRec46[2];
	double 	fRec45[2];
	double 	fRec82[2];
	double 	fRec44[3];
	double 	fRec43[2];
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
	id = "12ax7 feedback";
	name = N_("12ax7 feedback");
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
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<32768; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<3; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<3; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<3; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec63[i] = 0;
	for (int i=0; i<32768; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec62[i] = 0;
	for (int i=0; i<2; i++) fRec61[i] = 0;
	for (int i=0; i<3; i++) fRec60[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec59[i] = 0;
	for (int i=0; i<2; i++) fRec58[i] = 0;
	for (int i=0; i<3; i++) fRec57[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec56[i] = 0;
	for (int i=0; i<3; i++) fRec55[i] = 0;
	for (int i=0; i<3; i++) fRec54[i] = 0;
	for (int i=0; i<2; i++) fRec67[i] = 0;
	for (int i=0; i<3; i++) fRec66[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec65[i] = 0;
	for (int i=0; i<3; i++) fRec64[i] = 0;
	for (int i=0; i<2; i++) fRec71[i] = 0;
	for (int i=0; i<3; i++) fRec70[i] = 0;
	for (int i=0; i<3; i++) fRec69[i] = 0;
	for (int i=0; i<3; i++) fRec68[i] = 0;
	for (int i=0; i<2; i++) fRec73[i] = 0;
	for (int i=0; i<3; i++) fRec72[i] = 0;
	for (int i=0; i<2; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) fRec74[i] = 0;
	for (int i=0; i<3; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fRec77[i] = 0;
	for (int i=0; i<3; i++) fRec76[i] = 0;
	for (int i=0; i<2; i++) fRec75[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<2; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) fRec78[i] = 0;
	for (int i=0; i<3; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fRec81[i] = 0;
	for (int i=0; i<3; i++) fRec80[i] = 0;
	for (int i=0; i<2; i++) fRec79[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fRec82[i] = 0;
	for (int i=0; i<3; i++) fRec44[i] = 0;
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
	IOTA = 0;
	iConst37 = int((int((0.1111111111111111 * iConst0)) & 65535));
	fConst38 = (0.009000000000000008 / iConst0);
	fConst39 = (0 - fConst1);
	fConst40 = (1.0 / (fConst2 * fConst35));
	fConst41 = (1.0 / fConst29);
	fConst42 = (0 - fConst16);
	fConst43 = (1.0 / (fConst20 * fConst27));
	fConst44 = (2 * (0 - fConst14));
	fConst45 = (1 + ((fConst10 - 1.0000000000000004) / fConst7));
	fConst46 = (1.0 / (1 + ((fConst10 + 1.0000000000000004) / fConst7)));
	fConst47 = (1 + fConst10);
	fConst48 = (0 - ((1 - fConst10) / fConst47));
	fConst49 = (0 - fConst10);
	fConst50 = (1.0 / (fConst47 * fConst18));
	fConst51 = (2 * (0 - fConst8));
	fConst52 = (1 + ((fConst16 - 1.0) / fConst13));
	fConst53 = (1.0 / (1 + ((1.0 + fConst16) / fConst13)));
	fConst54 = (0 - fConst25);
	fConst55 = (2 * (0 - fConst23));
	fConst56 = (1.0 / fConst5);
	fConst57 = (1.0 / tan((270.1769682087222 / iConst0)));
	fConst58 = (1 + fConst57);
	fConst59 = (0 - ((1 - fConst57) / fConst58));
	fConst60 = (0.027 / fConst58);
	fConst61 = (0.025 / fConst2);
	fConst62 = (1.0 / tan((414.6902302738527 / iConst0)));
	fConst63 = (1 + fConst62);
	fConst64 = (0 - ((1 - fConst62) / fConst63));
	fConst65 = (0.015 / fConst63);
	fConst66 = (1.0 / tan((609.4689747964198 / iConst0)));
	fConst67 = (1 + fConst66);
	fConst68 = (0 - ((1 - fConst66) / fConst67));
	fConst69 = (0.0082 / fConst67);
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
	double 	fSlow5 = pow(1e+01,(2 * fSlow3));
	double 	fSlow6 = (fConst46 * fSlow5);
	double 	fSlow7 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow8 = (fConst46 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow9 = (2 * (fSlow3 - 0.5));
	double 	fSlow10 = (1 - max(0, (0 - fSlow9)));
	double 	fSlow11 = (1.25 * fSlow3);
	double 	fSlow12 = (0.024937655860349125 * (1 - max(0, fSlow9)));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec8[0] = (fSlow1 + (0.999 * fRec8[1]));
		double fTemp0 = (fConst9 * fRec13[1]);
		double fTemp1 = (double)input0[i];
		double fTemp2 = fabs(fTemp1);
		fRec22[0] = ((9.999999999998899e-05 * fTemp2) + (0.9999 * fRec22[1]));
		double fTemp3 = max(fRec22[0], fTemp2);
		fVec0[IOTA&32767] = fTemp3;
		fRec21[0] = ((fVec0[IOTA&32767] + fRec21[1]) - fVec0[(IOTA-iConst37)&32767]);
		fRec20[0] = ((fConst38 * fRec21[0]) + (0.999 * fRec20[1]));
		double fTemp4 = max(-1, min(-0.01, (fVec0[IOTA&32767] - (1.0 + (1.02 * fRec20[0])))));
		double fTemp5 = (0 - fTemp4);
		double fTemp6 = (40.1 * fTemp5);
		double fTemp7 = max(-600, fTemp6);
		double fTemp8 = (0 - fTemp7);
		double fTemp9 = (fTemp1 - fTemp4);
		double fTemp10 = (40.1 * fTemp9);
		double fTemp11 = max(-600, fTemp10);
		double fTemp12 = (0 - fTemp11);
		double fTemp13 = (((int((fabs(fTemp10) > 0.0001)))?((int((fTemp11 < -50)))?(exp(fTemp11) * fTemp12):(fTemp11 / (1 - exp(fTemp12)))):(1 + (fTemp9 * (20.05 + (134.00083333333336 * fTemp9))))) - ((int((fabs(fTemp6) > 0.0001)))?((int((fTemp7 < -50)))?(exp(fTemp7) * fTemp8):(fTemp7 / (1 - exp(fTemp8)))):(1 + (fTemp5 * (20.05 + (134.00083333333336 * fTemp5))))));
		fRec23[0] = (fSlow2 + (0.999 * fRec23[1]));
		double fTemp14 = (0.024937655860349125 * (fRec23[0] * fTemp13));
		fRec19[0] = (fTemp14 - (fConst36 * ((fConst34 * fRec19[2]) + (fConst32 * fRec19[1]))));
		double fTemp15 = (fRec19[2] + (fRec19[0] + (2 * fRec19[1])));
		fVec1[0] = fTemp15;
		fRec18[0] = ((fConst40 * ((fConst39 * fVec1[1]) + (fConst1 * fVec1[0]))) + (fConst3 * fRec18[1]));
		fRec17[0] = ((fConst41 * (fRec18[0] + fRec18[1])) + (fConst30 * fRec17[1]));
		fRec16[0] = (fRec17[0] - (fConst28 * ((fConst26 * fRec16[2]) + (fConst24 * fRec16[1]))));
		double fTemp16 = (fRec16[2] + (fRec16[0] + (2 * fRec16[1])));
		fVec2[0] = fTemp16;
		fRec15[0] = ((fConst43 * ((fConst42 * fVec2[1]) + (fConst16 * fVec2[0]))) + (fConst21 * fRec15[1]));
		fRec14[0] = (fRec15[0] - (fConst19 * ((fConst17 * fRec14[2]) + (fConst15 * fRec14[1]))));
		fRec13[0] = ((fConst19 * (((fConst14 * fRec14[0]) + (fConst44 * fRec14[1])) + (fConst14 * fRec14[2]))) - (fConst12 * ((fConst11 * fRec13[2]) + fTemp0)));
		double fTemp17 = max(-1, min(1, (fSlow4 * (fRec13[2] + (fConst12 * (fTemp0 + (fConst11 * fRec13[0])))))));
		fRec27[0] = ((fConst43 * (fVec2[0] + fVec2[1])) + (fConst21 * fRec27[1]));
		fRec26[0] = (fRec27[0] - (fConst19 * ((fConst17 * fRec26[2]) + (fConst15 * fRec26[1]))));
		double fTemp18 = (fRec26[2] + (fRec26[0] + (2 * fRec26[1])));
		fVec3[0] = fTemp18;
		fRec25[0] = ((fConst50 * ((fConst49 * fVec3[1]) + (fConst10 * fVec3[0]))) + (fConst48 * fRec25[1]));
		fRec24[0] = (fRec25[0] - (fConst46 * ((fConst45 * fRec24[2]) + (fConst9 * fRec24[1]))));
		double fTemp19 = max(-1, min(1, (fSlow6 * (((fConst8 * fRec24[0]) + (fConst51 * fRec24[1])) + (fConst8 * fRec24[2])))));
		double fTemp20 = (fConst9 * fRec28[1]);
		double fTemp21 = (fConst15 * fRec29[1]);
		fRec31[0] = ((fConst41 * ((fConst54 * fRec18[1]) + (fConst25 * fRec18[0]))) + (fConst30 * fRec31[1]));
		fRec30[0] = (fRec31[0] - (fConst28 * ((fConst26 * fRec30[2]) + (fConst24 * fRec30[1]))));
		fRec29[0] = ((fConst28 * (((fConst23 * fRec30[0]) + (fConst55 * fRec30[1])) + (fConst23 * fRec30[2]))) - (fConst53 * ((fConst52 * fRec29[2]) + fTemp21)));
		fRec28[0] = ((fRec29[2] + (fConst53 * (fTemp21 + (fConst52 * fRec29[0])))) - (fConst12 * ((fConst11 * fRec28[2]) + fTemp20)));
		double fTemp22 = max(-1, min(1, (fSlow7 * (fRec28[2] + (fConst12 * (fTemp20 + (fConst11 * fRec28[0])))))));
		fRec33[0] = ((fConst50 * (fVec3[0] + fVec3[1])) + (fConst48 * fRec33[1]));
		fRec32[0] = (fRec33[0] - (fConst46 * ((fConst45 * fRec32[2]) + (fConst9 * fRec32[1]))));
		double fTemp23 = max(-1, min(1, (fSlow8 * (fRec32[2] + (fRec32[0] + (2 * fRec32[1]))))));
		double fTemp24 = ((1.2589412 * (fTemp23 * (1 - (0.3333333333333333 * faustpower<2>(fTemp23))))) + (1.584893192 * ((fTemp22 * (1 - (0.3333333333333333 * faustpower<2>(fTemp22)))) + ((fTemp19 * (1 - (0.3333333333333333 * faustpower<2>(fTemp19)))) + (0.8413951417869425 * (fTemp17 * (1 - (0.3333333333333333 * faustpower<2>(fTemp17)))))))));
		fVec4[0] = fTemp24;
		fRec12[0] = ((fConst56 * (fVec4[0] + fVec4[1])) + (fConst6 * fRec12[1]));
		fRec34[0] = ((fConst60 * (fRec11[1] + fRec11[2])) + (fConst59 * fRec34[1]));
		double fTemp25 = max(-1, min(1, (fSlow5 * max(-0.7, min(0.7, fTemp14)))));
		double fTemp26 = (1 - fRec23[0]);
		double fTemp27 = (fSlow12 * fRec23[0]);
		fRec11[0] = (Ftube(TUBE_TABLE_12AX7_68k, (((fTemp13 * (fTemp27 + (fTemp26 * (0.024937655860349125 + (fSlow11 * ((0.0997506234413965 - (0.0997506234413965 * fabs((0.024937655860349125 * (fTemp26 * fTemp13))))) - 0.024937655860349125)))))) + ((0.5 * (fTemp25 * (1 - (0.3333333333333333 * faustpower<2>(fTemp25))))) + (fRec34[0] + (fSlow10 * fRec12[0])))) - 1.5816559999999988)) - 191.42014814814814);
		fRec10[0] = ((fConst61 * ((fConst39 * fRec11[1]) + (fConst1 * fRec11[0]))) + (fConst3 * fRec10[1]));
		fRec37[0] = ((fConst65 * (fRec36[1] + fRec36[2])) + (fConst64 * fRec37[1]));
		fRec36[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec37[0] + fRec9[1]) - 1.204284999999999)) - 169.71433333333334);
		fRec35[0] = ((fConst61 * ((fConst39 * fRec36[1]) + (fConst1 * fRec36[0]))) + (fConst3 * fRec35[1]));
		fRec9[0] = ((0.6 * fRec35[0]) - fRec10[0]);
		double fTemp28 = (fRec9[0] * fRec8[0]);
		fVec5[0] = fTemp28;
		fRec7[0] = ((fConst56 * (fVec5[0] + fVec5[1])) + (fConst6 * fRec7[1]));
		fRec38[0] = ((fConst65 * (fRec6[1] + fRec6[2])) + (fConst64 * fRec38[1]));
		fRec6[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec38[0] + fRec7[0]) - 1.204284999999999)) - 169.71433333333334);
		fRec5[0] = ((fConst61 * ((fConst39 * fRec6[1]) + (fConst1 * fRec6[0]))) + (fConst3 * fRec5[1]));
		fRec41[0] = ((fConst69 * (fRec40[1] + fRec40[2])) + (fConst68 * fRec41[1]));
		fRec40[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec41[0] + fRec4[1]) - 0.840701999999999)) - 147.47536585365856);
		fRec39[0] = ((fConst61 * ((fConst39 * fRec40[1]) + (fConst1 * fRec40[0]))) + (fConst3 * fRec39[1]));
		fRec4[0] = ((0.6 * fRec39[0]) + fRec5[0]);
		fRec3[0] = ((fConst56 * (fRec4[0] + fRec4[1])) + (fConst6 * fRec3[1]));
		fRec42[0] = ((fConst69 * (fRec2[1] + fRec2[2])) + (fConst68 * fRec42[1]));
		fRec2[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec42[0] + fRec3[0]) - 0.840701999999999)) - 147.47536585365856);
		fRec1[0] = ((fConst61 * ((fConst39 * fRec2[1]) + (fConst1 * fRec2[0]))) + (fConst3 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		double fTemp29 = (fConst9 * fRec54[1]);
		double fTemp30 = (double)input1[i];
		double fTemp31 = fabs(fTemp30);
		fRec63[0] = ((9.999999999998899e-05 * fTemp31) + (0.9999 * fRec63[1]));
		double fTemp32 = max(fRec63[0], fTemp31);
		fVec6[IOTA&32767] = fTemp32;
		fRec62[0] = ((fVec6[IOTA&32767] + fRec62[1]) - fVec6[(IOTA-iConst37)&32767]);
		fRec61[0] = ((fConst38 * fRec62[0]) + (0.999 * fRec61[1]));
		double fTemp33 = max(-1, min(-0.01, (fVec6[IOTA&32767] - (1.0 + (1.02 * fRec61[0])))));
		double fTemp34 = (0 - fTemp33);
		double fTemp35 = (40.1 * fTemp34);
		double fTemp36 = max(-600, fTemp35);
		double fTemp37 = (0 - fTemp36);
		double fTemp38 = (fTemp30 - fTemp33);
		double fTemp39 = (40.1 * fTemp38);
		double fTemp40 = max(-600, fTemp39);
		double fTemp41 = (0 - fTemp40);
		double fTemp42 = (((int((fabs(fTemp39) > 0.0001)))?((int((fTemp40 < -50)))?(exp(fTemp40) * fTemp41):(fTemp40 / (1 - exp(fTemp41)))):(1 + (fTemp38 * (20.05 + (134.00083333333336 * fTemp38))))) - ((int((fabs(fTemp35) > 0.0001)))?((int((fTemp36 < -50)))?(exp(fTemp36) * fTemp37):(fTemp36 / (1 - exp(fTemp37)))):(1 + (fTemp34 * (20.05 + (134.00083333333336 * fTemp34))))));
		double fTemp43 = (0.024937655860349125 * (fRec23[0] * fTemp42));
		fRec60[0] = (fTemp43 - (fConst36 * ((fConst34 * fRec60[2]) + (fConst32 * fRec60[1]))));
		double fTemp44 = (fRec60[2] + (fRec60[0] + (2 * fRec60[1])));
		fVec7[0] = fTemp44;
		fRec59[0] = ((fConst40 * ((fConst39 * fVec7[1]) + (fConst1 * fVec7[0]))) + (fConst3 * fRec59[1]));
		fRec58[0] = ((fConst41 * (fRec59[0] + fRec59[1])) + (fConst30 * fRec58[1]));
		fRec57[0] = (fRec58[0] - (fConst28 * ((fConst26 * fRec57[2]) + (fConst24 * fRec57[1]))));
		double fTemp45 = (fRec57[2] + (fRec57[0] + (2 * fRec57[1])));
		fVec8[0] = fTemp45;
		fRec56[0] = ((fConst43 * ((fConst42 * fVec8[1]) + (fConst16 * fVec8[0]))) + (fConst21 * fRec56[1]));
		fRec55[0] = (fRec56[0] - (fConst19 * ((fConst17 * fRec55[2]) + (fConst15 * fRec55[1]))));
		fRec54[0] = ((fConst19 * (((fConst14 * fRec55[0]) + (fConst44 * fRec55[1])) + (fConst14 * fRec55[2]))) - (fConst12 * ((fConst11 * fRec54[2]) + fTemp29)));
		double fTemp46 = max(-1, min(1, (fSlow4 * (fRec54[2] + (fConst12 * (fTemp29 + (fConst11 * fRec54[0])))))));
		fRec67[0] = ((fConst43 * (fVec8[0] + fVec8[1])) + (fConst21 * fRec67[1]));
		fRec66[0] = (fRec67[0] - (fConst19 * ((fConst17 * fRec66[2]) + (fConst15 * fRec66[1]))));
		double fTemp47 = (fRec66[2] + (fRec66[0] + (2 * fRec66[1])));
		fVec9[0] = fTemp47;
		fRec65[0] = ((fConst50 * ((fConst49 * fVec9[1]) + (fConst10 * fVec9[0]))) + (fConst48 * fRec65[1]));
		fRec64[0] = (fRec65[0] - (fConst46 * ((fConst45 * fRec64[2]) + (fConst9 * fRec64[1]))));
		double fTemp48 = max(-1, min(1, (fSlow6 * (((fConst8 * fRec64[0]) + (fConst51 * fRec64[1])) + (fConst8 * fRec64[2])))));
		double fTemp49 = (fConst9 * fRec68[1]);
		double fTemp50 = (fConst15 * fRec69[1]);
		fRec71[0] = ((fConst41 * ((fConst54 * fRec59[1]) + (fConst25 * fRec59[0]))) + (fConst30 * fRec71[1]));
		fRec70[0] = (fRec71[0] - (fConst28 * ((fConst26 * fRec70[2]) + (fConst24 * fRec70[1]))));
		fRec69[0] = ((fConst28 * (((fConst23 * fRec70[0]) + (fConst55 * fRec70[1])) + (fConst23 * fRec70[2]))) - (fConst53 * ((fConst52 * fRec69[2]) + fTemp50)));
		fRec68[0] = ((fRec69[2] + (fConst53 * (fTemp50 + (fConst52 * fRec69[0])))) - (fConst12 * ((fConst11 * fRec68[2]) + fTemp49)));
		double fTemp51 = max(-1, min(1, (fSlow7 * (fRec68[2] + (fConst12 * (fTemp49 + (fConst11 * fRec68[0])))))));
		fRec73[0] = ((fConst50 * (fVec9[0] + fVec9[1])) + (fConst48 * fRec73[1]));
		fRec72[0] = (fRec73[0] - (fConst46 * ((fConst45 * fRec72[2]) + (fConst9 * fRec72[1]))));
		double fTemp52 = max(-1, min(1, (fSlow8 * (fRec72[2] + (fRec72[0] + (2 * fRec72[1]))))));
		double fTemp53 = ((1.2589412 * (fTemp52 * (1 - (0.3333333333333333 * faustpower<2>(fTemp52))))) + (1.584893192 * ((fTemp51 * (1 - (0.3333333333333333 * faustpower<2>(fTemp51)))) + ((fTemp48 * (1 - (0.3333333333333333 * faustpower<2>(fTemp48)))) + (0.8413951417869425 * (fTemp46 * (1 - (0.3333333333333333 * faustpower<2>(fTemp46)))))))));
		fVec10[0] = fTemp53;
		fRec53[0] = ((fConst56 * (fVec10[0] + fVec10[1])) + (fConst6 * fRec53[1]));
		fRec74[0] = ((fConst60 * (fRec52[1] + fRec52[2])) + (fConst59 * fRec74[1]));
		double fTemp54 = max(-1, min(1, (fSlow5 * max(-0.7, min(0.7, fTemp43)))));
		fRec52[0] = (Ftube(TUBE_TABLE_12AX7_68k, (((fTemp42 * ((fTemp26 * (0.024937655860349125 + (fSlow11 * ((0.0997506234413965 - (0.0997506234413965 * fabs((0.024937655860349125 * (fTemp26 * fTemp42))))) - 0.024937655860349125)))) + fTemp27)) + ((0.5 * (fTemp54 * (1 - (0.3333333333333333 * faustpower<2>(fTemp54))))) + (fRec74[0] + (fSlow10 * fRec53[0])))) - 1.5816559999999988)) - 191.42014814814814);
		fRec51[0] = ((fConst61 * ((fConst39 * fRec52[1]) + (fConst1 * fRec52[0]))) + (fConst3 * fRec51[1]));
		fRec77[0] = ((fConst65 * (fRec76[1] + fRec76[2])) + (fConst64 * fRec77[1]));
		fRec76[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec77[0] + fRec50[1]) - 1.204284999999999)) - 169.71433333333334);
		fRec75[0] = ((fConst61 * ((fConst39 * fRec76[1]) + (fConst1 * fRec76[0]))) + (fConst3 * fRec75[1]));
		fRec50[0] = ((0.6 * fRec75[0]) - fRec51[0]);
		double fTemp55 = (fRec8[0] * fRec50[0]);
		fVec11[0] = fTemp55;
		fRec49[0] = ((fConst56 * (fVec11[0] + fVec11[1])) + (fConst6 * fRec49[1]));
		fRec78[0] = ((fConst65 * (fRec48[1] + fRec48[2])) + (fConst64 * fRec78[1]));
		fRec48[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec78[0] + fRec49[0]) - 1.204284999999999)) - 169.71433333333334);
		fRec47[0] = ((fConst61 * ((fConst39 * fRec48[1]) + (fConst1 * fRec48[0]))) + (fConst3 * fRec47[1]));
		fRec81[0] = ((fConst69 * (fRec80[1] + fRec80[2])) + (fConst68 * fRec81[1]));
		fRec80[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec81[0] + fRec46[1]) - 0.840701999999999)) - 147.47536585365856);
		fRec79[0] = ((fConst61 * ((fConst39 * fRec80[1]) + (fConst1 * fRec80[0]))) + (fConst3 * fRec79[1]));
		fRec46[0] = ((0.6 * fRec79[0]) + fRec47[0]);
		fRec45[0] = ((fConst56 * (fRec46[0] + fRec46[1])) + (fConst6 * fRec45[1]));
		fRec82[0] = ((fConst69 * (fRec44[1] + fRec44[2])) + (fConst68 * fRec82[1]));
		fRec44[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec82[0] + fRec45[0]) - 0.840701999999999)) - 147.47536585365856);
		fRec43[0] = ((fConst61 * ((fConst39 * fRec44[1]) + (fConst1 * fRec44[0]))) + (fConst3 * fRec43[1]));
		output1[i] = (FAUSTFLOAT)(fRec0[0] * fRec43[0]);
		// post processing
		fRec43[1] = fRec43[0];
		fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
		fRec82[1] = fRec82[0];
		fRec45[1] = fRec45[0];
		fRec46[1] = fRec46[0];
		fRec79[1] = fRec79[0];
		fRec80[2] = fRec80[1]; fRec80[1] = fRec80[0];
		fRec81[1] = fRec81[0];
		fRec47[1] = fRec47[0];
		fRec48[2] = fRec48[1]; fRec48[1] = fRec48[0];
		fRec78[1] = fRec78[0];
		fRec49[1] = fRec49[0];
		fVec11[1] = fVec11[0];
		fRec50[1] = fRec50[0];
		fRec75[1] = fRec75[0];
		fRec76[2] = fRec76[1]; fRec76[1] = fRec76[0];
		fRec77[1] = fRec77[0];
		fRec51[1] = fRec51[0];
		fRec52[2] = fRec52[1]; fRec52[1] = fRec52[0];
		fRec74[1] = fRec74[0];
		fRec53[1] = fRec53[0];
		fVec10[1] = fVec10[0];
		fRec72[2] = fRec72[1]; fRec72[1] = fRec72[0];
		fRec73[1] = fRec73[0];
		fRec68[2] = fRec68[1]; fRec68[1] = fRec68[0];
		fRec69[2] = fRec69[1]; fRec69[1] = fRec69[0];
		fRec70[2] = fRec70[1]; fRec70[1] = fRec70[0];
		fRec71[1] = fRec71[0];
		fRec64[2] = fRec64[1]; fRec64[1] = fRec64[0];
		fRec65[1] = fRec65[0];
		fVec9[1] = fVec9[0];
		fRec66[2] = fRec66[1]; fRec66[1] = fRec66[0];
		fRec67[1] = fRec67[0];
		fRec54[2] = fRec54[1]; fRec54[1] = fRec54[0];
		fRec55[2] = fRec55[1]; fRec55[1] = fRec55[0];
		fRec56[1] = fRec56[0];
		fVec8[1] = fVec8[0];
		fRec57[2] = fRec57[1]; fRec57[1] = fRec57[0];
		fRec58[1] = fRec58[0];
		fRec59[1] = fRec59[0];
		fVec7[1] = fVec7[0];
		fRec60[2] = fRec60[1]; fRec60[1] = fRec60[0];
		fRec61[1] = fRec61[0];
		fRec62[1] = fRec62[0];
		fRec63[1] = fRec63[0];
		fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec42[1] = fRec42[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec39[1] = fRec39[0];
		fRec40[2] = fRec40[1]; fRec40[1] = fRec40[0];
		fRec41[1] = fRec41[0];
		fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec38[1] = fRec38[0];
		fRec7[1] = fRec7[0];
		fVec5[1] = fVec5[0];
		fRec9[1] = fRec9[0];
		fRec35[1] = fRec35[0];
		fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec34[1] = fRec34[0];
		fRec12[1] = fRec12[0];
		fVec4[1] = fVec4[0];
		fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
		fRec33[1] = fRec33[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fVec3[1] = fVec3[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec2[1] = fVec2[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fVec1[1] = fVec1[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec23[1] = fRec23[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		IOTA = IOTA+1;
		fRec22[1] = fRec22[0];
		fRec8[1] = fRec8[0];
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

} // end namespace gxamp9_stereo
