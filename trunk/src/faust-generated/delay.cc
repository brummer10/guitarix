// generated from file '../src/faust/delay.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

namespace delay {
class Dsp: public PluginDef {
private:
    bool mem_allocated;
int 	IOTA;
float *fVec0;
FAUSTFLOAT 	fslider0;
float 	fConst0;
FAUSTFLOAT 	fslider1;
float 	fRec0[2];
    int fSamplingFreq;
    void clear_state_f();
    static void clear_state_f_static(PluginDef*);
    void init(unsigned int samplingFreq);
    static void init_static(unsigned int samplingFreq, PluginDef*);
    void mem_alloc();
    void mem_free();
    int activate(bool start);
    static int activate_static(bool start, PluginDef*);
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
    mem_allocated = false;
    version = PLUGINDEF_VERSION;
    flags = 0;
    id = "delay";
    name = N_("Delay");
    groups = 0;
    mono_audio = compute_static;
    stereo_audio = 0;
    set_samplerate = init_static;
    activate_plugin = activate_static;
    register_params = register_params_static;
    load_ui = 0;
    clear_state = clear_state_f_static;
    delete_instance = del_instance;
}

Dsp::~Dsp() {
}
inline void Dsp::clear_state_f()
{
	for (int i=0; i<262144; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
    static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	fConst0 = (0.001f * min(192000, max(1, fSamplingFreq)));
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
    static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fVec0) fVec0 = new float[262144];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec0) { delete fVec0; fVec0 = 0; }
}

int Dsp::activate(bool start)
{
    if (start) {
        if (!mem_allocated) {
            mem_alloc();
            clear_state_f();
        }
    } else if (!mem_allocated) {
        mem_free();
    }
    return 0;
}

int Dsp::activate_static(bool start, PluginDef *p)
{
    return static_cast<Dsp*>(p)->activate(start);
}

inline void Dsp::compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = (fConst0 * fslider0);
	int 	iSlow1 = int(fSlow0);
	int 	iSlow2 = int((iSlow1 & 262143));
	int 	iSlow3 = (1 + iSlow1);
	float 	fSlow4 = (iSlow3 - fSlow0);
	int 	iSlow5 = int((int(iSlow3) & 262143));
	float 	fSlow6 = (fSlow0 - iSlow1);
	float 	fSlow7 = (0.0010000000000000009f * powf(10,(0.05f * fslider1)));
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		fVec0[IOTA&262143] = fTemp0;
		fRec0[0] = (fSlow7 + (0.999f * fRec0[1]));
		output0[i] = (FAUSTFLOAT)(fVec0[IOTA&262143] + (fRec0[0] * ((fSlow6 * fVec0[(IOTA-iSlow5)&262143]) + (fSlow4 * fVec0[(IOTA-iSlow2)&262143]))));
		// post processing
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
	}
}

void Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
    static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("delay.gain","","S","",&fslider1, 0.0f, -2e+01f, 2e+01f, 0.1f);
	reg.registerVar("delay.delay","","S","",&fslider0, 0.0f, 0.0f, 5e+03f, 1e+01f);
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

} // end namespace delay
