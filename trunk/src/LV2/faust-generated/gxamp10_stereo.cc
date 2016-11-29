// generated from file '../src/LV2/faust/gxamp10_stereo.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp10_stereo {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
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
	double 	fVec5[2];
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fRec35[2];
	double 	fRec13[2];
	double 	fConst59;
	double 	fRec12[2];
	double 	fVec6[2];
	double 	fRec10[2];
	double 	fVec7[2];
	double 	fRec9[2];
	double 	fRec8[3];
	double 	fVec8[2];
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fRec36[2];
	double 	fRec7[2];
	double 	fRec6[2];
	double 	fVec9[2];
	double 	fRec5[2];
	double 	fVec10[2];
	double 	fRec4[2];
	double 	fRec3[3];
	double 	fVec11[2];
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fRec37[2];
	double 	fRec2[2];
	double 	fRec1[2];
	double 	fVec12[2];
	double 	fRec40[2];
	double 	fRec39[2];
	double 	fRec38[2];
	double 	fRec63[3];
	double 	fVec13[2];
	double 	fRec62[2];
	double 	fRec61[2];
	double 	fRec60[3];
	double 	fVec14[2];
	double 	fRec59[2];
	double 	fRec58[3];
	double 	fVec15[2];
	double 	fRec57[2];
	double 	fRec56[3];
	double 	fRec66[2];
	double 	fRec65[3];
	double 	fRec64[3];
	double 	fRec70[2];
	double 	fRec69[3];
	double 	fRec68[3];
	double 	fRec67[3];
	double 	fRec72[2];
	double 	fRec71[3];
	double 	fVec16[2];
	double 	fRec55[2];
	double 	fVec17[2];
	double 	fRec54[2];
	double 	fRec53[3];
	double 	fVec18[2];
	double 	fRec73[2];
	double 	fRec52[2];
	double 	fRec51[2];
	double 	fVec19[2];
	double 	fRec50[2];
	double 	fVec20[2];
	double 	fRec49[2];
	double 	fRec48[3];
	double 	fVec21[2];
	double 	fRec74[2];
	double 	fRec47[2];
	double 	fRec46[2];
	double 	fVec22[2];
	double 	fRec45[2];
	double 	fVec23[2];
	double 	fRec44[2];
	double 	fRec43[3];
	double 	fVec24[2];
	double 	fRec75[2];
	double 	fRec42[2];
	double 	fRec41[2];
	double 	fVec25[2];
	double 	fRec78[2];
	double 	fRec77[2];
	double 	fRec76[2];
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
	id = "6DJ8";
	name = N_("6DJ8");
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
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fVec12[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<3; i++) fRec63[i] = 0;
	for (int i=0; i<2; i++) fVec13[i] = 0;
	for (int i=0; i<2; i++) fRec62[i] = 0;
	for (int i=0; i<2; i++) fRec61[i] = 0;
	for (int i=0; i<3; i++) fRec60[i] = 0;
	for (int i=0; i<2; i++) fVec14[i] = 0;
	for (int i=0; i<2; i++) fRec59[i] = 0;
	for (int i=0; i<3; i++) fRec58[i] = 0;
	for (int i=0; i<2; i++) fVec15[i] = 0;
	for (int i=0; i<2; i++) fRec57[i] = 0;
	for (int i=0; i<3; i++) fRec56[i] = 0;
	for (int i=0; i<2; i++) fRec66[i] = 0;
	for (int i=0; i<3; i++) fRec65[i] = 0;
	for (int i=0; i<3; i++) fRec64[i] = 0;
	for (int i=0; i<2; i++) fRec70[i] = 0;
	for (int i=0; i<3; i++) fRec69[i] = 0;
	for (int i=0; i<3; i++) fRec68[i] = 0;
	for (int i=0; i<3; i++) fRec67[i] = 0;
	for (int i=0; i<2; i++) fRec72[i] = 0;
	for (int i=0; i<3; i++) fRec71[i] = 0;
	for (int i=0; i<2; i++) fVec16[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<2; i++) fVec17[i] = 0;
	for (int i=0; i<2; i++) fRec54[i] = 0;
	for (int i=0; i<3; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) fVec18[i] = 0;
	for (int i=0; i<2; i++) fRec73[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fVec19[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<2; i++) fVec20[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<3; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fVec21[i] = 0;
	for (int i=0; i<2; i++) fRec74[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fVec22[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fVec23[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<3; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) fVec24[i] = 0;
	for (int i=0; i<2; i++) fRec75[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fVec25[i] = 0;
	for (int i=0; i<2; i++) fRec78[i] = 0;
	for (int i=0; i<2; i++) fRec77[i] = 0;
	for (int i=0; i<2; i++) fRec76[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
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
	fConst57 = (1.0 / fConst56);
	fConst58 = (0 - ((1 - fConst55) / fConst56));
	fConst59 = (0.05 / fConst29);
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
	double 	fSlow4 = (2 * (fSlow3 - 0.5));
	double 	fSlow5 = (1 - max((double)0, fSlow4));
	double 	fSlow6 = (1.25 * fSlow3);
	double 	fSlow7 = (fConst6 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow8 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow9 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow10 = (fConst6 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow11 = (1 - max((double)0, (0 - fSlow4)));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.999 * fRec0[1]) + fSlow0);
		fRec11[0] = ((0.999 * fRec11[1]) + fSlow1);
		fRec16[0] = (fSlow2 + (0.999 * fRec16[1]));
		double fTemp0 = (double)input0[i];
		double fTemp1 = (1e-15 + (fTemp0 * fRec16[0]));
		double fTemp2 = (1 - fRec16[0]);
		double fTemp3 = (fTemp0 * fTemp2);
		double fTemp4 = (1e-15 + fTemp3);
		fRec25[0] = (fTemp1 - (fConst26 * ((fConst24 * fRec25[2]) + (fConst22 * fRec25[1]))));
		double fTemp5 = (fRec25[2] + (fRec25[0] + (2 * fRec25[1])));
		fVec0[0] = fTemp5;
		fRec24[0] = ((fConst31 * fRec24[1]) + (fConst30 * ((fConst27 * fVec0[0]) + (fConst28 * fVec0[1]))));
		fRec23[0] = ((fConst34 * fRec23[1]) + (fConst33 * (fRec24[0] + fRec24[1])));
		fRec22[0] = (fRec23[0] - (fConst20 * ((fConst18 * fRec22[2]) + (fConst16 * fRec22[1]))));
		double fTemp6 = (fRec22[2] + (fRec22[0] + (2 * fRec22[1])));
		fVec1[0] = fTemp6;
		fRec21[0] = ((fConst37 * fRec21[1]) + (fConst36 * (fVec1[0] + fVec1[1])));
		fRec20[0] = (fRec21[0] - (fConst13 * ((fConst11 * fRec20[2]) + (fConst9 * fRec20[1]))));
		double fTemp7 = (fRec20[2] + (fRec20[0] + (2 * fRec20[1])));
		fVec2[0] = fTemp7;
		fRec19[0] = ((fConst40 * fRec19[1]) + (fConst39 * (fVec2[0] + fVec2[1])));
		fRec18[0] = (fRec19[0] - (fConst6 * ((fConst5 * fRec18[2]) + (fConst3 * fRec18[1]))));
		double fTemp8 = max((double)-1, min((double)1, (fSlow7 * (fRec18[2] + (fRec18[0] + (2 * fRec18[1]))))));
		double fTemp9 = (fConst3 * fRec26[1]);
		fRec28[0] = ((fConst37 * fRec28[1]) + (fConst36 * ((fConst10 * fVec1[0]) + (fConst43 * fVec1[1]))));
		fRec27[0] = (fRec28[0] - (fConst13 * ((fConst11 * fRec27[2]) + (fConst9 * fRec27[1]))));
		fRec26[0] = ((fConst13 * (((fConst8 * fRec27[0]) + (fConst44 * fRec27[1])) + (fConst8 * fRec27[2]))) - (fConst42 * ((fConst41 * fRec26[2]) + fTemp9)));
		double fTemp10 = max((double)-1, min((double)1, (fSlow8 * (fRec26[2] + (fConst42 * (fTemp9 + (fConst41 * fRec26[0])))))));
		double fTemp11 = (fConst3 * fRec29[1]);
		double fTemp12 = (fConst9 * fRec30[1]);
		fRec32[0] = ((fConst34 * fRec32[1]) + (fConst33 * ((fConst17 * fRec24[0]) + (fConst47 * fRec24[1]))));
		fRec31[0] = (fRec32[0] - (fConst20 * ((fConst18 * fRec31[2]) + (fConst16 * fRec31[1]))));
		fRec30[0] = ((fConst20 * (((fConst15 * fRec31[0]) + (fConst48 * fRec31[1])) + (fConst15 * fRec31[2]))) - (fConst46 * ((fConst45 * fRec30[2]) + fTemp12)));
		fRec29[0] = ((fRec30[2] + (fConst46 * (fTemp12 + (fConst45 * fRec30[0])))) - (fConst42 * ((fConst41 * fRec29[2]) + fTemp11)));
		double fTemp13 = max((double)-1, min((double)1, (fSlow9 * (fRec29[2] + (fConst42 * (fTemp11 + (fConst41 * fRec29[0])))))));
		fRec34[0] = ((fConst40 * fRec34[1]) + (fConst39 * ((fConst4 * fVec2[0]) + (fConst49 * fVec2[1]))));
		fRec33[0] = (fRec34[0] - (fConst6 * ((fConst5 * fRec33[2]) + (fConst3 * fRec33[1]))));
		double fTemp14 = max((double)-1, min((double)1, (fSlow10 * (((fConst2 * fRec33[0]) + (fConst50 * fRec33[1])) + (fConst2 * fRec33[2])))));
		double fTemp15 = ((1.584893192 * ((fTemp14 * (1 - (0.3333333333333333 * faustpower<2>(fTemp14)))) + ((fTemp13 * (1 - (0.3333333333333333 * faustpower<2>(fTemp13)))) + (0.8413951417869425 * (fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10)))))))) + (1.2589412 * (fTemp8 * (1 - (0.3333333333333333 * faustpower<2>(fTemp8))))));
		fVec3[0] = fTemp15;
		fRec17[0] = ((fConst54 * fRec17[1]) + (fConst53 * (fVec3[0] + fVec3[1])));
		double fTemp16 = (((fSlow11 * fRec17[0]) + ((fTemp3 + (fSlow6 * ((fTemp4 * (4 - (4 * fabs(fTemp4)))) - fTemp4))) + (fSlow5 * fTemp1))) + 2e-15);
		fVec4[0] = fTemp16;
		fRec15[0] = ((0.9302847925323914 * (fVec4[0] + fVec4[1])) - (0.8605695850647829 * fRec15[1]));
		fRec14[0] = (fRec15[0] - ((1.8405051250752198 * fRec14[1]) + (0.8612942439318627 * fRec14[2])));
		double fTemp17 = (1e-15 + (0.027 * fRec13[1]));
		fVec5[0] = fTemp17;
		fRec35[0] = ((fConst58 * fRec35[1]) + (fConst57 * (fVec5[0] + fVec5[1])));
		fRec13[0] = (Ftube(TUBE_TABLE_6DJ8_68k, ((fRec35[0] + (0.9254498422517706 * (fRec14[2] + (fRec14[0] + (2.0 * fRec14[1]))))) - 1.863946)) - 60.96496296296296);
		fRec12[0] = ((fConst31 * fRec12[1]) + (fConst59 * ((fConst27 * fRec13[0]) + (fConst28 * fRec13[1]))));
		double fTemp18 = (fRec12[0] * fRec11[0]);
		fVec6[0] = fTemp18;
		fRec10[0] = ((fConst54 * fRec10[1]) + (fConst53 * (fVec6[0] + fVec6[1])));
		double fTemp19 = (1e-15 + fRec10[0]);
		fVec7[0] = fTemp19;
		fRec9[0] = ((0.9302847925323914 * (fVec7[0] + fVec7[1])) - (0.8605695850647829 * fRec9[1]));
		fRec8[0] = (fRec9[0] - ((1.8405051250752198 * fRec8[1]) + (0.8612942439318627 * fRec8[2])));
		double fTemp20 = (1e-15 + (0.015 * fRec7[1]));
		fVec8[0] = fTemp20;
		fRec36[0] = ((fConst63 * fRec36[1]) + (fConst62 * (fVec8[0] + fVec8[1])));
		fRec7[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec36[0] + (0.9254498422517706 * (fRec8[2] + (fRec8[0] + (2.0 * fRec8[1]))))) - 1.271609)) - 45.22606666666667);
		fRec6[0] = ((fConst31 * fRec6[1]) + (fConst59 * ((fConst27 * fRec7[0]) + (fConst28 * fRec7[1]))));
		double fTemp21 = (fRec11[0] * fRec6[0]);
		fVec9[0] = fTemp21;
		fRec5[0] = ((fConst54 * fRec5[1]) + (fConst53 * (fVec9[0] + fVec9[1])));
		double fTemp22 = (1e-15 + fRec5[0]);
		fVec10[0] = fTemp22;
		fRec4[0] = ((0.9302847925323914 * (fVec10[0] + fVec10[1])) - (0.8605695850647829 * fRec4[1]));
		fRec3[0] = (fRec4[0] - ((1.8405051250752198 * fRec3[1]) + (0.8612942439318627 * fRec3[2])));
		double fTemp23 = (0.9254498422517706 * (fRec3[2] + (fRec3[0] + (2.0 * fRec3[1]))));
		double fTemp24 = (1e-15 + (0.0082 * fRec2[1]));
		fVec11[0] = fTemp24;
		fRec37[0] = ((fConst67 * fRec37[1]) + (fConst66 * (fVec11[0] + fVec11[1])));
		fRec2[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec37[0] + fTemp23) - 0.797043)) - 32.799634146341475);
		fRec1[0] = ((fConst31 * fRec1[1]) + (fConst59 * ((fConst27 * fRec2[0]) + (fConst28 * fRec2[1]))));
		double fTemp25 = (1e-15 + (0.0082 * fRec39[1]));
		fVec12[0] = fTemp25;
		fRec40[0] = ((fConst67 * fRec40[1]) + (fConst66 * (fVec12[0] + fVec12[1])));
		fRec39[0] = (Ftube(TUBE_TABLE_6DJ8_68k, ((fRec40[0] + fTemp23) - 0.799031)) - 32.55719512195121);
		fRec38[0] = ((fConst31 * fRec38[1]) + (fConst59 * ((fConst27 * fRec39[0]) + (fConst28 * fRec39[1]))));
		output0[i] = (FAUSTFLOAT)((fRec38[0] + fRec1[0]) * fRec0[0]);
		double fTemp26 = (double)input1[i];
		double fTemp27 = (1e-15 + (fTemp26 * fRec16[0]));
		double fTemp28 = (fTemp26 * fTemp2);
		double fTemp29 = (1e-15 + fTemp28);
		fRec63[0] = (fTemp27 - (fConst26 * ((fConst24 * fRec63[2]) + (fConst22 * fRec63[1]))));
		double fTemp30 = (fRec63[2] + (fRec63[0] + (2 * fRec63[1])));
		fVec13[0] = fTemp30;
		fRec62[0] = ((fConst31 * fRec62[1]) + (fConst30 * ((fConst27 * fVec13[0]) + (fConst28 * fVec13[1]))));
		fRec61[0] = ((fConst34 * fRec61[1]) + (fConst33 * (fRec62[0] + fRec62[1])));
		fRec60[0] = (fRec61[0] - (fConst20 * ((fConst18 * fRec60[2]) + (fConst16 * fRec60[1]))));
		double fTemp31 = (fRec60[2] + (fRec60[0] + (2 * fRec60[1])));
		fVec14[0] = fTemp31;
		fRec59[0] = ((fConst37 * fRec59[1]) + (fConst36 * (fVec14[0] + fVec14[1])));
		fRec58[0] = (fRec59[0] - (fConst13 * ((fConst11 * fRec58[2]) + (fConst9 * fRec58[1]))));
		double fTemp32 = (fRec58[2] + (fRec58[0] + (2 * fRec58[1])));
		fVec15[0] = fTemp32;
		fRec57[0] = ((fConst40 * fRec57[1]) + (fConst39 * (fVec15[0] + fVec15[1])));
		fRec56[0] = (fRec57[0] - (fConst6 * ((fConst5 * fRec56[2]) + (fConst3 * fRec56[1]))));
		double fTemp33 = max((double)-1, min((double)1, (fSlow7 * (fRec56[2] + (fRec56[0] + (2 * fRec56[1]))))));
		double fTemp34 = (fConst3 * fRec64[1]);
		fRec66[0] = ((fConst37 * fRec66[1]) + (fConst36 * ((fConst10 * fVec14[0]) + (fConst43 * fVec14[1]))));
		fRec65[0] = (fRec66[0] - (fConst13 * ((fConst11 * fRec65[2]) + (fConst9 * fRec65[1]))));
		fRec64[0] = ((fConst13 * (((fConst8 * fRec65[0]) + (fConst44 * fRec65[1])) + (fConst8 * fRec65[2]))) - (fConst42 * ((fConst41 * fRec64[2]) + fTemp34)));
		double fTemp35 = max((double)-1, min((double)1, (fSlow8 * (fRec64[2] + (fConst42 * (fTemp34 + (fConst41 * fRec64[0])))))));
		double fTemp36 = (fConst3 * fRec67[1]);
		double fTemp37 = (fConst9 * fRec68[1]);
		fRec70[0] = ((fConst34 * fRec70[1]) + (fConst33 * ((fConst17 * fRec62[0]) + (fConst47 * fRec62[1]))));
		fRec69[0] = (fRec70[0] - (fConst20 * ((fConst18 * fRec69[2]) + (fConst16 * fRec69[1]))));
		fRec68[0] = ((fConst20 * (((fConst15 * fRec69[0]) + (fConst48 * fRec69[1])) + (fConst15 * fRec69[2]))) - (fConst46 * ((fConst45 * fRec68[2]) + fTemp37)));
		fRec67[0] = ((fRec68[2] + (fConst46 * (fTemp37 + (fConst45 * fRec68[0])))) - (fConst42 * ((fConst41 * fRec67[2]) + fTemp36)));
		double fTemp38 = max((double)-1, min((double)1, (fSlow9 * (fRec67[2] + (fConst42 * (fTemp36 + (fConst41 * fRec67[0])))))));
		fRec72[0] = ((fConst40 * fRec72[1]) + (fConst39 * ((fConst4 * fVec15[0]) + (fConst49 * fVec15[1]))));
		fRec71[0] = (fRec72[0] - (fConst6 * ((fConst5 * fRec71[2]) + (fConst3 * fRec71[1]))));
		double fTemp39 = max((double)-1, min((double)1, (fSlow10 * (((fConst2 * fRec71[0]) + (fConst50 * fRec71[1])) + (fConst2 * fRec71[2])))));
		double fTemp40 = ((1.584893192 * ((fTemp39 * (1 - (0.3333333333333333 * faustpower<2>(fTemp39)))) + ((fTemp38 * (1 - (0.3333333333333333 * faustpower<2>(fTemp38)))) + (0.8413951417869425 * (fTemp35 * (1 - (0.3333333333333333 * faustpower<2>(fTemp35)))))))) + (1.2589412 * (fTemp33 * (1 - (0.3333333333333333 * faustpower<2>(fTemp33))))));
		fVec16[0] = fTemp40;
		fRec55[0] = ((fConst54 * fRec55[1]) + (fConst53 * (fVec16[0] + fVec16[1])));
		double fTemp41 = (2e-15 + ((fSlow11 * fRec55[0]) + ((fTemp28 + (fSlow6 * ((fTemp29 * (4 - (4 * fabs(fTemp29)))) - fTemp29))) + (fSlow5 * fTemp27))));
		fVec17[0] = fTemp41;
		fRec54[0] = ((0.9302847925323914 * (fVec17[0] + fVec17[1])) - (0.8605695850647829 * fRec54[1]));
		fRec53[0] = (fRec54[0] - ((1.8405051250752198 * fRec53[1]) + (0.8612942439318627 * fRec53[2])));
		double fTemp42 = (1e-15 + (0.027 * fRec52[1]));
		fVec18[0] = fTemp42;
		fRec73[0] = ((fConst58 * fRec73[1]) + (fConst57 * (fVec18[0] + fVec18[1])));
		fRec52[0] = (Ftube(TUBE_TABLE_6DJ8_68k, ((fRec73[0] + (0.9254498422517706 * (fRec53[2] + (fRec53[0] + (2.0 * fRec53[1]))))) - 1.863946)) - 60.96496296296296);
		fRec51[0] = ((fConst31 * fRec51[1]) + (fConst59 * ((fConst27 * fRec52[0]) + (fConst28 * fRec52[1]))));
		double fTemp43 = (fRec11[0] * fRec51[0]);
		fVec19[0] = fTemp43;
		fRec50[0] = ((fConst54 * fRec50[1]) + (fConst53 * (fVec19[0] + fVec19[1])));
		double fTemp44 = (1e-15 + fRec50[0]);
		fVec20[0] = fTemp44;
		fRec49[0] = ((0.9302847925323914 * (fVec20[0] + fVec20[1])) - (0.8605695850647829 * fRec49[1]));
		fRec48[0] = (fRec49[0] - ((1.8405051250752198 * fRec48[1]) + (0.8612942439318627 * fRec48[2])));
		double fTemp45 = (1e-15 + (0.015 * fRec47[1]));
		fVec21[0] = fTemp45;
		fRec74[0] = ((fConst63 * fRec74[1]) + (fConst62 * (fVec21[0] + fVec21[1])));
		fRec47[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec74[0] + (0.9254498422517706 * (fRec48[2] + (fRec48[0] + (2.0 * fRec48[1]))))) - 1.271609)) - 45.22606666666667);
		fRec46[0] = ((fConst31 * fRec46[1]) + (fConst59 * ((fConst27 * fRec47[0]) + (fConst28 * fRec47[1]))));
		double fTemp46 = (fRec11[0] * fRec46[0]);
		fVec22[0] = fTemp46;
		fRec45[0] = ((fConst54 * fRec45[1]) + (fConst53 * (fVec22[0] + fVec22[1])));
		double fTemp47 = (1e-15 + fRec45[0]);
		fVec23[0] = fTemp47;
		fRec44[0] = ((0.9302847925323914 * (fVec23[0] + fVec23[1])) - (0.8605695850647829 * fRec44[1]));
		fRec43[0] = (fRec44[0] - ((1.8405051250752198 * fRec43[1]) + (0.8612942439318627 * fRec43[2])));
		double fTemp48 = (0.9254498422517706 * (fRec43[2] + (fRec43[0] + (2.0 * fRec43[1]))));
		double fTemp49 = (1e-15 + (0.0082 * fRec42[1]));
		fVec24[0] = fTemp49;
		fRec75[0] = ((fConst67 * fRec75[1]) + (fConst66 * (fVec24[0] + fVec24[1])));
		fRec42[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec75[0] + fTemp48) - 0.797043)) - 32.799634146341475);
		fRec41[0] = ((fConst31 * fRec41[1]) + (fConst59 * ((fConst27 * fRec42[0]) + (fConst28 * fRec42[1]))));
		double fTemp50 = (1e-15 + (0.0082 * fRec77[1]));
		fVec25[0] = fTemp50;
		fRec78[0] = ((fConst67 * fRec78[1]) + (fConst66 * (fVec25[0] + fVec25[1])));
		fRec77[0] = (Ftube(TUBE_TABLE_6DJ8_68k, ((fRec78[0] + fTemp48) - 0.799031)) - 32.55719512195121);
		fRec76[0] = ((fConst31 * fRec76[1]) + (fConst59 * ((fConst27 * fRec77[0]) + (fConst28 * fRec77[1]))));
		output1[i] = (FAUSTFLOAT)(fRec0[0] * (fRec76[0] + fRec41[0]));
		// post processing
		fRec76[1] = fRec76[0];
		fRec77[1] = fRec77[0];
		fRec78[1] = fRec78[0];
		fVec25[1] = fVec25[0];
		fRec41[1] = fRec41[0];
		fRec42[1] = fRec42[0];
		fRec75[1] = fRec75[0];
		fVec24[1] = fVec24[0];
		fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
		fRec44[1] = fRec44[0];
		fVec23[1] = fVec23[0];
		fRec45[1] = fRec45[0];
		fVec22[1] = fVec22[0];
		fRec46[1] = fRec46[0];
		fRec47[1] = fRec47[0];
		fRec74[1] = fRec74[0];
		fVec21[1] = fVec21[0];
		fRec48[2] = fRec48[1]; fRec48[1] = fRec48[0];
		fRec49[1] = fRec49[0];
		fVec20[1] = fVec20[0];
		fRec50[1] = fRec50[0];
		fVec19[1] = fVec19[0];
		fRec51[1] = fRec51[0];
		fRec52[1] = fRec52[0];
		fRec73[1] = fRec73[0];
		fVec18[1] = fVec18[0];
		fRec53[2] = fRec53[1]; fRec53[1] = fRec53[0];
		fRec54[1] = fRec54[0];
		fVec17[1] = fVec17[0];
		fRec55[1] = fRec55[0];
		fVec16[1] = fVec16[0];
		fRec71[2] = fRec71[1]; fRec71[1] = fRec71[0];
		fRec72[1] = fRec72[0];
		fRec67[2] = fRec67[1]; fRec67[1] = fRec67[0];
		fRec68[2] = fRec68[1]; fRec68[1] = fRec68[0];
		fRec69[2] = fRec69[1]; fRec69[1] = fRec69[0];
		fRec70[1] = fRec70[0];
		fRec64[2] = fRec64[1]; fRec64[1] = fRec64[0];
		fRec65[2] = fRec65[1]; fRec65[1] = fRec65[0];
		fRec66[1] = fRec66[0];
		fRec56[2] = fRec56[1]; fRec56[1] = fRec56[0];
		fRec57[1] = fRec57[0];
		fVec15[1] = fVec15[0];
		fRec58[2] = fRec58[1]; fRec58[1] = fRec58[0];
		fRec59[1] = fRec59[0];
		fVec14[1] = fVec14[0];
		fRec60[2] = fRec60[1]; fRec60[1] = fRec60[0];
		fRec61[1] = fRec61[0];
		fRec62[1] = fRec62[0];
		fVec13[1] = fVec13[0];
		fRec63[2] = fRec63[1]; fRec63[1] = fRec63[0];
		fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec40[1] = fRec40[0];
		fVec12[1] = fVec12[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec37[1] = fRec37[0];
		fVec11[1] = fVec11[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fVec10[1] = fVec10[0];
		fRec5[1] = fRec5[0];
		fVec9[1] = fVec9[0];
		fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec36[1] = fRec36[0];
		fVec8[1] = fVec8[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fVec7[1] = fVec7[0];
		fRec10[1] = fRec10[0];
		fVec6[1] = fVec6[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec35[1] = fRec35[0];
		fVec5[1] = fVec5[0];
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

} // end namespace gxamp10_stereo
