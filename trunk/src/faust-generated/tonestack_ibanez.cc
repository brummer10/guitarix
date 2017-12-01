// generated from file '../src/faust/tonestack_ibanez.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace tonestack_ibanez {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fRec0[4];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;

	void clear_state_f();
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
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
	id = "Ibanez";
	name = N_("Ibanez Style");
	groups = 0;
	description = ""; // description (tooltip)
	category = "";       // category
	shortname = "";     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	load_ui = 0;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<4; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(1.92e+05, max(1.0, (double)fSamplingFreq)));
	fConst1 = (2 * fConst0);
	fConst2 = faustpower<2>(fConst1);
	fConst3 = (6 * fConst0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	double 	fSlow0 = double(fslider0);
	double 	fSlow1 = (4.0108000000000004e-07 * fSlow0);
	double 	fSlow2 = exp((3.4 * (double(fslider1) - 1)));
	double 	fSlow3 = ((0.00010263250000000001 * fSlow2) + (fSlow0 * ((1.0027e-05 * fSlow2) - (3.5719200000000006e-06 + fSlow1))));
	double 	fSlow4 = (5.050300000000001e-06 + fSlow3);
	double 	fSlow5 = (3.78e-11 * fSlow0);
	double 	fSlow6 = (9.45e-10 * fSlow2);
	double 	fSlow7 = (6.75e-09 * fSlow2);
	double 	fSlow8 = (2.7e-10 + (fSlow7 + (fSlow0 * (fSlow6 - (fSlow5 + 2.3219999999999998e-10)))));
	double 	fSlow9 = (fConst1 * fSlow8);
	double 	fSlow10 = (0.025067500000000003 * fSlow2);
	double 	fSlow11 = (0.0004 * fSlow0);
	double 	fSlow12 = (fConst1 * (0.0150702 + (fSlow11 + fSlow10)));
	double 	fSlow13 = ((fSlow12 + (fConst2 * (fSlow9 - fSlow4))) - 1);
	double 	fSlow14 = (fConst3 * fSlow8);
	double 	fSlow15 = ((fSlow12 + (fConst2 * (fSlow4 - fSlow14))) - 3);
	double 	fSlow16 = ((fConst2 * (5.050300000000001e-06 + (fSlow3 + fSlow14))) - (3 + fSlow12));
	double 	fSlow17 = (1.0 / (0 - (1 + (fSlow12 + (fConst2 * (5.050300000000001e-06 + (fSlow3 + fSlow9)))))));
	double 	fSlow18 = double(fslider2);
	double 	fSlow19 = ((fSlow0 * ((3.78e-11 + fSlow6) - fSlow5)) + (fSlow18 * ((2.7e-10 + fSlow7) - (2.7e-10 * fSlow0))));
	double 	fSlow20 = (fConst1 * fSlow19);
	double 	fSlow21 = (((9.45e-07 * fSlow18) + (fSlow0 * (4.2808000000000006e-07 - fSlow1))) + (fSlow2 * (2.6324999999999998e-06 + (1.0027e-05 * fSlow0))));
	double 	fSlow22 = (fSlow21 + 1.0530000000000001e-07);
	double 	fSlow23 = ((fSlow10 + (fSlow11 + (6.75e-05 * fSlow18))) + 0.0010027);
	double 	fSlow24 = (fConst1 * fSlow23);
	double 	fSlow25 = (fSlow24 + (fConst2 * (0 - (fSlow22 - fSlow20))));
	double 	fSlow26 = (fConst3 * fSlow19);
	double 	fSlow27 = (fSlow24 + (fConst2 * (fSlow22 - fSlow26)));
	double 	fSlow28 = (fConst1 * (0 - fSlow23));
	double 	fSlow29 = (fSlow28 + (fConst2 * (1.0530000000000001e-07 + (fSlow21 + fSlow26))));
	double 	fSlow30 = (fSlow28 - (fConst2 * (1.0530000000000001e-07 + (fSlow21 + fSlow20))));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((double)input0[i] - (fSlow17 * (((fSlow16 * fRec0[1]) + (fSlow15 * fRec0[2])) + (fSlow13 * fRec0[3]))));
		output0[i] = (FAUSTFLOAT)(fSlow17 * ((((fSlow30 * fRec0[0]) + (fSlow29 * fRec0[1])) + (fSlow27 * fRec0[2])) + (fSlow25 * fRec0[3])));
		// post processing
		for (int i=3; i>0; i--) fRec0[i] = fRec0[i-1];
	}
#undef fslider0
#undef fslider1
#undef fslider2
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	fslider1_ = reg.registerVar("amp.tonestack.Bass","","SA","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	fslider0_ = reg.registerVar("amp.tonestack.Middle","","SA","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	fslider2_ = reg.registerVar("amp.tonestack.Treble","","SA","",&fslider2, 0.5, 0.0, 1.0, 0.01);
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

} // end namespace tonestack_ibanez
