// generated from file '../src/LV2/faust/gxmetal_amp.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)

#include "valve.h"

namespace gxmetal_amp {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
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
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec8[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec19[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fVec0[2];
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fVec1[2];
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fRec24[2];
	double 	fRec21[2];
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fRec20[2];
	double 	fVec2[2];
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fRec18[2];
	double 	fVec3[2];
	double 	fRec17[2];
	double 	fRec16[3];
	double 	fVec4[2];
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fRec25[2];
	double 	fRec15[2];
	double 	fRec14[2];
	double 	fRec13[2];
	double 	fVec5[2];
	double 	fRec12[2];
	double 	fRec11[3];
	double 	fVec6[2];
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fRec26[2];
	double 	fRec10[2];
	double 	fRec9[2];
	double 	fRec7[4];
	double 	fConst36;
	double 	fConst37;
	double 	fRec6[2];
	double 	fVec7[2];
	double 	fRec5[2];
	double 	fRec4[3];
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fRec27[2];
	double 	fRec3[3];
	double 	fConst42;
	double 	fRec2[2];
	double 	fRec30[2];
	double 	fRec29[3];
	double 	fRec28[2];
	double 	fRec1[3];
	double 	fConst43;
	double 	fRec0[3];
	double 	fRec31[2];
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
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<4; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = tan((37699.11184307752 / double(iConst0)));
	fConst2 = (2 * (1 - (1.0 / faustpower<2>(fConst1))));
	fConst3 = (1.0 / fConst1);
	fConst4 = (1 + ((fConst3 - 1.414213562373095) / fConst1));
	fConst5 = (1.0 / (1 + ((1.414213562373095 + fConst3) / fConst1)));
	fConst6 = tan((125.66370614359172 / double(iConst0)));
	fConst7 = (1.0 / faustpower<2>(fConst6));
	fConst8 = (2 * (1 - fConst7));
	fConst9 = (1.0 / fConst6);
	fConst10 = (1 + ((fConst9 - 1.414213562373095) / fConst6));
	fConst11 = (1.0 / (1 + ((1.414213562373095 + fConst9) / fConst6)));
	fConst12 = (2 * double(iConst0));
	fConst13 = faustpower<2>(fConst12);
	fConst14 = (3 * fConst12);
	fConst15 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst16 = (1 + fConst15);
	fConst17 = (1.0 / fConst16);
	fConst18 = (0 - ((1 - fConst15) / fConst16));
	fConst19 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst20 = (0 - fConst19);
	fConst21 = (1 + fConst19);
	fConst22 = (0.025 / fConst21);
	fConst23 = (0 - ((1 - fConst19) / fConst21));
	fConst24 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst25 = (1 + fConst24);
	fConst26 = (1.0 / fConst25);
	fConst27 = (0 - ((1 - fConst24) / fConst25));
	fConst28 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst29 = (1 + fConst28);
	fConst30 = (1.0 / fConst29);
	fConst31 = (0 - ((1 - fConst28) / fConst29));
	fConst32 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst33 = (1 + fConst32);
	fConst34 = (1.0 / fConst33);
	fConst35 = (0 - ((1 - fConst32) / fConst33));
	fConst36 = exp((0 - (0.1 / double(iConst0))));
	fConst37 = exp((0 - (2e+02 / double(iConst0))));
	fConst38 = (1.0 / tan((804.247719318987 / double(iConst0))));
	fConst39 = (1 + fConst38);
	fConst40 = (0.06571428571428571 / fConst39);
	fConst41 = (0 - ((1 - fConst38) / fConst39));
	fConst42 = (0.1 / fConst21);
	fConst43 = (2 * (0 - fConst7));
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
	double 	fSlow1 = exp((3.4 * (0 - fSlow0)));
	double 	fSlow2 = ((3.1361660000000006e-05 * fSlow1) + 6.993481000000001e-07);
	double 	fSlow3 = ((5.967937800000002e-09 * fSlow1) + 2.9839689000000005e-11);
	double 	fSlow4 = (fConst12 * fSlow3);
	double 	fSlow5 = (0.022470000000000004 * fSlow1);
	double 	fSlow6 = (fConst12 * (0.0026376999999999998 + fSlow5));
	double 	fSlow7 = ((fSlow6 + (fConst13 * (fSlow4 - fSlow2))) - 1);
	double 	fSlow8 = (fConst14 * fSlow3);
	double 	fSlow9 = ((fSlow6 + (fConst13 * (fSlow2 - fSlow8))) - 3);
	double 	fSlow10 = ((fConst13 * (fSlow2 + fSlow8)) - (3 + fSlow6));
	double 	fSlow11 = (1.0 / (0 - (1 + (fSlow6 + (fConst13 * (fSlow2 + fSlow4))))));
	double 	fSlow12 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider1))));
	double 	fSlow13 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider2))));
	double 	fSlow14 = double(fslider3);
	double 	fSlow15 = (fSlow14 - 1);
	double 	fSlow16 = (((4.859800000000001e-07 * fSlow0) + (8.613660000000003e-06 * fSlow1)) + 9.962810000000002e-08);
	double 	fSlow17 = (3.1107890000000005e-12 + ((6.221578000000002e-10 * fSlow1) + (fSlow0 * ((5.345780000000001e-09 * fSlow1) + 2.6728900000000006e-11))));
	double 	fSlow18 = (fConst12 * fSlow17);
	double 	fSlow19 = ((fSlow5 + (0.00023500000000000002 * fSlow0)) + 0.0003347);
	double 	fSlow20 = (fConst12 * fSlow19);
	double 	fSlow21 = (fSlow20 + (fConst13 * (fSlow18 - fSlow16)));
	double 	fSlow22 = (fConst14 * fSlow17);
	double 	fSlow23 = (fSlow20 + (fConst13 * (fSlow16 - fSlow22)));
	double 	fSlow24 = (fConst12 * (0 - fSlow19));
	double 	fSlow25 = (fSlow24 + (fConst13 * (fSlow16 + fSlow22)));
	double 	fSlow26 = (fSlow24 - (fConst13 * (fSlow16 + fSlow18)));
	double 	fSlow27 = (0.0010000000000000009 * pow(10,(0.05 * (0 - (0.4 * fSlow14)))));
	for (int i=0; i<count; i++) {
		fRec8[0] = ((0.999 * fRec8[1]) + fSlow12);
		fRec19[0] = ((0.999 * fRec19[1]) + fSlow13);
		double fTemp0 = (double)input0[i];
		double fTemp1 = fabs(fTemp0);
		double fTemp2 = (1e-15 + ((fTemp0 * (fSlow14 + fTemp1)) / (1 + ((fSlow15 * fTemp1) + faustpower<2>(fTemp0)))));
		fVec0[0] = fTemp2;
		fRec23[0] = ((0.9302847925323914 * (fVec0[0] + fVec0[1])) - (0.8605695850647829 * fRec23[1]));
		fRec22[0] = (fRec23[0] - ((1.8405051250752198 * fRec22[1]) + (0.8612942439318627 * fRec22[2])));
		double fTemp3 = (1e-15 + (0.027 * fRec21[1]));
		fVec1[0] = fTemp3;
		fRec24[0] = ((fConst18 * fRec24[1]) + (fConst17 * (fVec1[0] + fVec1[1])));
		fRec21[0] = (Ftube(TUBE_TABLE_12AY7_68k, ((fRec24[0] + (0.9254498422517706 * (fRec22[2] + (fRec22[0] + (2.0 * fRec22[1]))))) - 2.775058)) - 147.2200740740741);
		fRec20[0] = ((fConst23 * fRec20[1]) + (fConst22 * ((fConst19 * fRec21[0]) + (fConst20 * fRec21[1]))));
		double fTemp4 = (fRec20[0] * fRec19[0]);
		fVec2[0] = fTemp4;
		fRec18[0] = ((fConst27 * fRec18[1]) + (fConst26 * (fVec2[0] + fVec2[1])));
		double fTemp5 = (1e-15 + fRec18[0]);
		fVec3[0] = fTemp5;
		fRec17[0] = ((0.9302847925323914 * (fVec3[0] + fVec3[1])) - (0.8605695850647829 * fRec17[1]));
		fRec16[0] = (fRec17[0] - ((1.8405051250752198 * fRec16[1]) + (0.8612942439318627 * fRec16[2])));
		double fTemp6 = (1e-15 + (0.015 * fRec15[1]));
		fVec4[0] = fTemp6;
		fRec25[0] = ((fConst31 * fRec25[1]) + (fConst30 * (fVec4[0] + fVec4[1])));
		fRec15[0] = (Ftube(TUBE_TABLE_12AY7_250k, ((fRec25[0] + (0.9254498422517706 * (fRec16[2] + (fRec16[0] + (2.0 * fRec16[1]))))) - 1.954308)) - 119.71279999999999);
		fRec14[0] = ((fConst23 * fRec14[1]) + (fConst22 * ((fConst19 * fRec15[0]) + (fConst20 * fRec15[1]))));
		fRec13[0] = ((fConst27 * fRec13[1]) + (fConst26 * (fRec14[0] + fRec14[1])));
		double fTemp7 = (1e-15 + fRec13[0]);
		fVec5[0] = fTemp7;
		fRec12[0] = ((0.9302847925323914 * (fVec5[0] + fVec5[1])) - (0.8605695850647829 * fRec12[1]));
		fRec11[0] = (fRec12[0] - ((1.8405051250752198 * fRec11[1]) + (0.8612942439318627 * fRec11[2])));
		double fTemp8 = (1e-15 + (0.0082 * fRec10[1]));
		fVec6[0] = fTemp8;
		fRec26[0] = ((fConst35 * fRec26[1]) + (fConst34 * (fVec6[0] + fVec6[1])));
		fRec10[0] = (Ftube(TUBE_TABLE_12AY7_250k, ((fRec26[0] + (0.9254498422517706 * (fRec11[2] + (fRec11[0] + (2.0 * fRec11[1]))))) - 1.264916)) - 95.7419512195122);
		fRec9[0] = ((fConst23 * fRec9[1]) + (fConst22 * ((fConst19 * fRec10[0]) + (fConst20 * fRec10[1]))));
		fRec7[0] = ((fRec9[0] * fRec8[0]) - (fSlow11 * (((fSlow10 * fRec7[1]) + (fSlow9 * fRec7[2])) + (fSlow7 * fRec7[3]))));
		double fTemp9 = ((((fSlow26 * fRec7[0]) + (fSlow25 * fRec7[1])) + (fSlow23 * fRec7[2])) + (fSlow21 * fRec7[3]));
		double fTemp10 = max((double)1, fabs((fSlow11 * fTemp9)));
		double fTemp11 = ((fConst37 * (fRec6[1] < fTemp10)) + (fConst36 * (fRec6[1] >= fTemp10)));
		fRec6[0] = ((fRec6[1] * fTemp11) + (fTemp10 * (0 - (fTemp11 - 1))));
		double fTemp12 = max((double)0, ((20 * log10(fRec6[0])) + 5e+01));
		double fTemp13 = (0.5 * min((double)1, max((double)0, (0.09522902580706599 * fTemp12))));
		double fTemp14 = (fSlow11 * (fTemp9 * pow(10,(0.05 * (1e+01 + ((fTemp12 * (0 - fTemp13)) / (1 + fTemp13)))))));
		fVec7[0] = fTemp14;
		fRec5[0] = ((0.9302847925323914 * (fVec7[0] + fVec7[1])) - (0.8605695850647829 * fRec5[1]));
		fRec4[0] = (fRec5[0] - ((1.8405051250752198 * fRec4[1]) + (0.8612942439318627 * fRec4[2])));
		double fTemp15 = (0.9254498422517706 * (fRec4[2] + (fRec4[0] + (2.0 * fRec4[1]))));
		fRec27[0] = ((fConst41 * fRec27[1]) + (fConst40 * (fRec3[1] + fRec3[2])));
		fRec3[0] = (Ftube(TUBE_TABLE_EL34_250k, ((fRec27[0] + fTemp15) - 15.743945)) - 255.41822826086957);
		fRec2[0] = ((fConst23 * fRec2[1]) + (fConst42 * ((fConst19 * fRec3[0]) + (fConst20 * fRec3[1]))));
		fRec30[0] = ((fConst41 * fRec30[1]) + (fConst40 * (fRec29[1] + fRec29[2])));
		fRec29[0] = (Ftube(TUBE_TABLE_EL34_68k, ((fRec30[0] + fTemp15) - 15.743945)) - 255.41822826086957);
		fRec28[0] = ((fConst23 * fRec28[1]) + (fConst42 * ((fConst19 * fRec29[0]) + (fConst20 * fRec29[1]))));
		fRec1[0] = ((fRec28[0] + fRec2[0]) - (fConst11 * ((fConst10 * fRec1[2]) + (fConst8 * fRec1[1]))));
		fRec0[0] = ((fConst11 * (((fConst7 * fRec1[0]) + (fConst43 * fRec1[1])) + (fConst7 * fRec1[2]))) - (fConst5 * ((fConst4 * fRec0[2]) + (fConst2 * fRec0[1]))));
		fRec31[0] = ((0.999 * fRec31[1]) + fSlow27);
		output0[i] = (FAUSTFLOAT)(fConst5 * ((fRec8[0] * fRec31[0]) * (fRec0[2] + (fRec0[0] + (2 * fRec0[1])))));
		// post processing
		fRec31[1] = fRec31[0];
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec28[1] = fRec28[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec27[1] = fRec27[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec7[1] = fVec7[0];
		fRec6[1] = fRec6[0];
		for (int i=3; i>0; i--) fRec7[i] = fRec7[i-1];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec26[1] = fRec26[0];
		fVec6[1] = fVec6[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fVec5[1] = fVec5[0];
		fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fRec25[1] = fRec25[0];
		fVec4[1] = fVec4[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fVec3[1] = fVec3[0];
		fRec18[1] = fRec18[0];
		fVec2[1] = fVec2[0];
		fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec24[1] = fRec24[0];
		fVec1[1] = fVec1[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fVec0[1] = fVec0[0];
		fRec19[1] = fRec19[0];
		fRec8[1] = fRec8[0];
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
		fslider3_ = (float*)data; // , 1.0, 1.0, 2e+01, 0.1 
		break;
	case PREGAIN: 
		fslider2_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
		break;
	case TONE: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case GAIN1: 
		fslider1_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
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
   TONE, 
   GAIN1, 
} PortIndex;
*/

} // end namespace gxmetal_amp
