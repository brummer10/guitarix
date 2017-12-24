// generated from file '../src/faust/crybaby.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace crybaby {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	float 	fConst0;
	float 	fConst1;
	float 	fRec1[2];
	float 	fConst2;
	float 	fRec2[2];
	float 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	float 	fRec0[3];

	void clear_state_f();
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static void init_static(unsigned int samplingFreq, PluginDef*);
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
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05f, max(1.0f, (float)fSamplingFreq));
	fConst1 = (1413.7167f / fConst0);
	fConst2 = (2827.4333f / fConst0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	float 	fSlow0 = float(fslider0);
	float 	fSlow1 = powf(2.0f,(2.3f * fSlow0));
	float 	fSlow2 = (1 - (fConst1 * (fSlow1 / powf(2.0f,(1.0f + (2.0f * (1.0f - fSlow0)))))));
	float 	fSlow3 = (0.001f * faustpower<2>(fSlow2));
	float 	fSlow4 = (0.001f * (0 - (2.0f * (fSlow2 * cosf((fConst2 * fSlow1))))));
	float 	fSlow5 = (0.0001f * powf(4.0f,fSlow0));
	float 	fSlow6 = float(fslider2);
	float 	fSlow7 = (0.01f * (fSlow6 * float(fslider1)));
	float 	fSlow8 = (1 - (0.01f * fSlow6));
	for (int i=0; i<count; i++) {
		fRec1[0] = (fSlow3 + (0.999f * fRec1[1]));
		fRec2[0] = (fSlow4 + (0.999f * fRec2[1]));
		fRec3[0] = (fSlow5 + (0.999f * fRec3[1]));
		float fTemp0 = (float)input0[i];
		fRec0[0] = ((fSlow7 * (fTemp0 * fRec3[0])) - (0.996f * ((fRec0[1] * fRec2[0]) + (fRec0[2] * fRec1[0]))));
		output0[i] = (FAUSTFLOAT)(((fSlow8 * fTemp0) + fRec0[0]) - (0.996f * fRec0[1]));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	fslider1_ = reg.registerVar("crybaby.level","","SA","",&fslider1, 0.1f, 0.0f, 1.0f, 0.01f);
	fslider0_ = reg.registerVar("crybaby.wah","","SA","",&fslider0, 0.0f, 0.0f, 1.0f, 0.01f);
	fslider2_ = reg.registerVar("crybaby.wet_dry",N_("dry/wet"),"SA","",&fslider2, 1e+02f, 0.0f, 1e+02f, 1.0f);
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
