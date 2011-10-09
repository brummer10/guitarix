// generated from file '../src/faust/compressor.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

namespace compressor {
static FAUSTFLOAT 	fentry0;
static FAUSTFLOAT 	fentry1;
static int 	iConst0;
static double 	fConst1;
static double 	fConst2;
static double 	fRec1[2];
static double 	fConst3;
static FAUSTFLOAT 	fslider0;
static FAUSTFLOAT 	fslider1;
static double 	fRec0[2];
static FAUSTFLOAT 	fentry2;
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

static void init(int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = exp((0 - (1e+01 / iConst0)));
	fConst2 = (1 - fConst1);
	fConst3 = (1.0 / iConst0);
	clear_state();
}

static void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fentry1;
	double 	fSlow1 = (fSlow0 - fentry0);
	double 	fSlow2 = exp((0 - (fConst3 / max(fConst3, fslider0))));
	double 	fSlow3 = exp((0 - (fConst3 / max(fConst3, fslider1))));
	double 	fSlow4 = (1.0 / (0.001 + fSlow0));
	double 	fSlow5 = (fentry2 - 1);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec1[0] = ((fConst2 * fabs((fTemp0 + 1e-20))) + (fConst1 * fRec1[1]));
		double fTemp1 = ((fSlow3 * (fRec0[1] >= fRec1[0])) + (fSlow2 * (fRec0[1] < fRec1[0])));
		fRec0[0] = ((fRec1[0] * (0 - (fTemp1 - 1))) + (fRec0[1] * fTemp1));
		double fTemp2 = max(0, ((20 * log10(fRec0[0])) + fSlow1));
		double fTemp3 = (fSlow5 * min(1, max(0, (fSlow4 * fTemp2))));
		output0[i] = (FAUSTFLOAT)(fTemp0 * pow(10,(0.05 * ((fTemp2 * (0 - fTemp3)) / (1 + fTemp3)))));
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
	}
}

static int register_params(const ParamReg& reg)
{
	reg.registerVar("compressor.ratio","","S","",&fentry2, 2.0, 1.0, 2e+01, 0.1);
	reg.registerVar("compressor.knee","","S","",&fentry1, 3.0, 0.0, 2e+01, 0.1);
	reg.registerVar("compressor.threshold","","S","",&fentry0, -2e+01, -96.0, 1e+01, 0.1);
	reg.registerVar("compressor.release","","S","",&fslider1, 0.5, 0.0, 1e+01, 0.01);
	reg.registerVar("compressor.attack","","S","",&fslider0, 0.002, 0.0, 1.0, 0.001);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "compressor",  // id
    N_("Compressor"),  // name
    0,  // groups
    compute,  // mono_audio
    0,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace compressor
