// generated from file '../src/LV2/faust/tonestack_roland.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace tonestack_roland {

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
	id = "Roland";
	name = N_("Roland");
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
	fConst2 = (6 * fConst0);
	fConst3 = faustpower<2>(fConst1);
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
	double 	fSlow0 = exp((3.4 * (double(fslider0) - 1)));
	double 	fSlow1 = (0.00831 * fSlow0);
	double 	fSlow2 = double(fslider1);
	double 	fSlow3 = (0.0008200000000000001 * fSlow2);
	double 	fSlow4 = (fConst1 * (0.005107400000000001 + (fSlow3 + fSlow1)));
	double 	fSlow5 = (1.8898704000000002e-11 * fSlow2);
	double 	fSlow6 = (4.724676000000001e-10 * fSlow0);
	double 	fSlow7 = (1.6641900000000002e-09 * fSlow0);
	double 	fSlow8 = (6.656760000000001e-11 + (fSlow7 + (fSlow2 * (fSlow6 - (fSlow5 + 4.7668896000000004e-11)))));
	double 	fSlow9 = (fConst2 * fSlow8);
	double 	fSlow10 = (2.7256800000000006e-07 * fSlow2);
	double 	fSlow11 = ((2.851440000000001e-05 * fSlow0) + (fSlow2 * ((6.8142000000000025e-06 * fSlow0) - (7.876920000000001e-07 + fSlow10))));
	double 	fSlow12 = ((fConst3 * (1.4234760000000002e-06 + (fSlow11 + fSlow9))) - (3 + fSlow4));
	double 	fSlow13 = (1.4234760000000002e-06 + fSlow11);
	double 	fSlow14 = (fConst1 * fSlow8);
	double 	fSlow15 = ((fSlow4 + (fConst3 * (fSlow14 - fSlow13))) - 1);
	double 	fSlow16 = ((fSlow4 + (fConst3 * (fSlow13 - fSlow9))) - 3);
	double 	fSlow17 = (1.0 / (0 - (1 + (fSlow4 + (fConst3 * (1.4234760000000002e-06 + (fSlow11 + fSlow14)))))));
	double 	fSlow18 = double(fslider2);
	double 	fSlow19 = ((fSlow2 * ((1.8898704000000002e-11 + fSlow6) - fSlow5)) + (fSlow18 * ((6.656760000000001e-11 + fSlow7) - (6.656760000000001e-11 * fSlow2))));
	double 	fSlow20 = (fConst1 * fSlow19);
	double 	fSlow21 = (((2.829e-07 * fSlow18) + (fSlow2 * (3.2176800000000005e-07 - fSlow10))) + (fSlow0 * (7.779000000000002e-07 + (6.8142000000000025e-06 * fSlow2))));
	double 	fSlow22 = (fSlow21 + 3.1116000000000005e-08);
	double 	fSlow23 = ((fSlow1 + (fSlow3 + (6e-05 * fSlow18))) + 0.00033240000000000006);
	double 	fSlow24 = (fConst1 * fSlow23);
	double 	fSlow25 = (fSlow24 + (fConst3 * (0 - (fSlow22 - fSlow20))));
	double 	fSlow26 = (fConst2 * fSlow19);
	double 	fSlow27 = (fSlow24 + (fConst3 * (fSlow22 - fSlow26)));
	double 	fSlow28 = (fConst1 * (0 - fSlow23));
	double 	fSlow29 = (fSlow28 + (fConst3 * (3.1116000000000005e-08 + (fSlow21 + fSlow26))));
	double 	fSlow30 = (fSlow28 - (fConst3 * (3.1116000000000005e-08 + (fSlow21 + fSlow20))));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((double)input0[i] - (fSlow17 * ((fSlow16 * fRec0[2]) + ((fSlow15 * fRec0[3]) + (fSlow12 * fRec0[1])))));
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
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case MIDDLE: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
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

} // end namespace tonestack_roland
