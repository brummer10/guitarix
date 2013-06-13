// generated from file '../src/LV2/faust/gxamp14.dsp' by dsp2cc:
// Code generated with Faust 0.9.57 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp14 {

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
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec7[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec10[2];
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fVec0[2];
	double 	fConst10;
	double 	fRec11[2];
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
	double 	fRec19[3];
	double 	fVec1[2];
	double 	fConst41;
	double 	fConst42;
	double 	fRec18[2];
	double 	fConst43;
	double 	fRec17[2];
	double 	fRec16[3];
	double 	fVec2[2];
	double 	fConst44;
	double 	fConst45;
	double 	fRec15[2];
	double 	fRec14[3];
	double 	fConst46;
	double 	fRec13[3];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fVec3[2];
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
	double 	fVec4[2];
	double 	fConst58;
	double 	fRec12[2];
	double 	fRec9[2];
	double 	fConst59;
	double 	fRec8[2];
	double 	fVec5[2];
	double 	fRec6[2];
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fVec6[2];
	double 	fConst63;
	double 	fRec30[2];
	double 	fRec5[2];
	double 	fRec4[2];
	double 	fVec7[2];
	double 	fRec3[2];
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fVec8[2];
	double 	fConst67;
	double 	fRec31[2];
	double 	fRec2[2];
	double 	fRec1[2];
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
	id = "12AT7";
	name = N_("12AT7");
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
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst8 = (1 + fConst7);
	fConst9 = (0 - ((1 - fConst7) / fConst8));
	fConst10 = (1.0 / fConst8);
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
	fConst58 = (1.0 / fConst5);
	fConst59 = (0.025 / fConst2);
	fConst60 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst61 = (1 + fConst60);
	fConst62 = (0 - ((1 - fConst60) / fConst61));
	fConst63 = (1.0 / fConst61);
	fConst64 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst65 = (1 + fConst64);
	fConst66 = (0 - ((1 - fConst64) / fConst65));
	fConst67 = (1.0 / fConst65);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
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
	double 	fSlow10 = (1 - max((double)0, fSlow8));
	double 	fSlow11 = (1.25 * fSlow3);
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec7[0] = (fSlow1 + (0.999 * fRec7[1]));
		fRec10[0] = (fSlow2 + (0.999 * fRec10[1]));
		double fTemp0 = (double)input0[i];
		double fTemp1 = (fTemp0 * (1 - fRec10[0]));
		double fTemp2 = (1e-15 + (0.027 * fRec9[1]));
		fVec0[0] = fTemp2;
		fRec11[0] = ((fConst10 * (fVec0[0] + fVec0[1])) + (fConst9 * fRec11[1]));
		double fTemp3 = (fConst13 * fRec13[1]);
		double fTemp4 = (1e-15 + (fTemp0 * fRec10[0]));
		fRec19[0] = (fTemp4 - (fConst40 * ((fConst38 * fRec19[2]) + (fConst36 * fRec19[1]))));
		double fTemp5 = (fRec19[2] + (fRec19[0] + (2 * fRec19[1])));
		fVec1[0] = fTemp5;
		fRec18[0] = ((fConst42 * ((fConst41 * fVec1[1]) + (fConst1 * fVec1[0]))) + (fConst3 * fRec18[1]));
		fRec17[0] = ((fConst43 * (fRec18[0] + fRec18[1])) + (fConst34 * fRec17[1]));
		fRec16[0] = (fRec17[0] - (fConst32 * ((fConst30 * fRec16[2]) + (fConst28 * fRec16[1]))));
		double fTemp6 = (fRec16[2] + (fRec16[0] + (2 * fRec16[1])));
		fVec2[0] = fTemp6;
		fRec15[0] = ((fConst45 * ((fConst44 * fVec2[1]) + (fConst20 * fVec2[0]))) + (fConst25 * fRec15[1]));
		fRec14[0] = (fRec15[0] - (fConst23 * ((fConst21 * fRec14[2]) + (fConst19 * fRec14[1]))));
		fRec13[0] = ((fConst23 * (((fConst18 * fRec14[0]) + (fConst46 * fRec14[1])) + (fConst18 * fRec14[2]))) - (fConst16 * ((fConst15 * fRec13[2]) + fTemp3)));
		double fTemp7 = max((double)-1, min((double)1, (fSlow4 * (fRec13[2] + (fConst16 * (fTemp3 + (fConst15 * fRec13[0])))))));
		fRec23[0] = ((fConst45 * (fVec2[0] + fVec2[1])) + (fConst25 * fRec23[1]));
		fRec22[0] = (fRec23[0] - (fConst23 * ((fConst21 * fRec22[2]) + (fConst19 * fRec22[1]))));
		double fTemp8 = (fRec22[2] + (fRec22[0] + (2 * fRec22[1])));
		fVec3[0] = fTemp8;
		fRec21[0] = ((fConst52 * ((fConst51 * fVec3[1]) + (fConst14 * fVec3[0]))) + (fConst50 * fRec21[1]));
		fRec20[0] = (fRec21[0] - (fConst48 * ((fConst47 * fRec20[2]) + (fConst13 * fRec20[1]))));
		double fTemp9 = max((double)-1, min((double)1, (fSlow5 * (((fConst12 * fRec20[0]) + (fConst53 * fRec20[1])) + (fConst12 * fRec20[2])))));
		double fTemp10 = (fConst13 * fRec24[1]);
		double fTemp11 = (fConst19 * fRec25[1]);
		fRec27[0] = ((fConst43 * ((fConst56 * fRec18[1]) + (fConst29 * fRec18[0]))) + (fConst34 * fRec27[1]));
		fRec26[0] = (fRec27[0] - (fConst32 * ((fConst30 * fRec26[2]) + (fConst28 * fRec26[1]))));
		fRec25[0] = ((fConst32 * (((fConst27 * fRec26[0]) + (fConst57 * fRec26[1])) + (fConst27 * fRec26[2]))) - (fConst55 * ((fConst54 * fRec25[2]) + fTemp11)));
		fRec24[0] = ((fRec25[2] + (fConst55 * (fTemp11 + (fConst54 * fRec25[0])))) - (fConst16 * ((fConst15 * fRec24[2]) + fTemp10)));
		double fTemp12 = max((double)-1, min((double)1, (fSlow6 * (fRec24[2] + (fConst16 * (fTemp10 + (fConst15 * fRec24[0])))))));
		fRec29[0] = ((fConst52 * (fVec3[0] + fVec3[1])) + (fConst50 * fRec29[1]));
		fRec28[0] = (fRec29[0] - (fConst48 * ((fConst47 * fRec28[2]) + (fConst13 * fRec28[1]))));
		double fTemp13 = max((double)-1, min((double)1, (fSlow7 * (fRec28[2] + (fRec28[0] + (2 * fRec28[1]))))));
		double fTemp14 = ((1.2589412 * (fTemp13 * (1 - (0.3333333333333333 * faustpower<2>(fTemp13))))) + (1.584893192 * ((fTemp12 * (1 - (0.3333333333333333 * faustpower<2>(fTemp12)))) + ((fTemp9 * (1 - (0.3333333333333333 * faustpower<2>(fTemp9)))) + (0.8413951417869425 * (fTemp7 * (1 - (0.3333333333333333 * faustpower<2>(fTemp7)))))))));
		fVec4[0] = fTemp14;
		fRec12[0] = ((fConst58 * (fVec4[0] + fVec4[1])) + (fConst6 * fRec12[1]));
		double fTemp15 = (1e-15 + fTemp1);
		fRec9[0] = (Ftube(TUBE_TABLE_12AT7_68k, (((fSlow11 * ((fTemp15 * (4 - (4 * fabs(fTemp15)))) - fTemp15)) + ((fSlow10 * fTemp4) + ((fSlow9 * fRec12[0]) + (fRec11[0] + fTemp1)))) - 2.6177529999999978)) - 153.04618518518518);
		fRec8[0] = ((fConst59 * ((fConst41 * fRec9[1]) + (fConst1 * fRec9[0]))) + (fConst3 * fRec8[1]));
		double fTemp16 = (fRec8[0] * fRec7[0]);
		fVec5[0] = fTemp16;
		fRec6[0] = ((fConst58 * (fVec5[0] + fVec5[1])) + (fConst6 * fRec6[1]));
		double fTemp17 = (1e-15 + (0.015 * fRec5[1]));
		fVec6[0] = fTemp17;
		fRec30[0] = ((fConst63 * (fVec6[0] + fVec6[1])) + (fConst62 * fRec30[1]));
		fRec5[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec30[0] + fRec6[0]) - 1.887331999999999)) - 124.17786666666666);
		fRec4[0] = ((fConst59 * ((fConst41 * fRec5[1]) + (fConst1 * fRec5[0]))) + (fConst3 * fRec4[1]));
		double fTemp18 = (fRec7[0] * fRec4[0]);
		fVec7[0] = fTemp18;
		fRec3[0] = ((fConst58 * (fVec7[0] + fVec7[1])) + (fConst6 * fRec3[1]));
		double fTemp19 = (1e-15 + (0.0082 * fRec2[1]));
		fVec8[0] = fTemp19;
		fRec31[0] = ((fConst67 * (fVec8[0] + fVec8[1])) + (fConst66 * fRec31[1]));
		fRec2[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec31[0] + fRec3[0]) - 1.2569619999999988)) - 96.7119512195122);
		fRec1[0] = ((fConst59 * ((fConst41 * fRec2[1]) + (fConst1 * fRec2[0]))) + (fConst3 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec31[1] = fRec31[0];
		fVec8[1] = fVec8[0];
		fRec3[1] = fRec3[0];
		fVec7[1] = fVec7[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec30[1] = fRec30[0];
		fVec6[1] = fVec6[0];
		fRec6[1] = fRec6[0];
		fVec5[1] = fVec5[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec12[1] = fRec12[0];
		fVec4[1] = fVec4[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fVec3[1] = fVec3[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec2[1] = fVec2[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fVec1[1] = fVec1[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec11[1] = fRec11[0];
		fVec0[1] = fVec0[0];
		fRec10[1] = fRec10[0];
		fRec7[1] = fRec7[0];
		fRec0[1] = fRec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
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

/*
typedef enum
{
   DRIVE, 
   WET_DRY, 
   PREGAIN, 
   GAIN1, 
} PortIndex;
*/

} // end namespace gxamp14
