// generated from file '../src/LV2/faust/tonestack_twin_stereo.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace tonestack_twin_stereo {

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
	double 	fConst3;
	double 	fRec0[4];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec1[4];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
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
	id = "Twin Reverb";
	name = N_("Twin Reverb");
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
	fConst0 = double(min(1.92e+05, max(1.0, (double)fSamplingFreq)));
	fConst1 = (2 * fConst0);
	fConst2 = faustpower<2>(fConst1);
	fConst3 = (6 * fConst0);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	double 	fSlow0 = double(fslider0);
	double 	fSlow1 = (4.7056400000000006e-07 * fSlow0);
	double 	fSlow2 = exp((3.4 * (double(fslider1) - 1)));
	double 	fSlow3 = ((0.00011869100000000002 * fSlow2) + (fSlow0 * ((1.1764100000000001e-05 * fSlow2) - (4.215336e-06 + fSlow1))));
	double 	fSlow4 = (5.188640000000001e-06 + fSlow3);
	double 	fSlow5 = (1.974e-11 * fSlow0);
	double 	fSlow6 = (4.935e-10 * fSlow2);
	double 	fSlow7 = (3.525e-09 * fSlow2);
	double 	fSlow8 = (1.41e-10 + (fSlow7 + (fSlow0 * (fSlow6 - (fSlow5 + 1.2126e-10)))));
	double 	fSlow9 = (fConst1 * fSlow8);
	double 	fSlow10 = (0.02503 * fSlow2);
	double 	fSlow11 = (0.00047000000000000004 * fSlow0);
	double 	fSlow12 = (fConst1 * (0.0157312 + (fSlow11 + fSlow10)));
	double 	fSlow13 = ((fSlow12 + (fConst2 * (fSlow9 - fSlow4))) - 1);
	double 	fSlow14 = (fConst3 * fSlow8);
	double 	fSlow15 = ((fSlow12 + (fConst2 * (fSlow4 - fSlow14))) - 3);
	double 	fSlow16 = ((fConst2 * (5.188640000000001e-06 + (fSlow3 + fSlow14))) - (3 + fSlow12));
	double 	fSlow17 = (1.0 / (0 - (1 + (fSlow12 + (fConst2 * (5.188640000000001e-06 + (fSlow3 + fSlow9)))))));
	double 	fSlow18 = double(fslider2);
	double 	fSlow19 = ((fSlow0 * ((1.974e-11 + fSlow6) - fSlow5)) + (fSlow18 * ((1.41e-10 + fSlow7) - (1.41e-10 * fSlow0))));
	double 	fSlow20 = (fConst1 * fSlow19);
	double 	fSlow21 = (((4.410000000000001e-07 * fSlow18) + (fSlow0 * (4.846640000000001e-07 - fSlow1))) + (fSlow2 * (1.1910000000000001e-06 + (1.1764100000000001e-05 * fSlow0))));
	double 	fSlow22 = (fSlow21 + 4.764000000000001e-08);
	double 	fSlow23 = ((fSlow10 + (fSlow11 + (3e-05 * fSlow18))) + 0.0010012);
	double 	fSlow24 = (fConst1 * fSlow23);
	double 	fSlow25 = (fSlow24 + (fConst2 * (0 - (fSlow22 - fSlow20))));
	double 	fSlow26 = (fConst3 * fSlow19);
	double 	fSlow27 = (fSlow24 + (fConst2 * (fSlow22 - fSlow26)));
	double 	fSlow28 = (fConst1 * (0 - fSlow23));
	double 	fSlow29 = (fSlow28 + (fConst2 * (4.764000000000001e-08 + (fSlow21 + fSlow26))));
	double 	fSlow30 = (fSlow28 - (fConst2 * (4.764000000000001e-08 + (fSlow21 + fSlow20))));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((double)input0[i] - (fSlow17 * (((fSlow16 * fRec0[1]) + (fSlow15 * fRec0[2])) + (fSlow13 * fRec0[3]))));
		output0[i] = (FAUSTFLOAT)(fSlow17 * ((((fSlow30 * fRec0[0]) + (fSlow29 * fRec0[1])) + (fSlow27 * fRec0[2])) + (fSlow25 * fRec0[3])));
		fRec1[0] = ((double)input1[i] - (fSlow17 * (((fSlow16 * fRec1[1]) + (fSlow15 * fRec1[2])) + (fSlow13 * fRec1[3]))));
		output1[i] = (FAUSTFLOAT)(fSlow17 * ((((fSlow30 * fRec1[0]) + (fSlow29 * fRec1[1])) + (fSlow27 * fRec1[2])) + (fSlow25 * fRec1[3])));
		// post processing
		for (int i=3; i>0; i--) fRec1[i] = fRec1[i-1];
		for (int i=3; i>0; i--) fRec0[i] = fRec0[i-1];
	}
#undef fslider0
#undef fslider1
#undef fslider2
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

} // end namespace tonestack_twin_stereo
