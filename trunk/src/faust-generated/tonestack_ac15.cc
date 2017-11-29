// generated from file '../src/faust/tonestack_ac15.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace tonestack_ac15 {

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
	double 	fConst4;
	double 	fRec0[4];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst5;
	double 	fConst6;

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
	id = "AC-15";
	name = N_("AC-15 Style");
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
	fConst1 = (2.1383120000000005e-08 * fConst0);
	fConst2 = (2 * fConst0);
	fConst3 = faustpower<2>(fConst2);
	fConst4 = (6.414936000000001e-08 * fConst0);
	fConst5 = (0.044206800000000004 * fConst0);
	fConst6 = (6 * fConst0);
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
	double 	fSlow0 = exp((3.4 * (double(fslider0) - 1)));
	double 	fSlow1 = double(fslider1);
	double 	fSlow2 = (0.00022854915600000004 * fSlow1);
	double 	fSlow3 = ((fSlow1 * ((0.00012621831200000002 + (0.00022854915600000004 * fSlow0)) - fSlow2)) + (0.00010719478000000002 * fSlow0));
	double 	fSlow4 = (fSlow3 + 0.00010871476000000002);
	double 	fSlow5 = (3.421299200000001e-08 * fSlow1);
	double 	fSlow6 = (1.0 + (fSlow0 + (93531720.34763868 * (fSlow1 * ((2.3521432000000005e-08 + (3.421299200000001e-08 * fSlow0)) - fSlow5)))));
	double 	fSlow7 = (fConst1 * fSlow6);
	double 	fSlow8 = (fConst2 * (0.036906800000000003 + ((0.01034 * fSlow1) + (0.022103400000000002 * fSlow0))));
	double 	fSlow9 = ((fSlow8 + (fConst3 * (fSlow7 - fSlow4))) - 1);
	double 	fSlow10 = (fConst4 * fSlow6);
	double 	fSlow11 = ((fSlow8 + (fConst3 * (fSlow4 - fSlow10))) - 3);
	double 	fSlow12 = ((fConst3 * (0.00010871476000000002 + (fSlow3 + fSlow10))) - (3 + fSlow8));
	double 	fSlow13 = (1.0 / ((fConst3 * (0 - (0.00010871476000000002 + (fSlow3 + fSlow7)))) - (1 + fSlow8)));
	double 	fSlow14 = double(fslider2);
	double 	fSlow15 = (((1.0 + fSlow0) - fSlow1) * (fSlow5 + (1.0691560000000003e-08 * fSlow14)));
	double 	fSlow16 = (fConst2 * fSlow15);
	double 	fSlow17 = (((1.5199800000000001e-06 * fSlow14) + (fSlow1 * (0.00022961831200000004 - fSlow2))) + (fSlow0 * (fSlow2 + 3.7947800000000004e-06)));
	double 	fSlow18 = (3.7947800000000004e-06 + fSlow17);
	double 	fSlow19 = (1.0 + (fSlow0 + ((0.4678013337314621 * fSlow1) + (0.0046780133373146215 * fSlow14))));
	double 	fSlow20 = (fConst5 * fSlow19);
	double 	fSlow21 = (fSlow20 + (fConst3 * (0 - (fSlow18 - fSlow16))));
	double 	fSlow22 = (fConst6 * fSlow15);
	double 	fSlow23 = (fSlow20 + (fConst3 * (fSlow18 - fSlow22)));
	double 	fSlow24 = (fConst2 * (0 - (0.022103400000000002 * fSlow19)));
	double 	fSlow25 = (fSlow24 + (fConst3 * (3.7947800000000004e-06 + (fSlow17 + fSlow22))));
	double 	fSlow26 = (fSlow24 - (fConst3 * (3.7947800000000004e-06 + (fSlow17 + fSlow16))));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((double)input0[i] - (fSlow13 * (((fSlow12 * fRec0[1]) + (fSlow11 * fRec0[2])) + (fSlow9 * fRec0[3]))));
		output0[i] = (FAUSTFLOAT)(fSlow13 * ((((fSlow26 * fRec0[0]) + (fSlow25 * fRec0[1])) + (fSlow23 * fRec0[2])) + (fSlow21 * fRec0[3])));
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
	fslider0_ = reg.registerVar("amp.tonestack.Bass","","SA","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	fslider1_ = reg.registerVar("amp.tonestack.Middle","","SA","",&fslider1, 0.5, 0.0, 1.0, 0.01);
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

} // end namespace tonestack_ac15
