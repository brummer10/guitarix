// generated from file '../src/plugins/fuzzfacerm.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"


namespace pluginlib {
namespace fuzzfacerm {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	FAUSTFLOAT 	fslider0;
	double 	fRec0[2];
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
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fRec1[4];
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;

	int samplingFreq;
	gx_resample::FixedRateResampler smpCl;
	double 	fConstCl0;
	double 	fConstCl1;
	double 	fConstCl2;
	double 	fConstCl3;
	double 	fConstCl4;
	double 	fConstCl5;
	double 	fRecCl0[3];
	double 	fConstCl6;
	double 	fConstCl7;

	FAUSTFLOAT 	fsliderV0;
	double 	fRecV0[2];
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
	id = "fuzzfacerm";
	name = N_("Fuzz Face Mayer");
	groups = 0;
	description = N_("Roger Mayer Fuzz Face simulation"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("FF Mayer");     // shortname
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<4; i++) fRec1[i] = 0;

	for (int i=0; i<3; i++) fRecCl0[i] = 0;

	for (int i=0; i<2; i++) fRecV0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(192000, max(1, fSamplingFreq)));
	fConst1 = (1.72853928389298e-15 * fConst0);
	fConst2 = (2.6123111187704e-10 + (fConst0 * (4.32740215906676e-13 + fConst1)));
	fConst3 = (6.76928646854567e-33 * fConst0);
	fConst4 = (3.31695258087803e-30 * fConst0);
	fConst5 = ((5.00406457485288e-25 + (fConst0 * (8.26874714950455e-28 + fConst4))) + (2.81644163364677e-27 + (fConst0 * (8.88886207590151e-30 + fConst3))));
	fConst6 = (3.05119726906337e-14 * fConst0);
	fConst7 = (2.21726535708769e-11 + (fConst0 * (2.08816997599123e-11 + fConst6)));
	fConst8 = (3.22405119745267e-14 * fConst0);
	fConst9 = (1.26259937209307e-31 * fConst0);
	fConst10 = (6.18674104772942e-29 * fConst0);
	fConst11 = ((((fConst0 * (0 - (4.00204457374009e-26 + fConst10))) - 2.83832448080453e-29) + ((fConst0 * (0 - (2.15993317197785e-28 + fConst9))) - 8.68874841067831e-26)) + ((fConst0 * (0 - (2.08898268350887e-11 + fConst8))) - 2.21793415696022e-11));
	fConst12 = (1.19490650740761e-31 * fConst0);
	fConst13 = (5.85504578964162e-29 * fConst0);
	fConst14 = ((2.83746860731297e-29 + (fConst0 * (4.00083755606776e-26 + fConst13))) + (8.68612838978577e-26 + (fConst0 * (2.08767320417856e-28 + fConst12))));
	fConst15 = (2.27734110200845e-12 * fConst0);
	fConst16 = (2.90381085035365e-11 - fConst15);
	fConst17 = (2.23179427996828e-12 * fConst0);
	fConst18 = (fConst17 - 2.84573463334658e-11);
	fConst19 = ((fConst0 * (4.32740215906676e-13 - fConst1)) - 2.6123111187704e-10);
	fConst20 = (((fConst0 * (8.26874714950455e-28 - fConst4)) - 5.00406457485288e-25) + ((fConst0 * (8.88886207590151e-30 - fConst3)) - 2.81644163364677e-27));
	fConst21 = ((fConst0 * (2.08816997599123e-11 - fConst6)) - 2.21726535708769e-11);
	fConst22 = (((2.83832448080453e-29 + (fConst0 * (fConst10 - 4.00204457374009e-26))) + (8.68874841067831e-26 + (fConst0 * (fConst9 - 2.15993317197785e-28)))) + (2.21793415696022e-11 + (fConst0 * (fConst8 - 2.08898268350887e-11))));
	fConst23 = (((fConst0 * (4.00083755606776e-26 - fConst13)) - 2.83746860731297e-29) + ((fConst0 * (2.08767320417856e-28 - fConst12)) - 8.68612838978577e-26));
	fConst24 = (9.95085774263408e-30 * fConst0);
	fConst25 = (2.0307859405637e-32 * fConst0);
	fConst26 = (((fConst0 * (fConst25 - 8.88886207590151e-30)) - 2.81644163364677e-27) + ((fConst0 * (fConst24 - 8.26874714950455e-28)) - 5.00406457485288e-25));
	fConst27 = (9.67215359235801e-14 * fConst0);
	fConst28 = (3.78779811627921e-31 * fConst0);
	fConst29 = (1.85602231431883e-28 * fConst0);
	fConst30 = (((2.83832448080453e-29 + (fConst0 * (4.00204457374009e-26 - fConst29))) + (8.68874841067831e-26 + (fConst0 * (2.15993317197785e-28 - fConst28)))) + (2.21793415696022e-11 + (fConst0 * (2.08898268350887e-11 - fConst27))));
	fConst31 = (1.75651373689249e-28 * fConst0);
	fConst32 = (3.58471952222284e-31 * fConst0);
	fConst33 = (((fConst0 * (fConst32 - 2.08767320417856e-28)) - 8.68612838978577e-26) + ((fConst0 * (fConst31 - 4.00083755606776e-26)) - 2.83746860731297e-29));
	fConst34 = (9.15359180719011e-14 * fConst0);
	fConst35 = ((fConst0 * (fConst34 - 2.08816997599123e-11)) - 2.21726535708769e-11);
	fConst36 = (5.18561785167894e-15 * fConst0);
	fConst37 = ((fConst0 * (fConst36 - 4.32740215906676e-13)) - 2.6123111187704e-10);
	fConst38 = (2.6123111187704e-10 + (fConst0 * (0 - (4.32740215906676e-13 + fConst36))));
	fConst39 = ((5.00406457485288e-25 + (fConst0 * (0 - (8.26874714950455e-28 + fConst24)))) + (2.81644163364677e-27 + (fConst0 * (0 - (8.88886207590151e-30 + fConst25)))));
	fConst40 = (2.21726535708769e-11 + (fConst0 * (0 - (2.08816997599123e-11 + fConst34))));
	fConst41 = ((((fConst0 * (4.00204457374009e-26 + fConst29)) - 2.83832448080453e-29) + ((fConst0 * (2.15993317197785e-28 + fConst28)) - 8.68874841067831e-26)) + ((fConst0 * (2.08898268350887e-11 + fConst27)) - 2.21793415696022e-11));
	fConst42 = ((2.83746860731297e-29 + (fConst0 * (0 - (4.00083755606776e-26 + fConst31)))) + (8.68612838978577e-26 + (fConst0 * (0 - (2.08767320417856e-28 + fConst32)))));
	fConst43 = faustpower<2>(fConst0);
	fConst44 = (6.69538283990485e-12 * fConst0);
	fConst45 = (6.83202330602535e-12 * fConst0);
	fConst46 = (fConst43 * ((fConst45 - 2.90381085035365e-11) + (2.84573463334658e-11 - fConst44)));
	fConst47 = faustpower<3>(fConst0);
	fConst48 = (1.338980114240397e-13 * fConst47);
	fConst49 = (0 - (2.7424546964679977e-15 * fConst47));
	fConst50 = (0 - (2.90381085035365e-11 + fConst45));
	fConst51 = (2.84573463334658e-11 + fConst44);
	fConst52 = (fConst43 * ((0 - (2.84573463334658e-11 + fConst17)) + (2.90381085035365e-11 + fConst15)));
	fConst53 = (4.463267047468017e-14 * fConst47);
	fConst54 = (0 - (9.141515654894967e-16 * fConst47));

	samplingFreq = 96000;
	smpCl.setup(fSamplingFreq, samplingFreq);
	fSamplingFreq = samplingFreq;
	fConstCl0 = tan((138230.07675795088 / double(min(192000, max(1, fSamplingFreq)))));
	fConstCl1 = (2 * (1 - (1.0 / faustpower<2>(fConstCl0))));
	fConstCl2 = (1.0 / fConstCl0);
	fConstCl3 = (1 + ((fConstCl2 - 1.414213562373095) / fConstCl0));
	fConstCl4 = (1 + ((1.414213562373095 + fConstCl2) / fConstCl0));
	fConstCl5 = (1.0 / fConstCl4);
	fConstCl6 = (1.0001 / fConstCl4);
	fConstCl7 = (1.0 / tanh(1.0001));

	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlowV0 = (0.0010000000000000009 * double(fsliderV0));

	double 	fSlow0 = (0.007000000000000006 * (1 - double(fslider0)));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		double fTemp0 = ((fConst0 * (((fRec0[0] * ((fConst14 + (fConst11 * fRec0[0])) + fConst7)) + fConst5) + fConst2)) + 2.773253696040941e-10);
		fRec1[0] = ((double)input0[i] - ((((fRec1[1] * ((fConst0 * (((fRec0[0] * ((fConst42 + (fConst41 * fRec0[0])) + fConst40)) + fConst39) + fConst38)) + 8.319761088122833e-10)) + (fRec1[2] * (8.319761088122833e-10 + (fConst0 * (fConst37 + ((fRec0[0] * (fConst35 + (fConst33 + (fConst30 * fRec0[0])))) + fConst26)))))) + (fRec1[3] * (2.773253696040941e-10 + (fConst0 * (((fRec0[0] * ((fConst23 + (fConst22 * fRec0[0])) + fConst21)) + fConst20) + fConst19))))) / fTemp0));
		output0[i] = (FAUSTFLOAT)(((((fRec1[0] * ((fRec0[0] * ((fConst54 * fRec0[0]) - fConst53)) + fConst52)) + (fConst43 * (fRec1[1] * ((fConst51 + (fConst0 * (fRec0[0] * (6.69490057120194e-12 + ((2.7424546964679977e-15 * fRec0[0]) - 6.5610025597779e-12))))) + fConst50)))) + (fRec1[2] * ((fRec0[0] * ((fConst49 * fRec0[0]) - fConst48)) + fConst46))) + (fConst43 * (fRec1[3] * ((fConst18 + (fConst0 * (fRec0[0] * (2.23163352373398e-12 + ((9.141515654894967e-16 * fRec0[0]) - 2.1870008532593e-12))))) + fConst16)))) / fTemp0);
		// post processing
		for (int i=3; i>0; i--) fRec1[i] = fRec1[i-1];
		fRec0[1] = fRec0[0];
	}

	FAUSTFLOAT bufCl[smpCl.max_out_count(count)];
	int ReCount = smpCl.up(count, output0, bufCl);
	for (int i=0; i<ReCount; i++) {
		fRecCl0[0] = ((double)bufCl[i] - (fConstCl5 * ((fConstCl3 * fRecCl0[2]) + (fConstCl1 * fRecCl0[1]))));
		bufCl[i] = (FAUSTFLOAT)(fConstCl7 * tanh((fConstCl6 * (fRecCl0[2] + (fRecCl0[0] + (2 * fRecCl0[1]))))));
		// post processing
		fRecCl0[2] = fRecCl0[1]; fRecCl0[1] = fRecCl0[0];
	}
	smpCl.down(bufCl, output0);

	for (int i=0; i<count; i++) {
		fRecV0[0] = ((0.999 * fRecV0[1]) + fSlowV0);
		output0[i] = (FAUSTFLOAT)((double)output0[i] * fRecV0[0]);
		// post processing
		fRecV0[1] = fRecV0[0];
	}

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("fuzzfacerm.Level",N_("Level"),"S","",&fsliderV0, 0.5, 0.0, 1, 0.01);
	reg.registerVar("fuzzfacerm.Fuzz",N_("Fuzz"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
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
                        <property name=\"var_id\">fuzzfacerm.Fuzz</property>\n\
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
                        <property name=\"var_id\">fuzzfacerm.Level</property>\n\
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
                <property name=\"var_id\">fuzzfacerm.Level</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Level</property>\n\
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
#define PARAM(p) ("fuzzfacerm" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Fuzz"), N_("Fuzz"));
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Fuzz"), N_("Fuzz"));

    b.create_small_rackknobr(PARAM("Level"), N_("Level"));
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

} // end namespace fuzzfacerm
} // end namespace pluginlib
