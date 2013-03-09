// generated from file '../src/faust/autowah.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)


namespace autowah {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	IOTA;
	int 	iVec0[1024];
	int 	iRec2[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec1[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fRec3[2];
	double 	fRec4[2];
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
	for (int i=0; i<1024; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) iRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (2827.4333882308138 / iConst0);
	fConst2 = (1413.7166941154069 / iConst0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

inline void Dsp::compute(int count, float *input0, float *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	double 	fSlow0 = (2.384185791015625e-10 * fslider0);
	double 	fSlow1 = fslider2;
	double 	fSlow2 = (0.01 * (fSlow1 * fslider1));
	double 	fSlow3 = (1 - (0.01 * fSlow1));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		int iTemp1 = abs(int((4194304 * fTemp0)));
		iVec0[IOTA&1023] = iTemp1;
		iRec2[0] = ((iVec0[IOTA&1023] + iRec2[1]) - iVec0[(IOTA-1000)&1023]);
		double fTemp2 = min(1, max(0, (fSlow0 * double(iRec2[0]))));
		fRec1[0] = ((0.0001000000000000001 * pow(4.0,fTemp2)) + (0.999 * fRec1[1]));
		double fTemp3 = pow(2.0,(2.3 * fTemp2));
		double fTemp4 = (1 - (fConst2 * (fTemp3 / pow(2.0,(1.0 + (2.0 * (1.0 - fTemp2)))))));
		fRec3[0] = ((0.0010000000000000009 * (0 - (2.0 * (fTemp4 * cos((fConst1 * fTemp3)))))) + (0.999 * fRec3[1]));
		fRec4[0] = ((0.0010000000000000009 * faustpower<2>(fTemp4)) + (0.999 * fRec4[1]));
		fRec0[0] = (0 - (((fRec4[0] * fRec0[2]) + (fRec3[0] * fRec0[1])) - (fSlow2 * (fTemp0 * fRec1[0]))));
		output0[i] = (FAUSTFLOAT)((fRec0[0] + (fSlow3 * fTemp0)) - fRec0[1]);
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec1[1] = fRec1[0];
		iRec2[1] = iRec2[0];
		IOTA = IOTA+1;
	}
#undef fslider0
#undef fslider1
#undef fslider2
}

void Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
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

} // end namespace autowah
