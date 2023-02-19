// generated from file '../src/faust/champ.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "math.h"
#include "tweedchamp_neg_table.h"
#include "tweedchamp_table.h"

namespace champ {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int sample_rate;
	int fSampleRate;
	double fConst2;
	double fConst4;
	double fConst5;
	double fConst7;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec1[2];
	double fRec0[4];
	double fConst9;
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;
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
	id = "camp";
	name = N_("Single ended 6V6GT");
	groups = 0;
	description = N_("Single ended 6V6GT"); // description (tooltip)
	category = "";       // category
	shortname = N_("Champ");     // shortname
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
	for (int l1 = 0; l1 < 4; l1 = l1 + 1) fRec0[l1] = 0.0;
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
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 9.02998098452965e-15 * fConst0;
	fConst2 = fConst0 * (fConst0 * (5.88367790860307e-13 - fConst1) + -1.54838623349919e-11) + 3.43362590256886e-10;
	double fConst3 = 2.7089942953589e-14 * fConst0;
	fConst4 = fConst0 * (fConst0 * (fConst3 + -5.88367790860307e-13) + -1.54838623349919e-11) + 1.03008777077066e-09;
	fConst5 = fConst0 * (fConst0 * (-5.88367790860307e-13 - fConst3) + 1.54838623349919e-11) + 1.03008777077066e-09;
	double fConst6 = fConst0 * (fConst0 * (fConst1 + 5.88367790860307e-13) + 1.54838623349919e-11) + 3.43362590256886e-10;
	fConst7 = 1.0 / fConst6;
	double fConst8 = 1.34550628657417e-13 * fConst0;
	fConst9 = fConst0 * (6.51622383244889e-12 - fConst8) + -2.15398655450798e-14;
	double fConst10 = 4.0365188597225e-13 * fConst0;
	fConst11 = fConst0 * (fConst10 + -6.51622383244889e-12) + -2.15398655450798e-14;
	fConst12 = fConst0 * (-6.51622383244889e-12 - fConst10) + 2.15398655450798e-14;
	fConst13 = fConst0 * (fConst8 + 6.51622383244889e-12) + 2.15398655450798e-14;
	fConst14 = fConst0 / fConst6;
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
		fRec0[0] = double(buf[i0]) * fRec1[0] - fConst7 * (fConst5 * fRec0[1] + fConst4 * fRec0[2] + fConst2 * fRec0[3]);
		double fTemp0 = fConst14 * (fConst13 * fRec0[0] + fConst12 * fRec0[1] + fConst11 * fRec0[2] + fConst9 * fRec0[3]);
		fRec2[0] = fSlow1 + 0.999 * fRec2[1];
		buf[i0] = FAUSTFLOAT(0.2 * fRec2[0] * ((signbit(fTemp0)) ? tweedchamp_negclip(fTemp0) : tweedchampclip(fTemp0)));
		fRec1[1] = fRec1[0];
		for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
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

} // end namespace champ
