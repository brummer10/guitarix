// generated from file '../src/faust/low_high_cut.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#define FAUSTFLOAT float

namespace low_high_cut {

class Dsp {
private:
	int fSampleRate;
	int iVec0[2];
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fRec4[2];
	double fVec1[2];
	double fConst10;
	double fRec3[2];
	double fRec2[2];
	double fRec1[3];
	double fRec0[3];


public:
	void clear_state_f();
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);
	Dsp();
	~Dsp();
};

} // end namespace low_high_cut
