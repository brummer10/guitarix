// generated from file '../src/plugins/mbdel.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace mbdel {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider0;
	double 	fConst2;
	double 	fVec0[2];
	double 	fRec5[2];
	double 	fRec4[3];
	FAUSTFLOAT 	fslider1;
	double 	fRec6[2];
	int 	IOTA;
	double 	fVec1[262144];
	double 	fConst3;
	double 	fConst4;
	FAUSTFLOAT 	fslider2;
	int 	iConst5;
	double 	fRec7[2];
	double 	fRec8[2];
	double 	fRec9[2];
	double 	fRec10[2];
	double 	fRec0[2];
	int 	iRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT 	fslider3;
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fVec2[2];
	double 	fRec16[2];
	double 	fRec15[3];
	FAUSTFLOAT 	fslider4;
	double 	fRec19[2];
	double 	fVec3[262144];
	FAUSTFLOAT 	fslider5;
	double 	fRec20[2];
	double 	fRec21[2];
	double 	fRec22[2];
	double 	fRec23[2];
	double 	fRec11[2];
	int 	iRec12[2];
	double 	fRec13[2];
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT 	fslider6;
	double 	fRec31[2];
	double 	fRec30[3];
	double 	fVec4[2];
	double 	fRec29[2];
	double 	fRec28[3];
	FAUSTFLOAT 	fslider7;
	double 	fRec32[2];
	double 	fVec5[262144];
	FAUSTFLOAT 	fslider8;
	double 	fRec33[2];
	double 	fRec34[2];
	double 	fRec35[2];
	double 	fRec36[2];
	double 	fRec24[2];
	int 	iRec25[2];
	double 	fRec26[2];
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT 	fslider9;
	double 	fRec44[2];
	double 	fRec43[3];
	double 	fVec6[2];
	double 	fRec42[2];
	double 	fRec41[3];
	FAUSTFLOAT 	fslider10;
	double 	fRec45[2];
	double 	fVec7[262144];
	FAUSTFLOAT 	fslider11;
	double 	fRec46[2];
	double 	fRec47[2];
	double 	fRec48[2];
	double 	fRec49[2];
	double 	fRec37[2];
	int 	iRec38[2];
	double 	fRec39[2];
	FAUSTFLOAT 	fbargraph3;
	double 	fRec55[2];
	double 	fRec54[3];
	FAUSTFLOAT 	fslider12;
	double 	fRec56[2];
	double 	fVec8[262144];
	FAUSTFLOAT 	fslider13;
	double 	fRec57[2];
	double 	fRec58[2];
	double 	fRec59[2];
	double 	fRec60[2];
	double 	fRec50[2];
	int 	iRec51[2];
	double 	fRec52[2];
	FAUSTFLOAT 	fbargraph4;
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef*);
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
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<262144; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<262144; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) iRec12[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<262144; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) iRec25[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec44[i] = 0;
	for (int i=0; i<3; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<3; i++) fRec41[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<262144; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) iRec38[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
	for (int i=0; i<3; i++) fRec54[i] = 0;
	for (int i=0; i<2; i++) fRec56[i] = 0;
	for (int i=0; i<262144; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec57[i] = 0;
	for (int i=0; i<2; i++) fRec58[i] = 0;
	for (int i=0; i<2; i++) fRec59[i] = 0;
	for (int i=0; i<2; i++) fRec60[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<2; i++) iRec51[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
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
	IOTA = 0;
	fConst3 = (1e+01 / double(iConst0));
	fConst4 = (0 - fConst3);
	iConst5 = (60 * iConst0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = tan((fConst2 * fslider0));
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
	double 	fSlow13 = (double(iConst5) / fslider2);
	double 	fSlow14 = tan((fConst2 * fslider3));
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
	double 	fSlow28 = (double(iConst5) / fslider5);
	double 	fSlow29 = tan((fConst2 * fslider6));
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
	double 	fSlow43 = (double(iConst5) / fslider8);
	double 	fSlow44 = tan((fConst2 * fslider9));
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
	double 	fSlow57 = (double(iConst5) / fslider11);
	double 	fSlow58 = (0.0010000000000000009 * pow(10,(0.05 * fslider12)));
	double 	fSlow59 = (double(iConst5) / fslider13);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec5[0] = ((fSlow10 * ((fSlow9 * fVec0[1]) + (fSlow3 * fVec0[0]))) + (fSlow8 * fRec5[1]));
		fRec4[0] = (fRec5[0] - (fSlow6 * ((fSlow4 * fRec4[2]) + (fSlow2 * fRec4[1]))));
		fRec6[0] = (fSlow12 + (0.999 * fRec6[1]));
		double fTemp1 = (fSlow6 * (fRec6[0] * (((fSlow1 * fRec4[0]) + (fSlow11 * fRec4[1])) + (fSlow1 * fRec4[2]))));
		fVec1[IOTA&262143] = fTemp1;
		double fTemp2 = ((int((fRec7[1] != 0.0)))?((int(((fRec8[1] > 0.0) & (fRec8[1] < 1.0))))?fRec7[1]:0):((int(((fRec8[1] == 0.0) & (fSlow13 != fRec9[1]))))?fConst3:((int(((fRec8[1] == 1.0) & (fSlow13 != fRec10[1]))))?fConst4:0)));
		fRec7[0] = fTemp2;
		fRec8[0] = max(0.0, min(1.0, (fRec8[1] + fTemp2)));
		fRec9[0] = ((int(((fRec8[1] >= 1.0) & (fRec10[1] != fSlow13))))?fSlow13:fRec9[1]);
		fRec10[0] = ((int(((fRec8[1] <= 0.0) & (fRec9[1] != fSlow13))))?fSlow13:fRec10[1]);
		double fTemp3 = ((fRec8[0] * fVec1[(IOTA-int((int(fRec10[0]) & 262143)))&262143]) + ((1.0 - fRec8[0]) * fVec1[(IOTA-int((int(fRec9[0]) & 262143)))&262143]));
		double 	fRec3 = max(fConst1, fabs(fTemp3));
		int iTemp4 = int((iRec1[1] < 4096));
		fRec0[0] = ((iTemp4)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp4)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp4)?fRec2[1]:fRec0[1]);
		fbargraph0 = fRec2[0];
		double fTemp5 = (fVec0[0] + fVec0[1]);
		fRec18[0] = ((fSlow10 * fTemp5) + (fSlow8 * fRec18[1]));
		fRec17[0] = (fRec18[0] - (fSlow6 * ((fSlow4 * fRec17[2]) + (fSlow2 * fRec17[1]))));
		double fTemp6 = (fRec17[2] + (fRec17[0] + (2 * fRec17[1])));
		fVec2[0] = (fSlow6 * fTemp6);
		fRec16[0] = ((fSlow25 * ((fSlow24 * fVec2[1]) + (fSlow23 * fTemp6))) + (fSlow22 * fRec16[1]));
		fRec15[0] = (fRec16[0] - (fSlow20 * ((fSlow18 * fRec15[2]) + (fSlow16 * fRec15[1]))));
		fRec19[0] = (fSlow27 + (0.999 * fRec19[1]));
		double fTemp7 = (fSlow20 * (fRec19[0] * (((fSlow15 * fRec15[0]) + (fSlow26 * fRec15[1])) + (fSlow15 * fRec15[2]))));
		fVec3[IOTA&262143] = fTemp7;
		double fTemp8 = ((int((fRec20[1] != 0.0)))?((int(((fRec21[1] > 0.0) & (fRec21[1] < 1.0))))?fRec20[1]:0):((int(((fRec21[1] == 0.0) & (fSlow28 != fRec22[1]))))?fConst3:((int(((fRec21[1] == 1.0) & (fSlow28 != fRec23[1]))))?fConst4:0)));
		fRec20[0] = fTemp8;
		fRec21[0] = max(0.0, min(1.0, (fRec21[1] + fTemp8)));
		fRec22[0] = ((int(((fRec21[1] >= 1.0) & (fRec23[1] != fSlow28))))?fSlow28:fRec22[1]);
		fRec23[0] = ((int(((fRec21[1] <= 0.0) & (fRec22[1] != fSlow28))))?fSlow28:fRec23[1]);
		double fTemp9 = ((fRec21[0] * fVec3[(IOTA-int((int(fRec23[0]) & 262143)))&262143]) + ((1.0 - fRec21[0]) * fVec3[(IOTA-int((int(fRec22[0]) & 262143)))&262143]));
		double 	fRec14 = max(fConst1, fabs(fTemp9));
		int iTemp10 = int((iRec12[1] < 4096));
		fRec11[0] = ((iTemp10)?max(fRec11[1], fRec14):fRec14);
		iRec12[0] = ((iTemp10)?(1 + iRec12[1]):1);
		fRec13[0] = ((iTemp10)?fRec13[1]:fRec11[1]);
		fbargraph1 = fRec13[0];
		fRec31[0] = ((fSlow25 * fTemp5) + (fSlow22 * fRec31[1]));
		fRec30[0] = (fRec31[0] - (fSlow20 * ((fSlow18 * fRec30[2]) + (fSlow16 * fRec30[1]))));
		double fTemp11 = (fRec30[2] + (fRec30[0] + (2 * fRec30[1])));
		fVec4[0] = (fSlow20 * fTemp11);
		fRec29[0] = ((fSlow40 * ((fSlow39 * fVec4[1]) + (fSlow38 * fTemp11))) + (fSlow37 * fRec29[1]));
		fRec28[0] = (fRec29[0] - (fSlow35 * ((fSlow33 * fRec28[2]) + (fSlow31 * fRec28[1]))));
		fRec32[0] = (fSlow42 + (0.999 * fRec32[1]));
		double fTemp12 = (fSlow35 * (fRec32[0] * (((fSlow30 * fRec28[0]) + (fSlow41 * fRec28[1])) + (fSlow30 * fRec28[2]))));
		fVec5[IOTA&262143] = fTemp12;
		double fTemp13 = ((int((fRec33[1] != 0.0)))?((int(((fRec34[1] > 0.0) & (fRec34[1] < 1.0))))?fRec33[1]:0):((int(((fRec34[1] == 0.0) & (fSlow43 != fRec35[1]))))?fConst3:((int(((fRec34[1] == 1.0) & (fSlow43 != fRec36[1]))))?fConst4:0)));
		fRec33[0] = fTemp13;
		fRec34[0] = max(0.0, min(1.0, (fRec34[1] + fTemp13)));
		fRec35[0] = ((int(((fRec34[1] >= 1.0) & (fRec36[1] != fSlow43))))?fSlow43:fRec35[1]);
		fRec36[0] = ((int(((fRec34[1] <= 0.0) & (fRec35[1] != fSlow43))))?fSlow43:fRec36[1]);
		double fTemp14 = ((fRec34[0] * fVec5[(IOTA-int((int(fRec36[0]) & 262143)))&262143]) + ((1.0 - fRec34[0]) * fVec5[(IOTA-int((int(fRec35[0]) & 262143)))&262143]));
		double 	fRec27 = max(fConst1, fabs(fTemp14));
		int iTemp15 = int((iRec25[1] < 4096));
		fRec24[0] = ((iTemp15)?max(fRec24[1], fRec27):fRec27);
		iRec25[0] = ((iTemp15)?(1 + iRec25[1]):1);
		fRec26[0] = ((iTemp15)?fRec26[1]:fRec24[1]);
		fbargraph2 = fRec26[0];
		fRec44[0] = ((fSlow40 * fTemp5) + (fSlow37 * fRec44[1]));
		fRec43[0] = (fRec44[0] - (fSlow35 * ((fSlow33 * fRec43[2]) + (fSlow31 * fRec43[1]))));
		double fTemp16 = (fRec43[2] + (fRec43[0] + (2 * fRec43[1])));
		fVec6[0] = (fSlow35 * fTemp16);
		fRec42[0] = ((fSlow54 * ((fSlow53 * fVec6[1]) + (fSlow52 * fTemp16))) + (fSlow51 * fRec42[1]));
		fRec41[0] = (fRec42[0] - (fSlow49 * ((fSlow48 * fRec41[2]) + (fSlow46 * fRec41[1]))));
		fRec45[0] = (fSlow56 + (0.999 * fRec45[1]));
		double fTemp17 = (fSlow49 * (fRec45[0] * (((fSlow45 * fRec41[0]) + (fSlow55 * fRec41[1])) + (fSlow45 * fRec41[2]))));
		fVec7[IOTA&262143] = fTemp17;
		double fTemp18 = ((int((fRec46[1] != 0.0)))?((int(((fRec47[1] > 0.0) & (fRec47[1] < 1.0))))?fRec46[1]:0):((int(((fRec47[1] == 0.0) & (fSlow57 != fRec48[1]))))?fConst3:((int(((fRec47[1] == 1.0) & (fSlow57 != fRec49[1]))))?fConst4:0)));
		fRec46[0] = fTemp18;
		fRec47[0] = max(0.0, min(1.0, (fRec47[1] + fTemp18)));
		fRec48[0] = ((int(((fRec47[1] >= 1.0) & (fRec49[1] != fSlow57))))?fSlow57:fRec48[1]);
		fRec49[0] = ((int(((fRec47[1] <= 0.0) & (fRec48[1] != fSlow57))))?fSlow57:fRec49[1]);
		double fTemp19 = ((fRec47[0] * fVec7[(IOTA-int((int(fRec49[0]) & 262143)))&262143]) + ((1.0 - fRec47[0]) * fVec7[(IOTA-int((int(fRec48[0]) & 262143)))&262143]));
		double 	fRec40 = max(fConst1, fabs(fTemp19));
		int iTemp20 = int((iRec38[1] < 4096));
		fRec37[0] = ((iTemp20)?max(fRec37[1], fRec40):fRec40);
		iRec38[0] = ((iTemp20)?(1 + iRec38[1]):1);
		fRec39[0] = ((iTemp20)?fRec39[1]:fRec37[1]);
		fbargraph3 = fRec39[0];
		fRec55[0] = ((fSlow54 * fTemp5) + (fSlow51 * fRec55[1]));
		fRec54[0] = (fRec55[0] - (fSlow49 * ((fSlow48 * fRec54[2]) + (fSlow46 * fRec54[1]))));
		fRec56[0] = (fSlow58 + (0.999 * fRec56[1]));
		double fTemp21 = (fSlow49 * (fRec56[0] * (fRec54[2] + (fRec54[0] + (2 * fRec54[1])))));
		fVec8[IOTA&262143] = fTemp21;
		double fTemp22 = ((int((fRec57[1] != 0.0)))?((int(((fRec58[1] > 0.0) & (fRec58[1] < 1.0))))?fRec57[1]:0):((int(((fRec58[1] == 0.0) & (fSlow59 != fRec59[1]))))?fConst3:((int(((fRec58[1] == 1.0) & (fSlow59 != fRec60[1]))))?fConst4:0)));
		fRec57[0] = fTemp22;
		fRec58[0] = max(0.0, min(1.0, (fRec58[1] + fTemp22)));
		fRec59[0] = ((int(((fRec58[1] >= 1.0) & (fRec60[1] != fSlow59))))?fSlow59:fRec59[1]);
		fRec60[0] = ((int(((fRec58[1] <= 0.0) & (fRec59[1] != fSlow59))))?fSlow59:fRec60[1]);
		double fTemp23 = ((fRec58[0] * fVec8[(IOTA-int((int(fRec60[0]) & 262143)))&262143]) + ((1.0 - fRec58[0]) * fVec8[(IOTA-int((int(fRec59[0]) & 262143)))&262143]));
		double 	fRec53 = max(fConst1, fabs(fTemp23));
		int iTemp24 = int((iRec51[1] < 4096));
		fRec50[0] = ((iTemp24)?max(fRec50[1], fRec53):fRec53);
		iRec51[0] = ((iTemp24)?(1 + iRec51[1]):1);
		fRec52[0] = ((iTemp24)?fRec52[1]:fRec50[1]);
		fbargraph4 = fRec52[0];
		output0[i] = (FAUSTFLOAT)(fTemp23 + (fTemp19 + (fTemp14 + (fTemp9 + (fVec0[0] + fTemp3)))));
		// post processing
		fRec52[1] = fRec52[0];
		iRec51[1] = iRec51[0];
		fRec50[1] = fRec50[0];
		fRec60[1] = fRec60[0];
		fRec59[1] = fRec59[0];
		fRec58[1] = fRec58[0];
		fRec57[1] = fRec57[0];
		fRec56[1] = fRec56[0];
		fRec54[2] = fRec54[1]; fRec54[1] = fRec54[0];
		fRec55[1] = fRec55[0];
		fRec39[1] = fRec39[0];
		iRec38[1] = iRec38[0];
		fRec37[1] = fRec37[0];
		fRec49[1] = fRec49[0];
		fRec48[1] = fRec48[0];
		fRec47[1] = fRec47[0];
		fRec46[1] = fRec46[0];
		fRec45[1] = fRec45[0];
		fRec41[2] = fRec41[1]; fRec41[1] = fRec41[0];
		fRec42[1] = fRec42[0];
		fVec6[1] = fVec6[0];
		fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
		fRec44[1] = fRec44[0];
		fRec26[1] = fRec26[0];
		iRec25[1] = iRec25[0];
		fRec24[1] = fRec24[0];
		fRec36[1] = fRec36[0];
		fRec35[1] = fRec35[0];
		fRec34[1] = fRec34[0];
		fRec33[1] = fRec33[0];
		fRec32[1] = fRec32[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fVec4[1] = fVec4[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fRec13[1] = fRec13[0];
		iRec12[1] = iRec12[0];
		fRec11[1] = fRec11[0];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fRec19[1] = fRec19[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fVec2[1] = fVec2[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec0[1] = fRec0[0];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		IOTA = IOTA+1;
		fRec6[1] = fRec6[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec0[1] = fVec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
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
	reg.registerNonMidiFloatVar("mbdel.v1",&fbargraph4, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbdel.v2",&fbargraph3, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbdel.v3",&fbargraph2, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbdel.v4",&fbargraph1, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbdel.v5",&fbargraph0, false, true, -70.0, -70.0, 4.0, 0.00001);
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
b.openpaintampBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("delay1"), N_("BPM"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("gain1"), N_("Gain (db)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b1_b2"), N_("Low Shelf (Hz)"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 2"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
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
b.closeBox();

b.openHorizontalBox(N_("Band 3"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
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
b.closeBox();

b.openHorizontalBox(N_("Band 4"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
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
b.closeBox();

b.openHorizontalBox(N_("Band 5"));
b.openVerticalBox("");
b.openpaintampBox("");
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
b.openVerticalBox2("Analyze");
b.create_simple_meter(PARAM("v1"));
b.create_simple_meter(PARAM("v2"));
b.create_simple_meter(PARAM("v3"));
b.create_simple_meter(PARAM("v4"));
b.create_simple_meter(PARAM("v5"));
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
