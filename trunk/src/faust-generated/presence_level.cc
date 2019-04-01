// generated from file '../src/faust/presence_level.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace presence_level {


Dsp::Dsp() {
}

Dsp::~Dsp() {
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fVslider0 = FAUSTFLOAT(1.0);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
	double fSlow0 = double(fVslider0);
	double fSlow1 = (std::pow(10.0, (0.0 - (0.10000000000000001 * fSlow0))) * fSlow0);
	for (int i = 0; (i < count); i = (i + 1)) {
		output0[i] = FAUSTFLOAT((fSlow1 * double(input0[i])));
	}
#undef fVslider0
}

int Dsp::register_par(const ParamReg& reg)
{
	fVslider0_ = reg.registerVar("con.Level","","SA","",&fVslider0, 1.0, 0.5, 5.0, 0.5);
	return 0;
}


} // end namespace presence_level
