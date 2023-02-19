// generated from file '../src/LV2/faust/moog.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace moog {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	int iVec0[2];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	double fRec1[2];
	double fConst0;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	double fRec6[2];
	double fRec5[2];
	double fRec4[2];
	double fRec3[2];
	double fRec2[2];
	double fRec0[2];
	double fRec11[2];
	double fRec10[2];
	double fRec9[2];
	double fRec8[2];
	double fRec7[2];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "moog";
	name = N_("Moog Filter");
	mono_audio = 0;
	stereo_audio = compute_static;
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
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec1[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec6[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec5[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec4[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec3[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec2[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec0[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec11[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec10[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec9[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec8[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec7[l12] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = 6.283185307179586 / std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fHslider0 (*fHslider0_)
#define fHslider1 (*fHslider1_)
	double fSlow0 = 0.0010000000000000009 * double(fHslider0);
	double fSlow1 = double(fHslider1);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		iVec0[0] = 1;
		fRec1[0] = fSlow0 + 0.999 * fRec1[1];
		double fTemp0 = fConst0 * fRec1[0];
		double fTemp1 = mydsp_faustpower4_f(fTemp0);
		double fTemp2 = 1.0 - fTemp0;
		fRec6[0] = 1e-20 * double(1 - iVec0[1]) - fRec6[1];
		fRec5[0] = double(input0[i0]) + fRec6[0] + fTemp2 * fRec5[1] - fSlow1 * fRec0[1];
		fRec4[0] = fRec5[0] + fTemp2 * fRec4[1];
		fRec3[0] = fRec4[0] + fTemp2 * fRec3[1];
		fRec2[0] = fRec3[0] + fRec2[1] * fTemp2;
		fRec0[0] = fRec2[0] * fTemp1;
		output0[i0] = FAUSTFLOAT(fRec0[0]);
		fRec11[0] = double(input1[i0]) + fRec6[0] + fTemp2 * fRec11[1] - fSlow1 * fRec7[1];
		fRec10[0] = fRec11[0] + fTemp2 * fRec10[1];
		fRec9[0] = fRec10[0] + fTemp2 * fRec9[1];
		fRec8[0] = fRec9[0] + fTemp2 * fRec8[1];
		fRec7[0] = fRec8[0] * fTemp1;
		output1[i0] = FAUSTFLOAT(fRec7[0]);
		iVec0[1] = iVec0[0];
		fRec1[1] = fRec1[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec0[1] = fRec0[0];
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
	}
#undef fHslider0
#undef fHslider1
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case Q: 
		fHslider1_ = (float*)data; // , 1.0, 0.0, 4.0, 0.1 
		break;
	case FR: 
		fHslider0_ = (float*)data; // , 3e+03, 4.4e+02, 6e+03, 1e+01 
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
   Q, 
   FR, 
} PortIndex;
*/

} // end namespace moog
