// generated from file '../src/faust/flanger.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace flanger {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider1;
	int 	IOTA;
	double 	fVec1[2048];
	FAUSTFLOAT 	fslider2;
	int 	iConst0;
	double 	fConst1;
	double 	fRec1[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	double 	fRec0[2];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fcheckbox0;
	double 	fVec2[2048];
	double 	fRec3[2];
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
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
	id = "flanger";
	name = N_("Flanger");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Modulation");       // category
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
	for (int i=0; i<2048; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2048; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (0.10471975511965977 / double(iConst0));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	double 	fSlow0 = pow(10,(0.05 * double(fslider0)));
	double 	fSlow1 = double(fslider1);
	double 	fSlow2 = (fConst1 * double(fslider2));
	double 	fSlow3 = cos(fSlow2);
	double 	fSlow4 = sin(fSlow2);
	double 	fSlow5 = (0 - fSlow4);
	double 	fSlow6 = (0.0005 * double(fslider3));
	double 	fSlow7 = (0.001 * double(fslider4));
	double 	fSlow8 = double(fslider5);
	double 	fSlow9 = ((int(double(fcheckbox0)))?(0 - fSlow8):fSlow8);
	for (int i=0; i<count; i++) {
		double fTemp0 = (fSlow0 * (double)input0[i]);
		iVec0[0] = 1;
		double fTemp1 = ((fSlow1 * fRec0[1]) - fTemp0);
		fVec1[IOTA&2047] = fTemp1;
		fRec1[0] = ((fSlow4 * fRec2[1]) + (fSlow3 * fRec1[1]));
		fRec2[0] = ((1 + ((fSlow3 * fRec2[1]) + (fSlow5 * fRec1[1]))) - iVec0[1]);
		double fTemp2 = (iConst0 * (fSlow7 + (fSlow6 * (1 + fRec1[0]))));
		int iTemp3 = int(fTemp2);
		int iTemp4 = (1 + iTemp3);
		fRec0[0] = ((fVec1[(IOTA-int((iTemp3 & 2047)))&2047] * (iTemp4 - fTemp2)) + ((fTemp2 - iTemp3) * fVec1[(IOTA-int((int(iTemp4) & 2047)))&2047]));
		output0[i] = (FAUSTFLOAT)(0.5 * (fTemp0 + (fSlow9 * fRec0[0])));
		double fTemp5 = (fSlow0 * (double)input1[i]);
		double fTemp6 = ((fSlow1 * fRec3[1]) - fTemp5);
		fVec2[IOTA&2047] = fTemp6;
		double fTemp7 = (iConst0 * (fSlow7 + (fSlow6 * (1 + fRec2[0]))));
		int iTemp8 = int(fTemp7);
		int iTemp9 = (1 + iTemp8);
		fRec3[0] = ((fVec2[(IOTA-int((iTemp8 & 2047)))&2047] * (iTemp9 - fTemp7)) + ((fTemp7 - iTemp8) * fVec2[(IOTA-int((int(iTemp9) & 2047)))&2047]));
		output1[i] = (FAUSTFLOAT)(0.5 * (fTemp5 + (fSlow9 * fRec3[0])));
		// post processing
		fRec3[1] = fRec3[0];
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
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
	reg.registerVar("flanger.depth","","S","",&fslider5, 1.0, 0.0, 1.0, 0.01);
	reg.registerVar("flanger.feedback gain","","S","",&fslider1, 0.0, 0.0, 1.0, 0.01);
	reg.registerVar("flanger.flange delay","","S","",&fslider3, 1e+01, 0.0, 2e+01, 0.01);
	reg.registerVar("flanger.flange delay offset","","S","",&fslider4, 1.0, 0.0, 2e+01, 0.01);
	static const value_pair fcheckbox0_values[] = {{"linear"},{"invert"},{0}};
	reg.registerEnumVar("flanger.invert","","B","",fcheckbox0_values,&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("flanger.level","","S","",&fslider0, 0.0, -6e+01, 1e+01, 0.1);
	reg.registerVar("flanger.lfobpm",N_("LFO freq (bpm)"),"S",N_("LFO in Beats per Minute"),&fslider2, 24.0, 24.0, 3.6e+02, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("flanger" "." p)
// flanger
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("level"), _("level"));
b.closeBox();
b.openHorizontalBox("");
{
    b.openHorizontalBox("");
    {
	b.create_small_rackknobr(PARAM("level"), _("  level  "));
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.openHorizontalBox("");
	{
	    b.create_small_rackknob(PARAM("feedback gain"), _(" feedback "));
	    b.create_small_rackknob(PARAM("depth"), _("  depth  "));
	    b.create_small_rackknob(PARAM("flange delay"), _("  delay  "));
	    b.create_small_rackknob(PARAM("flange delay offset"), _(" delay offset"));
	    b.create_small_rackknob(PARAM("lfobpm"), _(" LFO freq (bpm)"));
	}
	b.closeBox();
	b.insertSpacer();
	b.openHorizontalBox("");
	{
	    b.insertSpacer();
	    b.create_selector(PARAM("invert"), "invert");
	    b.insertSpacer();
	    b.insertSpacer();
	    b.insertSpacer();
	    b.insertSpacer();
	    b.insertSpacer();
	    b.insertSpacer();
	}
	b.closeBox();
	b.openFrameBox("");
	b.closeBox();
    }
    b.closeBox();
}
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

} // end namespace flanger
