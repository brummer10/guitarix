// generated from file '../src/faust/gxamp8.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp8 {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iConst0;
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
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fRec5[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec6[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec8[2];
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
	double 	fVec0[2];
	double 	fConst40;
	double 	fRec21[2];
	double 	fRec20[2];
	double 	fRec19[3];
	double 	fRec18[3];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec22[2];
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fRec23[2];
	double 	fRec17[3];
	double 	fConst46;
	double 	fConst47;
	double 	fRec16[2];
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fRec26[2];
	double 	fRec25[3];
	double 	fRec24[2];
	double 	fRec15[2];
	double 	fConst52;
	double 	fRec14[2];
	double 	fRec27[2];
	double 	fRec13[3];
	double 	fRec12[2];
	double 	fConst53;
	double 	fConst54;
	double 	fConst55;
	double 	fConst56;
	double 	fRec30[2];
	double 	fRec29[3];
	double 	fRec28[2];
	double 	fRec11[2];
	double 	fRec31[2];
	double 	fRec10[3];
	double 	fRec9[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec34[2];
	int 	IOTA;
	double 	fVec1[32768];
	int 	iConst57;
	double 	fRec33[2];
	double 	fConst58;
	double 	fRec32[2];
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;
	double 	fConst74;
	double 	fConst75;
	double 	fConst76;
	double 	fConst77;
	double 	fConst78;
	double 	fConst79;
	double 	fConst80;
	double 	fConst81;
	double 	fConst82;
	double 	fConst83;
	double 	fConst84;
	double 	fConst85;
	double 	fConst86;
	double 	fConst87;
	double 	fConst88;
	double 	fRec42[3];
	double 	fVec2[2];
	double 	fConst89;
	double 	fRec41[2];
	double 	fConst90;
	double 	fRec40[2];
	double 	fRec39[3];
	double 	fVec3[2];
	double 	fConst91;
	double 	fConst92;
	double 	fRec38[2];
	double 	fRec37[3];
	double 	fConst93;
	double 	fRec36[3];
	double 	fConst94;
	double 	fConst95;
	double 	fConst96;
	double 	fConst97;
	double 	fRec46[2];
	double 	fRec45[3];
	double 	fVec4[2];
	double 	fConst98;
	double 	fConst99;
	double 	fRec44[2];
	double 	fRec43[3];
	double 	fConst100;
	double 	fConst101;
	double 	fConst102;
	double 	fConst103;
	double 	fRec50[2];
	double 	fRec49[3];
	double 	fConst104;
	double 	fRec48[3];
	double 	fRec47[3];
	double 	fRec52[2];
	double 	fRec51[3];
	double 	fVec5[2];
	double 	fRec35[2];
	double 	fVec6[2];
	double 	fRec7[2];
	double 	fRec4[3];
	double 	fConst105;
	double 	fRec3[2];
	double 	fRec55[2];
	double 	fRec54[3];
	double 	fRec53[2];
	double 	fRec2[3];
	double 	fConst106;
	double 	fConst107;
	double 	fConst108;
	double 	fRec1[3];
	double 	fConst109;
	double 	fConst110;
	double 	fConst111;
	double 	fRec0[3];
	double 	fConst112;
	double 	fConst113;
	double 	fConst114;
	void clear_state_f();
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, float *input0, float *output0, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "pre 12AU7/ push-pull 6V6";
	name = N_("pre 12AU7/ push-pull 6V6");
	groups = 0;
	description = ""; // description (tooltip)
	category = "";       // category
	shortname = "";     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	load_ui = 0;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<32768; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<3; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<3; i++) fRec37[i] = 0;
	for (int i=0; i<3; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<3; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<3; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<3; i++) fRec49[i] = 0;
	for (int i=0; i<3; i++) fRec48[i] = 0;
	for (int i=0; i<3; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<3; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<3; i++) fRec54[i] = 0;
	for (int i=0; i<2; i++) fRec53[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = tan((15852.476530014095 / double(iConst0)));
	fConst2 = (2 * (1 - (1.0 / faustpower<2>(fConst1))));
	fConst3 = double((1.0 / double(iConst0)));
	fConst4 = (fConst3 / sin((31704.95306002819 * fConst3)));
	fConst5 = (3304.180407135934 * fConst4);
	fConst6 = (1.0 / fConst1);
	fConst7 = (1 + ((fConst6 - fConst5) / fConst1));
	fConst8 = (1.0 / (1 + ((fConst5 + fConst6) / fConst1)));
	fConst9 = tan((24787.166036823466 / double(iConst0)));
	fConst10 = (2 * (1 - (1.0 / faustpower<2>(fConst9))));
	fConst11 = (fConst3 / sin((49574.33207364693 * fConst3)));
	fConst12 = (24715.450285350493 * fConst11);
	fConst13 = (1.0 / fConst9);
	fConst14 = (1 + ((fConst13 - fConst12) / fConst9));
	fConst15 = (1.0 / (1 + ((fConst12 + fConst13) / fConst9)));
	fConst16 = tan((30300.661143873556 / double(iConst0)));
	fConst17 = (2 * (1 - (1.0 / faustpower<2>(fConst16))));
	fConst18 = (fConst3 / sin((60601.32228774711 * fConst3)));
	fConst19 = (8555.25565523957 * fConst18);
	fConst20 = (1.0 / fConst16);
	fConst21 = (1 + ((fConst20 - fConst19) / fConst16));
	fConst22 = (1.0 / (1 + ((fConst19 + fConst20) / fConst16)));
	fConst23 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst24 = (1 + fConst23);
	fConst25 = (0 - ((1 - fConst23) / fConst24));
	fConst26 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst27 = (1 + fConst26);
	fConst28 = (0 - ((1 - fConst26) / fConst27));
	fConst29 = (0.0041 / fConst27);
	fConst30 = tan((37699.11184307752 / double(iConst0)));
	fConst31 = (2 * (1 - (1.0 / faustpower<2>(fConst30))));
	fConst32 = (1.0 / fConst30);
	fConst33 = (1 + ((fConst32 - 0.7653668647301795) / fConst30));
	fConst34 = (1 + ((0.7653668647301795 + fConst32) / fConst30));
	fConst35 = (1.0 / fConst34);
	fConst36 = (1 + ((fConst32 - 1.8477590650225735) / fConst30));
	fConst37 = (1.0 / (1 + ((fConst32 + 1.8477590650225735) / fConst30)));
	fConst38 = (973.8937226128359 / double(iConst0));
	fConst39 = (1 - fConst38);
	fConst40 = (1.0 / (1 + fConst38));
	fConst41 = (2.0 / fConst34);
	fConst42 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst43 = (1 + fConst42);
	fConst44 = (0 - ((1 - fConst42) / fConst43));
	fConst45 = (0.027 / fConst43);
	fConst46 = (0 - fConst23);
	fConst47 = (0.1 / fConst24);
	fConst48 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst49 = (1 + fConst48);
	fConst50 = (0 - ((1 - fConst48) / fConst49));
	fConst51 = (0.015 / fConst49);
	fConst52 = (1.0 / fConst27);
	fConst53 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst54 = (1 + fConst53);
	fConst55 = (0 - ((1 - fConst53) / fConst54));
	fConst56 = (0.0082 / fConst54);
	IOTA = 0;
	iConst57 = int((int((0.1111111111111111 * iConst0)) & 65535));
	fConst58 = (0.009000000000000008 / double(iConst0));
	fConst59 = tan((942.4777960769379 / double(iConst0)));
	fConst60 = (1.0 / faustpower<2>(fConst59));
	fConst61 = (2 * (1 - fConst60));
	fConst62 = (1.0 / fConst59);
	fConst63 = (1 + ((fConst62 - 1.0) / fConst59));
	fConst64 = (1.0 / (1 + ((1.0 + fConst62) / fConst59)));
	fConst65 = tan((3769.9111843077517 / double(iConst0)));
	fConst66 = (1.0 / faustpower<2>(fConst65));
	fConst67 = (2 * (1 - fConst66));
	fConst68 = (1.0 / fConst65);
	fConst69 = (1 + ((fConst68 - 1.0000000000000004) / fConst65));
	fConst70 = (1 + ((fConst68 + 1.0000000000000004) / fConst65));
	fConst71 = (1.0 / fConst70);
	fConst72 = (1 + fConst68);
	fConst73 = (0 - ((1 - fConst68) / fConst72));
	fConst74 = tan((10053.096491487338 / double(iConst0)));
	fConst75 = (1.0 / faustpower<2>(fConst74));
	fConst76 = (2 * (1 - fConst75));
	fConst77 = (1.0 / fConst74);
	fConst78 = (1 + ((fConst77 - 1.0000000000000004) / fConst74));
	fConst79 = (1 + ((1.0000000000000004 + fConst77) / fConst74));
	fConst80 = (1.0 / fConst79);
	fConst81 = (1 + fConst77);
	fConst82 = (0 - ((1 - fConst77) / fConst81));
	fConst83 = tan((47123.8898038469 / double(iConst0)));
	fConst84 = (2 * (1 - (1.0 / faustpower<2>(fConst83))));
	fConst85 = (1.0 / fConst83);
	fConst86 = (1 + ((fConst85 - 1.414213562373095) / fConst83));
	fConst87 = (1 + ((1.414213562373095 + fConst85) / fConst83));
	fConst88 = (1.0 / fConst87);
	fConst89 = (1.0 / (fConst24 * fConst87));
	fConst90 = (1.0 / fConst81);
	fConst91 = (0 - fConst68);
	fConst92 = (1.0 / (fConst72 * fConst79));
	fConst93 = (2 * (0 - fConst66));
	fConst94 = (1 + ((fConst62 - 1.0000000000000004) / fConst59));
	fConst95 = (1.0 / (1 + ((fConst62 + 1.0000000000000004) / fConst59)));
	fConst96 = (1 + fConst62);
	fConst97 = (0 - ((1 - fConst62) / fConst96));
	fConst98 = (0 - fConst62);
	fConst99 = (1.0 / (fConst96 * fConst70));
	fConst100 = (2 * (0 - fConst60));
	fConst101 = (1 + ((fConst68 - 1.0) / fConst65));
	fConst102 = (1.0 / (1 + ((1.0 + fConst68) / fConst65)));
	fConst103 = (0 - fConst77);
	fConst104 = (2 * (0 - fConst75));
	fConst105 = (0.025 / fConst24);
	fConst106 = (2148.983059849188 * fConst18);
	fConst107 = (1 + ((fConst20 - fConst106) / fConst16));
	fConst108 = (1 + ((fConst106 + fConst20) / fConst16));
	fConst109 = (3491.150146031474 * fConst11);
	fConst110 = (1 + ((fConst13 - fConst109) / fConst9));
	fConst111 = (1 + ((fConst109 + fConst13) / fConst9));
	fConst112 = (829.9725931944553 * fConst4);
	fConst113 = (1 + ((fConst6 - fConst112) / fConst1));
	fConst114 = (1 + ((fConst112 + fConst6) / fConst1));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, float *input0, float *output0)
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
	double 	fSlow8 = (fConst95 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow9 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow10 = (fConst95 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow11 = (1 - max((double)0, (0 - fSlow5)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (fConst2 * fRec0[1]);
		double fTemp1 = (fConst10 * fRec1[1]);
		double fTemp2 = (fConst17 * fRec2[1]);
		fRec5[0] = ((fConst29 * (fRec4[1] + fRec4[2])) + (fConst28 * fRec5[1]));
		fRec6[0] = (fSlow0 + (0.999 * fRec6[1]));
		fRec8[0] = (fSlow1 + (0.999 * fRec8[1]));
		double fTemp3 = (double)input0[i];
		fVec0[0] = fTemp3;
		fRec21[0] = (fConst40 * ((fVec0[0] - fVec0[1]) + (fConst39 * fRec21[1])));
		fRec20[0] = (fConst40 * ((fRec21[0] - fRec21[1]) + (fConst39 * fRec20[1])));
		fRec19[0] = (fRec20[0] - (fConst37 * ((fConst36 * fRec19[2]) + (fConst31 * fRec19[1]))));
		fRec18[0] = ((fConst37 * (fRec19[2] + (fRec19[0] + (2 * fRec19[1])))) - (fConst35 * ((fConst33 * fRec18[2]) + (fConst31 * fRec18[1]))));
		fRec22[0] = (fSlow2 + (0.999 * fRec22[1]));
		fRec23[0] = ((fConst45 * (fRec17[1] + fRec17[2])) + (fConst44 * fRec23[1]));
		fRec17[0] = (Ftube(TUBE_TABLE_12AU7_68k, ((fRec23[0] + (fConst41 * (fRec22[0] * (fRec18[2] + (fRec18[0] + (2 * fRec18[1])))))) - 1.25724)) - 83.43555555555557);
		fRec16[0] = ((fConst47 * ((fConst46 * fRec17[1]) + (fConst23 * fRec17[0]))) + (fConst25 * fRec16[1]));
		fRec26[0] = ((fConst51 * (fRec25[1] + fRec25[2])) + (fConst50 * fRec26[1]));
		fRec25[0] = (Ftube(TUBE_TABLE_12AU7_250k, ((fRec26[0] + fRec15[1]) - 0.776162)) - 78.25586666666666);
		fRec24[0] = ((fConst47 * ((fConst46 * fRec25[1]) + (fConst23 * fRec25[0]))) + (fConst25 * fRec24[1]));
		fRec15[0] = ((0.6 * fRec24[0]) + fRec16[0]);
		fRec14[0] = ((fConst52 * (fRec15[0] + fRec15[1])) + (fConst28 * fRec14[1]));
		fRec27[0] = ((fConst51 * (fRec13[1] + fRec13[2])) + (fConst50 * fRec27[1]));
		fRec13[0] = (Ftube(TUBE_TABLE_12AU7_250k, ((fRec27[0] + fRec14[0]) - 0.776162)) - 78.25586666666666);
		fRec12[0] = ((fConst47 * ((fConst46 * fRec13[1]) + (fConst23 * fRec13[0]))) + (fConst25 * fRec12[1]));
		fRec30[0] = ((fConst56 * (fRec29[1] + fRec29[2])) + (fConst55 * fRec30[1]));
		fRec29[0] = (Ftube(TUBE_TABLE_12AU7_250k, ((fRec30[0] + fRec11[1]) - 0.445487)) - 75.67231707317073);
		fRec28[0] = ((fConst47 * ((fConst46 * fRec29[1]) + (fConst23 * fRec29[0]))) + (fConst25 * fRec28[1]));
		fRec11[0] = ((0.6 * fRec28[0]) + fRec12[0]);
		fRec31[0] = ((fConst56 * (fRec10[1] + fRec10[2])) + (fConst55 * fRec31[1]));
		fRec10[0] = (Ftube(TUBE_TABLE_12AU7_250k, ((fRec31[0] + fRec11[0]) - 0.445487)) - 75.67231707317073);
		fRec9[0] = ((fConst47 * ((fConst46 * fRec10[1]) + (fConst23 * fRec10[0]))) + (fConst25 * fRec9[1]));
		double fTemp4 = (fRec9[0] * (1 - fRec8[0]));
		double fTemp5 = (fRec9[0] * fRec8[0]);
		double fTemp6 = fabs(fTemp5);
		fRec34[0] = ((9.999999999998899e-05 * fTemp6) + (0.9999 * fRec34[1]));
		double fTemp7 = max(fRec34[0], fTemp6);
		fVec1[IOTA&32767] = fTemp7;
		fRec33[0] = ((fVec1[IOTA&32767] + fRec33[1]) - fVec1[(IOTA-iConst57)&32767]);
		fRec32[0] = ((fConst58 * fRec33[0]) + (0.999 * fRec32[1]));
		double fTemp8 = max(-1.0, min(-0.01, (fVec1[IOTA&32767] - (1.0 + (1.02 * fRec32[0])))));
		double fTemp9 = (0 - fTemp8);
		double fTemp10 = (40.1 * fTemp9);
		double fTemp11 = max((double)-600, fTemp10);
		double fTemp12 = (0 - fTemp11);
		double fTemp13 = (fTemp5 - fTemp8);
		double fTemp14 = (40.1 * fTemp13);
		double fTemp15 = max((double)-600, fTemp14);
		double fTemp16 = (0 - fTemp15);
		double fTemp17 = (((int((fabs(fTemp14) > 0.0001)))?((int((fTemp15 < -50)))?(exp(fTemp15) * fTemp16):(fTemp15 / (1 - exp(fTemp16)))):(1 + (fTemp13 * (20.05 + (134.00083333333336 * fTemp13))))) - ((int((fabs(fTemp10) > 0.0001)))?((int((fTemp11 < -50)))?(exp(fTemp11) * fTemp12):(fTemp11 / (1 - exp(fTemp12)))):(1 + (fTemp9 * (20.05 + (134.00083333333336 * fTemp9))))));
		double fTemp18 = (fConst61 * fRec36[1]);
		fRec42[0] = ((0.024937655860349125 * fTemp17) - (fConst88 * ((fConst86 * fRec42[2]) + (fConst84 * fRec42[1]))));
		double fTemp19 = (fRec42[2] + (fRec42[0] + (2 * fRec42[1])));
		fVec2[0] = fTemp19;
		fRec41[0] = ((fConst89 * ((fConst46 * fVec2[1]) + (fConst23 * fVec2[0]))) + (fConst25 * fRec41[1]));
		fRec40[0] = ((fConst90 * (fRec41[0] + fRec41[1])) + (fConst82 * fRec40[1]));
		fRec39[0] = (fRec40[0] - (fConst80 * ((fConst78 * fRec39[2]) + (fConst76 * fRec39[1]))));
		double fTemp20 = (fRec39[2] + (fRec39[0] + (2 * fRec39[1])));
		fVec3[0] = fTemp20;
		fRec38[0] = ((fConst92 * ((fConst91 * fVec3[1]) + (fConst68 * fVec3[0]))) + (fConst73 * fRec38[1]));
		fRec37[0] = (fRec38[0] - (fConst71 * ((fConst69 * fRec37[2]) + (fConst67 * fRec37[1]))));
		fRec36[0] = ((fConst71 * (((fConst66 * fRec37[0]) + (fConst93 * fRec37[1])) + (fConst66 * fRec37[2]))) - (fConst64 * ((fConst63 * fRec36[2]) + fTemp18)));
		double fTemp21 = max((double)-1, min((double)1, (fSlow7 * (fRec36[2] + (fConst64 * (fTemp18 + (fConst63 * fRec36[0])))))));
		fRec46[0] = ((fConst92 * (fVec3[0] + fVec3[1])) + (fConst73 * fRec46[1]));
		fRec45[0] = (fRec46[0] - (fConst71 * ((fConst69 * fRec45[2]) + (fConst67 * fRec45[1]))));
		double fTemp22 = (fRec45[2] + (fRec45[0] + (2 * fRec45[1])));
		fVec4[0] = fTemp22;
		fRec44[0] = ((fConst99 * ((fConst98 * fVec4[1]) + (fConst62 * fVec4[0]))) + (fConst97 * fRec44[1]));
		fRec43[0] = (fRec44[0] - (fConst95 * ((fConst94 * fRec43[2]) + (fConst61 * fRec43[1]))));
		double fTemp23 = max((double)-1, min((double)1, (fSlow8 * (((fConst60 * fRec43[0]) + (fConst100 * fRec43[1])) + (fConst60 * fRec43[2])))));
		double fTemp24 = (fConst61 * fRec47[1]);
		double fTemp25 = (fConst67 * fRec48[1]);
		fRec50[0] = ((fConst90 * ((fConst103 * fRec41[1]) + (fConst77 * fRec41[0]))) + (fConst82 * fRec50[1]));
		fRec49[0] = (fRec50[0] - (fConst80 * ((fConst78 * fRec49[2]) + (fConst76 * fRec49[1]))));
		fRec48[0] = ((fConst80 * (((fConst75 * fRec49[0]) + (fConst104 * fRec49[1])) + (fConst75 * fRec49[2]))) - (fConst102 * ((fConst101 * fRec48[2]) + fTemp25)));
		fRec47[0] = ((fRec48[2] + (fConst102 * (fTemp25 + (fConst101 * fRec48[0])))) - (fConst64 * ((fConst63 * fRec47[2]) + fTemp24)));
		double fTemp26 = max((double)-1, min((double)1, (fSlow9 * (fRec47[2] + (fConst64 * (fTemp24 + (fConst63 * fRec47[0])))))));
		fRec52[0] = ((fConst99 * (fVec4[0] + fVec4[1])) + (fConst97 * fRec52[1]));
		fRec51[0] = (fRec52[0] - (fConst95 * ((fConst94 * fRec51[2]) + (fConst61 * fRec51[1]))));
		double fTemp27 = max((double)-1, min((double)1, (fSlow10 * (fRec51[2] + (fRec51[0] + (2 * fRec51[1]))))));
		double fTemp28 = ((1.2589412 * (fTemp27 * (1 - (0.3333333333333333 * faustpower<2>(fTemp27))))) + (1.584893192 * ((fTemp26 * (1 - (0.3333333333333333 * faustpower<2>(fTemp26)))) + ((fTemp23 * (1 - (0.3333333333333333 * faustpower<2>(fTemp23)))) + (0.8413951417869425 * (fTemp21 * (1 - (0.3333333333333333 * faustpower<2>(fTemp21)))))))));
		fVec5[0] = fTemp28;
		fRec35[0] = ((fConst52 * (fVec5[0] + fVec5[1])) + (fConst28 * fRec35[1]));
		double fTemp29 = (((fSlow11 * fRec35[0]) + (fSlow6 * fTemp17)) + (fTemp4 * (1 + (fSlow4 * ((4 - (4 * fabs(fTemp4))) - 1)))));
		fVec6[0] = fTemp29;
		fRec7[0] = ((fConst52 * (fVec6[0] + fVec6[1])) + (fConst28 * fRec7[1]));
		double fTemp30 = (fRec7[0] * fRec6[0]);
		fRec4[0] = (Ftube(TUBE_TABLE_6V6_68k, ((fTemp30 + fRec5[0]) - 0.664541)) - 87.91682926829267);
		fRec3[0] = ((fConst105 * ((fConst46 * fRec4[1]) + (fConst23 * fRec4[0]))) + (fConst25 * fRec3[1]));
		fRec55[0] = ((fConst29 * (fRec54[1] + fRec54[2])) + (fConst28 * fRec55[1]));
		fRec54[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec55[0] + fTemp30) - 0.659761)) - 89.08268292682925);
		fRec53[0] = ((fConst105 * ((fConst46 * fRec54[1]) + (fConst23 * fRec54[0]))) + (fConst25 * fRec53[1]));
		fRec2[0] = ((min(0.7, fRec53[0]) + max(-0.75, fRec3[0])) - (fConst22 * ((fConst21 * fRec2[2]) + fTemp2)));
		fRec1[0] = ((fConst22 * ((fTemp2 + (fConst108 * fRec2[0])) + (fConst107 * fRec2[2]))) - (fConst15 * ((fConst14 * fRec1[2]) + fTemp1)));
		fRec0[0] = ((fConst15 * ((fTemp1 + (fConst111 * fRec1[0])) + (fConst110 * fRec1[2]))) - (fConst8 * ((fConst7 * fRec0[2]) + fTemp0)));
		output0[i] = (FAUSTFLOAT)(fConst8 * ((fTemp0 + (fConst114 * fRec0[0])) + (fConst113 * fRec0[2])));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec53[1] = fRec53[0];
		fRec54[2] = fRec54[1]; fRec54[1] = fRec54[0];
		fRec55[1] = fRec55[0];
		fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec7[1] = fRec7[0];
		fVec6[1] = fVec6[0];
		fRec35[1] = fRec35[0];
		fVec5[1] = fVec5[0];
		fRec51[2] = fRec51[1]; fRec51[1] = fRec51[0];
		fRec52[1] = fRec52[0];
		fRec47[2] = fRec47[1]; fRec47[1] = fRec47[0];
		fRec48[2] = fRec48[1]; fRec48[1] = fRec48[0];
		fRec49[2] = fRec49[1]; fRec49[1] = fRec49[0];
		fRec50[1] = fRec50[0];
		fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
		fRec44[1] = fRec44[0];
		fVec4[1] = fVec4[0];
		fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
		fRec46[1] = fRec46[0];
		fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
		fRec37[2] = fRec37[1]; fRec37[1] = fRec37[0];
		fRec38[1] = fRec38[0];
		fVec3[1] = fVec3[0];
		fRec39[2] = fRec39[1]; fRec39[1] = fRec39[0];
		fRec40[1] = fRec40[0];
		fRec41[1] = fRec41[0];
		fVec2[1] = fVec2[0];
		fRec42[2] = fRec42[1]; fRec42[1] = fRec42[0];
		fRec32[1] = fRec32[0];
		fRec33[1] = fRec33[0];
		IOTA = IOTA+1;
		fRec34[1] = fRec34[0];
		fRec9[1] = fRec9[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec31[1] = fRec31[0];
		fRec11[1] = fRec11[0];
		fRec28[1] = fRec28[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec12[1] = fRec12[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec27[1] = fRec27[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec24[1] = fRec24[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fRec16[1] = fRec16[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fVec0[1] = fVec0[0];
		fRec8[1] = fRec8[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	fslider3_ = reg.registerVar("gxdistortion.drive","","SA","",&fslider3, 0.35, 0.0, 1.0, 0.01);
	fslider2_ = reg.registerVar("amp2.stage1.Pregain","","SA","",&fslider2, -6.0, -2e+01, 2e+01, 0.1);
	fslider1_ = reg.registerVar("gxdistortion.wet_dry","","SA","",&fslider1, 1e+02, 0.0, 1e+02, 1.0);
	fslider0_ = reg.registerVar("amp2.stage2.gain1","","SA","",&fslider0, -6.0, -2e+01, 2e+01, 0.1);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace gxamp8
