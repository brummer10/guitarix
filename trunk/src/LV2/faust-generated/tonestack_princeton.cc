// generated from file '../src/LV2/faust/tonestack_princeton.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace tonestack_princeton {

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
	double fSlow1 = 0.00011998125000000002 * fSlow0;
	double fSlow2 = double(fVslider1);
	double fSlow3 = 1.0855872000000003e-07 * fSlow2;
	double fSlow4 = 5.6541000000000015e-06 * fSlow0;
	double fSlow5 = fConst1 * (fSlow2 * (fSlow4 + -2.1333412800000006e-06 - fSlow3) + fSlow1 + 3.222390000000001e-06);
	double fSlow6 = 7.343750000000001e-09 * fSlow0;
	double fSlow7 = 9.4752e-12 * fSlow2;
	double fSlow8 = 4.935e-10 * fSlow0;
	double fSlow9 = fConst2 * (fSlow2 * (fSlow8 - fSlow7 + -1.315248e-10) + fSlow6 + 1.41e-10);
	double fSlow10 = 0.0250625 * fSlow0;
	double fSlow11 = 0.0002256 * fSlow2;
	double fSlow12 = fConst0 * (fSlow11 + fSlow10 + 0.015243699999999999);
	double fSlow13 = fSlow12 + fSlow9 + (-1.0 - fSlow5);
	double fSlow14 = fSlow12 + fSlow5;
	double fSlow15 = fSlow14 - 3.0 * (fSlow9 + 1.0);
	double fSlow16 = fSlow5 - (fSlow12 + 3.0 * (1.0 - fSlow9));
	double fSlow17 = 1.0 / (-1.0 - (fSlow14 + fSlow9));
	double fSlow18 = 1.0 - fSlow2;
	double fSlow19 = double(fVslider2);
	double fSlow20 = fSlow19 * (fSlow6 + 1.41e-10 * fSlow18) + fSlow2 * (fSlow8 + 9.4752e-12 * fSlow18);
	double fSlow21 = fConst2 * fSlow20;
	double fSlow22 = fConst1 * (9.187500000000001e-07 * fSlow19 + fSlow2 * (1.2265872000000003e-07 - fSlow3) + fSlow0 * (5.6541000000000015e-06 * fSlow2 + 2.48125e-06) + 4.764000000000001e-08);
	double fSlow23 = fConst0 * (fSlow10 + fSlow11 + 6.25e-05 * fSlow19 + 0.00048120000000000004);
	double fSlow24 = fSlow23 + fSlow22;
	double fSlow25 = fSlow24 + fSlow21;
	double fSlow26 = fSlow23 + fSlow21 - fSlow22;
	double fSlow27 = fConst3 * fSlow20;
	double fSlow28 = fSlow24 - fSlow27;
	double fSlow29 = fSlow22 + fSlow27 - fSlow23;
	double fSlow30 = 1.0 / (-1.0 - (fSlow12 + fConst1 * (fSlow1 + fSlow2 * (fSlow4 + (-2.1333412800000006e-06 - fSlow3)) + 3.222390000000001e-06) + fConst2 * (fSlow6 + fSlow2 * (fSlow8 + (-1.315248e-10 - fSlow7)) + 1.41e-10)));
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

} // end namespace tonestack_princeton
