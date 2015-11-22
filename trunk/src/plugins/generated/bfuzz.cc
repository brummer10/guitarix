// generated from file '../src/plugins/bfuzz.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace bfuzz {

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
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	FAUSTFLOAT 	fslider1;
	double 	fRec8[2];
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	FAUSTFLOAT 	fslider2;
	double 	fRec9[2];
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
	double 	fRec10[5];
	double 	fConst38;
	double 	fConst39;
	FAUSTFLOAT 	fslider3;
	double 	fRec11[2];
	double 	fVec0[2];
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fRec12[2];
	double 	fRec5[3];
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fRec4[2];
	double 	fConst52;
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fRec13[2];
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
	id = "bfuzz";
	name = N_("Bass Fuzz Pedal");
	groups = 0;
	description = N_("Bass Fuzz Pedal"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("Bass Fuzz Pedal");     // shortname
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
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<5; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
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
	fConst1 = tan((50265.48245743669 / double(iConst0)));
	fConst2 = (2 * (1 - (1.0 / faustpower<2>(fConst1))));
	fConst3 = (1.0 / fConst1);
	fConst4 = (1 + ((fConst3 - 1.0000000000000004) / fConst1));
	fConst5 = (1.0 / (1 + ((1.0000000000000004 + fConst3) / fConst1)));
	fConst6 = double(iConst0);
	fConst7 = (1.90624114055858e-19 * fConst6);
	fConst8 = (6.98583678876617e-09 + (fConst6 * (1.41002006493022e-10 + (fConst6 * (1.0005063720083e-14 + fConst7)))));
	fConst9 = (1.8235902618655e-20 * fConst6);
	fConst10 = (4.14452332248826e-10 + (fConst6 * (9.51587528271067e-12 + (fConst6 * (8.73857822258011e-15 + fConst9)))));
	fConst11 = ((fConst6 * ((fConst6 * (0 - (9.05150991318089e-15 + fConst7))) - 9.57238853136628e-11)) - 4.70914107604798e-09);
	fConst12 = ((fConst6 * ((fConst6 * ((fConst6 * (0 - (8.82979918090661e-15 + fConst9))) - 5.32286268006641e-11)) - 2.42569918771087e-09)) - 9.41937118747331e-10);
	fConst13 = (1.65780932898435e-16 * fConst6);
	fConst14 = (fConst13 - 8.29281439339673e-13);
	fConst15 = (7.76911913609341e-14 * fConst6);
	fConst16 = (fConst15 - 3.88632527694127e-10);
	fConst17 = ((fConst6 * (1.41002006493022e-10 + (fConst6 * (fConst7 - 1.0005063720083e-14)))) - 6.98583678876617e-09);
	fConst18 = ((fConst6 * (9.51587528271067e-12 + (fConst6 * (fConst9 - 8.73857822258011e-15)))) - 4.14452332248826e-10);
	fConst19 = (4.70914107604798e-09 + (fConst6 * ((fConst6 * (9.05150991318089e-15 - fConst7)) - 9.57238853136628e-11)));
	fConst20 = ((fConst6 * (2.42569918771087e-09 + (fConst6 * ((fConst6 * (8.82979918090661e-15 - fConst9)) - 5.32286268006641e-11)))) - 9.41937118747331e-10);
	fConst21 = (7.6249645622343e-19 * fConst6);
	fConst22 = faustpower<2>(fConst6);
	fConst23 = ((fConst22 * (2.00101274401661e-14 - fConst21)) - 1.39716735775323e-08);
	fConst24 = (7.294361047462e-20 * fConst6);
	fConst25 = ((fConst22 * (1.74771564451602e-14 - fConst24)) - 8.28904664497652e-10);
	fConst26 = (9.41828215209595e-09 + (fConst22 * (fConst21 - 1.81030198263618e-14)));
	fConst27 = ((fConst6 * (4.85139837542174e-09 + (fConst22 * (fConst24 - 1.76595983618132e-14)))) - 3.76774847498933e-09);
	fConst28 = (1.0941541571193e-19 * fConst22);
	fConst29 = (fConst28 - 1.90317505654213e-11);
	fConst30 = (1.14374468433515e-18 * fConst22);
	fConst31 = (1.91447770627326e-10 - fConst30);
	fConst32 = (fConst30 - 2.82004012986045e-10);
	fConst33 = ((fConst22 * (1.06457253601328e-10 - fConst28)) - 5.65162271248399e-09);
	fConst34 = (1.39716735775323e-08 + (fConst22 * (0 - (2.00101274401661e-14 + fConst21))));
	fConst35 = (8.28904664497652e-10 + (fConst22 * (0 - (1.74771564451602e-14 + fConst24))));
	fConst36 = ((fConst22 * (1.81030198263618e-14 + fConst21)) - 9.41828215209595e-09);
	fConst37 = ((fConst6 * ((fConst22 * (1.76595983618132e-14 + fConst24)) - 4.85139837542174e-09)) - 3.76774847498933e-09);
	fConst38 = (0 - (8.29281439339673e-13 + fConst13));
	fConst39 = (0 - (3.88632527694127e-10 + fConst15));
	fConst40 = (1 + fConst3);
	fConst41 = (fConst22 / fConst40);
	fConst42 = (0 - ((1 - fConst3) / fConst40));
	fConst43 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst44 = (1 + fConst43);
	fConst45 = (0.027 / fConst44);
	fConst46 = (0 - ((1 - fConst43) / fConst44));
	fConst47 = (1.0 / tan((34.55751918948772 / double(iConst0))));
	fConst48 = (0 - fConst47);
	fConst49 = (1 + fConst47);
	fConst50 = (0.025 / fConst49);
	fConst51 = (0 - ((1 - fConst47) / fConst49));
	fConst52 = (1.0 / fConst40);
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
	double 	fSlow3 = (0.007000000000000006 * double(fslider2));
	double 	fSlow4 = (0.007000000000000006 * double(fslider3));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec8[0] = ((0.993 * fRec8[1]) + fSlow2);
		fRec9[0] = ((0.993 * fRec9[1]) + fSlow3);
		double fTemp1 = (1.07025933546545e-08 + ((fConst12 * fRec8[0]) + (fConst6 * ((fRec9[0] * (fConst11 + (fConst10 * fRec8[0]))) + fConst8))));
		double fTemp2 = (1.65780932898435e-16 * fRec8[0]);
		fRec10[0] = ((fSlow0 * fTemp0) - (((((fRec10[1] * (4.2810373418618e-08 + ((fConst37 * fRec8[0]) + (fConst6 * ((fRec9[0] * (fConst36 + (fConst35 * fRec8[0]))) + fConst34))))) + (fRec10[2] * (6.4215560127927e-08 + ((fConst33 * fRec8[0]) + (fConst22 * (fConst32 + (fRec9[0] * (fConst31 + (fConst29 * fRec8[0]))))))))) + (fRec10[3] * (4.2810373418618e-08 + ((fConst27 * fRec8[0]) + (fConst6 * ((fRec9[0] * (fConst26 + (fConst25 * fRec8[0]))) + fConst23)))))) + (fRec10[4] * (1.07025933546545e-08 + ((fConst20 * fRec8[0]) + (fConst6 * ((fRec9[0] * (fConst19 + (fConst18 * fRec8[0]))) + fConst17)))))) / fTemp1));
		double fTemp3 = (3.3156186579687e-16 * fRec8[0]);
		double fTemp4 = (1.55382382721868e-13 + fTemp3);
		double fTemp5 = ((0 - fTemp3) - 1.55382382721868e-13);
		fRec11[0] = ((0.993 * fRec11[1]) + fSlow4);
		double fTemp6 = ((fRec11[0] * (((((fRec10[0] * ((fConst39 + (fConst38 * fRec8[0])) + (fConst6 * (fRec9[0] * (7.76911913609341e-14 + fTemp2))))) + (fConst6 * (fRec10[1] * (fTemp4 + (fRec9[0] * fTemp5))))) + (fRec10[2] * (7.77265055388254e-10 + (1.65856287867935e-12 * fRec8[0])))) + (fConst6 * (fRec10[3] * (fTemp5 + (fRec9[0] * fTemp4))))) + (fRec10[4] * ((fConst16 + (fConst14 * fRec8[0])) + (fConst6 * (fRec9[0] * ((0 - fTemp2) - 7.76911913609341e-14))))))) / fTemp1);
		fVec0[0] = fTemp6;
		fRec7[0] = ((fConst42 * fRec7[1]) + (fConst41 * (fVec0[0] + fVec0[1])));
		fRec6[0] = (fRec7[0] - (fConst5 * ((fConst4 * fRec6[2]) + (fConst2 * fRec6[1]))));
		fRec12[0] = ((fConst46 * fRec12[1]) + (fConst45 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec12[0] + (fConst5 * (fRec6[2] + (fRec6[0] + (2 * fRec6[1]))))) - 5.571981)) - 43.63033333333331);
		fRec4[0] = ((fConst51 * fRec4[1]) + (fConst50 * ((fConst47 * fRec5[0]) + (fConst48 * fRec5[1]))));
		fRec3[0] = ((fConst42 * fRec3[1]) + (fConst52 * (fRec4[0] + fRec4[1])));
		fRec2[0] = (fRec3[0] - (fConst5 * ((fConst4 * fRec2[2]) + (fConst2 * fRec2[1]))));
		fRec13[0] = ((fConst46 * fRec13[1]) + (fConst45 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec13[0] + (fConst5 * (fRec2[2] + (fRec2[0] + (2 * fRec2[1]))))) - 5.571981)) - 43.63033333333331);
		fRec0[0] = ((fConst51 * fRec0[1]) + (fConst50 * ((fConst47 * fRec1[0]) + (fConst48 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)(fRec0[0] + (fSlow1 * fTemp0));
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec13[1] = fRec13[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec12[1] = fRec12[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fVec0[1] = fVec0[0];
		fRec11[1] = fRec11[0];
		for (int i=4; i>0; i--) fRec10[i] = fRec10[i-1];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
	}

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("bfuzz.Drive",N_("Drive"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("bfuzz.Level",N_("Level"),"S","",&fslider3, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("bfuzz.Thickness",N_("Thickness"),"S","",&fslider2, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("bfuzz.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider0, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("bfuzz" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Level"), "Level");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Level"), "Level");

    b.create_small_rackknobr(PARAM("Drive"), "Drive");

    b.create_small_rackknobr(PARAM("Thickness"), "Thickness");
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

} // end namespace bfuzz
} // end namespace pluginlib
