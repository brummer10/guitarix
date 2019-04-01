// generated from file '../src/faust/presence_level.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#define FAUSTFLOAT float

namespace presence_level {

class Dsp {
private:
	int fSamplingFreq;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;


public:
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);
	Dsp();
	~Dsp();
};

} // end namespace presence_level
