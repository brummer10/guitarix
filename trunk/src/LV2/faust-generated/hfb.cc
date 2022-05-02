// generated from file '../src/LV2/faust/hfb.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace hfb {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec1[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec2[2];
	double fConst3;
	double fConst5;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fRec0[3];

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
	id = "hfb";
	name = N_("HF Brightener");
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec1[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec2[l1] = 0.0;
	for (int l2 = 0; l2 < 3; l2 = l2 + 1) fRec0[l2] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	double fConst2 = 1.1827552040751701e-09 * fConst0;
	fConst3 = fConst2 + -6.6128772258314704e-08;
	double fConst4 = 1.1702375430685401e-09 * fConst0;
	fConst5 = 6.5060860471186096e-08 - fConst4;
	double fConst6 = 2.3655104081503399e-10 * fConst0;
	fConst7 = fConst6 + -1.32257544516629e-08;
	fConst8 = fConst2 + 6.6128772258314704e-08;
	fConst9 = -6.5060860471186096e-08 - fConst4;
	fConst10 = fConst6 + 1.32257544516629e-08;
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
	double fSlow0 = 0.0070000000000000062 * double(fVslider0);
	double fSlow1 = 0.0070000000000000062 * (1.0 - double(fVslider1));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec1[0] = fSlow0 + 0.99299999999999999 * fRec1[1];
		fRec2[0] = fSlow1 + 0.99299999999999999 * fRec2[1];
		double fTemp0 = fConst0 * (fRec1[0] * (fConst8 + fConst9 * fRec1[0]) + fConst10 * fRec2[0] + 7.8850346938344698e-07) + 4.4085848172209803e-05;
		fRec0[0] = double(input0[i0]) - (fRec0[1] * (fConst1 * (fRec1[0] * (2.3404750861370802e-09 * fRec1[0] + -2.3655104081503402e-09) - 4.7310208163006798e-10 * fRec2[0]) + 8.8171696344419606e-05) + fRec0[2] * (fConst0 * (fRec1[0] * (fConst3 + fConst5 * fRec1[0]) + fConst7 * fRec2[0] + -7.8850346938344698e-07) + 4.4085848172209803e-05)) / fTemp0;
		double fTemp1 = fConst0 * (fRec1[0] * (5.12666523663255e-23 * fRec1[0] + -1.59041010538546e-09) - 3.1808202107709101e-10 * fRec2[0]);
		output0[i0] = FAUSTFLOAT(fConst0 * (fRec0[0] * (fTemp1 + -1.06027340359031e-06) + fConst0 * fRec0[1] * (6.3616404215418305e-10 * fRec2[0] + fRec1[0] * (0.0 - 1.02533304732651e-22 * fRec1[0] + 3.18082021077092e-09)) + fRec0[2] * (fTemp1 + 1.06027340359031e-06)) / fTemp0);
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
	}
#undef fVslider0
#undef fVslider1
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case INTENSITY: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   INTENSITY, 
   VOLUME, 
} PortIndex;
*/

} // end namespace hfb
