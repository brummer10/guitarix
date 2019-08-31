// generated from file '../src/faust/peak_eq.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace peak_eq {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fVslider5;
	double fConst2;
	double fRec3[3];
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT fVslider7;
	double fRec2[3];
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT fVslider9;
	double fRec1[3];
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT fVslider11;
	double fRec0[3];

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
	for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) fRec3[l0] = 0.0;
	for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) fRec2[l1] = 0.0;
	for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) fRec1[l2] = 0.0;
	for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) fRec0[l3] = 0.0;
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
	fConst2 = (6.2831853071795862 / fConst0);
	fVslider0 = FAUSTFLOAT(3520.0);
	fVslider1 = FAUSTFLOAT(1760.0);
	fVslider2 = FAUSTFLOAT(440.0);
	fVslider3 = FAUSTFLOAT(110.0);
	fVslider4 = FAUSTFLOAT(0.0);
	fVslider5 = FAUSTFLOAT(41.0);
	fVslider6 = FAUSTFLOAT(0.0);
	fVslider7 = FAUSTFLOAT(220.0);
	fVslider8 = FAUSTFLOAT(0.0);
	fVslider9 = FAUSTFLOAT(880.0);
	fVslider10 = FAUSTFLOAT(0.0);
	fVslider11 = FAUSTFLOAT(1760.0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = double(fVslider0);
	double fSlow1 = std::tan((fConst1 * fSlow0));
	double fSlow2 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fSlow1))));
	double fSlow3 = double(fVslider1);
	double fSlow4 = std::tan((fConst1 * fSlow3));
	double fSlow5 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fSlow4))));
	double fSlow6 = double(fVslider2);
	double fSlow7 = std::tan((fConst1 * fSlow6));
	double fSlow8 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fSlow7))));
	double fSlow9 = double(fVslider3);
	double fSlow10 = std::tan((fConst1 * fSlow9));
	double fSlow11 = (1.0 / fSlow10);
	double fSlow12 = double(fVslider4);
	int iSlow13 = (fSlow12 > 0.0);
	double fSlow14 = double(fVslider5);
	double fSlow15 = std::sin((fConst2 * fSlow9));
	double fSlow16 = (fConst1 * (fSlow14 / fSlow15));
	double fSlow17 = (fConst1 * ((fSlow14 * std::pow(10.0, (0.050000000000000003 * std::fabs(fSlow12)))) / fSlow15));
	double fSlow18 = (iSlow13?fSlow17:fSlow16);
	double fSlow19 = (1.0 - (fSlow11 * (fSlow18 - fSlow11)));
	double fSlow20 = (iSlow13?fSlow16:fSlow17);
	double fSlow21 = (1.0 - (fSlow11 * (fSlow20 - fSlow11)));
	double fSlow22 = (2.0 * (1.0 - (1.0 / mydsp_faustpower2_f(fSlow10))));
	double fSlow23 = ((fSlow11 * (fSlow11 + fSlow20)) + 1.0);
	double fSlow24 = ((fSlow11 * (fSlow11 + fSlow18)) + 1.0);
	double fSlow25 = (1.0 / fSlow7);
	double fSlow26 = double(fVslider6);
	int iSlow27 = (fSlow26 > 0.0);
	double fSlow28 = double(fVslider7);
	double fSlow29 = std::sin((fConst2 * fSlow6));
	double fSlow30 = (fConst1 * ((fSlow28 * std::pow(10.0, (0.050000000000000003 * std::fabs(fSlow26)))) / fSlow29));
	double fSlow31 = (fConst1 * (fSlow28 / fSlow29));
	double fSlow32 = (iSlow27?fSlow31:fSlow30);
	double fSlow33 = (1.0 - (fSlow25 * (fSlow32 - fSlow25)));
	double fSlow34 = ((fSlow25 * (fSlow25 + fSlow32)) + 1.0);
	double fSlow35 = (iSlow27?fSlow30:fSlow31);
	double fSlow36 = ((fSlow25 * (fSlow25 + fSlow35)) + 1.0);
	double fSlow37 = (1.0 - (fSlow25 * (fSlow35 - fSlow25)));
	double fSlow38 = (1.0 / fSlow4);
	double fSlow39 = double(fVslider8);
	int iSlow40 = (fSlow39 > 0.0);
	double fSlow41 = double(fVslider9);
	double fSlow42 = std::sin((fConst2 * fSlow3));
	double fSlow43 = (fConst1 * ((fSlow41 * std::pow(10.0, (0.050000000000000003 * std::fabs(fSlow39)))) / fSlow42));
	double fSlow44 = (fConst1 * (fSlow41 / fSlow42));
	double fSlow45 = (iSlow40?fSlow44:fSlow43);
	double fSlow46 = (1.0 - (fSlow38 * (fSlow45 - fSlow38)));
	double fSlow47 = ((fSlow38 * (fSlow38 + fSlow45)) + 1.0);
	double fSlow48 = (iSlow40?fSlow43:fSlow44);
	double fSlow49 = ((fSlow38 * (fSlow38 + fSlow48)) + 1.0);
	double fSlow50 = (1.0 - (fSlow38 * (fSlow48 - fSlow38)));
	double fSlow51 = (1.0 / fSlow1);
	double fSlow52 = double(fVslider10);
	int iSlow53 = (fSlow52 > 0.0);
	double fSlow54 = double(fVslider11);
	double fSlow55 = std::sin((fConst2 * fSlow0));
	double fSlow56 = (fConst1 * ((fSlow54 * std::pow(10.0, (0.050000000000000003 * std::fabs(fSlow52)))) / fSlow55));
	double fSlow57 = (fConst1 * (fSlow54 / fSlow55));
	double fSlow58 = (iSlow53?fSlow57:fSlow56);
	double fSlow59 = (1.0 - (fSlow51 * (fSlow58 - fSlow51)));
	double fSlow60 = ((fSlow51 * (fSlow51 + fSlow58)) + 1.0);
	double fSlow61 = (iSlow53?fSlow56:fSlow57);
	double fSlow62 = ((fSlow51 * (fSlow51 + fSlow61)) + 1.0);
	double fSlow63 = (1.0 - (fSlow51 * (fSlow61 - fSlow51)));
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = (fSlow22 * fRec3[1]);
		fRec3[0] = (double(input0[i]) - (((fRec3[2] * fSlow21) + fTemp0) / fSlow23));
		double fTemp1 = (fSlow8 * fRec2[1]);
		fRec2[0] = ((((fSlow19 * fRec3[2]) + ((fRec3[0] * fSlow24) + fTemp0)) / fSlow23) - (((fRec2[2] * fSlow33) + fTemp1) / fSlow34));
		double fTemp2 = (fSlow5 * fRec1[1]);
		fRec1[0] = ((((fTemp1 + (fRec2[0] * fSlow36)) + (fRec2[2] * fSlow37)) / fSlow34) - (((fRec1[2] * fSlow46) + fTemp2) / fSlow47));
		double fTemp3 = (fSlow2 * fRec0[1]);
		fRec0[0] = ((((fTemp2 + (fRec1[0] * fSlow49)) + (fRec1[2] * fSlow50)) / fSlow47) - (((fRec0[2] * fSlow59) + fTemp3) / fSlow60));
		output0[i] = FAUSTFLOAT((((fTemp3 + (fRec0[0] * fSlow62)) + (fRec0[2] * fSlow63)) / fSlow60));
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
	reg.registerVar("eq.bandwidth1",N_("Q"),"S",N_("bandwidth (hz)"),&fVslider5, 41.0, 5.0, 20000.0, 1.0);
	reg.registerVar("eq.bandwidth2",N_("Q"),"S",N_("bandwidth (hz)"),&fVslider7, 220.0, 5.0, 20000.0, 1.0);
	reg.registerVar("eq.bandwidth3",N_("Q"),"S",N_("bandwidth (hz)"),&fVslider9, 880.0, 5.0, 20000.0, 1.0);
	reg.registerVar("eq.bandwidth4",N_("Q"),"S",N_("bandwidth (hz)"),&fVslider11, 1760.0, 5.0, 20000.0, 1.0);
	reg.registerVar("eq.level1",N_("Sub"),"S",N_("gain (dB)"),&fVslider4, 0.0, -50.0, 50.0, 0.10000000000000001);
	reg.registerVar("eq.level2",N_("Low"),"S",N_("gain (dB)"),&fVslider6, 0.0, -50.0, 50.0, 0.10000000000000001);
	reg.registerVar("eq.level3",N_("Mid"),"S",N_("gain (dB)"),&fVslider8, 0.0, -50.0, 50.0, 0.10000000000000001);
	reg.registerVar("eq.level4",N_("High"),"S",N_("gain (dB)"),&fVslider10, 0.0, -50.0, 50.0, 0.10000000000000001);
	reg.registerVar("eq.peak1","","S",N_("frequency (hz)"),&fVslider3, 110.0, 20.0, 22000.0, 1.0);
	reg.registerVar("eq.peak2","","S",N_("frequency (hz)"),&fVslider2, 440.0, 20.0, 22000.0, 1.0);
	reg.registerVar("eq.peak3","","S",N_("frequency (hz)"),&fVslider1, 1760.0, 20.0, 22000.0, 1.0);
	reg.registerVar("eq.peak4","","S",N_("frequency (hz)"),&fVslider0, 3520.0, 20.0, 22000.0, 1.0);
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
