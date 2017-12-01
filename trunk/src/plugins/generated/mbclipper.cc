// generated from file '../src/plugins/mbclipper.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "clipping.h"

namespace pluginlib {
namespace mbclipper {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider0;
	double 	fConst2;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	double 	fRec12[2];
	double 	fVec1[2];
	double 	fRec11[2];
	double 	fRec10[3];
	double 	fVec2[2];
	double 	fRec9[2];
	double 	fRec8[3];
	double 	fVec3[2];
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fVec4[2];
	double 	fRec5[2];
	double 	fRec4[3];
	FAUSTFLOAT 	fslider4;
	double 	fRec13[2];
	double 	fRec0[2];
	int 	iRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph0;
	double 	fRec19[2];
	double 	fRec18[3];
	FAUSTFLOAT 	fslider5;
	double 	fRec20[2];
	double 	fRec14[2];
	int 	iRec15[2];
	double 	fRec16[2];
	FAUSTFLOAT 	fbargraph1;
	double 	fRec27[2];
	double 	fRec26[3];
	double 	fRec25[3];
	FAUSTFLOAT 	fslider6;
	double 	fRec28[2];
	double 	fRec21[2];
	int 	iRec22[2];
	double 	fRec23[2];
	FAUSTFLOAT 	fbargraph2;
	double 	fRec36[2];
	double 	fRec35[3];
	double 	fRec34[3];
	double 	fRec33[3];
	FAUSTFLOAT 	fslider7;
	double 	fRec37[2];
	double 	fRec29[2];
	int 	iRec30[2];
	double 	fRec31[2];
	FAUSTFLOAT 	fbargraph3;
	double 	fRec46[2];
	double 	fRec45[3];
	double 	fRec44[3];
	double 	fRec43[3];
	double 	fRec42[3];
	FAUSTFLOAT 	fslider8;
	double 	fRec47[2];
	double 	fRec38[2];
	int 	iRec39[2];
	double 	fRec40[2];
	FAUSTFLOAT 	fbargraph4;
	FAUSTFLOAT 	fslider9;
	double 	fRec48[2];

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
	id = "mbclip";
	name = N_("MultiBand Clipper");
	groups = 0;
	description = N_("MultiBand Clipper"); // description (tooltip)
	category = N_("Distortion");       // category
	shortname = N_("MB Clipper");     // shortname
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
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) iRec15[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) iRec22[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
	for (int i=0; i<3; i++) fRec35[i] = 0;
	for (int i=0; i<3; i++) fRec34[i] = 0;
	for (int i=0; i<3; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) iRec30[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<2; i++) fRec46[i] = 0;
	for (int i=0; i<3; i++) fRec45[i] = 0;
	for (int i=0; i<3; i++) fRec44[i] = 0;
	for (int i=0; i<3; i++) fRec43[i] = 0;
	for (int i=0; i<3; i++) fRec42[i] = 0;
	for (int i=0; i<2; i++) fRec47[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) iRec39[i] = 0;
	for (int i=0; i<2; i++) fRec40[i] = 0;
	for (int i=0; i<2; i++) fRec48[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = (1.0 / fConst0);
	fConst2 = (3.141592653589793 / fConst0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = tan((fConst2 * double(fslider0)));
	double 	fSlow1 = (1.0 / fSlow0);
	double 	fSlow2 = (1 + ((fSlow1 - 1.0000000000000004) / fSlow0));
	double 	fSlow3 = (1.0 / faustpower<2>(fSlow0));
	double 	fSlow4 = (2 * (1 - fSlow3));
	double 	fSlow5 = (1.0 / (1 + ((fSlow1 + 1.0000000000000004) / fSlow0)));
	double 	fSlow6 = tan((fConst2 * double(fslider1)));
	double 	fSlow7 = (1.0 / fSlow6);
	double 	fSlow8 = (1 + ((fSlow7 - 1.0000000000000004) / fSlow6));
	double 	fSlow9 = (1.0 / faustpower<2>(fSlow6));
	double 	fSlow10 = (2 * (1 - fSlow9));
	double 	fSlow11 = (1 + ((fSlow7 + 1.0000000000000004) / fSlow6));
	double 	fSlow12 = (1.0 / fSlow11);
	double 	fSlow13 = tan((fConst2 * double(fslider2)));
	double 	fSlow14 = (1.0 / fSlow13);
	double 	fSlow15 = (1 + ((fSlow14 - 1.0000000000000004) / fSlow13));
	double 	fSlow16 = (1.0 / faustpower<2>(fSlow13));
	double 	fSlow17 = (2 * (1 - fSlow16));
	double 	fSlow18 = (1 + ((fSlow14 + 1.0000000000000004) / fSlow13));
	double 	fSlow19 = (1.0 / fSlow18);
	double 	fSlow20 = tan((fConst2 * double(fslider3)));
	double 	fSlow21 = (1.0 / faustpower<2>(fSlow20));
	double 	fSlow22 = (2 * (1 - fSlow21));
	double 	fSlow23 = (1.0 / fSlow20);
	double 	fSlow24 = (1 + ((fSlow23 - 1.0000000000000004) / fSlow20));
	double 	fSlow25 = (1 + ((1.0000000000000004 + fSlow23) / fSlow20));
	double 	fSlow26 = (1.0 / fSlow25);
	double 	fSlow27 = (1 + fSlow23);
	double 	fSlow28 = (1.0 / fSlow27);
	double 	fSlow29 = (0 - ((1 - fSlow23) / fSlow27));
	double 	fSlow30 = (1 + fSlow14);
	double 	fSlow31 = (1.0 / fSlow30);
	double 	fSlow32 = (0 - ((1 - fSlow14) / fSlow30));
	double 	fSlow33 = (1 + fSlow7);
	double 	fSlow34 = (1.0 / fSlow33);
	double 	fSlow35 = (0 - ((1 - fSlow7) / fSlow33));
	double 	fSlow36 = (1 + fSlow1);
	double 	fSlow37 = (1.0 / fSlow36);
	double 	fSlow38 = (0 - ((1 - fSlow1) / fSlow36));
	double 	fSlow39 = (0.0010000000000000009 * double(fslider4));
	double 	fSlow40 = (0 - fSlow1);
	double 	fSlow41 = (1.0 / (fSlow0 * fSlow11));
	double 	fSlow42 = (2 * (0 - fSlow3));
	double 	fSlow43 = (0.0010000000000000009 * double(fslider5));
	double 	fSlow44 = (1 + ((fSlow1 - 1.0) / fSlow0));
	double 	fSlow45 = (1.0 / (1 + ((1.0 + fSlow1) / fSlow0)));
	double 	fSlow46 = (0 - fSlow7);
	double 	fSlow47 = (1.0 / (fSlow6 * fSlow18));
	double 	fSlow48 = (2 * (0 - fSlow9));
	double 	fSlow49 = (0.0010000000000000009 * double(fslider6));
	double 	fSlow50 = (1 + ((fSlow7 - 1.0) / fSlow6));
	double 	fSlow51 = (1.0 / (1 + ((1.0 + fSlow7) / fSlow6)));
	double 	fSlow52 = (0 - fSlow14);
	double 	fSlow53 = (1.0 / (fSlow13 * fSlow25));
	double 	fSlow54 = (2 * (0 - fSlow16));
	double 	fSlow55 = (0.0010000000000000009 * double(fslider7));
	double 	fSlow56 = (1 + ((fSlow14 - 1.0) / fSlow13));
	double 	fSlow57 = (1.0 / (1 + ((1.0 + fSlow14) / fSlow13)));
	double 	fSlow58 = (0 - fSlow23);
	double 	fSlow59 = (2 * (0 - fSlow21));
	double 	fSlow60 = (0.0010000000000000009 * double(fslider8));
	double 	fSlow61 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider9))));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec12[0] = ((1e-20 * (1 - iVec0[1])) - fRec12[1]);
		double fTemp0 = ((double)input0[i] + fRec12[0]);
		fVec1[0] = fTemp0;
		fRec11[0] = ((fSlow29 * fRec11[1]) + (fSlow28 * (fVec1[0] + fVec1[1])));
		fRec10[0] = (fRec11[0] - (fSlow26 * ((fSlow24 * fRec10[2]) + (fSlow22 * fRec10[1]))));
		double fTemp1 = (fRec10[0] + (fRec10[2] + (2 * fRec10[1])));
		double fTemp2 = (fSlow26 * fTemp1);
		fVec2[0] = fTemp2;
		fRec9[0] = ((fSlow32 * fRec9[1]) + (fSlow31 * (fVec2[0] + fVec2[1])));
		fRec8[0] = (fRec9[0] - (fSlow19 * ((fSlow17 * fRec8[1]) + (fSlow15 * fRec8[2]))));
		double fTemp3 = (fRec8[0] + (fRec8[2] + (2 * fRec8[1])));
		double fTemp4 = (fSlow19 * fTemp3);
		fVec3[0] = fTemp4;
		fRec7[0] = ((fSlow35 * fRec7[1]) + (fSlow34 * (fVec3[0] + fVec3[1])));
		fRec6[0] = (fRec7[0] - (fSlow12 * ((fSlow10 * fRec6[1]) + (fSlow8 * fRec6[2]))));
		double fTemp5 = (fRec6[0] + (fRec6[2] + (2 * fRec6[1])));
		double fTemp6 = (fSlow12 * fTemp5);
		fVec4[0] = fTemp6;
		fRec5[0] = ((fSlow38 * fRec5[1]) + (fSlow37 * (fVec4[0] + fVec4[1])));
		fRec4[0] = (fRec5[0] - (fSlow5 * ((fSlow4 * fRec4[1]) + (fSlow2 * fRec4[2]))));
		fRec13[0] = (fSlow39 + (0.999 * fRec13[1]));
		double fTemp7 = pow(1e+01,(2 * fRec13[0]));
		double fTemp8 = (max(1.0, (1.0 / fTemp7)) * symclip((fSlow5 * (fTemp7 * (fRec4[0] + (fRec4[2] + (2 * fRec4[1])))))));
		double 	fRec3 = max(fConst1, fabs(fTemp8));
		int iTemp9 = int((iRec1[1] < 4096));
		fRec0[0] = ((iTemp9)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp9)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp9)?fRec2[1]:fRec0[1]);
		fbargraph0 = fRec2[0];
		fRec19[0] = ((fSlow38 * fRec19[1]) + (fSlow37 * ((fSlow41 * fTemp5) + (fSlow40 * fVec4[1]))));
		fRec18[0] = (fRec19[0] - (fSlow5 * ((fSlow4 * fRec18[1]) + (fSlow2 * fRec18[2]))));
		fRec20[0] = (fSlow43 + (0.999 * fRec20[1]));
		double fTemp10 = pow(1e+01,(2 * fRec20[0]));
		double fTemp11 = (max(1.0, (1.0 / fTemp10)) * symclip((fSlow5 * (fTemp10 * ((fSlow42 * fRec18[1]) + (fSlow3 * (fRec18[2] + fRec18[0])))))));
		double 	fRec17 = max(fConst1, fabs(fTemp11));
		int iTemp12 = int((iRec15[1] < 4096));
		fRec14[0] = ((iTemp12)?max(fRec14[1], fRec17):fRec17);
		iRec15[0] = ((iTemp12)?(1 + iRec15[1]):1);
		fRec16[0] = ((iTemp12)?fRec16[1]:fRec14[1]);
		fbargraph1 = fRec16[0];
		double fTemp13 = (fSlow4 * fRec25[1]);
		fRec27[0] = ((fSlow35 * fRec27[1]) + (fSlow34 * ((fSlow47 * fTemp3) + (fSlow46 * fVec3[1]))));
		fRec26[0] = (fRec27[0] - (fSlow12 * ((fSlow10 * fRec26[1]) + (fSlow8 * fRec26[2]))));
		fRec25[0] = ((fSlow12 * ((fSlow48 * fRec26[1]) + (fSlow9 * (fRec26[2] + fRec26[0])))) - (fSlow45 * ((fSlow44 * fRec25[2]) + fTemp13)));
		fRec28[0] = (fSlow49 + (0.999 * fRec28[1]));
		double fTemp14 = pow(1e+01,(2 * fRec28[0]));
		double fTemp15 = (max(1.0, (1.0 / fTemp14)) * symclip((fTemp14 * (fRec25[2] + (fSlow45 * (fTemp13 + (fSlow44 * fRec25[0])))))));
		double 	fRec24 = max(fConst1, fabs(fTemp15));
		int iTemp16 = int((iRec22[1] < 4096));
		fRec21[0] = ((iTemp16)?max(fRec21[1], fRec24):fRec24);
		iRec22[0] = ((iTemp16)?(1 + iRec22[1]):1);
		fRec23[0] = ((iTemp16)?fRec23[1]:fRec21[1]);
		fbargraph2 = fRec23[0];
		double fTemp17 = (fSlow4 * fRec33[1]);
		double fTemp18 = (fSlow10 * fRec34[1]);
		fRec36[0] = ((fSlow32 * fRec36[1]) + (fSlow31 * ((fSlow53 * fTemp1) + (fSlow52 * fVec2[1]))));
		fRec35[0] = (fRec36[0] - (fSlow19 * ((fSlow17 * fRec35[1]) + (fSlow15 * fRec35[2]))));
		fRec34[0] = ((fSlow19 * ((fSlow54 * fRec35[1]) + (fSlow16 * (fRec35[2] + fRec35[0])))) - (fSlow51 * ((fSlow50 * fRec34[2]) + fTemp18)));
		fRec33[0] = ((fRec34[2] + (fSlow51 * (fTemp18 + (fSlow50 * fRec34[0])))) - (fSlow45 * ((fSlow44 * fRec33[2]) + fTemp17)));
		fRec37[0] = (fSlow55 + (0.999 * fRec37[1]));
		double fTemp19 = pow(1e+01,(2 * fRec37[0]));
		double fTemp20 = (max(1.0, (1.0 / fTemp19)) * symclip((fTemp19 * (fRec33[2] + (fSlow45 * (fTemp17 + (fSlow44 * fRec33[0])))))));
		double 	fRec32 = max(fConst1, fabs(fTemp20));
		int iTemp21 = int((iRec30[1] < 4096));
		fRec29[0] = ((iTemp21)?max(fRec29[1], fRec32):fRec32);
		iRec30[0] = ((iTemp21)?(1 + iRec30[1]):1);
		fRec31[0] = ((iTemp21)?fRec31[1]:fRec29[1]);
		fbargraph3 = fRec31[0];
		double fTemp22 = (fSlow4 * fRec42[1]);
		double fTemp23 = (fSlow10 * fRec43[1]);
		double fTemp24 = (fSlow17 * fRec44[1]);
		fRec46[0] = ((fSlow29 * fRec46[1]) + (fSlow28 * ((fSlow23 * fVec1[0]) + (fSlow58 * fVec1[1]))));
		fRec45[0] = (fRec46[0] - (fSlow26 * ((fSlow24 * fRec45[2]) + (fSlow22 * fRec45[1]))));
		fRec44[0] = ((fSlow26 * ((fSlow59 * fRec45[1]) + (fSlow21 * (fRec45[2] + fRec45[0])))) - (fSlow57 * ((fSlow56 * fRec44[2]) + fTemp24)));
		fRec43[0] = ((fRec44[2] + (fSlow57 * (fTemp24 + (fSlow56 * fRec44[0])))) - (fSlow51 * ((fSlow50 * fRec43[2]) + fTemp23)));
		fRec42[0] = ((fRec43[2] + (fSlow51 * (fTemp23 + (fSlow50 * fRec43[0])))) - (fSlow45 * ((fSlow44 * fRec42[2]) + fTemp22)));
		fRec47[0] = (fSlow60 + (0.999 * fRec47[1]));
		double fTemp25 = pow(1e+01,(2 * fRec47[0]));
		double fTemp26 = (max(1.0, (1.0 / fTemp25)) * symclip((fTemp25 * (fRec42[2] + (fSlow45 * (fTemp22 + (fSlow44 * fRec42[0])))))));
		double 	fRec41 = max(fConst1, fabs(fTemp26));
		int iTemp27 = int((iRec39[1] < 4096));
		fRec38[0] = ((iTemp27)?max(fRec38[1], fRec41):fRec41);
		iRec39[0] = ((iTemp27)?(1 + iRec39[1]):1);
		fRec40[0] = ((iTemp27)?fRec40[1]:fRec38[1]);
		fbargraph4 = fRec40[0];
		fRec48[0] = (fSlow61 + (0.999 * fRec48[1]));
		output0[i] = (FAUSTFLOAT)(fRec48[0] * ((((fTemp26 + fTemp20) + fTemp15) + fTemp11) + fTemp8));
		// post processing
		fRec48[1] = fRec48[0];
		fRec40[1] = fRec40[0];
		iRec39[1] = iRec39[0];
		fRec38[1] = fRec38[0];
		fRec47[1] = fRec47[0];
		fRec42[2] = fRec42[1]; fRec42[1] = fRec42[0];
		fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
		fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
		fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
		fRec46[1] = fRec46[0];
		fRec31[1] = fRec31[0];
		iRec30[1] = iRec30[0];
		fRec29[1] = fRec29[0];
		fRec37[1] = fRec37[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec34[2] = fRec34[1]; fRec34[1] = fRec34[0];
		fRec35[2] = fRec35[1]; fRec35[1] = fRec35[0];
		fRec36[1] = fRec36[0];
		fRec23[1] = fRec23[0];
		iRec22[1] = iRec22[0];
		fRec21[1] = fRec21[0];
		fRec28[1] = fRec28[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec16[1] = fRec16[0];
		iRec15[1] = iRec15[0];
		fRec14[1] = fRec14[0];
		fRec20[1] = fRec20[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec0[1] = fRec0[0];
		fRec13[1] = fRec13[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec4[1] = fVec4[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fVec3[1] = fVec3[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fVec2[1] = fVec2[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec1[1] = fVec1[0];
		fRec12[1] = fRec12[0];
		iVec0[1] = iVec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("mbclip.Drive1","","S",N_("Amount of distortion"),&fslider4, 0.33, 0.0, 1.0, 0.01);
	reg.registerVar("mbclip.Drive2","","S",N_("Amount of distortion"),&fslider5, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("mbclip.Drive3","","S",N_("Amount of distortion"),&fslider6, 0.65, 0.0, 1.0, 0.01);
	reg.registerVar("mbclip.Drive4","","S",N_("Amount of distortion"),&fslider7, 0.33, 0.0, 1.0, 0.01);
	reg.registerVar("mbclip.Drive5","","S",N_("Amount of distortion"),&fslider8, 0.1, 0.0, 1.0, 0.01);
	reg.registerVar("mbclip.Gain","","S","",&fslider9, 0.0, -4e+01, 4.0, 0.1);
	reg.registerVar("mbclip.crossover_b1_b2",N_("Crossover B1-B2 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fslider0, 8e+01, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbclip.crossover_b2_b3",N_("Crossover B2-B3 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fslider1, 2.1e+02, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbclip.crossover_b3_b4",N_("Crossover B3-B4 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fslider2, 1.7e+03, 2e+01, 2e+04, 1.08);
	reg.registerVar("mbclip.crossover_b4_b5",N_("Crossover B4-B5 (hz)"),"SL",N_("Crossover fi.bandpass frequency"),&fslider3, 5e+03, 2e+01, 2e+04, 1.08);
	reg.registerNonMidiFloatVar("mbclip.v1",&fbargraph0, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbclip.v2",&fbargraph1, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbclip.v3",&fbargraph2, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbclip.v4",&fbargraph3, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("mbclip.v5",&fbargraph4, false, true, -70.0, -70.0, 4.0, 0.00001);
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
                                    <property name=\"label\" translatable=\"yes\">Drive</property>\n\
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
                                    <property name=\"var_id\">mbclip.Drive1</property>\n\
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
                              <placeholder/>\n\
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
                                <property name=\"var_id\">mbclip.crossover_b1_b2</property>\n\
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
                                    <property name=\"label\" translatable=\"yes\">Drive</property>\n\
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
                                    <property name=\"var_id\">mbclip.Drive2</property>\n\
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
                              <placeholder/>\n\
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
                                <property name=\"var_id\">mbclip.crossover_b1_b2</property>\n\
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
                                <property name=\"var_id\">mbclip.crossover_b2_b3</property>\n\
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
                                    <property name=\"label\" translatable=\"yes\">Drive</property>\n\
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
                                    <property name=\"var_id\">mbclip.Drive3</property>\n\
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
                              <placeholder/>\n\
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
                                <property name=\"var_id\">mbclip.crossover_b2_b3</property>\n\
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
                                <property name=\"var_id\">mbclip.crossover_b3_b4</property>\n\
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
                                    <property name=\"label\" translatable=\"yes\">Drive</property>\n\
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
                                    <property name=\"var_id\">mbclip.Drive4</property>\n\
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
                              <placeholder/>\n\
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
                                <property name=\"var_id\">mbclip.crossover_b3_b4</property>\n\
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
                                <property name=\"var_id\">mbclip.crossover_b4_b5</property>\n\
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
                                    <property name=\"label\" translatable=\"yes\">Drive</property>\n\
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
                                    <property name=\"var_id\">mbclip.Drive5</property>\n\
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
                              <placeholder/>\n\
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
                                <property name=\"var_id\">mbclip.crossover_b4_b5</property>\n\
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
                        <property name=\"var_id\">mbclip.Gain</property>\n\
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
                            <property name=\"var_id\">mbclip.v1</property>\n\
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
                            <property name=\"var_id\">mbclip.v2</property>\n\
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
                            <property name=\"var_id\">mbclip.v3</property>\n\
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
                            <property name=\"var_id\">mbclip.v4</property>\n\
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
                            <property name=\"var_id\">mbclip.v5</property>\n\
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

} // end namespace mbclipper
} // end namespace pluginlib
