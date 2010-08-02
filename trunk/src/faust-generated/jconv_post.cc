namespace jconv_post {
// generated from file '../src/faust/jconv_post.dsp'

FAUSTFLOAT 	fslider0;
int 	IOTA;
double 	fVec0[65536];
FAUSTFLOAT 	fslider1;
double 	fConst0;
FAUSTFLOAT 	fslider2;
double 	fRec0[2];
FAUSTFLOAT 	fslider3;
FAUSTFLOAT&	fslider4 = get_alias("amp.balance");
double 	fVec1[65536];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	for (int i=0; i<65536; i++) fVec0[i] = 0;
	fConst0 = (0.001 * fSamplingFreq);
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<65536; i++) fVec1[i] = 0;
}

void compute(int count, float *input0, float *input1, float *input2, float *input3, float *output0, float *output1)
{
	double 	fSlow0 = (0.01 * fslider0);
	double 	fSlow1 = (1 - fSlow0);
	double 	fSlow2 = (fConst0 * fslider1);
	double 	fSlow3 = ((int((fSlow2 < 0)))?0:fSlow2);
	int 	iSlow4 = int(fSlow3);
	int 	iSlow5 = int((iSlow4 & 65535));
	int 	iSlow6 = (1 + iSlow4);
	double 	fSlow7 = (iSlow6 - fSlow3);
	int 	iSlow8 = int((int(iSlow6) & 65535));
	double 	fSlow9 = (fSlow3 - iSlow4);
	double 	fSlow10 = (0.0010000000000000009 * pow(10,(0.05 * fslider2)));
	double 	fSlow11 = fslider3;
	double 	fSlow12 = (1 - max(0, fSlow11));
	double 	fSlow13 = fslider4;
	double 	fSlow14 = (1 - max(0, fSlow13));
	double 	fSlow15 = ((int((fSlow2 > 0)))?0:(0 - fSlow2));
	int 	iSlow16 = int(fSlow15);
	int 	iSlow17 = int((iSlow16 & 65535));
	int 	iSlow18 = (1 + iSlow16);
	double 	fSlow19 = (iSlow18 - fSlow15);
	int 	iSlow20 = int((int(iSlow18) & 65535));
	double 	fSlow21 = (fSlow15 - iSlow16);
	double 	fSlow22 = (1 - max(0, (0 - fSlow11)));
	double 	fSlow23 = (1 - max(0, (0 - fSlow13)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (fSlow0 * (double)input2[i]);
		fVec0[IOTA&65535] = fTemp0;
		fRec0[0] = (fSlow10 + (0.999 * fRec0[1]));
		output0[i] = (FAUSTFLOAT)(fSlow14 * ((fSlow12 * (fRec0[0] * ((fSlow9 * fVec0[(IOTA-iSlow8)&65535]) + (fSlow7 * fVec0[(IOTA-iSlow5)&65535])))) + (fSlow1 * (double)input0[i])));
		double fTemp1 = (fSlow0 * (double)input3[i]);
		fVec1[IOTA&65535] = fTemp1;
		output1[i] = (FAUSTFLOAT)(fSlow23 * ((fSlow22 * (fRec0[0] * ((fSlow21 * fVec1[(IOTA-iSlow20)&65535]) + (fSlow19 * fVec1[(IOTA-iSlow17)&65535])))) + (fSlow1 * (double)input1[i])));
		// post processing
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("jconv.balance","Balance","S","left/right trim for processed signal",&fslider3, 0.0, -1.0, 1.0, 0.1);
	registerVar("jconv.gain","Gain","S","gain trim for processed signal (unit: dB)",&fslider2, 0.0, -2e+01, 2e+01, 0.1);
	registerVar("jconv.diff_delay","Delta Delay","S","delay left or right channel by the specified amount (unit: ms)",&fslider1, 0.0, -1e+01, 1e+01, 0.01);
	registerVar("jconv.wet_dry","wet/dry","S","percentage of processed signal in output signal",&fslider0, 1e+02, 0.0, 1e+02, 1.0);
	registerInit("jconv", init);
}

} // end namespace jconv_post
