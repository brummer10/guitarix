// generated from file '../src/plugins/bossds1.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "clipping.h"

namespace pluginlib {
namespace bossds1 {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int samplingFreq;
	int fSamplingFreq;
	double fConst0;
	double fConst1;
	double fConst2;
	FAUSTFLOAT fHslider0;
	double fRec0[2];
	double fConst3;
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
	double fRec7[2];
	double fConst24;
	double fConst25;
	double fConst26;
	double fRec6[4];
	FAUSTFLOAT fHslider1;
	double fRec8[2];
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fRec5[3];
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fRec4[2];
	double fConst38;
	double fVec0[2];
	double fRec9[2];
	double fConst39;
	double fRec3[2];
	FAUSTFLOAT fVslider0;
	double fRec10[2];
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
	double fRec2[3];
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fRec1[3];
	double fConst61;
	double fConst62;

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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec7[l1] = 0.0;
	for (int l2 = 0; (l2 < 4); l2 = (l2 + 1)) fRec6[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec8[l3] = 0.0;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec5[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec4[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fVec0[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec9[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec3[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec10[l9] = 0.0;
	for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) fRec2[l10] = 0.0;
	for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) fRec1[l11] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int RsamplingFreq)
{
	samplingFreq = 96000;
	smp.setup(RsamplingFreq, samplingFreq);
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = (4.3388393179513799e-10 * fConst0);
	fConst2 = (1.0 / (((fConst1 + 6.9041200790990803e-09) * fConst0) + 2.3380205663140299e-08));
	fConst3 = (4.2603135976886602e-10 * fConst0);
	fConst4 = ((fConst3 + 2.06011295826338e-10) * fConst0);
	fConst5 = (1.4042807475010899e-05 * fConst0);
	fConst6 = (fConst5 + 0.32594524119947799);
	fConst7 = (0.45081801796277066 / fConst6);
	fConst8 = (2.0798576354131901e-05 * fConst0);
	fConst9 = (fConst8 + 0.0016683350016683299);
	fConst10 = (1.0 / fConst9);
	fConst11 = (1.8907796685574499e-05 * fConst0);
	fConst12 = (0.0 - fConst11);
	fConst13 = (3.5398265163483301e-10 * fConst0);
	fConst14 = (1.0 / (((fConst13 + 2.3858234950004601e-07) * fConst0) + 1.94656546234155e-05));
	fConst15 = mydsp_faustpower2_f(fConst0);
	fConst16 = (5.5104196727749697e-09 * fConst15);
	fConst17 = (0.0 - fConst16);
	fConst18 = (2.0822345692386498e-05 * fConst0);
	fConst19 = (fConst18 + 0.00052740676544651695);
	fConst20 = (1.0 / fConst19);
	fConst21 = (2.0617948560036602e-05 * fConst0);
	fConst22 = (0.0 - fConst21);
	fConst23 = ((0.00052740676544651695 - fConst18) / fConst19);
	fConst24 = (((2.3858234950004601e-07 - fConst13) * fConst0) + 5.8396963870246599e-05);
	fConst25 = (((-2.3858234950004601e-07 - fConst13) * fConst0) + 5.8396963870246599e-05);
	fConst26 = (((fConst13 + -2.3858234950004601e-07) * fConst0) + 1.94656546234155e-05);
	fConst27 = (1.4950387453943399e-11 * fConst0);
	fConst28 = (fConst27 + -1.66555708487018e-05);
	fConst29 = (3.0314296262996001e-10 * fConst0);
	fConst30 = (fConst29 + 3.38397180940322e-09);
	fConst31 = (fConst27 + 1.66555708487018e-05);
	fConst32 = (fConst29 + -3.38397180940322e-09);
	fConst33 = (fConst27 + 7.5090334450657498e-07);
	fConst34 = (fConst29 + 1.5901283532385801e-05);
	fConst35 = (fConst27 + -7.5090334450657498e-07);
	fConst36 = (fConst29 + -1.5901283532385801e-05);
	fConst37 = ((0.0016683350016683299 - fConst8) / fConst9);
	fConst38 = (9.3999999999999995e-08 * fConst0);
	fConst39 = ((0.32594524119947799 - fConst5) / fConst6);
	fConst40 = ((5.7928870756649804e-10 * fConst15) + -0.0010756251997298301);
	fConst41 = (5.31143379426527e-10 * fConst15);
	fConst42 = (6.7557936384644e-10 * fConst15);
	fConst43 = (3.3778968192322e-10 * fConst0);
	fConst44 = ((fConst43 + -1.5555982487546801e-06) * fConst0);
	fConst45 = (2.6557168971326298e-10 * fConst0);
	fConst46 = ((fConst45 + -7.5042497934431299e-07) * fConst0);
	fConst47 = (2.8964435378324902e-10 * fConst0);
	fConst48 = (((9.4439892536279197e-07 - fConst47) * fConst0) + -0.00053781259986491602);
	fConst49 = ((fConst43 + 1.5555982487546801e-06) * fConst0);
	fConst50 = ((fConst45 + 7.5042497934431299e-07) * fConst0);
	fConst51 = (((-9.4439892536279197e-07 - fConst47) * fConst0) + -0.00053781259986491602);
	fConst52 = (2.1884240063623301e-10 * fConst0);
	fConst53 = ((fConst52 + 2.3332461832539501e-07) * fConst0);
	fConst54 = (((5.2060259666923803e-08 - fConst52) * fConst0) + 0.00053781259986491602);
	fConst55 = (4.3768480127246498e-10 * fConst15);
	fConst56 = (fConst55 + 0.0010756251997298301);
	fConst57 = ((fConst52 + -2.3332461832539501e-07) * fConst0);
	fConst58 = (((-5.2060259666923803e-08 - fConst52) * fConst0) + 0.00053781259986491602);
	fConst59 = (4.6760411326280498e-08 - (8.6776786359027599e-10 * fConst15));
	fConst60 = (((fConst1 + -6.9041200790990803e-09) * fConst0) + 2.3380205663140299e-08);
	fConst61 = (0.0 - (8.5206271953773298e-10 * fConst15));
	fConst62 = ((fConst3 + -2.06011295826338e-10) * fConst0);
	fHslider0 = FAUSTFLOAT(3.0);
	fHslider1 = FAUSTFLOAT(0.5);
	fVslider0 = FAUSTFLOAT(0.69999999999999996);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double fSlow0 = (0.0070000000000000062 * std::pow(10.0, (0.050000000000000003 * double(fHslider0))));
	double fSlow1 = (0.002198000000000002 * double(fHslider1));
	double fSlow2 = (0.0070000000000000062 * double(fVslider0));
	for (int i = 0; (i < ReCount); i = (i + 1)) {
		fRec0[0] = (fSlow0 + (0.99299999999999999 * fRec0[1]));
		fRec7[0] = (double(buf[i]) - (fConst23 * fRec7[1]));
		fRec6[0] = ((fConst20 * ((fConst22 * fRec7[1]) + (fConst21 * fRec7[0]))) - (fConst14 * (((fConst24 * fRec6[1]) + (fConst25 * fRec6[2])) + (fConst26 * fRec6[3]))));
		fRec8[0] = (fSlow1 + (0.99299999999999999 * fRec8[1]));
		double fTemp0 = (fConst15 * ((fRec8[0] * ((6.3618670016780696e-10 * fRec8[0]) + -6.0628592525992003e-10)) + -2.9900774907886902e-11));
		double fTemp1 = (fConst0 * (0.0 - (3.18093350083904e-10 * fRec8[0])));
		double fTemp2 = ((fConst0 * (fConst31 + (fRec8[0] * (fConst32 + fTemp1)))) + 0.00016919859047016201);
		fRec5[0] = ((fConst14 * ((((fConst17 * fRec6[0]) + (fConst16 * fRec6[1])) + (fConst16 * fRec6[2])) + (fConst17 * fRec6[3]))) - (((fRec5[1] * (fTemp0 + 0.00033839718094032402)) + (fRec5[2] * ((fConst0 * (fConst28 + (fRec8[0] * (fConst30 + fTemp1)))) + 0.00016919859047016201))) / fTemp2));
		fRec4[0] = ((0.31830988618379069 * std::atan(((((fRec5[0] * ((fConst0 * (fConst33 + (fRec8[0] * (fConst34 + fTemp1)))) + 0.00016919859047016101)) + (fRec5[1] * (fTemp0 + 0.00033839718094032299))) + (fRec5[2] * ((fConst0 * (fConst35 + (fRec8[0] * (fConst36 + fTemp1)))) + 0.00016919859047016101))) / fTemp2))) - (fConst37 * fRec4[1]));
		double fTemp3 = (fConst10 * ((fConst12 * fRec4[1]) + (fConst11 * fRec4[0])));
		double fTemp4 = double(opamp(double(fTemp3)));
		double fTemp5 = (1.0 - fRec8[0]);
		double fTemp6 = (fConst38 * ((100000.0 * fTemp5) + 4700.0));
		double fTemp7 = (fTemp3 - fTemp4);
		fVec0[0] = fTemp7;
		double fTemp8 = (fConst38 * ((100000.0 * (fTemp5 + (fRec8[0] + 1.0))) + 4700.0));
		fRec9[0] = (0.0 - (((fRec9[1] * (1.0 - fTemp6)) - ((fTemp7 * (fTemp8 + 1.0)) + (fVec0[1] * (1.0 - fTemp8)))) / (fTemp6 + 1.0)));
		fRec3[0] = (double(asymhardclip2(double((fTemp3 - (fTemp4 + double(opamp(double(((fRec9[0] + fTemp4) - fTemp3))))))))) - (fConst39 * fRec3[1]));
		fRec10[0] = (fSlow2 + (0.99299999999999999 * fRec10[1]));
		double fTemp9 = (fConst49 + ((fRec10[0] * (fConst50 + ((fConst51 * fRec10[0]) + 0.00053781259986491602))) + 0.00114855258827151));
		fRec2[0] = ((fConst7 * (fRec3[0] + fRec3[1])) - (((fRec2[1] * (((fRec10[0] * (((fConst40 * fRec10[0]) + 0.0010756251997298301) - fConst41)) + 0.00229710517654303) - fConst42)) + (fRec2[2] * (fConst44 + ((fRec10[0] * (fConst46 + ((fConst48 * fRec10[0]) + 0.00053781259986491602))) + 0.00114855258827151)))) / fTemp9));
		fRec1[0] = (((((fRec2[0] * (fConst53 + ((fConst54 * fRec10[0]) + 0.00018285628395407099))) + (fRec2[1] * (((fConst56 * fRec10[0]) + 0.00036571256790814301) - fConst55))) + (fRec2[2] * (fConst57 + ((fConst58 * fRec10[0]) + 0.00018285628395407099)))) / fTemp9) - (fConst2 * ((fConst59 * fRec1[1]) + (fConst60 * fRec1[2]))));
		buf[i] = FAUSTFLOAT((fConst2 * (fRec0[0] * (((fConst4 * fRec1[0]) + (fConst61 * fRec1[1])) + (fConst62 * fRec1[2])))));
		fRec0[1] = fRec0[0];
		fRec7[1] = fRec7[0];
		for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
			fRec6[j0] = fRec6[(j0 - 1)];
		}
		fRec8[1] = fRec8[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fVec0[1] = fVec0[0];
		fRec9[1] = fRec9[0];
		fRec3[1] = fRec3[0];
		fRec10[1] = fRec10[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
	}
	smp.down(buf, output0);
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("bossds1.Level",N_("Level"),"S","",&fHslider0, 3.0, -20.0, 12.0, 0.10000000000000001);
	reg.registerVar("bossds1.Tone",N_("Tone"),"S","",&fVslider0, 0.69999999999999996, 0.0, 1.0, 0.01);
	reg.registerVar("bossds1.drive",N_("Drive"),"S","",&fHslider1, 0.5, 0.0, 1.0, 0.01);
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
