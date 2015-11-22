// generated from file '../src/faust/gxamp6.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp6 {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int samplingFreq;
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
	double 	fRec12[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec13[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec18[2];
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fVec0[2];
	double 	fConst19;
	double 	fRec31[2];
	double 	fRec30[2];
	double 	fRec29[3];
	double 	fRec28[3];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec32[2];
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fRec33[2];
	double 	fRec27[3];
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fRec26[2];
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fRec36[2];
	double 	fRec35[3];
	double 	fRec34[2];
	double 	fRec25[2];
	double 	fConst33;
	double 	fRec24[2];
	double 	fRec37[2];
	double 	fRec23[3];
	double 	fRec22[2];
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fRec40[2];
	double 	fRec39[3];
	double 	fRec38[2];
	double 	fRec21[2];
	double 	fRec41[2];
	double 	fRec20[3];
	double 	fRec19[2];
	double 	fRec17[2];
	int 	IOTA;
	double 	fVec1[32768];
	int 	iConst38;
	double 	fRec16[2];
	double 	fConst39;
	double 	fRec15[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
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
	double 	fRec50[3];
	double 	fVec2[2];
	double 	fConst66;
	double 	fRec49[2];
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fRec48[2];
	double 	fRec47[3];
	double 	fVec3[2];
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fRec46[2];
	double 	fRec45[3];
	double 	fVec4[2];
	double 	fConst73;
	double 	fConst74;
	double 	fConst75;
	double 	fRec44[2];
	double 	fRec43[3];
	double 	fConst76;
	double 	fConst77;
	double 	fConst78;
	double 	fRec53[2];
	double 	fRec52[3];
	double 	fConst79;
	double 	fRec51[3];
	double 	fConst80;
	double 	fConst81;
	double 	fConst82;
	double 	fRec57[2];
	double 	fRec56[3];
	double 	fConst83;
	double 	fRec55[3];
	double 	fRec54[3];
	double 	fConst84;
	double 	fRec59[2];
	double 	fRec58[3];
	double 	fConst85;
	double 	fVec5[2];
	double 	fRec42[2];
	double 	fVec6[2];
	double 	fRec14[2];
	double 	fRec11[3];
	double 	fConst86;
	double 	fRec10[2];
	double 	fRec62[2];
	double 	fRec61[3];
	double 	fRec60[2];
	double 	fRec8[2];
	double 	fRec6[2];
	double 	fRec4[2];
	double 	fRec2[2];
	double 	fVec7[2];
	double 	fConst87;
	double 	fConst88;
	double 	fConst89;
	double 	fRec1[2];
	double 	fRec0[3];
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
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<3; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<3; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<32768; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec50[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<3; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<3; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<3; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) fRec53[i] = 0;
	for (int i=0; i<3; i++) fRec52[i] = 0;
	for (int i=0; i<3; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fRec57[i] = 0;
	for (int i=0; i<3; i++) fRec56[i] = 0;
	for (int i=0; i<3; i++) fRec55[i] = 0;
	for (int i=0; i<3; i++) fRec54[i] = 0;
	for (int i=0; i<2; i++) fRec59[i] = 0;
	for (int i=0; i<3; i++) fRec58[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec62[i] = 0;
	for (int i=0; i<3; i++) fRec61[i] = 0;
	for (int i=0; i<2; i++) fRec60[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int RsamplingFreq)
{
	samplingFreq = 192000;
	smp.setup(RsamplingFreq, samplingFreq);
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = tan((50265.48245743669 / double(iConst0)));
	fConst2 = (2 * (1 - (1.0 / faustpower<2>(fConst1))));
	fConst3 = (1.0 / fConst1);
	fConst4 = (1 + ((fConst3 - 1.0000000000000004) / fConst1));
	fConst5 = (1.0 / (1 + ((1.0000000000000004 + fConst3) / fConst1)));
	fConst6 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst7 = (1 + fConst6);
	fConst8 = (0.0041 / fConst7);
	fConst9 = (0 - ((1 - fConst6) / fConst7));
	fConst10 = tan((37699.11184307752 / double(iConst0)));
	fConst11 = (2 * (1 - (1.0 / faustpower<2>(fConst10))));
	fConst12 = (1.0 / fConst10);
	fConst13 = (1 + ((fConst12 - 0.7653668647301795) / fConst10));
	fConst14 = (1.0 / (1 + ((0.7653668647301795 + fConst12) / fConst10)));
	fConst15 = (1 + ((fConst12 - 1.8477590650225735) / fConst10));
	fConst16 = (1.0 / (1 + ((fConst12 + 1.8477590650225735) / fConst10)));
	fConst17 = (973.8937226128359 / double(iConst0));
	fConst18 = (1 - fConst17);
	fConst19 = (1.0 / (1 + fConst17));
	fConst20 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst21 = (1 + fConst20);
	fConst22 = (0.027 / fConst21);
	fConst23 = (0 - ((1 - fConst20) / fConst21));
	fConst24 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst25 = (0 - fConst24);
	fConst26 = (1 + fConst24);
	fConst27 = (0.05 / fConst26);
	fConst28 = (0 - ((1 - fConst24) / fConst26));
	fConst29 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst30 = (1 + fConst29);
	fConst31 = (0.015 / fConst30);
	fConst32 = (0 - ((1 - fConst29) / fConst30));
	fConst33 = (1.0 / fConst7);
	fConst34 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst35 = (1 + fConst34);
	fConst36 = (0.0082 / fConst35);
	fConst37 = (0 - ((1 - fConst34) / fConst35));
	IOTA = 0;
	iConst38 = int((int((0.1111111111111111 * iConst0)) & 65535));
	fConst39 = (0.009000000000000008 / double(iConst0));
	fConst40 = tan((942.4777960769379 / double(iConst0)));
	fConst41 = (1.0 / faustpower<2>(fConst40));
	fConst42 = (2 * (1 - fConst41));
	fConst43 = (1.0 / fConst40);
	fConst44 = (1 + ((fConst43 - 1.0000000000000004) / fConst40));
	fConst45 = (1.0 / (1 + ((1.0000000000000004 + fConst43) / fConst40)));
	fConst46 = tan((3769.9111843077517 / double(iConst0)));
	fConst47 = (1.0 / faustpower<2>(fConst46));
	fConst48 = (2 * (1 - fConst47));
	fConst49 = (1.0 / fConst46);
	fConst50 = (1 + ((fConst49 - 1.0000000000000004) / fConst46));
	fConst51 = (1 + ((1.0000000000000004 + fConst49) / fConst46));
	fConst52 = (1.0 / fConst51);
	fConst53 = tan((10053.096491487338 / double(iConst0)));
	fConst54 = (1.0 / faustpower<2>(fConst53));
	fConst55 = (2 * (1 - fConst54));
	fConst56 = (1.0 / fConst53);
	fConst57 = (1 + ((fConst56 - 1.0000000000000004) / fConst53));
	fConst58 = (1 + ((1.0000000000000004 + fConst56) / fConst53));
	fConst59 = (1.0 / fConst58);
	fConst60 = tan((47123.8898038469 / double(iConst0)));
	fConst61 = (2 * (1 - (1.0 / faustpower<2>(fConst60))));
	fConst62 = (1.0 / fConst60);
	fConst63 = (1 + ((fConst62 - 1.414213562373095) / fConst60));
	fConst64 = (1 + ((1.414213562373095 + fConst62) / fConst60));
	fConst65 = (1.0 / fConst64);
	fConst66 = (1.0 / (fConst26 * fConst64));
	fConst67 = (1 + fConst56);
	fConst68 = (1.0 / fConst67);
	fConst69 = (0 - ((1 - fConst56) / fConst67));
	fConst70 = (1 + fConst49);
	fConst71 = (1.0 / (fConst70 * fConst58));
	fConst72 = (0 - ((1 - fConst49) / fConst70));
	fConst73 = (1 + fConst43);
	fConst74 = (1.0 / (fConst73 * fConst51));
	fConst75 = (0 - ((1 - fConst43) / fConst73));
	fConst76 = (1 + ((fConst43 - 1.0) / fConst40));
	fConst77 = (1.0 / (1 + ((1.0 + fConst43) / fConst40)));
	fConst78 = (0 - fConst49);
	fConst79 = (2 * (0 - fConst47));
	fConst80 = (1 + ((fConst49 - 1.0) / fConst46));
	fConst81 = (1.0 / (1 + ((1.0 + fConst49) / fConst46)));
	fConst82 = (0 - fConst56);
	fConst83 = (2 * (0 - fConst54));
	fConst84 = (0 - fConst43);
	fConst85 = (2 * (0 - fConst41));
	fConst86 = (0.025 / fConst26);
	fConst87 = (1 + fConst3);
	fConst88 = (1.0 / fConst87);
	fConst89 = (0 - ((1 - fConst3) / fConst87));
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
	float buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider0))));
	double 	fSlow1 = (1.000000000000001e-05 * double(fslider1));
	double 	fSlow2 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider2))));
	double 	fSlow3 = double(fslider3);
	double 	fSlow4 = (2 * (fSlow3 - 0.5));
	double 	fSlow5 = (0.024937655860349125 * (1 - max((double)0, fSlow4)));
	double 	fSlow6 = (1.25 * fSlow3);
	double 	fSlow7 = (fConst45 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow8 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow9 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow10 = (fConst45 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow11 = (1 - max((double)0, (0 - fSlow4)));
	for (int i=0; i<ReCount; i++) {
		double fTemp0 = (0.4 * fRec4[1]);
		double fTemp1 = (0.5 * fRec2[1]);
		double fTemp2 = (fTemp1 + ((0.3 * fRec6[1]) + fTemp0));
		fRec12[0] = ((fConst9 * fRec12[1]) + (fConst8 * (fRec11[1] + fRec11[2])));
		fRec13[0] = ((0.999 * fRec13[1]) + fSlow0);
		fRec18[0] = (fSlow1 + (0.999 * fRec18[1]));
		double fTemp3 = (double)buf[i];
		fVec0[0] = fTemp3;
		fRec31[0] = (fConst19 * ((fVec0[0] - fVec0[1]) + (fConst18 * fRec31[1])));
		fRec30[0] = (fConst19 * ((fRec31[0] - fRec31[1]) + (fConst18 * fRec30[1])));
		fRec29[0] = (fRec30[0] - (fConst16 * ((fConst15 * fRec29[2]) + (fConst11 * fRec29[1]))));
		fRec28[0] = ((fConst16 * (fRec29[2] + (fRec29[0] + (2 * fRec29[1])))) - (fConst14 * ((fConst13 * fRec28[2]) + (fConst11 * fRec28[1]))));
		fRec32[0] = ((0.999 * fRec32[1]) + fSlow2);
		fRec33[0] = ((fConst23 * fRec33[1]) + (fConst22 * (fRec27[1] + fRec27[2])));
		fRec27[0] = (Ftube(TUBE_TABLE_6DJ8_68k, ((fRec33[0] + (fConst14 * (fRec32[0] * (fRec28[2] + (fRec28[0] + (2 * fRec28[1])))))) - 1.863946)) - 60.96496296296296);
		fRec26[0] = ((fConst28 * fRec26[1]) + (fConst27 * ((fConst24 * fRec27[0]) + (fConst25 * fRec27[1]))));
		fRec36[0] = ((fConst32 * fRec36[1]) + (fConst31 * (fRec35[1] + fRec35[2])));
		fRec35[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec36[0] + fRec25[1]) - 1.271609)) - 45.22606666666667);
		fRec34[0] = ((fConst28 * fRec34[1]) + (fConst27 * ((fConst24 * fRec35[0]) + (fConst25 * fRec35[1]))));
		fRec25[0] = ((0.6 * fRec34[0]) + fRec26[0]);
		fRec24[0] = ((fConst9 * fRec24[1]) + (fConst33 * (fRec25[0] + fRec25[1])));
		fRec37[0] = ((fConst32 * fRec37[1]) + (fConst31 * (fRec23[1] + fRec23[2])));
		fRec23[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec37[0] + fRec24[0]) - 1.271609)) - 45.22606666666667);
		fRec22[0] = ((fConst28 * fRec22[1]) + (fConst27 * ((fConst24 * fRec23[0]) + (fConst25 * fRec23[1]))));
		fRec40[0] = ((fConst37 * fRec40[1]) + (fConst36 * (fRec39[1] + fRec39[2])));
		fRec39[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec40[0] + fRec21[1]) - 0.797043)) - 32.799634146341475);
		fRec38[0] = ((fConst28 * fRec38[1]) + (fConst27 * ((fConst24 * fRec39[0]) + (fConst25 * fRec39[1]))));
		fRec21[0] = ((0.6 * fRec38[0]) + fRec22[0]);
		fRec41[0] = ((fConst37 * fRec41[1]) + (fConst36 * (fRec20[1] + fRec20[2])));
		fRec20[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec41[0] + fRec21[0]) - 0.797043)) - 32.799634146341475);
		fRec19[0] = ((fConst28 * fRec19[1]) + (fConst27 * ((fConst24 * fRec20[0]) + (fConst25 * fRec20[1]))));
		double fTemp4 = (fRec19[0] * fRec18[0]);
		double fTemp5 = fabs(fTemp4);
		fRec17[0] = ((0.9999 * fRec17[1]) + (9.999999999998899e-05 * fTemp5));
		double fTemp6 = max(fRec17[0], fTemp5);
		fVec1[IOTA&32767] = fTemp6;
		fRec16[0] = ((fVec1[IOTA&32767] + fRec16[1]) - fVec1[(IOTA-iConst38)&32767]);
		fRec15[0] = ((0.999 * fRec15[1]) + (fConst39 * fRec16[0]));
		double fTemp7 = max(-1.0, min(-0.01, (fVec1[IOTA&32767] - (1.0 + (1.02 * fRec15[0])))));
		double fTemp8 = (0 - fTemp7);
		double fTemp9 = (40.1 * fTemp8);
		double fTemp10 = max((double)-600, fTemp9);
		double fTemp11 = (0 - fTemp10);
		double fTemp12 = (fTemp4 - fTemp7);
		double fTemp13 = (40.1 * fTemp12);
		double fTemp14 = max((double)-600, fTemp13);
		double fTemp15 = (0 - fTemp14);
		double fTemp16 = (((int((fabs(fTemp13) > 0.0001)))?((int((fTemp14 < -50)))?(fTemp15 * exp(fTemp14)):(fTemp14 / (1 - exp(fTemp15)))):(1 + (fTemp12 * (20.05 + (134.00083333333336 * fTemp12))))) - ((int((fabs(fTemp9) > 0.0001)))?((int((fTemp10 < -50)))?(fTemp11 * exp(fTemp10)):(fTemp10 / (1 - exp(fTemp11)))):(1 + (fTemp8 * (20.05 + (134.00083333333336 * fTemp8))))));
		double fTemp17 = (fRec19[0] * (1 - fRec18[0]));
		fRec50[0] = ((0.024937655860349125 * fTemp16) - (fConst65 * ((fConst63 * fRec50[2]) + (fConst61 * fRec50[1]))));
		double fTemp18 = (fRec50[2] + (fRec50[0] + (2 * fRec50[1])));
		fVec2[0] = fTemp18;
		fRec49[0] = ((fConst28 * fRec49[1]) + (fConst66 * ((fConst24 * fVec2[0]) + (fConst25 * fVec2[1]))));
		fRec48[0] = ((fConst69 * fRec48[1]) + (fConst68 * (fRec49[0] + fRec49[1])));
		fRec47[0] = (fRec48[0] - (fConst59 * ((fConst57 * fRec47[2]) + (fConst55 * fRec47[1]))));
		double fTemp19 = (fRec47[2] + (fRec47[0] + (2 * fRec47[1])));
		fVec3[0] = fTemp19;
		fRec46[0] = ((fConst72 * fRec46[1]) + (fConst71 * (fVec3[0] + fVec3[1])));
		fRec45[0] = (fRec46[0] - (fConst52 * ((fConst50 * fRec45[2]) + (fConst48 * fRec45[1]))));
		double fTemp20 = (fRec45[2] + (fRec45[0] + (2 * fRec45[1])));
		fVec4[0] = fTemp20;
		fRec44[0] = ((fConst75 * fRec44[1]) + (fConst74 * (fVec4[0] + fVec4[1])));
		fRec43[0] = (fRec44[0] - (fConst45 * ((fConst44 * fRec43[2]) + (fConst42 * fRec43[1]))));
		double fTemp21 = max((double)-1, min((double)1, (fSlow7 * (fRec43[2] + (fRec43[0] + (2 * fRec43[1]))))));
		double fTemp22 = (fConst42 * fRec51[1]);
		fRec53[0] = ((fConst72 * fRec53[1]) + (fConst71 * ((fConst49 * fVec3[0]) + (fConst78 * fVec3[1]))));
		fRec52[0] = (fRec53[0] - (fConst52 * ((fConst50 * fRec52[2]) + (fConst48 * fRec52[1]))));
		fRec51[0] = ((fConst52 * (((fConst47 * fRec52[0]) + (fConst79 * fRec52[1])) + (fConst47 * fRec52[2]))) - (fConst77 * ((fConst76 * fRec51[2]) + fTemp22)));
		double fTemp23 = max((double)-1, min((double)1, (fSlow8 * (fRec51[2] + (fConst77 * (fTemp22 + (fConst76 * fRec51[0])))))));
		double fTemp24 = (fConst42 * fRec54[1]);
		double fTemp25 = (fConst48 * fRec55[1]);
		fRec57[0] = ((fConst69 * fRec57[1]) + (fConst68 * ((fConst56 * fRec49[0]) + (fConst82 * fRec49[1]))));
		fRec56[0] = (fRec57[0] - (fConst59 * ((fConst57 * fRec56[2]) + (fConst55 * fRec56[1]))));
		fRec55[0] = ((fConst59 * (((fConst54 * fRec56[0]) + (fConst83 * fRec56[1])) + (fConst54 * fRec56[2]))) - (fConst81 * ((fConst80 * fRec55[2]) + fTemp25)));
		fRec54[0] = ((fRec55[2] + (fConst81 * (fTemp25 + (fConst80 * fRec55[0])))) - (fConst77 * ((fConst76 * fRec54[2]) + fTemp24)));
		double fTemp26 = max((double)-1, min((double)1, (fSlow9 * (fRec54[2] + (fConst77 * (fTemp24 + (fConst76 * fRec54[0])))))));
		fRec59[0] = ((fConst75 * fRec59[1]) + (fConst74 * ((fConst43 * fVec4[0]) + (fConst84 * fVec4[1]))));
		fRec58[0] = (fRec59[0] - (fConst45 * ((fConst44 * fRec58[2]) + (fConst42 * fRec58[1]))));
		double fTemp27 = max((double)-1, min((double)1, (fSlow10 * (((fConst41 * fRec58[0]) + (fConst85 * fRec58[1])) + (fConst41 * fRec58[2])))));
		double fTemp28 = ((1.584893192 * ((fTemp27 * (1 - (0.3333333333333333 * faustpower<2>(fTemp27)))) + ((fTemp26 * (1 - (0.3333333333333333 * faustpower<2>(fTemp26)))) + (0.8413951417869425 * (fTemp23 * (1 - (0.3333333333333333 * faustpower<2>(fTemp23)))))))) + (1.2589412 * (fTemp21 * (1 - (0.3333333333333333 * faustpower<2>(fTemp21))))));
		fVec5[0] = fTemp28;
		fRec42[0] = ((fConst9 * fRec42[1]) + (fConst33 * (fVec5[0] + fVec5[1])));
		double fTemp29 = ((fSlow11 * fRec42[0]) + ((fTemp17 * (1 + (fSlow6 * ((4 - (4 * fabs(fTemp17))) - 1)))) + (fSlow5 * fTemp16)));
		fVec6[0] = fTemp29;
		fRec14[0] = ((fConst9 * fRec14[1]) + (fConst33 * (fVec6[0] + fVec6[1])));
		double fTemp30 = (fRec14[0] * fRec13[0]);
		fRec11[0] = (Ftube(TUBE_TABLE_6V6_68k, ((fTemp30 + fRec12[0]) - 0.664541)) - 87.91682926829267);
		fRec10[0] = ((fConst28 * fRec10[1]) + (fConst86 * ((fConst24 * fRec11[0]) + (fConst25 * fRec11[1]))));
		fRec62[0] = ((fConst9 * fRec62[1]) + (fConst8 * (fRec61[1] + fRec61[2])));
		fRec61[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec62[0] + fTemp30) - 0.659761)) - 89.08268292682925);
		fRec60[0] = ((fConst28 * fRec60[1]) + (fConst86 * ((fConst24 * fRec61[0]) + (fConst25 * fRec61[1]))));
		double fTemp31 = (min(0.7, fRec60[0]) + max(-0.75, fRec10[0]));
		double fTemp32 = ((fTemp31 + (0.2 * fRec8[1])) - fTemp2);
		fRec8[0] = fTemp32;
		double 	fRec9 = (0 - (0.2 * fTemp32));
		fRec6[0] = (fRec9 + fRec8[1]);
		double 	fRec7 = (0.3 * (fTemp31 - fTemp2));
		fRec4[0] = (fRec7 + fRec6[1]);
		double 	fRec5 = (0.4 * (fTemp31 - (fTemp0 + fTemp1)));
		fRec2[0] = (fRec5 + fRec4[1]);
		double 	fRec3 = (0.5 * (fTemp31 - fTemp1));
		double fTemp33 = (fRec3 + fRec2[1]);
		fVec7[0] = fTemp33;
		fRec1[0] = ((fConst89 * fRec1[1]) + (fConst88 * (fVec7[0] + fVec7[1])));
		fRec0[0] = (fRec1[0] - (fConst5 * ((fConst4 * fRec0[2]) + (fConst2 * fRec0[1]))));
		buf[i] = (FAUSTFLOAT)(fConst5 * (fRec0[2] + (fRec0[0] + (2 * fRec0[1]))));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fVec7[1] = fVec7[0];
		fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fRec6[1] = fRec6[0];
		fRec8[1] = fRec8[0];
		fRec60[1] = fRec60[0];
		fRec61[2] = fRec61[1]; fRec61[1] = fRec61[0];
		fRec62[1] = fRec62[0];
		fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec14[1] = fRec14[0];
		fVec6[1] = fVec6[0];
		fRec42[1] = fRec42[0];
		fVec5[1] = fVec5[0];
		fRec58[2] = fRec58[1]; fRec58[1] = fRec58[0];
		fRec59[1] = fRec59[0];
		fRec54[2] = fRec54[1]; fRec54[1] = fRec54[0];
		fRec55[2] = fRec55[1]; fRec55[1] = fRec55[0];
		fRec56[2] = fRec56[1]; fRec56[1] = fRec56[0];
		fRec57[1] = fRec57[0];
		fRec51[2] = fRec51[1]; fRec51[1] = fRec51[0];
		fRec52[2] = fRec52[1]; fRec52[1] = fRec52[0];
		fRec53[1] = fRec53[0];
		fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
		fRec44[1] = fRec44[0];
		fVec4[1] = fVec4[0];
		fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
		fRec46[1] = fRec46[0];
		fVec3[1] = fVec3[0];
		fRec47[2] = fRec47[1]; fRec47[1] = fRec47[0];
		fRec48[1] = fRec48[0];
		fRec49[1] = fRec49[0];
		fVec2[1] = fVec2[0];
		fRec50[2] = fRec50[1]; fRec50[1] = fRec50[0];
		fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		IOTA = IOTA+1;
		fRec17[1] = fRec17[0];
		fRec19[1] = fRec19[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec41[1] = fRec41[0];
		fRec21[1] = fRec21[0];
		fRec38[1] = fRec38[0];
		fRec39[2] = fRec39[1]; fRec39[1] = fRec39[0];
		fRec40[1] = fRec40[0];
		fRec22[1] = fRec22[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec37[1] = fRec37[0];
		fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec34[1] = fRec34[0];
		fRec35[2] = fRec35[1]; fRec35[1] = fRec35[0];
		fRec36[1] = fRec36[0];
		fRec26[1] = fRec26[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec33[1] = fRec33[0];
		fRec32[1] = fRec32[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fVec0[1] = fVec0[0];
		fRec18[1] = fRec18[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
	}
	smp.down(buf, output0);

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

} // end namespace gxamp6
