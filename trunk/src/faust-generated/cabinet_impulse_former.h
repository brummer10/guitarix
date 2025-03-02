// generated from file '../src/faust/cabinet_impulse_former.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#define FAUSTFLOAT float

namespace cabinet_impulse_former {

class Dsp {
private:
	int fSampleRate;
	double fVec0[3];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fRec1[3];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst4;
	double fConst5;
	double fConst6;
	double fRec0[3];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;


public:
	void clear_state_f();
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);
	Dsp();
	~Dsp();
};

} // end namespace cabinet_impulse_former
