// generated from file '../src/LV2/faust/noise_shaper.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace noise_shaper {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst1;
	double fConst2;
	double fRec0[2];
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
	id = "shaper";
	name = N_("Shaper");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = std::exp(0.0 - 0.1 / fConst0);
	fConst2 = std::exp(0.0 - 2e+02 / fConst0);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
	double fSlow0 = double(fVslider0);
	double fSlow1 = 5.0 * fSlow0;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		double fTemp1 = std::max<double>(1.0, std::fabs(fTemp0));
		double fTemp2 = fConst2 * double(fRec0[1] < fTemp1) + fConst1 * double(fRec0[1] >= fTemp1);
		fRec0[0] = fRec0[1] * fTemp2 + fTemp1 * (1.0 - fTemp2);
		double fTemp3 = std::max<double>(0.0, fSlow1 + 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec0[0])));
		double fTemp4 = 0.5 * std::min<double>(1.0, std::max<double>(0.0, 0.09522902580706599 * fTemp3));
		output0[i0] = FAUSTFLOAT(fTemp0 * std::pow(1e+01, 0.05 * (fSlow0 + fTemp3 * (0.0 - fTemp4) / (fTemp4 + 1.0))));
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
	case SHARPER: 
		fVslider0_ = (float*)data; // , 1.0, 1.0, 1e+01, 1.0 
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
   SHARPER, 
} PortIndex;
*/

} // end namespace noise_shaper
