// generated from file '../src/LV2/faust/low_high_cut.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace low_high_cut {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	int iVec0[2];
	double fConst2;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst9;
	double fRec4[2];
	double fVec1[2];
	double fConst10;
	double fRec3[2];
	double fRec2[2];
	double fRec1[3];
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
	id = "low_highcut";
	name = N_("low high cut");
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
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec4[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fVec1[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec3[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec2[l4] = 0.0;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec1[l5] = 0.0;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec0[l6] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = std::tan(3138.4510609362032 / fConst0);
	fConst2 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst1));
	double fConst3 = 1.0 / fConst1;
	fConst4 = (fConst3 + -0.7653668647301795) / fConst1 + 1.0;
	fConst5 = 1.0 / ((fConst3 + 0.7653668647301795) / fConst1 + 1.0);
	fConst6 = (fConst3 + -1.8477590650225735) / fConst1 + 1.0;
	fConst7 = 1.0 / ((fConst3 + 1.8477590650225735) / fConst1 + 1.0);
	double fConst8 = 72.25663103256524 / fConst0;
	fConst9 = 1.0 - fConst8;
	fConst10 = 1.0 / (fConst8 + 1.0);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		iVec0[0] = 1;
		fRec4[0] = 1e-20 * double(1 - iVec0[1]) - fRec4[1];
		double fTemp0 = double(input0[i0]) + fRec4[0];
		fVec1[0] = fTemp0;
		fRec3[0] = fConst10 * (fTemp0 - fVec1[1] + fConst9 * fRec3[1]);
		fRec2[0] = fConst10 * (fRec3[0] - fRec3[1] + fConst9 * fRec2[1]);
		fRec1[0] = fRec2[0] - fConst7 * (fConst6 * fRec1[2] + fConst2 * fRec1[1]);
		fRec0[0] = fConst7 * (fRec1[2] + fRec1[0] + 2.0 * fRec1[1]) - fConst5 * (fConst4 * fRec0[2] + fConst2 * fRec0[1]);
		output0[i0] = FAUSTFLOAT(fConst5 * (fRec0[2] + fRec0[0] + 2.0 * fRec0[1]));
		iVec0[1] = iVec0[0];
		fRec4[1] = fRec4[0];
		fVec1[1] = fVec1[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[2] = fRec0[1];
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

} // end namespace low_high_cut
