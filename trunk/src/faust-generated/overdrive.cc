// generated from file '../src/faust/overdrive.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace overdrive {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int samplingFreq;
	int fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	double 	fRec2[2];
	double 	fVec0[2];
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fRec1[2];
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
	id = "overdrive";
	name = N_("Overdrive");
	groups = 0;
	description = ""; // description (tooltip)
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
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int RsamplingFreq)
{
	samplingFreq = 192000;
	smp.setup(RsamplingFreq, samplingFreq);
	fSamplingFreq = samplingFreq;
	fConst0 = tan((50265.48245743669 / double(min(192000, max(1, fSamplingFreq)))));
	fConst1 = (2 * (1 - (1.0 / faustpower<2>(fConst0))));
	fConst2 = (1.0 / fConst0);
	fConst3 = (1 + ((fConst2 - 1.0000000000000004) / fConst0));
	fConst4 = (1.0 / (1 + ((1.0000000000000004 + fConst2) / fConst0)));
	fConst5 = (1 + fConst2);
	fConst6 = (1.0 / fConst5);
	fConst7 = (0 - ((1 - fConst2) / fConst5));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	float buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double 	fSlow0 = double(fslider0);
	double 	fSlow1 = (0.01 * fSlow0);
	double 	fSlow2 = double(fslider1);
	double 	fSlow3 = (fSlow2 - 1);
	double 	fSlow4 = (0.0001 * faustpower<2>(fSlow0));
	double 	fSlow5 = (0.0010000000000000009 * pow(10,(0.05 * (0 - (0.5 * fSlow2)))));
	double 	fSlow6 = (1 - fSlow1);
	for (int i=0; i<ReCount; i++) {
		double fTemp0 = (double)buf[i];
		double fTemp1 = fabs((fSlow1 * fTemp0));
		fRec2[0] = ((0.999 * fRec2[1]) + fSlow5);
		double fTemp2 = (fSlow1 * (((fTemp0 * fRec2[0]) * (fSlow2 + fTemp1)) / (1 + ((fSlow4 * faustpower<2>(fTemp0)) + (fSlow3 * fTemp1)))));
		fVec0[0] = fTemp2;
		fRec1[0] = ((fConst7 * fRec1[1]) + (fConst6 * (fVec0[0] + fVec0[1])));
		fRec0[0] = (fRec1[0] - (fConst4 * ((fConst3 * fRec0[2]) + (fConst1 * fRec0[1]))));
		buf[i] = (FAUSTFLOAT)((fSlow6 * fTemp0) + (fConst4 * (fRec0[2] + (fRec0[0] + (2 * fRec0[1])))));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fVec0[1] = fVec0[0];
		fRec2[1] = fRec2[0];
	}
	smp.down(buf, output0);

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("overdrive.drive","","S","",&fslider1, 1.0, 1.0, 2e+01, 0.1);
	reg.registerVar("overdrive.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider0, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("overdrive" "." p)
// -----overdrive
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("drive"), _("Drive"));
b.closeBox();
b.openHorizontalTableBox("");
{
    b.insertSpacer();
    b.create_small_rackknobr(PARAM("drive"), _("  Drive "));
    b.create_small_rackknob(PARAM("wet_dry"), _("Dry/Wet"));
    b.insertSpacer();
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

} // end namespace overdrive
