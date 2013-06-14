// generated from file '../src/faust/crybaby.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)


namespace crybaby {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fRec1[2];
	double 	fRec2[2];
	double 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec0[3];
	void clear_state_f();
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, float *input0, float *output0, PluginDef*);
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
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1413.7166941154069 / double(iConst0));
	fConst2 = (2827.4333882308138 / double(iConst0));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, float *input0, float *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	double 	fSlow0 = fslider0;
	double 	fSlow1 = pow(2.0,(2.3 * fSlow0));
	double 	fSlow2 = (1 - (fConst1 * (fSlow1 / pow(2.0,(1.0 + (2.0 * (1.0 - fSlow0)))))));
	double 	fSlow3 = (0.0010000000000000009 * (0 - (2.0 * (cos((fConst2 * fSlow1)) * fSlow2))));
	double 	fSlow4 = (0.0010000000000000009 * faustpower<2>(fSlow2));
	double 	fSlow5 = (0.0001000000000000001 * pow(4.0,fSlow0));
	double 	fSlow6 = fslider2;
	double 	fSlow7 = (0.01 * (fSlow6 * fslider1));
	double 	fSlow8 = (1 - (0.01 * fSlow6));
	for (int i=0; i<count; i++) {
		fRec1[0] = (fSlow3 + (0.999 * fRec1[1]));
		fRec2[0] = (fSlow4 + (0.999 * fRec2[1]));
		fRec3[0] = (fSlow5 + (0.999 * fRec3[1]));
		double fTemp0 = (double)input0[i];
		fRec0[0] = ((fSlow7 * (fTemp0 * fRec3[0])) - (0.996 * ((fRec2[0] * fRec0[2]) + (fRec1[0] * fRec0[1]))));
		output0[i] = (FAUSTFLOAT)((fRec0[0] + (fSlow8 * fTemp0)) - (0.996 * fRec0[1]));
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

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	fslider2_ = reg.registerVar("crybaby.wet_dry",N_("dry/wet"),"SA","",&fslider2, 1e+02, 0.0, 1e+02, 1.0);
	fslider1_ = reg.registerVar("crybaby.level","","SA","",&fslider1, 0.1, 0.0, 1.0, 0.01);
	fslider0_ = reg.registerVar("crybaby.wah","","SA","",&fslider0, 0.0, 0.0, 1.0, 0.01);
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
