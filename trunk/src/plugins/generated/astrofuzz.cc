// generated from file '../src/plugins/astrofuzz.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace astrofuzz {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	FAUSTFLOAT 	fslider0;
	double 	fRec8[2];
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	FAUSTFLOAT 	fslider1;
	double 	fRec9[2];
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
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fRec10[4];
	FAUSTFLOAT 	fslider2;
	double 	fRec11[2];
	double 	fVec0[2];
	double 	fConst38;
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fRec12[2];
	double 	fRec5[3];
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
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
	id = "astrofuzz";
	name = N_("Astrotone Fuzz");
	groups = 0;
	description = N_("Astrotone Fuzz"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("Astrotone");     // shortname
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
	for (int i=0; i<4; i++) fRec10[i] = 0;
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
	fConst2 = (4.49290068884749e-15 * fConst1);
	fConst3 = (9.42407659969146e-09 + (fConst1 * (1.34316849964884e-11 + fConst2)));
	fConst4 = (4.09854197590519e-14 * fConst1);
	fConst5 = (8.31252171811903e-11 + fConst4);
	fConst6 = (5.6592388303455e-09 + (fConst1 * fConst5));
	fConst7 = (3.46486099611082e-14 * fConst1);
	fConst8 = (3.92502015729988e-11 + fConst7);
	fConst9 = ((fConst1 * (0 - fConst8)) - 2.59598111483739e-09);
	fConst10 = (2.59598111483739e-09 + (fConst1 * fConst8));
	fConst11 = ((fConst1 * (0 - fConst5)) - 5.6592388303455e-09);
	fConst12 = (3.79430966640243e-15 * fConst1);
	fConst13 = ((fConst1 * ((fConst1 * (0 - (7.96218897097081e-12 + fConst12))) - 4.44205261980514e-09)) - 2.76168203706105e-07);
	fConst14 = ((fConst1 * (1.34316849964884e-11 - fConst2)) - 9.42407659969146e-09);
	fConst15 = ((fConst1 * (8.31252171811903e-11 - fConst4)) - 5.6592388303455e-09);
	fConst16 = (2.59598111483739e-09 + (fConst1 * (fConst7 - 3.92502015729988e-11)));
	fConst17 = ((fConst1 * (3.92502015729988e-11 - fConst7)) - 2.59598111483739e-09);
	fConst18 = (5.6592388303455e-09 + (fConst1 * (fConst4 - 8.31252171811903e-11)));
	fConst19 = ((fConst1 * (4.44205261980514e-09 + (fConst1 * (fConst12 - 7.96218897097081e-12)))) - 2.76168203706105e-07);
	fConst20 = (1.03945829883325e-13 * fConst1);
	fConst21 = (2.59598111483739e-09 + (fConst1 * (3.92502015729988e-11 - fConst20)));
	fConst22 = ((fConst1 * (fConst20 - 3.92502015729988e-11)) - 2.59598111483739e-09);
	fConst23 = (1.22956259277156e-13 * fConst1);
	fConst24 = (5.6592388303455e-09 + (fConst1 * (8.31252171811903e-11 - fConst23)));
	fConst25 = ((fConst1 * (fConst23 - 8.31252171811903e-11)) - 5.6592388303455e-09);
	fConst26 = (1.34787020665425e-14 * fConst1);
	fConst27 = ((fConst1 * (fConst26 - 1.34316849964884e-11)) - 9.42407659969146e-09);
	fConst28 = (1.13829289992073e-14 * fConst1);
	fConst29 = ((fConst1 * (4.44205261980514e-09 + (fConst1 * (7.96218897097081e-12 - fConst28)))) - 8.28504611118315e-07);
	fConst30 = (9.42407659969146e-09 + (fConst1 * (0 - (1.34316849964884e-11 + fConst26))));
	fConst31 = (8.31252171811903e-11 + fConst23);
	fConst32 = (5.6592388303455e-09 + (fConst1 * (0 - fConst31)));
	fConst33 = (3.92502015729988e-11 + fConst20);
	fConst34 = ((fConst1 * fConst33) - 2.59598111483739e-09);
	fConst35 = (2.59598111483739e-09 + (fConst1 * (0 - fConst33)));
	fConst36 = ((fConst1 * fConst31) - 5.6592388303455e-09);
	fConst37 = ((fConst1 * ((fConst1 * (7.96218897097081e-12 + fConst28)) - 4.44205261980514e-09)) - 8.28504611118315e-07);
	fConst38 = (0.9302847925323914 * faustpower<3>(fConst1));
	fConst39 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst40 = (1 + fConst39);
	fConst41 = (0.027 / fConst40);
	fConst42 = (0 - ((1 - fConst39) / fConst40));
	fConst43 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst44 = (0 - fConst43);
	fConst45 = (1 + fConst43);
	fConst46 = (0.025 / fConst45);
	fConst47 = (0 - ((1 - fConst43) / fConst45));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	double 	fSlow2 = (0.007000000000000006 * double(fslider2));
	for (int i=0; i<count; i++) {
		fRec8[0] = ((0.993 * fRec8[1]) + fSlow0);
		fRec9[0] = ((0.993 * fRec9[1]) + fSlow1);
		double fTemp0 = (6.02046684079309e-07 + ((fConst13 * fRec8[0]) + (fConst1 * ((fRec9[0] * (((fRec9[0] * (fConst11 + (fConst10 * fRec8[0]))) + (fConst9 * fRec8[0])) + fConst6)) + fConst3))));
		double fTemp1 = (1.00499515996459e-12 * fRec8[0]);
		fRec10[0] = ((double)input0[i] - ((((fRec10[1] * (1.80614005223793e-06 + ((fConst37 * fRec8[0]) + (fConst1 * ((fRec9[0] * (((fRec9[0] * (fConst36 + (fConst35 * fRec8[0]))) + (fConst34 * fRec8[0])) + fConst32)) + fConst30))))) + (fRec10[2] * (1.80614005223793e-06 + ((fConst29 * fRec8[0]) + (fConst1 * (fConst27 + (fRec9[0] * (fConst25 + ((fRec9[0] * (fConst24 + (fConst22 * fRec8[0]))) + (fConst21 * fRec8[0])))))))))) + (fRec10[3] * (6.02046684079309e-07 + ((fConst19 * fRec8[0]) + (fConst1 * ((fRec9[0] * (((fRec9[0] * (fConst18 + (fConst17 * fRec8[0]))) + (fConst16 * fRec8[0])) + fConst15)) + fConst14)))))) / fTemp0));
		double fTemp2 = (3.01498547989378e-12 * fRec8[0]);
		fRec11[0] = ((0.993 * fRec11[1]) + fSlow2);
		double fTemp3 = (((fRec9[0] * fRec11[0]) * ((((fRec10[0] * (fTemp1 - 1.18589428875822e-12)) + (fRec10[1] * (3.55768286627466e-12 + (0 - fTemp2)))) + (fRec10[2] * (fTemp2 - 3.55768286627466e-12))) + (fRec10[3] * (1.18589428875822e-12 + (0 - fTemp1))))) / fTemp0);
		fVec0[0] = fTemp3;
		fRec7[0] = ((fConst38 * (fVec0[0] + fVec0[1])) - (0.8605695850647829 * fRec7[1]));
		fRec6[0] = (fRec7[0] - ((1.8405051250752198 * fRec6[1]) + (0.8612942439318627 * fRec6[2])));
		fRec12[0] = ((fConst42 * fRec12[1]) + (fConst41 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec12[0] + (0.9254498422517706 * (fRec6[2] + (fRec6[0] + (2.0 * fRec6[1]))))) - 3.571981)) - 117.70440740740739);
		fRec4[0] = ((fConst47 * fRec4[1]) + (fConst46 * ((fConst43 * fRec5[0]) + (fConst44 * fRec5[1]))));
		fRec3[0] = ((0.9302847925323914 * (fRec4[0] + fRec4[1])) - (0.8605695850647829 * fRec3[1]));
		fRec2[0] = (fRec3[0] - ((1.8405051250752198 * fRec2[1]) + (0.8612942439318627 * fRec2[2])));
		fRec13[0] = ((fConst42 * fRec13[1]) + (fConst41 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec13[0] + (0.9254498422517706 * (fRec2[2] + (fRec2[0] + (2.0 * fRec2[1]))))) - 3.571981)) - 117.70440740740739);
		fRec0[0] = ((fConst47 * fRec0[1]) + (fConst46 * ((fConst43 * fRec1[0]) + (fConst44 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)fRec0[0];
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
		for (int i=3; i>0; i--) fRec10[i] = fRec10[i-1];
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
	reg.registerVar("astrofuzz.Attack",N_("Attack"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("astrofuzz.Tone",N_("Tone"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("astrofuzz.Volume",N_("Volume"),"S","",&fslider2, 0.5, 0.0, 1.0, 0.01);
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
                        <property name=\"var_id\">astrofuzz.Attack</property>\n\
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
                      <object class=\"GxMidKnob\" id=\"gxbigknob2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">astrofuzz.Volume</property>\n\
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
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">astrofuzz.Tone</property>\n\
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
                <property name=\"var_id\">astrofuzz.Volume</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Volume</property>\n\
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

} // end namespace astrofuzz
} // end namespace pluginlib
