// generated from file '../src/faust/peak_eq.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace peak_eq {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	double 	fConst4;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT 	fslider11;
	double 	fRec3[3];
	double 	fRec2[3];
	double 	fRec1[3];
	double 	fRec0[3];

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
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = (3.141592653589793 / fConst0);
	fConst2 = double((1.0 / fConst0));
	fConst3 = (6.283185307179586 * fConst2);
	fConst4 = (3.141592653589793 * fConst2);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = double(fslider0);
	double 	fSlow1 = tan((fConst1 * fSlow0));
	double 	fSlow2 = (1.0 / fSlow1);
	double 	fSlow3 = sin((fConst3 * fSlow0));
	double 	fSlow4 = double(fslider1);
	double 	fSlow5 = double(fslider2);
	double 	fSlow6 = (fConst4 * ((fSlow5 * pow(10,(0.05 * fabs(fSlow4)))) / fSlow3));
	double 	fSlow7 = (fConst4 * (fSlow5 / fSlow3));
	int 	iSlow8 = int((fSlow4 > 0));
	double 	fSlow9 = ((iSlow8)?fSlow7:fSlow6);
	double 	fSlow10 = (1 + (fSlow2 * (fSlow9 + fSlow2)));
	double 	fSlow11 = (2 * (1 - (1.0 / faustpower<2>(fSlow1))));
	double 	fSlow12 = (1 + (fSlow2 * (fSlow2 - fSlow9)));
	double 	fSlow13 = double(fslider3);
	double 	fSlow14 = tan((fConst1 * fSlow13));
	double 	fSlow15 = (1.0 / fSlow14);
	double 	fSlow16 = sin((fConst3 * fSlow13));
	double 	fSlow17 = double(fslider4);
	double 	fSlow18 = double(fslider5);
	double 	fSlow19 = (fConst4 * ((fSlow18 * pow(10,(0.05 * fabs(fSlow17)))) / fSlow16));
	double 	fSlow20 = (fConst4 * (fSlow18 / fSlow16));
	int 	iSlow21 = int((fSlow17 > 0));
	double 	fSlow22 = ((iSlow21)?fSlow20:fSlow19);
	double 	fSlow23 = (1 + (fSlow15 * (fSlow22 + fSlow15)));
	double 	fSlow24 = (2 * (1 - (1.0 / faustpower<2>(fSlow14))));
	double 	fSlow25 = (1 + (fSlow15 * (fSlow15 - fSlow22)));
	double 	fSlow26 = double(fslider6);
	double 	fSlow27 = tan((fConst1 * fSlow26));
	double 	fSlow28 = (1.0 / fSlow27);
	double 	fSlow29 = sin((fConst3 * fSlow26));
	double 	fSlow30 = double(fslider7);
	double 	fSlow31 = double(fslider8);
	double 	fSlow32 = (fConst4 * ((fSlow31 * pow(10,(0.05 * fabs(fSlow30)))) / fSlow29));
	double 	fSlow33 = (fConst4 * (fSlow31 / fSlow29));
	int 	iSlow34 = int((fSlow30 > 0));
	double 	fSlow35 = ((iSlow34)?fSlow33:fSlow32);
	double 	fSlow36 = (1 + (fSlow28 * (fSlow35 + fSlow28)));
	double 	fSlow37 = (2 * (1 - (1.0 / faustpower<2>(fSlow27))));
	double 	fSlow38 = (1 + (fSlow28 * (fSlow28 - fSlow35)));
	double 	fSlow39 = double(fslider9);
	double 	fSlow40 = tan((fConst1 * fSlow39));
	double 	fSlow41 = (1.0 / fSlow40);
	double 	fSlow42 = sin((fConst3 * fSlow39));
	double 	fSlow43 = double(fslider10);
	double 	fSlow44 = double(fslider11);
	double 	fSlow45 = (fConst4 * ((fSlow44 * pow(10,(0.05 * fabs(fSlow43)))) / fSlow42));
	double 	fSlow46 = (fConst4 * (fSlow44 / fSlow42));
	int 	iSlow47 = int((fSlow43 > 0));
	double 	fSlow48 = ((iSlow47)?fSlow46:fSlow45);
	double 	fSlow49 = (1 + (fSlow41 * (fSlow48 + fSlow41)));
	double 	fSlow50 = (2 * (1 - (1.0 / faustpower<2>(fSlow40))));
	double 	fSlow51 = (1 + (fSlow41 * (fSlow41 - fSlow48)));
	double 	fSlow52 = ((iSlow47)?fSlow45:fSlow46);
	double 	fSlow53 = (1 + (fSlow41 * (fSlow41 - fSlow52)));
	double 	fSlow54 = (1 + (fSlow41 * (fSlow52 + fSlow41)));
	double 	fSlow55 = ((iSlow34)?fSlow32:fSlow33);
	double 	fSlow56 = (1 + (fSlow28 * (fSlow28 - fSlow55)));
	double 	fSlow57 = (1 + (fSlow28 * (fSlow55 + fSlow28)));
	double 	fSlow58 = ((iSlow21)?fSlow19:fSlow20);
	double 	fSlow59 = (1 + (fSlow15 * (fSlow15 - fSlow58)));
	double 	fSlow60 = (1 + (fSlow15 * (fSlow58 + fSlow15)));
	double 	fSlow61 = ((iSlow8)?fSlow6:fSlow7);
	double 	fSlow62 = (1 + (fSlow2 * (fSlow2 - fSlow61)));
	double 	fSlow63 = (1 + (fSlow2 * (fSlow61 + fSlow2)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (fSlow11 * fRec0[1]);
		double fTemp1 = (fSlow24 * fRec1[1]);
		double fTemp2 = (fSlow37 * fRec2[1]);
		double fTemp3 = (fSlow50 * fRec3[1]);
		fRec3[0] = ((double)input0[i] - (((fSlow51 * fRec3[2]) + fTemp3) / fSlow49));
		fRec2[0] = (((fTemp3 + ((fSlow54 * fRec3[0]) + (fSlow53 * fRec3[2]))) / fSlow49) - (((fSlow38 * fRec2[2]) + fTemp2) / fSlow36));
		fRec1[0] = (((fTemp2 + ((fSlow57 * fRec2[0]) + (fSlow56 * fRec2[2]))) / fSlow36) - (((fSlow25 * fRec1[2]) + fTemp1) / fSlow23));
		fRec0[0] = (((fTemp1 + ((fSlow60 * fRec1[0]) + (fSlow59 * fRec1[2]))) / fSlow23) - (((fSlow12 * fRec0[2]) + fTemp0) / fSlow10));
		output0[i] = (FAUSTFLOAT)((fTemp0 + ((fSlow63 * fRec0[0]) + (fSlow62 * fRec0[2]))) / fSlow10);
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
	}
}
		
void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("eq.bandwidth1",N_("Q"),"S",N_("bandwidth (hz)"),&fslider11, 41.0, 5.0, 2e+04, 1.0);
	reg.registerVar("eq.bandwidth2",N_("Q"),"S",N_("bandwidth (hz)"),&fslider8, 2.2e+02, 5.0, 2e+04, 1.0);
	reg.registerVar("eq.bandwidth3",N_("Q"),"S",N_("bandwidth (hz)"),&fslider5, 8.8e+02, 5.0, 2e+04, 1.0);
	reg.registerVar("eq.bandwidth4",N_("Q"),"S",N_("bandwidth (hz)"),&fslider2, 1.76e+03, 5.0, 2e+04, 1.0);
	reg.registerVar("eq.level1",N_("Sub"),"S",N_("gain (dB)"),&fslider10, 0.0, -5e+01, 5e+01, 0.1);
	reg.registerVar("eq.level2",N_("Low"),"S",N_("gain (dB)"),&fslider7, 0.0, -5e+01, 5e+01, 0.1);
	reg.registerVar("eq.level3",N_("Mid"),"S",N_("gain (dB)"),&fslider4, 0.0, -5e+01, 5e+01, 0.1);
	reg.registerVar("eq.level4",N_("High"),"S",N_("gain (dB)"),&fslider1, 0.0, -5e+01, 5e+01, 0.1);
	reg.registerVar("eq.peak1","","S",N_("frequency (hz)"),&fslider9, 1.1e+02, 2e+01, 2.2e+04, 1.0);
	reg.registerVar("eq.peak2","","S",N_("frequency (hz)"),&fslider6, 4.4e+02, 2e+01, 2.2e+04, 1.0);
	reg.registerVar("eq.peak3","","S",N_("frequency (hz)"),&fslider3, 1.76e+03, 2e+01, 2.2e+04, 1.0);
	reg.registerVar("eq.peak4","","S",N_("frequency (hz)"),&fslider0, 3.52e+03, 2e+01, 2.2e+04, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<interface>\n\
  <!-- interface-requires gxwidgets 0.0 -->\n\
  <requires lib=\"gtk+\" version=\"2.20\"/>\n\
  <!-- interface-naming-policy project-wide -->\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can_focus\">False</property>\n\
    <child>\n\
      <object class=\"GtkVBox\" id=\"vbox1\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can_focus\">False</property>\n\
        <child>\n\
          <object class=\"GtkHBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <child>\n\
              <object class=\"GtkTable\" id=\"table1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"n_rows\">5</property>\n\
                <property name=\"n_columns\">4</property>\n\
                <property name=\"column_spacing\">14</property>\n\
                <property name=\"row_spacing\">3</property>\n\
                <child>\n\
                  <object class=\"GxSmallKnob\" id=\"gxsmallknob1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eq.bandwidth1</property>\n\
                    <property name=\"label_ref\">label1:rack_label_inverse</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"top_attach\">3</property>\n\
                    <property name=\"bottom_attach\">4</property>\n\
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
                    <property name=\"right_attach\">2</property>\n\
                    <property name=\"top_attach\">3</property>\n\
                    <property name=\"bottom_attach\">4</property>\n\
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
                    <property name=\"right_attach\">3</property>\n\
                    <property name=\"top_attach\">3</property>\n\
                    <property name=\"bottom_attach\">4</property>\n\
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
                    <property name=\"right_attach\">4</property>\n\
                    <property name=\"top_attach\">3</property>\n\
                    <property name=\"bottom_attach\">4</property>\n\
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
                    <property name=\"top_attach\">2</property>\n\
                    <property name=\"bottom_attach\">3</property>\n\
                    <property name=\"x_options\">GTK_EXPAND</property>\n\
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
                    <property name=\"right_attach\">2</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                    <property name=\"bottom_attach\">3</property>\n\
                    <property name=\"x_options\">GTK_EXPAND</property>\n\
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
                    <property name=\"right_attach\">3</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                    <property name=\"bottom_attach\">3</property>\n\
                    <property name=\"x_options\">GTK_EXPAND</property>\n\
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
                    <property name=\"right_attach\">4</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                    <property name=\"bottom_attach\">3</property>\n\
                    <property name=\"x_options\">GTK_EXPAND</property>\n\
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
                    <property name=\"x_options\">GTK_EXPAND</property>\n\
                    <property name=\"y_options\">GTK_EXPAND</property>\n\
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
                    <property name=\"right_attach\">2</property>\n\
                    <property name=\"x_options\">GTK_EXPAND</property>\n\
                    <property name=\"y_options\">GTK_EXPAND</property>\n\
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
                    <property name=\"right_attach\">3</property>\n\
                    <property name=\"x_options\">GTK_EXPAND</property>\n\
                    <property name=\"y_options\">GTK_EXPAND</property>\n\
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
                    <property name=\"right_attach\">4</property>\n\
                    <property name=\"x_options\">GTK_EXPAND</property>\n\
                    <property name=\"y_options\">GTK_EXPAND</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label1:rack_label_inverse\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"label\" translatable=\"yes\">label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"top_attach\">4</property>\n\
                    <property name=\"bottom_attach\">5</property>\n\
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
                    <property name=\"right_attach\">2</property>\n\
                    <property name=\"top_attach\">4</property>\n\
                    <property name=\"bottom_attach\">5</property>\n\
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
                    <property name=\"right_attach\">3</property>\n\
                    <property name=\"top_attach\">4</property>\n\
                    <property name=\"bottom_attach\">5</property>\n\
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
                    <property name=\"right_attach\">4</property>\n\
                    <property name=\"top_attach\">4</property>\n\
                    <property name=\"bottom_attach\">5</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkLabel\" id=\"label5:rack_label\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"label\" translatable=\"yes\">label</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"top_attach\">1</property>\n\
                    <property name=\"bottom_attach\">2</property>\n\
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
                    <property name=\"right_attach\">2</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                    <property name=\"bottom_attach\">2</property>\n\
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
                    <property name=\"right_attach\">3</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                    <property name=\"bottom_attach\">2</property>\n\
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
                    <property name=\"right_attach\">4</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                    <property name=\"bottom_attach\">2</property>\n\
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
          <object class=\"GtkHBox\" id=\"minibox\">\n\
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
