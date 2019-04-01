// generated from file '../src/LV2/faust/delay.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace delay {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	float fRec0[2];
	float fConst0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	int IOTA;
	float *fVec0;

	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void connect(uint32_t port,void* data);
	void clear_state_f();
	int activate(bool start);
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static int activate_static(bool start, PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec0[l0] = 0.0f;
	for (int l1 = 0; (l1 < 524288); l1 = (l1 + 1)) fVec0[l1] = 0.0f;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (0.00100000005f * std::min<float>(192000.0f, std::max<float>(1.0f, float(fSamplingFreq))));
	fVslider0 = FAUSTFLOAT(0.0f);
	fVslider1 = FAUSTFLOAT(0.0f);
			IOTA = 0;
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
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
	float fSlow0 = (0.00100000005f * std::pow(10.0f, (0.0500000007f * float(fVslider0))));
	float fSlow1 = (fConst0 * float(fVslider1));
	float fSlow2 = std::floor(fSlow1);
	float fSlow3 = (fSlow2 + (1.0f - fSlow1));
	int iSlow4 = int(fSlow1);
	int iSlow5 = std::min<int>(262145, std::max<int>(0, iSlow4));
	float fSlow6 = (fSlow1 - fSlow2);
	int iSlow7 = std::min<int>(262145, std::max<int>(0, (iSlow4 + 1)));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec0[0] = (fSlow0 + (0.999000013f * fRec0[1]));
		float fTemp0 = float(input0[i]);
		fVec0[(IOTA & 524287)] = fTemp0;
		output0[i] = FAUSTFLOAT(((fRec0[0] * ((fSlow3 * fVec0[((IOTA - iSlow5) & 524287)]) + (fSlow6 * fVec0[((IOTA - iSlow7) & 524287)]))) + fTemp0));
		fRec0[1] = fRec0[0];
		IOTA = (IOTA + 1);
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
		fVslider1_ = (float*)data; // , 0.0f, 0.0f, 5000.0f, 10.0f 
		break;
	case GAIN: 
		fVslider0_ = (float*)data; // , 0.0f, -20.0f, 20.0f, 0.100000001f 
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
