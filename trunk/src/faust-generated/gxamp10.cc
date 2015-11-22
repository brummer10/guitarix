// generated from file '../src/faust/gxamp10.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp10 {

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
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec2[2];
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fRec5[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec10[2];
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
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec22[2];
	double 	fRec21[3];
	double 	fVec0[2];
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fRec20[2];
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fRec19[2];
	double 	fRec18[3];
	double 	fVec1[2];
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fRec17[2];
	double 	fRec16[3];
	double 	fVec2[2];
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fRec15[2];
	double 	fRec14[3];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fRec25[2];
	double 	fRec24[3];
	double 	fConst53;
	double 	fRec23[3];
	double 	fConst54;
	double 	fConst55;
	double 	fConst56;
	double 	fRec29[2];
	double 	fRec28[3];
	double 	fConst57;
	double 	fRec27[3];
	double 	fRec26[3];
	double 	fConst58;
	double 	fRec31[2];
	double 	fRec30[3];
	double 	fConst59;
	double 	fVec3[2];
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fRec13[2];
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fRec32[2];
	double 	fRec12[3];
	double 	fConst68;
	double 	fRec11[2];
	double 	fVec4[2];
	double 	fRec9[2];
	double 	fConst69;
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fRec33[2];
	double 	fRec8[3];
	double 	fRec7[2];
	double 	fVec5[2];
	double 	fRec6[2];
	double 	fRec4[3];
	double 	fRec3[2];
	double 	fRec36[2];
	double 	fRec35[3];
	double 	fRec34[2];
	double 	fVec6[2];
	double 	fConst73;
	double 	fConst74;
	double 	fConst75;
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
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<3; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
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
	fConst6 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst7 = (1 + fConst6);
	fConst8 = (0.0082 / fConst7);
	fConst9 = (0 - ((1 - fConst6) / fConst7));
	fConst10 = tan((942.4777960769379 / double(iConst0)));
	fConst11 = (1.0 / faustpower<2>(fConst10));
	fConst12 = (2 * (1 - fConst11));
	fConst13 = (1.0 / fConst10);
	fConst14 = (1 + ((fConst13 - 1.0000000000000004) / fConst10));
	fConst15 = (1.0 / (1 + ((1.0000000000000004 + fConst13) / fConst10)));
	fConst16 = tan((3769.9111843077517 / double(iConst0)));
	fConst17 = (1.0 / faustpower<2>(fConst16));
	fConst18 = (2 * (1 - fConst17));
	fConst19 = (1.0 / fConst16);
	fConst20 = (1 + ((fConst19 - 1.0000000000000004) / fConst16));
	fConst21 = (1 + ((1.0000000000000004 + fConst19) / fConst16));
	fConst22 = (1.0 / fConst21);
	fConst23 = tan((10053.096491487338 / double(iConst0)));
	fConst24 = (1.0 / faustpower<2>(fConst23));
	fConst25 = (2 * (1 - fConst24));
	fConst26 = (1.0 / fConst23);
	fConst27 = (1 + ((fConst26 - 1.0000000000000004) / fConst23));
	fConst28 = (1 + ((1.0000000000000004 + fConst26) / fConst23));
	fConst29 = (1.0 / fConst28);
	fConst30 = tan((47123.8898038469 / double(iConst0)));
	fConst31 = (2 * (1 - (1.0 / faustpower<2>(fConst30))));
	fConst32 = (1.0 / fConst30);
	fConst33 = (1 + ((fConst32 - 1.414213562373095) / fConst30));
	fConst34 = (1 + ((1.414213562373095 + fConst32) / fConst30));
	fConst35 = (1.0 / fConst34);
	fConst36 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst37 = (0 - fConst36);
	fConst38 = (1 + fConst36);
	fConst39 = (1.0 / (fConst38 * fConst34));
	fConst40 = (0 - ((1 - fConst36) / fConst38));
	fConst41 = (1 + fConst26);
	fConst42 = (1.0 / fConst41);
	fConst43 = (0 - ((1 - fConst26) / fConst41));
	fConst44 = (1 + fConst19);
	fConst45 = (1.0 / (fConst44 * fConst28));
	fConst46 = (0 - ((1 - fConst19) / fConst44));
	fConst47 = (1 + fConst13);
	fConst48 = (1.0 / (fConst47 * fConst21));
	fConst49 = (0 - ((1 - fConst13) / fConst47));
	fConst50 = (1 + ((fConst13 - 1.0) / fConst10));
	fConst51 = (1.0 / (1 + ((1.0 + fConst13) / fConst10)));
	fConst52 = (0 - fConst19);
	fConst53 = (2 * (0 - fConst17));
	fConst54 = (1 + ((fConst19 - 1.0) / fConst16));
	fConst55 = (1.0 / (1 + ((1.0 + fConst19) / fConst16)));
	fConst56 = (0 - fConst26);
	fConst57 = (2 * (0 - fConst24));
	fConst58 = (0 - fConst13);
	fConst59 = (2 * (0 - fConst11));
	fConst60 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst61 = (1 + fConst60);
	fConst62 = (1.0 / fConst61);
	fConst63 = (0 - ((1 - fConst60) / fConst61));
	fConst64 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst65 = (1 + fConst64);
	fConst66 = (0.027 / fConst65);
	fConst67 = (0 - ((1 - fConst64) / fConst65));
	fConst68 = (0.05 / fConst38);
	fConst69 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst70 = (1 + fConst69);
	fConst71 = (0.015 / fConst70);
	fConst72 = (0 - ((1 - fConst69) / fConst70));
	fConst73 = (1 + fConst3);
	fConst74 = (1.0 / fConst73);
	fConst75 = (0 - ((1 - fConst3) / fConst73));
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
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider1))));
	double 	fSlow2 = (1.000000000000001e-05 * double(fslider2));
	double 	fSlow3 = double(fslider3);
	double 	fSlow4 = (fConst15 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow5 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow6 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow7 = (fConst15 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow8 = (2 * (fSlow3 - 0.5));
	double 	fSlow9 = (1 - max((double)0, (0 - fSlow8)));
	double 	fSlow10 = (1 - max((double)0, fSlow8));
	double 	fSlow11 = (1.25 * fSlow3);
	for (int i=0; i<ReCount; i++) {
		fRec2[0] = ((0.999 * fRec2[1]) + fSlow0);
		fRec5[0] = ((fConst9 * fRec5[1]) + (fConst8 * (fRec4[1] + fRec4[2])));
		fRec10[0] = ((0.999 * fRec10[1]) + fSlow1);
		fRec22[0] = (fSlow2 + (0.999 * fRec22[1]));
		double fTemp0 = (double)buf[i];
		fRec21[0] = ((fTemp0 * fRec22[0]) - (fConst35 * ((fConst33 * fRec21[2]) + (fConst31 * fRec21[1]))));
		double fTemp1 = (fRec21[2] + (fRec21[0] + (2 * fRec21[1])));
		fVec0[0] = fTemp1;
		fRec20[0] = ((fConst40 * fRec20[1]) + (fConst39 * ((fConst36 * fVec0[0]) + (fConst37 * fVec0[1]))));
		fRec19[0] = ((fConst43 * fRec19[1]) + (fConst42 * (fRec20[0] + fRec20[1])));
		fRec18[0] = (fRec19[0] - (fConst29 * ((fConst27 * fRec18[2]) + (fConst25 * fRec18[1]))));
		double fTemp2 = (fRec18[2] + (fRec18[0] + (2 * fRec18[1])));
		fVec1[0] = fTemp2;
		fRec17[0] = ((fConst46 * fRec17[1]) + (fConst45 * (fVec1[0] + fVec1[1])));
		fRec16[0] = (fRec17[0] - (fConst22 * ((fConst20 * fRec16[2]) + (fConst18 * fRec16[1]))));
		double fTemp3 = (fRec16[2] + (fRec16[0] + (2 * fRec16[1])));
		fVec2[0] = fTemp3;
		fRec15[0] = ((fConst49 * fRec15[1]) + (fConst48 * (fVec2[0] + fVec2[1])));
		fRec14[0] = (fRec15[0] - (fConst15 * ((fConst14 * fRec14[2]) + (fConst12 * fRec14[1]))));
		double fTemp4 = max((double)-1, min((double)1, (fSlow4 * (fRec14[2] + (fRec14[0] + (2 * fRec14[1]))))));
		double fTemp5 = (fConst12 * fRec23[1]);
		fRec25[0] = ((fConst46 * fRec25[1]) + (fConst45 * ((fConst19 * fVec1[0]) + (fConst52 * fVec1[1]))));
		fRec24[0] = (fRec25[0] - (fConst22 * ((fConst20 * fRec24[2]) + (fConst18 * fRec24[1]))));
		fRec23[0] = ((fConst22 * (((fConst17 * fRec24[0]) + (fConst53 * fRec24[1])) + (fConst17 * fRec24[2]))) - (fConst51 * ((fConst50 * fRec23[2]) + fTemp5)));
		double fTemp6 = max((double)-1, min((double)1, (fSlow5 * (fRec23[2] + (fConst51 * (fTemp5 + (fConst50 * fRec23[0])))))));
		double fTemp7 = (fConst12 * fRec26[1]);
		double fTemp8 = (fConst18 * fRec27[1]);
		fRec29[0] = ((fConst43 * fRec29[1]) + (fConst42 * ((fConst26 * fRec20[0]) + (fConst56 * fRec20[1]))));
		fRec28[0] = (fRec29[0] - (fConst29 * ((fConst27 * fRec28[2]) + (fConst25 * fRec28[1]))));
		fRec27[0] = ((fConst29 * (((fConst24 * fRec28[0]) + (fConst57 * fRec28[1])) + (fConst24 * fRec28[2]))) - (fConst55 * ((fConst54 * fRec27[2]) + fTemp8)));
		fRec26[0] = ((fRec27[2] + (fConst55 * (fTemp8 + (fConst54 * fRec27[0])))) - (fConst51 * ((fConst50 * fRec26[2]) + fTemp7)));
		double fTemp9 = max((double)-1, min((double)1, (fSlow6 * (fRec26[2] + (fConst51 * (fTemp7 + (fConst50 * fRec26[0])))))));
		fRec31[0] = ((fConst49 * fRec31[1]) + (fConst48 * ((fConst13 * fVec2[0]) + (fConst58 * fVec2[1]))));
		fRec30[0] = (fRec31[0] - (fConst15 * ((fConst14 * fRec30[2]) + (fConst12 * fRec30[1]))));
		double fTemp10 = max((double)-1, min((double)1, (fSlow7 * (((fConst11 * fRec30[0]) + (fConst59 * fRec30[1])) + (fConst11 * fRec30[2])))));
		double fTemp11 = ((1.584893192 * ((fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10)))) + ((fTemp9 * (1 - (0.3333333333333333 * faustpower<2>(fTemp9)))) + (0.8413951417869425 * (fTemp6 * (1 - (0.3333333333333333 * faustpower<2>(fTemp6)))))))) + (1.2589412 * (fTemp4 * (1 - (0.3333333333333333 * faustpower<2>(fTemp4))))));
		fVec3[0] = fTemp11;
		fRec13[0] = ((fConst63 * fRec13[1]) + (fConst62 * (fVec3[0] + fVec3[1])));
		fRec32[0] = ((fConst67 * fRec32[1]) + (fConst66 * (fRec12[1] + fRec12[2])));
		double fTemp12 = (1 - fRec22[0]);
		fRec12[0] = (Ftube(TUBE_TABLE_6DJ8_68k, (((fTemp0 * ((fTemp12 * (1 + (fSlow11 * ((4 - (4 * fabs((fTemp0 * fTemp12)))) - 1)))) + (fSlow10 * fRec22[0]))) + (fRec32[0] + (fSlow9 * fRec13[0]))) - 1.863946)) - 60.96496296296296);
		fRec11[0] = ((fConst40 * fRec11[1]) + (fConst68 * ((fConst36 * fRec12[0]) + (fConst37 * fRec12[1]))));
		double fTemp13 = (fRec11[0] * fRec10[0]);
		fVec4[0] = fTemp13;
		fRec9[0] = ((fConst63 * fRec9[1]) + (fConst62 * (fVec4[0] + fVec4[1])));
		fRec33[0] = ((fConst72 * fRec33[1]) + (fConst71 * (fRec8[1] + fRec8[2])));
		fRec8[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec33[0] + fRec9[0]) - 1.271609)) - 45.22606666666667);
		fRec7[0] = ((fConst40 * fRec7[1]) + (fConst68 * ((fConst36 * fRec8[0]) + (fConst37 * fRec8[1]))));
		double fTemp14 = (fRec10[0] * fRec7[0]);
		fVec5[0] = fTemp14;
		fRec6[0] = ((fConst63 * fRec6[1]) + (fConst62 * (fVec5[0] + fVec5[1])));
		fRec4[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec6[0] + fRec5[0]) - 0.797043)) - 32.799634146341475);
		fRec3[0] = ((fConst40 * fRec3[1]) + (fConst68 * ((fConst36 * fRec4[0]) + (fConst37 * fRec4[1]))));
		fRec36[0] = ((fConst9 * fRec36[1]) + (fConst8 * (fRec35[1] + fRec35[2])));
		fRec35[0] = (Ftube(TUBE_TABLE_6DJ8_68k, ((fRec36[0] + fRec6[0]) - 0.799031)) - 32.55719512195121);
		fRec34[0] = ((fConst40 * fRec34[1]) + (fConst68 * ((fConst36 * fRec35[0]) + (fConst37 * fRec35[1]))));
		double fTemp15 = ((fRec34[0] + fRec3[0]) * fRec2[0]);
		fVec6[0] = fTemp15;
		fRec1[0] = ((fConst75 * fRec1[1]) + (fConst74 * (fVec6[0] + fVec6[1])));
		fRec0[0] = (fRec1[0] - (fConst5 * ((fConst4 * fRec0[2]) + (fConst2 * fRec0[1]))));
		buf[i] = (FAUSTFLOAT)(fConst5 * (fRec0[2] + (fRec0[0] + (2 * fRec0[1]))));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fVec6[1] = fVec6[0];
		fRec34[1] = fRec34[0];
		fRec35[2] = fRec35[1]; fRec35[1] = fRec35[0];
		fRec36[1] = fRec36[0];
		fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec6[1] = fRec6[0];
		fVec5[1] = fVec5[0];
		fRec7[1] = fRec7[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec33[1] = fRec33[0];
		fRec9[1] = fRec9[0];
		fVec4[1] = fVec4[0];
		fRec11[1] = fRec11[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec32[1] = fRec32[0];
		fRec13[1] = fRec13[0];
		fVec3[1] = fVec3[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec2[1] = fVec2[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fVec1[1] = fVec1[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fVec0[1] = fVec0[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fRec10[1] = fRec10[0];
		fRec5[1] = fRec5[0];
		fRec2[1] = fRec2[0];
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
