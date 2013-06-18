// generated from file '../src/faust/gxamp16.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp16 {

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
	double 	fVec0[2];
	double 	fConst17;
	double 	fRec26[2];
	double 	fRec25[2];
	double 	fRec24[3];
	double 	fRec23[3];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec27[2];
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fRec28[2];
	double 	fRec22[3];
	double 	fConst22;
	double 	fConst23;
	double 	fRec21[2];
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fRec31[2];
	double 	fRec30[3];
	double 	fRec29[2];
	double 	fRec20[2];
	double 	fConst28;
	double 	fRec19[2];
	double 	fRec32[2];
	double 	fRec18[3];
	double 	fRec17[2];
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fRec35[2];
	double 	fRec34[3];
	double 	fRec33[2];
	double 	fRec16[2];
	double 	fRec36[2];
	double 	fRec15[3];
	double 	fRec14[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec39[2];
	int 	IOTA;
	double 	fVec1[32768];
	int 	iConst33;
	double 	fRec38[2];
	double 	fConst34;
	double 	fRec37[2];
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
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fRec47[3];
	double 	fVec2[2];
	double 	fConst65;
	double 	fRec46[2];
	double 	fConst66;
	double 	fRec45[2];
	double 	fRec44[3];
	double 	fVec3[2];
	double 	fConst67;
	double 	fConst68;
	double 	fRec43[2];
	double 	fRec42[3];
	double 	fConst69;
	double 	fRec41[3];
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;
	double 	fRec51[2];
	double 	fRec50[3];
	double 	fVec4[2];
	double 	fConst74;
	double 	fConst75;
	double 	fRec49[2];
	double 	fRec48[3];
	double 	fConst76;
	double 	fConst77;
	double 	fConst78;
	double 	fConst79;
	double 	fRec55[2];
	double 	fRec54[3];
	double 	fConst80;
	double 	fRec53[3];
	double 	fRec52[3];
	double 	fRec57[2];
	double 	fRec56[3];
	double 	fVec5[2];
	double 	fRec40[2];
	double 	fVec6[2];
	double 	fRec12[2];
	double 	fRec9[3];
	double 	fRec8[2];
	double 	fRec60[2];
	double 	fRec59[3];
	double 	fRec58[2];
	double 	fRec6[2];
	double 	fRec4[2];
	double 	fRec2[2];
	double 	fRec0[2];
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
	id = "pre 12AT7/ push pull 6V6";
	name = N_("pre 12AT7/ push pull 6V6");
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
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<3; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<32768; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<3; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<3; i++) fRec44[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec43[i] = 0;
	for (int i=0; i<3; i++) fRec42[i] = 0;
	for (int i=0; i<3; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<3; i++) fRec50[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<3; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<3; i++) fRec54[i] = 0;
	for (int i=0; i<3; i++) fRec53[i] = 0;
	for (int i=0; i<3; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) fRec57[i] = 0;
	for (int i=0; i<3; i++) fRec56[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec60[i] = 0;
	for (int i=0; i<3; i++) fRec59[i] = 0;
	for (int i=0; i<2; i++) fRec58[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = (0.0041 / fConst5);
	fConst8 = tan((37699.11184307752 / double(iConst0)));
	fConst9 = (2 * (1 - (1.0 / faustpower<2>(fConst8))));
	fConst10 = (1.0 / fConst8);
	fConst11 = (1 + ((fConst10 - 0.7653668647301795) / fConst8));
	fConst12 = (1.0 / (1 + ((0.7653668647301795 + fConst10) / fConst8)));
	fConst13 = (1 + ((fConst10 - 1.8477590650225735) / fConst8));
	fConst14 = (1.0 / (1 + ((fConst10 + 1.8477590650225735) / fConst8)));
	fConst15 = (973.8937226128359 / double(iConst0));
	fConst16 = (1 - fConst15);
	fConst17 = (1.0 / (1 + fConst15));
	fConst18 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst19 = (1 + fConst18);
	fConst20 = (0 - ((1 - fConst18) / fConst19));
	fConst21 = (0.027 / fConst19);
	fConst22 = (0 - fConst1);
	fConst23 = (0.025 / fConst2);
	fConst24 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst25 = (1 + fConst24);
	fConst26 = (0 - ((1 - fConst24) / fConst25));
	fConst27 = (0.015 / fConst25);
	fConst28 = (1.0 / fConst5);
	fConst29 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst30 = (1 + fConst29);
	fConst31 = (0 - ((1 - fConst29) / fConst30));
	fConst32 = (0.0082 / fConst30);
	IOTA = 0;
	iConst33 = int((int((0.1111111111111111 * iConst0)) & 65535));
	fConst34 = (0.009000000000000008 / double(iConst0));
	fConst35 = tan((942.4777960769379 / double(iConst0)));
	fConst36 = (1.0 / faustpower<2>(fConst35));
	fConst37 = (2 * (1 - fConst36));
	fConst38 = (1.0 / fConst35);
	fConst39 = (1 + ((fConst38 - 1.0) / fConst35));
	fConst40 = (1.0 / (1 + ((1.0 + fConst38) / fConst35)));
	fConst41 = tan((3769.9111843077517 / double(iConst0)));
	fConst42 = (1.0 / faustpower<2>(fConst41));
	fConst43 = (2 * (1 - fConst42));
	fConst44 = (1.0 / fConst41);
	fConst45 = (1 + ((fConst44 - 1.0000000000000004) / fConst41));
	fConst46 = (1 + ((fConst44 + 1.0000000000000004) / fConst41));
	fConst47 = (1.0 / fConst46);
	fConst48 = (1 + fConst44);
	fConst49 = (0 - ((1 - fConst44) / fConst48));
	fConst50 = tan((10053.096491487338 / double(iConst0)));
	fConst51 = (1.0 / faustpower<2>(fConst50));
	fConst52 = (2 * (1 - fConst51));
	fConst53 = (1.0 / fConst50);
	fConst54 = (1 + ((fConst53 - 1.0000000000000004) / fConst50));
	fConst55 = (1 + ((1.0000000000000004 + fConst53) / fConst50));
	fConst56 = (1.0 / fConst55);
	fConst57 = (1 + fConst53);
	fConst58 = (0 - ((1 - fConst53) / fConst57));
	fConst59 = tan((47123.8898038469 / double(iConst0)));
	fConst60 = (2 * (1 - (1.0 / faustpower<2>(fConst59))));
	fConst61 = (1.0 / fConst59);
	fConst62 = (1 + ((fConst61 - 1.414213562373095) / fConst59));
	fConst63 = (1 + ((1.414213562373095 + fConst61) / fConst59));
	fConst64 = (1.0 / fConst63);
	fConst65 = (1.0 / (fConst2 * fConst63));
	fConst66 = (1.0 / fConst57);
	fConst67 = (0 - fConst44);
	fConst68 = (1.0 / (fConst48 * fConst55));
	fConst69 = (2 * (0 - fConst42));
	fConst70 = (1 + ((fConst38 - 1.0000000000000004) / fConst35));
	fConst71 = (1.0 / (1 + ((fConst38 + 1.0000000000000004) / fConst35)));
	fConst72 = (1 + fConst38);
	fConst73 = (0 - ((1 - fConst38) / fConst72));
	fConst74 = (0 - fConst38);
	fConst75 = (1.0 / (fConst72 * fConst46));
	fConst76 = (2 * (0 - fConst36));
	fConst77 = (1 + ((fConst44 - 1.0) / fConst41));
	fConst78 = (1.0 / (1 + ((1.0 + fConst44) / fConst41)));
	fConst79 = (0 - fConst53);
	fConst80 = (2 * (0 - fConst51));
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
	double 	fSlow8 = (fConst71 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow9 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow10 = (fConst71 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow11 = (1 - max((double)0, (0 - fSlow5)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (0.5 * fRec0[1]);
		double fTemp1 = (fTemp0 + (0.4 * fRec2[1]));
		double fTemp2 = (fTemp1 + (0.3 * fRec4[1]));
		fRec10[0] = ((fConst7 * (fRec9[1] + fRec9[2])) + (fConst6 * fRec10[1]));
		fRec11[0] = (fSlow0 + (0.999 * fRec11[1]));
		fRec13[0] = (fSlow1 + (0.999 * fRec13[1]));
		double fTemp3 = (double)input0[i];
		fVec0[0] = fTemp3;
		fRec26[0] = (fConst17 * ((fVec0[0] - fVec0[1]) + (fConst16 * fRec26[1])));
		fRec25[0] = (fConst17 * ((fRec26[0] - fRec26[1]) + (fConst16 * fRec25[1])));
		fRec24[0] = (fRec25[0] - (fConst14 * ((fConst13 * fRec24[2]) + (fConst9 * fRec24[1]))));
		fRec23[0] = ((fConst14 * (fRec24[2] + (fRec24[0] + (2 * fRec24[1])))) - (fConst12 * ((fConst11 * fRec23[2]) + (fConst9 * fRec23[1]))));
		fRec27[0] = (fSlow2 + (0.999 * fRec27[1]));
		fRec28[0] = ((fConst21 * (fRec22[1] + fRec22[2])) + (fConst20 * fRec28[1]));
		fRec22[0] = (Ftube(TUBE_TABLE_12AT7_68k, ((fRec28[0] + (fConst12 * (fRec27[0] * (fRec23[2] + (fRec23[0] + (2 * fRec23[1])))))) - 2.617753)) - 153.04618518518518);
		fRec21[0] = ((fConst23 * ((fConst22 * fRec22[1]) + (fConst1 * fRec22[0]))) + (fConst3 * fRec21[1]));
		fRec31[0] = ((fConst27 * (fRec30[1] + fRec30[2])) + (fConst26 * fRec31[1]));
		fRec30[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec31[0] + fRec20[1]) - 1.887333)) - 124.17779999999999);
		fRec29[0] = ((fConst23 * ((fConst22 * fRec30[1]) + (fConst1 * fRec30[0]))) + (fConst3 * fRec29[1]));
		fRec20[0] = ((0.6 * fRec29[0]) + fRec21[0]);
		fRec19[0] = ((fConst28 * (fRec20[0] + fRec20[1])) + (fConst6 * fRec19[1]));
		fRec32[0] = ((fConst27 * (fRec18[1] + fRec18[2])) + (fConst26 * fRec32[1]));
		fRec18[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec32[0] + fRec19[0]) - 1.887333)) - 124.17779999999999);
		fRec17[0] = ((fConst23 * ((fConst22 * fRec18[1]) + (fConst1 * fRec18[0]))) + (fConst3 * fRec17[1]));
		fRec35[0] = ((fConst32 * (fRec34[1] + fRec34[2])) + (fConst31 * fRec35[1]));
		fRec34[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec35[0] + fRec16[1]) - 1.256962)) - 96.7119512195122);
		fRec33[0] = ((fConst23 * ((fConst22 * fRec34[1]) + (fConst1 * fRec34[0]))) + (fConst3 * fRec33[1]));
		fRec16[0] = ((0.6 * fRec33[0]) + fRec17[0]);
		fRec36[0] = ((fConst32 * (fRec15[1] + fRec15[2])) + (fConst31 * fRec36[1]));
		fRec15[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec36[0] + fRec16[0]) - 1.256962)) - 96.7119512195122);
		fRec14[0] = ((fConst23 * ((fConst22 * fRec15[1]) + (fConst1 * fRec15[0]))) + (fConst3 * fRec14[1]));
		double fTemp4 = (fRec14[0] * (1 - fRec13[0]));
		double fTemp5 = (fRec14[0] * fRec13[0]);
		double fTemp6 = fabs(fTemp5);
		fRec39[0] = ((9.999999999998899e-05 * fTemp6) + (0.9999 * fRec39[1]));
		double fTemp7 = max(fRec39[0], fTemp6);
		fVec1[IOTA&32767] = fTemp7;
		fRec38[0] = ((fVec1[IOTA&32767] + fRec38[1]) - fVec1[(IOTA-iConst33)&32767]);
		fRec37[0] = ((fConst34 * fRec38[0]) + (0.999 * fRec37[1]));
		double fTemp8 = max(-1.0, min(-0.01, (fVec1[IOTA&32767] - (1.0 + (1.02 * fRec37[0])))));
		double fTemp9 = (0 - fTemp8);
		double fTemp10 = (40.1 * fTemp9);
		double fTemp11 = max((double)-600, fTemp10);
		double fTemp12 = (0 - fTemp11);
		double fTemp13 = (fTemp5 - fTemp8);
		double fTemp14 = (40.1 * fTemp13);
		double fTemp15 = max((double)-600, fTemp14);
		double fTemp16 = (0 - fTemp15);
		double fTemp17 = (((int((fabs(fTemp14) > 0.0001)))?((int((fTemp15 < -50)))?(exp(fTemp15) * fTemp16):(fTemp15 / (1 - exp(fTemp16)))):(1 + (fTemp13 * (20.05 + (134.00083333333336 * fTemp13))))) - ((int((fabs(fTemp10) > 0.0001)))?((int((fTemp11 < -50)))?(exp(fTemp11) * fTemp12):(fTemp11 / (1 - exp(fTemp12)))):(1 + (fTemp9 * (20.05 + (134.00083333333336 * fTemp9))))));
		double fTemp18 = (fConst37 * fRec41[1]);
		fRec47[0] = ((0.024937655860349125 * fTemp17) - (fConst64 * ((fConst62 * fRec47[2]) + (fConst60 * fRec47[1]))));
		double fTemp19 = (fRec47[2] + (fRec47[0] + (2 * fRec47[1])));
		fVec2[0] = fTemp19;
		fRec46[0] = ((fConst65 * ((fConst22 * fVec2[1]) + (fConst1 * fVec2[0]))) + (fConst3 * fRec46[1]));
		fRec45[0] = ((fConst66 * (fRec46[0] + fRec46[1])) + (fConst58 * fRec45[1]));
		fRec44[0] = (fRec45[0] - (fConst56 * ((fConst54 * fRec44[2]) + (fConst52 * fRec44[1]))));
		double fTemp20 = (fRec44[2] + (fRec44[0] + (2 * fRec44[1])));
		fVec3[0] = fTemp20;
		fRec43[0] = ((fConst68 * ((fConst67 * fVec3[1]) + (fConst44 * fVec3[0]))) + (fConst49 * fRec43[1]));
		fRec42[0] = (fRec43[0] - (fConst47 * ((fConst45 * fRec42[2]) + (fConst43 * fRec42[1]))));
		fRec41[0] = ((fConst47 * (((fConst42 * fRec42[0]) + (fConst69 * fRec42[1])) + (fConst42 * fRec42[2]))) - (fConst40 * ((fConst39 * fRec41[2]) + fTemp18)));
		double fTemp21 = max((double)-1, min((double)1, (fSlow7 * (fRec41[2] + (fConst40 * (fTemp18 + (fConst39 * fRec41[0])))))));
		fRec51[0] = ((fConst68 * (fVec3[0] + fVec3[1])) + (fConst49 * fRec51[1]));
		fRec50[0] = (fRec51[0] - (fConst47 * ((fConst45 * fRec50[2]) + (fConst43 * fRec50[1]))));
		double fTemp22 = (fRec50[2] + (fRec50[0] + (2 * fRec50[1])));
		fVec4[0] = fTemp22;
		fRec49[0] = ((fConst75 * ((fConst74 * fVec4[1]) + (fConst38 * fVec4[0]))) + (fConst73 * fRec49[1]));
		fRec48[0] = (fRec49[0] - (fConst71 * ((fConst70 * fRec48[2]) + (fConst37 * fRec48[1]))));
		double fTemp23 = max((double)-1, min((double)1, (fSlow8 * (((fConst36 * fRec48[0]) + (fConst76 * fRec48[1])) + (fConst36 * fRec48[2])))));
		double fTemp24 = (fConst37 * fRec52[1]);
		double fTemp25 = (fConst43 * fRec53[1]);
		fRec55[0] = ((fConst66 * ((fConst79 * fRec46[1]) + (fConst53 * fRec46[0]))) + (fConst58 * fRec55[1]));
		fRec54[0] = (fRec55[0] - (fConst56 * ((fConst54 * fRec54[2]) + (fConst52 * fRec54[1]))));
		fRec53[0] = ((fConst56 * (((fConst51 * fRec54[0]) + (fConst80 * fRec54[1])) + (fConst51 * fRec54[2]))) - (fConst78 * ((fConst77 * fRec53[2]) + fTemp25)));
		fRec52[0] = ((fRec53[2] + (fConst78 * (fTemp25 + (fConst77 * fRec53[0])))) - (fConst40 * ((fConst39 * fRec52[2]) + fTemp24)));
		double fTemp26 = max((double)-1, min((double)1, (fSlow9 * (fRec52[2] + (fConst40 * (fTemp24 + (fConst39 * fRec52[0])))))));
		fRec57[0] = ((fConst75 * (fVec4[0] + fVec4[1])) + (fConst73 * fRec57[1]));
		fRec56[0] = (fRec57[0] - (fConst71 * ((fConst70 * fRec56[2]) + (fConst37 * fRec56[1]))));
		double fTemp27 = max((double)-1, min((double)1, (fSlow10 * (fRec56[2] + (fRec56[0] + (2 * fRec56[1]))))));
		double fTemp28 = ((1.2589412 * (fTemp27 * (1 - (0.3333333333333333 * faustpower<2>(fTemp27))))) + (1.584893192 * ((fTemp26 * (1 - (0.3333333333333333 * faustpower<2>(fTemp26)))) + ((fTemp23 * (1 - (0.3333333333333333 * faustpower<2>(fTemp23)))) + (0.8413951417869425 * (fTemp21 * (1 - (0.3333333333333333 * faustpower<2>(fTemp21)))))))));
		fVec5[0] = fTemp28;
		fRec40[0] = ((fConst28 * (fVec5[0] + fVec5[1])) + (fConst6 * fRec40[1]));
		double fTemp29 = (((fSlow11 * fRec40[0]) + (fSlow6 * fTemp17)) + (fTemp4 * (1 + (fSlow4 * ((4 - (4 * fabs(fTemp4))) - 1)))));
		fVec6[0] = fTemp29;
		fRec12[0] = ((fConst28 * (fVec6[0] + fVec6[1])) + (fConst6 * fRec12[1]));
		double fTemp30 = (fRec12[0] * fRec11[0]);
		fRec9[0] = (Ftube(TUBE_TABLE_6V6_68k, ((fTemp30 + fRec10[0]) - 0.664541)) - 87.91682926829267);
		fRec8[0] = ((fConst23 * ((fConst22 * fRec9[1]) + (fConst1 * fRec9[0]))) + (fConst3 * fRec8[1]));
		fRec60[0] = ((fConst7 * (fRec59[1] + fRec59[2])) + (fConst6 * fRec60[1]));
		fRec59[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec60[0] + fTemp30) - 0.659761)) - 89.08268292682925);
		fRec58[0] = ((fConst23 * ((fConst22 * fRec59[1]) + (fConst1 * fRec59[0]))) + (fConst3 * fRec58[1]));
		double fTemp31 = (min(0.7, fRec58[0]) + max(-0.75, fRec8[0]));
		double fTemp32 = ((fTemp31 + (0.2 * fRec6[1])) - fTemp2);
		fRec6[0] = fTemp32;
		double 	fRec7 = (0 - (0.2 * fTemp32));
		fRec4[0] = (fRec7 + fRec6[1]);
		double 	fRec5 = (0.3 * (fTemp31 - fTemp2));
		fRec2[0] = (fRec5 + fRec4[1]);
		double 	fRec3 = (0.4 * (fTemp31 - fTemp1));
		fRec0[0] = (fRec3 + fRec2[1]);
		double 	fRec1 = (0.5 * (fTemp31 - fTemp0));
		output0[i] = (FAUSTFLOAT)(fRec1 + fRec0[1]);
		// post processing
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fRec6[1] = fRec6[0];
		fRec58[1] = fRec58[0];
		fRec59[2] = fRec59[1]; fRec59[1] = fRec59[0];
		fRec60[1] = fRec60[0];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec12[1] = fRec12[0];
		fVec6[1] = fVec6[0];
		fRec40[1] = fRec40[0];
		fVec5[1] = fVec5[0];
		fRec56[2] = fRec56[1]; fRec56[1] = fRec56[0];
		fRec57[1] = fRec57[0];
		fRec52[2] = fRec52[1]; fRec52[1] = fRec52[0];
		fRec53[2] = fRec53[1]; fRec53[1] = fRec53[0];
		fRec54[2] = fRec54[1]; fRec54[1] = fRec54[0];
		fRec55[1] = fRec55[0];
		fRec48[2] = fRec48[1]; fRec48[1] = fRec48[0];
		fRec49[1] = fRec49[0];
		fVec4[1] = fVec4[0];
		fRec50[2] = fRec50[1]; fRec50[1] = fRec50[0];
		fRec51[1] = fRec51[0];
		fRec41[2] = fRec41[1]; fRec41[1] = fRec41[0];
		fRec42[2] = fRec42[1]; fRec42[1] = fRec42[0];
		fRec43[1] = fRec43[0];
		fVec3[1] = fVec3[0];
		fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
		fRec45[1] = fRec45[0];
		fRec46[1] = fRec46[0];
		fVec2[1] = fVec2[0];
		fRec47[2] = fRec47[1]; fRec47[1] = fRec47[0];
		fRec37[1] = fRec37[0];
		fRec38[1] = fRec38[0];
		IOTA = IOTA+1;
		fRec39[1] = fRec39[0];
		fRec14[1] = fRec14[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec36[1] = fRec36[0];
		fRec16[1] = fRec16[0];
		fRec33[1] = fRec33[0];
		fRec34[2] = fRec34[1]; fRec34[1] = fRec34[0];
		fRec35[1] = fRec35[0];
		fRec17[1] = fRec17[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec32[1] = fRec32[0];
		fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec29[1] = fRec29[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fRec21[1] = fRec21[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec28[1] = fRec28[0];
		fRec27[1] = fRec27[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fVec0[1] = fVec0[0];
		fRec13[1] = fRec13[0];
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
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

} // end namespace gxamp16
