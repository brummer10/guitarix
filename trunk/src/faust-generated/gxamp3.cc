// generated from file '../src/faust/gxamp3.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp3 {

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
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec9[2];
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
	double 	fConst31;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec21[2];
	double 	fRec20[3];
	double 	fVec0[2];
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fRec19[2];
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fVec1[2];
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fRec16[2];
	double 	fRec15[3];
	double 	fVec2[2];
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fRec14[2];
	double 	fRec13[3];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fRec24[2];
	double 	fRec23[3];
	double 	fConst49;
	double 	fRec22[3];
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fConst53;
	double 	fRec26[3];
	double 	fRec25[3];
	double 	fConst54;
	double 	fRec30[2];
	double 	fRec29[3];
	double 	fConst55;
	double 	fVec3[2];
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fRec12[2];
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fRec31[2];
	double 	fRec11[3];
	double 	fConst64;
	double 	fRec10[2];
	double 	fVec4[2];
	double 	fConst65;
	double 	fRec8[2];
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fRec32[2];
	double 	fRec7[3];
	double 	fRec6[2];
	double 	fVec5[2];
	double 	fRec5[2];
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;
	double 	fRec33[2];
	double 	fRec4[3];
	double 	fRec3[2];
	double 	fVec6[2];
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
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
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
	fConst6 = tan((942.4777960769379 / double(iConst0)));
	fConst7 = (1.0 / faustpower<2>(fConst6));
	fConst8 = (2 * (1 - fConst7));
	fConst9 = (1.0 / fConst6);
	fConst10 = (1 + ((fConst9 - 1.0000000000000004) / fConst6));
	fConst11 = (1.0 / (1 + ((1.0000000000000004 + fConst9) / fConst6)));
	fConst12 = tan((3769.9111843077517 / double(iConst0)));
	fConst13 = (1.0 / faustpower<2>(fConst12));
	fConst14 = (2 * (1 - fConst13));
	fConst15 = (1.0 / fConst12);
	fConst16 = (1 + ((fConst15 - 1.0000000000000004) / fConst12));
	fConst17 = (1 + ((1.0000000000000004 + fConst15) / fConst12));
	fConst18 = (1.0 / fConst17);
	fConst19 = tan((10053.096491487338 / double(iConst0)));
	fConst20 = (1.0 / faustpower<2>(fConst19));
	fConst21 = (2 * (1 - fConst20));
	fConst22 = (1.0 / fConst19);
	fConst23 = (1 + ((fConst22 - 1.0000000000000004) / fConst19));
	fConst24 = (1 + ((1.0000000000000004 + fConst22) / fConst19));
	fConst25 = (1.0 / fConst24);
	fConst26 = tan((47123.8898038469 / double(iConst0)));
	fConst27 = (2 * (1 - (1.0 / faustpower<2>(fConst26))));
	fConst28 = (1.0 / fConst26);
	fConst29 = (1 + ((fConst28 - 1.414213562373095) / fConst26));
	fConst30 = (1 + ((1.414213562373095 + fConst28) / fConst26));
	fConst31 = (1.0 / fConst30);
	fConst32 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst33 = (0 - fConst32);
	fConst34 = (1 + fConst32);
	fConst35 = (1.0 / (fConst34 * fConst30));
	fConst36 = (0 - ((1 - fConst32) / fConst34));
	fConst37 = (1 + fConst22);
	fConst38 = (1.0 / fConst37);
	fConst39 = (0 - ((1 - fConst22) / fConst37));
	fConst40 = (1 + fConst15);
	fConst41 = (1.0 / (fConst40 * fConst24));
	fConst42 = (0 - ((1 - fConst15) / fConst40));
	fConst43 = (1 + fConst9);
	fConst44 = (1.0 / (fConst43 * fConst17));
	fConst45 = (0 - ((1 - fConst9) / fConst43));
	fConst46 = (1 + ((fConst9 - 1.0) / fConst6));
	fConst47 = (1.0 / (1 + ((1.0 + fConst9) / fConst6)));
	fConst48 = (0 - fConst15);
	fConst49 = (2 * (0 - fConst13));
	fConst50 = (1 + ((fConst15 - 1.0) / fConst12));
	fConst51 = (1.0 / (1 + ((1.0 + fConst15) / fConst12)));
	fConst52 = (0 - fConst22);
	fConst53 = (2 * (0 - fConst20));
	fConst54 = (0 - fConst9);
	fConst55 = (2 * (0 - fConst7));
	fConst56 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst57 = (1 + fConst56);
	fConst58 = (1.0 / fConst57);
	fConst59 = (0 - ((1 - fConst56) / fConst57));
	fConst60 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst61 = (1 + fConst60);
	fConst62 = (0.027 / fConst61);
	fConst63 = (0 - ((1 - fConst60) / fConst61));
	fConst64 = (0.025 / fConst34);
	fConst65 = (2.0 / fConst57);
	fConst66 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst67 = (1 + fConst66);
	fConst68 = (0.015 / fConst67);
	fConst69 = (0 - ((1 - fConst66) / fConst67));
	fConst70 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst71 = (1 + fConst70);
	fConst72 = (0.0082 / fConst71);
	fConst73 = (0 - ((1 - fConst70) / fConst71));
	fConst74 = (1 + fConst3);
	fConst75 = (2.0 / fConst74);
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
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider1))));
	double 	fSlow2 = (1.000000000000001e-05 * double(fslider2));
	double 	fSlow3 = double(fslider3);
	double 	fSlow4 = (fConst11 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow5 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow6 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow7 = (fConst11 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow8 = (2 * (fSlow3 - 0.5));
	double 	fSlow9 = (1 - max((double)0, (0 - fSlow8)));
	double 	fSlow10 = (1 - max((double)0, fSlow8));
	double 	fSlow11 = (1.25 * fSlow3);
	for (int i=0; i<ReCount; i++) {
		fRec2[0] = ((0.999 * fRec2[1]) + fSlow0);
		fRec9[0] = ((0.999 * fRec9[1]) + fSlow1);
		fRec21[0] = (fSlow2 + (0.999 * fRec21[1]));
		double fTemp0 = (double)buf[i];
		fRec20[0] = ((fTemp0 * fRec21[0]) - (fConst31 * ((fConst29 * fRec20[2]) + (fConst27 * fRec20[1]))));
		double fTemp1 = (fRec20[2] + (fRec20[0] + (2 * fRec20[1])));
		fVec0[0] = fTemp1;
		fRec19[0] = ((fConst36 * fRec19[1]) + (fConst35 * ((fConst32 * fVec0[0]) + (fConst33 * fVec0[1]))));
		fRec18[0] = ((fConst39 * fRec18[1]) + (fConst38 * (fRec19[0] + fRec19[1])));
		fRec17[0] = (fRec18[0] - (fConst25 * ((fConst23 * fRec17[2]) + (fConst21 * fRec17[1]))));
		double fTemp2 = (fRec17[2] + (fRec17[0] + (2 * fRec17[1])));
		fVec1[0] = fTemp2;
		fRec16[0] = ((fConst42 * fRec16[1]) + (fConst41 * (fVec1[0] + fVec1[1])));
		fRec15[0] = (fRec16[0] - (fConst18 * ((fConst16 * fRec15[2]) + (fConst14 * fRec15[1]))));
		double fTemp3 = (fRec15[2] + (fRec15[0] + (2 * fRec15[1])));
		fVec2[0] = fTemp3;
		fRec14[0] = ((fConst45 * fRec14[1]) + (fConst44 * (fVec2[0] + fVec2[1])));
		fRec13[0] = (fRec14[0] - (fConst11 * ((fConst10 * fRec13[2]) + (fConst8 * fRec13[1]))));
		double fTemp4 = max((double)-1, min((double)1, (fSlow4 * (fRec13[2] + (fRec13[0] + (2 * fRec13[1]))))));
		double fTemp5 = (fConst8 * fRec22[1]);
		fRec24[0] = ((fConst42 * fRec24[1]) + (fConst41 * ((fConst15 * fVec1[0]) + (fConst48 * fVec1[1]))));
		fRec23[0] = (fRec24[0] - (fConst18 * ((fConst16 * fRec23[2]) + (fConst14 * fRec23[1]))));
		fRec22[0] = ((fConst18 * (((fConst13 * fRec23[0]) + (fConst49 * fRec23[1])) + (fConst13 * fRec23[2]))) - (fConst47 * ((fConst46 * fRec22[2]) + fTemp5)));
		double fTemp6 = max((double)-1, min((double)1, (fSlow5 * (fRec22[2] + (fConst47 * (fTemp5 + (fConst46 * fRec22[0])))))));
		double fTemp7 = (fConst8 * fRec25[1]);
		double fTemp8 = (fConst14 * fRec26[1]);
		fRec28[0] = ((fConst39 * fRec28[1]) + (fConst38 * ((fConst22 * fRec19[0]) + (fConst52 * fRec19[1]))));
		fRec27[0] = (fRec28[0] - (fConst25 * ((fConst23 * fRec27[2]) + (fConst21 * fRec27[1]))));
		fRec26[0] = ((fConst25 * (((fConst20 * fRec27[0]) + (fConst53 * fRec27[1])) + (fConst20 * fRec27[2]))) - (fConst51 * ((fConst50 * fRec26[2]) + fTemp8)));
		fRec25[0] = ((fRec26[2] + (fConst51 * (fTemp8 + (fConst50 * fRec26[0])))) - (fConst47 * ((fConst46 * fRec25[2]) + fTemp7)));
		double fTemp9 = max((double)-1, min((double)1, (fSlow6 * (fRec25[2] + (fConst47 * (fTemp7 + (fConst46 * fRec25[0])))))));
		fRec30[0] = ((fConst45 * fRec30[1]) + (fConst44 * ((fConst9 * fVec2[0]) + (fConst54 * fVec2[1]))));
		fRec29[0] = (fRec30[0] - (fConst11 * ((fConst10 * fRec29[2]) + (fConst8 * fRec29[1]))));
		double fTemp10 = max((double)-1, min((double)1, (fSlow7 * (((fConst7 * fRec29[0]) + (fConst55 * fRec29[1])) + (fConst7 * fRec29[2])))));
		double fTemp11 = ((1.584893192 * ((fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10)))) + ((fTemp9 * (1 - (0.3333333333333333 * faustpower<2>(fTemp9)))) + (0.8413951417869425 * (fTemp6 * (1 - (0.3333333333333333 * faustpower<2>(fTemp6)))))))) + (1.2589412 * (fTemp4 * (1 - (0.3333333333333333 * faustpower<2>(fTemp4))))));
		fVec3[0] = fTemp11;
		fRec12[0] = ((fConst59 * fRec12[1]) + (fConst58 * (fVec3[0] + fVec3[1])));
		fRec31[0] = ((fConst63 * fRec31[1]) + (fConst62 * (fRec11[1] + fRec11[2])));
		double fTemp12 = (1 - fRec21[0]);
		fRec11[0] = (Ftube(TUBE_TABLE_12AU7_68k, (((fTemp0 * ((fTemp12 * (1 + (fSlow11 * ((4 - (4 * fabs((fTemp0 * fTemp12)))) - 1)))) + (fSlow10 * fRec21[0]))) + (fRec31[0] + (fSlow9 * fRec12[0]))) - 3.718962)) - 112.26066666666668);
		fRec10[0] = ((fConst36 * fRec10[1]) + (fConst64 * ((fConst32 * fRec11[0]) + (fConst33 * fRec11[1]))));
		double fTemp13 = (fRec10[0] * fRec9[0]);
		fVec4[0] = fTemp13;
		fRec8[0] = ((fConst59 * fRec8[1]) + (fConst65 * (fVec4[0] + fVec4[1])));
		fRec32[0] = ((fConst69 * fRec32[1]) + (fConst68 * (fRec7[1] + fRec7[2])));
		fRec7[0] = (Ftube(TUBE_TABLE_12AU7_250k, ((fRec32[0] + fRec8[0]) - 2.314844)) - 95.67706666666666);
		fRec6[0] = ((fConst36 * fRec6[1]) + (fConst64 * ((fConst32 * fRec7[0]) + (fConst33 * fRec7[1]))));
		double fTemp14 = (fRec9[0] * fRec6[0]);
		fVec5[0] = fTemp14;
		fRec5[0] = ((fConst59 * fRec5[1]) + (fConst65 * (fVec5[0] + fVec5[1])));
		fRec33[0] = ((fConst73 * fRec33[1]) + (fConst72 * (fRec4[1] + fRec4[2])));
		fRec4[0] = (Ftube(TUBE_TABLE_12AU7_250k, ((fRec33[0] + fRec5[0]) - 1.356567)) - 84.565);
		fRec3[0] = ((fConst36 * fRec3[1]) + (fConst64 * ((fConst32 * fRec4[0]) + (fConst33 * fRec4[1]))));
		double fTemp15 = (fRec3[0] * fRec2[0]);
		fVec6[0] = fTemp15;
		fRec1[0] = ((fConst76 * fRec1[1]) + (fConst75 * (fVec6[0] + fVec6[1])));
		fRec0[0] = (fRec1[0] - (fConst5 * ((fConst4 * fRec0[2]) + (fConst2 * fRec0[1]))));
		buf[i] = (FAUSTFLOAT)(fConst5 * (fRec0[2] + (fRec0[0] + (2 * fRec0[1]))));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fVec6[1] = fVec6[0];
		fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec33[1] = fRec33[0];
		fRec5[1] = fRec5[0];
		fVec5[1] = fVec5[0];
		fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec32[1] = fRec32[0];
		fRec8[1] = fRec8[0];
		fVec4[1] = fVec4[0];
		fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec31[1] = fRec31[0];
		fRec12[1] = fRec12[0];
		fVec3[1] = fVec3[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fVec2[1] = fVec2[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fVec1[1] = fVec1[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fVec0[1] = fVec0[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec9[1] = fRec9[0];
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

} // end namespace gxamp3
