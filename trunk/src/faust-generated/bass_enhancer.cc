// generated from file '../src/faust/bass_enhancer.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace bass_enhancer {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fHslider0;
	double fConst1;
	double fConst3;
	double fVec0[2];
	double fVec1[2];
	double fVec2[2];
	double fConst4;
	double fRec4[2];
	double fRec3[3];
	double fRec2[3];
	double fRec1[3];
	double fRec0[3];
	double fRec9[2];
	double fRec8[3];
	double fRec7[3];
	double fRec6[3];
	double fRec5[3];
	FAUSTFLOAT fHslider1;
	double fRec10[2];
	double fRec17[3];
	double fRec16[3];
	double fRec15[3];
	double fRec14[3];
	double fRec13[2];
	double fRec12[2];
	double fRec11[2];
	double fRec22[2];
	double fRec21[3];
	double fRec20[3];
	double fRec19[3];
	double fRec18[3];

	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int sample_rate, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef*);
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
	id = "bassEnhancer";
	name = N_("Bass Enhancer");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Misc");       // category
	shortname = N_("BassEnhancer");     // shortname
	mono_audio = 0;
	stereo_audio = compute_static;
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fVec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fVec1[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fVec2[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec4[l3] = 0.0;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRec3[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec2[l5] = 0.0;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec1[l6] = 0.0;
	for (int l7 = 0; l7 < 3; l7 = l7 + 1) fRec0[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec9[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec8[l9] = 0.0;
	for (int l10 = 0; l10 < 3; l10 = l10 + 1) fRec7[l10] = 0.0;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec6[l11] = 0.0;
	for (int l12 = 0; l12 < 3; l12 = l12 + 1) fRec5[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec10[l13] = 0.0;
	for (int l14 = 0; l14 < 3; l14 = l14 + 1) fRec17[l14] = 0.0;
	for (int l15 = 0; l15 < 3; l15 = l15 + 1) fRec16[l15] = 0.0;
	for (int l16 = 0; l16 < 3; l16 = l16 + 1) fRec15[l16] = 0.0;
	for (int l17 = 0; l17 < 3; l17 = l17 + 1) fRec14[l17] = 0.0;
	for (int l18 = 0; l18 < 2; l18 = l18 + 1) fRec13[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fRec12[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec11[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec22[l21] = 0.0;
	for (int l22 = 0; l22 < 3; l22 = l22 + 1) fRec21[l22] = 0.0;
	for (int l23 = 0; l23 < 3; l23 = l23 + 1) fRec20[l23] = 0.0;
	for (int l24 = 0; l24 < 3; l24 = l24 + 1) fRec19[l24] = 0.0;
	for (int l25 = 0; l25 < 3; l25 = l25 + 1) fRec18[l25] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 3.141592653589793 / fConst0;
	double fConst2 = 62.83185307179586 / fConst0;
	fConst3 = 1.0 - fConst2;
	fConst4 = 1.0 / (fConst2 + 1.0);
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	double fSlow0 = std::tan(fConst1 * double(fHslider0));
	double fSlow1 = mydsp_faustpower2_f(fSlow0);
	double fSlow2 = 1.0 / fSlow1;
	double fSlow3 = 2.0 * (1.0 - fSlow2);
	double fSlow4 = 1.0 / fSlow0;
	double fSlow5 = (fSlow4 + -0.39018064403225594) / fSlow0 + 1.0;
	double fSlow6 = 1.0 / ((fSlow4 + 0.39018064403225594) / fSlow0 + 1.0);
	double fSlow7 = (fSlow4 + -1.111140466039204) / fSlow0 + 1.0;
	double fSlow8 = 1.0 / ((fSlow4 + 1.111140466039204) / fSlow0 + 1.0);
	double fSlow9 = (fSlow4 + -1.66293922460509) / fSlow0 + 1.0;
	double fSlow10 = 1.0 / ((fSlow4 + 1.66293922460509) / fSlow0 + 1.0);
	double fSlow11 = (fSlow4 + -1.9615705608064609) / fSlow0 + 1.0;
	double fSlow12 = 1.0 / ((fSlow4 + 1.9615705608064609) / fSlow0 + 1.0);
	double fSlow13 = 0.0 - 2.0 / fSlow1;
	double fSlow14 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fHslider1));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input1[i0]);
		fVec0[0] = fTemp0;
		double fTemp1 = double(input0[i0]);
		fVec1[0] = fTemp1;
		double fTemp2 = fTemp1 + fTemp0;
		fVec2[0] = fTemp2;
		fRec4[0] = fConst4 * (fTemp2 - fVec2[1] + fConst3 * fRec4[1]);
		fRec3[0] = fRec4[0] - fSlow12 * (fSlow11 * fRec3[2] + fSlow3 * fRec3[1]);
		fRec2[0] = fSlow12 * (fRec3[2] + fRec3[0] + 2.0 * fRec3[1]) - fSlow10 * (fSlow9 * fRec2[2] + fSlow3 * fRec2[1]);
		fRec1[0] = fSlow10 * (fRec2[2] + fRec2[0] + 2.0 * fRec2[1]) - fSlow8 * (fSlow7 * fRec1[2] + fSlow3 * fRec1[1]);
		fRec0[0] = fSlow8 * (fRec1[2] + fRec1[0] + 2.0 * fRec1[1]) - fSlow6 * (fSlow5 * fRec0[2] + fSlow3 * fRec0[1]);
		double fTemp3 = fRec0[2] + fRec0[0] + 2.0 * fRec0[1];
		fRec9[0] = fConst4 * (fTemp1 - fVec1[1] + fConst3 * fRec9[1]);
		fRec8[0] = fRec9[0] - fSlow12 * (fSlow11 * fRec8[2] + fSlow3 * fRec8[1]);
		fRec7[0] = fSlow12 * (fSlow2 * fRec8[0] + fSlow13 * fRec8[1] + fSlow2 * fRec8[2]) - fSlow10 * (fSlow9 * fRec7[2] + fSlow3 * fRec7[1]);
		fRec6[0] = fSlow10 * (fSlow2 * fRec7[0] + fSlow13 * fRec7[1] + fSlow2 * fRec7[2]) - fSlow8 * (fSlow7 * fRec6[2] + fSlow3 * fRec6[1]);
		fRec5[0] = fSlow8 * (fSlow2 * fRec6[0] + fSlow13 * fRec6[1] + fSlow2 * fRec6[2]) - fSlow6 * (fSlow5 * fRec5[2] + fSlow3 * fRec5[1]);
		fRec10[0] = fSlow14 + 0.999 * fRec10[1];
		fRec17[0] = fTemp2 - fSlow12 * (fSlow11 * fRec17[2] + fSlow3 * fRec17[1]);
		fRec16[0] = fSlow12 * (fRec17[2] + fRec17[0] + 2.0 * fRec17[1]) - fSlow10 * (fSlow9 * fRec16[2] + fSlow3 * fRec16[1]);
		fRec15[0] = fSlow10 * (fRec16[2] + fRec16[0] + 2.0 * fRec16[1]) - fSlow8 * (fSlow7 * fRec15[2] + fSlow3 * fRec15[1]);
		fRec14[0] = fSlow8 * (fRec15[2] + fRec15[0] + 2.0 * fRec15[1]) - fSlow6 * (fSlow5 * fRec14[2] + fSlow3 * fRec14[1]);
		double fTemp4 = fRec14[2] + fRec14[0] + 2.0 * fRec14[1];
		double fTemp5 = fSlow6 * fTemp4;
		fRec13[0] = (1.0 - (0.03 * double(fRec13[1] <= fTemp5) + 0.015 * double(fRec13[1] > fTemp5))) * fRec12[1] + fSlow6 * fTemp4 * (0.03 * double(fRec11[1] <= fTemp5) + 0.015 * double(fRec11[1] > fTemp5));
		fRec12[0] = fRec13[0];
		fRec11[0] = fRec12[0];
		double fTemp6 = fRec11[0] * fRec10[0];
		output0[i0] = FAUSTFLOAT(fTemp6 + fSlow6 * (fSlow2 * fRec5[0] + fSlow13 * fRec5[1] + fSlow2 * fRec5[2] + fTemp3));
		fRec22[0] = fConst4 * (fTemp0 - fVec0[1] + fConst3 * fRec22[1]);
		fRec21[0] = fRec22[0] - fSlow12 * (fSlow11 * fRec21[2] + fSlow3 * fRec21[1]);
		fRec20[0] = fSlow12 * (fSlow2 * fRec21[0] + fSlow13 * fRec21[1] + fSlow2 * fRec21[2]) - fSlow10 * (fSlow9 * fRec20[2] + fSlow3 * fRec20[1]);
		fRec19[0] = fSlow10 * (fSlow2 * fRec20[0] + fSlow13 * fRec20[1] + fSlow2 * fRec20[2]) - fSlow8 * (fSlow7 * fRec19[2] + fSlow3 * fRec19[1]);
		fRec18[0] = fSlow8 * (fSlow2 * fRec19[0] + fSlow13 * fRec19[1] + fSlow2 * fRec19[2]) - fSlow6 * (fSlow5 * fRec18[2] + fSlow3 * fRec18[1]);
		output1[i0] = FAUSTFLOAT(fTemp6 + fSlow6 * (fTemp3 + fSlow2 * fRec18[0] + fSlow13 * fRec18[1] + fSlow2 * fRec18[2]));
		fVec0[1] = fVec0[0];
		fVec1[1] = fVec1[0];
		fVec2[1] = fVec2[0];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec10[1] = fRec10[0];
		fRec17[2] = fRec17[1];
		fRec17[1] = fRec17[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fRec22[1] = fRec22[0];
		fRec21[2] = fRec21[1];
		fRec21[1] = fRec21[0];
		fRec20[2] = fRec20[1];
		fRec20[1] = fRec20[0];
		fRec19[2] = fRec19[1];
		fRec19[1] = fRec19[0];
		fRec18[2] = fRec18[1];
		fRec18[1] = fRec18[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("bassEnhancer.Frequency","","S","",&fHslider0, 1e+02, 6e+01, 2.4e+02, 5.0, 0);
	reg.registerFloatVar("bassEnhancer.HarmonicsdB",N_("Harmonics"),"S","",&fHslider1, 0.0, -16.0, 32.0, 0.1, 0);
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
                        <property name=\"var_id\">bassEnhancer.Frequency</property>\n\
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
                        <property name=\"var_id\">bassEnhancer.HarmonicsdB</property>\n\
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
                <property name=\"var_id\">bassEnhancer.HarmonicsdB</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Harmonics</property>\n\
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
#define PARAM(p) ("bassEnhancer" "." p)
// ----- bass enhancer
b.openHorizontalhideBox("");
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalTableBox("");
    {
	b.create_small_rackknob(PARAM("Frequency"),   _("   frequency  "));
	b.create_small_rackknob(PARAM("HarmonicsdB"), _(" harmonics dB "));
    }
    b.closeBox();
}
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

} // end namespace bass_enhancer
