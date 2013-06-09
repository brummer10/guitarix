// generated from file '../src/plugins/dunwah.dsp' by dsp2cc:
// Code generated with Faust 0.9.55 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"

namespace dunwah {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	int 	iConst0;
	double 	fConst1;
	double 	fRec1[2];
	double 	fConst2;
	double 	fConst3;
	double 	fRec2[2];
	double 	fConst4;
	double 	fRec3[2];
	double 	fRec0[4];
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	void clear_state_f();
	int load_ui_f(const UiBuilder& b);
	static const char *glade_def;
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, float *input0, float *output0, PluginDef*);
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
	id = "dunwah";
	name = N_("DunWah");
	groups = 0;
	description = ""; // description (tooltip)
	category = "";       // category
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
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<4; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (0.007000000000000006 * ((iConst0 * (1.73888e-06 - (8.38823e-12 * iConst0))) - 0.193457));
	fConst2 = (0.5 / double(iConst0));
	fConst3 = (1.0 / double(iConst0));
	fConst4 = exp((0 - (1236.9027460477864 / double(iConst0))));
	fConst5 = (1.77528e-06 - (8.52216e-12 * iConst0));
	fConst6 = (0.879905 + (iConst0 * fConst5));
	fConst7 = (1.54419e-05 - (6.43963e-11 * iConst0));
	fConst8 = ((iConst0 * fConst7) - 0.386688);
	fConst9 = (fConst8 * (0 - (1.00038 * fConst6)));
	fConst10 = ((fConst8 * fConst6) + (1.00038 * (fConst8 + fConst6)));
	fConst11 = (0 - ((iConst0 * (fConst7 + fConst5)) + 1.4935970000000003));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (fConst1 * (0 - ((1.0 / ((fSlow0 * (0.270546 + (fSlow0 * ((fSlow0 * (3.64419 + (fSlow0 * ((2.85511 * fSlow0) - 5.20364)))) - 0.86331)))) - 0.814203)) + 0.933975)));
	double 	fSlow2 = (1973.48 - (double(1000) / ((fSlow0 * (1.9841 + (fSlow0 * (5.76598 + (fSlow0 * ((fSlow0 * (49.9836 + (fSlow0 * ((12.499 * fSlow0) - 40.3658)))) - 28.3434)))))) - 1.6086)));
	double 	fSlow3 = (1 - (fConst2 * (fSlow2 / (21.9737 + (fSlow0 * ((fSlow0 * (42.2734 + (fSlow0 * ((fSlow0 * (115.375 - (52.3051 * fSlow0))) - 99.7712)))) - 24.555))))));
	double 	fSlow4 = (0.007000000000000006 * (cos((fConst3 * fSlow2)) * (0 - (2.0 * fSlow3))));
	double 	fSlow5 = (0.007000000000000006 * faustpower<2>(fSlow3));
	for (int i=0; i<count; i++) {
		fRec1[0] = (fSlow1 + (0.993 * fRec1[1]));
		fRec2[0] = (fSlow4 + (0.993 * fRec2[1]));
		fRec3[0] = (fSlow5 + (0.993 * fRec3[1]));
		fRec0[0] = (0 - (((fRec0[1] * (fRec2[0] - fConst4)) + ((fConst4 * ((0 - fRec3[0]) * fRec0[3])) + (fRec0[2] * (fRec3[0] - (fConst4 * fRec2[0]))))) - ((double)input0[i] * fRec1[0])));
		output0[i] = (FAUSTFLOAT)((fConst11 * fRec0[1]) + ((fConst10 * fRec0[2]) + (fRec0[0] + (fConst9 * fRec0[3]))));
		// post processing
		for (int i=3; i>0; i--) fRec0[i] = fRec0[i-1];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
	}
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("dunwah.wah","","S","",&fslider0, 0.0, 0.0, 1.0, 0.01);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<interface>\n\
  <requires lib=\"gtk+\" version=\"2.20\"/>\n\
  <!-- interface-requires gxwidgets 0.0 -->\n\
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
            <child>\n\
              <object class=\"GtkHBox\" id=\"hbox1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
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
                        <property name=\"fill\">True</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">dunwah.wah</property>\n\
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
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">True</property>\n\
            <property name=\"position\">0</property>\n\
          </packing>\n\
        </child>\n\
        <child>\n\
          <object class=\"GtkHBox\" id=\"minibox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <child>\n\
              <placeholder/>\n\
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

int Dsp::load_ui_f(const UiBuilder& b)
{
	b.load_glade(glade_def);
	return 0;
}

int Dsp::load_ui_f_static(const UiBuilder& b)
{
	return static_cast<Dsp*>(b.plugin)->load_ui_f(b);
}

PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

extern "C" __attribute__ ((visibility ("default"))) int
get_gx_plugin(unsigned int idx, PluginDef **pplugin)
{
    if (!pplugin) {
        return 1;
    }
    if (idx > 0) {
        return -1;
    }
    *pplugin = new Dsp();
    return 1;
}
} // end namespace dunwah
