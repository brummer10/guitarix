// generated from file '../src/plugins/fuzzfacefm.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

#include "clipping.h"

namespace pluginlib {
namespace fuzzfacefm {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	double fRec0[2];
	double fConst0;
	double fConst2;
	double fConst4;
	double fConst6;
	FAUSTFLOAT fVslider1;
	double fRec1[2];
	double fConst8;
	double fConst10;
	double fConst12;
	double fConst13;
	double fConst15;
	double fConst16;
	double fConst18;
	double fConst19;
	double fConst21;
	double fConst23;
	FAUSTFLOAT fVslider2;
	double fRec2[2];
	double fConst24;
	double fConst26;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
	double fConst46;
	double fConst48;
	double fConst50;
	double fConst52;
	double fConst54;
	double fConst56;
	double fConst58;
	double fConst60;
	double fConst62;
	double fConst64;
	double fConst66;
	double fConst68;
	double fConst70;
	double fConst71;
	double fConst72;
	double fConst73;
	double fConst74;
	double fConst75;
	double fConst76;
	double fConst77;
	double fConst78;
	double fConst79;
	double fConst80;
	double fConst81;
	double fConst82;
	double fRec3[4];
	double fConst84;
	double fConst86;
	double fConst87;
	double fConst88;
	double fConst89;
	double fConst90;


	gx_resample::FixedRateResampler smpCl;

	FAUSTFLOAT 	fsliderV0;
	double 	fRecV0[2];
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int sample_rate, PluginDef*);
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec1[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec2[l2] = 0.0;
	for (int l3 = 0; l3 < 4; l3 = l3 + 1) fRec3[l3] = 0.0;


	for (int i=0; i<2; i++) fRecV0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 1.42504059392599e-16 * fConst0;
	fConst2 = fConst0 * (fConst1 + 6.43443174346988e-16) + -3.26234246975457e-55;
	double fConst3 = 1.42392288693486e-16 * fConst0;
	fConst4 = fConst0 * (-6.43214948741896e-16 - fConst3);
	double fConst5 = 1.1177069911304e-19 * fConst0;
	fConst6 = fConst0 * (-3.24149709132582e-15 - fConst5);
	double fConst7 = 7.14615106636066e-14 * fConst0;
	fConst8 = fConst0 * (-7.44787041826973e-12 - fConst7) + -3.21721587173494e-11;
	double fConst9 = 7.14054610111223e-14 * fConst0;
	fConst10 = fConst0 * (fConst9 + 7.44216743501989e-12);
	double fConst11 = 5.60496524842164e-17 * fConst0;
	fConst12 = fConst0 * (fConst11 + 1.63110208134281e-12);
	fConst13 = 7.09616600760317e-14 * fConst0;
	double fConst14 = 7.09868387007524e-14 * fConst0;
	fConst15 = fConst14 + 7.07787491781686e-12;
	fConst16 = mydsp_faustpower2_f(fConst0);
	double fConst17 = 1.41557498356337e-16 * fConst0;
	fConst18 = 7.17715343346006e-56 - fConst17;
	fConst19 = 1.41507288723217e-16 * fConst0;
	double fConst20 = 5.02096331201311e-20 * fConst0;
	fConst21 = fConst0 * (fConst0 * (fConst20 + 3.21835699976039e-15) + -1.53335572595511e-54);
	double fConst22 = 2.51786247207522e-17 * fConst0;
	fConst23 = fConst0 * (fConst0 * (-1.61641996632585e-12 - fConst22) + -1.6091784998802e-10);
	fConst24 = mydsp_faustpower3_f(fConst0);
	double fConst25 = 2.8137466561353e-14 * fConst0;
	fConst26 = fConst16 * (fConst25 + -6.459042388838901e-13);
	double fConst27 = 4.1362075845187996e-14 * fConst0;
	fConst28 = fConst16 * (9.494792311593206e-13 - fConst27);
	fConst29 = -7.07536443616085e-12 - fConst13;
	fConst30 = fConst19 + -7.60754167271764e-56;
	fConst31 = fConst4 + 3.45797348759893e-55;
	fConst32 = fConst6 + -1.46288954534563e-14;
	fConst33 = fConst10 + 3.21607474370948e-11;
	fConst34 = fConst12 + 1.69410806769336e-10;
	fConst35 = 7.07787491781686e-12 - fConst14;
	fConst36 = fConst13 + -7.07536443616085e-12;
	fConst37 = fConst17 + 7.17715343346006e-56;
	fConst38 = -7.60754167271764e-56 - fConst19;
	fConst39 = fConst0 * (fConst0 * (3.21835699976039e-15 - fConst20) + 1.53335572595511e-54);
	fConst40 = fConst0 * (fConst0 * (fConst22 + -1.61641996632585e-12) + 1.6091784998802e-10);
	fConst41 = fConst0 * (6.43443174346988e-16 - fConst1) + 3.26234246975457e-55;
	fConst42 = fConst0 * (fConst3 + -6.43214948741896e-16) + -3.45797348759893e-55;
	fConst43 = fConst0 * (fConst5 + -3.24149709132582e-15) + 1.46288954534563e-14;
	fConst44 = fConst0 * (fConst7 + -7.44787041826973e-12) + 3.21721587173494e-11;
	fConst45 = fConst0 * (7.44216743501989e-12 - fConst9) + -3.21607474370948e-11;
	fConst46 = fConst0 * (1.63110208134281e-12 - fConst11) + -1.69410806769336e-10;
	double fConst47 = 2.12960516102257e-13 * fConst0;
	fConst48 = fConst47 + -7.07787491781686e-12;
	double fConst49 = 2.12884980228095e-13 * fConst0;
	fConst50 = 7.07536443616085e-12 - fConst49;
	double fConst51 = 4.24672495069012e-16 * fConst0;
	fConst52 = -7.17715343346006e-56 - fConst51;
	double fConst53 = 4.24521866169651e-16 * fConst0;
	fConst54 = fConst53 + 7.60754167271764e-56;
	double fConst55 = 1.50628899360393e-19 * fConst0;
	fConst56 = fConst0 * (fConst0 * (fConst55 + -3.21835699976039e-15) + 1.53335572595511e-54);
	double fConst57 = 7.55358741622564e-17 * fConst0;
	fConst58 = fConst0 * (fConst0 * (1.61641996632585e-12 - fConst57) + 1.6091784998802e-10);
	double fConst59 = 4.27512178177797e-16 * fConst0;
	fConst60 = fConst0 * (fConst59 + -6.43443174346988e-16) + 3.26234246975457e-55;
	double fConst61 = 4.27176866080457e-16 * fConst0;
	fConst62 = fConst0 * (6.43214948741896e-16 - fConst61) + -3.45797348759893e-55;
	double fConst63 = 3.35312097339121e-19 * fConst0;
	fConst64 = fConst0 * (3.24149709132582e-15 - fConst63) + 1.46288954534563e-14;
	double fConst65 = 2.1438453199082e-13 * fConst0;
	fConst66 = fConst0 * (7.44787041826973e-12 - fConst65) + 3.21721587173494e-11;
	double fConst67 = 2.14216383033367e-13 * fConst0;
	fConst68 = fConst0 * (fConst67 + -7.44216743501989e-12) + -3.21607474370948e-11;
	double fConst69 = 1.68148957452649e-16 * fConst0;
	fConst70 = fConst0 * (fConst69 + -1.63110208134281e-12) + -1.69410806769336e-10;
	fConst71 = -7.07787491781686e-12 - fConst47;
	fConst72 = fConst49 + 7.07536443616085e-12;
	fConst73 = fConst51 + -7.17715343346006e-56;
	fConst74 = 7.60754167271764e-56 - fConst53;
	fConst75 = fConst0 * (fConst0 * (-3.21835699976039e-15 - fConst55) + -1.53335572595511e-54);
	fConst76 = fConst0 * (fConst0 * (fConst57 + 1.61641996632585e-12) + -1.6091784998802e-10);
	fConst77 = fConst0 * (-6.43443174346988e-16 - fConst59) + -3.26234246975457e-55;
	fConst78 = fConst0 * (fConst61 + 6.43214948741896e-16) + 3.45797348759893e-55;
	fConst79 = fConst0 * (fConst63 + 3.24149709132582e-15) + -1.46288954534563e-14;
	fConst80 = fConst0 * (fConst65 + 7.44787041826973e-12) + -3.21721587173494e-11;
	fConst81 = fConst0 * (-7.44216743501989e-12 - fConst67) + 3.21607474370948e-11;
	fConst82 = fConst0 * (-1.63110208134281e-12 - fConst69) + 1.69410806769336e-10;
	double fConst83 = 8.4412399684057e-14 * fConst0;
	fConst84 = fConst16 * (6.459042388838901e-13 - fConst83);
	double fConst85 = 1.240862275355639e-13 * fConst0;
	fConst86 = fConst16 * (fConst85 + -9.494792311593206e-13);
	fConst87 = fConst16 * (fConst83 + 6.459042388838901e-13);
	fConst88 = fConst16 * (-9.494792311593206e-13 - fConst85);
	fConst89 = fConst16 * (-6.459042388838901e-13 - fConst25);
	fConst90 = fConst16 * (fConst27 + 9.494792311593206e-13);

	sample_rate = 96000;
	smpCl.setup(fSampleRate, sample_rate);
	fSampleRate = sample_rate;

	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlowV0 = (0.0010000000000000009 * double(fsliderV0));

	double fSlow0 = 0.007000000000000006 * (1.0 - double(fVslider0));
	double fSlow1 = 0.007000000000000006 * (1.0 - double(fVslider1));
	double fSlow2 = 0.007000000000000006 * double(fVslider2);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		double fTemp0 = fConst2 * fRec0[0];
		fRec1[0] = fSlow1 + 0.993 * fRec1[1];
		double fTemp1 = fConst8 * fRec0[0];
		double fTemp2 = fConst15 * fRec0[0];
		double fTemp3 = fConst18 * fRec0[0];
		fRec2[0] = fSlow2 + 0.993 * fRec2[1];
		double fTemp4 = 4.1501032582223993e-16 * fRec0[0];
		double fTemp5 = 2.8231994953894e-16 * fRec0[0];
		fRec3[0] = double(input0[i0]) - (fRec3[1] * (fConst0 * (fConst82 + fRec0[0] * (fConst81 + fConst80 * fRec0[0])) + fRec1[0] * (fConst0 * (fConst79 + fRec0[0] * (fConst78 + fConst77 * fRec0[0])) + 2.09093962630242e-53) + fRec2[0] * (fConst76 + fRec1[0] * (fConst75 + fConst16 * fRec0[0] * (fConst74 + fConst73 * fRec0[0])) + fConst16 * fRec0[0] * (fConst72 + fConst71 * fRec0[0])) + 2.19433431801845e-09) + fRec3[2] * (fConst0 * (fConst70 + fRec0[0] * (fConst68 + fConst66 * fRec0[0])) + fRec1[0] * (fConst0 * (fConst64 + fRec0[0] * (fConst62 + fConst60 * fRec0[0])) + 2.09093962630242e-53) + fRec2[0] * (fConst58 + fRec1[0] * (fConst56 + fConst16 * fRec0[0] * (fConst54 + fConst52 * fRec0[0])) + fConst16 * fRec0[0] * (fConst50 + fConst48 * fRec0[0])) + 2.19433431801845e-09) + fRec3[3] * (fConst0 * (fConst46 + fRec0[0] * (fConst45 + fConst44 * fRec0[0])) + fRec1[0] * (fConst0 * (fConst43 + fRec0[0] * (fConst42 + fConst41 * fRec0[0])) + 6.96979875434139e-54) + fRec2[0] * (fConst40 + fRec1[0] * (fConst39 + fConst16 * fRec0[0] * (fConst38 + fConst37 * fRec0[0])) + fConst16 * fRec0[0] * (fConst36 + fConst35 * fRec0[0])) + 7.31444772672817e-10)) / (fConst0 * (fConst34 + fRec0[0] * (fConst33 + fTemp1)) + fRec1[0] * (fConst0 * (fConst32 + fRec0[0] * (fConst31 + fTemp0)) + 6.96979875434139e-54) + fRec2[0] * (fConst23 + fRec1[0] * (fConst21 + fConst16 * fRec0[0] * (fConst30 + fTemp3)) + fConst16 * fRec0[0] * (fConst29 + fTemp2)) + 7.31444772672817e-10);
		double fTemp6 = 1.2450309774667304e-15 * fRec0[0];
		double fTemp7 = 8.4695984861682025e-16 * fRec0[0];
		output0[i0] = FAUSTFLOAT((fRec3[0] * (fConst90 + fRec1[0] * (fConst89 + fConst24 * fRec0[0] * (fTemp5 + 2.7855146611813e-14)) + fConst24 * fRec0[0] * (-4.0947065519365e-14 - fTemp4)) + fRec3[1] * (fConst88 + fRec1[0] * (fConst87 + fConst24 * fRec0[0] * (-8.356543983544001e-14 - fTemp7)) + fConst24 * fRec0[0] * (fTemp6 + 1.2284119655809702e-13)) + fRec3[2] * (fConst86 + fRec1[0] * (fConst84 + fConst24 * fRec0[0] * (fTemp7 + 8.356543983544001e-14)) + fConst24 * fRec0[0] * (-1.2284119655809702e-13 - fTemp6)) + fRec3[3] * (fConst28 + fRec1[0] * (fConst26 + fConst24 * fRec0[0] * (-2.7855146611813e-14 - fTemp5)) + fConst24 * fRec0[0] * (fTemp4 + 4.0947065519365e-14))) / (fRec2[0] * (fConst23 + fRec1[0] * (fConst21 + fConst16 * fRec0[0] * (fConst19 + fTemp3 + -7.60754167271764e-56)) + fConst16 * fRec0[0] * (fTemp2 + -7.07536443616085e-12 - fConst13)) + fConst0 * (fConst12 + fRec0[0] * (fConst10 + fTemp1 + 3.21607474370948e-11) + 1.69410806769336e-10) + fRec1[0] * (fConst0 * (fConst6 + fRec0[0] * (fConst4 + fTemp0 + 3.45797348759893e-55) + -1.46288954534563e-14) + 6.96979875434139e-54) + 7.31444772672817e-10));
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
			fRec3[j0] = fRec3[j0 - 1];
		}
	}

	FAUSTFLOAT bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		bufCl[i0] = FAUSTFLOAT(asymclip4(double(bufCl[i0])));
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
	reg.registerFloatVar("fuzzfacefm.Level",N_("Level"),"S","",&fsliderV0, 0.5, 0.0, 1, 0.01, 0);
	reg.registerFloatVar("fuzzfacefm.Drive",N_("Drive"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("fuzzfacefm.Fuzz",N_("Fuzz"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("fuzzfacefm.Input",N_("Input"),"S","",&fVslider2, 0.5, 0.0, 1.0, 0.01, 0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!-- Generated with glade 3.22.1 -->\n\
<interface>\n\
  <requires lib=\"gtk+\" version=\"3.20\"/>\n\
  <requires lib=\"gxwidgets\" version=\"0.0\"/>\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can_focus\">False</property>\n\
    <child>\n\
      <placeholder/>\n\
    </child>\n\
    <child>\n\
      <object class=\"GtkBox\" id=\"vbox1\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can_focus\">False</property>\n\
        <property name=\"orientation\">vertical</property>\n\
        <child>\n\
          <object class=\"GtkBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GtkBox\" id=\"hbox1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"spacing\">10</property>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
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
                  <object class=\"GtkBox\" id=\"vbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
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
                  <object class=\"GtkBox\" id=\"vbox4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
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
                  <object class=\"GtkBox\" id=\"vbox5\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
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
          <object class=\"GtkBox\" id=\"minibox\">\n\
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
                <property name=\"label\" translatable=\"yes\">Level</property>\n\
                <property name=\"xalign\">0</property>\n\
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
