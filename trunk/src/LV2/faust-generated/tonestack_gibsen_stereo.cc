// generated from file '../src/LV2/faust/tonestack_gibsen_stereo.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)


namespace tonestack_gibsen_stereo {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fRec0[4];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec1[4];
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, float *input0, float *input1, float *output0, float *output1);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, float *input0, float *input1, float *output0, float *output1, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "Gibsen";
	name = N_("Gibsen");
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
	for (int i=0; i<4; i++) fRec0[i] = 0;
	for (int i=0; i<4; i++) fRec1[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (2 * double(min(192000, max(1, fSamplingFreq))));
	fConst1 = faustpower<2>(fConst0);
	fConst2 = (3 * fConst0);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, float *input0, float *input1, float *output0, float *output1)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (1.0607618000000002e-05 * fSlow0);
	double 	fSlow2 = exp((3.4 * (fslider1 - 1)));
	double 	fSlow3 = (3.1187760000000004e-05 + ((0.00032604000000000004 * fSlow2) + (fSlow0 * (((0.00011284700000000001 * fSlow2) - 1.9801382e-05) - fSlow1))));
	double 	fSlow4 = ((3.5814000000000013e-09 * fSlow2) - (3.3665160000000007e-10 * fSlow0));
	double 	fSlow5 = (8.100000000000003e-09 * fSlow2);
	double 	fSlow6 = (7.614000000000002e-10 + (fSlow5 + (fSlow0 * (fSlow4 - 4.247484000000001e-10))));
	double 	fSlow7 = (fConst0 * fSlow6);
	double 	fSlow8 = (0.00188 * fSlow0);
	double 	fSlow9 = (0.060025 * fSlow2);
	double 	fSlow10 = (fConst0 * (0.027267350000000003 + (fSlow9 + fSlow8)));
	double 	fSlow11 = ((fSlow10 + (fConst1 * (fSlow7 - fSlow3))) - 1);
	double 	fSlow12 = (fConst2 * fSlow6);
	double 	fSlow13 = ((fConst1 * (fSlow3 + fSlow12)) - (3 + fSlow10));
	double 	fSlow14 = ((fSlow10 + (fConst1 * (fSlow3 - fSlow12))) - 3);
	double 	fSlow15 = (1.0 / (0 - (1 + (fSlow10 + (fConst1 * (fSlow3 + fSlow7))))));
	double 	fSlow16 = fslider2;
	double 	fSlow17 = ((fSlow0 * (3.3665160000000007e-10 + fSlow4)) + (fSlow16 * (fSlow5 + (7.614000000000002e-10 - (7.614000000000002e-10 * fSlow0)))));
	double 	fSlow18 = (fConst2 * fSlow17);
	double 	fSlow19 = (1.9176000000000002e-07 + (((5.400000000000001e-07 * fSlow16) + (fSlow0 * (1.0654618000000002e-05 - fSlow1))) + (fSlow2 * (2.0400000000000004e-06 + (0.00011284700000000001 * fSlow0)))));
	double 	fSlow20 = (0.005642350000000001 + (fSlow9 + (fSlow8 + (2.5e-05 * fSlow16))));
	double 	fSlow21 = (fConst0 * fSlow20);
	double 	fSlow22 = (fSlow21 + (fConst1 * (fSlow19 - fSlow18)));
	double 	fSlow23 = (fConst0 * fSlow17);
	double 	fSlow24 = (fSlow21 + (fConst1 * (fSlow23 - fSlow19)));
	double 	fSlow25 = (fConst0 * (0 - fSlow20));
	double 	fSlow26 = (fSlow25 + (fConst1 * (fSlow19 + fSlow18)));
	double 	fSlow27 = (fSlow25 - (fConst1 * (fSlow19 + fSlow23)));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((double)input0[i] - (fSlow15 * (((fSlow14 * fRec0[2]) + (fSlow13 * fRec0[1])) + (fSlow11 * fRec0[3]))));
		output0[i] = (FAUSTFLOAT)(fSlow15 * ((fSlow27 * fRec0[0]) + ((fSlow26 * fRec0[1]) + ((fSlow24 * fRec0[3]) + (fSlow22 * fRec0[2])))));
		fRec1[0] = ((double)input1[i] - (fSlow15 * (((fSlow14 * fRec1[2]) + (fSlow13 * fRec1[1])) + (fSlow11 * fRec1[3]))));
		output1[i] = (FAUSTFLOAT)(fSlow15 * ((fSlow27 * fRec1[0]) + ((fSlow26 * fRec1[1]) + ((fSlow24 * fRec1[3]) + (fSlow22 * fRec1[2])))));
		// post processing
		for (int i=3; i>0; i--) fRec1[i] = fRec1[i-1];
		for (int i=3; i>0; i--) fRec0[i] = fRec0[i-1];
	}
#undef fslider0
#undef fslider1
#undef fslider2
}

void __rt_func Dsp::compute_static(int count, float *input0, float *input1, float *output0, float *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case BASS: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case MIDDLE: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TREBLE: 
		fslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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

} // end namespace tonestack_gibsen_stereo
