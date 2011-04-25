namespace preamp {
// generated from file '../src/faust/preamp.dsp'

double 	fVec0[3];
int 	iVec1[2];
double 	fRec0[2];
FAUSTFLOAT 	fslider0;
double 	fVec2[3];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<3; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) iVec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<3; i++) fVec2[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (0.75 / atan(fSlow0));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		iVec1[0] = 1;
		double fTemp1 = (fVec0[2] + (fVec0[0] + fVec0[1]));
		fRec0[0] = ((1e-20 * (1 - iVec1[1])) - fRec0[1]);
		double fTemp2 = (fTemp1 * ((0.3333333333333333 - (0.016666666666666663 * fTemp1)) - (0.016666666666666663 * (fTemp1 * (fRec0[0] + (0.3333333333333333 * fTemp1))))));
		double fTemp3 = (fSlow1 * atan((fSlow0 * (fTemp2 * (1.5 - (0.5 * (fTemp2 * (fRec0[0] + fTemp2))))))));
		fVec2[0] = fTemp3;
		output0[i] = (FAUSTFLOAT)(0.3333333333333333 * (fVec2[2] + (fVec2[0] + fVec2[1])));
		// post processing
		fVec2[2] = fVec2[1]; fVec2[1] = fVec2[0];
		fRec0[1] = fRec0[0];
		iVec1[1] = iVec1[0];
		fVec0[2] = fVec0[1]; fVec0[1] = fVec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("preamp.atan","drive","S","Input level for pre-amp (higher level gives more distortion)",&fslider0, 1.0, 1.0, 1e+01, 1.0);
	registerInit("preamp", init);
}

} // end namespace preamp
