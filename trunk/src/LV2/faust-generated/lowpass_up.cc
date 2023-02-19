// generated from file '../src/LV2/faust/lowpass_up.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace lowpass_up {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fVec0[2];
	double fConst2;
	double fConst3;
	double fRec1[2];
	double fConst5;
	double fConst6;
	double fConst8;
	double fConst9;
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
	id = "lowpass_up";
	name = N_("lowpass_up");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fVec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec1[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec0[l2] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 1.0 / std::tan(17690.308232364125 / fConst0);
	fConst2 = 1.0 - fConst1;
	fConst3 = 1.0 / (fConst1 + 1.0);
	double fConst4 = std::tan(251.32741228718345 / fConst0);
	fConst5 = 1.0 / fConst4;
	fConst6 = 1.0 - fConst5;
	double fConst7 = fConst5 + 1.0;
	fConst8 = 1.0 / fConst7;
	fConst9 = 0.0 - 1.0 / (fConst4 * fConst7);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		fVec0[0] = fTemp0;
		fRec1[0] = 0.0 - fConst3 * (fConst2 * fRec1[1] - (fTemp0 + fVec0[1]));
		fRec0[0] = fConst9 * fRec1[1] - fConst8 * (fConst6 * fRec0[1] - fConst5 * fRec1[0]);
		output0[i0] = FAUSTFLOAT(std::max<double>(-0.9, std::min<double>(0.9, ((std::fabs(fRec0[0]) < 0.33) ? 2.0 * fRec0[0] : copysign(fRec0[0], 0.3333333333333333 * (3.0 - mydsp_faustpower2_f(2.0 - 3.0 * fRec0[0])))))));
		fVec0[1] = fVec0[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
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
} PortIndex;
*/

} // end namespace lowpass_up
