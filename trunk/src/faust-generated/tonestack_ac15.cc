// generated from file '../src/faust/tonestack_ac15.dsp' by dsp2cc:
namespace tonestack_ac15 {
static FAUSTFLOAT&	fslider0 = get_alias("amp.tonestack.Middle");
static FAUSTFLOAT&	fslider1 = get_alias("amp.tonestack.Bass");
static double 	fConst0;
static double 	fConst1;
static double 	fConst2;
static double 	fConst3;
static double 	fConst4;
static double 	fRec0[4];
static FAUSTFLOAT&	fslider2 = get_alias("amp.tonestack.Treble");
static double 	fConst5;
static double 	fConst6;
static int	fSamplingFreq;

static void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(fSamplingFreq);
	fConst1 = (2 * fConst0);
	fConst2 = (1.0691560000000003e-08 * fConst1);
	fConst3 = faustpower<2>(fConst1);
	fConst4 = (3.2074680000000005e-08 * fConst1);
	for (int i=0; i<4; i++) fRec0[i] = 0;
	fConst5 = (3 * fConst1);
	fConst6 = (0.044206800000000004 * fConst0);
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (0.00022854915600000004 * fSlow0);
	double 	fSlow2 = exp((3.4 * (fslider1 - 1)));
	double 	fSlow3 = (0.00010871476000000002 + ((0.00010719478000000002 * fSlow2) + (fSlow0 * ((0.00012621831200000002 + (0.00022854915600000004 * fSlow2)) - fSlow1))));
	double 	fSlow4 = ((3.421299200000001e-08 * fSlow2) - (3.421299200000001e-08 * fSlow0));
	double 	fSlow5 = (1.0 + (fSlow2 + (93531720.34763868 * (fSlow0 * (2.3521432000000005e-08 + fSlow4)))));
	double 	fSlow6 = (fConst2 * fSlow5);
	double 	fSlow7 = (fConst1 * (0.036906800000000003 + ((0.022103400000000002 * fSlow2) + (0.01034 * fSlow0))));
	double 	fSlow8 = ((fSlow7 + (fConst3 * (fSlow6 - fSlow3))) - 1);
	double 	fSlow9 = (fConst4 * fSlow5);
	double 	fSlow10 = ((fConst3 * (fSlow3 + fSlow9)) - (3 + fSlow7));
	double 	fSlow11 = ((fSlow7 + (fConst3 * (fSlow3 - fSlow9))) - 3);
	double 	fSlow12 = (1.0 / ((fConst3 * (0 - (fSlow3 + fSlow6))) - (1 + fSlow7)));
	double 	fSlow13 = fslider2;
	double 	fSlow14 = ((fSlow0 * (3.421299200000001e-08 + fSlow4)) + (fSlow13 * ((1.0691560000000003e-08 - (1.0691560000000003e-08 * fSlow0)) + (1.0691560000000003e-08 * fSlow2))));
	double 	fSlow15 = (fConst5 * fSlow14);
	double 	fSlow16 = (3.7947800000000004e-06 + (((1.5199800000000001e-06 * fSlow13) + (fSlow0 * (0.00022961831200000004 - fSlow1))) + (fSlow2 * (3.7947800000000004e-06 + fSlow1))));
	double 	fSlow17 = (1.0 + (fSlow2 + ((0.0046780133373146215 * fSlow13) + (0.4678013337314621 * fSlow0))));
	double 	fSlow18 = (fConst6 * fSlow17);
	double 	fSlow19 = (fSlow18 + (fConst3 * (fSlow16 - fSlow15)));
	double 	fSlow20 = (fConst1 * fSlow14);
	double 	fSlow21 = (fSlow18 + (fConst3 * (fSlow20 - fSlow16)));
	double 	fSlow22 = (fConst1 * (0 - (0.022103400000000002 * fSlow17)));
	double 	fSlow23 = (fSlow22 + (fConst3 * (fSlow16 + fSlow15)));
	double 	fSlow24 = (fSlow22 - (fConst3 * (fSlow16 + fSlow20)));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((double)input0[i] - (fSlow12 * (((fSlow11 * fRec0[2]) + (fSlow10 * fRec0[1])) + (fSlow8 * fRec0[3]))));
		output0[i] = (FAUSTFLOAT)(fSlow12 * ((fSlow24 * fRec0[0]) + ((fSlow23 * fRec0[1]) + ((fSlow21 * fRec0[3]) + (fSlow19 * fRec0[2])))));
		// post processing
		for (int i=3; i>0; i--) fRec0[i] = fRec0[i-1];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerInit("amp.tonestack", init);
}

} // end namespace tonestack_ac15
