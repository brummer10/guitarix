// generated from file '../src/LV2/faust/gxamp13.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp13 {

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
	double 	fRec8[2];
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
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fRec22[2];
	int 	IOTA;
	double 	fVec0[32768];
	int 	iConst37;
	double 	fRec21[2];
	double 	fConst38;
	double 	fRec20[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec23[2];
	double 	fRec19[3];
	double 	fVec1[2];
	double 	fConst39;
	double 	fConst40;
	double 	fRec18[2];
	double 	fConst41;
	double 	fRec17[2];
	double 	fRec16[3];
	double 	fVec2[2];
	double 	fConst42;
	double 	fConst43;
	double 	fRec15[2];
	double 	fRec14[3];
	double 	fConst44;
	double 	fRec13[3];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fRec27[2];
	double 	fRec26[3];
	double 	fVec3[2];
	double 	fConst49;
	double 	fConst50;
	double 	fRec25[2];
	double 	fRec24[3];
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	double 	fRec31[2];
	double 	fRec30[3];
	double 	fConst55;
	double 	fRec29[3];
	double 	fRec28[3];
	double 	fRec33[2];
	double 	fRec32[3];
	double 	fVec4[2];
	double 	fConst56;
	double 	fRec12[2];
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fVec5[2];
	double 	fConst60;
	double 	fRec34[2];
	double 	fRec11[2];
	double 	fConst61;
	double 	fRec10[2];
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fVec6[2];
	double 	fConst65;
	double 	fRec37[2];
	double 	fRec36[2];
	double 	fRec35[2];
	double 	fRec9[2];
	double 	fVec7[2];
	double 	fRec7[2];
	double 	fVec8[2];
	double 	fRec38[2];
	double 	fRec6[2];
	double 	fRec5[2];
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fVec9[2];
	double 	fConst69;
	double 	fRec41[2];
	double 	fRec40[2];
	double 	fRec39[2];
	double 	fRec4[2];
	double 	fRec3[2];
	double 	fVec10[2];
	double 	fRec42[2];
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
	id = "6DJ8 feedback";
	name = N_("6DJ8 feedback");
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
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<32768; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<3; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
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
	fConst7 = tan((942.4777960769379 / double(iConst0)));
	fConst8 = (1.0 / faustpower<2>(fConst7));
	fConst9 = (2 * (1 - fConst8));
	fConst10 = (1.0 / fConst7);
	fConst11 = (1 + ((fConst10 - 1.0) / fConst7));
	fConst12 = (1.0 / (1 + ((1.0 + fConst10) / fConst7)));
	fConst13 = tan((3769.9111843077517 / double(iConst0)));
	fConst14 = (1.0 / faustpower<2>(fConst13));
	fConst15 = (2 * (1 - fConst14));
	fConst16 = (1.0 / fConst13);
	fConst17 = (1 + ((fConst16 - 1.0000000000000004) / fConst13));
	fConst18 = (1 + ((fConst16 + 1.0000000000000004) / fConst13));
	fConst19 = (1.0 / fConst18);
	fConst20 = (1 + fConst16);
	fConst21 = (0 - ((1 - fConst16) / fConst20));
	fConst22 = tan((10053.096491487338 / double(iConst0)));
	fConst23 = (1.0 / faustpower<2>(fConst22));
	fConst24 = (2 * (1 - fConst23));
	fConst25 = (1.0 / fConst22);
	fConst26 = (1 + ((fConst25 - 1.0000000000000004) / fConst22));
	fConst27 = (1 + ((1.0000000000000004 + fConst25) / fConst22));
	fConst28 = (1.0 / fConst27);
	fConst29 = (1 + fConst25);
	fConst30 = (0 - ((1 - fConst25) / fConst29));
	fConst31 = tan((47123.8898038469 / double(iConst0)));
	fConst32 = (2 * (1 - (1.0 / faustpower<2>(fConst31))));
	fConst33 = (1.0 / fConst31);
	fConst34 = (1 + ((fConst33 - 1.414213562373095) / fConst31));
	fConst35 = (1 + ((1.414213562373095 + fConst33) / fConst31));
	fConst36 = (1.0 / fConst35);
	IOTA = 0;
	iConst37 = int((int((0.1111111111111111 * iConst0)) & 65535));
	fConst38 = (0.009000000000000008 / double(iConst0));
	fConst39 = (0 - fConst1);
	fConst40 = (1.0 / (fConst2 * fConst35));
	fConst41 = (1.0 / fConst29);
	fConst42 = (0 - fConst16);
	fConst43 = (1.0 / (fConst20 * fConst27));
	fConst44 = (2 * (0 - fConst14));
	fConst45 = (1 + ((fConst10 - 1.0000000000000004) / fConst7));
	fConst46 = (1.0 / (1 + ((fConst10 + 1.0000000000000004) / fConst7)));
	fConst47 = (1 + fConst10);
	fConst48 = (0 - ((1 - fConst10) / fConst47));
	fConst49 = (0 - fConst10);
	fConst50 = (1.0 / (fConst47 * fConst18));
	fConst51 = (2 * (0 - fConst8));
	fConst52 = (1 + ((fConst16 - 1.0) / fConst13));
	fConst53 = (1.0 / (1 + ((1.0 + fConst16) / fConst13)));
	fConst54 = (0 - fConst25);
	fConst55 = (2 * (0 - fConst23));
	fConst56 = (1.0 / fConst5);
	fConst57 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst58 = (1 + fConst57);
	fConst59 = (0 - ((1 - fConst57) / fConst58));
	fConst60 = (1.0 / fConst58);
	fConst61 = (0.05 / fConst2);
	fConst62 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst63 = (1 + fConst62);
	fConst64 = (0 - ((1 - fConst62) / fConst63));
	fConst65 = (1.0 / fConst63);
	fConst66 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst67 = (1 + fConst66);
	fConst68 = (0 - ((1 - fConst66) / fConst67));
	fConst69 = (1.0 / fConst67);
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
	double 	fSlow5 = pow(1e+01,(2 * fSlow3));
	double 	fSlow6 = (fConst46 * fSlow5);
	double 	fSlow7 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow8 = (fConst46 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow9 = (2 * (fSlow3 - 0.5));
	double 	fSlow10 = (1 - max((double)0, (0 - fSlow9)));
	double 	fSlow11 = (0.024937655860349125 * (1 - max((double)0, fSlow9)));
	double 	fSlow12 = (1.25 * fSlow3);
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec8[0] = (fSlow1 + (0.999 * fRec8[1]));
		double fTemp0 = (fConst9 * fRec13[1]);
		double fTemp1 = (double)input0[i];
		double fTemp2 = fabs(fTemp1);
		fRec22[0] = ((9.999999999998899e-05 * fTemp2) + (0.9999 * fRec22[1]));
		double fTemp3 = max(fRec22[0], fTemp2);
		fVec0[IOTA&32767] = fTemp3;
		fRec21[0] = ((fVec0[IOTA&32767] + fRec21[1]) - fVec0[(IOTA-iConst37)&32767]);
		fRec20[0] = ((fConst38 * fRec21[0]) + (0.999 * fRec20[1]));
		double fTemp4 = max((double)-1, min(-0.01, (fVec0[IOTA&32767] - (1.0 + (1.02 * fRec20[0])))));
		double fTemp5 = (0 - fTemp4);
		double fTemp6 = (40.1 * fTemp5);
		double fTemp7 = max((double)-600, fTemp6);
		double fTemp8 = (0 - fTemp7);
		double fTemp9 = (fTemp1 - fTemp4);
		double fTemp10 = (40.1 * fTemp9);
		double fTemp11 = max((double)-600, fTemp10);
		double fTemp12 = (0 - fTemp11);
		double fTemp13 = (((int((fabs(fTemp10) > 0.0001)))?((int((fTemp11 < -50)))?(exp(fTemp11) * fTemp12):(fTemp11 / (1 - exp(fTemp12)))):(1 + (fTemp9 * (20.05 + (134.00083333333336 * fTemp9))))) - ((int((fabs(fTemp6) > 0.0001)))?((int((fTemp7 < -50)))?(exp(fTemp7) * fTemp8):(fTemp7 / (1 - exp(fTemp8)))):(1 + (fTemp5 * (20.05 + (134.00083333333336 * fTemp5))))));
		fRec23[0] = (fSlow2 + (0.999 * fRec23[1]));
		double fTemp14 = (0.024937655860349125 * (fRec23[0] * fTemp13));
		fRec19[0] = (fTemp14 - (fConst36 * ((fConst34 * fRec19[2]) + (fConst32 * fRec19[1]))));
		double fTemp15 = (fRec19[2] + (fRec19[0] + (2 * fRec19[1])));
		fVec1[0] = fTemp15;
		fRec18[0] = ((fConst40 * ((fConst39 * fVec1[1]) + (fConst1 * fVec1[0]))) + (fConst3 * fRec18[1]));
		fRec17[0] = ((fConst41 * (fRec18[0] + fRec18[1])) + (fConst30 * fRec17[1]));
		fRec16[0] = (fRec17[0] - (fConst28 * ((fConst26 * fRec16[2]) + (fConst24 * fRec16[1]))));
		double fTemp16 = (fRec16[2] + (fRec16[0] + (2 * fRec16[1])));
		fVec2[0] = fTemp16;
		fRec15[0] = ((fConst43 * ((fConst42 * fVec2[1]) + (fConst16 * fVec2[0]))) + (fConst21 * fRec15[1]));
		fRec14[0] = (fRec15[0] - (fConst19 * ((fConst17 * fRec14[2]) + (fConst15 * fRec14[1]))));
		fRec13[0] = ((fConst19 * (((fConst14 * fRec14[0]) + (fConst44 * fRec14[1])) + (fConst14 * fRec14[2]))) - (fConst12 * ((fConst11 * fRec13[2]) + fTemp0)));
		double fTemp17 = max((double)-1, min((double)1, (fSlow4 * (fRec13[2] + (fConst12 * (fTemp0 + (fConst11 * fRec13[0])))))));
		fRec27[0] = ((fConst43 * (fVec2[0] + fVec2[1])) + (fConst21 * fRec27[1]));
		fRec26[0] = (fRec27[0] - (fConst19 * ((fConst17 * fRec26[2]) + (fConst15 * fRec26[1]))));
		double fTemp18 = (fRec26[2] + (fRec26[0] + (2 * fRec26[1])));
		fVec3[0] = fTemp18;
		fRec25[0] = ((fConst50 * ((fConst49 * fVec3[1]) + (fConst10 * fVec3[0]))) + (fConst48 * fRec25[1]));
		fRec24[0] = (fRec25[0] - (fConst46 * ((fConst45 * fRec24[2]) + (fConst9 * fRec24[1]))));
		double fTemp19 = max((double)-1, min((double)1, (fSlow6 * (((fConst8 * fRec24[0]) + (fConst51 * fRec24[1])) + (fConst8 * fRec24[2])))));
		double fTemp20 = (fConst9 * fRec28[1]);
		double fTemp21 = (fConst15 * fRec29[1]);
		fRec31[0] = ((fConst41 * ((fConst54 * fRec18[1]) + (fConst25 * fRec18[0]))) + (fConst30 * fRec31[1]));
		fRec30[0] = (fRec31[0] - (fConst28 * ((fConst26 * fRec30[2]) + (fConst24 * fRec30[1]))));
		fRec29[0] = ((fConst28 * (((fConst23 * fRec30[0]) + (fConst55 * fRec30[1])) + (fConst23 * fRec30[2]))) - (fConst53 * ((fConst52 * fRec29[2]) + fTemp21)));
		fRec28[0] = ((fRec29[2] + (fConst53 * (fTemp21 + (fConst52 * fRec29[0])))) - (fConst12 * ((fConst11 * fRec28[2]) + fTemp20)));
		double fTemp22 = max((double)-1, min((double)1, (fSlow7 * (fRec28[2] + (fConst12 * (fTemp20 + (fConst11 * fRec28[0])))))));
		fRec33[0] = ((fConst50 * (fVec3[0] + fVec3[1])) + (fConst48 * fRec33[1]));
		fRec32[0] = (fRec33[0] - (fConst46 * ((fConst45 * fRec32[2]) + (fConst9 * fRec32[1]))));
		double fTemp23 = max((double)-1, min((double)1, (fSlow8 * (fRec32[2] + (fRec32[0] + (2 * fRec32[1]))))));
		double fTemp24 = ((1.2589412 * (fTemp23 * (1 - (0.3333333333333333 * faustpower<2>(fTemp23))))) + (1.584893192 * ((fTemp22 * (1 - (0.3333333333333333 * faustpower<2>(fTemp22)))) + ((fTemp19 * (1 - (0.3333333333333333 * faustpower<2>(fTemp19)))) + (0.8413951417869425 * (fTemp17 * (1 - (0.3333333333333333 * faustpower<2>(fTemp17)))))))));
		fVec4[0] = fTemp24;
		fRec12[0] = ((fConst56 * (fVec4[0] + fVec4[1])) + (fConst6 * fRec12[1]));
		double fTemp25 = (1e-15 + (0.027 * fRec11[1]));
		fVec5[0] = fTemp25;
		fRec34[0] = ((fConst60 * (fVec5[0] + fVec5[1])) + (fConst59 * fRec34[1]));
		double fTemp26 = max((double)-1, min((double)1, (fSlow5 * max(-0.7, min(0.7, fTemp14)))));
		double fTemp27 = (1 - fRec23[0]);
		fRec11[0] = (Ftube(TUBE_TABLE_6DJ8_68k, (((fTemp13 * ((fTemp27 * (0.024937655860349125 + (fSlow12 * ((0.0997506234413965 - (0.0997506234413965 * fabs((0.024937655860349125 * (fTemp27 * fTemp13))))) - 0.024937655860349125)))) + (fSlow11 * fRec23[0]))) + ((0.5 * (fTemp26 * (1 - (0.3333333333333333 * faustpower<2>(fTemp26))))) + (fRec34[0] + (fSlow10 * fRec12[0])))) - 1.863945999999999)) - 60.96496296296296);
		fRec10[0] = ((fConst61 * ((fConst39 * fRec11[1]) + (fConst1 * fRec11[0]))) + (fConst3 * fRec10[1]));
		double fTemp28 = (1e-15 + (0.015 * fRec36[1]));
		fVec6[0] = fTemp28;
		fRec37[0] = ((fConst65 * (fVec6[0] + fVec6[1])) + (fConst64 * fRec37[1]));
		fRec36[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec37[0] + fRec9[1]) - 1.2716089999999989)) - 45.22606666666667);
		fRec35[0] = ((fConst61 * ((fConst39 * fRec36[1]) + (fConst1 * fRec36[0]))) + (fConst3 * fRec35[1]));
		fRec9[0] = ((0.6 * fRec35[0]) - fRec10[0]);
		double fTemp29 = (fRec9[0] * fRec8[0]);
		fVec7[0] = fTemp29;
		fRec7[0] = ((fConst56 * (fVec7[0] + fVec7[1])) + (fConst6 * fRec7[1]));
		double fTemp30 = (1e-15 + (0.015 * fRec6[1]));
		fVec8[0] = fTemp30;
		fRec38[0] = ((fConst65 * (fVec8[0] + fVec8[1])) + (fConst64 * fRec38[1]));
		fRec6[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec38[0] + fRec7[0]) - 1.2716089999999989)) - 45.22606666666667);
		fRec5[0] = ((fConst61 * ((fConst39 * fRec6[1]) + (fConst1 * fRec6[0]))) + (fConst3 * fRec5[1]));
		double fTemp31 = (1e-15 + (0.0082 * fRec40[1]));
		fVec9[0] = fTemp31;
		fRec41[0] = ((fConst69 * (fVec9[0] + fVec9[1])) + (fConst68 * fRec41[1]));
		fRec40[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec41[0] + fRec4[1]) - 0.797042999999999)) - 32.799634146341475);
		fRec39[0] = ((fConst61 * ((fConst39 * fRec40[1]) + (fConst1 * fRec40[0]))) + (fConst3 * fRec39[1]));
		fRec4[0] = ((0.6 * fRec39[0]) + fRec5[0]);
		fRec3[0] = ((fConst56 * (fRec4[0] + fRec4[1])) + (fConst6 * fRec3[1]));
		double fTemp32 = (1e-15 + (0.0082 * fRec2[1]));
		fVec10[0] = fTemp32;
		fRec42[0] = ((fConst69 * (fVec10[0] + fVec10[1])) + (fConst68 * fRec42[1]));
		fRec2[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec42[0] + fRec3[0]) - 0.797042999999999)) - 32.799634146341475);
		fRec1[0] = ((fConst61 * ((fConst39 * fRec2[1]) + (fConst1 * fRec2[0]))) + (fConst3 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec42[1] = fRec42[0];
		fVec10[1] = fVec10[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec39[1] = fRec39[0];
		fRec40[1] = fRec40[0];
		fRec41[1] = fRec41[0];
		fVec9[1] = fVec9[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec38[1] = fRec38[0];
		fVec8[1] = fVec8[0];
		fRec7[1] = fRec7[0];
		fVec7[1] = fVec7[0];
		fRec9[1] = fRec9[0];
		fRec35[1] = fRec35[0];
		fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fVec6[1] = fVec6[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec34[1] = fRec34[0];
		fVec5[1] = fVec5[0];
		fRec12[1] = fRec12[0];
		fVec4[1] = fVec4[0];
		fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
		fRec33[1] = fRec33[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fVec3[1] = fVec3[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec2[1] = fVec2[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fVec1[1] = fVec1[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec23[1] = fRec23[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		IOTA = IOTA+1;
		fRec22[1] = fRec22[0];
		fRec8[1] = fRec8[0];
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

} // end namespace gxamp13
