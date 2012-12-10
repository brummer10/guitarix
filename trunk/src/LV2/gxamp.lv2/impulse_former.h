// generated from file '../src/faust/presence_level.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)

#define FAUSTFLOAT float


class Impf {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
    void init(unsigned int samplingFreq);
	void connect(uint32_t port,void* data);

public:
	void compute(int count, float *input0, float *output0);
    static void connect_static(uint32_t port,void* data, Impf *p);
    static void init_static(unsigned int samplingFreq, Impf *p);
	Impf();
	~Impf();
};

