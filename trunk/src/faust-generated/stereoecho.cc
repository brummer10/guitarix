// generated from file '../src/faust/stereoecho.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)


namespace stereoecho {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	float 	fConst0;
	FAUSTFLOAT 	fslider1;
	int 	IOTA;
	float *fRec0;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	float *fRec1;
	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void clear_state_f();
	int activate(bool start);
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *input1, float *output0, float *output1);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int activate_static(bool start, PluginDef*);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, float *input0, float *input1, float *output0, float *output1, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);

public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginDef(),
	  fRec0(0),
	  fRec1(0),
	  mem_allocated(false) {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "stereoecho";
	name = N_("Stereo Echo");
	groups = 0;
	description = ""; // description (tooltip)
	category = "";       // category
	shortname = "";     // shortname
	mono_audio = 0;
	stereo_audio = compute_static;
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
	for (int i=0; i<262144; i++) fRec0[i] = 0;
	for (int i=0; i<262144; i++) fRec1[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (0.001f * min(192000, max(1, fSamplingFreq)));
	IOTA = 0;
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fRec0) fRec0 = new float[262144];
	if (!fRec1) fRec1 = new float[262144];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fRec0) { delete fRec0; fRec0 = 0; }
	if (fRec1) { delete fRec1; fRec1 = 0; }
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

inline void Dsp::compute(int count, float *input0, float *input1, float *output0, float *output1)
{
	int 	iSlow0 = int((1 + int((int((int((fConst0 * fslider0)) - 1)) & 131071))));
	float 	fSlow1 = (0.01f * fslider1);
	int 	iSlow2 = int((1 + int((int((int((fConst0 * fslider2)) - 1)) & 131071))));
	float 	fSlow3 = (0.01f * fslider3);
	for (int i=0; i<count; i++) {
		fRec0[IOTA&262143] = ((float)input0[i] + (fSlow1 * fRec0[(IOTA-iSlow0)&262143]));
		output0[i] = (FAUSTFLOAT)fRec0[(IOTA-0)&262143];
		fRec1[IOTA&262143] = ((float)input1[i] + (fSlow3 * fRec1[(IOTA-iSlow2)&262143]));
		output1[i] = (FAUSTFLOAT)fRec1[(IOTA-0)&262143];
		// post processing
		IOTA = IOTA+1;
	}
}

void Dsp::compute_static(int count, float *input0, float *input1, float *output0, float *output1, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("stereoecho.percent_r","","S","",&fslider3, 0.0f, 0.0f, 1e+02f, 0.1f);
	reg.registerVar("stereoecho.time_r","","S","",&fslider2, 1.0f, 1.0f, 2e+03f, 1.0f);
	reg.registerVar("stereoecho.percent_l","","S","",&fslider1, 0.0f, 0.0f, 1e+02f, 0.1f);
	reg.registerVar("stereoecho.time_l","","S","",&fslider0, 1.0f, 1.0f, 2e+03f, 1.0f);
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

} // end namespace stereoecho
