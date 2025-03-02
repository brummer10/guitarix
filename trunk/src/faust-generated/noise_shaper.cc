// generated from file '../src/faust/noise_shaper.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace noise_shaper {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fRec0[2];
	FAUSTFLOAT fVslider0;

	void clear_state_f();
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
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
	id = "shaper";
	name = N_("Shaper");
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
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = std::exp(-(0.1 / fConst0));
	fConst2 = std::exp(-(2e+02 / fConst0));
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = double(fVslider0);
	double fSlow1 = 5.0 * fSlow0;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		double fTemp1 = std::max<double>(1.0, std::fabs(fTemp0));
		double fTemp2 = fConst2 * double(fRec0[1] < fTemp1) + fConst1 * double(fRec0[1] >= fTemp1);
		fRec0[0] = fRec0[1] * fTemp2 + fTemp1 * (1.0 - fTemp2);
		double fTemp3 = std::max<double>(0.0, fSlow1 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec0[0])));
		double fTemp4 = std::min<double>(1.0, std::max<double>(0.0, 0.09522902580706599 * fTemp3));
		output0[i0] = FAUSTFLOAT(fTemp0 * std::pow(1e+01, 0.05 * (fSlow0 - 0.5 * (fTemp3 * fTemp4 / (0.5 * fTemp4 + 1.0)))));
		fRec0[1] = fRec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("shaper.sharper",N_("sharper"),"S","",&fVslider0, 1.0, 1.0, 1e+01, 1.0, 0);
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

} // end namespace noise_shaper
