// generated from file '../src/plugins/aclipper.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "clipping.h"

namespace pluginlib {
namespace aclipper {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	double 	fRec0[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fRec3[3];
	double 	fConst7;
	double 	fConst8;
	double 	fVec0[2];
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	FAUSTFLOAT 	fslider1;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fRec4[2];
	double 	fRec2[2];
	double 	fConst17;
	double 	fConst18;
	double 	fRec1[2];
	FAUSTFLOAT 	fslider2;
	double 	fRec5[2];
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
	id = "aclipper";
	name = N_("Rat");
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
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
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
	fConst2 = (3.64865447573811e-11 * fConst1);
	fConst3 = (0.000414619826788421 + (fConst1 * (fConst2 - 1.9073341271921e-05)));
	fConst4 = (0.000829239653576842 - (7.29730895147621e-11 * faustpower<2>(fConst1)));
	fConst5 = (0.000414619826788421 + (fConst1 * (1.9073341271921e-05 + fConst2)));
	fConst6 = (1.0 / fConst5);
	fConst7 = (1.82432723786905e-05 * fConst1);
	fConst8 = (0 - fConst7);
	fConst9 = (2.08332871602678e-05 * fConst1);
	fConst10 = (2.21630714470934e-06 + fConst9);
	fConst11 = ((2.21630714470934e-06 - fConst9) / fConst10);
	fConst12 = (9.4e-08 * iConst0);
	fConst13 = (0.00044179999999999995 * iConst0);
	fConst14 = (1 + fConst13);
	fConst15 = (1.0 / (fConst14 * fConst5));
	fConst16 = (0 - ((1 - fConst13) / fConst14));
	fConst17 = (0 - fConst9);
	fConst18 = (1.0 / fConst10);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.007000000000000006 * (1.0 - double(fslider0)));
	double 	fSlow1 = double(fslider1);
	double 	fSlow2 = (fConst12 * ((100000 * fSlow1) + 5700));
	double 	fSlow3 = (1 - fSlow2);
	double 	fSlow4 = (1 + fSlow2);
	double 	fSlow5 = (fConst18 * (1.0 + max(0.0, (fSlow1 - 0.25))));
	double 	fSlow6 = (0.007000000000000006 * pow(10,(0.05 * double(fslider2))));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.993 * fRec0[1]));
		double fTemp0 = (3.91923990498812e-05 * fRec0[0]);
		double fTemp1 = (0.0593824228028504 + (fConst1 * (3.91923990498812e-05 + (0 - fTemp0))));
		fRec3[0] = ((double)input0[i] - (fConst6 * ((fConst4 * fRec3[1]) + (fConst3 * fRec3[2]))));
		double fTemp2 = (((0.000829239653576842 * fRec3[1]) + (fConst7 * fRec3[0])) + (fConst8 * fRec3[2]));
		fVec0[0] = fTemp2;
		double fTemp3 = (fConst6 * fVec0[0]);
		fRec4[0] = ((fConst16 * fRec4[1]) + (fConst15 * ((fSlow4 * fVec0[0]) + (fSlow3 * fVec0[1]))));
		fRec2[0] = (0 - ((opamp((fRec4[0] - fTemp3)) + (fConst11 * fRec2[1])) - fTemp3));
		fRec1[0] = (asymhardclip2((fSlow5 * ((fConst17 * fRec2[1]) + (fConst9 * fRec2[0])))) - ((fRec1[1] * (0.0593824228028504 + (fConst1 * (fTemp0 - 3.91923990498812e-05)))) / fTemp1));
		fRec5[0] = ((0.993 * fRec5[1]) + fSlow6);
		output0[i] = (FAUSTFLOAT)(0.0593824228028504 * ((fRec5[0] * (fRec1[0] + fRec1[1])) / fTemp1));
		// post processing
		fRec5[1] = fRec5[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fVec0[1] = fVec0[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec0[1] = fRec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("aclipper.drive",N_("Drive"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("aclipper.level",N_("Level"),"S","",&fslider2, -2.0, -2e+01, 12.0, 0.1);
	reg.registerVar("aclipper.tone",N_("Tone"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("aclipper" "." p)
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("drive"), "drive");
b.closeBox();
b.openHorizontalBox("");
b.insertSpacer();
b.create_small_rackknobr(PARAM("drive"), "Distortion");
b.create_small_rackknob(PARAM("tone"), "Filter");
b.create_small_rackknob(PARAM("level"), "Volume");
b.insertSpacer();
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

} // end namespace aclipper
} // end namespace pluginlib
