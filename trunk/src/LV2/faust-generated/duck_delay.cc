// generated from file '../src/LV2/faust/duck_delay.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace duck_delay {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	int IOTA;
	double fVec0[524288];
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	double fRec1[2];
	double fRec0[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT	*fHslider2_;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT	*fHslider3_;
	double fConst4;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT	*fHslider4_;
	double fRec4[2];
	double fRec3[2];
	double fRec2[2];

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
	id = "duckDelay";
	name = N_("Duck Delay");
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
	for (int l0 = 0; (l0 < 524288); l0 = (l0 + 1)) fVec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec1[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec0[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec4[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec3[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec2[l5] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = (0.001 * fConst0);
	fConst2 = std::exp((0.0 - (10.0 / fConst0)));
	fConst3 = (1.0 - fConst2);
	fConst4 = (1.0 / fConst0);
	IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fHslider0 (*fHslider0_)
#define fHslider1 (*fHslider1_)
#define fHslider2 (*fHslider2_)
#define fHslider3 (*fHslider3_)
#define fHslider4 (*fHslider4_)
	double fSlow0 = double(fHslider0);
	double fSlow1 = (fConst3 * double(fHslider1));
	double fSlow2 = std::pow(10.0, (0.050000000000000003 * double(fHslider2)));
	double fSlow3 = double(fHslider3);
	int iSlow4 = (std::fabs(fSlow3) < 2.2204460492503131e-16);
	double fSlow5 = (iSlow4 ? 0.0 : std::exp((0.0 - (fConst4 / (iSlow4 ? 1.0 : fSlow3)))));
	double fSlow6 = double(fHslider4);
	int iSlow7 = (std::fabs(fSlow6) < 2.2204460492503131e-16);
	double fSlow8 = (iSlow7 ? 0.0 : std::exp((0.0 - (fConst4 / (iSlow7 ? 1.0 : fSlow6)))));
	double fSlow9 = (1.0 - fSlow8);
	double fSlow10 = (1.0 - fSlow5);
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = double(input0[i]);
		double fTemp1 = (fTemp0 + (fSlow0 * fRec0[1]));
		fVec0[(IOTA & 524287)] = fTemp1;
		fRec1[0] = (fSlow1 + (fConst2 * fRec1[1]));
		double fTemp2 = (fConst1 * fRec1[0]);
		int iTemp3 = int(fTemp2);
		double fTemp4 = std::floor(fTemp2);
		fRec0[0] = ((fVec0[((IOTA - std::min<int>(393217, std::max<int>(0, iTemp3))) & 524287)] * (fTemp4 + (1.0 - fTemp2))) + ((fTemp2 - fTemp4) * fVec0[((IOTA - std::min<int>(393217, std::max<int>(0, (iTemp3 + 1)))) & 524287)]));
		double fTemp5 = std::fabs(fTemp0);
		fRec4[0] = std::max<double>(fTemp5, ((fRec4[1] * fSlow8) + (fTemp5 * fSlow9)));
		fRec3[0] = ((fRec3[1] * fSlow5) + (fRec4[0] * fSlow10));
		fRec2[0] = ((fConst2 * fRec2[1]) + (fConst3 * double((1 - ((fSlow2 * fRec3[0]) > 1.0)))));
		output0[i] = FAUSTFLOAT((fTemp0 + (fRec0[0] * fRec2[0])));
		IOTA = (IOTA + 1);
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
	}
#undef fHslider0
#undef fHslider1
#undef fHslider2
#undef fHslider3
#undef fHslider4
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case AMOUNT: 
		fHslider2_ = (float*)data; // , 0.5, 0.0, 56.0, 0.050000000000000003 
		break;
	case ATTACK: 
		fHslider3_ = (float*)data; // , 0.10000000000000001, 0.050000000000000003, 0.5, 0.050000000000000003 
		break;
	case FEEDBACK: 
		fHslider0_ = (float*)data; // , 0.0, 0.0, 1.0, 0.050000000000000003 
		break;
	case RELESE: 
		fHslider4_ = (float*)data; // , 0.10000000000000001, 0.050000000000000003, 2.0, 0.050000000000000003 
		break;
	case TIME: 
		fHslider1_ = (float*)data; // , 500.0, 1.0, 2000.0, 1.0 
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
   AMOUNT, 
   ATTACK, 
   FEEDBACK, 
   RELESE, 
   TIME, 
} PortIndex;
*/

} // end namespace duck_delay
