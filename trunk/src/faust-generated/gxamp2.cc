// generated from file '../src/faust/gxamp2.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp2 {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec10[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
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
	double 	fConst27;
	double 	fConst28;
	double 	fRec19[3];
	double 	fVec0[2];
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fRec18[2];
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fRec17[2];
	double 	fRec16[3];
	double 	fVec1[2];
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fRec15[2];
	double 	fRec14[3];
	double 	fVec2[2];
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fRec13[2];
	double 	fRec12[3];
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fRec22[2];
	double 	fRec21[3];
	double 	fConst46;
	double 	fRec20[3];
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fRec26[2];
	double 	fRec25[3];
	double 	fConst50;
	double 	fRec24[3];
	double 	fRec23[3];
	double 	fConst51;
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fConst52;
	double 	fVec3[2];
	double 	fConst53;
	double 	fConst54;
	double 	fConst55;
	double 	fConst56;
	double 	fRec11[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec29[2];
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fRec30[2];
	double 	fRec9[3];
	double 	fConst61;
	double 	fRec8[2];
	double 	fConst62;
	double 	fRec7[2];
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fRec31[2];
	double 	fRec6[3];
	double 	fRec5[2];
	double 	fRec4[2];
	double 	fRec2[3];
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;
	double 	fRec32[2];
	double 	fRec1[3];
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
	id = "6V6";
	name = N_("6V6");
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
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = log((7539.822368615503 / double(iConst0)));
	fConst2 = (0 - (1.8442 * cos(exp((0.07238887 + (fConst1 * (1.31282248 + (fConst1 * (0.43359433 + (fConst1 * (0.27547621 + (fConst1 * (0.06446806 + (0.00506158 * fConst1))))))))))))));
	fConst3 = tan((942.4777960769379 / double(iConst0)));
	fConst4 = (1.0 / faustpower<2>(fConst3));
	fConst5 = (2 * (1 - fConst4));
	fConst6 = (1.0 / fConst3);
	fConst7 = (1 + ((fConst6 - 1.0000000000000004) / fConst3));
	fConst8 = (1.0 / (1 + ((fConst6 + 1.0000000000000004) / fConst3)));
	fConst9 = tan((3769.9111843077517 / double(iConst0)));
	fConst10 = (1.0 / faustpower<2>(fConst9));
	fConst11 = (2 * (1 - fConst10));
	fConst12 = (1.0 / fConst9);
	fConst13 = (1 + ((fConst12 - 1.0000000000000004) / fConst9));
	fConst14 = (1 + ((fConst12 + 1.0000000000000004) / fConst9));
	fConst15 = (1.0 / fConst14);
	fConst16 = tan((10053.096491487338 / double(iConst0)));
	fConst17 = (1.0 / faustpower<2>(fConst16));
	fConst18 = (2 * (1 - fConst17));
	fConst19 = (1.0 / fConst16);
	fConst20 = (1 + ((fConst19 - 1.0000000000000004) / fConst16));
	fConst21 = (1 + ((1.0000000000000004 + fConst19) / fConst16));
	fConst22 = (1.0 / fConst21);
	fConst23 = tan((47123.8898038469 / double(iConst0)));
	fConst24 = (2 * (1 - (1.0 / faustpower<2>(fConst23))));
	fConst25 = (1.0 / fConst23);
	fConst26 = (1 + ((fConst25 - 1.414213562373095) / fConst23));
	fConst27 = (1 + ((1.414213562373095 + fConst25) / fConst23));
	fConst28 = (1.0 / fConst27);
	fConst29 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst30 = (0 - fConst29);
	fConst31 = (1 + fConst29);
	fConst32 = (1.0 / (fConst31 * fConst27));
	fConst33 = (0 - ((1 - fConst29) / fConst31));
	fConst34 = (1 + fConst19);
	fConst35 = (1.0 / fConst34);
	fConst36 = (0 - ((1 - fConst19) / fConst34));
	fConst37 = (1 + fConst12);
	fConst38 = (1.0 / (fConst37 * fConst21));
	fConst39 = (0 - ((1 - fConst12) / fConst37));
	fConst40 = (1 + fConst6);
	fConst41 = (1.0 / (fConst40 * fConst14));
	fConst42 = (0 - ((1 - fConst6) / fConst40));
	fConst43 = (1 + ((fConst6 - 1.0) / fConst3));
	fConst44 = (1.0 / (1 + ((1.0 + fConst6) / fConst3)));
	fConst45 = (0 - fConst12);
	fConst46 = (2 * (0 - fConst10));
	fConst47 = (1 + ((fConst12 - 1.0) / fConst9));
	fConst48 = (1.0 / (1 + ((1.0 + fConst12) / fConst9)));
	fConst49 = (0 - fConst19);
	fConst50 = (2 * (0 - fConst17));
	fConst51 = (0 - fConst6);
	fConst52 = (2 * (0 - fConst4));
	fConst53 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst54 = (1 + fConst53);
	fConst55 = (1.0 / fConst54);
	fConst56 = (0 - ((1 - fConst53) / fConst54));
	fConst57 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst58 = (1 + fConst57);
	fConst59 = (0.027 / fConst58);
	fConst60 = (0 - ((1 - fConst57) / fConst58));
	fConst61 = (0.025 / fConst31);
	fConst62 = (0.77 / fConst54);
	fConst63 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst64 = (1 + fConst63);
	fConst65 = (0.015 / fConst64);
	fConst66 = (0 - ((1 - fConst63) / fConst64));
	fConst67 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst68 = (1 + fConst67);
	fConst69 = (0.0082 / fConst68);
	fConst70 = (0 - ((1 - fConst67) / fConst68));
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
	double 	fSlow1 = (1.000000000000001e-05 * double(fslider1));
	double 	fSlow2 = double(fslider2);
	double 	fSlow3 = (2 * (fSlow2 - 0.5));
	double 	fSlow4 = (1 - max((double)0, fSlow3));
	double 	fSlow5 = (1.25 * fSlow2);
	double 	fSlow6 = (fConst8 * pow(1e+01,(0.9 * fSlow2)));
	double 	fSlow7 = pow(1e+01,(1.2 * fSlow2));
	double 	fSlow8 = pow(1e+01,(0.8 * fSlow2));
	double 	fSlow9 = (fConst8 * pow(1e+01,(2 * fSlow2)));
	double 	fSlow10 = (1 - max((double)0, (0 - fSlow3)));
	double 	fSlow11 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider3))));
	for (int i=0; i<count; i++) {
		fRec3[0] = ((0.999 * fRec3[1]) + fSlow0);
		fRec10[0] = (fSlow1 + (0.999 * fRec10[1]));
		double fTemp0 = (1 - fRec10[0]);
		double fTemp1 = (double)input0[i];
		fRec19[0] = ((fTemp1 * fRec10[0]) - (fConst28 * ((fConst26 * fRec19[2]) + (fConst24 * fRec19[1]))));
		double fTemp2 = (fRec19[2] + (fRec19[0] + (2 * fRec19[1])));
		fVec0[0] = fTemp2;
		fRec18[0] = ((fConst33 * fRec18[1]) + (fConst32 * ((fConst29 * fVec0[0]) + (fConst30 * fVec0[1]))));
		fRec17[0] = ((fConst36 * fRec17[1]) + (fConst35 * (fRec18[0] + fRec18[1])));
		fRec16[0] = (fRec17[0] - (fConst22 * ((fConst20 * fRec16[2]) + (fConst18 * fRec16[1]))));
		double fTemp3 = (fRec16[2] + (fRec16[0] + (2 * fRec16[1])));
		fVec1[0] = fTemp3;
		fRec15[0] = ((fConst39 * fRec15[1]) + (fConst38 * (fVec1[0] + fVec1[1])));
		fRec14[0] = (fRec15[0] - (fConst15 * ((fConst13 * fRec14[2]) + (fConst11 * fRec14[1]))));
		double fTemp4 = (fRec14[2] + (fRec14[0] + (2 * fRec14[1])));
		fVec2[0] = fTemp4;
		fRec13[0] = ((fConst42 * fRec13[1]) + (fConst41 * (fVec2[0] + fVec2[1])));
		fRec12[0] = (fRec13[0] - (fConst8 * ((fConst7 * fRec12[2]) + (fConst5 * fRec12[1]))));
		double fTemp5 = max((double)-1, min((double)1, (fSlow6 * (fRec12[2] + (fRec12[0] + (2 * fRec12[1]))))));
		double fTemp6 = (fConst5 * fRec20[1]);
		fRec22[0] = ((fConst39 * fRec22[1]) + (fConst38 * ((fConst12 * fVec1[0]) + (fConst45 * fVec1[1]))));
		fRec21[0] = (fRec22[0] - (fConst15 * ((fConst13 * fRec21[2]) + (fConst11 * fRec21[1]))));
		fRec20[0] = ((fConst15 * (((fConst10 * fRec21[0]) + (fConst46 * fRec21[1])) + (fConst10 * fRec21[2]))) - (fConst44 * ((fConst43 * fRec20[2]) + fTemp6)));
		double fTemp7 = max((double)-1, min((double)1, (fSlow7 * (fRec20[2] + (fConst44 * (fTemp6 + (fConst43 * fRec20[0])))))));
		double fTemp8 = (fConst5 * fRec23[1]);
		double fTemp9 = (fConst11 * fRec24[1]);
		fRec26[0] = ((fConst36 * fRec26[1]) + (fConst35 * ((fConst19 * fRec18[0]) + (fConst49 * fRec18[1]))));
		fRec25[0] = (fRec26[0] - (fConst22 * ((fConst20 * fRec25[2]) + (fConst18 * fRec25[1]))));
		fRec24[0] = ((fConst22 * (((fConst17 * fRec25[0]) + (fConst50 * fRec25[1])) + (fConst17 * fRec25[2]))) - (fConst48 * ((fConst47 * fRec24[2]) + fTemp9)));
		fRec23[0] = ((fRec24[2] + (fConst48 * (fTemp9 + (fConst47 * fRec24[0])))) - (fConst44 * ((fConst43 * fRec23[2]) + fTemp8)));
		double fTemp10 = max((double)-1, min((double)1, (fSlow8 * (fRec23[2] + (fConst44 * (fTemp8 + (fConst43 * fRec23[0])))))));
		fRec28[0] = ((fConst42 * fRec28[1]) + (fConst41 * ((fConst6 * fVec2[0]) + (fConst51 * fVec2[1]))));
		fRec27[0] = (fRec28[0] - (fConst8 * ((fConst7 * fRec27[2]) + (fConst5 * fRec27[1]))));
		double fTemp11 = max((double)-1, min((double)1, (fSlow9 * (((fConst4 * fRec27[0]) + (fConst52 * fRec27[1])) + (fConst4 * fRec27[2])))));
		double fTemp12 = ((1.584893192 * ((fTemp11 * (1 - (0.3333333333333333 * faustpower<2>(fTemp11)))) + ((fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10)))) + (0.8413951417869425 * (fTemp7 * (1 - (0.3333333333333333 * faustpower<2>(fTemp7)))))))) + (1.2589412 * (fTemp5 * (1 - (0.3333333333333333 * faustpower<2>(fTemp5))))));
		fVec3[0] = fTemp12;
		fRec11[0] = ((fConst56 * fRec11[1]) + (fConst55 * (fVec3[0] + fVec3[1])));
		fRec29[0] = ((0.999 * fRec29[1]) + fSlow11);
		fRec30[0] = ((fConst60 * fRec30[1]) + (fConst59 * (fRec9[1] + fRec9[2])));
		fRec9[0] = (Ftube(TUBE_TABLE_6V6_68k, ((fRec30[0] + (fRec29[0] * ((fSlow10 * fRec11[0]) + (fTemp1 * ((fTemp0 * (1 + (fSlow5 * ((4 - (4 * fabs((fTemp1 * fTemp0)))) - 1)))) + (fSlow4 * fRec10[0])))))) - 2.29615)) - 164.9574074074074);
		fRec8[0] = ((fConst33 * fRec8[1]) + (fConst61 * ((fConst29 * fRec9[0]) + (fConst30 * fRec9[1]))));
		fRec7[0] = ((fConst56 * fRec7[1]) + (fConst62 * (fRec8[0] + fRec8[1])));
		fRec31[0] = ((fConst66 * fRec31[1]) + (fConst65 * (fRec6[1] + fRec6[2])));
		fRec6[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec31[0] + (fRec29[0] * fRec7[0])) - 1.675587)) - 138.2942);
		fRec5[0] = ((fConst33 * fRec5[1]) + (fConst61 * ((fConst29 * fRec6[0]) + (fConst30 * fRec6[1]))));
		fRec4[0] = ((fConst56 * fRec4[1]) + (fConst62 * (fRec5[0] + fRec5[1])));
		fRec2[0] = ((fRec4[0] * fRec3[0]) - ((fConst2 * fRec2[1]) + (0.8502684100000001 * fRec2[2])));
		fRec32[0] = ((fConst70 * fRec32[1]) + (fConst69 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec32[0] + fRec2[0]) - (1.130462 + (1.059 * fRec2[1])))) - 112.13878048780487);
		fRec0[0] = ((fConst33 * fRec0[1]) + (fConst61 * ((fConst29 * fRec1[0]) + (fConst30 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)(0.77 * fRec0[0]);
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec32[1] = fRec32[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec31[1] = fRec31[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec30[1] = fRec30[0];
		fRec29[1] = fRec29[0];
		fRec11[1] = fRec11[0];
		fVec3[1] = fVec3[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fVec2[1] = fVec2[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec1[1] = fVec1[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fVec0[1] = fVec0[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec10[1] = fRec10[0];
		fRec3[1] = fRec3[0];
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

} // end namespace gxamp2
