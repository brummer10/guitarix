// generated from file '../src/LV2/faust/gxamp10.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp10 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
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
	double 	fVec0[2];
	double 	fConst7;
	double 	fRec3[2];
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec8[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec11[2];
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fVec1[2];
	double 	fConst14;
	double 	fRec12[2];
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
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fRec20[3];
	double 	fVec2[2];
	double 	fConst45;
	double 	fConst46;
	double 	fRec19[2];
	double 	fConst47;
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fVec3[2];
	double 	fConst48;
	double 	fConst49;
	double 	fRec16[2];
	double 	fRec15[3];
	double 	fConst50;
	double 	fRec14[3];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	double 	fRec24[2];
	double 	fRec23[3];
	double 	fVec4[2];
	double 	fConst55;
	double 	fConst56;
	double 	fRec22[2];
	double 	fRec21[3];
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fConst61;
	double 	fRec26[3];
	double 	fRec25[3];
	double 	fRec30[2];
	double 	fRec29[3];
	double 	fVec5[2];
	double 	fConst62;
	double 	fRec13[2];
	double 	fRec10[2];
	double 	fConst63;
	double 	fRec9[2];
	double 	fVec6[2];
	double 	fRec7[2];
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fVec7[2];
	double 	fConst67;
	double 	fRec31[2];
	double 	fRec6[2];
	double 	fRec5[2];
	double 	fVec8[2];
	double 	fRec4[2];
	double 	fRec2[2];
	double 	fRec1[2];
	double 	fVec9[2];
	double 	fRec34[2];
	double 	fRec33[2];
	double 	fRec32[2];
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
	id = "6DJ8";
	name = N_("6DJ8");
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
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
	fConst4 = (1.0 / tan((609.4689747964198 / iConst0)));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = (1.0 / fConst5);
	fConst8 = (1.0 / tan((20517.741620594938 / iConst0)));
	fConst9 = (1 + fConst8);
	fConst10 = (0 - ((1 - fConst8) / fConst9));
	fConst11 = (1.0 / tan((270.1769682087222 / iConst0)));
	fConst12 = (1 + fConst11);
	fConst13 = (0 - ((1 - fConst11) / fConst12));
	fConst14 = (1.0 / fConst12);
	fConst15 = tan((942.4777960769379 / iConst0));
	fConst16 = (1.0 / faustpower<2>(fConst15));
	fConst17 = (2 * (1 - fConst16));
	fConst18 = (1.0 / fConst15);
	fConst19 = (1 + ((fConst18 - 1.0) / fConst15));
	fConst20 = (1.0 / (1 + ((1.0 + fConst18) / fConst15)));
	fConst21 = tan((3769.9111843077517 / iConst0));
	fConst22 = (1.0 / faustpower<2>(fConst21));
	fConst23 = (2 * (1 - fConst22));
	fConst24 = (1.0 / fConst21);
	fConst25 = (1 + ((fConst24 - 1.0000000000000004) / fConst21));
	fConst26 = (1 + ((fConst24 + 1.0000000000000004) / fConst21));
	fConst27 = (1.0 / fConst26);
	fConst28 = (1 + fConst24);
	fConst29 = (0 - ((1 - fConst24) / fConst28));
	fConst30 = tan((10053.096491487338 / iConst0));
	fConst31 = (1.0 / faustpower<2>(fConst30));
	fConst32 = (2 * (1 - fConst31));
	fConst33 = (1.0 / fConst30);
	fConst34 = (1 + ((fConst33 - 1.0000000000000004) / fConst30));
	fConst35 = (1 + ((1.0000000000000004 + fConst33) / fConst30));
	fConst36 = (1.0 / fConst35);
	fConst37 = (1 + fConst33);
	fConst38 = (0 - ((1 - fConst33) / fConst37));
	fConst39 = tan((47123.8898038469 / iConst0));
	fConst40 = (2 * (1 - (1.0 / faustpower<2>(fConst39))));
	fConst41 = (1.0 / fConst39);
	fConst42 = (1 + ((fConst41 - 1.414213562373095) / fConst39));
	fConst43 = (1 + ((1.414213562373095 + fConst41) / fConst39));
	fConst44 = (1.0 / fConst43);
	fConst45 = (0 - fConst1);
	fConst46 = (1.0 / (fConst2 * fConst43));
	fConst47 = (1.0 / fConst37);
	fConst48 = (0 - fConst24);
	fConst49 = (1.0 / (fConst28 * fConst35));
	fConst50 = (2 * (0 - fConst22));
	fConst51 = (1 + ((fConst18 - 1.0000000000000004) / fConst15));
	fConst52 = (1.0 / (1 + ((fConst18 + 1.0000000000000004) / fConst15)));
	fConst53 = (1 + fConst18);
	fConst54 = (0 - ((1 - fConst18) / fConst53));
	fConst55 = (0 - fConst18);
	fConst56 = (1.0 / (fConst53 * fConst26));
	fConst57 = (2 * (0 - fConst16));
	fConst58 = (1 + ((fConst24 - 1.0) / fConst21));
	fConst59 = (1.0 / (1 + ((1.0 + fConst24) / fConst21)));
	fConst60 = (0 - fConst33);
	fConst61 = (2 * (0 - fConst31));
	fConst62 = (1.0 / fConst9);
	fConst63 = (0.05 / fConst2);
	fConst64 = (1.0 / tan((414.6902302738527 / iConst0)));
	fConst65 = (1 + fConst64);
	fConst66 = (0 - ((1 - fConst64) / fConst65));
	fConst67 = (1.0 / fConst65);
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
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * fslider1)));
	double 	fSlow2 = (1.000000000000001e-05 * fslider2);
	double 	fSlow3 = fslider3;
	double 	fSlow4 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow5 = (fConst52 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow6 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow7 = (fConst52 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow8 = (2 * (fSlow3 - 0.5));
	double 	fSlow9 = (1 - max(0, (0 - fSlow8)));
	double 	fSlow10 = (1 - max(0, fSlow8));
	double 	fSlow11 = (1.25 * fSlow3);
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		double fTemp0 = (1e-15 + (0.0082 * fRec2[1]));
		fVec0[0] = fTemp0;
		fRec3[0] = ((fConst7 * (fVec0[0] + fVec0[1])) + (fConst6 * fRec3[1]));
		fRec8[0] = (fSlow1 + (0.999 * fRec8[1]));
		fRec11[0] = (fSlow2 + (0.999 * fRec11[1]));
		double fTemp1 = (double)input0[i];
		double fTemp2 = (fTemp1 * (1 - fRec11[0]));
		double fTemp3 = (1e-15 + (0.027 * fRec10[1]));
		fVec1[0] = fTemp3;
		fRec12[0] = ((fConst14 * (fVec1[0] + fVec1[1])) + (fConst13 * fRec12[1]));
		double fTemp4 = (fConst17 * fRec14[1]);
		double fTemp5 = (1e-15 + (fTemp1 * fRec11[0]));
		fRec20[0] = (fTemp5 - (fConst44 * ((fConst42 * fRec20[2]) + (fConst40 * fRec20[1]))));
		double fTemp6 = (fRec20[2] + (fRec20[0] + (2 * fRec20[1])));
		fVec2[0] = fTemp6;
		fRec19[0] = ((fConst46 * ((fConst45 * fVec2[1]) + (fConst1 * fVec2[0]))) + (fConst3 * fRec19[1]));
		fRec18[0] = ((fConst47 * (fRec19[0] + fRec19[1])) + (fConst38 * fRec18[1]));
		fRec17[0] = (fRec18[0] - (fConst36 * ((fConst34 * fRec17[2]) + (fConst32 * fRec17[1]))));
		double fTemp7 = (fRec17[2] + (fRec17[0] + (2 * fRec17[1])));
		fVec3[0] = fTemp7;
		fRec16[0] = ((fConst49 * ((fConst48 * fVec3[1]) + (fConst24 * fVec3[0]))) + (fConst29 * fRec16[1]));
		fRec15[0] = (fRec16[0] - (fConst27 * ((fConst25 * fRec15[2]) + (fConst23 * fRec15[1]))));
		fRec14[0] = ((fConst27 * (((fConst22 * fRec15[0]) + (fConst50 * fRec15[1])) + (fConst22 * fRec15[2]))) - (fConst20 * ((fConst19 * fRec14[2]) + fTemp4)));
		double fTemp8 = max(-1, min(1, (fSlow4 * (fRec14[2] + (fConst20 * (fTemp4 + (fConst19 * fRec14[0])))))));
		fRec24[0] = ((fConst49 * (fVec3[0] + fVec3[1])) + (fConst29 * fRec24[1]));
		fRec23[0] = (fRec24[0] - (fConst27 * ((fConst25 * fRec23[2]) + (fConst23 * fRec23[1]))));
		double fTemp9 = (fRec23[2] + (fRec23[0] + (2 * fRec23[1])));
		fVec4[0] = fTemp9;
		fRec22[0] = ((fConst56 * ((fConst55 * fVec4[1]) + (fConst18 * fVec4[0]))) + (fConst54 * fRec22[1]));
		fRec21[0] = (fRec22[0] - (fConst52 * ((fConst51 * fRec21[2]) + (fConst17 * fRec21[1]))));
		double fTemp10 = max(-1, min(1, (fSlow5 * (((fConst16 * fRec21[0]) + (fConst57 * fRec21[1])) + (fConst16 * fRec21[2])))));
		double fTemp11 = (fConst17 * fRec25[1]);
		double fTemp12 = (fConst23 * fRec26[1]);
		fRec28[0] = ((fConst47 * ((fConst60 * fRec19[1]) + (fConst33 * fRec19[0]))) + (fConst38 * fRec28[1]));
		fRec27[0] = (fRec28[0] - (fConst36 * ((fConst34 * fRec27[2]) + (fConst32 * fRec27[1]))));
		fRec26[0] = ((fConst36 * (((fConst31 * fRec27[0]) + (fConst61 * fRec27[1])) + (fConst31 * fRec27[2]))) - (fConst59 * ((fConst58 * fRec26[2]) + fTemp12)));
		fRec25[0] = ((fRec26[2] + (fConst59 * (fTemp12 + (fConst58 * fRec26[0])))) - (fConst20 * ((fConst19 * fRec25[2]) + fTemp11)));
		double fTemp13 = max(-1, min(1, (fSlow6 * (fRec25[2] + (fConst20 * (fTemp11 + (fConst19 * fRec25[0])))))));
		fRec30[0] = ((fConst56 * (fVec4[0] + fVec4[1])) + (fConst54 * fRec30[1]));
		fRec29[0] = (fRec30[0] - (fConst52 * ((fConst51 * fRec29[2]) + (fConst17 * fRec29[1]))));
		double fTemp14 = max(-1, min(1, (fSlow7 * (fRec29[2] + (fRec29[0] + (2 * fRec29[1]))))));
		double fTemp15 = ((1.2589412 * (fTemp14 * (1 - (0.3333333333333333 * faustpower<2>(fTemp14))))) + (1.584893192 * ((fTemp13 * (1 - (0.3333333333333333 * faustpower<2>(fTemp13)))) + ((fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10)))) + (0.8413951417869425 * (fTemp8 * (1 - (0.3333333333333333 * faustpower<2>(fTemp8)))))))));
		fVec5[0] = fTemp15;
		fRec13[0] = ((fConst62 * (fVec5[0] + fVec5[1])) + (fConst10 * fRec13[1]));
		double fTemp16 = (1e-15 + fTemp2);
		fRec10[0] = (Ftube(TUBE_TABLE_6DJ8_68k, (((fSlow11 * ((fTemp16 * (4 - (4 * fabs(fTemp16)))) - fTemp16)) + ((fSlow10 * fTemp5) + ((fSlow9 * fRec13[0]) + (fRec12[0] + fTemp2)))) - 1.863945999999998)) - 60.96496296296296);
		fRec9[0] = ((fConst63 * ((fConst45 * fRec10[1]) + (fConst1 * fRec10[0]))) + (fConst3 * fRec9[1]));
		double fTemp17 = (fRec9[0] * fRec8[0]);
		fVec6[0] = fTemp17;
		fRec7[0] = ((fConst62 * (fVec6[0] + fVec6[1])) + (fConst10 * fRec7[1]));
		double fTemp18 = (1e-15 + (0.015 * fRec6[1]));
		fVec7[0] = fTemp18;
		fRec31[0] = ((fConst67 * (fVec7[0] + fVec7[1])) + (fConst66 * fRec31[1]));
		fRec6[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec31[0] + fRec7[0]) - 1.2716089999999989)) - 45.22606666666667);
		fRec5[0] = ((fConst63 * ((fConst45 * fRec6[1]) + (fConst1 * fRec6[0]))) + (fConst3 * fRec5[1]));
		double fTemp19 = (fRec8[0] * fRec5[0]);
		fVec8[0] = fTemp19;
		fRec4[0] = ((fConst62 * (fVec8[0] + fVec8[1])) + (fConst10 * fRec4[1]));
		fRec2[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec4[0] + fRec3[0]) - 0.797042999999999)) - 32.799634146341475);
		fRec1[0] = ((fConst63 * ((fConst45 * fRec2[1]) + (fConst1 * fRec2[0]))) + (fConst3 * fRec1[1]));
		double fTemp20 = (1e-15 + (0.0082 * fRec33[1]));
		fVec9[0] = fTemp20;
		fRec34[0] = ((fConst7 * (fVec9[0] + fVec9[1])) + (fConst6 * fRec34[1]));
		fRec33[0] = (Ftube(TUBE_TABLE_6DJ8_68k, ((fRec34[0] + fRec4[0]) - 0.799030999999999)) - 32.55719512195121);
		fRec32[0] = ((fConst63 * ((fConst45 * fRec33[1]) + (fConst1 * fRec33[0]))) + (fConst3 * fRec32[1]));
		output0[i] = (FAUSTFLOAT)((fRec32[0] + fRec1[0]) * fRec0[0]);
		// post processing
		fRec32[1] = fRec32[0];
		fRec33[1] = fRec33[0];
		fRec34[1] = fRec34[0];
		fVec9[1] = fVec9[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fVec8[1] = fVec8[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec31[1] = fRec31[0];
		fVec7[1] = fVec7[0];
		fRec7[1] = fRec7[0];
		fVec6[1] = fVec6[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec13[1] = fRec13[0];
		fVec5[1] = fVec5[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fVec4[1] = fVec4[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fVec3[1] = fVec3[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fVec2[1] = fVec2[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec12[1] = fRec12[0];
		fVec1[1] = fVec1[0];
		fRec11[1] = fRec11[0];
		fRec8[1] = fRec8[0];
		fRec3[1] = fRec3[0];
		fVec0[1] = fVec0[0];
		fRec0[1] = fRec0[0];
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
	case DRIVE: 
		fslider3_ = (float*)data; // , 0.35, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fslider2_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
		break;
	case PREGAIN: 
		fslider1_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
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

} // end namespace gxamp10
