// generated from file '../src/faust/bassbooster.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace bassbooster {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fRec0[3];
	FAUSTFLOAT fVslider0;
	double fRec1[2];

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



static const char* parm_groups[] = {
	".bassbooster", N_("Bassbooster"),
	0
	};

Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "amp.bass_boost";
	name = N_("Bassbooster");
	groups = parm_groups;
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
	for (int l0 = 0; l0 < 3; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec1[l1] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::tan(376.99111843077515 / std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate))));
	fConst1 = 1.0 / (fConst0 * (fConst0 + 1.4142135623730951) + 1.0);
	fConst2 = fConst0 * (fConst0 + -1.4142135623730951) + 1.0;
	fConst3 = mydsp_faustpower2_f(fConst0);
	fConst4 = 2.0 * (fConst3 + -1.0);
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = 9.9999999999988987e-05 * double(fVslider0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = double(input0[i0]) - fConst1 * (fConst2 * fRec0[2] + fConst4 * fRec0[1]);
		fRec1[0] = fSlow0 + 0.99990000000000001 * fRec1[1];
		double fTemp0 = std::pow(10.0, 0.050000000000000003 * fRec1[0]);
		double fTemp1 = std::sqrt(2.0 * fTemp0);
		double fTemp2 = fConst0 * fTemp0;
		output0[i0] = FAUSTFLOAT(fConst1 * (fRec0[0] * (fConst0 * (fTemp1 + fTemp2) + 1.0) + 2.0 * fRec0[1] * (fConst3 * fTemp0 + -1.0) + fRec0[2] * (1.0 - fConst0 * (fTemp1 - fTemp2))));
		fRec0[2] = fRec0[1];
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
	reg.registerFloatVar("bassbooster.Level","","S","",&fVslider0, 10.0, 0.5, 20.0, 0.5, 0);
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

} // end namespace bassbooster
