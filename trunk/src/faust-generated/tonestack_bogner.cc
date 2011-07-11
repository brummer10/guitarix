namespace tonestack_bogner {
// generated from file '../src/faust/tonestack_bogner.dsp'

FAUSTFLOAT&	fslider0 = get_alias("amp.tonestack.Middle");
FAUSTFLOAT&	fslider1 = get_alias("amp.tonestack.Bass");
double 	fConst0;
double 	fConst1;
double 	fConst2;
double 	fRec0[4];
FAUSTFLOAT&	fslider2 = get_alias("amp.tonestack.Treble");
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (2 * double(fSamplingFreq));
	fConst1 = faustpower<2>(fConst0);
	fConst2 = (3 * fConst0);
	for (int i=0; i<4; i++) fRec0[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (7.790052600000002e-07 * fSlow0);
	double 	fSlow2 = exp((3.4 * (fslider1 - 1)));
	double 	fSlow3 = (1.4106061200000003e-06 + ((3.7475640000000014e-05 * fSlow2) + (fSlow0 * (((2.3606220000000006e-05 * fSlow2) - 3.2220474e-07) - fSlow1))));
	double 	fSlow4 = ((1.5406083e-09 * fSlow2) - (5.08400739e-11 * fSlow0));
	double 	fSlow5 = (1.9775250000000004e-09 * fSlow2);
	double 	fSlow6 = (6.5258325e-11 + (fSlow5 + (fSlow0 * (fSlow4 - 1.4418251099999996e-11))));
	double 	fSlow7 = (fConst0 * fSlow6);
	double 	fSlow8 = (0.001551 * fSlow0);
	double 	fSlow9 = (0.015220000000000001 * fSlow2);
	double 	fSlow10 = (fConst0 * (0.0037192600000000003 + (fSlow9 + fSlow8)));
	double 	fSlow11 = ((fSlow10 + (fConst1 * (fSlow7 - fSlow3))) - 1);
	double 	fSlow12 = (fConst2 * fSlow6);
	double 	fSlow13 = ((fConst1 * (fSlow3 + fSlow12)) - (3 + fSlow10));
	double 	fSlow14 = ((fSlow10 + (fConst1 * (fSlow3 - fSlow12))) - 3);
	double 	fSlow15 = (1.0 / (0 - (1 + (fSlow10 + (fConst1 * (fSlow3 + fSlow7))))));
	double 	fSlow16 = fslider2;
	double 	fSlow17 = ((fSlow0 * (5.08400739e-11 + fSlow4)) + (fSlow16 * ((6.5258325e-11 - (6.5258325e-11 * fSlow0)) + fSlow5)));
	double 	fSlow18 = (fConst2 * fSlow17);
	double 	fSlow19 = (5.018112e-08 + (((1.7391e-07 * fSlow16) + (fSlow0 * (8.643102600000002e-07 - fSlow1))) + (fSlow2 * (1.5206400000000001e-06 + (2.3606220000000006e-05 * fSlow0)))));
	double 	fSlow20 = (0.0005022600000000001 + (fSlow9 + (fSlow8 + (5.4999999999999995e-05 * fSlow16))));
	double 	fSlow21 = (fConst0 * fSlow20);
	double 	fSlow22 = (fSlow21 + (fConst1 * (fSlow19 - fSlow18)));
	double 	fSlow23 = (fConst0 * fSlow17);
	double 	fSlow24 = (fSlow21 + (fConst1 * (fSlow23 - fSlow19)));
	double 	fSlow25 = (fConst0 * (0 - fSlow20));
	double 	fSlow26 = (fSlow25 + (fConst1 * (fSlow19 + fSlow18)));
	double 	fSlow27 = (fSlow25 - (fConst1 * (fSlow19 + fSlow23)));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((double)input0[i] - (fSlow15 * (((fSlow14 * fRec0[2]) + (fSlow13 * fRec0[1])) + (fSlow11 * fRec0[3]))));
		output0[i] = (FAUSTFLOAT)(fSlow15 * ((fSlow27 * fRec0[0]) + ((fSlow26 * fRec0[1]) + ((fSlow24 * fRec0[3]) + (fSlow22 * fRec0[2])))));
		// post processing
		for (int i=3; i>0; i--) fRec0[i] = fRec0[i-1];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerInit("amp.tonestack", init);
}

} // end namespace tonestack_bogner
