// generated from file '../src/plugins/buffb.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace buffb {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	double fRec0[2];
	double fConst0;
	double fConst2;
	double fConst4;
	double fConst6;
	double fConst8;
	double fConst10;
	double fConst11;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst19;
	double fConst21;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fRec1[5];
	double fConst30;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	FAUSTFLOAT fVslider1;
	double fRec2[2];

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
	id = "buffb";
	name = N_("Buffer Booster");
	groups = 0;
	description = N_("Buffer Booster"); // description (tooltip)
	category = N_("Tone Control");       // category
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 5; l1 = l1 + 1) fRec1[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec2[l2] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 2.88228949502788e-20 * fConst0;
	fConst2 = fConst0 * (fConst0 * (-3.1353376203179e-14 - fConst1) + -9.57866164137552e-13) + -4.00199516463868e-12;
	double fConst3 = 3.01067992749548e-20 * fConst0;
	fConst4 = fConst0 * (fConst0 * (fConst3 + 3.28941142776728e-14) + 4.37053187936949e-12) + 2.10094331121784e-11;
	double fConst5 = 6.84245438067155e-19 * fConst0;
	fConst6 = fConst0 * (fConst5 + 7.47593506310745e-13) + 9.93302699856702e-11;
	double fConst7 = 2.84995035519639e-20 * fConst0;
	fConst8 = 6.45077038297955e-16 - fConst7;
	double fConst9 = 2.97690025361778e-20 * fConst0;
	fConst10 = fConst9 + 3.02300377935444e-13;
	fConst11 = mydsp_faustpower3_f(fConst0);
	double fConst12 = 6.76568239458587e-19 * fConst0;
	fConst13 = mydsp_faustpower2_f(fConst0);
	fConst14 = fConst13 * (-6.87046313489645e-12 - fConst12);
	fConst15 = fConst0 * (fConst0 * (3.1353376203179e-14 - fConst1) + -9.57866164137552e-13) + 4.00199516463868e-12;
	fConst16 = fConst0 * (fConst0 * (fConst3 + -3.28941142776728e-14) + 4.37053187936949e-12) + -2.10094331121784e-11;
	fConst17 = fConst0 * (7.47593506310745e-13 - fConst5) + -9.93302699856702e-11;
	double fConst18 = 1.15291579801115e-19 * fConst0;
	fConst19 = fConst13 * (fConst18 + -6.27067524063581e-14) + 8.00399032927735e-12;
	double fConst20 = 1.20427197099819e-19 * fConst0;
	fConst21 = fConst13 * (6.57882285553455e-14 - fConst20) + -4.20188662243568e-11;
	double fConst22 = 1.36849087613431e-18 * fConst13;
	fConst23 = fConst22 + -1.9866053997134e-10;
	fConst24 = 1.9157323282751e-12 - 1.72937369701673e-19 * fConst13;
	fConst25 = 1.80640795649729e-19 * fConst13 + -8.74106375873897e-12;
	fConst26 = fConst13 * (fConst18 + 6.27067524063581e-14) + -8.00399032927735e-12;
	fConst27 = fConst13 * (-6.57882285553455e-14 - fConst20) + 4.20188662243568e-11;
	fConst28 = 1.9866053997134e-10 - fConst22;
	double fConst29 = 1.13998014207856e-19 * fConst0;
	fConst30 = fConst29 + -1.29015407659591e-15;
	double fConst31 = 1.19076010144711e-19 * fConst0;
	fConst32 = -6.04600755870888e-13 - fConst31;
	fConst33 = mydsp_faustpower4_f(fConst0);
	fConst34 = 1.37409262697929e-11 * fConst13;
	fConst35 = fConst29 + 1.29015407659591e-15;
	fConst36 = 6.04600755870888e-13 - fConst31;
	fConst37 = -6.45077038297955e-16 - fConst7;
	fConst38 = fConst9 + -3.02300377935444e-13;
	fConst39 = fConst13 * (fConst12 + -6.87046313489645e-12);
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = 0.007000000000000006 * double(fVslider0);
	double fSlow1 = 0.007000000000000006 * double(fVslider1);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		double fTemp0 = fConst0 * (fConst6 + fRec0[0] * (fConst4 + fConst2 * fRec0[0])) + 4.77487116185873e-10;
		fRec1[0] = double(input0[i0]) - (fRec1[1] * (fConst0 * (fConst28 + fRec0[0] * (fConst27 + fConst26 * fRec0[0])) + 1.90994846474349e-09) + fRec1[2] * (fConst13 * (fRec0[0] * (fConst25 + fConst24 * fRec0[0]) + -1.49518701262149e-12) + 2.86492269711524e-09) + fRec1[3] * (fConst0 * (fConst23 + fRec0[0] * (fConst21 + fConst19 * fRec0[0])) + 1.90994846474349e-09) + fRec1[4] * (fConst0 * (fConst17 + fRec0[0] * (fConst16 + fConst15 * fRec0[0])) + 4.77487116185873e-10)) / fTemp0;
		fRec2[0] = fSlow1 + 0.993 * fRec2[1];
		output0[i0] = FAUSTFLOAT(fRec2[0] * (fRec1[0] * (fConst39 + fConst11 * fRec0[0] * (fConst38 + fConst37 * fRec0[0])) + fConst11 * fRec1[1] * (fRec0[0] * (fConst36 + fConst35 * fRec0[0]) + -1.35313647891717e-18) + fRec1[2] * (fConst34 + fConst33 * fRec0[0] * (0.0 - 1.70997021311783e-19 * fRec0[0] + 1.78614015217067e-19)) + fConst11 * fRec1[3] * (fRec0[0] * (fConst32 + fConst30 * fRec0[0]) + 1.35313647891717e-18) + fRec1[4] * (fConst14 + fConst11 * fRec0[0] * (fConst10 + fConst8 * fRec0[0]))) / fTemp0);
		fRec0[1] = fRec0[0];
		for (int j0 = 4; j0 > 0; j0 = j0 - 1) {
			fRec1[j0] = fRec1[j0 - 1];
		}
		fRec2[1] = fRec2[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("buffb.Intensity",N_("Intensity"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("buffb.Volume",N_("Volume"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
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
                <property name=\"label\" translatable=\"yes\">Volume</property>\n\
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
#define PARAM(p) ("buffb" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Volume"), "Volume");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Volume"), "Volume");

    b.create_small_rackknobr(PARAM("Intensity"), "Intensity");
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

} // end namespace buffb
} // end namespace pluginlib
