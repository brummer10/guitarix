// generated from file '../src/LV2/faust/hogsfoot.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace hogsfoot {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[4];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec1[2];
	double fConst8;

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
	id = "hogsfoot";
	name = N_("Hogs Foot");
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
	for (int l0 = 0; l0 < 4; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec1[l1] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 8.93887847679127e-15 * fConst0;
	fConst2 = fConst0 * (fConst0 * (4.96106145708971e-12 - fConst1) + -2.63723081667839e-11) + 2.67730449581491e-11;
	fConst3 = 2.68166354303738e-14 * fConst0;
	fConst4 = fConst0 * (fConst0 * (fConst3 + -4.96106145708971e-12) + -2.63723081667839e-11) + 8.03191348744474e-11;
	fConst5 = fConst0 * (fConst0 * (-4.96106145708971e-12 - fConst3) + 2.63723081667839e-11) + 8.03191348744474e-11;
	fConst6 = fConst0 * (fConst0 * (fConst1 + 4.96106145708971e-12) + 2.63723081667839e-11) + 2.67730449581491e-11;
	fConst7 = 1.0 / fConst6;
	fConst8 = mydsp_faustpower2_f(fConst0) / fConst6;
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
	double fSlow0 = 0.01 * double(fVslider0);
	double fSlow1 = 0.007000000000000006 * double(fVslider1);
	double fSlow2 = 1.0 - fSlow0;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		fRec0[0] = fSlow0 * fTemp0 - fConst7 * (fConst5 * fRec0[1] + fConst4 * fRec0[2] + fConst2 * fRec0[3]);
		fRec1[0] = fSlow1 + 0.993 * fRec1[1];
		double fTemp1 = 9.64632260709932e-11 * fRec1[0];
		output0[i0] = FAUSTFLOAT(fSlow2 * fTemp0 + fConst8 * ((fTemp1 + 9.64632260709932e-13) * (fRec0[1] + fRec0[2]) + (-9.64632260709932e-13 - fTemp1) * (fRec0[0] + fRec0[3])));
		for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
			fRec0[j0] = fRec0[j0 - 1];
		}
		fRec1[1] = fRec1[0];
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
	case VOLUME: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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
   VOLUME, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace hogsfoot
