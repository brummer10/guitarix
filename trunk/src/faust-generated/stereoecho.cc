// generated from file '../src/faust/stereoecho.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace stereoecho {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT fVslider0;
	int iVec0[2];
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fRec1[2];
	float fRec2[2];
	int iRec3[2];
	int iRec4[2];
	FAUSTFLOAT fCheckbox0;
	float fConst2;
	FAUSTFLOAT fHslider1;
	float fRec5[2];
	float fRec6[2];
	int IOTA;
	float *fRec0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fHslider2;
	float fRec8[2];
	float fRec9[2];
	int iRec10[2];
	int iRec11[2];
	float *fRec7;

	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void clear_state_f();
	int activate(bool start);
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int activate_static(bool start, PluginDef*);
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) iVec0[l0] = 0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec1[l1] = 0.0f;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec2[l2] = 0.0f;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) iRec3[l3] = 0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) iRec4[l4] = 0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec5[l5] = 0.0f;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec6[l6] = 0.0f;
	for (int l7 = 0; (l7 < 1048576); l7 = (l7 + 1)) fRec0[l7] = 0.0f;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec8[l8] = 0.0f;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec9[l9] = 0.0f;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) iRec10[l10] = 0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) iRec11[l11] = 0;
	for (int l12 = 0; (l12 < 1048576); l12 = (l12 + 1)) fRec7[l12] = 0.0f;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSamplingFreq)));
	fConst1 = (60.0f * fConst0);
	fConst2 = (0.104719758f / fConst0);
	fVslider0 = FAUSTFLOAT(0.0f);
	fHslider0 = FAUSTFLOAT(120.0f);
	fCheckbox0 = FAUSTFLOAT(0.0f);
	fHslider1 = FAUSTFLOAT(24.0f);
	fVslider1 = FAUSTFLOAT(0.0f);
	fHslider2 = FAUSTFLOAT(120.0f);
			IOTA = 0;
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
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
	float fSlow0 = (0.00999999978f * float(fVslider0));
	int iSlow1 = (int((fConst1 / float(fHslider0))) + -1);
	float fSlow2 = float(fCheckbox0);
	float fSlow3 = (fConst2 * float(fHslider1));
	float fSlow4 = std::sin(fSlow3);
	float fSlow5 = std::cos(fSlow3);
	float fSlow6 = (0.00999999978f * float(fVslider1));
	int iSlow7 = (int((fConst1 / float(fHslider2))) + -1);
	for (int i = 0; (i < count); i = (i + 1)) {
		iVec0[0] = 1;
		float fTemp0 = ((fRec1[1] != 0.0f)?(((fRec2[1] > 0.0f) & (fRec2[1] < 1.0f))?fRec1[1]:0.0f):(((fRec2[1] == 0.0f) & (iSlow1 != iRec3[1]))?0.0009765625f:(((fRec2[1] == 1.0f) & (iSlow1 != iRec4[1]))?-0.0009765625f:0.0f)));
		fRec1[0] = fTemp0;
		fRec2[0] = std::max<float>(0.0f, std::min<float>(1.0f, (fRec2[1] + fTemp0)));
		iRec3[0] = (((fRec2[1] >= 1.0f) & (iRec4[1] != iSlow1))?iSlow1:iRec3[1]);
		iRec4[0] = (((fRec2[1] <= 0.0f) & (iRec3[1] != iSlow1))?iSlow1:iRec4[1]);
		fRec5[0] = ((fSlow4 * fRec6[1]) + (fSlow5 * fRec5[1]));
		fRec6[0] = ((float((1 - iVec0[1])) + (fSlow5 * fRec6[1])) - (fSlow4 * fRec5[1]));
		fRec0[(IOTA & 1048575)] = ((fSlow0 * ((((1.0f - fRec2[0]) * fRec0[((IOTA - (std::min<int>(524288, std::max<int>(0, iRec3[0])) + 1)) & 1048575)]) + (fRec2[0] * fRec0[((IOTA - (std::min<int>(524288, std::max<int>(0, iRec4[0])) + 1)) & 1048575)])) * (1.0f - (fSlow2 * fRec5[0])))) + float(input0[i]));
		output0[i] = FAUSTFLOAT(fRec0[((IOTA - 0) & 1048575)]);
		float fTemp1 = ((fRec8[1] != 0.0f)?(((fRec9[1] > 0.0f) & (fRec9[1] < 1.0f))?fRec8[1]:0.0f):(((fRec9[1] == 0.0f) & (iSlow7 != iRec10[1]))?0.0009765625f:(((fRec9[1] == 1.0f) & (iSlow7 != iRec11[1]))?-0.0009765625f:0.0f)));
		fRec8[0] = fTemp1;
		fRec9[0] = std::max<float>(0.0f, std::min<float>(1.0f, (fRec9[1] + fTemp1)));
		iRec10[0] = (((fRec9[1] >= 1.0f) & (iRec11[1] != iSlow7))?iSlow7:iRec10[1]);
		iRec11[0] = (((fRec9[1] <= 0.0f) & (iRec10[1] != iSlow7))?iSlow7:iRec11[1]);
		fRec7[(IOTA & 1048575)] = ((fSlow6 * ((((1.0f - fRec9[0]) * fRec7[((IOTA - (std::min<int>(524288, std::max<int>(0, iRec10[0])) + 1)) & 1048575)]) + (fRec9[0] * fRec7[((IOTA - (std::min<int>(524288, std::max<int>(0, iRec11[0])) + 1)) & 1048575)])) * (1.0f - (fSlow2 * (0.0f - fRec5[0]))))) + float(input1[i]));
		output1[i] = FAUSTFLOAT(fRec7[((IOTA - 0) & 1048575)]);
		iVec0[1] = iVec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		iRec3[1] = iRec3[0];
		iRec4[1] = iRec4[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		IOTA = (IOTA + 1);
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
	reg.registerEnumVar("stereoecho.invert","","B","",fCheckbox0_values,&fCheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("stereoecho.lbpm",N_("Time L"),"S",N_("Echo in Beats per Minute"),&fHslider0, 120.0f, 24.0f, 360.0f, 1.0f);
	reg.registerVar("stereoecho.lfobpm",N_("LFO Freq"),"S",N_("LFO in Beats per Minute"),&fHslider1, 24.0f, 24.0f, 360.0f, 1.0f);
	reg.registerVar("stereoecho.percent_l",N_("Release L"),"S","",&fVslider0, 0.0f, 0.0f, 100.0f, 0.100000001f);
	reg.registerVar("stereoecho.percent_r",N_("Release R"),"S","",&fVslider1, 0.0f, 0.0f, 100.0f, 0.100000001f);
	reg.registerVar("stereoecho.rbpm",N_("Time R"),"S",N_("Echo in Beats per Minute"),&fHslider2, 120.0f, 24.0f, 360.0f, 1.0f);
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
