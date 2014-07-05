// generated from file '../src/LV2/faust/gxamp6.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp6 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double 	fVec0[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fRec10[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec11[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec16[2];
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fVec1[2];
	double 	fConst14;
	double 	fRec29[2];
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fRec26[3];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec30[2];
	double 	fVec2[2];
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fRec31[2];
	double 	fRec25[2];
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fRec24[2];
	double 	fVec3[2];
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fRec34[2];
	double 	fRec33[2];
	double 	fRec32[2];
	double 	fRec23[2];
	double 	fRec22[2];
	double 	fVec4[2];
	double 	fRec35[2];
	double 	fRec21[2];
	double 	fRec20[2];
	double 	fVec5[2];
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fRec38[2];
	double 	fRec37[2];
	double 	fRec36[2];
	double 	fRec19[2];
	double 	fVec6[2];
	double 	fRec39[2];
	double 	fRec18[2];
	double 	fRec17[2];
	double 	fRec15[2];
	int 	IOTA;
	double 	fVec7[32768];
	int 	iConst32;
	double 	fRec14[2];
	double 	fConst33;
	double 	fRec13[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
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
	double 	fConst58;
	double 	fConst59;
	double 	fRec48[3];
	double 	fVec8[2];
	double 	fConst60;
	double 	fRec47[2];
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fRec46[2];
	double 	fRec45[3];
	double 	fVec9[2];
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fRec44[2];
	double 	fRec43[3];
	double 	fVec10[2];
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fRec42[2];
	double 	fRec41[3];
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fRec51[2];
	double 	fRec50[3];
	double 	fConst73;
	double 	fRec49[3];
	double 	fConst74;
	double 	fConst75;
	double 	fConst76;
	double 	fRec55[2];
	double 	fRec54[3];
	double 	fConst77;
	double 	fRec53[3];
	double 	fRec52[3];
	double 	fConst78;
	double 	fRec57[2];
	double 	fRec56[3];
	double 	fConst79;
	double 	fVec11[2];
	double 	fRec40[2];
	double 	fVec12[2];
	double 	fRec12[2];
	double 	fRec9[2];
	double 	fConst80;
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
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<32768; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<3; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<3; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<3; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<3; i++) fRec50[i] = 0;
	for (int i=0; i<3; i++) fRec49[i] = 0;
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
	fConst1 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst2 = (1 + fConst1);
	fConst3 = (1.0 / fConst2);
	fConst4 = (0 - ((1 - fConst1) / fConst2));
	fConst5 = tan((37699.11184307752 / double(iConst0)));
	fConst6 = (2 * (1 - (1.0 / faustpower<2>(fConst5))));
	fConst7 = (1.0 / fConst5);
	fConst8 = (1 + ((fConst7 - 0.7653668647301795) / fConst5));
	fConst9 = (1.0 / (1 + ((0.7653668647301795 + fConst7) / fConst5)));
	fConst10 = (1 + ((fConst7 - 1.8477590650225735) / fConst5));
	fConst11 = (1.0 / (1 + ((fConst7 + 1.8477590650225735) / fConst5)));
	fConst12 = (973.8937226128359 / double(iConst0));
	fConst13 = (1 - fConst12);
	fConst14 = (1.0 / (1 + fConst12));
	fConst15 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst16 = (1 + fConst15);
	fConst17 = (1.0 / fConst16);
	fConst18 = (0 - ((1 - fConst15) / fConst16));
	fConst19 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst20 = (0 - fConst19);
	fConst21 = (1 + fConst19);
	fConst22 = (0.05 / fConst21);
	fConst23 = (0 - ((1 - fConst19) / fConst21));
	fConst24 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst25 = (1 + fConst24);
	fConst26 = (1.0 / fConst25);
	fConst27 = (0 - ((1 - fConst24) / fConst25));
	fConst28 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst29 = (1 + fConst28);
	fConst30 = (1.0 / fConst29);
	fConst31 = (0 - ((1 - fConst28) / fConst29));
	IOTA = 0;
	iConst32 = int((int((0.1111111111111111 * iConst0)) & 65535));
	fConst33 = (0.009000000000000008 / double(iConst0));
	fConst34 = tan((942.4777960769379 / double(iConst0)));
	fConst35 = (1.0 / faustpower<2>(fConst34));
	fConst36 = (2 * (1 - fConst35));
	fConst37 = (1.0 / fConst34);
	fConst38 = (1 + ((fConst37 - 1.0000000000000004) / fConst34));
	fConst39 = (1.0 / (1 + ((fConst37 + 1.0000000000000004) / fConst34)));
	fConst40 = tan((3769.9111843077517 / double(iConst0)));
	fConst41 = (1.0 / faustpower<2>(fConst40));
	fConst42 = (2 * (1 - fConst41));
	fConst43 = (1.0 / fConst40);
	fConst44 = (1 + ((fConst43 - 1.0000000000000004) / fConst40));
	fConst45 = (1 + ((fConst43 + 1.0000000000000004) / fConst40));
	fConst46 = (1.0 / fConst45);
	fConst47 = tan((10053.096491487338 / double(iConst0)));
	fConst48 = (1.0 / faustpower<2>(fConst47));
	fConst49 = (2 * (1 - fConst48));
	fConst50 = (1.0 / fConst47);
	fConst51 = (1 + ((fConst50 - 1.0000000000000004) / fConst47));
	fConst52 = (1 + ((1.0000000000000004 + fConst50) / fConst47));
	fConst53 = (1.0 / fConst52);
	fConst54 = tan((47123.8898038469 / double(iConst0)));
	fConst55 = (2 * (1 - (1.0 / faustpower<2>(fConst54))));
	fConst56 = (1.0 / fConst54);
	fConst57 = (1 + ((fConst56 - 1.414213562373095) / fConst54));
	fConst58 = (1 + ((1.414213562373095 + fConst56) / fConst54));
	fConst59 = (1.0 / fConst58);
	fConst60 = (1.0 / (fConst21 * fConst58));
	fConst61 = (1 + fConst50);
	fConst62 = (1.0 / fConst61);
	fConst63 = (0 - ((1 - fConst50) / fConst61));
	fConst64 = (1 + fConst43);
	fConst65 = (1.0 / (fConst64 * fConst52));
	fConst66 = (0 - ((1 - fConst43) / fConst64));
	fConst67 = (1 + fConst37);
	fConst68 = (1.0 / (fConst67 * fConst45));
	fConst69 = (0 - ((1 - fConst37) / fConst67));
	fConst70 = (1 + ((fConst37 - 1.0) / fConst34));
	fConst71 = (1.0 / (1 + ((1.0 + fConst37) / fConst34)));
	fConst72 = (0 - fConst43);
	fConst73 = (2 * (0 - fConst41));
	fConst74 = (1 + ((fConst43 - 1.0) / fConst40));
	fConst75 = (1.0 / (1 + ((1.0 + fConst43) / fConst40)));
	fConst76 = (0 - fConst50);
	fConst77 = (2 * (0 - fConst48));
	fConst78 = (0 - fConst37);
	fConst79 = (2 * (0 - fConst35));
	fConst80 = (0.025 / fConst21);
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
	double 	fSlow5 = (0.024937655860349125 * (1 - max((double)0, fSlow4)));
	double 	fSlow6 = (1.25 * fSlow3);
	double 	fSlow7 = (fConst39 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow8 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow9 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow10 = (fConst39 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow11 = (1 - max((double)0, (0 - fSlow4)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (0.4 * fRec2[1]);
		double fTemp1 = (0.5 * fRec0[1]);
		double fTemp2 = (fTemp1 + ((0.3 * fRec4[1]) + fTemp0));
		double fTemp3 = (1e-15 + (0.0041 * fRec9[1]));
		fVec0[0] = fTemp3;
		fRec10[0] = ((fConst4 * fRec10[1]) + (fConst3 * (fVec0[0] + fVec0[1])));
		fRec11[0] = ((0.999 * fRec11[1]) + fSlow0);
		fRec16[0] = (fSlow1 + (0.999 * fRec16[1]));
		double fTemp4 = (double)input0[i];
		fVec1[0] = fTemp4;
		fRec29[0] = (fConst14 * ((fVec1[0] - fVec1[1]) + (fConst13 * fRec29[1])));
		fRec28[0] = (fConst14 * ((fRec29[0] - fRec29[1]) + (fConst13 * fRec28[1])));
		fRec27[0] = (fRec28[0] - (fConst11 * ((fConst10 * fRec27[2]) + (fConst6 * fRec27[1]))));
		fRec26[0] = ((fConst11 * (fRec27[2] + (fRec27[0] + (2 * fRec27[1])))) - (fConst9 * ((fConst8 * fRec26[2]) + (fConst6 * fRec26[1]))));
		fRec30[0] = ((0.999 * fRec30[1]) + fSlow2);
		double fTemp5 = (1e-15 + (0.027 * fRec25[1]));
		fVec2[0] = fTemp5;
		fRec31[0] = ((fConst18 * fRec31[1]) + (fConst17 * (fVec2[0] + fVec2[1])));
		fRec25[0] = (Ftube(TUBE_TABLE_6DJ8_68k, ((fRec31[0] + (fConst9 * (fRec30[0] * (fRec26[2] + (fRec26[0] + (2 * fRec26[1])))))) - 1.863945999999999)) - 60.96496296296296);
		fRec24[0] = ((fConst23 * fRec24[1]) + (fConst22 * ((fConst19 * fRec25[0]) + (fConst20 * fRec25[1]))));
		double fTemp6 = (1e-15 + (0.015 * fRec33[1]));
		fVec3[0] = fTemp6;
		fRec34[0] = ((fConst27 * fRec34[1]) + (fConst26 * (fVec3[0] + fVec3[1])));
		fRec33[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec34[0] + fRec23[1]) - 1.2716089999999989)) - 45.22606666666667);
		fRec32[0] = ((fConst23 * fRec32[1]) + (fConst22 * ((fConst19 * fRec33[0]) + (fConst20 * fRec33[1]))));
		fRec23[0] = ((0.6 * fRec32[0]) + fRec24[0]);
		fRec22[0] = ((fConst4 * fRec22[1]) + (fConst3 * (fRec23[0] + fRec23[1])));
		double fTemp7 = (1e-15 + (0.015 * fRec21[1]));
		fVec4[0] = fTemp7;
		fRec35[0] = ((fConst27 * fRec35[1]) + (fConst26 * (fVec4[0] + fVec4[1])));
		fRec21[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec35[0] + fRec22[0]) - 1.2716089999999989)) - 45.22606666666667);
		fRec20[0] = ((fConst23 * fRec20[1]) + (fConst22 * ((fConst19 * fRec21[0]) + (fConst20 * fRec21[1]))));
		double fTemp8 = (1e-15 + (0.0082 * fRec37[1]));
		fVec5[0] = fTemp8;
		fRec38[0] = ((fConst31 * fRec38[1]) + (fConst30 * (fVec5[0] + fVec5[1])));
		fRec37[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec38[0] + fRec19[1]) - 0.797042999999999)) - 32.799634146341475);
		fRec36[0] = ((fConst23 * fRec36[1]) + (fConst22 * ((fConst19 * fRec37[0]) + (fConst20 * fRec37[1]))));
		fRec19[0] = ((0.6 * fRec36[0]) + fRec20[0]);
		double fTemp9 = (1e-15 + (0.0082 * fRec18[1]));
		fVec6[0] = fTemp9;
		fRec39[0] = ((fConst31 * fRec39[1]) + (fConst30 * (fVec6[0] + fVec6[1])));
		fRec18[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec39[0] + fRec19[0]) - 0.797042999999999)) - 32.799634146341475);
		fRec17[0] = ((fConst23 * fRec17[1]) + (fConst22 * ((fConst19 * fRec18[0]) + (fConst20 * fRec18[1]))));
		double fTemp10 = (fRec17[0] * fRec16[0]);
		double fTemp11 = fabs(fTemp10);
		fRec15[0] = ((0.9999 * fRec15[1]) + (9.999999999998899e-05 * fTemp11));
		double fTemp12 = max(fRec15[0], fTemp11);
		fVec7[IOTA&32767] = fTemp12;
		fRec14[0] = ((fVec7[IOTA&32767] + fRec14[1]) - fVec7[(IOTA-iConst32)&32767]);
		fRec13[0] = ((0.999 * fRec13[1]) + (fConst33 * fRec14[0]));
		double fTemp13 = max(-1.0, min(-0.01, (fVec7[IOTA&32767] - (1.0 + (1.02 * fRec13[0])))));
		double fTemp14 = (0 - fTemp13);
		double fTemp15 = (40.1 * fTemp14);
		double fTemp16 = max((double)-600, fTemp15);
		double fTemp17 = (0 - fTemp16);
		double fTemp18 = (fTemp10 - fTemp13);
		double fTemp19 = (40.1 * fTemp18);
		double fTemp20 = max((double)-600, fTemp19);
		double fTemp21 = (0 - fTemp20);
		double fTemp22 = (((int((fabs(fTemp19) > 0.0001)))?((int((fTemp20 < -50)))?(fTemp21 * exp(fTemp20)):(fTemp20 / (1 - exp(fTemp21)))):(1 + (fTemp18 * (20.05 + (134.00083333333336 * fTemp18))))) - ((int((fabs(fTemp15) > 0.0001)))?((int((fTemp16 < -50)))?(fTemp17 * exp(fTemp16)):(fTemp16 / (1 - exp(fTemp17)))):(1 + (fTemp14 * (20.05 + (134.00083333333336 * fTemp14))))));
		double fTemp23 = (fRec17[0] * (1 - fRec16[0]));
		fRec48[0] = ((0.024937655860349125 * fTemp22) - (fConst59 * ((fConst57 * fRec48[2]) + (fConst55 * fRec48[1]))));
		double fTemp24 = (fRec48[2] + (fRec48[0] + (2 * fRec48[1])));
		fVec8[0] = fTemp24;
		fRec47[0] = ((fConst23 * fRec47[1]) + (fConst60 * ((fConst19 * fVec8[0]) + (fConst20 * fVec8[1]))));
		fRec46[0] = ((fConst63 * fRec46[1]) + (fConst62 * (fRec47[0] + fRec47[1])));
		fRec45[0] = (fRec46[0] - (fConst53 * ((fConst51 * fRec45[2]) + (fConst49 * fRec45[1]))));
		double fTemp25 = (fRec45[2] + (fRec45[0] + (2 * fRec45[1])));
		fVec9[0] = fTemp25;
		fRec44[0] = ((fConst66 * fRec44[1]) + (fConst65 * (fVec9[0] + fVec9[1])));
		fRec43[0] = (fRec44[0] - (fConst46 * ((fConst44 * fRec43[2]) + (fConst42 * fRec43[1]))));
		double fTemp26 = (fRec43[2] + (fRec43[0] + (2 * fRec43[1])));
		fVec10[0] = fTemp26;
		fRec42[0] = ((fConst69 * fRec42[1]) + (fConst68 * (fVec10[0] + fVec10[1])));
		fRec41[0] = (fRec42[0] - (fConst39 * ((fConst38 * fRec41[2]) + (fConst36 * fRec41[1]))));
		double fTemp27 = max((double)-1, min((double)1, (fSlow7 * (fRec41[2] + (fRec41[0] + (2 * fRec41[1]))))));
		double fTemp28 = (fConst36 * fRec49[1]);
		fRec51[0] = ((fConst66 * fRec51[1]) + (fConst65 * ((fConst43 * fVec9[0]) + (fConst72 * fVec9[1]))));
		fRec50[0] = (fRec51[0] - (fConst46 * ((fConst44 * fRec50[2]) + (fConst42 * fRec50[1]))));
		fRec49[0] = ((fConst46 * (((fConst41 * fRec50[0]) + (fConst73 * fRec50[1])) + (fConst41 * fRec50[2]))) - (fConst71 * ((fConst70 * fRec49[2]) + fTemp28)));
		double fTemp29 = max((double)-1, min((double)1, (fSlow8 * (fRec49[2] + (fConst71 * (fTemp28 + (fConst70 * fRec49[0])))))));
		double fTemp30 = (fConst36 * fRec52[1]);
		double fTemp31 = (fConst42 * fRec53[1]);
		fRec55[0] = ((fConst63 * fRec55[1]) + (fConst62 * ((fConst50 * fRec47[0]) + (fConst76 * fRec47[1]))));
		fRec54[0] = (fRec55[0] - (fConst53 * ((fConst51 * fRec54[2]) + (fConst49 * fRec54[1]))));
		fRec53[0] = ((fConst53 * (((fConst48 * fRec54[0]) + (fConst77 * fRec54[1])) + (fConst48 * fRec54[2]))) - (fConst75 * ((fConst74 * fRec53[2]) + fTemp31)));
		fRec52[0] = ((fRec53[2] + (fConst75 * (fTemp31 + (fConst74 * fRec53[0])))) - (fConst71 * ((fConst70 * fRec52[2]) + fTemp30)));
		double fTemp32 = max((double)-1, min((double)1, (fSlow9 * (fRec52[2] + (fConst71 * (fTemp30 + (fConst70 * fRec52[0])))))));
		fRec57[0] = ((fConst69 * fRec57[1]) + (fConst68 * ((fConst37 * fVec10[0]) + (fConst78 * fVec10[1]))));
		fRec56[0] = (fRec57[0] - (fConst39 * ((fConst38 * fRec56[2]) + (fConst36 * fRec56[1]))));
		double fTemp33 = max((double)-1, min((double)1, (fSlow10 * (((fConst35 * fRec56[0]) + (fConst79 * fRec56[1])) + (fConst35 * fRec56[2])))));
		double fTemp34 = ((1.584893192 * ((fTemp33 * (1 - (0.3333333333333333 * faustpower<2>(fTemp33)))) + ((fTemp32 * (1 - (0.3333333333333333 * faustpower<2>(fTemp32)))) + (0.8413951417869425 * (fTemp29 * (1 - (0.3333333333333333 * faustpower<2>(fTemp29)))))))) + (1.2589412 * (fTemp27 * (1 - (0.3333333333333333 * faustpower<2>(fTemp27))))));
		fVec11[0] = fTemp34;
		fRec40[0] = ((fConst4 * fRec40[1]) + (fConst3 * (fVec11[0] + fVec11[1])));
		double fTemp35 = ((fSlow11 * fRec40[0]) + ((fTemp23 * (1 + (fSlow6 * ((4 - (4 * fabs(fTemp23))) - 1)))) + (fSlow5 * fTemp22)));
		fVec12[0] = fTemp35;
		fRec12[0] = ((fConst4 * fRec12[1]) + (fConst3 * (fVec12[0] + fVec12[1])));
		double fTemp36 = (fRec12[0] * fRec11[0]);
		fRec9[0] = (Ftube(TUBE_TABLE_6V6_68k, ((fTemp36 + fRec10[0]) - 0.664540999999999)) - 87.91682926829267);
		fRec8[0] = ((fConst23 * fRec8[1]) + (fConst80 * ((fConst19 * fRec9[0]) + (fConst20 * fRec9[1]))));
		double fTemp37 = (1e-15 + (0.0041 * fRec59[1]));
		fVec13[0] = fTemp37;
		fRec60[0] = ((fConst4 * fRec60[1]) + (fConst3 * (fVec13[0] + fVec13[1])));
		fRec59[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec60[0] + fTemp36) - 0.659760999999999)) - 89.08268292682925);
		fRec58[0] = ((fConst23 * fRec58[1]) + (fConst80 * ((fConst19 * fRec59[0]) + (fConst20 * fRec59[1]))));
		double fTemp38 = (min(0.7, fRec58[0]) + max(-0.75, fRec8[0]));
		double fTemp39 = ((fTemp38 + (0.2 * fRec6[1])) - fTemp2);
		fRec6[0] = fTemp39;
		double 	fRec7 = (0 - (0.2 * fTemp39));
		fRec4[0] = (fRec7 + fRec6[1]);
		double 	fRec5 = (0.3 * (fTemp38 - fTemp2));
		fRec2[0] = (fRec5 + fRec4[1]);
		double 	fRec3 = (0.4 * (fTemp38 - (fTemp0 + fTemp1)));
		fRec0[0] = (fRec3 + fRec2[1]);
		double 	fRec1 = (0.5 * (fTemp38 - fTemp1));
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
		fRec49[2] = fRec49[1]; fRec49[1] = fRec49[0];
		fRec50[2] = fRec50[1]; fRec50[1] = fRec50[0];
		fRec51[1] = fRec51[0];
		fRec41[2] = fRec41[1]; fRec41[1] = fRec41[0];
		fRec42[1] = fRec42[0];
		fVec10[1] = fVec10[0];
		fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
		fRec44[1] = fRec44[0];
		fVec9[1] = fVec9[0];
		fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
		fRec46[1] = fRec46[0];
		fRec47[1] = fRec47[0];
		fVec8[1] = fVec8[0];
		fRec48[2] = fRec48[1]; fRec48[1] = fRec48[0];
		fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		IOTA = IOTA+1;
		fRec15[1] = fRec15[0];
		fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec39[1] = fRec39[0];
		fVec6[1] = fVec6[0];
		fRec19[1] = fRec19[0];
		fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fRec38[1] = fRec38[0];
		fVec5[1] = fVec5[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec35[1] = fRec35[0];
		fVec4[1] = fVec4[0];
		fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec32[1] = fRec32[0];
		fRec33[1] = fRec33[0];
		fRec34[1] = fRec34[0];
		fVec3[1] = fVec3[0];
		fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec31[1] = fRec31[0];
		fVec2[1] = fVec2[0];
		fRec30[1] = fRec30[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fVec1[1] = fVec1[0];
		fRec16[1] = fRec16[0];
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

} // end namespace gxamp6
