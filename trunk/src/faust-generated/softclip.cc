// generated from file '../src/faust/softclip.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace softclip {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fHslider0;

	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void init_static(unsigned int sample_rate, PluginDef*);
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
	id = "amp.clip";
	name = N_("softclip");
	groups = 0;
	description = ""; // description (tooltip)
	category = "";       // category
	shortname = "";     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	load_ui = 0;
	clear_state = 0;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = (0.88 * (2.0 - double(fHslider0)));
	double fSlow1 = (-1.0 * fSlow0);
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = double(input0[i]);
		double fTemp1 = std::max<double>(fSlow1, std::min<double>(fSlow0, fTemp0));
		output0[i] = FAUSTFLOAT((fTemp1 + (0.33000000000000002 * (fTemp0 - std::max<double>(fSlow1, std::min<double>(fSlow0, fTemp1))))));
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("amp.fuzz","","S","",&fHslider0, 0.0, 0.0, 1.99, 0.01, 0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace softclip
