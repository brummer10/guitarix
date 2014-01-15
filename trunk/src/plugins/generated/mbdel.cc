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
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	double 	fVec0[2];
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fVec1[2];
	double 	fRec9[2];
	double 	fRec8[3];
	double 	fVec2[2];
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fVec3[2];
	double 	fRec5[2];
	double 	fRec4[3];
	FAUSTFLOAT 	fslider4;
	double 	fRec12[2];
	int 	IOTA;
	double 	fVec4[262144];
	double 	fConst3;
	double 	fConst4;
	FAUSTFLOAT 	fslider5;
	int 	iConst5;
	double 	fRec13[2];
	double 	fRec14[2];
	double 	fRec15[2];
	double 	fRec16[2];
	double 	fRec0[2];
	int 	iRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph0;
	double 	fRec22[2];
	double 	fRec21[3];
	FAUSTFLOAT 	fslider6;
	double 	fRec23[2];
	double 	fVec5[262144];
	FAUSTFLOAT 	fslider7;
	double 	fRec24[2];
	double 	fRec25[2];
	double 	fRec26[2];
	double 	fRec27[2];
	double 	fRec17[2];
	int 	iRec18[2];
	double 	fRec19[2];
	FAUSTFLOAT 	fbargraph1;
	double 	fRec34[2];
	double 	fRec33[3];
	double 	fRec32[3];
	FAUSTFLOAT 	fslider8;
	double 	fRec35[2];
	double 	fVec6[262144];
	FAUSTFLOAT 	fslider9;
	double 	fRec36[2];
	double 	fRec37[2];
	double 	fRec38[2];
	double 	fRec39[2];
	double 	fRec28[2];
	int 	iRec29[2];
	double 	fRec30[2];
	FAUSTFLOAT 	fbargraph2;
	double 	fRec47[2];
	double 	fRec46[3];
	double 	fRec45[3];
	double 	fRec44[3];
	FAUSTFLOAT 	fslider10;
	double 	fRec48[2];
	double 	fVec7[262144];
	FAUSTFLOAT 	fslider11;
	double 	fRec49[2];
	double 	fRec50[2];
	double 	fRec51[2];
	double 	fRec52[2];
	double 	fRec40[2];
	int 	iRec41[2];
	double 	fRec42[2];
	FAUSTFLOAT 	fbargraph3;
	double 	fRec61[2];
	double 	fRec60[3];
	double 	fRec59[3];
	double 	fRec58[3];
	double 	fRec57[3];
	FAUSTFLOAT 	fslider12;
	double 	fRec62[2];
	double 	fVec8[262144];
	FAUSTFLOAT 	fslider13;
	double 	fRec63[2];
	double 	fRec64[2];
	double 	fRec65[2];
	double 	fRec66[2];
	double 	fRec53[2];
	int 	iRec54[2];
	double 	fRec55[2];
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
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<262144; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<262144; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) iRec18[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<3; i++) fRec33[i] = 0;
	for (int i=0; i<3; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<262144; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) iRec29[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<3; i++) fRec46[i] = 0;
	for (int i=0; i<3; i++) fRec45[i] = 0;
	for (int i=0; i<3; i++) fRec44[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<262144; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) iRec41[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec61[i] = 0;
	for (int i=0; i<3; i++) fRec60[i] = 0;
	for (int i=0; i<3; i++) fRec59[i] = 0;
	for (int i=0; i<3; i++) fRec58[i] = 0;
	for (int i=0; i<3; i++) fRec57[i] = 0;
	for (int i=0; i<2; i++) fRec62[i] = 0;
	for (int i=0; i<262144; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec63[i] = 0;
	for (int i=0; i<2; i++) fRec64[i] = 0;
	for (int i=0; i<2; i++) fRec65[i] = 0;
	for (int i=0; i<2; i++) fRec66[i] = 0;
	for (int i=0; i<2; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) iRec54[i] = 0;
	for (int i=0; i<2; i++) fRec55[i] = 0;
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
	double 	fSlow5 = (1.0 / (1 + ((fSlow3 + 1.0000000000000004) / fSlow0)));
	double 	fSlow6 = (1 + fSlow3);
	double 	fSlow7 = (0 - ((1 - fSlow3) / fSlow6));
	double 	fSlow8 = tan((fConst2 * fslider1));
	double 	fSlow9 = (1.0 / faustpower<2>(fSlow8));
	double 	fSlow10 = (2 * (1 - fSlow9));
	double 	fSlow11 = (1.0 / fSlow8);
	double 	fSlow12 = (1 + ((fSlow11 - 1.0000000000000004) / fSlow8));
	double 	fSlow13 = (1 + ((fSlow11 + 1.0000000000000004) / fSlow8));
	double 	fSlow14 = (1.0 / fSlow13);
	double 	fSlow15 = (1 + fSlow11);
	double 	fSlow16 = (0 - ((1 - fSlow11) / fSlow15));
	double 	fSlow17 = tan((fConst2 * fslider2));
	double 	fSlow18 = (1.0 / faustpower<2>(fSlow17));
	double 	fSlow19 = (2 * (1 - fSlow18));
	double 	fSlow20 = (1.0 / fSlow17);
	double 	fSlow21 = (1 + ((fSlow20 - 1.0000000000000004) / fSlow17));
	double 	fSlow22 = (1 + ((fSlow20 + 1.0000000000000004) / fSlow17));
	double 	fSlow23 = (1.0 / fSlow22);
	double 	fSlow24 = (1 + fSlow20);
	double 	fSlow25 = (0 - ((1 - fSlow20) / fSlow24));
	double 	fSlow26 = tan((fConst2 * fslider3));
	double 	fSlow27 = (1.0 / faustpower<2>(fSlow26));
	double 	fSlow28 = (2 * (1 - fSlow27));
	double 	fSlow29 = (1.0 / fSlow26);
	double 	fSlow30 = (1 + ((fSlow29 - 1.0000000000000004) / fSlow26));
	double 	fSlow31 = (1 + ((1.0000000000000004 + fSlow29) / fSlow26));
	double 	fSlow32 = (1.0 / fSlow31);
	double 	fSlow33 = (1 + fSlow29);
	double 	fSlow34 = (0 - ((1 - fSlow29) / fSlow33));
	double 	fSlow35 = (1.0 / fSlow33);
	double 	fSlow36 = (1.0 / fSlow24);
	double 	fSlow37 = (1.0 / fSlow15);
	double 	fSlow38 = (1.0 / fSlow6);
	double 	fSlow39 = (0.0010000000000000009 * pow(10,(0.05 * fslider4)));
	double 	fSlow40 = (double(iConst5) / fslider5);
	double 	fSlow41 = (1.0 / (fSlow0 * fSlow13));
	double 	fSlow42 = (0 - fSlow3);
	double 	fSlow43 = (2 * (0 - fSlow1));
	double 	fSlow44 = (0.0010000000000000009 * pow(10,(0.05 * fslider6)));
	double 	fSlow45 = (double(iConst5) / fslider7);
	double 	fSlow46 = (1 + ((fSlow3 - 1.0) / fSlow0));
	double 	fSlow47 = (1.0 / (1 + ((1.0 + fSlow3) / fSlow0)));
	double 	fSlow48 = (1.0 / (fSlow8 * fSlow22));
	double 	fSlow49 = (0 - fSlow11);
	double 	fSlow50 = (2 * (0 - fSlow9));
	double 	fSlow51 = (0.0010000000000000009 * pow(10,(0.05 * fslider8)));
	double 	fSlow52 = (double(iConst5) / fslider9);
	double 	fSlow53 = (1 + ((fSlow11 - 1.0) / fSlow8));
	double 	fSlow54 = (1.0 / (1 + ((1.0 + fSlow11) / fSlow8)));
	double 	fSlow55 = (1.0 / (fSlow17 * fSlow31));
	double 	fSlow56 = (0 - fSlow20);
	double 	fSlow57 = (2 * (0 - fSlow18));
	double 	fSlow58 = (0.0010000000000000009 * pow(10,(0.05 * fslider10)));
	double 	fSlow59 = (double(iConst5) / fslider11);
	double 	fSlow60 = (1 + ((fSlow20 - 1.0) / fSlow17));
	double 	fSlow61 = (1.0 / (1 + ((1.0 + fSlow20) / fSlow17)));
	double 	fSlow62 = (0 - fSlow29);
	double 	fSlow63 = (2 * (0 - fSlow27));
	double 	fSlow64 = (0.0010000000000000009 * pow(10,(0.05 * fslider12)));
	double 	fSlow65 = (double(iConst5) / fslider13);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec11[0] = ((fSlow35 * (fVec0[0] + fVec0[1])) + (fSlow34 * fRec11[1]));
		fRec10[0] = (fRec11[0] - (fSlow32 * ((fSlow30 * fRec10[2]) + (fSlow28 * fRec10[1]))));
		double fTemp1 = (fRec10[2] + (fRec10[0] + (2 * fRec10[1])));
		double fTemp2 = (fSlow32 * fTemp1);
		fVec1[0] = fTemp2;
		fRec9[0] = ((fSlow36 * (fVec1[0] + fVec1[1])) + (fSlow25 * fRec9[1]));
		fRec8[0] = (fRec9[0] - (fSlow23 * ((fSlow21 * fRec8[2]) + (fSlow19 * fRec8[1]))));
		double fTemp3 = (fRec8[2] + (fRec8[0] + (2 * fRec8[1])));
		double fTemp4 = (fSlow23 * fTemp3);
		fVec2[0] = fTemp4;
		fRec7[0] = ((fSlow37 * (fVec2[0] + fVec2[1])) + (fSlow16 * fRec7[1]));
		fRec6[0] = (fRec7[0] - (fSlow14 * ((fSlow12 * fRec6[2]) + (fSlow10 * fRec6[1]))));
		double fTemp5 = (fRec6[2] + (fRec6[0] + (2 * fRec6[1])));
		double fTemp6 = (fSlow14 * fTemp5);
		fVec3[0] = fTemp6;
		fRec5[0] = ((fSlow38 * (fVec3[0] + fVec3[1])) + (fSlow7 * fRec5[1]));
		fRec4[0] = (fRec5[0] - (fSlow5 * ((fSlow4 * fRec4[2]) + (fSlow2 * fRec4[1]))));
		fRec12[0] = (fSlow39 + (0.999 * fRec12[1]));
		double fTemp7 = (fSlow5 * (fRec12[0] * (fRec4[2] + (fRec4[0] + (2 * fRec4[1])))));
		fVec4[IOTA&262143] = fTemp7;
		double fTemp8 = ((int((fRec13[1] != 0.0)))?((int(((fRec14[1] > 0.0) & (fRec14[1] < 1.0))))?fRec13[1]:0):((int(((fRec14[1] == 0.0) & (fSlow40 != fRec15[1]))))?fConst3:((int(((fRec14[1] == 1.0) & (fSlow40 != fRec16[1]))))?fConst4:0)));
		fRec13[0] = fTemp8;
		fRec14[0] = max(0.0, min(1.0, (fRec14[1] + fTemp8)));
		fRec15[0] = ((int(((fRec14[1] >= 1.0) & (fRec16[1] != fSlow40))))?fSlow40:fRec15[1]);
		fRec16[0] = ((int(((fRec14[1] <= 0.0) & (fRec15[1] != fSlow40))))?fSlow40:fRec16[1]);
		double fTemp9 = ((fRec14[0] * fVec4[(IOTA-int((int(fRec16[0]) & 262143)))&262143]) + ((1.0 - fRec14[0]) * fVec4[(IOTA-int((int(fRec15[0]) & 262143)))&262143]));
		double 	fRec3 = max(fConst1, fabs(fTemp9));
		int iTemp10 = int((iRec1[1] < 4096));
		fRec0[0] = ((iTemp10)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp10)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp10)?fRec2[1]:fRec0[1]);
		fbargraph0 = fRec2[0];
		fRec22[0] = ((fSlow38 * ((fSlow42 * fVec3[1]) + (fSlow41 * fTemp5))) + (fSlow7 * fRec22[1]));
		fRec21[0] = (fRec22[0] - (fSlow5 * ((fSlow4 * fRec21[2]) + (fSlow2 * fRec21[1]))));
		fRec23[0] = (fSlow44 + (0.999 * fRec23[1]));
		double fTemp11 = (fSlow5 * (fRec23[0] * (((fSlow1 * fRec21[0]) + (fSlow43 * fRec21[1])) + (fSlow1 * fRec21[2]))));
		fVec5[IOTA&262143] = fTemp11;
		double fTemp12 = ((int((fRec24[1] != 0.0)))?((int(((fRec25[1] > 0.0) & (fRec25[1] < 1.0))))?fRec24[1]:0):((int(((fRec25[1] == 0.0) & (fSlow45 != fRec26[1]))))?fConst3:((int(((fRec25[1] == 1.0) & (fSlow45 != fRec27[1]))))?fConst4:0)));
		fRec24[0] = fTemp12;
		fRec25[0] = max(0.0, min(1.0, (fRec25[1] + fTemp12)));
		fRec26[0] = ((int(((fRec25[1] >= 1.0) & (fRec27[1] != fSlow45))))?fSlow45:fRec26[1]);
		fRec27[0] = ((int(((fRec25[1] <= 0.0) & (fRec26[1] != fSlow45))))?fSlow45:fRec27[1]);
		double fTemp13 = ((fRec25[0] * fVec5[(IOTA-int((int(fRec27[0]) & 262143)))&262143]) + ((1.0 - fRec25[0]) * fVec5[(IOTA-int((int(fRec26[0]) & 262143)))&262143]));
		double 	fRec20 = max(fConst1, fabs(fTemp13));
		int iTemp14 = int((iRec18[1] < 4096));
		fRec17[0] = ((iTemp14)?max(fRec17[1], fRec20):fRec20);
		iRec18[0] = ((iTemp14)?(1 + iRec18[1]):1);
		fRec19[0] = ((iTemp14)?fRec19[1]:fRec17[1]);
		fbargraph1 = fRec19[0];
		double fTemp15 = (fSlow2 * fRec32[1]);
		fRec34[0] = ((fSlow37 * ((fSlow49 * fVec2[1]) + (fSlow48 * fTemp3))) + (fSlow16 * fRec34[1]));
		fRec33[0] = (fRec34[0] - (fSlow14 * ((fSlow12 * fRec33[2]) + (fSlow10 * fRec33[1]))));
		fRec32[0] = ((fSlow14 * (((fSlow9 * fRec33[0]) + (fSlow50 * fRec33[1])) + (fSlow9 * fRec33[2]))) - (fSlow47 * ((fSlow46 * fRec32[2]) + fTemp15)));
		fRec35[0] = (fSlow51 + (0.999 * fRec35[1]));
		double fTemp16 = (fRec35[0] * (fRec32[2] + (fSlow47 * (fTemp15 + (fSlow46 * fRec32[0])))));
		fVec6[IOTA&262143] = fTemp16;
		double fTemp17 = ((int((fRec36[1] != 0.0)))?((int(((fRec37[1] > 0.0) & (fRec37[1] < 1.0))))?fRec36[1]:0):((int(((fRec37[1] == 0.0) & (fSlow52 != fRec38[1]))))?fConst3:((int(((fRec37[1] == 1.0) & (fSlow52 != fRec39[1]))))?fConst4:0)));
		fRec36[0] = fTemp17;
		fRec37[0] = max(0.0, min(1.0, (fRec37[1] + fTemp17)));
		fRec38[0] = ((int(((fRec37[1] >= 1.0) & (fRec39[1] != fSlow52))))?fSlow52:fRec38[1]);
		fRec39[0] = ((int(((fRec37[1] <= 0.0) & (fRec38[1] != fSlow52))))?fSlow52:fRec39[1]);
		double fTemp18 = ((fRec37[0] * fVec6[(IOTA-int((int(fRec39[0]) & 262143)))&262143]) + ((1.0 - fRec37[0]) * fVec6[(IOTA-int((int(fRec38[0]) & 262143)))&262143]));
		double 	fRec31 = max(fConst1, fabs(fTemp18));
		int iTemp19 = int((iRec29[1] < 4096));
		fRec28[0] = ((iTemp19)?max(fRec28[1], fRec31):fRec31);
		iRec29[0] = ((iTemp19)?(1 + iRec29[1]):1);
		fRec30[0] = ((iTemp19)?fRec30[1]:fRec28[1]);
		fbargraph2 = fRec30[0];
		double fTemp20 = (fSlow2 * fRec44[1]);
		double fTemp21 = (fSlow10 * fRec45[1]);
		fRec47[0] = ((fSlow36 * ((fSlow56 * fVec1[1]) + (fSlow55 * fTemp1))) + (fSlow25 * fRec47[1]));
		fRec46[0] = (fRec47[0] - (fSlow23 * ((fSlow21 * fRec46[2]) + (fSlow19 * fRec46[1]))));
		fRec45[0] = ((fSlow23 * (((fSlow18 * fRec46[0]) + (fSlow57 * fRec46[1])) + (fSlow18 * fRec46[2]))) - (fSlow54 * ((fSlow53 * fRec45[2]) + fTemp21)));
		fRec44[0] = ((fRec45[2] + (fSlow54 * (fTemp21 + (fSlow53 * fRec45[0])))) - (fSlow47 * ((fSlow46 * fRec44[2]) + fTemp20)));
		fRec48[0] = (fSlow58 + (0.999 * fRec48[1]));
		double fTemp22 = (fRec48[0] * (fRec44[2] + (fSlow47 * (fTemp20 + (fSlow46 * fRec44[0])))));
		fVec7[IOTA&262143] = fTemp22;
		double fTemp23 = ((int((fRec49[1] != 0.0)))?((int(((fRec50[1] > 0.0) & (fRec50[1] < 1.0))))?fRec49[1]:0):((int(((fRec50[1] == 0.0) & (fSlow59 != fRec51[1]))))?fConst3:((int(((fRec50[1] == 1.0) & (fSlow59 != fRec52[1]))))?fConst4:0)));
		fRec49[0] = fTemp23;
		fRec50[0] = max(0.0, min(1.0, (fRec50[1] + fTemp23)));
		fRec51[0] = ((int(((fRec50[1] >= 1.0) & (fRec52[1] != fSlow59))))?fSlow59:fRec51[1]);
		fRec52[0] = ((int(((fRec50[1] <= 0.0) & (fRec51[1] != fSlow59))))?fSlow59:fRec52[1]);
		double fTemp24 = ((fRec50[0] * fVec7[(IOTA-int((int(fRec52[0]) & 262143)))&262143]) + ((1.0 - fRec50[0]) * fVec7[(IOTA-int((int(fRec51[0]) & 262143)))&262143]));
		double 	fRec43 = max(fConst1, fabs(fTemp24));
		int iTemp25 = int((iRec41[1] < 4096));
		fRec40[0] = ((iTemp25)?max(fRec40[1], fRec43):fRec43);
		iRec41[0] = ((iTemp25)?(1 + iRec41[1]):1);
		fRec42[0] = ((iTemp25)?fRec42[1]:fRec40[1]);
		fbargraph3 = fRec42[0];
		double fTemp26 = (fSlow2 * fRec57[1]);
		double fTemp27 = (fSlow10 * fRec58[1]);
		double fTemp28 = (fSlow19 * fRec59[1]);
		fRec61[0] = ((fSlow35 * ((fSlow62 * fVec0[1]) + (fSlow29 * fVec0[0]))) + (fSlow34 * fRec61[1]));
		fRec60[0] = (fRec61[0] - (fSlow32 * ((fSlow30 * fRec60[2]) + (fSlow28 * fRec60[1]))));
		fRec59[0] = ((fSlow32 * (((fSlow27 * fRec60[0]) + (fSlow63 * fRec60[1])) + (fSlow27 * fRec60[2]))) - (fSlow61 * ((fSlow60 * fRec59[2]) + fTemp28)));
		fRec58[0] = ((fRec59[2] + (fSlow61 * (fTemp28 + (fSlow60 * fRec59[0])))) - (fSlow54 * ((fSlow53 * fRec58[2]) + fTemp27)));
		fRec57[0] = ((fRec58[2] + (fSlow54 * (fTemp27 + (fSlow53 * fRec58[0])))) - (fSlow47 * ((fSlow46 * fRec57[2]) + fTemp26)));
		fRec62[0] = (fSlow64 + (0.999 * fRec62[1]));
		double fTemp29 = (fRec62[0] * (fRec57[2] + (fSlow47 * (fTemp26 + (fSlow46 * fRec57[0])))));
		fVec8[IOTA&262143] = fTemp29;
		double fTemp30 = ((int((fRec63[1] != 0.0)))?((int(((fRec64[1] > 0.0) & (fRec64[1] < 1.0))))?fRec63[1]:0):((int(((fRec64[1] == 0.0) & (fSlow65 != fRec65[1]))))?fConst3:((int(((fRec64[1] == 1.0) & (fSlow65 != fRec66[1]))))?fConst4:0)));
		fRec63[0] = fTemp30;
		fRec64[0] = max(0.0, min(1.0, (fRec64[1] + fTemp30)));
		fRec65[0] = ((int(((fRec64[1] >= 1.0) & (fRec66[1] != fSlow65))))?fSlow65:fRec65[1]);
		fRec66[0] = ((int(((fRec64[1] <= 0.0) & (fRec65[1] != fSlow65))))?fSlow65:fRec66[1]);
		double fTemp31 = ((fRec64[0] * fVec8[(IOTA-int((int(fRec66[0]) & 262143)))&262143]) + ((1.0 - fRec64[0]) * fVec8[(IOTA-int((int(fRec65[0]) & 262143)))&262143]));
		double 	fRec56 = max(fConst1, fabs(fTemp31));
		int iTemp32 = int((iRec54[1] < 4096));
		fRec53[0] = ((iTemp32)?max(fRec53[1], fRec56):fRec56);
		iRec54[0] = ((iTemp32)?(1 + iRec54[1]):1);
		fRec55[0] = ((iTemp32)?fRec55[1]:fRec53[1]);
		fbargraph4 = fRec55[0];
		output0[i] = (FAUSTFLOAT)(fTemp31 + (fTemp24 + (fTemp18 + (fTemp13 + (fVec0[0] + fTemp9)))));
		// post processing
		fRec55[1] = fRec55[0];
		iRec54[1] = iRec54[0];
		fRec53[1] = fRec53[0];
		fRec66[1] = fRec66[0];
		fRec65[1] = fRec65[0];
		fRec64[1] = fRec64[0];
		fRec63[1] = fRec63[0];
		fRec62[1] = fRec62[0];
		fRec57[2] = fRec57[1]; fRec57[1] = fRec57[0];
		fRec58[2] = fRec58[1]; fRec58[1] = fRec58[0];
		fRec59[2] = fRec59[1]; fRec59[1] = fRec59[0];
		fRec60[2] = fRec60[1]; fRec60[1] = fRec60[0];
		fRec61[1] = fRec61[0];
		fRec42[1] = fRec42[0];
		iRec41[1] = iRec41[0];
		fRec40[1] = fRec40[0];
		fRec52[1] = fRec52[0];
		fRec51[1] = fRec51[0];
		fRec50[1] = fRec50[0];
		fRec49[1] = fRec49[0];
		fRec48[1] = fRec48[0];
		fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
		fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
		fRec46[2] = fRec46[1]; fRec46[1] = fRec46[0];
		fRec47[1] = fRec47[0];
		fRec30[1] = fRec30[0];
		iRec29[1] = iRec29[0];
		fRec28[1] = fRec28[0];
		fRec39[1] = fRec39[0];
		fRec38[1] = fRec38[0];
		fRec37[1] = fRec37[0];
		fRec36[1] = fRec36[0];
		fRec35[1] = fRec35[0];
		fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec34[1] = fRec34[0];
		fRec19[1] = fRec19[0];
		iRec18[1] = iRec18[0];
		fRec17[1] = fRec17[0];
		fRec27[1] = fRec27[0];
		fRec26[1] = fRec26[0];
		fRec25[1] = fRec25[0];
		fRec24[1] = fRec24[0];
		fRec23[1] = fRec23[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec0[1] = fRec0[0];
		fRec16[1] = fRec16[0];
		fRec15[1] = fRec15[0];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		IOTA = IOTA+1;
		fRec12[1] = fRec12[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec3[1] = fVec3[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fVec2[1] = fVec2[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fVec1[1] = fVec1[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec0[1] = fVec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("mbdel.crossover_b1_b2",N_("Crossover B1-B2 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider0, 8e+01, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbdel.crossover_b2_b3",N_("Crossover B2-B3 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider1, 2.1e+02, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbdel.crossover_b3_b4",N_("Crossover B3-B4 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider2, 1.7e+03, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbdel.crossover_b4_b5",N_("Crossover B4-B5 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider3, 5e+03, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbdel.delay1","","S",N_("Delay in Beats per Minute"),&fslider5, 3e+01, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbdel.delay2","","S",N_("Delay in Beats per Minute"),&fslider7, 6e+01, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbdel.delay3","","S",N_("Delay in Beats per Minute"),&fslider9, 9e+01, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbdel.delay4","","S",N_("Delay in Beats per Minute"),&fslider11, 1.2e+02, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbdel.delay5","","S",N_("Delay in Beats per Minute"),&fslider13, 1.5e+02, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbdel.gain1","","S","",&fslider4, -1e+01, -2e+01, 2e+01, 0.1);
	reg.registerVar("mbdel.gain2","","S","",&fslider6, -5.0, -2e+01, 2e+01, 0.1);
	reg.registerVar("mbdel.gain3","","S","",&fslider8, -2.0, -2e+01, 2e+01, 0.1);
	reg.registerVar("mbdel.gain4","","S","",&fslider10, 0.0, -2e+01, 2e+01, 0.1);
	reg.registerVar("mbdel.gain5","","S","",&fslider12, -1e+01, -2e+01, 2e+01, 0.1);
	reg.registerNonMidiFloatVar("mbdel.v1",&fbargraph0, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbdel.v2",&fbargraph1, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbdel.v3",&fbargraph2, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbdel.v4",&fbargraph3, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbdel.v5",&fbargraph4, false, true, -70.0, -70.0, 4.0, 0.00001);
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
