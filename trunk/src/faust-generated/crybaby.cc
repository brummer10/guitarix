// generated from file '../src/faust/crybaby.dsp' by dsp2cc:
// Code generated with Faust 2.20.2 (https://faust.grame.fr)


namespace crybaby {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	float fRec1[2];
	float fConst0;
	float fConst1;
	float fConst2;
	float fRec2[2];
	float fRec3[2];
	float fRec0[3];

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
	id = "manual";
	name = N_("manual");
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec1[l0] = 0.0f;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec2[l1] = 0.0f;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec3[l2] = 0.0f;
	for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) fRec0[l3] = 0.0f;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
	fConst1 = (2827.43335f / fConst0);
	fConst2 = (1413.71667f / fConst0);
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
	float fSlow0 = float(fVslider0);
	float fSlow1 = (0.00999999978f * (fSlow0 * float(fVslider1)));
	float fSlow2 = float(fVslider2);
	float fSlow3 = (9.99999975e-05f * std::pow(4.0f, fSlow2));
	float fSlow4 = std::pow(2.0f, (2.29999995f * fSlow2));
	float fSlow5 = (1.0f - (fConst2 * (fSlow4 / std::pow(2.0f, ((2.0f * (1.0f - fSlow2)) + 1.0f)))));
	float fSlow6 = (0.00200000009f * (std::cos((fConst1 * fSlow4)) * fSlow5));
	float fSlow7 = (0.00100000005f * mydsp_faustpower2_f(fSlow5));
	float fSlow8 = (1.0f - (0.00999999978f * fSlow0));
	for (int i = 0; (i < count); i = (i + 1)) {
		float fTemp0 = float(input0[i]);
		fRec1[0] = (fSlow3 + (0.999000013f * fRec1[1]));
		fRec2[0] = ((0.999000013f * fRec2[1]) - fSlow6);
		fRec3[0] = (fSlow7 + (0.999000013f * fRec3[1]));
		fRec0[0] = ((fSlow1 * (fTemp0 * fRec1[0])) - (0.995999992f * ((fRec2[0] * fRec0[1]) + (fRec3[0] * fRec0[2]))));
		output0[i] = FAUSTFLOAT(((fRec0[0] + (fSlow8 * fTemp0)) - (0.995999992f * fRec0[1])));
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
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
	fVslider1_ = reg.registerFloatVar("crybaby.level","","SA","",&fVslider1, 0.100000001f, 0.0f, 1.0f, 0.00999999978f, 0);
	fVslider2_ = reg.registerFloatVar("crybaby.wah","","SA","",&fVslider2, 0.0f, 0.0f, 1.0f, 0.00999999978f, 0);
	fVslider0_ = reg.registerFloatVar("crybaby.wet_dry",N_("dry/wet"),"SA","",&fVslider0, 100.0f, 0.0f, 100.0f, 1.0f, 0);
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

} // end namespace crybaby
