// generated from file '../src/plugins/bossds1.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

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
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	FAUSTFLOAT 	fslider0;
	double 	fRec1[2];
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
	FAUSTFLOAT 	fslider1;
	double 	fRec5[2];
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
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fRec8[2];
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fRec7[4];
	double 	fConst44;
	double 	fConst45;
	double 	fRec6[3];
	double 	fConst46;
	double 	fRec4[2];
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fVec0[2];
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fRec9[2];
	double 	fRec3[2];
	double 	fConst54;
	double 	fRec2[3];
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fRec0[3];
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	FAUSTFLOAT 	fslider2;
	double 	fRec10[2];

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
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<4; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
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
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = double(fConst0);
	fConst2 = (4.33883931795138e-10 * fConst1);
	fConst3 = (2.33802056631403e-08 + (fConst1 * (fConst2 - 6.90412007909908e-09)));
	fConst4 = faustpower<2>(fConst1);
	fConst5 = (4.67604113262805e-08 - (8.67767863590276e-10 * fConst4));
	fConst6 = (1.0 / (2.33802056631403e-08 + (fConst1 * (6.90412007909908e-09 + fConst2))));
	fConst7 = (2.89644353783249e-10 * fConst1);
	fConst8 = ((fConst1 * (0 - (9.44398925362792e-07 + fConst7))) - 0.000537812599864916);
	fConst9 = (2.65571689713263e-10 * fConst1);
	fConst10 = (0.000537812599864916 + (fConst1 * (7.50424979344313e-07 + fConst9)));
	fConst11 = (3.3778968192322e-10 * fConst1);
	fConst12 = (0.00114855258827151 + (fConst1 * (1.55559824875468e-06 + fConst11)));
	fConst13 = (2.18842400636233e-10 * fConst1);
	fConst14 = (0.000537812599864916 + (fConst1 * (0 - (5.20602596669238e-08 + fConst13))));
	fConst15 = (0.000182856283954071 + (fConst1 * (fConst13 - 2.33324618325395e-07)));
	fConst16 = ((fConst1 * (9.44398925362792e-07 - fConst7)) - 0.000537812599864916);
	fConst17 = (0.000537812599864916 + (fConst1 * (fConst9 - 7.50424979344313e-07)));
	fConst18 = (0.00114855258827151 + (fConst1 * (fConst11 - 1.55559824875468e-06)));
	fConst19 = ((5.79288707566498e-10 * fConst4) - 0.00107562519972983);
	fConst20 = (0.00107562519972983 - (5.31143379426527e-10 * fConst4));
	fConst21 = (0.00229710517654303 - (6.7557936384644e-10 * fConst4));
	fConst22 = (1.40428074750109e-05 * fConst1);
	fConst23 = (0.325945241199478 + fConst22);
	fConst24 = ((0.325945241199478 - fConst22) / fConst23);
	fConst25 = (2.07985763541319e-05 * fConst1);
	fConst26 = (0.00166833500166833 + fConst25);
	fConst27 = ((0.00166833500166833 - fConst25) / fConst26);
	fConst28 = (1.49503874539434e-11 * fConst1);
	fConst29 = (1.66555708487018e-05 + fConst28);
	fConst30 = (fConst28 - 7.50903344506575e-07);
	fConst31 = (fConst28 - 1.66555708487018e-05);
	fConst32 = (3.53982651634833e-10 * fConst1);
	fConst33 = (1.94656546234155e-05 + (fConst1 * (fConst32 - 2.38582349500046e-07)));
	fConst34 = (2.38582349500046e-07 + fConst32);
	fConst35 = (5.83969638702466e-05 + (fConst1 * (0 - fConst34)));
	fConst36 = (5.83969638702466e-05 + (fConst1 * (2.38582349500046e-07 - fConst32)));
	fConst37 = (1.0 / (1.94656546234155e-05 + (fConst1 * fConst34)));
	fConst38 = (2.08223456923865e-05 * fConst1);
	fConst39 = (0.000527406765446517 + fConst38);
	fConst40 = ((0.000527406765446517 - fConst38) / fConst39);
	fConst41 = (2.06179485600366e-05 * fConst1);
	fConst42 = (0 - fConst41);
	fConst43 = (1.0 / fConst39);
	fConst44 = (5.51041967277497e-09 * fConst4);
	fConst45 = (0 - fConst44);
	fConst46 = (7.50903344506575e-07 + fConst28);
	fConst47 = (1.89077966855745e-05 * fConst1);
	fConst48 = (0 - fConst47);
	fConst49 = (1.0 / fConst26);
	fConst50 = (9.4e-08 * fConst0);
	fConst51 = (0.0192418 * fConst0);
	fConst52 = (1 - fConst51);
	fConst53 = (1 + fConst51);
	fConst54 = (0.45081801796277066 / fConst23);
	fConst55 = (4.37684801272465e-10 * fConst4);
	fConst56 = (0.00107562519972983 + fConst55);
	fConst57 = (0.000365712567908143 - fConst55);
	fConst58 = (0.000537812599864916 + (fConst1 * (5.20602596669238e-08 - fConst13)));
	fConst59 = (0.000182856283954071 + (fConst1 * (2.33324618325395e-07 + fConst13)));
	fConst60 = (4.26031359768866e-10 * fConst1);
	fConst61 = (fConst60 - 2.06011295826338e-10);
	fConst62 = (2.06011295826338e-10 + fConst60);
	fConst63 = (0 - (8.52062719537733e-10 * fConst4));
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
	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	double 	fSlow1 = (0.002198000000000002 * double(fslider1));
	double 	fSlow2 = (0.007000000000000006 * pow(10,(0.05 * double(fslider2))));
	for (int i=0; i<ReCount; i++) {
		fRec1[0] = (fSlow0 + (0.993 * fRec1[1]));
		double fTemp0 = (fConst12 + (fRec1[0] * (fConst10 + (fConst8 * fRec1[0]))));
		fRec5[0] = (fSlow1 + (0.993 * fRec5[1]));
		double fTemp1 = (fConst1 * (3.0314296262996e-10 + (0 - (3.18093350083904e-10 * fRec5[0]))));
		double fTemp2 = (0.000169198590470162 + (fConst1 * (fConst29 + (fRec5[0] * (fTemp1 - 3.38397180940322e-09)))));
		double fTemp3 = (fConst4 * ((fRec5[0] * ((6.36186700167807e-10 * fRec5[0]) - 6.0628592525992e-10)) - 2.99007749078869e-11));
		fRec8[0] = ((double)buf[i] - (fConst40 * fRec8[1]));
		fRec7[0] = ((fConst43 * ((fConst42 * fRec8[1]) + (fConst41 * fRec8[0]))) - (fConst37 * (((fConst36 * fRec7[1]) + (fConst35 * fRec7[2])) + (fConst33 * fRec7[3]))));
		fRec6[0] = ((fConst37 * ((fConst44 * (fRec7[1] + fRec7[2])) + (fConst45 * (fRec7[3] + fRec7[0])))) - (((fRec6[1] * (0.000338397180940324 + fTemp3)) + (fRec6[2] * (0.000169198590470162 + (fConst1 * (fConst31 + (fRec5[0] * (3.38397180940322e-09 + fTemp1))))))) / fTemp2));
		fRec4[0] = ((0.3183098861837907 * atan(((((fRec6[1] * (0.000338397180940323 + fTemp3)) + (fRec6[0] * (0.000169198590470161 + (fConst1 * (fConst46 + (fRec5[0] * (1.59012835323858e-05 + fTemp1))))))) + (fRec6[2] * (0.000169198590470161 + (fConst1 * (fConst30 + (fRec5[0] * (fTemp1 - 1.59012835323858e-05))))))) / fTemp2))) - (fConst27 * fRec4[1]));
		double fTemp4 = (fConst49 * ((fConst48 * fRec4[1]) + (fConst47 * fRec4[0])));
		double fTemp5 = (fConst50 * (4700 + (100000 * (1.0 - fRec5[0]))));
		double fTemp6 = (1 + fTemp5);
		double fTemp7 = opamp(fTemp4);
		double fTemp8 = (fTemp4 - fTemp7);
		fVec0[0] = fTemp8;
		fRec9[0] = ((fRec9[1] * (0 - ((1 - fTemp5) / fTemp6))) + (((fConst53 * fVec0[0]) + (fConst52 * fVec0[1])) / fTemp6));
		fRec3[0] = (asymhardclip2((0 - ((fTemp7 + opamp(((fTemp7 + fRec9[0]) - fTemp4))) - fTemp4))) - (fConst24 * fRec3[1]));
		fRec2[0] = ((fConst54 * (fRec3[1] + fRec3[0])) - (((fRec2[1] * (fConst21 + (fRec1[0] * (fConst20 + (fConst19 * fRec1[0]))))) + (fRec2[2] * (fConst18 + (fRec1[0] * (fConst17 + (fConst16 * fRec1[0])))))) / fTemp0));
		fRec0[0] = (((((fRec2[0] * (fConst59 + (fConst58 * fRec1[0]))) + (fRec2[1] * (fConst57 + (fConst56 * fRec1[0])))) + (fRec2[2] * (fConst15 + (fConst14 * fRec1[0])))) / fTemp0) - (fConst6 * ((fConst5 * fRec0[1]) + (fConst3 * fRec0[2]))));
		fRec10[0] = (fSlow2 + (0.993 * fRec10[1]));
		buf[i] = (FAUSTFLOAT)(fConst6 * (fRec10[0] * ((fConst63 * fRec0[1]) + (fConst1 * ((fConst62 * fRec0[0]) + (fConst61 * fRec0[2]))))));
		// post processing
		fRec10[1] = fRec10[0];
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec9[1] = fRec9[0];
		fVec0[1] = fVec0[0];
		fRec4[1] = fRec4[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		for (int i=3; i>0; i--) fRec7[i] = fRec7[i-1];
		fRec8[1] = fRec8[0];
		fRec5[1] = fRec5[0];
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
	reg.registerVar("bossds1.Level",N_("Level"),"S","",&fslider2, 3.0, -2e+01, 12.0, 0.1);
	reg.registerVar("bossds1.Tone",N_("Tone"),"S","",&fslider0, 0.7, 0.0, 1.0, 0.01);
	reg.registerVar("bossds1.drive",N_("Drive"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
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
                <property name=\"spacing\">10</property>\n\
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
