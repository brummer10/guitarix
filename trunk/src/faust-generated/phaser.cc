// generated from file '../src/faust/phaser.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace phaser {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHslider1;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	int iVec0[2];
	FAUSTFLOAT fHslider4;
	float fConst2;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	float fConst3;
	FAUSTFLOAT fHslider7;
	float fRec5[2];
	float fRec6[2];
	float fRec4[3];
	float fRec3[3];
	float fRec2[3];
	float fRec1[3];
	float fRec0[2];
	FAUSTFLOAT fCheckbox1;
	float fRec11[3];
	float fRec10[3];
	float fRec9[3];
	float fRec8[3];
	float fRec7[2];

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
	id = "phaser";
	name = N_("Phaser");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Modulation");       // category
	shortname = "";     // shortname
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) iVec0[l0] = 0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec5[l1] = 0.0f;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec6[l2] = 0.0f;
	for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) fRec4[l3] = 0.0f;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec3[l4] = 0.0f;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec2[l5] = 0.0f;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec1[l6] = 0.0f;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec0[l7] = 0.0f;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec11[l8] = 0.0f;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec10[l9] = 0.0f;
	for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) fRec9[l10] = 0.0f;
	for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) fRec8[l11] = 0.0f;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec7[l12] = 0.0f;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSamplingFreq)));
	fConst1 = (1.0f / fConst0);
	fConst2 = (6.28318548f / fConst0);
	fConst3 = (0.104719758f / fConst0);
	fHslider0 = FAUSTFLOAT(0.0f);
	fCheckbox0 = FAUSTFLOAT(0.0f);
	fHslider1 = FAUSTFLOAT(1.0f);
	fHslider2 = FAUSTFLOAT(1000.0f);
	fHslider3 = FAUSTFLOAT(0.0f);
	fHslider4 = FAUSTFLOAT(1.5f);
	fHslider5 = FAUSTFLOAT(100.0f);
	fHslider6 = FAUSTFLOAT(800.0f);
	fHslider7 = FAUSTFLOAT(30.0f);
	fCheckbox1 = FAUSTFLOAT(0.0f);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	float fSlow0 = std::pow(10.0f, (0.0500000007f * float(fHslider0)));
	float fSlow1 = (0.5f * (int(float(fCheckbox0))?2.0f:float(fHslider1)));
	float fSlow2 = (1.0f - fSlow1);
	float fSlow3 = std::exp((fConst1 * (0.0f - (3.14159274f * float(fHslider2)))));
	float fSlow4 = mydsp_faustpower2_f(fSlow3);
	float fSlow5 = (0.0f - (2.0f * fSlow3));
	float fSlow6 = float(fHslider3);
	float fSlow7 = float(fHslider4);
	float fSlow8 = float(fHslider5);
	float fSlow9 = (fConst2 * fSlow8);
	float fSlow10 = (0.5f * (0.0f - (fConst2 * (fSlow8 - std::max<float>(fSlow8, float(fHslider6))))));
	float fSlow11 = (fConst3 * float(fHslider7));
	float fSlow12 = std::sin(fSlow11);
	float fSlow13 = std::cos(fSlow11);
	float fSlow14 = mydsp_faustpower2_f(fSlow7);
	float fSlow15 = mydsp_faustpower3_f(fSlow7);
	float fSlow16 = mydsp_faustpower4_f(fSlow7);
	float fSlow17 = (int(float(fCheckbox1))?(-1.0f * fSlow1):fSlow1);
	for (int i = 0; (i < count); i = (i + 1)) {
		float fTemp0 = float(input0[i]);
		iVec0[0] = 1;
		fRec5[0] = ((fSlow12 * fRec6[1]) + (fSlow13 * fRec5[1]));
		fRec6[0] = ((float((1 - iVec0[1])) + (fSlow13 * fRec6[1])) - (fSlow12 * fRec5[1]));
		float fTemp1 = (fSlow9 + (fSlow10 * (1.0f - fRec5[0])));
		float fTemp2 = (fRec4[1] * std::cos((fSlow7 * fTemp1)));
		fRec4[0] = (((fSlow0 * fTemp0) + (fSlow6 * fRec0[1])) - ((fSlow5 * fTemp2) + (fSlow4 * fRec4[2])));
		float fTemp3 = (fRec3[1] * std::cos((fSlow14 * fTemp1)));
		fRec3[0] = ((fSlow5 * (fTemp2 - fTemp3)) + (fRec4[2] + (fSlow4 * (fRec4[0] - fRec3[2]))));
		float fTemp4 = (fRec2[1] * std::cos((fSlow15 * fTemp1)));
		fRec2[0] = ((fSlow5 * (fTemp3 - fTemp4)) + (fRec3[2] + (fSlow4 * (fRec3[0] - fRec2[2]))));
		float fTemp5 = (fRec1[1] * std::cos((fSlow16 * fTemp1)));
		fRec1[0] = ((fSlow5 * (fTemp4 - fTemp5)) + (fRec2[2] + (fSlow4 * (fRec2[0] - fRec1[2]))));
		fRec0[0] = ((fSlow4 * fRec1[0]) + ((fSlow5 * fTemp5) + fRec1[2]));
		output0[i] = FAUSTFLOAT(((fSlow0 * (fSlow2 * fTemp0)) + (fRec0[0] * fSlow17)));
		float fTemp6 = float(input1[i]);
		float fTemp7 = (fSlow9 + (fSlow10 * (1.0f - fRec6[0])));
		float fTemp8 = (fRec11[1] * std::cos((fSlow7 * fTemp7)));
		fRec11[0] = (((fSlow0 * fTemp6) + (fSlow6 * fRec7[1])) - ((fSlow5 * fTemp8) + (fSlow4 * fRec11[2])));
		float fTemp9 = (fRec10[1] * std::cos((fSlow14 * fTemp7)));
		fRec10[0] = ((fSlow5 * (fTemp8 - fTemp9)) + (fRec11[2] + (fSlow4 * (fRec11[0] - fRec10[2]))));
		float fTemp10 = (fRec9[1] * std::cos((fSlow15 * fTemp7)));
		fRec9[0] = ((fSlow5 * (fTemp9 - fTemp10)) + (fRec10[2] + (fSlow4 * (fRec10[0] - fRec9[2]))));
		float fTemp11 = (fRec8[1] * std::cos((fSlow16 * fTemp7)));
		fRec8[0] = ((fSlow5 * (fTemp10 - fTemp11)) + (fRec9[2] + (fSlow4 * (fRec9[0] - fRec8[2]))));
		fRec7[0] = ((fSlow4 * fRec8[0]) + ((fSlow5 * fTemp11) + fRec8[2]));
		output1[i] = FAUSTFLOAT(((fSlow0 * (fSlow2 * fTemp6)) + (fRec7[0] * fSlow17)));
		iVec0[1] = iVec0[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("phaser.MaxNotch1Freq",N_("Max Freq"),"S","",&fHslider6, 800.0f, 20.0f, 10000.0f, 1.0f);
	reg.registerVar("phaser.MinNotch1Freq",N_("Freq"),"S","",&fHslider5, 100.0f, 20.0f, 5000.0f, 1.0f);
	reg.registerVar("phaser.Notch width",N_("Width"),"S","",&fHslider2, 1000.0f, 10.0f, 5000.0f, 1.0f);
	reg.registerVar("phaser.NotchFreq",N_("Min Freq"),"S","",&fHslider4, 1.5f, 1.10000002f, 4.0f, 0.00999999978f);
	static const value_pair fCheckbox0_values[] = {{"direct "},{" vibrato"},{0}};
	reg.registerEnumVar("phaser.VibratoMode","","B","",fCheckbox0_values,&fCheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("phaser.depth",N_("Depth"),"S","",&fHslider1, 1.0f, 0.0f, 1.0f, 0.00999999978f);
	reg.registerVar("phaser.feedback gain",N_("Feedback"),"S","",&fHslider3, 0.0f, 0.0f, 1.0f, 0.00999999978f);
	static const value_pair fCheckbox1_values[] = {{"linear"},{"invert"},{0}};
	reg.registerEnumVar("phaser.invert","","B","",fCheckbox1_values,&fCheckbox1, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("phaser.level",N_("Level"),"S","",&fHslider0, 0.0f, -60.0f, 10.0f, 0.100000001f);
	reg.registerVar("phaser.lfobpm",N_("Speed (bpm)"),"S",N_("Speed in Beats per Minute"),&fHslider7, 30.0f, 24.0f, 360.0f, 1.0f);
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
                <property name=\"spacing\">15</property>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">4</property>\n\
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
                        <property name=\"var_id\">phaser.level</property>\n\
                        <property name=\"label_ref\">label1:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSelector\" id=\"gxselector1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">phaser.invert</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">2</property>\n\
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
                      <object class=\"GtkBox\" id=\"hbox2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"spacing\">2</property>\n\
                        <property name=\"homogeneous\">True</property>\n\
                        <child>\n\
                          <object class=\"GtkBox\" id=\"vbox4\">\n\
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
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnobR\" id=\"gxsmallknob1\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">phaser.feedback gain</property>\n\
                                <property name=\"label_ref\">label2:rack_label</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkBox\" id=\"vbox5\">\n\
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
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnobR\" id=\"gxsmallknob2\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">phaser.depth</property>\n\
                                <property name=\"label_ref\">label3:rack_label</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
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
                        <child>\n\
                          <object class=\"GtkBox\" id=\"vbox6\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label4:rack_label\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">label</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSmallKnobR\" id=\"gxsmallknob3\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">phaser.Notch width</property>\n\
                                <property name=\"label_ref\">label4:rack_label</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">2</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"hbox3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"spacing\">2</property>\n\
                        <property name=\"homogeneous\">True</property>\n\
                        <child>\n\
                          <object class=\"GtkBox\" id=\"vbox7\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <child>\n\
                              <object class=\"GxSmallKnobR\" id=\"gxsmallknob4\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">phaser.NotchFreq</property>\n\
                                <property name=\"label_ref\">label5:rack_label_inverse</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label5:rack_label_inverse\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">label</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkBox\" id=\"vbox8\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <child>\n\
                              <object class=\"GxSmallKnobR\" id=\"gxsmallknob5\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">phaser.MaxNotch1Freq</property>\n\
                                <property name=\"label_ref\">label6:rack_label_inverse</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label6:rack_label_inverse\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">label</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
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
                        <child>\n\
                          <object class=\"GtkBox\" id=\"vbox9\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"orientation\">vertical</property>\n\
                            <child>\n\
                              <object class=\"GxSmallKnobR\" id=\"gxsmallknob6\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">phaser.MinNotch1Freq</property>\n\
                                <property name=\"label_ref\">label7:rack_label_inverse</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkLabel\" id=\"label7:rack_label_inverse\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">label</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">True</property>\n\
                                <property name=\"fill\">True</property>\n\
                                <property name=\"position\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">2</property>\n\
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
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox10\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">4</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label8:rack_label\">\n\
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
                      <object class=\"GxMidKnob\" id=\"gxsmallknob7\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">phaser.lfobpm</property>\n\
                        <property name=\"label_ref\">label8:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSelector\" id=\"gxselector2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">phaser.VibratoMode</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">2</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
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
                <property name=\"var_id\">phaser.level</property>\n\
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
#define PARAM(p) ("phaser" "." p)
// phaser
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("level"), _("level"));
b.closeBox();
b.openHorizontalBox("");
{
    b.openHorizontalBox("");
    {
	b.create_small_rackknobr(PARAM("level"), _("  level "));
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.openHorizontalBox("");
	{
	    b.create_small_rackknob(PARAM("feedback gain"), _(" feedback "));
	    b.create_small_rackknob(PARAM("depth"), _("depth"));
	    b.create_small_rackknob(PARAM("Notch width"), _("width"));
	    b.create_small_rackknob(PARAM("NotchFreq"), _("freq"));
	    b.create_small_rackknob(PARAM("MaxNotch1Freq"), _("max Hz"));
	    b.create_small_rackknob(PARAM("MinNotch1Freq"), _("min Hz"));
	    b.create_small_rackknob(PARAM("lfobpm"), _("speed (bpm)"));
	}
	b.closeBox();
	b.insertSpacer();
	b.openHorizontalBox("");
	{
	    b.insertSpacer();
	    b.create_selector(PARAM("invert"), "invert");
	    b.insertSpacer();
	    b.create_selector(PARAM("VibratoMode"),"VibratoMode" );
	    b.insertSpacer();
	    b.insertSpacer();
	    b.insertSpacer();
	    b.insertSpacer();
	    b.insertSpacer();
	}
	b.closeBox();
	b.openFrameBox("");
	b.closeBox();
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

} // end namespace phaser
