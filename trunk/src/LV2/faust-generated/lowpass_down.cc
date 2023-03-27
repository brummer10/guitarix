// generated from file '../src/LV2/faust/lowpass_down.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace lowpass_down {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst1;
	double fVec0[2];
	double fConst3;
	double fConst4;
	double fRec4[2];
	double fConst6;
	double fConst7;
	double fConst9;
	double fConst10;
	double fRec3[2];
	double fRec0[2];
	int iRec1[2];
	double fRec2[2];
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT	*fVbargraph0_;

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
	id = "lowpass_down";
	name = N_("lowpass_down");
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
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec4[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec3[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec0[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) iRec1[l4] = 0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec2[l5] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 1.0 / fConst0;
	double fConst2 = 1.0 / std::tan(17690.308232364125 / fConst0);
	fConst3 = 1.0 - fConst2;
	fConst4 = 1.0 / (fConst2 + 1.0);
	double fConst5 = std::tan(251.32741228718345 / fConst0);
	fConst6 = 1.0 / fConst5;
	fConst7 = 1.0 - fConst6;
	double fConst8 = fConst6 + 1.0;
	fConst9 = 1.0 / fConst8;
	fConst10 = 0.0 - 1.0 / (fConst5 * fConst8);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVbargraph0 (*fVbargraph0_)
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		int iTemp0 = iRec1[1] < 4096;
		double fTemp1 = double(input0[i0]);
		fVec0[0] = fTemp1;
		fRec4[0] = 0.0 - fConst4 * (fConst3 * fRec4[1] - (fTemp1 + fVec0[1]));
		fRec3[0] = fConst10 * fRec4[1] - fConst9 * (fConst7 * fRec3[1] - fConst6 * fRec4[0]);
		double fTemp2 = std::max<double>(fConst1, std::fabs(fRec3[0]));
		fRec0[0] = ((iTemp0) ? fTemp2 + fRec0[1] : fTemp2);
		iRec1[0] = ((iTemp0) ? iRec1[1] + 1 : 1);
		fRec2[0] = ((iTemp0) ? fRec2[1] : 0.000244140625 * fRec0[1]);
		fVbargraph0 = FAUSTFLOAT(fRec2[0]);
		output0[i0] = FAUSTFLOAT(fRec3[0]);
		fVec0[1] = fVec0[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec0[1] = fRec0[0];
		iRec1[1] = iRec1[0];
		fRec2[1] = fRec2[0];
	}
#undef fVbargraph0
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case V1: 
		fVbargraph0_ = (float*)data; // , 0, -7e+01, 5.0, 0 
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
   V1, 
} PortIndex;
*/

} // end namespace lowpass_down
