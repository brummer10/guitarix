// generated from file '../src/LV2/faust/hogsfoot.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace hogsfoot {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fRec0[4];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
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
	id = "hogsfoot";
	name = N_("Hogs Foot");
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
	for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec1[l1] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (8.9388784767912697e-15 * fConst0);
	fConst2 = ((fConst0 * ((fConst0 * (fConst1 + 4.9610614570897104e-12)) + 2.63723081667839e-11)) + 2.6773044958149099e-11);
	fConst3 = (mydsp_faustpower2_f(fConst0) / fConst2);
	fConst4 = (1.0 / fConst2);
	fConst5 = (2.6816635430373801e-14 * fConst0);
	fConst6 = ((fConst0 * ((fConst0 * (-4.9610614570897104e-12 - fConst5)) + 2.63723081667839e-11)) + 8.0319134874447397e-11);
	fConst7 = ((fConst0 * ((fConst0 * (fConst5 + -4.9610614570897104e-12)) + -2.63723081667839e-11)) + 8.0319134874447397e-11);
	fConst8 = ((fConst0 * ((fConst0 * (4.9610614570897104e-12 - fConst1)) + -2.63723081667839e-11)) + 2.6773044958149099e-11);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
	double fSlow0 = (0.01 * double(fVslider0));
	double fSlow1 = (1.0 - fSlow0);
	double fSlow2 = (0.0070000000000000062 * double(fVslider1));
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = double(input0[i]);
		fRec0[0] = ((fSlow0 * fTemp0) - (fConst4 * (((fConst6 * fRec0[1]) + (fConst7 * fRec0[2])) + (fConst8 * fRec0[3]))));
		fRec1[0] = (fSlow2 + (0.99299999999999999 * fRec1[1]));
		double fTemp1 = (9.6463226070993199e-11 * fRec1[0]);
		double fTemp2 = ((0.0 - fTemp1) + -9.6463226070993207e-13);
		double fTemp3 = (fTemp1 + 9.6463226070993207e-13);
		output0[i] = FAUSTFLOAT(((fSlow1 * fTemp0) + (fConst3 * ((((fRec0[0] * fTemp2) + (fRec0[1] * fTemp3)) + (fRec0[2] * fTemp3)) + (fRec0[3] * fTemp2)))));
		for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
			fRec0[j0] = fRec0[(j0 - 1)];
		}
		fRec1[1] = fRec1[0];
	}
#undef fVslider0
#undef fVslider1
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case VOLUME: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fVslider0_ = (float*)data; // , 100.0, 0.0, 100.0, 1.0 
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
   VOLUME, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace hogsfoot
