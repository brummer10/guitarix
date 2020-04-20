// generated from file '../src/plugins/hornet.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace hornet {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider0;
	double fRec0[2];
	FAUSTFLOAT fVslider1;
	double fRec2[2];
	double fConst2;
	double fConst3;
	FAUSTFLOAT fVslider2;
	double fRec3[2];
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
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fRec1[5];
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
	double fConst63;
	double fConst64;
	double fConst65;
	double fConst66;
	double fConst67;
	double fConst68;
	double fConst69;
	double fConst70;
	double fConst71;
	double fConst72;
	double fConst73;
	double fConst74;
	double fConst75;
	double fConst76;
	double fConst77;
	double fConst78;
	double fConst79;
	double fConst80;
	double fConst81;

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
	id = "hornet";
	name = N_("Hornet");
	groups = 0;
	description = N_("Hornet simulation"); // description (tooltip)
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec2[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec3[l2] = 0.0;
	for (int l3 = 0; (l3 < 5); l3 = (l3 + 1)) fRec1[l3] = 0.0;
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
	fConst2 = (8.0344113490136796e-19 * fConst0);
	fConst3 = (((-2.1327709047497402e-15 - fConst2) * fConst1) + 4.6082764112797202e-12);
	fConst4 = (1.0533847926209301e-18 * fConst0);
	fConst5 = (((-2.7912118642523799e-15 - fConst4) * fConst1) + 2.1911443811562198e-12);
	fConst6 = (8.9092734281538994e-20 * fConst0);
	fConst7 = (((fConst6 + 2.3136174511326298e-16) * fConst1) + -1.7723782402438701e-13);
	fConst8 = (7.3938345895294102e-21 * fConst0);
	fConst9 = (((-4.97629551390976e-16 - fConst8) * fConst1) + 8.6188432028757995e-11);
	fConst10 = (2.8896627533487999e-21 * fConst0);
	fConst11 = (((-2.3141629669080201e-16 - fConst10) * fConst1) + 1.16303563314026e-11);
	fConst12 = (1.02834973428782e-20 * fConst0);
	fConst13 = (((fConst12 + 6.4056516005839696e-16) * fConst1) + -3.1853156396660198e-11);
	fConst14 = ((1.20516170235205e-18 * fConst1) + -2.2146088225976801e-13);
	fConst15 = ((1.5800771889314001e-18 * fConst1) + -2.4710764349103501e-13);
	fConst16 = (2.04220452060922e-14 - (1.3363910142230799e-19 * fConst1));
	fConst17 = ((1.10907518842941e-20 * fConst1) + -2.5054803935412798e-12);
	fConst18 = ((4.33449413002321e-21 * fConst1) + -1.16746083607033e-12);
	fConst19 = (3.1991095902122601e-12 - (1.5425246014317301e-20 * fConst1));
	fConst20 = (((2.1327709047497402e-15 - fConst2) * fConst1) + -4.6082764112797202e-12);
	fConst21 = (((2.7912118642523799e-15 - fConst4) * fConst1) + -2.1911443811562198e-12);
	fConst22 = (((fConst6 + -2.3136174511326298e-16) * fConst1) + 1.7723782402438701e-13);
	fConst23 = (((4.97629551390976e-16 - fConst8) * fConst1) + -8.6188432028757995e-11);
	fConst24 = (((2.3141629669080201e-16 - fConst10) * fConst1) + -1.16303563314026e-11);
	fConst25 = (((fConst12 + -6.4056516005839696e-16) * fConst1) + 3.1853156396660198e-11);
	fConst26 = (2.0086028372534199e-19 * fConst0);
	fConst27 = (((((fConst26 + -1.0663854523748701e-15) * fConst0) + 1.1073044112988401e-13) * fConst0) + -2.3041382056398601e-12);
	fConst28 = (2.6334619815523401e-19 * fConst0);
	fConst29 = (((((fConst28 + -1.3956059321261899e-15) * fConst0) + 1.2355382174551801e-13) * fConst0) + -1.0955721905781099e-12);
	fConst30 = (2.22731835703847e-20 * fConst0);
	fConst31 = (((((1.15680872556631e-16 - fConst30) * fConst0) + -1.02110226030461e-14) * fConst0) + 8.8618912012193706e-14);
	fConst32 = (1.8484586473823499e-21 * fConst0);
	fConst33 = (((((fConst32 + -2.48814775695488e-16) * fConst0) + 1.2527401967706399e-12) * fConst0) + -4.3094216014378998e-11);
	fConst34 = (7.2241568833720101e-22 * fConst0);
	fConst35 = (((((fConst34 + -1.1570814834540101e-16) * fConst0) + 5.8373041803516501e-13) * fConst0) + -5.8151781657012799e-12);
	fConst36 = (2.5708743357195501e-21 * fConst0);
	fConst37 = (((((3.2028258002919799e-16 - fConst36) * fConst0) + -1.59955479510613e-12) * fConst0) + 1.5926578198330099e-11);
	fConst38 = (((((fConst26 + 1.0663854523748701e-15) * fConst0) + 1.1073044112988401e-13) * fConst0) + 2.3041382056398601e-12);
	fConst39 = (((((fConst28 + 1.3956059321261899e-15) * fConst0) + 1.2355382174551801e-13) * fConst0) + 1.0955721905781099e-12);
	fConst40 = (((((-1.15680872556631e-16 - fConst30) * fConst0) + -1.02110226030461e-14) * fConst0) + -8.8618912012193706e-14);
	fConst41 = (((((fConst32 + 2.48814775695488e-16) * fConst0) + 1.2527401967706399e-12) * fConst0) + 4.3094216014378998e-11);
	fConst42 = (((((fConst34 + 1.1570814834540101e-16) * fConst0) + 5.8373041803516501e-13) * fConst0) + 5.8151781657012799e-12);
	fConst43 = (((((-3.2028258002919799e-16 - fConst36) * fConst0) + -1.59955479510613e-12) * fConst0) + -1.5926578198330099e-11);
	fConst44 = (2.4218162356217001e-20 * fConst0);
	fConst45 = (((fConst44 + 1.2685958335763499e-16) * fConst0) + 3.2109130517186899e-15);
	fConst46 = (9.4649563589667005e-21 * fConst0);
	fConst47 = (fConst46 + 4.9338602296741301e-17);
	fConst48 = (3.3683118715183703e-20 * fConst0);
	fConst49 = (-1.75582214579149e-16 - fConst48);
	fConst50 = (1.45891323583538e-19 * fConst0);
	fConst51 = (((fConst50 + 7.4048946315080199e-16) * fConst0) + -1.04296301457845e-13);
	fConst52 = (2.2865563315343902e-18 * fConst0);
	fConst53 = (fConst52 + 1.19192830048069e-14);
	fConst54 = (2.8979800773940299e-18 * fConst0);
	fConst55 = (fConst54 + 1.5106491892798699e-14);
	fConst56 = (9.6872649424868004e-20 * fConst0);
	fConst57 = (-2.5371916671527101e-16 - fConst56);
	fConst58 = (3.7859825435866802e-20 * fConst0);
	fConst59 = (-9.8677204593482602e-17 - fConst58);
	fConst60 = (1.34732474860735e-19 * fConst0);
	fConst61 = (fConst60 + 3.51164429158298e-16);
	fConst62 = (5.83565294334152e-19 * fConst0);
	fConst63 = (-1.4809789263016e-15 - fConst62);
	fConst64 = (9.1462253261375608e-18 * fConst0);
	fConst65 = (-2.38385660096139e-14 - fConst64);
	fConst66 = (1.15919203095761e-17 * fConst0);
	fConst67 = (-3.0212983785597297e-14 - fConst66);
	fConst68 = ((1.4530897413730201e-19 * fConst1) + -6.4218261034373797e-15);
	fConst69 = ((8.7534794150122796e-19 * fConst1) + 2.08592602915691e-13);
	fConst70 = (2.5371916671527101e-16 - fConst56);
	fConst71 = (9.8677204593482602e-17 - fConst58);
	fConst72 = (fConst60 + -3.51164429158298e-16);
	fConst73 = (1.4809789263016e-15 - fConst62);
	fConst74 = (2.38385660096139e-14 - fConst64);
	fConst75 = (3.0212983785597297e-14 - fConst66);
	fConst76 = (((fConst44 + -1.2685958335763499e-16) * fConst0) + 3.2109130517186899e-15);
	fConst77 = (fConst46 + -4.9338602296741301e-17);
	fConst78 = (1.75582214579149e-16 - fConst48);
	fConst79 = (((fConst50 + -7.4048946315080199e-16) * fConst0) + -1.04296301457845e-13);
	fConst80 = (fConst52 + -1.19192830048069e-14);
	fConst81 = (fConst54 + -1.5106491892798699e-14);
	fVslider0 = FAUSTFLOAT(0.5);
	fVslider1 = FAUSTFLOAT(0.5);
	fVslider2 = FAUSTFLOAT(0.5);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = (0.0070000000000000062 * double(fVslider0));
	double fSlow1 = (0.0070000000000000062 * double(fVslider1));
	double fSlow2 = (0.0070000000000000062 * double(fVslider2));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec0[0] = (fSlow0 + (0.99299999999999999 * fRec0[1]));
		fRec2[0] = (fSlow1 + (0.99299999999999999 * fRec2[1]));
		fRec3[0] = (fSlow2 + (0.99299999999999999 * fRec3[1]));
		double fTemp0 = (((fRec2[0] * ((fConst0 * (fConst38 + (fRec3[0] * (fConst39 + (fConst40 * fRec3[0]))))) + 1.30107041069324e-11)) + (fConst0 * (fConst41 + (fRec3[0] * (fConst42 + (fConst43 * fRec3[0])))))) + 3.05506357605318e-10);
		fRec1[0] = (double(input0[i]) - (((((fRec1[1] * (((fRec2[0] * ((fConst0 * (fConst3 + (fRec3[0] * (fConst5 + (fConst7 * fRec3[0]))))) + 5.2042816427729497e-11)) + (fConst0 * (fConst9 + (fRec3[0] * (fConst11 + (fConst13 * fRec3[0])))))) + 1.2220254304212699e-09)) + (fRec1[2] * (((fRec2[0] * ((fConst1 * (fConst14 + (fRec3[0] * (fConst15 + (fConst16 * fRec3[0]))))) + 7.8064224641594301e-11)) + (fConst1 * (fConst17 + (fRec3[0] * (fConst18 + (fConst19 * fRec3[0])))))) + 1.83303814563191e-09))) + (fRec1[3] * (((fRec2[0] * ((fConst0 * (fConst20 + (fRec3[0] * (fConst21 + (fConst22 * fRec3[0]))))) + 5.2042816427729497e-11)) + (fConst0 * (fConst23 + (fRec3[0] * (fConst24 + (fConst25 * fRec3[0])))))) + 1.2220254304212699e-09))) + (fRec1[4] * (((fRec2[0] * ((fConst0 * (fConst27 + (fRec3[0] * (fConst29 + (fConst31 * fRec3[0]))))) + 1.30107041069324e-11)) + (fConst0 * (fConst33 + (fRec3[0] * (fConst35 + (fConst37 * fRec3[0])))))) + 3.05506357605318e-10))) / fTemp0));
		output0[i] = FAUSTFLOAT((0.40000000000000002 * std::min<double>(0.75139999999999996, std::max<double>(-0.45140000000000002, (fConst1 * ((fRec0[0] * (((((fRec1[0] * (fConst45 + ((fConst0 * (fRec3[0] * (fConst47 + (fConst49 * fRec3[0])))) + (fRec2[0] * (fConst51 + (fConst0 * (fRec3[0] * (fConst53 + (fConst55 * fRec3[0]))))))))) + (fConst0 * (fRec1[1] * (fConst57 + ((fRec3[0] * (fConst59 + (fConst61 * fRec3[0]))) + (fRec2[0] * (fConst63 + (fRec3[0] * (fConst65 + (fConst67 * fRec3[0])))))))))) + (fRec1[2] * (fConst68 + ((fConst1 * (fRec3[0] * ((0.0 - (2.02098712291102e-19 * fRec3[0])) + 5.6789738153800206e-20))) + (fRec2[0] * (fConst69 + (fConst1 * (fRec3[0] * ((1.7387880464364199e-17 * fRec3[0]) + 1.37193379892063e-17))))))))) + (fConst0 * (fRec1[3] * (fConst70 + ((fRec3[0] * (fConst71 + (fConst72 * fRec3[0]))) + (fRec2[0] * (fConst73 + (fRec3[0] * (fConst74 + (fConst75 * fRec3[0])))))))))) + (fRec1[4] * (fConst76 + ((fConst0 * (fRec3[0] * (fConst77 + (fConst78 * fRec3[0])))) + (fRec2[0] * (fConst79 + (fConst0 * (fRec3[0] * (fConst80 + (fConst81 * fRec3[0]))))))))))) / fTemp0))))));
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		for (int j0 = 4; (j0 > 0); j0 = (j0 - 1)) {
			fRec1[j0] = fRec1[(j0 - 1)];
		}
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("hornet.Fuzz",N_("Fuzz"),"S","",&fVslider2, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("hornet.Level",N_("Level"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("hornet.Sustain",N_("Sustain"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01);
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
                        <property name=\"var_id\">hornet.Sustain</property>\n\
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
                        <property name=\"var_id\">hornet.Level</property>\n\
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
                        <property name=\"var_id\">hornet.Fuzz</property>\n\
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
                <property name=\"var_id\">hornet.Level</property>\n\
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
#define PARAM(p) ("hornet" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Fuzz"), N_("Fuzz"));
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Level"), N_("Level"));

    b.create_small_rackknobr(PARAM("Sustain"), N_("Sustain"));

    b.create_small_rackknobr(PARAM("Fuzz"), N_("Fuzz"));
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

} // end namespace hornet
} // end namespace pluginlib
