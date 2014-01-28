// generated from file '../src/LV2/faust/gxamp.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec7[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec10[2];
	double 	fVec0[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fRec11[2];
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
	double 	fRec20[3];
	double 	fVec1[2];
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fRec19[2];
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fVec2[2];
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fRec16[2];
	double 	fRec15[3];
	double 	fVec3[2];
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fRec14[2];
	double 	fRec13[3];
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fConst48;
	double 	fRec21[3];
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fRec27[2];
	double 	fRec26[3];
	double 	fConst52;
	double 	fRec25[3];
	double 	fRec24[3];
	double 	fConst53;
	double 	fRec29[2];
	double 	fRec28[3];
	double 	fConst54;
	double 	fVec4[2];
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fRec12[2];
	double 	fRec9[2];
	double 	fConst59;
	double 	fRec8[2];
	double 	fVec5[2];
	double 	fRec6[2];
	double 	fVec6[2];
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fRec30[2];
	double 	fRec5[2];
	double 	fRec4[2];
	double 	fVec7[2];
	double 	fRec3[2];
	double 	fVec8[2];
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fRec31[2];
	double 	fRec2[2];
	double 	fRec1[2];
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "12ax7";
	name = N_("12ax7");
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
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
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
	fConst1 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst2 = (1 + fConst1);
	fConst3 = (1.0 / fConst2);
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
	fConst59 = (0.025 / fConst33);
	fConst60 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst61 = (1 + fConst60);
	fConst62 = (1.0 / fConst61);
	fConst63 = (0 - ((1 - fConst60) / fConst61));
	fConst64 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst65 = (1 + fConst64);
	fConst66 = (1.0 / fConst65);
	fConst67 = (0 - ((1 - fConst64) / fConst65));
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
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
	double 	fSlow4 = (1.25 * fSlow3);
	double 	fSlow5 = (2 * (fSlow3 - 0.5));
	double 	fSlow6 = (1 - max((double)0, fSlow5));
	double 	fSlow7 = (fConst10 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow8 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow9 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow10 = (fConst10 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow11 = (1 - max((double)0, (0 - fSlow5)));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.999 * fRec0[1]) + fSlow0);
		fRec7[0] = ((0.999 * fRec7[1]) + fSlow1);
		fRec10[0] = (fSlow2 + (0.999 * fRec10[1]));
		double fTemp0 = (double)input0[i];
		double fTemp1 = (fTemp0 * (1 - fRec10[0]));
		double fTemp2 = (1e-15 + (0.027 * fRec9[1]));
		fVec0[0] = fTemp2;
		fRec11[0] = ((fConst4 * fRec11[1]) + (fConst3 * (fVec0[0] + fVec0[1])));
		double fTemp3 = (1e-15 + fTemp1);
		double fTemp4 = (1e-15 + (fTemp0 * fRec10[0]));
		fRec20[0] = (fTemp4 - (fConst30 * ((fConst28 * fRec20[2]) + (fConst26 * fRec20[1]))));
		double fTemp5 = (fRec20[2] + (fRec20[0] + (2 * fRec20[1])));
		fVec1[0] = fTemp5;
		fRec19[0] = ((fConst35 * fRec19[1]) + (fConst34 * ((fConst31 * fVec1[0]) + (fConst32 * fVec1[1]))));
		fRec18[0] = ((fConst38 * fRec18[1]) + (fConst37 * (fRec19[0] + fRec19[1])));
		fRec17[0] = (fRec18[0] - (fConst24 * ((fConst22 * fRec17[2]) + (fConst20 * fRec17[1]))));
		double fTemp6 = (fRec17[2] + (fRec17[0] + (2 * fRec17[1])));
		fVec2[0] = fTemp6;
		fRec16[0] = ((fConst41 * fRec16[1]) + (fConst40 * (fVec2[0] + fVec2[1])));
		fRec15[0] = (fRec16[0] - (fConst17 * ((fConst15 * fRec15[2]) + (fConst13 * fRec15[1]))));
		double fTemp7 = (fRec15[2] + (fRec15[0] + (2 * fRec15[1])));
		fVec3[0] = fTemp7;
		fRec14[0] = ((fConst44 * fRec14[1]) + (fConst43 * (fVec3[0] + fVec3[1])));
		fRec13[0] = (fRec14[0] - (fConst10 * ((fConst9 * fRec13[2]) + (fConst7 * fRec13[1]))));
		double fTemp8 = max((double)-1, min((double)1, (fSlow7 * (fRec13[2] + (fRec13[0] + (2 * fRec13[1]))))));
		double fTemp9 = (fConst7 * fRec21[1]);
		fRec23[0] = ((fConst41 * fRec23[1]) + (fConst40 * ((fConst14 * fVec2[0]) + (fConst47 * fVec2[1]))));
		fRec22[0] = (fRec23[0] - (fConst17 * ((fConst15 * fRec22[2]) + (fConst13 * fRec22[1]))));
		fRec21[0] = ((fConst17 * (((fConst12 * fRec22[0]) + (fConst48 * fRec22[1])) + (fConst12 * fRec22[2]))) - (fConst46 * ((fConst45 * fRec21[2]) + fTemp9)));
		double fTemp10 = max((double)-1, min((double)1, (fSlow8 * (fRec21[2] + (fConst46 * (fTemp9 + (fConst45 * fRec21[0])))))));
		double fTemp11 = (fConst7 * fRec24[1]);
		double fTemp12 = (fConst13 * fRec25[1]);
		fRec27[0] = ((fConst38 * fRec27[1]) + (fConst37 * ((fConst21 * fRec19[0]) + (fConst51 * fRec19[1]))));
		fRec26[0] = (fRec27[0] - (fConst24 * ((fConst22 * fRec26[2]) + (fConst20 * fRec26[1]))));
		fRec25[0] = ((fConst24 * (((fConst19 * fRec26[0]) + (fConst52 * fRec26[1])) + (fConst19 * fRec26[2]))) - (fConst50 * ((fConst49 * fRec25[2]) + fTemp12)));
		fRec24[0] = ((fRec25[2] + (fConst50 * (fTemp12 + (fConst49 * fRec25[0])))) - (fConst46 * ((fConst45 * fRec24[2]) + fTemp11)));
		double fTemp13 = max((double)-1, min((double)1, (fSlow9 * (fRec24[2] + (fConst46 * (fTemp11 + (fConst45 * fRec24[0])))))));
		fRec29[0] = ((fConst44 * fRec29[1]) + (fConst43 * ((fConst8 * fVec3[0]) + (fConst53 * fVec3[1]))));
		fRec28[0] = (fRec29[0] - (fConst10 * ((fConst9 * fRec28[2]) + (fConst7 * fRec28[1]))));
		double fTemp14 = max((double)-1, min((double)1, (fSlow10 * (((fConst6 * fRec28[0]) + (fConst54 * fRec28[1])) + (fConst6 * fRec28[2])))));
		double fTemp15 = ((1.584893192 * ((fTemp14 * (1 - (0.3333333333333333 * faustpower<2>(fTemp14)))) + ((fTemp13 * (1 - (0.3333333333333333 * faustpower<2>(fTemp13)))) + (0.8413951417869425 * (fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10)))))))) + (1.2589412 * (fTemp8 * (1 - (0.3333333333333333 * faustpower<2>(fTemp8))))));
		fVec4[0] = fTemp15;
		fRec12[0] = ((fConst58 * fRec12[1]) + (fConst57 * (fVec4[0] + fVec4[1])));
		fRec9[0] = (Ftube(TUBE_TABLE_12AX7_68k, (((fSlow11 * fRec12[0]) + ((fSlow6 * fTemp4) + ((fSlow4 * ((fTemp3 * (4 - (4 * fabs(fTemp3)))) - fTemp3)) + (fRec11[0] + fTemp1)))) - 1.581655999999998)) - 191.42014814814814);
		fRec8[0] = ((fConst35 * fRec8[1]) + (fConst59 * ((fConst31 * fRec9[0]) + (fConst32 * fRec9[1]))));
		double fTemp16 = (fRec8[0] * fRec7[0]);
		fVec5[0] = fTemp16;
		fRec6[0] = ((fConst58 * fRec6[1]) + (fConst57 * (fVec5[0] + fVec5[1])));
		double fTemp17 = (1e-15 + (0.015 * fRec5[1]));
		fVec6[0] = fTemp17;
		fRec30[0] = ((fConst63 * fRec30[1]) + (fConst62 * (fVec6[0] + fVec6[1])));
		fRec5[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec30[0] + fRec6[0]) - 1.204284999999999)) - 169.71433333333334);
		fRec4[0] = ((fConst35 * fRec4[1]) + (fConst59 * ((fConst31 * fRec5[0]) + (fConst32 * fRec5[1]))));
		double fTemp18 = (fRec7[0] * fRec4[0]);
		fVec7[0] = fTemp18;
		fRec3[0] = ((fConst58 * fRec3[1]) + (fConst57 * (fVec7[0] + fVec7[1])));
		double fTemp19 = (1e-15 + (0.0082 * fRec2[1]));
		fVec8[0] = fTemp19;
		fRec31[0] = ((fConst67 * fRec31[1]) + (fConst66 * (fVec8[0] + fVec8[1])));
		fRec2[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec31[0] + fRec3[0]) - 0.840702999999999)) - 147.47524390243905);
		fRec1[0] = ((fConst35 * fRec1[1]) + (fConst59 * ((fConst31 * fRec2[0]) + (fConst32 * fRec2[1]))));
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
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fVec3[1] = fVec3[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fVec2[1] = fVec2[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fVec1[1] = fVec1[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
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

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
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

} // end namespace gxamp
