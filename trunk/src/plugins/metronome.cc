// THE STATEMENT BELOW IS NO LONGER TRUE
// generated from file '../src/plugins/metronome.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace metronome {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT 	fslider1;
	int 	iRec6[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fRec7[2];
	int 	IOTA;
	int 	counter;
	double 	fVec0[1024];
	int 	iConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fRec5[3];
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fRec4[2];
	double 	fRec0[2];
	double 	fVec1[512];
	int 	iConst12;
	double 	fConst13;
	double 	fRec9[3];
	double 	fRec8[2];
	double 	fRec1[2];
	double 	fVec2[256];
	int 	iConst14;
	double 	fConst15;
	double 	fRec11[3];
	double 	fRec10[2];
	double 	fRec2[2];
	double 	fVec3[128];
	int 	iConst16;
	double 	fConst17;
	double 	fRec13[3];
	double 	fRec12[2];
	double 	fRec3[2];
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
	id = "metro";
	name = N_("Metronome");
	groups = 0;
	description = N_("Metronome"); // description (tooltip)
	category = N_("Misc");       // category
	shortname = N_("Metronome");     // shortname
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
	for (int i=0; i<2; i++) iRec6[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<1024; i++) fVec0[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<512; i++) fVec1[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<256; i++) fVec2[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<128; i++) fVec3[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1 - (1.0 / pow(9e+04,(1e+02 / double(iConst0)))));
	fConst2 = (1 - pow(9e+01,(2e+02 / double(iConst0))));
	fConst3 = (5e+01 / double(iConst0));
	IOTA = 0;
	counter = 0;
	iConst4 = int((int((0.004545454545454545 * iConst0)) & 4095));
	fConst5 = (1 - (100.53096491487338 / double(iConst0)));
	fConst6 = faustpower<2>(fConst5);
	fConst7 = (0 - (2 * fConst5));
	fConst8 = (fConst7 * cos((1382.300767579509 / double(iConst0))));
	fConst9 = (0.5 * fConst6);
	fConst10 = (fConst9 - 0.5);
	fConst11 = (0.5 - fConst9);
	iConst12 = int((int((0.001649294102124291 * iConst0)) & 4095));
	fConst13 = (fConst7 * cos((3809.620915449126 / double(iConst0))));
	iConst14 = int((int((0.0008411277841329655 * iConst0)) & 4095));
	fConst15 = (fConst7 * cos((7469.953347999665 / double(iConst0))));
	iConst16 = int((int((0.0005088385251824186 * iConst0)) & 4095));
	fConst17 = (fConst7 * cos((12348.092756787753 / double(iConst0))));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = double(fslider0);
	double 	fSlow5 = (0.03 + fSlow0);
	double 	fSlow6 = (60/(fslider1))*fSamplingFreq ;
	double 	fSlow1 = 0; 
	for (int i=0; i<count; i++) {
		counter = counter+1;
		if (counter >= (int)fSlow6) {
			counter = 0;
			fSlow1 = 1.0;
		} else {
			fSlow1 = 0.0;
		}
	    double 	fSlow2 = (2.5 * (fSlow1 * fSlow0));
	    int 	iSlow3 = (fSlow1 > 0);
	    int 	iSlow4 = (fSlow1 <= 0);
		iRec6[0] = (iSlow3 & (iRec6[1] | (fRec7[1] >= 1)));
		int iTemp0 = (iSlow4 & (fRec7[1] > 0));
		fRec7[0] = (((fConst3 * (((iRec6[1] == 0) & iSlow3) & (fRec7[1] < 1))) + (fRec7[1] * ((1 - (fConst2 * (iRec6[1] & (fRec7[1] > 90)))) - (fConst1 * iTemp0)))) * ((iTemp0 == 0) | (fRec7[1] >= 1e-06)));
		double fTemp1 = ((fSlow5 * fRec7[0]) - (0.9999999999999999 * ((0.8000000000000002 + (fRec0[1] + fRec2[1])) + (fRec1[1] + fRec3[1]))));
		double fTemp2 = faustpower<4>((0.75 + fabs(fTemp1)));
		double fTemp3 = (1.0 / fTemp2);
		double fTemp4 = (0.25 * (fTemp1 * ((fTemp3 > 1) + (double((fTemp3 <= 1)) / fTemp2))));
		fVec0[IOTA&1023] = ((fRec4[1] + fTemp4) + fSlow2);
		fRec5[0] = (0 - (((fConst8 * fRec5[1]) + (fConst6 * fRec5[2])) - (0.9 * fVec0[(IOTA-iConst4)&1023])));
		fRec4[0] = ((fConst11 * fRec5[0]) + (fConst10 * fRec5[2]));
		fRec0[0] = fRec4[0];
		fVec1[IOTA&511] = (fSlow2 + (fTemp4 + fRec8[1]));
		fRec9[0] = (0 - (((fConst13 * fRec9[1]) + (fConst6 * fRec9[2])) - (0.81 * fVec1[(IOTA-iConst12)&511])));
		fRec8[0] = ((fConst11 * fRec9[0]) + (fConst10 * fRec9[2]));
		fRec1[0] = fRec8[0];
		fVec2[IOTA&255] = (fSlow2 + (fTemp4 + fRec10[1]));
		fRec11[0] = (0 - (((fConst15 * fRec11[1]) + (fConst6 * fRec11[2])) - (0.7290000000000001 * fVec2[(IOTA-iConst14)&255])));
		fRec10[0] = ((fConst11 * fRec11[0]) + (fConst10 * fRec11[2]));
		fRec2[0] = fRec10[0];
		fVec3[IOTA&127] = (fSlow2 + (fTemp4 + fRec12[1]));
		fRec13[0] = (0 - (((fConst17 * fRec13[1]) + (fConst6 * fRec13[2])) - (0.6561 * fVec3[(IOTA-iConst16)&127])));
		fRec12[0] = ((fConst11 * fRec13[0]) + (fConst10 * fRec13[2]));
		fRec3[0] = fRec12[0];
		output0[i] = (FAUSTFLOAT)(fRec3[0] + (fRec2[0] + (fRec1[0] + ((double)input0[i] + fRec0[0]))));
		// post processing
		fRec3[1] = fRec3[0];
		fRec12[1] = fRec12[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec2[1] = fRec2[0];
		fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec1[1] = fRec1[0];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec0[1] = fRec0[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		IOTA = IOTA+1;
		fRec7[1] = fRec7[0];
		iRec6[1] = iRec6[0];
	}
}
		
void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("metro.BPM","","S",N_("Beats per Minute"),&fslider1, 3e+01, 24.0, 3.6e+02, 1.0);
	reg.registerVar("metro.Gain","","S",N_("Gain (value between 0 and 1)"),&fslider0, 0.8, 0.0, 1e+01, 0.01);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade_file("metronome_ui.glade");
        return 0;
    }
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("metro" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("BPM"), "BPM");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("BPM"), "BPM");
    b.create_small_rackknobr(PARAM("Gain"), "Gain");
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

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

#if true

PluginDef *plugin() {
    return new Dsp;
}

#else

extern "C" __attribute__ ((visibility ("default"))) int
get_gx_plugin(unsigned int idx, PluginDef **pplugin)
{
    const int count = 1;
    if (!pplugin) {
	return count;
    }
    switch (idx) {
    case 0: *pplugin = new Dsp; return count;
    default: *pplugin = 0; return -1;
    }
}

#endif

} // end namespace metronome
} // end namespace pluginlib
