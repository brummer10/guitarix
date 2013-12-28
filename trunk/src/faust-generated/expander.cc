// generated from file '../src/faust/expander.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)


namespace expander {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fRec1[2];
	double 	fConst3;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	double 	fRec0[2];
	FAUSTFLOAT 	fentry0;
	FAUSTFLOAT 	fentry1;
	FAUSTFLOAT 	fentry2;
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
	id = "expander";
	name = N_("Expander");
	groups = 0;
	description = N_("expander unit"); // description (tooltip)
	category = N_("Guitar Effects");       // category
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
	fConst1 = exp((0 - (1e+01 / double(iConst0))));
	fConst2 = (1 - fConst1);
	fConst3 = (1.0 / double(iConst0));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = exp((0 - (fConst3 / max(fConst3, fslider0))));
	double 	fSlow1 = exp((0 - (fConst3 / max(fConst3, fslider1))));
	double 	fSlow2 = fentry1;
	double 	fSlow3 = (fSlow2 + fentry0);
	double 	fSlow4 = (1.0 / (0.001 + fSlow2));
	double 	fSlow5 = (fentry2 - 1);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec1[0] = ((fConst2 * fabs(fTemp0)) + (fConst1 * fRec1[1]));
		double fTemp1 = max(fRec1[0], fTemp0);
		double fTemp2 = ((fSlow1 * (fRec0[1] >= fTemp1)) + (fSlow0 * (fRec0[1] < fTemp1)));
		fRec0[0] = ((fTemp1 * (0 - (fTemp2 - 1))) + (fRec0[1] * fTemp2));
		double fTemp3 = max((double)0, (fSlow3 - (20 * log10(fRec0[0]))));
		output0[i] = (FAUSTFLOAT)(fTemp0 * pow(10,(0.05 * (fTemp3 * (0 - (fSlow5 * min((double)1, max((double)0, (fSlow4 * fTemp3)))))))));
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("expander.attack","","S","",&fslider0, 0.001, 0.0, 1.0, 0.001);
	reg.registerVar("expander.knee","","S","",&fentry1, 3.0, 0.0, 2e+01, 0.1);
	reg.registerVar("expander.ratio","","S","",&fentry2, 2.0, 1.0, 2e+01, 0.1);
	reg.registerVar("expander.release","","S","",&fslider1, 0.1, 0.0, 1e+01, 0.01);
	reg.registerVar("expander.threshold","","S","",&fentry0, -4e+01, -96.0, 1e+01, 0.1);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("expander" "." p)
// ----- the expander
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("ratio"), _("ratio"));
b.closeBox();
b.openHorizontalTableBox("");
{
    b.create_small_rackknob(PARAM("knee"), _("knee"));
    b.create_small_rackknobr(PARAM("ratio"), _("ratio"));
    b.create_small_rackknob(PARAM("threshold"), _("threshold"));

    b.create_small_rackknob(PARAM("attack"), _("attack"));
    b.create_small_rackknob(PARAM("release"), _("release"));
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

} // end namespace expander
