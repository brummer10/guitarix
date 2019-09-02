// generated from file '../src/faust/freeverb.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace freeverb {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	double fRec9[2];
	int IOTA;
	double fVec0[2048];
	double fRec8[2];
	double fRec11[2];
	double fVec1[2048];
	double fRec10[2];
	double fRec13[2];
	double fVec2[2048];
	double fRec12[2];
	double fRec15[2];
	double fVec3[2048];
	double fRec14[2];
	double fRec17[2];
	double fVec4[2048];
	double fRec16[2];
	double fRec19[2];
	double fVec5[2048];
	double fRec18[2];
	double fRec21[2];
	double fVec6[2048];
	double fRec20[2];
	double fRec23[2];
	double fVec7[2048];
	double fRec22[2];
	double fVec8[1024];
	double fRec6[2];
	double fVec9[512];
	double fRec4[2];
	double fVec10[512];
	double fRec2[2];
	double fVec11[256];
	double fRec0[2];

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
	id = "freeverb";
	name = N_("Freeverb");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Reverb");       // category
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec9[l0] = 0.0;
	for (int l1 = 0; (l1 < 2048); l1 = (l1 + 1)) fVec0[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec8[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec11[l3] = 0.0;
	for (int l4 = 0; (l4 < 2048); l4 = (l4 + 1)) fVec1[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec10[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec13[l6] = 0.0;
	for (int l7 = 0; (l7 < 2048); l7 = (l7 + 1)) fVec2[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec12[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec15[l9] = 0.0;
	for (int l10 = 0; (l10 < 2048); l10 = (l10 + 1)) fVec3[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec14[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec17[l12] = 0.0;
	for (int l13 = 0; (l13 < 2048); l13 = (l13 + 1)) fVec4[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec16[l14] = 0.0;
	for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) fRec19[l15] = 0.0;
	for (int l16 = 0; (l16 < 2048); l16 = (l16 + 1)) fVec5[l16] = 0.0;
	for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) fRec18[l17] = 0.0;
	for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) fRec21[l18] = 0.0;
	for (int l19 = 0; (l19 < 2048); l19 = (l19 + 1)) fVec6[l19] = 0.0;
	for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) fRec20[l20] = 0.0;
	for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) fRec23[l21] = 0.0;
	for (int l22 = 0; (l22 < 2048); l22 = (l22 + 1)) fVec7[l22] = 0.0;
	for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) fRec22[l23] = 0.0;
	for (int l24 = 0; (l24 < 1024); l24 = (l24 + 1)) fVec8[l24] = 0.0;
	for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) fRec6[l25] = 0.0;
	for (int l26 = 0; (l26 < 512); l26 = (l26 + 1)) fVec9[l26] = 0.0;
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) fRec4[l27] = 0.0;
	for (int l28 = 0; (l28 < 512); l28 = (l28 + 1)) fVec10[l28] = 0.0;
	for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) fRec2[l29] = 0.0;
	for (int l30 = 0; (l30 < 256); l30 = (l30 + 1)) fVec11[l30] = 0.0;
	for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) fRec0[l31] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fVslider0 = FAUSTFLOAT(50.0);
	fVslider1 = FAUSTFLOAT(0.5);
	fVslider2 = FAUSTFLOAT(0.5);
			IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = double(fVslider0);
	double fSlow1 = (0.00014999999999999999 * fSlow0);
	double fSlow2 = ((0.28000000000000003 * double(fVslider1)) + 0.69999999999999996);
	double fSlow3 = double(fVslider2);
	double fSlow4 = (1.0 - fSlow3);
	double fSlow5 = (1.0 - (0.01 * fSlow0));
	double fSlow6 = (fSlow5 + (((0.01 * fSlow5) + 0.00014999999999999999) * fSlow0));
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = double(input0[i]);
		double fTemp1 = (fSlow1 * fTemp0);
		fRec9[0] = ((fSlow3 * fRec9[1]) + (fSlow4 * fRec8[1]));
		fVec0[(IOTA & 2047)] = (fTemp1 + (fSlow2 * fRec9[0]));
		fRec8[0] = fVec0[((IOTA - 1139) & 2047)];
		fRec11[0] = ((fSlow3 * fRec11[1]) + (fSlow4 * fRec10[1]));
		fVec1[(IOTA & 2047)] = (fTemp1 + (fSlow2 * fRec11[0]));
		fRec10[0] = fVec1[((IOTA - 1211) & 2047)];
		fRec13[0] = ((fSlow3 * fRec13[1]) + (fSlow4 * fRec12[1]));
		fVec2[(IOTA & 2047)] = (fTemp1 + (fSlow2 * fRec13[0]));
		fRec12[0] = fVec2[((IOTA - 1300) & 2047)];
		fRec15[0] = ((fSlow3 * fRec15[1]) + (fSlow4 * fRec14[1]));
		fVec3[(IOTA & 2047)] = (fTemp1 + (fSlow2 * fRec15[0]));
		fRec14[0] = fVec3[((IOTA - 1379) & 2047)];
		fRec17[0] = ((fSlow3 * fRec17[1]) + (fSlow4 * fRec16[1]));
		fVec4[(IOTA & 2047)] = (fTemp1 + (fSlow2 * fRec17[0]));
		fRec16[0] = fVec4[((IOTA - 1445) & 2047)];
		fRec19[0] = ((fSlow3 * fRec19[1]) + (fSlow4 * fRec18[1]));
		fVec5[(IOTA & 2047)] = (fTemp1 + (fSlow2 * fRec19[0]));
		fRec18[0] = fVec5[((IOTA - 1514) & 2047)];
		fRec21[0] = ((fSlow3 * fRec21[1]) + (fSlow4 * fRec20[1]));
		fVec6[(IOTA & 2047)] = (fTemp1 + (fSlow2 * fRec21[0]));
		fRec20[0] = fVec6[((IOTA - 1580) & 2047)];
		fRec23[0] = ((fSlow3 * fRec23[1]) + (fSlow4 * fRec22[1]));
		fVec7[(IOTA & 2047)] = (fTemp1 + (fSlow2 * fRec23[0]));
		fRec22[0] = fVec7[((IOTA - 1640) & 2047)];
		double fTemp2 = (((((((fRec8[0] + fRec10[0]) + fRec12[0]) + fRec14[0]) + fRec16[0]) + fRec18[0]) + fRec20[0]) + fRec22[0]);
		fVec8[(IOTA & 1023)] = (fTemp2 + (0.5 * fRec6[1]));
		fRec6[0] = fVec8[((IOTA - 579) & 1023)];
		double fRec7 = (fRec6[1] - fTemp2);
		fVec9[(IOTA & 511)] = (fRec7 + (0.5 * fRec4[1]));
		fRec4[0] = fVec9[((IOTA - 464) & 511)];
		double fRec5 = (fRec4[1] - fRec7);
		fVec10[(IOTA & 511)] = (fRec5 + (0.5 * fRec2[1]));
		fRec2[0] = fVec10[((IOTA - 364) & 511)];
		double fRec3 = (fRec2[1] - fRec5);
		fVec11[(IOTA & 255)] = (fRec3 + (0.5 * fRec0[1]));
		fRec0[0] = fVec11[((IOTA - 248) & 255)];
		double fRec1 = (fRec0[1] - fRec3);
		output0[i] = FAUSTFLOAT((fRec1 + (fSlow6 * fTemp0)));
		fRec9[1] = fRec9[0];
		IOTA = (IOTA + 1);
		fRec8[1] = fRec8[0];
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec15[1] = fRec15[0];
		fRec14[1] = fRec14[0];
		fRec17[1] = fRec17[0];
		fRec16[1] = fRec16[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec6[1] = fRec6[0];
		fRec4[1] = fRec4[0];
		fRec2[1] = fRec2[0];
		fRec0[1] = fRec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("freeverb.RoomSize",N_("Room Size"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.025000000000000001);
	reg.registerVar("freeverb.damp",N_("HF Damp"),"S","",&fVslider2, 0.5, 0.0, 1.0, 0.025000000000000001);
	reg.registerVar("freeverb.wet_dry",N_("Wet/Dry"),"S","",&fVslider0, 50.0, 0.0, 100.0, 1.0);
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
                        <property name=\"var_id\">freeverb.damp</property>\n\
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
                        <property name=\"var_id\">freeverb.RoomSize</property>\n\
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
                        <property name=\"var_id\">freeverb.wet_dry</property>\n\
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
                <property name=\"var_id\">freeverb.RoomSize</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Room Size</property>\n\
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
#define PARAM(p) ("freeverb" "." p)
// ----- freeverb
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("RoomSize"), _("RoomSize"));
b.closeBox();
b.openHorizontalBox("");
{
    b.openFrameBox("");
    b.closeBox();
    b.openFrameBox("");
    b.closeBox();
    b.openHorizontalTableBox("");
    {
	b.create_small_rackknobr(PARAM("RoomSize"), _("RoomSize"));
	b.create_small_rackknob(PARAM("damp"), _("damp"));
	b.create_small_rackknob(PARAM("wet_dry"), _("dry/wet"));
    }
    b.closeBox();
    b.openFrameBox("");
    b.closeBox();
    b.openFrameBox("");
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

} // end namespace freeverb
