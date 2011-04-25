namespace impulseresponse {
// generated from file '../src/faust/impulseresponse.dsp'

FAUSTFLOAT 	fslider0;
double 	fConst0;
FAUSTFLOAT 	fslider1;
double 	fConst1;
double 	fVec0[3];
FAUSTFLOAT 	fcheckbox0;
FAUSTFLOAT 	fslider2;
double 	fRec0[3];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (3.141592653589793 / fSamplingFreq);
	fConst1 = (6.283185307179586 / fSamplingFreq);
	for (int i=0; i<3; i++) fVec0[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = exp((0 - (fConst0 * fslider0)));
	double 	fSlow1 = (2 * cos((fConst1 * fslider1)));
	int 	iSlow2 = int(max(0, min(1, fcheckbox0)));
	double 	fSlow3 = (0.5 * (fslider2 * (1 - faustpower<2>(fSlow0))));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec0[0] = ((fSlow3 * (fVec0[0] - fVec0[2])) + (fSlow0 * ((fRec0[1] * ((iSlow2)?max(-0.6, min(0.6, fVec0[0])):fSlow1)) - (fSlow0 * fRec0[2]))));
		output0[i] = (FAUSTFLOAT)(fVec0[0] + fRec0[0]);
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fVec0[2] = fVec0[1]; fVec0[1] = fVec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerVar("IR.peak","","S","peak gain",&fslider2, 1.0, 0.0, 1e+01, 0.2);
	static const char *fcheckbox0_values[] = {"manual","auto",0};
	registerEnumVar("IR.auto_freq","auto freq","B","",fcheckbox0_values,&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	registerVar("IR.freq","","S","frequency (Hz)",&fslider1, 4.4e+02, 2e+01, 1.2e+04, 1e+01);
	registerVar("IR.bandwidth","","S","bandwidth (Hz)",&fslider0, 1e+02, 2e+01, 2e+04, 1e+01);
	registerInit("IR", init);
}

} // end namespace impulseresponse
