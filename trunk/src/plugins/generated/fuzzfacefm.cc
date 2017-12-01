// generated from file '../src/plugins/fuzzfacefm.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

#include "clipping.h"

namespace pluginlib {
namespace fuzzfacefm {

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
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	FAUSTFLOAT 	fslider1;
	double 	fRec1[2];
	FAUSTFLOAT 	fslider2;
	double 	fRec2[2];
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
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;
	double 	fConst74;
	double 	fConst75;
	double 	fConst76;
	double 	fConst77;
	double 	fRec3[4];
	double 	fConst78;
	double 	fConst79;
	double 	fConst80;
	double 	fConst81;
	double 	fConst82;
	double 	fConst83;
	double 	fConst84;
	double 	fConst85;
	double 	fConst86;


	int samplingFreq;
	gx_resample::FixedRateResampler smpCl;

	FAUSTFLOAT 	fsliderV0;
	double 	fRecV0[2];
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
	id = "fuzzfacefm";
	name = N_("Fuzz Face Fuller");
	groups = 0;
	description = N_("Micke Fuller Fuzz Face simulation"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("FF Fuller");     // shortname
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
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<4; i++) fRec3[i] = 0;


	for (int i=0; i<2; i++) fRecV0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(1.92e+05, max(1.0, (double)fSamplingFreq)));
	fConst1 = (7.09616600760317e-14 * fConst0);
	fConst2 = (7.07536443616085e-12 + fConst1);
	fConst3 = (7.09868387007524e-14 * fConst0);
	fConst4 = (7.07787491781686e-12 + fConst3);
	fConst5 = (2.51786247207522e-17 * fConst0);
	fConst6 = (0 - (1.61641996632585e-12 + fConst5));
	fConst7 = (1.41557498356337e-16 * fConst0);
	fConst8 = (7.17715343346006e-56 - fConst7);
	fConst9 = (1.41507288723217e-16 * fConst0);
	fConst10 = (fConst9 - 7.60754167271764e-56);
	fConst11 = (5.02096331201311e-20 * fConst0);
	fConst12 = (3.21835699976039e-15 + fConst11);
	fConst13 = (7.14615106636066e-14 * fConst0);
	fConst14 = ((fConst0 * (0 - (7.44787041826973e-12 + fConst13))) - 3.21721587173494e-11);
	fConst15 = (7.14054610111223e-14 * fConst0);
	fConst16 = (3.21607474370948e-11 + (fConst0 * (7.44216743501989e-12 + fConst15)));
	fConst17 = (5.60496524842164e-17 * fConst0);
	fConst18 = (1.69410806769336e-10 + (fConst0 * (1.63110208134281e-12 + fConst17)));
	fConst19 = (1.42504059392599e-16 * fConst0);
	fConst20 = ((fConst0 * (6.43443174346988e-16 + fConst19)) - 3.26234246975457e-55);
	fConst21 = (1.42392288693486e-16 * fConst0);
	fConst22 = (3.45797348759893e-55 + (fConst0 * (0 - (6.43214948741896e-16 + fConst21))));
	fConst23 = (1.1177069911304e-19 * fConst0);
	fConst24 = ((fConst0 * (0 - (3.24149709132582e-15 + fConst23))) - 1.46288954534563e-14);
	fConst25 = faustpower<2>(fConst0);
	fConst26 = (fConst25 * ((2.8137466561353e-14 * fConst0) - 6.459042388838901e-13));
	fConst27 = faustpower<3>(fConst0);
	fConst28 = (2.7855146611813e-14 * fConst27);
	fConst29 = (0 - (2.8231994953894e-16 * fConst27));
	fConst30 = (7.07787491781686e-12 - fConst3);
	fConst31 = (fConst1 - 7.07536443616085e-12);
	fConst32 = (fConst5 - 1.61641996632585e-12);
	fConst33 = (7.60754167271764e-56 + fConst9);
	fConst34 = (7.17715343346006e-56 + fConst7);
	fConst35 = (3.21835699976039e-15 - fConst11);
	fConst36 = (3.21721587173494e-11 + (fConst0 * (fConst13 - 7.44787041826973e-12)));
	fConst37 = ((fConst0 * (7.44216743501989e-12 - fConst15)) - 3.21607474370948e-11);
	fConst38 = ((fConst0 * (1.63110208134281e-12 - fConst17)) - 1.69410806769336e-10);
	fConst39 = (3.26234246975457e-55 + (fConst0 * (6.43443174346988e-16 - fConst19)));
	fConst40 = ((fConst0 * (fConst21 - 6.43214948741896e-16)) - 3.45797348759893e-55);
	fConst41 = (1.46288954534563e-14 + (fConst0 * (fConst23 - 3.24149709132582e-15)));
	fConst42 = (2.12960516102257e-13 * fConst0);
	fConst43 = (fConst42 - 7.07787491781686e-12);
	fConst44 = (2.12884980228095e-13 * fConst0);
	fConst45 = (7.07536443616085e-12 - fConst44);
	fConst46 = (7.55358741622564e-17 * fConst0);
	fConst47 = (1.61641996632585e-12 - fConst46);
	fConst48 = (4.24672495069012e-16 * fConst0);
	fConst49 = (0 - (7.17715343346006e-56 + fConst48));
	fConst50 = (4.24521866169651e-16 * fConst0);
	fConst51 = (7.60754167271764e-56 + fConst50);
	fConst52 = (1.50628899360393e-19 * fConst0);
	fConst53 = (fConst52 - 3.21835699976039e-15);
	fConst54 = (2.1438453199082e-13 * fConst0);
	fConst55 = (3.21721587173494e-11 + (fConst0 * (7.44787041826973e-12 - fConst54)));
	fConst56 = (2.14216383033367e-13 * fConst0);
	fConst57 = ((fConst0 * (fConst56 - 7.44216743501989e-12)) - 3.21607474370948e-11);
	fConst58 = (1.68148957452649e-16 * fConst0);
	fConst59 = ((fConst0 * (fConst58 - 1.63110208134281e-12)) - 1.69410806769336e-10);
	fConst60 = (4.27512178177797e-16 * fConst0);
	fConst61 = (3.26234246975457e-55 + (fConst0 * (fConst60 - 6.43443174346988e-16)));
	fConst62 = (4.27176866080457e-16 * fConst0);
	fConst63 = ((fConst0 * (6.43214948741896e-16 - fConst62)) - 3.45797348759893e-55);
	fConst64 = (3.35312097339121e-19 * fConst0);
	fConst65 = (1.46288954534563e-14 + (fConst0 * (3.24149709132582e-15 - fConst64)));
	fConst66 = (0 - (7.07787491781686e-12 + fConst42));
	fConst67 = (7.07536443616085e-12 + fConst44);
	fConst68 = (1.61641996632585e-12 + fConst46);
	fConst69 = (fConst48 - 7.17715343346006e-56);
	fConst70 = (7.60754167271764e-56 - fConst50);
	fConst71 = (0 - (3.21835699976039e-15 + fConst52));
	fConst72 = ((fConst0 * (7.44787041826973e-12 + fConst54)) - 3.21721587173494e-11);
	fConst73 = (3.21607474370948e-11 + (fConst0 * (0 - (7.44216743501989e-12 + fConst56))));
	fConst74 = (1.69410806769336e-10 + (fConst0 * (0 - (1.63110208134281e-12 + fConst58))));
	fConst75 = ((fConst0 * (0 - (6.43443174346988e-16 + fConst60))) - 3.26234246975457e-55);
	fConst76 = (3.45797348759893e-55 + (fConst0 * (6.43214948741896e-16 + fConst62)));
	fConst77 = ((fConst0 * (3.24149709132582e-15 + fConst64)) - 1.46288954534563e-14);
	fConst78 = ((1.240862275355639e-13 * fConst0) - 9.494792311593206e-13);
	fConst79 = (1.2284119655809702e-13 * fConst27);
	fConst80 = (0 - (1.2450309774667304e-15 * fConst27));
	fConst81 = (fConst25 * (6.459042388838901e-13 + (8.4412399684057e-14 * fConst0)));
	fConst82 = (8.356543983544001e-14 * fConst27);
	fConst83 = (0 - (8.4695984861682025e-16 * fConst27));
	fConst84 = (9.494792311593206e-13 + (4.1362075845187996e-14 * fConst0));
	fConst85 = (4.0947065519365e-14 * fConst27);
	fConst86 = (0 - (4.1501032582223993e-16 * fConst27));

	samplingFreq = 96000;
	smpCl.setup(fSamplingFreq, samplingFreq);
	fSamplingFreq = samplingFreq;

	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlowV0 = (0.0010000000000000009 * double(fsliderV0));

	double 	fSlow0 = (0.007000000000000006 * (1 - double(fslider0)));
	double 	fSlow1 = (0.007000000000000006 * (1 - double(fslider1)));
	double 	fSlow2 = (0.007000000000000006 * double(fslider2));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.993 * fRec0[1]));
		fRec1[0] = (fSlow1 + (0.993 * fRec1[1]));
		fRec2[0] = (fSlow2 + (0.993 * fRec2[1]));
		double fTemp0 = (7.31444772672817e-10 + ((fRec1[0] * (6.96979875434139e-54 + (fConst0 * (fConst24 + (fRec0[0] * (fConst22 + (fConst20 * fRec0[0]))))))) + (fConst0 * (fConst18 + ((fRec0[0] * (fConst16 + (fConst14 * fRec0[0]))) + (fRec2[0] * (((fRec1[0] * ((fConst0 * (fConst12 + (fRec0[0] * (fConst10 + (fConst8 * fRec0[0]))))) - 1.53335572595511e-54)) + (fConst0 * (fConst6 + (fRec0[0] * ((fConst4 * fRec0[0]) - fConst2))))) - 1.6091784998802e-10)))))));
		fRec3[0] = ((double)input0[i] - ((((fRec3[1] * (2.19433431801845e-09 + ((fRec1[0] * (2.09093962630242e-53 + (fConst0 * (fConst77 + (fRec0[0] * (fConst76 + (fConst75 * fRec0[0]))))))) + (fConst0 * (fConst74 + ((fRec0[0] * (fConst73 + (fConst72 * fRec0[0]))) + (fRec2[0] * (((fRec1[0] * ((fConst0 * (fConst71 + (fRec0[0] * (fConst70 + (fConst69 * fRec0[0]))))) - 1.53335572595511e-54)) + (fConst0 * (fConst68 + (fRec0[0] * (fConst67 + (fConst66 * fRec0[0])))))) - 1.6091784998802e-10)))))))) + (fRec3[2] * (2.19433431801845e-09 + ((fRec1[0] * (2.09093962630242e-53 + (fConst0 * (fConst65 + (fRec0[0] * (fConst63 + (fConst61 * fRec0[0]))))))) + (fConst0 * (fConst59 + ((fRec0[0] * (fConst57 + (fConst55 * fRec0[0]))) + (fRec2[0] * (1.6091784998802e-10 + ((fRec1[0] * (1.53335572595511e-54 + (fConst0 * (fConst53 + (fRec0[0] * (fConst51 + (fConst49 * fRec0[0]))))))) + (fConst0 * (fConst47 + (fRec0[0] * (fConst45 + (fConst43 * fRec0[0]))))))))))))))) + (fRec3[3] * (7.31444772672817e-10 + ((fRec1[0] * (6.96979875434139e-54 + (fConst0 * (fConst41 + (fRec0[0] * (fConst40 + (fConst39 * fRec0[0]))))))) + (fConst0 * (fConst38 + ((fRec0[0] * (fConst37 + (fConst36 * fRec0[0]))) + (fRec2[0] * (1.6091784998802e-10 + ((fRec1[0] * (1.53335572595511e-54 + (fConst0 * (fConst35 + (fRec0[0] * ((fConst34 * fRec0[0]) - fConst33)))))) + (fConst0 * (fConst32 + (fRec0[0] * (fConst31 + (fConst30 * fRec0[0]))))))))))))))) / fTemp0));
		output0[i] = (FAUSTFLOAT)(((((fRec3[0] * ((fRec0[0] * ((fConst86 * fRec0[0]) - fConst85)) + (fConst25 * ((fRec1[0] * ((fConst0 * ((1.12549866245409e-13 + (fRec0[0] * (2.7855146611813e-14 + (2.8231994953894e-16 * fRec0[0])))) - 1.40687332806762e-13)) - 6.459042388838901e-13)) + fConst84)))) + (fRec3[1] * ((fRec1[0] * ((fRec0[0] * ((fConst83 * fRec0[0]) - fConst82)) + fConst81)) + (fConst25 * ((fConst0 * ((4.96344910142255e-13 + (fRec0[0] * (1.2284119655809702e-13 + (1.2450309774667304e-15 * fRec0[0])))) - 6.20431137677819e-13)) - 9.494792311593206e-13))))) + (fRec3[2] * ((fRec0[0] * ((fConst80 * fRec0[0]) - fConst79)) + (fConst25 * ((fRec1[0] * (6.459042388838901e-13 + (fConst0 * ((3.37649598736228e-13 + (fRec0[0] * (8.356543983544001e-14 + (8.4695984861682025e-16 * fRec0[0])))) - 4.22061998420285e-13)))) + fConst78))))) + (fRec3[3] * ((fRec1[0] * ((fRec0[0] * ((fConst29 * fRec0[0]) - fConst28)) + fConst26)) + (fConst25 * (9.494792311593206e-13 + (fConst0 * ((1.65448303380752e-13 + (fRec0[0] * (4.0947065519365e-14 + (4.1501032582223993e-16 * fRec0[0])))) - 2.0681037922594e-13))))))) / fTemp0);
		// post processing
		for (int i=3; i>0; i--) fRec3[i] = fRec3[i-1];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}

	FAUSTFLOAT bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i=0; i<ReCount; i++) {
		bufCl[i] = (FAUSTFLOAT)asymclip4((double)bufCl[i]);
	}
	smpCl.down(bufCl, output0);

	for (int i=0; i<count; i++) {
		fRecV0[0] = ((0.999 * fRecV0[1]) + fSlowV0);
		output0[i] = (FAUSTFLOAT)((double)output0[i] * fRecV0[0]);
		// post processing
		fRecV0[1] = fRecV0[0];
	}

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("fuzzfacefm.Level",N_("Level"),"S","",&fsliderV0, 0.5, 0.0, 1, 0.01);
	reg.registerVar("fuzzfacefm.Drive",N_("Drive"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("fuzzfacefm.Fuzz",N_("Fuzz"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("fuzzfacefm.Input",N_("Input"),"S","",&fslider2, 0.5, 0.0, 1.0, 0.01);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<interface>\n\
  <!-- interface-requires gxwidgets 0.0 -->\n\
  <requires lib=\"gtk+\" version=\"2.20\"/>\n\
  <!-- interface-naming-policy project-wide -->\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can_focus\">False</property>\n\
    <child>\n\
      <object class=\"GtkVBox\" id=\"vbox1\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can_focus\">False</property>\n\
        <child>\n\
          <object class=\"GtkHBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GtkHBox\" id=\"hbox1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"spacing\">10</property>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label1:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">fuzzfacefm.Input</property>\n\
                        <property name=\"label_ref\">label1:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label2:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">fuzzfacefm.Drive</property>\n\
                        <property name=\"label_ref\">label2:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label3:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">fuzzfacefm.Fuzz</property>\n\
                        <property name=\"label_ref\">label3:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox5\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label4:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxMidKnob\" id=\"gxbigknob4\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">fuzzfacefm.Level</property>\n\
                        <property name=\"label_ref\">label4:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">3</property>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"pack_type\">end</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">False</property>\n\
            <property name=\"position\">0</property>\n\
          </packing>\n\
        </child>\n\
        <child>\n\
          <object class=\"GtkHBox\" id=\"minibox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GxHSlider\" id=\"gxhslider1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">True</property>\n\
                <property name=\"receives_default\">True</property>\n\
                <property name=\"round_digits\">0</property>\n\
                <property name=\"var_id\">fuzzfacefm.Level</property>\n\
                <property name=\"show_value\">False</property>\n\
                <property name=\"value_position\">right</property>\n\
                <property name=\"value_xalign\">0.52000000000000002</property>\n\
                <property name=\"label_ref\">label0:rack_label</property>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">False</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
            <child>\n\
              <object class=\"GtkLabel\" id=\"label0:rack_label\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"xalign\">0</property>\n\
                <property name=\"label\" translatable=\"yes\">Level</property>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">False</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"position\">1</property>\n\
              </packing>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">True</property>\n\
            <property name=\"position\">1</property>\n\
          </packing>\n\
        </child>\n\
      </object>\n\
    </child>\n\
  </object>\n\
</interface>\n\
";

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade(glade_def);
        return 0;
    }
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("fuzzfacefm" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Fuzz"), N_("Fuzz"));
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Input"), N_("Input"));

    b.create_small_rackknobr(PARAM("Drive"), N_("Drive"));

    b.create_small_rackknobr(PARAM("Fuzz"), N_("Fuzz"));

    b.create_small_rackknobr(PARAM("Level"), N_("Level"));
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

} // end namespace fuzzfacefm
} // end namespace pluginlib
