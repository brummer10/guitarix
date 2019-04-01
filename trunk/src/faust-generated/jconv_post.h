// generated from file '../src/faust/jconv_post.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)

#define FAUSTFLOAT float

namespace jconv_post {

class Dsp {
private:
	int fSamplingFreq;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	float fRec0[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	float fRec1[2];
	FAUSTFLOAT fVslider3;
	float fRec2[2];
	int IOTA;
	float *fVec0;
	float fConst0;
	FAUSTFLOAT fVslider4;
	float fRec3[2];
	float *fVec1;

	bool mem_allocated;
	void mem_alloc();
	void mem_free();

public:
	void clear_state_f();
	int activate(bool start);
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *input2, FAUSTFLOAT *input3, FAUSTFLOAT *output0, FAUSTFLOAT *output1);
	int register_par(const ParamReg& reg);
	Dsp();
	~Dsp();
};

} // end namespace jconv_post
