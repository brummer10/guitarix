// generated from file '../src/faust/hardlim.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace hardlim {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fRec5[2];
	double fRec4[2];
	double fRec3[2];
	double fRec0[2];
	int iRec1[2];
	double fRec2[2];
	FAUSTFLOAT fVbargraph0;

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
	id = "hardlim";
	name = N_("?limiter");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec5[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec4[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec3[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec0[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) iRec1[l4] = 0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec2[l5] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 1.0 / fConst0;
	fConst2 = std::exp(0.0 - 2500.0 / fConst0);
	fConst3 = 1.0 - fConst2;
	fConst4 = std::exp(0.0 - 1250.0 / fConst0);
	fConst5 = std::exp(0.0 - 2.0 / fConst0);
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		int iTemp1 = iRec1[1] < 1024;
		double fTemp2 = double(input1[i0]);
		double fTemp3 = std::fabs(std::max<double>(std::fabs(fTemp0), std::fabs(fTemp2)));
		double fTemp4 = ((fRec4[1] > fTemp3) ? fConst5 : fConst4);
		fRec5[0] = fTemp3 * (1.0 - fTemp4) + fTemp4 * fRec5[1];
		fRec4[0] = fRec5[0];
		fRec3[0] = fConst3 * (0.0 - 0.98999999999999999 * std::max<double>(20.0 * std::log10(std::max<double>(2.2250738585072014e-308, fRec4[0])), 0.0)) + fConst2 * fRec3[1];
		double fTemp5 = std::pow(10.0, 0.050000000000000003 * fRec3[0]);
		double fTemp6 = std::max<double>(fConst1, std::fabs(1.0 - fTemp5));
		double fElse1 = std::max<double>(fRec0[1], fTemp6);
		fRec0[0] = ((iTemp1) ? fElse1 : fTemp6);
		int iElse2 = iRec1[1] + 1;
		iRec1[0] = ((iTemp1) ? iElse2 : 1);
		fRec2[0] = ((iTemp1) ? fRec2[1] : fRec0[1]);
		fVbargraph0 = FAUSTFLOAT(fRec2[0]);
		double fTemp7 = fTemp5;
		output0[i0] = FAUSTFLOAT(fTemp0 * fTemp7);
		output1[i0] = FAUSTFLOAT(fTemp2 * fTemp7);
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec0[1] = fRec0[0];
		iRec1[1] = iRec1[0];
		fRec2[1] = fRec2[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("hardlim.v1","","SON",N_("Rack output Limiter"),&fVbargraph0, 0, 0.0, 1.0, 0, 0);
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

} // end namespace hardlim
