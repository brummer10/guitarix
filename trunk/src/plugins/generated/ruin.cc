// generated from file '../src/plugins/ruin.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"
#include <string.h>

namespace pluginlib {
namespace ruin {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int sample_rate;
	int fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	FAUSTFLOAT fVslider0;
	double fRec10[2];
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fRec9[3];
	double fVec0[2];
	double fRec8[2];
	double fRec7[3];
	double fRec6[2];
	double fRec5[2];
	double fRec4[2];
	double fRec3[3];
	double fRec2[2];
	double fRec1[2];
	double fConst13;
	double fConst14;
	FAUSTFLOAT fVslider1;
	double fRec11[2];
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
	double fRec0[4];

	FAUSTFLOAT fsliderdw0;
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
	id = "ruin";
	name = N_("Ruiner");
	groups = 0;
	description = N_("Devi Ever Dark Boost"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("Ruiner");     // shortname
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec10[l0] = 0.0;
	for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) fRec9[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fVec0[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec8[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec7[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec6[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec5[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec4[l7] = 0.0;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec3[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec2[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec1[l10] = 0.0;
	for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) fRec11[l11] = 0.0;
	for (int l12 = 0; (l12 < 4); l12 = (l12 + 1)) fRec0[l12] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int RsamplingFreq)
{
	sample_rate = 96000;
	smp.setup(RsamplingFreq, sample_rate);
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	fConst2 = (3.1415926535897931 / fConst0);
	fConst3 = (1.0 / (fConst2 + 1.0));
	fConst4 = (1.0 - fConst2);
	fConst5 = (3.6874037647271903e-05 * fConst0);
	fConst6 = (0.0 - fConst5);
	fConst7 = (2.5021125853332702e-10 * fConst0);
	fConst8 = (fConst7 + -1.4184134839295499e-07);
	fConst9 = (3.23341143501596e-10 * fConst0);
	fConst10 = (fConst9 + -1.8384980583165701e-06);
	fConst11 = (fConst7 + 1.4184134839295499e-07);
	fConst12 = (fConst9 + 1.8384980583165701e-06);
	fConst13 = (2.61465064881748e-14 * fConst0);
	fConst14 = (fConst0 * ((fConst0 * (-5.3758251484096497e-12 - fConst13)) + 8.1227954104630203e-10));
	fConst15 = (2.56034039795183e-15 * fConst0);
	fConst16 = ((fConst0 * (-5.2812234095761103e-13 - fConst15)) + 7.9995717349203405e-11);
	fConst17 = (2.5862024221735698e-15 * fConst0);
	fConst18 = ((fConst0 * (fConst17 + 4.4637938742608599e-13)) + -5.7583260273739602e-11);
	fConst19 = (fConst0 * ((fConst0 * (fConst13 + -5.3758251484096497e-12)) + -8.1227954104630203e-10));
	fConst20 = ((fConst0 * (fConst15 + -5.2812234095761103e-13)) + -7.9995717349203405e-11);
	fConst21 = ((fConst0 * (4.4637938742608599e-13 - fConst17)) + 5.7583260273739602e-11);
	fConst22 = (8.7155021627249292e-15 * fConst0);
	fConst23 = (fConst0 * ((fConst0 * (5.3758251484096497e-12 - fConst22)) + -8.1227954104630203e-10));
	fConst24 = (8.5344679931727804e-16 * fConst0);
	fConst25 = ((fConst0 * (5.2812234095761103e-13 - fConst24)) + -7.9995717349203405e-11);
	fConst26 = (8.6206747405785601e-16 * fConst0);
	fConst27 = ((fConst0 * (fConst26 + -4.4637938742608599e-13)) + 5.7583260273739602e-11);
	fConst28 = (fConst0 * ((fConst0 * (fConst22 + 5.3758251484096497e-12)) + 8.1227954104630203e-10));
	fConst29 = ((fConst0 * (fConst24 + 5.2812234095761103e-13)) + 7.9995717349203405e-11);
	fConst30 = ((fConst0 * (-4.4637938742608599e-13 - fConst26)) + -5.7583260273739602e-11);
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlowdw0 = (0.01 * fsliderdw0);
	double 	fSlowdw1 = (1 - fSlowdw0);
	FAUSTFLOAT 	dryinput[count];
	memcpy(&dryinput, input0, count * sizeof(float));

	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double fSlow0 = (0.0070000000000000062 * (1.0 - double(fVslider0)));
	double fSlow1 = (0.0070000000000000062 * double(fVslider1));
	for (int i = 0; (i < ReCount); i = (i + 1)) {
		fRec10[0] = (fSlow0 + (0.99299999999999999 * fRec10[1]));
		double fTemp0 = ((fConst0 * (fConst11 + (fConst12 * fRec10[0]))) + 9.1924902915828404e-05);
		fRec9[0] = (double(buf[i]) - (((fRec9[1] * ((fConst1 * ((0.0 - (6.4668228700319304e-10 * fRec10[0])) + -5.0042251706665405e-10)) + 0.000183849805831657)) + (fRec9[2] * ((fConst0 * (fConst8 + (fConst10 * fRec10[0]))) + 9.1924902915828404e-05))) / fTemp0));
		double fTemp1 = (((fConst6 * fRec9[0]) + (fConst5 * fRec9[2])) / fTemp0);
		fVec0[0] = fTemp1;
		fRec8[0] = ((0.93028479253239138 * (fTemp1 + fVec0[1])) - (0.86056958506478287 * fRec8[1]));
		fRec7[0] = (fRec8[0] - ((1.8405051250752198 * fRec7[1]) + (0.86129424393186271 * fRec7[2])));
		double fTemp2 = ((1.8508996845035413 * fRec7[1]) + (0.92544984225177063 * (fRec7[0] + fRec7[2])));
		double fTemp3 = double(Ftrany(int(TRANY_TABLE_SVEL34_68k), double(((fTemp2 + (2700.0 * (fTemp2 / (double(Rtrany(int(TRANY_TABLE_SVEL34_68k), double(fRec6[1]))) + 100000.0)))) + -25.922163000000001))));
		fRec6[0] = ((fTemp3 + (0.0096008011111111107 * (double(Rtrany(int(TRANY_TABLE_SVEL34_68k), double(fTemp3))) + 100000.0))) + -250.0);
		fRec5[0] = (fConst3 * ((fConst4 * fRec5[1]) + (0.025000000000000001 * (fRec6[0] - fRec6[1]))));
		fRec4[0] = ((0.93028479253239138 * (fRec5[0] + fRec5[1])) - (0.86056958506478287 * fRec4[1]));
		fRec3[0] = (fRec4[0] - ((1.8405051250752198 * fRec3[1]) + (0.86129424393186271 * fRec3[2])));
		double fTemp4 = ((1.8508996845035413 * fRec3[1]) + (0.92544984225177063 * (fRec3[0] + fRec3[2])));
		double fTemp5 = double(Ftrany(int(TRANY_TABLE_SVEL34_68k), double(((fTemp4 + (2700.0 * (fTemp4 / (double(Rtrany(int(TRANY_TABLE_SVEL34_68k), double(fRec2[1]))) + 100000.0)))) + -25.922163000000001))));
		fRec2[0] = ((fTemp5 + (0.0096008011111111107 * (double(Rtrany(int(TRANY_TABLE_SVEL34_68k), double(fTemp5))) + 100000.0))) + -250.0);
		fRec1[0] = (fConst3 * ((fConst4 * fRec1[1]) + (0.025000000000000001 * (fRec2[0] - fRec2[1]))));
		fRec11[0] = (fSlow1 + (0.99299999999999999 * fRec11[1]));
		double fTemp6 = (fConst28 + ((fRec11[0] * ((fConst0 * (fConst29 + (fConst30 * fRec11[0]))) + 2.8791630136869799e-09)) + 2.8820421767006702e-08));
		fRec0[0] = (fRec1[0] - ((((fRec0[1] * (fConst14 + ((fRec11[0] * ((fConst0 * (fConst16 + (fConst18 * fRec11[0]))) + 8.6374890410609398e-09)) + 8.6461265301020002e-08))) + (fRec0[2] * (fConst19 + ((fRec11[0] * ((fConst0 * (fConst20 + (fConst21 * fRec11[0]))) + 8.6374890410609398e-09)) + 8.6461265301020002e-08)))) + (fRec0[3] * (fConst23 + ((fRec11[0] * ((fConst0 * (fConst25 + (fConst27 * fRec11[0]))) + 2.8791630136869799e-09)) + 2.8820421767006702e-08)))) / fTemp6));
		double fTemp7 = (1.11891193819806e-10 * fRec11[0]);
		double fTemp8 = ((0.0 - fTemp7) + -1.1189119381980601e-12);
		double fTemp9 = (fTemp7 + 1.1189119381980601e-12);
		buf[i] = FAUSTFLOAT((fConst1 * (((((fRec0[0] * fTemp8) + (fRec0[1] * fTemp9)) + (fRec0[2] * fTemp9)) + (fRec0[3] * fTemp8)) / fTemp6)));
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fVec0[1] = fVec0[0];
		fRec8[1] = fRec8[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec11[1] = fRec11[0];
		for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
			fRec0[j0] = fRec0[(j0 - 1)];
		}
	}
	smp.down(buf, output0);
	for (int i=0; i<count; i++) {
		output0[i] = ((fSlowdw1 * (double)dryinput[i]) + (fSlowdw0 * (double)output0[i]));
	}

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("ruin.wet_dry",N_("Dry/Wet"),"S",N_("percentage of processed signal in output signal"),&fsliderdw0, 1e+02, 0.0, 1e+02, 1.0, 0);
	reg.registerFloatVar("ruin.Intensity",N_("Intensity"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("ruin.Level",N_("Level"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
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
                        <property name=\"var_id\">ruin.Intensity</property>\n\
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
                        <property name=\"var_id\">ruin.Level</property>\n\
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
                        <property name=\"var_id\">ruin.wet_dry</property>\n\
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
                <property name=\"var_id\">ruin.Intensity</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Intensity</property>\n\
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
#define PARAM(p) ("ruin" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Intensity"), "Intensity");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Level"), "Level");

    b.create_small_rackknobr(PARAM("Intensity"), "Intensity");
    b.create_small_rackknobr(PARAM("wet_dry"), "dry/wet");
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

} // end namespace ruin
} // end namespace pluginlib
