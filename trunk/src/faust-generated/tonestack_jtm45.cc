// generated from file '../src/faust/tonestack_jtm45.dsp' by dsp2cc:
namespace tonestack_jtm45 {
static FAUSTFLOAT&	fslider0 = get_alias("amp.tonestack.Middle");
static FAUSTFLOAT&	fslider1 = get_alias("amp.tonestack.Bass");
static double 	fConst0;
static double 	fConst1;
static double 	fConst2;
static double 	fRec0[4];
static FAUSTFLOAT&	fslider2 = get_alias("amp.tonestack.Treble");
static int	fSamplingFreq;

static void init(int samplingFreq)
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
	double 	fSlow1 = (3.0621250000000006e-07 * fSlow0);
	double 	fSlow2 = exp((3.4 * (fslider1 - 1)));
	double 	fSlow3 = (5.442360000000002e-07 + ((1.784904e-05 * fSlow2) + (fSlow0 * (((1.2248500000000003e-05 * fSlow2) - 5.596250000000005e-08) - fSlow1))));
	double 	fSlow4 = ((9.245610000000004e-10 * fSlow2) - (2.3114025000000008e-11 * fSlow0));
	double 	fSlow5 = (1.0781100000000005e-09 * fSlow2);
	double 	fSlow6 = (2.695275000000001e-11 + (fSlow5 + (fSlow0 * (fSlow4 - 3.8387250000000005e-12))));
	double 	fSlow7 = (fConst0 * fSlow6);
	double 	fSlow8 = (0.00055 * fSlow0);
	double 	fSlow9 = (0.02227 * fSlow2);
	double 	fSlow10 = (fConst0 * (0.00207625 + (fSlow9 + fSlow8)));
	double 	fSlow11 = ((fSlow10 + (fConst1 * (fSlow7 - fSlow3))) - 1);
	double 	fSlow12 = (fConst2 * fSlow6);
	double 	fSlow13 = ((fConst1 * (fSlow3 + fSlow12)) - (3 + fSlow10));
	double 	fSlow14 = ((fSlow10 + (fConst1 * (fSlow3 - fSlow12))) - 3);
	double 	fSlow15 = (1.0 / (0 - (1 + (fSlow10 + (fConst1 * (fSlow3 + fSlow7))))));
	double 	fSlow16 = fslider2;
	double 	fSlow17 = ((fSlow0 * (2.3114025000000008e-11 + fSlow4)) + (fSlow16 * ((2.695275000000001e-11 - (2.695275000000001e-11 * fSlow0)) + fSlow5)));
	double 	fSlow18 = (fConst2 * fSlow17);
	double 	fSlow19 = (4.6926e-08 + (((9.801000000000002e-08 * fSlow16) + (fSlow0 * (3.433375000000001e-07 - fSlow1))) + (fSlow2 * (1.8770400000000002e-06 + (1.2248500000000003e-05 * fSlow0)))));
	double 	fSlow20 = (0.0005567500000000001 + (fSlow9 + (fSlow8 + (6.75e-05 * fSlow16))));
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

} // end namespace tonestack_jtm45
