// generated from file '../src/faust/tube3.dsp' by dsp2cc:
namespace tube3 {
static FAUSTFLOAT 	fslider0;
static FAUSTFLOAT 	fslider1;
static FAUSTFLOAT 	fslider2;
static int	fSamplingFreq;

static void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = faustpower<3>((0 - fslider0));
	double 	fSlow1 = pow(10,fslider1);
	double 	fSlow2 = (fSlow1 * (0 - fSlow0));
	double 	fSlow3 = max(-600, fSlow2);
	double 	fSlow4 = (0 - fSlow3);
	double 	fSlow5 = ((int((fabs(fSlow2) > 0.0001)))?((int((fSlow3 < -50)))?(exp(fSlow3) * fSlow4):(fSlow3 / (1 - exp(fSlow4)))):(1 + (fSlow2 * (0.5 + (0.08333333333333333 * fSlow2)))));
	double 	fSlow6 = (0.08333333333333333 * fSlow1);
	double 	fSlow7 = (fslider2 / fSlow1);
	double 	fSlow8 = (1.0 / fSlow1);
	for (int i=0; i<count; i++) {
		double fTemp0 = ((double)input0[i] - fSlow0);
		double fTemp1 = (fSlow1 * fTemp0);
		double fTemp2 = max(-600, fTemp1);
		double fTemp3 = (0 - fTemp2);
		double fTemp4 = (0 - (fSlow0 + (fSlow7 * (((int((fabs(fTemp1) > 0.0001)))?((int((fTemp2 < -50)))?(exp(fTemp2) * fTemp3):(fTemp2 / (1 - exp(fTemp3)))):(1 + (fSlow1 * (fTemp0 * (0.5 + (fSlow6 * fTemp0)))))) - fSlow5))));
		double fTemp5 = (fSlow1 * fTemp4);
		double fTemp6 = max(-600, fTemp5);
		double fTemp7 = (0 - fTemp6);
		output0[i] = (FAUSTFLOAT)(0 - (fSlow8 * (((int((fabs(fTemp5) > 0.0001)))?((int((fTemp6 < -50)))?(exp(fTemp6) * fTemp7):(fTemp6 / (1 - exp(fTemp7)))):(1 + (fSlow1 * (fTemp4 * (0.5 + (fSlow6 * fTemp4)))))) - fSlow5)));
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("tube3.g","","S","",&fslider2, 1.0, 0.2, 2.0, 0.1);
	registerVar("tube3.dist","","S","",&fslider1, 0.0, 0.0, 1.7, 0.01);
	registerVar("tube3.q","","S","",&fslider0, 0.4, 0.4, 1.0, 0.001);
	registerInit("tube3", init);
}

} // end namespace tube3
