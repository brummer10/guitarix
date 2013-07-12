// generated from file '../src/faust/compressor.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)


namespace compressor {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fentry0;
	FAUSTFLOAT 	fentry1;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fRec1[2];
	double 	fConst3;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	double 	fRec0[2];
	FAUSTFLOAT 	fentry2;
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
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
	id = "compressor";
	name = N_("Compressor");
	groups = 0;
	description = ""; // description (tooltip)
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

void always_inline Dsp::compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fentry1;
	double 	fSlow1 = (fSlow0 - fentry0);
	double 	fSlow2 = exp((0 - (fConst3 / max(fConst3, fslider0))));
	double 	fSlow3 = exp((0 - (fConst3 / max(fConst3, fslider1))));
	double 	fSlow4 = (1.0 / (0.001 + fSlow0));
	double 	fSlow5 = (fentry2 - 1);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec1[0] = ((fConst2 * fabs((fTemp0 + 1e-20))) + (fConst1 * fRec1[1]));
		double fTemp1 = ((fSlow3 * (fRec0[1] >= fRec1[0])) + (fSlow2 * (fRec0[1] < fRec1[0])));
		fRec0[0] = ((fRec1[0] * (0 - (fTemp1 - 1))) + (fRec0[1] * fTemp1));
		double fTemp2 = max((double)0, ((20 * log10(fRec0[0])) + fSlow1));
		double fTemp3 = (fSlow5 * min((double)1, max((double)0, (fSlow4 * fTemp2))));
		output0[i] = (FAUSTFLOAT)(fTemp0 * pow(10,(0.05 * ((fTemp2 * (0 - fTemp3)) / (1 + fTemp3)))));
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
	}
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("compressor.attack","","S","",&fslider0, 0.002, 0.0, 1.0, 0.001);
	reg.registerVar("compressor.knee","","S","",&fentry1, 3.0, 0.0, 2e+01, 0.1);
	reg.registerVar("compressor.ratio","","S","",&fentry2, 2.0, 1.0, 2e+01, 0.1);
	reg.registerVar("compressor.release","","S","",&fslider1, 0.5, 0.0, 1e+01, 0.01);
	reg.registerVar("compressor.threshold","","S","",&fentry0, -2e+01, -96.0, 1e+01, 0.1);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("compressor" "." p)
// ----- the compressor
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("ratio"), N_("ratio"));
b.closeBox();
b.openHorizontalTableBox("");
{
    b.create_small_rackknob(PARAM("knee"), N_("knee"));
    b.create_small_rackknobr(PARAM("ratio"), N_("ratio"));
    b.create_small_rackknob(PARAM("threshold"), N_("threshold"));

    b.create_small_rackknob(PARAM("attack"), N_("attack"));
    b.create_small_rackknob(PARAM("release"), N_("release"));
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

} // end namespace compressor
