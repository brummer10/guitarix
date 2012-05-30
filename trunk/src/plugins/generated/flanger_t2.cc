// generated from file '../src/plugins/flanger_t2.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace flanger_t2 {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	IOTA;
	double 	fVec0[1024];
	FAUSTFLOAT 	fslider0;
	int 	iVec1[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	int 	iConst0;
	double 	fConst1;
	double 	fRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	double 	fConst2;
	double 	fVec2[1024];
	double 	fRec0[2];
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
	id = "flanger_mono_t2";
	name = N_("Flanger Mono T2");
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
	double 	fSlow1 = (2 - fSlow0);
	double 	fSlow2 = fslider1;
	double 	fSlow3 = (fConst1 * fslider2);
	double 	fSlow4 = sin(fSlow3);
	double 	fSlow5 = cos(fSlow3);
	double 	fSlow6 = (0 - fSlow4);
	double 	fSlow7 = (0.0005 * fslider3);
	double 	fSlow8 = (0.001 * fslider4);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[IOTA&1023] = fTemp0;
		iVec1[0] = 1;
		fRec1[0] = ((fSlow5 * fRec1[1]) + (fSlow4 * fRec2[1]));
		fRec2[0] = ((1 + ((fSlow6 * fRec1[1]) + (fSlow5 * fRec2[1]))) - iVec1[1]);
		double fTemp1 = (fConst2 * (fSlow8 + (fSlow7 * (1 + fRec1[0]))));
		int iTemp2 = int(fTemp1);
		int iTemp3 = int((iTemp2 & 1023));
		int iTemp4 = (1 + iTemp2);
		double fTemp5 = (iTemp4 - fTemp1);
		int iTemp6 = int((int(iTemp4) & 1023));
		double fTemp7 = (fTemp1 - iTemp2);
		double fTemp8 = (((fTemp7 * fVec0[(IOTA-iTemp6)&1023]) + (fTemp5 * fVec0[(IOTA-iTemp3)&1023])) + (fSlow2 * fRec0[1]));
		fVec2[IOTA&1023] = fTemp8;
		fRec0[0] = ((fTemp7 * fVec2[(IOTA-iTemp6)&1023]) + (fTemp5 * fVec2[(IOTA-iTemp3)&1023]));
		output0[i] = (FAUSTFLOAT)(0.5 * ((fSlow0 * fRec0[0]) + (fSlow1 * fVec0[IOTA&1023])));
		// post processing
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
	reg.registerVar("flanger_mono_t2.depth","","S","",&fslider4, 0.5, 0.0, 5.0, 0.01);
	reg.registerVar("flanger_mono_t2.width","","S","",&fslider3, 5.0, 0.0, 1e+01, 0.01);
	reg.registerVar("flanger_mono_t2.freq","","SL","",&fslider2, 0.2, 0.05, 5.0, 1.05);
	reg.registerVar("flanger_mono_t2.feedback","","S","",&fslider1, -0.707, -1.0, 1.0, 0.01);
	reg.registerVar("flanger_mono_t2.wet","","S","",&fslider0, 1.0, 0.0, 1.0, 0.1);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b)
{
#define PARAM(p) ("flanger_mono_t2" "." p)

b.openHorizontalhideBox("");
b.closeBox();
b.create_small_rackknob(PARAM("freq"), 0);
b.create_small_rackknob(PARAM("depth"), 0);
b.create_small_rackknob(PARAM("width"), 0);
b.create_small_rackknob(PARAM("feedback"), 0);
b.create_small_rackknob(PARAM("wet"), 0);

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

extern "C" __attribute__ ((visibility ("default"))) int
get_gx_plugin(unsigned int idx, PluginDef **pplugin)
{
    if (!pplugin) {
        return 1;
    }
    if (idx > 0) {
        return -1;
    }
    *pplugin = new Dsp();
    return 1;
}
} // end namespace flanger_t2
