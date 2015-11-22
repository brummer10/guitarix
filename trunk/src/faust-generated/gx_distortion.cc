// generated from file '../src/faust/gx_distortion.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace gx_distortion {

class Dsp: public PluginDef {
private:
	gx_resample::FixedRateResampler smp;
	int samplingFreq;
	int fSamplingFreq;
	int 	iVec0[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	FAUSTFLOAT 	fslider0;
	double 	fRec2[2];
	FAUSTFLOAT 	fentry0;
	double 	fConst6;
	FAUSTFLOAT 	fentry1;
	FAUSTFLOAT 	fentry2;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	int 	IOTA;
	double 	fVec1[4096];
	FAUSTFLOAT 	fslider3;
	double 	fRec12[2];
	FAUSTFLOAT 	fcheckbox0;
	double 	fRec13[2];
	double 	fRec11[3];
	double 	fVec2[2];
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fRec10[2];
	double 	fRec9[2];
	double 	fRec8[3];
	double 	fVec3[2];
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fVec4[2];
	double 	fRec5[2];
	double 	fRec4[3];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT 	fslider7;
	double 	fRec14[2];
	double 	fRec16[2];
	double 	fRec15[3];
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT 	fslider9;
	double 	fRec17[2];
	double 	fRec20[2];
	double 	fRec19[3];
	double 	fRec18[3];
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT 	fslider11;
	double 	fRec21[2];
	double 	fRec25[2];
	double 	fRec24[3];
	double 	fRec23[3];
	double 	fRec22[3];
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT 	fslider13;
	double 	fRec26[2];
	double 	fVec5[2];
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fRec3[2];
	double 	fVec6[2];
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fRec1[2];
	double 	fRec0[3];
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



static const char* parm_groups[] = {
	"resonator", N_("Distortion resonator"),
	0
	};

Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "gx_distortion";
	name = N_("Multi Band Distortion");
	groups = parm_groups;
	description = ""; // description (tooltip)
	category = N_("Distortion");       // category
	shortname = N_("Distortion");     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	load_ui = load_ui_f_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<4096; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<3; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int RsamplingFreq)
{
	samplingFreq = 192000;
	smp.setup(RsamplingFreq, samplingFreq);
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = tan((50265.48245743669 / double(iConst0)));
	fConst2 = (2 * (1 - (1.0 / faustpower<2>(fConst1))));
	fConst3 = (1.0 / fConst1);
	fConst4 = (1 + ((fConst3 - 1.0000000000000004) / fConst1));
	fConst5 = (1.0 / (1 + ((1.0000000000000004 + fConst3) / fConst1)));
	fConst6 = (3.141592653589793 / double(iConst0));
	fConst7 = tan((47123.8898038469 / double(iConst0)));
	fConst8 = (2 * (1 - (1.0 / faustpower<2>(fConst7))));
	fConst9 = (1.0 / fConst7);
	fConst10 = (1 + ((fConst9 - 1.414213562373095) / fConst7));
	fConst11 = (1 + ((1.414213562373095 + fConst9) / fConst7));
	fConst12 = (1.0 / fConst11);
	IOTA = 0;
	fConst13 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst14 = (0 - fConst13);
	fConst15 = (1 + fConst13);
	fConst16 = (1.0 / (fConst15 * fConst11));
	fConst17 = (0 - ((1 - fConst13) / fConst15));
	fConst18 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst19 = (1 + fConst18);
	fConst20 = (1.0 / fConst19);
	fConst21 = (0 - ((1 - fConst18) / fConst19));
	fConst22 = (1 + fConst3);
	fConst23 = (1.0 / fConst22);
	fConst24 = (0 - ((1 - fConst3) / fConst22));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	float buf[smp.max_out_count(count)];
	int ReCount = smp.up(count, input0, buf);
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * (double(fslider0) - 10))));
	double 	fSlow1 = tan((fConst6 * double(fentry0)));
	double 	fSlow2 = (1.0 / faustpower<2>(fSlow1));
	double 	fSlow3 = (2 * (1 - fSlow2));
	double 	fSlow4 = (1.0 / fSlow1);
	double 	fSlow5 = (1 + ((fSlow4 - 1.0000000000000004) / fSlow1));
	double 	fSlow6 = (1 + ((1.0000000000000004 + fSlow4) / fSlow1));
	double 	fSlow7 = (1.0 / fSlow6);
	double 	fSlow8 = tan((fConst6 * double(fentry1)));
	double 	fSlow9 = (1.0 / faustpower<2>(fSlow8));
	double 	fSlow10 = (2 * (1 - fSlow9));
	double 	fSlow11 = (1.0 / fSlow8);
	double 	fSlow12 = (1 + ((fSlow11 - 1.0000000000000004) / fSlow8));
	double 	fSlow13 = (1 + ((1.0000000000000004 + fSlow11) / fSlow8));
	double 	fSlow14 = (1.0 / fSlow13);
	double 	fSlow15 = tan((fConst6 * double(fentry2)));
	double 	fSlow16 = (1.0 / faustpower<2>(fSlow15));
	double 	fSlow17 = (2 * (1 - fSlow16));
	double 	fSlow18 = (1.0 / fSlow15);
	double 	fSlow19 = (1 + ((fSlow18 - 1.0000000000000004) / fSlow15));
	double 	fSlow20 = (1 + ((1.0000000000000004 + fSlow18) / fSlow15));
	double 	fSlow21 = (1.0 / fSlow20);
	double 	fSlow22 = (0.01 * double(fslider1));
	double 	fSlow23 = (1.0 - double(fslider2));
	double 	fSlow24 = double(fslider3);
	int 	iSlow25 = int((int(fSlow24) & 4095));
	int 	iSlow26 = int((int((fSlow24 - 1)) & 4095));
	int 	iSlow27 = int(double(fcheckbox0));
	double 	fSlow28 = (1 + fSlow18);
	double 	fSlow29 = (1.0 / fSlow28);
	double 	fSlow30 = (0 - ((1 - fSlow18) / fSlow28));
	double 	fSlow31 = (1 + fSlow11);
	double 	fSlow32 = (1.0 / fSlow31);
	double 	fSlow33 = (0 - ((1 - fSlow11) / fSlow31));
	double 	fSlow34 = (1 + fSlow4);
	double 	fSlow35 = (1.0 / fSlow34);
	double 	fSlow36 = (0 - ((1 - fSlow4) / fSlow34));
	double 	fSlow37 = double(fslider5);
	double 	fSlow38 = (pow(1e+01,(2 * (fSlow37 * double(fslider4)))) / fSlow6);
	double 	fSlow39 = double(fslider6);
	double 	fSlow40 = (0.0010000000000000009 * pow(10,(0.05 * (double(fslider7) - 10))));
	double 	fSlow41 = (0 - fSlow4);
	double 	fSlow42 = (1.0 / (fSlow1 * fSlow13));
	double 	fSlow43 = (2 * (0 - fSlow2));
	double 	fSlow44 = (pow(1e+01,(2 * (fSlow37 * double(fslider8)))) / fSlow6);
	double 	fSlow45 = (0.0010000000000000009 * pow(10,(0.05 * (double(fslider9) - 10))));
	double 	fSlow46 = (1 + ((fSlow4 - 1.0) / fSlow1));
	double 	fSlow47 = (1.0 / (1 + ((1.0 + fSlow4) / fSlow1)));
	double 	fSlow48 = (0 - fSlow11);
	double 	fSlow49 = (1.0 / (fSlow8 * fSlow20));
	double 	fSlow50 = (2 * (0 - fSlow9));
	double 	fSlow51 = pow(1e+01,(2 * (fSlow37 * double(fslider10))));
	double 	fSlow52 = (0.0010000000000000009 * pow(10,(0.05 * (double(fslider11) - 10))));
	double 	fSlow53 = (1 + ((fSlow11 - 1.0) / fSlow8));
	double 	fSlow54 = (1.0 / (1 + ((1.0 + fSlow11) / fSlow8)));
	double 	fSlow55 = (0 - fSlow18);
	double 	fSlow56 = (2 * (0 - fSlow16));
	double 	fSlow57 = pow(1e+01,(2 * (fSlow37 * double(fslider12))));
	double 	fSlow58 = (0.0010000000000000009 * pow(10,(0.05 * (double(fslider13) - 10))));
	double 	fSlow59 = (1 - fSlow22);
	for (int i=0; i<ReCount; i++) {
		iVec0[0] = 1;
		fRec2[0] = ((0.999 * fRec2[1]) + fSlow0);
		double fTemp0 = (double)buf[i];
		double fTemp1 = (fSlow22 * fTemp0);
		double fTemp2 = (fTemp1 + (fSlow23 * fRec12[1]));
		fVec1[IOTA&4095] = fTemp2;
		fRec12[0] = (0.5 * (fVec1[(IOTA-iSlow26)&4095] + fVec1[(IOTA-iSlow25)&4095]));
		fRec13[0] = ((1e-20 * (1 - iVec0[1])) - fRec13[1]);
		fRec11[0] = ((fRec13[0] + ((iSlow27)?fRec12[0]:fTemp1)) - (fConst12 * ((fConst10 * fRec11[2]) + (fConst8 * fRec11[1]))));
		double fTemp3 = (fRec11[2] + (fRec11[0] + (2 * fRec11[1])));
		fVec2[0] = fTemp3;
		fRec10[0] = ((fConst17 * fRec10[1]) + (fConst16 * ((fConst13 * fVec2[0]) + (fConst14 * fVec2[1]))));
		fRec9[0] = ((fSlow30 * fRec9[1]) + (fSlow29 * (fRec10[0] + fRec10[1])));
		fRec8[0] = (fRec9[0] - (fSlow21 * ((fSlow19 * fRec8[2]) + (fSlow17 * fRec8[1]))));
		double fTemp4 = (fRec8[2] + (fRec8[0] + (2 * fRec8[1])));
		double fTemp5 = (fSlow21 * fTemp4);
		fVec3[0] = fTemp5;
		fRec7[0] = ((fSlow33 * fRec7[1]) + (fSlow32 * (fVec3[0] + fVec3[1])));
		fRec6[0] = (fRec7[0] - (fSlow14 * ((fSlow12 * fRec6[2]) + (fSlow10 * fRec6[1]))));
		double fTemp6 = (fRec6[2] + (fRec6[0] + (2 * fRec6[1])));
		double fTemp7 = (fSlow14 * fTemp6);
		fVec4[0] = fTemp7;
		fRec5[0] = ((fSlow36 * fRec5[1]) + (fSlow35 * (fVec4[0] + fVec4[1])));
		fRec4[0] = (fRec5[0] - (fSlow7 * ((fSlow5 * fRec4[2]) + (fSlow3 * fRec4[1]))));
		double fTemp8 = max((double)-1, min((double)1, (fSlow39 + (fSlow38 * (fRec4[2] + (fRec4[0] + (2 * fRec4[1])))))));
		fRec14[0] = ((0.999 * fRec14[1]) + fSlow40);
		fRec16[0] = ((fSlow36 * fRec16[1]) + (fSlow35 * ((fSlow42 * fTemp6) + (fSlow41 * fVec4[1]))));
		fRec15[0] = (fRec16[0] - (fSlow7 * ((fSlow5 * fRec15[2]) + (fSlow3 * fRec15[1]))));
		double fTemp9 = max((double)-1, min((double)1, (fSlow39 + (fSlow44 * (((fSlow2 * fRec15[0]) + (fSlow43 * fRec15[1])) + (fSlow2 * fRec15[2]))))));
		fRec17[0] = ((0.999 * fRec17[1]) + fSlow45);
		double fTemp10 = (fSlow3 * fRec18[1]);
		fRec20[0] = ((fSlow33 * fRec20[1]) + (fSlow32 * ((fSlow49 * fTemp4) + (fSlow48 * fVec3[1]))));
		fRec19[0] = (fRec20[0] - (fSlow14 * ((fSlow12 * fRec19[2]) + (fSlow10 * fRec19[1]))));
		fRec18[0] = ((fSlow14 * (((fSlow9 * fRec19[0]) + (fSlow50 * fRec19[1])) + (fSlow9 * fRec19[2]))) - (fSlow47 * ((fSlow46 * fRec18[2]) + fTemp10)));
		double fTemp11 = max((double)-1, min((double)1, (fSlow39 + (fSlow51 * (fRec18[2] + (fSlow47 * (fTemp10 + (fSlow46 * fRec18[0]))))))));
		fRec21[0] = ((0.999 * fRec21[1]) + fSlow52);
		double fTemp12 = (fSlow3 * fRec22[1]);
		double fTemp13 = (fSlow10 * fRec23[1]);
		fRec25[0] = ((fSlow30 * fRec25[1]) + (fSlow29 * ((fSlow18 * fRec10[0]) + (fSlow55 * fRec10[1]))));
		fRec24[0] = (fRec25[0] - (fSlow21 * ((fSlow19 * fRec24[2]) + (fSlow17 * fRec24[1]))));
		fRec23[0] = ((fSlow21 * (((fSlow16 * fRec24[0]) + (fSlow56 * fRec24[1])) + (fSlow16 * fRec24[2]))) - (fSlow54 * ((fSlow53 * fRec23[2]) + fTemp13)));
		fRec22[0] = ((fRec23[2] + (fSlow54 * (fTemp13 + (fSlow53 * fRec23[0])))) - (fSlow47 * ((fSlow46 * fRec22[2]) + fTemp12)));
		double fTemp14 = max((double)-1, min((double)1, (fSlow39 + (fSlow57 * (fRec22[2] + (fSlow47 * (fTemp12 + (fSlow46 * fRec22[0]))))))));
		fRec26[0] = ((0.999 * fRec26[1]) + fSlow58);
		double fTemp15 = (((((fRec26[0] * fTemp14) * (1 - (0.3333333333333333 * faustpower<2>(fTemp14)))) + ((fRec21[0] * fTemp11) * (1 - (0.3333333333333333 * faustpower<2>(fTemp11))))) + ((fRec17[0] * fTemp9) * (1 - (0.3333333333333333 * faustpower<2>(fTemp9))))) + ((fRec14[0] * fTemp8) * (1 - (0.3333333333333333 * faustpower<2>(fTemp8)))));
		fVec5[0] = fTemp15;
		fRec3[0] = ((fConst21 * fRec3[1]) + (fConst20 * (fVec5[0] + fVec5[1])));
		double fTemp16 = (fRec3[0] * fRec2[0]);
		fVec6[0] = fTemp16;
		fRec1[0] = ((fConst24 * fRec1[1]) + (fConst23 * (fVec6[0] + fVec6[1])));
		fRec0[0] = (fRec1[0] - (fConst5 * ((fConst4 * fRec0[2]) + (fConst2 * fRec0[1]))));
		buf[i] = (FAUSTFLOAT)((fSlow59 * fTemp0) + (fConst5 * (fRec0[2] + (fRec0[0] + (2 * fRec0[1])))));
		// post processing
		fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fVec6[1] = fVec6[0];
		fRec3[1] = fRec3[0];
		fVec5[1] = fVec5[0];
		fRec26[1] = fRec26[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec21[1] = fRec21[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec17[1] = fRec17[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fRec14[1] = fRec14[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec4[1] = fVec4[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fVec3[1] = fVec3[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fVec2[1] = fVec2[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		IOTA = IOTA+1;
		fRec2[1] = fRec2[0];
		iVec0[1] = iVec0[0];
	}
	smp.down(buf, output0);

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("gx_distortion.drive","","S","",&fslider5, 0.64, 0.0, 1.0, 0.01);
	reg.registerVar("gx_distortion.gain","","S","",&fslider0, 2.0, -1e+01, 1e+01, 0.1);
	reg.registerVar("gx_distortion.high_drive",N_("high"),"S","",&fslider12, 1.0, 0.0, 1.0, 0.01);
	reg.registerVar("gx_distortion.high_gain",N_("high"),"S","",&fslider13, 1e+01, -1e+01, 2e+01, 0.1);
	reg.registerVar("gx_distortion.level","","S","",&fslider6, 0.0, 0.0, 0.5, 0.01);
	reg.registerVar("gx_distortion.low_drive",N_("low"),"S","",&fslider4, 1.0, 0.0, 1.0, 0.01);
	reg.registerVar("gx_distortion.low_gain",N_("low"),"S","",&fslider7, 1e+01, -1e+01, 2e+01, 0.1);
	reg.registerVar("gx_distortion.middle_h_drive",N_("middle h."),"S","",&fslider10, 1.0, 0.0, 1.0, 0.01);
	reg.registerVar("gx_distortion.middle_h_gain",N_("middle h."),"S","",&fslider11, 1e+01, -1e+01, 2e+01, 0.1);
	reg.registerVar("gx_distortion.middle_l_drive",N_("middle l."),"S","",&fslider8, 1.0, 0.0, 1.0, 0.01);
	reg.registerVar("gx_distortion.middle_l_gain",N_("middle l."),"S","",&fslider9, 1e+01, -1e+01, 2e+01, 0.1);
	reg.registerVar("gx_distortion.resonator.on_off",N_("resonat"),"B","",&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("gx_distortion.split_high_freq","","S","",&fentry2, 1.25e+03, 1.25e+03, 1.2e+04, 1e+01);
	reg.registerVar("gx_distortion.split_low_freq","","S","",&fentry0, 2.5e+02, 2e+01, 6e+02, 1e+01);
	reg.registerVar("gx_distortion.split_middle_freq","","S","",&fentry1, 6.5e+02, 6e+02, 1.25e+03, 1e+01);
	reg.registerVar("gx_distortion.trigger","","S","",&fslider2, 0.12, 0.0, 1.0, 0.01);
	reg.registerVar("gx_distortion.vibrato","","S","",&fslider3, 1.0, 0.0, 1.0, 0.01);
	reg.registerVar("gx_distortion.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider1, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade_file("gx_distortion_ui.glade");
        return 0;
    }
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("gx_distortion" "." p)
// ----- distortion
b.openHorizontalhideBox("");
b.create_master_slider("gx_distortion.drive", _("drive"));
b.closeBox();
b.openHorizontalBox("");
{
    b.openVerticalBox("");
    {
	b.openVerticalBox("");
	{
	    b.openFlipLabelBox(_("  drive "));
	    {
		b.openHorizontalBox("");
		{
		    b.create_small_rackknobr("gx_distortion.drive", _("  drive "));
		    b.create_small_rackknobr("gx_distortion.low_drive", _(" low "));
		    b.create_small_rackknobr("gx_distortion.middle_l_drive", _(" middle l. "));
		    b.create_small_rackknobr("gx_distortion.middle_h_drive", _(" middle h. "));
		    b.create_small_rackknobr("gx_distortion.high_drive", _(" high "));
		}
		b.closeBox();
	    }
	    b.closeBox();
	    b.openFlipLabelBox(_("  gain  "));
	    {
		b.openHorizontalBox("");
		{
		    b.create_small_rackknob("gx_distortion.gain", _("  gain  "));
		    b.create_small_rackknob("gx_distortion.low_gain", _(" low "));
		    b.create_small_rackknob("gx_distortion.middle_l_gain", _(" middle l. "));
		    b.create_small_rackknob("gx_distortion.middle_h_gain", _(" middle h. "));
		    b.create_small_rackknob("gx_distortion.high_gain", _(" high "));
		}
		b.closeBox();
	    }
	    b.closeBox();
	}
	b.closeBox();

	b.openHorizontalBox("");
	{
	    b.create_small_rackknob("gx_distortion.wet_dry", _("dry/wet"));
	    b.create_small_rackknob("gx_distortion.level", _("  level  "));
	    b.openVerticalBox(_("frequency split Hz"));
	    {
		b.openpaintampBox("");
		{
		    b.openHorizontalBox("");
		    {
			b.insertSpacer();
			b.create_wheel("gx_distortion.split_low_freq", _("split low freq"));
			b.insertSpacer();
			b.create_wheel("gx_distortion.split_middle_freq", _("split m. freq"));
			b.insertSpacer();
			b.create_wheel("gx_distortion.split_high_freq", _("split high freq"));
			b.insertSpacer();
		    }
		    b.closeBox();
		}
		b.closeBox();
	    }
	    b.closeBox();
	}
	b.closeBox();
    }
    b.closeBox();

    b.openVerticalBox(_("resonator"));
    {
	b.create_small_rackknob("gx_distortion.trigger", _("trigger "));
	b.create_small_rackknob("gx_distortion.vibrato", _(" vibrato "));
	b.create_switch_no_caption(sw_switchit, "gx_distortion.resonator.on_off");
    }
    b.closeBox();
}
b.closeBox();

#undef PARAM
        return 0;
    }
	return -1;
}

int Dsp::load_ui_f_static(const UiBuilder& b, int form)
{
	return static_cast<Dsp*>(b.plugin)->load_ui_f(b, form);
}
PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace gx_distortion
