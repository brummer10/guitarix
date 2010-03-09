namespace jconv_post {
// generated from file '../src/faust/jconv_post.dsp'

FAUSTFLOAT&	fslider0=*(float*)&GxEngine::instance()->fslider24;
int 	IOTA;
float 	fVec0[8192];
FAUSTFLOAT&	fslider1=*(float*)&GxEngine::instance()->fsliderdel0;
FAUSTFLOAT&	fslider2=*(float*)&GxEngine::instance()->fjc_ingain;
float 	fRec0[2];
FAUSTFLOAT&	fslider3=*(float*)&GxEngine::instance()->fslider25;
float 	fVec1[8192];
FAUSTFLOAT&	fslider4=*(float*)&GxEngine::instance()->fsliderdel1;
FAUSTFLOAT&	fslider5=*(float*)&GxEngine::instance()->fjc_ingain1;
float 	fRec1[2];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	for (int i=0; i<8192; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<8192; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
}

void compute(int count, float *input0, float *input1, float *input2, float *input3, float *output0, float *output1)
{
	float 	fSlow0 = fslider0;
	float 	fSlow1 = (1 - max(0, fSlow0));
	float 	fSlow2 = fslider1;
	int 	iSlow3 = int(fSlow2);
	int 	iSlow4 = int((iSlow3 & 262143));
	int 	iSlow5 = (1 + iSlow3);
	float 	fSlow6 = (iSlow5 - fSlow2);
	int 	iSlow7 = int((int(iSlow5) & 262143));
	float 	fSlow8 = (fSlow2 - iSlow3);
	float 	fSlow9 = (1.000000e-03f * powf(10,(5.000000e-02f * fslider2)));
	float 	fSlow10 = (1 - max(0, (0 - fSlow0)));
	float 	fSlow11 = fslider3;
	float 	fSlow12 = (1 - max(0, fSlow11));
	float 	fSlow13 = fslider4;
	int 	iSlow14 = int(fSlow13);
	int 	iSlow15 = int((iSlow14 & 262143));
	int 	iSlow16 = (1 + iSlow14);
	float 	fSlow17 = (iSlow16 - fSlow13);
	int 	iSlow18 = int((int(iSlow16) & 262143));
	float 	fSlow19 = (fSlow13 - iSlow14);
	float 	fSlow20 = (1.000000e-03f * powf(10,(5.000000e-02f * fslider5)));
	float 	fSlow21 = (1 - max(0, (0 - fSlow11)));
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input2[i];
		fVec0[IOTA&8191] = fTemp0;
		fRec0[0] = (fSlow9 + (0.999f * fRec0[1]));
		output0[i] = (FAUSTFLOAT)(fSlow12 * ((fSlow10 * (fRec0[0] * ((fSlow8 * fVec0[(IOTA-iSlow7)&8191]) + (fSlow6 * fVec0[(IOTA-iSlow4)&8191])))) + (fSlow1 * (float)input0[i])));
		float fTemp1 = (float)input3[i];
		fVec1[IOTA&8191] = fTemp1;
		fRec1[0] = (fSlow20 + (0.999f * fRec1[1]));
		output1[i] = (FAUSTFLOAT)(fSlow21 * ((fSlow10 * (fRec1[0] * ((fSlow19 * fVec1[(IOTA-iSlow18)&8191]) + (fSlow17 * fVec1[(IOTA-iSlow15)&8191])))) + (fSlow1 * (float)input1[i])));
		// post processing
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("jconv.right_gain","Right Gain","S","",&fslider5, 0.0f, -20.0f, 20.0f, 0.1f);
	registerVar("jconv.right_delay","Right Delay","S","",&fslider4, 0.0f, 0.0f, 5000.0f, 10.0f);
	registerVar("amp.balance","Balance","S","",&fslider3, 0.0f, -1.0f, 1.0f, 0.1f);
	registerVar("jconv.left_gain","Left Gain","S","",&fslider2, 0.0f, -20.0f, 20.0f, 0.1f);
	registerVar("jconv.left_delay","Left Delay","S","",&fslider1, 0.0f, 0.0f, 5000.0f, 10.0f);
	registerVar("jconv.wet_dry","wet/dry","S","",&fslider0, 0.0f, -1.0f, 1.0f, 0.1f);
	registerInit(init);
}

} // end namespace jconv_post
