// generated from file '../src/plugins/bfuzz.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace bfuzz {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	FAUSTFLOAT fVslider0;
	double fRec8[2];
	FAUSTFLOAT fVslider1;
	double fConst7;
	double fConst8;
	FAUSTFLOAT fVslider2;
	double fRec10[2];
	double fConst9;
	double fConst10;
	FAUSTFLOAT fVslider3;
	double fRec11[2];
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
	double fRec9[5];
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fVec0[2];
	double fRec7[2];
	double fRec6[3];
	double fConst39;
	double fConst40;
	double fConst41;
	double fRec12[2];
	double fRec5[3];
	double fConst42;
	double fConst43;
	double fRec4[2];
	double fRec3[2];
	double fRec2[3];
	double fRec13[2];
	double fRec1[3];
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
	id = "bfuzz";
	name = N_("Bass Fuzz Pedal");
	groups = 0;
	description = N_("Bass Fuzz Pedal"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("Bass Fuzz");     // shortname
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
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec10[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec11[l2] = 0.0;
	for (int l3 = 0; (l3 < 5); l3 = (l3 + 1)) fRec9[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fVec0[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec7[l5] = 0.0;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec6[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec12[l7] = 0.0;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec5[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec4[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec3[l10] = 0.0;
	for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) fRec2[l11] = 0.0;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec13[l12] = 0.0;
	for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) fRec1[l13] = 0.0;
	for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) fRec0[l14] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = std::tan((34.557519189487721 / fConst0));
	fConst2 = (1.0 / fConst1);
	fConst3 = (fConst2 + 1.0);
	fConst4 = (1.0 / (fConst3 * fConst1));
	fConst5 = mydsp_faustpower2_f(fConst0);
	fConst6 = (0.93028479253239138 * fConst5);
	fConst7 = (7.2943610474619998e-20 * fConst0);
	fConst8 = (((((fConst7 + 1.76595983618132e-14) * fConst5) + -4.8513983754217396e-09) * fConst0) + -3.7677484749893301e-09);
	fConst9 = (7.6249645622343004e-19 * fConst0);
	fConst10 = (((-2.00101274401661e-14 - fConst9) * fConst5) + 1.39716735775323e-08);
	fConst11 = (((fConst9 + 1.8103019826361799e-14) * fConst5) + -9.4182821520959501e-09);
	fConst12 = (((-1.74771564451602e-14 - fConst7) * fConst5) + 8.2890466449765197e-10);
	fConst13 = (1.0941541571193e-19 * fConst5);
	fConst14 = (((1.06457253601328e-10 - fConst13) * fConst5) + -5.6516227124839897e-09);
	fConst15 = (1.1437446843351499e-18 * fConst5);
	fConst16 = (fConst15 + -2.8200401298604502e-10);
	fConst17 = (1.9144777062732601e-10 - fConst15);
	fConst18 = (fConst13 + -1.9031750565421301e-11);
	fConst19 = (((((fConst7 + -1.76595983618132e-14) * fConst5) + 4.8513983754217396e-09) * fConst0) + -3.7677484749893301e-09);
	fConst20 = (((2.00101274401661e-14 - fConst9) * fConst5) + -1.39716735775323e-08);
	fConst21 = (((fConst9 + -1.8103019826361799e-14) * fConst5) + 9.4182821520959501e-09);
	fConst22 = (((1.74771564451602e-14 - fConst7) * fConst5) + -8.2890466449765197e-10);
	fConst23 = (1.8235902618654999e-20 * fConst0);
	fConst24 = (((((((8.8297991809066096e-15 - fConst23) * fConst0) + -5.3228626800664099e-11) * fConst0) + 2.4256991877108698e-09) * fConst0) + -9.4193711874733107e-10);
	fConst25 = (1.9062411405585799e-19 * fConst0);
	fConst26 = (((((fConst25 + -1.0005063720082999e-14) * fConst0) + 1.4100200649302199e-10) * fConst0) + -6.9858367887661699e-09);
	fConst27 = (((((9.0515099131808902e-15 - fConst25) * fConst0) + -9.5723885313662798e-11) * fConst0) + 4.70914107604798e-09);
	fConst28 = (((((fConst23 + -8.7385782225801096e-15) * fConst0) + 9.51587528271067e-12) * fConst0) + -4.1445233224882599e-10);
	fConst29 = (((((((-8.8297991809066096e-15 - fConst23) * fConst0) + -5.3228626800664099e-11) * fConst0) + -2.4256991877108698e-09) * fConst0) + -9.4193711874733107e-10);
	fConst30 = (((((fConst25 + 1.0005063720082999e-14) * fConst0) + 1.4100200649302199e-10) * fConst0) + 6.9858367887661699e-09);
	fConst31 = (((((-9.0515099131808902e-15 - fConst25) * fConst0) + -9.5723885313662798e-11) * fConst0) + -4.70914107604798e-09);
	fConst32 = (((((fConst23 + 8.7385782225801096e-15) * fConst0) + 9.51587528271067e-12) * fConst0) + 4.1445233224882599e-10);
	fConst33 = (7.7691191360934095e-14 * fConst0);
	fConst34 = (-3.8863252769412701e-10 - fConst33);
	fConst35 = (1.6578093289843499e-16 * fConst0);
	fConst36 = (-8.2928143933967301e-13 - fConst35);
	fConst37 = (fConst33 + -3.8863252769412701e-10);
	fConst38 = (fConst35 + -8.2928143933967301e-13);
	fConst39 = (1.0 / std::tan((270.1769682087222 / fConst0)));
	fConst40 = (1.0 / (fConst39 + 1.0));
	fConst41 = (1.0 - fConst39);
	fConst42 = (0.0 - fConst4);
	fConst43 = ((1.0 - fConst2) / fConst3);
	fVslider0 = FAUSTFLOAT(0.5);
	fVslider1 = FAUSTFLOAT(100.0);
	fVslider2 = FAUSTFLOAT(0.5);
	fVslider3 = FAUSTFLOAT(0.5);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = (0.0070000000000000062 * double(fVslider0));
	double fSlow1 = (0.01 * double(fVslider1));
	double fSlow2 = (0.0070000000000000062 * double(fVslider2));
	double fSlow3 = (0.0070000000000000062 * double(fVslider3));
	double fSlow4 = (1.0 - fSlow1);
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec8[0] = (fSlow0 + (0.99299999999999999 * fRec8[1]));
		double fTemp0 = double(input0[i]);
		fRec10[0] = (fSlow2 + (0.99299999999999999 * fRec10[1]));
		fRec11[0] = (fSlow3 + (0.99299999999999999 * fRec11[1]));
		double fTemp1 = (((fConst29 * fRec10[0]) + (fConst0 * (fConst30 + (fRec11[0] * (fConst31 + (fConst32 * fRec10[0])))))) + 1.0702593354654499e-08);
		fRec9[0] = ((fSlow1 * fTemp0) - (((((fRec9[1] * (((fConst8 * fRec10[0]) + (fConst0 * (fConst10 + (fRec11[0] * (fConst11 + (fConst12 * fRec10[0])))))) + 4.2810373418617997e-08)) + (fRec9[2] * (((fConst14 * fRec10[0]) + (fConst5 * (fConst16 + (fRec11[0] * (fConst17 + (fConst18 * fRec10[0])))))) + 6.4215560127927005e-08))) + (fRec9[3] * (((fConst19 * fRec10[0]) + (fConst0 * (fConst20 + (fRec11[0] * (fConst21 + (fConst22 * fRec10[0])))))) + 4.2810373418617997e-08))) + (fRec9[4] * (((fConst24 * fRec10[0]) + (fConst0 * (fConst26 + (fRec11[0] * (fConst27 + (fConst28 * fRec10[0])))))) + 1.0702593354654499e-08))) / fTemp1));
		double fTemp2 = (1.6578093289843499e-16 * fRec10[0]);
		double fTemp3 = (3.3156186579686998e-16 * fRec10[0]);
		double fTemp4 = (fTemp3 + 1.5538238272186799e-13);
		double fTemp5 = ((0.0 - fTemp3) + -1.5538238272186799e-13);
		double fTemp6 = ((fRec8[0] * (((((fRec9[0] * ((fConst34 + (fConst36 * fRec10[0])) + (fConst0 * (fRec11[0] * (fTemp2 + 7.7691191360934095e-14))))) + (fConst0 * (fRec9[1] * (fTemp4 + (fRec11[0] * fTemp5))))) + (fRec9[2] * ((1.6585628786793501e-12 * fRec10[0]) + 7.7726505538825401e-10))) + (fConst0 * (fRec9[3] * (fTemp5 + (fRec11[0] * fTemp4))))) + (fRec9[4] * ((fConst37 + (fConst38 * fRec10[0])) + (fConst0 * (fRec11[0] * ((0.0 - fTemp2) + -7.7691191360934095e-14))))))) / fTemp1);
		fVec0[0] = fTemp6;
		fRec7[0] = ((fConst6 * (fTemp6 + fVec0[1])) - (0.86056958506478287 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.86129424393186271 * fRec6[2])));
		fRec12[0] = (fConst40 * ((0.027 * (fRec5[1] + fRec5[2])) - (fConst41 * fRec12[1])));
		fRec5[0] = (double(Ftrany(int(TRANY_TABLE_7199P_68k), double((((0.92544984225177063 * (fRec6[0] + fRec6[2])) + (fRec12[0] + (1.8508996845035413 * fRec6[1]))) + -5.5719810000000001)))) + -43.630333333333311);
		fRec4[0] = ((0.025000000000000001 * ((fConst4 * fRec5[0]) + (fConst42 * fRec5[1]))) - (fConst43 * fRec4[1]));
		fRec3[0] = ((0.93028479253239138 * (fRec4[0] + fRec4[1])) - (0.86056958506478287 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.86129424393186271 * fRec2[2])));
		fRec13[0] = (fConst40 * ((0.027 * (fRec1[1] + fRec1[2])) - (fConst41 * fRec13[1])));
		fRec1[0] = (double(Ftrany(int(TRANY_TABLE_7199P_68k), double((((0.92544984225177063 * (fRec2[0] + fRec2[2])) + (fRec13[0] + (1.8508996845035413 * fRec2[1]))) + -5.5719810000000001)))) + -43.630333333333311);
		fRec0[0] = ((0.025000000000000001 * ((fConst4 * fRec1[0]) + (fConst42 * fRec1[1]))) - (fConst43 * fRec0[1]));
		output0[i] = FAUSTFLOAT((fRec0[0] + (fSlow4 * fTemp0)));
		fRec8[1] = fRec8[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		for (int j0 = 4; (j0 > 0); j0 = (j0 - 1)) {
			fRec9[j0] = fRec9[(j0 - 1)];
		}
		fVec0[1] = fVec0[0];
		fRec7[1] = fRec7[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec12[1] = fRec12[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec13[1] = fRec13[0];
		fRec1[2] = fRec1[1];
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
	reg.registerVar("bfuzz.Drive",N_("Drive"),"S","",&fVslider2, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("bfuzz.Level",N_("Level"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("bfuzz.Thickness",N_("Thickness"),"S","",&fVslider3, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("bfuzz.wet_dry",N_("Wet/Dry"),"S",N_("percentage of processed signal in output signal"),&fVslider1, 100.0, 0.0, 100.0, 1.0);
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
                        <property name=\"var_id\">bfuzz.Drive</property>\n\
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
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">bfuzz.Thickness</property>\n\
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
                      <object class=\"GxMidKnob\" id=\"gxbigknob3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">bfuzz.Level</property>\n\
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
                        <property name=\"var_id\">bfuzz.wet_dry</property>\n\
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
                    <property name=\"position\">3</property>\n\
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
                <property name=\"var_id\">bfuzz.Drive</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Drive</property>\n\
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
#define PARAM(p) ("bfuzz" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Level"), "Level");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Level"), "Level");

    b.create_small_rackknobr(PARAM("Drive"), "Drive");

    b.create_small_rackknobr(PARAM("Thickness"), "Thickness");
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

} // end namespace bfuzz
} // end namespace pluginlib
