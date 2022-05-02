// generated from file '../src/LV2/faust/biquad.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace biquad {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[3];

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
	id = "biquad";
	name = N_("BiQuad Filter");
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
	fConst0 = 6.2831853071795862 / std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
	double fSlow0 = std::log(fConst0 * double(fVslider0));
	double fSlow1 = 0.0 - 1.8442000000000001 * std::cos(std::exp(fSlow0 * (fSlow0 * (fSlow0 * (fSlow0 * (0.0050615800000000004 * fSlow0 + 0.064468059999999994) + 0.27547621) + 0.43359432999999997) + 1.3128224799999999) + 0.072388869999999994));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = double(input0[i0]) - (fSlow1 * fRec0[1] + 0.85026841000000009 * fRec0[2]);
		output0[i0] = FAUSTFLOAT(0.31622776601683794 * (fRec0[0] - 1.0589999999999999 * fRec0[1]));
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
	case FREQ: 
		fVslider0_ = (float*)data; // , 1200.0, 300.0, 3000.0, 5.0 
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
   FREQ, 
} PortIndex;
*/

} // end namespace biquad
