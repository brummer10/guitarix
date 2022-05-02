// generated from file '../src/LV2/faust/gx_flanger.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace gx_flanger {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	int iVec0[2];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	int IOTA0;
	double fVec1[2048];
	double fConst0;
	double fConst1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT	*fHslider2_;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT	*fHslider3_;
	double fConst2;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT	*fHslider4_;
	double fRec1[2];
	double fRec2[2];
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT	*fHslider5_;
	double fVec2[2048];
	double fRec0[2];
	double fVec3[4096];
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
	id = "flanger_mono_gx";
	name = N_("Flanger GX");
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
	for (int l1 = 0; l1 < 2048; l1 = l1 + 1) fVec1[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec1[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec2[l3] = 0.0;
	for (int l4 = 0; l4 < 2048; l4 = l4 + 1) fVec2[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec0[l5] = 0.0;
	for (int l6 = 0; l6 < 4096; l6 = l6 + 1) fVec3[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec3[l7] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 0.5 * fConst0;
	fConst2 = 6.2831853071795862 / fConst0;
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
#define fHslider5 (*fHslider5_)
	double fSlow0 = double(fHslider0);
	double fSlow1 = double(fHslider1);
	double fSlow2 = 0.01 * fSlow0 * std::min<double>(1.0, 1.0 - fSlow1);
	double fSlow3 = 2.0 - fSlow2;
	double fSlow4 = 0.01 * fSlow0 * std::min<double>(1.0, fSlow1 + 1.0);
	double fSlow5 = 2.0 - fSlow4;
	double fSlow6 = 0.001 * double(fHslider2);
	double fSlow7 = 0.00050000000000000001 * double(fHslider3);
	double fSlow8 = fConst2 * double(fHslider4);
	double fSlow9 = std::sin(fSlow8);
	double fSlow10 = std::cos(fSlow8);
	double fSlow11 = 0.33333333333333331 * double(fHslider5) * (std::fabs(fSlow1) + 2.0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		iVec0[0] = 1;
		double fTemp0 = double(input0[i0]);
		fVec1[IOTA0 & 2047] = fTemp0;
		fRec1[0] = fSlow9 * fRec2[1] + fSlow10 * fRec1[1];
		fRec2[0] = (double(1 - iVec0[1]) + fSlow10 * fRec2[1]) - fSlow9 * fRec1[1];
		double fTemp1 = fSlow6 + fSlow7 * (fRec1[0] + 1.0);
		double fTemp2 = fConst1 * fTemp1;
		double fTemp3 = std::floor(fTemp2);
		double fTemp4 = fTemp3 + 1.0 - fTemp2;
		double fTemp5 = fTemp2 - fTemp3;
		int iTemp6 = int(fTemp2);
		int iTemp7 = std::min<int>(1025, std::max<int>(0, iTemp6 + 1));
		int iTemp8 = std::min<int>(1025, std::max<int>(0, iTemp6));
		double fTemp9 = fTemp5 * fVec1[(IOTA0 - iTemp7) & 2047] + fSlow11 * fRec0[1] + fVec1[(IOTA0 - iTemp8) & 2047] * fTemp4;
		fVec2[IOTA0 & 2047] = fTemp9;
		fRec0[0] = fTemp4 * fVec2[(IOTA0 - iTemp8) & 2047] + fTemp5 * fVec2[(IOTA0 - iTemp7) & 2047];
		double fTemp10 = fSlow5 * fTemp0 + fSlow4 * fRec0[0];
		double fTemp11 = fTemp10 - fSlow11 * fRec3[1];
		fVec3[IOTA0 & 4095] = fTemp11;
		double fTemp12 = fConst0 * fTemp1;
		int iTemp13 = int(fTemp12);
		double fTemp14 = std::floor(fTemp12);
		fRec3[0] = fVec3[(IOTA0 - std::min<int>(2049, std::max<int>(0, iTemp13))) & 4095] * (fTemp14 + 1.0 - fTemp12) + (fTemp12 - fTemp14) * fVec3[(IOTA0 - std::min<int>(2049, std::max<int>(0, iTemp13 + 1))) & 4095];
		output0[i0] = FAUSTFLOAT(0.25 * (fSlow3 * fTemp10 + fSlow2 * fRec3[0]));
		iVec0[1] = iVec0[0];
		IOTA0 = IOTA0 + 1;
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec0[1] = fRec0[0];
		fRec3[1] = fRec3[0];
	}
#undef fHslider0
#undef fHslider1
#undef fHslider2
#undef fHslider3
#undef fHslider4
#undef fHslider5
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
		fHslider2_ = (float*)data; // , 0.5, 0.0, 5.0, 0.01 
		break;
	case FEEDBACK: 
		fHslider5_ = (float*)data; // , -0.70699999999999996, -0.98999999999999999, 0.98999999999999999, 0.01 
		break;
	case FREQ: 
		fHslider4_ = (float*)data; // , 0.20000000000000001, 0.050000000000000003, 10.0, 1.0600000000000001 
		break;
	case MIX: 
		fHslider1_ = (float*)data; // , 0.0, -1.0, 1.0, 0.10000000000000001 
		break;
	case WET: 
		fHslider0_ = (float*)data; // , 100.0, 0.0, 100.0, 1.0 
		break;
	case WIDTH: 
		fHslider3_ = (float*)data; // , 5.0, 0.0, 10.0, 0.01 
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
   FEEDBACK, 
   FREQ, 
   MIX, 
   WET, 
   WIDTH, 
} PortIndex;
*/

} // end namespace gx_flanger
