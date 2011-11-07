// generated from file '../src/faust/presence_level.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

namespace presence_level {
FAUSTFLOAT 	fslider0;
FAUSTFLOAT	*fslider0_;
#define fslider0 (*fslider0_)
static int	fSamplingFreq;

static void init(unsigned int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fslider0;
	for (int i=0; i<count; i++) {
		output0[i] = (FAUSTFLOAT)(fSlow0 * (double)input0[i]);
	}
}

static int register_params(const ParamReg& reg)
{
#undef fslider0
	fslider0_ = reg.registerVar("con.Level",N_(""),"SA",N_(""),&fslider0, 1.0, 0.5, 5.0, 0.5);
	return 0;
}

} // end namespace presence_level
