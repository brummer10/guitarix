// generated from file '../src/faust/bassbooster.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)



class BassBooster {
private:
	int32_t fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fRec0[3];
    float 	*fslider0_;
	float 	fslider0;
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void run(uint32_t count, float *input0, float *output0);
    void connect(uint32_t port,void* data);

public:
    static void init_static(uint32_t samplingFreq, BassBooster*);
	static void run_static(uint32_t count, float *input0, float *output0, BassBooster*);
    static void connect_static(uint32_t port,void* data, BassBooster *p);
	BassBooster();
	~BassBooster();
};


void BassBooster::connect(uint32_t port,void* data)
{
  switch ((EffectPortIndex)port)
    {
    case B_LEVEL:
      fslider0_ = (float*)data;
      break;
    default:
      break;
    }
}


BassBooster::BassBooster() {
}

BassBooster::~BassBooster() {
}

inline void BassBooster::clear_state_f()
{
	for (int32_t i=0; i<3; i++) fRec0[i] = 0;
}

inline void BassBooster::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = tan((376.99111843077515 / min(192000, max(1, fSamplingFreq))));
	fConst1 = faustpower<2>(fConst0);
	fConst2 = (2 * (fConst1 - 1));
	fConst3 = (1 + (fConst0 * (fConst0 - 1.4142135623730951)));
	fConst4 = (1.0 / (1 + (fConst0 * (1.4142135623730951 + fConst0))));
	clear_state_f();
}

inline void BassBooster::run(uint32_t count, float *input0, float *output0)
{
    fslider0 = (*fslider0_);
	double 	fSlow0 = pow(10,(0.05 * fslider0));
	double 	fSlow1 = sqrt((2 * fSlow0));
	double 	fSlow2 = (fConst0 * fSlow0);
	double 	fSlow3 = (1 + (fConst0 * (fSlow2 - fSlow1)));
	double 	fSlow4 = (2 * ((fConst1 * fSlow0) - 1));
	double 	fSlow5 = (1 + (fConst0 * (fSlow2 + fSlow1)));
	for (uint32_t i=0; i<count; i++) {
		fRec0[0] = ((double)input0[i] - (fConst4 * ((fConst3 * fRec0[2]) + (fConst2 * fRec0[1]))));
		output0[i] = (float)(fConst4 * (((fSlow5 * fRec0[0]) + (fSlow4 * fRec0[1])) + (fSlow3 * fRec0[2])));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
	}
}

void BassBooster::run_static(uint32_t count, float *input0, float *output0, BassBooster *p)
{
	p->run(count, input0, output0);
}

void BassBooster::init_static(uint32_t samplingFreq, BassBooster *p)
{
	p->init(samplingFreq);
}

void BassBooster::connect_static(uint32_t port,void* data, BassBooster *p)
{
  p->connect(port, data);
}




