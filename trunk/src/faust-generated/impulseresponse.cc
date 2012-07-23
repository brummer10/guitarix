// generated from file '../src/faust/impulseresponse.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)


namespace impulseresponse {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider1;
	double 	fConst2;
	double 	fVec0[3];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT 	fslider2;
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
	id = "IR";
	name = N_("ImpulseResponse");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Tone control");       // category
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
	fConst1 = (3.141592653589793 / iConst0);
	fConst2 = (6.283185307179586 / iConst0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

inline void Dsp::compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = exp((0 - (fConst1 * fslider0)));
	double 	fSlow1 = (2 * cos((fConst2 * fslider1)));
	int 	iSlow2 = int(max(0, min(1, fcheckbox0)));
	double 	fSlow3 = (0.5 * (fslider2 * (1 - faustpower<2>(fSlow0))));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec0[0] = ((fSlow3 * (fVec0[0] - fVec0[2])) + (fSlow0 * ((fRec0[1] * ((iSlow2)?max(-0.6, min(0.6, fVec0[0])):fSlow1)) - (fSlow0 * fRec0[2]))));
		output0[i] = (FAUSTFLOAT)(fVec0[0] + fRec0[0]);
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fVec0[2] = fVec0[1]; fVec0[1] = fVec0[0];
	}
}

void Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("IR.peak","","S",N_("peak gain"),&fslider2, 1.0, 0.0, 1e+01, 0.2);
	static const value_pair fcheckbox0_values[] = {{"manual"},{"auto"},{0}};
	reg.registerEnumVar("IR.auto_freq",N_("auto freq"),"B","",fcheckbox0_values,&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("IR.freq","","S",N_("frequency (Hz)"),&fslider1, 4.4e+02, 2e+01, 1.2e+04, 1e+01);
	reg.registerVar("IR.bandwidth","","S",N_("bandwidth (Hz)"),&fslider0, 1e+02, 2e+01, 2e+04, 1e+01);
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

} // end namespace impulseresponse
