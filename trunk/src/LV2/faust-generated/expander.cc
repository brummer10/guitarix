// generated from file '../src/LV2/faust/expander.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)


namespace expander {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fRec1[2];
	double 	fConst3;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec0[2];
	FAUSTFLOAT 	fentry0;
	FAUSTFLOAT	*fentry0_;
	FAUSTFLOAT 	fentry1;
	FAUSTFLOAT	*fentry1_;
	FAUSTFLOAT 	fentry2;
	FAUSTFLOAT	*fentry2_;
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, float *input0, float *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
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
	id = "expander";
	name = N_("Expander");
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
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = exp((0 - (1e+01 / double(iConst0))));
	fConst2 = (1 - fConst1);
	fConst3 = (1.0 / double(iConst0));
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, float *input0, float *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fentry0 (*fentry0_)
#define fentry1 (*fentry1_)
#define fentry2 (*fentry2_)
	double 	fSlow0 = exp((0 - (fConst3 / max(fConst3, fslider0))));
	double 	fSlow1 = exp((0 - (fConst3 / max(fConst3, fslider1))));
	double 	fSlow2 = fentry1;
	double 	fSlow3 = (fSlow2 + fentry0);
	double 	fSlow4 = (1.0 / (0.001 + fSlow2));
	double 	fSlow5 = (fentry2 - 1);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec1[0] = ((fConst2 * fabs(fTemp0)) + (fConst1 * fRec1[1]));
		double fTemp1 = max(fRec1[0], fTemp0);
		double fTemp2 = ((fSlow1 * (fRec0[1] >= fTemp1)) + (fSlow0 * (fRec0[1] < fTemp1)));
		fRec0[0] = ((fTemp1 * (0 - (fTemp2 - 1))) + (fRec0[1] * fTemp2));
		double fTemp3 = max((double)0, (fSlow3 - (20 * log10(fRec0[0]))));
		output0[i] = (FAUSTFLOAT)(fTemp0 * pow(10,(0.05 * (fTemp3 * (0 - (fSlow5 * min((double)1, max((double)0, (fSlow4 * fTemp3)))))))));
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
	}
#undef fslider0
#undef fslider1
#undef fentry0
#undef fentry1
#undef fentry2
}

void __rt_func Dsp::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case RATIO: 
		fentry2_ = (float*)data; // , 2.0, 1.0, 2e+01, 0.1 
		break;
	case KNEE: 
		fentry1_ = (float*)data; // , 3.0, 0.0, 2e+01, 0.1 
		break;
	case THRESHOLD: 
		fentry0_ = (float*)data; // , -4e+01, -96.0, 1e+01, 0.1 
		break;
	case RELEASE: 
		fslider1_ = (float*)data; // , 0.1, 0.0, 1e+01, 0.01 
		break;
	case ATTACK: 
		fslider0_ = (float*)data; // , 0.001, 0.0, 1.0, 0.001 
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

/*
typedef enum
{
   RATIO, 
   KNEE, 
   THRESHOLD, 
   RELEASE, 
   ATTACK, 
} PortIndex;
*/

} // end namespace expander
