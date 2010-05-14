namespace feed {
// generated from file '../src/faust/feed.dsp'

FAUSTFLOAT 	fslider0;
FAUSTFLOAT 	fslider1;
double 	fVec0[4];
FAUSTFLOAT 	fslider2;
double 	fRec0[6];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<4; i++) fVec0[i] = 0;
	for (int i=0; i<6; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0, float *output1)
{
	double 	fSlow0 = min(0.999999, fslider0);
	double 	fSlow1 = fslider1;
	double 	fSlow2 = fslider2;
	double 	fSlow3 = ngate;
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec0[0] = fold(fSlow0, (fSlow3 * ((fVec0[0] + (fSlow2 * fVec0[3])) - (fSlow1 * fRec0[5]))));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		output1[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		for (int i=5; i>0; i--) fRec0[i] = fRec0[i-1];
		for (int i=3; i>0; i--) fVec0[i] = fVec0[i-1];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("amp.feedforward","Feedforward","S","",&fslider2, 0.0, -1.0, 1.0, 0.01);
	registerVar("amp.feedback","Feedback","S","",&fslider1, 0.0, -1.0, 1.0, 0.01);
	registerVar("amp.fuzz","fuzz","S","",&fslider0, 1.0, 0.0, 1.0, 0.01);
	registerInit(init);
}

} // end namespace feed
