// generated from file '../src/faust/gxamp6.dsp' by dsp2cc:
// Code generated with Faust 0.9.57 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp6 {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fRec0[3];
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fRec3[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec4[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec6[2];
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fVec0[2];
	double 	fConst22;
	double 	fRec19[2];
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fRec16[3];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec20[2];
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fRec21[2];
	double 	fRec15[3];
	double 	fConst27;
	double 	fConst28;
	double 	fRec14[2];
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fRec24[2];
	double 	fRec23[3];
	double 	fRec22[2];
	double 	fRec13[2];
	double 	fConst33;
	double 	fRec12[2];
	double 	fRec25[2];
	double 	fRec11[3];
	double 	fRec10[2];
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fRec26[2];
	double 	fRec9[2];
	double 	fRec29[2];
	double 	fRec8[3];
	double 	fRec7[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec32[2];
	int 	IOTA;
	double 	fVec1[32768];
	int 	iConst38;
	double 	fRec31[2];
	double 	fConst39;
	double 	fRec30[2];
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
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fRec40[3];
	double 	fVec2[2];
	double 	fConst70;
	double 	fRec39[2];
	double 	fConst71;
	double 	fRec38[2];
	double 	fRec37[3];
	double 	fVec3[2];
	double 	fConst72;
	double 	fConst73;
	double 	fRec36[2];
	double 	fRec35[3];
	double 	fConst74;
	double 	fRec34[3];
	double 	fConst75;
	double 	fConst76;
	double 	fConst77;
	double 	fConst78;
	double 	fRec44[2];
	double 	fRec43[3];
	double 	fVec4[2];
	double 	fConst79;
	double 	fConst80;
	double 	fRec42[2];
	double 	fRec41[3];
	double 	fConst81;
	double 	fConst82;
	double 	fConst83;
	double 	fConst84;
	double 	fRec48[2];
	double 	fRec47[3];
	double 	fConst85;
	double 	fRec46[3];
	double 	fRec45[3];
	double 	fRec50[2];
	double 	fRec49[3];
	double 	fVec5[2];
	double 	fRec33[2];
	double 	fVec6[2];
	double 	fRec5[2];
	double 	fRec2[3];
	double 	fConst86;
	double 	fRec1[2];
	double 	fRec53[2];
	double 	fRec52[3];
	double 	fRec51[2];
	double 	fConst87;
	double 	fConst88;
	double 	fConst89;
	double 	fConst90;
	double 	fConst91;
	double 	fRec54[3];
	double 	fConst92;
	double 	fConst93;
	double 	fConst94;
	double 	fConst95;
	double 	fConst96;
	double 	fRec55[3];
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
	id = "pre 6DJ8/ push-pull 6V6";
	name = N_("pre 6DJ8/ push-pull 6V6");
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
	for (int i=0; i<3; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<32768; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<3; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<3; i++) fRec35[i] = 0;
	for (int i=0; i<3; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<3; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<3; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<3; i++) fRec47[i] = 0;
	for (int i=0; i<3; i++) fRec46[i] = 0;
	for (int i=0; i<3; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<3; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec53[i] = 0;
	for (int i=0; i<3; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<3; i++) fRec54[i] = 0;
	for (int i=0; i<3; i++) fRec55[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (60601.32228774711 / double(iConst0));
	fConst2 = (0 - (2 * cos(fConst1)));
	fConst3 = (0.03546099290780142 * sin(fConst1));
	fConst4 = (1 - fConst3);
	fConst5 = (1.0 / (1 + fConst3));
	fConst6 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst7 = (1 + fConst6);
	fConst8 = (0 - ((1 - fConst6) / fConst7));
	fConst9 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst10 = (1 + fConst9);
	fConst11 = (0 - ((1 - fConst9) / fConst10));
	fConst12 = (0.0041 / fConst10);
	fConst13 = tan((37699.11184307752 / double(iConst0)));
	fConst14 = (2 * (1 - (1.0 / faustpower<2>(fConst13))));
	fConst15 = (1.0 / fConst13);
	fConst16 = (1 + ((fConst15 - 0.7653668647301795) / fConst13));
	fConst17 = (1.0 / (1 + ((0.7653668647301795 + fConst15) / fConst13)));
	fConst18 = (1 + ((fConst15 - 1.8477590650225735) / fConst13));
	fConst19 = (1.0 / (1 + ((fConst15 + 1.8477590650225735) / fConst13)));
	fConst20 = (973.8937226128359 / double(iConst0));
	fConst21 = (1 - fConst20);
	fConst22 = (1.0 / (1 + fConst20));
	fConst23 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst24 = (1 + fConst23);
	fConst25 = (0 - ((1 - fConst23) / fConst24));
	fConst26 = (0.027 / fConst24);
	fConst27 = (0 - fConst6);
	fConst28 = (0.05 / fConst7);
	fConst29 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst30 = (1 + fConst29);
	fConst31 = (0 - ((1 - fConst29) / fConst30));
	fConst32 = (0.015 / fConst30);
	fConst33 = (1.0 / fConst10);
	fConst34 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst35 = (1 + fConst34);
	fConst36 = (0 - ((1 - fConst34) / fConst35));
	fConst37 = (0.0082 / fConst35);
	IOTA = 0;
	iConst38 = int((int((0.1111111111111111 * iConst0)) & 65535));
	fConst39 = (0.009000000000000008 / double(iConst0));
	fConst40 = tan((942.4777960769379 / double(iConst0)));
	fConst41 = (1.0 / faustpower<2>(fConst40));
	fConst42 = (2 * (1 - fConst41));
	fConst43 = (1.0 / fConst40);
	fConst44 = (1 + ((fConst43 - 1.0) / fConst40));
	fConst45 = (1.0 / (1 + ((1.0 + fConst43) / fConst40)));
	fConst46 = tan((3769.9111843077517 / double(iConst0)));
	fConst47 = (1.0 / faustpower<2>(fConst46));
	fConst48 = (2 * (1 - fConst47));
	fConst49 = (1.0 / fConst46);
	fConst50 = (1 + ((fConst49 - 1.0000000000000004) / fConst46));
	fConst51 = (1 + ((fConst49 + 1.0000000000000004) / fConst46));
	fConst52 = (1.0 / fConst51);
	fConst53 = (1 + fConst49);
	fConst54 = (0 - ((1 - fConst49) / fConst53));
	fConst55 = tan((10053.096491487338 / double(iConst0)));
	fConst56 = (1.0 / faustpower<2>(fConst55));
	fConst57 = (2 * (1 - fConst56));
	fConst58 = (1.0 / fConst55);
	fConst59 = (1 + ((fConst58 - 1.0000000000000004) / fConst55));
	fConst60 = (1 + ((1.0000000000000004 + fConst58) / fConst55));
	fConst61 = (1.0 / fConst60);
	fConst62 = (1 + fConst58);
	fConst63 = (0 - ((1 - fConst58) / fConst62));
	fConst64 = tan((47123.8898038469 / double(iConst0)));
	fConst65 = (2 * (1 - (1.0 / faustpower<2>(fConst64))));
	fConst66 = (1.0 / fConst64);
	fConst67 = (1 + ((fConst66 - 1.414213562373095) / fConst64));
	fConst68 = (1 + ((1.414213562373095 + fConst66) / fConst64));
	fConst69 = (1.0 / fConst68);
	fConst70 = (1.0 / (fConst7 * fConst68));
	fConst71 = (1.0 / fConst62);
	fConst72 = (0 - fConst49);
	fConst73 = (1.0 / (fConst53 * fConst60));
	fConst74 = (2 * (0 - fConst47));
	fConst75 = (1 + ((fConst43 - 1.0000000000000004) / fConst40));
	fConst76 = (1.0 / (1 + ((fConst43 + 1.0000000000000004) / fConst40)));
	fConst77 = (1 + fConst43);
	fConst78 = (0 - ((1 - fConst43) / fConst77));
	fConst79 = (0 - fConst43);
	fConst80 = (1.0 / (fConst77 * fConst51));
	fConst81 = (2 * (0 - fConst41));
	fConst82 = (1 + ((fConst49 - 1.0) / fConst46));
	fConst83 = (1.0 / (1 + ((1.0 + fConst49) / fConst46)));
	fConst84 = (0 - fConst58);
	fConst85 = (2 * (0 - fConst56));
	fConst86 = (0.025 / fConst7);
	fConst87 = (49574.33207364693 / double(iConst0));
	fConst88 = (0 - (2 * cos(fConst87)));
	fConst89 = (0.07042253521126761 * sin(fConst87));
	fConst90 = (1 - fConst89);
	fConst91 = (1.0 / (1 + fConst89));
	fConst92 = (31704.95306002819 / double(iConst0));
	fConst93 = (0 - (2 * cos(fConst92)));
	fConst94 = (0.026178010471204185 * sin(fConst92));
	fConst95 = (1 - fConst94);
	fConst96 = (1.0 / (1 + fConst94));
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
	double 	fSlow8 = (fConst76 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow9 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow10 = (fConst76 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow11 = (1 - max((double)0, (0 - fSlow5)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (fRec0[1] + (fConst2 * fRec0[2]));
		fRec0[0] = (fConst5 * (fConst4 - fTemp0));
		fRec3[0] = ((fConst12 * (fRec2[1] + fRec2[2])) + (fConst11 * fRec3[1]));
		fRec4[0] = (fSlow0 + (0.999 * fRec4[1]));
		fRec6[0] = (fSlow1 + (0.999 * fRec6[1]));
		double fTemp1 = (double)input0[i];
		fVec0[0] = fTemp1;
		fRec19[0] = (fConst22 * ((fVec0[0] - fVec0[1]) + (fConst21 * fRec19[1])));
		fRec18[0] = (fConst22 * ((fRec19[0] - fRec19[1]) + (fConst21 * fRec18[1])));
		fRec17[0] = (fRec18[0] - (fConst19 * ((fConst18 * fRec17[2]) + (fConst14 * fRec17[1]))));
		fRec16[0] = ((fConst19 * (fRec17[2] + (fRec17[0] + (2 * fRec17[1])))) - (fConst17 * ((fConst16 * fRec16[2]) + (fConst14 * fRec16[1]))));
		fRec20[0] = (fSlow2 + (0.999 * fRec20[1]));
		fRec21[0] = ((fConst26 * (fRec15[1] + fRec15[2])) + (fConst25 * fRec21[1]));
		fRec15[0] = (Ftube(TUBE_TABLE_6DJ8_68k, ((fRec21[0] + (fConst17 * (fRec20[0] * (fRec16[2] + (fRec16[0] + (2 * fRec16[1])))))) - 1.863946)) - 60.96496296296296);
		fRec14[0] = ((fConst28 * ((fConst27 * fRec15[1]) + (fConst6 * fRec15[0]))) + (fConst8 * fRec14[1]));
		fRec24[0] = ((fConst32 * (fRec23[1] + fRec23[2])) + (fConst31 * fRec24[1]));
		fRec23[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec24[0] + fRec13[1]) - 1.271609)) - 45.22606666666667);
		fRec22[0] = ((fConst28 * ((fConst27 * fRec23[1]) + (fConst6 * fRec23[0]))) + (fConst8 * fRec22[1]));
		fRec13[0] = ((0.6 * fRec22[0]) + fRec14[0]);
		fRec12[0] = ((fConst33 * (fRec13[0] + fRec13[1])) + (fConst11 * fRec12[1]));
		fRec25[0] = ((fConst32 * (fRec11[1] + fRec11[2])) + (fConst31 * fRec25[1]));
		fRec11[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec25[0] + fRec12[0]) - 1.271609)) - 45.22606666666667);
		fRec10[0] = ((fConst28 * ((fConst27 * fRec11[1]) + (fConst6 * fRec11[0]))) + (fConst8 * fRec10[1]));
		fRec28[0] = ((fConst37 * (fRec27[1] + fRec27[2])) + (fConst36 * fRec28[1]));
		fRec27[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec28[0] + fRec9[1]) - 0.797043)) - 32.799634146341475);
		fRec26[0] = ((fConst28 * ((fConst27 * fRec27[1]) + (fConst6 * fRec27[0]))) + (fConst8 * fRec26[1]));
		fRec9[0] = ((0.6 * fRec26[0]) + fRec10[0]);
		fRec29[0] = ((fConst37 * (fRec8[1] + fRec8[2])) + (fConst36 * fRec29[1]));
		fRec8[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec29[0] + fRec9[0]) - 0.797043)) - 32.799634146341475);
		fRec7[0] = ((fConst28 * ((fConst27 * fRec8[1]) + (fConst6 * fRec8[0]))) + (fConst8 * fRec7[1]));
		double fTemp2 = (fRec7[0] * (1 - fRec6[0]));
		double fTemp3 = (fRec7[0] * fRec6[0]);
		double fTemp4 = fabs(fTemp3);
		fRec32[0] = ((9.999999999998899e-05 * fTemp4) + (0.9999 * fRec32[1]));
		double fTemp5 = max(fRec32[0], fTemp4);
		fVec1[IOTA&32767] = fTemp5;
		fRec31[0] = ((fVec1[IOTA&32767] + fRec31[1]) - fVec1[(IOTA-iConst38)&32767]);
		fRec30[0] = ((fConst39 * fRec31[0]) + (0.999 * fRec30[1]));
		double fTemp6 = max(-1.0, min(-0.01, (fVec1[IOTA&32767] - (1.0 + (1.02 * fRec30[0])))));
		double fTemp7 = (0 - fTemp6);
		double fTemp8 = (40.1 * fTemp7);
		double fTemp9 = max((double)-600, fTemp8);
		double fTemp10 = (0 - fTemp9);
		double fTemp11 = (fTemp3 - fTemp6);
		double fTemp12 = (40.1 * fTemp11);
		double fTemp13 = max((double)-600, fTemp12);
		double fTemp14 = (0 - fTemp13);
		double fTemp15 = (((int((fabs(fTemp12) > 0.0001)))?((int((fTemp13 < -50)))?(exp(fTemp13) * fTemp14):(fTemp13 / (1 - exp(fTemp14)))):(1 + (fTemp11 * (20.05 + (134.00083333333336 * fTemp11))))) - ((int((fabs(fTemp8) > 0.0001)))?((int((fTemp9 < -50)))?(exp(fTemp9) * fTemp10):(fTemp9 / (1 - exp(fTemp10)))):(1 + (fTemp7 * (20.05 + (134.00083333333336 * fTemp7))))));
		double fTemp16 = (fConst42 * fRec34[1]);
		fRec40[0] = ((0.024937655860349125 * fTemp15) - (fConst69 * ((fConst67 * fRec40[2]) + (fConst65 * fRec40[1]))));
		double fTemp17 = (fRec40[2] + (fRec40[0] + (2 * fRec40[1])));
		fVec2[0] = fTemp17;
		fRec39[0] = ((fConst70 * ((fConst27 * fVec2[1]) + (fConst6 * fVec2[0]))) + (fConst8 * fRec39[1]));
		fRec38[0] = ((fConst71 * (fRec39[0] + fRec39[1])) + (fConst63 * fRec38[1]));
		fRec37[0] = (fRec38[0] - (fConst61 * ((fConst59 * fRec37[2]) + (fConst57 * fRec37[1]))));
		double fTemp18 = (fRec37[2] + (fRec37[0] + (2 * fRec37[1])));
		fVec3[0] = fTemp18;
		fRec36[0] = ((fConst73 * ((fConst72 * fVec3[1]) + (fConst49 * fVec3[0]))) + (fConst54 * fRec36[1]));
		fRec35[0] = (fRec36[0] - (fConst52 * ((fConst50 * fRec35[2]) + (fConst48 * fRec35[1]))));
		fRec34[0] = ((fConst52 * (((fConst47 * fRec35[0]) + (fConst74 * fRec35[1])) + (fConst47 * fRec35[2]))) - (fConst45 * ((fConst44 * fRec34[2]) + fTemp16)));
		double fTemp19 = max((double)-1, min((double)1, (fSlow7 * (fRec34[2] + (fConst45 * (fTemp16 + (fConst44 * fRec34[0])))))));
		fRec44[0] = ((fConst73 * (fVec3[0] + fVec3[1])) + (fConst54 * fRec44[1]));
		fRec43[0] = (fRec44[0] - (fConst52 * ((fConst50 * fRec43[2]) + (fConst48 * fRec43[1]))));
		double fTemp20 = (fRec43[2] + (fRec43[0] + (2 * fRec43[1])));
		fVec4[0] = fTemp20;
		fRec42[0] = ((fConst80 * ((fConst79 * fVec4[1]) + (fConst43 * fVec4[0]))) + (fConst78 * fRec42[1]));
		fRec41[0] = (fRec42[0] - (fConst76 * ((fConst75 * fRec41[2]) + (fConst42 * fRec41[1]))));
		double fTemp21 = max((double)-1, min((double)1, (fSlow8 * (((fConst41 * fRec41[0]) + (fConst81 * fRec41[1])) + (fConst41 * fRec41[2])))));
		double fTemp22 = (fConst42 * fRec45[1]);
		double fTemp23 = (fConst48 * fRec46[1]);
		fRec48[0] = ((fConst71 * ((fConst84 * fRec39[1]) + (fConst58 * fRec39[0]))) + (fConst63 * fRec48[1]));
		fRec47[0] = (fRec48[0] - (fConst61 * ((fConst59 * fRec47[2]) + (fConst57 * fRec47[1]))));
		fRec46[0] = ((fConst61 * (((fConst56 * fRec47[0]) + (fConst85 * fRec47[1])) + (fConst56 * fRec47[2]))) - (fConst83 * ((fConst82 * fRec46[2]) + fTemp23)));
		fRec45[0] = ((fRec46[2] + (fConst83 * (fTemp23 + (fConst82 * fRec46[0])))) - (fConst45 * ((fConst44 * fRec45[2]) + fTemp22)));
		double fTemp24 = max((double)-1, min((double)1, (fSlow9 * (fRec45[2] + (fConst45 * (fTemp22 + (fConst44 * fRec45[0])))))));
		fRec50[0] = ((fConst80 * (fVec4[0] + fVec4[1])) + (fConst78 * fRec50[1]));
		fRec49[0] = (fRec50[0] - (fConst76 * ((fConst75 * fRec49[2]) + (fConst42 * fRec49[1]))));
		double fTemp25 = max((double)-1, min((double)1, (fSlow10 * (fRec49[2] + (fRec49[0] + (2 * fRec49[1]))))));
		double fTemp26 = ((1.2589412 * (fTemp25 * (1 - (0.3333333333333333 * faustpower<2>(fTemp25))))) + (1.584893192 * ((fTemp24 * (1 - (0.3333333333333333 * faustpower<2>(fTemp24)))) + ((fTemp21 * (1 - (0.3333333333333333 * faustpower<2>(fTemp21)))) + (0.8413951417869425 * (fTemp19 * (1 - (0.3333333333333333 * faustpower<2>(fTemp19)))))))));
		fVec5[0] = fTemp26;
		fRec33[0] = ((fConst33 * (fVec5[0] + fVec5[1])) + (fConst11 * fRec33[1]));
		double fTemp27 = (((fSlow11 * fRec33[0]) + (fSlow6 * fTemp15)) + (fTemp2 * (1 + (fSlow4 * ((4 - (4 * fabs(fTemp2))) - 1)))));
		fVec6[0] = fTemp27;
		fRec5[0] = ((fConst33 * (fVec6[0] + fVec6[1])) + (fConst11 * fRec5[1]));
		double fTemp28 = (fRec5[0] * fRec4[0]);
		fRec2[0] = (Ftube(TUBE_TABLE_6V6_68k, ((fTemp28 + fRec3[0]) - 0.664541)) - 87.91682926829267);
		fRec1[0] = ((fConst86 * ((fConst27 * fRec2[1]) + (fConst6 * fRec2[0]))) + (fConst8 * fRec1[1]));
		fRec53[0] = ((fConst12 * (fRec52[1] + fRec52[2])) + (fConst11 * fRec53[1]));
		fRec52[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec53[0] + fTemp28) - 0.659761)) - 89.08268292682925);
		fRec51[0] = ((fConst86 * ((fConst27 * fRec52[1]) + (fConst6 * fRec52[0]))) + (fConst8 * fRec51[1]));
		double fTemp29 = (fRec54[1] + (fConst88 * fRec54[2]));
		fRec54[0] = (fConst91 * (fConst90 - fTemp29));
		double fTemp30 = (fRec55[1] + (fConst93 * fRec55[2]));
		fRec55[0] = (fConst96 * (fConst95 - fTemp30));
		output0[i] = (FAUSTFLOAT)((fConst96 * fTemp30) + (fRec55[0] * ((fConst91 * fTemp29) + (fRec54[0] * (((min(0.7, fRec51[0]) + max(-0.75, fRec1[0])) * fRec0[0]) + (fConst5 * fTemp0))))));
		// post processing
		fRec55[2] = fRec55[1]; fRec55[1] = fRec55[0];
		fRec54[2] = fRec54[1]; fRec54[1] = fRec54[0];
		fRec51[1] = fRec51[0];
		fRec52[2] = fRec52[1]; fRec52[1] = fRec52[0];
		fRec53[1] = fRec53[0];
		fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec5[1] = fRec5[0];
		fVec6[1] = fVec6[0];
		fRec33[1] = fRec33[0];
		fVec5[1] = fVec5[0];
		fRec49[2] = fRec49[1]; fRec49[1] = fRec49[0];
		fRec50[1] = fRec50[0];
		fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
		fRec46[2] = fRec46[1]; fRec46[1] = fRec46[0];
		fRec47[2] = fRec47[1]; fRec47[1] = fRec47[0];
		fRec48[1] = fRec48[0];
		fRec41[2] = fRec41[1]; fRec41[1] = fRec41[0];
		fRec42[1] = fRec42[0];
		fVec4[1] = fVec4[0];
		fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
		fRec44[1] = fRec44[0];
		fRec34[2] = fRec34[1]; fRec34[1] = fRec34[0];
		fRec35[2] = fRec35[1]; fRec35[1] = fRec35[0];
		fRec36[1] = fRec36[0];
		fVec3[1] = fVec3[0];
		fRec37[2] = fRec37[1]; fRec37[1] = fRec37[0];
		fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fVec2[1] = fVec2[0];
		fRec40[2] = fRec40[1]; fRec40[1] = fRec40[0];
		fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		IOTA = IOTA+1;
		fRec32[1] = fRec32[0];
		fRec7[1] = fRec7[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec29[1] = fRec29[0];
		fRec9[1] = fRec9[0];
		fRec26[1] = fRec26[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec25[1] = fRec25[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec22[1] = fRec22[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fRec14[1] = fRec14[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fVec0[1] = fVec0[0];
		fRec6[1] = fRec6[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
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

} // end namespace gxamp6
