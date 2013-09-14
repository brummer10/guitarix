// generated from file '../src/plugins/mbdel.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace mbdel {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	int 	iConst0;
	double 	fConst1;
	double 	fVec0[2];
	double 	fRec1[2];
	double 	fRec0[3];
	FAUSTFLOAT 	fslider1;
	double 	fRec2[2];
	int 	IOTA;
	double 	fVec1[262144];
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider2;
	int 	iConst4;
	double 	fRec3[2];
	double 	fRec4[2];
	double 	fRec5[2];
	double 	fRec6[2];
	FAUSTFLOAT 	fslider3;
	double 	fRec10[2];
	double 	fRec9[3];
	double 	fVec2[2];
	double 	fRec8[2];
	double 	fRec7[3];
	FAUSTFLOAT 	fslider4;
	double 	fRec11[2];
	double 	fVec3[262144];
	FAUSTFLOAT 	fslider5;
	double 	fRec12[2];
	double 	fRec13[2];
	double 	fRec14[2];
	double 	fRec15[2];
	FAUSTFLOAT 	fslider6;
	double 	fRec19[2];
	double 	fRec18[3];
	double 	fVec4[2];
	double 	fRec17[2];
	double 	fRec16[3];
	FAUSTFLOAT 	fslider7;
	double 	fRec20[2];
	double 	fVec5[262144];
	FAUSTFLOAT 	fslider8;
	double 	fRec21[2];
	double 	fRec22[2];
	double 	fRec23[2];
	double 	fRec24[2];
	FAUSTFLOAT 	fslider9;
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fVec6[2];
	double 	fRec26[2];
	double 	fRec25[3];
	FAUSTFLOAT 	fslider10;
	double 	fRec29[2];
	double 	fVec7[262144];
	FAUSTFLOAT 	fslider11;
	double 	fRec30[2];
	double 	fRec31[2];
	double 	fRec32[2];
	double 	fRec33[2];
	double 	fRec35[2];
	double 	fRec34[3];
	FAUSTFLOAT 	fslider12;
	double 	fRec36[2];
	double 	fVec8[262144];
	FAUSTFLOAT 	fslider13;
	double 	fRec37[2];
	double 	fRec38[2];
	double 	fRec39[2];
	double 	fRec40[2];
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
	id = "mbdel";
	name = N_("MultiBand Delay");
	groups = 0;
	description = N_("Multi Band Delay"); // description (tooltip)
	category = N_("Echo / Delay");       // category
	shortname = N_("MB Delay");     // shortname
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
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<262144; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<262144; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<262144; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<262144; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<3; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<262144; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (3.141592653589793 / double(iConst0));
	IOTA = 0;
	fConst2 = (1e+01 / double(iConst0));
	fConst3 = (0 - fConst2);
	iConst4 = (60 * iConst0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = tan((fConst1 * fslider0));
	double 	fSlow1 = (1.0 / faustpower<2>(fSlow0));
	double 	fSlow2 = (2 * (1 - fSlow1));
	double 	fSlow3 = (1.0 / fSlow0);
	double 	fSlow4 = (1 + ((fSlow3 - 1.0000000000000004) / fSlow0));
	double 	fSlow5 = (1 + ((1.0000000000000004 + fSlow3) / fSlow0));
	double 	fSlow6 = (1.0 / fSlow5);
	double 	fSlow7 = (1 + fSlow3);
	double 	fSlow8 = (0 - ((1 - fSlow3) / fSlow7));
	double 	fSlow9 = (0 - fSlow3);
	double 	fSlow10 = (1.0 / fSlow7);
	double 	fSlow11 = (2 * (0 - fSlow1));
	double 	fSlow12 = (0.0010000000000000009 * pow(10,(0.05 * fslider1)));
	double 	fSlow13 = (double(iConst4) / fslider2);
	double 	fSlow14 = tan((fConst1 * fslider3));
	double 	fSlow15 = (1.0 / faustpower<2>(fSlow14));
	double 	fSlow16 = (2 * (1 - fSlow15));
	double 	fSlow17 = (1.0 / fSlow14);
	double 	fSlow18 = (1 + ((fSlow17 - 1.0000000000000004) / fSlow14));
	double 	fSlow19 = (1 + ((1.0000000000000004 + fSlow17) / fSlow14));
	double 	fSlow20 = (1.0 / fSlow19);
	double 	fSlow21 = (1 + fSlow17);
	double 	fSlow22 = (0 - ((1 - fSlow17) / fSlow21));
	double 	fSlow23 = (1.0 / (fSlow5 * fSlow14));
	double 	fSlow24 = (0 - fSlow17);
	double 	fSlow25 = (1.0 / fSlow21);
	double 	fSlow26 = (2 * (0 - fSlow15));
	double 	fSlow27 = (0.0010000000000000009 * pow(10,(0.05 * fslider4)));
	double 	fSlow28 = (double(iConst4) / fslider5);
	double 	fSlow29 = tan((fConst1 * fslider6));
	double 	fSlow30 = (1.0 / faustpower<2>(fSlow29));
	double 	fSlow31 = (2 * (1 - fSlow30));
	double 	fSlow32 = (1.0 / fSlow29);
	double 	fSlow33 = (1 + ((fSlow32 - 1.0000000000000004) / fSlow29));
	double 	fSlow34 = (1 + ((1.0000000000000004 + fSlow32) / fSlow29));
	double 	fSlow35 = (1.0 / fSlow34);
	double 	fSlow36 = (1 + fSlow32);
	double 	fSlow37 = (0 - ((1 - fSlow32) / fSlow36));
	double 	fSlow38 = (1.0 / (fSlow19 * fSlow29));
	double 	fSlow39 = (0 - fSlow32);
	double 	fSlow40 = (1.0 / fSlow36);
	double 	fSlow41 = (2 * (0 - fSlow30));
	double 	fSlow42 = (0.0010000000000000009 * pow(10,(0.05 * fslider7)));
	double 	fSlow43 = (double(iConst4) / fslider8);
	double 	fSlow44 = tan((fConst1 * fslider9));
	double 	fSlow45 = (1.0 / faustpower<2>(fSlow44));
	double 	fSlow46 = (2 * (1 - fSlow45));
	double 	fSlow47 = (1.0 / fSlow44);
	double 	fSlow48 = (1 + ((fSlow47 - 1.0000000000000004) / fSlow44));
	double 	fSlow49 = (1.0 / (1 + ((1.0000000000000004 + fSlow47) / fSlow44)));
	double 	fSlow50 = (1 + fSlow47);
	double 	fSlow51 = (0 - ((1 - fSlow47) / fSlow50));
	double 	fSlow52 = (1.0 / (fSlow34 * fSlow44));
	double 	fSlow53 = (0 - fSlow47);
	double 	fSlow54 = (1.0 / fSlow50);
	double 	fSlow55 = (2 * (0 - fSlow45));
	double 	fSlow56 = (0.0010000000000000009 * pow(10,(0.05 * fslider10)));
	double 	fSlow57 = (double(iConst4) / fslider11);
	double 	fSlow58 = (0.0010000000000000009 * pow(10,(0.05 * fslider12)));
	double 	fSlow59 = (double(iConst4) / fslider13);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec1[0] = ((fSlow10 * ((fSlow9 * fVec0[1]) + (fSlow3 * fVec0[0]))) + (fSlow8 * fRec1[1]));
		fRec0[0] = (fRec1[0] - (fSlow6 * ((fSlow4 * fRec0[2]) + (fSlow2 * fRec0[1]))));
		fRec2[0] = (fSlow12 + (0.999 * fRec2[1]));
		double fTemp1 = (fSlow6 * (fRec2[0] * (((fSlow1 * fRec0[0]) + (fSlow11 * fRec0[1])) + (fSlow1 * fRec0[2]))));
		fVec1[IOTA&262143] = fTemp1;
		double fTemp2 = ((int((fRec3[1] != 0.0)))?((int(((fRec4[1] > 0.0) & (fRec4[1] < 1.0))))?fRec3[1]:0):((int(((fRec4[1] == 0.0) & (fSlow13 != fRec5[1]))))?fConst2:((int(((fRec4[1] == 1.0) & (fSlow13 != fRec6[1]))))?fConst3:0)));
		fRec3[0] = fTemp2;
		fRec4[0] = max(0.0, min(1.0, (fRec4[1] + fTemp2)));
		fRec5[0] = ((int(((fRec4[1] >= 1.0) & (fRec6[1] != fSlow13))))?fSlow13:fRec5[1]);
		fRec6[0] = ((int(((fRec4[1] <= 0.0) & (fRec5[1] != fSlow13))))?fSlow13:fRec6[1]);
		double fTemp3 = (fVec0[0] + fVec0[1]);
		fRec10[0] = ((fSlow10 * fTemp3) + (fSlow8 * fRec10[1]));
		fRec9[0] = (fRec10[0] - (fSlow6 * ((fSlow4 * fRec9[2]) + (fSlow2 * fRec9[1]))));
		double fTemp4 = (fRec9[2] + (fRec9[0] + (2 * fRec9[1])));
		fVec2[0] = (fSlow6 * fTemp4);
		fRec8[0] = ((fSlow25 * ((fSlow24 * fVec2[1]) + (fSlow23 * fTemp4))) + (fSlow22 * fRec8[1]));
		fRec7[0] = (fRec8[0] - (fSlow20 * ((fSlow18 * fRec7[2]) + (fSlow16 * fRec7[1]))));
		fRec11[0] = (fSlow27 + (0.999 * fRec11[1]));
		double fTemp5 = (fSlow20 * (fRec11[0] * (((fSlow15 * fRec7[0]) + (fSlow26 * fRec7[1])) + (fSlow15 * fRec7[2]))));
		fVec3[IOTA&262143] = fTemp5;
		double fTemp6 = ((int((fRec12[1] != 0.0)))?((int(((fRec13[1] > 0.0) & (fRec13[1] < 1.0))))?fRec12[1]:0):((int(((fRec13[1] == 0.0) & (fSlow28 != fRec14[1]))))?fConst2:((int(((fRec13[1] == 1.0) & (fSlow28 != fRec15[1]))))?fConst3:0)));
		fRec12[0] = fTemp6;
		fRec13[0] = max(0.0, min(1.0, (fRec13[1] + fTemp6)));
		fRec14[0] = ((int(((fRec13[1] >= 1.0) & (fRec15[1] != fSlow28))))?fSlow28:fRec14[1]);
		fRec15[0] = ((int(((fRec13[1] <= 0.0) & (fRec14[1] != fSlow28))))?fSlow28:fRec15[1]);
		fRec19[0] = ((fSlow25 * fTemp3) + (fSlow22 * fRec19[1]));
		fRec18[0] = (fRec19[0] - (fSlow20 * ((fSlow18 * fRec18[2]) + (fSlow16 * fRec18[1]))));
		double fTemp7 = (fRec18[2] + (fRec18[0] + (2 * fRec18[1])));
		fVec4[0] = (fSlow20 * fTemp7);
		fRec17[0] = ((fSlow40 * ((fSlow39 * fVec4[1]) + (fSlow38 * fTemp7))) + (fSlow37 * fRec17[1]));
		fRec16[0] = (fRec17[0] - (fSlow35 * ((fSlow33 * fRec16[2]) + (fSlow31 * fRec16[1]))));
		fRec20[0] = (fSlow42 + (0.999 * fRec20[1]));
		double fTemp8 = (fSlow35 * (fRec20[0] * (((fSlow30 * fRec16[0]) + (fSlow41 * fRec16[1])) + (fSlow30 * fRec16[2]))));
		fVec5[IOTA&262143] = fTemp8;
		double fTemp9 = ((int((fRec21[1] != 0.0)))?((int(((fRec22[1] > 0.0) & (fRec22[1] < 1.0))))?fRec21[1]:0):((int(((fRec22[1] == 0.0) & (fSlow43 != fRec23[1]))))?fConst2:((int(((fRec22[1] == 1.0) & (fSlow43 != fRec24[1]))))?fConst3:0)));
		fRec21[0] = fTemp9;
		fRec22[0] = max(0.0, min(1.0, (fRec22[1] + fTemp9)));
		fRec23[0] = ((int(((fRec22[1] >= 1.0) & (fRec24[1] != fSlow43))))?fSlow43:fRec23[1]);
		fRec24[0] = ((int(((fRec22[1] <= 0.0) & (fRec23[1] != fSlow43))))?fSlow43:fRec24[1]);
		fRec28[0] = ((fSlow40 * fTemp3) + (fSlow37 * fRec28[1]));
		fRec27[0] = (fRec28[0] - (fSlow35 * ((fSlow33 * fRec27[2]) + (fSlow31 * fRec27[1]))));
		double fTemp10 = (fRec27[2] + (fRec27[0] + (2 * fRec27[1])));
		fVec6[0] = (fSlow35 * fTemp10);
		fRec26[0] = ((fSlow54 * ((fSlow53 * fVec6[1]) + (fSlow52 * fTemp10))) + (fSlow51 * fRec26[1]));
		fRec25[0] = (fRec26[0] - (fSlow49 * ((fSlow48 * fRec25[2]) + (fSlow46 * fRec25[1]))));
		fRec29[0] = (fSlow56 + (0.999 * fRec29[1]));
		double fTemp11 = (fSlow49 * (fRec29[0] * (((fSlow45 * fRec25[0]) + (fSlow55 * fRec25[1])) + (fSlow45 * fRec25[2]))));
		fVec7[IOTA&262143] = fTemp11;
		double fTemp12 = ((int((fRec30[1] != 0.0)))?((int(((fRec31[1] > 0.0) & (fRec31[1] < 1.0))))?fRec30[1]:0):((int(((fRec31[1] == 0.0) & (fSlow57 != fRec32[1]))))?fConst2:((int(((fRec31[1] == 1.0) & (fSlow57 != fRec33[1]))))?fConst3:0)));
		fRec30[0] = fTemp12;
		fRec31[0] = max(0.0, min(1.0, (fRec31[1] + fTemp12)));
		fRec32[0] = ((int(((fRec31[1] >= 1.0) & (fRec33[1] != fSlow57))))?fSlow57:fRec32[1]);
		fRec33[0] = ((int(((fRec31[1] <= 0.0) & (fRec32[1] != fSlow57))))?fSlow57:fRec33[1]);
		fRec35[0] = ((fSlow54 * fTemp3) + (fSlow51 * fRec35[1]));
		fRec34[0] = (fRec35[0] - (fSlow49 * ((fSlow48 * fRec34[2]) + (fSlow46 * fRec34[1]))));
		fRec36[0] = (fSlow58 + (0.999 * fRec36[1]));
		double fTemp13 = (fSlow49 * (fRec36[0] * (fRec34[2] + (fRec34[0] + (2 * fRec34[1])))));
		fVec8[IOTA&262143] = fTemp13;
		double fTemp14 = ((int((fRec37[1] != 0.0)))?((int(((fRec38[1] > 0.0) & (fRec38[1] < 1.0))))?fRec37[1]:0):((int(((fRec38[1] == 0.0) & (fSlow59 != fRec39[1]))))?fConst2:((int(((fRec38[1] == 1.0) & (fSlow59 != fRec40[1]))))?fConst3:0)));
		fRec37[0] = fTemp14;
		fRec38[0] = max(0.0, min(1.0, (fRec38[1] + fTemp14)));
		fRec39[0] = ((int(((fRec38[1] >= 1.0) & (fRec40[1] != fSlow59))))?fSlow59:fRec39[1]);
		fRec40[0] = ((int(((fRec38[1] <= 0.0) & (fRec39[1] != fSlow59))))?fSlow59:fRec40[1]);
		output0[i] = (FAUSTFLOAT)(((1.0 - fRec38[0]) * fVec8[(IOTA-int((int(fRec39[0]) & 262143)))&262143]) + ((fRec38[0] * fVec8[(IOTA-int((int(fRec40[0]) & 262143)))&262143]) + (((1.0 - fRec31[0]) * fVec7[(IOTA-int((int(fRec32[0]) & 262143)))&262143]) + ((fRec31[0] * fVec7[(IOTA-int((int(fRec33[0]) & 262143)))&262143]) + (((1.0 - fRec22[0]) * fVec5[(IOTA-int((int(fRec23[0]) & 262143)))&262143]) + ((fRec22[0] * fVec5[(IOTA-int((int(fRec24[0]) & 262143)))&262143]) + (((1.0 - fRec13[0]) * fVec3[(IOTA-int((int(fRec14[0]) & 262143)))&262143]) + ((fRec13[0] * fVec3[(IOTA-int((int(fRec15[0]) & 262143)))&262143]) + (((1.0 - fRec4[0]) * fVec1[(IOTA-int((int(fRec5[0]) & 262143)))&262143]) + (fVec0[0] + (fRec4[0] * fVec1[(IOTA-int((int(fRec6[0]) & 262143)))&262143])))))))))));
		// post processing
		fRec40[1] = fRec40[0];
		fRec39[1] = fRec39[0];
		fRec38[1] = fRec38[0];
		fRec37[1] = fRec37[0];
		fRec36[1] = fRec36[0];
		fRec34[2] = fRec34[1]; fRec34[1] = fRec34[0];
		fRec35[1] = fRec35[0];
		fRec33[1] = fRec33[0];
		fRec32[1] = fRec32[0];
		fRec31[1] = fRec31[0];
		fRec30[1] = fRec30[0];
		fRec29[1] = fRec29[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fVec6[1] = fVec6[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec24[1] = fRec24[0];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fVec4[1] = fVec4[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fRec15[1] = fRec15[0];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fVec2[1] = fVec2[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		IOTA = IOTA+1;
		fRec2[1] = fRec2[0];
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fVec0[1] = fVec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("mbdel.crossover_b1_b2",N_("Crossover B1-B2 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider9, 8e+01, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbdel.crossover_b2_b3",N_("Crossover B2-B3 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider6, 2.1e+02, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbdel.crossover_b3_b4",N_("Crossover B3-B4 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider3, 1.7e+03, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbdel.crossover_b4_b5",N_("Crossover B4-B5 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider0, 5e+03, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbdel.delay1","","S",N_("Delay in Beats per Minute"),&fslider13, 3e+01, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbdel.delay2","","S",N_("Delay in Beats per Minute"),&fslider11, 6e+01, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbdel.delay3","","S",N_("Delay in Beats per Minute"),&fslider8, 9e+01, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbdel.delay4","","S",N_("Delay in Beats per Minute"),&fslider5, 1.2e+02, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbdel.delay5","","S",N_("Delay in Beats per Minute"),&fslider2, 1.5e+02, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbdel.gain1","","S","",&fslider12, -1e+01, -2e+01, 2e+01, 0.1);
	reg.registerVar("mbdel.gain2","","S","",&fslider10, -5.0, -2e+01, 2e+01, 0.1);
	reg.registerVar("mbdel.gain3","","S","",&fslider7, -2.0, -2e+01, 2e+01, 0.1);
	reg.registerVar("mbdel.gain4","","S","",&fslider4, 0.0, -2e+01, 2e+01, 0.1);
	reg.registerVar("mbdel.gain5","","S","",&fslider1, -1e+01, -2e+01, 2e+01, 0.1);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("mbdel" "." p)

b.openHorizontalhideBox("");
b.closeBox();

b.openHorizontalBox("");
b.openVerticalBox("");

b.openTabBox("");

b.openHorizontalBox(N_("Band 1"));
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("delay1"), N_("BPM"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("gain1"), N_("Gain (db)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b1_b2"), N_("Low Shelf (Hz)"));
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 2"));
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("delay2"), N_("BPM"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("gain2"), N_("Gain (db)"));
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
b.create_small_rackknob(PARAM("delay3"), N_("BPM"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("gain3"), N_("Gain (db)"));
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
b.create_small_rackknob(PARAM("delay4"), N_("BPM"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("gain4"), N_("Gain (db)"));
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
b.create_small_rackknob(PARAM("delay5"), N_("BPM"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("gain5"), N_("Gain (db)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b4_b5"), N_("High Shelf (Hz)"));
b.closeBox();
b.closeBox();
b.closeBox();

b.closeBox();
b.closeBox();
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

} // end namespace mbdel
} // end namespace pluginlib
