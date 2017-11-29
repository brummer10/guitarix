// generated from file '../src/faust/vibe_mono_lfo_sine.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

namespace vibe_mono_lfo_sine {
static int 	iVec0[2];
FAUSTFLOAT 	fslider0;
FAUSTFLOAT	*fslider0_;
static double 	fConst0;
static double 	fRec2[2];
static double 	fRec1[2];
static double 	fRec0[2];
static int	fSamplingFreq;

static void clear_state_f(PluginDef* = 0)
{
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

static void init(unsigned int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (100.53096491487338 / min(1.92e+05, max(1.0, (double)fSamplingFreq)));
	clear_state_f();
}

void compute(int count, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
	double 	fSlow0 = (fConst0 * double(fslider0));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec2[0] = ((fSlow0 * (0 - fRec0[1])) + fRec2[1]);
		fRec1[0] = ((1 + (fRec1[1] + (fSlow0 * fRec2[0]))) - iVec0[1]);
		fRec0[0] = fRec1[0];
		output0[i] = (FAUSTFLOAT)(0.5 * (1 + fRec0[0]));
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
}

static int register_params(const ParamReg& reg)
{
	fslider0_ = reg.registerVar("univibe_mono.freq",N_("Tempo"),"SA",N_("LFO frequency (Hz)"),&fslider0, 4.4, 0.1, 1e+01, 0.1);
	return 0;
}

} // end namespace vibe_mono_lfo_sine
