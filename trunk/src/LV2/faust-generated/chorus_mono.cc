// generated from file '../src/LV2/faust/chorus_mono.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace chorus_mono {
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
	
	void fillmydspSIG0(int count, double* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec1[0] = (iRec1[1] + 1);
			output[i] = std::sin((9.5873799242852573e-05 * double((iRec1[0] + -1))));
			iRec1[1] = iRec1[0];
			
		}
		
	}

};

mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static double ftbl0mydspSIG0[65536];


class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	int IOTA;
	double fVec0[131072];
	double fConst0;
	double fConst1;
	double fConst2;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	double fRec0[2];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
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
	id = "chorus_mono";
	name = N_("Chorus Mono");
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
	for (int l0 = 0; (l0 < 131072); l0 = (l0 + 1)) fVec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec0[l1] = 0.0;
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
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = (0.01 * fConst0);
	fConst2 = (1.0 / fConst0);
	fHslider0 = FAUSTFLOAT(0.5);
	fVslider0 = FAUSTFLOAT(100.0);
	fHslider1 = FAUSTFLOAT(2.0);
			IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fHslider0 (*fHslider0_)
#define fVslider0 (*fVslider0_)
#define fHslider1 (*fHslider1_)
	double fSlow0 = double(fHslider0);
	double fSlow1 = (0.01 * double(fVslider0));
	double fSlow2 = (fConst2 * double(fHslider1));
	double fSlow3 = (fSlow1 + (1.0 - fSlow1));
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = double(input0[i]);
		double fTemp1 = (fSlow1 * fTemp0);
		fVec0[(IOTA & 131071)] = fTemp1;
		fRec0[0] = (fSlow2 + (fRec0[1] - std::floor((fSlow2 + fRec0[1]))));
		double fTemp2 = (65536.0 * (fRec0[0] - std::floor(fRec0[0])));
		double fTemp3 = std::floor(fTemp2);
		int iTemp4 = int(fTemp3);
		double fTemp5 = (fConst1 * ((0.02 * (((fTemp3 + (1.0 - fTemp2)) * ftbl0mydspSIG0[(iTemp4 & 65535)]) + ((fTemp2 - fTemp3) * ftbl0mydspSIG0[((iTemp4 + 1) & 65535)]))) + 1.0));
		int iTemp6 = int(fTemp5);
		double fTemp7 = std::floor(fTemp5);
		output0[i] = FAUSTFLOAT(((fSlow0 * ((fVec0[((IOTA - std::min<int>(65537, std::max<int>(0, iTemp6))) & 131071)] * (fTemp7 + (1.0 - fTemp5))) + ((fTemp5 - fTemp7) * fVec0[((IOTA - std::min<int>(65537, std::max<int>(0, (iTemp6 + 1)))) & 131071)]))) + (fSlow3 * fTemp0)));
		IOTA = (IOTA + 1);
		fRec0[1] = fRec0[0];
	}
#undef fHslider0
#undef fVslider0
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
	case FREQ: 
		fHslider1_ = (float*)data; // , 2.0, 0.0, 10.0, 0.01 
		break;
	case LEVEL: 
		fHslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fVslider0_ = (float*)data; // , 100.0, 0.0, 100.0, 1.0 
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
   FREQ, 
   LEVEL, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace chorus_mono
