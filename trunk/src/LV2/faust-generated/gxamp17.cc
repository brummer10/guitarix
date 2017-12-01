// generated from file '../src/LV2/faust/gxamp17.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp17 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec12[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec18[2];
	double 	fRec21[2];
	int 	IOTA;
	double 	fVec0[32768];
	double 	fConst0;
	int 	iConst1;
	double 	fRec20[2];
	double 	fConst2;
	double 	fRec19[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
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
	double 	fRec30[3];
	double 	fVec1[2];
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fRec29[2];
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fVec2[2];
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fRec26[2];
	double 	fRec25[3];
	double 	fVec3[2];
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fRec24[2];
	double 	fRec23[3];
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fRec34[2];
	double 	fRec33[3];
	double 	fConst48;
	double 	fRec32[3];
	double 	fRec31[3];
	double 	fConst49;
	double 	fRec36[2];
	double 	fRec35[3];
	double 	fConst50;
	double 	fConst51;
	double 	fRec39[2];
	double 	fRec38[3];
	double 	fConst52;
	double 	fRec37[3];
	double 	fVec4[2];
	double 	fConst53;
	double 	fConst54;
	double 	fConst55;
	double 	fConst56;
	double 	fRec22[2];
	double 	fVec5[2];
	double 	fRec17[2];
	double 	fRec16[3];
	double 	fVec6[2];
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fRec40[2];
	double 	fRec15[2];
	double 	fConst61;
	double 	fRec14[2];
	double 	fVec7[2];
	double 	fRec44[2];
	double 	fRec43[3];
	double 	fVec8[2];
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fRec45[2];
	double 	fRec42[2];
	double 	fRec41[2];
	double 	fRec13[2];
	double 	fVec9[2];
	double 	fRec11[2];
	double 	fVec10[2];
	double 	fRec10[2];
	double 	fRec9[3];
	double 	fVec11[2];
	double 	fRec46[2];
	double 	fRec8[2];
	double 	fRec7[2];
	double 	fVec12[2];
	double 	fRec50[2];
	double 	fRec49[3];
	double 	fVec13[2];
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fRec51[2];
	double 	fRec48[2];
	double 	fRec47[2];
	double 	fRec6[2];
	double 	fRec5[2];
	double 	fVec14[2];
	double 	fRec4[2];
	double 	fRec3[3];
	double 	fVec15[2];
	double 	fRec52[2];
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
	id = "12AT7 feedback";
	name = N_("12AT7 feedback");
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
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<32768; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<3; i++) fRec33[i] = 0;
	for (int i=0; i<3; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<3; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<3; i++) fRec38[i] = 0;
	for (int i=0; i<3; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<3; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fVec12[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<3; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) fVec13[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec14[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec15[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
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
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	iConst1 = int((int((0.1111111111111111 * fConst0)) & 65535));
	fConst2 = (0.009000000000000008 / fConst0);
	fConst3 = tan((942.4777960769379 / fConst0));
	fConst4 = (1.0 / fConst3);
	fConst5 = (1 + ((fConst4 - 1.0000000000000004) / fConst3));
	fConst6 = (1.0 / faustpower<2>(fConst3));
	fConst7 = (2 * (1 - fConst6));
	fConst8 = (1.0 / (1 + ((1.0000000000000004 + fConst4) / fConst3)));
	fConst9 = tan((3769.9111843077517 / fConst0));
	fConst10 = (1.0 / fConst9);
	fConst11 = (1 + ((fConst10 - 1.0000000000000004) / fConst9));
	fConst12 = (1.0 / faustpower<2>(fConst9));
	fConst13 = (2 * (1 - fConst12));
	fConst14 = (1 + ((1.0000000000000004 + fConst10) / fConst9));
	fConst15 = (1.0 / fConst14);
	fConst16 = tan((10053.096491487338 / fConst0));
	fConst17 = (1.0 / faustpower<2>(fConst16));
	fConst18 = (2 * (1 - fConst17));
	fConst19 = (1.0 / fConst16);
	fConst20 = (1 + ((fConst19 - 1.0000000000000004) / fConst16));
	fConst21 = (1 + ((1.0000000000000004 + fConst19) / fConst16));
	fConst22 = (1.0 / fConst21);
	fConst23 = tan((47123.8898038469 / fConst0));
	fConst24 = (2 * (1 - (1.0 / faustpower<2>(fConst23))));
	fConst25 = (1.0 / fConst23);
	fConst26 = (1 + ((fConst25 - 1.414213562373095) / fConst23));
	fConst27 = (1 + ((1.414213562373095 + fConst25) / fConst23));
	fConst28 = (1.0 / fConst27);
	fConst29 = (1.0 / tan((97.38937226128358 / fConst0)));
	fConst30 = (0 - fConst29);
	fConst31 = (1 + fConst29);
	fConst32 = (1.0 / (fConst31 * fConst27));
	fConst33 = (0 - ((1 - fConst29) / fConst31));
	fConst34 = (1 + fConst19);
	fConst35 = (1.0 / fConst34);
	fConst36 = (0 - ((1 - fConst19) / fConst34));
	fConst37 = (1 + fConst10);
	fConst38 = (1.0 / (fConst37 * fConst21));
	fConst39 = (0 - ((1 - fConst10) / fConst37));
	fConst40 = (1 + fConst4);
	fConst41 = (1.0 / (fConst40 * fConst14));
	fConst42 = (0 - ((1 - fConst4) / fConst40));
	fConst43 = (1 + ((fConst4 - 1.0) / fConst3));
	fConst44 = (1.0 / (1 + ((1.0 + fConst4) / fConst3)));
	fConst45 = (1 + ((fConst10 - 1.0) / fConst9));
	fConst46 = (1.0 / (1 + ((1.0 + fConst10) / fConst9)));
	fConst47 = (0 - fConst19);
	fConst48 = (2 * (0 - fConst17));
	fConst49 = (0 - fConst4);
	fConst50 = (2 * (0 - fConst6));
	fConst51 = (0 - fConst10);
	fConst52 = (2 * (0 - fConst12));
	fConst53 = (1.0 / tan((20517.741620594938 / fConst0)));
	fConst54 = (1 + fConst53);
	fConst55 = (1.0 / fConst54);
	fConst56 = (0 - ((1 - fConst53) / fConst54));
	fConst57 = (1.0 / tan((270.1769682087222 / fConst0)));
	fConst58 = (1 + fConst57);
	fConst59 = (1.0 / fConst58);
	fConst60 = (0 - ((1 - fConst57) / fConst58));
	fConst61 = (0.025 / fConst31);
	fConst62 = (1.0 / tan((414.6902302738527 / fConst0)));
	fConst63 = (1 + fConst62);
	fConst64 = (1.0 / fConst63);
	fConst65 = (0 - ((1 - fConst62) / fConst63));
	fConst66 = (1.0 / tan((609.4689747964198 / fConst0)));
	fConst67 = (1 + fConst66);
	fConst68 = (1.0 / fConst67);
	fConst69 = (0 - ((1 - fConst66) / fConst67));
	IOTA = 0;
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
	double 	fSlow6 = (0.024937655860349125 * (1 - max((double)0, fSlow5)));
	double 	fSlow7 = (fConst8 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow8 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow9 = pow(1e+01,(2 * fSlow3));
	double 	fSlow10 = (fConst8 * fSlow9);
	double 	fSlow11 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow12 = (1 - max((double)0, (0 - fSlow5)));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec12[0] = (fSlow1 + (0.999 * fRec12[1]));
		fRec18[0] = (fSlow2 + (0.999 * fRec18[1]));
		double fTemp0 = (1 - fRec18[0]);
		double fTemp1 = (double)input0[i];
		double fTemp2 = fabs(fTemp1);
		fRec21[0] = ((9.999999999998899e-05 * fTemp2) + (0.9999 * fRec21[1]));
		double fTemp3 = max(fRec21[0], fTemp2);
		fVec0[IOTA&32767] = fTemp3;
		fRec20[0] = ((fVec0[IOTA&32767] + fRec20[1]) - fVec0[(IOTA-iConst1)&32767]);
		fRec19[0] = ((0.999 * fRec19[1]) + (fConst2 * fRec20[0]));
		double fTemp4 = max((double)-1, min(-0.01, (fVec0[IOTA&32767] - (1.0 + (1.02 * fRec19[0])))));
		double fTemp5 = (0 - fTemp4);
		double fTemp6 = (40.1 * fTemp5);
		double fTemp7 = max((double)-600, fTemp6);
		double fTemp8 = (0 - fTemp7);
		double fTemp9 = (fTemp1 - fTemp4);
		double fTemp10 = (40.1 * fTemp9);
		double fTemp11 = max((double)-600, fTemp10);
		double fTemp12 = (0 - fTemp11);
		double fTemp13 = (((int((fabs(fTemp10) > 0.0001)))?((int((fTemp11 < -50)))?(fTemp12 * exp(fTemp11)):(fTemp11 / (1 - exp(fTemp12)))):(1 + (fTemp9 * (20.05 + (134.00083333333336 * fTemp9))))) - ((int((fabs(fTemp6) > 0.0001)))?((int((fTemp7 < -50)))?(fTemp8 * exp(fTemp7)):(fTemp7 / (1 - exp(fTemp8)))):(1 + (fTemp5 * (20.05 + (134.00083333333336 * fTemp5))))));
		double fTemp14 = (0.024937655860349125 * (fTemp13 * fRec18[0]));
		fRec30[0] = (fTemp14 - (fConst28 * ((fConst26 * fRec30[2]) + (fConst24 * fRec30[1]))));
		double fTemp15 = (fRec30[0] + (fRec30[2] + (2 * fRec30[1])));
		fVec1[0] = fTemp15;
		fRec29[0] = ((fConst33 * fRec29[1]) + (fConst32 * ((fConst29 * fVec1[0]) + (fConst30 * fVec1[1]))));
		fRec28[0] = ((fConst36 * fRec28[1]) + (fConst35 * (fRec29[1] + fRec29[0])));
		fRec27[0] = (fRec28[0] - (fConst22 * ((fConst20 * fRec27[2]) + (fConst18 * fRec27[1]))));
		double fTemp16 = (fRec27[0] + (fRec27[2] + (2 * fRec27[1])));
		fVec2[0] = fTemp16;
		fRec26[0] = ((fConst39 * fRec26[1]) + (fConst38 * (fVec2[0] + fVec2[1])));
		fRec25[0] = (fRec26[0] - (fConst15 * ((fConst13 * fRec25[1]) + (fConst11 * fRec25[2]))));
		double fTemp17 = (fRec25[0] + (fRec25[2] + (2 * fRec25[1])));
		fVec3[0] = fTemp17;
		fRec24[0] = ((fConst42 * fRec24[1]) + (fConst41 * (fVec3[0] + fVec3[1])));
		fRec23[0] = (fRec24[0] - (fConst8 * ((fConst7 * fRec23[1]) + (fConst5 * fRec23[2]))));
		double fTemp18 = max((double)-1, min((double)1, (fSlow7 * (fRec23[0] + (fRec23[2] + (2 * fRec23[1]))))));
		double fTemp19 = (fConst7 * fRec31[1]);
		double fTemp20 = (fConst13 * fRec32[1]);
		fRec34[0] = ((fConst36 * fRec34[1]) + (fConst35 * ((fConst19 * fRec29[0]) + (fConst47 * fRec29[1]))));
		fRec33[0] = (fRec34[0] - (fConst22 * ((fConst20 * fRec33[2]) + (fConst18 * fRec33[1]))));
		fRec32[0] = ((fConst22 * ((fConst48 * fRec33[1]) + (fConst17 * (fRec33[2] + fRec33[0])))) - (fConst46 * ((fConst45 * fRec32[2]) + fTemp20)));
		fRec31[0] = ((fRec32[2] + (fConst46 * (fTemp20 + (fConst45 * fRec32[0])))) - (fConst44 * ((fConst43 * fRec31[2]) + fTemp19)));
		double fTemp21 = max((double)-1, min((double)1, (fSlow8 * (fRec31[2] + (fConst44 * (fTemp19 + (fConst43 * fRec31[0])))))));
		fRec36[0] = ((fConst42 * fRec36[1]) + (fConst41 * ((fConst4 * fVec3[0]) + (fConst49 * fVec3[1]))));
		fRec35[0] = (fRec36[0] - (fConst8 * ((fConst7 * fRec35[1]) + (fConst5 * fRec35[2]))));
		double fTemp22 = max((double)-1, min((double)1, (fSlow10 * ((fConst50 * fRec35[1]) + (fConst6 * (fRec35[2] + fRec35[0]))))));
		double fTemp23 = (fConst7 * fRec37[1]);
		fRec39[0] = ((fConst39 * fRec39[1]) + (fConst38 * ((fConst10 * fVec2[0]) + (fConst51 * fVec2[1]))));
		fRec38[0] = (fRec39[0] - (fConst15 * ((fConst13 * fRec38[1]) + (fConst11 * fRec38[2]))));
		fRec37[0] = ((fConst15 * ((fConst52 * fRec38[1]) + (fConst12 * (fRec38[2] + fRec38[0])))) - (fConst44 * ((fConst43 * fRec37[2]) + fTemp23)));
		double fTemp24 = max((double)-1, min((double)1, (fSlow11 * (fRec37[2] + (fConst44 * (fTemp23 + (fConst43 * fRec37[0])))))));
		double fTemp25 = ((1.584893192 * ((0.8413951417869425 * (fTemp24 * (1 - (0.3333333333333333 * faustpower<2>(fTemp24))))) + ((fTemp22 * (1 - (0.3333333333333333 * faustpower<2>(fTemp22)))) + (fTemp21 * (1 - (0.3333333333333333 * faustpower<2>(fTemp21))))))) + (1.2589412 * (fTemp18 * (1 - (0.3333333333333333 * faustpower<2>(fTemp18))))));
		fVec4[0] = fTemp25;
		fRec22[0] = ((fConst56 * fRec22[1]) + (fConst55 * (fVec4[0] + fVec4[1])));
		double fTemp26 = max((double)-1, min((double)1, (fSlow9 * max(-0.7, min(0.7, fTemp14)))));
		double fTemp27 = ((0.5 * (fTemp26 * (1 - (0.3333333333333333 * faustpower<2>(fTemp26))))) + ((fSlow12 * fRec22[0]) + (fTemp13 * ((fSlow6 * fRec18[0]) + (fTemp0 * (0.024937655860349125 + (fSlow4 * (0.07481296758104737 - (0.0997506234413965 * fabs((0.024937655860349125 * (fTemp13 * fTemp0))))))))))));
		fVec5[0] = (1e-15 + fTemp27);
		fRec17[0] = ((0.9302847925323914 * (1e-15 + (fTemp27 + fVec5[1]))) - (0.8605695850647829 * fRec17[1]));
		fRec16[0] = (fRec17[0] - ((1.8405051250752198 * fRec16[1]) + (0.8612942439318627 * fRec16[2])));
		double fTemp28 = (0.027 * fRec15[1]);
		fVec6[0] = (1e-15 + fTemp28);
		fRec40[0] = ((fConst60 * fRec40[1]) + (fConst59 * (1e-15 + (fTemp28 + fVec6[1]))));
		fRec15[0] = (Ftube(TUBE_TABLE_12AT7_68k, ((fRec40[0] + (0.9254498422517706 * (fRec16[0] + (fRec16[2] + (2.0 * fRec16[1]))))) - 2.617753)) - 153.04618518518518);
		fRec14[0] = ((fConst33 * fRec14[1]) + (fConst61 * ((fConst29 * fRec15[0]) + (fConst30 * fRec15[1]))));
		fVec7[0] = (1e-15 + fRec13[1]);
		fRec44[0] = ((0.9302847925323914 * (1e-15 + (fRec13[1] + fVec7[1]))) - (0.8605695850647829 * fRec44[1]));
		fRec43[0] = (fRec44[0] - ((1.8405051250752198 * fRec43[1]) + (0.8612942439318627 * fRec43[2])));
		double fTemp29 = (0.015 * fRec42[1]);
		fVec8[0] = (1e-15 + fTemp29);
		fRec45[0] = ((fConst65 * fRec45[1]) + (fConst64 * (1e-15 + (fTemp29 + fVec8[1]))));
		fRec42[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec45[0] + (0.9254498422517706 * (fRec43[0] + (fRec43[2] + (2.0 * fRec43[1]))))) - 1.887332)) - 124.17786666666666);
		fRec41[0] = ((fConst33 * fRec41[1]) + (fConst61 * ((fConst29 * fRec42[0]) + (fConst30 * fRec42[1]))));
		fRec13[0] = ((0.6 * fRec41[0]) - fRec14[0]);
		double fTemp30 = (fRec13[0] * fRec12[0]);
		fVec9[0] = fTemp30;
		fRec11[0] = ((fConst56 * fRec11[1]) + (fConst55 * (fVec9[0] + fVec9[1])));
		fVec10[0] = (1e-15 + fRec11[0]);
		fRec10[0] = ((0.9302847925323914 * (1e-15 + (fRec11[0] + fVec10[1]))) - (0.8605695850647829 * fRec10[1]));
		fRec9[0] = (fRec10[0] - ((1.8405051250752198 * fRec9[1]) + (0.8612942439318627 * fRec9[2])));
		double fTemp31 = (0.015 * fRec8[1]);
		fVec11[0] = (1e-15 + fTemp31);
		fRec46[0] = ((fConst65 * fRec46[1]) + (fConst64 * (1e-15 + (fTemp31 + fVec11[1]))));
		fRec8[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec46[0] + (0.9254498422517706 * (fRec9[0] + (fRec9[2] + (2.0 * fRec9[1]))))) - 1.887332)) - 124.17786666666666);
		fRec7[0] = ((fConst33 * fRec7[1]) + (fConst61 * ((fConst29 * fRec8[0]) + (fConst30 * fRec8[1]))));
		fVec12[0] = (1e-15 + fRec6[1]);
		fRec50[0] = ((0.9302847925323914 * (1e-15 + (fRec6[1] + fVec12[1]))) - (0.8605695850647829 * fRec50[1]));
		fRec49[0] = (fRec50[0] - ((1.8405051250752198 * fRec49[1]) + (0.8612942439318627 * fRec49[2])));
		double fTemp32 = (0.0082 * fRec48[1]);
		fVec13[0] = (1e-15 + fTemp32);
		fRec51[0] = ((fConst69 * fRec51[1]) + (fConst68 * (1e-15 + (fTemp32 + fVec13[1]))));
		fRec48[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec51[0] + (0.9254498422517706 * (fRec49[0] + (fRec49[2] + (2.0 * fRec49[1]))))) - 1.256962)) - 96.7119512195122);
		fRec47[0] = ((fConst33 * fRec47[1]) + (fConst61 * ((fConst29 * fRec48[0]) + (fConst30 * fRec48[1]))));
		fRec6[0] = ((0.6 * fRec47[0]) + fRec7[0]);
		fRec5[0] = ((fConst56 * fRec5[1]) + (fConst55 * (fRec6[1] + fRec6[0])));
		fVec14[0] = (1e-15 + fRec5[0]);
		fRec4[0] = ((0.9302847925323914 * (1e-15 + (fRec5[0] + fVec14[1]))) - (0.8605695850647829 * fRec4[1]));
		fRec3[0] = (fRec4[0] - ((1.8405051250752198 * fRec3[1]) + (0.8612942439318627 * fRec3[2])));
		double fTemp33 = (0.0082 * fRec2[1]);
		fVec15[0] = (1e-15 + fTemp33);
		fRec52[0] = ((fConst69 * fRec52[1]) + (fConst68 * (1e-15 + (fTemp33 + fVec15[1]))));
		fRec2[0] = (Ftube(TUBE_TABLE_12AT7_250k, ((fRec52[0] + (0.9254498422517706 * (fRec3[0] + (fRec3[2] + (2.0 * fRec3[1]))))) - 1.256962)) - 96.7119512195122);
		fRec1[0] = ((fConst33 * fRec1[1]) + (fConst61 * ((fConst29 * fRec2[0]) + (fConst30 * fRec2[1]))));
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec52[1] = fRec52[0];
		fVec15[1] = fVec15[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fVec14[1] = fVec14[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec47[1] = fRec47[0];
		fRec48[1] = fRec48[0];
		fRec51[1] = fRec51[0];
		fVec13[1] = fVec13[0];
		fRec49[2] = fRec49[1]; fRec49[1] = fRec49[0];
		fRec50[1] = fRec50[0];
		fVec12[1] = fVec12[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec46[1] = fRec46[0];
		fVec11[1] = fVec11[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fVec10[1] = fVec10[0];
		fRec11[1] = fRec11[0];
		fVec9[1] = fVec9[0];
		fRec13[1] = fRec13[0];
		fRec41[1] = fRec41[0];
		fRec42[1] = fRec42[0];
		fRec45[1] = fRec45[0];
		fVec8[1] = fVec8[0];
		fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
		fRec44[1] = fRec44[0];
		fVec7[1] = fVec7[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec40[1] = fRec40[0];
		fVec6[1] = fVec6[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fVec5[1] = fVec5[0];
		fRec22[1] = fRec22[0];
		fVec4[1] = fVec4[0];
		fRec37[2] = fRec37[1]; fRec37[1] = fRec37[0];
		fRec38[2] = fRec38[1]; fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec35[2] = fRec35[1]; fRec35[1] = fRec35[0];
		fRec36[1] = fRec36[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec34[1] = fRec34[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fVec3[1] = fVec3[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fVec2[1] = fVec2[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fVec1[1] = fVec1[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		IOTA = IOTA+1;
		fRec21[1] = fRec21[0];
		fRec18[1] = fRec18[0];
		fRec12[1] = fRec12[0];
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

} // end namespace gxamp17
