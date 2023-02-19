// generated from file '../src/LV2/faust/tonestack_default.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace tonestack_default {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fVec0[3];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst2;
	double fConst3;
	double fRec3[3];
	double fConst5;
	double fConst6;
	double fRec2[3];
	double fRec1[3];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
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
	id = "default";
	name = N_("default");
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
	for (int l0 = 0; l0 < 3; l0 = l0 + 1) fVec0[l0] = 0.0;
	for (int l1 = 0; l1 < 3; l1 = l1 + 1) fRec3[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRec2[l2] = 0.0;
	for (int l3 = 0; l3 < 3; l3 = l3 + 1) fRec1[l3] = 0.0;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRec0[l4] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 3769.9111843077517 / fConst0;
	fConst2 = 1.4142135623730951 * std::sin(fConst1);
	fConst3 = std::cos(fConst1);
	double fConst4 = 15079.644737231007 / fConst0;
	fConst5 = 1.4142135623730951 * std::sin(fConst4);
	fConst6 = std::cos(fConst4);
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
#define fVslider2 (*fVslider2_)
	double fSlow0 = double(fVslider0) + -0.5;
	double fSlow1 = 1e+01 * fSlow0;
	double fSlow2 = std::pow(1e+01, 0.025 * (2e+01 * (std::exp(3.4 * (double(fVslider1) + -1.0)) + -0.5) - fSlow1));
	double fSlow3 = fConst2 * std::sqrt(fSlow2);
	double fSlow4 = fConst3 * (fSlow2 + -1.0);
	double fSlow5 = fSlow2 + (1.0 - (fSlow4 + fSlow3));
	double fSlow6 = fConst3 * (fSlow2 + 1.0);
	double fSlow7 = 2.0 * (fSlow2 + (-1.0 - fSlow6));
	double fSlow8 = fSlow2 + fSlow3 + (1.0 - fSlow4);
	double fSlow9 = fSlow2 + fSlow4;
	double fSlow10 = fSlow9 + (1.0 - fSlow3);
	double fSlow11 = 0.0 - 2.0 * (fSlow2 + fSlow6 + -1.0);
	double fSlow12 = 1.0 / (fSlow9 + fSlow3 + 1.0);
	double fSlow13 = std::pow(1e+01, 0.25 * fSlow0);
	double fSlow14 = std::sqrt(fSlow13);
	double fSlow15 = fConst5 * fSlow14;
	double fSlow16 = fSlow13 + -1.0;
	double fSlow17 = fConst6 * fSlow16;
	double fSlow18 = fSlow13 + (1.0 - (fSlow17 + fSlow15));
	double fSlow19 = fSlow13 + 1.0;
	double fSlow20 = fConst6 * fSlow19;
	double fSlow21 = 2.0 * (fSlow13 + (-1.0 - fSlow20));
	double fSlow22 = fSlow13 + fSlow15 + (1.0 - fSlow17);
	double fSlow23 = fSlow13 + fSlow17;
	double fSlow24 = fSlow23 + (1.0 - fSlow15);
	double fSlow25 = 0.0 - 2.0 * (fSlow13 + fSlow20 + -1.0);
	double fSlow26 = 1.0 / (fSlow23 + fSlow15 + 1.0);
	double fSlow27 = fConst2 * fSlow14;
	double fSlow28 = fConst3 * fSlow16;
	double fSlow29 = fSlow13 + fSlow28;
	double fSlow30 = fSlow13 * (fSlow29 + (1.0 - fSlow27));
	double fSlow31 = fConst3 * fSlow19;
	double fSlow32 = (0.0 - 2.0 * fSlow13) * (fSlow13 + fSlow31 + -1.0);
	double fSlow33 = fSlow13 * (fSlow27 + fSlow29 + 1.0);
	double fSlow34 = 2.0 * (fSlow13 + (-1.0 - fSlow31));
	double fSlow35 = fSlow13 + (1.0 - (fSlow28 + fSlow27));
	double fSlow36 = 1.0 / (fSlow13 + fSlow27 + (1.0 - fSlow28));
	double fSlow37 = std::pow(1e+01, 0.025 * (2e+01 * (double(fVslider2) + -0.5) - fSlow1));
	double fSlow38 = fConst5 * std::sqrt(fSlow37);
	double fSlow39 = fConst6 * (fSlow37 + -1.0);
	double fSlow40 = fSlow37 + fSlow39;
	double fSlow41 = fSlow37 * (fSlow40 + (1.0 - fSlow38));
	double fSlow42 = fConst6 * (fSlow37 + 1.0);
	double fSlow43 = (0.0 - 2.0 * fSlow37) * (fSlow37 + fSlow42 + -1.0);
	double fSlow44 = fSlow37 * (fSlow38 + fSlow40 + 1.0);
	double fSlow45 = 2.0 * (fSlow37 + (-1.0 - fSlow42));
	double fSlow46 = fSlow37 + (1.0 - (fSlow39 + fSlow38));
	double fSlow47 = 1.0 / (fSlow37 + fSlow38 + (1.0 - fSlow39));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		fVec0[0] = fTemp0;
		fRec3[0] = 0.0 - fSlow12 * (fSlow11 * fRec3[1] + fSlow10 * fRec3[2] - fSlow2 * (fSlow8 * fTemp0 + fSlow7 * fVec0[1] + fSlow5 * fVec0[2]));
		fRec2[0] = 0.0 - fSlow26 * (fSlow25 * fRec2[1] + fSlow24 * fRec2[2] - fSlow13 * (fSlow22 * fRec3[0] + fSlow21 * fRec3[1] + fSlow18 * fRec3[2]));
		fRec1[0] = fSlow36 * (0.0 - (fSlow35 * fRec1[2] + fSlow34 * fRec1[1]) + fSlow33 * fRec2[0] + fSlow32 * fRec2[1] + fSlow30 * fRec2[2]);
		fRec0[0] = fSlow47 * (0.0 - (fSlow46 * fRec0[2] + fSlow45 * fRec0[1]) + fSlow44 * fRec1[0] + fSlow43 * fRec1[1] + fSlow41 * fRec1[2]);
		output0[i0] = FAUSTFLOAT(fRec0[0]);
		fVec0[2] = fVec0[1];
		fVec0[1] = fVec0[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case BASS: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case MIDDLE: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TREBLE: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   BASS, 
   MIDDLE, 
   TREBLE, 
} PortIndex;
*/

} // end namespace tonestack_default
