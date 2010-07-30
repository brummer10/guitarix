namespace jconv_post {
// generated from file '../src/faust/jconv_post.dsp'

volatile bool inited = false;
FAUSTFLOAT 	fslider0;
int 	IOTA;
float *fVec0;
FAUSTFLOAT 	fslider1;
float 	fConst0;
FAUSTFLOAT 	fslider2;
float 	fRec0[2];
FAUSTFLOAT 	fslider3;
FAUSTFLOAT&	fslider4 = get_alias("amp.balance");
float *fVec1;
int	fSamplingFreq;

void init(int samplingFreq)
{
	if (!fVec0) fVec0 = new float[65536];
	if (!fVec1) fVec1 = new float[65536];
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	for (int i=0; i<65536; i++) fVec0[i] = 0;
	fConst0 = (0.001f * fSamplingFreq);
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<65536; i++) fVec1[i] = 0;
	inited = true;
}

void mem_free()
{
	inited = false;
	jack_sync();
	if (fVec0) { delete fVec0; fVec0 = 0; }
	if (fVec1) { delete fVec1; fVec1 = 0; }
}

inline bool is_inited()
{
    return inited;
}


void activate(bool start, int samplingFreq)
{
	if (start) {
		if (!is_inited()) {
			init(samplingFreq);
		}
	} else {
		if (is_inited()) {
			mem_free();
		}
	}
}

void compute(int count, float *input0, float *input1, float *input2, float *input3, float *output0, float *output1)
{
	float 	fSlow0 = (0.01f * fslider0);
	float 	fSlow1 = (1 - fSlow0);
	float 	fSlow2 = (fConst0 * fslider1);
	float 	fSlow3 = ((int((fSlow2 > 0)))?0:(0 - fSlow2));
	int 	iSlow4 = int(fSlow3);
	int 	iSlow5 = int((iSlow4 & 65535));
	int 	iSlow6 = (1 + iSlow4);
	float 	fSlow7 = (iSlow6 - fSlow3);
	int 	iSlow8 = int((int(iSlow6) & 65535));
	float 	fSlow9 = (fSlow3 - iSlow4);
	float 	fSlow10 = (0.0010000000000000009f * powf(10,(0.05f * fslider2)));
	float 	fSlow11 = fslider3;
	float 	fSlow12 = (1 - max(0, fSlow11));
	float 	fSlow13 = fslider4;
	float 	fSlow14 = (1 - max(0, fSlow13));
	float 	fSlow15 = ((int((fSlow2 < 0)))?0:fSlow2);
	int 	iSlow16 = int(fSlow15);
	int 	iSlow17 = int((iSlow16 & 65535));
	int 	iSlow18 = (1 + iSlow16);
	float 	fSlow19 = (iSlow18 - fSlow15);
	int 	iSlow20 = int((int(iSlow18) & 65535));
	float 	fSlow21 = (fSlow15 - iSlow16);
	float 	fSlow22 = (1 - max(0, (0 - fSlow11)));
	float 	fSlow23 = (1 - max(0, (0 - fSlow13)));
	for (int i=0; i<count; i++) {
		float fTemp0 = (fSlow0 * (float)input2[i]);
		fVec0[IOTA&65535] = fTemp0;
		fRec0[0] = (fSlow10 + (0.999f * fRec0[1]));
		output0[i] = (FAUSTFLOAT)(fSlow14 * ((fSlow12 * (fRec0[0] * ((fSlow9 * fVec0[(IOTA-iSlow8)&65535]) + (fSlow7 * fVec0[(IOTA-iSlow5)&65535])))) + (fSlow1 * (float)input0[i])));
		float fTemp1 = (fSlow0 * (float)input3[i]);
		fVec1[IOTA&65535] = fTemp1;
		output1[i] = (FAUSTFLOAT)(fSlow23 * ((fSlow22 * (fRec0[0] * ((fSlow21 * fVec1[(IOTA-iSlow20)&65535]) + (fSlow19 * fVec1[(IOTA-iSlow17)&65535])))) + (fSlow1 * (float)input1[i])));
		// post processing
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("jconv.balance","Balance","S","left/right trim for processed signal",&fslider3, 0.0f, -1.0f, 1.0f, 0.1f);
	registerVar("jconv.gain","Gain","S","gain trim for processed signal (unit: dB)",&fslider2, 0.0f, -2e+01f, 2e+01f, 0.1f);
	registerVar("jconv.diff_delay","Delta Delay","S","delay left or right channel by the specified amount (unit: ms)",&fslider1, 0.0f, -1e+01f, 1e+01f, 0.1f);
	registerVar("jconv.wet_dry","wet/dry","S","percentage of processed signal in output signal",&fslider0, 1e+02f, 0.0f, 1e+02f, 1.0f);
	registerInit("jconv", init);
}

} // end namespace jconv_post
