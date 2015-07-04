// generated from file '../src/plugins/cstb.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace cstb {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	FAUSTFLOAT 	fslider0;
	double 	fRec0[2];
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	FAUSTFLOAT 	fslider1;
	double 	fRec1[2];
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	FAUSTFLOAT 	fslider2;
	double 	fRec2[5];
	double 	fConst22;
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
	id = "cstb";
	name = N_("Colorsound Tone Blender");
	groups = 0;
	description = N_("Colorsound Tone Blender"); // description (tooltip)
	category = N_("Distortion");       // category
	shortname = N_("CS Toneblender");     // shortname
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
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<5; i++) fRec2[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(192000, max(1, fSamplingFreq)));
	fConst1 = (7.72761004436121e-17 * fConst0);
	fConst2 = (1.90124164300881e-12 + (fConst0 * (4.0705776699833e-14 + fConst1)));
	fConst3 = (7.13788307669893e-19 * fConst0);
	fConst4 = ((fConst0 * ((fConst0 * (0 - (3.81274375281155e-16 + fConst3))) - 1.78337596435683e-14)) - 3.57720562427687e-14);
	fConst5 = (7.26395344169953e-19 * fConst0);
	fConst6 = (3.58457860428614e-14 + (fConst0 * (1.78716714442828e-14 + (fConst0 * (3.82634300978431e-16 + fConst5)))));
	fConst7 = ((fConst0 * (4.0705776699833e-14 - fConst1)) - 1.90124164300881e-12);
	fConst8 = (3.57720562427687e-14 + (fConst0 * ((fConst0 * (3.81274375281155e-16 - fConst3)) - 1.78337596435683e-14)));
	fConst9 = ((fConst0 * (1.78716714442828e-14 + (fConst0 * (fConst5 - 3.82634300978431e-16)))) - 3.58457860428614e-14);
	fConst10 = (2.85515323067957e-18 * fConst0);
	fConst11 = faustpower<2>(fConst0);
	fConst12 = (7.15441124855374e-14 + (fConst11 * (fConst10 - 7.6254875056231e-16)));
	fConst13 = (2.90558137667981e-18 * fConst0);
	fConst14 = ((fConst11 * (7.65268601956861e-16 - fConst13)) - 7.16915720857228e-14);
	fConst15 = (1.54552200887224e-16 * fConst11);
	fConst16 = (fConst15 - 3.80248328601762e-12);
	fConst17 = (3.56675192871367e-14 - (4.28272984601936e-18 * fConst11));
	fConst18 = ((4.35837206501972e-18 * fConst11) - 3.57433428885656e-14);
	fConst19 = (3.80248328601762e-12 - fConst15);
	fConst20 = ((fConst11 * (7.6254875056231e-16 + fConst10)) - 7.15441124855374e-14);
	fConst21 = (7.16915720857228e-14 + (fConst11 * (0 - (7.65268601956861e-16 + fConst13))));
	fConst22 = faustpower<3>(fConst0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	double 	fSlow2 = (0.01 * double(fslider2));
	double 	fSlow3 = (1 - fSlow2);
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		double fTemp0 = (3.81338149392143e-12 + (fConst0 * ((fRec0[0] * (fConst6 + (fConst4 * fRec0[0]))) + fConst2)));
		fRec1[0] = ((0.993 * fRec1[1]) + fSlow1);
		double fTemp1 = (fConst0 * (fRec0[0] * (((fRec0[0] * (2.34677954600673e-22 + (2.34677954600673e-19 * fRec1[0]))) - (2.35728909376724e-17 * fRec1[0])) - 2.35728909376724e-20)));
		double fTemp2 = (2.50775435507154e-15 * fRec1[0]);
		double fTemp3 = (double)input0[i];
		fRec2[0] = ((fSlow2 * fTemp3) - (((((fRec2[1] * (1.52535259756857e-11 + (fConst0 * ((fRec0[0] * (fConst21 + (fConst20 * fRec0[0]))) + fConst19)))) + (fRec2[2] * (2.28802889635286e-11 + (fConst11 * ((fRec0[0] * (fConst18 + (fConst17 * fRec0[0]))) - 8.14115533996661e-14))))) + (fRec2[3] * (1.52535259756857e-11 + (fConst0 * (fConst16 + (fRec0[0] * (fConst14 + (fConst12 * fRec0[0])))))))) + (fRec2[4] * (3.81338149392143e-12 + (fConst0 * ((fRec0[0] * (fConst9 + (fConst8 * fRec0[0]))) + fConst7))))) / fTemp0));
		double fTemp4 = (5.01550871014307e-15 * fRec1[0]);
		double fTemp5 = (fConst0 * (fRec0[0] * (9.42915637506898e-20 + ((9.42915637506898e-17 * fRec1[0]) + (fRec0[0] * ((0 - (9.38711818402692e-19 * fRec1[0])) - 9.38711818402692e-22))))));
		output0[i] = (FAUSTFLOAT)((fSlow3 * fTemp3) + (0.3 * min(0.7514, max(-0.4514, (fConst22 * ((((((fRec2[0] * ((fTemp1 - fTemp2) - 2.50775435507154e-18)) + (fRec2[1] * (5.01550871014307e-18 + (fTemp4 + fTemp5)))) + (fConst0 * ((fRec0[0] * fRec2[2]) * (((fRec0[0] * (1.40806772760404e-21 + (1.40806772760404e-18 * fRec1[0]))) - (1.41437345626035e-16 * fRec1[0])) - 1.41437345626035e-19)))) + (fRec2[3] * ((fTemp5 - fTemp4) - 5.01550871014307e-18))) + (fRec2[4] * (2.50775435507154e-18 + (fTemp2 + fTemp1)))) / fTemp0))))));
		// post processing
		for (int i=4; i>0; i--) fRec2[i] = fRec2[i-1];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("cstb.Attack",N_("Attack"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("cstb.Level",N_("Level"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("cstb.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider2, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("cstb" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Attack"), "Attack");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Level"), "Level");

    b.create_small_rackknobr(PARAM("Attack"), "Attack");
    b.create_small_rackknobr(PARAM("wet_dry"), "dry/wet");
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

} // end namespace cstb
} // end namespace pluginlib
