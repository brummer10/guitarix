// generated from file '../src/faust/gxamp10.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

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
	double 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec12[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec17[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
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
	double 	fConst30;
	double 	fRec26[3];
	double 	fVec0[2];
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fRec25[2];
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fRec24[2];
	double 	fRec23[3];
	double 	fVec1[2];
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fRec22[2];
	double 	fRec21[3];
	double 	fVec2[2];
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fRec20[2];
	double 	fRec19[3];
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fRec29[2];
	double 	fRec28[3];
	double 	fConst48;
	double 	fRec27[3];
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fRec33[2];
	double 	fRec32[3];
	double 	fConst52;
	double 	fRec31[3];
	double 	fRec30[3];
	double 	fConst53;
	double 	fRec35[2];
	double 	fRec34[3];
	double 	fConst54;
	double 	fVec3[2];
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fRec18[2];
	double 	fRec16[3];
	double 	fVec4[2];
	double 	fRec15[2];
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fRec36[2];
	double 	fRec14[3];
	double 	fConst63;
	double 	fRec13[2];
	double 	fVec5[2];
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fVec6[2];
	double 	fRec9[2];
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fRec37[2];
	double 	fRec8[3];
	double 	fRec7[2];
	double 	fVec7[2];
	double 	fRec6[2];
	double 	fRec5[3];
	double 	fVec8[2];
	double 	fRec4[2];
	double 	fRec2[3];
	double 	fRec1[2];
	double 	fRec40[2];
	double 	fRec39[3];
	double 	fRec38[2];
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
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<3; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<3; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<3; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst2 = (1 + fConst1);
	fConst3 = (0.0082 / fConst2);
	fConst4 = (0 - ((1 - fConst1) / fConst2));
	fConst5 = tan((942.4777960769379 / double(iConst0)));
	fConst6 = (1.0 / faustpower<2>(fConst5));
	fConst7 = (2 * (1 - fConst6));
	fConst8 = (1.0 / fConst5);
	fConst9 = (1 + ((fConst8 - 1.0000000000000004) / fConst5));
	fConst10 = (1.0 / (1 + ((fConst8 + 1.0000000000000004) / fConst5)));
	fConst11 = tan((3769.9111843077517 / double(iConst0)));
	fConst12 = (1.0 / faustpower<2>(fConst11));
	fConst13 = (2 * (1 - fConst12));
	fConst14 = (1.0 / fConst11);
	fConst15 = (1 + ((fConst14 - 1.0000000000000004) / fConst11));
	fConst16 = (1 + ((fConst14 + 1.0000000000000004) / fConst11));
	fConst17 = (1.0 / fConst16);
	fConst18 = tan((10053.096491487338 / double(iConst0)));
	fConst19 = (1.0 / faustpower<2>(fConst18));
	fConst20 = (2 * (1 - fConst19));
	fConst21 = (1.0 / fConst18);
	fConst22 = (1 + ((fConst21 - 1.0000000000000004) / fConst18));
	fConst23 = (1 + ((1.0000000000000004 + fConst21) / fConst18));
	fConst24 = (1.0 / fConst23);
	fConst25 = tan((47123.8898038469 / double(iConst0)));
	fConst26 = (2 * (1 - (1.0 / faustpower<2>(fConst25))));
	fConst27 = (1.0 / fConst25);
	fConst28 = (1 + ((fConst27 - 1.414213562373095) / fConst25));
	fConst29 = (1 + ((1.414213562373095 + fConst27) / fConst25));
	fConst30 = (1.0 / fConst29);
	fConst31 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst32 = (0 - fConst31);
	fConst33 = (1 + fConst31);
	fConst34 = (1.0 / (fConst33 * fConst29));
	fConst35 = (0 - ((1 - fConst31) / fConst33));
	fConst36 = (1 + fConst21);
	fConst37 = (1.0 / fConst36);
	fConst38 = (0 - ((1 - fConst21) / fConst36));
	fConst39 = (1 + fConst14);
	fConst40 = (1.0 / (fConst39 * fConst23));
	fConst41 = (0 - ((1 - fConst14) / fConst39));
	fConst42 = (1 + fConst8);
	fConst43 = (1.0 / (fConst42 * fConst16));
	fConst44 = (0 - ((1 - fConst8) / fConst42));
	fConst45 = (1 + ((fConst8 - 1.0) / fConst5));
	fConst46 = (1.0 / (1 + ((1.0 + fConst8) / fConst5)));
	fConst47 = (0 - fConst14);
	fConst48 = (2 * (0 - fConst12));
	fConst49 = (1 + ((fConst14 - 1.0) / fConst11));
	fConst50 = (1.0 / (1 + ((1.0 + fConst14) / fConst11)));
	fConst51 = (0 - fConst21);
	fConst52 = (2 * (0 - fConst19));
	fConst53 = (0 - fConst8);
	fConst54 = (2 * (0 - fConst6));
	fConst55 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst56 = (1 + fConst55);
	fConst57 = (1.0 / fConst56);
	fConst58 = (0 - ((1 - fConst55) / fConst56));
	fConst59 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst60 = (1 + fConst59);
	fConst61 = (0.027 / fConst60);
	fConst62 = (0 - ((1 - fConst59) / fConst60));
	fConst63 = (0.05 / fConst33);
	fConst64 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst65 = (1 + fConst64);
	fConst66 = (0.015 / fConst65);
	fConst67 = (0 - ((1 - fConst64) / fConst65));
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
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider1))));
	double 	fSlow2 = (1.000000000000001e-05 * double(fslider2));
	double 	fSlow3 = double(fslider3);
	double 	fSlow4 = (2 * (fSlow3 - 0.5));
	double 	fSlow5 = (1 - max((double)0, fSlow4));
	double 	fSlow6 = (1.25 * fSlow3);
	double 	fSlow7 = (fConst10 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow8 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow9 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow10 = (fConst10 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow11 = (1 - max((double)0, (0 - fSlow4)));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.999 * fRec0[1]) + fSlow0);
		fRec3[0] = ((fConst4 * fRec3[1]) + (fConst3 * (fRec2[1] + fRec2[2])));
		double fTemp0 = (2.0 * fRec5[1]);
		double fTemp1 = (2.0 * fRec10[1]);
		fRec12[0] = ((0.999 * fRec12[1]) + fSlow1);
		double fTemp2 = (2.0 * fRec16[1]);
		fRec17[0] = (fSlow2 + (0.999 * fRec17[1]));
		double fTemp3 = (1 - fRec17[0]);
		double fTemp4 = (double)input0[i];
		fRec26[0] = ((fTemp4 * fRec17[0]) - (fConst30 * ((fConst28 * fRec26[2]) + (fConst26 * fRec26[1]))));
		double fTemp5 = (fRec26[2] + (fRec26[0] + (2 * fRec26[1])));
		fVec0[0] = fTemp5;
		fRec25[0] = ((fConst35 * fRec25[1]) + (fConst34 * ((fConst31 * fVec0[0]) + (fConst32 * fVec0[1]))));
		fRec24[0] = ((fConst38 * fRec24[1]) + (fConst37 * (fRec25[0] + fRec25[1])));
		fRec23[0] = (fRec24[0] - (fConst24 * ((fConst22 * fRec23[2]) + (fConst20 * fRec23[1]))));
		double fTemp6 = (fRec23[2] + (fRec23[0] + (2 * fRec23[1])));
		fVec1[0] = fTemp6;
		fRec22[0] = ((fConst41 * fRec22[1]) + (fConst40 * (fVec1[0] + fVec1[1])));
		fRec21[0] = (fRec22[0] - (fConst17 * ((fConst15 * fRec21[2]) + (fConst13 * fRec21[1]))));
		double fTemp7 = (fRec21[2] + (fRec21[0] + (2 * fRec21[1])));
		fVec2[0] = fTemp7;
		fRec20[0] = ((fConst44 * fRec20[1]) + (fConst43 * (fVec2[0] + fVec2[1])));
		fRec19[0] = (fRec20[0] - (fConst10 * ((fConst9 * fRec19[2]) + (fConst7 * fRec19[1]))));
		double fTemp8 = max((double)-1, min((double)1, (fSlow7 * (fRec19[2] + (fRec19[0] + (2 * fRec19[1]))))));
		double fTemp9 = (fConst7 * fRec27[1]);
		fRec29[0] = ((fConst41 * fRec29[1]) + (fConst40 * ((fConst14 * fVec1[0]) + (fConst47 * fVec1[1]))));
		fRec28[0] = (fRec29[0] - (fConst17 * ((fConst15 * fRec28[2]) + (fConst13 * fRec28[1]))));
		fRec27[0] = ((fConst17 * (((fConst12 * fRec28[0]) + (fConst48 * fRec28[1])) + (fConst12 * fRec28[2]))) - (fConst46 * ((fConst45 * fRec27[2]) + fTemp9)));
		double fTemp10 = max((double)-1, min((double)1, (fSlow8 * (fRec27[2] + (fConst46 * (fTemp9 + (fConst45 * fRec27[0])))))));
		double fTemp11 = (fConst7 * fRec30[1]);
		double fTemp12 = (fConst13 * fRec31[1]);
		fRec33[0] = ((fConst38 * fRec33[1]) + (fConst37 * ((fConst21 * fRec25[0]) + (fConst51 * fRec25[1]))));
		fRec32[0] = (fRec33[0] - (fConst24 * ((fConst22 * fRec32[2]) + (fConst20 * fRec32[1]))));
		fRec31[0] = ((fConst24 * (((fConst19 * fRec32[0]) + (fConst52 * fRec32[1])) + (fConst19 * fRec32[2]))) - (fConst50 * ((fConst49 * fRec31[2]) + fTemp12)));
		fRec30[0] = ((fRec31[2] + (fConst50 * (fTemp12 + (fConst49 * fRec31[0])))) - (fConst46 * ((fConst45 * fRec30[2]) + fTemp11)));
		double fTemp13 = max((double)-1, min((double)1, (fSlow9 * (fRec30[2] + (fConst46 * (fTemp11 + (fConst45 * fRec30[0])))))));
		fRec35[0] = ((fConst44 * fRec35[1]) + (fConst43 * ((fConst53 * fVec2[1]) + (fConst8 * fVec2[0]))));
		fRec34[0] = (fRec35[0] - (fConst10 * ((fConst9 * fRec34[2]) + (fConst7 * fRec34[1]))));
		double fTemp14 = max((double)-1, min((double)1, (fSlow10 * (((fConst6 * fRec34[0]) + (fConst54 * fRec34[1])) + (fConst6 * fRec34[2])))));
		double fTemp15 = ((1.584893192 * ((fTemp14 * (1 - (0.3333333333333333 * faustpower<2>(fTemp14)))) + ((fTemp13 * (1 - (0.3333333333333333 * faustpower<2>(fTemp13)))) + (0.8413951417869425 * (fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10)))))))) + (1.2589412 * (fTemp8 * (1 - (0.3333333333333333 * faustpower<2>(fTemp8))))));
		fVec3[0] = fTemp15;
		fRec18[0] = ((fConst58 * fRec18[1]) + (fConst57 * (fVec3[0] + fVec3[1])));
		fRec16[0] = (((fSlow11 * fRec18[0]) + (fTemp4 * ((fTemp3 * (1 + (fSlow6 * ((4 - (4 * fabs((fTemp4 * fTemp3)))) - 1)))) + (fSlow5 * fRec17[0])))) - (fTemp2 + fRec16[2]));
		double fTemp16 = (fRec16[2] + (fRec16[0] + fTemp2));
		fVec4[0] = fTemp16;
		fRec15[0] = ((1.0000000000000002 * (fVec4[0] + fVec4[1])) - (0.9999999999999998 * fRec15[1]));
		fRec36[0] = ((fConst62 * fRec36[1]) + (fConst61 * (fRec14[1] + fRec14[2])));
		fRec14[0] = (Ftube(TUBE_TABLE_6DJ8_68k, ((fRec36[0] + fRec15[0]) - 1.863946)) - 60.96496296296296);
		fRec13[0] = ((fConst35 * fRec13[1]) + (fConst63 * ((fConst31 * fRec14[0]) + (fConst32 * fRec14[1]))));
		double fTemp17 = (fRec13[0] * fRec12[0]);
		fVec5[0] = fTemp17;
		fRec11[0] = ((fConst58 * fRec11[1]) + (fConst57 * (fVec5[0] + fVec5[1])));
		fRec10[0] = (fRec11[0] - (fTemp1 + fRec10[2]));
		double fTemp18 = (fRec10[2] + (fRec10[0] + fTemp1));
		fVec6[0] = fTemp18;
		fRec9[0] = ((1.0000000000000002 * (fVec6[0] + fVec6[1])) - (0.9999999999999998 * fRec9[1]));
		fRec37[0] = ((fConst67 * fRec37[1]) + (fConst66 * (fRec8[1] + fRec8[2])));
		fRec8[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec37[0] + fRec9[0]) - 1.271609)) - 45.22606666666667);
		fRec7[0] = ((fConst35 * fRec7[1]) + (fConst63 * ((fConst31 * fRec8[0]) + (fConst32 * fRec8[1]))));
		double fTemp19 = (fRec12[0] * fRec7[0]);
		fVec7[0] = fTemp19;
		fRec6[0] = ((fConst58 * fRec6[1]) + (fConst57 * (fVec7[0] + fVec7[1])));
		fRec5[0] = (fRec6[0] - (fTemp0 + fRec5[2]));
		double fTemp20 = (fRec5[2] + (fRec5[0] + fTemp0));
		fVec8[0] = fTemp20;
		fRec4[0] = ((1.0000000000000002 * (fVec8[0] + fVec8[1])) - (0.9999999999999998 * fRec4[1]));
		fRec2[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec4[0] + fRec3[0]) - 0.797043)) - 32.799634146341475);
		fRec1[0] = ((fConst35 * fRec1[1]) + (fConst63 * ((fConst31 * fRec2[0]) + (fConst32 * fRec2[1]))));
		fRec40[0] = ((fConst4 * fRec40[1]) + (fConst3 * (fRec39[1] + fRec39[2])));
		fRec39[0] = (Ftube(TUBE_TABLE_6DJ8_68k, ((fRec40[0] + fRec4[0]) - 0.799031)) - 32.55719512195121);
		fRec38[0] = ((fConst35 * fRec38[1]) + (fConst63 * ((fConst31 * fRec39[0]) + (fConst32 * fRec39[1]))));
		output0[i] = (FAUSTFLOAT)((fRec38[0] + fRec1[0]) * fRec0[0]);
		// post processing
		fRec38[1] = fRec38[0];
		fRec39[2] = fRec39[1]; fRec39[1] = fRec39[0];
		fRec40[1] = fRec40[0];
		fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fVec8[1] = fVec8[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fVec7[1] = fVec7[0];
		fRec7[1] = fRec7[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec37[1] = fRec37[0];
		fRec9[1] = fRec9[0];
		fVec6[1] = fVec6[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec5[1] = fVec5[0];
		fRec13[1] = fRec13[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec36[1] = fRec36[0];
		fRec15[1] = fRec15[0];
		fVec4[1] = fVec4[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec18[1] = fRec18[0];
		fVec3[1] = fVec3[0];
		fRec34[2] = fRec34[1]; fRec34[1] = fRec34[0];
		fRec35[1] = fRec35[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
		fRec33[1] = fRec33[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fVec2[1] = fVec2[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fVec1[1] = fVec1[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fVec0[1] = fVec0[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec17[1] = fRec17[0];
		fRec12[1] = fRec12[0];
		fRec3[1] = fRec3[0];
		fRec0[1] = fRec0[0];
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
