// generated from file '../src/faust/jconv_post_mono.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)

#define FAUSTFLOAT float

namespace jconv_post_mono {

class Dsp {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	double 	fRec0[2];

public:
	void clear_state_f();
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);
	Dsp();
	~Dsp();
};

} // end namespace jconv_post_mono
