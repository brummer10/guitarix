// generated from file '../src/faust/supersonic.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "math.h"
#include "supersonic_neg_table.h"
#include "supersonic_table.h"

namespace supersonic {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int sample_rate;
	int fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec1[2];
	double fRec0[6];
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec2[2];

	void clear_state_f();
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
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
	id = "supersonic";
	name = N_("Push Pull 6L6");
	groups = 0;
	description = N_("Push Pull 6L6"); // description (tooltip)
	category = "";       // category
	shortname = N_("SuperSonic");     // shortname
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec1[l0] = 0.0;
	for (int l1 = 0; l1 < 6; l1 = l1 + 1) fRec0[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec2[l2] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int RsamplingFreq)
{
	sample_rate = 96000;
	smp.setup(RsamplingFreq, sample_rate);
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 5.00590822563103e-27 * fConst0;
	fConst2 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (1.85439561729349e-19 - fConst1) + -1.29213045864058e-16) + 1.91675735640238e-14) + -9.77706930886932e-13) + 1.59787065310447e-11;
	fConst3 = 2.50295411281552e-26 * fConst0;
	fConst4 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst3 + -5.56318685188047e-19) + 1.29213045864058e-16) + 1.91675735640238e-14) + -2.9331207926608e-12) + 7.98935326552235e-11;
	fConst5 = 5.00590822563103e-26 * fConst0;
	fConst6 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (3.70879123458698e-19 - fConst5) + 2.58426091728115e-16) + -3.83351471280476e-14) + -1.95541386177386e-12) + 1.59787065310447e-10;
	fConst7 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst5 + 3.70879123458698e-19) + -2.58426091728115e-16) + -3.83351471280476e-14) + 1.95541386177386e-12) + 1.59787065310447e-10;
	fConst8 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-5.56318685188047e-19 - fConst3) + -1.29213045864058e-16) + 1.91675735640238e-14) + 2.9331207926608e-12) + 7.98935326552235e-11;
	fConst9 = 1.0 / (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst1 + 1.85439561729349e-19) + 1.29213045864058e-16) + 1.91675735640238e-14) + 9.77706930886932e-13) + 1.59787065310447e-11);
	fConst10 = 2.20682184684432e-26 * fConst0;
	fConst11 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (8.17344554235261e-19 - fConst10) + -1.15906710571025e-16) + 4.2235930719266e-15) + -7.76975700660911e-14) + 1.26979539981828e-12;
	fConst12 = 1.10341092342216e-25 * fConst0;
	fConst13 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst12 + -2.45203366270578e-18) + 1.15906710571025e-16) + 4.2235930719266e-15) + -2.33092710198273e-13) + 6.34897699909141e-12;
	fConst14 = 2.20682184684432e-25 * fConst0;
	fConst15 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (1.63468910847052e-18 - fConst14) + 2.31813421142051e-16) + -8.44718614385319e-15) + -1.55395140132182e-13) + 1.26979539981828e-11;
	fConst16 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst14 + 1.63468910847052e-18) + -2.31813421142051e-16) + -8.44718614385319e-15) + 1.55395140132182e-13) + 1.26979539981828e-11;
	fConst17 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-2.45203366270578e-18 - fConst12) + -1.15906710571025e-16) + 4.2235930719266e-15) + 2.33092710198273e-13) + 6.34897699909141e-12;
	fConst18 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst10 + 8.17344554235261e-19) + 1.15906710571025e-16) + 4.2235930719266e-15) + 7.76975700660911e-14) + 1.26979539981828e-12;
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
	double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider1));
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		fRec1[0] = fSlow0 + 0.999 * fRec1[1];
		fRec0[0] = double(buf[i0]) * fRec1[0] - fConst9 * (fConst8 * fRec0[1] + fConst7 * fRec0[2] + fConst6 * fRec0[3] + fConst4 * fRec0[4] + fConst2 * fRec0[5]);
		double fTemp0 = fConst9 * (fConst18 * fRec0[0] + fConst17 * fRec0[1] + fConst16 * fRec0[2] + fConst15 * fRec0[3] + fConst13 * fRec0[4] + fConst11 * fRec0[5]);
		fRec2[0] = fSlow1 + 0.999 * fRec2[1];
		buf[i0] = FAUSTFLOAT(0.8 * fRec2[0] * ((signbit(fTemp0)) ? supersonic_negclip(fTemp0) : supersonicclip(fTemp0)));
		fRec1[1] = fRec1[0];
		for (int j0 = 5; j0 > 0; j0 = j0 - 1) {
			fRec0[j0] = fRec0[j0 - 1];
		}
		fRec2[1] = fRec2[0];
	}
	smp.down(buf, output0);
#undef fVslider0
#undef fVslider1
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	fVslider1_ = reg.registerFloatVar("poweramp.Gain","","SA","",&fVslider1, 0.0, -3e+01, 3e+01, 0.1, 0);
	fVslider0_ = reg.registerFloatVar("poweramp.Pregain","","SA","",&fVslider0, 0.0, -3e+01, 3e+01, 0.1, 0);
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

} // end namespace supersonic
