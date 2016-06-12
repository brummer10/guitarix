// generated from file '../src/faust/low_high_pass.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace low_high_pass {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iVec0[2];
	double 	fRec2[2];
	double 	fVec1[2];
	FAUSTFLOAT 	fentry0;
	double 	fConst0;
	double 	fRec1[2];
	FAUSTFLOAT 	fentry1;
	double 	fRec0[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	double 	fVec2[2];
	double 	fRec6[2];
	double 	fVec3[2];
	double 	fRec5[2];
	double 	fRec4[3];
	double 	fRec3[3];
	FAUSTFLOAT 	fcheckbox1;
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (3.141592653589793 / double(min(192000, max(1, fSamplingFreq))));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (1.0 / tan((fConst0 * double(fentry0))));
	double 	fSlow1 = (1 + fSlow0);
	double 	fSlow2 = (1.0 / fSlow1);
	double 	fSlow3 = (0 - ((1 - fSlow0) / fSlow1));
	double 	fSlow4 = (1.0 / tan((fConst0 * double(fentry1))));
	double 	fSlow5 = (0 - fSlow4);
	double 	fSlow6 = (1 + fSlow4);
	double 	fSlow7 = (1.0 / fSlow6);
	double 	fSlow8 = (0 - ((1 - fSlow4) / fSlow6));
	int 	iSlow9 = int(double(fcheckbox0));
	double 	fSlow10 = tan((fConst0 * double(fslider0)));
	double 	fSlow11 = (2 * (1 - (1.0 / faustpower<2>(fSlow10))));
	double 	fSlow12 = (1.0 / fSlow10);
	double 	fSlow13 = (1 + ((fSlow12 - 0.7653668647301795) / fSlow10));
	double 	fSlow14 = (1.0 / (1 + ((0.7653668647301795 + fSlow12) / fSlow10)));
	double 	fSlow15 = (1 + ((fSlow12 - 1.8477590650225735) / fSlow10));
	double 	fSlow16 = (1.0 / (1 + ((1.8477590650225735 + fSlow12) / fSlow10)));
	double 	fSlow17 = (fConst0 * double(fslider1));
	double 	fSlow18 = (1.0 / (1 + fSlow17));
	double 	fSlow19 = (1 - fSlow17);
	int 	iSlow20 = int(double(fcheckbox1));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		iVec0[0] = 1;
		fRec2[0] = ((1e-20 * (1 - iVec0[1])) - fRec2[1]);
		double fTemp1 = (fTemp0 + fRec2[0]);
		fVec1[0] = fTemp1;
		fRec1[0] = ((fSlow3 * fRec1[1]) + (fSlow2 * (fVec1[0] + fVec1[1])));
		fRec0[0] = ((fSlow8 * fRec0[1]) + (fSlow7 * ((fSlow4 * fRec1[0]) + (fSlow5 * fRec1[1]))));
		double fTemp2 = ((iSlow9)?fRec0[0]:fTemp0);
		double fTemp3 = (fRec2[0] + fTemp2);
		fVec2[0] = (fSlow18 * fTemp3);
		fRec6[0] = ((fSlow18 * (fTemp3 + (fSlow19 * fRec6[1]))) - fVec2[1]);
		fVec3[0] = (fSlow18 * fRec6[0]);
		fRec5[0] = ((fSlow18 * (fRec6[0] + (fSlow19 * fRec5[1]))) - fVec3[1]);
		fRec4[0] = (fRec5[0] - (fSlow16 * ((fSlow15 * fRec4[2]) + (fSlow11 * fRec4[1]))));
		fRec3[0] = ((fSlow16 * (fRec4[2] + (fRec4[0] + (2 * fRec4[1])))) - (fSlow14 * ((fSlow13 * fRec3[2]) + (fSlow11 * fRec3[1]))));
		output0[i] = (FAUSTFLOAT)((iSlow20)?(fSlow14 * (fRec3[2] + (fRec3[0] + (2 * fRec3[1])))):fTemp2);
		// post processing
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec3[1] = fVec3[0];
		fRec6[1] = fRec6[0];
		fVec2[1] = fVec2[0];
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fVec1[1] = fVec1[0];
		fRec2[1] = fRec2[0];
		iVec0[1] = iVec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("low_high_pass.lhc.high_freq",N_("Highcut"),"S",N_("high-freq cutoff Hz"),&fslider0, 5e+03, 1e+03, 1.2e+04, 1e+01);
	reg.registerVar("low_high_pass.lhc.low_freq",N_("Lowcut"),"S",N_("low-freq cutoff Hz"),&fslider1, 1.3e+02, 2e+01, 1e+03, 1e+01);
	reg.registerVar("low_high_pass.lhc.on_off",N_("low highcutoff"),"B","",&fcheckbox1, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("low_high_pass.lhp.high_freq",N_("Highpass"),"S","",&fentry1, 1.3e+02, 2e+01, 7.04e+03, 1e+01);
	reg.registerVar("low_high_pass.lhp.low_freq",N_("Lowpass"),"S","",&fentry0, 5e+03, 2e+01, 1.2e+04, 1e+01);
	reg.registerVar("low_high_pass.lhp.on_off",N_("low highpass"),"B","",&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
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
                  <object class=\"GtkHBox\" id=\"hbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"spacing\">4</property>\n\
                    <child>\n\
                      <object class=\"GtkVBox\" id=\"vbox6\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
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
                            <property name=\"use_action_appearance\">False</property>\n\
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
                  <object class=\"GtkHBox\" id=\"hbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"spacing\">4</property>\n\
                    <child>\n\
                      <object class=\"GtkVBox\" id=\"vbox4\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
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
                      <object class=\"GtkVBox\" id=\"vbox5\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
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
                      <object class=\"GtkVBox\" id=\"vbox7\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
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
                            <property name=\"use_action_appearance\">False</property>\n\
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
          <object class=\"GtkHBox\" id=\"minibox\">\n\
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
