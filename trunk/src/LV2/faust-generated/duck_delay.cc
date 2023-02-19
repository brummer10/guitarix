// generated from file '../src/LV2/faust/duck_delay.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace duck_delay {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst1;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	double fConst2;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	double fRec2[2];
	double fRec1[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT	*fHslider2_;
	double fConst3;
	double fRec0[2];
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT	*fHslider3_;
	int IOTA0;
	double fVec0[524288];
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT	*fHslider4_;
	double fRec4[2];
	double fConst4;
	double fRec3[2];

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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec2[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec1[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec0[l2] = 0.0;
	for (int l3 = 0; l3 < 524288; l3 = l3 + 1) fVec0[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec4[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec3[l5] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = std::exp(0.0 - 1e+01 / fConst0);
	fConst2 = 1.0 / fConst0;
	fConst3 = 1.0 - fConst1;
	fConst4 = 0.001 * fConst0;
	IOTA0 = 0;
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
	int iSlow1 = std::fabs(fSlow0) < 2.220446049250313e-16;
	double fSlow2 = ((iSlow1) ? 0.0 : std::exp(0.0 - fConst2 / ((iSlow1) ? 1.0 : fSlow0)));
	double fSlow3 = 1.0 - fSlow2;
	double fSlow4 = double(fHslider1);
	int iSlow5 = std::fabs(fSlow4) < 2.220446049250313e-16;
	double fSlow6 = ((iSlow5) ? 0.0 : std::exp(0.0 - fConst2 / ((iSlow5) ? 1.0 : fSlow4)));
	double fSlow7 = 1.0 - fSlow6;
	double fSlow8 = std::pow(1e+01, 0.05 * double(fHslider2));
	double fSlow9 = double(fHslider3);
	double fSlow10 = fConst3 * double(fHslider4);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		double fTemp1 = std::fabs(fTemp0);
		fRec2[0] = std::max<double>(fTemp1, fRec2[1] * fSlow6 + fTemp1 * fSlow7);
		fRec1[0] = fRec2[0] * fSlow3 + fSlow2 * fRec1[1];
		fRec0[0] = fConst3 * double(1 - ((fSlow8 * fRec1[0]) > 1.0)) + fConst1 * fRec0[1];
		double fTemp2 = fTemp0 + fSlow9 * fRec3[1];
		fVec0[IOTA0 & 524287] = fTemp2;
		fRec4[0] = fSlow10 + fConst1 * fRec4[1];
		double fTemp3 = fConst4 * fRec4[0];
		int iTemp4 = int(fTemp3);
		double fTemp5 = std::floor(fTemp3);
		fRec3[0] = fVec0[(IOTA0 - std::min<int>(393217, std::max<int>(0, iTemp4))) & 524287] * (fTemp5 + (1.0 - fTemp3)) + (fTemp3 - fTemp5) * fVec0[(IOTA0 - std::min<int>(393217, std::max<int>(0, iTemp4 + 1))) & 524287];
		output0[i0] = FAUSTFLOAT(fTemp0 + fRec3[0] * fRec0[0]);
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		IOTA0 = IOTA0 + 1;
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
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
		fHslider2_ = (float*)data; // , 0.5, 0.0, 56.0, 0.05 
		break;
	case ATTACK: 
		fHslider0_ = (float*)data; // , 0.1, 0.05, 0.5, 0.05 
		break;
	case FEEDBACK: 
		fHslider3_ = (float*)data; // , 0.0, 0.0, 1.0, 0.05 
		break;
	case RELESE: 
		fHslider1_ = (float*)data; // , 0.1, 0.05, 2.0, 0.05 
		break;
	case TIME: 
		fHslider4_ = (float*)data; // , 5e+02, 1.0, 2e+03, 1.0 
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
