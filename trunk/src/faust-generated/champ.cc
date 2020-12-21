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
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec2[2];
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fRec1[4];
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;

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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec2[l1] = 0.0;
	for (int l2 = 0; (l2 < 4); l2 = (l2 + 1)) fRec1[l2] = 0.0;
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
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (9.0299809845296495e-15 * fConst0);
	fConst2 = ((fConst0 * ((fConst0 * (fConst1 + 5.8836779086030702e-13)) + 1.5483862334991899e-11)) + 3.4336259025688601e-10);
	fConst3 = (fConst0 / fConst2);
	fConst4 = (1.3455062865741699e-13 * fConst0);
	fConst5 = ((fConst0 * (fConst4 + 6.5162238324488899e-12)) + 2.1539865545079801e-14);
	fConst6 = (1.0 / fConst2);
	fConst7 = (2.7089942953588999e-14 * fConst0);
	fConst8 = ((fConst0 * ((fConst0 * (-5.8836779086030702e-13 - fConst7)) + 1.5483862334991899e-11)) + 1.0300877707706601e-09);
	fConst9 = ((fConst0 * ((fConst0 * (fConst7 + -5.8836779086030702e-13)) + -1.5483862334991899e-11)) + 1.0300877707706601e-09);
	fConst10 = ((fConst0 * ((fConst0 * (5.8836779086030702e-13 - fConst1)) + -1.5483862334991899e-11)) + 3.4336259025688601e-10);
	fConst11 = (4.0365188597225e-13 * fConst0);
	fConst12 = ((fConst0 * (-6.5162238324488899e-12 - fConst11)) + 2.1539865545079801e-14);
	fConst13 = ((fConst0 * (fConst11 + -6.5162238324488899e-12)) + -2.1539865545079801e-14);
	fConst14 = ((fConst0 * (6.5162238324488899e-12 - fConst4)) + -2.1539865545079801e-14);
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
	double fSlow0 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider0))));
	double fSlow1 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * double(fVslider1))));
	for (int i = 0; (i < ReCount); i = (i + 1)) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec2[0] = (fSlow1 + (0.999 * fRec2[1]));
		fRec1[0] = ((double(buf[i]) * fRec2[0]) - (fConst6 * (((fConst8 * fRec1[1]) + (fConst9 * fRec1[2])) + (fConst10 * fRec1[3]))));
		double fTemp0 = (fConst3 * ((((fConst5 * fRec1[0]) + (fConst12 * fRec1[1])) + (fConst13 * fRec1[2])) + (fConst14 * fRec1[3])));
		buf[i] = FAUSTFLOAT((0.20000000000000001 * (fRec0[0] * (int(signbit(double(fTemp0))) ? double(tweedchamp_negclip(double(fTemp0))) : double(tweedchampclip(double(fTemp0)))))));
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
			fRec1[j0] = fRec1[(j0 - 1)];
		}
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
	fVslider0_ = reg.registerFloatVar("poweramp.Gain","","SA","",&fVslider0, 0.0, -30.0, 30.0, 0.10000000000000001, 0);
	fVslider1_ = reg.registerFloatVar("poweramp.Pregain","","SA","",&fVslider1, 0.0, -30.0, 30.0, 0.10000000000000001, 0);
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
