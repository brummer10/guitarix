// generated from file '../src/LV2/faust/bmfp.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace bmfp {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec3[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fVec0[2];
	double fConst2;
	double fConst3;
	double fRec2[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fConst6;
	double fConst7;
	double fConst9;
	double fConst10;
	double fRec4[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fVec1[2];
	double fConst12;
	double fConst13;
	double fRec1[2];
	double fConst15;
	double fConst16;
	double fConst18;
	double fConst19;
	double fRec0[2];

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
	id = "bmpf";
	name = N_("BigMuffFuzzPadel");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec3[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fVec0[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec2[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec4[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fVec1[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec1[l5] = 0.0;
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
	double fConst1 = 1.0 / std::tan(1281.7698026646356 / fConst0);
	fConst2 = 1.0 - fConst1;
	fConst3 = 1.0 / (fConst1 + 1.0);
	double fConst4 = std::tan(5830.795965062656 / fConst0);
	double fConst5 = 1.0 / fConst4;
	fConst6 = 1.0 - fConst5;
	fConst7 = 0.01 / fConst4;
	double fConst8 = fConst5 + 1.0;
	fConst9 = 1.0 / fConst8;
	fConst10 = 0.0 - 1.0 / (fConst4 * fConst8);
	double fConst11 = 1.0 / std::tan(17690.308232364125 / fConst0);
	fConst12 = 1.0 - fConst11;
	fConst13 = 1.0 / (fConst11 + 1.0);
	double fConst14 = std::tan(251.32741228718345 / fConst0);
	fConst15 = 1.0 / fConst14;
	fConst16 = 1.0 - fConst15;
	double fConst17 = fConst15 + 1.0;
	fConst18 = 1.0 / fConst17;
	fConst19 = 0.0 - 1.0 / (fConst14 * fConst17);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
	double fSlow1 = double(fVslider1);
	double fSlow2 = 0.01 * fSlow1;
	double fSlow3 = double(fVslider2);
	double fSlow4 = 1.0 - fSlow3;
	double fSlow5 = fConst7 * fSlow1;
	double fSlow6 = double(fVslider3);
	double fSlow7 = 0.009900990099009901 * fSlow6;
	double fSlow8 = fSlow7 + 1.0;
	double fSlow9 = 0.25 * fSlow6;
	double fSlow10 = 1.0 - fSlow2;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec3[0] = fSlow0 + 0.999 * fRec3[1];
		double fTemp0 = double(input0[i0]);
		double fTemp1 = fTemp0 * fRec3[0];
		double fTemp2 = fSlow2 * fTemp1;
		fVec0[0] = fTemp2;
		fRec2[0] = 0.0 - fConst3 * (fConst2 * fRec2[1] - (fTemp2 + fVec0[1]));
		fRec4[0] = fConst10 * fVec0[1] + fConst9 * (fSlow5 * fTemp1 - fConst6 * fRec4[1]);
		double fTemp3 = fSlow3 * fRec4[0] + fSlow4 * fRec2[0];
		double fTemp4 = fSlow7 * std::fabs(fTemp3) + 1.0;
		double fTemp5 = fSlow8 * (fTemp3 / fTemp4);
		double fTemp6 = std::max<double>(-0.7, std::min<double>(0.7, fTemp5 + fSlow9 * (0.0 - fSlow8 * (fTemp3 * (1.0 - (2.0 - std::fabs(fTemp5))) / fTemp4))));
		double fTemp7 = mydsp_faustpower7_f(fTemp6) + fSlow10 * fTemp0 + fTemp6;
		fVec1[0] = fTemp7;
		fRec1[0] = 0.0 - fConst13 * (fConst12 * fRec1[1] - (fTemp7 + fVec1[1]));
		fRec0[0] = fConst19 * fRec1[1] - fConst18 * (fConst16 * fRec0[1] - fConst15 * fRec1[0]);
		output0[i0] = FAUSTFLOAT(fRec0[0]);
		fRec3[1] = fRec3[0];
		fVec0[1] = fVec0[0];
		fRec2[1] = fRec2[0];
		fRec4[1] = fRec4[0];
		fVec1[1] = fVec1[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
#undef fVslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case AUDIO_IN: 
		fVslider0_ = (float*)data; // , 0.0, -24.0, 2e+01, 0.1 
		break;
	case OUTPUT: 
		fVslider1_ = (float*)data; // , 1e+02, 5e+01, 1e+02, 1.0 
		break;
	case DRIVE: 
		fVslider3_ = (float*)data; // , 1.0, -3.0, 1e+02, 1.0 
		break;
	case TONE: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   INPUT, 
   OUTPUT, 
   DRIVE, 
   TONE, 
} PortIndex;
*/

} // end namespace bmfp
