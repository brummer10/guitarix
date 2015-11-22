// generated from file '../src/faust/flanger_mono.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace flanger_mono {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	int 	iVec0[2];
	int 	IOTA;
	double 	fVec1[2048];
	FAUSTFLOAT 	fslider2;
	int 	iConst0;
	double 	fConst1;
	double 	fRec1[2];
	double 	fRec2[2];
	double 	fRec0[2];
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
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
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "flanger_mono";
	name = N_("Flanger Mono");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Modulation");       // category
	shortname = "";     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	load_ui = load_ui_f_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2048; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
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
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (0.10471975511965977 / double(iConst0));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = double(fslider1);
	double 	fSlow1 = (0.01 * (fSlow0 * pow(10,(0.05 * double(fslider0)))));
	double 	fSlow2 = (fConst1 * double(fslider2));
	double 	fSlow3 = cos(fSlow2);
	double 	fSlow4 = sin(fSlow2);
	double 	fSlow5 = (0 - fSlow4);
	double 	fSlow6 = (1 - (0.01 * fSlow0));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		double fTemp1 = (fSlow1 * fTemp0);
		iVec0[0] = 1;
		double fTemp2 = ((0.5 * fRec0[1]) - fTemp1);
		fVec1[IOTA&2047] = fTemp2;
		fRec1[0] = ((fSlow4 * fRec2[1]) + (fSlow3 * fRec1[1]));
		fRec2[0] = ((1 + ((fSlow3 * fRec2[1]) + (fSlow5 * fRec1[1]))) - iVec0[1]);
		double fTemp3 = (iConst0 * (0.001 + (0.005 * (1 + fRec1[0]))));
		int iTemp4 = int(fTemp3);
		int iTemp5 = (1 + iTemp4);
		fRec0[0] = ((fVec1[(IOTA-int((iTemp4 & 2047)))&2047] * (iTemp5 - fTemp3)) + ((fTemp3 - iTemp4) * fVec1[(IOTA-int((int(iTemp5) & 2047)))&2047]));
		output0[i] = (FAUSTFLOAT)((fSlow6 * fTemp0) + (0.5 * (fTemp1 - fRec0[0])));
		// post processing
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		IOTA = IOTA+1;
		iVec0[1] = iVec0[0];
	}

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("flanger_mono.level","","S","",&fslider0, 0.0, -6e+01, 1e+01, 0.1);
	reg.registerVar("flanger_mono.lfobpm",N_("LFO freq (bpm)"),"S",N_("LFO in Beats per Minute"),&fslider2, 24.0, 24.0, 3.6e+02, 1.0);
	reg.registerVar("flanger_mono.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider1, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("flanger_mono" "." p)
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("level"), _("level"));
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalBox("");
    {
	b.create_small_rackknobr(PARAM("level"), _("level"));
	b.create_small_rackknob(PARAM("lfobpm"), _("LFO freq (bpm)"));
	b.create_small_rackknob(PARAM("wet_dry"), _("dry/wet"));
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

} // end namespace flanger_mono
