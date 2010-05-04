namespace tone {
// generated from file '../src/faust/tone.dsp'

FAUSTFLOAT 	fslider0;
FAUSTFLOAT 	fslider1;
float 	fConst0;
float 	fConst1;
float 	fConst2;
float 	fConst3;
float 	fConst4;
float 	fConst5;
FAUSTFLOAT 	fslider2;
float 	fVec0[3];
float 	fRec3[3];
float 	fRec2[3];
float 	fRec1[3];
float 	fRec0[3];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (15079.644737231007f / fSamplingFreq);
	fConst1 = cosf(fConst0);
	fConst2 = (1.4142135623730951f * sinf(fConst0));
	fConst3 = (3769.9111843077517f / fSamplingFreq);
	fConst4 = cosf(fConst3);
	fConst5 = (1.4142135623730951f * sinf(fConst3));
	for (int i=0; i<3; i++) fVec0[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	float 	fSlow0 = fslider0;
	float 	fSlow1 = (0.5f * fSlow0);
	float 	fSlow2 = powf(10,(0.025f * (fslider1 - fSlow1)));
	float 	fSlow3 = (1 + fSlow2);
	float 	fSlow4 = (fConst1 * fSlow3);
	float 	fSlow5 = (2 * (0 - ((1 + fSlow4) - fSlow2)));
	float 	fSlow6 = (fConst1 * (fSlow2 - 1));
	float 	fSlow7 = (fConst2 * sqrtf(fSlow2));
	float 	fSlow8 = (fSlow3 - (fSlow7 + fSlow6));
	float 	fSlow9 = powf(10,(0.0125f * fSlow0));
	float 	fSlow10 = (1 + fSlow9);
	float 	fSlow11 = (fConst4 * fSlow10);
	float 	fSlow12 = (2 * (0 - ((1 + fSlow11) - fSlow9)));
	float 	fSlow13 = (fSlow9 - 1);
	float 	fSlow14 = (fConst4 * fSlow13);
	float 	fSlow15 = sqrtf(fSlow9);
	float 	fSlow16 = (fConst5 * fSlow15);
	float 	fSlow17 = (fSlow10 - (fSlow16 + fSlow14));
	float 	fSlow18 = (fConst1 * fSlow10);
	float 	fSlow19 = (0 - (2 * ((fSlow9 + fSlow18) - 1)));
	float 	fSlow20 = (fConst2 * fSlow15);
	float 	fSlow21 = (fConst1 * fSlow13);
	float 	fSlow22 = ((1 + (fSlow9 + fSlow21)) - fSlow20);
	float 	fSlow23 = powf(10,(0.025f * (fslider2 - fSlow1)));
	float 	fSlow24 = (1 + fSlow23);
	float 	fSlow25 = (fConst4 * fSlow24);
	float 	fSlow26 = (0 - (2 * ((fSlow23 + fSlow25) - 1)));
	float 	fSlow27 = (fConst5 * sqrtf(fSlow23));
	float 	fSlow28 = (fConst4 * (fSlow23 - 1));
	float 	fSlow29 = ((1 + (fSlow23 + fSlow28)) - fSlow27);
	float 	fSlow30 = (fSlow24 - (fSlow27 + fSlow28));
	float 	fSlow31 = (2 * (0 - ((1 + fSlow25) - fSlow23)));
	float 	fSlow32 = (fSlow23 + fSlow27);
	float 	fSlow33 = ((1 + fSlow32) - fSlow28);
	float 	fSlow34 = (1.0f / (1 + (fSlow28 + fSlow32)));
	float 	fSlow35 = (fSlow10 - (fSlow20 + fSlow21));
	float 	fSlow36 = (2 * (0 - ((1 + fSlow18) - fSlow9)));
	float 	fSlow37 = (fSlow9 + fSlow20);
	float 	fSlow38 = ((1 + fSlow37) - fSlow21);
	float 	fSlow39 = (1.0f / (1 + (fSlow21 + fSlow37)));
	float 	fSlow40 = (fSlow9 * ((1 + (fSlow9 + fSlow14)) - fSlow16));
	float 	fSlow41 = (fSlow9 + fSlow16);
	float 	fSlow42 = (fSlow9 * (1 + (fSlow14 + fSlow41)));
	float 	fSlow43 = (((fSlow9 + fSlow11) - 1) * (0 - (2 * fSlow9)));
	float 	fSlow44 = (1.0f / ((1 + fSlow41) - fSlow14));
	float 	fSlow45 = (fSlow2 * ((1 + (fSlow2 + fSlow6)) - fSlow7));
	float 	fSlow46 = (fSlow2 + fSlow7);
	float 	fSlow47 = (fSlow2 * (1 + (fSlow6 + fSlow46)));
	float 	fSlow48 = (((fSlow2 + fSlow4) - 1) * (0 - (2 * fSlow2)));
	float 	fSlow49 = (1.0f / ((1 + fSlow46) - fSlow6));
	for (int i=0; i<count; i++) {
		float fTemp0 = (float)input0[i];
		fVec0[0] = fTemp0;
		fRec3[0] = (fSlow34 * ((fSlow23 * (((fSlow33 * fVec0[0]) + (fSlow31 * fVec0[1])) + (fSlow30 * fVec0[2]))) - ((fSlow29 * fRec3[2]) + (fSlow26 * fRec3[1]))));
		fRec2[0] = (fSlow39 * ((fSlow9 * (((fSlow38 * fRec3[0]) + (fSlow36 * fRec3[1])) + (fSlow35 * fRec3[2]))) - ((fSlow22 * fRec2[2]) + (fSlow19 * fRec2[1]))));
		fRec1[0] = (fSlow44 * ((((fSlow43 * fRec2[1]) + (fSlow42 * fRec2[0])) + (fSlow40 * fRec2[2])) + (0 - ((fSlow17 * fRec1[2]) + (fSlow12 * fRec1[1])))));
		fRec0[0] = (fSlow49 * ((((fSlow48 * fRec1[1]) + (fSlow47 * fRec1[0])) + (fSlow45 * fRec1[2])) + (0 - ((fSlow8 * fRec0[2]) + (fSlow5 * fRec0[1])))));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fVec0[2] = fVec0[1]; fVec0[1] = fVec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("amp.tone.bass","bass","S","",&fslider2, 0.0f, -2e+01f, 2e+01f, 0.1f);
	registerVar("amp.tone.treble","treble","S","",&fslider1, 0.0f, -2e+01f, 2e+01f, 0.1f);
	registerVar("amp.tone.middle","middle","S","",&fslider0, 0.0f, -2e+01f, 2e+01f, 0.1f);
	registerInit(init);
}

} // end namespace tone
