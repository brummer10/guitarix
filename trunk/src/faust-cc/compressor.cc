namespace compressor {
// generated from file '../src/faust/compressor.dsp'

FAUSTFLOAT 	fentry0;
FAUSTFLOAT 	fentry1;
float 	fConst0;
float 	fConst1;
float 	fRec1[2];
float 	fConst2;
FAUSTFLOAT 	fslider0;
FAUSTFLOAT 	fslider1;
float 	fRec0[2];
FAUSTFLOAT 	fentry2;
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = expf((0 - (10.0f / fSamplingFreq)));
	fConst1 = (1 - fConst0);
	for (int i=0; i<2; i++) fRec1[i] = 0;
	fConst2 = (1.0f / fSamplingFreq);
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = fentry1;
	float 	fSlow1 = (fSlow0 - fentry0);
	float 	fSlow2 = expf((0 - (fConst2 / max(fConst2, fslider0))));
	float 	fSlow3 = expf((0 - (fConst2 / max(fConst2, fslider1))));
	float 	fSlow4 = (1.0f / (1.000000e-03f + fSlow0));
	float 	fSlow5 = (fentry2 - 1);
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		fRec1[0] = ((fConst1 * fabsf(fTemp0)) + (fConst0 * fRec1[1]));
		float fTemp1 = ((fSlow3 * (fRec0[1] >= fRec1[0])) + (fSlow2 * (fRec0[1] < fRec1[0])));
		fRec0[0] = ((fRec1[0] * (0 - (fTemp1 - 1))) + (fRec0[1] * fTemp1));
		float fTemp2 = max(0, ((20 * log10f(fRec0[0])) + fSlow1));
		float fTemp3 = (fSlow5 * min(1, max(0, (fSlow4 * fTemp2))));
		output0[i] = (FAUSTFLOAT)(fTemp0 * powf(10,(5.000000e-02f * ((fTemp2 * (0 - fTemp3)) / (1 + fTemp3)))));
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("compressor.ratio","","S","",&fentry2, 2.0f, 1.0f, 20.0f, 0.1f);
	registerVar("compressor.knee","","S","",&fentry1, 3.0f, 0.0f, 20.0f, 0.1f);
	registerVar("compressor.threshold","","S","",&fentry0, -20.0f, -96.0f, 10.0f, 0.1f);
	registerVar("compressor.release","","S","",&fslider1, 0.5f, 0.0f, 10.0f, 1.000000e-02f);
	registerVar("compressor.attack","","S","",&fslider0, 2.000000e-03f, 0.0f, 1.0f, 1.000000e-03f);
	registerInit(init);
}

} // end namespace compressor
