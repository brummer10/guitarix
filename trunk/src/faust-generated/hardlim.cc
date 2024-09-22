// generated from file '../src/faust/hardlim.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace hardlim {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	double fConst0;
	double fRec0[2];
	int iRec1[2];
	double fRec2[2];
	FAUSTFLOAT fVbargraph0;
	double fRec3[2];
	int iRec4[2];
	double fRec5[2];
	FAUSTFLOAT fVbargraph1;

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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) iRec1[l1] = 0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec2[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec3[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) iRec4[l4] = 0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec5[l5] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = 1.0 / std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		int iTemp0 = iRec1[1] < 1024;
		double fTemp1 = double(input0[i0]);
		double fTemp2 = std::fabs(fTemp1);
		int iTemp3 = fTemp2 <= 0.8912509381337456;
		double fTemp4 = fTemp2 + -0.8912509381337456;
		double fTemp5 = double((fTemp1 > 0.0) - (fTemp1 < 0.0));
		double fTemp6 = std::max<double>(fConst0, std::fabs(9.19548162383097 * std::max<double>(std::fabs(((iTemp3) ? fTemp1 : fTemp5 * (1.0 - 0.10874906186625444 * std::exp(-(9.19548162383097 * fTemp4))))) + -0.8912509381337456, 0.0)));
		fRec0[0] = ((iTemp0) ? std::max<double>(fRec0[1], fTemp6) : fTemp6);
		iRec1[0] = ((iTemp0) ? iRec1[1] + 1 : 1);
		fRec2[0] = ((iTemp0) ? fRec2[1] : fRec0[1]);
		fVbargraph0 = FAUSTFLOAT(fRec2[0]);
		output0[i0] = FAUSTFLOAT(((iTemp3) ? fTemp1 : fTemp5 * (1.0 - 0.10874906186625444 * std::exp(-9.19548162383097 * fTemp4))));
		int iTemp7 = iRec4[1] < 1024;
		double fTemp8 = double(input1[i0]);
		double fTemp9 = std::fabs(fTemp8);
		int iTemp10 = fTemp9 <= 0.8912509381337456;
		double fTemp11 = fTemp9 + -0.8912509381337456;
		double fTemp12 = double((fTemp8 > 0.0) - (fTemp8 < 0.0));
		double fTemp13 = std::max<double>(fConst0, std::fabs(9.19548162383097 * std::max<double>(std::fabs(((iTemp10) ? fTemp8 : fTemp12 * (1.0 - 0.10874906186625444 * std::exp(-(9.19548162383097 * fTemp11))))) + -0.8912509381337456, 0.0)));
		fRec3[0] = ((iTemp7) ? std::max<double>(fRec3[1], fTemp13) : fTemp13);
		iRec4[0] = ((iTemp7) ? iRec4[1] + 1 : 1);
		fRec5[0] = ((iTemp7) ? fRec5[1] : fRec3[1]);
		fVbargraph1 = FAUSTFLOAT(fRec5[0]);
		output1[i0] = FAUSTFLOAT(((iTemp10) ? fTemp8 : fTemp12 * (1.0 - 0.10874906186625444 * std::exp(-9.19548162383097 * fTemp11))));
		fRec0[1] = fRec0[0];
		iRec1[1] = iRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		iRec4[1] = iRec4[0];
		fRec5[1] = fRec5[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("hardlim.v1","","SON",N_("Rack output limiter left"),&fVbargraph0, 0, 0.0, 1.0, 0, 0);
	reg.registerFloatVar("hardlim.v2","","SON",N_("Rack output limiter right"),&fVbargraph1, 0, 0.0, 1.0, 0, 0);
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
