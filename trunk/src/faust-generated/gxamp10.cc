// generated from file '../src/faust/gxamp10.dsp' by dsp2cc:
// Code generated with Faust 0.9.57 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp10 {

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
	double 	fConst7;
	double 	fRec3[2];
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec8[2];
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
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec19[2];
	double 	fRec18[3];
	double 	fVec0[2];
	double 	fConst41;
	double 	fConst42;
	double 	fRec17[2];
	double 	fConst43;
	double 	fRec16[2];
	double 	fRec15[3];
	double 	fVec1[2];
	double 	fConst44;
	double 	fConst45;
	double 	fRec14[2];
	double 	fRec13[3];
	double 	fConst46;
	double 	fRec12[3];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fVec2[2];
	double 	fConst51;
	double 	fConst52;
	double 	fRec21[2];
	double 	fRec20[3];
	double 	fConst53;
	double 	fConst54;
	double 	fConst55;
	double 	fConst56;
	double 	fRec27[2];
	double 	fRec26[3];
	double 	fConst57;
	double 	fRec25[3];
	double 	fRec24[3];
	double 	fRec29[2];
	double 	fRec28[3];
	double 	fVec3[2];
	double 	fConst58;
	double 	fRec11[2];
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fRec30[2];
	double 	fRec10[3];
	double 	fConst63;
	double 	fRec9[2];
	double 	fVec4[2];
	double 	fRec7[2];
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fRec31[2];
	double 	fRec6[3];
	double 	fRec5[2];
	double 	fVec5[2];
	double 	fRec4[2];
	double 	fRec2[3];
	double 	fRec1[2];
	double 	fRec34[2];
	double 	fRec33[3];
	double 	fRec32[2];
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
	id = "6DJ8";
	name = N_("6DJ8");
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
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<3; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
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
	fConst4 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = (0.0082 / fConst5);
	fConst8 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst9 = (1 + fConst8);
	fConst10 = (0 - ((1 - fConst8) / fConst9));
	fConst11 = tan((942.4777960769379 / double(iConst0)));
	fConst12 = (1.0 / faustpower<2>(fConst11));
	fConst13 = (2 * (1 - fConst12));
	fConst14 = (1.0 / fConst11);
	fConst15 = (1 + ((fConst14 - 1.0) / fConst11));
	fConst16 = (1.0 / (1 + ((1.0 + fConst14) / fConst11)));
	fConst17 = tan((3769.9111843077517 / double(iConst0)));
	fConst18 = (1.0 / faustpower<2>(fConst17));
	fConst19 = (2 * (1 - fConst18));
	fConst20 = (1.0 / fConst17);
	fConst21 = (1 + ((fConst20 - 1.0000000000000004) / fConst17));
	fConst22 = (1 + ((fConst20 + 1.0000000000000004) / fConst17));
	fConst23 = (1.0 / fConst22);
	fConst24 = (1 + fConst20);
	fConst25 = (0 - ((1 - fConst20) / fConst24));
	fConst26 = tan((10053.096491487338 / double(iConst0)));
	fConst27 = (1.0 / faustpower<2>(fConst26));
	fConst28 = (2 * (1 - fConst27));
	fConst29 = (1.0 / fConst26);
	fConst30 = (1 + ((fConst29 - 1.0000000000000004) / fConst26));
	fConst31 = (1 + ((1.0000000000000004 + fConst29) / fConst26));
	fConst32 = (1.0 / fConst31);
	fConst33 = (1 + fConst29);
	fConst34 = (0 - ((1 - fConst29) / fConst33));
	fConst35 = tan((47123.8898038469 / double(iConst0)));
	fConst36 = (2 * (1 - (1.0 / faustpower<2>(fConst35))));
	fConst37 = (1.0 / fConst35);
	fConst38 = (1 + ((fConst37 - 1.414213562373095) / fConst35));
	fConst39 = (1 + ((1.414213562373095 + fConst37) / fConst35));
	fConst40 = (1.0 / fConst39);
	fConst41 = (0 - fConst1);
	fConst42 = (1.0 / (fConst2 * fConst39));
	fConst43 = (1.0 / fConst33);
	fConst44 = (0 - fConst20);
	fConst45 = (1.0 / (fConst24 * fConst31));
	fConst46 = (2 * (0 - fConst18));
	fConst47 = (1 + ((fConst14 - 1.0000000000000004) / fConst11));
	fConst48 = (1.0 / (1 + ((fConst14 + 1.0000000000000004) / fConst11)));
	fConst49 = (1 + fConst14);
	fConst50 = (0 - ((1 - fConst14) / fConst49));
	fConst51 = (0 - fConst14);
	fConst52 = (1.0 / (fConst49 * fConst22));
	fConst53 = (2 * (0 - fConst12));
	fConst54 = (1 + ((fConst20 - 1.0) / fConst17));
	fConst55 = (1.0 / (1 + ((1.0 + fConst20) / fConst17)));
	fConst56 = (0 - fConst29);
	fConst57 = (2 * (0 - fConst27));
	fConst58 = (1.0 / fConst9);
	fConst59 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst60 = (1 + fConst59);
	fConst61 = (0 - ((1 - fConst59) / fConst60));
	fConst62 = (0.027 / fConst60);
	fConst63 = (0.05 / fConst2);
	fConst64 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst65 = (1 + fConst64);
	fConst66 = (0 - ((1 - fConst64) / fConst65));
	fConst67 = (0.015 / fConst65);
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
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * fslider1)));
	double 	fSlow2 = (1.000000000000001e-05 * fslider2);
	double 	fSlow3 = fslider3;
	double 	fSlow4 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow5 = (fConst48 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow6 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow7 = (fConst48 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow8 = (2 * (fSlow3 - 0.5));
	double 	fSlow9 = (1 - max((double)0, (0 - fSlow8)));
	double 	fSlow10 = (1.25 * fSlow3);
	double 	fSlow11 = (1 - max((double)0, fSlow8));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec3[0] = ((fConst7 * (fRec2[1] + fRec2[2])) + (fConst6 * fRec3[1]));
		fRec8[0] = (fSlow1 + (0.999 * fRec8[1]));
		double fTemp0 = (fConst13 * fRec12[1]);
		fRec19[0] = (fSlow2 + (0.999 * fRec19[1]));
		double fTemp1 = (double)input0[i];
		fRec18[0] = ((fTemp1 * fRec19[0]) - (fConst40 * ((fConst38 * fRec18[2]) + (fConst36 * fRec18[1]))));
		double fTemp2 = (fRec18[2] + (fRec18[0] + (2 * fRec18[1])));
		fVec0[0] = fTemp2;
		fRec17[0] = ((fConst42 * ((fConst41 * fVec0[1]) + (fConst1 * fVec0[0]))) + (fConst3 * fRec17[1]));
		fRec16[0] = ((fConst43 * (fRec17[0] + fRec17[1])) + (fConst34 * fRec16[1]));
		fRec15[0] = (fRec16[0] - (fConst32 * ((fConst30 * fRec15[2]) + (fConst28 * fRec15[1]))));
		double fTemp3 = (fRec15[2] + (fRec15[0] + (2 * fRec15[1])));
		fVec1[0] = fTemp3;
		fRec14[0] = ((fConst45 * ((fConst44 * fVec1[1]) + (fConst20 * fVec1[0]))) + (fConst25 * fRec14[1]));
		fRec13[0] = (fRec14[0] - (fConst23 * ((fConst21 * fRec13[2]) + (fConst19 * fRec13[1]))));
		fRec12[0] = ((fConst23 * (((fConst18 * fRec13[0]) + (fConst46 * fRec13[1])) + (fConst18 * fRec13[2]))) - (fConst16 * ((fConst15 * fRec12[2]) + fTemp0)));
		double fTemp4 = max((double)-1, min((double)1, (fSlow4 * (fRec12[2] + (fConst16 * (fTemp0 + (fConst15 * fRec12[0])))))));
		fRec23[0] = ((fConst45 * (fVec1[0] + fVec1[1])) + (fConst25 * fRec23[1]));
		fRec22[0] = (fRec23[0] - (fConst23 * ((fConst21 * fRec22[2]) + (fConst19 * fRec22[1]))));
		double fTemp5 = (fRec22[2] + (fRec22[0] + (2 * fRec22[1])));
		fVec2[0] = fTemp5;
		fRec21[0] = ((fConst52 * ((fConst51 * fVec2[1]) + (fConst14 * fVec2[0]))) + (fConst50 * fRec21[1]));
		fRec20[0] = (fRec21[0] - (fConst48 * ((fConst47 * fRec20[2]) + (fConst13 * fRec20[1]))));
		double fTemp6 = max((double)-1, min((double)1, (fSlow5 * (((fConst12 * fRec20[0]) + (fConst53 * fRec20[1])) + (fConst12 * fRec20[2])))));
		double fTemp7 = (fConst13 * fRec24[1]);
		double fTemp8 = (fConst19 * fRec25[1]);
		fRec27[0] = ((fConst43 * ((fConst56 * fRec17[1]) + (fConst29 * fRec17[0]))) + (fConst34 * fRec27[1]));
		fRec26[0] = (fRec27[0] - (fConst32 * ((fConst30 * fRec26[2]) + (fConst28 * fRec26[1]))));
		fRec25[0] = ((fConst32 * (((fConst27 * fRec26[0]) + (fConst57 * fRec26[1])) + (fConst27 * fRec26[2]))) - (fConst55 * ((fConst54 * fRec25[2]) + fTemp8)));
		fRec24[0] = ((fRec25[2] + (fConst55 * (fTemp8 + (fConst54 * fRec25[0])))) - (fConst16 * ((fConst15 * fRec24[2]) + fTemp7)));
		double fTemp9 = max((double)-1, min((double)1, (fSlow6 * (fRec24[2] + (fConst16 * (fTemp7 + (fConst15 * fRec24[0])))))));
		fRec29[0] = ((fConst52 * (fVec2[0] + fVec2[1])) + (fConst50 * fRec29[1]));
		fRec28[0] = (fRec29[0] - (fConst48 * ((fConst47 * fRec28[2]) + (fConst13 * fRec28[1]))));
		double fTemp10 = max((double)-1, min((double)1, (fSlow7 * (fRec28[2] + (fRec28[0] + (2 * fRec28[1]))))));
		double fTemp11 = ((1.2589412 * (fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10))))) + (1.584893192 * ((fTemp9 * (1 - (0.3333333333333333 * faustpower<2>(fTemp9)))) + ((fTemp6 * (1 - (0.3333333333333333 * faustpower<2>(fTemp6)))) + (0.8413951417869425 * (fTemp4 * (1 - (0.3333333333333333 * faustpower<2>(fTemp4)))))))));
		fVec3[0] = fTemp11;
		fRec11[0] = ((fConst58 * (fVec3[0] + fVec3[1])) + (fConst10 * fRec11[1]));
		fRec30[0] = ((fConst62 * (fRec10[1] + fRec10[2])) + (fConst61 * fRec30[1]));
		double fTemp12 = (1 - fRec19[0]);
		fRec10[0] = (Ftube(TUBE_TABLE_6DJ8_68k, (((fTemp1 * ((fSlow11 * fRec19[0]) + (fTemp12 * (1 + (fSlow10 * ((4 - (4 * fabs((fTemp1 * fTemp12)))) - 1)))))) + (fRec30[0] + (fSlow9 * fRec11[0]))) - 1.863946)) - 60.96496296296296);
		fRec9[0] = ((fConst63 * ((fConst41 * fRec10[1]) + (fConst1 * fRec10[0]))) + (fConst3 * fRec9[1]));
		double fTemp13 = (fRec9[0] * fRec8[0]);
		fVec4[0] = fTemp13;
		fRec7[0] = ((fConst58 * (fVec4[0] + fVec4[1])) + (fConst10 * fRec7[1]));
		fRec31[0] = ((fConst67 * (fRec6[1] + fRec6[2])) + (fConst66 * fRec31[1]));
		fRec6[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec31[0] + fRec7[0]) - 1.271609)) - 45.22606666666667);
		fRec5[0] = ((fConst63 * ((fConst41 * fRec6[1]) + (fConst1 * fRec6[0]))) + (fConst3 * fRec5[1]));
		double fTemp14 = (fRec8[0] * fRec5[0]);
		fVec5[0] = fTemp14;
		fRec4[0] = ((fConst58 * (fVec5[0] + fVec5[1])) + (fConst10 * fRec4[1]));
		fRec2[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec4[0] + fRec3[0]) - 0.797043)) - 32.799634146341475);
		fRec1[0] = ((fConst63 * ((fConst41 * fRec2[1]) + (fConst1 * fRec2[0]))) + (fConst3 * fRec1[1]));
		fRec34[0] = ((fConst7 * (fRec33[1] + fRec33[2])) + (fConst6 * fRec34[1]));
		fRec33[0] = (Ftube(TUBE_TABLE_6DJ8_68k, ((fRec34[0] + fRec4[0]) - 0.799031)) - 32.55719512195121);
		fRec32[0] = ((fConst63 * ((fConst41 * fRec33[1]) + (fConst1 * fRec33[0]))) + (fConst3 * fRec32[1]));
		output0[i] = (FAUSTFLOAT)((fRec32[0] + fRec1[0]) * fRec0[0]);
		// post processing
		fRec32[1] = fRec32[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec34[1] = fRec34[0];
		fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fVec5[1] = fVec5[0];
		fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec31[1] = fRec31[0];
		fRec7[1] = fRec7[0];
		fVec4[1] = fVec4[0];
		fRec9[1] = fRec9[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec30[1] = fRec30[0];
		fRec11[1] = fRec11[0];
		fVec3[1] = fVec3[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fVec2[1] = fVec2[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fVec1[1] = fVec1[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fVec0[1] = fVec0[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fRec8[1] = fRec8[0];
		fRec3[1] = fRec3[0];
		fRec0[1] = fRec0[0];
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

} // end namespace gxamp10
