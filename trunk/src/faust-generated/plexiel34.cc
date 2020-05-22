// generated from file '../src/faust/plexiel34.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "math.h"
#include "plexipowerampel34_neg_table.h"
#include "plexipowerampel34_table.h"

namespace plexiel34 {

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
	double fConst10;
	double fConst11;
	double fConst12;
	double fRec0[5];
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;

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
	id = "plexiel34";
	name = N_("Push Pull EL34");
	groups = 0;
	description = N_("PlexiEL34"); // description (tooltip)
	category = "";       // category
	shortname = N_("PlexiEL34");     // shortname
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
	for (int l0 = 0; (l0 < 5); l0 = (l0 + 1)) fRec0[l0] = 0.0;
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
	fConst1 = (1.8269373389389401e-19 * fConst0);
	fConst2 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst1 + 2.7124352361658701e-16)) + 8.16290535602033e-14)) + 4.6414729817426102e-12)) + 4.0015810287500304e-12);
	fConst3 = (fConst0 / fConst2);
	fConst4 = (3.87560926163844e-19 * fConst0);
	fConst5 = ((fConst0 * ((fConst0 * (fConst4 + 4.3080090312012499e-16)) + 3.1750970560917398e-17)) + 5.3495467261266997e-19);
	fConst6 = (1.0 / fConst2);
	fConst7 = mydsp_faustpower2_f(fConst0);
	fConst8 = (7.3077493557557401e-19 * fConst0);
	fConst9 = ((fConst0 * ((fConst7 * (-5.4248704723317303e-16 - fConst8)) + 9.2829459634852301e-12)) + 1.6006324115000099e-11);
	fConst10 = ((fConst7 * ((1.0961624033633601e-18 * fConst7) + -1.63258107120407e-13)) + 2.40094861725002e-11);
	fConst11 = ((fConst0 * ((fConst7 * (5.4248704723317303e-16 - fConst8)) + -9.2829459634852301e-12)) + 1.6006324115000099e-11);
	fConst12 = ((fConst0 * ((fConst0 * ((fConst0 * (fConst1 + -2.7124352361658701e-16)) + 8.16290535602033e-14)) + -4.6414729817426102e-12)) + 4.0015810287500304e-12);
	fConst13 = (1.5502437046553801e-18 * fConst0);
	fConst14 = ((fConst7 * (-8.6160180624025097e-16 - fConst13)) + 1.0699093452253399e-18);
	fConst15 = (fConst0 * ((2.32536555698307e-18 * fConst7) + -6.3501941121834698e-17));
	fConst16 = ((fConst7 * (8.6160180624025097e-16 - fConst13)) + -1.0699093452253399e-18);
	fConst17 = ((fConst0 * ((fConst0 * (fConst4 + -4.3080090312012499e-16)) + 3.1750970560917398e-17)) + -5.3495467261266997e-19);
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	FAUSTFLOAT buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	for (int i = 0; (i < ReCount); i = (i + 1)) {
		fRec0[0] = (double(buf[i]) - (fConst6 * ((((fConst9 * fRec0[1]) + (fConst10 * fRec0[2])) + (fConst11 * fRec0[3])) + (fConst12 * fRec0[4]))));
		double fTemp0 = (fConst3 * (((((fConst5 * fRec0[0]) + (fConst14 * fRec0[1])) + (fConst15 * fRec0[2])) + (fConst16 * fRec0[3])) + (fConst17 * fRec0[4])));
		buf[i] = FAUSTFLOAT((int(signbit(double(fTemp0))) ? double(plexipowerampel34_negclip(double(fTemp0))) : double(plexipowerampel34clip(double(fTemp0)))));
		for (int j0 = 4; (j0 > 0); j0 = (j0 - 1)) {
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

} // end namespace plexiel34
