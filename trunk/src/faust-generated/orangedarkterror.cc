// generated from file '../src/faust/orangedarkterror.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "math.h"
#include "orangedarkterrorp3_neg_table.h"
#include "orangedarkterrorp3_table.h"

namespace orangedarkterror {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int sample_rate;
	int fSampleRate;
	double fConst0;
	double fConst2;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec1[2];
	double fRec0[5];
	double fConst10;
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
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
	id = "orangedarkterror";
	name = N_("Push Pull EL84");
	groups = 0;
	description = N_("Push Pull EL84"); // description (tooltip)
	category = "";       // category
	shortname = N_("OrangeDarkTerror");     // shortname
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
	for (int l1 = 0; l1 < 5; l1 = l1 + 1) fRec0[l1] = 0.0;
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
	double fConst1 = 1.86957288162412e-19 * fConst0;
	fConst2 = fConst0 * (fConst0 * (fConst0 * (fConst1 + -6.82010407286301e-17) + 4.53454013961264e-15) + -6.51104139918237e-14) + 4.73642640396319e-17;
	double fConst3 = 7.47829152649647e-19 * fConst0;
	double fConst4 = mydsp_faustpower2_f(fConst0);
	fConst5 = fConst0 * (fConst4 * (1.3640208145726e-16 - fConst3) + -1.30220827983647e-13) + 1.89457056158527e-16;
	fConst6 = fConst4 * (1.12174372897447e-18 * fConst4 + -9.06908027922528e-15) + 2.84185584237791e-16;
	fConst7 = fConst0 * (fConst4 * (-1.3640208145726e-16 - fConst3) + 1.30220827983647e-13) + 1.89457056158527e-16;
	fConst8 = 1.0 / (fConst0 * (fConst0 * (fConst0 * (fConst1 + 6.82010407286301e-17) + 4.53454013961264e-15) + 6.51104139918237e-14) + 4.73642640396319e-17);
	double fConst9 = 6.57377333665727e-19 * fConst0;
	fConst10 = fConst0 * (fConst0 * (fConst0 * (4.01607201070155e-17 - fConst9) + -4.37865590304316e-21) + -1.22291757237028e-24);
	double fConst11 = 2.62950933466291e-18 * fConst0;
	fConst12 = fConst0 * (fConst4 * (fConst11 + -8.03214402140309e-17) + -2.44583514474056e-24);
	fConst13 = fConst4 * (8.75731180608631e-21 - 3.94426400199436e-18 * fConst4);
	fConst14 = fConst4 * (fConst11 + 8.03214402140309e-17) + 2.44583514474056e-24;
	fConst15 = fConst0 * (fConst0 * (-4.01607201070155e-17 - fConst9) + -4.37865590304316e-21) + 1.22291757237028e-24;
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
		fRec0[0] = double(buf[i0]) * fRec1[0] - fConst8 * (fConst7 * fRec0[1] + fConst6 * fRec0[2] + fConst5 * fRec0[3] + fConst2 * fRec0[4]);
		double fTemp0 = fConst8 * (fConst0 * (fConst15 * fRec0[0] + fConst14 * fRec0[1]) + fConst13 * fRec0[2] + fConst12 * fRec0[3] + fConst10 * fRec0[4]);
		fRec2[0] = fSlow1 + 0.999 * fRec2[1];
		buf[i0] = FAUSTFLOAT(0.6 * fRec2[0] * ((signbit(fTemp0)) ? orangedarkterrorp3_negclip(fTemp0) : orangedarkterrorp3clip(fTemp0)));
		fRec1[1] = fRec1[0];
		for (int j0 = 4; j0 > 0; j0 = j0 - 1) {
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

} // end namespace orangedarkterror
