namespace stereoecho {
// generated from file '../src/faust/stereoecho.dsp'

volatile bool inited = false;
FAUSTFLOAT 	fslider0;
float 	fConst0;
FAUSTFLOAT 	fslider1;
int 	IOTA;
float *fRec0;
FAUSTFLOAT 	fslider2;
FAUSTFLOAT 	fslider3;
float *fRec1;
int	fSamplingFreq;

void init(int samplingFreq)
{
	if (!fRec0) fRec0 = new float[262144];
	if (!fRec1) fRec1 = new float[262144];
	fSamplingFreq = samplingFreq;
	fConst0 = (0.001f * fSamplingFreq);
	IOTA = 0;
	for (int i=0; i<262144; i++) fRec0[i] = 0;
	for (int i=0; i<262144; i++) fRec1[i] = 0;
	inited = true;
}

void mem_free()
{
	inited = false;
	jack_sync();
	if (fRec0) { delete fRec0; fRec0 = 0; }
	if (fRec1) { delete fRec1; fRec1 = 0; }
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

void compute(int count, float *input0, float *input1, float *output0, float *output1)
{
	int 	iSlow0 = int((1 + int((int((int((fConst0 * fslider0)) - 1)) & 131071))));
	float 	fSlow1 = (0.01f * fslider1);
	int 	iSlow2 = int((1 + int((int((int((fConst0 * fslider2)) - 1)) & 131071))));
	float 	fSlow3 = (0.01f * fslider3);
	for (int i=0; i<count; i++) {
		fRec0[IOTA&262143] = ((float)input0[i] + (fSlow1 * fRec0[(IOTA-iSlow0)&262143]));
		output0[i] = (FAUSTFLOAT)fRec0[(IOTA-0)&262143];
		fRec1[IOTA&262143] = ((float)input1[i] + (fSlow3 * fRec1[(IOTA-iSlow2)&262143]));
		output1[i] = (FAUSTFLOAT)fRec1[(IOTA-0)&262143];
		// post processing
		IOTA = IOTA+1;
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("stereoecho.percent_r","","S","",&fslider3, 0.0f, 0.0f, 1e+02f, 0.1f);
	registerVar("stereoecho.time_r","","S","",&fslider2, 1.0f, 1.0f, 2e+03f, 1.0f);
	registerVar("stereoecho.percent_l","","S","",&fslider1, 0.0f, 0.0f, 1e+02f, 0.1f);
	registerVar("stereoecho.time_l","","S","",&fslider0, 1.0f, 1.0f, 2e+03f, 1.0f);
	registerInit("stereoecho", init);
}

} // end namespace stereoecho
