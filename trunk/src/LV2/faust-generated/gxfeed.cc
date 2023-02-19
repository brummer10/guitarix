// generated from file '../src/LV2/faust/gxfeed.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace gxfeed {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	int IOTA0;
	double fVec0[1024];
	double fRec6[2];
	double fVec1[1024];
	double fRec8[2];
	double fVec2[1024];
	double fRec10[2];
	double fVec3[2048];
	double fRec12[2];
	double fVec4[128];
	double fRec4[2];
	double fVec5[64];
	double fRec2[2];
	double fVec6[12];
	double fRec0[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;

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
	id = "gxfeed";
	name = N_("gxfeed");
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
	for (int l0 = 0; l0 < 1024; l0 = l0 + 1) fVec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec6[l1] = 0.0;
	for (int l2 = 0; l2 < 1024; l2 = l2 + 1) fVec1[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec8[l3] = 0.0;
	for (int l4 = 0; l4 < 1024; l4 = l4 + 1) fVec2[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec10[l5] = 0.0;
	for (int l6 = 0; l6 < 2048; l6 = l6 + 1) fVec3[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec12[l7] = 0.0;
	for (int l8 = 0; l8 < 128; l8 = l8 + 1) fVec4[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec4[l9] = 0.0;
	for (int l10 = 0; l10 < 64; l10 = l10 + 1) fVec5[l10] = 0.0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec2[l11] = 0.0;
	for (int l12 = 0; l12 < 12; l12 = l12 + 1) fVec6[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec0[l13] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
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
#define fVslider0 (*fVslider0_)
	int iSlow0 = int(double(fCheckbox0));
	double fSlow1 = double(fVslider0);
	double fSlow2 = 1.0 - std::max<double>(0.0, -1.0 * fSlow1);
	double fSlow3 = 1.0 - std::max<double>(0.0, fSlow1);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input1[i0]);
		double fTemp1 = 0.2 * fTemp0;
		double fTemp2 = fTemp1 + 0.805 * fRec6[1];
		fVec0[IOTA0 & 1023] = fTemp2;
		fRec6[0] = fVec0[(IOTA0 - 901) & 1023];
		double fRec7 = fTemp2;
		double fTemp3 = 0.827 * fRec8[1] + fTemp1;
		fVec1[IOTA0 & 1023] = fTemp3;
		fRec8[0] = fVec1[(IOTA0 - 778) & 1023];
		double fRec9 = fTemp3;
		double fTemp4 = fTemp1 + 0.783 * fRec10[1];
		fVec2[IOTA0 & 1023] = fTemp4;
		fRec10[0] = fVec2[(IOTA0 - 1011) & 1023];
		double fRec11 = fTemp4;
		double fTemp5 = fTemp1 + 0.764 * fRec12[1];
		fVec3[IOTA0 & 2047] = fTemp5;
		fRec12[0] = fVec3[(IOTA0 - 1123) & 2047];
		double fRec13 = fTemp5;
		double fTemp6 = 0.7 * fRec4[1] + fRec13 + fRec11 + fRec9 + fRec7;
		fVec4[IOTA0 & 127] = fTemp6;
		fRec4[0] = fVec4[(IOTA0 - 124) & 127];
		double fRec5 = 0.0 - 0.7 * fTemp6;
		double fTemp7 = fRec4[1] + fRec5 + 0.7 * fRec2[1];
		fVec5[IOTA0 & 63] = fTemp7;
		fRec2[0] = fVec5[(IOTA0 - 41) & 63];
		double fRec3 = 0.0 - 0.7 * fTemp7;
		double fTemp8 = fRec2[1] + fRec3 + 0.7 * fRec0[1];
		fVec6[0] = fTemp8;
		fRec0[0] = fVec6[11];
		double fRec1 = 0.0 - 0.7 * fTemp8;
		double fTemp9 = ((iSlow0) ? fSlow3 * fTemp0 + fSlow2 * (fRec1 + fRec0[1]) : double(input0[i0]));
		output0[i0] = FAUSTFLOAT(fTemp9);
		output1[i0] = FAUSTFLOAT(fTemp9);
		IOTA0 = IOTA0 + 1;
		fRec6[1] = fRec6[0];
		fRec8[1] = fRec8[0];
		fRec10[1] = fRec10[0];
		fRec12[1] = fRec12[0];
		fRec4[1] = fRec4[0];
		fRec2[1] = fRec2[0];
		for (int j0 = 11; j0 > 0; j0 = j0 - 1) {
			fVec6[j0] = fVec6[j0 - 1];
		}
		fRec0[1] = fRec0[0];
	}
#undef fCheckbox0
#undef fVslider0
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case FEED_ON_OFF: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case WET_DRY: 
		fVslider0_ = (float*)data; // , 0.0, -1.0, 1.0, 0.01 
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
   FEED_ON_OFF, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace gxfeed
