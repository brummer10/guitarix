// generated from file '../src/faust/tonestack_mesa.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

namespace tonestack_mesa {
class Dsp: public PluginDef {
private:
FAUSTFLOAT 	fslider0;
FAUSTFLOAT	*fslider0_;
#define fslider0 (*fslider0_)
FAUSTFLOAT 	fslider1;
FAUSTFLOAT	*fslider1_;
#define fslider1 (*fslider1_)
double 	fConst0;
double 	fConst1;
double 	fConst2;
double 	fRec0[4];
FAUSTFLOAT 	fslider2;
FAUSTFLOAT	*fslider2_;
#define fslider2 (*fslider2_)
    int fSamplingFreq;
    void clear_state_f();
    static void clear_state_f_static(PluginDef*);
    void init(unsigned int samplingFreq);
    static void init_static(unsigned int samplingFreq, PluginDef*);
    void compute(int count, float *input0, float *output0);
    static void compute_static(int count, float *input0, float *output0, PluginDef*);
    int register_par(const ParamReg& reg);
    static int register_params_static(const ParamReg& reg);
    static void del_instance(PluginDef *p);
public:
    Dsp();
    ~Dsp();
};


Dsp::Dsp(): PluginDef() {
    version = PLUGINDEF_VERSION;
    flags = 0;
    id = "Mesa Boogie";
    name = N_("Mesa Boogie");
    groups = 0;
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
	fConst0 = (2 * double(min(192000, max(1, fSamplingFreq))));
	fConst1 = faustpower<2>(fConst0);
	fConst2 = (3 * fConst0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
    static_cast<Dsp*>(p)->init(samplingFreq);
}


inline void Dsp::compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (2.9448437500000003e-06 * fSlow0);
	double 	fSlow2 = exp((3.4 * (fslider1 - 1)));
	double 	fSlow3 = (1.2916875000000002e-05 + ((0.00011998125000000002 * fSlow2) + (fSlow0 * (((2.9448437500000007e-05 * fSlow2) - 8.731718750000001e-06) - fSlow1))));
	double 	fSlow4 = ((2.5703125000000004e-09 * fSlow2) - (2.5703125000000003e-10 * fSlow0));
	double 	fSlow5 = (7.343750000000001e-09 * fSlow2);
	double 	fSlow6 = (7.343750000000001e-10 + (fSlow5 + (fSlow0 * (fSlow4 - 4.773437500000001e-10))));
	double 	fSlow7 = (fConst0 * fSlow6);
	double 	fSlow8 = (0.001175 * fSlow0);
	double 	fSlow9 = (0.0250625 * fSlow2);
	double 	fSlow10 = (fConst0 * (0.01726875 + (fSlow9 + fSlow8)));
	double 	fSlow11 = ((fSlow10 + (fConst1 * (fSlow7 - fSlow3))) - 1);
	double 	fSlow12 = (fConst2 * fSlow6);
	double 	fSlow13 = ((fConst1 * (fSlow3 + fSlow12)) - (3 + fSlow10));
	double 	fSlow14 = ((fSlow10 + (fConst1 * (fSlow3 - fSlow12))) - 3);
	double 	fSlow15 = (1.0 / (0 - (1 + (fSlow10 + (fConst1 * (fSlow3 + fSlow7))))));
	double 	fSlow16 = fslider2;
	double 	fSlow17 = ((fSlow0 * (2.5703125000000003e-10 + fSlow4)) + (fSlow16 * ((7.343750000000001e-10 - (7.343750000000001e-10 * fSlow0)) + fSlow5)));
	double 	fSlow18 = (fConst2 * fSlow17);
	double 	fSlow19 = (2.48125e-07 + (((9.187500000000001e-07 * fSlow16) + (fSlow0 * (3.0182812500000004e-06 - fSlow1))) + (fSlow2 * (2.48125e-06 + (2.9448437500000007e-05 * fSlow0)))));
	double 	fSlow20 = (0.0025062500000000002 + (fSlow9 + (fSlow8 + (6.25e-05 * fSlow16))));
	double 	fSlow21 = (fConst0 * fSlow20);
	double 	fSlow22 = (fSlow21 + (fConst1 * (fSlow19 - fSlow18)));
	double 	fSlow23 = (fConst0 * fSlow17);
	double 	fSlow24 = (fSlow21 + (fConst1 * (fSlow23 - fSlow19)));
	double 	fSlow25 = (fConst0 * (0 - fSlow20));
	double 	fSlow26 = (fSlow25 + (fConst1 * (fSlow19 + fSlow18)));
	double 	fSlow27 = (fSlow25 - (fConst1 * (fSlow19 + fSlow23)));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((double)input0[i] - (fSlow15 * (((fSlow14 * fRec0[2]) + (fSlow13 * fRec0[1])) + (fSlow11 * fRec0[3]))));
		output0[i] = (FAUSTFLOAT)(fSlow15 * ((fSlow27 * fRec0[0]) + ((fSlow26 * fRec0[1]) + ((fSlow24 * fRec0[3]) + (fSlow22 * fRec0[2])))));
		// post processing
		for (int i=3; i>0; i--) fRec0[i] = fRec0[i-1];
	}
}

void Dsp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
    static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
#undef fslider2
	fslider2_ = reg.registerVar("amp.tonestack.Treble","","SA","",&fslider2, 0.5, 0.0, 1.0, 0.01);
#undef fslider1
	fslider1_ = reg.registerVar("amp.tonestack.Bass","","SA","",&fslider1, 0.5, 0.0, 1.0, 0.01);
#undef fslider0
	fslider0_ = reg.registerVar("amp.tonestack.Middle","","SA","",&fslider0, 0.5, 0.0, 1.0, 0.01);
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

} // end namespace tonestack_mesa
