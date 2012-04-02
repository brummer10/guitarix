// generated from file '../src/faust/vibe_mono_lfo_triangle.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

namespace vibe_mono_lfo_triangle {
FAUSTFLOAT 	fslider0;
FAUSTFLOAT	*fslider0_;
static int 	iConst0;
static double 	fConst1;
static double 	fRec0[2];
static double 	fConst2;
static int	fSamplingFreq;

static void clear_state_f(PluginDef* = 0)
{
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

static void init(unsigned int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (0.0625 * iConst0);
	fConst2 = (32.0 / iConst0);
	clear_state_f();
}

void compute(int count, float *output0)
{
#define fslider0 (*fslider0_)
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (fConst1 / fSlow0);
	double 	fSlow2 = (fConst2 * fSlow0);
	for (int i=0; i<count; i++) {
		fRec0[0] = fmod((1.0 + fRec0[1]),fSlow1);
		double fTemp0 = (fSlow2 * fRec0[0]);
		output0[i] = (FAUSTFLOAT)((int((fTemp0 > 1)))?(2 - fTemp0):fTemp0);
		// post processing
		fRec0[1] = fRec0[0];
#undef fslider0
	}
}

static int register_params(const ParamReg& reg)
{
	fslider0_ = reg.registerVar("univibe_mono.freq",N_("Tempo"),"SA",N_("LFO frequency (Hz)"),&fslider0, 6.0, 0.1, 1e+01, 0.1);
	return 0;
}

} // end namespace vibe_mono_lfo_triangle
