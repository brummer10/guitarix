// generated from file '../src/LV2/faust/gxmetal_head.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)

#include "valve.h"

namespace gxmetal_head {

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
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec11[2];
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
	double 	fVec0[2];
	double 	fConst37;
	double 	fRec22[2];
	double 	fConst38;
	double 	fConst39;
	double 	fRec21[2];
	double 	fConst40;
	double 	fRec20[2];
	double 	fRec19[3];
	double 	fVec1[2];
	double 	fConst41;
	double 	fConst42;
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fConst43;
	double 	fRec16[3];
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fRec26[2];
	double 	fRec25[3];
	double 	fVec2[2];
	double 	fConst48;
	double 	fConst49;
	double 	fRec24[2];
	double 	fRec23[3];
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fRec30[2];
	double 	fRec29[3];
	double 	fConst54;
	double 	fRec28[3];
	double 	fRec27[3];
	double 	fRec32[2];
	double 	fRec31[3];
	double 	fVec3[2];
	double 	fRec15[2];
	double 	fRec14[2];
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fVec4[2];
	double 	fConst58;
	double 	fRec33[2];
	double 	fRec13[2];
	double 	fConst59;
	double 	fConst60;
	double 	fRec12[2];
	double 	fVec5[2];
	double 	fRec10[2];
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fVec6[2];
	double 	fConst64;
	double 	fRec34[2];
	double 	fRec9[2];
	double 	fRec8[2];
	double 	fRec7[2];
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fVec7[2];
	double 	fConst68;
	double 	fRec35[2];
	double 	fRec6[2];
	double 	fRec5[2];
	double 	fConst69;
	double 	fConst70;
	double 	fRec4[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;
	double 	fConst74;
	double 	fRec36[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec37[2];
	double 	fConst75;
	double 	fConst76;
	double 	fConst77;
	double 	fConst78;
	double 	fRec38[2];
	double 	fRec3[3];
	double 	fRec2[2];
	double 	fRec41[2];
	double 	fRec40[3];
	double 	fRec39[2];
	double 	fVec8[2];
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
	id = "metal";
	name = N_("GxMetal_head");
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
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<3; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
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
	fConst1 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = (1.0 / tan((5830.795965062656 / double(iConst0))));
	fConst8 = (1 + fConst7);
	fConst9 = (0 - ((1 - fConst7) / fConst8));
	fConst10 = (1.0 / tan((376.99111843077515 / double(iConst0))));
	fConst11 = (1 + fConst10);
	fConst12 = (0 - ((1 - fConst10) / fConst11));
	fConst13 = tan((942.4777960769379 / double(iConst0)));
	fConst14 = (1.0 / faustpower<2>(fConst13));
	fConst15 = (2 * (1 - fConst14));
	fConst16 = (1.0 / fConst13);
	fConst17 = (1 + ((fConst16 - 1.0) / fConst13));
	fConst18 = (1.0 / (1 + ((1.0 + fConst16) / fConst13)));
	fConst19 = tan((3769.9111843077517 / double(iConst0)));
	fConst20 = (1.0 / faustpower<2>(fConst19));
	fConst21 = (2 * (1 - fConst20));
	fConst22 = (1.0 / fConst19);
	fConst23 = (1 + ((fConst22 - 1.0000000000000004) / fConst19));
	fConst24 = (1 + ((fConst22 + 1.0000000000000004) / fConst19));
	fConst25 = (1.0 / fConst24);
	fConst26 = (1 + fConst22);
	fConst27 = (0 - ((1 - fConst22) / fConst26));
	fConst28 = tan((10053.096491487338 / double(iConst0)));
	fConst29 = (1.0 / faustpower<2>(fConst28));
	fConst30 = (2 * (1 - fConst29));
	fConst31 = (1.0 / fConst28);
	fConst32 = (1 + ((fConst31 - 1.0000000000000004) / fConst28));
	fConst33 = (1 + ((1.0000000000000004 + fConst31) / fConst28));
	fConst34 = (1.0 / fConst33);
	fConst35 = (1 + fConst31);
	fConst36 = (0 - ((1 - fConst31) / fConst35));
	fConst37 = (1.0 / fConst2);
	fConst38 = (0 - fConst10);
	fConst39 = (1.0 / fConst11);
	fConst40 = (1.0 / fConst35);
	fConst41 = (0 - fConst22);
	fConst42 = (1.0 / (fConst26 * fConst33));
	fConst43 = (2 * (0 - fConst20));
	fConst44 = (1 + ((fConst16 - 1.0000000000000004) / fConst13));
	fConst45 = (1.0 / (1 + ((fConst16 + 1.0000000000000004) / fConst13)));
	fConst46 = (1 + fConst16);
	fConst47 = (0 - ((1 - fConst16) / fConst46));
	fConst48 = (0 - fConst16);
	fConst49 = (1.0 / (fConst46 * fConst24));
	fConst50 = (2 * (0 - fConst14));
	fConst51 = (1 + ((fConst22 - 1.0) / fConst19));
	fConst52 = (1.0 / (1 + ((1.0 + fConst22) / fConst19)));
	fConst53 = (0 - fConst31);
	fConst54 = (2 * (0 - fConst29));
	fConst55 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst56 = (1 + fConst55);
	fConst57 = (0 - ((1 - fConst55) / fConst56));
	fConst58 = (1.0 / fConst56);
	fConst59 = (0 - fConst4);
	fConst60 = (0.025 / fConst5);
	fConst61 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst62 = (1 + fConst61);
	fConst63 = (0 - ((1 - fConst61) / fConst62));
	fConst64 = (1.0 / fConst62);
	fConst65 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst66 = (1 + fConst65);
	fConst67 = (0 - ((1 - fConst65) / fConst66));
	fConst68 = (1.0 / fConst66);
	fConst69 = (0 - fConst7);
	fConst70 = (1.0 / fConst8);
	fConst71 = (1.0 / tan((1281.7698026646356 / double(iConst0))));
	fConst72 = (1 + fConst71);
	fConst73 = (0 - ((1 - fConst71) / fConst72));
	fConst74 = (1.0 / fConst72);
	fConst75 = (1.0 / tan((804.247719318987 / double(iConst0))));
	fConst76 = (1 + fConst75);
	fConst77 = (0 - ((1 - fConst75) / fConst76));
	fConst78 = (0.098 / fConst76);
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
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * (0 - (12 * fSlow0)))));
	double 	fSlow2 = (0.0010000000000000009 * pow(10,(0.05 * fslider1)));
	double 	fSlow3 = pow(1e+01,(1.2 * fSlow0));
	double 	fSlow4 = pow(1e+01,(1.6 * fSlow0));
	double 	fSlow5 = (fConst45 * fSlow4);
	double 	fSlow6 = (fConst45 * pow(1e+01,(0.8 * fSlow0)));
	double 	fSlow7 = (2 * (fSlow0 - 0.5));
	double 	fSlow8 = (1 - max((double)0, (0 - fSlow7)));
	double 	fSlow9 = (1 - max((double)0, fSlow7));
	double 	fSlow10 = fslider2;
	double 	fSlow11 = (1 - fSlow10);
	double 	fSlow12 = (0.0010000000000000009 * pow(10,(0.05 * fslider3)));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow1 + (0.999 * fRec0[1]));
		fRec11[0] = (fSlow2 + (0.999 * fRec11[1]));
		double fTemp0 = (fConst15 * fRec16[1]);
		double fTemp1 = (double)input0[i];
		fVec0[0] = fTemp1;
		fRec22[0] = ((fConst37 * (fVec0[0] + fVec0[1])) + (fConst3 * fRec22[1]));
		fRec21[0] = ((fConst39 * ((fConst38 * fRec22[1]) + (fConst10 * fRec22[0]))) + (fConst12 * fRec21[1]));
		fRec20[0] = ((fConst40 * (fRec21[0] + fRec21[1])) + (fConst36 * fRec20[1]));
		fRec19[0] = (fRec20[0] - (fConst34 * ((fConst32 * fRec19[2]) + (fConst30 * fRec19[1]))));
		double fTemp2 = (fRec19[2] + (fRec19[0] + (2 * fRec19[1])));
		fVec1[0] = fTemp2;
		fRec18[0] = ((fConst42 * ((fConst41 * fVec1[1]) + (fConst22 * fVec1[0]))) + (fConst27 * fRec18[1]));
		fRec17[0] = (fRec18[0] - (fConst25 * ((fConst23 * fRec17[2]) + (fConst21 * fRec17[1]))));
		fRec16[0] = ((fConst25 * (((fConst20 * fRec17[0]) + (fConst43 * fRec17[1])) + (fConst20 * fRec17[2]))) - (fConst18 * ((fConst17 * fRec16[2]) + fTemp0)));
		double fTemp3 = max((double)-1, min((double)1, (fSlow3 * (fRec16[2] + (fConst18 * (fTemp0 + (fConst17 * fRec16[0])))))));
		fRec26[0] = ((fConst42 * (fVec1[0] + fVec1[1])) + (fConst27 * fRec26[1]));
		fRec25[0] = (fRec26[0] - (fConst25 * ((fConst23 * fRec25[2]) + (fConst21 * fRec25[1]))));
		double fTemp4 = (fRec25[2] + (fRec25[0] + (2 * fRec25[1])));
		fVec2[0] = fTemp4;
		fRec24[0] = ((fConst49 * ((fConst48 * fVec2[1]) + (fConst16 * fVec2[0]))) + (fConst47 * fRec24[1]));
		fRec23[0] = (fRec24[0] - (fConst45 * ((fConst44 * fRec23[2]) + (fConst15 * fRec23[1]))));
		double fTemp5 = max((double)-1, min((double)1, (fSlow5 * (((fConst14 * fRec23[0]) + (fConst50 * fRec23[1])) + (fConst14 * fRec23[2])))));
		double fTemp6 = (fConst15 * fRec27[1]);
		double fTemp7 = (fConst21 * fRec28[1]);
		fRec30[0] = ((fConst40 * ((fConst53 * fRec21[1]) + (fConst31 * fRec21[0]))) + (fConst36 * fRec30[1]));
		fRec29[0] = (fRec30[0] - (fConst34 * ((fConst32 * fRec29[2]) + (fConst30 * fRec29[1]))));
		fRec28[0] = ((fConst34 * (((fConst29 * fRec29[0]) + (fConst54 * fRec29[1])) + (fConst29 * fRec29[2]))) - (fConst52 * ((fConst51 * fRec28[2]) + fTemp7)));
		fRec27[0] = ((fRec28[2] + (fConst52 * (fTemp7 + (fConst51 * fRec28[0])))) - (fConst18 * ((fConst17 * fRec27[2]) + fTemp6)));
		double fTemp8 = max((double)-1, min((double)1, (fSlow4 * (fRec27[2] + (fConst18 * (fTemp6 + (fConst17 * fRec27[0])))))));
		fRec32[0] = ((fConst49 * (fVec2[0] + fVec2[1])) + (fConst47 * fRec32[1]));
		fRec31[0] = (fRec32[0] - (fConst45 * ((fConst44 * fRec31[2]) + (fConst15 * fRec31[1]))));
		double fTemp9 = max((double)-1, min((double)1, (fSlow6 * (fRec31[2] + (fRec31[0] + (2 * fRec31[1]))))));
		double fTemp10 = ((1.2589412 * (fTemp9 * (1 - (0.3333333333333333 * faustpower<2>(fTemp9))))) + (1.584893192 * ((fTemp8 * (1 - (0.3333333333333333 * faustpower<2>(fTemp8)))) + ((fTemp5 * (1 - (0.3333333333333333 * faustpower<2>(fTemp5)))) + (0.8413951417869425 * (fTemp3 * (1 - (0.3333333333333333 * faustpower<2>(fTemp3)))))))));
		fVec3[0] = fTemp10;
		fRec15[0] = ((fConst37 * (fVec3[0] + fVec3[1])) + (fConst3 * fRec15[1]));
		fRec14[0] = ((fConst39 * ((fConst38 * fRec15[1]) + (fConst10 * fRec15[0]))) + (fConst12 * fRec14[1]));
		double fTemp11 = (1e-15 + (0.027 * fRec13[1]));
		fVec4[0] = fTemp11;
		fRec33[0] = ((fConst58 * (fVec4[0] + fVec4[1])) + (fConst57 * fRec33[1]));
		fRec13[0] = (Ftube(TUBE_TABLE_12AX7_68k, (((fSlow9 * fVec0[0]) + (fRec33[0] + (fSlow8 * fRec14[0]))) - 1.5816559999999988)) - 191.42014814814814);
		fRec12[0] = ((fConst60 * ((fConst59 * fRec13[1]) + (fConst4 * fRec13[0]))) + (fConst6 * fRec12[1]));
		double fTemp12 = (fRec12[0] * fRec11[0]);
		fVec5[0] = fTemp12;
		fRec10[0] = ((fConst37 * (fVec5[0] + fVec5[1])) + (fConst3 * fRec10[1]));
		double fTemp13 = (1e-15 + (0.015 * fRec9[1]));
		fVec6[0] = fTemp13;
		fRec34[0] = ((fConst64 * (fVec6[0] + fVec6[1])) + (fConst63 * fRec34[1]));
		fRec9[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec34[0] + fRec10[0]) - 1.204284999999999)) - 169.71433333333334);
		fRec8[0] = ((fConst60 * ((fConst59 * fRec9[1]) + (fConst4 * fRec9[0]))) + (fConst6 * fRec8[1]));
		fRec7[0] = ((fConst37 * (fRec8[0] + fRec8[1])) + (fConst3 * fRec7[1]));
		double fTemp14 = (1e-15 + (0.0082 * fRec6[1]));
		fVec7[0] = fTemp14;
		fRec35[0] = ((fConst68 * (fVec7[0] + fVec7[1])) + (fConst67 * fRec35[1]));
		fRec6[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec35[0] + fRec7[0]) - 0.840702999999999)) - 147.47524390243905);
		fRec5[0] = ((fConst60 * ((fConst59 * fRec6[1]) + (fConst4 * fRec6[0]))) + (fConst6 * fRec5[1]));
		fRec4[0] = ((fConst70 * ((fConst69 * fRec5[1]) + (fConst7 * fRec5[0]))) + (fConst9 * fRec4[1]));
		fRec36[0] = ((fConst74 * (fRec5[0] + fRec5[1])) + (fConst73 * fRec36[1]));
		fRec37[0] = (fSlow12 + (0.999 * fRec37[1]));
		double fTemp15 = (fRec37[0] * ((fSlow11 * fRec36[0]) + (fSlow10 * fRec4[0])));
		fRec38[0] = ((fConst78 * (fRec3[1] + fRec3[2])) + (fConst77 * fRec38[1]));
		fRec3[0] = (Ftube(TUBE_TABLE_6L6CG_250k, ((fRec38[0] + fTemp15) - 20.063657)) - 245.26880612244898);
		fRec2[0] = ((fConst60 * ((fConst59 * fRec3[1]) + (fConst4 * fRec3[0]))) + (fConst6 * fRec2[1]));
		fRec41[0] = ((fConst78 * (fRec40[1] + fRec40[2])) + (fConst77 * fRec41[1]));
		fRec40[0] = (Ftube(TUBE_TABLE_6L6CG_68k, ((fRec41[0] + fTemp15) - 20.063657)) - 245.26880612244898);
		fRec39[0] = ((fConst60 * ((fConst59 * fRec40[1]) + (fConst4 * fRec40[0]))) + (fConst6 * fRec39[1]));
		double fTemp16 = (fRec37[0] * (fRec39[0] + fRec2[0]));
		fVec8[0] = fTemp16;
		fRec1[0] = ((fConst37 * (fVec8[0] + fVec8[1])) + (fConst3 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fVec8[1] = fVec8[0];
		fRec39[1] = fRec39[0];
		fRec40[2] = fRec40[1]; fRec40[1] = fRec40[0];
		fRec41[1] = fRec41[0];
		fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec38[1] = fRec38[0];
		fRec37[1] = fRec37[0];
		fRec36[1] = fRec36[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec35[1] = fRec35[0];
		fVec7[1] = fVec7[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec34[1] = fRec34[0];
		fVec6[1] = fVec6[0];
		fRec10[1] = fRec10[0];
		fVec5[1] = fVec5[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec33[1] = fRec33[0];
		fVec4[1] = fVec4[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec3[1] = fVec3[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec32[1] = fRec32[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fVec2[1] = fVec2[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fVec1[1] = fVec1[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fVec0[1] = fVec0[0];
		fRec11[1] = fRec11[0];
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
		fslider0_ = (float*)data; // , 0.35, 0.0, 1.0, 0.01 
		break;
	case PREGAIN: 
		fslider1_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
		break;
	case GAIN1: 
		fslider3_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
		break;
	case TONE: 
		fslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   PREGAIN, 
   GAIN1, 
   TONE, 
} PortIndex;
*/

} // end namespace gxmetal_head
