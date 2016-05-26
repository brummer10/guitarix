// generated from file '../src/faust/jconv_post.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


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
	for (int i=0; i<65536; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<65536; i++) fVec1[i] = 0;
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	fConst0 = (1.000000000000001e-06f * min(192000, max(1, fSamplingFreq)));
}

void Dsp::mem_alloc()
{
	if (!fVec0) fVec0 = new float[65536];
	if (!fVec1) fVec1 = new float[65536];
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
#define fslider4 (*fslider4_)
	float 	fSlow0 = (0.01f * float(fslider0));
	float 	fSlow1 = (fConst0 * float(fslider1));
	float 	fSlow2 = (0.0010000000000000009f * float(fslider2));
	float 	fSlow3 = (0.0010000000000000009f * powf(10,(0.05f * float(fslider3))));
	float 	fSlow4 = (1 - fSlow0);
	float 	fSlow5 = (0.0010000000000000009f * float(fslider4));
	for (int i=0; i<count; i++) {
		float fTemp0 = (fSlow0 * (float)input2[i]);
		fVec0[IOTA&65535] = fTemp0;
		fRec0[0] = (fSlow1 + (0.999f * fRec0[1]));
		float fTemp1 = ((int((fRec0[0] < 0)))?0:fRec0[0]);
		int iTemp2 = int(fTemp1);
		int iTemp3 = (1 + iTemp2);
		fRec1[0] = (fSlow2 + (0.999f * fRec1[1]));
		fRec2[0] = ((0.999f * fRec2[1]) + fSlow3);
		fRec3[0] = (fSlow5 + (0.999f * fRec3[1]));
		output0[i] = (FAUSTFLOAT)((1 - max((float)0, fRec3[0])) * ((fSlow4 * (float)input0[i]) + ((fRec2[0] * (1 - max((float)0, fRec1[0]))) * ((fVec0[(IOTA-int((iTemp2 & 65535)))&65535] * (iTemp3 - fTemp1)) + ((fTemp1 - iTemp2) * fVec0[(IOTA-int((int(iTemp3) & 65535)))&65535])))));
		float fTemp4 = (fSlow0 * (float)input3[i]);
		fVec1[IOTA&65535] = fTemp4;
		float fTemp5 = ((int((fRec0[0] > 0)))?0:(0 - fRec0[0]));
		int iTemp6 = int(fTemp5);
		int iTemp7 = (1 + iTemp6);
		output1[i] = (FAUSTFLOAT)((1 - max((float)0, (0 - fRec3[0]))) * ((fSlow4 * (float)input1[i]) + ((fRec2[0] * (1 - max((float)0, (0 - fRec1[0])))) * ((fVec1[(IOTA-int((iTemp6 & 65535)))&65535] * (iTemp7 - fTemp5)) + ((fTemp5 - iTemp6) * fVec1[(IOTA-int((int(iTemp7) & 65535)))&65535])))));
		// post processing
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
	}
#undef fslider4
}

int Dsp::register_par(const ParamReg& reg)
{
	fslider4_ = reg.registerVar("amp.balance",N_("Balance"),"SA","",&fslider4, 0.0f, -1.0f, 1.0f, 0.1f);
	reg.registerVar("jconv.balance",N_("Balance"),"S",N_("left/right trim for processed signal"),&fslider2, 0.0f, -1.0f, 1.0f, 0.1f);
	reg.registerVar("jconv.diff_delay",N_("Delta Delay"),"S",N_("delay left or right channel by the specified amount (unit: ms)"),&fslider1, 0.0f, -1e+02f, 1e+02f, 0.01f);
	reg.registerVar("jconv.gain",N_("Gain"),"S",N_("gain trim for processed signal (unit: dB)"),&fslider3, 0.0f, -2e+01f, 2e+01f, 0.1f);
	reg.registerVar("jconv.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider0, 1e+02f, 0.0f, 1e+02f, 1.0f);
	return 0;
}


} // end namespace jconv_post
