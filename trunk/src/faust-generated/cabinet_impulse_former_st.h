// generated from file '../src/faust/cabinet_impulse_former_st.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#define FAUSTFLOAT float

namespace cabinet_impulse_former_st {

class Dsp {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fVec0[3];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fRec1[3];
	double 	fRec0[3];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;


public:
	void clear_state_f();
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);
	Dsp();
	~Dsp();
};

} // end namespace cabinet_impulse_former_st
