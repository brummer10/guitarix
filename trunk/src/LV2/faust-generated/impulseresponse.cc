// generated from file '../src/LV2/faust/impulseresponse.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace impulseresponse {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fVec0[3];
	double fConst1;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	double fConst2;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT	*fHslider2_;
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
	id = "IR";
	name = N_("ImpulseResponse");
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
	for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) fVec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) fRec0[l1] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (3.1415926535897931 / fConst0);
	fConst2 = (6.2831853071795862 / fConst0);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fHslider0 (*fHslider0_)
#define fCheckbox0 (*fCheckbox0_)
#define fHslider1 (*fHslider1_)
#define fHslider2 (*fHslider2_)
	double fSlow0 = std::exp((-1.0 * (fConst1 * double(fHslider0))));
	int iSlow1 = int(std::max<double>(0.0, std::min<double>(1.0, double(fCheckbox0))));
	double fSlow2 = (2.0 * std::cos((fConst2 * double(fHslider1))));
	double fSlow3 = (0.5 * (double(fHslider2) * (1.0 - mydsp_faustpower2_f(fSlow0))));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		double fTemp0 = double(input0[i0]);
		fVec0[0] = fTemp0;
		fRec0[0] = ((fSlow0 * (((iSlow1 ? std::max<double>(-0.59999999999999998, std::min<double>(0.59999999999999998, fTemp0)) : fSlow2) * fRec0[1]) - (fSlow0 * fRec0[2]))) + (fSlow3 * (fTemp0 - fVec0[2])));
		output0[i0] = FAUSTFLOAT((fTemp0 + fRec0[0]));
		fVec0[2] = fVec0[1];
		fVec0[1] = fVec0[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
	}
#undef fHslider0
#undef fCheckbox0
#undef fHslider1
#undef fHslider2
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	// static const value_pair fCheckbox0_values[] = {{"manual"},{"auto"},{0}};
	case AUTO_FREQ: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case BANDWIDTH: 
		fHslider0_ = (float*)data; // , 100.0, 20.0, 20000.0, 10.0 
		break;
	case FREQ: 
		fHslider1_ = (float*)data; // , 440.0, 20.0, 12000.0, 10.0 
		break;
	case PEAK: 
		fHslider2_ = (float*)data; // , 1.0, 0.0, 10.0, 0.20000000000000001 
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
   AUTO_FREQ, 
   BANDWIDTH, 
   FREQ, 
   PEAK, 
} PortIndex;
*/

} // end namespace impulseresponse
