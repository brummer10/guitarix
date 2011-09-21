// generated from file '../src/faust/HighShelf.dsp' by dsp2cc:
namespace HighShelf {
static int 	iVec0[2];
static double 	fConst0;
static double 	fConst1;
static double 	fConst2;
static double 	fConst3;
static double 	fConst4;
static double 	fConst5;
static double 	fConst6;
static double 	fRec1[2];
static double 	fVec1[3];
static double 	fConst7;
static double 	fConst8;
static double 	fConst9;
static double 	fConst10;
static double 	fConst11;
static double 	fRec0[3];
static int	fSamplingFreq;

static void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) iVec0[i] = 0;
	fConst0 = (6.283185307179586 * (max(0, ((0.5 * fSamplingFreq) - 1e+02)) / fSamplingFreq));
	fConst1 = cos(fConst0);
	fConst2 = (1.316227766016838 * fConst1);
	fConst3 = (0 - (2 * (0 - (0.683772233983162 + fConst2))));
	fConst4 = (0.683772233983162 * fConst1);
	fConst5 = (0.005623413251903491 * sin(fConst0));
	fConst6 = (fConst5 - (fConst4 + 1.316227766016838));
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fVec1[i] = 0;
	fConst7 = (fConst5 + fConst4);
	fConst8 = (0.31622776601683794 * (1.316227766016838 - fConst7));
	fConst9 = (0.31622776601683794 * ((fConst5 + 1.316227766016838) - fConst4));
	fConst10 = (0 - (0.6324555320336759 * (fConst2 - 0.683772233983162)));
	fConst11 = (1.0 / (1.316227766016838 + fConst7));
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec1[0] = ((1e-20 * (1 - iVec0[1])) - fRec1[1]);
		double fTemp0 = ((double)input0[i] + fRec1[0]);
		fVec1[0] = fTemp0;
		fRec0[0] = (fConst11 * ((((fConst10 * fVec1[1]) + (fConst9 * fVec1[0])) + (fConst8 * fVec1[2])) + ((fConst6 * fRec0[2]) + (fConst3 * fRec0[1]))));
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
	registerInit("HighShelf", init);
}

} // end namespace HighShelf
