// generated from file '../src/plugins/flanger_gx.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace flanger_gx {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	IOTA;
	double 	fVec0[1024];
	int 	iVec1[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	int 	iConst0;
	double 	fConst1;
	double 	fRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	double 	fConst2;
	double 	fVec2[1024];
	double 	fRec0[2];
	double 	fVec3[2048];
	double 	fRec3[2];
	void clear_state_f();
	int load_ui_f(const UiBuilder& b);
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b);
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
	id = "flanger_mono_gx";
	name = N_("Flanger GX");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Modulation");       // category
	shortname = "";     // shortname
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
	for (int i=0; i<1024; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) iVec1[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<1024; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2048; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (6.283185307179586 / iConst0);
	fConst2 = (0.5 * iConst0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

inline void Dsp::compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = fslider1;
	double 	fSlow2 = (0.01 * (fSlow1 * min(1, (1 + fSlow0))));
	double 	fSlow3 = (2 - fSlow2);
	double 	fSlow4 = (0.3333333333333333 * ((2 + fabs(fSlow0)) * fslider2));
	double 	fSlow5 = (fConst1 * fslider3);
	double 	fSlow6 = sin(fSlow5);
	double 	fSlow7 = cos(fSlow5);
	double 	fSlow8 = (0 - fSlow6);
	double 	fSlow9 = (0.0005 * fslider4);
	double 	fSlow10 = (0.001 * fslider5);
	double 	fSlow11 = (0.01 * (min(1, (1 - fSlow0)) * fSlow1));
	double 	fSlow12 = (2 - fSlow11);
	double 	fSlow13 = (0 - fSlow4);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[IOTA&1023] = fTemp0;
		iVec1[0] = 1;
		fRec1[0] = ((fSlow7 * fRec1[1]) + (fSlow6 * fRec2[1]));
		fRec2[0] = ((1 + ((fSlow8 * fRec1[1]) + (fSlow7 * fRec2[1]))) - iVec1[1]);
		double fTemp1 = (fSlow10 + (fSlow9 * (1 + fRec1[0])));
		double fTemp2 = (fConst2 * fTemp1);
		int iTemp3 = int(fTemp2);
		int iTemp4 = int((iTemp3 & 1023));
		int iTemp5 = (1 + iTemp3);
		double fTemp6 = (iTemp5 - fTemp2);
		int iTemp7 = int((int(iTemp5) & 1023));
		double fTemp8 = (fTemp2 - iTemp3);
		double fTemp9 = (((fTemp8 * fVec0[(IOTA-iTemp7)&1023]) + (fTemp6 * fVec0[(IOTA-iTemp4)&1023])) + (fSlow4 * fRec0[1]));
		fVec2[IOTA&1023] = fTemp9;
		fRec0[0] = ((fTemp8 * fVec2[(IOTA-iTemp7)&1023]) + (fTemp6 * fVec2[(IOTA-iTemp4)&1023]));
		double fTemp10 = ((fSlow2 * fRec0[0]) + (fSlow3 * fVec0[IOTA&1023]));
		double fTemp11 = (fTemp10 + (fSlow13 * fRec3[1]));
		fVec3[IOTA&2047] = fTemp11;
		double fTemp12 = (iConst0 * fTemp1);
		int iTemp13 = int(fTemp12);
		int iTemp14 = (1 + iTemp13);
		fRec3[0] = (((fTemp12 - iTemp13) * fVec3[(IOTA-int((int(iTemp14) & 2047)))&2047]) + ((iTemp14 - fTemp12) * fVec3[(IOTA-int((iTemp13 & 2047)))&2047]));
		output0[i] = (FAUSTFLOAT)(0.25 * ((fSlow11 * fRec3[0]) + (fSlow12 * fTemp10)));
		// post processing
		fRec3[1] = fRec3[0];
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		iVec1[1] = iVec1[0];
		IOTA = IOTA+1;
	}
}

void Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("flanger_mono_gx.depth",N_("Depth"),"S","",&fslider5, 0.5, 0.0, 5.0, 0.01);
	reg.registerVar("flanger_mono_gx.width",N_("Width"),"S","",&fslider4, 5.0, 0.0, 1e+01, 0.01);
	reg.registerVar("flanger_mono_gx.freq",N_("Speed"),"SL","",&fslider3, 0.2, 0.05, 1e+01, 1.06);
	reg.registerVar("flanger_mono_gx.feedback",N_("Feedback"),"S","",&fslider2, -0.707, -0.99, 0.99, 0.01);
	reg.registerVar("flanger_mono_gx.wet",N_("Wet"),"S","",&fslider1, 1e+02, 0.0, 1e+02, 1.0);
	reg.registerVar("flanger_mono_gx.mix",N_("Mix"),"S","",&fslider0, 0.0, -1.0, 1.0, 0.1);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b)
{
#define PARAM(p) ("flanger_mono_gx" "." p)

b.openHorizontalhideBox("");
b.create_master_slider(PARAM("wet"), "Dry/Wet");
b.closeBox();

b.openHorizontalBox("");
b.create_small_rackknob(PARAM("freq"), 0);
b.create_small_rackknob(PARAM("depth"), 0);
b.create_small_rackknob(PARAM("width"), 0);
b.create_small_rackknob(PARAM("feedback"), 0);
b.create_small_rackknob(PARAM("mix"), 0);
b.create_small_rackknob(PARAM("wet"), 0);
b.closeBox();

#undef PARAM
	return 0;
}

int Dsp::load_ui_f_static(const UiBuilder& b)
{
	return static_cast<Dsp*>(b.plugin)->load_ui_f(b);
}

PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace flanger_gx
} // end namespace pluginlib
