// generated from file '../src/LV2/faust/gxamp10_stereo.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp10_stereo {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	double 	fVec0[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec8[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec11[2];
	double 	fVec1[2];
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fRec12[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
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
	double 	fRec21[3];
	double 	fVec2[2];
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fRec20[2];
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fRec19[2];
	double 	fRec18[3];
	double 	fVec3[2];
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fRec17[2];
	double 	fRec16[3];
	double 	fVec4[2];
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fRec15[2];
	double 	fRec14[3];
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fRec24[2];
	double 	fRec23[3];
	double 	fConst52;
	double 	fRec22[3];
	double 	fConst53;
	double 	fConst54;
	double 	fConst55;
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fConst56;
	double 	fRec26[3];
	double 	fRec25[3];
	double 	fConst57;
	double 	fRec30[2];
	double 	fRec29[3];
	double 	fConst58;
	double 	fVec5[2];
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fRec13[2];
	double 	fRec10[2];
	double 	fConst63;
	double 	fRec9[2];
	double 	fVec6[2];
	double 	fRec7[2];
	double 	fVec7[2];
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
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
	double 	fVec10[2];
	double 	fRec37[2];
	double 	fVec11[2];
	double 	fRec44[2];
	double 	fRec53[3];
	double 	fVec12[2];
	double 	fRec52[2];
	double 	fRec51[2];
	double 	fRec50[3];
	double 	fVec13[2];
	double 	fRec49[2];
	double 	fRec48[3];
	double 	fVec14[2];
	double 	fRec47[2];
	double 	fRec46[3];
	double 	fRec56[2];
	double 	fRec55[3];
	double 	fRec54[3];
	double 	fRec60[2];
	double 	fRec59[3];
	double 	fRec58[3];
	double 	fRec57[3];
	double 	fRec62[2];
	double 	fRec61[3];
	double 	fVec15[2];
	double 	fRec45[2];
	double 	fRec43[2];
	double 	fRec42[2];
	double 	fVec16[2];
	double 	fRec41[2];
	double 	fVec17[2];
	double 	fRec63[2];
	double 	fRec40[2];
	double 	fRec39[2];
	double 	fVec18[2];
	double 	fRec38[2];
	double 	fRec36[2];
	double 	fRec35[2];
	double 	fVec19[2];
	double 	fRec66[2];
	double 	fRec65[2];
	double 	fRec64[2];
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
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
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
	for (int i=0; i<2; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<3; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) fVec12[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<3; i++) fRec50[i] = 0;
	for (int i=0; i<2; i++) fVec13[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<3; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fVec14[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<3; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec56[i] = 0;
	for (int i=0; i<3; i++) fRec55[i] = 0;
	for (int i=0; i<3; i++) fRec54[i] = 0;
	for (int i=0; i<2; i++) fRec60[i] = 0;
	for (int i=0; i<3; i++) fRec59[i] = 0;
	for (int i=0; i<3; i++) fRec58[i] = 0;
	for (int i=0; i<3; i++) fRec57[i] = 0;
	for (int i=0; i<2; i++) fRec62[i] = 0;
	for (int i=0; i<3; i++) fRec61[i] = 0;
	for (int i=0; i<2; i++) fVec15[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fVec16[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fVec17[i] = 0;
	for (int i=0; i<2; i++) fRec63[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fVec18[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fVec19[i] = 0;
	for (int i=0; i<2; i++) fRec66[i] = 0;
	for (int i=0; i<2; i++) fRec65[i] = 0;
	for (int i=0; i<2; i++) fRec64[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst2 = (1 + fConst1);
	fConst3 = (1.0 / fConst2);
	fConst4 = (0 - ((1 - fConst1) / fConst2));
	fConst5 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst6 = (1 + fConst5);
	fConst7 = (1.0 / fConst6);
	fConst8 = (0 - ((1 - fConst5) / fConst6));
	fConst9 = tan((942.4777960769379 / double(iConst0)));
	fConst10 = (1.0 / faustpower<2>(fConst9));
	fConst11 = (2 * (1 - fConst10));
	fConst12 = (1.0 / fConst9);
	fConst13 = (1 + ((fConst12 - 1.0000000000000004) / fConst9));
	fConst14 = (1.0 / (1 + ((fConst12 + 1.0000000000000004) / fConst9)));
	fConst15 = tan((3769.9111843077517 / double(iConst0)));
	fConst16 = (1.0 / faustpower<2>(fConst15));
	fConst17 = (2 * (1 - fConst16));
	fConst18 = (1.0 / fConst15);
	fConst19 = (1 + ((fConst18 - 1.0000000000000004) / fConst15));
	fConst20 = (1 + ((fConst18 + 1.0000000000000004) / fConst15));
	fConst21 = (1.0 / fConst20);
	fConst22 = tan((10053.096491487338 / double(iConst0)));
	fConst23 = (1.0 / faustpower<2>(fConst22));
	fConst24 = (2 * (1 - fConst23));
	fConst25 = (1.0 / fConst22);
	fConst26 = (1 + ((fConst25 - 1.0000000000000004) / fConst22));
	fConst27 = (1 + ((1.0000000000000004 + fConst25) / fConst22));
	fConst28 = (1.0 / fConst27);
	fConst29 = tan((47123.8898038469 / double(iConst0)));
	fConst30 = (2 * (1 - (1.0 / faustpower<2>(fConst29))));
	fConst31 = (1.0 / fConst29);
	fConst32 = (1 + ((fConst31 - 1.414213562373095) / fConst29));
	fConst33 = (1 + ((1.414213562373095 + fConst31) / fConst29));
	fConst34 = (1.0 / fConst33);
	fConst35 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst36 = (0 - fConst35);
	fConst37 = (1 + fConst35);
	fConst38 = (1.0 / (fConst37 * fConst33));
	fConst39 = (0 - ((1 - fConst35) / fConst37));
	fConst40 = (1 + fConst25);
	fConst41 = (1.0 / fConst40);
	fConst42 = (0 - ((1 - fConst25) / fConst40));
	fConst43 = (1 + fConst18);
	fConst44 = (1.0 / (fConst43 * fConst27));
	fConst45 = (0 - ((1 - fConst18) / fConst43));
	fConst46 = (1 + fConst12);
	fConst47 = (1.0 / (fConst46 * fConst20));
	fConst48 = (0 - ((1 - fConst12) / fConst46));
	fConst49 = (1 + ((fConst12 - 1.0) / fConst9));
	fConst50 = (1.0 / (1 + ((1.0 + fConst12) / fConst9)));
	fConst51 = (0 - fConst18);
	fConst52 = (2 * (0 - fConst16));
	fConst53 = (1 + ((fConst18 - 1.0) / fConst15));
	fConst54 = (1.0 / (1 + ((1.0 + fConst18) / fConst15)));
	fConst55 = (0 - fConst25);
	fConst56 = (2 * (0 - fConst23));
	fConst57 = (0 - fConst12);
	fConst58 = (2 * (0 - fConst10));
	fConst59 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst60 = (1 + fConst59);
	fConst61 = (1.0 / fConst60);
	fConst62 = (0 - ((1 - fConst59) / fConst60));
	fConst63 = (0.05 / fConst37);
	fConst64 = (1.0 / tan((414.6902302738527 / double(iConst0))));
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
	double 	fSlow4 = (1.25 * fSlow3);
	double 	fSlow5 = (2 * (fSlow3 - 0.5));
	double 	fSlow6 = (1 - max((double)0, fSlow5));
	double 	fSlow7 = (fConst14 * pow(1e+01,(0.9 * fSlow3)));
	double 	fSlow8 = pow(1e+01,(1.2 * fSlow3));
	double 	fSlow9 = pow(1e+01,(0.8 * fSlow3));
	double 	fSlow10 = (fConst14 * pow(1e+01,(2 * fSlow3)));
	double 	fSlow11 = (1 - max((double)0, (0 - fSlow5)));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.999 * fRec0[1]) + fSlow0);
		double fTemp0 = (1e-15 + (0.0082 * fRec2[1]));
		fVec0[0] = fTemp0;
		fRec3[0] = ((fConst4 * fRec3[1]) + (fConst3 * (fVec0[0] + fVec0[1])));
		fRec8[0] = ((0.999 * fRec8[1]) + fSlow1);
		fRec11[0] = (fSlow2 + (0.999 * fRec11[1]));
		double fTemp1 = (1 - fRec11[0]);
		double fTemp2 = (double)input0[i];
		double fTemp3 = (fTemp2 * fTemp1);
		double fTemp4 = (1e-15 + (0.027 * fRec10[1]));
		fVec1[0] = fTemp4;
		fRec12[0] = ((fConst8 * fRec12[1]) + (fConst7 * (fVec1[0] + fVec1[1])));
		double fTemp5 = (1e-15 + fTemp3);
		double fTemp6 = (1e-15 + (fTemp2 * fRec11[0]));
		fRec21[0] = (fTemp6 - (fConst34 * ((fConst32 * fRec21[2]) + (fConst30 * fRec21[1]))));
		double fTemp7 = (fRec21[2] + (fRec21[0] + (2 * fRec21[1])));
		fVec2[0] = fTemp7;
		fRec20[0] = ((fConst39 * fRec20[1]) + (fConst38 * ((fConst35 * fVec2[0]) + (fConst36 * fVec2[1]))));
		fRec19[0] = ((fConst42 * fRec19[1]) + (fConst41 * (fRec20[0] + fRec20[1])));
		fRec18[0] = (fRec19[0] - (fConst28 * ((fConst26 * fRec18[2]) + (fConst24 * fRec18[1]))));
		double fTemp8 = (fRec18[2] + (fRec18[0] + (2 * fRec18[1])));
		fVec3[0] = fTemp8;
		fRec17[0] = ((fConst45 * fRec17[1]) + (fConst44 * (fVec3[0] + fVec3[1])));
		fRec16[0] = (fRec17[0] - (fConst21 * ((fConst19 * fRec16[2]) + (fConst17 * fRec16[1]))));
		double fTemp9 = (fRec16[2] + (fRec16[0] + (2 * fRec16[1])));
		fVec4[0] = fTemp9;
		fRec15[0] = ((fConst48 * fRec15[1]) + (fConst47 * (fVec4[0] + fVec4[1])));
		fRec14[0] = (fRec15[0] - (fConst14 * ((fConst13 * fRec14[2]) + (fConst11 * fRec14[1]))));
		double fTemp10 = max((double)-1, min((double)1, (fSlow7 * (fRec14[2] + (fRec14[0] + (2 * fRec14[1]))))));
		double fTemp11 = (fConst11 * fRec22[1]);
		fRec24[0] = ((fConst45 * fRec24[1]) + (fConst44 * ((fConst18 * fVec3[0]) + (fConst51 * fVec3[1]))));
		fRec23[0] = (fRec24[0] - (fConst21 * ((fConst19 * fRec23[2]) + (fConst17 * fRec23[1]))));
		fRec22[0] = ((fConst21 * (((fConst16 * fRec23[0]) + (fConst52 * fRec23[1])) + (fConst16 * fRec23[2]))) - (fConst50 * ((fConst49 * fRec22[2]) + fTemp11)));
		double fTemp12 = max((double)-1, min((double)1, (fSlow8 * (fRec22[2] + (fConst50 * (fTemp11 + (fConst49 * fRec22[0])))))));
		double fTemp13 = (fConst11 * fRec25[1]);
		double fTemp14 = (fConst17 * fRec26[1]);
		fRec28[0] = ((fConst42 * fRec28[1]) + (fConst41 * ((fConst25 * fRec20[0]) + (fConst55 * fRec20[1]))));
		fRec27[0] = (fRec28[0] - (fConst28 * ((fConst26 * fRec27[2]) + (fConst24 * fRec27[1]))));
		fRec26[0] = ((fConst28 * (((fConst23 * fRec27[0]) + (fConst56 * fRec27[1])) + (fConst23 * fRec27[2]))) - (fConst54 * ((fConst53 * fRec26[2]) + fTemp14)));
		fRec25[0] = ((fRec26[2] + (fConst54 * (fTemp14 + (fConst53 * fRec26[0])))) - (fConst50 * ((fConst49 * fRec25[2]) + fTemp13)));
		double fTemp15 = max((double)-1, min((double)1, (fSlow9 * (fRec25[2] + (fConst50 * (fTemp13 + (fConst49 * fRec25[0])))))));
		fRec30[0] = ((fConst48 * fRec30[1]) + (fConst47 * ((fConst12 * fVec4[0]) + (fConst57 * fVec4[1]))));
		fRec29[0] = (fRec30[0] - (fConst14 * ((fConst13 * fRec29[2]) + (fConst11 * fRec29[1]))));
		double fTemp16 = max((double)-1, min((double)1, (fSlow10 * (((fConst10 * fRec29[0]) + (fConst58 * fRec29[1])) + (fConst10 * fRec29[2])))));
		double fTemp17 = ((1.584893192 * ((fTemp16 * (1 - (0.3333333333333333 * faustpower<2>(fTemp16)))) + ((fTemp15 * (1 - (0.3333333333333333 * faustpower<2>(fTemp15)))) + (0.8413951417869425 * (fTemp12 * (1 - (0.3333333333333333 * faustpower<2>(fTemp12)))))))) + (1.2589412 * (fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10))))));
		fVec5[0] = fTemp17;
		fRec13[0] = ((fConst62 * fRec13[1]) + (fConst61 * (fVec5[0] + fVec5[1])));
		fRec10[0] = (Ftube(TUBE_TABLE_6DJ8_68k, (((fSlow11 * fRec13[0]) + ((fSlow6 * fTemp6) + ((fSlow4 * ((fTemp5 * (4 - (4 * fabs(fTemp5)))) - fTemp5)) + (fRec12[0] + fTemp3)))) - 1.863945999999998)) - 60.96496296296296);
		fRec9[0] = ((fConst39 * fRec9[1]) + (fConst63 * ((fConst35 * fRec10[0]) + (fConst36 * fRec10[1]))));
		double fTemp18 = (fRec9[0] * fRec8[0]);
		fVec6[0] = fTemp18;
		fRec7[0] = ((fConst62 * fRec7[1]) + (fConst61 * (fVec6[0] + fVec6[1])));
		double fTemp19 = (1e-15 + (0.015 * fRec6[1]));
		fVec7[0] = fTemp19;
		fRec31[0] = ((fConst67 * fRec31[1]) + (fConst66 * (fVec7[0] + fVec7[1])));
		fRec6[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec31[0] + fRec7[0]) - 1.2716089999999989)) - 45.22606666666667);
		fRec5[0] = ((fConst39 * fRec5[1]) + (fConst63 * ((fConst35 * fRec6[0]) + (fConst36 * fRec6[1]))));
		double fTemp20 = (fRec8[0] * fRec5[0]);
		fVec8[0] = fTemp20;
		fRec4[0] = ((fConst62 * fRec4[1]) + (fConst61 * (fVec8[0] + fVec8[1])));
		fRec2[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec4[0] + fRec3[0]) - 0.797042999999999)) - 32.799634146341475);
		fRec1[0] = ((fConst39 * fRec1[1]) + (fConst63 * ((fConst35 * fRec2[0]) + (fConst36 * fRec2[1]))));
		double fTemp21 = (1e-15 + (0.0082 * fRec33[1]));
		fVec9[0] = fTemp21;
		fRec34[0] = ((fConst4 * fRec34[1]) + (fConst3 * (fVec9[0] + fVec9[1])));
		fRec33[0] = (Ftube(TUBE_TABLE_6DJ8_68k, ((fRec34[0] + fRec4[0]) - 0.799030999999999)) - 32.55719512195121);
		fRec32[0] = ((fConst39 * fRec32[1]) + (fConst63 * ((fConst35 * fRec33[0]) + (fConst36 * fRec33[1]))));
		output0[i] = (FAUSTFLOAT)((fRec32[0] + fRec1[0]) * fRec0[0]);
		double fTemp22 = (1e-15 + (0.0082 * fRec36[1]));
		fVec10[0] = fTemp22;
		fRec37[0] = ((fConst4 * fRec37[1]) + (fConst3 * (fVec10[0] + fVec10[1])));
		double fTemp23 = (double)input1[i];
		double fTemp24 = (fTemp23 * fTemp1);
		double fTemp25 = (1e-15 + (0.027 * fRec43[1]));
		fVec11[0] = fTemp25;
		fRec44[0] = ((fConst8 * fRec44[1]) + (fConst7 * (fVec11[0] + fVec11[1])));
		double fTemp26 = (1e-15 + fTemp24);
		double fTemp27 = (1e-15 + (fTemp23 * fRec11[0]));
		fRec53[0] = (fTemp27 - (fConst34 * ((fConst32 * fRec53[2]) + (fConst30 * fRec53[1]))));
		double fTemp28 = (fRec53[2] + (fRec53[0] + (2 * fRec53[1])));
		fVec12[0] = fTemp28;
		fRec52[0] = ((fConst39 * fRec52[1]) + (fConst38 * ((fConst35 * fVec12[0]) + (fConst36 * fVec12[1]))));
		fRec51[0] = ((fConst42 * fRec51[1]) + (fConst41 * (fRec52[0] + fRec52[1])));
		fRec50[0] = (fRec51[0] - (fConst28 * ((fConst26 * fRec50[2]) + (fConst24 * fRec50[1]))));
		double fTemp29 = (fRec50[2] + (fRec50[0] + (2 * fRec50[1])));
		fVec13[0] = fTemp29;
		fRec49[0] = ((fConst45 * fRec49[1]) + (fConst44 * (fVec13[0] + fVec13[1])));
		fRec48[0] = (fRec49[0] - (fConst21 * ((fConst19 * fRec48[2]) + (fConst17 * fRec48[1]))));
		double fTemp30 = (fRec48[2] + (fRec48[0] + (2 * fRec48[1])));
		fVec14[0] = fTemp30;
		fRec47[0] = ((fConst48 * fRec47[1]) + (fConst47 * (fVec14[0] + fVec14[1])));
		fRec46[0] = (fRec47[0] - (fConst14 * ((fConst13 * fRec46[2]) + (fConst11 * fRec46[1]))));
		double fTemp31 = max((double)-1, min((double)1, (fSlow7 * (fRec46[2] + (fRec46[0] + (2 * fRec46[1]))))));
		double fTemp32 = (fConst11 * fRec54[1]);
		fRec56[0] = ((fConst45 * fRec56[1]) + (fConst44 * ((fConst18 * fVec13[0]) + (fConst51 * fVec13[1]))));
		fRec55[0] = (fRec56[0] - (fConst21 * ((fConst19 * fRec55[2]) + (fConst17 * fRec55[1]))));
		fRec54[0] = ((fConst21 * (((fConst16 * fRec55[0]) + (fConst52 * fRec55[1])) + (fConst16 * fRec55[2]))) - (fConst50 * ((fConst49 * fRec54[2]) + fTemp32)));
		double fTemp33 = max((double)-1, min((double)1, (fSlow8 * (fRec54[2] + (fConst50 * (fTemp32 + (fConst49 * fRec54[0])))))));
		double fTemp34 = (fConst11 * fRec57[1]);
		double fTemp35 = (fConst17 * fRec58[1]);
		fRec60[0] = ((fConst42 * fRec60[1]) + (fConst41 * ((fConst25 * fRec52[0]) + (fConst55 * fRec52[1]))));
		fRec59[0] = (fRec60[0] - (fConst28 * ((fConst26 * fRec59[2]) + (fConst24 * fRec59[1]))));
		fRec58[0] = ((fConst28 * (((fConst23 * fRec59[0]) + (fConst56 * fRec59[1])) + (fConst23 * fRec59[2]))) - (fConst54 * ((fConst53 * fRec58[2]) + fTemp35)));
		fRec57[0] = ((fRec58[2] + (fConst54 * (fTemp35 + (fConst53 * fRec58[0])))) - (fConst50 * ((fConst49 * fRec57[2]) + fTemp34)));
		double fTemp36 = max((double)-1, min((double)1, (fSlow9 * (fRec57[2] + (fConst50 * (fTemp34 + (fConst49 * fRec57[0])))))));
		fRec62[0] = ((fConst48 * fRec62[1]) + (fConst47 * ((fConst12 * fVec14[0]) + (fConst57 * fVec14[1]))));
		fRec61[0] = (fRec62[0] - (fConst14 * ((fConst13 * fRec61[2]) + (fConst11 * fRec61[1]))));
		double fTemp37 = max((double)-1, min((double)1, (fSlow10 * (((fConst10 * fRec61[0]) + (fConst58 * fRec61[1])) + (fConst10 * fRec61[2])))));
		double fTemp38 = ((1.584893192 * ((fTemp37 * (1 - (0.3333333333333333 * faustpower<2>(fTemp37)))) + ((fTemp36 * (1 - (0.3333333333333333 * faustpower<2>(fTemp36)))) + (0.8413951417869425 * (fTemp33 * (1 - (0.3333333333333333 * faustpower<2>(fTemp33)))))))) + (1.2589412 * (fTemp31 * (1 - (0.3333333333333333 * faustpower<2>(fTemp31))))));
		fVec15[0] = fTemp38;
		fRec45[0] = ((fConst62 * fRec45[1]) + (fConst61 * (fVec15[0] + fVec15[1])));
		fRec43[0] = (Ftube(TUBE_TABLE_6DJ8_68k, (((fSlow11 * fRec45[0]) + ((fSlow6 * fTemp27) + ((fSlow4 * ((fTemp26 * (4 - (4 * fabs(fTemp26)))) - fTemp26)) + (fRec44[0] + fTemp24)))) - 1.863945999999998)) - 60.96496296296296);
		fRec42[0] = ((fConst39 * fRec42[1]) + (fConst63 * ((fConst35 * fRec43[0]) + (fConst36 * fRec43[1]))));
		double fTemp39 = (fRec8[0] * fRec42[0]);
		fVec16[0] = fTemp39;
		fRec41[0] = ((fConst62 * fRec41[1]) + (fConst61 * (fVec16[0] + fVec16[1])));
		double fTemp40 = (1e-15 + (0.015 * fRec40[1]));
		fVec17[0] = fTemp40;
		fRec63[0] = ((fConst67 * fRec63[1]) + (fConst66 * (fVec17[0] + fVec17[1])));
		fRec40[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec63[0] + fRec41[0]) - 1.2716089999999989)) - 45.22606666666667);
		fRec39[0] = ((fConst39 * fRec39[1]) + (fConst63 * ((fConst35 * fRec40[0]) + (fConst36 * fRec40[1]))));
		double fTemp41 = (fRec8[0] * fRec39[0]);
		fVec18[0] = fTemp41;
		fRec38[0] = ((fConst62 * fRec38[1]) + (fConst61 * (fVec18[0] + fVec18[1])));
		fRec36[0] = (Ftube(TUBE_TABLE_6DJ8_250k, ((fRec38[0] + fRec37[0]) - 0.797042999999999)) - 32.799634146341475);
		fRec35[0] = ((fConst39 * fRec35[1]) + (fConst63 * ((fConst35 * fRec36[0]) + (fConst36 * fRec36[1]))));
		double fTemp42 = (1e-15 + (0.0082 * fRec65[1]));
		fVec19[0] = fTemp42;
		fRec66[0] = ((fConst4 * fRec66[1]) + (fConst3 * (fVec19[0] + fVec19[1])));
		fRec65[0] = (Ftube(TUBE_TABLE_6DJ8_68k, ((fRec66[0] + fRec38[0]) - 0.799030999999999)) - 32.55719512195121);
		fRec64[0] = ((fConst39 * fRec64[1]) + (fConst63 * ((fConst35 * fRec65[0]) + (fConst36 * fRec65[1]))));
		output1[i] = (FAUSTFLOAT)(fRec0[0] * (fRec64[0] + fRec35[0]));
		// post processing
		fRec64[1] = fRec64[0];
		fRec65[1] = fRec65[0];
		fRec66[1] = fRec66[0];
		fVec19[1] = fVec19[0];
		fRec35[1] = fRec35[0];
		fRec36[1] = fRec36[0];
		fRec38[1] = fRec38[0];
		fVec18[1] = fVec18[0];
		fRec39[1] = fRec39[0];
		fRec40[1] = fRec40[0];
		fRec63[1] = fRec63[0];
		fVec17[1] = fVec17[0];
		fRec41[1] = fRec41[0];
		fVec16[1] = fVec16[0];
		fRec42[1] = fRec42[0];
		fRec43[1] = fRec43[0];
		fRec45[1] = fRec45[0];
		fVec15[1] = fVec15[0];
		fRec61[2] = fRec61[1]; fRec61[1] = fRec61[0];
		fRec62[1] = fRec62[0];
		fRec57[2] = fRec57[1]; fRec57[1] = fRec57[0];
		fRec58[2] = fRec58[1]; fRec58[1] = fRec58[0];
		fRec59[2] = fRec59[1]; fRec59[1] = fRec59[0];
		fRec60[1] = fRec60[0];
		fRec54[2] = fRec54[1]; fRec54[1] = fRec54[0];
		fRec55[2] = fRec55[1]; fRec55[1] = fRec55[0];
		fRec56[1] = fRec56[0];
		fRec46[2] = fRec46[1]; fRec46[1] = fRec46[0];
		fRec47[1] = fRec47[0];
		fVec14[1] = fVec14[0];
		fRec48[2] = fRec48[1]; fRec48[1] = fRec48[0];
		fRec49[1] = fRec49[0];
		fVec13[1] = fVec13[0];
		fRec50[2] = fRec50[1]; fRec50[1] = fRec50[0];
		fRec51[1] = fRec51[0];
		fRec52[1] = fRec52[0];
		fVec12[1] = fVec12[0];
		fRec53[2] = fRec53[1]; fRec53[1] = fRec53[0];
		fRec44[1] = fRec44[0];
		fVec11[1] = fVec11[0];
		fRec37[1] = fRec37[0];
		fVec10[1] = fVec10[0];
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
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec4[1] = fVec4[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fVec3[1] = fVec3[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fVec2[1] = fVec2[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
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
