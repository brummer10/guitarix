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
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	double 	fVec0[2];
	double 	fRec17[2];
	double 	fRec16[3];
	double 	fVec1[2];
	double 	fRec15[2];
	double 	fRec14[3];
	double 	fVec2[2];
	double 	fRec13[2];
	double 	fRec12[3];
	double 	fVec3[2];
	double 	fRec11[2];
	double 	fRec10[3];
	int 	IOTA;
	double 	fRec4[524288];
	double 	fRec0[2];
	int 	iRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT 	fslider6;
	double 	fRec23[2];
	double 	fRec24[2];
	double 	fRec25[2];
	double 	fRec26[2];
	FAUSTFLOAT 	fslider7;
	double 	fRec27[2];
	double 	fRec29[2];
	double 	fRec28[3];
	double 	fRec22[524288];
	double 	fRec18[2];
	int 	iRec19[2];
	double 	fRec20[2];
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT 	fslider8;
	double 	fRec35[2];
	double 	fRec36[2];
	double 	fRec37[2];
	double 	fRec38[2];
	FAUSTFLOAT 	fslider9;
	double 	fRec39[2];
	double 	fRec42[2];
	double 	fRec41[3];
	double 	fRec40[3];
	double 	fRec34[524288];
	double 	fRec30[2];
	int 	iRec31[2];
	double 	fRec32[2];
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT 	fslider10;
	double 	fRec48[2];
	double 	fRec49[2];
	double 	fRec50[2];
	double 	fRec51[2];
	FAUSTFLOAT 	fslider11;
	double 	fRec52[2];
	double 	fRec56[2];
	double 	fRec55[3];
	double 	fRec54[3];
	double 	fRec53[3];
	double 	fRec47[524288];
	double 	fRec43[2];
	int 	iRec44[2];
	double 	fRec45[2];
	FAUSTFLOAT 	fbargraph3;
	FAUSTFLOAT 	fslider12;
	double 	fRec62[2];
	double 	fRec63[2];
	double 	fRec64[2];
	double 	fRec65[2];
	FAUSTFLOAT 	fslider13;
	double 	fRec66[2];
	double 	fRec71[2];
	double 	fRec70[3];
	double 	fRec69[3];
	double 	fRec68[3];
	double 	fRec67[3];
	double 	fRec61[524288];
	double 	fRec57[2];
	int 	iRec58[2];
	double 	fRec59[2];
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
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<524288; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<524288; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) iRec19[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec39[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<3; i++) fRec41[i] = 0;
	for (int i=0; i<3; i++) fRec40[i] = 0;
	for (int i=0; i<524288; i++) fRec34[i] = 0;
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) iRec31[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec49[i] = 0;
	for (int i=0; i<2; i++) fRec50[i] = 0;
	for (int i=0; i<2; i++) fRec51[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<2; i++) fRec56[i] = 0;
	for (int i=0; i<3; i++) fRec55[i] = 0;
	for (int i=0; i<3; i++) fRec54[i] = 0;
	for (int i=0; i<3; i++) fRec53[i] = 0;
	for (int i=0; i<524288; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) iRec44[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
	for (int i=0; i<2; i++) fRec62[i] = 0;
	for (int i=0; i<2; i++) fRec63[i] = 0;
	for (int i=0; i<2; i++) fRec64[i] = 0;
	for (int i=0; i<2; i++) fRec65[i] = 0;
	for (int i=0; i<2; i++) fRec66[i] = 0;
	for (int i=0; i<2; i++) fRec71[i] = 0;
	for (int i=0; i<3; i++) fRec70[i] = 0;
	for (int i=0; i<3; i++) fRec69[i] = 0;
	for (int i=0; i<3; i++) fRec68[i] = 0;
	for (int i=0; i<3; i++) fRec67[i] = 0;
	for (int i=0; i<524288; i++) fRec61[i] = 0;
	for (int i=0; i<2; i++) fRec57[i] = 0;
	for (int i=0; i<2; i++) iRec58[i] = 0;
	for (int i=0; i<2; i++) fRec59[i] = 0;
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

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (double(iConst4) / fslider0);
	double 	fSlow1 = (1.000000000000001e-05 * fslider1);
	double 	fSlow2 = tan((fConst5 * fslider2));
	double 	fSlow3 = (1.0 / faustpower<2>(fSlow2));
	double 	fSlow4 = (2 * (1 - fSlow3));
	double 	fSlow5 = (1.0 / fSlow2);
	double 	fSlow6 = (1 + ((fSlow5 - 1.0000000000000004) / fSlow2));
	double 	fSlow7 = (1.0 / (1 + ((fSlow5 + 1.0000000000000004) / fSlow2)));
	double 	fSlow8 = (1 + fSlow5);
	double 	fSlow9 = (0 - ((1 - fSlow5) / fSlow8));
	double 	fSlow10 = tan((fConst5 * fslider3));
	double 	fSlow11 = (1.0 / faustpower<2>(fSlow10));
	double 	fSlow12 = (2 * (1 - fSlow11));
	double 	fSlow13 = (1.0 / fSlow10);
	double 	fSlow14 = (1 + ((fSlow13 - 1.0000000000000004) / fSlow10));
	double 	fSlow15 = (1 + ((fSlow13 + 1.0000000000000004) / fSlow10));
	double 	fSlow16 = (1.0 / fSlow15);
	double 	fSlow17 = (1 + fSlow13);
	double 	fSlow18 = (0 - ((1 - fSlow13) / fSlow17));
	double 	fSlow19 = tan((fConst5 * fslider4));
	double 	fSlow20 = (1.0 / faustpower<2>(fSlow19));
	double 	fSlow21 = (2 * (1 - fSlow20));
	double 	fSlow22 = (1.0 / fSlow19);
	double 	fSlow23 = (1 + ((fSlow22 - 1.0000000000000004) / fSlow19));
	double 	fSlow24 = (1 + ((fSlow22 + 1.0000000000000004) / fSlow19));
	double 	fSlow25 = (1.0 / fSlow24);
	double 	fSlow26 = (1 + fSlow22);
	double 	fSlow27 = (0 - ((1 - fSlow22) / fSlow26));
	double 	fSlow28 = tan((fConst5 * fslider5));
	double 	fSlow29 = (1.0 / faustpower<2>(fSlow28));
	double 	fSlow30 = (2 * (1 - fSlow29));
	double 	fSlow31 = (1.0 / fSlow28);
	double 	fSlow32 = (1 + ((fSlow31 - 1.0000000000000004) / fSlow28));
	double 	fSlow33 = (1 + ((1.0000000000000004 + fSlow31) / fSlow28));
	double 	fSlow34 = (1.0 / fSlow33);
	double 	fSlow35 = (1 + fSlow31);
	double 	fSlow36 = (0 - ((1 - fSlow31) / fSlow35));
	double 	fSlow37 = (1.0 / fSlow35);
	double 	fSlow38 = (1.0 / fSlow26);
	double 	fSlow39 = (1.0 / fSlow17);
	double 	fSlow40 = (1.0 / fSlow8);
	double 	fSlow41 = (double(iConst4) / fslider6);
	double 	fSlow42 = (1.000000000000001e-05 * fslider7);
	double 	fSlow43 = (1.0 / (fSlow2 * fSlow15));
	double 	fSlow44 = (0 - fSlow5);
	double 	fSlow45 = (2 * (0 - fSlow3));
	double 	fSlow46 = (double(iConst4) / fslider8);
	double 	fSlow47 = (1.000000000000001e-05 * fslider9);
	double 	fSlow48 = (1 + ((fSlow5 - 1.0) / fSlow2));
	double 	fSlow49 = (1.0 / (1 + ((1.0 + fSlow5) / fSlow2)));
	double 	fSlow50 = (1.0 / (fSlow10 * fSlow24));
	double 	fSlow51 = (0 - fSlow13);
	double 	fSlow52 = (2 * (0 - fSlow11));
	double 	fSlow53 = (double(iConst4) / fslider10);
	double 	fSlow54 = (1.000000000000001e-05 * fslider11);
	double 	fSlow55 = (1 + ((fSlow13 - 1.0) / fSlow10));
	double 	fSlow56 = (1.0 / (1 + ((1.0 + fSlow13) / fSlow10)));
	double 	fSlow57 = (1.0 / (fSlow19 * fSlow33));
	double 	fSlow58 = (0 - fSlow22);
	double 	fSlow59 = (2 * (0 - fSlow20));
	double 	fSlow60 = (double(iConst4) / fslider12);
	double 	fSlow61 = (1.000000000000001e-05 * fslider13);
	double 	fSlow62 = (1 + ((fSlow22 - 1.0) / fSlow19));
	double 	fSlow63 = (1.0 / (1 + ((1.0 + fSlow22) / fSlow19)));
	double 	fSlow64 = (0 - fSlow31);
	double 	fSlow65 = (2 * (0 - fSlow29));
	for (int i=0; i<count; i++) {
		double fTemp0 = ((int((fRec5[1] != 0.0)))?((int(((fRec6[1] > 0.0) & (fRec6[1] < 1.0))))?fRec5[1]:0):((int(((fRec6[1] == 0.0) & (fSlow0 != fRec7[1]))))?fConst2:((int(((fRec6[1] == 1.0) & (fSlow0 != fRec8[1]))))?fConst3:0)));
		fRec5[0] = fTemp0;
		fRec6[0] = max(0.0, min(1.0, (fRec6[1] + fTemp0)));
		fRec7[0] = ((int(((fRec6[1] >= 1.0) & (fRec8[1] != fSlow0))))?fSlow0:fRec7[1]);
		fRec8[0] = ((int(((fRec6[1] <= 0.0) & (fRec7[1] != fSlow0))))?fSlow0:fRec8[1]);
		fRec9[0] = (fSlow1 + (0.999 * fRec9[1]));
		double fTemp1 = (double)input0[i];
		fVec0[0] = fTemp1;
		fRec17[0] = ((fSlow37 * (fVec0[0] + fVec0[1])) + (fSlow36 * fRec17[1]));
		fRec16[0] = (fRec17[0] - (fSlow34 * ((fSlow32 * fRec16[2]) + (fSlow30 * fRec16[1]))));
		double fTemp2 = (fRec16[2] + (fRec16[0] + (2 * fRec16[1])));
		double fTemp3 = (fSlow34 * fTemp2);
		fVec1[0] = fTemp3;
		fRec15[0] = ((fSlow38 * (fVec1[0] + fVec1[1])) + (fSlow27 * fRec15[1]));
		fRec14[0] = (fRec15[0] - (fSlow25 * ((fSlow23 * fRec14[2]) + (fSlow21 * fRec14[1]))));
		double fTemp4 = (fRec14[2] + (fRec14[0] + (2 * fRec14[1])));
		double fTemp5 = (fSlow25 * fTemp4);
		fVec2[0] = fTemp5;
		fRec13[0] = ((fSlow39 * (fVec2[0] + fVec2[1])) + (fSlow18 * fRec13[1]));
		fRec12[0] = (fRec13[0] - (fSlow16 * ((fSlow14 * fRec12[2]) + (fSlow12 * fRec12[1]))));
		double fTemp6 = (fRec12[2] + (fRec12[0] + (2 * fRec12[1])));
		double fTemp7 = (fSlow16 * fTemp6);
		fVec3[0] = fTemp7;
		fRec11[0] = ((fSlow40 * (fVec3[0] + fVec3[1])) + (fSlow9 * fRec11[1]));
		fRec10[0] = (fRec11[0] - (fSlow7 * ((fSlow6 * fRec10[2]) + (fSlow4 * fRec10[1]))));
		fRec4[IOTA&524287] = ((fSlow7 * (fRec10[2] + (fRec10[0] + (2 * fRec10[1])))) + (fRec9[0] * ((fRec6[0] * fRec4[(IOTA-int((1 + int((int(fRec8[0]) & 262143)))))&524287]) + ((1.0 - fRec6[0]) * fRec4[(IOTA-int((1 + int((int(fRec7[0]) & 262143)))))&524287]))));
		double fTemp8 = fRec4[(IOTA-0)&524287];
		double 	fRec3 = max(fConst1, fabs(fTemp8));
		int iTemp9 = int((iRec1[1] < 4096));
		fRec0[0] = ((iTemp9)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp9)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp9)?fRec2[1]:fRec0[1]);
		fbargraph0 = fRec2[0];
		double fTemp10 = ((int((fRec23[1] != 0.0)))?((int(((fRec24[1] > 0.0) & (fRec24[1] < 1.0))))?fRec23[1]:0):((int(((fRec24[1] == 0.0) & (fSlow41 != fRec25[1]))))?fConst2:((int(((fRec24[1] == 1.0) & (fSlow41 != fRec26[1]))))?fConst3:0)));
		fRec23[0] = fTemp10;
		fRec24[0] = max(0.0, min(1.0, (fRec24[1] + fTemp10)));
		fRec25[0] = ((int(((fRec24[1] >= 1.0) & (fRec26[1] != fSlow41))))?fSlow41:fRec25[1]);
		fRec26[0] = ((int(((fRec24[1] <= 0.0) & (fRec25[1] != fSlow41))))?fSlow41:fRec26[1]);
		fRec27[0] = (fSlow42 + (0.999 * fRec27[1]));
		fRec29[0] = ((fSlow40 * ((fSlow44 * fVec3[1]) + (fSlow43 * fTemp6))) + (fSlow9 * fRec29[1]));
		fRec28[0] = (fRec29[0] - (fSlow7 * ((fSlow6 * fRec28[2]) + (fSlow4 * fRec28[1]))));
		fRec22[IOTA&524287] = ((fSlow7 * (((fSlow3 * fRec28[0]) + (fSlow45 * fRec28[1])) + (fSlow3 * fRec28[2]))) + (fRec27[0] * ((fRec24[0] * fRec22[(IOTA-int((1 + int((int(fRec26[0]) & 262143)))))&524287]) + ((1.0 - fRec24[0]) * fRec22[(IOTA-int((1 + int((int(fRec25[0]) & 262143)))))&524287]))));
		double fTemp11 = fRec22[(IOTA-0)&524287];
		double 	fRec21 = max(fConst1, fabs(fTemp11));
		int iTemp12 = int((iRec19[1] < 4096));
		fRec18[0] = ((iTemp12)?max(fRec18[1], fRec21):fRec21);
		iRec19[0] = ((iTemp12)?(1 + iRec19[1]):1);
		fRec20[0] = ((iTemp12)?fRec20[1]:fRec18[1]);
		fbargraph1 = fRec20[0];
		double fTemp13 = ((int((fRec35[1] != 0.0)))?((int(((fRec36[1] > 0.0) & (fRec36[1] < 1.0))))?fRec35[1]:0):((int(((fRec36[1] == 0.0) & (fSlow46 != fRec37[1]))))?fConst2:((int(((fRec36[1] == 1.0) & (fSlow46 != fRec38[1]))))?fConst3:0)));
		fRec35[0] = fTemp13;
		fRec36[0] = max(0.0, min(1.0, (fRec36[1] + fTemp13)));
		fRec37[0] = ((int(((fRec36[1] >= 1.0) & (fRec38[1] != fSlow46))))?fSlow46:fRec37[1]);
		fRec38[0] = ((int(((fRec36[1] <= 0.0) & (fRec37[1] != fSlow46))))?fSlow46:fRec38[1]);
		fRec39[0] = (fSlow47 + (0.999 * fRec39[1]));
		double fTemp14 = (fSlow4 * fRec40[1]);
		fRec42[0] = ((fSlow39 * ((fSlow51 * fVec2[1]) + (fSlow50 * fTemp4))) + (fSlow18 * fRec42[1]));
		fRec41[0] = (fRec42[0] - (fSlow16 * ((fSlow14 * fRec41[2]) + (fSlow12 * fRec41[1]))));
		fRec40[0] = ((fSlow16 * (((fSlow11 * fRec41[0]) + (fSlow52 * fRec41[1])) + (fSlow11 * fRec41[2]))) - (fSlow49 * ((fSlow48 * fRec40[2]) + fTemp14)));
		fRec34[IOTA&524287] = ((fRec40[2] + (fSlow49 * (fTemp14 + (fSlow48 * fRec40[0])))) + (fRec39[0] * ((fRec36[0] * fRec34[(IOTA-int((1 + int((int(fRec38[0]) & 262143)))))&524287]) + ((1.0 - fRec36[0]) * fRec34[(IOTA-int((1 + int((int(fRec37[0]) & 262143)))))&524287]))));
		double fTemp15 = fRec34[(IOTA-0)&524287];
		double 	fRec33 = max(fConst1, fabs(fTemp15));
		int iTemp16 = int((iRec31[1] < 4096));
		fRec30[0] = ((iTemp16)?max(fRec30[1], fRec33):fRec33);
		iRec31[0] = ((iTemp16)?(1 + iRec31[1]):1);
		fRec32[0] = ((iTemp16)?fRec32[1]:fRec30[1]);
		fbargraph2 = fRec32[0];
		double fTemp17 = ((int((fRec48[1] != 0.0)))?((int(((fRec49[1] > 0.0) & (fRec49[1] < 1.0))))?fRec48[1]:0):((int(((fRec49[1] == 0.0) & (fSlow53 != fRec50[1]))))?fConst2:((int(((fRec49[1] == 1.0) & (fSlow53 != fRec51[1]))))?fConst3:0)));
		fRec48[0] = fTemp17;
		fRec49[0] = max(0.0, min(1.0, (fRec49[1] + fTemp17)));
		fRec50[0] = ((int(((fRec49[1] >= 1.0) & (fRec51[1] != fSlow53))))?fSlow53:fRec50[1]);
		fRec51[0] = ((int(((fRec49[1] <= 0.0) & (fRec50[1] != fSlow53))))?fSlow53:fRec51[1]);
		fRec52[0] = (fSlow54 + (0.999 * fRec52[1]));
		double fTemp18 = (fSlow4 * fRec53[1]);
		double fTemp19 = (fSlow12 * fRec54[1]);
		fRec56[0] = ((fSlow38 * ((fSlow58 * fVec1[1]) + (fSlow57 * fTemp2))) + (fSlow27 * fRec56[1]));
		fRec55[0] = (fRec56[0] - (fSlow25 * ((fSlow23 * fRec55[2]) + (fSlow21 * fRec55[1]))));
		fRec54[0] = ((fSlow25 * (((fSlow20 * fRec55[0]) + (fSlow59 * fRec55[1])) + (fSlow20 * fRec55[2]))) - (fSlow56 * ((fSlow55 * fRec54[2]) + fTemp19)));
		fRec53[0] = ((fRec54[2] + (fSlow56 * (fTemp19 + (fSlow55 * fRec54[0])))) - (fSlow49 * ((fSlow48 * fRec53[2]) + fTemp18)));
		fRec47[IOTA&524287] = ((fRec53[2] + (fSlow49 * (fTemp18 + (fSlow48 * fRec53[0])))) + (fRec52[0] * ((fRec49[0] * fRec47[(IOTA-int((1 + int((int(fRec51[0]) & 262143)))))&524287]) + ((1.0 - fRec49[0]) * fRec47[(IOTA-int((1 + int((int(fRec50[0]) & 262143)))))&524287]))));
		double fTemp20 = fRec47[(IOTA-0)&524287];
		double 	fRec46 = max(fConst1, fabs(fTemp20));
		int iTemp21 = int((iRec44[1] < 4096));
		fRec43[0] = ((iTemp21)?max(fRec43[1], fRec46):fRec46);
		iRec44[0] = ((iTemp21)?(1 + iRec44[1]):1);
		fRec45[0] = ((iTemp21)?fRec45[1]:fRec43[1]);
		fbargraph3 = fRec45[0];
		double fTemp22 = ((int((fRec62[1] != 0.0)))?((int(((fRec63[1] > 0.0) & (fRec63[1] < 1.0))))?fRec62[1]:0):((int(((fRec63[1] == 0.0) & (fSlow60 != fRec64[1]))))?fConst2:((int(((fRec63[1] == 1.0) & (fSlow60 != fRec65[1]))))?fConst3:0)));
		fRec62[0] = fTemp22;
		fRec63[0] = max(0.0, min(1.0, (fRec63[1] + fTemp22)));
		fRec64[0] = ((int(((fRec63[1] >= 1.0) & (fRec65[1] != fSlow60))))?fSlow60:fRec64[1]);
		fRec65[0] = ((int(((fRec63[1] <= 0.0) & (fRec64[1] != fSlow60))))?fSlow60:fRec65[1]);
		fRec66[0] = (fSlow61 + (0.999 * fRec66[1]));
		double fTemp23 = (fSlow4 * fRec67[1]);
		double fTemp24 = (fSlow12 * fRec68[1]);
		double fTemp25 = (fSlow21 * fRec69[1]);
		fRec71[0] = ((fSlow37 * ((fSlow64 * fVec0[1]) + (fSlow31 * fVec0[0]))) + (fSlow36 * fRec71[1]));
		fRec70[0] = (fRec71[0] - (fSlow34 * ((fSlow32 * fRec70[2]) + (fSlow30 * fRec70[1]))));
		fRec69[0] = ((fSlow34 * (((fSlow29 * fRec70[0]) + (fSlow65 * fRec70[1])) + (fSlow29 * fRec70[2]))) - (fSlow63 * ((fSlow62 * fRec69[2]) + fTemp25)));
		fRec68[0] = ((fRec69[2] + (fSlow63 * (fTemp25 + (fSlow62 * fRec69[0])))) - (fSlow56 * ((fSlow55 * fRec68[2]) + fTemp24)));
		fRec67[0] = ((fRec68[2] + (fSlow56 * (fTemp24 + (fSlow55 * fRec68[0])))) - (fSlow49 * ((fSlow48 * fRec67[2]) + fTemp23)));
		fRec61[IOTA&524287] = ((fRec67[2] + (fSlow49 * (fTemp23 + (fSlow48 * fRec67[0])))) + (fRec66[0] * ((fRec63[0] * fRec61[(IOTA-int((1 + int((int(fRec65[0]) & 262143)))))&524287]) + ((1.0 - fRec63[0]) * fRec61[(IOTA-int((1 + int((int(fRec64[0]) & 262143)))))&524287]))));
		double fTemp26 = fRec61[(IOTA-0)&524287];
		double 	fRec60 = max(fConst1, fabs(fTemp26));
		int iTemp27 = int((iRec58[1] < 4096));
		fRec57[0] = ((iTemp27)?max(fRec57[1], fRec60):fRec60);
		iRec58[0] = ((iTemp27)?(1 + iRec58[1]):1);
		fRec59[0] = ((iTemp27)?fRec59[1]:fRec57[1]);
		fbargraph4 = fRec59[0];
		output0[i] = (FAUSTFLOAT)((((fTemp26 + fTemp20) + fTemp15) + fTemp11) + fTemp8);
		// post processing
		fRec59[1] = fRec59[0];
		iRec58[1] = iRec58[0];
		fRec57[1] = fRec57[0];
		fRec67[2] = fRec67[1]; fRec67[1] = fRec67[0];
		fRec68[2] = fRec68[1]; fRec68[1] = fRec68[0];
		fRec69[2] = fRec69[1]; fRec69[1] = fRec69[0];
		fRec70[2] = fRec70[1]; fRec70[1] = fRec70[0];
		fRec71[1] = fRec71[0];
		fRec66[1] = fRec66[0];
		fRec65[1] = fRec65[0];
		fRec64[1] = fRec64[0];
		fRec63[1] = fRec63[0];
		fRec62[1] = fRec62[0];
		fRec45[1] = fRec45[0];
		iRec44[1] = iRec44[0];
		fRec43[1] = fRec43[0];
		fRec53[2] = fRec53[1]; fRec53[1] = fRec53[0];
		fRec54[2] = fRec54[1]; fRec54[1] = fRec54[0];
		fRec55[2] = fRec55[1]; fRec55[1] = fRec55[0];
		fRec56[1] = fRec56[0];
		fRec52[1] = fRec52[0];
		fRec51[1] = fRec51[0];
		fRec50[1] = fRec50[0];
		fRec49[1] = fRec49[0];
		fRec48[1] = fRec48[0];
		fRec32[1] = fRec32[0];
		iRec31[1] = iRec31[0];
		fRec30[1] = fRec30[0];
		fRec40[2] = fRec40[1]; fRec40[1] = fRec40[0];
		fRec41[2] = fRec41[1]; fRec41[1] = fRec41[0];
		fRec42[1] = fRec42[0];
		fRec39[1] = fRec39[0];
		fRec38[1] = fRec38[0];
		fRec37[1] = fRec37[0];
		fRec36[1] = fRec36[0];
		fRec35[1] = fRec35[0];
		fRec20[1] = fRec20[0];
		iRec19[1] = iRec19[0];
		fRec18[1] = fRec18[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec27[1] = fRec27[0];
		fRec26[1] = fRec26[0];
		fRec25[1] = fRec25[0];
		fRec24[1] = fRec24[0];
		fRec23[1] = fRec23[0];
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec3[1] = fVec3[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fVec2[1] = fVec2[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec1[1] = fVec1[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[1] = fRec17[0];
		fVec0[1] = fVec0[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("mbe.crossover_b1_b2",N_("Crossover B1-B2 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider2, 8e+01, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbe.crossover_b2_b3",N_("Crossover B2-B3 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider3, 2.1e+02, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbe.crossover_b3_b4",N_("Crossover B3-B4 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider4, 1.7e+03, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbe.crossover_b4_b5",N_("Crossover B4-B5 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider5, 5e+03, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbe.percent1","","S","",&fslider1, 1e+01, 0.0, 1e+02, 0.1);
	reg.registerVar("mbe.percent2","","S","",&fslider7, 3e+01, 0.0, 1e+02, 0.1);
	reg.registerVar("mbe.percent3","","S","",&fslider9, 45.0, 0.0, 1e+02, 0.1);
	reg.registerVar("mbe.percent4","","S","",&fslider11, 2e+01, 0.0, 1e+02, 0.1);
	reg.registerVar("mbe.percent5","","S","",&fslider13, 0.0, 0.0, 1e+02, 0.1);
	reg.registerVar("mbe.time1","","S",N_("Echo in Beats per Minute"),&fslider0, 3e+01, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbe.time2","","S",N_("Echo in Beats per Minute"),&fslider6, 6e+01, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbe.time3","","S",N_("Echo in Beats per Minute"),&fslider8, 1.2e+02, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbe.time4","","S",N_("Echo in Beats per Minute"),&fslider10, 1.5e+02, 24.0, 3.6e+02, 1.0);
	reg.registerVar("mbe.time5","","S",N_("Echo in Beats per Minute"),&fslider12, 2.4e+02, 24.0, 3.6e+02, 1.0);
	reg.registerNonMidiFloatVar("mbe.v1",&fbargraph0, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbe.v2",&fbargraph1, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbe.v3",&fbargraph2, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbe.v4",&fbargraph3, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbe.v5",&fbargraph4, false, true, -70.0, -70.0, 4.0, 0.00001);
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
b.openpaintampBox("");
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
b.closeBox();

b.openHorizontalBox(N_("Band 2"));
b.openVerticalBox("");
b.openpaintampBox("");
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
b.closeBox();

b.openHorizontalBox(N_("Band 3"));
b.openVerticalBox("");
b.openpaintampBox("");
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
b.closeBox();

b.openHorizontalBox(N_("Band 4"));
b.openVerticalBox("");
b.openpaintampBox("");
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
b.closeBox();

b.openHorizontalBox(N_("Band 5"));
b.openVerticalBox("");
b.openpaintampBox("");
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

} // end namespace mbe
} // end namespace pluginlib
