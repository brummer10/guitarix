// generated from file '../src/plugins/bmp.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "clipping.h"

namespace pluginlib {
namespace bmp {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int sample_rate;
	int fSampleRate;
	double fConst0;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst6;
	double fConst7;
	FAUSTFLOAT fVslider0;
	double fRec1[2];
	double fConst8;
	double fConst10;
	double fConst12;
	double fConst13;
	double fConst15;
	double fConst16;
	double fConst17;
	FAUSTFLOAT fVslider1;
	double fRec4[2];
	double fConst19;
	double fConst21;
	double fConst23;
	double fConst25;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst32;
	double fConst34;
	double fRec6[3];
	double fConst35;
	double fRec5[3];
	double fConst36;
	double fConst37;
	double fRec3[3];
	double fConst39;
	double fConst40;
	double fConst41;
	double fRec2[3];
	double fConst42;
	double fRec0[3];
	FAUSTFLOAT fVslider2;
	double fRec7[2];
	double fConst43;

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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec1[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec4[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRec6[l2] = 0.0;
	for (int l3 = 0; l3 < 3; l3 = l3 + 1) fRec5[l3] = 0.0;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRec3[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec2[l5] = 0.0;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec0[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec7[l7] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int RsamplingFreq)
{
	sample_rate = 96000;
	smp.setup(RsamplingFreq, sample_rate);
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 4.33884681055068e-10 * fConst0;
	fConst2 = fConst0 * (fConst1 + -6.86809013445937e-09) + 2.65226702159437e-08;
	fConst3 = mydsp_faustpower2_f(fConst0);
	fConst4 = 5.30453404318874e-08 - 8.67769362110135e-10 * fConst3;
	double fConst5 = fConst0 * (fConst1 + 6.86809013445937e-09) + 2.65226702159437e-08;
	fConst6 = 1.0 / fConst5;
	fConst7 = 8.67101574539126e-07 * fConst0;
	fConst8 = 3.68688858465455e-10 * fConst3 + -0.00316091270975185;
	double fConst9 = 3.68688858465455e-10 * fConst0;
	fConst10 = fConst0 * (fConst9 + -3.03485551088694e-06) + 0.00486780557301784;
	double fConst11 = 7.37377716930911e-10 * fConst3;
	fConst12 = 0.00973561114603569 - fConst11;
	fConst13 = 1.0 / (fConst0 * (fConst9 + 3.03485551088694e-06) + 0.00486780557301784);
	double fConst14 = 3.920487958595e-10 * fConst0;
	fConst15 = fConst0 * (fConst14 + -2.00478727462711e-06) + 0.000489785157611555;
	fConst16 = 0.000979570315223111 - 7.84097591718999e-10 * fConst3;
	fConst17 = 1.0 / (fConst0 * (fConst14 + 2.00478727462711e-06) + 0.000489785157611555);
	double fConst18 = 1.13446519814126e-09 * fConst0;
	fConst19 = -2.89110812782566e-06 - fConst18;
	double fConst20 = 1.12312054615984e-09 * fConst0;
	fConst21 = fConst20 + 2.8621970465474e-06;
	double fConst22 = 1.2821120020393e-10 * fConst0;
	fConst23 = fConst22 + 6.26521815410076e-07;
	double fConst24 = 2.26293387153501e-12 * fConst0;
	fConst25 = fConst24 + 1.17905906929765e-05;
	double fConst26 = 2.26293387153501e-14 * fConst0;
	fConst27 = fConst26 + 1.17905906929765e-07;
	fConst28 = 2.89110812782566e-06 - fConst18;
	fConst29 = fConst20 + -2.8621970465474e-06;
	fConst30 = fConst22 + -6.26521815410076e-07;
	double fConst31 = 2.08287704934496e-05 * fConst0;
	fConst32 = 0.000219016314271736 - fConst31;
	double fConst33 = fConst31 + 0.000219016314271736;
	fConst34 = 1.0 / fConst33;
	fConst35 = 3.7454979802542e-06 * (fConst0 / fConst33);
	fConst36 = fConst24 + -1.17905906929765e-05;
	fConst37 = fConst26 + -1.17905906929765e-07;
	double fConst38 = 7.66731214399861e-12 * fConst0;
	fConst39 = fConst0 * (fConst38 + 3.99490857178962e-05);
	fConst40 = 1.53346242879972e-11 * fConst3;
	fConst41 = fConst0 * (fConst38 + -3.99490857178962e-05);
	fConst42 = -0.00632182541950369 - fConst11;
	fConst43 = fConst3 / fConst5;
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double fSlow0 = 0.007000000000000006 * double(fVslider0);
	double fSlow1 = 0.007000000000000006 * double(fVslider1);
	double fSlow2 = 0.007000000000000006 * double(fVslider2);
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		fRec1[0] = fSlow0 + 0.993 * fRec1[1];
		double fTemp0 = fConst8 * fRec1[0] + 0.00401435914138484;
		fRec4[0] = fSlow1 + 0.993 * fRec4[1];
		double fTemp1 = fConst0 * (fConst23 + fRec4[0] * (fConst21 + fConst19 * fRec4[0])) + 0.000146000960455196;
		fRec6[0] = double(buf[i0]) - fConst34 * (fConst32 * fRec6[2] + 0.000438032628543473 * fRec6[1]);
		fRec5[0] = fConst35 * (fRec6[0] - fRec6[2]) - (fRec5[1] * (fConst3 * (fRec4[0] * (2.26893039628251e-09 * fRec4[0] + -2.24624109231969e-09) + -2.5642240040786e-10) + 0.000292001920910392) + fRec5[2] * (fConst0 * (fConst30 + fRec4[0] * (fConst29 + fConst28 * fRec4[0])) + 0.000146000960455196)) / fTemp1;
		fRec3[0] = 0.3183098861837907 * std::atan((fConst0 * fRec5[0] * (fConst37 + fConst36 * fRec4[0]) + fConst3 * fRec5[1] * (-4.52586774307001e-14 - 4.52586774307001e-12 * fRec4[0]) + fConst0 * fRec5[2] * (fConst27 + fConst25 * fRec4[0])) / fTemp1) - fConst17 * (fConst16 * fRec3[1] + fConst15 * fRec3[2]);
		fRec2[0] = symclip(fConst17 * (fConst41 * fRec3[0] - fConst40 * fRec3[1] + fConst39 * fRec3[2])) - fConst13 * (fConst12 * fRec2[1] + fConst10 * fRec2[2]);
		fRec0[0] = fConst13 * (fRec2[0] * (fConst7 + fTemp0) + fRec2[1] * (fConst42 * fRec1[0] + 0.00802871828276969) + fRec2[2] * (fTemp0 - fConst7)) - fConst6 * (fConst4 * fRec0[1] + fConst2 * fRec0[2]);
		fRec7[0] = fSlow2 + 0.993 * fRec7[1];
		buf[i0] = FAUSTFLOAT(fConst43 * fRec7[0] * (3.48651798046856e-09 * fRec0[1] - 1.74325899023428e-09 * (fRec0[0] + fRec0[2])));
		fRec1[1] = fRec1[0];
		fRec4[1] = fRec4[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
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
	reg.registerFloatVar("bmp.Sustain",N_("Sustain"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("bmp.Tone",N_("Tone"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("bmp.Volume",N_("Volume"),"S","",&fVslider2, 0.5, 0.0, 1.0, 0.01, 0);
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
