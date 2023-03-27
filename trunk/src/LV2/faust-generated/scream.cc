// generated from file '../src/LV2/faust/scream.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace scream {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	double fConst2;
	double fConst4;
	double fConst6;
	double fRec1[3];
	double fConst7;

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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 3; l1 = l1 + 1) fRec1[l1] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 3.64434266110822e-10 * fConst0;
	fConst2 = fConst0 * (fConst1 + -3.23311541086178e-06) + 0.00515391115930048;
	double fConst3 = mydsp_faustpower2_f(fConst0);
	fConst4 = 0.010307822318601 - 7.28868532221644e-10 * fConst3;
	double fConst5 = fConst0 * (fConst1 + 3.23311541086178e-06) + 0.00515391115930048;
	fConst6 = 1.0 / fConst5;
	fConst7 = fConst3 / fConst5;
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
	double fSlow0 = 0.007000000000000006 * double(fVslider0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		double fTemp0 = 0.0 - 6.82076449438528e-09 * fRec0[0] + -6.82076449438528e-10;
		fRec1[0] = double(input0[i0]) - fConst6 * (fConst4 * fRec1[1] + fConst2 * fRec1[2]);
		output0[i0] = FAUSTFLOAT(std::min<double>(0.4514, std::max<double>(-0.2514, fConst7 * (fRec1[0] * fTemp0 + fRec1[1] * (1.36415289887706e-08 * fRec0[0] + 1.36415289887706e-09) + fRec1[2] * fTemp0))));
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1];
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
