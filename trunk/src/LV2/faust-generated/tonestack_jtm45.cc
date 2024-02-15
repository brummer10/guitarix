// generated from file '../src/LV2/faust/tonestack_jtm45.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace tonestack_jtm45 {

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
	id = "JTM-45";
	name = N_("JTM-45");
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
	double fSlow1 = 1.784904e-05 * fSlow0;
	double fSlow2 = double(fVslider1);
	double fSlow3 = 3.0621250000000006e-07 * fSlow2;
	double fSlow4 = 1.2248500000000003e-05 * fSlow0;
	double fSlow5 = fConst1 * (fSlow2 * (fSlow4 + -5.596250000000005e-08 - fSlow3) + fSlow1 + 5.442360000000002e-07);
	double fSlow6 = 1.0781100000000005e-09 * fSlow0;
	double fSlow7 = 2.3114025000000008e-11 * fSlow2;
	double fSlow8 = 9.245610000000004e-10 * fSlow0;
	double fSlow9 = fConst2 * (fSlow2 * (fSlow8 - fSlow7 + -3.8387250000000005e-12) + fSlow6 + 2.695275000000001e-11);
	double fSlow10 = 0.02227 * fSlow0;
	double fSlow11 = 0.00055 * fSlow2;
	double fSlow12 = fConst0 * (fSlow11 + fSlow10 + 0.00207625);
	double fSlow13 = fSlow12 + fSlow9 + (-1.0 - fSlow5);
	double fSlow14 = fSlow12 + fSlow5;
	double fSlow15 = fSlow14 - 3.0 * (fSlow9 + 1.0);
	double fSlow16 = fSlow5 - (fSlow12 + 3.0 * (1.0 - fSlow9));
	double fSlow17 = 1.0 / (-1.0 - (fSlow14 + fSlow9));
	double fSlow18 = 1.0 - fSlow2;
	double fSlow19 = double(fVslider2);
	double fSlow20 = fSlow19 * (fSlow6 + 2.695275000000001e-11 * fSlow18) + fSlow2 * (fSlow8 + 2.3114025000000008e-11 * fSlow18);
	double fSlow21 = fConst2 * fSlow20;
	double fSlow22 = fConst1 * (9.801000000000002e-08 * fSlow19 + fSlow2 * (3.433375000000001e-07 - fSlow3) + fSlow0 * (1.2248500000000003e-05 * fSlow2 + 1.8770400000000002e-06) + 4.6926e-08);
	double fSlow23 = fConst0 * (fSlow10 + fSlow11 + 6.75e-05 * fSlow19 + 0.0005567500000000001);
	double fSlow24 = fSlow23 + fSlow22;
	double fSlow25 = fSlow24 + fSlow21;
	double fSlow26 = fSlow23 + fSlow21 - fSlow22;
	double fSlow27 = fConst3 * fSlow20;
	double fSlow28 = fSlow24 - fSlow27;
	double fSlow29 = fSlow22 + fSlow27 - fSlow23;
	double fSlow30 = 1.0 / (-1.0 - (fSlow12 + fConst1 * (fSlow1 + fSlow2 * (fSlow4 + (-5.596250000000005e-08 - fSlow3)) + 5.442360000000002e-07) + fConst2 * (fSlow6 + fSlow2 * (fSlow8 + (-3.8387250000000005e-12 - fSlow7)) + 2.695275000000001e-11)));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = double(input0[i0]) - fSlow17 * (fSlow16 * fRec0[1] + fSlow15 * fRec0[2] + fSlow13 * fRec0[3]);
		output0[i0] = FAUSTFLOAT(fSlow30 * (fSlow29 * fRec0[1] + fSlow28 * fRec0[2] + fSlow26 * fRec0[3] - fSlow25 * fRec0[0]));
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

} // end namespace tonestack_jtm45
