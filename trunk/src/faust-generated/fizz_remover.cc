// generated from file '../src/faust/fizz_remover.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace fizz_remover {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fRec0[3];
	double fConst8;
	double fConst9;
	double fConst10;
	double fRec1[3];

	void clear_state_f();
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static void init_static(unsigned int sample_rate, PluginDef*);
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
	id = "antyfizz";
	name = N_("Fizz Remover");
	groups = 0;
	description = ""; // description (tooltip)
	category = "";       // category
	shortname = "";     // shortname
	mono_audio = 0;
	stereo_audio = compute_static;
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
	for (int l1 = 0; l1 < 3; l1 = l1 + 1) fRec1[l1] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = std::tan(17454.68878334489 / fConst0);
	fConst2 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst1));
	fConst3 = fConst0 * std::sin(34909.37756668978 / fConst0);
	fConst4 = 5463.779747862935 / fConst3;
	fConst5 = 1.0 / fConst1;
	fConst6 = (fConst5 - fConst4) / fConst1 + 1.0;
	fConst7 = 1.0 / ((fConst5 + fConst4) / fConst1 + 1.0);
	fConst8 = 2053.4927980405755 / fConst3;
	fConst9 = (fConst5 - fConst8) / fConst1 + 1.0;
	fConst10 = (fConst5 + fConst8) / fConst1 + 1.0;
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = fConst2 * fRec0[1];
		fRec0[0] = double(input0[i0]) - fConst7 * (fConst6 * fRec0[2] + fTemp0);
		output0[i0] = FAUSTFLOAT(fConst7 * (fTemp0 + fConst10 * fRec0[0] + fConst9 * fRec0[2]));
		double fTemp1 = fConst2 * fRec1[1];
		fRec1[0] = double(input1[i0]) - fConst7 * (fConst6 * fRec1[2] + fTemp1);
		output1[i0] = FAUSTFLOAT(fConst7 * (fTemp1 + fConst10 * fRec1[0] + fConst9 * fRec1[2]));
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
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

} // end namespace fizz_remover
