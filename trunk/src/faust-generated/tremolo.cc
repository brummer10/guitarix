// generated from file '../src/faust/tremolo.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace tremolo {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iVec0[2];
	int 	iConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider0;
	double 	fConst2;
	double 	fRec1[2];
	double 	fConst3;
	double 	fConst4;
	double 	fRec4[2];
	double 	fRec3[2];
	double 	fRec2[2];
	double 	fConst5;
	int 	iRec6[2];
	int 	iRec5[2];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT 	fslider1;
	double 	fRec0[2];
	FAUSTFLOAT 	fslider2;
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) iRec6[i] = 0;
	for (int i=0; i<2; i++) iRec5[i] = 0;
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
	fConst1 = (1.0 / double(iConst0));
	fConst2 = double(iConst0);
	fConst3 = (1.0 / fConst2);
	fConst4 = (6.283185307179586 / double(iConst0));
	fConst5 = (0.5 * iConst0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = double(fslider0);
	double 	fSlow1 = (fConst2 / fSlow0);
	double 	fSlow2 = (fConst3 * fSlow0);
	double 	fSlow3 = (fConst4 * fSlow0);
	int 	iSlow4 = int((fConst5 / double(fSlow0)));
	double 	fSlow5 = (1.0 / double(iSlow4));
	int 	iSlow6 = int(double(fcheckbox0));
	double 	fSlow7 = double(fslider1);
	double 	fSlow8 = double(fslider2);
	double 	fSlow9 = (27.0 * fSlow8);
	double 	fSlow10 = (1 - (0.01 * fSlow8));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		double fTemp0 = (fRec0[1] * (1 - (fConst1 / (fConst1 + (0.06 * exp((0 - (2.4849066497880004 * fRec0[1]))))))));
		fRec1[0] = fmod((1.0 + fRec1[1]),fSlow1);
		fRec4[0] = (fRec4[1] + (fSlow3 * (0 - fRec2[1])));
		fRec3[0] = ((1 + (fRec3[1] + (fSlow3 * fRec4[0]))) - iVec0[1]);
		fRec2[0] = fRec3[0];
		iRec6[0] = ((int((iRec6[1] > 0)))?((2 * (iRec5[1] < iSlow4)) - 1):(1 - (2 * (iRec5[1] > 0))));
		iRec5[0] = (iRec6[0] + iRec5[1]);
		fRec0[0] = (fTemp0 + (fConst1 * (pow((1 + (fSlow7 * (((iSlow6==0)? (fSlow5 * iRec5[0]) : ((iSlow6==1)?max((double)0, (0.5 * (1 + fRec2[0]))):double(((fSlow2 * fRec1[0]) <= 0.5))) ) - 1))),1.9) / (fConst1 + (0.06 * exp((0 - (2.4849066497880004 * fTemp0))))))));
		output0[i] = (FAUSTFLOAT)((double)input0[i] * (fSlow10 + (fSlow9 / (2700 + exp((13.815510557964274 / log((2.718281828459045 + (8.551967507929417 * fRec0[0])))))))));
		// post processing
		fRec0[1] = fRec0[0];
		iRec5[1] = iRec5[0];
		iRec6[1] = iRec6[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec1[1] = fRec1[0];
		iVec0[1] = iVec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	static const value_pair fcheckbox0_values[] = {{"triangle"},{"sine"},{"square"},{0}};
	reg.registerEnumVar("tremolo.SINE","","B","",fcheckbox0_values,&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("tremolo.depth",N_("Depth"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("tremolo.freq",N_("Freq"),"S","",&fslider0, 5.0, 0.1, 5e+01, 0.1);
	reg.registerVar("tremolo.wet_dry",N_("Dry/Wet"),"S",N_("percentage of processed signal in output signal"),&fslider2, 1e+02, 0.0, 1e+02, 1.0);
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
