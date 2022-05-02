// generated from file '../src/faust/jconv_post.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

#define FAUSTFLOAT float

namespace jconv_post {

class Dsp {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	float fRec0[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	float fRec1[2];
	FAUSTFLOAT fVslider3;
	float fRec2[2];
	int IOTA0;
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
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *input2, FAUSTFLOAT *input3, FAUSTFLOAT *output0, FAUSTFLOAT *output1);
	int register_par(const ParamReg& reg);
	Dsp();
	~Dsp();
};

} // end namespace jconv_post
