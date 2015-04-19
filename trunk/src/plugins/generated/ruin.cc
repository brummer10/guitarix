// generated from file '../src/plugins/ruin.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace ruin {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	FAUSTFLOAT 	fslider0;
	double 	fRec0[2];
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	FAUSTFLOAT 	fslider1;
	double 	fRec1[2];
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
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	FAUSTFLOAT 	fslider2;
	double 	fRec2[6];
	double 	fConst55;
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
	id = "ruin";
	name = N_("Ruiner");
	groups = 0;
	description = N_("Devi Ever Dark Boost"); // description (tooltip)
	category = N_("Distortion");       // category
	shortname = N_("Ruiner");     // shortname
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
	for (int i=0; i<6; i++) fRec2[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(192000, max(1, fSamplingFreq)));
	fConst1 = (2.17193258571938e-24 * fConst0);
	fConst2 = (6.63702362788267e-13 + (fConst0 * (1.70492707442481e-15 + (fConst0 * (4.19596910358881e-18 + (fConst0 * (2.95819574097976e-21 + fConst1)))))));
	fConst3 = (2.80672888565836e-24 * fConst0);
	fConst4 = (5.80512966791183e-13 + (fConst0 * (1.24804042577715e-14 + (fConst0 * (1.48752851885156e-17 + (fConst0 * (1.81905884616603e-20 + fConst3)))))));
	fConst5 = (2.77619078700135e-25 * fConst0);
	fConst6 = (fConst0 * ((fConst0 * ((fConst0 * (0 - (1.77177960077957e-21 + fConst5))) - 1.30282134265895e-18)) - 1.15986606751485e-15));
	fConst7 = (2.74842887913133e-25 * fConst0);
	fConst8 = (5.79933033757426e-14 + (fConst0 * (1.22360789786831e-15 + (fConst0 * (1.45999906472023e-18 + (fConst0 * (1.78182371264179e-21 + fConst7)))))));
	fConst9 = (2.14830127173034e-25 * fConst0);
	fConst10 = ((fConst0 * ((fConst0 * ((fConst0 * (0 - (2.7133044348957e-22 + fConst9))) - 3.93508698145447e-19)) - 1.44426081917549e-16)) - 5.79933033757426e-14);
	fConst11 = (2.12681825901304e-25 * fConst0);
	fConst12 = (6.51446456326455e-14 + (fConst0 * (1.67435306237073e-16 + (fConst0 * (4.11311489819172e-19 + (fConst0 * (2.90100151771978e-22 + fConst11)))))));
	fConst13 = ((fConst0 * (1.70492707442481e-15 + (fConst0 * ((fConst0 * (2.95819574097976e-21 - fConst1)) - 4.19596910358881e-18)))) - 6.63702362788267e-13);
	fConst14 = ((fConst0 * (1.24804042577715e-14 + (fConst0 * ((fConst0 * (1.81905884616603e-20 - fConst3)) - 1.48752851885156e-17)))) - 5.80512966791183e-13);
	fConst15 = (fConst0 * ((fConst0 * (1.30282134265895e-18 + (fConst0 * (fConst5 - 1.77177960077957e-21)))) - 1.15986606751485e-15));
	fConst16 = ((fConst0 * (1.22360789786831e-15 + (fConst0 * ((fConst0 * (1.78182371264179e-21 - fConst7)) - 1.45999906472023e-18)))) - 5.79933033757426e-14);
	fConst17 = (5.79933033757426e-14 + (fConst0 * ((fConst0 * (3.93508698145447e-19 + (fConst0 * (fConst9 - 2.7133044348957e-22)))) - 1.44426081917549e-16)));
	fConst18 = ((fConst0 * (1.67435306237073e-16 + (fConst0 * ((fConst0 * (2.90100151771978e-22 - fConst11)) - 4.11311489819172e-19)))) - 6.51446456326455e-14);
	fConst19 = (1.08596629285969e-23 * fConst0);
	fConst20 = ((fConst0 * (1.70492707442481e-15 + (fConst0 * (4.19596910358881e-18 + (fConst0 * (fConst19 - 8.87458722293927e-21)))))) - 1.9911070883648e-12);
	fConst21 = (1.40336444282918e-23 * fConst0);
	fConst22 = ((fConst0 * (1.24804042577715e-14 + (fConst0 * (1.48752851885156e-17 + (fConst0 * (fConst21 - 5.4571765384981e-20)))))) - 1.74153890037355e-12);
	fConst23 = (1.38809539350067e-24 * fConst0);
	fConst24 = (fConst0 * ((fConst0 * ((fConst0 * (5.31533880233872e-21 - fConst23)) - 1.30282134265895e-18)) - 1.15986606751485e-15));
	fConst25 = (1.37421443956567e-24 * fConst0);
	fConst26 = ((fConst0 * (1.22360789786831e-15 + (fConst0 * (1.45999906472023e-18 + (fConst0 * (fConst25 - 5.34547113792538e-21)))))) - 1.73979910127228e-13);
	fConst27 = (1.07415063586517e-24 * fConst0);
	fConst28 = (1.73979910127228e-13 + (fConst0 * ((fConst0 * ((fConst0 * (8.13991330468709e-22 - fConst27)) - 3.93508698145447e-19)) - 1.44426081917549e-16)));
	fConst29 = (1.06340912950652e-24 * fConst0);
	fConst30 = ((fConst0 * (1.67435306237073e-16 + (fConst0 * (4.11311489819172e-19 + (fConst0 * (fConst29 - 8.70300455315933e-22)))))) - 1.95433936897936e-13);
	fConst31 = (2.17193258571938e-23 * fConst0);
	fConst32 = ((fConst0 * ((fConst0 * (8.39193820717763e-18 + (fConst0 * (5.91639148195952e-21 - fConst31)))) - 3.40985414884961e-15)) - 1.32740472557653e-12);
	fConst33 = (2.80672888565836e-23 * fConst0);
	fConst34 = ((fConst0 * ((fConst0 * (2.97505703770311e-17 + (fConst0 * (3.63811769233207e-20 - fConst33)))) - 2.49608085155429e-14)) - 1.16102593358237e-12);
	fConst35 = (2.77619078700135e-24 * fConst0);
	fConst36 = (fConst0 * (2.3197321350297e-15 + (fConst0 * ((fConst0 * (fConst35 - 3.54355920155915e-21)) - 2.60564268531789e-18))));
	fConst37 = (2.74842887913133e-24 * fConst0);
	fConst38 = ((fConst0 * ((fConst0 * (2.91999812944046e-18 + (fConst0 * (3.56364742528358e-21 - fConst37)))) - 2.44721579573661e-15)) - 1.15986606751485e-13);
	fConst39 = (2.14830127173034e-24 * fConst0);
	fConst40 = (1.15986606751485e-13 + (fConst0 * (2.88852163835099e-16 + (fConst0 * ((fConst0 * (fConst39 - 5.4266088697914e-22)) - 7.87017396290893e-19)))));
	fConst41 = (2.12681825901304e-24 * fConst0);
	fConst42 = ((fConst0 * ((fConst0 * (8.22622979638344e-19 + (fConst0 * (5.80200303543955e-22 - fConst41)))) - 3.34870612474147e-16)) - 1.30289291265291e-13);
	fConst43 = (1.32740472557653e-12 + (fConst0 * ((fConst0 * ((fConst0 * (5.91639148195952e-21 + fConst31)) - 8.39193820717763e-18)) - 3.40985414884961e-15)));
	fConst44 = (1.16102593358237e-12 + (fConst0 * ((fConst0 * ((fConst0 * (3.63811769233207e-20 + fConst33)) - 2.97505703770311e-17)) - 2.49608085155429e-14)));
	fConst45 = (fConst0 * (2.3197321350297e-15 + (fConst0 * (2.60564268531789e-18 + (fConst0 * (0 - (3.54355920155915e-21 + fConst35)))))));
	fConst46 = (1.15986606751485e-13 + (fConst0 * ((fConst0 * ((fConst0 * (3.56364742528358e-21 + fConst37)) - 2.91999812944046e-18)) - 2.44721579573661e-15)));
	fConst47 = ((fConst0 * (2.88852163835099e-16 + (fConst0 * (7.87017396290893e-19 + (fConst0 * (0 - (5.4266088697914e-22 + fConst39))))))) - 1.15986606751485e-13);
	fConst48 = (1.30289291265291e-13 + (fConst0 * ((fConst0 * ((fConst0 * (5.80200303543955e-22 + fConst41)) - 8.22622979638344e-19)) - 3.34870612474147e-16)));
	fConst49 = (1.9911070883648e-12 + (fConst0 * (1.70492707442481e-15 + (fConst0 * ((fConst0 * (0 - (8.87458722293927e-21 + fConst19))) - 4.19596910358881e-18)))));
	fConst50 = (1.74153890037355e-12 + (fConst0 * (1.24804042577715e-14 + (fConst0 * ((fConst0 * (0 - (5.4571765384981e-20 + fConst21))) - 1.48752851885156e-17)))));
	fConst51 = (fConst0 * ((fConst0 * (1.30282134265895e-18 + (fConst0 * (5.31533880233872e-21 + fConst23)))) - 1.15986606751485e-15));
	fConst52 = (1.73979910127228e-13 + (fConst0 * (1.22360789786831e-15 + (fConst0 * ((fConst0 * (0 - (5.34547113792538e-21 + fConst25))) - 1.45999906472023e-18)))));
	fConst53 = ((fConst0 * ((fConst0 * (3.93508698145447e-19 + (fConst0 * (8.13991330468709e-22 + fConst27)))) - 1.44426081917549e-16)) - 1.73979910127228e-13);
	fConst54 = (1.95433936897936e-13 + (fConst0 * (1.67435306237073e-16 + (fConst0 * ((fConst0 * (0 - (8.70300455315933e-22 + fConst29))) - 4.11311489819172e-19)))));
	fConst55 = faustpower<3>(fConst0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * (1 - double(fslider1)));
	double 	fSlow2 = (0.01 * double(fslider2));
	double 	fSlow3 = (1 - fSlow2);
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		fRec1[0] = ((0.993 * fRec1[1]) + fSlow1);
		double fTemp0 = (2.90256483395592e-11 + ((fRec0[0] * (2.89966516878713e-12 + (fConst0 * (fConst12 + (fConst10 * fRec0[0]))))) + (fConst0 * ((fRec1[0] * ((fRec0[0] * (fConst8 + (fConst6 * fRec0[0]))) + fConst4)) + fConst2))));
		double fTemp1 = (4.66576522119352e-14 * fRec0[0]);
		double fTemp2 = ((0 - fTemp1) - 4.66576522119352e-16);
		double fTemp3 = (double)input0[i];
		fRec2[0] = ((fSlow2 * fTemp3) - ((((((fRec2[1] * (1.45128241697796e-10 + ((fRec0[0] * (1.44983258439356e-11 + (fConst0 * (fConst54 + (fConst53 * fRec0[0]))))) + (fConst0 * ((fRec1[0] * ((fRec0[0] * (fConst52 + (fConst51 * fRec0[0]))) + fConst50)) + fConst49))))) + (fRec2[2] * (2.90256483395592e-10 + ((fRec0[0] * (2.89966516878713e-11 + (fConst0 * (fConst48 + (fConst47 * fRec0[0]))))) + (fConst0 * ((fRec1[0] * ((fRec0[0] * (fConst46 + (fConst45 * fRec0[0]))) + fConst44)) + fConst43)))))) + (fRec2[3] * (2.90256483395592e-10 + ((fRec0[0] * (2.89966516878713e-11 + (fConst0 * (fConst42 + (fConst40 * fRec0[0]))))) + (fConst0 * ((fRec1[0] * ((fRec0[0] * (fConst38 + (fConst36 * fRec0[0]))) + fConst34)) + fConst32)))))) + (fRec2[4] * (1.45128241697796e-10 + ((fRec0[0] * (1.44983258439356e-11 + (fConst0 * (fConst30 + (fConst28 * fRec0[0]))))) + (fConst0 * ((fRec1[0] * ((fRec0[0] * (fConst26 + (fConst24 * fRec0[0]))) + fConst22)) + fConst20)))))) + (fRec2[5] * (2.90256483395592e-11 + ((fRec0[0] * (2.89966516878713e-12 + (fConst0 * (fConst18 + (fConst17 * fRec0[0]))))) + (fConst0 * ((fRec1[0] * ((fRec0[0] * (fConst16 + (fConst15 * fRec0[0]))) + fConst14)) + fConst13)))))) / fTemp0));
		double fTemp4 = (4.66576522119352e-16 + fTemp1);
		double fTemp5 = (9.33153044238704e-14 * fRec0[0]);
		output0[i] = (FAUSTFLOAT)((fSlow3 * fTemp3) + (fConst55 * (((((((fRec2[0] * fTemp4) + (fRec2[1] * fTemp2)) + (fRec2[2] * ((0 - fTemp5) - 9.33153044238704e-16))) + (fRec2[3] * (9.33153044238704e-16 + fTemp5))) + (fRec2[4] * fTemp4)) + (fRec2[5] * fTemp2)) / fTemp0)));
		// post processing
		for (int i=5; i>0; i--) fRec2[i] = fRec2[i-1];
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
	reg.registerVar("ruin.Intensity",N_("Intensity"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("ruin.Volume",N_("Volume"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("ruin.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider2, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("ruin" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Intensity"), "Intensity");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Volume"), "Volume");

    b.create_small_rackknobr(PARAM("Intensity"), "Intensity");
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

} // end namespace ruin
} // end namespace pluginlib
