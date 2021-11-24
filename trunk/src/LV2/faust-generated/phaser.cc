// generated from file '../src/LV2/faust/phaser.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace phaser {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	float fConst1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT	*fHslider2_;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT	*fHslider3_;
	int iVec0[2];
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT	*fHslider4_;
	float fConst2;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT	*fHslider5_;
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT	*fHslider6_;
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT	*fHslider7_;
	float fRec5[2];
	float fRec6[2];
	float fRec4[3];
	float fRec3[3];
	float fRec2[3];
	float fRec1[3];
	float fRec0[2];
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT	*fCheckbox1_;
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) iVec0[l0] = 0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec5[l1] = 0.0f;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec6[l2] = 0.0f;
	for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) fRec4[l3] = 0.0f;
	for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) fRec3[l4] = 0.0f;
	for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) fRec2[l5] = 0.0f;
	for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) fRec1[l6] = 0.0f;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec0[l7] = 0.0f;
	for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) fRec11[l8] = 0.0f;
	for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) fRec10[l9] = 0.0f;
	for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) fRec9[l10] = 0.0f;
	for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) fRec8[l11] = 0.0f;
	for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) fRec7[l12] = 0.0f;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	float fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
	fConst1 = (1.0f / fConst0);
	fConst2 = (6.28318548f / fConst0);
	clear_state_f();
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fHslider0 (*fHslider0_)
#define fCheckbox0 (*fCheckbox0_)
#define fHslider1 (*fHslider1_)
#define fHslider2 (*fHslider2_)
#define fHslider3 (*fHslider3_)
#define fHslider4 (*fHslider4_)
#define fHslider5 (*fHslider5_)
#define fHslider6 (*fHslider6_)
#define fHslider7 (*fHslider7_)
#define fCheckbox1 (*fCheckbox1_)
	float fSlow0 = std::pow(10.0f, (0.0500000007f * float(fHslider0)));
	float fSlow1 = (0.5f * (int(float(fCheckbox0)) ? 2.0f : float(fHslider1)));
	float fSlow2 = (1.0f - fSlow1);
	float fSlow3 = std::exp((fConst1 * (0.0f - (3.14159274f * float(fHslider2)))));
	float fSlow4 = mydsp_faustpower2_f(fSlow3);
	float fSlow5 = (0.0f - (2.0f * fSlow3));
	float fSlow6 = float(fHslider3);
	float fSlow7 = float(fHslider4);
	float fSlow8 = float(fHslider5);
	float fSlow9 = (fConst2 * fSlow8);
	float fSlow10 = (0.5f * (0.0f - (fConst2 * (fSlow8 - std::max<float>(fSlow8, float(fHslider6))))));
	float fSlow11 = (fConst2 * float(fHslider7));
	float fSlow12 = std::sin(fSlow11);
	float fSlow13 = std::cos(fSlow11);
	float fSlow14 = mydsp_faustpower2_f(fSlow7);
	float fSlow15 = mydsp_faustpower3_f(fSlow7);
	float fSlow16 = mydsp_faustpower4_f(fSlow7);
	float fSlow17 = (int(float(fCheckbox1)) ? (-1.0f * fSlow1) : fSlow1);
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		float fTemp0 = float(input0[i0]);
		iVec0[0] = 1;
		fRec5[0] = ((fSlow12 * fRec6[1]) + (fSlow13 * fRec5[1]));
		fRec6[0] = ((float((1 - iVec0[1])) + (fSlow13 * fRec6[1])) - (fSlow12 * fRec5[1]));
		float fTemp1 = (fSlow9 + (fSlow10 * (1.0f - fRec5[0])));
		float fTemp2 = (fRec4[1] * std::cos((fSlow7 * fTemp1)));
		fRec4[0] = (((fSlow0 * fTemp0) + (fSlow6 * fRec0[1])) - ((fSlow5 * fTemp2) + (fSlow4 * fRec4[2])));
		float fTemp3 = (fRec3[1] * std::cos((fSlow14 * fTemp1)));
		fRec3[0] = ((fSlow5 * (fTemp2 - fTemp3)) + (fRec4[2] + (fSlow4 * (fRec4[0] - fRec3[2]))));
		float fTemp4 = (fRec2[1] * std::cos((fSlow15 * fTemp1)));
		fRec2[0] = ((fSlow5 * (fTemp3 - fTemp4)) + (fRec3[2] + (fSlow4 * (fRec3[0] - fRec2[2]))));
		float fTemp5 = (fRec1[1] * std::cos((fSlow16 * fTemp1)));
		fRec1[0] = ((fSlow5 * (fTemp4 - fTemp5)) + (fRec2[2] + (fSlow4 * (fRec2[0] - fRec1[2]))));
		fRec0[0] = ((fSlow4 * fRec1[0]) + ((fSlow5 * fTemp5) + fRec1[2]));
		output0[i0] = FAUSTFLOAT(((fSlow0 * (fTemp0 * fSlow2)) + (fRec0[0] * fSlow17)));
		float fTemp6 = float(input1[i0]);
		float fTemp7 = (fSlow9 + (fSlow10 * (1.0f - fRec6[0])));
		float fTemp8 = (fRec11[1] * std::cos((fSlow7 * fTemp7)));
		fRec11[0] = (((fSlow0 * fTemp6) + (fSlow6 * fRec7[1])) - ((fSlow5 * fTemp8) + (fSlow4 * fRec11[2])));
		float fTemp9 = (fRec10[1] * std::cos((fSlow14 * fTemp7)));
		fRec10[0] = ((fSlow5 * (fTemp8 - fTemp9)) + (fRec11[2] + (fSlow4 * (fRec11[0] - fRec10[2]))));
		float fTemp10 = (fRec9[1] * std::cos((fSlow15 * fTemp7)));
		fRec9[0] = ((fSlow5 * (fTemp9 - fTemp10)) + (fRec10[2] + (fSlow4 * (fRec10[0] - fRec9[2]))));
		float fTemp11 = (fRec8[1] * std::cos((fSlow16 * fTemp7)));
		fRec8[0] = ((fSlow5 * (fTemp10 - fTemp11)) + (fRec9[2] + (fSlow4 * (fRec9[0] - fRec8[2]))));
		fRec7[0] = ((fSlow4 * fRec8[0]) + ((fSlow5 * fTemp11) + fRec8[2]));
		output1[i0] = FAUSTFLOAT(((fSlow0 * (fTemp6 * fSlow2)) + (fRec7[0] * fSlow17)));
		iVec0[1] = iVec0[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
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
#undef fHslider0
#undef fCheckbox0
#undef fHslider1
#undef fHslider2
#undef fHslider3
#undef fHslider4
#undef fHslider5
#undef fHslider6
#undef fHslider7
#undef fCheckbox1
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
		fHslider6_ = (float*)data; // , 800.0f, 20.0f, 10000.0f, 1.0f 
		break;
	case MINNOTCH1FREQ: 
		fHslider5_ = (float*)data; // , 100.0f, 20.0f, 5000.0f, 1.0f 
		break;
	case NOTCHWIDTH: 
		fHslider2_ = (float*)data; // , 1000.0f, 10.0f, 5000.0f, 1.0f 
		break;
	case NOTCHFREQ: 
		fHslider4_ = (float*)data; // , 1.5f, 1.10000002f, 4.0f, 0.00999999978f 
		break;
	case SPEED: 
		fHslider7_ = (float*)data; // , 0.5f, 0.0f, 10.0f, 0.00999999978f 
		break;
	// static const value_pair fCheckbox0_values[] = {{"direct "},{" vibrato"},{0}};
	case VIBRATOMODE: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case DEPTH: 
		fHslider1_ = (float*)data; // , 1.0f, 0.0f, 1.0f, 0.00999999978f 
		break;
	case FEEDBACKGAIN: 
		fHslider3_ = (float*)data; // , 0.0f, 0.0f, 1.0f, 0.00999999978f 
		break;
	// static const value_pair fCheckbox1_values[] = {{"linear"},{"invert"},{0}};
	case INVERT: 
		fCheckbox1_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case LEVEL: 
		fHslider0_ = (float*)data; // , 0.0f, -60.0f, 10.0f, 0.100000001f 
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
