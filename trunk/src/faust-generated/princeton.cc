// generated from file '../src/faust/princeton.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "princeton_table.h"

namespace princeton {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int sample_rate;
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	double fConst2;
	double fConst4;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec2[2];
	double fConst6;
	double fConst7;
	double fRec1[3];
	double fConst8;
	double fConst9;

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
	id = "princeton";
	name = N_("Single ended 6V6");
	groups = 0;
	description = N_("Single ended 6V6"); // description (tooltip)
	category = "";       // category
	shortname = N_("Princeton");     // shortname
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec2[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRec1[l2] = 0.0;
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
	double fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 4.3142917114013401e-10 * fConst0;
	fConst2 = 1.0 / (fConst0 * (fConst1 + 1.24411557886099e-07) + 1.5434914598554401e-05);
	double fConst3 = 2.4638375260021699e-09 * fConst0;
	fConst4 = fConst0 * (fConst3 + 1.1853646984522199e-07);
	double fConst5 = mydsp_faustpower2_f(fConst0);
	fConst6 = 3.0869829197108802e-05 - 8.6285834228026802e-10 * fConst5;
	fConst7 = fConst0 * (fConst1 + -1.24411557886099e-07) + 1.5434914598554401e-05;
	fConst8 = 0.0 - 4.9276750520043498e-09 * fConst5;
	fConst9 = fConst0 * (fConst3 + -1.1853646984522199e-07);
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
	double fSlow0 = 0.0010000000000000009 * std::pow(10.0, 0.050000000000000003 * double(fVslider0));
	double fSlow1 = 0.0010000000000000009 * std::pow(10.0, 0.050000000000000003 * double(fVslider1));
	for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.999 * fRec0[1];
		fRec2[0] = fSlow1 + 0.999 * fRec2[1];
		fRec1[0] = double(buf[i0]) * fRec2[0] - fConst2 * (fConst6 * fRec1[1] + fConst7 * fRec1[2]);
		buf[i0] = FAUSTFLOAT(0.20000000000000001 * fRec0[0] * double(princetonclip(double(fConst2 * (fConst4 * fRec1[0] + fConst8 * fRec1[1] + fConst9 * fRec1[2])))));
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
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

} // end namespace princeton
