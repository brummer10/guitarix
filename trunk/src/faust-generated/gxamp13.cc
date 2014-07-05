// generated from file '../src/faust/gxamp13.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp13 {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec8[2];
	double 	fRec14[2];
	int 	IOTA;
	double 	fVec0[32768];
	int 	iConst0;
	int 	iConst1;
	double 	fRec13[2];
	double 	fConst2;
	double 	fRec12[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec15[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fRec16[2];
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
	double 	fRec25[3];
	double 	fVec1[2];
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fRec24[2];
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fVec2[2];
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fRec21[2];
	double 	fRec20[3];
	double 	fVec3[2];
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fRec19[2];
	double 	fRec18[3];
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fConst50;
	double 	fRec26[3];
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fRec32[2];
	double 	fRec31[3];
	double 	fConst54;
	double 	fRec30[3];
	double 	fRec29[3];
	double 	fConst55;
	double 	fRec34[2];
	double 	fRec33[3];
	double 	fConst56;
	double 	fVec4[2];
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fRec17[2];
	double 	fRec11[3];
	double 	fConst61;
	double 	fRec10[2];
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fRec37[2];
	double 	fRec36[3];
	double 	fRec35[2];
	double 	fRec9[2];
	double 	fVec5[2];
	double 	fRec7[2];
	double 	fRec38[2];
	double 	fRec6[3];
	double 	fRec5[2];
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fRec41[2];
	double 	fRec40[3];
	double 	fRec39[2];
	double 	fRec4[2];
	double 	fRec3[2];
	double 	fRec42[2];
	double 	fRec2[3];
	double 	fRec1[2];
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
	id = "6DJ8 feedback";
	name = N_("6DJ8 feedback");
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
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<32768; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<3; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<3; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<3; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
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
	IOTA = 0;
	iConst0 = min(192000, max(1, fSamplingFreq));
	iConst1 = int((int((0.1111111111111111 * iConst0)) & 65535));
	fConst2 = (0.009000000000000008 / double(iConst0));
	fConst3 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst4 = (1 + fConst3);
	fConst5 = (0.027 / fConst4);
	fConst6 = (0 - ((1 - fConst3) / fConst4));
	fConst7 = tan((942.4777960769379 / double(iConst0)));
	fConst8 = (1.0 / faustpower<2>(fConst7));
	fConst9 = (2 * (1 - fConst8));
	fConst10 = (1.0 / fConst7);
	fConst11 = (1 + ((fConst10 - 1.0000000000000004) / fConst7));
	fConst12 = (1.0 / (1 + ((fConst10 + 1.0000000000000004) / fConst7)));
	fConst13 = tan((3769.9111843077517 / double(iConst0)));
	fConst14 = (1.0 / faustpower<2>(fConst13));
	fConst15 = (2 * (1 - fConst14));
	fConst16 = (1.0 / fConst13);
	fConst17 = (1 + ((fConst16 - 1.0000000000000004) / fConst13));
	fConst18 = (1 + ((fConst16 + 1.0000000000000004) / fConst13));
	fConst19 = (1.0 / fConst18);
	fConst20 = tan((10053.096491487338 / double(iConst0)));
	fConst21 = (1.0 / faustpower<2>(fConst20));
	fConst22 = (2 * (1 - fConst21));
	fConst23 = (1.0 / fConst20);
	fConst24 = (1 + ((fConst23 - 1.0000000000000004) / fConst20));
	fConst25 = (1 + ((1.0000000000000004 + fConst23) / fConst20));
	fConst26 = (1.0 / fConst25);
	fConst27 = tan((47123.8898038469 / double(iConst0)));
	fConst28 = (2 * (1 - (1.0 / faustpower<2>(fConst27))));
	fConst29 = (1.0 / fConst27);
	fConst30 = (1 + ((fConst29 - 1.414213562373095) / fConst27));
	fConst31 = (1 + ((1.414213562373095 + fConst29) / fConst27));
	fConst32 = (1.0 / fConst31);
	fConst33 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst34 = (0 - fConst33);
	fConst35 = (1 + fConst33);
	fConst36 = (1.0 / (fConst35 * fConst31));
	fConst37 = (0 - ((1 - fConst33) / fConst35));
	fConst38 = (1 + fConst23);
	fConst39 = (1.0 / fConst38);
	fConst40 = (0 - ((1 - fConst23) / fConst38));
	fConst41 = (1 + fConst16);
	fConst42 = (1.0 / (fConst41 * fConst25));
	fConst43 = (0 - ((1 - fConst16) / fConst41));
	fConst44 = (1 + fConst10);
	fConst45 = (1.0 / (fConst44 * fConst18));
	fConst46 = (0 - ((1 - fConst10) / fConst44));
	fConst47 = (1 + ((fConst10 - 1.0) / fConst7));
	fConst48 = (1.0 / (1 + ((1.0 + fConst10) / fConst7)));
	fConst49 = (0 - fConst16);
	fConst50 = (2 * (0 - fConst14));
	fConst51 = (1 + ((fConst16 - 1.0) / fConst13));
	fConst52 = (1.0 / (1 + ((1.0 + fConst16) / fConst13)));
	fConst53 = (0 - fConst23);
	fConst54 = (2 * (0 - fConst21));
	fConst55 = (0 - fConst10);
	fConst56 = (2 * (0 - fConst8));
	fConst57 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst58 = (1 + fConst57);
	fConst59 = (1.0 / fConst58);
	fConst60 = (0 - ((1 - fConst57) / fConst58));
	fConst61 = (0.05 / fConst35);
	fConst62 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst63 = (1 + fConst62);
	fConst64 = (0.015 / fConst63);
	fConst65 = (0 - ((1 - fConst62) / fConst63));
	fConst66 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst67 = (1 + fConst66);
	fConst68 = (0.0082 / fConst67);
	fConst69 = (0 - ((1 - fConst66) / fConst67));
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
	double 	fSlow4 = pow(1e+01,(2 * fSlow3));
	double 	fSlow5 = (fConst12 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow6 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow7 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow8 = (fConst12 * fSlow4);
	double 	fSlow9 = (2 * (fSlow3 - 0.5));
	double 	fSlow10 = (1 - max((double)0, (0 - fSlow9)));
	double 	fSlow11 = (0.024937655860349125 * (1 - max((double)0, fSlow9)));
	double 	fSlow12 = (1.25 * fSlow3);
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.999 * fRec0[1]) + fSlow0);
		fRec8[0] = ((0.999 * fRec8[1]) + fSlow1);
		double fTemp0 = (double)input0[i];
		double fTemp1 = fabs(fTemp0);
		fRec14[0] = ((0.9999 * fRec14[1]) + (9.999999999998899e-05 * fTemp1));
		double fTemp2 = max(fRec14[0], fTemp1);
		fVec0[IOTA&32767] = fTemp2;
		fRec13[0] = ((fVec0[IOTA&32767] + fRec13[1]) - fVec0[(IOTA-iConst1)&32767]);
		fRec12[0] = ((0.999 * fRec12[1]) + (fConst2 * fRec13[0]));
		double fTemp3 = max((double)-1, min(-0.01, (fVec0[IOTA&32767] - (1.0 + (1.02 * fRec12[0])))));
		double fTemp4 = (0 - fTemp3);
		double fTemp5 = (40.1 * fTemp4);
		double fTemp6 = max((double)-600, fTemp5);
		double fTemp7 = (0 - fTemp6);
		double fTemp8 = (fTemp0 - fTemp3);
		double fTemp9 = (40.1 * fTemp8);
		double fTemp10 = max((double)-600, fTemp9);
		double fTemp11 = (0 - fTemp10);
		double fTemp12 = (((int((fabs(fTemp9) > 0.0001)))?((int((fTemp10 < -50)))?(fTemp11 * exp(fTemp10)):(fTemp10 / (1 - exp(fTemp11)))):(1 + (fTemp8 * (20.05 + (134.00083333333336 * fTemp8))))) - ((int((fabs(fTemp5) > 0.0001)))?((int((fTemp6 < -50)))?(fTemp7 * exp(fTemp6)):(fTemp6 / (1 - exp(fTemp7)))):(1 + (fTemp4 * (20.05 + (134.00083333333336 * fTemp4))))));
		fRec15[0] = (fSlow2 + (0.999 * fRec15[1]));
		double fTemp13 = (0.024937655860349125 * (fRec15[0] * fTemp12));
		double fTemp14 = max((double)-1, min((double)1, (fSlow4 * max(-0.7, min(0.7, fTemp13)))));
		fRec16[0] = ((fConst6 * fRec16[1]) + (fConst5 * (fRec11[1] + fRec11[2])));
		fRec25[0] = (fTemp13 - (fConst32 * ((fConst30 * fRec25[2]) + (fConst28 * fRec25[1]))));
		double fTemp15 = (fRec25[2] + (fRec25[0] + (2 * fRec25[1])));
		fVec1[0] = fTemp15;
		fRec24[0] = ((fConst37 * fRec24[1]) + (fConst36 * ((fConst33 * fVec1[0]) + (fConst34 * fVec1[1]))));
		fRec23[0] = ((fConst40 * fRec23[1]) + (fConst39 * (fRec24[0] + fRec24[1])));
		fRec22[0] = (fRec23[0] - (fConst26 * ((fConst24 * fRec22[2]) + (fConst22 * fRec22[1]))));
		double fTemp16 = (fRec22[2] + (fRec22[0] + (2 * fRec22[1])));
		fVec2[0] = fTemp16;
		fRec21[0] = ((fConst43 * fRec21[1]) + (fConst42 * (fVec2[0] + fVec2[1])));
		fRec20[0] = (fRec21[0] - (fConst19 * ((fConst17 * fRec20[2]) + (fConst15 * fRec20[1]))));
		double fTemp17 = (fRec20[2] + (fRec20[0] + (2 * fRec20[1])));
		fVec3[0] = fTemp17;
		fRec19[0] = ((fConst46 * fRec19[1]) + (fConst45 * (fVec3[0] + fVec3[1])));
		fRec18[0] = (fRec19[0] - (fConst12 * ((fConst11 * fRec18[2]) + (fConst9 * fRec18[1]))));
		double fTemp18 = max((double)-1, min((double)1, (fSlow5 * (fRec18[2] + (fRec18[0] + (2 * fRec18[1]))))));
		double fTemp19 = (fConst9 * fRec26[1]);
		fRec28[0] = ((fConst43 * fRec28[1]) + (fConst42 * ((fConst16 * fVec2[0]) + (fConst49 * fVec2[1]))));
		fRec27[0] = (fRec28[0] - (fConst19 * ((fConst17 * fRec27[2]) + (fConst15 * fRec27[1]))));
		fRec26[0] = ((fConst19 * (((fConst14 * fRec27[0]) + (fConst50 * fRec27[1])) + (fConst14 * fRec27[2]))) - (fConst48 * ((fConst47 * fRec26[2]) + fTemp19)));
		double fTemp20 = max((double)-1, min((double)1, (fSlow6 * (fRec26[2] + (fConst48 * (fTemp19 + (fConst47 * fRec26[0])))))));
		double fTemp21 = (fConst9 * fRec29[1]);
		double fTemp22 = (fConst15 * fRec30[1]);
		fRec32[0] = ((fConst40 * fRec32[1]) + (fConst39 * ((fConst23 * fRec24[0]) + (fConst53 * fRec24[1]))));
		fRec31[0] = (fRec32[0] - (fConst26 * ((fConst24 * fRec31[2]) + (fConst22 * fRec31[1]))));
		fRec30[0] = ((fConst26 * (((fConst21 * fRec31[0]) + (fConst54 * fRec31[1])) + (fConst21 * fRec31[2]))) - (fConst52 * ((fConst51 * fRec30[2]) + fTemp22)));
		fRec29[0] = ((fRec30[2] + (fConst52 * (fTemp22 + (fConst51 * fRec30[0])))) - (fConst48 * ((fConst47 * fRec29[2]) + fTemp21)));
		double fTemp23 = max((double)-1, min((double)1, (fSlow7 * (fRec29[2] + (fConst48 * (fTemp21 + (fConst47 * fRec29[0])))))));
		fRec34[0] = ((fConst46 * fRec34[1]) + (fConst45 * ((fConst55 * fVec3[1]) + (fConst10 * fVec3[0]))));
		fRec33[0] = (fRec34[0] - (fConst12 * ((fConst11 * fRec33[2]) + (fConst9 * fRec33[1]))));
		double fTemp24 = max((double)-1, min((double)1, (fSlow8 * (((fConst8 * fRec33[0]) + (fConst56 * fRec33[1])) + (fConst8 * fRec33[2])))));
		double fTemp25 = ((1.584893192 * ((fTemp24 * (1 - (0.3333333333333333 * faustpower<2>(fTemp24)))) + ((fTemp23 * (1 - (0.3333333333333333 * faustpower<2>(fTemp23)))) + (0.8413951417869425 * (fTemp20 * (1 - (0.3333333333333333 * faustpower<2>(fTemp20)))))))) + (1.2589412 * (fTemp18 * (1 - (0.3333333333333333 * faustpower<2>(fTemp18))))));
		fVec4[0] = fTemp25;
		fRec17[0] = ((fConst60 * fRec17[1]) + (fConst59 * (fVec4[0] + fVec4[1])));
		double fTemp26 = (1 - fRec15[0]);
		fRec11[0] = (Ftube(TUBE_TABLE_6DJ8_68k, (((fTemp12 * ((fTemp26 * (0.024937655860349125 + (fSlow12 * ((0.0997506234413965 - (0.0997506234413965 * fabs((0.024937655860349125 * (fTemp26 * fTemp12))))) - 0.024937655860349125)))) + (fSlow11 * fRec15[0]))) + ((fSlow10 * fRec17[0]) + (fRec16[0] + (0.5 * (fTemp14 * (1 - (0.3333333333333333 * faustpower<2>(fTemp14)))))))) - 1.863946)) - 60.96496296296296);
		fRec10[0] = ((fConst37 * fRec10[1]) + (fConst61 * ((fConst33 * fRec11[0]) + (fConst34 * fRec11[1]))));
		fRec37[0] = ((fConst65 * fRec37[1]) + (fConst64 * (fRec36[1] + fRec36[2])));
		fRec36[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec37[0] + fRec9[1]) - 1.271609)) - 45.22606666666667);
		fRec35[0] = ((fConst37 * fRec35[1]) + (fConst61 * ((fConst33 * fRec36[0]) + (fConst34 * fRec36[1]))));
		fRec9[0] = ((0.6 * fRec35[0]) - fRec10[0]);
		double fTemp27 = (fRec9[0] * fRec8[0]);
		fVec5[0] = fTemp27;
		fRec7[0] = ((fConst60 * fRec7[1]) + (fConst59 * (fVec5[0] + fVec5[1])));
		fRec38[0] = ((fConst65 * fRec38[1]) + (fConst64 * (fRec6[1] + fRec6[2])));
		fRec6[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec38[0] + fRec7[0]) - 1.271609)) - 45.22606666666667);
		fRec5[0] = ((fConst37 * fRec5[1]) + (fConst61 * ((fConst33 * fRec6[0]) + (fConst34 * fRec6[1]))));
		fRec41[0] = ((fConst69 * fRec41[1]) + (fConst68 * (fRec40[1] + fRec40[2])));
		fRec40[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec41[0] + fRec4[1]) - 0.797043)) - 32.799634146341475);
		fRec39[0] = ((fConst37 * fRec39[1]) + (fConst61 * ((fConst33 * fRec40[0]) + (fConst34 * fRec40[1]))));
		fRec4[0] = ((0.6 * fRec39[0]) + fRec5[0]);
		fRec3[0] = ((fConst60 * fRec3[1]) + (fConst59 * (fRec4[0] + fRec4[1])));
		fRec42[0] = ((fConst69 * fRec42[1]) + (fConst68 * (fRec2[1] + fRec2[2])));
		fRec2[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec42[0] + fRec3[0]) - 0.797043)) - 32.799634146341475);
		fRec1[0] = ((fConst37 * fRec1[1]) + (fConst61 * ((fConst33 * fRec2[0]) + (fConst34 * fRec2[1]))));
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec42[1] = fRec42[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec39[1] = fRec39[0];
		fRec40[2] = fRec40[1]; fRec40[1] = fRec40[0];
		fRec41[1] = fRec41[0];
		fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec38[1] = fRec38[0];
		fRec7[1] = fRec7[0];
		fVec5[1] = fVec5[0];
		fRec9[1] = fRec9[0];
		fRec35[1] = fRec35[0];
		fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec17[1] = fRec17[0];
		fVec4[1] = fVec4[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec34[1] = fRec34[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec32[1] = fRec32[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fVec3[1] = fVec3[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fVec2[1] = fVec2[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fVec1[1] = fVec1[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec16[1] = fRec16[0];
		fRec15[1] = fRec15[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		IOTA = IOTA+1;
		fRec14[1] = fRec14[0];
		fRec8[1] = fRec8[0];
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

} // end namespace gxamp13
