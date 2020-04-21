// generated from file '../src/LV2/faust/switched_tremolo.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace switched_tremolo {
class mydspSIG0 {
	
  private:
	
	int iRec2[2];
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
	}
	int getNumOutputsmydspSIG0() {
		return 1;
	}
	int getInputRatemydspSIG0(int channel) {
		int rate;
		switch ((channel)) {
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	int getOutputRatemydspSIG0(int channel) {
		int rate;
		switch ((channel)) {
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
	
	void instanceInitmydspSIG0(int sample_rate) {
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			iRec2[l3] = 0;
		}
	}
	
	void fillmydspSIG0(int count, double* table) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec2[0] = (iRec2[1] + 1);
			table[i] = std::sin((9.5873799242852573e-05 * double((iRec2[0] + -1))));
			iRec2[1] = iRec2[0];
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static double ftbl0mydspSIG0[65536];


class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	double fVec0[2];
	double fRec1[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT	*fHslider2_;
	double fRec0[2];
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT	*fHslider3_;
	double fRec3[2];
	double fRec4[2];
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT	*fHslider4_;
	double fRec5[2];
	double fRec6[2];
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT	*fHslider5_;
	double fRec7[2];
	double fRec8[2];
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT	*fHslider6_;
	double fRec9[2];

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
	id = "switched_tremolo";
	name = N_("switched_tremolo");
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fVec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec1[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec0[l2] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec3[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec4[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec5[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec6[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec7[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec8[l9] = 0.0;
	for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) fRec9[l10] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	mydspSIG0* sig0 = newmydspSIG0();
	sig0->instanceInitmydspSIG0(sample_rate);
	sig0->fillmydspSIG0(65536, ftbl0mydspSIG0);
	deletemydspSIG0(sig0);
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = std::exp((0.0 - (20.0 / fConst0)));
	fConst2 = (1.0 - fConst1);
	fConst3 = (1.0 / fConst0);
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
#define fHslider2 (*fHslider2_)
#define fHslider3 (*fHslider3_)
#define fHslider4 (*fHslider4_)
#define fHslider5 (*fHslider5_)
#define fHslider6 (*fHslider6_)
	double fSlow0 = (0.01 * double(fVslider0));
	double fSlow1 = (1.0 - fSlow0);
	double fSlow2 = double(fHslider0);
	double fSlow3 = double(fHslider1);
	double fSlow4 = double(fHslider2);
	double fSlow5 = (1.0 / fSlow4);
	double fSlow6 = (fConst3 * double(fHslider3));
	double fSlow7 = (2.0 / fSlow4);
	double fSlow8 = (fConst3 * double(fHslider4));
	double fSlow9 = (3.0 / fSlow4);
	double fSlow10 = (fConst3 * double(fHslider5));
	double fSlow11 = (4.0 / fSlow4);
	double fSlow12 = (fConst3 * double(fHslider6));
	for (int i = 0; (i < count); i = (i + 1)) {
		fVec0[0] = fSlow3;
		double fTemp0 = (fRec1[1] + (fConst3 * fVec0[1]));
		fRec1[0] = (fTemp0 - std::floor(fTemp0));
		fRec0[0] = ((fConst1 * fRec0[1]) + (fConst2 * double(((fRec1[0] <= fSlow5) * (fRec1[0] > 0.0)))));
		fRec3[0] = (fSlow6 + (fRec3[1] - std::floor((fSlow6 + fRec3[1]))));
		fRec4[0] = ((fConst1 * fRec4[1]) + (fConst2 * double(((fRec1[0] <= fSlow7) * (fRec1[0] > fSlow5)))));
		fRec5[0] = (fSlow8 + (fRec5[1] - std::floor((fSlow8 + fRec5[1]))));
		fRec6[0] = ((fConst1 * fRec6[1]) + (fConst2 * double(((fRec1[0] <= fSlow9) * (fRec1[0] > fSlow7)))));
		fRec7[0] = (fSlow10 + (fRec7[1] - std::floor((fSlow10 + fRec7[1]))));
		fRec8[0] = ((fConst1 * fRec8[1]) + (fConst2 * double(((fRec1[0] <= fSlow11) * (fRec1[0] > fSlow9)))));
		fRec9[0] = (fSlow12 + (fRec9[1] - std::floor((fSlow12 + fRec9[1]))));
		output0[i] = FAUSTFLOAT((double(input0[i]) * (fSlow1 + (fSlow0 * ((fSlow2 * (((((fRec0[0] * ftbl0mydspSIG0[int((65536.0 * fRec3[0]))]) + (fRec4[0] * ftbl0mydspSIG0[int((65536.0 * fRec5[0]))])) + (fRec6[0] * ftbl0mydspSIG0[int((65536.0 * fRec7[0]))])) + (fRec8[0] * ftbl0mydspSIG0[int((65536.0 * fRec9[0]))])) + -1.0)) + 1.0)))));
		fVec0[1] = fVec0[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
	}
#undef fVslider0
#undef fHslider0
#undef fHslider1
#undef fHslider2
#undef fHslider3
#undef fHslider4
#undef fHslider5
#undef fHslider6
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case DEPTH: 
		fHslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.050000000000000003 
		break;
	case FREQ0: 
		fHslider3_ = (float*)data; // , 1.0, 0.25, 15.0, 0.5 
		break;
	case FREQ1: 
		fHslider4_ = (float*)data; // , 1.0, 0.25, 15.0, 0.5 
		break;
	case FREQ2: 
		fHslider5_ = (float*)data; // , 1.0, 0.25, 15.0, 0.5 
		break;
	case FREQ3: 
		fHslider6_ = (float*)data; // , 1.0, 0.25, 15.0, 0.5 
		break;
	case STEPS: 
		fHslider2_ = (float*)data; // , 4.0, 1.0, 4.0, 1.0 
		break;
	case SWITCHFREQ: 
		fHslider1_ = (float*)data; // , 1.0, 0.25, 5.0, 0.25 
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
   DEPTH, 
   FREQ0, 
   FREQ1, 
   FREQ2, 
   FREQ3, 
   STEPS, 
   SWITCHFREQ, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace switched_tremolo
