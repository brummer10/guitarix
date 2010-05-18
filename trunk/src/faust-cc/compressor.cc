namespace compressor {
// generated from file '../src/faust/compressor.dsp'

FAUSTFLOAT 	fentry0;
FAUSTFLOAT 	fentry1;
double 	fConst0;
double 	fConst1;
double 	fRec1[2];
double 	fConst2;
FAUSTFLOAT 	fslider0;
FAUSTFLOAT 	fslider1;
double 	fRec0[2];
FAUSTFLOAT 	fentry2;
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = exp((0 - (1e+01 / fSamplingFreq)));
	fConst1 = (1 - fConst0);
	for (int i=0; i<2; i++) fRec1[i] = 0;
	fConst2 = (1.0 / fSamplingFreq);
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fentry1;
	double 	fSlow1 = (fSlow0 - fentry0);
	double 	fSlow2 = exp((0 - (fConst2 / max(fConst2, fslider0))));
	double 	fSlow3 = exp((0 - (fConst2 / max(fConst2, fslider1))));
	double 	fSlow4 = (1.0 / (0.001 + fSlow0));
	double 	fSlow5 = (fentry2 - 1);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec1[0] = ((fConst1 * fabs((fTemp0 + 1e-20))) + (fConst0 * fRec1[1]));
		double fTemp1 = ((fSlow3 * (fRec0[1] >= fRec1[0])) + (fSlow2 * (fRec0[1] < fRec1[0])));
		fRec0[0] = ((fRec1[0] * (0 - (fTemp1 - 1))) + (fRec0[1] * fTemp1));
		double fTemp2 = max(0, ((20 * log10(fRec0[0])) + fSlow1));
		double fTemp3 = (fSlow5 * min(1, max(0, (fSlow4 * fTemp2))));
		output0[i] = (FAUSTFLOAT)(fTemp0 * pow(10,(0.05 * ((fTemp2 * (0 - fTemp3)) / (1 + fTemp3)))));
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("compressor.ratio","","S","",&fentry2, 2.0, 1.0, 2e+01, 0.1);
	registerVar("compressor.knee","","S","",&fentry1, 3.0, 0.0, 2e+01, 0.1);
	registerVar("compressor.threshold","","S","",&fentry0, -2e+01, -96.0, 1e+01, 0.1);
	registerVar("compressor.release","","S","",&fslider1, 0.5, 0.0, 1e+01, 0.01);
	registerVar("compressor.attack","","S","",&fslider0, 0.002, 0.0, 1.0, 0.001);
	registerInit(init);
}

} // end namespace compressor
