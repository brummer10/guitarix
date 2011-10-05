// generated from file '../src/faust/balance1.dsp' by dsp2cc:
// Code generated with Faust 0.9.30 (http://faust.grame.fr)

namespace balance1 {
FAUSTFLOAT 	fslider0;
FAUSTFLOAT	*fslider0_;
#define fslider0 (*fslider0_)
static double 	fRec0[2];
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

static void init(int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	clear_state();
}

void compute(int count, float *input0, float *output0, float *output1)
{
	double 	fSlow0 = (0.0010000000000000009 * fslider0);
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		double fTemp0 = (double)input0[i];
		output0[i] = (FAUSTFLOAT)(fTemp0 * (1 - max(0, fRec0[0])));
		output1[i] = (FAUSTFLOAT)(fTemp0 * (1 - max(0, (0 - fRec0[0]))));
		// post processing
		fRec0[1] = fRec0[0];
	}
}

static int register_params(const ParamReg& reg)
{
#undef fslider0
	fslider0_ = reg.registerVar("amp.balance","Balance","SA","",&fslider0, 0.0, -1.0, 1.0, 0.1);
	return 0;
}

} // end namespace balance1
