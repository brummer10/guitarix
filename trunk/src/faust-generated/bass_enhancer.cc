// generated from file '../src/faust/bass_enhancer.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace bass_enhancer {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fVec0[2];
	double 	fVec1[2];
	double 	fVec2[2];
	double 	fConst4;
	double 	fRec4[2];
	double 	fRec3[3];
	double 	fRec2[3];
	double 	fRec1[3];
	double 	fRec0[3];
	double 	fRec9[2];
	double 	fRec8[3];
	double 	fRec7[3];
	double 	fRec6[3];
	double 	fRec5[3];
	FAUSTFLOAT 	fslider1;
	double 	fRec10[2];
	double 	fRec17[3];
	double 	fRec16[3];
	double 	fRec15[3];
	double 	fRec14[3];
	double 	fRec13[2];
	double 	fRec12[2];
	double 	fRec11[2];
	double 	fRec22[2];
	double 	fRec21[3];
	double 	fRec20[3];
	double 	fRec19[3];
	double 	fRec18[3];
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
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (3.141592653589793 / double(iConst0));
	fConst2 = (62.83185307179586 / double(iConst0));
	fConst3 = (1 - fConst2);
	fConst4 = (1.0 / (1 + fConst2));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	double 	fSlow0 = tan((fConst1 * double(fslider0)));
	double 	fSlow1 = (1.0 / faustpower<2>(fSlow0));
	double 	fSlow2 = (2 * (1 - fSlow1));
	double 	fSlow3 = (1.0 / fSlow0);
	double 	fSlow4 = (1 + ((fSlow3 - 0.39018064403225594) / fSlow0));
	double 	fSlow5 = (1.0 / (1 + ((0.39018064403225594 + fSlow3) / fSlow0)));
	double 	fSlow6 = (1 + ((fSlow3 - 1.111140466039204) / fSlow0));
	double 	fSlow7 = (1.0 / (1 + ((fSlow3 + 1.111140466039204) / fSlow0)));
	double 	fSlow8 = (1 + ((fSlow3 - 1.66293922460509) / fSlow0));
	double 	fSlow9 = (1.0 / (1 + ((fSlow3 + 1.66293922460509) / fSlow0)));
	double 	fSlow10 = (1 + ((fSlow3 - 1.9615705608064609) / fSlow0));
	double 	fSlow11 = (1.0 / (1 + ((fSlow3 + 1.9615705608064609) / fSlow0)));
	double 	fSlow12 = (2 * (0 - fSlow1));
	double 	fSlow13 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider1))));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input1[i];
		fVec0[0] = fTemp0;
		double fTemp1 = (double)input0[i];
		fVec1[0] = fTemp1;
		double fTemp2 = (fVec1[0] + fVec0[0]);
		fVec2[0] = fTemp2;
		fRec4[0] = (fConst4 * ((fVec2[0] - fVec2[1]) + (fConst3 * fRec4[1])));
		fRec3[0] = (fRec4[0] - (fSlow11 * ((fSlow10 * fRec3[2]) + (fSlow2 * fRec3[1]))));
		fRec2[0] = ((fSlow11 * (fRec3[2] + (fRec3[0] + (2 * fRec3[1])))) - (fSlow9 * ((fSlow8 * fRec2[2]) + (fSlow2 * fRec2[1]))));
		fRec1[0] = ((fSlow9 * (fRec2[2] + (fRec2[0] + (2 * fRec2[1])))) - (fSlow7 * ((fSlow6 * fRec1[2]) + (fSlow2 * fRec1[1]))));
		fRec0[0] = ((fSlow7 * (fRec1[2] + (fRec1[0] + (2 * fRec1[1])))) - (fSlow5 * ((fSlow4 * fRec0[2]) + (fSlow2 * fRec0[1]))));
		double fTemp3 = (fRec0[2] + (fRec0[0] + (2 * fRec0[1])));
		fRec9[0] = (fConst4 * ((fVec1[0] - fVec1[1]) + (fConst3 * fRec9[1])));
		fRec8[0] = (fRec9[0] - (fSlow11 * ((fSlow10 * fRec8[2]) + (fSlow2 * fRec8[1]))));
		fRec7[0] = ((fSlow11 * (((fSlow1 * fRec8[0]) + (fSlow12 * fRec8[1])) + (fSlow1 * fRec8[2]))) - (fSlow9 * ((fSlow8 * fRec7[2]) + (fSlow2 * fRec7[1]))));
		fRec6[0] = ((fSlow9 * (((fSlow1 * fRec7[0]) + (fSlow12 * fRec7[1])) + (fSlow1 * fRec7[2]))) - (fSlow7 * ((fSlow6 * fRec6[2]) + (fSlow2 * fRec6[1]))));
		fRec5[0] = ((fSlow7 * (((fSlow1 * fRec6[0]) + (fSlow12 * fRec6[1])) + (fSlow1 * fRec6[2]))) - (fSlow5 * ((fSlow4 * fRec5[2]) + (fSlow2 * fRec5[1]))));
		fRec10[0] = ((0.999 * fRec10[1]) + fSlow13);
		fRec17[0] = (fVec2[0] - (fSlow11 * ((fSlow10 * fRec17[2]) + (fSlow2 * fRec17[1]))));
		fRec16[0] = ((fSlow11 * (fRec17[2] + (fRec17[0] + (2 * fRec17[1])))) - (fSlow9 * ((fSlow8 * fRec16[2]) + (fSlow2 * fRec16[1]))));
		fRec15[0] = ((fSlow9 * (fRec16[2] + (fRec16[0] + (2 * fRec16[1])))) - (fSlow7 * ((fSlow6 * fRec15[2]) + (fSlow2 * fRec15[1]))));
		fRec14[0] = ((fSlow7 * (fRec15[2] + (fRec15[0] + (2 * fRec15[1])))) - (fSlow5 * ((fSlow4 * fRec14[2]) + (fSlow2 * fRec14[1]))));
		double fTemp4 = (fRec14[2] + (fRec14[0] + (2 * fRec14[1])));
		double fTemp5 = (fSlow5 * fTemp4);
		fRec13[0] = (((1 - ((0.03 * (fRec13[1] <= fTemp5)) + (0.015 * (fRec13[1] > fTemp5)))) * fRec12[1]) + (fSlow5 * (fTemp4 * ((0.03 * (fRec11[1] <= fTemp5)) + (0.015 * (fRec11[1] > fTemp5))))));
		fRec12[0] = fRec13[0];
		fRec11[0] = fRec12[0];
		double fTemp6 = (fRec11[0] * fRec10[0]);
		output0[i] = (FAUSTFLOAT)(fTemp6 + (fSlow5 * ((((fSlow1 * fRec5[0]) + (fSlow12 * fRec5[1])) + (fSlow1 * fRec5[2])) + fTemp3)));
		fRec22[0] = (fConst4 * ((fVec0[0] - fVec0[1]) + (fConst3 * fRec22[1])));
		fRec21[0] = (fRec22[0] - (fSlow11 * ((fSlow10 * fRec21[2]) + (fSlow2 * fRec21[1]))));
		fRec20[0] = ((fSlow11 * (((fSlow1 * fRec21[0]) + (fSlow12 * fRec21[1])) + (fSlow1 * fRec21[2]))) - (fSlow9 * ((fSlow8 * fRec20[2]) + (fSlow2 * fRec20[1]))));
		fRec19[0] = ((fSlow9 * (((fSlow1 * fRec20[0]) + (fSlow12 * fRec20[1])) + (fSlow1 * fRec20[2]))) - (fSlow7 * ((fSlow6 * fRec19[2]) + (fSlow2 * fRec19[1]))));
		fRec18[0] = ((fSlow7 * (((fSlow1 * fRec19[0]) + (fSlow12 * fRec19[1])) + (fSlow1 * fRec19[2]))) - (fSlow5 * ((fSlow4 * fRec18[2]) + (fSlow2 * fRec18[1]))));
		output1[i] = (FAUSTFLOAT)(fTemp6 + (fSlow5 * (fTemp3 + (((fSlow1 * fRec18[0]) + (fSlow12 * fRec18[1])) + (fSlow1 * fRec18[2])))));
		// post processing
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec10[1] = fRec10[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fVec2[1] = fVec2[0];
		fVec1[1] = fVec1[0];
		fVec0[1] = fVec0[0];
	}
}
		
void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("bassEnhancer.Frequency","","S","",&fslider0, 1e+02, 6e+01, 2.4e+02, 5.0);
	reg.registerVar("bassEnhancer.HarmonicsdB",N_("Harmonics"),"S","",&fslider1, 0.0, -16.0, 32.0, 0.1);
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
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GtkHBox\" id=\"hbox1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"spacing\">10</property>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
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
                  <object class=\"GtkVBox\" id=\"vbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
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
          <object class=\"GtkHBox\" id=\"minibox\">\n\
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
                <property name=\"xalign\">0</property>\n\
                <property name=\"label\" translatable=\"yes\">Harmonics</property>\n\
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
