// generated from file '../src/LV2/faust/tremolo.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace tremolo {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	int iVec0[2];
	double fConst1;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fConst2;
	int iRec2[2];
	int iRec1[2];
	double fConst3;
	double fRec5[2];
	double fRec4[2];
	double fRec3[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec0[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;

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
	id = "tremolo";
	name = N_("Tremolo");
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
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) iRec2[l1] = 0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) iRec1[l2] = 0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec5[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec4[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec3[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec0[l6] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 1.0 / fConst0;
	fConst2 = 0.5 * fConst0;
	fConst3 = 6.283185307179586 / fConst0;
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fCheckbox0 (*fCheckbox0_)
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
	int iSlow0 = int(double(fCheckbox0));
	double fSlow1 = double(fVslider0);
	int iSlow2 = int(fConst2 / fSlow1);
	double fSlow3 = 1.0 / double(iSlow2);
	double fSlow4 = fConst3 * fSlow1;
	double fSlow5 = double(fVslider1);
	double fSlow6 = double(fVslider2);
	double fSlow7 = 27.0 * fSlow6;
	double fSlow8 = 1.0 - 0.01 * fSlow6;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		iVec0[0] = 1;
		double fTemp0 = fRec0[1] * (1.0 - fConst1 / (fConst1 + 0.06 * std::exp(0.0 - 2.4849066497880004 * fRec0[1])));
		iRec2[0] = ((iRec2[1] > 0) ? 2 * (iRec1[1] < iSlow2) + -1 : 1 - 2 * (iRec1[1] > 0));
		iRec1[0] = iRec2[0] + iRec1[1];
		fRec5[0] = fRec5[1] + fSlow4 * (0.0 - fRec3[1]);
		fRec4[0] = fSlow4 * fRec5[0] + double(1 - iVec0[1]) + fRec4[1];
		fRec3[0] = fRec4[0];
		fRec0[0] = fTemp0 + fConst1 * (std::pow(1.0 - fSlow5 * (1.0 - ((iSlow0) ? std::max<double>(0.0, 0.5 * (fRec3[0] + 1.0)) : fSlow3 * double(iRec1[0]))), 1.9) / (fConst1 + 0.06 * std::exp(0.0 - 2.4849066497880004 * fTemp0)));
		output0[i0] = FAUSTFLOAT(double(input0[i0]) * (fSlow8 + fSlow7 / (std::exp(13.815510557964274 / std::log(8.551967507929417 * fRec0[0] + 2.718281828459045)) + 2.7e+03)));
		iVec0[1] = iVec0[0];
		iRec2[1] = iRec2[0];
		iRec1[1] = iRec1[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec0[1] = fRec0[0];
	}
#undef fCheckbox0
#undef fVslider0
#undef fVslider1
#undef fVslider2
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	// static const value_pair fCheckbox0_values[] = {{"os.triangle"},{"sine"},{0}};
	case SINE: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case DEPTH: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case FREQ: 
		fVslider0_ = (float*)data; // , 5.0, 0.1, 5e+01, 0.1 
		break;
	case WET_DRY: 
		fVslider2_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
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
   SINE, 
   DEPTH, 
   FREQ, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace tremolo
