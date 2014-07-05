// generated from file '../src/LV2/faust/gxamp13_stereo.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp13_stereo {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec8[2];
	double 	fRec14[2];
	int 	IOTA;
	double 	fVec0[32768];
	int 	iConst0;
	int 	iConst1;
	double 	fRec13[2];
	double 	fConst2;
	double 	fRec12[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec15[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fVec1[2];
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fRec16[2];
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
	double 	fRec25[3];
	double 	fVec2[2];
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fRec24[2];
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fVec3[2];
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fRec21[2];
	double 	fRec20[3];
	double 	fVec4[2];
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fRec19[2];
	double 	fRec18[3];
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fConst50;
	double 	fRec26[3];
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fRec32[2];
	double 	fRec31[3];
	double 	fConst54;
	double 	fRec30[3];
	double 	fRec29[3];
	double 	fConst55;
	double 	fRec34[2];
	double 	fRec33[3];
	double 	fConst56;
	double 	fVec5[2];
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fRec17[2];
	double 	fRec11[2];
	double 	fConst61;
	double 	fRec10[2];
	double 	fVec6[2];
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
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
	double 	fVec9[2];
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
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
	double 	fRec55[2];
	double 	fVec11[32768];
	double 	fRec54[2];
	double 	fRec53[2];
	double 	fVec12[2];
	double 	fRec56[2];
	double 	fRec65[3];
	double 	fVec13[2];
	double 	fRec64[2];
	double 	fRec63[2];
	double 	fRec62[3];
	double 	fVec14[2];
	double 	fRec61[2];
	double 	fRec60[3];
	double 	fVec15[2];
	double 	fRec59[2];
	double 	fRec58[3];
	double 	fRec68[2];
	double 	fRec67[3];
	double 	fRec66[3];
	double 	fRec72[2];
	double 	fRec71[3];
	double 	fRec70[3];
	double 	fRec69[3];
	double 	fRec74[2];
	double 	fRec73[3];
	double 	fVec16[2];
	double 	fRec57[2];
	double 	fRec52[2];
	double 	fRec51[2];
	double 	fVec17[2];
	double 	fRec77[2];
	double 	fRec76[2];
	double 	fRec75[2];
	double 	fRec50[2];
	double 	fVec18[2];
	double 	fRec49[2];
	double 	fVec19[2];
	double 	fRec78[2];
	double 	fRec48[2];
	double 	fRec47[2];
	double 	fVec20[2];
	double 	fRec81[2];
	double 	fRec80[2];
	double 	fRec79[2];
	double 	fRec46[2];
	double 	fRec45[2];
	double 	fVec21[2];
	double 	fRec82[2];
	double 	fRec44[2];
	double 	fRec43[2];
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2*);
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
	mono_audio = 0;
	stereo_audio = compute_static;
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
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<32768; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
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
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
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
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<32768; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec54[i] = 0;
	for (int i=0; i<2; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) fVec12[i] = 0;
	for (int i=0; i<2; i++) fRec56[i] = 0;
	for (int i=0; i<3; i++) fRec65[i] = 0;
	for (int i=0; i<2; i++) fVec13[i] = 0;
	for (int i=0; i<2; i++) fRec64[i] = 0;
	for (int i=0; i<2; i++) fRec63[i] = 0;
	for (int i=0; i<3; i++) fRec62[i] = 0;
	for (int i=0; i<2; i++) fVec14[i] = 0;
	for (int i=0; i<2; i++) fRec61[i] = 0;
	for (int i=0; i<3; i++) fRec60[i] = 0;
	for (int i=0; i<2; i++) fVec15[i] = 0;
	for (int i=0; i<2; i++) fRec59[i] = 0;
	for (int i=0; i<3; i++) fRec58[i] = 0;
	for (int i=0; i<2; i++) fRec68[i] = 0;
	for (int i=0; i<3; i++) fRec67[i] = 0;
	for (int i=0; i<3; i++) fRec66[i] = 0;
	for (int i=0; i<2; i++) fRec72[i] = 0;
	for (int i=0; i<3; i++) fRec71[i] = 0;
	for (int i=0; i<3; i++) fRec70[i] = 0;
	for (int i=0; i<3; i++) fRec69[i] = 0;
	for (int i=0; i<2; i++) fRec74[i] = 0;
	for (int i=0; i<3; i++) fRec73[i] = 0;
	for (int i=0; i<2; i++) fVec16[i] = 0;
	for (int i=0; i<2; i++) fRec57[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fVec17[i] = 0;
	for (int i=0; i<2; i++) fRec77[i] = 0;
	for (int i=0; i<2; i++) fRec76[i] = 0;
	for (int i=0; i<2; i++) fRec75[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<2; i++) fVec18[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) fVec19[i] = 0;
	for (int i=0; i<2; i++) fRec78[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fVec20[i] = 0;
	for (int i=0; i<2; i++) fRec81[i] = 0;
	for (int i=0; i<2; i++) fRec80[i] = 0;
	for (int i=0; i<2; i++) fRec79[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fVec21[i] = 0;
	for (int i=0; i<2; i++) fRec82[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<2; i++) fRec43[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	iConst0 = min(192000, max(1, fSamplingFreq));
	iConst1 = int((int((0.1111111111111111 * iConst0)) & 65535));
	fConst2 = (0.009000000000000008 / double(iConst0));
	fConst3 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst4 = (1 + fConst3);
	fConst5 = (1.0 / fConst4);
	fConst6 = (0 - ((1 - fConst3) / fConst4));
	fConst7 = tan((942.4777960769379 / double(iConst0)));
	fConst8 = (1.0 / faustpower<2>(fConst7));
	fConst9 = (2 * (1 - fConst8));
	fConst10 = (1.0 / fConst7);
	fConst11 = (1 + ((fConst10 - 1.0000000000000004) / fConst7));
	fConst12 = (1.0 / (1 + ((fConst10 + 1.0000000000000004) / fConst7)));
	fConst13 = tan((3769.9111843077517 / double(iConst0)));
	fConst14 = (1.0 / faustpower<2>(fConst13));
	fConst15 = (2 * (1 - fConst14));
	fConst16 = (1.0 / fConst13);
	fConst17 = (1 + ((fConst16 - 1.0000000000000004) / fConst13));
	fConst18 = (1 + ((fConst16 + 1.0000000000000004) / fConst13));
	fConst19 = (1.0 / fConst18);
	fConst20 = tan((10053.096491487338 / double(iConst0)));
	fConst21 = (1.0 / faustpower<2>(fConst20));
	fConst22 = (2 * (1 - fConst21));
	fConst23 = (1.0 / fConst20);
	fConst24 = (1 + ((fConst23 - 1.0000000000000004) / fConst20));
	fConst25 = (1 + ((1.0000000000000004 + fConst23) / fConst20));
	fConst26 = (1.0 / fConst25);
	fConst27 = tan((47123.8898038469 / double(iConst0)));
	fConst28 = (2 * (1 - (1.0 / faustpower<2>(fConst27))));
	fConst29 = (1.0 / fConst27);
	fConst30 = (1 + ((fConst29 - 1.414213562373095) / fConst27));
	fConst31 = (1 + ((1.414213562373095 + fConst29) / fConst27));
	fConst32 = (1.0 / fConst31);
	fConst33 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst34 = (0 - fConst33);
	fConst35 = (1 + fConst33);
	fConst36 = (1.0 / (fConst35 * fConst31));
	fConst37 = (0 - ((1 - fConst33) / fConst35));
	fConst38 = (1 + fConst23);
	fConst39 = (1.0 / fConst38);
	fConst40 = (0 - ((1 - fConst23) / fConst38));
	fConst41 = (1 + fConst16);
	fConst42 = (1.0 / (fConst41 * fConst25));
	fConst43 = (0 - ((1 - fConst16) / fConst41));
	fConst44 = (1 + fConst10);
	fConst45 = (1.0 / (fConst44 * fConst18));
	fConst46 = (0 - ((1 - fConst10) / fConst44));
	fConst47 = (1 + ((fConst10 - 1.0) / fConst7));
	fConst48 = (1.0 / (1 + ((1.0 + fConst10) / fConst7)));
	fConst49 = (0 - fConst16);
	fConst50 = (2 * (0 - fConst14));
	fConst51 = (1 + ((fConst16 - 1.0) / fConst13));
	fConst52 = (1.0 / (1 + ((1.0 + fConst16) / fConst13)));
	fConst53 = (0 - fConst23);
	fConst54 = (2 * (0 - fConst21));
	fConst55 = (0 - fConst10);
	fConst56 = (2 * (0 - fConst8));
	fConst57 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst58 = (1 + fConst57);
	fConst59 = (1.0 / fConst58);
	fConst60 = (0 - ((1 - fConst57) / fConst58));
	fConst61 = (0.05 / fConst35);
	fConst62 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst63 = (1 + fConst62);
	fConst64 = (1.0 / fConst63);
	fConst65 = (0 - ((1 - fConst62) / fConst63));
	fConst66 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst67 = (1 + fConst66);
	fConst68 = (1.0 / fConst67);
	fConst69 = (0 - ((1 - fConst66) / fConst67));
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider0))));
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider1))));
	double 	fSlow2 = (1.000000000000001e-05 * double(fslider2));
	double 	fSlow3 = double(fslider3);
	double 	fSlow4 = pow(1e+01,(2 * fSlow3));
	double 	fSlow5 = (fConst12 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow6 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow7 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow8 = (fConst12 * fSlow4);
	double 	fSlow9 = (2 * (fSlow3 - 0.5));
	double 	fSlow10 = (1 - max((double)0, (0 - fSlow9)));
	double 	fSlow11 = (0.024937655860349125 * (1 - max((double)0, fSlow9)));
	double 	fSlow12 = (1.25 * fSlow3);
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.999 * fRec0[1]) + fSlow0);
		fRec8[0] = ((0.999 * fRec8[1]) + fSlow1);
		double fTemp0 = (double)input0[i];
		double fTemp1 = fabs(fTemp0);
		fRec14[0] = ((0.9999 * fRec14[1]) + (9.999999999998899e-05 * fTemp1));
		double fTemp2 = max(fRec14[0], fTemp1);
		fVec0[IOTA&32767] = fTemp2;
		fRec13[0] = ((fVec0[IOTA&32767] + fRec13[1]) - fVec0[(IOTA-iConst1)&32767]);
		fRec12[0] = ((0.999 * fRec12[1]) + (fConst2 * fRec13[0]));
		double fTemp3 = max((double)-1, min(-0.01, (fVec0[IOTA&32767] - (1.0 + (1.02 * fRec12[0])))));
		double fTemp4 = (0 - fTemp3);
		double fTemp5 = (40.1 * fTemp4);
		double fTemp6 = max((double)-600, fTemp5);
		double fTemp7 = (0 - fTemp6);
		double fTemp8 = (fTemp0 - fTemp3);
		double fTemp9 = (40.1 * fTemp8);
		double fTemp10 = max((double)-600, fTemp9);
		double fTemp11 = (0 - fTemp10);
		double fTemp12 = (((int((fabs(fTemp9) > 0.0001)))?((int((fTemp10 < -50)))?(fTemp11 * exp(fTemp10)):(fTemp10 / (1 - exp(fTemp11)))):(1 + (fTemp8 * (20.05 + (134.00083333333336 * fTemp8))))) - ((int((fabs(fTemp5) > 0.0001)))?((int((fTemp6 < -50)))?(fTemp7 * exp(fTemp6)):(fTemp6 / (1 - exp(fTemp7)))):(1 + (fTemp4 * (20.05 + (134.00083333333336 * fTemp4))))));
		fRec15[0] = (fSlow2 + (0.999 * fRec15[1]));
		double fTemp13 = (0.024937655860349125 * (fRec15[0] * fTemp12));
		double fTemp14 = max((double)-1, min((double)1, (fSlow4 * max(-0.7, min(0.7, fTemp13)))));
		double fTemp15 = (1e-15 + (0.027 * fRec11[1]));
		fVec1[0] = fTemp15;
		fRec16[0] = ((fConst6 * fRec16[1]) + (fConst5 * (fVec1[0] + fVec1[1])));
		fRec25[0] = (fTemp13 - (fConst32 * ((fConst30 * fRec25[2]) + (fConst28 * fRec25[1]))));
		double fTemp16 = (fRec25[2] + (fRec25[0] + (2 * fRec25[1])));
		fVec2[0] = fTemp16;
		fRec24[0] = ((fConst37 * fRec24[1]) + (fConst36 * ((fConst33 * fVec2[0]) + (fConst34 * fVec2[1]))));
		fRec23[0] = ((fConst40 * fRec23[1]) + (fConst39 * (fRec24[0] + fRec24[1])));
		fRec22[0] = (fRec23[0] - (fConst26 * ((fConst24 * fRec22[2]) + (fConst22 * fRec22[1]))));
		double fTemp17 = (fRec22[2] + (fRec22[0] + (2 * fRec22[1])));
		fVec3[0] = fTemp17;
		fRec21[0] = ((fConst43 * fRec21[1]) + (fConst42 * (fVec3[0] + fVec3[1])));
		fRec20[0] = (fRec21[0] - (fConst19 * ((fConst17 * fRec20[2]) + (fConst15 * fRec20[1]))));
		double fTemp18 = (fRec20[2] + (fRec20[0] + (2 * fRec20[1])));
		fVec4[0] = fTemp18;
		fRec19[0] = ((fConst46 * fRec19[1]) + (fConst45 * (fVec4[0] + fVec4[1])));
		fRec18[0] = (fRec19[0] - (fConst12 * ((fConst11 * fRec18[2]) + (fConst9 * fRec18[1]))));
		double fTemp19 = max((double)-1, min((double)1, (fSlow5 * (fRec18[2] + (fRec18[0] + (2 * fRec18[1]))))));
		double fTemp20 = (fConst9 * fRec26[1]);
		fRec28[0] = ((fConst43 * fRec28[1]) + (fConst42 * ((fConst16 * fVec3[0]) + (fConst49 * fVec3[1]))));
		fRec27[0] = (fRec28[0] - (fConst19 * ((fConst17 * fRec27[2]) + (fConst15 * fRec27[1]))));
		fRec26[0] = ((fConst19 * (((fConst14 * fRec27[0]) + (fConst50 * fRec27[1])) + (fConst14 * fRec27[2]))) - (fConst48 * ((fConst47 * fRec26[2]) + fTemp20)));
		double fTemp21 = max((double)-1, min((double)1, (fSlow6 * (fRec26[2] + (fConst48 * (fTemp20 + (fConst47 * fRec26[0])))))));
		double fTemp22 = (fConst9 * fRec29[1]);
		double fTemp23 = (fConst15 * fRec30[1]);
		fRec32[0] = ((fConst40 * fRec32[1]) + (fConst39 * ((fConst23 * fRec24[0]) + (fConst53 * fRec24[1]))));
		fRec31[0] = (fRec32[0] - (fConst26 * ((fConst24 * fRec31[2]) + (fConst22 * fRec31[1]))));
		fRec30[0] = ((fConst26 * (((fConst21 * fRec31[0]) + (fConst54 * fRec31[1])) + (fConst21 * fRec31[2]))) - (fConst52 * ((fConst51 * fRec30[2]) + fTemp23)));
		fRec29[0] = ((fRec30[2] + (fConst52 * (fTemp23 + (fConst51 * fRec30[0])))) - (fConst48 * ((fConst47 * fRec29[2]) + fTemp22)));
		double fTemp24 = max((double)-1, min((double)1, (fSlow7 * (fRec29[2] + (fConst48 * (fTemp22 + (fConst47 * fRec29[0])))))));
		fRec34[0] = ((fConst46 * fRec34[1]) + (fConst45 * ((fConst10 * fVec4[0]) + (fConst55 * fVec4[1]))));
		fRec33[0] = (fRec34[0] - (fConst12 * ((fConst11 * fRec33[2]) + (fConst9 * fRec33[1]))));
		double fTemp25 = max((double)-1, min((double)1, (fSlow8 * (((fConst8 * fRec33[0]) + (fConst56 * fRec33[1])) + (fConst8 * fRec33[2])))));
		double fTemp26 = ((1.584893192 * ((fTemp25 * (1 - (0.3333333333333333 * faustpower<2>(fTemp25)))) + ((fTemp24 * (1 - (0.3333333333333333 * faustpower<2>(fTemp24)))) + (0.8413951417869425 * (fTemp21 * (1 - (0.3333333333333333 * faustpower<2>(fTemp21)))))))) + (1.2589412 * (fTemp19 * (1 - (0.3333333333333333 * faustpower<2>(fTemp19))))));
		fVec5[0] = fTemp26;
		fRec17[0] = ((fConst60 * fRec17[1]) + (fConst59 * (fVec5[0] + fVec5[1])));
		double fTemp27 = (fSlow11 * fRec15[0]);
		double fTemp28 = (1 - fRec15[0]);
		fRec11[0] = (Ftube(TUBE_TABLE_6DJ8_68k, (((fTemp12 * ((fTemp28 * (0.024937655860349125 + (fSlow12 * ((0.0997506234413965 - (0.0997506234413965 * fabs((0.024937655860349125 * (fTemp28 * fTemp12))))) - 0.024937655860349125)))) + fTemp27)) + ((fSlow10 * fRec17[0]) + (fRec16[0] + (0.5 * (fTemp14 * (1 - (0.3333333333333333 * faustpower<2>(fTemp14)))))))) - 1.863945999999999)) - 60.96496296296296);
		fRec10[0] = ((fConst37 * fRec10[1]) + (fConst61 * ((fConst33 * fRec11[0]) + (fConst34 * fRec11[1]))));
		double fTemp29 = (1e-15 + (0.015 * fRec36[1]));
		fVec6[0] = fTemp29;
		fRec37[0] = ((fConst65 * fRec37[1]) + (fConst64 * (fVec6[0] + fVec6[1])));
		fRec36[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec37[0] + fRec9[1]) - 1.2716089999999989)) - 45.22606666666667);
		fRec35[0] = ((fConst37 * fRec35[1]) + (fConst61 * ((fConst33 * fRec36[0]) + (fConst34 * fRec36[1]))));
		fRec9[0] = ((0.6 * fRec35[0]) - fRec10[0]);
		double fTemp30 = (fRec9[0] * fRec8[0]);
		fVec7[0] = fTemp30;
		fRec7[0] = ((fConst60 * fRec7[1]) + (fConst59 * (fVec7[0] + fVec7[1])));
		double fTemp31 = (1e-15 + (0.015 * fRec6[1]));
		fVec8[0] = fTemp31;
		fRec38[0] = ((fConst65 * fRec38[1]) + (fConst64 * (fVec8[0] + fVec8[1])));
		fRec6[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec38[0] + fRec7[0]) - 1.2716089999999989)) - 45.22606666666667);
		fRec5[0] = ((fConst37 * fRec5[1]) + (fConst61 * ((fConst33 * fRec6[0]) + (fConst34 * fRec6[1]))));
		double fTemp32 = (1e-15 + (0.0082 * fRec40[1]));
		fVec9[0] = fTemp32;
		fRec41[0] = ((fConst69 * fRec41[1]) + (fConst68 * (fVec9[0] + fVec9[1])));
		fRec40[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec41[0] + fRec4[1]) - 0.797042999999999)) - 32.799634146341475);
		fRec39[0] = ((fConst37 * fRec39[1]) + (fConst61 * ((fConst33 * fRec40[0]) + (fConst34 * fRec40[1]))));
		fRec4[0] = ((0.6 * fRec39[0]) + fRec5[0]);
		fRec3[0] = ((fConst60 * fRec3[1]) + (fConst59 * (fRec4[0] + fRec4[1])));
		double fTemp33 = (1e-15 + (0.0082 * fRec2[1]));
		fVec10[0] = fTemp33;
		fRec42[0] = ((fConst69 * fRec42[1]) + (fConst68 * (fVec10[0] + fVec10[1])));
		fRec2[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec42[0] + fRec3[0]) - 0.797042999999999)) - 32.799634146341475);
		fRec1[0] = ((fConst37 * fRec1[1]) + (fConst61 * ((fConst33 * fRec2[0]) + (fConst34 * fRec2[1]))));
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		double fTemp34 = (double)input1[i];
		double fTemp35 = fabs(fTemp34);
		fRec55[0] = ((0.9999 * fRec55[1]) + (9.999999999998899e-05 * fTemp35));
		double fTemp36 = max(fRec55[0], fTemp35);
		fVec11[IOTA&32767] = fTemp36;
		fRec54[0] = ((fVec11[IOTA&32767] + fRec54[1]) - fVec11[(IOTA-iConst1)&32767]);
		fRec53[0] = ((0.999 * fRec53[1]) + (fConst2 * fRec54[0]));
		double fTemp37 = max((double)-1, min(-0.01, (fVec11[IOTA&32767] - (1.0 + (1.02 * fRec53[0])))));
		double fTemp38 = (0 - fTemp37);
		double fTemp39 = (40.1 * fTemp38);
		double fTemp40 = max((double)-600, fTemp39);
		double fTemp41 = (0 - fTemp40);
		double fTemp42 = (fTemp34 - fTemp37);
		double fTemp43 = (40.1 * fTemp42);
		double fTemp44 = max((double)-600, fTemp43);
		double fTemp45 = (0 - fTemp44);
		double fTemp46 = (((int((fabs(fTemp43) > 0.0001)))?((int((fTemp44 < -50)))?(fTemp45 * exp(fTemp44)):(fTemp44 / (1 - exp(fTemp45)))):(1 + (fTemp42 * (20.05 + (134.00083333333336 * fTemp42))))) - ((int((fabs(fTemp39) > 0.0001)))?((int((fTemp40 < -50)))?(fTemp41 * exp(fTemp40)):(fTemp40 / (1 - exp(fTemp41)))):(1 + (fTemp38 * (20.05 + (134.00083333333336 * fTemp38))))));
		double fTemp47 = (0.024937655860349125 * (fRec15[0] * fTemp46));
		double fTemp48 = max((double)-1, min((double)1, (fSlow4 * max(-0.7, min(0.7, fTemp47)))));
		double fTemp49 = (1e-15 + (0.027 * fRec52[1]));
		fVec12[0] = fTemp49;
		fRec56[0] = ((fConst6 * fRec56[1]) + (fConst5 * (fVec12[0] + fVec12[1])));
		fRec65[0] = (fTemp47 - (fConst32 * ((fConst30 * fRec65[2]) + (fConst28 * fRec65[1]))));
		double fTemp50 = (fRec65[2] + (fRec65[0] + (2 * fRec65[1])));
		fVec13[0] = fTemp50;
		fRec64[0] = ((fConst37 * fRec64[1]) + (fConst36 * ((fConst33 * fVec13[0]) + (fConst34 * fVec13[1]))));
		fRec63[0] = ((fConst40 * fRec63[1]) + (fConst39 * (fRec64[0] + fRec64[1])));
		fRec62[0] = (fRec63[0] - (fConst26 * ((fConst24 * fRec62[2]) + (fConst22 * fRec62[1]))));
		double fTemp51 = (fRec62[2] + (fRec62[0] + (2 * fRec62[1])));
		fVec14[0] = fTemp51;
		fRec61[0] = ((fConst43 * fRec61[1]) + (fConst42 * (fVec14[0] + fVec14[1])));
		fRec60[0] = (fRec61[0] - (fConst19 * ((fConst17 * fRec60[2]) + (fConst15 * fRec60[1]))));
		double fTemp52 = (fRec60[2] + (fRec60[0] + (2 * fRec60[1])));
		fVec15[0] = fTemp52;
		fRec59[0] = ((fConst46 * fRec59[1]) + (fConst45 * (fVec15[0] + fVec15[1])));
		fRec58[0] = (fRec59[0] - (fConst12 * ((fConst11 * fRec58[2]) + (fConst9 * fRec58[1]))));
		double fTemp53 = max((double)-1, min((double)1, (fSlow5 * (fRec58[2] + (fRec58[0] + (2 * fRec58[1]))))));
		double fTemp54 = (fConst9 * fRec66[1]);
		fRec68[0] = ((fConst43 * fRec68[1]) + (fConst42 * ((fConst16 * fVec14[0]) + (fConst49 * fVec14[1]))));
		fRec67[0] = (fRec68[0] - (fConst19 * ((fConst17 * fRec67[2]) + (fConst15 * fRec67[1]))));
		fRec66[0] = ((fConst19 * (((fConst14 * fRec67[0]) + (fConst50 * fRec67[1])) + (fConst14 * fRec67[2]))) - (fConst48 * ((fConst47 * fRec66[2]) + fTemp54)));
		double fTemp55 = max((double)-1, min((double)1, (fSlow6 * (fRec66[2] + (fConst48 * (fTemp54 + (fConst47 * fRec66[0])))))));
		double fTemp56 = (fConst9 * fRec69[1]);
		double fTemp57 = (fConst15 * fRec70[1]);
		fRec72[0] = ((fConst40 * fRec72[1]) + (fConst39 * ((fConst23 * fRec64[0]) + (fConst53 * fRec64[1]))));
		fRec71[0] = (fRec72[0] - (fConst26 * ((fConst24 * fRec71[2]) + (fConst22 * fRec71[1]))));
		fRec70[0] = ((fConst26 * (((fConst21 * fRec71[0]) + (fConst54 * fRec71[1])) + (fConst21 * fRec71[2]))) - (fConst52 * ((fConst51 * fRec70[2]) + fTemp57)));
		fRec69[0] = ((fRec70[2] + (fConst52 * (fTemp57 + (fConst51 * fRec70[0])))) - (fConst48 * ((fConst47 * fRec69[2]) + fTemp56)));
		double fTemp58 = max((double)-1, min((double)1, (fSlow7 * (fRec69[2] + (fConst48 * (fTemp56 + (fConst47 * fRec69[0])))))));
		fRec74[0] = ((fConst46 * fRec74[1]) + (fConst45 * ((fConst10 * fVec15[0]) + (fConst55 * fVec15[1]))));
		fRec73[0] = (fRec74[0] - (fConst12 * ((fConst11 * fRec73[2]) + (fConst9 * fRec73[1]))));
		double fTemp59 = max((double)-1, min((double)1, (fSlow8 * (((fConst8 * fRec73[0]) + (fConst56 * fRec73[1])) + (fConst8 * fRec73[2])))));
		double fTemp60 = ((1.584893192 * ((fTemp59 * (1 - (0.3333333333333333 * faustpower<2>(fTemp59)))) + ((fTemp58 * (1 - (0.3333333333333333 * faustpower<2>(fTemp58)))) + (0.8413951417869425 * (fTemp55 * (1 - (0.3333333333333333 * faustpower<2>(fTemp55)))))))) + (1.2589412 * (fTemp53 * (1 - (0.3333333333333333 * faustpower<2>(fTemp53))))));
		fVec16[0] = fTemp60;
		fRec57[0] = ((fConst60 * fRec57[1]) + (fConst59 * (fVec16[0] + fVec16[1])));
		fRec52[0] = (Ftube(TUBE_TABLE_6DJ8_68k, (((fTemp46 * (fTemp27 + (fTemp28 * (0.024937655860349125 + (fSlow12 * ((0.0997506234413965 - (0.0997506234413965 * fabs((0.024937655860349125 * (fTemp28 * fTemp46))))) - 0.024937655860349125)))))) + ((fSlow10 * fRec57[0]) + (fRec56[0] + (0.5 * (fTemp48 * (1 - (0.3333333333333333 * faustpower<2>(fTemp48)))))))) - 1.863945999999999)) - 60.96496296296296);
		fRec51[0] = ((fConst37 * fRec51[1]) + (fConst61 * ((fConst33 * fRec52[0]) + (fConst34 * fRec52[1]))));
		double fTemp61 = (1e-15 + (0.015 * fRec76[1]));
		fVec17[0] = fTemp61;
		fRec77[0] = ((fConst65 * fRec77[1]) + (fConst64 * (fVec17[0] + fVec17[1])));
		fRec76[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec77[0] + fRec50[1]) - 1.2716089999999989)) - 45.22606666666667);
		fRec75[0] = ((fConst37 * fRec75[1]) + (fConst61 * ((fConst33 * fRec76[0]) + (fConst34 * fRec76[1]))));
		fRec50[0] = ((0.6 * fRec75[0]) - fRec51[0]);
		double fTemp62 = (fRec8[0] * fRec50[0]);
		fVec18[0] = fTemp62;
		fRec49[0] = ((fConst60 * fRec49[1]) + (fConst59 * (fVec18[0] + fVec18[1])));
		double fTemp63 = (1e-15 + (0.015 * fRec48[1]));
		fVec19[0] = fTemp63;
		fRec78[0] = ((fConst65 * fRec78[1]) + (fConst64 * (fVec19[0] + fVec19[1])));
		fRec48[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec78[0] + fRec49[0]) - 1.2716089999999989)) - 45.22606666666667);
		fRec47[0] = ((fConst37 * fRec47[1]) + (fConst61 * ((fConst33 * fRec48[0]) + (fConst34 * fRec48[1]))));
		double fTemp64 = (1e-15 + (0.0082 * fRec80[1]));
		fVec20[0] = fTemp64;
		fRec81[0] = ((fConst69 * fRec81[1]) + (fConst68 * (fVec20[0] + fVec20[1])));
		fRec80[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec81[0] + fRec46[1]) - 0.797042999999999)) - 32.799634146341475);
		fRec79[0] = ((fConst37 * fRec79[1]) + (fConst61 * ((fConst33 * fRec80[0]) + (fConst34 * fRec80[1]))));
		fRec46[0] = ((0.6 * fRec79[0]) + fRec47[0]);
		fRec45[0] = ((fConst60 * fRec45[1]) + (fConst59 * (fRec46[0] + fRec46[1])));
		double fTemp65 = (1e-15 + (0.0082 * fRec44[1]));
		fVec21[0] = fTemp65;
		fRec82[0] = ((fConst69 * fRec82[1]) + (fConst68 * (fVec21[0] + fVec21[1])));
		fRec44[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec82[0] + fRec45[0]) - 0.797042999999999)) - 32.799634146341475);
		fRec43[0] = ((fConst37 * fRec43[1]) + (fConst61 * ((fConst33 * fRec44[0]) + (fConst34 * fRec44[1]))));
		output1[i] = (FAUSTFLOAT)(fRec0[0] * fRec43[0]);
		// post processing
		fRec43[1] = fRec43[0];
		fRec44[1] = fRec44[0];
		fRec82[1] = fRec82[0];
		fVec21[1] = fVec21[0];
		fRec45[1] = fRec45[0];
		fRec46[1] = fRec46[0];
		fRec79[1] = fRec79[0];
		fRec80[1] = fRec80[0];
		fRec81[1] = fRec81[0];
		fVec20[1] = fVec20[0];
		fRec47[1] = fRec47[0];
		fRec48[1] = fRec48[0];
		fRec78[1] = fRec78[0];
		fVec19[1] = fVec19[0];
		fRec49[1] = fRec49[0];
		fVec18[1] = fVec18[0];
		fRec50[1] = fRec50[0];
		fRec75[1] = fRec75[0];
		fRec76[1] = fRec76[0];
		fRec77[1] = fRec77[0];
		fVec17[1] = fVec17[0];
		fRec51[1] = fRec51[0];
		fRec52[1] = fRec52[0];
		fRec57[1] = fRec57[0];
		fVec16[1] = fVec16[0];
		fRec73[2] = fRec73[1]; fRec73[1] = fRec73[0];
		fRec74[1] = fRec74[0];
		fRec69[2] = fRec69[1]; fRec69[1] = fRec69[0];
		fRec70[2] = fRec70[1]; fRec70[1] = fRec70[0];
		fRec71[2] = fRec71[1]; fRec71[1] = fRec71[0];
		fRec72[1] = fRec72[0];
		fRec66[2] = fRec66[1]; fRec66[1] = fRec66[0];
		fRec67[2] = fRec67[1]; fRec67[1] = fRec67[0];
		fRec68[1] = fRec68[0];
		fRec58[2] = fRec58[1]; fRec58[1] = fRec58[0];
		fRec59[1] = fRec59[0];
		fVec15[1] = fVec15[0];
		fRec60[2] = fRec60[1]; fRec60[1] = fRec60[0];
		fRec61[1] = fRec61[0];
		fVec14[1] = fVec14[0];
		fRec62[2] = fRec62[1]; fRec62[1] = fRec62[0];
		fRec63[1] = fRec63[0];
		fRec64[1] = fRec64[0];
		fVec13[1] = fVec13[0];
		fRec65[2] = fRec65[1]; fRec65[1] = fRec65[0];
		fRec56[1] = fRec56[0];
		fVec12[1] = fVec12[0];
		fRec53[1] = fRec53[0];
		fRec54[1] = fRec54[0];
		fRec55[1] = fRec55[0];
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
		fRec17[1] = fRec17[0];
		fVec5[1] = fVec5[0];
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
		fVec4[1] = fVec4[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fVec3[1] = fVec3[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fVec2[1] = fVec2[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec16[1] = fRec16[0];
		fVec1[1] = fVec1[0];
		fRec15[1] = fRec15[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		IOTA = IOTA+1;
		fRec14[1] = fRec14[0];
		fRec8[1] = fRec8[0];
		fRec0[1] = fRec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
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

} // end namespace gxamp13_stereo
