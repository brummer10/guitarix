// generated from file '../src/faust/jconv_post.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#define FAUSTFLOAT float

namespace jconv_post {

class Dsp {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	float 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	float 	fRec1[2];
	FAUSTFLOAT 	fslider2;
	int 	IOTA;
	float *fVec0;
	FAUSTFLOAT 	fslider3;
	float 	fConst0;
	float 	fRec2[2];
	FAUSTFLOAT 	fslider4;
	float 	fRec3[2];
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
