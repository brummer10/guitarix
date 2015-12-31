// generated from file '../src/plugins/bfuzz.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace bfuzz {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider1;
	double 	fRec8[2];
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	FAUSTFLOAT 	fslider2;
	double 	fRec9[2];
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fRec10[5];
	double 	fConst33;
	double 	fConst34;
	FAUSTFLOAT 	fslider3;
	double 	fRec11[2];
	double 	fVec0[2];
	double 	fConst35;
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fRec12[2];
	double 	fRec5[3];
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fRec4[2];
	double 	fRec3[2];
	double 	fRec2[3];
	double 	fRec13[2];
	double 	fRec1[3];
	double 	fRec0[2];
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
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<5; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = double(iConst0);
	fConst2 = (1.90624114055858e-19 * fConst1);
	fConst3 = (6.98583678876617e-09 + (fConst1 * (1.41002006493022e-10 + (fConst1 * (1.0005063720083e-14 + fConst2)))));
	fConst4 = (1.8235902618655e-20 * fConst1);
	fConst5 = (4.14452332248826e-10 + (fConst1 * (9.51587528271067e-12 + (fConst1 * (8.73857822258011e-15 + fConst4)))));
	fConst6 = ((fConst1 * ((fConst1 * (0 - (9.05150991318089e-15 + fConst2))) - 9.57238853136628e-11)) - 4.70914107604798e-09);
	fConst7 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (8.82979918090661e-15 + fConst4))) - 5.32286268006641e-11)) - 2.42569918771087e-09)) - 9.41937118747331e-10);
	fConst8 = (1.65780932898435e-16 * fConst1);
	fConst9 = (fConst8 - 8.29281439339673e-13);
	fConst10 = (7.76911913609341e-14 * fConst1);
	fConst11 = (fConst10 - 3.88632527694127e-10);
	fConst12 = ((fConst1 * (1.41002006493022e-10 + (fConst1 * (fConst2 - 1.0005063720083e-14)))) - 6.98583678876617e-09);
	fConst13 = ((fConst1 * (9.51587528271067e-12 + (fConst1 * (fConst4 - 8.73857822258011e-15)))) - 4.14452332248826e-10);
	fConst14 = (4.70914107604798e-09 + (fConst1 * ((fConst1 * (9.05150991318089e-15 - fConst2)) - 9.57238853136628e-11)));
	fConst15 = ((fConst1 * (2.42569918771087e-09 + (fConst1 * ((fConst1 * (8.82979918090661e-15 - fConst4)) - 5.32286268006641e-11)))) - 9.41937118747331e-10);
	fConst16 = (7.6249645622343e-19 * fConst1);
	fConst17 = faustpower<2>(fConst1);
	fConst18 = ((fConst17 * (2.00101274401661e-14 - fConst16)) - 1.39716735775323e-08);
	fConst19 = (7.294361047462e-20 * fConst1);
	fConst20 = ((fConst17 * (1.74771564451602e-14 - fConst19)) - 8.28904664497652e-10);
	fConst21 = (9.41828215209595e-09 + (fConst17 * (fConst16 - 1.81030198263618e-14)));
	fConst22 = ((fConst1 * (4.85139837542174e-09 + (fConst17 * (fConst19 - 1.76595983618132e-14)))) - 3.76774847498933e-09);
	fConst23 = (1.0941541571193e-19 * fConst17);
	fConst24 = (fConst23 - 1.90317505654213e-11);
	fConst25 = (1.14374468433515e-18 * fConst17);
	fConst26 = (1.91447770627326e-10 - fConst25);
	fConst27 = (fConst25 - 2.82004012986045e-10);
	fConst28 = ((fConst17 * (1.06457253601328e-10 - fConst23)) - 5.65162271248399e-09);
	fConst29 = (1.39716735775323e-08 + (fConst17 * (0 - (2.00101274401661e-14 + fConst16))));
	fConst30 = (8.28904664497652e-10 + (fConst17 * (0 - (1.74771564451602e-14 + fConst19))));
	fConst31 = ((fConst17 * (1.81030198263618e-14 + fConst16)) - 9.41828215209595e-09);
	fConst32 = ((fConst1 * ((fConst17 * (1.76595983618132e-14 + fConst19)) - 4.85139837542174e-09)) - 3.76774847498933e-09);
	fConst33 = (0 - (8.29281439339673e-13 + fConst8));
	fConst34 = (0 - (3.88632527694127e-10 + fConst10));
	fConst35 = (0.9302847925323914 * fConst17);
	fConst36 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst37 = (1 + fConst36);
	fConst38 = (0.027 / fConst37);
	fConst39 = (0 - ((1 - fConst36) / fConst37));
	fConst40 = (1.0 / tan((34.55751918948772 / double(iConst0))));
	fConst41 = (0 - fConst40);
	fConst42 = (1 + fConst40);
	fConst43 = (0.025 / fConst42);
	fConst44 = (0 - ((1 - fConst40) / fConst42));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.01 * double(fslider0));
	double 	fSlow1 = (1 - fSlow0);
	double 	fSlow2 = (0.007000000000000006 * double(fslider1));
	double 	fSlow3 = (0.007000000000000006 * double(fslider2));
	double 	fSlow4 = (0.007000000000000006 * double(fslider3));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec8[0] = ((0.993 * fRec8[1]) + fSlow2);
		fRec9[0] = ((0.993 * fRec9[1]) + fSlow3);
		double fTemp1 = (1.07025933546545e-08 + ((fConst7 * fRec8[0]) + (fConst1 * ((fRec9[0] * (fConst6 + (fConst5 * fRec8[0]))) + fConst3))));
		double fTemp2 = (1.65780932898435e-16 * fRec8[0]);
		fRec10[0] = ((fSlow0 * fTemp0) - (((((fRec10[1] * (4.2810373418618e-08 + ((fConst32 * fRec8[0]) + (fConst1 * ((fRec9[0] * (fConst31 + (fConst30 * fRec8[0]))) + fConst29))))) + (fRec10[2] * (6.4215560127927e-08 + ((fConst28 * fRec8[0]) + (fConst17 * (fConst27 + (fRec9[0] * (fConst26 + (fConst24 * fRec8[0]))))))))) + (fRec10[3] * (4.2810373418618e-08 + ((fConst22 * fRec8[0]) + (fConst1 * ((fRec9[0] * (fConst21 + (fConst20 * fRec8[0]))) + fConst18)))))) + (fRec10[4] * (1.07025933546545e-08 + ((fConst15 * fRec8[0]) + (fConst1 * ((fRec9[0] * (fConst14 + (fConst13 * fRec8[0]))) + fConst12)))))) / fTemp1));
		double fTemp3 = (3.3156186579687e-16 * fRec8[0]);
		double fTemp4 = (1.55382382721868e-13 + fTemp3);
		double fTemp5 = ((0 - fTemp3) - 1.55382382721868e-13);
		fRec11[0] = ((0.993 * fRec11[1]) + fSlow4);
		double fTemp6 = ((fRec11[0] * (((((fRec10[0] * ((fConst34 + (fConst33 * fRec8[0])) + (fConst1 * (fRec9[0] * (7.76911913609341e-14 + fTemp2))))) + (fConst1 * (fRec10[1] * (fTemp4 + (fRec9[0] * fTemp5))))) + (fRec10[2] * (7.77265055388254e-10 + (1.65856287867935e-12 * fRec8[0])))) + (fConst1 * (fRec10[3] * (fTemp5 + (fRec9[0] * fTemp4))))) + (fRec10[4] * ((fConst11 + (fConst9 * fRec8[0])) + (fConst1 * (fRec9[0] * ((0 - fTemp2) - 7.76911913609341e-14))))))) / fTemp1);
		fVec0[0] = fTemp6;
		fRec7[0] = ((fConst35 * (fVec0[0] + fVec0[1])) - (0.8605695850647829 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.8612942439318627 * fRec6[2])));
		fRec12[0] = ((fConst39 * fRec12[1]) + (fConst38 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec12[0] + (0.9254498422517706 * (fRec6[2] + (fRec6[0] + (2.0 * fRec6[1]))))) - 5.571981)) - 43.63033333333331);
		fRec4[0] = ((fConst44 * fRec4[1]) + (fConst43 * ((fConst40 * fRec5[0]) + (fConst41 * fRec5[1]))));
		fRec3[0] = ((0.9302847925323914 * (fRec4[0] + fRec4[1])) - (0.8605695850647829 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.8612942439318627 * fRec2[2])));
		fRec13[0] = ((fConst39 * fRec13[1]) + (fConst38 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec13[0] + (0.9254498422517706 * (fRec2[2] + (fRec2[0] + (2.0 * fRec2[1]))))) - 5.571981)) - 43.63033333333331);
		fRec0[0] = ((fConst44 * fRec0[1]) + (fConst43 * ((fConst40 * fRec1[0]) + (fConst41 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)(fRec0[0] + (fSlow1 * fTemp0));
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec13[1] = fRec13[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec12[1] = fRec12[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fVec0[1] = fVec0[0];
		fRec11[1] = fRec11[0];
		for (int i=4; i>0; i--) fRec10[i] = fRec10[i-1];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("bfuzz.Drive",N_("Drive"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("bfuzz.Level",N_("Level"),"S","",&fslider3, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("bfuzz.Thickness",N_("Thickness"),"S","",&fslider2, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("bfuzz.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider0, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<interface>\n\
  <!-- interface-requires gxwidgets 0.0 -->\n\
  <requires lib=\"gtk+\" version=\"2.20\"/>\n\
  <!-- interface-naming-policy project-wide -->\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can_focus\">False</property>\n\
    <child>\n\
      <object class=\"GtkVBox\" id=\"vbox1\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can_focus\">False</property>\n\
        <child>\n\
          <object class=\"GtkHBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GtkHBox\" id=\"hbox1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"spacing\">22</property>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
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
                  <object class=\"GtkVBox\" id=\"vbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
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
                  <object class=\"GtkVBox\" id=\"vbox4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
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
                  <object class=\"GtkVBox\" id=\"vbox5\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
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
          <object class=\"GtkHBox\" id=\"minibox\">\n\
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
                <property name=\"xalign\">0</property>\n\
                <property name=\"label\" translatable=\"yes\">Drive</property>\n\
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
