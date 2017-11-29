// generated from file '../src/LV2/faust/gxmetal_amp.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#include "valve.h"

namespace gxmetal_amp {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double 	fConst0;
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
	double 	fConst15;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec18[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fVec0[2];
	double 	fRec22[2];
	double 	fRec21[3];
	double 	fVec1[2];
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fRec23[2];
	double 	fRec20[2];
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fRec19[2];
	double 	fVec2[2];
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fRec17[2];
	double 	fVec3[2];
	double 	fRec16[2];
	double 	fRec15[3];
	double 	fVec4[2];
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fRec24[2];
	double 	fRec14[2];
	double 	fRec13[2];
	double 	fRec12[2];
	double 	fVec5[2];
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fVec6[2];
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fRec25[2];
	double 	fRec9[2];
	double 	fRec8[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec26[2];
	double 	fRec7[4];
	double 	fConst37;
	double 	fConst38;
	double 	fRec6[2];
	double 	fVec7[2];
	double 	fRec5[2];
	double 	fRec4[3];
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fRec27[2];
	double 	fRec3[3];
	double 	fConst43;
	double 	fRec2[2];
	double 	fRec30[2];
	double 	fRec29[3];
	double 	fRec28[2];
	double 	fRec1[3];
	double 	fConst44;
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
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
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
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = tan((37699.11184307752 / fConst0));
	fConst2 = (2 * (1 - (1.0 / faustpower<2>(fConst1))));
	fConst3 = (1.0 / fConst1);
	fConst4 = (1 + ((fConst3 - 1.414213562373095) / fConst1));
	fConst5 = (1.0 / (1 + ((1.414213562373095 + fConst3) / fConst1)));
	fConst6 = tan((125.66370614359172 / fConst0));
	fConst7 = (1.0 / faustpower<2>(fConst6));
	fConst8 = (2 * (1 - fConst7));
	fConst9 = (1.0 / fConst6);
	fConst10 = (1 + ((fConst9 - 1.414213562373095) / fConst6));
	fConst11 = (1.0 / (1 + ((1.414213562373095 + fConst9) / fConst6)));
	fConst12 = double(fConst0);
	fConst13 = (2 * fConst12);
	fConst14 = (6 * fConst12);
	fConst15 = faustpower<2>(fConst13);
	fConst16 = (1.0 / tan((270.1769682087222 / fConst0)));
	fConst17 = (1 + fConst16);
	fConst18 = (1.0 / fConst17);
	fConst19 = (0 - ((1 - fConst16) / fConst17));
	fConst20 = (1.0 / tan((97.38937226128358 / fConst0)));
	fConst21 = (0 - fConst20);
	fConst22 = (1 + fConst20);
	fConst23 = (0.025 / fConst22);
	fConst24 = (0 - ((1 - fConst20) / fConst22));
	fConst25 = (1.0 / tan((20517.741620594938 / fConst0)));
	fConst26 = (1 + fConst25);
	fConst27 = (1.0 / fConst26);
	fConst28 = (0 - ((1 - fConst25) / fConst26));
	fConst29 = (1.0 / tan((414.6902302738527 / fConst0)));
	fConst30 = (1 + fConst29);
	fConst31 = (1.0 / fConst30);
	fConst32 = (0 - ((1 - fConst29) / fConst30));
	fConst33 = (1.0 / tan((609.4689747964198 / fConst0)));
	fConst34 = (1 + fConst33);
	fConst35 = (1.0 / fConst34);
	fConst36 = (0 - ((1 - fConst33) / fConst34));
	fConst37 = exp((0 - (0.1 / fConst0)));
	fConst38 = exp((0 - (2e+02 / fConst0)));
	fConst39 = (1.0 / tan((804.247719318987 / fConst0)));
	fConst40 = (1 + fConst39);
	fConst41 = (0 - ((1 - fConst39) / fConst40));
	fConst42 = (0.06571428571428571 / fConst40);
	fConst43 = (0.1 / fConst22);
	fConst44 = (2 * (0 - fConst7));
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
	double 	fSlow2 = (0.022470000000000004 * fSlow1);
	double 	fSlow3 = (fConst13 * (0.0026376999999999998 + fSlow2));
	double 	fSlow4 = ((5.967937800000002e-09 * fSlow1) + 2.9839689000000005e-11);
	double 	fSlow5 = (fConst14 * fSlow4);
	double 	fSlow6 = (3.1361660000000006e-05 * fSlow1);
	double 	fSlow7 = ((fConst15 * (6.993481000000001e-07 + (fSlow6 + fSlow5))) - (3 + fSlow3));
	double 	fSlow8 = (fSlow6 + 6.993481000000001e-07);
	double 	fSlow9 = (fConst13 * fSlow4);
	double 	fSlow10 = ((fSlow3 + (fConst15 * (fSlow9 - fSlow8))) - 1);
	double 	fSlow11 = ((fSlow3 + (fConst15 * (fSlow8 - fSlow5))) - 3);
	double 	fSlow12 = (1.0 / (0 - (1 + (fSlow3 + (fConst15 * (6.993481000000001e-07 + (fSlow6 + fSlow9)))))));
	double 	fSlow13 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider1))));
	double 	fSlow14 = double(fslider2);
	double 	fSlow15 = (fSlow14 - 1);
	double 	fSlow16 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider3))));
	double 	fSlow17 = (3.1107890000000005e-12 + ((6.221578000000002e-10 * fSlow1) + (fSlow0 * ((5.345780000000001e-09 * fSlow1) + 2.6728900000000006e-11))));
	double 	fSlow18 = (fConst13 * fSlow17);
	double 	fSlow19 = ((4.859800000000001e-07 * fSlow0) + (8.613660000000003e-06 * fSlow1));
	double 	fSlow20 = ((fSlow2 + (0.00023500000000000002 * fSlow0)) + 0.0003347);
	double 	fSlow21 = (fConst13 * (0 - fSlow20));
	double 	fSlow22 = (fSlow21 - (fConst15 * (9.962810000000002e-08 + (fSlow19 + fSlow18))));
	double 	fSlow23 = (fSlow19 + 9.962810000000002e-08);
	double 	fSlow24 = (fConst13 * fSlow20);
	double 	fSlow25 = (fSlow24 + (fConst15 * (fSlow18 - fSlow23)));
	double 	fSlow26 = (fConst14 * fSlow17);
	double 	fSlow27 = (fSlow21 + (fConst15 * (9.962810000000002e-08 + (fSlow19 + fSlow26))));
	double 	fSlow28 = (fSlow24 + (fConst15 * (fSlow23 - fSlow26)));
	double 	fSlow29 = (0.0010000000000000009 * pow(10,(0.05 * (0 - (0.4 * fSlow14)))));
	for (int i=0; i<count; i++) {
		fRec18[0] = (fSlow13 + (0.999 * fRec18[1]));
		double fTemp0 = (double)input0[i];
		double fTemp1 = fabs(fTemp0);
		double fTemp2 = ((fTemp0 * (fSlow14 + fTemp1)) / (1 + ((fSlow15 * fTemp1) + faustpower<2>(fTemp0))));
		fVec0[0] = (1e-15 + fTemp2);
		fRec22[0] = ((0.9302847925323914 * (1e-15 + (fTemp2 + fVec0[1]))) - (0.8605695850647829 * fRec22[1]));
		fRec21[0] = (fRec22[0] - ((1.8405051250752198 * fRec21[1]) + (0.8612942439318627 * fRec21[2])));
		double fTemp3 = (0.027 * fRec20[1]);
		fVec1[0] = (1e-15 + fTemp3);
		fRec23[0] = ((fConst19 * fRec23[1]) + (fConst18 * (1e-15 + (fTemp3 + fVec1[1]))));
		fRec20[0] = (Ftube(TUBE_TABLE_12AY7_68k, ((fRec23[0] + (0.9254498422517706 * (fRec21[0] + (fRec21[2] + (2.0 * fRec21[1]))))) - 2.775058)) - 147.2200740740741);
		fRec19[0] = ((fConst24 * fRec19[1]) + (fConst23 * ((fConst20 * fRec20[0]) + (fConst21 * fRec20[1]))));
		double fTemp4 = (fRec19[0] * fRec18[0]);
		fVec2[0] = fTemp4;
		fRec17[0] = ((fConst28 * fRec17[1]) + (fConst27 * (fVec2[0] + fVec2[1])));
		fVec3[0] = (1e-15 + fRec17[0]);
		fRec16[0] = ((0.9302847925323914 * (1e-15 + (fRec17[0] + fVec3[1]))) - (0.8605695850647829 * fRec16[1]));
		fRec15[0] = (fRec16[0] - ((1.8405051250752198 * fRec15[1]) + (0.8612942439318627 * fRec15[2])));
		double fTemp5 = (0.015 * fRec14[1]);
		fVec4[0] = (1e-15 + fTemp5);
		fRec24[0] = ((fConst32 * fRec24[1]) + (fConst31 * (1e-15 + (fTemp5 + fVec4[1]))));
		fRec14[0] = (Ftube(TUBE_TABLE_12AY7_250k, ((fRec24[0] + (0.9254498422517706 * (fRec15[0] + (fRec15[2] + (2.0 * fRec15[1]))))) - 1.954308)) - 119.71279999999999);
		fRec13[0] = ((fConst24 * fRec13[1]) + (fConst23 * ((fConst20 * fRec14[0]) + (fConst21 * fRec14[1]))));
		fRec12[0] = ((fConst28 * fRec12[1]) + (fConst27 * (fRec13[1] + fRec13[0])));
		fVec5[0] = (1e-15 + fRec12[0]);
		fRec11[0] = ((0.9302847925323914 * (1e-15 + (fRec12[0] + fVec5[1]))) - (0.8605695850647829 * fRec11[1]));
		fRec10[0] = (fRec11[0] - ((1.8405051250752198 * fRec10[1]) + (0.8612942439318627 * fRec10[2])));
		double fTemp6 = (0.0082 * fRec9[1]);
		fVec6[0] = (1e-15 + fTemp6);
		fRec25[0] = ((fConst36 * fRec25[1]) + (fConst35 * (1e-15 + (fTemp6 + fVec6[1]))));
		fRec9[0] = (Ftube(TUBE_TABLE_12AY7_250k, ((fRec25[0] + (0.9254498422517706 * (fRec10[0] + (fRec10[2] + (2.0 * fRec10[1]))))) - 1.264916)) - 95.7419512195122);
		fRec8[0] = ((fConst24 * fRec8[1]) + (fConst23 * ((fConst20 * fRec9[0]) + (fConst21 * fRec9[1]))));
		fRec26[0] = (fSlow16 + (0.999 * fRec26[1]));
		fRec7[0] = ((fRec26[0] * fRec8[0]) - (fSlow12 * ((fSlow11 * fRec7[2]) + ((fSlow10 * fRec7[3]) + (fSlow7 * fRec7[1])))));
		double fTemp7 = ((fSlow28 * fRec7[2]) + ((fSlow27 * fRec7[1]) + ((fSlow25 * fRec7[3]) + (fSlow22 * fRec7[0]))));
		double fTemp8 = max((double)1, fabs((fSlow12 * fTemp7)));
		double fTemp9 = ((fConst38 * (fRec6[1] < fTemp8)) + (fConst37 * (fRec6[1] >= fTemp8)));
		fRec6[0] = ((fRec6[1] * fTemp9) + (fTemp8 * (0 - (fTemp9 - 1))));
		double fTemp10 = max((double)0, (5e+01 + (20 * log10(fRec6[0]))));
		double fTemp11 = (0.5 * min((double)1, max((double)0, (0.09522902580706599 * fTemp10))));
		double fTemp12 = (fSlow12 * (fTemp7 * pow(10,(0.05 * (1e+01 + ((fTemp10 * (0 - fTemp11)) / (1 + fTemp11)))))));
		fVec7[0] = fTemp12;
		fRec5[0] = ((0.9302847925323914 * (fVec7[0] + fVec7[1])) - (0.8605695850647829 * fRec5[1]));
		fRec4[0] = (fRec5[0] - ((1.8405051250752198 * fRec4[1]) + (0.8612942439318627 * fRec4[2])));
		double fTemp13 = (0.9254498422517706 * (fRec4[0] + (fRec4[2] + (2.0 * fRec4[1]))));
		fRec27[0] = ((fConst42 * (fRec3[1] + fRec3[2])) + (fConst41 * fRec27[1]));
		fRec3[0] = (Ftube(TUBE_TABLE_EL34_250k, ((fRec27[0] + fTemp13) - 15.743945)) - 255.41822826086957);
		fRec2[0] = ((fConst24 * fRec2[1]) + (fConst43 * ((fConst20 * fRec3[0]) + (fConst21 * fRec3[1]))));
		fRec30[0] = ((fConst42 * (fRec29[1] + fRec29[2])) + (fConst41 * fRec30[1]));
		fRec29[0] = (Ftube(TUBE_TABLE_EL34_68k, ((fRec30[0] + fTemp13) - 15.743945)) - 255.41822826086957);
		fRec28[0] = ((fConst24 * fRec28[1]) + (fConst43 * ((fConst20 * fRec29[0]) + (fConst21 * fRec29[1]))));
		fRec1[0] = ((fRec28[0] + fRec2[0]) - (fConst11 * ((fConst10 * fRec1[2]) + (fConst8 * fRec1[1]))));
		fRec0[0] = ((fConst11 * ((fConst44 * fRec1[1]) + (fConst7 * (fRec1[2] + fRec1[0])))) - (fConst5 * ((fConst4 * fRec0[2]) + (fConst2 * fRec0[1]))));
		fRec31[0] = (fSlow29 + (0.999 * fRec31[1]));
		output0[i] = (FAUSTFLOAT)(fConst5 * ((fRec26[0] * fRec31[0]) * (fRec0[0] + (fRec0[2] + (2 * fRec0[1])))));
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
		fRec26[1] = fRec26[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec25[1] = fRec25[0];
		fVec6[1] = fVec6[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec5[1] = fVec5[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fRec24[1] = fRec24[0];
		fVec4[1] = fVec4[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fVec3[1] = fVec3[0];
		fRec17[1] = fRec17[0];
		fVec2[1] = fVec2[0];
		fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec23[1] = fRec23[0];
		fVec1[1] = fVec1[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fVec0[1] = fVec0[0];
		fRec18[1] = fRec18[0];
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
		fslider2_ = (float*)data; // , 1.0, 1.0, 2e+01, 0.1 
		break;
	case PREGAIN: 
		fslider1_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
		break;
	case TONE: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case GAIN1: 
		fslider3_ = (float*)data; // , -6.0, -2e+01, 2e+01, 0.1 
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
