// generated from file '../src/faust/tremolo.dsp' by dsp2cc:
// Code generated with Faust 0.9.43 (http://faust.grame.fr)

namespace tremolo {
static int 	iVec0[2];
static int 	iConst0;
static double 	fConst1;
static FAUSTFLOAT 	fslider0;
static double 	fConst2;
static int 	iRec2[2];
static int 	iRec1[2];
static double 	fConst3;
static double 	fRec5[2];
static double 	fRec4[2];
static double 	fRec3[2];
static FAUSTFLOAT 	fcheckbox0;
static FAUSTFLOAT 	fslider1;
static double 	fRec0[2];
static FAUSTFLOAT 	fslider2;
static int	fSamplingFreq;

static void clear_state(PluginDef* = 0)
{
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) iRec2[i] = 0;
	for (int i=0; i<2; i++) iRec1[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

static void init(int samplingFreq, PluginDef* = 0)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / iConst0);
	fConst2 = (0.5 * iConst0);
	fConst3 = (6.283185307179586 / iConst0);
	clear_state();
}

static void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = fslider0;
	int 	iSlow1 = int((fConst2 / double(fSlow0)));
	double 	fSlow2 = (1.0 / iSlow1);
	double 	fSlow3 = (fConst3 * fSlow0);
	int 	iSlow4 = int(fcheckbox0);
	double 	fSlow5 = fslider1;
	double 	fSlow6 = fslider2;
	double 	fSlow7 = (27.0 * fSlow6);
	double 	fSlow8 = (1 - (0.01 * fSlow6));
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		double fTemp0 = (fRec0[1] * (1 - (fConst1 / (fConst1 + (0.06 * exp((0 - (2.4849066497880004 * fRec0[1]))))))));
		iRec2[0] = ((int((iRec2[1] > 0)))?((2 * (iRec1[1] < iSlow1)) - 1):(1 - (2 * (iRec1[1] > 0))));
		iRec1[0] = (iRec2[0] + iRec1[1]);
		fRec5[0] = ((fSlow3 * (0 - fRec3[1])) + fRec5[1]);
		fRec4[0] = ((1 + ((fSlow3 * fRec5[0]) + fRec4[1])) - iVec0[1]);
		fRec3[0] = fRec4[0];
		fRec0[0] = (fTemp0 + (fConst1 * (pow((1 + (fSlow5 * (((iSlow4)?max(0, (0.5 * (1 + fRec3[0]))):(fSlow2 * iRec1[0])) - 1))),1.9) / (fConst1 + (0.06 * exp((0 - (2.4849066497880004 * fTemp0))))))));
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

static int register_params(const ParamReg& reg)
{
	reg.registerVar("tremolo.wet_dry","wet/dry","S","percentage of processed signal in output signal",&fslider2, 1e+02, 0.0, 1e+02, 1.0);
	static const value_pair fcheckbox0_values[] = {{"triangle"},{"sine"},{0}};
	reg.registerEnumVar("tremolo.SINE","","B","",fcheckbox0_values,&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("tremolo.depth","","S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("tremolo.freq","","S","",&fslider0, 5.0, 0.1, 5e+01, 0.1);
	return 0;
}

PluginDef plugin = {
    PLUGINDEF_VERSION,
    0,   // flags
    "tremolo",  // id
    N_("Tremolo"),  // name
    0,  // groups
    compute,  // mono_audio
    0,  // stereo_audio
    init,  // set_samplerate
    0,  // activate plugin
    register_params,
    0,   // load_ui
    clear_state,  // clear_state
};

} // end namespace tremolo
