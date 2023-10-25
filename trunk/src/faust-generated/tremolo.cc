// generated from file '../src/faust/tremolo.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace tremolo {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	int iVec0[2];
	double fConst1;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fVslider0;
	double fRec1[2];
	double fConst2;
	double fRec4[2];
	double fRec3[2];
	double fRec2[2];
	double fConst3;
	int iRec6[2];
	int iRec5[2];
	FAUSTFLOAT fVslider1;
	double fRec0[2];
	FAUSTFLOAT fVslider2;

	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int sample_rate, PluginDef*);
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
	id = "tremolo";
	name = N_("Tremolo");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) iVec0[l0] = 0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec1[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec4[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec3[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec2[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) iRec6[l5] = 0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) iRec5[l6] = 0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec0[l7] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 1.0 / fConst0;
	fConst2 = 6.283185307179586 / fConst0;
	fConst3 = 0.5 * fConst0;
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = double(fCheckbox0);
	int iSlow1 = fSlow0 == 0.0;
	int iSlow2 = fSlow0 == 1.0;
	double fSlow3 = double(fVslider0);
	double fSlow4 = fConst1 * fSlow3;
	double fSlow5 = fConst2 * fSlow3;
	int iSlow6 = int(fConst3 / fSlow3);
	double fSlow7 = 1.0 / double(iSlow6);
	double fSlow8 = double(fVslider1);
	double fSlow9 = double(fVslider2);
	double fSlow10 = 27.0 * fSlow9;
	double fSlow11 = 1.0 - 0.01 * fSlow9;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		iVec0[0] = 1;
		double fTemp0 = fRec0[1] * (1.0 - fConst1 / (fConst1 + 0.06 * std::exp(0.0 - 2.4849066497880004 * fRec0[1])));
		int iTemp1 = 1 - iVec0[1];
		double fTemp2 = ((iTemp1) ? 0.0 : fSlow4 + fRec1[1]);
		fRec1[0] = fTemp2 - std::floor(fTemp2);
		fRec4[0] = fRec4[1] + fSlow5 * (0.0 - fRec2[1]);
		fRec3[0] = fSlow5 * fRec4[0] + double(iTemp1) + fRec3[1];
		fRec2[0] = fRec3[0];
		iRec6[0] = ((iRec6[1] > 0) ? 2 * (iRec5[1] < iSlow6) + -1 : 1 - 2 * (iRec5[1] > 0));
		iRec5[0] = iRec6[0] + iRec5[1];
		fRec0[0] = fTemp0 + fConst1 * (std::pow(1.0 - fSlow8 * (1.0 - ((iSlow1) ? fSlow7 * double(iRec5[0]) : ((iSlow2) ? std::max<double>(0.0, 0.5 * (fRec2[0] + 1.0)) : double(fRec1[0] <= 0.5)))), 1.9) / (fConst1 + 0.06 * std::exp(0.0 - 2.4849066497880004 * fTemp0)));
		output0[i0] = FAUSTFLOAT(double(input0[i0]) * (fSlow11 + fSlow10 / (std::exp(13.815510557964274 / std::log(8.551967507929417 * fRec0[0] + 2.718281828459045)) + 2.7e+03)));
		iVec0[1] = iVec0[0];
		fRec1[1] = fRec1[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		iRec6[1] = iRec6[0];
		iRec5[1] = iRec5[0];
		fRec0[1] = fRec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	static const value_pair fCheckbox0_values[] = {{"triangle"},{"sine"},{"square"},{0}};
	reg.registerFloatVar("tremolo.SINE","","B","",&fCheckbox0, 0.0, 0.0, 1.0, 1.0, fCheckbox0_values);
	reg.registerFloatVar("tremolo.depth",N_("Depth"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("tremolo.freq",N_("Freq"),"S","",&fVslider0, 5.0, 0.1, 5e+01, 0.1, 0);
	reg.registerFloatVar("tremolo.wet_dry",N_("Dry/Wet"),"S",N_("percentage of processed signal in output signal"),&fVslider2, 1e+02, 0.0, 1e+02, 1.0, 0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade_file("tremolo_ui.glade");
        return 0;
    }
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("tremolo" "." p)
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("freq"), _("Freq"));
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalBox("");
    {
	b.insertSpacer();
	b.create_selector_no_caption(PARAM("SINE"));
	b.insertSpacer();
	b.insertSpacer();
	b.openHorizontalTableBox("");
	{
	    b.create_small_rackknobr(PARAM("freq"), _("Freq"));
	    b.insertSpacer();
	    b.create_small_rackknobr(PARAM("depth"), _("Depth"));
	    b.insertSpacer();
	    b.create_small_rackknob(PARAM("wet_dry"), _("dry/wet"));
	}
	b.closeBox();
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

} // end namespace tremolo
