// generated from file '../src/faust/low_high_pass.dsp' by dsp2cc:
// Code generated with Faust 0.9.30 (http://faust.grame.fr)

namespace low_high_pass {
static int 	iVec0[2];
static FAUSTFLOAT 	fentry0;
static double 	fConst0;
static FAUSTFLOAT 	fentry1;
static double 	fRec2[2];
static double 	fVec1[2];
static double 	fRec1[2];
static double 	fRec0[2];
static FAUSTFLOAT 	fcheckbox0;
static FAUSTFLOAT 	fslider0;
static FAUSTFLOAT 	fslider1;
static double 	fVec2[2];
static double 	fRec6[2];
static double 	fVec3[2];
static double 	fRec5[2];
static double 	fRec4[3];
static double 	fRec3[3];
static FAUSTFLOAT 	fcheckbox1;
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
}

static void init(int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (3.141592653589793 / fSamplingFreq);
	clear_state();
}

static void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (1.0 / tan((fConst0 * fentry0)));
	double 	fSlow1 = (1 + fSlow0);
	double 	fSlow2 = (0 - ((1 - fSlow0) / fSlow1));
	double 	fSlow3 = (1.0 / tan((fConst0 * fentry1)));
	double 	fSlow4 = (1 + fSlow3);
	double 	fSlow5 = (0 - ((1 - fSlow3) / fSlow4));
	double 	fSlow6 = (1.0 / fSlow4);
	double 	fSlow7 = (0 - fSlow0);
	double 	fSlow8 = (1.0 / fSlow1);
	int 	iSlow9 = int(fcheckbox0);
	double 	fSlow10 = tan((fConst0 * fslider0));
	double 	fSlow11 = (2 * (1 - (1.0 / faustpower<2>(fSlow10))));
	double 	fSlow12 = (1.0 / fSlow10);
	double 	fSlow13 = (1 + ((fSlow12 - 0.7653668647301795) / fSlow10));
	double 	fSlow14 = (1.0 / (1 + ((0.7653668647301795 + fSlow12) / fSlow10)));
	double 	fSlow15 = (1 + ((fSlow12 - 1.8477590650225735) / fSlow10));
	double 	fSlow16 = (1.0 / (1 + ((1.8477590650225735 + fSlow12) / fSlow10)));
	double 	fSlow17 = (fConst0 * fslider1);
	double 	fSlow18 = (1.0 / (1 + fSlow17));
	double 	fSlow19 = (1 - fSlow17);
	int 	iSlow20 = int(fcheckbox1);
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		iVec0[0] = 1;
		fRec2[0] = ((1e-20 * (1 - iVec0[1])) - fRec2[1]);
		double fTemp1 = (fTemp0 + fRec2[0]);
		fVec1[0] = fTemp1;
		fRec1[0] = ((fSlow6 * (fVec1[0] + fVec1[1])) + (fSlow5 * fRec1[1]));
		fRec0[0] = ((fSlow8 * ((fSlow7 * fRec1[1]) + (fSlow0 * fRec1[0]))) + (fSlow2 * fRec0[1]));
		double fTemp2 = ((iSlow9)?fRec0[0]:fTemp0);
		double fTemp3 = (fRec2[0] + fTemp2);
		fVec2[0] = (fSlow18 * fTemp3);
		fRec6[0] = ((fSlow18 * (fTemp3 + (fSlow19 * fRec6[1]))) - fVec2[1]);
		fVec3[0] = (fSlow18 * fRec6[0]);
		fRec5[0] = ((fSlow18 * (fRec6[0] + (fSlow19 * fRec5[1]))) - fVec3[1]);
		fRec4[0] = (fRec5[0] - (fSlow16 * ((fSlow15 * fRec4[2]) + (fSlow11 * fRec4[1]))));
		fRec3[0] = ((fSlow16 * (fRec4[2] + (fRec4[0] + (2 * fRec4[1])))) - (fSlow14 * ((fSlow13 * fRec3[2]) + (fSlow11 * fRec3[1]))));
		output0[i] = (FAUSTFLOAT)((iSlow20)?(fSlow14 * (fRec3[2] + (fRec3[0] + (2 * fRec3[1])))):fTemp2);
		// post processing
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec3[1] = fVec3[0];
		fRec6[1] = fRec6[0];
		fVec2[1] = fVec2[0];
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fVec1[1] = fVec1[0];
		fRec2[1] = fRec2[0];
		iVec0[1] = iVec0[0];
	}
}

static int register_params(const ParamReg& reg)
{
	reg.registerVar("low_high_pass.lhc.on_off","low highcutoff","B","",&fcheckbox1, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("low_high_pass.lhp.on_off","low highpass","B","",&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("low_high_pass.lhp.low_freq","low freq","S","",&fentry1, 5e+03, 2e+01, 1.2e+04, 1e+01);
	reg.registerVar("low_high_pass.lhp.high_freq","high freq","S","",&fentry0, 1.3e+02, 2e+01, 7.04e+03, 1e+01);
	reg.registerVar("low_high_pass.lhc.low_freq","low freq","S","low-freq cutoff Hz",&fslider1, 1.3e+02, 2e+01, 1e+03, 1e+01);
	reg.registerVar("low_high_pass.lhc.high_freq","high freq","S","high-freq cutoff Hz",&fslider0, 5e+03, 1e+03, 1.2e+04, 1e+01);
	return 0;
}

static const char* groups[] = {
	".low_high_pass.lhp", N_("low_highpass"),
	".low_high_pass.lhc", N_("low_highcutoff"),
	0
	};

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "low_highpass",  // id
    N_("low high pass"),  // name
    groups,  // groups
    compute,  // mono_audio
    0,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace low_high_pass
