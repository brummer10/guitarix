// generated from file '../src/faust/dattorros_progenitor.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace dattorros_progenitor {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	int 	IOTA;
	double 	fVec1[262144];
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	FAUSTFLOAT 	fslider1;
	double 	fConst3;
	double 	fRec18[2];
	double 	fRec19[2];
	double 	fRec20[2];
	double 	fRec21[2];
	FAUSTFLOAT 	fslider2;
	double 	fRec17[3];
	FAUSTFLOAT 	fslider3;
	double 	fVec2[1024];
	int 	iConst4;
	double 	fRec15[2];
	double 	fVec3[1024];
	int 	iConst5;
	double 	fRec13[2];
	FAUSTFLOAT 	fslider4;
	double 	fVec4[4096];
	int 	iConst6;
	double 	fRec11[2];
	double 	fVec5[2048];
	int 	iConst7;
	double 	fRec9[2];
	double 	fVec6[8192];
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fRec22[2];
	double 	fConst11;
	double 	fRec23[2];
	FAUSTFLOAT 	fslider5;
	int 	iConst12;
	double 	fRec7[2];
	double 	fRec8[32768];
	int 	iConst13;
	FAUSTFLOAT 	fslider6;
	double 	fRec6[3];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	double 	fVec7[16384];
	int 	iConst14;
	double 	fRec4[2];
	double 	fVec8[32768];
	int 	iConst15;
	double 	fRec0[2];
	double 	fVec9[8192];
	int 	iConst16;
	double 	fRec27[2];
	double 	fRec28[32768];
	int 	iConst17;
	double 	fRec26[3];
	double 	fVec10[32768];
	int 	iConst18;
	double 	fRec24[2];
	double 	fVec11[32768];
	int 	iConst19;
	double 	fRec1[2];
	double 	fVec12[8192];
	double 	fRec29[2];
	double 	fVec13[8192];
	double 	fRec31[2];
	FAUSTFLOAT 	fslider9;

	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef*);
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
	id = "dattorros_progenitor";
	name = N_("Plate Reverb");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Reverb");       // category
	shortname = "";     // shortname
	mono_audio = 0;
	stereo_audio = compute_static;
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<262144; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<1024; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<1024; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<4096; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2048; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<8192; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<32768; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<16384; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<32768; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<8192; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<32768; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<32768; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<32768; i++) fVec11[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<8192; i++) fVec12[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<8192; i++) fVec13[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = (1e+01 / fConst0);
	fConst2 = (0 - fConst1);
	fConst3 = (0.001 * fConst0);
	iConst4 = int((0.004771345048889486 * fConst0));
	iConst5 = int((0.0035953092974026412 * fConst0));
	iConst6 = int((0.01273478713752898 * fConst0));
	iConst7 = int((0.009307482947481604 * fConst0));
	fConst8 = (6.283185307179586 / fConst0);
	fConst9 = cos(fConst8);
	fConst10 = sin(fConst8);
	fConst11 = (0 - fConst10);
	iConst12 = int((0.022042270085010585 * fConst0));
	iConst13 = int((0.14962534861059776 * fConst0));
	iConst14 = int((0.060481838647894894 * fConst0));
	iConst15 = int((0.12499579987231611 * fConst0));
	iConst16 = int((0.029972111152179026 * fConst0));
	iConst17 = int((0.14169550754342933 * fConst0));
	iConst18 = int((0.08924431302711602 * fConst0));
	iConst19 = int((0.10628003091293975 * fConst0));
	IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	double 	fSlow0 = double(fslider0);
	double 	fSlow1 = (fConst3 * double(fslider1));
	double 	fSlow2 = double(fslider2);
	double 	fSlow3 = (0.5 * fSlow2);
	double 	fSlow4 = (1 - fSlow2);
	double 	fSlow5 = double(fslider3);
	double 	fSlow6 = (0 - fSlow5);
	double 	fSlow7 = double(fslider4);
	double 	fSlow8 = (0 - fSlow7);
	double 	fSlow9 = (0.5 * double(fslider5));
	double 	fSlow10 = double(fslider6);
	double 	fSlow11 = (1 - fSlow10);
	double 	fSlow12 = double(fslider7);
	double 	fSlow13 = double(fslider8);
	double 	fSlow14 = (0 - fSlow13);
	double 	fSlow15 = double(fslider9);
	double 	fSlow16 = (1 - fSlow15);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		double fTemp0 = (0.5 * fRec1[1]);
		double fTemp1 = (double)input1[i];
		double fTemp2 = (double)input0[i];
		double fTemp3 = (fTemp2 + fTemp1);
		fVec1[IOTA&262143] = fTemp3;
		double fTemp4 = ((int((fRec18[1] != 0.0)))?((int(((fRec19[1] > 0.0) & (fRec19[1] < 1.0))))?fRec18[1]:0):((int(((fRec19[1] == 0.0) & (fSlow1 != fRec20[1]))))?fConst1:((int(((fRec19[1] == 1.0) & (fSlow1 != fRec21[1]))))?fConst2:0)));
		fRec18[0] = fTemp4;
		fRec19[0] = max(0.0, min(1.0, (fRec19[1] + fTemp4)));
		fRec20[0] = ((int(((fRec19[1] >= 1.0) & (fRec21[1] != fSlow1))))?fSlow1:fRec20[1]);
		fRec21[0] = ((int(((fRec19[1] <= 0.0) & (fRec20[1] != fSlow1))))?fSlow1:fRec21[1]);
		fRec17[0] = ((fSlow4 * fRec17[2]) + (fSlow3 * ((fVec1[(IOTA-int((int(fRec20[0]) & 262143)))&262143] * (1.0 - fRec19[0])) + (fRec19[0] * fVec1[(IOTA-int((int(fRec21[0]) & 262143)))&262143]))));
		double fTemp5 = ((fSlow6 * fRec15[1]) + fRec17[0]);
		fVec2[IOTA&1023] = fTemp5;
		fRec15[0] = fVec2[(IOTA-iConst4)&1023];
		double 	fRec16 = (fSlow5 * fVec2[IOTA&1023]);
		double fTemp6 = (fRec16 + ((fSlow6 * fRec13[1]) + fRec15[1]));
		fVec3[IOTA&1023] = fTemp6;
		fRec13[0] = fVec3[(IOTA-iConst5)&1023];
		double 	fRec14 = (fSlow5 * fVec3[IOTA&1023]);
		double fTemp7 = (fRec14 + ((fSlow8 * fRec11[1]) + fRec13[1]));
		fVec4[IOTA&4095] = fTemp7;
		fRec11[0] = fVec4[(IOTA-iConst6)&4095];
		double 	fRec12 = (fSlow7 * fVec4[IOTA&4095]);
		double fTemp8 = (fRec12 + ((fSlow8 * fRec9[1]) + fRec11[1]));
		fVec5[IOTA&2047] = fTemp8;
		fRec9[0] = fVec5[(IOTA-iConst7)&2047];
		double 	fRec10 = (fSlow7 * fVec5[IOTA&2047]);
		double fTemp9 = (0.3 * (fRec9[1] + fRec10));
		double fTemp10 = (fTemp9 + (fTemp0 + (fSlow0 * fRec7[1])));
		fVec6[IOTA&8191] = fTemp10;
		fRec22[0] = ((fConst10 * fRec23[1]) + (fConst9 * fRec22[1]));
		fRec23[0] = ((1 + ((fConst9 * fRec23[1]) + (fConst11 * fRec22[1]))) - iVec0[1]);
		double fTemp11 = (fSlow9 * (1 + fRec22[0]));
		int iTemp12 = int(fTemp11);
		int iTemp13 = int((int((1 + iTemp12)) & 16));
		int iTemp14 = int((iConst12 + iTemp13));
		double fTemp15 = floor(fTemp11);
		double fTemp16 = (fTemp11 - fTemp15);
		int iTemp17 = int((iTemp12 & 16));
		int iTemp18 = int((iConst12 + iTemp17));
		double fTemp19 = ((1 + fTemp15) - fTemp11);
		fRec7[0] = ((fTemp19 * fVec6[(IOTA-iTemp18)&8191]) + (fTemp16 * fVec6[(IOTA-iTemp14)&8191]));
		double fTemp20 = (fTemp0 + fTemp9);
		fRec8[IOTA&32767] = (fRec7[1] - fTemp20);
		fRec6[0] = ((fSlow10 * fRec6[2]) + (fSlow11 * fRec8[(IOTA-iConst13)&32767]));
		double fTemp21 = ((fSlow14 * fRec4[1]) + (fSlow12 * fRec6[0]));
		fVec7[IOTA&16383] = fTemp21;
		fRec4[0] = fVec7[(IOTA-iConst14)&16383];
		double 	fRec5 = (fSlow13 * fVec7[IOTA&16383]);
		fVec8[IOTA&32767] = (fRec4[1] + fRec5);
		fRec0[0] = (fSlow12 * fVec8[(IOTA-iConst15)&32767]);
		double fTemp22 = ((0.5 * fRec0[1]) + fTemp9);
		double fTemp23 = ((fSlow0 * fRec27[1]) + fTemp22);
		fVec9[IOTA&8191] = fTemp23;
		int iTemp24 = int((iConst16 + iTemp13));
		int iTemp25 = int((iConst16 + iTemp17));
		fRec27[0] = ((fTemp19 * fVec9[(IOTA-iTemp25)&8191]) + (fTemp16 * fVec9[(IOTA-iTemp24)&8191]));
		fRec28[IOTA&32767] = (fRec27[1] - fTemp22);
		fRec26[0] = ((fSlow10 * fRec26[2]) + (fSlow11 * fRec28[(IOTA-iConst17)&32767]));
		double fTemp26 = ((fSlow14 * fRec24[1]) + (fSlow12 * fRec26[0]));
		fVec10[IOTA&32767] = fTemp26;
		fRec24[0] = fVec10[(IOTA-iConst18)&32767];
		double 	fRec25 = (fSlow13 * fVec10[IOTA&32767]);
		fVec11[IOTA&32767] = (fRec24[1] + fRec25);
		fRec1[0] = (fSlow12 * fVec11[(IOTA-iConst19)&32767]);
		double fTemp27 = (fTemp20 + (fSlow0 * fRec29[1]));
		fVec12[IOTA&8191] = fTemp27;
		fRec29[0] = ((fTemp19 * fVec12[(IOTA-iTemp18)&8191]) + (fTemp16 * fVec12[(IOTA-iTemp14)&8191]));
		double 	fRec30 = (fRec29[1] - fTemp20);
		double 	fRec2 = fRec30;
		double fTemp28 = ((fSlow0 * fRec31[1]) + fTemp22);
		fVec13[IOTA&8191] = fTemp28;
		fRec31[0] = ((fTemp19 * fVec13[(IOTA-iTemp25)&8191]) + (fTemp16 * fVec13[(IOTA-iTemp24)&8191]));
		double 	fRec32 = (fRec31[1] - fTemp22);
		double 	fRec3 = fRec32;
		output0[i] = (FAUSTFLOAT)((fSlow16 * fTemp2) + (fSlow15 * (fRec0[0] + fRec2)));
		output1[i] = (FAUSTFLOAT)((fSlow16 * fTemp1) + (fSlow15 * (fRec1[0] + fRec3)));
		// post processing
		fRec31[1] = fRec31[0];
		fRec29[1] = fRec29[0];
		fRec1[1] = fRec1[0];
		fRec24[1] = fRec24[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec0[1] = fRec0[0];
		fRec4[1] = fRec4[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec9[1] = fRec9[0];
		fRec11[1] = fRec11[0];
		fRec13[1] = fRec13[0];
		fRec15[1] = fRec15[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		IOTA = IOTA+1;
		iVec0[1] = iVec0[0];
	}
}
		
void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("dattorros_progenitor.bandwidth",N_("Bandwidth"),"S","",&fslider2, 0.9, 0.1, 0.95, 0.0005);
	reg.registerVar("dattorros_progenitor.damping",N_("HF Damp"),"S","",&fslider6, 0.0005, 0.1, 0.95, 0.0005);
	reg.registerVar("dattorros_progenitor.decay diff 1",N_("Decay 1"),"S","",&fslider0, 0.1, 0.0, 0.7, 0.01);
	reg.registerVar("dattorros_progenitor.decay diff 2",N_("Decay 2"),"S","",&fslider8, 0.1, 0.0, 0.5, 0.01);
	reg.registerVar("dattorros_progenitor.decay",N_("Decay"),"S","",&fslider7, 0.1, 0.0, 0.5, 0.01);
	reg.registerVar("dattorros_progenitor.dry/wet",N_("Dry/Wet"),"S","",&fslider9, 0.5, 0.0, 1.0, 0.05);
	reg.registerVar("dattorros_progenitor.excursion",N_("Excursion"),"S","",&fslider5, 0.0, 0.0, 16.0, 0.5);
	reg.registerVar("dattorros_progenitor.input diff 1",N_("Input 1"),"S","",&fslider3, 0.1, 0.0, 0.75, 0.01);
	reg.registerVar("dattorros_progenitor.input diff 2",N_("Input 2"),"S","",&fslider4, 0.1, 0.0, 0.625, 0.01);
	reg.registerVar("dattorros_progenitor.predelay ms",N_("Predelay"),"S","",&fslider1, 0.0, 0.0, 2e+02, 1e+01);
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
              <object class=\"GtkVBox\" id=\"vbox13\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <child>\n\
                  <object class=\"GtkHBox\" id=\"hbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <child>\n\
                      <object class=\"GtkVBox\" id=\"vbox4\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GtkLabel\" id=\"label1\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkLabel\" id=\"label2:rack_label\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"label\" translatable=\"yes\">label</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">False</property>\n\
                            <property name=\"fill\">False</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxMidKnob\" id=\"gxmidknob1\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">dattorros_progenitor.decay</property>\n\
                            <property name=\"label_ref\">label2:rack_label</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">False</property>\n\
                            <property name=\"fill\">False</property>\n\
                            <property name=\"position\">2</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkLabel\" id=\"label2\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">3</property>\n\
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
                      <object class=\"GtkVBox\" id=\"vbox2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"spacing\">6</property>\n\
                        <child>\n\
                          <object class=\"GtkHBox\" id=\"hbox2\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"spacing\">3</property>\n\
                            <child>\n\
                              <object class=\"GtkVBox\" id=\"vbox3\">\n\
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
                                    <property name=\"var_id\">dattorros_progenitor.predelay ms</property>\n\
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
                              <object class=\"GtkVBox\" id=\"vbox8\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label11:rack_label\">\n\
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
                                  <object class=\"GxSmallKnobR\" id=\"gxbigknob6\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">True</property>\n\
                                    <property name=\"receives_default\">True</property>\n\
                                    <property name=\"var_id\">dattorros_progenitor.bandwidth</property>\n\
                                    <property name=\"label_ref\">label11:rack_label</property>\n\
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
                              <object class=\"GtkVBox\" id=\"vbox9\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label21:rack_label\">\n\
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
                                  <object class=\"GxSmallKnobR\" id=\"gxbigknob7\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">True</property>\n\
                                    <property name=\"receives_default\">True</property>\n\
                                    <property name=\"var_id\">dattorros_progenitor.damping</property>\n\
                                    <property name=\"label_ref\">label21:rack_label</property>\n\
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
                              <object class=\"GtkVBox\" id=\"vbox7\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkLabel\" id=\"label5:rack_label\">\n\
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
                                  <object class=\"GxSmallKnobR\" id=\"gxbigknob5\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">True</property>\n\
                                    <property name=\"receives_default\">True</property>\n\
                                    <property name=\"var_id\">dattorros_progenitor.excursion</property>\n\
                                    <property name=\"label_ref\">label5:rack_label</property>\n\
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
                            <property name=\"expand\">False</property>\n\
                            <property name=\"fill\">False</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkFrame\" id=\"frame1:frame_inversed\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"label_xalign\">0</property>\n\
                            <child>\n\
                              <object class=\"GtkHBox\" id=\"hbox4\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox5\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnob\" id=\"gxbigknob3\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">dattorros_progenitor.input diff 1</property>\n\
                                        <property name=\"label_ref\">label3:rack_label_inverse</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label3:rack_label_inverse\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">label</property>\n\
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
                                    <property name=\"position\">0</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox6\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnob\" id=\"gxbigknob4\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">dattorros_progenitor.input diff 2</property>\n\
                                        <property name=\"label_ref\">label4:rack_label_inverse</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label4:rack_label_inverse\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">label</property>\n\
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
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox10\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnob\" id=\"gxbigknob8\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">dattorros_progenitor.decay diff 1</property>\n\
                                        <property name=\"label_ref\">label31:rack_label_inverse</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label31:rack_label_inverse\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">label</property>\n\
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
                                    <property name=\"position\">2</property>\n\
                                  </packing>\n\
                                </child>\n\
                                <child>\n\
                                  <object class=\"GtkVBox\" id=\"vbox11\">\n\
                                    <property name=\"visible\">True</property>\n\
                                    <property name=\"can_focus\">False</property>\n\
                                    <child>\n\
                                      <object class=\"GxSmallKnob\" id=\"gxbigknob9\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">True</property>\n\
                                        <property name=\"receives_default\">True</property>\n\
                                        <property name=\"var_id\">dattorros_progenitor.decay diff 2</property>\n\
                                        <property name=\"label_ref\">label41:rack_label_inverse</property>\n\
                                      </object>\n\
                                      <packing>\n\
                                        <property name=\"expand\">False</property>\n\
                                        <property name=\"fill\">False</property>\n\
                                        <property name=\"position\">0</property>\n\
                                      </packing>\n\
                                    </child>\n\
                                    <child>\n\
                                      <object class=\"GtkLabel\" id=\"label41:rack_label_inverse\">\n\
                                        <property name=\"visible\">True</property>\n\
                                        <property name=\"can_focus\">False</property>\n\
                                        <property name=\"label\" translatable=\"yes\">label</property>\n\
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
                                    <property name=\"position\">3</property>\n\
                                  </packing>\n\
                                </child>\n\
                              </object>\n\
                            </child>\n\
                            <child type=\"label\">\n\
                              <object class=\"GtkLabel\" id=\"label300:rack_label_inverse\">\n\
                                <property name=\"visible\">True</property>\n\
                                <property name=\"can_focus\">False</property>\n\
                                <property name=\"label\" translatable=\"yes\">Diffusion</property>\n\
                                <property name=\"use_markup\">True</property>\n\
                              </object>\n\
                            </child>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">True</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GtkVBox\" id=\"vbox12\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <child>\n\
                          <object class=\"GtkLabel\" id=\"label3\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">0</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkLabel\" id=\"label51:rack_label\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                            <property name=\"label\" translatable=\"yes\">label</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">False</property>\n\
                            <property name=\"fill\">False</property>\n\
                            <property name=\"position\">1</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GxMidKnob\" id=\"gxmidknob2\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">True</property>\n\
                            <property name=\"receives_default\">True</property>\n\
                            <property name=\"var_id\">dattorros_progenitor.dry/wet</property>\n\
                            <property name=\"label_ref\">label51:rack_label</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">2</property>\n\
                          </packing>\n\
                        </child>\n\
                        <child>\n\
                          <object class=\"GtkLabel\" id=\"label4\">\n\
                            <property name=\"visible\">True</property>\n\
                            <property name=\"can_focus\">False</property>\n\
                          </object>\n\
                          <packing>\n\
                            <property name=\"expand\">True</property>\n\
                            <property name=\"fill\">True</property>\n\
                            <property name=\"position\">3</property>\n\
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
                    <property name=\"fill\">True</property>\n\
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
            <property name=\"expand\">False</property>\n\
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
                <property name=\"var_id\">dattorros_progenitor.dry/wet</property>\n\
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
                <property name=\"label\" translatable=\"yes\">Dry/Wet</property>\n\
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
#define PARAM(p) ("dattorros_progenitor" "." p)
// dattorros progenitor (Plate reverb)

b.openHorizontalhideBox("");
b.create_master_slider(PARAM("dry/wet"), _("dry/wet"));
b.closeBox();

b.openHorizontalBox("");
b.openVerticalBox("");
b.openHorizontalBox("");
{
	b.create_small_rackknob(PARAM("predelay ms"),  _("predelay ms"));
	b.create_small_rackknob(PARAM("bandwidth"),    _(" bandwidth "));
	b.create_small_rackknob(PARAM("input diff 1"), _(" in diff 1 "));
	b.create_small_rackknob(PARAM("input diff 2"), _(" in diff 2 "));
	b.create_small_rackknob(PARAM("excursion"),    _(" excursion "));

	
}
b.closeBox();
b.openHorizontalBox("");
{
	b.create_small_rackknob(PARAM("decay"),        _("  decay   "));
	b.create_small_rackknob(PARAM("decay diff 1"), _("dec diff 1"));
	b.create_small_rackknob(PARAM("decay diff 2"), _("dec diff 2"));
	b.create_small_rackknob(PARAM("damping"),      _("HF damping"));
	b.create_small_rackknobr(PARAM("dry/wet"),     _("  dry/wet "));
}
b.closeBox();
b.closeBox();
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

} // end namespace dattorros_progenitor
