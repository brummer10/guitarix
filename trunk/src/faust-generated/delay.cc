namespace delay {
// generated from file '../src/faust/delay.dsp'

volatile bool inited = false;
int 	IOTA;
float *fVec0;
FAUSTFLOAT 	fslider0;
float 	fConst0;
FAUSTFLOAT 	fslider1;
float 	fRec0[2];
int	fSamplingFreq;

void init(int samplingFreq)
{
	if (!fVec0) fVec0 = new float[2097152];
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	for (int i=0; i<2097152; i++) fVec0[i] = 0;
	fConst0 = (0.001f * fSamplingFreq);
	for (int i=0; i<2; i++) fRec0[i] = 0;
	inited = true;
}

void mem_free()
{
	inited = false;
	jack_sync();
	if (fVec0) { delete fVec0; fVec0 = 0; }
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

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = (fConst0 * fslider0);
	int 	iSlow1 = int(fSlow0);
	int 	iSlow2 = int((iSlow1 & 2097151));
	int 	iSlow3 = (1 + iSlow1);
	float 	fSlow4 = (iSlow3 - fSlow0);
	int 	iSlow5 = int((int(iSlow3) & 2097151));
	float 	fSlow6 = (fSlow0 - iSlow1);
	float 	fSlow7 = (0.0010000000000000009f * powf(10,(0.05f * fslider1)));
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		fVec0[IOTA&2097151] = fTemp0;
		fRec0[0] = (fSlow7 + (0.999f * fRec0[1]));
		output0[i] = (FAUSTFLOAT)(fVec0[IOTA&2097151] + (fRec0[0] * ((fSlow6 * fVec0[(IOTA-iSlow5)&2097151]) + (fSlow4 * fVec0[(IOTA-iSlow2)&2097151]))));
		// post processing
		fRec0[1] = fRec0[0];
		IOTA = IOTA+1;
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("delay.gain","","S","",&fslider1, 0.0f, -2e+01f, 2e+01f, 0.1f);
	registerVar("delay.delay","","S","",&fslider0, 0.0f, 0.0f, 5e+03f, 1e+01f);
	registerInit("delay", init);
}

} // end namespace delay
