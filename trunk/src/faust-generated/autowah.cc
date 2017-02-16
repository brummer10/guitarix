// generated from file '../src/faust/autowah.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace autowah {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	int 	iConst0;
	float 	fConst1;
	float 	fConst2;
	float 	fRec3[2];
	float 	fConst3;
	float 	fConst4;
	float 	fRec2[2];
	float 	fRec1[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	float 	fConst5;
	float 	fRec4[2];
	float 	fConst6;
	float 	fRec5[2];
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
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = expf((0 - (1e+01f / float(iConst0))));
	fConst2 = (1.0f - fConst1);
	fConst3 = expf((0 - (1e+02f / float(iConst0))));
	fConst4 = (1.0f - fConst3);
	fConst5 = (1413.7166941154069f / float(iConst0));
	fConst6 = (2827.4333882308138f / float(iConst0));
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
	float 	fSlow1 = float(fslider1);
	float 	fSlow2 = ((1.0f - fSlow1) + (1 - (0.01f * fSlow0)));
	float 	fSlow3 = (0.01f * (fSlow0 * float(fslider2)));
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		float fTemp1 = fabsf(fTemp0);
		fRec3[0] = max(fTemp1, ((fConst1 * fRec3[1]) + (fConst2 * fTemp1)));
		fRec2[0] = ((fConst3 * fRec2[1]) + (fConst4 * fRec3[0]));
		float fTemp2 = min((float)1, fRec2[0]);
		fRec1[0] = ((0.999f * fRec1[1]) + (0.0001000000000000001f * powf(4.0f,fTemp2)));
		float fTemp3 = powf(2.0f,(2.3f * fTemp2));
		float fTemp4 = (1 - (fConst5 * (fTemp3 / powf(2.0f,(1.0f + (2.0f * (1.0f - fTemp2)))))));
		fRec4[0] = ((0.999f * fRec4[1]) + (0.0010000000000000009f * faustpower<2>(fTemp4)));
		fRec5[0] = ((0.999f * fRec5[1]) + (0.0010000000000000009f * (0 - (2.0f * (fTemp4 * cosf((fConst6 * fTemp3)))))));
		fRec0[0] = (0 - (((fRec5[0] * fRec0[1]) + (fRec4[0] * fRec0[2])) - (fSlow3 * (fTemp0 * fRec1[0]))));
		output0[i] = (FAUSTFLOAT)((fSlow1 * (fRec0[0] - fRec0[1])) + (fSlow2 * fTemp0));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
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
	fslider2_ = reg.registerVar("crybaby.level","","SA","",&fslider2, 0.1f, 0.0f, 1.0f, 0.01f);
	fslider1_ = reg.registerVar("crybaby.wah","","SA","",&fslider1, 0.0f, 0.0f, 1.0f, 0.01f);
	fslider0_ = reg.registerVar("crybaby.wet_dry",N_("dry/wet"),"SA","",&fslider0, 1e+02f, 0.0f, 1e+02f, 1.0f);
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
