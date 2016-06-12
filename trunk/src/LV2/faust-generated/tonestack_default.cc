// generated from file '../src/LV2/faust/tonestack_default.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace tonestack_default {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fVec0[3];
	double 	fRec3[3];
	double 	fRec2[3];
	double 	fRec1[3];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec0[3];
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
	id = "default";
	name = N_("default");
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
	for (int i=0; i<3; i++) fVec0[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (15079.644737231007 / double(iConst0));
	fConst2 = (1.4142135623730951 * sin(fConst1));
	fConst3 = cos(fConst1);
	fConst4 = (3769.9111843077517 / double(iConst0));
	fConst5 = (1.4142135623730951 * sin(fConst4));
	fConst6 = cos(fConst4);
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
	double 	fSlow0 = (double(fslider0) - 0.5);
	double 	fSlow1 = pow(10,(0.25 * fSlow0));
	double 	fSlow2 = sqrt(fSlow1);
	double 	fSlow3 = (fConst2 * fSlow2);
	double 	fSlow4 = (fSlow1 - 1);
	double 	fSlow5 = (fConst3 * fSlow4);
	double 	fSlow6 = (fSlow1 + fSlow5);
	double 	fSlow7 = ((1 + fSlow6) - fSlow3);
	double 	fSlow8 = (1 + fSlow1);
	double 	fSlow9 = (fConst3 * fSlow8);
	double 	fSlow10 = (0 - (2 * ((fSlow1 + fSlow9) - 1)));
	double 	fSlow11 = (10 * fSlow0);
	double 	fSlow12 = pow(10,(0.025 * ((20 * (exp((3.4 * (double(fslider1) - 1))) - 0.5)) - fSlow11)));
	double 	fSlow13 = (fConst5 * sqrt(fSlow12));
	double 	fSlow14 = (fConst6 * (fSlow12 - 1));
	double 	fSlow15 = (fSlow12 + fSlow14);
	double 	fSlow16 = ((1 + fSlow15) - fSlow13);
	double 	fSlow17 = (1 + fSlow12);
	double 	fSlow18 = (fConst6 * fSlow17);
	double 	fSlow19 = (0 - (2 * ((fSlow12 + fSlow18) - 1)));
	double 	fSlow20 = (fSlow17 - (fSlow14 + fSlow13));
	double 	fSlow21 = (2 * (0 - ((1 + fSlow18) - fSlow12)));
	double 	fSlow22 = ((1 + (fSlow12 + fSlow13)) - fSlow14);
	double 	fSlow23 = (1.0 / (1 + (fSlow13 + fSlow15)));
	double 	fSlow24 = (fSlow8 - (fSlow5 + fSlow3));
	double 	fSlow25 = (2 * (0 - ((1 + fSlow9) - fSlow1)));
	double 	fSlow26 = ((1 + (fSlow1 + fSlow3)) - fSlow5);
	double 	fSlow27 = (1.0 / (1 + (fSlow3 + fSlow6)));
	double 	fSlow28 = (fConst5 * fSlow2);
	double 	fSlow29 = (fConst6 * fSlow4);
	double 	fSlow30 = (fSlow1 + fSlow29);
	double 	fSlow31 = (fSlow1 * ((1 + fSlow30) - fSlow28));
	double 	fSlow32 = (fConst6 * fSlow8);
	double 	fSlow33 = ((0 - (2 * fSlow1)) * ((fSlow1 + fSlow32) - 1));
	double 	fSlow34 = (fSlow1 * (1 + (fSlow30 + fSlow28)));
	double 	fSlow35 = (2 * (0 - ((1 + fSlow32) - fSlow1)));
	double 	fSlow36 = (fSlow8 - (fSlow29 + fSlow28));
	double 	fSlow37 = (1.0 / ((1 + (fSlow1 + fSlow28)) - fSlow29));
	double 	fSlow38 = pow(10,(0.025 * ((20 * (double(fslider2) - 0.5)) - fSlow11)));
	double 	fSlow39 = (fConst2 * sqrt(fSlow38));
	double 	fSlow40 = (fConst3 * (fSlow38 - 1));
	double 	fSlow41 = (fSlow38 + fSlow40);
	double 	fSlow42 = (fSlow38 * ((1 + fSlow41) - fSlow39));
	double 	fSlow43 = (1 + fSlow38);
	double 	fSlow44 = (fConst3 * fSlow43);
	double 	fSlow45 = ((0 - (2 * fSlow38)) * ((fSlow38 + fSlow44) - 1));
	double 	fSlow46 = (fSlow38 * (1 + (fSlow41 + fSlow39)));
	double 	fSlow47 = (2 * (0 - ((1 + fSlow44) - fSlow38)));
	double 	fSlow48 = (fSlow43 - (fSlow40 + fSlow39));
	double 	fSlow49 = (1.0 / ((1 + (fSlow38 + fSlow39)) - fSlow40));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec3[0] = (fSlow23 * ((fSlow12 * (((fSlow22 * fVec0[0]) + (fSlow21 * fVec0[1])) + (fSlow20 * fVec0[2]))) - ((fSlow19 * fRec3[1]) + (fSlow16 * fRec3[2]))));
		fRec2[0] = (fSlow27 * ((fSlow1 * (((fSlow26 * fRec3[0]) + (fSlow25 * fRec3[1])) + (fSlow24 * fRec3[2]))) - ((fSlow10 * fRec2[1]) + (fSlow7 * fRec2[2]))));
		fRec1[0] = (fSlow37 * ((0 - ((fSlow36 * fRec1[2]) + (fSlow35 * fRec1[1]))) + (((fSlow34 * fRec2[0]) + (fSlow33 * fRec2[1])) + (fSlow31 * fRec2[2]))));
		fRec0[0] = (fSlow49 * ((0 - ((fSlow48 * fRec0[2]) + (fSlow47 * fRec0[1]))) + (((fSlow46 * fRec1[0]) + (fSlow45 * fRec1[1])) + (fSlow42 * fRec1[2]))));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fVec0[2] = fVec0[1]; fVec0[1] = fVec0[0];
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

} // end namespace tonestack_default
