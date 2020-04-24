// generated from file '../src/faust/champ.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "math.h"
#include "tweedchamp_neg_table.h"
#include "tweedchamp_table.h"

namespace champ {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int samplingFreq;
	int fSamplingFreq;
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
	double fConst10;
	double fRec0[4];
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;

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
	for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) fRec0[l0] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int RsamplingFreq)
{
	samplingFreq = 96000;
	smp.setup(RsamplingFreq, samplingFreq);
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = (9.0299809845296495e-15 * fConst0);
	fConst2 = (((((fConst1 + 5.8836779086030702e-13) * fConst0) + 1.5483862334991899e-11) * fConst0) + 3.4336259025688601e-10);
	fConst3 = (fConst0 / fConst2);
	fConst4 = (1.3455062865741699e-13 * fConst0);
	fConst5 = (((fConst4 + 6.5162238324488899e-12) * fConst0) + 2.1539865545079801e-14);
	fConst6 = (1.0 / fConst2);
	fConst7 = (2.7089942953588999e-14 * fConst0);
	fConst8 = (((((-5.8836779086030702e-13 - fConst7) * fConst0) + 1.5483862334991899e-11) * fConst0) + 1.0300877707706601e-09);
	fConst9 = (((((fConst7 + -5.8836779086030702e-13) * fConst0) + -1.5483862334991899e-11) * fConst0) + 1.0300877707706601e-09);
	fConst10 = (((((5.8836779086030702e-13 - fConst1) * fConst0) + -1.5483862334991899e-11) * fConst0) + 3.4336259025688601e-10);
	fConst11 = (4.0365188597225e-13 * fConst0);
	fConst12 = (((-6.5162238324488899e-12 - fConst11) * fConst0) + 2.1539865545079801e-14);
	fConst13 = (((fConst11 + -6.5162238324488899e-12) * fConst0) + -2.1539865545079801e-14);
	fConst14 = (((6.5162238324488899e-12 - fConst4) * fConst0) + -2.1539865545079801e-14);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	for (int i = 0; (i < ReCount); i = (i + 1)) {
		fRec0[0] = (double(buf[i]) - (fConst6 * (((fConst8 * fRec0[1]) + (fConst9 * fRec0[2])) + (fConst10 * fRec0[3]))));
		double fTemp0 = (fConst3 * ((((fConst5 * fRec0[0]) + (fConst12 * fRec0[1])) + (fConst13 * fRec0[2])) + (fConst14 * fRec0[3])));
		buf[i] = FAUSTFLOAT((0.20000000000000001 * (int(signbit(double(fTemp0)))?double(tweedchamp_negclip(double(fTemp0))):double(tweedchampclip(double(fTemp0))))));
		for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
			fRec0[j0] = fRec0[(j0 - 1)];
		}
	}
	smp.down(buf, output0);
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
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
