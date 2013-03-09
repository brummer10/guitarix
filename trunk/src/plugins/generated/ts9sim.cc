// generated from file '../src/plugins/ts9sim.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "ts9nonlin.h"

namespace pluginlib {
namespace ts9sim {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	double 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	int 	iConst0;
	double 	fConst1;
	double 	fVec0[2];
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	FAUSTFLOAT 	fslider2;
	double 	fConst5;
	double 	fConst6;
	double 	fRec2[2];
	double 	fVec1[2];
	double 	fRec1[2];
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
	id = "ts9sim";
	name = N_("Tube Screamer");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Distortion");       // category
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (3.141592653589793 / iConst0);
	fConst2 = (0.00044179999999999995 * iConst0);
	fConst3 = (1 + fConst2);
	fConst4 = (0 - ((1 - fConst2) / fConst3));
	fConst5 = (9.4e-08 * iConst0);
	fConst6 = (1.0 / fConst3);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

inline void Dsp::compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = (1.0 / tan((fConst1 * fslider1)));
	double 	fSlow2 = (1 + fSlow1);
	double 	fSlow3 = (0 - ((1 - fSlow1) / fSlow2));
	double 	fSlow4 = (fConst5 * ((500000 * fslider2) + 55700));
	double 	fSlow5 = (1 + fSlow4);
	double 	fSlow6 = (1 - fSlow4);
	double 	fSlow7 = (1.0 / fSlow2);
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec2[0] = ((fConst6 * ((fSlow6 * fVec0[1]) + (fSlow5 * fVec0[0]))) + (fConst4 * fRec2[1]));
		double fTemp1 = (fVec0[0] - ts9nonlin((fRec2[0] - fVec0[0])));
		fVec1[0] = fTemp1;
		fRec1[0] = ((fSlow7 * (fVec1[0] + fVec1[1])) + (fSlow3 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fVec1[1] = fVec1[0];
		fRec2[1] = fRec2[0];
		fVec0[1] = fVec0[0];
		fRec0[1] = fRec0[0];
	}
}

void Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("ts9sim.drive",N_("Drive"),"S","",&fslider2, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("ts9sim.tone",N_("Tone"),"SL","",&fslider1, 4e+02, 1e+02, 1e+03, 1.03);
	reg.registerVar("ts9sim.level",N_("Level"),"S","",&fslider0, -16.0, -2e+01, 4.0, 0.1);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b)
{
#define PARAM(p) ("ts9sim" "." p)

b.openHorizontalhideBox("");
b.create_master_slider(PARAM("drive"), 0);
b.closeBox();
b.openHorizontalBox("");
b.insertSpacer();
b.create_small_rackknobr(PARAM("drive"), 0);
b.create_small_rackknob(PARAM("level"), 0);
b.create_small_rackknob(PARAM("tone"), 0);
b.insertSpacer();
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

} // end namespace ts9sim
} // end namespace pluginlib
