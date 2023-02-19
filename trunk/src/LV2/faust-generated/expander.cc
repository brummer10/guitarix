// generated from file '../src/LV2/faust/expander.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace expander {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst1;
	double fConst2;
	double fRec1[2];
	double fConst3;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	double fRec0[2];
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT	*fEntry0_;
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT	*fEntry1_;
	FAUSTFLOAT fEntry2;
	FAUSTFLOAT	*fEntry2_;

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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec1[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec0[l1] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = std::exp(0.0 - 1e+01 / fConst0);
	fConst2 = 1.0 - fConst1;
	fConst3 = 1.0 / fConst0;
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fHslider0 (*fHslider0_)
#define fHslider1 (*fHslider1_)
#define fEntry0 (*fEntry0_)
#define fEntry1 (*fEntry1_)
#define fEntry2 (*fEntry2_)
	double fSlow0 = std::exp(0.0 - fConst3 / std::max<double>(fConst3, double(fHslider0)));
	double fSlow1 = std::exp(0.0 - fConst3 / std::max<double>(fConst3, double(fHslider1)));
	double fSlow2 = double(fEntry1);
	double fSlow3 = fSlow2 + double(fEntry0);
	double fSlow4 = 1.0 / (fSlow2 + 0.001);
	double fSlow5 = 0.05 * (1.0 - double(fEntry2));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		fRec1[0] = fConst1 * fRec1[1] + fConst2 * std::fabs(fTemp0);
		double fTemp1 = std::max<double>(fRec1[0], fTemp0);
		double fTemp2 = fSlow1 * double(fRec0[1] < fTemp1) + fSlow0 * double(fRec0[1] >= fTemp1);
		fRec0[0] = fRec0[1] * fTemp2 + fTemp1 * (1.0 - fTemp2);
		double fTemp3 = std::max<double>(0.0, fSlow3 - 2e+01 * std::log10(std::max<double>(2.2250738585072014e-308, fRec0[0])));
		output0[i0] = FAUSTFLOAT(fTemp0 * std::pow(1e+01, fSlow5 * fTemp3 * std::min<double>(1.0, std::max<double>(0.0, fSlow4 * fTemp3))));
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
#undef fHslider0
#undef fHslider1
#undef fEntry0
#undef fEntry1
#undef fEntry2
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case ATTACK: 
		fHslider1_ = (float*)data; // , 0.001, 0.0, 1.0, 0.001 
		break;
	case RELEASE: 
		fHslider0_ = (float*)data; // , 0.1, 0.0, 1e+01, 0.01 
		break;
	case KNEE: 
		fEntry1_ = (float*)data; // , 3.0, 0.0, 2e+01, 0.1 
		break;
	case RATIO: 
		fEntry2_ = (float*)data; // , 2.0, 1.0, 2e+01, 0.1 
		break;
	case THRESHOLD: 
		fEntry0_ = (float*)data; // , -4e+01, -96.0, 1e+01, 0.1 
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
   ATTACK, 
   KNEE, 
   RATIO, 
   RELEASE, 
   THRESHOLD, 
} PortIndex;
*/

} // end namespace expander
