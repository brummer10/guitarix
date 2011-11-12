// generated from file '../src/faust/moog.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)


namespace moog {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	double 	fRec1[2];
	double 	fConst0;
	FAUSTFLOAT 	fslider1;
	double 	fRec6[2];
	double 	fRec5[2];
	double 	fRec4[2];
	double 	fRec3[2];
	double 	fRec2[2];
	double 	fRec0[2];
	double 	fRec11[2];
	double 	fRec10[2];
	double 	fRec9[2];
	double 	fRec8[2];
	double 	fRec7[2];
	void clear_state_f();
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *input1, float *output0, float *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, float *input0, float *input1, float *output0, float *output1, PluginDef*);
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
	id = "moog";
	name = N_("Moog Filter");
	groups = 0;
	mono_audio = 0;
	stereo_audio = compute_static;
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (6.283185307179586 / min(192000, max(1, fSamplingFreq)));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

inline void Dsp::compute(int count, float *input0, float *input1, float *output0, float *output1)
{
	double 	fSlow0 = (0.0010000000000000009 * fslider0);
	double 	fSlow1 = (0 - fslider1);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec1[0] = (fSlow0 + (0.999 * fRec1[1]));
		double fTemp0 = (fConst0 * fRec1[0]);
		double fTemp1 = faustpower<4>(fTemp0);
		double fTemp2 = (1.0 - fTemp0);
		fRec6[0] = ((1e-20 * (1 - iVec0[1])) - fRec6[1]);
		fRec5[0] = ((((double)input0[i] + fRec6[0]) + (fSlow1 * fRec0[1])) + (fTemp2 * fRec5[1]));
		fRec4[0] = (fRec5[0] + (fTemp2 * fRec4[1]));
		fRec3[0] = (fRec4[0] + (fTemp2 * fRec3[1]));
		fRec2[0] = (fRec3[0] + (fTemp2 * fRec2[1]));
		fRec0[0] = (fRec2[0] * fTemp1);
		output0[i] = (FAUSTFLOAT)fRec0[0];
		fRec11[0] = ((((double)input1[i] + fRec6[0]) + (fSlow1 * fRec7[1])) + (fTemp2 * fRec11[1]));
		fRec10[0] = (fRec11[0] + (fTemp2 * fRec10[1]));
		fRec9[0] = (fRec10[0] + (fTemp2 * fRec9[1]));
		fRec8[0] = (fRec9[0] + (fTemp2 * fRec8[1]));
		fRec7[0] = (fRec8[0] * fTemp1);
		output1[i] = (FAUSTFLOAT)fRec7[0];
		// post processing
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec1[1] = fRec1[0];
		iVec0[1] = iVec0[0];
	}
}

void Dsp::compute_static(int count, float *input0, float *input1, float *output0, float *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("moog.Q","","S","",&fslider1, 1.0, 0.0, 4.0, 0.1);
	reg.registerVar("moog.fr","","S","",&fslider0, 3e+03, 4.4e+02, 6e+03, 1e+01);
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

} // end namespace moog
