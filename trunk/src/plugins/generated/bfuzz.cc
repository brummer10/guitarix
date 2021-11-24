// generated from file '../src/plugins/bfuzz.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

#include "trany.h"

namespace pluginlib {
namespace bfuzz {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider1;
	double fRec0[2];
	double fConst3;
	FAUSTFLOAT fVslider2;
	double fRec2[2];
	double fConst5;
	FAUSTFLOAT fVslider3;
	double fRec3[2];
	double fConst6;
	double fConst7;
	double fConst9;
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst19;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fRec1[5];
	double fConst29;
	double fConst31;
	double fConst32;
	double fConst33;


	gx_resample::FixedRateResampler smpCl;
	double fConstCl4;
	double fVecCl0[2];
	double fRecCl7[2];
	double fRecCl6[3];
	double fConstCl6;
	double fConstCl7;
	double fRecCl8[2];
	double fRecCl5[3];
	double fConstCl8;
	double fConstCl9;
	double fRecCl4[2];
	double fRecCl3[2];
	double fRecCl2[3];
	double fRecCl9[2];
	double fRecCl1[3];
	double fRecCl0[2];

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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec2[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec3[l2] = 0.0;
	for (int l3 = 0; (l3 < 5); l3 = (l3 + 1)) fRec1[l3] = 0.0;

	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fVecCl0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRecCl7[l1] = 0.0;
	for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) fRecCl6[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRecCl8[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRecCl5[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRecCl4[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRecCl3[l6] = 0.0;
	for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) fRecCl2[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRecCl9[l8] = 0.0;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRecCl1[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRecCl0[l10] = 0.0;

}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	double fConst2 = (7.2943610474619998e-20 * fConst0);
	fConst3 = ((fConst0 * ((fConst1 * (fConst2 + 1.76595983618132e-14)) + -4.8513983754217396e-09)) + -3.7677484749893301e-09);
	double fConst4 = (7.6249645622343004e-19 * fConst0);
	fConst5 = ((fConst1 * (-2.00101274401661e-14 - fConst4)) + 1.39716735775323e-08);
	fConst6 = ((fConst1 * (fConst4 + 1.8103019826361799e-14)) + -9.4182821520959501e-09);
	fConst7 = ((fConst1 * (-1.74771564451602e-14 - fConst2)) + 8.2890466449765197e-10);
	double fConst8 = (1.0941541571193e-19 * fConst1);
	fConst9 = ((fConst1 * (1.06457253601328e-10 - fConst8)) + -5.6516227124839897e-09);
	double fConst10 = (1.1437446843351499e-18 * fConst1);
	fConst11 = (fConst10 + -2.8200401298604502e-10);
	fConst12 = (1.9144777062732601e-10 - fConst10);
	fConst13 = (fConst8 + -1.9031750565421301e-11);
	fConst14 = ((fConst0 * ((fConst1 * (fConst2 + -1.76595983618132e-14)) + 4.8513983754217396e-09)) + -3.7677484749893301e-09);
	fConst15 = ((fConst1 * (2.00101274401661e-14 - fConst4)) + -1.39716735775323e-08);
	fConst16 = ((fConst1 * (fConst4 + -1.8103019826361799e-14)) + 9.4182821520959501e-09);
	fConst17 = ((fConst1 * (1.74771564451602e-14 - fConst2)) + -8.2890466449765197e-10);
	double fConst18 = (1.8235902618654999e-20 * fConst0);
	fConst19 = ((fConst0 * ((fConst0 * ((fConst0 * (8.8297991809066096e-15 - fConst18)) + -5.3228626800664099e-11)) + 2.4256991877108698e-09)) + -9.4193711874733107e-10);
	double fConst20 = (1.9062411405585799e-19 * fConst0);
	fConst21 = ((fConst0 * ((fConst0 * (fConst20 + -1.0005063720082999e-14)) + 1.4100200649302199e-10)) + -6.9858367887661699e-09);
	fConst22 = ((fConst0 * ((fConst0 * (9.0515099131808902e-15 - fConst20)) + -9.5723885313662798e-11)) + 4.70914107604798e-09);
	fConst23 = ((fConst0 * ((fConst0 * (fConst18 + -8.7385782225801096e-15)) + 9.51587528271067e-12)) + -4.1445233224882599e-10);
	fConst24 = ((fConst0 * ((fConst0 * ((fConst0 * (-8.8297991809066096e-15 - fConst18)) + -5.3228626800664099e-11)) + -2.4256991877108698e-09)) + -9.4193711874733107e-10);
	fConst25 = ((fConst0 * ((fConst0 * (fConst20 + 1.0005063720082999e-14)) + 1.4100200649302199e-10)) + 6.9858367887661699e-09);
	fConst26 = ((fConst0 * ((fConst0 * (-9.0515099131808902e-15 - fConst20)) + -9.5723885313662798e-11)) + -4.70914107604798e-09);
	fConst27 = ((fConst0 * ((fConst0 * (fConst18 + 8.7385782225801096e-15)) + 9.51587528271067e-12)) + 4.1445233224882599e-10);
	double fConst28 = (7.7691191360934095e-14 * fConst0);
	fConst29 = (-3.8863252769412701e-10 - fConst28);
	double fConst30 = (1.6578093289843499e-16 * fConst0);
	fConst31 = (-8.2928143933967301e-13 - fConst30);
	fConst32 = (fConst28 + -3.8863252769412701e-10);
	fConst33 = (fConst30 + -8.2928143933967301e-13);

	sample_rate = 96000;
	smpCl.setup(fSampleRate, sample_rate);
	fSampleRate = sample_rate;
	double fConstCl0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConstCl1 = std::tan((97.389372261283583 / fConstCl0));
	double fConstCl2 = (1.0 / fConstCl1);
	double fConstCl3 = (fConstCl2 + 1.0);
	fConstCl4 = (1.0 / (fConstCl1 * fConstCl3));
	double fConstCl5 = (1.0 / std::tan((270.1769682087222 / fConstCl0)));
	fConstCl6 = (1.0 / (fConstCl5 + 1.0));
	fConstCl7 = (1.0 - fConstCl5);
	fConstCl8 = (0.0 - fConstCl4);
	fConstCl9 = ((1.0 - fConstCl2) / fConstCl3);

	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = (0.01 * double(fVslider0));
	double fSlow1 = (1.0 - fSlow0);
	double fSlow2 = (0.0070000000000000062 * double(fVslider1));
	double fSlow3 = (0.0070000000000000062 * double(fVslider2));
	double fSlow4 = (0.0070000000000000062 * double(fVslider3));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		double fTemp0 = double(input0[i0]);
		fRec0[0] = (fSlow2 + (0.99299999999999999 * fRec0[1]));
		fRec2[0] = (fSlow3 + (0.99299999999999999 * fRec2[1]));
		fRec3[0] = (fSlow4 + (0.99299999999999999 * fRec3[1]));
		double fTemp1 = (((fConst24 * fRec2[0]) + (fConst0 * (fConst25 + (fRec3[0] * (fConst26 + (fConst27 * fRec2[0])))))) + 1.0702593354654499e-08);
		fRec1[0] = ((fSlow0 * fTemp0) - (((((fRec1[1] * (((fConst3 * fRec2[0]) + (fConst0 * (fConst5 + (fRec3[0] * (fConst6 + (fConst7 * fRec2[0])))))) + 4.2810373418617997e-08)) + (fRec1[2] * (((fConst9 * fRec2[0]) + (fConst1 * (fConst11 + (fRec3[0] * (fConst12 + (fConst13 * fRec2[0])))))) + 6.4215560127927005e-08))) + (fRec1[3] * (((fConst14 * fRec2[0]) + (fConst0 * (fConst15 + (fRec3[0] * (fConst16 + (fConst17 * fRec2[0])))))) + 4.2810373418617997e-08))) + (fRec1[4] * (((fConst19 * fRec2[0]) + (fConst0 * (fConst21 + (fRec3[0] * (fConst22 + (fConst23 * fRec2[0])))))) + 1.0702593354654499e-08))) / fTemp1));
		double fTemp2 = (1.6578093289843499e-16 * fRec2[0]);
		double fTemp3 = (3.3156186579686998e-16 * fRec2[0]);
		double fTemp4 = (fTemp3 + 1.5538238272186799e-13);
		double fTemp5 = ((0.0 - fTemp3) + -1.5538238272186799e-13);
		output0[i0] = FAUSTFLOAT(((fSlow1 * fTemp0) + (fConst1 * ((fRec0[0] * (((((fRec1[0] * ((fConst29 + (fConst31 * fRec2[0])) + (fConst0 * (fRec3[0] * (fTemp2 + 7.7691191360934095e-14))))) + (fConst0 * (fRec1[1] * (fTemp4 + (fRec3[0] * fTemp5))))) + (fRec1[2] * ((1.6585628786793501e-12 * fRec2[0]) + 7.7726505538825401e-10))) + (fConst0 * (fRec1[3] * (fTemp5 + (fRec3[0] * fTemp4))))) + (fRec1[4] * ((fConst32 + (fConst33 * fRec2[0])) + (fConst0 * (fRec3[0] * ((0.0 - fTemp2) + -7.7691191360934095e-14))))))) / fTemp1))));
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		for (int j0 = 4; (j0 > 0); j0 = (j0 - 1)) {
			fRec1[j0] = fRec1[(j0 - 1)];
		}
	}

	FAUSTFLOAT bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i0 = 0; (i0 < ReCount); i0 = (i0 + 1)) {
		double fTemp0 = double(bufCl[i0]);
		fVecCl0[0] = fTemp0;
		fRecCl7[0] = ((0.93028479253239138 * (fTemp0 + fVecCl0[1])) - (0.86056958506478287 * fRecCl7[1]));
		fRecCl6[0] = (fRecCl7[0] - ((1.8405051250752198 * fRecCl6[1]) + (0.86129424393186271 * fRecCl6[2])));
		fRecCl8[0] = (fConstCl6 * ((0.027 * (fRecCl5[1] + fRecCl5[2])) - (fConstCl7 * fRecCl8[1])));
		fRecCl5[0] = (double(Ftrany(int(TRANY_TABLE_7199P_68k), double((((0.92544984225177063 * (fRecCl6[0] + fRecCl6[2])) + (fRecCl8[0] + (1.8508996845035413 * fRecCl6[1]))) + -3.5719810000000001)))) + -117.70440740740739);
		fRecCl4[0] = ((0.025000000000000001 * ((fConstCl4 * fRecCl5[0]) + (fConstCl8 * fRecCl5[1]))) - (fConstCl9 * fRecCl4[1]));
		fRecCl3[0] = ((0.93028479253239138 * (fRecCl4[0] + fRecCl4[1])) - (0.86056958506478287 * fRecCl3[1]));
		fRecCl2[0] = (fRecCl3[0] - ((1.8405051250752198 * fRecCl2[1]) + (0.86129424393186271 * fRecCl2[2])));
		fRecCl9[0] = (fConstCl6 * ((0.027 * (fRecCl1[1] + fRecCl1[2])) - (fConstCl7 * fRecCl9[1])));
		fRecCl1[0] = (double(Ftrany(int(TRANY_TABLE_7199P_68k), double((((0.92544984225177063 * (fRecCl2[0] + fRecCl2[2])) + (fRecCl9[0] + (1.8508996845035413 * fRecCl2[1]))) + -3.5719810000000001)))) + -117.70440740740739);
		fRecCl0[0] = ((0.025000000000000001 * ((fConstCl4 * fRecCl1[0]) + (fConstCl8 * fRecCl1[1]))) - (fConstCl9 * fRecCl0[1]));
		bufCl[i0] = FAUSTFLOAT(fRecCl0[0]);
		fVecCl0[1] = fVecCl0[0];
		fRecCl7[1] = fRecCl7[0];
		fRecCl6[2] = fRecCl6[1];
		fRecCl6[1] = fRecCl6[0];
		fRecCl8[1] = fRecCl8[0];
		fRecCl5[2] = fRecCl5[1];
		fRecCl5[1] = fRecCl5[0];
		fRecCl4[1] = fRecCl4[0];
		fRecCl3[1] = fRecCl3[0];
		fRecCl2[2] = fRecCl2[1];
		fRecCl2[1] = fRecCl2[0];
		fRecCl9[1] = fRecCl9[0];
		fRecCl1[2] = fRecCl1[1];
		fRecCl1[1] = fRecCl1[0];
		fRecCl0[1] = fRecCl0[0];
	}
	smpCl.down(bufCl, output0);

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("bfuzz.Drive",N_("Drive"),"S","",&fVslider2, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("bfuzz.Level",N_("Level"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("bfuzz.Thickness",N_("Thickness"),"S","",&fVslider3, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("bfuzz.wet_dry",N_("Wet/Dry"),"S",N_("percentage of processed signal in output signal"),&fVslider0, 100.0, 0.0, 100.0, 1.0, 0);
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
