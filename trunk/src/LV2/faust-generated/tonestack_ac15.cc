// generated from file '../src/LV2/faust/tonestack_ac15.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace tonestack_ac15 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst0;
	double fConst1;
	double fConst2;
	double fRec0[4];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fConst3;

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
	id = "AC-15";
	name = N_("AC-15");
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
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = 2.0 * std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	fConst2 = mydsp_faustpower3_f(fConst0);
	fConst3 = 3.0 * fConst2;
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
	double fSlow0 = std::exp(3.4 * (double(fVslider0) + -1.0));
	double fSlow1 = double(fVslider1);
	double fSlow2 = 0.00022854915600000004 * fSlow1;
	double fSlow3 = fConst1 * (fSlow1 * (0.00022854915600000004 * fSlow0 + 0.00012621831200000002 - fSlow2) + 0.00010719478000000002 * fSlow0 + 0.00010871476000000002);
	double fSlow4 = fSlow0 + 1.0;
	double fSlow5 = fSlow0 - fSlow1;
	double fSlow6 = fConst2 * (fSlow1 * (3.421299200000001e-08 * fSlow5 + 2.3521432000000005e-08) + 1.0691560000000003e-08 * fSlow4);
	double fSlow7 = 0.01034 * fSlow1;
	double fSlow8 = fConst0 * (fSlow7 + 0.022103400000000002 * fSlow0 + 0.036906800000000003);
	double fSlow9 = fSlow8 + fSlow6 + (-1.0 - fSlow3);
	double fSlow10 = fSlow8 + fSlow3;
	double fSlow11 = fSlow10 - 3.0 * (fSlow6 + 1.0);
	double fSlow12 = fSlow3 - (fSlow8 + 3.0 * (1.0 - fSlow6));
	double fSlow13 = 1.0 / (-1.0 - (fSlow10 + fSlow6));
	double fSlow14 = double(fVslider2);
	double fSlow15 = fConst1 * (1.5199800000000001e-06 * fSlow14 + fSlow1 * (0.00022961831200000004 - fSlow2) + fSlow0 * (fSlow2 + 3.7947800000000004e-06) + 3.7947800000000004e-06);
	double fSlow16 = 3.421299200000001e-08 * fSlow1 * (fSlow5 + 1.0) + 1.0691560000000003e-08 * fSlow14 * (fSlow0 + (1.0 - fSlow1));
	double fSlow17 = fConst2 * fSlow16;
	double fSlow18 = fConst0 * (fSlow7 + 0.0001034 * fSlow14 + 0.022103400000000002 * fSlow4);
	double fSlow19 = fSlow18 + fSlow17 - fSlow15;
	double fSlow20 = fConst3 * fSlow16;
	double fSlow21 = fSlow18 + fSlow15;
	double fSlow22 = fSlow21 - fSlow20;
	double fSlow23 = fSlow15 + fSlow20 - fSlow18;
	double fSlow24 = 0.0 - (fSlow21 + fSlow17);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = double(input0[i0]) - fSlow13 * (fSlow12 * fRec0[1] + fSlow11 * fRec0[2] + fSlow9 * fRec0[3]);
		output0[i0] = FAUSTFLOAT(fSlow13 * (fSlow24 * fRec0[0] + fSlow23 * fRec0[1] + fSlow22 * fRec0[2] + fSlow19 * fRec0[3]));
		for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
			fRec0[j0] = fRec0[j0 - 1];
		}
	}
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
	case BASS: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case MIDDLE: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TREBLE: 
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
   BASS, 
   MIDDLE, 
   TREBLE, 
} PortIndex;
*/

} // end namespace tonestack_ac15
