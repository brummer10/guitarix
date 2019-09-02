// generated from file '../src/faust/bass_enhancer.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace bass_enhancer {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fHslider0;
	double fVec0[2];
	double fVec1[2];
	double fVec2[2];
	double fRec6[3];
	double fRec5[3];
	double fRec4[3];
	double fRec3[3];
	double fRec2[2];
	double fRec1[2];
	double fRec0[2];
	FAUSTFLOAT fHslider1;
	double fRec7[2];
	double fConst2;
	double fConst3;
	double fConst4;
	double fRec12[2];
	double fRec11[3];
	double fRec10[3];
	double fRec9[3];
	double fRec8[3];
	double fRec17[2];
	double fRec16[3];
	double fRec15[3];
	double fRec14[3];
	double fRec13[3];
	double fRec22[2];
	double fRec21[3];
	double fRec20[3];
	double fRec19[3];
	double fRec18[3];

	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fVec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fVec1[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fVec2[l2] = 0.0;
	for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) fRec6[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec5[l4] = 0.0;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec4[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec3[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec2[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec1[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec0[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec7[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec12[l11] = 0.0;
	for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) fRec11[l12] = 0.0;
	for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) fRec10[l13] = 0.0;
	for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) fRec9[l14] = 0.0;
	for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) fRec8[l15] = 0.0;
	for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) fRec17[l16] = 0.0;
	for (int l17 = 0; (l17 < 3); l17 = (l17 + 1)) fRec16[l17] = 0.0;
	for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) fRec15[l18] = 0.0;
	for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) fRec14[l19] = 0.0;
	for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) fRec13[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec22[l21] = 0.0;
	for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) fRec21[l22] = 0.0;
	for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) fRec20[l23] = 0.0;
	for (int l24 = 0; (l24 < 3); l24 = (l24 + 1)) fRec19[l24] = 0.0;
	for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) fRec18[l25] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = (3.1415926535897931 / fConst0);
	fConst2 = (62.831853071795862 / fConst0);
	fConst3 = (1.0 / (fConst2 + 1.0));
	fConst4 = (1.0 - fConst2);
	fHslider0 = FAUSTFLOAT(100.0);
	fHslider1 = FAUSTFLOAT(0.0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	double fSlow0 = std::tan((fConst1 * double(fHslider0)));
	double fSlow1 = (1.0 / fSlow0);
	double fSlow2 = (1.0 / (((fSlow1 + 0.39018064403225594) / fSlow0) + 1.0));
	double fSlow3 = (1.0 / (((fSlow1 + 1.1111404660392039) / fSlow0) + 1.0));
	double fSlow4 = (1.0 / (((fSlow1 + 1.66293922460509) / fSlow0) + 1.0));
	double fSlow5 = (1.0 / (((fSlow1 + 1.9615705608064609) / fSlow0) + 1.0));
	double fSlow6 = (((fSlow1 + -1.9615705608064609) / fSlow0) + 1.0);
	double fSlow7 = mydsp_faustpower2_f(fSlow0);
	double fSlow8 = (1.0 / fSlow7);
	double fSlow9 = (2.0 * (1.0 - fSlow8));
	double fSlow10 = (((fSlow1 + -1.66293922460509) / fSlow0) + 1.0);
	double fSlow11 = (((fSlow1 + -1.1111404660392039) / fSlow0) + 1.0);
	double fSlow12 = (((fSlow1 + -0.39018064403225594) / fSlow0) + 1.0);
	double fSlow13 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fHslider1))));
	double fSlow14 = (0.0 - (2.0 / fSlow7));
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = double(input0[i]);
		fVec0[0] = fTemp0;
		double fTemp1 = double(input1[i]);
		fVec1[0] = fTemp1;
		double fTemp2 = (fTemp0 + fTemp1);
		fVec2[0] = fTemp2;
		fRec6[0] = (fTemp2 - (fSlow5 * ((fSlow6 * fRec6[2]) + (fSlow9 * fRec6[1]))));
		fRec5[0] = ((fSlow5 * (fRec6[2] + (fRec6[0] + (2.0 * fRec6[1])))) - (fSlow4 * ((fSlow10 * fRec5[2]) + (fSlow9 * fRec5[1]))));
		fRec4[0] = ((fSlow4 * (fRec5[2] + (fRec5[0] + (2.0 * fRec5[1])))) - (fSlow3 * ((fSlow11 * fRec4[2]) + (fSlow9 * fRec4[1]))));
		fRec3[0] = ((fSlow3 * (fRec4[2] + (fRec4[0] + (2.0 * fRec4[1])))) - (fSlow2 * ((fSlow12 * fRec3[2]) + (fSlow9 * fRec3[1]))));
		double fTemp3 = (fRec3[2] + (fRec3[0] + (2.0 * fRec3[1])));
		double fTemp4 = (fSlow2 * fTemp3);
		fRec2[0] = (((1.0 - ((0.029999999999999999 * double((fRec2[1] <= fTemp4))) + (0.014999999999999999 * double((fRec2[1] > fTemp4))))) * fRec1[1]) + (fSlow2 * (fTemp3 * ((0.029999999999999999 * double((fRec0[1] <= fTemp4))) + (0.014999999999999999 * double((fRec0[1] > fTemp4)))))));
		fRec1[0] = fRec2[0];
		fRec0[0] = fRec1[0];
		fRec7[0] = (fSlow13 + (0.999 * fRec7[1]));
		double fTemp5 = (fRec0[0] * fRec7[0]);
		fRec12[0] = (fConst3 * ((fTemp0 - fVec0[1]) + (fConst4 * fRec12[1])));
		fRec11[0] = (fRec12[0] - (fSlow5 * ((fSlow6 * fRec11[2]) + (fSlow9 * fRec11[1]))));
		fRec10[0] = ((fSlow5 * (((fSlow8 * fRec11[0]) + (fSlow14 * fRec11[1])) + (fSlow8 * fRec11[2]))) - (fSlow4 * ((fSlow10 * fRec10[2]) + (fSlow9 * fRec10[1]))));
		fRec9[0] = ((fSlow4 * (((fSlow8 * fRec10[0]) + (fSlow14 * fRec10[1])) + (fSlow8 * fRec10[2]))) - (fSlow3 * ((fSlow11 * fRec9[2]) + (fSlow9 * fRec9[1]))));
		fRec8[0] = ((fSlow3 * (((fSlow8 * fRec9[0]) + (fSlow14 * fRec9[1])) + (fSlow8 * fRec9[2]))) - (fSlow2 * ((fSlow12 * fRec8[2]) + (fSlow9 * fRec8[1]))));
		fRec17[0] = (fConst3 * ((fTemp2 - fVec2[1]) + (fConst4 * fRec17[1])));
		fRec16[0] = (fRec17[0] - (fSlow5 * ((fSlow6 * fRec16[2]) + (fSlow9 * fRec16[1]))));
		fRec15[0] = ((fSlow5 * (fRec16[2] + (fRec16[0] + (2.0 * fRec16[1])))) - (fSlow4 * ((fSlow10 * fRec15[2]) + (fSlow9 * fRec15[1]))));
		fRec14[0] = ((fSlow4 * (fRec15[2] + (fRec15[0] + (2.0 * fRec15[1])))) - (fSlow3 * ((fSlow11 * fRec14[2]) + (fSlow9 * fRec14[1]))));
		fRec13[0] = ((fSlow3 * (fRec14[2] + (fRec14[0] + (2.0 * fRec14[1])))) - (fSlow2 * ((fSlow12 * fRec13[2]) + (fSlow9 * fRec13[1]))));
		double fTemp6 = (fRec13[2] + (fRec13[0] + (2.0 * fRec13[1])));
		output0[i] = FAUSTFLOAT((fTemp5 + (fSlow2 * ((((fSlow8 * fRec8[0]) + (fSlow14 * fRec8[1])) + (fSlow8 * fRec8[2])) + fTemp6))));
		fRec22[0] = (fConst3 * ((fTemp1 - fVec1[1]) + (fConst4 * fRec22[1])));
		fRec21[0] = (fRec22[0] - (fSlow5 * ((fSlow6 * fRec21[2]) + (fSlow9 * fRec21[1]))));
		fRec20[0] = ((fSlow5 * (((fSlow8 * fRec21[0]) + (fSlow14 * fRec21[1])) + (fSlow8 * fRec21[2]))) - (fSlow4 * ((fSlow10 * fRec20[2]) + (fSlow9 * fRec20[1]))));
		fRec19[0] = ((fSlow4 * (((fSlow8 * fRec20[0]) + (fSlow14 * fRec20[1])) + (fSlow8 * fRec20[2]))) - (fSlow3 * ((fSlow11 * fRec19[2]) + (fSlow9 * fRec19[1]))));
		fRec18[0] = ((fSlow3 * (((fSlow8 * fRec19[0]) + (fSlow14 * fRec19[1])) + (fSlow8 * fRec19[2]))) - (fSlow2 * ((fSlow12 * fRec18[2]) + (fSlow9 * fRec18[1]))));
		output1[i] = FAUSTFLOAT((fTemp5 + (fSlow2 * (fTemp6 + (((fSlow8 * fRec18[0]) + (fSlow14 * fRec18[1])) + (fSlow8 * fRec18[2]))))));
		fVec0[1] = fVec0[0];
		fVec1[1] = fVec1[0];
		fVec2[1] = fVec2[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec7[1] = fRec7[0];
		fRec12[1] = fRec12[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec17[1] = fRec17[0];
		fRec16[2] = fRec16[1];
		fRec16[1] = fRec16[0];
		fRec15[2] = fRec15[1];
		fRec15[1] = fRec15[0];
		fRec14[2] = fRec14[1];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
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
	reg.registerVar("bassEnhancer.Frequency","","S","",&fHslider0, 100.0, 60.0, 240.0, 5.0);
	reg.registerVar("bassEnhancer.HarmonicsdB",N_("Harmonics"),"S","",&fHslider1, 0.0, -16.0, 32.0, 0.10000000000000001);
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
