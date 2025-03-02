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
	double fRec0[2];
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	FAUSTFLOAT fVslider1;
	double fRec1[2];
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
	FAUSTFLOAT fVslider2;
	double fRec2[5];
	double fConst34;
	FAUSTFLOAT fVslider3;
	double fRec3[2];


	gx_resample::FixedRateResampler smpCl;
	double fConstCl0;
	double fConstCl1;
	double fConstCl2;
	double fConstCl3;
	double fVecCl0[2];
	double fRecCl7[2];
	double fRecCl6[3];
	double fConstCl4;
	double fConstCl5;
	double fConstCl6;
	double fRecCl8[2];
	double fRecCl5[3];
	double fConstCl7;
	double fConstCl8;
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec1[l1] = 0.0;
	for (int l2 = 0; l2 < 5; l2 = l2 + 1) fRec2[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec3[l3] = 0.0;

	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fVecCl0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRecCl7[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRecCl6[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRecCl8[l3] = 0.0;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRecCl5[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRecCl4[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRecCl3[l6] = 0.0;
	for (int l7 = 0; l7 < 3; l7 = l7 + 1) fRecCl2[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRecCl9[l8] = 0.0;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRecCl1[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRecCl0[l10] = 0.0;

}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 1.8235902618655e-20 * fConst0;
	fConst2 = fConst0 * (fConst0 * (fConst1 + 8.73857822258011e-15) + 9.51587528271067e-12) + 4.14452332248826e-10;
	fConst3 = 1.90624114055858e-19 * fConst0;
	fConst4 = fConst0 * (fConst0 * (-9.05150991318089e-15 - fConst3) + -9.57238853136628e-11);
	fConst5 = fConst0 * (fConst0 * (fConst3 + 1.0005063720083e-14) + 1.41002006493022e-10);
	fConst6 = fConst0 * (fConst0 * (fConst0 * (-8.82979918090661e-15 - fConst1) + -5.32286268006641e-11) + -2.42569918771087e-09) + -9.41937118747331e-10;
	fConst7 = 1.65780932898435e-16 * fConst0;
	fConst8 = fConst7 + -8.29281439339673e-13;
	fConst9 = 7.76911913609341e-14 * fConst0;
	fConst10 = mydsp_faustpower2_f(fConst0);
	fConst11 = mydsp_faustpower3_f(fConst0);
	fConst12 = fConst4 + -4.70914107604798e-09;
	fConst13 = fConst5 + 6.98583678876617e-09;
	fConst14 = fConst0 * (fConst0 * (fConst1 + -8.73857822258011e-15) + 9.51587528271067e-12) + -4.14452332248826e-10;
	fConst15 = fConst0 * (fConst0 * (9.05150991318089e-15 - fConst3) + -9.57238853136628e-11) + 4.70914107604798e-09;
	fConst16 = fConst0 * (fConst0 * (fConst3 + -1.0005063720083e-14) + 1.41002006493022e-10) + -6.98583678876617e-09;
	fConst17 = fConst0 * (fConst0 * (fConst0 * (8.82979918090661e-15 - fConst1) + -5.32286268006641e-11) + 2.42569918771087e-09) + -9.41937118747331e-10;
	fConst18 = 7.294361047462e-20 * fConst0;
	fConst19 = fConst10 * (1.74771564451602e-14 - fConst18) + -8.28904664497652e-10;
	fConst20 = 7.6249645622343e-19 * fConst0;
	fConst21 = fConst10 * (fConst20 + -1.81030198263618e-14) + 9.41828215209595e-09;
	fConst22 = fConst10 * (2.00101274401661e-14 - fConst20) + -1.39716735775323e-08;
	fConst23 = fConst0 * (fConst10 * (fConst18 + -1.76595983618132e-14) + 4.85139837542174e-09) + -3.76774847498933e-09;
	fConst24 = 1.0941541571193e-19 * fConst10;
	fConst25 = fConst24 + -1.90317505654213e-11;
	fConst26 = 1.14374468433515e-18 * fConst10;
	fConst27 = 1.91447770627326e-10 - fConst26;
	fConst28 = fConst26 + -2.82004012986045e-10;
	fConst29 = fConst10 * (1.06457253601328e-10 - fConst24) + -5.65162271248399e-09;
	fConst30 = fConst10 * (-1.74771564451602e-14 - fConst18) + 8.28904664497652e-10;
	fConst31 = fConst10 * (fConst20 + 1.81030198263618e-14) + -9.41828215209595e-09;
	fConst32 = fConst10 * (-2.00101274401661e-14 - fConst20) + 1.39716735775323e-08;
	fConst33 = fConst0 * (fConst10 * (fConst18 + 1.76595983618132e-14) + -4.85139837542174e-09) + -3.76774847498933e-09;
	fConst34 = -8.29281439339673e-13 - fConst7;

	sample_rate = 96000;
	smpCl.setup(fSampleRate, sample_rate);
	fSampleRate = sample_rate;
	fConstCl0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConstCl1 = std::tan(97.38937226128358 / fConstCl0);
	fConstCl2 = 1.0 / fConstCl1;
	fConstCl3 = 1.0 - fConstCl2;
	fConstCl4 = 1.0 / std::tan(270.1769682087222 / fConstCl0);
	fConstCl5 = 1.0 - fConstCl4;
	fConstCl6 = 1.0 / (fConstCl4 + 1.0);
	fConstCl7 = 0.025 / fConstCl1;
	fConstCl8 = 1.0 / (fConstCl2 + 1.0);

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
	double fSlow2 = 0.01 * double(fVslider2);
	double fSlow3 = 0.007000000000000006 * double(fVslider3);
	double fSlow4 = 1.0 - fSlow2;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		double fTemp0 = fConst2 * fRec0[0];
		fRec1[0] = fSlow1 + 0.993 * fRec1[1];
		double fTemp1 = fConst6 * fRec0[0];
		double fTemp2 = 1.65780932898435e-16 * fRec0[0];
		double fTemp3 = double(input0[i0]);
		fRec2[0] = fSlow2 * fTemp3 - (fRec2[1] * (fConst33 * fRec0[0] + fConst0 * (fConst32 + fRec1[0] * (fConst31 + fConst30 * fRec0[0])) + 4.2810373418618e-08) + fRec2[2] * (fConst29 * fRec0[0] + fConst10 * (fConst28 + fRec1[0] * (fConst27 + fConst25 * fRec0[0])) + 6.4215560127927e-08) + fRec2[3] * (fConst23 * fRec0[0] + fConst0 * (fConst22 + fRec1[0] * (fConst21 + fConst19 * fRec0[0])) + 4.2810373418618e-08) + fRec2[4] * (fConst17 * fRec0[0] + fConst0 * (fConst16 + fRec1[0] * (fConst15 + fConst14 * fRec0[0])) + 1.07025933546545e-08)) / (fTemp1 + fConst0 * (fConst13 + fRec1[0] * (fConst12 + fTemp0)) + 1.07025933546545e-08);
		double fTemp4 = 3.3156186579687e-16 * fRec0[0];
		double fTemp5 = -1.55382382721868e-13 - fTemp4;
		fRec3[0] = fSlow3 + 0.993 * fRec3[1];
		output0[i0] = FAUSTFLOAT(fSlow4 * fTemp3 + fRec3[0] * (fConst10 * fRec2[2] * (1.65856287867935e-12 * fRec0[0] + 7.77265055388254e-10) + fRec2[0] * (fConst11 * fRec1[0] * (fTemp2 + 7.76911913609341e-14) + fConst10 * (fConst34 * fRec0[0] + -3.88632527694127e-10 - fConst9)) + fConst11 * (fRec2[1] * (fTemp4 + fRec1[0] * fTemp5 + 1.55382382721868e-13) + fRec2[3] * (fRec1[0] * (fTemp4 + 1.55382382721868e-13) + fTemp5)) + fRec2[4] * (fConst11 * fRec1[0] * (-7.76911913609341e-14 - fTemp2) + fConst10 * (fConst9 + fConst8 * fRec0[0] + -3.88632527694127e-10))) / (fTemp1 + fConst0 * (fConst5 + fRec1[0] * (fConst4 + fTemp0 + -4.70914107604798e-09) + 6.98583678876617e-09) + 1.07025933546545e-08));
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		for (int j0 = 4; j0 > 0; j0 = j0 - 1) {
			fRec2[j0] = fRec2[j0 - 1];
		}
		fRec3[1] = fRec3[0];
	}

	FAUSTFLOAT bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		double fTemp0 = double(bufCl[i0]);
		fVecCl0[0] = fTemp0;
		fRecCl7[0] = 0.9302847925323914 * (fTemp0 + fVecCl0[1]) - 0.8605695850647829 * fRecCl7[1];
		fRecCl6[0] = fRecCl7[0] - (1.8405051250752198 * fRecCl6[1] + 0.8612942439318627 * fRecCl6[2]);
		fRecCl8[0] = fConstCl6 * (0.027 * (fRecCl5[1] + fRecCl5[2]) - fConstCl5 * fRecCl8[1]);
		fRecCl5[0] = Ftrany(TRANY_TABLE_7199P_68k, 0.9254498422517706 * (fRecCl6[0] + fRecCl6[2]) + fRecCl8[0] + 1.8508996845035413 * fRecCl6[1] + -3.571981) + -117.70440740740739;
		fRecCl4[0] = fConstCl8 * (fConstCl7 * (fRecCl5[0] - fRecCl5[1]) - fConstCl3 * fRecCl4[1]);
		fRecCl3[0] = 0.9302847925323914 * (fRecCl4[0] + fRecCl4[1]) - 0.8605695850647829 * fRecCl3[1];
		fRecCl2[0] = fRecCl3[0] - (1.8405051250752198 * fRecCl2[1] + 0.8612942439318627 * fRecCl2[2]);
		fRecCl9[0] = fConstCl6 * (0.027 * (fRecCl1[1] + fRecCl1[2]) - fConstCl5 * fRecCl9[1]);
		fRecCl1[0] = Ftrany(TRANY_TABLE_7199P_68k, 0.9254498422517706 * (fRecCl2[0] + fRecCl2[2]) + fRecCl9[0] + 1.8508996845035413 * fRecCl2[1] + -3.571981) + -117.70440740740739;
		fRecCl0[0] = fConstCl8 * (fConstCl7 * (fRecCl1[0] - fRecCl1[1]) - fConstCl3 * fRecCl0[1]);
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
	reg.registerFloatVar("bfuzz.Drive",N_("Drive"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("bfuzz.Level",N_("Level"),"S","",&fVslider3, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("bfuzz.Thickness",N_("Thickness"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("bfuzz.wet_dry",N_("Wet/Dry"),"S",N_("percentage of processed signal in output signal"),&fVslider2, 1e+02, 0.0, 1e+02, 1.0, 0);
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
