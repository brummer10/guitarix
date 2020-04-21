// generated from file '../src/faust/tonestack_ibanez.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace tonestack_ibanez {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	double fConst0;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst1;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fConst2;
	double fRec0[4];

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
	id = "Ibanez";
	name = N_("Ibanez Style");
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
	for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) fRec0[l0] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = (2.0 * std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate))));
	fConst1 = mydsp_faustpower2_f(fConst0);
	fConst2 = (3.0 * fConst0);
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
	double fSlow0 = double(fVslider0);
	double fSlow1 = std::exp((3.3999999999999999 * (double(fVslider1) + -1.0)));
	double fSlow2 = ((0.00040000000000000002 * fSlow0) + (0.025067500000000003 * fSlow1));
	double fSlow3 = (fConst0 * (fSlow2 + 0.015070200000000001));
	double fSlow4 = (4.0108000000000004e-07 * fSlow0);
	double fSlow5 = (((fSlow0 * (((1.0027000000000001e-05 * fSlow1) + -3.5719200000000006e-06) - fSlow4)) + (0.00010263250000000001 * fSlow1)) + 5.0503000000000006e-06);
	double fSlow6 = ((9.4499999999999994e-10 * fSlow1) - (3.7800000000000001e-11 * fSlow0));
	double fSlow7 = (6.7500000000000001e-09 * fSlow1);
	double fSlow8 = (((fSlow0 * (fSlow6 + -2.3219999999999998e-10)) + fSlow7) + 2.7e-10);
	double fSlow9 = (fConst0 * fSlow8);
	double fSlow10 = (1.0 / (-1.0 - (fSlow3 + (fConst1 * (fSlow5 + fSlow9)))));
	double fSlow11 = double(fVslider2);
	double fSlow12 = (fConst0 * ((fSlow2 + (6.7500000000000001e-05 * fSlow11)) + 0.0010027));
	double fSlow13 = (((9.4499999999999995e-07 * fSlow11) + ((fSlow0 * (4.2808000000000006e-07 - fSlow4)) + (fSlow1 * ((1.0027000000000001e-05 * fSlow0) + 2.6324999999999998e-06)))) + 1.0530000000000001e-07);
	double fSlow14 = ((fSlow0 * (fSlow6 + 3.7800000000000001e-11)) + (fSlow11 * (fSlow7 - (2.7e-10 * (fSlow0 + -1.0)))));
	double fSlow15 = (fConst0 * fSlow14);
	double fSlow16 = (0.0 - (fSlow12 + (fConst1 * (fSlow13 + fSlow15))));
	double fSlow17 = (fConst2 * fSlow8);
	double fSlow18 = ((fConst1 * (fSlow5 + fSlow17)) + (-3.0 - fSlow3));
	double fSlow19 = ((fSlow3 + (fConst1 * (fSlow5 - fSlow17))) + -3.0);
	double fSlow20 = (fSlow3 + (-1.0 - (fConst1 * (fSlow5 - fSlow9))));
	double fSlow21 = (fConst2 * fSlow14);
	double fSlow22 = ((fConst1 * (fSlow13 + fSlow21)) - fSlow12);
	double fSlow23 = (fSlow12 + (fConst1 * (fSlow13 - fSlow21)));
	double fSlow24 = (fSlow12 - (fConst1 * (fSlow13 - fSlow15)));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec0[0] = (double(input0[i]) - (fSlow10 * (((fSlow18 * fRec0[1]) + (fSlow19 * fRec0[2])) + (fSlow20 * fRec0[3]))));
		output0[i] = FAUSTFLOAT((fSlow10 * ((((fSlow16 * fRec0[0]) + (fSlow22 * fRec0[1])) + (fSlow23 * fRec0[2])) + (fSlow24 * fRec0[3]))));
		for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
			fRec0[j0] = fRec0[(j0 - 1)];
		}
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	fVslider1_ = reg.registerFloatVar("amp.tonestack.Bass","","SA","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
	fVslider0_ = reg.registerFloatVar("amp.tonestack.Middle","","SA","",&fVslider0, 0.5, 0.0, 1.0, 0.01, 0);
	fVslider2_ = reg.registerFloatVar("amp.tonestack.Treble","","SA","",&fVslider2, 0.5, 0.0, 1.0, 0.01, 0);
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

} // end namespace tonestack_ibanez
