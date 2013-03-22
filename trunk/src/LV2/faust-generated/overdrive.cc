// generated from file '../src/LV2/faust/overdrive.dsp' by dsp2cc:
// Code generated with Faust 0.9.46 (http://faust.grame.fr)


namespace overdrive {

class Dsp: public PluginLV2 {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec0[2];
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(unsigned int samplingFreq, PluginLV2*);
	static void compute_static(int count, float *input0, float *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "overdrive";
	name = N_("Overdrive");
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

inline void Dsp::compute(int count, float *input0, float *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (0.0001 * faustpower<2>(fSlow0));
	double 	fSlow2 = (0.01 * fSlow0);
	double 	fSlow3 = fslider1;
	double 	fSlow4 = (fSlow3 - 1);
	double 	fSlow5 = (0.0010000000000000009 * pow(10,(0.05 * (0 - (0.5 * fSlow3)))));
	double 	fSlow6 = (1 - fSlow2);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		double fTemp1 = fabs((fSlow2 * fTemp0));
		fRec0[0] = (fSlow5 + (0.999 * fRec0[1]));
		output0[i] = (FAUSTFLOAT)(fTemp0 * (fSlow6 + (fSlow2 * ((fRec0[0] * (fSlow3 + fTemp1)) / (1 + ((fSlow4 * fTemp1) + (fSlow1 * faustpower<2>(fTemp0))))))));
		// post processing
		fRec0[1] = fRec0[0];
	}
#undef fslider0
#undef fslider1
}

void Dsp::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case DRIVE: 
		fslider1_ = (float*)data; // , 1.0, 1.0, 2e+01, 0.1 
		break;
	case WET_DRY: 
		fslider0_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
		break;
	default:
		break;
	}
}

void Dsp::connect_static(uint32_t port,void* data, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->connect(port, data);
}


PluginLV2 *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginLV2 *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace overdrive
