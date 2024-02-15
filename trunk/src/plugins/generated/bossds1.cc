// generated from file '../src/plugins/bossds1.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "clipping.h"

namespace pluginlib {
namespace bossds1 {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int sample_rate;
	int fSampleRate;
	double fConst0;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	FAUSTFLOAT fVslider0;
	double fRec1[2];
	double fConst7;
	double fConst9;
	double fConst11;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst23;
	double fConst26;
	FAUSTFLOAT fHslider0;
	double fRec5[2];
	double fConst27;
	double fConst29;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst41;
	double fConst44;
	double fRec8[2];
	double fConst45;
	double fRec7[4];
	double fConst46;
	double fRec6[3];
	double fConst47;
	double fConst48;
	double fRec4[2];
	double fConst49;
	double fConst50;
	double fVec0[2];
	double fRec9[2];
	double fRec3[2];
	double fConst51;
	double fRec2[3];
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fRec0[3];
	double fConst56;
	double fConst58;
	double fConst59;
	FAUSTFLOAT fHslider1;
	double fRec10[2];

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
	id = "bossds1";
	name = N_("DS1");
	groups = 0;
	description = N_("DS1 simulation"); // description (tooltip)
	category = N_("Distortion");       // category
	shortname = N_("DS1");     // shortname
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec1[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec5[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec8[l2] = 0.0;
	for (int l3 = 0; l3 < 4; l3 = l3 + 1) fRec7[l3] = 0.0;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRec6[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec4[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fVec0[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec9[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec3[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec2[l9] = 0.0;
	for (int l10 = 0; l10 < 3; l10 = l10 + 1) fRec0[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec10[l11] = 0.0;
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
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 4.33883931795138e-10 * fConst0;
	fConst2 = fConst0 * (fConst1 + -6.90412007909908e-09) + 2.33802056631403e-08;
	fConst3 = mydsp_faustpower2_f(fConst0);
	fConst4 = 4.67604113262805e-08 - 8.67767863590276e-10 * fConst3;
	fConst5 = 1.0 / (fConst0 * (fConst1 + 6.90412007909908e-09) + 2.33802056631403e-08);
	double fConst6 = 2.89644353783249e-10 * fConst0;
	fConst7 = fConst0 * (-9.44398925362792e-07 - fConst6) + -0.000537812599864916;
	double fConst8 = 2.65571689713263e-10 * fConst0;
	fConst9 = fConst0 * (fConst8 + 7.50424979344313e-07);
	double fConst10 = 3.3778968192322e-10 * fConst0;
	fConst11 = fConst0 * (fConst10 + 1.55559824875468e-06);
	double fConst12 = 2.18842400636233e-10 * fConst0;
	fConst13 = fConst0 * (-5.20602596669238e-08 - fConst12) + 0.000537812599864916;
	fConst14 = fConst0 * (fConst12 + -2.33324618325395e-07);
	fConst15 = fConst0 * (9.44398925362792e-07 - fConst6) + -0.000537812599864916;
	fConst16 = fConst0 * (fConst8 + -7.50424979344313e-07);
	fConst17 = fConst0 * (fConst10 + -1.55559824875468e-06);
	fConst18 = 6.7557936384644e-10 * fConst3;
	fConst19 = 5.31143379426527e-10 * fConst3;
	fConst20 = 5.79288707566498e-10 * fConst3 + -0.00107562519972983;
	double fConst21 = 1.40428074750109e-05 * fConst0;
	double fConst22 = fConst21 + 0.325945241199478;
	fConst23 = (0.325945241199478 - fConst21) / fConst22;
	double fConst24 = 2.07985763541319e-05 * fConst0;
	double fConst25 = fConst24 + 0.00166833500166833;
	fConst26 = (0.00166833500166833 - fConst24) / fConst25;
	fConst27 = 3.18093350083904e-10 * fConst3;
	double fConst28 = 3.0314296262996e-10 * fConst0;
	fConst29 = fConst0 * (fConst28 + -3.38397180940322e-09);
	double fConst30 = 1.49503874539434e-11 * fConst0;
	fConst31 = fConst0 * (fConst30 + 1.66555708487018e-05);
	fConst32 = fConst0 * (fConst28 + -1.59012835323858e-05);
	fConst33 = fConst0 * (fConst30 + -7.50903344506575e-07);
	fConst34 = fConst0 * (fConst28 + 3.38397180940322e-09);
	fConst35 = fConst0 * (fConst30 + -1.66555708487018e-05);
	double fConst36 = 3.53982651634833e-10 * fConst0;
	fConst37 = fConst0 * (fConst36 + -2.38582349500046e-07) + 1.94656546234155e-05;
	fConst38 = fConst0 * (-2.38582349500046e-07 - fConst36) + 5.83969638702466e-05;
	fConst39 = fConst0 * (2.38582349500046e-07 - fConst36) + 5.83969638702466e-05;
	double fConst40 = fConst0 * (fConst36 + 2.38582349500046e-07) + 1.94656546234155e-05;
	fConst41 = 1.0 / fConst40;
	double fConst42 = 2.08223456923865e-05 * fConst0;
	double fConst43 = fConst42 + 0.000527406765446517;
	fConst44 = (0.000527406765446517 - fConst42) / fConst43;
	fConst45 = 2.06179485600366e-05 * (fConst0 / fConst43);
	fConst46 = 5.51041967277497e-09 * (fConst3 / fConst40);
	fConst47 = fConst0 * (fConst28 + 1.59012835323858e-05);
	fConst48 = fConst0 * (fConst30 + 7.50903344506575e-07);
	fConst49 = 1.89077966855745e-05 * (fConst0 / fConst25);
	fConst50 = 9.4e-08 * fConst0;
	fConst51 = 0.45081801796277066 / fConst22;
	fConst52 = 4.37684801272465e-10 * fConst3;
	fConst53 = fConst52 + 0.00107562519972983;
	fConst54 = fConst0 * (5.20602596669238e-08 - fConst12) + 0.000537812599864916;
	fConst55 = fConst0 * (fConst12 + 2.33324618325395e-07);
	fConst56 = 8.52062719537733e-10 * fConst3;
	double fConst57 = 4.26031359768866e-10 * fConst0;
	fConst58 = fConst57 + -2.06011295826338e-10;
	fConst59 = fConst57 + 2.06011295826338e-10;
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double fSlow0 = 0.007000000000000006 * double(fVslider0);
	double fSlow1 = 0.002198000000000002 * double(fHslider0);
	double fSlow2 = 0.007000000000000006 * std::pow(1e+01, 0.05 * double(fHslider1));
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		fRec1[0] = fSlow0 + 0.993 * fRec1[1];
		double fTemp0 = fConst11 + fRec1[0] * (fConst9 + fConst7 * fRec1[0] + 0.000537812599864916) + 0.00114855258827151;
		fRec5[0] = fSlow1 + 0.993 * fRec5[1];
		double fTemp1 = fConst27 * fRec5[0];
		double fTemp2 = fConst31 + fRec5[0] * (fConst29 - fTemp1) + 0.000169198590470162;
		double fTemp3 = fConst3 * (fRec5[0] * (6.36186700167807e-10 * fRec5[0] + -6.0628592525992e-10) + -2.99007749078869e-11);
		fRec8[0] = double(buf[i0]) - fConst44 * fRec8[1];
		fRec7[0] = fConst45 * (fRec8[0] - fRec8[1]) - fConst41 * (fConst39 * fRec7[1] + fConst38 * fRec7[2] + fConst37 * fRec7[3]);
		fRec6[0] = -(fConst46 * (fRec7[3] + (fRec7[0] - fRec7[1] - fRec7[2])) + (fRec6[1] * (fTemp3 + 0.000338397180940324) + fRec6[2] * (fConst35 + fRec5[0] * (fConst34 - fTemp1) + 0.000169198590470162)) / fTemp2);
		fRec4[0] = 0.3183098861837907 * std::atan((fRec6[0] * (fConst48 + fRec5[0] * (fConst47 - fTemp1) + 0.000169198590470161) + fRec6[1] * (fTemp3 + 0.000338397180940323) + fRec6[2] * (fConst33 + fRec5[0] * (fConst32 - fTemp1) + 0.000169198590470161)) / fTemp2) - fConst26 * fRec4[1];
		double fTemp4 = fConst49 * (fRec4[0] - fRec4[1]);
		double fTemp5 = opamp(fTemp4);
		double fTemp6 = 1.0 - fRec5[0];
		double fTemp7 = fConst50 * (1e+05 * fTemp6 + 4.7e+03);
		double fTemp8 = fConst50 * (1e+05 * (fTemp6 + fRec5[0] + 1.0) + 4.7e+03);
		double fTemp9 = fTemp4 - fTemp5;
		fVec0[0] = fTemp9;
		fRec9[0] = -((fRec9[1] * (1.0 - fTemp7) - (fTemp9 * (fTemp8 + 1.0) + fVec0[1] * (1.0 - fTemp8))) / (fTemp7 + 1.0));
		fRec3[0] = asymhardclip2(fTemp4 - (fTemp5 + opamp(fRec9[0] + fTemp5 - fTemp4))) - fConst23 * fRec3[1];
		fRec2[0] = fConst51 * (fRec3[0] + fRec3[1]) - (fRec2[1] * (fRec1[0] * (fConst20 * fRec1[0] + 0.00107562519972983 - fConst19) + 0.00229710517654303 - fConst18) + fRec2[2] * (fConst17 + fRec1[0] * (fConst16 + fConst15 * fRec1[0] + 0.000537812599864916) + 0.00114855258827151)) / fTemp0;
		fRec0[0] = (fRec2[0] * (fConst55 + fConst54 * fRec1[0] + 0.000182856283954071) + fRec2[1] * (fConst53 * fRec1[0] + 0.000365712567908143 - fConst52) + fRec2[2] * (fConst14 + fConst13 * fRec1[0] + 0.000182856283954071)) / fTemp0 - fConst5 * (fConst4 * fRec0[1] + fConst2 * fRec0[2]);
		fRec10[0] = fSlow2 + 0.993 * fRec10[1];
		buf[i0] = FAUSTFLOAT(fConst5 * fRec10[0] * (fConst0 * (fConst59 * fRec0[0] + fConst58 * fRec0[2]) - fConst56 * fRec0[1]));
		fRec1[1] = fRec1[0];
		fRec5[1] = fRec5[0];
		fRec8[1] = fRec8[0];
		for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
			fRec7[j0] = fRec7[j0 - 1];
		}
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec4[1] = fRec4[0];
		fVec0[1] = fVec0[0];
		fRec9[1] = fRec9[0];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		fRec10[1] = fRec10[0];
	}
	smp.down(buf, output0);
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("bossds1.Level",N_("Level"),"S","",&fHslider1, 3.0, -2e+01, 12.0, 0.1, 0);
	reg.registerFloatVar("bossds1.Tone",N_("Tone"),"S","",&fVslider0, 0.7, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("bossds1.drive",N_("Drive"),"S","",&fHslider0, 0.5, 0.0, 1.0, 0.01, 0);
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
                        <property name=\"var_id\">bossds1.drive</property>\n\
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
                        <property name=\"var_id\">bossds1.Level</property>\n\
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
                        <property name=\"var_id\">bossds1.Tone</property>\n\
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
                <property name=\"var_id\">bossds1.drive</property>\n\
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
#define PARAM(p) ("bossds1" "." p)

b.openHorizontalhideBox("");
    b.create_small_rackknobr(PARAM("drive"), "Distortion");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("drive"), "Distortion");
    b.create_small_rackknobr(PARAM("Level"), "Level");

    b.create_small_rackknobr(PARAM("Tone"), "Tone");
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

} // end namespace bossds1
} // end namespace pluginlib
