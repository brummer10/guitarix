// generated from file '../src/faust/vibe_mono_lfo_sine.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)

namespace vibe_mono_lfo_sine {
static double fConst0;
FAUSTFLOAT fVslider0;
FAUSTFLOAT	*fVslider0_;
static int iVec0[2];
static double fRec2[2];
static double fRec1[2];
static double fRec0[2];
static int	fSampleRate;

static void clear_state_f(PluginDef* = 0)
{
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) iVec0[l0] = 0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec2[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec1[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec0[l3] = 0.0;
}

static void init(unsigned int sample_rate, PluginDef* = 0)
{
	fSampleRate = sample_rate;
	fConst0 = 100.53096491487338 / std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	clear_state_f();
}

void compute(int count, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
	double fSlow0 = fConst0 * double(fVslider0);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		iVec0[0] = 1;
		fRec2[0] = fRec2[1] + fSlow0 * (0.0 - fRec0[1]);
		fRec1[0] = fSlow0 * fRec2[0] + double(1 - iVec0[1]) + fRec1[1];
		fRec0[0] = fRec1[0];
		output0[i0] = FAUSTFLOAT(0.5 * (fRec0[0] + 1.0));
		iVec0[1] = iVec0[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
#undef fVslider0
}

static int register_params(const ParamReg& reg)
{
	fVslider0_ = reg.registerFloatVar("univibe_mono.freq",N_("Tempo"),"SA",N_("LFO frequency (Hz)"),&fVslider0, 4.4000000000000004, 0.10000000000000001, 10.0, 0.10000000000000001, 0);
	return 0;
}

} // end namespace vibe_mono_lfo_sine
