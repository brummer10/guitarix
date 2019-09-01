// generated from file '../src/faust/low_high_pass.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace low_high_pass {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fCheckbox1;
	double fConst0;
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fEntry1;
	int iVec0[2];
	double fRec2[2];
	double fVec1[2];
	double fRec1[2];
	double fRec0[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fVslider1;
	double fVec2[2];
	double fRec6[2];
	double fVec3[2];
	double fRec5[2];
	double fRec4[3];
	double fRec3[3];

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



static const char* parm_groups[] = {
	".low_high_pass.lhp", N_("low_highpass"),
	".low_high_pass.lhc", N_("low_highcutoff"),
	0
	};

Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "low_highpass";
	name = N_("Low/High Filter");
	groups = parm_groups;
	description = ""; // description (tooltip)
	category = N_("Tone Control");       // category
	shortname = N_("L/H Filter");     // shortname
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) iVec0[l0] = 0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec2[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fVec1[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec1[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec0[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fVec2[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec6[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fVec3[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec5[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec4[l9] = 0.0;
	for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) fRec3[l10] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (3.1415926535897931 / std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq))));
	fCheckbox0 = FAUSTFLOAT(0.0);
	fCheckbox1 = FAUSTFLOAT(0.0);
	fEntry0 = FAUSTFLOAT(130.0);
	fEntry1 = FAUSTFLOAT(5000.0);
	fVslider0 = FAUSTFLOAT(5000.0);
	fVslider1 = FAUSTFLOAT(130.0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	int iSlow0 = int(double(fCheckbox0));
	int iSlow1 = int(double(fCheckbox1));
	double fSlow2 = std::tan((fConst0 * double(fEntry0)));
	double fSlow3 = (1.0 / fSlow2);
	double fSlow4 = (fSlow3 + 1.0);
	double fSlow5 = (0.0 - (1.0 / (fSlow2 * fSlow4)));
	double fSlow6 = (1.0 / std::tan((fConst0 * double(fEntry1))));
	double fSlow7 = (1.0 / (fSlow6 + 1.0));
	double fSlow8 = (1.0 - fSlow6);
	double fSlow9 = (1.0 / fSlow4);
	double fSlow10 = (1.0 - fSlow3);
	double fSlow11 = std::tan((fConst0 * double(fVslider0)));
	double fSlow12 = (1.0 / fSlow11);
	double fSlow13 = (1.0 / (((fSlow12 + 0.76536686473017945) / fSlow11) + 1.0));
	double fSlow14 = (1.0 / (((fSlow12 + 1.8477590650225735) / fSlow11) + 1.0));
	double fSlow15 = (fConst0 * double(fVslider1));
	double fSlow16 = (1.0 / (fSlow15 + 1.0));
	double fSlow17 = (1.0 - fSlow15);
	double fSlow18 = (((fSlow12 + -1.8477590650225735) / fSlow11) + 1.0);
	double fSlow19 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fSlow11))));
	double fSlow20 = (((fSlow12 + -0.76536686473017945) / fSlow11) + 1.0);
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = double(input0[i]);
		iVec0[0] = 1;
		fRec2[0] = ((9.9999999999999995e-21 * double((1 - iVec0[1]))) - fRec2[1]);
		double fTemp1 = (fRec2[0] + fTemp0);
		fVec1[0] = fTemp1;
		fRec1[0] = (0.0 - (fSlow7 * ((fSlow8 * fRec1[1]) - (fTemp1 + fVec1[1]))));
		fRec0[0] = ((fSlow5 * fRec1[1]) - (fSlow9 * ((fSlow10 * fRec0[1]) - (fSlow3 * fRec1[0]))));
		double fTemp2 = (iSlow1?fRec0[0]:fTemp0);
		double fTemp3 = (fRec2[0] + fTemp2);
		fVec2[0] = (fSlow16 * fTemp3);
		fRec6[0] = ((fSlow16 * (fTemp3 + (fSlow17 * fRec6[1]))) - fVec2[1]);
		fVec3[0] = (fSlow16 * fRec6[0]);
		fRec5[0] = ((fSlow16 * (fRec6[0] + (fSlow17 * fRec5[1]))) - fVec3[1]);
		fRec4[0] = (fRec5[0] - (fSlow14 * ((fSlow18 * fRec4[2]) + (fSlow19 * fRec4[1]))));
		fRec3[0] = ((fSlow14 * (fRec4[2] + (fRec4[0] + (2.0 * fRec4[1])))) - (fSlow13 * ((fSlow20 * fRec3[2]) + (fSlow19 * fRec3[1]))));
		output0[i] = FAUSTFLOAT((iSlow0?(fSlow13 * (fRec3[2] + (fRec3[0] + (2.0 * fRec3[1])))):fTemp2));
		iVec0[1] = iVec0[0];
		fRec2[1] = fRec2[0];
		fVec1[1] = fVec1[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fVec2[1] = fVec2[0];
		fRec6[1] = fRec6[0];
		fVec3[1] = fVec3[0];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("low_high_pass.lhc.high_freq",N_("Highcut"),"S",N_("high-freq cutoff Hz"),&fVslider0, 5000.0, 1000.0, 12000.0, 10.0);
	reg.registerVar("low_high_pass.lhc.low_freq",N_("Lowcut"),"S",N_("low-freq cutoff Hz"),&fVslider1, 130.0, 20.0, 1000.0, 10.0);
	reg.registerVar("low_high_pass.lhc.on_off",N_("low highcutoff"),"B","",&fCheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("low_high_pass.lhp.high_freq",N_("Highpass"),"S","",&fEntry0, 130.0, 20.0, 7040.0, 10.0);
	reg.registerVar("low_high_pass.lhp.low_freq",N_("Lowpass"),"S","",&fEntry1, 5000.0, 20.0, 12000.0, 10.0);
	reg.registerVar("low_high_pass.lhp.on_off",N_("low fi.highpass"),"B","",&fCheckbox1, 0.0, 0.0, 1.0, 1.0);
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
                  <object class=\"GtkBox\" id=\"hbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"spacing\">4</property>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"vbox6\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"orientation\">vertical</property>\n\
                        <child>\n\
                          <object class=\"GtkLabel\" id=\"label2\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">False</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxSwitch\" id=\"gxswitch1\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">low_high_pass.lhp.on_off</property>\n\
                            <property name=\"base_name\">switch</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">False</property>\n\
                            <property name=\"fill\">False</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkLabel\" id=\"label4\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
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
                            <property name=\"var_id\">low_high_pass.lhp.high_freq</property>\n\
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
                        <property name=\"position\">1</property>\n\
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
                          <object class=\"GxSmallKnobR\" id=\"gxbigknob2\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">low_high_pass.lhp.low_freq</property>\n\
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
                        <property name=\"position\">2</property>\n\
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
                  <object class=\"GtkLabel\" id=\"label1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"label\" translatable=\"yes\">    </property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">True</property>\n\
                    <property name=\"fill\">True</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"hbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"spacing\">4</property>\n\
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
                            <property name=\"var_id\">low_high_pass.lhc.low_freq</property>\n\
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
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkBox\" id=\"vbox5\">\n\
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
                            <property name=\"expand\">False</property>\n\
                            <property name=\"fill\">False</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxSmallKnobR\" id=\"gxbigknob4\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">low_high_pass.lhc.high_freq</property>\n\
                            <property name=\"label_ref\">label4:rack_label</property>\n\
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
                      <object class=\"GtkBox\" id=\"vbox7\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"orientation\">vertical</property>\n\
                        <child>\n\
                          <object class=\"GtkLabel\" id=\"label3\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">False</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxSwitch\" id=\"gxswitch2\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">low_high_pass.lhc.on_off</property>\n\
                            <property name=\"base_name\">switch</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">False</property>\n\
                            <property name=\"fill\">False</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkLabel\" id=\"label5\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
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
              <placeholder/>\n\
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
#define PARAM(p) ("low_highpass" "." p)
// low high pass filter
b.openHorizontalhideBox("");
b.closeBox();
b.openHorizontalBox("");
{
    b.openHorizontalBox("");
    {
	b.create_small_rackknob("low_high_pass.lhp.high_freq", _("high-pass "));
	b.create_small_rackknob("low_high_pass.lhp.low_freq", _(" low-pass "));
	b.create_switch_no_caption(sw_switchit, "low_high_pass.lhp.on_off");
    }
    b.closeBox();
    b.insertSpacer();
    b.openHorizontalBox("");
    {
	b.create_small_rackknob("low_high_pass.lhc.low_freq", _("low-cut "));
	b.create_small_rackknob("low_high_pass.lhc.high_freq", _("high-cut "));
	b.create_switch_no_caption(sw_switchit, "low_high_pass.lhc.on_off");
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

} // end namespace low_high_pass
