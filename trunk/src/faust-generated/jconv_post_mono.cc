// generated from file '../src/faust/jconv_post_mono.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace jconv_post_mono {


Dsp::Dsp() {
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	clear_state_f();
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider0))));
	double 	fSlow1 = (0.01 * double(fslider1));
	double 	fSlow2 = (1 - fSlow1);
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.999 * fRec0[1]) + fSlow0);
		output0[i] = (FAUSTFLOAT)((fSlow2 * (double)input0[i]) + (fSlow1 * ((double)input1[i] * fRec0[0])));
		// post processing
		fRec0[1] = fRec0[0];
	}

}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("jconv_mono.gain",N_("Gain"),"S",N_("gain trim for processed signal (unit: dB)"),&fslider0, 0.0, -2e+01, 2e+01, 0.1);
	reg.registerVar("jconv_mono.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider1, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}


} // end namespace jconv_post_mono
