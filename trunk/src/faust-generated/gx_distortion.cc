// generated from file '../src/faust/gx_distortion.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace gx_distortion {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	double 	fRec0[2];
	FAUSTFLOAT 	fentry0;
	double 	fConst0;
	double 	fConst1;
	FAUSTFLOAT 	fentry1;
	FAUSTFLOAT 	fentry2;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fRec10[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	int 	IOTA;
	double 	fVec1[4096];
	FAUSTFLOAT 	fslider3;
	double 	fRec11[2];
	FAUSTFLOAT 	fcheckbox0;
	double 	fRec9[3];
	double 	fVec2[2];
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fRec8[2];
	double 	fRec7[2];
	double 	fRec6[3];
	double 	fVec3[2];
	double 	fRec5[2];
	double 	fRec4[3];
	double 	fVec4[2];
	double 	fRec3[2];
	double 	fRec2[3];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT 	fslider7;
	double 	fRec12[2];
	double 	fRec14[2];
	double 	fRec13[3];
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT 	fslider9;
	double 	fRec15[2];
	double 	fRec18[2];
	double 	fRec17[3];
	double 	fRec16[3];
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT 	fslider11;
	double 	fRec19[2];
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fRec21[3];
	double 	fRec20[3];
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT 	fslider13;
	double 	fRec24[2];
	double 	fVec5[2];
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fRec1[2];

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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<4096; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = (3.141592653589793 / fConst0);
	fConst2 = tan((47123.8898038469 / fConst0));
	fConst3 = (2 * (1 - (1.0 / faustpower<2>(fConst2))));
	fConst4 = (1.0 / fConst2);
	fConst5 = (1 + ((fConst4 - 1.414213562373095) / fConst2));
	fConst6 = (1 + ((1.414213562373095 + fConst4) / fConst2));
	fConst7 = (1.0 / fConst6);
	fConst8 = (1.0 / tan((97.38937226128358 / fConst0)));
	fConst9 = (0 - fConst8);
	fConst10 = (1 + fConst8);
	fConst11 = (1.0 / (fConst10 * fConst6));
	fConst12 = (0 - ((1 - fConst8) / fConst10));
	fConst13 = (1.0 / tan((20517.741620594938 / fConst0)));
	fConst14 = (1 + fConst13);
	fConst15 = (1.0 / fConst14);
	fConst16 = (0 - ((1 - fConst13) / fConst14));
	IOTA = 0;
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * (double(fslider0) - 10))));
	double 	fSlow1 = tan((fConst1 * double(fentry0)));
	double 	fSlow2 = (1.0 / fSlow1);
	double 	fSlow3 = (1 + ((fSlow2 - 1.0000000000000004) / fSlow1));
	double 	fSlow4 = (1.0 / faustpower<2>(fSlow1));
	double 	fSlow5 = (2 * (1 - fSlow4));
	double 	fSlow6 = (1 + ((fSlow2 + 1.0000000000000004) / fSlow1));
	double 	fSlow7 = (1.0 / fSlow6);
	double 	fSlow8 = tan((fConst1 * double(fentry1)));
	double 	fSlow9 = (1.0 / fSlow8);
	double 	fSlow10 = (1 + ((fSlow9 - 1.0000000000000004) / fSlow8));
	double 	fSlow11 = (1.0 / faustpower<2>(fSlow8));
	double 	fSlow12 = (2 * (1 - fSlow11));
	double 	fSlow13 = (1 + ((fSlow9 + 1.0000000000000004) / fSlow8));
	double 	fSlow14 = (1.0 / fSlow13);
	double 	fSlow15 = tan((fConst1 * double(fentry2)));
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
	double 	fSlow31 = (1 + fSlow9);
	double 	fSlow32 = (1.0 / fSlow31);
	double 	fSlow33 = (0 - ((1 - fSlow9) / fSlow31));
	double 	fSlow34 = (1 + fSlow2);
	double 	fSlow35 = (1.0 / fSlow34);
	double 	fSlow36 = (0 - ((1 - fSlow2) / fSlow34));
	double 	fSlow37 = double(fslider5);
	double 	fSlow38 = (pow(1e+01,(2 * (fSlow37 * double(fslider4)))) / fSlow6);
	double 	fSlow39 = double(fslider6);
	double 	fSlow40 = (0.0010000000000000009 * pow(10,(0.05 * (double(fslider7) - 10))));
	double 	fSlow41 = (0 - fSlow2);
	double 	fSlow42 = (1.0 / (fSlow1 * fSlow13));
	double 	fSlow43 = (2 * (0 - fSlow4));
	double 	fSlow44 = (pow(1e+01,(2 * (fSlow37 * double(fslider8)))) / fSlow6);
	double 	fSlow45 = (0.0010000000000000009 * pow(10,(0.05 * (double(fslider9) - 10))));
	double 	fSlow46 = (1 + ((fSlow2 - 1.0) / fSlow1));
	double 	fSlow47 = (1.0 / (1 + ((1.0 + fSlow2) / fSlow1)));
	double 	fSlow48 = (0 - fSlow9);
	double 	fSlow49 = (1.0 / (fSlow8 * fSlow20));
	double 	fSlow50 = (2 * (0 - fSlow11));
	double 	fSlow51 = pow(1e+01,(2 * (fSlow37 * double(fslider10))));
	double 	fSlow52 = (0.0010000000000000009 * pow(10,(0.05 * (double(fslider11) - 10))));
	double 	fSlow53 = (1 + ((fSlow9 - 1.0) / fSlow8));
	double 	fSlow54 = (1.0 / (1 + ((1.0 + fSlow9) / fSlow8)));
	double 	fSlow55 = (0 - fSlow18);
	double 	fSlow56 = (2 * (0 - fSlow16));
	double 	fSlow57 = pow(1e+01,(2 * (fSlow37 * double(fslider12))));
	double 	fSlow58 = (0.0010000000000000009 * pow(10,(0.05 * (double(fslider13) - 10))));
	double 	fSlow59 = (1 - fSlow22);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		fRec10[0] = ((1e-20 * (1 - iVec0[1])) - fRec10[1]);
		double fTemp0 = (double)input0[i];
		double fTemp1 = (fSlow22 * fTemp0);
		double fTemp2 = (fTemp1 + (fSlow23 * fRec11[1]));
		fVec1[IOTA&4095] = fTemp2;
		fRec11[0] = (0.5 * (fVec1[(IOTA-iSlow26)&4095] + fVec1[(IOTA-iSlow25)&4095]));
		fRec9[0] = ((((iSlow27)?fRec11[0]:fTemp1) + fRec10[0]) - (fConst7 * ((fConst5 * fRec9[2]) + (fConst3 * fRec9[1]))));
		double fTemp3 = (fRec9[0] + (fRec9[2] + (2 * fRec9[1])));
		fVec2[0] = fTemp3;
		fRec8[0] = ((fConst12 * fRec8[1]) + (fConst11 * ((fConst8 * fVec2[0]) + (fConst9 * fVec2[1]))));
		fRec7[0] = ((fSlow30 * fRec7[1]) + (fSlow29 * (fRec8[1] + fRec8[0])));
		fRec6[0] = (fRec7[0] - (fSlow21 * ((fSlow19 * fRec6[2]) + (fSlow17 * fRec6[1]))));
		double fTemp4 = (fRec6[0] + (fRec6[2] + (2 * fRec6[1])));
		double fTemp5 = (fSlow21 * fTemp4);
		fVec3[0] = fTemp5;
		fRec5[0] = ((fSlow33 * fRec5[1]) + (fSlow32 * (fVec3[0] + fVec3[1])));
		fRec4[0] = (fRec5[0] - (fSlow14 * ((fSlow12 * fRec4[1]) + (fSlow10 * fRec4[2]))));
		double fTemp6 = (fRec4[0] + (fRec4[2] + (2 * fRec4[1])));
		double fTemp7 = (fSlow14 * fTemp6);
		fVec4[0] = fTemp7;
		fRec3[0] = ((fSlow36 * fRec3[1]) + (fSlow35 * (fVec4[0] + fVec4[1])));
		fRec2[0] = (fRec3[0] - (fSlow7 * ((fSlow5 * fRec2[1]) + (fSlow3 * fRec2[2]))));
		double fTemp8 = max((double)-1, min((double)1, (fSlow39 + (fSlow38 * (fRec2[0] + (fRec2[2] + (2 * fRec2[1])))))));
		fRec12[0] = (fSlow40 + (0.999 * fRec12[1]));
		fRec14[0] = ((fSlow36 * fRec14[1]) + (fSlow35 * ((fSlow42 * fTemp6) + (fSlow41 * fVec4[1]))));
		fRec13[0] = (fRec14[0] - (fSlow7 * ((fSlow5 * fRec13[1]) + (fSlow3 * fRec13[2]))));
		double fTemp9 = max((double)-1, min((double)1, (fSlow39 + (fSlow44 * ((fSlow43 * fRec13[1]) + (fSlow4 * (fRec13[2] + fRec13[0])))))));
		fRec15[0] = (fSlow45 + (0.999 * fRec15[1]));
		double fTemp10 = (fSlow5 * fRec16[1]);
		fRec18[0] = ((fSlow33 * fRec18[1]) + (fSlow32 * ((fSlow49 * fTemp4) + (fSlow48 * fVec3[1]))));
		fRec17[0] = (fRec18[0] - (fSlow14 * ((fSlow12 * fRec17[1]) + (fSlow10 * fRec17[2]))));
		fRec16[0] = ((fSlow14 * ((fSlow50 * fRec17[1]) + (fSlow11 * (fRec17[2] + fRec17[0])))) - (fSlow47 * ((fSlow46 * fRec16[2]) + fTemp10)));
		double fTemp11 = max((double)-1, min((double)1, (fSlow39 + (fSlow51 * (fRec16[2] + (fSlow47 * (fTemp10 + (fSlow46 * fRec16[0]))))))));
		fRec19[0] = (fSlow52 + (0.999 * fRec19[1]));
		double fTemp12 = (fSlow5 * fRec20[1]);
		double fTemp13 = (fSlow12 * fRec21[1]);
		fRec23[0] = ((fSlow30 * fRec23[1]) + (fSlow29 * ((fSlow18 * fRec8[0]) + (fSlow55 * fRec8[1]))));
		fRec22[0] = (fRec23[0] - (fSlow21 * ((fSlow19 * fRec22[2]) + (fSlow17 * fRec22[1]))));
		fRec21[0] = ((fSlow21 * ((fSlow56 * fRec22[1]) + (fSlow16 * (fRec22[2] + fRec22[0])))) - (fSlow54 * ((fSlow53 * fRec21[2]) + fTemp13)));
		fRec20[0] = ((fRec21[2] + (fSlow54 * (fTemp13 + (fSlow53 * fRec21[0])))) - (fSlow47 * ((fSlow46 * fRec20[2]) + fTemp12)));
		double fTemp14 = max((double)-1, min((double)1, (fSlow39 + (fSlow57 * (fRec20[2] + (fSlow47 * (fTemp12 + (fSlow46 * fRec20[0]))))))));
		fRec24[0] = (fSlow58 + (0.999 * fRec24[1]));
		double fTemp15 = (((((fRec24[0] * fTemp14) * (1 - (0.3333333333333333 * faustpower<2>(fTemp14)))) + ((fRec19[0] * fTemp11) * (1 - (0.3333333333333333 * faustpower<2>(fTemp11))))) + ((fRec15[0] * fTemp9) * (1 - (0.3333333333333333 * faustpower<2>(fTemp9))))) + ((fRec12[0] * fTemp8) * (1 - (0.3333333333333333 * faustpower<2>(fTemp8)))));
		fVec5[0] = fTemp15;
		fRec1[0] = ((fConst16 * fRec1[1]) + (fConst15 * (fVec5[0] + fVec5[1])));
		output0[i] = (FAUSTFLOAT)((fSlow59 * fTemp0) + (fRec1[0] * fRec0[0]));
		// post processing
		fRec1[1] = fRec1[0];
		fVec5[1] = fVec5[0];
		fRec24[1] = fRec24[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec19[1] = fRec19[0];
		fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec18[1] = fRec18[0];
		fRec15[1] = fRec15[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec14[1] = fRec14[0];
		fRec12[1] = fRec12[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fVec4[1] = fVec4[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec3[1] = fVec3[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fVec2[1] = fVec2[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec11[1] = fRec11[0];
		IOTA = IOTA+1;
		fRec10[1] = fRec10[0];
		fRec0[1] = fRec0[0];
		iVec0[1] = iVec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("gx_distortion.drive",N_("Drive"),"S","",&fslider5, 0.64, 0.0, 1.0, 0.01);
	reg.registerVar("gx_distortion.gain",N_("Gain"),"S","",&fslider0, 2.0, -1e+01, 1e+01, 0.1);
	reg.registerVar("gx_distortion.high_drive",N_("Hi"),"S","",&fslider12, 1.0, 0.0, 1.0, 0.01);
	reg.registerVar("gx_distortion.high_gain",N_("Hi"),"S","",&fslider13, 1e+01, -1e+01, 2e+01, 0.1);
	reg.registerVar("gx_distortion.level",N_("Level"),"S","",&fslider6, 0.0, 0.0, 0.5, 0.01);
	reg.registerVar("gx_distortion.low_drive",N_("Lo"),"S","",&fslider4, 1.0, 0.0, 1.0, 0.01);
	reg.registerVar("gx_distortion.low_gain",N_("Lo"),"S","",&fslider7, 1e+01, -1e+01, 2e+01, 0.1);
	reg.registerVar("gx_distortion.middle_h_drive",N_("HiMid"),"S","",&fslider10, 1.0, 0.0, 1.0, 0.01);
	reg.registerVar("gx_distortion.middle_h_gain",N_("HiMid"),"S","",&fslider11, 1e+01, -1e+01, 2e+01, 0.1);
	reg.registerVar("gx_distortion.middle_l_drive",N_("LoMid"),"S","",&fslider8, 1.0, 0.0, 1.0, 0.01);
	reg.registerVar("gx_distortion.middle_l_gain",N_("LoMid"),"S","",&fslider9, 1e+01, -1e+01, 2e+01, 0.1);
	reg.registerVar("gx_distortion.resonator.on_off",N_("resonat"),"B","",&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("gx_distortion.split_high_freq",N_("Split Hi"),"S","",&fentry2, 1.25e+03, 1.25e+03, 1.2e+04, 1e+01);
	reg.registerVar("gx_distortion.split_low_freq",N_("Split Lo"),"S","",&fentry0, 2.5e+02, 2e+01, 6e+02, 1e+01);
	reg.registerVar("gx_distortion.split_middle_freq",N_("Split Mid"),"S","",&fentry1, 6.5e+02, 6e+02, 1.25e+03, 1e+01);
	reg.registerVar("gx_distortion.trigger",N_("Trigger"),"S","",&fslider2, 0.12, 0.0, 1.0, 0.01);
	reg.registerVar("gx_distortion.vibrato",N_("Vibrato"),"S","",&fslider3, 1.0, 0.0, 1.0, 0.01);
	reg.registerVar("gx_distortion.wet_dry",N_("Wet/Dry"),"S",N_("percentage of processed signal in output signal"),&fslider1, 1e+02, 0.0, 1e+02, 1.0);
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
