// generated from file '../src/faust/stereoecho.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace stereoecho {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	int iVec0[2];
	FAUSTFLOAT fHslider0;
	float fConst0;
	float fConst1;
	float fRec1[2];
	float fRec2[2];
	FAUSTFLOAT fCheckbox0;
	int IOTA0;
	FAUSTFLOAT fHslider1;
	float fConst2;
	float fRec3[2];
	float fRec4[2];
	int iRec5[2];
	int iRec6[2];
	FAUSTFLOAT fVslider0;
	float *fRec0;
	FAUSTFLOAT fHslider2;
	float fRec8[2];
	float fRec9[2];
	int iRec10[2];
	int iRec11[2];
	FAUSTFLOAT fVslider1;
	float *fRec7;

	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void clear_state_f();
	int activate(bool start);
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int activate_static(bool start, PluginDef*);
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
	: PluginDef(),
	  fRec0(0),
	  fRec7(0),
	  mem_allocated(false) {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "stereoecho";
	name = N_("Stereo Echo");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Echo / Delay");       // category
	shortname = "";     // shortname
	mono_audio = 0;
	stereo_audio = compute_static;
	set_samplerate = init_static;
	activate_plugin = activate_static;
	register_params = register_params_static;
	load_ui = load_ui_f_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) iVec0[l0] = 0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec1[l1] = 0.0f;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec2[l2] = 0.0f;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec3[l3] = 0.0f;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec4[l4] = 0.0f;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) iRec5[l5] = 0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) iRec6[l6] = 0;
	for (int l7 = 0; l7 < 1048576; l7 = l7 + 1) fRec0[l7] = 0.0f;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec8[l8] = 0.0f;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec9[l9] = 0.0f;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) iRec10[l10] = 0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) iRec11[l11] = 0;
	for (int l12 = 0; l12 < 1048576; l12 = l12 + 1) fRec7[l12] = 0.0f;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
	fConst1 = 0.10471976f / fConst0;
	fConst2 = 6e+01f * fConst0;
	IOTA0 = 0;
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void Dsp::mem_alloc()
{
	if (!fRec0) fRec0 = new float[1048576];
	if (!fRec7) fRec7 = new float[1048576];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fRec0) { delete fRec0; fRec0 = 0; }
	if (fRec7) { delete fRec7; fRec7 = 0; }
}

int Dsp::activate(bool start)
{
	if (start) {
		if (!mem_allocated) {
			mem_alloc();
			clear_state_f();
		}
	} else if (mem_allocated) {
		mem_free();
	}
	return 0;
}

int Dsp::activate_static(bool start, PluginDef *p)
{
	return static_cast<Dsp*>(p)->activate(start);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	float fSlow0 = fConst1 * float(fHslider0);
	float fSlow1 = std::cos(fSlow0);
	float fSlow2 = std::sin(fSlow0);
	float fSlow3 = float(fCheckbox0);
	int iSlow4 = int(fConst2 / float(fHslider1)) + -1;
	float fSlow5 = 0.01f * float(fVslider0);
	int iSlow6 = int(fConst2 / float(fHslider2)) + -1;
	float fSlow7 = 0.01f * float(fVslider1);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		iVec0[0] = 1;
		fRec1[0] = fSlow2 * fRec2[1] + fSlow1 * fRec1[1];
		fRec2[0] = float(1 - iVec0[1]) + fSlow1 * fRec2[1] - fSlow2 * fRec1[1];
		float fTemp0 = fSlow3 * fRec1[0];
		float fTemp1 = ((fRec3[1] != 0.0f) ? (((fRec4[1] > 0.0f) & (fRec4[1] < 1.0f)) ? fRec3[1] : 0.0f) : (((fRec4[1] == 0.0f) & (iSlow4 != iRec5[1])) ? 0.0009765625f : (((fRec4[1] == 1.0f) & (iSlow4 != iRec6[1])) ? -0.0009765625f : 0.0f)));
		fRec3[0] = fTemp1;
		fRec4[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec4[1] + fTemp1));
		iRec5[0] = (((fRec4[1] >= 1.0f) & (iRec6[1] != iSlow4)) ? iSlow4 : iRec5[1]);
		iRec6[0] = (((fRec4[1] <= 0.0f) & (iRec5[1] != iSlow4)) ? iSlow4 : iRec6[1]);
		float fTemp2 = fRec0[(IOTA0 - (std::min<int>(524288, std::max<int>(0, iRec5[0])) + 1)) & 1048575];
		fRec0[IOTA0 & 1048575] = float(input0[i0]) + fSlow5 * (fTemp2 + fRec4[0] * (fRec0[(IOTA0 - (std::min<int>(524288, std::max<int>(0, iRec6[0])) + 1)) & 1048575] - fTemp2)) * (1.0f - fTemp0);
		output0[i0] = FAUSTFLOAT(fRec0[IOTA0 & 1048575]);
		float fTemp3 = ((fRec8[1] != 0.0f) ? (((fRec9[1] > 0.0f) & (fRec9[1] < 1.0f)) ? fRec8[1] : 0.0f) : (((fRec9[1] == 0.0f) & (iSlow6 != iRec10[1])) ? 0.0009765625f : (((fRec9[1] == 1.0f) & (iSlow6 != iRec11[1])) ? -0.0009765625f : 0.0f)));
		fRec8[0] = fTemp3;
		fRec9[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec9[1] + fTemp3));
		iRec10[0] = (((fRec9[1] >= 1.0f) & (iRec11[1] != iSlow6)) ? iSlow6 : iRec10[1]);
		iRec11[0] = (((fRec9[1] <= 0.0f) & (iRec10[1] != iSlow6)) ? iSlow6 : iRec11[1]);
		float fTemp4 = fRec7[(IOTA0 - (std::min<int>(524288, std::max<int>(0, iRec10[0])) + 1)) & 1048575];
		fRec7[IOTA0 & 1048575] = float(input1[i0]) + fSlow7 * (fTemp4 + fRec9[0] * (fRec7[(IOTA0 - (std::min<int>(524288, std::max<int>(0, iRec11[0])) + 1)) & 1048575] - fTemp4)) * (fTemp0 + 1.0f);
		output1[i0] = FAUSTFLOAT(fRec7[IOTA0 & 1048575]);
		iVec0[1] = iVec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		IOTA0 = IOTA0 + 1;
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		iRec5[1] = iRec5[0];
		iRec6[1] = iRec6[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		iRec10[1] = iRec10[0];
		iRec11[1] = iRec11[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	static const value_pair fCheckbox0_values[] = {{"linear"},{"pingpong"},{0}};
	reg.registerFloatVar("stereoecho.invert","","B","",&fCheckbox0, 0.0, 0.0, 1.0, 1.0, fCheckbox0_values);
	reg.registerFloatVar("stereoecho.lbpm",N_("Time L"),"S",N_("Echo in Beats per Minute"),&fHslider1, 1.2e+02f, 24.0f, 3.6e+02f, 1.0f, 0);
	reg.registerFloatVar("stereoecho.lfobpm",N_("LFO Freq"),"S",N_("LFO in Beats per Minute"),&fHslider0, 24.0f, 24.0f, 3.6e+02f, 1.0f, 0);
	reg.registerFloatVar("stereoecho.percent_l",N_("Release L"),"S","",&fVslider0, 0.0f, 0.0f, 1e+02f, 0.1f, 0);
	reg.registerFloatVar("stereoecho.percent_r",N_("Release R"),"S","",&fVslider1, 0.0f, 0.0f, 1e+02f, 0.1f, 0);
	reg.registerFloatVar("stereoecho.rbpm",N_("Time R"),"S",N_("Echo in Beats per Minute"),&fHslider2, 1.2e+02f, 24.0f, 3.6e+02f, 1.0f, 0);
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
                <property name=\"spacing\">2</property>\n\
                <child>\n\
                  <object class=\"GxSelector\" id=\"gxselector1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">stereoecho.invert</property>\n\
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
                        <property name=\"var_id\">stereoecho.percent_l</property>\n\
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
                        <property name=\"var_id\">stereoecho.lbpm</property>\n\
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
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <property name=\"spacing\">4</property>\n\
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
                        <property name=\"var_id\">stereoecho.lfobpm</property>\n\
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
                    <property name=\"position\">3</property>\n\
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
                        <property name=\"var_id\">stereoecho.percent_r</property>\n\
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
                    <property name=\"position\">4</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox6\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label5:rack_label\">\n\
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
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob5\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">stereoecho.rbpm</property>\n\
                        <property name=\"label_ref\">label5:rack_label</property>\n\
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
                    <property name=\"position\">5</property>\n\
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
#define PARAM(p) ("stereoecho" "." p)
// echo
b.openHorizontalhideBox("");
b.closeBox();
b.openHorizontalBox("");
{
    b.openVerticalBox("");
    {
	b.create_small_rackknob(PARAM("percent_l"), _("left %"));
	b.insertSpacer();
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.create_small_rackknob(PARAM("lbpm"), _("left time (bpm)"));
	b.insertSpacer();
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.create_small_rackknobr(PARAM("lfobpm"), _("LFO (bpm)"));
	b.insertSpacer();
	b.create_selector(PARAM("invert"), "invert");
	b.openFrameBox("");
	b.closeBox();
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.create_small_rackknob(PARAM("percent_r"), _("right %"));
	b.insertSpacer();
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.create_small_rackknob(PARAM("rbpm"), _("right time (bpm)"));
	b.insertSpacer();
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

} // end namespace stereoecho
