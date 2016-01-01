// generated from file '../src/plugins/buffb.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace buffb {

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
	double 	fRec1[5];
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	FAUSTFLOAT 	fslider1;
	double 	fRec2[2];
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
	id = "buffb";
	name = N_("Buffer Booster");
	groups = 0;
	description = N_("Buffer Booster"); // description (tooltip)
	category = N_("Tone control");       // category
	shortname = N_("Buffer Boost");     // shortname
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
	for (int i=0; i<5; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(192000, max(1, fSamplingFreq)));
	fConst1 = (6.84245438067155e-19 * fConst0);
	fConst2 = (9.93302699856702e-11 + (fConst0 * (7.47593506310745e-13 + fConst1)));
	fConst3 = (2.88228949502788e-20 * fConst0);
	fConst4 = ((fConst0 * ((fConst0 * (0 - (3.1353376203179e-14 + fConst3))) - 9.57866164137552e-13)) - 4.00199516463868e-12);
	fConst5 = (3.01067992749548e-20 * fConst0);
	fConst6 = (2.10094331121784e-11 + (fConst0 * (4.37053187936949e-12 + (fConst0 * (3.28941142776728e-14 + fConst5)))));
	fConst7 = (2.84995035519639e-20 * fConst0);
	fConst8 = (6.45077038297955e-16 - fConst7);
	fConst9 = (2.97690025361778e-20 * fConst0);
	fConst10 = (3.02300377935444e-13 + fConst9);
	fConst11 = (6.76568239458587e-19 * fConst0);
	fConst12 = (0 - (6.87046313489645e-12 + fConst11));
	fConst13 = ((fConst0 * (7.47593506310745e-13 - fConst1)) - 9.93302699856702e-11);
	fConst14 = (4.00199516463868e-12 + (fConst0 * ((fConst0 * (3.1353376203179e-14 - fConst3)) - 9.57866164137552e-13)));
	fConst15 = ((fConst0 * (4.37053187936949e-12 + (fConst0 * (fConst5 - 3.28941142776728e-14)))) - 2.10094331121784e-11);
	fConst16 = (1.15291579801115e-19 * fConst0);
	fConst17 = faustpower<2>(fConst0);
	fConst18 = (8.00399032927735e-12 + (fConst17 * (fConst16 - 6.27067524063581e-14)));
	fConst19 = (1.20427197099819e-19 * fConst0);
	fConst20 = ((fConst17 * (6.57882285553455e-14 - fConst19)) - 4.20188662243568e-11);
	fConst21 = (1.36849087613431e-18 * fConst17);
	fConst22 = (fConst21 - 1.9866053997134e-10);
	fConst23 = (1.9157323282751e-12 - (1.72937369701673e-19 * fConst17));
	fConst24 = ((1.80640795649729e-19 * fConst17) - 8.74106375873897e-12);
	fConst25 = (1.9866053997134e-10 - fConst21);
	fConst26 = ((fConst17 * (6.27067524063581e-14 + fConst16)) - 8.00399032927735e-12);
	fConst27 = (4.20188662243568e-11 + (fConst17 * (0 - (6.57882285553455e-14 + fConst19))));
	fConst28 = (1.13998014207856e-19 * fConst0);
	fConst29 = (fConst28 - 1.29015407659591e-15);
	fConst30 = (1.19076010144711e-19 * fConst0);
	fConst31 = (0 - (6.04600755870888e-13 + fConst30));
	fConst32 = (1.29015407659591e-15 + fConst28);
	fConst33 = (6.04600755870888e-13 - fConst30);
	fConst34 = (0 - (6.45077038297955e-16 + fConst7));
	fConst35 = (fConst9 - 3.02300377935444e-13);
	fConst36 = (fConst11 - 6.87046313489645e-12);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		double fTemp0 = (4.77487116185873e-10 + (fConst0 * ((fRec0[0] * (fConst6 + (fConst4 * fRec0[0]))) + fConst2)));
		fRec1[0] = ((double)input0[i] - (((((fRec1[1] * (1.90994846474349e-09 + (fConst0 * ((fRec0[0] * (fConst27 + (fConst26 * fRec0[0]))) + fConst25)))) + (fRec1[2] * (2.86492269711524e-09 + (fConst17 * ((fRec0[0] * (fConst24 + (fConst23 * fRec0[0]))) - 1.49518701262149e-12))))) + (fRec1[3] * (1.90994846474349e-09 + (fConst0 * (fConst22 + (fRec0[0] * (fConst20 + (fConst18 * fRec0[0])))))))) + (fRec1[4] * (4.77487116185873e-10 + (fConst0 * ((fRec0[0] * (fConst15 + (fConst14 * fRec0[0]))) + fConst13))))) / fTemp0));
		fRec2[0] = ((0.993 * fRec2[1]) + fSlow1);
		output0[i] = (FAUSTFLOAT)(fConst17 * ((fRec2[0] * (((((fRec1[0] * (fConst36 + (fConst0 * (fRec0[0] * (fConst35 + (fConst34 * fRec0[0])))))) + (fConst0 * (fRec1[1] * ((fRec0[0] * (fConst33 + (fConst32 * fRec0[0]))) - 1.35313647891717e-18)))) + (fRec1[2] * (1.37409262697929e-11 + (fConst17 * (fRec0[0] * (1.78614015217067e-19 + (0 - (1.70997021311783e-19 * fRec0[0])))))))) + (fConst0 * (fRec1[3] * (1.35313647891717e-18 + (fRec0[0] * (fConst31 + (fConst29 * fRec0[0]))))))) + (fRec1[4] * (fConst12 + (fConst0 * (fRec0[0] * (fConst10 + (fConst8 * fRec0[0])))))))) / fTemp0));
		// post processing
		fRec2[1] = fRec2[0];
		for (int i=4; i>0; i--) fRec1[i] = fRec1[i-1];
		fRec0[1] = fRec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("buffb.Intensity",N_("Intensity"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("buffb.Volume",N_("Volume"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
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
                        <property name=\"var_id\">buffb.Intensity</property>\n\
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
                      <object class=\"GxMidKnob\" id=\"gxbigknob2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">buffb.Volume</property>\n\
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
                <property name=\"var_id\">buffb.Volume</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Volume</property>\n\
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

} // end namespace buffb
} // end namespace pluginlib
