// generated from file '../src/LV2/faust/stereoecho.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace stereoecho {

class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	int iVec0[2];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	float fConst1;
	float fRec1[2];
	float fRec2[2];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT	*fCheckbox0_;
	int IOTA0;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	float fConst2;
	float fRec3[2];
	float fRec4[2];
	int iRec5[2];
	int iRec6[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	float *fRec0;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	float fRec8[2];
	float fRec9[2];
	int iRec10[2];
	int iRec11[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	float *fRec7;

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
	  fRec0(0),
	  fRec7(0),
	  mem_allocated(false) {
	version = PLUGINLV2_VERSION;
	id = "stereoecho";
	name = N_("Stereo Echo");
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
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec1[l1] = 0.0f;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec2[l2] = 0.0f;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec3[l3] = 0.0f;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec4[l4] = 0.0f;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) iRec5[l5] = 0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) iRec6[l6] = 0;
	for (int l7 = 0; l7 < 262144; l7 = l7 + 1) fRec0[l7] = 0.0f;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec8[l8] = 0.0f;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec9[l9] = 0.0f;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) iRec10[l10] = 0;
	for (int l11 = 0; l11 < 2; l11 = l11 + 1) iRec11[l11] = 0;
	for (int l12 = 0; l12 < 262144; l12 = l12 + 1) fRec7[l12] = 0.0f;
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
	if (!fRec0) fRec0 = new float[262144];
	if (!fRec7) fRec7 = new float[262144];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fRec0) { delete fRec0; fRec0 = 0; }
	if (fRec7) { delete fRec7; fRec7 = 0; }
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
	int iSlow4 = int(fConst2 * float(fVslider0)) + -1;
	float fSlow5 = 0.01f * float(fVslider1);
	int iSlow6 = int(fConst2 * float(fVslider2)) + -1;
	float fSlow7 = 0.01f * float(fVslider3);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		iVec0[0] = 1;
		fRec1[0] = fSlow2 * fRec2[1] + fSlow1 * fRec1[1];
		fRec2[0] = float(1 - iVec0[1]) + fSlow1 * fRec2[1] - fSlow2 * fRec1[1];
		float fTemp0 = ((fRec3[1] != 0.0f) ? (((fRec4[1] > 0.0f) & (fRec4[1] < 1.0f)) ? fRec3[1] : 0.0f) : (((fRec4[1] == 0.0f) & (iSlow4 != iRec5[1])) ? 0.0009765625f : (((fRec4[1] == 1.0f) & (iSlow4 != iRec6[1])) ? -0.0009765625f : 0.0f)));
		fRec3[0] = fTemp0;
		fRec4[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec4[1] + fTemp0));
		iRec5[0] = (((fRec4[1] >= 1.0f) & (iRec6[1] != iSlow4)) ? iSlow4 : iRec5[1]);
		iRec6[0] = (((fRec4[1] <= 0.0f) & (iRec5[1] != iSlow4)) ? iSlow4 : iRec6[1]);
		float fTemp1 = fRec0[(IOTA0 - (std::min<int>(131072, std::max<int>(0, iRec5[0])) + 1)) & 262143];
		fRec0[IOTA0 & 262143] = float(input0[i0]) + fSlow5 * (fTemp1 + fRec4[0] * (fRec0[(IOTA0 - (std::min<int>(131072, std::max<int>(0, iRec6[0])) + 1)) & 262143] - fTemp1)) * (1.0f - fSlow3 * fRec1[0]);
		output0[i0] = FAUSTFLOAT(fRec0[IOTA0 & 262143]);
		float fTemp2 = ((fRec8[1] != 0.0f) ? (((fRec9[1] > 0.0f) & (fRec9[1] < 1.0f)) ? fRec8[1] : 0.0f) : (((fRec9[1] == 0.0f) & (iSlow6 != iRec10[1])) ? 0.0009765625f : (((fRec9[1] == 1.0f) & (iSlow6 != iRec11[1])) ? -0.0009765625f : 0.0f)));
		fRec8[0] = fTemp2;
		fRec9[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec9[1] + fTemp2));
		iRec10[0] = (((fRec9[1] >= 1.0f) & (iRec11[1] != iSlow6)) ? iSlow6 : iRec10[1]);
		iRec11[0] = (((fRec9[1] <= 0.0f) & (iRec10[1] != iSlow6)) ? iSlow6 : iRec11[1]);
		float fTemp3 = fRec7[(IOTA0 - (std::min<int>(131072, std::max<int>(0, iRec10[0])) + 1)) & 262143];
		fRec7[IOTA0 & 262143] = float(input1[i0]) + fSlow7 * (fTemp3 + fRec9[0] * (fRec7[(IOTA0 - (std::min<int>(131072, std::max<int>(0, iRec11[0])) + 1)) & 262143] - fTemp3)) * (1.0f - fSlow3 * (0.0f - fRec1[0]));
		output1[i0] = FAUSTFLOAT(fRec7[IOTA0 & 262143]);
		iVec0[1] = iVec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		IOTA0 = IOTA0 + 1;
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		iRec5[1] = iRec5[0];
		iRec6[1] = iRec6[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		iRec10[1] = iRec10[0];
		iRec11[1] = iRec11[0];
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
	case PERCENT_L: 
		fVslider1_ = (float*)data; // , 0.0f, 0.0f, 1e+02f, 0.1f 
		break;
	case PERCENT_R: 
		fVslider3_ = (float*)data; // , 0.0f, 0.0f, 1e+02f, 0.1f 
		break;
	case TIME_L: 
		fVslider0_ = (float*)data; // , 1.0f, 1.0f, 2e+03f, 1.0f 
		break;
	case TIME_R: 
		fVslider2_ = (float*)data; // , 1.0f, 1.0f, 2e+03f, 1.0f 
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
   PERCENT_L, 
   PERCENT_R, 
   TIME_L, 
   TIME_R, 
} PortIndex;
*/

} // end namespace stereoecho
