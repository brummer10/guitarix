// generated from file '../src/faust/jconv_post.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace jconv_post {


Dsp::Dsp()
	: fVec0(0),
	  fVec1(0),
	  mem_allocated(false) {
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0f;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec1[l1] = 0.0f;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec2[l2] = 0.0f;
	for (int l3 = 0; l3 < 131072; l3 = l3 + 1) fVec0[l3] = 0.0f;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec3[l4] = 0.0f;
	for (int l5 = 0; l5 < 131072; l5 = l5 + 1) fVec1[l5] = 0.0f;
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = 9.99999997e-07f * std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
	IOTA0 = 0;
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

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *input2, FAUSTFLOAT *input3, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fVslider0 (*fVslider0_)
	float fSlow0 = 0.00100000005f * float(fVslider0);
	float fSlow1 = 0.00999999978f * float(fVslider1);
	float fSlow2 = 1.0f - fSlow1;
	float fSlow3 = 0.00100000005f * std::pow(10.0f, 0.0500000007f * float(fVslider2));
	float fSlow4 = 0.00100000005f * float(fVslider3);
	float fSlow5 = fConst0 * float(fVslider4);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.999000013f * fRec0[1];
		fRec1[0] = fSlow3 + 0.999000013f * fRec1[1];
		fRec2[0] = fSlow4 + 0.999000013f * fRec2[1];
		float fTemp0 = fSlow1 * float(input2[i0]);
		fVec0[IOTA0 & 131071] = fTemp0;
		fRec3[0] = fSlow5 + 0.999000013f * fRec3[1];
		float fTemp1 = ((fRec3[0] < 0.0f) ? 0.0f : fRec3[0]);
		int iTemp2 = int(fTemp1);
		float fTemp3 = std::floor(fTemp1);
		output0[i0] = FAUSTFLOAT((1.0f - std::max<float>(0.0f, fRec0[0])) * (fSlow2 * float(input0[i0]) + fRec1[0] * (1.0f - std::max<float>(0.0f, fRec2[0])) * (fVec0[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp2))) & 131071] * (fTemp3 + 1.0f - fTemp1) + (fTemp1 - fTemp3) * fVec0[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp2 + 1))) & 131071])));
		float fTemp4 = fSlow1 * float(input3[i0]);
		fVec1[IOTA0 & 131071] = fTemp4;
		float fThen1 = -1.0f * fRec3[0];
		float fTemp5 = ((fRec3[0] > 0.0f) ? 0.0f : fThen1);
		int iTemp6 = int(fTemp5);
		float fTemp7 = std::floor(fTemp5);
		output1[i0] = FAUSTFLOAT((fSlow2 * float(input1[i0]) + fRec1[0] * (fVec1[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp6))) & 131071] * (fTemp7 + 1.0f - fTemp5) + (fTemp5 - fTemp7) * fVec1[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp6 + 1))) & 131071]) * (1.0f - std::max<float>(0.0f, -1.0f * fRec2[0]))) * (1.0f - std::max<float>(0.0f, -1.0f * fRec0[0])));
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		IOTA0 = IOTA0 + 1;
		fRec3[1] = fRec3[0];
	}
#undef fVslider0
}

int Dsp::register_par(const ParamReg& reg)
{
	fVslider0_ = reg.registerFloatVar("amp.balance",N_("Balance"),"SA","",&fVslider0, 0.0f, -1.0f, 1.0f, 0.100000001f, 0);
	reg.registerFloatVar("jconv.balance",N_("Balance"),"S",N_("left/right trim for processed signal"),&fVslider3, 0.0f, -1.0f, 1.0f, 0.100000001f, 0);
	reg.registerFloatVar("jconv.diff_delay",N_("Delta Delay"),"S",N_("delay left or right channel by the specified amount (unit: ms)"),&fVslider4, 0.0f, -100.0f, 100.0f, 0.00999999978f, 0);
	reg.registerFloatVar("jconv.gain",N_("Gain"),"S",N_("gain trim for processed signal (unit: dB)"),&fVslider2, 0.0f, -20.0f, 20.0f, 0.100000001f, 0);
	reg.registerFloatVar("jconv.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fVslider1, 100.0f, 0.0f, 100.0f, 1.0f, 0);
	return 0;
}


} // end namespace jconv_post
