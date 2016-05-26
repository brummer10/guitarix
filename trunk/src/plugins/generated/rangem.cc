// generated from file '../src/plugins/rangem.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace rangem {

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
	FAUSTFLOAT 	fslider1;
	double 	fRec1[4];
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
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
	id = "rangem";
	name = N_("Rangemaster");
	groups = 0;
	description = N_("High Frequency Booster"); // description (tooltip)
	category = N_("Tone Control");       // category
	shortname = N_("Rangemaster");     // shortname
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
	for (int i=0; i<4; i++) fRec1[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(192000, max(1, fSamplingFreq)));
	fConst1 = (4.37071753217797e-15 * fConst0);
	fConst2 = (4.663130715952e-08 + (fConst0 * (1.20972656728663e-08 + (fConst0 * (2.23510911173716e-10 + fConst1)))));
	fConst3 = (6.03049472237275e-17 * fConst0);
	fConst4 = (3.36357739377656e-23 + (fConst0 * (1.95791953523286e-11 + (fConst0 * (1.26333088694976e-11 - fConst3)))));
	fConst5 = (9.6103977657166e-17 * fConst0);
	fConst6 = ((fConst0 * ((fConst0 * (0 - (1.29828683375003e-11 + fConst5))) - 3.77055394062117e-11)) - 6.47756445986258e-23);
	fConst7 = (8.31466608544754e-13 * fConst0);
	fConst8 = (2.24531902904193e-12 - fConst7);
	fConst9 = (8.32852386225662e-13 * fConst0);
	fConst10 = (fConst9 - 2.24906122742367e-12);
	fConst11 = (4.663130715952e-08 + (fConst0 * ((fConst0 * (2.23510911173716e-10 - fConst1)) - 1.20972656728663e-08)));
	fConst12 = (3.36357739377656e-23 + (fConst0 * ((fConst0 * (1.26333088694976e-11 + fConst3)) - 1.95791953523286e-11)));
	fConst13 = ((fConst0 * (3.77055394062117e-11 + (fConst0 * (fConst5 - 1.29828683375003e-11)))) - 6.47756445986258e-23);
	fConst14 = (1.31121525965339e-14 * fConst0);
	fConst15 = (1.3989392147856e-07 + (fConst0 * ((fConst0 * (fConst14 - 2.23510911173716e-10)) - 1.20972656728663e-08)));
	fConst16 = (1.80914841671183e-16 * fConst0);
	fConst17 = (1.00907321813297e-22 + (fConst0 * ((fConst0 * (0 - (1.26333088694976e-11 + fConst16))) - 1.95791953523286e-11)));
	fConst18 = (2.88311932971498e-16 * fConst0);
	fConst19 = ((fConst0 * (3.77055394062117e-11 + (fConst0 * (1.29828683375003e-11 - fConst18)))) - 1.94326933795877e-22);
	fConst20 = (1.3989392147856e-07 + (fConst0 * (1.20972656728663e-08 + (fConst0 * (0 - (2.23510911173716e-10 + fConst14))))));
	fConst21 = (1.00907321813297e-22 + (fConst0 * (1.95791953523286e-11 + (fConst0 * (fConst16 - 1.26333088694976e-11)))));
	fConst22 = ((fConst0 * ((fConst0 * (1.29828683375003e-11 + fConst18)) - 3.77055394062117e-11)) - 1.94326933795877e-22);
	fConst23 = (2.49439982563426e-12 * fConst0);
	fConst24 = (fConst23 - 2.24531902904193e-12);
	fConst25 = (2.49855715867699e-12 * fConst0);
	fConst26 = (2.24906122742367e-12 - fConst25);
	fConst27 = (0 - (2.24531902904193e-12 + fConst23));
	fConst28 = (2.24906122742367e-12 + fConst25);
	fConst29 = (2.24531902904193e-12 + fConst7);
	fConst30 = (0 - (2.24906122742367e-12 + fConst9));
	fConst31 = faustpower<2>(fConst0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.007000000000000006 * (1 - double(fslider0)));
	double 	fSlow1 = (0.01 * double(fslider1));
	double 	fSlow2 = (1 - fSlow1);
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		double fTemp0 = ((fRec0[0] * ((fConst6 * fRec0[0]) + fConst4)) + fConst2);
		double fTemp1 = (double)input0[i];
		fRec1[0] = ((fSlow1 * fTemp1) - ((((fRec1[1] * ((fRec0[0] * ((fConst22 * fRec0[0]) + fConst21)) + fConst20)) + (fRec1[2] * ((fRec0[0] * ((fConst19 * fRec0[0]) + fConst17)) + fConst15))) + (fRec1[3] * ((fRec0[0] * ((fConst13 * fRec0[0]) + fConst12)) + fConst11))) / fTemp0));
		output0[i] = (FAUSTFLOAT)((fSlow2 * fTemp1) + (fConst31 * (((((fRec1[0] * (fConst30 + (fConst29 * fRec0[0]))) + (fRec1[1] * (fConst28 + (fConst27 * fRec0[0])))) + (fRec1[2] * (fConst26 + (fConst24 * fRec0[0])))) + (fRec1[3] * (fConst10 + (fConst8 * fRec0[0])))) / fTemp0)));
		// post processing
		for (int i=3; i>0; i--) fRec1[i] = fRec1[i-1];
		fRec0[1] = fRec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("rangem.Boost",N_("Boost"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("rangem.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider1, 1e+02, 0.0, 1e+02, 1.0);
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
                      <object class=\"GxMidKnob\" id=\"gxbigknob1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">rangem.Boost</property>\n\
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
                        <property name=\"var_id\">rangem.wet_dry</property>\n\
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
                <property name=\"var_id\">rangem.Boost</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Boost</property>\n\
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
#define PARAM(p) ("rangem" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Boost"), "Boost");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Boost"), "Boost");
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

} // end namespace rangem
} // end namespace pluginlib
