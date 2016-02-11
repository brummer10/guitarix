// generated from file '../src/LV2/faust/phaser_mono.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace phaser_mono {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	int 	iConst0;
	float 	fConst1;
	float 	fRec1[2];
	float 	fRec2[2];
	float 	fConst2;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	float 	fConst3;
	float 	fConst4;
	float 	fConst5;
	float 	fConst6;
	float 	fRec6[3];
	float 	fConst7;
	float 	fRec5[3];
	float 	fConst8;
	float 	fRec4[3];
	float 	fRec3[3];
	float 	fRec0[2];
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
	id = "phaser_mono";
	name = N_("Phaser Mono");
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (6.283185307179586f / float(iConst0));
	fConst2 = (16.0f / float(iConst0));
	fConst3 = expf((0 - (3141.592653589793f / float(iConst0))));
	fConst4 = faustpower<2>(fConst3);
	fConst5 = (2.0f / float(iConst0));
	fConst6 = (0 - (2 * fConst3));
	fConst7 = (4.0f / float(iConst0));
	fConst8 = (8.0f / float(iConst0));
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
	float 	fSlow0 = (fConst1 * float(fslider0));
	float 	fSlow1 = cosf(fSlow0);
	float 	fSlow2 = sinf(fSlow0);
	float 	fSlow3 = (0 - fSlow2);
	float 	fSlow4 = float(fslider2);
	float 	fSlow5 = (0.01f * (fSlow4 * powf(10,(0.05f * float(fslider1)))));
	float 	fSlow6 = (1 - (0.01f * fSlow4));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec1[0] = ((fSlow2 * fRec2[1]) + (fSlow1 * fRec1[1]));
		fRec2[0] = ((1 + ((fSlow1 * fRec2[1]) + (fSlow3 * fRec1[1]))) - iVec0[1]);
		float fTemp0 = (628.3185307179587f + (2199.1148575128555f * (1 - fRec1[0])));
		float fTemp1 = (float)input0[i];
		float fTemp2 = (fRec6[1] * cosf((fConst5 * fTemp0)));
		fRec6[0] = (0 - (((fConst6 * fTemp2) + (fConst4 * fRec6[2])) - ((fSlow5 * fTemp1) + (0.5f * fRec0[1]))));
		float fTemp3 = (fRec5[1] * cosf((fConst7 * fTemp0)));
		fRec5[0] = ((fConst6 * (fTemp2 - fTemp3)) + (fRec6[2] + (fConst4 * (fRec6[0] - fRec5[2]))));
		float fTemp4 = (fRec4[1] * cosf((fConst8 * fTemp0)));
		fRec4[0] = ((fConst6 * (fTemp3 - fTemp4)) + (fRec5[2] + (fConst4 * (fRec5[0] - fRec4[2]))));
		float fTemp5 = (fRec3[1] * cosf((fConst2 * fTemp0)));
		fRec3[0] = ((fConst6 * (fTemp4 - fTemp5)) + (fRec4[2] + (fConst4 * (fRec4[0] - fRec3[2]))));
		fRec0[0] = ((fConst4 * fRec3[0]) + (fRec3[2] + (fConst6 * fTemp5)));
		output0[i] = (FAUSTFLOAT)((fSlow6 * fTemp1) - fRec0[0]);
		// post processing
		fRec0[1] = fRec0[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		iVec0[1] = iVec0[0];
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
	case SPEED: 
		fslider0_ = (float*)data; // , 0.5f, 0.0f, 1e+01f, 0.01f 
		break;
	case LEVEL: 
		fslider1_ = (float*)data; // , 0.0f, -6e+01f, 1e+01f, 0.1f 
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
   SPEED, 
   LEVEL, 
   WET_DRY, 
} PortIndex;
*/

} // end namespace phaser_mono
