// generated from file '../src/LV2/faust/tonestack_mesa.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace tonestack_mesa {

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

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
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
	id = "Mesa Boogie";
	name = N_("Mesa Boogie");
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
	for (int i=0; i<4; i++) fRec0[i] = 0;
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

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	double 	fSlow0 = double(fslider0);
	double 	fSlow1 = (2.9448437500000003e-06 * fSlow0);
	double 	fSlow2 = exp((3.4 * (double(fslider1) - 1)));
	double 	fSlow3 = ((0.00011998125000000002 * fSlow2) + (fSlow0 * ((2.9448437500000007e-05 * fSlow2) - (8.731718750000001e-06 + fSlow1))));
	double 	fSlow4 = (1.2916875000000002e-05 + fSlow3);
	double 	fSlow5 = (2.5703125000000003e-10 * fSlow0);
	double 	fSlow6 = (2.5703125000000004e-09 * fSlow2);
	double 	fSlow7 = (7.343750000000001e-09 * fSlow2);
	double 	fSlow8 = (7.343750000000001e-10 + (fSlow7 + (fSlow0 * (fSlow6 - (fSlow5 + 4.773437500000001e-10)))));
	double 	fSlow9 = (fConst1 * fSlow8);
	double 	fSlow10 = (0.0250625 * fSlow2);
	double 	fSlow11 = (0.001175 * fSlow0);
	double 	fSlow12 = (fConst1 * (0.01726875 + (fSlow11 + fSlow10)));
	double 	fSlow13 = ((fSlow12 + (fConst2 * (fSlow9 - fSlow4))) - 1);
	double 	fSlow14 = (fConst3 * fSlow8);
	double 	fSlow15 = ((fSlow12 + (fConst2 * (fSlow4 - fSlow14))) - 3);
	double 	fSlow16 = ((fConst2 * (1.2916875000000002e-05 + (fSlow3 + fSlow14))) - (3 + fSlow12));
	double 	fSlow17 = (1.0 / (0 - (1 + (fSlow12 + (fConst2 * (1.2916875000000002e-05 + (fSlow3 + fSlow9)))))));
	double 	fSlow18 = double(fslider2);
	double 	fSlow19 = ((fSlow10 + (fSlow11 + (6.25e-05 * fSlow18))) + 0.0025062500000000002);
	double 	fSlow20 = (fConst1 * fSlow19);
	double 	fSlow21 = ((fSlow0 * ((2.5703125000000003e-10 + fSlow6) - fSlow5)) + (fSlow18 * ((7.343750000000001e-10 + fSlow7) - (7.343750000000001e-10 * fSlow0))));
	double 	fSlow22 = (fConst1 * fSlow21);
	double 	fSlow23 = (((9.187500000000001e-07 * fSlow18) + (fSlow0 * (3.0182812500000004e-06 - fSlow1))) + (fSlow2 * (2.48125e-06 + (2.9448437500000007e-05 * fSlow0))));
	double 	fSlow24 = (fSlow23 + 2.48125e-07);
	double 	fSlow25 = ((fConst2 * (0 - (fSlow24 - fSlow22))) + fSlow20);
	double 	fSlow26 = (fConst3 * fSlow21);
	double 	fSlow27 = (fSlow20 + (fConst2 * (fSlow24 - fSlow26)));
	double 	fSlow28 = (fConst1 * (0 - fSlow19));
	double 	fSlow29 = (fSlow28 + (fConst2 * (2.48125e-07 + (fSlow23 + fSlow26))));
	double 	fSlow30 = (fSlow28 - (fConst2 * (2.48125e-07 + (fSlow23 + fSlow22))));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((double)input0[i] - (fSlow17 * (((fSlow16 * fRec0[1]) + (fSlow15 * fRec0[2])) + (fSlow13 * fRec0[3]))));
		output0[i] = (FAUSTFLOAT)(fSlow17 * ((((fSlow30 * fRec0[0]) + (fSlow29 * fRec0[1])) + (fSlow27 * fRec0[2])) + (fSlow25 * fRec0[3])));
		// post processing
		for (int i=3; i>0; i--) fRec0[i] = fRec0[i-1];
	}
#undef fslider0
#undef fslider1
#undef fslider2
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

} // end namespace tonestack_mesa
