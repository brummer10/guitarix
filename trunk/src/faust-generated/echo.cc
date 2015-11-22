// generated from file '../src/faust/echo.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace echo {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iConst0;
	float 	fConst1;
	float 	fConst2;
	FAUSTFLOAT 	fslider0;
	int 	iConst3;
	float 	fRec1[2];
	float 	fRec2[2];
	int 	iRec3[2];
	int 	iRec4[2];
	FAUSTFLOAT 	fslider1;
	float 	fRec5[2];
	int 	IOTA;
	float *fRec0;
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
	  fRec0(0),
	  mem_allocated(false) {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "echo";
	name = N_("Echo");
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
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) iRec3[i] = 0;
	for (int i=0; i<2; i++) iRec4[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<1048576; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1e+01f / float(iConst0));
	fConst2 = (0 - fConst1);
	iConst3 = (60 * iConst0);
	IOTA = 0;
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fRec0) fRec0 = new float[1048576];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fRec0) { delete fRec0; fRec0 = 0; }
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
	int 	iSlow0 = (int((float(iConst3) / float(fslider0))) - 1);
	float 	fSlow1 = (1.000000000000001e-05f * float(fslider1));
	for (int i=0; i<count; i++) {
		float fTemp0 = ((int((fRec1[1] != 0.0f)))?((int(((fRec2[1] > 0.0f) & (fRec2[1] < 1.0f))))?fRec1[1]:0):((int(((fRec2[1] == 0.0f) & (iSlow0 != iRec3[1]))))?fConst1:((int(((fRec2[1] == 1.0f) & (iSlow0 != iRec4[1]))))?fConst2:0)));
		fRec1[0] = fTemp0;
		fRec2[0] = max(0.0f, min(1.0f, (fRec2[1] + fTemp0)));
		iRec3[0] = ((int(((fRec2[1] >= 1.0f) & (iRec4[1] != iSlow0))))?iSlow0:iRec3[1]);
		iRec4[0] = ((int(((fRec2[1] <= 0.0f) & (iRec3[1] != iSlow0))))?iSlow0:iRec4[1]);
		fRec5[0] = ((0.999f * fRec5[1]) + fSlow1);
		fRec0[IOTA&1048575] = ((float)input0[i] + (fRec5[0] * (((1.0f - fRec2[0]) * fRec0[(IOTA-int((1 + int((int(iRec3[0]) & 524287)))))&1048575]) + (fRec2[0] * fRec0[(IOTA-int((1 + int((int(iRec4[0]) & 524287)))))&1048575]))));
		output0[i] = (FAUSTFLOAT)fRec0[(IOTA-0)&1048575];
		// post processing
		IOTA = IOTA+1;
		fRec5[1] = fRec5[0];
		iRec4[1] = iRec4[0];
		iRec3[1] = iRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
	}

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("echo.bpm",N_("time (bpm)"),"S",N_("Echo in Beats per Minute"),&fslider0, 1.2e+02f, 24.0f, 3.6e+02f, 1.0f);
	reg.registerVar("echo.percent","","S","",&fslider1, 0.0f, 0.0f, 1e+02f, 0.1f);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("echo" "." p)
// ----- echo
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("percent"), "%");
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalTableBox("");
    {
	b.create_small_rackknobr(PARAM("bpm"), _("  time (bpm) "));
	b.create_small_rackknob(PARAM("percent"), "    %    ");
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

} // end namespace echo
