// generated from file '../src/faust/presence_level.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace presence_level {


Dsp::Dsp() {
}

Dsp::~Dsp() {
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
	double fSlow0 = double(fVslider0);
	double fSlow1 = fSlow0 * std::pow(1e+01, 0.0 - 0.1 * fSlow0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		output0[i0] = FAUSTFLOAT(fSlow1 * double(input0[i0]));
	}
#undef fVslider0
}

int Dsp::register_par(const ParamReg& reg)
{
	fVslider0_ = reg.registerFloatVar("con.Level","","SA","",&fVslider0, 1.0, 0.5, 5.0, 0.5, 0);
	return 0;
}


} // end namespace presence_level
