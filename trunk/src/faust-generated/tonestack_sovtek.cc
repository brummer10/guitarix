// generated from file '../src/faust/tonestack_sovtek.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace tonestack_sovtek {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst0;
	double fConst1;
	double fConst2;
	double fRec0[4];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fConst3;

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
	id = "MIG 100 H";
	name = N_("MIG 100 H Style");
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
	for (int l0 = 0; l0 < 4; l0 = l0 + 1) fRec0[l0] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = 2.0 * std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	fConst2 = mydsp_faustpower3_f(fConst0);
	fConst3 = 3.0 * fConst2;
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
	double fSlow0 = std::exp(3.4 * (double(fVslider0) + -1.0));
	double fSlow1 = 2.8889960000000004e-05 * fSlow0;
	double fSlow2 = double(fVslider1);
	double fSlow3 = 4.9434000000000004e-08 * fSlow2;
	double fSlow4 = 4.943400000000001e-06 * fSlow0;
	double fSlow5 = fConst1 * (fSlow2 * (fSlow4 + -1.2634599999999999e-07 - fSlow3) + fSlow1 + 7.748796000000001e-07);
	double fSlow6 = 5.345780000000001e-09 * fSlow0;
	double fSlow7 = 1.2443156000000002e-11 * fSlow2;
	double fSlow8 = 1.2443156000000004e-09 * fSlow0;
	double fSlow9 = fConst2 * (fSlow2 * (fSlow8 - fSlow7 + -4.101464400000001e-11) + fSlow6 + 5.345780000000001e-11);
	double fSlow10 = 0.022470000000000004 * fSlow0;
	double fSlow11 = 0.00022 * fSlow2;
	double fSlow12 = fConst0 * (fSlow11 + fSlow10 + 0.0025277);
	double fSlow13 = fSlow12 + fSlow9 + (-1.0 - fSlow5);
	double fSlow14 = fSlow12 + fSlow5;
	double fSlow15 = fSlow14 - 3.0 * (fSlow9 + 1.0);
	double fSlow16 = fSlow5 - (fSlow12 + 3.0 * (1.0 - fSlow9));
	double fSlow17 = 1.0 / (-1.0 - (fSlow14 + fSlow9));
	double fSlow18 = 1.0 - fSlow2;
	double fSlow19 = double(fVslider2);
	double fSlow20 = fSlow19 * (fSlow6 + 5.345780000000001e-11 * fSlow18) + fSlow2 * (fSlow8 + 1.2443156000000002e-11 * fSlow18);
	double fSlow21 = fConst2 * fSlow20;
	double fSlow22 = fConst1 * (4.859800000000001e-07 * fSlow19 + fSlow2 * (1.0113400000000001e-07 - fSlow3) + fSlow0 * (4.943400000000001e-06 * fSlow2 + 6.141960000000001e-06) + 6.141960000000001e-08);
	double fSlow23 = fConst0 * (fSlow10 + fSlow11 + 0.00023500000000000002 * fSlow19 + 0.00022470000000000001);
	double fSlow24 = fSlow23 + fSlow22;
	double fSlow25 = fSlow24 + fSlow21;
	double fSlow26 = fSlow23 + fSlow21 - fSlow22;
	double fSlow27 = fConst3 * fSlow20;
	double fSlow28 = fSlow24 - fSlow27;
	double fSlow29 = fSlow22 + fSlow27 - fSlow23;
	double fSlow30 = 1.0 / (-1.0 - (fSlow12 + fConst1 * (fSlow1 + fSlow2 * (fSlow4 + (-1.2634599999999999e-07 - fSlow3)) + 7.748796000000001e-07) + fConst2 * (fSlow6 + fSlow2 * (fSlow8 + (-4.101464400000001e-11 - fSlow7)) + 5.345780000000001e-11)));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = double(input0[i0]) - fSlow17 * (fSlow16 * fRec0[1] + fSlow15 * fRec0[2] + fSlow13 * fRec0[3]);
		output0[i0] = FAUSTFLOAT(fSlow30 * (fSlow29 * fRec0[1] + fSlow28 * fRec0[2] + fSlow26 * fRec0[3] - fSlow25 * fRec0[0]));
		for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
			fRec0[j0] = fRec0[j0 - 1];
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
	fVslider0_ = reg.registerFloatVar("amp.tonestack.Bass","","SA","",&fVslider0, 0.5, 0.0, 1.0, 0.01, 0);
	fVslider1_ = reg.registerFloatVar("amp.tonestack.Middle","","SA","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
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

} // end namespace tonestack_sovtek
