// generated from file '../src/plugins/buzz.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace buzz {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	FAUSTFLOAT fVslider0;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fRec8[4];
	FAUSTFLOAT fVslider1;
	double fRec9[2];
	double fVec0[2];
	double fRec7[2];
	double fRec6[3];
	double fConst13;
	double fConst14;
	double fConst15;
	double fRec10[2];
	double fRec5[3];
	double fConst16;
	double fConst17;
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fRec11[2];
	double fRec1[3];
	double fRec0[2];

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
	for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) fRec8[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec9[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fVec0[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec7[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec6[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec10[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec5[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec4[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec3[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec2[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec11[l10] = 0.0;
	for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) fRec1[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec0[l12] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = std::tan((34.557519189487721 / fConst0));
	fConst2 = (1.0 / fConst1);
	fConst3 = (fConst2 + 1.0);
	fConst4 = (1.0 / (fConst3 * fConst1));
	fConst5 = (9.0420168692285508e-15 * fConst0);
	fConst6 = (((((fConst5 + 1.0967885210812e-14) * fConst0) + 8.1405834755984808e-15) * fConst0) + 2.46256378077601e-15);
	fConst7 = (0.93028479253239138 * (mydsp_faustpower3_f(fConst0) / fConst6));
	fConst8 = (1.0 / fConst6);
	fConst9 = (2.71260506076857e-14 * fConst0);
	fConst10 = (((((-1.0967885210812e-14 - fConst9) * fConst0) + 8.1405834755984808e-15) * fConst0) + 7.3876913423280403e-15);
	fConst11 = (((((fConst9 + -1.0967885210812e-14) * fConst0) + -8.1405834755984808e-15) * fConst0) + 7.3876913423280403e-15);
	fConst12 = (((((1.0967885210812e-14 - fConst5) * fConst0) + -8.1405834755984808e-15) * fConst0) + 2.46256378077601e-15);
	fConst13 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst14 = (1.0 / (fConst13 + 1.0));
	fConst15 = (1.0 - fConst13);
	fConst16 = (0.0 - fConst4);
	fConst17 = ((1.0 - fConst2) / fConst3);
	fVslider0 = FAUSTFLOAT(100.0);
	fVslider1 = FAUSTFLOAT(0.5);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = (0.01 * double(fVslider0));
	double fSlow1 = (0.0070000000000000062 * double(fVslider1));
	double fSlow2 = (1.0 - fSlow0);
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = double(input0[i]);
		fRec8[0] = ((fSlow0 * fTemp0) - (fConst8 * (((fConst10 * fRec8[1]) + (fConst11 * fRec8[2])) + (fConst12 * fRec8[3]))));
		fRec9[0] = (fSlow1 + (0.99299999999999999 * fRec9[1]));
		double fTemp1 = ((((fRec8[1] * (0.0 - (1.1440429901255601e-12 * fRec9[0]))) + (3.8134766337518501e-13 * (fRec8[0] * fRec9[0]))) + (1.1440429901255601e-12 * (fRec9[0] * fRec8[2]))) + (fRec8[3] * (0.0 - (3.8134766337518501e-13 * fRec9[0]))));
		fVec0[0] = fTemp1;
		fRec7[0] = ((fConst7 * (fTemp1 + fVec0[1])) - (0.86056958506478287 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.86129424393186271 * fRec6[2])));
		fRec10[0] = (fConst14 * ((0.027 * (fRec5[1] + fRec5[2])) - (fConst15 * fRec10[1])));
		fRec5[0] = (double(Ftrany(int(TRANY_TABLE_7199P_68k), double((((0.92544984225177063 * (fRec6[0] + fRec6[2])) + (fRec10[0] + (1.8508996845035413 * fRec6[1]))) + -5.5719810000000001)))) + -43.630333333333311);
		fRec4[0] = ((0.025000000000000001 * ((fConst4 * fRec5[0]) + (fConst16 * fRec5[1]))) - (fConst17 * fRec4[1]));
		fRec3[0] = ((0.93028479253239138 * (fRec4[0] + fRec4[1])) - (0.86056958506478287 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.86129424393186271 * fRec2[2])));
		fRec11[0] = (fConst14 * ((0.027 * (fRec1[1] + fRec1[2])) - (fConst15 * fRec11[1])));
		fRec1[0] = (double(Ftrany(int(TRANY_TABLE_7199P_68k), double((((0.92544984225177063 * (fRec2[0] + fRec2[2])) + (fRec11[0] + (1.8508996845035413 * fRec2[1]))) + -5.5719810000000001)))) + -43.630333333333311);
		fRec0[0] = ((0.025000000000000001 * ((fConst4 * fRec1[0]) + (fConst16 * fRec1[1]))) - (fConst17 * fRec0[1]));
		output0[i] = FAUSTFLOAT((fRec0[0] + (fSlow2 * fTemp0)));
		for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
			fRec8[j0] = fRec8[(j0 - 1)];
		}
		fRec9[1] = fRec9[0];
		fVec0[1] = fVec0[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec10[1] = fRec10[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec11[1] = fRec11[0];
		fRec1[2] = fRec1[1];
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
	reg.registerVar("buzz.Level",N_("Level"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("buzz.wet_dry",N_("Wet/Dry"),"S",N_("percentage of processed signal in output signal"),&fVslider0, 100.0, 0.0, 100.0, 1.0);
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
                        <property name=\"var_id\">buzz.wet_dry</property>\n\
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
                      <object class=\"GxMidKnob\" id=\"gxbigknob2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">buzz.Level</property>\n\
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
                <property name=\"var_id\">buzz.Level</property>\n\
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
