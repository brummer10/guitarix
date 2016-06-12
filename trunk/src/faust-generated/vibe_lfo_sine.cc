// generated from file '../src/faust/vibe_lfo_sine.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)

namespace vibe_lfo_sine {
static int 	iVec0[2];
FAUSTFLOAT 	fslider0;
FAUSTFLOAT	*fslider0_;
static double 	fConst0;
static double 	fRec0[2];
static double 	fRec1[2];
FAUSTFLOAT 	fslider1;
FAUSTFLOAT	*fslider1_;
static int	fSamplingFreq;

static void clear_state_f(PluginDef* = 0)
{
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
}

static void init(unsigned int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (100.53096491487338 / double(min(192000, max(1, fSamplingFreq))));
	clear_state_f();
}

void compute(int count, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
	double 	fSlow0 = (fConst0 * double(fslider0));
	double 	fSlow1 = cos(fSlow0);
	double 	fSlow2 = sin(fSlow0);
	double 	fSlow3 = (0 - fSlow2);
	double 	fSlow4 = (6.283185307179586 * double(fslider1));
	double 	fSlow5 = sin(fSlow4);
	double 	fSlow6 = cos(fSlow4);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec0[0] = ((fSlow2 * fRec1[1]) + (fSlow1 * fRec0[1]));
		fRec1[0] = ((1 + ((fSlow1 * fRec1[1]) + (fSlow3 * fRec0[1]))) - iVec0[1]);
		output0[i] = (FAUSTFLOAT)(0.5 * (1 + fRec0[0]));
		output1[i] = (FAUSTFLOAT)(0.5 * (1 + ((fSlow6 * fRec0[0]) + (fSlow5 * fRec1[0]))));
		// post processing
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		iVec0[1] = iVec0[0];
	}
#undef fslider0
#undef fslider1
}

static int register_params(const ParamReg& reg)
{
	fslider0_ = reg.registerVar("univibe.freq",N_("Tempo"),"SA",N_("LFO frequency (Hz)"),&fslider0, 4.4, 0.1, 1e+01, 0.1);
	fslider1_ = reg.registerVar("univibe.stereo",N_("Phase"),"SA",N_("LFO phase shift between left and right channels"),&fslider1, 0.11, -0.5, 0.5, 0.01);
	return 0;
}

} // end namespace vibe_lfo_sine
