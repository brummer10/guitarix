// generated from file '../src/LV2/faust/chorus_mono.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace chorus_mono {
class mydspSIG0 {
	
  private:
	
	int iRec4[2];
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
	}
	int getNumOutputsmydspSIG0() {
		return 1;
	}
	
	void instanceInitmydspSIG0(int sample_rate) {
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			iRec4[l1] = 0;
		}
	}
	
	void fillmydspSIG0(int count, double* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iRec4[0] = iRec4[1] + 1;
			table[i1] = std::sin(9.587379924285257e-05 * double(iRec4[0] + -1));
			iRec4[1] = iRec4[0];
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
	int IOTA0;
	double fVec0[131072];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	double fConst1;
	double fRec5[2];
	double fConst2;
	double fConst3;
	double fConst4;
	double fRec0[2];
	double fRec1[2];
	double fRec2[2];
	double fRec3[2];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	double fRec6[2];

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
	for (int l0 = 0; l0 < 131072; l0 = l0 + 1) fVec0[l0] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec5[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec0[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec1[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec2[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec3[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec6[l7] = 0.0;
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
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 1.0 / fConst0;
	fConst2 = 0.01 * fConst0;
	fConst3 = 1e+03 / fConst0;
	fConst4 = 0.0 - fConst3;
	IOTA0 = 0;
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
	double fSlow0 = 0.01 * double(fVslider0);
	double fSlow1 = fSlow0 + (1.0 - fSlow0);
	double fSlow2 = fConst1 * double(fHslider0);
	double fSlow3 = 0.007000000000000006 * double(fHslider1);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		double fTemp1 = fSlow0 * fTemp0;
		fVec0[IOTA0 & 131071] = fTemp1;
		fRec5[0] = fSlow2 + (fRec5[1] - std::floor(fSlow2 + fRec5[1]));
		double fTemp2 = 65536.0 * (fRec5[0] - std::floor(fRec5[0]));
		double fTemp3 = std::floor(fTemp2);
		int iTemp4 = int(fTemp3);
		double fTemp5 = fConst2 * (0.02 * ((fTemp3 + (1.0 - fTemp2)) * ftbl0mydspSIG0[iTemp4 & 65535] + (fTemp2 - fTemp3) * ftbl0mydspSIG0[(iTemp4 + 1) & 65535]) + 1.0);
		double fTemp6 = ((fRec0[1] != 0.0) ? (((fRec1[1] > 0.0) & (fRec1[1] < 1.0)) ? fRec0[1] : 0.0) : (((fRec1[1] == 0.0) & (fTemp5 != fRec2[1])) ? fConst3 : (((fRec1[1] == 1.0) & (fTemp5 != fRec3[1])) ? fConst4 : 0.0)));
		fRec0[0] = fTemp6;
		fRec1[0] = std::max<double>(0.0, std::min<double>(1.0, fRec1[1] + fTemp6));
		fRec2[0] = (((fRec1[1] >= 1.0) & (fRec3[1] != fTemp5)) ? fTemp5 : fRec2[1]);
		fRec3[0] = (((fRec1[1] <= 0.0) & (fRec2[1] != fTemp5)) ? fTemp5 : fRec3[1]);
		double fTemp7 = fVec0[(IOTA0 - int(std::min<double>(65536.0, std::max<double>(0.0, fRec2[0])))) & 131071];
		fRec6[0] = fSlow3 + 0.993 * fRec6[1];
		output0[i0] = FAUSTFLOAT(fRec6[0] * (fTemp7 + fRec1[0] * (fVec0[(IOTA0 - int(std::min<double>(65536.0, std::max<double>(0.0, fRec3[0])))) & 131071] - fTemp7)) + fSlow1 * fTemp0);
		IOTA0 = IOTA0 + 1;
		fRec5[1] = fRec5[0];
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec6[1] = fRec6[0];
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
	case FREQ: 
		fHslider0_ = (float*)data; // , 2.0, 0.0, 1e+01, 0.01 
		break;
	case LEVEL: 
		fHslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case WET_DRY: 
		fVslider0_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
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
