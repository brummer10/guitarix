// generated from file '../src/faust/bitdowner.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace bitdowner {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	double 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	int 	iRec2[2];
	double 	fRec1[2];
	FAUSTFLOAT 	fslider3;
	double 	fRec3[2];
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
	id = "bitdowner";
	name = N_("BitDowner");
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider0))));
	double 	fSlow1 = pow(2,(double(fslider1) - 1));
	double 	fSlow2 = (1.0 / fSlow1);
	int 	iSlow3 = int(double(fslider2));
	int 	iSlow4 = (iSlow3 - 1);
	int 	iSlow5 = int((iSlow3 > 1));
	double 	fSlow6 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider3))));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.999 * fRec0[1]) + fSlow0);
		double fTemp0 = (fSlow2 * floor((fSlow1 * ((double)input0[i] * fRec0[0]))));
		double fTemp1 = ((int((fTemp0 > 1)))?1:((int((fTemp0 < -1)))?-1:fTemp0));
		iRec2[0] = int(((int((iRec2[1] < iSlow4)))?(1 + iRec2[1]):0));
		fRec1[0] = ((int((iRec2[0] == 0)))?fTemp1:fRec1[1]);
		fRec3[0] = ((0.999 * fRec3[1]) + fSlow6);
		output0[i] = (FAUSTFLOAT)(fRec3[0] * ((iSlow5)?fRec1[0]:fTemp1));
		// post processing
		fRec3[1] = fRec3[0];
		fRec1[1] = fRec1[0];
		iRec2[1] = iRec2[0];
		fRec0[1] = fRec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("bitdowner.bit_down",N_("Bit downing"),"S","",&fslider1, 16.0, 1.0, 16.0, 0.1);
	reg.registerVar("bitdowner.downsampling",N_("Downsampling,tooltip:Downsampling (samples to skip count)"),"S","",&fslider2, 1.0, 1.0, 2e+02, 1.0);
	reg.registerVar("bitdowner.input_gain",N_("Input gain,tooltip:Gain (dB)"),"S","",&fslider0, 0.0, -4e+01, 4e+01, 0.1);
	reg.registerVar("bitdowner.volume",N_("Volume,tooltip:Volume (dB)"),"S","",&fslider3, 0.0, -9e+01, 12.0, 0.1);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("bitdowner" "." p)
// ----- bitdowner
b.openHorizontalhideBox("");
b.create_master_slider("bitdowner.volume", _(" Volume "));
b.closeBox();
b.openHorizontalBox("");
{
	b.openVerticalBox("");
	{
		b.openFlipLabelBox("");
		{
			b.openHorizontalBox("");
			{
				b.create_small_rackknobr(
					"bitdowner.input_gain", _(" Input Gain "));
				b.create_small_rackknobr(
					"bitdowner.bit_down", _(" BitDown "));
				b.create_small_rackknobr(
					"bitdowner.downsampling", _(" Downsampling "));
				b.create_small_rackknobr(
					"bitdowner.volume", _(" Volume "));
			}
			b.closeBox();
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

} // end namespace bitdowner
