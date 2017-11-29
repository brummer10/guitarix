// generated from file '../src/faust/gxamp16.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp16 {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int samplingFreq;
	int fSamplingFreq;
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
	double 	fConst8;
	double 	fVec0[2];
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fRec33[2];
	double 	fRec32[2];
	double 	fRec31[3];
	double 	fRec30[3];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec34[2];
	double 	fVec1[2];
	double 	fConst12;
	double 	fRec29[2];
	double 	fRec28[3];
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fRec35[2];
	double 	fRec27[3];
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fRec26[2];
	double 	fRec39[2];
	double 	fRec38[3];
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fRec40[2];
	double 	fRec37[3];
	double 	fRec36[2];
	double 	fRec25[3];
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fRec24[2];
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fRec41[2];
	double 	fRec21[3];
	double 	fRec20[2];
	double 	fRec45[2];
	double 	fRec44[3];
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fRec46[2];
	double 	fRec43[3];
	double 	fRec42[2];
	double 	fRec19[3];
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fRec47[2];
	double 	fRec16[3];
	double 	fRec15[2];
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
	double 	fRec59[2];
	int 	IOTA;
	double 	fVec2[32768];
	int 	iConst60;
	double 	fRec58[2];
	double 	fConst61;
	double 	fRec57[2];
	double 	fRec56[3];
	double 	fVec3[2];
	double 	fConst62;
	double 	fRec55[2];
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fRec54[2];
	double 	fRec53[3];
	double 	fVec4[2];
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fRec52[2];
	double 	fRec51[3];
	double 	fVec5[2];
	double 	fConst69;
	double 	fConst70;
	double 	fConst71;
	double 	fRec50[2];
	double 	fRec49[3];
	double 	fConst72;
	double 	fConst73;
	double 	fConst74;
	double 	fConst75;
	double 	fConst76;
	double 	fRec63[2];
	double 	fRec62[3];
	double 	fConst77;
	double 	fRec61[3];
	double 	fRec60[3];
	double 	fConst78;
	double 	fRec65[2];
	double 	fRec64[3];
	double 	fConst79;
	double 	fConst80;
	double 	fRec68[2];
	double 	fRec67[3];
	double 	fConst81;
	double 	fRec66[3];
	double 	fVec6[2];
	double 	fRec48[2];
	double 	fVec7[2];
	double 	fRec13[2];
	double 	fVec8[2];
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fConst82;
	double 	fRec69[2];
	double 	fRec9[3];
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
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<3; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<3; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<3; i++) fRec44[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<3; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec59[i] = 0;
	for (int i=0; i<32768; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec58[i] = 0;
	for (int i=0; i<2; i++) fRec57[i] = 0;
	for (int i=0; i<3; i++) fRec56[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<2; i++) fRec54[i] = 0;
	for (int i=0; i<3; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<3; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
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
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec69[i] = 0;
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

inline void Dsp::init(unsigned int RsamplingFreq)
{
	samplingFreq = 96000;
	smp.setup(RsamplingFreq, samplingFreq);
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = tan((37699.11184307752 / fConst0));
	fConst2 = (1.0 / fConst1);
	fConst3 = (1 + ((fConst2 - 0.7653668647301795) / fConst1));
	fConst4 = (2 * (1 - (1.0 / faustpower<2>(fConst1))));
	fConst5 = (1 + ((0.7653668647301795 + fConst2) / fConst1));
	fConst6 = (1.0 / fConst5);
	fConst7 = (1 + ((fConst2 - 1.8477590650225735) / fConst1));
	fConst8 = (1.0 / (1 + ((fConst2 + 1.8477590650225735) / fConst1)));
	fConst9 = (973.8937226128359 / fConst0);
	fConst10 = (1 - fConst9);
	fConst11 = (1.0 / (1 + fConst9));
	fConst12 = (0.9302847925323914 / fConst5);
	fConst13 = (1.0 / tan((270.1769682087222 / fConst0)));
	fConst14 = (1 + fConst13);
	fConst15 = (0 - ((1 - fConst13) / fConst14));
	fConst16 = (0.027 / fConst14);
	fConst17 = (1.0 / tan((97.38937226128358 / fConst0)));
	fConst18 = (0 - fConst17);
	fConst19 = (1 + fConst17);
	fConst20 = (0.025 / fConst19);
	fConst21 = (0 - ((1 - fConst17) / fConst19));
	fConst22 = (1.0 / tan((414.6902302738527 / fConst0)));
	fConst23 = (1 + fConst22);
	fConst24 = (0 - ((1 - fConst22) / fConst23));
	fConst25 = (0.015 / fConst23);
	fConst26 = (1.0 / tan((20517.741620594938 / fConst0)));
	fConst27 = (1 + fConst26);
	fConst28 = (1.0 / fConst27);
	fConst29 = (0 - ((1 - fConst26) / fConst27));
	fConst30 = (1.0 / tan((609.4689747964198 / fConst0)));
	fConst31 = (1 + fConst30);
	fConst32 = (0 - ((1 - fConst30) / fConst31));
	fConst33 = (0.0082 / fConst31);
	fConst34 = tan((942.4777960769379 / fConst0));
	fConst35 = (1.0 / fConst34);
	fConst36 = (1 + ((fConst35 - 1.0000000000000004) / fConst34));
	fConst37 = (1.0 / faustpower<2>(fConst34));
	fConst38 = (2 * (1 - fConst37));
	fConst39 = (1.0 / (1 + ((1.0000000000000004 + fConst35) / fConst34)));
	fConst40 = tan((3769.9111843077517 / fConst0));
	fConst41 = (1.0 / fConst40);
	fConst42 = (1 + ((fConst41 - 1.0000000000000004) / fConst40));
	fConst43 = (1.0 / faustpower<2>(fConst40));
	fConst44 = (2 * (1 - fConst43));
	fConst45 = (1 + ((1.0000000000000004 + fConst41) / fConst40));
	fConst46 = (1.0 / fConst45);
	fConst47 = tan((10053.096491487338 / fConst0));
	fConst48 = (1.0 / faustpower<2>(fConst47));
	fConst49 = (2 * (1 - fConst48));
	fConst50 = (1.0 / fConst47);
	fConst51 = (1 + ((fConst50 - 1.0000000000000004) / fConst47));
	fConst52 = (1 + ((1.0000000000000004 + fConst50) / fConst47));
	fConst53 = (1.0 / fConst52);
	fConst54 = tan((47123.8898038469 / fConst0));
	fConst55 = (2 * (1 - (1.0 / faustpower<2>(fConst54))));
	fConst56 = (1.0 / fConst54);
	fConst57 = (1 + ((fConst56 - 1.414213562373095) / fConst54));
	fConst58 = (1 + ((1.414213562373095 + fConst56) / fConst54));
	fConst59 = (1.0 / fConst58);
	iConst60 = int((int((0.1111111111111111 * fConst0)) & 65535));
	fConst61 = (0.009000000000000008 / fConst0);
	fConst62 = (1.0 / (fConst19 * fConst58));
	fConst63 = (1 + fConst50);
	fConst64 = (1.0 / fConst63);
	fConst65 = (0 - ((1 - fConst50) / fConst63));
	fConst66 = (1 + fConst41);
	fConst67 = (1.0 / (fConst66 * fConst52));
	fConst68 = (0 - ((1 - fConst41) / fConst66));
	fConst69 = (1 + fConst35);
	fConst70 = (1.0 / (fConst69 * fConst45));
	fConst71 = (0 - ((1 - fConst35) / fConst69));
	fConst72 = (1 + ((fConst35 - 1.0) / fConst34));
	fConst73 = (1.0 / (1 + ((1.0 + fConst35) / fConst34)));
	fConst74 = (1 + ((fConst41 - 1.0) / fConst40));
	fConst75 = (1.0 / (1 + ((1.0 + fConst41) / fConst40)));
	fConst76 = (0 - fConst50);
	fConst77 = (2 * (0 - fConst48));
	fConst78 = (0 - fConst35);
	fConst79 = (2 * (0 - fConst37));
	fConst80 = (0 - fConst41);
	fConst81 = (2 * (0 - fConst43));
	fConst82 = (0.0041 / fConst27);
	IOTA = 0;
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
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider0))));
	double 	fSlow1 = (1.000000000000001e-05 * double(fslider1));
	double 	fSlow2 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider2))));
	double 	fSlow3 = double(fslider3);
	double 	fSlow4 = (1.25 * fSlow3);
	double 	fSlow5 = (fConst39 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow6 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow7 = (fConst39 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow8 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow9 = (2 * (fSlow3 - 0.5));
	double 	fSlow10 = (1 - max((double)0, (0 - fSlow9)));
	double 	fSlow11 = (0.024937655860349125 * (1 - max((double)0, fSlow9)));
	for (int i=0; i<ReCount; i++) {
		double fTemp0 = (0.5 * fRec0[1]);
		double fTemp1 = (fTemp0 + (0.4 * fRec2[1]));
		double fTemp2 = ((0.3 * fRec4[1]) + fTemp1);
		fRec12[0] = (fSlow0 + (0.999 * fRec12[1]));
		fRec14[0] = (fSlow1 + (0.999 * fRec14[1]));
		double fTemp3 = (double)buf[i];
		fVec0[0] = fTemp3;
		fRec33[0] = (fConst11 * ((fVec0[0] + (fConst10 * fRec33[1])) - fVec0[1]));
		fRec32[0] = (fConst11 * (((fConst10 * fRec32[1]) + fRec33[0]) - fRec33[1]));
		fRec31[0] = (fRec32[0] - (fConst8 * ((fConst7 * fRec31[2]) + (fConst4 * fRec31[1]))));
		fRec30[0] = ((fConst8 * (fRec31[0] + (fRec31[2] + (2 * fRec31[1])))) - (fConst6 * ((fConst4 * fRec30[1]) + (fConst3 * fRec30[2]))));
		fRec34[0] = (fSlow2 + (0.999 * fRec34[1]));
		double fTemp4 = (fRec34[0] * (fRec30[0] + (fRec30[2] + (2 * fRec30[1]))));
		fVec1[0] = fTemp4;
		fRec29[0] = ((fConst12 * (fVec1[0] + fVec1[1])) - (0.8605695850647829 * fRec29[1]));
		fRec28[0] = (fRec29[0] - ((1.8405051250752198 * fRec28[1]) + (0.8612942439318627 * fRec28[2])));
		fRec35[0] = ((fConst16 * (fRec27[1] + fRec27[2])) + (fConst15 * fRec35[1]));
		fRec27[0] = (Ftube(TUBE_TABLE_12AT7_68k, ((fRec35[0] + (0.9254498422517706 * (fRec28[0] + (fRec28[2] + (2.0 * fRec28[1]))))) - 2.617753)) - 153.04618518518518);
		fRec26[0] = ((fConst21 * fRec26[1]) + (fConst20 * ((fConst17 * fRec27[0]) + (fConst18 * fRec27[1]))));
		fRec39[0] = ((0.9302847925323914 * (fRec25[1] + fRec25[2])) - (0.8605695850647829 * fRec39[1]));
		fRec38[0] = (fRec39[0] - ((1.8405051250752198 * fRec38[1]) + (0.8612942439318627 * fRec38[2])));
		fRec40[0] = ((fConst25 * (fRec37[1] + fRec37[2])) + (fConst24 * fRec40[1]));
		fRec37[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec40[0] + (0.9254498422517706 * (fRec38[0] + (fRec38[2] + (2.0 * fRec38[1]))))) - 1.887333)) - 124.17779999999999);
		fRec36[0] = ((fConst21 * fRec36[1]) + (fConst20 * ((fConst17 * fRec37[0]) + (fConst18 * fRec37[1]))));
		fRec25[0] = ((0.6 * fRec36[0]) + fRec26[0]);
		fRec24[0] = ((fConst29 * fRec24[1]) + (fConst28 * (fRec25[1] + fRec25[0])));
		fRec23[0] = ((0.9302847925323914 * (fRec24[1] + fRec24[0])) - (0.8605695850647829 * fRec23[1]));
		fRec22[0] = (fRec23[0] - ((1.8405051250752198 * fRec22[1]) + (0.8612942439318627 * fRec22[2])));
		fRec41[0] = ((fConst25 * (fRec21[1] + fRec21[2])) + (fConst24 * fRec41[1]));
		fRec21[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec41[0] + (0.9254498422517706 * (fRec22[0] + (fRec22[2] + (2.0 * fRec22[1]))))) - 1.887333)) - 124.17779999999999);
		fRec20[0] = ((fConst21 * fRec20[1]) + (fConst20 * ((fConst17 * fRec21[0]) + (fConst18 * fRec21[1]))));
		fRec45[0] = ((0.9302847925323914 * (fRec19[1] + fRec19[2])) - (0.8605695850647829 * fRec45[1]));
		fRec44[0] = (fRec45[0] - ((1.8405051250752198 * fRec44[1]) + (0.8612942439318627 * fRec44[2])));
		fRec46[0] = ((fConst33 * (fRec43[1] + fRec43[2])) + (fConst32 * fRec46[1]));
		fRec43[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec46[0] + (0.9254498422517706 * (fRec44[0] + (fRec44[2] + (2.0 * fRec44[1]))))) - 1.256962)) - 96.7119512195122);
		fRec42[0] = ((fConst21 * fRec42[1]) + (fConst20 * ((fConst17 * fRec43[0]) + (fConst18 * fRec43[1]))));
		fRec19[0] = ((0.6 * fRec42[0]) + fRec20[0]);
		fRec18[0] = ((0.9302847925323914 * (fRec19[1] + fRec19[0])) - (0.8605695850647829 * fRec18[1]));
		fRec17[0] = (fRec18[0] - ((1.8405051250752198 * fRec17[1]) + (0.8612942439318627 * fRec17[2])));
		fRec47[0] = ((fConst33 * (fRec16[1] + fRec16[2])) + (fConst32 * fRec47[1]));
		fRec16[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec47[0] + (0.9254498422517706 * (fRec17[0] + (fRec17[2] + (2.0 * fRec17[1]))))) - 1.256962)) - 96.7119512195122);
		fRec15[0] = ((fConst21 * fRec15[1]) + (fConst20 * ((fConst17 * fRec16[0]) + (fConst18 * fRec16[1]))));
		double fTemp5 = (fRec15[0] * (1 - fRec14[0]));
		double fTemp6 = (fRec14[0] * fRec15[0]);
		double fTemp7 = fabs(fTemp6);
		fRec59[0] = ((0.9999 * fRec59[1]) + (9.999999999998899e-05 * fTemp7));
		double fTemp8 = max(fRec59[0], fTemp7);
		fVec2[IOTA&32767] = fTemp8;
		fRec58[0] = ((fVec2[IOTA&32767] + fRec58[1]) - fVec2[(IOTA-iConst60)&32767]);
		fRec57[0] = ((0.999 * fRec57[1]) + (fConst61 * fRec58[0]));
		double fTemp9 = max(-1.0, min(-0.01, (fVec2[IOTA&32767] - (1.0 + (1.02 * fRec57[0])))));
		double fTemp10 = (0 - fTemp9);
		double fTemp11 = (40.1 * fTemp10);
		double fTemp12 = max((double)-600, fTemp11);
		double fTemp13 = (0 - fTemp12);
		double fTemp14 = (fTemp6 - fTemp9);
		double fTemp15 = (40.1 * fTemp14);
		double fTemp16 = max((double)-600, fTemp15);
		double fTemp17 = (0 - fTemp16);
		double fTemp18 = (((int((fabs(fTemp15) > 0.0001)))?((int((fTemp16 < -50)))?(fTemp17 * exp(fTemp16)):(fTemp16 / (1 - exp(fTemp17)))):(1 + (fTemp14 * (20.05 + (134.00083333333336 * fTemp14))))) - ((int((fabs(fTemp11) > 0.0001)))?((int((fTemp12 < -50)))?(fTemp13 * exp(fTemp12)):(fTemp12 / (1 - exp(fTemp13)))):(1 + (fTemp10 * (20.05 + (134.00083333333336 * fTemp10))))));
		fRec56[0] = ((0.024937655860349125 * fTemp18) - (fConst59 * ((fConst57 * fRec56[2]) + (fConst55 * fRec56[1]))));
		double fTemp19 = (fRec56[0] + (fRec56[2] + (2 * fRec56[1])));
		fVec3[0] = fTemp19;
		fRec55[0] = ((fConst21 * fRec55[1]) + (fConst62 * ((fConst17 * fVec3[0]) + (fConst18 * fVec3[1]))));
		fRec54[0] = ((fConst65 * fRec54[1]) + (fConst64 * (fRec55[1] + fRec55[0])));
		fRec53[0] = (fRec54[0] - (fConst53 * ((fConst51 * fRec53[2]) + (fConst49 * fRec53[1]))));
		double fTemp20 = (fRec53[0] + (fRec53[2] + (2 * fRec53[1])));
		fVec4[0] = fTemp20;
		fRec52[0] = ((fConst68 * fRec52[1]) + (fConst67 * (fVec4[0] + fVec4[1])));
		fRec51[0] = (fRec52[0] - (fConst46 * ((fConst44 * fRec51[1]) + (fConst42 * fRec51[2]))));
		double fTemp21 = (fRec51[0] + (fRec51[2] + (2 * fRec51[1])));
		fVec5[0] = fTemp21;
		fRec50[0] = ((fConst71 * fRec50[1]) + (fConst70 * (fVec5[0] + fVec5[1])));
		fRec49[0] = (fRec50[0] - (fConst39 * ((fConst38 * fRec49[1]) + (fConst36 * fRec49[2]))));
		double fTemp22 = max((double)-1, min((double)1, (fSlow5 * (fRec49[0] + (fRec49[2] + (2 * fRec49[1]))))));
		double fTemp23 = (fConst38 * fRec60[1]);
		double fTemp24 = (fConst44 * fRec61[1]);
		fRec63[0] = ((fConst65 * fRec63[1]) + (fConst64 * ((fConst50 * fRec55[0]) + (fConst76 * fRec55[1]))));
		fRec62[0] = (fRec63[0] - (fConst53 * ((fConst51 * fRec62[2]) + (fConst49 * fRec62[1]))));
		fRec61[0] = ((fConst53 * ((fConst77 * fRec62[1]) + (fConst48 * (fRec62[2] + fRec62[0])))) - (fConst75 * ((fConst74 * fRec61[2]) + fTemp24)));
		fRec60[0] = ((fRec61[2] + (fConst75 * (fTemp24 + (fConst74 * fRec61[0])))) - (fConst73 * ((fConst72 * fRec60[2]) + fTemp23)));
		double fTemp25 = max((double)-1, min((double)1, (fSlow6 * (fRec60[2] + (fConst73 * (fTemp23 + (fConst72 * fRec60[0])))))));
		fRec65[0] = ((fConst71 * fRec65[1]) + (fConst70 * ((fConst35 * fVec5[0]) + (fConst78 * fVec5[1]))));
		fRec64[0] = (fRec65[0] - (fConst39 * ((fConst38 * fRec64[1]) + (fConst36 * fRec64[2]))));
		double fTemp26 = max((double)-1, min((double)1, (fSlow7 * ((fConst79 * fRec64[1]) + (fConst37 * (fRec64[2] + fRec64[0]))))));
		double fTemp27 = (fConst38 * fRec66[1]);
		fRec68[0] = ((fConst68 * fRec68[1]) + (fConst67 * ((fConst41 * fVec4[0]) + (fConst80 * fVec4[1]))));
		fRec67[0] = (fRec68[0] - (fConst46 * ((fConst44 * fRec67[1]) + (fConst42 * fRec67[2]))));
		fRec66[0] = ((fConst46 * ((fConst81 * fRec67[1]) + (fConst43 * (fRec67[2] + fRec67[0])))) - (fConst73 * ((fConst72 * fRec66[2]) + fTemp27)));
		double fTemp28 = max((double)-1, min((double)1, (fSlow8 * (fRec66[2] + (fConst73 * (fTemp27 + (fConst72 * fRec66[0])))))));
		double fTemp29 = ((1.584893192 * ((0.8413951417869425 * (fTemp28 * (1 - (0.3333333333333333 * faustpower<2>(fTemp28))))) + ((fTemp26 * (1 - (0.3333333333333333 * faustpower<2>(fTemp26)))) + (fTemp25 * (1 - (0.3333333333333333 * faustpower<2>(fTemp25))))))) + (1.2589412 * (fTemp22 * (1 - (0.3333333333333333 * faustpower<2>(fTemp22))))));
		fVec6[0] = fTemp29;
		fRec48[0] = ((fConst29 * fRec48[1]) + (fConst28 * (fVec6[0] + fVec6[1])));
		double fTemp30 = ((fSlow11 * fTemp18) + ((fSlow10 * fRec48[0]) + (fTemp5 * (1 + (fSlow4 * (3 - (4 * fabs(fTemp5))))))));
		fVec7[0] = fTemp30;
		fRec13[0] = ((fConst29 * fRec13[1]) + (fConst28 * (fVec7[0] + fVec7[1])));
		double fTemp31 = (fRec13[0] * fRec12[0]);
		fVec8[0] = fTemp31;
		fRec11[0] = ((0.9302847925323914 * (fVec8[0] + fVec8[1])) - (0.8605695850647829 * fRec11[1]));
		fRec10[0] = (fRec11[0] - ((1.8405051250752198 * fRec10[1]) + (0.8612942439318627 * fRec10[2])));
		double fTemp32 = (0.9254498422517706 * (fRec10[0] + (fRec10[2] + (2.0 * fRec10[1]))));
		fRec69[0] = ((fConst82 * (fRec9[1] + fRec9[2])) + (fConst29 * fRec69[1]));
		fRec9[0] = (Ftube(TUBE_TABLE_6V6_68k, ((fRec69[0] + fTemp32) - 0.664541)) - 87.91682926829267);
		fRec8[0] = ((fConst21 * fRec8[1]) + (fConst20 * ((fConst17 * fRec9[0]) + (fConst18 * fRec9[1]))));
		double fTemp33 = max(-0.75, fRec8[0]);
		fRec72[0] = ((fConst82 * (fRec71[1] + fRec71[2])) + (fConst29 * fRec72[1]));
		fRec71[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec72[0] + fTemp32) - 0.659761)) - 89.08268292682925);
		fRec70[0] = ((fConst21 * fRec70[1]) + (fConst20 * ((fConst17 * fRec71[0]) + (fConst18 * fRec71[1]))));
		double fTemp34 = min(0.7, fRec70[0]);
		double fTemp35 = ((fTemp34 + ((0.2 * fRec6[1]) + fTemp33)) - fTemp2);
		fRec6[0] = fTemp35;
		double 	fRec7 = (0 - (0.2 * fTemp35));
		fRec4[0] = (fRec6[1] + fRec7);
		double fTemp36 = (fTemp33 + fTemp34);
		double 	fRec5 = (0.3 * (fTemp36 - fTemp2));
		fRec2[0] = (fRec4[1] + fRec5);
		double 	fRec3 = (0.4 * (fTemp36 - fTemp1));
		fRec0[0] = (fRec2[1] + fRec3);
		double 	fRec1 = (0.5 * (fTemp36 - fTemp0));
		buf[i] = (FAUSTFLOAT)(fRec0[1] + fRec1);
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
		fRec69[1] = fRec69[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec8[1] = fVec8[0];
		fRec13[1] = fRec13[0];
		fVec7[1] = fVec7[0];
		fRec48[1] = fRec48[0];
		fVec6[1] = fVec6[0];
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
		fVec5[1] = fVec5[0];
		fRec51[2] = fRec51[1]; fRec51[1] = fRec51[0];
		fRec52[1] = fRec52[0];
		fVec4[1] = fVec4[0];
		fRec53[2] = fRec53[1]; fRec53[1] = fRec53[0];
		fRec54[1] = fRec54[0];
		fRec55[1] = fRec55[0];
		fVec3[1] = fVec3[0];
		fRec56[2] = fRec56[1]; fRec56[1] = fRec56[0];
		fRec57[1] = fRec57[0];
		fRec58[1] = fRec58[0];
		IOTA = IOTA+1;
		fRec59[1] = fRec59[0];
		fRec15[1] = fRec15[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec47[1] = fRec47[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec42[1] = fRec42[0];
		fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
		fRec46[1] = fRec46[0];
		fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
		fRec45[1] = fRec45[0];
		fRec20[1] = fRec20[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec41[1] = fRec41[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec36[1] = fRec36[0];
		fRec37[2] = fRec37[1]; fRec37[1] = fRec37[0];
		fRec40[1] = fRec40[0];
		fRec38[2] = fRec38[1]; fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec26[1] = fRec26[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec35[1] = fRec35[0];
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

} // end namespace gxamp16
