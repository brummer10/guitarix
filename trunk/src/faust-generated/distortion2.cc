// generated from file '../src/faust/distortion2.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace distortion2 {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider1;
	double 	fRec2[2];
	FAUSTFLOAT 	fslider2;
	double 	fRec3[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	double 	fRec5[3];
	double 	fVec0[2];
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fRec4[2];
	double 	fRec1[4];
	double 	fRec0[3];
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
	id = "distortion2";
	name = N_("WaveSharper");
	groups = 0;
	description = N_("A simple Wavesharper distortion"); // description (tooltip)
	category = N_("Distortion");       // category
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
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<4; i++) fRec1[i] = 0;
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
	fConst1 = (3.141592653589793 / double(iConst0));
	fConst2 = (1.0 / tan((20520.88321324853 / double(iConst0))));
	fConst3 = (1 + fConst2);
	fConst4 = (1.0 / fConst3);
	fConst5 = (0 - ((1 - fConst2) / fConst3));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = tan((fConst1 * double(fslider0)));
	double 	fSlow1 = (2 * (1 - (1.0 / faustpower<2>(fSlow0))));
	double 	fSlow2 = (1.0 / fSlow0);
	double 	fSlow3 = (1 + ((fSlow2 - 1.414213562373095) / fSlow0));
	double 	fSlow4 = (1.0 / (1 + ((1.414213562373095 + fSlow2) / fSlow0)));
	double 	fSlow5 = (0.0010000000000000009 * double(fslider1));
	double 	fSlow6 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider2))));
	double 	fSlow7 = tan((fConst1 * double(fslider3)));
	double 	fSlow8 = (1.0 / faustpower<2>(fSlow7));
	double 	fSlow9 = (2 * (1 - fSlow8));
	double 	fSlow10 = (1.0 / fSlow7);
	double 	fSlow11 = (1 + ((fSlow10 - 1.414213562373095) / fSlow7));
	double 	fSlow12 = (1.0 / (1 + ((1.414213562373095 + fSlow10) / fSlow7)));
	double 	fSlow13 = (0.01 * double(fslider4));
	double 	fSlow14 = (2 * (0 - fSlow8));
	double 	fSlow15 = (1 - fSlow13);
	for (int i=0; i<count; i++) {
		fRec2[0] = ((0.999 * fRec2[1]) + fSlow5);
		double fTemp0 = sin((0.01539996398818526 * (1 + fRec2[0])));
		double fTemp1 = (1 - fTemp0);
		fRec3[0] = ((0.999 * fRec3[1]) + fSlow6);
		double fTemp2 = (double)input0[i];
		fRec5[0] = ((fSlow13 * fTemp2) - (fSlow12 * ((fSlow11 * fRec5[2]) + (fSlow9 * fRec5[1]))));
		double fTemp3 = (fSlow12 * (((fSlow8 * fRec5[0]) + (fSlow14 * fRec5[1])) + (fSlow8 * fRec5[2])));
		fVec0[0] = fTemp3;
		fRec4[0] = ((fConst5 * fRec4[1]) + (fConst4 * (fVec0[0] + fVec0[1])));
		double fTemp4 = (fRec4[0] * fRec3[0]);
		fRec1[0] = ((0.5 * fRec1[3]) + ((fTemp4 * (1 + (2 * (fTemp0 / fTemp1)))) / (1 + (2 * ((fabs(fTemp4) * fTemp0) / fTemp1)))));
		fRec0[0] = (fRec1[0] - (fSlow4 * ((fSlow3 * fRec0[2]) + (fSlow1 * fRec0[1]))));
		output0[i] = (FAUSTFLOAT)((fSlow15 * fTemp2) + (fSlow4 * (fRec0[2] + (fRec0[0] + (2 * fRec0[1])))));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		for (int i=3; i>0; i--) fRec1[i] = fRec1[i-1];
		fRec4[1] = fRec4[0];
		fVec0[1] = fVec0[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("distortion2.Hfreq",N_("HighPass (hz)"),"SL",N_("Highpass Frequency"),&fslider3, 3e+01, 2e+01, 2e+03, 1.08);
	reg.registerVar("distortion2.drive","","S",N_("Distortion Level"),&fslider1, 5e+01, 0.0, 1e+02, 1.0);
	reg.registerVar("distortion2.freq",N_("freq (hz)"),"SL",N_("Lowpass Frequency"),&fslider0, 1e+04, 1e+03, 2e+04, 1.08);
	reg.registerVar("distortion2.gain","","S",N_("Volume Level"),&fslider2, 0.0, -3e+01, 1e+01, 0.1);
	reg.registerVar("distortion2.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider4, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("distortion2" "." p)
// -----distortion2
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("drive"), _(" drive "));
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalTableBox("");
    {
	b.create_small_rackknob(PARAM("gain"), _(" Gain "));
	b.create_small_rackknobr(PARAM("drive"), _(" Drive "));
    b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_TOP);
	b.create_small_rackknob(PARAM("Hfreq"), _("HighPass (hz)"));
    b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_TOP);
	b.create_small_rackknob(PARAM("freq"), _("LowPass (hz)"));
	b.create_small_rackknob(PARAM("wet_dry"), _(" wet/dry "));
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

} // end namespace distortion2
