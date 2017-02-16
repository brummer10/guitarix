// generated from file '../src/LV2/faust/phaser_mono.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace phaser_mono {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	int 	iConst0;
	float 	fConst1;
	float 	fConst2;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	float 	fConst3;
	float 	fRec5[2];
	float 	fRec6[2];
	float 	fConst4;
	float 	fConst5;
	float 	fRec4[3];
	float 	fConst6;
	float 	fRec3[3];
	float 	fConst7;
	float 	fRec2[3];
	float 	fConst8;
	float 	fRec1[3];
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
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
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
	fConst1 = expf((0 - (3141.592653589793f / float(iConst0))));
	fConst2 = faustpower<2>(fConst1);
	fConst3 = (6.283185307179586f / float(iConst0));
	fConst4 = (2.0f / float(iConst0));
	fConst5 = (0 - (2 * fConst1));
	fConst6 = (4.0f / float(iConst0));
	fConst7 = (8.0f / float(iConst0));
	fConst8 = (16.0f / float(iConst0));
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
	float 	fSlow0 = float(fslider1);
	float 	fSlow1 = (0.01f * (fSlow0 * powf(10,(0.05f * float(fslider0)))));
	float 	fSlow2 = (fConst3 * float(fslider2));
	float 	fSlow3 = cosf(fSlow2);
	float 	fSlow4 = sinf(fSlow2);
	float 	fSlow5 = (0 - fSlow4);
	float 	fSlow6 = (1 - (0.01f * fSlow0));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		float fTemp0 = (float)input0[i];
		fRec5[0] = ((fSlow4 * fRec6[1]) + (fSlow3 * fRec5[1]));
		fRec6[0] = ((1 + ((fSlow3 * fRec6[1]) + (fSlow5 * fRec5[1]))) - iVec0[1]);
		float fTemp1 = (628.3185307179587f + (2199.1148575128555f * (1 - fRec5[0])));
		float fTemp2 = (fRec4[1] * cosf((fConst4 * fTemp1)));
		fRec4[0] = (0 - (((fConst5 * fTemp2) + (fConst2 * fRec4[2])) - ((fSlow1 * fTemp0) + (0.5f * fRec0[1]))));
		float fTemp3 = (fRec3[1] * cosf((fConst6 * fTemp1)));
		fRec3[0] = ((fConst5 * (fTemp2 - fTemp3)) + (fRec4[2] + (fConst2 * (fRec4[0] - fRec3[2]))));
		float fTemp4 = (fRec2[1] * cosf((fConst7 * fTemp1)));
		fRec2[0] = ((fConst5 * (fTemp3 - fTemp4)) + (fRec3[2] + (fConst2 * (fRec3[0] - fRec2[2]))));
		float fTemp5 = (fRec1[1] * cosf((fConst8 * fTemp1)));
		fRec1[0] = ((fConst5 * (fTemp4 - fTemp5)) + (fRec2[2] + (fConst2 * (fRec2[0] - fRec1[2]))));
		fRec0[0] = ((fConst2 * fRec1[0]) + ((fConst5 * fTemp5) + fRec1[2]));
		output0[i] = (FAUSTFLOAT)((fSlow6 * fTemp0) - fRec0[0]);
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
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
		fslider2_ = (float*)data; // , 0.5f, 0.0f, 1e+01f, 0.01f 
		break;
	case LEVEL: 
		fslider0_ = (float*)data; // , 0.0f, -6e+01f, 1e+01f, 0.1f 
		break;
	case WET_DRY: 
		fslider1_ = (float*)data; // , 1e+02f, 0.0f, 1e+02f, 1.0f 
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
