// generated from file '../src/plugins/ruin.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace ruin {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	FAUSTFLOAT 	fslider1;
	double 	fRec4[2];
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	FAUSTFLOAT 	fslider2;
	double 	fRec5[2];
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
	double 	fConst55;
	double 	fRec6[6];
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fRec7[2];
	double 	fRec3[3];
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fRec2[2];
	double 	fRec8[2];
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
	id = "ruin";
	name = N_("Ruiner");
	groups = 0;
	description = N_("Devi Ever Dark Boost"); // description (tooltip)
	category = N_("Fuzz");       // category
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
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<6; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
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
	fConst2 = (2.17193258571938e-24 * fConst1);
	fConst3 = (6.63702362788267e-13 + (fConst1 * (1.70492707442481e-15 + (fConst1 * (4.19596910358881e-18 + (fConst1 * (2.95819574097976e-21 + fConst2)))))));
	fConst4 = (2.80672888565836e-24 * fConst1);
	fConst5 = (5.80512966791183e-13 + (fConst1 * (1.24804042577715e-14 + (fConst1 * (1.48752851885156e-17 + (fConst1 * (1.81905884616603e-20 + fConst4)))))));
	fConst6 = (2.77619078700135e-25 * fConst1);
	fConst7 = (fConst1 * ((fConst1 * ((fConst1 * (0 - (1.77177960077957e-21 + fConst6))) - 1.30282134265895e-18)) - 1.15986606751485e-15));
	fConst8 = (2.74842887913133e-25 * fConst1);
	fConst9 = (5.79933033757426e-14 + (fConst1 * (1.22360789786831e-15 + (fConst1 * (1.45999906472023e-18 + (fConst1 * (1.78182371264179e-21 + fConst8)))))));
	fConst10 = (2.14830127173034e-25 * fConst1);
	fConst11 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (2.7133044348957e-22 + fConst10))) - 3.93508698145447e-19)) - 1.44426081917549e-16)) - 5.79933033757426e-14);
	fConst12 = (2.12681825901304e-25 * fConst1);
	fConst13 = (6.51446456326455e-14 + (fConst1 * (1.67435306237073e-16 + (fConst1 * (4.11311489819172e-19 + (fConst1 * (2.90100151771978e-22 + fConst12)))))));
	fConst14 = ((fConst1 * (1.70492707442481e-15 + (fConst1 * ((fConst1 * (2.95819574097976e-21 - fConst2)) - 4.19596910358881e-18)))) - 6.63702362788267e-13);
	fConst15 = ((fConst1 * (1.24804042577715e-14 + (fConst1 * ((fConst1 * (1.81905884616603e-20 - fConst4)) - 1.48752851885156e-17)))) - 5.80512966791183e-13);
	fConst16 = (fConst1 * ((fConst1 * (1.30282134265895e-18 + (fConst1 * (fConst6 - 1.77177960077957e-21)))) - 1.15986606751485e-15));
	fConst17 = ((fConst1 * (1.22360789786831e-15 + (fConst1 * ((fConst1 * (1.78182371264179e-21 - fConst8)) - 1.45999906472023e-18)))) - 5.79933033757426e-14);
	fConst18 = (5.79933033757426e-14 + (fConst1 * ((fConst1 * (3.93508698145447e-19 + (fConst1 * (fConst10 - 2.7133044348957e-22)))) - 1.44426081917549e-16)));
	fConst19 = ((fConst1 * (1.67435306237073e-16 + (fConst1 * ((fConst1 * (2.90100151771978e-22 - fConst12)) - 4.11311489819172e-19)))) - 6.51446456326455e-14);
	fConst20 = (1.08596629285969e-23 * fConst1);
	fConst21 = ((fConst1 * (1.70492707442481e-15 + (fConst1 * (4.19596910358881e-18 + (fConst1 * (fConst20 - 8.87458722293927e-21)))))) - 1.9911070883648e-12);
	fConst22 = (1.40336444282918e-23 * fConst1);
	fConst23 = ((fConst1 * (1.24804042577715e-14 + (fConst1 * (1.48752851885156e-17 + (fConst1 * (fConst22 - 5.4571765384981e-20)))))) - 1.74153890037355e-12);
	fConst24 = (1.38809539350067e-24 * fConst1);
	fConst25 = (fConst1 * ((fConst1 * ((fConst1 * (5.31533880233872e-21 - fConst24)) - 1.30282134265895e-18)) - 1.15986606751485e-15));
	fConst26 = (1.37421443956567e-24 * fConst1);
	fConst27 = ((fConst1 * (1.22360789786831e-15 + (fConst1 * (1.45999906472023e-18 + (fConst1 * (fConst26 - 5.34547113792538e-21)))))) - 1.73979910127228e-13);
	fConst28 = (1.07415063586517e-24 * fConst1);
	fConst29 = (1.73979910127228e-13 + (fConst1 * ((fConst1 * ((fConst1 * (8.13991330468709e-22 - fConst28)) - 3.93508698145447e-19)) - 1.44426081917549e-16)));
	fConst30 = (1.06340912950652e-24 * fConst1);
	fConst31 = ((fConst1 * (1.67435306237073e-16 + (fConst1 * (4.11311489819172e-19 + (fConst1 * (fConst30 - 8.70300455315933e-22)))))) - 1.95433936897936e-13);
	fConst32 = (2.17193258571938e-23 * fConst1);
	fConst33 = ((fConst1 * ((fConst1 * (8.39193820717763e-18 + (fConst1 * (5.91639148195952e-21 - fConst32)))) - 3.40985414884961e-15)) - 1.32740472557653e-12);
	fConst34 = (2.80672888565836e-23 * fConst1);
	fConst35 = ((fConst1 * ((fConst1 * (2.97505703770311e-17 + (fConst1 * (3.63811769233207e-20 - fConst34)))) - 2.49608085155429e-14)) - 1.16102593358237e-12);
	fConst36 = (2.77619078700135e-24 * fConst1);
	fConst37 = (fConst1 * (2.3197321350297e-15 + (fConst1 * ((fConst1 * (fConst36 - 3.54355920155915e-21)) - 2.60564268531789e-18))));
	fConst38 = (2.74842887913133e-24 * fConst1);
	fConst39 = ((fConst1 * ((fConst1 * (2.91999812944046e-18 + (fConst1 * (3.56364742528358e-21 - fConst38)))) - 2.44721579573661e-15)) - 1.15986606751485e-13);
	fConst40 = (2.14830127173034e-24 * fConst1);
	fConst41 = (1.15986606751485e-13 + (fConst1 * (2.88852163835099e-16 + (fConst1 * ((fConst1 * (fConst40 - 5.4266088697914e-22)) - 7.87017396290893e-19)))));
	fConst42 = (2.12681825901304e-24 * fConst1);
	fConst43 = ((fConst1 * ((fConst1 * (8.22622979638344e-19 + (fConst1 * (5.80200303543955e-22 - fConst42)))) - 3.34870612474147e-16)) - 1.30289291265291e-13);
	fConst44 = (1.32740472557653e-12 + (fConst1 * ((fConst1 * ((fConst1 * (5.91639148195952e-21 + fConst32)) - 8.39193820717763e-18)) - 3.40985414884961e-15)));
	fConst45 = (1.16102593358237e-12 + (fConst1 * ((fConst1 * ((fConst1 * (3.63811769233207e-20 + fConst34)) - 2.97505703770311e-17)) - 2.49608085155429e-14)));
	fConst46 = (fConst1 * (2.3197321350297e-15 + (fConst1 * (2.60564268531789e-18 + (fConst1 * (0 - (3.54355920155915e-21 + fConst36)))))));
	fConst47 = (1.15986606751485e-13 + (fConst1 * ((fConst1 * ((fConst1 * (3.56364742528358e-21 + fConst38)) - 2.91999812944046e-18)) - 2.44721579573661e-15)));
	fConst48 = ((fConst1 * (2.88852163835099e-16 + (fConst1 * (7.87017396290893e-19 + (fConst1 * (0 - (5.4266088697914e-22 + fConst40))))))) - 1.15986606751485e-13);
	fConst49 = (1.30289291265291e-13 + (fConst1 * ((fConst1 * ((fConst1 * (5.80200303543955e-22 + fConst42)) - 8.22622979638344e-19)) - 3.34870612474147e-16)));
	fConst50 = (1.9911070883648e-12 + (fConst1 * (1.70492707442481e-15 + (fConst1 * ((fConst1 * (0 - (8.87458722293927e-21 + fConst20))) - 4.19596910358881e-18)))));
	fConst51 = (1.74153890037355e-12 + (fConst1 * (1.24804042577715e-14 + (fConst1 * ((fConst1 * (0 - (5.4571765384981e-20 + fConst22))) - 1.48752851885156e-17)))));
	fConst52 = (fConst1 * ((fConst1 * (1.30282134265895e-18 + (fConst1 * (5.31533880233872e-21 + fConst24)))) - 1.15986606751485e-15));
	fConst53 = (1.73979910127228e-13 + (fConst1 * (1.22360789786831e-15 + (fConst1 * ((fConst1 * (0 - (5.34547113792538e-21 + fConst26))) - 1.45999906472023e-18)))));
	fConst54 = ((fConst1 * ((fConst1 * (3.93508698145447e-19 + (fConst1 * (8.13991330468709e-22 + fConst28)))) - 1.44426081917549e-16)) - 1.73979910127228e-13);
	fConst55 = (1.95433936897936e-13 + (fConst1 * (1.67435306237073e-16 + (fConst1 * ((fConst1 * (0 - (8.70300455315933e-22 + fConst30))) - 4.11311489819172e-19)))));
	fConst56 = (0.5 * faustpower<3>(fConst1));
	fConst57 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst58 = (1 + fConst57);
	fConst59 = (0.027 / fConst58);
	fConst60 = (0 - ((1 - fConst57) / fConst58));
	fConst61 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst62 = (0 - fConst61);
	fConst63 = (1 + fConst61);
	fConst64 = (0.025 / fConst63);
	fConst65 = (0 - ((1 - fConst61) / fConst63));
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
	double 	fSlow3 = (0.007000000000000006 * (1 - double(fslider2)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec4[0] = ((0.993 * fRec4[1]) + fSlow2);
		fRec5[0] = ((0.993 * fRec5[1]) + fSlow3);
		double fTemp1 = (2.90256483395592e-11 + ((fRec4[0] * (2.89966516878713e-12 + (fConst1 * (fConst13 + (fConst11 * fRec4[0]))))) + (fConst1 * ((fRec5[0] * ((fRec4[0] * (fConst9 + (fConst7 * fRec4[0]))) + fConst5)) + fConst3))));
		double fTemp2 = (4.66576522119352e-14 * fRec4[0]);
		double fTemp3 = ((0 - fTemp2) - 4.66576522119352e-16);
		fRec6[0] = ((fSlow0 * fTemp0) - ((((((fRec6[1] * (1.45128241697796e-10 + ((fRec4[0] * (1.44983258439356e-11 + (fConst1 * (fConst55 + (fConst54 * fRec4[0]))))) + (fConst1 * ((fRec5[0] * ((fRec4[0] * (fConst53 + (fConst52 * fRec4[0]))) + fConst51)) + fConst50))))) + (fRec6[2] * (2.90256483395592e-10 + ((fRec4[0] * (2.89966516878713e-11 + (fConst1 * (fConst49 + (fConst48 * fRec4[0]))))) + (fConst1 * ((fRec5[0] * ((fRec4[0] * (fConst47 + (fConst46 * fRec4[0]))) + fConst45)) + fConst44)))))) + (fRec6[3] * (2.90256483395592e-10 + ((fRec4[0] * (2.89966516878713e-11 + (fConst1 * (fConst43 + (fConst41 * fRec4[0]))))) + (fConst1 * ((fRec5[0] * ((fRec4[0] * (fConst39 + (fConst37 * fRec4[0]))) + fConst35)) + fConst33)))))) + (fRec6[4] * (1.45128241697796e-10 + ((fRec4[0] * (1.44983258439356e-11 + (fConst1 * (fConst31 + (fConst29 * fRec4[0]))))) + (fConst1 * ((fRec5[0] * ((fRec4[0] * (fConst27 + (fConst25 * fRec4[0]))) + fConst23)) + fConst21)))))) + (fRec6[5] * (2.90256483395592e-11 + ((fRec4[0] * (2.89966516878713e-12 + (fConst1 * (fConst19 + (fConst18 * fRec4[0]))))) + (fConst1 * ((fRec5[0] * ((fRec4[0] * (fConst17 + (fConst16 * fRec4[0]))) + fConst15)) + fConst14)))))) / fTemp1));
		double fTemp4 = (4.66576522119352e-16 + fTemp2);
		double fTemp5 = (9.33153044238704e-14 * fRec4[0]);
		fRec7[0] = ((fConst60 * fRec7[1]) + (fConst59 * (fRec3[1] + fRec3[2])));
		fRec3[0] = (Ftrany(TRANY_TABLE_SVEL34_250k, ((fRec7[0] + (fConst56 * (((((((fRec6[0] * fTemp4) + (fRec6[1] * fTemp3)) + (fRec6[2] * ((0 - fTemp5) - 9.33153044238704e-16))) + (fRec6[3] * (9.33153044238704e-16 + fTemp5))) + (fRec6[4] * fTemp4)) + (fRec6[5] * fTemp3)) / fTemp1))) - 3.571981)) - 117.70440740740739);
		fRec2[0] = ((fConst65 * fRec2[1]) + (fConst64 * ((fConst61 * fRec3[0]) + (fConst62 * fRec3[1]))));
		fRec8[0] = ((fConst60 * fRec8[1]) + (fConst59 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_KT88_68k, ((fRec8[0] + fRec2[0]) - 5.562895)) - 43.96685185185183);
		fRec0[0] = ((fConst65 * fRec0[1]) + (fConst64 * ((fConst61 * fRec1[0]) + (fConst62 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)(fRec0[0] + (fSlow1 * fTemp0));
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec8[1] = fRec8[0];
		fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec7[1] = fRec7[0];
		for (int i=5; i>0; i--) fRec6[i] = fRec6[i-1];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("ruin.Intensity",N_("Intensity"),"S","",&fslider2, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("ruin.Level",N_("Level"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("ruin.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider0, 1e+02, 0.0, 1e+02, 1.0);
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

    b.create_small_rackknobr(PARAM("Level"), "Level");

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
