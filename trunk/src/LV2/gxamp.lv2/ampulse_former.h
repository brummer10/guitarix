
// generated from file '../src/faust/presence_level.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)

#define FAUSTFLOAT float


class Ampf {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
    void init(unsigned int samplingFreq);
	void connect(uint32_t port,void* data);

public:
	void compute(int count, float *input0, float *output0);
    static void connect_static(uint32_t port,void* data, Ampf *p);
    static void init_static(unsigned int samplingFreq, Ampf *p);
	Ampf();
	~Ampf();
};

