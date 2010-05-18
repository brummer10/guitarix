namespace HighShelf {
// generated from file '../src/faust/HighShelf.dsp'

int 	iVec0[2];
double 	fConst0;
double 	fConst1;
double 	fConst2;
double 	fConst3;
double 	fConst4;
double 	fRec1[2];
double 	fVec1[3];
double 	fConst5;
double 	fConst6;
double 	fConst7;
double 	fRec0[3];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) iVec0[i] = 0;
	fConst0 = (6.283185307179586 * (max(0, ((0.5 * fSamplingFreq) - 100)) / fSamplingFreq));
	fConst1 = cos(fConst0);
	fConst2 = (0 - (2 * (0 - (2.0 * fConst1))));
	fConst3 = (0.01 * sin(fConst0));
	fConst4 = (fConst3 - 2.0);
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fVec1[i] = 0;
	fConst5 = (0 - (4.0 * fConst1));
	fConst6 = (2.0 - fConst3);
	fConst7 = (1.0 / (2.0 + fConst3));
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec1[0] = ((1e-20 * (1 - iVec0[1])) - fRec1[1]);
		double fTemp0 = ((double)input0[i] + fRec1[0]);
		fVec1[0] = fTemp0;
		fRec0[0] = (fVec1[0] + (fConst7 * (((fConst6 * fVec1[2]) + (fConst5 * fVec1[1])) + ((fConst4 * fRec0[2]) + (fConst2 * fRec0[1])))));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fVec1[2] = fVec1[1]; fVec1[1] = fVec1[0];
		fRec1[1] = fRec1[0];
		iVec0[1] = iVec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerInit(init);
}

} // end namespace HighShelf
