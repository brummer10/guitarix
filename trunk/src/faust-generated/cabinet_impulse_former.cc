namespace cabinet_impulse_former {
// generated from file '../src/faust/cabinet_impulse_former.dsp'

FAUSTFLOAT&	fslider0 = get_alias("cab.treble");
double 	fConst0;
double 	fConst1;
double 	fConst2;
FAUSTFLOAT&	fslider1 = get_alias("cab.bass");
double 	fConst3;
double 	fConst4;
double 	fConst5;
double 	fVec0[3];
double 	fRec1[3];
double 	fRec0[3];
FAUSTFLOAT&	fslider2 = get_alias("cab.Level");
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (15079.644737231007 / fSamplingFreq);
	fConst1 = cos(fConst0);
	fConst2 = (1.4142135623730951 * sin(fConst0));
	fConst3 = (1884.9555921538758 / fSamplingFreq);
	fConst4 = cos(fConst3);
	fConst5 = (1.4142135623730951 * sin(fConst3));
	for (int i=0; i<3; i++) fVec0[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = pow(10,(0.025 * fslider0));
	double 	fSlow1 = (1 + fSlow0);
	double 	fSlow2 = (fConst1 * fSlow1);
	double 	fSlow3 = (2 * (0 - ((1 + fSlow2) - fSlow0)));
	double 	fSlow4 = (fConst1 * (fSlow0 - 1));
	double 	fSlow5 = (fConst2 * sqrt(fSlow0));
	double 	fSlow6 = (fSlow1 - (fSlow5 + fSlow4));
	double 	fSlow7 = pow(10,(0.025 * fslider1));
	double 	fSlow8 = (1 + fSlow7);
	double 	fSlow9 = (fConst4 * fSlow8);
	double 	fSlow10 = (0 - (2 * ((fSlow7 + fSlow9) - 1)));
	double 	fSlow11 = (fConst5 * sqrt(fSlow7));
	double 	fSlow12 = (fConst4 * (fSlow7 - 1));
	double 	fSlow13 = ((1 + (fSlow7 + fSlow12)) - fSlow11);
	double 	fSlow14 = (fSlow8 - (fSlow11 + fSlow12));
	double 	fSlow15 = (2 * (0 - ((1 + fSlow9) - fSlow7)));
	double 	fSlow16 = (fSlow7 + fSlow11);
	double 	fSlow17 = ((1 + fSlow16) - fSlow12);
	double 	fSlow18 = (1.0 / (1 + (fSlow12 + fSlow16)));
	double 	fSlow19 = (fSlow0 * ((1 + (fSlow0 + fSlow4)) - fSlow5));
	double 	fSlow20 = (fSlow0 + fSlow5);
	double 	fSlow21 = (fSlow0 * (1 + (fSlow4 + fSlow20)));
	double 	fSlow22 = (((fSlow0 + fSlow2) - 1) * (0 - (2 * fSlow0)));
	double 	fSlow23 = (1.0 / ((1 + fSlow20) - fSlow4));
	double 	fSlow24 = fslider2;
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec1[0] = (fSlow18 * ((fSlow7 * (((fSlow17 * fVec0[0]) + (fSlow15 * fVec0[1])) + (fSlow14 * fVec0[2]))) - ((fSlow13 * fRec1[2]) + (fSlow10 * fRec1[1]))));
		fRec0[0] = (fSlow23 * ((((fSlow22 * fRec1[1]) + (fSlow21 * fRec1[0])) + (fSlow19 * fRec1[2])) + (0 - ((fSlow6 * fRec0[2]) + (fSlow3 * fRec0[1])))));
		output0[i] = (FAUSTFLOAT)(fSlow24 * fRec0[0]);
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fVec0[2] = fVec0[1]; fVec0[1] = fVec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerInit("cab", init);
}

} // end namespace cabinet_impulse_former
