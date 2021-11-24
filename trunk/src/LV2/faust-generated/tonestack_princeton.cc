// generated from file '../src/LV2/faust/tonestack_princeton.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace tonestack_princeton {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	double fConst0;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst1;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fConst2;
	double fRec0[4];

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
	id = "Princeton";
	name = N_("Princeton");
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
	for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) fRec0[l0] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = (2.0 * std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate))));
	fConst1 = mydsp_faustpower2_f(fConst0);
	fConst2 = (3.0 * fConst0);
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
	double fSlow0 = double(fVslider0);
	double fSlow1 = std::exp((3.3999999999999999 * (double(fVslider1) + -1.0)));
	double fSlow2 = ((0.00022560000000000001 * fSlow0) + (0.025062500000000001 * fSlow1));
	double fSlow3 = (fConst0 * (fSlow2 + 0.015243699999999999));
	double fSlow4 = (1.0855872000000003e-07 * fSlow0);
	double fSlow5 = (((fSlow0 * (((5.6541000000000015e-06 * fSlow1) + -2.1333412800000006e-06) - fSlow4)) + (0.00011998125000000002 * fSlow1)) + 3.2223900000000008e-06);
	double fSlow6 = ((4.935e-10 * fSlow1) - (9.4752000000000007e-12 * fSlow0));
	double fSlow7 = (7.3437500000000008e-09 * fSlow1);
	double fSlow8 = (((fSlow0 * (fSlow6 + -1.3152480000000001e-10)) + fSlow7) + 1.41e-10);
	double fSlow9 = (fConst0 * fSlow8);
	double fSlow10 = (1.0 / (-1.0 - (fSlow3 + (fConst1 * (fSlow5 + fSlow9)))));
	double fSlow11 = double(fVslider2);
	double fSlow12 = (fConst0 * ((fSlow2 + (6.2500000000000001e-05 * fSlow11)) + 0.00048120000000000004));
	double fSlow13 = (((9.187500000000001e-07 * fSlow11) + ((fSlow0 * (1.2265872000000003e-07 - fSlow4)) + (fSlow1 * ((5.6541000000000015e-06 * fSlow0) + 2.4812500000000002e-06)))) + 4.7640000000000008e-08);
	double fSlow14 = ((fSlow0 * (fSlow6 + 9.4752000000000007e-12)) + (fSlow11 * (fSlow7 - (1.41e-10 * (fSlow0 + -1.0)))));
	double fSlow15 = (fConst0 * fSlow14);
	double fSlow16 = (0.0 - (fSlow12 + (fConst1 * (fSlow13 + fSlow15))));
	double fSlow17 = (fConst2 * fSlow8);
	double fSlow18 = ((fConst1 * (fSlow5 + fSlow17)) + (-3.0 - fSlow3));
	double fSlow19 = ((fSlow3 + (fConst1 * (fSlow5 - fSlow17))) + -3.0);
	double fSlow20 = (fSlow3 + (-1.0 - (fConst1 * (fSlow5 - fSlow9))));
	double fSlow21 = (fConst2 * fSlow14);
	double fSlow22 = ((fConst1 * (fSlow13 + fSlow21)) - fSlow12);
	double fSlow23 = (fSlow12 + (fConst1 * (fSlow13 - fSlow21)));
	double fSlow24 = (fSlow12 - (fConst1 * (fSlow13 - fSlow15)));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		fRec0[0] = (double(input0[i0]) - (fSlow10 * (((fSlow18 * fRec0[1]) + (fSlow19 * fRec0[2])) + (fSlow20 * fRec0[3]))));
		output0[i0] = FAUSTFLOAT((fSlow10 * ((((fSlow16 * fRec0[0]) + (fSlow22 * fRec0[1])) + (fSlow23 * fRec0[2])) + (fSlow24 * fRec0[3]))));
		for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
			fRec0[j0] = fRec0[(j0 - 1)];
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
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case MIDDLE: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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

} // end namespace tonestack_princeton
