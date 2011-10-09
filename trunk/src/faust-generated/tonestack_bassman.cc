// generated from file '../src/faust/tonestack_bassman.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

namespace tonestack_bassman {
FAUSTFLOAT 	fslider0;
FAUSTFLOAT	*fslider0_;
#define fslider0 (*fslider0_)
FAUSTFLOAT 	fslider1;
FAUSTFLOAT	*fslider1_;
#define fslider1 (*fslider1_)
static double 	fConst0;
static double 	fConst1;
static double 	fConst2;
static double 	fRec0[4];
FAUSTFLOAT 	fslider2;
FAUSTFLOAT	*fslider2_;
#define fslider2 (*fslider2_)
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<4; i++) fRec0[i] = 0;
}

static void init(int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (2 * double(min(192000, max(1, fSamplingFreq))));
	fConst1 = faustpower<2>(fConst0);
	fConst2 = (3 * fConst0);
	clear_state();
}

static void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (2.5312500000000006e-07 * fSlow0);
	double 	fSlow2 = exp((3.4 * (fslider1 - 1)));
	double 	fSlow3 = (7.4525e-07 + ((2.4210000000000004e-05 * fSlow2) + (fSlow0 * (((1.0125e-05 * fSlow2) - 2.75625e-07) - fSlow1))));
	double 	fSlow4 = ((7.650000000000002e-10 * fSlow2) - (1.9125000000000002e-11 * fSlow0));
	double 	fSlow5 = (1.4000000000000001e-09 * fSlow2);
	double 	fSlow6 = (3.500000000000001e-11 + (fSlow5 + (fSlow0 * (fSlow4 - 1.5875000000000007e-11))));
	double 	fSlow7 = (fConst0 * fSlow6);
	double 	fSlow8 = (0.0005 * fSlow0);
	double 	fSlow9 = (0.02025 * fSlow2);
	double 	fSlow10 = (fConst0 * (0.0028087500000000005 + (fSlow9 + fSlow8)));
	double 	fSlow11 = ((fSlow10 + (fConst1 * (fSlow7 - fSlow3))) - 1);
	double 	fSlow12 = (fConst2 * fSlow6);
	double 	fSlow13 = ((fConst1 * (fSlow3 + fSlow12)) - (3 + fSlow10));
	double 	fSlow14 = ((fSlow10 + (fConst1 * (fSlow3 - fSlow12))) - 3);
	double 	fSlow15 = (1.0 / (0 - (1 + (fSlow10 + (fConst1 * (fSlow3 + fSlow7))))));
	double 	fSlow16 = fslider2;
	double 	fSlow17 = ((fSlow0 * (1.9125000000000002e-11 + fSlow4)) + (fSlow16 * ((3.500000000000001e-11 - (3.500000000000001e-11 * fSlow0)) + fSlow5)));
	double 	fSlow18 = (fConst2 * fSlow17);
	double 	fSlow19 = (4.525e-08 + (((1.4e-07 * fSlow16) + (fSlow0 * (2.8437500000000003e-07 - fSlow1))) + (fSlow2 * (1.8100000000000002e-06 + (1.0125e-05 * fSlow0)))));
	double 	fSlow20 = (0.00050625 + (fSlow9 + (fSlow8 + (6.25e-05 * fSlow16))));
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

static int register_params(const ParamReg& reg)
{
#undef fslider2
	fslider2_ = reg.registerVar("amp.tonestack.Treble","","SA","",&fslider2, 0.5, 0.0, 1.0, 0.01);
#undef fslider1
	fslider1_ = reg.registerVar("amp.tonestack.Bass","","SA","",&fslider1, 0.5, 0.0, 1.0, 0.01);
#undef fslider0
	fslider0_ = reg.registerVar("amp.tonestack.Middle","","SA","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "Bassman",  // id
    N_("Bassman"),  // name
    0,  // groups
    compute,  // mono_audio
    0,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace tonestack_bassman
