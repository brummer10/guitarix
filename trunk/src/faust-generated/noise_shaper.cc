// generated from file '../src/faust/noise_shaper.dsp' by dsp2cc:
namespace noise_shaper {
static double 	fConst0;
static double 	fConst1;
static double 	fRec0[2];
static FAUSTFLOAT 	fslider0;
static int	fSamplingFreq;

static void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = exp((0 - (2e+02 / fSamplingFreq)));
	fConst1 = exp((0 - (0.1 / fSamplingFreq)));
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (5 * fSlow0);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		double fTemp1 = max(1, fabs(fTemp0));
		double fTemp2 = ((fConst1 * (fRec0[1] >= fTemp1)) + (fConst0 * (fRec0[1] < fTemp1)));
		fRec0[0] = ((fTemp1 * (0 - (fTemp2 - 1))) + (fRec0[1] * fTemp2));
		double fTemp3 = max(0, (fSlow1 + (20 * log10(fRec0[0]))));
		double fTemp4 = (0.5 * min(1, max(0, (0.09522902580706599 * fTemp3))));
		output0[i] = (FAUSTFLOAT)(fTemp0 * pow(10,(0.05 * (fSlow0 + ((fTemp3 * (0 - fTemp4)) / (1 + fTemp4))))));
		// post processing
		fRec0[1] = fRec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("shaper.sharper","sharper","S","",&fslider0, 1.0, 1.0, 1e+01, 1.0);
	registerInit("shaper", init);
}

} // end namespace noise_shaper
