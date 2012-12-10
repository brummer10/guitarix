// generated from file '../src/faust/presence_level.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)




Impf::Impf() {
}

Impf::~Impf() {
}

inline void Impf::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
    fslider0 = 1.;
}

inline void Impf::compute(int count, float *input0, float *output0)
{
    fslider0 = (*fslider0_);
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (fSlow0 * pow(10,(0 - (0.1 * fSlow0))));
	for (int i=0; i<count; i++) {
		output0[i] = (FAUSTFLOAT)(fSlow1 * (double)input0[i]);
	}
}

void Impf::connect(uint32_t port,void* data)
{
    switch ((PortIndex)port) {
      case AMP_MASTERGAIN:
        break;
      case AMP_PREGAIN:
        break;
      case AMP_WET_DRY:
        break;
      case AMP_DRIVE:
        break;
      case MID:
        break;
      case BASS:
        break;
      case TREBLE:
        break;
      case CLevel:
        fslider0_ = (float*)data;
        break;
      case ALevel:
        break;
      case AMP_OUTPUT:
        //output = (float*)data;
        break;
      case AMP_INPUT:
        //input = (float*)data;
        break;
      case AMP_CONTROL:
        break;
      case AMP_NOTIFY:
        break;
    }
}

void Impf::connect_static(uint32_t port,void* data, Impf *p)
{
	static_cast<Impf*>(p)->connect(port, data);
}

void Impf::init_static(unsigned int samplingFreq, Impf *p)
{
	static_cast<Impf*>(p)->init(samplingFreq);
}

