// generated from file '../src/LV2/faust/compressor.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace compressor {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT	*fEntry0_;
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT	*fEntry1_;
	double fConst1;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	double fConst2;
	double fConst3;
	double fRec1[2];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	double fRec0[2];
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
	id = "compressor";
	name = N_("Compressor");
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec1[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec0[l1] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (1.0 / fConst0);
	fConst2 = std::exp((0.0 - (10.0 / fConst0)));
	fConst3 = (1.0 - fConst2);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fEntry0 (*fEntry0_)
#define fEntry1 (*fEntry1_)
#define fHslider0 (*fHslider0_)
#define fHslider1 (*fHslider1_)
#define fEntry2 (*fEntry2_)
	double fSlow0 = (1.0 - double(fEntry0));
	double fSlow1 = (0.050000000000000003 * fSlow0);
	double fSlow2 = double(fEntry1);
	double fSlow3 = std::exp((0.0 - (fConst1 / std::max<double>(fConst1, double(fHslider0)))));
	double fSlow4 = std::exp((0.0 - (fConst1 / std::max<double>(fConst1, double(fHslider1)))));
	double fSlow5 = double(fEntry2);
	double fSlow6 = (1.0 / (fSlow2 + 0.001));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		double fTemp0 = double(input0[i0]);
		fRec1[0] = ((fConst2 * fRec1[1]) + (fConst3 * std::fabs((fTemp0 + 9.9999999999999995e-21))));
		double fTemp1 = ((fSlow3 * double((fRec0[1] < fRec1[0]))) + (fSlow4 * double((fRec0[1] >= fRec1[0]))));
		fRec0[0] = ((fRec0[1] * fTemp1) + (fRec1[0] * (1.0 - fTemp1)));
		double fTemp2 = std::max<double>(0.0, (fSlow2 + ((20.0 * std::log10(std::max<double>(2.2250738585072014e-308, fRec0[0]))) - fSlow5)));
		double fTemp3 = std::min<double>(1.0, std::max<double>(0.0, (fSlow6 * fTemp2)));
		output0[i0] = FAUSTFLOAT((fTemp0 * std::pow(10.0, (fSlow1 * ((fTemp2 * fTemp3) / (1.0 - (fSlow0 * fTemp3)))))));
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
#undef fEntry0
#undef fEntry1
#undef fHslider0
#undef fHslider1
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
		fHslider0_ = (float*)data; // , 0.002, 0.0, 1.0, 0.001 
		break;
	case RELEASE: 
		fHslider1_ = (float*)data; // , 0.5, 0.0, 10.0, 0.01 
		break;
	case KNEE: 
		fEntry1_ = (float*)data; // , 3.0, 0.0, 20.0, 0.10000000000000001 
		break;
	case RATIO: 
		fEntry0_ = (float*)data; // , 2.0, 1.0, 20.0, 0.10000000000000001 
		break;
	case THRESHOLD: 
		fEntry2_ = (float*)data; // , -20.0, -96.0, 10.0, 0.10000000000000001 
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

} // end namespace compressor
