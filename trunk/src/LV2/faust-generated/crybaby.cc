// generated from file '../src/LV2/faust/crybaby.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace crybaby {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	float 	fConst0;
	float 	fConst1;
	float 	fRec1[2];
	float 	fConst2;
	float 	fRec2[2];
	float 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	float 	fRec0[3];

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
	id = "manual";
	name = N_("manual");
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
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05f, max(1.0f, (float)fSamplingFreq));
	fConst1 = (1413.7167f / fConst0);
	fConst2 = (2827.4333f / fConst0);
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
	float 	fSlow0 = float(fslider0);
	float 	fSlow1 = powf(2.0f,(2.3f * fSlow0));
	float 	fSlow2 = (1 - (fConst1 * (fSlow1 / powf(2.0f,(1.0f + (2.0f * (1.0f - fSlow0)))))));
	float 	fSlow3 = (0.001f * faustpower<2>(fSlow2));
	float 	fSlow4 = (0.001f * (0 - (2.0f * (fSlow2 * cosf((fConst2 * fSlow1))))));
	float 	fSlow5 = (0.0001f * powf(4.0f,fSlow0));
	float 	fSlow6 = float(fslider2);
	float 	fSlow7 = (0.01f * (fSlow6 * float(fslider1)));
	float 	fSlow8 = (1 - (0.01f * fSlow6));
	for (int i=0; i<count; i++) {
		fRec1[0] = (fSlow3 + (0.999f * fRec1[1]));
		fRec2[0] = (fSlow4 + (0.999f * fRec2[1]));
		fRec3[0] = (fSlow5 + (0.999f * fRec3[1]));
		float fTemp0 = (float)input0[i];
		fRec0[0] = ((fSlow7 * (fTemp0 * fRec3[0])) - (0.996f * ((fRec0[1] * fRec2[0]) + (fRec0[2] * fRec1[0]))));
		output0[i] = (FAUSTFLOAT)(((fSlow8 * fTemp0) + fRec0[0]) - (0.996f * fRec0[1]));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
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
	case LEVEL: 
		fslider1_ = (float*)data; // , 0.1f, 0.0f, 1.0f, 0.01f 
		break;
	case WAH: 
		fslider0_ = (float*)data; // , 0.0f, 0.0f, 1.0f, 0.01f 
		break;
	case WET_DRY: 
		fslider2_ = (float*)data; // , 1e+02f, 0.0f, 1e+02f, 1.0f 
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
   LEVEL, 
   WAH, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace crybaby
