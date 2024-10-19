// generated from file '../src/faust/peak_eq.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace peak_eq {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fVslider1;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider2;
	double fConst2;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT fVslider11;
	double fRec3[3];
	double fRec2[3];
	double fRec1[3];
	double fRec0[3];

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
	id = "eq";
	name = N_("Peak EQ");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Tone Control");       // category
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
	for (int l0 = 0; l0 < 3; l0 = l0 + 1) fRec3[l0] = 0.0;
	for (int l1 = 0; l1 < 3; l1 = l1 + 1) fRec2[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRec1[l2] = 0.0;
	for (int l3 = 0; l3 < 3; l3 = l3 + 1) fRec0[l3] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 6.283185307179586 / fConst0;
	fConst2 = 3.141592653589793 / fConst0;
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = double(fVslider0);
	int iSlow1 = fSlow0 > 0.0;
	double fSlow2 = double(fVslider1);
	double fSlow3 = std::sin(fConst1 * fSlow2);
	double fSlow4 = double(fVslider2);
	double fSlow5 = fConst2 * (fSlow4 * std::pow(1e+01, 0.05 * std::fabs(fSlow0)) / fSlow3);
	double fSlow6 = fConst2 * (fSlow4 / fSlow3);
	double fSlow7 = ((iSlow1) ? fSlow6 : fSlow5);
	double fSlow8 = std::tan(fConst2 * fSlow2);
	double fSlow9 = 1.0 / fSlow8;
	double fSlow10 = fSlow9 * (fSlow9 + fSlow7) + 1.0;
	double fSlow11 = ((iSlow1) ? fSlow5 : fSlow6);
	double fSlow12 = fSlow9 * (fSlow9 - fSlow11) + 1.0;
	double fSlow13 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fSlow8));
	double fSlow14 = fSlow9 * (fSlow9 - fSlow7) + 1.0;
	double fSlow15 = double(fVslider3);
	int iSlow16 = fSlow15 > 0.0;
	double fSlow17 = double(fVslider4);
	double fSlow18 = std::sin(fConst1 * fSlow17);
	double fSlow19 = double(fVslider5);
	double fSlow20 = fConst2 * (fSlow19 * std::pow(1e+01, 0.05 * std::fabs(fSlow15)) / fSlow18);
	double fSlow21 = fConst2 * (fSlow19 / fSlow18);
	double fSlow22 = ((iSlow16) ? fSlow21 : fSlow20);
	double fSlow23 = std::tan(fConst2 * fSlow17);
	double fSlow24 = 1.0 / fSlow23;
	double fSlow25 = fSlow24 * (fSlow24 + fSlow22) + 1.0;
	double fSlow26 = ((iSlow16) ? fSlow20 : fSlow21);
	double fSlow27 = fSlow24 * (fSlow24 - fSlow26) + 1.0;
	double fSlow28 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fSlow23));
	double fSlow29 = fSlow24 * (fSlow24 - fSlow22) + 1.0;
	double fSlow30 = double(fVslider6);
	int iSlow31 = fSlow30 > 0.0;
	double fSlow32 = double(fVslider7);
	double fSlow33 = std::sin(fConst1 * fSlow32);
	double fSlow34 = double(fVslider8);
	double fSlow35 = fConst2 * (fSlow34 * std::pow(1e+01, 0.05 * std::fabs(fSlow30)) / fSlow33);
	double fSlow36 = fConst2 * (fSlow34 / fSlow33);
	double fSlow37 = ((iSlow31) ? fSlow36 : fSlow35);
	double fSlow38 = std::tan(fConst2 * fSlow32);
	double fSlow39 = 1.0 / fSlow38;
	double fSlow40 = fSlow39 * (fSlow39 + fSlow37) + 1.0;
	double fSlow41 = ((iSlow31) ? fSlow35 : fSlow36);
	double fSlow42 = fSlow39 * (fSlow39 - fSlow41) + 1.0;
	double fSlow43 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fSlow38));
	double fSlow44 = fSlow39 * (fSlow39 - fSlow37) + 1.0;
	double fSlow45 = double(fVslider9);
	int iSlow46 = fSlow45 > 0.0;
	double fSlow47 = double(fVslider10);
	double fSlow48 = std::sin(fConst1 * fSlow47);
	double fSlow49 = double(fVslider11);
	double fSlow50 = fConst2 * (fSlow49 * std::pow(1e+01, 0.05 * std::fabs(fSlow45)) / fSlow48);
	double fSlow51 = fConst2 * (fSlow49 / fSlow48);
	double fSlow52 = ((iSlow46) ? fSlow51 : fSlow50);
	double fSlow53 = std::tan(fConst2 * fSlow47);
	double fSlow54 = 1.0 / fSlow53;
	double fSlow55 = fSlow54 * (fSlow54 + fSlow52) + 1.0;
	double fSlow56 = ((iSlow46) ? fSlow50 : fSlow51);
	double fSlow57 = fSlow54 * (fSlow54 - fSlow56) + 1.0;
	double fSlow58 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fSlow53));
	double fSlow59 = fSlow54 * (fSlow54 - fSlow52) + 1.0;
	double fSlow60 = fSlow54 * (fSlow54 + fSlow56) + 1.0;
	double fSlow61 = fSlow39 * (fSlow39 + fSlow41) + 1.0;
	double fSlow62 = fSlow24 * (fSlow24 + fSlow26) + 1.0;
	double fSlow63 = fSlow9 * (fSlow9 + fSlow11) + 1.0;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = fSlow13 * fRec0[1];
		double fTemp1 = fSlow28 * fRec1[1];
		double fTemp2 = fSlow43 * fRec2[1];
		double fTemp3 = fSlow58 * fRec3[1];
		fRec3[0] = double(input0[i0]) - (fRec3[2] * fSlow59 + fTemp3) / fSlow55;
		fRec2[0] = (fTemp3 + fRec3[0] * fSlow60 + fRec3[2] * fSlow57) / fSlow55 - (fRec2[2] * fSlow44 + fTemp2) / fSlow40;
		fRec1[0] = (fTemp2 + fRec2[0] * fSlow61 + fRec2[2] * fSlow42) / fSlow40 - (fRec1[2] * fSlow29 + fTemp1) / fSlow25;
		fRec0[0] = (fTemp1 + fRec1[0] * fSlow62 + fRec1[2] * fSlow27) / fSlow25 - (fRec0[2] * fSlow14 + fTemp0) / fSlow10;
		output0[i0] = FAUSTFLOAT((fTemp0 + fRec0[0] * fSlow63 + fRec0[2] * fSlow12) / fSlow10);
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("eq.bandwidth1",N_("Q"),"SL",N_("bandwidth (hz)"),&fVslider11, 41.0, 5.0, 2e+04, 1.01, 0);
	reg.registerFloatVar("eq.bandwidth2",N_("Q"),"SL",N_("bandwidth (hz)"),&fVslider8, 2.2e+02, 5.0, 2e+04, 1.01, 0);
	reg.registerFloatVar("eq.bandwidth3",N_("Q"),"SL",N_("bandwidth (hz)"),&fVslider5, 8.8e+02, 5.0, 2e+04, 1.01, 0);
	reg.registerFloatVar("eq.bandwidth4",N_("Q"),"SL",N_("bandwidth (hz)"),&fVslider2, 1.76e+03, 5.0, 2e+04, 1.01, 0);
	reg.registerFloatVar("eq.level1",N_("Sub"),"S",N_("gain (dB)"),&fVslider9, 0.0, -5e+01, 5e+01, 0.1, 0);
	reg.registerFloatVar("eq.level2",N_("Low"),"S",N_("gain (dB)"),&fVslider6, 0.0, -5e+01, 5e+01, 0.1, 0);
	reg.registerFloatVar("eq.level3",N_("Mid"),"S",N_("gain (dB)"),&fVslider3, 0.0, -5e+01, 5e+01, 0.1, 0);
	reg.registerFloatVar("eq.level4",N_("High"),"S",N_("gain (dB)"),&fVslider0, 0.0, -5e+01, 5e+01, 0.1, 0);
	reg.registerFloatVar("eq.peak1","","SL",N_("frequency (hz)"),&fVslider10, 1.1e+02, 2e+01, 2.2e+04, 1.01, 0);
	reg.registerFloatVar("eq.peak2","","SL",N_("frequency (hz)"),&fVslider7, 4.4e+02, 2e+01, 2.2e+04, 1.01, 0);
	reg.registerFloatVar("eq.peak3","","SL",N_("frequency (hz)"),&fVslider4, 1.76e+03, 2e+01, 2.2e+04, 1.01, 0);
	reg.registerFloatVar("eq.peak4","","SL",N_("frequency (hz)"),&fVslider1, 3.52e+03, 2e+01, 2.2e+04, 1.01, 0);
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
            <child>\n\
              <object class=\"GtkGrid\" id=\"table1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"row_spacing\">3</property>\n\
                <property name=\"column_spacing\">14</property>\n\
                <child>\n\
                  <object class=\"GxSmallKnob\" id=\"gxsmallknob1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eq.bandwidth1</property>\n\
                    <property name=\"label_ref\">label1:rack_label_inverse</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">0</property>\n\
                    <property name=\"top_attach\">3</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxSmallKnob\" id=\"gxsmallknob2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eq.bandwidth2</property>\n\
                    <property name=\"label_ref\">label2:rack_label_inverse</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">1</property>\n\
                    <property name=\"top_attach\">3</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxSmallKnob\" id=\"gxsmallknob3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eq.bandwidth3</property>\n\
                    <property name=\"label_ref\">label3:rack_label_inverse</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">2</property>\n\
                    <property name=\"top_attach\">3</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxSmallKnob\" id=\"gxsmallknob4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eq.bandwidth4</property>\n\
                    <property name=\"label_ref\">label4:rack_label_inverse</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">3</property>\n\
                    <property name=\"top_attach\">3</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxSmallKnobR\" id=\"gxvslider1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eq.level1</property>\n\
                    <property name=\"label_ref\">label5:rack_label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">0</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxSmallKnobR\" id=\"gxvslider2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eq.level2</property>\n\
                    <property name=\"label_ref\">label6:rack_label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">1</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxSmallKnobR\" id=\"gxvslider3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eq.level3</property>\n\
                    <property name=\"label_ref\">label7:rack_label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">2</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxSmallKnobR\" id=\"gxvslider4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eq.level4</property>\n\
                    <property name=\"label_ref\">label8:rack_label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">3</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eq.peak1</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">0</property>\n\
                    <property name=\"top_attach\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eq.peak2</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">1</property>\n\
                    <property name=\"top_attach\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eq.peak3</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">2</property>\n\
                    <property name=\"top_attach\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eq.peak4</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">3</property>\n\
                    <property name=\"top_attach\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label1:rack_label_inverse\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"label\" translatable=\"yes\">label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">0</property>\n\
                    <property name=\"top_attach\">4</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label2:rack_label_inverse\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"label\" translatable=\"yes\">label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">1</property>\n\
                    <property name=\"top_attach\">4</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label3:rack_label_inverse\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"label\" translatable=\"yes\">label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">2</property>\n\
                    <property name=\"top_attach\">4</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label4:rack_label_inverse\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"label\" translatable=\"yes\">label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">3</property>\n\
                    <property name=\"top_attach\">4</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label5:rack_label\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"label\" translatable=\"yes\">label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">0</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label6:rack_label\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"label\" translatable=\"yes\">label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">1</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label7:rack_label\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"label\" translatable=\"yes\">label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">2</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label8:rack_label\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"label\" translatable=\"yes\">label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">3</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"position\">0</property>\n\
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
          <object class=\"GtkBox\" id=\"minibox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <placeholder/>\n\
            </child>\n\
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
#define PARAM(p) ("eq" "." p)
b.openHorizontalhideBox("");
b.closeBox();
b.openHorizontalTableBox("");
{
    b.openVerticalBox1("");
    {
	b.create_small_rackknob(PARAM("level1"), _("peak"));
	b.insertSpacer();
	b.create_spin_value(PARAM("peak1"), _("frequency"));
	b.insertSpacer();
	b.create_spin_value(PARAM("bandwidth1"), _("bandwidth"));
    }
    b.closeBox();
    b.openVerticalBox1("");
    {
	b.create_small_rackknob(PARAM("level2"), _("peak"));
	b.insertSpacer();
	b.create_spin_value(PARAM("peak2"), _("frequency"));
	b.insertSpacer();
	b.create_spin_value(PARAM("bandwidth2"), _("bandwidth"));
    }
    b.closeBox();
    b.openVerticalBox1("");
    {
	b.create_small_rackknob(PARAM("level3"), _("peak"));
	b.insertSpacer();
	b.create_spin_value(PARAM("peak3"), _("frequency"));
	b.insertSpacer();
	b.create_spin_value(PARAM("bandwidth3"), _("bandwidth"));
    }
    b.closeBox();
    b.openVerticalBox1("");
    {
	b.create_small_rackknob(PARAM("level4"), _("peak"));
	b.insertSpacer();
	b.create_spin_value(PARAM("peak4"), _("frequency"));
	b.insertSpacer();
	b.create_spin_value(PARAM("bandwidth4"), _("bandwidth"));
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

} // end namespace peak_eq
