// generated from file '../src/plugins/buzz.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace buzz {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	double 	fRec8[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fRec9[4];
	double 	fConst9;
	double 	fRec7[3];
	double 	fVec0[2];
	double 	fRec6[2];
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fRec10[2];
	double 	fRec5[3];
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fRec4[2];
	double 	fRec3[3];
	double 	fVec1[2];
	double 	fRec2[2];
	double 	fRec11[2];
	double 	fRec1[3];
	double 	fRec0[2];
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
	id = "buzz";
	name = N_("Buzz Box");
	groups = 0;
	description = N_("Buzz Box"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("Buzz Box");     // shortname
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
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<4; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = double(iConst0);
	fConst2 = (9.04201686922855e-15 * fConst1);
	fConst3 = (2.46256378077601e-15 + (fConst1 * ((fConst1 * (1.0967885210812e-14 - fConst2)) - 8.14058347559848e-15)));
	fConst4 = (2.71260506076857e-14 * fConst1);
	fConst5 = (7.38769134232804e-15 + (fConst1 * ((fConst1 * (fConst4 - 1.0967885210812e-14)) - 8.14058347559848e-15)));
	fConst6 = (7.38769134232804e-15 + (fConst1 * (8.14058347559848e-15 + (fConst1 * (0 - (1.0967885210812e-14 + fConst4))))));
	fConst7 = (2.46256378077601e-15 + (fConst1 * (8.14058347559848e-15 + (fConst1 * (1.0967885210812e-14 + fConst2)))));
	fConst8 = (1.0 / fConst7);
	fConst9 = (faustpower<3>(fConst1) / fConst7);
	fConst10 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst11 = (1 + fConst10);
	fConst12 = (0.027 / fConst11);
	fConst13 = (0 - ((1 - fConst10) / fConst11));
	fConst14 = (1.0 / tan((34.55751918948772 / double(iConst0))));
	fConst15 = (0 - fConst14);
	fConst16 = (1 + fConst14);
	fConst17 = (0.025 / fConst16);
	fConst18 = (0 - ((1 - fConst14) / fConst16));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.01 * double(fslider0));
	double 	fSlow1 = (1 - fSlow0);
	double 	fSlow2 = (0.007000000000000006 * double(fslider1));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		double fTemp1 = (2.0 * fRec3[1]);
		double fTemp2 = (2.0 * fRec7[1]);
		fRec8[0] = ((0.993 * fRec8[1]) + fSlow2);
		fRec9[0] = ((fSlow0 * fTemp0) - (fConst8 * (((fConst6 * fRec9[1]) + (fConst5 * fRec9[2])) + (fConst3 * fRec9[3]))));
		fRec7[0] = ((fConst9 * ((((fRec9[1] * (0 - (1.14404299012556e-12 * fRec8[0]))) + (3.81347663375185e-13 * (fRec9[0] * fRec8[0]))) + (1.14404299012556e-12 * (fRec8[0] * fRec9[2]))) + (fRec9[3] * (0 - (3.81347663375185e-13 * fRec8[0]))))) - (fTemp2 + fRec7[2]));
		double fTemp3 = (fRec7[2] + (fRec7[0] + fTemp2));
		fVec0[0] = fTemp3;
		fRec6[0] = ((1.0000000000000002 * (fVec0[0] + fVec0[1])) - (0.9999999999999998 * fRec6[1]));
		fRec10[0] = ((fConst13 * fRec10[1]) + (fConst12 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec10[0] + fRec6[0]) - 5.571981)) - 43.63033333333331);
		fRec4[0] = ((fConst18 * fRec4[1]) + (fConst17 * ((fConst14 * fRec5[0]) + (fConst15 * fRec5[1]))));
		fRec3[0] = (fRec4[0] - (fTemp1 + fRec3[2]));
		double fTemp4 = (fRec3[2] + (fRec3[0] + fTemp1));
		fVec1[0] = fTemp4;
		fRec2[0] = ((1.0000000000000002 * (fVec1[0] + fVec1[1])) - (0.9999999999999998 * fRec2[1]));
		fRec11[0] = ((fConst13 * fRec11[1]) + (fConst12 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec11[0] + fRec2[0]) - 5.571981)) - 43.63033333333331);
		fRec0[0] = ((fConst18 * fRec0[1]) + (fConst17 * ((fConst14 * fRec1[0]) + (fConst15 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)(fRec0[0] + (fSlow1 * fTemp0));
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec11[1] = fRec11[0];
		fRec2[1] = fRec2[0];
		fVec1[1] = fVec1[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec10[1] = fRec10[0];
		fRec6[1] = fRec6[0];
		fVec0[1] = fVec0[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		for (int i=3; i>0; i--) fRec9[i] = fRec9[i-1];
		fRec8[1] = fRec8[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("buzz.Level",N_("Level"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("buzz.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider0, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("buzz" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Level"), "Level");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Level"), "Level");
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

} // end namespace buzz
} // end namespace pluginlib
