// generated from file '../src/LV2/faust/chorus.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace chorus {
class mydspSIG0 {
	
  private:
	
	int iRec1[2];
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
		
	}
	int getNumOutputsmydspSIG0() {
		return 1;
		
	}
	int getInputRatemydspSIG0(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	int getOutputRatemydspSIG0(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 0;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	void instanceInitmydspSIG0(int samplingFreq) {
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			iRec1[l2] = 0;
			
		}
		
	}
	
	void fillmydspSIG0(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec1[0] = (iRec1[1] + 1);
			output[i] = std::sin((9.58738019e-05f * float((iRec1[0] + -1))));
			iRec1[1] = iRec1[0];
			
		}
		
	}

};

mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static float ftbl0mydspSIG0[65536];


class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	int IOTA;
	float *fVec0;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT	*fHslider2_;
	float fConst2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT	*fHslider3_;
	float fRec0[2];
	float *fVec1;

	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void connect(uint32_t port,void* data);
	void clear_state_f();
	int activate(bool start);
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);

	static void clear_state_f_static(PluginLV2*);
	static int activate_static(bool start, PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2(),
	  fVec0(0),
	  fVec1(0),
	  mem_allocated(false) {
	version = PLUGINLV2_VERSION;
	id = "chorus";
	name = N_("Chorus");
	mono_audio = 0;
	stereo_audio = compute_static;
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
	for (int l0 = 0; (l0 < 131072); l0 = (l0 + 1)) fVec0[l0] = 0.0f;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec0[l1] = 0.0f;
	for (int l3 = 0; (l3 < 131072); l3 = (l3 + 1)) fVec1[l3] = 0.0f;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	mydspSIG0* sig0 = newmydspSIG0();
	sig0->instanceInitmydspSIG0(samplingFreq);
	sig0->fillmydspSIG0(65536, ftbl0mydspSIG0);
	deletemydspSIG0(sig0);
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSamplingFreq)));
	fConst1 = (0.5f * fConst0);
	fConst2 = (1.0f / fConst0);
	fHslider0 = FAUSTFLOAT(0.5f);
	fHslider1 = FAUSTFLOAT(0.02f);
	fHslider2 = FAUSTFLOAT(0.02f);
	fHslider3 = FAUSTFLOAT(3.0f);
			IOTA = 0;
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void Dsp::mem_alloc()
{
	if (!fVec0) fVec0 = new float[131072];
	if (!fVec1) fVec1 = new float[131072];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec0) { delete fVec0; fVec0 = 0; }
	if (fVec1) { delete fVec1; fVec1 = 0; }
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

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fHslider0 (*fHslider0_)
#define fHslider1 (*fHslider1_)
#define fHslider2 (*fHslider2_)
#define fHslider3 (*fHslider3_)
	float fSlow0 = float(fHslider0);
	float fSlow1 = (fConst1 * float(fHslider1));
	float fSlow2 = float(fHslider2);
	float fSlow3 = (fConst2 * float(fHslider3));
	for (int i = 0; (i < count); i = (i + 1)) {
		float fTemp0 = float(input0[i]);
		fVec0[(IOTA & 131071)] = fTemp0;
		fRec0[0] = (fSlow3 + (fRec0[1] - std::floor((fSlow3 + fRec0[1]))));
		float fTemp1 = (65536.0f * (fRec0[0] - std::floor(fRec0[0])));
		float fTemp2 = std::floor(fTemp1);
		int iTemp3 = int(fTemp2);
		float fTemp4 = (fSlow1 * ((fSlow2 * (((fTemp2 + (1.0f - fTemp1)) * ftbl0mydspSIG0[(iTemp3 & 65535)]) + ((fTemp1 - fTemp2) * ftbl0mydspSIG0[((iTemp3 + 1) & 65535)]))) + 1.0f));
		int iTemp5 = int(fTemp4);
		float fTemp6 = std::floor(fTemp4);
		output0[i] = FAUSTFLOAT(((fSlow0 * ((fVec0[((IOTA - std::min<int>(65537, std::max<int>(0, iTemp5))) & 131071)] * (fTemp6 + (1.0f - fTemp4))) + ((fTemp4 - fTemp6) * fVec0[((IOTA - std::min<int>(65537, std::max<int>(0, (iTemp5 + 1)))) & 131071)]))) + fTemp0));
		float fTemp7 = float(input1[i]);
		fVec1[(IOTA & 131071)] = fTemp7;
		float fTemp8 = (65536.0f * (fRec0[0] + (0.25f - std::floor((fRec0[0] + 0.25f)))));
		float fTemp9 = std::floor(fTemp8);
		int iTemp10 = int(fTemp9);
		float fTemp11 = (fSlow1 * ((fSlow2 * (((fTemp9 + (1.0f - fTemp8)) * ftbl0mydspSIG0[(iTemp10 & 65535)]) + ((fTemp8 - fTemp9) * ftbl0mydspSIG0[((iTemp10 + 1) & 65535)]))) + 1.0f));
		int iTemp12 = int(fTemp11);
		float fTemp13 = std::floor(fTemp11);
		output1[i] = FAUSTFLOAT(((fSlow0 * ((fVec1[((IOTA - std::min<int>(65537, std::max<int>(0, iTemp12))) & 131071)] * (fTemp13 + (1.0f - fTemp11))) + ((fTemp11 - fTemp13) * fVec1[((IOTA - std::min<int>(65537, std::max<int>(0, (iTemp12 + 1)))) & 131071)]))) + fTemp7));
		IOTA = (IOTA + 1);
		fRec0[1] = fRec0[0];
	}
#undef fHslider0
#undef fHslider1
#undef fHslider2
#undef fHslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case DELAY: 
		fHslider1_ = (float*)data; // , 0.0199999996f, 0.0f, 0.200000003f, 0.00999999978f 
		break;
	case DEPTH: 
		fHslider2_ = (float*)data; // , 0.0199999996f, 0.0f, 1.0f, 0.00999999978f 
		break;
	case FREQ: 
		fHslider3_ = (float*)data; // , 3.0f, 0.0f, 10.0f, 0.00999999978f 
		break;
	case LEVEL: 
		fHslider0_ = (float*)data; // , 0.5f, 0.0f, 1.0f, 0.00999999978f 
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
   DEPTH, 
   FREQ, 
   LEVEL, 
} PortIndex;
*/

} // end namespace chorus
