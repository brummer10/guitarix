// generated from file '../src/plugins/mbd.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace mbd {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	int 	iVec0[2];
	double 	fRec0[2];
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider1;
	double 	fConst2;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	double 	fRec14[2];
	double 	fVec1[2];
	double 	fRec13[2];
	double 	fRec12[3];
	double 	fVec2[2];
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fVec3[2];
	double 	fRec9[2];
	double 	fRec8[3];
	double 	fVec4[2];
	double 	fRec7[2];
	double 	fRec6[3];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	double 	fRec15[2];
	double 	fVec5[2];
	double 	fRec5[2];
	double 	fRec1[2];
	int 	iRec2[2];
	double 	fRec3[2];
	FAUSTFLOAT 	fbargraph0;
	double 	fRec22[2];
	double 	fRec21[3];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	double 	fRec23[2];
	double 	fVec6[2];
	double 	fRec20[2];
	double 	fRec16[2];
	int 	iRec17[2];
	double 	fRec18[2];
	FAUSTFLOAT 	fbargraph1;
	double 	fRec31[2];
	double 	fRec30[3];
	double 	fRec29[3];
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fslider10;
	double 	fRec32[2];
	double 	fVec7[2];
	double 	fRec28[2];
	double 	fRec24[2];
	int 	iRec25[2];
	double 	fRec26[2];
	FAUSTFLOAT 	fbargraph2;
	double 	fRec41[2];
	double 	fRec40[3];
	double 	fRec39[3];
	double 	fRec38[3];
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT 	fslider12;
	double 	fRec42[2];
	double 	fVec8[2];
	double 	fRec37[2];
	double 	fRec33[2];
	int 	iRec34[2];
	double 	fRec35[2];
	FAUSTFLOAT 	fbargraph3;
	double 	fRec52[2];
	double 	fRec51[3];
	double 	fRec50[3];
	double 	fRec49[3];
	double 	fRec48[3];
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fslider14;
	double 	fRec53[2];
	double 	fVec9[2];
	double 	fRec47[2];
	double 	fRec43[2];
	int 	iRec44[2];
	double 	fRec45[2];
	FAUSTFLOAT 	fbargraph4;
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
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
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) iRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) iRec17[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) iRec25[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec41[i] = 0;
	for (int i=0; i<3; i++) fRec40[i] = 0;
	for (int i=0; i<3; i++) fRec39[i] = 0;
	for (int i=0; i<3; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) iRec34[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec52[i] = 0;
	for (int i=0; i<3; i++) fRec51[i] = 0;
	for (int i=0; i<3; i++) fRec50[i] = 0;
	for (int i=0; i<3; i++) fRec49[i] = 0;
	for (int i=0; i<3; i++) fRec48[i] = 0;
	for (int i=0; i<2; i++) fRec53[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fRec43[i] = 0;
	for (int i=0; i<2; i++) iRec44[i] = 0;
	for (int i=0; i<2; i++) fRec45[i] = 0;
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

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider0))));
	double 	fSlow1 = tan((fConst2 * double(fslider1)));
	double 	fSlow2 = (1.0 / faustpower<2>(fSlow1));
	double 	fSlow3 = (2 * (1 - fSlow2));
	double 	fSlow4 = (1.0 / fSlow1);
	double 	fSlow5 = (1 + ((fSlow4 - 1.0000000000000004) / fSlow1));
	double 	fSlow6 = (1 + ((fSlow4 + 1.0000000000000004) / fSlow1));
	double 	fSlow7 = (1.0 / fSlow6);
	double 	fSlow8 = tan((fConst2 * double(fslider2)));
	double 	fSlow9 = (1.0 / faustpower<2>(fSlow8));
	double 	fSlow10 = (2 * (1 - fSlow9));
	double 	fSlow11 = (1.0 / fSlow8);
	double 	fSlow12 = (1 + ((fSlow11 - 1.0000000000000004) / fSlow8));
	double 	fSlow13 = (1 + ((fSlow11 + 1.0000000000000004) / fSlow8));
	double 	fSlow14 = (1.0 / fSlow13);
	double 	fSlow15 = tan((fConst2 * double(fslider3)));
	double 	fSlow16 = (1.0 / faustpower<2>(fSlow15));
	double 	fSlow17 = (2 * (1 - fSlow16));
	double 	fSlow18 = (1.0 / fSlow15);
	double 	fSlow19 = (1 + ((fSlow18 - 1.0000000000000004) / fSlow15));
	double 	fSlow20 = (1 + ((fSlow18 + 1.0000000000000004) / fSlow15));
	double 	fSlow21 = (1.0 / fSlow20);
	double 	fSlow22 = tan((fConst2 * double(fslider4)));
	double 	fSlow23 = (1.0 / faustpower<2>(fSlow22));
	double 	fSlow24 = (2 * (1 - fSlow23));
	double 	fSlow25 = (1.0 / fSlow22);
	double 	fSlow26 = (1 + ((fSlow25 - 1.0000000000000004) / fSlow22));
	double 	fSlow27 = (1 + ((1.0000000000000004 + fSlow25) / fSlow22));
	double 	fSlow28 = (1.0 / fSlow27);
	double 	fSlow29 = (1 + fSlow25);
	double 	fSlow30 = (1.0 / fSlow29);
	double 	fSlow31 = (0 - ((1 - fSlow25) / fSlow29));
	double 	fSlow32 = (1 + fSlow18);
	double 	fSlow33 = (1.0 / fSlow32);
	double 	fSlow34 = (0 - ((1 - fSlow18) / fSlow32));
	double 	fSlow35 = (1 + fSlow11);
	double 	fSlow36 = (1.0 / fSlow35);
	double 	fSlow37 = (0 - ((1 - fSlow11) / fSlow35));
	double 	fSlow38 = (1 + fSlow4);
	double 	fSlow39 = (1.0 / fSlow38);
	double 	fSlow40 = (0 - ((1 - fSlow4) / fSlow38));
	double 	fSlow41 = (pow(1e+01,(2 * double(fslider5))) / fSlow6);
	double 	fSlow42 = (0.0010000000000000009 * double(fslider6));
	double 	fSlow43 = (0 - fSlow4);
	double 	fSlow44 = (1.0 / (fSlow1 * fSlow13));
	double 	fSlow45 = (2 * (0 - fSlow2));
	double 	fSlow46 = (pow(1e+01,(2 * double(fslider7))) / fSlow6);
	double 	fSlow47 = (0.0010000000000000009 * double(fslider8));
	double 	fSlow48 = (1 + ((fSlow4 - 1.0) / fSlow1));
	double 	fSlow49 = (1.0 / (1 + ((1.0 + fSlow4) / fSlow1)));
	double 	fSlow50 = (0 - fSlow11);
	double 	fSlow51 = (1.0 / (fSlow8 * fSlow20));
	double 	fSlow52 = (2 * (0 - fSlow9));
	double 	fSlow53 = pow(1e+01,(2 * double(fslider9)));
	double 	fSlow54 = (0.0010000000000000009 * double(fslider10));
	double 	fSlow55 = (1 + ((fSlow11 - 1.0) / fSlow8));
	double 	fSlow56 = (1.0 / (1 + ((1.0 + fSlow11) / fSlow8)));
	double 	fSlow57 = (0 - fSlow18);
	double 	fSlow58 = (1.0 / (fSlow15 * fSlow27));
	double 	fSlow59 = (2 * (0 - fSlow16));
	double 	fSlow60 = pow(1e+01,(2 * double(fslider11)));
	double 	fSlow61 = (0.0010000000000000009 * double(fslider12));
	double 	fSlow62 = (1 + ((fSlow18 - 1.0) / fSlow15));
	double 	fSlow63 = (1.0 / (1 + ((1.0 + fSlow18) / fSlow15)));
	double 	fSlow64 = (0 - fSlow25);
	double 	fSlow65 = (2 * (0 - fSlow23));
	double 	fSlow66 = pow(1e+01,(2 * double(fslider13)));
	double 	fSlow67 = (0.0010000000000000009 * double(fslider14));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec0[0] = ((0.999 * fRec0[1]) + fSlow0);
		fRec14[0] = ((1e-20 * (1 - iVec0[1])) - fRec14[1]);
		double fTemp0 = ((double)input0[i] + fRec14[0]);
		fVec1[0] = fTemp0;
		fRec13[0] = ((fSlow31 * fRec13[1]) + (fSlow30 * (fVec1[0] + fVec1[1])));
		fRec12[0] = (fRec13[0] - (fSlow28 * ((fSlow26 * fRec12[2]) + (fSlow24 * fRec12[1]))));
		double fTemp1 = (fRec12[2] + (fRec12[0] + (2 * fRec12[1])));
		double fTemp2 = (fSlow28 * fTemp1);
		fVec2[0] = fTemp2;
		fRec11[0] = ((fSlow34 * fRec11[1]) + (fSlow33 * (fVec2[0] + fVec2[1])));
		fRec10[0] = (fRec11[0] - (fSlow21 * ((fSlow19 * fRec10[2]) + (fSlow17 * fRec10[1]))));
		double fTemp3 = (fRec10[2] + (fRec10[0] + (2 * fRec10[1])));
		double fTemp4 = (fSlow21 * fTemp3);
		fVec3[0] = fTemp4;
		fRec9[0] = ((fSlow37 * fRec9[1]) + (fSlow36 * (fVec3[0] + fVec3[1])));
		fRec8[0] = (fRec9[0] - (fSlow14 * ((fSlow12 * fRec8[2]) + (fSlow10 * fRec8[1]))));
		double fTemp5 = (fRec8[2] + (fRec8[0] + (2 * fRec8[1])));
		double fTemp6 = (fSlow14 * fTemp5);
		fVec4[0] = fTemp6;
		fRec7[0] = ((fSlow40 * fRec7[1]) + (fSlow39 * (fVec4[0] + fVec4[1])));
		fRec6[0] = (fRec7[0] - (fSlow7 * ((fSlow5 * fRec6[2]) + (fSlow3 * fRec6[1]))));
		fRec15[0] = (fSlow42 + (0.999 * fRec15[1]));
		double fTemp7 = max((double)-1, min((double)1, (fRec15[0] + (fSlow41 * (fRec6[2] + (fRec6[0] + (2 * fRec6[1])))))));
		double fTemp8 = (fTemp7 * (1 - (0.3333333333333333 * faustpower<2>(fTemp7))));
		fVec5[0] = fTemp8;
		fRec5[0] = (((0.995 * fRec5[1]) + fVec5[0]) - fVec5[1]);
		double 	fRec4 = max(fConst1, fabs(fRec5[0]));
		int iTemp9 = int((iRec2[1] < 4096));
		fRec1[0] = ((iTemp9)?max(fRec1[1], fRec4):fRec4);
		iRec2[0] = ((iTemp9)?(1 + iRec2[1]):1);
		fRec3[0] = ((iTemp9)?fRec3[1]:fRec1[1]);
		fbargraph0 = fRec3[0];
		fRec22[0] = ((fSlow40 * fRec22[1]) + (fSlow39 * ((fSlow44 * fTemp5) + (fSlow43 * fVec4[1]))));
		fRec21[0] = (fRec22[0] - (fSlow7 * ((fSlow5 * fRec21[2]) + (fSlow3 * fRec21[1]))));
		fRec23[0] = (fSlow47 + (0.999 * fRec23[1]));
		double fTemp10 = max((double)-1, min((double)1, (fRec23[0] + (fSlow46 * (((fSlow2 * fRec21[0]) + (fSlow45 * fRec21[1])) + (fSlow2 * fRec21[2]))))));
		double fTemp11 = (fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10))));
		fVec6[0] = fTemp11;
		fRec20[0] = (((0.995 * fRec20[1]) + fVec6[0]) - fVec6[1]);
		double 	fRec19 = max(fConst1, fabs(fRec20[0]));
		int iTemp12 = int((iRec17[1] < 4096));
		fRec16[0] = ((iTemp12)?max(fRec16[1], fRec19):fRec19);
		iRec17[0] = ((iTemp12)?(1 + iRec17[1]):1);
		fRec18[0] = ((iTemp12)?fRec18[1]:fRec16[1]);
		fbargraph1 = fRec18[0];
		double fTemp13 = (fSlow3 * fRec29[1]);
		fRec31[0] = ((fSlow37 * fRec31[1]) + (fSlow36 * ((fSlow51 * fTemp3) + (fSlow50 * fVec3[1]))));
		fRec30[0] = (fRec31[0] - (fSlow14 * ((fSlow12 * fRec30[2]) + (fSlow10 * fRec30[1]))));
		fRec29[0] = ((fSlow14 * (((fSlow9 * fRec30[0]) + (fSlow52 * fRec30[1])) + (fSlow9 * fRec30[2]))) - (fSlow49 * ((fSlow48 * fRec29[2]) + fTemp13)));
		fRec32[0] = (fSlow54 + (0.999 * fRec32[1]));
		double fTemp14 = max((double)-1, min((double)1, (fRec32[0] + (fSlow53 * (fRec29[2] + (fSlow49 * (fTemp13 + (fSlow48 * fRec29[0]))))))));
		double fTemp15 = (fTemp14 * (1 - (0.3333333333333333 * faustpower<2>(fTemp14))));
		fVec7[0] = fTemp15;
		fRec28[0] = (((0.995 * fRec28[1]) + fVec7[0]) - fVec7[1]);
		double 	fRec27 = max(fConst1, fabs(fRec28[0]));
		int iTemp16 = int((iRec25[1] < 4096));
		fRec24[0] = ((iTemp16)?max(fRec24[1], fRec27):fRec27);
		iRec25[0] = ((iTemp16)?(1 + iRec25[1]):1);
		fRec26[0] = ((iTemp16)?fRec26[1]:fRec24[1]);
		fbargraph2 = fRec26[0];
		double fTemp17 = (fSlow3 * fRec38[1]);
		double fTemp18 = (fSlow10 * fRec39[1]);
		fRec41[0] = ((fSlow34 * fRec41[1]) + (fSlow33 * ((fSlow58 * fTemp1) + (fSlow57 * fVec2[1]))));
		fRec40[0] = (fRec41[0] - (fSlow21 * ((fSlow19 * fRec40[2]) + (fSlow17 * fRec40[1]))));
		fRec39[0] = ((fSlow21 * (((fSlow16 * fRec40[0]) + (fSlow59 * fRec40[1])) + (fSlow16 * fRec40[2]))) - (fSlow56 * ((fSlow55 * fRec39[2]) + fTemp18)));
		fRec38[0] = ((fRec39[2] + (fSlow56 * (fTemp18 + (fSlow55 * fRec39[0])))) - (fSlow49 * ((fSlow48 * fRec38[2]) + fTemp17)));
		fRec42[0] = (fSlow61 + (0.999 * fRec42[1]));
		double fTemp19 = max((double)-1, min((double)1, (fRec42[0] + (fSlow60 * (fRec38[2] + (fSlow49 * (fTemp17 + (fSlow48 * fRec38[0]))))))));
		double fTemp20 = (fTemp19 * (1 - (0.3333333333333333 * faustpower<2>(fTemp19))));
		fVec8[0] = fTemp20;
		fRec37[0] = (((0.995 * fRec37[1]) + fVec8[0]) - fVec8[1]);
		double 	fRec36 = max(fConst1, fabs(fRec37[0]));
		int iTemp21 = int((iRec34[1] < 4096));
		fRec33[0] = ((iTemp21)?max(fRec33[1], fRec36):fRec36);
		iRec34[0] = ((iTemp21)?(1 + iRec34[1]):1);
		fRec35[0] = ((iTemp21)?fRec35[1]:fRec33[1]);
		fbargraph3 = fRec35[0];
		double fTemp22 = (fSlow3 * fRec48[1]);
		double fTemp23 = (fSlow10 * fRec49[1]);
		double fTemp24 = (fSlow17 * fRec50[1]);
		fRec52[0] = ((fSlow31 * fRec52[1]) + (fSlow30 * ((fSlow25 * fVec1[0]) + (fSlow64 * fVec1[1]))));
		fRec51[0] = (fRec52[0] - (fSlow28 * ((fSlow26 * fRec51[2]) + (fSlow24 * fRec51[1]))));
		fRec50[0] = ((fSlow28 * (((fSlow23 * fRec51[0]) + (fSlow65 * fRec51[1])) + (fSlow23 * fRec51[2]))) - (fSlow63 * ((fSlow62 * fRec50[2]) + fTemp24)));
		fRec49[0] = ((fRec50[2] + (fSlow63 * (fTemp24 + (fSlow62 * fRec50[0])))) - (fSlow56 * ((fSlow55 * fRec49[2]) + fTemp23)));
		fRec48[0] = ((fRec49[2] + (fSlow56 * (fTemp23 + (fSlow55 * fRec49[0])))) - (fSlow49 * ((fSlow48 * fRec48[2]) + fTemp22)));
		fRec53[0] = (fSlow67 + (0.999 * fRec53[1]));
		double fTemp25 = max((double)-1, min((double)1, (fRec53[0] + (fSlow66 * (fRec48[2] + (fSlow49 * (fTemp22 + (fSlow48 * fRec48[0]))))))));
		double fTemp26 = (fTemp25 * (1 - (0.3333333333333333 * faustpower<2>(fTemp25))));
		fVec9[0] = fTemp26;
		fRec47[0] = (((0.995 * fRec47[1]) + fVec9[0]) - fVec9[1]);
		double 	fRec46 = max(fConst1, fabs(fRec47[0]));
		int iTemp27 = int((iRec44[1] < 4096));
		fRec43[0] = ((iTemp27)?max(fRec43[1], fRec46):fRec46);
		iRec44[0] = ((iTemp27)?(1 + iRec44[1]):1);
		fRec45[0] = ((iTemp27)?fRec45[1]:fRec43[1]);
		fbargraph4 = fRec45[0];
		output0[i] = (FAUSTFLOAT)(((((fRec47[0] + fRec37[0]) + fRec28[0]) + fRec20[0]) + fRec5[0]) * fRec0[0]);
		// post processing
		fRec45[1] = fRec45[0];
		iRec44[1] = iRec44[0];
		fRec43[1] = fRec43[0];
		fRec47[1] = fRec47[0];
		fVec9[1] = fVec9[0];
		fRec53[1] = fRec53[0];
		fRec48[2] = fRec48[1]; fRec48[1] = fRec48[0];
		fRec49[2] = fRec49[1]; fRec49[1] = fRec49[0];
		fRec50[2] = fRec50[1]; fRec50[1] = fRec50[0];
		fRec51[2] = fRec51[1]; fRec51[1] = fRec51[0];
		fRec52[1] = fRec52[0];
		fRec35[1] = fRec35[0];
		iRec34[1] = iRec34[0];
		fRec33[1] = fRec33[0];
		fRec37[1] = fRec37[0];
		fVec8[1] = fVec8[0];
		fRec42[1] = fRec42[0];
		fRec38[2] = fRec38[1]; fRec38[1] = fRec38[0];
		fRec39[2] = fRec39[1]; fRec39[1] = fRec39[0];
		fRec40[2] = fRec40[1]; fRec40[1] = fRec40[0];
		fRec41[1] = fRec41[0];
		fRec26[1] = fRec26[0];
		iRec25[1] = iRec25[0];
		fRec24[1] = fRec24[0];
		fRec28[1] = fRec28[0];
		fVec7[1] = fVec7[0];
		fRec32[1] = fRec32[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fRec18[1] = fRec18[0];
		iRec17[1] = iRec17[0];
		fRec16[1] = fRec16[0];
		fRec20[1] = fRec20[0];
		fVec6[1] = fVec6[0];
		fRec23[1] = fRec23[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fRec3[1] = fRec3[0];
		iRec2[1] = iRec2[0];
		fRec1[1] = fRec1[0];
		fRec5[1] = fRec5[0];
		fVec5[1] = fVec5[0];
		fRec15[1] = fRec15[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fVec4[1] = fVec4[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fVec3[1] = fVec3[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec2[1] = fVec2[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fVec1[1] = fVec1[0];
		fRec14[1] = fRec14[0];
		fRec0[1] = fRec0[0];
		iVec0[1] = iVec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("mbd.Drive1","","S",N_("Amount of distortion"),&fslider5, 0.0, 0.0, 1.0, 0.01);
	reg.registerVar("mbd.Drive2","","S",N_("Amount of distortion"),&fslider7, 0.0, 0.0, 1.0, 0.01);
	reg.registerVar("mbd.Drive3","","S",N_("Amount of distortion"),&fslider9, 0.0, 0.0, 1.0, 0.01);
	reg.registerVar("mbd.Drive4","","S",N_("Amount of distortion"),&fslider11, 0.0, 0.0, 1.0, 0.01);
	reg.registerVar("mbd.Drive5","","S",N_("Amount of distortion"),&fslider13, 0.0, 0.0, 1.0, 0.01);
	reg.registerVar("mbd.Gain","","S","",&fslider0, 0.0, -4e+01, 4.0, 0.1);
	reg.registerVar("mbd.Offset1","","S",N_("Brings in even harmonics"),&fslider6, 0.0, 0.0, 0.5, 0.01);
	reg.registerVar("mbd.Offset2","","S",N_("Brings in even harmonics"),&fslider8, 0.0, 0.0, 0.5, 0.01);
	reg.registerVar("mbd.Offset3","","S",N_("Brings in even harmonics"),&fslider10, 0.0, 0.0, 0.5, 0.01);
	reg.registerVar("mbd.Offset4","","S",N_("Brings in even harmonics"),&fslider12, 0.0, 0.0, 0.5, 0.01);
	reg.registerVar("mbd.Offset5","","S",N_("Brings in even harmonics"),&fslider14, 0.0, 0.0, 0.5, 0.01);
	reg.registerVar("mbd.crossover_b1_b2",N_("Crossover B1-B2 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider1, 8e+01, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbd.crossover_b2_b3",N_("Crossover B2-B3 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider2, 2.1e+02, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbd.crossover_b3_b4",N_("Crossover B3-B4 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider3, 1.7e+03, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbd.crossover_b4_b5",N_("Crossover B4-B5 (hz)"),"SL",N_("Crossover bandpass frequency"),&fslider4, 5e+03, 2e+01, 2e+04, 1.08);
	reg.registerNonMidiFloatVar("mbd.v1",&fbargraph0, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbd.v2",&fbargraph1, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbd.v3",&fbargraph2, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbd.v4",&fbargraph3, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbd.v5",&fbargraph4, false, true, -70.0, -70.0, 4.0, 0.00001);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<interface>\n\
  <!-- interface-requires gxwidgets 0.0 -->\n\
  <requires lib=\"gtk+\" version=\"2.20\"/>\n\
  <!-- interface-naming-policy project-wide -->\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can_focus\">False</property>\n\
    <child>\n\
      <object class=\"GtkVBox\" id=\"vbox1\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can_focus\">False</property>\n\
        <child>\n\
          <object class=\"GtkHBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GtkHBox\" id=\"hbox1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <child>\n\
                  <object class=\"GtkNotebook\" id=\"notebook:tab_rack\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <child>\n\
                      <object class=\"GtkHBox\" id=\"hbox2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"spacing\">4</property>\n\
                        <child>\n\
                          <object class=\"GtkHBox\" id=\"hbox4\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <child>\n\
                              <object class=\"GtkVBox\" id=\"vbox3\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_81:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Gain</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">False</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GxSmallKnobR\" id=\"gxmediumknob1\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">True</property>\n\
                                    <property name=\"receives_default\">True</property>\n\
                                    <property name=\"show_fill_level\">True</property>\n\
                                    <property name=\"var_id\">mbd.Drive1</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">False</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkVBox\" id=\"vbox4\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_91:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Offset</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">False</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GxSmallKnobR\" id=\"gxmediumknob2\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">True</property>\n\
                                    <property name=\"receives_default\">True</property>\n\
                                    <property name=\"var_id\">mbd.Offset1</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">False</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkTable\" id=\"table1\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"n_rows\">2</property>\n\
                            <property name=\"n_columns\">2</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <property name=\"homogeneous\">True</property>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_141:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                              </object>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob2\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbd.crossover_b1_b2</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"right_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                    </child>\n\
                    <child type=\"tab\">\n\
                      <object class=\"GtkLabel\" id=\"label1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Band 1</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"tab_fill\">False</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkHBox\" id=\"hbox5\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"spacing\">4</property>\n\
                        <child>\n\
                          <object class=\"GtkHBox\" id=\"hbox6\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <child>\n\
                              <object class=\"GtkVBox\" id=\"vbox8\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_8:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Gain</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">False</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GxSmallKnobR\" id=\"gxmediumknob4\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">True</property>\n\
                                    <property name=\"receives_default\">True</property>\n\
                                    <property name=\"show_fill_level\">True</property>\n\
                                    <property name=\"var_id\">mbd.Drive2</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">False</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkVBox\" id=\"vbox9\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_9:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Offset</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">False</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GxSmallKnobR\" id=\"gxmediumknob5\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">True</property>\n\
                                    <property name=\"receives_default\">True</property>\n\
                                    <property name=\"var_id\">mbd.Offset2</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">False</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkTable\" id=\"table2\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"n_rows\">2</property>\n\
                            <property name=\"n_columns\">2</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <property name=\"homogeneous\">True</property>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_13:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">Low</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob7\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbd.crossover_b1_b2</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"right_attach\">2</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_14:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                              </object>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob6\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbd.crossover_b2_b3</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"right_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child type=\"tab\">\n\
                      <object class=\"GtkLabel\" id=\"label2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Band 2</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">1</property>\n\
                        <property name=\"tab_fill\">False</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkHBox\" id=\"hbox7\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"spacing\">4</property>\n\
                        <child>\n\
                          <object class=\"GtkHBox\" id=\"hbox8\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <child>\n\
                              <object class=\"GtkVBox\" id=\"vbox7\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_82:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Gain</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">False</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GxSmallKnobR\" id=\"gxmediumknob7\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">True</property>\n\
                                    <property name=\"receives_default\">True</property>\n\
                                    <property name=\"show_fill_level\">True</property>\n\
                                    <property name=\"var_id\">mbd.Drive3</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">False</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkVBox\" id=\"vbox11\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_92:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Offset</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">False</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GxSmallKnobR\" id=\"gxmediumknob8\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">True</property>\n\
                                    <property name=\"receives_default\">True</property>\n\
                                    <property name=\"var_id\">mbd.Offset3</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">False</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkTable\" id=\"table3\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"n_rows\">2</property>\n\
                            <property name=\"n_columns\">2</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <property name=\"homogeneous\">True</property>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_132:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">Low</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob3\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbd.crossover_b2_b3</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"right_attach\">2</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_142:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                              </object>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob4\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbd.crossover_b3_b4</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"right_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">2</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child type=\"tab\">\n\
                      <object class=\"GtkLabel\" id=\"label3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Band 3</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">2</property>\n\
                        <property name=\"tab_fill\">False</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkHBox\" id=\"hbox9\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"spacing\">4</property>\n\
                        <child>\n\
                          <object class=\"GtkHBox\" id=\"hbox10\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <child>\n\
                              <object class=\"GtkVBox\" id=\"vbox14\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_83:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Gain</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">False</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GxSmallKnobR\" id=\"gxmediumknob10\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">True</property>\n\
                                    <property name=\"receives_default\">True</property>\n\
                                    <property name=\"show_fill_level\">True</property>\n\
                                    <property name=\"var_id\">mbd.Drive4</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">False</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkVBox\" id=\"vbox15\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_93:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Offset</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">False</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GxSmallKnobR\" id=\"gxmediumknob11\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">True</property>\n\
                                    <property name=\"receives_default\">True</property>\n\
                                    <property name=\"var_id\">mbd.Offset4</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">False</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkTable\" id=\"table4\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"n_rows\">2</property>\n\
                            <property name=\"n_columns\">2</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <property name=\"homogeneous\">True</property>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_133:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">Low</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob5\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbd.crossover_b3_b4</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"right_attach\">2</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_143:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">High</property>\n\
                              </object>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob8\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbd.crossover_b4_b5</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"right_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">3</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child type=\"tab\">\n\
                      <object class=\"GtkLabel\" id=\"label4\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Band 4</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">3</property>\n\
                        <property name=\"tab_fill\">False</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkHBox\" id=\"hbox11\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"spacing\">4</property>\n\
                        <child>\n\
                          <object class=\"GtkHBox\" id=\"hbox12\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <child>\n\
                              <object class=\"GtkVBox\" id=\"vbox18\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_84:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Gain</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">False</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GxSmallKnobR\" id=\"gxmediumknob13\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">True</property>\n\
                                    <property name=\"receives_default\">True</property>\n\
                                    <property name=\"show_fill_level\">True</property>\n\
                                    <property name=\"var_id\">mbd.Drive5</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">False</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkVBox\" id=\"vbox19\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label_94:rack_label\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"label\" translatable=\"yes\">Offset</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">False</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GxSmallKnobR\" id=\"gxmediumknob14\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">True</property>\n\
                                    <property name=\"receives_default\">True</property>\n\
                                    <property name=\"var_id\">mbd.Offset5</property>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">False</property>\n\
                                    <property name=\"fill\">False</property>\n\
                                    <property name=\"position\">1</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkTable\" id=\"table5\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"n_rows\">2</property>\n\
                            <property name=\"n_columns\">2</property>\n\
                            <property name=\"row_spacing\">4</property>\n\
                            <property name=\"homogeneous\">True</property>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label_134:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"xalign\">1</property>\n\
                                <property name=\"label\" translatable=\"yes\">Low</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnob\" id=\"gxsmallknob9\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">mbd.crossover_b4_b5</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"left_attach\">1</property>\n\
                                <property name=\"right_attach\">2</property>\n\
                                <property name=\"top_attach\">1</property>\n\
                                <property name=\"bottom_attach\">2</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">4</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child type=\"tab\">\n\
                      <object class=\"GtkLabel\" id=\"label6\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Band 5</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"position\">4</property>\n\
                        <property name=\"tab_fill\">False</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox5\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label_99:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Gain</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxMidKnob\" id=\"gxmidknob1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">mbd.Gain</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label5:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"xalign\">0</property>\n\
                        <property name=\"label\" translatable=\"yes\">Levels</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkHBox\" id=\"hbox3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter1\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbd.v1</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter2\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbd.v2</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter3\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbd.v3</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">2</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter4\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbd.v4</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">3</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxFastMeter\" id=\"gxfastmeter5\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"hold\">0</property>\n\
                            <property name=\"dimen\">0</property>\n\
                            <property name=\"var_id\">mbd.v5</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">4</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">2</property>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">True</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">True</property>\n\
            <property name=\"position\">0</property>\n\
          </packing>\n\
        </child>\n\
        <child>\n\
          <object class=\"GtkHBox\" id=\"minibox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <placeholder/>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">True</property>\n\
            <property name=\"position\">1</property>\n\
          </packing>\n\
        </child>\n\
      </object>\n\
    </child>\n\
  </object>\n\
</interface>\n\
";

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade(glade_def);
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
