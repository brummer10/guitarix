// generated from file '../src/faust/gxamp15.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp15 {

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
	double 	fRec4[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec5[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec7[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec15[2];
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fRec16[2];
	double 	fRec14[3];
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fRec13[2];
	double 	fConst19;
	double 	fRec12[2];
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fRec17[2];
	double 	fRec11[3];
	double 	fRec10[2];
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fRec18[2];
	double 	fRec9[3];
	double 	fRec8[2];
	double 	fConst28;
	double 	fConst29;
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
	double 	fRec27[3];
	double 	fVec0[2];
	double 	fConst54;
	double 	fRec26[2];
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fRec25[2];
	double 	fRec24[3];
	double 	fVec1[2];
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fVec2[2];
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fRec21[2];
	double 	fRec20[3];
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fRec30[2];
	double 	fRec29[3];
	double 	fConst67;
	double 	fRec28[3];
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;
	double 	fRec34[2];
	double 	fRec33[3];
	double 	fConst71;
	double 	fRec32[3];
	double 	fRec31[3];
	double 	fConst72;
	double 	fRec36[2];
	double 	fRec35[3];
	double 	fConst73;
	double 	fVec3[2];
	double 	fRec19[2];
	double 	fVec4[2];
	double 	fRec6[2];
	double 	fRec3[3];
	double 	fRec2[2];
	double 	fRec39[2];
	double 	fRec38[3];
	double 	fRec37[2];
	double 	fVec5[2];
	double 	fConst74;
	double 	fConst75;
	double 	fConst76;
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
	id = "pre 12AT7/ master 6V6";
	name = N_("pre 12AT7/ master 6V6");
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
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<3; i++) fRec33[i] = 0;
	for (int i=0; i<3; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<3; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<3; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
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
	fConst8 = (0.0082 / fConst7);
	fConst9 = (0 - ((1 - fConst6) / fConst7));
	fConst10 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst11 = (1 + fConst10);
	fConst12 = (0.027 / fConst11);
	fConst13 = (0 - ((1 - fConst10) / fConst11));
	fConst14 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst15 = (0 - fConst14);
	fConst16 = (1 + fConst14);
	fConst17 = (0.025 / fConst16);
	fConst18 = (0 - ((1 - fConst14) / fConst16));
	fConst19 = (1.0 / fConst7);
	fConst20 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst21 = (1 + fConst20);
	fConst22 = (0.015 / fConst21);
	fConst23 = (0 - ((1 - fConst20) / fConst21));
	fConst24 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst25 = (1 + fConst24);
	fConst26 = (0.0082 / fConst25);
	fConst27 = (0 - ((1 - fConst24) / fConst25));
	fConst28 = tan((942.4777960769379 / double(iConst0)));
	fConst29 = (1.0 / faustpower<2>(fConst28));
	fConst30 = (2 * (1 - fConst29));
	fConst31 = (1.0 / fConst28);
	fConst32 = (1 + ((fConst31 - 1.0000000000000004) / fConst28));
	fConst33 = (1.0 / (1 + ((1.0000000000000004 + fConst31) / fConst28)));
	fConst34 = tan((3769.9111843077517 / double(iConst0)));
	fConst35 = (1.0 / faustpower<2>(fConst34));
	fConst36 = (2 * (1 - fConst35));
	fConst37 = (1.0 / fConst34);
	fConst38 = (1 + ((fConst37 - 1.0000000000000004) / fConst34));
	fConst39 = (1 + ((1.0000000000000004 + fConst37) / fConst34));
	fConst40 = (1.0 / fConst39);
	fConst41 = tan((10053.096491487338 / double(iConst0)));
	fConst42 = (1.0 / faustpower<2>(fConst41));
	fConst43 = (2 * (1 - fConst42));
	fConst44 = (1.0 / fConst41);
	fConst45 = (1 + ((fConst44 - 1.0000000000000004) / fConst41));
	fConst46 = (1 + ((1.0000000000000004 + fConst44) / fConst41));
	fConst47 = (1.0 / fConst46);
	fConst48 = tan((47123.8898038469 / double(iConst0)));
	fConst49 = (2 * (1 - (1.0 / faustpower<2>(fConst48))));
	fConst50 = (1.0 / fConst48);
	fConst51 = (1 + ((fConst50 - 1.414213562373095) / fConst48));
	fConst52 = (1 + ((1.414213562373095 + fConst50) / fConst48));
	fConst53 = (1.0 / fConst52);
	fConst54 = (1.0 / (fConst16 * fConst52));
	fConst55 = (1 + fConst44);
	fConst56 = (1.0 / fConst55);
	fConst57 = (0 - ((1 - fConst44) / fConst55));
	fConst58 = (1 + fConst37);
	fConst59 = (1.0 / (fConst58 * fConst46));
	fConst60 = (0 - ((1 - fConst37) / fConst58));
	fConst61 = (1 + fConst31);
	fConst62 = (1.0 / (fConst61 * fConst39));
	fConst63 = (0 - ((1 - fConst31) / fConst61));
	fConst64 = (1 + ((fConst31 - 1.0) / fConst28));
	fConst65 = (1.0 / (1 + ((1.0 + fConst31) / fConst28)));
	fConst66 = (0 - fConst37);
	fConst67 = (2 * (0 - fConst35));
	fConst68 = (1 + ((fConst37 - 1.0) / fConst34));
	fConst69 = (1.0 / (1 + ((1.0 + fConst37) / fConst34)));
	fConst70 = (0 - fConst44);
	fConst71 = (2 * (0 - fConst42));
	fConst72 = (0 - fConst31);
	fConst73 = (2 * (0 - fConst29));
	fConst74 = (1 + fConst3);
	fConst75 = (1.0 / fConst74);
	fConst76 = (0 - ((1 - fConst3) / fConst74));
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
	double 	fSlow2 = double(fslider2);
	double 	fSlow3 = (2 * (fSlow2 - 0.5));
	double 	fSlow4 = (1 - max((double)0, fSlow3));
	double 	fSlow5 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider3))));
	double 	fSlow6 = (1.25 * fSlow2);
	double 	fSlow7 = (fConst33 * pow(1e+01,(0.9 * fSlow2)));
	double 	fSlow8 = pow(1e+01,(1.2 * fSlow2));
	double 	fSlow9 = pow(1e+01,(0.8 * fSlow2));
	double 	fSlow10 = (fConst33 * pow(1e+01,(2 * fSlow2)));
	double 	fSlow11 = (1 - max((double)0, (0 - fSlow3)));
	for (int i=0; i<ReCount; i++) {
		fRec4[0] = ((fConst9 * fRec4[1]) + (fConst8 * (fRec3[1] + fRec3[2])));
		fRec5[0] = ((0.999 * fRec5[1]) + fSlow0);
		fRec7[0] = (fSlow1 + (0.999 * fRec7[1]));
		double fTemp0 = (1 - fRec7[0]);
		fRec15[0] = ((0.999 * fRec15[1]) + fSlow5);
		fRec16[0] = ((fConst13 * fRec16[1]) + (fConst12 * (fRec14[1] + fRec14[2])));
		fRec14[0] = (Ftube(TUBE_TABLE_12AT7_68k, ((fRec16[0] + ((double)buf[i] * fRec15[0])) - 2.617753)) - 153.04618518518518);
		fRec13[0] = ((fConst18 * fRec13[1]) + (fConst17 * ((fConst14 * fRec14[0]) + (fConst15 * fRec14[1]))));
		fRec12[0] = ((fConst9 * fRec12[1]) + (fConst19 * (fRec13[0] + fRec13[1])));
		fRec17[0] = ((fConst23 * fRec17[1]) + (fConst22 * (fRec11[1] + fRec11[2])));
		fRec11[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec17[0] + fRec12[0]) - 1.887332)) - 124.17786666666666);
		fRec10[0] = ((fConst18 * fRec10[1]) + (fConst17 * ((fConst14 * fRec11[0]) + (fConst15 * fRec11[1]))));
		fRec18[0] = ((fConst27 * fRec18[1]) + (fConst26 * (fRec9[1] + fRec9[2])));
		fRec9[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec18[0] + fRec10[0]) - 1.256962)) - 96.7119512195122);
		fRec8[0] = ((fConst18 * fRec8[1]) + (fConst17 * ((fConst14 * fRec9[0]) + (fConst15 * fRec9[1]))));
		fRec27[0] = ((fRec8[0] * fRec7[0]) - (fConst53 * ((fConst51 * fRec27[2]) + (fConst49 * fRec27[1]))));
		double fTemp1 = (fRec27[2] + (fRec27[0] + (2 * fRec27[1])));
		fVec0[0] = fTemp1;
		fRec26[0] = ((fConst18 * fRec26[1]) + (fConst54 * ((fConst14 * fVec0[0]) + (fConst15 * fVec0[1]))));
		fRec25[0] = ((fConst57 * fRec25[1]) + (fConst56 * (fRec26[0] + fRec26[1])));
		fRec24[0] = (fRec25[0] - (fConst47 * ((fConst45 * fRec24[2]) + (fConst43 * fRec24[1]))));
		double fTemp2 = (fRec24[2] + (fRec24[0] + (2 * fRec24[1])));
		fVec1[0] = fTemp2;
		fRec23[0] = ((fConst60 * fRec23[1]) + (fConst59 * (fVec1[0] + fVec1[1])));
		fRec22[0] = (fRec23[0] - (fConst40 * ((fConst38 * fRec22[2]) + (fConst36 * fRec22[1]))));
		double fTemp3 = (fRec22[2] + (fRec22[0] + (2 * fRec22[1])));
		fVec2[0] = fTemp3;
		fRec21[0] = ((fConst63 * fRec21[1]) + (fConst62 * (fVec2[0] + fVec2[1])));
		fRec20[0] = (fRec21[0] - (fConst33 * ((fConst32 * fRec20[2]) + (fConst30 * fRec20[1]))));
		double fTemp4 = max((double)-1, min((double)1, (fSlow7 * (fRec20[2] + (fRec20[0] + (2 * fRec20[1]))))));
		double fTemp5 = (fConst30 * fRec28[1]);
		fRec30[0] = ((fConst60 * fRec30[1]) + (fConst59 * ((fConst37 * fVec1[0]) + (fConst66 * fVec1[1]))));
		fRec29[0] = (fRec30[0] - (fConst40 * ((fConst38 * fRec29[2]) + (fConst36 * fRec29[1]))));
		fRec28[0] = ((fConst40 * (((fConst35 * fRec29[0]) + (fConst67 * fRec29[1])) + (fConst35 * fRec29[2]))) - (fConst65 * ((fConst64 * fRec28[2]) + fTemp5)));
		double fTemp6 = max((double)-1, min((double)1, (fSlow8 * (fRec28[2] + (fConst65 * (fTemp5 + (fConst64 * fRec28[0])))))));
		double fTemp7 = (fConst30 * fRec31[1]);
		double fTemp8 = (fConst36 * fRec32[1]);
		fRec34[0] = ((fConst57 * fRec34[1]) + (fConst56 * ((fConst44 * fRec26[0]) + (fConst70 * fRec26[1]))));
		fRec33[0] = (fRec34[0] - (fConst47 * ((fConst45 * fRec33[2]) + (fConst43 * fRec33[1]))));
		fRec32[0] = ((fConst47 * (((fConst42 * fRec33[0]) + (fConst71 * fRec33[1])) + (fConst42 * fRec33[2]))) - (fConst69 * ((fConst68 * fRec32[2]) + fTemp8)));
		fRec31[0] = ((fRec32[2] + (fConst69 * (fTemp8 + (fConst68 * fRec32[0])))) - (fConst65 * ((fConst64 * fRec31[2]) + fTemp7)));
		double fTemp9 = max((double)-1, min((double)1, (fSlow9 * (fRec31[2] + (fConst65 * (fTemp7 + (fConst64 * fRec31[0])))))));
		fRec36[0] = ((fConst63 * fRec36[1]) + (fConst62 * ((fConst31 * fVec2[0]) + (fConst72 * fVec2[1]))));
		fRec35[0] = (fRec36[0] - (fConst33 * ((fConst32 * fRec35[2]) + (fConst30 * fRec35[1]))));
		double fTemp10 = max((double)-1, min((double)1, (fSlow10 * (((fConst29 * fRec35[0]) + (fConst73 * fRec35[1])) + (fConst29 * fRec35[2])))));
		double fTemp11 = ((1.584893192 * ((fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10)))) + ((fTemp9 * (1 - (0.3333333333333333 * faustpower<2>(fTemp9)))) + (0.8413951417869425 * (fTemp6 * (1 - (0.3333333333333333 * faustpower<2>(fTemp6)))))))) + (1.2589412 * (fTemp4 * (1 - (0.3333333333333333 * faustpower<2>(fTemp4))))));
		fVec3[0] = fTemp11;
		fRec19[0] = ((fConst9 * fRec19[1]) + (fConst19 * (fVec3[0] + fVec3[1])));
		double fTemp12 = ((fSlow11 * fRec19[0]) + (fRec8[0] * ((fTemp0 * (1 + (fSlow6 * ((4 - (4 * fabs((fRec8[0] * fTemp0)))) - 1)))) + (fSlow4 * fRec7[0]))));
		fVec4[0] = fTemp12;
		fRec6[0] = ((fConst9 * fRec6[1]) + (fConst19 * (fVec4[0] + fVec4[1])));
		double fTemp13 = (fRec6[0] * fRec5[0]);
		fRec3[0] = (Ftube(TUBE_TABLE_6V6_68k, ((fTemp13 + fRec4[0]) - 1.13074)) - 112.10487804878048);
		fRec2[0] = ((fConst18 * fRec2[1]) + (fConst17 * ((fConst14 * fRec3[0]) + (fConst15 * fRec3[1]))));
		fRec39[0] = ((fConst9 * fRec39[1]) + (fConst8 * (fRec38[1] + fRec38[2])));
		fRec38[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec39[0] + fTemp13) - 1.130462)) - 112.13878048780487);
		fRec37[0] = ((fConst18 * fRec37[1]) + (fConst17 * ((fConst14 * fRec38[0]) + (fConst15 * fRec38[1]))));
		double fTemp14 = (fRec37[0] + fRec2[0]);
		fVec5[0] = fTemp14;
		fRec1[0] = ((fConst76 * fRec1[1]) + (fConst75 * (fVec5[0] + fVec5[1])));
		fRec0[0] = (fRec1[0] - (fConst5 * ((fConst4 * fRec0[2]) + (fConst2 * fRec0[1]))));
		buf[i] = (FAUSTFLOAT)(fConst5 * (fRec0[2] + (fRec0[0] + (2 * fRec0[1]))));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fVec5[1] = fVec5[0];
		fRec37[1] = fRec37[0];
		fRec38[2] = fRec38[1]; fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec6[1] = fRec6[0];
		fVec4[1] = fVec4[0];
		fRec19[1] = fRec19[0];
		fVec3[1] = fVec3[0];
		fRec35[2] = fRec35[1]; fRec35[1] = fRec35[0];
		fRec36[1] = fRec36[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec34[1] = fRec34[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fVec2[1] = fVec2[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fVec1[1] = fVec1[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fVec0[1] = fVec0[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec18[1] = fRec18[0];
		fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec17[1] = fRec17[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec16[1] = fRec16[0];
		fRec15[1] = fRec15[0];
		fRec7[1] = fRec7[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
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
	fslider2_ = reg.registerVar("gxdistortion.drive","","SA","",&fslider2, 0.35, 0.0, 1.0, 0.01);
	fslider1_ = reg.registerVar("gxdistortion.wet_dry","","SA","",&fslider1, 1e+02, 0.0, 1e+02, 1.0);
	fslider3_ = reg.registerVar("amp2.stage1.Pregain","","SA","",&fslider3, -6.0, -2e+01, 2e+01, 0.1);
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

} // end namespace gxamp15
