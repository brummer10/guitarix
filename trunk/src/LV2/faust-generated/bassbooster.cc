// generated from file '../src/LV2/faust/bassbooster.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace bassbooster {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fRec0[3];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
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
	for (int l0 = 0; l0 < 3; l0 = l0 + 1) fRec0[l0] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::tan(376.99111843077515 / std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate))));
	fConst1 = mydsp_faustpower2_f(fConst0);
	fConst2 = 2.0 * (fConst1 + -1.0);
	fConst3 = fConst0 * (fConst0 + -1.4142135623730951) + 1.0;
	fConst4 = 1.0 / (fConst0 * (fConst0 + 1.4142135623730951) + 1.0);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
	double fSlow0 = std::pow(1e+01, 0.05 * double(fVslider0));
	double fSlow1 = fConst0 * fSlow0;
	double fSlow2 = std::sqrt(2.0 * fSlow0);
	double fSlow3 = 1.0 - fConst0 * (fSlow2 - fSlow1);
	double fSlow4 = 2.0 * (fConst1 * fSlow0 + -1.0);
	double fSlow5 = fConst0 * (fSlow2 + fSlow1) + 1.0;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = double(input0[i0]) - fConst4 * (fConst3 * fRec0[2] + fConst2 * fRec0[1]);
		output0[i0] = FAUSTFLOAT(fConst4 * (fSlow5 * fRec0[0] + fSlow4 * fRec0[1] + fSlow3 * fRec0[2]));
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
		fVslider0_ = (float*)data; // , 1e+01, 0.5, 2e+01, 0.5 
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
