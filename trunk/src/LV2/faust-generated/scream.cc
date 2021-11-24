// generated from file '../src/LV2/faust/scream.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace scream {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fRec0[3];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec1[2];

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
	id = "scream";
	name = N_("Screaming Bird");
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
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec1[l1] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = mydsp_faustpower2_f(fConst0);
	double fConst2 = (3.6443426611082201e-10 * fConst0);
	double fConst3 = ((fConst0 * (fConst2 + 3.23311541086178e-06)) + 0.0051539111593004797);
	fConst4 = (fConst1 / fConst3);
	fConst5 = (1.0 / fConst3);
	fConst6 = (0.010307822318600999 - (7.2886853222164402e-10 * fConst1));
	fConst7 = ((fConst0 * (fConst2 + -3.23311541086178e-06)) + 0.0051539111593004797);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
	double fSlow0 = (0.0070000000000000062 * double(fVslider0));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		fRec0[0] = (double(input0[i0]) - (fConst5 * ((fConst6 * fRec0[1]) + (fConst7 * fRec0[2]))));
		fRec1[0] = (fSlow0 + (0.99299999999999999 * fRec1[1]));
		double fTemp0 = ((0.0 - (6.8207644943852797e-09 * fRec1[0])) + -6.8207644943852799e-10);
		output0[i0] = FAUSTFLOAT(std::min<double>(0.45140000000000002, std::max<double>(-0.25140000000000001, (fConst4 * (((fRec0[0] * fTemp0) + (fRec0[1] * ((1.3641528988770601e-08 * fRec1[0]) + 1.3641528988770599e-09))) + (fRec0[2] * fTemp0))))));
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
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
	case SCREAM: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   SCREAM, 
} PortIndex;
*/

} // end namespace scream
