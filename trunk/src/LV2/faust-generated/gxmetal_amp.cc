// generated from file '../src/LV2/faust/gxmetal_amp.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)

#include "valve.h"

namespace gxmetal_amp {

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
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec6[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec13[2];
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
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fVec0[2];
	double 	fConst63;
	double 	fConst64;
	double 	fRec24[2];
	double 	fRec23[3];
	double 	fConst65;
	double 	fRec22[3];
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fRec21[3];
	double 	fConst69;
	double 	fConst70;
	double 	fConst71;
	double 	fRec20[3];
	double 	fConst72;
	double 	fConst73;
	double 	fConst74;
	double 	fRec19[3];
	double 	fConst75;
	double 	fConst76;
	double 	fConst77;
	double 	fRec18[3];
	double 	fConst78;
	double 	fConst79;
	double 	fConst80;
	double 	fVec1[2];
	double 	fConst81;
	double 	fRec17[2];
	double 	fRec16[3];
	double 	fConst82;
	double 	fConst83;
	double 	fConst84;
	double 	fConst85;
	double 	fVec2[2];
	double 	fConst86;
	double 	fRec25[2];
	double 	fRec15[2];
	double 	fConst87;
	double 	fConst88;
	double 	fRec14[2];
	double 	fVec3[2];
	double 	fConst89;
	double 	fRec12[2];
	double 	fConst90;
	double 	fConst91;
	double 	fConst92;
	double 	fVec4[2];
	double 	fConst93;
	double 	fRec26[2];
	double 	fRec11[2];
	double 	fRec10[2];
	double 	fRec9[2];
	double 	fConst94;
	double 	fConst95;
	double 	fConst96;
	double 	fVec5[2];
	double 	fConst97;
	double 	fRec27[2];
	double 	fRec8[2];
	double 	fRec7[2];
	double 	fRec5[4];
	double 	fConst98;
	double 	fConst99;
	double 	fRec4[2];
	double 	fVec6[2];
	double 	fRec28[2];
	double 	fRec3[2];
	double 	fRec2[2];
	double 	fVec7[2];
	double 	fRec31[2];
	double 	fRec30[2];
	double 	fRec29[2];
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
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<4; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
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
	fConst7 = (2 * double(iConst0));
	fConst8 = faustpower<2>(fConst7);
	fConst9 = (3 * fConst7);
	fConst10 = tan((37699.11184307752 / double(iConst0)));
	fConst11 = (2 * (1 - (1.0 / faustpower<2>(fConst10))));
	fConst12 = (1.0 / fConst10);
	fConst13 = (1 + ((fConst12 - 1.0000000000000004) / fConst10));
	fConst14 = (1 + ((1.0000000000000004 + fConst12) / fConst10));
	fConst15 = (1.0 / fConst14);
	fConst16 = (1 + fConst12);
	fConst17 = (0 - ((1 - fConst12) / fConst16));
	fConst18 = tan((25132.741228718343 / double(iConst0)));
	fConst19 = (2 * (1 - (1.0 / faustpower<2>(fConst18))));
	fConst20 = double((1.0 / double(iConst0)));
	fConst21 = (fConst20 / sin((50265.48245743669 * fConst20)));
	fConst22 = (3141.592653589793 * fConst21);
	fConst23 = (1.0 / fConst18);
	fConst24 = (1 + ((fConst23 - fConst22) / fConst18));
	fConst25 = (1 + ((fConst22 + fConst23) / fConst18));
	fConst26 = (1.0 / fConst25);
	fConst27 = tan((12566.370614359172 / double(iConst0)));
	fConst28 = (2 * (1 - (1.0 / faustpower<2>(fConst27))));
	fConst29 = (fConst20 / sin((25132.741228718343 * fConst20)));
	fConst30 = (6268.301430690795 * fConst29);
	fConst31 = (1.0 / fConst27);
	fConst32 = (1 + ((fConst31 - fConst30) / fConst27));
	fConst33 = (1.0 / (1 + ((fConst30 + fConst31) / fConst27)));
	fConst34 = tan((6283.185307179586 / double(iConst0)));
	fConst35 = (2 * (1 - (1.0 / faustpower<2>(fConst34))));
	fConst36 = (fConst20 / sin((12566.370614359172 * fConst20)));
	fConst37 = (1570.7963267948965 * fConst36);
	fConst38 = (1.0 / fConst34);
	fConst39 = (1 + ((fConst38 - fConst37) / fConst34));
	fConst40 = (1.0 / (1 + ((fConst37 + fConst38) / fConst34)));
	fConst41 = tan((1178.0972450961724 / double(iConst0)));
	fConst42 = (2 * (1 - (1.0 / faustpower<2>(fConst41))));
	fConst43 = (fConst20 / sin((2356.194490192345 * fConst20)));
	fConst44 = (392.6990816987241 * fConst43);
	fConst45 = (1.0 / fConst41);
	fConst46 = (1 + ((fConst45 - fConst44) / fConst41));
	fConst47 = (1.0 / (1 + ((fConst44 + fConst45) / fConst41)));
	fConst48 = tan((628.3185307179587 / double(iConst0)));
	fConst49 = (2 * (1 - (1.0 / faustpower<2>(fConst48))));
	fConst50 = (fConst20 / sin((1256.6370614359173 * fConst20)));
	fConst51 = (221.8808786553305 * fConst50);
	fConst52 = (1.0 / fConst48);
	fConst53 = (1 + ((fConst52 - fConst51) / fConst48));
	fConst54 = (1.0 / (1 + ((fConst51 + fConst52) / fConst48)));
	fConst55 = tan((251.32741228718345 / double(iConst0)));
	fConst56 = (1.0 / faustpower<2>(fConst55));
	fConst57 = (2 * (1 - fConst56));
	fConst58 = (1.0 / fConst55);
	fConst59 = (1 + ((fConst58 - 1.0000000000000004) / fConst55));
	fConst60 = (1.0 / (1 + ((1.0000000000000004 + fConst58) / fConst55)));
	fConst61 = (1 + fConst58);
	fConst62 = (0 - ((1 - fConst58) / fConst61));
	fConst63 = (0 - fConst58);
	fConst64 = (1.0 / fConst61);
	fConst65 = (2 * (0 - fConst56));
	fConst66 = (157.07963267948966 * fConst50);
	fConst67 = (1 + ((fConst52 - fConst66) / fConst48));
	fConst68 = (1 + ((fConst66 + fConst52) / fConst48));
	fConst69 = (466.72373331140534 * fConst43);
	fConst70 = (1 + ((fConst45 - fConst69) / fConst41));
	fConst71 = (1 + ((fConst69 + fConst45) / fConst41));
	fConst72 = (2218.808786553305 * fConst36);
	fConst73 = (1 + ((fConst38 - fConst72) / fConst34));
	fConst74 = (1 + ((fConst72 + fConst38) / fConst34));
	fConst75 = (3141.592653589793 * fConst29);
	fConst76 = (1 + ((fConst31 - fConst75) / fConst27));
	fConst77 = (1 + ((fConst75 + fConst31) / fConst27));
	fConst78 = (3955.030825110061 * fConst21);
	fConst79 = (1 + ((fConst23 - fConst78) / fConst18));
	fConst80 = (1 + ((fConst78 + fConst23) / fConst18));
	fConst81 = (1.0 / (fConst16 * fConst25));
	fConst82 = (1.0 / faustpower<2>(fConst14));
	fConst83 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst84 = (1 + fConst83);
	fConst85 = (0 - ((1 - fConst83) / fConst84));
	fConst86 = (1.0 / fConst84);
	fConst87 = (0 - fConst4);
	fConst88 = (0.025 / fConst5);
	fConst89 = (1.0 / fConst2);
	fConst90 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst91 = (1 + fConst90);
	fConst92 = (0 - ((1 - fConst90) / fConst91));
	fConst93 = (1.0 / fConst91);
	fConst94 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst95 = (1 + fConst94);
	fConst96 = (0 - ((1 - fConst94) / fConst95));
	fConst97 = (1.0 / fConst95);
	fConst98 = exp((0 - (2e+02 / double(iConst0))));
	fConst99 = exp((0 - (0.1 / double(iConst0))));
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
	double 	fSlow1 = (0.0010000000000000009 * pow(10,(0.05 * (0 - (0.4 * fSlow0)))));
	double 	fSlow2 = fslider1;
	double 	fSlow3 = exp((3.4 * (0 - fSlow2)));
	double 	fSlow4 = ((8.09459375e-05 * fSlow3) + 5.183421875000001e-06);
	double 	fSlow5 = ((5.121875000000001e-09 * fSlow3) + 2.5609375e-10);
	double 	fSlow6 = (fConst7 * fSlow5);
	double 	fSlow7 = (0.0250625 * fSlow3);
	double 	fSlow8 = (fConst7 * (fSlow7 + 0.01870375));
	double 	fSlow9 = ((fSlow8 + (fConst8 * (fSlow6 - fSlow4))) - 1);
	double 	fSlow10 = (fConst9 * fSlow5);
	double 	fSlow11 = ((fConst8 * (fSlow4 + fSlow10)) - (3 + fSlow8));
	double 	fSlow12 = ((fSlow8 + (fConst8 * (fSlow4 - fSlow10))) - 3);
	double 	fSlow13 = (1.0 / (0 - (1 + (fSlow8 + (fConst8 * (fSlow4 + fSlow6))))));
	double 	fSlow14 = (0.0010000000000000009 * pow(10,(0.05 * fslider2)));
	double 	fSlow15 = (0.0010000000000000009 * pow(10,(0.05 * fslider3)));
	double 	fSlow16 = (fSlow0 - 1);
	double 	fSlow17 = (3.265625e-11 + ((6.531250000000001e-10 * fSlow3) + (fSlow2 * ((4.468750000000001e-09 * fSlow3) + 2.234375e-10))));
	double 	fSlow18 = (fConst9 * fSlow17);
	double 	fSlow19 = (((9.912500000000003e-07 * fSlow2) + (9.445937500000003e-06 * fSlow3)) + 6.17171875e-07);
	double 	fSlow20 = ((fSlow7 + (6.25e-05 * fSlow2)) + 0.0027812500000000003);
	double 	fSlow21 = (fConst7 * fSlow20);
	double 	fSlow22 = (fSlow21 + (fConst8 * (fSlow19 - fSlow18)));
	double 	fSlow23 = (fConst7 * fSlow17);
	double 	fSlow24 = (fSlow21 + (fConst8 * (fSlow23 - fSlow19)));
	double 	fSlow25 = (fConst7 * (0 - fSlow20));
	double 	fSlow26 = (fSlow25 + (fConst8 * (fSlow19 + fSlow18)));
	double 	fSlow27 = (fSlow25 - (fConst8 * (fSlow19 + fSlow23)));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow1 + (0.999 * fRec0[1]));
		fRec6[0] = (fSlow14 + (0.999 * fRec6[1]));
		fRec13[0] = (fSlow15 + (0.999 * fRec13[1]));
		double fTemp0 = (fConst19 * fRec18[1]);
		double fTemp1 = (fConst28 * fRec19[1]);
		double fTemp2 = (fConst35 * fRec20[1]);
		double fTemp3 = (fConst42 * fRec21[1]);
		double fTemp4 = (fConst49 * fRec22[1]);
		double fTemp5 = (double)input0[i];
		fVec0[0] = fTemp5;
		fRec24[0] = ((fConst64 * ((fConst63 * fVec0[1]) + (fConst58 * fVec0[0]))) + (fConst62 * fRec24[1]));
		fRec23[0] = (fRec24[0] - (fConst60 * ((fConst59 * fRec23[2]) + (fConst57 * fRec23[1]))));
		fRec22[0] = ((fConst60 * (((fConst56 * fRec23[0]) + (fConst65 * fRec23[1])) + (fConst56 * fRec23[2]))) - (fConst54 * ((fConst53 * fRec22[2]) + fTemp4)));
		fRec21[0] = ((fConst54 * ((fTemp4 + (fConst68 * fRec22[0])) + (fConst67 * fRec22[2]))) - (fConst47 * ((fConst46 * fRec21[2]) + fTemp3)));
		fRec20[0] = ((fConst47 * ((fTemp3 + (fConst71 * fRec21[0])) + (fConst70 * fRec21[2]))) - (fConst40 * ((fConst39 * fRec20[2]) + fTemp2)));
		fRec19[0] = ((fConst40 * ((fTemp2 + (fConst74 * fRec20[0])) + (fConst73 * fRec20[2]))) - (fConst33 * ((fConst32 * fRec19[2]) + fTemp1)));
		fRec18[0] = ((fConst33 * ((fTemp1 + (fConst77 * fRec19[0])) + (fConst76 * fRec19[2]))) - (fConst26 * ((fConst24 * fRec18[2]) + fTemp0)));
		double fTemp6 = ((fTemp0 + (fConst80 * fRec18[0])) + (fConst79 * fRec18[2]));
		fVec1[0] = fTemp6;
		fRec17[0] = ((fConst81 * (fVec1[0] + fVec1[1])) + (fConst17 * fRec17[1]));
		fRec16[0] = (fRec17[0] - (fConst15 * ((fConst13 * fRec16[2]) + (fConst11 * fRec16[1]))));
		double fTemp7 = (fRec16[2] + (fRec16[0] + (2 * fRec16[1])));
		double fTemp8 = fabs((fConst15 * fTemp7));
		double fTemp9 = (1e-15 + (0.027 * fRec15[1]));
		fVec2[0] = fTemp9;
		fRec25[0] = ((fConst86 * (fVec2[0] + fVec2[1])) + (fConst85 * fRec25[1]));
		fRec15[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec25[0] + (fConst15 * ((fTemp7 * (fSlow0 + fTemp8)) / (1 + ((fSlow16 * fTemp8) + (fConst82 * faustpower<2>(fTemp7))))))) - 1.5816559999999988)) - 191.42014814814814);
		fRec14[0] = ((fConst88 * ((fConst87 * fRec15[1]) + (fConst4 * fRec15[0]))) + (fConst6 * fRec14[1]));
		double fTemp10 = (fRec14[0] * fRec13[0]);
		fVec3[0] = fTemp10;
		fRec12[0] = ((fConst89 * (fVec3[0] + fVec3[1])) + (fConst3 * fRec12[1]));
		double fTemp11 = (1e-15 + (0.015 * fRec11[1]));
		fVec4[0] = fTemp11;
		fRec26[0] = ((fConst93 * (fVec4[0] + fVec4[1])) + (fConst92 * fRec26[1]));
		fRec11[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec26[0] + fRec12[0]) - 1.204284999999999)) - 169.71433333333334);
		fRec10[0] = ((fConst88 * ((fConst87 * fRec11[1]) + (fConst4 * fRec11[0]))) + (fConst6 * fRec10[1]));
		fRec9[0] = ((fConst89 * (fRec10[0] + fRec10[1])) + (fConst3 * fRec9[1]));
		double fTemp12 = (1e-15 + (0.0082 * fRec8[1]));
		fVec5[0] = fTemp12;
		fRec27[0] = ((fConst97 * (fVec5[0] + fVec5[1])) + (fConst96 * fRec27[1]));
		fRec8[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec27[0] + fRec9[0]) - 0.840702999999999)) - 147.47524390243905);
		fRec7[0] = ((fConst88 * ((fConst87 * fRec8[1]) + (fConst4 * fRec8[0]))) + (fConst6 * fRec7[1]));
		fRec5[0] = ((fRec7[0] * fRec6[0]) - (fSlow13 * (((fSlow12 * fRec5[2]) + (fSlow11 * fRec5[1])) + (fSlow9 * fRec5[3]))));
		double fTemp13 = ((fSlow27 * fRec5[0]) + ((fSlow26 * fRec5[1]) + ((fSlow24 * fRec5[3]) + (fSlow22 * fRec5[2]))));
		double fTemp14 = max((double)1, fabs((fSlow13 * fTemp13)));
		double fTemp15 = ((fConst99 * (fRec4[1] >= fTemp14)) + (fConst98 * (fRec4[1] < fTemp14)));
		fRec4[0] = ((fTemp14 * (0 - (fTemp15 - 1))) + (fRec4[1] * fTemp15));
		double fTemp16 = max((double)0, ((20 * log10(fRec4[0])) + 5e+01));
		double fTemp17 = (0.5 * min((double)1, max((double)0, (0.09522902580706599 * fTemp16))));
		double fTemp18 = (fSlow13 * (fTemp13 * pow(10,(0.05 * (1e+01 + ((fTemp16 * (0 - fTemp17)) / (1 + fTemp17)))))));
		double fTemp19 = (1e-15 + (0.0041 * fRec3[1]));
		fVec6[0] = fTemp19;
		fRec28[0] = ((fConst89 * (fVec6[0] + fVec6[1])) + (fConst3 * fRec28[1]));
		fRec3[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec28[0] + fTemp18) - 0.659760999999999)) - 89.08268292682925);
		fRec2[0] = ((fConst88 * ((fConst87 * fRec3[1]) + (fConst4 * fRec3[0]))) + (fConst6 * fRec2[1]));
		double fTemp20 = (1e-15 + (0.0041 * fRec30[1]));
		fVec7[0] = fTemp20;
		fRec31[0] = ((fConst89 * (fVec7[0] + fVec7[1])) + (fConst3 * fRec31[1]));
		fRec30[0] = (Ftube(TUBE_TABLE_6V6_68k, ((fRec31[0] + fTemp18) - 0.664540999999999)) - 87.91682926829267);
		fRec29[0] = ((fConst88 * ((fConst87 * fRec30[1]) + (fConst4 * fRec30[0]))) + (fConst6 * fRec29[1]));
		double fTemp21 = (fRec29[0] + fRec2[0]);
		fVec8[0] = fTemp21;
		fRec1[0] = ((fConst89 * (fVec8[0] + fVec8[1])) + (fConst3 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fVec8[1] = fVec8[0];
		fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fVec7[1] = fVec7[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec28[1] = fRec28[0];
		fVec6[1] = fVec6[0];
		fRec4[1] = fRec4[0];
		for (int i=3; i>0; i--) fRec5[i] = fRec5[i-1];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec27[1] = fRec27[0];
		fVec5[1] = fVec5[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec26[1] = fRec26[0];
		fVec4[1] = fVec4[0];
		fRec12[1] = fRec12[0];
		fVec3[1] = fVec3[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec25[1] = fRec25[0];
		fVec2[1] = fVec2[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fVec1[1] = fVec1[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fVec0[1] = fVec0[0];
		fRec13[1] = fRec13[0];
		fRec6[1] = fRec6[0];
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
	case PREGAIN: 
		fslider3_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
		break;
	case GAIN1: 
		fslider2_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
		break;
	case TONE: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case DRIVE: 
		fslider0_ = (float*)data; // , 1.0, 1.0, 2e+01, 0.1 
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
   PREGAIN, 
   GAIN1, 
   TONE, 
   DRIVE, 
} PortIndex;
*/

} // end namespace gxmetal_amp
