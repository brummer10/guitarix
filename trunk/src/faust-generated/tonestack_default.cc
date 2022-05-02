// generated from file '../src/faust/tonestack_default.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace tonestack_default {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst2;
	double fConst3;
	double fConst5;
	double fConst6;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fVec0[3];
	double fRec3[3];
	double fRec2[3];
	double fRec1[3];
	double fRec0[3];

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
	id = "default";
	name = N_("default");
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
	for (int l0 = 0; l0 < 3; l0 = l0 + 1) fVec0[l0] = 0.0;
	for (int l1 = 0; l1 < 3; l1 = l1 + 1) fRec3[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRec2[l2] = 0.0;
	for (int l3 = 0; l3 < 3; l3 = l3 + 1) fRec1[l3] = 0.0;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRec0[l4] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 15079.644737231007 / fConst0;
	fConst2 = 1.4142135623730951 * std::sin(fConst1);
	fConst3 = std::cos(fConst1);
	double fConst4 = 3769.9111843077517 / fConst0;
	fConst5 = 1.4142135623730951 * std::sin(fConst4);
	fConst6 = std::cos(fConst4);
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
	double fSlow0 = double(fVslider1) + -0.5;
	double fSlow1 = 10.0 * fSlow0;
	double fSlow2 = std::pow(10.0, 0.025000000000000001 * (20.0 * (double(fVslider0) + -0.5) - fSlow1));
	double fSlow3 = fConst2 * std::sqrt(fSlow2);
	double fSlow4 = fConst3 * (fSlow2 + -1.0);
	double fSlow5 = 1.0 / (fSlow2 + fSlow3 + 1.0 - fSlow4);
	double fSlow6 = fSlow2 + 1.0 - (fSlow4 + fSlow3);
	double fSlow7 = fConst3 * (fSlow2 + 1.0);
	double fSlow8 = 2.0 * (fSlow2 + -1.0 - fSlow7);
	double fSlow9 = fSlow2 + fSlow4;
	double fSlow10 = fSlow2 * (fSlow3 + fSlow9 + 1.0);
	double fSlow11 = std::pow(10.0, 0.25 * fSlow0);
	double fSlow12 = std::sqrt(fSlow11);
	double fSlow13 = fConst5 * fSlow12;
	double fSlow14 = fSlow11 + -1.0;
	double fSlow15 = fConst6 * fSlow14;
	double fSlow16 = 1.0 / (fSlow11 + fSlow13 + 1.0 - fSlow15);
	double fSlow17 = fSlow11 + 1.0 - (fSlow13 + fSlow15);
	double fSlow18 = fSlow11 + 1.0;
	double fSlow19 = fConst6 * fSlow18;
	double fSlow20 = 2.0 * (fSlow11 + -1.0 - fSlow19);
	double fSlow21 = fSlow11 + fSlow15;
	double fSlow22 = fSlow11 * (fSlow13 + fSlow21 + 1.0);
	double fSlow23 = fConst2 * fSlow12;
	double fSlow24 = fConst3 * fSlow14;
	double fSlow25 = fSlow11 + fSlow24;
	double fSlow26 = 1.0 / (fSlow23 + fSlow25 + 1.0);
	double fSlow27 = fConst3 * fSlow18;
	double fSlow28 = 0.0 - 2.0 * (fSlow11 + fSlow27 + -1.0);
	double fSlow29 = fSlow25 + 1.0 - fSlow23;
	double fSlow30 = fSlow11 + fSlow23 + 1.0 - fSlow24;
	double fSlow31 = std::pow(10.0, 0.025000000000000001 * (20.0 * (std::exp(3.3999999999999999 * (double(fVslider2) + -1.0)) + -0.5) - fSlow1));
	double fSlow32 = fConst6 * (fSlow31 + -1.0);
	double fSlow33 = fSlow31 + fSlow32;
	double fSlow34 = fConst5 * std::sqrt(fSlow31);
	double fSlow35 = 1.0 / (fSlow33 + fSlow34 + 1.0);
	double fSlow36 = fConst6 * (fSlow31 + 1.0);
	double fSlow37 = 0.0 - 2.0 * (fSlow31 + fSlow36 + -1.0);
	double fSlow38 = fSlow33 + 1.0 - fSlow34;
	double fSlow39 = fSlow31 + fSlow34 + 1.0 - fSlow32;
	double fSlow40 = 2.0 * (fSlow31 + -1.0 - fSlow36);
	double fSlow41 = fSlow31 + 1.0 - (fSlow32 + fSlow34);
	double fSlow42 = 2.0 * (fSlow11 + -1.0 - fSlow27);
	double fSlow43 = fSlow11 + 1.0 - (fSlow23 + fSlow24);
	double fSlow44 = (0.0 - 2.0 * fSlow11) * (fSlow11 + fSlow19 + -1.0);
	double fSlow45 = fSlow11 * (fSlow21 + 1.0 - fSlow13);
	double fSlow46 = (0.0 - 2.0 * fSlow2) * (fSlow2 + fSlow7 + -1.0);
	double fSlow47 = fSlow2 * (fSlow9 + 1.0 - fSlow3);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		fVec0[0] = fTemp0;
		fRec3[0] = 0.0 - fSlow35 * ((fSlow37 * fRec3[1] + fSlow38 * fRec3[2]) - fSlow31 * (fSlow39 * fTemp0 + fSlow40 * fVec0[1] + fSlow41 * fVec0[2]));
		fRec2[0] = 0.0 - fSlow26 * ((fSlow28 * fRec2[1] + fSlow29 * fRec2[2]) - fSlow11 * (fSlow30 * fRec3[0] + fSlow42 * fRec3[1] + fSlow43 * fRec3[2]));
		fRec1[0] = fSlow16 * (0.0 - (fSlow17 * fRec1[2] + fSlow20 * fRec1[1]) + fSlow22 * fRec2[0] + fSlow44 * fRec2[1] + fSlow45 * fRec2[2]);
		fRec0[0] = fSlow5 * (0.0 - (fSlow6 * fRec0[2] + fSlow8 * fRec0[1]) + fSlow10 * fRec1[0] + fSlow46 * fRec1[1] + fSlow47 * fRec1[2]);
		output0[i0] = FAUSTFLOAT(fRec0[0]);
		fVec0[2] = fVec0[1];
		fVec0[1] = fVec0[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
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
	fVslider2_ = reg.registerFloatVar("amp.tonestack.Bass","","SA","",&fVslider2, 0.5, 0.0, 1.0, 0.01, 0);
	fVslider1_ = reg.registerFloatVar("amp.tonestack.Middle","","SA","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
	fVslider0_ = reg.registerFloatVar("amp.tonestack.Treble","","SA","",&fVslider0, 0.5, 0.0, 1.0, 0.01, 0);
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

} // end namespace tonestack_default
