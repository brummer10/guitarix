// generated from file '../src/LV2/faust/flanger_mono.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace flanger_mono {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	int iVec0[2];
	int IOTA0;
	double fVec1[4096];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	double fConst0;
	double fConst1;
	double fRec1[2];
	double fRec2[2];
	double fRec0[2];

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
	id = "flanger_mono";
	name = N_("Flanger Mono");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) iVec0[l0] = 0;
	for (int l1 = 0; l1 < 4096; l1 = l1 + 1) fVec1[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec1[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec2[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec0[l4] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 6.283185307179586 / fConst0;
	IOTA0 = 0;
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fHslider0 (*fHslider0_)
#define fVslider0 (*fVslider0_)
#define fHslider1 (*fHslider1_)
	double fSlow0 = double(fVslider0);
	double fSlow1 = 0.01 * fSlow0 * std::pow(1e+01, 0.05 * double(fHslider0));
	double fSlow2 = fConst1 * double(fHslider1);
	double fSlow3 = std::cos(fSlow2);
	double fSlow4 = std::sin(fSlow2);
	double fSlow5 = 1.0 - 0.01 * fSlow0;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		double fTemp1 = fSlow1 * fTemp0;
		iVec0[0] = 1;
		double fTemp2 = 0.5 * fRec0[1] - fTemp1;
		fVec1[IOTA0 & 4095] = fTemp2;
		fRec1[0] = fSlow4 * fRec2[1] + fSlow3 * fRec1[1];
		fRec2[0] = double(1 - iVec0[1]) + fSlow3 * fRec2[1] - fSlow4 * fRec1[1];
		double fTemp3 = fConst0 * (0.005 * (fRec1[0] + 1.0) + 0.001);
		int iTemp4 = int(fTemp3);
		double fTemp5 = std::floor(fTemp3);
		fRec0[0] = fVec1[(IOTA0 - std::min<int>(2049, std::max<int>(0, iTemp4))) & 4095] * (fTemp5 + (1.0 - fTemp3)) + (fTemp3 - fTemp5) * fVec1[(IOTA0 - std::min<int>(2049, std::max<int>(0, iTemp4 + 1))) & 4095];
		output0[i0] = FAUSTFLOAT(fSlow5 * fTemp0 + 0.5 * (fTemp1 - fRec0[0]));
		iVec0[1] = iVec0[0];
		IOTA0 = IOTA0 + 1;
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec0[1] = fRec0[0];
	}
#undef fHslider0
#undef fVslider0
#undef fHslider1
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
		fHslider1_ = (float*)data; // , 0.2, 0.0, 5.0, 0.01 
		break;
	case LEVEL: 
		fHslider0_ = (float*)data; // , 0.0, -6e+01, 1e+01, 0.1 
		break;
	case WET_DRY: 
		fVslider0_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
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
   LEVEL, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace flanger_mono
