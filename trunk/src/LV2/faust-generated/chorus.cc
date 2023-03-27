// generated from file '../src/LV2/faust/chorus.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace chorus {
class mydspSIG0 {
	
  private:
	
	int iRec4[2];
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
	}
	int getNumOutputsmydspSIG0() {
		return 1;
	}
	
	void instanceInitmydspSIG0(int sample_rate) {
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			iRec4[l1] = 0;
		}
	}
	
	void fillmydspSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iRec4[0] = iRec4[1] + 1;
			table[i1] = std::sin(9.58738e-05f * float(iRec4[0] + -1));
			iRec4[1] = iRec4[0];
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static float ftbl0mydspSIG0[65536];


class Dsp: public PluginLV2 {
private:
	uint32_t fSampleRate;
	int IOTA0;
	float *fVec0;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	float fRec6[2];
	float fConst1;
	float fRec5[2];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	float fRec7[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT	*fHslider2_;
	float fRec8[2];
	float fConst2;
	float fConst3;
	float fConst4;
	float fRec0[2];
	float fRec1[2];
	float fRec2[2];
	float fRec3[2];
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT	*fHslider3_;
	float fRec9[2];
	float *fVec1;
	float fRec10[2];
	float fRec11[2];
	float fRec12[2];
	float fRec13[2];

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
	  fVec0(0),
	  fVec1(0),
	  mem_allocated(false) {
	version = PLUGINLV2_VERSION;
	id = "chorus";
	name = N_("Chorus");
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
	for (int l0 = 0; l0 < 131072; l0 = l0 + 1) fVec0[l0] = 0.0f;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec6[l2] = 0.0f;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec5[l3] = 0.0f;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec7[l4] = 0.0f;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec8[l5] = 0.0f;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec0[l6] = 0.0f;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec1[l7] = 0.0f;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec2[l8] = 0.0f;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec3[l9] = 0.0f;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec9[l10] = 0.0f;
	for (int l11 = 0; l11 < 131072; l11 = l11 + 1) fVec1[l11] = 0.0f;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fRec10[l12] = 0.0f;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec11[l13] = 0.0f;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec12[l14] = 0.0f;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec13[l15] = 0.0f;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t sample_rate)
{
	mydspSIG0* sig0 = newmydspSIG0();
	sig0->instanceInitmydspSIG0(sample_rate);
	sig0->fillmydspSIG0(65536, ftbl0mydspSIG0);
	deletemydspSIG0(sig0);
	fSampleRate = sample_rate;
	float fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
	fConst1 = 1.0f / fConst0;
	fConst2 = 0.5f * fConst0;
	fConst3 = 1e+03f / fConst0;
	fConst4 = 0.0f - fConst3;
	IOTA0 = 0;
}

void Dsp::init_static(uint32_t sample_rate, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void Dsp::mem_alloc()
{
	if (!fVec0) fVec0 = new float[131072];
	if (!fVec1) fVec1 = new float[131072];
	mem_allocated = true;
}

void Dsp::mem_free()
{
	mem_allocated = false;
	if (fVec0) { delete fVec0; fVec0 = 0; }
	if (fVec1) { delete fVec1; fVec1 = 0; }
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
#define fHslider1 (*fHslider1_)
#define fHslider2 (*fHslider2_)
#define fHslider3 (*fHslider3_)
	float fSlow0 = 0.007f * float(fHslider0);
	float fSlow1 = 0.007f * float(fHslider1);
	float fSlow2 = 0.007f * float(fHslider2);
	float fSlow3 = 0.007f * float(fHslider3);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		float fTemp0 = float(input0[i0]);
		fVec0[IOTA0 & 131071] = fTemp0;
		fRec6[0] = fSlow0 + 0.993f * fRec6[1];
		float fTemp1 = fRec5[1] + fConst1 * fRec6[0];
		fRec5[0] = fTemp1 - std::floor(fTemp1);
		float fTemp2 = 65536.0f * (fRec5[0] - std::floor(fRec5[0]));
		float fTemp3 = std::floor(fTemp2);
		int iTemp4 = int(fTemp3);
		fRec7[0] = fSlow1 + 0.993f * fRec7[1];
		fRec8[0] = fSlow2 + 0.993f * fRec8[1];
		float fTemp5 = fConst2 * fRec8[0] * (fRec7[0] * ((fTemp3 + (1.0f - fTemp2)) * ftbl0mydspSIG0[iTemp4 & 65535] + (fTemp2 - fTemp3) * ftbl0mydspSIG0[(iTemp4 + 1) & 65535]) + 1.0f);
		float fTemp6 = ((fRec0[1] != 0.0f) ? (((fRec1[1] > 0.0f) & (fRec1[1] < 1.0f)) ? fRec0[1] : 0.0f) : (((fRec1[1] == 0.0f) & (fTemp5 != fRec2[1])) ? fConst3 : (((fRec1[1] == 1.0f) & (fTemp5 != fRec3[1])) ? fConst4 : 0.0f)));
		fRec0[0] = fTemp6;
		fRec1[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec1[1] + fTemp6));
		fRec2[0] = (((fRec1[1] >= 1.0f) & (fRec3[1] != fTemp5)) ? fTemp5 : fRec2[1]);
		fRec3[0] = (((fRec1[1] <= 0.0f) & (fRec2[1] != fTemp5)) ? fTemp5 : fRec3[1]);
		float fTemp7 = fVec0[(IOTA0 - int(std::min<float>(65536.0f, std::max<float>(0.0f, fRec2[0])))) & 131071];
		fRec9[0] = fSlow3 + 0.993f * fRec9[1];
		output0[i0] = FAUSTFLOAT(fTemp0 + fRec9[0] * (fTemp7 + fRec1[0] * (fVec0[(IOTA0 - int(std::min<float>(65536.0f, std::max<float>(0.0f, fRec3[0])))) & 131071] - fTemp7)));
		float fTemp8 = float(input1[i0]);
		fVec1[IOTA0 & 131071] = fTemp8;
		float fTemp9 = 65536.0f * (fRec5[0] + (0.25f - std::floor(fRec5[0] + 0.25f)));
		float fTemp10 = std::floor(fTemp9);
		int iTemp11 = int(fTemp10);
		float fTemp12 = fConst2 * fRec8[0] * (fRec7[0] * ((fTemp10 + (1.0f - fTemp9)) * ftbl0mydspSIG0[iTemp11 & 65535] + (fTemp9 - fTemp10) * ftbl0mydspSIG0[(iTemp11 + 1) & 65535]) + 1.0f);
		float fTemp13 = ((fRec10[1] != 0.0f) ? (((fRec11[1] > 0.0f) & (fRec11[1] < 1.0f)) ? fRec10[1] : 0.0f) : (((fRec11[1] == 0.0f) & (fTemp12 != fRec12[1])) ? fConst3 : (((fRec11[1] == 1.0f) & (fTemp12 != fRec13[1])) ? fConst4 : 0.0f)));
		fRec10[0] = fTemp13;
		fRec11[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec11[1] + fTemp13));
		fRec12[0] = (((fRec11[1] >= 1.0f) & (fRec13[1] != fTemp12)) ? fTemp12 : fRec12[1]);
		fRec13[0] = (((fRec11[1] <= 0.0f) & (fRec12[1] != fTemp12)) ? fTemp12 : fRec13[1]);
		float fTemp14 = fVec1[(IOTA0 - int(std::min<float>(65536.0f, std::max<float>(0.0f, fRec12[0])))) & 131071];
		output1[i0] = FAUSTFLOAT(fTemp8 + fRec9[0] * (fTemp14 + fRec11[0] * (fVec1[(IOTA0 - int(std::min<float>(65536.0f, std::max<float>(0.0f, fRec13[0])))) & 131071] - fTemp14)));
		IOTA0 = IOTA0 + 1;
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
	}
#undef fHslider0
#undef fHslider1
#undef fHslider2
#undef fHslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, input1, output0, output1);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case DELAY: 
		fHslider2_ = (float*)data; // , 0.02f, 0.0f, 0.2f, 0.01f 
		break;
	case DEPTH: 
		fHslider1_ = (float*)data; // , 0.02f, 0.0f, 1.0f, 0.01f 
		break;
	case FREQ: 
		fHslider0_ = (float*)data; // , 3.0f, 0.0f, 1e+01f, 0.01f 
		break;
	case LEVEL: 
		fHslider3_ = (float*)data; // , 0.5f, 0.0f, 1.0f, 0.01f 
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
   DELAY, 
   DEPTH, 
   FREQ, 
   LEVEL, 
} PortIndex;
*/

} // end namespace chorus
