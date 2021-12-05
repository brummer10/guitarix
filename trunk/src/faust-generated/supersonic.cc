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
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	double fConst2;
	double fConst4;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec2[2];
	double fConst6;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fRec1[6];
	double fConst13;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;

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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec2[l1] = 0.0;
	for (int l2 = 0; (l2 < 6); l2 = (l2 + 1)) fRec1[l2] = 0.0;
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
	double fConst1 = (5.00590822563103e-27 * fConst0);
	fConst2 = (1.0 / ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst1 + 1.8543956172934899e-19)) + 1.2921304586405799e-16)) + 1.91675735640238e-14)) + 9.7770693088693206e-13)) + 1.5978706531044701e-11));
	double fConst3 = (2.20682184684432e-26 * fConst0);
	fConst4 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst3 + 8.1734455423526096e-19)) + 1.15906710571025e-16)) + 4.2235930719266002e-15)) + 7.7697570066091103e-14)) + 1.26979539981828e-12);
	double fConst5 = (2.50295411281552e-26 * fConst0);
	fConst6 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-5.5631868518804697e-19 - fConst5)) + -1.2921304586405799e-16)) + 1.91675735640238e-14)) + 2.9331207926608e-12)) + 7.9893532655223494e-11);
	double fConst7 = (5.0059082256310297e-26 * fConst0);
	fConst8 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst7 + 3.7087912345869798e-19)) + -2.5842609172811499e-16)) + -3.8335147128047599e-14)) + 1.9554138617738601e-12)) + 1.5978706531044699e-10);
	fConst9 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (3.7087912345869798e-19 - fConst7)) + 2.5842609172811499e-16)) + -3.8335147128047599e-14)) + -1.9554138617738601e-12)) + 1.5978706531044699e-10);
	fConst10 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst5 + -5.5631868518804697e-19)) + 1.2921304586405799e-16)) + 1.91675735640238e-14)) + -2.9331207926608e-12)) + 7.9893532655223494e-11);
	fConst11 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (1.8543956172934899e-19 - fConst1)) + -1.2921304586405799e-16)) + 1.91675735640238e-14)) + -9.7770693088693206e-13)) + 1.5978706531044701e-11);
	double fConst12 = (1.1034109234221601e-25 * fConst0);
	fConst13 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (-2.4520336627057799e-18 - fConst12)) + -1.15906710571025e-16)) + 4.2235930719266002e-15)) + 2.3309271019827298e-13)) + 6.3489769990914101e-12);
	double fConst14 = (2.2068218468443202e-25 * fConst0);
	fConst15 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst14 + 1.63468910847052e-18)) + -2.3181342114205098e-16)) + -8.4471861438531893e-15)) + 1.55395140132182e-13)) + 1.2697953998182799e-11);
	fConst16 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (1.63468910847052e-18 - fConst14)) + 2.3181342114205098e-16)) + -8.4471861438531893e-15)) + -1.55395140132182e-13)) + 1.2697953998182799e-11);
	fConst17 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fConst12 + -2.4520336627057799e-18)) + 1.15906710571025e-16)) + 4.2235930719266002e-15)) + -2.3309271019827298e-13)) + 6.3489769990914101e-12);
	fConst18 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (8.1734455423526096e-19 - fConst3)) + -1.15906710571025e-16)) + 4.2235930719266002e-15)) + -7.7697570066091103e-14)) + 1.26979539981828e-12);
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
	for (int i0 = 0; (i0 < ReCount); i0 = (i0 + 1)) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec2[0] = (fSlow1 + (0.999 * fRec2[1]));
		fRec1[0] = ((double(buf[i0]) * fRec2[0]) - (fConst2 * (((((fConst6 * fRec1[1]) + (fConst8 * fRec1[2])) + (fConst9 * fRec1[3])) + (fConst10 * fRec1[4])) + (fConst11 * fRec1[5]))));
		double fTemp0 = (fConst2 * ((((((fConst4 * fRec1[0]) + (fConst13 * fRec1[1])) + (fConst15 * fRec1[2])) + (fConst16 * fRec1[3])) + (fConst17 * fRec1[4])) + (fConst18 * fRec1[5])));
		double fThen0 = double(supersonicclip(double(fTemp0)));
		double fElse0 = double(supersonic_negclip(double(fTemp0)));
		buf[i0] = FAUSTFLOAT((0.80000000000000004 * (fRec0[0] * (int(signbit(double(fTemp0))) ? fElse0 : fThen0))));
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		for (int j0 = 5; (j0 > 0); j0 = (j0 - 1)) {
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

} // end namespace supersonic
