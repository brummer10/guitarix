// generated from file '../src/plugins/mbd.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace mbd {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	double 	fRec0[2];
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider1;
	double 	fConst2;
	double 	fRec5[2];
	double 	fVec1[2];
	double 	fRec4[2];
	double 	fRec3[3];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	double 	fVec2[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT 	fslider4;
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fVec3[2];
	double 	fRec9[2];
	double 	fRec8[3];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	double 	fVec4[2];
	double 	fRec7[2];
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT 	fslider7;
	double 	fRec17[2];
	double 	fRec16[3];
	double 	fVec5[2];
	double 	fRec15[2];
	double 	fRec14[3];
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT 	fslider9;
	double 	fVec6[2];
	double 	fRec13[2];
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT 	fslider10;
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fVec7[2];
	double 	fRec21[2];
	double 	fRec20[3];
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT 	fslider12;
	double 	fVec8[2];
	double 	fRec19[2];
	FAUSTFLOAT 	fbargraph3;
	double 	fRec27[2];
	double 	fRec26[3];
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fslider14;
	double 	fVec9[2];
	double 	fRec25[2];
	FAUSTFLOAT 	fbargraph4;
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, float *input0, float *output0, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "mbd";
	name = N_("MultiBand Distortion");
	groups = 0;
	description = N_("MultiBand Distortion"); // description (tooltip)
	category = N_("Distortion");       // category
	shortname = N_("MB Distortion");     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	load_ui = load_ui_f_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / double(iConst0));
	fConst2 = (3.141592653589793 / double(iConst0));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = tan((fConst2 * fslider1));
	double 	fSlow2 = (1.0 / faustpower<2>(fSlow1));
	double 	fSlow3 = (2 * (1 - fSlow2));
	double 	fSlow4 = (1.0 / fSlow1);
	double 	fSlow5 = (1 + ((fSlow4 - 1.0000000000000004) / fSlow1));
	double 	fSlow6 = (1 + ((1.0000000000000004 + fSlow4) / fSlow1));
	double 	fSlow7 = (1.0 / fSlow6);
	double 	fSlow8 = (1 + fSlow4);
	double 	fSlow9 = (0 - ((1 - fSlow4) / fSlow8));
	double 	fSlow10 = (0 - fSlow4);
	double 	fSlow11 = (1.0 / fSlow8);
	double 	fSlow12 = (2 * (0 - fSlow2));
	double 	fSlow13 = (pow(1e+01,(2 * fslider2)) / fSlow6);
	double 	fSlow14 = fslider3;
	double 	fSlow15 = tan((fConst2 * fslider4));
	double 	fSlow16 = (1.0 / faustpower<2>(fSlow15));
	double 	fSlow17 = (2 * (1 - fSlow16));
	double 	fSlow18 = (1.0 / fSlow15);
	double 	fSlow19 = (1 + ((fSlow18 - 1.0000000000000004) / fSlow15));
	double 	fSlow20 = (1 + ((1.0000000000000004 + fSlow18) / fSlow15));
	double 	fSlow21 = (1.0 / fSlow20);
	double 	fSlow22 = (1 + fSlow18);
	double 	fSlow23 = (0 - ((1 - fSlow18) / fSlow22));
	double 	fSlow24 = (1.0 / (fSlow6 * fSlow15));
	double 	fSlow25 = (0 - fSlow18);
	double 	fSlow26 = (1.0 / fSlow22);
	double 	fSlow27 = (2 * (0 - fSlow16));
	double 	fSlow28 = (pow(1e+01,(2 * fslider5)) / fSlow20);
	double 	fSlow29 = fslider6;
	double 	fSlow30 = tan((fConst2 * fslider7));
	double 	fSlow31 = (1.0 / faustpower<2>(fSlow30));
	double 	fSlow32 = (2 * (1 - fSlow31));
	double 	fSlow33 = (1.0 / fSlow30);
	double 	fSlow34 = (1 + ((fSlow33 - 1.0000000000000004) / fSlow30));
	double 	fSlow35 = (1 + ((1.0000000000000004 + fSlow33) / fSlow30));
	double 	fSlow36 = (1.0 / fSlow35);
	double 	fSlow37 = (1 + fSlow33);
	double 	fSlow38 = (0 - ((1 - fSlow33) / fSlow37));
	double 	fSlow39 = (1.0 / (fSlow20 * fSlow30));
	double 	fSlow40 = (0 - fSlow33);
	double 	fSlow41 = (1.0 / fSlow37);
	double 	fSlow42 = (2 * (0 - fSlow31));
	double 	fSlow43 = (pow(1e+01,(2 * fslider8)) / fSlow35);
	double 	fSlow44 = fslider9;
	double 	fSlow45 = tan((fConst2 * fslider10));
	double 	fSlow46 = (1.0 / faustpower<2>(fSlow45));
	double 	fSlow47 = (2 * (1 - fSlow46));
	double 	fSlow48 = (1.0 / fSlow45);
	double 	fSlow49 = (1 + ((fSlow48 - 1.0000000000000004) / fSlow45));
	double 	fSlow50 = (1 + ((1.0000000000000004 + fSlow48) / fSlow45));
	double 	fSlow51 = (1.0 / fSlow50);
	double 	fSlow52 = (1 + fSlow48);
	double 	fSlow53 = (0 - ((1 - fSlow48) / fSlow52));
	double 	fSlow54 = (1.0 / (fSlow35 * fSlow45));
	double 	fSlow55 = (0 - fSlow48);
	double 	fSlow56 = (1.0 / fSlow52);
	double 	fSlow57 = (2 * (0 - fSlow46));
	double 	fSlow58 = (pow(1e+01,(2 * fslider11)) / fSlow50);
	double 	fSlow59 = fslider12;
	double 	fSlow60 = (pow(1e+01,(2 * fslider13)) / fSlow50);
	double 	fSlow61 = fslider14;
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec5[0] = ((1e-20 * (1 - iVec0[1])) - fRec5[1]);
		double fTemp0 = ((double)input0[i] + fRec5[0]);
		fVec1[0] = fTemp0;
		fRec4[0] = ((fSlow11 * ((fSlow10 * fVec1[1]) + (fSlow4 * fVec1[0]))) + (fSlow9 * fRec4[1]));
		fRec3[0] = (fRec4[0] - (fSlow7 * ((fSlow5 * fRec3[2]) + (fSlow3 * fRec3[1]))));
		double fTemp1 = max((double)-1, min((double)1, (fSlow14 + (fSlow13 * (((fSlow2 * fRec3[0]) + (fSlow12 * fRec3[1])) + (fSlow2 * fRec3[2]))))));
		double fTemp2 = (fTemp1 * (1 - (0.3333333333333333 * faustpower<2>(fTemp1))));
		fVec2[0] = fTemp2;
		fRec2[0] = ((fVec2[0] + (0.995 * fRec2[1])) - fVec2[1]);
		double 	fRec1 = max(fConst1, fabs(fRec2[0]));
		fbargraph0 = fRec1;
		double fTemp3 = (fVec1[0] + fVec1[1]);
		fRec11[0] = ((fSlow11 * fTemp3) + (fSlow9 * fRec11[1]));
		fRec10[0] = (fRec11[0] - (fSlow7 * ((fSlow5 * fRec10[2]) + (fSlow3 * fRec10[1]))));
		double fTemp4 = (fRec10[2] + (fRec10[0] + (2 * fRec10[1])));
		fVec3[0] = (fSlow7 * fTemp4);
		fRec9[0] = ((fSlow26 * ((fSlow25 * fVec3[1]) + (fSlow24 * fTemp4))) + (fSlow23 * fRec9[1]));
		fRec8[0] = (fRec9[0] - (fSlow21 * ((fSlow19 * fRec8[2]) + (fSlow17 * fRec8[1]))));
		double fTemp5 = max((double)-1, min((double)1, (fSlow29 + (fSlow28 * (((fSlow16 * fRec8[0]) + (fSlow27 * fRec8[1])) + (fSlow16 * fRec8[2]))))));
		double fTemp6 = (fTemp5 * (1 - (0.3333333333333333 * faustpower<2>(fTemp5))));
		fVec4[0] = fTemp6;
		fRec7[0] = ((fVec4[0] + (0.995 * fRec7[1])) - fVec4[1]);
		double 	fRec6 = max(fConst1, fabs(fRec7[0]));
		fbargraph1 = fRec6;
		fRec17[0] = ((fSlow26 * fTemp3) + (fSlow23 * fRec17[1]));
		fRec16[0] = (fRec17[0] - (fSlow21 * ((fSlow19 * fRec16[2]) + (fSlow17 * fRec16[1]))));
		double fTemp7 = (fRec16[2] + (fRec16[0] + (2 * fRec16[1])));
		fVec5[0] = (fSlow21 * fTemp7);
		fRec15[0] = ((fSlow41 * ((fSlow40 * fVec5[1]) + (fSlow39 * fTemp7))) + (fSlow38 * fRec15[1]));
		fRec14[0] = (fRec15[0] - (fSlow36 * ((fSlow34 * fRec14[2]) + (fSlow32 * fRec14[1]))));
		double fTemp8 = max((double)-1, min((double)1, (fSlow44 + (fSlow43 * (((fSlow31 * fRec14[0]) + (fSlow42 * fRec14[1])) + (fSlow31 * fRec14[2]))))));
		double fTemp9 = (fTemp8 * (1 - (0.3333333333333333 * faustpower<2>(fTemp8))));
		fVec6[0] = fTemp9;
		fRec13[0] = ((fVec6[0] + (0.995 * fRec13[1])) - fVec6[1]);
		double 	fRec12 = max(fConst1, fabs(fRec13[0]));
		fbargraph2 = fRec12;
		fRec23[0] = ((fSlow41 * fTemp3) + (fSlow38 * fRec23[1]));
		fRec22[0] = (fRec23[0] - (fSlow36 * ((fSlow34 * fRec22[2]) + (fSlow32 * fRec22[1]))));
		double fTemp10 = (fRec22[2] + (fRec22[0] + (2 * fRec22[1])));
		fVec7[0] = (fSlow36 * fTemp10);
		fRec21[0] = ((fSlow56 * ((fSlow55 * fVec7[1]) + (fSlow54 * fTemp10))) + (fSlow53 * fRec21[1]));
		fRec20[0] = (fRec21[0] - (fSlow51 * ((fSlow49 * fRec20[2]) + (fSlow47 * fRec20[1]))));
		double fTemp11 = max((double)-1, min((double)1, (fSlow59 + (fSlow58 * (((fSlow46 * fRec20[0]) + (fSlow57 * fRec20[1])) + (fSlow46 * fRec20[2]))))));
		double fTemp12 = (fTemp11 * (1 - (0.3333333333333333 * faustpower<2>(fTemp11))));
		fVec8[0] = fTemp12;
		fRec19[0] = ((fVec8[0] + (0.995 * fRec19[1])) - fVec8[1]);
		double 	fRec18 = max(fConst1, fabs(fRec19[0]));
		fbargraph3 = fRec18;
		fRec27[0] = ((fSlow56 * fTemp3) + (fSlow53 * fRec27[1]));
		fRec26[0] = (fRec27[0] - (fSlow51 * ((fSlow49 * fRec26[2]) + (fSlow47 * fRec26[1]))));
		double fTemp13 = max((double)-1, min((double)1, (fSlow61 + (fSlow60 * (fRec26[2] + (fRec26[0] + (2 * fRec26[1])))))));
		double fTemp14 = (fTemp13 * (1 - (0.3333333333333333 * faustpower<2>(fTemp13))));
		fVec9[0] = fTemp14;
		fRec25[0] = ((fVec9[0] + (0.995 * fRec25[1])) - fVec9[1]);
		double 	fRec24 = max(fConst1, fabs(fRec25[0]));
		fbargraph4 = fRec24;
		output0[i] = (FAUSTFLOAT)(((((fRec25[0] + fRec19[0]) + fRec13[0]) + fRec7[0]) + fRec2[0]) * fRec0[0]);
		// post processing
		fRec25[1] = fRec25[0];
		fVec9[1] = fVec9[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec19[1] = fRec19[0];
		fVec8[1] = fVec8[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fVec7[1] = fVec7[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec13[1] = fRec13[0];
		fVec6[1] = fVec6[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec5[1] = fVec5[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fRec7[1] = fRec7[0];
		fVec4[1] = fVec4[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fVec3[1] = fVec3[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec2[1] = fRec2[0];
		fVec2[1] = fVec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fVec1[1] = fVec1[0];
		fRec5[1] = fRec5[0];
		fRec0[1] = fRec0[0];
		iVec0[1] = iVec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("mbd.Drive1","","S",N_("Amount of distortion"),&fslider13, 0.0, 0.0, 1.0, 0.01);
	reg.registerVar("mbd.Drive2","","S",N_("Amount of distortion"),&fslider11, 0.0, 0.0, 1.0, 0.01);
	reg.registerVar("mbd.Drive3","","S",N_("Amount of distortion"),&fslider8, 0.0, 0.0, 1.0, 0.01);
	reg.registerVar("mbd.Drive4","","S",N_("Amount of distortion"),&fslider5, 0.0, 0.0, 1.0, 0.01);
	reg.registerVar("mbd.Drive5","","S",N_("Amount of distortion"),&fslider2, 0.0, 0.0, 1.0, 0.01);
	reg.registerVar("mbd.Gain","","S","",&fslider0, 0.0, -4e+01, 4.0, 0.1);
	reg.registerVar("mbd.Offset1","","S",N_("Brings in even harmonics"),&fslider14, 0.0, 0.0, 0.5, 0.01);
	reg.registerVar("mbd.Offset2","","S",N_("Brings in even harmonics"),&fslider12, 0.0, 0.0, 0.5, 0.01);
	reg.registerVar("mbd.Offset3","","S",N_("Brings in even harmonics"),&fslider9, 0.0, 0.0, 0.5, 0.01);
	reg.registerVar("mbd.Offset4","","S",N_("Brings in even harmonics"),&fslider6, 0.0, 0.0, 0.5, 0.01);
	reg.registerVar("mbd.Offset5","","S",N_("Brings in even harmonics"),&fslider3, 0.0, 0.0, 0.5, 0.01);
	reg.registerVar("mbd.crossover_b1_b2",N_("Crossover B1-B2 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider10, 8e+01, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbd.crossover_b2_b3",N_("Crossover B2-B3 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider7, 2.1e+02, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbd.crossover_b3_b4",N_("Crossover B3-B4 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider4, 1.7e+03, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbd.crossover_b4_b5",N_("Crossover B4-B5 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider1, 5e+03, 2e+01, 2e+04, 1.08);
	reg.registerNonMidiFloatVar("mbd.v1",&fbargraph4, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbd.v2",&fbargraph3, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbd.v3",&fbargraph2, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbd.v4",&fbargraph1, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbd.v5",&fbargraph0, false, true, -70.0, -70.0, 4.0, 0.00001);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("mbd" "." p)

b.openHorizontalhideBox("");
b.create_master_slider(PARAM("Gain"), N_("Gain"));
b.closeBox();

b.openHorizontalBox("");
b.openVerticalBox("");

b.openTabBox("");

b.openHorizontalBox(N_("Band 1"));
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Drive1"), N_("Drive"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Offset1"), N_("Offset"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b1_b2"), N_("Low Shelf (Hz)"));
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 2"));
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Drive2"), N_("Drive"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Offset2"), N_("Offset"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b1_b2"), N_("Low (Hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b2_b3"), N_("High (hz)"));
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 3"));
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Drive3"), N_("Drive"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Offset3"), N_("Offset"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b2_b3"), N_("Low (Hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b3_b4"), N_("High (hz)"));
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 4"));
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Drive4"), N_("Drive"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Offset4"), N_("Offset"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b3_b4"), N_("Low (Hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b4_b5"), N_("High (hz)"));
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 5"));
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Drive5"), N_("Drive"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("Offset5"), N_("Offset"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b4_b5"), N_("High Shelf (Hz)"));
b.closeBox();
b.closeBox();
b.closeBox();

b.closeBox();
b.closeBox();
b.create_small_rackknob(PARAM("Gain"), N_("Gain"));
b.create_simple_meter(PARAM("v1"));
b.create_simple_meter(PARAM("v2"));
b.create_simple_meter(PARAM("v3"));
b.create_simple_meter(PARAM("v4"));
b.create_simple_meter(PARAM("v5"));
b.closeBox();


#undef PARAM
        return 0;
    }
	return -1;
}

int Dsp::load_ui_f_static(const UiBuilder& b, int form)
{
	return static_cast<Dsp*>(b.plugin)->load_ui_f(b, form);
}
PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace mbd
} // end namespace pluginlib
