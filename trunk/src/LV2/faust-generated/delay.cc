// generated from file '../src/LV2/faust/delay.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace delay {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	int IOTA0;
	float *fVec0;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	float fConst0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	float fRec0[2];

	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void connect(uint32_t port,void* data);
	void clear_state_f();
	int activate(bool start);
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static int activate_static(bool start, PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2(),
	  fVec0(0),
	  mem_allocated(false) {
	version = PLUGINLV2_VERSION;
	id = "delay";
	name = N_("Delay");
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = activate_static;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; l0 < 524288; l0 = l0 + 1) fVec0[l0] = 0.0f;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec0[l1] = 0.0f;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = 0.001f * std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
	IOTA0 = 0;
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void Dsp::mem_alloc()
{
	if (!fVec0) fVec0 = new float[524288];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec0) { delete fVec0; fVec0 = 0; }
}

int Dsp::activate(bool start)
{
	if (start) {
		if (!mem_allocated) {
			mem_alloc();
			clear_state_f();
		}
	} else if (mem_allocated) {
		mem_free();
	}
	return 0;
}

int Dsp::activate_static(bool start, PluginLV2 *p)
{
	return static_cast<Dsp*>(p)->activate(start);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
	float fSlow0 = fConst0 * float(fVslider0);
	int iSlow1 = int(fSlow0);
	int iSlow2 = std::min<int>(262145, std::max<int>(0, iSlow1 + 1));
	float fSlow3 = std::floor(fSlow0);
	float fSlow4 = fSlow0 - fSlow3;
	int iSlow5 = std::min<int>(262145, std::max<int>(0, iSlow1));
	float fSlow6 = fSlow3 + (1.0f - fSlow0);
	float fSlow7 = 0.001f * std::pow(1e+01f, 0.05f * float(fVslider1));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		float fTemp0 = float(input0[i0]);
		fVec0[IOTA0 & 524287] = fTemp0;
		fRec0[0] = fSlow7 + 0.999f * fRec0[1];
		output0[i0] = FAUSTFLOAT(fTemp0 + fRec0[0] * (fSlow6 * fVec0[(IOTA0 - iSlow5) & 524287] + fSlow4 * fVec0[(IOTA0 - iSlow2) & 524287]));
		IOTA0 = IOTA0 + 1;
		fRec0[1] = fRec0[0];
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
	case DELAY: 
		fVslider0_ = (float*)data; // , 0.0f, 0.0f, 5e+03f, 1e+01f 
		break;
	case GAIN: 
		fVslider1_ = (float*)data; // , 0.0f, -2e+01f, 2e+01f, 0.1f 
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
   DELAY, 
   GAIN, 
} PortIndex;
*/

} // end namespace delay
