// generated from file '../src/faust/flanger.dsp' by dsp2cc:
// Code generated with Faust 0.9.30 (http://faust.grame.fr)

namespace flanger {
static FAUSTFLOAT 	fslider0;
static int 	iVec0[2];
static FAUSTFLOAT 	fslider1;
static int 	IOTA;
static double 	fVec1[2048];
static FAUSTFLOAT 	fslider2;
static double 	fConst0;
static double 	fRec1[2];
static double 	fRec2[2];
static FAUSTFLOAT 	fslider3;
static FAUSTFLOAT 	fslider4;
static double 	fRec0[2];
static FAUSTFLOAT 	fslider5;
static FAUSTFLOAT 	fcheckbox0;
static double 	fVec2[2048];
static double 	fRec3[2];
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2048; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2048; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
}

static void init(int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	IOTA = 0;
	fConst0 = (6.283185307179586 / fSamplingFreq);
	clear_state();
}

static void compute(int count, float *input0, float *input1, float *output0, float *output1)
{
	double 	fSlow0 = pow(10,(0.05 * fslider0));
	double 	fSlow1 = fslider1;
	double 	fSlow2 = (fConst0 * fslider2);
	double 	fSlow3 = sin(fSlow2);
	double 	fSlow4 = cos(fSlow2);
	double 	fSlow5 = (0 - fSlow3);
	double 	fSlow6 = (0.0005 * fslider3);
	double 	fSlow7 = (0.001 * fslider4);
	double 	fSlow8 = fslider5;
	double 	fSlow9 = ((int(fcheckbox0))?(0 - fSlow8):fSlow8);
	for (int i=0; i<count; i++) {
		double fTemp0 = (fSlow0 * (double)input0[i]);
		iVec0[0] = 1;
		double fTemp1 = ((fSlow1 * fRec0[1]) - fTemp0);
		fVec1[IOTA&2047] = fTemp1;
		fRec1[0] = ((fSlow4 * fRec1[1]) + (fSlow3 * fRec2[1]));
		fRec2[0] = ((1 + ((fSlow5 * fRec1[1]) + (fSlow4 * fRec2[1]))) - iVec0[1]);
		double fTemp2 = (fSamplingFreq * (fSlow7 + (fSlow6 * (1 + fRec1[0]))));
		int iTemp3 = int(fTemp2);
		int iTemp4 = (1 + iTemp3);
		fRec0[0] = (((fTemp2 - iTemp3) * fVec1[(IOTA-int((int(iTemp4) & 2047)))&2047]) + ((iTemp4 - fTemp2) * fVec1[(IOTA-int((iTemp3 & 2047)))&2047]));
		output0[i] = (FAUSTFLOAT)(0.5 * (fTemp0 + (fSlow9 * fRec0[0])));
		double fTemp5 = (fSlow0 * (double)input1[i]);
		double fTemp6 = ((fSlow1 * fRec3[1]) - fTemp5);
		fVec2[IOTA&2047] = fTemp6;
		double fTemp7 = (fSamplingFreq * (fSlow7 + (fSlow6 * (1 + fRec2[0]))));
		int iTemp8 = int(fTemp7);
		int iTemp9 = (1 + iTemp8);
		fRec3[0] = (((fTemp7 - iTemp8) * fVec2[(IOTA-int((int(iTemp9) & 2047)))&2047]) + ((iTemp9 - fTemp7) * fVec2[(IOTA-int((iTemp8 & 2047)))&2047]));
		output1[i] = (FAUSTFLOAT)(0.5 * (fTemp5 + (fSlow9 * fRec3[0])));
		// post processing
		fRec3[1] = fRec3[0];
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		IOTA = IOTA+1;
		iVec0[1] = iVec0[0];
	}
}

static int register_params(const ParamReg& reg)
{
	static const value_pair fcheckbox0_values[] = {{"linear"},{"invert"},{0}};
	reg.registerEnumVar("flanger.invert","","B","",fcheckbox0_values,&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("flanger.depth","","S","",&fslider5, 1.0, 0.0, 1.0, 0.01);
	reg.registerVar("flanger.flange delay offset","","S","",&fslider4, 1.0, 0.0, 2e+01, 0.01);
	reg.registerVar("flanger.flange delay","","S","",&fslider3, 1e+01, 0.0, 2e+01, 0.01);
	reg.registerVar("flanger.LFO freq","","S","",&fslider2, 0.2, 0.0, 5.0, 0.01);
	reg.registerVar("flanger.feedback gain","","S","",&fslider1, 0.0, 0.0, 1.0, 0.01);
	reg.registerVar("flanger.level","","S","",&fslider0, 0.0, -6e+01, 1e+01, 0.1);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "flanger",  // id
    N_("Flanger"),  // name
    0,  // groups
    0,  // mono_audio
    compute,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace flanger
