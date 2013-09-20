// generated from file '../src/plugins/mbe.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace mbe {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider0;
	int 	iConst4;
	double 	fRec5[2];
	double 	fRec6[2];
	double 	fRec7[2];
	double 	fRec8[2];
	FAUSTFLOAT 	fslider1;
	double 	fRec9[2];
	FAUSTFLOAT 	fslider2;
	double 	fConst5;
	double 	fVec0[2];
	double 	fRec11[2];
	double 	fRec10[3];
	int 	IOTA;
	double 	fRec4[524288];
	double 	fRec0[2];
	int 	iRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT 	fslider3;
	double 	fRec17[2];
	double 	fRec18[2];
	double 	fRec19[2];
	double 	fRec20[2];
	FAUSTFLOAT 	fslider4;
	double 	fRec21[2];
	FAUSTFLOAT 	fslider5;
	double 	fRec25[2];
	double 	fRec24[3];
	double 	fVec1[2];
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fRec16[524288];
	double 	fRec12[2];
	int 	iRec13[2];
	double 	fRec14[2];
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT 	fslider6;
	double 	fRec31[2];
	double 	fRec32[2];
	double 	fRec33[2];
	double 	fRec34[2];
	FAUSTFLOAT 	fslider7;
	double 	fRec35[2];
	FAUSTFLOAT 	fslider8;
	double 	fRec39[2];
	double 	fRec38[3];
	double 	fVec2[2];
	double 	fRec37[2];
	double 	fRec36[3];
	double 	fRec30[524288];
	double 	fRec26[2];
	int 	iRec27[2];
	double 	fRec28[2];
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT 	fslider9;
	double 	fRec45[2];
	double 	fRec46[2];
	double 	fRec47[2];
	double 	fRec48[2];
	FAUSTFLOAT 	fslider10;
	double 	fRec49[2];
	FAUSTFLOAT 	fslider11;
	double 	fRec53[2];
	double 	fRec52[3];
	double 	fVec3[2];
	double 	fRec51[2];
	double 	fRec50[3];
	double 	fRec44[524288];
	double 	fRec40[2];
	int 	iRec41[2];
	double 	fRec42[2];
	FAUSTFLOAT 	fbargraph3;
	FAUSTFLOAT 	fslider12;
	double 	fRec59[2];
	double 	fRec60[2];
	double 	fRec61[2];
	double 	fRec62[2];
	FAUSTFLOAT 	fslider13;
	double 	fRec63[2];
	double 	fRec65[2];
	double 	fRec64[3];
	double 	fRec58[524288];
	double 	fRec54[2];
	int 	iRec55[2];
	double 	fRec56[2];
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
	id = "mbe";
	name = N_("MultiBand Echo");
	groups = 0;
	description = N_("Multi Band Echo"); // description (tooltip)
	category = N_("Echo / Delay");       // category
	shortname = N_("MB Echo");     // shortname
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
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<524288; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<524288; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) iRec13[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<3; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<3; i++) fRec36[i] = 0;
	for (int i=0; i<524288; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) iRec27[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) fRec53[i] = 0;
	for (int i=0; i<3; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<3; i++) fRec50[i] = 0;
	for (int i=0; i<524288; i++) fRec44[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) iRec41[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec59[i] = 0;
	for (int i=0; i<2; i++) fRec60[i] = 0;
	for (int i=0; i<2; i++) fRec61[i] = 0;
	for (int i=0; i<2; i++) fRec62[i] = 0;
	for (int i=0; i<2; i++) fRec63[i] = 0;
	for (int i=0; i<2; i++) fRec65[i] = 0;
	for (int i=0; i<3; i++) fRec64[i] = 0;
	for (int i=0; i<524288; i++) fRec58[i] = 0;
	for (int i=0; i<2; i++) fRec54[i] = 0;
	for (int i=0; i<2; i++) iRec55[i] = 0;
	for (int i=0; i<2; i++) fRec56[i] = 0;
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
	fConst2 = (1e+01 / double(iConst0));
	fConst3 = (0 - fConst2);
	iConst4 = (60 * iConst0);
	fConst5 = (3.141592653589793 / double(iConst0));
	IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (double(iConst4) / fslider0);
	double 	fSlow1 = (1.000000000000001e-05 * fslider1);
	double 	fSlow2 = tan((fConst5 * fslider2));
	double 	fSlow3 = (1.0 / faustpower<2>(fSlow2));
	double 	fSlow4 = (2 * (1 - fSlow3));
	double 	fSlow5 = (1.0 / fSlow2);
	double 	fSlow6 = (1 + ((fSlow5 - 1.0000000000000004) / fSlow2));
	double 	fSlow7 = (1 + ((1.0000000000000004 + fSlow5) / fSlow2));
	double 	fSlow8 = (1.0 / fSlow7);
	double 	fSlow9 = (1 + fSlow5);
	double 	fSlow10 = (0 - ((1 - fSlow5) / fSlow9));
	double 	fSlow11 = (0 - fSlow5);
	double 	fSlow12 = (1.0 / fSlow9);
	double 	fSlow13 = (2 * (0 - fSlow3));
	double 	fSlow14 = (double(iConst4) / fslider3);
	double 	fSlow15 = (1.000000000000001e-05 * fslider4);
	double 	fSlow16 = tan((fConst5 * fslider5));
	double 	fSlow17 = (1.0 / faustpower<2>(fSlow16));
	double 	fSlow18 = (2 * (1 - fSlow17));
	double 	fSlow19 = (1.0 / fSlow16);
	double 	fSlow20 = (1 + ((fSlow19 - 1.0000000000000004) / fSlow16));
	double 	fSlow21 = (1 + ((1.0000000000000004 + fSlow19) / fSlow16));
	double 	fSlow22 = (1.0 / fSlow21);
	double 	fSlow23 = (1 + fSlow19);
	double 	fSlow24 = (0 - ((1 - fSlow19) / fSlow23));
	double 	fSlow25 = (1.0 / (fSlow7 * fSlow16));
	double 	fSlow26 = (0 - fSlow19);
	double 	fSlow27 = (1.0 / fSlow23);
	double 	fSlow28 = (2 * (0 - fSlow17));
	double 	fSlow29 = (double(iConst4) / fslider6);
	double 	fSlow30 = (1.000000000000001e-05 * fslider7);
	double 	fSlow31 = tan((fConst5 * fslider8));
	double 	fSlow32 = (1.0 / faustpower<2>(fSlow31));
	double 	fSlow33 = (2 * (1 - fSlow32));
	double 	fSlow34 = (1.0 / fSlow31);
	double 	fSlow35 = (1 + ((fSlow34 - 1.0000000000000004) / fSlow31));
	double 	fSlow36 = (1 + ((1.0000000000000004 + fSlow34) / fSlow31));
	double 	fSlow37 = (1.0 / fSlow36);
	double 	fSlow38 = (1 + fSlow34);
	double 	fSlow39 = (0 - ((1 - fSlow34) / fSlow38));
	double 	fSlow40 = (1.0 / (fSlow21 * fSlow31));
	double 	fSlow41 = (0 - fSlow34);
	double 	fSlow42 = (1.0 / fSlow38);
	double 	fSlow43 = (2 * (0 - fSlow32));
	double 	fSlow44 = (double(iConst4) / fslider9);
	double 	fSlow45 = (1.000000000000001e-05 * fslider10);
	double 	fSlow46 = tan((fConst5 * fslider11));
	double 	fSlow47 = (1.0 / faustpower<2>(fSlow46));
	double 	fSlow48 = (2 * (1 - fSlow47));
	double 	fSlow49 = (1.0 / fSlow46);
	double 	fSlow50 = (1 + ((fSlow49 - 1.0000000000000004) / fSlow46));
	double 	fSlow51 = (1.0 / (1 + ((1.0000000000000004 + fSlow49) / fSlow46)));
	double 	fSlow52 = (1 + fSlow49);
	double 	fSlow53 = (0 - ((1 - fSlow49) / fSlow52));
	double 	fSlow54 = (1.0 / (fSlow36 * fSlow46));
	double 	fSlow55 = (0 - fSlow49);
	double 	fSlow56 = (1.0 / fSlow52);
	double 	fSlow57 = (2 * (0 - fSlow47));
	double 	fSlow58 = (double(iConst4) / fslider12);
	double 	fSlow59 = (1.000000000000001e-05 * fslider13);
	for (int i=0; i<count; i++) {
		double fTemp0 = ((int((fRec5[1] != 0.0)))?((int(((fRec6[1] > 0.0) & (fRec6[1] < 1.0))))?fRec5[1]:0):((int(((fRec6[1] == 0.0) & (fSlow0 != fRec7[1]))))?fConst2:((int(((fRec6[1] == 1.0) & (fSlow0 != fRec8[1]))))?fConst3:0)));
		fRec5[0] = fTemp0;
		fRec6[0] = max(0.0, min(1.0, (fRec6[1] + fTemp0)));
		fRec7[0] = ((int(((fRec6[1] >= 1.0) & (fRec8[1] != fSlow0))))?fSlow0:fRec7[1]);
		fRec8[0] = ((int(((fRec6[1] <= 0.0) & (fRec7[1] != fSlow0))))?fSlow0:fRec8[1]);
		fRec9[0] = (fSlow1 + (0.999 * fRec9[1]));
		double fTemp1 = (double)input0[i];
		fVec0[0] = fTemp1;
		fRec11[0] = ((fSlow12 * ((fSlow11 * fVec0[1]) + (fSlow5 * fVec0[0]))) + (fSlow10 * fRec11[1]));
		fRec10[0] = (fRec11[0] - (fSlow8 * ((fSlow6 * fRec10[2]) + (fSlow4 * fRec10[1]))));
		fRec4[IOTA&524287] = ((fSlow8 * (((fSlow3 * fRec10[0]) + (fSlow13 * fRec10[1])) + (fSlow3 * fRec10[2]))) + (fRec9[0] * ((fRec6[0] * fRec4[(IOTA-int((1 + int((int(fRec8[0]) & 262143)))))&524287]) + ((1.0 - fRec6[0]) * fRec4[(IOTA-int((1 + int((int(fRec7[0]) & 262143)))))&524287]))));
		double fTemp2 = fRec4[(IOTA-0)&524287];
		double 	fRec3 = max(fConst1, fabs(fTemp2));
		int iTemp3 = int((iRec1[1] < 4096));
		fRec0[0] = ((iTemp3)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp3)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp3)?fRec2[1]:fRec0[1]);
		fbargraph0 = fRec2[0];
		double fTemp4 = ((int((fRec17[1] != 0.0)))?((int(((fRec18[1] > 0.0) & (fRec18[1] < 1.0))))?fRec17[1]:0):((int(((fRec18[1] == 0.0) & (fSlow14 != fRec19[1]))))?fConst2:((int(((fRec18[1] == 1.0) & (fSlow14 != fRec20[1]))))?fConst3:0)));
		fRec17[0] = fTemp4;
		fRec18[0] = max(0.0, min(1.0, (fRec18[1] + fTemp4)));
		fRec19[0] = ((int(((fRec18[1] >= 1.0) & (fRec20[1] != fSlow14))))?fSlow14:fRec19[1]);
		fRec20[0] = ((int(((fRec18[1] <= 0.0) & (fRec19[1] != fSlow14))))?fSlow14:fRec20[1]);
		fRec21[0] = (fSlow15 + (0.999 * fRec21[1]));
		double fTemp5 = (fVec0[0] + fVec0[1]);
		fRec25[0] = ((fSlow12 * fTemp5) + (fSlow10 * fRec25[1]));
		fRec24[0] = (fRec25[0] - (fSlow8 * ((fSlow6 * fRec24[2]) + (fSlow4 * fRec24[1]))));
		double fTemp6 = (fRec24[2] + (fRec24[0] + (2 * fRec24[1])));
		fVec1[0] = (fSlow8 * fTemp6);
		fRec23[0] = ((fSlow27 * ((fSlow26 * fVec1[1]) + (fSlow25 * fTemp6))) + (fSlow24 * fRec23[1]));
		fRec22[0] = (fRec23[0] - (fSlow22 * ((fSlow20 * fRec22[2]) + (fSlow18 * fRec22[1]))));
		fRec16[IOTA&524287] = ((fSlow22 * (((fSlow17 * fRec22[0]) + (fSlow28 * fRec22[1])) + (fSlow17 * fRec22[2]))) + (fRec21[0] * ((fRec18[0] * fRec16[(IOTA-int((1 + int((int(fRec20[0]) & 262143)))))&524287]) + ((1.0 - fRec18[0]) * fRec16[(IOTA-int((1 + int((int(fRec19[0]) & 262143)))))&524287]))));
		double fTemp7 = fRec16[(IOTA-0)&524287];
		double 	fRec15 = max(fConst1, fabs(fTemp7));
		int iTemp8 = int((iRec13[1] < 4096));
		fRec12[0] = ((iTemp8)?max(fRec12[1], fRec15):fRec15);
		iRec13[0] = ((iTemp8)?(1 + iRec13[1]):1);
		fRec14[0] = ((iTemp8)?fRec14[1]:fRec12[1]);
		fbargraph1 = fRec14[0];
		double fTemp9 = ((int((fRec31[1] != 0.0)))?((int(((fRec32[1] > 0.0) & (fRec32[1] < 1.0))))?fRec31[1]:0):((int(((fRec32[1] == 0.0) & (fSlow29 != fRec33[1]))))?fConst2:((int(((fRec32[1] == 1.0) & (fSlow29 != fRec34[1]))))?fConst3:0)));
		fRec31[0] = fTemp9;
		fRec32[0] = max(0.0, min(1.0, (fRec32[1] + fTemp9)));
		fRec33[0] = ((int(((fRec32[1] >= 1.0) & (fRec34[1] != fSlow29))))?fSlow29:fRec33[1]);
		fRec34[0] = ((int(((fRec32[1] <= 0.0) & (fRec33[1] != fSlow29))))?fSlow29:fRec34[1]);
		fRec35[0] = (fSlow30 + (0.999 * fRec35[1]));
		fRec39[0] = ((fSlow27 * fTemp5) + (fSlow24 * fRec39[1]));
		fRec38[0] = (fRec39[0] - (fSlow22 * ((fSlow20 * fRec38[2]) + (fSlow18 * fRec38[1]))));
		double fTemp10 = (fRec38[2] + (fRec38[0] + (2 * fRec38[1])));
		fVec2[0] = (fSlow22 * fTemp10);
		fRec37[0] = ((fSlow42 * ((fSlow41 * fVec2[1]) + (fSlow40 * fTemp10))) + (fSlow39 * fRec37[1]));
		fRec36[0] = (fRec37[0] - (fSlow37 * ((fSlow35 * fRec36[2]) + (fSlow33 * fRec36[1]))));
		fRec30[IOTA&524287] = ((fSlow37 * (((fSlow32 * fRec36[0]) + (fSlow43 * fRec36[1])) + (fSlow32 * fRec36[2]))) + (fRec35[0] * ((fRec32[0] * fRec30[(IOTA-int((1 + int((int(fRec34[0]) & 262143)))))&524287]) + ((1.0 - fRec32[0]) * fRec30[(IOTA-int((1 + int((int(fRec33[0]) & 262143)))))&524287]))));
		double fTemp11 = fRec30[(IOTA-0)&524287];
		double 	fRec29 = max(fConst1, fabs(fTemp11));
		int iTemp12 = int((iRec27[1] < 4096));
		fRec26[0] = ((iTemp12)?max(fRec26[1], fRec29):fRec29);
		iRec27[0] = ((iTemp12)?(1 + iRec27[1]):1);
		fRec28[0] = ((iTemp12)?fRec28[1]:fRec26[1]);
		fbargraph2 = fRec28[0];
		double fTemp13 = ((int((fRec45[1] != 0.0)))?((int(((fRec46[1] > 0.0) & (fRec46[1] < 1.0))))?fRec45[1]:0):((int(((fRec46[1] == 0.0) & (fSlow44 != fRec47[1]))))?fConst2:((int(((fRec46[1] == 1.0) & (fSlow44 != fRec48[1]))))?fConst3:0)));
		fRec45[0] = fTemp13;
		fRec46[0] = max(0.0, min(1.0, (fRec46[1] + fTemp13)));
		fRec47[0] = ((int(((fRec46[1] >= 1.0) & (fRec48[1] != fSlow44))))?fSlow44:fRec47[1]);
		fRec48[0] = ((int(((fRec46[1] <= 0.0) & (fRec47[1] != fSlow44))))?fSlow44:fRec48[1]);
		fRec49[0] = (fSlow45 + (0.999 * fRec49[1]));
		fRec53[0] = ((fSlow42 * fTemp5) + (fSlow39 * fRec53[1]));
		fRec52[0] = (fRec53[0] - (fSlow37 * ((fSlow35 * fRec52[2]) + (fSlow33 * fRec52[1]))));
		double fTemp14 = (fRec52[2] + (fRec52[0] + (2 * fRec52[1])));
		fVec3[0] = (fSlow37 * fTemp14);
		fRec51[0] = ((fSlow56 * ((fSlow55 * fVec3[1]) + (fSlow54 * fTemp14))) + (fSlow53 * fRec51[1]));
		fRec50[0] = (fRec51[0] - (fSlow51 * ((fSlow50 * fRec50[2]) + (fSlow48 * fRec50[1]))));
		fRec44[IOTA&524287] = ((fSlow51 * (((fSlow47 * fRec50[0]) + (fSlow57 * fRec50[1])) + (fSlow47 * fRec50[2]))) + (fRec49[0] * ((fRec46[0] * fRec44[(IOTA-int((1 + int((int(fRec48[0]) & 262143)))))&524287]) + ((1.0 - fRec46[0]) * fRec44[(IOTA-int((1 + int((int(fRec47[0]) & 262143)))))&524287]))));
		double fTemp15 = fRec44[(IOTA-0)&524287];
		double 	fRec43 = max(fConst1, fabs(fTemp15));
		int iTemp16 = int((iRec41[1] < 4096));
		fRec40[0] = ((iTemp16)?max(fRec40[1], fRec43):fRec43);
		iRec41[0] = ((iTemp16)?(1 + iRec41[1]):1);
		fRec42[0] = ((iTemp16)?fRec42[1]:fRec40[1]);
		fbargraph3 = fRec42[0];
		double fTemp17 = ((int((fRec59[1] != 0.0)))?((int(((fRec60[1] > 0.0) & (fRec60[1] < 1.0))))?fRec59[1]:0):((int(((fRec60[1] == 0.0) & (fSlow58 != fRec61[1]))))?fConst2:((int(((fRec60[1] == 1.0) & (fSlow58 != fRec62[1]))))?fConst3:0)));
		fRec59[0] = fTemp17;
		fRec60[0] = max(0.0, min(1.0, (fRec60[1] + fTemp17)));
		fRec61[0] = ((int(((fRec60[1] >= 1.0) & (fRec62[1] != fSlow58))))?fSlow58:fRec61[1]);
		fRec62[0] = ((int(((fRec60[1] <= 0.0) & (fRec61[1] != fSlow58))))?fSlow58:fRec62[1]);
		fRec63[0] = (fSlow59 + (0.999 * fRec63[1]));
		fRec65[0] = ((fSlow56 * fTemp5) + (fSlow53 * fRec65[1]));
		fRec64[0] = (fRec65[0] - (fSlow51 * ((fSlow50 * fRec64[2]) + (fSlow48 * fRec64[1]))));
		fRec58[IOTA&524287] = ((fSlow51 * (fRec64[2] + (fRec64[0] + (2 * fRec64[1])))) + (fRec63[0] * ((fRec60[0] * fRec58[(IOTA-int((1 + int((int(fRec62[0]) & 262143)))))&524287]) + ((1.0 - fRec60[0]) * fRec58[(IOTA-int((1 + int((int(fRec61[0]) & 262143)))))&524287]))));
		double fTemp18 = fRec58[(IOTA-0)&524287];
		double 	fRec57 = max(fConst1, fabs(fTemp18));
		int iTemp19 = int((iRec55[1] < 4096));
		fRec54[0] = ((iTemp19)?max(fRec54[1], fRec57):fRec57);
		iRec55[0] = ((iTemp19)?(1 + iRec55[1]):1);
		fRec56[0] = ((iTemp19)?fRec56[1]:fRec54[1]);
		fbargraph4 = fRec56[0];
		output0[i] = (FAUSTFLOAT)((((fTemp18 + fTemp15) + fTemp11) + fTemp7) + fTemp2);
		// post processing
		fRec56[1] = fRec56[0];
		iRec55[1] = iRec55[0];
		fRec54[1] = fRec54[0];
		fRec64[2] = fRec64[1]; fRec64[1] = fRec64[0];
		fRec65[1] = fRec65[0];
		fRec63[1] = fRec63[0];
		fRec62[1] = fRec62[0];
		fRec61[1] = fRec61[0];
		fRec60[1] = fRec60[0];
		fRec59[1] = fRec59[0];
		fRec42[1] = fRec42[0];
		iRec41[1] = iRec41[0];
		fRec40[1] = fRec40[0];
		fRec50[2] = fRec50[1]; fRec50[1] = fRec50[0];
		fRec51[1] = fRec51[0];
		fVec3[1] = fVec3[0];
		fRec52[2] = fRec52[1]; fRec52[1] = fRec52[0];
		fRec53[1] = fRec53[0];
		fRec49[1] = fRec49[0];
		fRec48[1] = fRec48[0];
		fRec47[1] = fRec47[0];
		fRec46[1] = fRec46[0];
		fRec45[1] = fRec45[0];
		fRec28[1] = fRec28[0];
		iRec27[1] = iRec27[0];
		fRec26[1] = fRec26[0];
		fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fVec2[1] = fVec2[0];
		fRec38[2] = fRec38[1]; fRec38[1] = fRec38[0];
		fRec39[1] = fRec39[0];
		fRec35[1] = fRec35[0];
		fRec34[1] = fRec34[0];
		fRec33[1] = fRec33[0];
		fRec32[1] = fRec32[0];
		fRec31[1] = fRec31[0];
		fRec14[1] = fRec14[0];
		iRec13[1] = iRec13[0];
		fRec12[1] = fRec12[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fVec1[1] = fVec1[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec17[1] = fRec17[0];
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec0[1] = fVec0[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
	}
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("mbe.crossover_b1_b2",N_("Crossover B1-B2 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider11, 8e+01, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbe.crossover_b2_b3",N_("Crossover B2-B3 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider8, 2.1e+02, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbe.crossover_b3_b4",N_("Crossover B3-B4 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider5, 1.7e+03, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbe.crossover_b4_b5",N_("Crossover B4-B5 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider2, 5e+03, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbe.percent1","","S","",&fslider13, 1e+01, 0.0, 1e+02, 0.1);
	reg.registerVar("mbe.percent2","","S","",&fslider10, 3e+01, 0.0, 1e+02, 0.1);
	reg.registerVar("mbe.percent3","","S","",&fslider7, 45.0, 0.0, 1e+02, 0.1);
	reg.registerVar("mbe.percent4","","S","",&fslider4, 2e+01, 0.0, 1e+02, 0.1);
	reg.registerVar("mbe.percent5","","S","",&fslider1, 0.0, 0.0, 1e+02, 0.1);
	reg.registerVar("mbe.time1","","S",N_("Echo in Beats per Minute"),&fslider12, 3e+01, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbe.time2","","S",N_("Echo in Beats per Minute"),&fslider9, 6e+01, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbe.time3","","S",N_("Echo in Beats per Minute"),&fslider6, 1.2e+02, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbe.time4","","S",N_("Echo in Beats per Minute"),&fslider3, 1.5e+02, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbe.time5","","S",N_("Echo in Beats per Minute"),&fslider0, 2.4e+02, 24.0, 3.6e+02, 1.0);
	reg.registerNonMidiFloatVar("mbe.v1",&fbargraph4, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbe.v2",&fbargraph3, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbe.v3",&fbargraph2, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbe.v4",&fbargraph1, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbe.v5",&fbargraph0, false, true, -70.0, -70.0, 4.0, 0.00001);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("mbe" "." p)

b.openHorizontalhideBox("");
b.closeBox();

b.openHorizontalBox("");
b.openVerticalBox("");

b.openTabBox("");

b.openHorizontalBox(N_("Band 1"));
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("time1"), N_("BPM"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("percent1"), N_("Amount"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b1_b2"), N_("Low Shelf (Hz)"));
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 2"));
b.openVerticalBox("");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("time2"), N_("BPM"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("percent2"), N_("Amount"));
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
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("time3"), N_("BPM"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("percent3"), N_("Amount"));
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
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("time4"), N_("BPM"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("percent4"), N_("Amount"));
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
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("time5"), N_("BPM"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("percent5"), N_("Amount"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b4_b5"), N_("High Shelf (Hz)"));
b.closeBox();
b.closeBox();
b.closeBox();

b.closeBox();
b.closeBox();
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

} // end namespace mbe
} // end namespace pluginlib
