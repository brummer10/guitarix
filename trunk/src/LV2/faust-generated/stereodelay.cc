// generated from file '../src/LV2/faust/stereodelay.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace stereodelay {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	int iVec0[2];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	float fConst1;
	float fRec0[2];
	float fRec1[2];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	int IOTA0;
	float *fVec1;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	float fConst2;
	float fRec2[2];
	float fRec3[2];
	float fRec4[2];
	float fRec5[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	float fRec6[2];
	float *fVec2;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	float fRec7[2];
	float fRec8[2];
	float fRec9[2];
	float fRec10[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	float fRec11[2];

	bool mem_allocated;
	void mem_alloc();
	void mem_free();
	void connect(uint32_t port,void* data);
	void clear_state_f();
	int activate(bool start);
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);

	static void clear_state_f_static(PluginLV2*);
	static int activate_static(bool start, PluginLV2*);
	static void init_static(uint32_t sample_rate, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2(),
	  fVec1(0),
	  fVec2(0),
	  mem_allocated(false) {
	version = PLUGINLV2_VERSION;
	id = "stereodelay";
	name = N_("Stereo Delay");
	mono_audio = 0;
	stereo_audio = compute_static;
	set_samplerate = init_static;
	activate_plugin = activate_static;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) iVec0[l0] = 0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec0[l1] = 0.0f;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec1[l2] = 0.0f;
	for (int l3 = 0; l3 < 524288; l3 = l3 + 1) fVec1[l3] = 0.0f;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec2[l4] = 0.0f;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec3[l5] = 0.0f;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec4[l6] = 0.0f;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec5[l7] = 0.0f;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec6[l8] = 0.0f;
	for (int l9 = 0; l9 < 524288; l9 = l9 + 1) fVec2[l9] = 0.0f;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec7[l10] = 0.0f;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) fRec8[l11] = 0.0f;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec9[l12] = 0.0f;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec10[l13] = 0.0f;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec11[l14] = 0.0f;
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
	fConst2 = 0.001f * fConst0;
	IOTA0 = 0;
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void Dsp::mem_alloc()
{
	if (!fVec1) fVec1 = new float[524288];
	if (!fVec2) fVec2 = new float[524288];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec1) { delete fVec1; fVec1 = 0; }
	if (fVec2) { delete fVec2; fVec2 = 0; }
}

int Dsp::activate(bool start)
{
	if (start) {
		if (!mem_allocated) {
			mem_alloc();
			clear_state_f();
		}
	} else if (mem_allocated) {
		mem_free();
	}
	return 0;
}

int Dsp::activate_static(bool start, PluginLV2 *p)
{
	return static_cast<Dsp*>(p)->activate(start);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fHslider0 (*fHslider0_)
#define fCheckbox0 (*fCheckbox0_)
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	float fSlow0 = fConst1 * float(fHslider0);
	float fSlow1 = std::cos(fSlow0);
	float fSlow2 = std::sin(fSlow0);
	float fSlow3 = float(fCheckbox0);
	float fSlow4 = fConst2 * float(fVslider0);
	float fSlow5 = 0.001f * std::pow(1e+01f, 0.05f * float(fVslider1));
	float fSlow6 = fConst2 * float(fVslider2);
	float fSlow7 = 0.001f * std::pow(1e+01f, 0.05f * float(fVslider3));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		iVec0[0] = 1;
		fRec0[0] = fSlow2 * fRec1[1] + fSlow1 * fRec0[1];
		fRec1[0] = float(1 - iVec0[1]) + fSlow1 * fRec1[1] - fSlow2 * fRec0[1];
		float fTemp0 = float(input0[i0]);
		fVec1[IOTA0 & 524287] = fTemp0;
		float fTemp1 = ((fRec2[1] != 0.0f) ? (((fRec3[1] > 0.0f) & (fRec3[1] < 1.0f)) ? fRec2[1] : 0.0f) : (((fRec3[1] == 0.0f) & (fSlow4 != fRec4[1])) ? 0.0009765625f : (((fRec3[1] == 1.0f) & (fSlow4 != fRec5[1])) ? -0.0009765625f : 0.0f)));
		fRec2[0] = fTemp1;
		fRec3[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec3[1] + fTemp1));
		fRec4[0] = (((fRec3[1] >= 1.0f) & (fRec5[1] != fSlow4)) ? fSlow4 : fRec4[1]);
		fRec5[0] = (((fRec3[1] <= 0.0f) & (fRec4[1] != fSlow4)) ? fSlow4 : fRec5[1]);
		float fTemp2 = fVec1[(IOTA0 - int(std::min<float>(262144.0f, std::max<float>(0.0f, fRec4[0])))) & 524287];
		fRec6[0] = fSlow5 + 0.999f * fRec6[1];
		output0[i0] = FAUSTFLOAT(fTemp0 + fRec6[0] * (fTemp2 + fRec3[0] * (fVec1[(IOTA0 - int(std::min<float>(262144.0f, std::max<float>(0.0f, fRec5[0])))) & 524287] - fTemp2)) * (1.0f - fSlow3 * fRec0[0]));
		float fTemp3 = float(input1[i0]);
		fVec2[IOTA0 & 524287] = fTemp3;
		float fTemp4 = ((fRec7[1] != 0.0f) ? (((fRec8[1] > 0.0f) & (fRec8[1] < 1.0f)) ? fRec7[1] : 0.0f) : (((fRec8[1] == 0.0f) & (fSlow6 != fRec9[1])) ? 0.0009765625f : (((fRec8[1] == 1.0f) & (fSlow6 != fRec10[1])) ? -0.0009765625f : 0.0f)));
		fRec7[0] = fTemp4;
		fRec8[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec8[1] + fTemp4));
		fRec9[0] = (((fRec8[1] >= 1.0f) & (fRec10[1] != fSlow6)) ? fSlow6 : fRec9[1]);
		fRec10[0] = (((fRec8[1] <= 0.0f) & (fRec9[1] != fSlow6)) ? fSlow6 : fRec10[1]);
		float fTemp5 = fVec2[(IOTA0 - int(std::min<float>(262144.0f, std::max<float>(0.0f, fRec9[0])))) & 524287];
		fRec11[0] = fSlow7 + 0.999f * fRec11[1];
		output1[i0] = FAUSTFLOAT(fTemp3 + fRec11[0] * (fTemp5 + fRec8[0] * (fVec2[(IOTA0 - int(std::min<float>(262144.0f, std::max<float>(0.0f, fRec10[0])))) & 524287] - fTemp5)) * (1.0f - fSlow3 * (0.0f - fRec0[0])));
		iVec0[1] = iVec0[0];
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		IOTA0 = IOTA0 + 1;
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
	}
#undef fHslider0
#undef fCheckbox0
#undef fVslider0
#undef fVslider1
#undef fVslider2
#undef fVslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	// static const value_pair fCheckbox0_values[] = {{"linear"},{"pingpong"},{0}};
	case INVERT: 
		fCheckbox0_ = (float*)data; // , 0.0, 0.0, 1.0, 1.0 
		break;
	case LFOFREQ: 
		fHslider0_ = (float*)data; // , 0.2f, 0.0f, 5.0f, 0.01f 
		break;
	case L_DELAY: 
		fVslider0_ = (float*)data; // , 0.0f, 0.0f, 5e+03f, 1e+01f 
		break;
	case L_GAIN: 
		fVslider1_ = (float*)data; // , 0.0f, -2e+01f, 2e+01f, 0.1f 
		break;
	case R_DELAY: 
		fVslider2_ = (float*)data; // , 0.0f, 0.0f, 5e+03f, 1e+01f 
		break;
	case R_GAIN: 
		fVslider3_ = (float*)data; // , 0.0f, -2e+01f, 2e+01f, 0.1f 
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
   LFOFREQ, 
   INVERT, 
   L_DELAY, 
   L_GAIN, 
   R_DELAY, 
   R_GAIN, 
} PortIndex;
*/

} // end namespace stereodelay
