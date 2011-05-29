namespace tremolo {
// generated from file '../src/faust/tremolo.dsp'

int 	iVec0[2];
double 	fConst0;
FAUSTFLOAT 	fslider0;
double 	fConst1;
int 	iRec2[2];
int 	iRec1[2];
double 	fConst2;
double 	fRec5[2];
double 	fRec4[2];
double 	fRec3[2];
FAUSTFLOAT 	fcheckbox0;
FAUSTFLOAT 	fslider1;
double 	fRec0[2];
FAUSTFLOAT 	fslider2;
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	for (int i=0; i<2; i++) iVec0[i] = 0;
	fConst0 = (1.0 / fSamplingFreq);
	fConst1 = (0.5 * fSamplingFreq);
	for (int i=0; i<2; i++) iRec2[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	fConst2 = (6.283185307179586 / fSamplingFreq);
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fslider0;
	int 	iSlow1 = int((fConst1 / double(fSlow0)));
	double 	fSlow2 = (1.0 / iSlow1);
	double 	fSlow3 = (fConst2 * fSlow0);
	int 	iSlow4 = int(fcheckbox0);
	double 	fSlow5 = fslider1;
	double 	fSlow6 = fslider2;
	double 	fSlow7 = (27.0 * fSlow6);
	double 	fSlow8 = (1 - (0.01 * fSlow6));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		double fTemp0 = (fRec0[1] * (1 - (fConst0 / (fConst0 + (0.06 * exp((0 - (2.4849066497880004 * fRec0[1]))))))));
		iRec2[0] = ((int((iRec2[1] > 0)))?((2 * (iRec1[1] < iSlow1)) - 1):(1 - (2 * (iRec1[1] > 0))));
		iRec1[0] = (iRec2[0] + iRec1[1]);
		fRec5[0] = ((fSlow3 * (0 - fRec3[1])) + fRec5[1]);
		fRec4[0] = ((1 + ((fSlow3 * fRec5[0]) + fRec4[1])) - iVec0[1]);
		fRec3[0] = fRec4[0];
		fRec0[0] = (fTemp0 + (fConst0 * (pow((1 + (fSlow5 * (((iSlow4)?max(0, (0.5 * (1 + fRec3[0]))):(fSlow2 * iRec1[0])) - 1))),1.9) / (fConst0 + (0.06 * exp((0 - (2.4849066497880004 * fTemp0))))))));
		output0[i] = (FAUSTFLOAT)((double)input0[i] * (fSlow8 + (fSlow7 / (2700 + exp((13.815510557964274 / log((2.718281828459045 + (8.551967507929417 * fRec0[0])))))))));
		// post processing
		fRec0[1] = fRec0[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		iRec1[1] = iRec1[0];
		iRec2[1] = iRec2[0];
		iVec0[1] = iVec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("tremolo.wet_dry","wet/dry","S","percentage of processed signal in output signal",&fslider2, 1e+02, 0.0, 1e+02, 1.0);
	static const char *fcheckbox0_values[] = {"triangle","sine",0};
	registerEnumVar("tremolo.SINE","","B","",fcheckbox0_values,&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	registerVar("tremolo.depth","","S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	registerVar("tremolo.freq","","S","",&fslider0, 5.0, 0.1, 5e+01, 0.1);
	registerInit("tremolo", init);
}

} // end namespace tremolo
