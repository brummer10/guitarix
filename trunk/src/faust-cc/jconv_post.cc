namespace jconv_post {
// generated from file '../src/faust/jconv_post.dsp'

FAUSTFLOAT 	fslider0;
int 	IOTA;
double 	fVec0[2097152];
FAUSTFLOAT 	fslider1;
double 	fConst0;
FAUSTFLOAT 	fslider2;
double 	fRec0[2];
FAUSTFLOAT&	fslider3 = get_alias("amp.balance");
double 	fVec1[2097152];
FAUSTFLOAT 	fslider4;
FAUSTFLOAT 	fslider5;
double 	fRec1[2];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	for (int i=0; i<2097152; i++) fVec0[i] = 0;
	fConst0 = (0.001 * fSamplingFreq);
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2097152; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
}

void compute(int count, float *input0, float *input1, float *input2, float *input3, float *output0, float *output1)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (1 - max(0, fSlow0));
	double 	fSlow2 = (fConst0 * fslider1);
	int 	iSlow3 = int(fSlow2);
	int 	iSlow4 = int((iSlow3 & 2097151));
	int 	iSlow5 = (1 + iSlow3);
	double 	fSlow6 = (iSlow5 - fSlow2);
	int 	iSlow7 = int((int(iSlow5) & 2097151));
	double 	fSlow8 = (fSlow2 - iSlow3);
	double 	fSlow9 = (0.0010000000000000009 * pow(10,(0.05 * fslider2)));
	double 	fSlow10 = (1 - max(0, (0 - fSlow0)));
	double 	fSlow11 = fslider3;
	double 	fSlow12 = (1 - max(0, fSlow11));
	double 	fSlow13 = (fConst0 * fslider4);
	int 	iSlow14 = int(fSlow13);
	int 	iSlow15 = int((iSlow14 & 2097151));
	int 	iSlow16 = (1 + iSlow14);
	double 	fSlow17 = (iSlow16 - fSlow13);
	int 	iSlow18 = int((int(iSlow16) & 2097151));
	double 	fSlow19 = (fSlow13 - iSlow14);
	double 	fSlow20 = (0.0010000000000000009 * pow(10,(0.05 * fslider5)));
	double 	fSlow21 = (1 - max(0, (0 - fSlow11)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input2[i];
		fVec0[IOTA&2097151] = fTemp0;
		fRec0[0] = (fSlow9 + (0.999 * fRec0[1]));
		output0[i] = (FAUSTFLOAT)(fSlow12 * ((fSlow10 * (fRec0[0] * ((fSlow8 * fVec0[(IOTA-iSlow7)&2097151]) + (fSlow6 * fVec0[(IOTA-iSlow4)&2097151])))) + (fSlow1 * (double)input0[i])));
		double fTemp1 = (double)input3[i];
		fVec1[IOTA&2097151] = fTemp1;
		fRec1[0] = (fSlow20 + (0.999 * fRec1[1]));
		output1[i] = (FAUSTFLOAT)(fSlow21 * ((fSlow10 * (fRec1[0] * ((fSlow19 * fVec1[(IOTA-iSlow18)&2097151]) + (fSlow17 * fVec1[(IOTA-iSlow15)&2097151])))) + (fSlow1 * (double)input1[i])));
		// post processing
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("jconv.right_gain","Right Gain","S","",&fslider5, 0.0, -2e+01, 2e+01, 0.1);
	registerVar("jconv.right_delay","Right Delay","S","",&fslider4, 0.0, 0.0, 5e+03, 1e+01);
	registerVar("jconv.left_gain","Left Gain","S","",&fslider2, 0.0, -2e+01, 2e+01, 0.1);
	registerVar("jconv.left_delay","Left Delay","S","",&fslider1, 0.0, 0.0, 5e+03, 1e+01);
	registerVar("jconv.wet_dry","wet/dry","S","",&fslider0, 0.0, -1.0, 1.0, 0.1);
	registerInit(init);
}

} // end namespace jconv_post
