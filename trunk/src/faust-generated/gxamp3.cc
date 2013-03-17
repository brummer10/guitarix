// generated from file '../src/faust/gxamp3.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp3 {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec7[2];
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
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fVec0[2];
	double 	fConst37;
	double 	fConst38;
	double 	fRec16[2];
	double 	fConst39;
	double 	fRec15[2];
	double 	fRec14[3];
	double 	fVec1[2];
	double 	fConst40;
	double 	fConst41;
	double 	fRec13[2];
	double 	fRec12[3];
	double 	fConst42;
	double 	fRec11[3];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fRec22[2];
	double 	fRec21[3];
	double 	fVec2[2];
	double 	fConst47;
	double 	fConst48;
	double 	fRec20[2];
	double 	fRec19[3];
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fRec26[2];
	double 	fRec25[3];
	double 	fConst53;
	double 	fRec24[3];
	double 	fRec23[3];
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fVec3[2];
	double 	fConst54;
	double 	fRec10[2];
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fRec29[2];
	double 	fRec9[3];
	double 	fConst59;
	double 	fRec8[2];
	double 	fVec4[2];
	double 	fConst60;
	double 	fRec6[2];
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fRec30[2];
	double 	fRec5[3];
	double 	fRec4[2];
	double 	fVec5[2];
	double 	fRec3[2];
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fRec31[2];
	double 	fRec2[3];
	double 	fRec1[2];
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
	id = "12AU7";
	name = N_("12AU7");
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / tan((97.38937226128358 / iConst0)));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0 / tan((20517.741620594938 / iConst0)));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = tan((942.4777960769379 / iConst0));
	fConst8 = (1.0 / faustpower<2>(fConst7));
	fConst9 = (2 * (1 - fConst8));
	fConst10 = (1.0 / fConst7);
	fConst11 = (1 + ((fConst10 - 1.0) / fConst7));
	fConst12 = (1.0 / (1 + ((1.0 + fConst10) / fConst7)));
	fConst13 = tan((3769.9111843077517 / iConst0));
	fConst14 = (1.0 / faustpower<2>(fConst13));
	fConst15 = (2 * (1 - fConst14));
	fConst16 = (1.0 / fConst13);
	fConst17 = (1 + ((fConst16 - 1.0000000000000004) / fConst13));
	fConst18 = (1 + ((fConst16 + 1.0000000000000004) / fConst13));
	fConst19 = (1.0 / fConst18);
	fConst20 = (1 + fConst16);
	fConst21 = (0 - ((1 - fConst16) / fConst20));
	fConst22 = tan((10053.096491487338 / iConst0));
	fConst23 = (1.0 / faustpower<2>(fConst22));
	fConst24 = (2 * (1 - fConst23));
	fConst25 = (1.0 / fConst22);
	fConst26 = (1 + ((fConst25 - 1.0000000000000004) / fConst22));
	fConst27 = (1 + ((1.0000000000000004 + fConst25) / fConst22));
	fConst28 = (1.0 / fConst27);
	fConst29 = (1 + fConst25);
	fConst30 = (0 - ((1 - fConst25) / fConst29));
	fConst31 = tan((47123.8898038469 / iConst0));
	fConst32 = (2 * (1 - (1.0 / faustpower<2>(fConst31))));
	fConst33 = (1.0 / fConst31);
	fConst34 = (1 + ((fConst33 - 1.414213562373095) / fConst31));
	fConst35 = (1 + ((1.414213562373095 + fConst33) / fConst31));
	fConst36 = (1.0 / fConst35);
	fConst37 = (0 - fConst1);
	fConst38 = (1.0 / (fConst2 * fConst35));
	fConst39 = (1.0 / fConst29);
	fConst40 = (0 - fConst16);
	fConst41 = (1.0 / (fConst20 * fConst27));
	fConst42 = (2 * (0 - fConst14));
	fConst43 = (1 + ((fConst10 - 1.0000000000000004) / fConst7));
	fConst44 = (1.0 / (1 + ((fConst10 + 1.0000000000000004) / fConst7)));
	fConst45 = (1 + fConst10);
	fConst46 = (0 - ((1 - fConst10) / fConst45));
	fConst47 = (0 - fConst10);
	fConst48 = (1.0 / (fConst45 * fConst18));
	fConst49 = (2 * (0 - fConst8));
	fConst50 = (1 + ((fConst16 - 1.0) / fConst13));
	fConst51 = (1.0 / (1 + ((1.0 + fConst16) / fConst13)));
	fConst52 = (0 - fConst25);
	fConst53 = (2 * (0 - fConst23));
	fConst54 = (1.0 / fConst5);
	fConst55 = (1.0 / tan((270.1769682087222 / iConst0)));
	fConst56 = (1 + fConst55);
	fConst57 = (0 - ((1 - fConst55) / fConst56));
	fConst58 = (0.027 / fConst56);
	fConst59 = (0.025 / fConst2);
	fConst60 = (2.0 / fConst5);
	fConst61 = (1.0 / tan((414.6902302738527 / iConst0)));
	fConst62 = (1 + fConst61);
	fConst63 = (0 - ((1 - fConst61) / fConst62));
	fConst64 = (0.015 / fConst62);
	fConst65 = (1.0 / tan((609.4689747964198 / iConst0)));
	fConst66 = (1 + fConst65);
	fConst67 = (0 - ((1 - fConst65) / fConst66));
	fConst68 = (0.0082 / fConst66);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

inline void Dsp::compute(int count, float *input0, float *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * fslider1)));
	double 	fSlow2 = (1.000000000000001e-05 * fslider2);
	double 	fSlow3 = fslider3;
	double 	fSlow4 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow5 = (fConst44 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow6 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow7 = (fConst44 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow8 = (2 * (fSlow3 - 0.5));
	double 	fSlow9 = (1 - max(0, (0 - fSlow8)));
	double 	fSlow10 = (1.25 * fSlow3);
	double 	fSlow11 = (1 - max(0, fSlow8));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec7[0] = (fSlow1 + (0.999 * fRec7[1]));
		double fTemp0 = (fConst9 * fRec11[1]);
		fRec18[0] = (fSlow2 + (0.999 * fRec18[1]));
		double fTemp1 = (double)input0[i];
		fRec17[0] = ((fTemp1 * fRec18[0]) - (fConst36 * ((fConst34 * fRec17[2]) + (fConst32 * fRec17[1]))));
		double fTemp2 = (fRec17[2] + (fRec17[0] + (2 * fRec17[1])));
		fVec0[0] = fTemp2;
		fRec16[0] = ((fConst38 * ((fConst37 * fVec0[1]) + (fConst1 * fVec0[0]))) + (fConst3 * fRec16[1]));
		fRec15[0] = ((fConst39 * (fRec16[0] + fRec16[1])) + (fConst30 * fRec15[1]));
		fRec14[0] = (fRec15[0] - (fConst28 * ((fConst26 * fRec14[2]) + (fConst24 * fRec14[1]))));
		double fTemp3 = (fRec14[2] + (fRec14[0] + (2 * fRec14[1])));
		fVec1[0] = fTemp3;
		fRec13[0] = ((fConst41 * ((fConst40 * fVec1[1]) + (fConst16 * fVec1[0]))) + (fConst21 * fRec13[1]));
		fRec12[0] = (fRec13[0] - (fConst19 * ((fConst17 * fRec12[2]) + (fConst15 * fRec12[1]))));
		fRec11[0] = ((fConst19 * (((fConst14 * fRec12[0]) + (fConst42 * fRec12[1])) + (fConst14 * fRec12[2]))) - (fConst12 * ((fConst11 * fRec11[2]) + fTemp0)));
		double fTemp4 = max(-1, min(1, (fSlow4 * (fRec11[2] + (fConst12 * (fTemp0 + (fConst11 * fRec11[0])))))));
		fRec22[0] = ((fConst41 * (fVec1[0] + fVec1[1])) + (fConst21 * fRec22[1]));
		fRec21[0] = (fRec22[0] - (fConst19 * ((fConst17 * fRec21[2]) + (fConst15 * fRec21[1]))));
		double fTemp5 = (fRec21[2] + (fRec21[0] + (2 * fRec21[1])));
		fVec2[0] = fTemp5;
		fRec20[0] = ((fConst48 * ((fConst47 * fVec2[1]) + (fConst10 * fVec2[0]))) + (fConst46 * fRec20[1]));
		fRec19[0] = (fRec20[0] - (fConst44 * ((fConst43 * fRec19[2]) + (fConst9 * fRec19[1]))));
		double fTemp6 = max(-1, min(1, (fSlow5 * (((fConst8 * fRec19[0]) + (fConst49 * fRec19[1])) + (fConst8 * fRec19[2])))));
		double fTemp7 = (fConst9 * fRec23[1]);
		double fTemp8 = (fConst15 * fRec24[1]);
		fRec26[0] = ((fConst39 * ((fConst52 * fRec16[1]) + (fConst25 * fRec16[0]))) + (fConst30 * fRec26[1]));
		fRec25[0] = (fRec26[0] - (fConst28 * ((fConst26 * fRec25[2]) + (fConst24 * fRec25[1]))));
		fRec24[0] = ((fConst28 * (((fConst23 * fRec25[0]) + (fConst53 * fRec25[1])) + (fConst23 * fRec25[2]))) - (fConst51 * ((fConst50 * fRec24[2]) + fTemp8)));
		fRec23[0] = ((fRec24[2] + (fConst51 * (fTemp8 + (fConst50 * fRec24[0])))) - (fConst12 * ((fConst11 * fRec23[2]) + fTemp7)));
		double fTemp9 = max(-1, min(1, (fSlow6 * (fRec23[2] + (fConst12 * (fTemp7 + (fConst11 * fRec23[0])))))));
		fRec28[0] = ((fConst48 * (fVec2[0] + fVec2[1])) + (fConst46 * fRec28[1]));
		fRec27[0] = (fRec28[0] - (fConst44 * ((fConst43 * fRec27[2]) + (fConst9 * fRec27[1]))));
		double fTemp10 = max(-1, min(1, (fSlow7 * (fRec27[2] + (fRec27[0] + (2 * fRec27[1]))))));
		double fTemp11 = ((1.2589412 * (fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10))))) + (1.584893192 * ((fTemp9 * (1 - (0.3333333333333333 * faustpower<2>(fTemp9)))) + ((fTemp6 * (1 - (0.3333333333333333 * faustpower<2>(fTemp6)))) + (0.8413951417869425 * (fTemp4 * (1 - (0.3333333333333333 * faustpower<2>(fTemp4)))))))));
		fVec3[0] = fTemp11;
		fRec10[0] = ((fConst54 * (fVec3[0] + fVec3[1])) + (fConst6 * fRec10[1]));
		fRec29[0] = ((fConst58 * (fRec9[1] + fRec9[2])) + (fConst57 * fRec29[1]));
		double fTemp12 = (1 - fRec18[0]);
		fRec9[0] = (Ftube(TUBE_TABLE_12AU7_68k, (((fTemp1 * ((fSlow11 * fRec18[0]) + (fTemp12 * (1 + (fSlow10 * ((4 - (4 * fabs((fTemp1 * fTemp12)))) - 1)))))) + (fRec29[0] + (fSlow9 * fRec10[0]))) - 3.718962)) - 112.26066666666668);
		fRec8[0] = ((fConst59 * ((fConst37 * fRec9[1]) + (fConst1 * fRec9[0]))) + (fConst3 * fRec8[1]));
		double fTemp13 = (fRec8[0] * fRec7[0]);
		fVec4[0] = fTemp13;
		fRec6[0] = ((fConst60 * (fVec4[0] + fVec4[1])) + (fConst6 * fRec6[1]));
		fRec30[0] = ((fConst64 * (fRec5[1] + fRec5[2])) + (fConst63 * fRec30[1]));
		fRec5[0] = (Ftube(TUBE_TABLE_12AU7_250k, ((fRec30[0] + fRec6[0]) - 2.314844)) - 95.67706666666666);
		fRec4[0] = ((fConst59 * ((fConst37 * fRec5[1]) + (fConst1 * fRec5[0]))) + (fConst3 * fRec4[1]));
		double fTemp14 = (fRec7[0] * fRec4[0]);
		fVec5[0] = fTemp14;
		fRec3[0] = ((fConst60 * (fVec5[0] + fVec5[1])) + (fConst6 * fRec3[1]));
		fRec31[0] = ((fConst68 * (fRec2[1] + fRec2[2])) + (fConst67 * fRec31[1]));
		fRec2[0] = (Ftube(TUBE_TABLE_12AU7_250k, ((fRec31[0] + fRec3[0]) - 1.356567)) - 84.565);
		fRec1[0] = ((fConst59 * ((fConst37 * fRec2[1]) + (fConst1 * fRec2[0]))) + (fConst3 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(2.0 * (fRec1[0] * fRec0[0]));
		// post processing
		fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec31[1] = fRec31[0];
		fRec3[1] = fRec3[0];
		fVec5[1] = fVec5[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec30[1] = fRec30[0];
		fRec6[1] = fRec6[0];
		fVec4[1] = fVec4[0];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec29[1] = fRec29[0];
		fRec10[1] = fRec10[0];
		fVec3[1] = fVec3[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fVec2[1] = fVec2[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fVec1[1] = fVec1[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fVec0[1] = fVec0[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec7[1] = fRec7[0];
		fRec0[1] = fRec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
}

void Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	fslider3_ = reg.registerVar("gxdistortion.drive","","SA","",&fslider3, 0.35, 0.0, 1.0, 0.01);
	fslider2_ = reg.registerVar("gxdistortion.wet_dry","","SA","",&fslider2, 1e+02, 0.0, 1e+02, 1.0);
	fslider1_ = reg.registerVar("amp2.stage1.Pregain","","SA","",&fslider1, -6.0, -2e+01, 2e+01, 0.1);
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

} // end namespace gxamp3
