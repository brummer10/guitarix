// generated from file '../src/faust/supersonic.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#include "math.h"
#include "supersonic_neg_table.h"
#include "supersonic_table.h"

namespace supersonic {

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
	double fConst11;
	double fRec0[6];
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;

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
	for (int l0 = 0; (l0 < 6); l0 = (l0 + 1)) fRec0[l0] = 0.0;
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
	fConst1 = (5.00590822563103e-27 * fConst0);
	fConst2 = (1.0 / (((((((((fConst1 + 1.8543956172934899e-19) * fConst0) + 1.2921304586405799e-16) * fConst0) + 1.91675735640238e-14) * fConst0) + 9.7770693088693206e-13) * fConst0) + 1.5978706531044701e-11));
	fConst3 = (2.20682184684432e-26 * fConst0);
	fConst4 = (((((((((fConst3 + 8.1734455423526096e-19) * fConst0) + 1.15906710571025e-16) * fConst0) + 4.2235930719266002e-15) * fConst0) + 7.7697570066091103e-14) * fConst0) + 1.26979539981828e-12);
	fConst5 = (2.50295411281552e-26 * fConst0);
	fConst6 = (((((((((-5.5631868518804697e-19 - fConst5) * fConst0) + -1.2921304586405799e-16) * fConst0) + 1.91675735640238e-14) * fConst0) + 2.9331207926608e-12) * fConst0) + 7.9893532655223494e-11);
	fConst7 = (5.0059082256310297e-26 * fConst0);
	fConst8 = (((((((((fConst7 + 3.7087912345869798e-19) * fConst0) + -2.5842609172811499e-16) * fConst0) + -3.8335147128047599e-14) * fConst0) + 1.9554138617738601e-12) * fConst0) + 1.5978706531044699e-10);
	fConst9 = (((((((((3.7087912345869798e-19 - fConst7) * fConst0) + 2.5842609172811499e-16) * fConst0) + -3.8335147128047599e-14) * fConst0) + -1.9554138617738601e-12) * fConst0) + 1.5978706531044699e-10);
	fConst10 = (((((((((fConst5 + -5.5631868518804697e-19) * fConst0) + 1.2921304586405799e-16) * fConst0) + 1.91675735640238e-14) * fConst0) + -2.9331207926608e-12) * fConst0) + 7.9893532655223494e-11);
	fConst11 = (((((((((1.8543956172934899e-19 - fConst1) * fConst0) + -1.2921304586405799e-16) * fConst0) + 1.91675735640238e-14) * fConst0) + -9.7770693088693206e-13) * fConst0) + 1.5978706531044701e-11);
	fConst12 = (1.1034109234221601e-25 * fConst0);
	fConst13 = (((((((((-2.4520336627057799e-18 - fConst12) * fConst0) + -1.15906710571025e-16) * fConst0) + 4.2235930719266002e-15) * fConst0) + 2.3309271019827298e-13) * fConst0) + 6.3489769990914101e-12);
	fConst14 = (2.2068218468443202e-25 * fConst0);
	fConst15 = (((((((((fConst14 + 1.63468910847052e-18) * fConst0) + -2.3181342114205098e-16) * fConst0) + -8.4471861438531893e-15) * fConst0) + 1.55395140132182e-13) * fConst0) + 1.2697953998182799e-11);
	fConst16 = (((((((((1.63468910847052e-18 - fConst14) * fConst0) + 2.3181342114205098e-16) * fConst0) + -8.4471861438531893e-15) * fConst0) + -1.55395140132182e-13) * fConst0) + 1.2697953998182799e-11);
	fConst17 = (((((((((fConst12 + -2.4520336627057799e-18) * fConst0) + 1.15906710571025e-16) * fConst0) + 4.2235930719266002e-15) * fConst0) + -2.3309271019827298e-13) * fConst0) + 6.3489769990914101e-12);
	fConst18 = (((((((((8.1734455423526096e-19 - fConst3) * fConst0) + -1.15906710571025e-16) * fConst0) + 4.2235930719266002e-15) * fConst0) + -7.7697570066091103e-14) * fConst0) + 1.26979539981828e-12);
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
		fRec0[0] = (double(buf[i]) - (fConst2 * (((((fConst6 * fRec0[1]) + (fConst8 * fRec0[2])) + (fConst9 * fRec0[3])) + (fConst10 * fRec0[4])) + (fConst11 * fRec0[5]))));
		double fTemp0 = (fConst2 * ((((((fConst4 * fRec0[0]) + (fConst13 * fRec0[1])) + (fConst15 * fRec0[2])) + (fConst16 * fRec0[3])) + (fConst17 * fRec0[4])) + (fConst18 * fRec0[5])));
		buf[i] = FAUSTFLOAT((0.80000000000000004 * (int(signbit(double(fTemp0)))?double(supersonic_negclip(double(fTemp0))):double(supersonicclip(double(fTemp0))))));
		for (int j0 = 5; (j0 > 0); j0 = (j0 - 1)) {
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

} // end namespace supersonic
