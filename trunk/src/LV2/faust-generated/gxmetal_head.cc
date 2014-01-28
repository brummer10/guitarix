// generated from file '../src/LV2/faust/gxmetal_head.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "valve.h"

namespace gxmetal_head {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec11[2];
	double 	fVec0[2];
	double 	fVec1[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fRec14[2];
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
	double 	fRec24[2];
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fRec23[2];
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fRec22[2];
	double 	fRec21[3];
	double 	fVec2[2];
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fRec20[2];
	double 	fRec19[3];
	double 	fVec3[2];
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fRec27[2];
	double 	fRec26[3];
	double 	fConst46;
	double 	fRec25[3];
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fRec31[2];
	double 	fRec30[3];
	double 	fConst50;
	double 	fRec29[3];
	double 	fRec28[3];
	double 	fConst51;
	double 	fRec33[2];
	double 	fRec32[3];
	double 	fConst52;
	double 	fVec4[2];
	double 	fRec16[2];
	double 	fRec15[2];
	double 	fRec13[2];
	double 	fConst53;
	double 	fConst54;
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fRec12[2];
	double 	fVec5[2];
	double 	fRec10[2];
	double 	fVec6[2];
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fRec34[2];
	double 	fRec9[2];
	double 	fRec8[2];
	double 	fRec7[2];
	double 	fVec7[2];
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fRec35[2];
	double 	fRec6[2];
	double 	fRec5[2];
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fRec4[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst70;
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
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<3; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
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
	fConst25 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst26 = (1 + fConst25);
	fConst27 = (1.0 / fConst26);
	fConst28 = (0 - ((1 - fConst25) / fConst26));
	fConst29 = (1.0 / tan((376.99111843077515 / double(iConst0))));
	fConst30 = (0 - fConst29);
	fConst31 = (1 + fConst29);
	fConst32 = (1.0 / fConst31);
	fConst33 = (0 - ((1 - fConst29) / fConst31));
	fConst34 = (1 + fConst21);
	fConst35 = (1.0 / fConst34);
	fConst36 = (0 - ((1 - fConst21) / fConst34));
	fConst37 = (1 + fConst14);
	fConst38 = (1.0 / (fConst37 * fConst23));
	fConst39 = (0 - ((1 - fConst14) / fConst37));
	fConst40 = (1 + fConst8);
	fConst41 = (1.0 / (fConst40 * fConst16));
	fConst42 = (0 - ((1 - fConst8) / fConst40));
	fConst43 = (1 + ((fConst8 - 1.0) / fConst5));
	fConst44 = (1.0 / (1 + ((1.0 + fConst8) / fConst5)));
	fConst45 = (0 - fConst14);
	fConst46 = (2 * (0 - fConst12));
	fConst47 = (1 + ((fConst14 - 1.0) / fConst11));
	fConst48 = (1.0 / (1 + ((1.0 + fConst14) / fConst11)));
	fConst49 = (0 - fConst21);
	fConst50 = (2 * (0 - fConst19));
	fConst51 = (0 - fConst8);
	fConst52 = (2 * (0 - fConst6));
	fConst53 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst54 = (0 - fConst53);
	fConst55 = (1 + fConst53);
	fConst56 = (0.025 / fConst55);
	fConst57 = (0 - ((1 - fConst53) / fConst55));
	fConst58 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst59 = (1 + fConst58);
	fConst60 = (1.0 / fConst59);
	fConst61 = (0 - ((1 - fConst58) / fConst59));
	fConst62 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst63 = (1 + fConst62);
	fConst64 = (1.0 / fConst63);
	fConst65 = (0 - ((1 - fConst62) / fConst63));
	fConst66 = (1.0 / tan((1281.7698026646356 / double(iConst0))));
	fConst67 = (1 + fConst66);
	fConst68 = (1.0 / fConst67);
	fConst69 = (0 - ((1 - fConst66) / fConst67));
	fConst70 = (1.0 / tan((5830.795965062656 / double(iConst0))));
	fConst71 = (0 - fConst70);
	fConst72 = (1 + fConst70);
	fConst73 = (1.0 / fConst72);
	fConst74 = (0 - ((1 - fConst70) / fConst72));
	fConst75 = (1.0 / tan((804.247719318987 / double(iConst0))));
	fConst76 = (1 + fConst75);
	fConst77 = (0.098 / fConst76);
	fConst78 = (0 - ((1 - fConst75) / fConst76));
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
	double 	fSlow0 = double(fslider0);
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * (0 - (12 * fSlow0)))));
	double 	fSlow2 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider1))));
	double 	fSlow3 = (2 * (fSlow0 - 0.5));
	double 	fSlow4 = (1 - max((double)0, fSlow3));
	double 	fSlow5 = (fConst10 * pow(1e+01,(0.8 * fSlow0)));
	double 	fSlow6 = pow(1e+01,(1.2 * fSlow0));
	double 	fSlow7 = pow(1e+01,(1.6 * fSlow0));
	double 	fSlow8 = (fConst10 * fSlow7);
	double 	fSlow9 = (1 - max((double)0, (0 - fSlow3)));
	double 	fSlow10 = double(fslider2);
	double 	fSlow11 = (1 - fSlow10);
	double 	fSlow12 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider3))));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.999 * fRec0[1]) + fSlow1);
		fRec11[0] = ((0.999 * fRec11[1]) + fSlow2);
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		double fTemp1 = (1e-15 + (0.027 * fRec13[1]));
		fVec1[0] = fTemp1;
		fRec14[0] = ((fConst4 * fRec14[1]) + (fConst3 * (fVec1[0] + fVec1[1])));
		fRec24[0] = ((fConst28 * fRec24[1]) + (fConst27 * (fVec0[0] + fVec0[1])));
		fRec23[0] = ((fConst33 * fRec23[1]) + (fConst32 * ((fConst29 * fRec24[0]) + (fConst30 * fRec24[1]))));
		fRec22[0] = ((fConst36 * fRec22[1]) + (fConst35 * (fRec23[0] + fRec23[1])));
		fRec21[0] = (fRec22[0] - (fConst24 * ((fConst22 * fRec21[2]) + (fConst20 * fRec21[1]))));
		double fTemp2 = (fRec21[2] + (fRec21[0] + (2 * fRec21[1])));
		fVec2[0] = fTemp2;
		fRec20[0] = ((fConst39 * fRec20[1]) + (fConst38 * (fVec2[0] + fVec2[1])));
		fRec19[0] = (fRec20[0] - (fConst17 * ((fConst15 * fRec19[2]) + (fConst13 * fRec19[1]))));
		double fTemp3 = (fRec19[2] + (fRec19[0] + (2 * fRec19[1])));
		fVec3[0] = fTemp3;
		fRec18[0] = ((fConst42 * fRec18[1]) + (fConst41 * (fVec3[0] + fVec3[1])));
		fRec17[0] = (fRec18[0] - (fConst10 * ((fConst9 * fRec17[2]) + (fConst7 * fRec17[1]))));
		double fTemp4 = max((double)-1, min((double)1, (fSlow5 * (fRec17[2] + (fRec17[0] + (2 * fRec17[1]))))));
		double fTemp5 = (fConst7 * fRec25[1]);
		fRec27[0] = ((fConst39 * fRec27[1]) + (fConst38 * ((fConst14 * fVec2[0]) + (fConst45 * fVec2[1]))));
		fRec26[0] = (fRec27[0] - (fConst17 * ((fConst15 * fRec26[2]) + (fConst13 * fRec26[1]))));
		fRec25[0] = ((fConst17 * (((fConst12 * fRec26[0]) + (fConst46 * fRec26[1])) + (fConst12 * fRec26[2]))) - (fConst44 * ((fConst43 * fRec25[2]) + fTemp5)));
		double fTemp6 = max((double)-1, min((double)1, (fSlow6 * (fRec25[2] + (fConst44 * (fTemp5 + (fConst43 * fRec25[0])))))));
		double fTemp7 = (fConst7 * fRec28[1]);
		double fTemp8 = (fConst13 * fRec29[1]);
		fRec31[0] = ((fConst36 * fRec31[1]) + (fConst35 * ((fConst21 * fRec23[0]) + (fConst49 * fRec23[1]))));
		fRec30[0] = (fRec31[0] - (fConst24 * ((fConst22 * fRec30[2]) + (fConst20 * fRec30[1]))));
		fRec29[0] = ((fConst24 * (((fConst19 * fRec30[0]) + (fConst50 * fRec30[1])) + (fConst19 * fRec30[2]))) - (fConst48 * ((fConst47 * fRec29[2]) + fTemp8)));
		fRec28[0] = ((fRec29[2] + (fConst48 * (fTemp8 + (fConst47 * fRec29[0])))) - (fConst44 * ((fConst43 * fRec28[2]) + fTemp7)));
		double fTemp9 = max((double)-1, min((double)1, (fSlow7 * (fRec28[2] + (fConst44 * (fTemp7 + (fConst43 * fRec28[0])))))));
		fRec33[0] = ((fConst42 * fRec33[1]) + (fConst41 * ((fConst8 * fVec3[0]) + (fConst51 * fVec3[1]))));
		fRec32[0] = (fRec33[0] - (fConst10 * ((fConst9 * fRec32[2]) + (fConst7 * fRec32[1]))));
		double fTemp10 = max((double)-1, min((double)1, (fSlow8 * (((fConst6 * fRec32[0]) + (fConst52 * fRec32[1])) + (fConst6 * fRec32[2])))));
		double fTemp11 = ((1.584893192 * ((fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10)))) + ((fTemp9 * (1 - (0.3333333333333333 * faustpower<2>(fTemp9)))) + (0.8413951417869425 * (fTemp6 * (1 - (0.3333333333333333 * faustpower<2>(fTemp6)))))))) + (1.2589412 * (fTemp4 * (1 - (0.3333333333333333 * faustpower<2>(fTemp4))))));
		fVec4[0] = fTemp11;
		fRec16[0] = ((fConst28 * fRec16[1]) + (fConst27 * (fVec4[0] + fVec4[1])));
		fRec15[0] = ((fConst33 * fRec15[1]) + (fConst32 * ((fConst29 * fRec16[0]) + (fConst30 * fRec16[1]))));
		fRec13[0] = (Ftube(TUBE_TABLE_12AX7_68k, (((fSlow9 * fRec15[0]) + (fRec14[0] + (fSlow4 * fVec0[0]))) - 1.5816559999999988)) - 191.42014814814814);
		fRec12[0] = ((fConst57 * fRec12[1]) + (fConst56 * ((fConst53 * fRec13[0]) + (fConst54 * fRec13[1]))));
		double fTemp12 = (fRec12[0] * fRec11[0]);
		fVec5[0] = fTemp12;
		fRec10[0] = ((fConst28 * fRec10[1]) + (fConst27 * (fVec5[0] + fVec5[1])));
		double fTemp13 = (1e-15 + (0.015 * fRec9[1]));
		fVec6[0] = fTemp13;
		fRec34[0] = ((fConst61 * fRec34[1]) + (fConst60 * (fVec6[0] + fVec6[1])));
		fRec9[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec34[0] + fRec10[0]) - 1.204284999999999)) - 169.71433333333334);
		fRec8[0] = ((fConst57 * fRec8[1]) + (fConst56 * ((fConst53 * fRec9[0]) + (fConst54 * fRec9[1]))));
		fRec7[0] = ((fConst28 * fRec7[1]) + (fConst27 * (fRec8[0] + fRec8[1])));
		double fTemp14 = (1e-15 + (0.0082 * fRec6[1]));
		fVec7[0] = fTemp14;
		fRec35[0] = ((fConst65 * fRec35[1]) + (fConst64 * (fVec7[0] + fVec7[1])));
		fRec6[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec35[0] + fRec7[0]) - 0.840702999999999)) - 147.47524390243905);
		fRec5[0] = ((fConst57 * fRec5[1]) + (fConst56 * ((fConst53 * fRec6[0]) + (fConst54 * fRec6[1]))));
		fRec4[0] = ((fConst69 * fRec4[1]) + (fConst68 * (fRec5[0] + fRec5[1])));
		fRec36[0] = ((fConst74 * fRec36[1]) + (fConst73 * ((fConst70 * fRec5[0]) + (fConst71 * fRec5[1]))));
		fRec37[0] = ((0.999 * fRec37[1]) + fSlow12);
		double fTemp15 = (fRec37[0] * ((fSlow10 * fRec36[0]) + (fSlow11 * fRec4[0])));
		fRec38[0] = ((fConst78 * fRec38[1]) + (fConst77 * (fRec3[1] + fRec3[2])));
		fRec3[0] = (Ftube(TUBE_TABLE_6L6CG_250k, ((fRec38[0] + fTemp15) - 20.063657)) - 245.26880612244898);
		fRec2[0] = ((fConst57 * fRec2[1]) + (fConst56 * ((fConst53 * fRec3[0]) + (fConst54 * fRec3[1]))));
		fRec41[0] = ((fConst78 * fRec41[1]) + (fConst77 * (fRec40[1] + fRec40[2])));
		fRec40[0] = (Ftube(TUBE_TABLE_6L6CG_68k, ((fRec41[0] + fTemp15) - 20.063657)) - 245.26880612244898);
		fRec39[0] = ((fConst57 * fRec39[1]) + (fConst56 * ((fConst53 * fRec40[0]) + (fConst54 * fRec40[1]))));
		double fTemp16 = (fRec37[0] * (fRec39[0] + fRec2[0]));
		fVec8[0] = fTemp16;
		fRec1[0] = ((fConst28 * fRec1[1]) + (fConst27 * (fVec8[0] + fVec8[1])));
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
		fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fVec4[1] = fVec4[0];
		fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
		fRec33[1] = fRec33[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fVec3[1] = fVec3[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fVec2[1] = fVec2[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fRec14[1] = fRec14[0];
		fVec1[1] = fVec1[0];
		fVec0[1] = fVec0[0];
		fRec11[1] = fRec11[0];
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
