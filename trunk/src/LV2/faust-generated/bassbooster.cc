// generated from file '../src/LV2/faust/bassbooster.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace bassbooster {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fConst2;
	double fConst3;
	double fConst4;
	double fRec0[3];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



static const char* parm_groups[] = {
	".bassbooster", N_("Bassbooster"),
	0
	};

Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "amp.bass_boost";
	name = N_("Bassbooster");
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
	for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) fRec0[l0] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::tan((376.99111843077515 / std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)))));
	fConst1 = (1.0 / ((fConst0 * (fConst0 + 1.4142135623730951)) + 1.0));
	fConst2 = ((fConst0 * (fConst0 + -1.4142135623730951)) + 1.0);
	fConst3 = mydsp_faustpower2_f(fConst0);
	fConst4 = (2.0 * (fConst3 + -1.0));
	fVslider0 = FAUSTFLOAT(10.0);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
	double fSlow0 = std::pow(10.0, (0.050000000000000003 * double(fVslider0)));
	double fSlow1 = std::sqrt((2.0 * fSlow0));
	double fSlow2 = (fConst0 * fSlow0);
	double fSlow3 = ((fConst0 * (fSlow1 + fSlow2)) + 1.0);
	double fSlow4 = (2.0 * ((fConst3 * fSlow0) + -1.0));
	double fSlow5 = (1.0 - (fConst0 * (fSlow1 - fSlow2)));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec0[0] = (double(input0[i]) - (fConst1 * ((fConst2 * fRec0[2]) + (fConst4 * fRec0[1]))));
		output0[i] = FAUSTFLOAT((fConst1 * (((fSlow3 * fRec0[0]) + (fSlow4 * fRec0[1])) + (fSlow5 * fRec0[2]))));
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
	}
#undef fVslider0
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case LEVEL: 
		fVslider0_ = (float*)data; // , 10.0, 0.5, 20.0, 0.5 
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
   LEVEL, 
} PortIndex;
*/

} // end namespace bassbooster
