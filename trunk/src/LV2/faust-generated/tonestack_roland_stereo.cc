// generated from file '../src/LV2/faust/tonestack_roland_stereo.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace tonestack_roland_stereo {

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
	double fRec1[4];

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
	id = "Roland";
	name = N_("Roland");
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
	for (int l0 = 0; l0 < 4; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 4; l1 = l1 + 1) fRec1[l1] = 0.0;
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

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
	double fSlow0 = std::exp(3.4 * (double(fVslider0) + -1.0));
	double fSlow1 = 2.851440000000001e-05 * fSlow0;
	double fSlow2 = double(fVslider1);
	double fSlow3 = 2.7256800000000006e-07 * fSlow2;
	double fSlow4 = 6.8142000000000025e-06 * fSlow0;
	double fSlow5 = fConst1 * (fSlow2 * (fSlow4 + -7.876920000000001e-07 - fSlow3) + fSlow1 + 1.4234760000000002e-06);
	double fSlow6 = 1.6641900000000002e-09 * fSlow0;
	double fSlow7 = 1.8898704000000002e-11 * fSlow2;
	double fSlow8 = 4.724676000000001e-10 * fSlow0;
	double fSlow9 = fConst2 * (fSlow2 * (fSlow8 - fSlow7 + -4.7668896000000004e-11) + fSlow6 + 6.656760000000001e-11);
	double fSlow10 = 0.00831 * fSlow0;
	double fSlow11 = 0.0008200000000000001 * fSlow2;
	double fSlow12 = fConst0 * (fSlow11 + fSlow10 + 0.005107400000000001);
	double fSlow13 = fSlow12 + fSlow9 + (-1.0 - fSlow5);
	double fSlow14 = fSlow12 + fSlow5;
	double fSlow15 = fSlow14 - 3.0 * (fSlow9 + 1.0);
	double fSlow16 = fSlow5 - (fSlow12 + 3.0 * (1.0 - fSlow9));
	double fSlow17 = 1.0 / (-1.0 - (fSlow14 + fSlow9));
	double fSlow18 = 1.0 - fSlow2;
	double fSlow19 = double(fVslider2);
	double fSlow20 = fSlow19 * (fSlow6 + 6.656760000000001e-11 * fSlow18) + fSlow2 * (fSlow8 + 1.8898704000000002e-11 * fSlow18);
	double fSlow21 = fConst2 * fSlow20;
	double fSlow22 = fConst1 * (2.829e-07 * fSlow19 + fSlow2 * (3.2176800000000005e-07 - fSlow3) + fSlow0 * (6.8142000000000025e-06 * fSlow2 + 7.779000000000002e-07) + 3.1116000000000005e-08);
	double fSlow23 = fConst0 * (fSlow10 + fSlow11 + 6e-05 * fSlow19 + 0.00033240000000000006);
	double fSlow24 = fSlow23 + fSlow22;
	double fSlow25 = fSlow24 + fSlow21;
	double fSlow26 = fSlow23 + fSlow21 - fSlow22;
	double fSlow27 = fConst3 * fSlow20;
	double fSlow28 = fSlow24 - fSlow27;
	double fSlow29 = fSlow22 + fSlow27 - fSlow23;
	double fSlow30 = 1.0 / (-1.0 - (fSlow12 + fConst1 * (fSlow1 + fSlow2 * (fSlow4 + (-7.876920000000001e-07 - fSlow3)) + 1.4234760000000002e-06) + fConst2 * (fSlow6 + fSlow2 * (fSlow8 + (-4.7668896000000004e-11 - fSlow7)) + 6.656760000000001e-11)));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = double(input0[i0]) - fSlow17 * (fSlow16 * fRec0[1] + fSlow15 * fRec0[2] + fSlow13 * fRec0[3]);
		output0[i0] = FAUSTFLOAT(fSlow30 * (fSlow29 * fRec0[1] + fSlow28 * fRec0[2] + fSlow26 * fRec0[3] - fSlow25 * fRec0[0]));
		fRec1[0] = double(input1[i0]) - fSlow17 * (fSlow16 * fRec1[1] + fSlow15 * fRec1[2] + fSlow13 * fRec1[3]);
		output1[i0] = FAUSTFLOAT(fSlow30 * (fSlow29 * fRec1[1] + fSlow28 * fRec1[2] + fSlow26 * fRec1[3] - fSlow25 * fRec1[0]));
		for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
			fRec0[j0] = fRec0[j0 - 1];
		}
		for (int j1 = 3; j1 > 0; j1 = j1 - 1) {
			fRec1[j1] = fRec1[j1 - 1];
		}
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
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

} // end namespace tonestack_roland_stereo
