// generated from file '../src/faust/jconv_post_mono.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace jconv_post_mono {


Dsp::Dsp() {
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	clear_state_f();
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0)
{
	double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
	double fSlow1 = 0.01 * double(fVslider1);
	double fSlow2 = 1.0 - fSlow1;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.999 * fRec0[1];
		output0[i0] = FAUSTFLOAT(fSlow2 * double(input0[i0]) + fSlow1 * double(input1[i0]) * fRec0[0]);
		fRec0[1] = fRec0[0];
	}
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("jconv_mono.gain",N_("Gain"),"S",N_("gain trim for processed signal (unit: dB)"),&fVslider0, 0.0, -2e+01, 2e+01, 0.1, 0);
	reg.registerFloatVar("jconv_mono.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fVslider1, 1e+02, 0.0, 1e+02, 1.0, 0);
	return 0;
}


} // end namespace jconv_post_mono
