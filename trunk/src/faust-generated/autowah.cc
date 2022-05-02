// generated from file '../src/faust/autowah.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace autowah {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fRec3[2];
	float fRec2[2];
	float fRec1[2];
	float fConst5;
	float fConst6;
	float fRec4[2];
	float fRec5[2];
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
	id = "auto";
	name = N_("auto");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec3[l0] = 0.0f;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec2[l1] = 0.0f;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec1[l2] = 0.0f;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec4[l3] = 0.0f;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec5[l4] = 0.0f;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec0[l5] = 0.0f;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	float fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
	fConst1 = std::exp(0.0f - 100.0f / fConst0);
	fConst2 = 1.0f - fConst1;
	fConst3 = std::exp(0.0f - 10.0f / fConst0);
	fConst4 = 1.0f - fConst3;
	fConst5 = 1413.71667f / fConst0;
	fConst6 = 2827.43335f / fConst0;
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
	float fSlow1 = float(fVslider1);
	float fSlow2 = 0.00999999978f * fSlow1 * float(fVslider2);
	float fSlow3 = 1.0f - fSlow0 + 1.0f - 0.00999999978f * fSlow1;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		float fTemp0 = float(input0[i0]);
		float fTemp1 = std::fabs(fTemp0);
		fRec3[0] = std::max<float>(fTemp1, fConst3 * fRec3[1] + fConst4 * fTemp1);
		fRec2[0] = fConst2 * fRec3[0] + fConst1 * fRec2[1];
		float fTemp2 = std::min<float>(1.0f, fRec2[0]);
		fRec1[0] = 9.99999975e-05f * std::pow(4.0f, fTemp2) + 0.999000013f * fRec1[1];
		float fTemp3 = std::pow(2.0f, 2.29999995f * fTemp2);
		float fTemp4 = 1.0f - fConst5 * fTemp3 / std::pow(2.0f, 2.0f * (1.0f - fTemp2) + 1.0f);
		fRec4[0] = 0.999000013f * fRec4[1] - 0.00200000009f * fTemp4 * std::cos(fConst6 * fTemp3);
		fRec5[0] = 0.00100000005f * mydsp_faustpower2_f(fTemp4) + 0.999000013f * fRec5[1];
		fRec0[0] = fSlow2 * fTemp0 * fRec1[0] - (fRec4[0] * fRec0[1] + fRec5[0] * fRec0[2]);
		output0[i0] = FAUSTFLOAT(fSlow0 * (fRec0[0] - fRec0[1]) + fSlow3 * fTemp0);
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
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
	fVslider2_ = reg.registerFloatVar("crybaby.level","","SA","",&fVslider2, 0.100000001f, 0.0f, 1.0f, 0.00999999978f, 0);
	fVslider0_ = reg.registerFloatVar("crybaby.wah","","SA","",&fVslider0, 0.0f, 0.0f, 1.0f, 0.00999999978f, 0);
	fVslider1_ = reg.registerFloatVar("crybaby.wet_dry",N_("dry/wet"),"SA","",&fVslider1, 100.0f, 0.0f, 100.0f, 1.0f, 0);
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

} // end namespace autowah
