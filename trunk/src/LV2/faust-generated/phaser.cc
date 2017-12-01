// generated from file '../src/LV2/faust/phaser.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace phaser {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	float 	fConst0;
	float 	fConst1;
	float 	fRec2[2];
	float 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	float 	fConst2;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT	*fslider6_;
	float 	fRec6[3];
	float 	fRec5[3];
	float 	fRec4[3];
	float 	fRec1[3];
	float 	fRec0[2];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT	*fslider7_;
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT	*fcheckbox0_;
	FAUSTFLOAT 	fcheckbox1;
	FAUSTFLOAT	*fcheckbox1_;
	float 	fRec11[3];
	float 	fRec10[3];
	float 	fRec9[3];
	float 	fRec8[3];
	float 	fRec7[2];

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
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
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
	fConst0 = min(1.92e+05f, max(1.0f, (float)fSamplingFreq));
	fConst1 = (6.2831855f / fConst0);
	fConst2 = (1.0f / fConst0);
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
#define fslider3 (*fslider3_)
#define fslider4 (*fslider4_)
#define fslider5 (*fslider5_)
#define fslider6 (*fslider6_)
#define fslider7 (*fslider7_)
#define fcheckbox0 (*fcheckbox0_)
#define fcheckbox1 (*fcheckbox1_)
	float 	fSlow0 = (fConst1 * float(fslider0));
	float 	fSlow1 = cosf(fSlow0);
	float 	fSlow2 = sinf(fSlow0);
	float 	fSlow3 = (0 - fSlow2);
	float 	fSlow4 = float(fslider1);
	float 	fSlow5 = (6.2831855f * fSlow4);
	float 	fSlow6 = (0.5f * ((6.2831855f * max(fSlow4, float(fslider2))) - fSlow5));
	float 	fSlow7 = float(fslider3);
	float 	fSlow8 = (fConst2 * faustpower<4>(fSlow7));
	float 	fSlow9 = (fConst2 * faustpower<3>(fSlow7));
	float 	fSlow10 = (fConst2 * faustpower<2>(fSlow7));
	float 	fSlow11 = float(fslider4);
	float 	fSlow12 = powf(10,(0.05f * float(fslider5)));
	float 	fSlow13 = (fConst2 * fSlow7);
	float 	fSlow14 = expf((fConst2 * (0 - (3.1415927f * float(fslider6)))));
	float 	fSlow15 = (0 - (2 * fSlow14));
	float 	fSlow16 = faustpower<2>(fSlow14);
	float 	fSlow17 = (0.5f * ((int(float(fcheckbox0)))?2:float(fslider7)));
	float 	fSlow18 = ((int(float(fcheckbox1)))?(0 - fSlow17):fSlow17);
	float 	fSlow19 = (1 - fSlow17);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec2[0] = ((fSlow2 * fRec3[1]) + (fSlow1 * fRec2[1]));
		fRec3[0] = ((1 + ((fSlow1 * fRec3[1]) + (fSlow3 * fRec2[1]))) - iVec0[1]);
		float fTemp0 = (fSlow5 + (fSlow6 * (1 - fRec2[0])));
		float fTemp1 = (fRec1[1] * cosf((fSlow8 * fTemp0)));
		float fTemp2 = (cosf((fSlow9 * fTemp0)) * fRec4[1]);
		float fTemp3 = (cosf((fSlow10 * fTemp0)) * fRec5[1]);
		float fTemp4 = (float)input0[i];
		float fTemp5 = (cosf((fSlow13 * fTemp0)) * fRec6[1]);
		fRec6[0] = (0 - (((fSlow16 * fRec6[2]) + (fSlow15 * fTemp5)) - ((fSlow12 * fTemp4) + (fSlow11 * fRec0[1]))));
		fRec5[0] = ((fRec6[2] + (fSlow16 * (fRec6[0] - fRec5[2]))) + (fSlow15 * (fTemp5 - fTemp3)));
		fRec4[0] = ((fRec5[2] + (fSlow16 * (fRec5[0] - fRec4[2]))) + (fSlow15 * (fTemp3 - fTemp2)));
		fRec1[0] = ((fSlow16 * (fRec4[0] - fRec1[2])) + (fRec4[2] + (fSlow15 * (fTemp2 - fTemp1))));
		fRec0[0] = ((fSlow15 * fTemp1) + (fRec1[2] + (fSlow16 * fRec1[0])));
		output0[i] = (FAUSTFLOAT)((fSlow12 * (fTemp4 * fSlow19)) + (fSlow18 * fRec0[0]));
		float fTemp6 = (fSlow5 + (fSlow6 * (1 - fRec3[0])));
		float fTemp7 = (fRec8[1] * cosf((fSlow8 * fTemp6)));
		float fTemp8 = (cosf((fSlow9 * fTemp6)) * fRec9[1]);
		float fTemp9 = (cosf((fSlow10 * fTemp6)) * fRec10[1]);
		float fTemp10 = (float)input1[i];
		float fTemp11 = (cosf((fSlow13 * fTemp6)) * fRec11[1]);
		fRec11[0] = (0 - (((fSlow16 * fRec11[2]) + (fSlow15 * fTemp11)) - ((fSlow12 * fTemp10) + (fSlow11 * fRec7[1]))));
		fRec10[0] = ((fRec11[2] + (fSlow16 * (fRec11[0] - fRec10[2]))) + (fSlow15 * (fTemp11 - fTemp9)));
		fRec9[0] = ((fRec10[2] + (fSlow16 * (fRec10[0] - fRec9[2]))) + (fSlow15 * (fTemp9 - fTemp8)));
		fRec8[0] = ((fSlow16 * (fRec9[0] - fRec8[2])) + (fRec9[2] + (fSlow15 * (fTemp8 - fTemp7))));
		fRec7[0] = ((fSlow15 * fTemp7) + (fRec8[2] + (fSlow16 * fRec8[0])));
		output1[i] = (FAUSTFLOAT)((fSlow12 * (fTemp10 * fSlow19)) + (fSlow18 * fRec7[0]));
		// post processing
		fRec7[1] = fRec7[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
#undef fslider4
#undef fslider5
#undef fslider6
#undef fslider7
#undef fcheckbox0
#undef fcheckbox1
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case MAXNOTCH1FREQ: 
		fslider2_ = (float*)data; // , 8e+02f, 2e+01f, 1e+04f, 1.0f 
		break;
	case MINNOTCH1FREQ: 
		fslider1_ = (float*)data; // , 1e+02f, 2e+01f, 5e+03f, 1.0f 
		break;
	case NOTCHWIDTH: 
		fslider6_ = (float*)data; // , 1e+03f, 1e+01f, 5e+03f, 1.0f 
		break;
	case NOTCHFREQ: 
		fslider3_ = (float*)data; // , 1.5f, 1.1f, 4.0f, 0.01f 
		break;
	case SPEED: 
		fslider0_ = (float*)data; // , 0.5f, 0.0f, 1e+01f, 0.01f 
		break;
	// static const value_pair fcheckbox0_values[] = {{"direct "},{" vibrato"},{0}};
	case VIBRATOMODE: 
		fcheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case DEPTH: 
		fslider7_ = (float*)data; // , 1.0f, 0.0f, 1.0f, 0.01f 
		break;
	case FEEDBACKGAIN: 
		fslider4_ = (float*)data; // , 0.0f, 0.0f, 1.0f, 0.01f 
		break;
	// static const value_pair fcheckbox1_values[] = {{"linear"},{"invert"},{0}};
	case INVERT: 
		fcheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case LEVEL: 
		fslider5_ = (float*)data; // , 0.0f, -6e+01f, 1e+01f, 0.1f 
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
