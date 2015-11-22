// generated from file '../src/plugins/gcb_95.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace gcb_95 {

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
	double 	fVec0[2];
	double 	fConst32;
	double 	fRec2[2];
	double 	fRec1[5];
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
	FAUSTFLOAT 	fslider1;
	double 	fRec3[2];
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
	id = "GCB_95";
	name = N_("GCB 95");
	groups = 0;
	description = N_("Linear filter simulating the GCB 95 crybaby circuit"); // description (tooltip)
	category = N_("Guitar Effects");       // category
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
	for (int i=0; i<5; i++) fRec1[i] = 0;
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
	fConst1 = double(iConst0);
	fConst2 = (6.9672955745145e-20 * fConst1);
	fConst3 = (fConst1 * ((fConst1 * (0 - (9.30061422376548e-18 + fConst2))) - 9.53707992555105e-14));
	fConst4 = (3.8766476861454e-19 * fConst1);
	fConst5 = (2.16751816489796e-12 + (fConst1 * (7.68323461702748e-14 + (fConst1 * (2.92076464853813e-17 + fConst4)))));
	fConst6 = (1.08819023657393e-20 * fConst1);
	fConst7 = (1.29191360120173e-11 + (fConst1 * (5.44712113689982e-13 + (fConst1 * (2.80985481683452e-17 + fConst6)))));
	fConst8 = (1.96834437163512e-21 * fConst1);
	fConst9 = (fConst1 * (8.09470493272714e-14 + (fConst1 * (fConst8 - 5.48587515516469e-17))));
	fConst10 = (1.96653248770188e-21 * fConst1);
	fConst11 = (1.78155704878595e-12 + (fConst1 * ((fConst1 * (5.48942867863191e-17 - fConst10)) - 8.21432353321142e-14)));
	fConst12 = (7.41350388334374e-21 * fConst1);
	fConst13 = (1.8397056665289e-12 + (fConst1 * ((fConst1 * (2.47418541205506e-16 - fConst12)) - 3.69672787496925e-13)));
	fConst14 = (fConst1 * ((fConst1 * (9.30061422376548e-18 - fConst2)) - 9.53707992555105e-14));
	fConst15 = ((fConst1 * (7.68323461702748e-14 + (fConst1 * (fConst4 - 2.92076464853813e-17)))) - 2.16751816489796e-12);
	fConst16 = ((fConst1 * (5.44712113689982e-13 + (fConst1 * (fConst6 - 2.80985481683452e-17)))) - 1.29191360120173e-11);
	fConst17 = (2.7869182298058e-19 * fConst1);
	fConst18 = faustpower<2>(fConst1);
	fConst19 = (fConst18 * (fConst17 - 1.8601228447531e-17));
	fConst20 = (1.55065907445816e-18 * fConst1);
	fConst21 = ((fConst18 * (5.84152929707626e-17 - fConst20)) - 4.33503632979593e-12);
	fConst22 = (4.3527609462957e-20 * fConst1);
	fConst23 = ((fConst18 * (5.61970963366905e-17 - fConst22)) - 2.58382720240347e-11);
	fConst24 = (1.90741598511021e-13 - (4.1803773447087e-19 * fConst18));
	fConst25 = ((2.32598861168724e-18 * fConst18) - 1.5366469234055e-13);
	fConst26 = ((6.52914141944355e-20 * fConst18) - 1.08942422737996e-12);
	fConst27 = (fConst18 * (1.8601228447531e-17 + fConst17));
	fConst28 = (4.33503632979593e-12 + (fConst18 * (0 - (5.84152929707626e-17 + fConst20))));
	fConst29 = (2.58382720240347e-11 + (fConst18 * (0 - (5.61970963366905e-17 + fConst22))));
	fConst30 = (716.6140154481191 / double(iConst0));
	fConst31 = (1 - fConst30);
	fConst32 = (1.0 / (1 + fConst30));
	fConst33 = (7.87337748654046e-21 * fConst1);
	fConst34 = (fConst18 * (1.09717503103294e-16 - fConst33));
	fConst35 = (7.86612995080753e-21 * fConst1);
	fConst36 = (3.56311409757189e-12 + (fConst18 * (fConst35 - 1.09788573572638e-16)));
	fConst37 = (2.9654015533375e-20 * fConst1);
	fConst38 = (3.67941133305779e-12 + (fConst18 * (fConst37 - 4.94837082411013e-16)));
	fConst39 = ((1.18100662298107e-20 * fConst18) - 1.61894098654543e-13);
	fConst40 = (1.64286470664228e-13 - (1.17991949262113e-20 * fConst18));
	fConst41 = (7.39345574993849e-13 - (4.44810233000624e-20 * fConst18));
	fConst42 = (fConst18 * (0 - (1.09717503103294e-16 + fConst33)));
	fConst43 = ((fConst18 * (1.09788573572638e-16 + fConst35)) - 3.56311409757189e-12);
	fConst44 = ((fConst18 * (4.94837082411013e-16 + fConst37)) - 3.67941133305779e-12);
	fConst45 = (fConst1 * (8.09470493272714e-14 + (fConst1 * (5.48587515516469e-17 + fConst8))));
	fConst46 = ((fConst1 * ((fConst1 * (0 - (5.48942867863191e-17 + fConst10))) - 8.21432353321142e-14)) - 1.78155704878595e-12);
	fConst47 = ((fConst1 * ((fConst1 * (0 - (2.47418541205506e-16 + fConst12))) - 3.69672787496925e-13)) - 1.8397056665289e-12);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (4.748558434412966e-05 * (exp((5 * (1 - double(fslider0)))) - 1));
	double 	fSlow1 = (0.007000000000000006 * pow(10,(0.05 * double(fslider1))));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		double fTemp0 = (4.92617764749537e-11 + (fConst1 * (fConst7 + (fRec0[0] * (fConst5 + (fConst3 * fRec0[0]))))));
		double fTemp1 = (double)input0[i];
		fVec0[0] = fTemp1;
		fRec2[0] = (fConst32 * ((fVec0[0] - fVec0[1]) + (fConst31 * fRec2[1])));
		fRec1[0] = (fRec2[0] - (((((fRec1[1] * (1.97047105899815e-10 + (fConst1 * (fConst29 + (fRec0[0] * (fConst28 + (fConst27 * fRec0[0]))))))) + (fRec1[2] * (2.95570658849723e-10 + (fConst18 * (fConst26 + (fRec0[0] * (fConst25 + (fConst24 * fRec0[0])))))))) + (fRec1[3] * (1.97047105899815e-10 + (fConst1 * (fConst23 + (fRec0[0] * (fConst21 + (fConst19 * fRec0[0])))))))) + (fRec1[4] * (4.92617764749537e-11 + (fConst1 * (fConst16 + (fRec0[0] * (fConst15 + (fConst14 * fRec0[0])))))))) / fTemp0));
		fRec3[0] = ((0.993 * fRec3[1]) + fSlow1);
		output0[i] = (FAUSTFLOAT)(fConst1 * ((fRec3[0] * (((((fRec1[0] * (fConst47 + (fRec0[0] * (fConst46 + (fConst45 * fRec0[0]))))) + (fRec1[1] * (fConst44 + (fRec0[0] * (fConst43 + (fConst42 * fRec0[0])))))) + (fConst1 * (fRec1[2] * (fConst41 + (fRec0[0] * (fConst40 + (fConst39 * fRec0[0]))))))) + (fRec1[3] * (fConst38 + (fRec0[0] * (fConst36 + (fConst34 * fRec0[0])))))) + (fRec1[4] * (fConst13 + (fRec0[0] * (fConst11 + (fConst9 * fRec0[0]))))))) / fTemp0));
		// post processing
		fRec3[1] = fRec3[0];
		for (int i=4; i>0; i--) fRec1[i] = fRec1[i-1];
		fRec2[1] = fRec2[0];
		fVec0[1] = fVec0[0];
		fRec0[1] = fRec0[0];
	}

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("GCB_95.Volume","","S","",&fslider1, 0.0, -2e+01, 4.0, 0.1);
	reg.registerVar("GCB_95.hotpotz",N_("Wah"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("GCB_95" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("hotpotz"), "Wah");
b.closeBox();
b.openHorizontalBox("");
    b.create_small_rackknobr(PARAM("Volume"), "Volume");

    b.create_small_rackknobr(PARAM("hotpotz"), "Wah");
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

} // end namespace gcb_95
} // end namespace pluginlib
