// generated from file '../src/faust/presence_level.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace presence_level {


Dsp::Dsp() {
}

Dsp::~Dsp() {
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	for (int i=0; i<count; i++) {
		output0[i] = (FAUSTFLOAT)(1.5811388300841898 * (double)input0[i]);
	}
}

int Dsp::register_par(const ParamReg& reg)
{
	return 0;
}


} // end namespace presence_level
