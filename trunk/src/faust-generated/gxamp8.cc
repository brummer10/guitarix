// generated from file '../src/faust/gxamp8.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

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
	double 	fRec10[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec13[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec18[2];
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
	double 	fVec0[2];
	double 	fConst15;
	double 	fRec37[2];
	double 	fRec36[2];
	double 	fRec35[3];
	double 	fRec34[3];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec38[2];
	double 	fConst16;
	double 	fRec33[3];
	double 	fVec1[2];
	double 	fRec32[2];
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fRec39[2];
	double 	fRec31[3];
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fRec30[2];
	double 	fRec43[3];
	double 	fVec2[2];
	double 	fRec42[2];
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fRec44[2];
	double 	fRec41[3];
	double 	fRec40[2];
	double 	fRec29[2];
	double 	fConst30;
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fVec3[2];
	double 	fRec26[2];
	double 	fRec45[2];
	double 	fRec25[3];
	double 	fRec24[2];
	double 	fRec49[3];
	double 	fVec4[2];
	double 	fRec48[2];
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fRec50[2];
	double 	fRec47[3];
	double 	fRec46[2];
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fVec5[2];
	double 	fRec21[2];
	double 	fRec51[2];
	double 	fRec20[3];
	double 	fRec19[2];
	double 	fRec17[2];
	int 	IOTA;
	double 	fVec6[32768];
	int 	iConst35;
	double 	fRec16[2];
	double 	fConst36;
	double 	fRec15[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
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
	double 	fRec60[3];
	double 	fVec7[2];
	double 	fConst63;
	double 	fRec59[2];
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fRec58[2];
	double 	fRec57[3];
	double 	fVec8[2];
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fRec56[2];
	double 	fRec55[3];
	double 	fVec9[2];
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fRec54[2];
	double 	fRec53[3];
	double 	fConst73;
	double 	fConst74;
	double 	fConst75;
	double 	fRec63[2];
	double 	fRec62[3];
	double 	fConst76;
	double 	fRec61[3];
	double 	fConst77;
	double 	fConst78;
	double 	fConst79;
	double 	fRec67[2];
	double 	fRec66[3];
	double 	fConst80;
	double 	fRec65[3];
	double 	fRec64[3];
	double 	fConst81;
	double 	fRec69[2];
	double 	fRec68[3];
	double 	fConst82;
	double 	fVec10[2];
	double 	fRec52[2];
	double 	fVec11[2];
	double 	fRec14[2];
	double 	fRec12[3];
	double 	fVec12[2];
	double 	fRec11[2];
	double 	fRec9[3];
	double 	fConst83;
	double 	fRec8[2];
	double 	fRec72[2];
	double 	fRec71[3];
	double 	fRec70[2];
	double 	fRec6[2];
	double 	fRec4[2];
	double 	fRec2[2];
	double 	fRec0[2];
	void clear_state_f();
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef*);
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
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<3; i++) fRec35[i] = 0;
	for (int i=0; i<3; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<3; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<3; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<3; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<32768; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec60[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec59[i] = 0;
	for (int i=0; i<2; i++) fRec58[i] = 0;
	for (int i=0; i<3; i++) fRec57[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec56[i] = 0;
	for (int i=0; i<3; i++) fRec55[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec54[i] = 0;
	for (int i=0; i<3; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) fRec63[i] = 0;
	for (int i=0; i<3; i++) fRec62[i] = 0;
	for (int i=0; i<3; i++) fRec61[i] = 0;
	for (int i=0; i<2; i++) fRec67[i] = 0;
	for (int i=0; i<3; i++) fRec66[i] = 0;
	for (int i=0; i<3; i++) fRec65[i] = 0;
	for (int i=0; i<3; i++) fRec64[i] = 0;
	for (int i=0; i<2; i++) fRec69[i] = 0;
	for (int i=0; i<3; i++) fRec68[i] = 0;
	for (int i=0; i<2; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec12[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec72[i] = 0;
	for (int i=0; i<3; i++) fRec71[i] = 0;
	for (int i=0; i<2; i++) fRec70[i] = 0;
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
	fConst1 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst2 = (1 + fConst1);
	fConst3 = (0.0041 / fConst2);
	fConst4 = (0 - ((1 - fConst1) / fConst2));
	fConst5 = tan((37699.11184307752 / double(iConst0)));
	fConst6 = (2 * (1 - (1.0 / faustpower<2>(fConst5))));
	fConst7 = (1.0 / fConst5);
	fConst8 = (1 + ((fConst7 - 0.7653668647301795) / fConst5));
	fConst9 = (1 + ((0.7653668647301795 + fConst7) / fConst5));
	fConst10 = (1.0 / fConst9);
	fConst11 = (1 + ((fConst7 - 1.8477590650225735) / fConst5));
	fConst12 = (1.0 / (1 + ((fConst7 + 1.8477590650225735) / fConst5)));
	fConst13 = (973.8937226128359 / double(iConst0));
	fConst14 = (1 - fConst13);
	fConst15 = (1.0 / (1 + fConst13));
	fConst16 = (2.0 / fConst9);
	fConst17 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst18 = (1 + fConst17);
	fConst19 = (0.027 / fConst18);
	fConst20 = (0 - ((1 - fConst17) / fConst18));
	fConst21 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst22 = (0 - fConst21);
	fConst23 = (1 + fConst21);
	fConst24 = (0.1 / fConst23);
	fConst25 = (0 - ((1 - fConst21) / fConst23));
	fConst26 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst27 = (1 + fConst26);
	fConst28 = (0.015 / fConst27);
	fConst29 = (0 - ((1 - fConst26) / fConst27));
	fConst30 = (1.0 / fConst2);
	fConst31 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst32 = (1 + fConst31);
	fConst33 = (0.0082 / fConst32);
	fConst34 = (0 - ((1 - fConst31) / fConst32));
	IOTA = 0;
	iConst35 = int((int((0.1111111111111111 * iConst0)) & 65535));
	fConst36 = (0.009000000000000008 / double(iConst0));
	fConst37 = tan((942.4777960769379 / double(iConst0)));
	fConst38 = (1.0 / faustpower<2>(fConst37));
	fConst39 = (2 * (1 - fConst38));
	fConst40 = (1.0 / fConst37);
	fConst41 = (1 + ((fConst40 - 1.0000000000000004) / fConst37));
	fConst42 = (1.0 / (1 + ((fConst40 + 1.0000000000000004) / fConst37)));
	fConst43 = tan((3769.9111843077517 / double(iConst0)));
	fConst44 = (1.0 / faustpower<2>(fConst43));
	fConst45 = (2 * (1 - fConst44));
	fConst46 = (1.0 / fConst43);
	fConst47 = (1 + ((fConst46 - 1.0000000000000004) / fConst43));
	fConst48 = (1 + ((fConst46 + 1.0000000000000004) / fConst43));
	fConst49 = (1.0 / fConst48);
	fConst50 = tan((10053.096491487338 / double(iConst0)));
	fConst51 = (1.0 / faustpower<2>(fConst50));
	fConst52 = (2 * (1 - fConst51));
	fConst53 = (1.0 / fConst50);
	fConst54 = (1 + ((fConst53 - 1.0000000000000004) / fConst50));
	fConst55 = (1 + ((1.0000000000000004 + fConst53) / fConst50));
	fConst56 = (1.0 / fConst55);
	fConst57 = tan((47123.8898038469 / double(iConst0)));
	fConst58 = (2 * (1 - (1.0 / faustpower<2>(fConst57))));
	fConst59 = (1.0 / fConst57);
	fConst60 = (1 + ((fConst59 - 1.414213562373095) / fConst57));
	fConst61 = (1 + ((1.414213562373095 + fConst59) / fConst57));
	fConst62 = (1.0 / fConst61);
	fConst63 = (1.0 / (fConst23 * fConst61));
	fConst64 = (1 + fConst53);
	fConst65 = (1.0 / fConst64);
	fConst66 = (0 - ((1 - fConst53) / fConst64));
	fConst67 = (1 + fConst46);
	fConst68 = (1.0 / (fConst67 * fConst55));
	fConst69 = (0 - ((1 - fConst46) / fConst67));
	fConst70 = (1 + fConst40);
	fConst71 = (1.0 / (fConst70 * fConst48));
	fConst72 = (0 - ((1 - fConst40) / fConst70));
	fConst73 = (1 + ((fConst40 - 1.0) / fConst37));
	fConst74 = (1.0 / (1 + ((1.0 + fConst40) / fConst37)));
	fConst75 = (0 - fConst46);
	fConst76 = (2 * (0 - fConst44));
	fConst77 = (1 + ((fConst46 - 1.0) / fConst43));
	fConst78 = (1.0 / (1 + ((1.0 + fConst46) / fConst43)));
	fConst79 = (0 - fConst53);
	fConst80 = (2 * (0 - fConst51));
	fConst81 = (0 - fConst40);
	fConst82 = (2 * (0 - fConst38));
	fConst83 = (0.025 / fConst23);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
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
	double 	fSlow7 = (fConst42 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow8 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow9 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow10 = (fConst42 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow11 = (1 - max((double)0, (0 - fSlow4)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (0.4 * fRec2[1]);
		double fTemp1 = (0.5 * fRec0[1]);
		double fTemp2 = (fTemp1 + ((0.3 * fRec4[1]) + fTemp0));
		fRec10[0] = ((fConst4 * fRec10[1]) + (fConst3 * (fRec9[1] + fRec9[2])));
		double fTemp3 = (2.0 * fRec12[1]);
		fRec13[0] = ((0.999 * fRec13[1]) + fSlow0);
		fRec18[0] = (fSlow1 + (0.999 * fRec18[1]));
		double fTemp4 = (2.0 * fRec22[1]);
		double fTemp5 = (2.0 * fRec27[1]);
		double fTemp6 = (2.0 * fRec33[1]);
		double fTemp7 = (double)input0[i];
		fVec0[0] = fTemp7;
		fRec37[0] = (fConst15 * ((fVec0[0] - fVec0[1]) + (fConst14 * fRec37[1])));
		fRec36[0] = (fConst15 * ((fRec37[0] - fRec37[1]) + (fConst14 * fRec36[1])));
		fRec35[0] = (fRec36[0] - (fConst12 * ((fConst11 * fRec35[2]) + (fConst6 * fRec35[1]))));
		fRec34[0] = ((fConst12 * (fRec35[2] + (fRec35[0] + (2 * fRec35[1])))) - (fConst10 * ((fConst8 * fRec34[2]) + (fConst6 * fRec34[1]))));
		fRec38[0] = ((0.999 * fRec38[1]) + fSlow2);
		fRec33[0] = ((fConst16 * (fRec38[0] * (fRec34[2] + (fRec34[0] + (2 * fRec34[1]))))) - (fTemp6 + fRec33[2]));
		double fTemp8 = (fRec33[2] + (fRec33[0] + fTemp6));
		fVec1[0] = fTemp8;
		fRec32[0] = ((1.0000000000000002 * (fVec1[0] + fVec1[1])) - (0.9999999999999998 * fRec32[1]));
		fRec39[0] = ((fConst20 * fRec39[1]) + (fConst19 * (fRec31[1] + fRec31[2])));
		fRec31[0] = (Ftube(TUBE_TABLE_12AU7_68k, ((fRec39[0] + fRec32[0]) - 1.25724)) - 83.43555555555557);
		fRec30[0] = ((fConst25 * fRec30[1]) + (fConst24 * ((fConst21 * fRec31[0]) + (fConst22 * fRec31[1]))));
		double fTemp9 = (2.0 * fRec43[1]);
		fRec43[0] = (fRec29[1] - (fTemp9 + fRec43[2]));
		double fTemp10 = (fRec43[2] + (fRec43[0] + fTemp9));
		fVec2[0] = fTemp10;
		fRec42[0] = ((1.0000000000000002 * (fVec2[0] + fVec2[1])) - (0.9999999999999998 * fRec42[1]));
		fRec44[0] = ((fConst29 * fRec44[1]) + (fConst28 * (fRec41[1] + fRec41[2])));
		fRec41[0] = (Ftube(TUBE_TABLE_12AU7_250k, ((fRec44[0] + fRec42[0]) - 0.776162)) - 78.25586666666666);
		fRec40[0] = ((fConst25 * fRec40[1]) + (fConst24 * ((fConst21 * fRec41[0]) + (fConst22 * fRec41[1]))));
		fRec29[0] = ((0.6 * fRec40[0]) + fRec30[0]);
		fRec28[0] = ((fConst4 * fRec28[1]) + (fConst30 * (fRec29[0] + fRec29[1])));
		fRec27[0] = (fRec28[0] - (fTemp5 + fRec27[2]));
		double fTemp11 = (fRec27[2] + (fRec27[0] + fTemp5));
		fVec3[0] = fTemp11;
		fRec26[0] = ((1.0000000000000002 * (fVec3[0] + fVec3[1])) - (0.9999999999999998 * fRec26[1]));
		fRec45[0] = ((fConst29 * fRec45[1]) + (fConst28 * (fRec25[1] + fRec25[2])));
		fRec25[0] = (Ftube(TUBE_TABLE_12AU7_250k, ((fRec45[0] + fRec26[0]) - 0.776162)) - 78.25586666666666);
		fRec24[0] = ((fConst25 * fRec24[1]) + (fConst24 * ((fConst21 * fRec25[0]) + (fConst22 * fRec25[1]))));
		double fTemp12 = (2.0 * fRec49[1]);
		fRec49[0] = (fRec23[1] - (fTemp12 + fRec49[2]));
		double fTemp13 = (fRec49[2] + (fRec49[0] + fTemp12));
		fVec4[0] = fTemp13;
		fRec48[0] = ((1.0000000000000002 * (fVec4[0] + fVec4[1])) - (0.9999999999999998 * fRec48[1]));
		fRec50[0] = ((fConst34 * fRec50[1]) + (fConst33 * (fRec47[1] + fRec47[2])));
		fRec47[0] = (Ftube(TUBE_TABLE_12AU7_250k, ((fRec50[0] + fRec48[0]) - 0.445487)) - 75.67231707317073);
		fRec46[0] = ((fConst25 * fRec46[1]) + (fConst24 * ((fConst21 * fRec47[0]) + (fConst22 * fRec47[1]))));
		fRec23[0] = ((0.6 * fRec46[0]) + fRec24[0]);
		fRec22[0] = (fRec23[0] - (fTemp4 + fRec22[2]));
		double fTemp14 = (fRec22[2] + (fRec22[0] + fTemp4));
		fVec5[0] = fTemp14;
		fRec21[0] = ((1.0000000000000002 * (fVec5[0] + fVec5[1])) - (0.9999999999999998 * fRec21[1]));
		fRec51[0] = ((fConst34 * fRec51[1]) + (fConst33 * (fRec20[1] + fRec20[2])));
		fRec20[0] = (Ftube(TUBE_TABLE_12AU7_250k, ((fRec51[0] + fRec21[0]) - 0.445487)) - 75.67231707317073);
		fRec19[0] = ((fConst25 * fRec19[1]) + (fConst24 * ((fConst21 * fRec20[0]) + (fConst22 * fRec20[1]))));
		double fTemp15 = (fRec19[0] * fRec18[0]);
		double fTemp16 = fabs(fTemp15);
		fRec17[0] = ((0.9999 * fRec17[1]) + (9.999999999998899e-05 * fTemp16));
		double fTemp17 = max(fRec17[0], fTemp16);
		fVec6[IOTA&32767] = fTemp17;
		fRec16[0] = ((fVec6[IOTA&32767] + fRec16[1]) - fVec6[(IOTA-iConst35)&32767]);
		fRec15[0] = ((0.999 * fRec15[1]) + (fConst36 * fRec16[0]));
		double fTemp18 = max(-1.0, min(-0.01, (fVec6[IOTA&32767] - (1.0 + (1.02 * fRec15[0])))));
		double fTemp19 = (0 - fTemp18);
		double fTemp20 = (40.1 * fTemp19);
		double fTemp21 = max((double)-600, fTemp20);
		double fTemp22 = (0 - fTemp21);
		double fTemp23 = (fTemp15 - fTemp18);
		double fTemp24 = (40.1 * fTemp23);
		double fTemp25 = max((double)-600, fTemp24);
		double fTemp26 = (0 - fTemp25);
		double fTemp27 = (((int((fabs(fTemp24) > 0.0001)))?((int((fTemp25 < -50)))?(fTemp26 * exp(fTemp25)):(fTemp25 / (1 - exp(fTemp26)))):(1 + (fTemp23 * (20.05 + (134.00083333333336 * fTemp23))))) - ((int((fabs(fTemp20) > 0.0001)))?((int((fTemp21 < -50)))?(fTemp22 * exp(fTemp21)):(fTemp21 / (1 - exp(fTemp22)))):(1 + (fTemp19 * (20.05 + (134.00083333333336 * fTemp19))))));
		double fTemp28 = (fRec19[0] * (1 - fRec18[0]));
		fRec60[0] = ((0.024937655860349125 * fTemp27) - (fConst62 * ((fConst60 * fRec60[2]) + (fConst58 * fRec60[1]))));
		double fTemp29 = (fRec60[2] + (fRec60[0] + (2 * fRec60[1])));
		fVec7[0] = fTemp29;
		fRec59[0] = ((fConst25 * fRec59[1]) + (fConst63 * ((fConst21 * fVec7[0]) + (fConst22 * fVec7[1]))));
		fRec58[0] = ((fConst66 * fRec58[1]) + (fConst65 * (fRec59[0] + fRec59[1])));
		fRec57[0] = (fRec58[0] - (fConst56 * ((fConst54 * fRec57[2]) + (fConst52 * fRec57[1]))));
		double fTemp30 = (fRec57[2] + (fRec57[0] + (2 * fRec57[1])));
		fVec8[0] = fTemp30;
		fRec56[0] = ((fConst69 * fRec56[1]) + (fConst68 * (fVec8[0] + fVec8[1])));
		fRec55[0] = (fRec56[0] - (fConst49 * ((fConst47 * fRec55[2]) + (fConst45 * fRec55[1]))));
		double fTemp31 = (fRec55[2] + (fRec55[0] + (2 * fRec55[1])));
		fVec9[0] = fTemp31;
		fRec54[0] = ((fConst72 * fRec54[1]) + (fConst71 * (fVec9[0] + fVec9[1])));
		fRec53[0] = (fRec54[0] - (fConst42 * ((fConst41 * fRec53[2]) + (fConst39 * fRec53[1]))));
		double fTemp32 = max((double)-1, min((double)1, (fSlow7 * (fRec53[2] + (fRec53[0] + (2 * fRec53[1]))))));
		double fTemp33 = (fConst39 * fRec61[1]);
		fRec63[0] = ((fConst69 * fRec63[1]) + (fConst68 * ((fConst46 * fVec8[0]) + (fConst75 * fVec8[1]))));
		fRec62[0] = (fRec63[0] - (fConst49 * ((fConst47 * fRec62[2]) + (fConst45 * fRec62[1]))));
		fRec61[0] = ((fConst49 * (((fConst44 * fRec62[0]) + (fConst76 * fRec62[1])) + (fConst44 * fRec62[2]))) - (fConst74 * ((fConst73 * fRec61[2]) + fTemp33)));
		double fTemp34 = max((double)-1, min((double)1, (fSlow8 * (fRec61[2] + (fConst74 * (fTemp33 + (fConst73 * fRec61[0])))))));
		double fTemp35 = (fConst39 * fRec64[1]);
		double fTemp36 = (fConst45 * fRec65[1]);
		fRec67[0] = ((fConst66 * fRec67[1]) + (fConst65 * ((fConst53 * fRec59[0]) + (fConst79 * fRec59[1]))));
		fRec66[0] = (fRec67[0] - (fConst56 * ((fConst54 * fRec66[2]) + (fConst52 * fRec66[1]))));
		fRec65[0] = ((fConst56 * (((fConst51 * fRec66[0]) + (fConst80 * fRec66[1])) + (fConst51 * fRec66[2]))) - (fConst78 * ((fConst77 * fRec65[2]) + fTemp36)));
		fRec64[0] = ((fRec65[2] + (fConst78 * (fTemp36 + (fConst77 * fRec65[0])))) - (fConst74 * ((fConst73 * fRec64[2]) + fTemp35)));
		double fTemp37 = max((double)-1, min((double)1, (fSlow9 * (fRec64[2] + (fConst74 * (fTemp35 + (fConst73 * fRec64[0])))))));
		fRec69[0] = ((fConst72 * fRec69[1]) + (fConst71 * ((fConst40 * fVec9[0]) + (fConst81 * fVec9[1]))));
		fRec68[0] = (fRec69[0] - (fConst42 * ((fConst41 * fRec68[2]) + (fConst39 * fRec68[1]))));
		double fTemp38 = max((double)-1, min((double)1, (fSlow10 * (((fConst38 * fRec68[0]) + (fConst82 * fRec68[1])) + (fConst38 * fRec68[2])))));
		double fTemp39 = ((1.584893192 * ((fTemp38 * (1 - (0.3333333333333333 * faustpower<2>(fTemp38)))) + ((fTemp37 * (1 - (0.3333333333333333 * faustpower<2>(fTemp37)))) + (0.8413951417869425 * (fTemp34 * (1 - (0.3333333333333333 * faustpower<2>(fTemp34)))))))) + (1.2589412 * (fTemp32 * (1 - (0.3333333333333333 * faustpower<2>(fTemp32))))));
		fVec10[0] = fTemp39;
		fRec52[0] = ((fConst4 * fRec52[1]) + (fConst30 * (fVec10[0] + fVec10[1])));
		double fTemp40 = ((fSlow11 * fRec52[0]) + ((fTemp28 * (1 + (fSlow6 * ((4 - (4 * fabs(fTemp28))) - 1)))) + (fSlow5 * fTemp27)));
		fVec11[0] = fTemp40;
		fRec14[0] = ((fConst4 * fRec14[1]) + (fConst30 * (fVec11[0] + fVec11[1])));
		fRec12[0] = ((fRec14[0] * fRec13[0]) - (fTemp3 + fRec12[2]));
		double fTemp41 = (fRec12[2] + (fRec12[0] + fTemp3));
		fVec12[0] = fTemp41;
		fRec11[0] = ((1.0000000000000002 * (fVec12[0] + fVec12[1])) - (0.9999999999999998 * fRec11[1]));
		fRec9[0] = (Ftube(TUBE_TABLE_6V6_68k, ((fRec11[0] + fRec10[0]) - 0.664541)) - 87.91682926829267);
		fRec8[0] = ((fConst25 * fRec8[1]) + (fConst83 * ((fConst21 * fRec9[0]) + (fConst22 * fRec9[1]))));
		fRec72[0] = ((fConst4 * fRec72[1]) + (fConst3 * (fRec71[1] + fRec71[2])));
		fRec71[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec72[0] + fRec11[0]) - 0.659761)) - 89.08268292682925);
		fRec70[0] = ((fConst25 * fRec70[1]) + (fConst83 * ((fConst21 * fRec71[0]) + (fConst22 * fRec71[1]))));
		double fTemp42 = (min(0.7, fRec70[0]) + max(-0.75, fRec8[0]));
		double fTemp43 = ((fTemp42 + (0.2 * fRec6[1])) - fTemp2);
		fRec6[0] = fTemp43;
		double 	fRec7 = (0 - (0.2 * fTemp43));
		fRec4[0] = (fRec7 + fRec6[1]);
		double 	fRec5 = (0.3 * (fTemp42 - fTemp2));
		fRec2[0] = (fRec5 + fRec4[1]);
		double 	fRec3 = (0.4 * (fTemp42 - (fTemp0 + fTemp1)));
		fRec0[0] = (fRec3 + fRec2[1]);
		double 	fRec1 = (0.5 * (fTemp42 - fTemp1));
		output0[i] = (FAUSTFLOAT)(fRec1 + fRec0[1]);
		// post processing
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fRec6[1] = fRec6[0];
		fRec70[1] = fRec70[0];
		fRec71[2] = fRec71[1]; fRec71[1] = fRec71[0];
		fRec72[1] = fRec72[0];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec11[1] = fRec11[0];
		fVec12[1] = fVec12[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec14[1] = fRec14[0];
		fVec11[1] = fVec11[0];
		fRec52[1] = fRec52[0];
		fVec10[1] = fVec10[0];
		fRec68[2] = fRec68[1]; fRec68[1] = fRec68[0];
		fRec69[1] = fRec69[0];
		fRec64[2] = fRec64[1]; fRec64[1] = fRec64[0];
		fRec65[2] = fRec65[1]; fRec65[1] = fRec65[0];
		fRec66[2] = fRec66[1]; fRec66[1] = fRec66[0];
		fRec67[1] = fRec67[0];
		fRec61[2] = fRec61[1]; fRec61[1] = fRec61[0];
		fRec62[2] = fRec62[1]; fRec62[1] = fRec62[0];
		fRec63[1] = fRec63[0];
		fRec53[2] = fRec53[1]; fRec53[1] = fRec53[0];
		fRec54[1] = fRec54[0];
		fVec9[1] = fVec9[0];
		fRec55[2] = fRec55[1]; fRec55[1] = fRec55[0];
		fRec56[1] = fRec56[0];
		fVec8[1] = fVec8[0];
		fRec57[2] = fRec57[1]; fRec57[1] = fRec57[0];
		fRec58[1] = fRec58[0];
		fRec59[1] = fRec59[0];
		fVec7[1] = fVec7[0];
		fRec60[2] = fRec60[1]; fRec60[1] = fRec60[0];
		fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		IOTA = IOTA+1;
		fRec17[1] = fRec17[0];
		fRec19[1] = fRec19[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec51[1] = fRec51[0];
		fRec21[1] = fRec21[0];
		fVec5[1] = fVec5[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec46[1] = fRec46[0];
		fRec47[2] = fRec47[1]; fRec47[1] = fRec47[0];
		fRec50[1] = fRec50[0];
		fRec48[1] = fRec48[0];
		fVec4[1] = fVec4[0];
		fRec49[2] = fRec49[1]; fRec49[1] = fRec49[0];
		fRec24[1] = fRec24[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec45[1] = fRec45[0];
		fRec26[1] = fRec26[0];
		fVec3[1] = fVec3[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec40[1] = fRec40[0];
		fRec41[2] = fRec41[1]; fRec41[1] = fRec41[0];
		fRec44[1] = fRec44[0];
		fRec42[1] = fRec42[0];
		fVec2[1] = fVec2[0];
		fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
		fRec30[1] = fRec30[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec39[1] = fRec39[0];
		fRec32[1] = fRec32[0];
		fVec1[1] = fVec1[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec38[1] = fRec38[0];
		fRec34[2] = fRec34[1]; fRec34[1] = fRec34[0];
		fRec35[2] = fRec35[1]; fRec35[1] = fRec35[0];
		fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fVec0[1] = fVec0[0];
		fRec18[1] = fRec18[0];
		fRec13[1] = fRec13[0];
		fRec10[1] = fRec10[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	fslider3_ = reg.registerVar("gxdistortion.drive","","SA","",&fslider3, 0.35, 0.0, 1.0, 0.01);
	fslider1_ = reg.registerVar("gxdistortion.wet_dry","","SA","",&fslider1, 1e+02, 0.0, 1e+02, 1.0);
	fslider2_ = reg.registerVar("amp2.stage1.Pregain","","SA","",&fslider2, -6.0, -2e+01, 2e+01, 0.1);
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
