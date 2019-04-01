// generated from file '../src/faust/preamp_impulse_former_st.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#define FAUSTFLOAT float

namespace preamp_impulse_former_st {

class Dsp {
private:
	int fSamplingFreq;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fConst6;
	double fVec0[3];
	double fRec1[3];
	double fRec0[3];


public:
	void clear_state_f();
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);
	Dsp();
	~Dsp();
};

} // end namespace preamp_impulse_former_st
