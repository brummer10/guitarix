// generated from file '../src/faust/dattorros_progenitor.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace dattorros_progenitor {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	class SIG0 {
	  private:
		int 	fSamplingFreq;
		int 	iRec22[2];
	  public:
		int getNumInputs() 	{ return 0; }
		int getNumOutputs() 	{ return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			for (int i=0; i<2; i++) iRec22[i] = 0;
		}
		void fill (int count, double output[]) {
			for (int i=0; i<count; i++) {
				iRec22[0] = (1 + iRec22[1]);
				output[i] = sin((9.587379924285257e-05 * double((iRec22[0] - 1))));
				// post processing
				iRec22[1] = iRec22[0];
			}
		}
	};
			FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	int 	IOTA;
	double 	fVec0[262144];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	FAUSTFLOAT 	fslider3;
	double 	fConst3;
	double 	fRec18[2];
	double 	fRec19[2];
	double 	fRec20[2];
	double 	fRec21[2];
	FAUSTFLOAT 	fslider4;
	double 	fRec17[3];
	double 	fVec1[1024];
	int 	iConst4;
	double 	fRec15[2];
	double 	fVec2[1024];
	int 	iConst5;
	double 	fRec13[2];
	double 	fVec3[4096];
	int 	iConst6;
	double 	fRec11[2];
	double 	fVec4[2048];
	int 	iConst7;
	double 	fRec9[2];
	double 	fVec5[8192];
	static double 	ftbl0[65536];
	double 	fConst8;
	double 	fRec23[2];
	FAUSTFLOAT 	fslider5;
	int 	iConst9;
	double 	fRec7[2];
	double 	fRec8[32768];
	int 	iConst10;
	FAUSTFLOAT 	fslider6;
	double 	fRec6[3];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	double 	fVec6[16384];
	int 	iConst11;
	double 	fRec4[2];
	double 	fVec7[32768];
	int 	iConst12;
	double 	fRec0[2];
	double 	fVec8[8192];
	int 	iConst13;
	double 	fRec27[2];
	double 	fRec28[32768];
	int 	iConst14;
	double 	fRec26[3];
	double 	fVec9[32768];
	int 	iConst15;
	double 	fRec24[2];
	double 	fVec10[32768];
	int 	iConst16;
	double 	fRec1[2];
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


double Dsp::ftbl0[65536];

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
	for (int i=0; i<262144; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<1024; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<1024; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<4096; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2048; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<8192; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<32768; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<16384; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<32768; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<8192; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<32768; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<32768; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<32768; i++) fVec10[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	SIG0 sig0;
	sig0.init(samplingFreq);
	sig0.fill(65536,ftbl0);
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1e+01 / double(iConst0));
	fConst2 = (0 - fConst1);
	fConst3 = (0.001 * iConst0);
	iConst4 = int((0.004771345048889486 * iConst0));
	iConst5 = int((0.0035953092974026412 * iConst0));
	iConst6 = int((0.01273478713752898 * iConst0));
	iConst7 = int((0.009307482947481604 * iConst0));
	fConst8 = (1.0 / double(iConst0));
	iConst9 = int((0.022042270085010585 * iConst0));
	iConst10 = int((0.14962534861059776 * iConst0));
	iConst11 = int((0.060481838647894894 * iConst0));
	iConst12 = int((0.12499579987231611 * iConst0));
	iConst13 = int((0.029972111152179026 * iConst0));
	iConst14 = int((0.14169550754342933 * iConst0));
	iConst15 = int((0.08924431302711602 * iConst0));
	iConst16 = int((0.10628003091293975 * iConst0));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	double 	fSlow0 = double(fslider0);
	double 	fSlow1 = double(fslider1);
	double 	fSlow2 = (0 - fSlow1);
	double 	fSlow3 = double(fslider2);
	double 	fSlow4 = (0 - fSlow3);
	double 	fSlow5 = (fConst3 * double(fslider3));
	double 	fSlow6 = double(fslider4);
	double 	fSlow7 = (0.5 * fSlow6);
	double 	fSlow8 = (1 - fSlow6);
	double 	fSlow9 = (0.5 * double(fslider5));
	double 	fSlow10 = double(fslider6);
	double 	fSlow11 = (1 - fSlow10);
	double 	fSlow12 = double(fslider7);
	double 	fSlow13 = double(fslider8);
	double 	fSlow14 = (0 - fSlow13);
	double 	fSlow15 = double(fslider9);
	double 	fSlow16 = (1 - fSlow15);
	for (int i=0; i<count; i++) {
		double fTemp0 = (0.5 * fRec1[1]);
		double fTemp1 = (double)input1[i];
		double fTemp2 = (double)input0[i];
		double fTemp3 = (fTemp2 + fTemp1);
		fVec0[IOTA&262143] = fTemp3;
		double fTemp4 = ((int((fRec18[1] != 0.0)))?((int(((fRec19[1] > 0.0) & (fRec19[1] < 1.0))))?fRec18[1]:0):((int(((fRec19[1] == 0.0) & (fSlow5 != fRec20[1]))))?fConst1:((int(((fRec19[1] == 1.0) & (fSlow5 != fRec21[1]))))?fConst2:0)));
		fRec18[0] = fTemp4;
		fRec19[0] = max(0.0, min(1.0, (fRec19[1] + fTemp4)));
		fRec20[0] = ((int(((fRec19[1] >= 1.0) & (fRec21[1] != fSlow5))))?fSlow5:fRec20[1]);
		fRec21[0] = ((int(((fRec19[1] <= 0.0) & (fRec20[1] != fSlow5))))?fSlow5:fRec21[1]);
		fRec17[0] = ((fSlow8 * fRec17[2]) + (fSlow7 * (((1.0 - fRec19[0]) * fVec0[(IOTA-int((int(fRec20[0]) & 262143)))&262143]) + (fRec19[0] * fVec0[(IOTA-int((int(fRec21[0]) & 262143)))&262143]))));
		double fTemp5 = (fRec17[0] + (fSlow4 * fRec15[1]));
		fVec1[IOTA&1023] = fTemp5;
		fRec15[0] = fVec1[(IOTA-iConst4)&1023];
		double 	fRec16 = (fSlow3 * fVec1[IOTA&1023]);
		double fTemp6 = (fRec15[1] + (fRec16 + (fSlow4 * fRec13[1])));
		fVec2[IOTA&1023] = fTemp6;
		fRec13[0] = fVec2[(IOTA-iConst5)&1023];
		double 	fRec14 = (fSlow3 * fVec2[IOTA&1023]);
		double fTemp7 = (fRec13[1] + (fRec14 + (fSlow2 * fRec11[1])));
		fVec3[IOTA&4095] = fTemp7;
		fRec11[0] = fVec3[(IOTA-iConst6)&4095];
		double 	fRec12 = (fSlow1 * fVec3[IOTA&4095]);
		double fTemp8 = (fRec11[1] + (fRec12 + (fSlow2 * fRec9[1])));
		fVec4[IOTA&2047] = fTemp8;
		fRec9[0] = fVec4[(IOTA-iConst7)&2047];
		double 	fRec10 = (fSlow1 * fVec4[IOTA&2047]);
		double fTemp9 = (0.3 * (fRec10 + fRec9[1]));
		double fTemp10 = (fTemp9 + ((fSlow0 * fRec7[1]) + fTemp0));
		fVec5[IOTA&8191] = fTemp10;
		double fTemp11 = (fConst8 + fRec23[1]);
		fRec23[0] = (fTemp11 - floor(fTemp11));
		double fTemp12 = (fSlow9 * (1 + ftbl0[int((65536.0 * fRec23[0]))]));
		int iTemp13 = int(fTemp12);
		int iTemp14 = (1 + iTemp13);
		int iTemp15 = int((int(iTemp14) & 16));
		double fTemp16 = (fTemp12 - iTemp13);
		double fTemp17 = (iTemp14 - fTemp12);
		int iTemp18 = int((iTemp13 & 16));
		fRec7[0] = ((fVec5[(IOTA-int((iConst9 + iTemp18)))&8191] * fTemp17) + (fTemp16 * fVec5[(IOTA-int((iConst9 + iTemp15)))&8191]));
		fRec8[IOTA&32767] = (fRec7[1] - (fTemp0 + fTemp9));
		fRec6[0] = ((fSlow10 * fRec6[2]) + (fSlow11 * fRec8[(IOTA-iConst10)&32767]));
		double fTemp19 = ((fSlow14 * fRec4[1]) + (fSlow12 * fRec6[0]));
		fVec6[IOTA&16383] = fTemp19;
		fRec4[0] = fVec6[(IOTA-iConst11)&16383];
		double 	fRec5 = (fSlow13 * fVec6[IOTA&16383]);
		fVec7[IOTA&32767] = (fRec5 + fRec4[1]);
		fRec0[0] = (fSlow12 * fVec7[(IOTA-iConst12)&32767]);
		double fTemp20 = (0.5 * fRec0[1]);
		double fTemp21 = (fTemp20 + (fTemp9 + (fSlow0 * fRec27[1])));
		fVec8[IOTA&8191] = fTemp21;
		fRec27[0] = ((fTemp17 * fVec8[(IOTA-int((iConst13 + iTemp18)))&8191]) + (fTemp16 * fVec8[(IOTA-int((iConst13 + iTemp15)))&8191]));
		fRec28[IOTA&32767] = (fRec27[1] - (fTemp9 + fTemp20));
		fRec26[0] = ((fSlow10 * fRec26[2]) + (fSlow11 * fRec28[(IOTA-iConst14)&32767]));
		double fTemp22 = ((fSlow14 * fRec24[1]) + (fSlow12 * fRec26[0]));
		fVec9[IOTA&32767] = fTemp22;
		fRec24[0] = fVec9[(IOTA-iConst15)&32767];
		double 	fRec25 = (fSlow13 * fVec9[IOTA&32767]);
		fVec10[IOTA&32767] = (fRec25 + fRec24[1]);
		fRec1[0] = (fSlow12 * fVec10[(IOTA-iConst16)&32767]);
		double 	fRec2 = fRec8[(IOTA-0)&32767];
		double 	fRec3 = fRec28[(IOTA-0)&32767];
		output0[i] = (FAUSTFLOAT)((fSlow16 * fTemp2) + (fSlow15 * (fRec0[0] + fRec2)));
		output1[i] = (FAUSTFLOAT)((fSlow16 * fTemp1) + (fSlow15 * (fRec1[0] + fRec3)));
		// post processing
		fRec1[1] = fRec1[0];
		fRec24[1] = fRec24[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec0[1] = fRec0[0];
		fRec4[1] = fRec4[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec23[1] = fRec23[0];
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
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("dattorros_progenitor.bandwidth",N_("Bandwidth"),"S","",&fslider4, 0.9, 0.1, 0.95, 0.0005);
	reg.registerVar("dattorros_progenitor.damping",N_("HF Damp"),"S","",&fslider6, 0.0005, 0.1, 0.95, 0.0005);
	reg.registerVar("dattorros_progenitor.decay diff 1",N_("Decay 1"),"S","",&fslider0, 0.1, 0.0, 0.7, 0.01);
	reg.registerVar("dattorros_progenitor.decay diff 2",N_("Decay 2"),"S","",&fslider8, 0.1, 0.0, 0.5, 0.01);
	reg.registerVar("dattorros_progenitor.decay",N_("Decay"),"S","",&fslider7, 0.1, 0.0, 0.5, 0.01);
	reg.registerVar("dattorros_progenitor.dry/wet",N_("Dry/Wet"),"S","",&fslider9, 0.5, 0.0, 1.0, 0.05);
	reg.registerVar("dattorros_progenitor.excursion",N_("Excursion"),"S","",&fslider5, 0.0, 0.0, 16.0, 0.5);
	reg.registerVar("dattorros_progenitor.input diff 1",N_("Input 1"),"S","",&fslider2, 0.1, 0.0, 0.75, 0.01);
	reg.registerVar("dattorros_progenitor.input diff 2",N_("Input 2"),"S","",&fslider1, 0.1, 0.0, 0.625, 0.01);
	reg.registerVar("dattorros_progenitor.predelay ms",N_("Predelay"),"S","",&fslider3, 0.0, 0.0, 2e+02, 1e+01);
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
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GtkVBox\" id=\"vbox13\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <child>\n\
                  <object class=\"GtkHBox\" id=\"hbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"spacing\">4</property>\n\
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
