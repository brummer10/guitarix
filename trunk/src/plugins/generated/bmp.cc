// generated from file '../src/plugins/bmp.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "clipping.h"

namespace pluginlib {
namespace bmp {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int samplingFreq;
	int fSamplingFreq;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
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
	double fRec4[3];
	FAUSTFLOAT fVslider0;
	double fRec5[2];
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fRec3[3];
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fRec2[3];
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fRec1[3];
	double fConst38;
	double fConst39;
	FAUSTFLOAT fVslider1;
	double fRec6[2];
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fRec0[3];
	FAUSTFLOAT fVslider2;
	double fRec7[2];

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
	id = "bmp";
	name = N_("BigMuffPi");
	groups = 0;
	description = N_("BigMuffPi"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("BMP");     // shortname
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
	for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) fRec4[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec5[l1] = 0.0;
	for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) fRec3[l2] = 0.0;
	for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) fRec2[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec1[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec6[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec0[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec7[l7] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int RsamplingFreq)
{
	samplingFreq = 96000;
	smp.setup(RsamplingFreq, samplingFreq);
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	fConst2 = (4.3388468105506801e-10 * fConst0);
	fConst3 = (((fConst2 + 6.8680901344593704e-09) * fConst0) + 2.6522670215943701e-08);
	fConst4 = (fConst1 / fConst3);
	fConst5 = (3.6868885846545499e-10 * fConst0);
	fConst6 = (1.0 / (((fConst5 + 3.0348555108869402e-06) * fConst0) + 0.00486780557301784));
	fConst7 = (3.9204879585950002e-10 * fConst0);
	fConst8 = (1.0 / (((fConst7 + 2.0047872746271098e-06) * fConst0) + 0.00048978515761155495));
	fConst9 = (7.6673121439986096e-12 * fConst0);
	fConst10 = ((fConst9 + -3.9949085717896201e-05) * fConst0);
	fConst11 = (2.0828770493449602e-05 * fConst0);
	fConst12 = (1.0 / (fConst11 + 0.00021901631427173599));
	fConst13 = (3.7454979802541999e-06 * fConst0);
	fConst14 = (0.0 - fConst13);
	fConst15 = (0.00021901631427173599 - fConst11);
	fConst16 = (1.2821120020392999e-10 * fConst0);
	fConst17 = (fConst16 + -6.2652181541007596e-07);
	fConst18 = (1.12312054615984e-09 * fConst0);
	fConst19 = (fConst18 + -2.8621970465474001e-06);
	fConst20 = (1.1344651981412601e-09 * fConst0);
	fConst21 = (2.8911081278256599e-06 - fConst20);
	fConst22 = (fConst16 + 6.2652181541007596e-07);
	fConst23 = (fConst18 + 2.8621970465474001e-06);
	fConst24 = (-2.8911081278256599e-06 - fConst20);
	fConst25 = (2.26293387153501e-14 * fConst0);
	fConst26 = (fConst25 + -1.17905906929765e-07);
	fConst27 = (2.26293387153501e-12 * fConst0);
	fConst28 = (fConst27 + -1.17905906929765e-05);
	fConst29 = (fConst25 + 1.17905906929765e-07);
	fConst30 = (fConst27 + 1.17905906929765e-05);
	fConst31 = (0.00097957031522311099 - (7.8409759171899901e-10 * fConst1));
	fConst32 = (((fConst7 + -2.0047872746271098e-06) * fConst0) + 0.00048978515761155495);
	fConst33 = (0.0 - (1.53346242879972e-11 * fConst1));
	fConst34 = ((fConst9 + 3.9949085717896201e-05) * fConst0);
	fConst35 = (7.3737771693091102e-10 * fConst1);
	fConst36 = (0.0097356111460356904 - fConst35);
	fConst37 = (((fConst5 + -3.0348555108869402e-06) * fConst0) + 0.00486780557301784);
	fConst38 = (8.6710157453912601e-07 * fConst0);
	fConst39 = ((3.6868885846545499e-10 * fConst1) + -0.0031609127097518498);
	fConst40 = (-0.0063218254195036901 - fConst35);
	fConst41 = (1.0 / fConst3);
	fConst42 = (5.3045340431887401e-08 - (8.6776936211013499e-10 * fConst1));
	fConst43 = (((fConst2 + -6.8680901344593704e-09) * fConst0) + 2.6522670215943701e-08);
	fVslider0 = FAUSTFLOAT(0.5);
	fVslider1 = FAUSTFLOAT(0.5);
	fVslider2 = FAUSTFLOAT(0.5);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double fSlow0 = (0.0070000000000000062 * double(fVslider0));
	double fSlow1 = (0.0070000000000000062 * double(fVslider1));
	double fSlow2 = (0.0070000000000000062 * double(fVslider2));
	for (int i = 0; (i < ReCount); i = (i + 1)) {
		fRec4[0] = (double(buf[i]) - (fConst12 * ((fConst15 * fRec4[2]) + (0.000438032628543473 * fRec4[1]))));
		fRec5[0] = (fSlow0 + (0.99299999999999999 * fRec5[1]));
		double fTemp0 = ((fConst0 * (fConst22 + (fRec5[0] * (fConst23 + (fConst24 * fRec5[0]))))) + 0.000146000960455196);
		fRec3[0] = ((fConst12 * ((fConst14 * fRec4[2]) + (fConst13 * fRec4[0]))) - (((fRec3[1] * ((fConst1 * ((fRec5[0] * ((2.2689303962825102e-09 * fRec5[0]) + -2.2462410923196899e-09)) + -2.5642240040785998e-10)) + 0.00029200192091039201)) + (fRec3[2] * ((fConst0 * (fConst17 + (fRec5[0] * (fConst19 + (fConst21 * fRec5[0]))))) + 0.000146000960455196))) / fTemp0));
		fRec2[0] = ((0.31830988618379069 * std::atan((fConst0 * ((((fRec3[0] * (fConst26 + (fConst28 * fRec5[0]))) + (fConst0 * (fRec3[1] * ((0.0 - (4.5258677430700104e-12 * fRec5[0])) + -4.5258677430700099e-14)))) + (fRec3[2] * (fConst29 + (fConst30 * fRec5[0])))) / fTemp0)))) - (fConst8 * ((fConst31 * fRec2[1]) + (fConst32 * fRec2[2]))));
		fRec1[0] = (double(symclip(double((fConst8 * (((fConst10 * fRec2[0]) + (fConst33 * fRec2[1])) + (fConst34 * fRec2[2])))))) - (fConst6 * ((fConst36 * fRec1[1]) + (fConst37 * fRec1[2]))));
		fRec6[0] = (fSlow1 + (0.99299999999999999 * fRec6[1]));
		double fTemp1 = ((fConst39 * fRec6[0]) + 0.0040143591413848399);
		fRec0[0] = ((fConst6 * (((fRec1[0] * (fConst38 + fTemp1)) + (fRec1[1] * ((fConst40 * fRec6[0]) + 0.0080287182827696903))) + (fRec1[2] * (fTemp1 - fConst38)))) - (fConst41 * ((fConst42 * fRec0[1]) + (fConst43 * fRec0[2]))));
		fRec7[0] = (fSlow2 + (0.99299999999999999 * fRec7[1]));
		double fTemp2 = (0.0 - (1.74325899023428e-09 * fRec7[0]));
		buf[i] = FAUSTFLOAT((fConst4 * (((fRec0[0] * fTemp2) + (3.4865179804685599e-09 * (fRec7[0] * fRec0[1]))) + (fRec0[2] * fTemp2))));
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec6[1] = fRec6[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		fRec7[1] = fRec7[0];
	}
	smp.down(buf, output0);
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("bmp.Sustain",N_("Sustain"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("bmp.Tone",N_("Tone"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("bmp.Volume",N_("Volume"),"S","",&fVslider2, 0.5, 0.0, 1.0, 0.01);
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
                        <property name=\"var_id\">bmp.Volume</property>\n\
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
                        <property name=\"var_id\">bmp.Tone</property>\n\
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
                        <property name=\"var_id\">bmp.Sustain</property>\n\
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
                <property name=\"var_id\">bmp.Sustain</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Drive</property>\n\
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
#define PARAM(p) ("bmp" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Sustain"), "Sustain");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Sustain"), "Sustain");
    b.create_small_rackknobr(PARAM("Tone"), "Tone");
    b.create_small_rackknobr(PARAM("Volume"), "Volume");
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

} // end namespace bmp
} // end namespace pluginlib
