// generated from file '../src/plugins/buffb.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace buffb {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider0;
	double fRec0[2];
	double fConst2;
	double fConst3;
	FAUSTFLOAT fVslider1;
	double fRec2[2];
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fRec1[5];
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;

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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec2[l1] = 0.0;
	for (int l2 = 0; (l2 < 5); l2 = (l2 + 1)) fRec1[l2] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	fConst2 = (1.3684908761343101e-18 * fConst1);
	fConst3 = (1.9866053997133999e-10 - fConst2);
	fConst4 = (1.2042719709981901e-19 * fConst0);
	fConst5 = (((-6.57882285553455e-14 - fConst4) * fConst1) + 4.2018866224356797e-11);
	fConst6 = (1.1529157980111499e-19 * fConst0);
	fConst7 = (((fConst6 + 6.2706752406358102e-14) * fConst1) + -8.0039903292773496e-12);
	fConst8 = ((1.80640795649729e-19 * fConst1) + -8.7410637587389698e-12);
	fConst9 = (1.9157323282751001e-12 - (1.7293736970167299e-19 * fConst1));
	fConst10 = (fConst2 + -1.9866053997133999e-10);
	fConst11 = (((6.57882285553455e-14 - fConst4) * fConst1) + -4.2018866224356797e-11);
	fConst12 = (((fConst6 + -6.2706752406358102e-14) * fConst1) + 8.0039903292773496e-12);
	fConst13 = (6.8424543806715503e-19 * fConst0);
	fConst14 = (((7.4759350631074502e-13 - fConst13) * fConst0) + -9.9330269985670203e-11);
	fConst15 = (3.0106799274954801e-20 * fConst0);
	fConst16 = (((((fConst15 + -3.28941142776728e-14) * fConst0) + 4.3705318793694897e-12) * fConst0) + -2.1009433112178399e-11);
	fConst17 = (2.8822894950278802e-20 * fConst0);
	fConst18 = (((((3.1353376203179e-14 - fConst17) * fConst0) + -9.5786616413755209e-13) * fConst0) + 4.0019951646386797e-12);
	fConst19 = (((fConst13 + 7.4759350631074502e-13) * fConst0) + 9.9330269985670203e-11);
	fConst20 = (((((fConst15 + 3.28941142776728e-14) * fConst0) + 4.3705318793694897e-12) * fConst0) + 2.1009433112178399e-11);
	fConst21 = (((((-3.1353376203179e-14 - fConst17) * fConst0) + -9.5786616413755209e-13) * fConst0) + -4.0019951646386797e-12);
	fConst22 = (6.7656823945858704e-19 * fConst0);
	fConst23 = (fConst22 + -6.8704631348964498e-12);
	fConst24 = (2.9769002536177801e-20 * fConst0);
	fConst25 = (fConst24 + -3.0230037793544402e-13);
	fConst26 = (2.8499503551963899e-20 * fConst0);
	fConst27 = (-6.4507703829795496e-16 - fConst26);
	fConst28 = (1.1907601014471101e-19 * fConst0);
	fConst29 = (6.0460075587088804e-13 - fConst28);
	fConst30 = (1.13998014207856e-19 * fConst0);
	fConst31 = (fConst30 + 1.2901540765959099e-15);
	fConst32 = (-6.0460075587088804e-13 - fConst28);
	fConst33 = (fConst30 + -1.2901540765959099e-15);
	fConst34 = (-6.8704631348964498e-12 - fConst22);
	fConst35 = (fConst24 + 3.0230037793544402e-13);
	fConst36 = (6.4507703829795496e-16 - fConst26);
	fVslider0 = FAUSTFLOAT(0.5);
	fVslider1 = FAUSTFLOAT(0.5);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = (0.0070000000000000062 * double(fVslider0));
	double fSlow1 = (0.0070000000000000062 * double(fVslider1));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec0[0] = (fSlow0 + (0.99299999999999999 * fRec0[1]));
		fRec2[0] = (fSlow1 + (0.99299999999999999 * fRec2[1]));
		double fTemp0 = ((fConst0 * (fConst19 + (fRec2[0] * (fConst20 + (fConst21 * fRec2[0]))))) + 4.7748711618587295e-10);
		fRec1[0] = (double(input0[i]) - (((((fRec1[1] * ((fConst0 * (fConst3 + (fRec2[0] * (fConst5 + (fConst7 * fRec2[0]))))) + 1.9099484647434901e-09)) + (fRec1[2] * ((fConst1 * ((fRec2[0] * (fConst8 + (fConst9 * fRec2[0]))) + -1.49518701262149e-12)) + 2.86492269711524e-09))) + (fRec1[3] * ((fConst0 * (fConst10 + (fRec2[0] * (fConst11 + (fConst12 * fRec2[0]))))) + 1.9099484647434901e-09))) + (fRec1[4] * ((fConst0 * (fConst14 + (fRec2[0] * (fConst16 + (fConst18 * fRec2[0]))))) + 4.7748711618587295e-10))) / fTemp0));
		output0[i] = FAUSTFLOAT((fConst1 * ((fRec0[0] * (((((fRec1[0] * (fConst23 + (fConst0 * (fRec2[0] * (fConst25 + (fConst27 * fRec2[0])))))) + (fConst0 * (fRec1[1] * ((fRec2[0] * (fConst29 + (fConst31 * fRec2[0]))) + -1.35313647891717e-18)))) + (fRec1[2] * ((fConst1 * (fRec2[0] * ((0.0 - (1.7099702131178301e-19 * fRec2[0])) + 1.78614015217067e-19))) + 1.37409262697929e-11))) + (fConst0 * (fRec1[3] * ((fRec2[0] * (fConst32 + (fConst33 * fRec2[0]))) + 1.35313647891717e-18)))) + (fRec1[4] * (fConst34 + (fConst0 * (fRec2[0] * (fConst35 + (fConst36 * fRec2[0])))))))) / fTemp0)));
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		for (int j0 = 4; (j0 > 0); j0 = (j0 - 1)) {
			fRec1[j0] = fRec1[(j0 - 1)];
		}
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("buffb.Intensity",N_("Intensity"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("buffb.Volume",N_("Volume"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01);
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
