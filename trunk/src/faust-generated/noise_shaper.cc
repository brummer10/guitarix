// generated from file '../src/faust/noise_shaper.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

namespace noise_shaper {
class Dsp: public PluginDef {
private:
int 	iConst0;
double 	fConst1;
double 	fConst2;
double 	fRec0[2];
FAUSTFLOAT 	fslider0;
    int fSamplingFreq;
    void clear_state_f();
    static void clear_state_f_static(PluginDef*);
    void init(unsigned int samplingFreq);
    static void init_static(unsigned int samplingFreq, PluginDef*);
    void compute(int count, float *input0, float *output0);
    static void compute_static(int count, float *input0, float *output0, PluginDef*);
    int register_par(const ParamReg& reg);
    static int register_params_static(const ParamReg& reg);
    static void del_instance(PluginDef *p);
public:
    Dsp();
    ~Dsp();
};


Dsp::Dsp(): PluginDef() {
    version = PLUGINDEF_VERSION;
    flags = 0;
    id = "shaper";
    name = N_("Shaper");
    groups = 0;
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
    static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = exp((0 - (2e+02 / iConst0)));
	fConst2 = exp((0 - (0.1 / iConst0)));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
    static_cast<Dsp*>(p)->init(samplingFreq);
}


inline void Dsp::compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (5 * fSlow0);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		double fTemp1 = max(1, fabs(fTemp0));
		double fTemp2 = ((fConst2 * (fRec0[1] >= fTemp1)) + (fConst1 * (fRec0[1] < fTemp1)));
		fRec0[0] = ((fTemp1 * (0 - (fTemp2 - 1))) + (fRec0[1] * fTemp2));
		double fTemp3 = max(0, (fSlow1 + (20 * log10(fRec0[0]))));
		double fTemp4 = (0.5 * min(1, max(0, (0.09522902580706599 * fTemp3))));
		output0[i] = (FAUSTFLOAT)(fTemp0 * pow(10,(0.05 * (fSlow0 + ((fTemp3 * (0 - fTemp4)) / (1 + fTemp4))))));
		// post processing
		fRec0[1] = fRec0[0];
	}
}

void Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
    static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("shaper.sharper",N_("sharper"),"S","",&fslider0, 1.0, 1.0, 1e+01, 1.0);
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

} // end namespace noise_shaper
