// generated from file '../src/faust/duck_delay.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace duck_delay {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	int 	iConst0;
	double 	fConst1;
	double 	fRec2[2];
	FAUSTFLOAT 	fslider1;
	double 	fRec1[2];
	FAUSTFLOAT 	fslider2;
	double 	fConst2;
	double 	fConst3;
	double 	fRec0[2];
	FAUSTFLOAT 	fslider3;
	int 	IOTA;
	double 	fVec0[524288];
	FAUSTFLOAT 	fslider4;
	double 	fRec4[2];
	double 	fConst4;
	double 	fRec3[2];
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
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
	id = "duckDelay";
	name = N_("Duck Delay");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Echo / Delay");       // category
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
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<524288; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / double(iConst0));
	fConst2 = exp((0 - (1e+01 / double(iConst0))));
	fConst3 = (1.0 - fConst2);
	IOTA = 0;
	fConst4 = (0.001 * iConst0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = exp((0 - (fConst1 / double(fslider0))));
	double 	fSlow1 = (1.0 - fSlow0);
	double 	fSlow2 = exp((0 - (fConst1 / double(fslider1))));
	double 	fSlow3 = (1.0 - fSlow2);
	double 	fSlow4 = pow(10,(0.05 * double(fslider2)));
	double 	fSlow5 = double(fslider3);
	double 	fSlow6 = (fConst3 * double(fslider4));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		double fTemp1 = fabs(fTemp0);
		fRec2[0] = ((fSlow0 * max(fTemp1, fRec2[1])) + (fSlow1 * fTemp1));
		fRec1[0] = ((fSlow2 * fRec1[1]) + (fSlow3 * fRec2[0]));
		fRec0[0] = ((fConst2 * fRec0[1]) + (fConst3 * (1 - ((fSlow4 * fRec1[0]) > 1))));
		double fTemp2 = (fTemp0 + (fSlow5 * fRec3[1]));
		fVec0[IOTA&524287] = fTemp2;
		fRec4[0] = (fSlow6 + (fConst2 * fRec4[1]));
		double fTemp3 = (fConst4 * fRec4[0]);
		int iTemp4 = int(fTemp3);
		int iTemp5 = (1 + iTemp4);
		fRec3[0] = ((fVec0[(IOTA-int((iTemp4 & 393215)))&524287] * (iTemp5 - fTemp3)) + ((fTemp3 - iTemp4) * fVec0[(IOTA-int((int(iTemp5) & 393215)))&524287]));
		output0[i] = (FAUSTFLOAT)(fTemp0 + (fRec3[0] * fRec0[0]));
		// post processing
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		IOTA = IOTA+1;
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("duckDelay.amount","","S","",&fslider2, 0.5, 0.0, 56.0, 0.05);
	reg.registerVar("duckDelay.attack","","S","",&fslider1, 0.1, 0.05, 0.5, 0.05);
	reg.registerVar("duckDelay.feedback","","S","",&fslider3, 0.0, 0.0, 1.0, 0.05);
	reg.registerVar("duckDelay.relese","","S","",&fslider0, 0.1, 0.05, 2.0, 0.05);
	reg.registerVar("duckDelay.time","","S","",&fslider4, 5e+02, 1.0, 2e+03, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("duckDelay" "." p)
// ----- ducking delay
b.openHorizontalhideBox("");
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalTableBox("");
    {
		b.create_small_rackknob(PARAM("time"),     _("   time ms  "));
		b.create_small_rackknob(PARAM("feedback"), _("   feedback "));
		b.create_small_rackknob(PARAM("attack"),   _("   attack s "));
		b.create_small_rackknob(PARAM("relese"),   _("  release s "));
		b.create_small_rackknob(PARAM("amount"),   _("  amount dB "));
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

} // end namespace duck_delay
