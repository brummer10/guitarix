// generated from file '../src/plugins/astrofuzz.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace astrofuzz {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	FAUSTFLOAT fVslider0;
	double fRec8[2];
	FAUSTFLOAT fVslider1;
	double fRec9[2];
	double fConst5;
	double fConst6;
	FAUSTFLOAT fVslider2;
	double fRec11[2];
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fRec10[4];
	double fVec0[2];
	double fRec7[2];
	double fRec6[3];
	double fRec5[2];
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fRec1[2];
	double fRec0[2];

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
	id = "astrofuzz";
	name = N_("Astrotone Fuzz");
	groups = 0;
	description = N_("Astrotone Fuzz"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("Astrotone");     // shortname
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec8[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec9[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec11[l2] = 0.0;
	for (int l3 = 0; (l3 < 4); l3 = (l3 + 1)) fRec10[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fVec0[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec7[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec6[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec5[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec4[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec3[l9] = 0.0;
	for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) fRec2[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec1[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec0[l12] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (3.1415926535897931 / fConst0);
	fConst2 = (1.0 / (fConst1 + 1.0));
	fConst3 = (1.0 - fConst1);
	fConst4 = (0.93028479253239138 * mydsp_faustpower3_f(fConst0));
	fConst5 = (1.13829289992073e-14 * fConst0);
	fConst6 = ((fConst0 * ((fConst0 * (fConst5 + 7.9621889709708099e-12)) + -4.4420526198051403e-09)) + -8.2850461111831503e-07);
	fConst7 = (1.34787020665425e-14 * fConst0);
	fConst8 = ((fConst0 * (-1.3431684996488399e-11 - fConst7)) + 9.4240765996914601e-09);
	fConst9 = (1.22956259277156e-13 * fConst0);
	fConst10 = ((fConst0 * (-8.3125217181190294e-11 - fConst9)) + 5.6592388303455001e-09);
	fConst11 = ((fConst0 * (fConst9 + 8.3125217181190294e-11)) + -5.6592388303455001e-09);
	fConst12 = (1.0394582988332501e-13 * fConst0);
	fConst13 = ((fConst0 * (-3.9250201572998802e-11 - fConst12)) + 2.59598111483739e-09);
	fConst14 = ((fConst0 * (fConst12 + 3.9250201572998802e-11)) + -2.59598111483739e-09);
	fConst15 = ((fConst0 * ((fConst0 * (7.9621889709708099e-12 - fConst5)) + 4.4420526198051403e-09)) + -8.2850461111831503e-07);
	fConst16 = ((fConst0 * (fConst7 + -1.3431684996488399e-11)) + -9.4240765996914601e-09);
	fConst17 = ((fConst0 * (fConst9 + -8.3125217181190294e-11)) + -5.6592388303455001e-09);
	fConst18 = ((fConst0 * (8.3125217181190294e-11 - fConst9)) + 5.6592388303455001e-09);
	fConst19 = ((fConst0 * (fConst12 + -3.9250201572998802e-11)) + -2.59598111483739e-09);
	fConst20 = ((fConst0 * (3.9250201572998802e-11 - fConst12)) + 2.59598111483739e-09);
	fConst21 = (3.7943096664024298e-15 * fConst0);
	fConst22 = ((fConst0 * ((fConst0 * (fConst21 + -7.9621889709708099e-12)) + 4.4420526198051403e-09)) + -2.7616820370610499e-07);
	fConst23 = (4.49290068884749e-15 * fConst0);
	fConst24 = ((fConst0 * (1.3431684996488399e-11 - fConst23)) + -9.4240765996914601e-09);
	fConst25 = (4.0985419759051898e-14 * fConst0);
	fConst26 = ((fConst0 * (8.3125217181190294e-11 - fConst25)) + -5.6592388303455001e-09);
	fConst27 = ((fConst0 * (fConst25 + -8.3125217181190294e-11)) + 5.6592388303455001e-09);
	fConst28 = (3.4648609961108198e-14 * fConst0);
	fConst29 = ((fConst0 * (3.9250201572998802e-11 - fConst28)) + -2.59598111483739e-09);
	fConst30 = ((fConst0 * (fConst28 + -3.9250201572998802e-11)) + 2.59598111483739e-09);
	fConst31 = ((fConst0 * ((fConst0 * (-7.9621889709708099e-12 - fConst21)) + -4.4420526198051403e-09)) + -2.7616820370610499e-07);
	fConst32 = ((fConst0 * (fConst23 + 1.3431684996488399e-11)) + 9.4240765996914601e-09);
	fConst33 = ((fConst0 * (fConst25 + 8.3125217181190294e-11)) + 5.6592388303455001e-09);
	fConst34 = ((fConst0 * (-8.3125217181190294e-11 - fConst25)) + -5.6592388303455001e-09);
	fConst35 = ((fConst0 * (fConst28 + 3.9250201572998802e-11)) + 2.59598111483739e-09);
	fConst36 = ((fConst0 * (-3.9250201572998802e-11 - fConst28)) + -2.59598111483739e-09);
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = (0.0070000000000000062 * double(fVslider0));
	double fSlow1 = (0.0070000000000000062 * double(fVslider1));
	double fSlow2 = (0.0070000000000000062 * double(fVslider2));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec8[0] = (fSlow0 + (0.99299999999999999 * fRec8[1]));
		fRec9[0] = (fSlow1 + (0.99299999999999999 * fRec9[1]));
		fRec11[0] = (fSlow2 + (0.99299999999999999 * fRec11[1]));
		double fTemp0 = (((fConst31 * fRec11[0]) + (fConst0 * (fConst32 + (fRec8[0] * (fConst33 + ((fRec8[0] * (fConst34 + (fConst35 * fRec11[0]))) + (fConst36 * fRec11[0]))))))) + 6.0204668407930903e-07);
		fRec10[0] = (double(input0[i]) - ((((fRec10[1] * (((fConst6 * fRec11[0]) + (fConst0 * (fConst8 + (fRec8[0] * (fConst10 + ((fRec8[0] * (fConst11 + (fConst13 * fRec11[0]))) + (fConst14 * fRec11[0]))))))) + 1.80614005223793e-06)) + (fRec10[2] * (((fConst15 * fRec11[0]) + (fConst0 * (fConst16 + (fRec8[0] * (fConst17 + ((fRec8[0] * (fConst18 + (fConst19 * fRec11[0]))) + (fConst20 * fRec11[0]))))))) + 1.80614005223793e-06))) + (fRec10[3] * (((fConst22 * fRec11[0]) + (fConst0 * (fConst24 + (fRec8[0] * (fConst26 + ((fRec8[0] * (fConst27 + (fConst29 * fRec11[0]))) + (fConst30 * fRec11[0]))))))) + 6.0204668407930903e-07))) / fTemp0));
		double fTemp1 = (1.0049951599645899e-12 * fRec11[0]);
		double fTemp2 = (3.0149854798937799e-12 * fRec11[0]);
		double fTemp3 = (((fRec8[0] * fRec9[0]) * ((((fRec10[0] * (fTemp1 + -1.18589428875822e-12)) + (fRec10[1] * ((0.0 - fTemp2) + 3.5576828662746601e-12))) + (fRec10[2] * (fTemp2 + -3.5576828662746601e-12))) + (fRec10[3] * ((0.0 - fTemp1) + 1.18589428875822e-12)))) / fTemp0);
		fVec0[0] = fTemp3;
		fRec7[0] = ((fConst4 * (fTemp3 + fVec0[1])) - (0.86056958506478287 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.86129424393186271 * fRec6[2])));
		double fTemp4 = ((1.8508996845035413 * fRec6[1]) + (0.92544984225177063 * (fRec6[0] + fRec6[2])));
		double fTemp5 = double(Ftrany(int(TRANY_TABLE_7199P_68k), double(((fTemp4 + (2700.0 * (fTemp4 / (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fRec5[1]))) + 100000.0)))) + -3.5719810000000001))));
		fRec5[0] = ((fTemp5 + (0.001322955925925926 * (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fTemp5))) + 100000.0))) + -250.0);
		fRec4[0] = (fConst2 * ((fConst3 * fRec4[1]) + (0.025000000000000001 * (fRec5[0] - fRec5[1]))));
		fRec3[0] = ((0.93028479253239138 * (fRec4[0] + fRec4[1])) - (0.86056958506478287 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.86129424393186271 * fRec2[2])));
		double fTemp6 = ((1.8508996845035413 * fRec2[1]) + (0.92544984225177063 * (fRec2[0] + fRec2[2])));
		double fTemp7 = double(Ftrany(int(TRANY_TABLE_7199P_68k), double(((fTemp6 + (2700.0 * (fTemp6 / (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fRec1[1]))) + 100000.0)))) + -3.5719810000000001))));
		fRec1[0] = ((fTemp7 + (0.001322955925925926 * (double(Rtrany(int(TRANY_TABLE_7199P_68k), double(fTemp7))) + 100000.0))) + -250.0);
		fRec0[0] = (fConst2 * ((fConst3 * fRec0[1]) + (0.025000000000000001 * (fRec1[0] - fRec1[1]))));
		output0[i] = FAUSTFLOAT(fRec0[0]);
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec11[1] = fRec11[0];
		for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
			fRec10[j0] = fRec10[(j0 - 1)];
		}
		fVec0[1] = fVec0[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("astrofuzz.Attack",N_("Attack"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("astrofuzz.Tone",N_("Tone"),"S","",&fVslider2, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("astrofuzz.Volume",N_("Volume"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
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
                        <property name=\"var_id\">astrofuzz.Attack</property>\n\
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
                        <property name=\"var_id\">astrofuzz.Volume</property>\n\
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
                        <property name=\"var_id\">astrofuzz.Tone</property>\n\
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
                <property name=\"var_id\">astrofuzz.Volume</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Volume</property>\n\
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
#define PARAM(p) ("astrofuzz" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Tone"), "Tone");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Tone"), "Tone");

    b.create_small_rackknobr(PARAM("Volume"), "Volume");

    b.create_small_rackknobr(PARAM("Attack"), "Attack");
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

} // end namespace astrofuzz
} // end namespace pluginlib
