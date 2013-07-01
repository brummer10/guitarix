// generated from file '../src/LV2/faust/phaser.dsp' by dsp2cc:
// Code generated with Faust 0.9.58 (http://faust.grame.fr)


namespace phaser {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	FAUSTFLOAT 	fcheckbox1;
	FAUSTFLOAT	*fcheckbox1_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	int 	iConst0;
	float 	fConst1;
	float 	fRec1[2];
	float 	fRec2[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	float 	fConst2;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT	*fslider7_;
	float 	fRec6[3];
	float 	fRec5[3];
	float 	fRec4[3];
	float 	fRec3[3];
	float 	fRec0[2];
	float 	fRec11[3];
	float 	fRec10[3];
	float 	fRec9[3];
	float 	fRec8[3];
	float 	fRec7[2];
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
	id = "phaser";
	name = N_("Phaser");
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
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
	fConst2 = (1.0f / float(iConst0));
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, float *input0, float *input1, float *output0, float *output1)
{
#define fslider0 (*fslider0_)
#define fcheckbox0 (*fcheckbox0_)
#define fslider1 (*fslider1_)
#define fcheckbox1 (*fcheckbox1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
#define fslider4 (*fslider4_)
#define fslider5 (*fslider5_)
#define fslider6 (*fslider6_)
#define fslider7 (*fslider7_)
	float 	fSlow0 = (0.5f * ((int(fcheckbox0))?2:fslider0));
	float 	fSlow1 = (1 - fSlow0);
	float 	fSlow2 = powf(10,(0.05f * fslider1));
	float 	fSlow3 = ((int(fcheckbox1))?(0 - fSlow0):fSlow0);
	float 	fSlow4 = (fConst1 * fslider2);
	float 	fSlow5 = sinf(fSlow4);
	float 	fSlow6 = cosf(fSlow4);
	float 	fSlow7 = (0 - fSlow5);
	float 	fSlow8 = fslider3;
	float 	fSlow9 = (6.283185307179586f * fSlow8);
	float 	fSlow10 = (0.5f * ((6.283185307179586f * max(fSlow8, fslider4)) - fSlow9));
	float 	fSlow11 = fslider5;
	float 	fSlow12 = (fConst2 * faustpower<4>(fSlow11));
	float 	fSlow13 = fslider6;
	float 	fSlow14 = (fConst2 * fSlow11);
	float 	fSlow15 = expf((fConst2 * (0 - (3.141592653589793f * fslider7))));
	float 	fSlow16 = (0 - (2 * fSlow15));
	float 	fSlow17 = faustpower<2>(fSlow15);
	float 	fSlow18 = (fConst2 * faustpower<2>(fSlow11));
	float 	fSlow19 = (fConst2 * faustpower<3>(fSlow11));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		float fTemp0 = (float)input0[i];
		fRec1[0] = ((fSlow6 * fRec1[1]) + (fSlow5 * fRec2[1]));
		fRec2[0] = ((1 + ((fSlow7 * fRec1[1]) + (fSlow6 * fRec2[1]))) - iVec0[1]);
		float fTemp1 = (fSlow9 + (fSlow10 * (1 - fRec1[0])));
		float fTemp2 = (fRec6[1] * cosf((fSlow14 * fTemp1)));
		fRec6[0] = (0 - (((fSlow17 * fRec6[2]) + (fSlow16 * fTemp2)) - ((fSlow2 * fTemp0) + (fSlow13 * fRec0[1]))));
		float fTemp3 = (fRec5[1] * cosf((fSlow18 * fTemp1)));
		fRec5[0] = ((fSlow16 * (fTemp2 - fTemp3)) + (fRec6[2] + (fSlow17 * (fRec6[0] - fRec5[2]))));
		float fTemp4 = (fRec4[1] * cosf((fSlow19 * fTemp1)));
		fRec4[0] = ((fSlow16 * (fTemp3 - fTemp4)) + (fRec5[2] + (fSlow17 * (fRec5[0] - fRec4[2]))));
		float fTemp5 = (fRec3[1] * cosf((fSlow12 * fTemp1)));
		fRec3[0] = ((fSlow16 * (fTemp4 - fTemp5)) + (fRec4[2] + (fSlow17 * (fRec4[0] - fRec3[2]))));
		fRec0[0] = ((fSlow17 * fRec3[0]) + (fRec3[2] + (fSlow16 * fTemp5)));
		output0[i] = (FAUSTFLOAT)((fRec0[0] * fSlow3) + (fSlow2 * (fTemp0 * fSlow1)));
		float fTemp6 = (float)input1[i];
		float fTemp7 = (fSlow9 + (fSlow10 * (1 - fRec2[0])));
		float fTemp8 = (fRec11[1] * cosf((fSlow14 * fTemp7)));
		fRec11[0] = (0 - (((fSlow17 * fRec11[2]) + (fSlow16 * fTemp8)) - ((fSlow2 * fTemp6) + (fSlow13 * fRec7[1]))));
		float fTemp9 = (fRec10[1] * cosf((fSlow18 * fTemp7)));
		fRec10[0] = ((fSlow16 * (fTemp8 - fTemp9)) + (fRec11[2] + (fSlow17 * (fRec11[0] - fRec10[2]))));
		float fTemp10 = (fRec9[1] * cosf((fSlow19 * fTemp7)));
		fRec9[0] = ((fSlow16 * (fTemp9 - fTemp10)) + (fRec10[2] + (fSlow17 * (fRec10[0] - fRec9[2]))));
		float fTemp11 = (fRec8[1] * cosf((fSlow12 * fTemp7)));
		fRec8[0] = ((fSlow16 * (fTemp10 - fTemp11)) + (fRec9[2] + (fSlow17 * (fRec9[0] - fRec8[2]))));
		fRec7[0] = ((fSlow17 * fRec8[0]) + (fRec8[2] + (fSlow16 * fTemp11)));
		output1[i] = (FAUSTFLOAT)((fRec7[0] * fSlow3) + (fSlow2 * (fTemp6 * fSlow1)));
		// post processing
		fRec7[1] = fRec7[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
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
#undef fcheckbox0
#undef fslider1
#undef fcheckbox1
#undef fslider2
#undef fslider3
#undef fslider4
#undef fslider5
#undef fslider6
#undef fslider7
}

void __rt_func Dsp::compute_static(int count, float *input0, float *input1, float *output0, float *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case MAXNOTCH1FREQ: 
		fslider4_ = (float*)data; // , 8e+02f, 2e+01f, 1e+04f, 1.0f 
		break;
	case MINNOTCH1FREQ: 
		fslider3_ = (float*)data; // , 1e+02f, 2e+01f, 5e+03f, 1.0f 
		break;
	case NOTCHWIDTH: 
		fslider7_ = (float*)data; // , 1e+03f, 1e+01f, 5e+03f, 1.0f 
		break;
	case NOTCHFREQ: 
		fslider5_ = (float*)data; // , 1.5f, 1.1f, 4.0f, 0.01f 
		break;
	case SPEED: 
		fslider2_ = (float*)data; // , 0.5f, 0.0f, 1e+01f, 0.01f 
		break;
	// static const value_pair fcheckbox0_values[] = {{"direct "},{" vibrato"},{0}};
	case VIBRATOMODE: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case DEPTH: 
		fslider0_ = (float*)data; // , 1.0f, 0.0f, 1.0f, 0.01f 
		break;
	case FEEDBACKGAIN: 
		fslider6_ = (float*)data; // , 0.0f, 0.0f, 1.0f, 0.01f 
		break;
	// static const value_pair fcheckbox1_values[] = {{"linear"},{"invert"},{0}};
	case INVERT: 
		fcheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case LEVEL: 
		fslider1_ = (float*)data; // , 0.0f, -6e+01f, 1e+01f, 0.1f 
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
   MAXNOTCH1FREQ, 
   MINNOTCH1FREQ, 
   NOTCHWIDTH, 
   NOTCHFREQ, 
   SPEED, 
   VIBRATOMODE, 
   DEPTH, 
   FEEDBACKGAIN, 
   INVERT, 
   LEVEL, 
} PortIndex;
*/

} // end namespace phaser
