// generated from file '../src/plugins/vumeter_st.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace vumeter_st {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double 	fConst0;
	FAUSTFLOAT 	fslider0;
	double 	fRec4[2];
	double 	fRec0[2];
	int 	iRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT 	fbargraph1;
	double 	fRec5[2];
	int 	iRec6[2];
	double 	fRec7[2];
	FAUSTFLOAT 	fbargraph2;
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
	id = "vu_st";
	name = N_("Vumeter Stereo");
	groups = 0;
	description = "Stereo Vumeter"; // description (tooltip)
	category = N_("Misc");       // category
	shortname = "St-Vumeter";     // shortname
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
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) iRec6[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (1.0 / double(min(192000, max(1, fSamplingFreq))));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider0))));
	fbargraph1 = int(max(fbargraph2,fbargraph0));
	for (int i=0; i<count; i++) {
		fRec4[0] = ((0.999 * fRec4[1]) + fSlow0);
		double fTemp0 = ((double)input0[i] * fRec4[0]);
		double 	fRec3 = max(fConst0, fabs(fTemp0));
		int iTemp1 = int((iRec1[1] < 4096));
		fRec0[0] = ((iTemp1)?max(fRec0[1], fRec3):fRec3);
		iRec1[0] = ((iTemp1)?(1 + iRec1[1]):1);
		fRec2[0] = ((iTemp1)?fRec2[1]:fRec0[1]);
		fbargraph0 = fRec2[0];
		fbargraph1 = int(fbargraph0);
		output0[i] = (FAUSTFLOAT)fTemp0;
		double fTemp2 = ((double)input1[i] * fRec4[0]);
		double 	fRec8 = max(fConst0, fabs(fTemp2));
		int iTemp3 = int((iRec6[1] < 4096));
		fRec5[0] = ((iTemp3)?max(fRec5[1], fRec8):fRec8);
		iRec6[0] = ((iTemp3)?(1 + iRec6[1]):1);
		fRec7[0] = ((iTemp3)?fRec7[1]:fRec5[1]);
		fbargraph2 = fRec7[0];
		output1[i] = (FAUSTFLOAT)fTemp2;
		// post processing
		fRec7[1] = fRec7[0];
		iRec6[1] = iRec6[0];
		fRec5[1] = fRec5[0];
		fRec2[1] = fRec2[0];
		iRec1[1] = iRec1[0];
		fRec0[1] = fRec0[0];
		fRec4[1] = fRec4[0];
	}
}
		
void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("vu_st.gain","","S","",&fslider0, 0.0, -2e+01, 4.0, 0.1);
	reg.registerNonMidiFloatVar("vu_st.v1",&fbargraph0, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("vu_st.v2",&fbargraph2, false, true, -70.0, -70.0, 4.0, 0.00001);
	reg.registerNonMidiFloatVar("vu_st.v3",&fbargraph1, false, true, -70.0, -70.0, 4.0, 0.00001);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<interface>\n\
  <requires lib=\"gtk+\" version=\"2.20\"/>\n\
  <!-- interface-requires gxwidgets 0.0 -->\n\
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
                  <object class=\"GtkAlignment\" id=\"alignment1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"yscale\">0</property>\n\
                    <child>\n\
                      <object class=\"GtkHBox\" id=\"hbox3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"spacing\">8</property>\n\
                        <child>\n\
                          <object class=\"GtkVBox\" id=\"vbox3\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"spacing\">2</property>\n\
                            <child>\n\
                              <placeholder/>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GtkHBox\" id=\"hbox11\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"spacing\">1</property>\n\
                                <child>\n\
                                  <object class=\"GtkAlignment\" id=\"alignment2\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"top_padding\">1</property>\n\
                                    <property name=\"bottom_padding\">1</property>\n\
                                    <child>\n\
                                      <object class=\"GtkVBox\" id=\"vbox4\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <child>\n\
                                          <object class=\"GtkEventBox\" id=\"eventbox2\">\n\
                                            <property name=\"visible\">True</property>\n\
                                            <property name=\"can_focus\">False</property>\n\
                                            <property name=\"above_child\">True</property>\n\
                                            <child>\n\
                                              <object class=\"GxFastMeter\" id=\"gxfastmeter1:meterframe\">\n\
                                                <property name=\"width_request\">200</property>\n\
                                                <property name=\"visible\">True</property>\n\
                                                <property name=\"can_focus\">False</property>\n\
                                                <property name=\"hold\">120</property>\n\
                                                <property name=\"horiz\">True</property>\n\
                                                <property name=\"type\">1</property>\n\
                                                <property name=\"var_id\">vu_st.v1</property>\n\
                                              </object>\n\
                                            </child>\n\
                                          </object>\n\
                                          <packing>\n\
                                            <property name=\"expand\">True</property>\n\
                                            <property name=\"fill\">True</property>\n\
                                            <property name=\"position\">0</property>\n\
                                          </packing>\n\
                                        </child>\n\
                                        <child>\n\
                                          <object class=\"GtkEventBox\" id=\"eventbox3\">\n\
                                            <property name=\"visible\">True</property>\n\
                                            <property name=\"can_focus\">False</property>\n\
                                            <property name=\"above_child\">True</property>\n\
                                            <child>\n\
                                              <object class=\"GxFastMeter\" id=\"gxfastmeter2:meterframe\">\n\
                                                <property name=\"width_request\">200</property>\n\
                                                <property name=\"visible\">True</property>\n\
                                                <property name=\"can_focus\">False</property>\n\
                                                <property name=\"hold\">120</property>\n\
                                                <property name=\"horiz\">True</property>\n\
                                                <property name=\"type\">2</property>\n\
                                                <property name=\"var_id\">vu_st.v2</property>\n\
                                              </object>\n\
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
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GxSwitch\" id=\"gxfswitch1\">\n\
                                    <property name=\"width_request\">30</property>\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">True</property>\n\
                                    <property name=\"receives_default\">True</property>\n\
                                    <property name=\"var_id\">vu_st.v3</property>\n\
                                    <property name=\"base_name\">switch_mid</property>\n\
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
                          <packing>\n\
                            <property name=\"expand\">False</property>\n\
                            <property name=\"fill\">False</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <placeholder/>\n\
                        </child>\n\
                      </object>\n\
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
                      <object class=\"GxMidKnob\" id=\"gxbigknob1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">vu_st.gain</property>\n\
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
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"padding\">5</property>\n\
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
            <property name=\"spacing\">10</property>\n\
            <child>\n\
              <placeholder/>\n\
            </child>\n\
            <child>\n\
              <object class=\"GtkVBox\" id=\"vbox5\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"spacing\">2</property>\n\
                <child>\n\
                  <placeholder/>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkHBox\" id=\"hbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"spacing\">1</property>\n\
                    <child>\n\
                      <object class=\"GtkAlignment\" id=\"alignment3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"top_padding\">5</property>\n\
                        <property name=\"bottom_padding\">5</property>\n\
                        <child>\n\
                          <object class=\"GtkHBox\" id=\"hbox4\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <child>\n\
                              <object class=\"GtkVBox\" id=\"vbox6\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkEventBox\" id=\"eventbox1\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"above_child\">True</property>\n\
                                    <child>\n\
                                      <object class=\"GxFastMeter\" id=\"gxfastmeter3:meterframe\">\n\
                                        <property name=\"width_request\">200</property>\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"hold\">120</property>\n\
                                        <property name=\"dimen\">2</property>\n\
                                        <property name=\"horiz\">True</property>\n\
                                        <property name=\"type\">1</property>\n\
                                        <property name=\"var_id\">vu_st.v1</property>\n\
                                      </object>\n\
                                    </child>\n\
                                  </object>\n\
                                  <packing>\n\
                                    <property name=\"expand\">True</property>\n\
                                    <property name=\"fill\">True</property>\n\
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkEventBox\" id=\"eventbox4\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <property name=\"above_child\">True</property>\n\
                                    <child>\n\
                                      <object class=\"GxFastMeter\" id=\"gxfastmeter4:meterframe\">\n\
                                        <property name=\"width_request\">200</property>\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"hold\">120</property>\n\
                                        <property name=\"dimen\">2</property>\n\
                                        <property name=\"horiz\">True</property>\n\
                                        <property name=\"type\">2</property>\n\
                                        <property name=\"var_id\">vu_st.v2</property>\n\
                                      </object>\n\
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
                                <property name=\"position\">0</property>\n\
                              </packing>\n\
                            </child>\n\
                            <child>\n\
                              <object class=\"GxSwitch\" id=\"gxfswitch2\">\n\
                                <property name=\"width_request\">30</property>\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">True</property>\n\
                                <property name=\"receives_default\">True</property>\n\
                                <property name=\"var_id\">vu_st.v3</property>\n\
                                <property name=\"base_name\">switch_mid</property>\n\
                              </object>\n\
                              <packing>\n\
                                <property name=\"expand\">False</property>\n\
                                <property name=\"fill\">False</property>\n\
                                <property name=\"position\">1</property>\n\
                              </packing>\n\
                            </child>\n\
                          </object>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
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
              <packing>\n\
                <property name=\"expand\">False</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"position\">1</property>\n\
              </packing>\n\
            </child>\n\
            <child>\n\
              <placeholder/>\n\
            </child>\n\
            <child>\n\
              <placeholder/>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">False</property>\n\
            <property name=\"fill\">False</property>\n\
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

} // end namespace vumeter_st
} // end namespace pluginlib
