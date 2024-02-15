// generated from file '../src/plugins/hornet.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace pluginlib {
namespace hornet {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	double fRec0[2];
	double fConst0;
	double fConst2;
	double fConst4;
	double fConst6;
	double fConst8;
	double fConst10;
	double fConst12;
	FAUSTFLOAT fVslider1;
	double fRec1[2];
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst18;
	double fConst19;
	double fConst21;
	double fConst22;
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
	double fConst36;
	double fConst38;
	double fConst40;
	double fConst42;
	double fConst44;
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
	double fRec2[5];
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst63;
	double fConst64;
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
	FAUSTFLOAT fVslider2;
	double fRec3[2];

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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec1[l1] = 0.0;
	for (int l2 = 0; l2 < 5; l2 = l2 + 1) fRec2[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec3[l3] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 2.57087433571955e-21 * fConst0;
	fConst2 = fConst0 * (fConst0 * (-3.20282580029198e-16 - fConst1) + -1.59955479510613e-12) + -1.59265781983301e-11;
	double fConst3 = 7.22415688337201e-22 * fConst0;
	fConst4 = fConst0 * (fConst0 * (fConst3 + 1.15708148345401e-16) + 5.83730418035165e-13);
	double fConst5 = 1.84845864738235e-21 * fConst0;
	fConst6 = fConst0 * (fConst0 * (fConst5 + 2.48814775695488e-16) + 1.25274019677064e-12);
	double fConst7 = 2.22731835703847e-20 * fConst0;
	fConst8 = fConst0 * (fConst0 * (-1.15680872556631e-16 - fConst7) + -1.02110226030461e-14) + -8.86189120121937e-14;
	double fConst9 = 2.63346198155234e-19 * fConst0;
	fConst10 = fConst0 * (fConst0 * (fConst9 + 1.39560593212619e-15) + 1.23553821745518e-13);
	double fConst11 = 2.00860283725342e-19 * fConst0;
	fConst12 = fConst0 * (fConst0 * (fConst11 + 1.06638545237487e-15) + 1.10730441129884e-13);
	double fConst13 = 2.89798007739403e-18 * fConst0;
	fConst14 = fConst13 + -1.51064918927987e-14;
	fConst15 = 2.28655633153439e-18 * fConst0;
	fConst16 = mydsp_faustpower3_f(fConst0);
	double fConst17 = 1.45891323583538e-19 * fConst0;
	fConst18 = mydsp_faustpower2_f(fConst0);
	fConst19 = fConst18 * (fConst0 * (fConst17 + -7.40489463150802e-16) + -1.04296301457845e-13);
	double fConst20 = 3.36831187151837e-20 * fConst0;
	fConst21 = 1.75582214579149e-16 - fConst20;
	fConst22 = 9.4649563589667e-21 * fConst0;
	double fConst23 = 2.4218162356217e-20 * fConst0;
	fConst24 = fConst18 * (fConst0 * (fConst23 + -1.26859583357635e-16) + 3.21091305171869e-15);
	fConst25 = fConst4 + 5.81517816570128e-12;
	fConst26 = fConst6 + 4.3094216014379e-11;
	fConst27 = fConst10 + 1.09557219057811e-12;
	fConst28 = fConst12 + 2.30413820563986e-12;
	fConst29 = fConst0 * (fConst0 * (3.20282580029198e-16 - fConst1) + -1.59955479510613e-12) + 1.59265781983301e-11;
	fConst30 = fConst0 * (fConst0 * (fConst3 + -1.15708148345401e-16) + 5.83730418035165e-13) + -5.81517816570128e-12;
	fConst31 = fConst0 * (fConst0 * (fConst5 + -2.48814775695488e-16) + 1.25274019677064e-12) + -4.3094216014379e-11;
	fConst32 = fConst0 * (fConst0 * (1.15680872556631e-16 - fConst7) + -1.02110226030461e-14) + 8.86189120121937e-14;
	fConst33 = fConst0 * (fConst0 * (fConst9 + -1.39560593212619e-15) + 1.23553821745518e-13) + -1.09557219057811e-12;
	fConst34 = fConst0 * (fConst0 * (fConst11 + -1.06638545237487e-15) + 1.10730441129884e-13) + -2.30413820563986e-12;
	double fConst35 = 1.02834973428782e-20 * fConst0;
	fConst36 = fConst18 * (fConst35 + -6.40565160058397e-16) + 3.18531563966602e-11;
	double fConst37 = 2.8896627533488e-21 * fConst0;
	fConst38 = fConst18 * (2.31416296690802e-16 - fConst37) + -1.16303563314026e-11;
	double fConst39 = 7.39383458952941e-21 * fConst0;
	fConst40 = fConst18 * (4.97629551390976e-16 - fConst39) + -8.6188432028758e-11;
	double fConst41 = 8.9092734281539e-20 * fConst0;
	fConst42 = fConst18 * (fConst41 + -2.31361745113263e-16) + 1.77237824024387e-13;
	double fConst43 = 1.05338479262093e-18 * fConst0;
	fConst44 = fConst18 * (2.79121186425238e-15 - fConst43) + -2.19114438115622e-12;
	double fConst45 = 8.03441134901368e-19 * fConst0;
	fConst46 = fConst18 * (2.13277090474974e-15 - fConst45) + -4.60827641127972e-12;
	fConst47 = 3.19910959021226e-12 - 1.54252460143173e-20 * fConst18;
	fConst48 = 4.33449413002321e-21 * fConst18 + -1.16746083607033e-12;
	fConst49 = 1.10907518842941e-20 * fConst18 + -2.50548039354128e-12;
	fConst50 = 2.04220452060922e-14 - 1.33639101422308e-19 * fConst18;
	fConst51 = 1.5800771889314e-18 * fConst18 + -2.47107643491035e-13;
	fConst52 = 1.20516170235205e-18 * fConst18 + -2.21460882259768e-13;
	fConst53 = fConst18 * (fConst35 + 6.40565160058397e-16) + -3.18531563966602e-11;
	fConst54 = fConst18 * (-2.31416296690802e-16 - fConst37) + 1.16303563314026e-11;
	fConst55 = fConst18 * (-4.97629551390976e-16 - fConst39) + 8.6188432028758e-11;
	fConst56 = fConst18 * (fConst41 + 2.31361745113263e-16) + -1.77237824024387e-13;
	fConst57 = fConst18 * (-2.79121186425238e-15 - fConst43) + 2.19114438115622e-12;
	fConst58 = fConst18 * (-2.13277090474974e-15 - fConst45) + 4.60827641127972e-12;
	fConst59 = 9.6872649424868e-20 * fConst0;
	fConst60 = 5.83565294334152e-19 * fConst0;
	fConst61 = 9.14622532613756e-18 * fConst0;
	double fConst62 = 1.15919203095761e-17 * fConst0;
	fConst63 = 3.02129837855973e-14 - fConst62;
	fConst64 = 3.78598254358668e-20 * fConst0;
	double fConst65 = 1.34732474860735e-19 * fConst0;
	fConst66 = fConst65 + -3.51164429158298e-16;
	fConst67 = -3.02129837855973e-14 - fConst62;
	fConst68 = fConst65 + 3.51164429158298e-16;
	fConst69 = fConst13 + 1.51064918927987e-14;
	fConst70 = fConst18 * (fConst0 * (fConst17 + 7.40489463150802e-16) + -1.04296301457845e-13);
	fConst71 = -1.75582214579149e-16 - fConst20;
	fConst72 = fConst18 * (fConst0 * (fConst23 + 1.26859583357635e-16) + 3.21091305171869e-15);
	fConst73 = mydsp_faustpower4_f(fConst0);
	fConst74 = fConst18 * (8.75347941501228e-19 * fConst18 + 2.08592602915691e-13);
	fConst75 = fConst18 * (1.45308974137302e-19 * fConst18 + -6.42182610343738e-15);
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = 0.007000000000000006 * double(fVslider0);
	double fSlow1 = 0.007000000000000006 * double(fVslider1);
	double fSlow2 = 0.007000000000000006 * double(fVslider2);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		double fTemp0 = fConst2 * fRec0[0];
		double fTemp1 = fConst8 * fRec0[0];
		fRec1[0] = fSlow1 + 0.993 * fRec1[1];
		fRec2[0] = double(input0[i0]) - (fRec2[1] * (fRec1[0] * (fConst0 * (fConst58 + fRec0[0] * (fConst57 + fConst56 * fRec0[0])) + 5.20428164277295e-11) + fConst0 * (fConst55 + fRec0[0] * (fConst54 + fConst53 * fRec0[0])) + 1.22202543042127e-09) + fRec2[2] * (fRec1[0] * (fConst18 * (fConst52 + fRec0[0] * (fConst51 + fConst50 * fRec0[0])) + 7.80642246415943e-11) + fConst18 * (fConst49 + fRec0[0] * (fConst48 + fConst47 * fRec0[0])) + 1.83303814563191e-09) + fRec2[3] * (fRec1[0] * (fConst0 * (fConst46 + fRec0[0] * (fConst44 + fConst42 * fRec0[0])) + 5.20428164277295e-11) + fConst0 * (fConst40 + fRec0[0] * (fConst38 + fConst36 * fRec0[0])) + 1.22202543042127e-09) + fRec2[4] * (fRec1[0] * (fConst0 * (fConst34 + fRec0[0] * (fConst33 + fConst32 * fRec0[0])) + 1.30107041069324e-11) + fConst0 * (fConst31 + fRec0[0] * (fConst30 + fConst29 * fRec0[0])) + 3.05506357605318e-10)) / (fRec1[0] * (fConst0 * (fConst28 + fRec0[0] * (fConst27 + fTemp1)) + 1.30107041069324e-11) + fConst0 * (fConst26 + fRec0[0] * (fConst25 + fTemp0)) + 3.05506357605318e-10);
		fRec3[0] = fSlow2 + 0.993 * fRec3[1];
		output0[i0] = FAUSTFLOAT(0.4 * std::min<double>(0.7514, std::max<double>(-0.4514, fRec3[0] * (fRec2[2] * (fConst75 + fConst73 * fRec0[0] * (5.67897381538002e-20 - 2.02098712291102e-19 * fRec0[0]) + fRec1[0] * (fConst74 + fConst73 * fRec0[0] * (1.73878804643642e-17 * fRec0[0] + 1.37193379892063e-17))) + fRec2[0] * (fConst72 + fConst16 * fRec0[0] * (fConst22 + fConst71 * fRec0[0] + 4.93386022967413e-17) + fRec1[0] * (fConst70 + fConst16 * fRec0[0] * (fConst15 + fConst69 * fRec0[0] + 1.19192830048069e-14))) + fConst16 * (fRec2[1] * (fRec0[0] * (fConst68 * fRec0[0] + -9.86772045934826e-17 - fConst64) + fRec1[0] * (fRec0[0] * (fConst67 * fRec0[0] + -2.38385660096139e-14 - fConst61) + -1.4809789263016e-15 - fConst60) + -2.53719166715271e-16 - fConst59) + fRec2[3] * (fRec0[0] * (fConst66 * fRec0[0] + 9.86772045934826e-17 - fConst64) + fRec1[0] * (fRec0[0] * (fConst63 * fRec0[0] + 2.38385660096139e-14 - fConst61) + 1.4809789263016e-15 - fConst60) + 2.53719166715271e-16 - fConst59)) + fRec2[4] * (fConst24 + fConst16 * fRec0[0] * (fConst22 + fConst21 * fRec0[0] + -4.93386022967413e-17) + fRec1[0] * (fConst19 + fConst16 * fRec0[0] * (fConst15 + fConst14 * fRec0[0] + -1.19192830048069e-14)))) / (fRec1[0] * (fConst0 * (fConst12 + fRec0[0] * (fConst10 + fTemp1 + 1.09557219057811e-12) + 2.30413820563986e-12) + 1.30107041069324e-11) + fConst0 * (fConst6 + fRec0[0] * (fConst4 + fTemp0 + 5.81517816570128e-12) + 4.3094216014379e-11) + 3.05506357605318e-10))));
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		for (int j0 = 4; j0 > 0; j0 = j0 - 1) {
			fRec2[j0] = fRec2[j0 - 1];
		}
		fRec3[1] = fRec3[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("hornet.Fuzz",N_("Fuzz"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("hornet.Level",N_("Level"),"S","",&fVslider2, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("hornet.Sustain",N_("Sustain"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
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
