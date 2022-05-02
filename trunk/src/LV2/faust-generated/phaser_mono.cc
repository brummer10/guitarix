// generated from file '../src/LV2/faust/phaser_mono.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace phaser_mono {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	float fConst2;
	float fConst3;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	int iVec0[2];
	float fConst4;
	float fConst5;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	float fRec5[2];
	float fRec6[2];
	float fRec4[3];
	float fConst6;
	float fRec3[3];
	float fConst7;
	float fRec2[3];
	float fConst8;
	float fRec1[3];
	float fRec0[2];

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
	id = "phaser_mono";
	name = N_("Phaser Mono");
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
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec5[l1] = 0.0f;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec6[l2] = 0.0f;
	for (int l3 = 0; l3 < 3; l3 = l3 + 1) fRec4[l3] = 0.0f;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRec3[l4] = 0.0f;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec2[l5] = 0.0f;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec1[l6] = 0.0f;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec0[l7] = 0.0f;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	float fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
	float fConst1 = std::exp(0.0f - 3141.59277f / fConst0);
	fConst2 = mydsp_faustpower2_f(fConst1);
	fConst3 = 0.0f - 2.0f * fConst1;
	fConst4 = 2.0f / fConst0;
	fConst5 = 6.28318548f / fConst0;
	fConst6 = 4.0f / fConst0;
	fConst7 = 8.0f / fConst0;
	fConst8 = 16.0f / fConst0;
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fHslider0 (*fHslider0_)
#define fHslider1 (*fHslider1_)
	float fSlow0 = float(fVslider0);
	float fSlow1 = 1.0f - 0.00999999978f * fSlow0;
	float fSlow2 = 0.00999999978f * fSlow0 * std::pow(10.0f, 0.0500000007f * float(fHslider0));
	float fSlow3 = fConst5 * float(fHslider1);
	float fSlow4 = std::sin(fSlow3);
	float fSlow5 = std::cos(fSlow3);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		float fTemp0 = float(input0[i0]);
		iVec0[0] = 1;
		fRec5[0] = fSlow4 * fRec6[1] + fSlow5 * fRec5[1];
		fRec6[0] = (float(1 - iVec0[1]) + fSlow5 * fRec6[1]) - fSlow4 * fRec5[1];
		float fTemp1 = 2199.11475f * (1.0f - fRec5[0]) + 628.318542f;
		float fTemp2 = fRec4[1] * std::cos(fConst4 * fTemp1);
		fRec4[0] = (fSlow2 * fTemp0 + 0.5f * fRec0[1]) - (fConst3 * fTemp2 + fConst2 * fRec4[2]);
		float fTemp3 = fRec3[1] * std::cos(fConst6 * fTemp1);
		fRec3[0] = fConst3 * (fTemp2 - fTemp3) + fRec4[2] + fConst2 * (fRec4[0] - fRec3[2]);
		float fTemp4 = fRec2[1] * std::cos(fConst7 * fTemp1);
		fRec2[0] = fConst3 * (fTemp3 - fTemp4) + fRec3[2] + fConst2 * (fRec3[0] - fRec2[2]);
		float fTemp5 = fRec1[1] * std::cos(fConst8 * fTemp1);
		fRec1[0] = fConst3 * (fTemp4 - fTemp5) + fRec2[2] + fConst2 * (fRec2[0] - fRec1[2]);
		fRec0[0] = fConst2 * fRec1[0] + fConst3 * fTemp5 + fRec1[2];
		output0[i0] = FAUSTFLOAT(fSlow1 * fTemp0 - fRec0[0]);
		iVec0[1] = iVec0[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
#undef fVslider0
#undef fHslider0
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
	case SPEED: 
		fHslider1_ = (float*)data; // , 0.5f, 0.0f, 10.0f, 0.00999999978f 
		break;
	case LEVEL: 
		fHslider0_ = (float*)data; // , 0.0f, -60.0f, 10.0f, 0.100000001f 
		break;
	case WET_DRY: 
		fVslider0_ = (float*)data; // , 100.0f, 0.0f, 100.0f, 1.0f 
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
   SPEED, 
   LEVEL, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace phaser_mono
