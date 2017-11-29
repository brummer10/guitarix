// generated from file '../src/LV2/faust/gxamp13_stereo.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp13_stereo {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec12[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec18[2];
	double 	fRec21[2];
	int 	IOTA;
	double 	fVec0[32768];
	double 	fConst0;
	int 	iConst1;
	double 	fRec20[2];
	double 	fConst2;
	double 	fRec19[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
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
	double 	fConst27;
	double 	fConst28;
	double 	fRec30[3];
	double 	fVec1[2];
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fRec29[2];
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fVec2[2];
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fRec26[2];
	double 	fRec25[3];
	double 	fVec3[2];
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fRec24[2];
	double 	fRec23[3];
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fRec34[2];
	double 	fRec33[3];
	double 	fConst48;
	double 	fRec32[3];
	double 	fRec31[3];
	double 	fConst49;
	double 	fRec36[2];
	double 	fRec35[3];
	double 	fConst50;
	double 	fConst51;
	double 	fRec39[2];
	double 	fRec38[3];
	double 	fConst52;
	double 	fRec37[3];
	double 	fVec4[2];
	double 	fConst53;
	double 	fConst54;
	double 	fConst55;
	double 	fConst56;
	double 	fRec22[2];
	double 	fVec5[2];
	double 	fRec17[2];
	double 	fRec16[3];
	double 	fVec6[2];
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fRec40[2];
	double 	fRec15[2];
	double 	fConst61;
	double 	fRec14[2];
	double 	fVec7[2];
	double 	fRec44[2];
	double 	fRec43[3];
	double 	fVec8[2];
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fRec45[2];
	double 	fRec42[2];
	double 	fRec41[2];
	double 	fRec13[2];
	double 	fVec9[2];
	double 	fRec11[2];
	double 	fVec10[2];
	double 	fRec10[2];
	double 	fRec9[3];
	double 	fVec11[2];
	double 	fRec46[2];
	double 	fRec8[2];
	double 	fRec7[2];
	double 	fVec12[2];
	double 	fRec50[2];
	double 	fRec49[3];
	double 	fVec13[2];
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fRec51[2];
	double 	fRec48[2];
	double 	fRec47[2];
	double 	fRec6[2];
	double 	fRec5[2];
	double 	fVec14[2];
	double 	fRec4[2];
	double 	fRec3[3];
	double 	fVec15[2];
	double 	fRec52[2];
	double 	fRec2[2];
	double 	fRec1[2];
	double 	fRec71[2];
	double 	fVec16[32768];
	double 	fRec70[2];
	double 	fRec69[2];
	double 	fRec80[3];
	double 	fVec17[2];
	double 	fRec79[2];
	double 	fRec78[2];
	double 	fRec77[3];
	double 	fVec18[2];
	double 	fRec76[2];
	double 	fRec75[3];
	double 	fVec19[2];
	double 	fRec74[2];
	double 	fRec73[3];
	double 	fRec84[2];
	double 	fRec83[3];
	double 	fRec82[3];
	double 	fRec81[3];
	double 	fRec86[2];
	double 	fRec85[3];
	double 	fRec89[2];
	double 	fRec88[3];
	double 	fRec87[3];
	double 	fVec20[2];
	double 	fRec72[2];
	double 	fVec21[2];
	double 	fRec68[2];
	double 	fRec67[3];
	double 	fVec22[2];
	double 	fRec90[2];
	double 	fRec66[2];
	double 	fRec65[2];
	double 	fVec23[2];
	double 	fRec94[2];
	double 	fRec93[3];
	double 	fVec24[2];
	double 	fRec95[2];
	double 	fRec92[2];
	double 	fRec91[2];
	double 	fRec64[2];
	double 	fVec25[2];
	double 	fRec63[2];
	double 	fVec26[2];
	double 	fRec62[2];
	double 	fRec61[3];
	double 	fVec27[2];
	double 	fRec96[2];
	double 	fRec60[2];
	double 	fRec59[2];
	double 	fVec28[2];
	double 	fRec100[2];
	double 	fRec99[3];
	double 	fVec29[2];
	double 	fRec101[2];
	double 	fRec98[2];
	double 	fRec97[2];
	double 	fRec58[2];
	double 	fRec57[2];
	double 	fVec30[2];
	double 	fRec56[2];
	double 	fRec55[3];
	double 	fVec31[2];
	double 	fRec102[2];
	double 	fRec54[2];
	double 	fRec53[2];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "6DJ8 feedback";
	name = N_("6DJ8 feedback");
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
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<32768; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<3; i++) fRec33[i] = 0;
	for (int i=0; i<3; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<3; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<3; i++) fRec38[i] = 0;
	for (int i=0; i<3; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<3; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fVec12[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<3; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) fVec13[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec14[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec15[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec71[i] = 0;
	for (int i=0; i<32768; i++) fVec16[i] = 0;
	for (int i=0; i<2; i++) fRec70[i] = 0;
	for (int i=0; i<2; i++) fRec69[i] = 0;
	for (int i=0; i<3; i++) fRec80[i] = 0;
	for (int i=0; i<2; i++) fVec17[i] = 0;
	for (int i=0; i<2; i++) fRec79[i] = 0;
	for (int i=0; i<2; i++) fRec78[i] = 0;
	for (int i=0; i<3; i++) fRec77[i] = 0;
	for (int i=0; i<2; i++) fVec18[i] = 0;
	for (int i=0; i<2; i++) fRec76[i] = 0;
	for (int i=0; i<3; i++) fRec75[i] = 0;
	for (int i=0; i<2; i++) fVec19[i] = 0;
	for (int i=0; i<2; i++) fRec74[i] = 0;
	for (int i=0; i<3; i++) fRec73[i] = 0;
	for (int i=0; i<2; i++) fRec84[i] = 0;
	for (int i=0; i<3; i++) fRec83[i] = 0;
	for (int i=0; i<3; i++) fRec82[i] = 0;
	for (int i=0; i<3; i++) fRec81[i] = 0;
	for (int i=0; i<2; i++) fRec86[i] = 0;
	for (int i=0; i<3; i++) fRec85[i] = 0;
	for (int i=0; i<2; i++) fRec89[i] = 0;
	for (int i=0; i<3; i++) fRec88[i] = 0;
	for (int i=0; i<3; i++) fRec87[i] = 0;
	for (int i=0; i<2; i++) fVec20[i] = 0;
	for (int i=0; i<2; i++) fRec72[i] = 0;
	for (int i=0; i<2; i++) fVec21[i] = 0;
	for (int i=0; i<2; i++) fRec68[i] = 0;
	for (int i=0; i<3; i++) fRec67[i] = 0;
	for (int i=0; i<2; i++) fVec22[i] = 0;
	for (int i=0; i<2; i++) fRec90[i] = 0;
	for (int i=0; i<2; i++) fRec66[i] = 0;
	for (int i=0; i<2; i++) fRec65[i] = 0;
	for (int i=0; i<2; i++) fVec23[i] = 0;
	for (int i=0; i<2; i++) fRec94[i] = 0;
	for (int i=0; i<3; i++) fRec93[i] = 0;
	for (int i=0; i<2; i++) fVec24[i] = 0;
	for (int i=0; i<2; i++) fRec95[i] = 0;
	for (int i=0; i<2; i++) fRec92[i] = 0;
	for (int i=0; i<2; i++) fRec91[i] = 0;
	for (int i=0; i<2; i++) fRec64[i] = 0;
	for (int i=0; i<2; i++) fVec25[i] = 0;
	for (int i=0; i<2; i++) fRec63[i] = 0;
	for (int i=0; i<2; i++) fVec26[i] = 0;
	for (int i=0; i<2; i++) fRec62[i] = 0;
	for (int i=0; i<3; i++) fRec61[i] = 0;
	for (int i=0; i<2; i++) fVec27[i] = 0;
	for (int i=0; i<2; i++) fRec96[i] = 0;
	for (int i=0; i<2; i++) fRec60[i] = 0;
	for (int i=0; i<2; i++) fRec59[i] = 0;
	for (int i=0; i<2; i++) fVec28[i] = 0;
	for (int i=0; i<2; i++) fRec100[i] = 0;
	for (int i=0; i<3; i++) fRec99[i] = 0;
	for (int i=0; i<2; i++) fVec29[i] = 0;
	for (int i=0; i<2; i++) fRec101[i] = 0;
	for (int i=0; i<2; i++) fRec98[i] = 0;
	for (int i=0; i<2; i++) fRec97[i] = 0;
	for (int i=0; i<2; i++) fRec58[i] = 0;
	for (int i=0; i<2; i++) fRec57[i] = 0;
	for (int i=0; i<2; i++) fVec30[i] = 0;
	for (int i=0; i<2; i++) fRec56[i] = 0;
	for (int i=0; i<3; i++) fRec55[i] = 0;
	for (int i=0; i<2; i++) fVec31[i] = 0;
	for (int i=0; i<2; i++) fRec102[i] = 0;
	for (int i=0; i<2; i++) fRec54[i] = 0;
	for (int i=0; i<2; i++) fRec53[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	iConst1 = int((int((0.1111111111111111 * fConst0)) & 65535));
	fConst2 = (0.009000000000000008 / fConst0);
	fConst3 = tan((942.4777960769379 / fConst0));
	fConst4 = (1.0 / fConst3);
	fConst5 = (1 + ((fConst4 - 1.0000000000000004) / fConst3));
	fConst6 = (1.0 / faustpower<2>(fConst3));
	fConst7 = (2 * (1 - fConst6));
	fConst8 = (1.0 / (1 + ((1.0000000000000004 + fConst4) / fConst3)));
	fConst9 = tan((3769.9111843077517 / fConst0));
	fConst10 = (1.0 / fConst9);
	fConst11 = (1 + ((fConst10 - 1.0000000000000004) / fConst9));
	fConst12 = (1.0 / faustpower<2>(fConst9));
	fConst13 = (2 * (1 - fConst12));
	fConst14 = (1 + ((1.0000000000000004 + fConst10) / fConst9));
	fConst15 = (1.0 / fConst14);
	fConst16 = tan((10053.096491487338 / fConst0));
	fConst17 = (1.0 / faustpower<2>(fConst16));
	fConst18 = (2 * (1 - fConst17));
	fConst19 = (1.0 / fConst16);
	fConst20 = (1 + ((fConst19 - 1.0000000000000004) / fConst16));
	fConst21 = (1 + ((1.0000000000000004 + fConst19) / fConst16));
	fConst22 = (1.0 / fConst21);
	fConst23 = tan((47123.8898038469 / fConst0));
	fConst24 = (2 * (1 - (1.0 / faustpower<2>(fConst23))));
	fConst25 = (1.0 / fConst23);
	fConst26 = (1 + ((fConst25 - 1.414213562373095) / fConst23));
	fConst27 = (1 + ((1.414213562373095 + fConst25) / fConst23));
	fConst28 = (1.0 / fConst27);
	fConst29 = (1.0 / tan((97.38937226128358 / fConst0)));
	fConst30 = (0 - fConst29);
	fConst31 = (1 + fConst29);
	fConst32 = (1.0 / (fConst31 * fConst27));
	fConst33 = (0 - ((1 - fConst29) / fConst31));
	fConst34 = (1 + fConst19);
	fConst35 = (1.0 / fConst34);
	fConst36 = (0 - ((1 - fConst19) / fConst34));
	fConst37 = (1 + fConst10);
	fConst38 = (1.0 / (fConst37 * fConst21));
	fConst39 = (0 - ((1 - fConst10) / fConst37));
	fConst40 = (1 + fConst4);
	fConst41 = (1.0 / (fConst40 * fConst14));
	fConst42 = (0 - ((1 - fConst4) / fConst40));
	fConst43 = (1 + ((fConst4 - 1.0) / fConst3));
	fConst44 = (1.0 / (1 + ((1.0 + fConst4) / fConst3)));
	fConst45 = (1 + ((fConst10 - 1.0) / fConst9));
	fConst46 = (1.0 / (1 + ((1.0 + fConst10) / fConst9)));
	fConst47 = (0 - fConst19);
	fConst48 = (2 * (0 - fConst17));
	fConst49 = (0 - fConst4);
	fConst50 = (2 * (0 - fConst6));
	fConst51 = (0 - fConst10);
	fConst52 = (2 * (0 - fConst12));
	fConst53 = (1.0 / tan((20517.741620594938 / fConst0)));
	fConst54 = (1 + fConst53);
	fConst55 = (1.0 / fConst54);
	fConst56 = (0 - ((1 - fConst53) / fConst54));
	fConst57 = (1.0 / tan((270.1769682087222 / fConst0)));
	fConst58 = (1 + fConst57);
	fConst59 = (1.0 / fConst58);
	fConst60 = (0 - ((1 - fConst57) / fConst58));
	fConst61 = (0.05 / fConst31);
	fConst62 = (1.0 / tan((414.6902302738527 / fConst0)));
	fConst63 = (1 + fConst62);
	fConst64 = (1.0 / fConst63);
	fConst65 = (0 - ((1 - fConst62) / fConst63));
	fConst66 = (1.0 / tan((609.4689747964198 / fConst0)));
	fConst67 = (1 + fConst66);
	fConst68 = (1.0 / fConst67);
	fConst69 = (0 - ((1 - fConst66) / fConst67));
	IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider0))));
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider1))));
	double 	fSlow2 = (1.000000000000001e-05 * double(fslider2));
	double 	fSlow3 = double(fslider3);
	double 	fSlow4 = (1.25 * fSlow3);
	double 	fSlow5 = (2 * (fSlow3 - 0.5));
	double 	fSlow6 = (0.024937655860349125 * (1 - max((double)0, fSlow5)));
	double 	fSlow7 = (fConst8 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow8 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow9 = pow(1e+01,(2 * fSlow3));
	double 	fSlow10 = (fConst8 * fSlow9);
	double 	fSlow11 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow12 = (1 - max((double)0, (0 - fSlow5)));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec12[0] = (fSlow1 + (0.999 * fRec12[1]));
		fRec18[0] = (fSlow2 + (0.999 * fRec18[1]));
		double fTemp0 = (1 - fRec18[0]);
		double fTemp1 = (double)input0[i];
		double fTemp2 = fabs(fTemp1);
		fRec21[0] = ((9.999999999998899e-05 * fTemp2) + (0.9999 * fRec21[1]));
		double fTemp3 = max(fRec21[0], fTemp2);
		fVec0[IOTA&32767] = fTemp3;
		fRec20[0] = ((fVec0[IOTA&32767] + fRec20[1]) - fVec0[(IOTA-iConst1)&32767]);
		fRec19[0] = ((0.999 * fRec19[1]) + (fConst2 * fRec20[0]));
		double fTemp4 = max((double)-1, min(-0.01, (fVec0[IOTA&32767] - (1.0 + (1.02 * fRec19[0])))));
		double fTemp5 = (0 - fTemp4);
		double fTemp6 = (40.1 * fTemp5);
		double fTemp7 = max((double)-600, fTemp6);
		double fTemp8 = (0 - fTemp7);
		double fTemp9 = (fTemp1 - fTemp4);
		double fTemp10 = (40.1 * fTemp9);
		double fTemp11 = max((double)-600, fTemp10);
		double fTemp12 = (0 - fTemp11);
		double fTemp13 = (((int((fabs(fTemp10) > 0.0001)))?((int((fTemp11 < -50)))?(fTemp12 * exp(fTemp11)):(fTemp11 / (1 - exp(fTemp12)))):(1 + (fTemp9 * (20.05 + (134.00083333333336 * fTemp9))))) - ((int((fabs(fTemp6) > 0.0001)))?((int((fTemp7 < -50)))?(fTemp8 * exp(fTemp7)):(fTemp7 / (1 - exp(fTemp8)))):(1 + (fTemp5 * (20.05 + (134.00083333333336 * fTemp5))))));
		double fTemp14 = (fSlow6 * fRec18[0]);
		double fTemp15 = (0.024937655860349125 * (fTemp13 * fRec18[0]));
		fRec30[0] = (fTemp15 - (fConst28 * ((fConst26 * fRec30[2]) + (fConst24 * fRec30[1]))));
		double fTemp16 = (fRec30[0] + (fRec30[2] + (2 * fRec30[1])));
		fVec1[0] = fTemp16;
		fRec29[0] = ((fConst33 * fRec29[1]) + (fConst32 * ((fConst29 * fVec1[0]) + (fConst30 * fVec1[1]))));
		fRec28[0] = ((fConst36 * fRec28[1]) + (fConst35 * (fRec29[1] + fRec29[0])));
		fRec27[0] = (fRec28[0] - (fConst22 * ((fConst20 * fRec27[2]) + (fConst18 * fRec27[1]))));
		double fTemp17 = (fRec27[0] + (fRec27[2] + (2 * fRec27[1])));
		fVec2[0] = fTemp17;
		fRec26[0] = ((fConst39 * fRec26[1]) + (fConst38 * (fVec2[0] + fVec2[1])));
		fRec25[0] = (fRec26[0] - (fConst15 * ((fConst13 * fRec25[1]) + (fConst11 * fRec25[2]))));
		double fTemp18 = (fRec25[0] + (fRec25[2] + (2 * fRec25[1])));
		fVec3[0] = fTemp18;
		fRec24[0] = ((fConst42 * fRec24[1]) + (fConst41 * (fVec3[0] + fVec3[1])));
		fRec23[0] = (fRec24[0] - (fConst8 * ((fConst7 * fRec23[1]) + (fConst5 * fRec23[2]))));
		double fTemp19 = max((double)-1, min((double)1, (fSlow7 * (fRec23[0] + (fRec23[2] + (2 * fRec23[1]))))));
		double fTemp20 = (fConst7 * fRec31[1]);
		double fTemp21 = (fConst13 * fRec32[1]);
		fRec34[0] = ((fConst36 * fRec34[1]) + (fConst35 * ((fConst19 * fRec29[0]) + (fConst47 * fRec29[1]))));
		fRec33[0] = (fRec34[0] - (fConst22 * ((fConst20 * fRec33[2]) + (fConst18 * fRec33[1]))));
		fRec32[0] = ((fConst22 * ((fConst48 * fRec33[1]) + (fConst17 * (fRec33[2] + fRec33[0])))) - (fConst46 * ((fConst45 * fRec32[2]) + fTemp21)));
		fRec31[0] = ((fRec32[2] + (fConst46 * (fTemp21 + (fConst45 * fRec32[0])))) - (fConst44 * ((fConst43 * fRec31[2]) + fTemp20)));
		double fTemp22 = max((double)-1, min((double)1, (fSlow8 * (fRec31[2] + (fConst44 * (fTemp20 + (fConst43 * fRec31[0])))))));
		fRec36[0] = ((fConst42 * fRec36[1]) + (fConst41 * ((fConst4 * fVec3[0]) + (fConst49 * fVec3[1]))));
		fRec35[0] = (fRec36[0] - (fConst8 * ((fConst7 * fRec35[1]) + (fConst5 * fRec35[2]))));
		double fTemp23 = max((double)-1, min((double)1, (fSlow10 * ((fConst50 * fRec35[1]) + (fConst6 * (fRec35[2] + fRec35[0]))))));
		double fTemp24 = (fConst7 * fRec37[1]);
		fRec39[0] = ((fConst39 * fRec39[1]) + (fConst38 * ((fConst10 * fVec2[0]) + (fConst51 * fVec2[1]))));
		fRec38[0] = (fRec39[0] - (fConst15 * ((fConst13 * fRec38[1]) + (fConst11 * fRec38[2]))));
		fRec37[0] = ((fConst15 * ((fConst52 * fRec38[1]) + (fConst12 * (fRec38[2] + fRec38[0])))) - (fConst44 * ((fConst43 * fRec37[2]) + fTemp24)));
		double fTemp25 = max((double)-1, min((double)1, (fSlow11 * (fRec37[2] + (fConst44 * (fTemp24 + (fConst43 * fRec37[0])))))));
		double fTemp26 = ((1.584893192 * ((0.8413951417869425 * (fTemp25 * (1 - (0.3333333333333333 * faustpower<2>(fTemp25))))) + ((fTemp23 * (1 - (0.3333333333333333 * faustpower<2>(fTemp23)))) + (fTemp22 * (1 - (0.3333333333333333 * faustpower<2>(fTemp22))))))) + (1.2589412 * (fTemp19 * (1 - (0.3333333333333333 * faustpower<2>(fTemp19))))));
		fVec4[0] = fTemp26;
		fRec22[0] = ((fConst56 * fRec22[1]) + (fConst55 * (fVec4[0] + fVec4[1])));
		double fTemp27 = max((double)-1, min((double)1, (fSlow9 * max(-0.7, min(0.7, fTemp15)))));
		double fTemp28 = ((0.5 * (fTemp27 * (1 - (0.3333333333333333 * faustpower<2>(fTemp27))))) + ((fSlow12 * fRec22[0]) + (fTemp13 * (fTemp14 + (fTemp0 * (0.024937655860349125 + (fSlow4 * (0.07481296758104737 - (0.0997506234413965 * fabs((0.024937655860349125 * (fTemp13 * fTemp0))))))))))));
		fVec5[0] = (1e-15 + fTemp28);
		fRec17[0] = ((0.9302847925323914 * (1e-15 + (fTemp28 + fVec5[1]))) - (0.8605695850647829 * fRec17[1]));
		fRec16[0] = (fRec17[0] - ((1.8405051250752198 * fRec16[1]) + (0.8612942439318627 * fRec16[2])));
		double fTemp29 = (0.027 * fRec15[1]);
		fVec6[0] = (1e-15 + fTemp29);
		fRec40[0] = ((fConst60 * fRec40[1]) + (fConst59 * (1e-15 + (fTemp29 + fVec6[1]))));
		fRec15[0] = (Ftube(TUBE_TABLE_6DJ8_68k, ((fRec40[0] + (0.9254498422517706 * (fRec16[0] + (fRec16[2] + (2.0 * fRec16[1]))))) - 1.863946)) - 60.96496296296296);
		fRec14[0] = ((fConst33 * fRec14[1]) + (fConst61 * ((fConst29 * fRec15[0]) + (fConst30 * fRec15[1]))));
		fVec7[0] = (1e-15 + fRec13[1]);
		fRec44[0] = ((0.9302847925323914 * (1e-15 + (fRec13[1] + fVec7[1]))) - (0.8605695850647829 * fRec44[1]));
		fRec43[0] = (fRec44[0] - ((1.8405051250752198 * fRec43[1]) + (0.8612942439318627 * fRec43[2])));
		double fTemp30 = (0.015 * fRec42[1]);
		fVec8[0] = (1e-15 + fTemp30);
		fRec45[0] = ((fConst65 * fRec45[1]) + (fConst64 * (1e-15 + (fTemp30 + fVec8[1]))));
		fRec42[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec45[0] + (0.9254498422517706 * (fRec43[0] + (fRec43[2] + (2.0 * fRec43[1]))))) - 1.271609)) - 45.22606666666667);
		fRec41[0] = ((fConst33 * fRec41[1]) + (fConst61 * ((fConst29 * fRec42[0]) + (fConst30 * fRec42[1]))));
		fRec13[0] = ((0.6 * fRec41[0]) - fRec14[0]);
		double fTemp31 = (fRec13[0] * fRec12[0]);
		fVec9[0] = fTemp31;
		fRec11[0] = ((fConst56 * fRec11[1]) + (fConst55 * (fVec9[0] + fVec9[1])));
		fVec10[0] = (1e-15 + fRec11[0]);
		fRec10[0] = ((0.9302847925323914 * (1e-15 + (fRec11[0] + fVec10[1]))) - (0.8605695850647829 * fRec10[1]));
		fRec9[0] = (fRec10[0] - ((1.8405051250752198 * fRec9[1]) + (0.8612942439318627 * fRec9[2])));
		double fTemp32 = (0.015 * fRec8[1]);
		fVec11[0] = (1e-15 + fTemp32);
		fRec46[0] = ((fConst65 * fRec46[1]) + (fConst64 * (1e-15 + (fTemp32 + fVec11[1]))));
		fRec8[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec46[0] + (0.9254498422517706 * (fRec9[0] + (fRec9[2] + (2.0 * fRec9[1]))))) - 1.271609)) - 45.22606666666667);
		fRec7[0] = ((fConst33 * fRec7[1]) + (fConst61 * ((fConst29 * fRec8[0]) + (fConst30 * fRec8[1]))));
		fVec12[0] = (1e-15 + fRec6[1]);
		fRec50[0] = ((0.9302847925323914 * (1e-15 + (fRec6[1] + fVec12[1]))) - (0.8605695850647829 * fRec50[1]));
		fRec49[0] = (fRec50[0] - ((1.8405051250752198 * fRec49[1]) + (0.8612942439318627 * fRec49[2])));
		double fTemp33 = (0.0082 * fRec48[1]);
		fVec13[0] = (1e-15 + fTemp33);
		fRec51[0] = ((fConst69 * fRec51[1]) + (fConst68 * (1e-15 + (fTemp33 + fVec13[1]))));
		fRec48[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec51[0] + (0.9254498422517706 * (fRec49[0] + (fRec49[2] + (2.0 * fRec49[1]))))) - 0.797043)) - 32.799634146341475);
		fRec47[0] = ((fConst33 * fRec47[1]) + (fConst61 * ((fConst29 * fRec48[0]) + (fConst30 * fRec48[1]))));
		fRec6[0] = ((0.6 * fRec47[0]) + fRec7[0]);
		fRec5[0] = ((fConst56 * fRec5[1]) + (fConst55 * (fRec6[1] + fRec6[0])));
		fVec14[0] = (1e-15 + fRec5[0]);
		fRec4[0] = ((0.9302847925323914 * (1e-15 + (fRec5[0] + fVec14[1]))) - (0.8605695850647829 * fRec4[1]));
		fRec3[0] = (fRec4[0] - ((1.8405051250752198 * fRec3[1]) + (0.8612942439318627 * fRec3[2])));
		double fTemp34 = (0.0082 * fRec2[1]);
		fVec15[0] = (1e-15 + fTemp34);
		fRec52[0] = ((fConst69 * fRec52[1]) + (fConst68 * (1e-15 + (fTemp34 + fVec15[1]))));
		fRec2[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec52[0] + (0.9254498422517706 * (fRec3[0] + (fRec3[2] + (2.0 * fRec3[1]))))) - 0.797043)) - 32.799634146341475);
		fRec1[0] = ((fConst33 * fRec1[1]) + (fConst61 * ((fConst29 * fRec2[0]) + (fConst30 * fRec2[1]))));
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		double fTemp35 = (double)input1[i];
		double fTemp36 = fabs(fTemp35);
		fRec71[0] = ((9.999999999998899e-05 * fTemp36) + (0.9999 * fRec71[1]));
		double fTemp37 = max(fRec71[0], fTemp36);
		fVec16[IOTA&32767] = fTemp37;
		fRec70[0] = ((fVec16[IOTA&32767] + fRec70[1]) - fVec16[(IOTA-iConst1)&32767]);
		fRec69[0] = ((0.999 * fRec69[1]) + (fConst2 * fRec70[0]));
		double fTemp38 = max((double)-1, min(-0.01, (fVec16[IOTA&32767] - (1.0 + (1.02 * fRec69[0])))));
		double fTemp39 = (0 - fTemp38);
		double fTemp40 = (40.1 * fTemp39);
		double fTemp41 = max((double)-600, fTemp40);
		double fTemp42 = (0 - fTemp41);
		double fTemp43 = (fTemp35 - fTemp38);
		double fTemp44 = (40.1 * fTemp43);
		double fTemp45 = max((double)-600, fTemp44);
		double fTemp46 = (0 - fTemp45);
		double fTemp47 = (((int((fabs(fTemp44) > 0.0001)))?((int((fTemp45 < -50)))?(fTemp46 * exp(fTemp45)):(fTemp45 / (1 - exp(fTemp46)))):(1 + (fTemp43 * (20.05 + (134.00083333333336 * fTemp43))))) - ((int((fabs(fTemp40) > 0.0001)))?((int((fTemp41 < -50)))?(fTemp42 * exp(fTemp41)):(fTemp41 / (1 - exp(fTemp42)))):(1 + (fTemp39 * (20.05 + (134.00083333333336 * fTemp39))))));
		double fTemp48 = (0.024937655860349125 * (fRec18[0] * fTemp47));
		fRec80[0] = (fTemp48 - (fConst28 * ((fConst26 * fRec80[2]) + (fConst24 * fRec80[1]))));
		double fTemp49 = (fRec80[0] + (fRec80[2] + (2 * fRec80[1])));
		fVec17[0] = fTemp49;
		fRec79[0] = ((fConst33 * fRec79[1]) + (fConst32 * ((fConst29 * fVec17[0]) + (fConst30 * fVec17[1]))));
		fRec78[0] = ((fConst36 * fRec78[1]) + (fConst35 * (fRec79[1] + fRec79[0])));
		fRec77[0] = (fRec78[0] - (fConst22 * ((fConst20 * fRec77[2]) + (fConst18 * fRec77[1]))));
		double fTemp50 = (fRec77[0] + (fRec77[2] + (2 * fRec77[1])));
		fVec18[0] = fTemp50;
		fRec76[0] = ((fConst39 * fRec76[1]) + (fConst38 * (fVec18[0] + fVec18[1])));
		fRec75[0] = (fRec76[0] - (fConst15 * ((fConst13 * fRec75[1]) + (fConst11 * fRec75[2]))));
		double fTemp51 = (fRec75[0] + (fRec75[2] + (2 * fRec75[1])));
		fVec19[0] = fTemp51;
		fRec74[0] = ((fConst42 * fRec74[1]) + (fConst41 * (fVec19[0] + fVec19[1])));
		fRec73[0] = (fRec74[0] - (fConst8 * ((fConst7 * fRec73[1]) + (fConst5 * fRec73[2]))));
		double fTemp52 = max((double)-1, min((double)1, (fSlow7 * (fRec73[0] + (fRec73[2] + (2 * fRec73[1]))))));
		double fTemp53 = (fConst7 * fRec81[1]);
		double fTemp54 = (fConst13 * fRec82[1]);
		fRec84[0] = ((fConst36 * fRec84[1]) + (fConst35 * ((fConst19 * fRec79[0]) + (fConst47 * fRec79[1]))));
		fRec83[0] = (fRec84[0] - (fConst22 * ((fConst20 * fRec83[2]) + (fConst18 * fRec83[1]))));
		fRec82[0] = ((fConst22 * ((fConst48 * fRec83[1]) + (fConst17 * (fRec83[2] + fRec83[0])))) - (fConst46 * ((fConst45 * fRec82[2]) + fTemp54)));
		fRec81[0] = ((fRec82[2] + (fConst46 * (fTemp54 + (fConst45 * fRec82[0])))) - (fConst44 * ((fConst43 * fRec81[2]) + fTemp53)));
		double fTemp55 = max((double)-1, min((double)1, (fSlow8 * (fRec81[2] + (fConst44 * (fTemp53 + (fConst43 * fRec81[0])))))));
		fRec86[0] = ((fConst42 * fRec86[1]) + (fConst41 * ((fConst4 * fVec19[0]) + (fConst49 * fVec19[1]))));
		fRec85[0] = (fRec86[0] - (fConst8 * ((fConst7 * fRec85[1]) + (fConst5 * fRec85[2]))));
		double fTemp56 = max((double)-1, min((double)1, (fSlow10 * ((fConst50 * fRec85[1]) + (fConst6 * (fRec85[2] + fRec85[0]))))));
		double fTemp57 = (fConst7 * fRec87[1]);
		fRec89[0] = ((fConst39 * fRec89[1]) + (fConst38 * ((fConst10 * fVec18[0]) + (fConst51 * fVec18[1]))));
		fRec88[0] = (fRec89[0] - (fConst15 * ((fConst13 * fRec88[1]) + (fConst11 * fRec88[2]))));
		fRec87[0] = ((fConst15 * ((fConst52 * fRec88[1]) + (fConst12 * (fRec88[2] + fRec88[0])))) - (fConst44 * ((fConst43 * fRec87[2]) + fTemp57)));
		double fTemp58 = max((double)-1, min((double)1, (fSlow11 * (fRec87[2] + (fConst44 * (fTemp57 + (fConst43 * fRec87[0])))))));
		double fTemp59 = ((1.584893192 * ((0.8413951417869425 * (fTemp58 * (1 - (0.3333333333333333 * faustpower<2>(fTemp58))))) + ((fTemp56 * (1 - (0.3333333333333333 * faustpower<2>(fTemp56)))) + (fTemp55 * (1 - (0.3333333333333333 * faustpower<2>(fTemp55))))))) + (1.2589412 * (fTemp52 * (1 - (0.3333333333333333 * faustpower<2>(fTemp52))))));
		fVec20[0] = fTemp59;
		fRec72[0] = ((fConst56 * fRec72[1]) + (fConst55 * (fVec20[0] + fVec20[1])));
		double fTemp60 = max((double)-1, min((double)1, (fSlow9 * max(-0.7, min(0.7, fTemp48)))));
		double fTemp61 = (((0.5 * (fTemp60 * (1 - (0.3333333333333333 * faustpower<2>(fTemp60))))) + (fSlow12 * fRec72[0])) + (fTemp47 * (fTemp14 + (fTemp0 * (0.024937655860349125 + (fSlow4 * (0.07481296758104737 - (0.0997506234413965 * fabs((0.024937655860349125 * (fTemp0 * fTemp47)))))))))));
		fVec21[0] = (1e-15 + fTemp61);
		fRec68[0] = ((0.9302847925323914 * (1e-15 + (fTemp61 + fVec21[1]))) - (0.8605695850647829 * fRec68[1]));
		fRec67[0] = (fRec68[0] - ((1.8405051250752198 * fRec67[1]) + (0.8612942439318627 * fRec67[2])));
		double fTemp62 = (0.027 * fRec66[1]);
		fVec22[0] = (1e-15 + fTemp62);
		fRec90[0] = ((fConst60 * fRec90[1]) + (fConst59 * (1e-15 + (fTemp62 + fVec22[1]))));
		fRec66[0] = (Ftube(TUBE_TABLE_6DJ8_68k, ((fRec90[0] + (0.9254498422517706 * (fRec67[0] + (fRec67[2] + (2.0 * fRec67[1]))))) - 1.863946)) - 60.96496296296296);
		fRec65[0] = ((fConst33 * fRec65[1]) + (fConst61 * ((fConst29 * fRec66[0]) + (fConst30 * fRec66[1]))));
		fVec23[0] = (1e-15 + fRec64[1]);
		fRec94[0] = ((0.9302847925323914 * (1e-15 + (fRec64[1] + fVec23[1]))) - (0.8605695850647829 * fRec94[1]));
		fRec93[0] = (fRec94[0] - ((1.8405051250752198 * fRec93[1]) + (0.8612942439318627 * fRec93[2])));
		double fTemp63 = (0.015 * fRec92[1]);
		fVec24[0] = (1e-15 + fTemp63);
		fRec95[0] = ((fConst65 * fRec95[1]) + (fConst64 * (1e-15 + (fTemp63 + fVec24[1]))));
		fRec92[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec95[0] + (0.9254498422517706 * (fRec93[0] + (fRec93[2] + (2.0 * fRec93[1]))))) - 1.271609)) - 45.22606666666667);
		fRec91[0] = ((fConst33 * fRec91[1]) + (fConst61 * ((fConst29 * fRec92[0]) + (fConst30 * fRec92[1]))));
		fRec64[0] = ((0.6 * fRec91[0]) - fRec65[0]);
		double fTemp64 = (fRec12[0] * fRec64[0]);
		fVec25[0] = fTemp64;
		fRec63[0] = ((fConst56 * fRec63[1]) + (fConst55 * (fVec25[0] + fVec25[1])));
		fVec26[0] = (1e-15 + fRec63[0]);
		fRec62[0] = ((0.9302847925323914 * (1e-15 + (fRec63[0] + fVec26[1]))) - (0.8605695850647829 * fRec62[1]));
		fRec61[0] = (fRec62[0] - ((1.8405051250752198 * fRec61[1]) + (0.8612942439318627 * fRec61[2])));
		double fTemp65 = (0.015 * fRec60[1]);
		fVec27[0] = (1e-15 + fTemp65);
		fRec96[0] = ((fConst65 * fRec96[1]) + (fConst64 * (1e-15 + (fTemp65 + fVec27[1]))));
		fRec60[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec96[0] + (0.9254498422517706 * (fRec61[0] + (fRec61[2] + (2.0 * fRec61[1]))))) - 1.271609)) - 45.22606666666667);
		fRec59[0] = ((fConst33 * fRec59[1]) + (fConst61 * ((fConst29 * fRec60[0]) + (fConst30 * fRec60[1]))));
		fVec28[0] = (1e-15 + fRec58[1]);
		fRec100[0] = ((0.9302847925323914 * (1e-15 + (fRec58[1] + fVec28[1]))) - (0.8605695850647829 * fRec100[1]));
		fRec99[0] = (fRec100[0] - ((1.8405051250752198 * fRec99[1]) + (0.8612942439318627 * fRec99[2])));
		double fTemp66 = (0.0082 * fRec98[1]);
		fVec29[0] = (1e-15 + fTemp66);
		fRec101[0] = ((fConst69 * fRec101[1]) + (fConst68 * (1e-15 + (fTemp66 + fVec29[1]))));
		fRec98[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec101[0] + (0.9254498422517706 * (fRec99[0] + (fRec99[2] + (2.0 * fRec99[1]))))) - 0.797043)) - 32.799634146341475);
		fRec97[0] = ((fConst33 * fRec97[1]) + (fConst61 * ((fConst29 * fRec98[0]) + (fConst30 * fRec98[1]))));
		fRec58[0] = ((0.6 * fRec97[0]) + fRec59[0]);
		fRec57[0] = ((fConst56 * fRec57[1]) + (fConst55 * (fRec58[1] + fRec58[0])));
		fVec30[0] = (1e-15 + fRec57[0]);
		fRec56[0] = ((0.9302847925323914 * (1e-15 + (fRec57[0] + fVec30[1]))) - (0.8605695850647829 * fRec56[1]));
		fRec55[0] = (fRec56[0] - ((1.8405051250752198 * fRec55[1]) + (0.8612942439318627 * fRec55[2])));
		double fTemp67 = (0.0082 * fRec54[1]);
		fVec31[0] = (1e-15 + fTemp67);
		fRec102[0] = ((fConst69 * fRec102[1]) + (fConst68 * (1e-15 + (fTemp67 + fVec31[1]))));
		fRec54[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec102[0] + (0.9254498422517706 * (fRec55[0] + (fRec55[2] + (2.0 * fRec55[1]))))) - 0.797043)) - 32.799634146341475);
		fRec53[0] = ((fConst33 * fRec53[1]) + (fConst61 * ((fConst29 * fRec54[0]) + (fConst30 * fRec54[1]))));
		output1[i] = (FAUSTFLOAT)(fRec0[0] * fRec53[0]);
		// post processing
		fRec53[1] = fRec53[0];
		fRec54[1] = fRec54[0];
		fRec102[1] = fRec102[0];
		fVec31[1] = fVec31[0];
		fRec55[2] = fRec55[1]; fRec55[1] = fRec55[0];
		fRec56[1] = fRec56[0];
		fVec30[1] = fVec30[0];
		fRec57[1] = fRec57[0];
		fRec58[1] = fRec58[0];
		fRec97[1] = fRec97[0];
		fRec98[1] = fRec98[0];
		fRec101[1] = fRec101[0];
		fVec29[1] = fVec29[0];
		fRec99[2] = fRec99[1]; fRec99[1] = fRec99[0];
		fRec100[1] = fRec100[0];
		fVec28[1] = fVec28[0];
		fRec59[1] = fRec59[0];
		fRec60[1] = fRec60[0];
		fRec96[1] = fRec96[0];
		fVec27[1] = fVec27[0];
		fRec61[2] = fRec61[1]; fRec61[1] = fRec61[0];
		fRec62[1] = fRec62[0];
		fVec26[1] = fVec26[0];
		fRec63[1] = fRec63[0];
		fVec25[1] = fVec25[0];
		fRec64[1] = fRec64[0];
		fRec91[1] = fRec91[0];
		fRec92[1] = fRec92[0];
		fRec95[1] = fRec95[0];
		fVec24[1] = fVec24[0];
		fRec93[2] = fRec93[1]; fRec93[1] = fRec93[0];
		fRec94[1] = fRec94[0];
		fVec23[1] = fVec23[0];
		fRec65[1] = fRec65[0];
		fRec66[1] = fRec66[0];
		fRec90[1] = fRec90[0];
		fVec22[1] = fVec22[0];
		fRec67[2] = fRec67[1]; fRec67[1] = fRec67[0];
		fRec68[1] = fRec68[0];
		fVec21[1] = fVec21[0];
		fRec72[1] = fRec72[0];
		fVec20[1] = fVec20[0];
		fRec87[2] = fRec87[1]; fRec87[1] = fRec87[0];
		fRec88[2] = fRec88[1]; fRec88[1] = fRec88[0];
		fRec89[1] = fRec89[0];
		fRec85[2] = fRec85[1]; fRec85[1] = fRec85[0];
		fRec86[1] = fRec86[0];
		fRec81[2] = fRec81[1]; fRec81[1] = fRec81[0];
		fRec82[2] = fRec82[1]; fRec82[1] = fRec82[0];
		fRec83[2] = fRec83[1]; fRec83[1] = fRec83[0];
		fRec84[1] = fRec84[0];
		fRec73[2] = fRec73[1]; fRec73[1] = fRec73[0];
		fRec74[1] = fRec74[0];
		fVec19[1] = fVec19[0];
		fRec75[2] = fRec75[1]; fRec75[1] = fRec75[0];
		fRec76[1] = fRec76[0];
		fVec18[1] = fVec18[0];
		fRec77[2] = fRec77[1]; fRec77[1] = fRec77[0];
		fRec78[1] = fRec78[0];
		fRec79[1] = fRec79[0];
		fVec17[1] = fVec17[0];
		fRec80[2] = fRec80[1]; fRec80[1] = fRec80[0];
		fRec69[1] = fRec69[0];
		fRec70[1] = fRec70[0];
		fRec71[1] = fRec71[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec52[1] = fRec52[0];
		fVec15[1] = fVec15[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fVec14[1] = fVec14[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec47[1] = fRec47[0];
		fRec48[1] = fRec48[0];
		fRec51[1] = fRec51[0];
		fVec13[1] = fVec13[0];
		fRec49[2] = fRec49[1]; fRec49[1] = fRec49[0];
		fRec50[1] = fRec50[0];
		fVec12[1] = fVec12[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec46[1] = fRec46[0];
		fVec11[1] = fVec11[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fVec10[1] = fVec10[0];
		fRec11[1] = fRec11[0];
		fVec9[1] = fVec9[0];
		fRec13[1] = fRec13[0];
		fRec41[1] = fRec41[0];
		fRec42[1] = fRec42[0];
		fRec45[1] = fRec45[0];
		fVec8[1] = fVec8[0];
		fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
		fRec44[1] = fRec44[0];
		fVec7[1] = fVec7[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec40[1] = fRec40[0];
		fVec6[1] = fVec6[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fVec5[1] = fVec5[0];
		fRec22[1] = fRec22[0];
		fVec4[1] = fVec4[0];
		fRec37[2] = fRec37[1]; fRec37[1] = fRec37[0];
		fRec38[2] = fRec38[1]; fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec35[2] = fRec35[1]; fRec35[1] = fRec35[0];
		fRec36[1] = fRec36[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec34[1] = fRec34[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fVec3[1] = fVec3[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fVec2[1] = fVec2[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fVec1[1] = fVec1[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		IOTA = IOTA+1;
		fRec21[1] = fRec21[0];
		fRec18[1] = fRec18[0];
		fRec12[1] = fRec12[0];
		fRec0[1] = fRec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
}
		
void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
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

/*
typedef enum
{
   DRIVE, 
   WET_DRY, 
   PREGAIN, 
   GAIN1, 
} PortIndex;
*/

} // end namespace gxamp13_stereo
