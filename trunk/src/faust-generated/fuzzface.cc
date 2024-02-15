// generated from file '../src/faust/fuzzface.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


#include "clipping.h"

namespace fuzzface {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	double fRec0[2];
	double fConst0;
	double fConst2;
	double fConst3;
	double fConst5;
	double fConst6;
	FAUSTFLOAT fVslider1;
	double fRec1[2];
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
	double fConst19;
	double fConst20;
	double fConst22;
	double fConst24;
	double fConst25;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fRec2[6];
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
	double fConst47;
	double fConst48;
	double fConst49;


	gx_resample::FixedRateResampler smpCl;

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
	id = "fuzzface";
	name = N_("Fuzz Face");
	groups = 0;
	description = N_("J Hendrix Fuzz Face simulation"); // description (tooltip)
	category = N_("Fuzz");       // category
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec1[l1] = 0.0;
	for (int l2 = 0; l2 < 6; l2 = l2 + 1) fRec2[l2] = 0.0;


}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 3.73292075290073e-29 * fConst0;
	fConst2 = fConst0 * (fConst0 * (fConst0 * (-1.05633134620746e-20 - fConst1) + -3.11506369039915e-14) + -2.30719916990074e-11) + -1.07493164710329e-09;
	fConst3 = fConst0 * (fConst0 * (fConst0 * (fConst1 + 1.01643277726662e-20) + 2.91602352831988e-14) + 2.29636966370042e-11);
	double fConst4 = 3.98985774247549e-22 * fConst0;
	fConst5 = fConst0 * (fConst0 * (fConst4 + 1.99042653510896e-15) + 1.83615604104971e-13);
	fConst6 = 4.76991513499346e-20 * fConst0;
	fConst7 = fConst6 + -5.38351707988916e-15;
	fConst8 = -5.00346713698171e-13 - fConst6;
	fConst9 = mydsp_faustpower3_f(fConst0);
	fConst10 = 5.05730339185222e-13 * fConst0;
	fConst11 = fConst10 + -1.16162215422261e-12;
	fConst12 = mydsp_faustpower2_f(fConst0);
	fConst13 = fConst3 + 1.07449105454163e-09;
	fConst14 = fConst5 + 5.31230624730483e-11;
	fConst15 = fConst0 * (fConst0 * (fConst0 * (fConst1 + -1.05633134620746e-20) + 3.11506369039915e-14) + -2.30719916990074e-11) + 1.07493164710329e-09;
	fConst16 = fConst0 * (fConst0 * (fConst0 * (1.01643277726662e-20 - fConst1) + -2.91602352831988e-14) + 2.29636966370042e-11) + -1.07449105454163e-09;
	fConst17 = fConst0 * (fConst0 * (fConst4 + -1.99042653510896e-15) + 1.83615604104971e-13) + -5.31230624730483e-11;
	double fConst18 = 1.86646037645036e-28 * fConst0;
	fConst19 = fConst0 * (fConst0 * (fConst0 * (3.16899403862238e-20 - fConst18) + -3.11506369039915e-14) + -2.30719916990074e-11) + 3.22479494130986e-09;
	fConst20 = fConst0 * (fConst0 * (fConst0 * (fConst18 + -3.04929833179984e-20) + 2.91602352831988e-14) + 2.29636966370042e-11) + -3.22347316362488e-09;
	double fConst21 = 1.19695732274265e-21 * fConst0;
	fConst22 = fConst0 * (fConst0 * (1.99042653510896e-15 - fConst21) + 1.83615604104971e-13) + -1.59369187419145e-10;
	double fConst23 = 3.73292075290073e-28 * fConst0;
	fConst24 = fConst0 * (fConst0 * (fConst0 * (fConst23 + -2.11266269241492e-20) + -6.2301273807983e-14) + 4.61439833980148e-11) + 2.14986329420657e-09;
	fConst25 = fConst0 * (fConst0 * (fConst0 * (2.03286555453323e-20 - fConst23) + 5.83204705663976e-14) + -4.59273932740084e-11) + -2.14898210908325e-09;
	double fConst26 = 7.97971548495099e-22 * fConst0;
	fConst27 = fConst0 * (fConst0 * (fConst26 + 3.98085307021793e-15) + -3.67231208209942e-13) + -1.06246124946097e-10;
	fConst28 = fConst0 * (fConst0 * (fConst0 * (-2.11266269241492e-20 - fConst23) + 6.2301273807983e-14) + 4.61439833980148e-11) + -2.14986329420657e-09;
	fConst29 = fConst0 * (fConst0 * (fConst0 * (fConst23 + 2.03286555453323e-20) + -5.83204705663976e-14) + -4.59273932740084e-11) + 2.14898210908325e-09;
	fConst30 = fConst0 * (fConst0 * (fConst26 + -3.98085307021793e-15) + -3.67231208209942e-13) + 1.06246124946097e-10;
	fConst31 = fConst0 * (fConst0 * (fConst0 * (fConst18 + 3.16899403862238e-20) + 3.11506369039915e-14) + -2.30719916990074e-11) + -3.22479494130986e-09;
	fConst32 = fConst0 * (fConst0 * (fConst0 * (-3.04929833179984e-20 - fConst18) + -2.91602352831988e-14) + 2.29636966370042e-11) + 3.22347316362488e-09;
	fConst33 = fConst0 * (fConst0 * (-1.99042653510896e-15 - fConst21) + 1.83615604104971e-13) + 1.59369187419145e-10;
	fConst34 = 1.43097454049804e-19 * fConst0;
	fConst35 = 5.38351707988916e-15 - fConst34;
	fConst36 = fConst34 + 5.00346713698171e-13;
	fConst37 = -1.16162215422261e-12 - fConst10;
	fConst38 = 1.01146067837044e-12 * fConst0;
	fConst39 = 2.32324430844522e-12 - fConst38;
	fConst40 = 9.53983026998693e-20 * fConst0;
	fConst41 = fConst40 + 1.07670341597783e-14;
	fConst42 = 1.00069342739634e-12 - fConst40;
	fConst43 = fConst38 + 2.32324430844522e-12;
	fConst44 = fConst40 + -1.07670341597783e-14;
	fConst45 = -1.00069342739634e-12 - fConst40;
	fConst46 = -5.38351707988916e-15 - fConst34;
	fConst47 = fConst34 + -5.00346713698171e-13;
	fConst48 = fConst6 + 5.38351707988916e-15;
	fConst49 = 5.00346713698171e-13 - fConst6;

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
	double fSlow0 = 0.007000000000000006 * (1.0 - double(fVslider0));
	double fSlow1 = 0.007000000000000006 * (1.0 - double(fVslider1));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		double fTemp0 = fConst2 * fRec0[0];
		fRec1[0] = fSlow1 + 0.993 * fRec1[1];
		double fTemp1 = fConst12 * (fConst11 * fRec1[0] + 1.16162215422261e-12 - fConst10);
		fRec2[0] = double(input0[i0]) - (fRec2[1] * (fConst0 * (fConst33 + fRec0[0] * (fConst32 + fConst31 * fRec0[0])) + 1.22201390871017e-08) + fRec2[2] * (fConst0 * (fConst30 + fRec0[0] * (fConst29 + fConst28 * fRec0[0])) + 2.44402781742033e-08) + fRec2[3] * (fConst0 * (fConst27 + fRec0[0] * (fConst25 + fConst24 * fRec0[0])) + 2.44402781742033e-08) + fRec2[4] * (fConst0 * (fConst22 + fRec0[0] * (fConst20 + fConst19 * fRec0[0])) + 1.22201390871017e-08) + fRec2[5] * (fConst0 * (fConst17 + fRec0[0] * (fConst16 + fConst15 * fRec0[0])) + 2.44402781742033e-09)) / (fConst0 * (fConst14 + fRec0[0] * (fConst13 + fTemp0)) + 2.44402781742033e-09);
		double fTemp2 = fConst12 * (fConst10 + fConst37 * fRec1[0] + 1.16162215422261e-12);
		output0[i0] = FAUSTFLOAT((fRec2[0] * (fConst9 * fRec0[0] * (fConst6 + fConst49 * fRec1[0] + fRec0[0] * (fConst48 * fRec1[0] + -5.38351707988916e-15 - fConst6) + -5.00346713698171e-13) + fTemp2) + fRec2[1] * (fConst9 * fRec0[0] * (fConst47 * fRec1[0] + fRec0[0] * (fConst34 + fConst46 * fRec1[0] + 5.38351707988916e-15) + 5.00346713698171e-13 - fConst34) + fTemp1) + fRec2[2] * (fConst9 * fRec0[0] * (fConst40 + fConst45 * fRec1[0] + fRec0[0] * (fConst44 * fRec1[0] + 1.07670341597783e-14 - fConst40) + 1.00069342739634e-12) + fConst12 * (fConst43 * fRec1[0] + -2.32324430844522e-12 - fConst38)) + fRec2[3] * (fConst9 * fRec0[0] * (fConst40 + fConst42 * fRec1[0] + fRec0[0] * (fConst41 * fRec1[0] + -1.07670341597783e-14 - fConst40) + -1.00069342739634e-12) + fConst12 * (fConst38 + fConst39 * fRec1[0] + -2.32324430844522e-12)) + fRec2[4] * (fTemp2 + fConst9 * fRec0[0] * (fConst36 * fRec1[0] + fRec0[0] * (fConst34 + fConst35 * fRec1[0] + -5.38351707988916e-15) + -5.00346713698171e-13 - fConst34)) + fRec2[5] * (fTemp1 + fConst9 * fRec0[0] * (fConst6 + fConst8 * fRec1[0] + fRec0[0] * (fConst7 * fRec1[0] + 5.38351707988916e-15 - fConst6) + 5.00346713698171e-13))) / (fConst0 * (fConst5 + fRec0[0] * (fConst3 + fTemp0 + 1.07449105454163e-09) + 5.31230624730483e-11) + 2.44402781742033e-09));
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		for (int j0 = 5; j0 > 0; j0 = j0 - 1) {
			fRec2[j0] = fRec2[j0 - 1];
		}
	}

	FAUSTFLOAT bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		bufCl[i0] = FAUSTFLOAT(asymclip4(double(bufCl[i0])));
	}
	smpCl.down(bufCl, output0);

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("fuzzface.Fuzz",N_("Fuzz"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("fuzzface.Level",N_("Level"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
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
                        <property name=\"var_id\">fuzzface.Fuzz</property>\n\
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
                        <property name=\"var_id\">fuzzface.Level</property>\n\
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
                <property name=\"var_id\">fuzzface.Level</property>\n\
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
#define PARAM(p) ("fuzzface" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Fuzz"), "Fuzz");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknob(PARAM("Level"), "Level");

    b.create_small_rackknobr(PARAM("Fuzz"), "Fuzz");
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

} // end namespace fuzzface
