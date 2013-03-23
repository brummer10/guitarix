// generated from file '../src/LV2/faust/gxamp2.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp2 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec3[2];
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec10[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
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
	double 	fConst37;
	double 	fConst38;
	double 	fRec18[3];
	double 	fVec0[2];
	double 	fConst39;
	double 	fConst40;
	double 	fRec17[2];
	double 	fConst41;
	double 	fRec16[2];
	double 	fRec15[3];
	double 	fVec1[2];
	double 	fConst42;
	double 	fConst43;
	double 	fRec14[2];
	double 	fRec13[3];
	double 	fConst44;
	double 	fRec12[3];
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fRec22[2];
	double 	fRec21[3];
	double 	fVec2[2];
	double 	fConst49;
	double 	fConst50;
	double 	fRec20[2];
	double 	fRec19[3];
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	double 	fRec26[2];
	double 	fRec25[3];
	double 	fConst55;
	double 	fRec24[3];
	double 	fRec23[3];
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fVec3[2];
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
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, float *input0, float *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, float *input0, float *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "6V6";
	name = N_("6V6");
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
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

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / tan((97.38937226128358 / iConst0)));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = log((7539.822368615503 / iConst0));
	fConst5 = (0 - (1.8442 * cos(exp((0.07238887 + (fConst4 * (1.31282248 + (fConst4 * (0.43359433 + (fConst4 * (0.27547621 + (fConst4 * (0.06446806 + (0.00506158 * fConst4))))))))))))));
	fConst6 = (1.0 / tan((20517.741620594938 / iConst0)));
	fConst7 = (1 + fConst6);
	fConst8 = (0 - ((1 - fConst6) / fConst7));
	fConst9 = tan((942.4777960769379 / iConst0));
	fConst10 = (1.0 / faustpower<2>(fConst9));
	fConst11 = (2 * (1 - fConst10));
	fConst12 = (1.0 / fConst9);
	fConst13 = (1 + ((fConst12 - 1.0) / fConst9));
	fConst14 = (1.0 / (1 + ((1.0 + fConst12) / fConst9)));
	fConst15 = tan((3769.9111843077517 / iConst0));
	fConst16 = (1.0 / faustpower<2>(fConst15));
	fConst17 = (2 * (1 - fConst16));
	fConst18 = (1.0 / fConst15);
	fConst19 = (1 + ((fConst18 - 1.0000000000000004) / fConst15));
	fConst20 = (1 + ((fConst18 + 1.0000000000000004) / fConst15));
	fConst21 = (1.0 / fConst20);
	fConst22 = (1 + fConst18);
	fConst23 = (0 - ((1 - fConst18) / fConst22));
	fConst24 = tan((10053.096491487338 / iConst0));
	fConst25 = (1.0 / faustpower<2>(fConst24));
	fConst26 = (2 * (1 - fConst25));
	fConst27 = (1.0 / fConst24);
	fConst28 = (1 + ((fConst27 - 1.0000000000000004) / fConst24));
	fConst29 = (1 + ((1.0000000000000004 + fConst27) / fConst24));
	fConst30 = (1.0 / fConst29);
	fConst31 = (1 + fConst27);
	fConst32 = (0 - ((1 - fConst27) / fConst31));
	fConst33 = tan((47123.8898038469 / iConst0));
	fConst34 = (2 * (1 - (1.0 / faustpower<2>(fConst33))));
	fConst35 = (1.0 / fConst33);
	fConst36 = (1 + ((fConst35 - 1.414213562373095) / fConst33));
	fConst37 = (1 + ((1.414213562373095 + fConst35) / fConst33));
	fConst38 = (1.0 / fConst37);
	fConst39 = (0 - fConst1);
	fConst40 = (1.0 / (fConst2 * fConst37));
	fConst41 = (1.0 / fConst31);
	fConst42 = (0 - fConst18);
	fConst43 = (1.0 / (fConst22 * fConst29));
	fConst44 = (2 * (0 - fConst16));
	fConst45 = (1 + ((fConst12 - 1.0000000000000004) / fConst9));
	fConst46 = (1.0 / (1 + ((fConst12 + 1.0000000000000004) / fConst9)));
	fConst47 = (1 + fConst12);
	fConst48 = (0 - ((1 - fConst12) / fConst47));
	fConst49 = (0 - fConst12);
	fConst50 = (1.0 / (fConst47 * fConst20));
	fConst51 = (2 * (0 - fConst10));
	fConst52 = (1 + ((fConst18 - 1.0) / fConst15));
	fConst53 = (1.0 / (1 + ((1.0 + fConst18) / fConst15)));
	fConst54 = (0 - fConst27);
	fConst55 = (2 * (0 - fConst25));
	fConst56 = (1.0 / fConst7);
	fConst57 = (1.0 / tan((270.1769682087222 / iConst0)));
	fConst58 = (1 + fConst57);
	fConst59 = (0 - ((1 - fConst57) / fConst58));
	fConst60 = (0.027 / fConst58);
	fConst61 = (0.025 / fConst2);
	fConst62 = (0.77 / fConst7);
	fConst63 = (1.0 / tan((414.6902302738527 / iConst0)));
	fConst64 = (1 + fConst63);
	fConst65 = (0 - ((1 - fConst63) / fConst64));
	fConst66 = (0.015 / fConst64);
	fConst67 = (1.0 / tan((609.4689747964198 / iConst0)));
	fConst68 = (1 + fConst67);
	fConst69 = (0 - ((1 - fConst67) / fConst68));
	fConst70 = (0.0082 / fConst68);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
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
	double 	fSlow1 = (1.000000000000001e-05 * fslider1);
	double 	fSlow2 = fslider2;
	double 	fSlow3 = (1.25 * fSlow2);
	double 	fSlow4 = (2 * (fSlow2 - 0.5));
	double 	fSlow5 = (1 - max(0, fSlow4));
	double 	fSlow6 = pow(1e+01,(1.2 * fSlow2));
	double 	fSlow7 = (fConst46 * pow(1e+01,(2 * fSlow2)));
	double 	fSlow8 = pow(1e+01,(0.8 * fSlow2));
	double 	fSlow9 = (fConst46 * pow(1e+01,(0.9 * fSlow2)));
	double 	fSlow10 = (1 - max(0, (0 - fSlow4)));
	double 	fSlow11 = (0.0010000000000000009 * pow(10,(0.05 * fslider3)));
	for (int i=0; i<count; i++) {
		fRec3[0] = (fSlow0 + (0.999 * fRec3[1]));
		fRec10[0] = (fSlow1 + (0.999 * fRec10[1]));
		double fTemp0 = (1 - fRec10[0]);
		double fTemp1 = (double)input0[i];
		double fTemp2 = (fConst11 * fRec12[1]);
		fRec18[0] = ((fTemp1 * fRec10[0]) - (fConst38 * ((fConst36 * fRec18[2]) + (fConst34 * fRec18[1]))));
		double fTemp3 = (fRec18[2] + (fRec18[0] + (2 * fRec18[1])));
		fVec0[0] = fTemp3;
		fRec17[0] = ((fConst40 * ((fConst39 * fVec0[1]) + (fConst1 * fVec0[0]))) + (fConst3 * fRec17[1]));
		fRec16[0] = ((fConst41 * (fRec17[0] + fRec17[1])) + (fConst32 * fRec16[1]));
		fRec15[0] = (fRec16[0] - (fConst30 * ((fConst28 * fRec15[2]) + (fConst26 * fRec15[1]))));
		double fTemp4 = (fRec15[2] + (fRec15[0] + (2 * fRec15[1])));
		fVec1[0] = fTemp4;
		fRec14[0] = ((fConst43 * ((fConst42 * fVec1[1]) + (fConst18 * fVec1[0]))) + (fConst23 * fRec14[1]));
		fRec13[0] = (fRec14[0] - (fConst21 * ((fConst19 * fRec13[2]) + (fConst17 * fRec13[1]))));
		fRec12[0] = ((fConst21 * (((fConst16 * fRec13[0]) + (fConst44 * fRec13[1])) + (fConst16 * fRec13[2]))) - (fConst14 * ((fConst13 * fRec12[2]) + fTemp2)));
		double fTemp5 = max(-1, min(1, (fSlow6 * (fRec12[2] + (fConst14 * (fTemp2 + (fConst13 * fRec12[0])))))));
		fRec22[0] = ((fConst43 * (fVec1[0] + fVec1[1])) + (fConst23 * fRec22[1]));
		fRec21[0] = (fRec22[0] - (fConst21 * ((fConst19 * fRec21[2]) + (fConst17 * fRec21[1]))));
		double fTemp6 = (fRec21[2] + (fRec21[0] + (2 * fRec21[1])));
		fVec2[0] = fTemp6;
		fRec20[0] = ((fConst50 * ((fConst49 * fVec2[1]) + (fConst12 * fVec2[0]))) + (fConst48 * fRec20[1]));
		fRec19[0] = (fRec20[0] - (fConst46 * ((fConst45 * fRec19[2]) + (fConst11 * fRec19[1]))));
		double fTemp7 = max(-1, min(1, (fSlow7 * (((fConst10 * fRec19[0]) + (fConst51 * fRec19[1])) + (fConst10 * fRec19[2])))));
		double fTemp8 = (fConst11 * fRec23[1]);
		double fTemp9 = (fConst17 * fRec24[1]);
		fRec26[0] = ((fConst41 * ((fConst54 * fRec17[1]) + (fConst27 * fRec17[0]))) + (fConst32 * fRec26[1]));
		fRec25[0] = (fRec26[0] - (fConst30 * ((fConst28 * fRec25[2]) + (fConst26 * fRec25[1]))));
		fRec24[0] = ((fConst30 * (((fConst25 * fRec25[0]) + (fConst55 * fRec25[1])) + (fConst25 * fRec25[2]))) - (fConst53 * ((fConst52 * fRec24[2]) + fTemp9)));
		fRec23[0] = ((fRec24[2] + (fConst53 * (fTemp9 + (fConst52 * fRec24[0])))) - (fConst14 * ((fConst13 * fRec23[2]) + fTemp8)));
		double fTemp10 = max(-1, min(1, (fSlow8 * (fRec23[2] + (fConst14 * (fTemp8 + (fConst13 * fRec23[0])))))));
		fRec28[0] = ((fConst50 * (fVec2[0] + fVec2[1])) + (fConst48 * fRec28[1]));
		fRec27[0] = (fRec28[0] - (fConst46 * ((fConst45 * fRec27[2]) + (fConst11 * fRec27[1]))));
		double fTemp11 = max(-1, min(1, (fSlow9 * (fRec27[2] + (fRec27[0] + (2 * fRec27[1]))))));
		double fTemp12 = ((1.2589412 * (fTemp11 * (1 - (0.3333333333333333 * faustpower<2>(fTemp11))))) + (1.584893192 * ((fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10)))) + ((fTemp7 * (1 - (0.3333333333333333 * faustpower<2>(fTemp7)))) + (0.8413951417869425 * (fTemp5 * (1 - (0.3333333333333333 * faustpower<2>(fTemp5)))))))));
		fVec3[0] = fTemp12;
		fRec11[0] = ((fConst56 * (fVec3[0] + fVec3[1])) + (fConst8 * fRec11[1]));
		fRec29[0] = (fSlow11 + (0.999 * fRec29[1]));
		fRec30[0] = ((fConst60 * (fRec9[1] + fRec9[2])) + (fConst59 * fRec30[1]));
		fRec9[0] = (Ftube(TUBE_TABLE_6V6_68k, ((fRec30[0] + (fRec29[0] * ((fSlow10 * fRec11[0]) + (fTemp1 * ((fSlow5 * fRec10[0]) + (fTemp0 * (1 + (fSlow3 * ((4 - (4 * fabs((fTemp1 * fTemp0)))) - 1))))))))) - 2.29615)) - 164.9574074074074);
		fRec8[0] = ((fConst61 * ((fConst39 * fRec9[1]) + (fConst1 * fRec9[0]))) + (fConst3 * fRec8[1]));
		fRec7[0] = ((fConst62 * (fRec8[0] + fRec8[1])) + (fConst8 * fRec7[1]));
		fRec31[0] = ((fConst66 * (fRec6[1] + fRec6[2])) + (fConst65 * fRec31[1]));
		fRec6[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec31[0] + (fRec29[0] * fRec7[0])) - 1.675587)) - 138.2942);
		fRec5[0] = ((fConst61 * ((fConst39 * fRec6[1]) + (fConst1 * fRec6[0]))) + (fConst3 * fRec5[1]));
		fRec4[0] = ((fConst62 * (fRec5[0] + fRec5[1])) + (fConst8 * fRec4[1]));
		fRec2[0] = ((fRec4[0] * fRec3[0]) - ((0.8502684100000001 * fRec2[2]) + (fConst5 * fRec2[1])));
		fRec32[0] = ((fConst70 * (fRec1[1] + fRec1[2])) + (fConst69 * fRec32[1]));
		fRec1[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec32[0] + fRec2[0]) - (1.130462 + (1.059 * fRec2[1])))) - 112.13878048780487);
		fRec0[0] = ((fConst61 * ((fConst39 * fRec1[1]) + (fConst1 * fRec1[0]))) + (fConst3 * fRec0[1]));
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
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fVec2[1] = fVec2[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fVec1[1] = fVec1[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fVec0[1] = fVec0[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec10[1] = fRec10[0];
		fRec3[1] = fRec3[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
}

void Dsp::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case PREGAIN: 
		fslider3_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
		break;
	case DRIVE: 
		fslider2_ = (float*)data; // , 0.35, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fslider1_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
		break;
	case GAIN1: 
		fslider0_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
		break;
	default:
		break;
	}
}

void Dsp::connect_static(uint32_t port,void* data, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->connect(port, data);
}


PluginLV2 *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginLV2 *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace gxamp2
