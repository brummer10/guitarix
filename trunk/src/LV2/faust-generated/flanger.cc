// generated from file '../src/LV2/faust/flanger.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace flanger {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	int iVec0[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT	*fHslider2_;
	int IOTA0;
	double fVec1[4096];
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT	*fHslider3_;
	double fConst0;
	double fConst1;
	double fRec1[2];
	double fRec2[2];
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT	*fHslider4_;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT	*fHslider5_;
	double fRec0[2];
	double fVec2[4096];
	double fRec3[2];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "flanger";
	name = N_("Flanger");
	mono_audio = 0;
	stereo_audio = compute_static;
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
	for (int l1 = 0; l1 < 4096; l1 = l1 + 1) fVec1[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec1[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec2[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec0[l4] = 0.0;
	for (int l5 = 0; l5 < 4096; l5 = l5 + 1) fVec2[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec3[l6] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 6.283185307179586 / fConst0;
	IOTA0 = 0;
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fCheckbox0 (*fCheckbox0_)
#define fHslider0 (*fHslider0_)
#define fHslider1 (*fHslider1_)
#define fHslider2 (*fHslider2_)
#define fHslider3 (*fHslider3_)
#define fHslider4 (*fHslider4_)
#define fHslider5 (*fHslider5_)
	double fSlow0 = double(fHslider0);
	double fSlow1 = ((int(double(fCheckbox0))) ? -1.0 * fSlow0 : fSlow0);
	double fSlow2 = std::pow(1e+01, 0.05 * double(fHslider1));
	double fSlow3 = double(fHslider2);
	double fSlow4 = fConst1 * double(fHslider3);
	double fSlow5 = std::cos(fSlow4);
	double fSlow6 = std::sin(fSlow4);
	double fSlow7 = 0.0005 * double(fHslider4);
	double fSlow8 = 0.001 * double(fHslider5);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = fSlow2 * double(input0[i0]);
		iVec0[0] = 1;
		double fTemp1 = fSlow3 * fRec0[1] - fTemp0;
		fVec1[IOTA0 & 4095] = fTemp1;
		fRec1[0] = fSlow6 * fRec2[1] + fSlow5 * fRec1[1];
		fRec2[0] = double(1 - iVec0[1]) + fSlow5 * fRec2[1] - fSlow6 * fRec1[1];
		double fTemp2 = fConst0 * (fSlow8 + fSlow7 * (fRec1[0] + 1.0));
		int iTemp3 = int(fTemp2);
		double fTemp4 = std::floor(fTemp2);
		fRec0[0] = fVec1[(IOTA0 - std::min<int>(2049, std::max<int>(0, iTemp3))) & 4095] * (fTemp4 + (1.0 - fTemp2)) + (fTemp2 - fTemp4) * fVec1[(IOTA0 - std::min<int>(2049, std::max<int>(0, iTemp3 + 1))) & 4095];
		output0[i0] = FAUSTFLOAT(0.5 * (fTemp0 + fRec0[0] * fSlow1));
		double fTemp5 = fSlow2 * double(input1[i0]);
		double fTemp6 = fSlow3 * fRec3[1] - fTemp5;
		fVec2[IOTA0 & 4095] = fTemp6;
		double fTemp7 = fConst0 * (fSlow8 + fSlow7 * (fRec2[0] + 1.0));
		int iTemp8 = int(fTemp7);
		double fTemp9 = std::floor(fTemp7);
		fRec3[0] = fVec2[(IOTA0 - std::min<int>(2049, std::max<int>(0, iTemp8))) & 4095] * (fTemp9 + (1.0 - fTemp7)) + (fTemp7 - fTemp9) * fVec2[(IOTA0 - std::min<int>(2049, std::max<int>(0, iTemp8 + 1))) & 4095];
		output1[i0] = FAUSTFLOAT(0.5 * (fTemp5 + fRec3[0] * fSlow1));
		iVec0[1] = iVec0[0];
		IOTA0 = IOTA0 + 1;
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec0[1] = fRec0[0];
		fRec3[1] = fRec3[0];
	}
#undef fCheckbox0
#undef fHslider0
#undef fHslider1
#undef fHslider2
#undef fHslider3
#undef fHslider4
#undef fHslider5
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	// static const value_pair fCheckbox0_values[] = {{"linear"},{"invert"},{0}};
	case INVERT: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case LFOFREQ: 
		fHslider3_ = (float*)data; // , 0.2, 0.0, 5.0, 0.01 
		break;
	case DEPTH: 
		fHslider0_ = (float*)data; // , 1.0, 0.0, 1.0, 0.01 
		break;
	case FEEDBACKGAIN: 
		fHslider2_ = (float*)data; // , 0.0, 0.0, 1.0, 0.01 
		break;
	case DELAY: 
		fHslider4_ = (float*)data; // , 1e+01, 0.0, 2e+01, 0.01 
		break;
	case DELAYOFFSET: 
		fHslider5_ = (float*)data; // , 1.0, 0.0, 2e+01, 0.01 
		break;
	case LEVEL: 
		fHslider1_ = (float*)data; // , 0.0, -6e+01, 1e+01, 0.1 
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
   LFOFREQ, 
   DEPTH, 
   FEEDBACKGAIN, 
   DELAY, 
   DELAYOFFSET, 
   INVERT, 
   LEVEL, 
} PortIndex;
*/

} // end namespace flanger
