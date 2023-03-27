// generated from file '../src/LV2/faust/phaser.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace phaser {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	int iVec0[2];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	float fConst1;
	float fRec2[2];
	float fRec3[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT	*fHslider2_;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT	*fHslider3_;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT	*fHslider4_;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT	*fHslider5_;
	float fConst2;
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT	*fHslider6_;
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT	*fHslider7_;
	float fRec6[3];
	float fRec5[3];
	float fRec4[3];
	float fRec1[3];
	float fRec0[2];
	float fRec11[3];
	float fRec10[3];
	float fRec9[3];
	float fRec8[3];
	float fRec7[2];

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) iVec0[l0] = 0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec2[l1] = 0.0f;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec3[l2] = 0.0f;
	for (int l3 = 0; l3 < 3; l3 = l3 + 1) fRec6[l3] = 0.0f;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRec5[l4] = 0.0f;
	for (int l5 = 0; l5 < 3; l5 = l5 + 1) fRec4[l5] = 0.0f;
	for (int l6 = 0; l6 < 3; l6 = l6 + 1) fRec1[l6] = 0.0f;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec0[l7] = 0.0f;
	for (int l8 = 0; l8 < 3; l8 = l8 + 1) fRec11[l8] = 0.0f;
	for (int l9 = 0; l9 < 3; l9 = l9 + 1) fRec10[l9] = 0.0f;
	for (int l10 = 0; l10 < 3; l10 = l10 + 1) fRec9[l10] = 0.0f;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec8[l11] = 0.0f;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec7[l12] = 0.0f;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	float fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
	fConst1 = 6.2831855f / fConst0;
	fConst2 = 1.0f / fConst0;
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fCheckbox0 (*fCheckbox0_)
#define fCheckbox1 (*fCheckbox1_)
#define fHslider0 (*fHslider0_)
#define fHslider1 (*fHslider1_)
#define fHslider2 (*fHslider2_)
#define fHslider3 (*fHslider3_)
#define fHslider4 (*fHslider4_)
#define fHslider5 (*fHslider5_)
#define fHslider6 (*fHslider6_)
#define fHslider7 (*fHslider7_)
	float fSlow0 = 0.5f * ((int(float(fCheckbox1))) ? 2.0f : float(fHslider0));
	float fSlow1 = ((int(float(fCheckbox0))) ? -1.0f * fSlow0 : fSlow0);
	float fSlow2 = fConst1 * float(fHslider1);
	float fSlow3 = std::cos(fSlow2);
	float fSlow4 = std::sin(fSlow2);
	float fSlow5 = float(fHslider2);
	float fSlow6 = 0.5f * (0.0f - fConst1 * (fSlow5 - std::max<float>(fSlow5, float(fHslider3))));
	float fSlow7 = fConst1 * fSlow5;
	float fSlow8 = float(fHslider4);
	float fSlow9 = mydsp_faustpower4_f(fSlow8);
	float fSlow10 = mydsp_faustpower3_f(fSlow8);
	float fSlow11 = mydsp_faustpower2_f(fSlow8);
	float fSlow12 = std::exp(fConst2 * (0.0f - 3.1415927f * float(fHslider5)));
	float fSlow13 = mydsp_faustpower2_f(fSlow12);
	float fSlow14 = 0.0f - 2.0f * fSlow12;
	float fSlow15 = float(fHslider6);
	float fSlow16 = std::pow(1e+01f, 0.05f * float(fHslider7));
	float fSlow17 = 1.0f - fSlow0;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		iVec0[0] = 1;
		fRec2[0] = fSlow4 * fRec3[1] + fSlow3 * fRec2[1];
		fRec3[0] = float(1 - iVec0[1]) + fSlow3 * fRec3[1] - fSlow4 * fRec2[1];
		float fTemp0 = fSlow7 + fSlow6 * (1.0f - fRec2[0]);
		float fTemp1 = fRec1[1] * std::cos(fSlow9 * fTemp0);
		float fTemp2 = fRec4[1] * std::cos(fSlow10 * fTemp0);
		float fTemp3 = fRec5[1] * std::cos(fSlow11 * fTemp0);
		float fTemp4 = fRec6[1] * std::cos(fSlow8 * fTemp0);
		float fTemp5 = float(input0[i0]);
		fRec6[0] = fSlow16 * fTemp5 + fSlow15 * fRec0[1] - (fSlow14 * fTemp4 + fSlow13 * fRec6[2]);
		fRec5[0] = fSlow13 * (fRec6[0] - fRec5[2]) + fRec6[2] + fSlow14 * (fTemp4 - fTemp3);
		fRec4[0] = fSlow13 * (fRec5[0] - fRec4[2]) + fRec5[2] + fSlow14 * (fTemp3 - fTemp2);
		fRec1[0] = fSlow13 * (fRec4[0] - fRec1[2]) + fRec4[2] + fSlow14 * (fTemp2 - fTemp1);
		fRec0[0] = fSlow13 * fRec1[0] + fSlow14 * fTemp1 + fRec1[2];
		output0[i0] = FAUSTFLOAT(fSlow16 * fTemp5 * fSlow17 + fRec0[0] * fSlow1);
		float fTemp6 = fSlow7 + fSlow6 * (1.0f - fRec3[0]);
		float fTemp7 = fRec8[1] * std::cos(fSlow9 * fTemp6);
		float fTemp8 = fRec9[1] * std::cos(fSlow10 * fTemp6);
		float fTemp9 = fRec10[1] * std::cos(fSlow11 * fTemp6);
		float fTemp10 = fRec11[1] * std::cos(fSlow8 * fTemp6);
		float fTemp11 = float(input1[i0]);
		fRec11[0] = fSlow16 * fTemp11 + fSlow15 * fRec7[1] - (fSlow14 * fTemp10 + fSlow13 * fRec11[2]);
		fRec10[0] = fSlow13 * (fRec11[0] - fRec10[2]) + fRec11[2] + fSlow14 * (fTemp10 - fTemp9);
		fRec9[0] = fSlow13 * (fRec10[0] - fRec9[2]) + fRec10[2] + fSlow14 * (fTemp9 - fTemp8);
		fRec8[0] = fSlow13 * (fRec9[0] - fRec8[2]) + fRec9[2] + fSlow14 * (fTemp8 - fTemp7);
		fRec7[0] = fSlow13 * fRec8[0] + fSlow14 * fTemp7 + fRec8[2];
		output1[i0] = FAUSTFLOAT(fSlow16 * fTemp11 * fSlow17 + fRec7[0] * fSlow1);
		iVec0[1] = iVec0[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec7[1] = fRec7[0];
	}
#undef fCheckbox0
#undef fCheckbox1
#undef fHslider0
#undef fHslider1
#undef fHslider2
#undef fHslider3
#undef fHslider4
#undef fHslider5
#undef fHslider6
#undef fHslider7
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	// static const value_pair fCheckbox1_values[] = {{"direct "},{" vibrato"},{0}};
	case VIBRATOMODE: 
		fCheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	// static const value_pair fCheckbox0_values[] = {{"linear"},{"invert"},{0}};
	case INVERT: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case MAXNOTCH1FREQ: 
		fHslider3_ = (float*)data; // , 8e+02f, 2e+01f, 1e+04f, 1.0f 
		break;
	case MINNOTCH1FREQ: 
		fHslider2_ = (float*)data; // , 1e+02f, 2e+01f, 5e+03f, 1.0f 
		break;
	case NOTCHWIDTH: 
		fHslider5_ = (float*)data; // , 1e+03f, 1e+01f, 5e+03f, 1.0f 
		break;
	case NOTCHFREQ: 
		fHslider4_ = (float*)data; // , 1.5f, 1.1f, 4.0f, 0.01f 
		break;
	case SPEED: 
		fHslider1_ = (float*)data; // , 0.5f, 0.0f, 1e+01f, 0.01f 
		break;
	case DEPTH: 
		fHslider0_ = (float*)data; // , 1.0f, 0.0f, 1.0f, 0.01f 
		break;
	case FEEDBACKGAIN: 
		fHslider6_ = (float*)data; // , 0.0f, 0.0f, 1.0f, 0.01f 
		break;
	case LEVEL: 
		fHslider7_ = (float*)data; // , 0.0f, -6e+01f, 1e+01f, 0.1f 
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
