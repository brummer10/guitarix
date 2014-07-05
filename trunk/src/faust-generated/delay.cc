// generated from file '../src/faust/delay.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace delay {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	IOTA;
	float *fVec0;
	int 	iConst0;
	float 	fConst1;
	float 	fConst2;
	FAUSTFLOAT 	fslider0;
	float 	fConst3;
	float 	fRec0[2];
	float 	fRec1[2];
	float 	fRec2[2];
	float 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	float 	fRec4[2];
	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void clear_state_f();
	int activate(bool start);
	int load_ui_f(const UiBuilder& b, int form);
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int activate_static(bool start, PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginDef(),
	  fVec0(0),
	  mem_allocated(false) {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "delay";
	name = N_("Delay");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Echo / Delay");       // category
	shortname = "";     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = activate_static;
	register_params = register_params_static;
	load_ui = load_ui_f_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<262144; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
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
	fConst1 = (1e+01f / float(iConst0));
	fConst2 = (0 - fConst1);
	fConst3 = (0.001f * iConst0);
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
	} else if (mem_allocated) {
		mem_free();
	}
	return 0;
}

int Dsp::activate_static(bool start, PluginDef *p)
{
	return static_cast<Dsp*>(p)->activate(start);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	float 	fSlow0 = (fConst3 * float(fslider0));
	float 	fSlow1 = (0.0010000000000000009f * powf(10,(0.05f * float(fslider1))));
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		fVec0[IOTA&262143] = fTemp0;
		float fTemp1 = ((int((fRec0[1] != 0.0f)))?((int(((fRec1[1] > 0.0f) & (fRec1[1] < 1.0f))))?fRec0[1]:0):((int(((fRec1[1] == 0.0f) & (fSlow0 != fRec2[1]))))?fConst1:((int(((fRec1[1] == 1.0f) & (fSlow0 != fRec3[1]))))?fConst2:0)));
		fRec0[0] = fTemp1;
		fRec1[0] = max(0.0f, min(1.0f, (fRec1[1] + fTemp1)));
		fRec2[0] = ((int(((fRec1[1] >= 1.0f) & (fRec3[1] != fSlow0))))?fSlow0:fRec2[1]);
		fRec3[0] = ((int(((fRec1[1] <= 0.0f) & (fRec2[1] != fSlow0))))?fSlow0:fRec3[1]);
		fRec4[0] = ((0.999f * fRec4[1]) + fSlow1);
		output0[i] = (FAUSTFLOAT)(fVec0[IOTA&262143] + (fRec4[0] * (((1.0f - fRec1[0]) * fVec0[(IOTA-int((int(fRec2[0]) & 262143)))&262143]) + (fRec1[0] * fVec0[(IOTA-int((int(fRec3[0]) & 262143)))&262143]))));
		// post processing
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("delay.delay","","S","",&fslider0, 0.0f, 0.0f, 5e+03f, 1e+01f);
	reg.registerVar("delay.gain","","S","",&fslider1, 0.0f, -2e+01f, 2e+01f, 0.1f);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("delay" "." p)
// -----delay
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("delay"), _(" delay "));
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalTableBox("");
    {
	b.create_small_rackknobr(PARAM("delay"), _(" delay "));
	b.create_small_rackknob(PARAM("gain"), _("  gain "));
    }
    b.closeBox();
}
b.closeBox();

#undef PARAM
        return 0;
    }
	return -1;
}

int Dsp::load_ui_f_static(const UiBuilder& b, int form)
{
	return static_cast<Dsp*>(b.plugin)->load_ui_f(b, form);
}
PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace delay
