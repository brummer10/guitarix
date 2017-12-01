// generated from file '../src/LV2/faust/gxamp6.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp6 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec12[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec14[2];
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fVec0[2];
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fRec33[2];
	double 	fRec32[2];
	double 	fRec31[3];
	double 	fRec30[3];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec34[2];
	double 	fVec1[2];
	double 	fRec29[2];
	double 	fRec28[3];
	double 	fVec2[2];
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fRec35[2];
	double 	fRec27[2];
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fRec26[2];
	double 	fVec3[2];
	double 	fRec39[2];
	double 	fRec38[3];
	double 	fVec4[2];
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fRec40[2];
	double 	fRec37[2];
	double 	fRec36[2];
	double 	fRec25[2];
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fRec24[2];
	double 	fVec5[2];
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fVec6[2];
	double 	fRec41[2];
	double 	fRec21[2];
	double 	fRec20[2];
	double 	fVec7[2];
	double 	fRec45[2];
	double 	fRec44[3];
	double 	fVec8[2];
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fRec46[2];
	double 	fRec43[2];
	double 	fRec42[2];
	double 	fRec19[2];
	double 	fVec9[2];
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fVec10[2];
	double 	fRec47[2];
	double 	fRec16[2];
	double 	fRec15[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
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
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fRec59[2];
	int 	IOTA;
	double 	fVec11[32768];
	int 	iConst58;
	double 	fRec58[2];
	double 	fConst59;
	double 	fRec57[2];
	double 	fRec56[3];
	double 	fVec12[2];
	double 	fConst60;
	double 	fRec55[2];
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fRec54[2];
	double 	fRec53[3];
	double 	fVec13[2];
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fRec52[2];
	double 	fRec51[3];
	double 	fVec14[2];
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fRec50[2];
	double 	fRec49[3];
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;
	double 	fConst74;
	double 	fRec63[2];
	double 	fRec62[3];
	double 	fConst75;
	double 	fRec61[3];
	double 	fRec60[3];
	double 	fConst76;
	double 	fRec65[2];
	double 	fRec64[3];
	double 	fConst77;
	double 	fConst78;
	double 	fRec68[2];
	double 	fRec67[3];
	double 	fConst79;
	double 	fRec66[3];
	double 	fVec15[2];
	double 	fRec48[2];
	double 	fVec16[2];
	double 	fRec13[2];
	double 	fVec17[2];
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fVec18[2];
	double 	fRec69[2];
	double 	fRec9[2];
	double 	fConst80;
	double 	fRec8[2];
	double 	fVec19[2];
	double 	fRec72[2];
	double 	fRec71[2];
	double 	fRec70[2];
	double 	fRec6[2];
	double 	fRec4[2];
	double 	fRec2[2];
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
	id = "pre 6DJ8/ push-pull 6V6";
	name = N_("pre 6DJ8/ push-pull 6V6");
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
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<3; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<3; i++) fRec44[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec59[i] = 0;
	for (int i=0; i<32768; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec58[i] = 0;
	for (int i=0; i<2; i++) fRec57[i] = 0;
	for (int i=0; i<3; i++) fRec56[i] = 0;
	for (int i=0; i<2; i++) fVec12[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<2; i++) fRec54[i] = 0;
	for (int i=0; i<3; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) fVec13[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<3; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fVec14[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<3; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) fRec63[i] = 0;
	for (int i=0; i<3; i++) fRec62[i] = 0;
	for (int i=0; i<3; i++) fRec61[i] = 0;
	for (int i=0; i<3; i++) fRec60[i] = 0;
	for (int i=0; i<2; i++) fRec65[i] = 0;
	for (int i=0; i<3; i++) fRec64[i] = 0;
	for (int i=0; i<2; i++) fRec68[i] = 0;
	for (int i=0; i<3; i++) fRec67[i] = 0;
	for (int i=0; i<3; i++) fRec66[i] = 0;
	for (int i=0; i<2; i++) fVec15[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fVec16[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fVec17[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec18[i] = 0;
	for (int i=0; i<2; i++) fRec69[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec19[i] = 0;
	for (int i=0; i<2; i++) fRec72[i] = 0;
	for (int i=0; i<2; i++) fRec71[i] = 0;
	for (int i=0; i<2; i++) fRec70[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = tan((37699.11184307752 / fConst0));
	fConst2 = (1.0 / fConst1);
	fConst3 = (1 + ((fConst2 - 0.7653668647301795) / fConst1));
	fConst4 = (2 * (1 - (1.0 / faustpower<2>(fConst1))));
	fConst5 = (1.0 / (1 + ((0.7653668647301795 + fConst2) / fConst1)));
	fConst6 = (1 + ((fConst2 - 1.8477590650225735) / fConst1));
	fConst7 = (1.0 / (1 + ((fConst2 + 1.8477590650225735) / fConst1)));
	fConst8 = (973.8937226128359 / fConst0);
	fConst9 = (1 - fConst8);
	fConst10 = (1.0 / (1 + fConst8));
	fConst11 = (1.0 / tan((270.1769682087222 / fConst0)));
	fConst12 = (1 + fConst11);
	fConst13 = (1.0 / fConst12);
	fConst14 = (0 - ((1 - fConst11) / fConst12));
	fConst15 = (1.0 / tan((97.38937226128358 / fConst0)));
	fConst16 = (0 - fConst15);
	fConst17 = (1 + fConst15);
	fConst18 = (0.05 / fConst17);
	fConst19 = (0 - ((1 - fConst15) / fConst17));
	fConst20 = (1.0 / tan((414.6902302738527 / fConst0)));
	fConst21 = (1 + fConst20);
	fConst22 = (1.0 / fConst21);
	fConst23 = (0 - ((1 - fConst20) / fConst21));
	fConst24 = (1.0 / tan((20517.741620594938 / fConst0)));
	fConst25 = (1 + fConst24);
	fConst26 = (1.0 / fConst25);
	fConst27 = (0 - ((1 - fConst24) / fConst25));
	fConst28 = (1.0 / tan((609.4689747964198 / fConst0)));
	fConst29 = (1 + fConst28);
	fConst30 = (1.0 / fConst29);
	fConst31 = (0 - ((1 - fConst28) / fConst29));
	fConst32 = tan((942.4777960769379 / fConst0));
	fConst33 = (1.0 / fConst32);
	fConst34 = (1 + ((fConst33 - 1.0000000000000004) / fConst32));
	fConst35 = (1.0 / faustpower<2>(fConst32));
	fConst36 = (2 * (1 - fConst35));
	fConst37 = (1.0 / (1 + ((1.0000000000000004 + fConst33) / fConst32)));
	fConst38 = tan((3769.9111843077517 / fConst0));
	fConst39 = (1.0 / fConst38);
	fConst40 = (1 + ((fConst39 - 1.0000000000000004) / fConst38));
	fConst41 = (1.0 / faustpower<2>(fConst38));
	fConst42 = (2 * (1 - fConst41));
	fConst43 = (1 + ((1.0000000000000004 + fConst39) / fConst38));
	fConst44 = (1.0 / fConst43);
	fConst45 = tan((10053.096491487338 / fConst0));
	fConst46 = (1.0 / faustpower<2>(fConst45));
	fConst47 = (2 * (1 - fConst46));
	fConst48 = (1.0 / fConst45);
	fConst49 = (1 + ((fConst48 - 1.0000000000000004) / fConst45));
	fConst50 = (1 + ((1.0000000000000004 + fConst48) / fConst45));
	fConst51 = (1.0 / fConst50);
	fConst52 = tan((47123.8898038469 / fConst0));
	fConst53 = (2 * (1 - (1.0 / faustpower<2>(fConst52))));
	fConst54 = (1.0 / fConst52);
	fConst55 = (1 + ((fConst54 - 1.414213562373095) / fConst52));
	fConst56 = (1 + ((1.414213562373095 + fConst54) / fConst52));
	fConst57 = (1.0 / fConst56);
	iConst58 = int((int((0.1111111111111111 * fConst0)) & 65535));
	fConst59 = (0.009000000000000008 / fConst0);
	fConst60 = (1.0 / (fConst17 * fConst56));
	fConst61 = (1 + fConst48);
	fConst62 = (1.0 / fConst61);
	fConst63 = (0 - ((1 - fConst48) / fConst61));
	fConst64 = (1 + fConst39);
	fConst65 = (1.0 / (fConst64 * fConst50));
	fConst66 = (0 - ((1 - fConst39) / fConst64));
	fConst67 = (1 + fConst33);
	fConst68 = (1.0 / (fConst67 * fConst43));
	fConst69 = (0 - ((1 - fConst33) / fConst67));
	fConst70 = (1 + ((fConst33 - 1.0) / fConst32));
	fConst71 = (1.0 / (1 + ((1.0 + fConst33) / fConst32)));
	fConst72 = (1 + ((fConst39 - 1.0) / fConst38));
	fConst73 = (1.0 / (1 + ((1.0 + fConst39) / fConst38)));
	fConst74 = (0 - fConst48);
	fConst75 = (2 * (0 - fConst46));
	fConst76 = (0 - fConst33);
	fConst77 = (2 * (0 - fConst35));
	fConst78 = (0 - fConst39);
	fConst79 = (2 * (0 - fConst41));
	fConst80 = (0.025 / fConst17);
	IOTA = 0;
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
	double 	fSlow4 = (1.25 * fSlow3);
	double 	fSlow5 = (fConst37 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow6 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow7 = (fConst37 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow8 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow9 = (2 * (fSlow3 - 0.5));
	double 	fSlow10 = (1 - max((double)0, (0 - fSlow9)));
	double 	fSlow11 = (0.024937655860349125 * (1 - max((double)0, fSlow9)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (0.5 * fRec0[1]);
		double fTemp1 = (fTemp0 + (0.4 * fRec2[1]));
		double fTemp2 = ((0.3 * fRec4[1]) + fTemp1);
		fRec12[0] = (fSlow0 + (0.999 * fRec12[1]));
		fRec14[0] = (fSlow1 + (0.999 * fRec14[1]));
		double fTemp3 = (double)input0[i];
		fVec0[0] = fTemp3;
		fRec33[0] = (fConst10 * ((fVec0[0] + (fConst9 * fRec33[1])) - fVec0[1]));
		fRec32[0] = (fConst10 * (((fConst9 * fRec32[1]) + fRec33[0]) - fRec33[1]));
		fRec31[0] = (fRec32[0] - (fConst7 * ((fConst6 * fRec31[2]) + (fConst4 * fRec31[1]))));
		fRec30[0] = ((fConst7 * (fRec31[0] + (fRec31[2] + (2 * fRec31[1])))) - (fConst5 * ((fConst4 * fRec30[1]) + (fConst3 * fRec30[2]))));
		fRec34[0] = (fSlow2 + (0.999 * fRec34[1]));
		double fTemp4 = (fConst5 * (fRec34[0] * (fRec30[0] + (fRec30[2] + (2 * fRec30[1])))));
		fVec1[0] = (1e-15 + fTemp4);
		fRec29[0] = ((0.9302847925323914 * (1e-15 + (fTemp4 + fVec1[1]))) - (0.8605695850647829 * fRec29[1]));
		fRec28[0] = (fRec29[0] - ((1.8405051250752198 * fRec28[1]) + (0.8612942439318627 * fRec28[2])));
		double fTemp5 = (0.027 * fRec27[1]);
		fVec2[0] = (1e-15 + fTemp5);
		fRec35[0] = ((fConst14 * fRec35[1]) + (fConst13 * (1e-15 + (fTemp5 + fVec2[1]))));
		fRec27[0] = (Ftube(TUBE_TABLE_6DJ8_68k, ((fRec35[0] + (0.9254498422517706 * (fRec28[0] + (fRec28[2] + (2.0 * fRec28[1]))))) - 1.863946)) - 60.96496296296296);
		fRec26[0] = ((fConst19 * fRec26[1]) + (fConst18 * ((fConst15 * fRec27[0]) + (fConst16 * fRec27[1]))));
		fVec3[0] = (1e-15 + fRec25[1]);
		fRec39[0] = ((0.9302847925323914 * (1e-15 + (fRec25[1] + fVec3[1]))) - (0.8605695850647829 * fRec39[1]));
		fRec38[0] = (fRec39[0] - ((1.8405051250752198 * fRec38[1]) + (0.8612942439318627 * fRec38[2])));
		double fTemp6 = (0.015 * fRec37[1]);
		fVec4[0] = (1e-15 + fTemp6);
		fRec40[0] = ((fConst23 * fRec40[1]) + (fConst22 * (1e-15 + (fTemp6 + fVec4[1]))));
		fRec37[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec40[0] + (0.9254498422517706 * (fRec38[0] + (fRec38[2] + (2.0 * fRec38[1]))))) - 1.271609)) - 45.22606666666667);
		fRec36[0] = ((fConst19 * fRec36[1]) + (fConst18 * ((fConst15 * fRec37[0]) + (fConst16 * fRec37[1]))));
		fRec25[0] = ((0.6 * fRec36[0]) + fRec26[0]);
		fRec24[0] = ((fConst27 * fRec24[1]) + (fConst26 * (fRec25[1] + fRec25[0])));
		fVec5[0] = (1e-15 + fRec24[0]);
		fRec23[0] = ((0.9302847925323914 * (1e-15 + (fRec24[0] + fVec5[1]))) - (0.8605695850647829 * fRec23[1]));
		fRec22[0] = (fRec23[0] - ((1.8405051250752198 * fRec22[1]) + (0.8612942439318627 * fRec22[2])));
		double fTemp7 = (0.015 * fRec21[1]);
		fVec6[0] = (1e-15 + fTemp7);
		fRec41[0] = ((fConst23 * fRec41[1]) + (fConst22 * (1e-15 + (fTemp7 + fVec6[1]))));
		fRec21[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec41[0] + (0.9254498422517706 * (fRec22[0] + (fRec22[2] + (2.0 * fRec22[1]))))) - 1.271609)) - 45.22606666666667);
		fRec20[0] = ((fConst19 * fRec20[1]) + (fConst18 * ((fConst15 * fRec21[0]) + (fConst16 * fRec21[1]))));
		fVec7[0] = (1e-15 + fRec19[1]);
		fRec45[0] = ((0.9302847925323914 * (1e-15 + (fRec19[1] + fVec7[1]))) - (0.8605695850647829 * fRec45[1]));
		fRec44[0] = (fRec45[0] - ((1.8405051250752198 * fRec44[1]) + (0.8612942439318627 * fRec44[2])));
		double fTemp8 = (0.0082 * fRec43[1]);
		fVec8[0] = (1e-15 + fTemp8);
		fRec46[0] = ((fConst31 * fRec46[1]) + (fConst30 * (1e-15 + (fTemp8 + fVec8[1]))));
		fRec43[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec46[0] + (0.9254498422517706 * (fRec44[0] + (fRec44[2] + (2.0 * fRec44[1]))))) - 0.797043)) - 32.799634146341475);
		fRec42[0] = ((fConst19 * fRec42[1]) + (fConst18 * ((fConst15 * fRec43[0]) + (fConst16 * fRec43[1]))));
		fRec19[0] = ((0.6 * fRec42[0]) + fRec20[0]);
		fVec9[0] = (1e-15 + fRec19[0]);
		fRec18[0] = ((0.9302847925323914 * (1e-15 + (fRec19[0] + fVec9[1]))) - (0.8605695850647829 * fRec18[1]));
		fRec17[0] = (fRec18[0] - ((1.8405051250752198 * fRec17[1]) + (0.8612942439318627 * fRec17[2])));
		double fTemp9 = (0.0082 * fRec16[1]);
		fVec10[0] = (1e-15 + fTemp9);
		fRec47[0] = ((fConst31 * fRec47[1]) + (fConst30 * (1e-15 + (fTemp9 + fVec10[1]))));
		fRec16[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec47[0] + (0.9254498422517706 * (fRec17[0] + (fRec17[2] + (2.0 * fRec17[1]))))) - 0.797043)) - 32.799634146341475);
		fRec15[0] = ((fConst19 * fRec15[1]) + (fConst18 * ((fConst15 * fRec16[0]) + (fConst16 * fRec16[1]))));
		double fTemp10 = (fRec15[0] * (1 - fRec14[0]));
		double fTemp11 = (fRec14[0] * fRec15[0]);
		double fTemp12 = fabs(fTemp11);
		fRec59[0] = ((0.9999 * fRec59[1]) + (9.999999999998899e-05 * fTemp12));
		double fTemp13 = max(fRec59[0], fTemp12);
		fVec11[IOTA&32767] = fTemp13;
		fRec58[0] = ((fVec11[IOTA&32767] + fRec58[1]) - fVec11[(IOTA-iConst58)&32767]);
		fRec57[0] = ((0.999 * fRec57[1]) + (fConst59 * fRec58[0]));
		double fTemp14 = max(-1.0, min(-0.01, (fVec11[IOTA&32767] - (1.0 + (1.02 * fRec57[0])))));
		double fTemp15 = (0 - fTemp14);
		double fTemp16 = (40.1 * fTemp15);
		double fTemp17 = max((double)-600, fTemp16);
		double fTemp18 = (0 - fTemp17);
		double fTemp19 = (fTemp11 - fTemp14);
		double fTemp20 = (40.1 * fTemp19);
		double fTemp21 = max((double)-600, fTemp20);
		double fTemp22 = (0 - fTemp21);
		double fTemp23 = (((int((fabs(fTemp20) > 0.0001)))?((int((fTemp21 < -50)))?(fTemp22 * exp(fTemp21)):(fTemp21 / (1 - exp(fTemp22)))):(1 + (fTemp19 * (20.05 + (134.00083333333336 * fTemp19))))) - ((int((fabs(fTemp16) > 0.0001)))?((int((fTemp17 < -50)))?(fTemp18 * exp(fTemp17)):(fTemp17 / (1 - exp(fTemp18)))):(1 + (fTemp15 * (20.05 + (134.00083333333336 * fTemp15))))));
		fRec56[0] = ((0.024937655860349125 * fTemp23) - (fConst57 * ((fConst55 * fRec56[2]) + (fConst53 * fRec56[1]))));
		double fTemp24 = (fRec56[0] + (fRec56[2] + (2 * fRec56[1])));
		fVec12[0] = fTemp24;
		fRec55[0] = ((fConst19 * fRec55[1]) + (fConst60 * ((fConst15 * fVec12[0]) + (fConst16 * fVec12[1]))));
		fRec54[0] = ((fConst63 * fRec54[1]) + (fConst62 * (fRec55[1] + fRec55[0])));
		fRec53[0] = (fRec54[0] - (fConst51 * ((fConst49 * fRec53[2]) + (fConst47 * fRec53[1]))));
		double fTemp25 = (fRec53[0] + (fRec53[2] + (2 * fRec53[1])));
		fVec13[0] = fTemp25;
		fRec52[0] = ((fConst66 * fRec52[1]) + (fConst65 * (fVec13[0] + fVec13[1])));
		fRec51[0] = (fRec52[0] - (fConst44 * ((fConst42 * fRec51[1]) + (fConst40 * fRec51[2]))));
		double fTemp26 = (fRec51[0] + (fRec51[2] + (2 * fRec51[1])));
		fVec14[0] = fTemp26;
		fRec50[0] = ((fConst69 * fRec50[1]) + (fConst68 * (fVec14[0] + fVec14[1])));
		fRec49[0] = (fRec50[0] - (fConst37 * ((fConst36 * fRec49[1]) + (fConst34 * fRec49[2]))));
		double fTemp27 = max((double)-1, min((double)1, (fSlow5 * (fRec49[0] + (fRec49[2] + (2 * fRec49[1]))))));
		double fTemp28 = (fConst36 * fRec60[1]);
		double fTemp29 = (fConst42 * fRec61[1]);
		fRec63[0] = ((fConst63 * fRec63[1]) + (fConst62 * ((fConst48 * fRec55[0]) + (fConst74 * fRec55[1]))));
		fRec62[0] = (fRec63[0] - (fConst51 * ((fConst49 * fRec62[2]) + (fConst47 * fRec62[1]))));
		fRec61[0] = ((fConst51 * ((fConst75 * fRec62[1]) + (fConst46 * (fRec62[2] + fRec62[0])))) - (fConst73 * ((fConst72 * fRec61[2]) + fTemp29)));
		fRec60[0] = ((fRec61[2] + (fConst73 * (fTemp29 + (fConst72 * fRec61[0])))) - (fConst71 * ((fConst70 * fRec60[2]) + fTemp28)));
		double fTemp30 = max((double)-1, min((double)1, (fSlow6 * (fRec60[2] + (fConst71 * (fTemp28 + (fConst70 * fRec60[0])))))));
		fRec65[0] = ((fConst69 * fRec65[1]) + (fConst68 * ((fConst33 * fVec14[0]) + (fConst76 * fVec14[1]))));
		fRec64[0] = (fRec65[0] - (fConst37 * ((fConst36 * fRec64[1]) + (fConst34 * fRec64[2]))));
		double fTemp31 = max((double)-1, min((double)1, (fSlow7 * ((fConst77 * fRec64[1]) + (fConst35 * (fRec64[2] + fRec64[0]))))));
		double fTemp32 = (fConst36 * fRec66[1]);
		fRec68[0] = ((fConst66 * fRec68[1]) + (fConst65 * ((fConst39 * fVec13[0]) + (fConst78 * fVec13[1]))));
		fRec67[0] = (fRec68[0] - (fConst44 * ((fConst42 * fRec67[1]) + (fConst40 * fRec67[2]))));
		fRec66[0] = ((fConst44 * ((fConst79 * fRec67[1]) + (fConst41 * (fRec67[2] + fRec67[0])))) - (fConst71 * ((fConst70 * fRec66[2]) + fTemp32)));
		double fTemp33 = max((double)-1, min((double)1, (fSlow8 * (fRec66[2] + (fConst71 * (fTemp32 + (fConst70 * fRec66[0])))))));
		double fTemp34 = ((1.584893192 * ((0.8413951417869425 * (fTemp33 * (1 - (0.3333333333333333 * faustpower<2>(fTemp33))))) + ((fTemp31 * (1 - (0.3333333333333333 * faustpower<2>(fTemp31)))) + (fTemp30 * (1 - (0.3333333333333333 * faustpower<2>(fTemp30))))))) + (1.2589412 * (fTemp27 * (1 - (0.3333333333333333 * faustpower<2>(fTemp27))))));
		fVec15[0] = fTemp34;
		fRec48[0] = ((fConst27 * fRec48[1]) + (fConst26 * (fVec15[0] + fVec15[1])));
		double fTemp35 = ((fSlow11 * fTemp23) + ((fSlow10 * fRec48[0]) + (fTemp10 * (1 + (fSlow4 * (3 - (4 * fabs(fTemp10))))))));
		fVec16[0] = fTemp35;
		fRec13[0] = ((fConst27 * fRec13[1]) + (fConst26 * (fVec16[0] + fVec16[1])));
		double fTemp36 = (fRec13[0] * fRec12[0]);
		fVec17[0] = (1e-15 + fTemp36);
		fRec11[0] = ((0.9302847925323914 * (1e-15 + (fTemp36 + fVec17[1]))) - (0.8605695850647829 * fRec11[1]));
		fRec10[0] = (fRec11[0] - ((1.8405051250752198 * fRec10[1]) + (0.8612942439318627 * fRec10[2])));
		double fTemp37 = (0.9254498422517706 * (fRec10[0] + (fRec10[2] + (2.0 * fRec10[1]))));
		double fTemp38 = (0.0041 * fRec9[1]);
		fVec18[0] = (1e-15 + fTemp38);
		fRec69[0] = ((fConst27 * fRec69[1]) + (fConst26 * (1e-15 + (fTemp38 + fVec18[1]))));
		fRec9[0] = (Ftube(TUBE_TABLE_6V6_68k, ((fRec69[0] + fTemp37) - 0.664541)) - 87.91682926829267);
		fRec8[0] = ((fConst19 * fRec8[1]) + (fConst80 * ((fConst15 * fRec9[0]) + (fConst16 * fRec9[1]))));
		double fTemp39 = max(-0.75, fRec8[0]);
		double fTemp40 = (0.0041 * fRec71[1]);
		fVec19[0] = (1e-15 + fTemp40);
		fRec72[0] = ((fConst27 * fRec72[1]) + (fConst26 * (1e-15 + (fTemp40 + fVec19[1]))));
		fRec71[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec72[0] + fTemp37) - 0.659761)) - 89.08268292682925);
		fRec70[0] = ((fConst19 * fRec70[1]) + (fConst80 * ((fConst15 * fRec71[0]) + (fConst16 * fRec71[1]))));
		double fTemp41 = min(0.7, fRec70[0]);
		double fTemp42 = ((fTemp41 + ((0.2 * fRec6[1]) + fTemp39)) - fTemp2);
		fRec6[0] = fTemp42;
		double 	fRec7 = (0 - (0.2 * fTemp42));
		fRec4[0] = (fRec6[1] + fRec7);
		double fTemp43 = (fTemp39 + fTemp41);
		double 	fRec5 = (0.3 * (fTemp43 - fTemp2));
		fRec2[0] = (fRec4[1] + fRec5);
		double 	fRec3 = (0.4 * (fTemp43 - fTemp1));
		fRec0[0] = (fRec2[1] + fRec3);
		double 	fRec1 = (0.5 * (fTemp43 - fTemp0));
		output0[i] = (FAUSTFLOAT)(fRec0[1] + fRec1);
		// post processing
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fRec6[1] = fRec6[0];
		fRec70[1] = fRec70[0];
		fRec71[1] = fRec71[0];
		fRec72[1] = fRec72[0];
		fVec19[1] = fVec19[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec69[1] = fRec69[0];
		fVec18[1] = fVec18[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec17[1] = fVec17[0];
		fRec13[1] = fRec13[0];
		fVec16[1] = fVec16[0];
		fRec48[1] = fRec48[0];
		fVec15[1] = fVec15[0];
		fRec66[2] = fRec66[1]; fRec66[1] = fRec66[0];
		fRec67[2] = fRec67[1]; fRec67[1] = fRec67[0];
		fRec68[1] = fRec68[0];
		fRec64[2] = fRec64[1]; fRec64[1] = fRec64[0];
		fRec65[1] = fRec65[0];
		fRec60[2] = fRec60[1]; fRec60[1] = fRec60[0];
		fRec61[2] = fRec61[1]; fRec61[1] = fRec61[0];
		fRec62[2] = fRec62[1]; fRec62[1] = fRec62[0];
		fRec63[1] = fRec63[0];
		fRec49[2] = fRec49[1]; fRec49[1] = fRec49[0];
		fRec50[1] = fRec50[0];
		fVec14[1] = fVec14[0];
		fRec51[2] = fRec51[1]; fRec51[1] = fRec51[0];
		fRec52[1] = fRec52[0];
		fVec13[1] = fVec13[0];
		fRec53[2] = fRec53[1]; fRec53[1] = fRec53[0];
		fRec54[1] = fRec54[0];
		fRec55[1] = fRec55[0];
		fVec12[1] = fVec12[0];
		fRec56[2] = fRec56[1]; fRec56[1] = fRec56[0];
		fRec57[1] = fRec57[0];
		fRec58[1] = fRec58[0];
		IOTA = IOTA+1;
		fRec59[1] = fRec59[0];
		fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fRec47[1] = fRec47[0];
		fVec10[1] = fVec10[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fVec9[1] = fVec9[0];
		fRec19[1] = fRec19[0];
		fRec42[1] = fRec42[0];
		fRec43[1] = fRec43[0];
		fRec46[1] = fRec46[0];
		fVec8[1] = fVec8[0];
		fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
		fRec45[1] = fRec45[0];
		fVec7[1] = fVec7[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec41[1] = fRec41[0];
		fVec6[1] = fVec6[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fVec5[1] = fVec5[0];
		fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fRec40[1] = fRec40[0];
		fVec4[1] = fVec4[0];
		fRec38[2] = fRec38[1]; fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fVec3[1] = fVec3[0];
		fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec35[1] = fRec35[0];
		fVec2[1] = fVec2[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fVec1[1] = fVec1[0];
		fRec34[1] = fRec34[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec32[1] = fRec32[0];
		fRec33[1] = fRec33[0];
		fVec0[1] = fVec0[0];
		fRec14[1] = fRec14[0];
		fRec12[1] = fRec12[0];
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

} // end namespace gxamp6
