// generated from file '../src/faust/gxamp14.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp14 {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int samplingFreq;
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec11[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec16[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
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
	double 	fRec25[3];
	double 	fVec0[2];
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fRec24[2];
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fVec1[2];
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fRec21[2];
	double 	fRec20[3];
	double 	fVec2[2];
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fRec19[2];
	double 	fRec18[3];
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fConst44;
	double 	fRec26[3];
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fRec32[2];
	double 	fRec31[3];
	double 	fConst48;
	double 	fRec30[3];
	double 	fRec29[3];
	double 	fConst49;
	double 	fRec34[2];
	double 	fRec33[3];
	double 	fConst50;
	double 	fVec3[2];
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	double 	fRec17[2];
	double 	fVec4[2];
	double 	fRec15[2];
	double 	fRec14[3];
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fRec35[2];
	double 	fRec13[3];
	double 	fConst59;
	double 	fRec12[2];
	double 	fVec5[2];
	double 	fRec10[2];
	double 	fRec9[2];
	double 	fRec8[3];
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fRec36[2];
	double 	fRec7[3];
	double 	fRec6[2];
	double 	fVec6[2];
	double 	fRec5[2];
	double 	fRec4[2];
	double 	fRec3[3];
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fRec37[2];
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
	id = "12AT7";
	name = N_("12AT7");
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
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
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
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
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
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = tan((942.4777960769379 / double(iConst0)));
	fConst2 = (1.0 / faustpower<2>(fConst1));
	fConst3 = (2 * (1 - fConst2));
	fConst4 = (1.0 / fConst1);
	fConst5 = (1 + ((fConst4 - 1.0000000000000004) / fConst1));
	fConst6 = (1.0 / (1 + ((1.0000000000000004 + fConst4) / fConst1)));
	fConst7 = tan((3769.9111843077517 / double(iConst0)));
	fConst8 = (1.0 / faustpower<2>(fConst7));
	fConst9 = (2 * (1 - fConst8));
	fConst10 = (1.0 / fConst7);
	fConst11 = (1 + ((fConst10 - 1.0000000000000004) / fConst7));
	fConst12 = (1 + ((1.0000000000000004 + fConst10) / fConst7));
	fConst13 = (1.0 / fConst12);
	fConst14 = tan((10053.096491487338 / double(iConst0)));
	fConst15 = (1.0 / faustpower<2>(fConst14));
	fConst16 = (2 * (1 - fConst15));
	fConst17 = (1.0 / fConst14);
	fConst18 = (1 + ((fConst17 - 1.0000000000000004) / fConst14));
	fConst19 = (1 + ((1.0000000000000004 + fConst17) / fConst14));
	fConst20 = (1.0 / fConst19);
	fConst21 = tan((47123.8898038469 / double(iConst0)));
	fConst22 = (2 * (1 - (1.0 / faustpower<2>(fConst21))));
	fConst23 = (1.0 / fConst21);
	fConst24 = (1 + ((fConst23 - 1.414213562373095) / fConst21));
	fConst25 = (1 + ((1.414213562373095 + fConst23) / fConst21));
	fConst26 = (1.0 / fConst25);
	fConst27 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst28 = (0 - fConst27);
	fConst29 = (1 + fConst27);
	fConst30 = (1.0 / (fConst29 * fConst25));
	fConst31 = (0 - ((1 - fConst27) / fConst29));
	fConst32 = (1 + fConst17);
	fConst33 = (1.0 / fConst32);
	fConst34 = (0 - ((1 - fConst17) / fConst32));
	fConst35 = (1 + fConst10);
	fConst36 = (1.0 / (fConst35 * fConst19));
	fConst37 = (0 - ((1 - fConst10) / fConst35));
	fConst38 = (1 + fConst4);
	fConst39 = (1.0 / (fConst38 * fConst12));
	fConst40 = (0 - ((1 - fConst4) / fConst38));
	fConst41 = (1 + ((fConst4 - 1.0) / fConst1));
	fConst42 = (1.0 / (1 + ((1.0 + fConst4) / fConst1)));
	fConst43 = (0 - fConst10);
	fConst44 = (2 * (0 - fConst8));
	fConst45 = (1 + ((fConst10 - 1.0) / fConst7));
	fConst46 = (1.0 / (1 + ((1.0 + fConst10) / fConst7)));
	fConst47 = (0 - fConst17);
	fConst48 = (2 * (0 - fConst15));
	fConst49 = (0 - fConst4);
	fConst50 = (2 * (0 - fConst2));
	fConst51 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst52 = (1 + fConst51);
	fConst53 = (1.0 / fConst52);
	fConst54 = (0 - ((1 - fConst51) / fConst52));
	fConst55 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst56 = (1 + fConst55);
	fConst57 = (0.027 / fConst56);
	fConst58 = (0 - ((1 - fConst55) / fConst56));
	fConst59 = (0.025 / fConst29);
	fConst60 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst61 = (1 + fConst60);
	fConst62 = (0.015 / fConst61);
	fConst63 = (0 - ((1 - fConst60) / fConst61));
	fConst64 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst65 = (1 + fConst64);
	fConst66 = (0.0082 / fConst65);
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
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider0))));
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider1))));
	double 	fSlow2 = (1.000000000000001e-05 * double(fslider2));
	double 	fSlow3 = double(fslider3);
	double 	fSlow4 = (2 * (fSlow3 - 0.5));
	double 	fSlow5 = (1 - max((double)0, fSlow4));
	double 	fSlow6 = (1.25 * fSlow3);
	double 	fSlow7 = (fConst6 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow8 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow9 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow10 = (fConst6 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow11 = (1 - max((double)0, (0 - fSlow4)));
	for (int i=0; i<ReCount; i++) {
		fRec0[0] = ((0.999 * fRec0[1]) + fSlow0);
		fRec11[0] = ((0.999 * fRec11[1]) + fSlow1);
		fRec16[0] = (fSlow2 + (0.999 * fRec16[1]));
		double fTemp0 = (1 - fRec16[0]);
		double fTemp1 = (double)buf[i];
		fRec25[0] = ((fTemp1 * fRec16[0]) - (fConst26 * ((fConst24 * fRec25[2]) + (fConst22 * fRec25[1]))));
		double fTemp2 = (fRec25[2] + (fRec25[0] + (2 * fRec25[1])));
		fVec0[0] = fTemp2;
		fRec24[0] = ((fConst31 * fRec24[1]) + (fConst30 * ((fConst27 * fVec0[0]) + (fConst28 * fVec0[1]))));
		fRec23[0] = ((fConst34 * fRec23[1]) + (fConst33 * (fRec24[0] + fRec24[1])));
		fRec22[0] = (fRec23[0] - (fConst20 * ((fConst18 * fRec22[2]) + (fConst16 * fRec22[1]))));
		double fTemp3 = (fRec22[2] + (fRec22[0] + (2 * fRec22[1])));
		fVec1[0] = fTemp3;
		fRec21[0] = ((fConst37 * fRec21[1]) + (fConst36 * (fVec1[0] + fVec1[1])));
		fRec20[0] = (fRec21[0] - (fConst13 * ((fConst11 * fRec20[2]) + (fConst9 * fRec20[1]))));
		double fTemp4 = (fRec20[2] + (fRec20[0] + (2 * fRec20[1])));
		fVec2[0] = fTemp4;
		fRec19[0] = ((fConst40 * fRec19[1]) + (fConst39 * (fVec2[0] + fVec2[1])));
		fRec18[0] = (fRec19[0] - (fConst6 * ((fConst5 * fRec18[2]) + (fConst3 * fRec18[1]))));
		double fTemp5 = max((double)-1, min((double)1, (fSlow7 * (fRec18[2] + (fRec18[0] + (2 * fRec18[1]))))));
		double fTemp6 = (fConst3 * fRec26[1]);
		fRec28[0] = ((fConst37 * fRec28[1]) + (fConst36 * ((fConst10 * fVec1[0]) + (fConst43 * fVec1[1]))));
		fRec27[0] = (fRec28[0] - (fConst13 * ((fConst11 * fRec27[2]) + (fConst9 * fRec27[1]))));
		fRec26[0] = ((fConst13 * (((fConst8 * fRec27[0]) + (fConst44 * fRec27[1])) + (fConst8 * fRec27[2]))) - (fConst42 * ((fConst41 * fRec26[2]) + fTemp6)));
		double fTemp7 = max((double)-1, min((double)1, (fSlow8 * (fRec26[2] + (fConst42 * (fTemp6 + (fConst41 * fRec26[0])))))));
		double fTemp8 = (fConst3 * fRec29[1]);
		double fTemp9 = (fConst9 * fRec30[1]);
		fRec32[0] = ((fConst34 * fRec32[1]) + (fConst33 * ((fConst17 * fRec24[0]) + (fConst47 * fRec24[1]))));
		fRec31[0] = (fRec32[0] - (fConst20 * ((fConst18 * fRec31[2]) + (fConst16 * fRec31[1]))));
		fRec30[0] = ((fConst20 * (((fConst15 * fRec31[0]) + (fConst48 * fRec31[1])) + (fConst15 * fRec31[2]))) - (fConst46 * ((fConst45 * fRec30[2]) + fTemp9)));
		fRec29[0] = ((fRec30[2] + (fConst46 * (fTemp9 + (fConst45 * fRec30[0])))) - (fConst42 * ((fConst41 * fRec29[2]) + fTemp8)));
		double fTemp10 = max((double)-1, min((double)1, (fSlow9 * (fRec29[2] + (fConst42 * (fTemp8 + (fConst41 * fRec29[0])))))));
		fRec34[0] = ((fConst40 * fRec34[1]) + (fConst39 * ((fConst4 * fVec2[0]) + (fConst49 * fVec2[1]))));
		fRec33[0] = (fRec34[0] - (fConst6 * ((fConst5 * fRec33[2]) + (fConst3 * fRec33[1]))));
		double fTemp11 = max((double)-1, min((double)1, (fSlow10 * (((fConst2 * fRec33[0]) + (fConst50 * fRec33[1])) + (fConst2 * fRec33[2])))));
		double fTemp12 = ((1.584893192 * ((fTemp11 * (1 - (0.3333333333333333 * faustpower<2>(fTemp11)))) + ((fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10)))) + (0.8413951417869425 * (fTemp7 * (1 - (0.3333333333333333 * faustpower<2>(fTemp7)))))))) + (1.2589412 * (fTemp5 * (1 - (0.3333333333333333 * faustpower<2>(fTemp5))))));
		fVec3[0] = fTemp12;
		fRec17[0] = ((fConst54 * fRec17[1]) + (fConst53 * (fVec3[0] + fVec3[1])));
		double fTemp13 = ((fSlow11 * fRec17[0]) + (fTemp1 * ((fTemp0 * (1 + (fSlow6 * ((4 - (4 * fabs((fTemp1 * fTemp0)))) - 1)))) + (fSlow5 * fRec16[0]))));
		fVec4[0] = fTemp13;
		fRec15[0] = ((0.9302847925323914 * (fVec4[0] + fVec4[1])) - (0.8605695850647829 * fRec15[1]));
		fRec14[0] = (fRec15[0] - ((1.8405051250752198 * fRec14[1]) + (0.8612942439318627 * fRec14[2])));
		fRec35[0] = ((fConst58 * fRec35[1]) + (fConst57 * (fRec13[1] + fRec13[2])));
		fRec13[0] = (Ftube(TUBE_TABLE_12AT7_68k, ((fRec35[0] + (0.9254498422517706 * (fRec14[2] + (fRec14[0] + (2.0 * fRec14[1]))))) - 2.617753)) - 153.04618518518518);
		fRec12[0] = ((fConst31 * fRec12[1]) + (fConst59 * ((fConst27 * fRec13[0]) + (fConst28 * fRec13[1]))));
		double fTemp14 = (fRec12[0] * fRec11[0]);
		fVec5[0] = fTemp14;
		fRec10[0] = ((fConst54 * fRec10[1]) + (fConst53 * (fVec5[0] + fVec5[1])));
		fRec9[0] = ((0.9302847925323914 * (fRec10[0] + fRec10[1])) - (0.8605695850647829 * fRec9[1]));
		fRec8[0] = (fRec9[0] - ((1.8405051250752198 * fRec8[1]) + (0.8612942439318627 * fRec8[2])));
		fRec36[0] = ((fConst63 * fRec36[1]) + (fConst62 * (fRec7[1] + fRec7[2])));
		fRec7[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec36[0] + (0.9254498422517706 * (fRec8[2] + (fRec8[0] + (2.0 * fRec8[1]))))) - 1.887332)) - 124.17786666666666);
		fRec6[0] = ((fConst31 * fRec6[1]) + (fConst59 * ((fConst27 * fRec7[0]) + (fConst28 * fRec7[1]))));
		double fTemp15 = (fRec11[0] * fRec6[0]);
		fVec6[0] = fTemp15;
		fRec5[0] = ((fConst54 * fRec5[1]) + (fConst53 * (fVec6[0] + fVec6[1])));
		fRec4[0] = ((0.9302847925323914 * (fRec5[0] + fRec5[1])) - (0.8605695850647829 * fRec4[1]));
		fRec3[0] = (fRec4[0] - ((1.8405051250752198 * fRec3[1]) + (0.8612942439318627 * fRec3[2])));
		fRec37[0] = ((fConst67 * fRec37[1]) + (fConst66 * (fRec2[1] + fRec2[2])));
		fRec2[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec37[0] + (0.9254498422517706 * (fRec3[2] + (fRec3[0] + (2.0 * fRec3[1]))))) - 1.256962)) - 96.7119512195122);
		fRec1[0] = ((fConst31 * fRec1[1]) + (fConst59 * ((fConst27 * fRec2[0]) + (fConst28 * fRec2[1]))));
		buf[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec37[1] = fRec37[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec6[1] = fVec6[0];
		fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec36[1] = fRec36[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fVec5[1] = fVec5[0];
		fRec12[1] = fRec12[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec35[1] = fRec35[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec4[1] = fVec4[0];
		fRec17[1] = fRec17[0];
		fVec3[1] = fVec3[0];
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
		fVec2[1] = fVec2[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fVec1[1] = fVec1[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fVec0[1] = fVec0[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec16[1] = fRec16[0];
		fRec11[1] = fRec11[0];
		fRec0[1] = fRec0[0];
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

} // end namespace gxamp14
