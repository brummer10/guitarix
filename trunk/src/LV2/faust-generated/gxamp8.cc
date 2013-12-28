// generated from file '../src/LV2/faust/gxamp8.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp8 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fVec0[2];
	double 	fConst7;
	double 	fRec10[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec11[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec13[2];
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
	double 	fVec1[2];
	double 	fConst18;
	double 	fRec26[2];
	double 	fRec25[2];
	double 	fRec24[3];
	double 	fRec23[3];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec27[2];
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fVec2[2];
	double 	fConst23;
	double 	fRec28[2];
	double 	fRec22[2];
	double 	fConst24;
	double 	fConst25;
	double 	fRec21[2];
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fVec3[2];
	double 	fConst29;
	double 	fRec31[2];
	double 	fRec30[2];
	double 	fRec29[2];
	double 	fRec20[2];
	double 	fRec19[2];
	double 	fVec4[2];
	double 	fRec32[2];
	double 	fRec18[2];
	double 	fRec17[2];
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fVec5[2];
	double 	fConst33;
	double 	fRec35[2];
	double 	fRec34[2];
	double 	fRec33[2];
	double 	fRec16[2];
	double 	fVec6[2];
	double 	fRec36[2];
	double 	fRec15[2];
	double 	fRec14[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec39[2];
	int 	IOTA;
	double 	fVec7[32768];
	int 	iConst34;
	double 	fRec38[2];
	double 	fConst35;
	double 	fRec37[2];
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
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fRec47[3];
	double 	fVec8[2];
	double 	fConst66;
	double 	fRec46[2];
	double 	fConst67;
	double 	fRec45[2];
	double 	fRec44[3];
	double 	fVec9[2];
	double 	fConst68;
	double 	fConst69;
	double 	fRec43[2];
	double 	fRec42[3];
	double 	fConst70;
	double 	fRec41[3];
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;
	double 	fConst74;
	double 	fRec51[2];
	double 	fRec50[3];
	double 	fVec10[2];
	double 	fConst75;
	double 	fConst76;
	double 	fRec49[2];
	double 	fRec48[3];
	double 	fConst77;
	double 	fConst78;
	double 	fConst79;
	double 	fConst80;
	double 	fRec55[2];
	double 	fRec54[3];
	double 	fConst81;
	double 	fRec53[3];
	double 	fRec52[3];
	double 	fRec57[2];
	double 	fRec56[3];
	double 	fVec11[2];
	double 	fRec40[2];
	double 	fVec12[2];
	double 	fRec12[2];
	double 	fRec9[2];
	double 	fConst82;
	double 	fRec8[2];
	double 	fVec13[2];
	double 	fRec60[2];
	double 	fRec59[2];
	double 	fRec58[2];
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
	id = "pre 12AU7/ push-pull 6V6";
	name = N_("pre 12AU7/ push-pull 6V6");
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
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<32768; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<3; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<3; i++) fRec44[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec43[i] = 0;
	for (int i=0; i<3; i++) fRec42[i] = 0;
	for (int i=0; i<3; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<3; i++) fRec50[i] = 0;
	for (int i=0; i<2; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<3; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<3; i++) fRec54[i] = 0;
	for (int i=0; i<3; i++) fRec53[i] = 0;
	for (int i=0; i<3; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) fRec57[i] = 0;
	for (int i=0; i<3; i++) fRec56[i] = 0;
	for (int i=0; i<2; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fVec12[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec13[i] = 0;
	for (int i=0; i<2; i++) fRec60[i] = 0;
	for (int i=0; i<2; i++) fRec59[i] = 0;
	for (int i=0; i<2; i++) fRec58[i] = 0;
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
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = (1.0 / fConst5);
	fConst8 = tan((37699.11184307752 / double(iConst0)));
	fConst9 = (2 * (1 - (1.0 / faustpower<2>(fConst8))));
	fConst10 = (1.0 / fConst8);
	fConst11 = (1 + ((fConst10 - 0.7653668647301795) / fConst8));
	fConst12 = (1 + ((0.7653668647301795 + fConst10) / fConst8));
	fConst13 = (1.0 / fConst12);
	fConst14 = (1 + ((fConst10 - 1.8477590650225735) / fConst8));
	fConst15 = (1.0 / (1 + ((fConst10 + 1.8477590650225735) / fConst8)));
	fConst16 = (973.8937226128359 / double(iConst0));
	fConst17 = (1 - fConst16);
	fConst18 = (1.0 / (1 + fConst16));
	fConst19 = (2.0 / fConst12);
	fConst20 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst21 = (1 + fConst20);
	fConst22 = (0 - ((1 - fConst20) / fConst21));
	fConst23 = (1.0 / fConst21);
	fConst24 = (0 - fConst1);
	fConst25 = (0.1 / fConst2);
	fConst26 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst27 = (1 + fConst26);
	fConst28 = (0 - ((1 - fConst26) / fConst27));
	fConst29 = (1.0 / fConst27);
	fConst30 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst31 = (1 + fConst30);
	fConst32 = (0 - ((1 - fConst30) / fConst31));
	fConst33 = (1.0 / fConst31);
	IOTA = 0;
	iConst34 = int((int((0.1111111111111111 * iConst0)) & 65535));
	fConst35 = (0.009000000000000008 / double(iConst0));
	fConst36 = tan((942.4777960769379 / double(iConst0)));
	fConst37 = (1.0 / faustpower<2>(fConst36));
	fConst38 = (2 * (1 - fConst37));
	fConst39 = (1.0 / fConst36);
	fConst40 = (1 + ((fConst39 - 1.0) / fConst36));
	fConst41 = (1.0 / (1 + ((1.0 + fConst39) / fConst36)));
	fConst42 = tan((3769.9111843077517 / double(iConst0)));
	fConst43 = (1.0 / faustpower<2>(fConst42));
	fConst44 = (2 * (1 - fConst43));
	fConst45 = (1.0 / fConst42);
	fConst46 = (1 + ((fConst45 - 1.0000000000000004) / fConst42));
	fConst47 = (1 + ((fConst45 + 1.0000000000000004) / fConst42));
	fConst48 = (1.0 / fConst47);
	fConst49 = (1 + fConst45);
	fConst50 = (0 - ((1 - fConst45) / fConst49));
	fConst51 = tan((10053.096491487338 / double(iConst0)));
	fConst52 = (1.0 / faustpower<2>(fConst51));
	fConst53 = (2 * (1 - fConst52));
	fConst54 = (1.0 / fConst51);
	fConst55 = (1 + ((fConst54 - 1.0000000000000004) / fConst51));
	fConst56 = (1 + ((1.0000000000000004 + fConst54) / fConst51));
	fConst57 = (1.0 / fConst56);
	fConst58 = (1 + fConst54);
	fConst59 = (0 - ((1 - fConst54) / fConst58));
	fConst60 = tan((47123.8898038469 / double(iConst0)));
	fConst61 = (2 * (1 - (1.0 / faustpower<2>(fConst60))));
	fConst62 = (1.0 / fConst60);
	fConst63 = (1 + ((fConst62 - 1.414213562373095) / fConst60));
	fConst64 = (1 + ((1.414213562373095 + fConst62) / fConst60));
	fConst65 = (1.0 / fConst64);
	fConst66 = (1.0 / (fConst2 * fConst64));
	fConst67 = (1.0 / fConst58);
	fConst68 = (0 - fConst45);
	fConst69 = (1.0 / (fConst49 * fConst56));
	fConst70 = (2 * (0 - fConst43));
	fConst71 = (1 + ((fConst39 - 1.0000000000000004) / fConst36));
	fConst72 = (1.0 / (1 + ((fConst39 + 1.0000000000000004) / fConst36)));
	fConst73 = (1 + fConst39);
	fConst74 = (0 - ((1 - fConst39) / fConst73));
	fConst75 = (0 - fConst39);
	fConst76 = (1.0 / (fConst73 * fConst47));
	fConst77 = (2 * (0 - fConst37));
	fConst78 = (1 + ((fConst45 - 1.0) / fConst42));
	fConst79 = (1.0 / (1 + ((1.0 + fConst45) / fConst42)));
	fConst80 = (0 - fConst54);
	fConst81 = (2 * (0 - fConst52));
	fConst82 = (0.025 / fConst2);
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
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = (1.000000000000001e-05 * fslider1);
	double 	fSlow2 = (0.0010000000000000009 * pow(10,(0.05 * fslider2)));
	double 	fSlow3 = fslider3;
	double 	fSlow4 = (1.25 * fSlow3);
	double 	fSlow5 = (2 * (fSlow3 - 0.5));
	double 	fSlow6 = (0.024937655860349125 * (1 - max((double)0, fSlow5)));
	double 	fSlow7 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow8 = (fConst72 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow9 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow10 = (fConst72 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow11 = (1 - max((double)0, (0 - fSlow5)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (0.5 * fRec0[1]);
		double fTemp1 = (fTemp0 + (0.4 * fRec2[1]));
		double fTemp2 = (fTemp1 + (0.3 * fRec4[1]));
		double fTemp3 = (1e-15 + (0.0041 * fRec9[1]));
		fVec0[0] = fTemp3;
		fRec10[0] = ((fConst7 * (fVec0[0] + fVec0[1])) + (fConst6 * fRec10[1]));
		fRec11[0] = (fSlow0 + (0.999 * fRec11[1]));
		fRec13[0] = (fSlow1 + (0.999 * fRec13[1]));
		double fTemp4 = (double)input0[i];
		fVec1[0] = fTemp4;
		fRec26[0] = (fConst18 * ((fVec1[0] - fVec1[1]) + (fConst17 * fRec26[1])));
		fRec25[0] = (fConst18 * ((fRec26[0] - fRec26[1]) + (fConst17 * fRec25[1])));
		fRec24[0] = (fRec25[0] - (fConst15 * ((fConst14 * fRec24[2]) + (fConst9 * fRec24[1]))));
		fRec23[0] = ((fConst15 * (fRec24[2] + (fRec24[0] + (2 * fRec24[1])))) - (fConst13 * ((fConst11 * fRec23[2]) + (fConst9 * fRec23[1]))));
		fRec27[0] = (fSlow2 + (0.999 * fRec27[1]));
		double fTemp5 = (1e-15 + (0.027 * fRec22[1]));
		fVec2[0] = fTemp5;
		fRec28[0] = ((fConst23 * (fVec2[0] + fVec2[1])) + (fConst22 * fRec28[1]));
		fRec22[0] = (Ftube(TUBE_TABLE_12AU7_68k, ((fRec28[0] + (fConst19 * (fRec27[0] * (fRec23[2] + (fRec23[0] + (2 * fRec23[1])))))) - 1.2572399999999988)) - 83.43555555555557);
		fRec21[0] = ((fConst25 * ((fConst24 * fRec22[1]) + (fConst1 * fRec22[0]))) + (fConst3 * fRec21[1]));
		double fTemp6 = (1e-15 + (0.015 * fRec30[1]));
		fVec3[0] = fTemp6;
		fRec31[0] = ((fConst29 * (fVec3[0] + fVec3[1])) + (fConst28 * fRec31[1]));
		fRec30[0] = (Ftube(TUBE_TABLE_12AU7_250k, ((fRec31[0] + fRec20[1]) - 0.776161999999999)) - 78.25586666666666);
		fRec29[0] = ((fConst25 * ((fConst24 * fRec30[1]) + (fConst1 * fRec30[0]))) + (fConst3 * fRec29[1]));
		fRec20[0] = ((0.6 * fRec29[0]) + fRec21[0]);
		fRec19[0] = ((fConst7 * (fRec20[0] + fRec20[1])) + (fConst6 * fRec19[1]));
		double fTemp7 = (1e-15 + (0.015 * fRec18[1]));
		fVec4[0] = fTemp7;
		fRec32[0] = ((fConst29 * (fVec4[0] + fVec4[1])) + (fConst28 * fRec32[1]));
		fRec18[0] = (Ftube(TUBE_TABLE_12AU7_250k, ((fRec32[0] + fRec19[0]) - 0.776161999999999)) - 78.25586666666666);
		fRec17[0] = ((fConst25 * ((fConst24 * fRec18[1]) + (fConst1 * fRec18[0]))) + (fConst3 * fRec17[1]));
		double fTemp8 = (1e-15 + (0.0082 * fRec34[1]));
		fVec5[0] = fTemp8;
		fRec35[0] = ((fConst33 * (fVec5[0] + fVec5[1])) + (fConst32 * fRec35[1]));
		fRec34[0] = (Ftube(TUBE_TABLE_12AU7_250k, ((fRec35[0] + fRec16[1]) - 0.445486999999999)) - 75.67231707317073);
		fRec33[0] = ((fConst25 * ((fConst24 * fRec34[1]) + (fConst1 * fRec34[0]))) + (fConst3 * fRec33[1]));
		fRec16[0] = ((0.6 * fRec33[0]) + fRec17[0]);
		double fTemp9 = (1e-15 + (0.0082 * fRec15[1]));
		fVec6[0] = fTemp9;
		fRec36[0] = ((fConst33 * (fVec6[0] + fVec6[1])) + (fConst32 * fRec36[1]));
		fRec15[0] = (Ftube(TUBE_TABLE_12AU7_250k, ((fRec36[0] + fRec16[0]) - 0.445486999999999)) - 75.67231707317073);
		fRec14[0] = ((fConst25 * ((fConst24 * fRec15[1]) + (fConst1 * fRec15[0]))) + (fConst3 * fRec14[1]));
		double fTemp10 = (fRec14[0] * (1 - fRec13[0]));
		double fTemp11 = (fRec14[0] * fRec13[0]);
		double fTemp12 = fabs(fTemp11);
		fRec39[0] = ((9.999999999998899e-05 * fTemp12) + (0.9999 * fRec39[1]));
		double fTemp13 = max(fRec39[0], fTemp12);
		fVec7[IOTA&32767] = fTemp13;
		fRec38[0] = ((fVec7[IOTA&32767] + fRec38[1]) - fVec7[(IOTA-iConst34)&32767]);
		fRec37[0] = ((fConst35 * fRec38[0]) + (0.999 * fRec37[1]));
		double fTemp14 = max(-1.0, min(-0.01, (fVec7[IOTA&32767] - (1.0 + (1.02 * fRec37[0])))));
		double fTemp15 = (0 - fTemp14);
		double fTemp16 = (40.1 * fTemp15);
		double fTemp17 = max((double)-600, fTemp16);
		double fTemp18 = (0 - fTemp17);
		double fTemp19 = (fTemp11 - fTemp14);
		double fTemp20 = (40.1 * fTemp19);
		double fTemp21 = max((double)-600, fTemp20);
		double fTemp22 = (0 - fTemp21);
		double fTemp23 = (((int((fabs(fTemp20) > 0.0001)))?((int((fTemp21 < -50)))?(exp(fTemp21) * fTemp22):(fTemp21 / (1 - exp(fTemp22)))):(1 + (fTemp19 * (20.05 + (134.00083333333336 * fTemp19))))) - ((int((fabs(fTemp16) > 0.0001)))?((int((fTemp17 < -50)))?(exp(fTemp17) * fTemp18):(fTemp17 / (1 - exp(fTemp18)))):(1 + (fTemp15 * (20.05 + (134.00083333333336 * fTemp15))))));
		double fTemp24 = (fConst38 * fRec41[1]);
		fRec47[0] = ((0.024937655860349125 * fTemp23) - (fConst65 * ((fConst63 * fRec47[2]) + (fConst61 * fRec47[1]))));
		double fTemp25 = (fRec47[2] + (fRec47[0] + (2 * fRec47[1])));
		fVec8[0] = fTemp25;
		fRec46[0] = ((fConst66 * ((fConst24 * fVec8[1]) + (fConst1 * fVec8[0]))) + (fConst3 * fRec46[1]));
		fRec45[0] = ((fConst67 * (fRec46[0] + fRec46[1])) + (fConst59 * fRec45[1]));
		fRec44[0] = (fRec45[0] - (fConst57 * ((fConst55 * fRec44[2]) + (fConst53 * fRec44[1]))));
		double fTemp26 = (fRec44[2] + (fRec44[0] + (2 * fRec44[1])));
		fVec9[0] = fTemp26;
		fRec43[0] = ((fConst69 * ((fConst68 * fVec9[1]) + (fConst45 * fVec9[0]))) + (fConst50 * fRec43[1]));
		fRec42[0] = (fRec43[0] - (fConst48 * ((fConst46 * fRec42[2]) + (fConst44 * fRec42[1]))));
		fRec41[0] = ((fConst48 * (((fConst43 * fRec42[0]) + (fConst70 * fRec42[1])) + (fConst43 * fRec42[2]))) - (fConst41 * ((fConst40 * fRec41[2]) + fTemp24)));
		double fTemp27 = max((double)-1, min((double)1, (fSlow7 * (fRec41[2] + (fConst41 * (fTemp24 + (fConst40 * fRec41[0])))))));
		fRec51[0] = ((fConst69 * (fVec9[0] + fVec9[1])) + (fConst50 * fRec51[1]));
		fRec50[0] = (fRec51[0] - (fConst48 * ((fConst46 * fRec50[2]) + (fConst44 * fRec50[1]))));
		double fTemp28 = (fRec50[2] + (fRec50[0] + (2 * fRec50[1])));
		fVec10[0] = fTemp28;
		fRec49[0] = ((fConst76 * ((fConst75 * fVec10[1]) + (fConst39 * fVec10[0]))) + (fConst74 * fRec49[1]));
		fRec48[0] = (fRec49[0] - (fConst72 * ((fConst71 * fRec48[2]) + (fConst38 * fRec48[1]))));
		double fTemp29 = max((double)-1, min((double)1, (fSlow8 * (((fConst37 * fRec48[0]) + (fConst77 * fRec48[1])) + (fConst37 * fRec48[2])))));
		double fTemp30 = (fConst38 * fRec52[1]);
		double fTemp31 = (fConst44 * fRec53[1]);
		fRec55[0] = ((fConst67 * ((fConst80 * fRec46[1]) + (fConst54 * fRec46[0]))) + (fConst59 * fRec55[1]));
		fRec54[0] = (fRec55[0] - (fConst57 * ((fConst55 * fRec54[2]) + (fConst53 * fRec54[1]))));
		fRec53[0] = ((fConst57 * (((fConst52 * fRec54[0]) + (fConst81 * fRec54[1])) + (fConst52 * fRec54[2]))) - (fConst79 * ((fConst78 * fRec53[2]) + fTemp31)));
		fRec52[0] = ((fRec53[2] + (fConst79 * (fTemp31 + (fConst78 * fRec53[0])))) - (fConst41 * ((fConst40 * fRec52[2]) + fTemp30)));
		double fTemp32 = max((double)-1, min((double)1, (fSlow9 * (fRec52[2] + (fConst41 * (fTemp30 + (fConst40 * fRec52[0])))))));
		fRec57[0] = ((fConst76 * (fVec10[0] + fVec10[1])) + (fConst74 * fRec57[1]));
		fRec56[0] = (fRec57[0] - (fConst72 * ((fConst71 * fRec56[2]) + (fConst38 * fRec56[1]))));
		double fTemp33 = max((double)-1, min((double)1, (fSlow10 * (fRec56[2] + (fRec56[0] + (2 * fRec56[1]))))));
		double fTemp34 = ((1.2589412 * (fTemp33 * (1 - (0.3333333333333333 * faustpower<2>(fTemp33))))) + (1.584893192 * ((fTemp32 * (1 - (0.3333333333333333 * faustpower<2>(fTemp32)))) + ((fTemp29 * (1 - (0.3333333333333333 * faustpower<2>(fTemp29)))) + (0.8413951417869425 * (fTemp27 * (1 - (0.3333333333333333 * faustpower<2>(fTemp27)))))))));
		fVec11[0] = fTemp34;
		fRec40[0] = ((fConst7 * (fVec11[0] + fVec11[1])) + (fConst6 * fRec40[1]));
		double fTemp35 = (((fSlow11 * fRec40[0]) + (fSlow6 * fTemp23)) + (fTemp10 * (1 + (fSlow4 * ((4 - (4 * fabs(fTemp10))) - 1)))));
		fVec12[0] = fTemp35;
		fRec12[0] = ((fConst7 * (fVec12[0] + fVec12[1])) + (fConst6 * fRec12[1]));
		double fTemp36 = (fRec12[0] * fRec11[0]);
		fRec9[0] = (Ftube(TUBE_TABLE_6V6_68k, ((fTemp36 + fRec10[0]) - 0.664540999999999)) - 87.91682926829267);
		fRec8[0] = ((fConst82 * ((fConst24 * fRec9[1]) + (fConst1 * fRec9[0]))) + (fConst3 * fRec8[1]));
		double fTemp37 = (1e-15 + (0.0041 * fRec59[1]));
		fVec13[0] = fTemp37;
		fRec60[0] = ((fConst7 * (fVec13[0] + fVec13[1])) + (fConst6 * fRec60[1]));
		fRec59[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec60[0] + fTemp36) - 0.659760999999999)) - 89.08268292682925);
		fRec58[0] = ((fConst82 * ((fConst24 * fRec59[1]) + (fConst1 * fRec59[0]))) + (fConst3 * fRec58[1]));
		double fTemp38 = (min(0.7, fRec58[0]) + max(-0.75, fRec8[0]));
		double fTemp39 = ((fTemp38 + (0.2 * fRec6[1])) - fTemp2);
		fRec6[0] = fTemp39;
		double 	fRec7 = (0 - (0.2 * fTemp39));
		fRec4[0] = (fRec7 + fRec6[1]);
		double 	fRec5 = (0.3 * (fTemp38 - fTemp2));
		fRec2[0] = (fRec5 + fRec4[1]);
		double 	fRec3 = (0.4 * (fTemp38 - fTemp1));
		fRec0[0] = (fRec3 + fRec2[1]);
		double 	fRec1 = (0.5 * (fTemp38 - fTemp0));
		output0[i] = (FAUSTFLOAT)(fRec1 + fRec0[1]);
		// post processing
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fRec6[1] = fRec6[0];
		fRec58[1] = fRec58[0];
		fRec59[1] = fRec59[0];
		fRec60[1] = fRec60[0];
		fVec13[1] = fVec13[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec12[1] = fRec12[0];
		fVec12[1] = fVec12[0];
		fRec40[1] = fRec40[0];
		fVec11[1] = fVec11[0];
		fRec56[2] = fRec56[1]; fRec56[1] = fRec56[0];
		fRec57[1] = fRec57[0];
		fRec52[2] = fRec52[1]; fRec52[1] = fRec52[0];
		fRec53[2] = fRec53[1]; fRec53[1] = fRec53[0];
		fRec54[2] = fRec54[1]; fRec54[1] = fRec54[0];
		fRec55[1] = fRec55[0];
		fRec48[2] = fRec48[1]; fRec48[1] = fRec48[0];
		fRec49[1] = fRec49[0];
		fVec10[1] = fVec10[0];
		fRec50[2] = fRec50[1]; fRec50[1] = fRec50[0];
		fRec51[1] = fRec51[0];
		fRec41[2] = fRec41[1]; fRec41[1] = fRec41[0];
		fRec42[2] = fRec42[1]; fRec42[1] = fRec42[0];
		fRec43[1] = fRec43[0];
		fVec9[1] = fVec9[0];
		fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
		fRec45[1] = fRec45[0];
		fRec46[1] = fRec46[0];
		fVec8[1] = fVec8[0];
		fRec47[2] = fRec47[1]; fRec47[1] = fRec47[0];
		fRec37[1] = fRec37[0];
		fRec38[1] = fRec38[0];
		IOTA = IOTA+1;
		fRec39[1] = fRec39[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec36[1] = fRec36[0];
		fVec6[1] = fVec6[0];
		fRec16[1] = fRec16[0];
		fRec33[1] = fRec33[0];
		fRec34[1] = fRec34[0];
		fRec35[1] = fRec35[0];
		fVec5[1] = fVec5[0];
		fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec32[1] = fRec32[0];
		fVec4[1] = fVec4[0];
		fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fVec3[1] = fVec3[0];
		fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fRec28[1] = fRec28[0];
		fVec2[1] = fVec2[0];
		fRec27[1] = fRec27[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fVec1[1] = fVec1[0];
		fRec13[1] = fRec13[0];
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
		fVec0[1] = fVec0[0];
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

} // end namespace gxamp8
