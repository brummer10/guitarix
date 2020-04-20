// generated from file '../src/faust/fuzzface.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


#include "clipping.h"

namespace fuzzface {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fVslider0;
	double fRec1[2];
	double fConst4;
	double fConst5;
	double fConst6;
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
	double fRec0[6];
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	FAUSTFLOAT fVslider1;
	double fRec2[2];
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;


	int samplingFreq;
	gx_resample::FixedRateResampler smpCl;

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
	id = "fuzzface";
	name = N_("Fuzz Face");
	groups = 0;
	description = N_("J Hendrix Fuzz Face simulation"); // description (tooltip)
	category = N_("Fuzz");       // category
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec1[l0] = 0.0;
	for (int l1 = 0; (l1 < 6); l1 = (l1 + 1)) fRec0[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec2[l2] = 0.0;


}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	fConst2 = (1.1969573227426499e-21 * fConst0);
	fConst3 = (((((-1.9904265351089599e-15 - fConst2) * fConst0) + 1.8361560410497099e-13) * fConst0) + 1.59369187419145e-10);
	fConst4 = (1.86646037645036e-28 * fConst0);
	fConst5 = (((((((-3.0492983317998401e-20 - fConst4) * fConst0) + -2.91602352831988e-14) * fConst0) + 2.2963696637004201e-11) * fConst0) + 3.2234731636248798e-09);
	fConst6 = (((((((fConst4 + 3.1689940386223803e-20) * fConst0) + 3.1150636903991498e-14) * fConst0) + -2.30719916990074e-11) * fConst0) + -3.22479494130986e-09);
	fConst7 = (7.97971548495099e-22 * fConst0);
	fConst8 = (((((fConst7 + -3.9808530702179302e-15) * fConst0) + -3.6723120820994199e-13) * fConst0) + 1.06246124946097e-10);
	fConst9 = (3.7329207529007299e-28 * fConst0);
	fConst10 = (((((((fConst9 + 2.0328655545332299e-20) * fConst0) + -5.83204705663976e-14) * fConst0) + -4.5927393274008403e-11) * fConst0) + 2.14898210908325e-09);
	fConst11 = (((((((-2.1126626924149201e-20 - fConst9) * fConst0) + 6.2301273807982996e-14) * fConst0) + 4.6143983398014799e-11) * fConst0) + -2.1498632942065702e-09);
	fConst12 = (((((fConst7 + 3.9808530702179302e-15) * fConst0) + -3.6723120820994199e-13) * fConst0) + -1.06246124946097e-10);
	fConst13 = (((((((2.0328655545332299e-20 - fConst9) * fConst0) + 5.83204705663976e-14) * fConst0) + -4.5927393274008403e-11) * fConst0) + -2.14898210908325e-09);
	fConst14 = (((((((fConst9 + -2.1126626924149201e-20) * fConst0) + -6.2301273807982996e-14) * fConst0) + 4.6143983398014799e-11) * fConst0) + 2.1498632942065702e-09);
	fConst15 = (((((1.9904265351089599e-15 - fConst2) * fConst0) + 1.8361560410497099e-13) * fConst0) + -1.59369187419145e-10);
	fConst16 = (((((((fConst4 + -3.0492983317998401e-20) * fConst0) + 2.91602352831988e-14) * fConst0) + 2.2963696637004201e-11) * fConst0) + -3.2234731636248798e-09);
	fConst17 = (((((((3.1689940386223803e-20 - fConst4) * fConst0) + -3.1150636903991498e-14) * fConst0) + -2.30719916990074e-11) * fConst0) + 3.22479494130986e-09);
	fConst18 = (3.9898577424754898e-22 * fConst0);
	fConst19 = (((((fConst18 + -1.9904265351089599e-15) * fConst0) + 1.8361560410497099e-13) * fConst0) + -5.3123062473048297e-11);
	fConst20 = (3.7329207529007301e-29 * fConst0);
	fConst21 = (((((((1.0164327772666201e-20 - fConst20) * fConst0) + -2.91602352831988e-14) * fConst0) + 2.2963696637004201e-11) * fConst0) + -1.07449105454163e-09);
	fConst22 = (((((((fConst20 + -1.05633134620746e-20) * fConst0) + 3.1150636903991498e-14) * fConst0) + -2.30719916990074e-11) * fConst0) + 1.07493164710329e-09);
	fConst23 = (((((fConst18 + 1.9904265351089599e-15) * fConst0) + 1.8361560410497099e-13) * fConst0) + 5.3123062473048297e-11);
	fConst24 = (((((((fConst20 + 1.0164327772666201e-20) * fConst0) + 2.91602352831988e-14) * fConst0) + 2.2963696637004201e-11) * fConst0) + 1.07449105454163e-09);
	fConst25 = (((((((-1.05633134620746e-20 - fConst20) * fConst0) + -3.1150636903991498e-14) * fConst0) + -2.30719916990074e-11) * fConst0) + -1.07493164710329e-09);
	fConst26 = (5.0573033918522197e-13 * fConst0);
	fConst27 = (fConst26 + 1.1616221542226101e-12);
	fConst28 = (4.7699151349934602e-20 * fConst0);
	fConst29 = (fConst28 + -5.0034671369817102e-13);
	fConst30 = (-5.3835170798891596e-15 - fConst28);
	fConst31 = (fConst28 + 5.3835170798891596e-15);
	fConst32 = (5.0034671369817102e-13 - fConst28);
	fConst33 = (-1.1616221542226101e-12 - fConst26);
	fConst34 = (1.1616221542226101e-12 - fConst26);
	fConst35 = (1.4309745404980399e-19 * fConst0);
	fConst36 = (5.0034671369817102e-13 - fConst35);
	fConst37 = (fConst35 + 5.3835170798891596e-15);
	fConst38 = (-5.3835170798891596e-15 - fConst35);
	fConst39 = (fConst35 + -5.0034671369817102e-13);
	fConst40 = (fConst26 + -1.1616221542226101e-12);
	fConst41 = (1.0114606783704401e-12 * fConst0);
	fConst42 = (-2.3232443084452202e-12 - fConst41);
	fConst43 = (9.5398302699869301e-20 * fConst0);
	fConst44 = (fConst43 + 1.00069342739634e-12);
	fConst45 = (1.07670341597783e-14 - fConst43);
	fConst46 = (fConst43 + -1.07670341597783e-14);
	fConst47 = (-1.00069342739634e-12 - fConst43);
	fConst48 = (fConst41 + 2.3232443084452202e-12);
	fConst49 = (fConst41 + -2.3232443084452202e-12);
	fConst50 = (fConst43 + -1.00069342739634e-12);
	fConst51 = (-1.07670341597783e-14 - fConst43);
	fConst52 = (fConst43 + 1.07670341597783e-14);
	fConst53 = (1.00069342739634e-12 - fConst43);
	fConst54 = (2.3232443084452202e-12 - fConst41);
	fConst55 = (-5.0034671369817102e-13 - fConst35);
	fConst56 = (fConst35 + -5.3835170798891596e-15);
	fConst57 = (5.3835170798891596e-15 - fConst35);
	fConst58 = (fConst35 + 5.0034671369817102e-13);
	fConst59 = (fConst28 + 5.0034671369817102e-13);
	fConst60 = (5.3835170798891596e-15 - fConst28);
	fConst61 = (fConst28 + -5.3835170798891596e-15);
	fConst62 = (-5.0034671369817102e-13 - fConst28);
	fVslider0 = FAUSTFLOAT(0.5);
	fVslider1 = FAUSTFLOAT(0.5);

	samplingFreq = 96000;
	smpCl.setup(fSamplingFreq, samplingFreq);
	fSamplingFreq = samplingFreq;

	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = (0.0070000000000000062 * (1.0 - double(fVslider0)));
	double fSlow1 = (0.0070000000000000062 * (1.0 - double(fVslider1)));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec1[0] = (fSlow0 + (0.99299999999999999 * fRec1[1]));
		double fTemp0 = ((fConst0 * (fConst23 + (fRec1[0] * (fConst24 + (fConst25 * fRec1[0]))))) + 2.4440278174203298e-09);
		fRec0[0] = (double(input0[i]) - ((((((fRec0[1] * ((fConst0 * (fConst3 + (fRec1[0] * (fConst5 + (fConst6 * fRec1[0]))))) + 1.2220139087101701e-08)) + (fRec0[2] * ((fConst0 * (fConst8 + (fRec1[0] * (fConst10 + (fConst11 * fRec1[0]))))) + 2.4440278174203299e-08))) + (fRec0[3] * ((fConst0 * (fConst12 + (fRec1[0] * (fConst13 + (fConst14 * fRec1[0]))))) + 2.4440278174203299e-08))) + (fRec0[4] * ((fConst0 * (fConst15 + (fRec1[0] * (fConst16 + (fConst17 * fRec1[0]))))) + 1.2220139087101701e-08))) + (fRec0[5] * ((fConst0 * (fConst19 + (fRec1[0] * (fConst21 + (fConst22 * fRec1[0]))))) + 2.4440278174203298e-09))) / fTemp0));
		fRec2[0] = (fSlow1 + (0.99299999999999999 * fRec2[1]));
		double fTemp1 = (fConst33 * fRec2[0]);
		double fTemp2 = (fConst40 * fRec2[0]);
		output0[i] = FAUSTFLOAT((fConst1 * (((((((fRec0[0] * (fConst27 + ((fConst0 * (fRec1[0] * (fConst29 + ((fRec1[0] * (fConst30 + (fConst31 * fRec2[0]))) + (fConst32 * fRec2[0]))))) + fTemp1))) + (fRec0[1] * (fConst34 + ((fConst0 * (fRec1[0] * (fConst36 + ((fRec1[0] * (fConst37 + (fConst38 * fRec2[0]))) + (fConst39 * fRec2[0]))))) + fTemp2)))) + (fRec0[2] * (fConst42 + ((fConst0 * (fRec1[0] * (fConst44 + ((fRec1[0] * (fConst45 + (fConst46 * fRec2[0]))) + (fConst47 * fRec2[0]))))) + (fConst48 * fRec2[0]))))) + (fRec0[3] * (fConst49 + ((fConst0 * (fRec1[0] * (fConst50 + ((fRec1[0] * (fConst51 + (fConst52 * fRec2[0]))) + (fConst53 * fRec2[0]))))) + (fConst54 * fRec2[0]))))) + (fRec0[4] * (fConst27 + (fTemp1 + (fConst0 * (fRec1[0] * (fConst55 + ((fRec1[0] * (fConst56 + (fConst57 * fRec2[0]))) + (fConst58 * fRec2[0]))))))))) + (fRec0[5] * (fConst34 + (fTemp2 + (fConst0 * (fRec1[0] * (fConst59 + ((fRec1[0] * (fConst60 + (fConst61 * fRec2[0]))) + (fConst62 * fRec2[0]))))))))) / fTemp0)));
		fRec1[1] = fRec1[0];
		for (int j0 = 5; (j0 > 0); j0 = (j0 - 1)) {
			fRec0[j0] = fRec0[(j0 - 1)];
		}
		fRec2[1] = fRec2[0];
	}

	FAUSTFLOAT bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i = 0; (i < ReCount); i = (i + 1)) {
		bufCl[i] = FAUSTFLOAT(double(asymclip4(double(double(bufCl[i])))));
	}
	smpCl.down(bufCl, output0);

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("fuzzface.Fuzz",N_("Fuzz"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("fuzzface.Level",N_("Level"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01);
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
                        <property name=\"var_id\">fuzzface.Fuzz</property>\n\
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
                        <property name=\"var_id\">fuzzface.Level</property>\n\
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
                <property name=\"var_id\">fuzzface.Level</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Level</property>\n\
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
#define PARAM(p) ("fuzzface" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Fuzz"), "Fuzz");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknob(PARAM("Level"), "Level");

    b.create_small_rackknobr(PARAM("Fuzz"), "Fuzz");
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

} // end namespace fuzzface
