// generated from file '../src/faust/tonestack_default.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace tonestack_default {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fVec0[3];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec3[3];
	double 	fRec2[3];
	double 	fRec1[3];
	double 	fRec0[3];

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
	for (int i=0; i<3; i++) fVec0[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = (15079.644737231007 / fConst0);
	fConst2 = cos(fConst1);
	fConst3 = (1.4142135623730951 * sin(fConst1));
	fConst4 = (3769.9111843077517 / fConst0);
	fConst5 = cos(fConst4);
	fConst6 = (1.4142135623730951 * sin(fConst4));
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
	double 	fSlow0 = (double(fslider0) - 0.5);
	double 	fSlow1 = (10 * fSlow0);
	double 	fSlow2 = pow(10,(0.025 * ((20 * (double(fslider1) - 0.5)) - fSlow1)));
	double 	fSlow3 = (1 + fSlow2);
	double 	fSlow4 = (fConst2 * fSlow3);
	double 	fSlow5 = (2 * (0 - ((1 + fSlow4) - fSlow2)));
	double 	fSlow6 = (fConst3 * sqrt(fSlow2));
	double 	fSlow7 = (fConst2 * (fSlow2 - 1));
	double 	fSlow8 = (fSlow3 - (fSlow7 + fSlow6));
	double 	fSlow9 = pow(10,(0.25 * fSlow0));
	double 	fSlow10 = (1 + fSlow9);
	double 	fSlow11 = (fConst5 * fSlow10);
	double 	fSlow12 = (2 * (0 - ((1 + fSlow11) - fSlow9)));
	double 	fSlow13 = sqrt(fSlow9);
	double 	fSlow14 = (fConst6 * fSlow13);
	double 	fSlow15 = (fSlow9 - 1);
	double 	fSlow16 = (fConst5 * fSlow15);
	double 	fSlow17 = (fSlow10 - (fSlow16 + fSlow14));
	double 	fSlow18 = pow(10,(0.025 * ((20 * (exp((3.4 * (double(fslider2) - 1))) - 0.5)) - fSlow1)));
	double 	fSlow19 = (fConst6 * sqrt(fSlow18));
	double 	fSlow20 = (fConst5 * (fSlow18 - 1));
	double 	fSlow21 = (1 + fSlow18);
	double 	fSlow22 = (fSlow21 - (fSlow20 + fSlow19));
	double 	fSlow23 = (fConst5 * fSlow21);
	double 	fSlow24 = (2 * (0 - ((1 + fSlow23) - fSlow18)));
	double 	fSlow25 = ((1 + (fSlow18 + fSlow19)) - fSlow20);
	double 	fSlow26 = (fSlow18 + fSlow20);
	double 	fSlow27 = ((1 + fSlow26) - fSlow19);
	double 	fSlow28 = (0 - (2 * ((fSlow18 + fSlow23) - 1)));
	double 	fSlow29 = (1.0 / (1 + (fSlow19 + fSlow26)));
	double 	fSlow30 = (fConst3 * fSlow13);
	double 	fSlow31 = (fConst2 * fSlow15);
	double 	fSlow32 = (fSlow10 - (fSlow31 + fSlow30));
	double 	fSlow33 = ((1 + (fSlow9 + fSlow30)) - fSlow31);
	double 	fSlow34 = (fConst2 * fSlow10);
	double 	fSlow35 = (2 * (0 - ((1 + fSlow34) - fSlow9)));
	double 	fSlow36 = (fSlow9 + fSlow31);
	double 	fSlow37 = ((1 + fSlow36) - fSlow30);
	double 	fSlow38 = (0 - (2 * ((fSlow9 + fSlow34) - 1)));
	double 	fSlow39 = (1.0 / (1 + (fSlow30 + fSlow36)));
	double 	fSlow40 = (fSlow9 + fSlow16);
	double 	fSlow41 = ((1 + fSlow40) - fSlow14);
	double 	fSlow42 = (1 + (fSlow40 + fSlow14));
	double 	fSlow43 = ((0 - (2 * fSlow9)) * ((fSlow9 + fSlow11) - 1));
	double 	fSlow44 = (1.0 / ((1 + (fSlow9 + fSlow14)) - fSlow16));
	double 	fSlow45 = (fSlow2 + fSlow7);
	double 	fSlow46 = ((1 + fSlow45) - fSlow6);
	double 	fSlow47 = (1 + (fSlow45 + fSlow6));
	double 	fSlow48 = ((0 - (2 * fSlow2)) * ((fSlow2 + fSlow4) - 1));
	double 	fSlow49 = (1.0 / ((1 + (fSlow2 + fSlow6)) - fSlow7));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec3[0] = (fSlow29 * (0 - (((fSlow28 * fRec3[1]) + (fSlow27 * fRec3[2])) - (fSlow18 * (((fSlow25 * fVec0[0]) + (fSlow24 * fVec0[1])) + (fSlow22 * fVec0[2]))))));
		fRec2[0] = (fSlow39 * (0 - (((fSlow38 * fRec2[1]) + (fSlow37 * fRec2[2])) - (fSlow9 * ((fSlow35 * fRec3[1]) + ((fSlow33 * fRec3[0]) + (fSlow32 * fRec3[2])))))));
		fRec1[0] = (fSlow44 * (((fSlow43 * fRec2[1]) + (fSlow9 * ((fSlow42 * fRec2[0]) + (fSlow41 * fRec2[2])))) - ((fSlow17 * fRec1[2]) + (fSlow12 * fRec1[1]))));
		fRec0[0] = (fSlow49 * (((fSlow48 * fRec1[1]) + (fSlow2 * ((fSlow47 * fRec1[0]) + (fSlow46 * fRec1[2])))) - ((fSlow8 * fRec0[2]) + (fSlow5 * fRec0[1]))));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fVec0[2] = fVec0[1]; fVec0[1] = fVec0[0];
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
	fslider2_ = reg.registerVar("amp.tonestack.Bass","","SA","",&fslider2, 0.5, 0.0, 1.0, 0.01);
	fslider0_ = reg.registerVar("amp.tonestack.Middle","","SA","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	fslider1_ = reg.registerVar("amp.tonestack.Treble","","SA","",&fslider1, 0.5, 0.0, 1.0, 0.01);
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
